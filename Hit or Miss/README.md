# HIT OR MISS
## Background
**HIT OR MISS** from https://ia802800.us.archive.org/1/items/family-computing-23/Family_Computing_Issue_23_1985_Jul.pdf

In my 8th grade computer science class in 1987 or '88, I transcribed this game as an extra credit assignment from Family Computing for Apple Basic on an Apple IIe.   My mother worked at the high school and that summer she borrowed an Apple IIe home and I fiddled with the source code and personalized it somewhat.  Late that year as a freshman, she bought a Tandy 1000 SX to replace her TRS-80.  It was an IBM PC Jr compatible with Intel 8088 processor and CGA+, but not EGA.  I then re-transcribed the game for the IBM PC and added a few different variants to it.   By the time I got to college, I had bought myself a new PC 80386 SX with VGA+ graphics.  GW Basic run stupid fast on it so this game was unplayable without modifications.   The amount of new "toys" as a freshman in college meant that I wouldn't revisit the game and at some point I lost the file with upgraded program.  The 90's were a wonderful time for diskette viruses, computer theft and hard drive failures for me.

A few years ago I found the archive.org version of the magazine and thought "I'll get that working".   But I didn't.  Until the other day when someone showed me a 3D Unity game their kid made via an LLM...

## The 

I asked GitHub copilot to write this as a Javascript game.  It was not going that great.  But I tried really hard to just "vibe code" it.   "Vibe coding" turned out to be really frustrating.

After two somewhat working versions, I asked GitHub copilot to make a third revision after correcting the AI OCR issues with the hitormiss.bas transcription from the PDF.  I'll include the chat transcript at a docx file.   

This one mirrored the BASIC logic and simulated the screen actions in a much better way using an array as the screen grid and rendering after changes.  The frame rate control using Javascript "setTimeout" around the game loop resolved the speed problem I never attempted to fix on the old 836SX.   Nevertheless, the game was still broke as there were still failures in the transcription.

So I found an on-line DOS/GW-Basic emulator:
https://www.pcjs.org/software/pcx86/lang/microsoft/basic/quickbasic/4.50/

And plugged the BASIC into it and debugged the transcription errors.

The latest version works a lot like the original version now.   I added a slight delay to the game when the HIT bar switches.   The LLM didn't have a good solution for the IBM Basic sound command so I consulted Stack Overflow to fiddle with the sound and there are now some sounds. 

I then was dissatisfied with the screen appearance and switched to a "square" fixed with font.  That was good, but I wanted more Unicode options.   I found the "KreativeSquare" font and embedded that.   Open Font License included in source listing.

Next is likely fiddling with the colors a little but.

## Original Game Summary
A summary of the article on pages 49 and 51 of the Family Computing from July 1985:

**ARCADE GAME: HIT OR MISS**
*By Joey Latimer*

### Overview:
"Hit or Miss" is an arcade-style game that combines elements of Ping-Pong, pinball, and bowling.
 The objective is to keep a projectile in play, score points, and avoid letting it hit the "MISS" rail.

### Gameplay:

The game begins with a square grid surrounded by four rails.
 The top rail is labeled "HIT," and the bottom rail is labeled "MISS."
The grid is filled with circles (point markers) and plus signs (bumpers).
A projectile is launched into play, and the player controls a paddle at the center of the grid using the "B" key to move left and the "N" key to move right.
The projectile bounces off the HIT rail and travels back toward the paddle.
Circles are worth 20 points each and disappear when hit.
 Plus signs are also worth 20 points but change the projectile's direction before disappearing.
Scoring and Challenges:

Each time the projectile hits the HIT rail, the player earns a bonus equal to the number of markers and bumpers hit.
The game ends if the projectile gets past the paddle and hits the MISS rail.
The HIT and MISS rails frequently swap positions, requiring quick reflexes and strategy.
Bonus markers (asterisks) worth 500 points appear randomly, and additional bumpers are introduced as the game progresses, increasing the challenge.

### Program Notes:
The game is designed to work within the limitations of BASIC, focusing on text-based graphics and simple movements.
The projectile's movement is based on a bounce-and-ricochet theme, with markers and bumpers adding complexity.
The HIT and MISS rail-swapping mechanic adds a unique challenge, requiring players to adapt quickly.
"Hit or Miss" is a creative and engaging game that demonstrates how BASIC can be used to create fun and challenging arcade-style gameplay.
