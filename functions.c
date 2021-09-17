#include <stdlib.h>
#include <stdio.h>

#define n_sector 3
#define epsilon 0.0001

/* Fill in the functions and define helper functions if you need to */

unsigned int find_index(float value, float *total_times_unsorted, unsigned int len);

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    int i, j, k;

    float ***sector_times;

    scanf("%u %u", n_drivers, n_laps);

    sector_times = (float ***) malloc(*n_drivers * sizeof(float *));
    
    for (i = 0; i < *n_drivers; i++)
    {
        sector_times[i] = (float **) malloc(*n_laps * sizeof(float *));

        for (j = 0; j < *n_laps; j++)
        {
            sector_times[i][j] = (float *) malloc(n_sector * sizeof(float));

            for (k = 0; k < n_sector; k++)
            {
                scanf("%f", &sector_times[i][j][k]);
            }
        }
    }
    return sector_times;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    unsigned int ** positions_arr;
    int i, j;

    scanf("%u %u", p_drivers, n_races);

    positions_arr = (unsigned int **) malloc(*p_drivers * sizeof(unsigned int *));

    for (i = 0; i < *p_drivers; i++)
    {
        positions_arr[i] = (unsigned int *) malloc(*n_races * sizeof(unsigned int));

        for (j = 0; j < *n_races; j++)
        {
            scanf("%u", &positions_arr[i][j]);
        }
    }

    return positions_arr;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    float **lap_times;
    int i, j;

    lap_times = (float **) malloc(n_drivers * sizeof(float *));
    
    for (i = 0; i < n_drivers; i++)
    {
        lap_times[i] = (float *) malloc(n_laps * sizeof(float));

        for (j = 0; j < n_laps; j++)
        {
            lap_times[i][j] = sector_times[i][j][0] + sector_times[i][j][1] + sector_times[i][j][2];
        }
    }

    return lap_times;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    unsigned int driver_id = 0;
    int i, j;
    float fastest_lap_time = lap_times[0][0];
    

    for (i = 0; i < n_drivers; i++)
    {
        for (j = 0; j < n_laps; j++)
        {
            if (lap_times[i][j] + epsilon < fastest_lap_time)
            {
                fastest_lap_time = lap_times[i][j];
                driver_id = i;
            }
        }
    }

    return driver_id;
}


unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
    unsigned int fastest_lap_no = 0;
    float fastest_lap_time = sector_times_of_driver[0][0] + sector_times_of_driver[0][1] + sector_times_of_driver[0][2];
    int i;

    for (i = 0; i < n_laps; i++)
    {
        float new_lap_time = sector_times_of_driver[i][0] + sector_times_of_driver[i][1] + sector_times_of_driver[i][2];

        if (new_lap_time + epsilon < fastest_lap_time)
        {
            fastest_lap_time = new_lap_time;
            fastest_lap_no = i;
        }
    }

    return fastest_lap_no;
}


float* selection_sort(float* arr, unsigned int len, char ord){
    float *sorted_arr = (float *) malloc(len * sizeof(float)), min_val, max_val;
    int i, j;
    unsigned int index;

    for (i = 0; i < len; i++)
    {
        sorted_arr[i] = arr[i];
    }

    if (ord == 'A')
    {
        for (i = 0; i < len - 1; i++)
        {
            min_val = sorted_arr[i + 1];
            index = i + 1;

            for (j = i + 1; j < len; j++)
            {
                if (sorted_arr[j] + epsilon < min_val)
                {
                    min_val = sorted_arr[j];
                    index = j;
                }
            }

            if (sorted_arr[i] - epsilon > sorted_arr[index])
            {
                sorted_arr[index] = sorted_arr[i];
                sorted_arr[i] = min_val;
            }
        }
    }
    else if (ord == 'D')
    {
        for (i = 0; i < len - 1; i++)
        {
            max_val = sorted_arr[i + 1];
            index = i + 1;

            for (j = i + 1; j < len; j++)
            {
                if (sorted_arr[j] - epsilon > max_val)
                {
                    max_val = sorted_arr[j];
                    index = j;
                }
            }

            if (sorted_arr[i] + epsilon < sorted_arr[index])
            {
                sorted_arr[index] = sorted_arr[i];
                sorted_arr[i] = max_val;
            }
        }
    }

    return sorted_arr;
}


unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    float *total_times_unsorted = (float *) malloc(n_drivers * sizeof(float)), total_time, *total_times_sorted;
    int i, j;
    unsigned int *finishing_positions = (unsigned int *) malloc(n_drivers * sizeof(unsigned int));

    for (i = 0; i < n_drivers; i++)
    {
        total_time = 0;

        for (j = 0; j < n_laps; j++)
        {
            total_time += lap_times[i][j];
        }

        total_times_unsorted[i] = total_time;
    }

    total_times_sorted = selection_sort(total_times_unsorted, n_drivers, 'A');

    for (i = 0; i < n_drivers; i++)
    {
        finishing_positions[i] = find_index(total_times_sorted[i], total_times_unsorted, n_drivers);
        total_times_unsorted[finishing_positions[i]] = -1;
    }

    return finishing_positions;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
    unsigned int driver2){
    float difference = 0, *arr = (float *) malloc(n_laps * sizeof(float));
    int i;

    for (i = 0; i < n_laps; i++)
    {
        difference += lap_times[driver1][i] - lap_times[driver2][i];
        arr[i] = difference;
    }

    return arr;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    unsigned int *arr = (unsigned int *) malloc(p_drivers * sizeof(unsigned int)), total;
    unsigned int *pos_point = (unsigned int *) malloc(p_drivers * sizeof(unsigned int));
    int i, j;

    for (i = 0; i < p_drivers; i++)
    {
        scanf("%u", pos_point + i);
    }

    for (i = 0; i < p_drivers; i++)
    {
        total = 0;
        for (j = 0; j < n_races; j++)
        {
            total += pos_point[positions[i][j] - 1];
        }
        arr[i] = total;
    }

    return arr;
}


unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    unsigned int ranking = p_drivers;
    float my_points = total_points[id];
    int i;

    for (i = 0; i < p_drivers; i++)
    {
        if (my_points > total_points[i])
        {
            ranking--;
        }
        else if (id < i && my_points == total_points[i])
        {
            ranking--;
        }
    }

    return ranking;
}


unsigned int find_index(float value, float *total_times_unsorted, unsigned int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (value == total_times_unsorted[i])
        {
            return i;
        }
    }
    return 0;
}
