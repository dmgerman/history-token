macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
DECL|macro|__KERNEL_CS
mdefine_line|#define __KERNEL_CS&t;0x10
DECL|macro|__KERNEL_DS
mdefine_line|#define __KERNEL_DS&t;0x18
DECL|macro|__KERNEL32_CS
mdefine_line|#define __KERNEL32_CS   0x38
multiline_comment|/* &n; * we cannot use the same code segment descriptor for user and kernel&n; * even not in the long flat model, because of different DPL /kkeil &n; * The segment offset needs to contain a RPL. Grr. -AK&n; * GDT layout to get 64bit syscall right (sysret hardcodes gdt offsets) &n; */
DECL|macro|__USER32_CS
mdefine_line|#define __USER32_CS   0x23   /* 4*8+3 */ 
DECL|macro|__USER_DS
mdefine_line|#define __USER_DS     0x2b   /* 5*8+3 */ 
DECL|macro|__USER_CS
mdefine_line|#define __USER_CS     0x33   /* 6*8+3 */ 
DECL|macro|__USER32_DS
mdefine_line|#define __USER32_DS&t;__USER_DS 
DECL|macro|GDT_ENTRY_TLS
mdefine_line|#define GDT_ENTRY_TLS 1
DECL|macro|GDT_ENTRY_TSS
mdefine_line|#define GDT_ENTRY_TSS 8&t;/* needs two entries */
DECL|macro|GDT_ENTRY_LDT
mdefine_line|#define GDT_ENTRY_LDT 10
DECL|macro|GDT_ENTRY_TLS_MIN
mdefine_line|#define GDT_ENTRY_TLS_MIN 11
DECL|macro|GDT_ENTRY_TLS_MAX
mdefine_line|#define GDT_ENTRY_TLS_MAX 13
DECL|macro|GDT_ENTRY_TLS_ENTRIES
mdefine_line|#define GDT_ENTRY_TLS_ENTRIES 3
DECL|macro|IDT_ENTRIES
mdefine_line|#define IDT_ENTRIES 256
DECL|macro|GDT_ENTRIES
mdefine_line|#define GDT_ENTRIES 16
DECL|macro|GDT_SIZE
mdefine_line|#define GDT_SIZE (GDT_ENTRIES * 8)
DECL|macro|TLS_SIZE
mdefine_line|#define TLS_SIZE (GDT_ENTRY_TLS_ENTRIES * 8) 
macro_line|#endif
eof
