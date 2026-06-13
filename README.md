# XMUS
text-based synthesizer
## usage
```
xmus [in_file.xmus] [out_file.wav]
```
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
you can also write rests as follows
```
rest(4)
```
if you want to make a comment, start the line with two forward slashes
```
// this is a comment
```