macro_line|#ifndef _RADEON_H
DECL|macro|_RADEON_H
mdefine_line|#define _RADEON_H
multiline_comment|/* radeon PCI ids */
DECL|macro|PCI_DEVICE_ID_RADEON_QD
mdefine_line|#define PCI_DEVICE_ID_RADEON_QD&t;&t;0x5144
DECL|macro|PCI_DEVICE_ID_RADEON_QE
mdefine_line|#define PCI_DEVICE_ID_RADEON_QE&t;&t;0x5145
DECL|macro|PCI_DEVICE_ID_RADEON_QF
mdefine_line|#define PCI_DEVICE_ID_RADEON_QF&t;&t;0x5146
DECL|macro|PCI_DEVICE_ID_RADEON_QG
mdefine_line|#define PCI_DEVICE_ID_RADEON_QG&t;&t;0x5147
DECL|macro|RADEON_REGSIZE
mdefine_line|#define RADEON_REGSIZE&t;&t;&t;0x4000
DECL|macro|MM_INDEX
mdefine_line|#define MM_INDEX                               0x0000  
DECL|macro|MM_DATA
mdefine_line|#define MM_DATA                                0x0004  
DECL|macro|BUS_CNTL
mdefine_line|#define BUS_CNTL                               0x0030  
DECL|macro|HI_STAT
mdefine_line|#define HI_STAT                                0x004C  
DECL|macro|BUS_CNTL1
mdefine_line|#define BUS_CNTL1                              0x0034
DECL|macro|I2C_CNTL_1
mdefine_line|#define I2C_CNTL_1&t;&t;&t;       0x0094  
DECL|macro|CONFIG_CNTL
mdefine_line|#define CONFIG_CNTL                            0x00E0  
DECL|macro|CONFIG_MEMSIZE
mdefine_line|#define CONFIG_MEMSIZE                         0x00F8  
DECL|macro|CONFIG_APER_0_BASE
mdefine_line|#define CONFIG_APER_0_BASE                     0x0100  
DECL|macro|CONFIG_APER_1_BASE
mdefine_line|#define CONFIG_APER_1_BASE                     0x0104  
DECL|macro|CONFIG_APER_SIZE
mdefine_line|#define CONFIG_APER_SIZE                       0x0108  
DECL|macro|CONFIG_REG_1_BASE
mdefine_line|#define CONFIG_REG_1_BASE                      0x010C  
DECL|macro|CONFIG_REG_APER_SIZE
mdefine_line|#define CONFIG_REG_APER_SIZE                   0x0110  
DECL|macro|PAD_AGPINPUT_DELAY
mdefine_line|#define PAD_AGPINPUT_DELAY                     0x0164  
DECL|macro|PAD_CTLR_STRENGTH
mdefine_line|#define PAD_CTLR_STRENGTH                      0x0168  
DECL|macro|PAD_CTLR_UPDATE
mdefine_line|#define PAD_CTLR_UPDATE                        0x016C
DECL|macro|AGP_CNTL
mdefine_line|#define AGP_CNTL                               0x0174
DECL|macro|BM_STATUS
mdefine_line|#define BM_STATUS                              0x0160
DECL|macro|CAP0_TRIG_CNTL
mdefine_line|#define CAP0_TRIG_CNTL&t;&t;&t;       0x0950
DECL|macro|VIPH_CONTROL
mdefine_line|#define VIPH_CONTROL&t;&t;&t;       0x0C40
DECL|macro|VENDOR_ID
mdefine_line|#define VENDOR_ID                              0x0F00  
DECL|macro|DEVICE_ID
mdefine_line|#define DEVICE_ID                              0x0F02  
DECL|macro|COMMAND
mdefine_line|#define COMMAND                                0x0F04  
DECL|macro|STATUS
mdefine_line|#define STATUS                                 0x0F06  
DECL|macro|REVISION_ID
mdefine_line|#define REVISION_ID                            0x0F08  
DECL|macro|REGPROG_INF
mdefine_line|#define REGPROG_INF                            0x0F09  
DECL|macro|SUB_CLASS
mdefine_line|#define SUB_CLASS                              0x0F0A  
DECL|macro|BASE_CODE
mdefine_line|#define BASE_CODE                              0x0F0B  
DECL|macro|CACHE_LINE
mdefine_line|#define CACHE_LINE                             0x0F0C  
DECL|macro|LATENCY
mdefine_line|#define LATENCY                                0x0F0D  
DECL|macro|HEADER
mdefine_line|#define HEADER                                 0x0F0E  
DECL|macro|BIST
mdefine_line|#define BIST                                   0x0F0F  
DECL|macro|REG_MEM_BASE
mdefine_line|#define REG_MEM_BASE                           0x0F10  
DECL|macro|REG_IO_BASE
mdefine_line|#define REG_IO_BASE                            0x0F14  
DECL|macro|REG_REG_BASE
mdefine_line|#define REG_REG_BASE                           0x0F18
DECL|macro|ADAPTER_ID
mdefine_line|#define ADAPTER_ID                             0x0F2C
DECL|macro|BIOS_ROM
mdefine_line|#define BIOS_ROM                               0x0F30
DECL|macro|CAPABILITIES_PTR
mdefine_line|#define CAPABILITIES_PTR                       0x0F34  
DECL|macro|INTERRUPT_LINE
mdefine_line|#define INTERRUPT_LINE                         0x0F3C  
DECL|macro|INTERRUPT_PIN
mdefine_line|#define INTERRUPT_PIN                          0x0F3D  
DECL|macro|MIN_GRANT
mdefine_line|#define MIN_GRANT                              0x0F3E  
DECL|macro|MAX_LATENCY
mdefine_line|#define MAX_LATENCY                            0x0F3F  
DECL|macro|ADAPTER_ID_W
mdefine_line|#define ADAPTER_ID_W                           0x0F4C  
DECL|macro|PMI_CAP_ID
mdefine_line|#define PMI_CAP_ID                             0x0F50  
DECL|macro|PMI_NXT_CAP_PTR
mdefine_line|#define PMI_NXT_CAP_PTR                        0x0F51  
DECL|macro|PMI_PMC_REG
mdefine_line|#define PMI_PMC_REG                            0x0F52  
DECL|macro|PM_STATUS
mdefine_line|#define PM_STATUS                              0x0F54  
DECL|macro|PMI_DATA
mdefine_line|#define PMI_DATA                               0x0F57  
DECL|macro|AGP_CAP_ID
mdefine_line|#define AGP_CAP_ID                             0x0F58  
DECL|macro|AGP_STATUS
mdefine_line|#define AGP_STATUS                             0x0F5C  
DECL|macro|AGP_COMMAND
mdefine_line|#define AGP_COMMAND                            0x0F60  
DECL|macro|AIC_CTRL
mdefine_line|#define AIC_CTRL                               0x01D0
DECL|macro|AIC_STAT
mdefine_line|#define AIC_STAT                               0x01D4
DECL|macro|AIC_PT_BASE
mdefine_line|#define AIC_PT_BASE                            0x01D8
DECL|macro|AIC_LO_ADDR
mdefine_line|#define AIC_LO_ADDR                            0x01DC  
DECL|macro|AIC_HI_ADDR
mdefine_line|#define AIC_HI_ADDR                            0x01E0  
DECL|macro|AIC_TLB_ADDR
mdefine_line|#define AIC_TLB_ADDR                           0x01E4  
DECL|macro|AIC_TLB_DATA
mdefine_line|#define AIC_TLB_DATA                           0x01E8  
DECL|macro|DAC_CNTL
mdefine_line|#define DAC_CNTL                               0x0058  
DECL|macro|CRTC_GEN_CNTL
mdefine_line|#define CRTC_GEN_CNTL                          0x0050  
DECL|macro|MEM_CNTL
mdefine_line|#define MEM_CNTL                               0x0140  
DECL|macro|EXT_MEM_CNTL
mdefine_line|#define EXT_MEM_CNTL                           0x0144  
DECL|macro|MC_AGP_LOCATION
mdefine_line|#define MC_AGP_LOCATION                        0x014C  
DECL|macro|MEM_IO_CNTL_A0
mdefine_line|#define MEM_IO_CNTL_A0                         0x0178  
DECL|macro|MEM_INIT_LATENCY_TIMER
mdefine_line|#define MEM_INIT_LATENCY_TIMER                 0x0154  
DECL|macro|MEM_SDRAM_MODE_REG
mdefine_line|#define MEM_SDRAM_MODE_REG                     0x0158  
DECL|macro|AGP_BASE
mdefine_line|#define AGP_BASE                               0x0170  
DECL|macro|MEM_IO_CNTL_A1
mdefine_line|#define MEM_IO_CNTL_A1                         0x017C  
DECL|macro|MEM_IO_CNTL_B0
mdefine_line|#define MEM_IO_CNTL_B0                         0x0180
DECL|macro|MEM_IO_CNTL_B1
mdefine_line|#define MEM_IO_CNTL_B1                         0x0184
DECL|macro|MC_DEBUG
mdefine_line|#define MC_DEBUG                               0x0188
DECL|macro|MC_STATUS
mdefine_line|#define MC_STATUS                              0x0150  
DECL|macro|MEM_IO_OE_CNTL
mdefine_line|#define MEM_IO_OE_CNTL                         0x018C  
DECL|macro|MC_FB_LOCATION
mdefine_line|#define MC_FB_LOCATION                         0x0148  
DECL|macro|HOST_PATH_CNTL
mdefine_line|#define HOST_PATH_CNTL                         0x0130  
DECL|macro|MEM_VGA_WP_SEL
mdefine_line|#define MEM_VGA_WP_SEL                         0x0038  
DECL|macro|MEM_VGA_RP_SEL
mdefine_line|#define MEM_VGA_RP_SEL                         0x003C  
DECL|macro|HDP_DEBUG
mdefine_line|#define HDP_DEBUG                              0x0138  
DECL|macro|SW_SEMAPHORE
mdefine_line|#define SW_SEMAPHORE                           0x013C  
DECL|macro|SURFACE_CNTL
mdefine_line|#define SURFACE_CNTL                           0x0B00  
DECL|macro|SURFACE0_LOWER_BOUND
mdefine_line|#define SURFACE0_LOWER_BOUND                   0x0B04  
DECL|macro|SURFACE1_LOWER_BOUND
mdefine_line|#define SURFACE1_LOWER_BOUND                   0x0B14  
DECL|macro|SURFACE2_LOWER_BOUND
mdefine_line|#define SURFACE2_LOWER_BOUND                   0x0B24  
DECL|macro|SURFACE3_LOWER_BOUND
mdefine_line|#define SURFACE3_LOWER_BOUND                   0x0B34  
DECL|macro|SURFACE4_LOWER_BOUND
mdefine_line|#define SURFACE4_LOWER_BOUND                   0x0B44  
DECL|macro|SURFACE5_LOWER_BOUND
mdefine_line|#define SURFACE5_LOWER_BOUND                   0x0B54
DECL|macro|SURFACE6_LOWER_BOUND
mdefine_line|#define SURFACE6_LOWER_BOUND                   0x0B64
DECL|macro|SURFACE7_LOWER_BOUND
mdefine_line|#define SURFACE7_LOWER_BOUND                   0x0B74
DECL|macro|SURFACE0_UPPER_BOUND
mdefine_line|#define SURFACE0_UPPER_BOUND                   0x0B08  
DECL|macro|SURFACE1_UPPER_BOUND
mdefine_line|#define SURFACE1_UPPER_BOUND                   0x0B18  
DECL|macro|SURFACE2_UPPER_BOUND
mdefine_line|#define SURFACE2_UPPER_BOUND                   0x0B28  
DECL|macro|SURFACE3_UPPER_BOUND
mdefine_line|#define SURFACE3_UPPER_BOUND                   0x0B38  
DECL|macro|SURFACE4_UPPER_BOUND
mdefine_line|#define SURFACE4_UPPER_BOUND                   0x0B48  
DECL|macro|SURFACE5_UPPER_BOUND
mdefine_line|#define SURFACE5_UPPER_BOUND                   0x0B58  
DECL|macro|SURFACE6_UPPER_BOUND
mdefine_line|#define SURFACE6_UPPER_BOUND                   0x0B68  
DECL|macro|SURFACE7_UPPER_BOUND
mdefine_line|#define SURFACE7_UPPER_BOUND                   0x0B78  
DECL|macro|SURFACE0_INFO
mdefine_line|#define SURFACE0_INFO                          0x0B0C  
DECL|macro|SURFACE1_INFO
mdefine_line|#define SURFACE1_INFO                          0x0B1C  
DECL|macro|SURFACE2_INFO
mdefine_line|#define SURFACE2_INFO                          0x0B2C  
DECL|macro|SURFACE3_INFO
mdefine_line|#define SURFACE3_INFO                          0x0B3C  
DECL|macro|SURFACE4_INFO
mdefine_line|#define SURFACE4_INFO                          0x0B4C  
DECL|macro|SURFACE5_INFO
mdefine_line|#define SURFACE5_INFO                          0x0B5C  
DECL|macro|SURFACE6_INFO
mdefine_line|#define SURFACE6_INFO                          0x0B6C
DECL|macro|SURFACE7_INFO
mdefine_line|#define SURFACE7_INFO                          0x0B7C
DECL|macro|SURFACE_ACCESS_FLAGS
mdefine_line|#define SURFACE_ACCESS_FLAGS                   0x0BF8
DECL|macro|SURFACE_ACCESS_CLR
mdefine_line|#define SURFACE_ACCESS_CLR                     0x0BFC  
DECL|macro|GEN_INT_CNTL
mdefine_line|#define GEN_INT_CNTL                           0x0040  
DECL|macro|GEN_INT_STATUS
mdefine_line|#define GEN_INT_STATUS                         0x0044  
DECL|macro|CRTC_EXT_CNTL
mdefine_line|#define CRTC_EXT_CNTL                          0x0054
DECL|macro|RB3D_CNTL
mdefine_line|#define RB3D_CNTL&t;&t;&t;       0x1C3C  
DECL|macro|WAIT_UNTIL
mdefine_line|#define WAIT_UNTIL                             0x1720  
DECL|macro|ISYNC_CNTL
mdefine_line|#define ISYNC_CNTL                             0x1724  
DECL|macro|RBBM_GUICNTL
mdefine_line|#define RBBM_GUICNTL                           0x172C  
DECL|macro|RBBM_STATUS
mdefine_line|#define RBBM_STATUS                            0x0E40  
DECL|macro|RBBM_STATUS_alt_1
mdefine_line|#define RBBM_STATUS_alt_1                      0x1740  
DECL|macro|RBBM_CNTL
mdefine_line|#define RBBM_CNTL                              0x00EC  
DECL|macro|RBBM_CNTL_alt_1
mdefine_line|#define RBBM_CNTL_alt_1                        0x0E44  
DECL|macro|RBBM_SOFT_RESET
mdefine_line|#define RBBM_SOFT_RESET                        0x00F0  
DECL|macro|RBBM_SOFT_RESET_alt_1
mdefine_line|#define RBBM_SOFT_RESET_alt_1                  0x0E48  
DECL|macro|NQWAIT_UNTIL
mdefine_line|#define NQWAIT_UNTIL                           0x0E50  
DECL|macro|RBBM_DEBUG
mdefine_line|#define RBBM_DEBUG                             0x0E6C
DECL|macro|RBBM_CMDFIFO_ADDR
mdefine_line|#define RBBM_CMDFIFO_ADDR                      0x0E70
DECL|macro|RBBM_CMDFIFO_DATAL
mdefine_line|#define RBBM_CMDFIFO_DATAL                     0x0E74
DECL|macro|RBBM_CMDFIFO_DATAH
mdefine_line|#define RBBM_CMDFIFO_DATAH                     0x0E78  
DECL|macro|RBBM_CMDFIFO_STAT
mdefine_line|#define RBBM_CMDFIFO_STAT                      0x0E7C  
DECL|macro|CRTC_STATUS
mdefine_line|#define CRTC_STATUS                            0x005C  
DECL|macro|GPIO_VGA_DDC
mdefine_line|#define GPIO_VGA_DDC                           0x0060  
DECL|macro|GPIO_DVI_DDC
mdefine_line|#define GPIO_DVI_DDC                           0x0064  
DECL|macro|GPIO_MONID
mdefine_line|#define GPIO_MONID                             0x0068  
DECL|macro|PALETTE_INDEX
mdefine_line|#define PALETTE_INDEX                          0x00B0  
DECL|macro|PALETTE_DATA
mdefine_line|#define PALETTE_DATA                           0x00B4  
DECL|macro|PALETTE_30_DATA
mdefine_line|#define PALETTE_30_DATA                        0x00B8  
DECL|macro|CRTC_H_TOTAL_DISP
mdefine_line|#define CRTC_H_TOTAL_DISP                      0x0200  
DECL|macro|CRTC_H_SYNC_STRT_WID
mdefine_line|#define CRTC_H_SYNC_STRT_WID                   0x0204  
DECL|macro|CRTC_V_TOTAL_DISP
mdefine_line|#define CRTC_V_TOTAL_DISP                      0x0208  
DECL|macro|CRTC_V_SYNC_STRT_WID
mdefine_line|#define CRTC_V_SYNC_STRT_WID                   0x020C  
DECL|macro|CRTC_VLINE_CRNT_VLINE
mdefine_line|#define CRTC_VLINE_CRNT_VLINE                  0x0210  
DECL|macro|CRTC_CRNT_FRAME
mdefine_line|#define CRTC_CRNT_FRAME                        0x0214
DECL|macro|CRTC_GUI_TRIG_VLINE
mdefine_line|#define CRTC_GUI_TRIG_VLINE                    0x0218
DECL|macro|CRTC_DEBUG
mdefine_line|#define CRTC_DEBUG                             0x021C
DECL|macro|CRTC_OFFSET_RIGHT
mdefine_line|#define CRTC_OFFSET_RIGHT                      0x0220  
DECL|macro|CRTC_OFFSET
mdefine_line|#define CRTC_OFFSET                            0x0224  
DECL|macro|CRTC_OFFSET_CNTL
mdefine_line|#define CRTC_OFFSET_CNTL                       0x0228  
DECL|macro|CRTC_PITCH
mdefine_line|#define CRTC_PITCH                             0x022C  
DECL|macro|OVR_CLR
mdefine_line|#define OVR_CLR                                0x0230  
DECL|macro|OVR_WID_LEFT_RIGHT
mdefine_line|#define OVR_WID_LEFT_RIGHT                     0x0234  
DECL|macro|OVR_WID_TOP_BOTTOM
mdefine_line|#define OVR_WID_TOP_BOTTOM                     0x0238  
DECL|macro|DISPLAY_BASE_ADDR
mdefine_line|#define DISPLAY_BASE_ADDR                      0x023C  
DECL|macro|SNAPSHOT_VH_COUNTS
mdefine_line|#define SNAPSHOT_VH_COUNTS                     0x0240  
DECL|macro|SNAPSHOT_F_COUNT
mdefine_line|#define SNAPSHOT_F_COUNT                       0x0244  
DECL|macro|N_VIF_COUNT
mdefine_line|#define N_VIF_COUNT                            0x0248  
DECL|macro|SNAPSHOT_VIF_COUNT
mdefine_line|#define SNAPSHOT_VIF_COUNT                     0x024C  
DECL|macro|FP_CRTC_H_TOTAL_DISP
mdefine_line|#define FP_CRTC_H_TOTAL_DISP                   0x0250  
DECL|macro|FP_CRTC_V_TOTAL_DISP
mdefine_line|#define FP_CRTC_V_TOTAL_DISP                   0x0254  
DECL|macro|CRT_CRTC_H_SYNC_STRT_WID
mdefine_line|#define CRT_CRTC_H_SYNC_STRT_WID               0x0258
DECL|macro|CRT_CRTC_V_SYNC_STRT_WID
mdefine_line|#define CRT_CRTC_V_SYNC_STRT_WID               0x025C
DECL|macro|CUR_OFFSET
mdefine_line|#define CUR_OFFSET                             0x0260
DECL|macro|CUR_HORZ_VERT_POSN
mdefine_line|#define CUR_HORZ_VERT_POSN                     0x0264  
DECL|macro|CUR_HORZ_VERT_OFF
mdefine_line|#define CUR_HORZ_VERT_OFF                      0x0268  
DECL|macro|CUR_CLR0
mdefine_line|#define CUR_CLR0                               0x026C  
DECL|macro|CUR_CLR1
mdefine_line|#define CUR_CLR1                               0x0270  
DECL|macro|FP_HORZ_VERT_ACTIVE
mdefine_line|#define FP_HORZ_VERT_ACTIVE                    0x0278  
DECL|macro|CRTC_MORE_CNTL
mdefine_line|#define CRTC_MORE_CNTL                         0x027C  
DECL|macro|DAC_EXT_CNTL
mdefine_line|#define DAC_EXT_CNTL                           0x0280  
DECL|macro|FP_GEN_CNTL
mdefine_line|#define FP_GEN_CNTL                            0x0284  
DECL|macro|FP_HORZ_STRETCH
mdefine_line|#define FP_HORZ_STRETCH                        0x028C  
DECL|macro|FP_VERT_STRETCH
mdefine_line|#define FP_VERT_STRETCH                        0x0290  
DECL|macro|FP_H_SYNC_STRT_WID
mdefine_line|#define FP_H_SYNC_STRT_WID                     0x02C4  
DECL|macro|FP_V_SYNC_STRT_WID
mdefine_line|#define FP_V_SYNC_STRT_WID                     0x02C8  
DECL|macro|AUX_WINDOW_HORZ_CNTL
mdefine_line|#define AUX_WINDOW_HORZ_CNTL                   0x02D8  
DECL|macro|AUX_WINDOW_VERT_CNTL
mdefine_line|#define AUX_WINDOW_VERT_CNTL                   0x02DC  
DECL|macro|DDA_CONFIG
mdefine_line|#define DDA_CONFIG&t;&t;&t;       0x02e0
DECL|macro|DDA_ON_OFF
mdefine_line|#define DDA_ON_OFF&t;&t;&t;       0x02e4
DECL|macro|GRPH_BUFFER_CNTL
mdefine_line|#define GRPH_BUFFER_CNTL                       0x02F0
DECL|macro|VGA_BUFFER_CNTL
mdefine_line|#define VGA_BUFFER_CNTL                        0x02F4
DECL|macro|OV0_Y_X_START
mdefine_line|#define OV0_Y_X_START                          0x0400
DECL|macro|OV0_Y_X_END
mdefine_line|#define OV0_Y_X_END                            0x0404  
DECL|macro|OV0_PIPELINE_CNTL
mdefine_line|#define OV0_PIPELINE_CNTL                      0x0408  
DECL|macro|OV0_REG_LOAD_CNTL
mdefine_line|#define OV0_REG_LOAD_CNTL                      0x0410  
DECL|macro|OV0_SCALE_CNTL
mdefine_line|#define OV0_SCALE_CNTL                         0x0420  
DECL|macro|OV0_V_INC
mdefine_line|#define OV0_V_INC                              0x0424  
DECL|macro|OV0_P1_V_ACCUM_INIT
mdefine_line|#define OV0_P1_V_ACCUM_INIT                    0x0428  
DECL|macro|OV0_P23_V_ACCUM_INIT
mdefine_line|#define OV0_P23_V_ACCUM_INIT                   0x042C  
DECL|macro|OV0_P1_BLANK_LINES_AT_TOP
mdefine_line|#define OV0_P1_BLANK_LINES_AT_TOP              0x0430  
DECL|macro|OV0_P23_BLANK_LINES_AT_TOP
mdefine_line|#define OV0_P23_BLANK_LINES_AT_TOP             0x0434  
DECL|macro|OV0_BASE_ADDR
mdefine_line|#define OV0_BASE_ADDR                          0x043C  
DECL|macro|OV0_VID_BUF0_BASE_ADRS
mdefine_line|#define OV0_VID_BUF0_BASE_ADRS                 0x0440  
DECL|macro|OV0_VID_BUF1_BASE_ADRS
mdefine_line|#define OV0_VID_BUF1_BASE_ADRS                 0x0444  
DECL|macro|OV0_VID_BUF2_BASE_ADRS
mdefine_line|#define OV0_VID_BUF2_BASE_ADRS                 0x0448  
DECL|macro|OV0_VID_BUF3_BASE_ADRS
mdefine_line|#define OV0_VID_BUF3_BASE_ADRS                 0x044C  
DECL|macro|OV0_VID_BUF4_BASE_ADRS
mdefine_line|#define OV0_VID_BUF4_BASE_ADRS                 0x0450
DECL|macro|OV0_VID_BUF5_BASE_ADRS
mdefine_line|#define OV0_VID_BUF5_BASE_ADRS                 0x0454
DECL|macro|OV0_VID_BUF_PITCH0_VALUE
mdefine_line|#define OV0_VID_BUF_PITCH0_VALUE               0x0460
DECL|macro|OV0_VID_BUF_PITCH1_VALUE
mdefine_line|#define OV0_VID_BUF_PITCH1_VALUE               0x0464  
DECL|macro|OV0_AUTO_FLIP_CNTRL
mdefine_line|#define OV0_AUTO_FLIP_CNTRL                    0x0470  
DECL|macro|OV0_DEINTERLACE_PATTERN
mdefine_line|#define OV0_DEINTERLACE_PATTERN                0x0474  
DECL|macro|OV0_SUBMIT_HISTORY
mdefine_line|#define OV0_SUBMIT_HISTORY                     0x0478  
DECL|macro|OV0_H_INC
mdefine_line|#define OV0_H_INC                              0x0480  
DECL|macro|OV0_STEP_BY
mdefine_line|#define OV0_STEP_BY                            0x0484  
DECL|macro|OV0_P1_H_ACCUM_INIT
mdefine_line|#define OV0_P1_H_ACCUM_INIT                    0x0488  
DECL|macro|OV0_P23_H_ACCUM_INIT
mdefine_line|#define OV0_P23_H_ACCUM_INIT                   0x048C  
DECL|macro|OV0_P1_X_START_END
mdefine_line|#define OV0_P1_X_START_END                     0x0494  
DECL|macro|OV0_P2_X_START_END
mdefine_line|#define OV0_P2_X_START_END                     0x0498  
DECL|macro|OV0_P3_X_START_END
mdefine_line|#define OV0_P3_X_START_END                     0x049C  
DECL|macro|OV0_FILTER_CNTL
mdefine_line|#define OV0_FILTER_CNTL                        0x04A0  
DECL|macro|OV0_FOUR_TAP_COEF_0
mdefine_line|#define OV0_FOUR_TAP_COEF_0                    0x04B0  
DECL|macro|OV0_FOUR_TAP_COEF_1
mdefine_line|#define OV0_FOUR_TAP_COEF_1                    0x04B4  
DECL|macro|OV0_FOUR_TAP_COEF_2
mdefine_line|#define OV0_FOUR_TAP_COEF_2                    0x04B8
DECL|macro|OV0_FOUR_TAP_COEF_3
mdefine_line|#define OV0_FOUR_TAP_COEF_3                    0x04BC
DECL|macro|OV0_FOUR_TAP_COEF_4
mdefine_line|#define OV0_FOUR_TAP_COEF_4                    0x04C0
DECL|macro|OV0_FLAG_CNTRL
mdefine_line|#define OV0_FLAG_CNTRL                         0x04DC  
DECL|macro|OV0_SLICE_CNTL
mdefine_line|#define OV0_SLICE_CNTL                         0x04E0  
DECL|macro|OV0_VID_KEY_CLR_LOW
mdefine_line|#define OV0_VID_KEY_CLR_LOW                    0x04E4  
DECL|macro|OV0_VID_KEY_CLR_HIGH
mdefine_line|#define OV0_VID_KEY_CLR_HIGH                   0x04E8  
DECL|macro|OV0_GRPH_KEY_CLR_LOW
mdefine_line|#define OV0_GRPH_KEY_CLR_LOW                   0x04EC  
DECL|macro|OV0_GRPH_KEY_CLR_HIGH
mdefine_line|#define OV0_GRPH_KEY_CLR_HIGH                  0x04F0  
DECL|macro|OV0_KEY_CNTL
mdefine_line|#define OV0_KEY_CNTL                           0x04F4  
DECL|macro|OV0_TEST
mdefine_line|#define OV0_TEST                               0x04F8  
DECL|macro|SUBPIC_CNTL
mdefine_line|#define SUBPIC_CNTL                            0x0540  
DECL|macro|SUBPIC_DEFCOLCON
mdefine_line|#define SUBPIC_DEFCOLCON                       0x0544  
DECL|macro|SUBPIC_Y_X_START
mdefine_line|#define SUBPIC_Y_X_START                       0x054C  
DECL|macro|SUBPIC_Y_X_END
mdefine_line|#define SUBPIC_Y_X_END                         0x0550  
DECL|macro|SUBPIC_V_INC
mdefine_line|#define SUBPIC_V_INC                           0x0554  
DECL|macro|SUBPIC_H_INC
mdefine_line|#define SUBPIC_H_INC                           0x0558  
DECL|macro|SUBPIC_BUF0_OFFSET
mdefine_line|#define SUBPIC_BUF0_OFFSET                     0x055C
DECL|macro|SUBPIC_BUF1_OFFSET
mdefine_line|#define SUBPIC_BUF1_OFFSET                     0x0560
DECL|macro|SUBPIC_LC0_OFFSET
mdefine_line|#define SUBPIC_LC0_OFFSET                      0x0564
DECL|macro|SUBPIC_LC1_OFFSET
mdefine_line|#define SUBPIC_LC1_OFFSET                      0x0568  
DECL|macro|SUBPIC_PITCH
mdefine_line|#define SUBPIC_PITCH                           0x056C  
DECL|macro|SUBPIC_BTN_HLI_COLCON
mdefine_line|#define SUBPIC_BTN_HLI_COLCON                  0x0570  
DECL|macro|SUBPIC_BTN_HLI_Y_X_START
mdefine_line|#define SUBPIC_BTN_HLI_Y_X_START               0x0574  
DECL|macro|SUBPIC_BTN_HLI_Y_X_END
mdefine_line|#define SUBPIC_BTN_HLI_Y_X_END                 0x0578  
DECL|macro|SUBPIC_PALETTE_INDEX
mdefine_line|#define SUBPIC_PALETTE_INDEX                   0x057C  
DECL|macro|SUBPIC_PALETTE_DATA
mdefine_line|#define SUBPIC_PALETTE_DATA                    0x0580  
DECL|macro|SUBPIC_H_ACCUM_INIT
mdefine_line|#define SUBPIC_H_ACCUM_INIT                    0x0584  
DECL|macro|SUBPIC_V_ACCUM_INIT
mdefine_line|#define SUBPIC_V_ACCUM_INIT                    0x0588  
DECL|macro|DISP_MISC_CNTL
mdefine_line|#define DISP_MISC_CNTL                         0x0D00  
DECL|macro|DAC_MACRO_CNTL
mdefine_line|#define DAC_MACRO_CNTL                         0x0D04  
DECL|macro|DISP_PWR_MAN
mdefine_line|#define DISP_PWR_MAN                           0x0D08  
DECL|macro|DISP_TEST_DEBUG_CNTL
mdefine_line|#define DISP_TEST_DEBUG_CNTL                   0x0D10  
DECL|macro|DISP_HW_DEBUG
mdefine_line|#define DISP_HW_DEBUG                          0x0D14  
DECL|macro|DAC_CRC_SIG1
mdefine_line|#define DAC_CRC_SIG1                           0x0D18
DECL|macro|DAC_CRC_SIG2
mdefine_line|#define DAC_CRC_SIG2                           0x0D1C
DECL|macro|OV0_LIN_TRANS_A
mdefine_line|#define OV0_LIN_TRANS_A                        0x0D20
DECL|macro|OV0_LIN_TRANS_B
mdefine_line|#define OV0_LIN_TRANS_B                        0x0D24  
DECL|macro|OV0_LIN_TRANS_C
mdefine_line|#define OV0_LIN_TRANS_C                        0x0D28  
DECL|macro|OV0_LIN_TRANS_D
mdefine_line|#define OV0_LIN_TRANS_D                        0x0D2C  
DECL|macro|OV0_LIN_TRANS_E
mdefine_line|#define OV0_LIN_TRANS_E                        0x0D30  
DECL|macro|OV0_LIN_TRANS_F
mdefine_line|#define OV0_LIN_TRANS_F                        0x0D34  
DECL|macro|OV0_GAMMA_0_F
mdefine_line|#define OV0_GAMMA_0_F                          0x0D40  
DECL|macro|OV0_GAMMA_10_1F
mdefine_line|#define OV0_GAMMA_10_1F                        0x0D44  
DECL|macro|OV0_GAMMA_20_3F
mdefine_line|#define OV0_GAMMA_20_3F                        0x0D48  
DECL|macro|OV0_GAMMA_40_7F
mdefine_line|#define OV0_GAMMA_40_7F                        0x0D4C  
DECL|macro|OV0_GAMMA_380_3BF
mdefine_line|#define OV0_GAMMA_380_3BF                      0x0D50  
DECL|macro|OV0_GAMMA_3C0_3FF
mdefine_line|#define OV0_GAMMA_3C0_3FF                      0x0D54  
DECL|macro|DISP_MERGE_CNTL
mdefine_line|#define DISP_MERGE_CNTL                        0x0D60  
DECL|macro|DISP_OUTPUT_CNTL
mdefine_line|#define DISP_OUTPUT_CNTL                       0x0D64  
DECL|macro|DISP_LIN_TRANS_GRPH_A
mdefine_line|#define DISP_LIN_TRANS_GRPH_A                  0x0D80  
DECL|macro|DISP_LIN_TRANS_GRPH_B
mdefine_line|#define DISP_LIN_TRANS_GRPH_B                  0x0D84
DECL|macro|DISP_LIN_TRANS_GRPH_C
mdefine_line|#define DISP_LIN_TRANS_GRPH_C                  0x0D88
DECL|macro|DISP_LIN_TRANS_GRPH_D
mdefine_line|#define DISP_LIN_TRANS_GRPH_D                  0x0D8C
DECL|macro|DISP_LIN_TRANS_GRPH_E
mdefine_line|#define DISP_LIN_TRANS_GRPH_E                  0x0D90  
DECL|macro|DISP_LIN_TRANS_GRPH_F
mdefine_line|#define DISP_LIN_TRANS_GRPH_F                  0x0D94  
DECL|macro|DISP_LIN_TRANS_VID_A
mdefine_line|#define DISP_LIN_TRANS_VID_A                   0x0D98  
DECL|macro|DISP_LIN_TRANS_VID_B
mdefine_line|#define DISP_LIN_TRANS_VID_B                   0x0D9C  
DECL|macro|DISP_LIN_TRANS_VID_C
mdefine_line|#define DISP_LIN_TRANS_VID_C                   0x0DA0  
DECL|macro|DISP_LIN_TRANS_VID_D
mdefine_line|#define DISP_LIN_TRANS_VID_D                   0x0DA4  
DECL|macro|DISP_LIN_TRANS_VID_E
mdefine_line|#define DISP_LIN_TRANS_VID_E                   0x0DA8  
DECL|macro|DISP_LIN_TRANS_VID_F
mdefine_line|#define DISP_LIN_TRANS_VID_F                   0x0DAC  
DECL|macro|RMX_HORZ_FILTER_0TAP_COEF
mdefine_line|#define RMX_HORZ_FILTER_0TAP_COEF              0x0DB0  
DECL|macro|RMX_HORZ_FILTER_1TAP_COEF
mdefine_line|#define RMX_HORZ_FILTER_1TAP_COEF              0x0DB4  
DECL|macro|RMX_HORZ_FILTER_2TAP_COEF
mdefine_line|#define RMX_HORZ_FILTER_2TAP_COEF              0x0DB8  
DECL|macro|RMX_HORZ_PHASE
mdefine_line|#define RMX_HORZ_PHASE                         0x0DBC  
DECL|macro|DAC_EMBEDDED_SYNC_CNTL
mdefine_line|#define DAC_EMBEDDED_SYNC_CNTL                 0x0DC0  
DECL|macro|DAC_BROAD_PULSE
mdefine_line|#define DAC_BROAD_PULSE                        0x0DC4  
DECL|macro|DAC_SKEW_CLKS
mdefine_line|#define DAC_SKEW_CLKS                          0x0DC8
DECL|macro|DAC_INCR
mdefine_line|#define DAC_INCR                               0x0DCC
DECL|macro|DAC_NEG_SYNC_LEVEL
mdefine_line|#define DAC_NEG_SYNC_LEVEL                     0x0DD0
DECL|macro|DAC_POS_SYNC_LEVEL
mdefine_line|#define DAC_POS_SYNC_LEVEL                     0x0DD4  
DECL|macro|DAC_BLANK_LEVEL
mdefine_line|#define DAC_BLANK_LEVEL                        0x0DD8  
DECL|macro|CLOCK_CNTL_INDEX
mdefine_line|#define CLOCK_CNTL_INDEX                       0x0008  
DECL|macro|CLOCK_CNTL_DATA
mdefine_line|#define CLOCK_CNTL_DATA                        0x000C  
DECL|macro|CP_RB_CNTL
mdefine_line|#define CP_RB_CNTL                             0x0704  
DECL|macro|CP_RB_BASE
mdefine_line|#define CP_RB_BASE                             0x0700  
DECL|macro|CP_RB_RPTR_ADDR
mdefine_line|#define CP_RB_RPTR_ADDR                        0x070C  
DECL|macro|CP_RB_RPTR
mdefine_line|#define CP_RB_RPTR                             0x0710  
DECL|macro|CP_RB_WPTR
mdefine_line|#define CP_RB_WPTR                             0x0714  
DECL|macro|CP_RB_WPTR_DELAY
mdefine_line|#define CP_RB_WPTR_DELAY                       0x0718  
DECL|macro|CP_IB_BASE
mdefine_line|#define CP_IB_BASE                             0x0738  
DECL|macro|CP_IB_BUFSZ
mdefine_line|#define CP_IB_BUFSZ                            0x073C  
DECL|macro|SCRATCH_REG0
mdefine_line|#define SCRATCH_REG0                           0x15E0  
DECL|macro|GUI_SCRATCH_REG0
mdefine_line|#define GUI_SCRATCH_REG0                       0x15E0  
DECL|macro|SCRATCH_REG1
mdefine_line|#define SCRATCH_REG1                           0x15E4  
DECL|macro|GUI_SCRATCH_REG1
mdefine_line|#define GUI_SCRATCH_REG1                       0x15E4  
DECL|macro|SCRATCH_REG2
mdefine_line|#define SCRATCH_REG2                           0x15E8
DECL|macro|GUI_SCRATCH_REG2
mdefine_line|#define GUI_SCRATCH_REG2                       0x15E8
DECL|macro|SCRATCH_REG3
mdefine_line|#define SCRATCH_REG3                           0x15EC
DECL|macro|GUI_SCRATCH_REG3
mdefine_line|#define GUI_SCRATCH_REG3                       0x15EC  
DECL|macro|SCRATCH_REG4
mdefine_line|#define SCRATCH_REG4                           0x15F0  
DECL|macro|GUI_SCRATCH_REG4
mdefine_line|#define GUI_SCRATCH_REG4                       0x15F0  
DECL|macro|SCRATCH_REG5
mdefine_line|#define SCRATCH_REG5                           0x15F4  
DECL|macro|GUI_SCRATCH_REG5
mdefine_line|#define GUI_SCRATCH_REG5                       0x15F4  
DECL|macro|SCRATCH_UMSK
mdefine_line|#define SCRATCH_UMSK                           0x0770  
DECL|macro|SCRATCH_ADDR
mdefine_line|#define SCRATCH_ADDR                           0x0774  
DECL|macro|DP_BRUSH_FRGD_CLR
mdefine_line|#define DP_BRUSH_FRGD_CLR                      0x147C  
DECL|macro|DP_BRUSH_BKGD_CLR
mdefine_line|#define DP_BRUSH_BKGD_CLR                      0x1478
DECL|macro|DST_LINE_START
mdefine_line|#define DST_LINE_START                         0x1600
DECL|macro|DST_LINE_END
mdefine_line|#define DST_LINE_END                           0x1604  
DECL|macro|SRC_OFFSET
mdefine_line|#define SRC_OFFSET                             0x15AC  
DECL|macro|SRC_PITCH
mdefine_line|#define SRC_PITCH                              0x15B0
DECL|macro|SRC_TILE
mdefine_line|#define SRC_TILE                               0x1704
DECL|macro|SRC_PITCH_OFFSET
mdefine_line|#define SRC_PITCH_OFFSET                       0x1428
DECL|macro|SRC_X
mdefine_line|#define SRC_X                                  0x1414  
DECL|macro|SRC_Y
mdefine_line|#define SRC_Y                                  0x1418  
DECL|macro|SRC_X_Y
mdefine_line|#define SRC_X_Y                                0x1590  
DECL|macro|SRC_Y_X
mdefine_line|#define SRC_Y_X                                0x1434  
DECL|macro|DST_Y_X
mdefine_line|#define DST_Y_X&t;&t;&t;&t;       0x1438
DECL|macro|DST_WIDTH_HEIGHT
mdefine_line|#define DST_WIDTH_HEIGHT&t;&t;       0x1598
DECL|macro|DST_HEIGHT_WIDTH
mdefine_line|#define DST_HEIGHT_WIDTH&t;&t;       0x143c
DECL|macro|SRC_CLUT_ADDRESS
mdefine_line|#define SRC_CLUT_ADDRESS                       0x1780  
DECL|macro|SRC_CLUT_DATA
mdefine_line|#define SRC_CLUT_DATA                          0x1784  
DECL|macro|SRC_CLUT_DATA_RD
mdefine_line|#define SRC_CLUT_DATA_RD                       0x1788  
DECL|macro|HOST_DATA0
mdefine_line|#define HOST_DATA0                             0x17C0  
DECL|macro|HOST_DATA1
mdefine_line|#define HOST_DATA1                             0x17C4  
DECL|macro|HOST_DATA2
mdefine_line|#define HOST_DATA2                             0x17C8  
DECL|macro|HOST_DATA3
mdefine_line|#define HOST_DATA3                             0x17CC  
DECL|macro|HOST_DATA4
mdefine_line|#define HOST_DATA4                             0x17D0  
DECL|macro|HOST_DATA5
mdefine_line|#define HOST_DATA5                             0x17D4  
DECL|macro|HOST_DATA6
mdefine_line|#define HOST_DATA6                             0x17D8  
DECL|macro|HOST_DATA7
mdefine_line|#define HOST_DATA7                             0x17DC
DECL|macro|HOST_DATA_LAST
mdefine_line|#define HOST_DATA_LAST                         0x17E0
DECL|macro|DP_SRC_ENDIAN
mdefine_line|#define DP_SRC_ENDIAN                          0x15D4
DECL|macro|DP_SRC_FRGD_CLR
mdefine_line|#define DP_SRC_FRGD_CLR                        0x15D8  
DECL|macro|DP_SRC_BKGD_CLR
mdefine_line|#define DP_SRC_BKGD_CLR                        0x15DC  
DECL|macro|SC_LEFT
mdefine_line|#define SC_LEFT                                0x1640  
DECL|macro|SC_RIGHT
mdefine_line|#define SC_RIGHT                               0x1644  
DECL|macro|SC_TOP
mdefine_line|#define SC_TOP                                 0x1648  
DECL|macro|SC_BOTTOM
mdefine_line|#define SC_BOTTOM                              0x164C  
DECL|macro|SRC_SC_RIGHT
mdefine_line|#define SRC_SC_RIGHT                           0x1654  
DECL|macro|SRC_SC_BOTTOM
mdefine_line|#define SRC_SC_BOTTOM                          0x165C  
DECL|macro|DP_CNTL
mdefine_line|#define DP_CNTL                                0x16C0  
DECL|macro|DP_CNTL_XDIR_YDIR_YMAJOR
mdefine_line|#define DP_CNTL_XDIR_YDIR_YMAJOR               0x16D0  
DECL|macro|DP_DATATYPE
mdefine_line|#define DP_DATATYPE                            0x16C4  
DECL|macro|DP_MIX
mdefine_line|#define DP_MIX                                 0x16C8  
DECL|macro|DP_WRITE_MSK
mdefine_line|#define DP_WRITE_MSK                           0x16CC  
DECL|macro|DP_XOP
mdefine_line|#define DP_XOP                                 0x17F8  
DECL|macro|CLR_CMP_CLR_SRC
mdefine_line|#define CLR_CMP_CLR_SRC                        0x15C4
DECL|macro|CLR_CMP_CLR_DST
mdefine_line|#define CLR_CMP_CLR_DST                        0x15C8
DECL|macro|CLR_CMP_CNTL
mdefine_line|#define CLR_CMP_CNTL                           0x15C0
DECL|macro|CLR_CMP_MSK
mdefine_line|#define CLR_CMP_MSK                            0x15CC  
DECL|macro|DSTCACHE_MODE
mdefine_line|#define DSTCACHE_MODE                          0x1710  
DECL|macro|DSTCACHE_CTLSTAT
mdefine_line|#define DSTCACHE_CTLSTAT                       0x1714  
DECL|macro|DEFAULT_PITCH_OFFSET
mdefine_line|#define DEFAULT_PITCH_OFFSET                   0x16E0  
DECL|macro|DEFAULT_SC_BOTTOM_RIGHT
mdefine_line|#define DEFAULT_SC_BOTTOM_RIGHT                0x16E8  
DECL|macro|DP_GUI_MASTER_CNTL
mdefine_line|#define DP_GUI_MASTER_CNTL                     0x146C  
DECL|macro|SC_TOP_LEFT
mdefine_line|#define SC_TOP_LEFT                            0x16EC  
DECL|macro|SC_BOTTOM_RIGHT
mdefine_line|#define SC_BOTTOM_RIGHT                        0x16F0  
DECL|macro|SRC_SC_BOTTOM_RIGHT
mdefine_line|#define SRC_SC_BOTTOM_RIGHT                    0x16F4  
DECL|macro|RB2D_DSTCACHE_CTLSTAT
mdefine_line|#define RB2D_DSTCACHE_CTLSTAT&t;&t;       0x342C
DECL|macro|CLK_PIN_CNTL
mdefine_line|#define CLK_PIN_CNTL                               0x0001
DECL|macro|PPLL_CNTL
mdefine_line|#define PPLL_CNTL                                  0x0002
DECL|macro|PPLL_REF_DIV
mdefine_line|#define PPLL_REF_DIV                               0x0003
DECL|macro|PPLL_DIV_0
mdefine_line|#define PPLL_DIV_0                                 0x0004
DECL|macro|PPLL_DIV_1
mdefine_line|#define PPLL_DIV_1                                 0x0005
DECL|macro|PPLL_DIV_2
mdefine_line|#define PPLL_DIV_2                                 0x0006
DECL|macro|PPLL_DIV_3
mdefine_line|#define PPLL_DIV_3                                 0x0007
DECL|macro|VCLK_ECP_CNTL
mdefine_line|#define VCLK_ECP_CNTL                              0x0008
DECL|macro|HTOTAL_CNTL
mdefine_line|#define HTOTAL_CNTL                                0x0009
DECL|macro|M_SPLL_REF_FB_DIV
mdefine_line|#define M_SPLL_REF_FB_DIV                          0x000a
DECL|macro|AGP_PLL_CNTL
mdefine_line|#define AGP_PLL_CNTL                               0x000b
DECL|macro|SPLL_CNTL
mdefine_line|#define SPLL_CNTL                                  0x000c
DECL|macro|SCLK_CNTL
mdefine_line|#define SCLK_CNTL                                  0x000d
DECL|macro|MPLL_CNTL
mdefine_line|#define MPLL_CNTL                                  0x000e
DECL|macro|MCLK_CNTL
mdefine_line|#define MCLK_CNTL                                  0x0012
DECL|macro|AGP_PLL_CNTL
mdefine_line|#define AGP_PLL_CNTL                               0x000b
DECL|macro|PLL_TEST_CNTL
mdefine_line|#define PLL_TEST_CNTL                              0x0013
multiline_comment|/* MCLK_CNTL bit constants */
DECL|macro|FORCEON_MCLKA
mdefine_line|#define FORCEON_MCLKA&t;&t;&t;&t;   (1 &lt;&lt; 16)
DECL|macro|FORCEON_MCLKB
mdefine_line|#define FORCEON_MCLKB         &t;&t;   &t;   (1 &lt;&lt; 17)
DECL|macro|FORCEON_YCLKA
mdefine_line|#define FORCEON_YCLKA         &t;    &t;   &t;   (1 &lt;&lt; 18)
DECL|macro|FORCEON_YCLKB
mdefine_line|#define FORCEON_YCLKB         &t;&t;   &t;   (1 &lt;&lt; 19)
DECL|macro|FORCEON_MC
mdefine_line|#define FORCEON_MC            &t;&t;   &t;   (1 &lt;&lt; 20)
DECL|macro|FORCEON_AIC
mdefine_line|#define FORCEON_AIC           &t;&t;   &t;   (1 &lt;&lt; 21)
multiline_comment|/* BUS_CNTL bit constants */
DECL|macro|BUS_DBL_RESYNC
mdefine_line|#define BUS_DBL_RESYNC                             0x00000001
DECL|macro|BUS_MSTR_RESET
mdefine_line|#define BUS_MSTR_RESET                             0x00000002
DECL|macro|BUS_FLUSH_BUF
mdefine_line|#define BUS_FLUSH_BUF                              0x00000004
DECL|macro|BUS_STOP_REQ_DIS
mdefine_line|#define BUS_STOP_REQ_DIS                           0x00000008
DECL|macro|BUS_ROTATION_DIS
mdefine_line|#define BUS_ROTATION_DIS                           0x00000010
DECL|macro|BUS_MASTER_DIS
mdefine_line|#define BUS_MASTER_DIS                             0x00000040
DECL|macro|BUS_ROM_WRT_EN
mdefine_line|#define BUS_ROM_WRT_EN                             0x00000080
DECL|macro|BUS_DIS_ROM
mdefine_line|#define BUS_DIS_ROM                                0x00001000
DECL|macro|BUS_PCI_READ_RETRY_EN
mdefine_line|#define BUS_PCI_READ_RETRY_EN                      0x00002000
DECL|macro|BUS_AGP_AD_STEPPING_EN
mdefine_line|#define BUS_AGP_AD_STEPPING_EN                     0x00004000
DECL|macro|BUS_PCI_WRT_RETRY_EN
mdefine_line|#define BUS_PCI_WRT_RETRY_EN                       0x00008000
DECL|macro|BUS_MSTR_RD_MULT
mdefine_line|#define BUS_MSTR_RD_MULT                           0x00100000
DECL|macro|BUS_MSTR_RD_LINE
mdefine_line|#define BUS_MSTR_RD_LINE                           0x00200000
DECL|macro|BUS_SUSPEND
mdefine_line|#define BUS_SUSPEND                                0x00400000
DECL|macro|LAT_16X
mdefine_line|#define LAT_16X                                    0x00800000
DECL|macro|BUS_RD_DISCARD_EN
mdefine_line|#define BUS_RD_DISCARD_EN                          0x01000000
DECL|macro|BUS_RD_ABORT_EN
mdefine_line|#define BUS_RD_ABORT_EN                            0x02000000
DECL|macro|BUS_MSTR_WS
mdefine_line|#define BUS_MSTR_WS                                0x04000000
DECL|macro|BUS_PARKING_DIS
mdefine_line|#define BUS_PARKING_DIS                            0x08000000
DECL|macro|BUS_MSTR_DISCONNECT_EN
mdefine_line|#define BUS_MSTR_DISCONNECT_EN                     0x10000000
DECL|macro|BUS_WRT_BURST
mdefine_line|#define BUS_WRT_BURST                              0x20000000
DECL|macro|BUS_READ_BURST
mdefine_line|#define BUS_READ_BURST                             0x40000000
DECL|macro|BUS_RDY_READ_DLY
mdefine_line|#define BUS_RDY_READ_DLY                           0x80000000
multiline_comment|/* CLOCK_CNTL_INDEX bit constants */
DECL|macro|PLL_WR_EN
mdefine_line|#define PLL_WR_EN                                  0x00000080
multiline_comment|/* CONFIG_CNTL bit constants */
DECL|macro|CFG_VGA_RAM_EN
mdefine_line|#define CFG_VGA_RAM_EN                             0x00000100
multiline_comment|/* CRTC_EXT_CNTL bit constants */
DECL|macro|VGA_ATI_LINEAR
mdefine_line|#define VGA_ATI_LINEAR                             0x00000008
DECL|macro|VGA_128KAP_PAGING
mdefine_line|#define VGA_128KAP_PAGING                          0x00000010
DECL|macro|XCRT_CNT_EN
mdefine_line|#define&t;XCRT_CNT_EN&t;&t;&t;&t;   (1 &lt;&lt; 6)
DECL|macro|CRTC_HSYNC_DIS
mdefine_line|#define CRTC_HSYNC_DIS&t;&t;&t;&t;   (1 &lt;&lt; 8)
DECL|macro|CRTC_VSYNC_DIS
mdefine_line|#define CRTC_VSYNC_DIS&t;&t;&t;&t;   (1 &lt;&lt; 9)
DECL|macro|CRTC_DISPLAY_DIS
mdefine_line|#define CRTC_DISPLAY_DIS&t;&t;&t;   (1 &lt;&lt; 10)
multiline_comment|/* DSTCACHE_CTLSTAT bit constants */
DECL|macro|RB2D_DC_FLUSH
mdefine_line|#define RB2D_DC_FLUSH&t;&t;&t;&t;   (3 &lt;&lt; 0)
DECL|macro|RB2D_DC_FLUSH_ALL
mdefine_line|#define RB2D_DC_FLUSH_ALL&t;&t;&t;   0xf
DECL|macro|RB2D_DC_BUSY
mdefine_line|#define RB2D_DC_BUSY&t;&t;&t;&t;   (1 &lt;&lt; 31)
multiline_comment|/* CRTC_GEN_CNTL bit constants */
DECL|macro|CRTC_DBL_SCAN_EN
mdefine_line|#define CRTC_DBL_SCAN_EN                           0x00000001
DECL|macro|CRTC_CUR_EN
mdefine_line|#define CRTC_CUR_EN                                0x00010000
DECL|macro|CRTC_EXT_DISP_EN
mdefine_line|#define CRTC_EXT_DISP_EN      &t;&t;&t;   (1 &lt;&lt; 24)
DECL|macro|CRTC_EN
mdefine_line|#define CRTC_EN&t;&t;&t;&t;&t;   (1 &lt;&lt; 25)
multiline_comment|/* CRTC_STATUS bit constants */
DECL|macro|CRTC_VBLANK
mdefine_line|#define CRTC_VBLANK                                0x00000001
multiline_comment|/* CUR_OFFSET, CUR_HORZ_VERT_POSN, CUR_HORZ_VERT_OFF bit constants */
DECL|macro|CUR_LOCK
mdefine_line|#define CUR_LOCK                                   0x80000000
multiline_comment|/* DAC_CNTL bit constants */
DECL|macro|DAC_8BIT_EN
mdefine_line|#define DAC_8BIT_EN                                0x00000100
DECL|macro|DAC_4BPP_PIX_ORDER
mdefine_line|#define DAC_4BPP_PIX_ORDER                         0x00000200
DECL|macro|DAC_CRC_EN
mdefine_line|#define DAC_CRC_EN                                 0x00080000
DECL|macro|DAC_MASK_ALL
mdefine_line|#define DAC_MASK_ALL&t;&t;&t;&t;   (0xff &lt;&lt; 24)
DECL|macro|DAC_VGA_ADR_EN
mdefine_line|#define DAC_VGA_ADR_EN&t;&t;&t;&t;   (1 &lt;&lt; 13)
DECL|macro|DAC_RANGE_CNTL
mdefine_line|#define DAC_RANGE_CNTL&t;&t;&t;&t;   (3 &lt;&lt; 0)
DECL|macro|DAC_BLANKING
mdefine_line|#define DAC_BLANKING&t;&t;&t;&t;   (1 &lt;&lt; 2)
multiline_comment|/* GEN_RESET_CNTL bit constants */
DECL|macro|SOFT_RESET_GUI
mdefine_line|#define SOFT_RESET_GUI                             0x00000001
DECL|macro|SOFT_RESET_VCLK
mdefine_line|#define SOFT_RESET_VCLK                            0x00000100
DECL|macro|SOFT_RESET_PCLK
mdefine_line|#define SOFT_RESET_PCLK                            0x00000200
DECL|macro|SOFT_RESET_ECP
mdefine_line|#define SOFT_RESET_ECP                             0x00000400
DECL|macro|SOFT_RESET_DISPENG_XCLK
mdefine_line|#define SOFT_RESET_DISPENG_XCLK                    0x00000800
multiline_comment|/* MEM_CNTL bit constants */
DECL|macro|MEM_CTLR_STATUS_IDLE
mdefine_line|#define MEM_CTLR_STATUS_IDLE                       0x00000000
DECL|macro|MEM_CTLR_STATUS_BUSY
mdefine_line|#define MEM_CTLR_STATUS_BUSY                       0x00100000
DECL|macro|MEM_SEQNCR_STATUS_IDLE
mdefine_line|#define MEM_SEQNCR_STATUS_IDLE                     0x00000000
DECL|macro|MEM_SEQNCR_STATUS_BUSY
mdefine_line|#define MEM_SEQNCR_STATUS_BUSY                     0x00200000
DECL|macro|MEM_ARBITER_STATUS_IDLE
mdefine_line|#define MEM_ARBITER_STATUS_IDLE                    0x00000000
DECL|macro|MEM_ARBITER_STATUS_BUSY
mdefine_line|#define MEM_ARBITER_STATUS_BUSY                    0x00400000
DECL|macro|MEM_REQ_UNLOCK
mdefine_line|#define MEM_REQ_UNLOCK                             0x00000000
DECL|macro|MEM_REQ_LOCK
mdefine_line|#define MEM_REQ_LOCK                               0x00800000
multiline_comment|/* RBBM_SOFT_RESET bit constants */
DECL|macro|SOFT_RESET_CP
mdefine_line|#define SOFT_RESET_CP           &t;&t;   (1 &lt;&lt;  0)
DECL|macro|SOFT_RESET_HI
mdefine_line|#define SOFT_RESET_HI           &t;&t;   (1 &lt;&lt;  1)
DECL|macro|SOFT_RESET_SE
mdefine_line|#define SOFT_RESET_SE           &t;&t;   (1 &lt;&lt;  2)
DECL|macro|SOFT_RESET_RE
mdefine_line|#define SOFT_RESET_RE           &t;&t;   (1 &lt;&lt;  3)
DECL|macro|SOFT_RESET_PP
mdefine_line|#define SOFT_RESET_PP           &t;&t;   (1 &lt;&lt;  4)
DECL|macro|SOFT_RESET_E2
mdefine_line|#define SOFT_RESET_E2           &t;&t;   (1 &lt;&lt;  5)
DECL|macro|SOFT_RESET_RB
mdefine_line|#define SOFT_RESET_RB           &t;&t;   (1 &lt;&lt;  6)
DECL|macro|SOFT_RESET_HDP
mdefine_line|#define SOFT_RESET_HDP          &t;&t;   (1 &lt;&lt;  7)
multiline_comment|/* DEFAULT_SC_BOTTOM_RIGHT bit constants */
DECL|macro|DEFAULT_SC_RIGHT_MAX
mdefine_line|#define DEFAULT_SC_RIGHT_MAX&t;&t;&t;   (0x1fff &lt;&lt; 0)
DECL|macro|DEFAULT_SC_BOTTOM_MAX
mdefine_line|#define DEFAULT_SC_BOTTOM_MAX&t;&t;&t;   (0x1fff &lt;&lt; 16)
multiline_comment|/* MM_INDEX bit constants */
DECL|macro|MM_APER
mdefine_line|#define MM_APER                                    0x80000000
multiline_comment|/* CLR_CMP_CNTL bit constants */
DECL|macro|COMPARE_SRC_FALSE
mdefine_line|#define COMPARE_SRC_FALSE                          0x00000000
DECL|macro|COMPARE_SRC_TRUE
mdefine_line|#define COMPARE_SRC_TRUE                           0x00000001
DECL|macro|COMPARE_SRC_NOT_EQUAL
mdefine_line|#define COMPARE_SRC_NOT_EQUAL                      0x00000004
DECL|macro|COMPARE_SRC_EQUAL
mdefine_line|#define COMPARE_SRC_EQUAL                          0x00000005
DECL|macro|COMPARE_SRC_EQUAL_FLIP
mdefine_line|#define COMPARE_SRC_EQUAL_FLIP                     0x00000007
DECL|macro|COMPARE_DST_FALSE
mdefine_line|#define COMPARE_DST_FALSE                          0x00000000
DECL|macro|COMPARE_DST_TRUE
mdefine_line|#define COMPARE_DST_TRUE                           0x00000100
DECL|macro|COMPARE_DST_NOT_EQUAL
mdefine_line|#define COMPARE_DST_NOT_EQUAL                      0x00000400
DECL|macro|COMPARE_DST_EQUAL
mdefine_line|#define COMPARE_DST_EQUAL                          0x00000500
DECL|macro|COMPARE_DESTINATION
mdefine_line|#define COMPARE_DESTINATION                        0x00000000
DECL|macro|COMPARE_SOURCE
mdefine_line|#define COMPARE_SOURCE                             0x01000000
DECL|macro|COMPARE_SRC_AND_DST
mdefine_line|#define COMPARE_SRC_AND_DST                        0x02000000
multiline_comment|/* DP_CNTL bit constants */
DECL|macro|DST_X_RIGHT_TO_LEFT
mdefine_line|#define DST_X_RIGHT_TO_LEFT                        0x00000000
DECL|macro|DST_X_LEFT_TO_RIGHT
mdefine_line|#define DST_X_LEFT_TO_RIGHT                        0x00000001
DECL|macro|DST_Y_BOTTOM_TO_TOP
mdefine_line|#define DST_Y_BOTTOM_TO_TOP                        0x00000000
DECL|macro|DST_Y_TOP_TO_BOTTOM
mdefine_line|#define DST_Y_TOP_TO_BOTTOM                        0x00000002
DECL|macro|DST_X_MAJOR
mdefine_line|#define DST_X_MAJOR                                0x00000000
DECL|macro|DST_Y_MAJOR
mdefine_line|#define DST_Y_MAJOR                                0x00000004
DECL|macro|DST_X_TILE
mdefine_line|#define DST_X_TILE                                 0x00000008
DECL|macro|DST_Y_TILE
mdefine_line|#define DST_Y_TILE                                 0x00000010
DECL|macro|DST_LAST_PEL
mdefine_line|#define DST_LAST_PEL                               0x00000020
DECL|macro|DST_TRAIL_X_RIGHT_TO_LEFT
mdefine_line|#define DST_TRAIL_X_RIGHT_TO_LEFT                  0x00000000
DECL|macro|DST_TRAIL_X_LEFT_TO_RIGHT
mdefine_line|#define DST_TRAIL_X_LEFT_TO_RIGHT                  0x00000040
DECL|macro|DST_TRAP_FILL_RIGHT_TO_LEFT
mdefine_line|#define DST_TRAP_FILL_RIGHT_TO_LEFT                0x00000000
DECL|macro|DST_TRAP_FILL_LEFT_TO_RIGHT
mdefine_line|#define DST_TRAP_FILL_LEFT_TO_RIGHT                0x00000080
DECL|macro|DST_BRES_SIGN
mdefine_line|#define DST_BRES_SIGN                              0x00000100
DECL|macro|DST_HOST_BIG_ENDIAN_EN
mdefine_line|#define DST_HOST_BIG_ENDIAN_EN                     0x00000200
DECL|macro|DST_POLYLINE_NONLAST
mdefine_line|#define DST_POLYLINE_NONLAST                       0x00008000
DECL|macro|DST_RASTER_STALL
mdefine_line|#define DST_RASTER_STALL                           0x00010000
DECL|macro|DST_POLY_EDGE
mdefine_line|#define DST_POLY_EDGE                              0x00040000
multiline_comment|/* DP_CNTL_YDIR_XDIR_YMAJOR bit constants (short version of DP_CNTL) */
DECL|macro|DST_X_MAJOR_S
mdefine_line|#define DST_X_MAJOR_S                              0x00000000
DECL|macro|DST_Y_MAJOR_S
mdefine_line|#define DST_Y_MAJOR_S                              0x00000001
DECL|macro|DST_Y_BOTTOM_TO_TOP_S
mdefine_line|#define DST_Y_BOTTOM_TO_TOP_S                      0x00000000
DECL|macro|DST_Y_TOP_TO_BOTTOM_S
mdefine_line|#define DST_Y_TOP_TO_BOTTOM_S                      0x00008000
DECL|macro|DST_X_RIGHT_TO_LEFT_S
mdefine_line|#define DST_X_RIGHT_TO_LEFT_S                      0x00000000
DECL|macro|DST_X_LEFT_TO_RIGHT_S
mdefine_line|#define DST_X_LEFT_TO_RIGHT_S                      0x80000000
multiline_comment|/* DP_DATATYPE bit constants */
DECL|macro|DST_8BPP
mdefine_line|#define DST_8BPP                                   0x00000002
DECL|macro|DST_15BPP
mdefine_line|#define DST_15BPP                                  0x00000003
DECL|macro|DST_16BPP
mdefine_line|#define DST_16BPP                                  0x00000004
DECL|macro|DST_24BPP
mdefine_line|#define DST_24BPP                                  0x00000005
DECL|macro|DST_32BPP
mdefine_line|#define DST_32BPP                                  0x00000006
DECL|macro|DST_8BPP_RGB332
mdefine_line|#define DST_8BPP_RGB332                            0x00000007
DECL|macro|DST_8BPP_Y8
mdefine_line|#define DST_8BPP_Y8                                0x00000008
DECL|macro|DST_8BPP_RGB8
mdefine_line|#define DST_8BPP_RGB8                              0x00000009
DECL|macro|DST_16BPP_VYUY422
mdefine_line|#define DST_16BPP_VYUY422                          0x0000000b
DECL|macro|DST_16BPP_YVYU422
mdefine_line|#define DST_16BPP_YVYU422                          0x0000000c
DECL|macro|DST_32BPP_AYUV444
mdefine_line|#define DST_32BPP_AYUV444                          0x0000000e
DECL|macro|DST_16BPP_ARGB4444
mdefine_line|#define DST_16BPP_ARGB4444                         0x0000000f
DECL|macro|BRUSH_SOLIDCOLOR
mdefine_line|#define BRUSH_SOLIDCOLOR                           0x00000d00
DECL|macro|SRC_MONO
mdefine_line|#define SRC_MONO                                   0x00000000
DECL|macro|SRC_MONO_LBKGD
mdefine_line|#define SRC_MONO_LBKGD                             0x00010000
DECL|macro|SRC_DSTCOLOR
mdefine_line|#define SRC_DSTCOLOR                               0x00030000
DECL|macro|BYTE_ORDER_MSB_TO_LSB
mdefine_line|#define BYTE_ORDER_MSB_TO_LSB                      0x00000000
DECL|macro|BYTE_ORDER_LSB_TO_MSB
mdefine_line|#define BYTE_ORDER_LSB_TO_MSB                      0x40000000
DECL|macro|DP_CONVERSION_TEMP
mdefine_line|#define DP_CONVERSION_TEMP                         0x80000000
DECL|macro|HOST_BIG_ENDIAN_EN
mdefine_line|#define HOST_BIG_ENDIAN_EN&t;&t;&t;   (1 &lt;&lt; 29)
multiline_comment|/* DP_GUI_MASTER_CNTL bit constants */
DECL|macro|GMC_SRC_PITCH_OFFSET_DEFAULT
mdefine_line|#define GMC_SRC_PITCH_OFFSET_DEFAULT               0x00000000
DECL|macro|GMC_SRC_PITCH_OFFSET_LEAVE
mdefine_line|#define GMC_SRC_PITCH_OFFSET_LEAVE                 0x00000001
DECL|macro|GMC_DST_PITCH_OFFSET_DEFAULT
mdefine_line|#define GMC_DST_PITCH_OFFSET_DEFAULT               0x00000000
DECL|macro|GMC_DST_PITCH_OFFSET_LEAVE
mdefine_line|#define GMC_DST_PITCH_OFFSET_LEAVE                 0x00000002
DECL|macro|GMC_SRC_CLIP_DEFAULT
mdefine_line|#define GMC_SRC_CLIP_DEFAULT                       0x00000000
DECL|macro|GMC_SRC_CLIP_LEAVE
mdefine_line|#define GMC_SRC_CLIP_LEAVE                         0x00000004
DECL|macro|GMC_DST_CLIP_DEFAULT
mdefine_line|#define GMC_DST_CLIP_DEFAULT                       0x00000000
DECL|macro|GMC_DST_CLIP_LEAVE
mdefine_line|#define GMC_DST_CLIP_LEAVE                         0x00000008
DECL|macro|GMC_BRUSH_8x8MONO
mdefine_line|#define GMC_BRUSH_8x8MONO                          0x00000000
DECL|macro|GMC_BRUSH_8x8MONO_LBKGD
mdefine_line|#define GMC_BRUSH_8x8MONO_LBKGD                    0x00000010
DECL|macro|GMC_BRUSH_8x1MONO
mdefine_line|#define GMC_BRUSH_8x1MONO                          0x00000020
DECL|macro|GMC_BRUSH_8x1MONO_LBKGD
mdefine_line|#define GMC_BRUSH_8x1MONO_LBKGD                    0x00000030
DECL|macro|GMC_BRUSH_1x8MONO
mdefine_line|#define GMC_BRUSH_1x8MONO                          0x00000040
DECL|macro|GMC_BRUSH_1x8MONO_LBKGD
mdefine_line|#define GMC_BRUSH_1x8MONO_LBKGD                    0x00000050
DECL|macro|GMC_BRUSH_32x1MONO
mdefine_line|#define GMC_BRUSH_32x1MONO                         0x00000060
DECL|macro|GMC_BRUSH_32x1MONO_LBKGD
mdefine_line|#define GMC_BRUSH_32x1MONO_LBKGD                   0x00000070
DECL|macro|GMC_BRUSH_32x32MONO
mdefine_line|#define GMC_BRUSH_32x32MONO                        0x00000080
DECL|macro|GMC_BRUSH_32x32MONO_LBKGD
mdefine_line|#define GMC_BRUSH_32x32MONO_LBKGD                  0x00000090
DECL|macro|GMC_BRUSH_8x8COLOR
mdefine_line|#define GMC_BRUSH_8x8COLOR                         0x000000a0
DECL|macro|GMC_BRUSH_8x1COLOR
mdefine_line|#define GMC_BRUSH_8x1COLOR                         0x000000b0
DECL|macro|GMC_BRUSH_1x8COLOR
mdefine_line|#define GMC_BRUSH_1x8COLOR                         0x000000c0
DECL|macro|GMC_BRUSH_SOLID_COLOR
mdefine_line|#define GMC_BRUSH_SOLID_COLOR                       0x000000d0
DECL|macro|GMC_DST_8BPP
mdefine_line|#define GMC_DST_8BPP                               0x00000200
DECL|macro|GMC_DST_15BPP
mdefine_line|#define GMC_DST_15BPP                              0x00000300
DECL|macro|GMC_DST_16BPP
mdefine_line|#define GMC_DST_16BPP                              0x00000400
DECL|macro|GMC_DST_24BPP
mdefine_line|#define GMC_DST_24BPP                              0x00000500
DECL|macro|GMC_DST_32BPP
mdefine_line|#define GMC_DST_32BPP                              0x00000600
DECL|macro|GMC_DST_8BPP_RGB332
mdefine_line|#define GMC_DST_8BPP_RGB332                        0x00000700
DECL|macro|GMC_DST_8BPP_Y8
mdefine_line|#define GMC_DST_8BPP_Y8                            0x00000800
DECL|macro|GMC_DST_8BPP_RGB8
mdefine_line|#define GMC_DST_8BPP_RGB8                          0x00000900
DECL|macro|GMC_DST_16BPP_VYUY422
mdefine_line|#define GMC_DST_16BPP_VYUY422                      0x00000b00
DECL|macro|GMC_DST_16BPP_YVYU422
mdefine_line|#define GMC_DST_16BPP_YVYU422                      0x00000c00
DECL|macro|GMC_DST_32BPP_AYUV444
mdefine_line|#define GMC_DST_32BPP_AYUV444                      0x00000e00
DECL|macro|GMC_DST_16BPP_ARGB4444
mdefine_line|#define GMC_DST_16BPP_ARGB4444                     0x00000f00
DECL|macro|GMC_SRC_MONO
mdefine_line|#define GMC_SRC_MONO                               0x00000000
DECL|macro|GMC_SRC_MONO_LBKGD
mdefine_line|#define GMC_SRC_MONO_LBKGD                         0x00001000
DECL|macro|GMC_SRC_DSTCOLOR
mdefine_line|#define GMC_SRC_DSTCOLOR                           0x00003000
DECL|macro|GMC_BYTE_ORDER_MSB_TO_LSB
mdefine_line|#define GMC_BYTE_ORDER_MSB_TO_LSB                  0x00000000
DECL|macro|GMC_BYTE_ORDER_LSB_TO_MSB
mdefine_line|#define GMC_BYTE_ORDER_LSB_TO_MSB                  0x00004000
DECL|macro|GMC_DP_CONVERSION_TEMP_9300
mdefine_line|#define GMC_DP_CONVERSION_TEMP_9300                0x00008000
DECL|macro|GMC_DP_CONVERSION_TEMP_6500
mdefine_line|#define GMC_DP_CONVERSION_TEMP_6500                0x00000000
DECL|macro|GMC_DP_SRC_RECT
mdefine_line|#define GMC_DP_SRC_RECT                            0x02000000
DECL|macro|GMC_DP_SRC_HOST
mdefine_line|#define GMC_DP_SRC_HOST                            0x03000000
DECL|macro|GMC_DP_SRC_HOST_BYTEALIGN
mdefine_line|#define GMC_DP_SRC_HOST_BYTEALIGN                  0x04000000
DECL|macro|GMC_3D_FCN_EN_CLR
mdefine_line|#define GMC_3D_FCN_EN_CLR                          0x00000000
DECL|macro|GMC_3D_FCN_EN_SET
mdefine_line|#define GMC_3D_FCN_EN_SET                          0x08000000
DECL|macro|GMC_DST_CLR_CMP_FCN_LEAVE
mdefine_line|#define GMC_DST_CLR_CMP_FCN_LEAVE                  0x00000000
DECL|macro|GMC_DST_CLR_CMP_FCN_CLEAR
mdefine_line|#define GMC_DST_CLR_CMP_FCN_CLEAR                  0x10000000
DECL|macro|GMC_AUX_CLIP_LEAVE
mdefine_line|#define GMC_AUX_CLIP_LEAVE                         0x00000000
DECL|macro|GMC_AUX_CLIP_CLEAR
mdefine_line|#define GMC_AUX_CLIP_CLEAR                         0x20000000
DECL|macro|GMC_WRITE_MASK_LEAVE
mdefine_line|#define GMC_WRITE_MASK_LEAVE                       0x00000000
DECL|macro|GMC_WRITE_MASK_SET
mdefine_line|#define GMC_WRITE_MASK_SET                         0x40000000
DECL|macro|GMC_CLR_CMP_CNTL_DIS
mdefine_line|#define GMC_CLR_CMP_CNTL_DIS      &t;&t;   (1 &lt;&lt; 28)
DECL|macro|GMC_SRC_DATATYPE_COLOR
mdefine_line|#define GMC_SRC_DATATYPE_COLOR&t;&t;&t;   (3 &lt;&lt; 12)
DECL|macro|ROP3_S
mdefine_line|#define ROP3_S                &t;&t;&t;   0x00cc0000
DECL|macro|ROP3_SRCCOPY
mdefine_line|#define ROP3_SRCCOPY&t;&t;&t;&t;   0x00cc0000
DECL|macro|ROP3_P
mdefine_line|#define ROP3_P                &t;&t;&t;   0x00f00000
DECL|macro|ROP3_PATCOPY
mdefine_line|#define ROP3_PATCOPY&t;&t;&t;&t;   0x00f00000
DECL|macro|DP_SRC_SOURCE_MASK
mdefine_line|#define DP_SRC_SOURCE_MASK        &t;&t;   (7    &lt;&lt; 24)
DECL|macro|GMC_BRUSH_NONE
mdefine_line|#define GMC_BRUSH_NONE            &t;&t;   (15   &lt;&lt;  4)
DECL|macro|DP_SRC_SOURCE_MEMORY
mdefine_line|#define DP_SRC_SOURCE_MEMORY&t;&t;&t;   (2    &lt;&lt; 24)
DECL|macro|GMC_BRUSH_SOLIDCOLOR
mdefine_line|#define GMC_BRUSH_SOLIDCOLOR&t;&t;&t;   0x000000d0
multiline_comment|/* DP_MIX bit constants */
DECL|macro|DP_SRC_RECT
mdefine_line|#define DP_SRC_RECT                                0x00000200
DECL|macro|DP_SRC_HOST
mdefine_line|#define DP_SRC_HOST                                0x00000300
DECL|macro|DP_SRC_HOST_BYTEALIGN
mdefine_line|#define DP_SRC_HOST_BYTEALIGN                      0x00000400
multiline_comment|/* masks */
DECL|macro|CONFIG_MEMSIZE_MASK
mdefine_line|#define CONFIG_MEMSIZE_MASK&t;&t;0x1f000000
DECL|macro|MEM_CFG_TYPE
mdefine_line|#define MEM_CFG_TYPE&t;&t;&t;0x40000000
DECL|macro|DST_OFFSET_MASK
mdefine_line|#define DST_OFFSET_MASK&t;&t;&t;0x003fffff
DECL|macro|DST_PITCH_MASK
mdefine_line|#define DST_PITCH_MASK&t;&t;&t;0x3fc00000
DECL|macro|DEFAULT_TILE_MASK
mdefine_line|#define DEFAULT_TILE_MASK&t;&t;0xc0000000
DECL|macro|PPLL_DIV_SEL_MASK
mdefine_line|#define&t;PPLL_DIV_SEL_MASK&t;&t;0x00000300
DECL|macro|PPLL_RESET
mdefine_line|#define&t;PPLL_RESET&t;&t;&t;0x00000001
DECL|macro|PPLL_ATOMIC_UPDATE_EN
mdefine_line|#define PPLL_ATOMIC_UPDATE_EN&t;&t;0x00010000
DECL|macro|PPLL_REF_DIV_MASK
mdefine_line|#define PPLL_REF_DIV_MASK&t;&t;0x000003ff
DECL|macro|PPLL_FB3_DIV_MASK
mdefine_line|#define&t;PPLL_FB3_DIV_MASK&t;&t;0x000007ff
DECL|macro|PPLL_POST3_DIV_MASK
mdefine_line|#define&t;PPLL_POST3_DIV_MASK&t;&t;0x00070000
DECL|macro|PPLL_ATOMIC_UPDATE_R
mdefine_line|#define PPLL_ATOMIC_UPDATE_R&t;&t;0x00008000
DECL|macro|PPLL_ATOMIC_UPDATE_W
mdefine_line|#define PPLL_ATOMIC_UPDATE_W&t;&t;0x00008000
DECL|macro|PPLL_VGA_ATOMIC_UPDATE_EN
mdefine_line|#define&t;PPLL_VGA_ATOMIC_UPDATE_EN&t;0x00020000
DECL|macro|GUI_ACTIVE
mdefine_line|#define GUI_ACTIVE&t;&t;&t;0x80000000
macro_line|#endif&t;/* _RADEON_H */
eof
