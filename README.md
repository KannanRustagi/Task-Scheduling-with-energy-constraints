# P4- Task Scheduling in Edge Server Systems with limited Solar Energy and Infinite Batteries
Achintya Gupta- 210101005 <br>
Kannan Rustagi- 210101054 <br>
Kshitij Maurya- 210101059<br>

## How to run the program?

1. To generate test cases, compile and run the generate_test_case.cpp file-
    g++ generate_test_case.cpp -o testcase
    ./a.out testcase

The program after running would prompt you to "Enter no. of machines:"(N), "Enter no. of time slots:"(T) and "Enter bound on energy generated in a slot:"(S). After all the values have been entered, the input file(test_case.txt) would be generated, which would contain the N, T values in the first 2 lines to be read by the code file containing the algorithm along with the task array(D) and power generated array(S) for each machine and time slot.

2. To get the final output, compile and run the algo.cpp file-
    g++ algo.cpp -o algo
    ./a.out algo

The program reads input from test_case.txt file generated after the first step mentioned above. After running the program, output.txt file will be generated which contains the following information about the tasks scheduled-
Tasks scheduled at ith time slot, Tasks scheduled at ith machine, Total tasks receieved, Total tasks completed.
