#include "appliance.h"

Appliance::Appliance(QObject *parent)
    : QObject{parent}
{
    qInfo() << this << "Constructed";
}


bool Appliance::cook()
{
    return true;
}

bool Appliance::grill()
{
    return true;
}

bool Appliance::freeze()
{
    return true;
}
