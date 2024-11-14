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
