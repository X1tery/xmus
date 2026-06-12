# XMUS
text file based daw
## usage
this daw uses western music notation written in a specific format, which is interpreted by the program\

the first two lines of the sheet file contain the bpm value and time signature respectively
```
120
4/4
```
after that, each note is formatted as follows
- note length in brackets (eg. 4 for 4th note)
- note pitch in parentheses (must be lowercase)
- note wave style
```
[4](a4){sin}
```
currently there are 3 wave styles:
- sin (sine wave)
- tri (triangular wave)
- sqr (square wave)

if you want to construct a chord, write multiple notes on a single line separated by comas
```
[4](d4){sin}, [4](a4){tri}
```