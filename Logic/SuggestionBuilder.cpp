//@author A0122357L

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

	string suggestedUserInput = commandType;// +suggestedCommandArguments;

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
		return "update [taskNumber] details/deadline/start end";
	}
	else if (isPredictedCommandCheckSavedFileLocation(userInput)){
		return "checkfileloc";
	}
	else if (isPredictedChangeFileLocation(userInput)){
		return "changefileloc [New Directory]";
	}

	return "invalid";

}

string SuggestionBuilder::suggestCommandArguments(string commandType, string userInput){
	
	if (commandType == "add"){
		return predictCommandAdd(userInput);
	}

	else if (commandType == "delete"){
		return "";
	}

	else if (commandType == "display"){
		return "";
	}

	else if (commandType == "exit"){
		return "";
	}

	else if (commandType == "mark"){
		return "";
	}

	else if (commandType == "undo"){
		return "";
	}

	else if (commandType == "unmark"){
		return "";
	}

	else if (commandType == "update"){
		return "";
		//should add more logic here!
	}

	return "";
}


string SuggestionBuilder::predictCommandAdd(string userInput){

	string currentArguments = removeFirstWord(userInput);

	ostringstream predictedArguments;

	//return nothing if no current arguments
	if (currentArguments == ""){
		return predictedArguments.str();
	}

	vector<string> textVec = splitParameters(currentArguments);
	vector<string>::iterator iter = textVec.begin();

	bool hitFirstCommandWord = false;
	ostringstream taskToAdd;

	bool predictedFrom = false, predictedBy = false, predictedEvery = false;
	bool predictedThis = false, predictedNext = false, predictedDay = false;
	string dayValue; 

	while (iter != textVec.end()){

		string predictString = predictedString(*iter);
		string currentString = *iter;

		if (!predictedFrom && !predictedBy && !predictedEvery){

			if (predictString == "from"){
				predictedFrom = true;
				hitFirstCommandWord = true;
			}
			else if (predictString == "by"){
				predictedBy = true;
				hitFirstCommandWord = true;
			}
			else if (predictString == "every"){
				predictedEvery = true;
				hitFirstCommandWord = true;
			}
		}
		else if (!predictedDay){
			if (predictString == "monday" || predictString == "tuesday" ||
				predictString == "wednesday" || predictString == "thursday" ||
				predictString == "friday" || predictString == "saturday"
				|| predictString == "sunday"){
				dayValue = predictString;
				predictedDay = true;
				hitFirstCommandWord = true;
			}
		}
		else if (!predictedThis){
			if (predictString == "this"){
				predictedThis = true;
				hitFirstCommandWord = true;
			}
		}
		else if (!predictedNext){
			if (predictString == "next"){
				predictedThis = true;
				hitFirstCommandWord = true;
			}
		}

		if (!hitFirstCommandWord){
			taskToAdd << " " << currentString;
		}

		iter++;
	}

	predictedArguments << taskToAdd.str();

	//forming string
	if (predictedFrom){
		if (predictedDay&&predictedThis&&predictedNext){
			predictedArguments << " from this " << dayValue << " to next ";
		}
		else if (predictedDay&&predictedThis&&!predictedNext){
			predictedArguments << " from this " << dayValue << " to ";
		}
		else if (predictedDay&&!predictedThis&&predictedNext){
			predictedArguments << " from next " << dayValue << " to ";
		}
		else if (predictedDay&&!predictedThis&&!predictedNext){
			predictedArguments << " from " << dayValue << " to ";
		}
		else if (!predictedDay){
			predictedArguments << " from ";
		}
	}
	else if (predictedBy){
		if (predictedDay&&predictedThis&&predictedNext){
			predictedArguments << " by " << dayValue;
		}
		else if (predictedDay&&predictedThis&&!predictedNext){
			predictedArguments << " by this " << dayValue;
		}
		else if (predictedDay&&!predictedThis&&predictedNext){
			predictedArguments << " by next " << dayValue;
		}
		else if (predictedDay&&!predictedThis&&!predictedNext){
			predictedArguments << " by " << dayValue;
		}
		else if (!predictedDay){
			predictedArguments << " by ";
		}

	}
	else if (predictedEvery){
		if (predictedDay){
			predictedArguments << " every " << dayValue;
		}
		else if (!predictedDay){
			predictedArguments << " every ";
		}
		//logic for predictedMonth?
	}

	return predictedArguments.str();
}

string SuggestionBuilder::predictedString(string text){

	//command words have higher priority
	string predictString = predictedKeyword(text);

	//days have next priority
	if (predictString == ""){
		predictString = predictedDay(text);
	}

	/*
	//dates have final priority
	if (predictString == ""){
		predictString = predictedDate(text);
	}*/

	return predictString;

}

string SuggestionBuilder::predictedKeyword(string text){

	if (isPredictedFrom(text)){
		return "from";
	}
	else if (isPredictedTo(text)){
		return "to";
	}
	else if (isPredictedNext(text)){
		return "next";
	}
	else if (isPredictedBy(text)){
		return "by";
	}
	else if (isPredictedThis(text)){
		return "this";
	}
	else if (isPredictedEvery(text)){
		return "every";
	}
	else{
		return "";
	}

}

bool SuggestionBuilder::isPredictedFrom(string userInput){

	if (userInput == "f" || userInput == "fr" || 
		userInput == "fro" || userInput == "from"){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedTo(string userInput){

	if (userInput == "t" || userInput == "to"){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedNext(string userInput){

	if (userInput == "n" || userInput == "ne" ||
		userInput == "nex" || userInput == "next"){
		return true;
	}

	return false;
}


bool SuggestionBuilder::isPredictedBy(string userInput){

	if (userInput == "b" || userInput == "by" ){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedThis(string userInput){

	if (userInput == "t" || userInput == "th" ||
		userInput == "thi" || userInput == "this"){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedEvery(string userInput){

	if (userInput == "e" || userInput == "ev" ||
		userInput == "eve" || userInput == "ever"
		|| userInput == "every"){
		return true;
	}

	return false;
}

string SuggestionBuilder::predictedDay(string text){
	
	if (isPredictedMonday(text)){
		return "monday";
	}
	else if (isPredictedTuesday(text)){
		return "tuesday";
	}
	else if (isPredictedWednesday(text)){
		return "wednesday";
	}
	else if (isPredictedThursday(text)){
		return "thursday";
	}
	else if (isPredictedFriday(text)){
		return "friday";
	}
	else if (isPredictedSaturday(text)){
		return "saturday";
	}
	else if (isPredictedSunday(text)){
		return "sunday";
	}
	else{
		return "";
	}
}

bool SuggestionBuilder::isPredictedMonday(string userInput){

	if (userInput == "m" || userInput == "mo" ||
		userInput == "mon" || userInput == "mond"
		|| userInput == "monda" || userInput == "monday"){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedTuesday(string userInput){

	if (userInput == "t" || userInput == "tu" ||
		userInput == "tue" || userInput == "tues"
		|| userInput == "tuesd" || userInput == "tuesda" 
		|| userInput == "tuesday"){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedWednesday(string userInput){

	if (userInput == "w" || userInput == "we" ||
		userInput == "wed" || userInput == "wedn"
		|| userInput == "wedne" || userInput == "wednes"
		|| userInput == "wednesd" || userInput == "wednesda"
		|| userInput == "wednesday"){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedThursday(string userInput){

	if (userInput == "t" || userInput == "th" ||
		userInput == "thu" || userInput == "thur"
		|| userInput == "thurs" || userInput == "thursd"
		|| userInput == "thursda" || userInput == "thursday"){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedFriday(string userInput){

	if (userInput == "f" || userInput == "fr" ||
		userInput == "fri" || userInput == "frid"
		|| userInput == "frida" || userInput == "friday"){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedSaturday(string userInput){

	if (userInput == "s" || userInput == "sa" ||
		userInput == "sat" || userInput == "satu"
		|| userInput == "satur" || userInput == "saturd"
		|| userInput == "saturda" || userInput == "saturday"){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedSunday(string userInput){

	if (userInput == "s" || userInput == "su" ||
		userInput == "sun" || userInput == "sund"
		|| userInput == "sunda" || userInput == "sunday"){
		return true;
	}

	return false;
}

bool SuggestionBuilder::isPredictedCommandAdd(string userInput){
	
	if (userInput == "a" || userInput == "ad" || userInput == "add"){
		return true;
	}

	if (StringDistance::LD(userInput.c_str(),"add")<=1){
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
