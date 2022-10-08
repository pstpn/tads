#include <stdio.h>
#include <stdlib.h>

#include "../inc/my_def.h"
#include "../inc/my_err.h"
#include "../inc/my_msgs.h"
#include "../inc/my_types.h"
#include "../inc/tools.h"
#include "../inc/w_w_table.h"
#include "../inc/my_in_out.h"
#include "../inc/my_print.h"
#include "../inc/my_measure.h"


int main(void)
{
    car_info table_cars[RECORDS_COUNT] = { 0 };

    help_table index_table[RECORDS_COUNT] = { 0 };

    measurement_table measures[COUNT_MEAS]= { 0 };

    int key = -1;
    int count = 0;

    char filename[FILENAME_LEN + 1] = { 0 };


    printf(FILE_INPUT_MSG);
    fscanf(stdin, "%s", filename);

    FILE *f = fopen(filename, "r+");
    char ans;


    if (f == NULL)
    {
        printf(CREATE_FILE_MSG);
        fscanf(stdin, "\n%c", &ans);
        if (ans == 'y')
        {
            f = fopen(filename, "w");
            if (f == NULL)
            {
                printf(ERR_CREATE_MSG);
                return UNKNOWN_FILE;
            }
        }
        else
        {
            printf(ERR_OPEN_MSG);
            return UNKNOWN_FILE;
        }

        printf("\n");
    }
    else
    {
        if (get_tables(f, table_cars, index_table, &count))
        {
            printf(ERR_READING_MSG);
            fclose(f);
            return INCORRECT_DATA;
        }
    }

    int sorted_keys = FALSE;


    while (key != 0)
    {
        printf(INPUT_MSG);
        if (fscanf(stdin, "%d", &key) != 1 ||
        key < 0 || key > MENU_LEN)
        {
            printf(ERR_CODE_MSG);
            fclose(f);
            return INCORRECT_CODE;
        }

        switch (key)
        {
            case 0:
                fclose(f);
                return SUCCESS;
            case 1:
            {
                if (finding_info(table_cars, count))
                    printf(ERR_ADD_MSG);
                break;
            }
            case 2:
            {
                car_info cur_table[RECORDS_COUNT] = { 0 };


                deep_cpy(cur_table, table_cars, count, sizeof(car_info));

                qsort(&cur_table, count, sizeof(car_info), compare_prices);

                print_cars(cur_table, count);
                break;
            }
            case 3:
            {
                qsort(&index_table, count, sizeof(help_table), key_compare_prices);

                sorted_keys = TRUE;

                print_keys(index_table, count);
                break;
            }
            case 4:
            {
                print_cars(table_cars, count);
                break;
            }
            case 5:
            {
                print_keys(index_table, count);
                break;
            }
            case 6:
            {
                if (sorted_keys == FALSE)
                    qsort(&index_table, count, sizeof(help_table), key_compare_prices);
                    
                sorted_keys = TRUE;

                print_cars_using_keys(table_cars, index_table, count);
                break;
            }
            case 7:
            {
                car_info new_car = { 0 };

                int rc = adding_car_in_table(f, &new_car, &count);


                if (rc == OVERFLOW)
                    printf(ERR_OVER_MSG);
                else if (rc > SUCCESS)
                    printf(ERR_ADD_MSG);
                else
                    table_cars[count - 1] = new_car;

                break;            
            }
            case 8:
            {
                if (delete_cars(table_cars, index_table, &count))
                    printf(ERR_DEL_MSG);

                break;
            }
            case 9:
            {
                if (sorted_keys == FALSE)
                    qsort(&index_table, count, sizeof(help_table), key_compare_prices);
                    
                sorted_keys = TRUE;

                print_keys(index_table, count);
                break;
            }
            case 10:
            {
                if (sorted_keys == TRUE)
                {
                    help_table new_keys[RECORDS_COUNT] = { 0 };


                    restore_key_table(new_keys, table_cars, count);
                    get_measures(measures, table_cars, new_keys, count);
                }
                else
                    get_measures(measures, table_cars, index_table, count);

                print_measures(measures);
                break;
            }
            case 11:
            {
                sorted_keys = FALSE;
                
                restore_key_table(index_table, table_cars, count);
                break;
            }
        }
    }

    fclose(f);    

    return SUCCESS;
}