#ifndef TESTQPROPERTY_H
#define TESTQPROPERTY_H

#include <QObject>
#include <QDebug>
#include <QTimer>

class TestQProperty : public QObject
{
    Q_OBJECT
    QString m_message;
public:
    explicit TestQProperty(QObject *parent = nullptr);

    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged FINAL)

    QString message() const;
    void setMessage(const QString &newMessage);

signals:
    void messageChanged(QString message);

public slots:
    void timeout();

private:
    QTimer m_timer;
};

#endif // TESTQPROPERTY_H
