# rock-paper-scissors-ai

Rock-Paper-Scissors game in C with an AI opponent, score tracking, and multiple difficulty levels.

A fun, interactive Rock-Paper-Scissors game written in C, featuring both a multiplayer mode and a single-player mode against an AI opponent.

## Table of Contents
- [About the Project](#about-the-project)
- [Features](#features)
- [How to Play](#how-to-play)
- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)


---

### About the Project

In this project, I’ve built a classic Rock-Paper-Scissors game in C. You can play against a friend in multiplayer mode or challenge an AI opponent. This project is designed to improve basic C programming skills, including user input, randomization, and game logic.

### Features
- **Single-Player Mode**: Play against an AI that makes random choices.
- **Multiplayer Mode**: Play against a friend on the same computer.
- **Score Tracking**: Tracks the score over multiple rounds and displays the final winner.
- **Round History**: Shows the history of each player’s choices for each round.
- **Colorful Output**: Game results are color-coded for better readability (using ANSI color codes).

---

### How to Play

The game follows standard Rock-Paper-Scissors rules:
- **Rock** beats **Scissors**
- **Scissors** beats **Paper**
- **Paper** beats **Rock**
- If both players choose the same option, it’s a **draw**

---

### Getting Started

To get a local copy up and running, follow these simple steps.

#### Prerequisites

You’ll need a C compiler to run this program. If you’re using GCC, you can install it as follows:

- **For Linux**:
  ```bash
  sudo apt-get install gcc

- **For Mac (using Homebrew)**:
  ```bash
  brew install gcc
- **For Windows**:
  You can use MinGW or Cygwin to install GCC.
#### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/rock-paper-scissors-ai.git

2. **Navigate to the project directory**:

   ```bash
   Copy code
   cd rock-paper-scissors-ai

   
3. **compile the code**:
   ```bash
   gcc -o rock_paper_scissors_game rock_paper_scissors_game.c

4. **Run the game**:
   ```bash
   ./rock_paper_scissors_game

### Usage

1. **Choose Game Mode**:
   - When prompted, press `M` for multiplayer or `A` to play against the AI.

2. **Make Your Move**:
   - You’ll be prompted to select `R` for Rock, `P` for Paper, or `S` for Scissors.

3. **View Results**:
   - After each round, the game will display the result (win, lose, or draw) in color-coded text.

4. **Repeat**:
   - The game will ask if you want to play another set of rounds or quit.

5. **Final Score**:
   - At the end, the game displays the final score and declares the winner.

---

### Project Structure

Here’s a quick overview of the key files in this project:

- **rock_paper_scissors_game.c**: Main game logic, including functions for AI, score tracking, and result display.
- **README.md**: Documentation and instructions.
- **LICENSE**: License file specifying project usage permissions.

---

### Contributing

Contributions are welcome! If you’d like to improve the game or add new features, feel free to fork the repository and submit a pull request. Here’s how:

1. **Fork the project**.
2. **Create your feature branch**:
   ```bash
   git checkout -b feature/AmazingFeature
3. **Commit your changes**:
   ```bash
   git commit -m 'Add some AmazingFeature'

4. **Push to the branch**:
   ```bash
   git push origin feature/AmazingFeature
5. **open pull request**.
   
### License

This project is licensed under the MIT License.


