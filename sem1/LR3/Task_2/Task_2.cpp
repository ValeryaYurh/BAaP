#include <iostream>
#include <cmath>
#include <string>
using namespace std;

#define BRED    "\033[91m"
#define GREEN   "\033[32m"
#define BBLUE   "\033[94m"
#define RESET   "\033[0m"
#define BYELLOW "\033[93m"

void sum(){
    int n = 1;
    double s= 0.0;
    double d;
    do {
        d = 1/pow(2, n) + 1/pow(3, n);
        s += d;
        n++;
    } while(d>=0.001);
    
    cout << GREEN << "Результат вычислений равен: " << s << RESET << endl;
}

void help(){
    cout << GREEN << "calc\tвыводит значение\n"<< BYELLOW << "help\tвыводит дополнительную информацию\n" << BRED <<"quit,exit\tвыходит из проекта"<<endl; 
}

int main(){
    cout << BBLUE << "Добро пожаловать!" << endl
         << "Данный проект подготовлен Юргилевич Валерией" << RESET << endl
         << BYELLOW << "В данном проекте нужно используя цикл используя цикл do while найти сумму ряда с точностью 𝜀 = 10−3, общий член которого 𝑑𝑛 = 1/2𝑛 + 1/3𝑛" << endl   
         << "Введите" << BBLUE << " calc"<< RESET << ", если хотите вывести значение;"<< BBLUE << " help" << RESET<<", если нужна дополнительная информация" << endl
         << "Если хотитие закончить проект, введите" << BBLUE << " quit или exit" << endl;
    while(true){
      string command;
      cout << BYELLOW << "Введите команду: " << RESET;
      cin >> command;  
      if(command == "calc"){
        sum();
      }else if(command == "help"){
        help();
      }else if(command == "quit" || command == "exit"){
        return 0;
      }else{
        cout << BRED << "Данная команда не найдена"<< RESET << endl;
      }
    }  
return 0;
}