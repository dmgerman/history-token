multiline_comment|/*&n; * SyncLink Multiprotocol Serial Adapter Driver&n; *&n; * $Id: synclink.h,v 3.5 2001/03/26 17:04:36 ez Exp $&n; *&n; * Copyright (C) 1998-2000 by Microgate Corporation&n; * &n; * Redistribution of this file is permitted under &n; * the terms of the GNU Public License (GPL)&n; */
macro_line|#ifndef _SYNCLINK_H_
DECL|macro|_SYNCLINK_H_
mdefine_line|#define _SYNCLINK_H_
DECL|macro|SYNCLINK_H_VERSION
mdefine_line|#define SYNCLINK_H_VERSION 3.5
DECL|macro|BOOLEAN
mdefine_line|#define BOOLEAN int
DECL|macro|TRUE
mdefine_line|#define TRUE 1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|BIT0
mdefine_line|#define BIT0&t;0x0001
DECL|macro|BIT1
mdefine_line|#define BIT1&t;0x0002
DECL|macro|BIT2
mdefine_line|#define BIT2&t;0x0004
DECL|macro|BIT3
mdefine_line|#define BIT3&t;0x0008
DECL|macro|BIT4
mdefine_line|#define BIT4&t;0x0010
DECL|macro|BIT5
mdefine_line|#define BIT5&t;0x0020
DECL|macro|BIT6
mdefine_line|#define BIT6&t;0x0040
DECL|macro|BIT7
mdefine_line|#define BIT7&t;0x0080
DECL|macro|BIT8
mdefine_line|#define BIT8&t;0x0100
DECL|macro|BIT9
mdefine_line|#define BIT9&t;0x0200
DECL|macro|BIT10
mdefine_line|#define BIT10&t;0x0400
DECL|macro|BIT11
mdefine_line|#define BIT11&t;0x0800
DECL|macro|BIT12
mdefine_line|#define BIT12&t;0x1000
DECL|macro|BIT13
mdefine_line|#define BIT13&t;0x2000
DECL|macro|BIT14
mdefine_line|#define BIT14&t;0x4000
DECL|macro|BIT15
mdefine_line|#define BIT15&t;0x8000
DECL|macro|BIT16
mdefine_line|#define BIT16&t;0x00010000
DECL|macro|BIT17
mdefine_line|#define BIT17&t;0x00020000
DECL|macro|BIT18
mdefine_line|#define BIT18&t;0x00040000
DECL|macro|BIT19
mdefine_line|#define BIT19&t;0x00080000
DECL|macro|BIT20
mdefine_line|#define BIT20&t;0x00100000
DECL|macro|BIT21
mdefine_line|#define BIT21&t;0x00200000
DECL|macro|BIT22
mdefine_line|#define BIT22&t;0x00400000
DECL|macro|BIT23
mdefine_line|#define BIT23&t;0x00800000
DECL|macro|BIT24
mdefine_line|#define BIT24&t;0x01000000
DECL|macro|BIT25
mdefine_line|#define BIT25&t;0x02000000
DECL|macro|BIT26
mdefine_line|#define BIT26&t;0x04000000
DECL|macro|BIT27
mdefine_line|#define BIT27&t;0x08000000
DECL|macro|BIT28
mdefine_line|#define BIT28&t;0x10000000
DECL|macro|BIT29
mdefine_line|#define BIT29&t;0x20000000
DECL|macro|BIT30
mdefine_line|#define BIT30&t;0x40000000
DECL|macro|BIT31
mdefine_line|#define BIT31&t;0x80000000
DECL|macro|HDLC_MAX_FRAME_SIZE
mdefine_line|#define HDLC_MAX_FRAME_SIZE&t;65535
DECL|macro|MAX_ASYNC_TRANSMIT
mdefine_line|#define MAX_ASYNC_TRANSMIT&t;4096
DECL|macro|MAX_ASYNC_BUFFER_SIZE
mdefine_line|#define MAX_ASYNC_BUFFER_SIZE&t;4096
DECL|macro|ASYNC_PARITY_NONE
mdefine_line|#define ASYNC_PARITY_NONE&t;&t;0
DECL|macro|ASYNC_PARITY_EVEN
mdefine_line|#define ASYNC_PARITY_EVEN&t;&t;1
DECL|macro|ASYNC_PARITY_ODD
mdefine_line|#define ASYNC_PARITY_ODD&t;&t;2
DECL|macro|ASYNC_PARITY_SPACE
mdefine_line|#define ASYNC_PARITY_SPACE&t;&t;3
DECL|macro|HDLC_FLAG_UNDERRUN_ABORT7
mdefine_line|#define HDLC_FLAG_UNDERRUN_ABORT7&t;0x0000
DECL|macro|HDLC_FLAG_UNDERRUN_ABORT15
mdefine_line|#define HDLC_FLAG_UNDERRUN_ABORT15&t;0x0001
DECL|macro|HDLC_FLAG_UNDERRUN_FLAG
mdefine_line|#define HDLC_FLAG_UNDERRUN_FLAG&t;&t;0x0002
DECL|macro|HDLC_FLAG_UNDERRUN_CRC
mdefine_line|#define HDLC_FLAG_UNDERRUN_CRC&t;&t;0x0004
DECL|macro|HDLC_FLAG_SHARE_ZERO
mdefine_line|#define HDLC_FLAG_SHARE_ZERO&t;&t;0x0010
DECL|macro|HDLC_FLAG_AUTO_CTS
mdefine_line|#define HDLC_FLAG_AUTO_CTS&t;&t;0x0020
DECL|macro|HDLC_FLAG_AUTO_DCD
mdefine_line|#define HDLC_FLAG_AUTO_DCD&t;&t;0x0040
DECL|macro|HDLC_FLAG_AUTO_RTS
mdefine_line|#define HDLC_FLAG_AUTO_RTS&t;&t;0x0080
DECL|macro|HDLC_FLAG_RXC_DPLL
mdefine_line|#define HDLC_FLAG_RXC_DPLL&t;&t;0x0100
DECL|macro|HDLC_FLAG_RXC_BRG
mdefine_line|#define HDLC_FLAG_RXC_BRG&t;&t;0x0200
DECL|macro|HDLC_FLAG_RXC_TXCPIN
mdefine_line|#define HDLC_FLAG_RXC_TXCPIN&t;&t;0x8000
DECL|macro|HDLC_FLAG_RXC_RXCPIN
mdefine_line|#define HDLC_FLAG_RXC_RXCPIN&t;&t;0x0000
DECL|macro|HDLC_FLAG_TXC_DPLL
mdefine_line|#define HDLC_FLAG_TXC_DPLL&t;&t;0x0400
DECL|macro|HDLC_FLAG_TXC_BRG
mdefine_line|#define HDLC_FLAG_TXC_BRG&t;&t;0x0800
DECL|macro|HDLC_FLAG_TXC_TXCPIN
mdefine_line|#define HDLC_FLAG_TXC_TXCPIN&t;&t;0x0000
DECL|macro|HDLC_FLAG_TXC_RXCPIN
mdefine_line|#define HDLC_FLAG_TXC_RXCPIN&t;&t;0x0008
DECL|macro|HDLC_FLAG_DPLL_DIV8
mdefine_line|#define HDLC_FLAG_DPLL_DIV8&t;&t;0x1000
DECL|macro|HDLC_FLAG_DPLL_DIV16
mdefine_line|#define HDLC_FLAG_DPLL_DIV16&t;&t;0x2000
DECL|macro|HDLC_FLAG_DPLL_DIV32
mdefine_line|#define HDLC_FLAG_DPLL_DIV32&t;&t;0x0000
DECL|macro|HDLC_FLAG_HDLC_LOOPMODE
mdefine_line|#define HDLC_FLAG_HDLC_LOOPMODE&t;&t;0x4000
DECL|macro|HDLC_CRC_NONE
mdefine_line|#define HDLC_CRC_NONE&t;&t;&t;0
DECL|macro|HDLC_CRC_16_CCITT
mdefine_line|#define HDLC_CRC_16_CCITT&t;&t;1
DECL|macro|HDLC_CRC_32_CCITT
mdefine_line|#define HDLC_CRC_32_CCITT&t;&t;2
DECL|macro|HDLC_CRC_MASK
mdefine_line|#define HDLC_CRC_MASK&t;&t;&t;0x00ff
DECL|macro|HDLC_CRC_RETURN_EX
mdefine_line|#define HDLC_CRC_RETURN_EX&t;&t;0x8000
DECL|macro|RX_OK
mdefine_line|#define RX_OK&t;&t;&t;&t;0
DECL|macro|RX_CRC_ERROR
mdefine_line|#define RX_CRC_ERROR&t;&t;&t;1
DECL|macro|HDLC_TXIDLE_FLAGS
mdefine_line|#define HDLC_TXIDLE_FLAGS&t;&t;0
DECL|macro|HDLC_TXIDLE_ALT_ZEROS_ONES
mdefine_line|#define HDLC_TXIDLE_ALT_ZEROS_ONES&t;1
DECL|macro|HDLC_TXIDLE_ZEROS
mdefine_line|#define HDLC_TXIDLE_ZEROS&t;&t;2
DECL|macro|HDLC_TXIDLE_ONES
mdefine_line|#define HDLC_TXIDLE_ONES&t;&t;3
DECL|macro|HDLC_TXIDLE_ALT_MARK_SPACE
mdefine_line|#define HDLC_TXIDLE_ALT_MARK_SPACE&t;4
DECL|macro|HDLC_TXIDLE_SPACE
mdefine_line|#define HDLC_TXIDLE_SPACE&t;&t;5
DECL|macro|HDLC_TXIDLE_MARK
mdefine_line|#define HDLC_TXIDLE_MARK&t;&t;6
DECL|macro|HDLC_ENCODING_NRZ
mdefine_line|#define HDLC_ENCODING_NRZ&t;&t;&t;0
DECL|macro|HDLC_ENCODING_NRZB
mdefine_line|#define HDLC_ENCODING_NRZB&t;&t;&t;1
DECL|macro|HDLC_ENCODING_NRZI_MARK
mdefine_line|#define HDLC_ENCODING_NRZI_MARK&t;&t;&t;2
DECL|macro|HDLC_ENCODING_NRZI_SPACE
mdefine_line|#define HDLC_ENCODING_NRZI_SPACE&t;&t;3
DECL|macro|HDLC_ENCODING_NRZI
mdefine_line|#define HDLC_ENCODING_NRZI&t;&t;&t;HDLC_ENCODING_NRZI_SPACE
DECL|macro|HDLC_ENCODING_BIPHASE_MARK
mdefine_line|#define HDLC_ENCODING_BIPHASE_MARK&t;&t;4
DECL|macro|HDLC_ENCODING_BIPHASE_SPACE
mdefine_line|#define HDLC_ENCODING_BIPHASE_SPACE&t;&t;5
DECL|macro|HDLC_ENCODING_BIPHASE_LEVEL
mdefine_line|#define HDLC_ENCODING_BIPHASE_LEVEL&t;&t;6
DECL|macro|HDLC_ENCODING_DIFF_BIPHASE_LEVEL
mdefine_line|#define HDLC_ENCODING_DIFF_BIPHASE_LEVEL&t;7
DECL|macro|HDLC_PREAMBLE_LENGTH_8BITS
mdefine_line|#define HDLC_PREAMBLE_LENGTH_8BITS&t;0
DECL|macro|HDLC_PREAMBLE_LENGTH_16BITS
mdefine_line|#define HDLC_PREAMBLE_LENGTH_16BITS&t;1
DECL|macro|HDLC_PREAMBLE_LENGTH_32BITS
mdefine_line|#define HDLC_PREAMBLE_LENGTH_32BITS&t;2
DECL|macro|HDLC_PREAMBLE_LENGTH_64BITS
mdefine_line|#define HDLC_PREAMBLE_LENGTH_64BITS&t;3
DECL|macro|HDLC_PREAMBLE_PATTERN_NONE
mdefine_line|#define HDLC_PREAMBLE_PATTERN_NONE&t;0
DECL|macro|HDLC_PREAMBLE_PATTERN_ZEROS
mdefine_line|#define HDLC_PREAMBLE_PATTERN_ZEROS&t;1
DECL|macro|HDLC_PREAMBLE_PATTERN_FLAGS
mdefine_line|#define HDLC_PREAMBLE_PATTERN_FLAGS&t;2
DECL|macro|HDLC_PREAMBLE_PATTERN_10
mdefine_line|#define HDLC_PREAMBLE_PATTERN_10&t;3
DECL|macro|HDLC_PREAMBLE_PATTERN_01
mdefine_line|#define HDLC_PREAMBLE_PATTERN_01&t;4
DECL|macro|HDLC_PREAMBLE_PATTERN_ONES
mdefine_line|#define HDLC_PREAMBLE_PATTERN_ONES&t;5
DECL|macro|MGSL_MODE_ASYNC
mdefine_line|#define MGSL_MODE_ASYNC&t;&t;1
DECL|macro|MGSL_MODE_HDLC
mdefine_line|#define MGSL_MODE_HDLC&t;&t;2
DECL|macro|MGSL_MODE_RAW
mdefine_line|#define MGSL_MODE_RAW&t;&t;6
DECL|macro|MGSL_BUS_TYPE_ISA
mdefine_line|#define MGSL_BUS_TYPE_ISA&t;1
DECL|macro|MGSL_BUS_TYPE_EISA
mdefine_line|#define MGSL_BUS_TYPE_EISA&t;2
DECL|macro|MGSL_BUS_TYPE_PCI
mdefine_line|#define MGSL_BUS_TYPE_PCI&t;5
DECL|struct|_MGSL_PARAMS
r_typedef
r_struct
id|_MGSL_PARAMS
(brace
multiline_comment|/* Common */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* Asynchronous or HDLC */
DECL|member|loopback
r_int
r_char
id|loopback
suffix:semicolon
multiline_comment|/* internal loopback mode */
multiline_comment|/* HDLC Only */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|encoding
r_int
r_char
id|encoding
suffix:semicolon
multiline_comment|/* NRZ, NRZI, etc. */
DECL|member|clock_speed
r_int
r_int
id|clock_speed
suffix:semicolon
multiline_comment|/* external clock speed in bits per second */
DECL|member|addr_filter
r_int
r_char
id|addr_filter
suffix:semicolon
multiline_comment|/* receive HDLC address filter, 0xFF = disable */
DECL|member|crc_type
r_int
r_int
id|crc_type
suffix:semicolon
multiline_comment|/* None, CRC16-CCITT, or CRC32-CCITT */
DECL|member|preamble_length
r_int
r_char
id|preamble_length
suffix:semicolon
DECL|member|preamble
r_int
r_char
id|preamble
suffix:semicolon
multiline_comment|/* Async Only */
DECL|member|data_rate
r_int
r_int
id|data_rate
suffix:semicolon
multiline_comment|/* bits per second */
DECL|member|data_bits
r_int
r_char
id|data_bits
suffix:semicolon
multiline_comment|/* 7 or 8 data bits */
DECL|member|stop_bits
r_int
r_char
id|stop_bits
suffix:semicolon
multiline_comment|/* 1 or 2 stop bits */
DECL|member|parity
r_int
r_char
id|parity
suffix:semicolon
multiline_comment|/* none, even, or odd */
DECL|typedef|MGSL_PARAMS
DECL|typedef|PMGSL_PARAMS
)brace
id|MGSL_PARAMS
comma
op_star
id|PMGSL_PARAMS
suffix:semicolon
DECL|macro|MICROGATE_VENDOR_ID
mdefine_line|#define MICROGATE_VENDOR_ID 0x13c0
DECL|macro|SYNCLINK_DEVICE_ID
mdefine_line|#define SYNCLINK_DEVICE_ID 0x0010
DECL|macro|MGSCC_DEVICE_ID
mdefine_line|#define MGSCC_DEVICE_ID 0x0020
DECL|macro|SYNCLINK_SCA_DEVICE_ID
mdefine_line|#define SYNCLINK_SCA_DEVICE_ID 0x0030
DECL|macro|MGSL_MAX_SERIAL_NUMBER
mdefine_line|#define MGSL_MAX_SERIAL_NUMBER 30
multiline_comment|/*&n;** device diagnostics status&n;*/
DECL|macro|DiagStatus_OK
mdefine_line|#define DiagStatus_OK&t;&t;&t;&t;0
DECL|macro|DiagStatus_AddressFailure
mdefine_line|#define DiagStatus_AddressFailure&t;&t;1
DECL|macro|DiagStatus_AddressConflict
mdefine_line|#define DiagStatus_AddressConflict&t;&t;2
DECL|macro|DiagStatus_IrqFailure
mdefine_line|#define DiagStatus_IrqFailure&t;&t;&t;3
DECL|macro|DiagStatus_IrqConflict
mdefine_line|#define DiagStatus_IrqConflict&t;&t;&t;4
DECL|macro|DiagStatus_DmaFailure
mdefine_line|#define DiagStatus_DmaFailure&t;&t;&t;5
DECL|macro|DiagStatus_DmaConflict
mdefine_line|#define DiagStatus_DmaConflict&t;&t;&t;6
DECL|macro|DiagStatus_PciAdapterNotFound
mdefine_line|#define DiagStatus_PciAdapterNotFound&t;&t;7
DECL|macro|DiagStatus_CantAssignPciResources
mdefine_line|#define DiagStatus_CantAssignPciResources&t;8
DECL|macro|DiagStatus_CantAssignPciMemAddr
mdefine_line|#define DiagStatus_CantAssignPciMemAddr&t;&t;9
DECL|macro|DiagStatus_CantAssignPciIoAddr
mdefine_line|#define DiagStatus_CantAssignPciIoAddr&t;&t;10
DECL|macro|DiagStatus_CantAssignPciIrq
mdefine_line|#define DiagStatus_CantAssignPciIrq&t;&t;11
DECL|macro|DiagStatus_MemoryError
mdefine_line|#define DiagStatus_MemoryError&t;&t;&t;12
DECL|macro|SerialSignal_DCD
mdefine_line|#define SerialSignal_DCD            0x01     /* Data Carrier Detect */
DECL|macro|SerialSignal_TXD
mdefine_line|#define SerialSignal_TXD            0x02     /* Transmit Data */
DECL|macro|SerialSignal_RI
mdefine_line|#define SerialSignal_RI             0x04     /* Ring Indicator */
DECL|macro|SerialSignal_RXD
mdefine_line|#define SerialSignal_RXD            0x08     /* Receive Data */
DECL|macro|SerialSignal_CTS
mdefine_line|#define SerialSignal_CTS            0x10     /* Clear to Send */
DECL|macro|SerialSignal_RTS
mdefine_line|#define SerialSignal_RTS            0x20     /* Request to Send */
DECL|macro|SerialSignal_DSR
mdefine_line|#define SerialSignal_DSR            0x40     /* Data Set Ready */
DECL|macro|SerialSignal_DTR
mdefine_line|#define SerialSignal_DTR            0x80     /* Data Terminal Ready */
multiline_comment|/*&n; * Counters of the input lines (CTS, DSR, RI, CD) interrupts&n; */
DECL|struct|mgsl_icount
r_struct
id|mgsl_icount
(brace
DECL|member|cts
DECL|member|dsr
DECL|member|rng
DECL|member|dcd
DECL|member|tx
DECL|member|rx
id|__u32
id|cts
comma
id|dsr
comma
id|rng
comma
id|dcd
comma
id|tx
comma
id|rx
suffix:semicolon
DECL|member|frame
DECL|member|parity
DECL|member|overrun
DECL|member|brk
id|__u32
id|frame
comma
id|parity
comma
id|overrun
comma
id|brk
suffix:semicolon
DECL|member|buf_overrun
id|__u32
id|buf_overrun
suffix:semicolon
DECL|member|txok
id|__u32
id|txok
suffix:semicolon
DECL|member|txunder
id|__u32
id|txunder
suffix:semicolon
DECL|member|txabort
id|__u32
id|txabort
suffix:semicolon
DECL|member|txtimeout
id|__u32
id|txtimeout
suffix:semicolon
DECL|member|rxshort
id|__u32
id|rxshort
suffix:semicolon
DECL|member|rxlong
id|__u32
id|rxlong
suffix:semicolon
DECL|member|rxabort
id|__u32
id|rxabort
suffix:semicolon
DECL|member|rxover
id|__u32
id|rxover
suffix:semicolon
DECL|member|rxcrc
id|__u32
id|rxcrc
suffix:semicolon
DECL|member|rxok
id|__u32
id|rxok
suffix:semicolon
DECL|member|exithunt
id|__u32
id|exithunt
suffix:semicolon
DECL|member|rxidle
id|__u32
id|rxidle
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DEBUG_LEVEL_DATA
mdefine_line|#define DEBUG_LEVEL_DATA&t;1
DECL|macro|DEBUG_LEVEL_ERROR
mdefine_line|#define DEBUG_LEVEL_ERROR &t;2
DECL|macro|DEBUG_LEVEL_INFO
mdefine_line|#define DEBUG_LEVEL_INFO  &t;3
DECL|macro|DEBUG_LEVEL_BH
mdefine_line|#define DEBUG_LEVEL_BH    &t;4
DECL|macro|DEBUG_LEVEL_ISR
mdefine_line|#define DEBUG_LEVEL_ISR&t;&t;5
multiline_comment|/*&n;** Event bit flags for use with MgslWaitEvent&n;*/
DECL|macro|MgslEvent_DsrActive
mdefine_line|#define MgslEvent_DsrActive&t;0x0001
DECL|macro|MgslEvent_DsrInactive
mdefine_line|#define MgslEvent_DsrInactive&t;0x0002
DECL|macro|MgslEvent_Dsr
mdefine_line|#define MgslEvent_Dsr&t;&t;0x0003
DECL|macro|MgslEvent_CtsActive
mdefine_line|#define MgslEvent_CtsActive&t;0x0004
DECL|macro|MgslEvent_CtsInactive
mdefine_line|#define MgslEvent_CtsInactive&t;0x0008
DECL|macro|MgslEvent_Cts
mdefine_line|#define MgslEvent_Cts&t;&t;0x000c
DECL|macro|MgslEvent_DcdActive
mdefine_line|#define MgslEvent_DcdActive&t;0x0010
DECL|macro|MgslEvent_DcdInactive
mdefine_line|#define MgslEvent_DcdInactive&t;0x0020
DECL|macro|MgslEvent_Dcd
mdefine_line|#define MgslEvent_Dcd&t;&t;0x0030
DECL|macro|MgslEvent_RiActive
mdefine_line|#define MgslEvent_RiActive&t;0x0040
DECL|macro|MgslEvent_RiInactive
mdefine_line|#define MgslEvent_RiInactive&t;0x0080
DECL|macro|MgslEvent_Ri
mdefine_line|#define MgslEvent_Ri&t;&t;0x00c0
DECL|macro|MgslEvent_ExitHuntMode
mdefine_line|#define MgslEvent_ExitHuntMode&t;0x0100
DECL|macro|MgslEvent_IdleReceived
mdefine_line|#define MgslEvent_IdleReceived&t;0x0200
multiline_comment|/* Private IOCTL codes:&n; *&n; * MGSL_IOCSPARAMS&t;set MGSL_PARAMS structure values&n; * MGSL_IOCGPARAMS&t;get current MGSL_PARAMS structure values&n; * MGSL_IOCSTXIDLE&t;set current transmit idle mode&n; * MGSL_IOCGTXIDLE&t;get current transmit idle mode&n; * MGSL_IOCTXENABLE&t;enable or disable transmitter&n; * MGSL_IOCRXENABLE&t;enable or disable receiver&n; * MGSL_IOCTXABORT&t;abort transmitting frame (HDLC)&n; * MGSL_IOCGSTATS&t;return current statistics&n; * MGSL_IOCWAITEVENT&t;wait for specified event to occur&n; * MGSL_LOOPTXDONE&t;transmit in HDLC LoopMode done&n; */
DECL|macro|MGSL_MAGIC_IOC
mdefine_line|#define MGSL_MAGIC_IOC&t;&squot;m&squot;
DECL|macro|MGSL_IOCSPARAMS
mdefine_line|#define MGSL_IOCSPARAMS&t;&t;_IOW(MGSL_MAGIC_IOC,0,struct _MGSL_PARAMS)
DECL|macro|MGSL_IOCGPARAMS
mdefine_line|#define MGSL_IOCGPARAMS&t;&t;_IOR(MGSL_MAGIC_IOC,1,struct _MGSL_PARAMS)
DECL|macro|MGSL_IOCSTXIDLE
mdefine_line|#define MGSL_IOCSTXIDLE&t;&t;_IO(MGSL_MAGIC_IOC,2)
DECL|macro|MGSL_IOCGTXIDLE
mdefine_line|#define MGSL_IOCGTXIDLE&t;&t;_IO(MGSL_MAGIC_IOC,3)
DECL|macro|MGSL_IOCTXENABLE
mdefine_line|#define MGSL_IOCTXENABLE&t;_IO(MGSL_MAGIC_IOC,4)
DECL|macro|MGSL_IOCRXENABLE
mdefine_line|#define MGSL_IOCRXENABLE&t;_IO(MGSL_MAGIC_IOC,5)
DECL|macro|MGSL_IOCTXABORT
mdefine_line|#define MGSL_IOCTXABORT&t;&t;_IO(MGSL_MAGIC_IOC,6)
DECL|macro|MGSL_IOCGSTATS
mdefine_line|#define MGSL_IOCGSTATS&t;&t;_IO(MGSL_MAGIC_IOC,7)
DECL|macro|MGSL_IOCWAITEVENT
mdefine_line|#define MGSL_IOCWAITEVENT&t;_IOWR(MGSL_MAGIC_IOC,8,int)
DECL|macro|MGSL_IOCCLRMODCOUNT
mdefine_line|#define MGSL_IOCCLRMODCOUNT&t;_IO(MGSL_MAGIC_IOC,15)
DECL|macro|MGSL_IOCLOOPTXDONE
mdefine_line|#define MGSL_IOCLOOPTXDONE&t;_IO(MGSL_MAGIC_IOC,9)
macro_line|#endif /* _SYNCLINK_H_ */
eof
