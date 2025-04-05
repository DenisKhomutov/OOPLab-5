#include <iostream>
#include <stdio.h>
using namespace std;

class Figure {
protected:
    int x, y;
public:
    Figure() : x(0), y(0) {
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

    virtual string className() {
        return "Figure";
    }

    virtual bool isA(string clsName) {
        return clsName == className();
    }

    virtual void method1() {
        method2();
        cout << "\nFigure method1";
    }

    void virtual method2() {
        cout << "\nFigure method2()";
    }

    void virtual method3() {
        cout << "\nFigure method3()";
    }
};

class Circle : public Figure {
private:
    int radius;
public:
    Circle() {
        radius = 0;
        printf("\nКонструктор Circle по умолчанию: x = %d, y = %d, radius = %d", x, y, radius);
    }
    Circle(int rad): radius(rad) {
        printf("\nКонструктор Circle с параметрами: x = %d, y = %d, radius = %d", x, y, radius);
    }
    Circle(const Circle& circle) : Figure(circle), radius(circle.radius) {
        printf("\nКонструктор Circle копирования: x = %d, y = %d, radius = %d", x, y, radius);
    }
    ~Circle() {
        printf("\nДеструктор Circle");
    }

    virtual string className() override {
        return "Circle";
    }

    virtual bool isA(string clsName) override {
        return clsName == className() || Figure::isA(clsName);
    }

    void method2() override {
        cout << "\nCircle method2()";
    }

    void method3() {
        cout << "\nCircle method3()";
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    printf("----|Конструкторы|----");
    Figure f1;
    Figure f2 = Figure(1, 1);
    Figure f3 = Figure(f2);
    Circle c1;
    Circle c2(5);
    Circle c3 = c2;
    printf("\n\n----|Виртуальный деструктор|----");
    Figure* f = new Circle(50);
    delete f;
    printf("\n\n----|Методы|----");
    f1.method1();
    c1.method1();
    f1.method3();
    c1.method3();
    printf("\n\n----|Деструкторы|----");
}
