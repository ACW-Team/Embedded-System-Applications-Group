# Embedded-System-Applications-Group
Embedded System Applications Group work

Heating Control System with Alarm (Group or Individual Project)
Assignment Overview

You will build a smart heating control system using the PIC18F45K22 board (EasyPIC7A).

Your system will:

    Measure temperature using the LM35 sensor
    Use an LED to show when the heating is ON or OFF
    Use Day and Night modes with different temperature settings
    Operate only during specific times of day (set by a real-time clock)
    Allow users to change the temperature, time, date and other settings using buttons
    Save all settings into EEPROM, so nothing is lost when the board is turned off
    Play an alarm tone from the buzzer at a set time
    Create your own libraries, follow the instructions from week 6.

You may complete this project on your own or in a group of two. The minimum group size is one and the maximum is two. Both options have the same technical requirements and marking criteria.

| Component | Weight |
| --- | ---: |
| Live demonstration and viva (hardware + code) | 50% |
| Written report (design + explanation) | 50% |

Compulsory Participation

Both parts of the assessment are compulsory:

    Part A: Live Demonstration and Individual Viva (50 marks)

    Part B: Written Report (50 marks)

Every student must participate in both parts to pass the module.

If you miss the live demonstration and viva, do not submit the report, or do not contribute to either part, you will fail the module, regardless of the marks achieved in the other part or your partner's work.

Students working in pairs must both contribute to the design, programming, testing and report writing. Both must also attend the demonstration and answer individual viva questions.

A non-participating group member may be removed after the module leader reviews the evidence. That student must then complete the assignment independently.

Approved alternative assessment arrangements will still apply.
What Your System Should Do

Your system must integrate sensing, control, and user interaction on the PIC18F45K22 (EasyPIC7A) board. It should run continuously, with all features operating together in real time. Functions must not pause or block each other. Use interrupts, timers, or efficient non-blocking loops to keep every feature responsive.

    Measure the Temperature (LM35 Sensor)
        Use the LM35 sensor connected to AN6/RE1 for analogue temperature measurement.
        Convert the ADC voltage to temperature in °C using correct calibration and scaling.
        Continuously update the measured value on both the 4-digit seven-segment display and the LCD, without flicker or delay.
        Display refresh should be smooth and concurrent with other system functions.
    Control the Heating (LED Indicator)
        Use an LED to show when the heating output is ON or OFF. The LED is only an indicator; it does not heat the room.
        Use two adjustable target temperatures: Day (for example 24 °C) and Night (for example 18 °C). Use the RTC to select the active mode. Turn the LED ON below the active target and OFF at or above it, but only when heating is enabled and within the heating window.
        Both target temperatures and the times when Day and Night modes start must be adjustable in the menu. Show the active mode on the LCD or in the status menu.
        Heating logic must continue to operate while other functions (menu, alarm, display updates) are running.
    Real-Time Clock (RTC)
        Use an external RTC module such as the Click16 board to maintain accurate time.
        Implement a heating window (for example 06:30–08:00) during which heating can operate. The selected Day or Night target applies only while heating is allowed.
        Show the current time and date on the LCD. They must be updated from the RTC while the system runs.
        Show the set alarm time in the menu. Allow the user to set the RTC time and date and the Day/Night changeover times using the buttons.
        The RTC should keep time independently, without interrupting other tasks.
    Menu and Buttons (User Interface)
        The system must not rely on hard-coded values.
        Use the menu to change:
        • Day target temperature and Night target temperature
        • Current RTC time and date
        • Day and Night changeover times
        • Heating window start and end times
        • Alarm time and tone
        • Heating and alarm ON/OFF settings
        The menu must be accessible at any time without stopping other running processes.
        Buttons must be debounced in software, and logic should allow smooth navigation between menu items.
        Use timers or flags instead of blocking delays so the system remains responsive.
    EEPROM (Save Settings)
        All user settings must be stored in EEPROM and reloaded on startup.
        Demonstrate that data persists after a full power cycle.
        Explain which EEPROM addresses hold each saved setting, such as Day/Night target temperatures, changeover times, heating window and alarm settings. The current time and date are kept by the RTC.
        EEPROM operations should occur without freezing other parts of the system (for example, using non-blocking read/write).
    Alarm and Buzzer
        The system must play a tone or melody at the programmed alarm time while maintaining other functions (temperature display, RTC update, LED control).
        Alarm must last at least 1–2 seconds using timer-based or interrupt-driven logic, not delay loops.
        Provide at least two selectable tones or melodies.
        Users must be able to enable, disable, or silence the alarm through the menu.

Suggested File Structure
| Function | Example Files |
| --- | --- |
| LM35 temperature | `lm35.c` / `lm35.h` |
| Seven-seg display | `sevenseg.c` / `sevenseg.h` |
| Buttons | `buttons.c` / `buttons.h` |
| LCD display | `lcd.c` / `lcd.h` |
| Buzzer | `buzzer.c` / `buzzer.h` |
| RTC clock | `rtc.c` / `rtc.h` |
| EEPROM | `eeprom_cfg.c` / `eeprom_cfg.h` |
| Main program | `main.c` |

Testing Procedure

| Step | Expected Behaviour |
| ---: | --- |
| 1 | Set Day to 24 °C and Night to 18 °C. Check that the LED turns ON below the active target and OFF at or above it. |
| 2 | Change the RTC time to switch between Day and Night. Check the active mode and temperature target. |
| 3 | Set the heating window to start in 1–2 minutes. Check that the LED operates only inside this window. |
| 4 | Switch heating OFF using the menu. The LED stays OFF. |
| 5 | Change the RTC time and date in the menu. Check that the LCD shows the new values. |
| 6 | Set the alarm one minute ahead. Check the buzzer plays the selected tone. |
| 7 | Restart the board. Check that Day/Night settings and other saved values return. Confirm the RTC still keeps time. |

Deliverables

One ZIP file per individual or group containing:

    All .c and .h files
    A README (build & run instructions)
    A short 2–3-minute video showing the system working

Submit one separate report per individual or group (do not put the report in the ZIP):

    A report on the system design, libraries, hardware, tests and learning (maximum 2,500 words, excluding figures, appendices, references and code). For pairs, include a contribution table, each person’s 150–200-word reflection, and an AI-use declaration from each student.

Group or Individual Work and Fair Marking

    You may work alone or with one partner. Groups must have at least one and no more than two students.
    In a pair, both students must take part in design, coding, testing, hardware work and report writing. Divide tasks fairly and keep a record of who did what.
    Each student must understand the whole system. The viva is individual, even if the project and report were completed as a pair.
    Keep your own progress notes and code history. The lecturer may ask either student to explain or change any part of the code.
    For pairs, submit a contribution table showing the tasks and report sections completed by each member. Each person must also write their own short reflection.

BuddyCheck will start in Week 6 and will be used at later checkpoints to record each person’s contribution. Both students must complete it honestly.

BuddyCheck and records of work are used to check each student’s contribution. Marks may go up or down as explained below. A student who does no report work receives 0/50 for Part B.

If your partner is not contributing, you are responsible for telling the module leader promptly. Do not wait until the final submission or just report it in BuddyCheck.

A student who is not taking part may be removed from the group after the module leader reviews the evidence. A removed student must complete and submit the assignment alone.

A student working alone is not required to complete BuddyCheck and will not lose marks for choosing to work alone.
BuddyCheck Marking and Examples

BuddyCheck starts in Week 6 and continues at later checkpoints. It is used for students working in pairs only. Each member must complete it and give an honest account of their partner's work. The module leader will also consider the contribution table, code changes, drafts, progress notes and viva answers before deciding any adjustment.

| Adjustment | When it may apply |
| --- | --- |
| +10% | Much more than a fair share of the design, code, testing and report, backed by evidence. |
| +5% | More than a fair share, backed by evidence. |
| 0% | A fair share of the work. |
| -5% | Limited work or missed agreed tasks. |
| -10% | Very little work, despite reminders and support. |
| -20% | Repeated lack of participation across the project, despite reminders and support. |
| No report work | Part B is 0/50 for that student. |
| No live demonstration and viva | Part A is 0/50, so Part B is also capped at 0/50. |

For the +10%, +5%, -5%, -10% and -20% bands, the adjustment is a percentage of the student's total mark after the Part B report cap has been applied. For example, a total of 80 with +10% becomes 88, not 90. The final mark cannot exceed 100/100. There is no automatic adjustment: the module leader decides after checking the evidence.

| Student | Part A /50 | Report before cap /50 | Part B after cap /50 | BuddyCheck | Final /100 |
| --- | ---: | ---: | ---: | ---: | ---: |
| A | 40 | 45 | 40 | +10% | 88 |
| B | 38 | 42 | 38 | +5% | 79.8 |
| C | 35 | 40 | 35 | 0% | 70 |
| D | 20 | 25 | 20 | -10% | 36 |
| E | 45 | 0 (no report work) | 0 | -10% | 40.5 |
| F | 0 (no viva) | 40 | 0 | 0% | 0 |
| G | 50 | 50 | 50 | +10% | 100 (capped) |
| H | 30 | 30 | 30 | -20% | 48 |

These figures are examples only. Students working alone receive no BuddyCheck adjustment. Where one person has not contributed, report it to the module leader as soon as possible. A non-participating member may be removed from the group and will then be required to complete the assignment alone.
Use of Artificial Intelligence (AI) and Academic Integrity

AI tools can help you learn, but the code and report must be your own work. Each student must follow the AI-use rules below.

    Permitted learning support: explaining concepts (such as ADC, interrupts, timers, I²C and EEPROM), suggesting debugging approaches, providing general planning ideas, and checking spelling or punctuation.
    Not allowed for this assessment: using AI to write or rewrite the report, produce complete assessed programs or libraries, create assessment diagrams or fabricated test results, or present AI-generated output as your own original work.
    Any explicitly permitted AI-generated code, figures or text included in the submission must be clearly identified and appropriately acknowledged. You remain responsible for correctness, testing, authorship and compliance with the assignment instructions.
    No AI assistance is permitted during the live demonstration or viva. You must answer questions and carry out any requested explanation or code change independently.
    Each student must include an AI-use declaration in the report. Say if you used AI and, if so, which tool, why you used it and what you checked or changed. Keep any relevant prompts or outputs if asked.
    Undeclared or unauthorised AI use may be investigated as academic misconduct. The viva checks your understanding of the work you submit.

For full guidance on AI use, see the Student Use of AI information on Canvas.
How You Will Be Marked in the Demonstration and Viva
Part A – Demonstration and Individual Viva (50 %)

    Show the working system on the EasyPIC7A board. In a pair, each student must take part in the demonstration and answer individual viva questions about the full system.

    Each criterion below is assessed using the live demonstration and each student’s viva answers together. A working feature alone does not earn separate marks.

Each student must show and explain each item to earn pass marks for that item. If either is missing, the item is marked in the fail band (0–39% of its marks).

The lecturer may ask you to trace code, explain a fault or make a small change.

Report cap: Part B cannot be higher than the student’s own Part A mark (both out of 50). After this cap, BuddyCheck may adjust the individual total as shown below.

| Criterion | Weight | Excellent (70–100 %) | Good (50–69 %) | Pass (40–49 %) | Fail (0–39 %) |
| --- | ---: | --- | --- | --- | --- |
| Heating Control (LED and Viva) | 8 | Shows Day and Night targets, correct LED control and heating times. Explains the code in the viva. | Day/Night heating works with small errors. Explains most control code in the viva. | Basic heating works in one mode. Shows it and explains the code in the viva. | Cannot show the control working or cannot explain it in the viva. |
| Temperature Reading (LM35 and Viva) | 6 | Shows the temperature on both displays and explains the ADC reading and calculation in the viva. | Reading works with small errors. Explains most of the ADC code in the viva. | Shows a basic reading and gives a simple ADC explanation in the viva. | Cannot show a reading or cannot explain the code in the viva. |
| RTC and Heating Times (Viva) | 7 | Shows RTC time/date editing, Day/Night changeovers and heating window. Explains the code in the viva. | Most clock settings work. Shows them and explains most RTC code in the viva. | Basic time features work and are partly explained in the viva. | Clock functions do not work or cannot be explained in the viva. |
| Menu and Buttons (Viva) | 7 | Shows Day/Night targets and times, RTC time/date and other settings. Explains menu code in the viva. | Most settings work. Shows them and explains most menu code in the viva. | Basic menu works and is partly explained in the viva. | Menu does not work or cannot be explained in the viva. |
| EEPROM Saving (Viva) | 6 | Shows Day/Night and other settings saved after restart. Explains EEPROM code in the viva. | Most settings are saved and the code is mostly explained in the viva. | Some settings are saved and partly explained in the viva. | Settings are not saved or the code cannot be explained in the viva. |
| Alarm and Buzzer (Viva) | 6 | Shows alarm timing and two tones. Explains how the buzzer works in the viva. | Alarm mostly works and its code is mostly explained in the viva. | Basic alarm works and is partly explained in the viva. | Alarm does not work or cannot be explained in the viva. |
| LCD and 7-Seg Displays (Viva) | 4 | Both displays update well. Shows them and explains the refresh code in the viva. | Displays mostly work and their code is mostly explained in the viva. | Basic displays work and are partly explained in the viva. | Displays do not work or cannot be explained in the viva. |
| Libraries and Full System (Viva) | 6 | Libraries work together. Shows the full system and explains its files and code in the viva. | Most libraries work together and are mostly explained in the viva. | Some libraries work and are partly explained in the viva. | Libraries do not work together or cannot be explained in the viva. |

Subtotal = 50 marks

Example: If you get 25/50 in Part A and the report earns 40/50, your report is capped at 25/50. Your total is 50/100 before any BuddyCheck adjustment.

    A video, a written explanation or a working output alone cannot replace your live demonstration and viva answers.

Part B – Group or Individual Report (50 %)

    Write about the system your group or you individually built and showed in Part A.

    Include a 150–200-word reflection and AI declaration from every student. Pairs must also include a contribution table.

    Use the report headings below. Your report must match the real code, hardware and tests.

Each report section may be checked during the viva. Marks depend on the written evidence and what you can show and explain. Unsupported claims do not earn marks.

Report cap: Each student’s Part B mark is based on their report work and then capped at their own Part A mark (both out of 50). The separate BuddyCheck adjustment is applied to the total after this cap.

| Section (use as heading) | Weight | Excellent (70–100 %) | Good (50–69 %) | Pass (40–49 %) | Fail (0–39 %) |
| --- | ---: | --- | --- | --- | --- |
| System Design and Overview | 10 | Clear diagram of the system, including Day/Night heating control. Explains the design choices. | Good diagram and design with small gaps. | Basic diagram with little explanation. | Design is missing, wrong or not explained. |
| Software Architecture and Modularity | 10 | Shows the main libraries, how they connect and why they are used. | Shows most files and how they connect. | Lists some files with little explanation. | Software structure is missing or unclear. |
| Hardware and Interfaces | 6 | Shows correct board connections and explains ADC, I²C and digital I/O. | Most connections and explanations are correct. | Lists hardware with basic explanations. | Hardware details are missing or wrong. |
| EEPROM and RTC | 8 | Explains how settings are saved and restored, and how RTC time and date are set. | Explains most of the EEPROM and RTC work. | Basic explanation with missing details. | EEPROM or RTC explanation is missing or wrong. |
| Testing and Results | 8 | Tests Day/Night switching, temperature control, RTC editing and other features, with evidence of fixes. | Tests most features with evidence. | Few tests and little evidence. | No useful tests or evidence. |
| Reflection and Contribution | 6 | Each member explains their work, problems faced and learning. The contribution table is clear (pairs only). | Each member explains their work with a few missing details. | Basic reflection or unclear account of work done. | No reflection or no evidence of personal contribution. |
| Presentation and Clarity | 2 | Clear writing, headings, labelled figures and references. | Clear report with small mistakes. | Readable but not well organised. | Hard to follow or missing labels. |
