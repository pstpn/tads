# Data types and structures

Eight labs in C, each implementing a structure by hand and then measuring what that choice
costs in time and memory. Sources of every lab live in `Проект` and the report with the
measurements in `Отчет`.

| Lab | Topic |
|-----|-------|
| [lab_01](lab_01) | Division of real numbers in long arithmetic |
| [lab_02](lab_02) | Data tables and joins, plain sorting against an accelerated one |
| [lab_03](lab_03) | Sparse matrix algorithms against the dense equivalents, over varying size and sparsity |
| [lab_04](lab_04) | A stack on an array and on a linked list |
| [lab_05](lab_05) | A queue on an array and on a linked list, with a simulation of a real process |
| [lab_06](lab_06) | A binary tree, with search cost measured against the degree of branching |
| [lab_07](lab_07) | A hash table and a balanced tree against a plain binary search tree |
| [lab_08](lab_08) | Graphs and the longest simple path |

## Building

Every lab from the second one on is built by its own makefile, while the first one carries
build scripts instead.

```bash
cd lab_05/Проект && make
```

