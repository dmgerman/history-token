macro_line|#ifndef _M68KNOMMU_PARAM_H
DECL|macro|_M68KNOMMU_PARAM_H
mdefine_line|#define _M68KNOMMU_PARAM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef HZ
macro_line|#ifdef CONFIG_COLDFIRE
macro_line|#if defined(CONFIG_CLEOPATRA)
DECL|macro|HZ
mdefine_line|#define HZ 1000
macro_line|#else
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_M68EN302
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
macro_line|#ifdef CONFIG_M68328
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
macro_line|#ifdef CONFIG_M68EZ328
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
macro_line|#ifdef CONFIG_UCSIMM
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
macro_line|#ifdef CONFIG_M68VZ328
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
macro_line|#ifdef CONFIG_SHGLCORE
DECL|macro|HZ
mdefine_line|#define HZ 50
macro_line|#endif
macro_line|#ifdef CONFIG_M68360
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|macro|USER_HZ
mdefine_line|#define&t;USER_HZ&t;&t;HZ
DECL|macro|CLOCKS_PER_SEC
mdefine_line|#define&t;CLOCKS_PER_SEC&t;(USER_HZ)
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
macro_line|#endif /* _M68KNOMMU_PARAM_H */
eof
