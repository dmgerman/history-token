macro_line|#ifndef _M68KNOMMU_PARAM_H
DECL|macro|_M68KNOMMU_PARAM_H
mdefine_line|#define _M68KNOMMU_PARAM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_CLEOPATRA)
DECL|macro|HZ
mdefine_line|#define&t;HZ 1000
macro_line|#endif
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define&t;HZ 100
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|macro|USER_HZ
mdefine_line|#define&t;USER_HZ&t;&t;HZ
DECL|macro|CLOCKS_PER_SEC
mdefine_line|#define&t;CLOCKS_PER_SEC&t;(USER_HZ)
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE&t;4096
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP&t;&t;(-1)
macro_line|#endif
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN&t;64&t;/* max length of hostname */
macro_line|#endif /* _M68KNOMMU_PARAM_H */
eof
