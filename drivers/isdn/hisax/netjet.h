multiline_comment|/* $Id: netjet.h,v 2.5.6.3 2001/09/23 22:24:50 kai Exp $&n; *&n; * NETjet common header file&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; *              by Matt Henderson,&n; *                 Traverse Technologies P/L www.traverse.com.au&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|macro|byteout
mdefine_line|#define byteout(addr,val) outb(val,addr)
DECL|macro|bytein
mdefine_line|#define bytein(addr) inb(addr)
DECL|macro|NETJET_CTRL
mdefine_line|#define NETJET_CTRL&t;0x00
DECL|macro|NETJET_DMACTRL
mdefine_line|#define NETJET_DMACTRL&t;0x01
DECL|macro|NETJET_AUXCTRL
mdefine_line|#define NETJET_AUXCTRL&t;0x02
DECL|macro|NETJET_AUXDATA
mdefine_line|#define NETJET_AUXDATA&t;0x03
DECL|macro|NETJET_IRQMASK0
mdefine_line|#define NETJET_IRQMASK0 0x04
DECL|macro|NETJET_IRQMASK1
mdefine_line|#define NETJET_IRQMASK1 0x05
DECL|macro|NETJET_IRQSTAT0
mdefine_line|#define NETJET_IRQSTAT0 0x06
DECL|macro|NETJET_IRQSTAT1
mdefine_line|#define NETJET_IRQSTAT1 0x07
DECL|macro|NETJET_DMA_READ_START
mdefine_line|#define NETJET_DMA_READ_START&t;0x08
DECL|macro|NETJET_DMA_READ_IRQ
mdefine_line|#define NETJET_DMA_READ_IRQ&t;0x0c
DECL|macro|NETJET_DMA_READ_END
mdefine_line|#define NETJET_DMA_READ_END&t;0x10
DECL|macro|NETJET_DMA_READ_ADR
mdefine_line|#define NETJET_DMA_READ_ADR&t;0x14
DECL|macro|NETJET_DMA_WRITE_START
mdefine_line|#define NETJET_DMA_WRITE_START&t;0x18
DECL|macro|NETJET_DMA_WRITE_IRQ
mdefine_line|#define NETJET_DMA_WRITE_IRQ&t;0x1c
DECL|macro|NETJET_DMA_WRITE_END
mdefine_line|#define NETJET_DMA_WRITE_END&t;0x20
DECL|macro|NETJET_DMA_WRITE_ADR
mdefine_line|#define NETJET_DMA_WRITE_ADR&t;0x24
DECL|macro|NETJET_PULSE_CNT
mdefine_line|#define NETJET_PULSE_CNT&t;0x28
DECL|macro|NETJET_ISAC_OFF
mdefine_line|#define NETJET_ISAC_OFF&t;0xc0
DECL|macro|NETJET_ISACIRQ
mdefine_line|#define NETJET_ISACIRQ&t;0x10
DECL|macro|NETJET_IRQM0_READ
mdefine_line|#define NETJET_IRQM0_READ&t;0x0c
DECL|macro|NETJET_IRQM0_READ_1
mdefine_line|#define NETJET_IRQM0_READ_1&t;0x04
DECL|macro|NETJET_IRQM0_READ_2
mdefine_line|#define NETJET_IRQM0_READ_2&t;0x08
DECL|macro|NETJET_IRQM0_WRITE
mdefine_line|#define NETJET_IRQM0_WRITE&t;0x03
DECL|macro|NETJET_IRQM0_WRITE_1
mdefine_line|#define NETJET_IRQM0_WRITE_1&t;0x01
DECL|macro|NETJET_IRQM0_WRITE_2
mdefine_line|#define NETJET_IRQM0_WRITE_2&t;0x02
DECL|macro|NETJET_DMA_TXSIZE
mdefine_line|#define NETJET_DMA_TXSIZE 512
DECL|macro|NETJET_DMA_RXSIZE
mdefine_line|#define NETJET_DMA_RXSIZE 128
DECL|macro|HDLC_ZERO_SEARCH
mdefine_line|#define HDLC_ZERO_SEARCH 0
DECL|macro|HDLC_FLAG_SEARCH
mdefine_line|#define HDLC_FLAG_SEARCH 1
DECL|macro|HDLC_FLAG_FOUND
mdefine_line|#define HDLC_FLAG_FOUND  2
DECL|macro|HDLC_FRAME_FOUND
mdefine_line|#define HDLC_FRAME_FOUND 3
DECL|macro|HDLC_NULL
mdefine_line|#define HDLC_NULL 4
DECL|macro|HDLC_PART
mdefine_line|#define HDLC_PART 5
DECL|macro|HDLC_FULL
mdefine_line|#define HDLC_FULL 6
DECL|macro|HDLC_FLAG_VALUE
mdefine_line|#define HDLC_FLAG_VALUE&t;0x7e
id|u_char
id|NETjet_ReadIC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|offset
)paren
suffix:semicolon
r_void
id|NETjet_WriteIC
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|offset
comma
id|u_char
id|value
)paren
suffix:semicolon
r_void
id|NETjet_ReadICfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
suffix:semicolon
r_void
id|NETjet_WriteICfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
op_star
id|data
comma
r_int
id|size
)paren
suffix:semicolon
r_void
id|read_tiger
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_void
id|write_tiger
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_void
id|netjet_fill_dma
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
suffix:semicolon
r_void
id|netjet_interrupt
c_func
(paren
r_int
id|intno
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
r_void
id|inittiger
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_void
id|release_io_netjet
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
