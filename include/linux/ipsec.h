macro_line|#ifndef _LINUX_IPSEC_H
DECL|macro|_LINUX_IPSEC_H
mdefine_line|#define _LINUX_IPSEC_H
multiline_comment|/* The definitions, required to talk to KAME racoon IKE. */
macro_line|#include &lt;linux/pfkeyv2.h&gt;
DECL|macro|IPSEC_PORT_ANY
mdefine_line|#define IPSEC_PORT_ANY&t;&t;0
DECL|macro|IPSEC_ULPROTO_ANY
mdefine_line|#define IPSEC_ULPROTO_ANY&t;255
DECL|macro|IPSEC_PROTO_ANY
mdefine_line|#define IPSEC_PROTO_ANY&t;&t;255
r_enum
(brace
DECL|enumerator|IPSEC_MODE_ANY
id|IPSEC_MODE_ANY
op_assign
l_int|0
comma
multiline_comment|/* We do not support this for SA */
DECL|enumerator|IPSEC_MODE_TRANSPORT
id|IPSEC_MODE_TRANSPORT
op_assign
l_int|1
comma
DECL|enumerator|IPSEC_MODE_TUNNEL
id|IPSEC_MODE_TUNNEL
op_assign
l_int|2
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IPSEC_DIR_ANY
id|IPSEC_DIR_ANY
op_assign
l_int|0
comma
DECL|enumerator|IPSEC_DIR_INBOUND
id|IPSEC_DIR_INBOUND
op_assign
l_int|1
comma
DECL|enumerator|IPSEC_DIR_OUTBOUND
id|IPSEC_DIR_OUTBOUND
op_assign
l_int|2
comma
DECL|enumerator|IPSEC_DIR_FWD
id|IPSEC_DIR_FWD
op_assign
l_int|3
comma
multiline_comment|/* It is our own */
DECL|enumerator|IPSEC_DIR_MAX
id|IPSEC_DIR_MAX
op_assign
l_int|4
comma
DECL|enumerator|IPSEC_DIR_INVALID
id|IPSEC_DIR_INVALID
op_assign
l_int|5
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IPSEC_POLICY_DISCARD
id|IPSEC_POLICY_DISCARD
op_assign
l_int|0
comma
DECL|enumerator|IPSEC_POLICY_NONE
id|IPSEC_POLICY_NONE
op_assign
l_int|1
comma
DECL|enumerator|IPSEC_POLICY_IPSEC
id|IPSEC_POLICY_IPSEC
op_assign
l_int|2
comma
DECL|enumerator|IPSEC_POLICY_ENTRUST
id|IPSEC_POLICY_ENTRUST
op_assign
l_int|3
comma
DECL|enumerator|IPSEC_POLICY_BYPASS
id|IPSEC_POLICY_BYPASS
op_assign
l_int|4
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|IPSEC_LEVEL_DEFAULT
id|IPSEC_LEVEL_DEFAULT
op_assign
l_int|0
comma
DECL|enumerator|IPSEC_LEVEL_USE
id|IPSEC_LEVEL_USE
op_assign
l_int|1
comma
DECL|enumerator|IPSEC_LEVEL_REQUIRE
id|IPSEC_LEVEL_REQUIRE
op_assign
l_int|2
comma
DECL|enumerator|IPSEC_LEVEL_UNIQUE
id|IPSEC_LEVEL_UNIQUE
op_assign
l_int|3
)brace
suffix:semicolon
DECL|macro|IPSEC_MANUAL_REQID_MAX
mdefine_line|#define IPSEC_MANUAL_REQID_MAX&t;0x3fff
DECL|macro|IPSEC_REPLAYWSIZE
mdefine_line|#define IPSEC_REPLAYWSIZE  32
macro_line|#endif&t;/* _LINUX_IPSEC_H */
eof
