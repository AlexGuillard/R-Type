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


# UDP Protocol Documentation

## Introduction

This document provides an overview of the UDP protocol used in our project.

## Protocol Overview

### Purpose

The UDP protocol is designed for fast and lightweight communication.

### Packet Structure

UDP packets have a simple structure consisting of:

- Header
- Data

## Error Codes

In case of errors, the UDP protocol uses the following error codes:

- `500: Internal Error`: This code indicates that the server have an internal error

- `404: Not Found`: This code is used when the sever isnt found

## Client Codes

- `200: Connection`: This code is used when the client connect to the server
- `201: Login`: This code is used when the client login to the server
- `202: Logout`: This code is used when the client logout to the server

### 210 Commands

- `211: UP`: This code is used when the client move up
- `212: DOWN`: This code is used when the client move down
- `213: LEFT`: This code is used when the client move left
- `214: RIGHT`: This code is used when the client move right
- `215: SHOOT`: This code is used when the client shoot
- `216: DROP`: This code is used when the client drop the force pod

## Server Codes
### 300 Infos

- `301: Accept`: This code is used when the server accept the client
- `302: Accept`: This code is used to communicate the life
- `303: Accept`: This code is used to communicate the score
- `304: Accept`: This code is used to communicate the level
- `305: Accept`: This code is used to communicate the scoll speed

### 31X Entity

- `310: Start Components`: This code is used to let know when we start sending components
- `311: Stop Components`: This code is used to let know when we stop sending components
- `313: Type Component`: This code is used to let know the component's type
- `314: Infos Component`: This code is used to let know component's infos 
- `315: Kill Entity`: This code is used to let know that an entity is killed

## Usage

Here's an example of how to use the UDP protocol in your application:

```cpp

ici fausse doc mais faudra la faire
# Sample code snippet
import udp_protocol

# Create a UDP socket
sock = udp_protocol.create_socket()

# Send a message
udp_protocol.send_message(sock, "Hello, UDP!")

# Receive a message
message = udp_protocol.receive_message(sock)
```

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
