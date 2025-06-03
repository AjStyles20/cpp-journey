# 2_WordFrequencyAnalyzer

## Project Description
This program analyzes text input to count word frequencies, displaying results sorted by occurrence count. It demonstrates text processing, map operations, and custom sorting in C++.

## Learning Objectives
- Process and normalize text input
- Count occurrences using map data structures
- Implement custom sorting algorithms
- Handle multi-line user input
- Perform case-insensitive comparisons

## Technologies Used
- **C++11** (or later)
- **STL map** for frequency counting
- **STL vector** and **algorithm** for sorting
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o WordFrequency
   ```
2. Run the executable:
   ```bash
   ./WordFrequency    # Linux/Mac
   .\WordFrequency.exe # Windows
   ```

## Usage Instructions
1. Enter your text when prompted
2. Press Enter after each line
3. Press Enter twice to finish input
4. The program will display:
   - All words (normalized to lowercase)
   - Their occurrence counts
   - Sorted by frequency (highest first)

## Example Usage
```
Enter a paragraph of text (press Enter twice to finish):
The quick brown fox jumps over the lazy dog.
The fox was quick and the dog was lazy.

Word Frequencies (sorted by count):
--------------------------------
the: 4
fox: 2
quick: 2
was: 2
dog: 2
lazy: 2
brown: 1
jumps: 1
over: 1
and: 1
```

## Key Features
- Case-insensitive word counting
- Punctuation stripping
- Multi-line text input
- Frequency-based sorting
- Clean, formatted output

## Text Processing
- Converts all words to lowercase
- Removes non-alphabetic characters
- Handles apostrophes and hyphens as part of words
- Preserves word boundaries

## Notes
- Requires C++11 or later
- Input terminates on double Enter
