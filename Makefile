CXX = g++
CXXFLAGS = -std=c++0x
#add CPP files here

SCRS = Game.cpp ParseLine.cpp room.cpp Item.cpp play.cpp  
#add HPP files here
HEADERS = Game.hpp room.hpp Item.hpp ParseLine.hpp 

#
#
#
project:${SCRS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SCRS} -o project
