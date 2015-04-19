# rshell
Rshell imitates the functionality of a terminal. Rshell performs the following steps:

1. Print the command prompt
	`userName@hostName $` 
2. Read in a command on one line. Commands can be separated by connectors.
Connectors include `&&`, `||`, and `;`.
3. Execute the line of commands
	- If a command is followed by `;`, then the next command (if any) is always executed.
	- If a command is followed by `&&`, then the next command is executed only if the first one succeeds (returning true).
	- If a command is followed by `||`, then the next command is executed only if the first one does not succeed (returning false).
	- If a command is empty, it returns false. Rshell does not output an error. 
	- Anything found after the first found `#` is considered a comment and will be ignored. 

## How To Run rshell
```
$ git clone https://github.com/jle034/rshell.git
$ cd rshell
$ git checkout hw0
$ make
$ bin/rshell
```

### Bugs/Limitations
- Commands with more than 2 but less than 7 flags will not execute.
- Echo with quotes will include quotes in output.
