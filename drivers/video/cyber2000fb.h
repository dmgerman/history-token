multiline_comment|/*&n; *  linux/drivers/video/cyber2000fb.h&n; *&n; *  Copyright (C) 1998-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Integraphics Cyber2000 frame buffer device&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|cyber2000_outb
mdefine_line|#define cyber2000_outb(dat,reg)&t;writeb(dat, CyberRegs + reg)
DECL|macro|cyber2000_outw
mdefine_line|#define cyber2000_outw(dat,reg)&t;writew(dat, CyberRegs + reg)
DECL|macro|cyber2000_outl
mdefine_line|#define cyber2000_outl(dat,reg)&t;writel(dat, CyberRegs + reg)
DECL|macro|cyber2000_inb
mdefine_line|#define cyber2000_inb(reg)&t;readb(CyberRegs + reg)
DECL|macro|cyber2000_inw
mdefine_line|#define cyber2000_inw(reg)&t;readw(CyberRegs + reg)
DECL|macro|cyber2000_inl
mdefine_line|#define cyber2000_inl(reg)&t;readl(CyberRegs + reg)
multiline_comment|/*&n; * Internal CyberPro sizes and offsets.&n; */
DECL|macro|MMIO_OFFSET
mdefine_line|#define MMIO_OFFSET&t;0x00800000
DECL|macro|MMIO_SIZE
mdefine_line|#define MMIO_SIZE&t;0x000c0000
DECL|macro|NR_PALETTE
mdefine_line|#define NR_PALETTE&t;256
macro_line|#if defined(DEBUG) &amp;&amp; defined(CONFIG_DEBUG_LL)
DECL|function|debug_printf
r_static
r_void
id|debug_printf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_char
id|buffer
(braket
l_int|128
)braket
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|buffer
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
id|printascii
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|debug_printf
mdefine_line|#define debug_printf(x...) do { } while (0)
macro_line|#endif
DECL|function|cyber2000_crtcw
r_static
r_inline
r_void
id|cyber2000_crtcw
c_func
(paren
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|cyber2000_outb
c_func
(paren
id|reg
comma
l_int|0x3d4
)paren
suffix:semicolon
id|cyber2000_outb
c_func
(paren
id|val
comma
l_int|0x3d5
)paren
suffix:semicolon
)brace
DECL|function|cyber2000_grphw
r_static
r_inline
r_void
id|cyber2000_grphw
c_func
(paren
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|cyber2000_outb
c_func
(paren
id|reg
comma
l_int|0x3ce
)paren
suffix:semicolon
id|cyber2000_outb
c_func
(paren
id|val
comma
l_int|0x3cf
)paren
suffix:semicolon
)brace
DECL|function|cyber2000_grphr
r_static
r_inline
r_int
r_int
id|cyber2000_grphr
c_func
(paren
r_int
id|reg
)paren
(brace
id|cyber2000_outb
c_func
(paren
id|reg
comma
l_int|0x3ce
)paren
suffix:semicolon
r_return
id|cyber2000_inb
c_func
(paren
l_int|0x3cf
)paren
suffix:semicolon
)brace
DECL|function|cyber2000_attrw
r_static
r_inline
r_void
id|cyber2000_attrw
c_func
(paren
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|cyber2000_inb
c_func
(paren
l_int|0x3da
)paren
suffix:semicolon
id|cyber2000_outb
c_func
(paren
id|reg
comma
l_int|0x3c0
)paren
suffix:semicolon
id|cyber2000_inb
c_func
(paren
l_int|0x3c1
)paren
suffix:semicolon
id|cyber2000_outb
c_func
(paren
id|val
comma
l_int|0x3c0
)paren
suffix:semicolon
)brace
DECL|function|cyber2000_seqw
r_static
r_inline
r_void
id|cyber2000_seqw
c_func
(paren
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|cyber2000_outb
c_func
(paren
id|reg
comma
l_int|0x3c4
)paren
suffix:semicolon
id|cyber2000_outb
c_func
(paren
id|val
comma
l_int|0x3c5
)paren
suffix:semicolon
)brace
DECL|macro|PIXFORMAT_8BPP
mdefine_line|#define PIXFORMAT_8BPP&t;&t;0
DECL|macro|PIXFORMAT_16BPP
mdefine_line|#define PIXFORMAT_16BPP&t;&t;1
DECL|macro|PIXFORMAT_24BPP
mdefine_line|#define PIXFORMAT_24BPP&t;&t;2
DECL|macro|VISUALID_256
mdefine_line|#define VISUALID_256&t;&t;1
DECL|macro|VISUALID_64K
mdefine_line|#define VISUALID_64K&t;&t;2
DECL|macro|VISUALID_16M
mdefine_line|#define VISUALID_16M&t;&t;4
DECL|macro|VISUALID_32K
mdefine_line|#define VISUALID_32K&t;&t;6
DECL|macro|FUNC_CTL
mdefine_line|#define FUNC_CTL&t;&t;0x3c
DECL|macro|FUNC_CTL_EXTREGENBL
mdefine_line|#define FUNC_CTL_EXTREGENBL&t;&t;0x80&t;/* enable access to 0xbcxxx&t;&t;*/
DECL|macro|BIU_BM_CONTROL
mdefine_line|#define BIU_BM_CONTROL&t;&t;0x3e
DECL|macro|BIU_BM_CONTROL_ENABLE
mdefine_line|#define BIU_BM_CONTROL_ENABLE&t;&t;0x01&t;/* enable bus-master&t;&t;&t;*/
DECL|macro|BIU_BM_CONTROL_BURST
mdefine_line|#define BIU_BM_CONTROL_BURST&t;&t;0x02&t;/* enable burst&t;&t;&t;&t;*/
DECL|macro|BIU_BM_CONTROL_BACK2BACK
mdefine_line|#define BIU_BM_CONTROL_BACK2BACK&t;0x04&t;/* enable back to back&t;&t;&t;*/
DECL|macro|X_V2_VID_MEM_START
mdefine_line|#define X_V2_VID_MEM_START&t;0x40
DECL|macro|X_V2_VID_SRC_WIDTH
mdefine_line|#define X_V2_VID_SRC_WIDTH&t;0x43
DECL|macro|X_V2_X_START
mdefine_line|#define X_V2_X_START&t;&t;0x45
DECL|macro|X_V2_X_END
mdefine_line|#define X_V2_X_END&t;&t;0x47
DECL|macro|X_V2_Y_START
mdefine_line|#define X_V2_Y_START&t;&t;0x49
DECL|macro|X_V2_Y_END
mdefine_line|#define X_V2_Y_END&t;&t;0x4b
DECL|macro|X_V2_VID_SRC_WIN_WIDTH
mdefine_line|#define X_V2_VID_SRC_WIN_WIDTH&t;0x4d
DECL|macro|Y_V2_DDA_X_INC
mdefine_line|#define Y_V2_DDA_X_INC&t;&t;0x43
DECL|macro|Y_V2_DDA_Y_INC
mdefine_line|#define Y_V2_DDA_Y_INC&t;&t;0x47
DECL|macro|Y_V2_VID_FIFO_CTL
mdefine_line|#define Y_V2_VID_FIFO_CTL&t;0x49
DECL|macro|Y_V2_VID_FMT
mdefine_line|#define Y_V2_VID_FMT&t;&t;0x4b
DECL|macro|Y_V2_VID_DISP_CTL1
mdefine_line|#define Y_V2_VID_DISP_CTL1&t;0x4c
DECL|macro|Y_V2_VID_FIFO_CTL1
mdefine_line|#define Y_V2_VID_FIFO_CTL1&t;0x4d
DECL|macro|J_X2_VID_MEM_START
mdefine_line|#define J_X2_VID_MEM_START&t;0x40
DECL|macro|J_X2_VID_SRC_WIDTH
mdefine_line|#define J_X2_VID_SRC_WIDTH&t;0x43
DECL|macro|J_X2_X_START
mdefine_line|#define J_X2_X_START&t;&t;0x47
DECL|macro|J_X2_X_END
mdefine_line|#define J_X2_X_END&t;&t;0x49
DECL|macro|J_X2_Y_START
mdefine_line|#define J_X2_Y_START&t;&t;0x4b
DECL|macro|J_X2_Y_END
mdefine_line|#define J_X2_Y_END&t;&t;0x4d
DECL|macro|J_X2_VID_SRC_WIN_WIDTH
mdefine_line|#define J_X2_VID_SRC_WIN_WIDTH&t;0x4f
DECL|macro|K_X2_DDA_X_INIT
mdefine_line|#define K_X2_DDA_X_INIT&t;&t;0x40
DECL|macro|K_X2_DDA_X_INC
mdefine_line|#define K_X2_DDA_X_INC&t;&t;0x42
DECL|macro|K_X2_DDA_Y_INIT
mdefine_line|#define K_X2_DDA_Y_INIT&t;&t;0x44
DECL|macro|K_X2_DDA_Y_INC
mdefine_line|#define K_X2_DDA_Y_INC&t;&t;0x46
DECL|macro|K_X2_VID_FMT
mdefine_line|#define K_X2_VID_FMT&t;&t;0x48
DECL|macro|K_X2_VID_DISP_CTL1
mdefine_line|#define K_X2_VID_DISP_CTL1&t;0x49
DECL|macro|K_CAP_X2_CTL1
mdefine_line|#define K_CAP_X2_CTL1&t;&t;0x49
DECL|macro|CAP_X_START
mdefine_line|#define CAP_X_START&t;&t;0x60
DECL|macro|CAP_X_END
mdefine_line|#define CAP_X_END&t;&t;0x62
DECL|macro|CAP_Y_START
mdefine_line|#define CAP_Y_START&t;&t;0x64
DECL|macro|CAP_Y_END
mdefine_line|#define CAP_Y_END&t;&t;0x66
DECL|macro|CAP_DDA_X_INIT
mdefine_line|#define CAP_DDA_X_INIT&t;&t;0x68
DECL|macro|CAP_DDA_X_INC
mdefine_line|#define CAP_DDA_X_INC&t;&t;0x6a
DECL|macro|CAP_DDA_Y_INIT
mdefine_line|#define CAP_DDA_Y_INIT&t;&t;0x6c
DECL|macro|CAP_DDA_Y_INC
mdefine_line|#define CAP_DDA_Y_INC&t;&t;0x6e
DECL|macro|MEM_CTL1
mdefine_line|#define MEM_CTL1&t;&t;0x71
DECL|macro|MEM_CTL2
mdefine_line|#define MEM_CTL2&t;&t;0x72
DECL|macro|MEM_CTL2_SIZE_2MB
mdefine_line|#define MEM_CTL2_SIZE_2MB&t;&t;0x01
DECL|macro|MEM_CTL2_SIZE_4MB
mdefine_line|#define MEM_CTL2_SIZE_4MB&t;&t;0x02
DECL|macro|MEM_CTL2_SIZE_MASK
mdefine_line|#define MEM_CTL2_SIZE_MASK&t;&t;0x03
DECL|macro|MEM_CTL2_64BIT
mdefine_line|#define MEM_CTL2_64BIT&t;&t;&t;0x04
DECL|macro|EXT_FIFO_CTL
mdefine_line|#define EXT_FIFO_CTL&t;&t;0x74
DECL|macro|CAP_PIP_X_START
mdefine_line|#define CAP_PIP_X_START&t;&t;0x80
DECL|macro|CAP_PIP_X_END
mdefine_line|#define CAP_PIP_X_END&t;&t;0x82
DECL|macro|CAP_PIP_Y_START
mdefine_line|#define CAP_PIP_Y_START&t;&t;0x84
DECL|macro|CAP_PIP_Y_END
mdefine_line|#define CAP_PIP_Y_END&t;&t;0x86
DECL|macro|CAP_NEW_CTL1
mdefine_line|#define CAP_NEW_CTL1&t;&t;0x88
DECL|macro|CAP_NEW_CTL2
mdefine_line|#define CAP_NEW_CTL2&t;&t;0x89
DECL|macro|BM_CTRL0
mdefine_line|#define BM_CTRL0&t;&t;0x9c
DECL|macro|BM_CTRL1
mdefine_line|#define BM_CTRL1&t;&t;0x9d
DECL|macro|CAP_MODE1
mdefine_line|#define CAP_MODE1&t;&t;0xa4
DECL|macro|CAP_MODE1_8BIT
mdefine_line|#define CAP_MODE1_8BIT&t;&t;&t;0x01&t;/* enable 8bit capture mode&t;&t;*/
DECL|macro|CAP_MODE1_CCIR656
mdefine_line|#define CAP_MODE1_CCIR656&t;&t;0x02&t;/* CCIR656 mode&t;&t;&t;&t;*/
DECL|macro|CAP_MODE1_IGNOREVGT
mdefine_line|#define CAP_MODE1_IGNOREVGT&t;&t;0x04&t;/* ignore VGT&t;&t;&t;&t;*/
DECL|macro|CAP_MODE1_ALTFIFO
mdefine_line|#define CAP_MODE1_ALTFIFO&t;&t;0x10&t;/* use alternate FIFO for capture&t;*/
DECL|macro|CAP_MODE1_SWAPUV
mdefine_line|#define CAP_MODE1_SWAPUV&t;&t;0x20&t;/* swap UV bytes&t;&t;&t;*/
DECL|macro|CAP_MODE1_MIRRORY
mdefine_line|#define CAP_MODE1_MIRRORY&t;&t;0x40&t;/* mirror vertically&t;&t;&t;*/
DECL|macro|CAP_MODE1_MIRRORX
mdefine_line|#define CAP_MODE1_MIRRORX&t;&t;0x80&t;/* mirror horizontally&t;&t;&t;*/
DECL|macro|DCLK_MULT
mdefine_line|#define DCLK_MULT&t;&t;0xb0
DECL|macro|DCLK_DIV
mdefine_line|#define DCLK_DIV&t;&t;0xb1
DECL|macro|MCLK_MULT
mdefine_line|#define MCLK_MULT&t;&t;0xb2
DECL|macro|MCLK_DIV
mdefine_line|#define MCLK_DIV&t;&t;0xb3
DECL|macro|CAP_MODE2
mdefine_line|#define CAP_MODE2&t;&t;0xa5
DECL|macro|Y_TV_CTL
mdefine_line|#define Y_TV_CTL&t;&t;0xae
DECL|macro|EXT_MEM_START
mdefine_line|#define EXT_MEM_START&t;&t;0xc0&t;&t;/* ext start address 21 bits&t;&t;*/
DECL|macro|HOR_PHASE_SHIFT
mdefine_line|#define HOR_PHASE_SHIFT&t;&t;0xc2&t;&t;/* high 3 bits&t;&t;&t;&t;*/
DECL|macro|EXT_SRC_WIDTH
mdefine_line|#define EXT_SRC_WIDTH&t;&t;0xc3&t;&t;/* ext offset phase  10 bits&t;&t;*/
DECL|macro|EXT_SRC_HEIGHT
mdefine_line|#define EXT_SRC_HEIGHT&t;&t;0xc4&t;&t;/* high 6 bits&t;&t;&t;&t;*/
DECL|macro|EXT_X_START
mdefine_line|#define EXT_X_START&t;&t;0xc5&t;&t;/* ext-&gt;screen, 16 bits&t;&t;&t;*/
DECL|macro|EXT_X_END
mdefine_line|#define EXT_X_END&t;&t;0xc7&t;&t;/* ext-&gt;screen, 16 bits&t;&t;&t;*/
DECL|macro|EXT_Y_START
mdefine_line|#define EXT_Y_START&t;&t;0xc9&t;&t;/* ext-&gt;screen, 16 bits&t;&t;&t;*/
DECL|macro|EXT_Y_END
mdefine_line|#define EXT_Y_END&t;&t;0xcb&t;&t;/* ext-&gt;screen, 16 bits&t;&t;&t;*/
DECL|macro|EXT_SRC_WIN_WIDTH
mdefine_line|#define EXT_SRC_WIN_WIDTH&t;0xcd&t;&t;/* 8 bits&t;&t;&t;&t;*/
DECL|macro|EXT_COLOUR_COMPARE
mdefine_line|#define EXT_COLOUR_COMPARE&t;0xce&t;&t;/* 24 bits&t;&t;&t;&t;*/
DECL|macro|EXT_DDA_X_INIT
mdefine_line|#define EXT_DDA_X_INIT&t;&t;0xd1&t;&t;/* ext-&gt;screen 16 bits&t;&t;&t;*/
DECL|macro|EXT_DDA_X_INC
mdefine_line|#define EXT_DDA_X_INC&t;&t;0xd3&t;&t;/* ext-&gt;screen 16 bits&t;&t;&t;*/
DECL|macro|EXT_DDA_Y_INIT
mdefine_line|#define EXT_DDA_Y_INIT&t;&t;0xd5&t;&t;/* ext-&gt;screen 16 bits&t;&t;&t;*/
DECL|macro|EXT_DDA_Y_INC
mdefine_line|#define EXT_DDA_Y_INC&t;&t;0xd7&t;&t;/* ext-&gt;screen 16 bits&t;&t;&t;*/
DECL|macro|EXT_VID_FIFO_CTL
mdefine_line|#define EXT_VID_FIFO_CTL&t;0xd9
DECL|macro|EXT_VID_FMT
mdefine_line|#define EXT_VID_FMT&t;&t;0xdb
DECL|macro|EXT_VID_FMT_YUV422
mdefine_line|#define EXT_VID_FMT_YUV422&t;&t;0x00&t;/* formats - does this cause conversion? */
DECL|macro|EXT_VID_FMT_RGB555
mdefine_line|#define EXT_VID_FMT_RGB555&t;&t;0x01
DECL|macro|EXT_VID_FMT_RGB565
mdefine_line|#define EXT_VID_FMT_RGB565&t;&t;0x02
DECL|macro|EXT_VID_FMT_RGB888_24
mdefine_line|#define EXT_VID_FMT_RGB888_24&t;&t;0x03
DECL|macro|EXT_VID_FMT_RGB888_32
mdefine_line|#define EXT_VID_FMT_RGB888_32&t;&t;0x04
DECL|macro|EXT_VID_FMT_DUP_PIX_ZOON
mdefine_line|#define EXT_VID_FMT_DUP_PIX_ZOON&t;0x08&t;/* duplicate pixel zoom&t;&t;&t;*/
DECL|macro|EXT_VID_FMT_MOD_3RD_PIX
mdefine_line|#define EXT_VID_FMT_MOD_3RD_PIX&t;&t;0x20&t;/* modify 3rd duplicated pixel&t;&t;*/
DECL|macro|EXT_VID_FMT_DBL_H_PIX
mdefine_line|#define EXT_VID_FMT_DBL_H_PIX&t;&t;0x40&t;/* double horiz pixels&t;&t;&t;*/
DECL|macro|EXT_VID_FMT_UV128
mdefine_line|#define EXT_VID_FMT_UV128&t;&t;0x80&t;/* UV data offset by 128&t;&t;*/
DECL|macro|EXT_VID_DISP_CTL1
mdefine_line|#define EXT_VID_DISP_CTL1&t;0xdc
DECL|macro|EXT_VID_DISP_CTL1_INTRAM
mdefine_line|#define EXT_VID_DISP_CTL1_INTRAM&t;0x01&t;/* video pixels go to internal RAM&t;*/
DECL|macro|EXT_VID_DISP_CTL1_IGNORE_CCOMP
mdefine_line|#define EXT_VID_DISP_CTL1_IGNORE_CCOMP&t;0x02&t;/* ignore colour compare registers&t;*/
DECL|macro|EXT_VID_DISP_CTL1_NOCLIP
mdefine_line|#define EXT_VID_DISP_CTL1_NOCLIP&t;0x04&t;/* do not clip to 16235,16240&t;&t;*/
DECL|macro|EXT_VID_DISP_CTL1_UV_AVG
mdefine_line|#define EXT_VID_DISP_CTL1_UV_AVG&t;0x08&t;/* U/V data is averaged&t;&t;&t;*/
DECL|macro|EXT_VID_DISP_CTL1_Y128
mdefine_line|#define EXT_VID_DISP_CTL1_Y128&t;&t;0x10&t;/* Y data offset by 128&t;&t;&t;*/
DECL|macro|EXT_VID_DISP_CTL1_VINTERPOL_OFF
mdefine_line|#define EXT_VID_DISP_CTL1_VINTERPOL_OFF&t;0x20&t;/* vertical interpolation off&t;&t;*/
DECL|macro|EXT_VID_DISP_CTL1_FULL_WIN
mdefine_line|#define EXT_VID_DISP_CTL1_FULL_WIN&t;0x40&t;/* video out window full&t;&t;*/
DECL|macro|EXT_VID_DISP_CTL1_ENABLE_WINDOW
mdefine_line|#define EXT_VID_DISP_CTL1_ENABLE_WINDOW&t;0x80&t;/* enable video window&t;&t;&t;*/
DECL|macro|EXT_VID_FIFO_CTL1
mdefine_line|#define EXT_VID_FIFO_CTL1&t;0xdd
DECL|macro|VFAC_CTL1
mdefine_line|#define VFAC_CTL1&t;&t;0xe8
DECL|macro|VFAC_CTL1_CAPTURE
mdefine_line|#define VFAC_CTL1_CAPTURE&t;&t;0x01&t;/* capture enable&t;&t;&t;*/
DECL|macro|VFAC_CTL1_VFAC_ENABLE
mdefine_line|#define VFAC_CTL1_VFAC_ENABLE&t;&t;0x02&t;/* vfac enable&t;&t;&t;&t;*/
DECL|macro|VFAC_CTL1_FREEZE_CAPTURE
mdefine_line|#define VFAC_CTL1_FREEZE_CAPTURE&t;0x04&t;/* freeze capture&t;&t;&t;*/
DECL|macro|VFAC_CTL1_FREEZE_CAPTURE_SYNC
mdefine_line|#define VFAC_CTL1_FREEZE_CAPTURE_SYNC&t;0x08&t;/* sync freeze capture&t;&t;&t;*/
DECL|macro|VFAC_CTL1_VALIDFRAME_SRC
mdefine_line|#define VFAC_CTL1_VALIDFRAME_SRC&t;0x10&t;/* select valid frame source&t;&t;*/
DECL|macro|VFAC_CTL1_PHILIPS
mdefine_line|#define VFAC_CTL1_PHILIPS&t;&t;0x40&t;/* select Philips mode&t;&t;&t;*/
DECL|macro|VFAC_CTL1_MODVINTERPOLCLK
mdefine_line|#define VFAC_CTL1_MODVINTERPOLCLK&t;0x80&t;/* modify vertical interpolation clocl&t;*/
DECL|macro|VFAC_CTL2
mdefine_line|#define VFAC_CTL2&t;&t;0xe9
DECL|macro|VFAC_CTL2_INVERT_VIDDATAVALID
mdefine_line|#define VFAC_CTL2_INVERT_VIDDATAVALID&t;0x01&t;/* invert video data valid&t;&t;*/
DECL|macro|VFAC_CTL2_INVERT_GRAPHREADY
mdefine_line|#define VFAC_CTL2_INVERT_GRAPHREADY&t;0x02&t;/* invert graphic ready output sig&t;*/
DECL|macro|VFAC_CTL2_INVERT_DATACLK
mdefine_line|#define VFAC_CTL2_INVERT_DATACLK&t;0x04&t;/* invert data clock signal&t;&t;*/
DECL|macro|VFAC_CTL2_INVERT_HSYNC
mdefine_line|#define VFAC_CTL2_INVERT_HSYNC&t;&t;0x08&t;/* invert hsync input&t;&t;&t;*/
DECL|macro|VFAC_CTL2_INVERT_VSYNC
mdefine_line|#define VFAC_CTL2_INVERT_VSYNC&t;&t;0x10&t;/* invert vsync input&t;&t;&t;*/
DECL|macro|VFAC_CTL2_INVERT_FRAME
mdefine_line|#define VFAC_CTL2_INVERT_FRAME&t;&t;0x20&t;/* invert frame odd/even input&t;&t;*/
DECL|macro|VFAC_CTL2_INVERT_BLANK
mdefine_line|#define VFAC_CTL2_INVERT_BLANK&t;&t;0x40&t;/* invert blank output&t;&t;&t;*/
DECL|macro|VFAC_CTL2_INVERT_OVSYNC
mdefine_line|#define VFAC_CTL2_INVERT_OVSYNC&t;&t;0x80&t;/* invert other vsync input&t;&t;*/
DECL|macro|VFAC_CTL3
mdefine_line|#define VFAC_CTL3&t;&t;0xea
DECL|macro|VFAC_CTL3_CAP_IRQ
mdefine_line|#define VFAC_CTL3_CAP_IRQ&t;&t;0x40&t;/* enable capture interrupt&t;&t;*/
DECL|macro|CAP_MEM_START
mdefine_line|#define CAP_MEM_START&t;&t;0xeb&t;&t;/* 18 bits&t;&t;&t;&t;*/
DECL|macro|CAP_MAP_WIDTH
mdefine_line|#define CAP_MAP_WIDTH&t;&t;0xed&t;&t;/* high 6 bits&t;&t;&t;&t;*/
DECL|macro|CAP_PITCH
mdefine_line|#define CAP_PITCH&t;&t;0xee&t;&t;/* 8 bits&t;&t;&t;&t;*/
DECL|macro|CAP_CTL_MISC
mdefine_line|#define CAP_CTL_MISC&t;&t;0xef
DECL|macro|CAP_CTL_MISC_HDIV
mdefine_line|#define CAP_CTL_MISC_HDIV&t;&t;0x01
DECL|macro|CAP_CTL_MISC_HDIV4
mdefine_line|#define CAP_CTL_MISC_HDIV4&t;&t;0x02
DECL|macro|CAP_CTL_MISC_ODDEVEN
mdefine_line|#define CAP_CTL_MISC_ODDEVEN&t;&t;0x04
DECL|macro|CAP_CTL_MISC_HSYNCDIV2
mdefine_line|#define CAP_CTL_MISC_HSYNCDIV2&t;&t;0x08
DECL|macro|CAP_CTL_MISC_SYNCTZHIGH
mdefine_line|#define CAP_CTL_MISC_SYNCTZHIGH&t;&t;0x10
DECL|macro|CAP_CTL_MISC_SYNCTZOR
mdefine_line|#define CAP_CTL_MISC_SYNCTZOR&t;&t;0x20
DECL|macro|CAP_CTL_MISC_DISPUSED
mdefine_line|#define CAP_CTL_MISC_DISPUSED&t;&t;0x80
DECL|macro|REG_BANK
mdefine_line|#define REG_BANK&t;&t;0xfa
DECL|macro|REG_BANK_X
mdefine_line|#define REG_BANK_X&t;&t;&t;0x00
DECL|macro|REG_BANK_Y
mdefine_line|#define REG_BANK_Y&t;&t;&t;0x01
DECL|macro|REG_BANK_W
mdefine_line|#define REG_BANK_W&t;&t;&t;0x02
DECL|macro|REG_BANK_T
mdefine_line|#define REG_BANK_T&t;&t;&t;0x03
DECL|macro|REG_BANK_J
mdefine_line|#define REG_BANK_J&t;&t;&t;0x04
DECL|macro|REG_BANK_K
mdefine_line|#define REG_BANK_K&t;&t;&t;0x05
multiline_comment|/*&n; * Bus-master&n; */
DECL|macro|BM_VID_ADDR_LOW
mdefine_line|#define BM_VID_ADDR_LOW&t;&t;0xbc040
DECL|macro|BM_VID_ADDR_HIGH
mdefine_line|#define BM_VID_ADDR_HIGH&t;0xbc044
DECL|macro|BM_ADDRESS_LOW
mdefine_line|#define BM_ADDRESS_LOW&t;&t;0xbc080
DECL|macro|BM_ADDRESS_HIGH
mdefine_line|#define BM_ADDRESS_HIGH&t;&t;0xbc084
DECL|macro|BM_LENGTH
mdefine_line|#define BM_LENGTH&t;&t;0xbc088
DECL|macro|BM_CONTROL
mdefine_line|#define BM_CONTROL&t;&t;0xbc08c
DECL|macro|BM_CONTROL_ENABLE
mdefine_line|#define BM_CONTROL_ENABLE&t;&t;0x01&t;/* enable transfer&t;&t;&t;*/
DECL|macro|BM_CONTROL_IRQEN
mdefine_line|#define BM_CONTROL_IRQEN&t;&t;0x02&t;/* enable IRQ at end of transfer&t;*/
DECL|macro|BM_CONTROL_INIT
mdefine_line|#define BM_CONTROL_INIT&t;&t;&t;0x04&t;/* initialise status &amp; count&t;&t;*/
DECL|macro|BM_COUNT
mdefine_line|#define BM_COUNT&t;&t;0xbc090&t;&t;/* read-only&t;&t;&t;&t;*/
multiline_comment|/*&n; * Graphics Co-processor&n; */
DECL|macro|CO_CMD_L_PATTERN_FGCOL
mdefine_line|#define CO_CMD_L_PATTERN_FGCOL&t;0x8000
DECL|macro|CO_CMD_L_INC_LEFT
mdefine_line|#define CO_CMD_L_INC_LEFT&t;0x0004
DECL|macro|CO_CMD_L_INC_UP
mdefine_line|#define CO_CMD_L_INC_UP&t;&t;0x0002
DECL|macro|CO_CMD_H_SRC_PIXMAP
mdefine_line|#define CO_CMD_H_SRC_PIXMAP&t;0x2000
DECL|macro|CO_CMD_H_BLITTER
mdefine_line|#define CO_CMD_H_BLITTER&t;0x0800
DECL|macro|CO_REG_CONTROL
mdefine_line|#define CO_REG_CONTROL&t;&t;0xbf011
DECL|macro|CO_REG_SRC_WIDTH
mdefine_line|#define CO_REG_SRC_WIDTH&t;0xbf018
DECL|macro|CO_REG_PIX_FORMAT
mdefine_line|#define CO_REG_PIX_FORMAT&t;0xbf01c
DECL|macro|CO_REG_FORE_MIX
mdefine_line|#define CO_REG_FORE_MIX&t;&t;0xbf048
DECL|macro|CO_REG_FOREGROUND
mdefine_line|#define CO_REG_FOREGROUND&t;0xbf058
DECL|macro|CO_REG_WIDTH
mdefine_line|#define CO_REG_WIDTH&t;&t;0xbf060
DECL|macro|CO_REG_HEIGHT
mdefine_line|#define CO_REG_HEIGHT&t;&t;0xbf062
DECL|macro|CO_REG_X_PHASE
mdefine_line|#define CO_REG_X_PHASE&t;&t;0xbf078
DECL|macro|CO_REG_CMD_L
mdefine_line|#define CO_REG_CMD_L&t;&t;0xbf07c
DECL|macro|CO_REG_CMD_H
mdefine_line|#define CO_REG_CMD_H&t;&t;0xbf07e
DECL|macro|CO_REG_SRC_PTR
mdefine_line|#define CO_REG_SRC_PTR&t;&t;0xbf170
DECL|macro|CO_REG_DEST_PTR
mdefine_line|#define CO_REG_DEST_PTR&t;&t;0xbf178
DECL|macro|CO_REG_DEST_WIDTH
mdefine_line|#define CO_REG_DEST_WIDTH&t;0xbf218
multiline_comment|/*&n; * Private structure&n; */
r_struct
id|cfb_info
suffix:semicolon
DECL|struct|cyberpro_info
r_struct
id|cyberpro_info
(brace
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|regs
r_int
r_char
op_star
id|regs
suffix:semicolon
DECL|member|fb
r_char
op_star
id|fb
suffix:semicolon
DECL|member|dev_name
r_char
id|dev_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|fb_size
r_int
r_int
id|fb_size
suffix:semicolon
multiline_comment|/*&n;&t; * The following is a pointer to be passed into the&n;&t; * functions below.  The modules outside the main&n;&t; * cyber2000fb.c driver have no knowledge as to what&n;&t; * is within this structure.&n;&t; */
DECL|member|info
r_struct
id|cfb_info
op_star
id|info
suffix:semicolon
multiline_comment|/*&n;&t; * Use these to enable the BM or TV registers.  In an SMP&n;&t; * environment, these two function pointers should only be&n;&t; * called from the module_init() or module_exit()&n;&t; * functions.&n;&t; */
DECL|member|enable_extregs
r_void
(paren
op_star
id|enable_extregs
)paren
(paren
r_struct
id|cfb_info
op_star
)paren
suffix:semicolon
DECL|member|disable_extregs
r_void
(paren
op_star
id|disable_extregs
)paren
(paren
r_struct
id|cfb_info
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Note! Writing to the Cyber20x0 registers from an interrupt&n; * routine is definitely a bad idea atm.&n; */
r_int
id|cyber2000fb_attach
c_func
(paren
r_struct
id|cyberpro_info
op_star
id|info
comma
r_int
id|idx
)paren
suffix:semicolon
r_void
id|cyber2000fb_detach
c_func
(paren
r_int
id|idx
)paren
suffix:semicolon
eof
