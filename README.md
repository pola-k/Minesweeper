# Minesweeper Game in C++

Welcome to the Minesweeper game, developed in C++ as part of my Programming Fundamentals course at university. This project utilizes the SFML (Simple and Fast Multimedia Library) for a visually appealing gaming experience.

## Overview

Minesweeper is a classic puzzle game where players uncover tiles while avoiding hidden mines. The game features user authentication, multiple difficulty levels, and interactive gameplay elements that enhance the overall experience.

## Key Features

- **SFML Graphics:**
  - The game employs SFML for smooth and engaging graphical elements, enhancing the visual appeal and user experience.

- **User Login System:** 
  - Players log in to their accounts, with the system distinguishing between new and returning users.

- **Two Difficulty Levels:** 
  - **Level 1:** A 12x12 matrix, suitable for beginners.
  - **Level 2:** A 20x15 matrix, accessible only after completing Level 1.

- **Save and Load Functionality:** 
  - Players can save their current game state and resume at a later time, allowing for flexible gameplay.

- **Score Tracking:** 
  - The game calculates the player's score based on their performance.

- **Sound Effects:** 
  - Engaging background music plays during gameplay, with additional sound effects for game events.

- **Extra Life Tile:** 
  - A special tile grants players an additional life when uncovered, adding an extra layer of strategy.

## How to Play

1. **Login:** 
  - Start the game and log in using your userID. New users will create an account upon first login.

2. **Select Difficulty:**
  - Choose between Level 1 or Level 2 based on your experience.

3. **Gameplay:**
  - Click on tiles to reveal them. Avoid mines and try to clear the board.
  - Collect the extra life tile if you find it!

4. **Saving Your Game:**
  - You can save your current progress and return to it later.

5. **Ending the Game:**
  - The game ends when all safe tiles are revealed or when a mine is triggered.

## Installation Instructions

1. Clone the Repository:
```bash
git clone <repository_url>
```

2. **Install Dependencies:**
  - Ensure you have SFML installed. You can find installation instructions on the [SFML website](https://www.sfml-dev.org/download.php).

3. **Build the Project:**
  - Open the project in your preferred C++ IDE (e.g., Visual Studio).
  - Make sure to link against the SFML libraries in your project settings.

4. **Run the Game:**
  - Compile and execute the project to start playing!

## Acknowledgments

  - A special thanks to my professors for their guidance throughout the course.
  - Appreciation for the SFML library, which enabled me to create a rich gaming experience.

---

Have fun playing Minesweeper!
