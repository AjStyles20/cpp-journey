# 04_Command-Line Args

## Project Description
This C++ program demonstrates how to handle command-line arguments for flexible input processing. It supports options for displaying help, processing a file, processing a number, and enabling verbose output. The code provides a template for building command-line utilities with argument parsing and error handling.

## Features
- Display help information (`-h` or `--help`)
- Process a specified file (`-f <file>`)
- Process a specified number (`-n <number>`)
- Enable verbose output (`-v` or `--verbose`)
- Error handling for missing or invalid arguments

## Usage

### Compilation
```bash
g++ -std=c++11 main.cpp -o CommandLineArgs
```

### Running
```bash
./CommandLineArgs [options] [arguments]
```
or on Windows:
```bash
CommandLineArgs.exe [options] [arguments]
```

### Options
- `-h`, `--help` &nbsp;&nbsp;&nbsp;&nbsp; Show help message and exit
- `-f <file>` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Process the specified file
- `-n <number>` &nbsp;&nbsp; Process the specified number
- `-v`, `--verbose` &nbsp; Enable verbose output

### Examples
```bash
./CommandLineArgs -f data.txt -n 42
./CommandLineArgs --verbose -n 100
./CommandLineArgs -h
```

## Example Output
```
Verbose mode enabled.
Processing file: data.txt
File 'data.txt' would be processed here.
Processing number: 42
Number 42 would be processed here.
```

## Error Handling
- Prints an error and help message for unknown or missing arguments.
- Handles invalid number formats and out-of-range values.

## Customization
- Add your file or number processing logic in the `processFile` and `processNumber` functions.

## Notes
- Arguments can be provided in any order.
- At least one of `-f` or `-n` is required unless using `-h`/`--help`.