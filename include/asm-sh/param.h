macro_line|#ifndef __ASM_SH_PARAM_H
DECL|macro|__ASM_SH_PARAM_H
mdefine_line|#define __ASM_SH_PARAM_H
macro_line|#ifdef __KERNEL__
macro_line|# ifdef CONFIG_SH_WDT
DECL|macro|HZ
macro_line|#  define HZ&t;&t;1000&t;&t;/* Needed for high-res WOVF */
macro_line|# else
DECL|macro|HZ
macro_line|#  define HZ&t;&t;100
macro_line|# endif
DECL|macro|USER_HZ
macro_line|# define USER_HZ&t;100&t;&t;/* User interfaces are in &quot;ticks&quot; */
DECL|macro|CLOCKS_PER_SEC
macro_line|# define CLOCKS_PER_SEC&t;(USER_HZ)&t;/* frequency at which times() counts */
macro_line|#endif
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
macro_line|#endif /* __ASM_SH_PARAM_H */
eof
