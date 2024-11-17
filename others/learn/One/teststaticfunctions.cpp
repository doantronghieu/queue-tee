#include "teststaticfunctions.h"

testStaticFunctions::testStaticFunctions(QObject *parent)
    : QObject{parent}
{}

void testStaticFunctions::doStuff()
{
    qInfo() << this << "doStuff";
    testStaticFunctions::doOtherStuff();
}

void testStaticFunctions::doOtherStuff()
{
    qInfo() << "doOtherStuff";
}

