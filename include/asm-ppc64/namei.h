multiline_comment|/* &n; * linux/include/asm-ppc/namei.h&n; * Adapted from linux/include/asm-alpha/namei.h&n; *&n; * Included from linux/fs/namei.c&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __PPC64_NAMEI_H
DECL|macro|__PPC64_NAMEI_H
mdefine_line|#define __PPC64_NAMEI_H
multiline_comment|/* This dummy routine maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|__emul_prefix
mdefine_line|#define __emul_prefix() NULL
macro_line|#endif /* __PPC64_NAMEI_H */
eof
