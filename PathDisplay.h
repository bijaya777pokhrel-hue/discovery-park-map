// PathDisplay.h
// Author: Bijaya Pokhrel
// Task: Draw path line on map (Production Plan row 8)
//
// Shows the route found by the shortest-path search as a red line from
// the start room to the destination, plus the total distance.
// Errors (like an invalid room) are shown with a red X.
//
// The console version draws the line with text. When the map view is
// ready, the same route list can be used to draw the red line on the map.

#ifndef PATHDISPLAY_H
#define PATHDISPLAY_H

#include <iostream>
#include <string>
#include <vector>

namespace PathDisplay {
	// rooms: room names in order from start to destination.
	// distance: total distance from the shortest-path search.
	// useColor: false turns off red color (for files or tests).
	void ShowRoute(const std::vector<std::string>& rooms, int distance,
	               std::ostream& out = std::cout, bool useColor = true);

	// Prints a message with a red X in front of it.
	void ShowError(const std::string& message,
	               std::ostream& out = std::cout, bool useColor = true);

	// Builds the route line as plain text: "A100 --> A101 --> A101A"
	std::string RouteLine(const std::vector<std::string>& rooms);
}

#endif
