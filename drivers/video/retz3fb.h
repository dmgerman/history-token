multiline_comment|/*&n; * linux/drivers/video/retz3fb.h -- Defines and macros for the RetinaZ3 frame&n; *&t;&t;&t;&t;    buffer device&n; *&n; *    Copyright (C) 1997 Jes Sorensen&n; *&n; * History:&n; *   - 22 Jan 97: Initial work&n; *&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/*&n; * Macros to read and write to registers.&n; */
DECL|macro|reg_w
mdefine_line|#define reg_w(regs, reg,dat) (*(regs + reg) = dat)
DECL|macro|reg_r
mdefine_line|#define reg_r(regs, reg) (*(regs + reg))
multiline_comment|/*&n; * Macro to access the sequencer.&n; */
DECL|macro|seq_w
mdefine_line|#define seq_w(regs, sreg, sdat) &bslash;&n;&t;do{ reg_w(regs, SEQ_IDX, sreg); reg_w(regs, SEQ_DATA, sdat); } while(0)
multiline_comment|/*&n; * Macro to access the CRT controller.&n; */
DECL|macro|crt_w
mdefine_line|#define crt_w(regs, creg, cdat) &bslash;&n;&t;do{ reg_w(regs, CRT_IDX, creg); reg_w(regs, CRT_DATA, cdat); } while(0)
multiline_comment|/*&n; * Macro to access the graphics controller.&n; */
DECL|macro|gfx_w
mdefine_line|#define gfx_w(regs, greg, gdat) &bslash;&n;&t;do{ reg_w(regs, GFX_IDX, greg); reg_w(regs, GFX_DATA, gdat); } while(0)
multiline_comment|/*&n; * Macro to access the attribute controller.&n; */
DECL|macro|attr_w
mdefine_line|#define attr_w(regs, areg, adat) &bslash;&n;&t;do{ reg_w(regs, ACT_IDX, areg); reg_w(regs, ACT_DATA, adat); } while(0)
multiline_comment|/*&n; * Macro to access the pll.&n; */
DECL|macro|pll_w
mdefine_line|#define pll_w(regs, preg, pdat) &bslash;&n;&t;do{ reg_w(regs, PLL_IDX, preg); &bslash;&n;&t;    reg_w(regs, PLL_DATA, (pdat &amp; 0xff)); &bslash;&n;&t;    reg_w(regs, PLL_DATA, (pdat &gt;&gt; 8));&bslash;&n;&t;} while(0)
multiline_comment|/*&n; * Offsets&n; */
DECL|macro|VIDEO_MEM_OFFSET
mdefine_line|#define VIDEO_MEM_OFFSET&t;0x00c00000
DECL|macro|ACM_OFFSET
mdefine_line|#define ACM_OFFSET&t;&t;0x00b00000
multiline_comment|/*&n; * Accelerator Control Menu&n; */
DECL|macro|ACM_PRIMARY_OFFSET
mdefine_line|#define ACM_PRIMARY_OFFSET&t;0x00
DECL|macro|ACM_SECONDARY_OFFSET
mdefine_line|#define ACM_SECONDARY_OFFSET&t;0x04
DECL|macro|ACM_MODE_CONTROL
mdefine_line|#define ACM_MODE_CONTROL&t;0x08
DECL|macro|ACM_CURSOR_POSITION
mdefine_line|#define ACM_CURSOR_POSITION&t;0x0c
DECL|macro|ACM_START_STATUS
mdefine_line|#define ACM_START_STATUS&t;0x30
DECL|macro|ACM_CONTROL
mdefine_line|#define ACM_CONTROL&t;&t;0x34
DECL|macro|ACM_RASTEROP_ROTATION
mdefine_line|#define ACM_RASTEROP_ROTATION&t;0x38
DECL|macro|ACM_BITMAP_DIMENSION
mdefine_line|#define ACM_BITMAP_DIMENSION&t;0x3c
DECL|macro|ACM_DESTINATION
mdefine_line|#define ACM_DESTINATION&t;&t;0x40
DECL|macro|ACM_SOURCE
mdefine_line|#define ACM_SOURCE&t;&t;0x44
DECL|macro|ACM_PATTERN
mdefine_line|#define ACM_PATTERN&t;&t;0x48
DECL|macro|ACM_FOREGROUND
mdefine_line|#define ACM_FOREGROUND&t;&t;0x4c
DECL|macro|ACM_BACKGROUND
mdefine_line|#define ACM_BACKGROUND&t;&t;0x50
multiline_comment|/*&n; * Video DAC addresses&n; */
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
multiline_comment|/*&n; * Sequencer&n; */
DECL|macro|SEQ_IDX
mdefine_line|#define SEQ_IDX&t;&t;&t;0x03c4&t;/* Sequencer Index */
DECL|macro|SEQ_DATA
mdefine_line|#define SEQ_DATA&t;&t;0x03c5
DECL|macro|SEQ_RESET
mdefine_line|#define SEQ_RESET&t;&t;0x00
DECL|macro|SEQ_CLOCKING_MODE
mdefine_line|#define SEQ_CLOCKING_MODE&t;0x01
DECL|macro|SEQ_MAP_MASK
mdefine_line|#define SEQ_MAP_MASK&t;&t;0x02
DECL|macro|SEQ_CHAR_MAP_SELECT
mdefine_line|#define SEQ_CHAR_MAP_SELECT&t;0x03
DECL|macro|SEQ_MEMORY_MODE
mdefine_line|#define SEQ_MEMORY_MODE&t;&t;0x04
DECL|macro|SEQ_EXTENDED_ENABLE
mdefine_line|#define SEQ_EXTENDED_ENABLE&t;0x05&t;/* NCR extensions */
DECL|macro|SEQ_UNKNOWN1
mdefine_line|#define SEQ_UNKNOWN1         &t;0x06
DECL|macro|SEQ_UNKNOWN2
mdefine_line|#define SEQ_UNKNOWN2         &t;0x07
DECL|macro|SEQ_CHIP_ID
mdefine_line|#define SEQ_CHIP_ID&t;&t;0x08
DECL|macro|SEQ_UNKNOWN3
mdefine_line|#define SEQ_UNKNOWN3         &t;0x09
DECL|macro|SEQ_CURSOR_COLOR1
mdefine_line|#define SEQ_CURSOR_COLOR1&t;0x0a
DECL|macro|SEQ_CURSOR_COLOR0
mdefine_line|#define SEQ_CURSOR_COLOR0&t;0x0b
DECL|macro|SEQ_CURSOR_CONTROL
mdefine_line|#define SEQ_CURSOR_CONTROL&t;0x0c
DECL|macro|SEQ_CURSOR_X_LOC_HI
mdefine_line|#define SEQ_CURSOR_X_LOC_HI&t;0x0d
DECL|macro|SEQ_CURSOR_X_LOC_LO
mdefine_line|#define SEQ_CURSOR_X_LOC_LO&t;0x0e
DECL|macro|SEQ_CURSOR_Y_LOC_HI
mdefine_line|#define SEQ_CURSOR_Y_LOC_HI&t;0x0f
DECL|macro|SEQ_CURSOR_Y_LOC_LO
mdefine_line|#define SEQ_CURSOR_Y_LOC_LO&t;0x10
DECL|macro|SEQ_CURSOR_X_INDEX
mdefine_line|#define SEQ_CURSOR_X_INDEX&t;0x11
DECL|macro|SEQ_CURSOR_Y_INDEX
mdefine_line|#define SEQ_CURSOR_Y_INDEX&t;0x12
DECL|macro|SEQ_CURSOR_STORE_HI
mdefine_line|#define SEQ_CURSOR_STORE_HI&t;0x13
DECL|macro|SEQ_CURSOR_STORE_LO
mdefine_line|#define SEQ_CURSOR_STORE_LO&t;0x14
DECL|macro|SEQ_CURSOR_ST_OFF_HI
mdefine_line|#define SEQ_CURSOR_ST_OFF_HI&t;0x15
DECL|macro|SEQ_CURSOR_ST_OFF_LO
mdefine_line|#define SEQ_CURSOR_ST_OFF_LO&t;0x16
DECL|macro|SEQ_CURSOR_PIXELMASK
mdefine_line|#define SEQ_CURSOR_PIXELMASK&t;0x17
DECL|macro|SEQ_PRIM_HOST_OFF_HI
mdefine_line|#define SEQ_PRIM_HOST_OFF_HI&t;0x18
DECL|macro|SEQ_PRIM_HOST_OFF_LO
mdefine_line|#define SEQ_PRIM_HOST_OFF_LO&t;0x19
DECL|macro|SEQ_LINEAR_0
mdefine_line|#define SEQ_LINEAR_0&t;&t;0x1a
DECL|macro|SEQ_LINEAR_1
mdefine_line|#define SEQ_LINEAR_1&t;&t;0x1b
DECL|macro|SEQ_SEC_HOST_OFF_HI
mdefine_line|#define SEQ_SEC_HOST_OFF_HI&t;0x1c
DECL|macro|SEQ_SEC_HOST_OFF_LO
mdefine_line|#define SEQ_SEC_HOST_OFF_LO&t;0x1d
DECL|macro|SEQ_EXTENDED_MEM_ENA
mdefine_line|#define SEQ_EXTENDED_MEM_ENA&t;0x1e
DECL|macro|SEQ_EXT_CLOCK_MODE
mdefine_line|#define SEQ_EXT_CLOCK_MODE&t;0x1f
DECL|macro|SEQ_EXT_VIDEO_ADDR
mdefine_line|#define SEQ_EXT_VIDEO_ADDR&t;0x20
DECL|macro|SEQ_EXT_PIXEL_CNTL
mdefine_line|#define SEQ_EXT_PIXEL_CNTL&t;0x21
DECL|macro|SEQ_BUS_WIDTH_FEEDB
mdefine_line|#define SEQ_BUS_WIDTH_FEEDB&t;0x22
DECL|macro|SEQ_PERF_SELECT
mdefine_line|#define SEQ_PERF_SELECT&t;&t;0x23
DECL|macro|SEQ_COLOR_EXP_WFG
mdefine_line|#define SEQ_COLOR_EXP_WFG&t;0x24
DECL|macro|SEQ_COLOR_EXP_WBG
mdefine_line|#define SEQ_COLOR_EXP_WBG&t;0x25
DECL|macro|SEQ_EXT_RW_CONTROL
mdefine_line|#define SEQ_EXT_RW_CONTROL&t;0x26
DECL|macro|SEQ_MISC_FEATURE_SEL
mdefine_line|#define SEQ_MISC_FEATURE_SEL&t;0x27
DECL|macro|SEQ_COLOR_KEY_CNTL
mdefine_line|#define SEQ_COLOR_KEY_CNTL&t;0x28
DECL|macro|SEQ_COLOR_KEY_MATCH0
mdefine_line|#define SEQ_COLOR_KEY_MATCH0&t;0x29
DECL|macro|SEQ_COLOR_KEY_MATCH1
mdefine_line|#define SEQ_COLOR_KEY_MATCH1 &t;0x2a
DECL|macro|SEQ_COLOR_KEY_MATCH2
mdefine_line|#define SEQ_COLOR_KEY_MATCH2 &t;0x2b
DECL|macro|SEQ_UNKNOWN6
mdefine_line|#define SEQ_UNKNOWN6         &t;0x2c
DECL|macro|SEQ_CRC_CONTROL
mdefine_line|#define SEQ_CRC_CONTROL&t;&t;0x2d
DECL|macro|SEQ_CRC_DATA_LOW
mdefine_line|#define SEQ_CRC_DATA_LOW&t;0x2e
DECL|macro|SEQ_CRC_DATA_HIGH
mdefine_line|#define SEQ_CRC_DATA_HIGH&t;0x2f
DECL|macro|SEQ_MEMORY_MAP_CNTL
mdefine_line|#define SEQ_MEMORY_MAP_CNTL&t;0x30
DECL|macro|SEQ_ACM_APERTURE_1
mdefine_line|#define SEQ_ACM_APERTURE_1&t;0x31
DECL|macro|SEQ_ACM_APERTURE_2
mdefine_line|#define SEQ_ACM_APERTURE_2&t;0x32
DECL|macro|SEQ_ACM_APERTURE_3
mdefine_line|#define SEQ_ACM_APERTURE_3&t;0x33
DECL|macro|SEQ_BIOS_UTILITY_0
mdefine_line|#define SEQ_BIOS_UTILITY_0&t;0x3e
DECL|macro|SEQ_BIOS_UTILITY_1
mdefine_line|#define SEQ_BIOS_UTILITY_1&t;0x3f
multiline_comment|/*&n; * Graphics Controller&n; */
DECL|macro|GFX_IDX
mdefine_line|#define GFX_IDX&t;&t;&t;0x03ce
DECL|macro|GFX_DATA
mdefine_line|#define GFX_DATA&t;&t;0x03cf
DECL|macro|GFX_SET_RESET
mdefine_line|#define GFX_SET_RESET&t;&t;0x00
DECL|macro|GFX_ENABLE_SET_RESET
mdefine_line|#define GFX_ENABLE_SET_RESET&t;0x01
DECL|macro|GFX_COLOR_COMPARE
mdefine_line|#define GFX_COLOR_COMPARE&t;0x02
DECL|macro|GFX_DATA_ROTATE
mdefine_line|#define GFX_DATA_ROTATE&t;&t;0x03
DECL|macro|GFX_READ_MAP_SELECT
mdefine_line|#define GFX_READ_MAP_SELECT&t;0x04
DECL|macro|GFX_GRAPHICS_MODE
mdefine_line|#define GFX_GRAPHICS_MODE&t;0x05
DECL|macro|GFX_MISC
mdefine_line|#define GFX_MISC&t;&t;0x06
DECL|macro|GFX_COLOR_XCARE
mdefine_line|#define GFX_COLOR_XCARE&t;&t;0x07
DECL|macro|GFX_BITMASK
mdefine_line|#define GFX_BITMASK&t;&t;0x08
multiline_comment|/*&n; * CRT Controller&n; */
DECL|macro|CRT_IDX
mdefine_line|#define CRT_IDX&t;&t;&t;0x03d4
DECL|macro|CRT_DATA
mdefine_line|#define CRT_DATA&t;&t;0x03d5
DECL|macro|CRT_HOR_TOTAL
mdefine_line|#define CRT_HOR_TOTAL&t;&t;0x00
DECL|macro|CRT_HOR_DISP_ENA_END
mdefine_line|#define CRT_HOR_DISP_ENA_END&t;0x01
DECL|macro|CRT_START_HOR_BLANK
mdefine_line|#define CRT_START_HOR_BLANK&t;0x02
DECL|macro|CRT_END_HOR_BLANK
mdefine_line|#define CRT_END_HOR_BLANK&t;0x03
DECL|macro|CRT_START_HOR_RETR
mdefine_line|#define CRT_START_HOR_RETR&t;0x04
DECL|macro|CRT_END_HOR_RETR
mdefine_line|#define CRT_END_HOR_RETR&t;0x05
DECL|macro|CRT_VER_TOTAL
mdefine_line|#define CRT_VER_TOTAL&t;&t;0x06
DECL|macro|CRT_OVERFLOW
mdefine_line|#define CRT_OVERFLOW&t;&t;0x07
DECL|macro|CRT_PRESET_ROW_SCAN
mdefine_line|#define CRT_PRESET_ROW_SCAN&t;0x08
DECL|macro|CRT_MAX_SCAN_LINE
mdefine_line|#define CRT_MAX_SCAN_LINE&t;0x09
DECL|macro|CRT_CURSOR_START
mdefine_line|#define CRT_CURSOR_START&t;0x0a
DECL|macro|CRT_CURSOR_END
mdefine_line|#define CRT_CURSOR_END&t;&t;0x0b
DECL|macro|CRT_START_ADDR_HIGH
mdefine_line|#define CRT_START_ADDR_HIGH&t;0x0c
DECL|macro|CRT_START_ADDR_LOW
mdefine_line|#define CRT_START_ADDR_LOW&t;0x0d
DECL|macro|CRT_CURSOR_LOC_HIGH
mdefine_line|#define CRT_CURSOR_LOC_HIGH&t;0x0e
DECL|macro|CRT_CURSOR_LOC_LOW
mdefine_line|#define CRT_CURSOR_LOC_LOW&t;0x0f
DECL|macro|CRT_START_VER_RETR
mdefine_line|#define CRT_START_VER_RETR&t;0x10
DECL|macro|CRT_END_VER_RETR
mdefine_line|#define CRT_END_VER_RETR&t;0x11
DECL|macro|CRT_VER_DISP_ENA_END
mdefine_line|#define CRT_VER_DISP_ENA_END&t;0x12
DECL|macro|CRT_OFFSET
mdefine_line|#define CRT_OFFSET&t;&t;0x13
DECL|macro|CRT_UNDERLINE_LOC
mdefine_line|#define CRT_UNDERLINE_LOC&t;0x14
DECL|macro|CRT_START_VER_BLANK
mdefine_line|#define CRT_START_VER_BLANK&t;0x15
DECL|macro|CRT_END_VER_BLANK
mdefine_line|#define CRT_END_VER_BLANK&t;0x16
DECL|macro|CRT_MODE_CONTROL
mdefine_line|#define CRT_MODE_CONTROL&t;0x17
DECL|macro|CRT_LINE_COMPARE
mdefine_line|#define CRT_LINE_COMPARE&t;0x18
DECL|macro|CRT_UNKNOWN1
mdefine_line|#define CRT_UNKNOWN1         &t;0x19
DECL|macro|CRT_UNKNOWN2
mdefine_line|#define CRT_UNKNOWN2         &t;0x1a
DECL|macro|CRT_UNKNOWN3
mdefine_line|#define CRT_UNKNOWN3         &t;0x1b
DECL|macro|CRT_UNKNOWN4
mdefine_line|#define CRT_UNKNOWN4         &t;0x1c
DECL|macro|CRT_UNKNOWN5
mdefine_line|#define CRT_UNKNOWN5         &t;0x1d
DECL|macro|CRT_UNKNOWN6
mdefine_line|#define CRT_UNKNOWN6         &t;0x1e
DECL|macro|CRT_UNKNOWN7
mdefine_line|#define CRT_UNKNOWN7         &t;0x1f
DECL|macro|CRT_UNKNOWN8
mdefine_line|#define CRT_UNKNOWN8         &t;0x20
DECL|macro|CRT_UNKNOWN9
mdefine_line|#define CRT_UNKNOWN9&t;&t;0x21
DECL|macro|CRT_UNKNOWN10
mdefine_line|#define CRT_UNKNOWN10&t;&t;0x22
DECL|macro|CRT_UNKNOWN11
mdefine_line|#define CRT_UNKNOWN11      &t;0x23
DECL|macro|CRT_UNKNOWN12
mdefine_line|#define CRT_UNKNOWN12      &t;0x24
DECL|macro|CRT_UNKNOWN13
mdefine_line|#define CRT_UNKNOWN13      &t;0x25
DECL|macro|CRT_UNKNOWN14
mdefine_line|#define CRT_UNKNOWN14      &t;0x26
DECL|macro|CRT_UNKNOWN15
mdefine_line|#define CRT_UNKNOWN15      &t;0x27
DECL|macro|CRT_UNKNOWN16
mdefine_line|#define CRT_UNKNOWN16      &t;0x28
DECL|macro|CRT_UNKNOWN17
mdefine_line|#define CRT_UNKNOWN17      &t;0x29
DECL|macro|CRT_UNKNOWN18
mdefine_line|#define CRT_UNKNOWN18      &t;0x2a
DECL|macro|CRT_UNKNOWN19
mdefine_line|#define CRT_UNKNOWN19      &t;0x2b
DECL|macro|CRT_UNKNOWN20
mdefine_line|#define CRT_UNKNOWN20      &t;0x2c
DECL|macro|CRT_UNKNOWN21
mdefine_line|#define CRT_UNKNOWN21      &t;0x2d
DECL|macro|CRT_UNKNOWN22
mdefine_line|#define CRT_UNKNOWN22      &t;0x2e
DECL|macro|CRT_UNKNOWN23
mdefine_line|#define CRT_UNKNOWN23      &t;0x2f
DECL|macro|CRT_EXT_HOR_TIMING1
mdefine_line|#define CRT_EXT_HOR_TIMING1&t;0x30&t;/* NCR crt extensions */
DECL|macro|CRT_EXT_START_ADDR
mdefine_line|#define CRT_EXT_START_ADDR&t;0x31
DECL|macro|CRT_EXT_HOR_TIMING2
mdefine_line|#define CRT_EXT_HOR_TIMING2&t;0x32
DECL|macro|CRT_EXT_VER_TIMING
mdefine_line|#define CRT_EXT_VER_TIMING&t;0x33
DECL|macro|CRT_MONITOR_POWER
mdefine_line|#define CRT_MONITOR_POWER&t;0x34
multiline_comment|/*&n; * General Registers&n; */
DECL|macro|GREG_STATUS0_R
mdefine_line|#define GREG_STATUS0_R&t;&t;0x03c2
DECL|macro|GREG_STATUS1_R
mdefine_line|#define GREG_STATUS1_R&t;&t;0x03da
DECL|macro|GREG_MISC_OUTPUT_R
mdefine_line|#define GREG_MISC_OUTPUT_R&t;0x03cc
DECL|macro|GREG_MISC_OUTPUT_W
mdefine_line|#define GREG_MISC_OUTPUT_W&t;0x03c2&t;
DECL|macro|GREG_FEATURE_CONTROL_R
mdefine_line|#define GREG_FEATURE_CONTROL_R&t;0x03ca
DECL|macro|GREG_FEATURE_CONTROL_W
mdefine_line|#define GREG_FEATURE_CONTROL_W&t;0x03da
DECL|macro|GREG_POS
mdefine_line|#define GREG_POS&t;&t;0x0102
multiline_comment|/*&n; * Attribute Controller&n; */
DECL|macro|ACT_IDX
mdefine_line|#define ACT_IDX&t;&t;&t;0x03C0
DECL|macro|ACT_ADDRESS_R
mdefine_line|#define ACT_ADDRESS_R&t;&t;0x03C0
DECL|macro|ACT_DATA
mdefine_line|#define ACT_DATA&t;&t;0x03C0
DECL|macro|ACT_ADDRESS_RESET
mdefine_line|#define ACT_ADDRESS_RESET&t;0x03DA
DECL|macro|ACT_PALETTE0
mdefine_line|#define ACT_PALETTE0&t;&t;0x00
DECL|macro|ACT_PALETTE1
mdefine_line|#define ACT_PALETTE1&t;&t;0x01
DECL|macro|ACT_PALETTE2
mdefine_line|#define ACT_PALETTE2&t;&t;0x02
DECL|macro|ACT_PALETTE3
mdefine_line|#define ACT_PALETTE3&t;&t;0x03
DECL|macro|ACT_PALETTE4
mdefine_line|#define ACT_PALETTE4&t;&t;0x04
DECL|macro|ACT_PALETTE5
mdefine_line|#define ACT_PALETTE5&t;&t;0x05
DECL|macro|ACT_PALETTE6
mdefine_line|#define ACT_PALETTE6&t;&t;0x06
DECL|macro|ACT_PALETTE7
mdefine_line|#define ACT_PALETTE7&t;&t;0x07
DECL|macro|ACT_PALETTE8
mdefine_line|#define ACT_PALETTE8&t;&t;0x08
DECL|macro|ACT_PALETTE9
mdefine_line|#define ACT_PALETTE9&t;&t;0x09
DECL|macro|ACT_PALETTE10
mdefine_line|#define ACT_PALETTE10&t;&t;0x0A
DECL|macro|ACT_PALETTE11
mdefine_line|#define ACT_PALETTE11&t;&t;0x0B
DECL|macro|ACT_PALETTE12
mdefine_line|#define ACT_PALETTE12&t;&t;0x0C
DECL|macro|ACT_PALETTE13
mdefine_line|#define ACT_PALETTE13&t;&t;0x0D
DECL|macro|ACT_PALETTE14
mdefine_line|#define ACT_PALETTE14&t;&t;0x0E
DECL|macro|ACT_PALETTE15
mdefine_line|#define ACT_PALETTE15&t;&t;0x0F
DECL|macro|ACT_ATTR_MODE_CNTL
mdefine_line|#define ACT_ATTR_MODE_CNTL&t;0x10
DECL|macro|ACT_OVERSCAN_COLOR
mdefine_line|#define ACT_OVERSCAN_COLOR&t;0x11
DECL|macro|ACT_COLOR_PLANE_ENA
mdefine_line|#define ACT_COLOR_PLANE_ENA&t;0x12
DECL|macro|ACT_HOR_PEL_PANNING
mdefine_line|#define ACT_HOR_PEL_PANNING&t;0x13
DECL|macro|ACT_COLOR_SELECT
mdefine_line|#define ACT_COLOR_SELECT&t;0x14
multiline_comment|/*&n; * PLL&n; */
DECL|macro|PLL_IDX
mdefine_line|#define PLL_IDX&t;&t;&t;0x83c8
DECL|macro|PLL_DATA
mdefine_line|#define PLL_DATA&t;&t;0x83c9
multiline_comment|/*&n; * Blitter operations&n; */
DECL|macro|Z3BLTclear
mdefine_line|#define&t;Z3BLTclear&t;&t;0x00&t;/* 0 */
DECL|macro|Z3BLTand
mdefine_line|#define Z3BLTand&t;&t;0x80&t;/* src AND dst */
DECL|macro|Z3BLTandReverse
mdefine_line|#define Z3BLTandReverse&t;&t;0x40&t;/* src AND NOT dst */
DECL|macro|Z3BLTcopy
mdefine_line|#define Z3BLTcopy&t;&t;0xc0&t;/* src */
DECL|macro|Z3BLTandInverted
mdefine_line|#define Z3BLTandInverted&t;0x20&t;/* NOT src AND dst */
DECL|macro|Z3BLTnoop
mdefine_line|#define&t;Z3BLTnoop&t;&t;0xa0&t;/* dst */
DECL|macro|Z3BLTxor
mdefine_line|#define Z3BLTxor&t;&t;0x60&t;/* src XOR dst */
DECL|macro|Z3BLTor
mdefine_line|#define Z3BLTor&t;&t;&t;0xe0&t;/* src OR dst */
DECL|macro|Z3BLTnor
mdefine_line|#define Z3BLTnor&t;&t;0x10&t;/* NOT src AND NOT dst */
DECL|macro|Z3BLTequiv
mdefine_line|#define Z3BLTequiv&t;&t;0x90&t;/* NOT src XOR dst */
DECL|macro|Z3BLTinvert
mdefine_line|#define Z3BLTinvert&t;&t;0x50&t;/* NOT dst */
DECL|macro|Z3BLTorReverse
mdefine_line|#define Z3BLTorReverse&t;&t;0xd0&t;/* src OR NOT dst */
DECL|macro|Z3BLTcopyInverted
mdefine_line|#define Z3BLTcopyInverted&t;0x30&t;/* NOT src */
DECL|macro|Z3BLTorInverted
mdefine_line|#define Z3BLTorInverted&t;&t;0xb0&t;/* NOT src OR dst */
DECL|macro|Z3BLTnand
mdefine_line|#define Z3BLTnand&t;&t;0x70&t;/* NOT src OR NOT dst */
DECL|macro|Z3BLTset
mdefine_line|#define Z3BLTset&t;&t;0xf0&t;/* 1 */
eof
