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

ifeq ($(WSDTEST),tgidave)
   all: wsd_sensor_TS00.bin

   wsd_sensor_TS00.bin: wsd_sensor.ino $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_TS00.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@


   flash: flashts00

   flashts00: wsd_sensor_TS00.bin
		particle flash TS00 wsd_sensor_TS00.bin

else
   all: wsd_sensor_S00.bin \
        wsd_sensor_S01.bin \
        wsd_sensor_S02.bin \
        wsd_sensor_S03.bin \
        wsd_sensor_S04.bin \
        wsd_sensor_S05.bin \
        wsd_sensor_S06.bin \
        wsd_sensor_S07.bin \
        wsd_sensor_S08.bin \
        wsd_sensor_S09.bin \
        wsd_sensor_S10.bin \
        wsd_sensor_S11.bin \
        wsd_sensor_S12.bin \
        wsd_sensor_S13.bin \
        wsd_sensor_S14.bin \
        wsd_sensor_S15.bin \
        wsd_sensor_S16.bin \
        wsd_sensor_S17.bin \
        wsd_sensor_S18.bin \
        wsd_sensor_S19.bin \
        wsd_sensor_S20.bin \
        wsd_sensor_S21.bin \
        wsd_sensor_S22.bin \
        wsd_sensor_S23.bin \
        wsd_sensor_S24.bin \
        wsd_sensor_S25.bin \
        wsd_sensor_S26.bin \
        wsd_sensor_S27.bin \
        wsd_sensor_S28.bin \
        wsd_sensor_S29.bin 
   
   wsd_sensor_S00.bin: wsd_sensor.ino ../include/wsd_sensor_S00.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S00.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S01.bin: wsd_sensor.ino ../include/wsd_sensor_S01.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S01.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S02.bin: wsd_sensor.ino ../include/wsd_sensor_S02.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S02.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S03.bin: wsd_sensor.ino ../include/wsd_sensor_S03.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S03.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S04.bin: wsd_sensor.ino ../include/wsd_sensor_S04.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S04.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S05.bin: wsd_sensor.ino ../include/wsd_sensor_S05.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S05.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S06.bin: wsd_sensor.ino ../include/wsd_sensor_S06.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S06.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S07.bin: wsd_sensor.ino ../include/wsd_sensor_S07.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S07.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S08.bin: wsd_sensor.ino ../include/wsd_sensor_S08.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S08.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S09.bin: wsd_sensor.ino ../include/wsd_sensor_S09.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S09.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S10.bin: wsd_sensor.ino ../include/wsd_sensor_S10.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S10.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S11.bin: wsd_sensor.ino ../include/wsd_sensor_S11.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S11.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S12.bin: wsd_sensor.ino ../include/wsd_sensor_S12.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S12.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S13.bin: wsd_sensor.ino ../include/wsd_sensor_S13.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S13.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S14.bin: wsd_sensor.ino ../include/wsd_sensor_S14.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S14.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S15.bin: wsd_sensor.ino ../include/wsd_sensor_S15.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S15.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S16.bin: wsd_sensor.ino ../include/wsd_sensor_S16.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S16.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S17.bin: wsd_sensor.ino ../include/wsd_sensor_S17.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S17.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S18.bin: wsd_sensor.ino ../include/wsd_sensor_S18.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S18.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S19.bin: wsd_sensor.ino ../include/wsd_sensor_S19.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S19.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S20.bin: wsd_sensor.ino ../include/wsd_sensor_S20.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S20.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S21.bin: wsd_sensor.ino ../include/wsd_sensor_S21.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S21.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S22.bin: wsd_sensor.ino ../include/wsd_sensor_S22.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S22.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S23.bin: wsd_sensor.ino ../include/wsd_sensor_S23.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S23.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S24.bin: wsd_sensor.ino ../include/wsd_sensor_S24.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S24.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S25.bin: wsd_sensor.ino ../include/wsd_sensor_S25.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S25.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S26.bin: wsd_sensor.ino ../include/wsd_sensor_S26.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S26.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S27.bin: wsd_sensor.ino ../include/wsd_sensor_S27.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S27.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S28.bin: wsd_sensor.ino ../include/wsd_sensor_S28.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S28.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@
    
   wsd_sensor_S29.bin: wsd_sensor.ino ../include/wsd_sensor_S29.h $(INCLUDES) $(LIBS)
		cp ../include/wsd_sensor_S29.h wsd_sensor.h
		particle compile p $< wsd_sensor.h $(INCLUDES) $(LIBS) --saveto $@

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


   flashs00: wsd_sensor_S00.bin
		particle flash S00 wsd_sensor_S00.bin

   flashs01: wsd_sensor_S01.bin
		particle flash S01 wsd_sensor_S01.bin

   flashs02: wsd_sensor_S02.bin 
		particle flash S02 wsd_sensor_S02.bin

   flashs03: wsd_sensor_S03.bin 
		particle flash S03 wsd_sensor_S03.bin

   flashs04: wsd_sensor_S04.bin 
		particle flash S04 wsd_sensor_S04.bin

   flashs05: wsd_sensor_S05.bin
		particle flash S05 wsd_sensor_S05.bin

   flashs06: wsd_sensor_S06.bin
		particle flash S06 wsd_sensor_S06.bin

   flashs07: wsd_sensor_S07.bin
		particle flash S07 wsd_sensor_S07.bin

   flashs08: wsd_sensor_S08.bin
		particle flash S08 wsd_sensor_S08.bin

   flashs09: wsd_sensor_S09.bin
		particle flash S09 wsd_sensor_S09.bin

   flashs10: wsd_sensor_S10.bin
		particle flash S10 wsd_sensor_S10.bin

   flashs11: wsd_sensor_S11.bin
		particle flash S11 wsd_sensor_S11.bin

   flashs12: wsd_sensor_S12.bin
		particle flash S12 wsd_sensor_S12.bin

   flashs13: wsd_sensor_S13.bin
		particle flash S13 wsd_sensor_S13.bin

   flashs14: wsd_sensor_S14.bin
		particle flash S14 wsd_sensor_S14.bin

   flashs15: wsd_sensor_S15.bin
		particle flash S15 wsd_sensor_S15.bin

   flashs16: wsd_sensor_S16.bin
		particle flash S16 wsd_sensor_S16.bin

   flashs17: wsd_sensor_S17.bin
		particle flash S17 wsd_sensor_S17.bin

   flashs18: wsd_sensor_S18.bin
		particle flash S18 wsd_sensor_S18.bin

   flashs19: wsd_sensor_S19.bin
		particle flash S19 wsd_sensor_S19.bin

   flashs20: wsd_sensor_S20.bin
		particle flash S20 wsd_sensor_S20.bin

   flashs21: wsd_sensor_S21.bin
		particle flash S21 wsd_sensor_S21.bin

   flashs22: wsd_sensor_S22.bin
		particle flash S22 wsd_sensor_S22.bin

   flashs23: wsd_sensor_S23.bin
		particle flash S23 wsd_sensor_S23.bin

   flashs24: wsd_sensor_S24.bin
		particle flash S24 wsd_sensor_S24.bin

   flashs25: wsd_sensor_S25.bin
		particle flash S25 wsd_sensor_S25.bin

   flashs26: wsd_sensor_S26.bin
		particle flash S26 wsd_sensor_S26.bin

   flashs27: wsd_sensor_S27.bin
		particle flash S27 wsd_sensor_S27.bin

   flashs28: wsd_sensor_S28.bin
		particle flash S28 wsd_sensor_S28.bin

   flashs29: wsd_sensor_S29.bin
		particle flash S29 wsd_sensor_S29.bin

endif

clean:
	rm -fr wsd_sensor_*.bin

