macro_line|#ifndef __LINUX_BRIDGE_EBT_802_3_H
DECL|macro|__LINUX_BRIDGE_EBT_802_3_H
mdefine_line|#define __LINUX_BRIDGE_EBT_802_3_H
DECL|macro|EBT_802_3_SAP
mdefine_line|#define EBT_802_3_SAP 0x01
DECL|macro|EBT_802_3_TYPE
mdefine_line|#define EBT_802_3_TYPE 0x02
DECL|macro|EBT_802_3_MATCH
mdefine_line|#define EBT_802_3_MATCH &quot;802_3&quot;
multiline_comment|/*&n; * If frame has DSAP/SSAP value 0xaa you must check the SNAP type&n; * to discover what kind of packet we&squot;re carrying. &n; */
DECL|macro|CHECK_TYPE
mdefine_line|#define CHECK_TYPE 0xaa
multiline_comment|/*&n; * Control field may be one or two bytes.  If the first byte has&n; * the value 0x03 then the entire length is one byte, otherwise it is two.&n; * One byte controls are used in Unnumbered Information frames.&n; * Two byte controls are used in Numbered Information frames.&n; */
DECL|macro|IS_UI
mdefine_line|#define IS_UI 0x03
DECL|macro|EBT_802_3_MASK
mdefine_line|#define EBT_802_3_MASK (EBT_802_3_SAP | EBT_802_3_TYPE | EBT_802_3)
multiline_comment|/* ui has one byte ctrl, ni has two */
DECL|struct|hdr_ui
r_struct
id|hdr_ui
(brace
DECL|member|dsap
r_uint8
id|dsap
suffix:semicolon
DECL|member|ssap
r_uint8
id|ssap
suffix:semicolon
DECL|member|ctrl
r_uint8
id|ctrl
suffix:semicolon
DECL|member|orig
r_uint8
id|orig
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|type
r_uint16
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hdr_ni
r_struct
id|hdr_ni
(brace
DECL|member|dsap
r_uint8
id|dsap
suffix:semicolon
DECL|member|ssap
r_uint8
id|ssap
suffix:semicolon
DECL|member|ctrl
r_uint16
id|ctrl
suffix:semicolon
DECL|member|orig
r_uint8
id|orig
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|type
r_uint16
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ebt_802_3_hdr
r_struct
id|ebt_802_3_hdr
(brace
DECL|member|daddr
r_uint8
id|daddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|saddr
r_uint8
id|saddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|len
r_uint16
id|len
suffix:semicolon
r_union
(brace
DECL|member|ui
r_struct
id|hdr_ui
id|ui
suffix:semicolon
DECL|member|ni
r_struct
id|hdr_ni
id|ni
suffix:semicolon
DECL|member|llc
)brace
id|llc
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/skbuff.h&gt;
DECL|function|ebt_802_3_hdr
r_static
r_inline
r_struct
id|ebt_802_3_hdr
op_star
id|ebt_802_3_hdr
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
(paren
r_struct
id|ebt_802_3_hdr
op_star
)paren
id|skb-&gt;mac.raw
suffix:semicolon
)brace
macro_line|#endif
DECL|struct|ebt_802_3_info
r_struct
id|ebt_802_3_info
(brace
DECL|member|sap
r_uint8
id|sap
suffix:semicolon
DECL|member|type
r_uint16
id|type
suffix:semicolon
DECL|member|bitmask
r_uint8
id|bitmask
suffix:semicolon
DECL|member|invflags
r_uint8
id|invflags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
