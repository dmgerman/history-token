multiline_comment|/* $Id: namei.h,v 1.4 1998/10/28 08:13:33 jj Exp $&n; * linux/include/asm-ppc/namei.h&n; * Adapted from linux/include/asm-alpha/namei.h&n; *&n; * Included from linux/fs/namei.c&n; */
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
