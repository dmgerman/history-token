multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the Frame relay interface.&n; *&n; * Version:&t;@(#)if_ifrad.h&t;0.20&t;13 Apr 96&n; *&n; * Author:&t;Mike McLagan &lt;mike.mclagan@linux.org&gt;&n; *&n; * Changes:&n; *&t;&t;0.15&t;Mike McLagan&t;Structure packing&n; *&n; *&t;&t;0.20&t;Mike McLagan&t;New flags for S508 buffer handling&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef SDLA_H
DECL|macro|SDLA_H
mdefine_line|#define SDLA_H
multiline_comment|/* adapter type */
DECL|macro|SDLA_TYPES
mdefine_line|#define SDLA_TYPES
DECL|macro|SDLA_S502A
mdefine_line|#define SDLA_S502A&t;&t;&t;5020
DECL|macro|SDLA_S502E
mdefine_line|#define SDLA_S502E&t;&t;&t;5021
DECL|macro|SDLA_S503
mdefine_line|#define SDLA_S503&t;&t;&t;5030
DECL|macro|SDLA_S507
mdefine_line|#define SDLA_S507&t;&t;&t;5070
DECL|macro|SDLA_S508
mdefine_line|#define SDLA_S508&t;&t;&t;5080
DECL|macro|SDLA_S509
mdefine_line|#define SDLA_S509&t;&t;&t;5090
DECL|macro|SDLA_UNKNOWN
mdefine_line|#define SDLA_UNKNOWN&t;&t;&t;-1
multiline_comment|/* port selection flags for the S508 */
DECL|macro|SDLA_S508_PORT_V35
mdefine_line|#define SDLA_S508_PORT_V35&t;&t;0x00
DECL|macro|SDLA_S508_PORT_RS232
mdefine_line|#define SDLA_S508_PORT_RS232&t;&t;0x02
multiline_comment|/* Z80 CPU speeds */
DECL|macro|SDLA_CPU_3M
mdefine_line|#define SDLA_CPU_3M&t;&t;&t;0x00
DECL|macro|SDLA_CPU_5M
mdefine_line|#define SDLA_CPU_5M&t;&t;&t;0x01
DECL|macro|SDLA_CPU_7M
mdefine_line|#define SDLA_CPU_7M&t;&t;&t;0x02
DECL|macro|SDLA_CPU_8M
mdefine_line|#define SDLA_CPU_8M&t;&t;&t;0x03
DECL|macro|SDLA_CPU_10M
mdefine_line|#define SDLA_CPU_10M&t;&t;&t;0x04
DECL|macro|SDLA_CPU_16M
mdefine_line|#define SDLA_CPU_16M&t;&t;&t;0x05
DECL|macro|SDLA_CPU_12M
mdefine_line|#define SDLA_CPU_12M&t;&t;&t;0x06
multiline_comment|/* some private IOCTLs */
DECL|macro|SDLA_IDENTIFY
mdefine_line|#define SDLA_IDENTIFY&t;&t;&t;(FRAD_LAST_IOCTL + 1)
DECL|macro|SDLA_CPUSPEED
mdefine_line|#define SDLA_CPUSPEED&t;&t;&t;(FRAD_LAST_IOCTL + 2)
DECL|macro|SDLA_PROTOCOL
mdefine_line|#define SDLA_PROTOCOL&t;&t;&t;(FRAD_LAST_IOCTL + 3)
DECL|macro|SDLA_CLEARMEM
mdefine_line|#define SDLA_CLEARMEM&t;&t;&t;(FRAD_LAST_IOCTL + 4)
DECL|macro|SDLA_WRITEMEM
mdefine_line|#define SDLA_WRITEMEM&t;&t;&t;(FRAD_LAST_IOCTL + 5)
DECL|macro|SDLA_READMEM
mdefine_line|#define SDLA_READMEM&t;&t;&t;(FRAD_LAST_IOCTL + 6)
DECL|struct|sdla_mem
r_struct
id|sdla_mem
(brace
DECL|member|addr
r_int
id|addr
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SDLA_START
mdefine_line|#define SDLA_START&t;&t;&t;(FRAD_LAST_IOCTL + 7)
DECL|macro|SDLA_STOP
mdefine_line|#define SDLA_STOP&t;&t;&t;(FRAD_LAST_IOCTL + 8)
multiline_comment|/* some offsets in the Z80&squot;s memory space */
DECL|macro|SDLA_NMIADDR
mdefine_line|#define SDLA_NMIADDR&t;&t;&t;0x0000
DECL|macro|SDLA_CONF_ADDR
mdefine_line|#define SDLA_CONF_ADDR&t;&t;&t;0x0010
DECL|macro|SDLA_S502A_NMIADDR
mdefine_line|#define SDLA_S502A_NMIADDR&t;&t;0x0066
DECL|macro|SDLA_CODE_BASEADDR
mdefine_line|#define SDLA_CODE_BASEADDR&t;&t;0x0100
DECL|macro|SDLA_WINDOW_SIZE
mdefine_line|#define SDLA_WINDOW_SIZE&t;&t;0x2000
DECL|macro|SDLA_ADDR_MASK
mdefine_line|#define SDLA_ADDR_MASK&t;&t;&t;0x1FFF
multiline_comment|/* largest handleable block of data */
DECL|macro|SDLA_MAX_DATA
mdefine_line|#define SDLA_MAX_DATA&t;&t;&t;4080
DECL|macro|SDLA_MAX_MTU
mdefine_line|#define SDLA_MAX_MTU&t;&t;&t;4072&t;/* MAX_DATA - sizeof(fradhdr) */
DECL|macro|SDLA_MAX_DLCI
mdefine_line|#define SDLA_MAX_DLCI&t;&t;&t;24
multiline_comment|/* this should be the same as frad_conf */
DECL|struct|sdla_conf
r_struct
id|sdla_conf
(brace
DECL|member|station
r_int
id|station
suffix:semicolon
DECL|member|config
r_int
id|config
suffix:semicolon
DECL|member|kbaud
r_int
id|kbaud
suffix:semicolon
DECL|member|clocking
r_int
id|clocking
suffix:semicolon
DECL|member|max_frm
r_int
id|max_frm
suffix:semicolon
DECL|member|T391
r_int
id|T391
suffix:semicolon
DECL|member|T392
r_int
id|T392
suffix:semicolon
DECL|member|N391
r_int
id|N391
suffix:semicolon
DECL|member|N392
r_int
id|N392
suffix:semicolon
DECL|member|N393
r_int
id|N393
suffix:semicolon
DECL|member|CIR_fwd
r_int
id|CIR_fwd
suffix:semicolon
DECL|member|Bc_fwd
r_int
id|Bc_fwd
suffix:semicolon
DECL|member|Be_fwd
r_int
id|Be_fwd
suffix:semicolon
DECL|member|CIR_bwd
r_int
id|CIR_bwd
suffix:semicolon
DECL|member|Bc_bwd
r_int
id|Bc_bwd
suffix:semicolon
DECL|member|Be_bwd
r_int
id|Be_bwd
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* this should be the same as dlci_conf */
DECL|struct|sdla_dlci_conf
r_struct
id|sdla_dlci_conf
(brace
DECL|member|config
r_int
id|config
suffix:semicolon
DECL|member|CIR_fwd
r_int
id|CIR_fwd
suffix:semicolon
DECL|member|Bc_fwd
r_int
id|Bc_fwd
suffix:semicolon
DECL|member|Be_fwd
r_int
id|Be_fwd
suffix:semicolon
DECL|member|CIR_bwd
r_int
id|CIR_bwd
suffix:semicolon
DECL|member|Bc_bwd
r_int
id|Bc_bwd
suffix:semicolon
DECL|member|Be_bwd
r_int
id|Be_bwd
suffix:semicolon
DECL|member|Tc_fwd
r_int
id|Tc_fwd
suffix:semicolon
DECL|member|Tc_bwd
r_int
id|Tc_bwd
suffix:semicolon
DECL|member|Tf_max
r_int
id|Tf_max
suffix:semicolon
DECL|member|Tb_max
r_int
id|Tb_max
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifndef __KERNEL__
r_void
id|sdla
c_func
(paren
r_void
op_star
id|cfg_info
comma
r_char
op_star
id|dev
comma
r_struct
id|frad_conf
op_star
id|conf
comma
r_int
id|quiet
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* important Z80 window addresses */
DECL|macro|SDLA_CONTROL_WND
mdefine_line|#define SDLA_CONTROL_WND&t;&t;0xE000
DECL|macro|SDLA_502_CMD_BUF
mdefine_line|#define SDLA_502_CMD_BUF&t;&t;0xEF60
DECL|macro|SDLA_502_RCV_BUF
mdefine_line|#define SDLA_502_RCV_BUF&t;&t;0xA900
DECL|macro|SDLA_502_TXN_AVAIL
mdefine_line|#define&t;SDLA_502_TXN_AVAIL&t;&t;0xFFF1
DECL|macro|SDLA_502_RCV_AVAIL
mdefine_line|#define SDLA_502_RCV_AVAIL&t;&t;0xFFF2
DECL|macro|SDLA_502_EVENT_FLAGS
mdefine_line|#define SDLA_502_EVENT_FLAGS&t;&t;0xFFF3
DECL|macro|SDLA_502_MDM_STATUS
mdefine_line|#define SDLA_502_MDM_STATUS&t;&t;0xFFF4
DECL|macro|SDLA_502_IRQ_INTERFACE
mdefine_line|#define SDLA_502_IRQ_INTERFACE&t;&t;0xFFFD
DECL|macro|SDLA_502_IRQ_PERMISSION
mdefine_line|#define SDLA_502_IRQ_PERMISSION&t;&t;0xFFFE
DECL|macro|SDLA_502_DATA_OFS
mdefine_line|#define SDLA_502_DATA_OFS&t;&t;0x0010
DECL|macro|SDLA_508_CMD_BUF
mdefine_line|#define SDLA_508_CMD_BUF&t;&t;0xE000
DECL|macro|SDLA_508_TXBUF_INFO
mdefine_line|#define SDLA_508_TXBUF_INFO&t;&t;0xF100
DECL|macro|SDLA_508_RXBUF_INFO
mdefine_line|#define SDLA_508_RXBUF_INFO&t;&t;0xF120
DECL|macro|SDLA_508_EVENT_FLAGS
mdefine_line|#define SDLA_508_EVENT_FLAGS&t;&t;0xF003
DECL|macro|SDLA_508_MDM_STATUS
mdefine_line|#define SDLA_508_MDM_STATUS&t;&t;0xF004
DECL|macro|SDLA_508_IRQ_INTERFACE
mdefine_line|#define SDLA_508_IRQ_INTERFACE&t;&t;0xF010
DECL|macro|SDLA_508_IRQ_PERMISSION
mdefine_line|#define SDLA_508_IRQ_PERMISSION&t;&t;0xF011
DECL|macro|SDLA_508_TSE_OFFSET
mdefine_line|#define SDLA_508_TSE_OFFSET&t;&t;0xF012
multiline_comment|/* Event flags */
DECL|macro|SDLA_EVENT_STATUS
mdefine_line|#define SDLA_EVENT_STATUS&t;&t;0x01
DECL|macro|SDLA_EVENT_DLCI_STATUS
mdefine_line|#define SDLA_EVENT_DLCI_STATUS&t;&t;0x02
DECL|macro|SDLA_EVENT_BAD_DLCI
mdefine_line|#define SDLA_EVENT_BAD_DLCI&t;&t;0x04
DECL|macro|SDLA_EVENT_LINK_DOWN
mdefine_line|#define SDLA_EVENT_LINK_DOWN&t;&t;0x40
multiline_comment|/* IRQ Trigger flags */
DECL|macro|SDLA_INTR_RX
mdefine_line|#define SDLA_INTR_RX&t;&t;&t;0x01
DECL|macro|SDLA_INTR_TX
mdefine_line|#define SDLA_INTR_TX&t;&t;&t;0x02
DECL|macro|SDLA_INTR_MODEM
mdefine_line|#define SDLA_INTR_MODEM&t;&t;&t;0x04
DECL|macro|SDLA_INTR_COMPLETE
mdefine_line|#define SDLA_INTR_COMPLETE&t;&t;0x08
DECL|macro|SDLA_INTR_STATUS
mdefine_line|#define SDLA_INTR_STATUS&t;&t;0x10
DECL|macro|SDLA_INTR_TIMER
mdefine_line|#define SDLA_INTR_TIMER&t;&t;&t;0x20
multiline_comment|/* DLCI status bits */
DECL|macro|SDLA_DLCI_DELETED
mdefine_line|#define SDLA_DLCI_DELETED&t;&t;0x01
DECL|macro|SDLA_DLCI_ACTIVE
mdefine_line|#define SDLA_DLCI_ACTIVE&t;&t;0x02
DECL|macro|SDLA_DLCI_WAITING
mdefine_line|#define SDLA_DLCI_WAITING&t;&t;0x04
DECL|macro|SDLA_DLCI_NEW
mdefine_line|#define SDLA_DLCI_NEW&t;&t;&t;0x08
DECL|macro|SDLA_DLCI_INCLUDED
mdefine_line|#define SDLA_DLCI_INCLUDED&t;&t;0x40
multiline_comment|/* valid command codes */
DECL|macro|SDLA_INFORMATION_WRITE
mdefine_line|#define&t;SDLA_INFORMATION_WRITE&t;&t;0x01
DECL|macro|SDLA_INFORMATION_READ
mdefine_line|#define&t;SDLA_INFORMATION_READ&t;&t;0x02
DECL|macro|SDLA_ISSUE_IN_CHANNEL_SIGNAL
mdefine_line|#define SDLA_ISSUE_IN_CHANNEL_SIGNAL&t;0x03
DECL|macro|SDLA_SET_DLCI_CONFIGURATION
mdefine_line|#define&t;SDLA_SET_DLCI_CONFIGURATION&t;0x10
DECL|macro|SDLA_READ_DLCI_CONFIGURATION
mdefine_line|#define&t;SDLA_READ_DLCI_CONFIGURATION&t;0x11
DECL|macro|SDLA_DISABLE_COMMUNICATIONS
mdefine_line|#define&t;SDLA_DISABLE_COMMUNICATIONS&t;0x12
DECL|macro|SDLA_ENABLE_COMMUNICATIONS
mdefine_line|#define&t;SDLA_ENABLE_COMMUNICATIONS&t;0x13
DECL|macro|SDLA_READ_DLC_STATUS
mdefine_line|#define&t;SDLA_READ_DLC_STATUS&t;&t;0x14
DECL|macro|SDLA_READ_DLC_STATISTICS
mdefine_line|#define&t;SDLA_READ_DLC_STATISTICS&t;0x15
DECL|macro|SDLA_FLUSH_DLC_STATISTICS
mdefine_line|#define&t;SDLA_FLUSH_DLC_STATISTICS&t;0x16
DECL|macro|SDLA_LIST_ACTIVE_DLCI
mdefine_line|#define&t;SDLA_LIST_ACTIVE_DLCI&t;&t;0x17
DECL|macro|SDLA_FLUSH_INFORMATION_BUFFERS
mdefine_line|#define&t;SDLA_FLUSH_INFORMATION_BUFFERS&t;0x18
DECL|macro|SDLA_ADD_DLCI
mdefine_line|#define&t;SDLA_ADD_DLCI&t;&t;&t;0x20
DECL|macro|SDLA_DELETE_DLCI
mdefine_line|#define&t;SDLA_DELETE_DLCI&t;&t;0x21
DECL|macro|SDLA_ACTIVATE_DLCI
mdefine_line|#define&t;SDLA_ACTIVATE_DLCI&t;&t;0x22
DECL|macro|SDLA_DEACTIVATE_DLCI
mdefine_line|#define&t;SDLA_DEACTIVATE_DLCI&t;&t;0x23
DECL|macro|SDLA_READ_MODEM_STATUS
mdefine_line|#define&t;SDLA_READ_MODEM_STATUS&t;&t;0x30
DECL|macro|SDLA_SET_MODEM_STATUS
mdefine_line|#define&t;SDLA_SET_MODEM_STATUS&t;&t;0x31
DECL|macro|SDLA_READ_COMMS_ERR_STATS
mdefine_line|#define&t;SDLA_READ_COMMS_ERR_STATS&t;0x32
DECL|macro|SDLA_FLUSH_COMMS_ERR_STATS
mdefine_line|#define SDLA_FLUSH_COMMS_ERR_STATS&t;0x33
DECL|macro|SDLA_READ_CODE_VERSION
mdefine_line|#define&t;SDLA_READ_CODE_VERSION&t;&t;0x40
DECL|macro|SDLA_SET_IRQ_TRIGGER
mdefine_line|#define SDLA_SET_IRQ_TRIGGER&t;&t;0x50
DECL|macro|SDLA_GET_IRQ_TRIGGER
mdefine_line|#define SDLA_GET_IRQ_TRIGGER&t;&t;0x51
multiline_comment|/* In channel signal types */
DECL|macro|SDLA_ICS_LINK_VERIFY
mdefine_line|#define SDLA_ICS_LINK_VERIFY&t;&t;0x02
DECL|macro|SDLA_ICS_STATUS_ENQ
mdefine_line|#define SDLA_ICS_STATUS_ENQ&t;&t;0x03
multiline_comment|/* modem status flags */
DECL|macro|SDLA_MODEM_DTR_HIGH
mdefine_line|#define SDLA_MODEM_DTR_HIGH&t;&t;0x01
DECL|macro|SDLA_MODEM_RTS_HIGH
mdefine_line|#define SDLA_MODEM_RTS_HIGH&t;&t;0x02
DECL|macro|SDLA_MODEM_DCD_HIGH
mdefine_line|#define SDLA_MODEM_DCD_HIGH&t;&t;0x08
DECL|macro|SDLA_MODEM_CTS_HIGH
mdefine_line|#define SDLA_MODEM_CTS_HIGH&t;&t;0x20
multiline_comment|/* used for RET_MODEM interpretation */
DECL|macro|SDLA_MODEM_DCD_LOW
mdefine_line|#define SDLA_MODEM_DCD_LOW&t;&t;0x01
DECL|macro|SDLA_MODEM_CTS_LOW
mdefine_line|#define SDLA_MODEM_CTS_LOW&t;&t;0x02
multiline_comment|/* return codes */
DECL|macro|SDLA_RET_OK
mdefine_line|#define SDLA_RET_OK&t;&t;&t;0x00
DECL|macro|SDLA_RET_COMMUNICATIONS
mdefine_line|#define SDLA_RET_COMMUNICATIONS&t;&t;0x01
DECL|macro|SDLA_RET_CHANNEL_INACTIVE
mdefine_line|#define SDLA_RET_CHANNEL_INACTIVE&t;0x02
DECL|macro|SDLA_RET_DLCI_INACTIVE
mdefine_line|#define SDLA_RET_DLCI_INACTIVE&t;&t;0x03
DECL|macro|SDLA_RET_DLCI_CONFIG
mdefine_line|#define SDLA_RET_DLCI_CONFIG&t;&t;0x04
DECL|macro|SDLA_RET_BUF_TOO_BIG
mdefine_line|#define SDLA_RET_BUF_TOO_BIG&t;&t;0x05
DECL|macro|SDLA_RET_NO_DATA
mdefine_line|#define SDLA_RET_NO_DATA&t;&t;0x05
DECL|macro|SDLA_RET_BUF_OVERSIZE
mdefine_line|#define SDLA_RET_BUF_OVERSIZE&t;&t;0x06
DECL|macro|SDLA_RET_CIR_OVERFLOW
mdefine_line|#define SDLA_RET_CIR_OVERFLOW&t;&t;0x07
DECL|macro|SDLA_RET_NO_BUFS
mdefine_line|#define SDLA_RET_NO_BUFS&t;&t;0x08
DECL|macro|SDLA_RET_TIMEOUT
mdefine_line|#define SDLA_RET_TIMEOUT&t;&t;0x0A
DECL|macro|SDLA_RET_MODEM
mdefine_line|#define SDLA_RET_MODEM&t;&t;&t;0x10
DECL|macro|SDLA_RET_CHANNEL_OFF
mdefine_line|#define SDLA_RET_CHANNEL_OFF&t;&t;0x11
DECL|macro|SDLA_RET_CHANNEL_ON
mdefine_line|#define SDLA_RET_CHANNEL_ON&t;&t;0x12
DECL|macro|SDLA_RET_DLCI_STATUS
mdefine_line|#define SDLA_RET_DLCI_STATUS&t;&t;0x13
DECL|macro|SDLA_RET_DLCI_UNKNOWN
mdefine_line|#define SDLA_RET_DLCI_UNKNOWN       &t;0x14
DECL|macro|SDLA_RET_COMMAND_INVALID
mdefine_line|#define SDLA_RET_COMMAND_INVALID    &t;0x1F
multiline_comment|/* Configuration flags */
DECL|macro|SDLA_DIRECT_RECV
mdefine_line|#define SDLA_DIRECT_RECV&t;&t;0x0080
DECL|macro|SDLA_TX_NO_EXCEPT
mdefine_line|#define SDLA_TX_NO_EXCEPT&t;&t;0x0020
DECL|macro|SDLA_NO_ICF_MSGS
mdefine_line|#define SDLA_NO_ICF_MSGS&t;&t;0x1000
DECL|macro|SDLA_TX50_RX50
mdefine_line|#define SDLA_TX50_RX50&t;&t;&t;0x0000
DECL|macro|SDLA_TX70_RX30
mdefine_line|#define SDLA_TX70_RX30&t;&t;&t;0x2000
DECL|macro|SDLA_TX30_RX70
mdefine_line|#define SDLA_TX30_RX70&t;&t;&t;0x4000
multiline_comment|/* IRQ selection flags */
DECL|macro|SDLA_IRQ_RECEIVE
mdefine_line|#define SDLA_IRQ_RECEIVE&t;&t;0x01
DECL|macro|SDLA_IRQ_TRANSMIT
mdefine_line|#define SDLA_IRQ_TRANSMIT&t;&t;0x02
DECL|macro|SDLA_IRQ_MODEM_STAT
mdefine_line|#define SDLA_IRQ_MODEM_STAT&t;&t;0x04
DECL|macro|SDLA_IRQ_COMMAND
mdefine_line|#define SDLA_IRQ_COMMAND&t;&t;0x08
DECL|macro|SDLA_IRQ_CHANNEL
mdefine_line|#define SDLA_IRQ_CHANNEL&t;&t;0x10
DECL|macro|SDLA_IRQ_TIMER
mdefine_line|#define SDLA_IRQ_TIMER&t;&t;&t;0x20
multiline_comment|/* definitions for PC memory mapping */
DECL|macro|SDLA_8K_WINDOW
mdefine_line|#define SDLA_8K_WINDOW&t;&t;&t;0x01
DECL|macro|SDLA_S502_SEG_A
mdefine_line|#define SDLA_S502_SEG_A&t;&t;&t;0x10
DECL|macro|SDLA_S502_SEG_C
mdefine_line|#define SDLA_S502_SEG_C&t;&t;&t;0x20
DECL|macro|SDLA_S502_SEG_D
mdefine_line|#define SDLA_S502_SEG_D&t;&t;&t;0x00
DECL|macro|SDLA_S502_SEG_E
mdefine_line|#define SDLA_S502_SEG_E&t;&t;&t;0x30
DECL|macro|SDLA_S507_SEG_A
mdefine_line|#define SDLA_S507_SEG_A&t;&t;&t;0x00
DECL|macro|SDLA_S507_SEG_B
mdefine_line|#define SDLA_S507_SEG_B&t;&t;&t;0x40
DECL|macro|SDLA_S507_SEG_C
mdefine_line|#define SDLA_S507_SEG_C&t;&t;&t;0x80
DECL|macro|SDLA_S507_SEG_E
mdefine_line|#define SDLA_S507_SEG_E&t;&t;&t;0xC0
DECL|macro|SDLA_S508_SEG_A
mdefine_line|#define SDLA_S508_SEG_A&t;&t;&t;0x00
DECL|macro|SDLA_S508_SEG_C
mdefine_line|#define SDLA_S508_SEG_C&t;&t;&t;0x10
DECL|macro|SDLA_S508_SEG_D
mdefine_line|#define SDLA_S508_SEG_D&t;&t;&t;0x08
DECL|macro|SDLA_S508_SEG_E
mdefine_line|#define SDLA_S508_SEG_E&t;&t;&t;0x18
multiline_comment|/* SDLA adapter port constants */
DECL|macro|SDLA_IO_EXTENTS
mdefine_line|#define SDLA_IO_EXTENTS&t;&t;&t;0x04
DECL|macro|SDLA_REG_CONTROL
mdefine_line|#define SDLA_REG_CONTROL&t;&t;0x00
DECL|macro|SDLA_REG_PC_WINDOW
mdefine_line|#define SDLA_REG_PC_WINDOW&t;&t;0x01&t;/* offset for PC window select latch */
DECL|macro|SDLA_REG_Z80_WINDOW
mdefine_line|#define SDLA_REG_Z80_WINDOW &t;&t;0x02&t;/* offset for Z80 window select latch */
DECL|macro|SDLA_REG_Z80_CONTROL
mdefine_line|#define SDLA_REG_Z80_CONTROL&t;&t;0x03&t;/* offset for Z80 control latch */
DECL|macro|SDLA_S502_STS
mdefine_line|#define SDLA_S502_STS&t;&t;&t;0x00&t;/* status reg for 502, 502E, 507 */
DECL|macro|SDLA_S508_GNRL
mdefine_line|#define SDLA_S508_GNRL&t;&t;&t;0x00&t;/* general purp. reg for 508 */
DECL|macro|SDLA_S508_STS
mdefine_line|#define SDLA_S508_STS&t;&t;&t;0x01&t;/* status reg for 508 */
DECL|macro|SDLA_S508_IDR
mdefine_line|#define SDLA_S508_IDR&t;&t;&t;0x02&t;/* ID reg for 508 */
multiline_comment|/* control register flags */
DECL|macro|SDLA_S502A_START
mdefine_line|#define SDLA_S502A_START&t;&t;0x00&t;/* start the CPU */
DECL|macro|SDLA_S502A_INTREQ
mdefine_line|#define SDLA_S502A_INTREQ&t;&t;0x02
DECL|macro|SDLA_S502A_INTEN
mdefine_line|#define SDLA_S502A_INTEN&t;&t;0x04
DECL|macro|SDLA_S502A_HALT
mdefine_line|#define SDLA_S502A_HALT&t;&t;&t;0x08&t;/* halt the CPU */&t;
DECL|macro|SDLA_S502A_NMI
mdefine_line|#define SDLA_S502A_NMI&t;&t;&t;0x10&t;/* issue an NMI to the CPU */
DECL|macro|SDLA_S502E_CPUEN
mdefine_line|#define SDLA_S502E_CPUEN&t;&t;0x01
DECL|macro|SDLA_S502E_ENABLE
mdefine_line|#define SDLA_S502E_ENABLE&t;&t;0x02
DECL|macro|SDLA_S502E_INTACK
mdefine_line|#define SDLA_S502E_INTACK&t;&t;0x04
DECL|macro|SDLA_S507_ENABLE
mdefine_line|#define SDLA_S507_ENABLE&t;&t;0x01
DECL|macro|SDLA_S507_IRQ3
mdefine_line|#define SDLA_S507_IRQ3&t;&t;&t;0x00
DECL|macro|SDLA_S507_IRQ4
mdefine_line|#define SDLA_S507_IRQ4&t;&t;&t;0x20
DECL|macro|SDLA_S507_IRQ5
mdefine_line|#define SDLA_S507_IRQ5&t;&t;&t;0x40
DECL|macro|SDLA_S507_IRQ7
mdefine_line|#define SDLA_S507_IRQ7&t;&t;&t;0x60
DECL|macro|SDLA_S507_IRQ10
mdefine_line|#define SDLA_S507_IRQ10&t;&t;&t;0x80
DECL|macro|SDLA_S507_IRQ11
mdefine_line|#define SDLA_S507_IRQ11&t;&t;&t;0xA0
DECL|macro|SDLA_S507_IRQ12
mdefine_line|#define SDLA_S507_IRQ12&t;&t;&t;0xC0
DECL|macro|SDLA_S507_IRQ15
mdefine_line|#define SDLA_S507_IRQ15&t;&t;&t;0xE0
DECL|macro|SDLA_HALT
mdefine_line|#define SDLA_HALT&t;&t;&t;0x00
DECL|macro|SDLA_CPUEN
mdefine_line|#define SDLA_CPUEN&t;&t;&t;0x02
DECL|macro|SDLA_MEMEN
mdefine_line|#define SDLA_MEMEN&t;&t;&t;0x04
DECL|macro|SDLA_S507_EPROMWR
mdefine_line|#define SDLA_S507_EPROMWR&t;&t;0x08
DECL|macro|SDLA_S507_EPROMCLK
mdefine_line|#define SDLA_S507_EPROMCLK&t;&t;0x10
DECL|macro|SDLA_S508_INTRQ
mdefine_line|#define SDLA_S508_INTRQ&t;&t;&t;0x08
DECL|macro|SDLA_S508_INTEN
mdefine_line|#define SDLA_S508_INTEN&t;&t;&t;0x10
DECL|struct|sdla_cmd
r_struct
id|sdla_cmd
(brace
DECL|member|opp_flag
r_char
id|opp_flag
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|cmd
r_char
id|cmd
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|length
r_int
id|length
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|retval
r_char
id|retval
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|dlci
r_int
id|dlci
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|flags
r_char
id|flags
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|rxlost_int
r_int
id|rxlost_int
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|rxlost_app
r_int
id|rxlost_app
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|reserve
r_char
id|reserve
(braket
l_int|2
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
id|SDLA_MAX_DATA
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* transfer data buffer */
)brace
suffix:semicolon
DECL|struct|intr_info
r_struct
id|intr_info
(brace
DECL|member|flags
r_char
id|flags
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|txlen
r_int
id|txlen
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|irq
r_char
id|irq
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|flags2
r_char
id|flags2
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* found in the 508&squot;s control window at RXBUF_INFO */
DECL|struct|buf_info
r_struct
id|buf_info
(brace
DECL|member|rse_num
r_int
r_int
id|rse_num
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|rse_base
r_int
r_int
id|rse_base
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|rse_next
r_int
r_int
id|rse_next
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|buf_base
r_int
r_int
id|buf_base
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|buf_top
r_int
r_int
id|buf_top
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* structure pointed to by rse_base in RXBUF_INFO struct */
DECL|struct|buf_entry
r_struct
id|buf_entry
(brace
DECL|member|opp_flag
r_char
id|opp_flag
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|length
r_int
id|length
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|dlci
r_int
id|dlci
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|flags
r_char
id|flags
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|timestamp
r_int
id|timestamp
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
(braket
l_int|2
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|buf_addr
r_int
id|buf_addr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
