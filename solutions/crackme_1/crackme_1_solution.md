# === Crackme #1 solution ===

**Source**: https://crackmes.one/crackme/608ecf9333c5d458ce0ec7d4

## Solution

The author of this crackme says that is very simple one to solve, but first we have to run it and look at its "exterior". Let's see what do we have here!

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/1.PNG">
<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/2.PNG">

As author mentioned in the description this crackme accepts only numbers. So we have 1 solid clue in our search for the key. Let's open the Code Browser and see what's under the hood of this crackme!

First we need to import the file to our project and then start the analyze process. Just use the default options to run the analysis.

Step 1:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/3.PNG">

Step 2:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/4.PNG">

Step 3:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/5.PNG">

Step 4:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/6.PNG">

And we finally opened the file in a Code Browser where all magic happens! I hope you've already watched the great Ghidra introduction video I've mentioned on the main page of this tutorial series, so we may consider that you are already familiar with the Ghidra UI.

As we've discovered the crackme has it's own classic "Please enter the password... blah blah" procedure as well as the error output with the furious notification that the password you've entered is wrong. So if we know what the phrase the machine gives us when we do something wrong, we can definitely find the phrase when the password is correct.

Our next step is to find a string the crackme outputs in case we feed it with a valid password. This time we use string search and filter.
Open "Search" --> "For Strings..."

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/7.png">

Then use filter to find a word in the asswembly code that associate with a password we need. For example we take "correct" as a bait =)

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/8.PNG">

Indeed this is a good start! We found a whole program notiofication that the password we entered is a valid one. Ghidra says that it's location is **0040213c**. Double click to go to its position in assembly code.

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/9.PNG">

As you dear reader already know everything the program does, buzzes, whispers, - all of it has its own interpretation in terms of programming code. We just need to find that code. And Ghidra helps us! You see the XREF notation? It's a key to our solution: reference to the function (**FUN_00401080**) which contains code that prints out the phrase about correct password.

Click the XREF marker twice aftert you hover it:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/10.png">

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_1/11.PNG">

And there it is. The middle window shows you the assembly code of the core function that does all the work of calculating the correctness of the password you enter. Right window is the 
