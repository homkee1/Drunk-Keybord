# 🥃 Windows Drunk Keyboard

> Your keyboards got a drinking problem. And its YOUR problem now.

<div style="display: flex; gap: 20px; align-items: center; justify-content: center; margin: 20px 0;">
  <img src="https://raw.githubusercontent.com/homkee1/Drunk-Keybord/assets/readme/gifs/1.gif" width="300">
</div>

![Windows](https://img.shields.io/badge/Windows-10%2F11-blue?style=flat-square)
![C++](https://img.shields.io/badge/C%2B%2B-20-green?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-orange?style=flat-square)
![CMake](https://img.shields.io/badge/CMake-3.12%2B-lightgrey?style=flat-square)

———————————————————————————————————————————————————

## 📑 Quick Navigation

- [What is this](#what-is-this-even)
- [Why tho](#why-tho)
- [How it works](#how-it-actually-works)
- [Quick Start](#-quick-start)
- [Setup](#setup-if-youre-actually-gonna-do-this)
- [Configuration](#configuration)
- [Troubleshooting](#its-broken-now-what)
- [Real World Usage](#real-world-usage-if-youre-unhinged)

———————————————————————————————————————————————————

## what is this even

**Drunk Keyboard** remaps your keys while you type. but like, its not random every time - your keyboard picks a direction and commits to it.
(YOU CAN CHANGE IT IN CONFIGURATION)

```
Type `A` → get `Z`  
Type `A` again → STILL get `Z`  
Type `B` → get `M`  
Rinse, repeat, suffer.
```

Your keyboard learned a new language last night and refuses to unlearn it.

———————————————————————————————————————————————————

## why tho

- 💀 prank your coworker
- 🧠 muscle memory is about to get humbled real quick
- 🎮 new difficulty unlocked..
- 📺 tryhard streamers are gonna have *content*
- 🐻 finally (but mb accidentally) learn russian

———————————————————————————————————————————————————

## Explained

<div style="display: flex; gap: 20px; align-items: center;">
  <div style="flex: 1;">
	<p>so ehm... what can i say...</p>
    <p>every key gets remapped.</p>
  </div>
  <div>
    <img src="https://raw.githubusercontent.com/homkee1/Drunk-Keybord/assets/readme/images/1.jpg" width="400">
  </div>
</div>

———————————————————————————————————————————————————

## what youre getting

| Feature | Why it slaps |
|---------|-------------|
| **consistent mapping** | same key = same cursed output every time (at least something makes sense) |
| **custom key set** | only want 16 keys scrambled? sure!!!! |
| **numbers too** | 0-9 can join the party (on your choice) |
| **Alt+F5 panic button** | instead of crying |
| **stealth af** | no console, no notifications |

<div style="display: flex; gap: 20px; align-items: center; margin-top: 20px;">
  <div style="flex: 1;">
    <strong>"numbers too":</strong>
    <p>You can choose to include 0-9 in the chaos or keep them sane. its your funeral.</p>
  </div>
  <div>
    <img src="https://raw.githubusercontent.com/homkee1/Drunk-Keybord/assets/readme/gifs/4.gif" width="150">
  </div>
</div>

———————————————————————————————————————————————————

## ⚠️ What It Actually Hooks

<div style="display: flex; gap: 20px; align-items: flex-start;">
  <div style="flex: 1;">
    <p>🚨 <strong>thats only hook ~60% of your keyboard - letters and numbers.</strong> im not trying to brick your pc or anything. ctrlaltdel? untouched. function keys? safe. arrows? chilling. im leaving you escape routes because im not *that* evil.</p>
  </div>
</div>

but if u have only 60% keyboard.... well, good luck buddy.
<div style="display: flex; gap: 20px; align-items: center; justify-content: center; margin: 20px 0;">
  <img src="https://raw.githubusercontent.com/homkee1/Drunk-Keybord/assets/readme/images/2.jpg" width="200">
</div>
———————————————————————————————————————————————————

## 🚀 Quick Start

```bash
# Clone the repo
git clone https://github.com/yourusername/drunk-keyboard.git
cd drunk-keyboard

# Build with CMake (recommended)
mkdir build && cd build
cmake ..
cmake --build . --config Release

# Run it
./drunk-keyboard.exe
```
DONT FORGET TO CHECK IN PATH
C:\Program Files\CMake\bin

**Thats it. your keyboard is now suffering.**

———————————————————————————————————————————————————

## setup (if youre actually gonna do this)

### Prerequisites

- **Windows 10/11** (god will forgive me🐧🐧🐧)
- **Visual Studio**, VS Code, or any C++ IDE
- **C++ compiler** (MSVC, MinGW, or Clang)
- **CMake**

### Build Options

#### Option 1: MSVC (Visual Studio)
use Developer Command Prompt
```bash
git clone https://github.com/homkee1/Drunk-Keybord.git
cd Drunk-Keybord
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

#### Option 2: MinGW
```bash
git clone https://github.com/homkee1/Drunk-Keybord.git
cd Drunk-Keybord
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

#### Option 3: Command Line (MSVC)
Use Developer Command Prompt
```bash
cl /W4 /EHsc /std:c++20 KeyMapRandomizer.cpp /link user32.lib /OUT:drunk-keyboard.exe
```

#### Option 4: Command Line (MinGW)
```bash
g++ -std=c++20 -Wall KeyMapRandomizer.cpp -o drunk-keyboard.exe -luser32
```

### Run It

```bash
./drunk-keyboard.exe
```

### Escape

```
Alt+F5
(or Task Manager if you panic)
```

———————————————————————————————————————————————————

## CONFIGURATION

Edit `KeyMapRandomizer.cpp` at the top:

```cpp
static bool useAllLetters = true;        // all 26 or custom set
static bool includeDigits = true;        // scramble 0-9? (yes)
static bool persistentMapping = true;    // same key = same output (yes... ELSE GOOD LUCK)
static bool isConsole = false;           // show console? (no thanks)
static bool altf5close = true;           // can you escape? (spoiler: DONT TURNING THAT OFF)
```

### Custom Key List

If `useAllLetters = false`:

```cpp
static const std::vector<int> customKeys = {
    'T', 'Y', 'U', 'R', 'Q', 'Z', 'X', 'C', 'V', 'B', 'N', 'G', 'H', 'J', 'M', 'L'
};
```

———————————————————————————————————————————————————

## how it actually works

```cpp
SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
```

thats literally it. drunKeyboard at the OS level, intercepting every keystroke before your app even *knows* it happened.

### The Flow

1. you press a key
2. windows tells us first (pwned)
3. i check the map: "what does THIS key do today?"
4. i send the wrong one instead
5. your app thinks you typed chaos
6. your brain short-circuits
7. profit

### Why its Fast

- OS-level hooks (fastest in the game fr fr)
- `std::unordered_map` does the lookups (O(1) suffering)
- `std::mt19937` for that premium rng

### Technical APIs

**APIs borrowed:**
- `SetWindowsHookEx()` – keyboard go beep
- `CallNextHookEx()` – pass it along
- `SendInput()` – inject the "drunk" key
- `UnhookWindowsHookEx()` – cleanup

**Data structures:**
- `unordered_map<int, int>` – original key → cursed key
- `unordered_set<int>` – which ones to actually mess with
- `vector<int>` – all the possible targets
- `mt19937` – idk lol

**Flags:**
- `LLKHF_INJECTED` – "this is us, tsss"
- `WM_KEYDOWN` – key go down
- `WM_KEYUP` – key go up
- `KEYEVENTF_KEYUP` – inject release event

———————————————————————————————————————————————————

## its broken now what

### "nothing happens"

- run as Admin (literally step 1)
- your antivirus thinks im malware (fair)
- are you actually pressing the keys you remapped lol

### "i cant turn it off"

- Alt+F5 (no cap)
- Task Manager
- try writing to the console `taskkill /f /IM KeyMapRandomizer` (GOOD LUCK..)

### "keyboard still weird"

- restart (noobie solution)
- reinstall drivers (psycho)
- accept your fate

### "permission denied"

- admin rights
- corporate PC? they hate fun anyway

### "somethings broken"

- thats the feature, not a bug

———————————————————————————————————————————————————

## real world usage (if youre unhinged)

### The Coworker Prank Setup

```
coworker sits down
app already running from startup
they type their password
screen: "zmkkd_r0ck5!!"
*yo wtf...*
you: "try Alt+F5"
them: oh thank u
(or u say nothing... but dont do it cuz its bad cuz bla bla bla)
(OR YOU TURNED OFF ALT+F5🥶🥶🥶🥶)
```


———————————————————————————————————————————————————

## license

MIT - do whatever. break stuff. its fine.

```
provided "as is" lmao
im not responsible for your keyboard
good luck
```

THATS NOT A WARRANTY CASE:
<div style="display: flex; gap: 20px; align-items: center; justify-content: center; margin-top: 20px;">
  <img src="https://raw.githubusercontent.com/homkee1/Drunk-Keybord/assets/readme/gifs/3.gif" width="200">
</div>
———————————————————————————————————————————————————

## credits

- Microsoft (for the hook API i stole)
- chaos itself
- your friend who said "do it"
- your sanity



———————————————————————————————————————————————————

## what youll actually learn

- Windows Keyboard Hooks
- Input injection APIs
- RNG (litl bit but still)
- Hash maps & sets
- how to weaponize C++ basically
- CMake (its hard af😭)

———————————————————————————————————————————————————

**go get that drunKeyboard experience**

———————————————————————————————————————————————————

*made with ❤️ and destructive impulses*
