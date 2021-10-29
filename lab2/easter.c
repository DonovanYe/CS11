/* Donovan Ye
 * CS 11 C Track
 * Lab 2
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ABS(a) ((a < 0) ? -a : a) /* Function for absolute value */
#define YEAR_UPPER 39999
#define YEAR_LOWER 1582
#define METONIC_CYCLE 19
#define CENTURY_YEARS 100
#define SUNDAY 1

/* Function prototypes */
int calculate_Easter_date(int year);
int is_Sunday(int day, int month, int year);

/*
 * calculate_Easter_date: returns the day of they year Easter falls 
 * argument: year: integer year in [1582, 39999] 
 * return: positive (April) or negative(March) value for the day of the month 
 *         Returns 0 if year is not in [1582, 39999]
 */
int calculate_Easter_date(int year) {
    int golden_year, 
        century, 
        skipped_leap_years, 
        correction_factor, 
        sunday,
        epact, 
        march_full_moon, 
        easter;

    /* Return 0 if out of range */
    if (year < YEAR_LOWER || year > YEAR_UPPER) {
        return 0;
    }

    /* The golden year in the metonic cycle */
    golden_year = (year % METONIC_CYCLE) + 1;

    /* The century the year is in */
    century = (year / CENTURY_YEARS) + 1;

    /* The number of leap years skipped */
    skipped_leap_years = (3 * century / 4) - 12;

    /* Correction factor because the moon does not orbit 
     * the Earth in exactly 235x in metonic cycle. */
    correction_factor = ((8 * century + 5) / 25) - 5;

    /* A Sunday based only on the year and skipped leap years */
    sunday = (5 * year / 4) - skipped_leap_years - 10;

    /* Epact: days since moon was new */
    epact = \
        (11 * golden_year + 20 + correction_factor - skipped_leap_years) % 30;
    if ((epact == 25 && golden_year > 11) || (epact == 24)) {
        epact++;
    }

    /* The date of the full moon in March */
    march_full_moon = 44 - epact;
    if (march_full_moon < 21) {
        march_full_moon += 30;
    }

    /* Adjust Sunday based on epact, correction factor, golden year, and 
     * the date of the full moon in March to get actual Sunday.
     */
    easter = march_full_moon + 7 - ((sunday + march_full_moon) % 7);

    /* If the value is greater than 31, it is in April so we return as positive
     * Otherwise, it is in March and so we return it as negative.
     */
    if (easter > 31) {
        return easter - 31;
    }
    else {
        return -easter;
    }
}

/*
 * is_Sunday: checks whether given day and month falls on a Sunday using
 *            Zeller's Congruence.
 * args: 
        day: day of month
         month: month of the year starting with March 
                (3 = March, 4 = April, ... , 13 = January, 14 = February)
         year: year of the day/month to check for Sunday
 * return: boolean of whether day of the month is a Sunday or not
 */
int is_Sunday(int day, int month, int year) {
    int day_of_week, year_of_century, zero_based_century;

    /* We want to start counting at March and change January to 13 and 
     * February to 14. If we adjust to 13 or 14, decrement the year.
     */
    if (month < 3) {
        month += 12;
        year--;
    }

    /* The years since the start of the century */
    year_of_century = year % CENTURY_YEARS;

    /* The century the year is in zero indexed. */
    zero_based_century = year / CENTURY_YEARS;

    /* Zeller's Congruence
     * h = (q + floor(13(m + 1) / 5) + K + floor(K / 4) + 
                                                    floor(J / 4) + 5J) mod 7
     * h = day of week (0 = Saturday, 1 = Sunday, ... )
     * q = day of the month
     * m = month (3 = March, 4 = April, ... , 13 = January, 14 = February)
     * K = year of the century
     * J = zero based century
     */
    day_of_week = (day + ((13 * (month + 1)) / 5) +  \
            year_of_century + year_of_century / 4 + \
            zero_based_century / 4 + 5 * zero_based_century) % 7;

    /* Check that the day of the week produced by the formula is Sunday. */
    return day_of_week == 1;
}

int main(void) {

    while(1) {
        int day, month_n, year, result, easter;
        char month[6];

        /* Scan input from stdin */
        result = scanf("%d", &year);

        /* If end of the file, then end loop */
        if (result == EOF) {
            break;
        }

        /* Calculate easter and assign proper month or handle error. */
        easter = calculate_Easter_date(year);
        day = ABS(easter);
        if (easter < 0) {
            strcpy(month, "March");
            month_n = 3;
        }
        else if (easter > 0) {
            strcpy(month, "April");
            month_n = 4;
        }
        else {
            /* Output error to stderr */
            fprintf(stderr, "Year %d is not within expected range.", year);
        }
        
        /* Check that the day is actually a Sunday */
        assert(is_Sunday(day, month_n, year));

        /* Output Year - Month Day to stdout */
        printf("%d - %s %d\n", year, month, day);
    }
    return 0;
}