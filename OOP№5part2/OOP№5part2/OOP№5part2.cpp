#include <iostream>
#include <stdio.h>
using namespace std;

class Base {
public:
	Base() {
		printf("\nBase()");
	}
	Base(Base* obj) {
		printf("\nBase(Base* obj)");
	}
	Base(Base& obj) {
		printf("\nBase(Base& obj)");
	}
	virtual ~Base() {
		printf("\n~Base()");
	}
};
class Desc : public Base {
public:
	Desc() {
		printf("\nDesc()");
	}
	Desc(Desc* obj) {
		printf("\nDesc(Desc* obj)");
	}
	Desc(Desc& obj) {
		printf("\nDesc(Desc& obj)");
	}
	~Desc() {
		printf("\n~Desc()");
	}
};

void func1(Base obj) {

};
void func2(Base* obj) {
	Desc* newdesc = dynamic_cast<Desc*>(obj);
	if (newdesc) {
		printf("\nОбъект класса Desc");
	}
	else {
		printf("\nОбъект другого класса");
	}
};
void func3(Base& obj) {

};

int main() {
	setlocale(LC_ALL, "Russian");
	printf("\n    ----|Передача объектов|----");
	printf("\n   Конструктор Base: ");
	Base base;
	printf("\n   Функция func1: ");
	func1(base);
	printf("\n----");
	printf("\n   Функция func2: ");
	func2(&base);
	printf("\n----");
	printf("\n   Функция func3: ");
	func3(base);

	printf("\n\n   Конструктор Desc: ");
	Desc desc;
	printf("\n   Функция func1: ");
	func1(desc);
	printf("\n----");
	printf("\n   Функция func2: ");
	func2(&desc);
	printf("\n----");
	printf("\n   Функция func3: ");
	func3(desc);
	printf("\n\n   Деструкторы: ");
}
