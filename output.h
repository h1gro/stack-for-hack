#ifndef OUTPUT
#define OUTPUT

void StackErrorOutput(struct stack_t *stk);
void StackDump(struct stack_t *stk, const char* func, const char* file, int line, int dump_call);

#endif

