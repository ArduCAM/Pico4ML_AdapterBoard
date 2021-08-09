This file is to help you use this routine. Since our ink screens are getting more and more, it is not convenient for our
maintenance, so all the ink screen programs are made into one project. A brief description of the use of this project is
here:

1. Basic information:
   This routine is verified using the corresponding module with the Pico4ML. You can see the corresponding test routine in
   the examples of the project.

2. Pin connection:
   Pin connection You can look at DEV_Config.c/h. Again, here:

   | LCD  | RST   | DC    | CS     | CLK    | MOSI   |
   | ---- | ----- | ----- | ------ | ------ | ------ |
   | PICO | GPIO7 | GPIO9 | GPIO13 | GPIO10 | GPIO11 |


3. Basic use:
   You need to execute:
   
   ​	If the directory already exists, you can go directly. If there is no build directory, execute 
   
   ​		`mkdir build `
   
   ​	Enter the build directory and type in the terminal:
   ​		`cd build `
   
   ​		`export PICO_SDK_PATH=../../pico-sdk`
   
   ​	 Where `../../pico-sdk` is your installed SDK directory 
   
   ​	Execute cmake automatically generate Makefile file, enter in the terminal:
   ​		`cmake .. 	`
   
   ​	Execute make to generate an executable file, and enter in the terminal:
   ​		`make` 
   
   ​	Copy the compiled uf2 file to pico
   
4. Directory structure (selection):

   Here is a brief introduction:

   You can see many definitions in DEV_Config.c(.h), including:

   ​	type of data; 

   ​	GPIO; 

   ​	Read and write GPIO; 

   ​	Delay: Note: This delay function does not use an oscilloscope to measure specific values. 

   ​	Module Init and exit processing:
   ​			`void DEV_Module_Init(void); `

   ​			`void DEV_Module_Exit(void);`

   ​	fonts.c(.h): for some commonly used fonts:

   ​		Ascii:
   ​			Font_7x10;

   ​			Font_11x18;

   ​			Font_16x26;

   ​		RGB565:

   ​			arducam_logo;

   ​			IMU_ICM20948;

   examples: This directory is the test program of LCD, you can see the common usage method in it;