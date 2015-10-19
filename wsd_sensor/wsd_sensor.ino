//*****************************************************************************
//
// wsd_sensor.c
//
// This program uses a wind speed sensor and a compass sensor to monitor
// the current wind speed and direction.  Data is collected five time pre 
// second and each value is accumulated in two arrays, the wind speed 
// array and the wind direction array.  When the arrays are full they are 
// formatted into a transmittable character array, terminated with a NULL 
// and then transmitted to the subscribed device.
//
//*****************************************************************************

#define CHECK_CONNECTED // Comment this out to remove code that checkes that 
                        // the device is connected and reconnects if not.

#include <stdio.h>

// beign digital compass code here
#if defined (SPARK)
#include "Adafruit_Sensor.h"
#include "Adafruit_HMC5883_U.h"
#include "math.h"
#else
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#endif

#include "wsd_defines.h"          // Defines common to all programs.
#include "wsd_sensor.h"           // Define for sensor device ID
//#include "wind_sensor.h"

const int OutPin = A0;            // wind sensor analog pin  hooked up to Wind P sensor "OUT" pin
const int TempPin = A2;           // temp sesnsor analog pin hooked up to Wind P sensor "TMP" pin

short windSpeed[ARRAY_SIZE];

short compassHeading[ARRAY_SIZE];

int arrayIndex = 0;

/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

//***************************************************************************** 
// void setup( void )
// 
// INPUT:
//        Nothing
// 
// OUTPUT:
//        Nothing
// 
// This is the initialization routine.  This routine is called only one time
// during system initialization.  Both hardware and software initialization 
// occurs here. 
// 
//*****************************************************************************

void setup(void) {
  // digital compass setup here - no additional setup commands for Rev P wind sensor:
  Serial.begin(9600);

  /* Initialise the sensor */
  if (!mag.begin()) {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }
}

/* Assign a unique ID to this sensor at the same time */
//Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

//***************************************************************************** 
// uint getWindSpeed( void )
// 
// INPUT:
//        Nothing.
// 
// OUTPUT:
//        An unsigned integer containing the current wind speed.
// 
// This function reads and calculated the current wind speed and 
// returns it as an unsigned intiger.
//
//*****************************************************************************

short getWindSpeed(void) {

  // read wind
  // ck added divide by 6 to account for 12 bit 3.3V ADC (?)
  long windADunits = analogRead(OutPin) / 6;
  float windMPH;

  //ck added declaration to enable float to long
  long wind;

  // wind formula derived from a wind tunnel data, annemometer and some fancy Excel regressions
  // this scalin doesn't have any temperature correction in it yet
  // ck changed 264 to 3000
  windMPH = pow((((float)windADunits - 300.0) / 85.6814), 3.36814);

  //the line below converts the windMPH to a long
  wind = windMPH + 0.5;

  return (short(wind));

}

//***************************************************************************** 
// uint getWindHeading( void )
// 
// INPUT:
//        Nothing.
// 
// OUTPUT:
//        An unsigned integer containing the current wind heading.
// 
// This function reads and calculated the current wind heading and 
// returns it as an unsigned intiger.
//
//*****************************************************************************

short getWindHeading( void ) {

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading;

  //ck added lines below to make publish conversion
  int headingInt;

  float headingDegrees;

  //begin digital compass loop code here:
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);

  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  //Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  //Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  //Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  heading = atan2(event.magnetic.y, event.magnetic.x);

  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.

  heading += DECLINATION_ANGLE;

  // Correct for when signs are reversed.
  if (heading < 0) {
    heading += 2 * M_PI;
  }

  // Check for wrap due to addition of declination.
  if (heading > 2 * M_PI) {
    heading -= 2 * M_PI;
  }

  // Convert radians to degrees for readability.
  headingDegrees = heading * 180 / M_PI;

  //Serial.print("Heading (degrees): "); Serial.println(headingDegrees);

  //ck Change the hading from float to int
  headingInt = headingDegrees + 0.5;

  return (short(headingInt));
}

//***************************************************************************** 
// void formatAndPublishData( void )
// 
// INPUT:
//        Nothing, but uses both the global wind speed and direction arrays.
// 
// OUTPUT:
//        Nothing, but formats the wind speed and direction arrays into a 
//        comma delimited data line that can be transmitted over the internet 
//        and then transmits it to the subscribed device.
// 
// This function takes both the wind speed and direction arrays and reformats
// them into a format that can be transmitted over the internet to the 
// subscribed device.  The format of the arrays is unsigned integer.  Data 
// transmitted to the subscribed device must be an array of characters
// terminated with a NULL.  Ten wind speed values and ten wind direction
// values must be sent with each transmission so a comma character ',' is used
// to indicate the end of each value field.  The wind speed and wind direction
// values are formated as pairs, IE ws1,wd1,ws2,wd2, ...
// 
// After the data is formatted it is sent to the subscribed device using the
// Particle.publish class.
// 
//*****************************************************************************

void formatAndPublishData(void) {

  int i;    // Index countere

  char transBuff[TRANSBUFF_SIZE];   // transmit buffer
  char buff[BUFF_SIZE];             // buffer for intermediate results.

  *transBuff = 0;                   // initialize the transmit buffer.

  // format both the 
  for (i = 0; i < ARRAY_SIZE; ++i) {    
    sprintf(buff, "%d", windSpeed[i]);
    strcat(buff, DELIMITER_STRING);
    strcat(transBuff, buff);

    sprintf(buff, "%d", compassHeading[i]);
    strcat(buff, DELIMITER_STRING);
    strcat(transBuff, buff);
  }

#ifdef DEBUG
  Serial.print(transBuff);
  Serial.print(CRLF);
#endif

  // initiate cloud function to publish the wind MPH as ascii
  //Particle.publish("wind01pub", buffSpeed);
  Particle.publish(SENSOR_NBR, transBuff);
}


//***************************************************************************** 
// void loop( void )
// 
// INPUT:
//        Nothing
// 
// OUTPUT:
//        Nothing
// 
// Main loop of the system.  This function gathers the wind speed and heading
// information populates the wind speed and heading arrays.  When the arrays
// are full the arrays are formatted for transmission and then published.  
// 
//*****************************************************************************

void loop(void) {
  //begin Rev C wind sensor declarations here:

#ifdef CHECK_CONNECTED
  if (!Particle.connected()) {
      Particle.connect();
  }
#endif

  windSpeed[arrayIndex] = getWindSpeed();
  compassHeading[arrayIndex] = getWindHeading();

  arrayIndex++;

  if (arrayIndex >= ARRAY_SIZE) {
    formatAndPublishData();
    arrayIndex = 0;
  }

  delay(mSECOND_DELAY);
}


