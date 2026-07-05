# tinyed
Tiny GUI text editor built with system libs (x11 for now, additionally win32 in future).
The goal for this editor is to be super tiny without being useless.
## Prerequisites
1. Build deps
- X11 headers (linux/freebsd/macos)
    - Debian-based: `sudo apt install libx11-dev`
    - Fedora/rhel:  `sudo dnf install libX11-devel`
    - Arch-based:   `sudo pacman -S xorgproto`
    - Freebsd:      `sudo pkg install libX11`
    - Macos:        `brew install --cask xquartz`
- Win32 api deps (Windows)
    - TBD 
2. Runtime deps 
- X11 Server / Xwayland (linux/freebsd) 
- XQuartz (macos)
## Getting 
```sh
git clone https://github.com/Freemorger/tinyed.git 
cd tinyed 
```
## Building on ~real systems~ Linux/Freebsd/Macos 
I use my simple build system `MAD` right here. [See more](https://github.com/Freemorger/mad)
Build it in debug:
```sh
mad debug 
```
Or optimized, release:
```sh
mad release
```
Clean up before building again:
```sh
mad clean
```
## Building on Windows 
TBD
