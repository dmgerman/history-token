multiline_comment|/*&n; *&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * Eicon File Revision :    1.3  &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY &n; * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  &n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*&n; * Source file for kernel interface to kernel log facility&n; */
macro_line|#include &quot;eicon.h&quot;
macro_line|#include &quot;sys.h&quot;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &quot;divas.h&quot;
macro_line|#include &quot;divalog.h&quot;
macro_line|#include &quot;uxio.h&quot;
DECL|function|DivasPrintf
r_void
id|DivasPrintf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|klog_t
id|log
suffix:semicolon
multiline_comment|/* log entry buffer */
id|va_list
id|argptr
suffix:semicolon
multiline_comment|/* pointer to additional args */
id|va_start
c_func
(paren
id|argptr
comma
id|fmt
)paren
suffix:semicolon
multiline_comment|/* clear log entry */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|log
comma
l_int|0
comma
r_sizeof
(paren
id|klog_t
)paren
)paren
suffix:semicolon
id|log.card
op_assign
op_minus
l_int|1
suffix:semicolon
id|log.type
op_assign
id|KLOG_TEXT_MSG
suffix:semicolon
multiline_comment|/* time stamp the entry */
id|log.time_stamp
op_assign
id|UxTimeGet
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* call vsprintf to format the user&squot;s information */
id|vsnprintf
c_func
(paren
id|log.buffer
comma
id|DIM
c_func
(paren
id|log.buffer
)paren
comma
id|fmt
comma
id|argptr
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|argptr
)paren
suffix:semicolon
multiline_comment|/* send to the log streams driver and return */
id|DivasLogAdd
c_func
(paren
op_amp
id|log
comma
r_sizeof
(paren
id|klog_t
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
