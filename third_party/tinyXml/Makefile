###############
## Makefile
###############

SHARED_LIB=lib/libtinyXml.so

ARCH = $(shell uname -m)	# ARCH becomes the output from the uname -m command.
CXX=/usr/bin/g++
CXXFLAGS=-g -O2 -Wall $(INCS) -DTIXML_USE_STL

SRCS = tinyxml.cpp \
       tinyxmlerror.cpp \
       tinyxmlparser.cpp \
       ticpp.cpp \
       tinystr.cpp \

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

INCS = -I. \

LIBS = \

all: $(SHARED_LIB) copyFiles

$(SHARED_LIB): $(OBJS)
	$(CXX) -shared $^ -o $@

copyFiles:
	(cp lib/* ../afterBuild/tinyXml/lib/)
	(cp *.h ../afterBuild/tinyXml/include/)

clean:
	rm -rf $(SHARED_LIB) *.o
