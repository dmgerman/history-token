multiline_comment|/*&n; * linux/drivers/video/virgefb.h -- CyberVision64 definitions for the&n; *                                  text console driver.&n; *&n; *   Copyright (c) 1998 Alan Bair&n; *&n; * This file is based on the initial port to Linux of grf_cvreg.h:&n; *&n; *   Copyright (c) 1997 Antonio Santos&n; *&n; * The original work is from the NetBSD CyberVision 64 framebuffer driver &n; * and support files (grf_cv.c, grf_cvreg.h, ite_cv.c):&n; * Permission to use the source of this driver was obtained from the&n; * author Michael Teske by Alan Bair.&n; *&n; *   Copyright (c) 1995 Michael Teske&n; *&n; * History:&n; *&n; *&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/* Enhanced register mapping (MMIO mode) */
DECL|macro|S3_CRTC_ADR
mdefine_line|#define S3_CRTC_ADR    0x03d4
DECL|macro|S3_CRTC_DATA
mdefine_line|#define S3_CRTC_DATA   0x03d5
DECL|macro|S3_REG_LOCK2
mdefine_line|#define S3_REG_LOCK2&t;0x39
DECL|macro|S3_HGC_MODE
mdefine_line|#define S3_HGC_MODE&t;0x45
DECL|macro|S3_HWGC_ORGX_H
mdefine_line|#define S3_HWGC_ORGX_H&t;0x46
DECL|macro|S3_HWGC_ORGX_L
mdefine_line|#define S3_HWGC_ORGX_L&t;0x47
DECL|macro|S3_HWGC_ORGY_H
mdefine_line|#define S3_HWGC_ORGY_H&t;0x48
DECL|macro|S3_HWGC_ORGY_L
mdefine_line|#define S3_HWGC_ORGY_L&t;0x49
DECL|macro|S3_HWGC_DX
mdefine_line|#define S3_HWGC_DX&t;0x4e
DECL|macro|S3_HWGC_DY
mdefine_line|#define S3_HWGC_DY&t;0x4f
DECL|macro|S3_LAW_CTL
mdefine_line|#define S3_LAW_CTL&t;0x58
multiline_comment|/**************************************************/
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
DECL|macro|SREG_VIDEO_SUBS_ENABLE
mdefine_line|#define SREG_VIDEO_SUBS_ENABLE&t;0x03C3&t;/* virge */
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
mdefine_line|#define ACT_ID_COLOR_SELECT&t;0x14    /* virge PX_PADD  pixel padding register */
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
mdefine_line|#define SEQ_ID_EXT_SEQ_REG9&t;0x09&t;/* b7 = 1 extended reg access by MMIO only */
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
mdefine_line|#define SEQ_ID_CLKSYN_TEST_LO&t;0x17&t;/* internal clock synthesizer   */
DECL|macro|SEQ_ID_RAMDAC_CNTL
mdefine_line|#define SEQ_ID_RAMDAC_CNTL&t;0x18
DECL|macro|SEQ_ID_MORE_MAGIC
mdefine_line|#define SEQ_ID_MORE_MAGIC&t;0x1A
DECL|macro|SEQ_ID_SIGNAL_SELECT
mdefine_line|#define SEQ_ID_SIGNAL_SELECT&t;0x1C&t;/* new for virge */
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
mdefine_line|#define CRT_ID_EXT_SYS_CNTL_1&t;0x50&t;/* NOT a virge register */
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
mdefine_line|#define CRT_ID_EXT_MEM_CNTL_3&t;0x60&t;/* NOT a virge register */
DECL|macro|CRT_ID_EXT_MEM_CNTL_4
mdefine_line|#define CRT_ID_EXT_MEM_CNTL_4&t;0x61
DECL|macro|CRT_ID_EX_SYNC_3
mdefine_line|#define CRT_ID_EX_SYNC_3&t;0x63&t;/* NOT a virge register */
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
multiline_comment|/* S3 virge extensions: more System Extension Registers  */
DECL|macro|CRT_ID_EXT_BIOS_FLAG_5
mdefine_line|#define CRT_ID_EXT_BIOS_FLAG_5&t;0x6D
DECL|macro|CRT_ID_EXT_DAC_TEST
mdefine_line|#define CRT_ID_EXT_DAC_TEST&t;0x6E
DECL|macro|CRT_ID_CONFIG_4
mdefine_line|#define CRT_ID_CONFIG_4 &t;0x6F
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
multiline_comment|/* Miscellaneous Registers */
DECL|macro|MR_SUBSYSTEM_STATUS_R
mdefine_line|#define MR_SUBSYSTEM_STATUS_R&t;&t;0x8504&t;/* new for virge */
DECL|macro|MR_SUBSYSTEM_CNTL_W
mdefine_line|#define MR_SUBSYSTEM_CNTL_W&t;&t;0x8504&t;/* new for virge */
DECL|macro|MR_ADVANCED_FUNCTION_CONTROL
mdefine_line|#define MR_ADVANCED_FUNCTION_CONTROL&t;0x850C&t;/* new for virge */
multiline_comment|/* Blitter  */
DECL|macro|BLT_COMMAND_SET
mdefine_line|#define BLT_COMMAND_SET&t;&t;0xA500
DECL|macro|BLT_SIZE_X_Y
mdefine_line|#define BLT_SIZE_X_Y&t;&t;0xA504
DECL|macro|BLT_SRC_X_Y
mdefine_line|#define BLT_SRC_X_Y&t;&t;0xA508
DECL|macro|BLT_DEST_X_Y
mdefine_line|#define BLT_DEST_X_Y&t;&t;0xA50C
DECL|macro|BLT_SRC_BASE
mdefine_line|#define BLT_SRC_BASE&t;&t;0xa4d4
DECL|macro|BLT_DEST_BASE
mdefine_line|#define BLT_DEST_BASE&t;&t;0xa4d8
DECL|macro|BLT_CLIP_LEFT_RIGHT
mdefine_line|#define BLT_CLIP_LEFT_RIGHT&t;0xa4dc
DECL|macro|BLT_CLIP_TOP_BOTTOM
mdefine_line|#define BLT_CLIP_TOP_BOTTOM&t;0xa4e0
DECL|macro|BLT_SRC_DEST_STRIDE
mdefine_line|#define BLT_SRC_DEST_STRIDE&t;0xa4e4
DECL|macro|BLT_MONO_PATTERN_0
mdefine_line|#define BLT_MONO_PATTERN_0&t;0xa4e8
DECL|macro|BLT_MONO_PATTERN_1
mdefine_line|#define BLT_MONO_PATTERN_1&t;0xa4ec
DECL|macro|BLT_PATTERN_COLOR
mdefine_line|#define BLT_PATTERN_COLOR&t;0xa4f4
DECL|macro|L2D_COMMAND_SET
mdefine_line|#define L2D_COMMAND_SET&t;&t;0xA900
DECL|macro|L2D_CLIP_LEFT_RIGHT
mdefine_line|#define L2D_CLIP_LEFT_RIGHT&t;0xA8DC
DECL|macro|L2D_CLIP_TOP_BOTTOM
mdefine_line|#define L2D_CLIP_TOP_BOTTOM&t;0xA8E0
DECL|macro|P2D_COMMAND_SET
mdefine_line|#define P2D_COMMAND_SET&t;&t;0xAD00
DECL|macro|P2D_CLIP_LEFT_RIGHT
mdefine_line|#define P2D_CLIP_LEFT_RIGHT&t;0xACDC
DECL|macro|P2D_CLIP_TOP_BOTTOM
mdefine_line|#define P2D_CLIP_TOP_BOTTOM&t;0xACE0
DECL|macro|CMD_NOP
mdefine_line|#define CMD_NOP&t;&t;(0xf &lt;&lt; 27)&t;/* %1111 &lt;&lt; 27, was 0x07 */ 
DECL|macro|S3V_BITBLT
mdefine_line|#define S3V_BITBLT&t;(0x0 &lt;&lt; 27)
DECL|macro|S3V_RECTFILL
mdefine_line|#define S3V_RECTFILL&t;(0x2 &lt;&lt; 27)
DECL|macro|S3V_AUTOEXE
mdefine_line|#define S3V_AUTOEXE&t;0x01
DECL|macro|S3V_HWCLIP
mdefine_line|#define S3V_HWCLIP&t;0x02
DECL|macro|S3V_DRAW
mdefine_line|#define S3V_DRAW&t;0x20
DECL|macro|S3V_DST_8BPP
mdefine_line|#define S3V_DST_8BPP&t;0x00
DECL|macro|S3V_DST_16BPP
mdefine_line|#define S3V_DST_16BPP&t;0x04
DECL|macro|S3V_DST_24BPP
mdefine_line|#define S3V_DST_24BPP&t;0x08
DECL|macro|S3V_MONO_PAT
mdefine_line|#define S3V_MONO_PAT&t;0x100
DECL|macro|S3V_BLT_COPY
mdefine_line|#define S3V_BLT_COPY&t;(0xcc&lt;&lt;17)
DECL|macro|S3V_BLT_CLEAR
mdefine_line|#define S3V_BLT_CLEAR&t;(0x00&lt;&lt;17)
DECL|macro|S3V_BLT_SET
mdefine_line|#define S3V_BLT_SET&t;(0xff&lt;&lt;17)
eof
