Here's the `README.md` for your log analysis tool following the requested format:

```markdown
# LogAnalyzerCLI

## Project Description
This program analyzes log files with timestamped entries, providing filtering capabilities by log level and time range. It processes standard log formats (`[timestamp] LEVEL: message`) and offers both console output and file export options.

## Learning Objectives
- Implement log file parsing and analysis
- Create advanced filtering with multiple criteria
- Work with timestamp comparisons
- Generate summary statistics
- Handle various log file formats

## Technologies Used
- **C++11** (or later)
- **<algorithm>** for string processing (e.g., `std::transform` for case conversion, `std::find` for searching)
- **<map>** for level counting
- **Time range filtering** with ISO-like timestamps (`YYYY-MM-DD_HH:MM:SS`)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o log_analyzer
   ```
2. Basic usage:
   ```bash
   ./log_analyzer <log_file> [options]
   ```

## Example Usage
1. Basic analysis:
   ```bash
   ./log_analyzer app.log
   ```
   Output:
   ```
   Analyzed 150 lines.
   Log Level Counts:
     INFO: 85
     WARNING: 42
     ERROR: 23

   Matching Entries (150):
   [2023-11-15_08:30:45] INFO: System started
   ...
   ```

2. Filtered analysis:
   ```bash
   ./log_analyzer app.log --level ERROR --start 2023-11-15_08:30:00
   # Note: The `--start` option expects a timestamp in the format `YYYY-MM-DD_HH:MM:SS`.
   ```
   Output:
   ```
   Analyzed 150 lines.
   Log Level Counts:
     INFO: 85
     WARNING: 42
     ERROR: 23

   Matching Entries (3):
   [2023-11-15_08:32:18] ERROR: Connection failed
   ...
   ```

## Key Features
- Comprehensive log statistics
- Case-insensitive level filtering
- Time range filtering
- Whitespace trimming
- File export capability
- Detailed error reporting

## Output Statistics
For each analysis, the tool provides:
- Total lines processed
- Count per log level
- Number of matching entries
- Full display of filtered entries

- Timestamps are compared lexicographically, meaning they are treated as strings for comparison. This ensures chronological order when timestamps are consistently formatted as `YYYY-MM-DD_HH:MM:SS`.
- Timestamps are compared lexicographically
- Empty lines and malformed entries are skipped
