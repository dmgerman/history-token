macro_line|#ifndef _ASM_VSYSCALL32_H
DECL|macro|_ASM_VSYSCALL32_H
mdefine_line|#define _ASM_VSYSCALL32_H 1
multiline_comment|/* Values need to match arch/x86_64/ia32/vsyscall.lds */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|VSYSCALL32_BASE
mdefine_line|#define VSYSCALL32_BASE 0xffffe000
DECL|macro|VSYSCALL32_SYSEXIT
mdefine_line|#define VSYSCALL32_SYSEXIT (VSYSCALL32_BASE + 0x410)
macro_line|#else
DECL|macro|VSYSCALL32_BASE
mdefine_line|#define VSYSCALL32_BASE 0xffffe000UL
DECL|macro|VSYSCALL32_END
mdefine_line|#define VSYSCALL32_END (VSYSCALL32_BASE + PAGE_SIZE)
DECL|macro|VSYSCALL32_EHDR
mdefine_line|#define VSYSCALL32_EHDR ((const struct elf32_hdr *) VSYSCALL32_BASE)
DECL|macro|VSYSCALL32_VSYSCALL
mdefine_line|#define VSYSCALL32_VSYSCALL ((void *)VSYSCALL32_BASE + 0x400) 
DECL|macro|VSYSCALL32_SYSEXIT
mdefine_line|#define VSYSCALL32_SYSEXIT ((void *)VSYSCALL32_BASE + 0x410)
DECL|macro|VSYSCALL32_SIGRETURN
mdefine_line|#define VSYSCALL32_SIGRETURN ((void __user *)VSYSCALL32_BASE + 0x500) 
DECL|macro|VSYSCALL32_RTSIGRETURN
mdefine_line|#define VSYSCALL32_RTSIGRETURN ((void __user *)VSYSCALL32_BASE + 0x600) 
macro_line|#endif
macro_line|#endif
eof
