macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
multiline_comment|/*&n; * The layout of the per-CPU GDT under Linux:&n; *&n; *   0 - null&n; *   1 - reserved&n; *   2 - reserved&n; *   3 - reserved&n; *&n; *   4 - unused&t;&t;&t;&lt;==== new cacheline&n; *   5 - unused&n; *&n; *  ------- start of TLS (Thread-Local Storage) segments:&n; *&n; *   6 - TLS segment #1&t;&t;&t;[ glibc&squot;s TLS segment ]&n; *   7 - TLS segment #2&t;&t;&t;[ Wine&squot;s %fs Win32 segment ]&n; *   8 - TLS segment #3&n; *   9 - reserved&n; *  10 - reserved&n; *  11 - reserved&n; *&n; *  ------- start of kernel segments:&n; *&n; *  12 - kernel code segment&t;&t;&lt;==== new cacheline&n; *  13 - kernel data segment&n; *  14 - default user CS&n; *  15 - default user DS&n; *  16 - TSS&n; *  17 - LDT&n; *  18 - PNPBIOS support (16-&gt;32 gate)&n; *  19 - PNPBIOS support&n; *  20 - PNPBIOS support&n; *  21 - PNPBIOS support&n; *  22 - PNPBIOS support&n; *  23 - APM BIOS support&n; *  24 - APM BIOS support&n; *  25 - APM BIOS support &n; */
DECL|macro|GDT_ENTRY_TLS_ENTRIES
mdefine_line|#define GDT_ENTRY_TLS_ENTRIES&t;3
DECL|macro|GDT_ENTRY_TLS_MIN
mdefine_line|#define GDT_ENTRY_TLS_MIN&t;6
DECL|macro|GDT_ENTRY_TLS_MAX
mdefine_line|#define GDT_ENTRY_TLS_MAX &t;(GDT_ENTRY_TLS_MIN + GDT_ENTRY_TLS_ENTRIES - 1)
DECL|macro|TLS_SIZE
mdefine_line|#define TLS_SIZE (GDT_ENTRY_TLS_ENTRIES * 8)
DECL|macro|GDT_ENTRY_DEFAULT_USER_CS
mdefine_line|#define GDT_ENTRY_DEFAULT_USER_CS&t;14
DECL|macro|__USER_CS
mdefine_line|#define __USER_CS (GDT_ENTRY_DEFAULT_USER_CS * 8 + 3)
DECL|macro|GDT_ENTRY_DEFAULT_USER_DS
mdefine_line|#define GDT_ENTRY_DEFAULT_USER_DS&t;15
DECL|macro|__USER_DS
mdefine_line|#define __USER_DS (GDT_ENTRY_DEFAULT_USER_DS * 8 + 3)
DECL|macro|GDT_ENTRY_KERNEL_BASE
mdefine_line|#define GDT_ENTRY_KERNEL_BASE&t;12
DECL|macro|GDT_ENTRY_KERNEL_CS
mdefine_line|#define GDT_ENTRY_KERNEL_CS&t;&t;(GDT_ENTRY_KERNEL_BASE + 0)
DECL|macro|__KERNEL_CS
mdefine_line|#define __KERNEL_CS (GDT_ENTRY_KERNEL_CS * 8)
DECL|macro|GDT_ENTRY_KERNEL_DS
mdefine_line|#define GDT_ENTRY_KERNEL_DS&t;&t;(GDT_ENTRY_KERNEL_BASE + 1)
DECL|macro|__KERNEL_DS
mdefine_line|#define __KERNEL_DS (GDT_ENTRY_KERNEL_DS * 8)
DECL|macro|GDT_ENTRY_TSS
mdefine_line|#define GDT_ENTRY_TSS&t;&t;&t;(GDT_ENTRY_KERNEL_BASE + 4)
DECL|macro|GDT_ENTRY_LDT
mdefine_line|#define GDT_ENTRY_LDT&t;&t;&t;(GDT_ENTRY_KERNEL_BASE + 5)
DECL|macro|GDT_ENTRY_PNPBIOS_BASE
mdefine_line|#define GDT_ENTRY_PNPBIOS_BASE&t;&t;(GDT_ENTRY_KERNEL_BASE + 6)
DECL|macro|GDT_ENTRY_APMBIOS_BASE
mdefine_line|#define GDT_ENTRY_APMBIOS_BASE&t;&t;(GDT_ENTRY_KERNEL_BASE + 11)
multiline_comment|/*&n; * The GDT has 23 entries but we pad it to cacheline boundary:&n; */
DECL|macro|GDT_ENTRIES
mdefine_line|#define GDT_ENTRIES 24
DECL|macro|GDT_SIZE
mdefine_line|#define GDT_SIZE (GDT_ENTRIES * 8)
multiline_comment|/*&n; * The interrupt descriptor table has room for 256 idt&squot;s,&n; * the global descriptor table is dependent on the number&n; * of tasks we can have..&n; */
DECL|macro|IDT_ENTRIES
mdefine_line|#define IDT_ENTRIES 256
macro_line|#endif
eof
