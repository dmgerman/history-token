macro_line|#ifndef __LINUX_BRIDGE_EBT_ARP_H
DECL|macro|__LINUX_BRIDGE_EBT_ARP_H
mdefine_line|#define __LINUX_BRIDGE_EBT_ARP_H
DECL|macro|EBT_ARP_OPCODE
mdefine_line|#define EBT_ARP_OPCODE 0x01
DECL|macro|EBT_ARP_HTYPE
mdefine_line|#define EBT_ARP_HTYPE 0x02
DECL|macro|EBT_ARP_PTYPE
mdefine_line|#define EBT_ARP_PTYPE 0x04
DECL|macro|EBT_ARP_SRC_IP
mdefine_line|#define EBT_ARP_SRC_IP 0x08
DECL|macro|EBT_ARP_DST_IP
mdefine_line|#define EBT_ARP_DST_IP 0x10
DECL|macro|EBT_ARP_MASK
mdefine_line|#define EBT_ARP_MASK (EBT_ARP_OPCODE | EBT_ARP_HTYPE | EBT_ARP_PTYPE | &bslash;&n;   EBT_ARP_SRC_IP | EBT_ARP_DST_IP)
DECL|macro|EBT_ARP_MATCH
mdefine_line|#define EBT_ARP_MATCH &quot;arp&quot;
DECL|struct|ebt_arp_info
r_struct
id|ebt_arp_info
(brace
DECL|member|htype
r_uint16
id|htype
suffix:semicolon
DECL|member|ptype
r_uint16
id|ptype
suffix:semicolon
DECL|member|opcode
r_uint16
id|opcode
suffix:semicolon
DECL|member|saddr
r_uint32
id|saddr
suffix:semicolon
DECL|member|smsk
r_uint32
id|smsk
suffix:semicolon
DECL|member|daddr
r_uint32
id|daddr
suffix:semicolon
DECL|member|dmsk
r_uint32
id|dmsk
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
