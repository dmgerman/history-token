multiline_comment|/* $Id: namei.h,v 1.1.1.1 1999/03/15 19:41:02 pjlahaie Exp $&n; * linux/include/asm-parisc/namei.h&n; *&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __PARISC_NAMEI_H
DECL|macro|__PARISC_NAMEI_H
mdefine_line|#define __PARISC_NAMEI_H
multiline_comment|/* This dummy routine maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|__emul_prefix
mdefine_line|#define __emul_prefix() NULL
macro_line|#endif /* __PARISC_NAMEI_H */
eof
