multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright 1994 - 2000 Ralf Baechle (ralf@gnu.org)&n; * Copyright 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PARAM_H
DECL|macro|_ASM_PARAM_H
mdefine_line|#define _ASM_PARAM_H
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ 100
DECL|macro|HZ
macro_line|#  define HZ 100
macro_line|#ifdef __KERNEL__
DECL|macro|hz_to_std
macro_line|#  define hz_to_std(a) (a)
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
macro_line|# define CLOCKS_PER_SEC&t;100&t;/* frequency at which times() counts */
macro_line|#endif
macro_line|#endif /* _ASM_PARAM_H */
eof
