#include "shuntpol.h"

void debug(t_sh *num, t_sh *op)
{
    while (num)
    {
        printf("number ---> %c\n", num->sh);
        num = num->next;
    }
    puts("");
    while (op)
    {
        printf("op ---> %c\n", op->sh);
        op = op->next;
    }
}

void remove_node(t_sh **list)
{
    t_sh *node = (*list)->next;
    free(*list);
    *list = node;
}

t_sh *cnode(char sh)
{
    t_sh *node = malloc(sizeof(t_sh));
    if (!node)
        return (NULL);
    node->sh = sh;
    if (sh == '+')
        node->lvl = ADD_LVL;
    else if (sh == '*')
        node->lvl = MULT_LVL;
    else
        node->lvl = -1;
    node->next = NULL;
    return (node);
}

int add_fr(t_sh **list, t_sh *node)
{
    if (!node)
        return (EXIT_FAILURE);
    node->next = *list;
    *list = node;
    return (EXIT_SUCCESS);
}

int shunt_op(t_sh **num, t_sh **op, t_sh *sh)
{
    if (!sh)
        return (EXIT_FAILURE);
    if (*op && (*op)->lvl > sh->lvl
    || (*op) && (*op)->lvl == sh->lvl)
    {
        add_fr(num, cnode((*op)->sh));
        remove_node(op);      
        add_fr(op, sh);
    }
    else
        add_fr(op, sh);
    return (EXIT_SUCCESS);
}

int calculator(t_sh **num, t_sh **op, char *str)
{
    int i = 0;
    while (str[i])
    {
        if (isdigit(str[i]) && add_fr(num, cnode(str[i])))
            return (printf("Error: Memory Allocation Failure\n"), 1);
        else if ((str[i] == '*' || str[i] == '+')
            && shunt_op(num, op, cnode(str[i])))
            return (printf("Error: Memory Allocation Failure\n"), 1);
        // Braces Handlers (TODO)
        i++;
    }
    while (*op)
    {
        add_fr(num, cnode((*op)->sh));
        (*op) = (*op)->next;
    }
}

int main(int argc, char **argv)
{
    if ( argc > 2)
        return (printf("Error: arguments\n"), 1);

    t_sh *num = NULL;
    t_sh *op = NULL;

    if (calculator(&num, &op, argv[1]))
        return (1);
    debug(num, op);
}