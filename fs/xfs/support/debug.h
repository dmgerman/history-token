multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_SUPPORT_DEBUG_H__
DECL|macro|__XFS_SUPPORT_DEBUG_H__
mdefine_line|#define __XFS_SUPPORT_DEBUG_H__
macro_line|#include &lt;stdarg.h&gt;
DECL|macro|CE_DEBUG
mdefine_line|#define CE_DEBUG&t;7&t;&t;/* debug&t;*/
DECL|macro|CE_CONT
mdefine_line|#define CE_CONT&t;&t;6&t;&t;/* continuation */
DECL|macro|CE_NOTE
mdefine_line|#define CE_NOTE&t;&t;5&t;&t;/* notice&t;*/
DECL|macro|CE_WARN
mdefine_line|#define CE_WARN&t;&t;4&t;&t;/* warning&t;*/
DECL|macro|CE_ALERT
mdefine_line|#define CE_ALERT&t;1&t;&t;/* alert&t;*/
DECL|macro|CE_PANIC
mdefine_line|#define CE_PANIC&t;0&t;&t;/* panic&t;*/
r_extern
r_void
id|icmn_err
c_func
(paren
r_int
comma
r_char
op_star
comma
id|va_list
)paren
suffix:semicolon
r_extern
r_void
id|cmn_err
c_func
(paren
r_int
comma
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
macro_line|# ifdef lint
DECL|macro|ASSERT
macro_line|#  define ASSERT(EX)&t;((void)0) /* avoid &quot;constant in conditional&quot; babble */
macro_line|# else
DECL|macro|ASSERT
macro_line|#  define ASSERT(EX) ((!doass||(EX))?((void)0):assfail(#EX, __FILE__, __LINE__))
macro_line|# endif /* lint */
macro_line|#else
DECL|macro|ASSERT
macro_line|# define ASSERT(x)&t;((void)0)
macro_line|#endif
r_extern
r_int
id|doass
suffix:semicolon
multiline_comment|/* dynamically turn off asserts */
r_extern
r_void
id|assfail
c_func
(paren
r_char
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_extern
r_int
r_int
id|random
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|get_thread_id
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|ASSERT_ALWAYS
mdefine_line|#define ASSERT_ALWAYS(EX)  ((EX)?((void)0):assfail(#EX, __FILE__, __LINE__))
DECL|macro|debug_stop_all_cpus
mdefine_line|#define debug_stop_all_cpus(param)&t;/* param is &quot;cpumask_t *&quot; */
macro_line|#endif&t;/* __XFS_SUPPORT_DEBUG_H__ */
eof
