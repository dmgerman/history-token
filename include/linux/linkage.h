macro_line|#ifndef _LINUX_LINKAGE_H
DECL|macro|_LINUX_LINKAGE_H
mdefine_line|#define _LINUX_LINKAGE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/linkage.h&gt;
macro_line|#ifdef __cplusplus
DECL|macro|CPP_ASMLINKAGE
mdefine_line|#define CPP_ASMLINKAGE extern &quot;C&quot;
macro_line|#else
DECL|macro|CPP_ASMLINKAGE
mdefine_line|#define CPP_ASMLINKAGE
macro_line|#endif
macro_line|#ifndef asmlinkage
DECL|macro|asmlinkage
mdefine_line|#define asmlinkage CPP_ASMLINKAGE
macro_line|#endif
macro_line|#ifndef prevent_tail_call
DECL|macro|prevent_tail_call
macro_line|# define prevent_tail_call(ret) do { } while (0)
macro_line|#endif
macro_line|#ifndef __ALIGN
DECL|macro|__ALIGN
mdefine_line|#define __ALIGN&t;&t;.align 4,0x90
DECL|macro|__ALIGN_STR
mdefine_line|#define __ALIGN_STR&t;&quot;.align 4,0x90&quot;
macro_line|#endif
macro_line|#ifdef __ASSEMBLY__
DECL|macro|ALIGN
mdefine_line|#define ALIGN __ALIGN
DECL|macro|ALIGN_STR
mdefine_line|#define ALIGN_STR __ALIGN_STR
DECL|macro|ENTRY
mdefine_line|#define ENTRY(name) &bslash;&n;  .globl name; &bslash;&n;  ALIGN; &bslash;&n;  name:
macro_line|#endif
DECL|macro|NORET_TYPE
mdefine_line|#define NORET_TYPE    /**/
DECL|macro|ATTRIB_NORET
mdefine_line|#define ATTRIB_NORET  __attribute__((noreturn))
DECL|macro|NORET_AND
mdefine_line|#define NORET_AND     noreturn,
macro_line|#ifndef FASTCALL
DECL|macro|FASTCALL
mdefine_line|#define FASTCALL(x)&t;x
DECL|macro|fastcall
mdefine_line|#define fastcall
macro_line|#endif
macro_line|#endif
eof
