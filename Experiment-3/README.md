# Output
![FIFO](https://github.com/DarkMortal/CN-UNIX/assets/67017303/b13d0646-4145-40fe-8a6b-0a05590b4933)

A FIFO special file (a named pipe with no extension) is similar to a pipe, except that it is accessed as part of the filesystem. It can be opened by multiple processes for reading or writing. When processes are exchanging data via the FIFO, the kernel passes all date internally without writing it to the filesystem. 

**Note:** Opening the read or write end of a FIFO blocks until the other end is also opened (by another process or thread). 
