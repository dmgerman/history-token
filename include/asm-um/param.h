macro_line|#ifndef _UM_PARAM_H
DECL|macro|_UM_PARAM_H
mdefine_line|#define _UM_PARAM_H
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE   4096
macro_line|#ifndef NGROUPS
DECL|macro|NGROUPS
mdefine_line|#define NGROUPS         32
macro_line|#endif
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP         (-1)
macro_line|#endif
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN  64      /* max length of hostname */
macro_line|#ifdef __KERNEL__
DECL|macro|HZ
mdefine_line|#define HZ 100
DECL|macro|USER_HZ
mdefine_line|#define USER_HZ&t;100&t;   /* .. some user interfaces are in &quot;ticks&quot; */
DECL|macro|CLOCKS_PER_SEC
mdefine_line|#define CLOCKS_PER_SEC (USER_HZ)  /* frequency at which times() counts */
macro_line|#endif
macro_line|#endif
eof
