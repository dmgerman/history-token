multiline_comment|/*&n; * include/video/epson13xx.h -- Epson 13xx frame buffer&n; *&n; * Copyright (C) Hewlett-Packard Company.  All rights reserved.&n; *&n; * Written by Christopher Hoover &lt;ch@hpl.hp.com&gt;&n; *&n; */
macro_line|#ifndef _EPSON13XX_H_
DECL|macro|_EPSON13XX_H_
mdefine_line|#define _EPSON13XX_H_
DECL|macro|REG_REVISION_CODE
mdefine_line|#define REG_REVISION_CODE              0x00
DECL|macro|REG_MEMORY_CONFIG
mdefine_line|#define REG_MEMORY_CONFIG              0x01
DECL|macro|REG_PANEL_TYPE
mdefine_line|#define REG_PANEL_TYPE                 0x02
DECL|macro|REG_MOD_RATE
mdefine_line|#define REG_MOD_RATE                   0x03
DECL|macro|REG_HORZ_DISP_WIDTH
mdefine_line|#define REG_HORZ_DISP_WIDTH            0x04
DECL|macro|REG_HORZ_NONDISP_PERIOD
mdefine_line|#define REG_HORZ_NONDISP_PERIOD        0x05
DECL|macro|REG_HRTC_START_POSITION
mdefine_line|#define REG_HRTC_START_POSITION        0x06
DECL|macro|REG_HRTC_PULSE_WIDTH
mdefine_line|#define REG_HRTC_PULSE_WIDTH           0x07
DECL|macro|REG_VERT_DISP_HEIGHT0
mdefine_line|#define REG_VERT_DISP_HEIGHT0          0x08
DECL|macro|REG_VERT_DISP_HEIGHT1
mdefine_line|#define REG_VERT_DISP_HEIGHT1          0x09
DECL|macro|REG_VERT_NONDISP_PERIOD
mdefine_line|#define REG_VERT_NONDISP_PERIOD        0x0A
DECL|macro|REG_VRTC_START_POSITION
mdefine_line|#define REG_VRTC_START_POSITION        0x0B
DECL|macro|REG_VRTC_PULSE_WIDTH
mdefine_line|#define REG_VRTC_PULSE_WIDTH           0x0C
DECL|macro|REG_DISPLAY_MODE
mdefine_line|#define REG_DISPLAY_MODE               0x0D
DECL|macro|REG_SCRN1_LINE_COMPARE0
mdefine_line|#define REG_SCRN1_LINE_COMPARE0        0x0E
DECL|macro|REG_SCRN1_LINE_COMPARE1
mdefine_line|#define REG_SCRN1_LINE_COMPARE1        0x0F
DECL|macro|REG_SCRN1_DISP_START_ADDR0
mdefine_line|#define REG_SCRN1_DISP_START_ADDR0     0x10
DECL|macro|REG_SCRN1_DISP_START_ADDR1
mdefine_line|#define REG_SCRN1_DISP_START_ADDR1     0x11
DECL|macro|REG_SCRN1_DISP_START_ADDR2
mdefine_line|#define REG_SCRN1_DISP_START_ADDR2     0x12
DECL|macro|REG_SCRN2_DISP_START_ADDR0
mdefine_line|#define REG_SCRN2_DISP_START_ADDR0     0x13
DECL|macro|REG_SCRN2_DISP_START_ADDR1
mdefine_line|#define REG_SCRN2_DISP_START_ADDR1     0x14
DECL|macro|REG_SCRN2_DISP_START_ADDR2
mdefine_line|#define REG_SCRN2_DISP_START_ADDR2     0x15
DECL|macro|REG_MEM_ADDR_OFFSET0
mdefine_line|#define REG_MEM_ADDR_OFFSET0           0x16
DECL|macro|REG_MEM_ADDR_OFFSET1
mdefine_line|#define REG_MEM_ADDR_OFFSET1           0x17
DECL|macro|REG_PIXEL_PANNING
mdefine_line|#define REG_PIXEL_PANNING              0x18
DECL|macro|REG_CLOCK_CONFIG
mdefine_line|#define REG_CLOCK_CONFIG               0x19
DECL|macro|REG_POWER_SAVE_CONFIG
mdefine_line|#define REG_POWER_SAVE_CONFIG          0x1A
DECL|macro|REG_MISC
mdefine_line|#define REG_MISC                       0x1B
DECL|macro|REG_MD_CONFIG_READBACK0
mdefine_line|#define REG_MD_CONFIG_READBACK0        0x1C
DECL|macro|REG_MD_CONFIG_READBACK1
mdefine_line|#define REG_MD_CONFIG_READBACK1        0x1D
DECL|macro|REG_GPIO_CONFIG0
mdefine_line|#define REG_GPIO_CONFIG0               0x1E
DECL|macro|REG_GPIO_CONFIG1
mdefine_line|#define REG_GPIO_CONFIG1               0x1F
DECL|macro|REG_GPIO_CONTROL0
mdefine_line|#define REG_GPIO_CONTROL0              0x20
DECL|macro|REG_GPIO_CONTROL1
mdefine_line|#define REG_GPIO_CONTROL1              0x21
DECL|macro|REG_PERF_ENHANCEMENT0
mdefine_line|#define REG_PERF_ENHANCEMENT0          0x22
DECL|macro|REG_PERF_ENHANCEMENT1
mdefine_line|#define REG_PERF_ENHANCEMENT1          0x23
DECL|macro|REG_LUT_ADDR
mdefine_line|#define REG_LUT_ADDR                   0x24
DECL|macro|REG_RESERVED_1
mdefine_line|#define REG_RESERVED_1                 0x25
DECL|macro|REG_LUT_DATA
mdefine_line|#define REG_LUT_DATA                   0x26
DECL|macro|REG_INK_CURSOR_CONTROL
mdefine_line|#define REG_INK_CURSOR_CONTROL         0x27
DECL|macro|REG_CURSOR_X_POSITION0
mdefine_line|#define REG_CURSOR_X_POSITION0         0x28
DECL|macro|REG_CURSOR_X_POSITION1
mdefine_line|#define REG_CURSOR_X_POSITION1         0x29
DECL|macro|REG_CURSOR_Y_POSITION0
mdefine_line|#define REG_CURSOR_Y_POSITION0         0x2A
DECL|macro|REG_CURSOR_Y_POSITION1
mdefine_line|#define REG_CURSOR_Y_POSITION1         0x2B
DECL|macro|REG_INK_CURSOR_COLOR0_0
mdefine_line|#define REG_INK_CURSOR_COLOR0_0        0x2C
DECL|macro|REG_INK_CURSOR_COLOR0_1
mdefine_line|#define REG_INK_CURSOR_COLOR0_1        0x2D
DECL|macro|REG_INK_CURSOR_COLOR1_0
mdefine_line|#define REG_INK_CURSOR_COLOR1_0        0x2E
DECL|macro|REG_INK_CURSOR_COLOR1_1
mdefine_line|#define REG_INK_CURSOR_COLOR1_1        0x2F
DECL|macro|REG_INK_CURSOR_START_ADDR
mdefine_line|#define REG_INK_CURSOR_START_ADDR      0x30
DECL|macro|REG_ALTERNATE_FRM
mdefine_line|#define REG_ALTERNATE_FRM              0x31
macro_line|#endif
eof
