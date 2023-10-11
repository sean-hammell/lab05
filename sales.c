#include <stdio.h>

#define N_MONTHS 12

const char *months[12] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December",
};

void short_month_name_extra_tab(int month)
{
    if (!(month == 1 || month == 8 || month == 10 || month == 11)) {
        printf("\t");
    }
}

void monthly_sales(float *sales)
{
    printf("\nMonthly Sales Report\n\n");
    printf("Month\t\tSales\n\n");
    for (int i = 0; i < N_MONTHS; ++i) {
        printf("%s", months[i]);
        short_month_name_extra_tab(i);
        printf("\t$%.2f\n", sales[i]);
    }
}

void sales_summary(float *sales)
{
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

void six_month_moving_average(float *sales)
{
    int i = 0;
    float moving_average = 0;
    for (; i < (N_MONTHS / 2) - 1; ++i) {
        moving_average += sales[i];
    }

    printf("\n\nSix-Month Moving Average Report\n\n");
    for (; i < N_MONTHS; ++i) {
        moving_average += sales[i];
        printf("%s\t", months[i - 5]);
        short_month_name_extra_tab(i - 5);
        printf("-\t%s", months[i]);
        short_month_name_extra_tab(i);
        printf("\t$%.2f\n", moving_average / 6);
        moving_average -= sales[i - 5];
    }
}

void highest_to_lowest(float *sales)
{
    int i_months[N_MONTHS] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
    };

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
        short_month_name_extra_tab(i_months[i]);
        printf("\t$%.2f\n", sales[i_months[i]]);
    }
}

int main()
{
    char file[64];
    printf("Enter input file: ");
    scanf("%s", file);
    FILE *input = fopen(file, "r");

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
