#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct memberVar{
    string dataType;
    string memberName;
};

string askClassName();
vector<string> askMemberVariables(vector<memberVar> &classVariables);
void writeFile(ofstream &classFile, string className, string fileName, string guardName,vector<memberVar> &classVariables, vector<string> includeList);
void checkInclude(vector<string> &includeList, string mData);
void outputPrivate(ofstream &classFile, vector<memberVar> &classVariables);
void outputPublic(ofstream &classFile, vector<memberVar> classVariables, string className);
void information();

#endif