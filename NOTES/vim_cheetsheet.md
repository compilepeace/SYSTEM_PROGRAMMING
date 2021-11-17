# VIM cheetsheet
This cheetsheet is created going through [lecture 3 of missing semester].

[lecture 3 of missing semester]: https://missing.csail.mit.edu/2020/editors/

Resources to read - 
```
:help vimrc-intro - Information to write .vimrc file.
:help user-manual - read user manual
```

## Executing commands in cmd mode
```
:!cmd	- execute a shell command. Eg: :!pwd (it will print the current working directory)

:w haha - writes changes into a file named 'haha'
```

## Moving
In normal mode - 
```
h,j,k,l - move left, down, up and right respectively
7h	- move 7 characters towards left
7j	- move 7 lines down the current position
7k	- move 7 lines up the current position
7l	- move 7 characters towards right

%	- type '%' while present on '(', '{' or '[' to go the matching closing character.
	  this is a very useful while debugging a program with unmatched paranthesis.

w 	- move to the start of next word (helpful key while reading code)
b 	- move back or move to the beginning of previous word
e	- move to the end of current word (helpful key while writing code)

G 	- move to the EOF (end of file)
gg	- move to the BOF (beginning of file)
7G	- move to the 7th line
10	- move 10 lines ahead of the current line

Ctrl+u 	- scroll up the text buffer
Ctrl+d 	- scroll down the text buffer

$	- move to the end of line
^	- move to the first representable character written on line
0	- move to the first character of line (char can be space)

```

## Searching
```
/findme - searches for 'findme' in forward direction and moves the cursor to it. 
	- use 'n' to goto next occurence and 'N' to goto the previous occrence of 'findme'
?findme - searches for 'findme' in backward direction.
/find\c - search the word 'find' with case insenstivity.
Ctrl+o	- move the cursor back to where it came from.
Ctrl+i	- move the cursor forward (from where we pressed Ctrl+o)

f[char] - move forward to the first occurence of [char]
F[char] - move to the [char] just before the current position.

```

## Editing
`i`, `a` and `A` all get into the insert mode after their effects.
```
i	- get into insert mode
a	- Append to the next character from the current position.
A	- Append to the end of line.

r<char>	- replace a character at current position with <char>
R<chars>- replace a stream of characters at current position with <chars>

o	- opens a newline below and move the cursor to it in insert mode.
O	- opens a newline above the current position.

```

## Deleting and Changing
```
dw	- delete a word ahead
db 	- delete a word behind 
dd 	- delete the current line

di{	- delete everything 'inside' braces.
da'	- delete everything 'around' single-quotes (including single-quotes). 

cw	- change word is like 'dw', but puts us into 'insert' mode after deleting.
cb	- deletes a word behind (just like 'db') but also puts us into 'insert' mode.
cc	- deletes the current line (just like 'dd') but also puts us into 'insert' mode. 
7cw	- change 7 words (could also be written as c7w)

ci(	- change/delete everything 'inside' paranthesis and put us into insert mode
ca"	- change/delete everything 'around' double-quotes (including paranthesis itself) 

x 	- delete the character at current position.
7x	- delete 7 characters from current position.

:s/old/new	- to substitute 'old' for 'new' for only the first occurence of 'old' in line
:s/old/new/g	- to substitute 'old' for 'new' in the whole line ('g')
:s/old/new/gc	- same as above command but asks the user before making a change
:#,#s/old/new/g - '#,#' is the range of line numbers in which substitution is to be made.
:%s/old/new/g	- to substitute all occurences of 'old' by 'new' in the entire file type.
```

## Undo and Redo
```
u	- undo an action
Ctrl+r	- redo an action
```

## Select, Copy and Paste
```
v	- get into visual/selection mode and use movement keys to select text
V       - select current line (visual line mode)
Ctrl+v  - select a rectangular block of text
:w new	- will write the selected text to a file named 'new'

~	- After selecting a chunk, use '~' to flip the case (upper<->lower) of selected text
d	- After selecting a chunk, press 'd' to delete it.


y	- yank/copy the selected chunk of text
yw	- copy a word ahead
yb	- copy a word behind
yy	- copy current line
y2j	- copies 2 lines below

p	- paste
```

## Retrieving and Merging 
We can retrieve the 'contents of a file' or 'output of a command' to the current position 
of our cursor by using `:r <file/cmd>` command.
```
:r haha - retrieve the 'content of file' named 'haha'. In other words, it places the 
	  content of a file named 'haha' to the current position of cursor.
:r !ls	- retrieve the 'output of command' named 'ls'. In other words, it places the output 
	  of 'ls' command to the current position of our cursor. 
```

## Misclaneous
When in command mode, press -
```
.	- period '.' pastes the exact same thing done previously on the current cursor.
:sp	- horizontal split windows 
:vsp	- vertical split windows 
Ctrl+ww - to switch between windows 

:edit file1	- start editing 'file1' (generally useful after splitting windows :vsp)
```

## Help, Settings and Configurations
```
:help		- opens up help (or press F1 key)
:help w		- open up help with key 'w' 
:help :w	- open up help for command ':w' (write changes to file)
Ctrl+ww		- Switch between windows.

:e<Ctrl+d>	- <Ctrl+d> will show all possible completions of commands starting with 'e'
:e<TAB>		- <TAB> uses autocompletion.	

:set ic		- set 'ignore-case' senstivity for searching
:set hls is	- set 'hlsearch' (highlight) and 'incsearch' (incremental search)

:set noic	- set 'no-ignore-case' for searching, i.e. enfore case-senstivity
:set nohls	- disable search highlighting
:set nois	- disable 'incremental search', i.e. search while typing itself '/typi..'
:set nocp	- disable compatability mode
```
