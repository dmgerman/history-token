multiline_comment|/*  $Id: aty128.h,v 1.1 1999/10/12 11:00:40 geert Exp $&n; *  linux/drivers/video/aty128.h&n; *  Register definitions for ATI Rage128 boards&n; *&n; *  Anthony Tong &lt;atong@uiuc.edu&gt;, 1999&n; *  Brad Douglas &lt;brad@neruo.com&gt;, 2000&n; */
macro_line|#ifndef REG_RAGE128_H
DECL|macro|REG_RAGE128_H
mdefine_line|#define REG_RAGE128_H
DECL|macro|CLOCK_CNTL_INDEX
mdefine_line|#define CLOCK_CNTL_INDEX&t;&t;&t;0x0008
DECL|macro|CLOCK_CNTL_DATA
mdefine_line|#define CLOCK_CNTL_DATA&t;&t;&t;&t;0x000c
DECL|macro|BIOS_0_SCRATCH
mdefine_line|#define BIOS_0_SCRATCH&t;&t;&t;&t;0x0010
DECL|macro|BUS_CNTL
mdefine_line|#define BUS_CNTL&t;&t;&t;&t;0x0030
DECL|macro|GEN_INT_CNTL
mdefine_line|#define GEN_INT_CNTL&t;&t;&t;&t;0x0040
DECL|macro|CRTC_GEN_CNTL
mdefine_line|#define CRTC_GEN_CNTL&t;&t;&t;&t;0x0050
DECL|macro|CRTC_EXT_CNTL
mdefine_line|#define CRTC_EXT_CNTL&t;&t;&t;&t;0x0054
DECL|macro|DAC_CNTL
mdefine_line|#define DAC_CNTL&t;&t;&t;&t;0x0058
DECL|macro|I2C_CNTL_1
mdefine_line|#define I2C_CNTL_1&t;&t;&t;&t;0x0094
DECL|macro|PALETTE_INDEX
mdefine_line|#define PALETTE_INDEX&t;&t;&t;&t;0x00b0
DECL|macro|PALETTE_DATA
mdefine_line|#define PALETTE_DATA&t;&t;&t;&t;0x00b4
DECL|macro|CONFIG_CNTL
mdefine_line|#define CONFIG_CNTL&t;&t;&t;&t;0x00e0
DECL|macro|GEN_RESET_CNTL
mdefine_line|#define GEN_RESET_CNTL&t;&t;&t;&t;0x00f0
DECL|macro|CONFIG_MEMSIZE
mdefine_line|#define CONFIG_MEMSIZE&t;&t;&t;&t;0x00f8
DECL|macro|MEM_CNTL
mdefine_line|#define MEM_CNTL&t;&t;&t;&t;0x0140
DECL|macro|AGP_BASE
mdefine_line|#define AGP_BASE&t;&t;&t;&t;0x0170
DECL|macro|AGP_CNTL
mdefine_line|#define AGP_CNTL&t;&t;&t;&t;0x0174
DECL|macro|AGP_APER_OFFSET
mdefine_line|#define AGP_APER_OFFSET&t;&t;&t;&t;0x0178
DECL|macro|PCI_GART_PAGE
mdefine_line|#define PCI_GART_PAGE&t;&t;&t;&t;0x017c
DECL|macro|PC_NGUI_MODE
mdefine_line|#define PC_NGUI_MODE&t;&t;&t;&t;0x0180
DECL|macro|PC_NGUI_CTLSTAT
mdefine_line|#define PC_NGUI_CTLSTAT&t;&t;&t;&t;0x0184
DECL|macro|MPP_TB_CONFIG
mdefine_line|#define MPP_TB_CONFIG&t;&t;&t;&t;0x01C0
DECL|macro|MPP_GP_CONFIG
mdefine_line|#define MPP_GP_CONFIG&t;&t;&t;&t;0x01C8
DECL|macro|VIPH_CONTROL
mdefine_line|#define VIPH_CONTROL&t;&t;&t;&t;0x01D0
DECL|macro|CRTC_H_TOTAL_DISP
mdefine_line|#define CRTC_H_TOTAL_DISP&t;&t;&t;0x0200
DECL|macro|CRTC_H_SYNC_STRT_WID
mdefine_line|#define CRTC_H_SYNC_STRT_WID&t;&t;&t;0x0204
DECL|macro|CRTC_V_TOTAL_DISP
mdefine_line|#define CRTC_V_TOTAL_DISP&t;&t;&t;0x0208
DECL|macro|CRTC_V_SYNC_STRT_WID
mdefine_line|#define CRTC_V_SYNC_STRT_WID&t;&t;&t;0x020c
DECL|macro|CRTC_OFFSET
mdefine_line|#define CRTC_OFFSET&t;&t;&t;&t;0x0224
DECL|macro|CRTC_OFFSET_CNTL
mdefine_line|#define CRTC_OFFSET_CNTL&t;&t;&t;0x0228
DECL|macro|CRTC_PITCH
mdefine_line|#define CRTC_PITCH&t;&t;&t;&t;0x022c
DECL|macro|OVR_CLR
mdefine_line|#define OVR_CLR&t;&t;&t;&t;&t;0x0230
DECL|macro|OVR_WID_LEFT_RIGHT
mdefine_line|#define OVR_WID_LEFT_RIGHT&t;&t;&t;0x0234
DECL|macro|OVR_WID_TOP_BOTTOM
mdefine_line|#define OVR_WID_TOP_BOTTOM&t;&t;&t;0x0238
DECL|macro|LVDS_GEN_CNTL
mdefine_line|#define LVDS_GEN_CNTL&t;&t;&t;&t;0x02d0
DECL|macro|DDA_CONFIG
mdefine_line|#define DDA_CONFIG&t;&t;&t;&t;0x02e0
DECL|macro|DDA_ON_OFF
mdefine_line|#define DDA_ON_OFF&t;&t;&t;&t;0x02e4
DECL|macro|VGA_DDA_CONFIG
mdefine_line|#define VGA_DDA_CONFIG&t;&t;&t;&t;0x02e8
DECL|macro|VGA_DDA_ON_OFF
mdefine_line|#define VGA_DDA_ON_OFF&t;&t;&t;&t;0x02ec
DECL|macro|OV0_SCALE_CNTL
mdefine_line|#define OV0_SCALE_CNTL&t;&t;&t;&t;0x0420
DECL|macro|SUBPIC_CNTL
mdefine_line|#define SUBPIC_CNTL&t;&t;&t;&t;0x0540
DECL|macro|PM4_BUFFER_OFFSET
mdefine_line|#define PM4_BUFFER_OFFSET&t;&t;&t;0x0700
DECL|macro|PM4_BUFFER_CNTL
mdefine_line|#define PM4_BUFFER_CNTL&t;&t;&t;&t;0x0704
DECL|macro|PM4_BUFFER_WM_CNTL
mdefine_line|#define PM4_BUFFER_WM_CNTL&t;&t;&t;0x0708
DECL|macro|PM4_BUFFER_DL_RPTR_ADDR
mdefine_line|#define PM4_BUFFER_DL_RPTR_ADDR&t;&t;&t;0x070c
DECL|macro|PM4_BUFFER_DL_RPTR
mdefine_line|#define PM4_BUFFER_DL_RPTR&t;&t;&t;0x0710
DECL|macro|PM4_BUFFER_DL_WPTR
mdefine_line|#define PM4_BUFFER_DL_WPTR&t;&t;&t;0x0714
DECL|macro|PM4_VC_FPU_SETUP
mdefine_line|#define PM4_VC_FPU_SETUP&t;&t;&t;0x071c
DECL|macro|PM4_FPU_CNTL
mdefine_line|#define PM4_FPU_CNTL&t;&t;&t;&t;0x0720
DECL|macro|PM4_VC_FORMAT
mdefine_line|#define PM4_VC_FORMAT&t;&t;&t;&t;0x0724
DECL|macro|PM4_VC_CNTL
mdefine_line|#define PM4_VC_CNTL&t;&t;&t;&t;0x0728
DECL|macro|PM4_VC_I01
mdefine_line|#define PM4_VC_I01&t;&t;&t;&t;0x072c
DECL|macro|PM4_VC_VLOFF
mdefine_line|#define PM4_VC_VLOFF&t;&t;&t;&t;0x0730
DECL|macro|PM4_VC_VLSIZE
mdefine_line|#define PM4_VC_VLSIZE&t;&t;&t;&t;0x0734
DECL|macro|PM4_IW_INDOFF
mdefine_line|#define PM4_IW_INDOFF&t;&t;&t;&t;0x0738
DECL|macro|PM4_IW_INDSIZE
mdefine_line|#define PM4_IW_INDSIZE&t;&t;&t;&t;0x073c
DECL|macro|PM4_FPU_FPX0
mdefine_line|#define PM4_FPU_FPX0&t;&t;&t;&t;0x0740
DECL|macro|PM4_FPU_FPY0
mdefine_line|#define PM4_FPU_FPY0&t;&t;&t;&t;0x0744
DECL|macro|PM4_FPU_FPX1
mdefine_line|#define PM4_FPU_FPX1&t;&t;&t;&t;0x0748
DECL|macro|PM4_FPU_FPY1
mdefine_line|#define PM4_FPU_FPY1&t;&t;&t;&t;0x074c
DECL|macro|PM4_FPU_FPX2
mdefine_line|#define PM4_FPU_FPX2&t;&t;&t;&t;0x0750
DECL|macro|PM4_FPU_FPY2
mdefine_line|#define PM4_FPU_FPY2&t;&t;&t;&t;0x0754
DECL|macro|PM4_FPU_FPY3
mdefine_line|#define PM4_FPU_FPY3&t;&t;&t;&t;0x0758
DECL|macro|PM4_FPU_FPY4
mdefine_line|#define PM4_FPU_FPY4&t;&t;&t;&t;0x075c
DECL|macro|PM4_FPU_FPY5
mdefine_line|#define PM4_FPU_FPY5&t;&t;&t;&t;0x0760
DECL|macro|PM4_FPU_FPY6
mdefine_line|#define PM4_FPU_FPY6&t;&t;&t;&t;0x0764
DECL|macro|PM4_FPU_FPR
mdefine_line|#define PM4_FPU_FPR&t;&t;&t;&t;0x0768
DECL|macro|PM4_FPU_FPG
mdefine_line|#define PM4_FPU_FPG&t;&t;&t;&t;0x076c
DECL|macro|PM4_FPU_FPB
mdefine_line|#define PM4_FPU_FPB&t;&t;&t;&t;0x0770
DECL|macro|PM4_FPU_FPA
mdefine_line|#define PM4_FPU_FPA&t;&t;&t;&t;0x0774
DECL|macro|PM4_FPU_INTXY0
mdefine_line|#define PM4_FPU_INTXY0&t;&t;&t;&t;0x0780
DECL|macro|PM4_FPU_INTXY1
mdefine_line|#define PM4_FPU_INTXY1&t;&t;&t;&t;0x0784
DECL|macro|PM4_FPU_INTXY2
mdefine_line|#define PM4_FPU_INTXY2&t;&t;&t;&t;0x0788
DECL|macro|PM4_FPU_INTARGB
mdefine_line|#define PM4_FPU_INTARGB&t;&t;&t;&t;0x078c
DECL|macro|PM4_FPU_FPTWICEAREA
mdefine_line|#define PM4_FPU_FPTWICEAREA&t;&t;&t;0x0790
DECL|macro|PM4_FPU_DMAJOR01
mdefine_line|#define PM4_FPU_DMAJOR01&t;&t;&t;0x0794
DECL|macro|PM4_FPU_DMAJOR12
mdefine_line|#define PM4_FPU_DMAJOR12&t;&t;&t;0x0798
DECL|macro|PM4_FPU_DMAJOR02
mdefine_line|#define PM4_FPU_DMAJOR02&t;&t;&t;0x079c
DECL|macro|PM4_FPU_STAT
mdefine_line|#define PM4_FPU_STAT&t;&t;&t;&t;0x07a0
DECL|macro|PM4_STAT
mdefine_line|#define PM4_STAT&t;&t;&t;&t;0x07b8
DECL|macro|PM4_TEST_CNTL
mdefine_line|#define PM4_TEST_CNTL&t;&t;&t;&t;0x07d0
DECL|macro|PM4_MICROCODE_ADDR
mdefine_line|#define PM4_MICROCODE_ADDR&t;&t;&t;0x07d4
DECL|macro|PM4_MICROCODE_RADDR
mdefine_line|#define PM4_MICROCODE_RADDR&t;&t;&t;0x07d8
DECL|macro|PM4_MICROCODE_DATAH
mdefine_line|#define PM4_MICROCODE_DATAH&t;&t;&t;0x07dc
DECL|macro|PM4_MICROCODE_DATAL
mdefine_line|#define PM4_MICROCODE_DATAL&t;&t;&t;0x07e0
DECL|macro|PM4_CMDFIFO_ADDR
mdefine_line|#define PM4_CMDFIFO_ADDR&t;&t;&t;0x07e4
DECL|macro|PM4_CMDFIFO_DATAH
mdefine_line|#define PM4_CMDFIFO_DATAH&t;&t;&t;0x07e8
DECL|macro|PM4_CMDFIFO_DATAL
mdefine_line|#define PM4_CMDFIFO_DATAL&t;&t;&t;0x07ec
DECL|macro|PM4_BUFFER_ADDR
mdefine_line|#define PM4_BUFFER_ADDR&t;&t;&t;&t;0x07f0
DECL|macro|PM4_BUFFER_DATAH
mdefine_line|#define PM4_BUFFER_DATAH&t;&t;&t;0x07f4
DECL|macro|PM4_BUFFER_DATAL
mdefine_line|#define PM4_BUFFER_DATAL&t;&t;&t;0x07f8
DECL|macro|PM4_MICRO_CNTL
mdefine_line|#define PM4_MICRO_CNTL&t;&t;&t;&t;0x07fc
DECL|macro|CAP0_TRIG_CNTL
mdefine_line|#define CAP0_TRIG_CNTL&t;&t;&t;&t;0x0950
DECL|macro|CAP1_TRIG_CNTL
mdefine_line|#define CAP1_TRIG_CNTL&t;&t;&t;&t;0x09c0
multiline_comment|/******************************************************************************&n; *                  GUI Block Memory Mapped Registers                         *&n; *                     These registers are FIFOed.                            *&n; *****************************************************************************/
DECL|macro|PM4_FIFO_DATA_EVEN
mdefine_line|#define PM4_FIFO_DATA_EVEN&t;&t;&t;0x1000
DECL|macro|PM4_FIFO_DATA_ODD
mdefine_line|#define PM4_FIFO_DATA_ODD&t;&t;&t;0x1004
DECL|macro|DST_OFFSET
mdefine_line|#define DST_OFFSET&t;&t;&t;&t;0x1404
DECL|macro|DST_PITCH
mdefine_line|#define DST_PITCH&t;&t;&t;&t;0x1408
DECL|macro|DST_WIDTH
mdefine_line|#define DST_WIDTH&t;&t;&t;&t;0x140c
DECL|macro|DST_HEIGHT
mdefine_line|#define DST_HEIGHT&t;&t;&t;&t;0x1410
DECL|macro|SRC_X
mdefine_line|#define SRC_X&t;&t;&t;&t;&t;0x1414
DECL|macro|SRC_Y
mdefine_line|#define SRC_Y&t;&t;&t;&t;&t;0x1418
DECL|macro|DST_X
mdefine_line|#define DST_X&t;&t;&t;&t;&t;0x141c
DECL|macro|DST_Y
mdefine_line|#define DST_Y&t;&t;&t;&t;&t;0x1420
DECL|macro|SRC_PITCH_OFFSET
mdefine_line|#define SRC_PITCH_OFFSET&t;&t;&t;0x1428
DECL|macro|DST_PITCH_OFFSET
mdefine_line|#define DST_PITCH_OFFSET&t;&t;&t;0x142c
DECL|macro|SRC_Y_X
mdefine_line|#define SRC_Y_X&t;&t;&t;&t;&t;0x1434
DECL|macro|DST_Y_X
mdefine_line|#define DST_Y_X&t;&t;&t;&t;&t;0x1438
DECL|macro|DST_HEIGHT_WIDTH
mdefine_line|#define DST_HEIGHT_WIDTH&t;&t;&t;0x143c
DECL|macro|DP_GUI_MASTER_CNTL
mdefine_line|#define DP_GUI_MASTER_CNTL&t;&t;&t;0x146c
DECL|macro|BRUSH_SCALE
mdefine_line|#define BRUSH_SCALE&t;&t;&t;&t;0x1470
DECL|macro|BRUSH_Y_X
mdefine_line|#define BRUSH_Y_X&t;&t;&t;&t;0x1474
DECL|macro|DP_BRUSH_BKGD_CLR
mdefine_line|#define DP_BRUSH_BKGD_CLR&t;&t;&t;0x1478
DECL|macro|DP_BRUSH_FRGD_CLR
mdefine_line|#define DP_BRUSH_FRGD_CLR&t;&t;&t;0x147c
DECL|macro|DST_WIDTH_X
mdefine_line|#define DST_WIDTH_X&t;&t;&t;&t;0x1588
DECL|macro|DST_HEIGHT_WIDTH_8
mdefine_line|#define DST_HEIGHT_WIDTH_8&t;&t;&t;0x158c
DECL|macro|SRC_X_Y
mdefine_line|#define SRC_X_Y&t;&t;&t;&t;&t;0x1590
DECL|macro|DST_X_Y
mdefine_line|#define DST_X_Y&t;&t;&t;&t;&t;0x1594
DECL|macro|DST_WIDTH_HEIGHT
mdefine_line|#define DST_WIDTH_HEIGHT&t;&t;&t;0x1598
DECL|macro|DST_WIDTH_X_INCY
mdefine_line|#define DST_WIDTH_X_INCY&t;&t;&t;0x159c
DECL|macro|DST_HEIGHT_Y
mdefine_line|#define DST_HEIGHT_Y&t;&t;&t;&t;0x15a0
DECL|macro|DST_X_SUB
mdefine_line|#define DST_X_SUB&t;&t;&t;&t;0x15a4
DECL|macro|DST_Y_SUB
mdefine_line|#define DST_Y_SUB&t;&t;&t;&t;0x15a8
DECL|macro|SRC_OFFSET
mdefine_line|#define SRC_OFFSET&t;&t;&t;&t;0x15ac
DECL|macro|SRC_PITCH
mdefine_line|#define SRC_PITCH&t;&t;&t;&t;0x15b0
DECL|macro|DST_HEIGHT_WIDTH_BW
mdefine_line|#define DST_HEIGHT_WIDTH_BW&t;&t;&t;0x15b4
DECL|macro|CLR_CMP_CNTL
mdefine_line|#define CLR_CMP_CNTL&t;&t;&t;&t;0x15c0
DECL|macro|CLR_CMP_CLR_SRC
mdefine_line|#define CLR_CMP_CLR_SRC&t;&t;&t;&t;0x15c4
DECL|macro|CLR_CMP_CLR_DST
mdefine_line|#define CLR_CMP_CLR_DST&t;&t;&t;&t;0x15c8
DECL|macro|CLR_CMP_MASK
mdefine_line|#define CLR_CMP_MASK&t;&t;&t;&t;0x15cc
DECL|macro|DP_SRC_FRGD_CLR
mdefine_line|#define DP_SRC_FRGD_CLR&t;&t;&t;&t;0x15d8
DECL|macro|DP_SRC_BKGD_CLR
mdefine_line|#define DP_SRC_BKGD_CLR&t;&t;&t;&t;0x15dc
DECL|macro|DST_BRES_ERR
mdefine_line|#define DST_BRES_ERR&t;&t;&t;&t;0x1628
DECL|macro|DST_BRES_INC
mdefine_line|#define DST_BRES_INC&t;&t;&t;&t;0x162c
DECL|macro|DST_BRES_DEC
mdefine_line|#define DST_BRES_DEC&t;&t;&t;&t;0x1630
DECL|macro|DST_BRES_LNTH
mdefine_line|#define DST_BRES_LNTH&t;&t;&t;&t;0x1634
DECL|macro|DST_BRES_LNTH_SUB
mdefine_line|#define DST_BRES_LNTH_SUB&t;&t;&t;0x1638
DECL|macro|SC_LEFT
mdefine_line|#define SC_LEFT&t;&t;&t;&t;&t;0x1640
DECL|macro|SC_RIGHT
mdefine_line|#define SC_RIGHT&t;&t;&t;&t;0x1644
DECL|macro|SC_TOP
mdefine_line|#define SC_TOP&t;&t;&t;&t;&t;0x1648
DECL|macro|SC_BOTTOM
mdefine_line|#define SC_BOTTOM&t;&t;&t;&t;0x164c
DECL|macro|SRC_SC_RIGHT
mdefine_line|#define SRC_SC_RIGHT&t;&t;&t;&t;0x1654
DECL|macro|SRC_SC_BOTTOM
mdefine_line|#define SRC_SC_BOTTOM&t;&t;&t;&t;0x165c
DECL|macro|GUI_DEBUG0
mdefine_line|#define GUI_DEBUG0&t;&t;&t;&t;0x16a0
DECL|macro|GUI_DEBUG1
mdefine_line|#define GUI_DEBUG1&t;&t;&t;&t;0x16a4
DECL|macro|GUI_TIMEOUT
mdefine_line|#define GUI_TIMEOUT&t;&t;&t;&t;0x16b0
DECL|macro|GUI_TIMEOUT0
mdefine_line|#define GUI_TIMEOUT0&t;&t;&t;&t;0x16b4
DECL|macro|GUI_TIMEOUT1
mdefine_line|#define GUI_TIMEOUT1&t;&t;&t;&t;0x16b8
DECL|macro|GUI_PROBE
mdefine_line|#define GUI_PROBE&t;&t;&t;&t;0x16bc
DECL|macro|DP_CNTL
mdefine_line|#define DP_CNTL&t;&t;&t;&t;&t;0x16c0
DECL|macro|DP_DATATYPE
mdefine_line|#define DP_DATATYPE&t;&t;&t;&t;0x16c4
DECL|macro|DP_MIX
mdefine_line|#define DP_MIX&t;&t;&t;&t;&t;0x16c8
DECL|macro|DP_WRITE_MASK
mdefine_line|#define DP_WRITE_MASK&t;&t;&t;&t;0x16cc
DECL|macro|DP_CNTL_XDIR_YDIR_YMAJOR
mdefine_line|#define DP_CNTL_XDIR_YDIR_YMAJOR&t;&t;0x16d0
DECL|macro|DEFAULT_OFFSET
mdefine_line|#define DEFAULT_OFFSET&t;&t;&t;&t;0x16e0
DECL|macro|DEFAULT_PITCH
mdefine_line|#define DEFAULT_PITCH&t;&t;&t;&t;0x16e4
DECL|macro|DEFAULT_SC_BOTTOM_RIGHT
mdefine_line|#define DEFAULT_SC_BOTTOM_RIGHT&t;&t;&t;0x16e8
DECL|macro|SC_TOP_LEFT
mdefine_line|#define SC_TOP_LEFT&t;&t;&t;&t;0x16ec
DECL|macro|SC_BOTTOM_RIGHT
mdefine_line|#define SC_BOTTOM_RIGHT&t;&t;&t;&t;0x16f0
DECL|macro|SRC_SC_BOTTOM_RIGHT
mdefine_line|#define SRC_SC_BOTTOM_RIGHT&t;&t;&t;0x16f4
DECL|macro|WAIT_UNTIL
mdefine_line|#define WAIT_UNTIL&t;&t;&t;&t;0x1720
DECL|macro|CACHE_CNTL
mdefine_line|#define CACHE_CNTL&t;&t;&t;&t;0x1724
DECL|macro|GUI_STAT
mdefine_line|#define GUI_STAT&t;&t;&t;&t;0x1740
DECL|macro|PC_GUI_MODE
mdefine_line|#define PC_GUI_MODE&t;&t;&t;&t;0x1744
DECL|macro|PC_GUI_CTLSTAT
mdefine_line|#define PC_GUI_CTLSTAT&t;&t;&t;&t;0x1748
DECL|macro|PC_DEBUG_MODE
mdefine_line|#define PC_DEBUG_MODE&t;&t;&t;&t;0x1760
DECL|macro|BRES_DST_ERR_DEC
mdefine_line|#define BRES_DST_ERR_DEC&t;&t;&t;0x1780
DECL|macro|TRAIL_BRES_T12_ERR_DEC
mdefine_line|#define TRAIL_BRES_T12_ERR_DEC&t;&t;&t;0x1784
DECL|macro|TRAIL_BRES_T12_INC
mdefine_line|#define TRAIL_BRES_T12_INC&t;&t;&t;0x1788
DECL|macro|DP_T12_CNTL
mdefine_line|#define DP_T12_CNTL&t;&t;&t;&t;0x178c
DECL|macro|DST_BRES_T1_LNTH
mdefine_line|#define DST_BRES_T1_LNTH&t;&t;&t;0x1790
DECL|macro|DST_BRES_T2_LNTH
mdefine_line|#define DST_BRES_T2_LNTH&t;&t;&t;0x1794
DECL|macro|SCALE_SRC_HEIGHT_WIDTH
mdefine_line|#define SCALE_SRC_HEIGHT_WIDTH&t;&t;&t;0x1994
DECL|macro|SCALE_OFFSET_0
mdefine_line|#define SCALE_OFFSET_0&t;&t;&t;&t;0x1998
DECL|macro|SCALE_PITCH
mdefine_line|#define SCALE_PITCH&t;&t;&t;&t;0x199c
DECL|macro|SCALE_X_INC
mdefine_line|#define SCALE_X_INC&t;&t;&t;&t;0x19a0
DECL|macro|SCALE_Y_INC
mdefine_line|#define SCALE_Y_INC&t;&t;&t;&t;0x19a4
DECL|macro|SCALE_HACC
mdefine_line|#define SCALE_HACC&t;&t;&t;&t;0x19a8
DECL|macro|SCALE_VACC
mdefine_line|#define SCALE_VACC&t;&t;&t;&t;0x19ac
DECL|macro|SCALE_DST_X_Y
mdefine_line|#define SCALE_DST_X_Y&t;&t;&t;&t;0x19b0
DECL|macro|SCALE_DST_HEIGHT_WIDTH
mdefine_line|#define SCALE_DST_HEIGHT_WIDTH&t;&t;&t;0x19b4
DECL|macro|SCALE_3D_CNTL
mdefine_line|#define SCALE_3D_CNTL&t;&t;&t;&t;0x1a00
DECL|macro|SCALE_3D_DATATYPE
mdefine_line|#define SCALE_3D_DATATYPE&t;&t;&t;0x1a20
DECL|macro|SETUP_CNTL
mdefine_line|#define SETUP_CNTL&t;&t;&t;&t;0x1bc4
DECL|macro|SOLID_COLOR
mdefine_line|#define SOLID_COLOR&t;&t;&t;&t;0x1bc8
DECL|macro|WINDOW_XY_OFFSET
mdefine_line|#define WINDOW_XY_OFFSET&t;&t;&t;0x1bcc
DECL|macro|DRAW_LINE_POINT
mdefine_line|#define DRAW_LINE_POINT&t;&t;&t;&t;0x1bd0
DECL|macro|SETUP_CNTL_PM4
mdefine_line|#define SETUP_CNTL_PM4&t;&t;&t;&t;0x1bd4
DECL|macro|DST_PITCH_OFFSET_C
mdefine_line|#define DST_PITCH_OFFSET_C&t;&t;&t;0x1c80
DECL|macro|DP_GUI_MASTER_CNTL_C
mdefine_line|#define DP_GUI_MASTER_CNTL_C&t;&t;&t;0x1c84
DECL|macro|SC_TOP_LEFT_C
mdefine_line|#define SC_TOP_LEFT_C&t;&t;&t;&t;0x1c88
DECL|macro|SC_BOTTOM_RIGHT_C
mdefine_line|#define SC_BOTTOM_RIGHT_C&t;&t;&t;0x1c8c
DECL|macro|CLR_CMP_MASK_3D
mdefine_line|#define CLR_CMP_MASK_3D&t;&t;&t;&t;0x1A28
DECL|macro|MISC_3D_STATE_CNTL_REG
mdefine_line|#define MISC_3D_STATE_CNTL_REG&t;&t;&t;0x1CA0
DECL|macro|MC_SRC1_CNTL
mdefine_line|#define MC_SRC1_CNTL&t;&t;&t;&t;0x19D8
DECL|macro|TEX_CNTL
mdefine_line|#define TEX_CNTL&t;&t;&t;&t;0x1800
multiline_comment|/* CONSTANTS */
DECL|macro|GUI_ACTIVE
mdefine_line|#define GUI_ACTIVE&t;&t;&t;&t;0x80000000
DECL|macro|ENGINE_IDLE
mdefine_line|#define ENGINE_IDLE&t;&t;&t;&t;0x0
DECL|macro|PLL_WR_EN
mdefine_line|#define PLL_WR_EN&t;&t;&t;&t;0x00000080
DECL|macro|CLK_PIN_CNTL
mdefine_line|#define CLK_PIN_CNTL&t;&t;&t;&t;0x0001
DECL|macro|PPLL_CNTL
mdefine_line|#define PPLL_CNTL&t;&t;&t;&t;0x0002
DECL|macro|PPLL_REF_DIV
mdefine_line|#define PPLL_REF_DIV&t;&t;&t;&t;0x0003
DECL|macro|PPLL_DIV_0
mdefine_line|#define PPLL_DIV_0&t;&t;&t;&t;0x0004
DECL|macro|PPLL_DIV_1
mdefine_line|#define PPLL_DIV_1&t;&t;&t;&t;0x0005
DECL|macro|PPLL_DIV_2
mdefine_line|#define PPLL_DIV_2&t;&t;&t;&t;0x0006
DECL|macro|PPLL_DIV_3
mdefine_line|#define PPLL_DIV_3&t;&t;&t;&t;0x0007
DECL|macro|VCLK_ECP_CNTL
mdefine_line|#define VCLK_ECP_CNTL&t;&t;&t;&t;0x0008
DECL|macro|HTOTAL_CNTL
mdefine_line|#define HTOTAL_CNTL&t;&t;&t;&t;0x0009
DECL|macro|X_MPLL_REF_FB_DIV
mdefine_line|#define X_MPLL_REF_FB_DIV&t;&t;&t;0x000a
DECL|macro|XPLL_CNTL
mdefine_line|#define XPLL_CNTL&t;&t;&t;&t;0x000b
DECL|macro|XDLL_CNTL
mdefine_line|#define XDLL_CNTL&t;&t;&t;&t;0x000c
DECL|macro|XCLK_CNTL
mdefine_line|#define XCLK_CNTL&t;&t;&t;&t;0x000d
DECL|macro|MPLL_CNTL
mdefine_line|#define MPLL_CNTL&t;&t;&t;&t;0x000e
DECL|macro|MCLK_CNTL
mdefine_line|#define MCLK_CNTL&t;&t;&t;&t;0x000f
DECL|macro|AGP_PLL_CNTL
mdefine_line|#define AGP_PLL_CNTL&t;&t;&t;&t;0x0010
DECL|macro|FCP_CNTL
mdefine_line|#define FCP_CNTL&t;&t;&t;&t;0x0012
DECL|macro|PLL_TEST_CNTL
mdefine_line|#define PLL_TEST_CNTL&t;&t;&t;&t;0x0013
DECL|macro|PPLL_RESET
mdefine_line|#define PPLL_RESET&t;&t;&t;&t;0x01
DECL|macro|PPLL_ATOMIC_UPDATE_EN
mdefine_line|#define PPLL_ATOMIC_UPDATE_EN&t;&t;&t;0x10000
DECL|macro|PPLL_VGA_ATOMIC_UPDATE_EN
mdefine_line|#define PPLL_VGA_ATOMIC_UPDATE_EN&t;&t;0x20000
DECL|macro|PPLL_REF_DIV_MASK
mdefine_line|#define PPLL_REF_DIV_MASK&t;&t;&t;0x3FF
DECL|macro|PPLL_FB3_DIV_MASK
mdefine_line|#define PPLL_FB3_DIV_MASK&t;&t;&t;0x7FF
DECL|macro|PPLL_POST3_DIV_MASK
mdefine_line|#define PPLL_POST3_DIV_MASK&t;&t;&t;0x70000
DECL|macro|PPLL_ATOMIC_UPDATE_R
mdefine_line|#define PPLL_ATOMIC_UPDATE_R&t;&t;&t;0x8000
DECL|macro|PPLL_ATOMIC_UPDATE_W
mdefine_line|#define PPLL_ATOMIC_UPDATE_W&t;&t;&t;0x8000
DECL|macro|MEM_CFG_TYPE_MASK
mdefine_line|#define MEM_CFG_TYPE_MASK&t;&t;&t;0x3
DECL|macro|XCLK_SRC_SEL_MASK
mdefine_line|#define XCLK_SRC_SEL_MASK&t;&t;&t;0x7
DECL|macro|XPLL_FB_DIV_MASK
mdefine_line|#define XPLL_FB_DIV_MASK&t;&t;&t;0xFF00
DECL|macro|X_MPLL_REF_DIV_MASK
mdefine_line|#define X_MPLL_REF_DIV_MASK&t;&t;&t;0xFF
multiline_comment|/* CRTC control values (CRTC_GEN_CNTL) */
DECL|macro|CRTC_CSYNC_EN
mdefine_line|#define CRTC_CSYNC_EN&t;&t;&t;&t;0x00000010
DECL|macro|CRTC_PIX_WIDTH_MASK
mdefine_line|#define CRTC_PIX_WIDTH_MASK&t;&t;&t;0x00000700
DECL|macro|CRTC_PIX_WIDTH_4BPP
mdefine_line|#define CRTC_PIX_WIDTH_4BPP&t;&t;&t;0x00000100
DECL|macro|CRTC_PIX_WIDTH_8BPP
mdefine_line|#define CRTC_PIX_WIDTH_8BPP&t;&t;&t;0x00000200
DECL|macro|CRTC_PIX_WIDTH_15BPP
mdefine_line|#define CRTC_PIX_WIDTH_15BPP&t;&t;&t;0x00000300
DECL|macro|CRTC_PIX_WIDTH_16BPP
mdefine_line|#define CRTC_PIX_WIDTH_16BPP&t;&t;&t;0x00000400
DECL|macro|CRTC_PIX_WIDTH_24BPP
mdefine_line|#define CRTC_PIX_WIDTH_24BPP&t;&t;&t;0x00000500
DECL|macro|CRTC_PIX_WIDTH_32BPP
mdefine_line|#define CRTC_PIX_WIDTH_32BPP&t;&t;&t;0x00000600
multiline_comment|/* DAC_CNTL bit constants */
DECL|macro|DAC_8BIT_EN
mdefine_line|#define DAC_8BIT_EN&t;&t;&t;&t;0x00000100
DECL|macro|DAC_MASK
mdefine_line|#define DAC_MASK&t;&t;&t;&t;0xFF000000
DECL|macro|DAC_BLANKING
mdefine_line|#define DAC_BLANKING&t;&t;&t;&t;0x00000004
DECL|macro|DAC_RANGE_CNTL
mdefine_line|#define DAC_RANGE_CNTL&t;&t;&t;&t;0x00000003
DECL|macro|DAC_RANGE_CNTL
mdefine_line|#define DAC_RANGE_CNTL&t;&t;&t;&t;0x00000003
DECL|macro|DAC_PALETTE_ACCESS_CNTL
mdefine_line|#define DAC_PALETTE_ACCESS_CNTL&t;&t;&t;0x00000020
DECL|macro|DAC_PDWN
mdefine_line|#define DAC_PDWN&t;&t;&t;&t;0x00008000
multiline_comment|/* GEN_RESET_CNTL bit constants */
DECL|macro|SOFT_RESET_GUI
mdefine_line|#define SOFT_RESET_GUI&t;&t;&t;&t;0x00000001
DECL|macro|SOFT_RESET_VCLK
mdefine_line|#define SOFT_RESET_VCLK&t;&t;&t;&t;0x00000100
DECL|macro|SOFT_RESET_PCLK
mdefine_line|#define SOFT_RESET_PCLK&t;&t;&t;&t;0x00000200
DECL|macro|SOFT_RESET_ECP
mdefine_line|#define SOFT_RESET_ECP&t;&t;&t;&t;0x00000400
DECL|macro|SOFT_RESET_DISPENG_XCLK
mdefine_line|#define SOFT_RESET_DISPENG_XCLK&t;&t;&t;0x00000800
multiline_comment|/* PC_GUI_CTLSTAT bit constants */
DECL|macro|PC_BUSY_INIT
mdefine_line|#define PC_BUSY_INIT&t;&t;&t;&t;0x10000000                 
DECL|macro|PC_BUSY_GUI
mdefine_line|#define PC_BUSY_GUI&t;&t;&t;&t;0x20000000                 
DECL|macro|PC_BUSY_NGUI
mdefine_line|#define PC_BUSY_NGUI&t;&t;&t;&t;0x40000000
DECL|macro|PC_BUSY
mdefine_line|#define PC_BUSY&t;&t;&t;&t;&t;0x80000000
DECL|macro|BUS_MASTER_DIS
mdefine_line|#define BUS_MASTER_DIS&t;&t;&t;&t;0x00000040
DECL|macro|PM4_BUFFER_CNTL_NONPM4
mdefine_line|#define PM4_BUFFER_CNTL_NONPM4&t;&t;&t;0x00000000
multiline_comment|/* DP_DATATYPE bit constants */
DECL|macro|DST_8BPP
mdefine_line|#define DST_8BPP&t;&t;&t;&t;0x00000002
DECL|macro|DST_15BPP
mdefine_line|#define DST_15BPP&t;&t;&t;&t;0x00000003
DECL|macro|DST_16BPP
mdefine_line|#define DST_16BPP&t;&t;&t;&t;0x00000004
DECL|macro|DST_24BPP
mdefine_line|#define DST_24BPP&t;&t;&t;&t;0x00000005
DECL|macro|DST_32BPP
mdefine_line|#define DST_32BPP&t;&t;&t;&t;0x00000006
DECL|macro|BRUSH_SOLIDCOLOR
mdefine_line|#define BRUSH_SOLIDCOLOR&t;&t;&t;0x00000d00
multiline_comment|/* DP_GUI_MASTER_CNTL bit constants */
DECL|macro|GMC_SRC_PITCH_OFFSET_DEFAULT
mdefine_line|#define&t;GMC_SRC_PITCH_OFFSET_DEFAULT&t;&t;0x00000000
DECL|macro|GMC_DST_PITCH_OFFSET_DEFAULT
mdefine_line|#define GMC_DST_PITCH_OFFSET_DEFAULT&t;&t;0x00000000
DECL|macro|GMC_SRC_CLIP_DEFAULT
mdefine_line|#define GMC_SRC_CLIP_DEFAULT&t;&t;&t;0x00000000
DECL|macro|GMC_DST_CLIP_DEFAULT
mdefine_line|#define GMC_DST_CLIP_DEFAULT&t;&t;&t;0x00000000
DECL|macro|GMC_BRUSH_SOLIDCOLOR
mdefine_line|#define GMC_BRUSH_SOLIDCOLOR&t;&t;&t;0x000000d0
DECL|macro|GMC_SRC_DSTCOLOR
mdefine_line|#define GMC_SRC_DSTCOLOR&t;&t;&t;0x00003000
DECL|macro|GMC_BYTE_ORDER_MSB_TO_LSB
mdefine_line|#define GMC_BYTE_ORDER_MSB_TO_LSB&t;&t;0x00000000
DECL|macro|GMC_DP_SRC_RECT
mdefine_line|#define GMC_DP_SRC_RECT&t;&t;&t;&t;0x02000000
DECL|macro|GMC_3D_FCN_EN_CLR
mdefine_line|#define GMC_3D_FCN_EN_CLR&t;&t;&t;0x00000000
DECL|macro|GMC_AUX_CLIP_CLEAR
mdefine_line|#define GMC_AUX_CLIP_CLEAR&t;&t;&t;0x20000000
DECL|macro|GMC_DST_CLR_CMP_FCN_CLEAR
mdefine_line|#define GMC_DST_CLR_CMP_FCN_CLEAR&t;&t;0x10000000
DECL|macro|GMC_WRITE_MASK_SET
mdefine_line|#define GMC_WRITE_MASK_SET&t;&t;&t;0x40000000
DECL|macro|GMC_DP_CONVERSION_TEMP_6500
mdefine_line|#define GMC_DP_CONVERSION_TEMP_6500&t;&t;0x00000000
multiline_comment|/* DP_GUI_MASTER_CNTL ROP3 named constants */
DECL|macro|ROP3_PATCOPY
mdefine_line|#define&t;ROP3_PATCOPY&t;&t;&t;&t;0x00f00000
DECL|macro|ROP3_SRCCOPY
mdefine_line|#define ROP3_SRCCOPY&t;&t;&t;&t;0x00cc0000
DECL|macro|SRC_DSTCOLOR
mdefine_line|#define SRC_DSTCOLOR&t;&t;&t;&t;0x00030000
multiline_comment|/* DP_CNTL bit constants */
DECL|macro|DST_X_RIGHT_TO_LEFT
mdefine_line|#define DST_X_RIGHT_TO_LEFT&t;&t;&t;0x00000000
DECL|macro|DST_X_LEFT_TO_RIGHT
mdefine_line|#define DST_X_LEFT_TO_RIGHT&t;&t;&t;0x00000001
DECL|macro|DST_Y_BOTTOM_TO_TOP
mdefine_line|#define DST_Y_BOTTOM_TO_TOP&t;&t;&t;0x00000000
DECL|macro|DST_Y_TOP_TO_BOTTOM
mdefine_line|#define DST_Y_TOP_TO_BOTTOM&t;&t;&t;0x00000002
DECL|macro|DST_X_MAJOR
mdefine_line|#define DST_X_MAJOR&t;&t;&t;&t;0x00000000
DECL|macro|DST_Y_MAJOR
mdefine_line|#define DST_Y_MAJOR&t;&t;&t;&t;0x00000004
DECL|macro|DST_X_TILE
mdefine_line|#define DST_X_TILE&t;&t;&t;&t;0x00000008
DECL|macro|DST_Y_TILE
mdefine_line|#define DST_Y_TILE&t;&t;&t;&t;0x00000010
DECL|macro|DST_LAST_PEL
mdefine_line|#define DST_LAST_PEL&t;&t;&t;&t;0x00000020
DECL|macro|DST_TRAIL_X_RIGHT_TO_LEFT
mdefine_line|#define DST_TRAIL_X_RIGHT_TO_LEFT&t;&t;0x00000000
DECL|macro|DST_TRAIL_X_LEFT_TO_RIGHT
mdefine_line|#define DST_TRAIL_X_LEFT_TO_RIGHT&t;&t;0x00000040
DECL|macro|DST_TRAP_FILL_RIGHT_TO_LEFT
mdefine_line|#define DST_TRAP_FILL_RIGHT_TO_LEFT&t;&t;0x00000000
DECL|macro|DST_TRAP_FILL_LEFT_TO_RIGHT
mdefine_line|#define DST_TRAP_FILL_LEFT_TO_RIGHT&t;&t;0x00000080
DECL|macro|DST_BRES_SIGN
mdefine_line|#define DST_BRES_SIGN&t;&t;&t;&t;0x00000100
DECL|macro|DST_HOST_BIG_ENDIAN_EN
mdefine_line|#define DST_HOST_BIG_ENDIAN_EN&t;&t;&t;0x00000200
DECL|macro|DST_POLYLINE_NONLAST
mdefine_line|#define DST_POLYLINE_NONLAST&t;&t;&t;0x00008000
DECL|macro|DST_RASTER_STALL
mdefine_line|#define DST_RASTER_STALL&t;&t;&t;0x00010000
DECL|macro|DST_POLY_EDGE
mdefine_line|#define DST_POLY_EDGE&t;&t;&t;&t;0x00040000
multiline_comment|/* DP_MIX bit constants */
DECL|macro|DP_SRC_RECT
mdefine_line|#define DP_SRC_RECT&t;&t;&t;&t;0x00000200
DECL|macro|DP_SRC_HOST
mdefine_line|#define DP_SRC_HOST&t;&t;&t;&t;0x00000300
DECL|macro|DP_SRC_HOST_BYTEALIGN
mdefine_line|#define DP_SRC_HOST_BYTEALIGN&t;&t;&t;0x00000400
multiline_comment|/* LVDS_GEN_CNTL constants */
DECL|macro|LVDS_BL_MOD_LEVEL_MASK
mdefine_line|#define LVDS_BL_MOD_LEVEL_MASK&t;&t;&t;0x0000ff00
DECL|macro|LVDS_BL_MOD_LEVEL_SHIFT
mdefine_line|#define LVDS_BL_MOD_LEVEL_SHIFT&t;&t;&t;8
DECL|macro|LVDS_BL_MOD_EN
mdefine_line|#define LVDS_BL_MOD_EN&t;&t;&t;&t;0x00010000
DECL|macro|LVDS_DIGION
mdefine_line|#define LVDS_DIGION&t;&t;&t;&t;0x00040000
DECL|macro|LVDS_BLON
mdefine_line|#define LVDS_BLON&t;&t;&t;&t;0x00080000
macro_line|#endif /* REG_RAGE128_H */
eof
