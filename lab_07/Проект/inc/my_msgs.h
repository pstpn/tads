#ifndef ___MY_MSGS___
#define ___MY_MSGS___


#define INFO_MSG "\n- Формат входных данных: пункт меню (от 0 до 6)\n\n\
- Операции, производимые программой: указаны с пунктах меню\n\n\
- Формат выходных данных: экземпляр сбалансированного дерева и хеш-таблица\n\n"
#define INPUT_HELP_MSG "\nВведите подсказку для введенного ключевого слова (до 150 символов):\n\n"
#define INPUT_WORD_MSG "\nВведите ключевое слово, которое Вы хотите добавить в хеш-таблицу (до 15 символов): "
#define INPUT_FIND_WORD_MSG "\nВведите ключевое слово, для которого Вы хотите найти подсказку (до 15 символов): "
#define HASH_TABLE_INFO_MSG "\
|%sINDEX: %s%*d    %s|%sKEYWORD: %s%*s       %s|%sADDRESS: %s%*p%s|\n"
#define CHILDS_HASH_TABLE_INFO_MSG "\
|%sPARENT_INDEX: %s%*d    %s|%sKEYWORD: %s%*s       %s|%sADDRESS: %s%*p%s|\n"
#define HELP_MSG "\n%sВведенное слово: \"%s\"\nКоличество сравнений: %d\nПодсказка по данному слову:\n\n%s\"%s\"%s\n"
#define ERR_ALLOC_MSG "\n%sНе удалось выделить память. Попробуйте снова.%s\n\n"
#define ERR_CODE_MSG "\n%sНекорректный код. Попробуйте снова.%s\n\n"
#define ERR_READING_STDIN_MSG "\n%sНе удалось получить элемент. Попробуйте снова.%s\n\n"
#define ERR_FINDIND_MSG "\n%sНе удалось найти подсказку по данному слову. Попробуйте снова.%s\n\n"
#define ERR_MEASURES_MSG "\n%sНе удалось произвести замерный эксперимент. Попробуйте снова.%s\n\n"
#define OPENED_TABLE_MSG "открытое"
#define CLOSED_TABLE_MSG "закрытое"
#define CHANGE_HASH_MSG "\n%sВы сменили тип хеширования на \"%s\"%s\n"
#define MENU_MSG  "\n\
1  --  Вывести сбалансированное дерево зарезервированных слов\n\
2  --  Вывести хеш-таблицу для зарезервированных слов\n\
3  --  Получить подсказку по введенному слову\n\
4  --  Добавить подсказку по введенному слову в хеш-таблицу\n\
5  --  Сравнить время поиска и кол-во сравнений для различных размерностей таблицы\n\
6  --  Изменить тип хеширования (текущий: %s)\n\
0  --  Выход\n: "
#define COUNT_MEASURES_MSG "\n%sКоличество запусков для каждого типа: %d%s\n"
#define MEASURE_TABLE_MSG "%s|  TYPE  | TIME / MEM (10 elems, mcs) / AVG_CMP_COUNT | \
TIME / MEM (50 elems, mcs) / AVG_CMP_COUNT | TIME / MEM (100 elems, mcs) / AVG_CMP_COUNT |%s\n"

#endif // ___MY_MSGS___
