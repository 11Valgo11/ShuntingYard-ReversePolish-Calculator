#ifndef SHUNPOL_H
#define SHUNTPOL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

# define MULT_LVL 11
# define ADD_LVL 10

typedef struct s_sh
{
    char sh;
    int lvl;
    struct s_sh *next;
}   t_sh;

#endif