macro_line|#ifndef __LINUX_BRIDGE_EBT_VLAN_H
DECL|macro|__LINUX_BRIDGE_EBT_VLAN_H
mdefine_line|#define __LINUX_BRIDGE_EBT_VLAN_H
DECL|macro|EBT_VLAN_ID
mdefine_line|#define EBT_VLAN_ID&t;0x01
DECL|macro|EBT_VLAN_PRIO
mdefine_line|#define EBT_VLAN_PRIO&t;0x02
DECL|macro|EBT_VLAN_ENCAP
mdefine_line|#define EBT_VLAN_ENCAP&t;0x04
DECL|macro|EBT_VLAN_MASK
mdefine_line|#define EBT_VLAN_MASK (EBT_VLAN_ID | EBT_VLAN_PRIO | EBT_VLAN_ENCAP)
DECL|macro|EBT_VLAN_MATCH
mdefine_line|#define EBT_VLAN_MATCH &quot;vlan&quot;
DECL|struct|ebt_vlan_info
r_struct
id|ebt_vlan_info
(brace
DECL|member|id
r_uint16
id|id
suffix:semicolon
multiline_comment|/* VLAN ID {1-4095} */
DECL|member|prio
r_uint8
id|prio
suffix:semicolon
multiline_comment|/* VLAN User Priority {0-7} */
DECL|member|encap
r_uint16
id|encap
suffix:semicolon
multiline_comment|/* VLAN Encapsulated frame code {0-65535} */
DECL|member|bitmask
r_uint8
id|bitmask
suffix:semicolon
multiline_comment|/* Args bitmask bit 1=1 - ID arg,&n;&t;&t;&t;&t;   bit 2=1 User-Priority arg, bit 3=1 encap*/
DECL|member|invflags
r_uint8
id|invflags
suffix:semicolon
multiline_comment|/* Inverse bitmask  bit 1=1 - inversed ID arg, &n;&t;&t;&t;&t;   bit 2=1 - inversed Pirority arg */
)brace
suffix:semicolon
macro_line|#endif
eof
