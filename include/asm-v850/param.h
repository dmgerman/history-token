multiline_comment|/*&n; * include/asm-v850/param.h -- Varions kernel parameters&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_PARAM_H__
DECL|macro|__V850_PARAM_H__
mdefine_line|#define __V850_PARAM_H__
macro_line|#include &lt;asm/machdep.h&gt;&t;/* For HZ */
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
DECL|macro|USER_HZ
macro_line|# define USER_HZ&t;100
DECL|macro|CLOCKS_PER_SEC
macro_line|# define CLOCKS_PER_SEC&t;USER_HZ
macro_line|#endif
macro_line|#endif /* __V850_PARAM_H__ */
eof
