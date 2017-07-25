CXX = g++
CXXFLAGS = -std=c++0x
#add CPP files here
<<<<<<< HEAD

SCRS = Game.cpp Room.cpp ParseLine.cpp Item.cpp play.cpp  
#add HPP files here
HEADERS = Game.hpp Room.hpp ParseLine.hpp Item.hpp 

#
#
#
project:${SCRS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SCRS} -o project
