# 6_ConfigParserCLI

## Project Description
This program implements a command-line configuration file parser that reads, modifies, and saves key-value pairs in configuration files. It features case-insensitive key lookup and preserves file formatting while handling various edge cases.

## Learning Objectives
- Implement configuration file parsing
- Create a command-line interface (CLI)
- Handle file I/O operations with error checking
- Work with STL maps for key-value storage
- Process strings with trimming and case conversion

## Technologies Used
- **C++11** (or later)
- **<map>** for configuration storage
- **<algorithm>** for string processing
- **Case-insensitive** key comparison
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o ConfigTool
   ```
2. Run with commands:
   ```bash
   ./ConfigTool 
   ```

## File Format Requirements
Configuration files should:
- Contain key-value pairs (`key = value`)
- Support comments (lines starting with `#`)
- Be in plain text format

Example `settings.cfg`:
```
# Server configuration
port = 8080
hostname = localhost
timeout = 30
```

## Available Commands
| Command | Arguments | Description |
|---------|-----------|-------------|
| `get`   | `<key>`   | Get value for specified key |
| `set`   | `<key> <value>` | Update or add key-value pair |
| `list`  | - | Show all configuration entries |
| `help`  | - | Display usage information |

## Example Usage
1. View all settings:
   ```bash
   ./ConfigTool settings.cfg list
   ```
   Output:
   ```
   Current configuration:
     port = 8080
     hostname = localhost
     timeout = 30
   ```

2. Get specific value:
   ```bash
   ./ConfigTool settings.cfg get timeout
   ```
   Output:
   ```
   30
   ```

3. Update configuration:
   ```bash
   ./ConfigTool settings.cfg set port 9090
   ```
   Output:
   ```
   Updated port = 9090
   ```

## Key Features
- Case-insensitive key lookup
- Whitespace trimming
- Comment preservation
- Error handling for:
  - Missing files
  - Invalid syntax
  - Missing keys
- File writing with original formatting

## Error Handling
The program detects and reports:
- Missing or unreadable config files
- Invalid command syntax
- Missing configuration keys
- File write permissions issues
- Malformed configuration lines

## Notes
- Keys are converted to lowercase for case-insensitive comparison
- Original values maintain their case
- Comments and empty lines are preserved when reading
- Can be extended with:
  - Support for sections (`[section]`)
  - Data type validation (numbers, booleans)
  - Environment variable expansion
  - Configuration file templates
  - Multi-file configuration
