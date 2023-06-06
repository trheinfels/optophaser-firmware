# Optophaser Guitar Pedal - Firmware

This repository contains the firmware sources for an eight stage optophaser guitar effect pedal. In particular, the MCU is used to control the low-frequency oscillator (LFO) altering the analog filter characteristics.


## Features

The following features are currently implemented:

- Variable-frequency wavetable LFO synthesis for sine, rectangle, triangle, and sawtooth waves and mixes between them


These features are supported by hardware but not currently implemented:

- Tap tempo
- Expression pedal
- Firmware update over USB
- Altering the wavetables over USB


## Targets

```bash
make             # Build .elf binary build/optophaser-app.elf
make flash       # Use Black Magic Probe to flash the binary
make debug       # Start GDB session using Black Magic Probe
make debug-tui   # Start GDB session with TUI mode enabled using Black Magic Probe
make doc         # Create doxygen documentation under doc/{html,latex}
make clean       # Clean sources
make dist-clean  # Clean sources and documentation
```


## License

The sources are licensed under GPLv3 or later versions, see [COPYING](COPYING).
