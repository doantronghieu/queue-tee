#include "testqproperty.h"

TestQProperty::TestQProperty(QObject *parent)
    : QObject{parent}
{
    connect(&m_timer, &QTimer::timeout, this, &TestQProperty::timeout);
    m_timer.setInterval(1000);
    m_timer.start();
    // m_timer.stop();
}

QString TestQProperty::message() const
{
    return m_message;
}

void TestQProperty::setMessage(const QString &newMessage)
{
    m_message = newMessage;
    emit messageChanged(m_message);
}

void TestQProperty::timeout()
{
    qInfo() << "Test!";
}
