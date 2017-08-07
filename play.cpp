#include <iostream>

#include "ParseLine.hpp"
#include "Game.hpp"

int main() {
	Game newGame;

	newGame.setcurRoom(1);

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



	Room empty(0,"");

	//ALL ROOMS	
	Room entrance(1, "Entrance");
	entrance.addNorth(2);
	//entrance.addSouth(0);
	//entrance.addEast(0);
	//entrance.addWest(0);
		
	Room vestibule(2, "Vestibule");
	vestibule.addNorth(7); 
	vestibule.addSouth(1); 
	vestibule.addEast(3); 
	//vestibule.addWest(0);

		
	Room mechanicalRoom(3, "Mechanical Room");
	//mechanicalRoom.addNorth(0);
	//mechanicalRoom.addSouth(0);
	mechanicalRoom.addEast(4); 
	mechanicalRoom.addWest(2);
	
	Room garage(4,"Hidden Garage");
	//garage.addNorth(0);
	//garage.addSouth(0);
	garage.addEast(4); 
	garage.addWest(3);
	
	Room bathroom(5,"Bathroom");
	//bathroom.addNorth(0);
	//bathroom.addSouth(0);
	bathroom.addEast(6); 
	//bathroom.addWest(0);


	Room breakroom(6,"Break Room");
	//breakroom.addNorth(0);
	//breakroom.addSouth(0);
	breakroom.addEast(7); 
	breakroom.addWest(5);
	

	Room lounge(7, "Lounge");
	lounge.addNorth(12); 
	lounge.addSouth(2); 
	lounge.addEast(8); 
	lounge.addWest(6);


	Room office(8,"Office");
	//office.addNorth(0);
	//office.addSouth(0);
	//office.addEast(0);
	office.addWest(7);

	Room mechanicalpartsupplyroom(9, "Mechanical Parts Supply Room");
	//mechanicalpartsupplyroom.addNorth(0);
	//mechanicalpartsupplyroom.addSouth(0);
	mechanicalpartsupplyroom.addEast(10); 
	//mechanicalpartsupplyroom.addWest(0);

	Room robotassemblyroom(10,"Robot Assembly Room");
	//robotassemblyroom.addNorth(0);
	//robotassemblyroom.addSouth(0);
	robotassemblyroom.addEast(11); 
	robotassemblyroom.addWest(9);

	Room taxidermyreasearchroom(11,"Taxidermy Research Room");
	//taxidermyreasearchroom.addNorth(0);
	//taxidermyreasearchroom.addSouth(0);
	taxidermyreasearchroom.addEast(12); 
	taxidermyreasearchroom.addWest(10);

	Room computerlab(12, "Computer Lab");
	computerlab.addNorth(15); 
	computerlab.addSouth(7); 
	computerlab.addEast(13); 
	computerlab.addWest(11);

	Room liverobotanimals(13, "Live Robot Animals");
	//liverobotanimals.addNorth(0);
	//liverobotanimals.addSouth(0);
	liverobotanimals.addEast(14); 
	liverobotanimals.addWest(12);

	Room mockforest(14,"Mock Forest");
	//mockforest.addNorth(0);
	//mockforest.addNorth(0);
	//mockforest.addEast(0);
	mockforest.addWest(13);

	Room monitoringroom(15, "Monitoring Room");
	monitoringroom.addSouth(13); 
	//monitoringroom.addNorth(0);
	//monitoringroom.addEast(0);
	//monitoringroom.addWest(0);



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
	

    newGame.play(newGame, entrance);
    return 0;
}