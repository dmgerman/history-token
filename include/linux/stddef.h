macro_line|#ifndef _LINUX_STDDEF_H
DECL|macro|_LINUX_STDDEF_H
mdefine_line|#define _LINUX_STDDEF_H
DECL|macro|NULL
macro_line|#undef NULL
macro_line|#if defined(__cplusplus)
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#else
DECL|macro|NULL
mdefine_line|#define NULL ((void *)0)
macro_line|#endif
DECL|macro|offsetof
macro_line|#undef offsetof
DECL|macro|offsetof
mdefine_line|#define offsetof(TYPE, MEMBER) ((size_t) &amp;((TYPE *)0)-&gt;MEMBER)
macro_line|#endif
eof
