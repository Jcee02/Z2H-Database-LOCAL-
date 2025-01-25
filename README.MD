# Employee Database Manager

## Project Overview
A command-line employee database management system implemented in C using POSIX file descriptors. This tool allows you to maintain a database of employee records with basic operations like listing and adding employees.

## Features
- List all employees in a database file
- Add new employees with their details
- Persistent storage using binary database files
- Command-line interface for easy integration

## Building
To build the project, simply run:
```
make
```
This will:
1. Clean any previous build files
2. Compile all source files
3. Generate the executable in the `bin` directory

## Usage
The program supports the following command-line arguments:
- `-f <filename>` : Specify the database file to use
- `-n` : List all employees in the database
- `-a <record>` : Add a new employee record

## Data Format
Employee records are stored in the following format:
```
name,address,id
```
Where:
- name: Employee's full name
- address: Employee's complete address
- id: Unique employee identifier

## Examples
1. List all employees in a database:
```
./bin/dbview -f mydba.db -n
```

2. Add a new employee:
```
./bin/dbview -f mydba.db -a "Juan T.,Calzada Norte 198,420"
```
