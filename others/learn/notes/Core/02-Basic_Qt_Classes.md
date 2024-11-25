# Comprehensive Qt Framework Study Notes

## 1. Qt Objects (QObject)

### 1.1 Core Concepts
- QObject is the base class for most Qt classes
- Exceptions: template classes, Qt string, and a few utility classes
- Key characteristics:
  - Cannot be copied (copy constructor disabled)
  - Cannot be moved
  - Supports signals and slots mechanism
  - Requires Q_OBJECT macro
  - Supports parent-child relationships

### 1.2 Class Structure
```cpp
class MyClass : public QObject {
    Q_OBJECT  // Required macro for Qt features

private:    // Private section (default)
    int someVar;

public:     // Public section
    MyClass(QObject *parent = nullptr);

signals:    // Signals section (automatically public)
    void someSignal();

public slots:  // Public slots section
    void someSlot();

private slots: // Private slots section
    void internalSlot();
};
```

### 1.3 Signals and Slots
- Signals: Events emitted by objects
  - No implementation needed (defined by moc)
  - Can be emitted from inside or outside QObject
  - Can carry data as parameters

- Slots: Functions that respond to signals
  - Regular functions with special marking
  - Can be called directly like normal functions
  - Can check sender() to verify signal source

```cpp
// Signal-Slot Connection Examples
QObject::connect(dog, &Dog::bark, cat, &Cat::scared);
QObject::connect(cat, &Cat::run, dog, &Dog::chase);

// Connection types
QObject::connect(dog, &Dog::bark, cat, &Cat::scared, Qt::AutoConnection); // Default for same thread

// Emitting signals
emit bark();                // From within QObject
emit dog->bark();          // From outside (e.g., main function)
```

### 1.4 Object Names and Debugging
```cpp
// Set object name
object->setObjectName("MainWindow");

// Access name in debug
qDebug() << "Object:" << object->objectName();

// Sender checking in slots
void MyClass::mySlot() {
    if (QObject* s = sender()) {
        qDebug() << "Signal from:" << s->objectName();
    }
}
```

### 1.5 Meta-Object System
- Handled by Meta-Object Compiler (moc)
- Creates additional code for:
  - Signal/slot mechanism
  - Runtime type information (RTTI)
  - Dynamic property system
- Generated files: moc_classname.cpp
- Enables dynamic features at runtime

## 2. Qt Data Types

### 2.1 Basic Integer Types
- Platform-independent integers:
  ```cpp
  qint8   // 8-bit integer
  qint16  // 16-bit integer
  qint32  // 32-bit integer
  qint64  // 64-bit integer
  qintptr // Pointer-sized integer
  ```

### 2.2 QString
- Universal string class
- Features:
  - UTF-8 support built-in
  - Rich manipulation methods
  - Implicit sharing
  - Can be copied

```cpp
QString str = "Hello World";

// Basic Operations
str.mid(1, 3);              // Extract substring "ell"
str.insert(0, "Mr. ");      // Insert at position
str.split(" ");             // Split into QStringList
str.contains("Hello");      // Check content
str.indexOf(".");          // Find position
str.remove(0, 4);          // Remove characters
str.trimmed();             // Remove whitespace

// Advanced Operations
str.simplified();          // Remove extra whitespace
str.replace("Hello", "Hi");
str.toLower();            // Convert case
str.toUpper();

// Conversions
QString::number(42);       // Number to string
str.toInt();              // String to number
```

### 2.3 QByteArray
- Universal binary data handler
- Features:
  - Buffer operations
  - Data conversion
  - Encoding/decoding

```cpp
QByteArray buffer;

// Basic Operations
buffer.append("Data");
buffer.prepend("Start");
buffer.insert(5, "Middle");

// Buffer Management
buffer.reserve(1000);     // Pre-allocate
buffer.resize(500);       // Resize
buffer.fill('x', 100);    // Fill

// Encoding
buffer.toBase64();        // Base64 encode
buffer.toHex();          // Hex encode

// Raw Data Access
const char* data = buffer.constData();
char* rawData = buffer.data();
```

## 3. Qt Containers

### 3.1 QList
- Primary container class
- Template-based
- Dynamic size management
- Features:
  - Index-based access
  - Iterator support
  - Rich set of operations

```cpp
QList<int> numbers = {1, 2, 3};
numbers.append(4);
numbers.prepend(0);
numbers.removeAt(0);
```

### 3.2 QStringList
- Specialized string container
- Inherits from QList<QString>
- Additional string operations

```cpp
QStringList list = QString("Hello world").split(" ");
list.sort(Qt::CaseInsensitive);
list.filter("H");         // Filter strings
list.join(" ");          // Join with separator
```

### 3.3 QMap
- Key-value container
- Ordered by key
- Unique keys

```cpp
QMap<QString, int> map;

// Basic Operations
map.insert("one", 1);
map.value("one", -1);     // With default value
map.contains("one");

// Iteration
for(auto it = map.begin(); it != map.end(); ++it) {
    qDebug() << it.key() << it.value();
}

// Memory Management with Pointers
QMap<QString, QObject*> objectMap;
qDeleteAll(objectMap.values());
objectMap.clear();
```

## 4. Date and Time

### 4.1 QDate, QTime, QDateTime
```cpp
// Date Operations
QDate date = QDate::currentDate();
date = date.addDays(1);
date = date.addYears(1);

// Time Operations
QTime time = QTime::currentTime();
time = time.addSecs(3600);  // Add 1 hour

// DateTime
QDateTime dt = QDateTime::currentDateTime();
dt = dt.addDays(45);

// Formatting
QString isoDate = date.toString(Qt::ISODate);
QString textDate = date.toString(Qt::TextDate);
QString customFormat = dt.toString("yyyy-MM-dd hh:mm:ss");
```

## 5. QVariant

### 5.1 Core Features
- Type-safe union
- Universal data container
- Automatic type conversion

```cpp
QVariant var = 42;
QVariant var2 = "Hello";

// Type Checking
if (var.type() == QVariant::Int) {
    int num = var.toInt();
}

// Safe Conversion
bool ok;
int num = var.toInt(&ok);
if (ok) {
    // Conversion successful
}
```

## 6. Best Practices

1. Memory Management
   - Use parent-child relationships
   - Clean up manual allocations
   - Clear containers after qDeleteAll
   - Check pointers before use

2. Container Usage
   - Prefer QList in Qt 6
   - Use appropriate container for use case
   - Consider performance implications

3. String Handling
   - Use QString for text
   - QByteArray for binary data
   - Consider UTF-8 encoding

4. Signal-Slot
   - Connect to appropriate thread type
   - Check sender() when needed
   - Use type-safe signal-slot syntax

5. Error Handling
   - Check return values
   - Validate conversions
   - Handle invalid dates/times
   - Verify pointer validity
