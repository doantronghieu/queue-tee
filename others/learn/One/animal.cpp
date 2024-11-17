#include "animal.h"

Animal::Animal(QObject *parent)
    : QObject{parent}
{
    count++;
    qInfo() << this << "Constructed";
}

Animal::~Animal()
{
    count--;
    qInfo() << this << "Deconstructed";
}

void Animal::speak(QString message)
{
    qInfo() << this << message;
}
