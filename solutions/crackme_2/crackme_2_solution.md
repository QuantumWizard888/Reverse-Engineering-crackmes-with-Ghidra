# === RedXen's C File CrackMe solution ===

**Source**: https://crackmes.one/crackme/62de952533c5d44a934e997b

## Solution

The second crackme that we're going to CRACK and this one, despite being "a beginner" level puzzle, has somewthing that is worth covering, because the basis of it's solution will help us in future way more sophisticated reverse engineering challenges.

After downloading the cracke archive we shall see what it got for us. Unpack the archive and run the **C File CrackMe.exe**:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/1.PNG">

Well, well, well! What do we have here? A Win32 GUI crackme that spills out bad words without even having an INPUT? Or maybe we don't see the catch? Again it says that "something" is INCORRECT so, as logic assumes, it can not proceed to the stage where the requirements are satisfied and other messagebox pops up and says how cool we are, i.e the input IS CORRECT. But where is it, this INPUT that must be CORRECT? You can notice that this crackme archive contains some other file: **password.bin**. We're gonne look inside of it (I use HxD hex editor):

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/2.PNG">

It's empty. But the file's name hints that it can relate to the INPUT that program checks before deciding its "correctness". And how we're gonna find out where is the key? Of course using our incomparable GHIDRA!

As usual we create project, add our crackme EXE, analyze it with default settings. Where should we start? We already know that this crackme includes strings. And MessageBox (at least 1) that displays the text, depending on some conditions (which we'll understand later). So let us start from searching the strings!

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/3.PNG">

That's interesting. We've found the same string which is displayed on MessageBox. Now we have to jump to it:



WIP
