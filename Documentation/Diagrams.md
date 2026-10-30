# LM35 Temperature Sensor
```mermaid
flowchart 
    A[LM35 Sensor/10 mV per °C] 
    B[AN6 / RE1/Analogue Input] 
    C[ADC<br/>10-bit Conversion] 
    D[Temperature Calculation/Voltage to °C]
    E[ Temperature Value ] 

    F[ LCD Display ]
    G[ 4-Digit 7-Segment ]

    A --> B
    B --> C
    C --> D
    D --> E
    E --> F
    E --> G
```

# Control Heating LED (Light Emmitting Diode)

```mermaid
flowchart 
    A[ LM35 Sensor<br/>Current Temperature ]
    B[ RTC Module<br/>Current Time ]
    C[ Heating Settings<br/>Enabled / Disabled ]
    D{ Heating Enabled<br/>and Within Time Window? }
    E[ LED OFF<br/>Heating Inactive ]
    F{ RTC Mode }
    G[ Day Temperature<br/>Target: 24°C ]
    H[ Night Temperature<br/>Target: 18°C ]
    I{ Current Temperature<br/>< Target Temperature? }
    J[ LED ON<br/>Heating Active ]
    K[ LCD Display<br/>Mode and Temperature ]

    A --> I
    B --> D
    C --> D
    D -->|No| E
    D -->|Yes| F
    F -->|Day| G
    F -->|Night| H
    G --> I
    H --> I
    I -->|Yes| J
    I -->|No| E
    J --> K
    E --> K

```

# Real-Time Clock (RTC)

```mermaid
flowchart
```

# User Interface (UI)

```mermaid
flowchart
```

# EEPROM

```mermaid
flowchart
```

# Alarm and Buzzer 

```mermaid
flowchart
```

# File Structure

```mermaid
flowchart
```