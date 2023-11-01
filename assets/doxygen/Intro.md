# Commit Convention

We use the Conventional Commits, here is a link that shows the commit standard we use : https://www.conventionalcommits.org/en/v1.0.0-beta.4/

- Here are few basic examples of commit message with a description.
```
fix: correct minor typos in code
feat: allow provided config object to extend other configs
feat(lang): add polish language
ci: run linters on pull requests
```
You can install "Conventional Commits" extension on your editor to make it easier to understand

## Pr's title convention
```
<type>[branchefrom > brancheto]: <description>
```
Use conventional commits for the title of PR.
here is an example

```feat(server > main): add connection clients```

## Commit's convention  merge

Use the default git message

## Tickets's convention

- title:
       ```<type>: <description>```
example: 
       ```fix: connection client```

- description:

- for features: 
exact details on what you want to be done to complete this ticket.

- for bugs:
exact details on how to reproduce the bug (and maybe where you think the problem comes from)

- labels:
link tickets to every labels that can be related to them.

- milestones:
link tickets to every milestones that can be related to this ticket.

**/!\ don't forget to assign the ticket to the person who need to work on it.**


# TCP/UDP Protocol Documentation

## Introduction

This document provides an overview of the TCP and UDP protocol used in our project.

## Protocol Overview

### Purpose

The UDP protocol is designed for fast and lightweight communication.

### Packet Structure

packets send by the server have a simple structure consisting of:

- Header struct with:
```c++
struct header {
  int RFC; // RFC code
  int id; // id of the concerned entity in the registry
};
```
- structure body depending of the RFC number
- int of the RFC code to finish the sended data

packets sends by the client are the header struct with the RFC code and the id of the client.

## Connection

- The connection part is in TCP
- When a client is connecting to the server, the client need to send the magic number 81732 in the rfcCode variable of the header. Then the connection can be established

## Error Codes

In case of errors, the protocol uses the following error codes:

- `401: Forbidden`: This code is used when the server refuse the connection in the format:
```c++
struct header {
    code: 401;
    entity: -1;
};
401
```

## Client Codes

### TCP

- Connection: The client connect to the server and send the magic number (81732). Then the server respond with this:
```c++
struct header {
    code: 200;
    entity: index of the player;
};
number of clients connected (including you)
200
```
- `201: Lauch game`: this made the server change to udp and send to every clients:
```c++
struct header {
    code: 201;
    entity: index of the player;
};
port to connect on udp
201
```
- `202: new player`: sended by the server when new client is connected
```c++
struct header {
    code: 202;
    entity: your index of player;
};
number of players
202
```
- `203: solo`
- `204: multi`

### 210 Commands
```c++
struct header {
    code: 21X;
    indexPlayer: 0;
};
```

* `217: CONNECTED`: This code is used when the client connect to udp and confirm to server he is on udp
* `211: UP`: This code is used when the client move up
* `212: DOWN`: This code is used when the client move down
* `213: LEFT`: This code is used when the client move left
* `214: RIGHT`: This code is used when the client move right
* `215: SHOOT`: This code is used when the client shoot
* `216: DROP`: This code is used when the client drop the force pod

### 22X Win/Lose
```c++
struct header {
    code: 22X;
    entity: 0;
};
22X
```
 * `221: WIN`: this code is send to indicate win
 * `222: LOSE`: this code is send to indicate lose
 * `223: RIGHT`: this code is send to indicate that the team on the RIGHT won (PVP)
 * `224: LEFT`: this code is send to indicate that the team on the LEFT won (PVP)

### 23X Stage
```c++
struct header {
    code: 231;
    entity: stage level;
};
231
```
 * `231: [Stage]`: this code indicate the new stage

### 24X Mode
```c++
struct header {
    code: 24X;
    entity: 0;
};
24X
```
 * `241`: this code indicate the classic mode
 * `242`: this code indicate the infini mode
 * `243`: this code indicate the friendly fire mode
 * `244`: this code indicate the pvp mode

## Server Codes
### 3XX: entity
#### 30X: spawn mob
* 301: ([Pata-Pata](https://rtype.fandom.com/wiki/Pata-Pata)) [X, Y]
* 302: ([Bink](https://rtype.fandom.com/wiki/Bink)) [X, Y]
* 303: ([Scant](https://rtype.fandom.com/wiki/Scant)) [X, Y]
* 304: ([Bug](https://rtype.fandom.com/wiki/Bug)) [X, Y]
* 305: ([Cancer](https://rtype.fandom.com/wiki/Cancer)) [X, Y]
* 306: ([Blaster](https://rtype.fandom.com/wiki/Blaster)) [X, Y]
* 307: ([Dobkeratops](https://rtype.fandom.com/wiki/Dobkeratops)) [X, Y]
#### 31X: spawn ally
* 311: (Player) [X, Y, Enum: Color]
* 312: (Ally) [X, Y, Enum: Color]
#### 32X: spawn missile
* 321: (Classic) [X, Y, VelocityX, VelocityY, Enum: Team]
* 322: (Wave Beam) [X, Y, VelocityX, VelocityY, Enum: Team, Force]
* 323: ([Bydo Shot](https://rtype.fandom.com/wiki/Bydo_Shot)) [X, Y, VelocityX, VelocityY, Enum: Team]

#### 33X: existing entities
The server send 331 and 332 of the same entity just after to avoid a shift
* 331: positions of the entities (id of entity in the header and use for body PositionComponent) and velocity of the entities (id of entity in the header and use for body VelocityComponent)
* If the entity don't have a PositionComponent, the server send a PositionComponent with -1 and -1 inside, same for VelocityComponent
```c++

struct header {
    code: 331;
    entity: index of the entity;
};
struct PositionComponent "((-100, -100) if not defined)"
struct VelocityComponent "((0, 0) if not defined)"
number of tick from server
331
```
### Legend
* ID: size_t
* X: int
* Y: int
* Velocity*: float
* Enum: Color
```c++
enum class PlayerColor {
  CYAN = 0,
  PURPLE,
  LIME,
  RED,
  BLUE,
  COUNT // keep last
};
```
* Enum: Team
```
enum ECS::Components::TeamGroup {
  ALLY,
  ENEMY
};
```

## Usage of the UDP protocol to send and receive data
### Example with missiles, each data transferred has at least a header and a footer

#### Example to receive
```c++
header packet = getHeader(received);
bodyMissile missileData = getMissile(str);
BodyNumber footer = getBody(str);
```
Each type of body has a structure and a getters to extract that structures

#### Example to send
```c++
std::string res = "";
res.append(Send::makeHeader(321, eId));
res.append(Send::makeBodyMissile(pos, vel, team, 1));
res.append(Send::makeBodyNum(321);
```
Here you firstly create a Headerwith rfc code and entity, then fill a bodyMissile structure with X/Y position/velocity, teams and strength

# How to use Clang-tidy Config on VScode ?

Firstly Open Vscode and go to **Settings**

Then go to **Workspace**

**you should see this windows**
![image](https://github.com/AlexGuillard/R-Type/assets/91668926/0d9912f3-d151-4dcc-9f3b-9f4b1c5b4bec)

After that type "**code analysis**"
turn ```C_Cpp > Code Analysis > Clang Tidy : Enabled ``` to True

![image](https://github.com/AlexGuillard/R-Type/assets/91668926/5d4c6b83-e050-4857-84a0-c0229fc043db)

And specify the path to .clang-tidy from our source file for example ```/home/YourName/SourceFolderWhere.clang-tidy```

![image](https://github.com/AlexGuillard/R-Type/assets/91668926/2c035b8b-50a6-4d2f-bb49-8a19eaf4bfad)

# How to use Editor Config on VScode ?

1. Start by running
```bash
npm i -g editorconfig
```
in your terminal to make sure the extension will work.

2. Then, open your VScode and go to the settings (`File > Preferences > Settings`)
3. Search for `format on` and check `Editor:Format on Save`
4. If you use autosave, you need to also check `Editor:Format on Type`
5. Then search for the `EditorConfig.EditorConfig` extension and install it
