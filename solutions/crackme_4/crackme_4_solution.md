# === psyr3n's PIDXploit solution ===

**Source**: https://crackmes.one/crackme/66ff78369b533b4c22bd0c5d

## Solution

In this crackme the author suggests that we try to dive into the process information and get its PID. Somehow this is gonna help us to solve this puzzle. And yes: no bypassing. Honest fight? Good.

We'll start using classic technique, i.e. by searching of strings that .exe file may contain.

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/1.PNG">

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/2.PNG">

For the purpose of convinience this tutorial already contains renamed variables here and there in the crackme decompiled code.

Great. We've found the first pice of the "treasure map". Now we have to analyze the decompiled source code of this crackme.

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/3.PNG">

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/4.PNG">

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/6.PNG">

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/7.PNG">

Nothing fantastic as we see. The ```main``` function contains simple scheme of user input ```scanf()``` [Line 11], input validity check [Lines 13-14] and then conditional ```if/else``` jump [Lines 14, 18]. In [Line 13] the programm calls ```strcmp()``` function to check if there is any difference between the true password string and our input string. For this section the ```int is_different``` variable is used. Then if the password is correct we'll see the desired crackme's response. And if not - well, we must try harder.

Why shouldn't we try to use that hint of this crackme author about PID? If you use **ConEmu** terminal emulator then you will see ```PID``` of running .exe (our crackme) in terminal status bar (low left corner). Or you may try the amazing **Procmon** tool by Mark Russinovich. Let's have a look.

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/9.PNG">

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/10.PNG">

Hmmm. What did we miss?

This [Line 12].

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/5.PNG">

The ```generate_password()``` function takes ```char pass_real``` array variable as an input and then returns something. But what does it return?

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/8.PNG">

Now we're getting close to the origin of this wizardry! You see the ```generate_password()``` takes the pointer to array (empty char array ```buffer_string```) and then this happenes:

- [Line 7] ```PID_string```  variable (yes, it is declared as int, but later it will be used as a part of a string) is initialized with the value of ```_getpid()``` function, which is obviously gets the PID of current process
- [Line 8] ```_sprintf()``` function takes the ```PID_string``` value, some string ```"TheEndIsNear-%d"``` and ```buffer_string```. But what is the purpose of ```_sprintf()``` function? Is it like ```printf()``` function? Not really. According to [this](https://cplusplus.com/reference/cstdio/sprintf/) documentation it takes 3 arguments (the 3rd is optional):
  - 1 -> **pointer** to a **string buffer** where the resulting C-string is stored
  - 2 -> the C string that contains a **format string** that follows the same specifications as **format** in ```printf()```
  - 3 -> depending on the **format string**, the function ```sprintf()``` may expect a sequence of additional arguments, each containing a value to be used to replace a **format specifier** in the **format string**
