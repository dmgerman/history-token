macro_line|#ifndef __INCLUDED_SAA7146__
DECL|macro|__INCLUDED_SAA7146__
mdefine_line|#define __INCLUDED_SAA7146__
DECL|struct|saa7146_video_dma
r_struct
id|saa7146_video_dma
(brace
DECL|member|base_odd
id|u32
id|base_odd
suffix:semicolon
DECL|member|base_even
id|u32
id|base_even
suffix:semicolon
DECL|member|prot_addr
id|u32
id|prot_addr
suffix:semicolon
DECL|member|pitch
id|u32
id|pitch
suffix:semicolon
DECL|member|base_page
id|u32
id|base_page
suffix:semicolon
DECL|member|num_line_byte
id|u32
id|num_line_byte
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|saa7146_debi_transfer
r_struct
id|saa7146_debi_transfer
(brace
DECL|member|timeout
id|u8
id|timeout
suffix:semicolon
multiline_comment|/* have a look at the specs for reasonable values, p.110 ff */
DECL|member|swap
id|u8
id|swap
suffix:semicolon
DECL|member|slave16
id|u8
id|slave16
suffix:semicolon
DECL|member|increment
id|u8
id|increment
suffix:semicolon
multiline_comment|/* only for block transfers */
DECL|member|intel
id|u8
id|intel
suffix:semicolon
DECL|member|tien
id|u8
id|tien
suffix:semicolon
DECL|member|address
id|u16
id|address
suffix:semicolon
DECL|member|num_bytes
id|u16
id|num_bytes
suffix:semicolon
DECL|member|direction
id|u8
id|direction
suffix:semicolon
DECL|member|mem
id|u32
id|mem
suffix:semicolon
multiline_comment|/* either a &quot;pointer&quot; (actually the physical address) of the debi-memory (block-transfer, use virt_to_bus to supply it) or 4 bytes (as one u32-value) for immediate transfer */
)brace
suffix:semicolon
DECL|struct|saa7146_modes_constants
r_struct
id|saa7146_modes_constants
(brace
DECL|member|v_offset
id|u8
id|v_offset
suffix:semicolon
DECL|member|v_field
id|u16
id|v_field
suffix:semicolon
DECL|member|v_calc
id|u16
id|v_calc
suffix:semicolon
DECL|member|h_offset
id|u8
id|h_offset
suffix:semicolon
DECL|member|h_pixels
id|u16
id|h_pixels
suffix:semicolon
DECL|member|h_calc
id|u16
id|h_calc
suffix:semicolon
DECL|member|v_max_out
id|u16
id|v_max_out
suffix:semicolon
DECL|member|h_max_out
id|u16
id|h_max_out
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|saa7146_mmap_struct
r_struct
id|saa7146_mmap_struct
(brace
DECL|member|adr
r_const
r_char
op_star
id|adr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SAA7146_PAL
mdefine_line|#define SAA7146_PAL&t;0
DECL|macro|SAA7146_NTSC
mdefine_line|#define SAA7146_NTSC&t;1
DECL|macro|SAA7146_SECAM
mdefine_line|#define SAA7146_SECAM&t;2
DECL|macro|SAA7146_HPS_SOURCE_PORT_A
mdefine_line|#define SAA7146_HPS_SOURCE_PORT_A&t;0x00
DECL|macro|SAA7146_HPS_SOURCE_PORT_B
mdefine_line|#define SAA7146_HPS_SOURCE_PORT_B&t;0x01
DECL|macro|SAA7146_HPS_SOURCE_YPB_CPA
mdefine_line|#define SAA7146_HPS_SOURCE_YPB_CPA&t;0x02
DECL|macro|SAA7146_HPS_SOURCE_YPA_CPB
mdefine_line|#define SAA7146_HPS_SOURCE_YPA_CPB&t;0x03
DECL|macro|SAA7146_HPS_SYNC_PORT_A
mdefine_line|#define SAA7146_HPS_SYNC_PORT_A&t;0x00
DECL|macro|SAA7146_HPS_SYNC_PORT_B
mdefine_line|#define SAA7146_HPS_SYNC_PORT_B&t;0x01
multiline_comment|/* Number of vertical active lines */
DECL|macro|V_ACTIVE_LINES_PAL
mdefine_line|#define V_ACTIVE_LINES_PAL&t;576
DECL|macro|V_ACTIVE_LINES_NTSC
mdefine_line|#define V_ACTIVE_LINES_NTSC&t;480
DECL|macro|V_ACTIVE_LINES_SECAM
mdefine_line|#define V_ACTIVE_LINES_SECAM&t;576
multiline_comment|/* Number of lines in a field for HPS to process */
DECL|macro|V_FIELD_PAL
mdefine_line|#define V_FIELD_PAL&t;288
DECL|macro|V_FIELD_NTSC
mdefine_line|#define V_FIELD_NTSC&t;240
DECL|macro|V_FIELD_SECAM
mdefine_line|#define V_FIELD_SECAM&t;288
multiline_comment|/* Number of lines of vertical offset before processing */
DECL|macro|V_OFFSET_NTSC
mdefine_line|#define V_OFFSET_NTSC&t;0x10 /* PLI */
DECL|macro|V_OFFSET_PAL
mdefine_line|#define V_OFFSET_PAL&t;0x15
DECL|macro|V_OFFSET_SECAM
mdefine_line|#define V_OFFSET_SECAM&t;0x14
multiline_comment|/* Number of horizontal pixels to process */
DECL|macro|H_PIXELS_NTSC
mdefine_line|#define H_PIXELS_NTSC&t;708
DECL|macro|H_PIXELS_PAL
mdefine_line|#define H_PIXELS_PAL&t;720
DECL|macro|H_PIXELS_SECAM
mdefine_line|#define H_PIXELS_SECAM&t;720
multiline_comment|/* Horizontal offset of processing window */
DECL|macro|H_OFFSET_NTSC
mdefine_line|#define H_OFFSET_NTSC&t;0x40 /* PLI Try 0x3f and find all red colors turning into blue !!?? */
DECL|macro|H_OFFSET_PAL
mdefine_line|#define H_OFFSET_PAL&t;0x3a
DECL|macro|H_OFFSET_SECAM
mdefine_line|#define H_OFFSET_SECAM&t;0x14
multiline_comment|/* some memory-sizes */
DECL|macro|GRABBING_MEM_SIZE
mdefine_line|#define GRABBING_MEM_SIZE&t;0x240000&t;/* 1024 * 576 * 4*/
DECL|macro|CLIPPING_MEM_SIZE
mdefine_line|#define CLIPPING_MEM_SIZE&t;20000 &t;        /* 1024 * 625 / 32 */
DECL|macro|I2C_MEM_SIZE
mdefine_line|#define I2C_MEM_SIZE&t;&t;0x000800&t;/* 2048 */
DECL|macro|RPS_MEM_SIZE
mdefine_line|#define&t;RPS_MEM_SIZE&t;&t;0x000800&t;/* 2048 */
multiline_comment|/************************************************************************/
multiline_comment|/* UNSORTED&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|ME1
mdefine_line|#define ME1    0x0000000800
DECL|macro|PV1
mdefine_line|#define PV1    0x0000000008
multiline_comment|/************************************************************************/
multiline_comment|/* CLIPPING&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/* some defines for the various clipping-modes */
DECL|macro|SAA7146_CLIPPING_RECT
mdefine_line|#define SAA7146_CLIPPING_RECT&t;&t;0x4
DECL|macro|SAA7146_CLIPPING_RECT_INVERTED
mdefine_line|#define SAA7146_CLIPPING_RECT_INVERTED&t;0x5
DECL|macro|SAA7146_CLIPPING_MASK
mdefine_line|#define SAA7146_CLIPPING_MASK&t;&t;0x6
DECL|macro|SAA7146_CLIPPING_MASK_INVERTED
mdefine_line|#define SAA7146_CLIPPING_MASK_INVERTED&t;0x7
multiline_comment|/************************************************************************/
multiline_comment|/* RPS&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|CMD_NOP
mdefine_line|#define CMD_NOP&t;&t;0x00000000  /* No operation */
DECL|macro|CMD_CLR_EVENT
mdefine_line|#define CMD_CLR_EVENT&t;0x00000000  /* Clear event */
DECL|macro|CMD_SET_EVENT
mdefine_line|#define CMD_SET_EVENT&t;0x10000000  /* Set signal event */
DECL|macro|CMD_PAUSE
mdefine_line|#define CMD_PAUSE&t;0x20000000  /* Pause */
DECL|macro|CMD_CHECK_LATE
mdefine_line|#define CMD_CHECK_LATE&t;0x30000000  /* Check late */
DECL|macro|CMD_UPLOAD
mdefine_line|#define CMD_UPLOAD&t;0x40000000  /* Upload */
DECL|macro|CMD_STOP
mdefine_line|#define CMD_STOP&t;0x50000000  /* Stop */
DECL|macro|CMD_INTERRUPT
mdefine_line|#define CMD_INTERRUPT&t;0x60000000  /* Interrupt */
DECL|macro|CMD_JUMP
mdefine_line|#define CMD_JUMP&t;0x80000000  /* Jump */
DECL|macro|CMD_WR_REG
mdefine_line|#define CMD_WR_REG&t;0x90000000  /* Write (load) register */
DECL|macro|CMD_RD_REG
mdefine_line|#define CMD_RD_REG&t;0xa0000000  /* Read (store) register */
DECL|macro|CMD_WR_REG_MASK
mdefine_line|#define CMD_WR_REG_MASK&t;0xc0000000  /* Write register with mask */
multiline_comment|/************************************************************************/
multiline_comment|/* OUTPUT FORMATS &t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/* output formats; each entry holds three types of information */
multiline_comment|/* composed is used in the sense of &quot;not-planar&quot; */
DECL|macro|RGB15_COMPOSED
mdefine_line|#define RGB15_COMPOSED&t;0x213
multiline_comment|/* this means: yuv2rgb-conversation-mode=2, dither=yes(=1), format-mode = 3 */
DECL|macro|RGB16_COMPOSED
mdefine_line|#define RGB16_COMPOSED&t;0x210
DECL|macro|RGB24_COMPOSED
mdefine_line|#define RGB24_COMPOSED&t;0x201
DECL|macro|RGB32_COMPOSED
mdefine_line|#define RGB32_COMPOSED&t;0x202
DECL|macro|YUV411_COMPOSED
mdefine_line|#define YUV411_COMPOSED&t;&t;0x003
multiline_comment|/* this means: yuv2rgb-conversation-mode=0, dither=no(=0), format-mode = 3 */
DECL|macro|YUV422_COMPOSED
mdefine_line|#define YUV422_COMPOSED&t;&t;0x000
DECL|macro|YUV411_DECOMPOSED
mdefine_line|#define YUV411_DECOMPOSED&t;0x00b
DECL|macro|YUV422_DECOMPOSED
mdefine_line|#define YUV422_DECOMPOSED&t;0x009
DECL|macro|YUV420_DECOMPOSED
mdefine_line|#define YUV420_DECOMPOSED&t;0x00a
multiline_comment|/************************************************************************/
multiline_comment|/* MISC &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/* Bit mask constants */
DECL|macro|MASK_00
mdefine_line|#define MASK_00   0x00000001    /* Mask value for bit 0 */
DECL|macro|MASK_01
mdefine_line|#define MASK_01   0x00000002    /* Mask value for bit 1 */
DECL|macro|MASK_02
mdefine_line|#define MASK_02   0x00000004    /* Mask value for bit 2 */
DECL|macro|MASK_03
mdefine_line|#define MASK_03   0x00000008    /* Mask value for bit 3 */
DECL|macro|MASK_04
mdefine_line|#define MASK_04   0x00000010    /* Mask value for bit 4 */
DECL|macro|MASK_05
mdefine_line|#define MASK_05   0x00000020    /* Mask value for bit 5 */
DECL|macro|MASK_06
mdefine_line|#define MASK_06   0x00000040    /* Mask value for bit 6 */
DECL|macro|MASK_07
mdefine_line|#define MASK_07   0x00000080    /* Mask value for bit 7 */
DECL|macro|MASK_08
mdefine_line|#define MASK_08   0x00000100    /* Mask value for bit 8 */
DECL|macro|MASK_09
mdefine_line|#define MASK_09   0x00000200    /* Mask value for bit 9 */
DECL|macro|MASK_10
mdefine_line|#define MASK_10   0x00000400    /* Mask value for bit 10 */
DECL|macro|MASK_11
mdefine_line|#define MASK_11   0x00000800    /* Mask value for bit 11 */
DECL|macro|MASK_12
mdefine_line|#define MASK_12   0x00001000    /* Mask value for bit 12 */
DECL|macro|MASK_13
mdefine_line|#define MASK_13   0x00002000    /* Mask value for bit 13 */
DECL|macro|MASK_14
mdefine_line|#define MASK_14   0x00004000    /* Mask value for bit 14 */
DECL|macro|MASK_15
mdefine_line|#define MASK_15   0x00008000    /* Mask value for bit 15 */
DECL|macro|MASK_16
mdefine_line|#define MASK_16   0x00010000    /* Mask value for bit 16 */
DECL|macro|MASK_17
mdefine_line|#define MASK_17   0x00020000    /* Mask value for bit 17 */
DECL|macro|MASK_18
mdefine_line|#define MASK_18   0x00040000    /* Mask value for bit 18 */
DECL|macro|MASK_19
mdefine_line|#define MASK_19   0x00080000    /* Mask value for bit 19 */
DECL|macro|MASK_20
mdefine_line|#define MASK_20   0x00100000    /* Mask value for bit 20 */
DECL|macro|MASK_21
mdefine_line|#define MASK_21   0x00200000    /* Mask value for bit 21 */
DECL|macro|MASK_22
mdefine_line|#define MASK_22   0x00400000    /* Mask value for bit 22 */
DECL|macro|MASK_23
mdefine_line|#define MASK_23   0x00800000    /* Mask value for bit 23 */
DECL|macro|MASK_24
mdefine_line|#define MASK_24   0x01000000    /* Mask value for bit 24 */
DECL|macro|MASK_25
mdefine_line|#define MASK_25   0x02000000    /* Mask value for bit 25 */
DECL|macro|MASK_26
mdefine_line|#define MASK_26   0x04000000    /* Mask value for bit 26 */
DECL|macro|MASK_27
mdefine_line|#define MASK_27   0x08000000    /* Mask value for bit 27 */
DECL|macro|MASK_28
mdefine_line|#define MASK_28   0x10000000    /* Mask value for bit 28 */
DECL|macro|MASK_29
mdefine_line|#define MASK_29   0x20000000    /* Mask value for bit 29 */
DECL|macro|MASK_30
mdefine_line|#define MASK_30   0x40000000    /* Mask value for bit 30 */
DECL|macro|MASK_31
mdefine_line|#define MASK_31   0x80000000    /* Mask value for bit 31 */
DECL|macro|MASK_B0
mdefine_line|#define MASK_B0   0x000000ff    /* Mask value for byte 0 */
DECL|macro|MASK_B1
mdefine_line|#define MASK_B1   0x0000ff00    /* Mask value for byte 1 */
DECL|macro|MASK_B2
mdefine_line|#define MASK_B2   0x00ff0000    /* Mask value for byte 2 */
DECL|macro|MASK_B3
mdefine_line|#define MASK_B3   0xff000000    /* Mask value for byte 3 */
DECL|macro|MASK_W0
mdefine_line|#define MASK_W0   0x0000ffff    /* Mask value for word 0 */
DECL|macro|MASK_W1
mdefine_line|#define MASK_W1   0xffff0000    /* Mask value for word 1 */
DECL|macro|MASK_PA
mdefine_line|#define MASK_PA   0xfffffffc    /* Mask value for physical address */
DECL|macro|MASK_PR
mdefine_line|#define MASK_PR   0xfffffffe &t;/* Mask value for protection register */
DECL|macro|MASK_ER
mdefine_line|#define MASK_ER   0xffffffff    /* Mask value for the entire register */
DECL|macro|MASK_NONE
mdefine_line|#define MASK_NONE 0x00000000    /* No mask */
multiline_comment|/************************************************************************/
multiline_comment|/* REGISTERS &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|BASE_ODD1
mdefine_line|#define BASE_ODD1         0x00  /* Video DMA 1 registers  */
DECL|macro|BASE_EVEN1
mdefine_line|#define BASE_EVEN1        0x04
DECL|macro|PROT_ADDR1
mdefine_line|#define PROT_ADDR1        0x08
DECL|macro|PITCH1
mdefine_line|#define PITCH1            0x0C
DECL|macro|BASE_PAGE1
mdefine_line|#define BASE_PAGE1        0x10  /* Video DMA 1 base page */
DECL|macro|NUM_LINE_BYTE1
mdefine_line|#define NUM_LINE_BYTE1    0x14
DECL|macro|BASE_ODD2
mdefine_line|#define BASE_ODD2         0x18  /* Video DMA 2 registers */
DECL|macro|BASE_EVEN2
mdefine_line|#define BASE_EVEN2        0x1C
DECL|macro|PROT_ADDR2
mdefine_line|#define PROT_ADDR2        0x20
DECL|macro|PITCH2
mdefine_line|#define PITCH2            0x24
DECL|macro|BASE_PAGE2
mdefine_line|#define BASE_PAGE2        0x28  /* Video DMA 2 base page */
DECL|macro|NUM_LINE_BYTE2
mdefine_line|#define NUM_LINE_BYTE2    0x2C
DECL|macro|BASE_ODD3
mdefine_line|#define BASE_ODD3         0x30  /* Video DMA 3 registers */
DECL|macro|BASE_EVEN3
mdefine_line|#define BASE_EVEN3        0x34
DECL|macro|PROT_ADDR3
mdefine_line|#define PROT_ADDR3        0x38
DECL|macro|PITCH3
mdefine_line|#define PITCH3            0x3C         
DECL|macro|BASE_PAGE3
mdefine_line|#define BASE_PAGE3        0x40  /* Video DMA 3 base page */
DECL|macro|NUM_LINE_BYTE3
mdefine_line|#define NUM_LINE_BYTE3    0x44
DECL|macro|PCI_BT_V1
mdefine_line|#define PCI_BT_V1         0x48  /* Video/FIFO 1 */
DECL|macro|PCI_BT_V2
mdefine_line|#define PCI_BT_V2         0x49  /* Video/FIFO 2 */
DECL|macro|PCI_BT_V3
mdefine_line|#define PCI_BT_V3         0x4A  /* Video/FIFO 3 */
DECL|macro|PCI_BT_DEBI
mdefine_line|#define PCI_BT_DEBI       0x4B  /* DEBI */
DECL|macro|PCI_BT_A
mdefine_line|#define PCI_BT_A          0x4C  /* Audio */
DECL|macro|DD1_INIT
mdefine_line|#define DD1_INIT          0x50  /* Init setting of DD1 interface */
DECL|macro|DD1_STREAM_B
mdefine_line|#define DD1_STREAM_B      0x54  /* DD1 B video data stream handling */
DECL|macro|DD1_STREAM_A
mdefine_line|#define DD1_STREAM_A      0x56  /* DD1 A video data stream handling */
DECL|macro|BRS_CTRL
mdefine_line|#define BRS_CTRL          0x58  /* BRS control register */
DECL|macro|HPS_CTRL
mdefine_line|#define HPS_CTRL          0x5C  /* HPS control register */
DECL|macro|HPS_V_SCALE
mdefine_line|#define HPS_V_SCALE       0x60  /* HPS vertical scale */
DECL|macro|HPS_V_GAIN
mdefine_line|#define HPS_V_GAIN        0x64  /* HPS vertical ACL and gain */
DECL|macro|HPS_H_PRESCALE
mdefine_line|#define HPS_H_PRESCALE    0x68  /* HPS horizontal prescale   */
DECL|macro|HPS_H_SCALE
mdefine_line|#define HPS_H_SCALE       0x6C  /* HPS horizontal scale */
DECL|macro|BCS_CTRL
mdefine_line|#define BCS_CTRL          0x70  /* BCS control */
DECL|macro|CHROMA_KEY_RANGE
mdefine_line|#define CHROMA_KEY_RANGE  0x74
DECL|macro|CLIP_FORMAT_CTRL
mdefine_line|#define CLIP_FORMAT_CTRL  0x78  /* HPS outputs formats &amp; clipping */
DECL|macro|DEBI_CONFIG
mdefine_line|#define DEBI_CONFIG       0x7C
DECL|macro|DEBI_COMMAND
mdefine_line|#define DEBI_COMMAND      0x80
DECL|macro|DEBI_PAGE
mdefine_line|#define DEBI_PAGE         0x84
DECL|macro|DEBI_AD
mdefine_line|#define DEBI_AD           0x88&t;
DECL|macro|I2C_TRANSFER
mdefine_line|#define I2C_TRANSFER      0x8C&t;
DECL|macro|I2C_STATUS
mdefine_line|#define I2C_STATUS        0x90&t;
DECL|macro|BASE_A1_IN
mdefine_line|#define BASE_A1_IN        0x94&t;/* Audio 1 input DMA */
DECL|macro|PROT_A1_IN
mdefine_line|#define PROT_A1_IN        0x98
DECL|macro|PAGE_A1_IN
mdefine_line|#define PAGE_A1_IN        0x9C
DECL|macro|BASE_A1_OUT
mdefine_line|#define BASE_A1_OUT       0xA0  /* Audio 1 output DMA */
DECL|macro|PROT_A1_OUT
mdefine_line|#define PROT_A1_OUT       0xA4
DECL|macro|PAGE_A1_OUT
mdefine_line|#define PAGE_A1_OUT       0xA8
DECL|macro|BASE_A2_IN
mdefine_line|#define BASE_A2_IN        0xAC  /* Audio 2 input DMA */
DECL|macro|PROT_A2_IN
mdefine_line|#define PROT_A2_IN        0xB0
DECL|macro|PAGE_A2_IN
mdefine_line|#define PAGE_A2_IN        0xB4
DECL|macro|BASE_A2_OUT
mdefine_line|#define BASE_A2_OUT       0xB8  /* Audio 2 output DMA */
DECL|macro|PROT_A2_OUT
mdefine_line|#define PROT_A2_OUT       0xBC
DECL|macro|PAGE_A2_OUT
mdefine_line|#define PAGE_A2_OUT       0xC0
DECL|macro|RPS_PAGE0
mdefine_line|#define RPS_PAGE0         0xC4  /* RPS task 0 page register */
DECL|macro|RPS_PAGE1
mdefine_line|#define RPS_PAGE1         0xC8  /* RPS task 1 page register */
DECL|macro|RPS_THRESH0
mdefine_line|#define RPS_THRESH0       0xCC  /* HBI threshold for task 0 */
DECL|macro|RPS_THRESH1
mdefine_line|#define RPS_THRESH1       0xD0  /* HBI threshold for task 1 */
DECL|macro|RPS_TOV0
mdefine_line|#define RPS_TOV0          0xD4  /* RPS timeout for task 0 */
DECL|macro|RPS_TOV1
mdefine_line|#define RPS_TOV1          0xD8  /* RPS timeout for task 1 */
DECL|macro|IER
mdefine_line|#define IER               0xDC  /* Interrupt enable register */
DECL|macro|GPIO_CTRL
mdefine_line|#define GPIO_CTRL         0xE0  /* GPIO 0-3 register */
DECL|macro|EC1SSR
mdefine_line|#define EC1SSR            0xE4  /* Event cnt set 1 source select */
DECL|macro|EC2SSR
mdefine_line|#define EC2SSR            0xE8  /* Event cnt set 2 source select */
DECL|macro|ECT1R
mdefine_line|#define ECT1R             0xEC  /* Event cnt set 1 thresholds */
DECL|macro|ECT2R
mdefine_line|#define ECT2R             0xF0  /* Event cnt set 2 thresholds */
DECL|macro|ACON1
mdefine_line|#define ACON1             0xF4
DECL|macro|ACON2
mdefine_line|#define ACON2             0xF8
DECL|macro|MC1
mdefine_line|#define MC1               0xFC   /* Main control register 1 */
DECL|macro|MC2
mdefine_line|#define MC2               0x100  /* Main control register 2  */
DECL|macro|RPS_ADDR0
mdefine_line|#define RPS_ADDR0         0x104  /* RPS task 0 address register */
DECL|macro|RPS_ADDR1
mdefine_line|#define RPS_ADDR1         0x108  /* RPS task 1 address register */
DECL|macro|ISR
mdefine_line|#define ISR               0x10C  /* Interrupt status register */                                                             
DECL|macro|PSR
mdefine_line|#define PSR               0x110  /* Primary status register */
DECL|macro|SSR
mdefine_line|#define SSR               0x114  /* Secondary status register */
DECL|macro|EC1R
mdefine_line|#define EC1R              0x118  /* Event counter set 1 register */
DECL|macro|EC2R
mdefine_line|#define EC2R              0x11C  /* Event counter set 2 register */         
DECL|macro|PCI_VDP1
mdefine_line|#define PCI_VDP1          0x120  /* Video DMA pointer of FIFO 1 */
DECL|macro|PCI_VDP2
mdefine_line|#define PCI_VDP2          0x124  /* Video DMA pointer of FIFO 2 */
DECL|macro|PCI_VDP3
mdefine_line|#define PCI_VDP3          0x128  /* Video DMA pointer of FIFO 3 */
DECL|macro|PCI_ADP1
mdefine_line|#define PCI_ADP1          0x12C  /* Audio DMA pointer of audio out 1 */
DECL|macro|PCI_ADP2
mdefine_line|#define PCI_ADP2          0x130  /* Audio DMA pointer of audio in 1 */
DECL|macro|PCI_ADP3
mdefine_line|#define PCI_ADP3          0x134  /* Audio DMA pointer of audio out 2 */
DECL|macro|PCI_ADP4
mdefine_line|#define PCI_ADP4          0x138  /* Audio DMA pointer of audio in 2 */
DECL|macro|PCI_DMA_DDP
mdefine_line|#define PCI_DMA_DDP       0x13C  /* DEBI DMA pointer */
DECL|macro|LEVEL_REP
mdefine_line|#define LEVEL_REP         0x140,
DECL|macro|A_TIME_SLOT1
mdefine_line|#define A_TIME_SLOT1      0x180,  /* from 180 - 1BC */
DECL|macro|A_TIME_SLOT2
mdefine_line|#define A_TIME_SLOT2      0x1C0,  /* from 1C0 - 1FC */
multiline_comment|/************************************************************************/
multiline_comment|/* ISR-MASKS &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|SPCI_PPEF
mdefine_line|#define SPCI_PPEF       0x80000000  /* PCI parity error */
DECL|macro|SPCI_PABO
mdefine_line|#define SPCI_PABO       0x40000000  /* PCI access error (target or master abort) */
DECL|macro|SPCI_PPED
mdefine_line|#define SPCI_PPED       0x20000000  /* PCI parity error on &squot;real time data&squot; */
DECL|macro|SPCI_RPS_I1
mdefine_line|#define SPCI_RPS_I1     0x10000000  /* Interrupt issued by RPS1 */
DECL|macro|SPCI_RPS_I0
mdefine_line|#define SPCI_RPS_I0     0x08000000  /* Interrupt issued by RPS0 */
DECL|macro|SPCI_RPS_LATE1
mdefine_line|#define SPCI_RPS_LATE1  0x04000000  /* RPS task 1 is late */
DECL|macro|SPCI_RPS_LATE0
mdefine_line|#define SPCI_RPS_LATE0  0x02000000  /* RPS task 0 is late */
DECL|macro|SPCI_RPS_E1
mdefine_line|#define SPCI_RPS_E1     0x01000000  /* RPS error from task 1 */
DECL|macro|SPCI_RPS_E0
mdefine_line|#define SPCI_RPS_E0     0x00800000  /* RPS error from task 0 */
DECL|macro|SPCI_RPS_TO1
mdefine_line|#define SPCI_RPS_TO1    0x00400000  /* RPS timeout task 1 */
DECL|macro|SPCI_RPS_TO0
mdefine_line|#define SPCI_RPS_TO0    0x00200000  /* RPS timeout task 0 */
DECL|macro|SPCI_UPLD
mdefine_line|#define SPCI_UPLD       0x00100000  /* RPS in upload */
DECL|macro|SPCI_DEBI_S
mdefine_line|#define SPCI_DEBI_S     0x00080000  /* DEBI status */
DECL|macro|SPCI_DEBI_E
mdefine_line|#define SPCI_DEBI_E     0x00040000  /* DEBI error */
DECL|macro|SPCI_IIC_S
mdefine_line|#define SPCI_IIC_S      0x00020000  /* I2C status */
DECL|macro|SPCI_IIC_E
mdefine_line|#define SPCI_IIC_E      0x00010000  /* I2C error */
DECL|macro|SPCI_A2_IN
mdefine_line|#define SPCI_A2_IN      0x00008000  /* Audio 2 input DMA protection / limit */
DECL|macro|SPCI_A2_OUT
mdefine_line|#define SPCI_A2_OUT     0x00004000  /* Audio 2 output DMA protection / limit */
DECL|macro|SPCI_A1_IN
mdefine_line|#define SPCI_A1_IN      0x00002000  /* Audio 1 input DMA protection / limit */
DECL|macro|SPCI_A1_OUT
mdefine_line|#define SPCI_A1_OUT     0x00001000  /* Audio 1 output DMA protection / limit */
DECL|macro|SPCI_AFOU
mdefine_line|#define SPCI_AFOU       0x00000800  /* Audio FIFO over- / underflow */
DECL|macro|SPCI_V_PE
mdefine_line|#define SPCI_V_PE       0x00000400  /* Video protection address */
DECL|macro|SPCI_VFOU
mdefine_line|#define SPCI_VFOU       0x00000200  /* Video FIFO over- / underflow */
DECL|macro|SPCI_FIDA
mdefine_line|#define SPCI_FIDA       0x00000100  /* Field ID video port A */
DECL|macro|SPCI_FIDB
mdefine_line|#define SPCI_FIDB       0x00000080  /* Field ID video port B */
DECL|macro|SPCI_PIN3
mdefine_line|#define SPCI_PIN3       0x00000040  /* GPIO pin 3 */
DECL|macro|SPCI_PIN2
mdefine_line|#define SPCI_PIN2       0x00000020  /* GPIO pin 2 */
DECL|macro|SPCI_PIN1
mdefine_line|#define SPCI_PIN1       0x00000010  /* GPIO pin 1 */
DECL|macro|SPCI_PIN0
mdefine_line|#define SPCI_PIN0       0x00000008  /* GPIO pin 0 */
DECL|macro|SPCI_ECS
mdefine_line|#define SPCI_ECS        0x00000004  /* Event counter 1, 2, 4, 5 */
DECL|macro|SPCI_EC3S
mdefine_line|#define SPCI_EC3S       0x00000002  /* Event counter 3 */
DECL|macro|SPCI_EC0S
mdefine_line|#define SPCI_EC0S       0x00000001  /* Event counter 0 */
multiline_comment|/************************************************************************/
multiline_comment|/* I2C&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/* time we wait after certain i2c-operations */
DECL|macro|SAA7146_I2C_DELAY
mdefine_line|#define SAA7146_I2C_DELAY &t;&t;10
DECL|macro|SAA7146_I2C_ABORT
mdefine_line|#define&t;SAA7146_I2C_ABORT&t;(1&lt;&lt;7)
DECL|macro|SAA7146_I2C_SPERR
mdefine_line|#define&t;SAA7146_I2C_SPERR&t;(1&lt;&lt;6)
DECL|macro|SAA7146_I2C_APERR
mdefine_line|#define&t;SAA7146_I2C_APERR&t;(1&lt;&lt;5)
DECL|macro|SAA7146_I2C_DTERR
mdefine_line|#define&t;SAA7146_I2C_DTERR&t;(1&lt;&lt;4)
DECL|macro|SAA7146_I2C_DRERR
mdefine_line|#define&t;SAA7146_I2C_DRERR&t;(1&lt;&lt;3)
DECL|macro|SAA7146_I2C_AL
mdefine_line|#define&t;SAA7146_I2C_AL&t;&t;(1&lt;&lt;2)
DECL|macro|SAA7146_I2C_ERR
mdefine_line|#define&t;SAA7146_I2C_ERR&t;&t;(1&lt;&lt;1)
DECL|macro|SAA7146_I2C_BUSY
mdefine_line|#define&t;SAA7146_I2C_BUSY&t;(1&lt;&lt;0)
DECL|macro|SAA7146_I2C_START
mdefine_line|#define&t;SAA7146_I2C_START&t;(0x3)
DECL|macro|SAA7146_I2C_CONT
mdefine_line|#define&t;SAA7146_I2C_CONT&t;(0x2)
DECL|macro|SAA7146_I2C_STOP
mdefine_line|#define&t;SAA7146_I2C_STOP&t;(0x1)
DECL|macro|SAA7146_I2C_NOP
mdefine_line|#define&t;SAA7146_I2C_NOP&t;&t;(0x0)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_6400
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_6400&t;(0x500)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_3200
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_3200&t;(0x100)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_480
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_480&t;(0x400)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_320
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_320&t;(0x600)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_240
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_240&t;(0x700)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_120
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_120&t;(0x000)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_80
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_80&t;(0x200)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_60
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_60&t;(0x300)
macro_line|#endif
eof
