multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; *  $Id: bluetooth.h,v 1.6 2001/08/03 04:19:49 maxk Exp $&n; */
macro_line|#ifndef __BLUETOOTH_H
DECL|macro|__BLUETOOTH_H
mdefine_line|#define __BLUETOOTH_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifndef AF_BLUETOOTH
DECL|macro|AF_BLUETOOTH
mdefine_line|#define AF_BLUETOOTH&t;31
DECL|macro|PF_BLUETOOTH
mdefine_line|#define PF_BLUETOOTH&t;AF_BLUETOOTH
macro_line|#endif
DECL|macro|BTPROTO_L2CAP
mdefine_line|#define BTPROTO_L2CAP   0
DECL|macro|BTPROTO_HCI
mdefine_line|#define BTPROTO_HCI     1
DECL|macro|SOL_HCI
mdefine_line|#define SOL_HCI     0
DECL|macro|SOL_L2CAP
mdefine_line|#define SOL_L2CAP   6
multiline_comment|/* Connection and socket states */
r_enum
(brace
DECL|enumerator|BT_CONNECTED
id|BT_CONNECTED
op_assign
l_int|1
comma
multiline_comment|/* Equal to TCP_ESTABLISHED to make net code happy */
DECL|enumerator|BT_OPEN
id|BT_OPEN
comma
DECL|enumerator|BT_BOUND
id|BT_BOUND
comma
DECL|enumerator|BT_LISTEN
id|BT_LISTEN
comma
DECL|enumerator|BT_CONNECT
id|BT_CONNECT
comma
DECL|enumerator|BT_CONFIG
id|BT_CONFIG
comma
DECL|enumerator|BT_DISCONN
id|BT_DISCONN
comma
DECL|enumerator|BT_CLOSED
id|BT_CLOSED
)brace
suffix:semicolon
multiline_comment|/* Endianness conversions */
DECL|macro|htobs
mdefine_line|#define htobs(a)&t;__cpu_to_le16(a)
DECL|macro|htobl
mdefine_line|#define htobl(a)&t;__cpu_to_le32(a)
DECL|macro|btohs
mdefine_line|#define btohs(a)&t;__le16_to_cpu(a)
DECL|macro|btohl
mdefine_line|#define btohl(a)&t;__le32_to_cpu(a)
multiline_comment|/* BD Address */
r_typedef
r_struct
(brace
DECL|member|b
id|__u8
id|b
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|bdaddr_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|bdaddr_t
suffix:semicolon
DECL|macro|BDADDR_ANY
mdefine_line|#define BDADDR_ANY ((bdaddr_t *)&quot;&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&quot;)
multiline_comment|/* Copy, swap, convert BD Address */
DECL|function|bacmp
r_static
r_inline
r_int
id|bacmp
c_func
(paren
id|bdaddr_t
op_star
id|ba1
comma
id|bdaddr_t
op_star
id|ba2
)paren
(brace
r_return
id|memcmp
c_func
(paren
id|ba1
comma
id|ba2
comma
r_sizeof
(paren
id|bdaddr_t
)paren
)paren
suffix:semicolon
)brace
DECL|function|bacpy
r_static
r_inline
r_void
id|bacpy
c_func
(paren
id|bdaddr_t
op_star
id|dst
comma
id|bdaddr_t
op_star
id|src
)paren
(brace
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
r_sizeof
(paren
id|bdaddr_t
)paren
)paren
suffix:semicolon
)brace
r_void
id|baswap
c_func
(paren
id|bdaddr_t
op_star
id|dst
comma
id|bdaddr_t
op_star
id|src
)paren
suffix:semicolon
r_char
op_star
id|batostr
c_func
(paren
id|bdaddr_t
op_star
id|ba
)paren
suffix:semicolon
id|bdaddr_t
op_star
id|strtoba
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
r_int
id|bterr
c_func
(paren
id|__u16
id|code
)paren
suffix:semicolon
macro_line|#endif /* __BLUETOOTH_H */
eof
