multiline_comment|/* ibmmpeg2.h - IBM MPEGCD21 definitions */
macro_line|#ifndef __IBM_MPEG2__
DECL|macro|__IBM_MPEG2__
mdefine_line|#define __IBM_MPEG2__
multiline_comment|/* Define all MPEG Decoder registers */
multiline_comment|/* Chip Control and Status */
DECL|macro|IBM_MP2_CHIP_CONTROL
mdefine_line|#define IBM_MP2_CHIP_CONTROL&t;0x200*2
DECL|macro|IBM_MP2_CHIP_MODE
mdefine_line|#define IBM_MP2_CHIP_MODE&t;0x201*2
multiline_comment|/* Timer Control and Status */
DECL|macro|IBM_MP2_SYNC_STC2
mdefine_line|#define IBM_MP2_SYNC_STC2&t;0x202*2
DECL|macro|IBM_MP2_SYNC_STC1
mdefine_line|#define IBM_MP2_SYNC_STC1&t;0x203*2
DECL|macro|IBM_MP2_SYNC_STC0
mdefine_line|#define IBM_MP2_SYNC_STC0&t;0x204*2
DECL|macro|IBM_MP2_SYNC_PTS2
mdefine_line|#define IBM_MP2_SYNC_PTS2&t;0x205*2
DECL|macro|IBM_MP2_SYNC_PTS1
mdefine_line|#define IBM_MP2_SYNC_PTS1&t;0x206*2
DECL|macro|IBM_MP2_SYNC_PTS0
mdefine_line|#define IBM_MP2_SYNC_PTS0&t;0x207*2
multiline_comment|/* Video FIFO Control */
DECL|macro|IBM_MP2_FIFO
mdefine_line|#define IBM_MP2_FIFO&t;&t;0x208*2
DECL|macro|IBM_MP2_FIFOW
mdefine_line|#define IBM_MP2_FIFOW&t;&t;0x100*2
DECL|macro|IBM_MP2_FIFO_STAT
mdefine_line|#define IBM_MP2_FIFO_STAT&t;0x209*2
DECL|macro|IBM_MP2_RB_THRESHOLD
mdefine_line|#define IBM_MP2_RB_THRESHOLD&t;0x22b*2
multiline_comment|/* Command buffer */
DECL|macro|IBM_MP2_COMMAND
mdefine_line|#define IBM_MP2_COMMAND&t;&t;0x20a*2
DECL|macro|IBM_MP2_CMD_DATA
mdefine_line|#define IBM_MP2_CMD_DATA&t;0x20b*2
DECL|macro|IBM_MP2_CMD_STAT
mdefine_line|#define IBM_MP2_CMD_STAT&t;0x20c*2
DECL|macro|IBM_MP2_CMD_ADDR
mdefine_line|#define IBM_MP2_CMD_ADDR&t;0x20d*2
multiline_comment|/* Internal Processor Control and Status */
DECL|macro|IBM_MP2_PROC_IADDR
mdefine_line|#define IBM_MP2_PROC_IADDR&t;0x20e*2
DECL|macro|IBM_MP2_PROC_IDATA
mdefine_line|#define IBM_MP2_PROC_IDATA&t;0x20f*2
DECL|macro|IBM_MP2_WR_PROT
mdefine_line|#define IBM_MP2_WR_PROT&t;&t;0x235*2
multiline_comment|/* DRAM Access */
DECL|macro|IBM_MP2_DRAM_ADDR
mdefine_line|#define IBM_MP2_DRAM_ADDR&t;0x210*2
DECL|macro|IBM_MP2_DRAM_DATA
mdefine_line|#define IBM_MP2_DRAM_DATA&t;0x212*2
DECL|macro|IBM_MP2_DRAM_CMD_STAT
mdefine_line|#define IBM_MP2_DRAM_CMD_STAT&t;0x213*2
DECL|macro|IBM_MP2_BLOCK_SIZE
mdefine_line|#define IBM_MP2_BLOCK_SIZE&t;0x23b*2
DECL|macro|IBM_MP2_SRC_ADDR
mdefine_line|#define IBM_MP2_SRC_ADDR&t;0x23c*2
multiline_comment|/* Onscreen Display */
DECL|macro|IBM_MP2_OSD_ADDR
mdefine_line|#define IBM_MP2_OSD_ADDR&t;0x214*2
DECL|macro|IBM_MP2_OSD_DATA
mdefine_line|#define IBM_MP2_OSD_DATA&t;0x215*2
DECL|macro|IBM_MP2_OSD_MODE
mdefine_line|#define IBM_MP2_OSD_MODE&t;0x217*2
DECL|macro|IBM_MP2_OSD_LINK_ADDR
mdefine_line|#define IBM_MP2_OSD_LINK_ADDR&t;0x229*2
DECL|macro|IBM_MP2_OSD_SIZE
mdefine_line|#define IBM_MP2_OSD_SIZE&t;0x22a*2
multiline_comment|/* Interrupt Control */
DECL|macro|IBM_MP2_HOST_INT
mdefine_line|#define IBM_MP2_HOST_INT&t;0x218*2
DECL|macro|IBM_MP2_MASK0
mdefine_line|#define IBM_MP2_MASK0&t;&t;0x219*2
DECL|macro|IBM_MP2_HOST_INT1
mdefine_line|#define IBM_MP2_HOST_INT1&t;0x23e*2
DECL|macro|IBM_MP2_MASK1
mdefine_line|#define IBM_MP2_MASK1&t;&t;0x23f*2
multiline_comment|/* Audio Control */
DECL|macro|IBM_MP2_AUD_IADDR
mdefine_line|#define IBM_MP2_AUD_IADDR&t;0x21a*2
DECL|macro|IBM_MP2_AUD_IDATA
mdefine_line|#define IBM_MP2_AUD_IDATA&t;0x21b*2
DECL|macro|IBM_MP2_AUD_FIFO
mdefine_line|#define IBM_MP2_AUD_FIFO&t;0x21c*2
DECL|macro|IBM_MP2_AUD_FIFOW
mdefine_line|#define IBM_MP2_AUD_FIFOW&t;0x101*2
DECL|macro|IBM_MP2_AUD_CTL
mdefine_line|#define IBM_MP2_AUD_CTL&t;&t;0x21d*2
DECL|macro|IBM_MP2_BEEP_CTL
mdefine_line|#define IBM_MP2_BEEP_CTL&t;0x21e*2
DECL|macro|IBM_MP2_FRNT_ATTEN
mdefine_line|#define IBM_MP2_FRNT_ATTEN&t;0x22d*2
multiline_comment|/* Display Control */
DECL|macro|IBM_MP2_DISP_MODE
mdefine_line|#define IBM_MP2_DISP_MODE&t;0x220*2
DECL|macro|IBM_MP2_DISP_DLY
mdefine_line|#define IBM_MP2_DISP_DLY&t;0x221*2
DECL|macro|IBM_MP2_VBI_CTL
mdefine_line|#define IBM_MP2_VBI_CTL&t;&t;0x222*2
DECL|macro|IBM_MP2_DISP_LBOR
mdefine_line|#define IBM_MP2_DISP_LBOR&t;0x223*2
DECL|macro|IBM_MP2_DISP_TBOR
mdefine_line|#define IBM_MP2_DISP_TBOR&t;0x224*2
multiline_comment|/* Polarity Control */
DECL|macro|IBM_MP2_INFC_CTL
mdefine_line|#define IBM_MP2_INFC_CTL&t;0x22c*2
multiline_comment|/* control commands */
DECL|macro|IBM_MP2_PLAY
mdefine_line|#define IBM_MP2_PLAY&t;&t;0
DECL|macro|IBM_MP2_PAUSE
mdefine_line|#define IBM_MP2_PAUSE&t;&t;1
DECL|macro|IBM_MP2_SINGLE_FRAME
mdefine_line|#define IBM_MP2_SINGLE_FRAME&t;2
DECL|macro|IBM_MP2_FAST_FORWARD
mdefine_line|#define IBM_MP2_FAST_FORWARD&t;3
DECL|macro|IBM_MP2_SLOW_MOTION
mdefine_line|#define IBM_MP2_SLOW_MOTION&t;4
DECL|macro|IBM_MP2_IMED_NORM_PLAY
mdefine_line|#define IBM_MP2_IMED_NORM_PLAY&t;5
DECL|macro|IBM_MP2_RESET_WINDOW
mdefine_line|#define IBM_MP2_RESET_WINDOW&t;6
DECL|macro|IBM_MP2_FREEZE_FRAME
mdefine_line|#define IBM_MP2_FREEZE_FRAME&t;7
DECL|macro|IBM_MP2_RESET_VID_RATE
mdefine_line|#define IBM_MP2_RESET_VID_RATE&t;8
DECL|macro|IBM_MP2_CONFIG_DECODER
mdefine_line|#define IBM_MP2_CONFIG_DECODER&t;9
DECL|macro|IBM_MP2_CHANNEL_SWITCH
mdefine_line|#define IBM_MP2_CHANNEL_SWITCH&t;10
DECL|macro|IBM_MP2_RESET_AUD_RATE
mdefine_line|#define IBM_MP2_RESET_AUD_RATE&t;11
DECL|macro|IBM_MP2_PRE_OP_CHN_SW
mdefine_line|#define IBM_MP2_PRE_OP_CHN_SW&t;12
DECL|macro|IBM_MP2_SET_STILL_MODE
mdefine_line|#define IBM_MP2_SET_STILL_MODE&t;14
multiline_comment|/* Define Xilinx FPGA Internal Registers */
multiline_comment|/* general control register 0 */
DECL|macro|XILINX_CTL0
mdefine_line|#define XILINX_CTL0&t;&t;0x600
multiline_comment|/* genlock delay resister 1 */
DECL|macro|XILINX_GLDELAY
mdefine_line|#define XILINX_GLDELAY&t;&t;0x602
multiline_comment|/* send 16 bits to CS3310 port */
DECL|macro|XILINX_CS3310
mdefine_line|#define XILINX_CS3310&t;&t;0x604
multiline_comment|/* send 16 bits to CS3310 and complete */
DECL|macro|XILINX_CS3310_CMPLT
mdefine_line|#define XILINX_CS3310_CMPLT&t;0x60c
multiline_comment|/* pulse width modulator control */
DECL|macro|XILINX_PWM
mdefine_line|#define XILINX_PWM&t;&t;0x606
macro_line|#endif
eof
