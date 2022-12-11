#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "my_types.h"
#include "tree_funcs.h"
#include "my_err.h"
#include "balance_tree_funcs.h"
#include "graph.h"
#include "hash_table_funcs.h"
#include "tools.h"


unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;
    return val.tv_sec * 1000000ULL + val.tv_usec * 1ULL;
}


int get_measures(measurement_table table[MEAS_COUNT])
{
    int counts[] = { 10, 50, 100 };

    char CPP_KEYWORDS[MAX_KEYWORDS_COUNT][MAX_KEYWORD_LEN + 1] = 
        {
            "case", "bool", "break", "char", "continue", "delete",
            "default", "do", "else", "enum", "export", "extern",
            "true", "false", "for", "goto", "if", "static",
            "or", "typedef", "while", "return", "double",
            "cadse", "bodol", "brdeak", "chard", "contdinue", "deldete",
            "defdault", "ddo", "elsde", "enudm", "expdort", "exdtern",
            "trdue", "falsde", "fdor", "gdoto", "idf", "statdic",
            "odr", "typeddef", "whdile", "retdurn", "doudble",
            "casae", "booal", "braeak", "chaar", "containue", "daelete",
            "defaualt", "dao", "elase", "enaum", "expoart", "extaern",
            "traue", "faalse", "faor", "gotao", "iaf", "staatic",
            "oar", "typedaef", "whaile", "retuarn", "doauble",
            "cahse", "bohol", "brehak", "chhar", "cohntinue", "dehlete",
            "defauhlt", "dho", "elhse", "enhum", "expohrt", "exhtern",
            "truhe", "fahlse", "fohr", "gohto", "hif", "stahtic",
            "ohr", "typehdef", "whihle", "retuhrn", "dhouble",
            "casme", "boml", "brmeak", "chmar", "conmtinue", "delmete",
            "defamult", "dom", "elmse", "enmum", "expmort", "exmtern",
            "trme", "famlse", "fmor", "gomto", "ifm", "smtatic",
            "omr", "typemdef", "whilme", "retmurn", "doumble"
        };

    char CPP_HELP[MAX_KEYWORDS_COUNT][MAX_HELP_LEN + 1] = 
        {
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement",
            "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement", "statement"
        };

    long long unsigned beg, end;


    for (int j = 0; j < 3; ++j)
    {
        tree_node_t *root_node = NULL;

        int f_ind = counts[j] - 2;
        // int f_ind = counts[j] / 2 - 2;

        int stop_finding = FALSE;


        for (int i = 0; i < counts[j]; ++i)
        {
            tree_node_t *c_node = create_node(CPP_KEYWORDS[i]);


            root_node = insert(root_node, c_node);
        }


        beg = microseconds_now();

        for (int k = 0; k < 10000; ++k)
            find_tree_node(root_node, CPP_KEYWORDS[f_ind], &stop_finding);

        end = microseconds_now();

        table[j].time = end - beg;
        table[j].type = 'b';
        table[j].mem = sizeof(tree_node_t) * counts[j] + sizeof(char *) * counts[j];
        table[j].count = counts[j];

        apply(root_node, destroy_node, NULL);
    }

    for (int j = 0; j < 3; ++j)
    {
        int f_ind = counts[j] - 2;
        // int f_ind = counts[j] / 2 - 2;

        int stop_finding = FALSE;

        balance_tree_node_t *root_node = create_keywords_balance_tree(CPP_KEYWORDS, counts[j]);


        beg = microseconds_now();

        for (int k = 0; k < 10000; ++k)
            b_find_tree_node(root_node, CPP_KEYWORDS[f_ind], &stop_finding);

        end = microseconds_now();

        table[3 + j].time = end - beg;
        table[3 + j].type = 'a';
        table[3 + j].mem = sizeof(balance_tree_node_t) * counts[j] + sizeof(char *) * counts[j];
        table[3 + j].count = counts[j];

        b_apply(root_node, b_destroy_node, NULL, FALSE);
    }

    for (int j = 0; j < 3; ++j)
    {
        int f_ind = counts[j] - 2;
        // int f_ind = counts[j] / 2 - 2;

        hash_table_t *hash_table = NULL;

        int is_list_hash_table = TRUE;

        int tmp_size = get_new_table_size(counts[j]);

        int rc = create_hash_table(&hash_table, CPP_KEYWORDS, CPP_HELP, counts[j], tmp_size, is_list_hash_table);
        

        while (rc == NEED_RESTRUCT)
        {
            tmp_size = get_new_table_size(hash_table->size);
            

            free_list_hash_table(hash_table);

            rc = create_hash_table(&hash_table, CPP_KEYWORDS, CPP_HELP, counts[j], tmp_size, is_list_hash_table);
        }


        beg = microseconds_now();

        for (int k = 0; k < 10000; ++k)
            find_list_keyword(hash_table, CPP_KEYWORDS[f_ind]);

        end = microseconds_now();

        table[6 + j].time = end - beg;
        table[6 + j].type = 'h';
        table[6 + j].mem = sizeof(hash_table_t) + sizeof(list_keyword_info_t) * counts[j];
        table[6 + j].count = counts[j];

        free_list_hash_table(hash_table);
    }
    
    return SUCCESS;
}