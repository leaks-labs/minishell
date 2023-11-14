# Minishell docs

---

- ***[Descriptions](#descriptions)***

- ***[Authorised functions](#authorised-functions)***

- ***[Commit flags](#commit-flags)***

---

## Descriptions

### 42 School Minishell Project

The 42 school minishell project is an educational initiative aimed at teaching students the foundations of Unix-like shell programming and system calls. As a key component of the 42 curriculum, this project challenges students to develop a simplified shell that replicates the functionalities of a standard command-line interface. By undertaking this project, students gain practical experience in system programming, process management, and interaction with the operating system.

### Project Overview

The minishell project serves as an opportunity for students to deepen their understanding of essential concepts related to shell development and system-level programming. With a strong emphasis on hands-on learning, this project enables students to apply their C programming skills and knowledge of system calls in a real-world context. Through the project, students learn to create a functional and user-friendly shell while adhering to Unix conventions and best practices.

### Key Learning Objectives

Throughout the minishell project, students engage with a variety of concepts and tasks, including:

- **Command Execution**: Implementing the core logic for parsing and executing user-entered commands, mirroring the behavior of a standard shell.
- **Built-in Commands**: Developing built-in commands like `cd`, `echo`, and `exit`, which are directly executed by the shell.
- **Environment Variables**: Managing environment variables by setting, displaying, and modifying them within the shell.
- **Path Resolution**: Implementing a mechanism to locate executable files in directories listed in the `PATH` environment variable.
- **Redirection and Pipes**: Handling input/output redirection and pipe operations to facilitate command chaining.
- **Signal Handling**: Capturing and responding to signals such as `Ctrl+C` and `Ctrl+Z` to enhance user experience.
- **Error Handling**: Implementing robust error handling to provide informative feedback to users in various scenarios.
- **Memory Management**: Managing memory efficiently to prevent memory leaks and ensure proper allocation and deallocation.
- **Process Management**: Understanding the fundamentals of processes, process IDs, and parent-child relationships.

### Educational Significance

The minishell project is a pivotal learning experience for students at 42 school. By engaging with the intricacies of shell programming, students acquire a profound understanding of the interactions between users, shells, and the operating system. The project empowers students to develop their problem-solving skills, promote code reusability, and adhere to coding standards within a real-world coding scenario. Through this project, students not only refine their programming skills but also acquire a deeper appreciation for the underlying mechanisms of Unix-based operating systems.

---

## Authorised functions

### `readline`

```c
char *readline(const char *prompt);
```

- **Parameters**: `prompt` is an optional string to be displayed as a prompt for input.
- **Return Value**: Returns a pointer to the input line read, or `NULL` if an error occurs or if the input stream is closed.

### `rl_clear_history`

```c
void rl_clear_history(void);
```

- **Parameters**: None.
- **Return Value**: None.

### `rl_on_new_line`

```c
void rl_on_new_line(void);
```

- **Parameters**: None.
- **Return Value**: None.

### `rl_replace_line`

```c
void rl_replace_line(const char *text, int clear_undo);
```

- **Parameters**: `text` is the new input line as a string, `clear_undo` is a flag to clear the undo history.
- **Return Value**: None.

### `rl_redisplay`

```c
void rl_redisplay(void);
```

- **Parameters**: None.
- **Return Value**: None.

### `add_history`

```c
void add_history(const char *line);
```

- **Parameters**: `line` is the line to be added to the history.
- **Return Value**: None.

### `printf`

```c
int printf(const char *format, ...);
```

- **Parameters**: `format` is the format string, followed by optional arguments.
- **Return Value**: Number of characters printed.

### `malloc`

```c
void *malloc(size_t size);
```

- **Parameters**: `size` is the number of bytes to allocate.
- **Return Value**: Pointer to the allocated memory or `NULL` if allocation fails.

### `free`

```c
void free(void *ptr);
```

- **Parameters**: `ptr` is the pointer to the memory to be freed.
- **Return Value**: None.

### `write`

```c
ssize_t write(int fd, const void *buf, size_t count);
```

- **Parameters**: `fd` is the file descriptor, `buf` is the data buffer, `count` is the number of bytes to write.
- **Return Value**: Number of bytes written or -1 on error.

### `access`

```c
int access(const char *pathname, int mode);
```

- **Parameters**: `pathname` is the file path, `mode` is the access mode for checks (e.g., `R_OK`, `W_OK`, `X_OK`, `F_OK`).
- **Return Value**: Returns 0 if access is successful, -1 on error.

### `open`

```c
int open(const char *pathname, int flags, mode_t mode);
```

- **Parameters**: `pathname` is the file path, `flags` are the flags for opening (e.g., `O_RDONLY`, `O_WRONLY`, `O_CREAT`), `mode` is the permission mode for new files.
- **Return Value**: File descriptor on success, -1 on error.

### `read`

```c
ssize_t read(int fd, void *buf, size_t count);
```

- **Parameters**: `fd` is the file descriptor, `buf` is the data buffer, `count` is the number of bytes to read.
- **Return Value**: Number of bytes read, 0 at end of file, -1 on error.

### `close`

```c
int close(int fd);
```

- **Parameters**: `fd` is the file descriptor to close.
- **Return Value**: 0 on success, -1 on error.

### `fork`

```c
pid_t fork(void);
```

- **Parameters**: None.
- **Return Value**: Returns 0 to the child process and the child's process ID to the parent process, or -1 on error.

### `wait`

```c
pid_t wait(int *status);
```

- **Parameters**: Pointer to an integer for storing child process status.
- **Return Value**: Process ID of the terminated child on success, -1 on error.

### `waitpid`, `wait3`, `wait4`

```c
pid_t waitpid(pid_t pid, int *status, int options);
pid_t wait3(int *status, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```

- **Parameters**: `pid` is the process ID of the child to wait for, `status` is a pointer to an integer for storing child process status, `options` are wait options, and `rusage` is a pointer to a `struct rusage` for resource usage information.
- **Return Value**: Process ID of the terminated child on success, 0 if used with `WNOHANG` and no child has exited, -1 on error.

### `signal`

```c
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```

- A type definition for a signal handler function.

### `sigaction`

```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```

- **Parameters**: `signum` is the signal number, `act` is a pointer to a `struct sigaction` specifying the new action, `oldact` is a pointer to a `struct sigaction` for storing the previous action.
- **Return Value**: 0 on success, -1 on error.

### `sigemptyset`, `sigaddset`

```c
int sigemptyset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
```

- **Parameters**: Pointer to a signal set (`sigset_t`).
- **Return Value**: 0 on success, -1 on error.

### `kill`

```c
int kill(pid_t pid, int sig);
```

- **Parameters**: `pid` is the process ID or process group ID, `sig` is the signal number.
- **Return Value**: 0 on success, -1 on error.

### `exit`

```c
void exit(int status);
```

- **Parameters**: Exit status.
- **Return Value**: None.

### `getcwd`

```c
char *getcwd(char *buf, size_t size);
```

- **Parameters**: `buf` is the buffer to store the current working directory, `size` is the size of the buffer.
- **Return Value**: Returns the buffer on success, `NULL` on error.

### `chdir`

```c
int chdir(const char *path);
```

- **Parameters**: Directory path to change to.
- **Return Value**: 0 on success, -1 on error.

### `stat`, `lstat`, `fstat`

```c
int stat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
```

- **Parameters**: `path` is the file path or file descriptor, `buf` is a pointer to a `struct stat` to store file information.
- **Return Value**: 0 on success, -1 on error.

### `unlink`

```c
int unlink(const char *pathname);
```

- **Parameters**: `pathname` is the file path to be deleted.
- **Return Value**: 0 on success, -1 on error.

### `execve`

```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

- **Parameters**: `pathname` is the file path of the executable, `argv` is an array of argument strings, `envp` is an array of environment variable strings.
- **Return Value**: Only returns on error, -1 on error.

### `dup`, `dup2`

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

- **Parameters**: `oldfd` is the file descriptor to duplicate, `newfd` is the new file descriptor (for `dup2`).
- **Return Value**: New file descriptor on success, -1 on error.

### `pipe`

```c
int pipe(int pipefd[2]);
```

- **Parameters**: Array to store read and write file descriptors.
- **Return Value**: 0 on success, -1 on error.

### `opendir`, `readdir`, `closedir`

```c
DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);
```

- **Parameters**: `name` is the directory path (for `opendir`), `dirp` is the directory handle (for `readdir` and `closedir`).
- **Return Value**: `DIR *` on success (`opendir`), `struct dirent *` on success (`readdir`), 0 on success (`closedir`), `NULL` on error.

### `strerror`

```c
char *strerror(int errnum);
```

- **Parameters**: Error number.
- **Return Value**: Error message string.

### `perror`

```c
void perror(const char *s);
```

- **Parameters**: Error message prefix (optional).
- **Return Value**: None.

### `isatty`

```c
int isatty(int fd);
```

- **Parameters**: File descriptor.
- **Return Value**: Returns 1 if the file descriptor refers to a terminal, 0 otherwise.

### `ttyname`

```c
char *ttyname(int fd);
```

- **Parameters**: File descriptor.
- **Return Value**: Returns a pointer to the terminal name string on success, `NULL` on error.

### `ttyslot`

```c
int ttyslot(void);
```

- **Parameters**: None.
- **Return Value**: Slot number in the terminal table.

### `ioctl`

```c
int ioctl(int fd, int request, ...);
```

- **Parameters**: `fd` is the file descriptor, `request` is the ioctl request code, optional argument.
- **Return Value**: Varies depending on the request and success/failure.

### `getenv`

```c
char *getenv(const char *name);
```

- **Parameters**: Environment variable name.
- **Return Value**: Returns a pointer to the value of the environment variable, or `NULL` if not found.

### `tcsetattr`, `tcgetattr`

```c
int tcsetattr(int fd, int actions, const struct termios *termios_p);
int tcgetattr(int fd, struct termios *termios_p);
```

- **Parameters**: `fd` is the file descriptor, `actions` are optional actions, `termios_p` is a pointer to a `struct termios` to store terminal attributes.
- **Return Value**: 0 on success, -1 on error.

### `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

```c
int tgetent(char *bp, const char *name);
int tgetflag(const char *id);
int tgetnum(const char *id);
char *tgetstr(const char *id, char **area);
char *tgoto(const char *cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));
```

- **Parameters**: Termcap or terminfo database entry name, buffer to store the result, optional arguments.
- **Return Value**: 1 on success, 0 if the entry is not found, -1 on error.

---

## Commit flags

| Flags    | Args                      |
|----------|---------------------------|
| FIX      | norm / bug                |
| REFACTOR | norm / feature / function |
| ADD      | file / function / feature |
| DELETE   | file / function / feature |
| MERGE    | from->to                  |
