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

The mathfs.c file contains the logic for the FUSE implementation. The file contains several strings as 
global variables to represent certain paths for valid directories and files and data for doc files. It 
will procedureally generate files and folders for math operations.  In order to prevent repeat operations,
there exist a global int flag to see if a path is valid, and a global C string pointer to keep hold of
the desired file string. It begins in mathfs_getattr() to see if the file/directory should exist. If it
should (e.g., add/1/ or fib/12), then it will create the file/directory. If it should not, then it will 
return -ENOENT. 

A path is deemed valid if it begins with "add", "sub", "mul", "div", "exp", "fib", or 
"factor". The beginning of the path may or may not be followed by one or two more numerical 
"directories", in which case it is valid. If there is a depth of 3 directories (e.g., add/1/2/3), the
path is invalid. The example "add" and "add/1" will specify a directory, while "add/1/2" will specify
file, which can hold the results of 1+2 as a double floating point number. Decimal numbers are valid
(e.g. add/1.2/3.3 is valid). If the file is a 1st level directory (e.g. "add", "sub", etc.), then it 
will list the paths ".", "..", and "doc". "doc" is a file present in each of the 1st level 
directories that explains what the directory does. If the path is a 2nd level directory (e.g.,"add/1"), 
then it will simply list "." and "..". 

When opening a file, like "add/doc", the file system will check to see if the path is valid, by looking 
at the valid path flag. If the path is good, the file system will continue, otherwise it will return 
-ENOENT. If the access permissions are bad, then -EACCES will be returned. 

Upon opening a file, the file system will write the results of the operations or the "doc" file strings
to the file. If the path of the file is invalid, -ENOENT will be returned instead.
