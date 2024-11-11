# 🔄 C Dynamic Data Structures

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C Standard](https://img.shields.io/badge/C-C99-blue.svg)](https://en.wikipedia.org/wiki/C99)

A simple C library implementing dynamic arrays and strings with basic operations.

## ✨ Features

### 📊 Dynamic Array

- Generic dynamic array implementation that can store any data type
- Automatic resizing when capacity is reached
- Basic operations: append, remove, get elements
- Memory management utilities

### 📝 Dynamic String

- String manipulation utilities
- Operations: create, copy, concatenate, substring
- String comparison and length functions
- Automatic memory management

## 📦 How to Use

1. Build the library:

```bash
make
```

2. Include the headers in your program:

```c
#include "dynamic_array.h"
#include "dynamic_string.h"
```

3. Compile your program with the library:

```bash
cc your_program.c -L. -ldynarray -I.
```

The `-L.` flag tells the compiler to look for libraries in the current directory
The `-ldynarray` links against the library
The `-I.` adds the current directory to include search path

## 🧪 Running Tests

The library comes with a test suite built using the Greatest testing framework.

```bash
make test
```

## 💡 Example Usage

```c
// Dynamic Array example

/*
    ** ⚠️ Be careful when using pointers to pointers
    ** The following code will NOT work because
    ** the array will store the address of the pointer
    ** instead of the value itself,
    ** which will cause memory issues:
    **
    ** t_array *arr = array_init(2, sizeof(char *));
    ** char *str = "Hello";
    ** arr->append(arr, &str);  // Wrong!
*/
t_array *arr = array_init(8, sizeof(int));  // Initialize array with capacity 8 for integers

arr->append(arr, &(int){42});  // Append int value to array
arr->append(arr, &(int){1});

int *retrieved = (int*)arr->get(arr, 0);  // Get first element
printf("Retrieved value: %d\n", *retrieved);

arr->destroy(arr);  // Clean up

// Dynamic String example
t_string *str = string_init("Hello");
t_string *str2 = string_init(" World");
t_string *combined = str->concat(str, str2);

printf("%s\n", combined->data); // Prints: Hello World

str->destroy(str);
str2->destroy(str2);
combined->destroy(combined);
```

## 🤝 Contributing

Feel free to open issues or submit pull requests to improve the library.

## 📜 License

This project is open source and available under the MIT License.
