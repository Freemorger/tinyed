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
### Via make
Build it in debug:
```sh
make debug 
```
Or optimized, release:
```sh
make release 
```
Clean up before building again:
```sh
make clean
```
## Building on Windows 
TBD
## Development
On linux (and maybe some other systems like macos/freebsd perhaps), to make LSP (clangd) 
work during development, you can run bear and make it generate compile commands:
```sh
make clean 
bear -- make
```
