# Bounce
![banner image](/Images/banner.jpeg)

Title Screen and Concept Art by: LENZ

LENZ's work can be found at:

[LENZ's Instagram](https://www.instagram.com/lenzartz/)

Developer: Zachariah Falgout (RetrobitCoder)

Game Art: Zachariah Falgout (RetrobitCoder)

Arduboy Library: Arduboy2

![screenshot0](/Images/screenshot0.png)
![screenshot1](/Images/screenshot1.png)

## Story
---

A paddle and ball game in the vein on Atari's Pong.
Two dogs are trying to hit the ball back and forth without the ball going past them.
If the ball does go past them, that is a point for the other dog. The dog with the
highest score when the player(s) stop, wins.

This game is designed to be able to play with two players. One player uses the Up and Down buttons,
while the other Player uses the A and B buttons. This game is made to run on the Arduboy.

The max score value is 255, if a player plays long enough to reach the max value, then score resets to 0, and player
adds new score to 255 to determine final score.

## How to Play
---

Two players control two paddles and try to hit the ball past the opposing player. The player with the most points when after the set amount of time that was decided by the players has passed. To score a point the ball must pass the opposing player's dog.

## Controls
---

### Menu Controls
---
Left/Right button moves menu select left/right

A button selects option

### Game Controls
---
Up/Down button moves left dog up/down

B/A moves button right dog up/down

Left/Right button pause/unpause the game

Left and Right buttons pressed at same time returns to main menu

Left and B buttons pressed at same time resets game to start, where scores are 0

### Option Controls
---
Left/Right button moves option select left/right

Up/Down button moves option select up/down

A button selects option

B button returns to menu screen

Left and Right buttons pressed at same time returns to main menu

### Credits Control
---
B button returns to menu screen

Left and Right buttons pressed at same time returns to main menu

## How to Download
---
### .hex
Using an Arduboy game uploader that supports .hex files, or any other tools that can upload .hex files to the Arduboy, upload the .hex file to your Arduboy.

### source
Rename file from Bounce-master to Bounce then upload to Arduboy using the Arduino IDE.

## Game License
---
[MIT](https://opensource.org/licenses/MIT)
