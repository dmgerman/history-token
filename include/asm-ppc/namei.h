multiline_comment|/*&n; * include/asm-ppc/namei.h&n; * Adapted from include/asm-alpha/namei.h&n; *&n; * Included from fs/namei.c&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_NAMEI_H
DECL|macro|__PPC_NAMEI_H
mdefine_line|#define __PPC_NAMEI_H
multiline_comment|/* This dummy routine maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|__emul_prefix
mdefine_line|#define __emul_prefix() NULL
macro_line|#endif /* __PPC_NAMEI_H */
macro_line|#endif /* __KERNEL__ */
eof
