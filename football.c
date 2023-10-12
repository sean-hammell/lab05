#include <stdio.h>

/**
 * types of scoring plays
 */
enum play_types {
        TD_2PT,
        TD_FG,
        TD,
        FG,
        SAFETY,
        N_PLAY_TYPES,
};

/**
 * value of each play type
 */
const int play_values[N_PLAY_TYPES] = {8, 7, 6, 3, 2};

/**
 * print_plays: print the combination of scoring plays that results in the final
 * score
 */
void print_plays(int *plays)
{
        printf("%d TD + 2pt, ", plays[TD_2PT]);
        printf("%d TD + FG, ", plays[TD_FG]);
        printf("%d TD, ", plays[TD]);
        printf("%d 3pt FG, ", plays[FG]);
        printf("%d Safety\n", plays[SAFETY]);
}

/**
 * scoring_plays: recursively determine the possible combinations of scoring
 * plays that equal the provided NFL score.
 */
void scoring_combinations(int score, int *plays, int play_type)
{
        /**
         * once each play type has been checked, print the combination if it
         * matches the NFL score
         */
        if (play_type == N_PLAY_TYPES) {
                if (score == 0) {
                        print_plays(plays);
                }

                return;
        }

        /**
         * loop over possible combinations of the current play type and
         * recursively check the remaining play types
         */
        int max_plays = score / play_values[play_type];
        for (int i = 0; i <= max_plays; ++i) {
                plays[play_type] = i;
                scoring_combinations(score - (play_values[play_type] * i),
                                     plays,
                                     play_type + 1);
        }
}

int main()
{
        int score = 0;
        int plays[N_PLAY_TYPES] = {0};
        while (1) {
                printf("\nEnter 0 or 1 to STOP");
                printf("\nEnter the NFL score: ");
                scanf("%d", &score);
                if (score < 2) {
                        return 0;
                }
                printf("\nPossible Combinations of Scoring Plays\n");
                scoring_combinations(score, plays, TD_2PT);
        }

        return 0;
}