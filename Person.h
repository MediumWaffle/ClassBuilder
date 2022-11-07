#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <fstream>
#include <fstream>
#include <fstream>

class Person
{
    public:
        int getAge(){return age;}
        std::string getName(){return name;}
        std::vector<int> getList(){return list;}
        std::fstream* getFFile(){return &fFile;}
        std::ifstream* getIFile(){return &iFile;}
        std::ofstream* getOFile(){return &oFile;}
        char getMiddleInitial(){return middleInitial;}
        void setAge(int age){this->age=age;}
        void setName(std::string name){this->name=name;}
        void setList(std::vector<int> list){this->list=list;}
        void setMiddleInitial(char middleInitial){this->middleInitial=middleInitial;}
    private:
        int age;
        std::string name;
        std::vector<int> list;
        std::fstream fFile;
        std::ifstream iFile;
        std::ofstream oFile;
        char middleInitial;
};

#endif