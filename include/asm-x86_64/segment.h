macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
DECL|macro|__KERNEL_CS
mdefine_line|#define __KERNEL_CS&t;0x10
DECL|macro|__KERNEL_DS
mdefine_line|#define __KERNEL_DS&t;0x18
multiline_comment|/* &n; * we cannot use the same code segment descriptor for user and kernel&n; * even not in the long flat model, because of different DPL /kkeil &n; * The segment offset needs to contain a RPL. Grr. -AK&n; * GDT layout to get 64bit syscall right (sysret hardcodes gdt offsets) &n; */
DECL|macro|__USER32_CS
mdefine_line|#define __USER32_CS   0x23   /* 4*8+3 */ 
DECL|macro|__USER_DS
mdefine_line|#define __USER_DS     0x2b   /* 5*8+3 */ 
DECL|macro|__USER_CS
mdefine_line|#define __USER_CS     0x33   /* 6*8+3 */ 
DECL|macro|__USER32_DS
mdefine_line|#define __USER32_DS&t;__USER_DS 
macro_line|#endif
eof
