ESP32-Based Vehicle Indicator Controller with FreeRTOS

A real-time vehicle indicator controller built using the ESP32 and FreeRTOS.
This project demonstrates interrupt-driven input handling, real-time timing control, and high-current LED switching using a MOSFET driver stage.

Features
Left and right turn indicator control
Hazard light override mode
GPIO interrupt-based switch detection
Real-time timing using FreeRTOS
MOSFET-based high-current LED switching
TC4427 gate driver integration for reliable MOSFET operation
Developed using ESP-IDF in Embedded C
Hardware Used
Component	Purpose
ESP32	Main microcontroller
Push Buttons	Left, Right, Hazard inputs
LEDs / Indicator Lamps	Vehicle indicators
MOSFET	High-current switching
TC4427 Gate Driver IC	Fast MOSFET gate driving
External Power Supply	Indicator load power
System Overview

The ESP32 monitors three switches:

Left Indicator Switch
Right Indicator Switch
Hazard Switch

GPIO interrupts are used to detect switch state changes in real time.

Whenever a button changes state, the corresponding Interrupt Service Routine (ISR) updates a shared state variable.

The main application logic uses these updated states to control:

Left indicator blinking
Right indicator blinking
Hazard light override behavior

Timing control is handled using FreeRTOS delays.

GPIO Configuration
GPIO	Function
GPIO18	Left Indicator Switch
GPIO19	Right Indicator Switch
GPIO5	Hazard Switch
GPIO21	Left Indicator Output
GPIO22	Right Indicator Output
Software Concepts Used
FreeRTOS

Used for:

Real-time timing control
Task delays using vTaskDelay()
Deterministic blinking behavior
GPIO Interrupts

Used for:

Immediate switch-state detection
Event-driven input handling
Reduced CPU overhead compared to polling
Embedded C

Low-level firmware written using:

ESP-IDF
GPIO driver APIs
ISR handlers
Working Logic
Left Indicator

When Button 1 is pressed:

Left indicator blinks ON/OFF every 200 ms
Right Indicator

When Button 2 is pressed:

Right indicator blinks ON/OFF every 200 ms
Hazard Mode

When Hazard switch is pressed:

Both indicators blink simultaneously
Overrides left/right indicator operation
Circuit Design

The ESP32 GPIO pins cannot directly drive high-current vehicle indicator loads.

To solve this:

MOSFETs are used as switching devices
TC4427 gate driver IC improves MOSFET switching performance
Allows reliable switching of higher-current LED loads
Project Structure
├── main
│   └── main.c
├── CMakeLists.txt
├── sdkconfig
└── README.md
Code Highlights
GPIO Interrupt Service Routine
static void IRAM_ATTR isr_func_1(void *arg)
{
    button_1_value = gpio_get_level(BUTTON_1);
}
Hazard Override Logic
if (button_3_value == 0)
{
    gpio_set_level(LED_1, 1);
    gpio_set_level(LED_2, 1);
}
FreeRTOS Timing Control
vTaskDelay(pdMS_TO_TICKS(200));
How to Run
1. Install ESP-IDF

Official ESP-IDF Documentation:

ESP-IDF Documentation

2. Clone the Repository
git clone <your-repo-link>
cd <repo-name>
3. Build the Project
idf.py build
4. Flash to ESP32
idf.py -p COMx flash monitor

Replace COMx with your ESP32 serial port.

Future Improvements
Separate FreeRTOS tasks for each indicator
Software debouncing for switches
CAN bus integration
Automotive-grade protection circuitry
PWM brightness control
Audible relay-click simulation
Learning Outcomes

This project helped in understanding:

Embedded C programming
ESP-IDF development
FreeRTOS basics
GPIO interrupts
Event-driven embedded systems
MOSFET driver circuits
Hardware-software integration
