multiline_comment|/*&n; * ATI Mach64 Register Definitions&n; *&n; * Copyright (C) 1997 Michael AK Tesch&n; *  written with much help from Jon Howell&n; *&n; * Updated for 3D RAGE PRO and 3D RAGE Mobility by Geert Uytterhoeven&n; *&t;&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; * most of the rest of this file comes from ATI sample code&n; */
macro_line|#ifndef REGMACH64_H
DECL|macro|REGMACH64_H
mdefine_line|#define REGMACH64_H
multiline_comment|/* NON-GUI MEMORY MAPPED Registers - expressed in BYTE offsets */
multiline_comment|/* Accelerator CRTC */
DECL|macro|CRTC_H_TOTAL_DISP
mdefine_line|#define CRTC_H_TOTAL_DISP&t;0x0000&t;/* Dword offset 0_00 */
DECL|macro|CRTC2_H_TOTAL_DISP
mdefine_line|#define CRTC2_H_TOTAL_DISP&t;0x0000&t;/* Dword offset 0_00 */
DECL|macro|CRTC_H_SYNC_STRT_WID
mdefine_line|#define CRTC_H_SYNC_STRT_WID&t;0x0004&t;/* Dword offset 0_01 */
DECL|macro|CRTC2_H_SYNC_STRT_WID
mdefine_line|#define CRTC2_H_SYNC_STRT_WID&t;0x0004&t;/* Dword offset 0_01 */
DECL|macro|CRTC_H_SYNC_STRT
mdefine_line|#define CRTC_H_SYNC_STRT&t;0x0004
DECL|macro|CRTC2_H_SYNC_STRT
mdefine_line|#define CRTC2_H_SYNC_STRT&t;0x0004
DECL|macro|CRTC_H_SYNC_DLY
mdefine_line|#define CRTC_H_SYNC_DLY&t;&t;0x0005
DECL|macro|CRTC2_H_SYNC_DLY
mdefine_line|#define CRTC2_H_SYNC_DLY&t;0x0005
DECL|macro|CRTC_H_SYNC_WID
mdefine_line|#define CRTC_H_SYNC_WID&t;&t;0x0006
DECL|macro|CRTC2_H_SYNC_WID
mdefine_line|#define CRTC2_H_SYNC_WID&t;0x0006
DECL|macro|CRTC_V_TOTAL_DISP
mdefine_line|#define CRTC_V_TOTAL_DISP&t;0x0008&t;/* Dword offset 0_02 */
DECL|macro|CRTC2_V_TOTAL_DISP
mdefine_line|#define CRTC2_V_TOTAL_DISP&t;0x0008&t;/* Dword offset 0_02 */
DECL|macro|CRTC_V_TOTAL
mdefine_line|#define CRTC_V_TOTAL&t;&t;0x0008
DECL|macro|CRTC2_V_TOTAL
mdefine_line|#define CRTC2_V_TOTAL&t;&t;0x0008
DECL|macro|CRTC_V_DISP
mdefine_line|#define CRTC_V_DISP&t;&t;0x000A
DECL|macro|CRTC2_V_DISP
mdefine_line|#define CRTC2_V_DISP&t;&t;0x000A
DECL|macro|CRTC_V_SYNC_STRT_WID
mdefine_line|#define CRTC_V_SYNC_STRT_WID&t;0x000C&t;/* Dword offset 0_03 */
DECL|macro|CRTC2_V_SYNC_STRT_WID
mdefine_line|#define CRTC2_V_SYNC_STRT_WID&t;0x000C&t;/* Dword offset 0_03 */
DECL|macro|CRTC_V_SYNC_STRT
mdefine_line|#define CRTC_V_SYNC_STRT&t;0x000C
DECL|macro|CRTC2_V_SYNC_STRT
mdefine_line|#define CRTC2_V_SYNC_STRT&t;0x000C
DECL|macro|CRTC_V_SYNC_WID
mdefine_line|#define CRTC_V_SYNC_WID&t;&t;0x000E
DECL|macro|CRTC2_V_SYNC_WID
mdefine_line|#define CRTC2_V_SYNC_WID&t;0x000E
DECL|macro|CRTC_VLINE_CRNT_VLINE
mdefine_line|#define CRTC_VLINE_CRNT_VLINE&t;0x0010&t;/* Dword offset 0_04 */
DECL|macro|CRTC2_VLINE_CRNT_VLINE
mdefine_line|#define CRTC2_VLINE_CRNT_VLINE&t;0x0010&t;/* Dword offset 0_04 */
DECL|macro|CRTC_OFF_PITCH
mdefine_line|#define CRTC_OFF_PITCH&t;&t;0x0014&t;/* Dword offset 0_05 */
DECL|macro|CRTC_OFFSET
mdefine_line|#define CRTC_OFFSET&t;&t;0x0014
DECL|macro|CRTC_PITCH
mdefine_line|#define CRTC_PITCH&t;&t;0x0016
DECL|macro|CRTC_INT_CNTL
mdefine_line|#define CRTC_INT_CNTL&t;&t;0x0018&t;/* Dword offset 0_06 */
DECL|macro|CRTC_GEN_CNTL
mdefine_line|#define CRTC_GEN_CNTL&t;&t;0x001C&t;/* Dword offset 0_07 */
DECL|macro|CRTC_PIX_WIDTH
mdefine_line|#define CRTC_PIX_WIDTH&t;&t;0x001D
DECL|macro|CRTC_FIFO
mdefine_line|#define CRTC_FIFO&t;&t;0x001E
DECL|macro|CRTC_EXT_DISP
mdefine_line|#define CRTC_EXT_DISP&t;&t;0x001F
multiline_comment|/* Memory Buffer Control */
DECL|macro|DSP_CONFIG
mdefine_line|#define DSP_CONFIG&t;&t;0x0020&t;/* Dword offset 0_08 */
DECL|macro|PM_DSP_CONFIG
mdefine_line|#define PM_DSP_CONFIG&t;&t;0x0020&t;/* Dword offset 0_08 (Mobility Only) */
DECL|macro|DSP_ON_OFF
mdefine_line|#define DSP_ON_OFF&t;&t;0x0024&t;/* Dword offset 0_09 */
DECL|macro|PM_DSP_ON_OFF
mdefine_line|#define PM_DSP_ON_OFF&t;&t;0x0024&t;/* Dword offset 0_09 (Mobility Only) */
DECL|macro|TIMER_CONFIG
mdefine_line|#define TIMER_CONFIG&t;&t;0x0028&t;/* Dword offset 0_0A */
DECL|macro|MEM_BUF_CNTL
mdefine_line|#define MEM_BUF_CNTL&t;&t;0x002C&t;/* Dword offset 0_0B */
DECL|macro|MEM_ADDR_CONFIG
mdefine_line|#define MEM_ADDR_CONFIG&t;&t;0x0034&t;/* Dword offset 0_0D */
multiline_comment|/* Accelerator CRTC */
DECL|macro|CRT_TRAP
mdefine_line|#define CRT_TRAP&t;&t;0x0038&t;/* Dword offset 0_0E */
DECL|macro|I2C_CNTL_0
mdefine_line|#define I2C_CNTL_0&t;&t;0x003C&t;/* Dword offset 0_0F */
multiline_comment|/* Overscan */
DECL|macro|OVR_CLR
mdefine_line|#define OVR_CLR&t;&t;&t;0x0040&t;/* Dword offset 0_10 */
DECL|macro|OVR2_CLR
mdefine_line|#define OVR2_CLR&t;&t;0x0040&t;/* Dword offset 0_10 */
DECL|macro|OVR_WID_LEFT_RIGHT
mdefine_line|#define OVR_WID_LEFT_RIGHT&t;0x0044&t;/* Dword offset 0_11 */
DECL|macro|OVR2_WID_LEFT_RIGHT
mdefine_line|#define OVR2_WID_LEFT_RIGHT&t;0x0044&t;/* Dword offset 0_11 */
DECL|macro|OVR_WID_TOP_BOTTOM
mdefine_line|#define OVR_WID_TOP_BOTTOM&t;0x0048&t;/* Dword offset 0_12 */
DECL|macro|OVR2_WID_TOP_BOTTOM
mdefine_line|#define OVR2_WID_TOP_BOTTOM&t;0x0048&t;/* Dword offset 0_12 */
multiline_comment|/* Memory Buffer Control */
DECL|macro|VGA_DSP_CONFIG
mdefine_line|#define VGA_DSP_CONFIG&t;&t;0x004C&t;/* Dword offset 0_13 */
DECL|macro|PM_VGA_DSP_CONFIG
mdefine_line|#define PM_VGA_DSP_CONFIG&t;0x004C&t;/* Dword offset 0_13 (Mobility Only) */
DECL|macro|VGA_DSP_ON_OFF
mdefine_line|#define VGA_DSP_ON_OFF&t;&t;0x0050&t;/* Dword offset 0_14 */
DECL|macro|PM_VGA_DSP_ON_OFF
mdefine_line|#define PM_VGA_DSP_ON_OFF&t;0x0050&t;/* Dword offset 0_14 (Mobility Only) */
DECL|macro|DSP2_CONFIG
mdefine_line|#define DSP2_CONFIG&t;&t;0x0054&t;/* Dword offset 0_15 */
DECL|macro|PM_DSP2_CONFIG
mdefine_line|#define PM_DSP2_CONFIG&t;&t;0x0054&t;/* Dword offset 0_15 (Mobility Only) */
DECL|macro|DSP2_ON_OFF
mdefine_line|#define DSP2_ON_OFF&t;&t;0x0058&t;/* Dword offset 0_16 */
DECL|macro|PM_DSP2_ON_OFF
mdefine_line|#define PM_DSP2_ON_OFF&t;&t;0x0058&t;/* Dword offset 0_16 (Mobility Only) */
multiline_comment|/* Accelerator CRTC */
DECL|macro|CRTC2_OFF_PITCH
mdefine_line|#define CRTC2_OFF_PITCH&t;&t;0x005C&t;/* Dword offset 0_17 */
multiline_comment|/* Hardware Cursor */
DECL|macro|CUR_CLR0
mdefine_line|#define CUR_CLR0&t;&t;0x0060&t;/* Dword offset 0_18 */
DECL|macro|CUR2_CLR0
mdefine_line|#define CUR2_CLR0&t;&t;0x0060&t;/* Dword offset 0_18 */
DECL|macro|CUR_CLR1
mdefine_line|#define CUR_CLR1&t;&t;0x0064&t;/* Dword offset 0_19 */
DECL|macro|CUR2_CLR1
mdefine_line|#define CUR2_CLR1&t;&t;0x0064&t;/* Dword offset 0_19 */
DECL|macro|CUR_OFFSET
mdefine_line|#define CUR_OFFSET&t;&t;0x0068&t;/* Dword offset 0_1A */
DECL|macro|CUR2_OFFSET
mdefine_line|#define CUR2_OFFSET&t;&t;0x0068&t;/* Dword offset 0_1A */
DECL|macro|CUR_HORZ_VERT_POSN
mdefine_line|#define CUR_HORZ_VERT_POSN&t;0x006C&t;/* Dword offset 0_1B */
DECL|macro|CUR2_HORZ_VERT_POSN
mdefine_line|#define CUR2_HORZ_VERT_POSN&t;0x006C&t;/* Dword offset 0_1B */
DECL|macro|CUR_HORZ_VERT_OFF
mdefine_line|#define CUR_HORZ_VERT_OFF&t;0x0070&t;/* Dword offset 0_1C */
DECL|macro|CUR2_HORZ_VERT_OFF
mdefine_line|#define CUR2_HORZ_VERT_OFF&t;0x0070&t;/* Dword offset 0_1C */
DECL|macro|CONFIG_PANEL_LG
mdefine_line|#define CONFIG_PANEL_LG&t;&t;0x0074&t;/* Dword offset 0_1D */
multiline_comment|/* General I/O Control */
DECL|macro|GP_IO
mdefine_line|#define GP_IO&t;&t;&t;0x0078&t;/* Dword offset 0_1E */
multiline_comment|/* Test and Debug */
DECL|macro|HW_DEBUG
mdefine_line|#define HW_DEBUG&t;&t;0x007C&t;/* Dword offset 0_1F */
multiline_comment|/* Scratch Pad and Test */
DECL|macro|SCRATCH_REG0
mdefine_line|#define SCRATCH_REG0&t;&t;0x0080&t;/* Dword offset 0_20 */
DECL|macro|SCRATCH_REG1
mdefine_line|#define SCRATCH_REG1&t;&t;0x0084&t;/* Dword offset 0_21 */
DECL|macro|SCRATCH_REG2
mdefine_line|#define SCRATCH_REG2&t;&t;0x0088&t;/* Dword offset 0_22 */
DECL|macro|SCRATCH_REG3
mdefine_line|#define SCRATCH_REG3&t;&t;0x008C&t;/* Dword offset 0_23 */
multiline_comment|/* Clock Control */
DECL|macro|CLOCK_CNTL
mdefine_line|#define CLOCK_CNTL&t;&t;0x0090&t;/* Dword offset 0_24 */
DECL|macro|CLOCK_SEL_CNTL
mdefine_line|#define CLOCK_SEL_CNTL&t;&t;0x0090&t;/* Dword offset 0_24 */
multiline_comment|/* Configuration */
DECL|macro|CONFIG_STAT1
mdefine_line|#define CONFIG_STAT1&t;&t;0x0094&t;/* Dword offset 0_25 */
DECL|macro|CONFIG_STAT2
mdefine_line|#define CONFIG_STAT2&t;&t;0x0098&t;/* Dword offset 0_26 */
multiline_comment|/* Bus Control */
DECL|macro|BUS_CNTL
mdefine_line|#define BUS_CNTL&t;&t;0x00A0&t;/* Dword offset 0_28 */
DECL|macro|LCD_INDEX
mdefine_line|#define LCD_INDEX&t;&t;0x00A4&t;/* Dword offset 0_29 */
DECL|macro|LCD_DATA
mdefine_line|#define LCD_DATA&t;&t;0x00A8&t;/* Dword offset 0_2A */
multiline_comment|/* Memory Control */
DECL|macro|EXT_MEM_CNTL
mdefine_line|#define EXT_MEM_CNTL&t;&t;0x00AC&t;/* Dword offset 0_2B */
DECL|macro|MEM_CNTL
mdefine_line|#define MEM_CNTL&t;&t;0x00B0&t;/* Dword offset 0_2C */
DECL|macro|MEM_VGA_WP_SEL
mdefine_line|#define MEM_VGA_WP_SEL&t;&t;0x00B4&t;/* Dword offset 0_2D */
DECL|macro|MEM_VGA_RP_SEL
mdefine_line|#define MEM_VGA_RP_SEL&t;&t;0x00B8&t;/* Dword offset 0_2E */
DECL|macro|I2C_CNTL_1
mdefine_line|#define I2C_CNTL_1&t;&t;0x00BC&t;/* Dword offset 0_2F */
multiline_comment|/* DAC Control */
DECL|macro|DAC_REGS
mdefine_line|#define DAC_REGS&t;&t;0x00C0&t;/* Dword offset 0_30 */
DECL|macro|DAC_W_INDEX
mdefine_line|#define DAC_W_INDEX&t;&t;0x00C0&t;/* Dword offset 0_30 */
DECL|macro|DAC_DATA
mdefine_line|#define DAC_DATA&t;&t;0x00C1&t;/* Dword offset 0_30 */
DECL|macro|DAC_MASK
mdefine_line|#define DAC_MASK&t;&t;0x00C2&t;/* Dword offset 0_30 */
DECL|macro|DAC_R_INDEX
mdefine_line|#define DAC_R_INDEX&t;&t;0x00C3&t;/* Dword offset 0_30 */
DECL|macro|DAC_CNTL
mdefine_line|#define DAC_CNTL&t;&t;0x00C4&t;/* Dword offset 0_31 */
DECL|macro|EXT_DAC_REGS
mdefine_line|#define EXT_DAC_REGS&t;&t;0x00C8&t;/* Dword offset 0_32 */
multiline_comment|/* Test and Debug */
DECL|macro|GEN_TEST_CNTL
mdefine_line|#define GEN_TEST_CNTL&t;&t;0x00D0&t;/* Dword offset 0_34 */
multiline_comment|/* Custom Macros */
DECL|macro|CUSTOM_MACRO_CNTL
mdefine_line|#define CUSTOM_MACRO_CNTL&t;0x00D4&t;/* Dword offset 0_35 */
DECL|macro|LCD_GEN_CNTL_LG
mdefine_line|#define LCD_GEN_CNTL_LG&t;&t;0x00D4&t;/* Dword offset 0_35 */
DECL|macro|POWER_MANAGEMENT_LG
mdefine_line|#define POWER_MANAGEMENT_LG&t;0x00D8&t;/* Dword offset 0_36 (LG) */
multiline_comment|/* Configuration */
DECL|macro|CONFIG_CNTL
mdefine_line|#define CONFIG_CNTL&t;&t;0x00DC&t;/* Dword offset 0_37 (CT, ET, VT) */
DECL|macro|CONFIG_CHIP_ID
mdefine_line|#define CONFIG_CHIP_ID&t;&t;0x00E0&t;/* Dword offset 0_38 */
DECL|macro|CONFIG_STAT0
mdefine_line|#define CONFIG_STAT0&t;&t;0x00E4&t;/* Dword offset 0_39 */
multiline_comment|/* Test and Debug */
DECL|macro|CRC_SIG
mdefine_line|#define CRC_SIG&t;&t;&t;0x00E8&t;/* Dword offset 0_3A */
DECL|macro|CRC2_SIG
mdefine_line|#define CRC2_SIG&t;&t;0x00E8&t;/* Dword offset 0_3A */
multiline_comment|/* GUI MEMORY MAPPED Registers */
multiline_comment|/* Draw Engine Destination Trajectory */
DECL|macro|DST_OFF_PITCH
mdefine_line|#define DST_OFF_PITCH&t;&t;0x0100&t;/* Dword offset 0_40 */
DECL|macro|DST_X
mdefine_line|#define DST_X&t;&t;&t;0x0104&t;/* Dword offset 0_41 */
DECL|macro|DST_Y
mdefine_line|#define DST_Y&t;&t;&t;0x0108&t;/* Dword offset 0_42 */
DECL|macro|DST_Y_X
mdefine_line|#define DST_Y_X&t;&t;&t;0x010C&t;/* Dword offset 0_43 */
DECL|macro|DST_WIDTH
mdefine_line|#define DST_WIDTH&t;&t;0x0110&t;/* Dword offset 0_44 */
DECL|macro|DST_HEIGHT
mdefine_line|#define DST_HEIGHT&t;&t;0x0114&t;/* Dword offset 0_45 */
DECL|macro|DST_HEIGHT_WIDTH
mdefine_line|#define DST_HEIGHT_WIDTH&t;0x0118&t;/* Dword offset 0_46 */
DECL|macro|DST_X_WIDTH
mdefine_line|#define DST_X_WIDTH&t;&t;0x011C&t;/* Dword offset 0_47 */
DECL|macro|DST_BRES_LNTH
mdefine_line|#define DST_BRES_LNTH&t;&t;0x0120&t;/* Dword offset 0_48 */
DECL|macro|DST_BRES_ERR
mdefine_line|#define DST_BRES_ERR&t;&t;0x0124&t;/* Dword offset 0_49 */
DECL|macro|DST_BRES_INC
mdefine_line|#define DST_BRES_INC&t;&t;0x0128&t;/* Dword offset 0_4A */
DECL|macro|DST_BRES_DEC
mdefine_line|#define DST_BRES_DEC&t;&t;0x012C&t;/* Dword offset 0_4B */
DECL|macro|DST_CNTL
mdefine_line|#define DST_CNTL&t;&t;0x0130&t;/* Dword offset 0_4C */
DECL|macro|DST_Y_X__ALIAS__
mdefine_line|#define DST_Y_X__ALIAS__&t;0x0134&t;/* Dword offset 0_4D */
DECL|macro|TRAIL_BRES_ERR
mdefine_line|#define TRAIL_BRES_ERR&t;&t;0x0138&t;/* Dword offset 0_4E */
DECL|macro|TRAIL_BRES_INC
mdefine_line|#define TRAIL_BRES_INC&t;&t;0x013C&t;/* Dword offset 0_4F */
DECL|macro|TRAIL_BRES_DEC
mdefine_line|#define TRAIL_BRES_DEC&t;&t;0x0140&t;/* Dword offset 0_50 */
DECL|macro|LEAD_BRES_LNTH
mdefine_line|#define LEAD_BRES_LNTH&t;&t;0x0144&t;/* Dword offset 0_51 */
DECL|macro|Z_OFF_PITCH
mdefine_line|#define Z_OFF_PITCH&t;&t;0x0148&t;/* Dword offset 0_52 */
DECL|macro|Z_CNTL
mdefine_line|#define Z_CNTL&t;&t;&t;0x014C&t;/* Dword offset 0_53 */
DECL|macro|ALPHA_TST_CNTL
mdefine_line|#define ALPHA_TST_CNTL&t;&t;0x0150&t;/* Dword offset 0_54 */
DECL|macro|SECONDARY_STW_EXP
mdefine_line|#define SECONDARY_STW_EXP&t;0x0158&t;/* Dword offset 0_56 */
DECL|macro|SECONDARY_S_X_INC
mdefine_line|#define SECONDARY_S_X_INC&t;0x015C&t;/* Dword offset 0_57 */
DECL|macro|SECONDARY_S_Y_INC
mdefine_line|#define SECONDARY_S_Y_INC&t;0x0160&t;/* Dword offset 0_58 */
DECL|macro|SECONDARY_S_START
mdefine_line|#define SECONDARY_S_START&t;0x0164&t;/* Dword offset 0_59 */
DECL|macro|SECONDARY_W_X_INC
mdefine_line|#define SECONDARY_W_X_INC&t;0x0168&t;/* Dword offset 0_5A */
DECL|macro|SECONDARY_W_Y_INC
mdefine_line|#define SECONDARY_W_Y_INC&t;0x016C&t;/* Dword offset 0_5B */
DECL|macro|SECONDARY_W_START
mdefine_line|#define SECONDARY_W_START&t;0x0170&t;/* Dword offset 0_5C */
DECL|macro|SECONDARY_T_X_INC
mdefine_line|#define SECONDARY_T_X_INC&t;0x0174&t;/* Dword offset 0_5D */
DECL|macro|SECONDARY_T_Y_INC
mdefine_line|#define SECONDARY_T_Y_INC&t;0x0178&t;/* Dword offset 0_5E */
DECL|macro|SECONDARY_T_START
mdefine_line|#define SECONDARY_T_START&t;0x017C&t;/* Dword offset 0_5F */
multiline_comment|/* Draw Engine Source Trajectory */
DECL|macro|SRC_OFF_PITCH
mdefine_line|#define SRC_OFF_PITCH&t;&t;0x0180&t;/* Dword offset 0_60 */
DECL|macro|SRC_X
mdefine_line|#define SRC_X&t;&t;&t;0x0184&t;/* Dword offset 0_61 */
DECL|macro|SRC_Y
mdefine_line|#define SRC_Y&t;&t;&t;0x0188&t;/* Dword offset 0_62 */
DECL|macro|SRC_Y_X
mdefine_line|#define SRC_Y_X&t;&t;&t;0x018C&t;/* Dword offset 0_63 */
DECL|macro|SRC_WIDTH1
mdefine_line|#define SRC_WIDTH1&t;&t;0x0190&t;/* Dword offset 0_64 */
DECL|macro|SRC_HEIGHT1
mdefine_line|#define SRC_HEIGHT1&t;&t;0x0194&t;/* Dword offset 0_65 */
DECL|macro|SRC_HEIGHT1_WIDTH1
mdefine_line|#define SRC_HEIGHT1_WIDTH1&t;0x0198&t;/* Dword offset 0_66 */
DECL|macro|SRC_X_START
mdefine_line|#define SRC_X_START&t;&t;0x019C&t;/* Dword offset 0_67 */
DECL|macro|SRC_Y_START
mdefine_line|#define SRC_Y_START&t;&t;0x01A0&t;/* Dword offset 0_68 */
DECL|macro|SRC_Y_X_START
mdefine_line|#define SRC_Y_X_START&t;&t;0x01A4&t;/* Dword offset 0_69 */
DECL|macro|SRC_WIDTH2
mdefine_line|#define SRC_WIDTH2&t;&t;0x01A8&t;/* Dword offset 0_6A */
DECL|macro|SRC_HEIGHT2
mdefine_line|#define SRC_HEIGHT2&t;&t;0x01AC&t;/* Dword offset 0_6B */
DECL|macro|SRC_HEIGHT2_WIDTH2
mdefine_line|#define SRC_HEIGHT2_WIDTH2&t;0x01B0&t;/* Dword offset 0_6C */
DECL|macro|SRC_CNTL
mdefine_line|#define SRC_CNTL&t;&t;0x01B4&t;/* Dword offset 0_6D */
DECL|macro|SCALE_OFF
mdefine_line|#define SCALE_OFF&t;&t;0x01C0&t;/* Dword offset 0_70 */
DECL|macro|SECONDARY_SCALE_OFF
mdefine_line|#define SECONDARY_SCALE_OFF&t;0x01C4&t;/* Dword offset 0_71 */
DECL|macro|TEX_0_OFF
mdefine_line|#define TEX_0_OFF&t;&t;0x01C0&t;/* Dword offset 0_70 */
DECL|macro|TEX_1_OFF
mdefine_line|#define TEX_1_OFF&t;&t;0x01C4&t;/* Dword offset 0_71 */
DECL|macro|TEX_2_OFF
mdefine_line|#define TEX_2_OFF&t;&t;0x01C8&t;/* Dword offset 0_72 */
DECL|macro|TEX_3_OFF
mdefine_line|#define TEX_3_OFF&t;&t;0x01CC&t;/* Dword offset 0_73 */
DECL|macro|TEX_4_OFF
mdefine_line|#define TEX_4_OFF&t;&t;0x01D0&t;/* Dword offset 0_74 */
DECL|macro|TEX_5_OFF
mdefine_line|#define TEX_5_OFF&t;&t;0x01D4&t;/* Dword offset 0_75 */
DECL|macro|TEX_6_OFF
mdefine_line|#define TEX_6_OFF&t;&t;0x01D8&t;/* Dword offset 0_76 */
DECL|macro|TEX_7_OFF
mdefine_line|#define TEX_7_OFF&t;&t;0x01DC&t;/* Dword offset 0_77 */
DECL|macro|SCALE_WIDTH
mdefine_line|#define SCALE_WIDTH&t;&t;0x01DC&t;/* Dword offset 0_77 */
DECL|macro|SCALE_HEIGHT
mdefine_line|#define SCALE_HEIGHT&t;&t;0x01E0&t;/* Dword offset 0_78 */
DECL|macro|TEX_8_OFF
mdefine_line|#define TEX_8_OFF&t;&t;0x01E0&t;/* Dword offset 0_78 */
DECL|macro|TEX_9_OFF
mdefine_line|#define TEX_9_OFF&t;&t;0x01E4&t;/* Dword offset 0_79 */
DECL|macro|TEX_10_OFF
mdefine_line|#define TEX_10_OFF&t;&t;0x01E8&t;/* Dword offset 0_7A */
DECL|macro|S_Y_INC
mdefine_line|#define S_Y_INC&t;&t;&t;0x01EC&t;/* Dword offset 0_7B */
DECL|macro|SCALE_PITCH
mdefine_line|#define SCALE_PITCH&t;&t;0x01EC&t;/* Dword offset 0_7B */
DECL|macro|SCALE_X_INC
mdefine_line|#define SCALE_X_INC&t;&t;0x01F0&t;/* Dword offset 0_7C */
DECL|macro|RED_X_INC
mdefine_line|#define RED_X_INC&t;&t;0x01F0&t;/* Dword offset 0_7C */
DECL|macro|GREEN_X_INC
mdefine_line|#define GREEN_X_INC&t;&t;0x01F4&t;/* Dword offset 0_7D */
DECL|macro|SCALE_Y_INC
mdefine_line|#define SCALE_Y_INC&t;&t;0x01F4&t;/* Dword offset 0_7D */
DECL|macro|SCALE_VACC
mdefine_line|#define SCALE_VACC&t;&t;0x01F8&t;/* Dword offset 0_7E */
DECL|macro|SCALE_3D_CNTL
mdefine_line|#define SCALE_3D_CNTL&t;&t;0x01FC&t;/* Dword offset 0_7F */
multiline_comment|/* Host Data */
DECL|macro|HOST_DATA0
mdefine_line|#define HOST_DATA0&t;&t;0x0200&t;/* Dword offset 0_80 */
DECL|macro|HOST_DATA1
mdefine_line|#define HOST_DATA1&t;&t;0x0204&t;/* Dword offset 0_81 */
DECL|macro|HOST_DATA2
mdefine_line|#define HOST_DATA2&t;&t;0x0208&t;/* Dword offset 0_82 */
DECL|macro|HOST_DATA3
mdefine_line|#define HOST_DATA3&t;&t;0x020C&t;/* Dword offset 0_83 */
DECL|macro|HOST_DATA4
mdefine_line|#define HOST_DATA4&t;&t;0x0210&t;/* Dword offset 0_84 */
DECL|macro|HOST_DATA5
mdefine_line|#define HOST_DATA5&t;&t;0x0214&t;/* Dword offset 0_85 */
DECL|macro|HOST_DATA6
mdefine_line|#define HOST_DATA6&t;&t;0x0218&t;/* Dword offset 0_86 */
DECL|macro|HOST_DATA7
mdefine_line|#define HOST_DATA7&t;&t;0x021C&t;/* Dword offset 0_87 */
DECL|macro|HOST_DATA8
mdefine_line|#define HOST_DATA8&t;&t;0x0220&t;/* Dword offset 0_88 */
DECL|macro|HOST_DATA9
mdefine_line|#define HOST_DATA9&t;&t;0x0224&t;/* Dword offset 0_89 */
DECL|macro|HOST_DATAA
mdefine_line|#define HOST_DATAA&t;&t;0x0228&t;/* Dword offset 0_8A */
DECL|macro|HOST_DATAB
mdefine_line|#define HOST_DATAB&t;&t;0x022C&t;/* Dword offset 0_8B */
DECL|macro|HOST_DATAC
mdefine_line|#define HOST_DATAC&t;&t;0x0230&t;/* Dword offset 0_8C */
DECL|macro|HOST_DATAD
mdefine_line|#define HOST_DATAD&t;&t;0x0234&t;/* Dword offset 0_8D */
DECL|macro|HOST_DATAE
mdefine_line|#define HOST_DATAE&t;&t;0x0238&t;/* Dword offset 0_8E */
DECL|macro|HOST_DATAF
mdefine_line|#define HOST_DATAF&t;&t;0x023C&t;/* Dword offset 0_8F */
DECL|macro|HOST_CNTL
mdefine_line|#define HOST_CNTL&t;&t;0x0240&t;/* Dword offset 0_90 */
multiline_comment|/* GUI Bus Mastering */
DECL|macro|BM_HOSTDATA
mdefine_line|#define BM_HOSTDATA&t;&t;0x0244&t;/* Dword offset 0_91 */
DECL|macro|BM_ADDR
mdefine_line|#define BM_ADDR&t;&t;&t;0x0248&t;/* Dword offset 0_92 */
DECL|macro|BM_DATA
mdefine_line|#define BM_DATA&t;&t;&t;0x0248&t;/* Dword offset 0_92 */
DECL|macro|BM_GUI_TABLE_CMD
mdefine_line|#define BM_GUI_TABLE_CMD&t;0x024C&t;/* Dword offset 0_93 */
multiline_comment|/* Pattern */
DECL|macro|PAT_REG0
mdefine_line|#define PAT_REG0&t;&t;0x0280&t;/* Dword offset 0_A0 */
DECL|macro|PAT_REG1
mdefine_line|#define PAT_REG1&t;&t;0x0284&t;/* Dword offset 0_A1 */
DECL|macro|PAT_CNTL
mdefine_line|#define PAT_CNTL&t;&t;0x0288&t;/* Dword offset 0_A2 */
multiline_comment|/* Scissors */
DECL|macro|SC_LEFT
mdefine_line|#define SC_LEFT&t;&t;&t;0x02A0&t;/* Dword offset 0_A8 */
DECL|macro|SC_RIGHT
mdefine_line|#define SC_RIGHT&t;&t;0x02A4&t;/* Dword offset 0_A9 */
DECL|macro|SC_LEFT_RIGHT
mdefine_line|#define SC_LEFT_RIGHT&t;&t;0x02A8&t;/* Dword offset 0_AA */
DECL|macro|SC_TOP
mdefine_line|#define SC_TOP&t;&t;&t;0x02AC&t;/* Dword offset 0_AB */
DECL|macro|SC_BOTTOM
mdefine_line|#define SC_BOTTOM&t;&t;0x02B0&t;/* Dword offset 0_AC */
DECL|macro|SC_TOP_BOTTOM
mdefine_line|#define SC_TOP_BOTTOM&t;&t;0x02B4&t;/* Dword offset 0_AD */
multiline_comment|/* Data Path */
DECL|macro|USR1_DST_OFF_PITCH
mdefine_line|#define USR1_DST_OFF_PITCH&t;0x02B8&t;/* Dword offset 0_AE */
DECL|macro|USR2_DST_OFF_PITCH
mdefine_line|#define USR2_DST_OFF_PITCH&t;0x02BC&t;/* Dword offset 0_AF */
DECL|macro|DP_BKGD_CLR
mdefine_line|#define DP_BKGD_CLR&t;&t;0x02C0&t;/* Dword offset 0_B0 */
DECL|macro|DP_FOG_CLR
mdefine_line|#define DP_FOG_CLR&t;&t;0x02C4&t;/* Dword offset 0_B1 */
DECL|macro|DP_FRGD_CLR
mdefine_line|#define DP_FRGD_CLR&t;&t;0x02C4&t;/* Dword offset 0_B1 */
DECL|macro|DP_WRITE_MASK
mdefine_line|#define DP_WRITE_MASK&t;&t;0x02C8&t;/* Dword offset 0_B2 */
DECL|macro|DP_CHAIN_MASK
mdefine_line|#define DP_CHAIN_MASK&t;&t;0x02CC&t;/* Dword offset 0_B3 */
DECL|macro|DP_PIX_WIDTH
mdefine_line|#define DP_PIX_WIDTH&t;&t;0x02D0&t;/* Dword offset 0_B4 */
DECL|macro|DP_MIX
mdefine_line|#define DP_MIX&t;&t;&t;0x02D4&t;/* Dword offset 0_B5 */
DECL|macro|DP_SRC
mdefine_line|#define DP_SRC&t;&t;&t;0x02D8&t;/* Dword offset 0_B6 */
DECL|macro|DP_FRGD_CLR_MIX
mdefine_line|#define DP_FRGD_CLR_MIX&t;&t;0x02DC&t;/* Dword offset 0_B7 */
DECL|macro|DP_FRGD_BKGD_CLR
mdefine_line|#define DP_FRGD_BKGD_CLR&t;0x02E0&t;/* Dword offset 0_B8 */
multiline_comment|/* Draw Engine Destination Trajectory */
DECL|macro|DST_X_Y
mdefine_line|#define DST_X_Y&t;&t;&t;0x02E8&t;/* Dword offset 0_BA */
DECL|macro|DST_WIDTH_HEIGHT
mdefine_line|#define DST_WIDTH_HEIGHT&t;0x02EC&t;/* Dword offset 0_BB */
multiline_comment|/* Data Path */
DECL|macro|USR_DST_PICTH
mdefine_line|#define USR_DST_PICTH&t;&t;0x02F0&t;/* Dword offset 0_BC */
DECL|macro|DP_SET_GUI_ENGINE2
mdefine_line|#define DP_SET_GUI_ENGINE2&t;0x02F8&t;/* Dword offset 0_BE */
DECL|macro|DP_SET_GUI_ENGINE
mdefine_line|#define DP_SET_GUI_ENGINE&t;0x02FC&t;/* Dword offset 0_BF */
multiline_comment|/* Color Compare */
DECL|macro|CLR_CMP_CLR
mdefine_line|#define CLR_CMP_CLR&t;&t;0x0300&t;/* Dword offset 0_C0 */
DECL|macro|CLR_CMP_MASK
mdefine_line|#define CLR_CMP_MASK&t;&t;0x0304&t;/* Dword offset 0_C1 */
DECL|macro|CLR_CMP_CNTL
mdefine_line|#define CLR_CMP_CNTL&t;&t;0x0308&t;/* Dword offset 0_C2 */
multiline_comment|/* Command FIFO */
DECL|macro|FIFO_STAT
mdefine_line|#define FIFO_STAT&t;&t;0x0310&t;/* Dword offset 0_C4 */
DECL|macro|CONTEXT_MASK
mdefine_line|#define CONTEXT_MASK&t;&t;0x0320&t;/* Dword offset 0_C8 */
DECL|macro|CONTEXT_LOAD_CNTL
mdefine_line|#define CONTEXT_LOAD_CNTL&t;0x032C&t;/* Dword offset 0_CB */
multiline_comment|/* Engine Control */
DECL|macro|GUI_TRAJ_CNTL
mdefine_line|#define GUI_TRAJ_CNTL&t;&t;0x0330&t;/* Dword offset 0_CC */
multiline_comment|/* Engine Status/FIFO */
DECL|macro|GUI_STAT
mdefine_line|#define GUI_STAT&t;&t;0x0338&t;/* Dword offset 0_CE */
DECL|macro|TEX_PALETTE_INDEX
mdefine_line|#define TEX_PALETTE_INDEX&t;0x0340&t;/* Dword offset 0_D0 */
DECL|macro|STW_EXP
mdefine_line|#define STW_EXP&t;&t;&t;0x0344&t;/* Dword offset 0_D1 */
DECL|macro|LOG_MAX_INC
mdefine_line|#define LOG_MAX_INC&t;&t;0x0348&t;/* Dword offset 0_D2 */
DECL|macro|S_X_INC
mdefine_line|#define S_X_INC&t;&t;&t;0x034C&t;/* Dword offset 0_D3 */
DECL|macro|S_Y_INC__ALIAS__
mdefine_line|#define S_Y_INC__ALIAS__&t;0x0350&t;/* Dword offset 0_D4 */
DECL|macro|SCALE_PITCH__ALIAS__
mdefine_line|#define SCALE_PITCH__ALIAS__&t;0x0350&t;/* Dword offset 0_D4 */
DECL|macro|S_START
mdefine_line|#define S_START&t;&t;&t;0x0354&t;/* Dword offset 0_D5 */
DECL|macro|W_X_INC
mdefine_line|#define W_X_INC&t;&t;&t;0x0358&t;/* Dword offset 0_D6 */
DECL|macro|W_Y_INC
mdefine_line|#define W_Y_INC&t;&t;&t;0x035C&t;/* Dword offset 0_D7 */
DECL|macro|W_START
mdefine_line|#define W_START&t;&t;&t;0x0360&t;/* Dword offset 0_D8 */
DECL|macro|T_X_INC
mdefine_line|#define T_X_INC&t;&t;&t;0x0364&t;/* Dword offset 0_D9 */
DECL|macro|T_Y_INC
mdefine_line|#define T_Y_INC&t;&t;&t;0x0368&t;/* Dword offset 0_DA */
DECL|macro|SECONDARY_SCALE_PITCH
mdefine_line|#define SECONDARY_SCALE_PITCH&t;0x0368&t;/* Dword offset 0_DA */
DECL|macro|T_START
mdefine_line|#define T_START&t;&t;&t;0x036C&t;/* Dword offset 0_DB */
DECL|macro|TEX_SIZE_PITCH
mdefine_line|#define TEX_SIZE_PITCH&t;&t;0x0370&t;/* Dword offset 0_DC */
DECL|macro|TEX_CNTL
mdefine_line|#define TEX_CNTL&t;&t;0x0374&t;/* Dword offset 0_DD */
DECL|macro|SECONDARY_TEX_OFFSET
mdefine_line|#define SECONDARY_TEX_OFFSET&t;0x0378&t;/* Dword offset 0_DE */
DECL|macro|TEX_PALETTE
mdefine_line|#define TEX_PALETTE&t;&t;0x037C&t;/* Dword offset 0_DF */
DECL|macro|SCALE_PITCH_BOTH
mdefine_line|#define SCALE_PITCH_BOTH&t;0x0380&t;/* Dword offset 0_E0 */
DECL|macro|SECONDARY_SCALE_OFF_ACC
mdefine_line|#define SECONDARY_SCALE_OFF_ACC&t;0x0384&t;/* Dword offset 0_E1 */
DECL|macro|SCALE_OFF_ACC
mdefine_line|#define SCALE_OFF_ACC&t;&t;0x0388&t;/* Dword offset 0_E2 */
DECL|macro|SCALE_DST_Y_X
mdefine_line|#define SCALE_DST_Y_X&t;&t;0x038C&t;/* Dword offset 0_E3 */
multiline_comment|/* Draw Engine Destination Trajectory */
DECL|macro|COMPOSITE_SHADOW_ID
mdefine_line|#define COMPOSITE_SHADOW_ID&t;0x0398&t;/* Dword offset 0_E6 */
DECL|macro|SECONDARY_SCALE_X_INC
mdefine_line|#define SECONDARY_SCALE_X_INC&t;0x039C&t;/* Dword offset 0_E7 */
DECL|macro|SPECULAR_RED_X_INC
mdefine_line|#define SPECULAR_RED_X_INC&t;0x039C&t;/* Dword offset 0_E7 */
DECL|macro|SPECULAR_RED_Y_INC
mdefine_line|#define SPECULAR_RED_Y_INC&t;0x03A0&t;/* Dword offset 0_E8 */
DECL|macro|SPECULAR_RED_START
mdefine_line|#define SPECULAR_RED_START&t;0x03A4&t;/* Dword offset 0_E9 */
DECL|macro|SECONDARY_SCALE_HACC
mdefine_line|#define SECONDARY_SCALE_HACC&t;0x03A4&t;/* Dword offset 0_E9 */
DECL|macro|SPECULAR_GREEN_X_INC
mdefine_line|#define SPECULAR_GREEN_X_INC&t;0x03A8&t;/* Dword offset 0_EA */
DECL|macro|SPECULAR_GREEN_Y_INC
mdefine_line|#define SPECULAR_GREEN_Y_INC&t;0x03AC&t;/* Dword offset 0_EB */
DECL|macro|SPECULAR_GREEN_START
mdefine_line|#define SPECULAR_GREEN_START&t;0x03B0&t;/* Dword offset 0_EC */
DECL|macro|SPECULAR_BLUE_X_INC
mdefine_line|#define SPECULAR_BLUE_X_INC&t;0x03B4&t;/* Dword offset 0_ED */
DECL|macro|SPECULAR_BLUE_Y_INC
mdefine_line|#define SPECULAR_BLUE_Y_INC&t;0x03B8&t;/* Dword offset 0_EE */
DECL|macro|SPECULAR_BLUE_START
mdefine_line|#define SPECULAR_BLUE_START&t;0x03BC&t;/* Dword offset 0_EF */
DECL|macro|SCALE_X_INC__ALIAS__
mdefine_line|#define SCALE_X_INC__ALIAS__&t;0x03C0&t;/* Dword offset 0_F0 */
DECL|macro|RED_X_INC__ALIAS__
mdefine_line|#define RED_X_INC__ALIAS__&t;0x03C0&t;/* Dword offset 0_F0 */
DECL|macro|RED_Y_INC
mdefine_line|#define RED_Y_INC&t;&t;0x03C4&t;/* Dword offset 0_F1 */
DECL|macro|RED_START
mdefine_line|#define RED_START&t;&t;0x03C8&t;/* Dword offset 0_F2 */
DECL|macro|SCALE_HACC
mdefine_line|#define SCALE_HACC&t;&t;0x03C8&t;/* Dword offset 0_F2 */
DECL|macro|SCALE_Y_INC__ALIAS__
mdefine_line|#define SCALE_Y_INC__ALIAS__&t;0x03CC&t;/* Dword offset 0_F3 */
DECL|macro|GREEN_X_INC__ALIAS__
mdefine_line|#define GREEN_X_INC__ALIAS__&t;0x03CC&t;/* Dword offset 0_F3 */
DECL|macro|GREEN_Y_INC
mdefine_line|#define GREEN_Y_INC&t;&t;0x03D0&t;/* Dword offset 0_F4 */
DECL|macro|SECONDARY_SCALE_Y_INC
mdefine_line|#define SECONDARY_SCALE_Y_INC&t;0x03D0&t;/* Dword offset 0_F4 */
DECL|macro|SECONDARY_SCALE_VACC
mdefine_line|#define SECONDARY_SCALE_VACC&t;0x03D4&t;/* Dword offset 0_F5 */
DECL|macro|GREEN_START
mdefine_line|#define GREEN_START&t;&t;0x03D4&t;/* Dword offset 0_F5 */
DECL|macro|BLUE_X_INC
mdefine_line|#define BLUE_X_INC&t;&t;0x03D8&t;/* Dword offset 0_F6 */
DECL|macro|BLUE_Y_INC
mdefine_line|#define BLUE_Y_INC&t;&t;0x03DC&t;/* Dword offset 0_F7 */
DECL|macro|BLUE_START
mdefine_line|#define BLUE_START&t;&t;0x03E0&t;/* Dword offset 0_F8 */
DECL|macro|Z_X_INC
mdefine_line|#define Z_X_INC&t;&t;&t;0x03E4&t;/* Dword offset 0_F9 */
DECL|macro|Z_Y_INC
mdefine_line|#define Z_Y_INC&t;&t;&t;0x03E8&t;/* Dword offset 0_FA */
DECL|macro|Z_START
mdefine_line|#define Z_START&t;&t;&t;0x03EC&t;/* Dword offset 0_FB */
DECL|macro|ALPHA_X_INC
mdefine_line|#define ALPHA_X_INC&t;&t;0x03F0&t;/* Dword offset 0_FC */
DECL|macro|FOG_X_INC
mdefine_line|#define FOG_X_INC&t;&t;0x03F0&t;/* Dword offset 0_FC */
DECL|macro|ALPHA_Y_INC
mdefine_line|#define ALPHA_Y_INC&t;&t;0x03F4&t;/* Dword offset 0_FD */
DECL|macro|FOG_Y_INC
mdefine_line|#define FOG_Y_INC&t;&t;0x03F4&t;/* Dword offset 0_FD */
DECL|macro|ALPHA_START
mdefine_line|#define ALPHA_START&t;&t;0x03F8&t;/* Dword offset 0_FE */
DECL|macro|FOG_START
mdefine_line|#define FOG_START&t;&t;0x03F8&t;/* Dword offset 0_FE */
DECL|macro|OVERLAY_Y_X_START
mdefine_line|#define OVERLAY_Y_X_START&t;&t;0x0400&t;/* Dword offset 1_00 */
DECL|macro|OVERLAY_Y_X_END
mdefine_line|#define OVERLAY_Y_X_END&t;&t;&t;0x0404&t;/* Dword offset 1_01 */
DECL|macro|OVERLAY_VIDEO_KEY_CLR
mdefine_line|#define OVERLAY_VIDEO_KEY_CLR&t;&t;0x0408&t;/* Dword offset 1_02 */
DECL|macro|OVERLAY_VIDEO_KEY_MSK
mdefine_line|#define OVERLAY_VIDEO_KEY_MSK&t;&t;0x040C&t;/* Dword offset 1_03 */
DECL|macro|OVERLAY_GRAPHICS_KEY_CLR
mdefine_line|#define OVERLAY_GRAPHICS_KEY_CLR&t;0x0410&t;/* Dword offset 1_04 */
DECL|macro|OVERLAY_GRAPHICS_KEY_MSK
mdefine_line|#define OVERLAY_GRAPHICS_KEY_MSK&t;0x0414&t;/* Dword offset 1_05 */
DECL|macro|OVERLAY_KEY_CNTL
mdefine_line|#define OVERLAY_KEY_CNTL&t;&t;0x0418&t;/* Dword offset 1_06 */
DECL|macro|OVERLAY_SCALE_INC
mdefine_line|#define OVERLAY_SCALE_INC&t;0x0420&t;/* Dword offset 1_08 */
DECL|macro|OVERLAY_SCALE_CNTL
mdefine_line|#define OVERLAY_SCALE_CNTL&t;0x0424&t;/* Dword offset 1_09 */
DECL|macro|SCALER_HEIGHT_WIDTH
mdefine_line|#define SCALER_HEIGHT_WIDTH&t;0x0428&t;/* Dword offset 1_0A */
DECL|macro|SCALER_TEST
mdefine_line|#define SCALER_TEST&t;&t;0x042C&t;/* Dword offset 1_0B */
DECL|macro|SCALER_BUF0_OFFSET
mdefine_line|#define SCALER_BUF0_OFFSET&t;0x0434&t;/* Dword offset 1_0D */
DECL|macro|SCALER_BUF1_OFFSET
mdefine_line|#define SCALER_BUF1_OFFSET&t;0x0438&t;/* Dword offset 1_0E */
DECL|macro|SCALE_BUF_PITCH
mdefine_line|#define SCALE_BUF_PITCH&t;&t;0x043C&t;/* Dword offset 1_0F */
DECL|macro|CAPTURE_START_END
mdefine_line|#define CAPTURE_START_END&t;0x0440&t;/* Dword offset 1_10 */
DECL|macro|CAPTURE_X_WIDTH
mdefine_line|#define CAPTURE_X_WIDTH&t;&t;0x0444&t;/* Dword offset 1_11 */
DECL|macro|VIDEO_FORMAT
mdefine_line|#define VIDEO_FORMAT&t;&t;0x0448&t;/* Dword offset 1_12 */
DECL|macro|VBI_START_END
mdefine_line|#define VBI_START_END&t;&t;0x044C&t;/* Dword offset 1_13 */
DECL|macro|CAPTURE_CONFIG
mdefine_line|#define CAPTURE_CONFIG&t;&t;0x0450&t;/* Dword offset 1_14 */
DECL|macro|TRIG_CNTL
mdefine_line|#define TRIG_CNTL&t;&t;0x0454&t;/* Dword offset 1_15 */
DECL|macro|OVERLAY_EXCLUSIVE_HORZ
mdefine_line|#define OVERLAY_EXCLUSIVE_HORZ&t;0x0458&t;/* Dword offset 1_16 */
DECL|macro|OVERLAY_EXCLUSIVE_VERT
mdefine_line|#define OVERLAY_EXCLUSIVE_VERT&t;0x045C&t;/* Dword offset 1_17 */
DECL|macro|VAL_WIDTH
mdefine_line|#define VAL_WIDTH&t;&t;0x0460&t;/* Dword offset 1_18 */
DECL|macro|CAPTURE_DEBUG
mdefine_line|#define CAPTURE_DEBUG&t;&t;0x0464&t;/* Dword offset 1_19 */
DECL|macro|VIDEO_SYNC_TEST
mdefine_line|#define VIDEO_SYNC_TEST&t;&t;0x0468&t;/* Dword offset 1_1A */
multiline_comment|/* GenLocking */
DECL|macro|SNAPSHOT_VH_COUNTS
mdefine_line|#define SNAPSHOT_VH_COUNTS&t;0x0470&t;/* Dword offset 1_1C */
DECL|macro|SNAPSHOT_F_COUNT
mdefine_line|#define SNAPSHOT_F_COUNT&t;0x0474&t;/* Dword offset 1_1D */
DECL|macro|N_VIF_COUNT
mdefine_line|#define N_VIF_COUNT&t;&t;0x0478&t;/* Dword offset 1_1E */
DECL|macro|SNAPSHOT_VIF_COUNT
mdefine_line|#define SNAPSHOT_VIF_COUNT&t;0x047C&t;/* Dword offset 1_1F */
DECL|macro|CAPTURE_BUF0_OFFSET
mdefine_line|#define CAPTURE_BUF0_OFFSET&t;0x0480&t;/* Dword offset 1_20 */
DECL|macro|CAPTURE_BUF1_OFFSET
mdefine_line|#define CAPTURE_BUF1_OFFSET&t;0x0484&t;/* Dword offset 1_21 */
DECL|macro|CAPTURE_BUF_PITCH
mdefine_line|#define CAPTURE_BUF_PITCH&t;0x0488&t;/* Dword offset 1_22 */
multiline_comment|/* GenLocking */
DECL|macro|SNAPSHOT2_VH_COUNTS
mdefine_line|#define SNAPSHOT2_VH_COUNTS&t;0x04B0&t;/* Dword offset 1_2C */
DECL|macro|SNAPSHOT2_F_COUNT
mdefine_line|#define SNAPSHOT2_F_COUNT&t;0x04B4&t;/* Dword offset 1_2D */
DECL|macro|N_VIF2_COUNT
mdefine_line|#define N_VIF2_COUNT&t;&t;0x04B8&t;/* Dword offset 1_2E */
DECL|macro|SNAPSHOT2_VIF_COUNT
mdefine_line|#define SNAPSHOT2_VIF_COUNT&t;0x04BC&t;/* Dword offset 1_2F */
DECL|macro|MPP_CONFIG
mdefine_line|#define MPP_CONFIG&t;&t;0x04C0&t;/* Dword offset 1_30 */
DECL|macro|MPP_STROBE_SEQ
mdefine_line|#define MPP_STROBE_SEQ&t;&t;0x04C4&t;/* Dword offset 1_31 */
DECL|macro|MPP_ADDR
mdefine_line|#define MPP_ADDR&t;&t;0x04C8&t;/* Dword offset 1_32 */
DECL|macro|MPP_DATA
mdefine_line|#define MPP_DATA&t;&t;0x04CC&t;/* Dword offset 1_33 */
DECL|macro|TVO_CNTL
mdefine_line|#define TVO_CNTL&t;&t;0x0500&t;/* Dword offset 1_40 */
multiline_comment|/* Test and Debug */
DECL|macro|CRT_HORZ_VERT_LOAD
mdefine_line|#define CRT_HORZ_VERT_LOAD&t;0x0544&t;/* Dword offset 1_51 */
multiline_comment|/* AGP */
DECL|macro|AGP_BASE
mdefine_line|#define AGP_BASE&t;&t;0x0548&t;/* Dword offset 1_52 */
DECL|macro|AGP_CNTL
mdefine_line|#define AGP_CNTL&t;&t;0x054C&t;/* Dword offset 1_53 */
DECL|macro|SCALER_COLOUR_CNTL
mdefine_line|#define SCALER_COLOUR_CNTL&t;0x0550&t;/* Dword offset 1_54 */
DECL|macro|SCALER_H_COEFF0
mdefine_line|#define SCALER_H_COEFF0&t;&t;0x0554&t;/* Dword offset 1_55 */
DECL|macro|SCALER_H_COEFF1
mdefine_line|#define SCALER_H_COEFF1&t;&t;0x0558&t;/* Dword offset 1_56 */
DECL|macro|SCALER_H_COEFF2
mdefine_line|#define SCALER_H_COEFF2&t;&t;0x055C&t;/* Dword offset 1_57 */
DECL|macro|SCALER_H_COEFF3
mdefine_line|#define SCALER_H_COEFF3&t;&t;0x0560&t;/* Dword offset 1_58 */
DECL|macro|SCALER_H_COEFF4
mdefine_line|#define SCALER_H_COEFF4&t;&t;0x0564&t;/* Dword offset 1_59 */
multiline_comment|/* Command FIFO */
DECL|macro|GUI_CMDFIFO_DEBUG
mdefine_line|#define GUI_CMDFIFO_DEBUG&t;0x0570&t;/* Dword offset 1_5C */
DECL|macro|GUI_CMDFIFO_DATA
mdefine_line|#define GUI_CMDFIFO_DATA&t;0x0574&t;/* Dword offset 1_5D */
DECL|macro|GUI_CNTL
mdefine_line|#define GUI_CNTL&t;&t;0x0578&t;/* Dword offset 1_5E */
multiline_comment|/* Bus Mastering */
DECL|macro|BM_FRAME_BUF_OFFSET
mdefine_line|#define BM_FRAME_BUF_OFFSET&t;0x0580&t;/* Dword offset 1_60 */
DECL|macro|BM_SYSTEM_MEM_ADDR
mdefine_line|#define BM_SYSTEM_MEM_ADDR&t;0x0584&t;/* Dword offset 1_61 */
DECL|macro|BM_COMMAND
mdefine_line|#define BM_COMMAND&t;&t;0x0588&t;/* Dword offset 1_62 */
DECL|macro|BM_STATUS
mdefine_line|#define BM_STATUS&t;&t;0x058C&t;/* Dword offset 1_63 */
DECL|macro|BM_GUI_TABLE
mdefine_line|#define BM_GUI_TABLE&t;&t;0x05B8&t;/* Dword offset 1_6E */
DECL|macro|BM_SYSTEM_TABLE
mdefine_line|#define BM_SYSTEM_TABLE&t;&t;0x05BC&t;/* Dword offset 1_6F */
DECL|macro|SCALER_BUF0_OFFSET_U
mdefine_line|#define SCALER_BUF0_OFFSET_U&t;0x05D4&t;/* Dword offset 1_75 */
DECL|macro|SCALER_BUF0_OFFSET_V
mdefine_line|#define SCALER_BUF0_OFFSET_V&t;0x05D8&t;/* Dword offset 1_76 */
DECL|macro|SCALER_BUF1_OFFSET_U
mdefine_line|#define SCALER_BUF1_OFFSET_U&t;0x05DC&t;/* Dword offset 1_77 */
DECL|macro|SCALER_BUF1_OFFSET_V
mdefine_line|#define SCALER_BUF1_OFFSET_V&t;0x05E0&t;/* Dword offset 1_78 */
multiline_comment|/* Setup Engine */
DECL|macro|VERTEX_1_S
mdefine_line|#define VERTEX_1_S&t;&t;0x0640&t;/* Dword offset 1_90 */
DECL|macro|VERTEX_1_T
mdefine_line|#define VERTEX_1_T&t;&t;0x0644&t;/* Dword offset 1_91 */
DECL|macro|VERTEX_1_W
mdefine_line|#define VERTEX_1_W&t;&t;0x0648&t;/* Dword offset 1_92 */
DECL|macro|VERTEX_1_SPEC_ARGB
mdefine_line|#define VERTEX_1_SPEC_ARGB&t;0x064C&t;/* Dword offset 1_93 */
DECL|macro|VERTEX_1_Z
mdefine_line|#define VERTEX_1_Z&t;&t;0x0650&t;/* Dword offset 1_94 */
DECL|macro|VERTEX_1_ARGB
mdefine_line|#define VERTEX_1_ARGB&t;&t;0x0654&t;/* Dword offset 1_95 */
DECL|macro|VERTEX_1_X_Y
mdefine_line|#define VERTEX_1_X_Y&t;&t;0x0658&t;/* Dword offset 1_96 */
DECL|macro|ONE_OVER_AREA
mdefine_line|#define ONE_OVER_AREA&t;&t;0x065C&t;/* Dword offset 1_97 */
DECL|macro|VERTEX_2_S
mdefine_line|#define VERTEX_2_S&t;&t;0x0660&t;/* Dword offset 1_98 */
DECL|macro|VERTEX_2_T
mdefine_line|#define VERTEX_2_T&t;&t;0x0664&t;/* Dword offset 1_99 */
DECL|macro|VERTEX_2_W
mdefine_line|#define VERTEX_2_W&t;&t;0x0668&t;/* Dword offset 1_9A */
DECL|macro|VERTEX_2_SPEC_ARGB
mdefine_line|#define VERTEX_2_SPEC_ARGB&t;0x066C&t;/* Dword offset 1_9B */
DECL|macro|VERTEX_2_Z
mdefine_line|#define VERTEX_2_Z&t;&t;0x0670&t;/* Dword offset 1_9C */
DECL|macro|VERTEX_2_ARGB
mdefine_line|#define VERTEX_2_ARGB&t;&t;0x0674&t;/* Dword offset 1_9D */
DECL|macro|VERTEX_2_X_Y
mdefine_line|#define VERTEX_2_X_Y&t;&t;0x0678&t;/* Dword offset 1_9E */
DECL|macro|ONE_OVER_AREA
mdefine_line|#define ONE_OVER_AREA&t;&t;0x065C&t;/* Dword offset 1_9F */
DECL|macro|VERTEX_3_S
mdefine_line|#define VERTEX_3_S&t;&t;0x0680&t;/* Dword offset 1_A0 */
DECL|macro|VERTEX_3_T
mdefine_line|#define VERTEX_3_T&t;&t;0x0684&t;/* Dword offset 1_A1 */
DECL|macro|VERTEX_3_W
mdefine_line|#define VERTEX_3_W&t;&t;0x0688&t;/* Dword offset 1_A2 */
DECL|macro|VERTEX_3_SPEC_ARGB
mdefine_line|#define VERTEX_3_SPEC_ARGB&t;0x068C&t;/* Dword offset 1_A3 */
DECL|macro|VERTEX_3_Z
mdefine_line|#define VERTEX_3_Z&t;&t;0x0690&t;/* Dword offset 1_A4 */
DECL|macro|VERTEX_3_ARGB
mdefine_line|#define VERTEX_3_ARGB&t;&t;0x0694&t;/* Dword offset 1_A5 */
DECL|macro|VERTEX_3_X_Y
mdefine_line|#define VERTEX_3_X_Y&t;&t;0x0698&t;/* Dword offset 1_A6 */
DECL|macro|ONE_OVER_AREA
mdefine_line|#define ONE_OVER_AREA&t;&t;0x065C&t;/* Dword offset 1_A7 */
DECL|macro|VERTEX_1_S
mdefine_line|#define VERTEX_1_S&t;&t;0x0640&t;/* Dword offset 1_AB */
DECL|macro|VERTEX_1_T
mdefine_line|#define VERTEX_1_T&t;&t;0x0644&t;/* Dword offset 1_AC */
DECL|macro|VERTEX_1_W
mdefine_line|#define VERTEX_1_W&t;&t;0x0648&t;/* Dword offset 1_AD */
DECL|macro|VERTEX_2_S
mdefine_line|#define VERTEX_2_S&t;&t;0x0660&t;/* Dword offset 1_AE */
DECL|macro|VERTEX_2_T
mdefine_line|#define VERTEX_2_T&t;&t;0x0664&t;/* Dword offset 1_AF */
DECL|macro|VERTEX_2_W
mdefine_line|#define VERTEX_2_W&t;&t;0x0668&t;/* Dword offset 1_B0 */
DECL|macro|VERTEX_3_SECONDARY_S
mdefine_line|#define VERTEX_3_SECONDARY_S&t;0x06C0&t;/* Dword offset 1_B0 */
DECL|macro|VERTEX_3_S
mdefine_line|#define VERTEX_3_S&t;&t;0x0680&t;/* Dword offset 1_B1 */
DECL|macro|VERTEX_3_SECONDARY_T
mdefine_line|#define VERTEX_3_SECONDARY_T&t;0x06C4&t;/* Dword offset 1_B1 */
DECL|macro|VERTEX_3_T
mdefine_line|#define VERTEX_3_T&t;&t;0x0684&t;/* Dword offset 1_B2 */
DECL|macro|VERTEX_3_SECONDARY_W
mdefine_line|#define VERTEX_3_SECONDARY_W&t;0x06C8&t;/* Dword offset 1_B2 */
DECL|macro|VERTEX_3_W
mdefine_line|#define VERTEX_3_W&t;&t;0x0688&t;/* Dword offset 1_B3 */
DECL|macro|VERTEX_1_SPEC_ARGB
mdefine_line|#define VERTEX_1_SPEC_ARGB&t;0x064C&t;/* Dword offset 1_B4 */
DECL|macro|VERTEX_2_SPEC_ARGB
mdefine_line|#define VERTEX_2_SPEC_ARGB&t;0x066C&t;/* Dword offset 1_B5 */
DECL|macro|VERTEX_3_SPEC_ARGB
mdefine_line|#define VERTEX_3_SPEC_ARGB&t;0x068C&t;/* Dword offset 1_B6 */
DECL|macro|VERTEX_1_Z
mdefine_line|#define VERTEX_1_Z&t;&t;0x0650&t;/* Dword offset 1_B7 */
DECL|macro|VERTEX_2_Z
mdefine_line|#define VERTEX_2_Z&t;&t;0x0670&t;/* Dword offset 1_B8 */
DECL|macro|VERTEX_3_Z
mdefine_line|#define VERTEX_3_Z&t;&t;0x0690&t;/* Dword offset 1_B9 */
DECL|macro|VERTEX_1_ARGB
mdefine_line|#define VERTEX_1_ARGB&t;&t;0x0654&t;/* Dword offset 1_BA */
DECL|macro|VERTEX_2_ARGB
mdefine_line|#define VERTEX_2_ARGB&t;&t;0x0674&t;/* Dword offset 1_BB */
DECL|macro|VERTEX_3_ARGB
mdefine_line|#define VERTEX_3_ARGB&t;&t;0x0694&t;/* Dword offset 1_BC */
DECL|macro|VERTEX_1_X_Y
mdefine_line|#define VERTEX_1_X_Y&t;&t;0x0658&t;/* Dword offset 1_BD */
DECL|macro|VERTEX_2_X_Y
mdefine_line|#define VERTEX_2_X_Y&t;&t;0x0678&t;/* Dword offset 1_BE */
DECL|macro|VERTEX_3_X_Y
mdefine_line|#define VERTEX_3_X_Y&t;&t;0x0698&t;/* Dword offset 1_BF */
DECL|macro|ONE_OVER_AREA_UC
mdefine_line|#define ONE_OVER_AREA_UC&t;0x0700&t;/* Dword offset 1_C0 */
DECL|macro|SETUP_CNTL
mdefine_line|#define SETUP_CNTL&t;&t;0x0704&t;/* Dword offset 1_C1 */
DECL|macro|VERTEX_1_SECONDARY_S
mdefine_line|#define VERTEX_1_SECONDARY_S&t;0x0728&t;/* Dword offset 1_CA */
DECL|macro|VERTEX_1_SECONDARY_T
mdefine_line|#define VERTEX_1_SECONDARY_T&t;0x072C&t;/* Dword offset 1_CB */
DECL|macro|VERTEX_1_SECONDARY_W
mdefine_line|#define VERTEX_1_SECONDARY_W&t;0x0730&t;/* Dword offset 1_CC */
DECL|macro|VERTEX_2_SECONDARY_S
mdefine_line|#define VERTEX_2_SECONDARY_S&t;0x0734&t;/* Dword offset 1_CD */
DECL|macro|VERTEX_2_SECONDARY_T
mdefine_line|#define VERTEX_2_SECONDARY_T&t;0x0738&t;/* Dword offset 1_CE */
DECL|macro|VERTEX_2_SECONDARY_W
mdefine_line|#define VERTEX_2_SECONDARY_W&t;0x073C&t;/* Dword offset 1_CF */
DECL|macro|GTC_3D_RESET_DELAY
mdefine_line|#define GTC_3D_RESET_DELAY&t;3&t;/* 3D engine reset delay in ms */
multiline_comment|/* CRTC control values (mostly CRTC_GEN_CNTL) */
DECL|macro|CRTC_H_SYNC_NEG
mdefine_line|#define CRTC_H_SYNC_NEG&t;&t;0x00200000
DECL|macro|CRTC_V_SYNC_NEG
mdefine_line|#define CRTC_V_SYNC_NEG&t;&t;0x00200000
DECL|macro|CRTC_DBL_SCAN_EN
mdefine_line|#define CRTC_DBL_SCAN_EN&t;0x00000001
DECL|macro|CRTC_INTERLACE_EN
mdefine_line|#define CRTC_INTERLACE_EN&t;0x00000002
DECL|macro|CRTC_HSYNC_DIS
mdefine_line|#define CRTC_HSYNC_DIS&t;&t;0x00000004
DECL|macro|CRTC_VSYNC_DIS
mdefine_line|#define CRTC_VSYNC_DIS&t;&t;0x00000008
DECL|macro|CRTC_CSYNC_EN
mdefine_line|#define CRTC_CSYNC_EN&t;&t;0x00000010
DECL|macro|CRTC_PIX_BY_2_EN
mdefine_line|#define CRTC_PIX_BY_2_EN&t;0x00000020&t;/* unused on RAGE */
DECL|macro|CRTC_DISPLAY_DIS
mdefine_line|#define CRTC_DISPLAY_DIS&t;0x00000040
DECL|macro|CRTC_VGA_XOVERSCAN
mdefine_line|#define CRTC_VGA_XOVERSCAN&t;0x00000040
DECL|macro|CRTC_PIX_WIDTH_MASK
mdefine_line|#define CRTC_PIX_WIDTH_MASK&t;0x00000700
DECL|macro|CRTC_PIX_WIDTH_4BPP
mdefine_line|#define CRTC_PIX_WIDTH_4BPP&t;0x00000100
DECL|macro|CRTC_PIX_WIDTH_8BPP
mdefine_line|#define CRTC_PIX_WIDTH_8BPP&t;0x00000200
DECL|macro|CRTC_PIX_WIDTH_15BPP
mdefine_line|#define CRTC_PIX_WIDTH_15BPP&t;0x00000300
DECL|macro|CRTC_PIX_WIDTH_16BPP
mdefine_line|#define CRTC_PIX_WIDTH_16BPP&t;0x00000400
DECL|macro|CRTC_PIX_WIDTH_24BPP
mdefine_line|#define CRTC_PIX_WIDTH_24BPP&t;0x00000500
DECL|macro|CRTC_PIX_WIDTH_32BPP
mdefine_line|#define CRTC_PIX_WIDTH_32BPP&t;0x00000600
DECL|macro|CRTC_BYTE_PIX_ORDER
mdefine_line|#define CRTC_BYTE_PIX_ORDER&t;0x00000800
DECL|macro|CRTC_PIX_ORDER_MSN_LSN
mdefine_line|#define CRTC_PIX_ORDER_MSN_LSN&t;0x00000000
DECL|macro|CRTC_PIX_ORDER_LSN_MSN
mdefine_line|#define CRTC_PIX_ORDER_LSN_MSN&t;0x00000800
DECL|macro|CRTC_FIFO_LWM
mdefine_line|#define CRTC_FIFO_LWM&t;&t;0x000f0000
DECL|macro|VGA_128KAP_PAGING
mdefine_line|#define VGA_128KAP_PAGING&t;0x00100000
DECL|macro|VFC_SYNC_TRISTATE
mdefine_line|#define VFC_SYNC_TRISTATE&t;0x00200000
DECL|macro|CRTC_LOCK_REGS
mdefine_line|#define CRTC_LOCK_REGS&t;&t;0x00400000
DECL|macro|CRTC_SYNC_TRISTATE
mdefine_line|#define CRTC_SYNC_TRISTATE&t;0x00800000
DECL|macro|CRTC_EXT_DISP_EN
mdefine_line|#define CRTC_EXT_DISP_EN&t;0x01000000
DECL|macro|CRTC_ENABLE
mdefine_line|#define CRTC_ENABLE&t;&t;0x02000000
DECL|macro|CRTC_DISP_REQ_ENB
mdefine_line|#define CRTC_DISP_REQ_ENB&t;0x04000000
DECL|macro|VGA_ATI_LINEAR
mdefine_line|#define VGA_ATI_LINEAR&t;&t;0x08000000
DECL|macro|CRTC_VSYNC_FALL_EDGE
mdefine_line|#define CRTC_VSYNC_FALL_EDGE&t;0x10000000
DECL|macro|VGA_TEXT_132
mdefine_line|#define VGA_TEXT_132&t;&t;0x20000000
DECL|macro|VGA_XCRT_CNT_EN
mdefine_line|#define VGA_XCRT_CNT_EN&t;&t;0x40000000
DECL|macro|VGA_CUR_B_TEST
mdefine_line|#define VGA_CUR_B_TEST&t;&t;0x80000000
DECL|macro|CRTC_CRNT_VLINE
mdefine_line|#define CRTC_CRNT_VLINE&t;&t;0x07f00000
DECL|macro|CRTC_VBLANK
mdefine_line|#define CRTC_VBLANK&t;&t;0x00000001
multiline_comment|/* DAC control values */
DECL|macro|DAC_EXT_SEL_RS2
mdefine_line|#define DAC_EXT_SEL_RS2&t;&t;0x01
DECL|macro|DAC_EXT_SEL_RS3
mdefine_line|#define DAC_EXT_SEL_RS3&t;&t;0x02
DECL|macro|DAC_8BIT_EN
mdefine_line|#define DAC_8BIT_EN&t;&t;0x00000100
DECL|macro|DAC_PIX_DLY_MASK
mdefine_line|#define DAC_PIX_DLY_MASK&t;0x00000600
DECL|macro|DAC_PIX_DLY_0NS
mdefine_line|#define DAC_PIX_DLY_0NS&t;&t;0x00000000
DECL|macro|DAC_PIX_DLY_2NS
mdefine_line|#define DAC_PIX_DLY_2NS&t;&t;0x00000200
DECL|macro|DAC_PIX_DLY_4NS
mdefine_line|#define DAC_PIX_DLY_4NS&t;&t;0x00000400
DECL|macro|DAC_BLANK_ADJ_MASK
mdefine_line|#define DAC_BLANK_ADJ_MASK&t;0x00001800
DECL|macro|DAC_BLANK_ADJ_0
mdefine_line|#define DAC_BLANK_ADJ_0&t;&t;0x00000000
DECL|macro|DAC_BLANK_ADJ_1
mdefine_line|#define DAC_BLANK_ADJ_1&t;&t;0x00000800
DECL|macro|DAC_BLANK_ADJ_2
mdefine_line|#define DAC_BLANK_ADJ_2&t;&t;0x00001000
multiline_comment|/* Mix control values */
DECL|macro|MIX_NOT_DST
mdefine_line|#define MIX_NOT_DST&t;&t;0x0000
DECL|macro|MIX_0
mdefine_line|#define MIX_0&t;&t;&t;0x0001
DECL|macro|MIX_1
mdefine_line|#define MIX_1&t;&t;&t;0x0002
DECL|macro|MIX_DST
mdefine_line|#define MIX_DST&t;&t;&t;0x0003
DECL|macro|MIX_NOT_SRC
mdefine_line|#define MIX_NOT_SRC&t;&t;0x0004
DECL|macro|MIX_XOR
mdefine_line|#define MIX_XOR&t;&t;&t;0x0005
DECL|macro|MIX_XNOR
mdefine_line|#define MIX_XNOR&t;&t;0x0006
DECL|macro|MIX_SRC
mdefine_line|#define MIX_SRC&t;&t;&t;0x0007
DECL|macro|MIX_NAND
mdefine_line|#define MIX_NAND&t;&t;0x0008
DECL|macro|MIX_NOT_SRC_OR_DST
mdefine_line|#define MIX_NOT_SRC_OR_DST&t;0x0009
DECL|macro|MIX_SRC_OR_NOT_DST
mdefine_line|#define MIX_SRC_OR_NOT_DST&t;0x000a
DECL|macro|MIX_OR
mdefine_line|#define MIX_OR&t;&t;&t;0x000b
DECL|macro|MIX_AND
mdefine_line|#define MIX_AND&t;&t;&t;0x000c
DECL|macro|MIX_SRC_AND_NOT_DST
mdefine_line|#define MIX_SRC_AND_NOT_DST&t;0x000d
DECL|macro|MIX_NOT_SRC_AND_DST
mdefine_line|#define MIX_NOT_SRC_AND_DST&t;0x000e
DECL|macro|MIX_NOR
mdefine_line|#define MIX_NOR&t;&t;&t;0x000f
multiline_comment|/* Maximum engine dimensions */
DECL|macro|ENGINE_MIN_X
mdefine_line|#define ENGINE_MIN_X&t;&t;0
DECL|macro|ENGINE_MIN_Y
mdefine_line|#define ENGINE_MIN_Y&t;&t;0
DECL|macro|ENGINE_MAX_X
mdefine_line|#define ENGINE_MAX_X&t;&t;4095
DECL|macro|ENGINE_MAX_Y
mdefine_line|#define ENGINE_MAX_Y&t;&t;16383
multiline_comment|/* Mach64 engine bit constants - these are typically ORed together */
multiline_comment|/* BUS_CNTL register constants */
DECL|macro|BUS_FIFO_ERR_ACK
mdefine_line|#define BUS_FIFO_ERR_ACK&t;0x00200000
DECL|macro|BUS_HOST_ERR_ACK
mdefine_line|#define BUS_HOST_ERR_ACK&t;0x00800000
multiline_comment|/* GEN_TEST_CNTL register constants */
DECL|macro|GEN_OVR_OUTPUT_EN
mdefine_line|#define GEN_OVR_OUTPUT_EN&t;0x20
DECL|macro|HWCURSOR_ENABLE
mdefine_line|#define HWCURSOR_ENABLE&t;&t;0x80
DECL|macro|GUI_ENGINE_ENABLE
mdefine_line|#define GUI_ENGINE_ENABLE&t;0x100
DECL|macro|BLOCK_WRITE_ENABLE
mdefine_line|#define BLOCK_WRITE_ENABLE&t;0x200
multiline_comment|/* DSP_CONFIG register constants */
DECL|macro|DSP_XCLKS_PER_QW
mdefine_line|#define DSP_XCLKS_PER_QW&t;0x00003fff
DECL|macro|DSP_LOOP_LATENCY
mdefine_line|#define DSP_LOOP_LATENCY&t;0x000f0000
DECL|macro|DSP_PRECISION
mdefine_line|#define DSP_PRECISION&t;&t;0x00700000
multiline_comment|/* DSP_ON_OFF register constants */
DECL|macro|DSP_OFF
mdefine_line|#define DSP_OFF&t;&t;&t;0x000007ff
DECL|macro|DSP_ON
mdefine_line|#define DSP_ON&t;&t;&t;0x07ff0000
multiline_comment|/* CLOCK_CNTL register constants */
DECL|macro|CLOCK_SEL
mdefine_line|#define CLOCK_SEL&t;&t;0x0f
DECL|macro|CLOCK_DIV
mdefine_line|#define CLOCK_DIV&t;&t;0x30
DECL|macro|CLOCK_DIV1
mdefine_line|#define CLOCK_DIV1&t;&t;0x00
DECL|macro|CLOCK_DIV2
mdefine_line|#define CLOCK_DIV2&t;&t;0x10
DECL|macro|CLOCK_DIV4
mdefine_line|#define CLOCK_DIV4&t;&t;0x20
DECL|macro|CLOCK_STROBE
mdefine_line|#define CLOCK_STROBE&t;&t;0x40
DECL|macro|PLL_WR_EN
mdefine_line|#define PLL_WR_EN&t;&t;0x02
multiline_comment|/* PLL register indices */
DECL|macro|MPLL_CNTL
mdefine_line|#define MPLL_CNTL&t;&t;0x00
DECL|macro|VPLL_CNTL
mdefine_line|#define VPLL_CNTL&t;&t;0x01
DECL|macro|PLL_REF_DIV
mdefine_line|#define PLL_REF_DIV&t;&t;0x02
DECL|macro|PLL_GEN_CNTL
mdefine_line|#define PLL_GEN_CNTL&t;&t;0x03
DECL|macro|MCLK_FB_DIV
mdefine_line|#define MCLK_FB_DIV&t;&t;0x04
DECL|macro|PLL_VCLK_CNTL
mdefine_line|#define PLL_VCLK_CNTL&t;&t;0x05
DECL|macro|VCLK_POST_DIV
mdefine_line|#define VCLK_POST_DIV&t;&t;0x06
DECL|macro|VCLK0_FB_DIV
mdefine_line|#define VCLK0_FB_DIV&t;&t;0x07
DECL|macro|VCLK1_FB_DIV
mdefine_line|#define VCLK1_FB_DIV&t;&t;0x08
DECL|macro|VCLK2_FB_DIV
mdefine_line|#define VCLK2_FB_DIV&t;&t;0x09
DECL|macro|VCLK3_FB_DIV
mdefine_line|#define VCLK3_FB_DIV&t;&t;0x0A
DECL|macro|PLL_EXT_CNTL
mdefine_line|#define PLL_EXT_CNTL&t;&t;0x0B
DECL|macro|DLL_CNTL
mdefine_line|#define DLL_CNTL&t;&t;0x0C
DECL|macro|DLL1_CNTL
mdefine_line|#define DLL1_CNTL&t;&t;0x0C
DECL|macro|VFC_CNTL
mdefine_line|#define VFC_CNTL&t;&t;0x0D
DECL|macro|PLL_TEST_CNTL
mdefine_line|#define PLL_TEST_CNTL&t;&t;0x0E
DECL|macro|PLL_TEST_COUNT
mdefine_line|#define PLL_TEST_COUNT&t;&t;0x0F
DECL|macro|LVDS_CNTL0
mdefine_line|#define LVDS_CNTL0&t;&t;0x10
DECL|macro|LVDS_CNTL1
mdefine_line|#define LVDS_CNTL1&t;&t;0x11
DECL|macro|AGP1_CNTL
mdefine_line|#define AGP1_CNTL&t;&t;0x12
DECL|macro|AGP2_CNTL
mdefine_line|#define AGP2_CNTL&t;&t;0x13
DECL|macro|DLL2_CNTL
mdefine_line|#define DLL2_CNTL&t;&t;0x14
DECL|macro|SCLK_FB_DIV
mdefine_line|#define SCLK_FB_DIV&t;&t;0x15
DECL|macro|SPLL_CNTL1
mdefine_line|#define SPLL_CNTL1&t;&t;0x16
DECL|macro|SPLL_CNTL2
mdefine_line|#define SPLL_CNTL2&t;&t;0x17
DECL|macro|APLL_STRAPS
mdefine_line|#define APLL_STRAPS&t;&t;0x18
DECL|macro|EXT_VPLL_CNTL
mdefine_line|#define EXT_VPLL_CNTL&t;&t;0x19
DECL|macro|EXT_VPLL_REF_DIV
mdefine_line|#define EXT_VPLL_REF_DIV&t;0x1A
DECL|macro|EXT_VPLL_FB_DIV
mdefine_line|#define EXT_VPLL_FB_DIV&t;&t;0x1B
DECL|macro|EXT_VPLL_MSB
mdefine_line|#define EXT_VPLL_MSB&t;&t;0x1C
DECL|macro|HTOTAL_CNTL
mdefine_line|#define HTOTAL_CNTL&t;&t;0x1D
DECL|macro|BYTE_CLK_CNTL
mdefine_line|#define BYTE_CLK_CNTL&t;&t;0x1E
DECL|macro|TV_PLL_CNTL1
mdefine_line|#define TV_PLL_CNTL1&t;&t;0x1F
DECL|macro|TV_PLL_CNTL2
mdefine_line|#define TV_PLL_CNTL2&t;&t;0x20
DECL|macro|TV_PLL_CNTL
mdefine_line|#define TV_PLL_CNTL&t;&t;0x21
DECL|macro|EXT_TV_PLL
mdefine_line|#define EXT_TV_PLL&t;&t;0x22
DECL|macro|V2PLL_CNTL
mdefine_line|#define V2PLL_CNTL&t;&t;0x23
DECL|macro|PLL_V2CLK_CNTL
mdefine_line|#define PLL_V2CLK_CNTL&t;&t;0x24
DECL|macro|EXT_V2PLL_REF_DIV
mdefine_line|#define EXT_V2PLL_REF_DIV&t;0x25
DECL|macro|EXT_V2PLL_FB_DIV
mdefine_line|#define EXT_V2PLL_FB_DIV&t;0x26
DECL|macro|EXT_V2PLL_MSB
mdefine_line|#define EXT_V2PLL_MSB&t;&t;0x27
DECL|macro|HTOTAL2_CNTL
mdefine_line|#define HTOTAL2_CNTL&t;&t;0x28
DECL|macro|PLL_YCLK_CNTL
mdefine_line|#define PLL_YCLK_CNTL&t;&t;0x29
DECL|macro|PM_DYN_CLK_CNTL
mdefine_line|#define PM_DYN_CLK_CNTL&t;&t;0x2A
multiline_comment|/* Fields in PLL registers */
DECL|macro|PLL_PC_GAIN
mdefine_line|#define PLL_PC_GAIN&t;&t;0x07
DECL|macro|PLL_VC_GAIN
mdefine_line|#define PLL_VC_GAIN&t;&t;0x18
DECL|macro|PLL_DUTY_CYC
mdefine_line|#define PLL_DUTY_CYC&t;&t;0xE0
DECL|macro|PLL_OVERRIDE
mdefine_line|#define PLL_OVERRIDE&t;&t;0x01
DECL|macro|PLL_MCLK_RST
mdefine_line|#define PLL_MCLK_RST&t;&t;0x02
DECL|macro|OSC_EN
mdefine_line|#define OSC_EN&t;&t;&t;0x04
DECL|macro|EXT_CLK_EN
mdefine_line|#define EXT_CLK_EN&t;&t;0x08
DECL|macro|MCLK_SRC_SEL
mdefine_line|#define MCLK_SRC_SEL&t;&t;0x70
DECL|macro|EXT_CLK_CNTL
mdefine_line|#define EXT_CLK_CNTL&t;&t;0x80
DECL|macro|VCLK_SRC_SEL
mdefine_line|#define VCLK_SRC_SEL&t;&t;0x03
DECL|macro|PLL_VCLK_RST
mdefine_line|#define PLL_VCLK_RST&t;&t;0x04
DECL|macro|VCLK_INVERT
mdefine_line|#define VCLK_INVERT&t;&t;0x08
DECL|macro|VCLK0_POST
mdefine_line|#define VCLK0_POST&t;&t;0x03
DECL|macro|VCLK1_POST
mdefine_line|#define VCLK1_POST&t;&t;0x0C
DECL|macro|VCLK2_POST
mdefine_line|#define VCLK2_POST&t;&t;0x30
DECL|macro|VCLK3_POST
mdefine_line|#define VCLK3_POST&t;&t;0xC0
multiline_comment|/* CONFIG_CNTL register constants */
DECL|macro|APERTURE_4M_ENABLE
mdefine_line|#define APERTURE_4M_ENABLE&t;1
DECL|macro|APERTURE_8M_ENABLE
mdefine_line|#define APERTURE_8M_ENABLE&t;2
DECL|macro|VGA_APERTURE_ENABLE
mdefine_line|#define VGA_APERTURE_ENABLE&t;4
multiline_comment|/* CONFIG_STAT0 register constants (GX, CX) */
DECL|macro|CFG_BUS_TYPE
mdefine_line|#define CFG_BUS_TYPE&t;&t;0x00000007
DECL|macro|CFG_MEM_TYPE
mdefine_line|#define CFG_MEM_TYPE&t;&t;0x00000038
DECL|macro|CFG_INIT_DAC_TYPE
mdefine_line|#define CFG_INIT_DAC_TYPE&t;0x00000e00
multiline_comment|/* CONFIG_STAT0 register constants (CT, ET, VT) */
DECL|macro|CFG_MEM_TYPE_xT
mdefine_line|#define CFG_MEM_TYPE_xT&t;&t;0x00000007
DECL|macro|ISA
mdefine_line|#define ISA&t;&t;&t;0
DECL|macro|EISA
mdefine_line|#define EISA&t;&t;&t;1
DECL|macro|LOCAL_BUS
mdefine_line|#define LOCAL_BUS&t;&t;6
DECL|macro|PCI
mdefine_line|#define PCI&t;&t;&t;7
multiline_comment|/* Memory types for GX, CX */
DECL|macro|DRAMx4
mdefine_line|#define DRAMx4&t;&t;&t;0
DECL|macro|VRAMx16
mdefine_line|#define VRAMx16&t;&t;&t;1
DECL|macro|VRAMx16ssr
mdefine_line|#define VRAMx16ssr&t;&t;2
DECL|macro|DRAMx16
mdefine_line|#define DRAMx16&t;&t;&t;3
DECL|macro|GraphicsDRAMx16
mdefine_line|#define GraphicsDRAMx16&t;&t;4
DECL|macro|EnhancedVRAMx16
mdefine_line|#define EnhancedVRAMx16&t;&t;5
DECL|macro|EnhancedVRAMx16ssr
mdefine_line|#define EnhancedVRAMx16ssr&t;6
multiline_comment|/* Memory types for CT, ET, VT, GT */
DECL|macro|DRAM
mdefine_line|#define DRAM&t;&t;&t;1
DECL|macro|EDO
mdefine_line|#define EDO&t;&t;&t;2
DECL|macro|PSEUDO_EDO
mdefine_line|#define PSEUDO_EDO&t;&t;3
DECL|macro|SDRAM
mdefine_line|#define SDRAM&t;&t;&t;4
DECL|macro|SGRAM
mdefine_line|#define SGRAM&t;&t;&t;5
DECL|macro|WRAM
mdefine_line|#define WRAM&t;&t;&t;6
DECL|macro|DAC_INTERNAL
mdefine_line|#define DAC_INTERNAL&t;&t;0x00
DECL|macro|DAC_IBMRGB514
mdefine_line|#define DAC_IBMRGB514&t;&t;0x01
DECL|macro|DAC_ATI68875
mdefine_line|#define DAC_ATI68875&t;&t;0x02
DECL|macro|DAC_TVP3026_A
mdefine_line|#define DAC_TVP3026_A&t;&t;0x72
DECL|macro|DAC_BT476
mdefine_line|#define DAC_BT476&t;&t;0x03
DECL|macro|DAC_BT481
mdefine_line|#define DAC_BT481&t;&t;0x04
DECL|macro|DAC_ATT20C491
mdefine_line|#define DAC_ATT20C491&t;&t;0x14
DECL|macro|DAC_SC15026
mdefine_line|#define DAC_SC15026&t;&t;0x24
DECL|macro|DAC_MU9C1880
mdefine_line|#define DAC_MU9C1880&t;&t;0x34
DECL|macro|DAC_IMSG174
mdefine_line|#define DAC_IMSG174&t;&t;0x44
DECL|macro|DAC_ATI68860_B
mdefine_line|#define DAC_ATI68860_B&t;&t;0x05
DECL|macro|DAC_ATI68860_C
mdefine_line|#define DAC_ATI68860_C&t;&t;0x15
DECL|macro|DAC_TVP3026_B
mdefine_line|#define DAC_TVP3026_B&t;&t;0x75
DECL|macro|DAC_STG1700
mdefine_line|#define DAC_STG1700&t;&t;0x06
DECL|macro|DAC_ATT498
mdefine_line|#define DAC_ATT498&t;&t;0x16
DECL|macro|DAC_STG1702
mdefine_line|#define DAC_STG1702&t;&t;0x07
DECL|macro|DAC_SC15021
mdefine_line|#define DAC_SC15021&t;&t;0x17
DECL|macro|DAC_ATT21C498
mdefine_line|#define DAC_ATT21C498&t;&t;0x27
DECL|macro|DAC_STG1703
mdefine_line|#define DAC_STG1703&t;&t;0x37
DECL|macro|DAC_CH8398
mdefine_line|#define DAC_CH8398&t;&t;0x47
DECL|macro|DAC_ATT20C408
mdefine_line|#define DAC_ATT20C408&t;&t;0x57
DECL|macro|CLK_ATI18818_0
mdefine_line|#define CLK_ATI18818_0&t;&t;0
DECL|macro|CLK_ATI18818_1
mdefine_line|#define CLK_ATI18818_1&t;&t;1
DECL|macro|CLK_STG1703
mdefine_line|#define CLK_STG1703&t;&t;2
DECL|macro|CLK_CH8398
mdefine_line|#define CLK_CH8398&t;&t;3
DECL|macro|CLK_INTERNAL
mdefine_line|#define CLK_INTERNAL&t;&t;4
DECL|macro|CLK_ATT20C408
mdefine_line|#define CLK_ATT20C408&t;&t;5
DECL|macro|CLK_IBMRGB514
mdefine_line|#define CLK_IBMRGB514&t;&t;6
multiline_comment|/* MEM_CNTL register constants */
DECL|macro|MEM_SIZE_ALIAS
mdefine_line|#define MEM_SIZE_ALIAS&t;&t;0x00000007
DECL|macro|MEM_SIZE_512K
mdefine_line|#define MEM_SIZE_512K&t;&t;0x00000000
DECL|macro|MEM_SIZE_1M
mdefine_line|#define MEM_SIZE_1M&t;&t;0x00000001
DECL|macro|MEM_SIZE_2M
mdefine_line|#define MEM_SIZE_2M&t;&t;0x00000002
DECL|macro|MEM_SIZE_4M
mdefine_line|#define MEM_SIZE_4M&t;&t;0x00000003
DECL|macro|MEM_SIZE_6M
mdefine_line|#define MEM_SIZE_6M&t;&t;0x00000004
DECL|macro|MEM_SIZE_8M
mdefine_line|#define MEM_SIZE_8M&t;&t;0x00000005
DECL|macro|MEM_SIZE_ALIAS_GTB
mdefine_line|#define MEM_SIZE_ALIAS_GTB&t;0x0000000F
DECL|macro|MEM_SIZE_2M_GTB
mdefine_line|#define MEM_SIZE_2M_GTB&t;&t;0x00000003
DECL|macro|MEM_SIZE_4M_GTB
mdefine_line|#define MEM_SIZE_4M_GTB&t;&t;0x00000007
DECL|macro|MEM_SIZE_6M_GTB
mdefine_line|#define MEM_SIZE_6M_GTB&t;&t;0x00000009
DECL|macro|MEM_SIZE_8M_GTB
mdefine_line|#define MEM_SIZE_8M_GTB&t;&t;0x0000000B
DECL|macro|MEM_BNDRY
mdefine_line|#define MEM_BNDRY&t;&t;0x00030000
DECL|macro|MEM_BNDRY_0K
mdefine_line|#define MEM_BNDRY_0K&t;&t;0x00000000
DECL|macro|MEM_BNDRY_256K
mdefine_line|#define MEM_BNDRY_256K&t;&t;0x00010000
DECL|macro|MEM_BNDRY_512K
mdefine_line|#define MEM_BNDRY_512K&t;&t;0x00020000
DECL|macro|MEM_BNDRY_1M
mdefine_line|#define MEM_BNDRY_1M&t;&t;0x00030000
DECL|macro|MEM_BNDRY_EN
mdefine_line|#define MEM_BNDRY_EN&t;&t;0x00040000
multiline_comment|/* ATI PCI constants */
DECL|macro|PCI_ATI_VENDOR_ID
mdefine_line|#define PCI_ATI_VENDOR_ID&t;0x1002
multiline_comment|/* CONFIG_CHIP_ID register constants */
DECL|macro|CFG_CHIP_TYPE
mdefine_line|#define CFG_CHIP_TYPE&t;&t;0x0000FFFF
DECL|macro|CFG_CHIP_CLASS
mdefine_line|#define CFG_CHIP_CLASS&t;&t;0x00FF0000
DECL|macro|CFG_CHIP_REV
mdefine_line|#define CFG_CHIP_REV&t;&t;0xFF000000
DECL|macro|CFG_CHIP_MAJOR
mdefine_line|#define CFG_CHIP_MAJOR&t;&t;0x07000000
DECL|macro|CFG_CHIP_FND_ID
mdefine_line|#define CFG_CHIP_FND_ID&t;&t;0x38000000
DECL|macro|CFG_CHIP_MINOR
mdefine_line|#define CFG_CHIP_MINOR&t;&t;0xC0000000
multiline_comment|/* Chip IDs read from CONFIG_CHIP_ID */
multiline_comment|/* mach64GX family */
DECL|macro|GX_CHIP_ID
mdefine_line|#define GX_CHIP_ID&t;0xD7&t;/* mach64GX (ATI888GX00) */
DECL|macro|CX_CHIP_ID
mdefine_line|#define CX_CHIP_ID&t;0x57&t;/* mach64CX (ATI888CX00) */
DECL|macro|GX_PCI_ID
mdefine_line|#define GX_PCI_ID&t;0x4758&t;/* mach64GX (ATI888GX00) */
DECL|macro|CX_PCI_ID
mdefine_line|#define CX_PCI_ID&t;0x4358&t;/* mach64CX (ATI888CX00) */
multiline_comment|/* mach64CT family */
DECL|macro|CT_CHIP_ID
mdefine_line|#define CT_CHIP_ID&t;0x4354&t;/* mach64CT (ATI264CT) */
DECL|macro|ET_CHIP_ID
mdefine_line|#define ET_CHIP_ID&t;0x4554&t;/* mach64ET (ATI264ET) */
multiline_comment|/* mach64CT family / mach64VT class */
DECL|macro|VT_CHIP_ID
mdefine_line|#define VT_CHIP_ID&t;0x5654&t;/* mach64VT (ATI264VT) */
DECL|macro|VU_CHIP_ID
mdefine_line|#define VU_CHIP_ID&t;0x5655&t;/* mach64VTB (ATI264VTB) */
DECL|macro|VV_CHIP_ID
mdefine_line|#define VV_CHIP_ID&t;0x5656&t;/* mach64VT4 (ATI264VT4) */
multiline_comment|/* mach64CT family / mach64GT (3D RAGE) class */
DECL|macro|LB_CHIP_ID
mdefine_line|#define LB_CHIP_ID&t;0x4c42&t;/* RAGE LT PRO, AGP */
DECL|macro|LD_CHIP_ID
mdefine_line|#define LD_CHIP_ID&t;0x4c44&t;/* RAGE LT PRO */
DECL|macro|LG_CHIP_ID
mdefine_line|#define LG_CHIP_ID&t;0x4c47&t;/* RAGE LT */
DECL|macro|LI_CHIP_ID
mdefine_line|#define LI_CHIP_ID&t;0x4c49&t;/* RAGE LT PRO */
DECL|macro|LP_CHIP_ID
mdefine_line|#define LP_CHIP_ID&t;0x4c50&t;/* RAGE LT PRO */
DECL|macro|LT_CHIP_ID
mdefine_line|#define LT_CHIP_ID&t;0x4c54&t;/* RAGE LT */
DECL|macro|XL_CHIP_ID
mdefine_line|#define XL_CHIP_ID&t;0x4752&t;/* RAGE (XL) */
DECL|macro|GT_CHIP_ID
mdefine_line|#define GT_CHIP_ID&t;0x4754&t;/* RAGE (GT) */
DECL|macro|GU_CHIP_ID
mdefine_line|#define GU_CHIP_ID&t;0x4755&t;/* RAGE II/II+ (GTB) */
DECL|macro|GV_CHIP_ID
mdefine_line|#define GV_CHIP_ID&t;0x4756&t;/* RAGE IIC, PCI */
DECL|macro|GW_CHIP_ID
mdefine_line|#define GW_CHIP_ID&t;0x4757&t;/* RAGE IIC, AGP */
DECL|macro|GZ_CHIP_ID
mdefine_line|#define GZ_CHIP_ID&t;0x475a&t;/* RAGE IIC, AGP */
DECL|macro|GB_CHIP_ID
mdefine_line|#define GB_CHIP_ID&t;0x4742&t;/* RAGE PRO, BGA, AGP 1x and 2x */
DECL|macro|GD_CHIP_ID
mdefine_line|#define GD_CHIP_ID&t;0x4744&t;/* RAGE PRO, BGA, AGP 1x only */
DECL|macro|GI_CHIP_ID
mdefine_line|#define GI_CHIP_ID&t;0x4749&t;/* RAGE PRO, BGA, PCI33 only */
DECL|macro|GP_CHIP_ID
mdefine_line|#define GP_CHIP_ID&t;0x4750&t;/* RAGE PRO, PQFP, PCI33, full 3D */
DECL|macro|GQ_CHIP_ID
mdefine_line|#define GQ_CHIP_ID&t;0x4751&t;/* RAGE PRO, PQFP, PCI33, limited 3D */
DECL|macro|LM_CHIP_ID
mdefine_line|#define LM_CHIP_ID&t;0x4c4d&t;/* RAGE Mobility PCI */
DECL|macro|LN_CHIP_ID
mdefine_line|#define LN_CHIP_ID&t;0x4c4e&t;/* RAGE Mobility AGP */
multiline_comment|/* Mach64 major ASIC revisions */
DECL|macro|MACH64_ASIC_NEC_VT_A3
mdefine_line|#define MACH64_ASIC_NEC_VT_A3&t;&t;0x08
DECL|macro|MACH64_ASIC_NEC_VT_A4
mdefine_line|#define MACH64_ASIC_NEC_VT_A4&t;&t;0x48
DECL|macro|MACH64_ASIC_SGS_VT_A4
mdefine_line|#define MACH64_ASIC_SGS_VT_A4&t;&t;0x40
DECL|macro|MACH64_ASIC_SGS_VT_B1S1
mdefine_line|#define MACH64_ASIC_SGS_VT_B1S1&t;&t;0x01
DECL|macro|MACH64_ASIC_SGS_GT_B1S1
mdefine_line|#define MACH64_ASIC_SGS_GT_B1S1&t;&t;0x01
DECL|macro|MACH64_ASIC_SGS_GT_B1S2
mdefine_line|#define MACH64_ASIC_SGS_GT_B1S2&t;&t;0x41
DECL|macro|MACH64_ASIC_UMC_GT_B2U1
mdefine_line|#define MACH64_ASIC_UMC_GT_B2U1&t;&t;0x1a
DECL|macro|MACH64_ASIC_UMC_GT_B2U2
mdefine_line|#define MACH64_ASIC_UMC_GT_B2U2&t;&t;0x5a
DECL|macro|MACH64_ASIC_UMC_VT_B2U3
mdefine_line|#define MACH64_ASIC_UMC_VT_B2U3&t;&t;0x9a
DECL|macro|MACH64_ASIC_UMC_GT_B2U3
mdefine_line|#define MACH64_ASIC_UMC_GT_B2U3&t;&t;0x9a
DECL|macro|MACH64_ASIC_UMC_R3B_D_P_A1
mdefine_line|#define MACH64_ASIC_UMC_R3B_D_P_A1&t;0x1b
DECL|macro|MACH64_ASIC_UMC_R3B_D_P_A2
mdefine_line|#define MACH64_ASIC_UMC_R3B_D_P_A2&t;0x5b
DECL|macro|MACH64_ASIC_UMC_R3B_D_P_A3
mdefine_line|#define MACH64_ASIC_UMC_R3B_D_P_A3&t;0x1c
DECL|macro|MACH64_ASIC_UMC_R3B_D_P_A4
mdefine_line|#define MACH64_ASIC_UMC_R3B_D_P_A4&t;0x5c
multiline_comment|/* Mach64 foundries */
DECL|macro|MACH64_FND_SGS
mdefine_line|#define MACH64_FND_SGS&t;&t;0
DECL|macro|MACH64_FND_NEC
mdefine_line|#define MACH64_FND_NEC&t;&t;1
DECL|macro|MACH64_FND_UMC
mdefine_line|#define MACH64_FND_UMC&t;&t;3
multiline_comment|/* Mach64 chip types */
DECL|macro|MACH64_UNKNOWN
mdefine_line|#define MACH64_UNKNOWN&t;&t;0
DECL|macro|MACH64_GX
mdefine_line|#define MACH64_GX&t;&t;1
DECL|macro|MACH64_CX
mdefine_line|#define MACH64_CX&t;&t;2
DECL|macro|MACH64_CT
mdefine_line|#define MACH64_CT&t;&t;3
DECL|macro|MACH64_ET
mdefine_line|#define MACH64_ET&t;&t;4
DECL|macro|MACH64_VT
mdefine_line|#define MACH64_VT&t;&t;5
DECL|macro|MACH64_GT
mdefine_line|#define MACH64_GT&t;&t;6
multiline_comment|/* DST_CNTL register constants */
DECL|macro|DST_X_RIGHT_TO_LEFT
mdefine_line|#define DST_X_RIGHT_TO_LEFT&t;0
DECL|macro|DST_X_LEFT_TO_RIGHT
mdefine_line|#define DST_X_LEFT_TO_RIGHT&t;1
DECL|macro|DST_Y_BOTTOM_TO_TOP
mdefine_line|#define DST_Y_BOTTOM_TO_TOP&t;0
DECL|macro|DST_Y_TOP_TO_BOTTOM
mdefine_line|#define DST_Y_TOP_TO_BOTTOM&t;2
DECL|macro|DST_X_MAJOR
mdefine_line|#define DST_X_MAJOR&t;&t;0
DECL|macro|DST_Y_MAJOR
mdefine_line|#define DST_Y_MAJOR&t;&t;4
DECL|macro|DST_X_TILE
mdefine_line|#define DST_X_TILE&t;&t;8
DECL|macro|DST_Y_TILE
mdefine_line|#define DST_Y_TILE&t;&t;0x10
DECL|macro|DST_LAST_PEL
mdefine_line|#define DST_LAST_PEL&t;&t;0x20
DECL|macro|DST_POLYGON_ENABLE
mdefine_line|#define DST_POLYGON_ENABLE&t;0x40
DECL|macro|DST_24_ROTATION_ENABLE
mdefine_line|#define DST_24_ROTATION_ENABLE&t;0x80
multiline_comment|/* SRC_CNTL register constants */
DECL|macro|SRC_PATTERN_ENABLE
mdefine_line|#define SRC_PATTERN_ENABLE&t;&t;1
DECL|macro|SRC_ROTATION_ENABLE
mdefine_line|#define SRC_ROTATION_ENABLE&t;&t;2
DECL|macro|SRC_LINEAR_ENABLE
mdefine_line|#define SRC_LINEAR_ENABLE&t;&t;4
DECL|macro|SRC_BYTE_ALIGN
mdefine_line|#define SRC_BYTE_ALIGN&t;&t;&t;8
DECL|macro|SRC_LINE_X_RIGHT_TO_LEFT
mdefine_line|#define SRC_LINE_X_RIGHT_TO_LEFT&t;0
DECL|macro|SRC_LINE_X_LEFT_TO_RIGHT
mdefine_line|#define SRC_LINE_X_LEFT_TO_RIGHT&t;0x10
multiline_comment|/* HOST_CNTL register constants */
DECL|macro|HOST_BYTE_ALIGN
mdefine_line|#define HOST_BYTE_ALIGN&t;&t;1
multiline_comment|/* GUI_TRAJ_CNTL register constants */
DECL|macro|PAT_MONO_8x8_ENABLE
mdefine_line|#define PAT_MONO_8x8_ENABLE&t;0x01000000
DECL|macro|PAT_CLR_4x2_ENABLE
mdefine_line|#define PAT_CLR_4x2_ENABLE&t;0x02000000
DECL|macro|PAT_CLR_8x1_ENABLE
mdefine_line|#define PAT_CLR_8x1_ENABLE&t;0x04000000
multiline_comment|/* DP_CHAIN_MASK register constants */
DECL|macro|DP_CHAIN_4BPP
mdefine_line|#define DP_CHAIN_4BPP&t;&t;0x8888
DECL|macro|DP_CHAIN_7BPP
mdefine_line|#define DP_CHAIN_7BPP&t;&t;0xD2D2
DECL|macro|DP_CHAIN_8BPP
mdefine_line|#define DP_CHAIN_8BPP&t;&t;0x8080
DECL|macro|DP_CHAIN_8BPP_RGB
mdefine_line|#define DP_CHAIN_8BPP_RGB&t;0x9292
DECL|macro|DP_CHAIN_15BPP
mdefine_line|#define DP_CHAIN_15BPP&t;&t;0x4210
DECL|macro|DP_CHAIN_16BPP
mdefine_line|#define DP_CHAIN_16BPP&t;&t;0x8410
DECL|macro|DP_CHAIN_24BPP
mdefine_line|#define DP_CHAIN_24BPP&t;&t;0x8080
DECL|macro|DP_CHAIN_32BPP
mdefine_line|#define DP_CHAIN_32BPP&t;&t;0x8080
multiline_comment|/* DP_PIX_WIDTH register constants */
DECL|macro|DST_1BPP
mdefine_line|#define DST_1BPP&t;&t;0
DECL|macro|DST_4BPP
mdefine_line|#define DST_4BPP&t;&t;1
DECL|macro|DST_8BPP
mdefine_line|#define DST_8BPP&t;&t;2
DECL|macro|DST_15BPP
mdefine_line|#define DST_15BPP&t;&t;3
DECL|macro|DST_16BPP
mdefine_line|#define DST_16BPP&t;&t;4
DECL|macro|DST_32BPP
mdefine_line|#define DST_32BPP&t;&t;6
DECL|macro|SRC_1BPP
mdefine_line|#define SRC_1BPP&t;&t;0
DECL|macro|SRC_4BPP
mdefine_line|#define SRC_4BPP&t;&t;0x100
DECL|macro|SRC_8BPP
mdefine_line|#define SRC_8BPP&t;&t;0x200
DECL|macro|SRC_15BPP
mdefine_line|#define SRC_15BPP&t;&t;0x300
DECL|macro|SRC_16BPP
mdefine_line|#define SRC_16BPP&t;&t;0x400
DECL|macro|SRC_32BPP
mdefine_line|#define SRC_32BPP&t;&t;0x600
DECL|macro|HOST_1BPP
mdefine_line|#define HOST_1BPP&t;&t;0
DECL|macro|HOST_4BPP
mdefine_line|#define HOST_4BPP&t;&t;0x10000
DECL|macro|HOST_8BPP
mdefine_line|#define HOST_8BPP&t;&t;0x20000
DECL|macro|HOST_15BPP
mdefine_line|#define HOST_15BPP&t;&t;0x30000
DECL|macro|HOST_16BPP
mdefine_line|#define HOST_16BPP&t;&t;0x40000
DECL|macro|HOST_32BPP
mdefine_line|#define HOST_32BPP&t;&t;0x60000
DECL|macro|BYTE_ORDER_MSB_TO_LSB
mdefine_line|#define BYTE_ORDER_MSB_TO_LSB&t;0
DECL|macro|BYTE_ORDER_LSB_TO_MSB
mdefine_line|#define BYTE_ORDER_LSB_TO_MSB&t;0x1000000
multiline_comment|/* DP_MIX register constants */
DECL|macro|BKGD_MIX_NOT_D
mdefine_line|#define BKGD_MIX_NOT_D&t;&t;&t;0
DECL|macro|BKGD_MIX_ZERO
mdefine_line|#define BKGD_MIX_ZERO&t;&t;&t;1
DECL|macro|BKGD_MIX_ONE
mdefine_line|#define BKGD_MIX_ONE&t;&t;&t;2
DECL|macro|BKGD_MIX_D
mdefine_line|#define BKGD_MIX_D&t;&t;&t;3
DECL|macro|BKGD_MIX_NOT_S
mdefine_line|#define BKGD_MIX_NOT_S&t;&t;&t;4
DECL|macro|BKGD_MIX_D_XOR_S
mdefine_line|#define BKGD_MIX_D_XOR_S&t;&t;5
DECL|macro|BKGD_MIX_NOT_D_XOR_S
mdefine_line|#define BKGD_MIX_NOT_D_XOR_S&t;&t;6
DECL|macro|BKGD_MIX_S
mdefine_line|#define BKGD_MIX_S&t;&t;&t;7
DECL|macro|BKGD_MIX_NOT_D_OR_NOT_S
mdefine_line|#define BKGD_MIX_NOT_D_OR_NOT_S&t;&t;8
DECL|macro|BKGD_MIX_D_OR_NOT_S
mdefine_line|#define BKGD_MIX_D_OR_NOT_S&t;&t;9
DECL|macro|BKGD_MIX_NOT_D_OR_S
mdefine_line|#define BKGD_MIX_NOT_D_OR_S&t;&t;10
DECL|macro|BKGD_MIX_D_OR_S
mdefine_line|#define BKGD_MIX_D_OR_S&t;&t;&t;11
DECL|macro|BKGD_MIX_D_AND_S
mdefine_line|#define BKGD_MIX_D_AND_S&t;&t;12
DECL|macro|BKGD_MIX_NOT_D_AND_S
mdefine_line|#define BKGD_MIX_NOT_D_AND_S&t;&t;13
DECL|macro|BKGD_MIX_D_AND_NOT_S
mdefine_line|#define BKGD_MIX_D_AND_NOT_S&t;&t;14
DECL|macro|BKGD_MIX_NOT_D_AND_NOT_S
mdefine_line|#define BKGD_MIX_NOT_D_AND_NOT_S&t;15
DECL|macro|BKGD_MIX_D_PLUS_S_DIV2
mdefine_line|#define BKGD_MIX_D_PLUS_S_DIV2&t;&t;0x17
DECL|macro|FRGD_MIX_NOT_D
mdefine_line|#define FRGD_MIX_NOT_D&t;&t;&t;0
DECL|macro|FRGD_MIX_ZERO
mdefine_line|#define FRGD_MIX_ZERO&t;&t;&t;0x10000
DECL|macro|FRGD_MIX_ONE
mdefine_line|#define FRGD_MIX_ONE&t;&t;&t;0x20000
DECL|macro|FRGD_MIX_D
mdefine_line|#define FRGD_MIX_D&t;&t;&t;0x30000
DECL|macro|FRGD_MIX_NOT_S
mdefine_line|#define FRGD_MIX_NOT_S&t;&t;&t;0x40000
DECL|macro|FRGD_MIX_D_XOR_S
mdefine_line|#define FRGD_MIX_D_XOR_S&t;&t;0x50000
DECL|macro|FRGD_MIX_NOT_D_XOR_S
mdefine_line|#define FRGD_MIX_NOT_D_XOR_S&t;&t;0x60000
DECL|macro|FRGD_MIX_S
mdefine_line|#define FRGD_MIX_S&t;&t;&t;0x70000
DECL|macro|FRGD_MIX_NOT_D_OR_NOT_S
mdefine_line|#define FRGD_MIX_NOT_D_OR_NOT_S&t;&t;0x80000
DECL|macro|FRGD_MIX_D_OR_NOT_S
mdefine_line|#define FRGD_MIX_D_OR_NOT_S&t;&t;0x90000
DECL|macro|FRGD_MIX_NOT_D_OR_S
mdefine_line|#define FRGD_MIX_NOT_D_OR_S&t;&t;0xa0000
DECL|macro|FRGD_MIX_D_OR_S
mdefine_line|#define FRGD_MIX_D_OR_S&t;&t;&t;0xb0000
DECL|macro|FRGD_MIX_D_AND_S
mdefine_line|#define FRGD_MIX_D_AND_S&t;&t;0xc0000
DECL|macro|FRGD_MIX_NOT_D_AND_S
mdefine_line|#define FRGD_MIX_NOT_D_AND_S&t;&t;0xd0000
DECL|macro|FRGD_MIX_D_AND_NOT_S
mdefine_line|#define FRGD_MIX_D_AND_NOT_S&t;&t;0xe0000
DECL|macro|FRGD_MIX_NOT_D_AND_NOT_S
mdefine_line|#define FRGD_MIX_NOT_D_AND_NOT_S&t;0xf0000
DECL|macro|FRGD_MIX_D_PLUS_S_DIV2
mdefine_line|#define FRGD_MIX_D_PLUS_S_DIV2&t;&t;0x170000
multiline_comment|/* DP_SRC register constants */
DECL|macro|BKGD_SRC_BKGD_CLR
mdefine_line|#define BKGD_SRC_BKGD_CLR&t;0
DECL|macro|BKGD_SRC_FRGD_CLR
mdefine_line|#define BKGD_SRC_FRGD_CLR&t;1
DECL|macro|BKGD_SRC_HOST
mdefine_line|#define BKGD_SRC_HOST&t;&t;2
DECL|macro|BKGD_SRC_BLIT
mdefine_line|#define BKGD_SRC_BLIT&t;&t;3
DECL|macro|BKGD_SRC_PATTERN
mdefine_line|#define BKGD_SRC_PATTERN&t;4
DECL|macro|FRGD_SRC_BKGD_CLR
mdefine_line|#define FRGD_SRC_BKGD_CLR&t;0
DECL|macro|FRGD_SRC_FRGD_CLR
mdefine_line|#define FRGD_SRC_FRGD_CLR&t;0x100
DECL|macro|FRGD_SRC_HOST
mdefine_line|#define FRGD_SRC_HOST&t;&t;0x200
DECL|macro|FRGD_SRC_BLIT
mdefine_line|#define FRGD_SRC_BLIT&t;&t;0x300
DECL|macro|FRGD_SRC_PATTERN
mdefine_line|#define FRGD_SRC_PATTERN&t;0x400
DECL|macro|MONO_SRC_ONE
mdefine_line|#define MONO_SRC_ONE&t;&t;0
DECL|macro|MONO_SRC_PATTERN
mdefine_line|#define MONO_SRC_PATTERN&t;0x10000
DECL|macro|MONO_SRC_HOST
mdefine_line|#define MONO_SRC_HOST&t;&t;0x20000
DECL|macro|MONO_SRC_BLIT
mdefine_line|#define MONO_SRC_BLIT&t;&t;0x30000
multiline_comment|/* CLR_CMP_CNTL register constants */
DECL|macro|COMPARE_FALSE
mdefine_line|#define COMPARE_FALSE&t;&t;0
DECL|macro|COMPARE_TRUE
mdefine_line|#define COMPARE_TRUE&t;&t;1
DECL|macro|COMPARE_NOT_EQUAL
mdefine_line|#define COMPARE_NOT_EQUAL&t;4
DECL|macro|COMPARE_EQUAL
mdefine_line|#define COMPARE_EQUAL&t;&t;5
DECL|macro|COMPARE_DESTINATION
mdefine_line|#define COMPARE_DESTINATION&t;0
DECL|macro|COMPARE_SOURCE
mdefine_line|#define COMPARE_SOURCE&t;&t;0x1000000
multiline_comment|/* FIFO_STAT register constants */
DECL|macro|FIFO_ERR
mdefine_line|#define FIFO_ERR&t;&t;0x80000000
multiline_comment|/* CONTEXT_LOAD_CNTL constants */
DECL|macro|CONTEXT_NO_LOAD
mdefine_line|#define CONTEXT_NO_LOAD&t;&t;&t;0
DECL|macro|CONTEXT_LOAD
mdefine_line|#define CONTEXT_LOAD&t;&t;&t;0x10000
DECL|macro|CONTEXT_LOAD_AND_DO_FILL
mdefine_line|#define CONTEXT_LOAD_AND_DO_FILL&t;0x20000
DECL|macro|CONTEXT_LOAD_AND_DO_LINE
mdefine_line|#define CONTEXT_LOAD_AND_DO_LINE&t;0x30000
DECL|macro|CONTEXT_EXECUTE
mdefine_line|#define CONTEXT_EXECUTE&t;&t;&t;0
DECL|macro|CONTEXT_CMD_DISABLE
mdefine_line|#define CONTEXT_CMD_DISABLE&t;&t;0x80000000
multiline_comment|/* GUI_STAT register constants */
DECL|macro|ENGINE_IDLE
mdefine_line|#define ENGINE_IDLE&t;&t;0
DECL|macro|ENGINE_BUSY
mdefine_line|#define ENGINE_BUSY&t;&t;1
DECL|macro|SCISSOR_LEFT_FLAG
mdefine_line|#define SCISSOR_LEFT_FLAG&t;0x10
DECL|macro|SCISSOR_RIGHT_FLAG
mdefine_line|#define SCISSOR_RIGHT_FLAG&t;0x20
DECL|macro|SCISSOR_TOP_FLAG
mdefine_line|#define SCISSOR_TOP_FLAG&t;0x40
DECL|macro|SCISSOR_BOTTOM_FLAG
mdefine_line|#define SCISSOR_BOTTOM_FLAG&t;0x80
multiline_comment|/* ATI VGA Extended Regsiters */
DECL|macro|sioATIEXT
mdefine_line|#define sioATIEXT&t;&t;0x1ce
DECL|macro|bioATIEXT
mdefine_line|#define bioATIEXT&t;&t;0x3ce
DECL|macro|ATI2E
mdefine_line|#define ATI2E&t;&t;&t;0xae
DECL|macro|ATI32
mdefine_line|#define ATI32&t;&t;&t;0xb2
DECL|macro|ATI36
mdefine_line|#define ATI36&t;&t;&t;0xb6
multiline_comment|/* VGA Graphics Controller Registers */
DECL|macro|VGAGRA
mdefine_line|#define VGAGRA&t;&t;&t;0x3ce
DECL|macro|GRA06
mdefine_line|#define GRA06&t;&t;&t;0x06
multiline_comment|/* VGA Seququencer Registers */
DECL|macro|VGASEQ
mdefine_line|#define VGASEQ&t;&t;&t;0x3c4
DECL|macro|SEQ02
mdefine_line|#define SEQ02&t;&t;&t;0x02
DECL|macro|SEQ04
mdefine_line|#define SEQ04&t;&t;&t;0x04
DECL|macro|MACH64_MAX_X
mdefine_line|#define MACH64_MAX_X&t;&t;ENGINE_MAX_X
DECL|macro|MACH64_MAX_Y
mdefine_line|#define MACH64_MAX_Y&t;&t;ENGINE_MAX_Y
DECL|macro|INC_X
mdefine_line|#define INC_X&t;&t;&t;0x0020
DECL|macro|INC_Y
mdefine_line|#define INC_Y&t;&t;&t;0x0080
DECL|macro|RGB16_555
mdefine_line|#define RGB16_555&t;&t;0x0000
DECL|macro|RGB16_565
mdefine_line|#define RGB16_565&t;&t;0x0040
DECL|macro|RGB16_655
mdefine_line|#define RGB16_655&t;&t;0x0080
DECL|macro|RGB16_664
mdefine_line|#define RGB16_664&t;&t;0x00c0
DECL|macro|POLY_TEXT_TYPE
mdefine_line|#define POLY_TEXT_TYPE&t;&t;0x0001
DECL|macro|IMAGE_TEXT_TYPE
mdefine_line|#define IMAGE_TEXT_TYPE&t;&t;0x0002
DECL|macro|TEXT_TYPE_8_BIT
mdefine_line|#define TEXT_TYPE_8_BIT&t;&t;0x0004
DECL|macro|TEXT_TYPE_16_BIT
mdefine_line|#define TEXT_TYPE_16_BIT&t;0x0008
DECL|macro|POLY_TEXT_TYPE_8
mdefine_line|#define POLY_TEXT_TYPE_8&t;(POLY_TEXT_TYPE | TEXT_TYPE_8_BIT)
DECL|macro|IMAGE_TEXT_TYPE_8
mdefine_line|#define IMAGE_TEXT_TYPE_8&t;(IMAGE_TEXT_TYPE | TEXT_TYPE_8_BIT)
DECL|macro|POLY_TEXT_TYPE_16
mdefine_line|#define POLY_TEXT_TYPE_16&t;(POLY_TEXT_TYPE | TEXT_TYPE_16_BIT)
DECL|macro|IMAGE_TEXT_TYPE_16
mdefine_line|#define IMAGE_TEXT_TYPE_16&t;(IMAGE_TEXT_TYPE | TEXT_TYPE_16_BIT)
DECL|macro|MACH64_NUM_CLOCKS
mdefine_line|#define MACH64_NUM_CLOCKS&t;16
DECL|macro|MACH64_NUM_FREQS
mdefine_line|#define MACH64_NUM_FREQS&t;50
multiline_comment|/* Power Management register constants (LT &amp; LT Pro) */
DECL|macro|PWR_MGT_ON
mdefine_line|#define PWR_MGT_ON&t;&t;0x00000001
DECL|macro|PWR_MGT_MODE_MASK
mdefine_line|#define PWR_MGT_MODE_MASK&t;0x00000006
DECL|macro|AUTO_PWR_UP
mdefine_line|#define AUTO_PWR_UP&t;&t;0x00000008
DECL|macro|USE_F32KHZ
mdefine_line|#define USE_F32KHZ&t;&t;0x00000400
DECL|macro|TRISTATE_MEM_EN
mdefine_line|#define TRISTATE_MEM_EN&t;&t;0x00000800
DECL|macro|SELF_REFRESH
mdefine_line|#define SELF_REFRESH&t;&t;0x00000080
DECL|macro|PWR_BLON
mdefine_line|#define PWR_BLON&t;&t;0x02000000
DECL|macro|STANDBY_NOW
mdefine_line|#define STANDBY_NOW&t;&t;0x10000000
DECL|macro|SUSPEND_NOW
mdefine_line|#define SUSPEND_NOW&t;&t;0x20000000
DECL|macro|PWR_MGT_STATUS_MASK
mdefine_line|#define PWR_MGT_STATUS_MASK&t;0xC0000000
DECL|macro|PWR_MGT_STATUS_SUSPEND
mdefine_line|#define PWR_MGT_STATUS_SUSPEND&t;0x80000000
multiline_comment|/* PM Mode constants  */
DECL|macro|PWR_MGT_MODE_PIN
mdefine_line|#define PWR_MGT_MODE_PIN&t;0x00000000
DECL|macro|PWR_MGT_MODE_REG
mdefine_line|#define PWR_MGT_MODE_REG&t;0x00000002
DECL|macro|PWR_MGT_MODE_TIMER
mdefine_line|#define PWR_MGT_MODE_TIMER&t;0x00000004
DECL|macro|PWR_MGT_MODE_PCI
mdefine_line|#define PWR_MGT_MODE_PCI&t;0x00000006
multiline_comment|/* LCD registers (LT Pro) */
multiline_comment|/* LCD Index register */
DECL|macro|LCD_INDEX_MASK
mdefine_line|#define LCD_INDEX_MASK&t;&t;0x0000003F
DECL|macro|LCD_DISPLAY_DIS
mdefine_line|#define LCD_DISPLAY_DIS&t;&t;0x00000100
DECL|macro|LCD_SRC_SEL
mdefine_line|#define LCD_SRC_SEL&t;&t;0x00000200
DECL|macro|CRTC2_DISPLAY_DIS
mdefine_line|#define CRTC2_DISPLAY_DIS&t;0x00000400
multiline_comment|/* LCD register indices */
DECL|macro|CONFIG_PANEL
mdefine_line|#define CONFIG_PANEL&t;&t;0x00
DECL|macro|LCD_GEN_CTRL
mdefine_line|#define LCD_GEN_CTRL&t;&t;0x01
DECL|macro|DSTN_CONTROL
mdefine_line|#define DSTN_CONTROL&t;&t;0x02
DECL|macro|HFB_PITCH_ADDR
mdefine_line|#define HFB_PITCH_ADDR&t;&t;0x03
DECL|macro|HORZ_STRETCHING
mdefine_line|#define HORZ_STRETCHING&t;&t;0x04
DECL|macro|VERT_STRETCHING
mdefine_line|#define VERT_STRETCHING&t;&t;0x05
DECL|macro|EXT_VERT_STRETCH
mdefine_line|#define EXT_VERT_STRETCH&t;0x06
DECL|macro|LT_GIO
mdefine_line|#define LT_GIO&t;&t;&t;0x07
DECL|macro|POWER_MANAGEMENT
mdefine_line|#define POWER_MANAGEMENT&t;0x08
DECL|macro|ZVGPIO
mdefine_line|#define ZVGPIO&t;&t;&t;0x09
DECL|macro|ICON_CLR0
mdefine_line|#define ICON_CLR0&t;&t;0x0A
DECL|macro|ICON_CLR1
mdefine_line|#define ICON_CLR1&t;&t;0x0B
DECL|macro|ICON_OFFSET
mdefine_line|#define ICON_OFFSET&t;&t;0x0C
DECL|macro|ICON_HORZ_VERT_POSN
mdefine_line|#define ICON_HORZ_VERT_POSN&t;0x0D
DECL|macro|ICON_HORZ_VERT_OFF
mdefine_line|#define ICON_HORZ_VERT_OFF&t;0x0E
DECL|macro|ICON2_CLR0
mdefine_line|#define ICON2_CLR0&t;&t;0x0F
DECL|macro|ICON2_CLR1
mdefine_line|#define ICON2_CLR1&t;&t;0x10
DECL|macro|ICON2_OFFSET
mdefine_line|#define ICON2_OFFSET&t;&t;0x11
DECL|macro|ICON2_HORZ_VERT_POSN
mdefine_line|#define ICON2_HORZ_VERT_POSN&t;0x12
DECL|macro|ICON2_HORZ_VERT_OFF
mdefine_line|#define ICON2_HORZ_VERT_OFF&t;0x13
DECL|macro|LCD_MISC_CNTL
mdefine_line|#define LCD_MISC_CNTL&t;&t;0x14
DECL|macro|APC_CNTL
mdefine_line|#define APC_CNTL&t;&t;0x1C
DECL|macro|POWER_MANAGEMENT_2
mdefine_line|#define POWER_MANAGEMENT_2&t;0x1D
DECL|macro|ALPHA_BLENDING
mdefine_line|#define ALPHA_BLENDING&t;&t;0x25
DECL|macro|PORTRAIT_GEN_CNTL
mdefine_line|#define PORTRAIT_GEN_CNTL&t;0x26
DECL|macro|APC_CTRL_IO
mdefine_line|#define APC_CTRL_IO&t;&t;0x27
DECL|macro|TEST_IO
mdefine_line|#define TEST_IO&t;&t;&t;0x28
DECL|macro|TEST_OUTPUTS
mdefine_line|#define TEST_OUTPUTS&t;&t;0x29
DECL|macro|DP1_MEM_ACCESS
mdefine_line|#define DP1_MEM_ACCESS&t;&t;0x2A
DECL|macro|DP0_MEM_ACCESS
mdefine_line|#define DP0_MEM_ACCESS&t;&t;0x2B
DECL|macro|DP0_DEBUG_A
mdefine_line|#define DP0_DEBUG_A&t;&t;0x2C
DECL|macro|DP0_DEBUG_B
mdefine_line|#define DP0_DEBUG_B&t;&t;0x2D
DECL|macro|DP1_DEBUG_A
mdefine_line|#define DP1_DEBUG_A&t;&t;0x2E
DECL|macro|DP1_DEBUG_B
mdefine_line|#define DP1_DEBUG_B&t;&t;0x2F
DECL|macro|DPCTRL_DEBUG_A
mdefine_line|#define DPCTRL_DEBUG_A&t;&t;0x30
DECL|macro|DPCTRL_DEBUG_B
mdefine_line|#define DPCTRL_DEBUG_B&t;&t;0x31
DECL|macro|MEMBLK_DEBUG
mdefine_line|#define MEMBLK_DEBUG&t;&t;0x32
DECL|macro|APC_LUT_AB
mdefine_line|#define APC_LUT_AB&t;&t;0x33
DECL|macro|APC_LUT_CD
mdefine_line|#define APC_LUT_CD&t;&t;0x34
DECL|macro|APC_LUT_EF
mdefine_line|#define APC_LUT_EF&t;&t;0x35
DECL|macro|APC_LUT_GH
mdefine_line|#define APC_LUT_GH&t;&t;0x36
DECL|macro|APC_LUT_IJ
mdefine_line|#define APC_LUT_IJ&t;&t;0x37
DECL|macro|APC_LUT_KL
mdefine_line|#define APC_LUT_KL&t;&t;0x38
DECL|macro|APC_LUT_MN
mdefine_line|#define APC_LUT_MN&t;&t;0x39
DECL|macro|APC_LUT_OP
mdefine_line|#define APC_LUT_OP&t;&t;0x3A
multiline_comment|/* Values in LCD_MISC_CNTL */
DECL|macro|BIAS_MOD_LEVEL_MASK
mdefine_line|#define BIAS_MOD_LEVEL_MASK&t;0x0000ff00
DECL|macro|BIAS_MOD_LEVEL_SHIFT
mdefine_line|#define BIAS_MOD_LEVEL_SHIFT&t;8
DECL|macro|BLMOD_EN
mdefine_line|#define BLMOD_EN&t;&t;0x00010000
DECL|macro|BIASMOD_EN
mdefine_line|#define BIASMOD_EN&t;&t;0x00020000
macro_line|#endif /* REGMACH64_H */
eof
