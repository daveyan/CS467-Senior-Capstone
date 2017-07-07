#include <iostream>
#include <cstdlib>
#include <string>

#include "room.hpp"

using namespace std;

int main(){

	Room r("Room1");

	r.readDesc(r.visited,"look");
	r.readDesc(r.visited,"look");

	//cout << r.roomDesc << endl;
	

	return 0;
}

