// RoomValidator.h
// Author: Bijaya Pokhrel
// Task: Invalid room validation (Production Plan row 9)
//
// Checks what the user typed for the start and end rooms before the
// shortest-path search runs. Catches empty input, rooms that are not in
// roomListNumbered.txt, and a start that is the same as the end.
// When a room is not found, it suggests close matches.

#ifndef ROOMVALIDATOR_H
#define ROOMVALIDATOR_H

#include <string>
#include <vector>

// Result of checking one room (or a start/end pair).
struct RoomCheck {
	bool valid;          // true if the input can be used
	int index;           // room number from roomListNumbered.txt (-1 if invalid)
	std::string room;    // cleaned-up room name, e.g. "A101B"
	std::string message; // explains the problem when valid is false
};

class RoomValidator {
	public:
		// Reads "<number> <room>" lines. Returns false if the file can't be opened.
		bool LoadRooms(const std::string& fileName);

		// Checks a single typed room name.
		RoomCheck CheckRoom(const std::string& input) const;

		// Checks start and end together (also catches start == end).
		// Returns the result for whichever one is wrong, or a valid
		// result for the end room if both are fine.
		RoomCheck CheckTrip(const std::string& startInput,
		                    const std::string& endInput) const;

		// Up to maxCount room names that look like the input.
		std::vector<std::string> Suggest(const std::string& input,
		                                 int maxCount = 3) const;

		int RoomCount() const;

		// Trims spaces and makes letters uppercase: " a101b " -> "A101B"
		static std::string Normalize(const std::string& input);

	private:
		std::vector<int> numbers;
		std::vector<std::string> names;

		static int EditDistance(const std::string& a, const std::string& b);
};

#endif
