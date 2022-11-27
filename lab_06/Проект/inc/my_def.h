#ifndef ___MY_DEF___
#define ___MY_DEF___

#define MENU_LEN 7

#define TRUE 1
#define FALSE 0

#define TABLE_WIDTH 55

#define INDEX_WIDTH 3
#define VALUE_WIDTH 3
#define POINTER_WIDTH 10
#define CHILD_WIDTH 9

#define MAX_FILENAME_LEN 30

#define MIN_ASCII 97
#define MAX_ASCII 122

#define NULL_STR "NULL"

#define TREE_GRAPH_FILENAME "tree.dot"
#define OUT_TREE_GRAPH_FILENAME "tree.png"

#define IN_FILE_TREE_GRAPH_FILENAME "in_file_tree.dot"
#define OUT_IN_FILE_TREE_GRAPH_FILENAME "in_file_tree.png"

#define OUT_FILE_TREE_GRAPH_FILENAME "out_file_tree.dot"
#define OUT_OUT_FILE_TREE_GRAPH_FILENAME "out_file_tree.png"

#define TREE_NAME "CURRENT_TREE"
#define IN_FILE_TREE_NAME "IN_FILE_TREE"
#define OUT_FILE_TREE_NAME "OUT_FILE_TREE"

#define MAKE_TREE_GRAPH_COMMAND "dot -Tpng tree.dot -o tree.png"
#define OPEN_TREE_PNG_COMMAND "xdg-open tree.png"

#define MAKE_IN_FILE_TREE_GRAPH_COMMAND "dot -Tpng in_file_tree.dot -o in_file_tree.png"
#define OPEN_IN_FILE_TREE_PNG_COMMAND "xdg-open in_file_tree.png"

#define MAKE_OUT_FILE_TREE_GRAPH_COMMAND "dot -Tpng out_file_tree.dot -o out_file_tree.png"
#define OPEN_OUT_FILE_TREE_PNG_COMMAND "xdg-open out_file_tree.png"

#define MEAS_COUNT 25

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define PURPLE "\033[1;35m"
#define BLUE "\033[1;36m"

#endif // ___MY_DEF___