DEBUG=0

ifneq ($(DEBUG),0)
DEBUGFLAGS=-g3 -DMALLOC_CHECK_=3 -DDODEBUG=$(DEBUG)
else
DEBUGFLAGS=
endif
SUMOVERSION:=$(shell sumo --version | head -n 1 | grep -o -e '0\..\+' | sed 's,\.,,g')
ifeq ($(SUMOVERSION),"")
	$(error "sumo not found or version not recognized")
endif

CXXFLAGS=-Wall -Wextra -O2 -std=c++0x $(DEBUGFLAGS) -DSUMOVERSION=0x$(SUMOVERSION)

all: 
	$(MAKE) clean
	$(MAKE) sumo-wrapper genInstanceFile RS getOriginalTL

sumo-wrapper: sumo-wrapper.cpp cInstance.cpp simpleXMLParser.cpp
	$(CXX) $(CXXFLAGS) -o sumo-wrapper sumo-wrapper.cpp cInstance.cpp simpleXMLParser.cpp

genInstanceFile: genInstanceFile.cpp simpleXMLParser.cpp
	$(CXX) $(CXXFLAGS) -o genInstanceFile genInstanceFile.cpp simpleXMLParser.cpp

RS: RS.cpp simpleXMLParser.cpp cInstance.cpp
	$(CXX) $(CXXFLAGS) -o RS RS.cpp simpleXMLParser.cpp cInstance.cpp

getOriginalTL: getOriginalTL.cpp simpleXMLParser.cpp
	$(CXX) $(CXXFLAGS) -o getOriginalTL getOriginalTL.cpp simpleXMLParser.cpp

clean:
	$(RM) *.o
	$(RM) sumo-wrapper genInstanceFile RS getOriginalTL

