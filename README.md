# ftrace
As you know, ftrace allows you to list all the various inputs and outputs of a program function.
We therefore list the following elements:
- system calls
- internal program function calls, with name and address,
- signals received from other programs,
- function calls contained in shared libraries (.so).

This information is displayed as follows:

![image](https://github.com/LindonAliu/ftrace/assets/91671191/213558d4-6141-4d49-b4a5-343d13581c26)

According to the available elements, the display can limit itself, for example, if the executable that you call
does not have a table of symbols.
However, you must follow the function calls and display a description.
For example: `func_0x8765FDE0@a.out`.
