multiline_comment|/*&n; * cs_types.h 1.18 2000/06/12 21:55:40&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_CS_TYPES_H
DECL|macro|_LINUX_CS_TYPES_H
mdefine_line|#define _LINUX_CS_TYPES_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#else
macro_line|#include &lt;sys/types.h&gt;
macro_line|#endif
macro_line|#ifdef __arm__
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
r_struct
id|eraseq_t
suffix:semicolon
DECL|typedef|eraseq_handle_t
r_typedef
r_struct
id|eraseq_t
op_star
id|eraseq_handle_t
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
