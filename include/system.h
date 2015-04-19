#ifndef H_SYSTEM
#define H_SYSTEM

struct regs_struct {
	unsigned int edi, esi, ebp, esp;
	unsigned int ebx, edx, ecx, eax;
	unsigned int gs, fs, es, ds;
	unsigned int vector, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
}__attribute__((packed));
typedef struct regs_struct regs_t;

extern void init_gdt();
extern void init_idt();
extern void init_isrs();
extern void init_irq();
extern void init_timer(unsigned int hz);

typedef void (*irq_handler_t) (regs_t *);


#define NULL(type) (type*)0

//char HEX_SYMBOL_TABLES[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

#endif