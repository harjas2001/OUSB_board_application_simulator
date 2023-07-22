/*==============  Proforma : EEET2246 Final Programming Assignment: OUSB Simulator ============

Proforma version number: 2021.001.1 (10-06-2021)

Document Revision Details:
version 2021.001.1 (10-06-2021) - Original version

Release time:		9:00 am Thursday 10-June-2020
Submission time:	9:00 am Friday 11-June-2020 - Exactly 24 hours! 

Submission process: Via Canvas Assignments - "Final Programming Assignment" 

Assessment weight:  EEET2246 Final Programming Assignment is worth 20% of your final grade.

Late Submissions:   All submissions that are made after the submission deadline will not be
                    eligible for any grades/marks.
					
                    No extensions will be provided!
					
					Late Submissions will score zero, 0%
					
PURPOSE:
This file is the proforma for the EEET2246 Final Programming Assignment: OUSB Simulator. 

This file defines the assignment - there is no other documentation and you do NOT need a Physical
OUSB Board or the ousb.exe or ousbsim.exe file/s to complete this task. You must extend this C++ program
to cope with the functionality identified below.

GOAL:
To write a C++ Win32 Console Application in Visual Studio that implements the functionality of an OUSB
Simulator tool for PORTB, PORTD, PINC and ADC5. The tool you are being asked to write could potentially
replace the ousbsim.exe simulator you used this year. Note: PORTD is very similar to PORTB apart from 2 bits
out of the 8-bit port which must remain set to zero (i.e. bit 7 and bit 2).

You program should meet all the functional requirements and perform input error and program error checking.
It is also required to call the FileReader() and FileWriter() functions which are provided within this proforma.
Both of these functions will take care of the File IO operations, however you must call them correctly and
provide them with the correct input arguments. You are also required to check for any returned file IO errors
and deal with them as a MURPHY'S LAW error.

To put the problem into perspective, this year many EEET2246 students heavily relied on the use of the
OUSB Simulator (ousbSim.exe), which replaced the need to have a physical OUSB board. Your task for this
assessment item is to write your own version of the OUSB Simulator which is capable of simulating the
functionality of PORTB, PORTD, PINC and ADC5 to the specifications outlined within this proforma. You will
do this by using the provided FileReader() and FileWriter() function implantations within this proforma. 

The FileReader() and FileWriter() functions will handle all the File IO functionality required to complete
this task in much the same way that the provide PIPE code handled the communication functionality for previous
labs using the OUSB Board command line arguments. To achieve the correct outcome you will be required to call
FileReader() and FileWriter() functions using the correct arguments (i.e. valid references) so the FileReader()
and FileWriter() functions can correctly read and write to the appropriate files holding the state of each
port (i.e. read/write to the portb.txt, portd.txt, pinc.txt and adc5.txt files).  

Unlike the original OUSB Simulator (ousbSim.exe) which was used throughout this semester, your solution will
be writing and reading an 8-bit binary representation of the PORTB, PORTD, PINC values to the register state
files. The only exception is for the ADC 5 command, where it will write a number between 0 and 1023 to the
adc5.txt file. In the case of writing a value to either PORTB or PORTD, your solution will only accept integer
based decimal formatted values as an optional fourth input argument.

Your solution will need to support the following type of OUSB commands:

your_code.exe -r io portb		// Example of reading the PORTB value
your_code.exe -r io portd		// Example of reading the PORTD value
your_code.exe -r io pinc		// Example of reading the PINC value
your_code.exe -r ADC 5			// Example of reading the ADC5 value
your_code.exe -r io portb 10	// Example of writing 10 to PORTB using the option fourth input argument.
your_code.exe -r io portb 255	// Example of writing 255 to PORTB using the option fourth input argument.
your_code.exe -r io portd 255	// Example of writing 255 to PORTD (which will only result in 123 being 
                                // written due to the required bitwise behaviour of PORTD for bits 7 and 2)

In the case where your solution needs to write the value for PORTB and PORTD, the only accepted command
line arguments for the 4th input argument will be an integer based number between 0 to 255 in decimal format.

Note: PORTD is has very similar functionality as PORTB as it is also an 8-bit data out port. The only
difference is that PORTD always has bit-7 and bit-2 of set low (e.g. bit cleared). Hence if you write the
value 255 (0b11111111) to PORTD, your solution should only store the value 123 (0b01111011) to the PORTD
register file (i.e. portd.txt).

Note: You are NOT required to implement any other OUSB functionality other than the base commands shown
above. Please note that the solution you are being asked to develop is not required to directly replicate
the functionality of the ousbSim.exe or that of the OUSB.exe/OUSB Board, as the specifications within this
document have been simplified or changed for the purpose of this assessment task.

RESOURCES:
This is an open book assessment, so you can use any reference material you need, however this does not
include another students work/solution. The work must be your own. If similar solutions are detected, 
they will be submitted for further review in accordance with RMIT policies.


SUBMISSION:
You will be required to rename this *.cpp to the following format:
	Lab4_s1234567.cpp
where the numbers 1234567 should be your student number. There should be no space characters in the filename.

Your submission must be made via canvas. Your last submission will be used for your mark.

MARKING:
The Autotester will mark your code submission using over 70+ test vectors. As a rough guide:
- If your code meets Functional Requirements F1 through to F2.6.4, as well as meeting the
  correct Error Precedence specification defined in section F4, a mark of ~25% to 30% is achievable.

Note: Your code will not be modified at all and must compile. Code that fails to compile will score 0%.
	 
Academic Misconduct:
The submission must be your code solution in its entirety. If your code is found to be similar to
another submission it will be investigated for possible plagiarism. Please respect the academic
process and	make sure your submission complies with RMIT's Student Conduct Policy. See:
https://www.rmit.edu.au/about/governance-and-management/policies/student-conduct-policy
*/

/*
___________________________________________________________________________________________
___ GENERAL SPECIFICATIONS:

G1.	You must rename your file to Lab4_s1234567.cpp, where 1234567 is your student number.
Your filename MUST NEVER EVER contain any spaces. _under_score_is_Fine.
You do not need to include the 's' in front of your student number.

G2.	Edit the name/email address string in the main() function to your student number,
student email and student name.	The format of the student ID line is CSV (Comma Separated
Variables) with NO SPACES-
student_id,student_email,student_name
When the program is run without any operands i.e. simply the name of the executable such as:
lab4_1234567.exe
the program MUST print student ID string in Comma Separated Values (CSV) format with no
spaces. For example the following text should be outputted to the console updated with
your student details:
"1234567,s1234567@student.rmit.edu.au,FirstName_LastName"

G3.	All outputs are a single error character or a single line formatted string, as specified by
the FUNCTIONAL SPECIFICATIONS, followed by a linefeed ( endl or \n).

G4.	DO NOT add more than what is specified. Do NOT add additional information, text or
comments to the  console output.

G5.	DO NOT use 'cin', system("pause"), getchar(), gets(), etc. type functions. Do NOT ask
for user input from the keyboard.

G6. All input MUST be specified on the command line separated by blank spaces (i.e. use
the argc and argv[] input parameters). All input and output is case sensitive.

G7.	You should use the Integrated Debugging Environment (IDE) to change input arguments during
the development process. You should be using debug mode and a breakpoint at the return statement
prior to program finish in main during the process of developing your solution.

G8.	When your code exits the 'main()' function using the 'return' command, you MUST
use zero as the return value. This requirement is for exiting the 'main()' function ONLY.
A return value other than zero will indicate that something went wrong to the Autotester and
no marks will be awarded.

G9.	Do NOT put any functions or class declarations AFTER the 'main()' function - if you write
your own functions/Classes, add them BEFORE the 'main()' function. This is a requirement of the
Autotester and failure to do so will result in the Autotester not compiling your code correctly
and loss of marks, even though the code might work in your Visual Studio Environment. Hence any
user-defined functions must be written before the 'main()' function and within this file.

G10. You MUST run this file as part of a Project - No other *.cpp files or *.h files should be
added to your solution.

G11. You are not permitted to add any other #includes statements to your solution. The only
libraries permitted to be used are the ones predefined in this file.

G12. Some binary numbers within this document have the prefix 0b. This notation is now C++
compliant (depending on the C++ version), however is used within this document to avoid confusion
between decimal, hexadecimal and binary number formats within the description and specification
provided in within. For example the number 10 in decimal could be written as 0xA in hexadecimal
or 0b1010 in binary. It can equally be written with leading zeroes such as: 0x0A or
0b00001010. For output to the console screen you should only ever display the numerical
characters only and omit the 0x or 0b prefixes.

*/

/*
___________________________________________________________________________________________
___ PROGRAM STRUCTURE and FUNCTIONAL REQUIREMENTS:

HINT: For the purposes of this assessment, it is strongly recommended that you implement your
code in the order that the functional requirements appear within this proforma. 

   Summary of each section:
    - F1:	Details regarding the required cout statement for (argc==1).
	- F2:	Details regarding acceptable input argument combinations and error codes relating
			to invalid input arguments.
	- F3:	Details regarding File IO functions and what to display to console when valid
			input arguments are provided to your solution. Also covers error code situations
			for File IO based error situations.
	- F4:	Details regarding Error Precedence.

	
F1.	For situations where NO command line arguments are passed to your program:

F1.1 Your program must display your student details in the correct format to the console:
	 "1234567,s1234567@student.rmit.edu.au,FirstName_LastName"
	 Your program should then return 0 and exit.

F2.	For situations where one (1) or more command line arguments are passed to your program:

F2.1 For situations where less than three (3) command line arguments are passed to your program,
the output shall be 'P' which signals a parameter error. Then program should return 0 and exit.

Example 1:
your_code.exe -r io			// Invalid: too few arguments. Output 'P'. Then return 0 and exit.
your_code.exe -r adc		// Invalid: too few arguments. Output 'P'. Then return 0 and exit.
your_code.exe io portb		// Invalid: too few arguments. Output 'P'. Then return 0 and exit.

F2.2 For situations where more than four (4) command line arguments are passed to your program,
the output shall be 'P' which signals a parameter error. Then program must return 0 and exit.

Example 2:
your_code.exe -r io portb 50	// Valid: Example that sets the value of PORTB to 50.
your_code.exe -r io portb 50 1	// Invalid: too many arguments. Output 'P'. Then return 0 and exit.
your_code.exe -r adc 5 50 1		// Invalid: too many arguments. Output 'P'. Then return 0 and exit.

F2.3 Check that the first input argument is "-r" or "-R". The input should not be case sensitive.
If the first argument is not "-r" or "-R", then the output shall be 'R', which signals an error and
the program must return 0 and exit. No other output other than 'R' should appear on the console.

Example 3:
your_code.exe -r io portb  	// Valid: Example that reads the value of PORTB.
your_code.exe -R adc 5 		// Valid: Example that reads the value of ADC_5.
your_code.exe R io portb	// Invalid: Output should be 'R'. Then program should return 0 and exit.
your_code.exe io portb 20	// Invalid: Output should be 'R'. Then program should return 0 and exit.
your_code.exe r io portb 2	// Invalid: Output should be 'R'. Then program should return 0 and exit.
your_code.exe t5 adc 5		// Invalid: Output should be 'R'. Then program should return 0 and exit.

F2.4 Check that the second input argument is "io" or "adc". The input should not be case sensitive.
If the second input argument is not "io" or "adc", then the output shall be 'C', which signals an
invalid register type is requested and the program should return 0 and exit. No other output other
than 'C' should appear on the console.

Example 4:
your_code.exe -r IO pinc	   // Valid: Example that reads the value of PINC.
your_code.exe -r io portd	   // Valid: Example that reads the value of PORTD.
your_code.exe -R ADC 5         // Valid: Example that reads the value of ADC_5.
your_code.exe -r ioportb 2	   // Invalid: Output should be 'C'. Then program should return 0 and exit.
your_code.exe -r adc5 5        // Invalid: Output should be 'C'. Then program should return 0 and exit.

F2.5 Check that the third input argument is a valid register argument (e.g. "portb", "portd", "pinc"
or "5" for the ADC command). The input should not be case sensitive. If the third input argument is not
"portb", "portd", "pinc" or "5", then the console output shall be 'S', which signals a register selection
error and the program should return 0 and exit. No other output other than 'S' should appear on the console.

Example 5:
your_code.exe -r io portD 8	   // Valid: Example that writes the value 8 to PORTD.
your_code.exe -r io pwm 3      // Invalid: Output should be 'S'. Then program should return 0 and exit.
your_code.exe -r io adc 33     // Invalid: Output should be 'S'. Then program should return 0 and exit.


F2.6 Check if there is a valid fourth input argument. The presence of a fourth argument is optional in some
cases and not allowed in others. Its presences determines what value should be written to either PORTB or
PORTD. However before acting on the value, your solution should first check if the (optional) fourth argument
is both allowed and valid.

F2.6.1 If there is a fourth input argument and the first, second and third input arguments are "-r", "io" and
"pinc", respectively, the output shall be 'P', and the program should return 0 and exit. No other output other
than 'P' should appear on the console. 

F2.6.2 If there is a fourth input argument and the first, second and third input arguments are "-r", "adc" and
"5", respectively, the output shall be 'P', and the program should return 0 and exit. No other output other
than 'P' should appear on the console. 

Example 6:
your_code.exe -r io PORTD 80	   // Valid: Example that writes the value 80 to PORTD.
your_code.exe -r io pinc 45		   // Invalid: Output should be 'P'. Then program should return 0 and exit.
your_code.exe -r io adc 5 		   // Invalid: Output should be 'P'. Then program should return 0 and exit.


F2.6.3 If there is a fourth argument, and the first and second input arguments are "-r" and "io" with the third
argument being either "portb" or "portd", check that all characters in the fourth argument are all numerical
ASCII characters. No other characters other than '1','2','3','4','5','6','7','8','9' and '0' should be in any
position. If any other characters are found in the fourth argument, then the output shall be 'N', which signals
an invalid numerical value and the program should return 0 and exit. No other output other than 'N' should
appear on the console.

Example 7:
your_code.exe -r io portD 80	   // Valid: Example that writes the value 80 to PORTD.
your_code.exe -r io PORTb 0		   // Valid: Example that writes the value 0 to PORTB.
your_code.exe -r io portb +45	   // Invalid: Output should be 'N'. Then program should return 0 and exit.
your_code.exe -r io portd 80.0	   // Invalid: Output should be 'N'. Then program should return 0 and exit.

F2.6.4 If there is a fourth argument, and the first and second input arguments are "-r" and "io" with the third
argument being either "portb" or "portd", check that all characters in the numerical value of the fourth argument
must be between 0 - 255 inclusive (and only whole integer values should be accepted). If the value is outside
this range, then the output shall be 'N', and the program should return 0 and exit. No other output other than
'N' should appear on the console.

Example 8:
your_code.exe -r io portb 45.0	   // Invalid: Output should be 'N'. Then program should return 0 and exit.
your_code.exe -r io portd 256	   // Invalid: Output should be 'N'. Then program should return 0 and exit.
your_code.exe -r io portd -1	   // Invalid: Output should be 'N'. Then program should return 0 and exit.

**********************************************************************************************************
NOTE:
 As a rough guide, if your code meets Functional Requirements F1 through to F2.6.4, as well as
 meeting the correct Error Precedence specifications defined in section F4 and correctly outputs the correct
 values or error codes to the console (see section F3), a mark of ~25 to 30% is achievable.
 
 To achieve the remaining marks, your code must call the provided File IO functions with correctly formed
 string arguments/references. The format of the file IO string arguments and the exact format of the required
 console output for all valid input arguments is provided below, as defined in F3. The only exception is 
 MURPHY'S LAW based file IO error handling (which is also discussed in section F3).
 
 F3 Functional Requirements concern all the File IO operations, where as F4 concerns Error Precedence.
**********************************************************************************************************

*/

/*

F3. For each of the commands discussed above which don't result in an error code situation, there are
file IO operation/s that need to be completed in addition to outputting a correctly formatted string to the
console. Your solution should call the provided File IO function/s by passing the correct arguments for each
situation. 

Note: You do not need to modify the provided FileWriter() and FileReader() function implementations in order
to use them. It is possible to score 100% by just using them as provided. If you choose to not call the
File IO functions you can still achieve some marks by outputting the required (i.e. correctly formatted)
console output for all error code situations and the OUSB write based commands outlined in F3.1 and F3.2.

Note: Section F3.1 and F3.2 will discuss the OUSB write based command requirements and Section F3.3 and
F3.4 will discuss the OUSB read based requirements.

- Short description of provided FileWriter() function:
	Prototype:
			errno_t FileWriter(const char* filename, const char* strToWrite);
	Parameters: 
			filename	 - Null-terminated string that hold the name of the file to work on.
			strToWrite   - Null-terminated source string that will be written to the first line of the file.
			Return Value - Zero if successful; an error code on failure.

- Short description of provided FileReader() function:
	Prototype:
			errno_t FileReader(const char* filename, char* resultStr, int byteCount = maxByteSize);
	Parameters: 
			filename	 - Null-terminated string that hold the name of the file to work on.
			resultStr    - Location of the destination string (null-terminated).
			byteCount	 - Used to limit the number of bytes read in from the file (default maxByteSize)
			Return Value - Zero if successful; an error code on failure.


______ Write: "portb.txt" file instructions:
F3.1 If there is a valid fourth input argument passed to your solution, and the first, second and third
input arguments are "-r", "io" and "portb", respectively: Your solution must convert the fourth input
argument value to an 8-bit binary representation (e.g. b7,b6,b5,b4,b3,b2,b1,b0). It is suggested that
the 8-bit binary representation be stored in a null terminated character array (under normal conditions).

Note: The console output of all 8-bit binary strings must be a string of eight characters with each character
either being a zero ('0') or a one ('1') character. The MSB (i.e. bit-7) will be the left-hand most value and
the LSB being bit-0 will be the most right-hand value (e.g. b7,b6,b5,b4,b3,b2,b1,b0). The same will apply to
other sections in F3.

F3.1.1 If the value of the fourth input argument is valid, your solution should then attempt to call the
FileWriter() function with the first argument of the FileWriter() function being set to "portb.txt" and
the second arguments as a reference to the null terminated character array containing the 8-bit binary
representation of the value that should be written to the portb.txt file.

F3.1.2 If no error was returned by the FileWriter() function, your solution should display the decimal value
of the fourth input argument to the console followed by a comma character and a space (i.e. ", "), which is
then followed by the 8-bit binary representation of the input value. As an example, the exact format of
console output for a value of 64 as the fourth input argument would be:
64, 01000000
No other characters should be displayed to the console window.

F3.1.3 If no errors occurred, then your solution should return 0 and exit. Else, if an error occurred during
any part of the process, nothing other than the error code should be displayed to the console. Any error
associated with the file IO operation (i.e. the provided FileWriter() function) should be treated as a
MURPHY'S LAW error and nothing other than 'Z' should be displayed to the console. Your solution should
always return 0 and exit.

Example 9:
 - Your code is executed with following arguments:
	  your_code.exe -r io portb 32
 - Your code should determine that it is required to convert the number 32 to an 8-bit binary number (0b00100000)
 - It should then call the FileWriter() with the correct arguments so that the portb.txt file contains the
   string: 00100000
 - If no errors occur, it should then print the specified output F3.1.2 to the console. Hence, nothing other
   than the following string should be displayed to the console):
32, 00100000
 - Then your code will return 0; and exit.
 - You should then manually check that the portb.txt file holds the string "00100000" as its first line in
   the file. 

   
______ Write: "portd.txt" file instructions:
F3.2 If there is a valid fourth input argument passed to your solution, and the first, second and third
input arguments are "-r", "io" and "portd", respectively: Your solution must convert the fourth input
argument value to an 8-bit binary representation (e.g. b7,b6,b5,b4,b3,b2,b1,b0). It is suggested that
the 8-bit binary representation be stored in a null terminated character array (under normal conditions).

F3.2.1 If the value of the fourth input argument is valid, your solution should then attempt to call the
FileWriter() function with the first argument of the FileWriter() function being set to "portd.txt" and
the second arguments as a reference to the null terminated character array containing the 8-bit binary
representation of the value that should be written to the portd.txt file with bits 7 and 2 set to zero (0).
Hence, if "255" was the fourth input argument (i.e. 0b11111111) the final string that will be written to
the portd.txt file must become "01111011" (i.e. 0b01111011).

F3.2.2 If no error was returned by the FileWriter() function, your solution should display the decimal value  
of the fourth input argument to the console followed by a comma character and a space (i.e. ", "), which is
then followed by the 8-bit binary representation of the input value. As an example, the exact format of
console output for a value of 255 as the fourth input argument would be:
255, 11111111
No other characters should be displayed to the console window.

Note: The console output should retain bits 7 and 2 in all cases (i.e. The console output should not have 
bit 7 and 2 should cleared) as this is how the real OUSB Board and ousb.exe interface application deals
with such situations in the real world.

F3.2.3 If no errors occurred, then your solution should return 0 and exit. Else, if an error occurred during
any part of the process, nothing other than the error code should be displayed to the console. Any error
associated with the file IO operation (i.e. the provided FileWriter() function) should be treated as a
MURPHY'S LAW error and nothing other than 'Z' should be displayed to the console. Your solution should
always return 0 and exit.

Example 10:
 - Your code is executed with following arguments:
	  your_code.exe -r io portd 127
 - Your code should determine that it is required to convert the number 127 to an 8-bit binary number (0b01111111)
 - It should then call the FileWriter() with the correct arguments so that the portd.txt file contains the
   string: 01111011
   NOTE: Bit 2 was required to be cleared and set to 0. Bit 7 in this example was already set to 0.
 - If no errors occur, it should then print the specified output F3.2.2 to the console. Hence, nothing other
   than the following string should be displayed to the console):
127, 01111111
 - Then your code will return 0; and exit.
 - You should then manually check that the portd.txt file holds the string "01111011" as its first line in
   the file.


______ Read: "portb.txt" file instructions:
F3.3 If there are only three valid input arguments passed to your solution, and the first, second and third
input arguments are "-r", "io" and "portb", respectively: Your solution must call the FileReader() function with
the first argument of the FileReader() function being set to "portb.txt" and the second argument as a reference
to a suitably sized null terminated character array that can store an 8-bit binary representation of a number
between 0 and 255 (under normal conditions).

Note: Under normal operation the string containing the 8-bit binary value will be a string of eight characters
with each character either being a zero ('0') or a one ('1'). The MSB (i.e. bit-7) will be the left-hand most
value and LSB being bit-0 will be the most right-hand value (e.g. b7,b6,b5,b4,b3,b2,b1,b0). The same will apply
for portd.txt (F3.4) and pinc.txt (F3.5).

F3.3.1 Your solution should then check that the returned string from the FileReader() only contains the numerical
characters '0' or '1' and that when the string is converted to an decimal integer it is between the values 0 and
255, inclusive. The string should also have eight (8) characters followed by a null terminator to be valid. If
the string fails to comply with these specifications or a file error occurred, your solution should treat the
situation as a MURPHY'S LAW error and nothing other than 'Z' should be displayed to the console. Your solution
must always return 0; and exit.

F3.3.2 If the value returned by the FileReader() function is valid, your solution should then display the string
as its (converted) decimal value followed by a comma character and a space (i.e. ", "), which is then followed by
the original 8-bit binary representation string returned by the FileReader() function (or its second argument
reference). As an example, if the portb.txt file contains the string "11111110", the exact format of console
display output should be:
254, 11111110
No other characters should be displayed to the console window.

F3.3.3 If no errors occurred, then your solution should return 0 and exit. Else, if an error occurred during
any part of the process, or the value returned by the FileReader() contains anything other than a string that
represents an 8-bit binary value, nothing other than the error code should be displayed to the console. Any error
associated with the file IO operation (i.e. the provided FileReader() function) or the returned string containing
the 8-bit bit binary value should be treated as a MURPHY'S LAW error and nothing other than 'Z' should be
displayed to the console. Your solution must always return 0 and exit.

Example 11:
 - A file called "portb.txt" contains the string "00011111" on the first line.
 - Your code is executed with the following arguments:
	  your_code.exe -r io portb
 - Your code must call the FileReader() function with the correct arguments so that the value within the
   portb.txt is converted to a decimal value and then the appropriate sting is displayed to the console
   output as specified in F3.3.2 to the console. Hence, nothing other than the following string should be
   displayed to the console):
31, 00011111
 - Then your code will return 0; and exit.

Example 12:
 - No "portb.txt" exists.
 - Your code is executed with the following arguments:
	  your_code.exe -r io portb
 - Your code must call the FileReader() function, where the string "00000000" will be return to the reference
   argument or return value of the FileReader() function. Note: The provided FileReader() function will
   automatically create a portb.txt file and save the the string "00000000" as the first line.
 - Your code should then display the following string to the console:
0, 00000000
 - Then your code will return 0; and exit.
 
Example 13:
 - A file called "portb.txt" contains the string "0101" on the first line.
 - Your code is executed with the following arguments:
	  your_code.exe -r io portb
 - Your code must call the FileReader() function with the correct arguments so that the value within the
   portb.txt is tested. As the returned value in this example does not represent a valid 8-bit binary
   value, nothing other than 'Z' should be displayed to the console:	  
Z	  
 - Then your code will return 0; and exit. 
 
 
______ Read: "portd.txt" file instructions:
F3.4 If there are only three valid input arguments passed to your solution, and the first, second and third
input arguments are "-r", "io" and "portd", respectively: Your solution must call the FileReader() function with
the first argument of the FileReader() function being set to "portd.txt" and the second argument as a reference
to a suitably sized null terminated character array that can store an 8-bit binary representation of a number
between 0 and 255 (under normal conditions).

F3.4.1 Your solution should then check that the returned string from the FileReader() only contains the numerical
characters '0' or '1' and that when the string is converted to an decimal integer it is between the values 0 and
255, inclusive. The string should also have eight (8) characters followed by a null terminator to be valid. 
Additionally, your solution should check that the string returned by the FileReader() represents an 8-bit binary
value with bit-7 (MSB) and bit-2 not set to zero ('0'), as this is a requirement for the PORTD value to be valid.
If the string fails to comply with these specifications or a file error occurred, your solution should treat the
situation as a MURPHY'S LAW error and nothing other than 'Z' should be displayed to the console. Your solution
must always return 0; and exit.

F3.4.2 If the value returned by the FileReader() function is valid, your solution should then display the string
as its (converted) decimal value followed by a comma character and a space (i.e. ", "), which is then followed by
the original 8-bit binary representation string returned by the FileReader() function (or its second argument
reference). As an example, if the portd.txt file contains the string "01111011", the exact format of console
display output should be:
123, 01111011
No other characters should be displayed to the console window.

F3.4.3 If no errors occurred, then your solution should return 0 and exit. Else, if an error occurred during
any part of the process, or the value returned by the FileReader() contains anything other than a string that
represents an 8-bit binary value with bit-7 (MSB) and bit-2 not set to zero ('0'), nothing other than
the error code should be displayed to the console. Any error associated with the file IO operation (i.e. the
provided FileReader() function) or the returned string containing the 8-bit bit binary value should be treated
as a MURPHY'S LAW error and nothing other than 'Z' should be displayed to the console. Your solution must always
return 0 and exit.

Example 14:
 - A file called "portd.txt" contains the string "01111011" on the first line.
 - Your code is executed with the following arguments:
	  your_code.exe -r io portd
 - Your code must call the FileReader() function with the correct arguments so that the value within the
   portd.txt is converted to a decimal value and then the appropriate sting is displayed to the console
   output as specified in F3.4.2 to the console. Hence, nothing other than the following string should be
   displayed to the console):
123, 01111011
 - Then your code will return 0; and exit. 

 Example 15:
 - A file called "portd.txt" contains the string "11111011" on the first line (which is invalid for PORTD).
 - Your code is executed with the following arguments:
	  your_code.exe -r io portd
 - Your code must call the FileReader() function with the correct arguments so that the value within the
   portd.txt is tested. As the value in this example has bit-7 set to a value other than '0', then nothing
   other than 'Z' should be displayed to the console:
Z
 - Then your code will return 0; and exit. 

 
______ Read: "pinc.txt" file instructions:
F3.5 If there are only three valid input arguments passed to your solution, and the first, second and third
input arguments are "-r", "io" and "pinc", respectively: Your solution must call the FileReader() function with
the first argument of the FileReader() function being set to "pinc.txt" and the second argument as a reference
to a suitably sized null terminated character array that can store an 8-bit binary representation of a number
between 0 and 255 (under normal conditions).

Note: Much of the functionality of between reading the pinc.txt file is the same as reading the portb.txt file.

F3.5.1 Your solution should then check that the returned string from the FileReader() only contains the numerical
characters '0' or '1' and that when the string is converted to an decimal integer it is between the values 0 and
255, inclusive. The string should also have eight (8) characters followed by a null terminator to be valid. If
the string fails to comply with these specifications or a file error occurred, your solution should treat the
situation as a MURPHY'S LAW error and nothing other than 'Z' should be displayed to the console. Your solution
must always return 0; and exit.

F3.5.2 If the value returned by the FileReader() function is valid, your solution should then display the string
as its (converted) decimal value followed by a comma character and a space (i.e. ", "), which is then followed by
the original 8-bit binary representation string returned by the FileReader() function (or its second argument
reference). As an example, if the pinc.txt file contains the string "10101101", the exact format of console
display output should be:
173, 10101101
No other characters should be displayed to the console window.

F3.5.3 If no errors occurred, then your solution should return 0 and exit. Else, if an error occurred during
any part of the process, or the value returned by the FileReader() contains anything other than a string that
represents an 8-bit binary value, nothing other than the error code should be displayed to the console. Any error
associated with the file IO operation (i.e. the provided FileReader() function) or the returned string containing
the 8-bit bit binary value should be treated as a MURPHY'S LAW error and nothing other than 'Z' should be
displayed to the console. Your solution must always return 0 and exit.

Example 16:
 - A file called "pinc.txt" contains the string "01011111" on the first line.
 - Your code is executed with the following arguments:
	  your_code.exe -r io pinc
 - Your code must call the FileReader() function with the correct arguments so that the value within the
   pinc.txt is converted to a decimal value and then the appropriate sting is displayed to the console
   output as specified in F3.5.2 to the console. Hence, nothing other than the following string should be
   displayed to the console):
95, 01011111
 - Then your code will return 0; and exit.

Example 17:
 - A file called "pinc.txt" contains the string "0101" on the first line.
 - Your code is executed with the following arguments:
	  your_code.exe -r io pinc
 - Your code must call the FileReader() function with the correct arguments so that the value within the
   pinc.txt is tested. As the value in this example is not a valid string containing a valid 8-bit binary
   string, then nothing other than 'Z' should be displayed to the console:
Z
 - Then your code will return 0; and exit.

Example 18:
 - A file called "pinc.txt" contains the string "0201" on the first line.
 - Your code is executed with the following arguments:
	  your_code.exe -r io pinc
 - Your code must call the FileReader() function with the correct arguments so that the value within the
   pinc.txt is tested. As the value in this example is not a valid string containing a valid 8-bit binary
   string, then nothing other than 'Z' should be displayed to the console:
Z
 - Then your code will return 0; and exit.

 
______ Read: "adc5.txt" file instructions:
F3.6 If there are only three valid input arguments passed to your solution, and the first, second and third
input arguments are "-r", "adc" and "5", respectively: Your solution must call the FileReader() function with
the first argument of the FileReader() function being set to "adc5.txt" and the second argument as a reference
to a suitably sized null terminated character array that can store the integer number representation of a number
between 0 and 1023 (under normal conditions).

F3.6.1 Your solution should then check that the returned string from the FileReader() only contains the numerical
characters '0', '1', '2', '3', '4', '5', '6', '7', '8' or '9' and that when the string is converted to an integer
it is between the values 0 and 1023, inclusive. The string should also be followed by a null terminator to be valid.
If the string fails to comply with these specifications or a file error occurred, your solution should treat the
situation as a MURPHY'S LAW error and nothing other than 'Z' should be displayed to the console. Your solution must
always return 0; and exit.

F3.6.2 If the value returned by the FileReader() function is valid, your solution should then display the string
as a decimal value followed by a comma character and a space (i.e. ", "), which is then followed by a percentage
of full scale deflection (i.e. out of 1023) calculated using integer arithmetic. Therefore all percentage values
shall be whole numbers with no decimal places (or floating point numbers). As an example, if the adc5.txt file
contains the string "512", the exact format of console display output should be:
512, 50%
No other characters should be displayed to the console window.

F3.6.3 If no errors occurred, then your solution should return 0 and exit. Else, if an error occurred during
any part of the process, or the value returned by the FileReader() contains anything other than a string that
represents an integer value between 0 - 1023, nothing other than the error code should be displayed to the console.
Any error associated with the file IO operation (i.e. the provided FileReader() function) or the returned string
containing an invalid value should be treated as a MURPHY'S LAW error and nothing other than 'Z' should be
displayed to the console. Your solution must always return 0 and exit.

Example 17:
 - A file called "adc5.txt" contains the string "512" on the first line.
 - Your code is executed with the following arguments:
	  your_code.exe -r adc 5
 - Your code must call the FileReader() function with the correct arguments so that the value within the
   adc5.txt is converted to a integer and then the appropriate sting is displayed to the console output
   as specified in F3.6.2 to the console. Hence, nothing other than the following string should be
   displayed to the console):
512, 50%
 - Then your code will return 0; and exit.

Example 18:
 - A file called "adc5.txt" contains the string "353" on the first line.
 - Your code is executed with the following arguments:
	  your_code.exe -r adc 5
 - Your code must call the FileReader() function with the correct arguments so that the value within the
   adc5.txt is converted to a integer and then the appropriate sting is displayed to the console output
   as specified in F3.6.2 to the console. Hence, nothing other than the following string should be
   displayed to the console):
353, 34%
 - Then your code will return 0; and exit.

Note: If your solution outputs a string like "353, 34.5%" to the console it will be marked as not meeting
specification. The achieve marks for this exact input your solution should only output the following to
the console:
353, 34%
 
Example 19:
 - A file called "adc5.txt" contains the string "1024" on the first line.
 - Your code is executed with the following arguments:
	  your_code.exe -r adc 5
 - Your code must call the FileReader() function with the correct arguments so that the value within the
   adc5.txt is tested. As the value in this example does not represent a valid ADC value, then nothing
   other than 'Z' should be displayed to the console:
Z
 - Then your code will return 0; and exit.


F4. Error Precedence. 

The following text lists errors you must detect and a priority of testing/output.

NOTE: All error code outputs are a single character followed by a newline (endl or '\n').
DO NOT add more than what is specified; DO NOT add additional information to the console output.

The order of errors can theoretically be checked in any order, however if multiple errors
occur during a program execution event, your program should only display one error code
followed by a newline character and then exit (with a return 0;). The displayed error
codes to the console window should occur in this order:
	'P' - Incorrect number of input command line arguments (less than 3 and more than 4)
	'R' - Invalid first command line argument (first argument should be "-r" or "-R" only)
	'C' - Invalid second command line argument (second argument should be "io" or "acd")
	'S' - Invalid third command line argument (third argument should be "portb", "portd", "pinc" or "5")
	'N' - Invalid fourth command line argument (optional fourth argument must be numerical characters only)
	'N' - Invalid fourth command line argument (fourth argument must be in the correct range)
	'Z' - MURPHY'S LAW (undefined error)

Therefore, if an invalid numerical command line argument (input argument four) with an invalid first input
argument are passed to the program, the error code that should be displayed to the console in this case
would be 'R'. Displaying 'N' or any other error code would be result in a loss of marks.

Example 20:
your_code.exe -s io portb 330     // InValid: output should be 'R'. Then program should return 0 and exit.
your_code.exe -s io portd 40.0    // InValid: output should be 'R'. Then program should return 0 and exit.
your_code.exe -s io portb 0x40    // InValid: output should be 'R'. Then program should return 0 and exit.
your_code.exe -R i portb 0x45     // InValid: output should be 'C'. Then program should return 0 and exit.


___ End of PROGRAM STRUCTURE and FUNCTIONAL REQUIREMENTS ____
___________________________________________________________________________________________


Other considerations:

- Your program should only display a single line on the console for all function requirements,
followed by a newline character and then exit (with a return 0).

- It is recommended that you write your program in the order of the function requirements are listed.

- Although there are comments to help you with small code fragments provided in the proforma, you don't
have to use them. You are free to tackle the problem the way you see fit.  The Autotester
will only look at the output behaviour of your program.

- The Autotester will test the console as well as the portb.txt, portd.txt, pinc.txt and adc5.txt text
files your program creates via the use of the FileReader() and FileWriter() functions. The Autotester
will also produce its own portb.txt, portd.txt, pinc.txt and adc5.txt files that your program will need
to read and preform work on.

- If you can't get part of the requirements working, (especially the later requirements), then don't
make the mistake of letting erroneous code affecting the behaviour of the earlier requirements.
In most cases it will be better to remove the erroneous code and get marks for the easier requirements.

- Compare the behaviour of your solution to that of the sample binary

- Use debug mode and breakpoints while you are developing and debugging your solution.

- Don't forget that there are no late submissions. Failure to submit on time will result in a mark of 0%.

- Remember that code that does not compile will score zero (0%).  0% does not scale, so please make
sure you code compiles before submitting it.
____________________________________________________________________________________________
*/
// These are the libraries you are allowed to use to write your solution. Do not add any
// additional libraries as the auto-tester will be locked down to the following:
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <windows.h> 
#include <cmath>
#include <errno.h>  
// Do NOT Add or remove any #include statements to this project!!
// All library functions required should be covered by the above
// include list. Do not add a *.h file for this project as all your
// code should be included in this file.

using namespace std; // Please do not remove this line

// Define any global variables here:
const int maxByteSize = 10;	// Used by  FileWriter() and FileReader() to size buffers
const int MAXRANGE = 255;
const int MINRANGE = 0;

// WRITE YOUR FUNCTION PROTOTYPES HERE (OPTIONAL, however if you write lots of functions
// having a prototype list will mean that they can be written in any order)

//     Provided functions:
errno_t FileWriter(const char* filename, const char* strToWrite);
errno_t FileReader(const char* filename, char* resultStr, int byteCount = maxByteSize);
bool ascvalid(char* arrofarg, int valadc = 0);
void convertingtobinary(int x, char* placement);
void asciiconv(char* arrayofchar);
int funcreqbas(char* argfirst, char* argsecond, char* argthird);
bool checkbin(char* buffstem);
//     Example of optional function prototype:
bool valid(char* cstring);  // You are free to use this or discard.



// Any standalone function definitions go here:

/* 
 FileWriter() description:
   The FileWriter() function is used to write the contents of a text file.
   This function is fully implemented and requires no modification to work,
   though you can modify it if you wish too.
     - Uses: 
           - The function must be used with 2 arguments.
           - The function will automatically create the file or overwrite
             the file if it already exists. The name of the file 
             is determined by the reference passed by the first argument.
           - The second argument is the string to write to the file.
           - Both input arguments are const references.
     - Dependencies:
           - Uses fstream library (file stream library)  #include <fstream>
           - Uses errno to return error code on failure.
     - Inputs: 
           - First argument is a reference to the location of the name of the
             file to write too.
           - Second argument is a reference to the char array (data) that
             will be written to the file.
     - Outputs:
           - The function returns a zero (false) if no error occurs during the
             file writing process and returns a an error code on failure.
*/
errno_t FileWriter(const char* filename, const char* strToWrite)
{
	ofstream outfile;		// Create outfile object

	outfile.open(filename, ios::out | ios::trunc);
	if (!outfile.fail())
	{
		outfile << strToWrite;
		outfile.close();
	}
	else					// If file operation did not work
	{
		return errno;		// return error code
	}
	return errno;			// return error code (0 = success - no error to report)
}
/*
 FileReader() description:
   The FileReader() function is used to read the contents of a text file
   and return the first line of the file contents. This function is fully
   implemented and requires no modification to work, though you can modify 
   it if you wish too.
     - Uses: 
           - The function can be used with either 2 arguments or 3 due to 
             ByteCount having a default value of maxByteSize (10) bytes. 
           - The function will automatically remove any of the following
             character types ' ', '\r', '\n', '\t' and replace with '\0'. 
           - The function will call the FileWriter() function to create a file
             if the file it is trying to read does not exist. The name of
			 the file is determined by the reference passed by the first
			 argument. In the case of the "adc5.txt" file it will save "0",
             in all other cases it will save the string "00000000" to the file
             if the file does not exist.
           - The first input argument is a const reference, however the function
             can modify the memory pointed to by the second input argument.
           - Function only reads in maxByteSize (or less) from first line -
             ignores all other content in the file.
     - Dependencies:
           - Requires FileWriter() function.
           - Uses fstream library (file stream library)  #include <fstream>
           - Uses errno to return error code on failure.
     - Inputs: 
           - First argument is a reference to the location of the name of the
             file to read.
           - Second argument is a reference to the location of the destination
             string (null-terminated).
           - Third (optional) argument can be used to limit the number of
             bytes read in from the file (default is set to maxByteSize)
     - Outputs:
           - The function returns a zero (false) if no error occurs during the
             file writing process and returns a an error code on failure.
*/
errno_t FileReader(const char* filename, char* resultStr, int byteCount)
{
	// create a buffer array for file read operations.
	char buffer[maxByteSize + 1] = {};

	if (byteCount <= 0 || byteCount >= maxByteSize)
		byteCount = maxByteSize;

	ifstream infile;				// Create infile object
	infile.open(filename, ios::in);
	if (!infile.fail())
	{
		while (!infile.eof())		// runs until end of file
		{
			infile.getline(buffer, byteCount);
			break;					// read only the first line of the file
		}
		infile.close();

		// remove ' ', '\r', '\n', '\t' and replace with '\0'
		for (int i = 0; buffer[i] != '\0'; i++)
		{
			if (buffer[i] == '\r' || buffer[i] == '\n' || buffer[i] == '\t' || buffer[i] == ' ')
				buffer[i] = '\0';
		}

		int i = 0;
		for (i = 0; buffer[i] != '\0'; i++) // copy characters to result string till '\0' or up until byteCount limit
		{
			resultStr[i] = buffer[i];
			if (i >= byteCount) break;
		}
		resultStr[i + 1] = '\0';			// ensure result array is null terminated
	}
	else
	{
		// create a new file with "00000000" as first line
		for (int i = 0; i < 8; i++) 		// copy 8 characters to result string
			resultStr[i] = '0';
		resultStr[8] = '\0';				// ensure result array is null terminated

		//TESt for github
		// if adc5.txt is to be created, only put one '0' in the file
		if (!(strcmp(filename, "adc5.txt")))
			resultStr[1] = '\0';			// null terminate after first character

		// Attempt to create a new file
		errno = 0;					// clear errors from file not existing so we can track future errors
		if (FileWriter(filename, resultStr))
			return errno;			// return error code (0 = success - no error to report)
	}

	return errno;					// return error code (0 = success - no error to report)
}

// NOTE: You are free to use this or discard.
bool valid(char* str)
{
	// Suggested - check if each digit is numerical up to the null terminator

	// Suggested - check if the str length is less than 5 and at least 1 character long

	return true;
}

// All other user defined functions to be defined below and above main()  
//    - NO exceptions !!!  Do NOT define function below main() as your
//      code will fail to compile in the auto-tester.


// WRITE ANY USER DEFINED FUNCTIONS HERE (optional)

unsigned int changearray = 0;

bool ascvalid(char* arrofarg, int valadc)
{
	bool arraying = true;
	for (int i = 0; arrofarg[i] != '\0'; i++)
	{
		if (arrofarg[i] >= 48 && arrofarg[i] <= 57)
		{
			arrofarg[i] = arrofarg[i];
		}
		else
		{
			return !arraying;
		}
	}

	changearray = (unsigned int)atoi(arrofarg);

	if (valadc > 0)
	{
		if (changearray < 0 || changearray > 1023)
		{
			arraying = false;
		}
	}
	else if (valadc == 0)
	{
		if (changearray < 0 || changearray > 255)
		{
			arraying = false;
		}
	}

	return arraying;
}

bool checkbin(char* buffstem)
{
	bool arraying = true;
	if (strlen(buffstem) != 8)
	{
		return !arraying;
	}

	for (int i = 0; buffstem[i] != '\0'; i++)
	{
		if (buffstem[i] != '0' && buffstem[i] != '1')
		{
			arraying = false;
		}
	}

	return arraying;
}

void convertingtobinary(int x, char* placement)
{
	int bina = 0;
	int ans = x;
	int incre[maxByteSize] = {};

	for (int i = 0, j = 7; i <= 7; i++, j--)
	{
		bina = ans % 2;
		ans = ans / 2;
		incre[i] = bina;
		placement[j] = incre[i] + '0';
	}

}


void asciiconv(char* arrayofchar)
{
	for (int i = 0; i <= strlen(arrayofchar); i++)
	{
		if (arrayofchar[i] >= 65 && arrayofchar[i] <= 90)
		{
			if (arrayofchar[i] == '\0')
			{

			}
			else
			{
				arrayofchar[i] = arrayofchar[i] + 32;
			}
		}
	}
}

int funcreqbas(char* argfirst, char* argsecond, char* argthird)
{
	if ((strcmp(argfirst, "-r") == 0) || (strcmp(argfirst, "-R") == 0))
	{
		asciiconv(argfirst);
	}
	else
	{
		return 1;
	}

	if ((strcmp(argsecond, "io") == 0) || (strcmp(argsecond, "IO") == 0) || (strcmp(argsecond, "adc") == 0) || (strcmp(argsecond, "ADC") == 0))
	{
		asciiconv(argsecond);
	}
	else
	{
		return 2;
	}

	asciiconv(argthird);
	if ((strcmp(argthird, "portb") == 0) || (strcmp(argthird, "pinc") == 0) || (strcmp(argthird, "5") == 0) || (strcmp(argthird, "portd") == 0))
	{
	}
	else return 3;


	return 0;
}




// all function definitions and prototypes to be defined above this line - NO exceptions !!!
int main(int argc, char *argv[])
{ 
	// ALL CODE (excluding variable declarations) MUST come after the following 'if' statement
	if (argc == 1)
	{
		// When run with just the program name (no parameters) your code  MUST print 
		// student ID string in CSV format. i.e.
		// "studentNumber,student_email,student_name"
		// eg: "2345678,s2345678@student.rmit.edu.au,FirstName_LastName"

		// Edit string below: eg: "studentNumber,student_email,student_name"
		cout << "3843524,s3843524@student.rmit.edu.au,Harjas_GILL" << endl;

		// The convention is to return Zero to signal NO ERRORS (please do not change it).
		return 0;
	}
	//--- START YOUR CODE HERE.
	
	else if (argc == 2 || argc == 3)
	{
		cout << "P" << endl;
		return 0;
	}

	if (argc == 4)
	{
		char* a1 = argv[1], * a2 = argv[2], * a3 = argv[3];


		if (funcreqbas(a1, a2, a3) == 1)
		{
			cout << "R" << endl;
			return 0;
		}
		else if (funcreqbas(a1, a2, a3) == 2)
		{
			cout << "C" << endl;
			return 0;
		}
		else if (funcreqbas(a1, a2, a3) == 3)
		{
			cout << "S" << endl;
			return 0;
		}



	}

	if (argc >= 4)
	{
		char* a1 = argv[1], * a2 = argv[2], * a3 = argv[3];
		char stream[maxByteSize] = {};
		int bincalc = 0;
		if (funcreqbas(a1, a2, a3) == 1)
		{
			cout << "R" << endl;
			return 0;
		}
		else if (funcreqbas(a1, a2, a3) == 2)
		{
			cout << "C" << endl;
			return 0;
		}
		else if (funcreqbas(a1, a2, a3) == 3)
		{
			cout << "S" << endl;
			return 0;
		}


		try
		{
			if (argv[4] != NULL)
			{
				if ((strcmp(a1, "-r") == 0) && (strcmp(a2, "io") == 0))
				{
					if ((strcmp(a3, "portb") == 0) || (strcmp(a3, "portd") == 0))
					{
						if (ascvalid(argv[4]) == false)
						{
							throw 50;
						}
						else if (ascvalid(argv[4]) == true)
						{
							if (strcmp(a3, "portb") == 0)
							{
								convertingtobinary(changearray, stream);
								if (FileWriter("portb.txt", stream) == 0)
								{
									cout << changearray << ", " << stream << endl;
									return 0;
								}
							}
							else if (strcmp(a3, "portd") == 0)
							{
								convertingtobinary(changearray, stream);
								stream[0] = 48;
								stream[5] = 48;
								if (FileWriter("portd.txt", stream) == 0)
								{
									convertingtobinary(changearray, stream);
									cout << changearray << ", " << stream << endl;
									return 0;
								}
							}
						}
					}
					else
					{
						throw 100;
					}
				}
				else if ((strcmp(a1, "-r") == 0) && (strcmp(a2, "adc") == 0))
				{
					throw 100;
				}
			}
			else if ((argv[4]) == NULL)
			{
				if ((strcmp(a1, "-r") == 0) && (strcmp(a2, "io") == 0))
				{
					if (strcmp(a3, "portb") == 0)
					{
						errno_t read_portb = FileReader("portb.txt", stream);
						if (checkbin(stream) == false)
						{
							throw 150;
						}
						if (read_portb == 0)
						{
							bincalc = stoi(stream, 0, 2);
							if (bincalc < 0 || bincalc > 255)
							{
								throw 150;
							}
							cout << bincalc << ", " << stream << endl;
							return 0;
						}
						else
						{
							throw 150;
						}
					}

					else if (strcmp(a3, "portd") == 0)
					{
						errno_t read_portd = FileReader("portd.txt", stream);
						if (checkbin(stream) == false)
						{
							throw 150;
						}
						if (stream[0] != '0' || stream[5] != '0')
						{
							throw 150;
						}

						if (read_portd == 0)
						{
							bincalc = stoi(stream, 0, 2);
							if (bincalc < 0 || bincalc > 255)
							{
								throw 150;
							}
							cout << bincalc << ", " << stream << endl;
							return 0;
						}
						else
						{
							throw 150;
						}
					}
					else if (strcmp(a3, "pinc") == 0)
					{
						errno_t read_pinc = FileReader("pinc.txt", stream);
						if (checkbin(stream) == false)
						{
							throw 150;
						}
						if (read_pinc == 0)
						{
							bincalc = stoi(stream, 0, 2);
							if (bincalc < 0 || bincalc > 255)
							{
								throw 150;
							}
							cout << bincalc << ", " << stream << endl;
							return 0;
						}
						else
						{
							throw 150;
						}
					}
				}
				else if ((strcmp(a1, "-r") == 0) && (strcmp(a2, "adc") == 0))
				{
					errno_t read_adc = FileReader("adc5.txt", stream);
					if (ascvalid(stream, 1) == false)
					{
						throw 150;
					}
					if (read_adc == 0)
					{
						float percen = (float)changearray / 1023;
						percen = percen * 100;
						cout << changearray << ", " << (int)percen << "%" << endl;
					}
					else
					{
						throw 150;
					}
				}
			}
		}
		catch (int errpres)
		{
			if (errpres == 50)
			{
				cout << "N" << endl;
				return 0;
			}
			else if (errpres == 100)
			{
				cout << "P" << endl;
				return 0;
			}
			else if (errpres == 150)
			{
				cout << "Z" << endl;
				return 0;
			}
		}

	}

	else if (argc > 5)
	{
		cout << "P" << endl;
		return 0;
	}

	
	// F2.1 check that we have the correct number of arguments: less than 3 command line arguments - output 'P'
	// F2.2 check that we have the correct number of arguments: more than 4 command line arguments - output 'P'

	// Suggested - Go through the input arguments an convert all characters to lower-case

	
	// F2.3 check that the first argument is "-r"
	
	
	// F2.4 check if second input argument is a valid register type (e.g. "io" or "adc")
	
	
	// F2.5 check if third input argument is a valid register (e.g. "portb", "portd", "pinc" or "5")
	
	
	// F2.6.1 and F2.6.2 check if the (optional) fourth argument is valid.
	

	// Suggested. Create a char array of size [maxByteSize + 1] to ensure that it will always be
	//            big enough to hold the 8 characters +  the null terminator character ('\0').
	//            Ensure that it is initialised to all zero (i.e. all '\0').
		
	// Suggested. Determine if the operation is to write or read to the OUSB Board

     	// If Writing 	
					
			//F2.6.3 and F2.6.4 if the (optional) fourth argument is valid.
			// F3. write value for PORTB (F3.1) or PORTD (F3.2)
		
		// If Reading
		
			// F3. read PORTB (F3.3), PORTD (F3.4), PINC (F3.5) or ADC_5 (F3.6)

	
	
	// The convention is to return Zero to signal NO ERRORS (please do not change it).
	// If you change it the AutoTester will assume you have made some major error. 
	return 0;
}  // No code to be placed below this line - all functions to be defined above main() function.
   // End of file. 

   
   
 

 