multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * $Id: hci_h4.h,v 1.1.1.1 2002/03/08 21:03:15 maxk Exp $&n; */
macro_line|#ifdef __KERNEL__
DECL|struct|h4_struct
r_struct
id|h4_struct
(brace
DECL|member|rx_state
r_int
r_int
id|rx_state
suffix:semicolon
DECL|member|rx_count
r_int
r_int
id|rx_count
suffix:semicolon
DECL|member|rx_skb
r_struct
id|sk_buff
op_star
id|rx_skb
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* H4 receiver States */
DECL|macro|H4_W4_PACKET_TYPE
mdefine_line|#define H4_W4_PACKET_TYPE 0
DECL|macro|H4_W4_EVENT_HDR
mdefine_line|#define H4_W4_EVENT_HDR&t;  1
DECL|macro|H4_W4_ACL_HDR
mdefine_line|#define H4_W4_ACL_HDR     2
DECL|macro|H4_W4_SCO_HDR
mdefine_line|#define H4_W4_SCO_HDR     3
DECL|macro|H4_W4_DATA
mdefine_line|#define H4_W4_DATA        4
macro_line|#endif /* __KERNEL__ */
eof
