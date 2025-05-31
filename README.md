# Arduino LCD Sensor Display

A simple Arduino project that displays temperature and light sensor readings on an LCD screen, alternating between the two measurements every 2 seconds.

## Features

- **Temperature Monitoring**: Reads analog temperature sensor (TMP36)
- **Light Level Detection**: Measures ambient light using an LDR (Light Dependent Resistor)
- **Custom LCD Icons**: Displays thermometer and lightbulb icons for visual clarity
- **Auto-switching Display**: Alternates between temperature and light readings every 2 seconds
- **16x2 LCD Support**: Uses standard HD44780-compatible LCD in 4-bit mode

## Hardware Requirements

### Components
- Arduino Uno 
- 16x2 LCD Display 
- Temperature sensor (TMP36)
- LDR (Light Dependent Resistor)
- 10kΩ resistor (for LDR voltage divider)
- Jumper wires
- Breadboard

### Pin Connections

#### LCD Connections
| LCD Pin | Arduino Pin | Description |
|---------|-------------|-------------|
| VSS     | GND         | Ground |
| VDD     | 5V          | Power |
| V0      | Potentiometer | Contrast adjustment |
| RS      | Pin 12      | Register Select |
| EN      | Pin 11      | Enable |
| D4      | Pin 5       | Data bit 4 |
| D5      | Pin 4       | Data bit 5 |
| D6      | Pin 3       | Data bit 6 |
| D7      | Pin 2       | Data bit 7 |
| A       | 5V          | Backlight anode |
| K       | GND         | Backlight cathode |

#### Sensor Connections
| Component | Arduino Pin | Notes |
|-----------|-------------|-------|
| Temperature Sensor | A0 | TMP36: Flat side facing you - Left=VCC, Center=Signal, Right=GND |
| LDR | A1 | Use with 10kΩ pull-down resistor |

## Wiring Diagram

```
Temperature Sensor (TMP36):
VCC (Left pin) → 5V
Signal (Center) → A0
GND (Right pin) → GND

LDR Circuit:
LDR → A1 → 10kΩ Resistor → GND
LDR other end → 5V
```

## Software Features

### Custom Characters
The code includes custom 8x8 pixel characters:
- **Thermometer icon** (index 0): Displayed with temperature readings
- **Lightbulb icon** (index 1): Displayed with light level readings

### Display Format
- **Temperature**: `🌡 Temp: XX.X C`
- **Light Level**: `💡 Light: XX %`

### LCD Library Implementation
This project implements a custom LCD library with essential functions:
- 4-bit communication mode
- Cursor positioning
- Custom character creation
- Float and integer printing with proper formatting

## Installation and Setup

1. **Wire the components** according to the pin connections table above
2. **Upload the code** to your Arduino using the Arduino IDE
3. **Adjust LCD contrast** using the potentiometer connected to V0
4. **Power on** and observe the alternating display

## Code Structure

### Main Functions
- `setup()`: Initializes LCD, creates custom characters, sets up sensor pins
- `loop()`: Main program loop that alternates between sensor readings every 2 seconds

### LCD Functions
- `lcdInit()`: Initializes the LCD in 4-bit mode
- `lcdCreateChar()`: Creates custom characters
- `lcdPrint()`: Prints strings to LCD
- `lcdPrintFloat()`: Prints floating-point numbers with specified decimal places
- `lcdSetCursor()`: Positions cursor on the display

### Sensor Reading
- **Temperature**: Converts analog reading to voltage, then to Celsius (assumes TMP36 sensor)
- **Light Level**: Maps analog reading (0-1023) to percentage (0-100%)

## Customization Options

### Modify Display Interval
Change the switching interval by modifying the comparison value:
```cpp
if (millis() - lastSwitch >= 2000) { // Change 2000 to desired milliseconds
```

### Adjust Temperature Calculation
For different temperature sensors, modify the conversion formula:
```cpp
float tempC = voltage / 0.01; // TMP36: 10mV per degree
```

### Reverse Light Level Mapping
If your LDR gives higher values in darkness:
```cpp
int lightPercent = map(lightLevel, 0, 1023, 100, 0); // Inverted mapping
```

### Add Welcome Message
Uncomment the welcome message line in `setup()`:
```cpp
lcdPrint("Your Name Here");
```

## Troubleshooting

### Display Issues
- **Blank screen**: Check wiring, especially power and ground connections
- **Unreadable text**: Adjust contrast potentiometer
- **Partial display**: Verify all data pin connections (D4-D7)

### Sensor Issues
- **Incorrect temperature**: Verify sensor type and wiring, check conversion formula
- **Light readings stuck**: Check LDR and resistor connections
- **Erratic readings**: Add delay or averaging for stable readings

### Common Problems
- **Display not updating**: Check if Arduino is receiving power and code is uploaded
- **Wrong sensor values**: Verify analog pin connections (A0 for temp, A1 for light)

## License

This project is open source.

## Contributing

Feel free to submit issues, fork the repository, and create pull requests for any improvements.

---

**Enjoy building your Arduino sensor display project!** 🔧⚡
