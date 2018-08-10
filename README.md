# Turing-Machine-Simulator that performs arithmetic operations and string operations.
The input file goes something like this:

Q:q1,q2,q3,q4
A:0,1
Z:0,1,x
T:q1,0,q2,x,R
T:q1,1,q2,x,R
T:q2,0,q2,0,R
...
S:q1
F:q3,q4

Where Q is states, A is input values, Z is tape alphabet, S is start state, F is accept and reject states.

It needs to handle an input where it takes in the number of inputs, the input strings and accept or reject.

For example, if the input is:
3
0,#,1,1
1,1
0,1,0

the output would print out the steps and whether it accepts or rejects.
