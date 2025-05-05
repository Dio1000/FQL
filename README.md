## About the Project
FQL is a programming language used to manage data in a relation database management system. Written in C++, FQL allows the user to create and define Relations (aka Tables), add and remove data, as well as updating and querying it in a fast manner (dependent on the operation and queried data).

## Features 
- **Creating Schemas**: Allows the user to create and use schemas (aka databases).
- **Creating Relations**: Allows the user to create and use relations (aka tables), which can be queried.
- **CRUD operations**: Implementation of creating, reading, updating, deleting data in a schema.
- **Human-readable warnings and errors**: Users receive warnings and error messages for all operations that don't allow full compliation.
- **Fast PK-querying**: Implementation of B-tree data structure to allow for fast lookup of PKs (Primary keys) and row IDs.

## How to use
FQL lets users query and update data using simple functional and OOP principles. Here is the syntax alongside some code examplex.

### Creating Schemas
   
Creating and using a Schema (aka Database) in FQL requires the understanding of two keywords:
```
-- This is how you define a schema --
schema: schemaName

-- From now on, all declared relations will be stored in ’schemaName’ --
using: schemaName
```
### Creating Relations
   
Creating and defining Relations(aka Tables) in FQL requires the understanding of a few concepts:
```
relation: relationName -> {
    attributeName1, attributeDataType1, attributeConstraint1
    attributeName2, attributeDataType2, attributeConstraint2
    attributeName3, attributeDataType3, attributeConstraint3
    -- Insert as many as you would like--
}
```

attributeNames
- Must consist **only of alphanumerical characters**.

attributeDataTypes
- `int` — Numerical value in the interval (-2,147,483,648, 2,147,483,647)
- `boolean` — Value consisting of either `True` or `False`
- `date` — Value representing time in the format `dd/MM/YYYY`
- `datetime` — Value representing time in the format `dd/MM/YYYY ss/mm/hh`
- `UUID` — Random string of 16 digits
- `char(x)` — String with length exactly `x`
- `varchar(x)` — String with length ≤ `x`

attributeConstraint
- `PK` — Specifies the **Primary Key** of the relation (important for schema definition)
- `FK` — Specifies the **Foreign Key** of the relation
- `NULLABLE` — Specifies the attribute **can be NULL**
- `NOT NULL` — Specifies the attribute **cannot be NULL**

Example (Creation of a Relation and two Schemas):
```
-- Creating the School schema
schema: School

-- Stating that the following Relations will be stored in School
using: School

-- This is how you declare Relations --
-- All these Relations will be stored in School --
relation: Student
relation: Teacher

-- This is how you define a Relation --
Student -> {
    -- This is where you define the attributes of a Relation. --
    ID, UUID, PK
    Name, varchar(20), NOT NULL
    Surname, varchar(20), NOT NULL
    isRegistered, boolean, NULLABLE
    grade, int, NULLABLE
}

Teacher -> {
    ID, UUID, PK
    StudentID, UUID, FK
    Name, varchar(20), NULLABLE
    Surname, varchar(20), NULLABLE
}
```

### Linking

Users can "copy-paste" code from one file to the other using the `include` keyword. 

```
-- This is the code from files/schoolRelation --
schema: School
using: School

relation: Student
Student -> {
    ID, UUID, PK
    Name, varchar(20), NOT NULL
    Surname, varchar(20), NOT NULL
    isRegistered, boolean, NULLABLE
    grade, int, NULLABLE
}

-- This is the code from files/code --
include: files/schoolRelations

-- Do something with the Student relation --
```

### Inserting data (The add method)
   
Users can insert data into one of the declared relations.

```
Signature: Relation.add(value1, value2, value3, ...)
Returns: void

Description: Adds a set of values into a Relation. The set of values must have the same data types
as the attributes with the index they are passed on. This function is deprecated and will replaced
with a better add function in a future version which lets the user choose the values
represented by the attributes.
```

Here are some examples using the Student declaration from earlier.
```
Examples:
Student.add(2618792023759228, Darian, Sandru, True, 10)
Student.add(8717272261061594, James, Java, False, NULL)
Student.add(4763175962178574, John, C, NULL, NULL)
Student.add(8380409196254499, Peter, Python, True, 5)
```

### Inserting data (The addf method)

Users can insert the data from a CSV-formatted file into one of their declared relations.

```
Signature: Relation.addf(filePath)
Returns: void

Description: Adds values from a file into a Relation. The values from the file need to be separated
by commas (CSV format). This function will convert the data to add methods, so the data still needs
to maintain the order of the attribute declarations.
```
Here are some examples using the Student declaration from earlier.

```
Examples:
-- The files/data file constains the following lines: --
-/
2618792023759228, Darian, Sandru, True, 10
8717272261061594, James, Java, False, NULL
4763175962178574, John, C, NULL, NULL
8380409196254499, Peter, Python, True, 5
/-

Student.addf(files/data)
-- The lines will now be converted to --
-/
Student.add(2618792023759228, Darian, Sandru, True, 10)
Student.add(8717272261061594, James, Java, False, NULL)
Student.add(4763175962178574, John, C, NULL, NULL)
Student.add(8380409196254499, Peter, Python, True, 5)
/-
```

### Updating data

FQL also allows the users to update data. This is done by using the following method called from inside a Relation object.

```
Syntax: Relation.update(void) where {
    expression
} set {
    statement
}
Returns: void

Description: Updates all the values of a Relation for which the expression inside the
where clause returns true and sets their values according to the satatement inside the
set clause.
```

The expression inside the where clause must be written in strong syntax (this will be changed in a future update). This means that all operators are binary and there must be parentheses around all binary operators. Here are some examples:

```
-- Assume we are in a Student update where clause --

-- This is valid --
((Name == "Peter") and (Surname == "Python"))

-- This is not valid --
(Name == "Peter") and (Surname == "Python")

-/ Reason: there must be parenthesis around ALL operators, that inclused the binary and that takes
as the first argument the boolean result of (Name == "Peter") and the boolean result
of (Surname == "Python") /-

-- This is valid --
(((Name == "James") or (Name == "John")) or (Name == "Peter"))
```

The statement inside the set clause must also be written in strong sytnax. Here are some examples of statements, highlighting the difference between an expression and a statement.

```
(Name = "Darian")
-/ This is a statement, it is not true or false, it will just be executed as
an assignment. -/

((Name = "Darian") and (Surname = "Sandru"))
-/ This is also a statement, both the Name and the Surname attributes will be
replaced in the relation -/

(Name == "James")
-/ This is not a statement because it can be evaluated to true or false, this
is an expression -/

((Name = "Darian") or (Name = "Peter))
-/ This is not a statement, and acts more like a comma, but there can be no
randomness when deciding which values to change -/
```

Here is an example in practice. We will take a look at a query and the data before and after the query.

```
Student.update() where {
    ((Name == "Darian") and (isRegistered == True))
} set {
    (isRegistered = False)
}

-- This is before the query --
RID,ID,Name,Surname,isRegistered,Grade
0,2618792023759228,Darian,Sandru,True,10
1,8717272261061594,James,Java,False,NULL
2,4763175962178574,John,C,NULL,NULL
3,8380409196254499,Peter,Python,True,5

-- This is after the query --
RID,ID,Name,Surname,isRegistered,Grade
0,2618792023759228,Darian,Sandru,False,10 -- This line changed --
1,8717272261061594,James,Java,False,NULL
2,4763175962178574,John,C,NULL,NULL
3,8380409196254499,Peter,Python,True,5
```

### Deleting data

Everything that is available to the update() method is also available here. Notice the set clause is missing, because we already know what to do with the row once we find it: delete it. In the case of update(), the user also has to specify how the line should be modified.

```
Syntax: Relation.delete(void) where {
    expression
}
Returns: void

Description: Deletes all the rows from a Relation where the expression is
evaluated to true.
```

We will now take a look at a query and the data before and after the query.
```
Student.delete() where {
    ((isRegistered == False) and (Surname != "Java"))
}

-- This is before the query --
RID,ID,Name,Surname,isRegistered,Grade
0,2618792023759228,Darian,Sandru,True,10
1,8717272261061594,James,Java,False,8
2,4763175962178574,John,C,False,7
3,8380409196254499,Peter,Python,False,5

-- This is after the query --
RID,ID,Name,Surname,isRegistered,Grade
0,2618792023759228,Darian,Sandru,True,10
1,8717272261061594,James,Java,False,8
-- 2,4763175962178574,John,C,False,7 this was deleted --
-- 3,8380409196254499,Peter,Python,False,5 this was deleted --
```

### Array Declaration

The arrays will be declared using the ’let’ keyword. Let’s take a look at the syntax:
```
let: arrayName = -- What to store, we will see this later --
```
Empty array declaration is now allowed, although an array may be empty if the fetch() method does not return anything.

### The fetch method

This is the most important part of array declaration, as it tells the array what to store. We will now dive into the fetch() method:

```
Syntax: Relation.fetch(attributeName1, attributeName2, ... attributeNameN)
Returns: An array of arrays, each of the arrays containing the data stored in
the attribute.

Description: Fetches all the data from an 1 or more attributes and stores it
in different arrays.
```

Let’s take a look at how this works with an example:
```
let studentNames = Student.fetch(Name)
-/ Now studentNames will hold one array with the information:
[Darian, James, John, Peter] /-

let studentFullNames = Student.fetch(Name, Surname)
-/ Now studentFullNames will hold 2 arrayds with the information:
[Darian, James, John, Peter]
[Sandru, Java, C, Python] -/
```

The fetch() method also allows for use of the where clause, meaning data can be filtered. Please take a look at the following example:

```
let registeredStudents = Student.fetch(Name, Surname) where {
    (isRegistered == True)
}

-/ Now registeredStudents will hold the following arrays:
[Darian]
[Sandru]
Because Darian Sandru is the only registered student -/
```

### Array concatenation

Concatenation of constant string literals is also allowed using the following syntax with the overloaded operator ’+’ (meaning concatenation between string literals). Please take a look at the following example:

```
let studentFullNames = Student.fetch(Name) + " " + Student.fetch(Surname)
-- Everything after the array declaration will now be concatenated into one array --

-/
Now studentFullNames will hold:
[Darian Sandru, James Java, John C, Peter Python] -/

let unregisterdStudents = Student.fetch(Name, Surname) + " " + Student.fetch(isRegistered) where {
    (isRegistered == False)
}
-/ unregisteredStudents will now hold the following arrays:
[Darian True, James False, John False, Peter False]
[Sandru, Java, C, Python] -/
```

For anyone familiar with LEFT JOINS and RIGHT JOINS this may seem a bit weird. We have no way of specifying a default value in case we are querying more data from one literal. Here is an example of how a ’default’ keyword could work in a future update:

```
let unregisterdStudents = Student.fetch(Name, Surname) + " " + Student.fetch(isRegistered) where {
    (isRegistered == False)
} default {
    "None"
}
-/ unregisteredStudents will now hold the following arrays:
[Darian True, James False, John False, Peter False]
[Sandru None, Java None, C None, Python None]
As you can see, there is a default value for values that are not queried.-/
```

### Outputting Schemas / Relations

Users can output the data in a ASCII-formatted way using the keyword `show`. 

```
show: Student

-- Where the Student Relation contains the data: --
RID,ID,Name,Surname,isRegistered,Grade
0,2618792023759228,Darian,Sandru,True,10
1,8717272261061594,James,Java,False,8
2,4763175962178574,John,C,False,7
3,8380409196254499,Peter,Python,False,5
4,4319109456259177,Simon Quinton,Larry,True,2
5,2351789416435487,Ada,Ada,True,10

-- It will output --
+------------------------------------------------------------------------------------------------------------------------+
|                                                           Student                                                      |
+------------------------------------------------------------------------------------------------------------------------+
|RID          |ID                        |Name                   |Surname          |isRegistered          |Grade         |
+------------------------------------------------------------------------------------------------------------------------+
|0            |2618792023759228          |Darian                 |Sandru           |True                  |10            |
|1            |8717272261061594          |James                  |Java             |False                 |8             |
|2            |4763175962178574          |John                   |C                |False                 |7             |
|3            |8380409196254499          |Peter                  |Python           |False                 |5             |
|4            |4319109456259177          |Simon Quinton          |Larry            |True                  |2             |
|5            |2351789416435487          |Ada                    |Ada              |True                  |10            |
+------------------------------------------------------------------------------------------------------------------------+
```

## Prerequisites 

- C++17 compatible compiler (GCC 9+, Clang 10+, or MSVC 2019+)
- CMake 3.15+
- Boost Libraries 1.75+

## Usage

1. Clone the repository:
```bash
git clone https://github.com/Dio1000/FQL.git
cd FQL
```

2. Build the project:
```bash
mkdir build && cd build
cmake ..
make
```

3. You can run FQL in different modes using command-line arguments:

- `run <buildFile>`: Executes a built file given as the argument.
- `run <buildFile> <execFile>`: Builds the buildFile, saves the executable as execFile, then executes it.
- `build <codeFile> <buildFile>`: Builds the codeFile, saves the executable as buildFile, but does not execute it.

## Contact

Email: [sandru.darian@gmail.com](mailto:sandru.darian@gmail.com)  

FQL: [https://github.com/Dio1000/FQL](https://github.com/Dio1000/FQL)  

