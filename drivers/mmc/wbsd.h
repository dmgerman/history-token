multiline_comment|/*&n; *  linux/drivers/mmc/wbsd.h - Winbond W83L51xD SD/MMC driver&n; *&n; *  Copyright (C) 2004-2005 Pierre Ossman, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|variable|config_ports
r_const
r_int
id|config_ports
(braket
)braket
op_assign
(brace
l_int|0x2E
comma
l_int|0x4E
)brace
suffix:semicolon
DECL|variable|unlock_codes
r_const
r_int
id|unlock_codes
(braket
)braket
op_assign
(brace
l_int|0x83
comma
l_int|0x87
)brace
suffix:semicolon
DECL|variable|valid_ids
r_const
r_int
id|valid_ids
(braket
)braket
op_assign
(brace
l_int|0x7112
comma
)brace
suffix:semicolon
DECL|macro|LOCK_CODE
mdefine_line|#define LOCK_CODE&t;&t;0xAA
DECL|macro|WBSD_CONF_SWRST
mdefine_line|#define WBSD_CONF_SWRST&t;&t;0x02
DECL|macro|WBSD_CONF_DEVICE
mdefine_line|#define WBSD_CONF_DEVICE&t;0x07
DECL|macro|WBSD_CONF_ID_HI
mdefine_line|#define WBSD_CONF_ID_HI&t;&t;0x20
DECL|macro|WBSD_CONF_ID_LO
mdefine_line|#define WBSD_CONF_ID_LO&t;&t;0x21
DECL|macro|WBSD_CONF_POWER
mdefine_line|#define WBSD_CONF_POWER&t;&t;0x22
DECL|macro|WBSD_CONF_PME
mdefine_line|#define WBSD_CONF_PME&t;&t;0x23
DECL|macro|WBSD_CONF_PMES
mdefine_line|#define WBSD_CONF_PMES&t;&t;0x24
DECL|macro|WBSD_CONF_ENABLE
mdefine_line|#define WBSD_CONF_ENABLE&t;0x30
DECL|macro|WBSD_CONF_PORT_HI
mdefine_line|#define WBSD_CONF_PORT_HI&t;0x60
DECL|macro|WBSD_CONF_PORT_LO
mdefine_line|#define WBSD_CONF_PORT_LO&t;0x61
DECL|macro|WBSD_CONF_IRQ
mdefine_line|#define WBSD_CONF_IRQ&t;&t;0x70
DECL|macro|WBSD_CONF_DRQ
mdefine_line|#define WBSD_CONF_DRQ&t;&t;0x74
DECL|macro|WBSD_CONF_PINS
mdefine_line|#define WBSD_CONF_PINS&t;&t;0xF0
DECL|macro|DEVICE_SD
mdefine_line|#define DEVICE_SD&t;&t;0x03
DECL|macro|WBSD_CMDR
mdefine_line|#define WBSD_CMDR&t;&t;0x00
DECL|macro|WBSD_DFR
mdefine_line|#define WBSD_DFR&t;&t;0x01
DECL|macro|WBSD_EIR
mdefine_line|#define WBSD_EIR&t;&t;0x02
DECL|macro|WBSD_ISR
mdefine_line|#define WBSD_ISR&t;&t;0x03
DECL|macro|WBSD_FSR
mdefine_line|#define WBSD_FSR&t;&t;0x04
DECL|macro|WBSD_IDXR
mdefine_line|#define WBSD_IDXR&t;&t;0x05
DECL|macro|WBSD_DATAR
mdefine_line|#define WBSD_DATAR&t;&t;0x06
DECL|macro|WBSD_CSR
mdefine_line|#define WBSD_CSR&t;&t;0x07
DECL|macro|WBSD_EINT_CARD
mdefine_line|#define WBSD_EINT_CARD&t;&t;0x40
DECL|macro|WBSD_EINT_FIFO_THRE
mdefine_line|#define WBSD_EINT_FIFO_THRE&t;0x20
DECL|macro|WBSD_EINT_CCRC
mdefine_line|#define WBSD_EINT_CCRC&t;&t;0x10
DECL|macro|WBSD_EINT_TIMEOUT
mdefine_line|#define WBSD_EINT_TIMEOUT&t;0x08
DECL|macro|WBSD_EINT_PROGEND
mdefine_line|#define WBSD_EINT_PROGEND&t;0x04
DECL|macro|WBSD_EINT_CRC
mdefine_line|#define WBSD_EINT_CRC&t;&t;0x02
DECL|macro|WBSD_EINT_TC
mdefine_line|#define WBSD_EINT_TC&t;&t;0x01
DECL|macro|WBSD_INT_PENDING
mdefine_line|#define WBSD_INT_PENDING&t;0x80
DECL|macro|WBSD_INT_CARD
mdefine_line|#define WBSD_INT_CARD&t;&t;0x40
DECL|macro|WBSD_INT_FIFO_THRE
mdefine_line|#define WBSD_INT_FIFO_THRE&t;0x20
DECL|macro|WBSD_INT_CRC
mdefine_line|#define WBSD_INT_CRC&t;&t;0x10
DECL|macro|WBSD_INT_TIMEOUT
mdefine_line|#define WBSD_INT_TIMEOUT&t;0x08
DECL|macro|WBSD_INT_PROGEND
mdefine_line|#define WBSD_INT_PROGEND&t;0x04
DECL|macro|WBSD_INT_BUSYEND
mdefine_line|#define WBSD_INT_BUSYEND&t;0x02
DECL|macro|WBSD_INT_TC
mdefine_line|#define WBSD_INT_TC&t;&t;0x01
DECL|macro|WBSD_FIFO_EMPTY
mdefine_line|#define WBSD_FIFO_EMPTY&t;&t;0x80
DECL|macro|WBSD_FIFO_FULL
mdefine_line|#define WBSD_FIFO_FULL&t;&t;0x40
DECL|macro|WBSD_FIFO_EMTHRE
mdefine_line|#define WBSD_FIFO_EMTHRE&t;0x20
DECL|macro|WBSD_FIFO_FUTHRE
mdefine_line|#define WBSD_FIFO_FUTHRE&t;0x10
DECL|macro|WBSD_FIFO_SZMASK
mdefine_line|#define WBSD_FIFO_SZMASK&t;0x0F
DECL|macro|WBSD_MSLED
mdefine_line|#define WBSD_MSLED&t;&t;0x20
DECL|macro|WBSD_POWER_N
mdefine_line|#define WBSD_POWER_N&t;&t;0x10
DECL|macro|WBSD_WRPT
mdefine_line|#define WBSD_WRPT&t;&t;0x04
DECL|macro|WBSD_CARDPRESENT
mdefine_line|#define WBSD_CARDPRESENT&t;0x01
DECL|macro|WBSD_IDX_CLK
mdefine_line|#define WBSD_IDX_CLK&t;&t;0x01
DECL|macro|WBSD_IDX_PBSMSB
mdefine_line|#define WBSD_IDX_PBSMSB&t;&t;0x02
DECL|macro|WBSD_IDX_TAAC
mdefine_line|#define WBSD_IDX_TAAC&t;&t;0x03
DECL|macro|WBSD_IDX_NSAC
mdefine_line|#define WBSD_IDX_NSAC&t;&t;0x04
DECL|macro|WBSD_IDX_PBSLSB
mdefine_line|#define WBSD_IDX_PBSLSB&t;&t;0x05
DECL|macro|WBSD_IDX_SETUP
mdefine_line|#define WBSD_IDX_SETUP&t;&t;0x06
DECL|macro|WBSD_IDX_DMA
mdefine_line|#define WBSD_IDX_DMA&t;&t;0x07
DECL|macro|WBSD_IDX_FIFOEN
mdefine_line|#define WBSD_IDX_FIFOEN&t;&t;0x08
DECL|macro|WBSD_IDX_STATUS
mdefine_line|#define WBSD_IDX_STATUS&t;&t;0x10
DECL|macro|WBSD_IDX_RSPLEN
mdefine_line|#define WBSD_IDX_RSPLEN&t;&t;0x1E
DECL|macro|WBSD_IDX_RESP0
mdefine_line|#define WBSD_IDX_RESP0&t;&t;0x1F
DECL|macro|WBSD_IDX_RESP1
mdefine_line|#define WBSD_IDX_RESP1&t;&t;0x20
DECL|macro|WBSD_IDX_RESP2
mdefine_line|#define WBSD_IDX_RESP2&t;&t;0x21
DECL|macro|WBSD_IDX_RESP3
mdefine_line|#define WBSD_IDX_RESP3&t;&t;0x22
DECL|macro|WBSD_IDX_RESP4
mdefine_line|#define WBSD_IDX_RESP4&t;&t;0x23
DECL|macro|WBSD_IDX_RESP5
mdefine_line|#define WBSD_IDX_RESP5&t;&t;0x24
DECL|macro|WBSD_IDX_RESP6
mdefine_line|#define WBSD_IDX_RESP6&t;&t;0x25
DECL|macro|WBSD_IDX_RESP7
mdefine_line|#define WBSD_IDX_RESP7&t;&t;0x26
DECL|macro|WBSD_IDX_RESP8
mdefine_line|#define WBSD_IDX_RESP8&t;&t;0x27
DECL|macro|WBSD_IDX_RESP9
mdefine_line|#define WBSD_IDX_RESP9&t;&t;0x28
DECL|macro|WBSD_IDX_RESP10
mdefine_line|#define WBSD_IDX_RESP10&t;&t;0x29
DECL|macro|WBSD_IDX_RESP11
mdefine_line|#define WBSD_IDX_RESP11&t;&t;0x2A
DECL|macro|WBSD_IDX_RESP12
mdefine_line|#define WBSD_IDX_RESP12&t;&t;0x2B
DECL|macro|WBSD_IDX_RESP13
mdefine_line|#define WBSD_IDX_RESP13&t;&t;0x2C
DECL|macro|WBSD_IDX_RESP14
mdefine_line|#define WBSD_IDX_RESP14&t;&t;0x2D
DECL|macro|WBSD_IDX_RESP15
mdefine_line|#define WBSD_IDX_RESP15&t;&t;0x2E
DECL|macro|WBSD_IDX_RESP16
mdefine_line|#define WBSD_IDX_RESP16&t;&t;0x2F
DECL|macro|WBSD_IDX_CRCSTATUS
mdefine_line|#define WBSD_IDX_CRCSTATUS&t;0x30
DECL|macro|WBSD_IDX_ISR
mdefine_line|#define WBSD_IDX_ISR&t;&t;0x3F
DECL|macro|WBSD_CLK_375K
mdefine_line|#define WBSD_CLK_375K&t;&t;0x00
DECL|macro|WBSD_CLK_12M
mdefine_line|#define WBSD_CLK_12M&t;&t;0x01
DECL|macro|WBSD_CLK_16M
mdefine_line|#define WBSD_CLK_16M&t;&t;0x02
DECL|macro|WBSD_CLK_24M
mdefine_line|#define WBSD_CLK_24M&t;&t;0x03
DECL|macro|WBSD_DAT3_H
mdefine_line|#define WBSD_DAT3_H&t;&t;0x08
DECL|macro|WBSD_FIFO_RESET
mdefine_line|#define WBSD_FIFO_RESET&t;&t;0x04
DECL|macro|WBSD_SOFT_RESET
mdefine_line|#define WBSD_SOFT_RESET&t;&t;0x02
DECL|macro|WBSD_INC_INDEX
mdefine_line|#define WBSD_INC_INDEX&t;&t;0x01
DECL|macro|WBSD_DMA_SINGLE
mdefine_line|#define WBSD_DMA_SINGLE&t;&t;0x02
DECL|macro|WBSD_DMA_ENABLE
mdefine_line|#define WBSD_DMA_ENABLE&t;&t;0x01
DECL|macro|WBSD_FIFOEN_EMPTY
mdefine_line|#define WBSD_FIFOEN_EMPTY&t;0x20
DECL|macro|WBSD_FIFOEN_FULL
mdefine_line|#define WBSD_FIFOEN_FULL&t;0x10
DECL|macro|WBSD_FIFO_THREMASK
mdefine_line|#define WBSD_FIFO_THREMASK&t;0x0F
DECL|macro|WBSD_BLOCK_READ
mdefine_line|#define WBSD_BLOCK_READ&t;&t;0x80
DECL|macro|WBSD_BLOCK_WRITE
mdefine_line|#define WBSD_BLOCK_WRITE&t;0x40
DECL|macro|WBSD_BUSY
mdefine_line|#define WBSD_BUSY&t;&t;0x20
DECL|macro|WBSD_CARDTRAFFIC
mdefine_line|#define WBSD_CARDTRAFFIC&t;0x04
DECL|macro|WBSD_SENDCMD
mdefine_line|#define WBSD_SENDCMD&t;&t;0x02
DECL|macro|WBSD_RECVRES
mdefine_line|#define WBSD_RECVRES&t;&t;0x01
DECL|macro|WBSD_RSP_SHORT
mdefine_line|#define WBSD_RSP_SHORT&t;&t;0x00
DECL|macro|WBSD_RSP_LONG
mdefine_line|#define WBSD_RSP_LONG&t;&t;0x01
DECL|macro|WBSD_CRC_MASK
mdefine_line|#define WBSD_CRC_MASK&t;&t;0x1F
DECL|macro|WBSD_CRC_OK
mdefine_line|#define WBSD_CRC_OK&t;&t;0x05 /* S010E (00101) */
DECL|macro|WBSD_CRC_FAIL
mdefine_line|#define WBSD_CRC_FAIL&t;&t;0x0B /* S101E (01011) */
DECL|struct|wbsd_host
r_struct
id|wbsd_host
(brace
DECL|member|mmc
r_struct
id|mmc_host
op_star
id|mmc
suffix:semicolon
multiline_comment|/* MMC structure */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Mutex */
DECL|member|mrq
r_struct
id|mmc_request
op_star
id|mrq
suffix:semicolon
multiline_comment|/* Current request */
DECL|member|isr
id|u8
id|isr
suffix:semicolon
multiline_comment|/* Accumulated ISR */
DECL|member|cur_sg
r_struct
id|scatterlist
op_star
id|cur_sg
suffix:semicolon
multiline_comment|/* Current SG entry */
DECL|member|num_sg
r_int
r_int
id|num_sg
suffix:semicolon
multiline_comment|/* Number of entries left */
DECL|member|mapped_sg
r_void
op_star
id|mapped_sg
suffix:semicolon
multiline_comment|/* vaddr of mapped sg */
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* Offset into current entry */
DECL|member|remain
r_int
r_int
id|remain
suffix:semicolon
multiline_comment|/* Data left in curren entry */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* Total size of transfer */
DECL|member|dma_buffer
r_char
op_star
id|dma_buffer
suffix:semicolon
multiline_comment|/* ISA DMA buffer */
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
multiline_comment|/* Physical address for same */
DECL|member|firsterr
r_int
id|firsterr
suffix:semicolon
multiline_comment|/* See fifo functions */
DECL|member|clk
id|u8
id|clk
suffix:semicolon
multiline_comment|/* Current clock speed */
DECL|member|config
r_int
id|config
suffix:semicolon
multiline_comment|/* Config port */
DECL|member|unlock_code
id|u8
id|unlock_code
suffix:semicolon
multiline_comment|/* Code to unlock config */
DECL|member|chip_id
r_int
id|chip_id
suffix:semicolon
multiline_comment|/* ID of controller */
DECL|member|base
r_int
id|base
suffix:semicolon
multiline_comment|/* I/O port base */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* Interrupt */
DECL|member|dma
r_int
id|dma
suffix:semicolon
multiline_comment|/* DMA channel */
DECL|member|card_tasklet
r_struct
id|tasklet_struct
id|card_tasklet
suffix:semicolon
multiline_comment|/* Tasklet structures */
DECL|member|fifo_tasklet
r_struct
id|tasklet_struct
id|fifo_tasklet
suffix:semicolon
DECL|member|crc_tasklet
r_struct
id|tasklet_struct
id|crc_tasklet
suffix:semicolon
DECL|member|timeout_tasklet
r_struct
id|tasklet_struct
id|timeout_tasklet
suffix:semicolon
DECL|member|finish_tasklet
r_struct
id|tasklet_struct
id|finish_tasklet
suffix:semicolon
DECL|member|block_tasklet
r_struct
id|tasklet_struct
id|block_tasklet
suffix:semicolon
)brace
suffix:semicolon
eof
