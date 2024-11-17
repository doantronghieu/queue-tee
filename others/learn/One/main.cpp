#include <QCoreApplication>
#include <QDebug>
#include <array>
#include <iostream>
#include "animal.h"
#include "laptop.h"
#include "feline.h"
#include "canine.h"
#include "appliance.h"
#include "agecalc.h"
#include "teststaticfunctions.h"

using namespace std;

int Animal::count = 0;

void test() {
    qInfo("Hello from test");
}

int calc(int offset, int age) {
    if (offset == 0) qFatal("Offset can not be zero");

    if (age <= 0 || age > 120) {
        qFatal("Invalid age");
    }

    int x = offset * age;
    qInfo() << "Calc: " << x;
    return x;
}

int catYears(int age) {
    return calc(9, age);
}

int dogYears(int age) {
    return calc(7, age);
}

void testVal(int x) {
    // Passing by value - Copy - QObject do not like being copied.
    x = x * 10;
    qInfo() << "TestVal X: " << x;
}

void testRef(int &y) {
    // Passing by Reference
    y = y * 10; // Modify the original
    qInfo() << "TestVal Y: " << y;
}

QObject* get_ptr(QString name) {
    QObject *o = new QObject();
    o->setObjectName(name);
    return o;
}

void testLaptop(Laptop &machine) {
    machine.test();
}

void makeLaptops() {
    Laptop mine(nullptr, "My Laptop");
    Laptop yours(nullptr, "Your Laptop");

    mine.weight = 3;
    yours.weight = 5;

    testLaptop(mine);
    testLaptop(yours);
}

void printAges(AgeCalc &calc) {
    qInfo() << calc.name() << "Human Years: " << calc.humanYears();
    qInfo() << calc.name() << "Dog Years: " << calc.dogYears();
    qInfo() << calc.name() << "Cat Years: " << calc.catYears();
}



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

    // cerr << "Error";

    /*
    int age = 18;
    qInfo() << "Age: " << age;

    if (age == 0) qFatal("Not a valid age!");


    if (age < 18) {
        qInfo() << "You are NOT an adult";
    } else {
        qInfo() << "You are OLD!";
    }

    qInfo() << "Done!";
    */

    /*
    int age = 18;
    qInfo() << "Age: " << age;

    switch (age) {
    case 0:
        qFatal("You did not enter a valid age.");
        break;
    case 16:
        qInfo() << "You are NOT an adult";
        break;
    default:
        break;
    }
    */

    /*
    int start = 0;
    int i = start;
    while (i < 10) {
        qInfo() << i;
        i++;
    }
    */

    /*
    int max = 5;
    qInfo() << "Max: " << max;

    if (max <= 0) qFatal("Please enter a valid number.");

    for (int i = 0; i < max; i++) {
        qInfo() << i;
    }


    array<int, 4> numbers = { 1, 2, 3, 4 };
    for (int i = 0; i < numbers.size(); i++) {
        qInfo() << numbers.at(i);
    }
    */

    /*
    test();

    int age = 5;
    qInfo() << "Age: " << age;

    int value = calc(2, age);
    qInfo() << "Double: " << value;

    qInfo() << "Cat years: " << catYears(age);
    qInfo() << "Dog years: " << dogYears(age);
    */

    /*
    int x = 5;
    qInfo() << "Marin X: " << x;
    testVal(x); // COPY value
    qInfo() << "Main X: " << x;

    int y = 5;
    qInfo() << "Main Y: " << y;
    testRef(y); // Pass the original
    qInfo() << "Main Y: " << y;
    */

    /*
    QObject *o3 = get_ptr("ByPtr");
    qInfo() << o3->objectName();
    qInfo() << o3;
    delete o3;
    */

    /*
    Animal cat;
    Animal dog;
    Animal fish;

    cat.setObjectName("Kitty");
    dog.setObjectName("Fido");
    fish.setObjectName("FishStick");

    cat.speak("Meow");
    dog.speak("Bark");
    fish.speak("Fzzzz");
    */

    /*
    makeLaptops();
    */

    /*
    Canine dog;
    Feline cat;
    */

    /*
    Appliance machine3000;
    qInfo() << "Cook:" << machine3000.cook();
    qInfo() << "Freeze:" << machine3000.freeze();
    qInfo() << "Grill:" << machine3000.grill();
    */

    /*
    AgeCalc bryan;
    AgeCalc tommy;

    bryan.setName("Bryan");
    bryan.setAge(46);
    tommy.setName("Tommy");
    tommy.setAge(27);

    printAges(bryan);
    printAges(tommy);
    */

    /*
    Animal cat1;
    Animal cat2;
    Animal cat3;
    qInfo() << cat1.count;
    */

    /**/
    testStaticFunctions t;
    t.doStuff();
    t.doOtherStuff();
    testStaticFunctions::doOtherStuff();
    /**/
    /**/
    /**/

    return a.exec();
}

























