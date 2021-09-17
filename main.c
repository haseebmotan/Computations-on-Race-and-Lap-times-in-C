#include "functions.h"

/*
You will not submit this file, just use for testing your code.
All your implementations should be in functions.c
*/

/*
To compile your code, use "make main"
Then "./main" to run.
If you want to compile again, you need to delete the previous executable.
You may do this by "make clean" or simply "rm main"
*/

int main(){

    /*
    Function calls here to test your code
    Example:
    float ***sector_times, **laptimes;
    unsigned int fastest_lap, **positions;
    sector_times = create_sector_times(...);
    positions = create_positions(...);
    lap_times = calculate_lap_times(...);
    fastest_lap = find_fastest_lap(lap_times, ...);
    printf("Printing fastest lap to check the answer: %d\n", fastest_lap);
    */

    float unsorted[25], *sorted;
    int i;
    
    for (i = 0; i < 25; i++)
    {
        scanf("%f", unsorted + i);
    }

    sorted = selection_sort(unsorted, 25, 'D');

    for (i = 0; i < 25; i++)
    {
        printf("%.2f\n", sorted[i]);
    }

    return 0;
}
