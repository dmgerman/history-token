macro_line|#ifndef __ASM_LINKAGE_H
DECL|macro|__ASM_LINKAGE_H
mdefine_line|#define __ASM_LINKAGE_H
DECL|macro|asmlinkage
mdefine_line|#define asmlinkage CPP_ASMLINKAGE __attribute__((regparm(0)))
DECL|macro|FASTCALL
mdefine_line|#define FASTCALL(x)&t;x __attribute__((regparm(3)))
DECL|macro|fastcall
mdefine_line|#define fastcall&t;__attribute__((regparm(3)))
macro_line|#ifdef CONFIG_REGPARM
DECL|macro|prevent_tail_call
macro_line|# define prevent_tail_call(ret) __asm__ (&quot;&quot; : &quot;=r&quot; (ret) : &quot;0&quot; (ret))
macro_line|#endif
macro_line|#ifdef CONFIG_X86_ALIGNMENT_16
DECL|macro|__ALIGN
mdefine_line|#define __ALIGN .align 16,0x90
DECL|macro|__ALIGN_STR
mdefine_line|#define __ALIGN_STR &quot;.align 16,0x90&quot;
macro_line|#endif
macro_line|#endif
eof
