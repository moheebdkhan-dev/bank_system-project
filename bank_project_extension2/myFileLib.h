#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

namespace myFileLib {
    vector<string> LoadLinesFromFile(string FileName) {
        vector<string> vLines;
        fstream File;
        File.open(FileName, ios::in);
        string Line;
        if (File.is_open()) {
            while (getline(File, Line)) {
                if (Line != "")
                    vLines.push_back(Line);
            }
            File.close();
        }
        return vLines;
    }
    bool AppendLineToFile(string Line, string FileName) {
        fstream File;
        File.open(FileName, ios::out | ios::app);
        if (File.is_open()) {
            File << Line << endl;
            File.close();
            return true;
        }
        return false;
    }
    void SaveLinesToFile(vector<string> Lines, string FileName) {
        fstream File;
        File.open(FileName, ios::out);
        if (File.is_open()) {
            for (string& Line : Lines) {
                File << Line << endl;
            }
            File.close();
        }
    }
}