# Study Buddy App

A terminal-based C++ application that helps students find study partners based on shared courses and overlapping availability.

---

## Features

- Create or log into a student profile
- Edit your profile with courses and weekly availability
- Search for compatible study partners
- View suggested study sessions
- Confirm study sessions and save them
- Persistent storage via CSV-style text files

---
## Requirements

- C++17 compiler (e.g., `g++`, `clang++`)
- CMake ≥ 3.10
- macOS, Linux, or Windows with a compatible terminal

---

## Build Instructions

1. **Clone the repository**
   ```bash
   git clone https://github.com/ianray9/study_buddy_app
   cd study_buddy_app
   ```
2. **Configure and build with CMake** (MacOs/Linux)
    ```bash
    cmake -S . -B build
    cmake --build build
3. **Configure and build with CMake** (Windows)
    ```bash
    cmake -S . -B build -G "MinGW Makefiles" # Make sure you have MinGW install and in your path
    cmake --build build
    ```
    *Alternatively*, if this does not work for your windows machine you can use vsCode to build the app with its Cmake tools and C/C++ extensions
4. Run the app (in root of project)
    ```bash
    ./StudyBuddyApp # MacOs/Linux
    .\StudyBuddyApp # Windows
    ```
    **WARNING**: If you're on macOS and encounter a file error on launch, make sure you run ./app from the root of the repo (not from inside build/).

---

## Data
The app automatically creates the following files in data/ if they don’t exist:
- `profiles.txt` - Stores student info
- `session.txt` - Stores confirmed sessions
- `currentID.txt` - Used to generate unique student IDs 

---

## Dependencies
This project uses the [csv.hpp](https://github.com/vincentlaucsb/csv-parser?utm_source=chatgpt.com)
Licensed under MIT. Included locally in include/third_party/csv.hpp.
