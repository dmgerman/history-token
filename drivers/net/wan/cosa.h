multiline_comment|/* $Id: cosa.h,v 1.6 1999/01/06 14:02:44 kas Exp $ */
multiline_comment|/*&n; *  Copyright (C) 1995-1997  Jan &quot;Yenya&quot; Kasprzak &lt;kas@fi.muni.cz&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef COSA_H__
DECL|macro|COSA_H__
mdefine_line|#define COSA_H__
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/* status register - output bits */
DECL|macro|SR_RX_DMA_ENA
mdefine_line|#define SR_RX_DMA_ENA   0x04    /* receiver DMA enable bit */
DECL|macro|SR_TX_DMA_ENA
mdefine_line|#define SR_TX_DMA_ENA   0x08    /* transmitter DMA enable bit */
DECL|macro|SR_RST
mdefine_line|#define SR_RST          0x10    /* SRP reset */
DECL|macro|SR_USR_INT_ENA
mdefine_line|#define SR_USR_INT_ENA  0x20    /* user interrupt enable bit */
DECL|macro|SR_TX_INT_ENA
mdefine_line|#define SR_TX_INT_ENA   0x40    /* transmitter interrupt enable bit */
DECL|macro|SR_RX_INT_ENA
mdefine_line|#define SR_RX_INT_ENA   0x80    /* receiver interrupt enable bit */
multiline_comment|/* status register - input bits */
DECL|macro|SR_USR_RQ
mdefine_line|#define SR_USR_RQ       0x20    /* user interupt request pending */
DECL|macro|SR_TX_RDY
mdefine_line|#define SR_TX_RDY       0x40    /* transmitter empty (ready) */
DECL|macro|SR_RX_RDY
mdefine_line|#define SR_RX_RDY       0x80    /* receiver data ready */
DECL|macro|SR_UP_REQUEST
mdefine_line|#define SR_UP_REQUEST   0x02    /* request from SRP to transfer data&n;                                   up to PC */
DECL|macro|SR_DOWN_REQUEST
mdefine_line|#define SR_DOWN_REQUEST 0x01    /* SRP is able to transfer data down&n;                                   from PC to SRP */
DECL|macro|SR_END_OF_TRANSFER
mdefine_line|#define SR_END_OF_TRANSFER      0x03    /* SRP signalize end of&n;                                           transfer (up or down) */
DECL|macro|SR_CMD_FROM_SRP_MASK
mdefine_line|#define SR_CMD_FROM_SRP_MASK    0x03    /* mask to get SRP command */
multiline_comment|/* bits in driver status byte definitions : */
DECL|macro|SR_RDY_RCV
mdefine_line|#define SR_RDY_RCV      0x01    /* ready to receive packet */
DECL|macro|SR_RDY_SND
mdefine_line|#define SR_RDY_SND      0x02    /* ready to send packet */
DECL|macro|SR_CMD_PND
mdefine_line|#define SR_CMD_PND      0x04    /* command pending */ /* not currently used */
multiline_comment|/* ???? */
DECL|macro|SR_PKT_UP
mdefine_line|#define SR_PKT_UP       0x01    /* transfer of packet up in progress */
DECL|macro|SR_PKT_DOWN
mdefine_line|#define SR_PKT_DOWN     0x02    /* transfer of packet down in progress */
macro_line|#endif /* __KERNEL__ */
DECL|macro|SR_LOAD_ADDR
mdefine_line|#define SR_LOAD_ADDR    0x4400  /* SRP microcode load address */
DECL|macro|SR_START_ADDR
mdefine_line|#define SR_START_ADDR   0x4400  /* SRP microcode start address */
DECL|macro|COSA_LOAD_ADDR
mdefine_line|#define COSA_LOAD_ADDR    0x400  /* SRP microcode load address */
DECL|macro|COSA_MAX_FIRMWARE_SIZE
mdefine_line|#define COSA_MAX_FIRMWARE_SIZE&t;0x10000
multiline_comment|/* ioctls */
DECL|struct|cosa_download
r_struct
id|cosa_download
(brace
DECL|member|addr
DECL|member|len
r_int
id|addr
comma
id|len
suffix:semicolon
DECL|member|code
r_char
op_star
id|code
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Reset the device */
DECL|macro|COSAIORSET
mdefine_line|#define COSAIORSET&t;_IO(&squot;C&squot;,0xf0)
multiline_comment|/* Start microcode at given address */
DECL|macro|COSAIOSTRT
mdefine_line|#define COSAIOSTRT&t;_IOW(&squot;C&squot;,0xf1,sizeof(int))
multiline_comment|/* Read the block from the device memory */
DECL|macro|COSAIORMEM
mdefine_line|#define COSAIORMEM&t;_IOR(&squot;C&squot;,0xf2,sizeof(struct cosa_download *))
multiline_comment|/* Write the block to the device memory (i.e. download the microcode) */
DECL|macro|COSAIODOWNLD
mdefine_line|#define COSAIODOWNLD&t;_IOW(&squot;C&squot;,0xf2,sizeof(struct cosa_download *))
multiline_comment|/* Read the device type (one of &quot;srp&quot;, &quot;cosa&quot;, and &quot;cosa8&quot; for now) */
DECL|macro|COSAIORTYPE
mdefine_line|#define COSAIORTYPE&t;_IOR(&squot;C&squot;,0xf3,sizeof(char *))
multiline_comment|/* Read the device identification string */
DECL|macro|COSAIORIDSTR
mdefine_line|#define COSAIORIDSTR&t;_IOR(&squot;C&squot;,0xf4,sizeof(char *))
multiline_comment|/* Maximum length of the identification string. */
DECL|macro|COSA_MAX_ID_STRING
mdefine_line|#define COSA_MAX_ID_STRING 128
multiline_comment|/* Increment/decrement the module usage count :-) */
multiline_comment|/* #define COSAIOMINC&t;_IO(&squot;C&squot;,0xf5) */
multiline_comment|/* #define COSAIOMDEC&t;_IO(&squot;C&squot;,0xf6) */
multiline_comment|/* Get the total number of cards installed */
DECL|macro|COSAIONRCARDS
mdefine_line|#define COSAIONRCARDS&t;_IO(&squot;C&squot;,0xf7)
multiline_comment|/* Get the number of channels on this card */
DECL|macro|COSAIONRCHANS
mdefine_line|#define COSAIONRCHANS&t;_IO(&squot;C&squot;,0xf8)
multiline_comment|/* Set the driver for the bus-master operations */
DECL|macro|COSAIOBMSET
mdefine_line|#define COSAIOBMSET&t;_IOW(&squot;C&squot;, 0xf9, sizeof(unsigned short))
DECL|macro|COSA_BM_OFF
mdefine_line|#define COSA_BM_OFF&t;0&t;/* Bus-mastering off - use ISA DMA (default) */
DECL|macro|COSA_BM_ON
mdefine_line|#define COSA_BM_ON&t;1&t;/* Bus-mastering on - faster but untested */
multiline_comment|/* Gets the busmaster status */
DECL|macro|COSAIOBMGET
mdefine_line|#define COSAIOBMGET&t;_IO(&squot;C&squot;, 0xfa)
macro_line|#endif /* !COSA_H__ */
eof
