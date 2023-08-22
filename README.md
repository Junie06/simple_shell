---
# C - Simple Shell Project

This is a simple shell implementation in C, aiming to replicate the basic functionalities of the UNIX shell. The project focuses on fundamental concepts of operating systems, including process creation, command execution, and handling user input. The shell provides a command-line interface for users to interact with the system and execute commands.

## Features

- **Command Execution:** Execute both built-in shell commands and external executable files.
- **Built-in Commands:** Includes support for common built-in commands like `exit`, `cd`, `env`, and more.
- **Tokenization:** Tokenize user input to separate command and arguments.
- **Path Resolution:** Resolve the full path of executable files using the `PATH` environment variable.
- **Error Handling:** Provide appropriate error messages and handle various scenarios, like memory allocation failures or command not found.
- **Modular Design:** Implement the shell's functionalities as modular functions for better maintainability and readability.
## Getting Started

1. Clone the repository: `git clone https://github.com/Junie06/simple_shell.git
`
2. Navigate to the project directory: `cd simple_shell`
3. Compile the shell: `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell`
4. Run the shell: `./shell`

## Usage

1. Launch the shell by running `./shell`.
2. Enter commands just like you would in a regular terminal.
3. The shell supports basic built-in commands such as `exit`, `cd`, and `env`.
4. External executable commands can also be executed.
