#include <stdio.h>
#include <string.h>

#define SUCCESS 0
#define UNKNOWN_FILE 1
#define EMPTY_STR 2
#define OVERFLOW 3
#define INCORRECT_DATA 4

#define MODEL_LEN 50
#define COUNTRY_LEN 50
#define COLOR_LEN 30
#define CONDITION_LEN 5
#define FILENAME_LEN 20
#define MAX_RECORDS_COUNT 100

#define FILE_INPUT_MSG "Введите имя входного файла для работы: "
#define CREATE_FILE_MSG "\nУказанный файл не найден. Желаете ли Вы создать новый? ('y' to continue) "
#define ERR_CREATE_MSG "\nНе удалось создать файл с таким именем. Попробуйте снова.\n"
#define INPUT_MSG "\
1 -- Поиск информации о сроках гарантии на новые автомобили\n \
2 -- Упорядочить таблицу по возрастанию цены на автомобиль\n \
3 -- Добавить запись в конец таблицы\n \
4 -- Удалить запись по указанному полю\n \
5 -- Просмотр отсортированной таблицы ключей при неотсортированной исходной таблице\n \
6 -- Вывод упорядоченной исходной таблицы\n \
7 -- TODO\n"


typedef struct info
{
    char model[MODEL_LEN + 2];
    char country[COUNTRY_LEN + 2];
    int price;
    char color[COLOR_LEN + 2];
    char condition[CONDITION_LEN + 2];
    union
    {
        int guarantee;
        struct old_info
        {
            int year;
            int mileage;
            int number_of_repairs;
            int number_of_owners;
        } old_car;
        
    } add_info;
    
} car_info;


typedef struct indexes
{
    int index;
    int price;
} help_table;


int get_str(FILE *f, char *str, int max_len)
{
    int len = 0;

    char ch = getc(f);


    while (ch != ';')
    {
        str[len++] = ch;

        if (len > max_len - 1)
            return OVERFLOW;

        ch = getc(f);
    }

    return (len) ? SUCCESS : EMPTY_STR;
}


int get_table(FILE *f, car_info table[], help_table index_table[])
{
    char buf;


    for (int i = 0; i < MAX_RECORDS_COUNT + 1 && feof(f) == 0; ++i)
    {
        if (i == MAX_RECORDS_COUNT)
            return OVERFLOW;

        if (get_str(f, table[i].model, MODEL_LEN + 1))
            return INCORRECT_DATA;

        if (get_str(f, table[i].country, COUNTRY_LEN + 1))
            return INCORRECT_DATA;

        if (fscanf(f, "%d", &(table[i].price)) != 1 || (buf = getc(f)) != ';')
            return INCORRECT_DATA;

        if (get_str(f, table[i].color, COLOR_LEN + 1))
            return INCORRECT_DATA;

        if (get_str(f, table[i].condition, CONDITION_LEN + 1))
            return INCORRECT_DATA;
        if (strcmp(table[i].condition, "new") == 0)
        {
            if (fscanf(f, "%d", &(table[i].add_info.guarantee)) != 1 || (buf = getc(f)) != ';')
                return INCORRECT_DATA;
        }
        else if (strcmp(table[i].condition, "old") == 0)
        {

        }
        else
            return INCORRECT_DATA;
    }
}


int main(void)
{
    int key = -1;

    char filename[FILENAME_LEN + 1] = { 0 };


    printf(FILE_INPUT_MSG);
    fscanf(stdin, "%s", filename);

    FILE *f = fopen(filename, "r+");
    if (f == NULL)
    {
        char ans;


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
            return UNKNOWN_FILE;
    }

    while (key != 0)
    {
        printf(INPUT_MSG);
    }

    fclose(f);    

    return SUCCESS;
}
