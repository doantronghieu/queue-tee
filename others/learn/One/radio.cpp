#include "radio.h"

Radio::Radio(QObject *parent)
    : QObject{parent}
{}

void Radio::listen(int channel, QString name, QString message)
{
    qInfo() << QString("Channel: %1, Name: %2 - %3").arg(channel).arg(name).arg(message);
}
