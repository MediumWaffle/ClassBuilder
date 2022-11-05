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
    for(int j=0; j<(int)includeList.size(); ++j){
        for(int k=0; k<(int)includeList[0].length(); ++k){
            cout << includeList[j][k] << " ";
        }
        cout << "\n";
    }
    //write to the class file
    //top guard
    classFile << "#ifndef " << guardName << "\n"
              << "#define " << guardName << "\n";
    //class initilization'
    for(int i=0; i<(int)includeList.size(); ++i){
        cout << "\n";
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
              << "{\n"
              << "    private:\n";
              for(int i=0; i<(int)classVariables.size(); ++i){
                classFile << "        " << classVariables[i].dataType << " " << classVariables[i].memberName << ";\n";
              }
    classFile << "    public:\n"
              << "        //get and set functions here\n"
              << "};\n\n"
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

//TODO LIST
/*
-make getter and setter functions
    -set first index of variable name to toupper()
    -put get/set infront of it
    -get
        -same data type as member variable
        -return member variable name
    -set
        -void func
        -perameters, with variable as same data type
        -set member variable to perameter variable
*/