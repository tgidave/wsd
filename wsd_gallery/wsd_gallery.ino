//*****************************************************************************
//
// wsd_gallery.c
//
// This program receives wind speed and direction data from the wsd_sensor 
// program and displays that data using the servo and LED hardware.
// Data is collected five time per second by the wsd_sensor progran and is 
// accumulated in two arrays, the wind speed array and the wind direction array.
// These arrays are formatted into character data which is delimited by a ','
// character.  The received data is reformatted into short integer values
// and placed back into the windSpeed and compassHeading arrays.  That data
// is then played back to the display hardware at 200 ms intervals. 
//
//*****************************************************************************

#include "wsd_defines.h"
#include "wsd_sensor.h"

#define SERVO_UPDATE_LIMIT -1 // If the wind speed is equal to or less than this
                              // value the servo direction is not updated.  A value 
                              // of -1 should always update the servo direction.

const int ledPin1 =  A5;
const int ledPin2 =  A4; // the number of the LED pin driver

short windSpeed[ARRAY_SIZE];

short compassHeading[ARRAY_SIZE];

int arrayIndex = ARRAY_SIZE;

short dmaRing[DMA_RING_SIZE];
  
int dmaRingIndex;  

Servo myservo0; // create servo object to control servo 0
Servo myservo1; // create servo object to control servo 1

int incrementDmaRingIndex(int indexIn) {

  indexIn++;

  if ( indexIn >= DMA_RING_SIZE) {
    return(0);
  }

  return(indexIn);
}

short calcDirMovingAverage(short dataIn) {

  int i;
  int dmaRingTotal = 0;

  dmaRing[dmaRingIndex] = dataIn;

  for (i = incrementDmaRingIndex(dmaRingIndex);i != dmaRingIndex; i = incrementDmaRingIndex(i)) {
    dmaRingTotal += dmaRing[i];
  }

  dmaRingIndex = incrementDmaRingIndex(dmaRingIndex);
  return((short)(dmaRingTotal / DMA_RING_SIZE));
}

//*****************************************************************************
//
// void speedrProcess(const char* event, const char* data)
//
// INPUT:
//      event - an indication of what event has occured.
//
//      data - the data accumulated by the sensor program.
//
// This is the interrupt processing routine that receives data from the sensor
// program.  This routine runs only when data is received and can interrupt the
// loop process at any point.
//
// The data sent by the sensor program is received here and is reformatted 
// from character data to native short integer format and placed back into an 
// array.  The array index variable is then set to zero to indicate that new 
// data has been received and is ready to process.
//
//*****************************************************************************

void speedrProcess(const char* event, const char* data) {

  int i;

  char* dataPtr;
  char* tmpPtr;

  dataPtr = (char *)data;

  for (i = 0; i < ARRAY_SIZE; ++i) {

    tmpPtr = strchr(dataPtr, DELIMITER_CHAR);
    *tmpPtr = 0;
    windSpeed[i] = (short)strtol(dataPtr, NULL, 10);  //gets wind speed and cast to short
    dataPtr = tmpPtr + 1;

    tmpPtr = strchr(dataPtr, DELIMITER_CHAR);
    *tmpPtr = 0;
    compassHeading[i] = (short)strtol(dataPtr, NULL, 10);  //gets wind direction and cast to short
    dataPtr = tmpPtr + 1;
  }

  arrayIndex = 0;
}

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

void setup() {

  int i;

  Particle.subscribe(SENSOR_NBR, speedrProcess);

  // begin light event setup here:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  //begin servo point setup here:
  myservo0.attach(D0);  // attaches the servo on pin D0 to the servo object
  myservo1.attach(D1);  // attaches the servo on pin D1 to the servo object

  for (i = 0; i < DMA_RING_SIZE; ++i) {
    dmaRing[i] = 0;
  }

  dmaRingIndex = 0;
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
// Main loop of the system.  This function processes the wind speed and heading
// information received from the sensor program.  If the array index is set to 
// ARRAY_SIZE, past the end of the array,  this routine does nothing.  If the 
// array index is less than ARRAY_SIZE, the array entry pointed to by the array
// index is processed, the array index is incremented, processing is delayed
// by mSECOND_DELAY  milliseconds, and then the loop processing returns.
// 
//*****************************************************************************

void loop() {

  short speedMap;
  short direction;

  short directionMap0;
  short directionMap1;

  int delayTime = mSECOND_DELAY;

  if (arrayIndex < ARRAY_SIZE) {

    speedMap = map(windSpeed[arrayIndex], 0, 50, 0, 255);
    direction = calcDirMovingAverage(compassHeading[arrayIndex]); 

    if (speedMap > SERVO_UPDATE_LIMIT) {  // If the wind speed is above the servo
                                          // update limit, update the servo direction.
      delayTime -= 50;    // we know we are going to delay 50ms so adjust for it.

      if (direction >= 0 && direction <= 90) {
      analogWrite(ledPin2, 0);
      directionMap0 = map(direction, 0, 180, 0, 170);
      myservo0.write(directionMap0);
      delay(50);
      analogWrite(ledPin1, speedMap);
      myservo1.write(170);
    }

    else if (direction >= 91 && direction <= 180) {
      analogWrite(ledPin2, 0);
      directionMap0 = map(direction, 0, 180, 0, 170);
      myservo0.write(directionMap0);
      delay(50);
      analogWrite(ledPin1, speedMap);
      myservo1.write(0);
    }

    else if (direction >= 181 && direction <= 270) {
      analogWrite(ledPin1, 0);
      directionMap1 = map(direction, 181, 360, 0, 170);
      myservo1.write(directionMap1);
      delay(50);
      analogWrite(ledPin2, speedMap);
      myservo0.write(170);
    }

    else {
      analogWrite(ledPin1, 0);
      directionMap1 = map(direction, 181, 360, 0, 170);
      myservo1.write(directionMap1);
      delay(50);
      analogWrite(ledPin2, speedMap);
      myservo0.write(0);
      }
    }

    else {  // The wind speed is below the SERVO_UPDATE_LIMIT.  Just set the light brightness.
            // Since we don't know which LED was on last and the wind speed is very low just go 
            // ahead and set both LEDs to the current value.  This is important only when the LED 
            // was set very bright during the last loop.
      analogWrite(ledPin1, speedMap);  
      analogWrite(ledPin2, speedMap);
    }

    arrayIndex += 1;
  }

  delay(delayTime);
}

