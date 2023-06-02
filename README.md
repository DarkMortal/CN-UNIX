# Difference between return Statement and exit() Function

| return Statement  | exit() Function |
| ------------- | ------------- |
| The return statement is a keyword | exit() function is part of the Standard Library <stdlib.h>  |
| It is used to return the program control to the calling function | It is used to terminate the current process |
| When the return is used in main(), all the objects are destroyed whether they are local or static | When the exit() is used, only the destructor of static objects is called |
