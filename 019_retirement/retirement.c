#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info_t working,  //info about working
                retire_info_t retired)  //info about being retired
{
  double balance;
  balance = initial;
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, balance);
    balance = balance + balance * working.rate_of_return + working.contribution;
    startAge++;
  }

  for (int j = 0; j < retired.months; j++) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, balance);
    balance = balance + balance * retired.rate_of_return + retired.contribution;
    startAge++;
  }
}
int main(void) {
  retire_info_t Working;
  retire_info_t Retired;
  int Age = 327;
  double savings = 21345;
  Working.months = 489;
  Working.contribution = 1000;
  Working.rate_of_return = 0.045 / 12;
  Retired.months = 384;
  Retired.contribution = -4000;
  Retired.rate_of_return = 0.01 / 12;
  retirement(Age, savings, Working, Retired);
  return 0;
}
