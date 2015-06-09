##Grep

####What is grep?

Grep is a useful search tool.
It searches any inputted FILEs for lines that contain a match to a given PATTERN.

If no files are specified or the file name `-` is given, it searches standard input.
Grep prints the matching lines to standard output by default, but you can use its many options to display additional information.
We will be talking about some of grep’s commonly used flags in more detail later.

####How to use grep

It’s pretty easy, really! Grep uses the following format:

```
$ grep ‘pattern’ filename
```

For example, if you want to search through your source code and examine the instances where you used “cout” in your code, you could simply use a `find` command (such as `/` in vim) within your code.
This method, however, leaves a lot of room for mistakes and does not have as much functionality as grep does.
It is very easy to accidentally overlook something when you are monotonously searching through every instance of the word “cout” looking for the exact line you want to find.
This is where the grep command comes in.
By using the grep command, you could have every matching line printed out to standard out for you to look through and analyze all together.

Let’s try to do the above mentioned using the grep command on main.cpp

```
$ grep ‘cout’ main.cpp
```

This would output the following:

```
		cout << “Hello, I am a child!” << endl;
		cout << “Hello, I am a parent!” << endl;
	cout << endl;
```

This might not seem like much of a difference from using the ‘find’ command within your code, but imagine searching for a pattern that is matched over twenty times.
Even with a `find` command, that is a lot of code to look through.
Grep

The grep command is not limited to only one file.
You could search through multiple files using the same format we have been talking about.
Let’s say you want to search for the instances where you used “cout” in both main.cpp and ex1.cpp.
You would type in the following command:

``` 
$ grep ‘cout’ main.cpp ex1.cpp
```

This command will search through both files for the pattern “cout” and print it to standard output.
You will get this:

```
``` 

It can be used with other commands to search anything you would like.
You could also search multiple files for the same pattern and have this printed to standard output all together.
Let’s talk about another instance where you would want to use grep.
Let’s say you want to search through your history and look for the times where you used “g++”.

```
$ history | grep “g++”
```

In this line of commands, we are using the history command piped to a grep command.
If you don’t already know how the pipe command works, you can read about it HERE.
This line will search through your history and print any lines that contain “g++” to standard output.
Depending on your history, this line of commands could output something like this:

```

```

#### Repitition Operators
 

                    ?                  The preceding item is optional and matched at most once.
                    *                  The preceding item will be matched zero or more times.
                    +                  The preceding item will be matched one or more times.
                    {n}              The preceding item is matched exactly n times.
                    {n, }            The preceding item is matched n or more times.
                    {n,m}         The preceding item is matched at least n times, but not more than m times.

 

As mentioned, grep’s flags are optional.
You can include anything between zero and all of the flags if you want to.
Grep can search through one or more input files, separated by spaces.
The input file names are technically optional as well.
If no input file names are included, grep uses standard input as the input.
This is pretty useless for programming and such, but it is an easy way to learn how the grep command works.

Let’s look at some examples, shall we?

```
$ grep execvp file1
$ grep “execvp” file1
$ grep “execvp other stuff” file1
$ grep “hello world” file1 file2
```

It is important to remember that grep separates a command by spaces.
If you want to search for a single word, the quotes are optional.
Lines 1 and 2 will output the same thing.
If you want to search for a pattern that has more than one word, you must include double or single quotes around it, as shown in line 3.

######Now what happens if I don’t include a file name?

Let’s look at some examples.

```
$ grep “hello world”
> hi
> hello there
> hello world
hello world
> Hello world my name is Jennifer
> hello world my name is Jennifer
hello world my name is Jennifer
```

If you use the grep command without including an input file, it will wait and check for the pattern in standard input.
In the example above, the arrow indicates the user input and everything else is standard output.
On line 4, you can see that grep simply echoes the user input if it has a match to the pattern being searched for.
It is important to note that grep is case-sensitive.
This is why line 6 is not echoed.

####What are some commonly used flags?

####What are some features of grep? (flags, using ‘.’, etc. will be mentioned here)

####When would I use grep?
