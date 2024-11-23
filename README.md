# Notes CLI Program

**Notes** is a simple, lightweight command-line program for managing notes directly from the terminal. It allows you to create, organize, and manage your notes by grouping them into categories, and all data is stored in files for persistent storage.

## Features
- Create groups for organizing your notes.
- Add notes inside specific groups.
- Select groups and notes for quick access.
- List all notes within a group.
- Delete specific notes or entire groups.
- Print the content of a selected note.

## Usage

### General Command Syntax
```bash
./notes [--help] [--version] [--new-note VAR] [--new-group VAR] [--select-group VAR] [--select-note VAR] [--select] [--list] [--delete-group VAR] [--delete-note VAR] [--print] [notes]...
```

### Options and Commands

| Option/Command         | Description                                                                 |
|-------------------------|-----------------------------------------------------------------------------|
| `-h, --help`           | Shows the help message and exits.                                          |
| `-v, --version`        | Prints version information and exits.                                      |
| `-nn, --new-note VAR`  | Creates a new note with the specified name.                                |
| `-ng, --new-group VAR` | Creates a new group with the specified name.                               |
| `-sg, --select-group VAR` | Selects the specified group for operations.                              |
| `-sn, --select-note VAR`  | Selects the specified note from the selected group.                      |
| `-s, --select`         | Automatically selects the group or note immediately after creation.        |
| `-l, --list`           | Lists all notes inside the selected group.                                 |
| `-dg, --delete-group VAR` | Deletes the specified group.                                              |
| `-dn, --delete-note VAR`  | Deletes the specified note from the selected group.                      |
| `-p, --print`          | Prints the content of the selected note.                                   |

## Example Workflow

1. **Create a Group**:
   ```bash
   ./notes --new-group "Work"
   ```
2. **Select the Group**:
   ```bash
   ./notes --select-group "Work"
   ```
3. **Add a Note to the Group**:
   ```bash
   ./notes --new-note "MeetingNotes"
   ```
4. **Select the Note**:
   ```bash
   ./notes --select-note "MeetingNotes"
   ```
5. **List Notes in the Group**:
   ```bash
   ./notes --list
   ```
6. **Print a Note's Content**:
   ```bash
   ./notes --print
   ```
7. **Delete a Note**:
   ```bash
   ./notes --delete-note "MeetingNotes"
   ```
8. **Delete a Group**:
   ```bash
   ./notes --delete-group "Work"
   ```

## Build Instructions

To build the program from source, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/<your-username>/notes-cli.git
   cd notes-cli
   ```

2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Configure the build:
   ```bash
   cmake ..
   ```

4. Compile the program:
   ```bash
   make
   ```

5. Run the program:
   ```bash
   ./notes --help
   ```

## Contribution
Contributions are welcome! Feel free to submit issues or pull requests for bug fixes, feature additions, or documentation updates.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.
