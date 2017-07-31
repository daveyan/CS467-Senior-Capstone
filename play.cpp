#include <iostream>

#include "ParseLine.hpp"
#include "Game.hpp"

int main() {
	Game newGame;

	
	
	Item metalBar(1, "Metal Bar", "Looks sturdy, like it could be used for leverage");
	Item keycard(2, "Keycard", "Keycard, probably used to gain access to the facility");
	Item flashlight(3, "Flashlight", "Used to illuminate the darkness");

	
	Room entrance(1, "Entrance");
	entrance.addNorth(2); // Vestibule/Lockers is the next room
		
	Room vestibule(2, "Vestibule");
	vestibule.addNorth(7); 
	vestibule.addSouth(1); 
	vestibule.addEast(3); 

		
	Room mechanicalRoom(3, "Mechanical Room");
	mechanicalRoom.addEast(4); 
	mechanicalRoom.addWest(2);
	
	Room garage(4,"Hidden Garage");
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


	Room rootassemblyroom(10,"Root Assembly Room");
	rootassemblyroom.addEast(11); 
	rootassemblyroom.addWest(9);

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



	//ITEM ADDING
	entrance.addItem(metalBar);

	vestibule.addItem(keycard);
	vestibule.addItem(flashlight);
	
	
	//ADD ROOMS TO NEW GAME
	newGame.addRoom(entrance);
	newGame.addRoom(vestibule);
	newGame.addRoom(mechanicalRoom);
	newGame.addRoom(garage);
	newGame.addRoom(bathroom);
	newGame.addRoom(breakroom);
	newGame.addRoom(lounge);
	newGame.addRoom(office);
	newGame.addRoom(mechanicalpartsupplyroom);
	newGame.addRoom(rootassemblyroom);
	newGame.addRoom(taxidermyreasearchroom);
	newGame.addRoom(computerlab);
	newGame.addRoom(liverobotanimals);
	newGame.addRoom(mockforest);
	newGame.addRoom(monitoringroom);
	

    newGame.play(newGame, entrance);
    return 0;
}