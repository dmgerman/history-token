macro_line|#ifndef __LINUX_BRIDGE_EBT_MARK_M_H
DECL|macro|__LINUX_BRIDGE_EBT_MARK_M_H
mdefine_line|#define __LINUX_BRIDGE_EBT_MARK_M_H
DECL|macro|EBT_MARK_AND
mdefine_line|#define EBT_MARK_AND 0x01
DECL|macro|EBT_MARK_OR
mdefine_line|#define EBT_MARK_OR 0x02
DECL|macro|EBT_MARK_MASK
mdefine_line|#define EBT_MARK_MASK (EBT_MARK_AND | EBT_MARK_OR)
DECL|struct|ebt_mark_m_info
r_struct
id|ebt_mark_m_info
(brace
DECL|member|mark
DECL|member|mask
r_int
r_int
id|mark
comma
id|mask
suffix:semicolon
DECL|member|invert
r_uint8
id|invert
suffix:semicolon
DECL|member|bitmask
r_uint8
id|bitmask
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EBT_MARK_MATCH
mdefine_line|#define EBT_MARK_MATCH &quot;mark_m&quot;
macro_line|#endif
eof
