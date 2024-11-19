# C++ Scoping Concepts Study Notes

## 1. Fundamental Understanding of Scope

### Basic Definition
- Scope is simply variable access at the current scope and parent scope
- Determines where variables "live" and can be accessed
- Primary purpose: Avoid naming collisions and protect data
- C++ uses lexical (static) scoping by design

### Scope Hierarchy (Top-down)
1. Global Scope (Application-wide)
2. Namespace Scope
3. Class Scope
4. Function Scope
5. Block Scope (if, while, for, etc.)

## 2. Lexical vs Dynamic Scoping

### Lexical (Static) Scoping in C++
```cpp
int x = 10;  // Global scope

void f() { 
    return x;  // Returns 10 due to lexical scope
}

void g() {
    int x = 20;
    f();      // Still returns 10, not 20
}
```

### Dynamic Scoping (Not used in C++)
- Would use most recent value in call stack
- More unpredictable behavior
- Harder to track variable values
- Example shows why C++ chose lexical scoping

## 3. Memory and Variable Identity

### Address Verification
```cpp
void demonstrateScope() {
    int globalVar = 75;
    {
        int globalVar = 50;  // Different variable
        cout << "&globalVar (block): " << &globalVar << endl;
    }
    cout << "&globalVar (function): " << &globalVar << endl;
    // Shows different memory addresses
}
```

### Variable Independence
- Each scope creates new storage for variables
- Same names in different scopes = different variables
- Use & operator to verify different memory locations
- Important for understanding variable lifetime

## 4. Class Scope Fundamentals

### Instance Independence
```cpp
class Animal {
public:
    QString name;
    Animal(QString n) : name(n) {}
};

void scopeExample() {
    Animal cat(nullptr, "Lucky");
    Animal dog(nullptr, "Fido");
    // Each has independent name storage
    qDebug() << &cat.name << &dog.name;  // Different addresses
}
```

### Name Resolution with 'this'
```cpp
class Animal {
    QString name;
    Animal(QString name) {
        this->name = name;  // Clear member reference
        // Without this: name = name would be unclear
    }
};
```

## 5. Static Members and Functions

### Static Variables
```cpp
class Counter {
    static int instances;
public:
    Counter() { ++instances; }
    ~Counter() { --instances; }
    static int getCount() { return instances; }
};
int Counter::instances = 0;  // Required initialization
```

### Static Function Constraints
```cpp
class Test {
    QString name;
    static void staticFunc() {
        // ERROR: Cannot use 'this'
        // ERROR: Cannot access non-static 'name'
        // OK: Can access other static members
    }
};
```

## 6. Block Scope Details

### Variable Shadowing
```cpp
int x = 10;  // Global

void function() {
    int x = 20;  // Shadows global
    {
        int x = 30;  // Shadows function scope
        cout << x;     // 30
        cout << ::x;   // 10 (global)
    }
    cout << x;       // 20
}
```

### Scope Lifetime
```cpp
void scopeExample() {
    {
        QString temp = "hello";  // Created
    }  // temp destroyed here

    if (true) {
        Animal cat;  // Created
    }  // cat destroyed here
}
```

## 7. Namespace Organization

### Purpose and Usage
```cpp
namespace ProjectA {
    class Database {};
}

namespace ProjectB {
    class Database {};  // No collision
}

void example() {
    ProjectA::Database db1;
    ProjectB::Database db2;  // Clear which is which
}
```

## 8. Global Scope and Threading

### Thread Safety Issues
```cpp
// DANGEROUS: Global state
int globalCounter = 0;

// Thread 1
void thread1() {
    globalCounter++;  // Race condition
}

// Thread 2
void thread2() {
    globalCounter++;  // Race condition
}
```

### Safe Alternative
```cpp
class ThreadSafeCounter {
    int count;
    mutex mtx;
public:
    void increment() {
        lock_guard<mutex> lock(mtx);
        count++;
    }
};
```

## 9. Best Practices

### Variable Declaration
1. Declare at lowest necessary scope
2. Initialize at declaration when possible
3. Avoid global variables
4. Use namespaces for organization
5. Be careful with static members

### Scope Management
1. Keep scopes small and focused
2. Use classes for encapsulation
3. Pass parameters instead of using globals
4. Document static members
5. Consider threading implications

### Debugging Approach
1. Check variable addresses to verify scope
2. Watch for naming conflicts
3. Monitor static member usage
4. Test with multiple threads
5. Use IDE scope highlighting

## 10. Common Pitfalls to Avoid

### Design Issues
1. Global variable overuse
2. Unintended variable shadowing
3. Static member initialization issues
4. Scope lifetime misunderstandings
5. Threading problems with shared state

### Code Issues
1. Missing static member initialization
2. Accessing destroyed variables
3. Name collisions in global scope
4. Confusion with 'this' pointer
5. Improper scope resolution

### Memory Management
1. Returning references to local variables
2. Accessing out-of-scope variables
3. Memory leaks from improper cleanup
4. Dangling pointers across scopes
5. Static initialization order problems