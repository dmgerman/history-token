multiline_comment|/*&n; * Simulated Ethernet Driver&n; *&n; * Copyright (C) 1999-2001 Hewlett-Packard Co&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|SIMETH_RECV_MAX
mdefine_line|#define SIMETH_RECV_MAX&t;10
multiline_comment|/*&n; * Maximum possible received frame for Ethernet.&n; * We preallocate an sk_buff of that size to avoid costly&n; * memcpy for temporary buffer into sk_buff. We do basically&n; * what&squot;s done in other drivers, like eepro with a ring.&n; * The difference is, of course, that we don&squot;t have real DMA !!!&n; */
DECL|macro|SIMETH_FRAME_SIZE
mdefine_line|#define SIMETH_FRAME_SIZE&t;ETH_FRAME_LEN
DECL|macro|SSC_NETDEV_PROBE
mdefine_line|#define SSC_NETDEV_PROBE&t;&t;100
DECL|macro|SSC_NETDEV_SEND
mdefine_line|#define SSC_NETDEV_SEND&t;&t;&t;101
DECL|macro|SSC_NETDEV_RECV
mdefine_line|#define SSC_NETDEV_RECV&t;&t;&t;102
DECL|macro|SSC_NETDEV_ATTACH
mdefine_line|#define SSC_NETDEV_ATTACH&t;&t;103
DECL|macro|SSC_NETDEV_DETACH
mdefine_line|#define SSC_NETDEV_DETACH&t;&t;104
DECL|macro|NETWORK_INTR
mdefine_line|#define NETWORK_INTR&t;&t;&t;8
DECL|struct|simeth_local
r_struct
id|simeth_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|simfd
r_int
id|simfd
suffix:semicolon
multiline_comment|/* descriptor in the simulator */
)brace
suffix:semicolon
r_static
r_int
id|simeth_probe1
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|simeth_open
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
id|simeth_close
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
id|simeth_tx
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
suffix:semicolon
r_static
r_int
id|simeth_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device_stats
op_star
id|simeth_get_stats
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
id|simeth_interrupt
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
r_static
r_void
id|set_multicast_list
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
id|simeth_device_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
suffix:semicolon
DECL|variable|simeth_version
r_static
r_char
op_star
id|simeth_version
op_assign
l_string|&quot;0.3&quot;
suffix:semicolon
multiline_comment|/*&n; * This variable is used to establish a mapping between the Linux/ia64 kernel&n; * and the host linux kernel.&n; *&n; * As of today, we support only one card, even though most of the code&n; * is ready for many more. The mapping is then:&n; *&t;linux/ia64 -&gt; linux/x86&n; * &t;   eth0    -&gt; eth1&n; *&n; * In the future, we some string operations, we could easily support up&n; * to 10 cards (0-9).&n; *&n; * The default mapping can be changed on the kernel command line by&n; * specifying simeth=ethX (or whatever string you want).&n; */
DECL|variable|simeth_device
r_static
r_char
op_star
id|simeth_device
op_assign
l_string|&quot;eth0&quot;
suffix:semicolon
multiline_comment|/* default host interface to use */
DECL|variable|card_count
r_static
r_volatile
r_int
r_int
id|card_count
suffix:semicolon
multiline_comment|/* how many cards &quot;found&quot; so far */
DECL|variable|simeth_debug
r_static
r_int
id|simeth_debug
suffix:semicolon
multiline_comment|/* set to 1 to get debug information */
multiline_comment|/*&n; * Used to catch IFF_UP &amp; IFF_DOWN events&n; */
DECL|variable|simeth_dev_notifier
r_static
r_struct
id|notifier_block
id|simeth_dev_notifier
op_assign
(brace
id|simeth_device_event
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; * Function used when using a kernel command line option.&n; *&n; * Format: simeth=interface_name (like eth0)&n; */
r_static
r_int
id|__init
DECL|function|simeth_setup
id|simeth_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|simeth_device
op_assign
id|str
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;simeth=&quot;
comma
id|simeth_setup
)paren
suffix:semicolon
multiline_comment|/*&n; * Function used to probe for simeth devices when not installed&n; * as a loadable module&n; */
r_int
id|__init
DECL|function|simeth_probe
id|simeth_probe
(paren
r_void
)paren
(brace
r_int
id|r
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;simeth: v%s&bslash;n&quot;
comma
id|simeth_version
)paren
suffix:semicolon
id|r
op_assign
id|simeth_probe1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
l_int|0
)paren
id|register_netdevice_notifier
c_func
(paren
op_amp
id|simeth_dev_notifier
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_extern
r_int
id|ia64_ssc
(paren
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ia64_ssc_connect_irq
(paren
r_int
id|intr
comma
r_int
id|irq
)paren
suffix:semicolon
r_static
r_inline
r_int
DECL|function|netdev_probe
id|netdev_probe
c_func
(paren
r_char
op_star
id|name
comma
r_int
r_char
op_star
id|ether
)paren
(brace
r_return
id|ia64_ssc
c_func
(paren
id|__pa
c_func
(paren
id|name
)paren
comma
id|__pa
c_func
(paren
id|ether
)paren
comma
l_int|0
comma
l_int|0
comma
id|SSC_NETDEV_PROBE
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|netdev_connect
id|netdev_connect
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/* XXX Fix me&n;&t; * this does not support multiple cards&n;&t; * also no return value&n;&t; */
id|ia64_ssc_connect_irq
c_func
(paren
id|NETWORK_INTR
comma
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|netdev_attach
id|netdev_attach
c_func
(paren
r_int
id|fd
comma
r_int
id|irq
comma
r_int
r_int
id|ipaddr
)paren
(brace
multiline_comment|/* this puts the host interface in the right mode (start interupting) */
r_return
id|ia64_ssc
c_func
(paren
id|fd
comma
id|ipaddr
comma
l_int|0
comma
l_int|0
comma
id|SSC_NETDEV_ATTACH
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|netdev_detach
id|netdev_detach
c_func
(paren
r_int
id|fd
)paren
(brace
multiline_comment|/*&n;&t; * inactivate the host interface (don&squot;t interrupt anymore) */
r_return
id|ia64_ssc
c_func
(paren
id|fd
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_NETDEV_DETACH
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|netdev_send
id|netdev_send
c_func
(paren
r_int
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|len
)paren
(brace
r_return
id|ia64_ssc
c_func
(paren
id|fd
comma
id|__pa
c_func
(paren
id|buf
)paren
comma
id|len
comma
l_int|0
comma
id|SSC_NETDEV_SEND
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|netdev_read
id|netdev_read
c_func
(paren
r_int
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|len
)paren
(brace
r_return
id|ia64_ssc
c_func
(paren
id|fd
comma
id|__pa
c_func
(paren
id|buf
)paren
comma
id|len
comma
l_int|0
comma
id|SSC_NETDEV_RECV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function shared with module code, so cannot be in init section&n; *&n; * So far this function &quot;detects&quot; only one card (test_&amp;_set) but could&n; * be extended easily.&n; *&n; * Return:&n; * &t;- -ENODEV is no device found&n; *&t;- -ENOMEM is no more memory&n; *&t;- 0 otherwise&n; */
r_static
r_int
DECL|function|simeth_probe1
id|simeth_probe1
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|mac_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
r_struct
id|simeth_local
op_star
id|local
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|fd
comma
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * XXX Fix me&n;&t; * let&squot;s support just one card for now&n;&t; */
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|card_count
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/*&n;&t; * check with the simulator for the device&n;&t; */
id|fd
op_assign
id|netdev_probe
c_func
(paren
id|simeth_device
comma
id|mac_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dev
op_assign
id|init_etherdev
c_func
(paren
l_int|NULL
comma
r_sizeof
(paren
r_struct
id|simeth_local
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
id|mac_addr
comma
r_sizeof
(paren
id|mac_addr
)paren
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|ia64_alloc_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * attach the interrupt in the simulator, this does enable interrupts&n;&t; * until a netdev_attach() is called&n;&t; */
id|netdev_connect
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|simeth_local
)paren
)paren
suffix:semicolon
id|local
op_assign
id|dev-&gt;priv
suffix:semicolon
id|local-&gt;simfd
op_assign
id|fd
suffix:semicolon
multiline_comment|/* keep track of underlying file descriptor */
id|dev-&gt;open
op_assign
id|simeth_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|simeth_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|simeth_tx
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|simeth_get_stats
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
id|set_multicast_list
suffix:semicolon
multiline_comment|/* no yet used */
multiline_comment|/* Fill in the fields of the device structure with ethernet-generic values. */
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: hosteth=%s simfd=%d, HwAddr&quot;
comma
id|dev-&gt;name
comma
id|simeth_device
comma
id|local-&gt;simfd
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
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %2.2x&quot;
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
l_string|&quot;, IRQ %d&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * actually binds the device to an interrupt vector&n; */
r_static
r_int
DECL|function|simeth_open
id|simeth_open
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
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|simeth_interrupt
comma
l_int|0
comma
l_string|&quot;simeth&quot;
comma
id|dev
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;simeth: unable to get IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* copied from lapbether.c */
DECL|function|dev_is_ethdev
r_static
id|__inline__
r_int
id|dev_is_ethdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_ETHER
op_logical_and
id|strncmp
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;dummy&quot;
comma
l_int|5
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handler for IFF_UP or IFF_DOWN&n; *&n; * The reason for that is that we don&squot;t want to be interrupted when the&n; * interface is down. There is no way to unconnect in the simualtor. Instead&n; * we use this function to shutdown packet processing in the frame filter&n; * in the simulator. Thus no interrupts are generated&n; *&n; *&n; * That&squot;s also the place where we pass the IP address of this device to the&n; * simulator so that that we can start filtering packets for it&n; *&n; * There may be a better way of doing this, but I don&squot;t know which yet.&n; */
r_static
r_int
DECL|function|simeth_device_event
id|simeth_device_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
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
id|ptr
suffix:semicolon
r_struct
id|simeth_local
op_star
id|local
suffix:semicolon
r_struct
id|in_device
op_star
id|in_dev
suffix:semicolon
r_struct
id|in_ifaddr
op_star
op_star
id|ifap
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|in_ifaddr
op_star
id|ifa
op_assign
l_int|NULL
suffix:semicolon
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;simeth_device_event dev=0&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|event
op_ne
id|NETDEV_UP
op_logical_and
id|event
op_ne
id|NETDEV_DOWN
)paren
r_return
id|NOTIFY_DONE
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether or not it&squot;s for an ethernet device&n;&t; *&n;&t; * XXX Fixme: This works only as long as we support one&n;&t; * type of ethernet device.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|dev_is_ethdev
c_func
(paren
id|dev
)paren
)paren
r_return
id|NOTIFY_DONE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|in_dev
op_assign
id|dev-&gt;ip_ptr
)paren
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|ifap
op_assign
op_amp
id|in_dev-&gt;ifa_list
suffix:semicolon
(paren
id|ifa
op_assign
op_star
id|ifap
)paren
op_ne
l_int|NULL
suffix:semicolon
id|ifap
op_assign
op_amp
id|ifa-&gt;ifa_next
)paren
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|dev-&gt;name
comma
id|ifa-&gt;ifa_label
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ifa
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;simeth_open: can&squot;t find device %s&squot;s ifa&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;simeth_device_event: %s ipaddr=0x%x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|htonl
c_func
(paren
id|ifa-&gt;ifa_local
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * XXX Fix me&n;&t; * if the device was up, and we&squot;re simply reconfiguring it, not sure&n;&t; * we get DOWN then UP.&n;&t; */
id|local
op_assign
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* now do it for real */
id|r
op_assign
id|event
op_eq
id|NETDEV_UP
ques
c_cond
id|netdev_attach
c_func
(paren
id|local-&gt;simfd
comma
id|dev-&gt;irq
comma
id|htonl
c_func
(paren
id|ifa-&gt;ifa_local
)paren
)paren
suffix:colon
id|netdev_detach
c_func
(paren
id|local-&gt;simfd
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;simeth: netdev_attach/detach: event=%s -&gt;%d&bslash;n&quot;
comma
id|event
op_eq
id|NETDEV_UP
ques
c_cond
l_string|&quot;attach&quot;
suffix:colon
l_string|&quot;detach&quot;
comma
id|r
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
r_static
r_int
DECL|function|simeth_close
id|simeth_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Only used for debug&n; */
r_static
r_void
DECL|function|frame_print
id|frame_print
c_func
(paren
r_int
r_char
op_star
id|from
comma
r_int
r_char
op_star
id|frame
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: (%d) %02x&quot;
comma
id|from
comma
id|len
comma
id|frame
(braket
l_int|0
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;:%02x&quot;
comma
id|frame
(braket
id|i
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %2x&quot;
comma
id|frame
(braket
l_int|6
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
OL
l_int|12
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;:%02x&quot;
comma
id|frame
(braket
id|i
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; [%02x%02x]&bslash;n&quot;
comma
id|frame
(braket
l_int|12
)braket
comma
id|frame
(braket
l_int|13
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|14
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|frame
(braket
id|i
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|10
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function used to transmit of frame, very last one on the path before&n; * going to the simulator.&n; */
r_static
r_int
DECL|function|simeth_tx
id|simeth_tx
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
id|simeth_local
op_star
id|local
op_assign
(paren
r_struct
id|simeth_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
macro_line|#if 0
multiline_comment|/* ensure we have at least ETH_ZLEN bytes (min frame size) */
r_int
r_int
id|length
op_assign
id|ETH_ZLEN
OL
id|skb-&gt;len
ques
c_cond
id|skb-&gt;len
suffix:colon
id|ETH_ZLEN
suffix:semicolon
multiline_comment|/* Where do the extra padding bytes comes from inthe skbuff ? */
macro_line|#else
multiline_comment|/* the real driver in the host system is going to take care of that&n;&t; * or maybe it&squot;s the NIC itself.&n;&t; */
r_int
r_int
id|length
op_assign
id|skb-&gt;len
suffix:semicolon
macro_line|#endif
id|local-&gt;stats.tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|local-&gt;stats.tx_packets
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|simeth_debug
OG
l_int|5
)paren
id|frame_print
c_func
(paren
l_string|&quot;simeth_tx&quot;
comma
id|skb-&gt;data
comma
id|length
)paren
suffix:semicolon
id|netdev_send
c_func
(paren
id|local-&gt;simfd
comma
id|skb-&gt;data
comma
id|length
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * we are synchronous on write, so we don&squot;t simulate a&n;&t; * trasnmit complete interrupt, thus we don&squot;t need to arm a tx&n;&t; */
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|sk_buff
op_star
DECL|function|make_new_skb
id|make_new_skb
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|sk_buff
op_star
id|nskb
suffix:semicolon
multiline_comment|/*&n;&t; * The +2 is used to make sure that the IP header is nicely&n;&t; * aligned (on 4byte boundary I assume 14+2=16)&n;&t; */
id|nskb
op_assign
id|dev_alloc_skb
c_func
(paren
id|SIMETH_FRAME_SIZE
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nskb
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: memory squeeze. dropping packet.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|nskb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb_reserve
c_func
(paren
id|nskb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Align IP on 16 byte boundaries */
id|skb_put
c_func
(paren
id|nskb
comma
id|SIMETH_FRAME_SIZE
)paren
suffix:semicolon
r_return
id|nskb
suffix:semicolon
)brace
multiline_comment|/*&n; * called from interrupt handler to process a received frame&n; */
r_static
r_int
DECL|function|simeth_rx
id|simeth_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|simeth_local
op_star
id|local
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|rcv_count
op_assign
id|SIMETH_RECV_MAX
suffix:semicolon
id|local
op_assign
(paren
r_struct
id|simeth_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/*&n;&t; * the loop concept has been borrowed from other drivers&n;&t; * looks to me like it&squot;s a throttling thing to avoid pushing to many&n;&t; * packets at one time into the stack. Making sure we can process them&n;&t; * upstream and make forward progress overall&n;&t; */
r_do
(brace
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|make_new_skb
c_func
(paren
id|dev
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: memory squeeze. dropping packet.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|local-&gt;stats.rx_dropped
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Read only one frame at a time&n;&t;&t; */
id|len
op_assign
id|netdev_read
c_func
(paren
id|local-&gt;simfd
comma
id|skb-&gt;data
comma
id|SIMETH_FRAME_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|simeth_debug
OG
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: count=%d netdev_read=0&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|SIMETH_RECV_MAX
op_minus
id|rcv_count
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/*&n;&t;&t; * XXX Fix me&n;&t;&t; * Should really do a csum+copy here&n;&t;&t; */
id|memcpy
c_func
(paren
id|skb-&gt;data
comma
id|frame
comma
id|len
)paren
suffix:semicolon
macro_line|#endif
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
r_if
c_cond
(paren
id|simeth_debug
OG
l_int|6
)paren
id|frame_print
c_func
(paren
l_string|&quot;simeth_rx&quot;
comma
id|skb-&gt;data
comma
id|len
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * push the packet up &amp; trigger software interrupt&n;&t;&t; */
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|local-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|local-&gt;stats.rx_bytes
op_add_assign
id|len
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|rcv_count
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
multiline_comment|/* 0 = nothing left to read, otherwise, we can try again */
)brace
multiline_comment|/*&n; * Interrupt handler (Yes, we can do it too !!!)&n; */
r_static
r_void
DECL|function|simeth_interrupt
id|simeth_interrupt
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
id|dev_id
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
id|KERN_WARNING
l_string|&quot;simeth: irq %d for unknown device&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * very simple loop because we get interrupts only when receving&n;&t; */
r_while
c_loop
(paren
id|simeth_rx
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
r_static
r_struct
id|net_device_stats
op_star
DECL|function|simeth_get_stats
id|simeth_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|simeth_local
op_star
id|local
op_assign
(paren
r_struct
id|simeth_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|local-&gt;stats
suffix:semicolon
)brace
multiline_comment|/* fake multicast ability */
r_static
r_void
DECL|function|set_multicast_list
id|set_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: set_multicast_list called&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_FASTROUTE
r_static
r_int
DECL|function|simeth_accept_fastpath
id|simeth_accept_fastpath
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|dst_entry
op_star
id|dst
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: simeth_accept_fastpath called&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|simeth_probe
id|__initcall
c_func
(paren
id|simeth_probe
)paren
suffix:semicolon
eof
