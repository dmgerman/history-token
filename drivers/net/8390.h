multiline_comment|/* Generic NS8390 register definitions. */
multiline_comment|/* This file is part of Donald Becker&squot;s 8390 drivers, and is distributed&n;   under the same license. Auto-loading of 8390.o only in v2.2 - Paul G.&n;   Some of these names and comments originated from the Crynwr&n;   packet drivers, which are distributed under the GPL. */
macro_line|#ifndef _8390_h
DECL|macro|_8390_h
mdefine_line|#define _8390_h
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
DECL|macro|TX_2X_PAGES
mdefine_line|#define TX_2X_PAGES 12
DECL|macro|TX_1X_PAGES
mdefine_line|#define TX_1X_PAGES 6
multiline_comment|/* Should always use two Tx slots to get back-to-back transmits. */
DECL|macro|EI_PINGPONG
mdefine_line|#define EI_PINGPONG
macro_line|#ifdef EI_PINGPONG
DECL|macro|TX_PAGES
mdefine_line|#define TX_PAGES TX_2X_PAGES
macro_line|#else
DECL|macro|TX_PAGES
mdefine_line|#define TX_PAGES TX_1X_PAGES
macro_line|#endif
DECL|macro|ETHER_ADDR_LEN
mdefine_line|#define ETHER_ADDR_LEN 6
multiline_comment|/* The 8390 specific per-packet-header format. */
DECL|struct|e8390_pkt_hdr
r_struct
id|e8390_pkt_hdr
(brace
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* status */
DECL|member|next
r_int
r_char
id|next
suffix:semicolon
multiline_comment|/* pointer to next packet. */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* header + packet length in bytes */
)brace
suffix:semicolon
macro_line|#ifdef notdef
r_extern
r_int
id|ei_debug
suffix:semicolon
macro_line|#else
DECL|macro|ei_debug
mdefine_line|#define ei_debug 1
macro_line|#endif
macro_line|#ifndef HAVE_AUTOIRQ
multiline_comment|/* From auto_irq.c */
r_extern
r_void
id|autoirq_setup
c_func
(paren
r_int
id|waittime
)paren
suffix:semicolon
r_extern
r_int
r_int
id|autoirq_report
c_func
(paren
r_int
id|waittime
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Currently unused - delete in v2.5.x after purging from drivers */
DECL|macro|load_8390_module
mdefine_line|#define load_8390_module(driver)&t;0
DECL|macro|unload_8390_module
mdefine_line|#define unload_8390_module()&t;&t;do { } while (0)
r_extern
r_int
id|ethdev_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|NS8390_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|startp
)paren
suffix:semicolon
r_extern
r_int
id|ei_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ei_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|ei_interrupt
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
multiline_comment|/* Most of these entries should be in &squot;struct net_device&squot; (or most of the&n;   things in there should be here!) */
multiline_comment|/* You have one of these per-board */
DECL|struct|ei_device
r_struct
id|ei_device
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|reset_8390
r_void
(paren
op_star
id|reset_8390
)paren
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|member|get_8390_hdr
r_void
(paren
op_star
id|get_8390_hdr
)paren
(paren
r_struct
id|net_device
op_star
comma
r_struct
id|e8390_pkt_hdr
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|block_output
r_void
(paren
op_star
id|block_output
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
comma
r_const
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|block_input
r_void
(paren
op_star
id|block_input
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
comma
r_struct
id|sk_buff
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|mcfilter
r_int
r_char
id|mcfilter
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:colon
l_int|1
suffix:semicolon
DECL|member|word16
r_int
id|word16
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* We have the 16-bit (vs 8-bit) version of the card. */
DECL|member|bigendian
r_int
id|bigendian
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16-bit big endian mode */
DECL|member|txing
r_int
id|txing
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Transmit Active */
DECL|member|irqlock
r_int
id|irqlock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 8390&squot;s intrs disabled when &squot;1&squot;. */
DECL|member|dmaing
r_int
id|dmaing
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Remote DMA Active */
DECL|member|tx_start_page
DECL|member|rx_start_page
DECL|member|stop_page
r_int
r_char
id|tx_start_page
comma
id|rx_start_page
comma
id|stop_page
suffix:semicolon
DECL|member|current_page
r_int
r_char
id|current_page
suffix:semicolon
multiline_comment|/* Read pointer in buffer  */
DECL|member|interface_num
r_int
r_char
id|interface_num
suffix:semicolon
multiline_comment|/* Net port (AUI, 10bT.) to use. */
DECL|member|txqueue
r_int
r_char
id|txqueue
suffix:semicolon
multiline_comment|/* Tx Packet buffer queue length. */
DECL|member|tx1
DECL|member|tx2
r_int
id|tx1
comma
id|tx2
suffix:semicolon
multiline_comment|/* Packet lengths for ping-pong tx. */
DECL|member|lasttx
r_int
id|lasttx
suffix:semicolon
multiline_comment|/* Alpha version consistency check. */
DECL|member|reg0
r_int
r_char
id|reg0
suffix:semicolon
multiline_comment|/* Register &squot;0&squot; in a WD8013 */
DECL|member|reg5
r_int
r_char
id|reg5
suffix:semicolon
multiline_comment|/* Register &squot;5&squot; in a WD8013 */
DECL|member|saved_irq
r_int
r_char
id|saved_irq
suffix:semicolon
multiline_comment|/* Original dev-&gt;irq value. */
DECL|member|stat
r_struct
id|net_device_stats
id|stat
suffix:semicolon
multiline_comment|/* The new statistics table. */
DECL|member|reg_offset
id|u32
op_star
id|reg_offset
suffix:semicolon
multiline_comment|/* Register mapping table */
DECL|member|page_lock
id|spinlock_t
id|page_lock
suffix:semicolon
multiline_comment|/* Page register locks */
DECL|member|priv
r_int
r_int
id|priv
suffix:semicolon
multiline_comment|/* Private field to store bus IDs etc. */
)brace
suffix:semicolon
multiline_comment|/* The maximum number of 8390 interrupt service routines called per IRQ. */
DECL|macro|MAX_SERVICE
mdefine_line|#define MAX_SERVICE 12
multiline_comment|/* The maximum time waited (in jiffies) before assuming a Tx failed. (20ms) */
DECL|macro|TX_TIMEOUT
mdefine_line|#define TX_TIMEOUT (20*HZ/100)
DECL|macro|ei_status
mdefine_line|#define ei_status (*(struct ei_device *)(dev-&gt;priv))
multiline_comment|/* Some generic ethernet register configurations. */
DECL|macro|E8390_TX_IRQ_MASK
mdefine_line|#define E8390_TX_IRQ_MASK&t;0xa&t;/* For register EN0_ISR */
DECL|macro|E8390_RX_IRQ_MASK
mdefine_line|#define E8390_RX_IRQ_MASK&t;0x5
DECL|macro|E8390_RXCONFIG
mdefine_line|#define E8390_RXCONFIG&t;&t;0x4&t;/* EN0_RXCR: broadcasts, no multicast,errors */
DECL|macro|E8390_RXOFF
mdefine_line|#define E8390_RXOFF&t;&t;0x20&t;/* EN0_RXCR: Accept no packets */
DECL|macro|E8390_TXCONFIG
mdefine_line|#define E8390_TXCONFIG&t;&t;0x00&t;/* EN0_TXCR: Normal transmit mode */
DECL|macro|E8390_TXOFF
mdefine_line|#define E8390_TXOFF&t;&t;0x02&t;/* EN0_TXCR: Transmitter off */
multiline_comment|/*  Register accessed at EN_CMD, the 8390 base addr.  */
DECL|macro|E8390_STOP
mdefine_line|#define E8390_STOP&t;0x01&t;/* Stop and reset the chip */
DECL|macro|E8390_START
mdefine_line|#define E8390_START&t;0x02&t;/* Start the chip, clear reset */
DECL|macro|E8390_TRANS
mdefine_line|#define E8390_TRANS&t;0x04&t;/* Transmit a frame */
DECL|macro|E8390_RREAD
mdefine_line|#define E8390_RREAD&t;0x08&t;/* Remote read */
DECL|macro|E8390_RWRITE
mdefine_line|#define E8390_RWRITE&t;0x10&t;/* Remote write  */
DECL|macro|E8390_NODMA
mdefine_line|#define E8390_NODMA&t;0x20&t;/* Remote DMA */
DECL|macro|E8390_PAGE0
mdefine_line|#define E8390_PAGE0&t;0x00&t;/* Select page chip registers */
DECL|macro|E8390_PAGE1
mdefine_line|#define E8390_PAGE1&t;0x40&t;/* using the two high-order bits */
DECL|macro|E8390_PAGE2
mdefine_line|#define E8390_PAGE2&t;0x80&t;/* Page 3 is invalid. */
multiline_comment|/*&n; *&t;Only generate indirect loads given a machine that needs them.&n; */
macro_line|#if defined(CONFIG_MAC) || defined(CONFIG_AMIGA_PCMCIA) || &bslash;&n;    defined(CONFIG_ARIADNE2) || defined(CONFIG_ARIADNE2_MODULE) || &bslash;&n;    defined(CONFIG_HYDRA) || defined(CONFIG_HYDRA_MODULE)
DECL|macro|EI_SHIFT
mdefine_line|#define EI_SHIFT(x)&t;(ei_local-&gt;reg_offset[x])
macro_line|#else
DECL|macro|EI_SHIFT
mdefine_line|#define EI_SHIFT(x)&t;(x)
macro_line|#endif
DECL|macro|E8390_CMD
mdefine_line|#define E8390_CMD&t;EI_SHIFT(0x00)  /* The command register (for all pages) */
multiline_comment|/* Page 0 register offsets. */
DECL|macro|EN0_CLDALO
mdefine_line|#define EN0_CLDALO&t;EI_SHIFT(0x01)&t;/* Low byte of current local dma addr  RD */
DECL|macro|EN0_STARTPG
mdefine_line|#define EN0_STARTPG&t;EI_SHIFT(0x01)&t;/* Starting page of ring bfr WR */
DECL|macro|EN0_CLDAHI
mdefine_line|#define EN0_CLDAHI&t;EI_SHIFT(0x02)&t;/* High byte of current local dma addr  RD */
DECL|macro|EN0_STOPPG
mdefine_line|#define EN0_STOPPG&t;EI_SHIFT(0x02)&t;/* Ending page +1 of ring bfr WR */
DECL|macro|EN0_BOUNDARY
mdefine_line|#define EN0_BOUNDARY&t;EI_SHIFT(0x03)&t;/* Boundary page of ring bfr RD WR */
DECL|macro|EN0_TSR
mdefine_line|#define EN0_TSR&t;&t;EI_SHIFT(0x04)&t;/* Transmit status reg RD */
DECL|macro|EN0_TPSR
mdefine_line|#define EN0_TPSR&t;EI_SHIFT(0x04)&t;/* Transmit starting page WR */
DECL|macro|EN0_NCR
mdefine_line|#define EN0_NCR&t;&t;EI_SHIFT(0x05)&t;/* Number of collision reg RD */
DECL|macro|EN0_TCNTLO
mdefine_line|#define EN0_TCNTLO&t;EI_SHIFT(0x05)&t;/* Low  byte of tx byte count WR */
DECL|macro|EN0_FIFO
mdefine_line|#define EN0_FIFO&t;EI_SHIFT(0x06)&t;/* FIFO RD */
DECL|macro|EN0_TCNTHI
mdefine_line|#define EN0_TCNTHI&t;EI_SHIFT(0x06)&t;/* High byte of tx byte count WR */
DECL|macro|EN0_ISR
mdefine_line|#define EN0_ISR&t;&t;EI_SHIFT(0x07)&t;/* Interrupt status reg RD WR */
DECL|macro|EN0_CRDALO
mdefine_line|#define EN0_CRDALO&t;EI_SHIFT(0x08)&t;/* low byte of current remote dma address RD */
DECL|macro|EN0_RSARLO
mdefine_line|#define EN0_RSARLO&t;EI_SHIFT(0x08)&t;/* Remote start address reg 0 */
DECL|macro|EN0_CRDAHI
mdefine_line|#define EN0_CRDAHI&t;EI_SHIFT(0x09)&t;/* high byte, current remote dma address RD */
DECL|macro|EN0_RSARHI
mdefine_line|#define EN0_RSARHI&t;EI_SHIFT(0x09)&t;/* Remote start address reg 1 */
DECL|macro|EN0_RCNTLO
mdefine_line|#define EN0_RCNTLO&t;EI_SHIFT(0x0a)&t;/* Remote byte count reg WR */
DECL|macro|EN0_RCNTHI
mdefine_line|#define EN0_RCNTHI&t;EI_SHIFT(0x0b)&t;/* Remote byte count reg WR */
DECL|macro|EN0_RSR
mdefine_line|#define EN0_RSR&t;&t;EI_SHIFT(0x0c)&t;/* rx status reg RD */
DECL|macro|EN0_RXCR
mdefine_line|#define EN0_RXCR&t;EI_SHIFT(0x0c)&t;/* RX configuration reg WR */
DECL|macro|EN0_TXCR
mdefine_line|#define EN0_TXCR&t;EI_SHIFT(0x0d)&t;/* TX configuration reg WR */
DECL|macro|EN0_COUNTER0
mdefine_line|#define EN0_COUNTER0&t;EI_SHIFT(0x0d)&t;/* Rcv alignment error counter RD */
DECL|macro|EN0_DCFG
mdefine_line|#define EN0_DCFG&t;EI_SHIFT(0x0e)&t;/* Data configuration reg WR */
DECL|macro|EN0_COUNTER1
mdefine_line|#define EN0_COUNTER1&t;EI_SHIFT(0x0e)&t;/* Rcv CRC error counter RD */
DECL|macro|EN0_IMR
mdefine_line|#define EN0_IMR&t;&t;EI_SHIFT(0x0f)&t;/* Interrupt mask reg WR */
DECL|macro|EN0_COUNTER2
mdefine_line|#define EN0_COUNTER2&t;EI_SHIFT(0x0f)&t;/* Rcv missed frame error counter RD */
multiline_comment|/* Bits in EN0_ISR - Interrupt status register */
DECL|macro|ENISR_RX
mdefine_line|#define ENISR_RX&t;0x01&t;/* Receiver, no error */
DECL|macro|ENISR_TX
mdefine_line|#define ENISR_TX&t;0x02&t;/* Transmitter, no error */
DECL|macro|ENISR_RX_ERR
mdefine_line|#define ENISR_RX_ERR&t;0x04&t;/* Receiver, with error */
DECL|macro|ENISR_TX_ERR
mdefine_line|#define ENISR_TX_ERR&t;0x08&t;/* Transmitter, with error */
DECL|macro|ENISR_OVER
mdefine_line|#define ENISR_OVER&t;0x10&t;/* Receiver overwrote the ring */
DECL|macro|ENISR_COUNTERS
mdefine_line|#define ENISR_COUNTERS&t;0x20&t;/* Counters need emptying */
DECL|macro|ENISR_RDC
mdefine_line|#define ENISR_RDC&t;0x40&t;/* remote dma complete */
DECL|macro|ENISR_RESET
mdefine_line|#define ENISR_RESET&t;0x80&t;/* Reset completed */
DECL|macro|ENISR_ALL
mdefine_line|#define ENISR_ALL&t;0x3f&t;/* Interrupts we will enable */
multiline_comment|/* Bits in EN0_DCFG - Data config register */
DECL|macro|ENDCFG_WTS
mdefine_line|#define ENDCFG_WTS&t;0x01&t;/* word transfer mode selection */
DECL|macro|ENDCFG_BOS
mdefine_line|#define ENDCFG_BOS&t;0x02&t;/* byte order selection */
multiline_comment|/* Page 1 register offsets. */
DECL|macro|EN1_PHYS
mdefine_line|#define EN1_PHYS   EI_SHIFT(0x01)&t;/* This board&squot;s physical enet addr RD WR */
DECL|macro|EN1_PHYS_SHIFT
mdefine_line|#define EN1_PHYS_SHIFT(i)  EI_SHIFT(i+1) /* Get and set mac address */
DECL|macro|EN1_CURPAG
mdefine_line|#define EN1_CURPAG EI_SHIFT(0x07)&t;/* Current memory page RD WR */
DECL|macro|EN1_MULT
mdefine_line|#define EN1_MULT   EI_SHIFT(0x08)&t;/* Multicast filter mask array (8 bytes) RD WR */
DECL|macro|EN1_MULT_SHIFT
mdefine_line|#define EN1_MULT_SHIFT(i)  EI_SHIFT(8+i) /* Get and set multicast filter */
multiline_comment|/* Bits in received packet status byte and EN0_RSR*/
DECL|macro|ENRSR_RXOK
mdefine_line|#define ENRSR_RXOK&t;0x01&t;/* Received a good packet */
DECL|macro|ENRSR_CRC
mdefine_line|#define ENRSR_CRC&t;0x02&t;/* CRC error */
DECL|macro|ENRSR_FAE
mdefine_line|#define ENRSR_FAE&t;0x04&t;/* frame alignment error */
DECL|macro|ENRSR_FO
mdefine_line|#define ENRSR_FO&t;0x08&t;/* FIFO overrun */
DECL|macro|ENRSR_MPA
mdefine_line|#define ENRSR_MPA&t;0x10&t;/* missed pkt */
DECL|macro|ENRSR_PHY
mdefine_line|#define ENRSR_PHY&t;0x20&t;/* physical/multicast address */
DECL|macro|ENRSR_DIS
mdefine_line|#define ENRSR_DIS&t;0x40&t;/* receiver disable. set in monitor mode */
DECL|macro|ENRSR_DEF
mdefine_line|#define ENRSR_DEF&t;0x80&t;/* deferring */
multiline_comment|/* Transmitted packet status, EN0_TSR. */
DECL|macro|ENTSR_PTX
mdefine_line|#define ENTSR_PTX 0x01&t;/* Packet transmitted without error */
DECL|macro|ENTSR_ND
mdefine_line|#define ENTSR_ND  0x02&t;/* The transmit wasn&squot;t deferred. */
DECL|macro|ENTSR_COL
mdefine_line|#define ENTSR_COL 0x04&t;/* The transmit collided at least once. */
DECL|macro|ENTSR_ABT
mdefine_line|#define ENTSR_ABT 0x08  /* The transmit collided 16 times, and was deferred. */
DECL|macro|ENTSR_CRS
mdefine_line|#define ENTSR_CRS 0x10&t;/* The carrier sense was lost. */
DECL|macro|ENTSR_FU
mdefine_line|#define ENTSR_FU  0x20  /* A &quot;FIFO underrun&quot; occurred during transmit. */
DECL|macro|ENTSR_CDH
mdefine_line|#define ENTSR_CDH 0x40&t;/* The collision detect &quot;heartbeat&quot; signal was lost. */
DECL|macro|ENTSR_OWC
mdefine_line|#define ENTSR_OWC 0x80  /* There was an out-of-window collision. */
macro_line|#endif /* _8390_h */
eof
