# 🚀 Hover-Bug: Floating Text Display

![GitHub release (latest by date)](https://img.shields.io/github/v/release/saahen-sriyan-mishra/Hover-Bug)

[Demo](https://github.com/your-repo/path-to-file.mpc)

A lightweight Windows utility that displays customizable floating text with smooth animations and color effects. Perfect for streamers, presenters, or desktop customization.

## ✨ Features

- **Dynamic Floating Text**  
  - Smooth movement patterns (3-7 sec per direction)  
  - Starts centered on any screen  

- **Eye-Catching Effects**  
  - 🌈 Smooth color fading (rainbow mode)  
  - 🎯 Always-on-top display  

- **Easy Control**  
  - Simple launcher for text updates  
  - System tray friendly (low resource usage)  

## 📥 Installation

1. Download the latest release from [Releases](https://github.com/saahen-sriyan-mishra/Hover-Bug/releases)
2. Extract `Hover-Bug_v2.3.zip`
3. Run `main.exe`

*No admin rights required!*

## 🖥️ Usage

### Basic Controls

Type your text in the launcher

Click "Start" to launch floating text

Use "Stop" to remove it


### Advanced Options
- **Command Line**:  
  ```bash
  Hover_Bug.exe "Your Text Here"
  ```

## 🛠️ Building from Source

Requires:

- MinGW/GCC (Windows)
- Win32 API development headers
```bash
g++ -std=c++11 -O2 -mwindows hover_bug.cpp -o Hover_Bug.exe -static -lgdi32 -lwinmm
g++ main.cpp -o main.exe -mwindows
```

## 📜 License
MIT License - Free for personal and commercial use.


## 🐞 Found a bug? Open an Issue

  
