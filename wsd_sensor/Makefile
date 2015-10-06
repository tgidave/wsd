# build and flash the sensor devices
#
# "make" or "make all" will compile the wsd_sensor.ino file into wsd_sensor.bin
# if no bin file exists or the bin file is out of date.
#
# "make clean" removes the bin file and will force a recompile the next time a
# make is run.
# 
# "make flash" will flash all the sensor devices with the current bin file.  If no 
# bin file exists, or the bin file is out of date, the bin file is re-built.
#
# "make flashsNN" where NN is a number between 00 and 29 will flash the current
# bin file to the specified device only.  If no bin file exists, or the bin file
# is out of date, the bin file is re-built.

INCLUDES = ../include/wsd_defines.h \
           ../include/Adafruit_Sensor.h \
           ../include/Adafruit_HMC5883_U.h

LIBS = ../lib/Adafruit_Sensor.cpp \
       ../lib/Adafruit_HMC5883_U.cpp

wsd_sensor.bin: wsd_sensor.ino $(INCLUDES) $(LIBS)
	particle compile p $< $(INCLUDES) $(LIBS) --saveto $@

all: wsd_sensor.bin

clean:
	rm -fr wsd_sensor.bin

#flash: flashts00

flash: flashs00 \
       flashs01 \
       flashs02 \
       flashs03 \
       flashs04 \
       flashs05 \
       flashs06 \
       flashs07 \
       flashs08 \
       flashs09 \
       flashs10 \
       flashs11 \
       flashs12 \
       flashs13 \
       flashs14 \
       flashs15 \
       flashs16 \
       flashs17 \
       flashs18 \
       flashs19 \
       flashs20 \
       flashs21 \
       flashs22 \
       flashs23 \
       flashs24 \
       flashs25 \
       flashs26 \
       flashs27 \
       flashs28 \
       flashs29 

#flashts00: wsd_sensor.bin
#	particle flash TS00 wsd_sensor.bin

flashs00: wsd_sensor.bin
	particle flash S00 wsd_sensor.bin

flashs01: wsd_sensor.bin
	particle flash S01 wsd_sensor.bin

flashs02: wsd_sensor.bin 
	particle flash S02 wsd_sensor.bin

flashs03: wsd_sensor.bin 
	particle flash S03 wsd_sensor.bin

flashs04: wsd_sensor.bin 
	particle flash S04 wsd_sensor.bin

flashs05: wsd_sensor.bin
	particle flash S05 wsd_sensor.bin

flashs06: wsd_sensor.bin
	particle flash S06 wsd_sensor.bin

flashs07: wsd_sensor.bin
	particle flash S07 wsd_sensor.bin

flashs08: wsd_sensor.bin
	particle flash S08 wsd_sensor.bin

flashs09: wsd_sensor.bin
	particle flash S09 wsd_sensor.bin

flashs10: wsd_sensor.bin
	particle flash S10 wsd_sensor.bin

flashs11: wsd_sensor.bin
	particle flash S11 wsd_sensor.bin

flashs12: wsd_sensor.bin
	particle flash S12 wsd_sensor.bin

flashs13: wsd_sensor.bin
	particle flash S13 wsd_sensor.bin

flashs14: wsd_sensor.bin
	particle flash S14 wsd_sensor.bin

flashs15: wsd_sensor.bin
	particle flash S15 wsd_sensor.bin

flashs16: wsd_sensor.bin
	particle flash S16 wsd_sensor.bin

flashs17: wsd_sensor.bin
	particle flash S17 wsd_sensor.bin

flashs18: wsd_sensor.bin
	particle flash S18 wsd_sensor.bin

flashs19: wsd_sensor.bin
	particle flash S19 wsd_sensor.bin

flashs20: wsd_sensor.bin
	particle flash S20 wsd_sensor.bin

flashs21: wsd_sensor.bin
	particle flash S21 wsd_sensor.bin

flashs22: wsd_sensor.bin
	particle flash S22 wsd_sensor.bin

flashs23: wsd_sensor.bin
	particle flash S23 wsd_sensor.bin

flashs24: wsd_sensor.bin
	particle flash S24 wsd_sensor.bin

flashs25: wsd_sensor.bin
	particle flash S25 wsd_sensor.bin

flashs26: wsd_sensor.bin
	particle flash S26 wsd_sensor.bin

flashs27: wsd_sensor.bin
	particle flash S27 wsd_sensor.bin

flashs28: wsd_sensor.bin
	particle flash S28 wsd_sensor.bin

flashs29: wsd_sensor.bin
	particle flash S29 wsd_sensor.bin


