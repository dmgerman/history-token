multiline_comment|/* $Id: iga.h,v 1.2 1999/09/11 22:56:31 zaitcev Exp $&n; * iga1682.h: Sparc/PCI iga1682 driver constants etc.&n; *&n; * Copyleft 1998 V. Roganov and G. Raiko&n; */
macro_line|#ifndef _IGA1682_H
DECL|macro|_IGA1682_H
mdefine_line|#define _IGA1682_H 1
DECL|struct|iga1682_info
r_struct
id|iga1682_info
(brace
DECL|member|total_vram
r_int
r_int
id|total_vram
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IGA_ATTR_CTL
mdefine_line|#define IGA_ATTR_CTL&t;&t;&t;0x3C0
DECL|macro|IGA_IDX_VGA_OVERSCAN
mdefine_line|#define   IGA_IDX_VGA_OVERSCAN&t;&t;0x11
DECL|macro|DAC_W_INDEX
mdefine_line|#define DAC_W_INDEX                     0x03C8
DECL|macro|DAC_DATA
mdefine_line|#define DAC_DATA                        0x03C9
DECL|macro|IGA_EXT_CNTRL
mdefine_line|#define IGA_EXT_CNTRL                   0x3CE
DECL|macro|IGA_IDX_EXT_BUS_CNTL
mdefine_line|#define   IGA_IDX_EXT_BUS_CNTL          0x30
DECL|macro|MEM_SIZE_ALIAS
mdefine_line|#define     MEM_SIZE_ALIAS              0x3
DECL|macro|MEM_SIZE_1M
mdefine_line|#define     MEM_SIZE_1M                 0x0
DECL|macro|MEM_SIZE_2M
mdefine_line|#define     MEM_SIZE_2M                 0x1
DECL|macro|MEM_SIZE_4M
mdefine_line|#define     MEM_SIZE_4M                 0x2
DECL|macro|MEM_SIZE_RESERVED
mdefine_line|#define     MEM_SIZE_RESERVED           0x3
DECL|macro|IGA_IDX_OVERSCAN_COLOR
mdefine_line|#define   IGA_IDX_OVERSCAN_COLOR        0x58
DECL|macro|IGA_IDX_EXT_MEM_2
mdefine_line|#define   IGA_IDX_EXT_MEM_2             0x72
macro_line|#endif /* !(_IGA1682_H) */
eof
