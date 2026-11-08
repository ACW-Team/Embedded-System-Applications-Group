# Reece 
## 1. Tempreature Measurement (LM35 Sensor)
### Requirments:
1. Read LM35 Temperature sensor to AN6/RE1
2. Convert ADC reading int Degrees Celsius
3. Privide Temperature to LCD
4. Continuously monitor temperature without blocking other system functions.

``` mermaid
flowchart TD
    A([Start]) --> B[Initialise ADC Module]
    B --> C[Configure RE1 / AN6 as Analogue Input]
    C --> D[Configure ADC Reference Voltage and Conversion Clock]
    D --> E[Begin Main Program Loop]

    E --> F{Temperature Reading Due?}

    F -- No --> G([Return to Main Loop])

    F -- Yes --> H[Select ADC Channel AN6]

    H --> I[Start ADC Conversion]

    I --> J{ADC Conversion Complete?}

    J -- No --> G

    J -- Yes --> K[Read 10-bit ADC Result]

    K --> L[Convert ADC Result to Voltage]

    L --> M[Convert Voltage to Temperature in Celsius]

    M --> N[Update Shared Temperature Value]

    N --> O[Update LCD Temperature Data]

    O --> P[Update Seven-Segment Display Buffer]

    P --> Q[Provide Temperature to Heating Control]

    Q --> G
```

```
As the EasyPic PIC18F45K22 usese internal ADC analouge values produced, 
approximately 10 mV per degree.
If ADC conversion is not complete the program will check during iteration.
```

## 3. Real Time Clock (LED Indicator)
### Requirments:
1. Communicate with an external RTC module, such as the Click16 board.
2. Read the current time and date.
3. Allow the user to adjust the RTC time and date.
4. Support adjustable Day/Night changeover times.
5. Support adjustable heating-window start and end times.
6. Supply accurate time information to the heating-control and alarm systems.

```mermaid
flowchart TD
    A([Start]) --> B[Initialise I2C Communication]

    B --> C[Initialise External RTC Module]

    C --> D{RTC Communication Successful?}

    D -- No --> E[Set RTC Error Flag]
    E --> F([Return to Main Loop])

    D -- Yes --> G[Begin RTC Update Loop]

    G --> H{RTC Update Due?}

    H -- No --> F

    H -- Yes --> I[Read RTC Time and Date]

    I --> J{RTC Data Valid?}

    J -- No --> E

    J -- Yes --> K[Update Current Time and Date]

    K --> L{RTC Adjustment Requested?}

    L -- Yes --> M[Receive New Time and Date from Menu]
    M --> N[Validate New Values]

    N --> O{Values Valid?}

    O -- No --> P[Report Invalid Settings]
    P --> Q[Read Day and Night Changeover Settings]

    O -- Yes --> R[Write New Time and Date to RTC]
    R --> Q

    L -- No --> Q

    Q --> S{Current Time Within Day Period?}

    S -- Yes --> T[Set Active Mode to Day]

    S -- No --> U[Set Active Mode to Night]

    T --> V[Read Heating Window Settings]
    U --> V

    V --> W{Current Time Inside Heating Window?}

    W -- Yes --> X[Set Heating Window Active Flag]
    W -- No --> Y[Clear Heating Window Active Flag]

    X --> Z[Update Shared RTC and Mode Data]
    Y --> Z

    Z --> AA[Supply Time to Heating and Alarm Systems]

    AA --> AB[Update LCD Time and Date Data]

    AB --> F
```

```
As the RTC module act indepenantly from the PIC18F45K22 maintains the current time and date.
As the microcontroller communicates with it using I²C as seen by the table:
```
| Setting | Example Value |
|---|---|
| Day Mode Start | 07:00 |
| Night Mode Start | 21:00 |
| Heating Window Start | 06:30 |
| Heating Window End | 08:00 |

```
At 07:30, Day mode would be active, and the system would be inside the heating window.

At 22:00, Night mode would be active, but the heating window would be inactive.

RTC communication and menu adjustments must not prevent temperature readings,
LED updates or alarm operation. The final implementation should use short,
scheduled operations or a non-blocking communication state machine where necessary.
```

## 5 EEPROM (Save Settings)

### Requirments:
1. Store user-configurable settings in EEPROM.
2. Restore the saved settings when the system starts.
3. Preserve settings after a power cycle.
4. Define which EEPROM addresses store individual settings.
5. Avoid unnecessary writes and blocking operations.
6. Keep the current time and date in the external RTC rather than duplicating them in EEPROM.

```mermaid
flowchart TD
    A([System Startup]) --> B[Initialise EEPROM Configuration]

    B --> C[Read Configuration from EEPROM]

    C --> D{Saved Configuration Valid?}

    D -- No --> E[Load Default Configuration]

    E --> F[Mark Default Configuration for Saving]

    D -- Yes --> G[Restore Saved Configuration]

    F --> H[Apply Configuration to System]
    G --> H

    H --> I[Enter Main Program Loop]

    I --> J{User Settings Modified?}

    J -- No --> K([Return to Main Loop])

    J -- Yes --> L[Validate New Configuration]

    L --> M{Configuration Valid?}

    M -- No --> N[Reject Invalid Settings]
    N --> K

    M -- Yes --> O[Mark Configuration as Changed]

    O --> P{EEPROM Write Ready?}

    P -- No --> K

    P -- Yes --> Q[Write Next Configuration Byte]

    Q --> R{Write Operation Complete?}

    R -- No --> K

    R -- Yes --> S{More Configuration Bytes Pending?}

    S -- Yes --> T[Advance EEPROM Write Position]
    T --> K

    S -- No --> U[Mark Configuration Save Complete]

    U --> V[Clear Configuration Changed Flag]

    V --> K
```

``` 
EEPROM stores the settings and users configurations through the menu,
unlike RAM EEPROM retains the contents and data after the microcontrikker loses power.

Upon startup the loaded program reads the stored configuration and checks against valid records.

If it is invalid or has not been saved/set the program loads default values. 

When the user updates the congiguration becomes valid, with the updated values
saved to EEPROM.

EEPROM writes should be performed only when necessary and should not introduce long blocking delays. The firmware can track pending writes and check their completion during successive main-loop iterations.
```

## Intergration
```mermaid
flowchart TD
    A([System Startup]) --> B[Initialise Hardware and Libraries]

    B --> C[Load Configuration from EEPROM]

    C --> D[Start Main Program Loop]

    D --> E[Update LM35 Temperature Reading]

    E --> F[Update RTC Time and Date]

    F --> G[Evaluate Heating Control]

    G --> H[Process Menu and Button Inputs]

    H --> I[Update LCD and Seven-Segment Data]

    I --> J[Process Alarm and Buzzer]

    J --> K[Process Pending EEPROM Writes]

    K --> D
```
# Wiktor
## 2. Heating Control (LED Indicator)

## 4. Menu and Burrons (User Interface)

## 6. Alarm and Buzzer

## Intergration