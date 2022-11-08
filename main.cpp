#include "class.h"

int main(){
    //initilize variables
    string className, fileName, guardName;
    ofstream classFile;
    vector<memberVar> classVariables;
    vector<string> includeList;

    information();

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
//Person int age string name vector<int> calendar vector<string> bdayInvites char middleInitial fstream fFile ifstream iFile ofstream oFile .