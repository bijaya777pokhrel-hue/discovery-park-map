// test_validation.cpp
// Author: Bijaya Pokhrel
// Tests for RoomValidator and PathDisplay.
//
// Build and run:
//   g++ -o ValidationTest test_validation.cpp RoomValidator.cpp PathDisplay.cpp
//   ./ValidationTest

#include "RoomValidator.h"
#include "PathDisplay.h"
#include <iostream>
#include <sstream>

using namespace std;

int passed = 0;
int failed = 0;

void Check(bool condition, const string& name){
	if(condition){
		passed++;
		cout << "PASS  " << name << endl;
	} else {
		failed++;
		cout << "FAIL  " << name << endl;
	}
}

int main(){
	RoomValidator validator;
	Check(validator.LoadRooms("roomListNumbered.txt"), "loads roomListNumbered.txt");
	Check(validator.RoomCount() > 0, "room list is not empty");

	// Valid rooms
	RoomCheck a100 = validator.CheckRoom("A100");
	Check(a100.valid && a100.index == 1, "A100 is valid and is room 1");
	Check(validator.CheckRoom("  a101b ").valid, "extra spaces and lowercase are accepted");

	// Invalid rooms
	RoomCheck empty = validator.CheckRoom("   ");
	Check(!empty.valid && empty.index == -1, "empty input is rejected");

	RoomCheck fake = validator.CheckRoom("Z999");
	Check(!fake.valid, "unknown room Z999 is rejected");

	RoomCheck typo = validator.CheckRoom("A10");
	Check(!typo.valid && typo.message.find("Did you mean") != string::npos,
	      "typo A10 is rejected with suggestions");

	// Start and destination together
	Check(validator.CheckTrip("A100", "A101").valid, "A100 to A101 is a valid trip");
	Check(!validator.CheckTrip("A100", "a100").valid, "same start and destination is rejected");
	Check(!validator.CheckTrip("", "A101").valid, "missing start is rejected");
	Check(validator.CheckTrip("A100", "Z999").message.find("Destination") == 0,
	      "bad destination says Destination in the message");

	// Path display
	vector<string> route;
	route.push_back("A100");
	route.push_back("A101");
	route.push_back("A101A");
	Check(PathDisplay::RouteLine(route) == "A100 --> A101 --> A101A", "route line joins rooms in order");

	ostringstream shown;
	PathDisplay::ShowRoute(route, 5, shown, false);
	Check(shown.str().find("Total distance: 5") != string::npos, "route shows total distance");

	ostringstream noPath;
	PathDisplay::ShowRoute(vector<string>(), 0, noPath, false);
	Check(noPath.str().find("X No path found") == 0, "empty route shows red X error");

	// Demo output
	cout << endl << "Demo:" << endl;
	PathDisplay::ShowRoute(route, 5);
	PathDisplay::ShowError(typo.message);

	cout << endl << passed << " passed, " << failed << " failed" << endl;
	return failed == 0 ? 0 : 1;
}
