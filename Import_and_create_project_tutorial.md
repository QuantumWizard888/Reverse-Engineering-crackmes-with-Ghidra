# How to import file and create a project in Ghidra

## === How to create a project ===

To begin researching some executable or library in Ghidra you actually have to create project and import file to it.
1. Launch Ghidra, then press **File** --> **New Project**
<img src="https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/tutorial_1.JPG"  width="75%">
2. You'll see this window, here click Non-Shared Project
<img src="https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/tutorial_2.JPG"  width="75%">
3. Next, you'll have to decide where your project will be located. Name it too!
<img src="https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/tutorial_3.JPG"  width="75%">
4. That's all. You now can add files to your project and start reversing.
<img src="https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/tutorial_4.JPG"  width="75%">

## === How to import file to a project ===

It's time to add some files to your project.
1. Open the project file (.gpr). If you've already launched Ghidra click **File** --> **Open Project** when in main window.
2. After you loaded the project, pick the file you want and DRAG&DROP it into the Ghidra start window. Also you can import file using the menu **File** --> **Import File**.
3. Ghidra tries to detect the file format. In most cases, especially when reverse engineering different crackmes on Windows OS, the default choice (PE - portable executable) is fine.
<img src="https://github.com/Marco888Space/Reverse-Engineering-crackmes-with-Ghidra/blob/main/tutorial_5.PNG"  width="75%">
4. Click OK twice: first time to import the file and then when closing the file description report window.
For now you can start Code Browser and begin researching the file.
