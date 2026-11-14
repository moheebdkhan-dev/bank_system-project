#pragma once
#include <iostream>

using namespace std;

namespace myInputLib {
	short ReadInteger(string Message) {
		short Num;
		cout << Message;
		cin >> Num;
		return Num;
	}
	float ReadFloat(string Message) {
		float Num;
		cout << Message;
		cin >> Num;
		return Num;
	}
}