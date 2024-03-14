# Pipex

## Description
Pipex is a project designed to familiarize users with the concept of process creation and pipeline manipulation in Unix-like operating systems. The goal is to recreate the functionality of the shell command `'< file1 cmd1 | cmd2 > file2'` using basic system calls.

## How it Works
Pipex takes two commands as arguments along with input and output file descriptors. It then executes these commands in separate child processes, setting up a pipeline between them. The output of the first command is redirected to the input of the second command using the `pipe()` system call. Input and output files are also managed accordingly.

## Commands
To use Pipex, follow these steps:

1. **Compile the Program**: Compile the Pipex program using the provided Makefile or your preferred compiler.

2. **Execute Pipex Command**: ./pipex file1 cmd1 cmd2 file2

- `file1`: Input file to be used as input for the first command.
- `cmd1`: First command to be executed.
- `cmd2`: Second command to be executed.
- `file2`: Output file to store the result of the second command.

**Example**: /pipex infile "ls -l" "grep pipex" outfile

3. **View Output**: Once executed, the output of `cmd2` will be stored in `file2`.

## Notes
- Ensure that the commands passed to Pipex are properly formatted and executable.
- Input and output files should exist and have appropriate permissions.
- Any errors during execution will be displayed on the standard error output.
- For to use the pipex bonus, to do ```make pipex_bonus``` and run with ```./pipex```, the bonus can take multiple orders.

## Contributing
Contributions are welcome! Feel free to fork the repository, make your changes, and submit a pull request.
