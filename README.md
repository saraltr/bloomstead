# Bloomstead Garden Simulator - C++

Bloomstead is a terminal based garden simulation game developed in C++. In this game, players manage a small garden where they can plant seeds, water plants, deal with pests and weeds, harvest mature plants and sell them to a merket. My goal with this project was to deepen my understanding of core C++ concepts such as object-oriented programming, class inheritance, virtual functions, dynamic memory management, and working with STL data structures like vectors and maps.

A secondary iteration of the project introduces a graphical user interface (GUI) using the Raylib library. While the GUI differs slightly in some mechanics for usability, it still relies on the same class structure and game logic.

[Software Demo Video](http://youtube.link.goes.here)

# Development Environment

- Programming Language: C++17
- Compiler: g++ 15.1.0 (Rev7, Built by MSYS2 project)
- Debugger: GDB (configured via MSYS2)
- GUI Library: Raylib for the graphical interface

The debugger is configured through launch.json to use GDB for stepping through and inspecting code during runtime.

# Useful Websites

{Make a list of websites that you found helpful in this project}

- [Practical C++: Learn C++ Basics Step by Step](https://learning.oreilly.com/course/practical-c-learn/9781803234687/)
- [MSYS2, C++ development environment for Windows](https://www.msys2.org/)
- [Visual Studio Code C++ Configuration](https://code.visualstudio.com/docs/cpp/config-mingw)
- [Raylib Documentation](https://www.raylib.com/)
- [Get Started in raylib in 20 minutes](https://www.youtube.com/watch?v=RGzj-PF7D74&ab_channel=ProgrammingWithNick)

# Future Work

- Integrate full terminal version mechanics into the GUI, such as variety of plants, market and inventory system 
- Implement file system to save and load game state between sessions
- Expand gameplay mechanics such as npc errands, level tasks or weather effects