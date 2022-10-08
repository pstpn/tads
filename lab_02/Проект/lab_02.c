#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define SUCCESS 0
#define UNKNOWN_FILE 1
#define EMPTY_STR 2
#define OVERFLOW 3
#define INCORRECT_DATA 4
#define INCORRECT_CODE 5
#define INCORRECT_MODEL 6
#define INCORRECT_PRICE 7

#define MODEL_LEN 11
#define COUNTRY_LEN 15
#define COLOR_LEN 11
#define CONDITION_LEN 11
#define FILENAME_LEN 20
#define RECORDS_COUNT 20000
#define PRICE_LEN 11
#define YEAR_LEN 6
#define MIL_LEN 9
#define REP_LEN 9
#define OWN_LEN 8
#define GUAR_LEN 11
#define INDEX_LEN 17
#define NUM_LEN 17
#define SLOW_LEN 16
#define QUICK_LEN 17
#define TIME_MEM_LEN 8
#define TABLE_WIDTH 113
#define KEY_TABLE_WIDTH 49
#define MEASURE_TABLE_WIDTH 79
#define MAX_PRICE 99999999
#define MAX_GUAR 99
#define MAX_YEAR 2022
#define MAX_MIL 999999
#define MAX_REP 99
#define MAX_OWN 99
#define TRUE 1
#define FALSE 0
#define MENU_LEN 11
#define COUNT_MEAS 4

#define SEP ';'
#define NEW_SEP '\n'
#define EMPTY ' '

#define FILE_INPUT_MSG "Введите имя входного файла для работы: "
#define CREATE_FILE_MSG "\nУказанный файл не найден. Желаете ли Вы создать новый? ('y' to continue): "
#define ERR_CREATE_MSG "\nНе удалось создать файл с таким именем. Попробуйте снова.\n\n"
#define ERR_READING_MSG "\nНе удалось прочитать файл с данными. Попробуйте снова.\n\n"
#define ERR_OPEN_MSG "\nНе удалось открыть файл. Попробуйте снова.\n\n"
#define ERR_CODE_MSG "\nНекорректный код. Попробуйте снова.\n\n"
#define ERR_OVER_MSG "\nПроизошло переполнение таблицы. Освободите место и попробуйте снова.\n\n"
#define ERR_ADD_MSG "\nНе удалось добавить запись, так как введено некорректное значение. Попробуйте снова.\n\n"
#define ERR_DEL_MSG "\nНе удалось удалить запись, так как введено некорректное значение. Попробуйте снова.\n\n"
#define INPUT_MSG "\n\
1  --  Поиск информации о неновых автомобилях указанной марки с одним предыдущим \
собственником, отсутствием ремонта в указанном диапазоне цен\n\
2  --  Упорядочить таблицу автомобилей по возрастанию цены на автомобиль и вывести\n\
3  --  Упорядочить таблицу ключей по возрастанию цены на автомобиль и вывести\n\
4  --  Вывести исходную таблицу\n\
5  --  Вывести таблицу ключей\n\
6  --  Вывести исходную таблицу в упорядоченном виде, используя таблицу ключей\n\
7  --  Добавить запись в конец таблицы\n\
8  --  Удалить записи по значению цены\n\
9  --  Просмотр отсортированной таблицы ключей при неотсортированной исходной таблице\n\
10 --  Произвести замеры эффективности обычной и ускоренной сортировок при обработке \
данных в исходной таблице и таблице ключей\n\
11 --  Вернуть таблицу ключей в исходное состояние\n\
0  --  Выход\n: "
#define TABLE_NAME "|   MODEL   |    COUNTRY    |   PRICE   |   COLOR   | CONDITION | GUARANTEE | YEAR | \
MILEAGE | REPAIRS | OWNERS |\n"
#define KEY_TABLE_NAME "|        №        |      INDEX      |   PRICE   |\n"
#define MEASURE_TABLE_NAME "        | SLOW SORT DATA | QUICK SORT DATA | SLOW SORT KEYS | QUICK SORT KEYS |\n"
#define IN_MODEL_MSG "\nВведите модель машины (до 11 символов): "
#define IN_COUNTRY_MSG "\nВведите страну-производитель автомобиля (до 15 символов): "
#define IN_PRICE_MSG "\nВведите цену автомобиля (до 8 цифр): "
#define IN_COLOR_MSG "\nВведите цвет автомобиля (до 11 символов): "
#define IN_COND_MSG "\nВведите состояние автомобиля (0 -- новый; 1 -- старый): "
#define IN_GUAR_MSG "\nВведите срок гарантии в годах (до 99 лет): "
#define IN_YEAR_MSG "\nВведите год выпуска автомобиля (до 2022 года): "
#define IN_MIL_MSG "\nВведите пробег автомобиля (до 6 цифр): "
#define IN_REP_MSG "\nВведите количество ремонтов (до 99): "
#define IN_OWN "\nВведите количество владельцев (до 99): "
#define ADD_IN_FILE_MSG "\nЗапись была успешно добавлена в таблицу! Желаете ли Вы также добавить \
эту информацию в исходный файл? ('y' to continue): "
#define IN_FIND_MODEL_MSG "\nВведите марку автомобиля, который Вы хотите найти: "
#define IN_FIND_MIN_PRICE_MSG "\nВведите минимальную цену: "
#define IN_FIND_MAX_PRICE_MSG "\nВведите максимальную цену: "
#define IN_DEL_MSG "\nВведите цену для удаления всех записей с ней: "


typedef struct info
{
    char model[MODEL_LEN + 2];
    char country[COUNTRY_LEN + 2];
    int price;
    char color[COLOR_LEN + 2];
    int condition;
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


typedef struct measure
{
    long long unsigned time;
    int mem;
} measurement_table;



void draw_line(int len)
{
    for (int i = 0; i < len; ++i)
        printf("-");
    printf("\n");
}


void draw_name(char *table_name, int table_width)
{
    draw_line(table_width);
    printf("%s", table_name);
    draw_line(table_width);
}


void clear_buf(FILE *f)
{
    char buf = '\0';

    
    while (buf != '\n')
        buf = fgetc(f);
}


unsigned long long milliseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;
    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}


void print_car(car_info car)
{
    printf("|%*s|%*s|%*d|%*s|%*d|%*d|%*c|%*c|%*c|%*c|\n",
    MODEL_LEN, car.model, COUNTRY_LEN, car.country,
    PRICE_LEN, car.price, COLOR_LEN, car.color,
    CONDITION_LEN, car.condition, GUAR_LEN,
    car.add_info.guarantee, YEAR_LEN, EMPTY,
    MIL_LEN, EMPTY, REP_LEN, EMPTY, OWN_LEN, EMPTY);
}


void print_cars(car_info cars[], int count)
{
    draw_name(TABLE_NAME, TABLE_WIDTH);

    for (int i = 0; i < count; ++i)
    {
        if (cars[i].condition)
            printf("|%*s|%*s|%*d|%*s|%*d|%*c|%*d|%*d|%*d|%*d|\n",
            MODEL_LEN, cars[i].model, COUNTRY_LEN, cars[i].country,
            PRICE_LEN, cars[i].price, COLOR_LEN, cars[i].color,
            CONDITION_LEN, cars[i].condition, GUAR_LEN, EMPTY, 
            YEAR_LEN, cars[i].add_info.old_car.year, 
            MIL_LEN, cars[i].add_info.old_car.mileage, REP_LEN,
            cars[i].add_info.old_car.number_of_repairs,
            OWN_LEN, cars[i].add_info.old_car.number_of_owners);
        else
            print_car(cars[i]);
        draw_line(TABLE_WIDTH);
    }
}


void write_in_file(FILE *f, car_info car, int count)
{
    if (count)
        fprintf(f, "\n");

    if (car.condition)
        fprintf(f, "%s;%s;%d;%s;%d;%d;%d;%d;%d;",
        car.model, car.country, car.price, car.color, 
        car.condition, car.add_info.old_car.year,
        car.add_info.old_car.mileage,
        car.add_info.old_car.number_of_repairs,
        car.add_info.old_car.number_of_owners);
    else
        fprintf(f, "%s;%s;%d;%s;%d;%d;", car.model, 
        car.country, car.price, car.color,
        car.condition, car.add_info.guarantee);
}


int get_str(FILE *f, char *str, int max_len, char sep)
{
    int len = 0;

    char ch = getc(f);
    if (sep == NEW_SEP)
        ch = fgetc(f);


    while (ch != sep)
    {
        str[len++] = ch;

        if (len > max_len - 1)
        {
            if (sep == NEW_SEP)
                clear_buf(stdin);
                
            return OVERFLOW;
        }

        ch = getc(f);
    }

    return (len) ? SUCCESS : EMPTY_STR;
}


int get_tables(FILE *f, car_info table[], help_table index_table[], int *count)
{
    char buf;


    fgetc(f);
    if (feof(f) != 0)
        return SUCCESS;
    rewind(f);

    for (int i = 0; i < RECORDS_COUNT + 1 && feof(f) == 0; ++i)
    {
        if (i == RECORDS_COUNT)
            return OVERFLOW;

        if (get_str(f, table[i].model, MODEL_LEN + 1, SEP))
            return INCORRECT_DATA;

        if (get_str(f, table[i].country, COUNTRY_LEN + 1, SEP))
            return INCORRECT_DATA;

        if (fscanf(f, "%d", &(table[i].price)) != 1 ||
        (buf = getc(f)) != ';')
            return INCORRECT_DATA;
        if (table[i].price < 1 || table[i].price > MAX_PRICE)
            return INCORRECT_DATA;

        if (get_str(f, table[i].color, COLOR_LEN + 1, SEP))
            return INCORRECT_DATA;

        if (fscanf(f, "%d", &(table[i].condition)) != 1 ||
        (buf = getc(f)) != ';')
            return INCORRECT_DATA;
        if (table[i].condition != 1 &&
        table[i].condition != 0)
            return INCORRECT_DATA;

        if (table[i].condition == 0)
        {
            if (fscanf(f, "%d", &(table[i].add_info.guarantee)) != 1 ||
            (buf = getc(f)) != ';')
                return INCORRECT_DATA;
            if (table[i].add_info.guarantee < 0 ||
            table[i].add_info.guarantee > MAX_GUAR)
                return INCORRECT_DATA;
        }
        else if (table[i].condition == 1)
        {
            if (fscanf(f, "%d", &(table[i].add_info.old_car.year)) != 1 ||
            (buf = getc(f)) != ';')
                return INCORRECT_DATA;
            if (table[i].add_info.old_car.year < 1 ||
            table[i].add_info.old_car.year > MAX_YEAR)
                return INCORRECT_DATA;

            if (fscanf(f, "%d", &(table[i].add_info.old_car.mileage)) != 1 ||
            (buf = getc(f)) != ';')
                return INCORRECT_DATA;
            if (table[i].add_info.old_car.mileage < 1 ||
            table[i].add_info.old_car.mileage > MAX_MIL)
                return INCORRECT_DATA;

            if (fscanf(f, "%d", &(table[i].add_info.old_car.number_of_repairs)) != 1 ||
            (buf = getc(f)) != ';')
                return INCORRECT_DATA;
            if (table[i].add_info.old_car.number_of_repairs < 0 ||
            table[i].add_info.old_car.number_of_repairs > MAX_REP)
                return INCORRECT_DATA;

            if (fscanf(f, "%d", &(table[i].add_info.old_car.number_of_owners)) != 1 ||
            (buf = getc(f)) != ';')
                return INCORRECT_DATA;
            if (table[i].add_info.old_car.number_of_owners < 1 ||
            table[i].add_info.old_car.number_of_owners > MAX_OWN)
                return INCORRECT_DATA;
        }
        else
            return INCORRECT_DATA;

        fgetc(f);

        index_table[i].index = i;
        index_table[i].price = table[i].price;
        ++(*count);
    }

    return SUCCESS;
}


int finding_info(car_info cars[], int count)
{
    char model[MODEL_LEN + 1] = { '\0' };

    int min_price, max_price;


    printf(IN_FIND_MODEL_MSG);
    if (get_str(stdin, model, MODEL_LEN + 1, NEW_SEP))
    {
        clear_buf(stdin);
        return INCORRECT_MODEL;
    }

    printf(IN_FIND_MIN_PRICE_MSG);
    if (fscanf(stdin, "%d", &min_price) != 1 ||
    min_price < 1 || min_price > MAX_PRICE)
    {
        clear_buf(stdin);
        return INCORRECT_PRICE;
    }

    printf(IN_FIND_MAX_PRICE_MSG);
    if (fscanf(stdin, "%d", &max_price) != 1 ||
    max_price < 1 || max_price > MAX_PRICE ||
    max_price < min_price)
    {
        clear_buf(stdin);
        return INCORRECT_PRICE;
    }

    draw_name(TABLE_NAME, TABLE_WIDTH);

    for (int i = 0; i < count; ++i)
        if (cars[i].condition && strcmp(model, cars[i].model) == 0 &&
        cars[i].add_info.old_car.number_of_owners == 1 &&
        cars[i].add_info.old_car.number_of_repairs == 0 &&
        cars[i].price >= min_price && cars[i].price <= max_price)
        {
            print_car(cars[i]);
            draw_line(TABLE_WIDTH);
        }

    return SUCCESS;
}


int compare_prices(const void *p_1, const void *p_2)
{
    const car_info *a = p_1;
    const car_info *b = p_2;


    return a->price - b->price;
}


int key_compare_prices(const void *p_1, const void *p_2)
{
    const help_table *a = p_1;
    const help_table *b = p_2;


    return a->price - b->price;
}


int adding_car_in_table(FILE *f, car_info *car, int *count)
{
    if (*count + 1 > RECORDS_COUNT)
        return OVERFLOW;

    clear_buf(stdin);
    printf(IN_MODEL_MSG);        
    if (get_str(stdin, car->model, MODEL_LEN + 1, NEW_SEP))
        return INCORRECT_DATA;

    printf(IN_COUNTRY_MSG);
    if (get_str(stdin, car->country, COUNTRY_LEN + 1, NEW_SEP))
        return INCORRECT_DATA;

    printf(IN_PRICE_MSG);
    if (fscanf(stdin, "%d", &(car->price)) != 1)
    {
        clear_buf(stdin);
        return INCORRECT_DATA;
    }
    if (car->price < 1 || car->price > MAX_PRICE)
        return INCORRECT_DATA;

    clear_buf(stdin);
    printf(IN_COLOR_MSG);
    if (get_str(stdin, car->color, COLOR_LEN + 1, NEW_SEP))
        return INCORRECT_DATA;

    printf(IN_COND_MSG);
    if (fscanf(stdin, "%d", &(car->condition)) != 1)
    {
        clear_buf(stdin);
        return INCORRECT_DATA;
    }
    if (car->condition != 1 &&
    car->condition != 0)
        return INCORRECT_DATA;

    if (car->condition == 0)
    {
        printf(IN_GUAR_MSG);
        if (fscanf(stdin, "%d", &(car->add_info.guarantee)) != 1)
        {
            clear_buf(stdin);
            return INCORRECT_DATA;
        }
        if (car->add_info.guarantee < 0 ||
        car->add_info.guarantee > MAX_GUAR)
            return INCORRECT_DATA;
    }
    else if (car->condition == 1)
    {
        printf(IN_YEAR_MSG);
        if (fscanf(stdin, "%d", &(car->add_info.old_car.year)) != 1)
        {
            clear_buf(stdin);
            return INCORRECT_DATA;
        }
        if (car->add_info.old_car.year < 1 ||
        car->add_info.old_car.year > MAX_YEAR)
            return INCORRECT_DATA;

        printf(IN_MIL_MSG);
        if (fscanf(stdin, "%d", &(car->add_info.old_car.mileage)) != 1)
        {
            clear_buf(stdin);
            return INCORRECT_DATA;
        }
        if (car->add_info.old_car.mileage < 1 ||
        car->add_info.old_car.mileage > MAX_MIL)
            return INCORRECT_DATA;

        printf(IN_REP_MSG);
        if (fscanf(stdin, "%d", &(car->add_info.old_car.number_of_repairs)) != 1)
        {
            clear_buf(stdin);
            return INCORRECT_DATA;
        }
        if (car->add_info.old_car.number_of_repairs < 0 ||
        car->add_info.old_car.number_of_repairs > MAX_REP)
            return INCORRECT_DATA;

        printf(IN_OWN);
        if (fscanf(stdin, "%d", &(car->add_info.old_car.number_of_owners)) != 1)
        {
            clear_buf(stdin);
            return INCORRECT_DATA;
        }
        if (car->add_info.old_car.number_of_owners < 1 ||
        car->add_info.old_car.number_of_owners > MAX_OWN)
            return INCORRECT_DATA;
    }
    else
        return INCORRECT_DATA;

    char ans;


    printf(ADD_IN_FILE_MSG);
    fscanf(stdin, "\n%c", &ans);
    if (ans == 'y')
        write_in_file(f, *car, *count);

    ++(*count);

    return SUCCESS;
}


void deep_cpy(void *dst, void *base, int count, int size)
{
    for (int i = 0; i < count; ++i)
    {
        char *d = (char *) dst + i * size;
        char *b = (char *) base + i * size;


        for (int j = 0; j < size; ++j)
            *(d++) = *(b++);
    }
}


void print_keys(help_table index_table[],int count)
{
    draw_name(KEY_TABLE_NAME, KEY_TABLE_WIDTH);

    for (int i = 0; i < count; ++i)
    {
        printf("|%*d|%*d|%*d|\n",NUM_LEN, i + 1, INDEX_LEN, 
        index_table[i].index, PRICE_LEN, index_table[i].price);

        draw_line(KEY_TABLE_WIDTH);
    }
}


void transpose_at_the_end(void *cars, int ind, int size, int *count)
{   
    char buf;

    for (; ind < *count - 1; ++ind)
    {
        char *p1 = ((char *) cars) + size * ind;
        char *p2 = ((char *) cars) + size * (ind + 1);


        for (int j = 0; j < size; ++j)
        {
            buf = *p1;
            *(p1++) = *p2;
            *(p2++) = buf;
        }
    }
}


int delete_cars(car_info cars[], help_table inds[], int *count)
{
    int price;


    printf(IN_DEL_MSG);
    if (fscanf(stdin, "%d", &price) != 1 || price < 0 || price > MAX_PRICE)
    {
        clear_buf(stdin);
        return INCORRECT_PRICE;
    }

    for (int i = 0; i < *count; ++i)
        if (cars[i].price == price)
        {
            for (int j = 0; j < *count; ++j)
            {
                if (inds[j].index == i)
                {
                    transpose_at_the_end(inds, j, sizeof(help_table), count);
                    break;
                }
            }

            transpose_at_the_end(cars, i, sizeof(car_info), count);
            --(*count);
        }

    return SUCCESS;
}


void print_cars_using_keys(car_info cars[], help_table inds[], int count)
{
    draw_name(TABLE_NAME, TABLE_WIDTH);

    for (int i = 0; i < count; ++i)
    {
        int ind = inds[i].index;


        if (cars[ind].condition)
            printf("|%*s|%*s|%*d|%*s|%*d|%*c|%*d|%*d|%*d|%*d|\n",
            MODEL_LEN, cars[ind].model, COUNTRY_LEN, cars[ind].country,
            PRICE_LEN, cars[ind].price, COLOR_LEN, cars[ind].color,
            CONDITION_LEN, cars[ind].condition, GUAR_LEN, EMPTY, 
            YEAR_LEN, cars[ind].add_info.old_car.year, 
            MIL_LEN, cars[ind].add_info.old_car.mileage, REP_LEN,
            cars[ind].add_info.old_car.number_of_repairs,
            OWN_LEN, cars[ind].add_info.old_car.number_of_owners);
        else
            print_car(cars[ind]);

        draw_line(TABLE_WIDTH);
    }
}


void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
{
    char *p_end = (char *) base + nmemb * size;
    char temp;

    size_t i = 0;


    for (char *pi_cur = (char *) base; pi_cur != p_end; pi_cur += 2 * size, ++i)
    {
        size_t count = 0;


        if (nmemb <= i)
            break;

        for (size_t j = i; j < nmemb - (1 + i); ++j)
        {
            char *p1 = (char *) base + size * j;
            char *p2 = (char *) base + size * (j + 1);


            if (compar((void *) p1, (void *) p2) > 0)
            {
                ++count;
                for (size_t elem = 0; elem < size; ++elem)
                {
                    temp = *p1;
                    *(p1++) = *p2;
                    *(p2++) = temp;
                }
            }
        }
        if (!count)
            break;
        count = 0;

        for (size_t j = nmemb - i - 1; j > i; --j)
        {
            char *p1 = (char *) base + size * j;
            char *p2 = (char *) base + size * (j - 1);


            if (compar((void *) p1, (void *) p2) < 0)
            {
                ++count;
                for (size_t elem = 0; elem < size; ++elem)
                {
                    temp = *p1;
                    *(p1++) = *p2;
                    *(p2++) = temp;
                }
            }
        }
        if (!count)
            break;
    }
}


void restore_key_table(help_table keys[], car_info cars[], int count)
{
    for (int i = 0; i < count; ++i)
    {
        keys[i].index = i;
        keys[i].price = cars[i].price;
    }
}


void get_measures(measurement_table table[], car_info cars[], help_table inds[], int count)
{
    car_info cur_table[RECORDS_COUNT] = { 0 };

    help_table cur_keys[RECORDS_COUNT] = { 0 };
    
    long long unsigned beg, end;


    deep_cpy(cur_table, cars, count, sizeof(car_info));

    // Table_slow

    beg = milliseconds_now();
    mysort(&cur_table, count, sizeof(car_info), compare_prices);
    end = milliseconds_now();

    table[0].time = end - beg;
    table[0].mem = sizeof(car_info) * count;

    deep_cpy(cur_table, cars, count, sizeof(car_info));

    // Table_quick

    beg = milliseconds_now();
    qsort(&cur_table, count, sizeof(car_info), compare_prices);
    end = milliseconds_now();

    table[1].time = end - beg;
    table[1].mem = sizeof(car_info) * count;

    deep_cpy(cur_keys, inds, count, sizeof(help_table));

    // Key_slow

    beg = milliseconds_now();
    mysort(&cur_keys, count, sizeof(help_table), key_compare_prices);
    end = milliseconds_now();

    table[2].time = end - beg;
    table[2].mem = (sizeof(car_info) + sizeof(help_table)) * count;

    deep_cpy(cur_keys, inds, count, sizeof(help_table));

    // Key_quick

    beg = milliseconds_now();
    qsort(&cur_keys, count, sizeof(help_table), key_compare_prices);
    end = milliseconds_now();

    table[3].time = end - beg;
    table[3].mem = (sizeof(car_info) + sizeof(help_table)) * count;
}


void print_measures(measurement_table measures[])
{
    draw_name(MEASURE_TABLE_NAME, MEASURE_TABLE_WIDTH);

    printf("%*s|%*llu|%*llu|%*llu|%*llu|\n", TIME_MEM_LEN, "TIME",
    SLOW_LEN, measures[0].time, QUICK_LEN, measures[1].time,
    SLOW_LEN, measures[2].time, QUICK_LEN, measures[3].time);
    draw_line(MEASURE_TABLE_WIDTH);
    printf("%*s|%*d|%*d|%*d|%*d|\n", TIME_MEM_LEN, "MEMORY", SLOW_LEN,
    measures[0].mem, QUICK_LEN, measures[1].mem, SLOW_LEN,
    measures[2].mem, QUICK_LEN, measures[3].mem);
    draw_line(MEASURE_TABLE_WIDTH);
}


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
                restore_key_table(index_table, table_cars, count);
                break;
            }
        }
    }

    fclose(f);    

    return SUCCESS;
}
