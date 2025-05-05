# cpp-journey: 30–75 Days of C++ Projects

**A structured, progressive series of daily C++ projects** designed to take you from beginner syntax through advanced robotics and AI topics. Document your journey, strengthen your resume, and build a portfolio with hands-on, real‑world tasks.



## Table of Contents

1. [Overview](#overview)
2. [Repository Structure](#repository-structure)
3. [Weekly Themes](#weekly-themes)
4. [Getting Started](#getting-started)
5. [Daily Workflow](#daily-workflow)
6. [Requirements & Tools](#requirements--tools)
7. [Contributing & Feedback](#contributing--feedback)
8. [License & Acknowledgments](#license--acknowledgments)



## Overview

This repo contains **one C++ project per day** over a period of **1 to 2.5 months** (30–75 days). Each project focuses on a specific concept or skill:

* **Weeks 1–2:** C++ fundamentals, control flow, functions, arrays, pointers
* **Weeks 3–4:** Object‑oriented programming, inheritance, polymorphism
* **Week 5:** File I/O, error handling
* **Week 6:** STL containers & algorithms
* **Weeks 7–8:** Robotics simulations (line following, obstacle avoidance, control loops)
* **Weeks 9–10:** AI algorithms (search algorithms, state machines, pathfinding)

By the end of this journey, you’ll have a **robust portfolio** of C++ code and practical experience relevant to **AI & robotics development**.



## Repository Structure

```
cpp-journey/
├── README.md               # This overview
├── .gitignore              # Exclude binaries and build artifacts
├── Stage01_Basics/         # Learning phase 1: C++ fundamentals
│   ├── 01_HelloWorld/      # Mini-project 1
│   │   ├── main.cpp
│   │   └── README.md       # Project-specific README
│   ├── 02_Calculator/
│   │   ├── main.cpp
│   │   └── README.md
│   └── 03_TemperatureConverter/
│       ├── main.cpp
│       └── README.md
├── Stage02_FunctionsPointers/
│   ├── 01_ModularMath/
│   ├── 02_StringReversal/
│   └── …
└── StageNN_Capstone/         # Final or advanced projects
    ├── src/                # If multi-file, include headers and sources
    ├── README.md
    └── docs/               # Optional diagrams or notes
```

> **Tip:** Use the **StageXX\_Theme** + **Sequence\_Number\_ProjectTitle** naming convention for clarity and flexibility.



## 🗓 Weekly Themes

| Week | Theme                              | Focus Areas                                                           |
| :--: | :--------------------------------- | :-------------------------------------------------------------------- |
|   1  | Syntax & Control Flow              | variables, loops, conditionals, I/O                                   |
|   2  | Functions, Arrays & Pointers       | modular code, dynamic memory, pointers                                |
|   3  | Object‑Oriented Programming        | classes, constructors, inheritance, polymorphism                      |
|   4  | File I/O & Error Handling          | file streams, CSV parsing, exceptions, CLI arguments                  |
|   5  | STL & Data Structures              | vectors, maps, stacks, queues, algorithms                             |
|   6  | Algorithms & Recursion             | sorting, searching, BFS/DFS, recursion                                |
|   7  | Robotics Simulation I              | line following, obstacle avoidance, sensor processing, state machines |
|   8  | Robotics Simulation II             | PID control, kinematics, grid navigation, sensor fusion               |
|   9  | AI Search & State Machines         | BFS, DFS, A\*, FSM, minimax                                           |
|  10  | Capstone & Advanced AI Integration | Dijkstra’s, advanced FSM, simple ML, full project integration         |



## 🚀 Getting Started

1. **Clone the repo**

   ```bash
   git clone https://github.com/<your-username>/cpp-journey.git
   cd cpp-journey
   ```
2. **Configure VS Code**

   * Install the C/C++ extension by Microsoft.
   * Make sure your compiler (g++) is in PATH.
3. **Explore Day Folders**
   Each `DayXX_Title` folder contains its own `main.cpp` and a project-specific `README.md` with instructions.



## Daily Workflow

1. **Create / Enter** `DayXX_Title` folder.
2. **Edit** `main.cpp` (and other files) in VS Code.
3. **Compile & Run** in the integrated terminal:

   ```bash
   g++ main.cpp -o app   # or use -o <exe_name>
   ./app                # on Windows: .\app.exe
   ```
4. **Write** or update the project’s `README.md`:

   * Describe the project, objectives, and run instructions.
5. **Commit & Push** your changes:

   ```bash
   git add DayXX_Title/*
   git commit -m "Add DayXX: <Project Title>"
   git push
   ```


## Requirements & Tools

* **Compiler:** GNU g++ (C++14 or later)
* **Editor:** VS Code (C/C++ extension by Microsoft)
* **Version Control:** Git & GitHub
* **Optional Libraries:**

  * SFML (for future graphical projects)
  * Eigen or Armadillo (for linear algebra)



## Contributing & Feedback

* Feel free to open issues or pull requests with improvements.
* Share tips or optimizations in `CONTRIBUTING.md` (future).



## License & Acknowledgments

This project is for personal growth. Some project ideas are inspired by online C++ and robotics tutorials.



Good luck on your C++ journey! 
