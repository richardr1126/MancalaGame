
<div align="center">
<h1 align="center">
<img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" width="100" />
<br>MancalaGameGUI
</h1>
<h3>◦ Master the Mancala Magic with Intuitive Gaming Interface!</h3>
<h3>◦ Developed with the software and tools listed below.</h3>

<p align="center">
<img src="https://img.shields.io/badge/C-A8B9CC.svg?style&logo=C&logoColor=black" alt="C" />
</p>
<img src="https://img.shields.io/github/languages/top/richardr1126/MancalaGameGUI?style&color=5D6D7E" alt="GitHub top language" />
<img src="https://img.shields.io/github/languages/code-size/richardr1126/MancalaGameGUI?style&color=5D6D7E" alt="GitHub code size in bytes" />
<img src="https://img.shields.io/github/commit-activity/m/richardr1126/MancalaGameGUI?style&color=5D6D7E" alt="GitHub commit activity" />
<img src="https://img.shields.io/github/license/richardr1126/MancalaGameGUI?style&color=5D6D7E" alt="GitHub license" />
</div>

---

## 📒 Table of Contents
- [📒 Table of Contents](#-table-of-contents)
- [📍 Overview](#-overview)
- [⚙️ Features](#-features)
- [📂 Project Structure](#project-structure)
- [🧩 Modules](#modules)
- [🚀 Getting Started](#-getting-started)
- [🗺 Roadmap](#-roadmap)
- [🤝 Contributing](#-contributing)
- [📄 License](#-license)
- [👏 Acknowledgments](#-acknowledgments)

---


## 📍 Overview

The project is a Graphical User Interface (GUI) implementation of the "Mancala" board game using C++ and Qt framework. The Mancala game logic is encapsulated within numerous classes defining objects such as `Player`, `Marble`, `Pit`, and `Board`. The code allows performing game operations such as game initialization, handling player moves, scoring, and switching player turns involving random manipulation of Marbles-all based on user interactions within the graphical interface.The value proposition of this project is to provide a digitized version of a traditional board game with a useful GUI, reducing the need for physical components. As a tool of educational value, it could assist with understanding object-oriented programming, game logic implementation, user interaction handling, and graphics rendering.

---

## ⚙️ Features

| Feature                | Description                           |
| ---------------------- | ------------------------------------- |
| **⚙️ Architecture**     | The system has a well-structured architecture, following the MVC pattern, separated in different sections such as classes, GUI using classes like QGraphicsScene, QMainWindow,Player, Store etc for business logic.
| **📖 Documentation**   | Documentation is lacking which compounds difficulty understanding the purpose and directions behind some classes.
| **🔗 Dependencies**    | This project relies heavily on the Qt library for all its GUI aspects (windowing, widgets, graphics, event handling) and standard C++ for core logic.
| **🧩 Modularity**      | The system is modular, broken down into distinct classes such as player, pit and marble among others. Architected to be easy to maintain/expand.
| **✔️ Testing**          | No explicit testing framework or tests appear in the examined files. Use of testing methodologies is unverifiable in current form.
| **⚡️ Performance**      | Efficient and fast, given that Qt provides efficiency and speed, and the MVC components interact without overcomplication.
| **🔐 Security**        | No signs of security measures or considerations within the codebase. Seems irrelevant due to game nature.
| **🔀 Version Control** | Git is in use for versioning. Detailed versioning or release strategy is not readily apparent from the provided information.
| **🔌 Integrations**    | Their project cleanly integrates with the Qt library. Beyond that, no other apparent service integration exist.
| **📶 Scalability**     | Utilizes local Client-Server. Very little elasticity or ability to scale beyond initial size. However, for a GUI based two-player game scalability features might not be needed.|

---

## 🧩 Modules

<summary>Root</summary>

| File                                                                                                  | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            |
| ---                                                                                                   | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| [pit.cpp](https://github.com/richardr1126/MancalaGameGUI/blob/main/pit.cpp)                           | The provided code snippet defines classes for'Pit' and'Store'.'Pit' handles operations like adding and removing'Marble' (an external component) and interfaces with graphics to provide visualization. It includes event handling for mouse clicking within pit objects and implements comparison.'Store' implements similar graphical representation methods and differs in dimensional representation.                                                                                                           |
| [marble.cpp](https://github.com/richardr1126/MancalaGameGUI/blob/main/marble.cpp)                     | This C++ code creates colored marbles and assigns them to pits, ensuring the marbles are not overlapping each other by generating random offset values for their rendering position. The class has functionality to update a marble's pits, while it verifies the position of the marble does not cause overlap by re-calculating offsets. It also provides methods to paint the marble and determine its shape and bounding rectangle. Lastly, a factory for creating new marbles or special marbles is provided. |
| [player.cpp](https://github.com/richardr1126/MancalaGameGUI/blob/main/player.cpp)                     | The provided code displays the functionalities of a Player object within a C++ program including a Player constructor and an overload of the "==" operator. The Player constructor initially sets the'score' to 0, assigns a unique player number, and assigns a specific color based on the player number. The "==" operator has been defined to compare whether two Player instances have the same player number and score.                                                                                      |
| [gamewindow.cpp](https://github.com/richardr1126/MancalaGameGUI/blob/main/gamewindow.cpp)             | This C++ program implements a graphical board game. It builds the board, enables play between two players, scores their moves and declares a winner based on earned points. Key functionality includes game initialization, making game moves, distributing marbles, checking end-game conditions, switching players, and updating scores. The game hooks up player inputs (clicking on pits in the GUI) with corresponding game actions and periodically updates the gaming interface.                            |
| [player.h](https://github.com/richardr1126/MancalaGameGUI/blob/main/player.h)                         | The provided snippet defines a Player class in C++. The key functionalities include an initial constructor for a player object, "get" type functions to retrieve player attributes including score, number and color, and a "set" function to update player score. Additionally, an equality operator overload has been provided to compare two Player objects.                                                                                                                                                    |
| [board.cpp](https://github.com/richardr1126/MancalaGameGUI/blob/main/board.cpp)                       | The provided C++ code describes the construction of a game board having 12 pits (2 of which are'special') and 2'stores'. The pits and stores are positioned based on specific calculations involving variables such as store_height and pit_width. The game board is divided for player1 and player2.                                                                                                                                                                                                              |
| [pit.h](https://github.com/richardr1126/MancalaGameGUI/blob/main/pit.h)                               | The provided code snippet defines two classes:'Pit' and'Store.''Pit' manages values such as its coordinates, dimensions, identifier, color, special status, and property of belonging to a player. It also holds Marbles, and provides a mechanism to interface with these contained elements. The'Store' class, inheriting from'Pit', adds height as an extra feature and Customizes visual rendering methods like paint and shape. All renderings are done via Qt graphics facilities.                           |
| [gamewindow.ui](https://github.com/richardr1126/MancalaGameGUI/blob/main/gamewindow.ui)               | The given code snippet represents an XML based UI layout for a Game Window using the Qt user interface framework. This window hosts a game program called "Mancala." It's detailed with a fixed-sized main window, two operational buttons ("Start Game" and "End Game"), labels for scores (store1Label and store2Label), visible instructions for the game, alerts, and game objects graphically represented on a QWidget.                                                                                       |
| [MancalaGame.pro.user](https://github.com/richardr1126/MancalaGameGUI/blob/main/MancalaGame.pro.user) | The provided XML code defines the project settings in Qt Creator IDE. Key definitions include Environment ID, Active Target, Editor Settings like indent size, tab size, codec, and AutoIndent. Also, it details Configuration Settings for build configurations like Debug, Release and Profile. Final details reflect plugin settings and project target parameters.                                                                                                                                             |
| [marble.h](https://github.com/richardr1126/MancalaGameGUI/blob/main/marble.h)                         | The code defines classes related to a game using Marbles.'Marble' is the base class containing characteristics like location (x_, y_), color, pit association, and functions for accessing/modifying them. There are methods to manipulate rendering in the user interface.'SpecialMarble' extends'Marble', differing by points value.'MarbleFactory' provides creation of'Marble' &'SpecialMarble' instances.                                                                                                     |
| [board.h](https://github.com/richardr1126/MancalaGameGUI/blob/main/board.h)                           | The provided code configures a board for a game. The board class inherits from QGraphicsScene. It includes methods-get_pit_at, get_player1/2_pit_at, get_store1/2-to access game element states stored in vectors (pits_, player1/2_pits_) and Store objects (store1/2).                                                                                                                                                                                                                                           |
| [main.cpp](https://github.com/richardr1126/MancalaGameGUI/blob/main/main.cpp)                         | This C++ code runs a Qt application that displays a GameWindow. It initializes a random seed with the current millisecond time for non-deterministic random number generation. The code initializes the Qt application, creates a game window instance, displays it, then enters the Qt event loop.                                                                                                                                                                                                                |
| [gamewindow.h](https://github.com/richardr1126/MancalaGameGUI/blob/main/gamewindow.h)                 | The provided code is for a gaming window interface in C++ using QMainWindow. It includes features to initialize the game (MakeBoard, HandoutMarbles), handle game dynamics (SwitchPlayer, DistributeMarblesFrom) & user events (start/end game). Auxiliary features like game alerts, verifying game conditions (checking for empty pits or declaring the winner) and special actions like stealing marbles system also exist.                                                                                     |

</details>

---

## 🤝 Contributing

Contributions are always welcome! Please follow these steps:
1. Fork the project repository. This creates a copy of the project on your account that you can modify without affecting the original project.
2. Clone the forked repository to your local machine using a Git client like Git or GitHub Desktop.
3. Create a new branch with a descriptive name (e.g., `new-feature-branch` or `bugfix-issue-123`).
```sh
git checkout -b new-feature-branch
```
4. Make changes to the project's codebase.
5. Commit your changes to your local branch with a clear commit message that explains the changes you've made.
```sh
git commit -m 'Implemented new feature.'
```
6. Push your changes to your forked repository on GitHub using the following command
```sh
git push origin new-feature-branch
```
7. Create a new pull request to the original project repository. In the pull request, describe the changes you've made and why they're necessary.
The project maintainers will review your changes and provide feedback or merge them into the main branch.

