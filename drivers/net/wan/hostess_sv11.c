multiline_comment|/*&n; *&t;Comtrol SV11 card driver&n; *&n; *&t;This is a slightly odd Z85230 synchronous driver. All you need to&n; *&t;know basically is&n; *&n; *&t;Its a genuine Z85230&n; *&n; *&t;It supports DMA using two DMA channels in SYNC mode. The driver doesn&squot;t&n; *&t;use these facilities&n; *&t;&n; *&t;The control port is at io+1, the data at io+3 and turning off the DMA&n; *&t;is done by writing 0 to io+4&n; *&n; *&t;The hardware does the bus handling to avoid the need for delays between&n; *&t;touching control registers.&n; *&n; *&t;Port B isnt wired (why - beats me)&n; */
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
DECL|variable|dma
r_static
r_int
id|dma
suffix:semicolon
DECL|struct|sv11_device
r_struct
id|sv11_device
(brace
DECL|member|if_ptr
r_void
op_star
id|if_ptr
suffix:semicolon
multiline_comment|/* General purpose pointer (used by SPPP) */
DECL|member|sync
r_struct
id|z8530_dev
id|sync
suffix:semicolon
DECL|member|netdev
r_struct
id|ppp_device
id|netdev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Network driver support routines&n; */
multiline_comment|/*&n; *&t;Frame receive. Simple for our card as we do sync ppp and there&n; *&t;is no funny garbage involved&n; */
DECL|function|hostess_input
r_static
r_void
id|hostess_input
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
multiline_comment|/* Drop the CRC - its not a good idea to try and negotiate it ;) */
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
id|__constant_htons
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
multiline_comment|/*&n;&t; *&t;Send it to the PPP layer. We dont have time to process&n;&t; *&t;it right now.&n;&t; */
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
DECL|function|hostess_open
r_static
r_int
id|hostess_open
c_func
(paren
r_struct
id|net_device
op_star
id|d
)paren
(brace
r_struct
id|sv11_device
op_star
id|sv11
op_assign
id|d-&gt;priv
suffix:semicolon
r_int
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Link layer up&n;&t; */
r_switch
c_cond
(paren
id|dma
)paren
(brace
r_case
l_int|0
suffix:colon
id|err
op_assign
id|z8530_sync_open
c_func
(paren
id|d
comma
op_amp
id|sv11-&gt;sync.chanA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|err
op_assign
id|z8530_sync_dma_open
c_func
(paren
id|d
comma
op_amp
id|sv11-&gt;sync.chanA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|err
op_assign
id|z8530_sync_txdma_open
c_func
(paren
id|d
comma
op_amp
id|sv11-&gt;sync.chanA
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
id|dma
)paren
(brace
r_case
l_int|0
suffix:colon
id|z8530_sync_close
c_func
(paren
id|d
comma
op_amp
id|sv11-&gt;sync.chanA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|z8530_sync_dma_close
c_func
(paren
id|d
comma
op_amp
id|sv11-&gt;sync.chanA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|z8530_sync_txdma_close
c_func
(paren
id|d
comma
op_amp
id|sv11-&gt;sync.chanA
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
id|sv11-&gt;sync.chanA.rx_function
op_assign
id|hostess_input
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Go go go&n;&t; */
id|netif_start_queue
c_func
(paren
id|d
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hostess_close
r_static
r_int
id|hostess_close
c_func
(paren
r_struct
id|net_device
op_star
id|d
)paren
(brace
r_struct
id|sv11_device
op_star
id|sv11
op_assign
id|d-&gt;priv
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Discard new frames&n;&t; */
id|sv11-&gt;sync.chanA.rx_function
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
id|dma
)paren
(brace
r_case
l_int|0
suffix:colon
id|z8530_sync_close
c_func
(paren
id|d
comma
op_amp
id|sv11-&gt;sync.chanA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|z8530_sync_dma_close
c_func
(paren
id|d
comma
op_amp
id|sv11-&gt;sync.chanA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|z8530_sync_txdma_close
c_func
(paren
id|d
comma
op_amp
id|sv11-&gt;sync.chanA
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hostess_ioctl
r_static
r_int
id|hostess_ioctl
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
multiline_comment|/* struct sv11_device *sv11=d-&gt;priv;&n;&t;   z8530_ioctl(d,&amp;sv11-&gt;sync.chanA,ifr,cmd) */
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
DECL|function|hostess_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|hostess_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|d
)paren
(brace
r_struct
id|sv11_device
op_star
id|sv11
op_assign
id|d-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|sv11
)paren
(brace
r_return
id|z8530_get_stats
c_func
(paren
op_amp
id|sv11-&gt;sync.chanA
)paren
suffix:semicolon
)brace
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Passed PPP frames, fire them downwind.&n; */
DECL|function|hostess_queue_xmit
r_static
r_int
id|hostess_queue_xmit
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
id|sv11_device
op_star
id|sv11
op_assign
id|d-&gt;priv
suffix:semicolon
r_return
id|z8530_queue_xmit
c_func
(paren
op_amp
id|sv11-&gt;sync.chanA
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|hostess_neigh_setup
r_static
r_int
id|hostess_neigh_setup
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
DECL|function|hostess_neigh_setup_dev
r_static
r_int
id|hostess_neigh_setup_dev
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
id|hostess_neigh_setup
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
multiline_comment|/*&n; *&t;Description block for a Comtrol Hostess SV11 card&n; */
DECL|function|sv11_init
r_static
r_struct
id|sv11_device
op_star
id|sv11_init
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
id|z8530_dev
op_star
id|dev
suffix:semicolon
r_struct
id|sv11_device
op_star
id|sv
suffix:semicolon
r_int
r_int
id|flags
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
l_string|&quot;Comtrol SV11&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hostess: I/O 0x%X already in use.&bslash;n&quot;
comma
id|iobase
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|sv
op_assign
(paren
r_struct
id|sv11_device
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sv11_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sv
)paren
(brace
r_goto
id|fail3
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sv
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sv
)paren
)paren
suffix:semicolon
id|sv-&gt;if_ptr
op_assign
op_amp
id|sv-&gt;netdev
suffix:semicolon
id|sv-&gt;netdev.dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|net_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sv-&gt;netdev.dev
)paren
(brace
r_goto
id|fail2
suffix:semicolon
)brace
id|dev
op_assign
op_amp
id|sv-&gt;sync
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Stuff in the I/O addressing&n;&t; */
id|dev-&gt;active
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;chanA.ctrlio
op_assign
id|iobase
op_plus
l_int|1
suffix:semicolon
id|dev-&gt;chanA.dataio
op_assign
id|iobase
op_plus
l_int|3
suffix:semicolon
id|dev-&gt;chanB.ctrlio
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev-&gt;chanB.dataio
op_assign
op_minus
l_int|1
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
id|outb
c_func
(paren
l_int|0
comma
id|iobase
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* DMA off */
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
l_string|&quot;Hostess SV/11&quot;
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
l_string|&quot;hostess: IRQ %d already in use.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_goto
id|fail1
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
id|sv
suffix:semicolon
id|dev-&gt;chanA.netdevice
op_assign
id|sv-&gt;netdev.dev
suffix:semicolon
id|dev-&gt;chanA.dev
op_assign
id|dev
suffix:semicolon
id|dev-&gt;chanB.dev
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|dma
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;You can have DMA off or 1 and 3 thats the lot&n;&t;&t; *&t;on the Comtrol.&n;&t;&t; */
id|dev-&gt;chanA.txdma
op_assign
l_int|3
suffix:semicolon
id|dev-&gt;chanA.rxdma
op_assign
l_int|1
suffix:semicolon
id|outb
c_func
(paren
l_int|0x03
op_or
l_int|0x08
comma
id|iobase
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* DMA on */
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|dev-&gt;chanA.txdma
comma
l_string|&quot;Hostess SV/11 (TX)&quot;
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
id|dma
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|dev-&gt;chanA.rxdma
comma
l_string|&quot;Hostess SV/11 (RX)&quot;
)paren
op_ne
l_int|0
)paren
(brace
r_goto
id|dmafail
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Kill our private IRQ line the hostess can end up chattering&n;&t;   until the configuration is set */
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
id|z8530_channel_load
c_func
(paren
op_amp
id|dev-&gt;chanB
comma
id|z8530_dead_port
)paren
suffix:semicolon
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
)brace
r_else
id|z8530_channel_load
c_func
(paren
op_amp
id|dev-&gt;chanA
comma
id|z8530_hdlc_kilostream_85230
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Now we can take the IRQ&n;&t; */
r_if
c_cond
(paren
id|dev_alloc_name
c_func
(paren
id|dev-&gt;chanA.netdevice
comma
l_string|&quot;hdlc%d&quot;
)paren
op_ge
l_int|0
)paren
(brace
r_struct
id|net_device
op_star
id|d
op_assign
id|dev-&gt;chanA.netdevice
suffix:semicolon
multiline_comment|/* &n;&t;&t; *&t;Initialise the PPP components&n;&t;&t; */
id|sppp_attach
c_func
(paren
op_amp
id|sv-&gt;netdev
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Local fields&n;&t;&t; */
id|d-&gt;base_addr
op_assign
id|iobase
suffix:semicolon
id|d-&gt;irq
op_assign
id|irq
suffix:semicolon
id|d-&gt;priv
op_assign
id|sv
suffix:semicolon
id|d-&gt;init
op_assign
l_int|NULL
suffix:semicolon
id|d-&gt;open
op_assign
id|hostess_open
suffix:semicolon
id|d-&gt;stop
op_assign
id|hostess_close
suffix:semicolon
id|d-&gt;hard_start_xmit
op_assign
id|hostess_queue_xmit
suffix:semicolon
id|d-&gt;get_stats
op_assign
id|hostess_get_stats
suffix:semicolon
id|d-&gt;set_multicast_list
op_assign
l_int|NULL
suffix:semicolon
id|d-&gt;do_ioctl
op_assign
id|hostess_ioctl
suffix:semicolon
id|d-&gt;neigh_setup
op_assign
id|hostess_neigh_setup_dev
suffix:semicolon
id|d-&gt;set_mac_address
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|d
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to register device.&bslash;n&quot;
comma
id|d-&gt;name
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
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
id|sv
suffix:semicolon
)brace
id|dmafail2
suffix:colon
r_if
c_cond
(paren
id|dma
op_eq
l_int|1
)paren
(brace
id|free_dma
c_func
(paren
id|dev-&gt;chanA.rxdma
)paren
suffix:semicolon
)brace
id|dmafail
suffix:colon
r_if
c_cond
(paren
id|dma
)paren
(brace
id|free_dma
c_func
(paren
id|dev-&gt;chanA.txdma
)paren
suffix:semicolon
)brace
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
id|fail1
suffix:colon
id|kfree
c_func
(paren
id|sv-&gt;netdev.dev
)paren
suffix:semicolon
id|fail2
suffix:colon
id|kfree
c_func
(paren
id|sv
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
DECL|function|sv11_shutdown
r_static
r_void
id|sv11_shutdown
c_func
(paren
r_struct
id|sv11_device
op_star
id|dev
)paren
(brace
id|sppp_detach
c_func
(paren
id|dev-&gt;netdev.dev
)paren
suffix:semicolon
id|z8530_shutdown
c_func
(paren
op_amp
id|dev-&gt;sync
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev-&gt;netdev.dev
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;sync.irq
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma
)paren
(brace
r_if
c_cond
(paren
id|dma
op_eq
l_int|1
)paren
(brace
id|free_dma
c_func
(paren
id|dev-&gt;sync.chanA.rxdma
)paren
suffix:semicolon
)brace
id|free_dma
c_func
(paren
id|dev-&gt;sync.chanA.txdma
)paren
suffix:semicolon
)brace
id|release_region
c_func
(paren
id|dev-&gt;sync.chanA.ctrlio
op_minus
l_int|1
comma
l_int|8
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|io
r_static
r_int
id|io
op_assign
l_int|0x200
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
op_assign
l_int|9
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
l_string|&quot;The I/O base of the Comtrol Hostess SV11 card&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dma
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|dma
comma
l_string|&quot;Set this to 1 to use DMA1/DMA3 for TX/RX&quot;
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
l_string|&quot;The interrupt line setting for the Comtrol Hostess SV11 card&quot;
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
l_string|&quot;Modular driver for the Comtrol Hostess SV11&quot;
)paren
suffix:semicolon
DECL|variable|sv11_unit
r_static
r_struct
id|sv11_device
op_star
id|sv11_unit
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SV-11 Z85230 Synchronous Driver v 0.03.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;(c) Copyright 2001, Red Hat Inc.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sv11_unit
op_assign
id|sv11_init
c_func
(paren
id|io
comma
id|irq
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|sv11_unit
)paren
(brace
id|sv11_shutdown
c_func
(paren
id|sv11_unit
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
