#ifndef ___MY_MSGS___
#define ___MY_MSGS___


#define INFO_MSG "\n- Формат входных данных: пункт меню (от 0 до 6)\n\n\
- Операции, производимые программой: указаны с пунктах меню\n\n\
- Формат выходных данных: экземпляр сбалансированного дерева и хеш-таблица\n\n"
#define INPUT_ELEM_MSG "\nВведите слово, которое Вы хотите добавить в хеш-таблицу (до 15 символов): "
#define INPUT_FIND_INDEX_MSG "\nВведите индекс элемента, который Вы хотите найти: "
#define INPUT_FILE_TREE_NODES_COUNT_MSG "\nВведите желаемое количество элементов в дереве: "
#define INPUT_DATE_FILE_TREE_MSG "\nВведите дату, до которой произвести удаление всех файлов (в виде \"num.month.year\"): "
#define INPUT_DETOUR_TYPE_MSG "\nВведите желаемый тип обхода:\n1 -- Префиксный\n2 -- Инфиксный\n3 -- Постфиксный\n: "
#define ELEM_NOT_FOUND_MSG "\n%sЭлемент с таким индексом не был найден! Попробуйте другой.%s\n"
#define EMPTY_TREE_MSG "\n%sДерево пусто. Сначала добавьте элементы!%s\n"
#define DEL_ELEM_MSG "\n%sЭлемент успешно удален!%s\n"
#define SUCCESSFULLY_DEL_MSG "\n%sУдаленный элемент: \"%d\"\n\n\
Адрес освобожденной ячейки памяти в узла дерева: %p%s\n"
#define NODE_INFO_MSG "\
|%sINDEX: %s%*d    %s|%sVALUE: %s%*c    %s|%sADDRESS: %s%*p%s|\
\n-------------------------------------------------------\
\n|LEFT CHILD:   |INDEX: %s%*d    %s|VALUE: %s%*c       %s|\
\n|RIGHT CHILD:  |INDEX: %s%*d    %s|VALUE: %s%*c       %s|\n"
#define SUCCESSFULLY_ADD_MSG "\n%sДобавление элемента произведено успешно%s\n"
#define ERR_GET_DATE_MSG "\n%sНе удалось получить корректную дату. Попробуйте снова.%s\n"
#define ERR_FILE_TREE_NODES_COUNT_MSG "\n%sНекорректное количество! Попробуйте снова.%s\n"
#define ERR_ALLOC_MSG "\n%sНе удалось выделить память. Попробуйте снова.%s\n\n"
#define ERR_CODE_MSG "\n%sНекорректный код. Попробуйте снова.%s\n\n"
#define ERR_READING_STDIN_MSG "\n%sНе удалось получить элемент. Попробуйте снова.%s\n\n"
#define ERR_TREE_IS_EMPTY_MSG "\n%sДерево пустое. Сначала добавьте элементы в него и попробуйте снова.%s\n\n"
#define ERR_MEASURES_MSG "\n%sНе удалось произвести замерный эксперимент. Попробуйте снова.%s\n\n"
#define MENU_MSG  "\n\
1  --  Вывести сбалансированное дерево зарезервированных слов\n\
2  --  Вывести хеш-таблицу для зарезервированных слов\n\
3  --  Получить подсказку по введенному слову\n\
4  --  Добавить подсказку по введенному слову в хэш-таблицу\n\
5  --  Сравнить время поиска и кол-во сравнений для различных размерностей таблицы\n\
6  --  Сравнить эффективность добавления ключа в таблицу для различной степени заполненности таблицы\n\
0  --  Выход\n: "
// #define MEASURE_TABLE_MSG "%s| BRANCHING (%%) | TIME / MEM (1000 elems, mcs) | TIME / MEM (10000 elems, mcs) |
// TIME / MEM (25000 elems, mcs) | TIME / MEM (50000 elems, mcs) | TIME / MEM (100000 elems, mcs) |%s\n"

#endif // ___MY_MSGS___
