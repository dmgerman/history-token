macro_line|#ifndef _RADEON_H
DECL|macro|_RADEON_H
mdefine_line|#define _RADEON_H
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
DECL|macro|PAD_CTLR_MISC
mdefine_line|#define PAD_CTLR_MISC                          0x0aa0
DECL|macro|AGP_CNTL
mdefine_line|#define AGP_CNTL                               0x0174
DECL|macro|BM_STATUS
mdefine_line|#define BM_STATUS                              0x0160
DECL|macro|CAP0_TRIG_CNTL
mdefine_line|#define CAP0_TRIG_CNTL&t;&t;&t;       0x0950
DECL|macro|CAP1_TRIG_CNTL
mdefine_line|#define CAP1_TRIG_CNTL&t;&t;               0x09c0
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
DECL|macro|DAC_CNTL2
mdefine_line|#define DAC_CNTL2                              0x007c
DECL|macro|CRTC_GEN_CNTL
mdefine_line|#define CRTC_GEN_CNTL                          0x0050  
DECL|macro|MEM_CNTL
mdefine_line|#define MEM_CNTL                               0x0140  
DECL|macro|MC_CNTL
mdefine_line|#define MC_CNTL                                0x0140
DECL|macro|EXT_MEM_CNTL
mdefine_line|#define EXT_MEM_CNTL                           0x0144  
DECL|macro|MC_TIMING_CNTL
mdefine_line|#define MC_TIMING_CNTL                         0x0144
DECL|macro|MC_AGP_LOCATION
mdefine_line|#define MC_AGP_LOCATION                        0x014C  
DECL|macro|MEM_IO_CNTL_A0
mdefine_line|#define MEM_IO_CNTL_A0                         0x0178  
DECL|macro|MEM_REFRESH_CNTL
mdefine_line|#define MEM_REFRESH_CNTL                       0x0178
DECL|macro|MEM_INIT_LATENCY_TIMER
mdefine_line|#define MEM_INIT_LATENCY_TIMER                 0x0154  
DECL|macro|MC_INIT_GFX_LAT_TIMER
mdefine_line|#define MC_INIT_GFX_LAT_TIMER                  0x0154
DECL|macro|MEM_SDRAM_MODE_REG
mdefine_line|#define MEM_SDRAM_MODE_REG                     0x0158  
DECL|macro|AGP_BASE
mdefine_line|#define AGP_BASE                               0x0170  
DECL|macro|MEM_IO_CNTL_A1
mdefine_line|#define MEM_IO_CNTL_A1                         0x017C  
DECL|macro|MC_READ_CNTL_AB
mdefine_line|#define MC_READ_CNTL_AB                        0x017C
DECL|macro|MEM_IO_CNTL_B0
mdefine_line|#define MEM_IO_CNTL_B0                         0x0180
DECL|macro|MC_INIT_MISC_LAT_TIMER
mdefine_line|#define MC_INIT_MISC_LAT_TIMER                 0x0180
DECL|macro|MEM_IO_CNTL_B1
mdefine_line|#define MEM_IO_CNTL_B1                         0x0184
DECL|macro|MC_IOPAD_CNTL
mdefine_line|#define MC_IOPAD_CNTL                          0x0184
DECL|macro|MC_DEBUG
mdefine_line|#define MC_DEBUG                               0x0188
DECL|macro|MC_STATUS
mdefine_line|#define MC_STATUS                              0x0150  
DECL|macro|MEM_IO_OE_CNTL
mdefine_line|#define MEM_IO_OE_CNTL                         0x018C  
DECL|macro|MC_CHIP_IO_OE_CNTL_AB
mdefine_line|#define MC_CHIP_IO_OE_CNTL_AB                  0x018C
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
DECL|macro|CRTC2_GEN_CNTL
mdefine_line|#define CRTC2_GEN_CNTL                         0x03f8  
DECL|macro|CRTC2_DISPLAY_BASE_ADDR
mdefine_line|#define CRTC2_DISPLAY_BASE_ADDR                0x033c
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
DECL|macro|GPIO_CRT2_DDC
mdefine_line|#define GPIO_CRT2_DDC                          0x006c
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
DECL|macro|CRTC_H_CUTOFF_ACTIVE_EN
mdefine_line|#define CRTC_H_CUTOFF_ACTIVE_EN                (1&lt;&lt;4)
DECL|macro|CRTC_V_CUTOFF_ACTIVE_EN
mdefine_line|#define CRTC_V_CUTOFF_ACTIVE_EN                (1&lt;&lt;5)
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
singleline_comment|//#define DDA_CONFIG&t;&t;&t;       0x02e0
singleline_comment|//#define DDA_ON_OFF&t;&t;&t;       0x02e4
DECL|macro|DVI_I2C_CNTL_1
mdefine_line|#define DVI_I2C_CNTL_1&t;&t;&t;       0x02e4
DECL|macro|GRPH_BUFFER_CNTL
mdefine_line|#define GRPH_BUFFER_CNTL                       0x02F0
DECL|macro|GRPH2_BUFFER_CNTL
mdefine_line|#define GRPH2_BUFFER_CNTL                      0x03F0
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
DECL|macro|DST_OFFSET
mdefine_line|#define DST_OFFSET                             0x1404
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
DECL|macro|DEFAULT_SC_TOP_LEFT
mdefine_line|#define DEFAULT_SC_TOP_LEFT                    0x16EC
DECL|macro|SRC_PITCH_OFFSET
mdefine_line|#define SRC_PITCH_OFFSET                       0x1428
DECL|macro|DST_PITCH_OFFSET
mdefine_line|#define DST_PITCH_OFFSET                       0x142C
DECL|macro|DP_GUI_MASTER_CNTL
mdefine_line|#define DP_GUI_MASTER_CNTL                     0x146C  
DECL|macro|SC_TOP_LEFT
mdefine_line|#define SC_TOP_LEFT                            0x16EC  
DECL|macro|SC_BOTTOM_RIGHT
mdefine_line|#define SC_BOTTOM_RIGHT                        0x16F0  
DECL|macro|SRC_SC_BOTTOM_RIGHT
mdefine_line|#define SRC_SC_BOTTOM_RIGHT                    0x16F4  
DECL|macro|RB2D_DSTCACHE_MODE
mdefine_line|#define RB2D_DSTCACHE_MODE&t;&t;       0x3428
DECL|macro|RB2D_DSTCACHE_CTLSTAT
mdefine_line|#define RB2D_DSTCACHE_CTLSTAT&t;&t;       0x342C
DECL|macro|LVDS_GEN_CNTL
mdefine_line|#define LVDS_GEN_CNTL&t;&t;&t;       0x02d0
DECL|macro|LVDS_PLL_CNTL
mdefine_line|#define LVDS_PLL_CNTL&t;&t;&t;       0x02d4
DECL|macro|FP2_GEN_CNTL
mdefine_line|#define FP2_GEN_CNTL                           0x0288
DECL|macro|TMDS_CNTL
mdefine_line|#define TMDS_CNTL                              0x0294
DECL|macro|TMDS_CRC
mdefine_line|#define TMDS_CRC&t;&t;&t;       0x02a0
DECL|macro|TMDS_TRANSMITTER_CNTL
mdefine_line|#define TMDS_TRANSMITTER_CNTL&t;&t;       0x02a4
DECL|macro|MPP_TB_CONFIG
mdefine_line|#define MPP_TB_CONFIG            &t;       0x01c0
DECL|macro|PAMAC0_DLY_CNTL
mdefine_line|#define PAMAC0_DLY_CNTL                        0x0a94
DECL|macro|PAMAC1_DLY_CNTL
mdefine_line|#define PAMAC1_DLY_CNTL                        0x0a98
DECL|macro|PAMAC2_DLY_CNTL
mdefine_line|#define PAMAC2_DLY_CNTL                        0x0a9c
DECL|macro|FW_CNTL
mdefine_line|#define FW_CNTL                                0x0118
DECL|macro|FCP_CNTL
mdefine_line|#define FCP_CNTL                               0x0910
DECL|macro|VGA_DDA_ON_OFF
mdefine_line|#define VGA_DDA_ON_OFF                         0x02ec
DECL|macro|TV_MASTER_CNTL
mdefine_line|#define TV_MASTER_CNTL                         0x0800
singleline_comment|//#define BASE_CODE&t;&t;&t;       0x0f0b
DECL|macro|BIOS_0_SCRATCH
mdefine_line|#define BIOS_0_SCRATCH&t;&t;&t;       0x0010
DECL|macro|BIOS_1_SCRATCH
mdefine_line|#define BIOS_1_SCRATCH&t;&t;&t;       0x0014
DECL|macro|BIOS_2_SCRATCH
mdefine_line|#define BIOS_2_SCRATCH&t;&t;&t;       0x0018
DECL|macro|BIOS_3_SCRATCH
mdefine_line|#define BIOS_3_SCRATCH&t;&t;&t;       0x001c
DECL|macro|BIOS_4_SCRATCH
mdefine_line|#define BIOS_4_SCRATCH&t;&t;&t;       0x0020
DECL|macro|BIOS_5_SCRATCH
mdefine_line|#define BIOS_5_SCRATCH&t;&t;&t;       0x0024
DECL|macro|BIOS_6_SCRATCH
mdefine_line|#define BIOS_6_SCRATCH&t;&t;&t;       0x0028
DECL|macro|BIOS_7_SCRATCH
mdefine_line|#define BIOS_7_SCRATCH&t;&t;&t;       0x002c
DECL|macro|HDP_SOFT_RESET
mdefine_line|#define HDP_SOFT_RESET                         (1 &lt;&lt; 26)
DECL|macro|TV_DAC_CNTL
mdefine_line|#define TV_DAC_CNTL                            0x088c
DECL|macro|GPIOPAD_MASK
mdefine_line|#define GPIOPAD_MASK                           0x0198
DECL|macro|GPIOPAD_A
mdefine_line|#define GPIOPAD_A                              0x019c
DECL|macro|GPIOPAD_EN
mdefine_line|#define GPIOPAD_EN                             0x01a0
DECL|macro|GPIOPAD_Y
mdefine_line|#define GPIOPAD_Y                              0x01a4
DECL|macro|ZV_LCDPAD_MASK
mdefine_line|#define ZV_LCDPAD_MASK                         0x01a8
DECL|macro|ZV_LCDPAD_A
mdefine_line|#define ZV_LCDPAD_A                            0x01ac
DECL|macro|ZV_LCDPAD_EN
mdefine_line|#define ZV_LCDPAD_EN                           0x01b0
DECL|macro|ZV_LCDPAD_Y
mdefine_line|#define ZV_LCDPAD_Y                            0x01b4
multiline_comment|/* PLL Registers */
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
DECL|macro|MDLL_CKO
mdefine_line|#define MDLL_CKO                                   0x000f
DECL|macro|MDLL_RDCKA
mdefine_line|#define MDLL_RDCKA                                 0x0010
DECL|macro|MCLK_CNTL
mdefine_line|#define MCLK_CNTL                                  0x0012
DECL|macro|AGP_PLL_CNTL
mdefine_line|#define AGP_PLL_CNTL                               0x000b
DECL|macro|PLL_TEST_CNTL
mdefine_line|#define PLL_TEST_CNTL                              0x0013
DECL|macro|CLK_PWRMGT_CNTL
mdefine_line|#define CLK_PWRMGT_CNTL                            0x0014
DECL|macro|PLL_PWRMGT_CNTL
mdefine_line|#define PLL_PWRMGT_CNTL                            0x0015
DECL|macro|MCLK_MISC
mdefine_line|#define MCLK_MISC                                  0x001f
DECL|macro|P2PLL_CNTL
mdefine_line|#define P2PLL_CNTL                                 0x002a
DECL|macro|P2PLL_REF_DIV
mdefine_line|#define P2PLL_REF_DIV                              0x002b
DECL|macro|PIXCLKS_CNTL
mdefine_line|#define PIXCLKS_CNTL                               0x002d
DECL|macro|SCLK_MORE_CNTL
mdefine_line|#define SCLK_MORE_CNTL&t;&t;&t;&t;   0x0035
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
multiline_comment|/* SCLK_CNTL bit constants */
DECL|macro|DYN_STOP_LAT_MASK
mdefine_line|#define DYN_STOP_LAT_MASK&t;&t;&t;   0x00007ff8
DECL|macro|CP_MAX_DYN_STOP_LAT
mdefine_line|#define CP_MAX_DYN_STOP_LAT&t;&t;&t;   0x0008
DECL|macro|SCLK_FORCEON_MASK
mdefine_line|#define SCLK_FORCEON_MASK&t;&t;&t;   0xffff8000
multiline_comment|/* SCLK_MORE_CNTL bit constants */
DECL|macro|SCLK_MORE_FORCEON
mdefine_line|#define SCLK_MORE_FORCEON&t;&t;&t;   0x0700
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
multiline_comment|/* PIXCLKS_CNTL */
DECL|macro|PIX2CLK_SRC_SEL_MASK
mdefine_line|#define PIX2CLK_SRC_SEL_MASK                       0x03
DECL|macro|PIX2CLK_SRC_SEL_CPUCLK
mdefine_line|#define PIX2CLK_SRC_SEL_CPUCLK                     0x00
DECL|macro|PIX2CLK_SRC_SEL_PSCANCLK
mdefine_line|#define PIX2CLK_SRC_SEL_PSCANCLK                   0x01
DECL|macro|PIX2CLK_SRC_SEL_BYTECLK
mdefine_line|#define PIX2CLK_SRC_SEL_BYTECLK                    0x02
DECL|macro|PIX2CLK_SRC_SEL_P2PLLCLK
mdefine_line|#define PIX2CLK_SRC_SEL_P2PLLCLK                   0x03
DECL|macro|PIX2CLK_ALWAYS_ONb
mdefine_line|#define PIX2CLK_ALWAYS_ONb                         (1&lt;&lt;6)
DECL|macro|PIX2CLK_DAC_ALWAYS_ONb
mdefine_line|#define PIX2CLK_DAC_ALWAYS_ONb                     (1&lt;&lt;7)
DECL|macro|PIXCLK_TV_SRC_SEL
mdefine_line|#define PIXCLK_TV_SRC_SEL                          (1 &lt;&lt; 8)
DECL|macro|PIXCLK_LVDS_ALWAYS_ONb
mdefine_line|#define PIXCLK_LVDS_ALWAYS_ONb                     (1 &lt;&lt; 14)
DECL|macro|PIXCLK_TMDS_ALWAYS_ONb
mdefine_line|#define PIXCLK_TMDS_ALWAYS_ONb                     (1 &lt;&lt; 15)
multiline_comment|/* CLOCK_CNTL_INDEX bit constants */
DECL|macro|PLL_WR_EN
mdefine_line|#define PLL_WR_EN                                  0x00000080
multiline_comment|/* CONFIG_CNTL bit constants */
DECL|macro|CFG_VGA_RAM_EN
mdefine_line|#define CFG_VGA_RAM_EN                             0x00000100
DECL|macro|CFG_ATI_REV_ID_MASK
mdefine_line|#define CFG_ATI_REV_ID_MASK&t;&t;&t;   (0xf &lt;&lt; 16)
DECL|macro|CFG_ATI_REV_A11
mdefine_line|#define CFG_ATI_REV_A11&t;&t;&t;&t;   (0 &lt;&lt; 16)
DECL|macro|CFG_ATI_REV_A12
mdefine_line|#define CFG_ATI_REV_A12&t;&t;&t;&t;   (1 &lt;&lt; 16)
DECL|macro|CFG_ATI_REV_A13
mdefine_line|#define CFG_ATI_REV_A13&t;&t;&t;&t;   (2 &lt;&lt; 16)
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
DECL|macro|CRTC_CRT_ON
mdefine_line|#define CRTC_CRT_ON&t;&t;&t;&t;   (1 &lt;&lt; 15)
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
DECL|macro|CRTC_INTERLACE_EN
mdefine_line|#define CRTC_INTERLACE_EN&t;&t;&t;   (1 &lt;&lt; 1)
DECL|macro|CRTC_BYPASS_LUT_EN
mdefine_line|#define CRTC_BYPASS_LUT_EN     &t;&t;&t;   (1 &lt;&lt; 14)
DECL|macro|CRTC_EXT_DISP_EN
mdefine_line|#define CRTC_EXT_DISP_EN      &t;&t;&t;   (1 &lt;&lt; 24)
DECL|macro|CRTC_EN
mdefine_line|#define CRTC_EN&t;&t;&t;&t;&t;   (1 &lt;&lt; 25)
DECL|macro|CRTC_DISP_REQ_EN_B
mdefine_line|#define CRTC_DISP_REQ_EN_B                         (1 &lt;&lt; 26)
multiline_comment|/* CRTC_STATUS bit constants */
DECL|macro|CRTC_VBLANK
mdefine_line|#define CRTC_VBLANK                                0x00000001
multiline_comment|/* CRTC2_GEN_CNTL bit constants */
DECL|macro|CRT2_ON
mdefine_line|#define CRT2_ON                                    (1 &lt;&lt; 7)
DECL|macro|CRTC2_DISPLAY_DIS
mdefine_line|#define CRTC2_DISPLAY_DIS                          (1 &lt;&lt; 23)
DECL|macro|CRTC2_EN
mdefine_line|#define CRTC2_EN                                   (1 &lt;&lt; 25)
DECL|macro|CRTC2_DISP_REQ_EN_B
mdefine_line|#define CRTC2_DISP_REQ_EN_B                        (1 &lt;&lt; 26)
multiline_comment|/* CUR_OFFSET, CUR_HORZ_VERT_POSN, CUR_HORZ_VERT_OFF bit constants */
DECL|macro|CUR_LOCK
mdefine_line|#define CUR_LOCK                                   0x80000000
multiline_comment|/* GPIO bit constants */
DECL|macro|GPIO_A_0
mdefine_line|#define GPIO_A_0&t;&t;(1 &lt;&lt;  0)
DECL|macro|GPIO_A_1
mdefine_line|#define GPIO_A_1&t;&t;(1 &lt;&lt;  1)
DECL|macro|GPIO_Y_0
mdefine_line|#define GPIO_Y_0&t;&t;(1 &lt;&lt;  8)
DECL|macro|GPIO_Y_1
mdefine_line|#define GPIO_Y_1&t;&t;(1 &lt;&lt;  9)
DECL|macro|GPIO_EN_0
mdefine_line|#define GPIO_EN_0&t;&t;(1 &lt;&lt; 16)
DECL|macro|GPIO_EN_1
mdefine_line|#define GPIO_EN_1&t;&t;(1 &lt;&lt; 17)
DECL|macro|GPIO_MASK_0
mdefine_line|#define GPIO_MASK_0&t;&t;(1 &lt;&lt; 24)
DECL|macro|GPIO_MASK_1
mdefine_line|#define GPIO_MASK_1&t;&t;(1 &lt;&lt; 25)
DECL|macro|VGA_DDC_DATA_OUTPUT
mdefine_line|#define VGA_DDC_DATA_OUTPUT&t;GPIO_A_0
DECL|macro|VGA_DDC_CLK_OUTPUT
mdefine_line|#define VGA_DDC_CLK_OUTPUT&t;GPIO_A_1
DECL|macro|VGA_DDC_DATA_INPUT
mdefine_line|#define VGA_DDC_DATA_INPUT&t;GPIO_Y_0
DECL|macro|VGA_DDC_CLK_INPUT
mdefine_line|#define VGA_DDC_CLK_INPUT&t;GPIO_Y_1
DECL|macro|VGA_DDC_DATA_OUT_EN
mdefine_line|#define VGA_DDC_DATA_OUT_EN&t;GPIO_EN_0
DECL|macro|VGA_DDC_CLK_OUT_EN
mdefine_line|#define VGA_DDC_CLK_OUT_EN&t;GPIO_EN_1
multiline_comment|/* FP bit constants */
DECL|macro|FP_CRTC_H_TOTAL_MASK
mdefine_line|#define FP_CRTC_H_TOTAL_MASK&t;&t;&t;   0x000003ff
DECL|macro|FP_CRTC_H_DISP_MASK
mdefine_line|#define FP_CRTC_H_DISP_MASK&t;&t;&t;   0x01ff0000
DECL|macro|FP_CRTC_V_TOTAL_MASK
mdefine_line|#define FP_CRTC_V_TOTAL_MASK&t;&t;&t;   0x00000fff
DECL|macro|FP_CRTC_V_DISP_MASK
mdefine_line|#define FP_CRTC_V_DISP_MASK&t;&t;&t;   0x0fff0000
DECL|macro|FP_H_SYNC_STRT_CHAR_MASK
mdefine_line|#define FP_H_SYNC_STRT_CHAR_MASK&t;&t;   0x00001ff8
DECL|macro|FP_H_SYNC_WID_MASK
mdefine_line|#define FP_H_SYNC_WID_MASK&t;&t;&t;   0x003f0000
DECL|macro|FP_V_SYNC_STRT_MASK
mdefine_line|#define FP_V_SYNC_STRT_MASK&t;&t;&t;   0x00000fff
DECL|macro|FP_V_SYNC_WID_MASK
mdefine_line|#define FP_V_SYNC_WID_MASK&t;&t;&t;   0x001f0000
DECL|macro|FP_CRTC_H_TOTAL_SHIFT
mdefine_line|#define FP_CRTC_H_TOTAL_SHIFT&t;&t;&t;   0x00000000
DECL|macro|FP_CRTC_H_DISP_SHIFT
mdefine_line|#define FP_CRTC_H_DISP_SHIFT&t;&t;&t;   0x00000010
DECL|macro|FP_CRTC_V_TOTAL_SHIFT
mdefine_line|#define FP_CRTC_V_TOTAL_SHIFT&t;&t;&t;   0x00000000
DECL|macro|FP_CRTC_V_DISP_SHIFT
mdefine_line|#define FP_CRTC_V_DISP_SHIFT&t;&t;&t;   0x00000010
DECL|macro|FP_H_SYNC_STRT_CHAR_SHIFT
mdefine_line|#define FP_H_SYNC_STRT_CHAR_SHIFT&t;&t;   0x00000003
DECL|macro|FP_H_SYNC_WID_SHIFT
mdefine_line|#define FP_H_SYNC_WID_SHIFT&t;&t;&t;   0x00000010
DECL|macro|FP_V_SYNC_STRT_SHIFT
mdefine_line|#define FP_V_SYNC_STRT_SHIFT&t;&t;&t;   0x00000000
DECL|macro|FP_V_SYNC_WID_SHIFT
mdefine_line|#define FP_V_SYNC_WID_SHIFT&t;&t;&t;   0x00000010
multiline_comment|/* FP_GEN_CNTL bit constants */
DECL|macro|FP_FPON
mdefine_line|#define FP_FPON&t;&t;&t;&t;&t;   (1 &lt;&lt; 0)
DECL|macro|FP_TMDS_EN
mdefine_line|#define FP_TMDS_EN&t;&t;&t;&t;   (1 &lt;&lt; 2)
DECL|macro|FP_PANEL_FORMAT
mdefine_line|#define FP_PANEL_FORMAT                            (1 &lt;&lt; 3)
DECL|macro|FP_EN_TMDS
mdefine_line|#define FP_EN_TMDS&t;&t;&t;&t;   (1 &lt;&lt; 7)
DECL|macro|FP_DETECT_SENSE
mdefine_line|#define FP_DETECT_SENSE&t;&t;&t;&t;   (1 &lt;&lt; 8)
DECL|macro|R200_FP_SOURCE_SEL_MASK
mdefine_line|#define R200_FP_SOURCE_SEL_MASK                    (3 &lt;&lt; 10)
DECL|macro|R200_FP_SOURCE_SEL_CRTC1
mdefine_line|#define R200_FP_SOURCE_SEL_CRTC1                   (0 &lt;&lt; 10)
DECL|macro|R200_FP_SOURCE_SEL_CRTC2
mdefine_line|#define R200_FP_SOURCE_SEL_CRTC2                   (1 &lt;&lt; 10)
DECL|macro|R200_FP_SOURCE_SEL_RMX
mdefine_line|#define R200_FP_SOURCE_SEL_RMX                     (2 &lt;&lt; 10)
DECL|macro|R200_FP_SOURCE_SEL_TRANS
mdefine_line|#define R200_FP_SOURCE_SEL_TRANS                   (3 &lt;&lt; 10)
DECL|macro|FP_SEL_CRTC1
mdefine_line|#define FP_SEL_CRTC1&t;&t;&t;&t;   (0 &lt;&lt; 13)
DECL|macro|FP_SEL_CRTC2
mdefine_line|#define FP_SEL_CRTC2&t;&t;&t;&t;   (1 &lt;&lt; 13)
DECL|macro|FP_USE_VGA_HSYNC
mdefine_line|#define FP_USE_VGA_HSYNC                           (1 &lt;&lt; 14)
DECL|macro|FP_CRTC_DONT_SHADOW_HPAR
mdefine_line|#define FP_CRTC_DONT_SHADOW_HPAR&t;&t;   (1 &lt;&lt; 15)
DECL|macro|FP_CRTC_DONT_SHADOW_VPAR
mdefine_line|#define FP_CRTC_DONT_SHADOW_VPAR&t;&t;   (1 &lt;&lt; 16)
DECL|macro|FP_CRTC_DONT_SHADOW_HEND
mdefine_line|#define FP_CRTC_DONT_SHADOW_HEND&t;&t;   (1 &lt;&lt; 17)
DECL|macro|FP_CRTC_USE_SHADOW_VEND
mdefine_line|#define FP_CRTC_USE_SHADOW_VEND&t;&t;&t;   (1 &lt;&lt; 18)
DECL|macro|FP_RMX_HVSYNC_CONTROL_EN
mdefine_line|#define FP_RMX_HVSYNC_CONTROL_EN&t;&t;   (1 &lt;&lt; 20)
DECL|macro|FP_DFP_SYNC_SEL
mdefine_line|#define FP_DFP_SYNC_SEL&t;&t;&t;&t;   (1 &lt;&lt; 21)
DECL|macro|FP_CRTC_LOCK_8DOT
mdefine_line|#define FP_CRTC_LOCK_8DOT&t;&t;&t;   (1 &lt;&lt; 22)
DECL|macro|FP_CRT_SYNC_SEL
mdefine_line|#define FP_CRT_SYNC_SEL&t;&t;&t;&t;   (1 &lt;&lt; 23)
DECL|macro|FP_USE_SHADOW_EN
mdefine_line|#define FP_USE_SHADOW_EN&t;&t;&t;   (1 &lt;&lt; 24)
DECL|macro|FP_CRT_SYNC_ALT
mdefine_line|#define FP_CRT_SYNC_ALT&t;&t;&t;&t;   (1 &lt;&lt; 26)
multiline_comment|/* FP2_GEN_CNTL bit constants */
DECL|macro|FP2_BLANK_EN
mdefine_line|#define FP2_BLANK_EN             (1 &lt;&lt;  1)
DECL|macro|FP2_ON
mdefine_line|#define FP2_ON                   (1 &lt;&lt;  2)
DECL|macro|FP2_PANEL_FORMAT
mdefine_line|#define FP2_PANEL_FORMAT         (1 &lt;&lt;  3)
DECL|macro|FP2_SOURCE_SEL_MASK
mdefine_line|#define FP2_SOURCE_SEL_MASK      (3 &lt;&lt; 10)
DECL|macro|FP2_SOURCE_SEL_CRTC2
mdefine_line|#define FP2_SOURCE_SEL_CRTC2     (1 &lt;&lt; 10)
DECL|macro|FP2_SRC_SEL_MASK
mdefine_line|#define FP2_SRC_SEL_MASK         (3 &lt;&lt; 13)
DECL|macro|FP2_SRC_SEL_CRTC2
mdefine_line|#define FP2_SRC_SEL_CRTC2        (1 &lt;&lt; 13)
DECL|macro|FP2_FP_POL
mdefine_line|#define FP2_FP_POL               (1 &lt;&lt; 16)
DECL|macro|FP2_LP_POL
mdefine_line|#define FP2_LP_POL               (1 &lt;&lt; 17)
DECL|macro|FP2_SCK_POL
mdefine_line|#define FP2_SCK_POL              (1 &lt;&lt; 18)
DECL|macro|FP2_LCD_CNTL_MASK
mdefine_line|#define FP2_LCD_CNTL_MASK        (7 &lt;&lt; 19)
DECL|macro|FP2_PAD_FLOP_EN
mdefine_line|#define FP2_PAD_FLOP_EN          (1 &lt;&lt; 22)
DECL|macro|FP2_CRC_EN
mdefine_line|#define FP2_CRC_EN               (1 &lt;&lt; 23)
DECL|macro|FP2_CRC_READ_EN
mdefine_line|#define FP2_CRC_READ_EN          (1 &lt;&lt; 24)
DECL|macro|FP2_DV0_EN
mdefine_line|#define FP2_DV0_EN               (1 &lt;&lt; 25)
DECL|macro|FP2_DV0_RATE_SEL_SDR
mdefine_line|#define FP2_DV0_RATE_SEL_SDR     (1 &lt;&lt; 26)
multiline_comment|/* LVDS_GEN_CNTL bit constants */
DECL|macro|LVDS_ON
mdefine_line|#define LVDS_ON&t;&t;&t;&t;&t;   (1 &lt;&lt; 0)
DECL|macro|LVDS_DISPLAY_DIS
mdefine_line|#define LVDS_DISPLAY_DIS&t;&t;&t;   (1 &lt;&lt; 1)
DECL|macro|LVDS_PANEL_TYPE
mdefine_line|#define LVDS_PANEL_TYPE&t;&t;&t;&t;   (1 &lt;&lt; 2)
DECL|macro|LVDS_PANEL_FORMAT
mdefine_line|#define LVDS_PANEL_FORMAT&t;&t;&t;   (1 &lt;&lt; 3)
DECL|macro|LVDS_EN
mdefine_line|#define LVDS_EN&t;&t;&t;&t;&t;   (1 &lt;&lt; 7)
DECL|macro|LVDS_BL_MOD_LEVEL_MASK
mdefine_line|#define LVDS_BL_MOD_LEVEL_MASK&t;&t;&t;   0x0000ff00
DECL|macro|LVDS_BL_MOD_LEVEL_SHIFT
mdefine_line|#define LVDS_BL_MOD_LEVEL_SHIFT&t;&t;&t;   8
DECL|macro|LVDS_BL_MOD_EN
mdefine_line|#define LVDS_BL_MOD_EN&t;&t;&t;&t;   (1 &lt;&lt; 16)
DECL|macro|LVDS_DIGON
mdefine_line|#define LVDS_DIGON&t;&t;&t;&t;   (1 &lt;&lt; 18)
DECL|macro|LVDS_BLON
mdefine_line|#define LVDS_BLON&t;&t;&t;&t;   (1 &lt;&lt; 19)
DECL|macro|LVDS_SEL_CRTC2
mdefine_line|#define LVDS_SEL_CRTC2&t;&t;&t;&t;   (1 &lt;&lt; 23)
DECL|macro|LVDS_STATE_MASK
mdefine_line|#define LVDS_STATE_MASK&t;&bslash;&n;&t;(LVDS_ON | LVDS_DISPLAY_DIS | LVDS_BL_MOD_LEVEL_MASK | LVDS_BLON)
multiline_comment|/* LVDS_PLL_CNTL bit constatns */
DECL|macro|HSYNC_DELAY_SHIFT
mdefine_line|#define HSYNC_DELAY_SHIFT&t;&t;&t;   0x1c
DECL|macro|HSYNC_DELAY_MASK
mdefine_line|#define HSYNC_DELAY_MASK&t;&t;&t;   (0xf &lt;&lt; 0x1c)
multiline_comment|/* TMDS_TRANSMITTER_CNTL bit constants */
DECL|macro|TMDS_PLL_EN
mdefine_line|#define TMDS_PLL_EN&t;&t;&t;&t;   (1 &lt;&lt; 0)
DECL|macro|TMDS_PLLRST
mdefine_line|#define TMDS_PLLRST&t;&t;&t;&t;   (1 &lt;&lt; 1)
DECL|macro|TMDS_RAN_PAT_RST
mdefine_line|#define TMDS_RAN_PAT_RST&t;&t;&t;   (1 &lt;&lt; 7)
DECL|macro|TMDS_ICHCSEL
mdefine_line|#define TMDS_ICHCSEL&t;&t;&t;&t;   (1 &lt;&lt; 28)
multiline_comment|/* FP_HORZ_STRETCH bit constants */
DECL|macro|HORZ_STRETCH_RATIO_MASK
mdefine_line|#define HORZ_STRETCH_RATIO_MASK&t;&t;&t;   0xffff
DECL|macro|HORZ_STRETCH_RATIO_MAX
mdefine_line|#define HORZ_STRETCH_RATIO_MAX&t;&t;&t;   4096
DECL|macro|HORZ_PANEL_SIZE
mdefine_line|#define HORZ_PANEL_SIZE&t;&t;&t;&t;   (0x1ff &lt;&lt; 16)
DECL|macro|HORZ_PANEL_SHIFT
mdefine_line|#define HORZ_PANEL_SHIFT&t;&t;&t;   16
DECL|macro|HORZ_STRETCH_PIXREP
mdefine_line|#define HORZ_STRETCH_PIXREP&t;&t;&t;   (0 &lt;&lt; 25)
DECL|macro|HORZ_STRETCH_BLEND
mdefine_line|#define HORZ_STRETCH_BLEND&t;&t;&t;   (1 &lt;&lt; 26)
DECL|macro|HORZ_STRETCH_ENABLE
mdefine_line|#define HORZ_STRETCH_ENABLE&t;&t;&t;   (1 &lt;&lt; 25)
DECL|macro|HORZ_AUTO_RATIO
mdefine_line|#define HORZ_AUTO_RATIO&t;&t;&t;&t;   (1 &lt;&lt; 27)
DECL|macro|HORZ_FP_LOOP_STRETCH
mdefine_line|#define HORZ_FP_LOOP_STRETCH&t;&t;&t;   (0x7 &lt;&lt; 28)
DECL|macro|HORZ_AUTO_RATIO_INC
mdefine_line|#define HORZ_AUTO_RATIO_INC&t;&t;&t;   (1 &lt;&lt; 31)
multiline_comment|/* FP_VERT_STRETCH bit constants */
DECL|macro|VERT_STRETCH_RATIO_MASK
mdefine_line|#define VERT_STRETCH_RATIO_MASK&t;&t;&t;   0xfff
DECL|macro|VERT_STRETCH_RATIO_MAX
mdefine_line|#define VERT_STRETCH_RATIO_MAX&t;&t;&t;   4096
DECL|macro|VERT_PANEL_SIZE
mdefine_line|#define VERT_PANEL_SIZE&t;&t;&t;&t;   (0xfff &lt;&lt; 12)
DECL|macro|VERT_PANEL_SHIFT
mdefine_line|#define VERT_PANEL_SHIFT&t;&t;&t;   12
DECL|macro|VERT_STRETCH_LINREP
mdefine_line|#define VERT_STRETCH_LINREP&t;&t;&t;   (0 &lt;&lt; 26)
DECL|macro|VERT_STRETCH_BLEND
mdefine_line|#define VERT_STRETCH_BLEND&t;&t;&t;   (1 &lt;&lt; 26)
DECL|macro|VERT_STRETCH_ENABLE
mdefine_line|#define VERT_STRETCH_ENABLE&t;&t;&t;   (1 &lt;&lt; 25)
DECL|macro|VERT_AUTO_RATIO_EN
mdefine_line|#define VERT_AUTO_RATIO_EN&t;&t;&t;   (1 &lt;&lt; 27)
DECL|macro|VERT_FP_LOOP_STRETCH
mdefine_line|#define VERT_FP_LOOP_STRETCH&t;&t;&t;   (0x7 &lt;&lt; 28)
DECL|macro|VERT_STRETCH_RESERVED
mdefine_line|#define VERT_STRETCH_RESERVED&t;&t;&t;   0xf1000000
multiline_comment|/* DAC_CNTL bit constants */
DECL|macro|DAC_8BIT_EN
mdefine_line|#define DAC_8BIT_EN                                0x00000100
DECL|macro|DAC_4BPP_PIX_ORDER
mdefine_line|#define DAC_4BPP_PIX_ORDER                         0x00000200
DECL|macro|DAC_CRC_EN
mdefine_line|#define DAC_CRC_EN                                 0x00080000
DECL|macro|DAC_MASK_ALL
mdefine_line|#define DAC_MASK_ALL&t;&t;&t;&t;   (0xff &lt;&lt; 24)
DECL|macro|DAC_PDWN
mdefine_line|#define DAC_PDWN                                   (1 &lt;&lt; 15)
DECL|macro|DAC_EXPAND_MODE
mdefine_line|#define DAC_EXPAND_MODE&t;&t;&t;&t;   (1 &lt;&lt; 14)
DECL|macro|DAC_VGA_ADR_EN
mdefine_line|#define DAC_VGA_ADR_EN&t;&t;&t;&t;   (1 &lt;&lt; 13)
DECL|macro|DAC_RANGE_CNTL
mdefine_line|#define DAC_RANGE_CNTL&t;&t;&t;&t;   (3 &lt;&lt;  0)
DECL|macro|DAC_RANGE_CNTL_MASK
mdefine_line|#define DAC_RANGE_CNTL_MASK    &t;&t;&t;   0x03
DECL|macro|DAC_BLANKING
mdefine_line|#define DAC_BLANKING&t;&t;&t;&t;   (1 &lt;&lt;  2)
DECL|macro|DAC_CMP_EN
mdefine_line|#define DAC_CMP_EN                                 (1 &lt;&lt;  3)
DECL|macro|DAC_CMP_OUTPUT
mdefine_line|#define DAC_CMP_OUTPUT                             (1 &lt;&lt;  7)
multiline_comment|/* DAC_CNTL2 bit constants */
DECL|macro|DAC2_EXPAND_MODE
mdefine_line|#define DAC2_EXPAND_MODE&t;&t;&t;   (1 &lt;&lt; 14)
DECL|macro|DAC2_CMP_EN
mdefine_line|#define DAC2_CMP_EN                                (1 &lt;&lt; 7)
DECL|macro|DAC2_PALETTE_ACCESS_CNTL
mdefine_line|#define DAC2_PALETTE_ACCESS_CNTL                   (1 &lt;&lt; 5)
multiline_comment|/* DAC_EXT_CNTL bit constants */
DECL|macro|DAC_FORCE_BLANK_OFF_EN
mdefine_line|#define DAC_FORCE_BLANK_OFF_EN                     (1 &lt;&lt; 4)
DECL|macro|DAC_FORCE_DATA_EN
mdefine_line|#define DAC_FORCE_DATA_EN                          (1 &lt;&lt; 5)
DECL|macro|DAC_FORCE_DATA_SEL_MASK
mdefine_line|#define DAC_FORCE_DATA_SEL_MASK                    (3 &lt;&lt; 6)
DECL|macro|DAC_FORCE_DATA_MASK
mdefine_line|#define DAC_FORCE_DATA_MASK                        0x0003ff00
DECL|macro|DAC_FORCE_DATA_SHIFT
mdefine_line|#define DAC_FORCE_DATA_SHIFT                       8
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
DECL|macro|MEM_NUM_CHANNELS_MASK
mdefine_line|#define MEM_NUM_CHANNELS_MASK &t;&t;&t;   0x00000001
DECL|macro|MEM_USE_B_CH_ONLY
mdefine_line|#define MEM_USE_B_CH_ONLY                          0x00000002
DECL|macro|RV100_MEM_HALF_MODE
mdefine_line|#define RV100_MEM_HALF_MODE                        0x00000008
DECL|macro|R300_MEM_NUM_CHANNELS_MASK
mdefine_line|#define R300_MEM_NUM_CHANNELS_MASK                 0x00000003
DECL|macro|R300_MEM_USE_CD_CH_ONLY
mdefine_line|#define R300_MEM_USE_CD_CH_ONLY                    0x00000004
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
multiline_comment|/* SURFACE_CNTL bit consants */
DECL|macro|SURF_TRANSLATION_DIS
mdefine_line|#define SURF_TRANSLATION_DIS&t;&t;&t;   (1 &lt;&lt; 8)
DECL|macro|NONSURF_AP0_SWP_16BPP
mdefine_line|#define NONSURF_AP0_SWP_16BPP&t;&t;&t;   (1 &lt;&lt; 20)
DECL|macro|NONSURF_AP0_SWP_32BPP
mdefine_line|#define NONSURF_AP0_SWP_32BPP&t;&t;&t;   (1 &lt;&lt; 21)
DECL|macro|NONSURF_AP1_SWP_16BPP
mdefine_line|#define NONSURF_AP1_SWP_16BPP&t;&t;&t;   (1 &lt;&lt; 22)
DECL|macro|NONSURF_AP1_SWP_32BPP
mdefine_line|#define NONSURF_AP1_SWP_32BPP&t;&t;&t;   (1 &lt;&lt; 23)
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
multiline_comment|/* MPLL_CNTL bit constants */
DECL|macro|MPLL_RESET
mdefine_line|#define MPLL_RESET                                 0x00000001
multiline_comment|/* MDLL_CKO bit constants */
DECL|macro|MCKOA_SLEEP
mdefine_line|#define MCKOA_SLEEP                                0x00000001
DECL|macro|MCKOA_RESET
mdefine_line|#define MCKOA_RESET                                0x00000002
DECL|macro|MCKOA_REF_SKEW_MASK
mdefine_line|#define MCKOA_REF_SKEW_MASK                        0x00000700
DECL|macro|MCKOA_FB_SKEW_MASK
mdefine_line|#define MCKOA_FB_SKEW_MASK                         0x00007000
multiline_comment|/* MDLL_RDCKA bit constants */
DECL|macro|MRDCKA0_SLEEP
mdefine_line|#define MRDCKA0_SLEEP                              0x00000001
DECL|macro|MRDCKA0_RESET
mdefine_line|#define MRDCKA0_RESET                              0x00000002
DECL|macro|MRDCKA1_SLEEP
mdefine_line|#define MRDCKA1_SLEEP                              0x00010000
DECL|macro|MRDCKA1_RESET
mdefine_line|#define MRDCKA1_RESET                              0x00020000
multiline_comment|/* VCLK_ECP_CNTL constants */
DECL|macro|VCLK_SRC_SEL_MASK
mdefine_line|#define VCLK_SRC_SEL_MASK                          0x03
DECL|macro|VCLK_SRC_SEL_CPUCLK
mdefine_line|#define VCLK_SRC_SEL_CPUCLK                        0x00
DECL|macro|VCLK_SRC_SEL_PSCANCLK
mdefine_line|#define VCLK_SRC_SEL_PSCANCLK                      0x01
DECL|macro|VCLK_SRC_SEL_BYTECLK
mdefine_line|#define VCLK_SRC_SEL_BYTECLK&t;                   0x02
DECL|macro|VCLK_SRC_SEL_PPLLCLK
mdefine_line|#define VCLK_SRC_SEL_PPLLCLK&t;&t;&t;   0x03
DECL|macro|PIXCLK_ALWAYS_ONb
mdefine_line|#define PIXCLK_ALWAYS_ONb                          0x00000040
DECL|macro|PIXCLK_DAC_ALWAYS_ONb
mdefine_line|#define PIXCLK_DAC_ALWAYS_ONb                      0x00000080
multiline_comment|/* BUS_CNTL1 constants */
DECL|macro|BUS_CNTL1_MOBILE_PLATFORM_SEL_MASK
mdefine_line|#define BUS_CNTL1_MOBILE_PLATFORM_SEL_MASK         0x0c000000
DECL|macro|BUS_CNTL1_MOBILE_PLATFORM_SEL_SHIFT
mdefine_line|#define BUS_CNTL1_MOBILE_PLATFORM_SEL_SHIFT        26
DECL|macro|BUS_CNTL1_AGPCLK_VALID
mdefine_line|#define BUS_CNTL1_AGPCLK_VALID                     0x80000000
multiline_comment|/* PLL_PWRMGT_CNTL constants */
DECL|macro|PLL_PWRMGT_CNTL_SPLL_TURNOFF
mdefine_line|#define PLL_PWRMGT_CNTL_SPLL_TURNOFF               0x00000002
DECL|macro|PLL_PWRMGT_CNTL_PPLL_TURNOFF
mdefine_line|#define PLL_PWRMGT_CNTL_PPLL_TURNOFF               0x00000004
DECL|macro|PLL_PWRMGT_CNTL_P2PLL_TURNOFF
mdefine_line|#define PLL_PWRMGT_CNTL_P2PLL_TURNOFF              0x00000008
DECL|macro|PLL_PWRMGT_CNTL_TVPLL_TURNOFF
mdefine_line|#define PLL_PWRMGT_CNTL_TVPLL_TURNOFF              0x00000010
DECL|macro|PLL_PWRMGT_CNTL_MOBILE_SU
mdefine_line|#define PLL_PWRMGT_CNTL_MOBILE_SU                  0x00010000
DECL|macro|PLL_PWRMGT_CNTL_SU_SCLK_USE_BCLK
mdefine_line|#define PLL_PWRMGT_CNTL_SU_SCLK_USE_BCLK           0x00020000
DECL|macro|PLL_PWRMGT_CNTL_SU_MCLK_USE_BCLK
mdefine_line|#define PLL_PWRMGT_CNTL_SU_MCLK_USE_BCLK           0x00040000
multiline_comment|/* TV_DAC_CNTL constants */
DECL|macro|TV_DAC_CNTL_BGSLEEP
mdefine_line|#define TV_DAC_CNTL_BGSLEEP                        0x00000040
DECL|macro|TV_DAC_CNTL_DETECT
mdefine_line|#define TV_DAC_CNTL_DETECT                         0x00000010
DECL|macro|TV_DAC_CNTL_BGADJ_MASK
mdefine_line|#define TV_DAC_CNTL_BGADJ_MASK                     0x000f0000
DECL|macro|TV_DAC_CNTL_DACADJ_MASK
mdefine_line|#define TV_DAC_CNTL_DACADJ_MASK                    0x00f00000
DECL|macro|TV_DAC_CNTL_BGADJ__SHIFT
mdefine_line|#define TV_DAC_CNTL_BGADJ__SHIFT                   16
DECL|macro|TV_DAC_CNTL_DACADJ__SHIFT
mdefine_line|#define TV_DAC_CNTL_DACADJ__SHIFT                  20
DECL|macro|TV_DAC_CNTL_RDACPD
mdefine_line|#define TV_DAC_CNTL_RDACPD                         0x01000000
DECL|macro|TV_DAC_CNTL_GDACPD
mdefine_line|#define TV_DAC_CNTL_GDACPD                         0x02000000
DECL|macro|TV_DAC_CNTL_BDACPD
mdefine_line|#define TV_DAC_CNTL_BDACPD                         0x04000000
multiline_comment|/* DISP_MISC_CNTL constants */
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_GRPH_PP
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_GRPH_PP          (1 &lt;&lt; 0)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_SUBPIC_PP
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_SUBPIC_PP        (1 &lt;&lt; 1)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_OV0_PP
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_OV0_PP           (1 &lt;&lt; 2)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_GRPH_SCLK
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_GRPH_SCLK        (1 &lt;&lt; 4)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_SUBPIC_SCLK
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_SUBPIC_SCLK      (1 &lt;&lt; 5)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_OV0_SCLK
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_OV0_SCLK         (1 &lt;&lt; 6)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_GRPH2_PP
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_GRPH2_PP         (1 &lt;&lt; 12)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_GRPH2_SCLK
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_GRPH2_SCLK       (1 &lt;&lt; 15)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_LVDS
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_LVDS             (1 &lt;&lt; 16)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_TMDS
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_TMDS             (1 &lt;&lt; 17)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_DIG_TMDS
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_DIG_TMDS         (1 &lt;&lt; 18)
DECL|macro|DISP_MISC_CNTL_SOFT_RESET_TV
mdefine_line|#define DISP_MISC_CNTL_SOFT_RESET_TV               (1 &lt;&lt; 19)
multiline_comment|/* DISP_PWR_MAN constants */
DECL|macro|DISP_PWR_MAN_DISP_PWR_MAN_D3_CRTC_EN
mdefine_line|#define DISP_PWR_MAN_DISP_PWR_MAN_D3_CRTC_EN       (1 &lt;&lt; 0)
DECL|macro|DISP_PWR_MAN_DISP2_PWR_MAN_D3_CRTC2_EN
mdefine_line|#define DISP_PWR_MAN_DISP2_PWR_MAN_D3_CRTC2_EN     (1 &lt;&lt; 4)
DECL|macro|DISP_PWR_MAN_DISP_D3_RST
mdefine_line|#define DISP_PWR_MAN_DISP_D3_RST                   (1 &lt;&lt; 16)
DECL|macro|DISP_PWR_MAN_DISP_D3_REG_RST
mdefine_line|#define DISP_PWR_MAN_DISP_D3_REG_RST               (1 &lt;&lt; 17)
DECL|macro|DISP_PWR_MAN_DISP_D3_GRPH_RST
mdefine_line|#define DISP_PWR_MAN_DISP_D3_GRPH_RST              (1 &lt;&lt; 18)
DECL|macro|DISP_PWR_MAN_DISP_D3_SUBPIC_RST
mdefine_line|#define DISP_PWR_MAN_DISP_D3_SUBPIC_RST            (1 &lt;&lt; 19)
DECL|macro|DISP_PWR_MAN_DISP_D3_OV0_RST
mdefine_line|#define DISP_PWR_MAN_DISP_D3_OV0_RST               (1 &lt;&lt; 20)
DECL|macro|DISP_PWR_MAN_DISP_D1D2_GRPH_RST
mdefine_line|#define DISP_PWR_MAN_DISP_D1D2_GRPH_RST            (1 &lt;&lt; 21)
DECL|macro|DISP_PWR_MAN_DISP_D1D2_SUBPIC_RST
mdefine_line|#define DISP_PWR_MAN_DISP_D1D2_SUBPIC_RST          (1 &lt;&lt; 22)
DECL|macro|DISP_PWR_MAN_DISP_D1D2_OV0_RST
mdefine_line|#define DISP_PWR_MAN_DISP_D1D2_OV0_RST             (1 &lt;&lt; 23)
DECL|macro|DISP_PWR_MAN_DIG_TMDS_ENABLE_RST
mdefine_line|#define DISP_PWR_MAN_DIG_TMDS_ENABLE_RST           (1 &lt;&lt; 24)
DECL|macro|DISP_PWR_MAN_TV_ENABLE_RST
mdefine_line|#define DISP_PWR_MAN_TV_ENABLE_RST                 (1 &lt;&lt; 25)
DECL|macro|DISP_PWR_MAN_AUTO_PWRUP_EN
mdefine_line|#define DISP_PWR_MAN_AUTO_PWRUP_EN                 (1 &lt;&lt; 26)
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
DECL|macro|PPLL_SLEEP
mdefine_line|#define&t;PPLL_SLEEP&t;&t;&t;0x00000002
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
DECL|macro|R300_PPLL_REF_DIV_ACC_MASK
mdefine_line|#define R300_PPLL_REF_DIV_ACC_MASK&t;(0x3ff &lt;&lt; 18)
DECL|macro|R300_PPLL_REF_DIV_ACC_SHIFT
mdefine_line|#define R300_PPLL_REF_DIV_ACC_SHIFT&t;18
DECL|macro|GUI_ACTIVE
mdefine_line|#define GUI_ACTIVE&t;&t;&t;0x80000000
DECL|macro|MC_IND_INDEX
mdefine_line|#define MC_IND_INDEX                           0x01F8
DECL|macro|MC_IND_DATA
mdefine_line|#define MC_IND_DATA                            0x01FC
multiline_comment|/* PAD_CTLR_STRENGTH */
DECL|macro|PAD_MANUAL_OVERRIDE
mdefine_line|#define PAD_MANUAL_OVERRIDE&t;&t;0x80000000
singleline_comment|// pllCLK_PIN_CNTL
DECL|macro|CLK_PIN_CNTL__OSC_EN_MASK
mdefine_line|#define CLK_PIN_CNTL__OSC_EN_MASK                          0x00000001L
DECL|macro|CLK_PIN_CNTL__OSC_EN
mdefine_line|#define CLK_PIN_CNTL__OSC_EN                               0x00000001L
DECL|macro|CLK_PIN_CNTL__XTL_LOW_GAIN_MASK
mdefine_line|#define CLK_PIN_CNTL__XTL_LOW_GAIN_MASK                    0x00000004L
DECL|macro|CLK_PIN_CNTL__XTL_LOW_GAIN
mdefine_line|#define CLK_PIN_CNTL__XTL_LOW_GAIN                         0x00000004L
DECL|macro|CLK_PIN_CNTL__DONT_USE_XTALIN_MASK
mdefine_line|#define CLK_PIN_CNTL__DONT_USE_XTALIN_MASK                 0x00000010L
DECL|macro|CLK_PIN_CNTL__DONT_USE_XTALIN
mdefine_line|#define CLK_PIN_CNTL__DONT_USE_XTALIN                      0x00000010L
DECL|macro|CLK_PIN_CNTL__SLOW_CLOCK_SOURCE_MASK
mdefine_line|#define CLK_PIN_CNTL__SLOW_CLOCK_SOURCE_MASK               0x00000020L
DECL|macro|CLK_PIN_CNTL__SLOW_CLOCK_SOURCE
mdefine_line|#define CLK_PIN_CNTL__SLOW_CLOCK_SOURCE                    0x00000020L
DECL|macro|CLK_PIN_CNTL__CG_CLK_TO_OUTPIN_MASK
mdefine_line|#define CLK_PIN_CNTL__CG_CLK_TO_OUTPIN_MASK                0x00000800L
DECL|macro|CLK_PIN_CNTL__CG_CLK_TO_OUTPIN
mdefine_line|#define CLK_PIN_CNTL__CG_CLK_TO_OUTPIN                     0x00000800L
DECL|macro|CLK_PIN_CNTL__CG_COUNT_UP_TO_OUTPIN_MASK
mdefine_line|#define CLK_PIN_CNTL__CG_COUNT_UP_TO_OUTPIN_MASK           0x00001000L
DECL|macro|CLK_PIN_CNTL__CG_COUNT_UP_TO_OUTPIN
mdefine_line|#define CLK_PIN_CNTL__CG_COUNT_UP_TO_OUTPIN                0x00001000L
DECL|macro|CLK_PIN_CNTL__ACCESS_REGS_IN_SUSPEND_MASK
mdefine_line|#define CLK_PIN_CNTL__ACCESS_REGS_IN_SUSPEND_MASK          0x00002000L
DECL|macro|CLK_PIN_CNTL__ACCESS_REGS_IN_SUSPEND
mdefine_line|#define CLK_PIN_CNTL__ACCESS_REGS_IN_SUSPEND               0x00002000L
DECL|macro|CLK_PIN_CNTL__CG_SPARE_MASK
mdefine_line|#define CLK_PIN_CNTL__CG_SPARE_MASK                        0x00004000L
DECL|macro|CLK_PIN_CNTL__CG_SPARE
mdefine_line|#define CLK_PIN_CNTL__CG_SPARE                             0x00004000L
DECL|macro|CLK_PIN_CNTL__SCLK_DYN_START_CNTL_MASK
mdefine_line|#define CLK_PIN_CNTL__SCLK_DYN_START_CNTL_MASK             0x00008000L
DECL|macro|CLK_PIN_CNTL__SCLK_DYN_START_CNTL
mdefine_line|#define CLK_PIN_CNTL__SCLK_DYN_START_CNTL                  0x00008000L
DECL|macro|CLK_PIN_CNTL__CP_CLK_RUNNING_MASK
mdefine_line|#define CLK_PIN_CNTL__CP_CLK_RUNNING_MASK                  0x00010000L
DECL|macro|CLK_PIN_CNTL__CP_CLK_RUNNING
mdefine_line|#define CLK_PIN_CNTL__CP_CLK_RUNNING                       0x00010000L
DECL|macro|CLK_PIN_CNTL__CG_SPARE_RD_MASK
mdefine_line|#define CLK_PIN_CNTL__CG_SPARE_RD_MASK                     0x00060000L
DECL|macro|CLK_PIN_CNTL__XTALIN_ALWAYS_ONb_MASK
mdefine_line|#define CLK_PIN_CNTL__XTALIN_ALWAYS_ONb_MASK               0x00080000L
DECL|macro|CLK_PIN_CNTL__XTALIN_ALWAYS_ONb
mdefine_line|#define CLK_PIN_CNTL__XTALIN_ALWAYS_ONb                    0x00080000L
DECL|macro|CLK_PIN_CNTL__PWRSEQ_DELAY_MASK
mdefine_line|#define CLK_PIN_CNTL__PWRSEQ_DELAY_MASK                    0xff000000L
singleline_comment|// pllCLK_PWRMGT_CNTL
DECL|macro|CLK_PWRMGT_CNTL__MPLL_PWRMGT_OFF__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__MPLL_PWRMGT_OFF__SHIFT         0x00000000
DECL|macro|CLK_PWRMGT_CNTL__SPLL_PWRMGT_OFF__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__SPLL_PWRMGT_OFF__SHIFT         0x00000001
DECL|macro|CLK_PWRMGT_CNTL__PPLL_PWRMGT_OFF__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__PPLL_PWRMGT_OFF__SHIFT         0x00000002
DECL|macro|CLK_PWRMGT_CNTL__P2PLL_PWRMGT_OFF__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__P2PLL_PWRMGT_OFF__SHIFT        0x00000003
DECL|macro|CLK_PWRMGT_CNTL__MCLK_TURNOFF__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__MCLK_TURNOFF__SHIFT            0x00000004
DECL|macro|CLK_PWRMGT_CNTL__SCLK_TURNOFF__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__SCLK_TURNOFF__SHIFT            0x00000005
DECL|macro|CLK_PWRMGT_CNTL__PCLK_TURNOFF__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__PCLK_TURNOFF__SHIFT            0x00000006
DECL|macro|CLK_PWRMGT_CNTL__P2CLK_TURNOFF__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__P2CLK_TURNOFF__SHIFT           0x00000007
DECL|macro|CLK_PWRMGT_CNTL__MC_CH_MODE__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__MC_CH_MODE__SHIFT              0x00000008
DECL|macro|CLK_PWRMGT_CNTL__TEST_MODE__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__TEST_MODE__SHIFT               0x00000009
DECL|macro|CLK_PWRMGT_CNTL__GLOBAL_PMAN_EN__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__GLOBAL_PMAN_EN__SHIFT          0x0000000a
DECL|macro|CLK_PWRMGT_CNTL__ENGINE_DYNCLK_MODE__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__ENGINE_DYNCLK_MODE__SHIFT      0x0000000c
DECL|macro|CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT__SHIFT         0x0000000d
DECL|macro|CLK_PWRMGT_CNTL__DISP_DYN_STOP_LAT__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__DISP_DYN_STOP_LAT__SHIFT       0x0000000f
DECL|macro|CLK_PWRMGT_CNTL__MC_BUSY__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__MC_BUSY__SHIFT                 0x00000010
DECL|macro|CLK_PWRMGT_CNTL__MC_INT_CNTL__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__MC_INT_CNTL__SHIFT             0x00000011
DECL|macro|CLK_PWRMGT_CNTL__MC_SWITCH__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__MC_SWITCH__SHIFT               0x00000012
DECL|macro|CLK_PWRMGT_CNTL__DLL_READY__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__DLL_READY__SHIFT               0x00000013
DECL|macro|CLK_PWRMGT_CNTL__DISP_PM__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__DISP_PM__SHIFT                 0x00000014
DECL|macro|CLK_PWRMGT_CNTL__DYN_STOP_MODE__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__DYN_STOP_MODE__SHIFT           0x00000015
DECL|macro|CLK_PWRMGT_CNTL__CG_NO1_DEBUG__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__CG_NO1_DEBUG__SHIFT            0x00000018
DECL|macro|CLK_PWRMGT_CNTL__TVPLL_PWRMGT_OFF__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__TVPLL_PWRMGT_OFF__SHIFT        0x0000001e
DECL|macro|CLK_PWRMGT_CNTL__TVCLK_TURNOFF__SHIFT
mdefine_line|#define&t;CLK_PWRMGT_CNTL__TVCLK_TURNOFF__SHIFT           0x0000001f
singleline_comment|// pllP2PLL_CNTL
DECL|macro|P2PLL_CNTL__P2PLL_RESET_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_RESET_MASK                       0x00000001L
DECL|macro|P2PLL_CNTL__P2PLL_RESET
mdefine_line|#define P2PLL_CNTL__P2PLL_RESET                            0x00000001L
DECL|macro|P2PLL_CNTL__P2PLL_SLEEP_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_SLEEP_MASK                       0x00000002L
DECL|macro|P2PLL_CNTL__P2PLL_SLEEP
mdefine_line|#define P2PLL_CNTL__P2PLL_SLEEP                            0x00000002L
DECL|macro|P2PLL_CNTL__P2PLL_TST_EN_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_TST_EN_MASK                      0x00000004L
DECL|macro|P2PLL_CNTL__P2PLL_TST_EN
mdefine_line|#define P2PLL_CNTL__P2PLL_TST_EN                           0x00000004L
DECL|macro|P2PLL_CNTL__P2PLL_REFCLK_SEL_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_REFCLK_SEL_MASK                  0x00000010L
DECL|macro|P2PLL_CNTL__P2PLL_REFCLK_SEL
mdefine_line|#define P2PLL_CNTL__P2PLL_REFCLK_SEL                       0x00000010L
DECL|macro|P2PLL_CNTL__P2PLL_FBCLK_SEL_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_FBCLK_SEL_MASK                   0x00000020L
DECL|macro|P2PLL_CNTL__P2PLL_FBCLK_SEL
mdefine_line|#define P2PLL_CNTL__P2PLL_FBCLK_SEL                        0x00000020L
DECL|macro|P2PLL_CNTL__P2PLL_TCPOFF_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_TCPOFF_MASK                      0x00000040L
DECL|macro|P2PLL_CNTL__P2PLL_TCPOFF
mdefine_line|#define P2PLL_CNTL__P2PLL_TCPOFF                           0x00000040L
DECL|macro|P2PLL_CNTL__P2PLL_TVCOMAX_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_TVCOMAX_MASK                     0x00000080L
DECL|macro|P2PLL_CNTL__P2PLL_TVCOMAX
mdefine_line|#define P2PLL_CNTL__P2PLL_TVCOMAX                          0x00000080L
DECL|macro|P2PLL_CNTL__P2PLL_PCP_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_PCP_MASK                         0x00000700L
DECL|macro|P2PLL_CNTL__P2PLL_PVG_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_PVG_MASK                         0x00003800L
DECL|macro|P2PLL_CNTL__P2PLL_PDC_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_PDC_MASK                         0x0000c000L
DECL|macro|P2PLL_CNTL__P2PLL_ATOMIC_UPDATE_EN_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_ATOMIC_UPDATE_EN_MASK            0x00010000L
DECL|macro|P2PLL_CNTL__P2PLL_ATOMIC_UPDATE_EN
mdefine_line|#define P2PLL_CNTL__P2PLL_ATOMIC_UPDATE_EN                 0x00010000L
DECL|macro|P2PLL_CNTL__P2PLL_ATOMIC_UPDATE_SYNC_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_ATOMIC_UPDATE_SYNC_MASK          0x00040000L
DECL|macro|P2PLL_CNTL__P2PLL_ATOMIC_UPDATE_SYNC
mdefine_line|#define P2PLL_CNTL__P2PLL_ATOMIC_UPDATE_SYNC               0x00040000L
DECL|macro|P2PLL_CNTL__P2PLL_DISABLE_AUTO_RESET_MASK
mdefine_line|#define P2PLL_CNTL__P2PLL_DISABLE_AUTO_RESET_MASK          0x00080000L
DECL|macro|P2PLL_CNTL__P2PLL_DISABLE_AUTO_RESET
mdefine_line|#define P2PLL_CNTL__P2PLL_DISABLE_AUTO_RESET               0x00080000L
singleline_comment|// pllPIXCLKS_CNTL
DECL|macro|PIXCLKS_CNTL__PIX2CLK_SRC_SEL__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIX2CLK_SRC_SEL__SHIFT               0x00000000
DECL|macro|PIXCLKS_CNTL__PIX2CLK_INVERT__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIX2CLK_INVERT__SHIFT                0x00000004
DECL|macro|PIXCLKS_CNTL__PIX2CLK_SRC_INVERT__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIX2CLK_SRC_INVERT__SHIFT            0x00000005
DECL|macro|PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb__SHIFT            0x00000006
DECL|macro|PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb__SHIFT        0x00000007
DECL|macro|PIXCLKS_CNTL__PIXCLK_TV_SRC_SEL__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIXCLK_TV_SRC_SEL__SHIFT             0x00000008
DECL|macro|PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb__SHIFT       0x0000000b
DECL|macro|PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb__SHIFT          0x0000000c
DECL|macro|PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb__SHIFT    0x0000000d
DECL|macro|PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb__SHIFT        0x0000000e
DECL|macro|PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb__SHIFT
mdefine_line|#define&t;PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb__SHIFT        0x0000000f
singleline_comment|// pllPIXCLKS_CNTL
DECL|macro|PIXCLKS_CNTL__PIX2CLK_SRC_SEL_MASK
mdefine_line|#define PIXCLKS_CNTL__PIX2CLK_SRC_SEL_MASK                 0x00000003L
DECL|macro|PIXCLKS_CNTL__PIX2CLK_INVERT
mdefine_line|#define PIXCLKS_CNTL__PIX2CLK_INVERT                       0x00000010L
DECL|macro|PIXCLKS_CNTL__PIX2CLK_SRC_INVERT
mdefine_line|#define PIXCLKS_CNTL__PIX2CLK_SRC_INVERT                   0x00000020L
DECL|macro|PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb                   0x00000040L
DECL|macro|PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb               0x00000080L
DECL|macro|PIXCLKS_CNTL__PIXCLK_TV_SRC_SEL
mdefine_line|#define PIXCLKS_CNTL__PIXCLK_TV_SRC_SEL                    0x00000100L
DECL|macro|PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb              0x00000800L
DECL|macro|PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb                 0x00001000L
DECL|macro|PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb           0x00002000L
DECL|macro|PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb               0x00004000L
DECL|macro|PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb               0x00008000L
DECL|macro|PIXCLKS_CNTL__DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb      (1 &lt;&lt; 9)
DECL|macro|PIXCLKS_CNTL__R300_DVOCLK_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__R300_DVOCLK_ALWAYS_ONb               (1 &lt;&lt; 10)
DECL|macro|PIXCLKS_CNTL__R300_PIXCLK_DVO_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__R300_PIXCLK_DVO_ALWAYS_ONb           (1 &lt;&lt; 13)
DECL|macro|PIXCLKS_CNTL__R300_PIXCLK_TRANS_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__R300_PIXCLK_TRANS_ALWAYS_ONb         (1 &lt;&lt; 16)
DECL|macro|PIXCLKS_CNTL__R300_PIXCLK_TVO_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__R300_PIXCLK_TVO_ALWAYS_ONb           (1 &lt;&lt; 17)
DECL|macro|PIXCLKS_CNTL__R300_P2G2CLK_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__R300_P2G2CLK_ALWAYS_ONb              (1 &lt;&lt; 18)
DECL|macro|PIXCLKS_CNTL__R300_P2G2CLK_DAC_ALWAYS_ONb
mdefine_line|#define PIXCLKS_CNTL__R300_P2G2CLK_DAC_ALWAYS_ONb          (1 &lt;&lt; 19)
DECL|macro|PIXCLKS_CNTL__R300_DISP_DAC_PIXCLK_DAC2_BLANK_OFF
mdefine_line|#define PIXCLKS_CNTL__R300_DISP_DAC_PIXCLK_DAC2_BLANK_OFF  (1 &lt;&lt; 23)
singleline_comment|// pllP2PLL_DIV_0
DECL|macro|P2PLL_DIV_0__P2PLL_FB_DIV_MASK
mdefine_line|#define P2PLL_DIV_0__P2PLL_FB_DIV_MASK                     0x000007ffL
DECL|macro|P2PLL_DIV_0__P2PLL_ATOMIC_UPDATE_W_MASK
mdefine_line|#define P2PLL_DIV_0__P2PLL_ATOMIC_UPDATE_W_MASK            0x00008000L
DECL|macro|P2PLL_DIV_0__P2PLL_ATOMIC_UPDATE_W
mdefine_line|#define P2PLL_DIV_0__P2PLL_ATOMIC_UPDATE_W                 0x00008000L
DECL|macro|P2PLL_DIV_0__P2PLL_ATOMIC_UPDATE_R_MASK
mdefine_line|#define P2PLL_DIV_0__P2PLL_ATOMIC_UPDATE_R_MASK            0x00008000L
DECL|macro|P2PLL_DIV_0__P2PLL_ATOMIC_UPDATE_R
mdefine_line|#define P2PLL_DIV_0__P2PLL_ATOMIC_UPDATE_R                 0x00008000L
DECL|macro|P2PLL_DIV_0__P2PLL_POST_DIV_MASK
mdefine_line|#define P2PLL_DIV_0__P2PLL_POST_DIV_MASK                   0x00070000L
singleline_comment|// pllSCLK_CNTL
DECL|macro|SCLK_CNTL__SCLK_SRC_SEL_MASK
mdefine_line|#define SCLK_CNTL__SCLK_SRC_SEL_MASK                    0x00000007L
DECL|macro|SCLK_CNTL__CP_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__CP_MAX_DYN_STOP_LAT                  0x00000008L
DECL|macro|SCLK_CNTL__HDP_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__HDP_MAX_DYN_STOP_LAT                 0x00000010L
DECL|macro|SCLK_CNTL__TV_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__TV_MAX_DYN_STOP_LAT                  0x00000020L
DECL|macro|SCLK_CNTL__E2_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__E2_MAX_DYN_STOP_LAT                  0x00000040L
DECL|macro|SCLK_CNTL__SE_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__SE_MAX_DYN_STOP_LAT                  0x00000080L
DECL|macro|SCLK_CNTL__IDCT_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__IDCT_MAX_DYN_STOP_LAT                0x00000100L
DECL|macro|SCLK_CNTL__VIP_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__VIP_MAX_DYN_STOP_LAT                 0x00000200L
DECL|macro|SCLK_CNTL__RE_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__RE_MAX_DYN_STOP_LAT                  0x00000400L
DECL|macro|SCLK_CNTL__PB_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__PB_MAX_DYN_STOP_LAT                  0x00000800L
DECL|macro|SCLK_CNTL__TAM_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__TAM_MAX_DYN_STOP_LAT                 0x00001000L
DECL|macro|SCLK_CNTL__TDM_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__TDM_MAX_DYN_STOP_LAT                 0x00002000L
DECL|macro|SCLK_CNTL__RB_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL__RB_MAX_DYN_STOP_LAT                  0x00004000L
DECL|macro|SCLK_CNTL__DYN_STOP_LAT_MASK
mdefine_line|#define SCLK_CNTL__DYN_STOP_LAT_MASK                     0x00007ff8
DECL|macro|SCLK_CNTL__FORCE_DISP2
mdefine_line|#define SCLK_CNTL__FORCE_DISP2                          0x00008000L
DECL|macro|SCLK_CNTL__FORCE_CP
mdefine_line|#define SCLK_CNTL__FORCE_CP                             0x00010000L
DECL|macro|SCLK_CNTL__FORCE_HDP
mdefine_line|#define SCLK_CNTL__FORCE_HDP                            0x00020000L
DECL|macro|SCLK_CNTL__FORCE_DISP1
mdefine_line|#define SCLK_CNTL__FORCE_DISP1                          0x00040000L
DECL|macro|SCLK_CNTL__FORCE_TOP
mdefine_line|#define SCLK_CNTL__FORCE_TOP                            0x00080000L
DECL|macro|SCLK_CNTL__FORCE_E2
mdefine_line|#define SCLK_CNTL__FORCE_E2                             0x00100000L
DECL|macro|SCLK_CNTL__FORCE_SE
mdefine_line|#define SCLK_CNTL__FORCE_SE                             0x00200000L
DECL|macro|SCLK_CNTL__FORCE_IDCT
mdefine_line|#define SCLK_CNTL__FORCE_IDCT                           0x00400000L
DECL|macro|SCLK_CNTL__FORCE_VIP
mdefine_line|#define SCLK_CNTL__FORCE_VIP                            0x00800000L
DECL|macro|SCLK_CNTL__FORCE_RE
mdefine_line|#define SCLK_CNTL__FORCE_RE                             0x01000000L
DECL|macro|SCLK_CNTL__FORCE_PB
mdefine_line|#define SCLK_CNTL__FORCE_PB                             0x02000000L
DECL|macro|SCLK_CNTL__FORCE_TAM
mdefine_line|#define SCLK_CNTL__FORCE_TAM                            0x04000000L
DECL|macro|SCLK_CNTL__FORCE_TDM
mdefine_line|#define SCLK_CNTL__FORCE_TDM                            0x08000000L
DECL|macro|SCLK_CNTL__FORCE_RB
mdefine_line|#define SCLK_CNTL__FORCE_RB                             0x10000000L
DECL|macro|SCLK_CNTL__FORCE_TV_SCLK
mdefine_line|#define SCLK_CNTL__FORCE_TV_SCLK                        0x20000000L
DECL|macro|SCLK_CNTL__FORCE_SUBPIC
mdefine_line|#define SCLK_CNTL__FORCE_SUBPIC                         0x40000000L
DECL|macro|SCLK_CNTL__FORCE_OV0
mdefine_line|#define SCLK_CNTL__FORCE_OV0                            0x80000000L
DECL|macro|SCLK_CNTL__R300_FORCE_VAP
mdefine_line|#define SCLK_CNTL__R300_FORCE_VAP                       (1&lt;&lt;21)
DECL|macro|SCLK_CNTL__R300_FORCE_SR
mdefine_line|#define SCLK_CNTL__R300_FORCE_SR                        (1&lt;&lt;25)
DECL|macro|SCLK_CNTL__R300_FORCE_PX
mdefine_line|#define SCLK_CNTL__R300_FORCE_PX                        (1&lt;&lt;26)
DECL|macro|SCLK_CNTL__R300_FORCE_TX
mdefine_line|#define SCLK_CNTL__R300_FORCE_TX                        (1&lt;&lt;27)
DECL|macro|SCLK_CNTL__R300_FORCE_US
mdefine_line|#define SCLK_CNTL__R300_FORCE_US                        (1&lt;&lt;28)
DECL|macro|SCLK_CNTL__R300_FORCE_SU
mdefine_line|#define SCLK_CNTL__R300_FORCE_SU                        (1&lt;&lt;30)
DECL|macro|SCLK_CNTL__FORCEON_MASK
mdefine_line|#define SCLK_CNTL__FORCEON_MASK                         0xffff8000L
singleline_comment|// pllSCLK_CNTL2
DECL|macro|SCLK_CNTL2__R300_TCL_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL2__R300_TCL_MAX_DYN_STOP_LAT           (1&lt;&lt;10)
DECL|macro|SCLK_CNTL2__R300_GA_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL2__R300_GA_MAX_DYN_STOP_LAT            (1&lt;&lt;11)
DECL|macro|SCLK_CNTL2__R300_CBA_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_CNTL2__R300_CBA_MAX_DYN_STOP_LAT           (1&lt;&lt;12)
DECL|macro|SCLK_CNTL2__R300_FORCE_TCL
mdefine_line|#define SCLK_CNTL2__R300_FORCE_TCL                      (1&lt;&lt;13)
DECL|macro|SCLK_CNTL2__R300_FORCE_CBA
mdefine_line|#define SCLK_CNTL2__R300_FORCE_CBA                      (1&lt;&lt;14)
DECL|macro|SCLK_CNTL2__R300_FORCE_GA
mdefine_line|#define SCLK_CNTL2__R300_FORCE_GA                       (1&lt;&lt;15)
singleline_comment|// SCLK_MORE_CNTL
DECL|macro|SCLK_MORE_CNTL__DISPREGS_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_MORE_CNTL__DISPREGS_MAX_DYN_STOP_LAT          0x00000001L
DECL|macro|SCLK_MORE_CNTL__MC_GUI_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_MORE_CNTL__MC_GUI_MAX_DYN_STOP_LAT            0x00000002L
DECL|macro|SCLK_MORE_CNTL__MC_HOST_MAX_DYN_STOP_LAT
mdefine_line|#define SCLK_MORE_CNTL__MC_HOST_MAX_DYN_STOP_LAT           0x00000004L
DECL|macro|SCLK_MORE_CNTL__FORCE_DISPREGS
mdefine_line|#define SCLK_MORE_CNTL__FORCE_DISPREGS                     0x00000100L
DECL|macro|SCLK_MORE_CNTL__FORCE_MC_GUI
mdefine_line|#define SCLK_MORE_CNTL__FORCE_MC_GUI                       0x00000200L
DECL|macro|SCLK_MORE_CNTL__FORCE_MC_HOST
mdefine_line|#define SCLK_MORE_CNTL__FORCE_MC_HOST                      0x00000400L
DECL|macro|SCLK_MORE_CNTL__STOP_SCLK_EN
mdefine_line|#define SCLK_MORE_CNTL__STOP_SCLK_EN                       0x00001000L
DECL|macro|SCLK_MORE_CNTL__STOP_SCLK_A
mdefine_line|#define SCLK_MORE_CNTL__STOP_SCLK_A                        0x00002000L
DECL|macro|SCLK_MORE_CNTL__STOP_SCLK_B
mdefine_line|#define SCLK_MORE_CNTL__STOP_SCLK_B                        0x00004000L
DECL|macro|SCLK_MORE_CNTL__STOP_SCLK_C
mdefine_line|#define SCLK_MORE_CNTL__STOP_SCLK_C                        0x00008000L
DECL|macro|SCLK_MORE_CNTL__HALF_SPEED_SCLK
mdefine_line|#define SCLK_MORE_CNTL__HALF_SPEED_SCLK                    0x00010000L
DECL|macro|SCLK_MORE_CNTL__IO_CG_VOLTAGE_DROP
mdefine_line|#define SCLK_MORE_CNTL__IO_CG_VOLTAGE_DROP                 0x00020000L
DECL|macro|SCLK_MORE_CNTL__TVFB_SOFT_RESET
mdefine_line|#define SCLK_MORE_CNTL__TVFB_SOFT_RESET                    0x00040000L
DECL|macro|SCLK_MORE_CNTL__VOLTAGE_DROP_SYNC
mdefine_line|#define SCLK_MORE_CNTL__VOLTAGE_DROP_SYNC                  0x00080000L
DECL|macro|SCLK_MORE_CNTL__IDLE_DELAY_HALF_SCLK
mdefine_line|#define SCLK_MORE_CNTL__IDLE_DELAY_HALF_SCLK               0x00400000L
DECL|macro|SCLK_MORE_CNTL__AGP_BUSY_HALF_SCLK
mdefine_line|#define SCLK_MORE_CNTL__AGP_BUSY_HALF_SCLK                 0x00800000L
DECL|macro|SCLK_MORE_CNTL__CG_SPARE_RD_C_MASK
mdefine_line|#define SCLK_MORE_CNTL__CG_SPARE_RD_C_MASK                 0xff000000L
DECL|macro|SCLK_MORE_CNTL__FORCEON
mdefine_line|#define SCLK_MORE_CNTL__FORCEON                            0x00000700L
singleline_comment|// MCLK_CNTL
DECL|macro|MCLK_CNTL__MCLKA_SRC_SEL_MASK
mdefine_line|#define MCLK_CNTL__MCLKA_SRC_SEL_MASK                   0x00000007L
DECL|macro|MCLK_CNTL__YCLKA_SRC_SEL_MASK
mdefine_line|#define MCLK_CNTL__YCLKA_SRC_SEL_MASK                   0x00000070L
DECL|macro|MCLK_CNTL__MCLKB_SRC_SEL_MASK
mdefine_line|#define MCLK_CNTL__MCLKB_SRC_SEL_MASK                   0x00000700L
DECL|macro|MCLK_CNTL__YCLKB_SRC_SEL_MASK
mdefine_line|#define MCLK_CNTL__YCLKB_SRC_SEL_MASK                   0x00007000L
DECL|macro|MCLK_CNTL__FORCE_MCLKA_MASK
mdefine_line|#define MCLK_CNTL__FORCE_MCLKA_MASK                     0x00010000L
DECL|macro|MCLK_CNTL__FORCE_MCLKA
mdefine_line|#define MCLK_CNTL__FORCE_MCLKA                          0x00010000L
DECL|macro|MCLK_CNTL__FORCE_MCLKB_MASK
mdefine_line|#define MCLK_CNTL__FORCE_MCLKB_MASK                     0x00020000L
DECL|macro|MCLK_CNTL__FORCE_MCLKB
mdefine_line|#define MCLK_CNTL__FORCE_MCLKB                          0x00020000L
DECL|macro|MCLK_CNTL__FORCE_YCLKA_MASK
mdefine_line|#define MCLK_CNTL__FORCE_YCLKA_MASK                     0x00040000L
DECL|macro|MCLK_CNTL__FORCE_YCLKA
mdefine_line|#define MCLK_CNTL__FORCE_YCLKA                          0x00040000L
DECL|macro|MCLK_CNTL__FORCE_YCLKB_MASK
mdefine_line|#define MCLK_CNTL__FORCE_YCLKB_MASK                     0x00080000L
DECL|macro|MCLK_CNTL__FORCE_YCLKB
mdefine_line|#define MCLK_CNTL__FORCE_YCLKB                          0x00080000L
DECL|macro|MCLK_CNTL__FORCE_MC_MASK
mdefine_line|#define MCLK_CNTL__FORCE_MC_MASK                        0x00100000L
DECL|macro|MCLK_CNTL__FORCE_MC
mdefine_line|#define MCLK_CNTL__FORCE_MC                             0x00100000L
DECL|macro|MCLK_CNTL__FORCE_AIC_MASK
mdefine_line|#define MCLK_CNTL__FORCE_AIC_MASK                       0x00200000L
DECL|macro|MCLK_CNTL__FORCE_AIC
mdefine_line|#define MCLK_CNTL__FORCE_AIC                            0x00200000L
DECL|macro|MCLK_CNTL__MRDCKA0_SOUTSEL_MASK
mdefine_line|#define MCLK_CNTL__MRDCKA0_SOUTSEL_MASK                 0x03000000L
DECL|macro|MCLK_CNTL__MRDCKA1_SOUTSEL_MASK
mdefine_line|#define MCLK_CNTL__MRDCKA1_SOUTSEL_MASK                 0x0c000000L
DECL|macro|MCLK_CNTL__MRDCKB0_SOUTSEL_MASK
mdefine_line|#define MCLK_CNTL__MRDCKB0_SOUTSEL_MASK                 0x30000000L
DECL|macro|MCLK_CNTL__MRDCKB1_SOUTSEL_MASK
mdefine_line|#define MCLK_CNTL__MRDCKB1_SOUTSEL_MASK                 0xc0000000L
DECL|macro|MCLK_CNTL__R300_DISABLE_MC_MCLKA
mdefine_line|#define MCLK_CNTL__R300_DISABLE_MC_MCLKA                (1 &lt;&lt; 21)
DECL|macro|MCLK_CNTL__R300_DISABLE_MC_MCLKB
mdefine_line|#define MCLK_CNTL__R300_DISABLE_MC_MCLKB                (1 &lt;&lt; 21)
singleline_comment|// MCLK_MISC
DECL|macro|MCLK_MISC__SCLK_SOURCED_FROM_MPLL_SEL_MASK
mdefine_line|#define MCLK_MISC__SCLK_SOURCED_FROM_MPLL_SEL_MASK         0x00000003L
DECL|macro|MCLK_MISC__MCLK_FROM_SPLL_DIV_SEL_MASK
mdefine_line|#define MCLK_MISC__MCLK_FROM_SPLL_DIV_SEL_MASK             0x00000004L
DECL|macro|MCLK_MISC__MCLK_FROM_SPLL_DIV_SEL
mdefine_line|#define MCLK_MISC__MCLK_FROM_SPLL_DIV_SEL                  0x00000004L
DECL|macro|MCLK_MISC__ENABLE_SCLK_FROM_MPLL_MASK
mdefine_line|#define MCLK_MISC__ENABLE_SCLK_FROM_MPLL_MASK              0x00000008L
DECL|macro|MCLK_MISC__ENABLE_SCLK_FROM_MPLL
mdefine_line|#define MCLK_MISC__ENABLE_SCLK_FROM_MPLL                   0x00000008L
DECL|macro|MCLK_MISC__MPLL_MODEA_MODEC_HW_SEL_EN_MASK
mdefine_line|#define MCLK_MISC__MPLL_MODEA_MODEC_HW_SEL_EN_MASK         0x00000010L
DECL|macro|MCLK_MISC__MPLL_MODEA_MODEC_HW_SEL_EN
mdefine_line|#define MCLK_MISC__MPLL_MODEA_MODEC_HW_SEL_EN              0x00000010L
DECL|macro|MCLK_MISC__DLL_READY_LAT_MASK
mdefine_line|#define MCLK_MISC__DLL_READY_LAT_MASK                      0x00000100L
DECL|macro|MCLK_MISC__DLL_READY_LAT
mdefine_line|#define MCLK_MISC__DLL_READY_LAT                           0x00000100L
DECL|macro|MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT_MASK
mdefine_line|#define MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT_MASK           0x00001000L
DECL|macro|MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT
mdefine_line|#define MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT                0x00001000L
DECL|macro|MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT_MASK
mdefine_line|#define MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT_MASK           0x00002000L
DECL|macro|MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT
mdefine_line|#define MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT                0x00002000L
DECL|macro|MCLK_MISC__MC_MCLK_DYN_ENABLE_MASK
mdefine_line|#define MCLK_MISC__MC_MCLK_DYN_ENABLE_MASK                 0x00004000L
DECL|macro|MCLK_MISC__MC_MCLK_DYN_ENABLE
mdefine_line|#define MCLK_MISC__MC_MCLK_DYN_ENABLE                      0x00004000L
DECL|macro|MCLK_MISC__IO_MCLK_DYN_ENABLE_MASK
mdefine_line|#define MCLK_MISC__IO_MCLK_DYN_ENABLE_MASK                 0x00008000L
DECL|macro|MCLK_MISC__IO_MCLK_DYN_ENABLE
mdefine_line|#define MCLK_MISC__IO_MCLK_DYN_ENABLE                      0x00008000L
DECL|macro|MCLK_MISC__CGM_CLK_TO_OUTPIN_MASK
mdefine_line|#define MCLK_MISC__CGM_CLK_TO_OUTPIN_MASK                  0x00010000L
DECL|macro|MCLK_MISC__CGM_CLK_TO_OUTPIN
mdefine_line|#define MCLK_MISC__CGM_CLK_TO_OUTPIN                       0x00010000L
DECL|macro|MCLK_MISC__CLK_OR_COUNT_SEL_MASK
mdefine_line|#define MCLK_MISC__CLK_OR_COUNT_SEL_MASK                   0x00020000L
DECL|macro|MCLK_MISC__CLK_OR_COUNT_SEL
mdefine_line|#define MCLK_MISC__CLK_OR_COUNT_SEL                        0x00020000L
DECL|macro|MCLK_MISC__EN_MCLK_TRISTATE_IN_SUSPEND_MASK
mdefine_line|#define MCLK_MISC__EN_MCLK_TRISTATE_IN_SUSPEND_MASK        0x00040000L
DECL|macro|MCLK_MISC__EN_MCLK_TRISTATE_IN_SUSPEND
mdefine_line|#define MCLK_MISC__EN_MCLK_TRISTATE_IN_SUSPEND             0x00040000L
DECL|macro|MCLK_MISC__CGM_SPARE_RD_MASK
mdefine_line|#define MCLK_MISC__CGM_SPARE_RD_MASK                       0x00300000L
DECL|macro|MCLK_MISC__CGM_SPARE_A_RD_MASK
mdefine_line|#define MCLK_MISC__CGM_SPARE_A_RD_MASK                     0x00c00000L
DECL|macro|MCLK_MISC__TCLK_TO_YCLKB_EN_MASK
mdefine_line|#define MCLK_MISC__TCLK_TO_YCLKB_EN_MASK                   0x01000000L
DECL|macro|MCLK_MISC__TCLK_TO_YCLKB_EN
mdefine_line|#define MCLK_MISC__TCLK_TO_YCLKB_EN                        0x01000000L
DECL|macro|MCLK_MISC__CGM_SPARE_A_MASK
mdefine_line|#define MCLK_MISC__CGM_SPARE_A_MASK                        0x0e000000L
singleline_comment|// VCLK_ECP_CNTL
DECL|macro|VCLK_ECP_CNTL__VCLK_SRC_SEL_MASK
mdefine_line|#define VCLK_ECP_CNTL__VCLK_SRC_SEL_MASK                   0x00000003L
DECL|macro|VCLK_ECP_CNTL__VCLK_INVERT
mdefine_line|#define VCLK_ECP_CNTL__VCLK_INVERT                         0x00000010L
DECL|macro|VCLK_ECP_CNTL__PIXCLK_SRC_INVERT
mdefine_line|#define VCLK_ECP_CNTL__PIXCLK_SRC_INVERT                   0x00000020L
DECL|macro|VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb
mdefine_line|#define VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb                   0x00000040L
DECL|macro|VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb
mdefine_line|#define VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb               0x00000080L
DECL|macro|VCLK_ECP_CNTL__ECP_DIV_MASK
mdefine_line|#define VCLK_ECP_CNTL__ECP_DIV_MASK                        0x00000300L
DECL|macro|VCLK_ECP_CNTL__ECP_FORCE_ON
mdefine_line|#define VCLK_ECP_CNTL__ECP_FORCE_ON                        0x00040000L
DECL|macro|VCLK_ECP_CNTL__SUBCLK_FORCE_ON
mdefine_line|#define VCLK_ECP_CNTL__SUBCLK_FORCE_ON                     0x00080000L
DECL|macro|VCLK_ECP_CNTL__R300_DISP_DAC_PIXCLK_DAC_BLANK_OFF
mdefine_line|#define VCLK_ECP_CNTL__R300_DISP_DAC_PIXCLK_DAC_BLANK_OFF  (1&lt;&lt;23)
singleline_comment|// PLL_PWRMGT_CNTL
DECL|macro|PLL_PWRMGT_CNTL__MPLL_TURNOFF_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__MPLL_TURNOFF_MASK                 0x00000001L
DECL|macro|PLL_PWRMGT_CNTL__MPLL_TURNOFF
mdefine_line|#define PLL_PWRMGT_CNTL__MPLL_TURNOFF                      0x00000001L
DECL|macro|PLL_PWRMGT_CNTL__SPLL_TURNOFF_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__SPLL_TURNOFF_MASK                 0x00000002L
DECL|macro|PLL_PWRMGT_CNTL__SPLL_TURNOFF
mdefine_line|#define PLL_PWRMGT_CNTL__SPLL_TURNOFF                      0x00000002L
DECL|macro|PLL_PWRMGT_CNTL__PPLL_TURNOFF_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__PPLL_TURNOFF_MASK                 0x00000004L
DECL|macro|PLL_PWRMGT_CNTL__PPLL_TURNOFF
mdefine_line|#define PLL_PWRMGT_CNTL__PPLL_TURNOFF                      0x00000004L
DECL|macro|PLL_PWRMGT_CNTL__P2PLL_TURNOFF_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__P2PLL_TURNOFF_MASK                0x00000008L
DECL|macro|PLL_PWRMGT_CNTL__P2PLL_TURNOFF
mdefine_line|#define PLL_PWRMGT_CNTL__P2PLL_TURNOFF                     0x00000008L
DECL|macro|PLL_PWRMGT_CNTL__TVPLL_TURNOFF_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__TVPLL_TURNOFF_MASK                0x00000010L
DECL|macro|PLL_PWRMGT_CNTL__TVPLL_TURNOFF
mdefine_line|#define PLL_PWRMGT_CNTL__TVPLL_TURNOFF                     0x00000010L
DECL|macro|PLL_PWRMGT_CNTL__AGPCLK_DYN_STOP_LAT_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__AGPCLK_DYN_STOP_LAT_MASK          0x000001e0L
DECL|macro|PLL_PWRMGT_CNTL__APM_POWER_STATE_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__APM_POWER_STATE_MASK              0x00000600L
DECL|macro|PLL_PWRMGT_CNTL__APM_PWRSTATE_RD_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__APM_PWRSTATE_RD_MASK              0x00001800L
DECL|macro|PLL_PWRMGT_CNTL__PM_MODE_SEL_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__PM_MODE_SEL_MASK                  0x00002000L
DECL|macro|PLL_PWRMGT_CNTL__PM_MODE_SEL
mdefine_line|#define PLL_PWRMGT_CNTL__PM_MODE_SEL                       0x00002000L
DECL|macro|PLL_PWRMGT_CNTL__EN_PWRSEQ_DONE_COND_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__EN_PWRSEQ_DONE_COND_MASK          0x00004000L
DECL|macro|PLL_PWRMGT_CNTL__EN_PWRSEQ_DONE_COND
mdefine_line|#define PLL_PWRMGT_CNTL__EN_PWRSEQ_DONE_COND               0x00004000L
DECL|macro|PLL_PWRMGT_CNTL__EN_DISP_PARKED_COND_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__EN_DISP_PARKED_COND_MASK          0x00008000L
DECL|macro|PLL_PWRMGT_CNTL__EN_DISP_PARKED_COND
mdefine_line|#define PLL_PWRMGT_CNTL__EN_DISP_PARKED_COND               0x00008000L
DECL|macro|PLL_PWRMGT_CNTL__MOBILE_SU_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__MOBILE_SU_MASK                    0x00010000L
DECL|macro|PLL_PWRMGT_CNTL__MOBILE_SU
mdefine_line|#define PLL_PWRMGT_CNTL__MOBILE_SU                         0x00010000L
DECL|macro|PLL_PWRMGT_CNTL__SU_SCLK_USE_BCLK_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__SU_SCLK_USE_BCLK_MASK             0x00020000L
DECL|macro|PLL_PWRMGT_CNTL__SU_SCLK_USE_BCLK
mdefine_line|#define PLL_PWRMGT_CNTL__SU_SCLK_USE_BCLK                  0x00020000L
DECL|macro|PLL_PWRMGT_CNTL__SU_MCLK_USE_BCLK_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__SU_MCLK_USE_BCLK_MASK             0x00040000L
DECL|macro|PLL_PWRMGT_CNTL__SU_MCLK_USE_BCLK
mdefine_line|#define PLL_PWRMGT_CNTL__SU_MCLK_USE_BCLK                  0x00040000L
DECL|macro|PLL_PWRMGT_CNTL__SU_SUSTAIN_DISABLE_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__SU_SUSTAIN_DISABLE_MASK           0x00080000L
DECL|macro|PLL_PWRMGT_CNTL__SU_SUSTAIN_DISABLE
mdefine_line|#define PLL_PWRMGT_CNTL__SU_SUSTAIN_DISABLE                0x00080000L
DECL|macro|PLL_PWRMGT_CNTL__TCL_BYPASS_DISABLE_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__TCL_BYPASS_DISABLE_MASK           0x00100000L
DECL|macro|PLL_PWRMGT_CNTL__TCL_BYPASS_DISABLE
mdefine_line|#define PLL_PWRMGT_CNTL__TCL_BYPASS_DISABLE                0x00100000L
DECL|macro|PLL_PWRMGT_CNTL__TCL_CLOCK_CTIVE_RD_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__TCL_CLOCK_CTIVE_RD_MASK          0x00200000L
DECL|macro|PLL_PWRMGT_CNTL__TCL_CLOCK_ACTIVE_RD
mdefine_line|#define PLL_PWRMGT_CNTL__TCL_CLOCK_ACTIVE_RD               0x00200000L
DECL|macro|PLL_PWRMGT_CNTL__CG_NO2_DEBUG_MASK
mdefine_line|#define PLL_PWRMGT_CNTL__CG_NO2_DEBUG_MASK                 0xff000000L
singleline_comment|// CLK_PWRMGT_CNTL
DECL|macro|CLK_PWRMGT_CNTL__MPLL_PWRMGT_OFF_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__MPLL_PWRMGT_OFF_MASK           0x00000001L
DECL|macro|CLK_PWRMGT_CNTL__MPLL_PWRMGT_OFF
mdefine_line|#define CLK_PWRMGT_CNTL__MPLL_PWRMGT_OFF                0x00000001L
DECL|macro|CLK_PWRMGT_CNTL__SPLL_PWRMGT_OFF_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__SPLL_PWRMGT_OFF_MASK           0x00000002L
DECL|macro|CLK_PWRMGT_CNTL__SPLL_PWRMGT_OFF
mdefine_line|#define CLK_PWRMGT_CNTL__SPLL_PWRMGT_OFF                0x00000002L
DECL|macro|CLK_PWRMGT_CNTL__PPLL_PWRMGT_OFF_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__PPLL_PWRMGT_OFF_MASK           0x00000004L
DECL|macro|CLK_PWRMGT_CNTL__PPLL_PWRMGT_OFF
mdefine_line|#define CLK_PWRMGT_CNTL__PPLL_PWRMGT_OFF                0x00000004L
DECL|macro|CLK_PWRMGT_CNTL__P2PLL_PWRMGT_OFF_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__P2PLL_PWRMGT_OFF_MASK          0x00000008L
DECL|macro|CLK_PWRMGT_CNTL__P2PLL_PWRMGT_OFF
mdefine_line|#define CLK_PWRMGT_CNTL__P2PLL_PWRMGT_OFF               0x00000008L
DECL|macro|CLK_PWRMGT_CNTL__MCLK_TURNOFF_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__MCLK_TURNOFF_MASK              0x00000010L
DECL|macro|CLK_PWRMGT_CNTL__MCLK_TURNOFF
mdefine_line|#define CLK_PWRMGT_CNTL__MCLK_TURNOFF                   0x00000010L
DECL|macro|CLK_PWRMGT_CNTL__SCLK_TURNOFF_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__SCLK_TURNOFF_MASK              0x00000020L
DECL|macro|CLK_PWRMGT_CNTL__SCLK_TURNOFF
mdefine_line|#define CLK_PWRMGT_CNTL__SCLK_TURNOFF                   0x00000020L
DECL|macro|CLK_PWRMGT_CNTL__PCLK_TURNOFF_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__PCLK_TURNOFF_MASK              0x00000040L
DECL|macro|CLK_PWRMGT_CNTL__PCLK_TURNOFF
mdefine_line|#define CLK_PWRMGT_CNTL__PCLK_TURNOFF                   0x00000040L
DECL|macro|CLK_PWRMGT_CNTL__P2CLK_TURNOFF_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__P2CLK_TURNOFF_MASK             0x00000080L
DECL|macro|CLK_PWRMGT_CNTL__P2CLK_TURNOFF
mdefine_line|#define CLK_PWRMGT_CNTL__P2CLK_TURNOFF                  0x00000080L
DECL|macro|CLK_PWRMGT_CNTL__MC_CH_MODE_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__MC_CH_MODE_MASK                0x00000100L
DECL|macro|CLK_PWRMGT_CNTL__MC_CH_MODE
mdefine_line|#define CLK_PWRMGT_CNTL__MC_CH_MODE                     0x00000100L
DECL|macro|CLK_PWRMGT_CNTL__TEST_MODE_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__TEST_MODE_MASK                 0x00000200L
DECL|macro|CLK_PWRMGT_CNTL__TEST_MODE
mdefine_line|#define CLK_PWRMGT_CNTL__TEST_MODE                      0x00000200L
DECL|macro|CLK_PWRMGT_CNTL__GLOBAL_PMAN_EN_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__GLOBAL_PMAN_EN_MASK            0x00000400L
DECL|macro|CLK_PWRMGT_CNTL__GLOBAL_PMAN_EN
mdefine_line|#define CLK_PWRMGT_CNTL__GLOBAL_PMAN_EN                 0x00000400L
DECL|macro|CLK_PWRMGT_CNTL__ENGINE_DYNCLK_MODE_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__ENGINE_DYNCLK_MODE_MASK        0x00001000L
DECL|macro|CLK_PWRMGT_CNTL__ENGINE_DYNCLK_MODE
mdefine_line|#define CLK_PWRMGT_CNTL__ENGINE_DYNCLK_MODE             0x00001000L
DECL|macro|CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT_MASK           0x00006000L
DECL|macro|CLK_PWRMGT_CNTL__DISP_DYN_STOP_LAT_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__DISP_DYN_STOP_LAT_MASK         0x00008000L
DECL|macro|CLK_PWRMGT_CNTL__DISP_DYN_STOP_LAT
mdefine_line|#define CLK_PWRMGT_CNTL__DISP_DYN_STOP_LAT              0x00008000L
DECL|macro|CLK_PWRMGT_CNTL__MC_BUSY_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__MC_BUSY_MASK                   0x00010000L
DECL|macro|CLK_PWRMGT_CNTL__MC_BUSY
mdefine_line|#define CLK_PWRMGT_CNTL__MC_BUSY                        0x00010000L
DECL|macro|CLK_PWRMGT_CNTL__MC_INT_CNTL_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__MC_INT_CNTL_MASK               0x00020000L
DECL|macro|CLK_PWRMGT_CNTL__MC_INT_CNTL
mdefine_line|#define CLK_PWRMGT_CNTL__MC_INT_CNTL                    0x00020000L
DECL|macro|CLK_PWRMGT_CNTL__MC_SWITCH_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__MC_SWITCH_MASK                 0x00040000L
DECL|macro|CLK_PWRMGT_CNTL__MC_SWITCH
mdefine_line|#define CLK_PWRMGT_CNTL__MC_SWITCH                      0x00040000L
DECL|macro|CLK_PWRMGT_CNTL__DLL_READY_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__DLL_READY_MASK                 0x00080000L
DECL|macro|CLK_PWRMGT_CNTL__DLL_READY
mdefine_line|#define CLK_PWRMGT_CNTL__DLL_READY                      0x00080000L
DECL|macro|CLK_PWRMGT_CNTL__DISP_PM_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__DISP_PM_MASK                   0x00100000L
DECL|macro|CLK_PWRMGT_CNTL__DISP_PM
mdefine_line|#define CLK_PWRMGT_CNTL__DISP_PM                        0x00100000L
DECL|macro|CLK_PWRMGT_CNTL__DYN_STOP_MODE_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__DYN_STOP_MODE_MASK             0x00e00000L
DECL|macro|CLK_PWRMGT_CNTL__CG_NO1_DEBUG_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__CG_NO1_DEBUG_MASK              0x3f000000L
DECL|macro|CLK_PWRMGT_CNTL__TVPLL_PWRMGT_OFF_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__TVPLL_PWRMGT_OFF_MASK          0x40000000L
DECL|macro|CLK_PWRMGT_CNTL__TVPLL_PWRMGT_OFF
mdefine_line|#define CLK_PWRMGT_CNTL__TVPLL_PWRMGT_OFF               0x40000000L
DECL|macro|CLK_PWRMGT_CNTL__TVCLK_TURNOFF_MASK
mdefine_line|#define CLK_PWRMGT_CNTL__TVCLK_TURNOFF_MASK             0x80000000L
DECL|macro|CLK_PWRMGT_CNTL__TVCLK_TURNOFF
mdefine_line|#define CLK_PWRMGT_CNTL__TVCLK_TURNOFF                  0x80000000L
singleline_comment|// BUS_CNTL1
DECL|macro|BUS_CNTL1__PMI_IO_DISABLE_MASK
mdefine_line|#define BUS_CNTL1__PMI_IO_DISABLE_MASK                     0x00000001L
DECL|macro|BUS_CNTL1__PMI_IO_DISABLE
mdefine_line|#define BUS_CNTL1__PMI_IO_DISABLE                          0x00000001L
DECL|macro|BUS_CNTL1__PMI_MEM_DISABLE_MASK
mdefine_line|#define BUS_CNTL1__PMI_MEM_DISABLE_MASK                    0x00000002L
DECL|macro|BUS_CNTL1__PMI_MEM_DISABLE
mdefine_line|#define BUS_CNTL1__PMI_MEM_DISABLE                         0x00000002L
DECL|macro|BUS_CNTL1__PMI_BM_DISABLE_MASK
mdefine_line|#define BUS_CNTL1__PMI_BM_DISABLE_MASK                     0x00000004L
DECL|macro|BUS_CNTL1__PMI_BM_DISABLE
mdefine_line|#define BUS_CNTL1__PMI_BM_DISABLE                          0x00000004L
DECL|macro|BUS_CNTL1__PMI_INT_DISABLE_MASK
mdefine_line|#define BUS_CNTL1__PMI_INT_DISABLE_MASK                    0x00000008L
DECL|macro|BUS_CNTL1__PMI_INT_DISABLE
mdefine_line|#define BUS_CNTL1__PMI_INT_DISABLE                         0x00000008L
DECL|macro|BUS_CNTL1__BUS2_IMMEDIATE_PMI_DISABLE_MASK
mdefine_line|#define BUS_CNTL1__BUS2_IMMEDIATE_PMI_DISABLE_MASK         0x00000020L
DECL|macro|BUS_CNTL1__BUS2_IMMEDIATE_PMI_DISABLE
mdefine_line|#define BUS_CNTL1__BUS2_IMMEDIATE_PMI_DISABLE              0x00000020L
DECL|macro|BUS_CNTL1__BUS2_VGA_REG_COHERENCY_DIS_MASK
mdefine_line|#define BUS_CNTL1__BUS2_VGA_REG_COHERENCY_DIS_MASK         0x00000100L
DECL|macro|BUS_CNTL1__BUS2_VGA_REG_COHERENCY_DIS
mdefine_line|#define BUS_CNTL1__BUS2_VGA_REG_COHERENCY_DIS              0x00000100L
DECL|macro|BUS_CNTL1__BUS2_VGA_MEM_COHERENCY_DIS_MASK
mdefine_line|#define BUS_CNTL1__BUS2_VGA_MEM_COHERENCY_DIS_MASK         0x00000200L
DECL|macro|BUS_CNTL1__BUS2_VGA_MEM_COHERENCY_DIS
mdefine_line|#define BUS_CNTL1__BUS2_VGA_MEM_COHERENCY_DIS              0x00000200L
DECL|macro|BUS_CNTL1__BUS2_HDP_REG_COHERENCY_DIS_MASK
mdefine_line|#define BUS_CNTL1__BUS2_HDP_REG_COHERENCY_DIS_MASK         0x00000400L
DECL|macro|BUS_CNTL1__BUS2_HDP_REG_COHERENCY_DIS
mdefine_line|#define BUS_CNTL1__BUS2_HDP_REG_COHERENCY_DIS              0x00000400L
DECL|macro|BUS_CNTL1__BUS2_GUI_INITIATOR_COHERENCY_DIS_MASK
mdefine_line|#define BUS_CNTL1__BUS2_GUI_INITIATOR_COHERENCY_DIS_MASK   0x00000800L
DECL|macro|BUS_CNTL1__BUS2_GUI_INITIATOR_COHERENCY_DIS
mdefine_line|#define BUS_CNTL1__BUS2_GUI_INITIATOR_COHERENCY_DIS        0x00000800L
DECL|macro|BUS_CNTL1__MOBILE_PLATFORM_SEL_MASK
mdefine_line|#define BUS_CNTL1__MOBILE_PLATFORM_SEL_MASK                0x0c000000L
DECL|macro|BUS_CNTL1__SEND_SBA_LATENCY_MASK
mdefine_line|#define BUS_CNTL1__SEND_SBA_LATENCY_MASK                   0x70000000L
DECL|macro|BUS_CNTL1__AGPCLK_VALID_MASK
mdefine_line|#define BUS_CNTL1__AGPCLK_VALID_MASK                       0x80000000L
DECL|macro|BUS_CNTL1__AGPCLK_VALID
mdefine_line|#define BUS_CNTL1__AGPCLK_VALID                            0x80000000L
singleline_comment|// BUS_CNTL1
DECL|macro|BUS_CNTL1__PMI_IO_DISABLE__SHIFT
mdefine_line|#define&t;BUS_CNTL1__PMI_IO_DISABLE__SHIFT                   0x00000000
DECL|macro|BUS_CNTL1__PMI_MEM_DISABLE__SHIFT
mdefine_line|#define&t;BUS_CNTL1__PMI_MEM_DISABLE__SHIFT                  0x00000001
DECL|macro|BUS_CNTL1__PMI_BM_DISABLE__SHIFT
mdefine_line|#define&t;BUS_CNTL1__PMI_BM_DISABLE__SHIFT                   0x00000002
DECL|macro|BUS_CNTL1__PMI_INT_DISABLE__SHIFT
mdefine_line|#define&t;BUS_CNTL1__PMI_INT_DISABLE__SHIFT                  0x00000003
DECL|macro|BUS_CNTL1__BUS2_IMMEDIATE_PMI_DISABLE__SHIFT
mdefine_line|#define&t;BUS_CNTL1__BUS2_IMMEDIATE_PMI_DISABLE__SHIFT       0x00000005
DECL|macro|BUS_CNTL1__BUS2_VGA_REG_COHERENCY_DIS__SHIFT
mdefine_line|#define&t;BUS_CNTL1__BUS2_VGA_REG_COHERENCY_DIS__SHIFT       0x00000008
DECL|macro|BUS_CNTL1__BUS2_VGA_MEM_COHERENCY_DIS__SHIFT
mdefine_line|#define&t;BUS_CNTL1__BUS2_VGA_MEM_COHERENCY_DIS__SHIFT       0x00000009
DECL|macro|BUS_CNTL1__BUS2_HDP_REG_COHERENCY_DIS__SHIFT
mdefine_line|#define&t;BUS_CNTL1__BUS2_HDP_REG_COHERENCY_DIS__SHIFT       0x0000000a
DECL|macro|BUS_CNTL1__BUS2_GUI_INITIATOR_COHERENCY_DIS__SHIFT
mdefine_line|#define&t;BUS_CNTL1__BUS2_GUI_INITIATOR_COHERENCY_DIS__SHIFT 0x0000000b
DECL|macro|BUS_CNTL1__MOBILE_PLATFORM_SEL__SHIFT
mdefine_line|#define&t;BUS_CNTL1__MOBILE_PLATFORM_SEL__SHIFT              0x0000001a
DECL|macro|BUS_CNTL1__SEND_SBA_LATENCY__SHIFT
mdefine_line|#define&t;BUS_CNTL1__SEND_SBA_LATENCY__SHIFT                 0x0000001c
DECL|macro|BUS_CNTL1__AGPCLK_VALID__SHIFT
mdefine_line|#define&t;BUS_CNTL1__AGPCLK_VALID__SHIFT                     0x0000001f
singleline_comment|// CRTC_OFFSET_CNTL
DECL|macro|CRTC_OFFSET_CNTL__CRTC_TILE_LINE_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_TILE_LINE_MASK              0x0000000fL
DECL|macro|CRTC_OFFSET_CNTL__CRTC_TILE_LINE_RIGHT_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_TILE_LINE_RIGHT_MASK        0x000000f0L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_TILE_EN_RIGHT_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_TILE_EN_RIGHT_MASK          0x00004000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_TILE_EN_RIGHT
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_TILE_EN_RIGHT               0x00004000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_TILE_EN_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_TILE_EN_MASK                0x00008000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_TILE_EN
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_TILE_EN                     0x00008000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_OFFSET_FLIP_CNTL_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_OFFSET_FLIP_CNTL_MASK       0x00010000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_OFFSET_FLIP_CNTL
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_OFFSET_FLIP_CNTL            0x00010000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_STEREO_OFFSET_EN_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_STEREO_OFFSET_EN_MASK       0x00020000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_STEREO_OFFSET_EN
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_STEREO_OFFSET_EN            0x00020000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC_EN_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC_EN_MASK         0x000c0000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC_OUT_EN_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC_OUT_EN_MASK     0x00100000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC_OUT_EN
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC_OUT_EN          0x00100000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC_MASK            0x00200000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC                 0x00200000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET_LEFT_EN_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET_LEFT_EN_MASK 0x10000000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET_LEFT_EN
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET_LEFT_EN     0x10000000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET_RIGHT_EN_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET_RIGHT_EN_MASK 0x20000000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET_RIGHT_EN
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET_RIGHT_EN    0x20000000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET_MASK        0x40000000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_GUI_TRIG_OFFSET             0x40000000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_OFFSET_LOCK_MASK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_OFFSET_LOCK_MASK            0x80000000L
DECL|macro|CRTC_OFFSET_CNTL__CRTC_OFFSET_LOCK
mdefine_line|#define CRTC_OFFSET_CNTL__CRTC_OFFSET_LOCK                 0x80000000L
singleline_comment|// CRTC_GEN_CNTL
DECL|macro|CRTC_GEN_CNTL__CRTC_DBL_SCAN_EN_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_DBL_SCAN_EN_MASK               0x00000001L
DECL|macro|CRTC_GEN_CNTL__CRTC_DBL_SCAN_EN
mdefine_line|#define CRTC_GEN_CNTL__CRTC_DBL_SCAN_EN                    0x00000001L
DECL|macro|CRTC_GEN_CNTL__CRTC_INTERLACE_EN_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_INTERLACE_EN_MASK              0x00000002L
DECL|macro|CRTC_GEN_CNTL__CRTC_INTERLACE_EN
mdefine_line|#define CRTC_GEN_CNTL__CRTC_INTERLACE_EN                   0x00000002L
DECL|macro|CRTC_GEN_CNTL__CRTC_C_SYNC_EN_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_C_SYNC_EN_MASK                 0x00000010L
DECL|macro|CRTC_GEN_CNTL__CRTC_C_SYNC_EN
mdefine_line|#define CRTC_GEN_CNTL__CRTC_C_SYNC_EN                      0x00000010L
DECL|macro|CRTC_GEN_CNTL__CRTC_PIX_WIDTH_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_PIX_WIDTH_MASK                 0x00000f00L
DECL|macro|CRTC_GEN_CNTL__CRTC_ICON_EN_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_ICON_EN_MASK                   0x00008000L
DECL|macro|CRTC_GEN_CNTL__CRTC_ICON_EN
mdefine_line|#define CRTC_GEN_CNTL__CRTC_ICON_EN                        0x00008000L
DECL|macro|CRTC_GEN_CNTL__CRTC_CUR_EN_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_CUR_EN_MASK                    0x00010000L
DECL|macro|CRTC_GEN_CNTL__CRTC_CUR_EN
mdefine_line|#define CRTC_GEN_CNTL__CRTC_CUR_EN                         0x00010000L
DECL|macro|CRTC_GEN_CNTL__CRTC_VSTAT_MODE_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_VSTAT_MODE_MASK                0x00060000L
DECL|macro|CRTC_GEN_CNTL__CRTC_CUR_MODE_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_CUR_MODE_MASK                  0x00700000L
DECL|macro|CRTC_GEN_CNTL__CRTC_EXT_DISP_EN_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_EXT_DISP_EN_MASK               0x01000000L
DECL|macro|CRTC_GEN_CNTL__CRTC_EXT_DISP_EN
mdefine_line|#define CRTC_GEN_CNTL__CRTC_EXT_DISP_EN                    0x01000000L
DECL|macro|CRTC_GEN_CNTL__CRTC_EN_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_EN_MASK                        0x02000000L
DECL|macro|CRTC_GEN_CNTL__CRTC_EN
mdefine_line|#define CRTC_GEN_CNTL__CRTC_EN                             0x02000000L
DECL|macro|CRTC_GEN_CNTL__CRTC_DISP_REQ_EN_B_MASK
mdefine_line|#define CRTC_GEN_CNTL__CRTC_DISP_REQ_EN_B_MASK             0x04000000L
DECL|macro|CRTC_GEN_CNTL__CRTC_DISP_REQ_EN_B
mdefine_line|#define CRTC_GEN_CNTL__CRTC_DISP_REQ_EN_B                  0x04000000L
singleline_comment|// CRTC2_GEN_CNTL
DECL|macro|CRTC2_GEN_CNTL__CRTC2_DBL_SCAN_EN_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_DBL_SCAN_EN_MASK             0x00000001L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_DBL_SCAN_EN
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_DBL_SCAN_EN                  0x00000001L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_INTERLACE_EN_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_INTERLACE_EN_MASK            0x00000002L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_INTERLACE_EN
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_INTERLACE_EN                 0x00000002L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_SYNC_TRISTATE_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_SYNC_TRISTATE_MASK           0x00000010L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_SYNC_TRISTATE
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_SYNC_TRISTATE                0x00000010L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_HSYNC_TRISTATE_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_HSYNC_TRISTATE_MASK          0x00000020L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_HSYNC_TRISTATE
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_HSYNC_TRISTATE               0x00000020L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_VSYNC_TRISTATE_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_VSYNC_TRISTATE_MASK          0x00000040L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_VSYNC_TRISTATE
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_VSYNC_TRISTATE               0x00000040L
DECL|macro|CRTC2_GEN_CNTL__CRT2_ON_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRT2_ON_MASK                       0x00000080L
DECL|macro|CRTC2_GEN_CNTL__CRT2_ON
mdefine_line|#define CRTC2_GEN_CNTL__CRT2_ON                            0x00000080L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_PIX_WIDTH_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_PIX_WIDTH_MASK               0x00000f00L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_ICON_EN_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_ICON_EN_MASK                 0x00008000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_ICON_EN
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_ICON_EN                      0x00008000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_CUR_EN_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_CUR_EN_MASK                  0x00010000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_CUR_EN
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_CUR_EN                       0x00010000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_CUR_MODE_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_CUR_MODE_MASK                0x00700000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_DISPLAY_DIS_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_DISPLAY_DIS_MASK             0x00800000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_DISPLAY_DIS
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_DISPLAY_DIS                  0x00800000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_EN_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_EN_MASK                      0x02000000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_EN
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_EN                           0x02000000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_DISP_REQ_EN_B_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_DISP_REQ_EN_B_MASK           0x04000000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_DISP_REQ_EN_B
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_DISP_REQ_EN_B                0x04000000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_C_SYNC_EN_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_C_SYNC_EN_MASK               0x08000000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_C_SYNC_EN
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_C_SYNC_EN                    0x08000000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_HSYNC_DIS_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_HSYNC_DIS_MASK               0x10000000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_HSYNC_DIS
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_HSYNC_DIS                    0x10000000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_VSYNC_DIS_MASK
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_VSYNC_DIS_MASK               0x20000000L
DECL|macro|CRTC2_GEN_CNTL__CRTC2_VSYNC_DIS
mdefine_line|#define CRTC2_GEN_CNTL__CRTC2_VSYNC_DIS                    0x20000000L
singleline_comment|// AGP_CNTL
DECL|macro|AGP_CNTL__MAX_IDLE_CLK_MASK
mdefine_line|#define AGP_CNTL__MAX_IDLE_CLK_MASK                        0x000000ffL
DECL|macro|AGP_CNTL__HOLD_RD_FIFO_MASK
mdefine_line|#define AGP_CNTL__HOLD_RD_FIFO_MASK                        0x00000100L
DECL|macro|AGP_CNTL__HOLD_RD_FIFO
mdefine_line|#define AGP_CNTL__HOLD_RD_FIFO                             0x00000100L
DECL|macro|AGP_CNTL__HOLD_RQ_FIFO_MASK
mdefine_line|#define AGP_CNTL__HOLD_RQ_FIFO_MASK                        0x00000200L
DECL|macro|AGP_CNTL__HOLD_RQ_FIFO
mdefine_line|#define AGP_CNTL__HOLD_RQ_FIFO                             0x00000200L
DECL|macro|AGP_CNTL__EN_2X_STBB_MASK
mdefine_line|#define AGP_CNTL__EN_2X_STBB_MASK                          0x00000400L
DECL|macro|AGP_CNTL__EN_2X_STBB
mdefine_line|#define AGP_CNTL__EN_2X_STBB                               0x00000400L
DECL|macro|AGP_CNTL__FORCE_FULL_SBA_MASK
mdefine_line|#define AGP_CNTL__FORCE_FULL_SBA_MASK                      0x00000800L
DECL|macro|AGP_CNTL__FORCE_FULL_SBA
mdefine_line|#define AGP_CNTL__FORCE_FULL_SBA                           0x00000800L
DECL|macro|AGP_CNTL__SBA_DIS_MASK
mdefine_line|#define AGP_CNTL__SBA_DIS_MASK                             0x00001000L
DECL|macro|AGP_CNTL__SBA_DIS
mdefine_line|#define AGP_CNTL__SBA_DIS                                  0x00001000L
DECL|macro|AGP_CNTL__AGP_REV_ID_MASK
mdefine_line|#define AGP_CNTL__AGP_REV_ID_MASK                          0x00002000L
DECL|macro|AGP_CNTL__AGP_REV_ID
mdefine_line|#define AGP_CNTL__AGP_REV_ID                               0x00002000L
DECL|macro|AGP_CNTL__REG_CRIPPLE_AGP4X_MASK
mdefine_line|#define AGP_CNTL__REG_CRIPPLE_AGP4X_MASK                   0x00004000L
DECL|macro|AGP_CNTL__REG_CRIPPLE_AGP4X
mdefine_line|#define AGP_CNTL__REG_CRIPPLE_AGP4X                        0x00004000L
DECL|macro|AGP_CNTL__REG_CRIPPLE_AGP2X4X_MASK
mdefine_line|#define AGP_CNTL__REG_CRIPPLE_AGP2X4X_MASK                 0x00008000L
DECL|macro|AGP_CNTL__REG_CRIPPLE_AGP2X4X
mdefine_line|#define AGP_CNTL__REG_CRIPPLE_AGP2X4X                      0x00008000L
DECL|macro|AGP_CNTL__FORCE_INT_VREF_MASK
mdefine_line|#define AGP_CNTL__FORCE_INT_VREF_MASK                      0x00010000L
DECL|macro|AGP_CNTL__FORCE_INT_VREF
mdefine_line|#define AGP_CNTL__FORCE_INT_VREF                           0x00010000L
DECL|macro|AGP_CNTL__PENDING_SLOTS_VAL_MASK
mdefine_line|#define AGP_CNTL__PENDING_SLOTS_VAL_MASK                   0x00060000L
DECL|macro|AGP_CNTL__PENDING_SLOTS_SEL_MASK
mdefine_line|#define AGP_CNTL__PENDING_SLOTS_SEL_MASK                   0x00080000L
DECL|macro|AGP_CNTL__PENDING_SLOTS_SEL
mdefine_line|#define AGP_CNTL__PENDING_SLOTS_SEL                        0x00080000L
DECL|macro|AGP_CNTL__EN_EXTENDED_AD_STB_2X_MASK
mdefine_line|#define AGP_CNTL__EN_EXTENDED_AD_STB_2X_MASK               0x00100000L
DECL|macro|AGP_CNTL__EN_EXTENDED_AD_STB_2X
mdefine_line|#define AGP_CNTL__EN_EXTENDED_AD_STB_2X                    0x00100000L
DECL|macro|AGP_CNTL__DIS_QUEUED_GNT_FIX_MASK
mdefine_line|#define AGP_CNTL__DIS_QUEUED_GNT_FIX_MASK                  0x00200000L
DECL|macro|AGP_CNTL__DIS_QUEUED_GNT_FIX
mdefine_line|#define AGP_CNTL__DIS_QUEUED_GNT_FIX                       0x00200000L
DECL|macro|AGP_CNTL__EN_RDATA2X4X_MULTIRESET_MASK
mdefine_line|#define AGP_CNTL__EN_RDATA2X4X_MULTIRESET_MASK             0x00400000L
DECL|macro|AGP_CNTL__EN_RDATA2X4X_MULTIRESET
mdefine_line|#define AGP_CNTL__EN_RDATA2X4X_MULTIRESET                  0x00400000L
DECL|macro|AGP_CNTL__EN_RBFCALM_MASK
mdefine_line|#define AGP_CNTL__EN_RBFCALM_MASK                          0x00800000L
DECL|macro|AGP_CNTL__EN_RBFCALM
mdefine_line|#define AGP_CNTL__EN_RBFCALM                               0x00800000L
DECL|macro|AGP_CNTL__FORCE_EXT_VREF_MASK
mdefine_line|#define AGP_CNTL__FORCE_EXT_VREF_MASK                      0x01000000L
DECL|macro|AGP_CNTL__FORCE_EXT_VREF
mdefine_line|#define AGP_CNTL__FORCE_EXT_VREF                           0x01000000L
DECL|macro|AGP_CNTL__DIS_RBF_MASK
mdefine_line|#define AGP_CNTL__DIS_RBF_MASK                             0x02000000L
DECL|macro|AGP_CNTL__DIS_RBF
mdefine_line|#define AGP_CNTL__DIS_RBF                                  0x02000000L
DECL|macro|AGP_CNTL__DELAY_FIRST_SBA_EN_MASK
mdefine_line|#define AGP_CNTL__DELAY_FIRST_SBA_EN_MASK                  0x04000000L
DECL|macro|AGP_CNTL__DELAY_FIRST_SBA_EN
mdefine_line|#define AGP_CNTL__DELAY_FIRST_SBA_EN                       0x04000000L
DECL|macro|AGP_CNTL__DELAY_FIRST_SBA_VAL_MASK
mdefine_line|#define AGP_CNTL__DELAY_FIRST_SBA_VAL_MASK                 0x38000000L
DECL|macro|AGP_CNTL__AGP_MISC_MASK
mdefine_line|#define AGP_CNTL__AGP_MISC_MASK                            0xc0000000L
singleline_comment|// AGP_CNTL
DECL|macro|AGP_CNTL__MAX_IDLE_CLK__SHIFT
mdefine_line|#define&t;AGP_CNTL__MAX_IDLE_CLK__SHIFT                      0x00000000
DECL|macro|AGP_CNTL__HOLD_RD_FIFO__SHIFT
mdefine_line|#define&t;AGP_CNTL__HOLD_RD_FIFO__SHIFT                      0x00000008
DECL|macro|AGP_CNTL__HOLD_RQ_FIFO__SHIFT
mdefine_line|#define&t;AGP_CNTL__HOLD_RQ_FIFO__SHIFT                      0x00000009
DECL|macro|AGP_CNTL__EN_2X_STBB__SHIFT
mdefine_line|#define&t;AGP_CNTL__EN_2X_STBB__SHIFT                        0x0000000a
DECL|macro|AGP_CNTL__FORCE_FULL_SBA__SHIFT
mdefine_line|#define&t;AGP_CNTL__FORCE_FULL_SBA__SHIFT                    0x0000000b
DECL|macro|AGP_CNTL__SBA_DIS__SHIFT
mdefine_line|#define&t;AGP_CNTL__SBA_DIS__SHIFT                           0x0000000c
DECL|macro|AGP_CNTL__AGP_REV_ID__SHIFT
mdefine_line|#define&t;AGP_CNTL__AGP_REV_ID__SHIFT                        0x0000000d
DECL|macro|AGP_CNTL__REG_CRIPPLE_AGP4X__SHIFT
mdefine_line|#define&t;AGP_CNTL__REG_CRIPPLE_AGP4X__SHIFT                 0x0000000e
DECL|macro|AGP_CNTL__REG_CRIPPLE_AGP2X4X__SHIFT
mdefine_line|#define&t;AGP_CNTL__REG_CRIPPLE_AGP2X4X__SHIFT               0x0000000f
DECL|macro|AGP_CNTL__FORCE_INT_VREF__SHIFT
mdefine_line|#define&t;AGP_CNTL__FORCE_INT_VREF__SHIFT                    0x00000010
DECL|macro|AGP_CNTL__PENDING_SLOTS_VAL__SHIFT
mdefine_line|#define&t;AGP_CNTL__PENDING_SLOTS_VAL__SHIFT                 0x00000011
DECL|macro|AGP_CNTL__PENDING_SLOTS_SEL__SHIFT
mdefine_line|#define&t;AGP_CNTL__PENDING_SLOTS_SEL__SHIFT                 0x00000013
DECL|macro|AGP_CNTL__EN_EXTENDED_AD_STB_2X__SHIFT
mdefine_line|#define&t;AGP_CNTL__EN_EXTENDED_AD_STB_2X__SHIFT             0x00000014
DECL|macro|AGP_CNTL__DIS_QUEUED_GNT_FIX__SHIFT
mdefine_line|#define&t;AGP_CNTL__DIS_QUEUED_GNT_FIX__SHIFT                0x00000015
DECL|macro|AGP_CNTL__EN_RDATA2X4X_MULTIRESET__SHIFT
mdefine_line|#define&t;AGP_CNTL__EN_RDATA2X4X_MULTIRESET__SHIFT           0x00000016
DECL|macro|AGP_CNTL__EN_RBFCALM__SHIFT
mdefine_line|#define&t;AGP_CNTL__EN_RBFCALM__SHIFT                        0x00000017
DECL|macro|AGP_CNTL__FORCE_EXT_VREF__SHIFT
mdefine_line|#define&t;AGP_CNTL__FORCE_EXT_VREF__SHIFT                    0x00000018
DECL|macro|AGP_CNTL__DIS_RBF__SHIFT
mdefine_line|#define&t;AGP_CNTL__DIS_RBF__SHIFT                           0x00000019
DECL|macro|AGP_CNTL__DELAY_FIRST_SBA_EN__SHIFT
mdefine_line|#define&t;AGP_CNTL__DELAY_FIRST_SBA_EN__SHIFT                0x0000001a
DECL|macro|AGP_CNTL__DELAY_FIRST_SBA_VAL__SHIFT
mdefine_line|#define&t;AGP_CNTL__DELAY_FIRST_SBA_VAL__SHIFT               0x0000001b
DECL|macro|AGP_CNTL__AGP_MISC__SHIFT
mdefine_line|#define&t;AGP_CNTL__AGP_MISC__SHIFT                          0x0000001e
singleline_comment|// DISP_MISC_CNTL
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_GRPH_PP_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_GRPH_PP_MASK            0x00000001L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_GRPH_PP
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_GRPH_PP                 0x00000001L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_SUBPIC_PP_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_SUBPIC_PP_MASK          0x00000002L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_SUBPIC_PP
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_SUBPIC_PP               0x00000002L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_OV0_PP_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_OV0_PP_MASK             0x00000004L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_OV0_PP
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_OV0_PP                  0x00000004L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_GRPH_SCLK_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_GRPH_SCLK_MASK          0x00000010L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_GRPH_SCLK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_GRPH_SCLK               0x00000010L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_SUBPIC_SCLK_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_SUBPIC_SCLK_MASK        0x00000020L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_SUBPIC_SCLK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_SUBPIC_SCLK             0x00000020L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_OV0_SCLK_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_OV0_SCLK_MASK           0x00000040L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_OV0_SCLK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_OV0_SCLK                0x00000040L
DECL|macro|DISP_MISC_CNTL__SYNC_STRENGTH_MASK
mdefine_line|#define DISP_MISC_CNTL__SYNC_STRENGTH_MASK                 0x00000300L
DECL|macro|DISP_MISC_CNTL__SYNC_PAD_FLOP_EN_MASK
mdefine_line|#define DISP_MISC_CNTL__SYNC_PAD_FLOP_EN_MASK              0x00000400L
DECL|macro|DISP_MISC_CNTL__SYNC_PAD_FLOP_EN
mdefine_line|#define DISP_MISC_CNTL__SYNC_PAD_FLOP_EN                   0x00000400L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_GRPH2_PP_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_GRPH2_PP_MASK           0x00001000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_GRPH2_PP
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_GRPH2_PP                0x00001000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_GRPH2_SCLK_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_GRPH2_SCLK_MASK         0x00008000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_GRPH2_SCLK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_GRPH2_SCLK              0x00008000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_LVDS_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_LVDS_MASK               0x00010000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_LVDS
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_LVDS                    0x00010000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_TMDS_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_TMDS_MASK               0x00020000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_TMDS
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_TMDS                    0x00020000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_DIG_TMDS_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_DIG_TMDS_MASK           0x00040000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_DIG_TMDS
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_DIG_TMDS                0x00040000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_TV_MASK
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_TV_MASK                 0x00080000L
DECL|macro|DISP_MISC_CNTL__SOFT_RESET_TV
mdefine_line|#define DISP_MISC_CNTL__SOFT_RESET_TV                      0x00080000L
DECL|macro|DISP_MISC_CNTL__PALETTE2_MEM_RD_MARGIN_MASK
mdefine_line|#define DISP_MISC_CNTL__PALETTE2_MEM_RD_MARGIN_MASK        0x00f00000L
DECL|macro|DISP_MISC_CNTL__PALETTE_MEM_RD_MARGIN_MASK
mdefine_line|#define DISP_MISC_CNTL__PALETTE_MEM_RD_MARGIN_MASK         0x0f000000L
DECL|macro|DISP_MISC_CNTL__RMX_BUF_MEM_RD_MARGIN_MASK
mdefine_line|#define DISP_MISC_CNTL__RMX_BUF_MEM_RD_MARGIN_MASK         0xf0000000L
singleline_comment|// DISP_PWR_MAN
DECL|macro|DISP_PWR_MAN__DISP_PWR_MAN_D3_CRTC_EN_MASK
mdefine_line|#define DISP_PWR_MAN__DISP_PWR_MAN_D3_CRTC_EN_MASK         0x00000001L
DECL|macro|DISP_PWR_MAN__DISP_PWR_MAN_D3_CRTC_EN
mdefine_line|#define DISP_PWR_MAN__DISP_PWR_MAN_D3_CRTC_EN              0x00000001L
DECL|macro|DISP_PWR_MAN__DISP2_PWR_MAN_D3_CRTC2_EN_MASK
mdefine_line|#define DISP_PWR_MAN__DISP2_PWR_MAN_D3_CRTC2_EN_MASK       0x00000010L
DECL|macro|DISP_PWR_MAN__DISP2_PWR_MAN_D3_CRTC2_EN
mdefine_line|#define DISP_PWR_MAN__DISP2_PWR_MAN_D3_CRTC2_EN            0x00000010L
DECL|macro|DISP_PWR_MAN__DISP_PWR_MAN_DPMS_MASK
mdefine_line|#define DISP_PWR_MAN__DISP_PWR_MAN_DPMS_MASK               0x00000300L
DECL|macro|DISP_PWR_MAN__DISP_D3_RST_MASK
mdefine_line|#define DISP_PWR_MAN__DISP_D3_RST_MASK                     0x00010000L
DECL|macro|DISP_PWR_MAN__DISP_D3_RST
mdefine_line|#define DISP_PWR_MAN__DISP_D3_RST                          0x00010000L
DECL|macro|DISP_PWR_MAN__DISP_D3_REG_RST_MASK
mdefine_line|#define DISP_PWR_MAN__DISP_D3_REG_RST_MASK                 0x00020000L
DECL|macro|DISP_PWR_MAN__DISP_D3_REG_RST
mdefine_line|#define DISP_PWR_MAN__DISP_D3_REG_RST                      0x00020000L
DECL|macro|DISP_PWR_MAN__DISP_D3_GRPH_RST_MASK
mdefine_line|#define DISP_PWR_MAN__DISP_D3_GRPH_RST_MASK                0x00040000L
DECL|macro|DISP_PWR_MAN__DISP_D3_GRPH_RST
mdefine_line|#define DISP_PWR_MAN__DISP_D3_GRPH_RST                     0x00040000L
DECL|macro|DISP_PWR_MAN__DISP_D3_SUBPIC_RST_MASK
mdefine_line|#define DISP_PWR_MAN__DISP_D3_SUBPIC_RST_MASK              0x00080000L
DECL|macro|DISP_PWR_MAN__DISP_D3_SUBPIC_RST
mdefine_line|#define DISP_PWR_MAN__DISP_D3_SUBPIC_RST                   0x00080000L
DECL|macro|DISP_PWR_MAN__DISP_D3_OV0_RST_MASK
mdefine_line|#define DISP_PWR_MAN__DISP_D3_OV0_RST_MASK                 0x00100000L
DECL|macro|DISP_PWR_MAN__DISP_D3_OV0_RST
mdefine_line|#define DISP_PWR_MAN__DISP_D3_OV0_RST                      0x00100000L
DECL|macro|DISP_PWR_MAN__DISP_D1D2_GRPH_RST_MASK
mdefine_line|#define DISP_PWR_MAN__DISP_D1D2_GRPH_RST_MASK              0x00200000L
DECL|macro|DISP_PWR_MAN__DISP_D1D2_GRPH_RST
mdefine_line|#define DISP_PWR_MAN__DISP_D1D2_GRPH_RST                   0x00200000L
DECL|macro|DISP_PWR_MAN__DISP_D1D2_SUBPIC_RST_MASK
mdefine_line|#define DISP_PWR_MAN__DISP_D1D2_SUBPIC_RST_MASK            0x00400000L
DECL|macro|DISP_PWR_MAN__DISP_D1D2_SUBPIC_RST
mdefine_line|#define DISP_PWR_MAN__DISP_D1D2_SUBPIC_RST                 0x00400000L
DECL|macro|DISP_PWR_MAN__DISP_D1D2_OV0_RST_MASK
mdefine_line|#define DISP_PWR_MAN__DISP_D1D2_OV0_RST_MASK               0x00800000L
DECL|macro|DISP_PWR_MAN__DISP_D1D2_OV0_RST
mdefine_line|#define DISP_PWR_MAN__DISP_D1D2_OV0_RST                    0x00800000L
DECL|macro|DISP_PWR_MAN__DIG_TMDS_ENABLE_RST_MASK
mdefine_line|#define DISP_PWR_MAN__DIG_TMDS_ENABLE_RST_MASK             0x01000000L
DECL|macro|DISP_PWR_MAN__DIG_TMDS_ENABLE_RST
mdefine_line|#define DISP_PWR_MAN__DIG_TMDS_ENABLE_RST                  0x01000000L
DECL|macro|DISP_PWR_MAN__TV_ENABLE_RST_MASK
mdefine_line|#define DISP_PWR_MAN__TV_ENABLE_RST_MASK                   0x02000000L
DECL|macro|DISP_PWR_MAN__TV_ENABLE_RST
mdefine_line|#define DISP_PWR_MAN__TV_ENABLE_RST                        0x02000000L
DECL|macro|DISP_PWR_MAN__AUTO_PWRUP_EN_MASK
mdefine_line|#define DISP_PWR_MAN__AUTO_PWRUP_EN_MASK                   0x04000000L
DECL|macro|DISP_PWR_MAN__AUTO_PWRUP_EN
mdefine_line|#define DISP_PWR_MAN__AUTO_PWRUP_EN                        0x04000000L
singleline_comment|// MC_IND_INDEX
DECL|macro|MC_IND_INDEX__MC_IND_ADDR_MASK
mdefine_line|#define MC_IND_INDEX__MC_IND_ADDR_MASK                     0x0000001fL
DECL|macro|MC_IND_INDEX__MC_IND_WR_EN_MASK
mdefine_line|#define MC_IND_INDEX__MC_IND_WR_EN_MASK                    0x00000100L
DECL|macro|MC_IND_INDEX__MC_IND_WR_EN
mdefine_line|#define MC_IND_INDEX__MC_IND_WR_EN                         0x00000100L
singleline_comment|// MC_IND_DATA
DECL|macro|MC_IND_DATA__MC_IND_DATA_MASK
mdefine_line|#define MC_IND_DATA__MC_IND_DATA_MASK                      0xffffffffL
singleline_comment|// MC_CHP_IO_CNTL_A1
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_CKA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SLEWN_CKA__SHIFT            0x00000000
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_AA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SLEWN_AA__SHIFT             0x00000001
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQMA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQMA__SHIFT           0x00000002
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQSA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQSA__SHIFT           0x00000003
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_CKA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SLEWP_CKA__SHIFT            0x00000004
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_AA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SLEWP_AA__SHIFT             0x00000005
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQMA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQMA__SHIFT           0x00000006
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQSA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQSA__SHIFT           0x00000007
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_PREAMP_AA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_PREAMP_AA__SHIFT            0x00000008
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQMA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQMA__SHIFT          0x00000009
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQSA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQSA__SHIFT          0x0000000a
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_IO_MODEA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_IO_MODEA__SHIFT             0x0000000c
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_REC_CKA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_REC_CKA__SHIFT              0x0000000e
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_REC_AA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_REC_AA__SHIFT               0x00000010
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_REC_DQMA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_REC_DQMA__SHIFT             0x00000012
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_REC_DQSA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_REC_DQSA__SHIFT             0x00000014
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SYNC_PHASEA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SYNC_PHASEA__SHIFT          0x00000016
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SYNC_CENTERA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SYNC_CENTERA__SHIFT         0x00000017
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SYNC_ENA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_SYNC_ENA__SHIFT             0x00000018
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_CLK_SELA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_CLK_SELA__SHIFT             0x0000001a
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_CLK_INVA__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_CLK_INVA__SHIFT             0x0000001c
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_DATA_ENIMP_A__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_DATA_ENIMP_A__SHIFT         0x0000001e
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_CNTL_ENIMP_A__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_A1__MEM_CNTL_ENIMP_A__SHIFT         0x0000001f
singleline_comment|// MC_CHP_IO_CNTL_B1
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_CKB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SLEWN_CKB__SHIFT            0x00000000
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_AB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SLEWN_AB__SHIFT             0x00000001
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQMB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQMB__SHIFT           0x00000002
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQSB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQSB__SHIFT           0x00000003
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_CKB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SLEWP_CKB__SHIFT            0x00000004
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_AB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SLEWP_AB__SHIFT             0x00000005
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQMB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQMB__SHIFT           0x00000006
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQSB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQSB__SHIFT           0x00000007
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_PREAMP_AB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_PREAMP_AB__SHIFT            0x00000008
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQMB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQMB__SHIFT          0x00000009
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQSB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQSB__SHIFT          0x0000000a
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_IO_MODEB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_IO_MODEB__SHIFT             0x0000000c
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_REC_CKB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_REC_CKB__SHIFT              0x0000000e
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_REC_AB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_REC_AB__SHIFT               0x00000010
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_REC_DQMB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_REC_DQMB__SHIFT             0x00000012
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_REC_DQSB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_REC_DQSB__SHIFT             0x00000014
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SYNC_PHASEB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SYNC_PHASEB__SHIFT          0x00000016
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SYNC_CENTERB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SYNC_CENTERB__SHIFT         0x00000017
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SYNC_ENB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_SYNC_ENB__SHIFT             0x00000018
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_CLK_SELB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_CLK_SELB__SHIFT             0x0000001a
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_CLK_INVB__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_CLK_INVB__SHIFT             0x0000001c
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_DATA_ENIMP_B__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_DATA_ENIMP_B__SHIFT         0x0000001e
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_CNTL_ENIMP_B__SHIFT
mdefine_line|#define&t;MC_CHP_IO_CNTL_B1__MEM_CNTL_ENIMP_B__SHIFT         0x0000001f
singleline_comment|// MC_CHP_IO_CNTL_A1
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_CKA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWN_CKA_MASK              0x00000001L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_CKA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWN_CKA                   0x00000001L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_AA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWN_AA_MASK               0x00000002L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_AA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWN_AA                    0x00000002L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQMA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQMA_MASK             0x00000004L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQMA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQMA                  0x00000004L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQSA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQSA_MASK             0x00000008L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQSA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWN_DQSA                  0x00000008L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_CKA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWP_CKA_MASK              0x00000010L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_CKA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWP_CKA                   0x00000010L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_AA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWP_AA_MASK               0x00000020L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_AA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWP_AA                    0x00000020L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQMA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQMA_MASK             0x00000040L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQMA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQMA                  0x00000040L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQSA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQSA_MASK             0x00000080L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQSA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SLEWP_DQSA                  0x00000080L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_PREAMP_AA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_PREAMP_AA_MASK              0x00000100L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_PREAMP_AA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_PREAMP_AA                   0x00000100L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQMA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQMA_MASK            0x00000200L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQMA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQMA                 0x00000200L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQSA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQSA_MASK            0x00000400L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQSA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_PREAMP_DQSA                 0x00000400L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_IO_MODEA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_IO_MODEA_MASK               0x00003000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_REC_CKA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_REC_CKA_MASK                0x0000c000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_REC_AA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_REC_AA_MASK                 0x00030000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_REC_DQMA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_REC_DQMA_MASK               0x000c0000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_REC_DQSA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_REC_DQSA_MASK               0x00300000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SYNC_PHASEA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SYNC_PHASEA_MASK            0x00400000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SYNC_PHASEA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SYNC_PHASEA                 0x00400000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SYNC_CENTERA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SYNC_CENTERA_MASK           0x00800000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SYNC_CENTERA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SYNC_CENTERA                0x00800000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_SYNC_ENA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_SYNC_ENA_MASK               0x03000000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_CLK_SELA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_CLK_SELA_MASK               0x0c000000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_CLK_INVA_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_CLK_INVA_MASK               0x10000000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_CLK_INVA
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_CLK_INVA                    0x10000000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_DATA_ENIMP_A_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_DATA_ENIMP_A_MASK           0x40000000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_DATA_ENIMP_A
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_DATA_ENIMP_A                0x40000000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_CNTL_ENIMP_A_MASK
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_CNTL_ENIMP_A_MASK           0x80000000L
DECL|macro|MC_CHP_IO_CNTL_A1__MEM_CNTL_ENIMP_A
mdefine_line|#define MC_CHP_IO_CNTL_A1__MEM_CNTL_ENIMP_A                0x80000000L
singleline_comment|// MC_CHP_IO_CNTL_B1
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_CKB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWN_CKB_MASK              0x00000001L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_CKB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWN_CKB                   0x00000001L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_AB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWN_AB_MASK               0x00000002L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_AB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWN_AB                    0x00000002L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQMB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQMB_MASK             0x00000004L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQMB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQMB                  0x00000004L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQSB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQSB_MASK             0x00000008L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQSB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWN_DQSB                  0x00000008L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_CKB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWP_CKB_MASK              0x00000010L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_CKB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWP_CKB                   0x00000010L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_AB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWP_AB_MASK               0x00000020L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_AB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWP_AB                    0x00000020L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQMB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQMB_MASK             0x00000040L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQMB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQMB                  0x00000040L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQSB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQSB_MASK             0x00000080L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQSB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SLEWP_DQSB                  0x00000080L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_PREAMP_AB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_PREAMP_AB_MASK              0x00000100L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_PREAMP_AB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_PREAMP_AB                   0x00000100L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQMB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQMB_MASK            0x00000200L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQMB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQMB                 0x00000200L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQSB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQSB_MASK            0x00000400L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQSB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_PREAMP_DQSB                 0x00000400L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_IO_MODEB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_IO_MODEB_MASK               0x00003000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_REC_CKB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_REC_CKB_MASK                0x0000c000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_REC_AB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_REC_AB_MASK                 0x00030000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_REC_DQMB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_REC_DQMB_MASK               0x000c0000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_REC_DQSB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_REC_DQSB_MASK               0x00300000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SYNC_PHASEB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SYNC_PHASEB_MASK            0x00400000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SYNC_PHASEB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SYNC_PHASEB                 0x00400000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SYNC_CENTERB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SYNC_CENTERB_MASK           0x00800000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SYNC_CENTERB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SYNC_CENTERB                0x00800000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_SYNC_ENB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_SYNC_ENB_MASK               0x03000000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_CLK_SELB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_CLK_SELB_MASK               0x0c000000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_CLK_INVB_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_CLK_INVB_MASK               0x10000000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_CLK_INVB
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_CLK_INVB                    0x10000000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_DATA_ENIMP_B_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_DATA_ENIMP_B_MASK           0x40000000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_DATA_ENIMP_B
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_DATA_ENIMP_B                0x40000000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_CNTL_ENIMP_B_MASK
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_CNTL_ENIMP_B_MASK           0x80000000L
DECL|macro|MC_CHP_IO_CNTL_B1__MEM_CNTL_ENIMP_B
mdefine_line|#define MC_CHP_IO_CNTL_B1__MEM_CNTL_ENIMP_B                0x80000000L
singleline_comment|// MEM_SDRAM_MODE_REG
DECL|macro|MEM_SDRAM_MODE_REG__MEM_MODE_REG_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_MODE_REG_MASK              0x00007fffL
DECL|macro|MEM_SDRAM_MODE_REG__MEM_WR_LATENCY_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_WR_LATENCY_MASK            0x000f0000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_CAS_LATENCY_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_CAS_LATENCY_MASK           0x00700000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_CMD_LATENCY_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_CMD_LATENCY_MASK           0x00800000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_CMD_LATENCY
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_CMD_LATENCY                0x00800000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_STR_LATENCY_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_STR_LATENCY_MASK           0x01000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_STR_LATENCY
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_STR_LATENCY                0x01000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_FALL_OUT_CMD_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_FALL_OUT_CMD_MASK          0x02000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_FALL_OUT_CMD
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_FALL_OUT_CMD               0x02000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_FALL_OUT_DATA_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_FALL_OUT_DATA_MASK         0x04000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_FALL_OUT_DATA
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_FALL_OUT_DATA              0x04000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_FALL_OUT_STR_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_FALL_OUT_STR_MASK          0x08000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_FALL_OUT_STR
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_FALL_OUT_STR               0x08000000L
DECL|macro|MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE_MASK          0x10000000L
DECL|macro|MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE
mdefine_line|#define MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE               0x10000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_DDR_DLL_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_DDR_DLL_MASK               0x20000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_DDR_DLL
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_DDR_DLL                    0x20000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_CFG_TYPE_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_CFG_TYPE_MASK              0x40000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_CFG_TYPE
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_CFG_TYPE                   0x40000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET_MASK
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET_MASK           0x80000000L
DECL|macro|MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET
mdefine_line|#define MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET                0x80000000L
singleline_comment|// MEM_SDRAM_MODE_REG
DECL|macro|MEM_SDRAM_MODE_REG__MEM_MODE_REG__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_MODE_REG__SHIFT            0x00000000
DECL|macro|MEM_SDRAM_MODE_REG__MEM_WR_LATENCY__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_WR_LATENCY__SHIFT          0x00000010
DECL|macro|MEM_SDRAM_MODE_REG__MEM_CAS_LATENCY__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_CAS_LATENCY__SHIFT         0x00000014
DECL|macro|MEM_SDRAM_MODE_REG__MEM_CMD_LATENCY__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_CMD_LATENCY__SHIFT         0x00000017
DECL|macro|MEM_SDRAM_MODE_REG__MEM_STR_LATENCY__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_STR_LATENCY__SHIFT         0x00000018
DECL|macro|MEM_SDRAM_MODE_REG__MEM_FALL_OUT_CMD__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_FALL_OUT_CMD__SHIFT        0x00000019
DECL|macro|MEM_SDRAM_MODE_REG__MEM_FALL_OUT_DATA__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_FALL_OUT_DATA__SHIFT       0x0000001a
DECL|macro|MEM_SDRAM_MODE_REG__MEM_FALL_OUT_STR__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_FALL_OUT_STR__SHIFT        0x0000001b
DECL|macro|MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE__SHIFT        0x0000001c
DECL|macro|MEM_SDRAM_MODE_REG__MEM_DDR_DLL__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_DDR_DLL__SHIFT             0x0000001d
DECL|macro|MEM_SDRAM_MODE_REG__MEM_CFG_TYPE__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_CFG_TYPE__SHIFT            0x0000001e
DECL|macro|MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET__SHIFT
mdefine_line|#define&t;MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET__SHIFT         0x0000001f
singleline_comment|// MEM_REFRESH_CNTL
DECL|macro|MEM_REFRESH_CNTL__MEM_REFRESH_RATE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_REFRESH_RATE_MASK            0x000000ffL
DECL|macro|MEM_REFRESH_CNTL__MEM_REFRESH_DIS_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_REFRESH_DIS_MASK             0x00000100L
DECL|macro|MEM_REFRESH_CNTL__MEM_REFRESH_DIS
mdefine_line|#define MEM_REFRESH_CNTL__MEM_REFRESH_DIS                  0x00000100L
DECL|macro|MEM_REFRESH_CNTL__MEM_DYNAMIC_CKE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_DYNAMIC_CKE_MASK             0x00000200L
DECL|macro|MEM_REFRESH_CNTL__MEM_DYNAMIC_CKE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_DYNAMIC_CKE                  0x00000200L
DECL|macro|MEM_REFRESH_CNTL__MEM_TRFC_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_TRFC_MASK                    0x0000f000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKA0_ENABLE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKA0_ENABLE_MASK            0x00010000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKA0_ENABLE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKA0_ENABLE                 0x00010000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKA0b_ENABLE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKA0b_ENABLE_MASK           0x00020000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKA0b_ENABLE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKA0b_ENABLE                0x00020000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKA1_ENABLE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKA1_ENABLE_MASK            0x00040000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKA1_ENABLE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKA1_ENABLE                 0x00040000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKA1b_ENABLE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKA1b_ENABLE_MASK           0x00080000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKA1b_ENABLE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKA1b_ENABLE                0x00080000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKAFB_ENABLE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKAFB_ENABLE_MASK           0x00100000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKAFB_ENABLE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKAFB_ENABLE                0x00100000L
DECL|macro|MEM_REFRESH_CNTL__DLL_FB_SLCT_CKA_MASK
mdefine_line|#define MEM_REFRESH_CNTL__DLL_FB_SLCT_CKA_MASK             0x00c00000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKB0_ENABLE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKB0_ENABLE_MASK            0x01000000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKB0_ENABLE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKB0_ENABLE                 0x01000000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKB0b_ENABLE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKB0b_ENABLE_MASK           0x02000000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKB0b_ENABLE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKB0b_ENABLE                0x02000000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKB1_ENABLE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKB1_ENABLE_MASK            0x04000000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKB1_ENABLE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKB1_ENABLE                 0x04000000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKB1b_ENABLE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKB1b_ENABLE_MASK           0x08000000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKB1b_ENABLE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKB1b_ENABLE                0x08000000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKBFB_ENABLE_MASK
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKBFB_ENABLE_MASK           0x10000000L
DECL|macro|MEM_REFRESH_CNTL__MEM_CLKBFB_ENABLE
mdefine_line|#define MEM_REFRESH_CNTL__MEM_CLKBFB_ENABLE                0x10000000L
DECL|macro|MEM_REFRESH_CNTL__DLL_FB_SLCT_CKB_MASK
mdefine_line|#define MEM_REFRESH_CNTL__DLL_FB_SLCT_CKB_MASK             0xc0000000L
singleline_comment|// MC_STATUS
DECL|macro|MC_STATUS__MEM_PWRUP_COMPL_A_MASK
mdefine_line|#define MC_STATUS__MEM_PWRUP_COMPL_A_MASK                  0x00000001L
DECL|macro|MC_STATUS__MEM_PWRUP_COMPL_A
mdefine_line|#define MC_STATUS__MEM_PWRUP_COMPL_A                       0x00000001L
DECL|macro|MC_STATUS__MEM_PWRUP_COMPL_B_MASK
mdefine_line|#define MC_STATUS__MEM_PWRUP_COMPL_B_MASK                  0x00000002L
DECL|macro|MC_STATUS__MEM_PWRUP_COMPL_B
mdefine_line|#define MC_STATUS__MEM_PWRUP_COMPL_B                       0x00000002L
DECL|macro|MC_STATUS__MC_IDLE_MASK
mdefine_line|#define MC_STATUS__MC_IDLE_MASK                            0x00000004L
DECL|macro|MC_STATUS__MC_IDLE
mdefine_line|#define MC_STATUS__MC_IDLE                                 0x00000004L
DECL|macro|MC_STATUS__IMP_N_VALUE_R_BACK_MASK
mdefine_line|#define MC_STATUS__IMP_N_VALUE_R_BACK_MASK                 0x00000078L
DECL|macro|MC_STATUS__IMP_P_VALUE_R_BACK_MASK
mdefine_line|#define MC_STATUS__IMP_P_VALUE_R_BACK_MASK                 0x00000780L
DECL|macro|MC_STATUS__TEST_OUT_R_BACK_MASK
mdefine_line|#define MC_STATUS__TEST_OUT_R_BACK_MASK                    0x00000800L
DECL|macro|MC_STATUS__TEST_OUT_R_BACK
mdefine_line|#define MC_STATUS__TEST_OUT_R_BACK                         0x00000800L
DECL|macro|MC_STATUS__DUMMY_OUT_R_BACK_MASK
mdefine_line|#define MC_STATUS__DUMMY_OUT_R_BACK_MASK                   0x00001000L
DECL|macro|MC_STATUS__DUMMY_OUT_R_BACK
mdefine_line|#define MC_STATUS__DUMMY_OUT_R_BACK                        0x00001000L
DECL|macro|MC_STATUS__IMP_N_VALUE_A_R_BACK_MASK
mdefine_line|#define MC_STATUS__IMP_N_VALUE_A_R_BACK_MASK               0x0001e000L
DECL|macro|MC_STATUS__IMP_P_VALUE_A_R_BACK_MASK
mdefine_line|#define MC_STATUS__IMP_P_VALUE_A_R_BACK_MASK               0x001e0000L
DECL|macro|MC_STATUS__IMP_N_VALUE_CK_R_BACK_MASK
mdefine_line|#define MC_STATUS__IMP_N_VALUE_CK_R_BACK_MASK              0x01e00000L
DECL|macro|MC_STATUS__IMP_P_VALUE_CK_R_BACK_MASK
mdefine_line|#define MC_STATUS__IMP_P_VALUE_CK_R_BACK_MASK              0x1e000000L
singleline_comment|// MDLL_CKO
DECL|macro|MDLL_CKO__MCKOA_SLEEP_MASK
mdefine_line|#define MDLL_CKO__MCKOA_SLEEP_MASK                         0x00000001L
DECL|macro|MDLL_CKO__MCKOA_SLEEP
mdefine_line|#define MDLL_CKO__MCKOA_SLEEP                              0x00000001L
DECL|macro|MDLL_CKO__MCKOA_RESET_MASK
mdefine_line|#define MDLL_CKO__MCKOA_RESET_MASK                         0x00000002L
DECL|macro|MDLL_CKO__MCKOA_RESET
mdefine_line|#define MDLL_CKO__MCKOA_RESET                              0x00000002L
DECL|macro|MDLL_CKO__MCKOA_RANGE_MASK
mdefine_line|#define MDLL_CKO__MCKOA_RANGE_MASK                         0x0000000cL
DECL|macro|MDLL_CKO__ERSTA_SOUTSEL_MASK
mdefine_line|#define MDLL_CKO__ERSTA_SOUTSEL_MASK                       0x00000030L
DECL|macro|MDLL_CKO__MCKOA_FB_SEL_MASK
mdefine_line|#define MDLL_CKO__MCKOA_FB_SEL_MASK                        0x000000c0L
DECL|macro|MDLL_CKO__MCKOA_REF_SKEW_MASK
mdefine_line|#define MDLL_CKO__MCKOA_REF_SKEW_MASK                      0x00000700L
DECL|macro|MDLL_CKO__MCKOA_FB_SKEW_MASK
mdefine_line|#define MDLL_CKO__MCKOA_FB_SKEW_MASK                       0x00007000L
DECL|macro|MDLL_CKO__MCKOA_BP_SEL_MASK
mdefine_line|#define MDLL_CKO__MCKOA_BP_SEL_MASK                        0x00008000L
DECL|macro|MDLL_CKO__MCKOA_BP_SEL
mdefine_line|#define MDLL_CKO__MCKOA_BP_SEL                             0x00008000L
DECL|macro|MDLL_CKO__MCKOB_SLEEP_MASK
mdefine_line|#define MDLL_CKO__MCKOB_SLEEP_MASK                         0x00010000L
DECL|macro|MDLL_CKO__MCKOB_SLEEP
mdefine_line|#define MDLL_CKO__MCKOB_SLEEP                              0x00010000L
DECL|macro|MDLL_CKO__MCKOB_RESET_MASK
mdefine_line|#define MDLL_CKO__MCKOB_RESET_MASK                         0x00020000L
DECL|macro|MDLL_CKO__MCKOB_RESET
mdefine_line|#define MDLL_CKO__MCKOB_RESET                              0x00020000L
DECL|macro|MDLL_CKO__MCKOB_RANGE_MASK
mdefine_line|#define MDLL_CKO__MCKOB_RANGE_MASK                         0x000c0000L
DECL|macro|MDLL_CKO__ERSTB_SOUTSEL_MASK
mdefine_line|#define MDLL_CKO__ERSTB_SOUTSEL_MASK                       0x00300000L
DECL|macro|MDLL_CKO__MCKOB_FB_SEL_MASK
mdefine_line|#define MDLL_CKO__MCKOB_FB_SEL_MASK                        0x00c00000L
DECL|macro|MDLL_CKO__MCKOB_REF_SKEW_MASK
mdefine_line|#define MDLL_CKO__MCKOB_REF_SKEW_MASK                      0x07000000L
DECL|macro|MDLL_CKO__MCKOB_FB_SKEW_MASK
mdefine_line|#define MDLL_CKO__MCKOB_FB_SKEW_MASK                       0x70000000L
DECL|macro|MDLL_CKO__MCKOB_BP_SEL_MASK
mdefine_line|#define MDLL_CKO__MCKOB_BP_SEL_MASK                        0x80000000L
DECL|macro|MDLL_CKO__MCKOB_BP_SEL
mdefine_line|#define MDLL_CKO__MCKOB_BP_SEL                             0x80000000L
singleline_comment|// MDLL_RDCKA
DECL|macro|MDLL_RDCKA__MRDCKA0_SLEEP_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA0_SLEEP_MASK                     0x00000001L
DECL|macro|MDLL_RDCKA__MRDCKA0_SLEEP
mdefine_line|#define MDLL_RDCKA__MRDCKA0_SLEEP                          0x00000001L
DECL|macro|MDLL_RDCKA__MRDCKA0_RESET_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA0_RESET_MASK                     0x00000002L
DECL|macro|MDLL_RDCKA__MRDCKA0_RESET
mdefine_line|#define MDLL_RDCKA__MRDCKA0_RESET                          0x00000002L
DECL|macro|MDLL_RDCKA__MRDCKA0_RANGE_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA0_RANGE_MASK                     0x0000000cL
DECL|macro|MDLL_RDCKA__MRDCKA0_REF_SEL_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA0_REF_SEL_MASK                   0x00000030L
DECL|macro|MDLL_RDCKA__MRDCKA0_FB_SEL_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA0_FB_SEL_MASK                    0x000000c0L
DECL|macro|MDLL_RDCKA__MRDCKA0_REF_SKEW_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA0_REF_SKEW_MASK                  0x00000700L
DECL|macro|MDLL_RDCKA__MRDCKA0_SINSEL_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA0_SINSEL_MASK                    0x00000800L
DECL|macro|MDLL_RDCKA__MRDCKA0_SINSEL
mdefine_line|#define MDLL_RDCKA__MRDCKA0_SINSEL                         0x00000800L
DECL|macro|MDLL_RDCKA__MRDCKA0_FB_SKEW_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA0_FB_SKEW_MASK                   0x00007000L
DECL|macro|MDLL_RDCKA__MRDCKA0_BP_SEL_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA0_BP_SEL_MASK                    0x00008000L
DECL|macro|MDLL_RDCKA__MRDCKA0_BP_SEL
mdefine_line|#define MDLL_RDCKA__MRDCKA0_BP_SEL                         0x00008000L
DECL|macro|MDLL_RDCKA__MRDCKA1_SLEEP_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA1_SLEEP_MASK                     0x00010000L
DECL|macro|MDLL_RDCKA__MRDCKA1_SLEEP
mdefine_line|#define MDLL_RDCKA__MRDCKA1_SLEEP                          0x00010000L
DECL|macro|MDLL_RDCKA__MRDCKA1_RESET_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA1_RESET_MASK                     0x00020000L
DECL|macro|MDLL_RDCKA__MRDCKA1_RESET
mdefine_line|#define MDLL_RDCKA__MRDCKA1_RESET                          0x00020000L
DECL|macro|MDLL_RDCKA__MRDCKA1_RANGE_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA1_RANGE_MASK                     0x000c0000L
DECL|macro|MDLL_RDCKA__MRDCKA1_REF_SEL_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA1_REF_SEL_MASK                   0x00300000L
DECL|macro|MDLL_RDCKA__MRDCKA1_FB_SEL_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA1_FB_SEL_MASK                    0x00c00000L
DECL|macro|MDLL_RDCKA__MRDCKA1_REF_SKEW_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA1_REF_SKEW_MASK                  0x07000000L
DECL|macro|MDLL_RDCKA__MRDCKA1_SINSEL_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA1_SINSEL_MASK                    0x08000000L
DECL|macro|MDLL_RDCKA__MRDCKA1_SINSEL
mdefine_line|#define MDLL_RDCKA__MRDCKA1_SINSEL                         0x08000000L
DECL|macro|MDLL_RDCKA__MRDCKA1_FB_SKEW_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA1_FB_SKEW_MASK                   0x70000000L
DECL|macro|MDLL_RDCKA__MRDCKA1_BP_SEL_MASK
mdefine_line|#define MDLL_RDCKA__MRDCKA1_BP_SEL_MASK                    0x80000000L
DECL|macro|MDLL_RDCKA__MRDCKA1_BP_SEL
mdefine_line|#define MDLL_RDCKA__MRDCKA1_BP_SEL                         0x80000000L
singleline_comment|// MDLL_RDCKB
DECL|macro|MDLL_RDCKB__MRDCKB0_SLEEP_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB0_SLEEP_MASK                     0x00000001L
DECL|macro|MDLL_RDCKB__MRDCKB0_SLEEP
mdefine_line|#define MDLL_RDCKB__MRDCKB0_SLEEP                          0x00000001L
DECL|macro|MDLL_RDCKB__MRDCKB0_RESET_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB0_RESET_MASK                     0x00000002L
DECL|macro|MDLL_RDCKB__MRDCKB0_RESET
mdefine_line|#define MDLL_RDCKB__MRDCKB0_RESET                          0x00000002L
DECL|macro|MDLL_RDCKB__MRDCKB0_RANGE_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB0_RANGE_MASK                     0x0000000cL
DECL|macro|MDLL_RDCKB__MRDCKB0_REF_SEL_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB0_REF_SEL_MASK                   0x00000030L
DECL|macro|MDLL_RDCKB__MRDCKB0_FB_SEL_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB0_FB_SEL_MASK                    0x000000c0L
DECL|macro|MDLL_RDCKB__MRDCKB0_REF_SKEW_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB0_REF_SKEW_MASK                  0x00000700L
DECL|macro|MDLL_RDCKB__MRDCKB0_SINSEL_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB0_SINSEL_MASK                    0x00000800L
DECL|macro|MDLL_RDCKB__MRDCKB0_SINSEL
mdefine_line|#define MDLL_RDCKB__MRDCKB0_SINSEL                         0x00000800L
DECL|macro|MDLL_RDCKB__MRDCKB0_FB_SKEW_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB0_FB_SKEW_MASK                   0x00007000L
DECL|macro|MDLL_RDCKB__MRDCKB0_BP_SEL_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB0_BP_SEL_MASK                    0x00008000L
DECL|macro|MDLL_RDCKB__MRDCKB0_BP_SEL
mdefine_line|#define MDLL_RDCKB__MRDCKB0_BP_SEL                         0x00008000L
DECL|macro|MDLL_RDCKB__MRDCKB1_SLEEP_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB1_SLEEP_MASK                     0x00010000L
DECL|macro|MDLL_RDCKB__MRDCKB1_SLEEP
mdefine_line|#define MDLL_RDCKB__MRDCKB1_SLEEP                          0x00010000L
DECL|macro|MDLL_RDCKB__MRDCKB1_RESET_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB1_RESET_MASK                     0x00020000L
DECL|macro|MDLL_RDCKB__MRDCKB1_RESET
mdefine_line|#define MDLL_RDCKB__MRDCKB1_RESET                          0x00020000L
DECL|macro|MDLL_RDCKB__MRDCKB1_RANGE_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB1_RANGE_MASK                     0x000c0000L
DECL|macro|MDLL_RDCKB__MRDCKB1_REF_SEL_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB1_REF_SEL_MASK                   0x00300000L
DECL|macro|MDLL_RDCKB__MRDCKB1_FB_SEL_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB1_FB_SEL_MASK                    0x00c00000L
DECL|macro|MDLL_RDCKB__MRDCKB1_REF_SKEW_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB1_REF_SKEW_MASK                  0x07000000L
DECL|macro|MDLL_RDCKB__MRDCKB1_SINSEL_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB1_SINSEL_MASK                    0x08000000L
DECL|macro|MDLL_RDCKB__MRDCKB1_SINSEL
mdefine_line|#define MDLL_RDCKB__MRDCKB1_SINSEL                         0x08000000L
DECL|macro|MDLL_RDCKB__MRDCKB1_FB_SKEW_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB1_FB_SKEW_MASK                   0x70000000L
DECL|macro|MDLL_RDCKB__MRDCKB1_BP_SEL_MASK
mdefine_line|#define MDLL_RDCKB__MRDCKB1_BP_SEL_MASK                    0x80000000L
DECL|macro|MDLL_RDCKB__MRDCKB1_BP_SEL
mdefine_line|#define MDLL_RDCKB__MRDCKB1_BP_SEL                         0x80000000L
DECL|macro|MDLL_R300_RDCK__MRDCKA_SLEEP
mdefine_line|#define MDLL_R300_RDCK__MRDCKA_SLEEP                       0x00000001L
DECL|macro|MDLL_R300_RDCK__MRDCKA_RESET
mdefine_line|#define MDLL_R300_RDCK__MRDCKA_RESET                       0x00000002L
DECL|macro|MDLL_R300_RDCK__MRDCKB_SLEEP
mdefine_line|#define MDLL_R300_RDCK__MRDCKB_SLEEP                       0x00000004L
DECL|macro|MDLL_R300_RDCK__MRDCKB_RESET
mdefine_line|#define MDLL_R300_RDCK__MRDCKB_RESET                       0x00000008L
DECL|macro|MDLL_R300_RDCK__MRDCKC_SLEEP
mdefine_line|#define MDLL_R300_RDCK__MRDCKC_SLEEP                       0x00000010L
DECL|macro|MDLL_R300_RDCK__MRDCKC_RESET
mdefine_line|#define MDLL_R300_RDCK__MRDCKC_RESET                       0x00000020L
DECL|macro|MDLL_R300_RDCK__MRDCKD_SLEEP
mdefine_line|#define MDLL_R300_RDCK__MRDCKD_SLEEP                       0x00000040L
DECL|macro|MDLL_R300_RDCK__MRDCKD_RESET
mdefine_line|#define MDLL_R300_RDCK__MRDCKD_RESET                       0x00000080L
DECL|macro|pllCLK_PIN_CNTL
mdefine_line|#define pllCLK_PIN_CNTL                             0x0001
DECL|macro|pllPPLL_CNTL
mdefine_line|#define pllPPLL_CNTL                                0x0002
DECL|macro|pllPPLL_REF_DIV
mdefine_line|#define pllPPLL_REF_DIV                             0x0003
DECL|macro|pllPPLL_DIV_0
mdefine_line|#define pllPPLL_DIV_0                               0x0004
DECL|macro|pllPPLL_DIV_1
mdefine_line|#define pllPPLL_DIV_1                               0x0005
DECL|macro|pllPPLL_DIV_2
mdefine_line|#define pllPPLL_DIV_2                               0x0006
DECL|macro|pllPPLL_DIV_3
mdefine_line|#define pllPPLL_DIV_3                               0x0007
DECL|macro|pllVCLK_ECP_CNTL
mdefine_line|#define pllVCLK_ECP_CNTL                            0x0008
DECL|macro|pllHTOTAL_CNTL
mdefine_line|#define pllHTOTAL_CNTL                              0x0009
DECL|macro|pllM_SPLL_REF_FB_DIV
mdefine_line|#define pllM_SPLL_REF_FB_DIV                        0x000A
DECL|macro|pllAGP_PLL_CNTL
mdefine_line|#define pllAGP_PLL_CNTL                             0x000B
DECL|macro|pllSPLL_CNTL
mdefine_line|#define pllSPLL_CNTL                                0x000C
DECL|macro|pllSCLK_CNTL
mdefine_line|#define pllSCLK_CNTL                                0x000D
DECL|macro|pllMPLL_CNTL
mdefine_line|#define pllMPLL_CNTL                                0x000E
DECL|macro|pllMDLL_CKO
mdefine_line|#define pllMDLL_CKO                                 0x000F
DECL|macro|pllMDLL_RDCKA
mdefine_line|#define pllMDLL_RDCKA                               0x0010
DECL|macro|pllMDLL_RDCKB
mdefine_line|#define pllMDLL_RDCKB                               0x0011
DECL|macro|pllMCLK_CNTL
mdefine_line|#define pllMCLK_CNTL                                0x0012
DECL|macro|pllPLL_TEST_CNTL
mdefine_line|#define pllPLL_TEST_CNTL                            0x0013
DECL|macro|pllCLK_PWRMGT_CNTL
mdefine_line|#define pllCLK_PWRMGT_CNTL                          0x0014
DECL|macro|pllPLL_PWRMGT_CNTL
mdefine_line|#define pllPLL_PWRMGT_CNTL                          0x0015
DECL|macro|pllCG_TEST_MACRO_RW_WRITE
mdefine_line|#define pllCG_TEST_MACRO_RW_WRITE                   0x0016
DECL|macro|pllCG_TEST_MACRO_RW_READ
mdefine_line|#define pllCG_TEST_MACRO_RW_READ                    0x0017
DECL|macro|pllCG_TEST_MACRO_RW_DATA
mdefine_line|#define pllCG_TEST_MACRO_RW_DATA                    0x0018
DECL|macro|pllCG_TEST_MACRO_RW_CNTL
mdefine_line|#define pllCG_TEST_MACRO_RW_CNTL                    0x0019
DECL|macro|pllDISP_TEST_MACRO_RW_WRITE
mdefine_line|#define pllDISP_TEST_MACRO_RW_WRITE                 0x001A
DECL|macro|pllDISP_TEST_MACRO_RW_READ
mdefine_line|#define pllDISP_TEST_MACRO_RW_READ                  0x001B
DECL|macro|pllDISP_TEST_MACRO_RW_DATA
mdefine_line|#define pllDISP_TEST_MACRO_RW_DATA                  0x001C
DECL|macro|pllDISP_TEST_MACRO_RW_CNTL
mdefine_line|#define pllDISP_TEST_MACRO_RW_CNTL                  0x001D
DECL|macro|pllSCLK_CNTL2
mdefine_line|#define pllSCLK_CNTL2                               0x001E
DECL|macro|pllMCLK_MISC
mdefine_line|#define pllMCLK_MISC                                0x001F
DECL|macro|pllTV_PLL_FINE_CNTL
mdefine_line|#define pllTV_PLL_FINE_CNTL                         0x0020
DECL|macro|pllTV_PLL_CNTL
mdefine_line|#define pllTV_PLL_CNTL                              0x0021
DECL|macro|pllTV_PLL_CNTL1
mdefine_line|#define pllTV_PLL_CNTL1                             0x0022
DECL|macro|pllTV_DTO_INCREMENTS
mdefine_line|#define pllTV_DTO_INCREMENTS                        0x0023
DECL|macro|pllSPLL_AUX_CNTL
mdefine_line|#define pllSPLL_AUX_CNTL                            0x0024
DECL|macro|pllMPLL_AUX_CNTL
mdefine_line|#define pllMPLL_AUX_CNTL                            0x0025
DECL|macro|pllP2PLL_CNTL
mdefine_line|#define pllP2PLL_CNTL                               0x002A
DECL|macro|pllP2PLL_REF_DIV
mdefine_line|#define pllP2PLL_REF_DIV                            0x002B
DECL|macro|pllP2PLL_DIV_0
mdefine_line|#define pllP2PLL_DIV_0                              0x002C
DECL|macro|pllPIXCLKS_CNTL
mdefine_line|#define pllPIXCLKS_CNTL                             0x002D
DECL|macro|pllHTOTAL2_CNTL
mdefine_line|#define pllHTOTAL2_CNTL                             0x002E
DECL|macro|pllSSPLL_CNTL
mdefine_line|#define pllSSPLL_CNTL                               0x0030
DECL|macro|pllSSPLL_REF_DIV
mdefine_line|#define pllSSPLL_REF_DIV                            0x0031
DECL|macro|pllSSPLL_DIV_0
mdefine_line|#define pllSSPLL_DIV_0                              0x0032
DECL|macro|pllSS_INT_CNTL
mdefine_line|#define pllSS_INT_CNTL                              0x0033
DECL|macro|pllSS_TST_CNTL
mdefine_line|#define pllSS_TST_CNTL                              0x0034
DECL|macro|pllSCLK_MORE_CNTL
mdefine_line|#define pllSCLK_MORE_CNTL                           0x0035
DECL|macro|ixMC_PERF_CNTL
mdefine_line|#define ixMC_PERF_CNTL                             0x0000
DECL|macro|ixMC_PERF_SEL
mdefine_line|#define ixMC_PERF_SEL                              0x0001
DECL|macro|ixMC_PERF_REGION_0
mdefine_line|#define ixMC_PERF_REGION_0                         0x0002
DECL|macro|ixMC_PERF_REGION_1
mdefine_line|#define ixMC_PERF_REGION_1                         0x0003
DECL|macro|ixMC_PERF_COUNT_0
mdefine_line|#define ixMC_PERF_COUNT_0                          0x0004
DECL|macro|ixMC_PERF_COUNT_1
mdefine_line|#define ixMC_PERF_COUNT_1                          0x0005
DECL|macro|ixMC_PERF_COUNT_2
mdefine_line|#define ixMC_PERF_COUNT_2                          0x0006
DECL|macro|ixMC_PERF_COUNT_3
mdefine_line|#define ixMC_PERF_COUNT_3                          0x0007
DECL|macro|ixMC_PERF_COUNT_MEMCH_A
mdefine_line|#define ixMC_PERF_COUNT_MEMCH_A                    0x0008
DECL|macro|ixMC_PERF_COUNT_MEMCH_B
mdefine_line|#define ixMC_PERF_COUNT_MEMCH_B                    0x0009
DECL|macro|ixMC_IMP_CNTL
mdefine_line|#define ixMC_IMP_CNTL                              0x000A
DECL|macro|ixMC_CHP_IO_CNTL_A0
mdefine_line|#define ixMC_CHP_IO_CNTL_A0                        0x000B
DECL|macro|ixMC_CHP_IO_CNTL_A1
mdefine_line|#define ixMC_CHP_IO_CNTL_A1                        0x000C
DECL|macro|ixMC_CHP_IO_CNTL_B0
mdefine_line|#define ixMC_CHP_IO_CNTL_B0                        0x000D
DECL|macro|ixMC_CHP_IO_CNTL_B1
mdefine_line|#define ixMC_CHP_IO_CNTL_B1                        0x000E
DECL|macro|ixMC_IMP_CNTL_0
mdefine_line|#define ixMC_IMP_CNTL_0                            0x000F
DECL|macro|ixTC_MISMATCH_1
mdefine_line|#define ixTC_MISMATCH_1                            0x0010
DECL|macro|ixTC_MISMATCH_2
mdefine_line|#define ixTC_MISMATCH_2                            0x0011
DECL|macro|ixMC_BIST_CTRL
mdefine_line|#define ixMC_BIST_CTRL                             0x0012
DECL|macro|ixREG_COLLAR_WRITE
mdefine_line|#define ixREG_COLLAR_WRITE                         0x0013
DECL|macro|ixREG_COLLAR_READ
mdefine_line|#define ixREG_COLLAR_READ                          0x0014
DECL|macro|ixR300_MC_IMP_CNTL
mdefine_line|#define ixR300_MC_IMP_CNTL                         0x0018
DECL|macro|ixR300_MC_CHP_IO_CNTL_A0
mdefine_line|#define ixR300_MC_CHP_IO_CNTL_A0                   0x0019
DECL|macro|ixR300_MC_CHP_IO_CNTL_A1
mdefine_line|#define ixR300_MC_CHP_IO_CNTL_A1                   0x001a
DECL|macro|ixR300_MC_CHP_IO_CNTL_B0
mdefine_line|#define ixR300_MC_CHP_IO_CNTL_B0                   0x001b
DECL|macro|ixR300_MC_CHP_IO_CNTL_B1
mdefine_line|#define ixR300_MC_CHP_IO_CNTL_B1                   0x001c
DECL|macro|ixR300_MC_CHP_IO_CNTL_C0
mdefine_line|#define ixR300_MC_CHP_IO_CNTL_C0                   0x001d
DECL|macro|ixR300_MC_CHP_IO_CNTL_C1
mdefine_line|#define ixR300_MC_CHP_IO_CNTL_C1                   0x001e
DECL|macro|ixR300_MC_CHP_IO_CNTL_D0
mdefine_line|#define ixR300_MC_CHP_IO_CNTL_D0                   0x001f
DECL|macro|ixR300_MC_CHP_IO_CNTL_D1
mdefine_line|#define ixR300_MC_CHP_IO_CNTL_D1                   0x0020
DECL|macro|ixR300_MC_IMP_CNTL_0
mdefine_line|#define ixR300_MC_IMP_CNTL_0                       0x0021
DECL|macro|ixR300_MC_ELPIDA_CNTL
mdefine_line|#define ixR300_MC_ELPIDA_CNTL                      0x0022
DECL|macro|ixR300_MC_CHP_IO_OE_CNTL_CD
mdefine_line|#define ixR300_MC_CHP_IO_OE_CNTL_CD                0x0023
DECL|macro|ixR300_MC_READ_CNTL_CD
mdefine_line|#define ixR300_MC_READ_CNTL_CD                     0x0024
DECL|macro|ixR300_MC_MC_INIT_WR_LAT_TIMER
mdefine_line|#define ixR300_MC_MC_INIT_WR_LAT_TIMER             0x0025
DECL|macro|ixR300_MC_DEBUG_CNTL
mdefine_line|#define ixR300_MC_DEBUG_CNTL                       0x0026
DECL|macro|ixR300_MC_BIST_CNTL_0
mdefine_line|#define ixR300_MC_BIST_CNTL_0                      0x0028
DECL|macro|ixR300_MC_BIST_CNTL_1
mdefine_line|#define ixR300_MC_BIST_CNTL_1                      0x0029
DECL|macro|ixR300_MC_BIST_CNTL_2
mdefine_line|#define ixR300_MC_BIST_CNTL_2                      0x002a
DECL|macro|ixR300_MC_BIST_CNTL_3
mdefine_line|#define ixR300_MC_BIST_CNTL_3                      0x002b
DECL|macro|ixR300_MC_BIST_CNTL_4
mdefine_line|#define ixR300_MC_BIST_CNTL_4                      0x002c
DECL|macro|ixR300_MC_BIST_CNTL_5
mdefine_line|#define ixR300_MC_BIST_CNTL_5                      0x002d
DECL|macro|ixR300_MC_IMP_STATUS
mdefine_line|#define ixR300_MC_IMP_STATUS                       0x002e
DECL|macro|ixR300_MC_DLL_CNTL
mdefine_line|#define ixR300_MC_DLL_CNTL                         0x002f
DECL|macro|NB_TOM
mdefine_line|#define NB_TOM                                     0x15C
macro_line|#endif&t;/* _RADEON_H */
eof
