macro_line|#ifndef _INTELFBHW_H
DECL|macro|_INTELFBHW_H
mdefine_line|#define _INTELFBHW_H
multiline_comment|/* $DHD: intelfb/intelfbhw.h,v 1.5 2003/06/27 15:06:25 dawes Exp $ */
multiline_comment|/*** HW-specific data ***/
multiline_comment|/* Information about the 852GM/855GM variants */
DECL|macro|INTEL_85X_CAPID
mdefine_line|#define INTEL_85X_CAPID&t;&t;0x44
DECL|macro|INTEL_85X_VARIANT_MASK
mdefine_line|#define INTEL_85X_VARIANT_MASK&t;&t;0x7
DECL|macro|INTEL_85X_VARIANT_SHIFT
mdefine_line|#define INTEL_85X_VARIANT_SHIFT&t;&t;5
DECL|macro|INTEL_VAR_855GME
mdefine_line|#define INTEL_VAR_855GME&t;&t;0x0
DECL|macro|INTEL_VAR_855GM
mdefine_line|#define INTEL_VAR_855GM&t;&t;&t;0x4
DECL|macro|INTEL_VAR_852GME
mdefine_line|#define INTEL_VAR_852GME&t;&t;0x2
DECL|macro|INTEL_VAR_852GM
mdefine_line|#define INTEL_VAR_852GM&t;&t;&t;0x5
multiline_comment|/* Information about DVO/LVDS Ports */
DECL|macro|DVOA_PORT
mdefine_line|#define DVOA_PORT  0x1
DECL|macro|DVOB_PORT
mdefine_line|#define DVOB_PORT  0x2
DECL|macro|DVOC_PORT
mdefine_line|#define DVOC_PORT  0x4
DECL|macro|LVDS_PORT
mdefine_line|#define LVDS_PORT  0x8
multiline_comment|/*&n; * The Bridge device&squot;s PCI config space has information about the&n; * fb aperture size and the amount of pre-reserved memory.&n; */
DECL|macro|INTEL_GMCH_CTRL
mdefine_line|#define INTEL_GMCH_CTRL&t;&t;0x52
DECL|macro|INTEL_GMCH_ENABLED
mdefine_line|#define INTEL_GMCH_ENABLED&t;&t;0x4
DECL|macro|INTEL_GMCH_MEM_MASK
mdefine_line|#define INTEL_GMCH_MEM_MASK&t;&t;0x1
DECL|macro|INTEL_GMCH_MEM_64M
mdefine_line|#define INTEL_GMCH_MEM_64M&t;&t;0x1
DECL|macro|INTEL_GMCH_MEM_128M
mdefine_line|#define INTEL_GMCH_MEM_128M&t;&t;0
DECL|macro|INTEL_830_GMCH_GMS_MASK
mdefine_line|#define INTEL_830_GMCH_GMS_MASK&t;&t;(0x7 &lt;&lt; 4)
DECL|macro|INTEL_830_GMCH_GMS_DISABLED
mdefine_line|#define INTEL_830_GMCH_GMS_DISABLED&t;(0x0 &lt;&lt; 4)
DECL|macro|INTEL_830_GMCH_GMS_LOCAL
mdefine_line|#define INTEL_830_GMCH_GMS_LOCAL&t;(0x1 &lt;&lt; 4)
DECL|macro|INTEL_830_GMCH_GMS_STOLEN_512
mdefine_line|#define INTEL_830_GMCH_GMS_STOLEN_512&t;(0x2 &lt;&lt; 4)
DECL|macro|INTEL_830_GMCH_GMS_STOLEN_1024
mdefine_line|#define INTEL_830_GMCH_GMS_STOLEN_1024&t;(0x3 &lt;&lt; 4)
DECL|macro|INTEL_830_GMCH_GMS_STOLEN_8192
mdefine_line|#define INTEL_830_GMCH_GMS_STOLEN_8192&t;(0x4 &lt;&lt; 4)
DECL|macro|INTEL_855_GMCH_GMS_MASK
mdefine_line|#define INTEL_855_GMCH_GMS_MASK&t;&t;(0x7 &lt;&lt; 4)
DECL|macro|INTEL_855_GMCH_GMS_DISABLED
mdefine_line|#define INTEL_855_GMCH_GMS_DISABLED&t;(0x0 &lt;&lt; 4)
DECL|macro|INTEL_855_GMCH_GMS_STOLEN_1M
mdefine_line|#define INTEL_855_GMCH_GMS_STOLEN_1M&t;(0x1 &lt;&lt; 4)
DECL|macro|INTEL_855_GMCH_GMS_STOLEN_4M
mdefine_line|#define INTEL_855_GMCH_GMS_STOLEN_4M&t;(0x2 &lt;&lt; 4)
DECL|macro|INTEL_855_GMCH_GMS_STOLEN_8M
mdefine_line|#define INTEL_855_GMCH_GMS_STOLEN_8M&t;(0x3 &lt;&lt; 4)
DECL|macro|INTEL_855_GMCH_GMS_STOLEN_16M
mdefine_line|#define INTEL_855_GMCH_GMS_STOLEN_16M&t;(0x4 &lt;&lt; 4)
DECL|macro|INTEL_855_GMCH_GMS_STOLEN_32M
mdefine_line|#define INTEL_855_GMCH_GMS_STOLEN_32M&t;(0x5 &lt;&lt; 4)
multiline_comment|/* HW registers */
multiline_comment|/* Fence registers */
DECL|macro|FENCE
mdefine_line|#define FENCE&t;&t;&t;0x2000
DECL|macro|FENCE_NUM
mdefine_line|#define FENCE_NUM&t;&t;&t;8
multiline_comment|/* Primary ring buffer */
DECL|macro|PRI_RING_TAIL
mdefine_line|#define PRI_RING_TAIL&t;&t;0x2030
DECL|macro|RING_TAIL_MASK
mdefine_line|#define RING_TAIL_MASK&t;&t;&t;0x001ffff8
DECL|macro|RING_INUSE
mdefine_line|#define RING_INUSE&t;&t;&t;0x1
DECL|macro|PRI_RING_HEAD
mdefine_line|#define PRI_RING_HEAD&t;&t;0x2034
DECL|macro|RING_HEAD_WRAP_MASK
mdefine_line|#define RING_HEAD_WRAP_MASK&t;&t;0x7ff
DECL|macro|RING_HEAD_WRAP_SHIFT
mdefine_line|#define RING_HEAD_WRAP_SHIFT&t;&t;21
DECL|macro|RING_HEAD_MASK
mdefine_line|#define RING_HEAD_MASK&t;&t;&t;0x001ffffc
DECL|macro|PRI_RING_START
mdefine_line|#define PRI_RING_START&t;&t;0x2038
DECL|macro|RING_START_MASK
mdefine_line|#define RING_START_MASK&t;&t;&t;0xfffff000
DECL|macro|PRI_RING_LENGTH
mdefine_line|#define PRI_RING_LENGTH&t;&t;0x203c
DECL|macro|RING_LENGTH_MASK
mdefine_line|#define RING_LENGTH_MASK&t;&t;0x001ff000
DECL|macro|RING_REPORT_MASK
mdefine_line|#define RING_REPORT_MASK&t;&t;(0x3 &lt;&lt; 1)
DECL|macro|RING_NO_REPORT
mdefine_line|#define RING_NO_REPORT&t;&t;&t;(0x0 &lt;&lt; 1)
DECL|macro|RING_REPORT_64K
mdefine_line|#define RING_REPORT_64K&t;&t;&t;(0x1 &lt;&lt; 1)
DECL|macro|RING_REPORT_4K
mdefine_line|#define RING_REPORT_4K&t;&t;&t;(0x2 &lt;&lt; 1)
DECL|macro|RING_REPORT_128K
mdefine_line|#define RING_REPORT_128K&t;&t;(0x3 &lt;&lt; 1)
DECL|macro|RING_ENABLE
mdefine_line|#define RING_ENABLE&t;&t;&t;0x1
multiline_comment|/*&n; * Tail can&squot;t wrap to any closer than RING_MIN_FREE bytes of the head,&n; * and the last RING_MIN_FREE bytes need to be padded with MI_NOOP&n; */
DECL|macro|RING_MIN_FREE
mdefine_line|#define RING_MIN_FREE&t;&t;&t;64
DECL|macro|IPEHR
mdefine_line|#define IPEHR     &t;&t;0x2088
DECL|macro|INSTDONE
mdefine_line|#define INSTDONE&t;&t;0x2090
DECL|macro|PRI_RING_EMPTY
mdefine_line|#define PRI_RING_EMPTY&t;&t;&t;1
DECL|macro|INSTPM
mdefine_line|#define INSTPM&t;&t;&t;0x20c0
DECL|macro|SYNC_FLUSH_ENABLE
mdefine_line|#define SYNC_FLUSH_ENABLE&t;&t;(1 &lt;&lt; 5)
DECL|macro|INSTPS
mdefine_line|#define INSTPS&t;&t;&t;0x20c4
DECL|macro|MEM_MODE
mdefine_line|#define MEM_MODE&t;&t;0x20cc
DECL|macro|MASK_SHIFT
mdefine_line|#define MASK_SHIFT&t;&t;&t;16
DECL|macro|FW_BLC_0
mdefine_line|#define FW_BLC_0&t;&t;0x20d8
DECL|macro|FW_DISPA_WM_SHIFT
mdefine_line|#define FW_DISPA_WM_SHIFT&t;&t;0
DECL|macro|FW_DISPA_WM_MASK
mdefine_line|#define FW_DISPA_WM_MASK&t;&t;0x3f
DECL|macro|FW_DISPA_BL_SHIFT
mdefine_line|#define FW_DISPA_BL_SHIFT&t;&t;8
DECL|macro|FW_DISPA_BL_MASK
mdefine_line|#define FW_DISPA_BL_MASK&t;&t;0xf
DECL|macro|FW_DISPB_WM_SHIFT
mdefine_line|#define FW_DISPB_WM_SHIFT&t;&t;16
DECL|macro|FW_DISPB_WM_MASK
mdefine_line|#define FW_DISPB_WM_MASK&t;&t;0x1f
DECL|macro|FW_DISPB_BL_SHIFT
mdefine_line|#define FW_DISPB_BL_SHIFT&t;&t;24
DECL|macro|FW_DISPB_BL_MASK
mdefine_line|#define FW_DISPB_BL_MASK&t;&t;0x7
DECL|macro|FW_BLC_1
mdefine_line|#define FW_BLC_1&t;&t;0x20dc
DECL|macro|FW_DISPC_WM_SHIFT
mdefine_line|#define FW_DISPC_WM_SHIFT&t;&t;0
DECL|macro|FW_DISPC_WM_MASK
mdefine_line|#define FW_DISPC_WM_MASK&t;&t;0x1f
DECL|macro|FW_DISPC_BL_SHIFT
mdefine_line|#define FW_DISPC_BL_SHIFT&t;&t;8
DECL|macro|FW_DISPC_BL_MASK
mdefine_line|#define FW_DISPC_BL_MASK&t;&t;0x7
multiline_comment|/* PLL registers */
DECL|macro|VGA0_DIVISOR
mdefine_line|#define VGA0_DIVISOR&t;&t;0x06000
DECL|macro|VGA1_DIVISOR
mdefine_line|#define VGA1_DIVISOR&t;&t;0x06004
DECL|macro|VGAPD
mdefine_line|#define VGAPD&t;&t;&t;0x06010
DECL|macro|VGAPD_0_P1_SHIFT
mdefine_line|#define VGAPD_0_P1_SHIFT&t;&t;0
DECL|macro|VGAPD_0_P1_FORCE_DIV2
mdefine_line|#define VGAPD_0_P1_FORCE_DIV2&t;&t;(1 &lt;&lt; 5)
DECL|macro|VGAPD_0_P2_SHIFT
mdefine_line|#define VGAPD_0_P2_SHIFT&t;&t;7
DECL|macro|VGAPD_1_P1_SHIFT
mdefine_line|#define VGAPD_1_P1_SHIFT&t;&t;8
DECL|macro|VGAPD_1_P1_FORCE_DIV2
mdefine_line|#define VGAPD_1_P1_FORCE_DIV2&t;&t;(1 &lt;&lt; 13)
DECL|macro|VGAPD_1_P2_SHIFT
mdefine_line|#define VGAPD_1_P2_SHIFT&t;&t;15
DECL|macro|DPLL_A
mdefine_line|#define DPLL_A&t;&t;&t;0x06014
DECL|macro|DPLL_B
mdefine_line|#define DPLL_B&t;&t;&t;0x06018
DECL|macro|DPLL_VCO_ENABLE
mdefine_line|#define DPLL_VCO_ENABLE&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|DPLL_2X_CLOCK_ENABLE
mdefine_line|#define DPLL_2X_CLOCK_ENABLE&t;&t;(1 &lt;&lt; 30)
DECL|macro|DPLL_SYNCLOCK_ENABLE
mdefine_line|#define DPLL_SYNCLOCK_ENABLE&t;&t;(1 &lt;&lt; 29)
DECL|macro|DPLL_VGA_MODE_DISABLE
mdefine_line|#define DPLL_VGA_MODE_DISABLE&t;&t;(1 &lt;&lt; 28)
DECL|macro|DPLL_P2_MASK
mdefine_line|#define DPLL_P2_MASK&t;&t;&t;1
DECL|macro|DPLL_P2_SHIFT
mdefine_line|#define DPLL_P2_SHIFT&t;&t;&t;23
DECL|macro|DPLL_P1_FORCE_DIV2
mdefine_line|#define DPLL_P1_FORCE_DIV2&t;&t;(1 &lt;&lt; 21)
DECL|macro|DPLL_P1_MASK
mdefine_line|#define DPLL_P1_MASK&t;&t;&t;0x1f
DECL|macro|DPLL_P1_SHIFT
mdefine_line|#define DPLL_P1_SHIFT&t;&t;&t;16
DECL|macro|DPLL_REFERENCE_SELECT_MASK
mdefine_line|#define DPLL_REFERENCE_SELECT_MASK&t;(0x3 &lt;&lt; 13)
DECL|macro|DPLL_REFERENCE_DEFAULT
mdefine_line|#define DPLL_REFERENCE_DEFAULT&t;&t;(0x0 &lt;&lt; 13)
DECL|macro|DPLL_REFERENCE_TVCLK
mdefine_line|#define DPLL_REFERENCE_TVCLK&t;&t;(0x2 &lt;&lt; 13)
DECL|macro|DPLL_RATE_SELECT_MASK
mdefine_line|#define DPLL_RATE_SELECT_MASK&t;&t;(1 &lt;&lt; 8)
DECL|macro|DPLL_RATE_SELECT_FP0
mdefine_line|#define DPLL_RATE_SELECT_FP0&t;&t;(0 &lt;&lt; 8)
DECL|macro|DPLL_RATE_SELECT_FP1
mdefine_line|#define DPLL_RATE_SELECT_FP1&t;&t;(1 &lt;&lt; 8)
DECL|macro|FPA0
mdefine_line|#define FPA0&t;&t;&t;0x06040
DECL|macro|FPA1
mdefine_line|#define FPA1&t;&t;&t;0x06044
DECL|macro|FPB0
mdefine_line|#define FPB0&t;&t;&t;0x06048
DECL|macro|FPB1
mdefine_line|#define FPB1&t;&t;&t;0x0604c
DECL|macro|FP_DIVISOR_MASK
mdefine_line|#define FP_DIVISOR_MASK&t;&t;&t;0x3f
DECL|macro|FP_N_DIVISOR_SHIFT
mdefine_line|#define FP_N_DIVISOR_SHIFT&t;&t;16
DECL|macro|FP_M1_DIVISOR_SHIFT
mdefine_line|#define FP_M1_DIVISOR_SHIFT&t;&t;8
DECL|macro|FP_M2_DIVISOR_SHIFT
mdefine_line|#define FP_M2_DIVISOR_SHIFT&t;&t;0
multiline_comment|/* PLL parameters (these are for 852GM/855GM/865G, check earlier chips). */
multiline_comment|/* Clock values are in units of kHz */
DECL|macro|PLL_REFCLK
mdefine_line|#define PLL_REFCLK&t;&t;48000
DECL|macro|MIN_VCO_FREQ
mdefine_line|#define MIN_VCO_FREQ&t;&t;930000
DECL|macro|MAX_VCO_FREQ
mdefine_line|#define MAX_VCO_FREQ&t;&t;1400000
DECL|macro|MIN_CLOCK
mdefine_line|#define MIN_CLOCK&t;&t;25000
DECL|macro|MAX_CLOCK
mdefine_line|#define MAX_CLOCK&t;&t;350000
DECL|macro|P_TRANSITION_CLOCK
mdefine_line|#define P_TRANSITION_CLOCK&t;165000
DECL|macro|MIN_M
mdefine_line|#define MIN_M&t;&t;&t;108
DECL|macro|MAX_M
mdefine_line|#define MAX_M&t;&t;&t;140
DECL|macro|MIN_M1
mdefine_line|#define MIN_M1&t;&t;&t;18
DECL|macro|MAX_M1
mdefine_line|#define MAX_M1&t;&t;&t;26
DECL|macro|MIN_M2
mdefine_line|#define MIN_M2&t;&t;&t;6
DECL|macro|MAX_M2
mdefine_line|#define MAX_M2&t;&t;&t;16
DECL|macro|MIN_P
mdefine_line|#define MIN_P&t;&t;&t;4
DECL|macro|MAX_P
mdefine_line|#define MAX_P&t;&t;&t;128
DECL|macro|MIN_P1
mdefine_line|#define MIN_P1&t;&t;&t;0
DECL|macro|MAX_P1
mdefine_line|#define MAX_P1&t;&t;&t;31
DECL|macro|MIN_N
mdefine_line|#define MIN_N&t;&t;&t;3
DECL|macro|MAX_N
mdefine_line|#define MAX_N&t;&t;&t;16
DECL|macro|CALC_VCLOCK
mdefine_line|#define CALC_VCLOCK(m1, m2, n, p1, p2) &bslash;&n;        ((PLL_REFCLK * (5 * ((m1) + 2) + ((m2) + 2)) / ((n) + 2)) / &bslash;&n;        (((p1) + 2) * (1 &lt;&lt; (p2 + 1))))
DECL|macro|CALC_VCLOCK3
mdefine_line|#define CALC_VCLOCK3(m, n, p)&t;((PLL_REFCLK * (m) / (n)) / (p))
multiline_comment|/* Two pipes */
DECL|macro|PIPE_A
mdefine_line|#define PIPE_A&t;&t;&t;0
DECL|macro|PIPE_B
mdefine_line|#define PIPE_B&t;&t;&t;1
DECL|macro|PIPE_MASK
mdefine_line|#define PIPE_MASK&t;&t;1
multiline_comment|/* palette registers */
DECL|macro|PALETTE_A
mdefine_line|#define PALETTE_A&t;&t;0x0a000
DECL|macro|PALETTE_B
mdefine_line|#define PALETTE_B&t;&t;0x0a800
macro_line|#ifndef PALETTE_8_ENTRIES
DECL|macro|PALETTE_8_ENTRIES
mdefine_line|#define PALETTE_8_ENTRIES&t;&t;256
macro_line|#endif
DECL|macro|PALETTE_8_SIZE
mdefine_line|#define PALETTE_8_SIZE&t;&t;&t;(PALETTE_8_ENTRIES * 4)
DECL|macro|PALETTE_10_ENTRIES
mdefine_line|#define PALETTE_10_ENTRIES&t;&t;128
DECL|macro|PALETTE_10_SIZE
mdefine_line|#define PALETTE_10_SIZE&t;&t;&t;(PALETTE_10_ENTRIES * 8)
DECL|macro|PALETTE_8_MASK
mdefine_line|#define PALETTE_8_MASK&t;&t;&t;0xff
DECL|macro|PALETTE_8_RED_SHIFT
mdefine_line|#define PALETTE_8_RED_SHIFT&t;&t;16
DECL|macro|PALETTE_8_GREEN_SHIFT
mdefine_line|#define PALETTE_8_GREEN_SHIFT&t;&t;8
DECL|macro|PALETTE_8_BLUE_SHIFT
mdefine_line|#define PALETTE_8_BLUE_SHIFT&t;&t;0
multiline_comment|/* CRTC registers */
DECL|macro|HTOTAL_A
mdefine_line|#define HTOTAL_A&t;&t;0x60000
DECL|macro|HBLANK_A
mdefine_line|#define HBLANK_A&t;&t;0x60004
DECL|macro|HSYNC_A
mdefine_line|#define HSYNC_A&t;&t;&t;0x60008
DECL|macro|VTOTAL_A
mdefine_line|#define VTOTAL_A&t;&t;0x6000c
DECL|macro|VBLANK_A
mdefine_line|#define VBLANK_A&t;&t;0x60010
DECL|macro|VSYNC_A
mdefine_line|#define VSYNC_A&t;&t;&t;0x60014
DECL|macro|SRC_SIZE_A
mdefine_line|#define SRC_SIZE_A&t;&t;0x6001c
DECL|macro|BCLRPAT_A
mdefine_line|#define BCLRPAT_A&t;&t;0x60020
DECL|macro|HTOTAL_B
mdefine_line|#define HTOTAL_B&t;&t;0x61000
DECL|macro|HBLANK_B
mdefine_line|#define HBLANK_B&t;&t;0x61004
DECL|macro|HSYNC_B
mdefine_line|#define HSYNC_B&t;&t;&t;0x61008
DECL|macro|VTOTAL_B
mdefine_line|#define VTOTAL_B&t;&t;0x6100c
DECL|macro|VBLANK_B
mdefine_line|#define VBLANK_B&t;&t;0x61010
DECL|macro|VSYNC_B
mdefine_line|#define VSYNC_B&t;&t;&t;0x61014
DECL|macro|SRC_SIZE_B
mdefine_line|#define SRC_SIZE_B&t;&t;0x6101c
DECL|macro|BCLRPAT_B
mdefine_line|#define BCLRPAT_B&t;&t;0x61020
DECL|macro|HTOTAL_MASK
mdefine_line|#define HTOTAL_MASK&t;&t;&t;0xfff
DECL|macro|HTOTAL_SHIFT
mdefine_line|#define HTOTAL_SHIFT&t;&t;&t;16
DECL|macro|HACTIVE_MASK
mdefine_line|#define HACTIVE_MASK&t;&t;&t;0x7ff
DECL|macro|HACTIVE_SHIFT
mdefine_line|#define HACTIVE_SHIFT&t;&t;&t;0
DECL|macro|HBLANKEND_MASK
mdefine_line|#define HBLANKEND_MASK&t;&t;&t;0xfff
DECL|macro|HBLANKEND_SHIFT
mdefine_line|#define HBLANKEND_SHIFT&t;&t;&t;16
DECL|macro|HBLANKSTART_MASK
mdefine_line|#define HBLANKSTART_MASK&t;&t;0xfff
DECL|macro|HBLANKSTART_SHIFT
mdefine_line|#define HBLANKSTART_SHIFT&t;&t;0
DECL|macro|HSYNCEND_MASK
mdefine_line|#define HSYNCEND_MASK&t;&t;&t;0xfff
DECL|macro|HSYNCEND_SHIFT
mdefine_line|#define HSYNCEND_SHIFT&t;&t;&t;16
DECL|macro|HSYNCSTART_MASK
mdefine_line|#define HSYNCSTART_MASK&t;&t;&t;0xfff
DECL|macro|HSYNCSTART_SHIFT
mdefine_line|#define HSYNCSTART_SHIFT&t;&t;0
DECL|macro|VTOTAL_MASK
mdefine_line|#define VTOTAL_MASK&t;&t;&t;0xfff
DECL|macro|VTOTAL_SHIFT
mdefine_line|#define VTOTAL_SHIFT&t;&t;&t;16
DECL|macro|VACTIVE_MASK
mdefine_line|#define VACTIVE_MASK&t;&t;&t;0x7ff
DECL|macro|VACTIVE_SHIFT
mdefine_line|#define VACTIVE_SHIFT&t;&t;&t;0
DECL|macro|VBLANKEND_MASK
mdefine_line|#define VBLANKEND_MASK&t;&t;&t;0xfff
DECL|macro|VBLANKEND_SHIFT
mdefine_line|#define VBLANKEND_SHIFT&t;&t;&t;16
DECL|macro|VBLANKSTART_MASK
mdefine_line|#define VBLANKSTART_MASK&t;&t;0xfff
DECL|macro|VBLANKSTART_SHIFT
mdefine_line|#define VBLANKSTART_SHIFT&t;&t;0
DECL|macro|VSYNCEND_MASK
mdefine_line|#define VSYNCEND_MASK&t;&t;&t;0xfff
DECL|macro|VSYNCEND_SHIFT
mdefine_line|#define VSYNCEND_SHIFT&t;&t;&t;16
DECL|macro|VSYNCSTART_MASK
mdefine_line|#define VSYNCSTART_MASK&t;&t;&t;0xfff
DECL|macro|VSYNCSTART_SHIFT
mdefine_line|#define VSYNCSTART_SHIFT&t;&t;0
DECL|macro|SRC_SIZE_HORIZ_MASK
mdefine_line|#define SRC_SIZE_HORIZ_MASK&t;&t;0x7ff
DECL|macro|SRC_SIZE_HORIZ_SHIFT
mdefine_line|#define SRC_SIZE_HORIZ_SHIFT&t;&t;16
DECL|macro|SRC_SIZE_VERT_MASK
mdefine_line|#define SRC_SIZE_VERT_MASK&t;&t;0x7ff
DECL|macro|SRC_SIZE_VERT_SHIFT
mdefine_line|#define SRC_SIZE_VERT_SHIFT&t;&t;0
DECL|macro|ADPA
mdefine_line|#define ADPA&t;&t;&t;0x61100
DECL|macro|ADPA_DAC_ENABLE
mdefine_line|#define ADPA_DAC_ENABLE&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|ADPA_DAC_DISABLE
mdefine_line|#define ADPA_DAC_DISABLE&t;&t;0
DECL|macro|ADPA_PIPE_SELECT_SHIFT
mdefine_line|#define ADPA_PIPE_SELECT_SHIFT&t;&t;30
DECL|macro|ADPA_USE_VGA_HVPOLARITY
mdefine_line|#define ADPA_USE_VGA_HVPOLARITY&t;&t;(1 &lt;&lt; 15)
DECL|macro|ADPA_SETS_HVPOLARITY
mdefine_line|#define ADPA_SETS_HVPOLARITY&t;&t;0
DECL|macro|ADPA_DPMS_CONTROL_MASK
mdefine_line|#define ADPA_DPMS_CONTROL_MASK&t;&t;(0x3 &lt;&lt; 10)
DECL|macro|ADPA_DPMS_D0
mdefine_line|#define ADPA_DPMS_D0&t;&t;&t;(0x0 &lt;&lt; 10)
DECL|macro|ADPA_DPMS_D2
mdefine_line|#define ADPA_DPMS_D2&t;&t;&t;(0x1 &lt;&lt; 10)
DECL|macro|ADPA_DPMS_D1
mdefine_line|#define ADPA_DPMS_D1&t;&t;&t;(0x2 &lt;&lt; 10)
DECL|macro|ADPA_DPMS_D3
mdefine_line|#define ADPA_DPMS_D3&t;&t;&t;(0x3 &lt;&lt; 10)
DECL|macro|ADPA_VSYNC_ACTIVE_SHIFT
mdefine_line|#define ADPA_VSYNC_ACTIVE_SHIFT&t;&t;4
DECL|macro|ADPA_HSYNC_ACTIVE_SHIFT
mdefine_line|#define ADPA_HSYNC_ACTIVE_SHIFT&t;&t;3
DECL|macro|ADPA_SYNC_ACTIVE_MASK
mdefine_line|#define ADPA_SYNC_ACTIVE_MASK&t;&t;1
DECL|macro|ADPA_SYNC_ACTIVE_HIGH
mdefine_line|#define ADPA_SYNC_ACTIVE_HIGH&t;&t;1
DECL|macro|ADPA_SYNC_ACTIVE_LOW
mdefine_line|#define ADPA_SYNC_ACTIVE_LOW&t;&t;0
DECL|macro|DVOA
mdefine_line|#define DVOA&t;&t;&t;0x61120
DECL|macro|DVOB
mdefine_line|#define DVOB&t;&t;&t;0x61140
DECL|macro|DVOC
mdefine_line|#define DVOC&t;&t;&t;0x61160
DECL|macro|LVDS
mdefine_line|#define LVDS&t;&t;&t;0x61180
DECL|macro|PORT_ENABLE
mdefine_line|#define PORT_ENABLE&t;&t;        (1 &lt;&lt; 31)
DECL|macro|PORT_PIPE_SELECT_SHIFT
mdefine_line|#define PORT_PIPE_SELECT_SHIFT&t;        30
DECL|macro|PORT_TV_FLAGS_MASK
mdefine_line|#define PORT_TV_FLAGS_MASK              0xFF
DECL|macro|PORT_TV_FLAGS
mdefine_line|#define PORT_TV_FLAGS                   0xC4  
singleline_comment|// ripped from my BIOS
singleline_comment|// to understand and correct
DECL|macro|DVOA_SRCDIM
mdefine_line|#define DVOA_SRCDIM&t;&t;0x61124
DECL|macro|DVOB_SRCDIM
mdefine_line|#define DVOB_SRCDIM&t;&t;0x61144
DECL|macro|DVOC_SRCDIM
mdefine_line|#define DVOC_SRCDIM&t;&t;0x61164
DECL|macro|PIPEACONF
mdefine_line|#define PIPEACONF&t;&t;0x70008
DECL|macro|PIPEBCONF
mdefine_line|#define PIPEBCONF&t;&t;0x71008
DECL|macro|PIPECONF_ENABLE
mdefine_line|#define PIPECONF_ENABLE&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|PIPECONF_DISABLE
mdefine_line|#define PIPECONF_DISABLE&t;&t;0
DECL|macro|PIPECONF_DOUBLE_WIDE
mdefine_line|#define PIPECONF_DOUBLE_WIDE&t;&t;(1 &lt;&lt; 30)
DECL|macro|PIPECONF_SINGLE_WIDE
mdefine_line|#define PIPECONF_SINGLE_WIDE&t;&t;0
DECL|macro|PIPECONF_LOCKED
mdefine_line|#define PIPECONF_LOCKED&t;&t;&t;(1 &lt;&lt; 25)
DECL|macro|PIPECONF_UNLOCKED
mdefine_line|#define PIPECONF_UNLOCKED&t;&t;0
DECL|macro|PIPECONF_GAMMA
mdefine_line|#define PIPECONF_GAMMA&t;&t;&t;(1 &lt;&lt; 24)
DECL|macro|PIPECONF_PALETTE
mdefine_line|#define PIPECONF_PALETTE&t;&t;0
DECL|macro|DISPARB
mdefine_line|#define DISPARB&t;&t;&t;0x70030
DECL|macro|DISPARB_AEND_MASK
mdefine_line|#define DISPARB_AEND_MASK&t;&t;0x1ff
DECL|macro|DISPARB_AEND_SHIFT
mdefine_line|#define DISPARB_AEND_SHIFT&t;&t;0
DECL|macro|DISPARB_BEND_MASK
mdefine_line|#define DISPARB_BEND_MASK&t;&t;0x3ff
DECL|macro|DISPARB_BEND_SHIFT
mdefine_line|#define DISPARB_BEND_SHIFT&t;&t;9
multiline_comment|/* Desktop HW cursor */
DECL|macro|CURSOR_CONTROL
mdefine_line|#define CURSOR_CONTROL&t;&t;0x70080
DECL|macro|CURSOR_ENABLE
mdefine_line|#define CURSOR_ENABLE&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|CURSOR_GAMMA_ENABLE
mdefine_line|#define CURSOR_GAMMA_ENABLE&t;&t;(1 &lt;&lt; 30)
DECL|macro|CURSOR_STRIDE_MASK
mdefine_line|#define CURSOR_STRIDE_MASK&t;&t;(0x3 &lt;&lt; 28)
DECL|macro|CURSOR_STRIDE_256
mdefine_line|#define CURSOR_STRIDE_256&t;&t;(0x0 &lt;&lt; 28)
DECL|macro|CURSOR_STRIDE_512
mdefine_line|#define CURSOR_STRIDE_512&t;&t;(0x1 &lt;&lt; 28)
DECL|macro|CURSOR_STRIDE_1K
mdefine_line|#define CURSOR_STRIDE_1K&t;&t;(0x2 &lt;&lt; 28)
DECL|macro|CURSOR_STRIDE_2K
mdefine_line|#define CURSOR_STRIDE_2K&t;&t;(0x3 &lt;&lt; 28)
DECL|macro|CURSOR_FORMAT_MASK
mdefine_line|#define CURSOR_FORMAT_MASK&t;&t;(0x7 &lt;&lt; 24)
DECL|macro|CURSOR_FORMAT_2C
mdefine_line|#define CURSOR_FORMAT_2C&t;&t;(0x0 &lt;&lt; 24)
DECL|macro|CURSOR_FORMAT_3C
mdefine_line|#define CURSOR_FORMAT_3C&t;&t;(0x1 &lt;&lt; 24)
DECL|macro|CURSOR_FORMAT_4C
mdefine_line|#define CURSOR_FORMAT_4C&t;&t;(0x2 &lt;&lt; 24)
DECL|macro|CURSOR_FORMAT_ARGB
mdefine_line|#define CURSOR_FORMAT_ARGB&t;&t;(0x4 &lt;&lt; 24)
DECL|macro|CURSOR_FORMAT_XRGB
mdefine_line|#define CURSOR_FORMAT_XRGB&t;&t;(0x5 &lt;&lt; 24)
multiline_comment|/* Mobile HW cursor (and i810) */
DECL|macro|CURSOR_A_CONTROL
mdefine_line|#define CURSOR_A_CONTROL&t;CURSOR_CONTROL
DECL|macro|CURSOR_B_CONTROL
mdefine_line|#define CURSOR_B_CONTROL&t;0x700c0
DECL|macro|CURSOR_MODE_MASK
mdefine_line|#define CURSOR_MODE_MASK&t;&t;0x27
DECL|macro|CURSOR_MODE_DISABLE
mdefine_line|#define CURSOR_MODE_DISABLE&t;&t;0
DECL|macro|CURSOR_MODE_64_3C
mdefine_line|#define CURSOR_MODE_64_3C&t;&t;0x04
DECL|macro|CURSOR_MODE_64_4C_AX
mdefine_line|#define CURSOR_MODE_64_4C_AX&t;&t;0x05
DECL|macro|CURSOR_MODE_64_4C
mdefine_line|#define CURSOR_MODE_64_4C&t;&t;0x06
DECL|macro|CURSOR_MODE_64_32B_AX
mdefine_line|#define CURSOR_MODE_64_32B_AX&t;&t;0x07
DECL|macro|CURSOR_MODE_64_ARGB_AX
mdefine_line|#define CURSOR_MODE_64_ARGB_AX&t;&t;0x27
DECL|macro|CURSOR_PIPE_SELECT_SHIFT
mdefine_line|#define CURSOR_PIPE_SELECT_SHIFT&t;28
DECL|macro|CURSOR_MOBILE_GAMMA_ENABLE
mdefine_line|#define CURSOR_MOBILE_GAMMA_ENABLE&t;(1 &lt;&lt; 26)
DECL|macro|CURSOR_MEM_TYPE_LOCAL
mdefine_line|#define CURSOR_MEM_TYPE_LOCAL&t;&t;(1 &lt;&lt; 25)
multiline_comment|/* All platforms (desktop has no pipe B) */
DECL|macro|CURSOR_A_BASEADDR
mdefine_line|#define CURSOR_A_BASEADDR&t;0x70084
DECL|macro|CURSOR_B_BASEADDR
mdefine_line|#define CURSOR_B_BASEADDR&t;0x700c4
DECL|macro|CURSOR_BASE_MASK
mdefine_line|#define CURSOR_BASE_MASK&t;&t;0xffffff00
DECL|macro|CURSOR_A_POSITION
mdefine_line|#define CURSOR_A_POSITION&t;0x70088
DECL|macro|CURSOR_B_POSITION
mdefine_line|#define CURSOR_B_POSITION&t;0x700c8
DECL|macro|CURSOR_POS_SIGN
mdefine_line|#define CURSOR_POS_SIGN&t;&t;&t;(1 &lt;&lt; 15)
DECL|macro|CURSOR_POS_MASK
mdefine_line|#define CURSOR_POS_MASK&t;&t;&t;0x7ff
DECL|macro|CURSOR_X_SHIFT
mdefine_line|#define CURSOR_X_SHIFT&t;&t;&t;0
DECL|macro|CURSOR_Y_SHIFT
mdefine_line|#define CURSOR_Y_SHIFT&t;&t;&t;16
DECL|macro|CURSOR_A_PALETTE0
mdefine_line|#define CURSOR_A_PALETTE0&t;0x70090
DECL|macro|CURSOR_A_PALETTE1
mdefine_line|#define CURSOR_A_PALETTE1&t;0x70094
DECL|macro|CURSOR_A_PALETTE2
mdefine_line|#define CURSOR_A_PALETTE2&t;0x70098
DECL|macro|CURSOR_A_PALETTE3
mdefine_line|#define CURSOR_A_PALETTE3&t;0x7009c
DECL|macro|CURSOR_B_PALETTE0
mdefine_line|#define CURSOR_B_PALETTE0&t;0x700d0
DECL|macro|CURSOR_B_PALETTE1
mdefine_line|#define CURSOR_B_PALETTE1&t;0x700d4
DECL|macro|CURSOR_B_PALETTE2
mdefine_line|#define CURSOR_B_PALETTE2&t;0x700d8
DECL|macro|CURSOR_B_PALETTE3
mdefine_line|#define CURSOR_B_PALETTE3&t;0x700dc
DECL|macro|CURSOR_COLOR_MASK
mdefine_line|#define CURSOR_COLOR_MASK&t;&t;&t;0xff
DECL|macro|CURSOR_RED_SHIFT
mdefine_line|#define CURSOR_RED_SHIFT&t;&t;&t;16
DECL|macro|CURSOR_GREEN_SHIFT
mdefine_line|#define CURSOR_GREEN_SHIFT&t;&t;&t;8
DECL|macro|CURSOR_BLUE_SHIFT
mdefine_line|#define CURSOR_BLUE_SHIFT&t;&t;&t;0
DECL|macro|CURSOR_PALETTE_MASK
mdefine_line|#define CURSOR_PALETTE_MASK&t;&t;&t;0xffffff
multiline_comment|/* Desktop only */
DECL|macro|CURSOR_SIZE
mdefine_line|#define CURSOR_SIZE&t;&t;0x700a0
DECL|macro|CURSOR_SIZE_MASK
mdefine_line|#define CURSOR_SIZE_MASK&t;&t;0x3ff
DECL|macro|CURSOR_SIZE_H_SHIFT
mdefine_line|#define CURSOR_SIZE_H_SHIFT&t;&t;0
DECL|macro|CURSOR_SIZE_V_SHIFT
mdefine_line|#define CURSOR_SIZE_V_SHIFT&t;&t;12
DECL|macro|DSPACNTR
mdefine_line|#define DSPACNTR&t;&t;0x70180
DECL|macro|DSPBCNTR
mdefine_line|#define DSPBCNTR&t;&t;0x71180
DECL|macro|DISPPLANE_PLANE_ENABLE
mdefine_line|#define DISPPLANE_PLANE_ENABLE&t;&t;(1 &lt;&lt; 31)
DECL|macro|DISPPLANE_PLANE_DISABLE
mdefine_line|#define DISPPLANE_PLANE_DISABLE&t;&t;0
DECL|macro|DISPPLANE_GAMMA_ENABLE
mdefine_line|#define DISPPLANE_GAMMA_ENABLE&t;&t;(1&lt;&lt;30)
DECL|macro|DISPPLANE_GAMMA_DISABLE
mdefine_line|#define DISPPLANE_GAMMA_DISABLE&t;&t;0
DECL|macro|DISPPLANE_PIXFORMAT_MASK
mdefine_line|#define DISPPLANE_PIXFORMAT_MASK&t;(0xf&lt;&lt;26)
DECL|macro|DISPPLANE_8BPP
mdefine_line|#define DISPPLANE_8BPP&t;&t;&t;(0x2&lt;&lt;26)
DECL|macro|DISPPLANE_15_16BPP
mdefine_line|#define DISPPLANE_15_16BPP&t;&t;(0x4&lt;&lt;26)
DECL|macro|DISPPLANE_16BPP
mdefine_line|#define DISPPLANE_16BPP&t;&t;&t;(0x5&lt;&lt;26)
DECL|macro|DISPPLANE_32BPP_NO_ALPHA
mdefine_line|#define DISPPLANE_32BPP_NO_ALPHA &t;(0x6&lt;&lt;26)
DECL|macro|DISPPLANE_32BPP
mdefine_line|#define DISPPLANE_32BPP&t;&t;&t;(0x7&lt;&lt;26)
DECL|macro|DISPPLANE_STEREO_ENABLE
mdefine_line|#define DISPPLANE_STEREO_ENABLE&t;&t;(1&lt;&lt;25)
DECL|macro|DISPPLANE_STEREO_DISABLE
mdefine_line|#define DISPPLANE_STEREO_DISABLE&t;0
DECL|macro|DISPPLANE_SEL_PIPE_SHIFT
mdefine_line|#define DISPPLANE_SEL_PIPE_SHIFT&t;24
DECL|macro|DISPPLANE_SRC_KEY_ENABLE
mdefine_line|#define DISPPLANE_SRC_KEY_ENABLE&t;(1&lt;&lt;22)
DECL|macro|DISPPLANE_SRC_KEY_DISABLE
mdefine_line|#define DISPPLANE_SRC_KEY_DISABLE&t;0
DECL|macro|DISPPLANE_LINE_DOUBLE
mdefine_line|#define DISPPLANE_LINE_DOUBLE&t;&t;(1&lt;&lt;20)
DECL|macro|DISPPLANE_NO_LINE_DOUBLE
mdefine_line|#define DISPPLANE_NO_LINE_DOUBLE&t;0
DECL|macro|DISPPLANE_STEREO_POLARITY_FIRST
mdefine_line|#define DISPPLANE_STEREO_POLARITY_FIRST&t;0
DECL|macro|DISPPLANE_STEREO_POLARITY_SECOND
mdefine_line|#define DISPPLANE_STEREO_POLARITY_SECOND (1&lt;&lt;18)
multiline_comment|/* plane B only */
DECL|macro|DISPPLANE_ALPHA_TRANS_ENABLE
mdefine_line|#define DISPPLANE_ALPHA_TRANS_ENABLE&t;(1&lt;&lt;15)
DECL|macro|DISPPLANE_ALPHA_TRANS_DISABLE
mdefine_line|#define DISPPLANE_ALPHA_TRANS_DISABLE&t;0
DECL|macro|DISPPLANE_SPRITE_ABOVE_DISPLAYA
mdefine_line|#define DISPPLANE_SPRITE_ABOVE_DISPLAYA&t;0
DECL|macro|DISPPLANE_SPRITE_ABOVE_OVERLAY
mdefine_line|#define DISPPLANE_SPRITE_ABOVE_OVERLAY&t;1
DECL|macro|DSPABASE
mdefine_line|#define DSPABASE&t;&t;0x70184
DECL|macro|DSPASTRIDE
mdefine_line|#define DSPASTRIDE&t;&t;0x70188
DECL|macro|DSPBBASE
mdefine_line|#define DSPBBASE&t;&t;0x71184
DECL|macro|DSPBSTRIDE
mdefine_line|#define DSPBSTRIDE&t;&t;0x71188
DECL|macro|VGACNTRL
mdefine_line|#define VGACNTRL&t;&t;0x71400
DECL|macro|VGA_DISABLE
mdefine_line|#define VGA_DISABLE&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|VGA_ENABLE
mdefine_line|#define VGA_ENABLE&t;&t;&t;0
DECL|macro|VGA_PIPE_SELECT_SHIFT
mdefine_line|#define VGA_PIPE_SELECT_SHIFT&t;&t;29
DECL|macro|VGA_PALETTE_READ_SELECT
mdefine_line|#define VGA_PALETTE_READ_SELECT&t;&t;23
DECL|macro|VGA_PALETTE_A_WRITE_DISABLE
mdefine_line|#define VGA_PALETTE_A_WRITE_DISABLE&t;(1 &lt;&lt; 22)
DECL|macro|VGA_PALETTE_B_WRITE_DISABLE
mdefine_line|#define VGA_PALETTE_B_WRITE_DISABLE&t;(1 &lt;&lt; 21)
DECL|macro|VGA_LEGACY_PALETTE
mdefine_line|#define VGA_LEGACY_PALETTE&t;&t;(1 &lt;&lt; 20)
DECL|macro|VGA_6BIT_DAC
mdefine_line|#define VGA_6BIT_DAC&t;&t;&t;0
DECL|macro|VGA_8BIT_DAC
mdefine_line|#define VGA_8BIT_DAC&t;&t;&t;(1 &lt;&lt; 20)
DECL|macro|ADD_ID
mdefine_line|#define ADD_ID&t;&t;&t;0x71408
DECL|macro|ADD_ID_MASK
mdefine_line|#define ADD_ID_MASK&t;&t;&t;0xff
multiline_comment|/* BIOS scratch area registers (830M and 845G). */
DECL|macro|SWF0
mdefine_line|#define SWF0&t;&t;&t;0x71410
DECL|macro|SWF1
mdefine_line|#define SWF1&t;&t;&t;0x71414
DECL|macro|SWF2
mdefine_line|#define SWF2&t;&t;&t;0x71418
DECL|macro|SWF3
mdefine_line|#define SWF3&t;&t;&t;0x7141c
DECL|macro|SWF4
mdefine_line|#define SWF4&t;&t;&t;0x71420
DECL|macro|SWF5
mdefine_line|#define SWF5&t;&t;&t;0x71424
DECL|macro|SWF6
mdefine_line|#define SWF6&t;&t;&t;0x71428
multiline_comment|/* BIOS scratch area registers (852GM, 855GM, 865G). */
DECL|macro|SWF00
mdefine_line|#define SWF00&t;&t;&t;0x70410
DECL|macro|SWF01
mdefine_line|#define SWF01&t;&t;&t;0x70414
DECL|macro|SWF02
mdefine_line|#define SWF02&t;&t;&t;0x70418
DECL|macro|SWF03
mdefine_line|#define SWF03&t;&t;&t;0x7041c
DECL|macro|SWF04
mdefine_line|#define SWF04&t;&t;&t;0x70420
DECL|macro|SWF05
mdefine_line|#define SWF05&t;&t;&t;0x70424
DECL|macro|SWF06
mdefine_line|#define SWF06&t;&t;&t;0x70428
DECL|macro|SWF10
mdefine_line|#define SWF10&t;&t;&t;SWF0
DECL|macro|SWF11
mdefine_line|#define SWF11&t;&t;&t;SWF1
DECL|macro|SWF12
mdefine_line|#define SWF12&t;&t;&t;SWF2
DECL|macro|SWF13
mdefine_line|#define SWF13&t;&t;&t;SWF3
DECL|macro|SWF14
mdefine_line|#define SWF14&t;&t;&t;SWF4
DECL|macro|SWF15
mdefine_line|#define SWF15&t;&t;&t;SWF5
DECL|macro|SWF16
mdefine_line|#define SWF16&t;&t;&t;SWF6
DECL|macro|SWF30
mdefine_line|#define SWF30&t;&t;&t;0x72414
DECL|macro|SWF31
mdefine_line|#define SWF31&t;&t;&t;0x72418
DECL|macro|SWF32
mdefine_line|#define SWF32&t;&t;&t;0x7241c
multiline_comment|/* Memory Commands */
DECL|macro|MI_NOOP
mdefine_line|#define MI_NOOP&t;&t;&t;(0x00 &lt;&lt; 23)
DECL|macro|MI_NOOP_WRITE_ID
mdefine_line|#define MI_NOOP_WRITE_ID&t;&t;(1 &lt;&lt; 22)
DECL|macro|MI_NOOP_ID_MASK
mdefine_line|#define MI_NOOP_ID_MASK&t;&t;&t;((1 &lt;&lt; 22) - 1)
DECL|macro|MI_FLUSH
mdefine_line|#define MI_FLUSH&t;&t;(0x04 &lt;&lt; 23)
DECL|macro|MI_WRITE_DIRTY_STATE
mdefine_line|#define MI_WRITE_DIRTY_STATE&t;&t;(1 &lt;&lt; 4)
DECL|macro|MI_END_SCENE
mdefine_line|#define MI_END_SCENE&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|MI_INHIBIT_RENDER_CACHE_FLUSH
mdefine_line|#define MI_INHIBIT_RENDER_CACHE_FLUSH&t;(1 &lt;&lt; 2)
DECL|macro|MI_INVALIDATE_MAP_CACHE
mdefine_line|#define MI_INVALIDATE_MAP_CACHE&t;&t;(1 &lt;&lt; 0)
DECL|macro|MI_STORE_DWORD_IMM
mdefine_line|#define MI_STORE_DWORD_IMM&t;((0x20 &lt;&lt; 23) | 1)
multiline_comment|/* 2D Commands */
DECL|macro|COLOR_BLT_CMD
mdefine_line|#define COLOR_BLT_CMD&t;&t;((2 &lt;&lt; 29) | (0x40 &lt;&lt; 22) | 3)
DECL|macro|XY_COLOR_BLT_CMD
mdefine_line|#define XY_COLOR_BLT_CMD&t;((2 &lt;&lt; 29) | (0x50 &lt;&lt; 22) | 4)
DECL|macro|XY_SETUP_CLIP_BLT_CMD
mdefine_line|#define XY_SETUP_CLIP_BLT_CMD&t;((2 &lt;&lt; 29) | (0x03 &lt;&lt; 22) | 1)
DECL|macro|XY_SRC_COPY_BLT_CMD
mdefine_line|#define XY_SRC_COPY_BLT_CMD&t;((2 &lt;&lt; 29) | (0x53 &lt;&lt; 22) | 6)
DECL|macro|SRC_COPY_BLT_CMD
mdefine_line|#define SRC_COPY_BLT_CMD&t;((2 &lt;&lt; 29) | (0x43 &lt;&lt; 22) | 4)
DECL|macro|XY_MONO_PAT_BLT_CMD
mdefine_line|#define XY_MONO_PAT_BLT_CMD&t;((2 &lt;&lt; 29) | (0x52 &lt;&lt; 22) | 7)
DECL|macro|XY_MONO_SRC_BLT_CMD
mdefine_line|#define XY_MONO_SRC_BLT_CMD&t;((2 &lt;&lt; 29) | (0x54 &lt;&lt; 22) | 6)
DECL|macro|XY_MONO_SRC_IMM_BLT_CMD
mdefine_line|#define XY_MONO_SRC_IMM_BLT_CMD&t;((2 &lt;&lt; 29) | (0x71 &lt;&lt; 22) | 5)
DECL|macro|TXT_IMM_BLT_CMD
mdefine_line|#define TXT_IMM_BLT_CMD&t;        ((2 &lt;&lt; 29) | (0x30 &lt;&lt; 22) | 2)
DECL|macro|SETUP_BLT_CMD
mdefine_line|#define SETUP_BLT_CMD&t;        ((2 &lt;&lt; 29) | (0x00 &lt;&lt; 22) | 6)
DECL|macro|DW_LENGTH_MASK
mdefine_line|#define DW_LENGTH_MASK&t;&t;&t;0xff
DECL|macro|WRITE_ALPHA
mdefine_line|#define WRITE_ALPHA&t;&t;&t;(1 &lt;&lt; 21)
DECL|macro|WRITE_RGB
mdefine_line|#define WRITE_RGB&t;&t;&t;(1 &lt;&lt; 20)
DECL|macro|VERT_SEED
mdefine_line|#define VERT_SEED&t;&t;&t;(3 &lt;&lt; 8)
DECL|macro|HORIZ_SEED
mdefine_line|#define HORIZ_SEED&t;&t;&t;(3 &lt;&lt; 12)
DECL|macro|COLOR_DEPTH_8
mdefine_line|#define COLOR_DEPTH_8&t;&t;&t;(0 &lt;&lt; 24)
DECL|macro|COLOR_DEPTH_16
mdefine_line|#define COLOR_DEPTH_16&t;&t;&t;(1 &lt;&lt; 24)
DECL|macro|COLOR_DEPTH_32
mdefine_line|#define COLOR_DEPTH_32&t;&t;&t;(3 &lt;&lt; 24)
DECL|macro|SRC_ROP_GXCOPY
mdefine_line|#define SRC_ROP_GXCOPY&t;&t;&t;0xcc
DECL|macro|SRC_ROP_GXXOR
mdefine_line|#define SRC_ROP_GXXOR&t;&t;&t;0x66
DECL|macro|PAT_ROP_GXCOPY
mdefine_line|#define PAT_ROP_GXCOPY                  0xf0
DECL|macro|PAT_ROP_GXXOR
mdefine_line|#define PAT_ROP_GXXOR                   0x5a
DECL|macro|PITCH_SHIFT
mdefine_line|#define PITCH_SHIFT&t;&t;&t;0
DECL|macro|ROP_SHIFT
mdefine_line|#define ROP_SHIFT&t;&t;&t;16
DECL|macro|WIDTH_SHIFT
mdefine_line|#define WIDTH_SHIFT&t;&t;&t;0
DECL|macro|HEIGHT_SHIFT
mdefine_line|#define HEIGHT_SHIFT&t;&t;&t;16
multiline_comment|/* in bytes */
DECL|macro|MAX_MONO_IMM_SIZE
mdefine_line|#define MAX_MONO_IMM_SIZE&t;&t;128
multiline_comment|/*** Macros ***/
multiline_comment|/* I/O macros */
DECL|macro|INREG8
mdefine_line|#define INREG8(addr)&t;      readb((u8 __iomem *)(dinfo-&gt;mmio_base + (addr)))
DECL|macro|INREG
mdefine_line|#define INREG(addr)&t;      readl((u32 __iomem *)(dinfo-&gt;mmio_base + (addr)))
DECL|macro|OUTREG8
mdefine_line|#define OUTREG8(addr, val)    writeb((val),(u8 __iomem *)(dinfo-&gt;mmio_base + &bslash;&n;&t;&t;&t;&t;&t;&t;&t;   (addr)))
DECL|macro|OUTREG
mdefine_line|#define OUTREG(addr, val)     writel((val),(u32 __iomem *)(dinfo-&gt;mmio_base + &bslash;&n;                                     (addr)))
multiline_comment|/* Ring buffer macros */
DECL|macro|OUT_RING
mdefine_line|#define OUT_RING(n)&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;writel((n), (u32 __iomem *)(dinfo-&gt;ring.virtual + dinfo-&gt;ring_tail));&bslash;&n;&t;dinfo-&gt;ring_tail += 4;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;dinfo-&gt;ring_tail &amp;= dinfo-&gt;ring_tail_mask;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|START_RING
mdefine_line|#define START_RING(n)&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (dinfo-&gt;ring_space &lt; (n) * 4)&t;&t;&t;&t;&bslash;&n;&t;&t;wait_ring(dinfo,(n) * 4);&t;&t;&t;&t;&bslash;&n;&t;dinfo-&gt;ring_space -= (n) * 4;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|ADVANCE_RING
mdefine_line|#define ADVANCE_RING()&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;OUTREG(PRI_RING_TAIL, dinfo-&gt;ring_tail);                        &bslash;&n;} while (0)
DECL|macro|DO_RING_IDLE
mdefine_line|#define DO_RING_IDLE()&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u32 head, tail;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;head = INREG(PRI_RING_HEAD) &amp; RING_HEAD_MASK;&t;&t;&bslash;&n;&t;&t;tail = INREG(PRI_RING_TAIL) &amp; RING_TAIL_MASK;&t;&t;&bslash;&n;&t;&t;udelay(10);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (head != tail);&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* function protoypes */
r_extern
r_int
id|intelfbhw_get_chipset
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_char
op_star
op_star
id|name
comma
r_int
op_star
id|chipset
comma
r_int
op_star
id|mobile
)paren
suffix:semicolon
r_extern
r_int
id|intelfbhw_get_memory
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
op_star
id|aperture_size
comma
r_int
op_star
id|stolen_size
)paren
suffix:semicolon
r_extern
r_int
id|intelfbhw_check_non_crt
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|intelfbhw_dvo_to_string
c_func
(paren
r_int
id|dvo
)paren
suffix:semicolon
r_extern
r_int
id|intelfbhw_validate_mode
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
r_extern
r_int
id|intelfbhw_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_do_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_setcolreg
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
comma
r_int
id|transp
)paren
suffix:semicolon
r_extern
r_int
id|intelfbhw_read_hw_state
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
r_struct
id|intelfb_hwstate
op_star
id|hw
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_print_hw_state
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
r_struct
id|intelfb_hwstate
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_int
id|intelfbhw_mode_to_hw
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
r_struct
id|intelfb_hwstate
op_star
id|hw
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
r_extern
r_int
id|intelfbhw_program_mode
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
r_const
r_struct
id|intelfb_hwstate
op_star
id|hw
comma
r_int
id|blank
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_do_sync
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_2d_stop
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_2d_start
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_do_fillrect
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
id|u32
id|x
comma
id|u32
id|y
comma
id|u32
id|w
comma
id|u32
id|h
comma
id|u32
id|color
comma
id|u32
id|pitch
comma
id|u32
id|bpp
comma
id|u32
id|rop
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_do_bitblt
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
id|u32
id|curx
comma
id|u32
id|cury
comma
id|u32
id|dstx
comma
id|u32
id|dsty
comma
id|u32
id|w
comma
id|u32
id|h
comma
id|u32
id|pitch
comma
id|u32
id|bpp
)paren
suffix:semicolon
r_extern
r_int
id|intelfbhw_do_drawglyph
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
id|u32
id|fg
comma
id|u32
id|bg
comma
id|u32
id|w
comma
id|u32
id|h
comma
r_const
id|u8
op_star
id|cdat
comma
id|u32
id|x
comma
id|u32
id|y
comma
id|u32
id|pitch
comma
id|u32
id|bpp
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_cursor_init
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_cursor_hide
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_cursor_show
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_cursor_setpos
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
r_int
id|x
comma
r_int
id|y
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_cursor_setcolor
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
id|u32
id|bg
comma
id|u32
id|fg
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_cursor_load
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
comma
r_int
id|width
comma
r_int
id|height
comma
id|u8
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|intelfbhw_cursor_reset
c_func
(paren
r_struct
id|intelfb_info
op_star
id|dinfo
)paren
suffix:semicolon
macro_line|#endif /* _INTELFBHW_H */
eof
