CXX = g++
CXXFLAGS = -std=c++0x
#add CPP files here
SCRS = Game.cpp Room.cpp Item.cpp play.cpp  
#add HPP files here
HEADERS = Game.hpp Room.hpp Item.hpp 

#
#
#
project:${SCRS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SCRS} -o project
