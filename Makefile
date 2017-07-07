CXX = g++
CXXFLAGS = -std=c++0x
#add CPP files here
SCRS = main.cpp room.cpp object.cpp feature.cpp  
#add HPP files here
HEADERS = room.hpp object.hpp feature.hpp


#
#
#
run: ${SCRS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SCRS} -o run
