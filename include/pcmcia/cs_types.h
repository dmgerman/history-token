multiline_comment|/*&n; * cs_types.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * (C) 1999             David A. Hinds&n; */
macro_line|#ifndef _LINUX_CS_TYPES_H
DECL|macro|_LINUX_CS_TYPES_H
mdefine_line|#define _LINUX_CS_TYPES_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#else
macro_line|#include &lt;sys/types.h&gt;
macro_line|#endif
macro_line|#if defined(__arm__) || defined(__mips__)
DECL|typedef|ioaddr_t
r_typedef
id|u_int
id|ioaddr_t
suffix:semicolon
macro_line|#else
DECL|typedef|ioaddr_t
r_typedef
id|u_short
id|ioaddr_t
suffix:semicolon
macro_line|#endif
DECL|typedef|socket_t
r_typedef
id|u_short
id|socket_t
suffix:semicolon
DECL|typedef|event_t
r_typedef
id|u_int
id|event_t
suffix:semicolon
DECL|typedef|cisdata_t
r_typedef
id|u_char
id|cisdata_t
suffix:semicolon
DECL|typedef|page_t
r_typedef
id|u_short
id|page_t
suffix:semicolon
r_struct
id|client_t
suffix:semicolon
DECL|typedef|client_handle_t
r_typedef
r_struct
id|client_t
op_star
id|client_handle_t
suffix:semicolon
r_struct
id|window_t
suffix:semicolon
DECL|typedef|window_handle_t
r_typedef
r_struct
id|window_t
op_star
id|window_handle_t
suffix:semicolon
r_struct
id|region_t
suffix:semicolon
DECL|typedef|memory_handle_t
r_typedef
r_struct
id|region_t
op_star
id|memory_handle_t
suffix:semicolon
macro_line|#ifndef DEV_NAME_LEN
DECL|macro|DEV_NAME_LEN
mdefine_line|#define DEV_NAME_LEN 32
macro_line|#endif
DECL|typedef|dev_info_t
r_typedef
r_char
id|dev_info_t
(braket
id|DEV_NAME_LEN
)braket
suffix:semicolon
macro_line|#endif /* _LINUX_CS_TYPES_H */
eof
