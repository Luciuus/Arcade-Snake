# Arcade Snake: Cosmic Loop Edition

A high-performance, CLI-based rendering of the classic Snake game implemented in modern C++. This project demonstrates low-level console buffer handling, state machine architecture, and reactive asynchronous input polling paired with a branching narrative system.

---

## 📌 Table of Contents
- [Core Architecture & Features](#-core-architecture--features)
- [Control Schema](#-control-schema)
- [Technical Deep Dive](#-technical-deep-dive)
- [Installation & Build Guide](#-installation--build-guide)
- [Narrative Engine](#-narrative-engine)
- [Roadmap & Enhancements](#-roadmap--enhancements)
- [License](#-license)

---

## 🎮 Core Architecture & Features

- **Procedural Grid Initialization:** Dynamically generates an (N+2) × (N+2) coordinate matrix supporting custom boundaries.
- **Asynchronous Input Polling:** Utilizes zero-blocking keyboard listeners to separate the render pipeline from the execution thread.
- **State Persistence Modes:**
  - `Hardcore Permadeath (One Life)`: Instant stack termination upon collision evaluation.
  - `State Reversion (Return by Death)`: Implements a pseudo-loop state machine that tracks execution cycles and rolls back head/tail vector allocations upon death.
- **Micro-timed QTE Loop:** A time-sliced Quick Time Event (QTE) framework running independent of blocked streams (`std::cin`).

---

## 🕹️ Control Schema

| Input Key | Runtime Action | Context |
| :---: | --- | --- |
| **`W` / `A` / `S` / `D`** | Directional Vector Changes (Up, Left, Down, Right) | Grid Traversal |
| **`Spacebar`** | Increment Counter | QTE Climax Stage |
| **`Q`** | Graceful Process Termination | Anywhere |

---

## 🛠️ Technical Deep Dive

### 1. Vector-Based Segment Management
Unlike primitive grid arrays, the snake's anatomy relies on a dynamic sequence memory buffer. Position histories are shifted continuously to optimize continuous memory layout allocations:
```cpp
// Segment progression matrix logic
bodyArray.push_back(playerPositionStorage);
mainArray[playerPositionStorage] = playerTail;
// ... directional computation ...
if (!ateApple) {
    mainArray[bodyArray.front()] = placeholder;
    bodyArray.erase(bodyArray.begin());
}
```

### 2. High-Frequency Non-Blocking QTE Polling
To bypass the standard `std::cin` blocking mechanism, the engine applies discrete time-slicing via `<conio.h>` inside the narrative climax loop, distributing 1-second ticks into 50ms listening intervals:
```cpp
// Frequency-adjusted polling for optimal responsiveness
for (int i = 0; i < 20; i++) {
    if (_kbhit()) {
        char click = _getch();
        if (click == ' ') spaceClick++;
    }
    Sleep(50); // Balanced delta time matching 1000ms total
}
```

---

## 🚀 Installation & Build Guide

### System Requirements
- **OS:** Microsoft Windows (due to `<windows.h>` and `<conio.h>` system dependencies)
- **Compiler:** GCC 7.0+ (MinGW) or MSVC 2017+

### Compilation
Compile the source tree using any standard C++ compiler with optimal optimization flags:

```bash
# Using GCC via Command Line
g++ -O3 -std=c++17 main.cpp -o CosmicSnake.exe
```

### Running the Executable
```bash
./CosmicSnake.exe
```

---

## 📜 Narrative Engine

The gameplay layer serves as a metaphor for an underlying existential loop. Upon passing the threshold of three successive systemic failures (`isDead == 3`), the program intercepts standard control flow to transition into a dialogue sequence with the game's architect (`GOD`).

The user's final objective tests physical inputs against a countdown sequence. Reaching critical threshold targets shifts execution towards a hidden victory state, while failure safely disposes allocations and closes the process.

---

## 🗺️ Roadmap & Enhancements
- [ ] Implement Cross-Platform POSIX support (`termios.h`) for Linux/macOS compatibility.
- [ ] Refactor procedural rendering into Double Buffer Console Windows APIs to eliminate screen flicker (`system("cls")`).
- [ ] Introduce JSON-based state serialization for persistent high-score leaderboards.

---

