#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace myStringLib {
	string ReadString(string Message) {
		string Str;
		cout << Message;
		getline(cin >> ws, Str);
		return Str;
	}
	char ReadChar(string Message) {
		char Ch;
		cout << Message;
		cin >> Ch;
		return Ch;
	}
	vector<string> SplitString(string Str, string Delim) {
		vector<string> vLines;
		string Word;
		short pos = Str.find(Delim);
		while (pos != string::npos) {
			Word = Str.substr(0, pos);
			if (Word != "") {
				vLines.push_back(Word);
			}
			Str.erase(0, pos + Delim.length());
			pos = Str.find(Delim);
		}
		vLines.push_back(Str);
		return vLines;
	}
	string JoinString(vector<string> Str, string Delim) {
		string JoinedStr = "";
		for (string& Word : Str) {
			JoinedStr.append(Word + Delim);
		}
		return JoinedStr.substr(0, JoinedStr.length() - Delim.length());
	}
	char InvertCharCase(char Ch) {
		return islower(Ch) ? toupper(Ch) : tolower(Ch);
	}
	string UpperAllString(string Str) {
		string UpperStr = "";
		for (char& ch : Str) {
			UpperStr.push_back(toupper(ch));
		}
		return UpperStr;
	}
	string LowerAllString(string Str) {
		string LowerStr = "";
		for (char& ch : Str) {
			LowerStr.push_back(tolower(ch));
		}
		return LowerStr;
	}
	string UpperFirstLetterInEachWord(string Str) {
		vector<string> SplittedStr = SplitString(Str, " ");
		// Here the reference sign is required because changes should be reflexed to the vector.
		for (string& Word : SplittedStr) {
			Word[0] = toupper(Word[0]);
		}
		return JoinString(SplittedStr, " ");
	}
	string LowerFirstLetterInEachWord(string Str) {
		// Method 2
		// by default, the char at the first index is the first letter.
		bool IsFirstLetter = true;
		for (short i = 0; i < Str.length(); i++) {
			if (Str[i] != ' ' && IsFirstLetter) {
				Str[i] = tolower(Str[i]);
			}
			IsFirstLetter = (Str[i] == ' ');
		}
		return Str;
	}
}