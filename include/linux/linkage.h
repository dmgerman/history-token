macro_line|#ifndef _LINUX_LINKAGE_H
DECL|macro|_LINUX_LINKAGE_H
mdefine_line|#define _LINUX_LINKAGE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __cplusplus
DECL|macro|CPP_ASMLINKAGE
mdefine_line|#define CPP_ASMLINKAGE extern &quot;C&quot;
macro_line|#else
DECL|macro|CPP_ASMLINKAGE
mdefine_line|#define CPP_ASMLINKAGE
macro_line|#endif
macro_line|#if defined __i386__
DECL|macro|asmlinkage
mdefine_line|#define asmlinkage CPP_ASMLINKAGE __attribute__((regparm(0)))
macro_line|#elif defined __ia64__
DECL|macro|asmlinkage
mdefine_line|#define asmlinkage CPP_ASMLINKAGE __attribute__((syscall_linkage))
macro_line|#else
DECL|macro|asmlinkage
mdefine_line|#define asmlinkage CPP_ASMLINKAGE
macro_line|#endif
macro_line|#ifdef __arm__
DECL|macro|__ALIGN
mdefine_line|#define __ALIGN .align 0
DECL|macro|__ALIGN_STR
mdefine_line|#define __ALIGN_STR &quot;.align 0&quot;
macro_line|#else
macro_line|#ifdef __mc68000__
DECL|macro|__ALIGN
mdefine_line|#define __ALIGN .align 4
DECL|macro|__ALIGN_STR
mdefine_line|#define __ALIGN_STR &quot;.align 4&quot;
macro_line|#else
macro_line|#ifdef __sh__
DECL|macro|__ALIGN
mdefine_line|#define __ALIGN .balign 4
DECL|macro|__ALIGN_STR
mdefine_line|#define __ALIGN_STR &quot;.balign 4&quot;
macro_line|#else
macro_line|#if defined(__i386__) &amp;&amp; defined(CONFIG_X86_ALIGNMENT_16)
DECL|macro|__ALIGN
mdefine_line|#define __ALIGN .align 16,0x90
DECL|macro|__ALIGN_STR
mdefine_line|#define __ALIGN_STR &quot;.align 16,0x90&quot;
macro_line|#else
DECL|macro|__ALIGN
mdefine_line|#define __ALIGN .align 4,0x90
DECL|macro|__ALIGN_STR
mdefine_line|#define __ALIGN_STR &quot;.align 4,0x90&quot;
macro_line|#endif
macro_line|#endif /* __sh__ */
macro_line|#endif /* __mc68000__ */
macro_line|#endif /* __arm__ */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|ALIGN
mdefine_line|#define ALIGN __ALIGN
DECL|macro|ALIGN_STR
mdefine_line|#define ALIGN_STR __ALIGN_STR
DECL|macro|ENTRY
mdefine_line|#define ENTRY(name) &bslash;&n;  .globl name; &bslash;&n;  ALIGN; &bslash;&n;  name:
macro_line|#endif
DECL|macro|NORET_TYPE
macro_line|# define NORET_TYPE    /**/
DECL|macro|ATTRIB_NORET
macro_line|# define ATTRIB_NORET  __attribute__((noreturn))
DECL|macro|NORET_AND
macro_line|# define NORET_AND     noreturn,
macro_line|#ifdef __i386__
DECL|macro|FASTCALL
mdefine_line|#define FASTCALL(x)&t;x __attribute__((regparm(3)))
macro_line|#else
DECL|macro|FASTCALL
mdefine_line|#define FASTCALL(x)&t;x
macro_line|#endif
macro_line|#endif
eof
