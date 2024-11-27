# Qt QML Programming: Comprehensive Study Guide

## 1. Foundations and Basic Concepts

### Object Positioning System
1. **Basic Positioning**
   - X/Y coordinates for manual positioning
   - Z-axis for stacking order
   - Position tracking capabilities
   - Anchoring system can override manual positioning

2. **Position Tracking Implementation**
```qml
function update() {
    console.log(x, y)  // Position debugging
    label.text = Math.round(x) + ", " + Math.round(y)
}

Component.onCompleted: update()
onXChanged: update()
onYChanged: update()
```

3. **Z-Order Management**
   - Higher values appear on top (like stacked papers)
   - Can be modified dynamically: `z++`
   - Affects entire parent-child hierarchy
   - Used for interactive UI layering

### Component Lifecycle
1. **Initialization Order**
   - Component creation
   - Property initialization
   - Anchor application
   - Component.onCompleted signal

2. **Position Reporting**
   - Affected by anchoring system
   - Need to consider timing of position updates
   - Use Component.onCompleted for initial values

## 2. Layout Systems

### Column Layout
```qml
Column {
    spacing: 5
    anchors.centerIn: parent
    
    Rectangle { width: 100; height: 50; color: "red" }
    Rectangle { width: 100; height: 50; color: "blue" }
}
```
- Vertical arrangement
- Automatic spacing
- Can be anchored as a unit
- Items stack top-to-bottom

### Row Layout
```qml
Row {
    spacing: 5
    anchors.centerIn: parent
    
    Rectangle { width: 50; height: 100; color: "red" }
    Rectangle { width: 50; height: 100; color: "blue" }
}
```
- Horizontal arrangement
- Same properties as Column
- Simple conversion from Column
- Items arrange left-to-right

### Grid Layout
```qml
Grid {
    rows: 2
    columns: 3
    spacing: 5
    
    Repeater {
        model: 6
        Rectangle {
            width: 50
            height: 50
            color: index % 2 ? "red" : "blue"
        }
    }
}
```
- Combines row and column concepts
- Auto-arrangement with -1 for rows/columns
- Items placed left-to-right, top-to-bottom
- Handles overflow with stacking

### Flow Layout
```qml
Flow {
    flow: Flow.LeftToRight  // or Flow.TopToBottom
    spacing: 5
    anchors.fill: parent
    
    // Children flow based on available space
    Rectangle { width: 50; height: 50; color: "red" }
    Rectangle { width: 50; height: 50; color: "blue" }
}
```
- Adaptive layout based on space
- Two flow directions available
- Clipping controls overflow visibility
- No right-to-left option

## 3. Anchoring System

### Basic Anchors
```qml
Rectangle {
    anchors {
        left: parent.left
        right: parent.right
        top: parent.top
        bottom: parent.bottom
        margins: 10
    }
}
```
- Overrides manual positioning
- Centers with centerIn
- Fills parent with fill
- Individual edge anchoring

### Margins
```qml
Rectangle {
    anchors {
        left: parent.left
        leftMargin: 10
        right: parent.right
        rightMargin: 10
    }
}
```
- Only work with set anchors
- Can be global or per-edge
- Common in responsive layouts
- Provide spacing from anchor points

## 4. Custom Components

### Basic Component Structure
```qml
Item {
    id: root
    property color color: "gray"
    property color hoverColor: "pink"
    property alias title: display.text
    
    Rectangle {
        anchors.fill: parent
        color: root.color
    }
}
```
- Properties for configuration
- Aliases for child access
- ID for self-reference
- Encapsulation of functionality

### Interactive Components
```qml
MouseArea {
    anchors.fill: parent
    hoverEnabled: true
    
    onEntered: parent.color = root.hoverColor
    onExited: parent.color = root.color
    onPressed: parent.color = root.clickColor
    onReleased: parent.color = root.hoverColor
}
```
- Hover state management
- Click handling
- State changes
- Event propagation

## 5. Practical Application: Image Viewer

### Layout Structure
```qml
Item {
    Rectangle {
        id: buttonPanel
        width: 100
        height: parent.height
        color: "gray"
        
        Column {
            anchors.fill: parent
            spacing: 5
            // Hover buttons here
        }
    }
    
    Rectangle {
        x: buttonPanel.width
        width: parent.width - x
        height: parent.height
        
        Image {
            anchors.fill: parent
            anchors.margins: 25
            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/default.jpg"
        }
    }
}
```

### HoverButton Component
```qml
Item {
    id: root
    property color color: "gray"
    property color hoverColor: "pink"
    property color clickColor: "orange"
    property alias title: display.text
    property alias area: mouseArea
    
    Rectangle {
        anchors.fill: parent
        color: root.color
        
        Text {
            id: display
            anchors.centerIn: parent
            color: "white"
            font.bold: true
        }
        
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            
            onEntered: parent.color = root.hoverColor
            onExited: parent.color = root.color
            onPressed: parent.color = root.clickColor
            onReleased: parent.color = root.hoverColor
        }
    }
}
```

## Best Practices

1. **Component Organization**
   - Use property aliases for efficiency
   - Implement proper state management
   - Consider component lifecycle

2. **Layout Management**
   - Choose appropriate layout type
   - Handle responsive behavior
   - Implement proper spacing

3. **Interaction Design**
   - Enable hover when needed
   - Handle all mouse states
   - Consider z-ordering

4. **Performance**
   - Use aliases over properties when possible
   - Implement proper clipping
   - Manage component lifecycle

## Common Pitfalls

1. **Layout Issues**
   - Anchor conflicts
   - Improper margin handling
   - Layout system misuse

2. **Interaction Problems**
   - Missing hover enabled
   - Incomplete state handling
   - Incorrect z-order management

3. **Component Design**
   - Poor property organization
   - Inefficient alias usage
   - Lifecycle mismanagement