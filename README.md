


# Voting System in C lang

## Overview
The Voting System is a console-based application designed to facilitate student elections. It allows students to cast their votes for candidates and provides an administrator panel to manage elections, candidates, and results.

## Files
- **ELECTION.H**: This header file contains the necessary functions, structures, and global variables to manage the voting system.
- **mainfile.c**: The main program file where the user interacts with the voting system. It includes "election.h" to utilize the functions and features provided by the header file.

## Compilation and Execution
To compile and run the Voting System, follow these steps:

1. Open your terminal or command prompt.
2. Navigate to the directory containing the project files.
3. Compile the main program using a C compiler (e.g., gcc):
   ```
   gcc mainfile.c -o mainfile
   ```
4. Run the compiled program:
   ```
   ./mainfile
   ```

## Features

### Student Panel
1. Students can enter their User ID to cast their votes for candidates.
2. The list of candidates is displayed for students to choose from.
3. The system checks the validity of the User ID, whether it has already voted, and the selected candidate's number.
4. After casting a vote, a confirmation message is displayed.

### Admin Panel
1. Admin authentication is required to access the panel.
2. The admin can initiate a new election, providing details like the election year, branch code, total voters, and number of candidates.
3. Candidate files are created, each containing the candidate's initial vote count and name.
4. The admin can continue a previous election, loading details from saved files.
5. The admin can delete illegal votes by entering the User ID associated with the vote.
6. The admin can ban specific User IDs by marking their votes as '$'.
7. The admin can view election results, including the winner and each candidate's votes.
8. The system calculates and displays the voting percentage.
9. The admin can logout from the panel.

## Notes
- The program uses various functions to handle authentication, election management, and user interactions.
- The "ElectionInfo.txt" file stores election details.
- Candidate information and student votes are saved in separate files.
- Banned User IDs are stored in "Banned.txt".

## Usage
1. Run the program using the compilation and execution steps mentioned above.
2. Choose the "Student panel" or "Admin panel" by entering the respective option number.
3. Follow the on-screen instructions to cast votes (Student panel) or manage the election (Admin panel).

## Contributors
- Shafaq Ayyub

