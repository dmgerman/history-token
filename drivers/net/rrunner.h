macro_line|#ifndef _RRUNNER_H_
DECL|macro|_RRUNNER_H_
mdefine_line|#define _RRUNNER_H_
macro_line|#include&lt;linux/config.h&gt;
macro_line|#if ((BITS_PER_LONG != 32) &amp;&amp; (BITS_PER_LONG != 64))
macro_line|#error &quot;BITS_PER_LONG not defined or not valid&quot;
macro_line|#endif
DECL|struct|rr_regs
r_struct
id|rr_regs
(brace
DECL|member|pad0
id|u32
id|pad0
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|HostCtrl
id|u32
id|HostCtrl
suffix:semicolon
DECL|member|LocalCtrl
id|u32
id|LocalCtrl
suffix:semicolon
DECL|member|Pc
id|u32
id|Pc
suffix:semicolon
DECL|member|BrkPt
id|u32
id|BrkPt
suffix:semicolon
multiline_comment|/* Timer increments every 0.97 micro-seconds (unsigned int) */
DECL|member|Timer_Hi
id|u32
id|Timer_Hi
suffix:semicolon
DECL|member|Timer
id|u32
id|Timer
suffix:semicolon
DECL|member|TimerRef
id|u32
id|TimerRef
suffix:semicolon
DECL|member|PciState
id|u32
id|PciState
suffix:semicolon
DECL|member|Event
id|u32
id|Event
suffix:semicolon
DECL|member|MbEvent
id|u32
id|MbEvent
suffix:semicolon
DECL|member|WinBase
id|u32
id|WinBase
suffix:semicolon
DECL|member|WinData
id|u32
id|WinData
suffix:semicolon
DECL|member|RX_state
id|u32
id|RX_state
suffix:semicolon
DECL|member|TX_state
id|u32
id|TX_state
suffix:semicolon
DECL|member|Overhead
id|u32
id|Overhead
suffix:semicolon
DECL|member|ExtIo
id|u32
id|ExtIo
suffix:semicolon
DECL|member|DmaWriteHostHi
id|u32
id|DmaWriteHostHi
suffix:semicolon
DECL|member|DmaWriteHostLo
id|u32
id|DmaWriteHostLo
suffix:semicolon
DECL|member|pad1
id|u32
id|pad1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|DmaReadHostHi
id|u32
id|DmaReadHostHi
suffix:semicolon
DECL|member|DmaReadHostLo
id|u32
id|DmaReadHostLo
suffix:semicolon
DECL|member|pad2
id|u32
id|pad2
suffix:semicolon
DECL|member|DmaReadLen
id|u32
id|DmaReadLen
suffix:semicolon
DECL|member|DmaWriteState
id|u32
id|DmaWriteState
suffix:semicolon
DECL|member|DmaWriteLcl
id|u32
id|DmaWriteLcl
suffix:semicolon
DECL|member|DmaWriteIPchecksum
id|u32
id|DmaWriteIPchecksum
suffix:semicolon
DECL|member|DmaWriteLen
id|u32
id|DmaWriteLen
suffix:semicolon
DECL|member|DmaReadState
id|u32
id|DmaReadState
suffix:semicolon
DECL|member|DmaReadLcl
id|u32
id|DmaReadLcl
suffix:semicolon
DECL|member|DmaReadIPchecksum
id|u32
id|DmaReadIPchecksum
suffix:semicolon
DECL|member|pad3
id|u32
id|pad3
suffix:semicolon
DECL|member|RxBase
id|u32
id|RxBase
suffix:semicolon
DECL|member|RxPrd
id|u32
id|RxPrd
suffix:semicolon
DECL|member|RxCon
id|u32
id|RxCon
suffix:semicolon
DECL|member|pad4
id|u32
id|pad4
suffix:semicolon
DECL|member|TxBase
id|u32
id|TxBase
suffix:semicolon
DECL|member|TxPrd
id|u32
id|TxPrd
suffix:semicolon
DECL|member|TxCon
id|u32
id|TxCon
suffix:semicolon
DECL|member|pad5
id|u32
id|pad5
suffix:semicolon
DECL|member|RxIndPro
id|u32
id|RxIndPro
suffix:semicolon
DECL|member|RxIndCon
id|u32
id|RxIndCon
suffix:semicolon
DECL|member|RxIndRef
id|u32
id|RxIndRef
suffix:semicolon
DECL|member|pad6
id|u32
id|pad6
suffix:semicolon
DECL|member|TxIndPro
id|u32
id|TxIndPro
suffix:semicolon
DECL|member|TxIndCon
id|u32
id|TxIndCon
suffix:semicolon
DECL|member|TxIndRef
id|u32
id|TxIndRef
suffix:semicolon
DECL|member|pad7
id|u32
id|pad7
(braket
l_int|17
)braket
suffix:semicolon
DECL|member|DrCmndPro
id|u32
id|DrCmndPro
suffix:semicolon
DECL|member|DrCmndCon
id|u32
id|DrCmndCon
suffix:semicolon
DECL|member|DrCmndRef
id|u32
id|DrCmndRef
suffix:semicolon
DECL|member|pad8
id|u32
id|pad8
suffix:semicolon
DECL|member|DwCmndPro
id|u32
id|DwCmndPro
suffix:semicolon
DECL|member|DwCmndCon
id|u32
id|DwCmndCon
suffix:semicolon
DECL|member|DwCmndRef
id|u32
id|DwCmndRef
suffix:semicolon
DECL|member|AssistState
id|u32
id|AssistState
suffix:semicolon
DECL|member|DrDataPro
id|u32
id|DrDataPro
suffix:semicolon
DECL|member|DrDataCon
id|u32
id|DrDataCon
suffix:semicolon
DECL|member|DrDataRef
id|u32
id|DrDataRef
suffix:semicolon
DECL|member|pad9
id|u32
id|pad9
suffix:semicolon
DECL|member|DwDataPro
id|u32
id|DwDataPro
suffix:semicolon
DECL|member|DwDataCon
id|u32
id|DwDataCon
suffix:semicolon
DECL|member|DwDataRef
id|u32
id|DwDataRef
suffix:semicolon
DECL|member|pad10
id|u32
id|pad10
(braket
l_int|33
)braket
suffix:semicolon
DECL|member|EvtCon
id|u32
id|EvtCon
suffix:semicolon
DECL|member|pad11
id|u32
id|pad11
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|TxPi
id|u32
id|TxPi
suffix:semicolon
DECL|member|IpRxPi
id|u32
id|IpRxPi
suffix:semicolon
DECL|member|pad11a
id|u32
id|pad11a
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|CmdRing
id|u32
id|CmdRing
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* The ULA is in two registers the high order two bytes of the first&n; * word contain the RunCode features.&n; * ula0&t;&t;res&t;res&t;byte0&t;byte1&n; * ula1&t;&t;byte2&t;byte3&t;byte4&t;byte5&n; */
DECL|member|Ula0
id|u32
id|Ula0
suffix:semicolon
DECL|member|Ula1
id|u32
id|Ula1
suffix:semicolon
DECL|member|RxRingHi
id|u32
id|RxRingHi
suffix:semicolon
DECL|member|RxRingLo
id|u32
id|RxRingLo
suffix:semicolon
DECL|member|InfoPtrHi
id|u32
id|InfoPtrHi
suffix:semicolon
DECL|member|InfoPtrLo
id|u32
id|InfoPtrLo
suffix:semicolon
DECL|member|Mode
id|u32
id|Mode
suffix:semicolon
DECL|member|ConRetry
id|u32
id|ConRetry
suffix:semicolon
DECL|member|ConRetryTmr
id|u32
id|ConRetryTmr
suffix:semicolon
DECL|member|ConTmout
id|u32
id|ConTmout
suffix:semicolon
DECL|member|CtatTmr
id|u32
id|CtatTmr
suffix:semicolon
DECL|member|MaxRxRng
id|u32
id|MaxRxRng
suffix:semicolon
DECL|member|IntrTmr
id|u32
id|IntrTmr
suffix:semicolon
DECL|member|TxDataMvTimeout
id|u32
id|TxDataMvTimeout
suffix:semicolon
DECL|member|RxDataMvTimeout
id|u32
id|RxDataMvTimeout
suffix:semicolon
DECL|member|EvtPrd
id|u32
id|EvtPrd
suffix:semicolon
DECL|member|TraceIdx
id|u32
id|TraceIdx
suffix:semicolon
DECL|member|Fail1
id|u32
id|Fail1
suffix:semicolon
DECL|member|Fail2
id|u32
id|Fail2
suffix:semicolon
DECL|member|DrvPrm
id|u32
id|DrvPrm
suffix:semicolon
DECL|member|FilterLA
id|u32
id|FilterLA
suffix:semicolon
DECL|member|FwRev
id|u32
id|FwRev
suffix:semicolon
DECL|member|FwRes1
id|u32
id|FwRes1
suffix:semicolon
DECL|member|FwRes2
id|u32
id|FwRes2
suffix:semicolon
DECL|member|FwRes3
id|u32
id|FwRes3
suffix:semicolon
DECL|member|WriteDmaThresh
id|u32
id|WriteDmaThresh
suffix:semicolon
DECL|member|ReadDmaThresh
id|u32
id|ReadDmaThresh
suffix:semicolon
DECL|member|pad12
id|u32
id|pad12
(braket
l_int|325
)braket
suffix:semicolon
DECL|member|Window
id|u32
id|Window
(braket
l_int|512
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Host control register bits.&n; */
DECL|macro|RR_INT
mdefine_line|#define RR_INT&t;&t;0x01
DECL|macro|RR_CLEAR_INT
mdefine_line|#define RR_CLEAR_INT&t;0x02
DECL|macro|NO_SWAP
mdefine_line|#define NO_SWAP&t;&t;0x04000004
DECL|macro|NO_SWAP1
mdefine_line|#define NO_SWAP1&t;0x00000004
DECL|macro|PCI_RESET_NIC
mdefine_line|#define PCI_RESET_NIC&t;0x08
DECL|macro|HALT_NIC
mdefine_line|#define HALT_NIC&t;0x10
DECL|macro|SSTEP_NIC
mdefine_line|#define SSTEP_NIC&t;0x20
DECL|macro|MEM_READ_MULTI
mdefine_line|#define MEM_READ_MULTI&t;0x40
DECL|macro|NIC_HALTED
mdefine_line|#define NIC_HALTED&t;0x100
DECL|macro|HALT_INST
mdefine_line|#define HALT_INST&t;0x200
DECL|macro|PARITY_ERR
mdefine_line|#define PARITY_ERR&t;0x400
DECL|macro|INVALID_INST_B
mdefine_line|#define INVALID_INST_B&t;0x800
DECL|macro|RR_REV_2
mdefine_line|#define RR_REV_2&t;0x20000000
DECL|macro|RR_REV_MASK
mdefine_line|#define RR_REV_MASK&t;0xf0000000
multiline_comment|/*&n; * Local control register bits.&n; */
DECL|macro|INTA_STATE
mdefine_line|#define INTA_STATE&t;&t;0x01
DECL|macro|CLEAR_INTA
mdefine_line|#define CLEAR_INTA&t;&t;0x02
DECL|macro|FAST_EEPROM_ACCESS
mdefine_line|#define FAST_EEPROM_ACCESS&t;0x08
DECL|macro|ENABLE_EXTRA_SRAM
mdefine_line|#define ENABLE_EXTRA_SRAM&t;0x100
DECL|macro|ENABLE_EXTRA_DESC
mdefine_line|#define ENABLE_EXTRA_DESC&t;0x200
DECL|macro|ENABLE_PARITY
mdefine_line|#define ENABLE_PARITY&t;&t;0x400
DECL|macro|FORCE_DMA_PARITY_ERROR
mdefine_line|#define FORCE_DMA_PARITY_ERROR&t;0x800
DECL|macro|ENABLE_EEPROM_WRITE
mdefine_line|#define ENABLE_EEPROM_WRITE&t;0x1000
DECL|macro|ENABLE_DATA_CACHE
mdefine_line|#define ENABLE_DATA_CACHE&t;0x2000
DECL|macro|SRAM_LO_PARITY_ERR
mdefine_line|#define SRAM_LO_PARITY_ERR&t;0x4000
DECL|macro|SRAM_HI_PARITY_ERR
mdefine_line|#define SRAM_HI_PARITY_ERR&t;0x8000
multiline_comment|/*&n; * PCI state bits.&n; */
DECL|macro|FORCE_PCI_RESET
mdefine_line|#define FORCE_PCI_RESET&t;&t;0x01
DECL|macro|PROVIDE_LENGTH
mdefine_line|#define PROVIDE_LENGTH&t;&t;0x02
DECL|macro|MASK_DMA_READ_MAX
mdefine_line|#define MASK_DMA_READ_MAX&t;0x1C
DECL|macro|RBURST_DISABLE
mdefine_line|#define RBURST_DISABLE&t;&t;0x00
DECL|macro|RBURST_4
mdefine_line|#define RBURST_4&t;&t;0x04
DECL|macro|RBURST_16
mdefine_line|#define RBURST_16&t;&t;0x08
DECL|macro|RBURST_32
mdefine_line|#define RBURST_32&t;&t;0x0C
DECL|macro|RBURST_64
mdefine_line|#define RBURST_64&t;&t;0x10
DECL|macro|RBURST_128
mdefine_line|#define RBURST_128&t;&t;0x14
DECL|macro|RBURST_256
mdefine_line|#define RBURST_256&t;&t;0x18
DECL|macro|RBURST_1024
mdefine_line|#define RBURST_1024&t;&t;0x1C
DECL|macro|MASK_DMA_WRITE_MAX
mdefine_line|#define MASK_DMA_WRITE_MAX&t;0xE0
DECL|macro|WBURST_DISABLE
mdefine_line|#define WBURST_DISABLE&t;&t;0x00
DECL|macro|WBURST_4
mdefine_line|#define WBURST_4&t;&t;0x20
DECL|macro|WBURST_16
mdefine_line|#define WBURST_16&t;&t;0x40
DECL|macro|WBURST_32
mdefine_line|#define WBURST_32&t;&t;0x60
DECL|macro|WBURST_64
mdefine_line|#define WBURST_64&t;&t;0x80
DECL|macro|WBURST_128
mdefine_line|#define WBURST_128&t;&t;0xa0
DECL|macro|WBURST_256
mdefine_line|#define WBURST_256&t;&t;0xc0
DECL|macro|WBURST_1024
mdefine_line|#define WBURST_1024&t;&t;0xe0
DECL|macro|MASK_MIN_DMA
mdefine_line|#define MASK_MIN_DMA&t;&t;0xFF00
DECL|macro|FIFO_RETRY_ENABLE
mdefine_line|#define FIFO_RETRY_ENABLE&t;0x10000
multiline_comment|/*&n; * Event register&n; */
DECL|macro|DMA_WRITE_DONE
mdefine_line|#define DMA_WRITE_DONE&t;&t;0x10000
DECL|macro|DMA_READ_DONE
mdefine_line|#define DMA_READ_DONE&t;&t;0x20000
DECL|macro|DMA_WRITE_ERR
mdefine_line|#define DMA_WRITE_ERR&t;&t;0x40000
DECL|macro|DMA_READ_ERR
mdefine_line|#define DMA_READ_ERR&t;&t;0x80000
multiline_comment|/*&n; * Receive state&n; *&n; * RoadRunner HIPPI Receive State Register controls and monitors the &n; * HIPPI receive interface in the NIC. Look at err bits when a HIPPI&n; * receive Error Event occurs. &n; */
DECL|macro|ENABLE_NEW_CON
mdefine_line|#define ENABLE_NEW_CON&t;&t;0x01
DECL|macro|RESET_RECV
mdefine_line|#define RESET_RECV&t;&t;0x02
DECL|macro|RECV_ALL
mdefine_line|#define RECV_ALL&t;&t;0x00
DECL|macro|RECV_1K
mdefine_line|#define RECV_1K&t;&t;&t;0x20
DECL|macro|RECV_2K
mdefine_line|#define RECV_2K&t;&t;&t;0x40
DECL|macro|RECV_4K
mdefine_line|#define RECV_4K&t;&t;&t;0x60
DECL|macro|RECV_8K
mdefine_line|#define RECV_8K&t;&t;&t;0x80
DECL|macro|RECV_16K
mdefine_line|#define RECV_16K&t;&t;0xa0
DECL|macro|RECV_32K
mdefine_line|#define RECV_32K&t;&t;0xc0
DECL|macro|RECV_64K
mdefine_line|#define RECV_64K&t;&t;0xe0
multiline_comment|/*&n; * Transmit status.&n; */
DECL|macro|ENA_XMIT
mdefine_line|#define ENA_XMIT&t;&t;0x01
DECL|macro|PERM_CON
mdefine_line|#define PERM_CON&t;&t;0x02
multiline_comment|/*&n; * DMA write state&n; */
DECL|macro|RESET_DMA
mdefine_line|#define RESET_DMA&t;&t;0x01
DECL|macro|NO_SWAP_DMA
mdefine_line|#define NO_SWAP_DMA&t;&t;0x02
DECL|macro|DMA_ACTIVE
mdefine_line|#define DMA_ACTIVE&t;&t;0x04
DECL|macro|THRESH_MASK
mdefine_line|#define THRESH_MASK&t;&t;0x1F
DECL|macro|DMA_ERROR_MASK
mdefine_line|#define DMA_ERROR_MASK&t;&t;0xff000000
multiline_comment|/*&n; * Gooddies stored in the ULA registers.&n; */
DECL|macro|TRACE_ON_WHAT_BIT
mdefine_line|#define TRACE_ON_WHAT_BIT&t;0x00020000    /* Traces on */
DECL|macro|ONEM_BUF_WHAT_BIT
mdefine_line|#define ONEM_BUF_WHAT_BIT&t;0x00040000    /* 1Meg vs 256K */
DECL|macro|CHAR_API_WHAT_BIT
mdefine_line|#define CHAR_API_WHAT_BIT&t;0x00080000    /* Char API vs network only */
DECL|macro|CMD_EVT_WHAT_BIT
mdefine_line|#define CMD_EVT_WHAT_BIT&t;0x00200000    /* Command event */
DECL|macro|LONG_TX_WHAT_BIT
mdefine_line|#define LONG_TX_WHAT_BIT&t;0x00400000
DECL|macro|LONG_RX_WHAT_BIT
mdefine_line|#define LONG_RX_WHAT_BIT&t;0x00800000
DECL|macro|WHAT_BIT_MASK
mdefine_line|#define WHAT_BIT_MASK&t;&t;0xFFFD0000    /* Feature bit mask */
multiline_comment|/*&n; * Mode status&n; */
DECL|macro|EVENT_OVFL
mdefine_line|#define EVENT_OVFL&t;&t;0x80000000
DECL|macro|FATAL_ERR
mdefine_line|#define FATAL_ERR&t;&t;0x40000000
DECL|macro|LOOP_BACK
mdefine_line|#define LOOP_BACK&t;&t;0x01
DECL|macro|MODE_PH
mdefine_line|#define MODE_PH&t;&t;&t;0x02
DECL|macro|MODE_FP
mdefine_line|#define MODE_FP&t;&t;&t;0x00
DECL|macro|PTR64BIT
mdefine_line|#define PTR64BIT&t;&t;0x04
DECL|macro|PTR32BIT
mdefine_line|#define PTR32BIT&t;&t;0x00
DECL|macro|PTR_WD_SWAP
mdefine_line|#define PTR_WD_SWAP&t;&t;0x08
DECL|macro|PTR_WD_NOSWAP
mdefine_line|#define PTR_WD_NOSWAP&t;&t;0x00
DECL|macro|POST_WARN_EVENT
mdefine_line|#define POST_WARN_EVENT&t;&t;0x10
DECL|macro|ERR_TERM
mdefine_line|#define ERR_TERM&t;&t;0x20
DECL|macro|DIRECT_CONN
mdefine_line|#define DIRECT_CONN&t;&t;0x40
DECL|macro|NO_NIC_WATCHDOG
mdefine_line|#define NO_NIC_WATCHDOG&t;&t;0x80
DECL|macro|SWAP_DATA
mdefine_line|#define SWAP_DATA&t;&t;0x100
DECL|macro|SWAP_CONTROL
mdefine_line|#define SWAP_CONTROL&t;&t;0x200
DECL|macro|NIC_HALT_ON_ERR
mdefine_line|#define NIC_HALT_ON_ERR&t;&t;0x400
DECL|macro|NIC_NO_RESTART
mdefine_line|#define NIC_NO_RESTART&t;&t;0x800
DECL|macro|HALF_DUP_TX
mdefine_line|#define HALF_DUP_TX&t;&t;0x1000
DECL|macro|HALF_DUP_RX
mdefine_line|#define HALF_DUP_RX&t;&t;0x2000
multiline_comment|/*&n; * Error codes&n; */
multiline_comment|/* Host Error Codes - values of fail1 */
DECL|macro|ERR_UNKNOWN_MBOX
mdefine_line|#define ERR_UNKNOWN_MBOX&t;0x1001
DECL|macro|ERR_UNKNOWN_CMD
mdefine_line|#define ERR_UNKNOWN_CMD&t;&t;0x1002
DECL|macro|ERR_MAX_RING
mdefine_line|#define ERR_MAX_RING&t;&t;0x1003
DECL|macro|ERR_RING_CLOSED
mdefine_line|#define ERR_RING_CLOSED&t;&t;0x1004
DECL|macro|ERR_RING_OPEN
mdefine_line|#define ERR_RING_OPEN&t;&t;0x1005
multiline_comment|/* Firmware internal errors */
DECL|macro|ERR_EVENT_RING_FULL
mdefine_line|#define ERR_EVENT_RING_FULL&t;0x01
DECL|macro|ERR_DW_PEND_CMND_FULL
mdefine_line|#define ERR_DW_PEND_CMND_FULL&t;0x02
DECL|macro|ERR_DR_PEND_CMND_FULL
mdefine_line|#define ERR_DR_PEND_CMND_FULL&t;0x03
DECL|macro|ERR_DW_PEND_DATA_FULL
mdefine_line|#define ERR_DW_PEND_DATA_FULL&t;0x04
DECL|macro|ERR_DR_PEND_DATA_FULL
mdefine_line|#define ERR_DR_PEND_DATA_FULL&t;0x05
DECL|macro|ERR_ILLEGAL_JUMP
mdefine_line|#define ERR_ILLEGAL_JUMP&t;0x06
DECL|macro|ERR_UNIMPLEMENTED
mdefine_line|#define ERR_UNIMPLEMENTED&t;0x07
DECL|macro|ERR_TX_INFO_FULL
mdefine_line|#define ERR_TX_INFO_FULL&t;0x08
DECL|macro|ERR_RX_INFO_FULL
mdefine_line|#define ERR_RX_INFO_FULL&t;0x09
DECL|macro|ERR_ILLEGAL_MODE
mdefine_line|#define ERR_ILLEGAL_MODE&t;0x0A
DECL|macro|ERR_MAIN_TIMEOUT
mdefine_line|#define ERR_MAIN_TIMEOUT&t;0x0B
DECL|macro|ERR_EVENT_BITS
mdefine_line|#define ERR_EVENT_BITS&t;&t;0x0C
DECL|macro|ERR_UNPEND_FULL
mdefine_line|#define ERR_UNPEND_FULL&t;&t;0x0D
DECL|macro|ERR_TIMER_QUEUE_FULL
mdefine_line|#define ERR_TIMER_QUEUE_FULL&t;0x0E
DECL|macro|ERR_TIMER_QUEUE_EMPTY
mdefine_line|#define ERR_TIMER_QUEUE_EMPTY&t;0x0F
DECL|macro|ERR_TIMER_NO_FREE
mdefine_line|#define ERR_TIMER_NO_FREE&t;0x10
DECL|macro|ERR_INTR_START
mdefine_line|#define ERR_INTR_START&t;&t;0x11
DECL|macro|ERR_BAD_STARTUP
mdefine_line|#define ERR_BAD_STARTUP&t;&t;0x12
DECL|macro|ERR_NO_PKT_END
mdefine_line|#define ERR_NO_PKT_END&t;&t;0x13
DECL|macro|ERR_HALTED_ON_ERR
mdefine_line|#define ERR_HALTED_ON_ERR&t;0x14
multiline_comment|/* Hardware NIC Errors */
DECL|macro|ERR_WRITE_DMA
mdefine_line|#define ERR_WRITE_DMA&t;&t;0x0101
DECL|macro|ERR_READ_DMA
mdefine_line|#define ERR_READ_DMA&t;&t;0x0102
DECL|macro|ERR_EXT_SERIAL
mdefine_line|#define ERR_EXT_SERIAL&t;&t;0x0103
DECL|macro|ERR_TX_INT_PARITY
mdefine_line|#define ERR_TX_INT_PARITY&t;0x0104
multiline_comment|/*&n; * Event definitions&n; */
DECL|macro|EVT_RING_ENTRIES
mdefine_line|#define EVT_RING_ENTRIES&t;64
DECL|macro|EVT_RING_SIZE
mdefine_line|#define EVT_RING_SIZE&t;(EVT_RING_ENTRIES * sizeof(struct event))
DECL|struct|event
r_struct
id|event
(brace
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|index
id|u16
id|index
suffix:semicolon
DECL|member|ring
id|u8
id|ring
suffix:semicolon
DECL|member|code
id|u8
id|code
suffix:semicolon
macro_line|#else
id|u8
id|code
suffix:semicolon
id|u8
id|ring
suffix:semicolon
id|u16
id|index
suffix:semicolon
macro_line|#endif
DECL|member|timestamp
id|u32
id|timestamp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * General Events&n; */
DECL|macro|E_NIC_UP
mdefine_line|#define E_NIC_UP&t;0x01
DECL|macro|E_WATCHDOG
mdefine_line|#define E_WATCHDOG&t;0x02
DECL|macro|E_STAT_UPD
mdefine_line|#define E_STAT_UPD&t;0x04
DECL|macro|E_INVAL_CMD
mdefine_line|#define E_INVAL_CMD&t;0x05
DECL|macro|E_SET_CMD_CONS
mdefine_line|#define E_SET_CMD_CONS&t;0x06
DECL|macro|E_LINK_ON
mdefine_line|#define E_LINK_ON&t;0x07
DECL|macro|E_LINK_OFF
mdefine_line|#define E_LINK_OFF&t;0x08
DECL|macro|E_INTERN_ERR
mdefine_line|#define E_INTERN_ERR&t;0x09
DECL|macro|E_HOST_ERR
mdefine_line|#define E_HOST_ERR&t;0x0A
DECL|macro|E_STATS_UPDATE
mdefine_line|#define E_STATS_UPDATE&t;0x0B
DECL|macro|E_REJECTING
mdefine_line|#define E_REJECTING&t;0x0C
multiline_comment|/*&n; * Send  Events&n; */
DECL|macro|E_CON_REJ
mdefine_line|#define E_CON_REJ&t;0x13
DECL|macro|E_CON_TMOUT
mdefine_line|#define E_CON_TMOUT&t;0x14
DECL|macro|E_CON_NC_TMOUT
mdefine_line|#define E_CON_NC_TMOUT&t;0x15&t;/* I  , Connection No Campon Timeout */
DECL|macro|E_DISC_ERR
mdefine_line|#define E_DISC_ERR&t;0x16
DECL|macro|E_INT_PRTY
mdefine_line|#define E_INT_PRTY&t;0x17
DECL|macro|E_TX_IDLE
mdefine_line|#define E_TX_IDLE&t;0x18
DECL|macro|E_TX_LINK_DROP
mdefine_line|#define E_TX_LINK_DROP&t;0x19
DECL|macro|E_TX_INV_RNG
mdefine_line|#define E_TX_INV_RNG&t;0x1A
DECL|macro|E_TX_INV_BUF
mdefine_line|#define E_TX_INV_BUF&t;0x1B
DECL|macro|E_TX_INV_DSC
mdefine_line|#define E_TX_INV_DSC&t;0x1C
multiline_comment|/*&n; * Destination Events&n; */
multiline_comment|/*&n; * General Receive events&n; */
DECL|macro|E_VAL_RNG
mdefine_line|#define E_VAL_RNG&t;0x20
DECL|macro|E_RX_RNG_ENER
mdefine_line|#define E_RX_RNG_ENER&t;0x21
DECL|macro|E_INV_RNG
mdefine_line|#define E_INV_RNG&t;0x22
DECL|macro|E_RX_RNG_SPC
mdefine_line|#define E_RX_RNG_SPC&t;0x23
DECL|macro|E_RX_RNG_OUT
mdefine_line|#define E_RX_RNG_OUT&t;0x24
DECL|macro|E_PKT_DISCARD
mdefine_line|#define E_PKT_DISCARD&t;0x25
DECL|macro|E_INFO_EVT
mdefine_line|#define E_INFO_EVT&t;0x27
multiline_comment|/*&n; * Data corrupted events&n; */
DECL|macro|E_RX_PAR_ERR
mdefine_line|#define E_RX_PAR_ERR&t;0x2B
DECL|macro|E_RX_LLRC_ERR
mdefine_line|#define E_RX_LLRC_ERR&t;0x2C
DECL|macro|E_IP_CKSM_ERR
mdefine_line|#define E_IP_CKSM_ERR&t;0x2D
DECL|macro|E_DTA_CKSM_ERR
mdefine_line|#define E_DTA_CKSM_ERR&t;0x2E
DECL|macro|E_SHT_BST
mdefine_line|#define E_SHT_BST&t;0x2F
multiline_comment|/*&n; * Data lost events&n; */
DECL|macro|E_LST_LNK_ERR
mdefine_line|#define E_LST_LNK_ERR&t;0x30
DECL|macro|E_FLG_SYN_ERR
mdefine_line|#define E_FLG_SYN_ERR&t;0x31
DECL|macro|E_FRM_ERR
mdefine_line|#define E_FRM_ERR&t;0x32
DECL|macro|E_RX_IDLE
mdefine_line|#define E_RX_IDLE&t;0x33
DECL|macro|E_PKT_LN_ERR
mdefine_line|#define E_PKT_LN_ERR&t;0x34
DECL|macro|E_STATE_ERR
mdefine_line|#define E_STATE_ERR&t;0x35
DECL|macro|E_UNEXP_DATA
mdefine_line|#define E_UNEXP_DATA&t;0x3C
multiline_comment|/*&n; * Fatal events&n; */
DECL|macro|E_RX_INV_BUF
mdefine_line|#define E_RX_INV_BUF&t;0x36
DECL|macro|E_RX_INV_DSC
mdefine_line|#define E_RX_INV_DSC&t;0x37
DECL|macro|E_RNG_BLK
mdefine_line|#define E_RNG_BLK&t;0x38
multiline_comment|/*&n; * Warning events&n; */
DECL|macro|E_RX_TO
mdefine_line|#define E_RX_TO&t;&t;0x39
DECL|macro|E_BFR_SPC
mdefine_line|#define E_BFR_SPC&t;0x3A
DECL|macro|E_INV_ULP
mdefine_line|#define E_INV_ULP&t;0x3B
DECL|macro|E_NOT_IMPLEMENTED
mdefine_line|#define E_NOT_IMPLEMENTED 0x40
multiline_comment|/*&n; * Commands&n; */
DECL|macro|CMD_RING_ENTRIES
mdefine_line|#define CMD_RING_ENTRIES&t;16
DECL|struct|cmd
r_struct
id|cmd
(brace
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|index
id|u16
id|index
suffix:semicolon
DECL|member|ring
id|u8
id|ring
suffix:semicolon
DECL|member|code
id|u8
id|code
suffix:semicolon
macro_line|#else
id|u8
id|code
suffix:semicolon
id|u8
id|ring
suffix:semicolon
id|u16
id|index
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|C_START_FW
mdefine_line|#define C_START_FW&t;0x01
DECL|macro|C_UPD_STAT
mdefine_line|#define C_UPD_STAT&t;0x02
DECL|macro|C_WATCHDOG
mdefine_line|#define C_WATCHDOG&t;0x05
DECL|macro|C_DEL_RNG
mdefine_line|#define C_DEL_RNG&t;0x09
DECL|macro|C_NEW_RNG
mdefine_line|#define C_NEW_RNG&t;0x0A
DECL|macro|C_CONN
mdefine_line|#define C_CONN&t;&t;0x0D
multiline_comment|/*&n; * Mode bits&n; */
DECL|macro|INTERRUPT
mdefine_line|#define  INTERRUPT&t;&t;0x02
DECL|macro|TX_IP_CKSUM
mdefine_line|#define  TX_IP_CKSUM&t;&t;0x04
DECL|macro|PACKET_END
mdefine_line|#define  PACKET_END&t;&t;0x08
DECL|macro|PACKET_START
mdefine_line|#define  PACKET_START&t;&t;0x10
DECL|macro|SAME_IFIELD
mdefine_line|#define  SAME_IFIELD&t;&t;0x80
r_typedef
r_struct
(brace
macro_line|#if (BITS_PER_LONG == 64)
DECL|member|addrlo
id|u64
id|addrlo
suffix:semicolon
macro_line|#else
id|u32
id|addrhi
suffix:semicolon
id|u32
id|addrlo
suffix:semicolon
macro_line|#endif
DECL|typedef|rraddr
)brace
id|rraddr
suffix:semicolon
DECL|function|set_rraddr
r_static
r_inline
r_void
id|set_rraddr
c_func
(paren
id|rraddr
op_star
id|ra
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|baddr
op_assign
id|virt_to_bus
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
macro_line|#if (BITS_PER_LONG == 64)
id|ra-&gt;addrlo
op_assign
id|baddr
suffix:semicolon
macro_line|#else
multiline_comment|/* Don&squot;t bother setting zero every time */
id|ra-&gt;addrlo
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
DECL|function|set_rxaddr
r_static
r_inline
r_void
id|set_rxaddr
c_func
(paren
r_struct
id|rr_regs
op_star
id|regs
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|baddr
op_assign
id|virt_to_bus
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
macro_line|#if (BITS_PER_LONG == 64) &amp;&amp; defined(__LITTLE_ENDIAN)
id|writel
c_func
(paren
id|baddr
op_amp
l_int|0xffffffff
comma
op_amp
id|regs-&gt;RxRingHi
)paren
suffix:semicolon
id|writel
c_func
(paren
id|baddr
op_rshift
l_int|32
comma
op_amp
id|regs-&gt;RxRingLo
)paren
suffix:semicolon
macro_line|#elif (BITS_PER_LONG == 64)
id|writel
c_func
(paren
id|baddr
op_rshift
l_int|32
comma
op_amp
id|regs-&gt;RxRingHi
)paren
suffix:semicolon
id|writel
c_func
(paren
id|baddr
op_amp
l_int|0xffffffff
comma
op_amp
id|regs-&gt;RxRingLo
)paren
suffix:semicolon
macro_line|#else
id|writel
c_func
(paren
l_int|0
comma
op_amp
id|regs-&gt;RxRingHi
)paren
suffix:semicolon
id|writel
c_func
(paren
id|baddr
comma
op_amp
id|regs-&gt;RxRingLo
)paren
suffix:semicolon
macro_line|#endif
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|set_infoaddr
r_static
r_inline
r_void
id|set_infoaddr
c_func
(paren
r_struct
id|rr_regs
op_star
id|regs
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|baddr
op_assign
id|virt_to_bus
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
macro_line|#if (BITS_PER_LONG == 64) &amp;&amp; defined(__LITTLE_ENDIAN)
id|writel
c_func
(paren
id|baddr
op_amp
l_int|0xffffffff
comma
op_amp
id|regs-&gt;InfoPtrHi
)paren
suffix:semicolon
id|writel
c_func
(paren
id|baddr
op_rshift
l_int|32
comma
op_amp
id|regs-&gt;InfoPtrLo
)paren
suffix:semicolon
macro_line|#elif (BITS_PER_LONG == 64)
id|writel
c_func
(paren
id|baddr
op_rshift
l_int|32
comma
op_amp
id|regs-&gt;InfoPtrHi
)paren
suffix:semicolon
id|writel
c_func
(paren
id|baddr
op_amp
l_int|0xffffffff
comma
op_amp
id|regs-&gt;InfoPtrLo
)paren
suffix:semicolon
macro_line|#else
id|writel
c_func
(paren
l_int|0
comma
op_amp
id|regs-&gt;InfoPtrHi
)paren
suffix:semicolon
id|writel
c_func
(paren
id|baddr
comma
op_amp
id|regs-&gt;InfoPtrLo
)paren
suffix:semicolon
macro_line|#endif
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * TX ring&n; */
macro_line|#ifdef CONFIG_ROADRUNNER_LARGE_RINGS
DECL|macro|TX_RING_ENTRIES
mdefine_line|#define TX_RING_ENTRIES&t;32
macro_line|#else
DECL|macro|TX_RING_ENTRIES
mdefine_line|#define TX_RING_ENTRIES&t;16
macro_line|#endif
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE&t;(TX_RING_ENTRIES * sizeof(struct tx_desc))
DECL|struct|tx_desc
r_struct
id|tx_desc
(brace
DECL|member|addr
id|rraddr
id|addr
suffix:semicolon
DECL|member|res
id|u32
id|res
suffix:semicolon
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|pad
id|u8
id|pad
suffix:semicolon
DECL|member|mode
id|u8
id|mode
suffix:semicolon
macro_line|#else
DECL|member|mode
id|u8
id|mode
suffix:semicolon
DECL|member|pad
id|u8
id|pad
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ROADRUNNER_LARGE_RINGS
DECL|macro|RX_RING_ENTRIES
mdefine_line|#define RX_RING_ENTRIES&t;32
macro_line|#else
DECL|macro|RX_RING_ENTRIES
mdefine_line|#define RX_RING_ENTRIES 16
macro_line|#endif
DECL|macro|RX_RING_SIZE
mdefine_line|#define RX_RING_SIZE&t;(RX_RING_ENTRIES * sizeof(struct rx_desc))
DECL|struct|rx_desc
r_struct
id|rx_desc
(brace
DECL|member|addr
id|rraddr
id|addr
suffix:semicolon
DECL|member|res
id|u32
id|res
suffix:semicolon
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|pad
id|u8
id|pad
suffix:semicolon
DECL|member|mode
id|u8
id|mode
suffix:semicolon
macro_line|#else
DECL|member|mode
id|u8
id|mode
suffix:semicolon
DECL|member|pad
id|u8
id|pad
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * ioctl&squot;s&n; */
DECL|macro|SIOCRRPFW
mdefine_line|#define SIOCRRPFW&t;SIOCDEVPRIVATE&t;&t;/* put firmware */
DECL|macro|SIOCRRGFW
mdefine_line|#define SIOCRRGFW&t;SIOCDEVPRIVATE+1&t;/* get firmware */
DECL|macro|SIOCRRID
mdefine_line|#define SIOCRRID&t;SIOCDEVPRIVATE+2&t;/* identify */
DECL|struct|seg_hdr
r_struct
id|seg_hdr
(brace
DECL|member|seg_start
id|u32
id|seg_start
suffix:semicolon
DECL|member|seg_len
id|u32
id|seg_len
suffix:semicolon
DECL|member|seg_eestart
id|u32
id|seg_eestart
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EEPROM_BASE
mdefine_line|#define EEPROM_BASE 0x80000000
DECL|macro|EEPROM_WORDS
mdefine_line|#define EEPROM_WORDS 8192
DECL|macro|EEPROM_BYTES
mdefine_line|#define EEPROM_BYTES (EEPROM_WORDS * sizeof(u32))
DECL|struct|eeprom_boot
r_struct
id|eeprom_boot
(brace
DECL|member|key1
id|u32
id|key1
suffix:semicolon
DECL|member|key2
id|u32
id|key2
suffix:semicolon
DECL|member|sram_size
id|u32
id|sram_size
suffix:semicolon
DECL|member|loader
r_struct
id|seg_hdr
id|loader
suffix:semicolon
DECL|member|init_chksum
id|u32
id|init_chksum
suffix:semicolon
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eeprom_manf
r_struct
id|eeprom_manf
(brace
DECL|member|HeaderFmt
id|u32
id|HeaderFmt
suffix:semicolon
DECL|member|Firmware
id|u32
id|Firmware
suffix:semicolon
DECL|member|BoardRevision
id|u32
id|BoardRevision
suffix:semicolon
DECL|member|RoadrunnerRev
id|u32
id|RoadrunnerRev
suffix:semicolon
DECL|member|OpticsPart
r_char
id|OpticsPart
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|OpticsRev
id|u32
id|OpticsRev
suffix:semicolon
DECL|member|pad1
id|u32
id|pad1
suffix:semicolon
DECL|member|SramPart
r_char
id|SramPart
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|SramRev
id|u32
id|SramRev
suffix:semicolon
DECL|member|pad2
id|u32
id|pad2
suffix:semicolon
DECL|member|EepromPart
r_char
id|EepromPart
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|EepromRev
id|u32
id|EepromRev
suffix:semicolon
DECL|member|EepromSize
id|u32
id|EepromSize
suffix:semicolon
DECL|member|PalPart
r_char
id|PalPart
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|PalRev
id|u32
id|PalRev
suffix:semicolon
DECL|member|pad3
id|u32
id|pad3
suffix:semicolon
DECL|member|PalCodeFile
r_char
id|PalCodeFile
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|PalCodeRev
id|u32
id|PalCodeRev
suffix:semicolon
DECL|member|BoardULA
r_char
id|BoardULA
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|SerialNo
r_char
id|SerialNo
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|MfgDate
r_char
id|MfgDate
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|MfgTime
r_char
id|MfgTime
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ModifyDate
r_char
id|ModifyDate
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ModCount
id|u32
id|ModCount
suffix:semicolon
DECL|member|pad4
id|u32
id|pad4
(braket
l_int|13
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eeprom_phase_info
r_struct
id|eeprom_phase_info
(brace
DECL|member|phase1File
r_char
id|phase1File
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|phase1Rev
id|u32
id|phase1Rev
suffix:semicolon
DECL|member|phase1Date
r_char
id|phase1Date
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|phase2File
r_char
id|phase2File
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|phase2Rev
id|u32
id|phase2Rev
suffix:semicolon
DECL|member|phase2Date
r_char
id|phase2Date
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|reserved7
id|u32
id|reserved7
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eeprom_rncd_info
r_struct
id|eeprom_rncd_info
(brace
DECL|member|FwStart
id|u32
id|FwStart
suffix:semicolon
DECL|member|FwRev
id|u32
id|FwRev
suffix:semicolon
DECL|member|FwDate
r_char
id|FwDate
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|AddrRunCodeSegs
id|u32
id|AddrRunCodeSegs
suffix:semicolon
DECL|member|FileNames
id|u32
id|FileNames
suffix:semicolon
DECL|member|File
r_char
id|File
(braket
l_int|13
)braket
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Phase 1 region (starts are word offset 0x80) */
DECL|struct|phase1_hdr
r_struct
id|phase1_hdr
(brace
DECL|member|jump
id|u32
id|jump
suffix:semicolon
DECL|member|noop
id|u32
id|noop
suffix:semicolon
DECL|member|phase2Seg
r_struct
id|seg_hdr
id|phase2Seg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eeprom
r_struct
id|eeprom
(brace
DECL|member|boot
r_struct
id|eeprom_boot
id|boot
suffix:semicolon
DECL|member|pad1
id|u32
id|pad1
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|manf
r_struct
id|eeprom_manf
id|manf
suffix:semicolon
DECL|member|phase_info
r_struct
id|eeprom_phase_info
id|phase_info
suffix:semicolon
DECL|member|rncd_info
r_struct
id|eeprom_rncd_info
id|rncd_info
suffix:semicolon
DECL|member|pad2
id|u32
id|pad2
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|hdr_checksum
id|u32
id|hdr_checksum
suffix:semicolon
DECL|member|phase1
r_struct
id|phase1_hdr
id|phase1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rr_stats
r_struct
id|rr_stats
(brace
DECL|member|NicTimeStamp
id|u32
id|NicTimeStamp
suffix:semicolon
DECL|member|RngCreated
id|u32
id|RngCreated
suffix:semicolon
DECL|member|RngDeleted
id|u32
id|RngDeleted
suffix:semicolon
DECL|member|IntrGen
id|u32
id|IntrGen
suffix:semicolon
DECL|member|NEvtOvfl
id|u32
id|NEvtOvfl
suffix:semicolon
DECL|member|InvCmd
id|u32
id|InvCmd
suffix:semicolon
DECL|member|DmaReadErrs
id|u32
id|DmaReadErrs
suffix:semicolon
DECL|member|DmaWriteErrs
id|u32
id|DmaWriteErrs
suffix:semicolon
DECL|member|StatUpdtT
id|u32
id|StatUpdtT
suffix:semicolon
DECL|member|StatUpdtC
id|u32
id|StatUpdtC
suffix:semicolon
DECL|member|WatchDog
id|u32
id|WatchDog
suffix:semicolon
DECL|member|Trace
id|u32
id|Trace
suffix:semicolon
multiline_comment|/* Serial HIPPI */
DECL|member|LnkRdyEst
id|u32
id|LnkRdyEst
suffix:semicolon
DECL|member|GLinkErr
id|u32
id|GLinkErr
suffix:semicolon
DECL|member|AltFlgErr
id|u32
id|AltFlgErr
suffix:semicolon
DECL|member|OvhdBit8Sync
id|u32
id|OvhdBit8Sync
suffix:semicolon
DECL|member|RmtSerPrtyErr
id|u32
id|RmtSerPrtyErr
suffix:semicolon
DECL|member|RmtParPrtyErr
id|u32
id|RmtParPrtyErr
suffix:semicolon
DECL|member|RmtLoopBk
id|u32
id|RmtLoopBk
suffix:semicolon
DECL|member|pad1
id|u32
id|pad1
suffix:semicolon
multiline_comment|/* HIPPI tx */
DECL|member|ConEst
id|u32
id|ConEst
suffix:semicolon
DECL|member|ConRejS
id|u32
id|ConRejS
suffix:semicolon
DECL|member|ConRetry
id|u32
id|ConRetry
suffix:semicolon
DECL|member|ConTmOut
id|u32
id|ConTmOut
suffix:semicolon
DECL|member|SndConDiscon
id|u32
id|SndConDiscon
suffix:semicolon
DECL|member|SndParErr
id|u32
id|SndParErr
suffix:semicolon
DECL|member|PktSnt
id|u32
id|PktSnt
suffix:semicolon
DECL|member|pad2
id|u32
id|pad2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ShFBstSnt
id|u32
id|ShFBstSnt
suffix:semicolon
DECL|member|BytSent
id|u64
id|BytSent
suffix:semicolon
DECL|member|TxTimeout
id|u32
id|TxTimeout
suffix:semicolon
DECL|member|pad3
id|u32
id|pad3
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* HIPPI rx */
DECL|member|ConAcc
id|u32
id|ConAcc
suffix:semicolon
DECL|member|ConRejdiPrty
id|u32
id|ConRejdiPrty
suffix:semicolon
DECL|member|ConRejd64b
id|u32
id|ConRejd64b
suffix:semicolon
DECL|member|ConRejdBuf
id|u32
id|ConRejdBuf
suffix:semicolon
DECL|member|RxConDiscon
id|u32
id|RxConDiscon
suffix:semicolon
DECL|member|RxConNoData
id|u32
id|RxConNoData
suffix:semicolon
DECL|member|PktRx
id|u32
id|PktRx
suffix:semicolon
DECL|member|pad4
id|u32
id|pad4
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ShFBstRx
id|u32
id|ShFBstRx
suffix:semicolon
DECL|member|BytRx
id|u64
id|BytRx
suffix:semicolon
DECL|member|RxParErr
id|u32
id|RxParErr
suffix:semicolon
DECL|member|RxLLRCerr
id|u32
id|RxLLRCerr
suffix:semicolon
DECL|member|RxBstSZerr
id|u32
id|RxBstSZerr
suffix:semicolon
DECL|member|RxStateErr
id|u32
id|RxStateErr
suffix:semicolon
DECL|member|RxRdyErr
id|u32
id|RxRdyErr
suffix:semicolon
DECL|member|RxInvULP
id|u32
id|RxInvULP
suffix:semicolon
DECL|member|RxSpcBuf
id|u32
id|RxSpcBuf
suffix:semicolon
DECL|member|RxSpcDesc
id|u32
id|RxSpcDesc
suffix:semicolon
DECL|member|RxRngSpc
id|u32
id|RxRngSpc
suffix:semicolon
DECL|member|RxRngFull
id|u32
id|RxRngFull
suffix:semicolon
DECL|member|RxPktLenErr
id|u32
id|RxPktLenErr
suffix:semicolon
DECL|member|RxCksmErr
id|u32
id|RxCksmErr
suffix:semicolon
DECL|member|RxPktDrp
id|u32
id|RxPktDrp
suffix:semicolon
DECL|member|RngLowSpc
id|u32
id|RngLowSpc
suffix:semicolon
DECL|member|RngDataClose
id|u32
id|RngDataClose
suffix:semicolon
DECL|member|RxTimeout
id|u32
id|RxTimeout
suffix:semicolon
DECL|member|RxIdle
id|u32
id|RxIdle
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This struct is shared with the NIC firmware.&n; */
DECL|struct|ring_ctrl
r_struct
id|ring_ctrl
(brace
DECL|member|rngptr
id|rraddr
id|rngptr
suffix:semicolon
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|entries
id|u16
id|entries
suffix:semicolon
DECL|member|pad
id|u8
id|pad
suffix:semicolon
DECL|member|entry_size
id|u8
id|entry_size
suffix:semicolon
DECL|member|pi
id|u16
id|pi
suffix:semicolon
DECL|member|mode
id|u16
id|mode
suffix:semicolon
macro_line|#else
DECL|member|entry_size
id|u8
id|entry_size
suffix:semicolon
DECL|member|pad
id|u8
id|pad
suffix:semicolon
DECL|member|entries
id|u16
id|entries
suffix:semicolon
DECL|member|mode
id|u16
id|mode
suffix:semicolon
DECL|member|pi
id|u16
id|pi
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|rr_info
r_struct
id|rr_info
(brace
r_union
(brace
DECL|member|stats
r_struct
id|rr_stats
id|stats
suffix:semicolon
DECL|member|stati
id|u32
id|stati
(braket
l_int|128
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
DECL|member|pad
id|u8
id|pad
(braket
l_int|464
)braket
suffix:semicolon
DECL|member|trace
id|u8
id|trace
(braket
l_int|3072
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The linux structure for the RoadRunner.&n; *&n; * RX/TX descriptors are put first to make sure they are properly&n; * aligned and do not cross cache-line boundaries.&n; */
DECL|struct|rr_private
r_struct
id|rr_private
(brace
DECL|member|rx_ring
r_struct
id|rx_desc
id|rx_ring
(braket
id|RX_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|tx_ring
r_struct
id|tx_desc
id|tx_ring
(braket
id|TX_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|evt_ring
r_struct
id|event
id|evt_ring
(braket
id|EVT_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|rx_skbuff
r_struct
id|sk_buff
op_star
id|rx_skbuff
(braket
id|RX_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|tx_skbuff
r_struct
id|sk_buff
op_star
id|tx_skbuff
(braket
id|TX_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|regs
r_struct
id|rr_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* Register base */
DECL|member|rx_ctrl
r_struct
id|ring_ctrl
op_star
id|rx_ctrl
suffix:semicolon
multiline_comment|/* Receive ring control */
DECL|member|info
r_struct
id|rr_info
op_star
id|info
suffix:semicolon
multiline_comment|/* Shared info page */
DECL|member|next
r_struct
id|net_device
op_star
id|next
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|cur_rx
DECL|member|cur_cmd
DECL|member|cur_evt
id|u32
id|cur_rx
comma
id|cur_cmd
comma
id|cur_evt
suffix:semicolon
DECL|member|dirty_rx
DECL|member|dirty_tx
id|u32
id|dirty_rx
comma
id|dirty_tx
suffix:semicolon
DECL|member|tx_full
id|u32
id|tx_full
suffix:semicolon
DECL|member|fw_rev
id|u32
id|fw_rev
suffix:semicolon
DECL|member|fw_running
r_int
id|fw_running
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* The assigned name */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Prototypes&n; */
r_static
r_int
id|rr_init
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
id|rr_init1
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
id|rr_interrupt
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
id|rr_open
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
id|rr_start_xmit
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
id|rr_close
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
id|rr_get_stats
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
id|rr_ioctl
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
id|rq
comma
r_int
id|cmd
)paren
suffix:semicolon
r_static
r_int
r_int
id|rr_read_eeprom
c_func
(paren
r_struct
id|rr_private
op_star
id|rrpriv
comma
r_int
r_int
id|offset
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|length
)paren
suffix:semicolon
r_static
id|u32
id|rr_read_eeprom_word
c_func
(paren
r_struct
id|rr_private
op_star
id|rrpriv
comma
r_void
op_star
id|offset
)paren
suffix:semicolon
r_static
r_int
id|rr_load_firmware
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* _RRUNNER_H_ */
eof
