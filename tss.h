#ifndef H_TSS
#define H_TSS

struct tss {
  int task_link;
  int esp0;
  int ss0;
  int esp1;
  int ss1;
  int esp2;
  int ss2;
  int cr3;
  int eip;
  int eflags;
  int eax;
  int ecx;
  int edx;
  int ebx;
  int esp;
  int ebp;
  int esi;
  int edi;
  int es;
  int cs;
  int ss;
  int ds;
  int fs;
  int gs;
  int ldt_ss;
  int io_maps;
}__attribute__((packed));
typedef struct tss tss_t;

#endif
