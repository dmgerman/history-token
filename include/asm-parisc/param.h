macro_line|#ifndef _ASMPARISC_PARAM_H
DECL|macro|_ASMPARISC_PARAM_H
mdefine_line|#define _ASMPARISC_PARAM_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|# ifdef CONFIG_PA20
DECL|macro|HZ
macro_line|#  define HZ&t;&t;1000&t;&t;/* Faster machines */
macro_line|# else
DECL|macro|HZ
macro_line|#  define HZ&t;&t;100&t;&t;/* Internal kernel timer frequency */
macro_line|# endif
DECL|macro|USER_HZ
macro_line|# define USER_HZ&t;100&t;&t;/* .. some user interfaces are in &quot;ticks&quot; */
DECL|macro|CLOCKS_PER_SEC
macro_line|# define CLOCKS_PER_SEC&t;(USER_HZ)&t;/* like times() */
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
