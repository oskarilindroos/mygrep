# mygrep

C++ clone of the command line tool "grep" on Unix. Clones the basic functionality of grep.

Done as a course project for *Ohjelmoinnin edistyneet piirteet*.

## Installation
---

`g++ mygrep.cpp -o mygrep`

## Usage
---
`./mygrep [OPTION(s)] pattern [FILE]`

On Windows, use `./mygrep.exe` instead.

Examples
```
$ ./mygrep following man_grep_plain_ASCII.txt 
     The following options are available:
     The grep utility exits with one of the following values:
```

```
$ ./mygrep -olio FolloWING man_grep_plain_ASCII.txt 
32:     The following options are available:
245:     The grep utility exits with one of the following values:

Occurrences of lines containing "FolloWING": 2
```

```
$ ./mygrep
Give a string from which to search for: Search me please
Give a search string: me

"me" found in "Search me please" in position 7
```
## Options/Command line arguments
---
        All arguments must start with '-o' and can be combined with each other in any order. 
        For example: -oloir, -oroil, oirlo all return the same result.

        Valid arguments
        -ol
            Prints the line numbers of the lines the pattern was found on.

        -oo
            Prints how many occurrences of the pattern were found.

        -or
            Reverse search. Prints every line that the pattern wasn't found on.

        -oi
            Case insensitive search. 
