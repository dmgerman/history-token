multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright 1994 - 2000, 2002 Ralf Baechle (ralf@gnu.org)&n; * Copyright 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PARAM_H
DECL|macro|_ASM_PARAM_H
mdefine_line|#define _ASM_PARAM_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DECSTATION
multiline_comment|/*&n;    * log2(HZ), change this here if you want another HZ value. This is also&n;    * used in dec_time_init.  Minimum is 1, Maximum is 15.&n;    */
DECL|macro|LOG_2_HZ
macro_line|#  define LOG_2_HZ 7
DECL|macro|HZ
macro_line|#  define HZ (1 &lt;&lt; LOG_2_HZ)
macro_line|#else
DECL|macro|HZ
macro_line|# define HZ&t;&t;1000&t;&t;/* Internal kernel timer frequency */
macro_line|#endif
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
macro_line|#endif /* _ASM_PARAM_H */
eof
