multiline_comment|/*&n; *  include/asm-s390/param.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/param.h&quot;&n; */
macro_line|#ifndef _ASMS390_PARAM_H
DECL|macro|_ASMS390_PARAM_H
mdefine_line|#define _ASMS390_PARAM_H
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE&t;4096
macro_line|#ifndef NGROUPS
DECL|macro|NGROUPS
mdefine_line|#define NGROUPS&t;&t;32
macro_line|#endif
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP&t;&t;(-1)
macro_line|#endif
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN&t;64&t;/* max length of hostname */
macro_line|#ifdef __KERNEL__
DECL|macro|CLOCKS_PER_SEC
macro_line|# define CLOCKS_PER_SEC&t;&t;HZ&t;/* frequency at which times() counts */
macro_line|#endif
macro_line|#endif
eof
