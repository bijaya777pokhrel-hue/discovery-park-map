// PathDisplay.cpp
// Author: Bijaya Pokhrel
// Task: Draw path line on map (Production Plan row 8)

#include "PathDisplay.h"

using namespace std;

namespace {
	const string RED = "\033[31m";
	const string BOLD = "\033[1m";
	const string RESET = "\033[0m";
}

namespace PathDisplay {

string RouteLine(const vector<string>& rooms){
	string line;
	for(size_t i = 0; i < rooms.size(); i++){
		line += rooms[i];
		if(i + 1 < rooms.size()){
			line += " --> ";
		}
	}
	return line;
}

void ShowRoute(const vector<string>& rooms, int distance,
               ostream& out, bool useColor){
	if(rooms.empty()){
		ShowError("No path found between these rooms.", out, useColor);
		return;
	}

	string red = useColor ? RED : "";
	string bold = useColor ? BOLD : "";
	string reset = useColor ? RESET : "";

	out << bold << "Route: " << reset
	    << rooms.front() << " to " << rooms.back() << endl;

	if(rooms.size() == 1){
		out << "You are already at " << rooms.front() << "." << endl;
		return;
	}

	out << red << RouteLine(rooms) << reset << endl;
	out << "Stops: " << rooms.size() - 2
	    << " | Total distance: " << distance << endl;
}

void ShowError(const string& message, ostream& out, bool useColor){
	string red = useColor ? RED : "";
	string reset = useColor ? RESET : "";
	out << red << "X " << reset << message << endl;
}

}
