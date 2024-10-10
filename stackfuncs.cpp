#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "global.h"
#include "stackfuncs.h"
#include "checks.h"

void StackCtor(struct stack_t *stk)
{
    assert(stk);

    stk->output = fopen(DUMP_FILE, "w");

    #ifdef DEBUG
        stk->canary1 = CANARY;
        stk->canary2 = CANARY;
    #endif
    //printf("canary1 = %lg, canary2 = %lg\n", stk->canary1, stk->canary2);

    stk->size = 0;
    stk->error_code = NO_ERRORS;
    stk->capacity = CAPACITY;
    stk->data = (stackelem_t*) calloc(stk->capacity + NUM_CANARIES_BUF, sizeof(double)) + NUM_CANARIES_IN_LEFT;

    FillingDataPoison(stk->data, stk->capacity - stk->size);

    //printf("canary1 = %lg, canary2 = %lg\n", stk->canary1, stk->canary2);
    stk->data[-1] = CANARY;
    stk->data[stk->capacity] = CANARY;

    assert(stk->data);
    assert(stk->capacity);

    STACK_CHECK(stk);
}

void StackDtor(struct stack_t *stk)
{
    assert(stk);
    assert(stk->data);

    stk->capacity = 0;

    stk->size = 0;

    fclose(stk->output);
    free(stk->data - NUM_CANARIES_IN_LEFT);
}

void FillingDataPoison(stackelem_t *data, int num_el_poison)
{
    for (int i = 0; i <= num_el_poison; i++)
    {
        data[i] = POISON;
    }
}

void StackPush(struct stack_t *stk, stackelem_t elem)
{
    assert(stk);
    assert(stk->data);
    STACK_CHECK(stk);

    int pop_or_push = PUSH;
    ResizeIf(stk, pop_or_push);

    stk->data[stk->size] = elem;
    stk->size++;
    printf("cap = %d, size = %d,\n", stk->capacity, stk->size);
    printf("elem = %lg\n", stk->data[stk->size]);

    assert(stk->capacity);
    assert(stk->size);

    STACK_CHECK(stk);

}

stackelem_t StackPop(struct stack_t *stk)
{
    STACK_CHECK(stk);
    stackelem_t discared_elem = stk->data[stk->size];
    stk->data[stk->size] = POISON;

    int pop_or_push = POP;
    ResizeIf(stk, pop_or_push);

    stk->size--;

    STACK_CHECK(stk);

    return discared_elem;
}

void ResizeIf(struct stack_t *stk, int pop_or_push)
{
    printf("pop_or_push = %d\n", pop_or_push);
    if (pop_or_push == PUSH && stk->size == stk->capacity)
    {
        stk->data[stk->capacity] = POISON;
        stk->capacity = stk->capacity * CAPAC_RESIZE;
        stk->data = (stackelem_t*) realloc(stk->data - NUM_CANARIES_IN_LEFT, (stk->capacity + NUM_CANARIES_BUF) * sizeof(stackelem_t)) + NUM_CANARIES_IN_LEFT;

        FillingDataPoison(stk->data + stk->size, stk->capacity - stk->size);

        stk->data[stk->capacity] = CANARY;

        stk->size--;

        printf("push cap = %d\n", stk->capacity);
    }

    if (pop_or_push == POP && stk->size * CAPAC_RESIZE + CAPAC_SHIFT < stk->capacity)
    {
        stk->capacity = stk->capacity / CAPAC_RESIZE;

        stk->data = (stackelem_t*) realloc(stk->data - NUM_CANARIES_IN_LEFT, (stk->capacity + NUM_CANARIES_BUF) * sizeof(stackelem_t)) + NUM_CANARIES_IN_LEFT;

        stk->data[stk->capacity] = CANARY;

        printf("pop cap = %d\n", stk->capacity);
    }
}
