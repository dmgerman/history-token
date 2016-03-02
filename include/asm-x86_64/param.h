macro_line|#ifndef _ASMx86_64_PARAM_H
DECL|macro|_ASMx86_64_PARAM_H
mdefine_line|#define _ASMx86_64_PARAM_H
macro_line|#ifdef __KERNEL__
DECL|macro|HZ
macro_line|# define HZ            1000            /* Internal kernel timer frequency */
DECL|macro|USER_HZ
macro_line|# define USER_HZ       100          /* .. some user interfaces are in &quot;ticks */
DECL|macro|CLOCKS_PER_SEC
mdefine_line|#define CLOCKS_PER_SEC        (USER_HZ)       /* like times() */
macro_line|#endif
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE&t;4096
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP&t;&t;(-1)
macro_line|#endif
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN&t;64&t;/* max length of hostname */
macro_line|#endif
eof
