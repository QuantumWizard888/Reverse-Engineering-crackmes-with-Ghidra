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

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/4.PNG">

Clearly we've got to the point that many things uncover themselves. First, we know that phrase about INCORRECTness is stored in data segment ```004050d6```. Second, we also have found another data segment at adress ```0040508c``` with another phrase with presumably is displayed when the INPUT IS CORRECT.

Now we can also see the function which references to these phrases: ```_CheckForPassword()```. After jumping to its section we can see both the disassembled and decompiled code listing:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/5.PNG">

Things start to become even more interesting. We can see the final destination for both CORRECT and INCORRECT input that:

- Either calls ```_ShowInformationMessage()``` function if input is **CORRECT**
- Or calls ```_ShowErrorMessage()``` function if input is **NOT CORRECT**

Both of these message displaying functions actually call another internal Windows GUI function ```MessageBoxA()```:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/6.PNG">

And that is not the part that we are interested in. There must be somthing that activates the choice between those 2 phrases. And it is triggered in ```_ReadPasswordFromFile()``` function whic is inside of ```_CheckForPassword()``` function. So what we're waiting for?! IN TO THE DUNGEON! The dissasembly and decompiled "face" of ```_ReadPasswordFromFile()``` function is this:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/7.PNG">

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/8.PNG">

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/9.PNG">

Let's analyze the decompiled C code of this function:

- Lines [5-6] variables declaration
- Line 7 is where FILE pointer is declared
- Line 9 is where variable ```iVar1``` is initialized with return value of ```_PasswordFileExists()``` function
- Lines [10-12] **if section** where value of **1** is assigned ```iVar1``` variable if ```_PasswordFileExists()``` returns **1**
- Lines [13-18] **else section** if the iVar1 value is other than 1:
  - Line 14 is where we open **password.bin** file with a mode ```rb``` (read bytes) using ```_fopen()``` function
  - Line 15 we read **password.bin** file and write it contains to ```local_2e``` variable using ```_fscanf()``` function
  - Line 16 we close **password.bin** file using ```_fclose()``` function
  - Line 17 is where we use ```_strcmp()``` function to compare the string we get from **password.bin** and some ```_password``` data (we'll check this later), the return value of ```_strcmp()``` function is written to ```iVar1``` variable
- Line 19 we return ```iVar1``` value to the its calling environment

Some notes about the code.

```_PasswordFileExists()``` function usses ```_access()``` [function](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/access-waccess?view=msvc-170) to determine if a file is a read-only or not. To be short: it returns **0** if everything is OK, and -1 if not. In our decompiled code the return value "if everything IS NOT OK" (i.e. file doesn't exist or doesn't have the given access mode) is **1**. Otherwise, if the file can be opened with a mode provided the return value is **0**.

So, after the program found the file it has to read the inner part of **password.bin** and then compare it to some data located at ```_password``` data segment. Yes, we're getting close to the solution, but be patient! ```_strcmp()``` function returns **0** if contains of the **password.bin** and ```_password``` equal.

The result of comparison is written to ```iVar1``` and then it "transported" to ```_CheckForPassword()``` function which, if ```iVar1``` value is **0**, brings us to the success:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/10.PNG">

Well, we've finally approached to the gates of cybernetic Oblivion, and we are ready to know the truth about this ```_password``` data segment. What is it?

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/11_edited.PNG">

YES! The statically stored sequence of data is our password. And it is the string that has to be in **password.bin** in order to get the success messagebox.

As a last step we somehow have to write this string as BYTES to **password.bin**. And here we have 2 ways:

- Manually edit the file using HEX editor
- Create a programm that writes the data to this **password.bin** file

We are programmers, so we'll make a program! And we'll make it as simple as possible. For that purpose we will use Python. Just create a program file with a name, for example, **pswd.py**. Open it and write this code to it:

```
msg = b'W269N-WFGWX-YVC9B-4J6C9-T83GX'

with open('password.bin', 'wb') as f:

    f.write(msg)
```

Nothing special here:
1. Create ```msg``` variable with our string as bytes
2. Using context manager open **password.bin** file in READ BYTES mode
3. Write our string to file

Execute the program. The location of your Python program must be the same as **password.bin** file.

And after all the manipulations we're ready to run the crackme file again:

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_2/12.PNG">

The prize is in our hands!
