# 05_Strategy Game Bot (Tic-Tac-Toe AI)

## Description

This project implements a Tic-Tac-Toe game where a human player competes against an AI bot. The AI uses the Minimax algorithm to play optimally, ensuring it never loses if played correctly. The game is played in the terminal, with the board displayed after each move and prompts for user input.

---

## Features

- Play Tic-Tac-Toe against an unbeatable AI
- Human is `X`, AI is `O`
- Board displayed in ASCII after every move
- Input validation for human moves
- AI uses the Minimax algorithm for perfect play
- Detects win, loss, or tie and announces the result

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o strategy_game_bot -std=c++11
   ```

2. **Run the game:**
   ```bash
   ./strategy_game_bot
   ```
   or on Windows:
   ```powershell
   .\strategy_game_bot.exe
   ```

3. **How to play:**
   - Enter your move as two numbers (row and column), both between 0 and 2, separated by a space.
   - Example: `1 2` (places your `X` in row 1, column 2)

---

## Example Output

```
Tic-Tac-Toe - You are X, AI is O
Enter row and column (0-2) separated by space

   |   |   
-----------
   |   |   
-----------
   |   |   

Your move (row col): 0 0

 X |   |   
-----------
   |   |   
-----------
   |   |   

AI is thinking...

 X |   |   
-----------
   | O |   
-----------
   |   |   

...
It's a tie!
```

---

## Learning Objectives

- Understand and implement the Minimax algorithm for game AI
- Practice board representation and move validation in C++
- Learn about turn-based game loops and user interaction in the terminal

---

This project provides a hands-on introduction to AI for turn-based games and demonstrates how to build an unbeatable bot using classic algorithms.