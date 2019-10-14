# Two’s Complement

*Why use two’s complement to represent negative numbers?*

Two’s complement is a method to represent negative binary numbers in a signed binary number system.

In two’s complement, the positive numbers remained unchanged. A negative number is represented by a binary number, which when added to its corresponding positive equivalent results in zero.

To compute the two’s complement of a negative number, we do the following:

1.	Get the positive value in binary.
2.	Invert all bits.
3.	Add 1 (we ignore the overflow bit if there is one).

Example:

To get the two’s complement value of -27<sub>10</sub> we do:
1.	Get the positive value in binary: 27<sub>10</sub> = 0001 1011<sub>2</sub>
2.	Invert all bits: 1110 0100<sub>2</sub>
3.	Add 1: 1110 0101<sub>2</sub>

The main advantage of two’s complement compared to one’s complement (the other method to represent signed binary numbers) is that there is no double-zero problem (one’s complement has a “positive zero” and a “negative” zero), plus the fundamental arithmetic operations of addition, subtraction, and multiplication are identical to those for unsigned binary numbers, and are easier to implement in a computer system.
