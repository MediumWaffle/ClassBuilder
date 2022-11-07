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
void outputPublic(ofstream &classFile, vector<memberVar> classVariables);


int main(){

    //initilize variables
    string className, fileName, guardName;
    ofstream classFile;
    vector<memberVar> classVariables;
    vector<string> includeList;

    className = askClassName();

    //set file name
    fileName = className;
    fileName += ".h";

    //check if file was created and opened
    classFile.open(fileName);
    if(!classFile){
        cout << "Error opening file\n";
        exit(1);
    }

    includeList = askMemberVariables(classVariables);

    //make name for guard code, uppercase
    guardName = className;
    for(int i=0; i<(int)guardName.length(); ++i){
        guardName[i] = toupper(guardName[i]); 
    }
    guardName += "_H";

    writeFile(classFile, className, fileName, guardName, classVariables, includeList);

    classFile.close();
    return 0;
}



string askClassName(){
    //ask for class name
    string className;
    cout << "Welcome to Class Creator\n\n"
         << "To get started, please enter the name of your class\n"
         << "Make sure this name has no spaces\n";
    cin >> className;
    return className;
}

vector<string> askMemberVariables(vector<memberVar> &classVariables){
    //ask for member variables
    memberVar newMemberVariable;
    vector<string> includeList;
    string mVar;
    string mData;
    cout << "\nDo you want your class to have any member variables?\n"
         << "Remember that you may not use spaces to define variables or data types.\n"
         << "Enter the name of your data type first, or\n"
         << "You may enter a '.' (period) if you have no variables\n";
    cin >> mData;
    if(mData != "."){
        checkInclude(includeList, mData);
        cout << "Now enter the name of your varibale\n";
        cin >> mVar;
    }
    while(mData != "."){
        newMemberVariable.dataType = mData;
        newMemberVariable.memberName = mVar;
        classVariables.push_back(newMemberVariable);
        cout << "\nPlease enter another data type or a '.' (period) to finish\n";
        cin >> mData;
        if(mData != "."){
            checkInclude(includeList, mData);
            cout << "Please enter the variable name\n";
            cin >> mVar;
        }
    }
    return includeList;
}

void writeFile(ofstream &classFile, string className, string fileName, string guardName, vector<memberVar> &classVariables, vector<string> includeList){
    //write to the class file
    //top guard
    classFile << "#ifndef " << guardName << "\n"
              << "#define " << guardName << "\n";
    //class initilization'
    if(includeList.size() > 0){
        classFile << "\n";
    }
    for(int i=0; i<(int)includeList.size(); ++i){
        if(includeList[i] == "string"){
            classFile << "#include <string>\n";
        } else if (includeList[i].size()>=6 &&
                   includeList[i][0] == 'v' && 
                   includeList[i][1] == 'e' && 
                   includeList[i][2] == 'c' && 
                   includeList[i][3] == 't' && 
                   includeList[i][4] == 'o' && 
                   includeList[i][5] == 'r'){
            classFile << "#include <vector>\n";
        } else if (includeList[i] == "fstream"){
            classFile << "#include <fstream>\n";
        }
    }
    classFile << "\nclass " << className << "\n"
              << "{\n";
    outputPublic(classFile, classVariables);
    outputPrivate(classFile, classVariables);
    classFile << "};\n\n"
    //bottom guard
              << "#endif";
}

void checkInclude(vector<string> &includeList, string mData){
    //adds more includes if certain data types are added to be more dynamic
    if (mData == "string"){
        includeList.push_back("string");
    } else if (mData.size()>=6 &&
               mData[0] == 'v' && 
               mData[1] == 'e' && 
               mData[2] == 'c' && 
               mData[3] == 't' && 
               mData[4] == 'o' && 
               mData[5] == 'r'){
        includeList.push_back("vector");
    } else if (mData == "fstream" || mData == "ifstream" || mData == "ofstream"){
        includeList.push_back("fstream");
    }
}

void outputPrivate(ofstream &classFile, vector<memberVar> &classVariables){
    classFile << "    private:\n";
    for(int i=0; i<(int)classVariables.size(); ++i){
        if(classVariables[i].dataType == "string" || classVariables[i].dataType == "fstream" || classVariables[i].dataType == "ifstream" || classVariables[i].dataType == "ofstream"){
            classFile << "        std::" << classVariables[i].dataType << " " << classVariables[i].memberName << ";\n";
        } else if (classVariables[i].dataType.size()>=6 &&
                    classVariables[i].dataType[0] == 'v' && 
                    classVariables[i].dataType[1] == 'e' && 
                    classVariables[i].dataType[2] == 'c' && 
                    classVariables[i].dataType[3] == 't' && 
                    classVariables[i].dataType[4] == 'o' && 
                    classVariables[i].dataType[5] == 'r'){
            classFile << "        std::" << classVariables[i].dataType << " " << classVariables[i].memberName << ";\n";
        } else {
            classFile << "        " << classVariables[i].dataType << " " << classVariables[i].memberName << ";\n";
        }
    }
}

void outputPublic(ofstream &classFile, vector<memberVar> classVariables){
    classFile << "    public:\n";
    //get functions
    for(int i=0; i<(int)classVariables.size(); ++i){
        string temp = classVariables[i].memberName;
        temp[0] = toupper(temp[0]);
        if(classVariables[i].dataType == "string"){
            classFile << "        std::" << classVariables[i].dataType << " get"<< temp << "(){return " << classVariables[i].memberName << ";}\n";
        } else if (classVariables[i].dataType == "fstream" || classVariables[i].dataType == "ifstream" || classVariables[i].dataType == "ofstream"){
            classFile << "        std::" << classVariables[i].dataType << "* get"<< temp << "(){return &" << classVariables[i].memberName << ";}\n";
        }else if (classVariables[i].dataType.size()>=6 &&
                    classVariables[i].dataType[0] == 'v' && 
                    classVariables[i].dataType[1] == 'e' && 
                    classVariables[i].dataType[2] == 'c' && 
                    classVariables[i].dataType[3] == 't' && 
                    classVariables[i].dataType[4] == 'o' && 
                    classVariables[i].dataType[5] == 'r'){
            classFile << "        std::" << classVariables[i].dataType << " get"<< temp << "(){return " << classVariables[i].memberName << ";}\n";
        } else {
            classFile << "        " << classVariables[i].dataType << " get"<< temp << "(){return " << classVariables[i].memberName << ";}\n";
        }
    }
    //set functions
    for(int k=0; k<(int)classVariables.size(); ++k){
        string temp = classVariables[k].memberName;
        temp[0] = toupper(temp[0]);
        if(classVariables[k].dataType == "string"){
            classFile << "        void set" << temp << "(std::" << classVariables[k].dataType << " " << classVariables[k].memberName << "){this->" << classVariables[k].memberName << "=" << classVariables[k].memberName << ";}\n";
        } else if (classVariables[k].dataType == "fstream" || classVariables[k].dataType == "ifstream" || classVariables[k].dataType == "ofstream"){
            //cannot set a file, if you have a member name called fileName, then it will set that instead
        }else if (classVariables[k].dataType.size()>=6 &&
                    classVariables[k].dataType[0] == 'v' && 
                    classVariables[k].dataType[1] == 'e' && 
                    classVariables[k].dataType[2] == 'c' && 
                    classVariables[k].dataType[3] == 't' && 
                    classVariables[k].dataType[4] == 'o' && 
                    classVariables[k].dataType[5] == 'r'){
            classFile << "        void set" << temp << "(std::" << classVariables[k].dataType << " " << classVariables[k].memberName << "){this->" << classVariables[k].memberName << "=" << classVariables[k].memberName << ";}\n";
        } else {
            classFile << "        void set" << temp << "(" << classVariables[k].dataType << " " << classVariables[k].memberName << "){this->" << classVariables[k].memberName << "=" << classVariables[k].memberName << ";}\n";
        }
    }
}

//TODO
/*
- Clean up text, make look nice
- If an include is already included, do not repeat that include
- Make setter's for fstream objects
*/