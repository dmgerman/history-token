multiline_comment|/*&n; *&t;Apple Sound Chip &n; */
macro_line|#ifndef __ASM_MAC_ASC_H
DECL|macro|__ASM_MAC_ASC_H
mdefine_line|#define __ASM_MAC_ASC_H
multiline_comment|/*&n; *&t;ASC offsets and controls&n; */
DECL|macro|ASC_BUF_BASE
mdefine_line|#define ASC_BUF_BASE&t;0x00&t;/* RAM buffer offset */
DECL|macro|ASC_BUF_SIZE
mdefine_line|#define ASC_BUF_SIZE&t;0x800
DECL|macro|ASC_CONTROL
mdefine_line|#define ASC_CONTROL&t;0x800
DECL|macro|ASC_CONTROL_OFF
mdefine_line|#define ASC_CONTROL_OFF&t;&t;0x00
DECL|macro|ASC_FREQ
mdefine_line|#define ASC_FREQ(chan,byte)&t;((0x810)+((chan)&lt;&lt;3)+(byte))
DECL|macro|ASC_ENABLE
mdefine_line|#define ASC_ENABLE&t;0x801
DECL|macro|ASC_ENABLE_SAMPLE
mdefine_line|#define ASC_ENABLE_SAMPLE&t;0x02
DECL|macro|ASC_MODE
mdefine_line|#define ASC_MODE&t;0x802
DECL|macro|ASC_MODE_SAMPLE
mdefine_line|#define ASC_MODE_SAMPLE&t;&t;0x02
DECL|macro|ASC_VOLUME
mdefine_line|#define ASC_VOLUME&t;0x806
DECL|macro|ASC_CHAN
mdefine_line|#define ASC_CHAN&t;0x807&t;/* ??? */
macro_line|#endif
eof
