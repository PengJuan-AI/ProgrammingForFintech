#include <stdio.h>
#include <stdlib.h>

struct _retire_info{
    int months;
    double contribution;
    double rate_of_return;
};
typedef struct _retire_info retire_info;

double calculation(double capital, double rate, double contribution){
    double result;
    result = capital*(1+rate/12)+contribution;
    return result;
}
void Print(int Age, double capital){
    printf("Age %3d month %2d you have $%.2f\n", Age/12, Age%12,capital);
}

void retirement(int startAge,   //in months
                double initial, //initial savings in dollars
                retire_info working, //info about working
                retire_info retired) //info about being retired
{
    int age=startAge;
    double capital=initial;
    int months = working.months;
    
    while(months!=0){
        Print(age, capital);
        capital = calculation(capital, working.rate_of_return, working.contribution);
        months--;
        age++;
    }
    
    // when retiring
    months = retired.months;
    while(months!=0){
        Print(age, capital);
        capital = calculation(capital, retired.rate_of_return, retired.contribution);
        months--;
        age++;
    }
    
}

int main(void) {
    retire_info working;
    working.months=489;
    working.contribution=1000;
    working.rate_of_return=0.045;

    retire_info retired;
    retired.months=384;
    retired.contribution=-4000;
    retired.rate_of_return=0.01;

    int start_age = 327;
    double initial = 21345;

    retirement(start_age, initial, working, retired);

    return EXIT_SUCCESS;
}
