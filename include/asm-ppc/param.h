macro_line|#ifndef _ASM_PPC_PARAM_H
DECL|macro|_ASM_PPC_PARAM_H
mdefine_line|#define _ASM_PPC_PARAM_H
macro_line|#ifdef __KERNEL__
DECL|macro|HZ
mdefine_line|#define HZ&t;&t;1000&t;&t;/* internal timer frequency */
DECL|macro|USER_HZ
mdefine_line|#define USER_HZ&t;&t;100&t;&t;/* for user interfaces in &quot;ticks&quot; */
DECL|macro|CLOCKS_PER_SEC
mdefine_line|#define CLOCKS_PER_SEC&t;(USER_HZ)&t;/* frequency at which times() counts */
macro_line|#endif /* __KERNEL__ */
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
