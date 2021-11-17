#!/usr/bin/env sh

# Important metacharacters matching
# \d - any digit in range [0-9]
# \w - alphanumeric match characters in english text [A-Za-z0-9_]
# \s - whitespace character

# \D - any non-digit character
# \W - any non-alphanumeric char (such as punctuation)
# \S - any non-whitespace char


# Matches
# [ab8] : any char among 'a', 'b' or '8'
# [^ab] : any char except 'a' or 'b' 
# [a-d] : any char in the range of 'a' through 'd'
# ^abhi : match all lines beginning with the word 'abhi'
# abhi$ : match all lines ending with the word 'abhi'

# a{3}	: {number} specifies the number of times a pattern should match
# a{1,3}: match the char 'a' no more than 3 times but no less than one time. Puts a more
#         restrictive bounds on the pattern (lower an upper bounds) occurence.
# ab?c	: optionality character '?'. Will match both strings 'abc' and 'ac'. 

# Capturing group patterns
# ^(IMG\d+)\.png$ 	: Finds all images, but captures only filenames (without extension .png)
# ^(IMG(\d+))\.png$	: Finds 2 groups (nested paranthesis), i.e. filenames and image #

# Using conditional operators on groups
# Hello\s(world|hell)	: matches "Hello world" and "Hello hell" only

# Using backreferencing to refer to captured groups (not all implementations have it)
# \0 - usually the full matched text
# \1 - group 1
# \2 - group 2



# challenge #2: Find the number of words (in /usr/share/dict/words) that contain at least three as and don’t have a 's ending.
cat /usr/share/dict/words | grep -P '.*a.*a.*a.*[^a]$' | wc -l

# What are the three most common last two letters of those words? 
# grep -E 'patter'  -> -E is for extended regular expression ERE (unlike BRE used by default) 
# NOTE: -E option of grep (ERE) doesn't allow metacharacters like \d etc to work. For that
#       we need to use -P (perl syntax)
# sed -E 's/pattern/replace' -> -E is again for ERE, \1 refers to the 1st matched group 
# uniq -c -> removes duplicate and preceeds the words with 'count' of their occurence
# sort -n -> sorts numerically rather than alphabetically
# tail -n 3 -> print last 3 lines
# awk '{print $2}' -> useful for performing column wise operations (here printing 2nd column of output)
cat /usr/share/dict/words | grep -P '.*a.*a.*a.*[^a]$' | sed -E 's/.*(..)$/\1/' | sort | uniq -c | sort -n | tail -n 3 | awk '{print $2}'

#  How many of those two-letter combinations are there? 
# tr <find> <replace>	-> (tr)anslate command used to modify character stream
cat /usr/share/dict/words | grep -P '.*a.*a.*a.*[^a]$' | tr [:upper:] [:lower:] | sed -E 's/.*(..)$/\1/' | sort | uniq -c | wc -l


# Find your average, median, and max system boot time over the last ten boots. Use journalctl on Linux and log show on macOS, and look for log timestamps near the beginning and end of each boot.
# I am leaving the output to 'total' number of seconds taken by userspace to boot (from all in instances of journalctl log)
# paste -sd+ : places the delimiter char '+' at the end of every line of text in STDOUT.
journalctl | grep -P 'systemd\[\d+\]: Startup finished in.*\(userspace\).*' | sed -E 's/.*\+ (.*)s \(userspace\).*\.$/\1/' | paste -sd+ | bc


# Look for boot messages that are not shared between your past three reboots (see journalctl’s -b flag). Break this task down into multiple steps. First, find a way to get just the logs from the past three boots. There may be an applicable flag on the tool you use to extract the boot logs, or you can use sed '0,/STRING/d' to remove all lines previous to one that matches STRING. Next, remove any parts of the line that always varies (like the timestamp). Then, de-duplicate the input lines and keep a count of each one (uniq is your friend). And finally, eliminate any line whose count is 3 (since it was shared among all the boots).
(journalctl -b && journalctl -b -1 && journalctl -b -2)  | sed -E 's/[0-9]{2}:[0-9]{2}:[0-9]{2}+/Abhinav/' | sort | uniq -c | sed -E 's/^\s+3.*$//'





