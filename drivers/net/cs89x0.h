multiline_comment|/*  Copyright, 1988-1992, Russell Nelson, Crynwr Software&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation, version 1.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;   */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|PP_ChipID
mdefine_line|#define PP_ChipID 0x0000&t;/* offset   0h -&gt; Corp -ID              */
multiline_comment|/* offset   2h -&gt; Model/Product Number  */
multiline_comment|/* offset   3h -&gt; Chip Revision Number  */
DECL|macro|PP_ISAIOB
mdefine_line|#define PP_ISAIOB 0x0020&t;/*  IO base address */
DECL|macro|PP_CS8900_ISAINT
mdefine_line|#define PP_CS8900_ISAINT 0x0022&t;/*  ISA interrupt select */
DECL|macro|PP_CS8920_ISAINT
mdefine_line|#define PP_CS8920_ISAINT 0x0370&t;/*  ISA interrupt select */
DECL|macro|PP_CS8900_ISADMA
mdefine_line|#define PP_CS8900_ISADMA 0x0024&t;/*  ISA Rec DMA channel */
DECL|macro|PP_CS8920_ISADMA
mdefine_line|#define PP_CS8920_ISADMA 0x0374&t;/*  ISA Rec DMA channel */
DECL|macro|PP_ISASOF
mdefine_line|#define PP_ISASOF 0x0026&t;/*  ISA DMA offset */
DECL|macro|PP_DmaFrameCnt
mdefine_line|#define PP_DmaFrameCnt 0x0028&t;/*  ISA DMA Frame count */
DECL|macro|PP_DmaByteCnt
mdefine_line|#define PP_DmaByteCnt 0x002A&t;/*  ISA DMA Byte count */
DECL|macro|PP_CS8900_ISAMemB
mdefine_line|#define PP_CS8900_ISAMemB 0x002C&t;/*  Memory base */
DECL|macro|PP_CS8920_ISAMemB
mdefine_line|#define PP_CS8920_ISAMemB 0x0348 /*  */
DECL|macro|PP_ISABootBase
mdefine_line|#define PP_ISABootBase 0x0030&t;/*  Boot Prom base  */
DECL|macro|PP_ISABootMask
mdefine_line|#define PP_ISABootMask 0x0034&t;/*  Boot Prom Mask */
multiline_comment|/* EEPROM data and command registers */
DECL|macro|PP_EECMD
mdefine_line|#define PP_EECMD 0x0040&t;&t;/*  NVR Interface Command register */
DECL|macro|PP_EEData
mdefine_line|#define PP_EEData 0x0042&t;/*  NVR Interface Data Register */
DECL|macro|PP_DebugReg
mdefine_line|#define PP_DebugReg 0x0044&t;/*  Debug Register */
DECL|macro|PP_RxCFG
mdefine_line|#define PP_RxCFG 0x0102&t;&t;/*  Rx Bus config */
DECL|macro|PP_RxCTL
mdefine_line|#define PP_RxCTL 0x0104&t;&t;/*  Receive Control Register */
DECL|macro|PP_TxCFG
mdefine_line|#define PP_TxCFG 0x0106&t;&t;/*  Transmit Config Register */
DECL|macro|PP_TxCMD
mdefine_line|#define PP_TxCMD 0x0108&t;&t;/*  Transmit Command Register */
DECL|macro|PP_BufCFG
mdefine_line|#define PP_BufCFG 0x010A&t;/*  Bus configuration Register */
DECL|macro|PP_LineCTL
mdefine_line|#define PP_LineCTL 0x0112&t;/*  Line Config Register */
DECL|macro|PP_SelfCTL
mdefine_line|#define PP_SelfCTL 0x0114&t;/*  Self Command Register */
DECL|macro|PP_BusCTL
mdefine_line|#define PP_BusCTL 0x0116&t;/*  ISA bus control Register */
DECL|macro|PP_TestCTL
mdefine_line|#define PP_TestCTL 0x0118&t;/*  Test Register */
DECL|macro|PP_AutoNegCTL
mdefine_line|#define PP_AutoNegCTL 0x011C&t;/*  Auto Negotiation Ctrl */
DECL|macro|PP_ISQ
mdefine_line|#define PP_ISQ 0x0120&t;&t;/*  Interrupt Status */
DECL|macro|PP_RxEvent
mdefine_line|#define PP_RxEvent 0x0124&t;/*  Rx Event Register */
DECL|macro|PP_TxEvent
mdefine_line|#define PP_TxEvent 0x0128&t;/*  Tx Event Register */
DECL|macro|PP_BufEvent
mdefine_line|#define PP_BufEvent 0x012C&t;/*  Bus Event Register */
DECL|macro|PP_RxMiss
mdefine_line|#define PP_RxMiss 0x0130&t;/*  Receive Miss Count */
DECL|macro|PP_TxCol
mdefine_line|#define PP_TxCol 0x0132&t;&t;/*  Transmit Collision Count */
DECL|macro|PP_LineST
mdefine_line|#define PP_LineST 0x0134&t;/*  Line State Register */
DECL|macro|PP_SelfST
mdefine_line|#define PP_SelfST 0x0136&t;/*  Self State register */
DECL|macro|PP_BusST
mdefine_line|#define PP_BusST 0x0138&t;&t;/*  Bus Status */
DECL|macro|PP_TDR
mdefine_line|#define PP_TDR 0x013C&t;&t;/*  Time Domain Reflectometry */
DECL|macro|PP_AutoNegST
mdefine_line|#define PP_AutoNegST 0x013E&t;/*  Auto Neg Status */
DECL|macro|PP_TxCommand
mdefine_line|#define PP_TxCommand 0x0144&t;/*  Tx Command */
DECL|macro|PP_TxLength
mdefine_line|#define PP_TxLength 0x0146&t;/*  Tx Length */
DECL|macro|PP_LAF
mdefine_line|#define PP_LAF 0x0150&t;&t;/*  Hash Table */
DECL|macro|PP_IA
mdefine_line|#define PP_IA 0x0158&t;&t;/*  Physical Address Register */
DECL|macro|PP_RxStatus
mdefine_line|#define PP_RxStatus 0x0400&t;/*  Receive start of frame */
DECL|macro|PP_RxLength
mdefine_line|#define PP_RxLength 0x0402&t;/*  Receive Length of frame */
DECL|macro|PP_RxFrame
mdefine_line|#define PP_RxFrame 0x0404&t;/*  Receive frame pointer */
DECL|macro|PP_TxFrame
mdefine_line|#define PP_TxFrame 0x0A00&t;/*  Transmit frame pointer */
multiline_comment|/*  Primary I/O Base Address. If no I/O base is supplied by the user, then this */
multiline_comment|/*  can be used as the default I/O base to access the PacketPage Area. */
DECL|macro|DEFAULTIOBASE
mdefine_line|#define DEFAULTIOBASE 0x0300
DECL|macro|FIRST_IO
mdefine_line|#define FIRST_IO 0x020C&t;&t;/*  First I/O port to check */
DECL|macro|LAST_IO
mdefine_line|#define LAST_IO 0x037C&t;&t;/*  Last I/O port to check (+10h) */
DECL|macro|ADD_MASK
mdefine_line|#define ADD_MASK 0x3000&t;&t;/*  Mask it use of the ADD_PORT register */
DECL|macro|ADD_SIG
mdefine_line|#define ADD_SIG 0x3000&t;&t;/*  Expected ID signature */
multiline_comment|/* On Macs, we only need use the ISA I/O stuff until we do MEMORY_ON */
macro_line|#ifdef CONFIG_MAC
DECL|macro|LCSLOTBASE
mdefine_line|#define LCSLOTBASE 0xfee00000
DECL|macro|MMIOBASE
mdefine_line|#define MMIOBASE 0x40000
macro_line|#endif
DECL|macro|CHIP_EISA_ID_SIG
mdefine_line|#define CHIP_EISA_ID_SIG 0x630E   /*  Product ID Code for Crystal Chip (CS8900 spec 4.3) */
macro_line|#ifdef IBMEIPKT
DECL|macro|EISA_ID_SIG
mdefine_line|#define EISA_ID_SIG 0x4D24&t;/*  IBM */
DECL|macro|PART_NO_SIG
mdefine_line|#define PART_NO_SIG 0x1010&t;/*  IBM */
DECL|macro|MONGOOSE_BIT
mdefine_line|#define MONGOOSE_BIT 0x0000&t;/*  IBM */
macro_line|#else
DECL|macro|EISA_ID_SIG
mdefine_line|#define EISA_ID_SIG 0x630E&t;/*  PnP Vendor ID (same as chip id for Crystal board) */
DECL|macro|PART_NO_SIG
mdefine_line|#define PART_NO_SIG 0x4000&t;/*  ID code CS8920 board (PnP Vendor Product code) */
DECL|macro|MONGOOSE_BIT
mdefine_line|#define MONGOOSE_BIT 0x2000&t;/*  PART_NO_SIG + MONGOOSE_BUT =&gt; ID of mongoose */
macro_line|#endif
DECL|macro|PRODUCT_ID_ADD
mdefine_line|#define PRODUCT_ID_ADD 0x0002   /*  Address of product ID */
multiline_comment|/*  Mask to find out the types of  registers */
DECL|macro|REG_TYPE_MASK
mdefine_line|#define REG_TYPE_MASK 0x001F
multiline_comment|/*  Eeprom Commands */
DECL|macro|ERSE_WR_ENBL
mdefine_line|#define ERSE_WR_ENBL 0x00F0
DECL|macro|ERSE_WR_DISABLE
mdefine_line|#define ERSE_WR_DISABLE 0x0000
multiline_comment|/*  Defines Control/Config register quintuplet numbers */
DECL|macro|RX_BUF_CFG
mdefine_line|#define RX_BUF_CFG 0x0003
DECL|macro|RX_CONTROL
mdefine_line|#define RX_CONTROL 0x0005
DECL|macro|TX_CFG
mdefine_line|#define TX_CFG 0x0007
DECL|macro|TX_COMMAND
mdefine_line|#define TX_COMMAND 0x0009
DECL|macro|BUF_CFG
mdefine_line|#define BUF_CFG 0x000B
DECL|macro|LINE_CONTROL
mdefine_line|#define LINE_CONTROL 0x0013
DECL|macro|SELF_CONTROL
mdefine_line|#define SELF_CONTROL 0x0015
DECL|macro|BUS_CONTROL
mdefine_line|#define BUS_CONTROL 0x0017
DECL|macro|TEST_CONTROL
mdefine_line|#define TEST_CONTROL 0x0019
multiline_comment|/*  Defines Status/Count registers quintuplet numbers */
DECL|macro|RX_EVENT
mdefine_line|#define RX_EVENT 0x0004
DECL|macro|TX_EVENT
mdefine_line|#define TX_EVENT 0x0008
DECL|macro|BUF_EVENT
mdefine_line|#define BUF_EVENT 0x000C
DECL|macro|RX_MISS_COUNT
mdefine_line|#define RX_MISS_COUNT 0x0010
DECL|macro|TX_COL_COUNT
mdefine_line|#define TX_COL_COUNT 0x0012
DECL|macro|LINE_STATUS
mdefine_line|#define LINE_STATUS 0x0014
DECL|macro|SELF_STATUS
mdefine_line|#define SELF_STATUS 0x0016
DECL|macro|BUS_STATUS
mdefine_line|#define BUS_STATUS 0x0018
DECL|macro|TDR
mdefine_line|#define TDR 0x001C
multiline_comment|/* PP_RxCFG - Receive  Configuration and Interrupt Mask bit definition -  Read/write */
DECL|macro|SKIP_1
mdefine_line|#define SKIP_1 0x0040
DECL|macro|RX_STREAM_ENBL
mdefine_line|#define RX_STREAM_ENBL 0x0080
DECL|macro|RX_OK_ENBL
mdefine_line|#define RX_OK_ENBL 0x0100
DECL|macro|RX_DMA_ONLY
mdefine_line|#define RX_DMA_ONLY 0x0200
DECL|macro|AUTO_RX_DMA
mdefine_line|#define AUTO_RX_DMA 0x0400
DECL|macro|BUFFER_CRC
mdefine_line|#define BUFFER_CRC 0x0800
DECL|macro|RX_CRC_ERROR_ENBL
mdefine_line|#define RX_CRC_ERROR_ENBL 0x1000
DECL|macro|RX_RUNT_ENBL
mdefine_line|#define RX_RUNT_ENBL 0x2000
DECL|macro|RX_EXTRA_DATA_ENBL
mdefine_line|#define RX_EXTRA_DATA_ENBL 0x4000
multiline_comment|/* PP_RxCTL - Receive Control bit definition - Read/write */
DECL|macro|RX_IA_HASH_ACCEPT
mdefine_line|#define RX_IA_HASH_ACCEPT 0x0040
DECL|macro|RX_PROM_ACCEPT
mdefine_line|#define RX_PROM_ACCEPT 0x0080
DECL|macro|RX_OK_ACCEPT
mdefine_line|#define RX_OK_ACCEPT 0x0100
DECL|macro|RX_MULTCAST_ACCEPT
mdefine_line|#define RX_MULTCAST_ACCEPT 0x0200
DECL|macro|RX_IA_ACCEPT
mdefine_line|#define RX_IA_ACCEPT 0x0400
DECL|macro|RX_BROADCAST_ACCEPT
mdefine_line|#define RX_BROADCAST_ACCEPT 0x0800
DECL|macro|RX_BAD_CRC_ACCEPT
mdefine_line|#define RX_BAD_CRC_ACCEPT 0x1000
DECL|macro|RX_RUNT_ACCEPT
mdefine_line|#define RX_RUNT_ACCEPT 0x2000
DECL|macro|RX_EXTRA_DATA_ACCEPT
mdefine_line|#define RX_EXTRA_DATA_ACCEPT 0x4000
DECL|macro|RX_ALL_ACCEPT
mdefine_line|#define RX_ALL_ACCEPT (RX_PROM_ACCEPT|RX_BAD_CRC_ACCEPT|RX_RUNT_ACCEPT|RX_EXTRA_DATA_ACCEPT)
multiline_comment|/*  Default receive mode - individually addressed, broadcast, and error free */
DECL|macro|DEF_RX_ACCEPT
mdefine_line|#define DEF_RX_ACCEPT (RX_IA_ACCEPT | RX_BROADCAST_ACCEPT | RX_OK_ACCEPT)
multiline_comment|/* PP_TxCFG - Transmit Configuration Interrupt Mask bit definition - Read/write */
DECL|macro|TX_LOST_CRS_ENBL
mdefine_line|#define TX_LOST_CRS_ENBL 0x0040
DECL|macro|TX_SQE_ERROR_ENBL
mdefine_line|#define TX_SQE_ERROR_ENBL 0x0080
DECL|macro|TX_OK_ENBL
mdefine_line|#define TX_OK_ENBL 0x0100
DECL|macro|TX_LATE_COL_ENBL
mdefine_line|#define TX_LATE_COL_ENBL 0x0200
DECL|macro|TX_JBR_ENBL
mdefine_line|#define TX_JBR_ENBL 0x0400
DECL|macro|TX_ANY_COL_ENBL
mdefine_line|#define TX_ANY_COL_ENBL 0x0800
DECL|macro|TX_16_COL_ENBL
mdefine_line|#define TX_16_COL_ENBL 0x8000
multiline_comment|/* PP_TxCMD - Transmit Command bit definition - Read-only */
DECL|macro|TX_START_4_BYTES
mdefine_line|#define TX_START_4_BYTES 0x0000
DECL|macro|TX_START_64_BYTES
mdefine_line|#define TX_START_64_BYTES 0x0040
DECL|macro|TX_START_128_BYTES
mdefine_line|#define TX_START_128_BYTES 0x0080
DECL|macro|TX_START_ALL_BYTES
mdefine_line|#define TX_START_ALL_BYTES 0x00C0
DECL|macro|TX_FORCE
mdefine_line|#define TX_FORCE 0x0100
DECL|macro|TX_ONE_COL
mdefine_line|#define TX_ONE_COL 0x0200
DECL|macro|TX_TWO_PART_DEFF_DISABLE
mdefine_line|#define TX_TWO_PART_DEFF_DISABLE 0x0400
DECL|macro|TX_NO_CRC
mdefine_line|#define TX_NO_CRC 0x1000
DECL|macro|TX_RUNT
mdefine_line|#define TX_RUNT 0x2000
multiline_comment|/* PP_BufCFG - Buffer Configuration Interrupt Mask bit definition - Read/write */
DECL|macro|GENERATE_SW_INTERRUPT
mdefine_line|#define GENERATE_SW_INTERRUPT 0x0040
DECL|macro|RX_DMA_ENBL
mdefine_line|#define RX_DMA_ENBL 0x0080
DECL|macro|READY_FOR_TX_ENBL
mdefine_line|#define READY_FOR_TX_ENBL 0x0100
DECL|macro|TX_UNDERRUN_ENBL
mdefine_line|#define TX_UNDERRUN_ENBL 0x0200
DECL|macro|RX_MISS_ENBL
mdefine_line|#define RX_MISS_ENBL 0x0400
DECL|macro|RX_128_BYTE_ENBL
mdefine_line|#define RX_128_BYTE_ENBL 0x0800
DECL|macro|TX_COL_COUNT_OVRFLOW_ENBL
mdefine_line|#define TX_COL_COUNT_OVRFLOW_ENBL 0x1000
DECL|macro|RX_MISS_COUNT_OVRFLOW_ENBL
mdefine_line|#define RX_MISS_COUNT_OVRFLOW_ENBL 0x2000
DECL|macro|RX_DEST_MATCH_ENBL
mdefine_line|#define RX_DEST_MATCH_ENBL 0x8000
multiline_comment|/* PP_LineCTL - Line Control bit definition - Read/write */
DECL|macro|SERIAL_RX_ON
mdefine_line|#define SERIAL_RX_ON 0x0040
DECL|macro|SERIAL_TX_ON
mdefine_line|#define SERIAL_TX_ON 0x0080
DECL|macro|AUI_ONLY
mdefine_line|#define AUI_ONLY 0x0100
DECL|macro|AUTO_AUI_10BASET
mdefine_line|#define AUTO_AUI_10BASET 0x0200
DECL|macro|MODIFIED_BACKOFF
mdefine_line|#define MODIFIED_BACKOFF 0x0800
DECL|macro|NO_AUTO_POLARITY
mdefine_line|#define NO_AUTO_POLARITY 0x1000
DECL|macro|TWO_PART_DEFDIS
mdefine_line|#define TWO_PART_DEFDIS 0x2000
DECL|macro|LOW_RX_SQUELCH
mdefine_line|#define LOW_RX_SQUELCH 0x4000
multiline_comment|/* PP_SelfCTL - Software Self Control bit definition - Read/write */
DECL|macro|POWER_ON_RESET
mdefine_line|#define POWER_ON_RESET 0x0040
DECL|macro|SW_STOP
mdefine_line|#define SW_STOP 0x0100
DECL|macro|SLEEP_ON
mdefine_line|#define SLEEP_ON 0x0200
DECL|macro|AUTO_WAKEUP
mdefine_line|#define AUTO_WAKEUP 0x0400
DECL|macro|HCB0_ENBL
mdefine_line|#define HCB0_ENBL 0x1000
DECL|macro|HCB1_ENBL
mdefine_line|#define HCB1_ENBL 0x2000
DECL|macro|HCB0
mdefine_line|#define HCB0 0x4000
DECL|macro|HCB1
mdefine_line|#define HCB1 0x8000
multiline_comment|/* PP_BusCTL - ISA Bus Control bit definition - Read/write */
DECL|macro|RESET_RX_DMA
mdefine_line|#define RESET_RX_DMA 0x0040
DECL|macro|MEMORY_ON
mdefine_line|#define MEMORY_ON 0x0400
DECL|macro|DMA_BURST_MODE
mdefine_line|#define DMA_BURST_MODE 0x0800
DECL|macro|IO_CHANNEL_READY_ON
mdefine_line|#define IO_CHANNEL_READY_ON 0x1000
DECL|macro|RX_DMA_SIZE_64K
mdefine_line|#define RX_DMA_SIZE_64K 0x2000
DECL|macro|ENABLE_IRQ
mdefine_line|#define ENABLE_IRQ 0x8000
multiline_comment|/* PP_TestCTL - Test Control bit definition - Read/write */
DECL|macro|LINK_OFF
mdefine_line|#define LINK_OFF 0x0080
DECL|macro|ENDEC_LOOPBACK
mdefine_line|#define ENDEC_LOOPBACK 0x0200
DECL|macro|AUI_LOOPBACK
mdefine_line|#define AUI_LOOPBACK 0x0400
DECL|macro|BACKOFF_OFF
mdefine_line|#define BACKOFF_OFF 0x0800
DECL|macro|FDX_8900
mdefine_line|#define FDX_8900 0x4000
DECL|macro|FAST_TEST
mdefine_line|#define FAST_TEST 0x8000
multiline_comment|/* PP_RxEvent - Receive Event Bit definition - Read-only */
DECL|macro|RX_IA_HASHED
mdefine_line|#define RX_IA_HASHED 0x0040
DECL|macro|RX_DRIBBLE
mdefine_line|#define RX_DRIBBLE 0x0080
DECL|macro|RX_OK
mdefine_line|#define RX_OK 0x0100
DECL|macro|RX_HASHED
mdefine_line|#define RX_HASHED 0x0200
DECL|macro|RX_IA
mdefine_line|#define RX_IA 0x0400
DECL|macro|RX_BROADCAST
mdefine_line|#define RX_BROADCAST 0x0800
DECL|macro|RX_CRC_ERROR
mdefine_line|#define RX_CRC_ERROR 0x1000
DECL|macro|RX_RUNT
mdefine_line|#define RX_RUNT 0x2000
DECL|macro|RX_EXTRA_DATA
mdefine_line|#define RX_EXTRA_DATA 0x4000
DECL|macro|HASH_INDEX_MASK
mdefine_line|#define HASH_INDEX_MASK 0x0FC00
multiline_comment|/* PP_TxEvent - Transmit Event Bit definition - Read-only */
DECL|macro|TX_LOST_CRS
mdefine_line|#define TX_LOST_CRS 0x0040
DECL|macro|TX_SQE_ERROR
mdefine_line|#define TX_SQE_ERROR 0x0080
DECL|macro|TX_OK
mdefine_line|#define TX_OK 0x0100
DECL|macro|TX_LATE_COL
mdefine_line|#define TX_LATE_COL 0x0200
DECL|macro|TX_JBR
mdefine_line|#define TX_JBR 0x0400
DECL|macro|TX_16_COL
mdefine_line|#define TX_16_COL 0x8000
DECL|macro|TX_SEND_OK_BITS
mdefine_line|#define TX_SEND_OK_BITS (TX_OK|TX_LOST_CRS)
DECL|macro|TX_COL_COUNT_MASK
mdefine_line|#define TX_COL_COUNT_MASK 0x7800
multiline_comment|/* PP_BufEvent - Buffer Event Bit definition - Read-only */
DECL|macro|SW_INTERRUPT
mdefine_line|#define SW_INTERRUPT 0x0040
DECL|macro|RX_DMA
mdefine_line|#define RX_DMA 0x0080
DECL|macro|READY_FOR_TX
mdefine_line|#define READY_FOR_TX 0x0100
DECL|macro|TX_UNDERRUN
mdefine_line|#define TX_UNDERRUN 0x0200
DECL|macro|RX_MISS
mdefine_line|#define RX_MISS 0x0400
DECL|macro|RX_128_BYTE
mdefine_line|#define RX_128_BYTE 0x0800
DECL|macro|TX_COL_OVRFLW
mdefine_line|#define TX_COL_OVRFLW 0x1000
DECL|macro|RX_MISS_OVRFLW
mdefine_line|#define RX_MISS_OVRFLW 0x2000
DECL|macro|RX_DEST_MATCH
mdefine_line|#define RX_DEST_MATCH 0x8000
multiline_comment|/* PP_LineST - Ethernet Line Status bit definition - Read-only */
DECL|macro|LINK_OK
mdefine_line|#define LINK_OK 0x0080
DECL|macro|AUI_ON
mdefine_line|#define AUI_ON 0x0100
DECL|macro|TENBASET_ON
mdefine_line|#define TENBASET_ON 0x0200
DECL|macro|POLARITY_OK
mdefine_line|#define POLARITY_OK 0x1000
DECL|macro|CRS_OK
mdefine_line|#define CRS_OK 0x4000
multiline_comment|/* PP_SelfST - Chip Software Status bit definition */
DECL|macro|ACTIVE_33V
mdefine_line|#define ACTIVE_33V 0x0040
DECL|macro|INIT_DONE
mdefine_line|#define INIT_DONE 0x0080
DECL|macro|SI_BUSY
mdefine_line|#define SI_BUSY 0x0100
DECL|macro|EEPROM_PRESENT
mdefine_line|#define EEPROM_PRESENT 0x0200
DECL|macro|EEPROM_OK
mdefine_line|#define EEPROM_OK 0x0400
DECL|macro|EL_PRESENT
mdefine_line|#define EL_PRESENT 0x0800
DECL|macro|EE_SIZE_64
mdefine_line|#define EE_SIZE_64 0x1000
multiline_comment|/* PP_BusST - ISA Bus Status bit definition */
DECL|macro|TX_BID_ERROR
mdefine_line|#define TX_BID_ERROR 0x0080
DECL|macro|READY_FOR_TX_NOW
mdefine_line|#define READY_FOR_TX_NOW 0x0100
multiline_comment|/* PP_AutoNegCTL - Auto Negotiation Control bit definition */
DECL|macro|RE_NEG_NOW
mdefine_line|#define RE_NEG_NOW 0x0040
DECL|macro|ALLOW_FDX
mdefine_line|#define ALLOW_FDX 0x0080
DECL|macro|AUTO_NEG_ENABLE
mdefine_line|#define AUTO_NEG_ENABLE 0x0100
DECL|macro|NLP_ENABLE
mdefine_line|#define NLP_ENABLE 0x0200
DECL|macro|FORCE_FDX
mdefine_line|#define FORCE_FDX 0x8000
DECL|macro|AUTO_NEG_BITS
mdefine_line|#define AUTO_NEG_BITS (FORCE_FDX|NLP_ENABLE|AUTO_NEG_ENABLE)
DECL|macro|AUTO_NEG_MASK
mdefine_line|#define AUTO_NEG_MASK (FORCE_FDX|NLP_ENABLE|AUTO_NEG_ENABLE|ALLOW_FDX|RE_NEG_NOW)
multiline_comment|/* PP_AutoNegST - Auto Negotiation Status bit definition */
DECL|macro|AUTO_NEG_BUSY
mdefine_line|#define AUTO_NEG_BUSY 0x0080
DECL|macro|FLP_LINK
mdefine_line|#define FLP_LINK 0x0100
DECL|macro|FLP_LINK_GOOD
mdefine_line|#define FLP_LINK_GOOD 0x0800
DECL|macro|LINK_FAULT
mdefine_line|#define LINK_FAULT 0x1000
DECL|macro|HDX_ACTIVE
mdefine_line|#define HDX_ACTIVE 0x4000
DECL|macro|FDX_ACTIVE
mdefine_line|#define FDX_ACTIVE 0x8000
multiline_comment|/*  The following block defines the ISQ event types */
DECL|macro|ISQ_RECEIVER_EVENT
mdefine_line|#define ISQ_RECEIVER_EVENT 0x04
DECL|macro|ISQ_TRANSMITTER_EVENT
mdefine_line|#define ISQ_TRANSMITTER_EVENT 0x08
DECL|macro|ISQ_BUFFER_EVENT
mdefine_line|#define ISQ_BUFFER_EVENT 0x0c
DECL|macro|ISQ_RX_MISS_EVENT
mdefine_line|#define ISQ_RX_MISS_EVENT 0x10
DECL|macro|ISQ_TX_COL_EVENT
mdefine_line|#define ISQ_TX_COL_EVENT 0x12
DECL|macro|ISQ_EVENT_MASK
mdefine_line|#define ISQ_EVENT_MASK 0x003F   /*  ISQ mask to find out type of event */
DECL|macro|ISQ_HIST
mdefine_line|#define ISQ_HIST 16&t;&t;/*  small history buffer */
DECL|macro|AUTOINCREMENT
mdefine_line|#define AUTOINCREMENT 0x8000&t;/*  Bit mask to set bit-15 for autoincrement */
DECL|macro|TXRXBUFSIZE
mdefine_line|#define TXRXBUFSIZE 0x0600
DECL|macro|RXDMABUFSIZE
mdefine_line|#define RXDMABUFSIZE 0x8000
DECL|macro|RXDMASIZE
mdefine_line|#define RXDMASIZE 0x4000
DECL|macro|TXRX_LENGTH_MASK
mdefine_line|#define TXRX_LENGTH_MASK 0x07FF
multiline_comment|/*  rx options bits */
DECL|macro|RCV_WITH_RXON
mdefine_line|#define RCV_WITH_RXON&t;1       /*  Set SerRx ON */
DECL|macro|RCV_COUNTS
mdefine_line|#define RCV_COUNTS&t;2       /*  Use Framecnt1 */
DECL|macro|RCV_PONG
mdefine_line|#define RCV_PONG&t;4       /*  Pong respondent */
DECL|macro|RCV_DONG
mdefine_line|#define RCV_DONG&t;8       /*  Dong operation */
DECL|macro|RCV_POLLING
mdefine_line|#define RCV_POLLING&t;0x10&t;/*  Poll RxEvent */
DECL|macro|RCV_ISQ
mdefine_line|#define RCV_ISQ&t;&t;0x20&t;/*  Use ISQ, int */
DECL|macro|RCV_AUTO_DMA
mdefine_line|#define RCV_AUTO_DMA&t;0x100&t;/*  Set AutoRxDMAE */
DECL|macro|RCV_DMA
mdefine_line|#define RCV_DMA&t;&t;0x200&t;/*  Set RxDMA only */
DECL|macro|RCV_DMA_ALL
mdefine_line|#define RCV_DMA_ALL&t;0x400&t;/*  Copy all DMA&squot;ed */
DECL|macro|RCV_FIXED_DATA
mdefine_line|#define RCV_FIXED_DATA&t;0x800&t;/*  Every frame same */
DECL|macro|RCV_IO
mdefine_line|#define RCV_IO&t;&t;0x1000&t;/*  Use ISA IO only */
DECL|macro|RCV_MEMORY
mdefine_line|#define RCV_MEMORY&t;0x2000&t;/*  Use ISA Memory */
DECL|macro|RAM_SIZE
mdefine_line|#define RAM_SIZE&t;0x1000       /*  The card has 4k bytes or RAM */
DECL|macro|PKT_START
mdefine_line|#define PKT_START PP_TxFrame  /*  Start of packet RAM */
DECL|macro|RX_FRAME_PORT
mdefine_line|#define RX_FRAME_PORT&t;0x0000
DECL|macro|TX_FRAME_PORT
mdefine_line|#define TX_FRAME_PORT RX_FRAME_PORT
DECL|macro|TX_CMD_PORT
mdefine_line|#define TX_CMD_PORT&t;0x0004
DECL|macro|TX_NOW
mdefine_line|#define TX_NOW&t;&t;0x0000       /*  Tx packet after   5 bytes copied */
DECL|macro|TX_AFTER_381
mdefine_line|#define TX_AFTER_381&t;0x0040       /*  Tx packet after 381 bytes copied */
DECL|macro|TX_AFTER_ALL
mdefine_line|#define TX_AFTER_ALL&t;0x00c0       /*  Tx packet after all bytes copied */
DECL|macro|TX_LEN_PORT
mdefine_line|#define TX_LEN_PORT&t;0x0006
DECL|macro|ISQ_PORT
mdefine_line|#define ISQ_PORT&t;0x0008
DECL|macro|ADD_PORT
mdefine_line|#define ADD_PORT&t;0x000A
DECL|macro|DATA_PORT
mdefine_line|#define DATA_PORT&t;0x000C
DECL|macro|EEPROM_WRITE_EN
mdefine_line|#define EEPROM_WRITE_EN&t;&t;0x00F0
DECL|macro|EEPROM_WRITE_DIS
mdefine_line|#define EEPROM_WRITE_DIS&t;0x0000
DECL|macro|EEPROM_WRITE_CMD
mdefine_line|#define EEPROM_WRITE_CMD&t;0x0100
DECL|macro|EEPROM_READ_CMD
mdefine_line|#define EEPROM_READ_CMD&t;&t;0x0200
multiline_comment|/*  Receive Header */
multiline_comment|/*  Description of header of each packet in receive area of memory */
DECL|macro|RBUF_EVENT_LOW
mdefine_line|#define RBUF_EVENT_LOW&t;0   /*  Low byte of RxEvent - status of received frame */
DECL|macro|RBUF_EVENT_HIGH
mdefine_line|#define RBUF_EVENT_HIGH&t;1   /*  High byte of RxEvent - status of received frame */
DECL|macro|RBUF_LEN_LOW
mdefine_line|#define RBUF_LEN_LOW&t;2   /*  Length of received data - low byte */
DECL|macro|RBUF_LEN_HI
mdefine_line|#define RBUF_LEN_HI&t;3   /*  Length of received data - high byte */
DECL|macro|RBUF_HEAD_LEN
mdefine_line|#define RBUF_HEAD_LEN&t;4   /*  Length of this header */
DECL|macro|CHIP_READ
mdefine_line|#define CHIP_READ 0x1   /*  Used to mark state of the repins code (chip or dma) */
DECL|macro|DMA_READ
mdefine_line|#define DMA_READ 0x2   /*  Used to mark state of the repins code (chip or dma) */
multiline_comment|/*  for bios scan */
multiline_comment|/*  */
macro_line|#ifdef CSDEBUG
multiline_comment|/*  use these values for debugging bios scan */
DECL|macro|BIOS_START_SEG
mdefine_line|#define BIOS_START_SEG 0x00000
DECL|macro|BIOS_OFFSET_INC
mdefine_line|#define BIOS_OFFSET_INC 0x0010
macro_line|#else
DECL|macro|BIOS_START_SEG
mdefine_line|#define BIOS_START_SEG 0x0c000
DECL|macro|BIOS_OFFSET_INC
mdefine_line|#define BIOS_OFFSET_INC 0x0200
macro_line|#endif
DECL|macro|BIOS_LAST_OFFSET
mdefine_line|#define BIOS_LAST_OFFSET 0x0fc00
multiline_comment|/*  Byte offsets into the EEPROM configuration buffer */
DECL|macro|ISA_CNF_OFFSET
mdefine_line|#define ISA_CNF_OFFSET 0x6
DECL|macro|TX_CTL_OFFSET
mdefine_line|#define TX_CTL_OFFSET (ISA_CNF_OFFSET + 8)&t;&t;&t;/*  8900 eeprom */
DECL|macro|AUTO_NEG_CNF_OFFSET
mdefine_line|#define AUTO_NEG_CNF_OFFSET (ISA_CNF_OFFSET + 8)&t;&t;/*  8920 eeprom */
multiline_comment|/*  the assumption here is that the bits in the eeprom are generally  */
multiline_comment|/*  in the same position as those in the autonegctl register. */
multiline_comment|/*  Of course the IMM bit is not in that register so it must be  */
multiline_comment|/*  masked out */
DECL|macro|EE_FORCE_FDX
mdefine_line|#define EE_FORCE_FDX  0x8000
DECL|macro|EE_NLP_ENABLE
mdefine_line|#define EE_NLP_ENABLE 0x0200
DECL|macro|EE_AUTO_NEG_ENABLE
mdefine_line|#define EE_AUTO_NEG_ENABLE 0x0100
DECL|macro|EE_ALLOW_FDX
mdefine_line|#define EE_ALLOW_FDX 0x0080
DECL|macro|EE_AUTO_NEG_CNF_MASK
mdefine_line|#define EE_AUTO_NEG_CNF_MASK (EE_FORCE_FDX|EE_NLP_ENABLE|EE_AUTO_NEG_ENABLE|EE_ALLOW_FDX)
DECL|macro|IMM_BIT
mdefine_line|#define IMM_BIT 0x0040&t;&t;/*  ignore missing media&t; */
DECL|macro|ADAPTER_CNF_OFFSET
mdefine_line|#define ADAPTER_CNF_OFFSET (AUTO_NEG_CNF_OFFSET + 2)
DECL|macro|A_CNF_10B_T
mdefine_line|#define A_CNF_10B_T 0x0001
DECL|macro|A_CNF_AUI
mdefine_line|#define A_CNF_AUI 0x0002
DECL|macro|A_CNF_10B_2
mdefine_line|#define A_CNF_10B_2 0x0004
DECL|macro|A_CNF_MEDIA_TYPE
mdefine_line|#define A_CNF_MEDIA_TYPE 0x0060
DECL|macro|A_CNF_MEDIA_AUTO
mdefine_line|#define A_CNF_MEDIA_AUTO 0x0000
DECL|macro|A_CNF_MEDIA_10B_T
mdefine_line|#define A_CNF_MEDIA_10B_T 0x0020
DECL|macro|A_CNF_MEDIA_AUI
mdefine_line|#define A_CNF_MEDIA_AUI 0x0040
DECL|macro|A_CNF_MEDIA_10B_2
mdefine_line|#define A_CNF_MEDIA_10B_2 0x0060
DECL|macro|A_CNF_DC_DC_POLARITY
mdefine_line|#define A_CNF_DC_DC_POLARITY 0x0080
DECL|macro|A_CNF_NO_AUTO_POLARITY
mdefine_line|#define A_CNF_NO_AUTO_POLARITY 0x2000
DECL|macro|A_CNF_LOW_RX_SQUELCH
mdefine_line|#define A_CNF_LOW_RX_SQUELCH 0x4000
DECL|macro|A_CNF_EXTND_10B_2
mdefine_line|#define A_CNF_EXTND_10B_2 0x8000
DECL|macro|PACKET_PAGE_OFFSET
mdefine_line|#define PACKET_PAGE_OFFSET 0x8
multiline_comment|/*  Bit definitions for the ISA configuration word from the EEPROM */
DECL|macro|INT_NO_MASK
mdefine_line|#define INT_NO_MASK 0x000F
DECL|macro|DMA_NO_MASK
mdefine_line|#define DMA_NO_MASK 0x0070
DECL|macro|ISA_DMA_SIZE
mdefine_line|#define ISA_DMA_SIZE 0x0200
DECL|macro|ISA_AUTO_RxDMA
mdefine_line|#define ISA_AUTO_RxDMA 0x0400
DECL|macro|ISA_RxDMA
mdefine_line|#define ISA_RxDMA 0x0800
DECL|macro|DMA_BURST
mdefine_line|#define DMA_BURST 0x1000
DECL|macro|STREAM_TRANSFER
mdefine_line|#define STREAM_TRANSFER 0x2000
DECL|macro|ANY_ISA_DMA
mdefine_line|#define ANY_ISA_DMA (ISA_AUTO_RxDMA | ISA_RxDMA)
multiline_comment|/*  DMA controller registers */
DECL|macro|DMA_BASE
mdefine_line|#define DMA_BASE 0x00     /*  DMA controller base */
DECL|macro|DMA_BASE_2
mdefine_line|#define DMA_BASE_2 0x0C0    /*  DMA controller base */
DECL|macro|DMA_STAT
mdefine_line|#define DMA_STAT 0x0D0    /*  DMA controller status register */
DECL|macro|DMA_MASK
mdefine_line|#define DMA_MASK 0x0D4    /*  DMA controller mask register */
DECL|macro|DMA_MODE
mdefine_line|#define DMA_MODE 0x0D6    /*  DMA controller mode register */
DECL|macro|DMA_RESETFF
mdefine_line|#define DMA_RESETFF 0x0D8    /*  DMA controller first/last flip flop */
multiline_comment|/*  DMA data */
DECL|macro|DMA_DISABLE
mdefine_line|#define DMA_DISABLE 0x04     /*  Disable channel n */
DECL|macro|DMA_ENABLE
mdefine_line|#define DMA_ENABLE 0x00     /*  Enable channel n */
multiline_comment|/*  Demand transfers, incr. address, auto init, writes, ch. n */
DECL|macro|DMA_RX_MODE
mdefine_line|#define DMA_RX_MODE 0x14
multiline_comment|/*  Demand transfers, incr. address, auto init, reads, ch. n */
DECL|macro|DMA_TX_MODE
mdefine_line|#define DMA_TX_MODE 0x18
DECL|macro|DMA_SIZE
mdefine_line|#define DMA_SIZE (16*1024) /*  Size of dma buffer - 16k */
DECL|macro|CS8900
mdefine_line|#define CS8900 0x0000
DECL|macro|CS8920
mdefine_line|#define CS8920 0x4000   
DECL|macro|CS8920M
mdefine_line|#define CS8920M 0x6000   
DECL|macro|REVISON_BITS
mdefine_line|#define REVISON_BITS 0x1F00
DECL|macro|EEVER_NUMBER
mdefine_line|#define EEVER_NUMBER 0x12
DECL|macro|CHKSUM_LEN
mdefine_line|#define CHKSUM_LEN 0x14
DECL|macro|CHKSUM_VAL
mdefine_line|#define CHKSUM_VAL 0x0000
DECL|macro|START_EEPROM_DATA
mdefine_line|#define START_EEPROM_DATA 0x001c /*  Offset into eeprom for start of data */
DECL|macro|IRQ_MAP_EEPROM_DATA
mdefine_line|#define IRQ_MAP_EEPROM_DATA 0x0046 /*  Offset into eeprom for the IRQ map */
DECL|macro|IRQ_MAP_LEN
mdefine_line|#define IRQ_MAP_LEN 0x0004 /*  No of bytes to read for the IRQ map */
DECL|macro|PNP_IRQ_FRMT
mdefine_line|#define PNP_IRQ_FRMT 0x0022 /*  PNP small item IRQ format */
DECL|macro|CS8900_IRQ_MAP
mdefine_line|#define CS8900_IRQ_MAP 0x1c20 /*  This IRQ map is fixed */
DECL|macro|CS8920_NO_INTS
mdefine_line|#define CS8920_NO_INTS 0x0F   /*  Max CS8920 interrupt select # */
DECL|macro|PNP_ADD_PORT
mdefine_line|#define PNP_ADD_PORT 0x0279
DECL|macro|PNP_WRITE_PORT
mdefine_line|#define PNP_WRITE_PORT 0x0A79
DECL|macro|GET_PNP_ISA_STRUCT
mdefine_line|#define GET_PNP_ISA_STRUCT 0x40
DECL|macro|PNP_ISA_STRUCT_LEN
mdefine_line|#define PNP_ISA_STRUCT_LEN 0x06
DECL|macro|PNP_CSN_CNT_OFF
mdefine_line|#define PNP_CSN_CNT_OFF 0x01
DECL|macro|PNP_RD_PORT_OFF
mdefine_line|#define PNP_RD_PORT_OFF 0x02
DECL|macro|PNP_FUNCTION_OK
mdefine_line|#define PNP_FUNCTION_OK 0x00
DECL|macro|PNP_WAKE
mdefine_line|#define PNP_WAKE 0x03
DECL|macro|PNP_RSRC_DATA
mdefine_line|#define PNP_RSRC_DATA 0x04
DECL|macro|PNP_RSRC_READY
mdefine_line|#define PNP_RSRC_READY 0x01
DECL|macro|PNP_STATUS
mdefine_line|#define PNP_STATUS 0x05
DECL|macro|PNP_ACTIVATE
mdefine_line|#define PNP_ACTIVATE 0x30
DECL|macro|PNP_CNF_IO_H
mdefine_line|#define PNP_CNF_IO_H 0x60
DECL|macro|PNP_CNF_IO_L
mdefine_line|#define PNP_CNF_IO_L 0x61
DECL|macro|PNP_CNF_INT
mdefine_line|#define PNP_CNF_INT 0x70
DECL|macro|PNP_CNF_DMA
mdefine_line|#define PNP_CNF_DMA 0x74
DECL|macro|PNP_CNF_MEM
mdefine_line|#define PNP_CNF_MEM 0x48
DECL|macro|BIT0
mdefine_line|#define BIT0 1
DECL|macro|BIT15
mdefine_line|#define BIT15 0x8000
eof
