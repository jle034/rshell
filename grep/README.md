##Grep

####What is grep?

Grep is a useful search tool.

If no files are specified or the file name `-` is given, it searches standard input.
Grep prints the matching lines to standard output by default, but you can use its built-in options to display additional information.
We will be talking about some of the commonly used options in more detail later.

####How to use grep

It’s pretty easy, really! Grep uses the following format:

```
grep ‘pattern’ filename
```

For example, if you want to search through your source code and examine the instances where you used “cout” in your code, you could simply use a `find` command (such as ‘/’ in vim) within your code.
This method, however, leaves a lot of room for mistakes.
It is very easy to accidentally overlook something when you are monotonously searching through every instance of the word “cout” looking for the exact one you want to find.
By using the grep command, you could have every matching line printed out to standard out for you to look through and analyze all together.

Let’s try to do the above mentioned using the grep command on main.cpp

```
grep cout main.cpp
```

This would output the following:

```
		cout << “Hello, I am a child!” << endl;
		cout << “Hello, I am a parent!” << endl;
	cout << endl;
```

 

 

Let’s look at an example of when you would use grep.

 

```

history | grep “g++”

```

In this line of commands, we are using the history command piped to a grep command.
This line will search through your history and print any lines that contain “g++” to standard output.
This will be helpful for times when you go back and search for a specific error or warning that was found when you previously used the g++ command.

This line of commands could output something like this depending on your history:

```

 

 

 

                   

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
