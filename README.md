# Minestorm Project

This projet aims to reproduce the game Mine Storm released in 1982 on Vectrex with the raylib library. It is written in C.
In this projet, we use the math library we developed in math class. For all collisions in the game
we have to use the SAT algorithm, that we had to write ourselves.

## Authors
    - ROBION   Mathieu       - (v.caraulan@student.isartdigital.com)
	- LUANDA   Osvaldo Bento - (o.luanda@student.isartdigital.com)
    - CARAULAN Victor        - (m.robion@student.isartdigital.com)


## Mathematical tools
You can find it in the directory :
- src/Math.h and src/Math.c
- src/collisions.h src/collisions.c (SAT Algorithm)


## Gameplay:
The player controls a ship to distroy the enemies present on the screen.
If your ship collides with an enemy mine you lose a life. After you kill all the enemies, a minelayer spawns other enemies. After killing the remaining enemies you can advance to next level.

## Features:

1 or 2 playable fighters

The magnetic enemies will try to go the shortest path towards the players, even trying to wrap around the level.


## Controls:
Keyboard :

### General
    Space - Pause
    Esc   - Exit
### Player one:
    D and G - Rotation
    R       - Move
    F       - Fire (bullet)
    T       - Teleport
### Player two:
    J and L - Rotation
    I       - Move
    U       - Fire (bullet)
    O       - Teleport

