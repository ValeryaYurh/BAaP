#pragma once
#include <string>
using namespace std; 

union DiscountValue
{
    int percent;
    char code;
};

struct Customer
{
    string name;
    string address;
    union DiscountValue discount;
};

void menu();

void allCustomers(Customer *&person, int &size);

void printArr(Customer *&person, int &size);

void addCustomers(Customer *&person, int &size);

void findCustomer(Customer *&person, int &size);

void delete_changeCustomer(Customer *&person, int &size);

void writeFile(Customer *&person, int &size);

void readFile(Customer *&person, int &size);

void insertionSortByDiscount(Customer *&person, int &size);
