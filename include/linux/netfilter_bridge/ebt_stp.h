macro_line|#ifndef __LINUX_BRIDGE_EBT_STP_H
DECL|macro|__LINUX_BRIDGE_EBT_STP_H
mdefine_line|#define __LINUX_BRIDGE_EBT_STP_H
DECL|macro|EBT_STP_TYPE
mdefine_line|#define EBT_STP_TYPE&t;&t;0x0001
DECL|macro|EBT_STP_FLAGS
mdefine_line|#define EBT_STP_FLAGS&t;&t;0x0002
DECL|macro|EBT_STP_ROOTPRIO
mdefine_line|#define EBT_STP_ROOTPRIO&t;0x0004
DECL|macro|EBT_STP_ROOTADDR
mdefine_line|#define EBT_STP_ROOTADDR&t;0x0008
DECL|macro|EBT_STP_ROOTCOST
mdefine_line|#define EBT_STP_ROOTCOST&t;0x0010
DECL|macro|EBT_STP_SENDERPRIO
mdefine_line|#define EBT_STP_SENDERPRIO&t;0x0020
DECL|macro|EBT_STP_SENDERADDR
mdefine_line|#define EBT_STP_SENDERADDR&t;0x0040
DECL|macro|EBT_STP_PORT
mdefine_line|#define EBT_STP_PORT&t;&t;0x0080
DECL|macro|EBT_STP_MSGAGE
mdefine_line|#define EBT_STP_MSGAGE&t;&t;0x0100
DECL|macro|EBT_STP_MAXAGE
mdefine_line|#define EBT_STP_MAXAGE&t;&t;0x0200
DECL|macro|EBT_STP_HELLOTIME
mdefine_line|#define EBT_STP_HELLOTIME&t;0x0400
DECL|macro|EBT_STP_FWDD
mdefine_line|#define EBT_STP_FWDD&t;&t;0x0800
DECL|macro|EBT_STP_MASK
mdefine_line|#define EBT_STP_MASK&t;&t;0x0fff
DECL|macro|EBT_STP_CONFIG_MASK
mdefine_line|#define EBT_STP_CONFIG_MASK&t;0x0ffe
DECL|macro|EBT_STP_MATCH
mdefine_line|#define EBT_STP_MATCH &quot;stp&quot;
DECL|struct|ebt_stp_config_info
r_struct
id|ebt_stp_config_info
(brace
DECL|member|flags
r_uint8
id|flags
suffix:semicolon
DECL|member|root_priol
DECL|member|root_priou
r_uint16
id|root_priol
comma
id|root_priou
suffix:semicolon
DECL|member|root_addr
DECL|member|root_addrmsk
r_char
id|root_addr
(braket
l_int|6
)braket
comma
id|root_addrmsk
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|root_costl
DECL|member|root_costu
r_uint32
id|root_costl
comma
id|root_costu
suffix:semicolon
DECL|member|sender_priol
DECL|member|sender_priou
r_uint16
id|sender_priol
comma
id|sender_priou
suffix:semicolon
DECL|member|sender_addr
DECL|member|sender_addrmsk
r_char
id|sender_addr
(braket
l_int|6
)braket
comma
id|sender_addrmsk
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|portl
DECL|member|portu
r_uint16
id|portl
comma
id|portu
suffix:semicolon
DECL|member|msg_agel
DECL|member|msg_ageu
r_uint16
id|msg_agel
comma
id|msg_ageu
suffix:semicolon
DECL|member|max_agel
DECL|member|max_ageu
r_uint16
id|max_agel
comma
id|max_ageu
suffix:semicolon
DECL|member|hello_timel
DECL|member|hello_timeu
r_uint16
id|hello_timel
comma
id|hello_timeu
suffix:semicolon
DECL|member|forward_delayl
DECL|member|forward_delayu
r_uint16
id|forward_delayl
comma
id|forward_delayu
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ebt_stp_info
r_struct
id|ebt_stp_info
(brace
DECL|member|type
r_uint8
id|type
suffix:semicolon
DECL|member|config
r_struct
id|ebt_stp_config_info
id|config
suffix:semicolon
DECL|member|bitmask
r_uint16
id|bitmask
suffix:semicolon
DECL|member|invflags
r_uint16
id|invflags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
