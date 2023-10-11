#include <stdio.h>

#define TD_2PT  8
#define TD_FG   7

enum scoring_plays_idx {
    TD_2PT_IDX,
    TD_FG_IDX,
    TOTAL_SCORING_PLAYS,
};

void print_scoring_plays(int *scoring_plays)
{
    printf("%d TD + 2pt, ", scoring_plays[TD_2PT_IDX]);
    printf("%d TD + FG\n", scoring_plays[TD_FG_IDX]);
}

void n_touchdown_fg(int score, int *scoring_plays) {
    for (int i = 0; i <= score / TD_FG; ++i) {
        scoring_plays[TD_FG_IDX] = i;
        if (score - (TD_FG * i) == 0) {
            print_scoring_plays(scoring_plays);
        }
    }
}

void n_touchdown_2pt(int score, int *scoring_plays)
{
    for (int i = 0; i <= score / TD_2PT; ++i) {
        scoring_plays[TD_2PT_IDX] = i;
        n_touchdown_fg(score - (TD_2PT * i), scoring_plays);
    }
}

void find_possible_scoring_combos(int score)
{
    printf("\nPossible Combinations of Scoring Plays\n");
    int scoring_plays[TOTAL_SCORING_PLAYS] = {0};
    n_touchdown_2pt(score, scoring_plays);
    printf("\n");
}

int main()
{
    int score = 0;
    while (1) {
        printf("\nEnter 0 or 1 to STOP");
        printf("\nEnter the NFL score: ");
        scanf("%d", &score);
        if (score < 2) {
            return 0;
        }
        find_possible_scoring_combos(score);
    }
    return 0;
}