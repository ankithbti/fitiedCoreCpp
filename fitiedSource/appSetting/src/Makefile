###############
## Makefile
###############

BINARY=../bin/appSetting
SHARED_LIB=../lib/libappSetting.so
BOOST_BASE=${BOOST_INSTALL_ROOT}
TINYXML_BASE=../../../third_party/afterBuild/tinyXml


ARCH = $(shell uname -m)	# ARCH becomes the output from the uname -m command.
CXX=/usr/bin/g++
CXXFLAGS=-g -O2 -Wall $(INCS)

SRCS = Value.cpp
MAIN_SRC = Main.cpp

OBJS = $(patsubst %.cpp, %.o, $(SRCS))
MAIN_OBJ = $(patsubst %.cpp, %.o, $(MAIN_SRC))

INCS = -I../include \
       -I$(BOOST_BASE)/include \
       -I$(TINYXML_BASE)/include \

LIBS = \
        -L$(TINYXML_BASE)/lib -ltinyXml \
        -L$(BOOST_BASE)/lib -lboost_thread \
        -L$(BOOST_BASE)/lib -lboost_system \
	-lpthread

all: $(BINARY) run
	
$(BINARY): $(OBJS) $(MAIN_OBJ)
	$(CXX) -o $(BINARY) $(OBJS) $(MAIN_OBJ) $(LIBS)

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared $^ -o $@

createlib: $(SHARED_LIB)
	
run:
	@echo "----------------------------"
	@echo "Running the programme. "
	@echo "----------------------------"
	(export DYLD_LIBRARY_PATH=../../../third_party/afterBuild/tinyXml/lib:${DYLD_LIBRARY_PATH})
	@echo "----------------------------"
	$(BINARY)
	@echo "----------------------------"

clean:
	rm -rf $(BINARY) $(SHARED_LIB) *.o
