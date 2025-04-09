#include <iostream>
#include <stdio.h>
using namespace std;

class Base {
public:
	int a;
public:
	Base(): a(10) {
		printf("\nBase()");
	}
	Base(Base* obj): a(obj->a){
		printf("\nBase(Base* obj)");
	}
	Base(Base& obj): a(obj.a){
		printf("\nBase(Base& obj)");
	}
	virtual ~Base() {
		printf("\n~Base()");
	}
	Base(const Base& obj): a(obj.a) {
		printf("\nBase(const Base& obj)");
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

Base rfunc1() {
	Base base;
	return base;
}

Base* rfunc2() { // Неопр. пов.
	Base base;
	return &base;
}

Base& rfunc3() { // Неопр. пов.
	Base base;
	return base;
}

Base rfunc4() {
	Base* base = new Base();
	return  *base;
}
Base* rfunc5() {
	Base* base = new Base();
	return base;
}
Base& rfunc6() {
	Base* base = new Base();
	return *base;
}

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

	printf("\n\n    ----|Создание и возвращение статических объектов|----");
	Base base1 = rfunc1();
	printf("\na of base1 = %d", base1.a);
	printf("\n----");
	Base* base2 = rfunc2(); // Неопр. пов. возвращается указатель на уже уничтоженный объект
	printf("\na of base2 = %d", base2->a); 
	printf("\n----");
	Base base3 = rfunc3(); // Неопр. пов. + попытка создать объект, копируя его из недействительной ссылки, которая ссылается на уже удаленный объект
	printf("\na of base3 = %d", base3.a);
	printf("\n----");
	printf("\na of base1 = %d", base1.a);
	printf("\na of base2 = %d", base2->a);
	printf("\na of base3 = %d", base3.a);

	printf("\n\n    ----|Создание и возвращение динамических объектов|----");
	Base base4 = rfunc4();
	printf("\n----");
	Base* base5 = rfunc5();
	printf("\n----");
	Base& base6 = rfunc6();
	printf("\n----");
	printf("\na of base4 = %d", base4.a);
	printf("\na of base5 = %d", base5->a);
	printf("\na of base6 = %d", base6.a);
	delete base5;

	printf("\n\n    ----|Использование умных указателей|----");
	unique_ptr<Base> uniqueBase1 = make_unique<Base>();
	//unique_ptr<Base> uniqueBase2 = uniqueBase1;
	printf("\na of uniqueBase1 = %d", uniqueBase1->a);
	unique_ptr<Base> uniqueBase2 = move(uniqueBase1);
	printf("\nПосле перемещения:");
	printf("\nuniqueBase2: a = %d", uniqueBase2->a);
	if (uniqueBase1) printf("\n uniqueBase1 существует");
	else printf("\nuniqueBase1 пуст\n");

	shared_ptr<Base> sharedBase1 = make_unique<Base>();
	printf("\sharedBase1: a = %d (использований: %d)", sharedBase1->a, sharedBase1.use_count());
	shared_ptr<Base> sharedBase2 = sharedBase1;
	printf("\n    После копирования:");
	printf("\nsharedBase1 использований: %d", sharedBase1.use_count());
	printf("\nsharedBase2 использований: %d", sharedBase2.use_count());

	{
		shared_ptr<Base> sharedBase3 = sharedBase1;
		printf("\n    Внутри блока: использований = %d", sharedBase1.use_count());
	}
	printf("\n    После блока: использований = %d", sharedBase1.use_count());

	sharedBase1.reset();
	sharedBase2.reset();
	printf("\n    После reset: использований = %d", sharedBase2.use_count());

	printf("\n\n   Деструкторы: ");
}
