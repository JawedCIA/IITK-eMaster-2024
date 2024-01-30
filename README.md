# Programming Assignment 1

## Directory Structure
PA1 code base contains 5 directory, Makefile and other supported files required to complete the PA1 and described as follows:

1. The **Task-1** directory contains the template code for the Task-1.

    1.1. Directory contains four C files, namely **task1_calc.c**, **task1_calculate.c**, **task1_client.c**, and **task1_server.c**.

    1.2. **task1_calc.c** contains the main code that you will use for establishing the communication channel between client and server.

    1.3. **task1_client.c** and **task1_server.c** contains the template function to implement the client and server functionality. These template function need to be invoked from the main function available in  **task1_calc.c** file.

    1.4. The **task1_calculate.c** file contains the template function for the calculate function to evaluate the mathematical expression and return the final result. This calculate function is being invoked by the server whenever required.

    1.5. Execute **test\_task1.sh** to run provided sample testcases for Task-1. Generate more testcases to thoroughly evaluate your implementation.


2. The **Task-2** directory contains the template code for the Task-2

    2.1. Directory contains two C files and two sample chat content files, namely **task2_driver.c**, **task2_user.c**, **chat-1.txt**, and **chat-2.txt**.

    2.2. The **task2_driver.c** and **task2_user.c** files contains the template code for the driver and user program that you need to implement.

    2.3. The **chat-1.txt**, and **chat-2.txt** are the sample **chat content** file that are decribed in the PA1. Use these files to test the functionality of your implementation.
    
    2.4. Execute **test\_task2.sh** to run provided sample testcases for Task-2. Generate more testcases to thoroughly evaluate your implementation.
    

3. The **Task-3** directory contains the template code for the Task-3

    3.1. Directory contains C file **myDU.c**.
    
    3.2. Execute **test\_task3.sh** to run provided sample testcases for Task-3. Generate more testcases to thoroughly evaluate your implementation.


4. The **inc** directory contains the standard functions and data structure that can be used in the task given for the PA1.

    4.1. This directory contains two files, namely **calc.h**.

    4.2. The **calc.h** file contains the function declaration and constants that are required for Task-1. For example, all the function required to implement client-server based calculator are declared in this file.


6. **Makefile** is used for the compilation of the PA1 code base.

7. The **README.md**, this file.


## To Build System
Use **make** command to compile the assignment. After successful compilation, all the binaries are generated in the root directory of the PA1 code base.

1. **Compile code for all the Task:** To compile for all the task, use the **make** command from the root directory of the PA1 code base.
    > **make**

2. **Compile Individual Task code:** Individual task code can be compiled using the **make** command followed by the Task number in lower case. For example, if you want to build the code base for Task-1, the syntax is as follows:
    > **make task1**

    Similarly, other tasks i.e., Task-2, and Task-3 code can be compiled individually.

3. **Clean the build:**
    > **make clean**

## Generated Binary Code
After the compilation of an individual task code or entire assignment code, binary files are placed in the root directory of the PA1 code base. These files are as follows:

1. **Task-1:** Its binary file is **task1_calc**.

2. **Task-2:** Its **driver** and **user** binary files are represented as **task2_driver** and **task2_user**, respectively.

3. **Task-3:** Its binary file is **myDU**.

