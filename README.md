### SmartCheckers 

Сheckers game with artificial intelligence elements.
The players take turns.
The first one who collects a row of nine pieces in the opponent's position wins.<br><br>
[![🏁 Window](https://github.com/SergeyG22/SmartCheckers/actions/workflows/windows_builds.yml/badge.svg)](https://github.com/SergeyG22/SmartCheckers/actions/workflows/windows_builds.yml)<br>
[![🐧 Linux](https://github.com/SergeyG22/SmartCheckers/actions/workflows/linux_builds.yml/badge.svg)](https://github.com/SergeyG22/SmartCheckers/actions/workflows/linux_builds.yml)<br>
[![🍎 macOS](https://github.com/SergeyG22/SmartCheckers/actions/workflows/macos_builds.yml/badge.svg)](https://github.com/SergeyG22/SmartCheckers/actions/workflows/macos_builds.yml)<br>


### Rules of the game

Choose a chess piece, make a move. The opponent will also make a move. 
The winner is the one who puts all nine chess pieces on the opponent's position.


### Build from source
CMake 3.13 or higher must be installed
```
git clone https://github.com/SergeyG22/SmartCheckers.git
cd WorldOfTanks
mkdir build
cd build
cmake ..
```

### If Linux requires a dependency type in cmd:

```
sudo apt-get install build-essential pkg-config libx11-dev libxcursor-dev libxinerama-dev libgl1-mesa-dev libglu-dev libasound2-dev libpulse-dev libdbus-1-dev libudev-dev libxi-dev libxrandr-dev yasm xvfb wget unzip libopenal-dev libvorbis-dev libflac-dev
```

### Keyboard control

```
 [W] - move up
 [S] - move down
 [A] - move left
 [D] - move right
```

### Mouse control

```
 [left mouse button] - select a shape
```

### Preview
 
![hippo](https://github.com/SergeyG22/SmartCheckers/blob/master/docs/animation/animation.gif)

