multiline_comment|/*&n; * linux/arch/m68k/console/cvision.h -- CyberVision64 definitions for the&n; *                                      text console driver.&n; *&n; *   Copyright (c) 1998 Alan Bair&n; *&n; * This file is based on the initial port to Linux of grf_cvreg.h:&n; *&n; *   Copyright (c) 1997 Antonio Santos&n; *&n; * The original work is from the NetBSD CyberVision 64 framebuffer driver &n; * and support files (grf_cv.c, grf_cvreg.h, ite_cv.c):&n; * Permission to use the source of this driver was obtained from the&n; * author Michael Teske by Alan Bair.&n; *&n; *   Copyright (c) 1995 Michael Teske&n; *&n; * History:&n; *&n; *&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/* s3 commands */
DECL|macro|S3_BITBLT
mdefine_line|#define S3_BITBLT       0xc011
DECL|macro|S3_TWOPOINTLINE
mdefine_line|#define S3_TWOPOINTLINE 0x2811
DECL|macro|S3_FILLEDRECT
mdefine_line|#define S3_FILLEDRECT   0x40b1
DECL|macro|S3_FIFO_EMPTY
mdefine_line|#define S3_FIFO_EMPTY 0x0400
DECL|macro|S3_HDW_BUSY
mdefine_line|#define S3_HDW_BUSY   0x0200
multiline_comment|/* Enhanced register mapping (MMIO mode) */
DECL|macro|S3_READ_SEL
mdefine_line|#define S3_READ_SEL      0xbee8 /* offset f */
DECL|macro|S3_MULT_MISC
mdefine_line|#define S3_MULT_MISC     0xbee8 /* offset e */
DECL|macro|S3_ERR_TERM
mdefine_line|#define S3_ERR_TERM      0x92e8
DECL|macro|S3_FRGD_COLOR
mdefine_line|#define S3_FRGD_COLOR    0xa6e8
DECL|macro|S3_BKGD_COLOR
mdefine_line|#define S3_BKGD_COLOR    0xa2e8
DECL|macro|S3_PIXEL_CNTL
mdefine_line|#define S3_PIXEL_CNTL    0xbee8 /* offset a */
DECL|macro|S3_FRGD_MIX
mdefine_line|#define S3_FRGD_MIX      0xbae8
DECL|macro|S3_BKGD_MIX
mdefine_line|#define S3_BKGD_MIX      0xb6e8
DECL|macro|S3_CUR_Y
mdefine_line|#define S3_CUR_Y         0x82e8
DECL|macro|S3_CUR_X
mdefine_line|#define S3_CUR_X         0x86e8
DECL|macro|S3_DESTY_AXSTP
mdefine_line|#define S3_DESTY_AXSTP   0x8ae8
DECL|macro|S3_DESTX_DIASTP
mdefine_line|#define S3_DESTX_DIASTP  0x8ee8
DECL|macro|S3_MIN_AXIS_PCNT
mdefine_line|#define S3_MIN_AXIS_PCNT 0xbee8 /* offset 0 */
DECL|macro|S3_MAJ_AXIS_PCNT
mdefine_line|#define S3_MAJ_AXIS_PCNT 0x96e8
DECL|macro|S3_CMD
mdefine_line|#define S3_CMD           0x9ae8
DECL|macro|S3_GP_STAT
mdefine_line|#define S3_GP_STAT       0x9ae8
DECL|macro|S3_ADVFUNC_CNTL
mdefine_line|#define S3_ADVFUNC_CNTL  0x4ae8
DECL|macro|S3_WRT_MASK
mdefine_line|#define S3_WRT_MASK      0xaae8
DECL|macro|S3_RD_MASK
mdefine_line|#define S3_RD_MASK       0xaee8
multiline_comment|/* Enhanced register mapping (Packed MMIO mode, write only) */
DECL|macro|S3_ALT_CURXY
mdefine_line|#define S3_ALT_CURXY     0x8100
DECL|macro|S3_ALT_CURXY2
mdefine_line|#define S3_ALT_CURXY2    0x8104
DECL|macro|S3_ALT_STEP
mdefine_line|#define S3_ALT_STEP      0x8108
DECL|macro|S3_ALT_STEP2
mdefine_line|#define S3_ALT_STEP2     0x810c
DECL|macro|S3_ALT_ERR
mdefine_line|#define S3_ALT_ERR       0x8110
DECL|macro|S3_ALT_CMD
mdefine_line|#define S3_ALT_CMD       0x8118
DECL|macro|S3_ALT_MIX
mdefine_line|#define S3_ALT_MIX       0x8134
DECL|macro|S3_ALT_PCNT
mdefine_line|#define S3_ALT_PCNT      0x8148
DECL|macro|S3_ALT_PAT
mdefine_line|#define S3_ALT_PAT       0x8168
multiline_comment|/* Drawing modes */
DECL|macro|S3_NOTCUR
mdefine_line|#define S3_NOTCUR          0x0000
DECL|macro|S3_LOGICALZERO
mdefine_line|#define S3_LOGICALZERO     0x0001
DECL|macro|S3_LOGICALONE
mdefine_line|#define S3_LOGICALONE      0x0002
DECL|macro|S3_LEAVEASIS
mdefine_line|#define S3_LEAVEASIS       0x0003
DECL|macro|S3_NOTNEW
mdefine_line|#define S3_NOTNEW          0x0004
DECL|macro|S3_CURXORNEW
mdefine_line|#define S3_CURXORNEW       0x0005
DECL|macro|S3_NOT_CURXORNEW
mdefine_line|#define S3_NOT_CURXORNEW   0x0006
DECL|macro|S3_NEW
mdefine_line|#define S3_NEW             0x0007
DECL|macro|S3_NOTCURORNOTNEW
mdefine_line|#define S3_NOTCURORNOTNEW  0x0008
DECL|macro|S3_CURORNOTNEW
mdefine_line|#define S3_CURORNOTNEW     0x0009
DECL|macro|S3_NOTCURORNEW
mdefine_line|#define S3_NOTCURORNEW     0x000a
DECL|macro|S3_CURORNEW
mdefine_line|#define S3_CURORNEW        0x000b
DECL|macro|S3_CURANDNEW
mdefine_line|#define S3_CURANDNEW       0x000c
DECL|macro|S3_NOTCURANDNEW
mdefine_line|#define S3_NOTCURANDNEW    0x000d
DECL|macro|S3_CURANDNOTNEW
mdefine_line|#define S3_CURANDNOTNEW    0x000e
DECL|macro|S3_NOTCURANDNOTNEW
mdefine_line|#define S3_NOTCURANDNOTNEW 0x000f
DECL|macro|S3_CRTC_ADR
mdefine_line|#define S3_CRTC_ADR    0x03d4
DECL|macro|S3_CRTC_DATA
mdefine_line|#define S3_CRTC_DATA   0x03d5
DECL|macro|S3_REG_LOCK2
mdefine_line|#define S3_REG_LOCK2 0x39
DECL|macro|S3_HGC_MODE
mdefine_line|#define S3_HGC_MODE  0x45
DECL|macro|S3_HWGC_ORGX_H
mdefine_line|#define S3_HWGC_ORGX_H 0x46
DECL|macro|S3_HWGC_ORGX_L
mdefine_line|#define S3_HWGC_ORGX_L 0x47
DECL|macro|S3_HWGC_ORGY_H
mdefine_line|#define S3_HWGC_ORGY_H 0x48
DECL|macro|S3_HWGC_ORGY_L
mdefine_line|#define S3_HWGC_ORGY_L 0x49
DECL|macro|S3_HWGC_DX
mdefine_line|#define S3_HWGC_DX     0x4e
DECL|macro|S3_HWGC_DY
mdefine_line|#define S3_HWGC_DY     0x4f
DECL|macro|S3_LAW_CTL
mdefine_line|#define S3_LAW_CTL 0x58
multiline_comment|/**************************************************/
macro_line|#ifndef min
DECL|macro|min
mdefine_line|#define min(a,b)&t;((a) &lt; (b) ? (a) : (b))
macro_line|#endif /* !min */
macro_line|#ifndef max
DECL|macro|max
mdefine_line|#define max(a,b)&t;((a) &gt; (b) ? (a) : (b))
macro_line|#endif /* !max */
multiline_comment|/* support for a BitBlt operation. The op-codes are identical&n;   to X11 GCs */
DECL|macro|GRFBBOPclear
mdefine_line|#define&t;GRFBBOPclear&t;&t;0x0&t;/* 0 */
DECL|macro|GRFBBOPand
mdefine_line|#define GRFBBOPand&t;&t;0x1&t;/* src AND dst */
DECL|macro|GRFBBOPandReverse
mdefine_line|#define GRFBBOPandReverse&t;0x2&t;/* src AND NOT dst */
DECL|macro|GRFBBOPcopy
mdefine_line|#define GRFBBOPcopy&t;&t;0x3&t;/* src */
DECL|macro|GRFBBOPandInverted
mdefine_line|#define GRFBBOPandInverted&t;0x4&t;/* NOT src AND dst */
DECL|macro|GRFBBOPnoop
mdefine_line|#define&t;GRFBBOPnoop&t;&t;0x5&t;/* dst */
DECL|macro|GRFBBOPxor
mdefine_line|#define GRFBBOPxor&t;&t;0x6&t;/* src XOR dst */
DECL|macro|GRFBBOPor
mdefine_line|#define GRFBBOPor&t;&t;0x7&t;/* src OR dst */
DECL|macro|GRFBBOPnor
mdefine_line|#define GRFBBOPnor&t;&t;0x8&t;/* NOT src AND NOT dst */
DECL|macro|GRFBBOPequiv
mdefine_line|#define GRFBBOPequiv&t;&t;0x9&t;/* NOT src XOR dst */
DECL|macro|GRFBBOPinvert
mdefine_line|#define GRFBBOPinvert&t;&t;0xa&t;/* NOT dst */
DECL|macro|GRFBBOPorReverse
mdefine_line|#define GRFBBOPorReverse&t;0xb&t;/* src OR NOT dst */
DECL|macro|GRFBBOPcopyInverted
mdefine_line|#define GRFBBOPcopyInverted&t;0xc&t;/* NOT src */
DECL|macro|GRFBBOPorInverted
mdefine_line|#define GRFBBOPorInverted&t;0xd&t;/* NOT src OR dst */
DECL|macro|GRFBBOPnand
mdefine_line|#define GRFBBOPnand&t;&t;0xe&t;/* NOT src OR NOT dst */
DECL|macro|GRFBBOPset
mdefine_line|#define GRFBBOPset&t;&t;0xf&t;/* 1 */
multiline_comment|/* Write 16 Bit VGA register */
DECL|macro|vgaw16
mdefine_line|#define vgaw16(ba, reg, val) &bslash;&n;*((unsigned short *)  (((volatile unsigned char *)ba)+reg)) = val
multiline_comment|/*&n; * Defines for the used register addresses (mw)&n; *&n; * NOTE: There are some registers that have different addresses when&n; *       in mono or color mode. We only support color mode, and thus&n; *       some addresses won&squot;t work in mono-mode!&n; *&n; * General and VGA-registers taken from retina driver. Fixed a few&n; * bugs in it. (SR and GR read address is Port + 1, NOT Port)&n; *&n; */
multiline_comment|/* General Registers: */
DECL|macro|GREG_MISC_OUTPUT_R
mdefine_line|#define GREG_MISC_OUTPUT_R&t;0x03CC
DECL|macro|GREG_MISC_OUTPUT_W
mdefine_line|#define GREG_MISC_OUTPUT_W&t;0x03C2&t;
DECL|macro|GREG_FEATURE_CONTROL_R
mdefine_line|#define GREG_FEATURE_CONTROL_R&t;0x03CA
DECL|macro|GREG_FEATURE_CONTROL_W
mdefine_line|#define GREG_FEATURE_CONTROL_W&t;0x03DA
DECL|macro|GREG_INPUT_STATUS0_R
mdefine_line|#define GREG_INPUT_STATUS0_R&t;0x03C2
DECL|macro|GREG_INPUT_STATUS1_R
mdefine_line|#define GREG_INPUT_STATUS1_R&t;0x03DA
multiline_comment|/* Setup Registers: */
DECL|macro|SREG_OPTION_SELECT
mdefine_line|#define SREG_OPTION_SELECT&t;0x0102
DECL|macro|SREG_VIDEO_SUBS_ENABLE
mdefine_line|#define SREG_VIDEO_SUBS_ENABLE&t;0x46E8
multiline_comment|/* Attribute Controller: */
DECL|macro|ACT_ADDRESS
mdefine_line|#define ACT_ADDRESS&t;&t;0x03C0
DECL|macro|ACT_ADDRESS_R
mdefine_line|#define ACT_ADDRESS_R&t;&t;0x03C1
DECL|macro|ACT_ADDRESS_W
mdefine_line|#define ACT_ADDRESS_W&t;&t;0x03C0
DECL|macro|ACT_ADDRESS_RESET
mdefine_line|#define ACT_ADDRESS_RESET&t;0x03DA
DECL|macro|ACT_ID_PALETTE0
mdefine_line|#define ACT_ID_PALETTE0&t;&t;0x00
DECL|macro|ACT_ID_PALETTE1
mdefine_line|#define ACT_ID_PALETTE1&t;&t;0x01
DECL|macro|ACT_ID_PALETTE2
mdefine_line|#define ACT_ID_PALETTE2&t;&t;0x02
DECL|macro|ACT_ID_PALETTE3
mdefine_line|#define ACT_ID_PALETTE3&t;&t;0x03
DECL|macro|ACT_ID_PALETTE4
mdefine_line|#define ACT_ID_PALETTE4&t;&t;0x04
DECL|macro|ACT_ID_PALETTE5
mdefine_line|#define ACT_ID_PALETTE5&t;&t;0x05
DECL|macro|ACT_ID_PALETTE6
mdefine_line|#define ACT_ID_PALETTE6&t;&t;0x06
DECL|macro|ACT_ID_PALETTE7
mdefine_line|#define ACT_ID_PALETTE7&t;&t;0x07
DECL|macro|ACT_ID_PALETTE8
mdefine_line|#define ACT_ID_PALETTE8&t;&t;0x08
DECL|macro|ACT_ID_PALETTE9
mdefine_line|#define ACT_ID_PALETTE9&t;&t;0x09
DECL|macro|ACT_ID_PALETTE10
mdefine_line|#define ACT_ID_PALETTE10&t;0x0A
DECL|macro|ACT_ID_PALETTE11
mdefine_line|#define ACT_ID_PALETTE11&t;0x0B
DECL|macro|ACT_ID_PALETTE12
mdefine_line|#define ACT_ID_PALETTE12&t;0x0C
DECL|macro|ACT_ID_PALETTE13
mdefine_line|#define ACT_ID_PALETTE13&t;0x0D
DECL|macro|ACT_ID_PALETTE14
mdefine_line|#define ACT_ID_PALETTE14&t;0x0E
DECL|macro|ACT_ID_PALETTE15
mdefine_line|#define ACT_ID_PALETTE15&t;0x0F
DECL|macro|ACT_ID_ATTR_MODE_CNTL
mdefine_line|#define ACT_ID_ATTR_MODE_CNTL&t;0x10
DECL|macro|ACT_ID_OVERSCAN_COLOR
mdefine_line|#define ACT_ID_OVERSCAN_COLOR&t;0x11
DECL|macro|ACT_ID_COLOR_PLANE_ENA
mdefine_line|#define ACT_ID_COLOR_PLANE_ENA&t;0x12
DECL|macro|ACT_ID_HOR_PEL_PANNING
mdefine_line|#define ACT_ID_HOR_PEL_PANNING&t;0x13
DECL|macro|ACT_ID_COLOR_SELECT
mdefine_line|#define ACT_ID_COLOR_SELECT&t;0x14
multiline_comment|/* Graphics Controller: */
DECL|macro|GCT_ADDRESS
mdefine_line|#define GCT_ADDRESS&t;&t;0x03CE
DECL|macro|GCT_ADDRESS_R
mdefine_line|#define GCT_ADDRESS_R&t;&t;0x03CF
DECL|macro|GCT_ADDRESS_W
mdefine_line|#define GCT_ADDRESS_W&t;&t;0x03CF
DECL|macro|GCT_ID_SET_RESET
mdefine_line|#define GCT_ID_SET_RESET&t;0x00
DECL|macro|GCT_ID_ENABLE_SET_RESET
mdefine_line|#define GCT_ID_ENABLE_SET_RESET&t;0x01
DECL|macro|GCT_ID_COLOR_COMPARE
mdefine_line|#define GCT_ID_COLOR_COMPARE&t;0x02
DECL|macro|GCT_ID_DATA_ROTATE
mdefine_line|#define GCT_ID_DATA_ROTATE&t;0x03
DECL|macro|GCT_ID_READ_MAP_SELECT
mdefine_line|#define GCT_ID_READ_MAP_SELECT&t;0x04
DECL|macro|GCT_ID_GRAPHICS_MODE
mdefine_line|#define GCT_ID_GRAPHICS_MODE&t;0x05
DECL|macro|GCT_ID_MISC
mdefine_line|#define GCT_ID_MISC&t;&t;0x06
DECL|macro|GCT_ID_COLOR_XCARE
mdefine_line|#define GCT_ID_COLOR_XCARE&t;0x07
DECL|macro|GCT_ID_BITMASK
mdefine_line|#define GCT_ID_BITMASK&t;&t;0x08
multiline_comment|/* Sequencer: */
DECL|macro|SEQ_ADDRESS
mdefine_line|#define SEQ_ADDRESS&t;&t;0x03C4
DECL|macro|SEQ_ADDRESS_R
mdefine_line|#define SEQ_ADDRESS_R&t;&t;0x03C5
DECL|macro|SEQ_ADDRESS_W
mdefine_line|#define SEQ_ADDRESS_W&t;&t;0x03C5
DECL|macro|SEQ_ID_RESET
mdefine_line|#define SEQ_ID_RESET&t;&t;0x00
DECL|macro|SEQ_ID_CLOCKING_MODE
mdefine_line|#define SEQ_ID_CLOCKING_MODE&t;0x01
DECL|macro|SEQ_ID_MAP_MASK
mdefine_line|#define SEQ_ID_MAP_MASK&t;&t;0x02
DECL|macro|SEQ_ID_CHAR_MAP_SELECT
mdefine_line|#define SEQ_ID_CHAR_MAP_SELECT&t;0x03
DECL|macro|SEQ_ID_MEMORY_MODE
mdefine_line|#define SEQ_ID_MEMORY_MODE&t;0x04
DECL|macro|SEQ_ID_UNKNOWN1
mdefine_line|#define SEQ_ID_UNKNOWN1&t;&t;0x05
DECL|macro|SEQ_ID_UNKNOWN2
mdefine_line|#define SEQ_ID_UNKNOWN2&t;&t;0x06
DECL|macro|SEQ_ID_UNKNOWN3
mdefine_line|#define SEQ_ID_UNKNOWN3&t;&t;0x07
multiline_comment|/* S3 extensions */
DECL|macro|SEQ_ID_UNLOCK_EXT
mdefine_line|#define SEQ_ID_UNLOCK_EXT&t;0x08
DECL|macro|SEQ_ID_EXT_SEQ_REG9
mdefine_line|#define SEQ_ID_EXT_SEQ_REG9&t;0x09
DECL|macro|SEQ_ID_BUS_REQ_CNTL
mdefine_line|#define SEQ_ID_BUS_REQ_CNTL&t;0x0A
DECL|macro|SEQ_ID_EXT_MISC_SEQ
mdefine_line|#define SEQ_ID_EXT_MISC_SEQ&t;0x0B
DECL|macro|SEQ_ID_UNKNOWN4
mdefine_line|#define SEQ_ID_UNKNOWN4&t;&t;0x0C
DECL|macro|SEQ_ID_EXT_SEQ
mdefine_line|#define SEQ_ID_EXT_SEQ&t;&t;0x0D
DECL|macro|SEQ_ID_UNKNOWN5
mdefine_line|#define SEQ_ID_UNKNOWN5&t;&t;0x0E
DECL|macro|SEQ_ID_UNKNOWN6
mdefine_line|#define SEQ_ID_UNKNOWN6&t;&t;0x0F
DECL|macro|SEQ_ID_MCLK_LO
mdefine_line|#define SEQ_ID_MCLK_LO&t;&t;0x10
DECL|macro|SEQ_ID_MCLK_HI
mdefine_line|#define SEQ_ID_MCLK_HI&t;&t;0x11
DECL|macro|SEQ_ID_DCLK_LO
mdefine_line|#define SEQ_ID_DCLK_LO&t;&t;0x12
DECL|macro|SEQ_ID_DCLK_HI
mdefine_line|#define SEQ_ID_DCLK_HI&t;&t;0x13
DECL|macro|SEQ_ID_CLKSYN_CNTL_1
mdefine_line|#define SEQ_ID_CLKSYN_CNTL_1&t;0x14
DECL|macro|SEQ_ID_CLKSYN_CNTL_2
mdefine_line|#define SEQ_ID_CLKSYN_CNTL_2&t;0x15
DECL|macro|SEQ_ID_CLKSYN_TEST_HI
mdefine_line|#define SEQ_ID_CLKSYN_TEST_HI&t;0x16&t;/* reserved for S3 testing of the */
DECL|macro|SEQ_ID_CLKSYN_TEST_LO
mdefine_line|#define SEQ_ID_CLKSYN_TEST_LO&t;0x17&t;/*   internal clock synthesizer   */
DECL|macro|SEQ_ID_RAMDAC_CNTL
mdefine_line|#define SEQ_ID_RAMDAC_CNTL&t;0x18
DECL|macro|SEQ_ID_MORE_MAGIC
mdefine_line|#define SEQ_ID_MORE_MAGIC&t;0x1A
multiline_comment|/* CRT Controller: */
DECL|macro|CRT_ADDRESS
mdefine_line|#define CRT_ADDRESS&t;&t;0x03D4
DECL|macro|CRT_ADDRESS_R
mdefine_line|#define CRT_ADDRESS_R&t;&t;0x03D5
DECL|macro|CRT_ADDRESS_W
mdefine_line|#define CRT_ADDRESS_W&t;&t;0x03D5
DECL|macro|CRT_ID_HOR_TOTAL
mdefine_line|#define CRT_ID_HOR_TOTAL&t;0x00
DECL|macro|CRT_ID_HOR_DISP_ENA_END
mdefine_line|#define CRT_ID_HOR_DISP_ENA_END&t;0x01
DECL|macro|CRT_ID_START_HOR_BLANK
mdefine_line|#define CRT_ID_START_HOR_BLANK&t;0x02
DECL|macro|CRT_ID_END_HOR_BLANK
mdefine_line|#define CRT_ID_END_HOR_BLANK&t;0x03
DECL|macro|CRT_ID_START_HOR_RETR
mdefine_line|#define CRT_ID_START_HOR_RETR&t;0x04
DECL|macro|CRT_ID_END_HOR_RETR
mdefine_line|#define CRT_ID_END_HOR_RETR&t;0x05
DECL|macro|CRT_ID_VER_TOTAL
mdefine_line|#define CRT_ID_VER_TOTAL&t;0x06
DECL|macro|CRT_ID_OVERFLOW
mdefine_line|#define CRT_ID_OVERFLOW&t;&t;0x07
DECL|macro|CRT_ID_PRESET_ROW_SCAN
mdefine_line|#define CRT_ID_PRESET_ROW_SCAN&t;0x08
DECL|macro|CRT_ID_MAX_SCAN_LINE
mdefine_line|#define CRT_ID_MAX_SCAN_LINE&t;0x09
DECL|macro|CRT_ID_CURSOR_START
mdefine_line|#define CRT_ID_CURSOR_START&t;0x0A
DECL|macro|CRT_ID_CURSOR_END
mdefine_line|#define CRT_ID_CURSOR_END&t;0x0B
DECL|macro|CRT_ID_START_ADDR_HIGH
mdefine_line|#define CRT_ID_START_ADDR_HIGH&t;0x0C
DECL|macro|CRT_ID_START_ADDR_LOW
mdefine_line|#define CRT_ID_START_ADDR_LOW&t;0x0D
DECL|macro|CRT_ID_CURSOR_LOC_HIGH
mdefine_line|#define CRT_ID_CURSOR_LOC_HIGH&t;0x0E
DECL|macro|CRT_ID_CURSOR_LOC_LOW
mdefine_line|#define CRT_ID_CURSOR_LOC_LOW&t;0x0F
DECL|macro|CRT_ID_START_VER_RETR
mdefine_line|#define CRT_ID_START_VER_RETR&t;0x10
DECL|macro|CRT_ID_END_VER_RETR
mdefine_line|#define CRT_ID_END_VER_RETR&t;0x11
DECL|macro|CRT_ID_VER_DISP_ENA_END
mdefine_line|#define CRT_ID_VER_DISP_ENA_END&t;0x12
DECL|macro|CRT_ID_SCREEN_OFFSET
mdefine_line|#define CRT_ID_SCREEN_OFFSET&t;0x13
DECL|macro|CRT_ID_UNDERLINE_LOC
mdefine_line|#define CRT_ID_UNDERLINE_LOC&t;0x14
DECL|macro|CRT_ID_START_VER_BLANK
mdefine_line|#define CRT_ID_START_VER_BLANK&t;0x15
DECL|macro|CRT_ID_END_VER_BLANK
mdefine_line|#define CRT_ID_END_VER_BLANK&t;0x16
DECL|macro|CRT_ID_MODE_CONTROL
mdefine_line|#define CRT_ID_MODE_CONTROL&t;0x17
DECL|macro|CRT_ID_LINE_COMPARE
mdefine_line|#define CRT_ID_LINE_COMPARE&t;0x18
DECL|macro|CRT_ID_GD_LATCH_RBACK
mdefine_line|#define CRT_ID_GD_LATCH_RBACK&t;0x22
DECL|macro|CRT_ID_ACT_TOGGLE_RBACK
mdefine_line|#define CRT_ID_ACT_TOGGLE_RBACK&t;0x24
DECL|macro|CRT_ID_ACT_INDEX_RBACK
mdefine_line|#define CRT_ID_ACT_INDEX_RBACK&t;0x26
multiline_comment|/* S3 extensions: S3 VGA Registers */
DECL|macro|CRT_ID_DEVICE_HIGH
mdefine_line|#define CRT_ID_DEVICE_HIGH&t;0x2D
DECL|macro|CRT_ID_DEVICE_LOW
mdefine_line|#define CRT_ID_DEVICE_LOW&t;0x2E
DECL|macro|CRT_ID_REVISION
mdefine_line|#define CRT_ID_REVISION &t;0x2F
DECL|macro|CRT_ID_CHIP_ID_REV
mdefine_line|#define CRT_ID_CHIP_ID_REV&t;0x30
DECL|macro|CRT_ID_MEMORY_CONF
mdefine_line|#define CRT_ID_MEMORY_CONF&t;0x31
DECL|macro|CRT_ID_BACKWAD_COMP_1
mdefine_line|#define CRT_ID_BACKWAD_COMP_1&t;0x32
DECL|macro|CRT_ID_BACKWAD_COMP_2
mdefine_line|#define CRT_ID_BACKWAD_COMP_2&t;0x33
DECL|macro|CRT_ID_BACKWAD_COMP_3
mdefine_line|#define CRT_ID_BACKWAD_COMP_3&t;0x34
DECL|macro|CRT_ID_REGISTER_LOCK
mdefine_line|#define CRT_ID_REGISTER_LOCK&t;0x35
DECL|macro|CRT_ID_CONFIG_1
mdefine_line|#define CRT_ID_CONFIG_1 &t;0x36
DECL|macro|CRT_ID_CONFIG_2
mdefine_line|#define CRT_ID_CONFIG_2 &t;0x37
DECL|macro|CRT_ID_REGISTER_LOCK_1
mdefine_line|#define CRT_ID_REGISTER_LOCK_1&t;0x38
DECL|macro|CRT_ID_REGISTER_LOCK_2
mdefine_line|#define CRT_ID_REGISTER_LOCK_2&t;0x39
DECL|macro|CRT_ID_MISC_1
mdefine_line|#define CRT_ID_MISC_1&t;&t;0x3A
DECL|macro|CRT_ID_DISPLAY_FIFO
mdefine_line|#define CRT_ID_DISPLAY_FIFO&t;0x3B
DECL|macro|CRT_ID_LACE_RETR_START
mdefine_line|#define CRT_ID_LACE_RETR_START&t;0x3C
multiline_comment|/* S3 extensions: System Control Registers  */
DECL|macro|CRT_ID_SYSTEM_CONFIG
mdefine_line|#define CRT_ID_SYSTEM_CONFIG&t;0x40
DECL|macro|CRT_ID_BIOS_FLAG
mdefine_line|#define CRT_ID_BIOS_FLAG&t;0x41
DECL|macro|CRT_ID_LACE_CONTROL
mdefine_line|#define CRT_ID_LACE_CONTROL&t;0x42
DECL|macro|CRT_ID_EXT_MODE
mdefine_line|#define CRT_ID_EXT_MODE &t;0x43
DECL|macro|CRT_ID_HWGC_MODE
mdefine_line|#define CRT_ID_HWGC_MODE&t;0x45&t;/* HWGC = Hardware Graphics Cursor */
DECL|macro|CRT_ID_HWGC_ORIGIN_X_HI
mdefine_line|#define CRT_ID_HWGC_ORIGIN_X_HI&t;0x46
DECL|macro|CRT_ID_HWGC_ORIGIN_X_LO
mdefine_line|#define CRT_ID_HWGC_ORIGIN_X_LO&t;0x47
DECL|macro|CRT_ID_HWGC_ORIGIN_Y_HI
mdefine_line|#define CRT_ID_HWGC_ORIGIN_Y_HI&t;0x48
DECL|macro|CRT_ID_HWGC_ORIGIN_Y_LO
mdefine_line|#define CRT_ID_HWGC_ORIGIN_Y_LO&t;0x49
DECL|macro|CRT_ID_HWGC_FG_STACK
mdefine_line|#define CRT_ID_HWGC_FG_STACK&t;0x4A
DECL|macro|CRT_ID_HWGC_BG_STACK
mdefine_line|#define CRT_ID_HWGC_BG_STACK&t;0x4B
DECL|macro|CRT_ID_HWGC_START_AD_HI
mdefine_line|#define CRT_ID_HWGC_START_AD_HI&t;0x4C
DECL|macro|CRT_ID_HWGC_START_AD_LO
mdefine_line|#define CRT_ID_HWGC_START_AD_LO&t;0x4D
DECL|macro|CRT_ID_HWGC_DSTART_X
mdefine_line|#define CRT_ID_HWGC_DSTART_X&t;0x4E
DECL|macro|CRT_ID_HWGC_DSTART_Y
mdefine_line|#define CRT_ID_HWGC_DSTART_Y&t;0x4F
multiline_comment|/* S3 extensions: System Extension Registers  */
DECL|macro|CRT_ID_EXT_SYS_CNTL_1
mdefine_line|#define CRT_ID_EXT_SYS_CNTL_1&t;0x50
DECL|macro|CRT_ID_EXT_SYS_CNTL_2
mdefine_line|#define CRT_ID_EXT_SYS_CNTL_2&t;0x51
DECL|macro|CRT_ID_EXT_BIOS_FLAG_1
mdefine_line|#define CRT_ID_EXT_BIOS_FLAG_1&t;0x52
DECL|macro|CRT_ID_EXT_MEM_CNTL_1
mdefine_line|#define CRT_ID_EXT_MEM_CNTL_1&t;0x53
DECL|macro|CRT_ID_EXT_MEM_CNTL_2
mdefine_line|#define CRT_ID_EXT_MEM_CNTL_2&t;0x54
DECL|macro|CRT_ID_EXT_DAC_CNTL
mdefine_line|#define CRT_ID_EXT_DAC_CNTL&t;0x55
DECL|macro|CRT_ID_EX_SYNC_1
mdefine_line|#define CRT_ID_EX_SYNC_1&t;0x56
DECL|macro|CRT_ID_EX_SYNC_2
mdefine_line|#define CRT_ID_EX_SYNC_2&t;0x57
DECL|macro|CRT_ID_LAW_CNTL
mdefine_line|#define CRT_ID_LAW_CNTL&t;&t;0x58&t;/* LAW = Linear Address Window */
DECL|macro|CRT_ID_LAW_POS_HI
mdefine_line|#define CRT_ID_LAW_POS_HI&t;0x59
DECL|macro|CRT_ID_LAW_POS_LO
mdefine_line|#define CRT_ID_LAW_POS_LO&t;0x5A
DECL|macro|CRT_ID_GOUT_PORT
mdefine_line|#define CRT_ID_GOUT_PORT&t;0x5C
DECL|macro|CRT_ID_EXT_HOR_OVF
mdefine_line|#define CRT_ID_EXT_HOR_OVF&t;0x5D
DECL|macro|CRT_ID_EXT_VER_OVF
mdefine_line|#define CRT_ID_EXT_VER_OVF&t;0x5E
DECL|macro|CRT_ID_EXT_MEM_CNTL_3
mdefine_line|#define CRT_ID_EXT_MEM_CNTL_3&t;0x60
DECL|macro|CRT_ID_EX_SYNC_3
mdefine_line|#define CRT_ID_EX_SYNC_3&t;0x63
DECL|macro|CRT_ID_EXT_MISC_CNTL
mdefine_line|#define CRT_ID_EXT_MISC_CNTL&t;0x65
DECL|macro|CRT_ID_EXT_MISC_CNTL_1
mdefine_line|#define CRT_ID_EXT_MISC_CNTL_1&t;0x66
DECL|macro|CRT_ID_EXT_MISC_CNTL_2
mdefine_line|#define CRT_ID_EXT_MISC_CNTL_2&t;0x67
DECL|macro|CRT_ID_CONFIG_3
mdefine_line|#define CRT_ID_CONFIG_3 &t;0x68
DECL|macro|CRT_ID_EXT_SYS_CNTL_3
mdefine_line|#define CRT_ID_EXT_SYS_CNTL_3&t;0x69
DECL|macro|CRT_ID_EXT_SYS_CNTL_4
mdefine_line|#define CRT_ID_EXT_SYS_CNTL_4&t;0x6A
DECL|macro|CRT_ID_EXT_BIOS_FLAG_3
mdefine_line|#define CRT_ID_EXT_BIOS_FLAG_3&t;0x6B
DECL|macro|CRT_ID_EXT_BIOS_FLAG_4
mdefine_line|#define CRT_ID_EXT_BIOS_FLAG_4&t;0x6C
multiline_comment|/* Enhanced Commands Registers: */
DECL|macro|ECR_SUBSYSTEM_STAT
mdefine_line|#define ECR_SUBSYSTEM_STAT&t;0x42E8
DECL|macro|ECR_SUBSYSTEM_CNTL
mdefine_line|#define ECR_SUBSYSTEM_CNTL&t;0x42E8
DECL|macro|ECR_ADV_FUNC_CNTL
mdefine_line|#define ECR_ADV_FUNC_CNTL&t;0x4AE8
DECL|macro|ECR_CURRENT_Y_POS
mdefine_line|#define ECR_CURRENT_Y_POS&t;0x82E8
DECL|macro|ECR_CURRENT_Y_POS2
mdefine_line|#define ECR_CURRENT_Y_POS2&t;0x82EA&t;/* Trio64 only */
DECL|macro|ECR_CURRENT_X_POS
mdefine_line|#define ECR_CURRENT_X_POS&t;0x86E8
DECL|macro|ECR_CURRENT_X_POS2
mdefine_line|#define ECR_CURRENT_X_POS2&t;0x86EA&t;/* Trio64 only */
DECL|macro|ECR_DEST_Y__AX_STEP
mdefine_line|#define ECR_DEST_Y__AX_STEP&t;0x8AE8
DECL|macro|ECR_DEST_Y2__AX_STEP2
mdefine_line|#define ECR_DEST_Y2__AX_STEP2&t;0x8AEA&t;/* Trio64 only */
DECL|macro|ECR_DEST_X__DIA_STEP
mdefine_line|#define ECR_DEST_X__DIA_STEP&t;0x8EE8
DECL|macro|ECR_DEST_X2__DIA_STEP2
mdefine_line|#define ECR_DEST_X2__DIA_STEP2&t;0x8EEA&t;/* Trio64 only */
DECL|macro|ECR_ERR_TERM
mdefine_line|#define ECR_ERR_TERM&t;&t;0x92E8
DECL|macro|ECR_ERR_TERM2
mdefine_line|#define ECR_ERR_TERM2&t;&t;0x92EA&t;/* Trio64 only */
DECL|macro|ECR_MAJ_AXIS_PIX_CNT
mdefine_line|#define ECR_MAJ_AXIS_PIX_CNT&t;0x96E8
DECL|macro|ECR_MAJ_AXIS_PIX_CNT2
mdefine_line|#define ECR_MAJ_AXIS_PIX_CNT2&t;0x96EA&t;/* Trio64 only */
DECL|macro|ECR_GP_STAT
mdefine_line|#define ECR_GP_STAT&t;&t;0x9AE8&t;/* GP = Graphics Processor */
DECL|macro|ECR_DRAW_CMD
mdefine_line|#define ECR_DRAW_CMD&t;&t;0x9AE8
DECL|macro|ECR_DRAW_CMD2
mdefine_line|#define ECR_DRAW_CMD2&t;&t;0x9AEA&t;/* Trio64 only */
DECL|macro|ECR_SHORT_STROKE
mdefine_line|#define ECR_SHORT_STROKE&t;0x9EE8
DECL|macro|ECR_BKGD_COLOR
mdefine_line|#define ECR_BKGD_COLOR&t;&t;0xA2E8&t;/* BKGD = Background */
DECL|macro|ECR_FRGD_COLOR
mdefine_line|#define ECR_FRGD_COLOR&t;&t;0xA6E8&t;/* FRGD = Foreground */
DECL|macro|ECR_BITPLANE_WRITE_MASK
mdefine_line|#define ECR_BITPLANE_WRITE_MASK&t;0xAAE8
DECL|macro|ECR_BITPLANE_READ_MASK
mdefine_line|#define ECR_BITPLANE_READ_MASK&t;0xAEE8
DECL|macro|ECR_COLOR_COMPARE
mdefine_line|#define ECR_COLOR_COMPARE&t;0xB2E8
DECL|macro|ECR_BKGD_MIX
mdefine_line|#define ECR_BKGD_MIX&t;&t;0xB6E8
DECL|macro|ECR_FRGD_MIX
mdefine_line|#define ECR_FRGD_MIX&t;&t;0xBAE8
DECL|macro|ECR_READ_REG_DATA
mdefine_line|#define ECR_READ_REG_DATA&t;0xBEE8
DECL|macro|ECR_ID_MIN_AXIS_PIX_CNT
mdefine_line|#define ECR_ID_MIN_AXIS_PIX_CNT&t;0x00
DECL|macro|ECR_ID_SCISSORS_TOP
mdefine_line|#define ECR_ID_SCISSORS_TOP&t;0x01
DECL|macro|ECR_ID_SCISSORS_LEFT
mdefine_line|#define ECR_ID_SCISSORS_LEFT&t;0x02
DECL|macro|ECR_ID_SCISSORS_BUTTOM
mdefine_line|#define ECR_ID_SCISSORS_BUTTOM&t;0x03
DECL|macro|ECR_ID_SCISSORS_RIGHT
mdefine_line|#define ECR_ID_SCISSORS_RIGHT&t;0x04
DECL|macro|ECR_ID_PIX_CNTL
mdefine_line|#define ECR_ID_PIX_CNTL&t;&t;0x0A
DECL|macro|ECR_ID_MULT_CNTL_MISC_2
mdefine_line|#define ECR_ID_MULT_CNTL_MISC_2&t;0x0D
DECL|macro|ECR_ID_MULT_CNTL_MISC
mdefine_line|#define ECR_ID_MULT_CNTL_MISC&t;0x0E
DECL|macro|ECR_ID_READ_SEL
mdefine_line|#define ECR_ID_READ_SEL&t;&t;0x0F
DECL|macro|ECR_PIX_TRANS
mdefine_line|#define ECR_PIX_TRANS&t;&t;0xE2E8
DECL|macro|ECR_PIX_TRANS_EXT
mdefine_line|#define ECR_PIX_TRANS_EXT&t;0xE2EA
DECL|macro|ECR_PATTERN_Y
mdefine_line|#define ECR_PATTERN_Y&t;&t;0xEAE8&t;/* Trio64 only */
DECL|macro|ECR_PATTERN_X
mdefine_line|#define ECR_PATTERN_X&t;&t;0xEAEA&t;/* Trio64 only */
multiline_comment|/* Pass-through */
DECL|macro|PASS_ADDRESS
mdefine_line|#define PASS_ADDRESS&t;&t;0x40001
DECL|macro|PASS_ADDRESS_W
mdefine_line|#define PASS_ADDRESS_W&t;&t;0x40001
multiline_comment|/* Video DAC */
DECL|macro|VDAC_ADDRESS
mdefine_line|#define VDAC_ADDRESS&t;&t;0x03c8
DECL|macro|VDAC_ADDRESS_W
mdefine_line|#define VDAC_ADDRESS_W&t;&t;0x03c8
DECL|macro|VDAC_ADDRESS_R
mdefine_line|#define VDAC_ADDRESS_R&t;&t;0x03c7
DECL|macro|VDAC_STATE
mdefine_line|#define VDAC_STATE&t;&t;0x03c7
DECL|macro|VDAC_DATA
mdefine_line|#define VDAC_DATA&t;&t;0x03c9
DECL|macro|VDAC_MASK
mdefine_line|#define VDAC_MASK&t;&t;0x03c6
DECL|macro|WGfx
mdefine_line|#define WGfx(ba, idx, val) &bslash;&n;do { wb_64(ba, GCT_ADDRESS, idx); wb_64(ba, GCT_ADDRESS_W , val); } while (0)
DECL|macro|WSeq
mdefine_line|#define WSeq(ba, idx, val) &bslash;&n;do { wb_64(ba, SEQ_ADDRESS, idx); wb_64(ba, SEQ_ADDRESS_W , val); } while (0)
DECL|macro|WCrt
mdefine_line|#define WCrt(ba, idx, val) &bslash;&n;do { wb_64(ba, CRT_ADDRESS, idx); wb_64(ba, CRT_ADDRESS_W , val); } while (0)
DECL|macro|WAttr
mdefine_line|#define WAttr(ba, idx, val) &bslash;&n;do { &bslash;&n;  unsigned char tmp;&bslash;&n;  tmp = rb_64(ba, ACT_ADDRESS_RESET);&bslash;&n;  wb_64(ba, ACT_ADDRESS_W, idx);&bslash;&n;  wb_64(ba, ACT_ADDRESS_W, val);&bslash;&n;} while (0)
DECL|macro|SetTextPlane
mdefine_line|#define SetTextPlane(ba, m) &bslash;&n;do { &bslash;&n;  WGfx(ba, GCT_ID_READ_MAP_SELECT, m &amp; 3 );&bslash;&n;  WSeq(ba, SEQ_ID_MAP_MASK, (1 &lt;&lt; (m &amp; 3)));&bslash;&n;} while (0)
multiline_comment|/* --------------------------------- */
multiline_comment|/* prototypes                        */
multiline_comment|/* --------------------------------- */
r_inline
r_int
r_char
id|RAttr
c_func
(paren
r_volatile
r_int
r_char
op_star
id|board
comma
r_int
id|idx
)paren
suffix:semicolon
r_inline
r_int
r_char
id|RSeq
c_func
(paren
r_volatile
r_int
r_char
op_star
id|board
comma
r_int
id|idx
)paren
suffix:semicolon
r_inline
r_int
r_char
id|RCrt
c_func
(paren
r_volatile
r_int
r_char
op_star
id|board
comma
r_int
id|idx
)paren
suffix:semicolon
r_inline
r_int
r_char
id|RGfx
c_func
(paren
r_volatile
r_int
r_char
op_star
id|board
comma
r_int
id|idx
)paren
suffix:semicolon
r_inline
r_void
id|cv64_write_port
c_func
(paren
r_int
r_int
id|bits
comma
r_volatile
r_int
r_char
op_star
id|board
)paren
suffix:semicolon
r_inline
r_void
id|cvscreen
c_func
(paren
r_int
id|toggle
comma
r_volatile
r_int
r_char
op_star
id|board
)paren
suffix:semicolon
r_inline
r_void
id|gfx_on_off
c_func
(paren
r_int
id|toggle
comma
r_volatile
r_int
r_char
op_star
id|board
)paren
suffix:semicolon
macro_line|#if 0
r_int
r_int
id|cv64_compute_clock
c_func
(paren
r_int
r_int
id|freq
)paren
suffix:semicolon
r_int
id|cv_has_4mb
c_func
(paren
r_volatile
r_int
r_char
op_star
id|fb
)paren
suffix:semicolon
r_void
id|cv64_board_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cv64_load_video_mode
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|video_mode
)paren
suffix:semicolon
macro_line|#endif
r_void
id|cvision_bitblt
c_func
(paren
id|u_short
id|sx
comma
id|u_short
id|sy
comma
id|u_short
id|dx
comma
id|u_short
id|dy
comma
id|u_short
id|w
comma
id|u_short
id|h
)paren
suffix:semicolon
r_void
id|cvision_clear
c_func
(paren
id|u_short
id|dx
comma
id|u_short
id|dy
comma
id|u_short
id|w
comma
id|u_short
id|h
comma
id|u_short
id|bg
)paren
suffix:semicolon
eof
