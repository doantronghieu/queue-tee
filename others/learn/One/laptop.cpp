#include "laptop.h"

Laptop::Laptop(QObject *parent, QString name)
    : QObject{parent}
{
    this->name = name;
    qInfo() << this << "Constructor" << name;
}

Laptop::~Laptop()
{
    qInfo() << this << "Deconstructor" << name;
}

double Laptop::asKilo()
{
    return this->weight * 0.453592;
}

void Laptop::test()
{
    qInfo() << this << "Test: " << name << " Kilo: " << asKilo();
}
