<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# Analog Peripheral Manager (APM) — Light-sensing Alarm with CMP and APM Using the PIC18F56Q71 Microcontroller with MCC Melody

This code example demonstrates one use case of the Analog Peripheral Manager (APM) and showcases its configuration in MPLAB® Code Configurator (MCC) Melody. The Comparator Peripheral (CMP) and the APM are used to create a light-sensing alarm. Two Click boards, a POT 3 potentiometer, and an AMBIENT light sensor supply the Comparator's input signals. The Comparator’s output signal and a Pulse-Width Modulation (PWM) signal are inputs to the Configurable Logic Cell (CLC) module set up as an AND gate whose output drives a BUZZ Click board. The potentiometer sets the threshold at which the speaker is driven. The APM will switch the Comparator on and off based on the specified period and event timings.

## Related Documentation

More details and code examples on the PIC18F56Q71 can be found at the following links:

- [PIC18-Q71 Product Family Page](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/pic-mcus/pic18-q71)
- [PIC18F56Q71 Code Examples on GitHub](https://github.com/orgs/microchip-pic-avr-examples/repositories?q=pic18f56q71&type=all&language=&sort=)

## Software Used

- [MPLAB® X IDE](http://www.microchip.com/mplab/mplab-x-ide) v6.10 or newer
- [MPLAB® XC8](http://www.microchip.com/mplab/compilers) v2.41 or newer
- [PIC18F-Q Series Device Pack](https://packs.download.microchip.com/) v1.19.401 or newer

## Hardware Used

- The [PIC18F56Q71 Curiosity Nano](https://www.microchip.com/en-us/development-tool/EV01G21A) development board is used as a test platform:
  <br><img src="images/pic18f56q71-curiosity-nano-board.png">

- [Curiosity Nano Adapter](https://www.microchip.com/en-us/development-tool/AC164162):
  <br><img src="images/Curiosity-Nano-Adapter.jpg" height="400">

- [POT 3 CLICK board™](https://www.mikroe.com/pot-3-click) (mikroBUS™ socket 1):
  <br><img src="images/pot-3-click-board.jpg" height="400">

- [AMBIENT CLICK board](https://www.mikroe.com/ambient-click) (mikroBUS socket 2):
  <br><img src="images/ambient-click-board.jpg" height="400">

- [BUZZ CLICK board](https://www.mikroe.com/buzz-click) (mikroBUS socket 3):
  <br><img src="images/buzz-click-board.jpg" height="400">
<br>

## Operation

To program the Curiosity Nano board with this MPLAB X project, follow the steps provided in the [How to Program the Curiosity Nano Board](#how-to-program-the-curiosity-nano-board) chapter.<br><br>

## Setup

The following configurations must be made for this project:

- Clock Control:
  - Clock Source: HFINTOSC
  - HF Internal Clock: 1 MHz
  - Clock Divider: 1

  <br><img src="images/case1_clock_control.PNG" width="600">

- Configuration bits:
  - WDT operating mode: WDT disabled

  <br><img src="images/case1_configuration_bits.PNG" width="600">

- Interrupt Manager:
  - Enable Vectored Interrupt: Yes

  <br><img src="images/case1_interrupt_manager.PNG" width="600">

- CMP1:
  - Enable Comparator: No
  - Mode: asynchronous
  - Hysteresis: 30 mV
  - Positive Input Selection: CIN0+
  - Negative Input Selection: CIN1-
  - Output Polarity: not inverted
  - Comparator Speed: 50 ns high speed
  - Enable Comparator Interrupt: Yes
  - Enable Rising Edge Interrupt: intFlag_pos
  - Enable Falling Edge Interrupt: no_intFlag

  <br><img src="images/case1_comparator.PNG" width="600">

- PWM2:
  - Enable PWM: Yes
  - Clock Source: LFINTOSC
  - Clock Prescaler: 10
  - Mode: Left aligned mode
  - Requested Frequency: 0.5 kHz
  - Output1 Duty Cycle: 50%
  - Period Interrupt Enable: Yes
  - Period Interrupt Postscaler: No postscale

  <br><img src="images/case1_pwm_1.PNG" width="600">
  <br><img src="images/case1_pwm_2.PNG" width="600">

- CLC3:
  - Enable CLC: Yes
  - Logic Cell Mode bits: AND-OR
  - First OR gate input: PWM2_OUT1
  - Second OR gate input: CMP1_OUT

  <br><img src="images/case1_clc.PNG" width="600">

- APM:
  - Enable APM: Yes
  - Clock Source: LFINTOSC
  - Requested Period: 10s
  - APM Events:
    - Start 1: enable CMP1
    - End 1: disable CMP1
    - Start 2: -
    - End 2: -
  - Requested Start 1: 1s
  - Requested End 1: 3s
  - Requested Start 2: 0s
  - Requested End2: 3s

  <br><img src="images/case1_apm_1.PNG" width="600">
  <br><img src="images/case1_apm_2.PNG" width="600">

    The configured APM period is 10s. The Start 1 event, which enables the Comparator peripheral, occurs one second after the period counter started. The End 1 event, which disables the Comparator, occurs 3 seconds after the Start 1 event. The Start 2 and End 2 events are not used in this case. Therefore, the Start 2 event timing is irrelevant, but the End 2 event must occur after or at the same time with the End 1 event.

| Pin | Configuration  |        Description        |
| :-: | :------------: | :-----------------------: |
| RA1 |  Analog input  |        Potentiometer      |
| RA2 |  Analog input  |    Ambient light sensor   |
| RA3 | Digital output |            CMP1           |
| RB1 | Digital output |            PWM2           |
| RB2 | Digital output |            CLC3           |
| RB3 | Digital output |   Analog modules status   |
| RC7 | Digital output |      Speaker status       |

<br><img src="images/case1_pin_grid.PNG" width="600">

| Pin |     Label      |
| :-: | :------------: |
| RB3 |    APMStatus   |
| RC7 |      LED       |

<br><img src="images/case1_pins_configuration.PNG" width="600">

## Demo

Board setup:

<br><img src="images/demo_setup.PNG" width="600">

Logic analyzer screen captures:

<br><img src="images/case1_demo1.png" width="1000">
<br><img src="images/case1_demo2.png" width="1000">


## Summary

This code example shows how to configure the APM to enable and disable the CMP and create a light-sensing alarm. 

<br><br>
[Back to Top](#analog-peripheral-manager-apm--light-sensing-alarm-with-cmp-and-apm-using-the-pic18f56q71-microcontroller-with-mcc-melody)
<br>

## How to Program the Curiosity Nano Board

This chapter demonstrates how to use the MPLAB X IDE to program a PIC® device with an `Example_Project.X`. This applies to other projects.

1.  Connect the board to the PC.

2.  Open the `Example_Project.X` project in MPLAB X IDE.

3.  Set the `Example_Project.X` project as main project.
    <br>Right click the project in the **Projects** tab and then **Set as Main Project**.
    <br><img src="images/Program_Set_as_Main_Project.PNG" width="600">

4.  Clean and build the `Example_Project.X` project.
    <br>Right click the `Example_Project.X` project and select **Clean and Build**.
    <br><img src="images/Program_Clean_and_Build.PNG" width="600">

5.  Select PICxxxxx Curiosity Nano in the Connected Hardware Tool section of the project settings:
    <br>Right click the project and **Properties**.
    <br>Click the arrow under the Connected Hardware Tool, and from the dropdown select **PICxxxxx Curiosity Nano** (click the **SN**).
    <br>Click **Apply** and then **OK**:
    <br><img src="images/Program_Tool_Selection.jpg" width="600">

6.  Program the project to the board.
    <br>Right click the project and then **Make and Program Device**.
    <br><img src="images/Program_Make_and_Program_Device.PNG" width="600">

<br>

- [Analog Peripheral Manager (APM) — Light-sensing Alarm with CMP and APM Using the PIC18F56Q71 Microcontroller with MCC Melody](#analog-peripheral-manager-apm--light-sensing-alarm-with-cmp-and-apm-using-the-pic18f56q71-microcontroller-with-mcc-melody)
  - [Related Documentation](#related-documentation)
  - [Software Used](#software-used)
  - [Hardware Used](#hardware-used)
  - [Operation](#operation)
  - [Setup](#setup)
  - [Demo](#demo)
  - [Summary](#summary)
  - [How to Program the Curiosity Nano Board](#how-to-program-the-curiosity-nano-board)
