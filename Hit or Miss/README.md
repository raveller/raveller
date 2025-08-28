HIT OR MISS from
https://ia802800.us.archive.org/1/items/family-computing-23/Family_Computing_Issue_23_1985_Jul.pdf

I'm asking GitHub copilot to write this as a Javascript game.  It's not going that great.

After two somewhat working versions, I asked GitHub copilot to make a third revision after correcting the AI OCR issues with the hitormiss.bas transcription from the PDF.

This one mirrored the BASIC logic and simulated the screen actions in a much better way using an array as the screen grid and rendering after changes.   It was still broke as there were still failures in the transcription.

I found an on-line DOS/GW-Basic emulator:
https://www.pcjs.org/software/pcx86/lang/microsoft/basic/quickbasic/4.50/

And plugged the BASIC into it and debugged the transcription errors.

The final version works a lot like the original version now.   I fiddled with the sound and there now some better sounds.
