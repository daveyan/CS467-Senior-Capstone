#include <iostream>

#include "ParseLine.hpp"
#include "Game.hpp"

int main() {
	Game newGame;

	newGame.setcurRoom(0);

	//ALL ITEMS

	
	Item a(1,"metalBar","desc");
	Item b(2,"keycard","desc");
	Item c(3,"flashlight","desc");
	Item d(4,"d","desc");
	Item e(5,"e","desc");
	Item f(6,"f","desc");
	Item g(7,"g","desc");
	Item h(8,"h","desc");
	Item i(9,"i","desc");
	Item j(10,"j","desc");
	Item k(11,"k","desc");
	Item l(12,"l","desc");
	Item m(13,"m","desc");
	Item n(14,"n","desc");
	Item o(15,"o","desc");

	//push items into game.allitems vector - loadgame
	newGame.allitems.push_back(a);
	newGame.allitems.push_back(b);
	newGame.allitems.push_back(c);
	newGame.allitems.push_back(d);
	newGame.allitems.push_back(e);
	newGame.allitems.push_back(f);
	newGame.allitems.push_back(g);
	newGame.allitems.push_back(h);
	newGame.allitems.push_back(i);
	newGame.allitems.push_back(j);
	newGame.allitems.push_back(k);
	newGame.allitems.push_back(l);
	newGame.allitems.push_back(m);
	newGame.allitems.push_back(n);
	newGame.allitems.push_back(o);



	Room empty(0,"");

	//ALL ROOMS	
	Room entrance(1, "Entrance");
	entrance.addNorth(2);
			
	Room vestibule(2, "Vestibule");
	vestibule.addNorth(7); 
	vestibule.addSouth(1); 
	vestibule.addEast(3); 
	
		
	Room mechanicalRoom(3, "Mechanical Room");
	
	mechanicalRoom.addEast(4); 
	mechanicalRoom.addWest(2);
	
	Room garage(4,"Hidden Garage");
	garage.addEast(4); 
	garage.addWest(3);
	
	Room bathroom(5,"Bathroom");
	bathroom.addEast(6); 
	
	Room breakroom(6,"Break Room");
	breakroom.addEast(7); 
	breakroom.addWest(5);
	

	Room lounge(7, "Lounge");
	lounge.addNorth(12); 
	lounge.addSouth(2); 
	lounge.addEast(8); 
	lounge.addWest(6);


	Room office(8,"Office");
	office.addWest(7);

	Room mechanicalpartsupplyroom(9, "Mechanical Parts Supply Room");
	mechanicalpartsupplyroom.addEast(10); 

	Room robotassemblyroom(10,"Robot Assembly Room");
	robotassemblyroom.addEast(11); 
	robotassemblyroom.addWest(9);

	Room taxidermyreasearchroom(11,"Taxidermy Research Room");
	taxidermyreasearchroom.addEast(12); 
	taxidermyreasearchroom.addWest(10);

	Room computerlab(12, "Computer Lab");
	computerlab.addNorth(15); 
	computerlab.addSouth(7); 
	computerlab.addEast(13); 
	computerlab.addWest(11);

	Room liverobotanimals(13, "Live Robot Animals");
	liverobotanimals.addEast(14); 
	liverobotanimals.addWest(12);

	Room mockforest(14,"Mock Forest");
	mockforest.addWest(13);

	Room monitoringroom(15, "Monitoring Room");
	monitoringroom.addSouth(13); 
	

	//ADDING ITEMS TO ROOMS
	entrance.addItem("metalBar");
	vestibule.addItem("keycard");
	mechanicalRoom.addItem("flashlight");
	garage.addItem("d");
	bathroom.addItem("e");
	breakroom.addItem("f");
	lounge.addItem("g");
	office.addItem("h");
	mechanicalpartsupplyroom.addItem("i");
	robotassemblyroom.addItem("j");
	taxidermyreasearchroom.addItem("k");
	computerlab.addItem("l");
	liverobotanimals.addItem("m");
	mockforest.addItem("n");
	monitoringroom.addItem("o");

	
	
	//ADD ROOMS TO NEW GAME
	newGame.addRoom(empty);
	newGame.addRoom(entrance); 					//1
	newGame.addRoom(vestibule);					//2	
	newGame.addRoom(mechanicalRoom);			//3
	newGame.addRoom(garage);					//4
	newGame.addRoom(bathroom);					//5
	newGame.addRoom(breakroom);					//6
	newGame.addRoom(lounge);					//7
	newGame.addRoom(office);
	newGame.addRoom(mechanicalpartsupplyroom);
	newGame.addRoom(robotassemblyroom);
	newGame.addRoom(taxidermyreasearchroom);
	newGame.addRoom(computerlab);
	newGame.addRoom(liverobotanimals);
	newGame.addRoom(mockforest);
	newGame.addRoom(monitoringroom);
	
	//Reading room text and adding it to the rooms.
	for (int i = 1; i <= 15; i++){
		string desclong = "";
		string descshort = "";
		string feature1 = "";
		string feature2 = "";
		desclong = newGame.rooms[i].getDesc("long");
		descshort = newGame.rooms[i].getDesc("short");
		feature1 = newGame.rooms[i].getDesc("Feature1");
		feature2 = newGame.rooms[i].getDesc("Feature2");

		newGame.rooms[i].setLongDesc(desclong);
		newGame.rooms[i].setShortDesc(descshort);
		newGame.rooms[i].setFeature1Response(feature1);
		newGame.rooms[i].setFeature2Response(feature2);
	}



    newGame.play(newGame, entrance);
    return 0;
}