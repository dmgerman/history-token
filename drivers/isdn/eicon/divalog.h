multiline_comment|/*&n; *&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * This source file is supplied for the exclusive use with Eicon&n; * Technology Corporation&squot;s range of DIVA Server Adapters.&n; *&n; * Eicon File Revision :    1.0  &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY &n; * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  &n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*&n; * Include file for defining the kernel loggger messages&n; * These definitions are shared between the klog driver and the&n; * klogd daemon process&n; */
macro_line|#if !defined(_KLOGMSG_H)
DECL|macro|_KLOGMSG_H
mdefine_line|#define _KLOGMSG_H
multiline_comment|/* define a type for a log entry */
DECL|macro|KLOG_TEXT_MSG
mdefine_line|#define KLOG_TEXT_MSG   &t;(0)
DECL|macro|KLOG_XLOG_MSG
mdefine_line|#define KLOG_XLOG_MSG   &t;(1)
DECL|macro|KLOG_XTXT_MSG
mdefine_line|#define KLOG_XTXT_MSG   &t;(2)
DECL|macro|KLOG_IDI_REQ
mdefine_line|#define KLOG_IDI_REQ   &t;&t;(4)
DECL|macro|KLOG_IDI_CALLBACK
mdefine_line|#define KLOG_IDI_CALLBACK   (5)
DECL|macro|KLOG_CAPI_MSG
mdefine_line|#define KLOG_CAPI_MSG   &t;(6)
r_typedef
r_struct
(brace
DECL|member|time_stamp
r_int
r_int
id|time_stamp
suffix:semicolon
multiline_comment|/* in ms since last system boot */
DECL|member|card
r_int
id|card
suffix:semicolon
multiline_comment|/* card number (-1 for all) */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* type of log message (0 is text) */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* message length (non-text messages only) */
DECL|member|code
r_int
r_int
id|code
suffix:semicolon
multiline_comment|/* message code (non-text messages only) */
DECL|member|buffer
r_char
id|buffer
(braket
l_int|110
)braket
suffix:semicolon
multiline_comment|/* text/data to log */
DECL|typedef|klog_t
)brace
id|klog_t
suffix:semicolon
r_void
id|DivasLogAdd
c_func
(paren
r_void
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
macro_line|#endif /* of _KLOGMSG_H */
eof
