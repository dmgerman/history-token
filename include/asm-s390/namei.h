multiline_comment|/*&n; *  include/asm-s390/namei.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/namei.h&quot;&n; *&n; *  Included from linux/fs/namei.c&n; */
macro_line|#ifndef __S390_NAMEI_H
DECL|macro|__S390_NAMEI_H
mdefine_line|#define __S390_NAMEI_H
multiline_comment|/* This dummy routine maybe changed to something useful&n; * for /usr/gnemul/ emulation stuff.&n; * Look at asm-sparc/namei.h for details.&n; */
DECL|macro|__prefix_lookup_dentry
mdefine_line|#define __prefix_lookup_dentry(name, lookup_flags) &bslash;&n;        do {} while (0)
macro_line|#endif /* __S390_NAMEI_H */
eof
