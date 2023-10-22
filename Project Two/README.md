# Course Planning and Advising Assistance Program in C++

## Project Overview

This C++ program, named "Project-Two.cpp," is a Course Planning and Advising Assistance program developed by Oved AYDIN in 2023. This program is designed to plan academic schedules by managing and accessing course information efficiently.

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Getting Started](#getting-started)
3. [Usage](#usage)
4. [Functionality](#functionality)
5. [Data Structure](#data-structure)

## Prerequisites

To use this program, you need to have the following:

- C++ development environment (e.g., Visual Studio).
- A compatible operating system (Windows, macOS, or Linux).
- The `courses.dat` file (included in the repository) containing course information.

## Getting Started

1. Clone or download the repository to your local machine.
2. Open the project in your C++ development environment (e.g., Visual Studio).
3. Ensure you have the `courses.dat` file in the same directory as the project.
4. Compile and run the program.

## Usage

Upon running the program, you will be presented with a menu with the following options:

1. **Load Data Structure:** Load course data from the `courses.dat` file or specify another data source.
2. **Print Course List:** Display a list of courses in alphabetical order, considering prerequisites.
3. **Print Course:** Retrieve information about a specific course by entering its course number.
9. **Exit:** Quit the program.

## Functionality

- **Load Data Structure:** You can load course data from the default source (courses.dat) or specify a different source file.
- **Print Course List:** The program displays a list of courses sorted alphabetically, taking course prerequisites into account.
- **Print Course:** You can retrieve information about a specific course by entering its course number.

### Customizing the Hash Table Size (Optional)

You can customize the size of the hash table used by the program by providing a command-line argument when running the program. If you do not specify a size, the program will use the default size.

To specify a custom table size, run the program as follows:

```sh
./Project-Two <table_size>
```

or

1. Open your C++ project in Visual Studio.

2. In the Solution Explorer, find your project's name and right-click on it.

3. Select "Properties" from the context menu.

4. In the project's properties, go to the "Configuration Properties" section and select "Debugging."

5. In the "Command Arguments" field, you can specify the table size as a command-line argument. For example, if you want to set the table size to 200, enter the following:

```sh
200
```

6. Click "Apply" or "OK" to save your changes.

## Data Structure

The program uses a custom hash table to efficiently store and manage course information. The `HashTable` class includes methods for inserting, removing, searching for, and retrieving a list of courses.
