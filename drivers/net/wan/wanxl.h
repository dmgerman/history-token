multiline_comment|/*&n; * wanXL serial card driver for Linux&n; * definitions common to host driver and card firmware&n; *&n; * Copyright (C) 2003 Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License&n; * as published by the Free Software Foundation.&n; */
DECL|macro|RESET_WHILE_LOADING
mdefine_line|#define RESET_WHILE_LOADING 0
multiline_comment|/* you must rebuild the firmware if any of the following is changed */
DECL|macro|DETECT_RAM
mdefine_line|#define DETECT_RAM 0&t;&t;/* needed for &gt; 4MB RAM, 16 MB maximum */
DECL|macro|QUICC_MEMCPY_USES_PLX
mdefine_line|#define QUICC_MEMCPY_USES_PLX 1&t;/* must be used if the host has &gt; 256 MB RAM */
DECL|macro|STATUS_CABLE_V35
mdefine_line|#define STATUS_CABLE_V35&t;2
DECL|macro|STATUS_CABLE_X21
mdefine_line|#define STATUS_CABLE_X21&t;3
DECL|macro|STATUS_CABLE_V24
mdefine_line|#define STATUS_CABLE_V24&t;4
DECL|macro|STATUS_CABLE_EIA530
mdefine_line|#define STATUS_CABLE_EIA530&t;5
DECL|macro|STATUS_CABLE_INVALID
mdefine_line|#define STATUS_CABLE_INVALID&t;6
DECL|macro|STATUS_CABLE_NONE
mdefine_line|#define STATUS_CABLE_NONE&t;7
DECL|macro|STATUS_CABLE_DCE
mdefine_line|#define STATUS_CABLE_DCE&t;0x8000
DECL|macro|STATUS_CABLE_DSR
mdefine_line|#define STATUS_CABLE_DSR&t;0x0010
DECL|macro|STATUS_CABLE_DCD
mdefine_line|#define STATUS_CABLE_DCD&t;0x0008
DECL|macro|STATUS_CABLE_PM_SHIFT
mdefine_line|#define STATUS_CABLE_PM_SHIFT&t;5
DECL|macro|PDM_OFFSET
mdefine_line|#define PDM_OFFSET 0x1000
DECL|macro|TX_BUFFERS
mdefine_line|#define TX_BUFFERS 10&t;&t;/* per port */
DECL|macro|RX_BUFFERS
mdefine_line|#define RX_BUFFERS 30
DECL|macro|RX_QUEUE_LENGTH
mdefine_line|#define RX_QUEUE_LENGTH 40&t;/* card-&gt;host queue length - per card */
DECL|macro|PACKET_EMPTY
mdefine_line|#define PACKET_EMPTY&t;&t;0x00
DECL|macro|PACKET_FULL
mdefine_line|#define PACKET_FULL&t;&t;0x10
DECL|macro|PACKET_SENT
mdefine_line|#define PACKET_SENT&t;&t;0x20 /* TX only */
DECL|macro|PACKET_UNDERRUN
mdefine_line|#define PACKET_UNDERRUN&t;&t;0x30 /* TX only */
DECL|macro|PACKET_PORT_MASK
mdefine_line|#define PACKET_PORT_MASK&t;0x03 /* RX only */
multiline_comment|/* bit numbers in PLX9060 doorbell registers */
DECL|macro|DOORBELL_FROM_CARD_TX_0
mdefine_line|#define DOORBELL_FROM_CARD_TX_0&t;&t;0 /* packet sent by the card */
DECL|macro|DOORBELL_FROM_CARD_TX_1
mdefine_line|#define DOORBELL_FROM_CARD_TX_1&t;&t;1
DECL|macro|DOORBELL_FROM_CARD_TX_2
mdefine_line|#define DOORBELL_FROM_CARD_TX_2&t;&t;2
DECL|macro|DOORBELL_FROM_CARD_TX_3
mdefine_line|#define DOORBELL_FROM_CARD_TX_3&t;&t;3
DECL|macro|DOORBELL_FROM_CARD_RX
mdefine_line|#define DOORBELL_FROM_CARD_RX&t;&t;4
DECL|macro|DOORBELL_FROM_CARD_CABLE_0
mdefine_line|#define DOORBELL_FROM_CARD_CABLE_0&t;5 /* cable/PM/etc. changed */
DECL|macro|DOORBELL_FROM_CARD_CABLE_1
mdefine_line|#define DOORBELL_FROM_CARD_CABLE_1&t;6
DECL|macro|DOORBELL_FROM_CARD_CABLE_2
mdefine_line|#define DOORBELL_FROM_CARD_CABLE_2&t;7
DECL|macro|DOORBELL_FROM_CARD_CABLE_3
mdefine_line|#define DOORBELL_FROM_CARD_CABLE_3&t;8
DECL|macro|DOORBELL_TO_CARD_OPEN_0
mdefine_line|#define DOORBELL_TO_CARD_OPEN_0&t;&t;0
DECL|macro|DOORBELL_TO_CARD_OPEN_1
mdefine_line|#define DOORBELL_TO_CARD_OPEN_1&t;&t;1
DECL|macro|DOORBELL_TO_CARD_OPEN_2
mdefine_line|#define DOORBELL_TO_CARD_OPEN_2&t;&t;2
DECL|macro|DOORBELL_TO_CARD_OPEN_3
mdefine_line|#define DOORBELL_TO_CARD_OPEN_3&t;&t;3
DECL|macro|DOORBELL_TO_CARD_CLOSE_0
mdefine_line|#define DOORBELL_TO_CARD_CLOSE_0&t;4
DECL|macro|DOORBELL_TO_CARD_CLOSE_1
mdefine_line|#define DOORBELL_TO_CARD_CLOSE_1&t;5
DECL|macro|DOORBELL_TO_CARD_CLOSE_2
mdefine_line|#define DOORBELL_TO_CARD_CLOSE_2&t;6
DECL|macro|DOORBELL_TO_CARD_CLOSE_3
mdefine_line|#define DOORBELL_TO_CARD_CLOSE_3&t;7
DECL|macro|DOORBELL_TO_CARD_TX_0
mdefine_line|#define DOORBELL_TO_CARD_TX_0&t;&t;8 /* outbound packet queued */
DECL|macro|DOORBELL_TO_CARD_TX_1
mdefine_line|#define DOORBELL_TO_CARD_TX_1&t;&t;9
DECL|macro|DOORBELL_TO_CARD_TX_2
mdefine_line|#define DOORBELL_TO_CARD_TX_2&t;&t;10
DECL|macro|DOORBELL_TO_CARD_TX_3
mdefine_line|#define DOORBELL_TO_CARD_TX_3&t;&t;11
multiline_comment|/* firmware-only status bits, starting from last DOORBELL_TO_CARD + 1 */
DECL|macro|TASK_SCC_0
mdefine_line|#define TASK_SCC_0&t;&t;&t;12
DECL|macro|TASK_SCC_1
mdefine_line|#define TASK_SCC_1&t;&t;&t;13
DECL|macro|TASK_SCC_2
mdefine_line|#define TASK_SCC_2&t;&t;&t;14
DECL|macro|TASK_SCC_3
mdefine_line|#define TASK_SCC_3&t;&t;&t;15
DECL|macro|ALIGN32
mdefine_line|#define ALIGN32(x) (((x) + 3) &amp; 0xFFFFFFFC)
DECL|macro|BUFFER_LENGTH
mdefine_line|#define BUFFER_LENGTH&t;ALIGN32(HDLC_MAX_MRU + 4) /* 4 bytes for 32-bit CRC */
multiline_comment|/* Address of TX and RX buffers in 68360 address space */
DECL|macro|BUFFERS_ADDR
mdefine_line|#define BUFFERS_ADDR&t;0x4000&t;/* 16 KB */
macro_line|#ifndef __ASSEMBLER__
DECL|macro|PLX_OFFSET
mdefine_line|#define PLX_OFFSET&t;&t;0
macro_line|#else
DECL|macro|PLX_OFFSET
mdefine_line|#define PLX_OFFSET&t;&t;PLX + 0x80
macro_line|#endif
DECL|macro|PLX_MAILBOX_0
mdefine_line|#define PLX_MAILBOX_0&t;&t;(PLX_OFFSET + 0x40)
DECL|macro|PLX_MAILBOX_1
mdefine_line|#define PLX_MAILBOX_1&t;&t;(PLX_OFFSET + 0x44)
DECL|macro|PLX_MAILBOX_2
mdefine_line|#define PLX_MAILBOX_2&t;&t;(PLX_OFFSET + 0x48)
DECL|macro|PLX_MAILBOX_3
mdefine_line|#define PLX_MAILBOX_3&t;&t;(PLX_OFFSET + 0x4C)
DECL|macro|PLX_MAILBOX_4
mdefine_line|#define PLX_MAILBOX_4&t;&t;(PLX_OFFSET + 0x50)
DECL|macro|PLX_MAILBOX_5
mdefine_line|#define PLX_MAILBOX_5&t;&t;(PLX_OFFSET + 0x54)
DECL|macro|PLX_MAILBOX_6
mdefine_line|#define PLX_MAILBOX_6&t;&t;(PLX_OFFSET + 0x58)
DECL|macro|PLX_MAILBOX_7
mdefine_line|#define PLX_MAILBOX_7&t;&t;(PLX_OFFSET + 0x5C)
DECL|macro|PLX_DOORBELL_TO_CARD
mdefine_line|#define PLX_DOORBELL_TO_CARD&t;(PLX_OFFSET + 0x60)
DECL|macro|PLX_DOORBELL_FROM_CARD
mdefine_line|#define PLX_DOORBELL_FROM_CARD&t;(PLX_OFFSET + 0x64)
DECL|macro|PLX_INTERRUPT_CS
mdefine_line|#define PLX_INTERRUPT_CS&t;(PLX_OFFSET + 0x68)
DECL|macro|PLX_CONTROL
mdefine_line|#define PLX_CONTROL&t;&t;(PLX_OFFSET + 0x6C)
macro_line|#ifdef __ASSEMBLER__
DECL|macro|PLX_DMA_0_MODE
mdefine_line|#define PLX_DMA_0_MODE&t;&t;(PLX + 0x100)
DECL|macro|PLX_DMA_0_PCI
mdefine_line|#define PLX_DMA_0_PCI&t;&t;(PLX + 0x104)
DECL|macro|PLX_DMA_0_LOCAL
mdefine_line|#define PLX_DMA_0_LOCAL&t;&t;(PLX + 0x108)
DECL|macro|PLX_DMA_0_LENGTH
mdefine_line|#define PLX_DMA_0_LENGTH&t;(PLX + 0x10C)
DECL|macro|PLX_DMA_0_DESC
mdefine_line|#define PLX_DMA_0_DESC&t;&t;(PLX + 0x110)
DECL|macro|PLX_DMA_1_MODE
mdefine_line|#define PLX_DMA_1_MODE&t;&t;(PLX + 0x114)
DECL|macro|PLX_DMA_1_PCI
mdefine_line|#define PLX_DMA_1_PCI&t;&t;(PLX + 0x118)
DECL|macro|PLX_DMA_1_LOCAL
mdefine_line|#define PLX_DMA_1_LOCAL&t;&t;(PLX + 0x11C)
DECL|macro|PLX_DMA_1_LENGTH
mdefine_line|#define PLX_DMA_1_LENGTH&t;(PLX + 0x120)
DECL|macro|PLX_DMA_1_DESC
mdefine_line|#define PLX_DMA_1_DESC&t;&t;(PLX + 0x124)
DECL|macro|PLX_DMA_CMD_STS
mdefine_line|#define PLX_DMA_CMD_STS&t;&t;(PLX + 0x128)
DECL|macro|PLX_DMA_ARBITR_0
mdefine_line|#define PLX_DMA_ARBITR_0&t;(PLX + 0x12C)
DECL|macro|PLX_DMA_ARBITR_1
mdefine_line|#define PLX_DMA_ARBITR_1&t;(PLX + 0x130)
macro_line|#endif
DECL|macro|DESC_LENGTH
mdefine_line|#define DESC_LENGTH 12
multiline_comment|/* offsets from start of status_t */
multiline_comment|/* card to host */
DECL|macro|STATUS_OPEN
mdefine_line|#define STATUS_OPEN&t;&t;0
DECL|macro|STATUS_CABLE
mdefine_line|#define STATUS_CABLE&t;&t;(STATUS_OPEN + 4)
DECL|macro|STATUS_RX_OVERRUNS
mdefine_line|#define STATUS_RX_OVERRUNS&t;(STATUS_CABLE + 4)
DECL|macro|STATUS_RX_FRAME_ERRORS
mdefine_line|#define STATUS_RX_FRAME_ERRORS&t;(STATUS_RX_OVERRUNS + 4)
multiline_comment|/* host to card */
DECL|macro|STATUS_PARITY
mdefine_line|#define STATUS_PARITY&t;&t;(STATUS_RX_FRAME_ERRORS + 4)
DECL|macro|STATUS_ENCODING
mdefine_line|#define STATUS_ENCODING&t;&t;(STATUS_PARITY + 4)
DECL|macro|STATUS_CLOCKING
mdefine_line|#define STATUS_CLOCKING&t;&t;(STATUS_ENCODING + 4)
DECL|macro|STATUS_TX_DESCS
mdefine_line|#define STATUS_TX_DESCS&t;&t;(STATUS_CLOCKING + 4)
macro_line|#ifndef __ASSEMBLER__
r_typedef
r_struct
(brace
DECL|member|stat
r_volatile
id|u32
id|stat
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
multiline_comment|/* PCI address */
DECL|member|length
r_volatile
id|u32
id|length
suffix:semicolon
DECL|typedef|desc_t
)brace
id|desc_t
suffix:semicolon
r_typedef
r_struct
(brace
singleline_comment|// Card to host
DECL|member|open
r_volatile
id|u32
id|open
suffix:semicolon
DECL|member|cable
r_volatile
id|u32
id|cable
suffix:semicolon
DECL|member|rx_overruns
r_volatile
id|u32
id|rx_overruns
suffix:semicolon
DECL|member|rx_frame_errors
r_volatile
id|u32
id|rx_frame_errors
suffix:semicolon
singleline_comment|// Host to card
DECL|member|parity
id|u32
id|parity
suffix:semicolon
DECL|member|encoding
id|u32
id|encoding
suffix:semicolon
DECL|member|clocking
id|u32
id|clocking
suffix:semicolon
DECL|member|tx_descs
id|desc_t
id|tx_descs
(braket
id|TX_BUFFERS
)braket
suffix:semicolon
DECL|typedef|port_status_t
)brace
id|port_status_t
suffix:semicolon
macro_line|#endif /* __ASSEMBLER__ */
eof
