#Grep

Grep is a useful search command. 
It searches any inputted file(s) for lines that match a given pattern.

By default, grep prints the matching lines to standard output.
You can, however, use any of its many options to display additional information.
We will be talking about some of grep’s commonly used flags in more detail later.

It’s pretty easy, really! Grep uses the following format:

```
$ grep ‘pattern’ filename
```

###Searching through a file

Let’s say you want to search through your code to find the lines where you used `cout`.
  
This is where the grep bash command comes in.
By using the grep command, you could have every matching line printed to standard out.
Only the lines of code you are focusing on will be filtered out and put in one place for you to analyze.

To search through ex1.cpp, you would use the grep command as follows:

```
$ grep ‘cout’ examples/ex1.cpp
```

This would output the following to standard output:

```
		cout << “Hello, I am a child!” << endl;
		cout << “Hello, I am a parent!” << endl;
	cout << endl;
```

This might not seem like much of an upgrade from using the ‘find’ command within your code, but imagine searching for a pattern that is matched over twenty times.
Even with a `find` command, that is a lot of code to manually look through. 
Grep makes it a bit easier by isolating the important text from everything else.

###Searching through multiple files

The grep command is not limited to only one file.
You could search through multiple files and even directories using the same format we have been using.
Let’s say you want to search for the instances where you used `cout` in both `ex1.cpp` and `ex2.cpp`.

If you pass multiple files as command line parameters, grep will search through all of them.
For example:

``` 
$ grep ‘cout’ examples/ex1.cpp examples/ex2.cpp
```

You can also recursively search through a directory by including the ‘-r’ option as follows:

```
$ grep -r ‘cout’ examples
```

Both of these commands have the same output:

```
examples/ex1.cpp:		 cout << "Hello, I am a child!" << endl;
examples/ex1.cpp:		cout << "Hello, I am a parent!" << endl;
examples/ex1.cpp:	cout << endl;
examples/ex2.cpp:	cout << "goodbye world" << endl;
``` 

###Searching through other texts

Now that you know how to use grep to search through files, you can also use it to search through any other form of text. 
Note that if no files are specified or the file name `-` is given, grep waits for and searches standard input.
This is a quick and easy way to practice using the grep command. 

One special use of the grep command is with `git log`, which shows your commit logs.
Let’s say you are able to fix a crucial bug in your code one day.
You commit, celebrate, and continue working on your code.
After spending days on this project, you realize that your code is completely wrong and want to go back to an old commit.
Perhaps you want to go back to that ‘bug-fixed’ commit.
How are you going to search through over hundreds of commits?

It turns out that `git log` has a `grep` option!
You could use this command to search for the right commit:

```
$ git log --grep “bug fixed”
```

If you are smart enough with your commit messages and search pattern, you will be able to narrow down your search significantly.
The command will output something like this, depending on your commit log:

```
commit 2ef16dec1d0fc79cc0c01ec02a5c1c17b1e91963
Author: Jennifer Le <jle034@hammer.cs.ucr.edu>
Date:   Tue May 05 15:49:31 2015 -0700

    long user-inputs bug fixed

commit 91b19e03715aa6bbf876a2d3b836de65bbea7daa
Author: Jennifer Le <jle034@hammer.cs.ucr.edu>
Date:   Wed Apr 01 00:18:44 2015 -0700

    infinite loop bug fixed

commit 1e6715e5577ffb11299da2d919a98e097ac3f299
Author: Jennifer Le <jle034@hammer.cs.ucr.edu>
Date:   Tue Mar 31 01:06:24 2015 -0700

    code works but doesn’t end, still needs infinite loop bug fixed
```

You could also use `grep` with most other bash commands.
Let’s say you want to search through your history and find all previous uses of `g++`.
You could pipe the history command to your grep search as follows

```
$ history | grep ‘g++’
```

The command will output something like this, depending on your history:

```
169     g++ main.cpp
172     echo g++
173     g++ main.cpp 2> errors
175     g++ -Wall -Werror -ansi -pedantic main.cpp
177     g++ main2.cpp
183     g++ -Wall -Werror -ansi -pedantic main2.cpp
184     history | grep 'g++'
190     
```

TALK ABOUT USING REGEX TO SEARCH FOR ‘^g++’
MOVE REGEX SECTION UP HERE

###Including options

We have already briefly mentioned the ‘-r’ flag that allows ‘grep’ to recursively search through directories.
Grep has many other options to choose from as well. 
To include options in your command, just follow this format:

```
$ grep [options] ‘pattern’ filename
```

A good example would be the ‘-c’ flag. 
We have been talking about using the grep command to output matching lines.
What if you only cared about how many times a matching line was found?

Easy. 
Just include the `-c` flag as follows:

```
$ grep –c ‘cout’ examples/ex1.cpp
```

This command line will search through ex1.cpp and count how many lines contain the pattern ‘cout’.
You should get this:

```
3
```
You could also use multiple options at once.
Let’s say you want to recursively search through a directory and count how many lines contain a match to your pattern.
You could use both the ‘-c’ and ‘-r’ flags together.
You can add flags to a command in two different ways as follows:

```
$ grep –cr ‘cout’ examples
```
or 
```
$ grep –c –r ‘cout’ examples
```

Both of these command lines will search through the example directory and count the number of matching lines. You will get this:

```
examples/ex1.cpp:3
examples/ex2.cpp:1
```

These are only two of grep’s many options.
You can browse through a complete list of these by visiting the [grep](http://linux.die.net/man/1/grep) man page.

###Using regular expressions

Another neat way to expand your uses of the grep command is with the use of [regex] (https://github.com/mikeizbicki/ucr-cs100/tree/2015spring/textbook/tools/bash/regex), short for regular expressions.
Regular expressions are special patterns of letters and symbols that represent a search pattern.

Let’s say you want to search for blank lines in your code. 
Maybe you just want to know how many lines of your code are not being used.
How do you search for a blank line using grep?

The caret symbol `^` is a regular expression that matches at the beginning of a string or line, and the dollar sign `$` is a regular expression that matches at the end.
Putting these two regular expressions together, we have a pattern that represents a blank line.
 
Let’s search for blank lines in our examples/ex1.cpp file:

```
$ grep ‘^$’ examples/ex1.cpp
```

Using this command line, you should get this:

```




```

But wait a minute, that’s a bit silly to be printing blank lines.
That doesn’t mean anything to us.
What we want to know is exactly how many of these lines we have in our code.

We can update our search command to this:

```
$ grep –c ‘^$’ examples/ex1.cpp
```

This command line will output this:

```
4
```

Whoa. 
Grep flags AND regular expressions?
That’s right.
You can use any combination of grep’s options, regular expressions, and other bash commands to narrow down your search to exactly what you are looking for.
Think of the endless possibilities!

Happy searching! :]

