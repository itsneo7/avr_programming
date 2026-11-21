# AVR Programming with Embedded C

A hands-on learning repository for understanding **AVR microcontrollers** and developing firmware in **Embedded C**. It is intended as a practical companion to learning how a microcontroller works: configure its registers, control its I/O pins, use on-chip peripherals, and build small programs that interact with real hardware.

> **Learning goal:** Move beyond writing C programs for a computer and learn how C code controls the hardware inside a microcontroller.

---
## About This Repository

This repository is a collection of AVR programming practice work organised into numbered exercise folders. The aim is to build understanding progressively through code and experimentation.

The examples are intended to help learners become comfortable with:

- The structure and operation of an AVR microcontroller.
- The relationship between C code, CPU registers, memory, and peripheral hardware.
- Direct register-level programming instead of depending entirely on high-level libraries.
- Reading a datasheet and using it to configure a peripheral.
- Compiling, flashing, testing, and debugging embedded firmware.

The exact registers, pin names, peripheral features, and fuse settings depend on the AVR device being used. Always check the datasheet for your specific microcontroller before adapting an example.

## What You Will Learn

| Area | Concepts |
|---|---|
| Embedded C fundamentals | Data types, operators, bitwise operations, functions, pointers, and `volatile` |
| AVR architecture | CPU, registers, SRAM, Flash, EEPROM, stack, and interrupt vectors |
| GPIO | Input/output configuration, pull-up resistors, switches, and LEDs |
| Timing | Clock sources, prescalers, delays, and timer/counter modules |
| Timers and PWM | Overflow, compare match, input capture, and pulse-width modulation |
| Interrupts | External interrupts, peripheral interrupts, interrupt service routines, and shared data |
| ADC | Analog input, reference voltage, resolution, and conversion results |
| Serial communication | UART/USART, SPI, and I²C/TWI fundamentals |
| Memory and reliability | EEPROM, watchdog timer, reset causes, and low-power operation |
| Development workflow | Building, generating HEX files, programming, testing, and debugging |

Not every AVR device supports every peripheral listed above. Check the device datasheet before choosing an exercise or peripheral.

## Prerequisites

You will get the most out of this repository if you have:

- Basic knowledge of the C programming language.
- A basic understanding of digital electronics (voltage, current, logic levels, and resistors).
- An AVR development board or a compatible AVR microcontroller setup.
- A USB programmer or bootloader-based upload method supported by your board.
- Willingness to read the microcontroller datasheet and experiment carefully.

You do not need to master all these topics before starting. Learn the C and electronics concepts alongside the practical exercises.

## Hardware and Software

### Hardware

Choose a board or bare-metal setup based on the AVR device used in your exercises. Common learning options include boards built around ATmega-family microcontrollers, but this repository is not limited to one specific device.

You may also need:

- A USB-to-serial adapter or AVR ISP programmer, depending on the board and upload method.
- Breadboard and jumper wires.
- LEDs and suitable current-limiting resistors.
- Push buttons, potentiometers, and other basic components for peripheral experiments.
- A multimeter for checking supply voltage and circuit connections.

### Software

A typical command-line AVR development environment includes:

| Tool | Purpose |
|---|---|
| **avr-gcc** | Compiles Embedded C source code for AVR devices |
| **avr-libc** | Provides device definitions, standard support, and AVR-specific headers |
| **avr-binutils** | Includes tools such as `avr-objcopy` for converting firmware files |
| **avrdude** | Programs supported AVR microcontrollers |
| **Make** (optional) | Automates repeatable build commands |
| **Microchip Studio** (optional) | IDE and debugging environment for supported AVR devices and tools |
| **VS Code** (optional) | Source-code editor; configure the AVR toolchain separately |

Install the toolchain appropriate for your operating system and target MCU. Confirm that the compiler, device support files, and programmer support your exact AVR part.

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/itsneo7/avr_programming.git
cd avr_programming
```

### 2. Explore the exercises

Open the numbered exercise folders and read the source code before running it. Start with the introductory material and progress towards exercises involving timers, interrupts, ADC, and communication peripherals.

The folder names alone may not describe the hardware or objective. Check the comments and source files in each exercise, and verify the target MCU before compiling.

### 3. Identify your target microcontroller

Find the exact part number printed on your chip or listed in your development board documentation (for example, an ATmega-series part). Use that device's datasheet to confirm:

- Supported peripherals and register names.
- I/O pin mapping and alternate pin functions.
- Clock frequency and clock-source configuration.
- Supply-voltage and electrical limits.
- Fuse-bit and programming requirements.

### 4. Set the clock frequency

Many AVR examples use the `F_CPU` macro to tell avr-libc the CPU clock frequency assumed by the program. Define it to match the actual clock configuration of your microcontroller.

For example, `16000000UL` represents 16 MHz:

```c
#define F_CPU 16000000UL
```

This definition does **not** set the physical clock by itself. The actual clock depends on the MCU, clock source, fuse configuration, and any clock prescaler settings.

## Compile and Generate a HEX File

The following is an example command-line workflow using an **ATmega328P** as the target. Replace the MCU name, clock frequency, source filename, and options to match your hardware.

### 1. Compile the source file

```bash
avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -std=gnu11 -Wall -Wextra \
  -o main.elf main.c
```

### 2. Convert the ELF file to Intel HEX format

```bash
avr-objcopy -O ihex -R .eeprom main.elf main.hex
```

### 3. Check the generated files

- `main.elf` — compiled ELF firmware, useful for inspection and debugging.
- `main.hex` — Intel HEX firmware file commonly used by programming tools.

To inspect memory usage, you can use:

```bash
avr-size --format=avr --mcu=atmega328p main.elf
```

> **Important:** These commands are examples for the ATmega328P. They are not universal AVR commands. Select the correct `-mmcu` value and verify the clock and compiler options for your specific target.

## Upload Firmware to an AVR

`avrdude` can program many AVR devices through supported programmers and bootloaders. The correct programmer type, MCU identifier, port, and baud rate depend on your hardware.

Example only — a common serial bootloader setup for an ATmega328P board on a Windows COM port may look like this:

```bash
avrdude -v -p m328p -c arduino -P COM3 -b 115200 \
  -U flash:w:main.hex:i
```

Before running the command, confirm all of the following:

1. The MCU identifier matches the installed microcontroller.
2. The programmer (`-c`) matches your programmer or bootloader.
3. The port (`-P`) is the correct serial or programmer port.
4. The baud rate is supported by the bootloader, if one is being used.
5. The board is powered correctly and connected as required.

For an ISP programmer, use its corresponding `avrdude` programmer setting and connection method. Do not copy the example command blindly.

## A Simple Embedded C Example

The following example toggles an LED using the GPIO registers of an **ATmega328P**. It assumes the LED and its current-limiting resistor are connected to PB5 in an appropriate active-high configuration.

```c
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Configure PB5 as an output.
    DDRB |= (1 << DDB5);

    while (1)
    {
        // Set PB5 HIGH.
        PORTB |= (1 << PORTB5);
        _delay_ms(500);

        // Set PB5 LOW.
        PORTB &= ~(1 << PORTB5);
        _delay_ms(500);
    }
}
```

### Understanding the register operations

- `DDRB` is the data-direction register for Port B on the ATmega328P.
- Setting bit `DDB5` configures PB5 as an output.
- `PORTB` controls the output level when the pin is configured as an output.
- `|=` sets a bit without changing the other bits in the register.
- `&= ~` clears a bit while preserving the other bits.
- `_delay_ms()` is provided by avr-libc; its timing calculation depends on the correct `F_CPU` definition and compiler optimisation settings.

This register and pin example is device-specific. Other AVR families may use different register names, pin mappings, or peripheral architectures.

## Suggested Learning Roadmap

A practical sequence for learning AVR and Embedded C is:

1. **C for embedded systems** — integer types, bitwise operators, pointers, macros, header files, and `volatile`.
2. **Microcontroller fundamentals** — architecture, clock, reset, Flash, SRAM, EEPROM, and registers.
3. **GPIO programming** — configure pins, blink LEDs, read switches, and use internal pull-ups.
4. **Timers and counters** — understand prescalers, overflow, compare match, and accurate time measurement.
5. **PWM generation** — control LED brightness or the speed of a suitable DC motor driver.
6. **Interrupts** — respond to external events and peripheral conditions without continuously polling.
7. **ADC** — read analog signals from sensors and potentiometers.
8. **Serial communication** — exchange data using UART/USART, SPI, and I²C/TWI.
9. **Other MCU features** — EEPROM, watchdog, sleep modes, and reset handling.
10. **Small projects** — combine GPIO, timers, interrupts, sensors, and communication into complete applications.

Try to understand the register configuration and the reason behind each setting rather than copying code without understanding it.

## Working with the Exercises

For each exercise, follow a repeatable process:

1. Read the objective and inspect the source code.
2. Identify the target MCU and the peripherals being used.
3. Find the relevant registers and bit definitions in the datasheet.
4. Draw or review the circuit and verify the pin connections.
5. Compile the code and resolve warnings or errors.
6. Program the microcontroller using the correct upload method.
7. Test the behaviour and compare it with the expected result.
8. Record what you learned and any device-specific changes you made.

When adding to the repository, keep each exercise focused, use meaningful filenames, and add comments that explain non-obvious register settings.

## Troubleshooting

| Problem | Things to check |
|---|---|
| `avr-gcc` or `avrdude` command not found | Install the relevant tool and add its executable directory to your system `PATH`. |
| Device not recognised by the compiler | Check the `-mmcu` value and confirm that the installed toolchain supports the target. |
| Programmer cannot connect | Check wiring, power, programmer type, selected port, and ISP/bootloader configuration. |
| Firmware uploads but does not behave as expected | Check the clock source, `F_CPU`, fuse configuration, pin mapping, and circuit wiring. |
| Delay timing is incorrect | Verify the actual CPU clock, `F_CPU`, and compiler optimisation settings. |
| Peripheral does not work | Check the datasheet for clock enable, pin multiplexing, register setup, and required timing. |
| Unexpected behaviour after enabling interrupts | Check interrupt configuration, shared variables, ISR execution time, and `volatile` usage where appropriate. |

## Good Embedded C Practices

- Prefer fixed-width integer types such as `uint8_t` and `uint16_t` from `<stdint.h>` when the required width matters.
- Use bit masks and bitwise operations to change individual register bits without unintentionally modifying others.
- Use `volatile` for variables that can change outside the normal program flow, such as values shared with an interrupt service routine or hardware-mapped registers. It is not a general-purpose replacement for proper concurrency protection.
- Keep interrupt service routines short. Avoid lengthy delays and blocking operations inside an ISR.
- Initialise peripherals explicitly and document important register settings.
- Use clear names for constants, masks, and functions.
- Check compiler warnings instead of ignoring them.
- Avoid assuming that register names or peripheral behaviour are identical across different AVR families.
- Keep hardware-specific configuration separate where practical so code can be adapted more easily.

## Safety Notes

- Check the MCU datasheet and development-board documentation before wiring anything.
- Never exceed the specified supply voltage, input voltage, or per-pin current limits.
- Use a current-limiting resistor with a bare LED.
- Do not drive motors, relays, or other high-current loads directly from an MCU pin. Use a suitable driver circuit.
- Disconnect power before changing circuit connections.
- Be careful when changing fuse bits: an incorrect clock or programming configuration can make a device difficult to access with an ordinary programmer.

## Useful References

- [Microchip Technology](https://www.microchip.com/) — AVR product information, datasheets, application notes, and development tools.
- [AVR-LibC documentation](https://www.nongnu.org/avr-libc/) — AVR-specific C library documentation and examples.
- [GNU AVR Toolchain](https://gcc.gnu.org/) — GCC compiler project and documentation.
- [AVRDUDE](https://github.com/avrdudes/avrdude) — programming utility for supported AVR devices.

**The datasheet for your exact microcontroller should be your primary reference** for register definitions, electrical limits, clock configuration, and peripheral operation.

## Contributing

Suggestions, corrections, and additional practical examples are welcome.

When contributing:

1. Keep examples focused on one concept where possible.
2. Mention the exact AVR device and any required clock assumptions.
3. Include wiring details when external components are required.
4. Explain important register configurations in comments or documentation.
5. Verify that the code compiles for the stated target and clearly mention any untested hardware assumptions.
re. Understand the registers. Build with Embedded C.</b>
</p>
