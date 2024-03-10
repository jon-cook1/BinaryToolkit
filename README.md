# Binary Toolkit

This project, developed for COSC 208: Introduction to Computer Systems (Fall 2023), is a command-line toolkit for performing binary number conversions and calculations. It supports converting binary to decimal (and vice versa), arithmetic operations between binary numbers, and provides insight into the conversion process.

## Features

- **Binary to Decimal Conversion**: Converts binary numbers to their decimal equivalents and vice versa. It also prints the step-by-step conversion process for educational purposes.
- **Binary Arithmetic**: Supports addition and subtraction of binary numbers, including handling of signed binaries.
- **Debugging Tools**: Offers a detailed walkthrough of arithmetic operations, aiding in understanding binary calculations.

## Usage

To use the binary toolkit, compile the C file and run it from the command line with appropriate arguments. Here are the basic commands:

- **Convert Binary to Decimal**: 
`./binarytoolkit 0b1101 u`

Where `0b1101` is the binary number and `u` indicates an unsigned binary (use `s` for signed).

- **Convert Decimal to Binary**: 
`./binarytoolkit 13 8`

Where `13` is the decimal number to convert and `8` is the bit size of the resulting binary.

- **Binary Arithmetic**: 
`./binarytoolkit 0b1010 + 0b0101`

Where `0b1010` is the first binary number, `+` is the operation (use `-` for subtraction), and `0b0101` is the second binary number.

## Project Structure

- The project includes functions for both conversions and arithmetic, with a focus on educational insights into binary computations.
- Debugging and verbose modes provide a step-by-step breakdown of the internal logic, useful for understanding the underpinning mathematical principles.

## Development

This toolkit was developed to aid in the understanding of binary number systems and arithmetic, leveraging basic C programming concepts. It features rudimentary implementations intended for educational use, with potential for optimization and enhancement.

## Acknowledgments

This project was a collaborative effort with [Kyle Leclair]



