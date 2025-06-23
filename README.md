# slast - Linux Last Command Implementation

A simple and efficient implementation of the `last` command for Linux systems. This program reads the `/var/log/wtmp` file and displays login/logout records in a clean, formatted output.

## Features

- **Simple and clean**: Minimal, readable code following Linux philosophy
- **Efficient file reading**: Optimized backward reading from the end of the wtmp file
- **Professional error handling**: Essential error checking without over-engineering
- **Configurable output**: Option to limit the number of displayed records
- **Linux-focused**: Uses standard Linux headers and conventions
- **Cross-platform compilation**: Can compile on Windows (though wtmp file won't exist)

## Installation

### Prerequisites

- GCC compiler (or compatible C compiler)
- Make utility
- Linux system (for full functionality)

### Building

1. Clone the repository:
```bash
git clone https://github.com/VictoKu1/LinuxLast_Command.git
cd LinuxLast_Command
```

2. Build the program:
```bash
make
```

**Note**: The program can compile on Windows but will show "Cannot open /var/log/wtmp" since that file doesn't exist on Windows systems.

## Usage

### Basic Usage

Display all login records:
```bash
./slast
```

Display the last N records:
```bash
./slast 10
```

### Examples

```bash
# Show all login records
./slast

# Show last 5 login records
./slast 5

# Show last 20 records
./slast 20
```

### Output Format

The program displays records in the following format:
```
username    tty          hostname        time
user1       pts/0        192.168.1.100   Dec 15 14:30
user2       system boot                  Dec 15 09:15
```

## Technical Details

### File Format

The program reads from `/var/log/wtmp`, which contains login/logout records in the utmp format. Each record contains:
- Username
- Terminal/line information
- Hostname/IP address
- Timestamp
- Process type (login, logout, boot, etc.)

### Algorithm

1. **File positioning**: Seeks to the end of the wtmp file
2. **Backward reading**: Reads records from newest to oldest
3. **Filtering**: Only displays USER_PROCESS and BOOT_TIME entries
4. **Formatting**: Formats timestamps and aligns output columns
5. **Limiting**: Stops after displaying the requested number of records

### Error Handling

The program includes essential error handling for:
- File access issues
- Invalid command line arguments
- File read errors
- Memory safety

## Code Quality

### Design Philosophy

This implementation follows the **KISS principle** (Keep It Simple, Stupid):
- **Minimal code**: Only essential functionality
- **Clear structure**: Easy to understand and maintain
- **Linux conventions**: Uses standard Linux tools and practices
- **Efficient**: Optimized without unnecessary complexity

### Code Structure

```
slast.c
├── Includes and definitions
├── showtime() - Format and display timestamp
├── show_info() - Display utmp entry
└── main() - File reading and argument handling
```

### Key Features

- **Simple makefile**: Just `make` to build, `make clean` to clean
- **Essential error checking**: Handles common failure cases
- **Clean output**: Professional formatting
- **Memory safe**: Proper bounds checking and null pointer handling
- **Cross-platform compilation**: Works on both Linux and Windows

## Limitations

- **Linux functionality**: Only works fully on Linux systems with wtmp file
- **File permissions**: Requires read access to `/var/log/wtmp`
- **Record types**: Only displays user login and boot time records

## Troubleshooting

### Common Issues

1. **"Cannot open /var/log/wtmp"**:
   - On Linux: Ensure you have read permissions on the file
   - On Windows: This is expected - the file doesn't exist on Windows

2. **"Invalid number"**:
   - Make sure you provide a positive integer as argument

3. **Build errors**:
   - Ensure GCC is installed: `sudo apt-get install build-essential` (Ubuntu/Debian)
   - Or: `sudo yum install gcc make`

