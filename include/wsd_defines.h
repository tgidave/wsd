//*****************************************************************************
//
//  wsp_defines.h
//
// Defines common to both the sensor and gallery programs.
//
//*****************************************************************************

#define WSD_DEBUG                 // Include debugging information
#define WSD_DEBUG_MAX             // Include more debugging information
                                  // MAX_DEBUG needs DEBUG to be on for it to work

#define ARRAY_SIZE        10      // Size of both the wind direction and the wind speed arrays

#define BUFF_SIZE         10      // Size of the intermediate results buffer for formatting
                                  // a single wind direction or wind speed value.  This buffer should
                                  // be able to hold the maximum value of an unsigned int (65535)
                                  // followed by a comma and then a NULL.

#define TRANSBUFF_SIZE    141     // Size of the transmit buffer.  This buffer needs to hold ten wind
                                  // speed values and ten wind direction values separated by a comma
                                  // along with a terminating NULL.  The maximum size as currently
                                  // configures would be (7 * 20) + 1 for 141 characters.

#define mSECOND_DELAY     200     // set to 200 mS or 5 time per second.

#define DECLINATION_ANGLE 0.22    // Declation angle for the wind speed calculation

#define DELIMITER_STRING  ","     // Transmit buffer data delimiter in string format
#define DELIMITER_CHAR    ','     // Transmit buffer data delimiter in character format
        
#define CRLF              "\r\n"  // Just a carrage return and a line feed (new line)

#define SERVO_DELAY       50

#define DMA_RING_SIZE     10
