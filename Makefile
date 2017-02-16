
RM          := rm -rf
CXXFLAGS    = -std=c++1y  -g -fPIC -D_REENTRANT -Wall 
LIBNAME     := ds-hal
LIBNAMEFULL := lib$(LIBNAME).so
OBJS        := $(patsubst %.c,%.o,$(wildcard *.c))

library: $(OBJS)
	@echo "Building $(LIBNAMEFULL) ...."
	$(CXX) $(OBJS) $(CXXFLAGS) $(CFLAGS) -shared -Wl,-soname,lib$(LIBNAME).so -o $(LIBNAMEFULL)

%.o: %.c
	@echo "Building $@ ...."
	$(CXX) -c $<  $(CXXFLAGS) $(CFLAGS) -o $@

install: $(LIBNAMEFULL)
	@echo "Installing files in $(DESTDIR) ..."
	install -d $(DESTDIR)
	install -m 0755 $< $(DESTDIR)
