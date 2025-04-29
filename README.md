# Lab Test 2: Ariel Oudmayer - 2695316
# Description for Lab Test

This code takes as input a data file with the weight and height of individuals and computes the body mass index (BMI). The BMI of a person is the weight of a person in kilograms divided by the square of the height in metres. The program should then categorise the BMI according to these rules
* Less than 19: A
* Not less than 19 but less than 25: B
* Not less than 25 but less than 30: C 
* 30 or over: D

The complexity is that the country in which the study is being done, the weight of people is given in "stones", "pounds" and "ounces", and height in "feet" and "inches". So the program does the necessary conversion.

Input is a file that contains the identifiers and measurements of individuals (weight and height). A two line example is shown below: the first person (A7B3) weighs 6 stone, 13 pounds and 12 ounces and is 5 foot 9 inches tall; the second person (CC2E) weighs 7 stone 10 pounds and 3 ounces and is 5 foot 11 inches tall.

```
A7B3 6 13 12 5 9
CC2E 7 10 3 5 11
```

Assume the following conversion:
* 14 pounds in a stone
* 16 ounces in a pound
* 2.2 pounds in a kilogram
* 12 inches in a foot
* 3.28 feet in a metre

# How to build and test

```
make
make test
```

# How the program should be run

The program is run from the command line. It should take two command-line arguments: the name of an input file and the name of an output file. For example

```
./bmi study.dat cats.txt
```

This opens the file `study.dat` categorises each person and puts the result in the file `cats.txt`. For example, if the two line example above is the content of `study.dat`, then `cats.txt` should contain

```
A7B3 B
CC2E B
```
