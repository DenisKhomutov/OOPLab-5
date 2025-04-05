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

    virtual void method2() {
        cout << "\nFigure method2()";
    }

    virtual void method3() {
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

    string className() override {
        return "Circle";
    }

    bool isA(string clsName) override {
        if (clsName == className()) {
            return true;
        }
        return Figure::isA(clsName);
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
    printf("     ----|Конструкторы|----");
    Figure f1;
    Figure f2 = Figure(1, 1);
    Figure f3 = Figure(f2);
    Circle c1;
    Circle c2(5);
    Circle c3 = c2;
    printf("\n\n    ----|Виртуальный деструктор|----");
    Figure* f = new Circle(50);
    delete f;
    printf("\n\n    ----|Методы|----");
    printf("\n----");
    f1.method1();
    printf("\n----");
    c1.method1();
    printf("\n----");
    f1.method3();
    printf("\n----");
    c1.method3();
    printf("\n----");
    printf("\n\n    ----|Принадлежность|----");
    printf("\nclassName Figure: %s", f1.className().c_str());
    printf("\nclassName Circle: %s", c1.className().c_str());
    printf("\nisA Figure (is Figure - Fig?): %d", f1.isA("Fig"));
    printf("\nisA Figure (is Figure - Figure?): %d", f1.isA("Figure"));
    printf("\nisA Circle (is Circle - Figure?): %d", c1.isA("Figure"));
    printf("\nisA Circle (is Circle - Circle?): %d", c1.isA("Circle"));
    printf("\n\n    ----|Приведение типов|----");

    printf("\n\n    ----|Деструкторы|----");
}
