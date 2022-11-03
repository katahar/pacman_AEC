# Hello & Welcome to PacMan!

## Running The Game
   
   The main executable is called animationWithMapVelocity.cpp but can be built by using the target name "PacMan" and the executable will be built as "PacMan.exe". \
   The folders containing the sprites, maps, and sound clips, along with the highscores file are placed in the data folder. We've added post build so that the game can run from the build directory, without worrying about the relative path from the build to the data folder.

   We've also added Public and MMLPlayer git repositories as submodules for this project repository to make the path standard for all systems. Thus, these submodules have to be initialized and updated before building the game. 
   To do that run the following commands from inside the Strange_Team_Name_Here folder.
   
   ```
   git submodule init
   git submodule update
   ```

   Then run the following commands from inside the build directory to build and run the game.

   ```
   cmake < Relative path to Strange_Team_Name_Here/PacMan >
   cmake --build . --target PacMan --config Release
   .\Release\PacMan.exe
   ```

## Playing The Game
 - Press the Space bar to begin playing the game.
 - Up/Down/Left/Right Arrow keys will move Pacman.
 - While in the game, press the Space bar to toggle pause game, or ESC to quit.
 - While in the game, the user can press the H key to display the Highscores on the console window.
 - The +/- keys can be used to increase/decrease the volume respectively.

## Game Features
 1. Authentic Pacman and Ghost behaviours.
 2. Sprites, Map, Sounds and Animations replicated from the original Pacman.
 3. Level transition animations.
 4. A custom map for level 2.
 5. Highscore tracking b/w games.

### Now everyone can play the classic PacMan on their laptops, without having to search for an arcade!

# Enjoy!