macro_line|#ifndef LOAD_OFFSET
DECL|macro|LOAD_OFFSET
mdefine_line|#define LOAD_OFFSET 0
macro_line|#endif
macro_line|#ifndef VMLINUX_SYMBOL
DECL|macro|VMLINUX_SYMBOL
mdefine_line|#define VMLINUX_SYMBOL(_sym_) _sym_
macro_line|#endif
DECL|macro|RODATA
mdefine_line|#define RODATA&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.rodata           : AT(ADDR(.rodata) - LOAD_OFFSET) {&t;&t;&bslash;&n;&t;&t;*(.rodata) *(.rodata.*)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*(__vermagic)&t;&t;/* Kernel version magic */&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.rodata1          : AT(ADDR(.rodata1) - LOAD_OFFSET) {&t;&t;&bslash;&n;&t;&t;*(.rodata1)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Kernel symbol table: Normal symbols */&t;&t;&t;&bslash;&n;&t;__ksymtab         : AT(ADDR(__ksymtab) - LOAD_OFFSET) {&t;&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__start___ksymtab) = .;&t;&t;&t;&bslash;&n;&t;&t;*(__ksymtab)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__stop___ksymtab) = .;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Kernel symbol table: GPL-only symbols */&t;&t;&t;&bslash;&n;&t;__ksymtab_gpl     : AT(ADDR(__ksymtab_gpl) - LOAD_OFFSET) {&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__start___ksymtab_gpl) = .;&t;&t;&bslash;&n;&t;&t;*(__ksymtab_gpl)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__stop___ksymtab_gpl) = .;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Kernel symbol table: Normal symbols */&t;&t;&t;&bslash;&n;&t;__kcrctab         : AT(ADDR(__kcrctab) - LOAD_OFFSET) {&t;&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__start___kcrctab) = .;&t;&t;&t;&bslash;&n;&t;&t;*(__kcrctab)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__stop___kcrctab) = .;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Kernel symbol table: GPL-only symbols */&t;&t;&t;&bslash;&n;&t;__kcrctab_gpl     : AT(ADDR(__kcrctab_gpl) - LOAD_OFFSET) {&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__start___kcrctab_gpl) = .;&t;&t;&bslash;&n;&t;&t;*(__kcrctab_gpl)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__stop___kcrctab_gpl) = .;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Kernel symbol table: strings */&t;&t;&t;&t;&bslash;&n;        __ksymtab_strings : AT(ADDR(__ksymtab_strings) - LOAD_OFFSET) {&t;&bslash;&n;&t;&t;*(__ksymtab_strings)&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|SECURITY_INIT
mdefine_line|#define SECURITY_INIT&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.security_initcall.init : {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__security_initcall_start) = .;&t;&t;&bslash;&n;&t;&t;*(.security_initcall.init) &t;&t;&t;&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__security_initcall_end) = .;&t;&t;&bslash;&n;&t;}
DECL|macro|SCHED_TEXT
mdefine_line|#define SCHED_TEXT&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__sched_text_start) = .;&t;&t;&t;&bslash;&n;&t;&t;*(.sched.text)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;VMLINUX_SYMBOL(__sched_text_end) = .;
eof
