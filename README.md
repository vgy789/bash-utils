[На русском 🇷🇺](README_RUS.md)

# Simple Bash Utils

This project implements simplified versions of `cat` and `grep` utilities adhering to the POSIX.1-2017 standard.

- [Cat Implementation](#cat-implementation)
- [Grep Implementation](#grep-implementation)
- [Build and Usage](#build-and-usage)
- [License](#license)

## Features

### Cat Implementation
- Supports key options: -b, -e, -n, -s, -t, -v
- Efficient handling of multiple input files
- Proper handling of multiple EOF characters within files
- Platform-specific behavior:
    - When compiled on macOS, simulates macOS cat utility behavior
    - When compiled on Linux, simulates GNU cat utility behavior

### Grep Implementation
- Support for basic regular expressions (BRE)
- Key options: -e, -i, -v, -c, -l, -n, -h, -s, -f, -o
- Regular expressions stored in linked list for multiple pattern support
- Bit fields used for flag management

## Build and Usage

```bash
make
./cat [OPTIONS] [FILE...]
./grep [OPTIONS] [PATTERN] [FILE...]
```

## License
This project is licensed under the Apache License, Version 2.0. See LICENSE file for details.
