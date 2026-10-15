# Campus Emergency Alert System (CLI) 🚨

A lightweight, terminal-based application written in C designed to log, manage, and track campus emergency alerts. 

## Features
- **Log Emergencies:** Users can quickly input their name, the type of emergency (Medical, Security, etc.), and their campus location.
- **View Active Alerts:** Displays a formatted table of all currently logged alerts and their resolution status.
- **Persistent Storage:** Utilizes C File I/O to automatically save all logged alerts to a local text file (`alerts_database.txt`), ensuring data is not lost between sessions.

## Technical Skills Demonstrated
- C Programming (Standard Libraries: `stdio.h`, `stdlib.h`, `string.h`)
- Use of `struct` for complex data management
- Pass-by-reference using pointers
- Persistent data storage using File Handling (`fopen`, `fprintf`, `fscanf`)

## How to Run
1. Compile the code using GCC:
   ```bash
   gcc main.c -o alert_system
