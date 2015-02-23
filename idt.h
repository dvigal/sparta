#ifndef H_IDT
#define H_IDT

struct idt_struct {
  unsigned short base_low;
  unsigned short selector;
  unsigned char reserved;
  unsigned char flags;
  unsigned short base_high;
} __attribute__((packed));
typedef struct idt_struct idt_t;

struct idt_r_struct {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));
typedef struct idt_r_struct idtr_t;

void init_idt();
void load_idtr(idtr_t *ptr);
void save_idtr(idtr_t *ptr);
void set_idt_gate(unsigned char num, unsigned int base, unsigned short selector, unsigned char flags);

#endif