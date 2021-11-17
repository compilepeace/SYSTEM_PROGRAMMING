# Missing Semester
This is my notekeeping from [missing semester].

[missing semester]: https://missing.csail.mit.edu/ 


## **4 Data Wrangling**
Tools used - 

```
sed 's/regx/w/g'- useful while substituting input stream
awk		- useful to perform column wise operations on input data
uniq		- remove duplicate data
sort		- sort date based on many aspects
past -sd+	- To merge lines of files via a delimiter '-d<char>' 
bc		- standard calculator which takes an arithmetic expression as input from STDIN

ffmpeg		- tool to work with video conversions
convert		- converts images from one type to another
feh		- an image viewer
```

* Practice regular expressions from [short interactive regex tutorial]

[short interactive regex tutorial]: https://regexone.com/

Summary for RE - 
```
# Important metacharacters matching
\d - any digit in range [0-9]
\w - alphanumeric match characters in english text [A-Za-z0-9_]
\s - whitespace character

\D - any non-digit character
\W - any non-alphanumeric char (such as punctuation)
\S - any non-whitespace char


# Matches
[ab8] : any char among 'a', 'b' or '8'
[^ab] : any char except 'a' or 'b' 
[a-d] : any char in the range of 'a' through 'd'
^abhi : match all lines beginning with the word 'abhi'
abhi$ : match all lines ending with the word 'abhi'

a{3}	: {number} specifies the number of times a pattern should match
a{1,3}: match the char 'a' no more than 3 times but no less than one time. Puts a more
        restrictive bounds on the pattern (lower an upper bounds) occurence.
ab?c	: optionality character '?'. Will match both strings 'abc' and 'ac'. 

# Capturing group patterns
^(IMG\d+)\.png$ 	: Finds all images, but captures only filenames (without extension .png)
^(IMG(\d+))\.png$	: Finds 2 groups (nested paranthesis), i.e. filenames and image #

# Using conditional operators on groups
Hello\s(world|hell)	: matches "Hello world" and "Hello hell" only

# Using backreferencing to refer to captured groups (not all implementations have it)
\0 - usually the full matched text
\1 - group 1
\2 - group 2
```

## **5 Command-line Environment**

* Job Control

```
ps aux | grep <patter>					# find processes
pgrep -au <username> <process_name>		# find pid and cmdline name of a process 
pkill <process_name>					# kill a process by name

kill -TERM <pid>						# ask <pid> to exit gracefully
kill -INT <pid>							


```


```
sleep 1000
nohup sleep 2000 &

jobs	# lists all the jobs that are run by the current session
bg %1	# makes the suspended program back into running stage
fg %1	# bring the background program to foreground

kill -STOP %1	# stop the first program (displayed by 'jobs' cmd)
kill -HUP %1	# program will stop (hangup) because 'nohup' was not given 
kill -HUP %2	# send a hangup signal to 2nd job (cannot be hangup because of 'nohup')

alias ls="ls -lAtch"
alias mkdir="mkdir -p"
alias mv="mv -i"
alias ls			# tells what the alias is
alias				# displays all the aliases 
```

* Visualizing Sessions, Windows and Panes
```
Sessions
	Windows (relate to TABS in browsers)
		Panes (partition of a window/tab)
```
* Using terminal multiplexer (tmux)

```
tmux
sleep 1000 &
tmux a			# attach to the session
tmux ls			# list all sessions (default naming is number based '0', '1' ...)
	
Sessions : 
tmux			# start a new session
tmux ls			# lists current sessions
tmux new -s NAME 	# create a new session('new') by the name('-t') of 'foobar'
tmux rename-session -t 0 <new_name>
tmux a			# attaches the last session.
tmux a -t NAME		# specify which session ('NAME' here) to attach to
<c-a> ?	
<c-a> d		: detach a session

Windows : 
<c-a> c		: create a new window
<c-a> <N>	: goto N'th window
<c-a> p		: goto (p)revious window
<c-a> n		: goto (n)ext window
<c-a> ,		: rename current window
<c-a> w		: list current windows

Panes : 
<c-a> -		: horizontally split the current pane (default is <c-b> ")
<c-a> |		: vertically split the current pane (default is <c-b> %)
<M>-h,j,k,l	: (M)eta key (usually Alt) to navigate through panes
<c-a> space	: equally space the panes (repetidly press it to navigate through different layouts)
<c-a> z		: zoom-in or out the current pane
<c-a> <c-arrow> : to resize a pane in the direction of arrow key
```

### Dotfiles
These are the configuration files/startup scripts used by programs (for user-customizations/plugins)
* .bashrc
* .vimrc

```

```





