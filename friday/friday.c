/*
ID: garrett2
LANG: C
TASK: friday
*/

#include <stdio.h>
#include <stdlib.h>

#define START_YEAR 1900
#define START_DAY MONDAY
#define DAYS_IN_WEEK 7
#define MONTHS_IN_YEAR 12
#define TARGET_DATE 13

typedef enum {
  SATURDAY,
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY
} DAY;

typedef enum {
  JANUARY,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
} MONTH;

// Figure out how long a month is in a given year, counting leap years
int monthLength(MONTH month, int year) {
  switch (month) {
    case JANUARY:
    case MARCH:
    case MAY:
    case JULY:
    case AUGUST:
    case OCTOBER:
    case DECEMBER:
      return 31;
      
    case APRIL:
    case JUNE:
    case SEPTEMBER:
    case NOVEMBER:
      return 30;
    
    case FEBRUARY:
      if (year % 4 == 0 && (year % 400 == 0 || year % 100 != 0)) {
        return 29;
      } else {
        return 28;
      }
      
    default:
      return -1;
  }
}

// Figure out what day a given day of the month falls on,
// given the day of the 1st
DAY whatDay(DAY first, int target) {
  return (first + target - 1) % DAYS_IN_WEEK;
}

// Figure out the next day, given the current day
DAY nextDay(DAY current) {
  return (current + 1) % DAYS_IN_WEEK;
}

int main() {
  int i, j; // Loop indices
  
  FILE *fin = fopen("friday.in", "r");
  if (!fin) {
    printf("Failed to open friday.in\n");
    exit(EXIT_FAILURE);
  }
  
  int N;
  fscanf(fin, "%d", &N);
  
  int num_per_day[DAYS_IN_WEEK];
  for (i = 0; i < DAYS_IN_WEEK; i++) {
    num_per_day[i] = 0;
  }
  
  DAY curr_day = START_DAY;
  for (i = 0; i < N; i++) {
    for (j = JANUARY; j < MONTHS_IN_YEAR; j++) {
      num_per_day[whatDay(curr_day, TARGET_DATE)]++;
      curr_day = nextDay(whatDay(curr_day, monthLength(j, START_YEAR + i)));
    }
  }
  
  FILE *fout = fopen("friday.out", "w");
  for (i = SATURDAY; i < DAYS_IN_WEEK; i++) {
    fprintf(fout, "%d", num_per_day[i]);
    if (i == DAYS_IN_WEEK - 1) {
      fprintf(fout, "\n");
    } else {
      fprintf(fout, " ");
    }
  }
  
  // Clean up and exit
  fclose(fin);
  fclose(fout);
  exit(EXIT_SUCCESS);
}

