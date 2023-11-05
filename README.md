
# R-Type 🚀

![Alt text](https://m.media-amazon.com/images/I/911DV9FiRTL.png)

R-Type is a horizontally scrolling shooter arcade video game developed and released by Irem in 1987 and the first game in the R-Type series. The player controls a star ship, the R-9 "Arrowhead", in its efforts to destroy the Bydo, a powerful alien race bent on wiping out all of mankind. The R-9 can acquire a glowing orbicular device called a "Force", protecting it from enemy fire and providing additional firepower.

This version of the game is played in networks of up to 4 people.

## How to build 🛠️
### Linux 🐧
<img align="right" width="100" height="120" src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/b0/NewTux.svg/150px-NewTux.svg.png">


If your on Linux you need CMake, on root of the project, execute:
```bash
./init.sh
```

### Windows 🪟
<img align="right" width="100" height="100" src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/5f/Windows_logo_-_2012.svg/1024px-Windows_logo_-_2012.svg.png">

#### Requirements
* CMakeGUI
* Visual Studio 2022 with workload '[Desktop development with C++](https://learn.microsoft.com/en-us/cpp/ide/using-the-visual-studio-ide-for-cpp-desktop-development?view=msvc-170)'

In CMakeGUI:
  1. Set 'Where is the source code' as the root of the repository
  2. Set 'Where to build the binaries' wherevere you want (we recommend making a build/ directory in the repository)
  3. Press 'Configure', 'Generate' and 'Open Project' buttons in succession
In Visual Studio:
  1. Click here ![image](https://github.com/AlexGuillard/R-Type/assets/91672539/abfa7647-48ad-4e3a-87e7-168cf46a3d7d)
  2. Then select multiple start-up project and set `r-type_client` and `r-type_server` to Start ![image](https://github.com/AlexGuillard/R-Type/assets/91672539/25604bf4-d4e2-4513-b846-c27e8979340b) and click OK
  3. 🎉 You can now run the project by clicking the Green Start button at the top 👍


Then you have to configure and generate the project.
After that you can open the project with visualStudio and setup the startup project to the client and the server.
Then you can build the project.

## How to play 🛝
When you launch the executable, you will have connect to the server.
For that you will have to enter the ip address of the server and the port here is what it have to looks.

⚠️⚠️ Make sure the Server is running before you try to connect to it ⚠️⚠️
![image](https://github.com/AlexGuillard/R-Type/assets/91672539/81afc5af-2823-4a9c-828c-0c71d4497f65)

If you chose `solo` you will be brought to the game otherwise, you will need to choose you game mode.

⚠️⚠️ Make sure all the players are connected before you choose a game mode because there is no comeback once the game started ⚠️⚠️
![image](https://github.com/AlexGuillard/R-Type/assets/91672539/52807eb4-9cca-4a04-b568-caa228227ef5)


After that, the game will start and you will have to destroy all the enemies to win the game. Good luck soldier 🫡🫡🫡!

The ship is controlled with the directional arrows and the space bar to shoot, more time you keep pressing the space bar more bigger is your shoot.

## Supported Platforms 🤝

| Platforms | Availability |
| :---    |  :---:  |
| Linux   | ✅ |
| Window  | ✅ |
| MacOs   | ❌ |

## Authors 🐐

<p align="center" width="100%">
  <a href="https://github.com/AlexGuillard">
    <img width="15%" src="https://avatars.githubusercontent.com/u/91674655?v=4">
  </a>
  <a href="https://github.com/Pablodeibar">
    <img width="15%" src="https://avatars.githubusercontent.com/u/91668926?v=4">
  </a>
  <a href="https://github.com/Benjicatch">
    <img width="15%" src="https://avatars.githubusercontent.com/u/91670393?v=4">
  </a>
  <a href="https://github.com/Kiya971">
    <img width="15%" src="https://avatars.githubusercontent.com/u/91669051?v=4">
  </a>
  <a href="https://github.com/azeuio">
    <img width="15%" src="https://avatars.githubusercontent.com/u/91672539?v=4">
  </a>
</p>

## Developer's Documentation 👷

- [Documentation](https://github.com/AlexGuillard/R-Type/wiki/Developer's-Documentation)

- [UDP Protocol](https://github.com/AlexGuillard/R-Type/wiki/Developer's-Documentation#udp-protocol-documentation)

- [Doxygen Documentation](https://alexguillard.github.io/R-Type/)

## License

[MIT](https://choosealicense.com/licenses/mit/)

