# Comprehensive Qt Container Classes Study Guide

## Overview
Qt provides several container classes for different use cases. Each container is optimized for specific operations and has unique characteristics. This guide covers all major container classes, their usage patterns, and important considerations.

## 1. QList - Core Sequential Container
### Basic Characteristics
- Template class without QObject inheritance (no signals/slots)
- Implements a dynamic array internally
- Maintains insertion order
- Most commonly used Qt container

### Core Operations
```cpp
QList<int> list;
list.append(1);        // Add single item
list.append(2);        // Add another
list.size();          // Number of items
list.count();         // Same as size()
list.length();        // Same as size() (kept for legacy)
list.count(value);    // Count occurrences of value
```

### Key Methods
```cpp
list.replace(2, 99);   // Replace at index
list.removeAll(3);     // Remove all 3s
list.remove(3);        // Remove first 3
list.clear();          // Remove everything
list.slice(2, 3);      // Get subset
list.contains(4);      // Check existence
list.indexOf(4);       // Get position (-1 if not found)
list.at(index);        // Safe access (preferred over [])
```

### Important Notes
- Provides index-based access
- Maintains order of elements
- Efficient for sequential access
- Use at() for safer element access

## 2. QVector - Qt 6 Changes
### Key Points
- Now just an alias for QList in Qt 6
- Identical functionality to QList
- Kept for Qt 5 compatibility
- Example:
  ```cpp
  QVector<int> vec;  // Exactly same as QList<int>
  vec.append(1);     // All QList operations work identically
  ```

## 3. QSet - Fast Lookup Container
### Core Characteristics
- Hash table-based implementation
- Optimized for extremely fast lookups
- Unordered storage
- No duplicates allowed

### Usage Example
```cpp
QSet<QString> set;
set.insert("value1");   // Add items
set.insert("value2");   // Order not guaranteed
bool has = set.contains("value1");  // Very fast lookup
```

### Important Notes
- Best choice for frequent containment checks
- Order is implementation-defined
- May change order between runs
- Uses QHash internally

## 4. QMap - Key-Value Container
### Core Characteristics
- Ordered key-value pairs
- Unique keys
- Automatic sorting by key
- Fast key-based lookups

### Basic Operations
```cpp
QMap<QString, int> map;
map.insert("key1", 100);       // Basic insertion
map["key2"] = 200;            // Alternative insertion
int val = map.value("key1");  // Safe access
bool has = map.contains("key1");  // Check existence

// Important behavior
map["newkey"] = 300;  // Creates entry if doesn't exist
int safe = map.value("missing", -1);  // With default value
```

### Special Features
- Access all keys: `map.keys()`
- Access all values: `map.values()`
- Automatic entry creation with operator[]
- Safe access with value() method

## 5. QStringList - Specialized String Container
### Core Features
- Inherits from QList<QString>
- Additional string-specific operations
- Built for text processing

### String Operations
```cpp
QStringList names;
names << "Brian" << "Heather" << "Rango";

// String manipulations
names.replaceInStrings("a", "@");  // Replace in all
names.filter("r");                 // Filter containing 'r'
names.sort(Qt::CaseSensitive);     // Sort with case sensitivity
QString combined = names.join(","); // Combine with separator
```

### Use Cases
- File path handling
- Command-line argument processing
- Text processing
- Configuration data

## 6. Memory Management
### Raw Pointer Management (qDeleteAll)
```cpp
QList<Test*> list;
list.append(new Test());

// Cleanup process
qDeleteAll(list);   // Delete objects
list.clear();       // MUST clear after!

// DANGER: Don't do this
// list[0]->someMethod();  // Crash! (after qDeleteAll)
```

### Smart Pointer Usage (Recommended)
```cpp
QList<QSharedPointer<Test>> list;
list.append(QSharedPointer<Test>(new Test()));
// No manual cleanup needed
```

### Production Best Practice
```cpp
// Complex container typedef
typedef QMap<QString, QSharedPointer<Test>> TestMap;
TestMap map;  // Cleaner syntax
```

## Best Practices for Production
1. Container Selection:
   - Default to QList for sequences
   - Use QSet for membership testing
   - Choose QMap for key-value needs
   - Prefer QStringList for string collections

2. Memory Management:
   - Prefer smart pointers in production code
   - Always clear after qDeleteAll if using raw pointers
   - Use consistent typedef naming across team

3. Performance Considerations:
   - Use QSet for frequent lookups
   - Consider QMap when key-based access is needed
   - Remember QStringList's specialized string operations

## Common Pitfalls
1. Memory Management:
   - Accessing items after qDeleteAll
   - Not clearing container after qDeleteAll
   - Memory leaks with raw pointers

2. Container Behavior:
   - Assuming QSet maintains order
   - Forgetting QMap[] creates entries
   - Expecting remove() to remove all instances

3. API Usage:
   - Using [] instead of at() for QList access
   - Not providing defaults for QMap::value()
   - Misunderstanding QVector/QList equivalence in Qt 6

## Additional Notes
- QVector to QList transition in Qt 6 resolves historical debates
- Smart pointers are strongly recommended for production code
- Container choice significantly impacts performance
- Type safety is enforced by template system
- Consider memory management strategy early in design

Remember: These containers are fundamental Qt tools - choosing the right one for your use case is crucial for both performance and maintainability.