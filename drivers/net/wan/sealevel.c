multiline_comment|/*&n; *&t;Sealevel Systems 4021 driver.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;(c) Copyright 1999, 2001 Alan Cox&n; *&t;(c) Copyright 2001 Red Hat Inc.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;net/syncppp.h&gt;
macro_line|#include &quot;z85230.h&quot;
DECL|struct|slvl_device
r_struct
id|slvl_device
(brace
DECL|member|if_ptr
r_void
op_star
id|if_ptr
suffix:semicolon
multiline_comment|/* General purpose pointer (used by SPPP) */
DECL|member|chan
r_struct
id|z8530_channel
op_star
id|chan
suffix:semicolon
DECL|member|pppdev
r_struct
id|ppp_device
id|pppdev
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|slvl_board
r_struct
id|slvl_board
(brace
DECL|member|dev
r_struct
id|slvl_device
op_star
id|dev
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|board
r_struct
id|z8530_dev
id|board
suffix:semicolon
DECL|member|iobase
r_int
id|iobase
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Network driver support routines&n; */
multiline_comment|/*&n; *&t;Frame receive. Simple for our card as we do sync ppp and there&n; *&t;is no funny garbage involved&n; */
DECL|function|sealevel_input
r_static
r_void
id|sealevel_input
c_func
(paren
r_struct
id|z8530_channel
op_star
id|c
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
multiline_comment|/* Drop the CRC - it&squot;s not a good idea to try and negotiate it ;) */
id|skb_trim
c_func
(paren
id|skb
comma
id|skb-&gt;len
op_minus
l_int|2
)paren
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_WAN_PPP
)paren
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb-&gt;dev
op_assign
id|c-&gt;netdevice
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Send it to the PPP layer. We don&squot;t have time to process&n;&t; *&t;it right now.&n;&t; */
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|c-&gt;netdevice-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;We&squot;ve been placed in the UP state&n; */
DECL|function|sealevel_open
r_static
r_int
id|sealevel_open
c_func
(paren
r_struct
id|net_device
op_star
id|d
)paren
(brace
r_struct
id|slvl_device
op_star
id|slvl
op_assign
id|d-&gt;priv
suffix:semicolon
r_int
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|unit
op_assign
id|slvl-&gt;channel
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Link layer up. &n;&t; */
r_switch
c_cond
(paren
id|unit
)paren
(brace
r_case
l_int|0
suffix:colon
id|err
op_assign
id|z8530_sync_dma_open
c_func
(paren
id|d
comma
id|slvl-&gt;chan
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|err
op_assign
id|z8530_sync_open
c_func
(paren
id|d
comma
id|slvl-&gt;chan
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Begin PPP&n;&t; */
id|err
op_assign
id|sppp_open
c_func
(paren
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_switch
c_cond
(paren
id|unit
)paren
(brace
r_case
l_int|0
suffix:colon
id|z8530_sync_dma_close
c_func
(paren
id|d
comma
id|slvl-&gt;chan
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|z8530_sync_close
c_func
(paren
id|d
comma
id|slvl-&gt;chan
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
id|slvl-&gt;chan-&gt;rx_function
op_assign
id|sealevel_input
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Go go go&n;&t; */
id|netif_start_queue
c_func
(paren
id|d
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sealevel_close
r_static
r_int
id|sealevel_close
c_func
(paren
r_struct
id|net_device
op_star
id|d
)paren
(brace
r_struct
id|slvl_device
op_star
id|slvl
op_assign
id|d-&gt;priv
suffix:semicolon
r_int
id|unit
op_assign
id|slvl-&gt;channel
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Discard new frames&n;&t; */
id|slvl-&gt;chan-&gt;rx_function
op_assign
id|z8530_null_rx
suffix:semicolon
multiline_comment|/*&n;&t; *&t;PPP off&n;&t; */
id|sppp_close
c_func
(paren
id|d
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Link layer down&n;&t; */
id|netif_stop_queue
c_func
(paren
id|d
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|unit
)paren
(brace
r_case
l_int|0
suffix:colon
id|z8530_sync_dma_close
c_func
(paren
id|d
comma
id|slvl-&gt;chan
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|z8530_sync_close
c_func
(paren
id|d
comma
id|slvl-&gt;chan
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sealevel_ioctl
r_static
r_int
id|sealevel_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|d
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
id|cmd
)paren
(brace
multiline_comment|/* struct slvl_device *slvl=d-&gt;priv;&n;&t;   z8530_ioctl(d,&amp;slvl-&gt;sync.chanA,ifr,cmd) */
r_return
id|sppp_do_ioctl
c_func
(paren
id|d
comma
id|ifr
comma
id|cmd
)paren
suffix:semicolon
)brace
DECL|function|sealevel_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|sealevel_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|d
)paren
(brace
r_struct
id|slvl_device
op_star
id|slvl
op_assign
id|d-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|slvl
)paren
(brace
r_return
id|z8530_get_stats
c_func
(paren
id|slvl-&gt;chan
)paren
suffix:semicolon
)brace
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Passed PPP frames, fire them downwind.&n; */
DECL|function|sealevel_queue_xmit
r_static
r_int
id|sealevel_queue_xmit
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
id|d
)paren
(brace
r_struct
id|slvl_device
op_star
id|slvl
op_assign
id|d-&gt;priv
suffix:semicolon
r_return
id|z8530_queue_xmit
c_func
(paren
id|slvl-&gt;chan
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|sealevel_neigh_setup
r_static
r_int
id|sealevel_neigh_setup
c_func
(paren
r_struct
id|neighbour
op_star
id|n
)paren
(brace
r_if
c_cond
(paren
id|n-&gt;nud_state
op_eq
id|NUD_NONE
)paren
(brace
id|n-&gt;ops
op_assign
op_amp
id|arp_broken_ops
suffix:semicolon
id|n-&gt;output
op_assign
id|n-&gt;ops-&gt;output
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sealevel_neigh_setup_dev
r_static
r_int
id|sealevel_neigh_setup_dev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|neigh_parms
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;tbl-&gt;family
op_eq
id|AF_INET
)paren
(brace
id|p-&gt;neigh_setup
op_assign
id|sealevel_neigh_setup
suffix:semicolon
id|p-&gt;ucast_probes
op_assign
l_int|0
suffix:semicolon
id|p-&gt;mcast_probes
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sealevel_attach
r_static
r_int
id|sealevel_attach
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|slvl_device
op_star
id|sv
op_assign
id|dev-&gt;priv
suffix:semicolon
id|sppp_attach
c_func
(paren
op_amp
id|sv-&gt;pppdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sealevel_detach
r_static
r_void
id|sealevel_detach
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|sppp_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|slvl_setup
r_static
r_void
id|slvl_setup
c_func
(paren
r_struct
id|net_device
op_star
id|d
)paren
(brace
id|d-&gt;open
op_assign
id|sealevel_open
suffix:semicolon
id|d-&gt;stop
op_assign
id|sealevel_close
suffix:semicolon
id|d-&gt;init
op_assign
id|sealevel_attach
suffix:semicolon
id|d-&gt;uninit
op_assign
id|sealevel_detach
suffix:semicolon
id|d-&gt;hard_start_xmit
op_assign
id|sealevel_queue_xmit
suffix:semicolon
id|d-&gt;get_stats
op_assign
id|sealevel_get_stats
suffix:semicolon
id|d-&gt;set_multicast_list
op_assign
l_int|NULL
suffix:semicolon
id|d-&gt;do_ioctl
op_assign
id|sealevel_ioctl
suffix:semicolon
id|d-&gt;neigh_setup
op_assign
id|sealevel_neigh_setup_dev
suffix:semicolon
id|d-&gt;set_mac_address
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|slvl_alloc
r_static
r_inline
r_struct
id|slvl_device
op_star
id|slvl_alloc
c_func
(paren
r_int
id|iobase
comma
r_int
id|irq
)paren
(brace
r_struct
id|net_device
op_star
id|d
suffix:semicolon
r_struct
id|slvl_device
op_star
id|sv
suffix:semicolon
id|d
op_assign
id|alloc_netdev
c_func
(paren
r_sizeof
(paren
r_struct
id|slvl_device
)paren
comma
l_string|&quot;hdlc%d&quot;
comma
id|slvl_setup
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
r_return
l_int|NULL
suffix:semicolon
id|sv
op_assign
id|d-&gt;priv
suffix:semicolon
id|sv-&gt;if_ptr
op_assign
op_amp
id|sv-&gt;pppdev
suffix:semicolon
id|sv-&gt;pppdev.dev
op_assign
id|d
suffix:semicolon
id|d-&gt;base_addr
op_assign
id|iobase
suffix:semicolon
id|d-&gt;irq
op_assign
id|irq
suffix:semicolon
r_return
id|sv
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Allocate and setup Sealevel board.&n; */
DECL|function|slvl_init
r_static
id|__init
r_struct
id|slvl_board
op_star
id|slvl_init
c_func
(paren
r_int
id|iobase
comma
r_int
id|irq
comma
r_int
id|txdma
comma
r_int
id|rxdma
comma
r_int
id|slow
)paren
(brace
r_struct
id|z8530_dev
op_star
id|dev
suffix:semicolon
r_struct
id|slvl_board
op_star
id|b
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Get the needed I/O space&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|iobase
comma
l_int|8
comma
l_string|&quot;Sealevel 4021&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sealevel: I/O 0x%X already in use.&bslash;n&quot;
comma
id|iobase
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|b
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|slvl_board
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b
)paren
(brace
r_goto
id|fail3
suffix:semicolon
)brace
id|memset
c_func
(paren
id|b
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|b
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|b-&gt;dev
(braket
l_int|0
)braket
op_assign
id|slvl_alloc
c_func
(paren
id|iobase
comma
id|irq
)paren
)paren
)paren
r_goto
id|fail2
suffix:semicolon
id|b-&gt;dev
(braket
l_int|0
)braket
op_member_access_from_pointer
id|chan
op_assign
op_amp
id|b-&gt;board.chanA
suffix:semicolon
id|b-&gt;dev
(braket
l_int|0
)braket
op_member_access_from_pointer
id|channel
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|b-&gt;dev
(braket
l_int|1
)braket
op_assign
id|slvl_alloc
c_func
(paren
id|iobase
comma
id|irq
)paren
)paren
)paren
r_goto
id|fail1_0
suffix:semicolon
id|b-&gt;dev
(braket
l_int|1
)braket
op_member_access_from_pointer
id|chan
op_assign
op_amp
id|b-&gt;board.chanB
suffix:semicolon
id|b-&gt;dev
(braket
l_int|1
)braket
op_member_access_from_pointer
id|channel
op_assign
l_int|1
suffix:semicolon
id|dev
op_assign
op_amp
id|b-&gt;board
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Stuff in the I/O addressing&n;&t; */
id|dev-&gt;active
op_assign
l_int|0
suffix:semicolon
id|b-&gt;iobase
op_assign
id|iobase
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Select 8530 delays for the old board&n;&t; */
r_if
c_cond
(paren
id|slow
)paren
(brace
id|iobase
op_or_assign
id|Z8530_PORT_SLEEP
suffix:semicolon
)brace
id|dev-&gt;chanA.ctrlio
op_assign
id|iobase
op_plus
l_int|1
suffix:semicolon
id|dev-&gt;chanA.dataio
op_assign
id|iobase
suffix:semicolon
id|dev-&gt;chanB.ctrlio
op_assign
id|iobase
op_plus
l_int|3
suffix:semicolon
id|dev-&gt;chanB.dataio
op_assign
id|iobase
op_plus
l_int|2
suffix:semicolon
id|dev-&gt;chanA.irqs
op_assign
op_amp
id|z8530_nop
suffix:semicolon
id|dev-&gt;chanB.irqs
op_assign
op_amp
id|z8530_nop
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Assert DTR enable DMA&n;&t; */
id|outb
c_func
(paren
l_int|3
op_or
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
id|b-&gt;iobase
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* We want a fast IRQ for this device. Actually we&squot;d like an even faster&n;&t;   IRQ ;) - This is one driver RtLinux is made for */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
op_amp
id|z8530_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;SeaLevel&quot;
comma
id|dev
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sealevel: IRQ %d already in use.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_goto
id|fail1_1
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|dev-&gt;chanA
dot
r_private
op_assign
op_amp
id|b-&gt;dev
(braket
l_int|0
)braket
suffix:semicolon
id|dev-&gt;chanB
dot
r_private
op_assign
op_amp
id|b-&gt;dev
(braket
l_int|1
)braket
suffix:semicolon
id|dev-&gt;chanA.netdevice
op_assign
id|b-&gt;dev
(braket
l_int|0
)braket
op_member_access_from_pointer
id|pppdev.dev
suffix:semicolon
id|dev-&gt;chanB.netdevice
op_assign
id|b-&gt;dev
(braket
l_int|1
)braket
op_member_access_from_pointer
id|pppdev.dev
suffix:semicolon
id|dev-&gt;chanA.dev
op_assign
id|dev
suffix:semicolon
id|dev-&gt;chanB.dev
op_assign
id|dev
suffix:semicolon
id|dev-&gt;chanA.txdma
op_assign
l_int|3
suffix:semicolon
id|dev-&gt;chanA.rxdma
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|dev-&gt;chanA.txdma
comma
l_string|&quot;SeaLevel (TX)&quot;
)paren
op_ne
l_int|0
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|dev-&gt;chanA.rxdma
comma
l_string|&quot;SeaLevel (RX)&quot;
)paren
op_ne
l_int|0
)paren
(brace
r_goto
id|dmafail
suffix:semicolon
)brace
id|disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Begin normal initialise&n;&t; */
r_if
c_cond
(paren
id|z8530_init
c_func
(paren
id|dev
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Z8530 series device not found.&bslash;n&quot;
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_goto
id|dmafail2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
id|Z85C30
)paren
(brace
id|z8530_channel_load
c_func
(paren
op_amp
id|dev-&gt;chanA
comma
id|z8530_hdlc_kilostream
)paren
suffix:semicolon
id|z8530_channel_load
c_func
(paren
op_amp
id|dev-&gt;chanB
comma
id|z8530_hdlc_kilostream
)paren
suffix:semicolon
)brace
r_else
(brace
id|z8530_channel_load
c_func
(paren
op_amp
id|dev-&gt;chanA
comma
id|z8530_hdlc_kilostream_85230
)paren
suffix:semicolon
id|z8530_channel_load
c_func
(paren
op_amp
id|dev-&gt;chanB
comma
id|z8530_hdlc_kilostream_85230
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Now we can take the IRQ&n;&t; */
id|enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|b-&gt;dev
(braket
l_int|0
)braket
op_member_access_from_pointer
id|pppdev.dev
)paren
)paren
r_goto
id|dmafail2
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|b-&gt;dev
(braket
l_int|1
)braket
op_member_access_from_pointer
id|pppdev.dev
)paren
)paren
r_goto
id|fail_unit
suffix:semicolon
id|z8530_describe
c_func
(paren
id|dev
comma
l_string|&quot;I/O&quot;
comma
id|iobase
)paren
suffix:semicolon
id|dev-&gt;active
op_assign
l_int|1
suffix:semicolon
r_return
id|b
suffix:semicolon
id|fail_unit
suffix:colon
id|unregister_netdev
c_func
(paren
id|b-&gt;dev
(braket
l_int|0
)braket
op_member_access_from_pointer
id|pppdev.dev
)paren
suffix:semicolon
id|dmafail2
suffix:colon
id|free_dma
c_func
(paren
id|dev-&gt;chanA.rxdma
)paren
suffix:semicolon
id|dmafail
suffix:colon
id|free_dma
c_func
(paren
id|dev-&gt;chanA.txdma
)paren
suffix:semicolon
id|fail
suffix:colon
id|free_irq
c_func
(paren
id|irq
comma
id|dev
)paren
suffix:semicolon
id|fail1_1
suffix:colon
id|free_netdev
c_func
(paren
id|b-&gt;dev
(braket
l_int|1
)braket
op_member_access_from_pointer
id|pppdev.dev
)paren
suffix:semicolon
id|fail1_0
suffix:colon
id|free_netdev
c_func
(paren
id|b-&gt;dev
(braket
l_int|0
)braket
op_member_access_from_pointer
id|pppdev.dev
)paren
suffix:semicolon
id|fail2
suffix:colon
id|kfree
c_func
(paren
id|b
)paren
suffix:semicolon
id|fail3
suffix:colon
id|release_region
c_func
(paren
id|iobase
comma
l_int|8
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|slvl_shutdown
r_static
r_void
id|__exit
id|slvl_shutdown
c_func
(paren
r_struct
id|slvl_board
op_star
id|b
)paren
(brace
r_int
id|u
suffix:semicolon
id|z8530_shutdown
c_func
(paren
op_amp
id|b-&gt;board
)paren
suffix:semicolon
r_for
c_loop
(paren
id|u
op_assign
l_int|0
suffix:semicolon
id|u
OL
l_int|2
suffix:semicolon
id|u
op_increment
)paren
(brace
r_struct
id|net_device
op_star
id|d
op_assign
id|b-&gt;dev
(braket
id|u
)braket
op_member_access_from_pointer
id|pppdev.dev
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|d
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
id|free_irq
c_func
(paren
id|b-&gt;board.irq
comma
op_amp
id|b-&gt;board
)paren
suffix:semicolon
id|free_dma
c_func
(paren
id|b-&gt;board.chanA.rxdma
)paren
suffix:semicolon
id|free_dma
c_func
(paren
id|b-&gt;board.chanA.txdma
)paren
suffix:semicolon
multiline_comment|/* DMA off on the card, drop DTR */
id|outb
c_func
(paren
l_int|0
comma
id|b-&gt;iobase
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|b-&gt;iobase
comma
l_int|8
)paren
suffix:semicolon
)brace
DECL|variable|io
r_static
r_int
id|io
op_assign
l_int|0x238
suffix:semicolon
DECL|variable|txdma
r_static
r_int
id|txdma
op_assign
l_int|1
suffix:semicolon
DECL|variable|rxdma
r_static
r_int
id|rxdma
op_assign
l_int|3
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
op_assign
l_int|5
suffix:semicolon
DECL|variable|slow
r_static
r_int
id|slow
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;The I/O base of the Sealevel card&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|txdma
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|txdma
comma
l_string|&quot;Transmit DMA channel&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|rxdma
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|rxdma
comma
l_string|&quot;Receive DMA channel&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;The interrupt line setting for the SeaLevel card&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|slow
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|slow
comma
l_string|&quot;Set this for an older Sealevel card such as the 4012&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Alan Cox&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Modular driver for the SeaLevel 4021&quot;
)paren
suffix:semicolon
DECL|variable|slvl_unit
r_static
r_struct
id|slvl_board
op_star
id|slvl_unit
suffix:semicolon
DECL|function|slvl_init_module
r_static
r_int
id|__init
id|slvl_init_module
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SeaLevel Z85230 Synchronous Driver v 0.02.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;(c) Copyright 1998, Building Number Three Ltd.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|slvl_unit
op_assign
id|slvl_init
c_func
(paren
id|io
comma
id|irq
comma
id|txdma
comma
id|rxdma
comma
id|slow
)paren
suffix:semicolon
r_return
id|slvl_unit
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|slvl_cleanup_module
r_static
r_void
id|__exit
id|slvl_cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|slvl_unit
)paren
(brace
id|slvl_shutdown
c_func
(paren
id|slvl_unit
)paren
suffix:semicolon
)brace
)brace
DECL|variable|slvl_init_module
id|module_init
c_func
(paren
id|slvl_init_module
)paren
suffix:semicolon
DECL|variable|slvl_cleanup_module
id|module_exit
c_func
(paren
id|slvl_cleanup_module
)paren
suffix:semicolon
eof
