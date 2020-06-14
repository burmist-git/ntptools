########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Tue Apr 16 22:42:58 JST 2019                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# Script description:                                                  #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
########################################################################

ROOTCFLAGS  = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS    = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS   = $(shell $(ROOTSYS)/bin/root-config --glibs)
ROOTLDFLAGS = $(shell $(ROOTSYS)/bin/root-config --ldflags)

# add xml files
#ROOTLIBS += -lMLP -lXMLIO

#OUTLIB = /home/hvala/ntptools/obj/
#OUTLIB = /home/hvala/pcstatlog/ntptools/obj/
#OUTLIB = /home/usr/hvala/ntptools/obj/
OUTLIB = /home/usr/hvala/ntptools/obj/

CXX  = g++
CXX += -I./     

CXXFLAGS  = -g -Wall -fPIC -Wno-deprecated
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(ROOTLIBS)
CXXFLAGS += $(ROOTGLIBS)
CXXFLAGS += $(ROOTLDFLAGS)
CXXFLAGSDICT = -g -Wall -fPIC -Wno-deprecated

PATHTOSHAREDLIB=$(OUTLIB)

.PHONY: clean

#----------------------------------------------------#

all: makedir libntpLoopstatsOne.so

makedir:
	mkdir -p $(OUTLIB);

obj/ntpLoopstatsOne.o: ntpLoopstatsOne.C  libntpLoopstatsOne.h
	$(CXX) $(CXXFLAGS) -c -I. -o $@ $<

libntpLoopstatsOne.so: obj/ntpLoopstatsOne.o
	$(CXX) -shared -o $(PATHTOSHAREDLIB)$@ $^ $(ROOTLIBS) $(ROOTGLIBS)

clean: 
	rm -f *~
	rm -f .*~
	rm -rf $(OUTLIB)
