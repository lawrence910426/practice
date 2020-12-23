#include <stdio.h>

int get_history_score() {
    int ans;
    FILE *f = fopen("history_score.txt", "r");
    fscanf(f, "%d", &ans);
    fclose(f);
    return ans;
}

void write_score(int score) {
    FILE *f = fopen("history_score.txt", "w");
    fprintf(f, "%d", score);
    fclose(f);
}
