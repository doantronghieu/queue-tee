# Qt Signals and Slots - Ultimate Study Guide

## 1. Fundamental Concepts

### What Makes Qt Special
- Signals and slots are Qt's defining feature
- Unmatched functionality compared to other frameworks
- Simple yet powerful implementation
- Built into Qt's core through QObject base class

### Basic Architecture
- Based on Qt's meta-object system
- Requires QObject inheritance
- Uses Meta-Object Compiler (MOC)
- Enables object-to-object communication without tight coupling

## 2. Core Components

### Signals
```cpp
class Source : public QObject {
signals:
    void mySignal(const QString &message);  // No implementation needed
    
public:
    void test() {
        emit mySignal("Hello World");  // Emitting the signal
    }
};
```
Key Points:
- Never implemented (just declared)
- Automatically handled by MOC
- Always public
- Must use 'emit' keyword to send
- Can't be called directly
- Function-like prototypes

### Slots
```cpp
class Destination : public QObject {
public slots:
    void mySlot(const QString &message) {
        qInfo() << message;  // Must be implemented
    }
};
```
Key Points:
- Regular C++ functions with special connection capability
- Must be implemented
- Can be public/private/protected
- Can be called directly or through signals
- Function implementation required

## 3. Connection System

### Basic Connection Syntax
```cpp
QObject::connect(
    sourceObject,      // Source pointer
    &Source::signal,   // Signal address
    destinationObject, // Destination pointer
    &Dest::slot,       // Slot address
    connectionType     // Optional connection type
);
```

### Connection Types
1. Qt::AutoConnection (Default)
   - Qt chooses appropriate type
   - May not be optimal for all cases

2. Qt::DirectConnection
   - Immediate execution
   - Same thread calls

3. Qt::QueuedConnection
   - Thread-safe communication
   - Uses event queue

4. Qt::BlockingQueuedConnection
   - Blocks until slot completes

5. Qt::UniqueConnection
   - Prevents duplicate connections
   ```cpp
   QObject::connect(&source, &Source::signal, &dest, &Dest::slot, 
                   Qt::UniqueConnection);
   ```

## 4. Property System

### Basic Property Definition
```cpp
class MyClass : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString message 
               READ message 
               WRITE setMessage 
               NOTIFY messageChanged)
private:
    QString m_message;
public:
    QString message() const { return m_message; }
    void setMessage(const QString &msg) {
        if (m_message != msg) {
            m_message = msg;
            emit messageChanged(msg);
        }
    }
signals:
    void messageChanged(const QString &msg);
};
```

### Property Usage
```cpp
// Direct property access
myObject->setProperty("message", QVariant("Hello"));

// Through setter
myObject->setMessage("Hello");
```

## 5. Practical Examples

### Timer Implementation
```cpp
class TimerExample : public QObject {
private:
    QTimer timer;
    int count = 0;

public:
    TimerExample() {
        connect(&timer, &QTimer::timeout, this, &TimerExample::onTimeout);
        timer.setInterval(1000);  // 1 second
        timer.start();
    }

public slots:
    void onTimeout() {
        qInfo() << "Timer fired:" << count++;
        if (count >= 3) {
            timer.stop();
            qInfo() << "Timer complete";
        }
    }
};
```

### Radio-Station Communication
```cpp
class Station : public QObject {
private:
    int channel;
    QString name;

public:
    Station(QObject* parent = nullptr) 
        : QObject(parent), channel(0), name("unknown") {}
    
    void broadcast(const QString& message) {
        emit send(channel, name, message);
    }

signals:
    void send(int channel, const QString &name, const QString &message);
};

class Radio : public QObject {
public slots:
    void listen(int channel, const QString &name, const QString &message) {
        qInfo() << "Channel:" << channel << "Station:" << name 
                << "Message:" << message;
    }
};
```

### Multiple Connections Example
```cpp
class Owner : public QObject {
signals:
    void treats();
public:
    void giveSnacks() {
        qInfo() << "Snacks ready!";
        emit treats();
    }
};

class Dog : public QObject {
public slots:
    void treatsAvailable() {
        qInfo() << "Bark!";
    }
};
```

## 6. Memory Management

### Parent-Child System
- Parents automatically delete children
- Use parent parameter in constructors
```cpp
Station* station = new Station(parentObject);  // Auto cleanup
```

### Connection Cleanup
- Connections auto-cleanup when objects are destroyed
- Manual cleanup possible with disconnect()
- Parent deletion handles child connections

## 7. Best Practices

### Design Guidelines
1. Keep signals and slots loosely coupled
2. Use appropriate connection types
3. Consider thread safety
4. Document signal-slot relationships
5. Use parent-child memory management
6. Implement proper cleanup
7. Test connection behavior thoroughly

### Common Pitfalls
1. Multiple connection issues
2. Thread safety problems
3. Memory leaks
4. Signal emission in constructors
5. Missing parent-child relationships
6. Wrong connection types

## 8. Debugging Tips

### Connection Issues
- Verify connection success
- Check for multiple connections
- Monitor signal emissions
- Test across threads
- Verify property bindings
- Check parent-child relationships

### Performance Considerations
- Monitor connection counts
- Watch for excessive signal emissions
- Consider connection types impact
- Profile signal-slot overhead

## 9. Advanced Features

### Thread Safety
- Use Qt::QueuedConnection for cross-thread
- Avoid DirectConnection across threads
- Consider BlockingQueuedConnection when needed

### Custom Connections
- Combine connection types
- Create custom connection patterns
- Use unique connections when appropriate

### QML Integration
- Use property system
- Implement proper bindings
- Consider QVariant usage
- Handle property notifications

## 10. Key Advantages

### Over Traditional Methods
1. Cleaner than callbacks
2. Type-safe connections
3. Thread-safe when properly used
4. Dynamic connection management
5. Automatic memory management
6. Cross-thread communication
7. Integration with Qt's property system

### Maintainability Benefits
1. Loose coupling
2. Clear communication patterns
3. Easy debugging
4. Proven technology
5. Stable API
6. Comprehensive documentation