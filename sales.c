#include <stdio.h>

#define N_MONTHS 12

/**
 * array of month names for easy access in loops
 */
const char *months[N_MONTHS] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December",
};

/**
 * short_name_extra_tab: add an extra tab for months with names less than 8
 * characters to keep tabular format consistent
 */
void short_name_extra_tab(int month)
{
        if (!(month == 1 || month == 8 || month == 10 || month == 11)) {
                printf("\t");
        }
}

/**
 * monthly_sales: print the sales report by month
 */
void monthly_sales(float *sales)
{
        printf("\nMonthly Sales Report\n\n");
        printf("Month\t\tSales\n\n");
        for (int i = 0; i < N_MONTHS; ++i) {
                printf("%s", months[i]);
                short_name_extra_tab(i);
                printf("\t$%.2f\n", sales[i]);
        }
}

/**
 * sales_summary: print a summary of the sales report including maximum sales,
 * minimum sales, and average sales
 */
void sales_summary(float *sales)
{
        /**
         * find the the indices for the months with maximum and minimum sales
         * and calculate average sales
         */
        int i_max = 0;
        int i_min = 0;
        float average = 0;
        for (int i = 0; i < N_MONTHS; ++i) {
                if (sales[i] > sales[i_max]) {
                        i_max = i;
                }

                if (sales[i] < sales[i_min]) {
                        i_min = i;
                }

                average += sales[i];
        }
        average /= N_MONTHS;

        printf("\n\nSales Summary\n\n");
        printf("Minimum Sales:\t$%.2f\t(%s)\n", sales[i_min], months[i_min]);
        printf("Maximum Sales:\t$%.2f\t(%s)\n", sales[i_max], months[i_max]);
        printf("Averag Sales:\t$%.2f\n", average);
}

/**
 * six_month_moving_average: print the six month moving averages across the year
 */
void six_month_moving_average(float *sales)
{
        /**
         * sum up the first five months
         */
        int i = 0;
        float moving_average = 0;
        for (; i < (N_MONTHS / 2) - 1; ++i) {
                moving_average += sales[i];
        }

        /**
         * for the remaining seven months, add the sales for that month to the
         * moving average, compute the average, and remove the earliest month
         * of sales remaining in the average for the next iteration
         */
        printf("\n\nSix-Month Moving Average Report\n\n");
        for (; i < N_MONTHS; ++i) {
                moving_average += sales[i];
                printf("%s\t", months[i - 5]);
                short_name_extra_tab(i - 5);
                printf("-\t%s", months[i]);
                short_name_extra_tab(i);
                printf("\t$%.2f\n", moving_average / 6);
                moving_average -= sales[i - 5];
        }
}

/**
 * highest_to_lowest: print the sales report by month ordered from highest sales
 * to lowest sales
 */
void highest_to_lowest(float *sales)
{
        /**
         * bubble sort the array of month indices (so the original array isn't
         * altered) in descending order
         */
        int i_months[N_MONTHS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        for (int i = N_MONTHS; i > 0; --i) {
                for (int j = 0; j < i - 1; ++j) {
                        if (sales[i_months[j]] < sales[i_months[j + 1]]) {
                                float temp = i_months[j];
                                i_months[j] = i_months[j + 1];
                                i_months[j + 1] = temp;
                        }
                }
        }

        printf("\n\nSales Report (Highest to Lowest)\n\n");
        printf("Month\t\tSales\n\n");
        for (int i = 0; i < N_MONTHS; ++i) {
                printf("%s", months[i_months[i]]);
                short_name_extra_tab(i_months[i]);
                printf("\t$%.2f\n", sales[i_months[i]]);
        }
}

int main()
{
        /**
         * get the input file from the user
         */
        char file[64];
        printf("Enter input file: ");
        scanf("%s", file);
        FILE *input = fopen(file, "r");

        /**
         * write the input data to the sales array
         */
        float sales[N_MONTHS];
        for (int i = 0; i < N_MONTHS; ++i) {
                fscanf(input, "%f\n", sales + i);
        }

        monthly_sales(sales);
        sales_summary(sales);
        six_month_moving_average(sales);
        highest_to_lowest(sales);
        printf("\n");

        fclose(input);
}
