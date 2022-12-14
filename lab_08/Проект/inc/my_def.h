#ifndef ___MY_DEF___
#define ___MY_DEF___

#define MENU_LEN 2

#define TRUE 1
#define FALSE 0

#define MAX_GRAPH_FILENAME_LEN 50

#define MAX_OUT_ROAD 1024

#define GRAPH_FILENAME "graph.dot"
#define OUT_GRAPH_FILENAME "graph.png"

#define GRAPH_NAME "CURRENT_GRAPH"

#define MAKE_GRAPH_COMMAND "circo -Tpng "GRAPH_FILENAME" -o "OUT_GRAPH_FILENAME
#define OPEN_GRAPH_PNG_COMMAND "xdg-open "OUT_GRAPH_FILENAME

#define MAX_ROAD_GRAPH_FILENAME "max_road_graph.dot"
#define MAX_ROAD_OUT_GRAPH_FILENAME "max_road_graph.png"

#define BRANCH_COLOR "green"

#define MAX_ROAD_GRAPH_NAME "MAX_ROAD_GRAPH"

#define MAKE_MAX_ROAD_GRAPH_COMMAND "circo -Tpng "MAX_ROAD_GRAPH_FILENAME" -o "MAX_ROAD_OUT_GRAPH_FILENAME
#define OPEN_MAX_ROAD_GRAPH_PNG_COMMAND "xdg-open "MAX_ROAD_OUT_GRAPH_FILENAME

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define PURPLE "\033[1;35m"
#define BLUE "\033[1;36m"

#endif // ___MY_DEF___