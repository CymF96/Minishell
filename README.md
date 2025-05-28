# Minishell - Custom Unix Shell Implementation

> A Unix shell implementation built from scratch in C, replicating core Bash functionality including command parsing, execution, piping, redirections, and built-in commands with proper signal handling.

## ✨ Features

- **Interactive Prompt** - Clean command-line interface with custom prompt
- **Command Parsing** - Robust tokenization and syntax analysis
- **Built-in Commands** - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Path Resolution** - Automatic command searching in PATH directories
- **Piping System** - Multi-command pipeline execution (`cmd1 | cmd2 | cmd3`)
- **Redirections** - Input (`<`), output (`>`), and append (`>>`) redirections
- **Quote Handling** - Single and double quote parsing with proper escaping
- **Environment Variables** - Variable expansion and manipulation (`$VAR`, `$?`)
- **Command History** - Navigate through previous commands with arrow keys
- **Signal Handling** - Proper Ctrl+C, Ctrl+D, and Ctrl+\ behavior
- **Exit Status** - Accurate exit code tracking and `$?` variable

## 🛠️ Tech Stack

**Core Technologies:**
- **C Language** - System-level programming with manual memory management
- **GNU Readline** - Command-line editing and history functionality
- **Unix System Calls** - `fork()`, `execve()`, `pipe()`, `dup2()`, `waitpid()`
- **Makefile** - Automated compilation and dependency management

**Key Concepts Implemented:**
- Lexical analysis and parsing
- Inter-process communication (pipes)
- File descriptor manipulation
- Signal handling and process control
- Memory management and leak prevention

## 🚀 Quick Start

### Prerequisites
- GCC compiler (with C99 support)
- Make utility
- GNU Readline library
- Unix-like operating system (Linux, macOS)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/minishell.git minishell
   cd minishell
   ```

2. **Compile the project**
   ```bash
   make
   ```

3. **Run minishell**
   ```bash
   ./minishell
   ```

4. **Start using your shell!**
   ```bash
   minishell>> echo "Hello, World!"
   Hello, World!
   minishell>> ls -la | grep minishell
   minishell>> export MY_VAR="test"
   minishell>> echo $MY_VAR
   test
   minishell>> exit
   Goodbye!
   ```

## 🔧 Core Features

### Command Parsing
The shell implements a multi-stage parsing process:

1. **Lexical Analysis** - Breaks input into tokens
2. **Quote Processing** - Handles single/double quotes and escaping
3. **Variable Expansion** - Expands `$VAR` and special parameters
4. **Syntax Analysis** - Builds command structures with pipes and redirections prioritization

### Built-in Commands

| Command | Description | Usage Examples |
|---------|-------------|----------------|
| `echo` | Print text with `-n` option support | `echo "Hello"`, `echo -n "No newline"` |
| `cd` | Change directory with relative/absolute paths | `cd /home`, `cd ..`, `cd` (home) |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variables | `export VAR=value`, `export` (list all) |
| `unset` | Remove environment variables | `unset VAR` |
| `env` | Display environment variables | `env` |
| `exit` | Exit shell with optional code | `exit`, `exit 42` |

### Advanced Features

**Pipeline Execution:**
```bash
minishell>> ls -la | grep ".c" | wc -l
15
```

**I/O Redirections:**
```bash
minishell>> echo "Hello" > output.txt
minishell>> cat < input.txt >> output.txt
```

**Variable Expansion:**
```bash
minishell>> export NAME="World"
minishell>> echo "Hello $NAME!"
Hello World!
minishell>> echo "Exit code: $?"
Exit code: 0
```

## 🧮 Technical Implementation

### Memory Management
- **Leak-Free Design** - All allocated memory is properly initialize
- **Error Handling** - Graceful handling of allocation failures including when signal is catched
- **Cleanup on Exit** - Proper resource deallocation on shell termination

### Signal Handling
- **SIGINT (Ctrl+C)** - Interrupts current command, returns to prompt
- **SIGQUIT (Ctrl+\)** - Ignored in interactive mode
- **EOF (Ctrl+D)** - Exits shell gracefully

## 🧪 Testing

```bash
# Test specific features
./minishell
minishell>> ps aux | grep -v "grep" | awk '{print $2, $11}' | head -4
PID COMMAND
1 /sbin/init
2 [kthreadd]
3 [pool_workqueue_release]

# Test built-ins
minishell>> cd /tmp
minishell>> pwd
/tmp

# Test redirections
minishell>> cat << EOF > config.txt
>server_name=localhost
>port=8080
>debug=true
EOF
minishell>> cat config.txt 
server_name=localhost
port=8080
debug=true

# Test variable expansion
minishell>> export TEST="hello"
minishell>> echo "$TEST world"
hello world

#Test of variable expansion & built-in command
minishell>> export VAR="ho 123"
minishell>> ec$VAR
123
```

### Test Cases Coverage
- ✅ Basic command execution
- ✅ Pipeline chains (4+ commands)
- ✅ Multiple Input/Output redirections
- ✅ Quote handling (single/double)
- ✅ Variable expansion
- ✅ Built-in commands
- ✅ Error handling
- ✅ Signal behavior
- ✅ Memory leak detection

## 🔧 Building and Compilation

```bash
# Standard build
make

# Clean object files
make clean

# Complete clean (including executable)
make fclean

# Rebuild everything
make re
```

## 🔧 Troubleshooting

**Memory leaks:**
```bash
# Create a rl.supp file to hide the GNU memory leak -- those leak are related to the internal system and independent from the minishell program -- 
echo -e "{\n   leak readline\n   Memcheck:Leak\n   ...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n   ...\n   fun:add_history\n}" > rl.supp

# Run with Valgrind for checking memory leaks
valgrind --suppressions=./OTHER/debugging/rl.supp --leak-check=full --show-leak-kinds=all --verbose --log-file=valgrind-out.txt ./minishell

# Run with Valgrind for file descriptor errors
valgrind --suppressions=./OTHER/debugging/rl.supp --track-origins=yes --track-fds=yes --verbose --log-file=valgrind-out.txt ./minishell
```
## 📚 Learning Resources

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Programming in Unix Environment](https://www.apue.com/)
- [Unix System Calls Tutorial](https://www.tutorialspoint.com/unix_system_calls/)

## 📝 License

This project is part of the 42 School curriculum and follows their academic guidelines.

## 👨‍💻 Authors

**Coline Fischer** & **Muktim Coskuner**
- GitHub: [@CymF96](https://github.com/CymF96)
- GitHub: [@Muktim](https://github.com/Muktim)

## 🏆 42 School Project

This project demonstrates mastery of:
- **System Programming** - Low-level Unix system calls and process management
- **C Programming** - Advanced C concepts including pointers, memory management, and data structures
- **Shell Internals** - Understanding how shells work under the hood
- **Software Architecture** - Designing modular, maintainable code structures
- **Error Handling** - Robust error management and edge case handling

**Skills Developed:**
- Process creation and management (`fork`, `execve`, `waitpid`)
- Inter-process communication (pipes)
- File descriptor manipulation
- Signal handling and process control
- Lexical analysis and parsing
- Memory management and leak prevention
- Unix system programming

**Complexity Highlights:**
- Multi-process pipeline execution
- Complex parsing with quote handling
- Environment variable management
- Signal handling in multi-process context
- Memory-efficient string manipulation

**Grade:** 101/100
