# Assignment7
CS416 - Assignment 7 - math filesystem
GROUP MEMBERS: Imran Farooqui & Michael Sabbagh

Our implementation of the system utilizes a functions file. functions.c contains all the logic 
for the math functions. It does not malloc for better memory usage. Instead, it keeps track of 
two arrays of chars that are returned for a given math function. At the beginning of each function
the arrays are reset so as to make sure there is no garbage data in them. This prevents the problem
of mallocing data which we can then not free.

There are specific error messages if the user tries to perform an impossible function. For example, 
factor outputs an error if it is fed a decimal number, there is an error if the user tries to divide 
by 0, if there is overflow to an integer (number too big) user gets an error, etc.
