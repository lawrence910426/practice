# The Gomoku Problem
This problem is a naive brute force problem. The real problem is, how should we design our program with simple & delicate implementation?

# By using loops and arrays to reduce sophisticated & repeative code
```C
int dx[8], dy[8]; //dx, dy represents the eight directions on a Cartesian coordinate.
for(i = 0;i < 8;i++) {
    x += dx[i];
    y += dy[i];
}
```
