### rshell
`rshell` imitates the functionality of a terminal. `rshell` performs the following steps:

##### hw0

1. Print the command prompt `userName@hostName $` 
2. Read in a command on one line. Commands can be separated by connectors.
	- Connectors include `&&`, `||`, and `;`.
3. Execute the line of commands
	- If a command is followed by `;`, then the next command (if any) is always executed.
	- If a command is followed by `&&`, then the next command is executed only if the first one succeeds (returning true).
	- If a command is followed by `||`, then the next command is executed only if the first one does not succeed (returning false).
	- Anything found after the first found `#` is considered a comment and will be ignored. 

##### Known Bugs(hw0)

- Commands with more than 2 but less than 7 flags will not execute.
- `echo` with quotes will include quotes in output.

##### hw2

In addition to hw0 functionality, `rshell` can now perform the following:

1. Input redirection (< and <<<)
2. Output redirection (> and >>)
3. Pipes (single and chained)

##### Known Bugs(hw2)

- single and double quotes are always included in string inputs	
- Cannot pipe with input redirection

##### hw3

In addition to hw0 and hw2 funcionality, `rshell` can now perform the following:

1. prompt also displays the current working directory
	- the home folder is replaced with a `~` for readability
2. `cd <PATH>` which will change the current working directory to <PATH>
3. `cd` which will change the current working directory to the home directory
4. `cd -` prints an error if OLDPID is not set
4. `^C` does not exist `rshell`.
The current foreground job receives the `SIGINT` signal instead.
This kills the job, and control is returned to `rshell`.

##### Known Bugs(hw3)

- `cd -` does not change the current working directory

### ls
`ls` implements a subset of the GNU `ls` command: 

1. It can support the -a, -l, and -R optional flags; and the ability to pass in one or many files optional. 
2. It also displays different types of files in different colors that can be combinable
	- directories are blue
	- executables are green
	- hidden files have a gray background

##### Known Bugs(hw1)
- Files are listed in alphabetical order from left to right, then top to bottom.
- Columns are all of equal width.	
- Sometimes outputs an unnecessary endl.

##### How To Run rshell
```
$ git clone https://github.com/jle034/rshell.git
$ cd rshell
$ git checkout hw2
$ make
$ bin/rshell
```

##### How To Run ls
```
$ git clone https://github.com/jle034/rshell.git
$ cd rshell
$ git checkout hw1
$ make
$ bin/ls
```
