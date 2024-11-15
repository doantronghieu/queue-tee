#include <QCoreApplication>
#include <QDebug>
#include <array>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    // qInfo() << "Hello World";

    /*
    bool lightSwitch = false;
    qInfo() << "Is one: " << lightSwitch;

    lightSwitch = true;
    qInfo() << "Is one: " << lightSwitch;
    */

    /*
    int age = 44;
    double height = 6.02;
    qInfo() << "Age: " << age;
    qInfo() << "Height: " << height;

    signed int dogs = -1;
    qInfo() << "Dogs: " << dogs;
    dogs = 15;
    qInfo() << "Dogs: " << dogs;

    qInfo() << sizeof(dogs);
    */

    // const int id = 215;

    /*
    enum Color { red, green, blue };
    Color myColor = Color::blue;
    qInfo() << "Color: " << myColor;
    */

    /*
    enum Colors { black, red, green, blue };

    struct product {
        int weight;
        double value;
        Colors color;
    };

    product laptop;
    qInfo() << "Size: " << sizeof(laptop);

    laptop.color = Colors::green;
    laptop.value = 5678;
    laptop.weight = 3;
    qInfo() << "Value: " << laptop.value;
    */

    /*
    int ages[4] = { 1, 2, 3, 4 };
    qInfo() << ages[0];

    array<int, 5> cars;
    cars[2] = 99;
    qInfo() << cars[1];
    qInfo() << cars.size();
    qInfo() << sizeof(cars);
    */

    /*
    int x = 10;
    qInfo() << "x in (5, 20): " << (x > 5 && x < 20);
    */

    /*
    cout << "Hello" << endl;
    */

    /*
    int age = 0;
    qInfo() << "Enter an age: ";
    cin >> age;
    qInfo() << "Age: " << age;
    */

    cerr << "Error";


    return a.exec();
}

























