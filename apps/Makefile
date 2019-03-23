LIB_DIR = ./../lib/
TOP_DIR = ./..

SOURCES = $(wildcard ./src/*.cc)
INCLUDE_DIRS = -I./include  -I./../led-matrix-driver/include

TARGET = libapp.a
OBJECTS = $(patsubst %.cc,%.o,$(SOURCES))

$(TARGET) : $(OBJECTS)
	$(AR) $(ARFLAG) $@ $^
	cp $@ $(LIB_DIR)
	
$(OBJECTS) : %.o : %.cc 
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(INCLUDE_DIRS)

.PHONY : clean
clean:
	rm -rf $(TARGET) $(OBJECTS)