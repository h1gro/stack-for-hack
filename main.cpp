#include <TXLib.h>
#include <stdlib.h>

#include "global.h"
#include "stackfuncs.h"
#include "output.h"

int main()
{
    struct stack_t stk = {INIT(CANARY, stk)};

    StackCtor(&stk);

    StackPush(&stk, 1);
    StackPush(&stk, 2);
    StackPush(&stk, 3);
    StackPush(&stk, 4);
    StackPush(&stk, 5);
    StackPop(&stk);

    int dump_call = INFO_PRINT;
    StackDump(&stk, __func__, __FILE__, __LINE__, dump_call);

    StackDtor(&stk);

    return 0;
}
