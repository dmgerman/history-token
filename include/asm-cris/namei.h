multiline_comment|/* $Id: namei.h,v 1.1 2000/07/10 16:32:31 bjornw Exp $&n; * linux/include/asm-cris/namei.h&n; *&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __CRIS_NAMEI_H
DECL|macro|__CRIS_NAMEI_H
mdefine_line|#define __CRIS_NAMEI_H
multiline_comment|/* used to find file-system prefixes for doing emulations&n; * see for example asm-sparc/namei.h&n; * we dont use it...&n; */
DECL|macro|__emul_prefix
mdefine_line|#define __emul_prefix() NULL
macro_line|#endif /* __CRIS_NAMEI_H */
eof
