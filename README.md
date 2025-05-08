# Warehouse Control Tool

This tool was created to manage the quantity and batch of items in a company's inventory. This project was developed for the **Data Structures** course. The main goal is to compare the performance between a **Binary Search Tree** and an **Ordered List** in terms of insertion, deletion, consumption, and search of each item by its part number.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Libraries Used](#libraries-used)
- [Compilation & Execution Guide](#project-compilation-guide)

---

## Overview

**CompressFast - FIFO Inventory Management System in C**

This project is a C language application designed for inventory management based on the **FIFO (First In, First Out)** policy. The system was developed to compare the performance and effectiveness of two distinct data structures in the context of item search and organization:

- **Doubly linked list of ordered queues**
- **Binary search tree with queues in each node**

Each item in the inventory is an object with the following attributes:

- `Part Number` (numeric)
- `Description`
- `Batch entry date`
- `Stock location` (format: StreetA-AddressB-LevelC)
- `Shelf Life`
- `Flag` (Released or Retained, based on expiration)

The system allows for **inserting**, **using**, **discarding**, and **searching** items in an organized way, simulating a real batch control environment.

---

## Features

- **Item Insertion**: Adds batches to an existing queue based on the part number. If the part number does not exist, it creates a new queue in the list or tree in order.
- **Optimized Search**: Efficient batch search by part number using an ordered list or binary search tree.
- **FIFO Consumption**: Items are always consumed in the order they were received (FIFO), respecting validity and availability.
- **Item Discarding**: Expired or retained items can be discarded manually or automatically.
- **Location Management**: Checks if a specific location (Street A-D, Address A-T, Level 1-5) is available or already occupied.
- **Structure Comparison**: Implements and compares the performance of both data structures in the context of search and manipulation.

---

## Libraries Used

- `stdio.h` – For standard input and output.
- `stdlib.h` – For dynamic memory allocation.
- `string.h` – For string manipulation (descriptions and location).
- `time.h` – For date control and item expiration.

---

## Project Compilation Guide

### Requirements

- GCC compiler
- C99 standard support

### Compilation

To compile the project, use the following command:

```bash
gcc -std=c99 -Wall -Wextra *.c -o main
```

### Execution

To run the project just use:

```bash
./main
```
