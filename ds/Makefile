#SDK_ROOT=../../sdk/fsroot/ramdisk
CXX=$(SDK_ROOT)/usr/bin/g++
RM          := rm -rf 
CFLAGS      := -std=c++0x  -g -fPIC -D_REENTRANT -Wall
LIBNAME     := ds
LIBNAMEFULL := lib$(LIBNAME).so
INSTALL     := $(PWD)/install
OBJS        := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
INCLUDE     := -I$(PWD)                          \
               -I$(SDK_ROOT)/usr/local/include   \
    	       -I$(PWD)/hal/emu/include          \
    	       -I$(PWD)/ds                       \
               -I$(PWD)/ds/include               \
               -I$(PWD)/../rdkemulator/Apps/iarm \
               -I$(PWD)/../iarmmgrs/generic/hal/include \


INCLUDE      += $(HAL_INCLUDE)

CFLAGS      += $(INCLUDE)


all: install
	@echo "Build Finished...."

library: $(OBJS)
	@echo "Building $(LIBNAMEFULL) ...."
	$(CXX) $(OBJS) $(CFLAGS) -shared -Wl -o $(LIBNAMEFULL)

%.o: %.cpp
	@echo "Building $@ ...."
	$(CXX) -c $<  $(CFLAGS) -o $@

install: library
	@echo "installling...!"
	@cp -f $(LIBNAMEFULL) $(INSTALL)/lib

uninstall:
	@$(RM) $(INSTALL)/lib/$(LIBNAMEFULL)

clean:
	@echo "Cleaning the directory..."
	@$(RM) $(OBJS) $(LIBNAMEFULL)


