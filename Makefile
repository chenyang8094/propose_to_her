CXX=g++
CC=gcc
CXXFLAGS=-Wall -O3 -g -Wextra -Wno-unused-parameter -Wunused-variable
ARFLAG=-rcs
TARGET=propose_to_her

SUBDIRS=$(shell ls -l | grep ^d | awk '{ if($$9 != "lib" && $$9 != "resource") print $$9}')
ROOT_DIR=$(shell pwd)

CUR_SOURCE=${wildcard *.cc}
CUR_OBJS=${patsubst %.cc, %.o, $(CUR_SOURCE)}

export CXX ROOT_DIR CXXFLAGS ARFLAG

INCLUDES=$(wildcard ./app/include/*.h ./sensor-driver/include/*.h ./algorithm/include/*.h) 
INCLUDE_DIRS=-I./app/include/ -I./led-matrix-driver/include -I./sensor-driver/include/
LDFLAGS+=-L./lib/ -L/usr/local/lib -lapp -lrgbmatrix -lwiringPi -lwiringPiDev -lrt -lm -lpthread  -lcrypt 

all : $(TARGET) 

$(TARGET) : $(CUR_OBJS) $(SUBDIRS)
	$(CXX) $< -o $@ $(LDFLAGS)

$(CUR_OBJS) : %.o : %.cc 
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(INCLUDE_DIRS)

$(SUBDIRS):ECHO
	$(MAKE) -C $@

ECHO:
	@echo begin compile

.PHONY : clean
clean:
	for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir clean||exit 1;\
	done
	rm -rf $(TARGET) $(CUR_OBJS)  ./lib/*.a