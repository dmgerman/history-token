macro_line|#ifndef _ASM_PPC64_PARAM_H
DECL|macro|_ASM_PPC64_PARAM_H
mdefine_line|#define _ASM_PPC64_PARAM_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ 1024
macro_line|#ifdef __KERNEL__
macro_line|#if HZ == 100
multiline_comment|/* ppc (like X86) is defined to provide userspace with a world where HZ=100&n;   We have to do this, (x*const)/const2 isnt optimised out because its not&n;   a null operation as it might overflow.. */
DECL|macro|hz_to_std
mdefine_line|#define hz_to_std(a) (a)
macro_line|#else
DECL|macro|hz_to_std
mdefine_line|#define hz_to_std(a) ((a)*(100/HZ)+((a)*(100%HZ))/HZ)
macro_line|#endif
macro_line|#endif
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
macro_line|# define CLOCKS_PER_SEC&t;HZ&t;/* frequency at which times() counts */
macro_line|#endif
macro_line|#endif /* _ASM_PPC64_PARAM_H */
eof
