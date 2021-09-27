#include <stdio.h>

char chess[15][15], junk;
int main() {
    int Q; // We have to solve Q tasks
    int i, j, x, y; // 'i' represents the enumerator of the x-axis. 'j' represents the enumerator of the y-axis.
    int col; // 'col' represents the enumerator of color
    
    int dx[8], dy[8];
    int direction = 0, len;
    for(i = 0;i < 3;i++) for(j = 0;j < 3;j++) if(i != 1 || j != 1) {
        dx[direction] = (i - 1);
        dy[direction] = (j - 1);
        direction += 1;
    }

    int ans;
    scanf("%d", &Q); scanf("%c", &junk); // Junk would receive '\n' from the input stream.
    
    while(Q--) {
        for(i = 0;i < 15;i++) {
            for(j = 0;j < 15;j++) scanf("%c", &chess[i][j]);
            scanf("%c", &junk); // Junk would receive '\n' from the input stream.
        }
        
        ans = -1;
        for(i = 0;i < 15;i++) for(j = 0;j < 15;j++) for(col = 0;col < 2;col++) for(direction = 0;direction < 8;direction++) {
            x = i; y = j;
            for(len = 0;len < 5;len++) {
                if(x < 0 || 15 <= x || y < 0 || 15 <= y || chess[x][y] != (col == 0 ? 'w' : 'b')) break;
                x += dx[direction]; y += dy[direction];
            }
            if(len == 5) ans = col;
        }
        if(ans == -1) printf("none\n");
        else if(ans == 0) printf("white\n");
        else if(ans == 1) printf("black\n");
    }

}
