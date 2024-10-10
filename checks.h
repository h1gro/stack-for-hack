#ifndef CHECKS
#define CHECKS

int CheckForErrors(struct stack_t *stk);
int StackCheck(struct stack_t *stk, const char* file, int line, const char* func);

#endif
