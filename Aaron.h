#ifndef AARON_H
#define AARON_H

#include <string>
#include <vector>
#include <fstream>
#include <fstream>
#include <fstream>

class Aaron
{
    public:
        int getAge(){return age;}
        std::string getName(){return name;}
        std::vector<int> getCalendar(){return calendar;}
        std::fstream* getFFile(){return &fFile;}
        std::ifstream* getIFile(){return &iFile;}
        std::ofstream* getOFile(){return &oFile;}
        void setAge(int age){this->age=age;}
        void setName(std::string name){this->name=name;}
        void setCalendar(std::vector<int> calendar){this->calendar=calendar;}
    private:
        int age;
        std::string name;
        std::vector<int> calendar;
        std::fstream fFile;
        std::ifstream iFile;
        std::ofstream oFile;
};

#endif