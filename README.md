# Programming Assignment 8 - Dictionary ADT

The file **Dictionary.cpp** has implementation of the **Dictionary** Data Structure with help of **Red Black Tree (RBT)**.

## Files In The Repository

1. Dictionary.cpp
2. Dictionary.h
3. DictionaryTest.cpp
4. Order.cpp
5. WordFrequency.cpp
6. README.md
7. Makefile

# Make commands
```
$ make clean
```
This command will make the repository clean by deleting the object file and executable file of **DictionaryTest.cpp**, **Order.cpp**, **Dictionary.cpp** and , **WordFrequency.cpp**.


```
$ make
```

This command will just compile other C files and make the executable and object file for **DictionaryTest.cpp**, **Order.cpp** and **WordFrequency.cpp**.

# Running the program

```
$ make
```

1. This command will just compile and make the executable and object file for **DictionaryTest.cpp**, **Order.cpp** and **WordFrequency.cpp**.

```
$ ./DictionaryTest
```

2. This command will run the DictionaryTest file and show the output of Dictionary ADT functions.

```
$ ./Order <infile> <outfile>
```

3. This command will run Order.cpp and it takes **2** arguments i.e. input file and an output file.

```
$ ./WordFrequency <infile> <outfile>
```

4. This command will run WordFrequency.cpp and it takes **2** arguments i.e. input file and an output file.


# Memory Leak Check

1. Run the make command

```
$ make
```

2. Run the following command to check the memory leaks in DictionaryTest file.

```
$ make checkTest
```

3. Run the following command to check the memory leaks in Order File.

```
$ make checkOrder
```

4. Run the following command to check the memory leaks in WordFrequency File.

```
$ make checkWord
```


# Other Commands

1. To clean the **.txt** files.

```
$ make cleanText
```

2. To clean the **backup** directory.

```
$ make cleandir
```
