//@author A0114084N

#include "SuggestionBuilder.h"


SuggestionBuilder::SuggestionBuilder()
{
}


SuggestionBuilder::~SuggestionBuilder()
{
}


string SuggestionBuilder::suggestUserInput(string userInput){

	std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);

	string commandType = suggestCommandType(userInput);

	string suggestedUserInput = commandType;

	return suggestedUserInput;
}


string SuggestionBuilder::suggestCommandType(string userInput){

	if (userInput == ""){

		return "e.g: add, delete, update, search, mark, unmark, undo, checkfilelocation, changefilelocation, help";

	}

	userInput = getFirstWord(userInput);

	if (isPredictedCommandAdd(userInput)){
		return "add cs2103 from 6 may 13:00 to 7 may 14:00 #high";
	}

	else if (isPredictedCommandDelete(userInput)){
		return "delete [taskNumber]";
	}

	else if (isPredictedCommandDisplay(userInput)){
		return "display";
	}

	else if (isPredictedCommandExit(userInput)){
		return "exit";
	}

	else if (isPredictedCommandMark(userInput)){
		return "mark [taskNumber]";
	}

	else if (isPredictedCommandUndo(userInput)){
		return "undo";
	}

	else if (isPredictedCommandUnmark(userInput)){
		return "unmark [taskNumber]";
	}

	else if (isPredictedCommandUpdate(userInput)){
		return "update [taskNumber] details/deadline/starttime/endtime/priority [things to be updated]";
	}
	else if (isPredictedCommandCheckSavedFileLocation(userInput)){
		return "checkfileloc";
	}
	else if (isPredictedChangeFileLocation(userInput)){
		return "changefileloc [New Directory]";
	}
	else if (isPredictedCommandSearch(userInput)){
		return "search next available [xx day yy hour zz min]";
	}
	else if (isPredictedCommandHelp(userInput)){
		return "Help : Press F1";
	}

	return "invalid";

}




bool SuggestionBuilder::isPredictedCommandAdd(string userInput){

	if (userInput == "a" || userInput == "ad" || userInput == "add"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "add") <= 1){
		return true;
	}

	return false;

}

bool SuggestionBuilder::isPredictedCommandDelete(string userInput){

	if (userInput == "d" || userInput == "de" ||
		userInput == "del" || userInput == "dele" ||
		userInput == "delet" || userInput == "delete"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "delete") <= 1){
		return true;
	}

	return false;
}


bool SuggestionBuilder::isPredictedCommandDisplay(string userInput){

	if (userInput == "d" || userInput == "di" ||
		userInput == "dis" || userInput == "disp" ||
		userInput == "displ" || userInput == "display"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "display") <= 1){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedCommandExit(string userInput){

	if (userInput == "e" || userInput == "ex" ||
		userInput == "exi" || userInput == "exit"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "exit") <= 1){
		return true;
	}

	return false;
}


bool SuggestionBuilder::isPredictedCommandMark(string userInput){

	if (userInput == "m" || userInput == "ma" ||
		userInput == "mar" || userInput == "mark"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "mark") <= 1){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedCommandUndo(string userInput){

	if (userInput == "u" || userInput == "un" ||
		userInput == "und" || userInput == "undo"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "undo") <= 1){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedCommandUnmark(string userInput){

	if (userInput == "u" || userInput == "un" ||
		userInput == "unm" || userInput == "unma" ||
		userInput == "unmar" || userInput == "unmark"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "unmark") <= 1){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedCommandUpdate(string userInput){

	if (userInput == "u" || userInput == "up" ||
		userInput == "upd" || userInput == "upda" ||
		userInput == "updat" || userInput == "update"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "update") <= 1){
		return true;
	}

	return false;
}



bool SuggestionBuilder::isPredictedCommandCheckSavedFileLocation(string userInput){

	if (userInput == "c" || userInput == "ch" ||
		userInput == "che" || userInput == "chec" ||
		userInput == "check" || userInput == "checkf" ||
		userInput == "checkfi" || userInput == "checkfil" ||
		userInput == "checkfile" || userInput == "checkfilel" ||
		userInput == "checkfilelo" || userInput == "checkfileloc"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "checkfileloc") <= 1){
		return true;
	}
	return false;
}

bool SuggestionBuilder::isPredictedChangeFileLocation(string userInput){

	if (userInput == "c" || userInput == "ch" ||
		userInput == "cha" || userInput == "chan" ||
		userInput == "chang" || userInput == "change" ||
		userInput == "changef" || userInput == "changefi" ||
		userInput == "changefil" || userInput == "changefile" ||
		userInput == "changefilel" || userInput == "changefilelo" ||
		userInput == "changefileloc"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "checkfileloc") <= 1){
		return true;
	}
	return false;
}

bool SuggestionBuilder::isPredictedCommandSearch(string userInput){
	if (userInput == "s" || userInput == "se" ||
		userInput == "sea" || userInput == "sear" ||
		userInput == "searc" || userInput == "search"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "search") <= 1){
		return true;
	}
	return false;


}

bool SuggestionBuilder::isPredictedCommandHelp(string userInput){
	if (userInput == "h" || userInput == "he" ||
		userInput == "hel" || userInput == "help"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(), "help") <= 1){
		return true;
	}
	return false;


}


/*
* ====================================================================
*  Additional functions
* ====================================================================
*/
string SuggestionBuilder::removeFirstWord(string userCommand) {
	return trim(replace(userCommand, getFirstWord(userCommand), ""));
}

string SuggestionBuilder::getFirstWord(string userCommand) {
	string commandTypeString = splitParameters(userCommand)[0];
	return commandTypeString;
}

// This method only split string based on delimiter space
vector<string> SuggestionBuilder::splitParameters(string commandParametersString){
	vector<string> tokens;
	istringstream iss(commandParametersString);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter<vector<string> >(tokens));

	return tokens;
}

inline string SuggestionBuilder::trim_right(const string& s, const string& delimiters) {
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

inline string SuggestionBuilder::trim_left(const string& s, const string& delimiters) {
	return s.substr(s.find_first_not_of(delimiters));
}

inline string SuggestionBuilder::trim(const string& s, const string& delimiters) {
	if (!s.empty())
		return trim_left(trim_right(s, delimiters), delimiters);
	else
		return s;
}

bool SuggestionBuilder::equalsIgnoreCase(const string& str1, const string& str2) {
	if (str1.size() != str2.size()) {
		return false;
	}
	for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
		if (tolower(*c1) != tolower(*c2)) {
			return false;
		}
	}
	return true;
}

int SuggestionBuilder::parseInt(string str) {
	char c;
	int i = 0;
	std::stringstream ss(str);
	ss >> i;
	if (ss.fail() || ss.get(c)) {
		return -1;
	}
	else {
		return i;
	}
}

string SuggestionBuilder::replace(string a, string b, string c) {
	int pos;
	do {
		pos = a.find(b);
		if (pos != -1)  a.replace(pos, b.length(), c);
	} while (pos != -1);
	return a;
}
