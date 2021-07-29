# C Library Functions

## **/usr/include/string.h**

### Memory functions
Here source and destination are memory addresses.  
* **memcpy**    : copy N bytes of SRC to DEST  
* **memccpy**   : Copy no more than N bytes of SRC to DEST, stopping when C is found. Return the position in DEST one byte past where C was copied, or NULL if C was not found in the first N bytes of SRC.   
* **memmove**   : copy N bytes of SRC to DEST, guaranteeing correct behavior for overlapping strings.  
* **memset**    : set N bytes of S to C.  
* **memcmp**    : compare N bytes of S1 and S2.  
* **memchr**    : search N bytes of S for C.  
* **memrchr**   : search N bytes of S for the final occurence of C.  
* **rawmemchr** : search in S for C. This is similar to `memchr` but there is no length limit.  

* **memmem**    : find the first occurrence of NEEDLE in HAYSTACK.

### String functions  
Here source and destination are strings (array of characters terminated by a NULL byte).  

* **strnlen**   : find the length of STRING, but scan at most MAXLEN characters. If no '\0' terminator is found in that many characters, return MAXLEN. 
* **strncpy**   : copy no more than N chars of SRC to DEST. 
* **strncat**   : Append no more than N characters from SRC onto DEST.   
* **strncmp**   : compare N characters of S1 and S2.  

* **strcoll**   : compare the collated forms of S1 and S2.
* **strxfrm**   : put a transformation of SRC into no more than N bytes of DEST.
* **strcoll_l** : compare the collated forms of S1 and S2, using sorting rules from L (locale).
* **strxfrm_l** : put a transformation of SRC into no more than N bytes of DEST, using sorting rules from L.  
  
* **strndup**   : return a malloc'd copy of at most N bytes of STRING. The resultant string is terminated even if no NULL terminator appears before STRING[N].
* **strndupa**  : return an alloca'd copy of at most N bytes of string. 

* **strchr**    : find the first occurence of C in S.  
* **strrchr**   : find the last occurence of C in S.  
* **strchrnul** : it is similar to `strchr`. But it returns a pointer to the closing NULL byte in case C is not found in S. 

* **strspn**    : return the length of the initial segment of S which consists entirely of characters in ACCEPT. 
* **strcspn**   : return the length of the initial segment of S which consists entirely of characters not in REJECT.
* **strpbrk**   : find the first occurrence in S of any character in ACCEPT.

* **strstr**    : find the first occurrence of NEEDLE in HAYSTACK.
* **strcasestr**: similar to `strstr` but this function ignores the case of both strings.  
* **strtok**    : Divide S into tokens separated by characters in DELIM.  

* **strerror**          : return a string describing the meaning of the `errno` code in ERRNUM parameter.
* **strsignal**         : return a string describing the meaning of the signal number in SIG.
* **basename**          : return the file name within directory of FILENAME.  
* **explicit_bzero**    : set N bytes of S to 0.  
* **strsep**            : return the next DELIM-delimited token from *STRINGP  
* **strverscmp**        : compare S1 and S2 as strings holding name & indices/version numbers.
* **strfry**            : Sautee STRING briskly.
* **memfrob**           : Frobnicate N bytes of S.


```
Degraded Functions
* strcpy    : copy SRC to DEST
* strcat    : Append SRC onto DEST. 
* strcmp    : compare S1 and S2.  
* strdup    : duplicate S, returning an identical malloc'd string.  
* strdupa   : Duplicate S, returning an identical alloca'd string (memory on stack segment).  
* strlen    : return the length of S.  
```