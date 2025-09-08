# GTFO-EXTERNAL

**Simple external tool for a non-anti-cheat game using WinAPI**

This project **GTFO-EXTERNAL-** is a minimalistic external tool written in C++ that connects to a game's process (GTFO) without an anti-cheat system. It uses WinAPI calls to apply cheats such as *infinite ammo*, feature toggles, and other hacks controlled via hotkeys.




---

## Features

- **External memory manipulation** using WinAPI, no internal DLL injection required.
- Hotkey toggles (e.g., `INSERT`) for features like *infinite ammo*.
- Read and write memory of the game process.
- Console feedback using `std::cout` and sound notifications via `mciSendString()` (MP3/WAV support).
- State check before applying or restoring patches.

---

## How to Use

1. Compile the project with your C++ environment (Visual Studio, etc.).
2. Place the executable (`.exe`) in the same folder as your game.
3. Run the `.exe` and press `F2` in-game to toggle *infinite ammo*.
4. The console will display logs for activation/deactivation.

---

## CODE STRUCT 

```cpp

GTFO-EXTERNAL-/
├── bin/
│   └── SE.mp3               # Sound played when activated
├── src/
│   ├── main.cpp             # Toggle loop and sound
│   └── features.cpp/.h      # Function toggleInfinityAmmo
├── include/                 # Headers (if any)
├── README.md
└── .gitignore



