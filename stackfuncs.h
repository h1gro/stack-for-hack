#ifndef STACK_FUNCS
#define STACK_FUNCS

void StackCtor(struct stack_t *stk);
void StackDtor(struct stack_t *stk);
void FillingDataPoison(stackelem_t *data, int num_el_poison);
void StackPush(struct stack_t *stk, stackelem_t elem);
void ResizeIf(struct stack_t *stk, int is_pop_or_push);

stackelem_t StackPop(struct stack_t *stk);

#endif
