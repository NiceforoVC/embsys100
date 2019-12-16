# EMBSYS100 - AU19, Assignment 08 (Bonus assignment)

## Goal

The goals for the assignment this week:

1. Explore the use of PWM on our NUCLEO-F401RE board.

## Problems

### 1. Bonus.

*a. Study the tutorial: https://www.waveshare.com/wiki/STM32CubeMX_Tutorial_Series:_PWM*

*b. Use the STM32CubeMX similar to what’s described in the tutorial in order to generate the code that connects one of the PWM channels to our user LED.*

I used the STM32CubeMX to connect the LED to TIM2 in order to setup the PWM in the board.

First I selected the function I wanted to connect to the LED. In this case, I selected TIM2_CH1.

![Image of TIM2 selection](https://github.com/NiceforoVC/embsys100/blob/master/assignment08/TIM2_selection.png)

Then I configured TIM2 Channel 1 in the peripherals section to be used as PWM generator.

![Image of TIM2 configuration 1](https://github.com/NiceforoVC/embsys100/blob/master/assignment08/TIM2_configuration_1.png)

*c. Modify the code generated similar to the tutorial in order to control the LED blinking and brightness.*

*d. Create a video demonstrating the brightness of the LED changing overtime.*

*e. Submit your video along with your entire IAR project to your GitHub.*

***Video copied to the assignment folder:***

Name | Description 
------ | ------ 
LED_PWM_NICEFORO.mp4 | LED changing brightness using PWM in a loop

*f. Describe one problem you encountered while working on this project, and share what was your approach to solve it.*

The only problem I encounter was to understand the system clock in order to setup the parameters of the PWM for the STM32nucleo. 
I reviewed the User Manual for the STM32 Nucleo board to understand what clock is used, there I found that the board uses the 
MCO output from ST-Link as input clock, this is fixed at 8 MHz. With that I setup the project to use similar time settings as the 
tutorial example. In this case, since the system clock is 8 MHz, we need to setup the prescaler to 80 to get the 100 KHz time base 
of the tutorial example, and use the same 2000 value in the period, to have a 20 ms period.

See below the configuration I used for TIM2 in the project:

![Image of TIM2 configuration 2](https://github.com/NiceforoVC/embsys100/blob/master/assignment08/TIM2_configuration_2.png)


**Hint:** *Refer to the STM32F401 Reference Manual RM0368 for details on TIMERs and PWM.*