# VIM cheetsheet
This cheetsheet is created going through [lecture 3 of missing semester].

[lecture 3 of missing semester]: https://missing.csail.mit.edu/2020/editors/

## Moving
In normal mode - 
```
h,j,k,l - move left, down, up and right respectively
7h	- move 7 characters towards left
7j	- move 7 lines down the current position
7k	- move 7 lines up the current position
7l	- move 7 characters towards right

w 	- move to the start of next word
b 	- move back or move to the beginning of previous word
e	- move to the end of current word

G 	- move to the EOF (end of file)
gg	- move to the BOF (beginning of file)
7G	- move to the 7th line

Ctrl+u 	- move up the text buffer
Ctrl+d 	- move down the text buffer

$	- move to the end of line
^	- move to the first representable character written on line
0	- move to the first character of line (char can be space)

```

## Searching
```
/findme - searches for 'findme' in the file and moves the cursor to it when we press enter
	- use 'n' to go to next occurence of 'findme'

f[char] - move forward to the first occurence of [char]
F[char] - move to the [char] just before the current position.
`
```

## Editing

```
i	- get into insert mode
a	- get into append mode (i.e. move one character ahead in insert mode)

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

~	- After selecting line of text, use '~' to flip the case (upper<->lower) of selected text


y	- yank/copy the selected chunk of text
yw	- copy a word ahead
yb	- copy a word behind
yy	- copy current line

p	- paste
```

## Command mode 
```
:help w		- open up help with key 'w' (jump to word ahead)
:help :w	- open up help for command ':w' (write changes to file)
```

## Misclaneous
When in command mode, press -
```
.	- period '.' pastes the exact same thing done previously on the current cursor.
:sp	- open up another window
```
