multiline_comment|/* drivers/atm/midway.h - Efficient Networks Midway (SAR) description */
multiline_comment|/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef DRIVERS_ATM_MIDWAY_H
DECL|macro|DRIVERS_ATM_MIDWAY_H
mdefine_line|#define DRIVERS_ATM_MIDWAY_H
DECL|macro|NR_VCI
mdefine_line|#define NR_VCI&t;&t;1024&t;&t;/* number of VCIs */
DECL|macro|NR_VCI_LD
mdefine_line|#define NR_VCI_LD&t;10&t;&t;/* log2(NR_VCI) */
DECL|macro|NR_DMA_RX
mdefine_line|#define NR_DMA_RX&t;512&t;&t;/* RX DMA queue entries */
DECL|macro|NR_DMA_TX
mdefine_line|#define NR_DMA_TX&t;512&t;&t;/* TX DMA queue entries */
DECL|macro|NR_SERVICE
mdefine_line|#define NR_SERVICE&t;NR_VCI&t;&t;/* service list size */
DECL|macro|NR_CHAN
mdefine_line|#define NR_CHAN&t;&t;8&t;&t;/* number of TX channels */
DECL|macro|TS_CLOCK
mdefine_line|#define TS_CLOCK&t;25000000&t;/* traffic shaper clock (cell/sec) */
DECL|macro|MAP_MAX_SIZE
mdefine_line|#define MAP_MAX_SIZE&t;0x00400000&t;/* memory window for max config */
DECL|macro|EPROM_SIZE
mdefine_line|#define EPROM_SIZE&t;0x00010000
DECL|macro|MEM_VALID
mdefine_line|#define&t;MEM_VALID&t;0xffc00000&t;/* mask base address with this */
DECL|macro|PHY_BASE
mdefine_line|#define PHY_BASE&t;0x00020000&t;/* offset of PHY register are */
DECL|macro|REG_BASE
mdefine_line|#define REG_BASE&t;0x00040000&t;/* offset of Midway register area */
DECL|macro|RAM_BASE
mdefine_line|#define RAM_BASE&t;0x00200000&t;/* offset of RAM area */
DECL|macro|RAM_INCREMENT
mdefine_line|#define RAM_INCREMENT&t;0x00020000&t;/* probe for RAM every 128kB */
DECL|macro|MID_VCI_BASE
mdefine_line|#define MID_VCI_BASE&t;RAM_BASE
DECL|macro|MID_DMA_RX_BASE
mdefine_line|#define MID_DMA_RX_BASE&t;(MID_VCI_BASE+NR_VCI*16)
DECL|macro|MID_DMA_TX_BASE
mdefine_line|#define MID_DMA_TX_BASE&t;(MID_DMA_RX_BASE+NR_DMA_RX*8)
DECL|macro|MID_SERVICE_BASE
mdefine_line|#define MID_SERVICE_BASE (MID_DMA_TX_BASE+NR_DMA_TX*8)
DECL|macro|MID_FREE_BASE
mdefine_line|#define MID_FREE_BASE&t;(MID_SERVICE_BASE+NR_SERVICE*4)
DECL|macro|MAC_LEN
mdefine_line|#define MAC_LEN 6 /* atm.h */
DECL|macro|MID_MIN_BUF_SIZE
mdefine_line|#define MID_MIN_BUF_SIZE (1024)&t;&t;/*   1 kB is minimum */
DECL|macro|MID_MAX_BUF_SIZE
mdefine_line|#define MID_MAX_BUF_SIZE (128*1024)&t;/* 128 kB is maximum */
DECL|macro|RX_DESCR_SIZE
mdefine_line|#define RX_DESCR_SIZE&t;1&t;&t;/* RX PDU descr is 1 longword */
DECL|macro|TX_DESCR_SIZE
mdefine_line|#define TX_DESCR_SIZE&t;2&t;&t;/* TX PDU descr is 2 longwords */
DECL|macro|AAL5_TRAILER
mdefine_line|#define AAL5_TRAILER&t;(ATM_AAL5_TRAILER/4) /* AAL5 trailer is 2 longwords */
DECL|macro|TX_GAP
mdefine_line|#define TX_GAP&t;&t;8&t;&t;/* TX buffer gap (words) */
multiline_comment|/*&n; * Midway Reset/ID&n; *&n; * All values read-only. Writing to this register resets Midway chip.&n; */
DECL|macro|MID_RES_ID_MCON
mdefine_line|#define MID_RES_ID_MCON&t;0x00&t;&t;/* Midway Reset/ID */
DECL|macro|MID_ID
mdefine_line|#define MID_ID&t;&t;0xf0000000&t;/* Midway version */
DECL|macro|MID_SHIFT
mdefine_line|#define MID_SHIFT&t;24
DECL|macro|MID_MOTHER_ID
mdefine_line|#define MID_MOTHER_ID&t;0x00000700&t;/* mother board id */
DECL|macro|MID_MOTHER_SHIFT
mdefine_line|#define MID_MOTHER_SHIFT 8
DECL|macro|MID_CON_TI
mdefine_line|#define MID_CON_TI&t;0x00000080&t;/* 0: normal ctrl; 1: SABRE */
DECL|macro|MID_CON_SUNI
mdefine_line|#define MID_CON_SUNI&t;0x00000040&t;/* 0: UTOPIA; 1: SUNI */
DECL|macro|MID_CON_V6
mdefine_line|#define MID_CON_V6&t;0x00000020&t;/* 0: non-pipel UTOPIA (required iff&n;&t;&t;&t;&t;&t;   !CON_SUNI; 1: UTOPIA */
DECL|macro|DAUGTHER_ID
mdefine_line|#define DAUGTHER_ID&t;0x0000001f&t;/* daugther board id */
multiline_comment|/*&n; * Interrupt Status Acknowledge, Interrupt Status &amp; Interrupt Enable&n; */
DECL|macro|MID_ISA
mdefine_line|#define MID_ISA&t;&t;0x01&t;&t;/* Interrupt Status Acknowledge */
DECL|macro|MID_IS
mdefine_line|#define MID_IS&t;&t;0x02&t;&t;/* Interrupt Status */
DECL|macro|MID_IE
mdefine_line|#define MID_IE&t;&t;0x03&t;&t;/* Interrupt Enable */
DECL|macro|MID_TX_COMPLETE_7
mdefine_line|#define MID_TX_COMPLETE_7 0x00010000&t;/* channel N completed a PDU */
DECL|macro|MID_TX_COMPLETE_6
mdefine_line|#define MID_TX_COMPLETE_6 0x00008000&t;/* transmission */
DECL|macro|MID_TX_COMPLETE_5
mdefine_line|#define MID_TX_COMPLETE_5 0x00004000
DECL|macro|MID_TX_COMPLETE_4
mdefine_line|#define MID_TX_COMPLETE_4 0x00002000
DECL|macro|MID_TX_COMPLETE_3
mdefine_line|#define MID_TX_COMPLETE_3 0x00001000
DECL|macro|MID_TX_COMPLETE_2
mdefine_line|#define MID_TX_COMPLETE_2 0x00000800
DECL|macro|MID_TX_COMPLETE_1
mdefine_line|#define MID_TX_COMPLETE_1 0x00000400
DECL|macro|MID_TX_COMPLETE_0
mdefine_line|#define MID_TX_COMPLETE_0 0x00000200
DECL|macro|MID_TX_COMPLETE
mdefine_line|#define MID_TX_COMPLETE&t;0x0001fe00&t;/* any TX */
DECL|macro|MID_TX_DMA_OVFL
mdefine_line|#define MID_TX_DMA_OVFL&t;0x00000100&t;/* DMA to adapter overflow */
DECL|macro|MID_TX_IDENT_MISM
mdefine_line|#define MID_TX_IDENT_MISM 0x00000080&t;/* TX: ident mismatch =&gt; halted */
DECL|macro|MID_DMA_LERR_ACK
mdefine_line|#define MID_DMA_LERR_ACK 0x00000040&t;/* LERR - SBus ? */
DECL|macro|MID_DMA_ERR_ACK
mdefine_line|#define MID_DMA_ERR_ACK&t;0x00000020&t;/* DMA error */
DECL|macro|MID_RX_DMA_COMPLETE
mdefine_line|#define&t;MID_RX_DMA_COMPLETE 0x00000010&t;/* DMA to host done */
DECL|macro|MID_TX_DMA_COMPLETE
mdefine_line|#define MID_TX_DMA_COMPLETE 0x00000008&t;/* DMA from host done */
DECL|macro|MID_SERVICE
mdefine_line|#define MID_SERVICE&t;0x00000004&t;/* something in service list */
DECL|macro|MID_SUNI_INT
mdefine_line|#define MID_SUNI_INT&t;0x00000002&t;/* interrupt from SUNI */
DECL|macro|MID_STAT_OVFL
mdefine_line|#define MID_STAT_OVFL&t;0x00000001&t;/* statistics overflow */
multiline_comment|/*&n; * Master Control/Status&n; */
DECL|macro|MID_MC_S
mdefine_line|#define MID_MC_S&t;0x04
DECL|macro|MID_INT_SELECT
mdefine_line|#define MID_INT_SELECT&t;0x000001C0&t;/* Interrupt level (000: off) */
DECL|macro|MID_INT_SEL_SHIFT
mdefine_line|#define MID_INT_SEL_SHIFT 6
DECL|macro|MID_TX_LOCK_MODE
mdefine_line|#define&t;MID_TX_LOCK_MODE 0x00000020&t;/* 0: streaming; 1: TX ovfl-&gt;lock */
DECL|macro|MID_DMA_ENABLE
mdefine_line|#define MID_DMA_ENABLE&t;0x00000010&t;/* R: 0: disable; 1: enable&n;&t;&t;&t;&t;&t;   W: 0: no change; 1: enable */
DECL|macro|MID_TX_ENABLE
mdefine_line|#define MID_TX_ENABLE&t;0x00000008&t;/* R: 0: TX disabled; 1: enabled&n;&t;&t;&t;&t;&t;   W: 0: no change; 1: enable */
DECL|macro|MID_RX_ENABLE
mdefine_line|#define MID_RX_ENABLE&t;0x00000004&t;/* like TX */
DECL|macro|MID_WAIT_1MS
mdefine_line|#define MID_WAIT_1MS&t;0x00000002&t;/* R: 0: timer not running; 1: running&n;&t;&t;&t;&t;&t;   W: 0: no change; 1: no interrupts&n;&t;&t;&t;&t;&t;&t;&t;       for 1 ms */
DECL|macro|MID_WAIT_500US
mdefine_line|#define MID_WAIT_500US&t;0x00000001&t;/* like WAIT_1MS, but 0.5 ms */
multiline_comment|/*&n; * Statistics&n; *&n; * Cleared when reading.&n; */
DECL|macro|MID_STAT
mdefine_line|#define MID_STAT&t;&t;0x05
DECL|macro|MID_VCI_TRASH
mdefine_line|#define MID_VCI_TRASH&t;0xFFFF0000&t;/* trashed cells because of VCI mode */
DECL|macro|MID_VCI_TRASH_SHIFT
mdefine_line|#define MID_VCI_TRASH_SHIFT 16
DECL|macro|MID_OVFL_TRASH
mdefine_line|#define MID_OVFL_TRASH&t;0x0000FFFF&t;/* trashed cells because of overflow */
multiline_comment|/*&n; * Address registers&n; */
DECL|macro|MID_SERV_WRITE
mdefine_line|#define MID_SERV_WRITE&t;0x06&t;/* free pos in service area (R, 10 bits) */
DECL|macro|MID_DMA_ADDR
mdefine_line|#define MID_DMA_ADDR&t;0x07&t;/* virtual DMA address (R, 32 bits) */
DECL|macro|MID_DMA_WR_RX
mdefine_line|#define MID_DMA_WR_RX&t;0x08&t;/* (RW, 9 bits) */
DECL|macro|MID_DMA_RD_RX
mdefine_line|#define MID_DMA_RD_RX&t;0x09
DECL|macro|MID_DMA_WR_TX
mdefine_line|#define MID_DMA_WR_TX&t;0x0A
DECL|macro|MID_DMA_RD_TX
mdefine_line|#define MID_DMA_RD_TX&t;0x0B
multiline_comment|/*&n; * Transmit Place Registers (0x10+4*channel)&n; */
DECL|macro|MID_TX_PLACE
mdefine_line|#define MID_TX_PLACE(c)&t;(0x10+4*(c))
DECL|macro|MID_SIZE
mdefine_line|#define MID_SIZE&t;0x00003800&t;/* size, N*256 x 32 bit */
DECL|macro|MID_SIZE_SHIFT
mdefine_line|#define MID_SIZE_SHIFT&t;11
DECL|macro|MID_LOCATION
mdefine_line|#define MID_LOCATION&t;0x000007FF&t;/* location in adapter memory (word) */
DECL|macro|MID_LOC_SKIP
mdefine_line|#define MID_LOC_SKIP&t;8&t;&t;/* 8 bits of location are always zero&n;&t;&t;&t;&t;&t;   (applies to all uses of location) */
multiline_comment|/*&n; * Transmit ReadPtr Registers (0x11+4*channel)&n; */
DECL|macro|MID_TX_RDPTR
mdefine_line|#define MID_TX_RDPTR(c)&t;(0x11+4*(c))
DECL|macro|MID_READ_PTR
mdefine_line|#define MID_READ_PTR&t;0x00007FFF&t;/* next word for PHY */
multiline_comment|/*&n; * Transmit DescrStart Registers (0x12+4*channel)&n; */
DECL|macro|MID_TX_DESCRSTART
mdefine_line|#define MID_TX_DESCRSTART(c) (0x12+4*(c))
DECL|macro|MID_DESCR_START
mdefine_line|#define MID_DESCR_START&t;0x00007FFF&t;/* seg buffer being DMAed */
DECL|macro|ENI155_MAGIC
mdefine_line|#define ENI155_MAGIC&t;0xa54b872d
DECL|struct|midway_eprom
r_struct
id|midway_eprom
(brace
DECL|member|mac
DECL|member|inv_mac
r_int
r_char
id|mac
(braket
id|MAC_LEN
)braket
comma
id|inv_mac
(braket
id|MAC_LEN
)braket
suffix:semicolon
DECL|member|pad
r_int
r_char
id|pad
(braket
l_int|36
)braket
suffix:semicolon
DECL|member|serial
DECL|member|inv_serial
id|u32
id|serial
comma
id|inv_serial
suffix:semicolon
DECL|member|magic
DECL|member|inv_magic
id|u32
id|magic
comma
id|inv_magic
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * VCI table entry&n; */
DECL|macro|MID_VCI_IN_SERVICE
mdefine_line|#define MID_VCI_IN_SERVICE&t;0x00000001&t;/* set if VCI is currently in&n;&t;&t;&t;&t;&t;&t;   service list */
DECL|macro|MID_VCI_SIZE
mdefine_line|#define MID_VCI_SIZE&t;&t;0x00038000&t;/* reassembly buffer size,&n;&t;&t;&t;&t;&t;&t;   2*&lt;size&gt; kB */
DECL|macro|MID_VCI_SIZE_SHIFT
mdefine_line|#define MID_VCI_SIZE_SHIFT&t;15
DECL|macro|MID_VCI_LOCATION
mdefine_line|#define MID_VCI_LOCATION&t;0x1ffc0000&t;/* buffer location */
DECL|macro|MID_VCI_LOCATION_SHIFT
mdefine_line|#define MID_VCI_LOCATION_SHIFT&t;18
DECL|macro|MID_VCI_PTI_MODE
mdefine_line|#define MID_VCI_PTI_MODE&t;0x20000000&t;/* 0: trash, 1: preserve */
DECL|macro|MID_VCI_MODE
mdefine_line|#define MID_VCI_MODE&t;&t;0xc0000000
DECL|macro|MID_VCI_MODE_SHIFT
mdefine_line|#define MID_VCI_MODE_SHIFT&t;30
DECL|macro|MID_VCI_READ
mdefine_line|#define MID_VCI_READ&t;&t;0x00007fff
DECL|macro|MID_VCI_READ_SHIFT
mdefine_line|#define MID_VCI_READ_SHIFT&t;0
DECL|macro|MID_VCI_DESCR
mdefine_line|#define MID_VCI_DESCR&t;&t;0x7fff0000
DECL|macro|MID_VCI_DESCR_SHIFT
mdefine_line|#define MID_VCI_DESCR_SHIFT&t;16
DECL|macro|MID_VCI_COUNT
mdefine_line|#define MID_VCI_COUNT&t;&t;0x000007ff
DECL|macro|MID_VCI_COUNT_SHIFT
mdefine_line|#define MID_VCI_COUNT_SHIFT&t;0
DECL|macro|MID_VCI_STATE
mdefine_line|#define MID_VCI_STATE&t;&t;0x0000c000
DECL|macro|MID_VCI_STATE_SHIFT
mdefine_line|#define MID_VCI_STATE_SHIFT&t;14
DECL|macro|MID_VCI_WRITE
mdefine_line|#define MID_VCI_WRITE&t;&t;0x7fff0000
DECL|macro|MID_VCI_WRITE_SHIFT
mdefine_line|#define MID_VCI_WRITE_SHIFT&t;16
DECL|macro|MID_MODE_TRASH
mdefine_line|#define MID_MODE_TRASH&t;0
DECL|macro|MID_MODE_RAW
mdefine_line|#define MID_MODE_RAW&t;1
DECL|macro|MID_MODE_AAL5
mdefine_line|#define MID_MODE_AAL5&t;2
multiline_comment|/*&n; * Reassembly buffer descriptor&n; */
DECL|macro|MID_RED_COUNT
mdefine_line|#define MID_RED_COUNT&t;&t;0x000007ff
DECL|macro|MID_RED_CRC_ERR
mdefine_line|#define MID_RED_CRC_ERR&t;&t;0x00000800
DECL|macro|MID_RED_T
mdefine_line|#define MID_RED_T&t;&t;0x00001000
DECL|macro|MID_RED_CE
mdefine_line|#define MID_RED_CE&t;&t;0x00010000
DECL|macro|MID_RED_CLP
mdefine_line|#define MID_RED_CLP&t;&t;0x01000000
DECL|macro|MID_RED_IDEN
mdefine_line|#define MID_RED_IDEN&t;&t;0xfe000000
DECL|macro|MID_RED_SHIFT
mdefine_line|#define MID_RED_SHIFT&t;&t;25
DECL|macro|MID_RED_RX_ID
mdefine_line|#define MID_RED_RX_ID&t;&t;0x1b&t;&t;/* constant identifier */
multiline_comment|/*&n; * Segmentation buffer descriptor&n; */
DECL|macro|MID_SEG_COUNT
mdefine_line|#define MID_SEG_COUNT&t;&t;MID_RED_COUNT
DECL|macro|MID_SEG_RATE
mdefine_line|#define MID_SEG_RATE&t;&t;0x01f80000
DECL|macro|MID_SEG_RATE_SHIFT
mdefine_line|#define MID_SEG_RATE_SHIFT&t;19
DECL|macro|MID_SEG_PR
mdefine_line|#define MID_SEG_PR&t;&t;0x06000000
DECL|macro|MID_SEG_PR_SHIFT
mdefine_line|#define MID_SEG_PR_SHIFT&t;25
DECL|macro|MID_SEG_AAL5
mdefine_line|#define MID_SEG_AAL5&t;&t;0x08000000
DECL|macro|MID_SEG_ID
mdefine_line|#define MID_SEG_ID&t;&t;0xf0000000
DECL|macro|MID_SEG_ID_SHIFT
mdefine_line|#define MID_SEG_ID_SHIFT&t;28
DECL|macro|MID_SEG_MAX_RATE
mdefine_line|#define MID_SEG_MAX_RATE&t;63
DECL|macro|MID_SEG_CLP
mdefine_line|#define MID_SEG_CLP&t;&t;0x00000001
DECL|macro|MID_SEG_PTI
mdefine_line|#define MID_SEG_PTI&t;&t;0x0000000e
DECL|macro|MID_SEG_PTI_SHIFT
mdefine_line|#define MID_SEG_PTI_SHIFT&t;1
DECL|macro|MID_SEG_VCI
mdefine_line|#define MID_SEG_VCI&t;&t;0x00003ff0
DECL|macro|MID_SEG_VCI_SHIFT
mdefine_line|#define MID_SEG_VCI_SHIFT&t;4
DECL|macro|MID_SEG_TX_ID
mdefine_line|#define MID_SEG_TX_ID&t;&t;0xb&t;&t;/* constant identifier */
multiline_comment|/*&n; * DMA entry&n; */
DECL|macro|MID_DMA_COUNT
mdefine_line|#define MID_DMA_COUNT&t;&t;0xffff0000
DECL|macro|MID_DMA_COUNT_SHIFT
mdefine_line|#define MID_DMA_COUNT_SHIFT&t;16
DECL|macro|MID_DMA_END
mdefine_line|#define MID_DMA_END&t;&t;0x00000020
DECL|macro|MID_DMA_TYPE
mdefine_line|#define MID_DMA_TYPE&t;&t;0x0000000f
DECL|macro|MID_DT_JK
mdefine_line|#define MID_DT_JK&t;0x3
DECL|macro|MID_DT_WORD
mdefine_line|#define MID_DT_WORD&t;0x0
DECL|macro|MID_DT_2W
mdefine_line|#define MID_DT_2W&t;0x7
DECL|macro|MID_DT_4W
mdefine_line|#define MID_DT_4W&t;0x4
DECL|macro|MID_DT_8W
mdefine_line|#define MID_DT_8W&t;0x5
DECL|macro|MID_DT_16W
mdefine_line|#define MID_DT_16W&t;0x6
DECL|macro|MID_DT_2WM
mdefine_line|#define MID_DT_2WM&t;0xf
DECL|macro|MID_DT_4WM
mdefine_line|#define MID_DT_4WM&t;0xc
DECL|macro|MID_DT_8WM
mdefine_line|#define MID_DT_8WM&t;0xd
DECL|macro|MID_DT_16WM
mdefine_line|#define MID_DT_16WM&t;0xe
multiline_comment|/* only for RX*/
DECL|macro|MID_DMA_VCI
mdefine_line|#define MID_DMA_VCI&t;&t;0x0000ffc0
DECL|macro|MID_DMA_VCI_SHIFT
mdefine_line|#define&t;MID_DMA_VCI_SHIFT&t;6
multiline_comment|/* only for TX */
DECL|macro|MID_DMA_CHAN
mdefine_line|#define MID_DMA_CHAN&t;&t;0x000001c0
DECL|macro|MID_DMA_CHAN_SHIFT
mdefine_line|#define MID_DMA_CHAN_SHIFT&t;6
DECL|macro|MID_DT_BYTE
mdefine_line|#define MID_DT_BYTE&t;0x1
DECL|macro|MID_DT_HWORD
mdefine_line|#define MID_DT_HWORD&t;0x2
macro_line|#endif
eof
