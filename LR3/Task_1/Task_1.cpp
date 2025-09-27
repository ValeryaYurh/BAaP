#include <iostream>
using namespace std;

#define BRED    "\033[91m"
#define GREEN   "\033[32m"
#define BBLUE   "\033[94m"
#define RESET   "\033[0m"
#define BYELLOW "\033[93m"

void sum(){
    int i = 1;
    double s = 0;
    while(i<=30){
        double a = i%2==0 ? i/2 : i;
        double b = i%2==0 ? i*i*i : i*i;
        s += (a-b)*(a-b);
        ++i;
    }
    cout << GREEN << "Результат вычислений равен: " << s << RESET << endl;
}

void help(){
    cout << GREEN << "calc\tвыводит значение\n"<< BYELLOW << "help\tвыводит дополнительную информацию\n" << BRED <<"quit,exit\tвыходит из проекта"<<endl; 
}

int main(){
    cout << BBLUE << "Добро пожаловать!" << endl
         << "Данный проект подготовлен Юргилевич Валерией" << RESET << endl
         << BYELLOW << "В данном проекте нужно используя цикл while вычислить 𝑁  = ᵢ₌₁∑³⁰ (aᵢ + bᵢ), где" << endl
         << "𝑎𝑖={𝑖, если 𝑖 нечётное\t 𝑏𝑖={ 𝑖2, если 𝑖 нечётное\n    i/2, если 𝑖 чётное\t      𝑖3, если 𝑖 чётное " << RESET << endl    
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