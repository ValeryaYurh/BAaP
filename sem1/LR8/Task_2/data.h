#pragma once
#include <string>
using namespace std;

union Date
{
    double number;
    char fullDate[20];
};

struct InfCall
{
    union Date date;
    bool isNumericDate;
    int code;
    string city;
    double tariff;
    int lengthOfConversation;
    int telephoneInCity;
    int telephone;
};

void menu();

void allInfCalls(InfCall *&call, int &size);

void printArr(InfCall *&call, int &size);

void addInfCalls(InfCall *&call, int &size);

void sumCallsForCities(InfCall *&call, int &size);

void delete_changeInfCall(InfCall *&call, int &size);

void writeFile(InfCall *&call, int &size);

void readFile(InfCall *&call, int &size);

