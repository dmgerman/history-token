multiline_comment|/*&n; *&n; *    Copyright (c) 1999-2000 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: oaknet.c&n; *&n; *    Description:&n; *      Driver for the National Semiconductor DP83902AV Ethernet controller&n; *      on-board the IBM PowerPC &quot;Oak&quot; evaluation board. Adapted from the&n; *      various other 8390 drivers written by Donald Becker and Paul Gortmaker.&n; *&n; *      Additional inspiration from the &quot;tcd8390.c&quot; driver from TiVo, Inc. &n; *      and &quot;enetLib.c&quot; from IBM.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/board.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;8390.h&quot;
multiline_comment|/* Preprocessor Defines */
macro_line|#if !defined(TRUE) || TRUE != 1
DECL|macro|TRUE
mdefine_line|#define&t;TRUE&t;1
macro_line|#endif
macro_line|#if !defined(FALSE) || FALSE != 0
DECL|macro|FALSE
mdefine_line|#define&t;FALSE&t;0
macro_line|#endif
DECL|macro|OAKNET_START_PG
mdefine_line|#define&t;OAKNET_START_PG&t;&t;0x20&t;/* First page of TX buffer */
DECL|macro|OAKNET_STOP_PG
mdefine_line|#define&t;OAKNET_STOP_PG&t;&t;0x40&t;/* Last pagge +1 of RX ring */
DECL|macro|OAKNET_WAIT
mdefine_line|#define&t;OAKNET_WAIT&t;&t;(2 * HZ / 100)&t;/* 20 ms */
multiline_comment|/* Experimenting with some fixes for a broken driver... */
DECL|macro|OAKNET_DISINT
mdefine_line|#define&t;OAKNET_DISINT
DECL|macro|OAKNET_HEADCHECK
mdefine_line|#define&t;OAKNET_HEADCHECK
DECL|macro|OAKNET_RWFIX
mdefine_line|#define&t;OAKNET_RWFIX
multiline_comment|/* Global Variables */
DECL|variable|name
r_static
r_const
r_char
op_star
id|name
op_assign
l_string|&quot;National DP83902AV&quot;
suffix:semicolon
DECL|variable|oaknet_devs
r_static
r_struct
id|net_device
op_star
id|oaknet_devs
suffix:semicolon
multiline_comment|/* Function Prototypes */
r_static
r_int
id|oaknet_open
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
id|oaknet_close
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
id|oaknet_reset_8390
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
id|oaknet_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
suffix:semicolon
r_static
r_void
id|oaknet_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
suffix:semicolon
r_static
r_void
id|oaknet_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|start_page
)paren
suffix:semicolon
r_static
r_void
id|oaknet_dma_error
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/*&n; * int oaknet_init()&n; *&n; * Description:&n; *   This routine performs all the necessary platform-specific initiali-&n; *   zation and set-up for the IBM &quot;Oak&quot; evaluation board&squot;s National&n; *   Semiconductor DP83902AV &quot;ST-NIC&quot; Ethernet controller.&n; *&n; * Input(s):&n; *   N/A&n; *&n; * Output(s):&n; *   N/A&n; *&n; * Returns:&n; *   0 if OK, otherwise system error number on error.&n; *&n; */
DECL|function|oaknet_init
r_static
r_int
id|__init
id|oaknet_init
c_func
(paren
r_void
)paren
(brace
r_register
r_int
id|i
suffix:semicolon
r_int
id|reg0
comma
id|regd
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|net_device
id|tmp
comma
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if 0
r_int
r_int
id|ioaddr
op_assign
id|OAKNET_IO_BASE
suffix:semicolon
macro_line|#else
r_int
r_int
id|ioaddr
op_assign
id|ioremap
c_func
(paren
id|OAKNET_IO_BASE
comma
id|OAKNET_IO_SIZE
)paren
suffix:semicolon
macro_line|#endif
id|bd_t
op_star
id|bip
op_assign
(paren
id|bd_t
op_star
)paren
id|__res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ioaddr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/*&n;&t; * This MUST happen here because of the nic_* macros&n;&t; * which have an implicit dependency on dev-&gt;base_addr.&n;&t; */
id|tmp.base_addr
op_assign
id|ioaddr
suffix:semicolon
id|dev
op_assign
op_amp
id|tmp
suffix:semicolon
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|OAKNET_IO_BASE
comma
id|OAKNET_IO_SIZE
comma
id|name
)paren
)paren
r_goto
id|out_unmap
suffix:semicolon
multiline_comment|/* Quick register check to see if the device is really there. */
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|reg0
op_assign
id|ei_ibp
c_func
(paren
id|ioaddr
)paren
)paren
op_eq
l_int|0xFF
)paren
r_goto
id|out_region
suffix:semicolon
multiline_comment|/*&n;&t; * That worked. Now a more thorough check, using the multicast&n;&t; * address registers, that the device is definitely out there&n;&t; * and semi-functional.&n;&t; */
id|ei_obp
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE1
op_plus
id|E8390_STOP
comma
id|ioaddr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|regd
op_assign
id|ei_ibp
c_func
(paren
id|ioaddr
op_plus
l_int|0x0D
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
l_int|0xFF
comma
id|ioaddr
op_plus
l_int|0x0D
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
comma
id|ioaddr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|ei_ibp
c_func
(paren
id|ioaddr
op_plus
id|EN0_COUNTER0
)paren
suffix:semicolon
multiline_comment|/* It&squot;s no good. Fix things back up and leave. */
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|ei_ibp
c_func
(paren
id|ioaddr
op_plus
id|EN0_COUNTER0
)paren
op_ne
l_int|0
)paren
(brace
id|ei_obp
c_func
(paren
id|reg0
comma
id|ioaddr
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|regd
comma
id|ioaddr
op_plus
l_int|0x0D
)paren
suffix:semicolon
r_goto
id|out_region
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We&squot;re not using the old-style probing API, so we have to allocate&n;&t; * our own device structure.&n;&t; */
id|dev
op_assign
id|init_etherdev
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_goto
id|out_region
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|oaknet_devs
op_assign
id|dev
suffix:semicolon
multiline_comment|/*&n;&t; * This controller is on an embedded board, so the base address&n;&t; * and interrupt assignments are pre-assigned and unchageable.&n;&t; */
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|dev-&gt;irq
op_assign
id|OAKNET_INT
suffix:semicolon
multiline_comment|/* Allocate 8390-specific device-private area and fields. */
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|ethdev_init
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; unable to get memory for dev-&gt;priv.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_dev
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Disable all chip interrupts for now and ACK all pending&n;&t; * interrupts.&n;&t; */
id|ei_obp
c_func
(paren
l_int|0x0
comma
id|ioaddr
op_plus
id|EN0_IMR
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
l_int|0xFF
comma
id|ioaddr
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Attempt to get the interrupt line */
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|ei_interrupt
comma
l_int|0
comma
id|name
comma
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: unable to request interrupt %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_goto
id|out_priv
suffix:semicolon
)brace
multiline_comment|/* Tell the world about what and where we&squot;ve found. */
id|printk
c_func
(paren
l_string|&quot;%s: %s at&quot;
comma
id|dev-&gt;name
comma
id|name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ETHER_ADDR_LEN
suffix:semicolon
op_increment
id|i
)paren
(brace
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|bip-&gt;bi_enetaddr
(braket
id|i
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%c%.2x&quot;
comma
(paren
id|i
ques
c_cond
l_char|&squot;:&squot;
suffix:colon
l_char|&squot; &squot;
)paren
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;, found at %#lx, using IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Set up some required driver fields and then we&squot;re done. */
id|ei_status.name
op_assign
id|name
suffix:semicolon
id|ei_status.word16
op_assign
id|FALSE
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|OAKNET_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|OAKNET_START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|OAKNET_STOP_PG
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|oaknet_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|oaknet_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|oaknet_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|oaknet_get_8390_hdr
suffix:semicolon
id|dev-&gt;open
op_assign
id|oaknet_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|oaknet_close
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
id|FALSE
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|out_priv
suffix:colon
id|kfree
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|out_dev
suffix:colon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out_region
suffix:colon
id|release_region
c_func
(paren
id|OAKNET_IO_BASE
comma
id|OAKNET_IO_SIZE
)paren
suffix:semicolon
id|out_unmap
suffix:colon
id|iounmap
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * static int oaknet_open()&n; *&n; * Description:&n; *   This routine is a modest wrapper around ei_open, the 8390-generic,&n; *   driver open routine. This just increments the module usage count&n; *   and passes along the status from ei_open.&n; *&n; * Input(s):&n; *  *dev - Pointer to the device structure for this driver.&n; *&n; * Output(s):&n; *  *dev - Pointer to the device structure for this driver, potentially&n; *         modified by ei_open.&n; *&n; * Returns:&n; *   0 if OK, otherwise &lt; 0 on error.&n; *&n; */
r_static
r_int
DECL|function|oaknet_open
id|oaknet_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|status
op_assign
id|ei_open
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * static int oaknet_close()&n; *&n; * Description:&n; *   This routine is a modest wrapper around ei_close, the 8390-generic,&n; *   driver close routine. This just decrements the module usage count&n; *   and passes along the status from ei_close.&n; *&n; * Input(s):&n; *  *dev - Pointer to the device structure for this driver.&n; *&n; * Output(s):&n; *  *dev - Pointer to the device structure for this driver, potentially&n; *         modified by ei_close.&n; *&n; * Returns:&n; *   0 if OK, otherwise &lt; 0 on error.&n; *&n; */
r_static
r_int
DECL|function|oaknet_close
id|oaknet_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|status
op_assign
id|ei_close
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * static void oaknet_reset_8390()&n; *&n; * Description:&n; *   This routine resets the DP83902 chip.&n; *&n; * Input(s):&n; *  *dev - Pointer to the device structure for this driver.&n; *&n; * Output(s):&n; *   N/A&n; *&n; * Returns:&n; *   N/A&n; *&n; */
r_static
r_void
DECL|function|oaknet_reset_8390
id|oaknet_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|base
op_assign
id|E8390_BASE
suffix:semicolon
multiline_comment|/*&n;&t; * We have no provision of reseting the controller as is done&n;&t; * in other drivers, such as &quot;ne.c&quot;. However, the following&n;&t; * seems to work well enough in the TiVo driver.&n;&t; */
id|printk
c_func
(paren
l_string|&quot;Resetting %s...&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|E8390_STOP
op_or
id|E8390_NODMA
op_or
id|E8390_PAGE0
comma
id|base
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|ei_status.dmaing
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * static void oaknet_get_8390_hdr()&n; *&n; * Description:&n; *   This routine grabs the 8390-specific header. It&squot;s similar to the&n; *   block input routine, but we don&squot;t need to be concerned with ring wrap&n; *   as the header will be at the start of a page, so we optimize accordingly.&n; *&n; * Input(s):&n; *  *dev       - Pointer to the device structure for this driver.&n; *  *hdr       - Pointer to storage for the 8390-specific packet header.&n; *   ring_page - ?&n; *&n; * Output(s):&n; *  *hdr       - Pointer to the 8390-specific packet header for the just-&n; *               received frame.&n; *&n; * Returns:&n; *   N/A&n; *&n; */
r_static
r_void
DECL|function|oaknet_get_8390_hdr
id|oaknet_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
(brace
r_int
id|base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
multiline_comment|/*&n;&t; * This should NOT happen. If it does, it is the LAST thing you&squot;ll&n;&t; * see.&n;&t; */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|oaknet_dma_error
c_func
(paren
id|dev
comma
l_string|&quot;oaknet_get_8390_hdr&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_START
comma
id|base
op_plus
id|OAKNET_CMD
)paren
suffix:semicolon
id|outb_p
c_func
(paren
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
comma
id|base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
multiline_comment|/* On page boundary */
id|outb_p
c_func
(paren
id|ring_page
comma
id|base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|base
op_plus
id|OAKNET_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
id|insw
c_func
(paren
id|base
op_plus
id|OAKNET_DATA
comma
id|hdr
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_else
id|insb
c_func
(paren
id|base
op_plus
id|OAKNET_DATA
comma
id|hdr
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
)paren
suffix:semicolon
multiline_comment|/* Byte-swap the packet byte count */
id|hdr-&gt;count
op_assign
id|le16_to_cpu
c_func
(paren
id|hdr-&gt;count
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ENISR_RDC
comma
id|base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* ACK Remote DMA interrupt */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
)brace
multiline_comment|/*&n; * XXX - Document me.&n; */
r_static
r_void
DECL|function|oaknet_block_input
id|oaknet_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
(brace
r_int
id|base
op_assign
id|OAKNET_BASE
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/*&n;&t; * This should NOT happen. If it does, it is the LAST thing you&squot;ll&n;&t; * see.&n;&t; */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|oaknet_dma_error
c_func
(paren
id|dev
comma
l_string|&quot;oaknet_block_input&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef OAKNET_DISINT
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
id|ei_obp
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_START
comma
id|base
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|ring_offset
op_amp
l_int|0xff
comma
id|base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|ring_offset
op_rshift
l_int|8
comma
id|base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|base
op_plus
id|E8390_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
(brace
id|ei_isw
c_func
(paren
id|base
op_plus
id|E8390_DATA
comma
id|buf
comma
id|count
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|0x01
)paren
(brace
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|ei_ib
c_func
(paren
id|base
op_plus
id|E8390_DATA
)paren
suffix:semicolon
macro_line|#ifdef OAKNET_HEADCHECK
id|bytes
op_increment
suffix:semicolon
macro_line|#endif
)brace
)brace
r_else
(brace
id|ei_isb
c_func
(paren
id|base
op_plus
id|E8390_DATA
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
macro_line|#ifdef OAKNET_HEADCHECK
multiline_comment|/*&n;&t; * This was for the ALPHA version only, but enough people have&n;&t; * been encountering problems so it is still here.  If you see&n;&t; * this message you either 1) have a slightly incompatible clone&n;&t; * or 2) have noise/speed problems with your bus.&n;&t; */
multiline_comment|/* DMA termination address check... */
(brace
r_int
id|addr
comma
id|tries
op_assign
l_int|20
suffix:semicolon
r_do
(brace
multiline_comment|/* DON&squot;T check for &squot;ei_ibp(EN0_ISR) &amp; ENISR_RDC&squot; here&n;&t;&t;&t;   -- it&squot;s broken for Rx on some cards! */
r_int
id|high
op_assign
id|ei_ibp
c_func
(paren
id|base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
r_int
id|low
op_assign
id|ei_ibp
c_func
(paren
id|base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|addr
op_assign
(paren
id|high
op_lshift
l_int|8
)paren
op_plus
id|low
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|ring_offset
op_plus
id|bytes
)paren
op_amp
l_int|0xff
)paren
op_eq
id|low
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|tries
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tries
op_le
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: RX transfer address mismatch,&quot;
l_string|&quot;%#4.4x (expected) vs. %#4.4x (actual).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ring_offset
op_plus
id|bytes
comma
id|addr
)paren
suffix:semicolon
)brace
macro_line|#endif
id|ei_obp
c_func
(paren
id|ENISR_RDC
comma
id|base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* ACK Remote DMA interrupt */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
macro_line|#ifdef OAKNET_DISINT
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * static void oaknet_block_output()&n; *&n; * Description:&n; *   This routine...&n; *&n; * Input(s):&n; *  *dev        - Pointer to the device structure for this driver.&n; *   count      - Number of bytes to be transferred.&n; *  *buf        - &n; *   start_page - &n; *&n; * Output(s):&n; *   N/A&n; *&n; * Returns:&n; *   N/A&n; *&n; */
r_static
r_void
DECL|function|oaknet_block_output
id|oaknet_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|start_page
)paren
(brace
r_int
id|base
op_assign
id|E8390_BASE
suffix:semicolon
macro_line|#if 0
r_int
id|bug
suffix:semicolon
macro_line|#endif
r_int
r_int
id|start
suffix:semicolon
macro_line|#ifdef OAKNET_DISINT
r_int
r_int
id|flags
suffix:semicolon
macro_line|#endif
macro_line|#ifdef OAKNET_HEADCHECK
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* Round the count up for word writes. */
r_if
c_cond
(paren
id|ei_status.word16
op_logical_and
(paren
id|count
op_amp
l_int|0x1
)paren
)paren
id|count
op_increment
suffix:semicolon
multiline_comment|/*&n;&t; * This should NOT happen. If it does, it is the LAST thing you&squot;ll&n;&t; * see.&n;&t; */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|oaknet_dma_error
c_func
(paren
id|dev
comma
l_string|&quot;oaknet_block_output&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef OAKNET_DISINT
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* Make sure we are in page 0. */
id|ei_obp
c_func
(paren
id|E8390_PAGE0
op_plus
id|E8390_START
op_plus
id|E8390_NODMA
comma
id|base
op_plus
id|E8390_CMD
)paren
suffix:semicolon
macro_line|#ifdef OAKNET_HEADCHECK
id|retry
suffix:colon
macro_line|#endif
macro_line|#if 0
multiline_comment|/*&n;&t; * The 83902 documentation states that the processor needs to&n;&t; * do a &quot;dummy read&quot; before doing the remote write to work&n;&t; * around a chip bug they don&squot;t feel like fixing.&n;&t; */
id|bug
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
r_int
id|rdhi
suffix:semicolon
r_int
r_int
id|rdlo
suffix:semicolon
multiline_comment|/* Now the normal output. */
id|ei_obp
c_func
(paren
id|ENISR_RDC
comma
id|base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
l_int|0x00
comma
id|base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|start_page
comma
id|base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bug
op_increment
)paren
r_break
suffix:semicolon
multiline_comment|/* Perform the dummy read */
id|rdhi
op_assign
id|ei_ibp
c_func
(paren
id|base
op_plus
id|EN0_CRDAHI
)paren
suffix:semicolon
id|rdlo
op_assign
id|ei_ibp
c_func
(paren
id|base
op_plus
id|EN0_CRDALO
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|base
op_plus
id|E8390_CMD
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
r_int
id|nrdhi
suffix:semicolon
r_int
r_int
id|nrdlo
suffix:semicolon
id|nrdhi
op_assign
id|ei_ibp
c_func
(paren
id|base
op_plus
id|EN0_CRDAHI
)paren
suffix:semicolon
id|nrdlo
op_assign
id|ei_ibp
c_func
(paren
id|base
op_plus
id|EN0_CRDALO
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rdhi
op_ne
id|nrdhi
)paren
op_logical_or
(paren
id|rdlo
op_ne
id|nrdlo
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
macro_line|#else
macro_line|#ifdef OAKNET_RWFIX
multiline_comment|/*&n;&t; * Handle the read-before-write bug the same way as the&n;&t; * Crynwr packet driver -- the Nat&squot;l Semi. method doesn&squot;t work.&n;&t; * Actually this doesn&squot;t always work either, but if you have&n;&t; * problems with your 83902 this is better than nothing!&n;&t; */
id|ei_obp
c_func
(paren
l_int|0x42
comma
id|base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
l_int|0x00
comma
id|base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
l_int|0x42
comma
id|base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
l_int|0x00
comma
id|base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|base
op_plus
id|E8390_CMD
)paren
suffix:semicolon
multiline_comment|/* Make certain that the dummy read has occurred. */
id|udelay
c_func
(paren
l_int|6
)paren
suffix:semicolon
macro_line|#endif
id|ei_obp
c_func
(paren
id|ENISR_RDC
comma
id|base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Now the normal output. */
id|ei_obp
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
l_int|0x00
comma
id|base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|ei_obp
c_func
(paren
id|start_page
comma
id|base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
macro_line|#endif /* 0/1 */
id|ei_obp
c_func
(paren
id|E8390_RWRITE
op_plus
id|E8390_START
comma
id|base
op_plus
id|E8390_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
(brace
id|ei_osw
c_func
(paren
id|E8390_BASE
op_plus
id|E8390_DATA
comma
id|buf
comma
id|count
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|ei_osb
c_func
(paren
id|E8390_BASE
op_plus
id|E8390_DATA
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
macro_line|#ifdef OAKNET_DISINT
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#endif
id|start
op_assign
id|jiffies
suffix:semicolon
macro_line|#ifdef OAKNET_HEADCHECK
multiline_comment|/*&n;&t; * This was for the ALPHA version only, but enough people have&n;&t; * been encountering problems so it is still here.&n;&t; */
(brace
multiline_comment|/* DMA termination address check... */
r_int
id|addr
comma
id|tries
op_assign
l_int|20
suffix:semicolon
r_do
(brace
r_int
id|high
op_assign
id|ei_ibp
c_func
(paren
id|base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
r_int
id|low
op_assign
id|ei_ibp
c_func
(paren
id|base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|addr
op_assign
(paren
id|high
op_lshift
l_int|8
)paren
op_plus
id|low
suffix:semicolon
r_if
c_cond
(paren
(paren
id|start_page
op_lshift
l_int|8
)paren
op_plus
id|count
op_eq
id|addr
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|tries
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tries
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Tx packet transfer address mismatch,&quot;
l_string|&quot;%#4.4x (expected) vs. %#4.4x (actual).&bslash;n&quot;
comma
id|dev-&gt;name
comma
(paren
id|start_page
op_lshift
l_int|8
)paren
op_plus
id|count
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retries
op_increment
op_eq
l_int|0
)paren
r_goto
id|retry
suffix:semicolon
)brace
)brace
macro_line|#endif
r_while
c_loop
(paren
(paren
id|ei_ibp
c_func
(paren
id|base
op_plus
id|EN0_ISR
)paren
op_amp
id|ENISR_RDC
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|jiffies
op_minus
id|start
OG
id|OAKNET_WAIT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: timeout waiting for Tx RDC.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|oaknet_reset_8390
c_func
(paren
id|dev
)paren
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
id|TRUE
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|ei_obp
c_func
(paren
id|ENISR_RDC
comma
id|base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
)brace
multiline_comment|/*&n; * static void oaknet_dma_error()&n; *&n; * Description:&n; *   This routine prints out a last-ditch informative message to the console&n; *   indicating that a DMA error occurred. If you see this, it&squot;s the last&n; *   thing you&squot;ll see.&n; *&n; * Input(s):&n; *  *dev  - Pointer to the device structure for this driver.&n; *  *name - Informative text (e.g. function name) indicating where the&n; *          DMA error occurred.&n; *&n; * Output(s):&n; *   N/A&n; *&n; * Returns:&n; *   N/A&n; *&n; */
r_static
r_void
DECL|function|oaknet_dma_error
id|oaknet_dma_error
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_const
r_char
op_star
id|name
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;%s: DMAing conflict in %s.&quot;
l_string|&quot;[DMAstat:%d][irqlock:%d][intr:%ld]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
comma
id|dev-&gt;interrupt
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Oak Ethernet module load interface.&n; */
DECL|function|oaknet_init_module
r_static
r_int
id|__init
id|oaknet_init_module
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|oaknet_devs
op_ne
l_int|NULL
)paren
r_return
(paren
op_minus
id|EBUSY
)paren
suffix:semicolon
r_return
(paren
id|oaknet_init
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Oak Ethernet module unload interface.&n; */
DECL|function|oaknet_cleanup_module
r_static
r_void
id|__exit
id|oaknet_cleanup_module
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|oaknet_devs
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|oaknet_devs-&gt;priv
op_ne
l_int|NULL
)paren
(brace
r_int
id|ioaddr
op_assign
id|oaknet_devs-&gt;base_addr
suffix:semicolon
r_void
op_star
id|priv
op_assign
id|oaknet_devs-&gt;priv
suffix:semicolon
id|free_irq
c_func
(paren
id|oaknet_devs-&gt;irq
comma
id|oaknet_devs
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ioaddr
comma
id|OAKNET_IO_SIZE
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|oaknet_dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert to loop once driver supports multiple devices. */
id|kfree
c_func
(paren
id|oaknet_devs
)paren
suffix:semicolon
)brace
DECL|variable|oaknet_init_module
id|module_init
c_func
(paren
id|oaknet_init_module
)paren
suffix:semicolon
DECL|variable|oaknet_cleanup_module
id|module_exit
c_func
(paren
id|oaknet_cleanup_module
)paren
suffix:semicolon
eof
