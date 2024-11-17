#ifndef TESTSTATICFUNCTIONS_H
#define TESTSTATICFUNCTIONS_H

#include <QObject>
#include <QDebug>

class testStaticFunctions : public QObject
{
    Q_OBJECT
public:
    explicit testStaticFunctions(QObject *parent = nullptr);

    void doStuff();
    static void doOtherStuff();
signals:
};

#endif // TESTSTATICFUNCTIONS_H
