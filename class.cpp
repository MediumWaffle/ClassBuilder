#include "class.h"

string askClassName(){
    //ask for class name
    string className;
    cout << "+-----------------------------+\n";
    cout << "+- Please enter a Class Name -+\n";
    cout << "+-----------------------------+\n";
    cout << " - ";
    cin >> className;
    cout << "\n";
    return className;
}

vector<string> askMemberVariables(vector<memberVar> &classVariables){
    //ask for member variables
    memberVar newMemberVariable;
    vector<string> includeList;
    string mVar;
    string mData;
    cout << "+-------------------------------------------------+\n";
    cout << "+- Enter the data type of your member variable   -+\n";
    cout << "+- Or enter '.' if you have no member variables  -+\n";
    cout << "+-------------------------------------------------+\n";
    cout << " - ";
    cin >> mData;
    cout << "\n";
    if(mData != "."){
        checkInclude(includeList, mData);
        cout << "+---------------------------------------+\n";
        cout << "+- Now enter the name of your varibale -+\n";
        cout << "+---------------------------------------+\n";
        cout << " - ";
        cin >> mVar;
        cout << "\n";
    }
    while(mData != "."){
        newMemberVariable.dataType = mData;
        newMemberVariable.memberName = mVar;
        classVariables.push_back(newMemberVariable);
        cout << "+----------------------------------+\n";
        cout << "+- Please enter another data type -+\n";
        cout << "+- Or enter '.' to exit           -+\n";
        cout << "+----------------------------------+\n";
        cout << " - ";
        cin >> mData;
        cout << "\n";
        if(mData != "."){
            checkInclude(includeList, mData);
            cout << "+----------------------------------+\n";
            cout << "+- Please enter the variable name -+\n";
            cout << "+----------------------------------+\n";
            cout << " - ";
            cin >> mVar;
            cout << "\n";
        }
    }
    return includeList;
}

void writeFile(ofstream &classFile, string className, string fileName, string guardName, vector<memberVar> &classVariables, vector<string> includeList){
    bool stringBool = false, vectorBool = false, fstreamBool = false;
    //write to the class file
    //top guard
    classFile << "#ifndef " << guardName << "\n"
              << "#define " << guardName << "\n";
    //class initilization'
    if(includeList.size() > 0){
        classFile << "\n";
    }
    for(int i=0; i<(int)includeList.size(); ++i){
        if(includeList[i] == "string" && !stringBool){
            classFile << "#include <string>\n";
            stringBool = true;
        } else if (includeList[i].size()>=6 &&
                   includeList[i][0] == 'v' && 
                   includeList[i][1] == 'e' && 
                   includeList[i][2] == 'c' && 
                   includeList[i][3] == 't' && 
                   includeList[i][4] == 'o' && 
                   includeList[i][5] == 'r' &&
                   !vectorBool){
            classFile << "#include <vector>\n";
            vectorBool = true;
        } else if (includeList[i] == "fstream" && !fstreamBool){
            classFile << "#include <fstream>\n";
            fstreamBool = true;
        }
    }
    classFile << "\nclass " << className << "\n"
              << "{\n";
    outputPublic(classFile, classVariables, className);
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
            if(classVariables[i].dataType.length() >= 14 &&
               classVariables[i].dataType[7] == 's' &&
               classVariables[i].dataType[8] == 't' &&
               classVariables[i].dataType[9] == 'r' &&
               classVariables[i].dataType[10] == 'i' &&
               classVariables[i].dataType[11] == 'n' &&
               classVariables[i].dataType[12] == 'g'){
                    classVariables[i].dataType[7] = 's';
                    classVariables[i].dataType[8] = 't';
                    classVariables[i].dataType[9] = 'd';
                    classVariables[i].dataType[10] = ':';
                    classVariables[i].dataType[11] = ':';
                    classVariables[i].dataType[12] = 's';
                    classVariables[i].dataType[13] = 't';
                    classVariables[i].dataType += "ring>";
                        classFile << "        std::" << classVariables[i].dataType << " " << classVariables[i].memberName << ";\n";
            } else {
                classFile << "        std::" << classVariables[i].dataType << " " << classVariables[i].memberName << ";\n";
            }
        } else {
            classFile << "        " << classVariables[i].dataType << " " << classVariables[i].memberName << ";\n";
        }
    }
}

void outputPublic(ofstream &classFile, vector<memberVar> classVariables, string className){
    classFile << "    public:\n"
              << "        " << className << "(){}\n"
              << "        ~" << className << "(){}\n";
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
            if(classVariables[i].dataType.length() >= 14 &&
               classVariables[i].dataType[7] == 's' &&
               classVariables[i].dataType[8] == 't' &&
               classVariables[i].dataType[9] == 'r' &&
               classVariables[i].dataType[10] == 'i' &&
               classVariables[i].dataType[11] == 'n' &&
               classVariables[i].dataType[12] == 'g'){    
                    classVariables[i].dataType[7] = 's';
                    classVariables[i].dataType[8] = 't';
                    classVariables[i].dataType[9] = 'd';
                    classVariables[i].dataType[10] = ':';
                    classVariables[i].dataType[11] = ':';
                    classVariables[i].dataType[12] = 's';
                    classVariables[i].dataType[13] = 't';
                    classVariables[i].dataType += "ring>";
                    classFile << "        std::" << classVariables[i].dataType << " get"<< temp << "(){return " << classVariables[i].memberName << ";}\n";
            } else{
                classFile << "        std::" << classVariables[i].dataType << " get"<< temp << "(){return " << classVariables[i].memberName << ";}\n";
            }
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
            if(classVariables[k].dataType.length() >= 14 &&
               classVariables[k].dataType[7] == 's' &&
               classVariables[k].dataType[8] == 't' &&
               classVariables[k].dataType[9] == 'r' &&
               classVariables[k].dataType[10] == 'i' &&
               classVariables[k].dataType[11] == 'n' &&
               classVariables[k].dataType[12] == 'g'){    
                    classVariables[k].dataType[7] = 's';
                    classVariables[k].dataType[8] = 't';
                    classVariables[k].dataType[9] = 'd';
                    classVariables[k].dataType[10] = ':';
                    classVariables[k].dataType[11] = ':';
                    classVariables[k].dataType[12] = 's';
                    classVariables[k].dataType[13] = 't';
                    classVariables[k].dataType += "ring>";
                    classFile << "        void set" << temp << "(std::" << classVariables[k].dataType << " " << classVariables[k].memberName << "){this->" << classVariables[k].memberName << "=" << classVariables[k].memberName << ";}\n";
            } else {
                classFile << "        void set" << temp << "(std::" << classVariables[k].dataType << " " << classVariables[k].memberName << "){this->" << classVariables[k].memberName << "=" << classVariables[k].memberName << ";}\n";
            }
        } else {
            classFile << "        void set" << temp << "(" << classVariables[k].dataType << " " << classVariables[k].memberName << "){this->" << classVariables[k].memberName << "=" << classVariables[k].memberName << ";}\n";
        }
    }
}

void information(){
    cout << "+----------------------------+\n"
         << "+- Welcome to Class Creator -+\n"
         << "+----------------------------+\n"
         << "+- [Class Name]             -+\n"
         << "+- When entereing a class   -+\n"
         << "+- name dont use any spaces -+\n"
         << "+-                          -+\n"
         << "+- [Member Variables]       -+\n"
         << "+- You will be asked to     -+\n"
         << "+- enter a data type then   -+\n"
         << "+- a variable name. Don't   -+\n"
         << "+- use any spaces here.     -+\n"
         << "+-                          -+\n"
         << "+- [When Finished]          -+\n"
         << "+- Enter a '.' (period) to  -+\n"
         << "+- end program and write    -+\n"
         << "+- to the file.             -+\n"
         << "+----------------------------+\n\n";
}
