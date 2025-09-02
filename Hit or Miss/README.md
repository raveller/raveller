HIT OR MISS from
https://ia802800.us.archive.org/1/items/family-computing-23/Family_Computing_Issue_23_1985_Jul.pdf

I asked GitHub copilot to write this as a Javascript game.  It was not going that great.

After two somewhat working versions, I asked GitHub copilot to make a third revision after correcting the AI OCR issues with the hitormiss.bas transcription from the PDF.

This one mirrored the BASIC logic and simulated the screen actions in a much better way using an array as the screen grid and rendering after changes.   It was still broke as there were still failures in the transcription.

I found an on-line DOS/GW-Basic emulator:
https://www.pcjs.org/software/pcx86/lang/microsoft/basic/quickbasic/4.50/

And plugged the BASIC into it and debugged the transcription errors.

The final version works a lot like the original version now.   I fiddled with the sound and there are now some better sounds.

A summary of the article on pages 49 and 51 of the Family Computing from July 1985:

ARCADE GAME: HIT OR MISS
By Joey Latimer

Overview:
"Hit or Miss" is an arcade-style game that combines elements of Ping-Pong, pinball, and bowling.
 The objective is to keep a projectile in play, score points, and avoid letting it hit the "MISS" rail.

Gameplay:

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

Program Notes:
The game is designed to work within the limitations of BASIC, focusing on text-based graphics and simple movements.
The projectile's movement is based on a bounce-and-ricochet theme, with markers and bumpers adding complexity.
The HIT and MISS rail-swapping mechanic adds a unique challenge, requiring players to adapt quickly.
"Hit or Miss" is a creative and engaging game that demonstrates how BASIC can be used to create fun and challenging arcade-style gameplay.
