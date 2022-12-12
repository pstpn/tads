#ifndef ___MY_DEF___
#define ___MY_DEF___

#define MENU_LEN 6

#define TRUE 1
#define FALSE 0

#define MAX_KEYWORDS_COUNT 500
#define KEYWORDS_COUNT 23
#define MAX_KEYWORD_LEN 15
#define MAX_HELP_LEN 150

#define NEED_RESTRUCT -1

#define TABLE_WIDTH 82
#define INDEX_WIDTH 10
#define KEYWORD_WIDTH MAX_KEYWORD_LEN + 3
#define POINTER_WIDTH 10
#define CHILD_WIDTH 9

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

#define MEAS_COUNT 9
#define MEAS_TABLE_WIDTH 146

#define FIRST_FIELD_WIDTH 8
#define SECOND_FIELD_WIDTH 51

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define PURPLE "\033[1;35m"
#define BLUE "\033[1;36m"

#endif // ___MY_DEF___