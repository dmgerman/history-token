multiline_comment|/*&n; * File:&t;mca.c&n; * Purpose:&t;SN specific MCA code.&n; *&n; * Copyright (C) 2001-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/mca.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
multiline_comment|/*&n; * Interval for calling SAL to poll for errors that do NOT cause error&n; * interrupts. SAL will raise a CPEI if any errors are present that&n; * need to be logged.&n; */
DECL|macro|CPEI_INTERVAL
mdefine_line|#define CPEI_INTERVAL&t;(5*HZ)
DECL|variable|sn_cpei_timer
r_struct
id|timer_list
id|sn_cpei_timer
suffix:semicolon
r_void
id|sn_init_cpei_timer
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * print_hook&n; *&n; * This function is the callback routine that SAL calls to log error&n; * info for platform errors. &n; */
r_static
r_int
DECL|function|print_hook
id|print_hook
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_static
r_int
id|newline
op_assign
l_int|1
suffix:semicolon
r_char
id|buf
(braket
l_int|400
)braket
comma
op_star
id|p
suffix:semicolon
id|va_list
id|args
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newline
)paren
(brace
id|strcpy
c_func
(paren
id|buf
comma
l_string|&quot;+ &quot;
)paren
suffix:semicolon
id|len
op_add_assign
l_int|2
suffix:semicolon
)brace
id|len
op_add_assign
id|vsnprintf
c_func
(paren
id|buf
op_plus
id|len
comma
r_sizeof
(paren
id|buf
)paren
op_minus
id|len
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
multiline_comment|/* Prefix each line with &quot;+ &quot; to be consistent with mca.c. */
id|p
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
)paren
op_logical_and
op_star
op_increment
id|p
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|memmove
c_func
(paren
id|p
op_plus
l_int|2
comma
id|p
comma
l_int|1
op_plus
id|strlen
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|p
comma
l_string|&quot;+ &quot;
comma
l_int|2
)paren
suffix:semicolon
id|len
op_add_assign
l_int|2
suffix:semicolon
)brace
id|newline
op_assign
(paren
id|p
op_ne
l_int|0
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|buf
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * ia64_sn2_platform_plat_specific_err_print&n; *&n; * Called by the MCA handler to log platform-specific errors.&n; */
r_void
DECL|function|ia64_sn2_platform_plat_specific_err_print
id|ia64_sn2_platform_plat_specific_err_print
c_func
(paren
r_int
id|header_len
comma
r_int
id|sect_len
comma
id|u8
op_star
id|p_data
comma
id|prfunc_t
id|prfunc
)paren
(brace
id|ia64_sn_plat_specific_err_print
c_func
(paren
id|print_hook
comma
id|p_data
op_minus
id|sect_len
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sn_cpei_handler
id|sn_cpei_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|devid
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/*&n;&t; * this function&squot;s sole purpose is to call SAL when we receive&n;&t; * a CE interrupt from SHUB or when the timer routine decides&n;&t; * we need to call SAL to check for CEs.&n;&t; */
multiline_comment|/* CALL SAL_LOG_CE */
id|ia64_sn_plat_cpei_handler
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sn_cpei_timer_handler
id|sn_cpei_timer_handler
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
id|sn_cpei_handler
c_func
(paren
op_minus
l_int|1
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|sn_cpei_timer
comma
id|jiffies
op_plus
id|CPEI_INTERVAL
)paren
suffix:semicolon
)brace
r_void
DECL|function|sn_init_cpei_timer
id|sn_init_cpei_timer
c_func
(paren
)paren
(brace
id|sn_cpei_timer.expires
op_assign
id|jiffies
op_plus
id|CPEI_INTERVAL
suffix:semicolon
id|sn_cpei_timer.function
op_assign
id|sn_cpei_timer_handler
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sn_cpei_timer
)paren
suffix:semicolon
)brace
eof
