macro_line|#ifndef _ASM_ALPHA_PARAM_H
DECL|macro|_ASM_ALPHA_PARAM_H
mdefine_line|#define _ASM_ALPHA_PARAM_H
multiline_comment|/* ??? Gross.  I don&squot;t want to parameterize this, and supposedly the&n;   hardware ignores reprogramming.  We also need userland buy-in to the &n;   change in HZ, since this is visible in the wait4 resources etc.  */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef HZ
macro_line|# ifndef CONFIG_ALPHA_RAWHIDE
DECL|macro|HZ
macro_line|#  define HZ&t;1024
macro_line|# else
DECL|macro|HZ
macro_line|#  define HZ&t;1200
macro_line|# endif
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE&t;8192
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
macro_line|# define CLOCKS_PER_SEC&t;HZ&t;/* frequency at which times() counts */
macro_line|#endif
macro_line|#endif /* _ASM_ALPHA_PARAM_H */
eof
