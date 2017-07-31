#include <iostream>

#include "ParseLine.hpp"
#include "Game.hpp"

int main() {
	Game newGame;

	// Initialize first room
	string entranceLongDesc = "You see a patch of cracked stone on the ground. The slabs are thin, and there is a gap in the pile that reveals what looks like metal. The tremor must have caused the stone to crack, but why is there metal underneath? There is also a small pile of what looks like mangled metal debris at the edge of the cracked stone.";
	string entranceShortDesc = "A tremor has loosened stone that was used to conceal a secret door, a door which as been pried open.";
	string entranceName = "Entrance";
	int entranceId = 1;
	// Item for room 1
	Item metalBar(1, "Metal Bar", "Looks sturdy, like it could be used for leverage");
	// Create room, add adjacent rooms, and add item
	Room entrance(entranceId, entranceName, entranceShortDesc, entranceLongDesc);
	entrance.addNorth(2); // Vestibule/Lockers is the next room
	entrance.addItem(metalBar);
	// Add room to game
	newGame.addRoom(entrance);

	// Initialize second room
	string vestLongDesc = "Small vestibule. There are lockers on both sides of the walls, with benches in between. To the left is a door labeled “Utility Closet.” It is dark inside except for the light coming in from the door you just pried open. One of the lockers appears to be slightly open. To the east is the power supply room.";
	string vestShortDesc = "Small vestibule"; \
		string vestName = "Vestibule";
	int vestId = 2;
	// Items for room 2
	Item keycard(2, "Keycard", "Keycard, probably used to gain access to the facility");
	Item flashlight(3, "Flashlight", "Used to illuminate the darkness");
	// Create room, add adjacent rooms, and add item
	Room vestibule(vestId, vestName, vestShortDesc, vestLongDesc);
	vestibule.addSouth(1); // Entrance
	vestibule.addEast(3); // Mechanical Room
	vestibule.addNorth(5); // Lounge
	vestibule.addItem(keycard);
	vestibule.addItem(flashlight);
	// Add room to game
	newGame.addRoom(vestibule);

	// Initialize third room
	string mechLongDesc = "This appears to have the machinery necessary to provide energy to the building and keep the equipment running. This includes a furnace, AC unit, and water. There are two dead bodies near the power supply.";
	string mechShortDesc = "This appears to have the machinery necessary to provide energy to the building and keep the equipment running";
	string mechName = "Mechanical Room";
	int mechId = 3;
	// Create room, add adjacent rooms
	Room mechanicalRoom(mechId, mechName, mechShortDesc, mechLongDesc);
	mechanicalRoom.addWest(2); // Vestibule
	mechanicalRoom.addEast(4); // Garage
						  // Add room to game
	newGame.addRoom(mechanicalRoom);

	// Initialize fifth room
	string loungeLongDesc = "Open area. A couple of couches. There is a table with a chess board out. You see a note next to the chess board. The is a bulletin board with a warning on it.";
	string loungeShortDesc = "Open area. A couple of couches. There is a table with a chess board out. You see a note next to the chess board. The is a bulletin board with a warning on it.";
	string loungeName = "Lounge";
	int loungeId = 5;
	// Create room, add adjacent rooms
	Room lounge(loungeId, loungeName, loungeShortDesc, loungeLongDesc);
	lounge.addSouth(2);
	// Add room to game
	newGame.addRoom(lounge);

	/*
	Room roomarray[] = { Room(1, "Room1"), Room(2, "Room2"), Room(3, "Room3") };
	for (int i = 0; i < 3; i++)
		newGame.addRoom(roomarray[i]);
	*/

    newGame.play(newGame, entrance);
    return 0;
}