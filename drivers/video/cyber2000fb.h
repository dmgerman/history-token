multiline_comment|/*&n; *  linux/drivers/video/cyber2000fb.h&n; *&n; *  Copyright (C) 1998-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Integraphics Cyber2000 frame buffer device&n; */
macro_line|#include &lt;linux/config.h&gt;
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
r_extern
r_void
id|printascii
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
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
DECL|macro|PIXFORMAT_8BPP
mdefine_line|#define PIXFORMAT_8BPP&t;&t;0
DECL|macro|PIXFORMAT_16BPP
mdefine_line|#define PIXFORMAT_16BPP&t;&t;1
DECL|macro|PIXFORMAT_24BPP
mdefine_line|#define PIXFORMAT_24BPP&t;&t;2
DECL|macro|EXT_CRT_IRQ
mdefine_line|#define EXT_CRT_IRQ&t;&t;0x12
DECL|macro|EXT_CRT_IRQ_ENABLE
mdefine_line|#define EXT_CRT_IRQ_ENABLE&t;&t;0x01
DECL|macro|EXT_CRT_IRQ_ACT_HIGH
mdefine_line|#define EXT_CRT_IRQ_ACT_HIGH&t;&t;0x04
DECL|macro|EXT_CRT_TEST
mdefine_line|#define EXT_CRT_TEST&t;&t;0x13
DECL|macro|EXT_SYNC_CTL
mdefine_line|#define EXT_SYNC_CTL&t;&t;0x16
DECL|macro|EXT_SYNC_CTL_HS_NORMAL
mdefine_line|#define EXT_SYNC_CTL_HS_NORMAL&t;&t;0x00
DECL|macro|EXT_SYNC_CTL_HS_0
mdefine_line|#define EXT_SYNC_CTL_HS_0&t;&t;0x01
DECL|macro|EXT_SYNC_CTL_HS_1
mdefine_line|#define EXT_SYNC_CTL_HS_1&t;&t;0x02
DECL|macro|EXT_SYNC_CTL_HS_HSVS
mdefine_line|#define EXT_SYNC_CTL_HS_HSVS&t;&t;0x03
DECL|macro|EXT_SYNC_CTL_VS_NORMAL
mdefine_line|#define EXT_SYNC_CTL_VS_NORMAL&t;&t;0x00
DECL|macro|EXT_SYNC_CTL_VS_0
mdefine_line|#define EXT_SYNC_CTL_VS_0&t;&t;0x04
DECL|macro|EXT_SYNC_CTL_VS_1
mdefine_line|#define EXT_SYNC_CTL_VS_1&t;&t;0x08
DECL|macro|EXT_SYNC_CTL_VS_COMP
mdefine_line|#define EXT_SYNC_CTL_VS_COMP&t;&t;0x0c
DECL|macro|EXT_BUS_CTL
mdefine_line|#define EXT_BUS_CTL&t;&t;0x30
DECL|macro|EXT_BUS_CTL_LIN_1MB
mdefine_line|#define EXT_BUS_CTL_LIN_1MB&t;&t;0x00
DECL|macro|EXT_BUS_CTL_LIN_2MB
mdefine_line|#define EXT_BUS_CTL_LIN_2MB&t;&t;0x01
DECL|macro|EXT_BUS_CTL_LIN_4MB
mdefine_line|#define EXT_BUS_CTL_LIN_4MB&t;&t;0x02
DECL|macro|EXT_BUS_CTL_ZEROWAIT
mdefine_line|#define EXT_BUS_CTL_ZEROWAIT&t;&t;0x04
DECL|macro|EXT_BUS_CTL_PCIBURST
mdefine_line|#define EXT_BUS_CTL_PCIBURST&t;&t;0x20
DECL|macro|EXT_SEG_WRITE_PTR
mdefine_line|#define EXT_SEG_WRITE_PTR&t;0x31
DECL|macro|EXT_SEG_READ_PTR
mdefine_line|#define EXT_SEG_READ_PTR&t;0x32
DECL|macro|EXT_BIU_MISC
mdefine_line|#define EXT_BIU_MISC&t;&t;0x33
DECL|macro|EXT_BIU_MISC_LIN_ENABLE
mdefine_line|#define EXT_BIU_MISC_LIN_ENABLE&t;&t;0x01
DECL|macro|EXT_BIU_MISC_COP_ENABLE
mdefine_line|#define EXT_BIU_MISC_COP_ENABLE&t;&t;0x04
DECL|macro|EXT_BIU_MISC_COP_BFC
mdefine_line|#define EXT_BIU_MISC_COP_BFC&t;&t;0x08
DECL|macro|EXT_FUNC_CTL
mdefine_line|#define EXT_FUNC_CTL&t;&t;0x3c
DECL|macro|EXT_FUNC_CTL_EXTREGENBL
mdefine_line|#define EXT_FUNC_CTL_EXTREGENBL&t;&t;0x80&t;/* enable access to 0xbcxxx&t;&t;*/
DECL|macro|PCI_BM_CTL
mdefine_line|#define PCI_BM_CTL&t;&t;0x3e
DECL|macro|PCI_BM_CTL_ENABLE
mdefine_line|#define PCI_BM_CTL_ENABLE&t;&t;0x01&t;/* enable bus-master&t;&t;&t;*/
DECL|macro|PCI_BM_CTL_BURST
mdefine_line|#define PCI_BM_CTL_BURST&t;&t;0x02&t;/* enable burst&t;&t;&t;&t;*/
DECL|macro|PCI_BM_CTL_BACK2BACK
mdefine_line|#define PCI_BM_CTL_BACK2BACK&t;&t;0x04&t;/* enable back to back&t;&t;&t;*/
DECL|macro|PCI_BM_CTL_DUMMY
mdefine_line|#define PCI_BM_CTL_DUMMY&t;&t;0x08&t;/* insert dummy cycle&t;&t;&t;*/
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
DECL|macro|CURS_H_START
mdefine_line|#define CURS_H_START&t;&t;0x50
DECL|macro|CURS_H_PRESET
mdefine_line|#define CURS_H_PRESET&t;&t;0x52
DECL|macro|CURS_V_START
mdefine_line|#define CURS_V_START&t;&t;0x53
DECL|macro|CURS_V_PRESET
mdefine_line|#define CURS_V_PRESET&t;&t;0x55
DECL|macro|CURS_CTL
mdefine_line|#define CURS_CTL&t;&t;0x56
DECL|macro|EXT_ATTRIB_CTL
mdefine_line|#define EXT_ATTRIB_CTL&t;&t;0x57
DECL|macro|EXT_ATTRIB_CTL_EXT
mdefine_line|#define EXT_ATTRIB_CTL_EXT&t;&t;0x01
DECL|macro|EXT_OVERSCAN_RED
mdefine_line|#define EXT_OVERSCAN_RED&t;0x58
DECL|macro|EXT_OVERSCAN_GREEN
mdefine_line|#define EXT_OVERSCAN_GREEN&t;0x59
DECL|macro|EXT_OVERSCAN_BLUE
mdefine_line|#define EXT_OVERSCAN_BLUE&t;0x5a
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
DECL|macro|EXT_MEM_CTL0
mdefine_line|#define EXT_MEM_CTL0&t;&t;0x70
DECL|macro|EXT_MEM_CTL0_7CLK
mdefine_line|#define EXT_MEM_CTL0_7CLK&t;&t;0x01
DECL|macro|EXT_MEM_CTL0_RAS_1
mdefine_line|#define EXT_MEM_CTL0_RAS_1&t;&t;0x02
DECL|macro|EXT_MEM_CTL0_RAS2CAS_1
mdefine_line|#define EXT_MEM_CTL0_RAS2CAS_1&t;&t;0x04
DECL|macro|EXT_MEM_CTL0_MULTCAS
mdefine_line|#define EXT_MEM_CTL0_MULTCAS&t;&t;0x08
DECL|macro|EXT_MEM_CTL0_ASYM
mdefine_line|#define EXT_MEM_CTL0_ASYM&t;&t;0x10
DECL|macro|EXT_MEM_CTL0_CAS1ON
mdefine_line|#define EXT_MEM_CTL0_CAS1ON&t;&t;0x20
DECL|macro|EXT_MEM_CTL0_FIFOFLUSH
mdefine_line|#define EXT_MEM_CTL0_FIFOFLUSH&t;&t;0x40
DECL|macro|EXT_MEM_CTL0_SEQRESET
mdefine_line|#define EXT_MEM_CTL0_SEQRESET&t;&t;0x80
DECL|macro|EXT_MEM_CTL1
mdefine_line|#define EXT_MEM_CTL1&t;&t;0x71
DECL|macro|EXT_MEM_CTL1_PAR
mdefine_line|#define EXT_MEM_CTL1_PAR&t;&t;0x00
DECL|macro|EXT_MEM_CTL1_SERPAR
mdefine_line|#define EXT_MEM_CTL1_SERPAR&t;&t;0x01
DECL|macro|EXT_MEM_CTL1_SER
mdefine_line|#define EXT_MEM_CTL1_SER&t;&t;0x03
DECL|macro|EXT_MEM_CTL1_SYNC
mdefine_line|#define EXT_MEM_CTL1_SYNC&t;&t;0x04
DECL|macro|EXT_MEM_CTL1_VRAM
mdefine_line|#define EXT_MEM_CTL1_VRAM&t;&t;0x08
DECL|macro|EXT_MEM_CTL1_4K_REFRESH
mdefine_line|#define EXT_MEM_CTL1_4K_REFRESH&t;&t;0x10
DECL|macro|EXT_MEM_CTL1_256Kx4
mdefine_line|#define EXT_MEM_CTL1_256Kx4&t;&t;0x00
DECL|macro|EXT_MEM_CTL1_512Kx8
mdefine_line|#define EXT_MEM_CTL1_512Kx8&t;&t;0x40
DECL|macro|EXT_MEM_CTL1_1Mx16
mdefine_line|#define EXT_MEM_CTL1_1Mx16&t;&t;0x60
DECL|macro|EXT_MEM_CTL2
mdefine_line|#define EXT_MEM_CTL2&t;&t;0x72
DECL|macro|MEM_CTL2_SIZE_1MB
mdefine_line|#define MEM_CTL2_SIZE_1MB&t;&t;0x00
DECL|macro|MEM_CTL2_SIZE_2MB
mdefine_line|#define MEM_CTL2_SIZE_2MB&t;&t;0x01
DECL|macro|MEM_CTL2_SIZE_4MB
mdefine_line|#define MEM_CTL2_SIZE_4MB&t;&t;0x02
DECL|macro|MEM_CTL2_SIZE_MASK
mdefine_line|#define MEM_CTL2_SIZE_MASK&t;&t;0x03
DECL|macro|MEM_CTL2_64BIT
mdefine_line|#define MEM_CTL2_64BIT&t;&t;&t;0x04
DECL|macro|EXT_HIDDEN_CTL1
mdefine_line|#define EXT_HIDDEN_CTL1&t;&t;0x73
DECL|macro|EXT_FIFO_CTL
mdefine_line|#define EXT_FIFO_CTL&t;&t;0x74
DECL|macro|EXT_SEQ_MISC
mdefine_line|#define EXT_SEQ_MISC&t;&t;0x77
DECL|macro|EXT_SEQ_MISC_8
mdefine_line|#define EXT_SEQ_MISC_8&t;&t;&t;0x01
DECL|macro|EXT_SEQ_MISC_16_RGB565
mdefine_line|#define EXT_SEQ_MISC_16_RGB565&t;&t;0x02
DECL|macro|EXT_SEQ_MISC_32
mdefine_line|#define EXT_SEQ_MISC_32&t;&t;&t;0x03
DECL|macro|EXT_SEQ_MISC_24_RGB888
mdefine_line|#define EXT_SEQ_MISC_24_RGB888&t;&t;0x04
DECL|macro|EXT_SEQ_MISC_16_RGB555
mdefine_line|#define EXT_SEQ_MISC_16_RGB555&t;&t;0x06
DECL|macro|EXT_SEQ_MISC_8_RGB332
mdefine_line|#define EXT_SEQ_MISC_8_RGB332&t;&t;0x09
DECL|macro|EXT_SEQ_MISC_16_RGB444
mdefine_line|#define EXT_SEQ_MISC_16_RGB444&t;&t;0x0a
DECL|macro|EXT_HIDDEN_CTL4
mdefine_line|#define EXT_HIDDEN_CTL4&t;&t;0x7a
DECL|macro|CURS_MEM_START
mdefine_line|#define CURS_MEM_START&t;&t;0x7e&t;&t;/* bits 23..12 */
DECL|macro|CAP_PIP_X_START
mdefine_line|#define CAP_PIP_X_START&t;&t;0x80
DECL|macro|CAP_PIP_X_END
mdefine_line|#define CAP_PIP_X_END&t;&t;0x82
DECL|macro|CAP_PIP_Y_START
mdefine_line|#define CAP_PIP_Y_START&t;&t;0x84
DECL|macro|CAP_PIP_Y_END
mdefine_line|#define CAP_PIP_Y_END&t;&t;0x86
DECL|macro|EXT_CAP_CTL1
mdefine_line|#define EXT_CAP_CTL1&t;&t;0x88
DECL|macro|EXT_CAP_CTL2
mdefine_line|#define EXT_CAP_CTL2&t;&t;0x89
DECL|macro|EXT_CAP_CTL2_ODDFRAMEIRQ
mdefine_line|#define EXT_CAP_CTL2_ODDFRAMEIRQ&t;0x01
DECL|macro|EXT_CAP_CTL2_ANYFRAMEIRQ
mdefine_line|#define EXT_CAP_CTL2_ANYFRAMEIRQ&t;0x02
DECL|macro|BM_CTRL0
mdefine_line|#define BM_CTRL0&t;&t;0x9c
DECL|macro|BM_CTRL1
mdefine_line|#define BM_CTRL1&t;&t;0x9d
DECL|macro|EXT_CAP_MODE1
mdefine_line|#define EXT_CAP_MODE1&t;&t;0xa4
DECL|macro|EXT_CAP_MODE1_8BIT
mdefine_line|#define EXT_CAP_MODE1_8BIT&t;&t;0x01&t;/* enable 8bit capture mode&t;&t;*/
DECL|macro|EXT_CAP_MODE1_CCIR656
mdefine_line|#define EXT_CAP_MODE1_CCIR656&t;&t;0x02&t;/* CCIR656 mode&t;&t;&t;&t;*/
DECL|macro|EXT_CAP_MODE1_IGNOREVGT
mdefine_line|#define EXT_CAP_MODE1_IGNOREVGT&t;&t;0x04&t;/* ignore VGT&t;&t;&t;&t;*/
DECL|macro|EXT_CAP_MODE1_ALTFIFO
mdefine_line|#define EXT_CAP_MODE1_ALTFIFO&t;&t;0x10&t;/* use alternate FIFO for capture&t;*/
DECL|macro|EXT_CAP_MODE1_SWAPUV
mdefine_line|#define EXT_CAP_MODE1_SWAPUV&t;&t;0x20&t;/* swap UV bytes&t;&t;&t;*/
DECL|macro|EXT_CAP_MODE1_MIRRORY
mdefine_line|#define EXT_CAP_MODE1_MIRRORY&t;&t;0x40&t;/* mirror vertically&t;&t;&t;*/
DECL|macro|EXT_CAP_MODE1_MIRRORX
mdefine_line|#define EXT_CAP_MODE1_MIRRORX&t;&t;0x80&t;/* mirror horizontally&t;&t;&t;*/
DECL|macro|EXT_CAP_MODE2
mdefine_line|#define EXT_CAP_MODE2&t;&t;0xa5
DECL|macro|EXT_CAP_MODE2_CCIRINVOE
mdefine_line|#define EXT_CAP_MODE2_CCIRINVOE&t;&t;0x01
DECL|macro|EXT_CAP_MODE2_CCIRINVVGT
mdefine_line|#define EXT_CAP_MODE2_CCIRINVVGT&t;0x02
DECL|macro|EXT_CAP_MODE2_CCIRINVHGT
mdefine_line|#define EXT_CAP_MODE2_CCIRINVHGT&t;0x04
DECL|macro|EXT_CAP_MODE2_CCIRINVDG
mdefine_line|#define EXT_CAP_MODE2_CCIRINVDG&t;&t;0x08
DECL|macro|EXT_CAP_MODE2_DATEND
mdefine_line|#define EXT_CAP_MODE2_DATEND&t;&t;0x10
DECL|macro|EXT_CAP_MODE2_CCIRDGH
mdefine_line|#define EXT_CAP_MODE2_CCIRDGH&t;&t;0x20
DECL|macro|EXT_CAP_MODE2_FIXSONY
mdefine_line|#define EXT_CAP_MODE2_FIXSONY&t;&t;0x40
DECL|macro|EXT_CAP_MODE2_SYNCFREEZE
mdefine_line|#define EXT_CAP_MODE2_SYNCFREEZE&t;0x80
DECL|macro|EXT_TV_CTL
mdefine_line|#define EXT_TV_CTL&t;&t;0xae
DECL|macro|EXT_DCLK_MULT
mdefine_line|#define EXT_DCLK_MULT&t;&t;0xb0
DECL|macro|EXT_DCLK_DIV
mdefine_line|#define EXT_DCLK_DIV&t;&t;0xb1
DECL|macro|EXT_DCLK_DIV_VFSEL
mdefine_line|#define EXT_DCLK_DIV_VFSEL&t;&t;0x20
DECL|macro|EXT_MCLK_MULT
mdefine_line|#define EXT_MCLK_MULT&t;&t;0xb2
DECL|macro|EXT_MCLK_DIV
mdefine_line|#define EXT_MCLK_DIV&t;&t;0xb3
DECL|macro|EXT_LATCH1
mdefine_line|#define EXT_LATCH1&t;&t;0xb5
DECL|macro|EXT_LATCH1_VAFC_EN
mdefine_line|#define EXT_LATCH1_VAFC_EN&t;&t;0x01&t;/* enable VAFC&t;&t;&t;&t;*/
DECL|macro|EXT_FEATURE
mdefine_line|#define EXT_FEATURE&t;&t;0xb7
DECL|macro|EXT_FEATURE_BUS_MASK
mdefine_line|#define EXT_FEATURE_BUS_MASK&t;&t;0x07&t;/* host bus mask&t;&t;&t;*/
DECL|macro|EXT_FEATURE_BUS_PCI
mdefine_line|#define EXT_FEATURE_BUS_PCI&t;&t;0x00
DECL|macro|EXT_FEATURE_BUS_VL_STD
mdefine_line|#define EXT_FEATURE_BUS_VL_STD&t;&t;0x04
DECL|macro|EXT_FEATURE_BUS_VL_LINEAR
mdefine_line|#define EXT_FEATURE_BUS_VL_LINEAR&t;0x05
DECL|macro|EXT_FEATURE_1682
mdefine_line|#define EXT_FEATURE_1682&t;&t;0x20&t;/* IGS 1682 compatibility&t;&t;*/
DECL|macro|EXT_LATCH2
mdefine_line|#define EXT_LATCH2&t;&t;0xb6
DECL|macro|EXT_LATCH2_I2C_CLKEN
mdefine_line|#define EXT_LATCH2_I2C_CLKEN&t;&t;0x10
DECL|macro|EXT_LATCH2_I2C_CLK
mdefine_line|#define EXT_LATCH2_I2C_CLK&t;&t;0x20
DECL|macro|EXT_LATCH2_I2C_DATEN
mdefine_line|#define EXT_LATCH2_I2C_DATEN&t;&t;0x40
DECL|macro|EXT_LATCH2_I2C_DAT
mdefine_line|#define EXT_LATCH2_I2C_DAT&t;&t;0x80
DECL|macro|EXT_XT_CTL
mdefine_line|#define EXT_XT_CTL&t;&t;0xbe
DECL|macro|EXT_XT_CAP16
mdefine_line|#define EXT_XT_CAP16&t;&t;&t;0x04
DECL|macro|EXT_XT_LINEARFB
mdefine_line|#define EXT_XT_LINEARFB&t;&t;&t;0x08
DECL|macro|EXT_XT_PAL
mdefine_line|#define EXT_XT_PAL&t;&t;&t;0x10
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
DECL|macro|EXT_VID_FMT_RGB8
mdefine_line|#define EXT_VID_FMT_RGB8&t;&t;0x05
DECL|macro|EXT_VID_FMT_RGB4444
mdefine_line|#define EXT_VID_FMT_RGB4444&t;&t;0x06
DECL|macro|EXT_VID_FMT_RGB8T
mdefine_line|#define EXT_VID_FMT_RGB8T&t;&t;0x07
DECL|macro|EXT_VID_FMT_DUP_PIX_ZOON
mdefine_line|#define EXT_VID_FMT_DUP_PIX_ZOON&t;0x08&t;/* duplicate pixel zoom&t;&t;&t;*/
DECL|macro|EXT_VID_FMT_MOD_3RD_PIX
mdefine_line|#define EXT_VID_FMT_MOD_3RD_PIX&t;&t;0x20&t;/* modify 3rd duplicated pixel&t;&t;*/
DECL|macro|EXT_VID_FMT_DBL_H_PIX
mdefine_line|#define EXT_VID_FMT_DBL_H_PIX&t;&t;0x40&t;/* double horiz pixels&t;&t;&t;*/
DECL|macro|EXT_VID_FMT_YUV128
mdefine_line|#define EXT_VID_FMT_YUV128&t;&t;0x80&t;/* YUV data offset by 128&t;&t;*/
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
mdefine_line|#define EXT_VID_DISP_CTL1_Y128&t;&t;0x10&t;/* Y data offset by 128 (if YUV128 set)&t;*/
DECL|macro|EXT_VID_DISP_CTL1_VINTERPOL_OFF
mdefine_line|#define EXT_VID_DISP_CTL1_VINTERPOL_OFF&t;0x20&t;/* disable vertical interpolation&t;*/
DECL|macro|EXT_VID_DISP_CTL1_FULL_WIN
mdefine_line|#define EXT_VID_DISP_CTL1_FULL_WIN&t;0x40&t;/* video out window full&t;&t;*/
DECL|macro|EXT_VID_DISP_CTL1_ENABLE_WINDOW
mdefine_line|#define EXT_VID_DISP_CTL1_ENABLE_WINDOW&t;0x80&t;/* enable video window&t;&t;&t;*/
DECL|macro|EXT_VID_FIFO_CTL1
mdefine_line|#define EXT_VID_FIFO_CTL1&t;0xdd
DECL|macro|EXT_VID_FIFO_CTL1_OE_HIGH
mdefine_line|#define EXT_VID_FIFO_CTL1_OE_HIGH&t;0x02
DECL|macro|EXT_VID_FIFO_CTL1_INTERLEAVE
mdefine_line|#define EXT_VID_FIFO_CTL1_INTERLEAVE&t;0x04&t;/* enable interleaved memory read&t;*/
DECL|macro|EXT_ROM_UCB4GH
mdefine_line|#define EXT_ROM_UCB4GH&t;&t;0xe5
DECL|macro|EXT_ROM_UCB4GH_FREEZE
mdefine_line|#define EXT_ROM_UCB4GH_FREEZE&t;&t;0x02&t;/* capture frozen&t;&t;&t;*/
DECL|macro|EXT_ROM_UCB4GH_ODDFRAME
mdefine_line|#define EXT_ROM_UCB4GH_ODDFRAME&t;&t;0x04&t;/* 1 = odd frame captured&t;&t;*/
DECL|macro|EXT_ROM_UCB4GH_1HL
mdefine_line|#define EXT_ROM_UCB4GH_1HL&t;&t;0x08&t;/* first horizonal line after VGT falling edge */
DECL|macro|EXT_ROM_UCB4GH_ODD
mdefine_line|#define EXT_ROM_UCB4GH_ODD&t;&t;0x10&t;/* odd frame indicator&t;&t;&t;*/
DECL|macro|EXT_ROM_UCB4GH_INTSTAT
mdefine_line|#define EXT_ROM_UCB4GH_INTSTAT&t;&t;0x20&t;/* video interrupt&t;&t;&t;*/
DECL|macro|VFAC_CTL1
mdefine_line|#define VFAC_CTL1&t;&t;0xe8
DECL|macro|VFAC_CTL1_CAPTURE
mdefine_line|#define VFAC_CTL1_CAPTURE&t;&t;0x01&t;/* capture enable (only when VSYNC high)*/
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
DECL|macro|VFAC_CTL3_CAP_LARGE_FIFO
mdefine_line|#define VFAC_CTL3_CAP_LARGE_FIFO&t;0x01&t;/* large capture fifo&t;&t;&t;*/
DECL|macro|VFAC_CTL3_CAP_INTERLACE
mdefine_line|#define VFAC_CTL3_CAP_INTERLACE&t;&t;0x02&t;/* capture odd and even fields&t;&t;*/
DECL|macro|VFAC_CTL3_CAP_HOLD_4NS
mdefine_line|#define VFAC_CTL3_CAP_HOLD_4NS&t;&t;0x00&t;/* hold capture data for 4ns&t;&t;*/
DECL|macro|VFAC_CTL3_CAP_HOLD_2NS
mdefine_line|#define VFAC_CTL3_CAP_HOLD_2NS&t;&t;0x04&t;/* hold capture data for 2ns&t;&t;*/
DECL|macro|VFAC_CTL3_CAP_HOLD_6NS
mdefine_line|#define VFAC_CTL3_CAP_HOLD_6NS&t;&t;0x08&t;/* hold capture data for 6ns&t;&t;*/
DECL|macro|VFAC_CTL3_CAP_HOLD_0NS
mdefine_line|#define VFAC_CTL3_CAP_HOLD_0NS&t;&t;0x0c&t;/* hold capture data for 0ns&t;&t;*/
DECL|macro|VFAC_CTL3_CHROMAKEY
mdefine_line|#define VFAC_CTL3_CHROMAKEY&t;&t;0x20&t;/* capture data will be chromakeyed&t;*/
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
multiline_comment|/*&n; * TV registers&n; */
DECL|macro|TV_VBLANK_EVEN_START
mdefine_line|#define TV_VBLANK_EVEN_START&t;0xbe43c
DECL|macro|TV_VBLANK_EVEN_END
mdefine_line|#define TV_VBLANK_EVEN_END&t;0xbe440
DECL|macro|TV_VBLANK_ODD_START
mdefine_line|#define TV_VBLANK_ODD_START&t;0xbe444
DECL|macro|TV_VBLANK_ODD_END
mdefine_line|#define TV_VBLANK_ODD_END&t;0xbe448
DECL|macro|TV_SYNC_YGAIN
mdefine_line|#define TV_SYNC_YGAIN&t;&t;0xbe44c
DECL|macro|TV_UV_GAIN
mdefine_line|#define TV_UV_GAIN&t;&t;0xbe450
DECL|macro|TV_PED_UVDET
mdefine_line|#define TV_PED_UVDET&t;&t;0xbe454
DECL|macro|TV_UV_BURST_AMP
mdefine_line|#define TV_UV_BURST_AMP&t;&t;0xbe458
DECL|macro|TV_HSYNC_START
mdefine_line|#define TV_HSYNC_START&t;&t;0xbe45c
DECL|macro|TV_HSYNC_END
mdefine_line|#define TV_HSYNC_END&t;&t;0xbe460
DECL|macro|TV_Y_DELAY1
mdefine_line|#define TV_Y_DELAY1&t;&t;0xbe464
DECL|macro|TV_Y_DELAY2
mdefine_line|#define TV_Y_DELAY2&t;&t;0xbe468
DECL|macro|TV_UV_DELAY1
mdefine_line|#define TV_UV_DELAY1&t;&t;0xbe46c
DECL|macro|TV_BURST_START
mdefine_line|#define TV_BURST_START&t;&t;0xbe470
DECL|macro|TV_BURST_END
mdefine_line|#define TV_BURST_END&t;&t;0xbe474
DECL|macro|TV_HBLANK_START
mdefine_line|#define TV_HBLANK_START&t;&t;0xbe478
DECL|macro|TV_HBLANK_END
mdefine_line|#define TV_HBLANK_END&t;&t;0xbe47c
DECL|macro|TV_PED_EVEN_START
mdefine_line|#define TV_PED_EVEN_START&t;0xbe480
DECL|macro|TV_PED_EVEN_END
mdefine_line|#define TV_PED_EVEN_END&t;&t;0xbe484
DECL|macro|TV_PED_ODD_START
mdefine_line|#define TV_PED_ODD_START&t;0xbe488
DECL|macro|TV_PED_ODD_END
mdefine_line|#define TV_PED_ODD_END&t;&t;0xbe48c
DECL|macro|TV_VSYNC_EVEN_START
mdefine_line|#define TV_VSYNC_EVEN_START&t;0xbe490
DECL|macro|TV_VSYNC_EVEN_END
mdefine_line|#define TV_VSYNC_EVEN_END&t;0xbe494
DECL|macro|TV_VSYNC_ODD_START
mdefine_line|#define TV_VSYNC_ODD_START&t;0xbe498
DECL|macro|TV_VSYNC_ODD_END
mdefine_line|#define TV_VSYNC_ODD_END&t;0xbe49c
DECL|macro|TV_SCFL
mdefine_line|#define TV_SCFL&t;&t;&t;0xbe4a0
DECL|macro|TV_SCFH
mdefine_line|#define TV_SCFH&t;&t;&t;0xbe4a4
DECL|macro|TV_SCP
mdefine_line|#define TV_SCP&t;&t;&t;0xbe4a8
DECL|macro|TV_DELAYBYPASS
mdefine_line|#define TV_DELAYBYPASS&t;&t;0xbe4b4
DECL|macro|TV_EQL_END
mdefine_line|#define TV_EQL_END&t;&t;0xbe4bc
DECL|macro|TV_SERR_START
mdefine_line|#define TV_SERR_START&t;&t;0xbe4c0
DECL|macro|TV_SERR_END
mdefine_line|#define TV_SERR_END&t;&t;0xbe4c4
DECL|macro|TV_CTL
mdefine_line|#define TV_CTL&t;&t;&t;0xbe4dc&t;/* reflects a previous register- MVFCLR, MVPCLR etc P241*/
DECL|macro|TV_VSYNC_VGA_HS
mdefine_line|#define TV_VSYNC_VGA_HS&t;&t;0xbe4e8
DECL|macro|TV_FLICK_XMIN
mdefine_line|#define TV_FLICK_XMIN&t;&t;0xbe514
DECL|macro|TV_FLICK_XMAX
mdefine_line|#define TV_FLICK_XMAX&t;&t;0xbe518
DECL|macro|TV_FLICK_YMIN
mdefine_line|#define TV_FLICK_YMIN&t;&t;0xbe51c
DECL|macro|TV_FLICK_YMAX
mdefine_line|#define TV_FLICK_YMAX&t;&t;0xbe520
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
DECL|member|chip_id
r_int
r_int
id|chip_id
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
DECL|macro|ID_IGA_1682
mdefine_line|#define ID_IGA_1682&t;&t;0
DECL|macro|ID_CYBERPRO_2000
mdefine_line|#define ID_CYBERPRO_2000&t;1
DECL|macro|ID_CYBERPRO_2010
mdefine_line|#define ID_CYBERPRO_2010&t;2
DECL|macro|ID_CYBERPRO_5000
mdefine_line|#define ID_CYBERPRO_5000&t;3
r_struct
id|fb_var_screeninfo
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
r_void
id|cyber2000fb_enable_extregs
c_func
(paren
r_struct
id|cfb_info
op_star
id|cfb
)paren
suffix:semicolon
r_void
id|cyber2000fb_disable_extregs
c_func
(paren
r_struct
id|cfb_info
op_star
id|cfb
)paren
suffix:semicolon
r_void
id|cyber2000fb_get_fb_var
c_func
(paren
r_struct
id|cfb_info
op_star
id|cfb
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
eof
