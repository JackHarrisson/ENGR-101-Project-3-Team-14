# ENGR-101-Project-3-Team-14
Team 14's Project 3

## Team Name: Team 14

### Team Members & contact info
- Jack Harrisson - harrisjack1@myvuw.ac.nz
- Jamie U - uujami@myvuw.ac.nz
- McGregor Smith – mcgregor.ms@hotmail.com
- Aleksey Belov – belovalex@myvuw.ac.nz

### Communication Tool:
- Discord

### Roles

- Jamie - Project Manager
- Jack - Software Architect
- McGregor - Software Writer
- Aleksey - Software Writer

GitHub: <https://github.com/JackHarrisson/ENGR-101-Project-3-Team-14>

### Milestones

| Date | Objectives | Due Date | Item Due | Tasks | Date completed |
|------|------------|----------|----------|-------|-------|
|2/06/2020| Start the project | 4 June | Testing Code| MS - Tests all installations. Write test cases for team - 4 June| 04/06 |
|      |            |          |          | JH - Ensure Plan is done, Help install SFML on all computers - 4 June| 04/06 |
|      |            |          |          | AB - Ensure Robot is built - 4 June| 04/06 |
|      |            |          |          | JU - Get pictures from robot - 4 June| 04/06 |
|      |            |          |          | ALL - Complete AVC Plan - 4 June| 04/06 |
|      | Core       | 11 June  | Core code | ALL - Write code so robot 11/5 1 & 2 moves through the maze | 12/06 |
|      |            |          |          | ALL - Intro & Background for  progress report started | |
|      |            |          |          | AB, JU - In charge of Q1 code | 12/06 |
|      |            |          |          | JU, MS, JH - Debug hardware if robot is not fit for the circuit | n/a |
|      | Completion | 15 June  | Completion code | AB - In charge of Q2 code | 14/06 |
|      |            |          |          | JU - Help debug & check report, plan meetings for following week | n/a |
|      |            |          |          | MS - Checks code for Q1&2 enables robot to completes circuit, debug/fix if necessary | 14/06 |
|      | Challenge  | 18 June  | Challenge code | AB - In charge of Q3 code | |
|      |            |          |          | JU, MS, JH - help to test and debug | |
|      | Write installation instructions    | 18 June  | Installation instructions | JH - Write robot install instructions for Geany IDE | |

### Robot Installation Instructions

1. Install Geany [Here](https://www.geany.org/download/releases/).
2. Download the correct version of SFML from [Here](https://www.sfml-dev.org/download/sfml/2.5.1/). Select the MinGW version.
3. Download all the code from the "Code" file on the GitHub.
4. Unzip the SFML file into C/SFML.
5. Create A folder for the project.
6. Download the **makefile** (You may have to modify the INCLUDE and LIBS lines to fit your install).
7. In Geany go to Build -> Set Build Commands
8. Instead of **make** enter **mingw32-make**.
9. Copy all **dll** files from the SFML file into the project file.
10. Instead of **Compile**, **Build** and **Run** select **make** from Geany menu.
11. **make** then **execute** Server.hpp first and then do the same to Robot.cpp
12. Once you **execute** Robot.cpp it will promt you to enter "1" for Core, "2" for Completion or "3" for Challenge.
