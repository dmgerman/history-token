multiline_comment|/*&n; * sonic.c&n; *&n; * (C) 1996,1998 by Thomas Bogendoerfer (tsbogend@alpha.franken.de)&n; * &n; * This driver is based on work from Andreas Busse, but most of&n; * the code is rewritten.&n; * &n; * (C) 1995 by Andreas Busse (andy@waldorf-gmbh.de)&n; *&n; *    Core code included by system sonic drivers&n; */
multiline_comment|/*&n; * Sources: Olivetti M700-10 Risc Personal Computer hardware handbook,&n; * National Semiconductors data sheet for the DP83932B Sonic Ethernet&n; * controller, and the files &quot;8390.c&quot; and &quot;skeleton.c&quot; in this directory.&n; */
multiline_comment|/*&n; * Open/initialize the SONIC controller.&n; *&n; * This routine should set everything up anew at each open, even&n; *  registers that &quot;should&quot; only need to be set once at boot, so that&n; *  there is non-reboot way to recover if something goes wrong.&n; */
DECL|function|sonic_open
r_static
r_int
id|sonic_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_open: initializing sonic driver.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t need to deal with auto-irq stuff since we&n;&t; * hardwire the sonic interrupt.&n;&t; */
multiline_comment|/*&n; * XXX Horrible work around:  We install sonic_interrupt as fast interrupt.&n; * This means that during execution of the handler interrupt are disabled&n; * covering another bug otherwise corrupting data.  This doesn&squot;t mean&n; * this glue works ok under all situations.&n; */
singleline_comment|//    if (sonic_request_irq(dev-&gt;irq, &amp;sonic_interrupt, 0, &quot;sonic&quot;, dev)) {
r_if
c_cond
(paren
id|sonic_request_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|sonic_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;sonic&quot;
comma
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s: unable to get IRQ %d .&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Initialize the SONIC&n;&t; */
id|sonic_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_open: Initialization done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Close the SONIC device&n; */
DECL|function|sonic_close
r_static
r_int
id|sonic_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_close&bslash;n&quot;
)paren
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * stop the SONIC, disable interrupts&n;&t; */
id|SONIC_WRITE
c_func
(paren
id|SONIC_ISR
comma
l_int|0x7fff
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_IMR
comma
l_int|0
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
id|SONIC_CR_RST
)paren
suffix:semicolon
id|sonic_free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* release the IRQ */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sonic_tx_timeout
r_static
r_void
id|sonic_tx_timeout
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|sonic_local
op_star
id|lp
op_assign
(paren
r_struct
id|sonic_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: transmit timed out.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* Try to restart the adaptor. */
id|sonic_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|lp-&gt;stats.tx_errors
op_increment
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * transmit packet&n; */
DECL|function|sonic_send_packet
r_static
r_int
id|sonic_send_packet
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
(brace
r_struct
id|sonic_local
op_star
id|lp
op_assign
(paren
r_struct
id|sonic_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
r_int
id|laddr
suffix:semicolon
r_int
id|entry
comma
id|length
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_send_packet: skb=%p, dev=%p&bslash;n&quot;
comma
id|skb
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Map the packet data into the logical DMA address space&n;&t; */
r_if
c_cond
(paren
(paren
id|laddr
op_assign
id|vdma_alloc
c_func
(paren
id|CPHYSADDR
c_func
(paren
id|skb-&gt;data
)paren
comma
id|skb-&gt;len
)paren
)paren
op_eq
op_complement
l_int|0UL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: no VDMA entry for transmit available.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|entry
op_assign
id|lp-&gt;cur_tx
op_amp
id|SONIC_TDS_MASK
suffix:semicolon
id|lp-&gt;tx_laddr
(braket
id|entry
)braket
op_assign
id|laddr
suffix:semicolon
id|lp-&gt;tx_skb
(braket
id|entry
)braket
op_assign
id|skb
suffix:semicolon
id|length
op_assign
(paren
id|skb-&gt;len
OL
id|ETH_ZLEN
)paren
ques
c_cond
id|ETH_ZLEN
suffix:colon
id|skb-&gt;len
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup the transmit descriptor and issue the transmit command.&n;&t; */
id|lp-&gt;tda
(braket
id|entry
)braket
dot
id|tx_status
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* clear status */
id|lp-&gt;tda
(braket
id|entry
)braket
dot
id|tx_frag_count
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* single fragment */
id|lp-&gt;tda
(braket
id|entry
)braket
dot
id|tx_pktsize
op_assign
id|length
suffix:semicolon
multiline_comment|/* length of packet */
id|lp-&gt;tda
(braket
id|entry
)braket
dot
id|tx_frag_ptr_l
op_assign
id|laddr
op_amp
l_int|0xffff
suffix:semicolon
id|lp-&gt;tda
(braket
id|entry
)braket
dot
id|tx_frag_ptr_h
op_assign
id|laddr
op_rshift
l_int|16
suffix:semicolon
id|lp-&gt;tda
(braket
id|entry
)braket
dot
id|tx_frag_size
op_assign
id|length
suffix:semicolon
id|lp-&gt;cur_tx
op_increment
suffix:semicolon
id|lp-&gt;stats.tx_bytes
op_add_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_send_packet: issueing Tx command&bslash;n&quot;
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
id|SONIC_CR_TXP
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;cur_tx
OL
id|lp-&gt;dirty_tx
op_plus
id|SONIC_NUM_TDS
)paren
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
id|lp-&gt;tx_full
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The typical workload of the driver:&n; * Handle the network interface interrupts.&n; */
DECL|function|sonic_interrupt
r_static
id|irqreturn_t
id|sonic_interrupt
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
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|dev_id
suffix:semicolon
r_int
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_struct
id|sonic_local
op_star
id|lp
suffix:semicolon
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sonic_interrupt: irq %d for unknown device.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
id|lp
op_assign
(paren
r_struct
id|sonic_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|status
op_assign
id|SONIC_READ
c_func
(paren
id|SONIC_ISR
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_ISR
comma
l_int|0x7fff
)paren
suffix:semicolon
multiline_comment|/* clear all bits */
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_interrupt: ISR=%x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_INT_PKTRX
)paren
(brace
id|sonic_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* got packet(s) */
)brace
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_INT_TXDN
)paren
(brace
r_int
id|dirty_tx
op_assign
id|lp-&gt;dirty_tx
suffix:semicolon
r_while
c_loop
(paren
id|dirty_tx
OL
id|lp-&gt;cur_tx
)paren
(brace
r_int
id|entry
op_assign
id|dirty_tx
op_amp
id|SONIC_TDS_MASK
suffix:semicolon
r_int
id|status
op_assign
id|lp-&gt;tda
(braket
id|entry
)braket
dot
id|tx_status
suffix:semicolon
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|3
)paren
id|printk
(paren
l_string|&quot;sonic_interrupt: status %d, cur_tx %d, dirty_tx %d&bslash;n&quot;
comma
id|status
comma
id|lp-&gt;cur_tx
comma
id|lp-&gt;dirty_tx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
l_int|0
)paren
(brace
multiline_comment|/* It still hasn&squot;t been Txed, kick the sonic again */
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
id|SONIC_CR_TXP
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* put back EOL and free descriptor */
id|lp-&gt;tda
(braket
id|entry
)braket
dot
id|tx_frag_count
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tda
(braket
id|entry
)braket
dot
id|tx_status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0001
)paren
id|lp-&gt;stats.tx_packets
op_increment
suffix:semicolon
r_else
(brace
id|lp-&gt;stats.tx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0642
)paren
id|lp-&gt;stats.tx_aborted_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0180
)paren
id|lp-&gt;stats.tx_carrier_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0020
)paren
id|lp-&gt;stats.tx_window_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0004
)paren
id|lp-&gt;stats.tx_fifo_errors
op_increment
suffix:semicolon
)brace
multiline_comment|/* We must free the original skb */
r_if
c_cond
(paren
id|lp-&gt;tx_skb
(braket
id|entry
)braket
)paren
(brace
id|dev_kfree_skb_irq
c_func
(paren
id|lp-&gt;tx_skb
(braket
id|entry
)braket
)paren
suffix:semicolon
id|lp-&gt;tx_skb
(braket
id|entry
)braket
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* and the VDMA address */
id|vdma_free
c_func
(paren
id|lp-&gt;tx_laddr
(braket
id|entry
)braket
)paren
suffix:semicolon
id|dirty_tx
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lp-&gt;tx_full
op_logical_and
id|dirty_tx
op_plus
id|SONIC_NUM_TDS
OG
id|lp-&gt;cur_tx
op_plus
l_int|2
)paren
(brace
multiline_comment|/* The ring is no longer full, clear tbusy. */
id|lp-&gt;tx_full
op_assign
l_int|0
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|lp-&gt;dirty_tx
op_assign
id|dirty_tx
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * check error conditions&n;&t; */
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_INT_RFO
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: receive fifo underrun&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|lp-&gt;stats.rx_fifo_errors
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_INT_RDE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: receive descriptors exhausted&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|lp-&gt;stats.rx_dropped
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_INT_RBE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: receive buffer exhausted&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|lp-&gt;stats.rx_dropped
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_INT_RBAE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: receive buffer area exhausted&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|lp-&gt;stats.rx_dropped
op_increment
suffix:semicolon
)brace
multiline_comment|/* counter overruns; all counters are 16bit wide */
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_INT_FAE
)paren
id|lp-&gt;stats.rx_frame_errors
op_add_assign
l_int|65536
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_INT_CRC
)paren
id|lp-&gt;stats.rx_crc_errors
op_add_assign
l_int|65536
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_INT_MP
)paren
id|lp-&gt;stats.rx_missed_errors
op_add_assign
l_int|65536
suffix:semicolon
multiline_comment|/* transmit error */
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_INT_TXER
)paren
id|lp-&gt;stats.tx_errors
op_increment
suffix:semicolon
multiline_comment|/*&n;&t; * clear interrupt bits and return&n;&t; */
id|SONIC_WRITE
c_func
(paren
id|SONIC_ISR
comma
id|status
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * We have a good packet(s), get it/them out of the buffers.&n; */
DECL|function|sonic_rx
r_static
r_void
id|sonic_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_struct
id|sonic_local
op_star
id|lp
op_assign
(paren
r_struct
id|sonic_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|sonic_rd_t
op_star
id|rd
op_assign
op_amp
id|lp-&gt;rda
(braket
id|lp-&gt;cur_rx
op_amp
id|SONIC_RDS_MASK
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
r_while
c_loop
(paren
id|rd-&gt;in_use
op_eq
l_int|0
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|pkt_len
suffix:semicolon
r_int
r_char
op_star
id|pkt_ptr
suffix:semicolon
id|status
op_assign
id|rd-&gt;rx_status
suffix:semicolon
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot;status %x, cur_rx %d, cur_rra %x&bslash;n&quot;
comma
id|status
comma
id|lp-&gt;cur_rx
comma
id|lp-&gt;cur_rra
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_RCR_PRX
)paren
(brace
id|pkt_len
op_assign
id|rd-&gt;rx_pktlen
suffix:semicolon
id|pkt_ptr
op_assign
(paren
r_char
op_star
)paren
id|sonic_chiptomem
c_func
(paren
(paren
id|rd-&gt;rx_pktptr_h
op_lshift
l_int|16
)paren
op_plus
id|rd-&gt;rx_pktptr_l
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|3
)paren
id|printk
(paren
l_string|&quot;pktptr %p (rba %p) h:%x l:%x, bsize h:%x l:%x&bslash;n&quot;
comma
id|pkt_ptr
comma
id|lp-&gt;rba
comma
id|rd-&gt;rx_pktptr_h
comma
id|rd-&gt;rx_pktptr_l
comma
id|SONIC_READ
c_func
(paren
id|SONIC_RBWC1
)paren
comma
id|SONIC_READ
c_func
(paren
id|SONIC_RBWC0
)paren
)paren
suffix:semicolon
multiline_comment|/* Malloc up new buffer. */
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|pkt_len
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;%s: Memory squeeze, dropping packet.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|lp-&gt;stats.rx_dropped
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* 16 byte align */
id|skb_put
c_func
(paren
id|skb
comma
id|pkt_len
)paren
suffix:semicolon
multiline_comment|/* Make room */
id|eth_copy_and_sum
c_func
(paren
id|skb
comma
id|pkt_ptr
comma
id|pkt_len
comma
l_int|0
)paren
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* pass the packet to upper layers */
id|dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
id|lp-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|lp-&gt;stats.rx_bytes
op_add_assign
id|pkt_len
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This should only happen, if we enable accepting broken packets. */
id|lp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_RCR_FAER
)paren
id|lp-&gt;stats.rx_frame_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_RCR_CRCR
)paren
id|lp-&gt;stats.rx_crc_errors
op_increment
suffix:semicolon
)brace
id|rd-&gt;in_use
op_assign
l_int|1
suffix:semicolon
id|rd
op_assign
op_amp
id|lp-&gt;rda
(braket
(paren
op_increment
id|lp-&gt;cur_rx
)paren
op_amp
id|SONIC_RDS_MASK
)braket
suffix:semicolon
multiline_comment|/* now give back the buffer to the receive buffer area */
r_if
c_cond
(paren
id|status
op_amp
id|SONIC_RCR_LPKT
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * this was the last packet out of the current receice buffer&n;&t;&t;&t; * give the buffer back to the SONIC&n;&t;&t;&t; */
id|lp-&gt;cur_rra
op_add_assign
r_sizeof
(paren
id|sonic_rr_t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;cur_rra
OG
(paren
id|lp-&gt;rra_laddr
op_plus
(paren
id|SONIC_NUM_RRS
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|sonic_rr_t
)paren
)paren
)paren
id|lp-&gt;cur_rra
op_assign
id|lp-&gt;rra_laddr
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_RWP
comma
id|lp-&gt;cur_rra
op_amp
l_int|0xffff
)paren
suffix:semicolon
)brace
r_else
id|printk
(paren
l_string|&quot;%s: rx desc without RCR_LPKT. Shouldn&squot;t happen !?&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If any worth-while packets have been received, dev_rint()&n;&t; * has done a mark_bh(NET_BH) for us and will work on them&n;&t; * when we get to the bottom-half routine.&n;&t; */
)brace
multiline_comment|/*&n; * Get the current statistics.&n; * This may be called with the device open or closed.&n; */
DECL|function|sonic_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|sonic_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|sonic_local
op_star
id|lp
op_assign
(paren
r_struct
id|sonic_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
multiline_comment|/* read the tally counter from the SONIC and reset them */
id|lp-&gt;stats.rx_crc_errors
op_add_assign
id|SONIC_READ
c_func
(paren
id|SONIC_CRCT
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CRCT
comma
l_int|0xffff
)paren
suffix:semicolon
id|lp-&gt;stats.rx_frame_errors
op_add_assign
id|SONIC_READ
c_func
(paren
id|SONIC_FAET
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_FAET
comma
l_int|0xffff
)paren
suffix:semicolon
id|lp-&gt;stats.rx_missed_errors
op_add_assign
id|SONIC_READ
c_func
(paren
id|SONIC_MPT
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_MPT
comma
l_int|0xffff
)paren
suffix:semicolon
r_return
op_amp
id|lp-&gt;stats
suffix:semicolon
)brace
multiline_comment|/*&n; * Set or clear the multicast filter for this adaptor.&n; */
DECL|function|sonic_multicast_list
r_static
r_void
id|sonic_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|sonic_local
op_star
id|lp
op_assign
(paren
r_struct
id|sonic_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
r_int
id|rcr
suffix:semicolon
r_struct
id|dev_mc_list
op_star
id|dmi
op_assign
id|dev-&gt;mc_list
suffix:semicolon
r_int
r_char
op_star
id|addr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|rcr
op_assign
id|SONIC_READ
c_func
(paren
id|SONIC_RCR
)paren
op_amp
op_complement
(paren
id|SONIC_RCR_PRO
op_or
id|SONIC_RCR_AMC
)paren
suffix:semicolon
id|rcr
op_or_assign
id|SONIC_RCR_BRD
suffix:semicolon
multiline_comment|/* accept broadcast packets */
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_PROMISC
)paren
(brace
multiline_comment|/* set promiscuous mode */
id|rcr
op_or_assign
id|SONIC_RCR_PRO
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|dev-&gt;flags
op_amp
id|IFF_ALLMULTI
)paren
op_logical_or
(paren
id|dev-&gt;mc_count
OG
l_int|15
)paren
)paren
(brace
id|rcr
op_or_assign
id|SONIC_RCR_AMC
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
(paren
l_string|&quot;sonic_multicast_list: mc_count %d&bslash;n&quot;
comma
id|dev-&gt;mc_count
)paren
suffix:semicolon
id|lp-&gt;cda.cam_enable
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* always enable our own address */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|dev-&gt;mc_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|addr
op_assign
id|dmi-&gt;dmi_addr
suffix:semicolon
id|dmi
op_assign
id|dmi-&gt;next
suffix:semicolon
id|lp-&gt;cda.cam_desc
(braket
id|i
)braket
dot
id|cam_cap0
op_assign
id|addr
(braket
l_int|1
)braket
op_lshift
l_int|8
op_or
id|addr
(braket
l_int|0
)braket
suffix:semicolon
id|lp-&gt;cda.cam_desc
(braket
id|i
)braket
dot
id|cam_cap1
op_assign
id|addr
(braket
l_int|3
)braket
op_lshift
l_int|8
op_or
id|addr
(braket
l_int|2
)braket
suffix:semicolon
id|lp-&gt;cda.cam_desc
(braket
id|i
)braket
dot
id|cam_cap2
op_assign
id|addr
(braket
l_int|5
)braket
op_lshift
l_int|8
op_or
id|addr
(braket
l_int|4
)braket
suffix:semicolon
id|lp-&gt;cda.cam_enable
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
id|SONIC_WRITE
c_func
(paren
id|SONIC_CDC
comma
l_int|16
)paren
suffix:semicolon
multiline_comment|/* issue Load CAM command */
id|SONIC_WRITE
c_func
(paren
id|SONIC_CDP
comma
id|lp-&gt;cda_laddr
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
id|SONIC_CR_LCAM
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_multicast_list: setting RCR=%x&bslash;n&quot;
comma
id|rcr
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_RCR
comma
id|rcr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the SONIC ethernet controller.&n; */
DECL|function|sonic_init
r_static
r_int
id|sonic_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
r_int
id|cmd
suffix:semicolon
r_struct
id|sonic_local
op_star
id|lp
op_assign
(paren
r_struct
id|sonic_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
r_int
id|rra_start
suffix:semicolon
r_int
r_int
id|rra_end
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * put the Sonic into software-reset mode and&n;&t; * disable all interrupts&n;&t; */
id|SONIC_WRITE
c_func
(paren
id|SONIC_ISR
comma
l_int|0x7fff
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_IMR
comma
l_int|0
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
id|SONIC_CR_RST
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * clear software reset flag, disable receiver, clear and&n;&t; * enable interrupts, then completely initialize the SONIC&n;&t; */
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
l_int|0
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
id|SONIC_CR_RXDIS
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * initialize the receive resource area&n;&t; */
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_init: initialize receive resource area&bslash;n&quot;
)paren
suffix:semicolon
id|rra_start
op_assign
id|lp-&gt;rra_laddr
op_amp
l_int|0xffff
suffix:semicolon
id|rra_end
op_assign
(paren
id|rra_start
op_plus
(paren
id|SONIC_NUM_RRS
op_star
r_sizeof
(paren
id|sonic_rr_t
)paren
)paren
)paren
op_amp
l_int|0xffff
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
id|SONIC_NUM_RRS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|lp-&gt;rra
(braket
id|i
)braket
dot
id|rx_bufadr_l
op_assign
(paren
id|lp-&gt;rba_laddr
op_plus
id|i
op_star
id|SONIC_RBSIZE
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|lp-&gt;rra
(braket
id|i
)braket
dot
id|rx_bufadr_h
op_assign
(paren
id|lp-&gt;rba_laddr
op_plus
id|i
op_star
id|SONIC_RBSIZE
)paren
op_rshift
l_int|16
suffix:semicolon
id|lp-&gt;rra
(braket
id|i
)braket
dot
id|rx_bufsize_l
op_assign
id|SONIC_RBSIZE
op_rshift
l_int|1
suffix:semicolon
id|lp-&gt;rra
(braket
id|i
)braket
dot
id|rx_bufsize_h
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* initialize all RRA registers */
id|SONIC_WRITE
c_func
(paren
id|SONIC_RSA
comma
id|rra_start
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_REA
comma
id|rra_end
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_RRP
comma
id|rra_start
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_RWP
comma
id|rra_end
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_URRA
comma
id|lp-&gt;rra_laddr
op_rshift
l_int|16
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_EOBC
comma
(paren
id|SONIC_RBSIZE
op_minus
l_int|2
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|lp-&gt;cur_rra
op_assign
id|lp-&gt;rra_laddr
op_plus
(paren
id|SONIC_NUM_RRS
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|sonic_rr_t
)paren
suffix:semicolon
multiline_comment|/* load the resource pointers */
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_init: issueing RRRA command&bslash;n&quot;
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
id|SONIC_CR_RRRA
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
op_increment
OL
l_int|100
)paren
(brace
r_if
c_cond
(paren
id|SONIC_READ
c_func
(paren
id|SONIC_CMD
)paren
op_amp
id|SONIC_CR_RRRA
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_init: status=%x&bslash;n&quot;
comma
id|SONIC_READ
c_func
(paren
id|SONIC_CMD
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the receive descriptors so that they&n;&t; * become a circular linked list, ie. let the last&n;&t; * descriptor point to the first again.&n;&t; */
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_init: initialize receive descriptors&bslash;n&quot;
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
id|SONIC_NUM_RDS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|lp-&gt;rda
(braket
id|i
)braket
dot
id|rx_status
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;rda
(braket
id|i
)braket
dot
id|rx_pktlen
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;rda
(braket
id|i
)braket
dot
id|rx_pktptr_l
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;rda
(braket
id|i
)braket
dot
id|rx_pktptr_h
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;rda
(braket
id|i
)braket
dot
id|rx_seqno
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;rda
(braket
id|i
)braket
dot
id|in_use
op_assign
l_int|1
suffix:semicolon
id|lp-&gt;rda
(braket
id|i
)braket
dot
id|link
op_assign
id|lp-&gt;rda_laddr
op_plus
(paren
id|i
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
id|sonic_rd_t
)paren
suffix:semicolon
)brace
multiline_comment|/* fix last descriptor */
id|lp-&gt;rda
(braket
id|SONIC_NUM_RDS
op_minus
l_int|1
)braket
dot
id|link
op_assign
id|lp-&gt;rda_laddr
suffix:semicolon
id|lp-&gt;cur_rx
op_assign
l_int|0
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_URDA
comma
id|lp-&gt;rda_laddr
op_rshift
l_int|16
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CRDA
comma
id|lp-&gt;rda_laddr
op_amp
l_int|0xffff
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * initialize transmit descriptors&n;&t; */
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_init: initialize transmit descriptors&bslash;n&quot;
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
id|SONIC_NUM_TDS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|lp-&gt;tda
(braket
id|i
)braket
dot
id|tx_status
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tda
(braket
id|i
)braket
dot
id|tx_config
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tda
(braket
id|i
)braket
dot
id|tx_pktsize
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tda
(braket
id|i
)braket
dot
id|tx_frag_count
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tda
(braket
id|i
)braket
dot
id|link
op_assign
(paren
id|lp-&gt;tda_laddr
op_plus
(paren
id|i
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
id|sonic_td_t
)paren
)paren
op_or
id|SONIC_END_OF_LINKS
suffix:semicolon
)brace
id|lp-&gt;tda
(braket
id|SONIC_NUM_TDS
op_minus
l_int|1
)braket
dot
id|link
op_assign
(paren
id|lp-&gt;tda_laddr
op_amp
l_int|0xffff
)paren
op_or
id|SONIC_END_OF_LINKS
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_UTDA
comma
id|lp-&gt;tda_laddr
op_rshift
l_int|16
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CTDA
comma
id|lp-&gt;tda_laddr
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|lp-&gt;cur_tx
op_assign
id|lp-&gt;dirty_tx
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * put our own address to CAM desc[0]&n;&t; */
id|lp-&gt;cda.cam_desc
(braket
l_int|0
)braket
dot
id|cam_cap0
op_assign
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
op_lshift
l_int|8
op_or
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
suffix:semicolon
id|lp-&gt;cda.cam_desc
(braket
l_int|0
)braket
dot
id|cam_cap1
op_assign
id|dev-&gt;dev_addr
(braket
l_int|3
)braket
op_lshift
l_int|8
op_or
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
suffix:semicolon
id|lp-&gt;cda.cam_desc
(braket
l_int|0
)braket
dot
id|cam_cap2
op_assign
id|dev-&gt;dev_addr
(braket
l_int|5
)braket
op_lshift
l_int|8
op_or
id|dev-&gt;dev_addr
(braket
l_int|4
)braket
suffix:semicolon
id|lp-&gt;cda.cam_enable
op_assign
l_int|1
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|lp-&gt;cda.cam_desc
(braket
id|i
)braket
dot
id|cam_entry_pointer
op_assign
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * initialize CAM registers&n;&t; */
id|SONIC_WRITE
c_func
(paren
id|SONIC_CDP
comma
id|lp-&gt;cda_laddr
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CDC
comma
l_int|16
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * load the CAM&n;&t; */
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
id|SONIC_CR_LCAM
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
op_increment
OL
l_int|100
)paren
(brace
r_if
c_cond
(paren
id|SONIC_READ
c_func
(paren
id|SONIC_ISR
)paren
op_amp
id|SONIC_INT_LCD
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sonic_init: CMD=%x, ISR=%x&bslash;n&quot;
comma
id|SONIC_READ
c_func
(paren
id|SONIC_CMD
)paren
comma
id|SONIC_READ
c_func
(paren
id|SONIC_ISR
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * enable receiver, disable loopback&n;&t; * and enable all interrupts&n;&t; */
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
id|SONIC_CR_RXEN
op_or
id|SONIC_CR_STP
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_RCR
comma
id|SONIC_RCR_DEFAULT
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_TCR
comma
id|SONIC_TCR_DEFAULT
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_ISR
comma
l_int|0x7fff
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_IMR
comma
id|SONIC_IMR_DEFAULT
)paren
suffix:semicolon
id|cmd
op_assign
id|SONIC_READ
c_func
(paren
id|SONIC_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cmd
op_amp
id|SONIC_CR_RXEN
)paren
op_eq
l_int|0
op_logical_or
(paren
id|cmd
op_amp
id|SONIC_CR_STP
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_init: failed, status=%x&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;sonic_init: new status=%x&bslash;n&quot;
comma
id|SONIC_READ
c_func
(paren
id|SONIC_CMD
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
