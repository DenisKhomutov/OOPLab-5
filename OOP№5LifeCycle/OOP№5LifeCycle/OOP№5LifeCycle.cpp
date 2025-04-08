#include <iostream>
#include <stdio.h>
using namespace std;

class Figure {
protected:
    int x, y;
public:
    Figure() : x(1), y(1) {
        printf("\nКонструктор Figure по умолчанию: x = %d, y = %d", x, y);
    }
    Figure(int x, int y) : x(x), y(y) {
        printf("\nКонструктор Figure с параметрами: x = %d, y = %d", x, y);
    }
    Figure(const Figure& fig) : x(fig.x), y(fig.y) {
        printf("\nКонструктор Figure копирования: x = %d, y = %d", x, y);
    }
    virtual ~Figure() {
        printf("\nДеструктор Figure");
    }
    void method1() {
        method2();
        printf("\nmethod 1 (Figure)");
    }
    virtual void method2() {
        printf("\nmethod 2 (Figure)");
    }
    virtual void methodTest() {
        printf("\nTest method (Figure)");
    }
    virtual void showArea() {
        printf("\nS = 0 (Figure)");
    }
    virtual string className() {
        return "Figure";
    }
    virtual bool isA(string clsName) {
        return clsName == className();
    }
};

class Circle : public Figure {
public:
    int radius;
public:
    Circle(): radius(5) {
        printf("\nКонструктор Circle по умолчанию: x = %d, y = %d, radius = %d", x, y, radius);
    }
    Circle(int rad) : radius(rad) {
        printf("\nКонструктор Circle с параметрами: x = %d, y = %d, radius = %d", x, y, radius);
    }
    Circle(const Circle& circle) : Figure(circle), radius(circle.radius) {
        printf("\nКонструктор Circle копирования: x = %d, y = %d, radius = %d", x, y, radius);
    }
    ~Circle() {
        printf("\nДеструктор Circle");
    }
    void method2() override {
        cout << "\nmethod 2 (Circle)";
    }
    void methodTest() {
        printf("\nTest method (Circle)");
    }
    void showArea() override {
        printf("\nS = %.1f (Circle)", 3.14*radius*radius);
    }
    string className() override {
        return "Circle";
    }
    bool isA(string clsName) override {
        if (clsName == className()) {
            return true;
        }
        return Figure::isA(clsName);
    }
};
int main() {
    setlocale(LC_ALL, "Russian");

    printf("\n    ----|Перекрываемые методы|----");
    Figure* f1 = new Figure();
    Circle* c1 = new Circle();
    printf("\n----");
    f1->showArea();
    c1->showArea();
    printf("\n\n    ----|Виртуальный деструктор|----");
    Figure* f = new Circle(10);
    delete f;

    printf("\n\n    ----|Методы|----");
    f1->method1();
    c1->method1();
    printf("\n----");
    f1->methodTest();
    c1->methodTest();
    
    printf("\n\n    ----|Принадлежность|----");
    printf("\nClassname of f1: %s", f1->className().c_str());
    printf("\nClassname of c1: %s", c1->className().c_str());
    printf("\n----");
    printf("\nisA Figure (is Figure - Fig?): %d", f1->isA("Fig"));
    printf("\nisA Figure (is Figure - Figure?): %d", f1->isA("Figure"));
    printf("\nisA Circle (is Circle - Figure?): %d", c1->isA("Figure"));
    printf("\nisA Circle (is Circle - Circle?): %d", c1->isA("Circle"));

    printf("\n\n    ----|Опасное приведение типов|----");
    Figure* testF = new Circle(10); // Указатель типа Figure testF указывает на объект класса Circle
    Circle* testC = (Circle*)testF; // Безопасно, если указатель testF действительно указывает на объект класса Circle
    printf("\n    Опасное приведение: radius = %d", testC->radius);
    delete testF;
    //delete testC; - Ошибка: testF и testC ссылаются на один и тот же объект, при попытке удалить testC освобождаем уже освобожденную память
    printf("\n----");
    Figure* testF1 = new Figure(5, 5); // Указатель типа Figure testF1 указывает на объект класса Figure
    Circle* testC1 = (Circle*)testF1;
    printf("\n    Опасное приведение (UB): radius = %d", testC1->radius); // Выведет мусор, т.к. объект класса Figure не имеет radius
    printf("\n\n    ----|Предварительная проверка типов|----");
    if (testC1->isA("Circle")) {
        printf("\n    Опасное приведение (с предварительной проверкой): radius = %d", testC1->radius);
    }
    else {
        printf("\n    Опасное приведение (с предварительной проверкой): not Circle");
    }
    delete testF1;

    printf("\n\n    ----|Использование стандартных средств языка (dynamic_cast)|----");
    Figure* fig1 = new Figure();
    Figure* fig2 = new Circle();
    Circle* cir1 = dynamic_cast <Circle*>(fig1);
    printf("\n----");
    printf("\n    Figure -> Circle");
    if (cir1) {
        printf("\n    Приведение с помощью dynamic_cast: radius = %d", cir1->radius);
    }
    else {
        printf("\n    not a Figure");
    }
    printf("\n----");
    printf("\n    Circle -> Circle");
    Circle* cir2 = dynamic_cast <Circle*>(fig2);
    if (cir2) {
        printf("\n    Приведение с помощью dynamic_cast: radius = %d", cir2->radius);
    }
    else {
        printf("\n    not a Figure");
    }
    printf("\n\n    ----|Деструкторы|----");
    delete f1;
    delete c1;
    delete fig1;
    delete fig2;
}
