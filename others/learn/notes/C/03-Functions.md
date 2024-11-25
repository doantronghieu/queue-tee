# C++ Functions Study Notes

## 1. Understanding Function Scope & Declaration Order

### Compilation Order Fundamentals
```cpp
// WRONG - Won't compile
int main() {
    test();  // Error: test not declared yet
}

void test() {
    cout << "Hello";
}

// CORRECT
void test() {
    cout << "Hello";
}

int main() {
    test();  // Works: test declared before use
}
```

### Function Independence
- Functions are "independent islands" of code
- Each function has its own scope (isolated block)
- Variables inside function are local to that function
- Functions can only "see" what's defined before them

### Scope Visualization
```cpp
void functionA() {
    int x = 5;  // Only exists in functionA
}

void functionB() {
    // Cannot see or use x from functionA
    int x = 10;  // Different x, local to functionB
}
```

## 2. Memory Concepts

### Memory Types
1. Stack Memory:
   - Automatic management
   - Local variables & function parameters
   - Limited size but faster
   - Automatically cleaned up

2. Heap Memory:
   - Manual management (new/delete)
   - Larger size available
   - Must be explicitly cleaned up
   - Used for dynamic allocation

### Pointers vs References
- Pointer Analogy: Like a web browser bookmark
  - Bookmark doesn't contain the website
  - Just stores the address/location
  - Can be null/empty
  ```cpp
  int* ptr = &value;  // Stores address of value
  ```

- Reference Analogy: Like a nickname
  - Always refers to original variable
  - Can't be null
  - Must be initialized
  ```cpp
  int& ref = value;  // Another name for value
  ```

## 3. Function Parameters

### By Value
```cpp
void modifyValue(int x) {
    x = x * 2;  // Original unchanged
    cout << "Inside: " << x << endl;
}

int main() {
    int num = 5;
    modifyValue(num);
    cout << "Outside: " << num << endl;  // Still 5
}
```

### By Reference
```cpp
void modifyReference(int& x) {
    x = x * 2;  // Original changed
    cout << "Inside: " << x << endl;
}

int main() {
    int num = 5;
    modifyReference(num);
    cout << "Outside: " << num << endl;  // Now 10
}
```

### By Pointer
```cpp
void modifyPointer(int* x) {
    if (x != nullptr) {
        *x = *x * 2;  // Original changed
        cout << "Inside: " << *x << endl;
    }
}

int main() {
    int num = 5;
    modifyPointer(&num);
    cout << "Outside: " << num << endl;  // Now 10
}
```

## 4. Evolution of Calculator Example

### Stage 1: Messy Implementation
```cpp
// Everything in one place - hard to maintain
if (type == "dog") {
    result = age * 7;
} else if (type == "cat") {
    result = age * 9;
} else if (type == "fish") {
    result = age * 3;
} else if (type == "bird") {
    result = age * 4;
} else if (type == "wookie") {
    result = age * 100;
}
```

### Stage 2: Switch Statement
```cpp
// Better but still not ideal
switch(type) {
    case 0:  // dog
        result = age * 7;
        break;
    case 1:  // cat
        result = age * 9;
        break;
    // etc...
}
```

### Stage 3: Function Implementation
```cpp
// Clean, reusable, maintainable
int calculateDogYears(int age) {
    // Validation
    if (age <= 0 || age > 120) {
        cout << "Invalid age";
        return 0;
    }
    return age * 7;
}

int calculateCatYears(int age) {
    if (age <= 0 || age > 120) {
        cout << "Invalid age";
        return 0;
    }
    return age * 9;
}

// Main logic becomes simple
int result = calculateDogYears(age);
```

## 5. Qt Object Management

### Creation and Lifecycle
```cpp
// Stack allocation (automatic cleanup)
QObject localObj;  // Deleted when scope ends

// Heap allocation (manual cleanup)
QObject* heapObj = new QObject();
heapObj->setObjectName("test");
delete heapObj;  // Must delete manually
```

### Common Qt Errors
```cpp
// ERROR 1: Copying QObject
QObject obj1;
QObject obj2 = obj1;  // Error: Copy constructor deleted

// ERROR 2: Returning stack object
QObject& getObject() {
    QObject local;
    return local;  // Error! Returns dangling reference
}

// ERROR 3: Using deleted object
QObject* ptr = new QObject();
delete ptr;
ptr->setObjectName("test");  // Error! Using deleted object

// CORRECT: Return heap object
QObject* createObject() {
    return new QObject();  // Caller must delete
}
```

### Qt Memory Management Tips
1. Never copy QObjects
2. Use pointers for heap allocation
3. Always delete heap objects
4. Be careful with object lifetime
5. Use smart pointers when possible
6. Consider parent-child relationships

## 6. Function Overloading

### Basic Examples
```cpp
void test() { }
void test(int age) { }
void test(string name) { }
void test(bool isActive) { }
```

### Ambiguity Issues
```cpp
// Ambiguous calls
test(57.09);  // Error: Could be int or bool
test("Brian");  // May not call version you expect

// Clear calls
test(57);      // Calls int version
test("Brian"s); // Calls string version
test(true);    // Calls bool version
```

## 7. Functions in Structs

### Basic Example
```cpp
struct Laptop {
    double weight;
    
    // Possible but not recommended
    double asKilograms() {
        return weight * 0.453592;
    }
};
```

### Why Avoid
1. Structs should focus on data
2. Use classes for combining data and behavior
3. Keeps data structures simple
4. Maintains clear separation of concerns

## Best Practices
1. Follow top-down declaration order
2. Use clear, descriptive names
3. Single responsibility per function
4. Clean up heap memory
5. Validate parameters
6. Document complex functions
7. Consider scope carefully
8. Use appropriate parameter passing method
9. Avoid overloading when possible
10. Be careful with Qt objects
11. Prefer stack allocation when possible
12. Keep functions focused and small
13. Use references over pointers when null is not needed
14. Always initialize pointers and references
15. Consider const correctness

## Common Pitfalls
1. Using functions before declaration
2. Memory leaks
3. Copying Qt objects
4. Ambiguous overloads
5. Returning local variables by reference
6. Not cleaning up heap memory
7. Improper scope management
8. Confusing value/reference/pointer semantics
9. Relying on OS for cleanup
10. Poor function organization
11. Dangling pointers/references
12. Not checking for null pointers
13. Unnecessary object copying
14. Complex function overloading
15. Mixing stack and heap management

## Key Reminders
- Functions are independent scope units
- Memory management is critical
- Consider parameter passing carefully
- Qt objects have special requirements
- Clear organization prevents bugs
- Think about scope and lifetime
- Always validate inputs
- Clean up heap allocations
- Use appropriate error handling
- Keep code maintainable