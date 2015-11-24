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

// Uncomment the next line if you want the gallery devices to replay old data when
// they have processed all current data and no new data has arrived.

//#define REPLAY_OLD_DATA

#include "wsd_defines.h"
#include "wsd_sensor.h"

#define SERVO_UPDATE_LIMIT 3  // If the wind speed is equal to or less than this
                              // value the servo direction is not updated.  A value 
                              // of -1 should always update the servo direction.

//#define ADD_FLICKER           // Comment out this like to stop flickering.

#ifdef ADD_FLICKER
  
  #define FLICKER_ON_TIME 50  // This should probably not go above 1/2 the mSECOND_DELAY
  #define FLICKER_OFF_TIME 20 // This should probably not go above 1/2 the mSECOND_DELAY

  #define RANDOMIZE_FLICKER   // Comment out this line to remove randomness from the flicker.
      
  #ifdef RANDOMIZE_FLICKER    
    #define RANDOM_FLICKER_LIMIT_LOW  -10 //the absolute value of this should not go above 1/2 the lessor of FLICKER_ON_TIME and FLICKER_OFF_TIME
                                          // and should be less than RANDOM_FLICKER_LIMIT_HIGH
                                          
    #define RANDOM_FLICKER_LIMIT_HIGH 11  //the absolute value of this should not go above 1/2 the lessor of FLICKER_ON_TIME and FLICKER_OFF_TIME 
                                          // and should be greater than RANDOM_FLICKER_LIMIT_LOW  
  #endif    
#endif

#define LOWSPEED_FLICKER

#ifdef LOWSPEED_FLICKER
  #define LOWSPEED_FLICKER_LIMIT 100 
  #define LOWSPEED_FLICKER_ON_TIME  25
  #define LOWSPEED_FLICKER_OFF_TIME 975

  #define RANDOMIZE_LOWSPEED_FLICKER

  #ifdef RANDOMIZE_LOWSPEED_FLICKER
    #define LOWSPEED_FLICKER_RAND_LOW_LIMIT   -15
    #define LOWSPEED_FLICKER_RAND_HIGH_LIMIT  16
  #endif
#endif

const int ledPin1 =  A5;
const int ledPin2 =  A4; // the number of the LED pin driver

int userLED = D7;                 

int userLEDState = false;

short windSpeed[ARRAY_SIZE];

short compassHeading[ARRAY_SIZE];

int arrayIndex = ARRAY_SIZE;

short dmaRing[DMA_RING_SIZE];
  
int dmaRingIndex;  

int activeLED = ledPin1;

int lowSpeedFlickerOnTime;
int lowSpeedFlickerOffTime;

Servo myservo0; // create servo object to control servo 0
Servo myservo1; // create servo object to control servo 1

void FlipUserLED(void) {
  if (userLEDState == false) {
    userLEDState = true;
    digitalWrite(userLED, HIGH);
  } else {
    userLEDState = false;
    digitalWrite(userLED, LOW);
  }
}

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

  pinMode(userLED, OUTPUT);
  userLEDState = false;
  digitalWrite(userLED, LOW);

  // begin light event setup here:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  //begin servo point setup here:
  myservo0.attach(D0);  // attaches the servo on pin D0 to the servo object
  myservo1.attach(D1);  // attaches the servo on pin D1 to the servo object

  for (i = 0; i < ARRAY_SIZE; ++i) {
    windSpeed[ARRAY_SIZE] = 0;
    compassHeading[ARRAY_SIZE] = 0;
  }

  for (i = 0; i < DMA_RING_SIZE; ++i) {
    dmaRing[i] = 0;
  }

  dmaRingIndex = 0;

#ifdef LOWSPEED_FLICKER
  lowSpeedFlickerOnTime = lowSpeedFlickerOffTime = 0;
#endif
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

#ifdef ADD_FLICKER
  int flickerOnTime = FLICKER_ON_TIME;

  int flickerOffTime = FLICKER_OFF_TIME;

  bool flickerState = false;

  int randomFlicker;
#endif

#ifdef LOWSPEED_FLICKER
  int lsfDelayTime;
#endif

#ifdef REPLAY_OLD_DATA
// If REPLAY_OLD_DATA is defined and the array index is greater than or equal to
// ARRAY_SIZE set arrayIndex back to zero and replay the data.
  if (arrayIndex >= ARRAY_SIZE) { 
    arrayIndex = 0;               
  }
#endif

  if (arrayIndex < ARRAY_SIZE) {

    speedMap = map(windSpeed[arrayIndex], 0, 12, 20, 255);
    direction = calcDirMovingAverage(compassHeading[arrayIndex]); 

    if (speedMap > SERVO_UPDATE_LIMIT) {  // If the wind speed is above the servo
                                          // update limit, update the servo direction.

      if (direction >= 0 && direction <= 90) {
        analogWrite(ledPin2, 0);
        directionMap0 = map(direction, 0, 180, 0, 170);
        myservo0.write(directionMap0);
        activeLED = ledPin1;
        myservo1.write(170);
      }

      else if (direction >= 91 && direction <= 180) {
        analogWrite(ledPin2, 0);
        directionMap0 = map(direction, 0, 180, 0, 170);
        myservo0.write(directionMap0);
        activeLED = ledPin1;
        myservo1.write(0);
      }

      else if (direction >= 181 && direction <= 270) {
        analogWrite(ledPin1, 0);
        directionMap1 = map(direction, 181, 360, 0, 170);
        myservo1.write(directionMap1);
        activeLED = ledPin2;
        myservo0.write(170);
      }

      else {
        analogWrite(ledPin1, 0);
        directionMap1 = map(direction, 181, 360, 0, 170);
        myservo1.write(directionMap1);
        activeLED = ledPin2;
        myservo0.write(0);
      }
    }

    arrayIndex += 1;
  }

#ifdef LOWSPEED_FLICKER
  if (speedMap <= LOWSPEED_FLICKER_LIMIT) {

    if ((lowSpeedFlickerOnTime == 0) && 
        (lowSpeedFlickerOffTime == 0)) {
      lowSpeedFlickerOnTime = LOWSPEED_FLICKER_ON_TIME;
      lowSpeedFlickerOffTime = LOWSPEED_FLICKER_OFF_TIME;
#ifdef RANDOMIZE_LOWSPEED_FLICKER
      lowSpeedFlickerOnTime += random( LOWSPEED_FLICKER_RAND_LOW_LIMIT, LOWSPEED_FLICKER_RAND_HIGH_LIMIT );
#endif
    }

    while (delayTime > 0) {

      if (lowSpeedFlickerOnTime != 0) {
        analogWrite(activeLED, speedMap);

        if (delayTime <= lowSpeedFlickerOnTime ) {
          FlipUserLED();
          lowSpeedFlickerOnTime -= delayTime;
          lsfDelayTime = delayTime;
          delayTime = 0;

        } else {
          lsfDelayTime = lowSpeedFlickerOnTime;
          delayTime -= lowSpeedFlickerOnTime;
          lowSpeedFlickerOnTime = 0;
        }

      } else if (lowSpeedFlickerOffTime != 0 ) {
        analogWrite(activeLED, 0);

        if (delayTime <= lowSpeedFlickerOffTime ) {
          lowSpeedFlickerOffTime -= delayTime;
          lsfDelayTime = delayTime;
          delayTime = 0;

        } else { 
          lsfDelayTime = lowSpeedFlickerOffTime;
          delayTime -= lowSpeedFlickerOffTime;
          lowSpeedFlickerOnTime = 0;

        }
      }

      delay(lsfDelayTime);
    }
    return;
  }

  lowSpeedFlickerOnTime = lowSpeedFlickerOffTime = 0;
#endif

#ifdef ADD_FLICKER
  while ( delayTime - flickerOnTime > 0) {

    if (flickerState == false ) {
      analogWrite(activeLED, speedMap);
      flickerState = TRUE;
      randomFlicker = flickerOnTime;

#ifdef RANDOMIZE_FLICKER
      randomFlicker += random( RANDOM_FLICKER_LIMIT_LOW, RANDOM_FLICKER_LIMIT_HIGH );
#endif

      delayTime -= randomFlicker;  
      delay(randomFlicker);
    }

    else {
      analogWrite(activeLED, 0);
      flickerState = FALSE;
      randomFlicker = flickerOffTime;

#ifdef RANDOMIZE_FLICKER
      randomFlicker += random( RANDOM_FLICKER_LIMIT_LOW, RANDOM_FLICKER_LIMIT_HIGH );
#endif

      delayTime -= randomFlicker;  
      delay(randomFlicker);
    }
  }
#else
  analogWrite(activeLED, speedMap);
#endif

  if (delayTime > 0) {
    delay(delayTime);
  }
}

