multiline_comment|/*&n; * drivers/video/geode/display_gx1.h&n; *   -- Geode GX1 display controller&n; *&n; * Copyright (C) 2005 Arcom Control Systems Ltd.&n; *&n; * Based on AMD&squot;s original 2.4 driver:&n; *   Copyright (C) 2004 Advanced Micro Devices, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#ifndef __DISPLAY_GX1_H__
DECL|macro|__DISPLAY_GX1_H__
mdefine_line|#define __DISPLAY_GX1_H__
r_int
id|gx1_gx_base
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|gx1_frame_buffer_size
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|geode_dc_ops
id|gx1_dc_ops
suffix:semicolon
multiline_comment|/* GX1 configuration I/O registers */
DECL|macro|CONFIG_CCR3
mdefine_line|#define CONFIG_CCR3 0xc3
DECL|macro|CONFIG_CCR3_MAPEN
macro_line|#  define CONFIG_CCR3_MAPEN 0x10
DECL|macro|CONFIG_GCR
mdefine_line|#define CONFIG_GCR  0xb8
multiline_comment|/* Memory controller registers */
DECL|macro|MC_BANK_CFG
mdefine_line|#define MC_BANK_CFG&t;&t;0x08
DECL|macro|MC_BCFG_DIMM0_SZ_MASK
macro_line|#  define MC_BCFG_DIMM0_SZ_MASK&t;&t;0x00000700
DECL|macro|MC_BCFG_DIMM0_PG_SZ_MASK
macro_line|#  define MC_BCFG_DIMM0_PG_SZ_MASK&t;0x00000070
DECL|macro|MC_BCFG_DIMM0_PG_SZ_NO_DIMM
macro_line|#  define MC_BCFG_DIMM0_PG_SZ_NO_DIMM&t;0x00000070
DECL|macro|MC_GBASE_ADD
mdefine_line|#define MC_GBASE_ADD&t;&t;0x14
DECL|macro|MC_GADD_GBADD_MASK
macro_line|#  define MC_GADD_GBADD_MASK&t;&t;0x000003ff
multiline_comment|/* Display controller registers */
DECL|macro|DC_PAL_ADDRESS
mdefine_line|#define DC_PAL_ADDRESS&t;&t;0x70
DECL|macro|DC_PAL_DATA
mdefine_line|#define DC_PAL_DATA&t;&t;0x74
DECL|macro|DC_UNLOCK
mdefine_line|#define DC_UNLOCK&t;&t;0x00
DECL|macro|DC_UNLOCK_CODE
macro_line|#  define DC_UNLOCK_CODE&t;&t;0x00004758
DECL|macro|DC_GENERAL_CFG
mdefine_line|#define DC_GENERAL_CFG&t;&t;0x04
DECL|macro|DC_GCFG_DFLE
macro_line|#  define DC_GCFG_DFLE&t;&t;&t;0x00000001
DECL|macro|DC_GCFG_CURE
macro_line|#  define DC_GCFG_CURE&t;&t;&t;0x00000002
DECL|macro|DC_GCFG_VCLK_DIV
macro_line|#  define DC_GCFG_VCLK_DIV&t;&t;0x00000004
DECL|macro|DC_GCFG_PLNO
macro_line|#  define DC_GCFG_PLNO&t;&t;&t;0x00000004
DECL|macro|DC_GCFG_PPC
macro_line|#  define DC_GCFG_PPC&t;&t;&t;0x00000008
DECL|macro|DC_GCFG_CMPE
macro_line|#  define DC_GCFG_CMPE&t;&t;&t;0x00000010
DECL|macro|DC_GCFG_DECE
macro_line|#  define DC_GCFG_DECE&t;&t;&t;0x00000020
DECL|macro|DC_GCFG_DCLK_MASK
macro_line|#  define DC_GCFG_DCLK_MASK&t;&t;0x000000C0
DECL|macro|DC_GCFG_DCLK_DIV_1
macro_line|#  define DC_GCFG_DCLK_DIV_1&t;&t;0x00000080
DECL|macro|DC_GCFG_DFHPSL_MASK
macro_line|#  define DC_GCFG_DFHPSL_MASK&t;&t;0x00000F00
DECL|macro|DC_GCFG_DFHPSL_POS
macro_line|#  define DC_GCFG_DFHPSL_POS&t;&t;&t; 8
DECL|macro|DC_GCFG_DFHPEL_MASK
macro_line|#  define DC_GCFG_DFHPEL_MASK&t;&t;0x0000F000
DECL|macro|DC_GCFG_DFHPEL_POS
macro_line|#  define DC_GCFG_DFHPEL_POS&t;&t;&t;12
DECL|macro|DC_GCFG_CIM_MASK
macro_line|#  define DC_GCFG_CIM_MASK&t;&t;0x00030000
DECL|macro|DC_GCFG_CIM_POS
macro_line|#  define DC_GCFG_CIM_POS&t;&t;&t;16
DECL|macro|DC_GCFG_FDTY
macro_line|#  define DC_GCFG_FDTY&t;&t;&t;0x00040000
DECL|macro|DC_GCFG_RTPM
macro_line|#  define DC_GCFG_RTPM&t;&t;&t;0x00080000
DECL|macro|DC_GCFG_DAC_RS_MASK
macro_line|#  define DC_GCFG_DAC_RS_MASK&t;&t;0x00700000
DECL|macro|DC_GCFG_DAC_RS_POS
macro_line|#  define DC_GCFG_DAC_RS_POS&t;&t;&t;20
DECL|macro|DC_GCFG_CKWR
macro_line|#  define DC_GCFG_CKWR&t;&t;&t;0x00800000
DECL|macro|DC_GCFG_LDBL
macro_line|#  define DC_GCFG_LDBL&t;&t;&t;0x01000000
DECL|macro|DC_GCFG_DIAG
macro_line|#  define DC_GCFG_DIAG&t;&t;&t;0x02000000
DECL|macro|DC_GCFG_CH4S
macro_line|#  define DC_GCFG_CH4S&t;&t;&t;0x04000000
DECL|macro|DC_GCFG_SSLC
macro_line|#  define DC_GCFG_SSLC&t;&t;&t;0x08000000
DECL|macro|DC_GCFG_VIDE
macro_line|#  define DC_GCFG_VIDE&t;&t;&t;0x10000000
DECL|macro|DC_GCFG_VRDY
macro_line|#  define DC_GCFG_VRDY&t;&t;&t;0x20000000
DECL|macro|DC_GCFG_DPCK
macro_line|#  define DC_GCFG_DPCK&t;&t;&t;0x40000000
DECL|macro|DC_GCFG_DDCK
macro_line|#  define DC_GCFG_DDCK&t;&t;&t;0x80000000
DECL|macro|DC_TIMING_CFG
mdefine_line|#define DC_TIMING_CFG&t;&t;0x08
DECL|macro|DC_TCFG_FPPE
macro_line|#  define DC_TCFG_FPPE&t;&t;&t;0x00000001
DECL|macro|DC_TCFG_HSYE
macro_line|#  define DC_TCFG_HSYE&t;&t;&t;0x00000002
DECL|macro|DC_TCFG_VSYE
macro_line|#  define DC_TCFG_VSYE&t;&t;&t;0x00000004
DECL|macro|DC_TCFG_BLKE
macro_line|#  define DC_TCFG_BLKE&t;&t;&t;0x00000008
DECL|macro|DC_TCFG_DDCK
macro_line|#  define DC_TCFG_DDCK&t;&t;&t;0x00000010
DECL|macro|DC_TCFG_TGEN
macro_line|#  define DC_TCFG_TGEN&t;&t;&t;0x00000020
DECL|macro|DC_TCFG_VIEN
macro_line|#  define DC_TCFG_VIEN&t;&t;&t;0x00000040
DECL|macro|DC_TCFG_BLNK
macro_line|#  define DC_TCFG_BLNK&t;&t;&t;0x00000080
DECL|macro|DC_TCFG_CHSP
macro_line|#  define DC_TCFG_CHSP&t;&t;&t;0x00000100
DECL|macro|DC_TCFG_CVSP
macro_line|#  define DC_TCFG_CVSP&t;&t;&t;0x00000200
DECL|macro|DC_TCFG_FHSP
macro_line|#  define DC_TCFG_FHSP&t;&t;&t;0x00000400
DECL|macro|DC_TCFG_FVSP
macro_line|#  define DC_TCFG_FVSP&t;&t;&t;0x00000800
DECL|macro|DC_TCFG_FCEN
macro_line|#  define DC_TCFG_FCEN&t;&t;&t;0x00001000
DECL|macro|DC_TCFG_CDCE
macro_line|#  define DC_TCFG_CDCE&t;&t;&t;0x00002000
DECL|macro|DC_TCFG_PLNR
macro_line|#  define DC_TCFG_PLNR&t;&t;&t;0x00002000
DECL|macro|DC_TCFG_INTL
macro_line|#  define DC_TCFG_INTL&t;&t;&t;0x00004000
DECL|macro|DC_TCFG_PXDB
macro_line|#  define DC_TCFG_PXDB&t;&t;&t;0x00008000
DECL|macro|DC_TCFG_BKRT
macro_line|#  define DC_TCFG_BKRT&t;&t;&t;0x00010000
DECL|macro|DC_TCFG_PSD_MASK
macro_line|#  define DC_TCFG_PSD_MASK&t;&t;0x000E0000
DECL|macro|DC_TCFG_PSD_POS
macro_line|#  define DC_TCFG_PSD_POS&t;&t;&t;17
DECL|macro|DC_TCFG_DDCI
macro_line|#  define DC_TCFG_DDCI&t;&t;&t;0x08000000
DECL|macro|DC_TCFG_SENS
macro_line|#  define DC_TCFG_SENS&t;&t;&t;0x10000000
DECL|macro|DC_TCFG_DNA
macro_line|#  define DC_TCFG_DNA&t;&t;&t;0x20000000
DECL|macro|DC_TCFG_VNA
macro_line|#  define DC_TCFG_VNA&t;&t;&t;0x40000000
DECL|macro|DC_TCFG_VINT
macro_line|#  define DC_TCFG_VINT&t;&t;&t;0x80000000
DECL|macro|DC_OUTPUT_CFG
mdefine_line|#define DC_OUTPUT_CFG&t;&t;0x0C
DECL|macro|DC_OCFG_8BPP
macro_line|#  define DC_OCFG_8BPP&t;&t;&t;0x00000001
DECL|macro|DC_OCFG_555
macro_line|#  define DC_OCFG_555&t;&t;&t;0x00000002
DECL|macro|DC_OCFG_PCKE
macro_line|#  define DC_OCFG_PCKE&t;&t;&t;0x00000004
DECL|macro|DC_OCFG_FRME
macro_line|#  define DC_OCFG_FRME&t;&t;&t;0x00000008
DECL|macro|DC_OCFG_DITE
macro_line|#  define DC_OCFG_DITE&t;&t;&t;0x00000010
DECL|macro|DC_OCFG_2PXE
macro_line|#  define DC_OCFG_2PXE&t;&t;&t;0x00000020
DECL|macro|DC_OCFG_2XCK
macro_line|#  define DC_OCFG_2XCK&t;&t;&t;0x00000040
DECL|macro|DC_OCFG_2IND
macro_line|#  define DC_OCFG_2IND&t;&t;&t;0x00000080
DECL|macro|DC_OCFG_34ADD
macro_line|#  define DC_OCFG_34ADD&t;&t;&t;0x00000100
DECL|macro|DC_OCFG_FRMS
macro_line|#  define DC_OCFG_FRMS&t;&t;&t;0x00000200
DECL|macro|DC_OCFG_CKSL
macro_line|#  define DC_OCFG_CKSL&t;&t;&t;0x00000400
DECL|macro|DC_OCFG_PRMP
macro_line|#  define DC_OCFG_PRMP&t;&t;&t;0x00000800
DECL|macro|DC_OCFG_PDEL
macro_line|#  define DC_OCFG_PDEL&t;&t;&t;0x00001000
DECL|macro|DC_OCFG_PDEH
macro_line|#  define DC_OCFG_PDEH&t;&t;&t;0x00002000
DECL|macro|DC_OCFG_CFRW
macro_line|#  define DC_OCFG_CFRW&t;&t;&t;0x00004000
DECL|macro|DC_OCFG_DIAG
macro_line|#  define DC_OCFG_DIAG&t;&t;&t;0x00008000
DECL|macro|DC_FB_ST_OFFSET
mdefine_line|#define DC_FB_ST_OFFSET&t;&t;0x10
DECL|macro|DC_CB_ST_OFFSET
mdefine_line|#define DC_CB_ST_OFFSET&t;&t;0x14
DECL|macro|DC_CURS_ST_OFFSET
mdefine_line|#define DC_CURS_ST_OFFSET&t;0x18
DECL|macro|DC_ICON_ST_OFFSET
mdefine_line|#define DC_ICON_ST_OFFSET&t;0x1C
DECL|macro|DC_VID_ST_OFFSET
mdefine_line|#define DC_VID_ST_OFFSET&t;0x20
DECL|macro|DC_LINE_DELTA
mdefine_line|#define DC_LINE_DELTA&t;&t;0x24
DECL|macro|DC_BUF_SIZE
mdefine_line|#define DC_BUF_SIZE&t;&t;0x28
DECL|macro|DC_H_TIMING_1
mdefine_line|#define DC_H_TIMING_1&t;&t;0x30
DECL|macro|DC_H_TIMING_2
mdefine_line|#define DC_H_TIMING_2&t;&t;0x34
DECL|macro|DC_H_TIMING_3
mdefine_line|#define DC_H_TIMING_3&t;&t;0x38
DECL|macro|DC_FP_H_TIMING
mdefine_line|#define DC_FP_H_TIMING&t;&t;0x3C
DECL|macro|DC_V_TIMING_1
mdefine_line|#define DC_V_TIMING_1&t;&t;0x40
DECL|macro|DC_V_TIMING_2
mdefine_line|#define DC_V_TIMING_2&t;&t;0x44
DECL|macro|DC_V_TIMING_3
mdefine_line|#define DC_V_TIMING_3&t;&t;0x48
DECL|macro|DC_FP_V_TIMING
mdefine_line|#define DC_FP_V_TIMING&t;&t;0x4C
DECL|macro|DC_CURSOR_X
mdefine_line|#define DC_CURSOR_X&t;&t;0x50
DECL|macro|DC_ICON_X
mdefine_line|#define DC_ICON_X&t;&t;0x54
DECL|macro|DC_V_LINE_CNT
mdefine_line|#define DC_V_LINE_CNT&t;&t;0x54
DECL|macro|DC_CURSOR_Y
mdefine_line|#define DC_CURSOR_Y&t;&t;0x58
DECL|macro|DC_ICON_Y
mdefine_line|#define DC_ICON_Y&t;&t;0x5C
DECL|macro|DC_SS_LINE_CMP
mdefine_line|#define DC_SS_LINE_CMP&t;&t;0x5C
DECL|macro|DC_CURSOR_COLOR
mdefine_line|#define DC_CURSOR_COLOR&t;&t;0x60
DECL|macro|DC_ICON_COLOR
mdefine_line|#define DC_ICON_COLOR&t;&t;0x64
DECL|macro|DC_BORDER_COLOR
mdefine_line|#define DC_BORDER_COLOR&t;&t;0x68
DECL|macro|DC_PAL_ADDRESS
mdefine_line|#define DC_PAL_ADDRESS&t;&t;0x70
DECL|macro|DC_PAL_DATA
mdefine_line|#define DC_PAL_DATA&t;&t;0x74
DECL|macro|DC_DFIFO_DIAG
mdefine_line|#define DC_DFIFO_DIAG&t;&t;0x78
DECL|macro|DC_CFIFO_DIAG
mdefine_line|#define DC_CFIFO_DIAG&t;&t;0x7C
macro_line|#endif /* !__DISPLAY_GX1_H__ */
eof
