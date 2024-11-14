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
 
And finally ```sprintf()``` returns the **total number of characters written** to ```\*buffer_string``` (if success; if fail - function returns negative number)

Therefore, we have:
- 1 -> ```*buffer_string``` is pointer to array of char which accepts the data from the 2 argument (format string)
- 2 -> ```"EndIsNear-%d"``` is format string, where ```%d``` is a format specifier which accepts integer value from 3 argument
- 3 -> ```PID_string``` is variable that holds integer value of ```PID``` that consequently is concatenated with the format string (2 argument)

And only then the final result from the 2 argument will be written to ```*buffer_string```.

So? Does ```_sprintf()``` function return anything at all? No. The trick is that ```*buffer_string``` that ```generate_password``` accepts as an argument and which again is used by ```_sprintf()``` is a POINTER to other variable! ```pass_real``` inside ```main()``` function. It is empty when the program starts and only after ```generate_password()``` executes the ```pass_real``` variable (which is an array of char) is filled with the data from ```_sprintf()``` which writes the final string ```"TheEndIsNear-%d"``` to ```buffer_string```.

```"TheEndIsNear-%d"``` is the password. Well, to be precise the password is ```"TheEndIsNear-[PID]"```, where ```PID``` is the value of crackme process ```PID```.
Time to prove our words.

<img src = "https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/solutions/crackme_4/11.PNG">

As programmers we don't want to use other software to manually "construct" password when we can just generate it. Yes, just like that!

```python
import psutil


proc_name = "PIDXploit.exe"

for p in psutil.process_iter():

    if p.name() == proc_name:
        
        print("EndIsNear-"+str(p.pid))
```

Save this Python code as a file and execute while crackme is running and you will see the greatness of programming! The keygen file file will be in the crackme directory.

Again we attain our goal! Congratulations! Well done!
