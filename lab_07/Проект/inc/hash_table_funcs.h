#ifndef ___MY_HASH_FUNCS___
#define ___MY_HASH_FUNCS___

#include "my_def.h"
#include "my_types.h"


unsigned int hash_func(const char *str, unsigned int table_len);
void free_hash_table(hash_table_t *hash_table);
void free_list_hash_table(hash_table_t *hash_table);
int fix_collision(hash_table_t **hash_table, keyword_info_t *keyword, int cur_index, int k_count);
int fix_list_collision(hash_table_t **hash_table, list_keyword_info_t *keyword, int cur_index);
int insert_in_hash_table(hash_table_t **hash_table, char *keyword, char *help, int k_count, int table_size);
int insert_in_list_hash_table(hash_table_t **hash_table, char *keyword, char *help, int table_size);
int create_hash_table(hash_table_t **hash_table, char (*keywords)[MAX_KEYWORD_LEN + 1],
                      char (*help)[MAX_HELP_LEN + 1], int k_count, int table_size, int is_list_table);

#endif // ___MY_HASH_FUNCS___