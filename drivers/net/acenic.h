macro_line|#ifndef _ACENIC_H_
DECL|macro|_ACENIC_H_
mdefine_line|#define _ACENIC_H_
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Generate TX index update each time, when TX ring is closed.&n; * Normally, this is not useful, because results in more dma (and irqs&n; * without TX_COAL_INTS_ONLY).&n; */
DECL|macro|USE_TX_COAL_NOW
mdefine_line|#define USE_TX_COAL_NOW&t; 0
macro_line|#ifndef MAX_SKB_FRAGS
DECL|macro|MAX_SKB_FRAGS
mdefine_line|#define MAX_SKB_FRAGS 0
macro_line|#endif
multiline_comment|/*&n; * Addressing:&n; *&n; * The Tigon uses 64-bit host addresses, regardless of their actual&n; * length, and it expects a big-endian format. For 32 bit systems the&n; * upper 32 bits of the address are simply ignored (zero), however for&n; * little endian 64 bit systems (Alpha) this looks strange with the&n; * two parts of the address word being swapped.&n; *&n; * The addresses are split in two 32 bit words for all architectures&n; * as some of them are in PCI shared memory and it is necessary to use&n; * readl/writel to access them.&n; *&n; * The addressing code is derived from Pete Wyckoff&squot;s work, but&n; * modified to deal properly with readl/writel usage.&n; */
DECL|struct|ace_regs
r_struct
id|ace_regs
(brace
DECL|member|pad0
id|u32
id|pad0
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* PCI control registers */
DECL|member|HostCtrl
id|u32
id|HostCtrl
suffix:semicolon
multiline_comment|/* 0x40 */
DECL|member|LocalCtrl
id|u32
id|LocalCtrl
suffix:semicolon
DECL|member|pad1
id|u32
id|pad1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|MiscCfg
id|u32
id|MiscCfg
suffix:semicolon
multiline_comment|/* 0x50 */
DECL|member|pad2
id|u32
id|pad2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|PciState
id|u32
id|PciState
suffix:semicolon
DECL|member|pad3
id|u32
id|pad3
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x60 */
DECL|member|WinBase
id|u32
id|WinBase
suffix:semicolon
DECL|member|WinData
id|u32
id|WinData
suffix:semicolon
DECL|member|pad4
id|u32
id|pad4
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* 0x70 */
DECL|member|DmaWriteState
id|u32
id|DmaWriteState
suffix:semicolon
multiline_comment|/* 0xa0 */
DECL|member|pad5
id|u32
id|pad5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|DmaReadState
id|u32
id|DmaReadState
suffix:semicolon
multiline_comment|/* 0xb0 */
DECL|member|pad6
id|u32
id|pad6
(braket
l_int|26
)braket
suffix:semicolon
DECL|member|AssistState
id|u32
id|AssistState
suffix:semicolon
DECL|member|pad7
id|u32
id|pad7
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x120 */
DECL|member|CpuCtrl
id|u32
id|CpuCtrl
suffix:semicolon
multiline_comment|/* 0x140 */
DECL|member|Pc
id|u32
id|Pc
suffix:semicolon
DECL|member|pad8
id|u32
id|pad8
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|SramAddr
id|u32
id|SramAddr
suffix:semicolon
multiline_comment|/* 0x154 */
DECL|member|SramData
id|u32
id|SramData
suffix:semicolon
DECL|member|pad9
id|u32
id|pad9
(braket
l_int|49
)braket
suffix:semicolon
DECL|member|MacRxState
id|u32
id|MacRxState
suffix:semicolon
multiline_comment|/* 0x220 */
DECL|member|pad10
id|u32
id|pad10
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|CpuBCtrl
id|u32
id|CpuBCtrl
suffix:semicolon
multiline_comment|/* 0x240 */
DECL|member|PcB
id|u32
id|PcB
suffix:semicolon
DECL|member|pad11
id|u32
id|pad11
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|SramBAddr
id|u32
id|SramBAddr
suffix:semicolon
multiline_comment|/* 0x254 */
DECL|member|SramBData
id|u32
id|SramBData
suffix:semicolon
DECL|member|pad12
id|u32
id|pad12
(braket
l_int|105
)braket
suffix:semicolon
DECL|member|pad13
id|u32
id|pad13
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 0x400 */
DECL|member|Stats
id|u32
id|Stats
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|Mb0Hi
id|u32
id|Mb0Hi
suffix:semicolon
multiline_comment|/* 0x500 */
DECL|member|Mb0Lo
id|u32
id|Mb0Lo
suffix:semicolon
DECL|member|Mb1Hi
id|u32
id|Mb1Hi
suffix:semicolon
DECL|member|CmdPrd
id|u32
id|CmdPrd
suffix:semicolon
DECL|member|Mb2Hi
id|u32
id|Mb2Hi
suffix:semicolon
DECL|member|TxPrd
id|u32
id|TxPrd
suffix:semicolon
DECL|member|Mb3Hi
id|u32
id|Mb3Hi
suffix:semicolon
DECL|member|RxStdPrd
id|u32
id|RxStdPrd
suffix:semicolon
DECL|member|Mb4Hi
id|u32
id|Mb4Hi
suffix:semicolon
DECL|member|RxJumboPrd
id|u32
id|RxJumboPrd
suffix:semicolon
DECL|member|Mb5Hi
id|u32
id|Mb5Hi
suffix:semicolon
DECL|member|RxMiniPrd
id|u32
id|RxMiniPrd
suffix:semicolon
DECL|member|Mb6Hi
id|u32
id|Mb6Hi
suffix:semicolon
DECL|member|Mb6Lo
id|u32
id|Mb6Lo
suffix:semicolon
DECL|member|Mb7Hi
id|u32
id|Mb7Hi
suffix:semicolon
DECL|member|Mb7Lo
id|u32
id|Mb7Lo
suffix:semicolon
DECL|member|Mb8Hi
id|u32
id|Mb8Hi
suffix:semicolon
DECL|member|Mb8Lo
id|u32
id|Mb8Lo
suffix:semicolon
DECL|member|Mb9Hi
id|u32
id|Mb9Hi
suffix:semicolon
DECL|member|Mb9Lo
id|u32
id|Mb9Lo
suffix:semicolon
DECL|member|MbAHi
id|u32
id|MbAHi
suffix:semicolon
DECL|member|MbALo
id|u32
id|MbALo
suffix:semicolon
DECL|member|MbBHi
id|u32
id|MbBHi
suffix:semicolon
DECL|member|MbBLo
id|u32
id|MbBLo
suffix:semicolon
DECL|member|MbCHi
id|u32
id|MbCHi
suffix:semicolon
DECL|member|MbCLo
id|u32
id|MbCLo
suffix:semicolon
DECL|member|MbDHi
id|u32
id|MbDHi
suffix:semicolon
DECL|member|MbDLo
id|u32
id|MbDLo
suffix:semicolon
DECL|member|MbEHi
id|u32
id|MbEHi
suffix:semicolon
DECL|member|MbELo
id|u32
id|MbELo
suffix:semicolon
DECL|member|MbFHi
id|u32
id|MbFHi
suffix:semicolon
DECL|member|MbFLo
id|u32
id|MbFLo
suffix:semicolon
DECL|member|pad14
id|u32
id|pad14
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|MacAddrHi
id|u32
id|MacAddrHi
suffix:semicolon
multiline_comment|/* 0x600 */
DECL|member|MacAddrLo
id|u32
id|MacAddrLo
suffix:semicolon
DECL|member|InfoPtrHi
id|u32
id|InfoPtrHi
suffix:semicolon
DECL|member|InfoPtrLo
id|u32
id|InfoPtrLo
suffix:semicolon
DECL|member|MultiCastHi
id|u32
id|MultiCastHi
suffix:semicolon
multiline_comment|/* 0x610 */
DECL|member|MultiCastLo
id|u32
id|MultiCastLo
suffix:semicolon
DECL|member|ModeStat
id|u32
id|ModeStat
suffix:semicolon
DECL|member|DmaReadCfg
id|u32
id|DmaReadCfg
suffix:semicolon
DECL|member|DmaWriteCfg
id|u32
id|DmaWriteCfg
suffix:semicolon
multiline_comment|/* 0x620 */
DECL|member|TxBufRat
id|u32
id|TxBufRat
suffix:semicolon
DECL|member|EvtCsm
id|u32
id|EvtCsm
suffix:semicolon
DECL|member|CmdCsm
id|u32
id|CmdCsm
suffix:semicolon
DECL|member|TuneRxCoalTicks
id|u32
id|TuneRxCoalTicks
suffix:semicolon
multiline_comment|/* 0x630 */
DECL|member|TuneTxCoalTicks
id|u32
id|TuneTxCoalTicks
suffix:semicolon
DECL|member|TuneStatTicks
id|u32
id|TuneStatTicks
suffix:semicolon
DECL|member|TuneMaxTxDesc
id|u32
id|TuneMaxTxDesc
suffix:semicolon
DECL|member|TuneMaxRxDesc
id|u32
id|TuneMaxRxDesc
suffix:semicolon
multiline_comment|/* 0x640 */
DECL|member|TuneTrace
id|u32
id|TuneTrace
suffix:semicolon
DECL|member|TuneLink
id|u32
id|TuneLink
suffix:semicolon
DECL|member|TuneFastLink
id|u32
id|TuneFastLink
suffix:semicolon
DECL|member|TracePtr
id|u32
id|TracePtr
suffix:semicolon
multiline_comment|/* 0x650 */
DECL|member|TraceStrt
id|u32
id|TraceStrt
suffix:semicolon
DECL|member|TraceLen
id|u32
id|TraceLen
suffix:semicolon
DECL|member|IfIdx
id|u32
id|IfIdx
suffix:semicolon
DECL|member|IfMtu
id|u32
id|IfMtu
suffix:semicolon
multiline_comment|/* 0x660 */
DECL|member|MaskInt
id|u32
id|MaskInt
suffix:semicolon
DECL|member|GigLnkState
id|u32
id|GigLnkState
suffix:semicolon
DECL|member|FastLnkState
id|u32
id|FastLnkState
suffix:semicolon
DECL|member|pad16
id|u32
id|pad16
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x670 */
DECL|member|RxRetCsm
id|u32
id|RxRetCsm
suffix:semicolon
multiline_comment|/* 0x680 */
DECL|member|pad17
id|u32
id|pad17
(braket
l_int|31
)braket
suffix:semicolon
DECL|member|CmdRng
id|u32
id|CmdRng
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* 0x700 */
DECL|member|Window
id|u32
id|Window
(braket
l_int|0x200
)braket
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|addrhi
id|u32
id|addrhi
suffix:semicolon
DECL|member|addrlo
id|u32
id|addrlo
suffix:semicolon
DECL|typedef|aceaddr
)brace
id|aceaddr
suffix:semicolon
DECL|macro|ACE_WINDOW_SIZE
mdefine_line|#define ACE_WINDOW_SIZE&t;0x800
DECL|macro|ACE_JUMBO_MTU
mdefine_line|#define ACE_JUMBO_MTU 9000
DECL|macro|ACE_STD_MTU
mdefine_line|#define ACE_STD_MTU 1500
DECL|macro|ACE_TRACE_SIZE
mdefine_line|#define ACE_TRACE_SIZE 0x8000
multiline_comment|/*&n; * Host control register bits.&n; */
DECL|macro|IN_INT
mdefine_line|#define IN_INT&t;&t;0x01
DECL|macro|CLR_INT
mdefine_line|#define CLR_INT&t;&t;0x02
DECL|macro|HW_RESET
mdefine_line|#define HW_RESET&t;0x08
DECL|macro|BYTE_SWAP
mdefine_line|#define BYTE_SWAP&t;0x10
DECL|macro|WORD_SWAP
mdefine_line|#define WORD_SWAP&t;0x20
DECL|macro|MASK_INTS
mdefine_line|#define MASK_INTS&t;0x40
multiline_comment|/*&n; * Local control register bits.&n; */
DECL|macro|EEPROM_DATA_IN
mdefine_line|#define EEPROM_DATA_IN&t;&t;0x800000
DECL|macro|EEPROM_DATA_OUT
mdefine_line|#define EEPROM_DATA_OUT&t;&t;0x400000
DECL|macro|EEPROM_WRITE_ENABLE
mdefine_line|#define EEPROM_WRITE_ENABLE&t;0x200000
DECL|macro|EEPROM_CLK_OUT
mdefine_line|#define EEPROM_CLK_OUT&t;&t;0x100000
DECL|macro|EEPROM_BASE
mdefine_line|#define EEPROM_BASE&t;&t;0xa0000000
DECL|macro|EEPROM_WRITE_SELECT
mdefine_line|#define EEPROM_WRITE_SELECT&t;0xa0
DECL|macro|EEPROM_READ_SELECT
mdefine_line|#define EEPROM_READ_SELECT&t;0xa1
DECL|macro|SRAM_BANK_512K
mdefine_line|#define SRAM_BANK_512K&t;&t;0x200
multiline_comment|/*&n; * udelay() values for when clocking the eeprom&n; */
DECL|macro|ACE_SHORT_DELAY
mdefine_line|#define ACE_SHORT_DELAY&t;&t;2
DECL|macro|ACE_LONG_DELAY
mdefine_line|#define ACE_LONG_DELAY&t;&t;4
multiline_comment|/*&n; * Misc Config bits&n; */
DECL|macro|SYNC_SRAM_TIMING
mdefine_line|#define SYNC_SRAM_TIMING&t;0x100000
multiline_comment|/*&n; * CPU state bits.&n; */
DECL|macro|CPU_RESET
mdefine_line|#define CPU_RESET&t;&t;0x01
DECL|macro|CPU_TRACE
mdefine_line|#define CPU_TRACE&t;&t;0x02
DECL|macro|CPU_PROM_FAILED
mdefine_line|#define CPU_PROM_FAILED&t;&t;0x10
DECL|macro|CPU_HALT
mdefine_line|#define CPU_HALT&t;&t;0x00010000
DECL|macro|CPU_HALTED
mdefine_line|#define CPU_HALTED&t;&t;0xffff0000
multiline_comment|/*&n; * PCI State bits.&n; */
DECL|macro|DMA_READ_MAX_4
mdefine_line|#define DMA_READ_MAX_4&t;&t;0x04
DECL|macro|DMA_READ_MAX_16
mdefine_line|#define DMA_READ_MAX_16&t;&t;0x08
DECL|macro|DMA_READ_MAX_32
mdefine_line|#define DMA_READ_MAX_32&t;&t;0x0c
DECL|macro|DMA_READ_MAX_64
mdefine_line|#define DMA_READ_MAX_64&t;&t;0x10
DECL|macro|DMA_READ_MAX_128
mdefine_line|#define DMA_READ_MAX_128&t;0x14
DECL|macro|DMA_READ_MAX_256
mdefine_line|#define DMA_READ_MAX_256&t;0x18
DECL|macro|DMA_READ_MAX_1K
mdefine_line|#define DMA_READ_MAX_1K&t;&t;0x1c
DECL|macro|DMA_WRITE_MAX_4
mdefine_line|#define DMA_WRITE_MAX_4&t;&t;0x20
DECL|macro|DMA_WRITE_MAX_16
mdefine_line|#define DMA_WRITE_MAX_16&t;0x40
DECL|macro|DMA_WRITE_MAX_32
mdefine_line|#define DMA_WRITE_MAX_32&t;0x60
DECL|macro|DMA_WRITE_MAX_64
mdefine_line|#define DMA_WRITE_MAX_64&t;0x80
DECL|macro|DMA_WRITE_MAX_128
mdefine_line|#define DMA_WRITE_MAX_128&t;0xa0
DECL|macro|DMA_WRITE_MAX_256
mdefine_line|#define DMA_WRITE_MAX_256&t;0xc0
DECL|macro|DMA_WRITE_MAX_1K
mdefine_line|#define DMA_WRITE_MAX_1K&t;0xe0
DECL|macro|DMA_READ_WRITE_MASK
mdefine_line|#define DMA_READ_WRITE_MASK&t;0xfc
DECL|macro|MEM_READ_MULTIPLE
mdefine_line|#define MEM_READ_MULTIPLE&t;0x00020000
DECL|macro|PCI_66MHZ
mdefine_line|#define PCI_66MHZ&t;&t;0x00080000
DECL|macro|PCI_32BIT
mdefine_line|#define PCI_32BIT&t;&t;0x00100000
DECL|macro|DMA_WRITE_ALL_ALIGN
mdefine_line|#define DMA_WRITE_ALL_ALIGN&t;0x00800000
DECL|macro|READ_CMD_MEM
mdefine_line|#define READ_CMD_MEM&t;&t;0x06000000
DECL|macro|WRITE_CMD_MEM
mdefine_line|#define WRITE_CMD_MEM&t;&t;0x70000000
multiline_comment|/*&n; * Mode status&n; */
DECL|macro|ACE_BYTE_SWAP_BD
mdefine_line|#define ACE_BYTE_SWAP_BD&t;0x02
DECL|macro|ACE_WORD_SWAP_BD
mdefine_line|#define ACE_WORD_SWAP_BD&t;0x04&t;&t;/* not actually used */
DECL|macro|ACE_WARN
mdefine_line|#define ACE_WARN&t;&t;0x08
DECL|macro|ACE_BYTE_SWAP_DMA
mdefine_line|#define ACE_BYTE_SWAP_DMA&t;0x10
DECL|macro|ACE_NO_JUMBO_FRAG
mdefine_line|#define ACE_NO_JUMBO_FRAG&t;0x200
DECL|macro|ACE_FATAL
mdefine_line|#define ACE_FATAL&t;&t;0x40000000
multiline_comment|/*&n; * DMA config&n; */
DECL|macro|DMA_THRESH_1W
mdefine_line|#define DMA_THRESH_1W&t;&t;0x10
DECL|macro|DMA_THRESH_2W
mdefine_line|#define DMA_THRESH_2W&t;&t;0x20
DECL|macro|DMA_THRESH_4W
mdefine_line|#define DMA_THRESH_4W&t;&t;0x40
DECL|macro|DMA_THRESH_8W
mdefine_line|#define DMA_THRESH_8W&t;&t;0x80
DECL|macro|DMA_THRESH_16W
mdefine_line|#define DMA_THRESH_16W&t;&t;0x100
DECL|macro|DMA_THRESH_32W
mdefine_line|#define DMA_THRESH_32W&t;&t;0x0&t;/* not described in doc, but exists. */
multiline_comment|/*&n; * Tuning parameters&n; */
DECL|macro|TICKS_PER_SEC
mdefine_line|#define TICKS_PER_SEC&t;&t;1000000
multiline_comment|/*&n; * Link bits&n; */
DECL|macro|LNK_PREF
mdefine_line|#define LNK_PREF&t;&t;0x00008000
DECL|macro|LNK_10MB
mdefine_line|#define LNK_10MB&t;&t;0x00010000
DECL|macro|LNK_100MB
mdefine_line|#define LNK_100MB&t;&t;0x00020000
DECL|macro|LNK_1000MB
mdefine_line|#define LNK_1000MB&t;&t;0x00040000
DECL|macro|LNK_FULL_DUPLEX
mdefine_line|#define LNK_FULL_DUPLEX&t;&t;0x00080000
DECL|macro|LNK_HALF_DUPLEX
mdefine_line|#define LNK_HALF_DUPLEX&t;&t;0x00100000
DECL|macro|LNK_TX_FLOW_CTL_Y
mdefine_line|#define LNK_TX_FLOW_CTL_Y&t;0x00200000
DECL|macro|LNK_NEG_ADVANCED
mdefine_line|#define LNK_NEG_ADVANCED&t;0x00400000
DECL|macro|LNK_RX_FLOW_CTL_Y
mdefine_line|#define LNK_RX_FLOW_CTL_Y&t;0x00800000
DECL|macro|LNK_NIC
mdefine_line|#define LNK_NIC&t;&t;&t;0x01000000
DECL|macro|LNK_JAM
mdefine_line|#define LNK_JAM&t;&t;&t;0x02000000
DECL|macro|LNK_JUMBO
mdefine_line|#define LNK_JUMBO&t;&t;0x04000000
DECL|macro|LNK_ALTEON
mdefine_line|#define LNK_ALTEON&t;&t;0x08000000
DECL|macro|LNK_NEG_FCTL
mdefine_line|#define LNK_NEG_FCTL&t;&t;0x10000000
DECL|macro|LNK_NEGOTIATE
mdefine_line|#define LNK_NEGOTIATE&t;&t;0x20000000
DECL|macro|LNK_ENABLE
mdefine_line|#define LNK_ENABLE&t;&t;0x40000000
DECL|macro|LNK_UP
mdefine_line|#define LNK_UP&t;&t;&t;0x80000000
multiline_comment|/*&n; * Event definitions&n; */
DECL|macro|EVT_RING_ENTRIES
mdefine_line|#define EVT_RING_ENTRIES&t;256
DECL|macro|EVT_RING_SIZE
mdefine_line|#define EVT_RING_SIZE&t;(EVT_RING_ENTRIES * sizeof(struct event))
DECL|struct|event
r_struct
id|event
(brace
macro_line|#ifdef __LITTLE_ENDIAN_BITFIELD
DECL|member|idx
id|u32
id|idx
suffix:colon
l_int|12
suffix:semicolon
DECL|member|code
id|u32
id|code
suffix:colon
l_int|12
suffix:semicolon
DECL|member|evt
id|u32
id|evt
suffix:colon
l_int|8
suffix:semicolon
macro_line|#else
id|u32
id|evt
suffix:colon
l_int|8
suffix:semicolon
id|u32
id|code
suffix:colon
l_int|12
suffix:semicolon
id|u32
id|idx
suffix:colon
l_int|12
suffix:semicolon
macro_line|#endif
DECL|member|pad
id|u32
id|pad
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Events&n; */
DECL|macro|E_FW_RUNNING
mdefine_line|#define E_FW_RUNNING&t;&t;0x01
DECL|macro|E_STATS_UPDATED
mdefine_line|#define E_STATS_UPDATED&t;&t;0x04
DECL|macro|E_STATS_UPDATE
mdefine_line|#define E_STATS_UPDATE&t;&t;0x04
DECL|macro|E_LNK_STATE
mdefine_line|#define E_LNK_STATE&t;&t;0x06
DECL|macro|E_C_LINK_UP
mdefine_line|#define E_C_LINK_UP&t;&t;0x01
DECL|macro|E_C_LINK_DOWN
mdefine_line|#define E_C_LINK_DOWN&t;&t;0x02
DECL|macro|E_C_LINK_10_100
mdefine_line|#define E_C_LINK_10_100&t;&t;0x03
DECL|macro|E_ERROR
mdefine_line|#define E_ERROR&t;&t;&t;0x07
DECL|macro|E_C_ERR_INVAL_CMD
mdefine_line|#define E_C_ERR_INVAL_CMD&t;0x01
DECL|macro|E_C_ERR_UNIMP_CMD
mdefine_line|#define E_C_ERR_UNIMP_CMD&t;0x02
DECL|macro|E_C_ERR_BAD_CFG
mdefine_line|#define E_C_ERR_BAD_CFG&t;&t;0x03
DECL|macro|E_MCAST_LIST
mdefine_line|#define E_MCAST_LIST&t;&t;0x08
DECL|macro|E_C_MCAST_ADDR_ADD
mdefine_line|#define E_C_MCAST_ADDR_ADD&t;0x01
DECL|macro|E_C_MCAST_ADDR_DEL
mdefine_line|#define E_C_MCAST_ADDR_DEL&t;0x02
DECL|macro|E_RESET_JUMBO_RNG
mdefine_line|#define E_RESET_JUMBO_RNG&t;0x09
multiline_comment|/*&n; * Commands&n; */
DECL|macro|CMD_RING_ENTRIES
mdefine_line|#define CMD_RING_ENTRIES&t;64
DECL|struct|cmd
r_struct
id|cmd
(brace
macro_line|#ifdef __LITTLE_ENDIAN_BITFIELD
DECL|member|idx
id|u32
id|idx
suffix:colon
l_int|12
suffix:semicolon
DECL|member|code
id|u32
id|code
suffix:colon
l_int|12
suffix:semicolon
DECL|member|evt
id|u32
id|evt
suffix:colon
l_int|8
suffix:semicolon
macro_line|#else
id|u32
id|evt
suffix:colon
l_int|8
suffix:semicolon
id|u32
id|code
suffix:colon
l_int|12
suffix:semicolon
id|u32
id|idx
suffix:colon
l_int|12
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|C_HOST_STATE
mdefine_line|#define C_HOST_STATE&t;&t;0x01
DECL|macro|C_C_STACK_UP
mdefine_line|#define C_C_STACK_UP&t;&t;0x01
DECL|macro|C_C_STACK_DOWN
mdefine_line|#define C_C_STACK_DOWN&t;&t;0x02
DECL|macro|C_FDR_FILTERING
mdefine_line|#define C_FDR_FILTERING&t;&t;0x02
DECL|macro|C_C_FDR_FILT_ENABLE
mdefine_line|#define C_C_FDR_FILT_ENABLE&t;0x01
DECL|macro|C_C_FDR_FILT_DISABLE
mdefine_line|#define C_C_FDR_FILT_DISABLE&t;0x02
DECL|macro|C_SET_RX_PRD_IDX
mdefine_line|#define C_SET_RX_PRD_IDX&t;0x03
DECL|macro|C_UPDATE_STATS
mdefine_line|#define C_UPDATE_STATS&t;&t;0x04
DECL|macro|C_RESET_JUMBO_RNG
mdefine_line|#define C_RESET_JUMBO_RNG&t;0x05
DECL|macro|C_ADD_MULTICAST_ADDR
mdefine_line|#define C_ADD_MULTICAST_ADDR&t;0x08
DECL|macro|C_DEL_MULTICAST_ADDR
mdefine_line|#define C_DEL_MULTICAST_ADDR&t;0x09
DECL|macro|C_SET_PROMISC_MODE
mdefine_line|#define C_SET_PROMISC_MODE&t;0x0a
DECL|macro|C_C_PROMISC_ENABLE
mdefine_line|#define C_C_PROMISC_ENABLE&t;0x01
DECL|macro|C_C_PROMISC_DISABLE
mdefine_line|#define C_C_PROMISC_DISABLE&t;0x02
DECL|macro|C_LNK_NEGOTIATION
mdefine_line|#define C_LNK_NEGOTIATION&t;0x0b
DECL|macro|C_C_NEGOTIATE_BOTH
mdefine_line|#define C_C_NEGOTIATE_BOTH&t;0x00
DECL|macro|C_C_NEGOTIATE_GIG
mdefine_line|#define C_C_NEGOTIATE_GIG&t;0x01
DECL|macro|C_C_NEGOTIATE_10_100
mdefine_line|#define C_C_NEGOTIATE_10_100&t;0x02
DECL|macro|C_SET_MAC_ADDR
mdefine_line|#define C_SET_MAC_ADDR&t;&t;0x0c
DECL|macro|C_CLEAR_PROFILE
mdefine_line|#define C_CLEAR_PROFILE&t;&t;0x0d
DECL|macro|C_SET_MULTICAST_MODE
mdefine_line|#define C_SET_MULTICAST_MODE&t;0x0e
DECL|macro|C_C_MCAST_ENABLE
mdefine_line|#define C_C_MCAST_ENABLE&t;0x01
DECL|macro|C_C_MCAST_DISABLE
mdefine_line|#define C_C_MCAST_DISABLE&t;0x02
DECL|macro|C_CLEAR_STATS
mdefine_line|#define C_CLEAR_STATS&t;&t;0x0f
DECL|macro|C_SET_RX_JUMBO_PRD_IDX
mdefine_line|#define C_SET_RX_JUMBO_PRD_IDX&t;0x10
DECL|macro|C_REFRESH_STATS
mdefine_line|#define C_REFRESH_STATS&t;&t;0x11
multiline_comment|/*&n; * Descriptor flags&n; */
DECL|macro|BD_FLG_TCP_UDP_SUM
mdefine_line|#define BD_FLG_TCP_UDP_SUM&t;0x01
DECL|macro|BD_FLG_IP_SUM
mdefine_line|#define BD_FLG_IP_SUM&t;&t;0x02
DECL|macro|BD_FLG_END
mdefine_line|#define BD_FLG_END&t;&t;0x04
DECL|macro|BD_FLG_JUMBO
mdefine_line|#define BD_FLG_JUMBO&t;&t;0x10
DECL|macro|BD_FLG_COAL_NOW
mdefine_line|#define BD_FLG_COAL_NOW&t;&t;0x800
DECL|macro|BD_FLG_MINI
mdefine_line|#define BD_FLG_MINI&t;&t;0x1000
multiline_comment|/*&n; * Ring Control block flags&n; */
DECL|macro|RCB_FLG_TCP_UDP_SUM
mdefine_line|#define RCB_FLG_TCP_UDP_SUM&t;0x01
DECL|macro|RCB_FLG_IP_SUM
mdefine_line|#define RCB_FLG_IP_SUM&t;&t;0x02
DECL|macro|RCB_FLG_NO_PSEUDO_HDR
mdefine_line|#define RCB_FLG_NO_PSEUDO_HDR&t;0x08
DECL|macro|RCB_FLG_VLAN_ASSIST
mdefine_line|#define RCB_FLG_VLAN_ASSIST&t;0x10
DECL|macro|RCB_FLG_COAL_INT_ONLY
mdefine_line|#define RCB_FLG_COAL_INT_ONLY&t;0x20
DECL|macro|RCB_FLG_TX_HOST_RING
mdefine_line|#define RCB_FLG_TX_HOST_RING&t;0x40
DECL|macro|RCB_FLG_IEEE_SNAP_SUM
mdefine_line|#define RCB_FLG_IEEE_SNAP_SUM&t;0x80
DECL|macro|RCB_FLG_EXT_RX_BD
mdefine_line|#define RCB_FLG_EXT_RX_BD&t;0x100
DECL|macro|RCB_FLG_RNG_DISABLE
mdefine_line|#define RCB_FLG_RNG_DISABLE&t;0x200
multiline_comment|/*&n; * TX ring&n; */
DECL|macro|TX_RING_ENTRIES
mdefine_line|#define TX_RING_ENTRIES&t;256&t;
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE&t;(TX_RING_ENTRIES * sizeof(struct tx_desc))
DECL|macro|TX_RING_BASE
mdefine_line|#define TX_RING_BASE&t;0x3800
DECL|struct|tx_desc
r_struct
id|tx_desc
(brace
DECL|member|addr
id|aceaddr
id|addr
suffix:semicolon
DECL|member|flagsize
id|u32
id|flagsize
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n; * This is in PCI shared mem and must be accessed with readl/writel&n; * real layout is:&n; */
macro_line|#if __LITTLE_ENDIAN
id|u16
id|flags
suffix:semicolon
id|u16
id|size
suffix:semicolon
id|u16
id|vlan
suffix:semicolon
id|u16
id|reserved
suffix:semicolon
macro_line|#else
id|u16
id|size
suffix:semicolon
id|u16
id|flags
suffix:semicolon
id|u16
id|reserved
suffix:semicolon
id|u16
id|vlan
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|member|vlanres
id|u32
id|vlanres
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RX_STD_RING_ENTRIES
mdefine_line|#define RX_STD_RING_ENTRIES&t;512
DECL|macro|RX_STD_RING_SIZE
mdefine_line|#define RX_STD_RING_SIZE&t;(RX_STD_RING_ENTRIES * sizeof(struct rx_desc))
DECL|macro|RX_JUMBO_RING_ENTRIES
mdefine_line|#define RX_JUMBO_RING_ENTRIES&t;256
DECL|macro|RX_JUMBO_RING_SIZE
mdefine_line|#define RX_JUMBO_RING_SIZE&t;(RX_JUMBO_RING_ENTRIES *sizeof(struct rx_desc))
DECL|macro|RX_MINI_RING_ENTRIES
mdefine_line|#define RX_MINI_RING_ENTRIES&t;1024
DECL|macro|RX_MINI_RING_SIZE
mdefine_line|#define RX_MINI_RING_SIZE&t;(RX_MINI_RING_ENTRIES *sizeof(struct rx_desc))
DECL|macro|RX_RETURN_RING_ENTRIES
mdefine_line|#define RX_RETURN_RING_ENTRIES&t;2048
DECL|macro|RX_RETURN_RING_SIZE
mdefine_line|#define RX_RETURN_RING_SIZE&t;(RX_MAX_RETURN_RING_ENTRIES * &bslash;&n;&t;&t;&t;&t; sizeof(struct rx_desc))
DECL|struct|rx_desc
r_struct
id|rx_desc
(brace
DECL|member|addr
id|aceaddr
id|addr
suffix:semicolon
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|idx
id|u16
id|idx
suffix:semicolon
macro_line|#else
DECL|member|idx
id|u16
id|idx
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|type
id|u16
id|type
suffix:semicolon
macro_line|#else
DECL|member|type
id|u16
id|type
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|tcp_udp_csum
id|u16
id|tcp_udp_csum
suffix:semicolon
DECL|member|ip_csum
id|u16
id|ip_csum
suffix:semicolon
macro_line|#else
DECL|member|ip_csum
id|u16
id|ip_csum
suffix:semicolon
DECL|member|tcp_udp_csum
id|u16
id|tcp_udp_csum
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|vlan
id|u16
id|vlan
suffix:semicolon
DECL|member|err_flags
id|u16
id|err_flags
suffix:semicolon
macro_line|#else
DECL|member|err_flags
id|u16
id|err_flags
suffix:semicolon
DECL|member|vlan
id|u16
id|vlan
suffix:semicolon
macro_line|#endif
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|opague
id|u32
id|opague
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This struct is shared with the NIC firmware.&n; */
DECL|struct|ring_ctrl
r_struct
id|ring_ctrl
(brace
DECL|member|rngptr
id|aceaddr
id|rngptr
suffix:semicolon
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|max_len
id|u16
id|max_len
suffix:semicolon
macro_line|#else
DECL|member|max_len
id|u16
id|max_len
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
macro_line|#endif
DECL|member|pad
id|u32
id|pad
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ace_mac_stats
r_struct
id|ace_mac_stats
(brace
DECL|member|excess_colls
id|u32
id|excess_colls
suffix:semicolon
DECL|member|coll_1
id|u32
id|coll_1
suffix:semicolon
DECL|member|coll_2
id|u32
id|coll_2
suffix:semicolon
DECL|member|coll_3
id|u32
id|coll_3
suffix:semicolon
DECL|member|coll_4
id|u32
id|coll_4
suffix:semicolon
DECL|member|coll_5
id|u32
id|coll_5
suffix:semicolon
DECL|member|coll_6
id|u32
id|coll_6
suffix:semicolon
DECL|member|coll_7
id|u32
id|coll_7
suffix:semicolon
DECL|member|coll_8
id|u32
id|coll_8
suffix:semicolon
DECL|member|coll_9
id|u32
id|coll_9
suffix:semicolon
DECL|member|coll_10
id|u32
id|coll_10
suffix:semicolon
DECL|member|coll_11
id|u32
id|coll_11
suffix:semicolon
DECL|member|coll_12
id|u32
id|coll_12
suffix:semicolon
DECL|member|coll_13
id|u32
id|coll_13
suffix:semicolon
DECL|member|coll_14
id|u32
id|coll_14
suffix:semicolon
DECL|member|coll_15
id|u32
id|coll_15
suffix:semicolon
DECL|member|late_coll
id|u32
id|late_coll
suffix:semicolon
DECL|member|defers
id|u32
id|defers
suffix:semicolon
DECL|member|crc_err
id|u32
id|crc_err
suffix:semicolon
DECL|member|underrun
id|u32
id|underrun
suffix:semicolon
DECL|member|crs_err
id|u32
id|crs_err
suffix:semicolon
DECL|member|pad
id|u32
id|pad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|drop_ula
id|u32
id|drop_ula
suffix:semicolon
DECL|member|drop_mc
id|u32
id|drop_mc
suffix:semicolon
DECL|member|drop_fc
id|u32
id|drop_fc
suffix:semicolon
DECL|member|drop_space
id|u32
id|drop_space
suffix:semicolon
DECL|member|coll
id|u32
id|coll
suffix:semicolon
DECL|member|kept_bc
id|u32
id|kept_bc
suffix:semicolon
DECL|member|kept_mc
id|u32
id|kept_mc
suffix:semicolon
DECL|member|kept_uc
id|u32
id|kept_uc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ace_info
r_struct
id|ace_info
(brace
r_union
(brace
DECL|member|stats
id|u32
id|stats
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|evt_ctrl
r_struct
id|ring_ctrl
id|evt_ctrl
suffix:semicolon
DECL|member|cmd_ctrl
r_struct
id|ring_ctrl
id|cmd_ctrl
suffix:semicolon
DECL|member|tx_ctrl
r_struct
id|ring_ctrl
id|tx_ctrl
suffix:semicolon
DECL|member|rx_std_ctrl
r_struct
id|ring_ctrl
id|rx_std_ctrl
suffix:semicolon
DECL|member|rx_jumbo_ctrl
r_struct
id|ring_ctrl
id|rx_jumbo_ctrl
suffix:semicolon
DECL|member|rx_mini_ctrl
r_struct
id|ring_ctrl
id|rx_mini_ctrl
suffix:semicolon
DECL|member|rx_return_ctrl
r_struct
id|ring_ctrl
id|rx_return_ctrl
suffix:semicolon
DECL|member|evt_prd_ptr
id|aceaddr
id|evt_prd_ptr
suffix:semicolon
DECL|member|rx_ret_prd_ptr
id|aceaddr
id|rx_ret_prd_ptr
suffix:semicolon
DECL|member|tx_csm_ptr
id|aceaddr
id|tx_csm_ptr
suffix:semicolon
DECL|member|stats2_ptr
id|aceaddr
id|stats2_ptr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_X86) || defined(CONFIG_PPC)
multiline_comment|/* Intel has null pci_unmap_single, no reasons to remember mapping. */
DECL|macro|DUMMY_PCI_UNMAP
mdefine_line|#define DUMMY_PCI_UNMAP
macro_line|#endif
DECL|struct|ring_info
r_struct
id|ring_info
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
macro_line|#ifndef DUMMY_PCI_UNMAP
DECL|member|mapping
id|dma_addr_t
id|mapping
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Funny... As soon as we add maplen on alpha, it starts to work&n; * much slower. Hmm... is it because struct does not fit to one cacheline?&n; * So, split tx_ring_info.&n; */
DECL|struct|tx_ring_info
r_struct
id|tx_ring_info
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
macro_line|#ifndef DUMMY_PCI_UNMAP
DECL|member|mapping
id|dma_addr_t
id|mapping
suffix:semicolon
DECL|member|maplen
r_int
id|maplen
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * struct ace_skb holding the rings of skb&squot;s. This is an awful lot of&n; * pointers, but I don&squot;t see any other smart mode to do this in an&n; * efficient manner ;-(&n; */
DECL|struct|ace_skb
r_struct
id|ace_skb
(brace
DECL|member|tx_skbuff
r_struct
id|tx_ring_info
id|tx_skbuff
(braket
id|TX_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|rx_std_skbuff
r_struct
id|ring_info
id|rx_std_skbuff
(braket
id|RX_STD_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|rx_mini_skbuff
r_struct
id|ring_info
id|rx_mini_skbuff
(braket
id|RX_MINI_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|rx_jumbo_skbuff
r_struct
id|ring_info
id|rx_jumbo_skbuff
(braket
id|RX_JUMBO_RING_ENTRIES
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Struct private for the AceNIC.&n; *&n; * Elements are grouped so variables used by the tx handling goes&n; * together, and will go into the same cache lines etc. in order to&n; * avoid cache line contention between the rx and tx handling on SMP.&n; *&n; * Frequently accessed variables are put at the beginning of the&n; * struct to help the compiler generate better/shorter code.&n; */
DECL|struct|ace_private
r_struct
id|ace_private
(brace
DECL|member|info
r_struct
id|ace_info
op_star
id|info
suffix:semicolon
DECL|member|regs
r_struct
id|ace_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* register base */
DECL|member|skb
r_struct
id|ace_skb
op_star
id|skb
suffix:semicolon
DECL|member|info_dma
id|dma_addr_t
id|info_dma
suffix:semicolon
multiline_comment|/* 32/64 bit */
DECL|member|version
DECL|member|link
r_int
id|version
comma
id|link
suffix:semicolon
DECL|member|promisc
DECL|member|mcast_all
r_int
id|promisc
comma
id|mcast_all
suffix:semicolon
multiline_comment|/*&n;&t; * TX elements&n;&t; */
DECL|member|tx_ring
r_struct
id|tx_desc
op_star
id|tx_ring
suffix:semicolon
DECL|member|tx_prd
id|u32
id|tx_prd
suffix:semicolon
DECL|member|tx_ret_csm
r_volatile
id|u32
id|tx_ret_csm
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/*&n;&t; * RX elements&n;&t; */
DECL|member|std_refill_busy
r_int
r_int
id|std_refill_busy
id|__attribute__
(paren
(paren
id|aligned
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
DECL|member|mini_refill_busy
DECL|member|jumbo_refill_busy
r_int
r_int
id|mini_refill_busy
comma
id|jumbo_refill_busy
suffix:semicolon
DECL|member|cur_rx_bufs
id|atomic_t
id|cur_rx_bufs
suffix:semicolon
DECL|member|cur_mini_bufs
id|atomic_t
id|cur_mini_bufs
suffix:semicolon
DECL|member|cur_jumbo_bufs
id|atomic_t
id|cur_jumbo_bufs
suffix:semicolon
DECL|member|rx_std_skbprd
DECL|member|rx_mini_skbprd
DECL|member|rx_jumbo_skbprd
id|u32
id|rx_std_skbprd
comma
id|rx_mini_skbprd
comma
id|rx_jumbo_skbprd
suffix:semicolon
DECL|member|cur_rx
id|u32
id|cur_rx
suffix:semicolon
DECL|member|rx_std_ring
r_struct
id|rx_desc
op_star
id|rx_std_ring
suffix:semicolon
DECL|member|rx_jumbo_ring
r_struct
id|rx_desc
op_star
id|rx_jumbo_ring
suffix:semicolon
DECL|member|rx_mini_ring
r_struct
id|rx_desc
op_star
id|rx_mini_ring
suffix:semicolon
DECL|member|rx_return_ring
r_struct
id|rx_desc
op_star
id|rx_return_ring
suffix:semicolon
DECL|member|tasklet_pending
DECL|member|jumbo
r_int
id|tasklet_pending
comma
id|jumbo
suffix:semicolon
DECL|member|ace_tasklet
r_struct
id|tasklet_struct
id|ace_tasklet
suffix:semicolon
DECL|member|evt_ring
r_struct
id|event
op_star
id|evt_ring
suffix:semicolon
DECL|member|evt_prd
DECL|member|rx_ret_prd
DECL|member|tx_csm
r_volatile
id|u32
op_star
id|evt_prd
comma
op_star
id|rx_ret_prd
comma
op_star
id|tx_csm
suffix:semicolon
DECL|member|tx_ring_dma
id|dma_addr_t
id|tx_ring_dma
suffix:semicolon
multiline_comment|/* 32/64 bit */
DECL|member|rx_ring_base_dma
id|dma_addr_t
id|rx_ring_base_dma
suffix:semicolon
DECL|member|evt_ring_dma
id|dma_addr_t
id|evt_ring_dma
suffix:semicolon
DECL|member|evt_prd_dma
DECL|member|rx_ret_prd_dma
DECL|member|tx_csm_dma
id|dma_addr_t
id|evt_prd_dma
comma
id|rx_ret_prd_dma
comma
id|tx_csm_dma
suffix:semicolon
DECL|member|trace_buf
r_int
r_char
op_star
id|trace_buf
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|next
r_struct
id|net_device
op_star
id|next
suffix:semicolon
DECL|member|fw_running
r_volatile
r_int
id|fw_running
suffix:semicolon
DECL|member|board_idx
r_int
id|board_idx
suffix:semicolon
DECL|member|pci_command
id|u16
id|pci_command
suffix:semicolon
DECL|member|pci_latency
id|u8
id|pci_latency
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|48
)braket
suffix:semicolon
macro_line|#ifdef INDEX_DEBUG
DECL|member|debug_lock
id|spinlock_t
id|debug_lock
id|__attribute__
(paren
(paren
id|aligned
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
suffix:semicolon
DECL|member|last_tx
DECL|member|last_std_rx
DECL|member|last_mini_rx
id|u32
id|last_tx
comma
id|last_std_rx
comma
id|last_mini_rx
suffix:semicolon
macro_line|#endif
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TX_RESERVED
mdefine_line|#define TX_RESERVED&t;MAX_SKB_FRAGS
DECL|function|tx_space
r_static
r_inline
r_int
id|tx_space
(paren
id|u32
id|csm
comma
id|u32
id|prd
)paren
(brace
r_return
(paren
id|csm
op_minus
id|prd
op_minus
l_int|1
)paren
op_amp
(paren
id|TX_RING_ENTRIES
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|macro|tx_free
mdefine_line|#define tx_free(ap) &t;&t;tx_space((ap)-&gt;tx_ret_csm, (ap)-&gt;tx_prd)
macro_line|#if MAX_SKB_FRAGS
DECL|macro|tx_ring_full
mdefine_line|#define tx_ring_full(csm, prd)&t;(tx_space(csm, prd) &lt;= TX_RESERVED)
macro_line|#else
DECL|macro|tx_ring_full
mdefine_line|#define tx_ring_full&t;&t;0
macro_line|#endif
DECL|function|set_aceaddr
r_static
r_inline
r_void
id|set_aceaddr
c_func
(paren
id|aceaddr
op_star
id|aa
comma
id|dma_addr_t
id|addr
)paren
(brace
r_int
r_int
id|baddr
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
macro_line|#ifdef ACE_64BIT_PTR
id|aa-&gt;addrlo
op_assign
id|baddr
op_amp
l_int|0xffffffff
suffix:semicolon
id|aa-&gt;addrhi
op_assign
id|baddr
op_rshift
l_int|32
suffix:semicolon
macro_line|#else
multiline_comment|/* Don&squot;t bother setting zero every time */
id|aa-&gt;addrlo
op_assign
id|baddr
suffix:semicolon
macro_line|#endif
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_inline
r_void
op_star
id|get_aceaddr
c_func
(paren
id|aceaddr
op_star
id|aa
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef ACE_64BIT_PTR
id|addr
op_assign
(paren
id|u64
)paren
id|aa-&gt;addrhi
op_lshift
l_int|32
op_or
id|aa-&gt;addrlo
suffix:semicolon
macro_line|#else
id|addr
op_assign
id|aa-&gt;addrlo
suffix:semicolon
macro_line|#endif
r_return
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
)brace
macro_line|#endif
DECL|function|ace_set_txprd
r_static
r_inline
r_void
id|ace_set_txprd
c_func
(paren
r_struct
id|ace_regs
op_star
id|regs
comma
r_struct
id|ace_private
op_star
id|ap
comma
id|u32
id|value
)paren
(brace
macro_line|#ifdef INDEX_DEBUG
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ap-&gt;debug_lock
comma
id|flags
)paren
suffix:semicolon
id|writel
c_func
(paren
id|value
comma
op_amp
id|regs-&gt;TxPrd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
id|ap-&gt;last_tx
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AceNIC RACE ALERT! writing identical value &quot;
l_string|&quot;to tx producer (%i)&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
id|ap-&gt;last_tx
op_assign
id|value
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ap-&gt;debug_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#else
id|writel
c_func
(paren
id|value
comma
op_amp
id|regs-&gt;TxPrd
)paren
suffix:semicolon
macro_line|#endif
id|wmb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Prototypes&n; */
r_static
r_int
id|ace_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ace_load_std_rx_ring
c_func
(paren
r_struct
id|ace_private
op_star
id|ap
comma
r_int
id|nr_bufs
)paren
suffix:semicolon
r_static
r_void
id|ace_load_mini_rx_ring
c_func
(paren
r_struct
id|ace_private
op_star
id|ap
comma
r_int
id|nr_bufs
)paren
suffix:semicolon
r_static
r_void
id|ace_load_jumbo_rx_ring
c_func
(paren
r_struct
id|ace_private
op_star
id|ap
comma
r_int
id|nr_bufs
)paren
suffix:semicolon
r_static
r_void
id|ace_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_int
id|ace_load_firmware
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ace_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ace_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ace_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ace_tasklet
c_func
(paren
r_int
r_int
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ace_dump_trace
c_func
(paren
r_struct
id|ace_private
op_star
id|ap
)paren
suffix:semicolon
r_static
r_void
id|ace_set_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ace_change_mtu
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|new_mtu
)paren
suffix:semicolon
r_static
r_int
id|ace_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
id|cmd
)paren
suffix:semicolon
r_static
r_int
id|ace_set_mac_addr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|p
)paren
suffix:semicolon
r_static
r_void
id|ace_set_rxtx_parms
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|jumbo
)paren
suffix:semicolon
r_static
r_int
id|ace_allocate_descriptors
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ace_free_descriptors
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ace_init_cleanup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device_stats
op_star
id|ace_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|read_eeprom_byte
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
macro_line|#endif /* _ACENIC_H_ */
eof
