# Qt Framework Comprehensive Study Guide

## Table of Contents
1. Course Context & Prerequisites
2. Qt Creator Environment
3. QObject Fundamentals
4. Signals and Slots System
5. Memory Management
6. Debugging & Development Tools
7. Best Practices & Common Pitfalls
8. Implementation Examples

## 1. Course Context & Prerequisites

### Level & Audience
- Intermediate level Qt programming
- Assumes basic C++ knowledge
- Prior Qt experience helpful but not required
- Can skip if already familiar with QObject

### Required Background
- C++ object-oriented programming
- Basic build system concepts
- Understanding of pointers and memory management
- Familiarity with IDEs

## 2. Qt Creator Environment

### IDE Overview
1. **Welcome Screen Features**
   - Examples browser with search functionality
   - Recent projects access
   - Documentation links
   - Tutorial access
   - Version selection capability

2. **Main Interface Components**
   - Edit mode for coding
   - Debug mode for testing
   - Projects mode for configuration
   - Help system (F1 access)
   - Terminal output options

### Project Configuration
1. **Application Types**
   ```cpp
   // Console Application
   int main(int argc, char *argv[]) {
       QApplication a(argc, argv);
       // Setup code
       return a.exec();
   }
   ```
   - Qt Widgets Application
   - Qt Console Application
   - Qt Quick Application
   - Library projects

2. **Build Systems**
   - CMake support
   - qmake support
   - Build configurations
   - Kit selection and management

## 3. QObject Fundamentals

### Core Concepts
1. **Base Class Properties**
   ```cpp
   class MyClass : public QObject {
       Q_OBJECT  // Required macro
   private:
       // Private members
   public:
       MyClass(QObject* parent = nullptr);
   };
   ```
   - Foundation of Qt framework
   - Provides object model
   - Enables signals and slots
   - Cannot be used with templates

2. **Meta-Object System**
   - Automatic code generation by MOC
   - Runtime type information
   - Property system support
   - Dynamic object features

### MOC (Meta-Object Compiler)
1. **Processing Steps**
   - Scans for Q_OBJECT macro
   - Generates meta-object code
   - Creates moc_*.cpp files
   - Enables runtime features

2. **Generated Files**
   - Located in build directory
   - Never modify manually
   - Contains meta-object information
   - Automatically included in build

## 4. Signals and Slots System

### Signal Declaration
```cpp
signals:
    void dataChanged(const QString& data);
    void statusUpdated(int status);
    void operationComplete();
```
- Always public
- Never implemented
- Declaration only
- Used with emit keyword

### Slot Implementation
```cpp
public slots:
    void handleData(const QString& data) {
        qInfo() << "Data received:" << data;
    }

private slots:
    void processStatus(int status) {
        qInfo() << "Status:" << status;
    }
```
- Can be public/private/protected
- Must be implemented
- Can be called directly
- Must match signal parameters

### Connection Types
```cpp
// Auto connection (default)
connect(&source, &Source::signal, &dest, &Dest::slot);

// Direct connection
connect(&source, &Source::signal, &dest, &Dest::slot,
        Qt::DirectConnection);

// Queued for thread safety
connect(&source, &Source::signal, &dest, &Dest::slot,
        Qt::QueuedConnection);
```

## 5. Memory Management

### Parent-Child System
```cpp
// Parent owns child
QObject* parent = new QObject();
QObject* child = new QObject(parent);  // Parent takes ownership

// Delete parent deletes children
delete parent;  // child also deleted
```

### Copy Prevention
```cpp
Test original;
// Test copy = original;  // Error: copying disabled
// Test copy(original);   // Error: copy constructor deleted
```

## 6. Debugging & Development

### Debug Output System
```cpp
qDebug() << "Debug info";
qInfo() << "Information";
qWarning() << "Warning message";
qCritical() << "Critical error";
qFatal() << "Fatal error";

// Object information
qInfo() << "Object:" << object->objectName()
        << "Address:" << object;
```

### Testing Tools
- Integrated debugger
- Output monitoring
- Signal spy
- Object inspection

## 7. Best Practices & Common Pitfalls

### Best Practices
1. **Signal-Slot Design**
   - Connect before emission
   - Match parameters exactly
   - Use appropriate connection type
   - Consider thread safety

2. **Memory Management**
   - Use parent-child relationships
   - Avoid raw pointers without parents
   - Clean up non-parented objects
   - Watch for cross-thread deletion

### Common Pitfalls
1. **Build Issues**
   - Missing Q_OBJECT macro
   - Incorrect MOC processing
   - Missing connections
   - Thread safety violations

2. **Runtime Issues**
   - Signal-slot mismatches
   - Memory leaks
   - Thread conflicts
   - Connection timing

## 8. Implementation Examples

### Basic QObject Usage
```cpp
class Test : public QObject {
    Q_OBJECT
public:
    Test(QObject* parent = nullptr) : QObject(parent) {
        qInfo() << "Constructed:" << objectName();
    }
    
    ~Test() {
        qInfo() << "Destroyed:" << objectName();
    }

signals:
    void statusChanged(const QString& status);

public slots:
    void handleStatus(const QString& status) {
        qInfo() << objectName() << "received:" << status;
    }
};

// Usage
int main() {
    Test parent;
    Test child;
    parent.setObjectName("Parent");
    child.setObjectName("Child");

    connect(&parent, &Test::statusChanged,
            &child, &Test::handleStatus);

    emit parent.statusChanged("Hello!");
    return 0;
}
```

### Thread-Safe Communication
```cpp
// Worker thread
class Worker : public QObject {
    Q_OBJECT
signals:
    void workComplete(const QString& result);
public slots:
    void doWork() {
        // Process
        emit workComplete("Done");
    }
};

// Main thread
Worker* worker = new Worker;
QThread* thread = new QThread;
worker->moveToThread(thread);

connect(thread, &QThread::started, worker, &Worker::doWork);
connect(worker, &Worker::workComplete, this, &MainWindow::handleResult,
        Qt::QueuedConnection);

thread->start();
```
