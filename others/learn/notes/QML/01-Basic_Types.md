# Comprehensive Qt QML Study Notes

## 1. Understanding the Item Type
### Core Concept
- Fundamental base type for all QML visual items
- Similar to QObject in Qt Core ("the base class of everything")
- Paradoxical nature:
  - Documentation calls it a "basic visual type"
  - Yet has "no visual appearance"

### Purpose
- Acts as container/parent for other elements
- Provides foundation for custom components
- Manages layout and child elements
- NOT meant for direct visual use

### Implementation
```qml
Item {
    id: root
    width: 100
    height: 100
    
    // Properties
    property int customValue: 0
    
    // Child elements
    Rectangle {
        anchors.fill: parent
        color: "blue"
    }
}
```

### Key Features
- Anchoring system
- Child element management
- Rectangle clipping
- Layout control
- Property binding support

## 2. Rectangle Type
### Basic Usage
```qml
Rectangle {
    width: 200
    height: 200
    color: "red"
    border.color: "black"
    border.width: 2
}
```

### Advanced Features
1. Circle Creation:
```qml
Rectangle {
    width: 100
    height: 100
    radius: width  // Creates perfect circle
    color: "blue"
}
```

2. Gradient Support:
```qml
Rectangle {
    gradient: Gradient {
        GradientStop { position: 0.0; color: "red" }     // Start
        GradientStop { position: 0.5; color: "yellow" }  // Middle
        GradientStop { position: 1.0; color: "blue" }    // End
    }
}
```

### Properties
- color: Fill color
- border.color: Border color
- border.width: Border thickness
- radius: Corner rounding
- visible: Visibility control

## 3. Image Type
### Resource System Integration
- Files compile directly into executable
- Uses virtual directory structure
- Two supported path formats:
```qml
Image {
    source: ":/images/image.png"      // Colon syntax
    source: "qrc:/images/image.png"   // QQ syntax
}
```

### Loading Behaviors
1. Local Images:
- Preload at application start
- Block UI until loaded
- Immediate display

2. Remote Images:
- Background loading
- Non-blocking
- Progress monitoring available

### Example Implementation
```qml
Image {
    id: myImage
    source: "http://example.com/image.png"
    
    // Aspect ratio handling
    fillMode: Image.PreserveAspectFit
    
    // Loading monitoring
    onProgressChanged: console.log("Loading progress:", progress)
    onStatusChanged: {
        if (status === Image.Ready) {
            console.log("Image loaded")
        } else if (status === Image.Error) {
            console.log("Loading failed")
        }
    }
}
```

### Performance Considerations
- Local images impact startup time
- Consider async loading for large images
- Monitor memory usage with multiple images

## 4. Text Type
### Basic Usage
```qml
Text {
    text: "Simple text"
    color: "black"
    font.pointSize: 12
}
```

### HTML Support
```qml
Text {
    text: "<b>Bold</b> and <i>italic</i> with <font color='green'>color</font>"
    textFormat: Text.RichText
}
```

### Styling Approaches
1. Property-Based (Preferred for simple styling):
```qml
Text {
    text: "Styled text"
    font.bold: true
    font.italic: true
    color: "blue"
}
```

2. HTML-Based (For complex formatting):
```qml
Text {
    text: "<b>Bold</b> with <u>underline</u> and <i>italic</i>"
}
```

### Important Warning
- Avoid mixing HTML and property styling
- Can lead to unpredictable results
```qml
// DON'T DO THIS:
Text {
    text: "<b>Bold text</b>"
    font.bold: true  // Conflicts with HTML
}
```

### Link Handling
```qml
Text {
    text: "<a href='https://example.com'>Click me</a>"
    onLinkHovered: console.log("Hover:", link)
    onLinkActivated: Qt.openUrlExternally(link)
}
```

## 5. MouseArea
### Critical Setup Requirements
1. Size Definition (Required):
```qml
MouseArea {
    // MUST have either:
    anchors.fill: parent
    // OR
    width: 100; height: 100
}
```

2. Hover Enabling (For position tracking):
```qml
MouseArea {
    hoverEnabled: true
    onPositionChanged: console.log(mouse.x, mouse.y)
}
```

3. Button Acceptance:
```qml
MouseArea {
    acceptedButtons: Qt.LeftButton | Qt.RightButton
    onClicked: {
        if (mouse.button === Qt.LeftButton) {
            console.log("Left click")
        } else if (mouse.button === Qt.RightButton) {
            console.log("Right click")
        }
    }
}
```

### Best Practices
1. Parent-Child Relationship:
```qml
Rectangle {
    id: myRect
    color: "blue"
    
    MouseArea {
        anchors.fill: parent
        onClicked: parent.color = "red"
    }
}
```

2. Event Handling:
```qml
MouseArea {
    anchors.fill: parent
    hoverEnabled: true
    
    // Basic events
    onClicked: console.log("Clicked")
    onDoubleClicked: console.log("Double clicked")
    
    // Mouse tracking
    onEntered: console.log("Mouse entered")
    onExited: console.log("Mouse exited")
    onPositionChanged: console.log("Mouse moved")
    
    // Press handling
    onPressed: console.log("Pressed")
    onReleased: console.log("Released")
}
```

## 6. Custom Components
### File Requirements
- Must use CamelCase naming (MyButton.qml)
- Platform/version specific naming rules apply
- Must match component name

### Basic Structure
```qml
// MyButton.qml
Item {
    id: root
    width: 100
    height: 40
    
    // Public properties
    property color normalColor: "lightgray"
    property color clickedColor: "green"
    property string buttonText: "Click me"
    
    // Visual elements
    Rectangle {
        id: background
        anchors.fill: parent
        color: normalColor
        
        Text {
            anchors.centerIn: parent
            text: buttonText
        }
        
        MouseArea {
            anchors.fill: parent
            onPressed: parent.color = clickedColor
            onReleased: parent.color = normalColor
        }
    }
}
```

### Usage
```qml
MyButton {
    normalColor: "blue"
    clickedColor: "red"
    buttonText: "Custom Button"
}
```

## Common Gotchas and Solutions
1. Item Type:
   - Remember it's non-visual
   - Use for structure, not display

2. Resource Handling:
   - Use Qt Creator's path copy feature
   - Test both local and resource loading
   - Monitor memory usage

3. Text Styling:
   - Choose one styling approach
   - Don't mix HTML and properties
   - Consider performance with rich text

4. MouseArea Setup:
   - Always define size
   - Enable hover explicitly
   - Specify accepted buttons
   - Consider performance with hover tracking

5. Component Design:
   - Keep interaction elements as children
   - Use clear property names
   - Follow naming conventions
   - Consider reusability

## Best Practices Summary
1. Structure:
   - Organize components logically
   - Maintain clear parent-child relationships
   - Use proper encapsulation

2. Performance:
   - Monitor image loading impact
   - Use async loading when appropriate
   - Consider resource usage

3. Style:
   - Consistent naming conventions
   - Clear property names
   - Proper documentation

4. Testing:
   - Test different platforms
   - Verify resource loading
   - Check interaction handling