multiline_comment|/* $Id: namei.h,v 1.2 2001/07/04 09:08:13 ak Exp $&n; * linux/include/asm-i386/namei.h&n; *&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __X8664_NAMEI_H
DECL|macro|__X8664_NAMEI_H
mdefine_line|#define __X8664_NAMEI_H
multiline_comment|/* This dummy routine maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|__emul_prefix
mdefine_line|#define __emul_prefix() NULL
macro_line|#endif
eof
