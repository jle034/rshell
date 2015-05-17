## rshell
`rshell` imitates the functionality of a terminal. `rshell` performs the following steps:

#### hw0

1. Print the command prompt `userName@hostName $` 
2. Read in a command on one line. Commands can be separated by connectors.
Connectors include `&&`, `||`, and `;`.
3. Execute the line of commands
	- If a command is followed by `;`, then the next command (if any) is always executed.
	- If a command is followed by `&&`, then the next command is executed only if the first one succeeds (returning true).
	- If a command is followed by `||`, then the next command is executed only if the first one does not succeed (returning false).
	- Anything found after the first found `#` is considered a comment and will be ignored. 

##### Known Bugs(hw0)
	- Commands with more than 2 but less than 7 flags will not execute.
	- `echo` with quotes will include quotes in output.

#### hw2

`rshell` can now perform the following:

1. Input redirection (< and <<<)
2. Output redirection (> and >>)
3. Pipes (single and chained)

##### Known Bugs(hw2)
	- single and double quotes are always included in string inputs	
	- Cannot pipe with input redirection

## ls
`ls` implements a subset of the GNU `ls` command: 

1. It can support the -a, -l, and -R optional flags; and the ability to pass in one or many files optional. 
2. It also displays different types of files in different colors that can be combinable
	- directories are blue
	- executables are green
	- hidden files have a gray background

##### Known Bugs 
	- Files are listed in alphabetical order from left to right, then top to bottom.
	- Columns are all of equal width.	
	- Sometimes outputs an unnecessary endl.

### How To Run rshell
```
$ git clone https://github.com/jle034/rshell.git
$ cd rshell
$ git checkout hw2
$ make
$ bin/rshell
```

### How To Run ls
```
$ git clone https://github.com/jle034/rshell.git
$ cd rshell
$ git checkout hw1
$ make
$ bin/ls
```
