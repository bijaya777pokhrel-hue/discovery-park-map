// RoomValidator.cpp
// Author: Bijaya Pokhrel
// Task: Invalid room validation (Production Plan row 9)

#include "RoomValidator.h"
#include <algorithm>
#include <cctype>
#include <fstream>

using namespace std;

bool RoomValidator::LoadRooms(const string& fileName){
	ifstream in(fileName);
	if(!in){
		return false;
	}
	numbers.clear();
	names.clear();
	int number;
	string name;
	while(in >> number >> name){
		numbers.push_back(number);
		names.push_back(Normalize(name));
	}
	return true;
}

int RoomValidator::RoomCount() const {
	return (int)names.size();
}

string RoomValidator::Normalize(const string& input){
	size_t first = input.find_first_not_of(" \t\r\n");
	if(first == string::npos){
		return "";
	}
	size_t last = input.find_last_not_of(" \t\r\n");
	string out = input.substr(first, last - first + 1);
	for(size_t i = 0; i < out.size(); i++){
		out[i] = (char)toupper((unsigned char)out[i]);
	}
	return out;
}

RoomCheck RoomValidator::CheckRoom(const string& input) const {
	RoomCheck result;
	result.valid = false;
	result.index = -1;
	result.room = Normalize(input);

	if(result.room.empty()){
		result.message = "Please enter a room name.";
		return result;
	}

	for(size_t i = 0; i < names.size(); i++){
		if(names[i] == result.room){
			result.valid = true;
			result.index = numbers[i];
			return result;
		}
	}

	result.message = "Room \"" + result.room + "\" was not found in Discovery Park.";
	vector<string> close = Suggest(result.room);
	if(!close.empty()){
		result.message += " Did you mean: ";
		for(size_t i = 0; i < close.size(); i++){
			result.message += close[i];
			if(i + 1 < close.size()){
				result.message += ", ";
			}
		}
		result.message += "?";
	}
	return result;
}

RoomCheck RoomValidator::CheckTrip(const string& startInput,
                                   const string& endInput) const {
	RoomCheck start = CheckRoom(startInput);
	if(!start.valid){
		start.message = "Start: " + start.message;
		return start;
	}
	RoomCheck end = CheckRoom(endInput);
	if(!end.valid){
		end.message = "Destination: " + end.message;
		return end;
	}
	if(start.index == end.index){
		end.valid = false;
		end.message = "Start and destination are both " + end.room +
		              ". Please pick two different rooms.";
	}
	return end;
}

vector<string> RoomValidator::Suggest(const string& input, int maxCount) const {
	string target = Normalize(input);
	vector<pair<int, string>> scored;
	if(target.empty()){
		return vector<string>();
	}

	for(size_t i = 0; i < names.size(); i++){
		int score = EditDistance(target, names[i]);
		// Rooms that start with what the user typed are good matches too.
		if(names[i].compare(0, target.size(), target) == 0){
			score = min(score, 1);
		}
		if(score <= 2){
			scored.push_back(make_pair(score, names[i]));
		}
	}
	sort(scored.begin(), scored.end());

	vector<string> out;
	for(size_t i = 0; i < scored.size() && (int)out.size() < maxCount; i++){
		out.push_back(scored[i].second);
	}
	return out;
}

// Number of single-letter edits needed to turn a into b.
int RoomValidator::EditDistance(const string& a, const string& b){
	vector<int> prev(b.size() + 1), curr(b.size() + 1);
	for(size_t j = 0; j <= b.size(); j++){
		prev[j] = (int)j;
	}
	for(size_t i = 1; i <= a.size(); i++){
		curr[0] = (int)i;
		for(size_t j = 1; j <= b.size(); j++){
			int cost = (a[i-1] == b[j-1]) ? 0 : 1;
			curr[j] = min(min(prev[j] + 1, curr[j-1] + 1), prev[j-1] + cost);
		}
		prev.swap(curr);
	}
	return prev[b.size()];
}
