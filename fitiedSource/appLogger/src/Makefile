###############
## Makefile
###############

BINARY=../bin/appLogger
SHARED_LIB=../lib/libappLogger.so
BOOST_BASE=${BOOST_INSTALL_ROOT}
TINYXML_BASE=${TINYXML_ROOT}


ARCH = $(shell uname -m)	# ARCH becomes the output from the uname -m command.
CXX=/usr/bin/g++
CXXFLAGS=-g -O2 -Wall $(INCS)

SRCS = \
       ConsoleLogger.cpp \
       Log.cpp \
       SimpleFileLogger.cpp \

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
	$(CXX) -shared $^ -o $@ $(LIBS)

createlib: $(SHARED_LIB)
	
run:
	@echo "----------------------------"
	@echo "Running the programme. "
	@echo "----------------------------"
	@echo "----------------------------"
	$(BINARY)
	@echo "----------------------------"

clean:
	rm -rf $(BINARY) $(SHARED_LIB) *.o *.log
