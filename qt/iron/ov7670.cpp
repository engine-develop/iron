// Reference: https://github.com/ComputerNerd/ov7670-simple/blob/master/main.c
//
#ifdef __AVR__

//------------------------------------------------------------------------------

// Arduino
#include <Arduino.h>
#include <Wire/Wire.h>
#include <SPI/SPI.h>

#include <util/twi.h>
#include <util/delay.h>

// Engine
#include "i2c.hpp"

#include "ov7670.hpp"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Define registers
//

// Register constants
//
enum Registers
{
    REG_GAIN            = 0x00, /* AGC - Gain control gain setting */
    REG_BLUE            = 0x01, /* AGC - Blue channel gain setting */
    REG_RED             = 0x02, /* AGC - Red channel gain setting */
    REG_VREF            = 0x03, /* Vertical frame control */

    REG_COM1            = 0x04, /* Common control 1 */
    COM1_CCIR656_E      = 0x40, /* CCIR656 enable */

    REG_BAVE            = 0x05, /* U/B Average level */
    REG_GbAVE           = 0x06, /* Y/Gb Average level */
    REG_AECHH           = 0x07, /* Exposure Value - AEC MSB 5 bits */
    REG_RAVE            = 0x08, /* V/R Average level */

    REG_COM2            = 0x09, /* Common Control 2 */
    COM2_SSLEEP         = 0x10, /* Soft sleep mode */

    REG_PID             = 0x0a, /* Product ID Number MSB (Read only) */
    REG_VER             = 0x0b, /* Product ID Number LSB (Read only) */

    REG_COM3            = 0x0c, /* Common Control 3 */
    COM3_SWAP           = 0x40, /* Output data MSB and LSB swap */
    COM3_SCALEEN        = 0x08, /* Scale enable */
    COM3_DCWEN          = 0x04, /* Enable downsamp/crop/window */

    REG_COM4            = 0x0d, /* Common Control 4 */
    REG_COM5            = 0x0e, /* Common Control 5 */
    REG_COM6            = 0x0f, /* Common Control 6 */
    REG_AECH            = 0x10, /* Exposure Value */

    REG_CLKRC           = 0x11, /* Internal Clock */
    CLKRC_CLK_EXT       = 0x40, /* Use external clock directly */
    CLKRC_CLK_SCALE     = 0x3f, /* Internal clock pre-scalar */

    REG_COM7            = 0x12, /* Common Control 7 */
    COM7_RESET          = 0x80, /* SCCB Register reset */
    COM7_FMT_CIF        = 0x20, /* CIF format */
    COM7_FMT_QVGA       = 0x10, /* QVGA format */
    COM7_FMT_QCIF       = 0x08, /* QCIF format */
    COM7_FMT_RGB        = 0x04, /* RGB format */
    COM7_CLR_BAR        = 0x02, /* Color bar */
    COM7_FMT_RAW        = 0x00, /* Raw RGB format */
    COM7_FMT_RAW_YUV    = 0x00, /* YUV */
    COM7_FMT_RAW_RGB    = 0x00, /* RGB */
    COM7_FMT_RAW_BAYER  = 0x01, /* Bayer RAW */
    COM7_FMT_RAW_PBAYER = 0x05, /* Processed Bayer RAW */

    REG_COM8            = 0x13, /* Common Control 8 */
    COM8_FASTAEC        = 0x80, /* Enable fast AGC/AEC */
    COM8_AECSTEP        = 0x40, /* AEC - Step size limit */
    COM8_BFILT          = 0x20, /* Band filter enable */
    COM8_AGC            = 0x04, /* AGC enable */
    COM8_AWB            = 0x02, /* AWB enable */
    COM8_AEC            = 0x01, /* AEC enable */

    REG_COM9            = 0x14, /* Common Control 9 */

    REG_COM10           = 0x15, /* Common Control 10 */
    COM10_HSYNC         = 0x40, /* HSYNC instead of HREF */
    COM10_PCLK_HB       = 0x20, /* Suppress PCLK on horiz blank */
    COM10_HREF_REV      = 0x08, /* Reverse HREF */
    COM10_VS_LEAD       = 0x04, /* VSYNC on clock leading edge */
    COM10_VS_NEG        = 0x02, /* VSYNC negative */
    COM10_HS_NEG        = 0x01, /* HSYNC negative */

    REG_HSTART          = 0x17, /* Horiz start high bits */
    REG_HSTOP           = 0x18, /* Horiz stop high bits */
    REG_VSTART          = 0x19, /* Vert start high bits */
    REG_VSTOP           = 0x1a, /* Vert stop high bits */
    REG_PSHFT           = 0x1b, /* Pixel delay after HREF */
    REG_MIDH            = 0x1c, /* Manuf. ID high */
    REG_MIDL            = 0x1d, /* Manuf. ID low */
    REG_MVFP            = 0x1e, /* Mirror / vflip */
    MVFP_MIRROR         = 0x20, /* Mirror image */
    MVFP_FLIP           = 0x10, /* Vertical flip */
    REG_AEW             = 0x24, /* AGC upper limit */
    REG_AEB             = 0x25, /* AGC lower limit */
    REG_VPT             = 0x26, /* AGC/AEC fast mode op region */
    REG_HSYST           = 0x30, /* HSYNC rising edge delay */
    REG_HSYEN           = 0x31, /* HSYNC falling edge delay */
    REG_HREF            = 0x32, /* HREF pieces */
    REG_TSLB            = 0x3a, /* lots of stuff */
    TSLB_YLAST          = 0x04, /* UYVY or VYUY - see com13 */

    REG_COM11           = 0x3b, /* Common Control 11 */
    COM11_NIGHT         = 0x80, /* NIght mode enable */
    COM11_NMFR          = 0x60, /* Two bit NM frame rate */
    COM11_HZAUTO        = 0x10, /* Auto detect 50/60 Hz */
    COM11_50HZ          = 0x08, /* Manual 50Hz select */
    COM11_EXP           = 0x02,

    REG_COM12           = 0x3c, /* Common Control 12 */
    COM12_HREF          = 0x80, /* HREF always */

    REG_COM13           = 0x3d, /* Common Control 13 */
    COM13_GAMMA         = 0x80, /* Gamma enable */
    COM13_UVSAT         = 0x40, /* UV saturation auto adjustment */
    COM13_UVSWAP        = 0x01, /* V before U - w/TSLB */

    REG_COM14           = 0x3e, /* Common Control 14 */
    COM14_DCWEN         = 0x10, /* DCW/PCLK-scale enable */

    REG_EDGE            = 0x3f, /* Edge enhancement factor */

    REG_COM15           = 0x40, /* Common Control 15 */
    COM15_R10F0         = 0x00, /* Data range 10 to F0 */
    COM15_R01FE         = 0x80, /*            01 to FE */
    COM15_R00FF         = 0xc0, /*            00 to FF */
    COM15_RGB565        = 0x10, /* RGB565 output */
    COM15_RGB555        = 0x30, /* RGB555 output */

    REG_COM16           = 0x41, /* Common Control 16 */
    COM16_AWBGAIN       = 0x08, /* AWB gain enable */

    REG_COM17           = 0x42, /* Common Control 17 */
    COM17_AECWIN        = 0xc0, /* AEC window - must match COM4 */
    COM17_CBAR          = 0x08, /* DSP Color bar */

    /*
     * This matrix defines how the colors are generated, must be
     * tweaked to adjust hue and saturation.
     *
     * Order: v-red, v-green, v-blue, u-red, u-green, u-blue
     *
     * They are nine-bit signed quantities, with the sign bit
     * stored in 0x58.  Sign for v-red is bit 0, and up from there.
     */
    REG_CMATRIX_BASE    = 0x4f,
    REG_CMATRIX_LEN     = 6,
    REG_CMATRIX_SIGN    = 0x58,

    REG_BRIGHT          = 0x55, /* Brightness */
    REG_CONTRAS         = 0x56, /* Contrast control */
    REG_GFIX            = 0x69, /* Fix gain control */
    REG_REG76           = 0x76, /* OV's name */
    R76_BLKPCOR         = 0x80, /* Black pixel correction enable */
    R76_WHTPCOR         = 0x40, /* White pixel correction enable */
    REG_RGB444          = 0x8c, /* RGB 444 control */
    R444_ENABLE         = 0x02, /* Turn on RGB444, overrides 5x5 */
    R444_RGBX           = 0x01, /* Empty nibble at end */
    REG_HAECC1          = 0x9f, /* Hist AEC/AGC control 1 */
    REG_HAECC2          = 0xa0, /* Hist AEC/AGC control 2 */
    REG_BD50MAX         = 0xa5, /* 50hz banding step limit */
    REG_HAECC3          = 0xa6, /* Hist AEC/AGC control 3 */
    REG_HAECC4          = 0xa7, /* Hist AEC/AGC control 4 */
    REG_HAECC5          = 0xa8, /* Hist AEC/AGC control 5 */
    REG_HAECC6          = 0xa9, /* Hist AEC/AGC control 6 */
    REG_HAECC7          = 0xaa, /* Hist AEC/AGC control 7 */
    REG_BD60MAX         = 0xab, /* 60hz banding step limit */
    MTX1                = 0x4f, /* Matrix Coefficient 1 */
    MTX2                = 0x50, /* Matrix Coefficient 2 */
    MTX3                = 0x51, /* Matrix Coefficient 3 */
    MTX4                = 0x52, /* Matrix Coefficient 4 */
    MTX5                = 0x53, /* Matrix Coefficient 5 */
    MTX6                = 0x54, /* Matrix Coefficient 6 */
    MTXS                = 0x58, /* Matrix Coefficient Sign */
    AWBC7               = 0x59, /* AWB Control 7 */
    AWBC8               = 0x5a, /* AWB Control 8 */
    AWBC9               = 0x5b, /* AWB Control 9 */
    AWBC10              = 0x5c, /* AWB Control 10 */
    AWBC11              = 0x5d, /* AWB Control 11 */
    AWBC12              = 0x5e, /* AWB Control 12 */
    GGAIN               = 0x6a, /* G Channel AWB Gain */
    DBLV                = 0x6b, /* ? */
    AWBCTR3             = 0x6c, /* AWB Control 3 */
    AWBCTR2             = 0x6d, /* AWB Control 2 */
    AWBCTR1             = 0x6e, /* AWB Control 1 */
    AWBCTR0             = 0x6f /* AWB Control 0 */
};

//------------------------------------------------------------------------------

#define camAddr_WR 0x42
#define camAddr_RD 0x43

static void error_led(void){
    DDRB|=32;//make sure led is output
    while(1){//wait for reset
        PORTB^=32;// toggle led
        _delay_ms(100);
    }
}
static void twiStart(void){
    TWCR=_BV(TWINT)| _BV(TWSTA)| _BV(TWEN);//send start
    while(!(TWCR & (1<<TWINT)));//wait for start to be transmitted
    if((TWSR & 0xF8)!=TW_START)
    {
        error_led();
    }
}
static void twiWriteByte(uint8_t DATA,uint8_t type){
    TWDR = DATA;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while (!(TWCR & (1<<TWINT))) {}
    if ((TWSR & 0xF8) != type)
    {
        error_led();
    }
}
static void twiAddr(uint8_t addr,uint8_t typeTWI){
    TWDR = addr;//send address
    TWCR = _BV(TWINT) | _BV(TWEN);		/* clear interrupt to start transmission */
    while ((TWCR & _BV(TWINT)) == 0);	/* wait for transmission */
    if ((TWSR & 0xF8) != typeTWI)
    {
        error_led();
    }
}
void wrReg(uint8_t reg,uint8_t dat){
    //send start condition
    twiStart();
    twiAddr(camAddr_WR,TW_MT_SLA_ACK);
    twiWriteByte(reg,TW_MT_DATA_ACK);
    twiWriteByte(dat,TW_MT_DATA_ACK);
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);//send stop
    _delay_ms(1);
}
static uint8_t twiRd(uint8_t nack){
    if (nack){
        TWCR=_BV(TWINT) | _BV(TWEN);
        while ((TWCR & _BV(TWINT)) == 0);	/* wait for transmission */
    if ((TWSR & 0xF8) != TW_MR_DATA_NACK)
    {
        error_led();
    }
        return TWDR;
    }else{
        TWCR=_BV(TWINT) | _BV(TWEN) | _BV(TWEA);
        while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
        if ((TWSR & 0xF8) != TW_MR_DATA_ACK)
        {
            error_led();
        }
        return TWDR;
    }
}
uint8_t rdReg(uint8_t reg){
    uint8_t dat;
    twiStart();
    twiAddr(camAddr_WR,TW_MT_SLA_ACK);
    twiWriteByte(reg,TW_MT_DATA_ACK);
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);//send stop
    _delay_ms(1);
    twiStart();
    twiAddr(camAddr_RD,TW_MR_SLA_ACK);
    dat=twiRd(1);
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);//send stop
    _delay_ms(1);
    return dat;
}

namespace engine
{

//------------------------------------------------------------------------------
//

OV7670::OV7670()
{
}

//------------------------------------------------------------------------------
//

OV7670::~OV7670()
{
}

//------------------------------------------------------------------------------
//

void OV7670::writeReg( uint8_t addr,
                            uint8_t data )
{
    Wire.beginTransmission( s_addr_w );
    Wire.write( addr );
    Wire.write( data );
    Wire.endTransmission();

    _delay_ms( 1 );
}

//------------------------------------------------------------------------------
//

uint8_t OV7670::readReg( uint8_t addr )
{
    Wire.beginTransmission( s_addr_w );
    Wire.write( addr );
    Wire.endTransmission();
    _delay_ms( 1 );

    Wire.requestFrom( s_addr_r, 1u );
    _delay_ms( 1 );

    return Wire.read();
}

//------------------------------------------------------------------------------
//

void OV7670::setup()
{
    //cli(); // Disable interrupts

    // Set up I2C
    //
    Wire.begin();
    disableI2CPullups();
#if 0
    delay(15);
    Serial.println( "a0" ); delay( 15 );

    Wire.beginTransmission(0x21);
    Serial.println( "a0.0" ); delay( 15 );
    Wire.write(byte(0x0A));
    Serial.println( "a0.1" ); delay( 15 );
    int n = Wire.endTransmission();
    Serial.println( n ); delay( 15 );

    Serial.println( "a1" ); delay( 15 );

    Wire.requestFrom(0x21, 1);
    Serial.println( "a1.0" ); delay( 15 );
    Serial.println( Wire.available() ); delay( 15 );
    //while(!Wire.available()){}
    Serial.println( "a1.1" ); delay( 15 );
    int val = Wire.read();
    Serial.println(val); delay( 15 );

    Serial.println( "a2" ); delay( 15 );
#endif
#if 0
    // Set up TWI for 100khz
    //
    //TWSR &= ~3; // Disable TWI prescaler
    //TWBR = 72; // Set to 100khz

    // Set up pins
    //
    DDRB  |= B00101111 /*47*/; // Clock/SPI pins as output, MISO input
    PORTB |= B00000110 /*6*/; // Set SS pins high
    DDRC &= ~B00001111 /*15*/; // D0-D3 camera as input
    DDRD &= ~B11111100 /*252*/; // D7-D4 and interrupt pins as input

    // Set up serial
    //
    //UBRR0H = 0;
    //UBRR0L = 3; // 3 = 0.5M 2M baud rate = 0 7 = 250k 207 is 9600 baud rate
    //UCSR0A |= 2; // Double speed aysnc
    //UCSR0B = (1<<RXEN0) | (1<<TXEN0); // Enable receiver and transmitter
    //UCSR0C = 6; // Async 1 stop bit 8bit char no parity bits

    // Set up SPI
    //
    //SPI.begin();
    //SPCR = B01010000 /*80*/; // SPI enable master
    //SPSR = B00000001 /*1*/; // Double speed

    uint8_t rd = 0;

    wrReg( REG_COM7, COM7_RESET );

    //rd = rdReg( REG_COM7 );
    //Serial.println( rd );

    //writeReg( REG_COM7, COM7_RESET ); // Reset registers to default
#endif
#if 0
    // Set up camera
    //
    writeReg( 0x15, 32 ); // PCLK does not toggle on HBLANK COM10
    //writeReg( 0x11, 32 ); // Register 0x11 is for pixel clock divider
    writeReg( REG_RGB444, 0x00 ); // Disable RGB444
    writeReg( REG_COM11, 226 ); // enable night mode 1/8 frame rate COM11*/
    //writeReg( 0x2E, 63 ); // Longer delay
    writeReg( REG_TSLB, 0x04 ); // 0D = UYVY  04 = YUYV
    writeReg( REG_COM13, 0x88 ); // connect to REG_TSLB
    //writeReg( REG_COM13, 0x8 ); // connect to REG_TSLB disable gamma
    #ifdef rgb565
        writeReg( REG_COM7, 0x04 ); // RGB + color bar disable
        writeReg( REG_COM15, 0xD0 ); // Set rgb565 with Full range	0xD0
    #elif defined rgbRAW
        writeReg( REG_COM7, 1 ); // raw rgb bayer
        writeReg( REG_COM15, 0xC0 ); // Full range
    #else
        writeReg( REG_COM7, 0x00 ); // YUV
        //writeReg( REG_COM17, 0x00 ); // color bar disable
        writeReg( REG_COM15, 0xC0 ); //Full range
    #endif
    //writeReg( REG_COM3, 0x04 );
    #if defined qqVGA || defined qVGA
        writeReg( REG_COM3, 4 );	// REG_COM3
    #else
        writeReg( REG_COM3, 0 ); // REG_COM3
    #endif
    //writeReg( 0x3e, 0x00 ); //  REG_COM14
    //writeReg( 0x72, 0x11 ); //
    //writeReg( 0x73, 0xf0 ); //
    //writeReg( REG_COM8, 0x8F ); // AGC AWB AEC Unlimited step size
    /*writeReg( REG_COM8, 0x88 ); // disable AGC disable AEC
    writeReg( REG_COM1, 3); // manual exposure
    writeReg( 0x07, 0xFF ); // manual exposure
    writeReg( 0x10, 0xFF ); // manual exposure*/
    #ifdef qqVGA
        writeReg( REG_COM14, 0x1a ); // divide by 4
        writeReg( 0x72, 0x22 ); // downsample by 4
        writeReg( 0x73, 0xf2 ); // divide by 4
        writeReg( REG_HSTART, 0x16 );
        writeReg( REG_HSTOP, 0x04 );
        writeReg( REG_HREF, 0xa4 );
        writeReg( REG_VSTART, 0x02 );
        writeReg( REG_VSTOP, 0x7a );
        writeReg( REG_VREF, 0x0a );
    #endif
    #ifdef qVGA
        writeReg( REG_COM14, 0x19 );
        writeReg( 0x72, 0x11 );
        writeReg( 0x73, 0xf1 );
        writeReg( REG_HSTART, 0x16 );
        writeReg( REG_HSTOP, 0x04 );
        writeReg( REG_HREF, 0x24 );
        writeReg( REG_VSTART, 0x02 );
        writeReg( REG_VSTOP, 0x7a );
        writeReg( REG_VREF, 0x0a );
    #else
        writeReg( 0x32, 0xF6 ); // was B6
        writeReg( 0x17, 0x13 ); // HSTART
        writeReg( 0x18, 0x01 ); // HSTOP
        writeReg( 0x19, 0x02 ); // VSTART
        writeReg( 0x1a, 0x7a ); // VSTOP
        //writeReg( 0x03, 0x0a ); // VREF
        writeReg( REG_VREF, 0xCA ); // set 2 high GAIN MSB
    #endif
    //writeReg( 0x70, 0x3a ); // Scaling Xsc
    //writeReg( 0x71, 0x35 ); // Scaling Ysc
    //writeReg( 0xA2, 0x02 ); // pixel clock delay
    //Color Settings
    //writeReg( 0, 0xFF ); // set gain to maximum possible
    //writeReg( 0xAA, 0x14 ); // Average-based AEC algorithm
    writeReg( REG_BRIGHT, 0x00 ); // 0x00(Brightness 0) - 0x18(Brightness +1) - 0x98(Brightness -1)
    writeReg( REG_CONTRAS, 0x40 );	// 0x40(Contrast 0) - 0x50(Contrast +1) - 0x38(Contrast -1)
    //writeReg( 0xB1, 0xB1 ); // Automatic Black level Calibration
    writeReg( 0xb1, 4 ); // really enable ABLC
    writeReg( MTX1, 0x80 );
    writeReg( MTX2, 0x80 );
    writeReg( MTX3, 0x00 );
    writeReg( MTX4, 0x22 );
    writeReg( MTX5, 0x5e );
    writeReg( MTX6, 0x80 );
    writeReg( MTXS, 0x9e );
    writeReg( AWBC7, 0x88 );
    writeReg( AWBC8, 0x88 );
    writeReg( AWBC9, 0x44 );
    writeReg( AWBC10, 0x67 );
    writeReg( AWBC11, 0x49 );
    writeReg( AWBC12, 0x0e );
    writeReg( REG_GFIX, 0x00 );
    //writeReg( GGAIN, 0 );
    writeReg( AWBCTR3, 0x0a );
    writeReg( AWBCTR2, 0x55 );
    writeReg( AWBCTR1, 0x11 );
    writeReg( AWBCTR0, 0x9f );
    //writeReg( 0xb0, 0x84 ); / /not sure what this does
    writeReg( REG_COM16, COM16_AWBGAIN ); // disable auto denoise and edge enhancement
    //writeReg( REG_COM16, 0 );
    writeReg( 0x4C, 0 );//disable denoise
    writeReg( 0x76, 0 );//disable denoise
    writeReg( 0x77, 0 );//disable denoise
    writeReg( 0x7B, 4 );//brighten up shadows a bit end point 4
    writeReg( 0x7C, 8 );//brighten up shadows a bit end point 8
    //writeReg( 0x88, 238); // darken highlights end point 176
    //writeReg( 0x89, 211); // try to get more highlight detail
    //writeReg( 0x7A, 60); // slope
    //writeReg( 0x26, 0xB4); // lower maximum stable operating range for AEC
    //hueSatMatrix( 0, 100 );
    //ov7670_store_cmatrix();
    //writeReg( 0x20,12); // set ADC range to 1.5x
    writeReg( REG_COM9,0x6A); // max gain to 128x
    writeReg( 0x74, 16); // disable digital gain
    //writeReg( 0x93, 15); // dummy line MSB
    writeReg( 0x11, 4);
    //writeReg( 0x2a, 5); //href delay
#endif

}

//------------------------------------------------------------------------------
//

void OV7670::read( uint16_t ws,
                   uint16_t hs,
                   uint16_t wg,
                   uint16_t hg )
{
#if 0
    // Wait for VSYNC, on pin 3 (counting from 0) portD
    //

    // Skip pixels (dummy?)
    while ( !(PIND&8) ) {} // wait for high
    while (  (PIND&8) ) {} // wait for low

    uint16_t l2;

    if ( hs )
    {
        while ( hs-- )
        {
            l2 = ws;

            while ( l2-- )
            {
                while (  (PIND&4) ) {} // wait for low
                while ( !(PIND&4) ) {} // wait for high
            }
        }
    }

    // Read pixels to SPI ram
    //
    while ( hg-- )
    {
        l2 = wg;

        while ( l2-- )
        {
            while (  (PIND&4) ); // wait for low
            SPDR = (PINC&15) | (PIND&240);
            while ( !(PIND&4) ); // wait for high
        }
    }
#endif
}

} // engine

#endif // __AVR__
