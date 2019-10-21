# EMBSYS100 - AU19, Assignment 02

## Goal
The goals for the assignment this week:
1. To explore the IAR IDE and the different debug views.
2. Get a better understanding of machine instructions, addresses, variables and pointers.

## Setup
1. Create a new project in IAR following the steps from the slide deck
2. Create a counter local variable and increment the counter several times.
3. Run the program in the simulator environment and answer the following questions:

## Observe and Answer

### 1. Inject 0x7FFFFFFF for the "counter" value in the variable window, then step thru the program only once to increment "counter".
*a) What is the value of the “counter” from the “Locals” window?*

The value of counter is **-2147483648** in the Locals window

*b) What is the value of the “counter” in the “Register” window?*

The value of counter is **0x80000000** in the Register window

*c) Which flags are set in the APSR register? Explain why?*

Flags N(Negative) and V(Overflow) are set in the APSR register.

![Image of flags in simulator run 1c](https://github.com/NiceforoVC/embsys100/blob/master/assignment02/flags_1c.png)

This is because the result is negative and an overflow condition happened (the result doesn't fit in the data type).

The flags in APSR are: 

Name | Description
---- | -------------
N | Negative condition flag (set when result is negative)
Z | Zero condition flag (set when result is zero)
C | Carry condition flag (set when there is a carry bit in the result)
V | Overflow condition flag (set when there is an overflow condition in the result)
Q | Overflow or saturation flag (set when saturation has occurred in saturating arithmetic instructions, or when overflow has occurred in certain multiply instructions)
GE | Greater than or equals flags (set by the parallel add and subtract instructions. They are used by the SEL instruction to perform byte-based selection from two registers)

### 2. If your write all Fs (0xFFFFFFFF) in the Register value for "counter" then step thru the program once to increment "counter".
*a) What happens to the value of “counter” in the “Locals” window?*

The value of counter changes from **-1** to **0** in the Locals window

*b) What flags, if any, are set in the APSR?*

The Z(Zero) and C(Carry) flags are set because incrementing 0xFFFFFFFF by one produces **0x1**00000000. The 0x1 is the Carry, and the final result is zero.

![Image of flags in simulator run 2b](https://github.com/NiceforoVC/embsys100/blob/master/assignment02/flags_2b.png)

### 3. Change the "counter" variable type in your code to "unsigned". Inject the value "0x7FFFFFFF" then step thru the program to increment the "counter" once:
*a) What is the value of “counter” in the “Locals” window after incrementing for each value?*

The value of counter is **2147483648** in the Locals window

*b) What flags, if any, are set in the APSR? Explain why?*

Same flags as in 1c, the reason is because the flags are set based on the signed two's complement result, regardless of the data type of the variables in the program.


### 4. Change the "counter" variable type in your code to "unsigned". Inject the value "0xFFFFFFFF" then step thru the program to increment the "counter" once:
*a) What is the value of “counter” in the “Locals” window after incrementing for each value?*

The value of counter changes from **4294967295** to **0** in the Locals window

*b) What flags, if any, are set in the APSR? Explain why?*

Same as in 2b. In both cases the flags are set the same because the operations are performed using two's complements.

### 5. Move the "counter" variable outside of main (at the top of the file):
*a) What is the scope of the variable "counter"?*

The scope of the variable now is global.

*b) Is it still visible in the "Locals" view?*

No, it is no longer visible in the Locals view.

*c) In which window view can we track "counter" now?*

We have 2 options:

1. Use the **Watch window** to add the variable name to see the value.
2. Use one of the **Memory windows** and locate the address of the global variable. 

*d) What is the address of the “counter” variable in memory?*

The address of the counter variable in memory is **0x20000000**.

### 6. Change the source code to the following, then run the program still in the simulator:
```
int counter = 0x0;
int main() {
  int *p_int = (int *)0x20000000;
  ++(*p_int);
  ++(*p_int);
  ++(*p_int);
  counter ++;
  return 0;
}
```
*a) What is the value of "counter" at the end of the program (halting at the return 0 statement)*

The final value of counter is **4**.

![Image of simulator run](https://github.com/NiceforoVC/embsys100/blob/master/assignment02/Simulator_Run.png)

*b) Explain why the counter value has changed?*

First we used pointers to access the memory address of the **counter** variable, and directly manipulated the content value.
Then in the last statement: `counter ++`, we used the variable and incremented it one last time. 

### 7. Change the setting of IAR to run the same program on the evaluation board:
*a) What is the address where "counter" is stored?*

It is stored in address **0x20000000**.

*b) Is the “counter” variable stored in RAM or ROM?*

It is stored in **RAM**. We can see it in the RAM section of the memory window.

![Image of Board Run Memory Window](https://github.com/NiceforoVC/embsys100/blob/master/assignment02/Board_Run_MemoryWindow.png)

It matches the definition of the Cortex M4 memory map.

![Image of Cortex M4 Memory Map](https://github.com/NiceforoVC/embsys100/blob/master/assignment02/Cortex_M4_MemoryMap.png)

*c) What is the value of “counter” at the end of the program (halting at the return 0 statement).*

The final value of counter is **4**.

![Image of board run](https://github.com/NiceforoVC/embsys100/blob/master/assignment02/Board_Run.png)
