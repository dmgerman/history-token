multiline_comment|/*&n;  * Copyright (c) 1997-2000 LAN Media Corporation (LMC)&n;  * All rights reserved.  www.lanmedia.com&n;  *&n;  * This code is written by:&n;  * Andrew Stanley-Jones (asj@cban.com)&n;  * Rob Braun (bbraun@vix.com),&n;  * Michael Graff (explorer@vix.com) and&n;  * Matt Thomas (matt@3am-software.com).&n;  *&n;  * With Help By:&n;  * David Boggs&n;  * Ron Crane&n;  * Allan Cox&n;  *&n;  * This software may be used and distributed according to the terms&n;  * of the GNU General Public License version 2, incorporated herein by reference.&n;  *&n;  * Driver for the LanMedia LMC5200, LMC5245, LMC1000, LMC1200 cards.&n;  */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;asm/processor.h&gt;             /* Processor type for cache alignment. */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &quot;../syncppp.h&quot;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &quot;lmc_ver.h&quot;
macro_line|#include &quot;lmc.h&quot;
macro_line|#include &quot;lmc_var.h&quot;
macro_line|#include &quot;lmc_debug.h&quot;
macro_line|#include &quot;lmc_ioctl.h&quot;
macro_line|#include &quot;lmc_proto.h&quot;
singleline_comment|//#include &quot;lmc_proto_raw.h&quot;
multiline_comment|/*&n; * The compile-time variable SPPPSTUP causes the module to be&n; * compiled without referencing any of the sync ppp routines.&n; */
macro_line|#ifdef SPPPSTUB
DECL|macro|SYNC_PPP_init
mdefine_line|#define SYNC_PPP_init() (void)0
DECL|macro|SPPP_detach
mdefine_line|#define SPPP_detach(d)&t;(void)0
DECL|macro|SPPP_open
mdefine_line|#define SPPP_open(d)&t;0
DECL|macro|SPPP_reopen
mdefine_line|#define SPPP_reopen(d)&t;(void)0
DECL|macro|SPPP_close
mdefine_line|#define SPPP_close(d)&t;(void)0
DECL|macro|SPPP_attach
mdefine_line|#define SPPP_attach(d)&t;(void)0
DECL|macro|SPPP_do_ioctl
mdefine_line|#define SPPP_do_ioctl(d,i,c)&t;-EOPNOTSUPP
macro_line|#else
macro_line|#if LINUX_VERSION_CODE &lt; 0x20363
DECL|macro|SYNC_PPP_init
mdefine_line|#define SYNC_PPP_init&t;sync_ppp_init
DECL|macro|SPPP_attach
mdefine_line|#define SPPP_attach(x)&t;sppp_attach((struct ppp_device *)(x)-&gt;lmc_device)
DECL|macro|SPPP_detach
mdefine_line|#define SPPP_detach(x)&t;sppp_detach((x)-&gt;lmc_device)
DECL|macro|SPPP_open
mdefine_line|#define SPPP_open(x)&t;sppp_open((x)-&gt;lmc_device)
DECL|macro|SPPP_reopen
mdefine_line|#define SPPP_reopen(x)&t;sppp_reopen((x)-&gt;lmc_device)
DECL|macro|SPPP_close
mdefine_line|#define SPPP_close(x)&t;sppp_close((x)-&gt;lmc_device)
DECL|macro|SPPP_do_ioctl
mdefine_line|#define SPPP_do_ioctl(x, y, z)&t;sppp_do_ioctl((x)-&gt;lmc_device, (y), (z))
macro_line|#else
DECL|macro|SYNC_PPP_init
mdefine_line|#define SYNC_PPP_init&t;sync_ppp_init
DECL|macro|SPPP_attach
mdefine_line|#define SPPP_attach(x)&t;sppp_attach((x)-&gt;pd)
DECL|macro|SPPP_detach
mdefine_line|#define SPPP_detach(x)&t;sppp_detach((x)-&gt;pd-&gt;dev)
DECL|macro|SPPP_open
mdefine_line|#define SPPP_open(x)&t;sppp_open((x)-&gt;pd-&gt;dev)
DECL|macro|SPPP_reopen
mdefine_line|#define SPPP_reopen(x)&t;sppp_reopen((x)-&gt;pd-&gt;dev)
DECL|macro|SPPP_close
mdefine_line|#define SPPP_close(x)&t;sppp_close((x)-&gt;pd-&gt;dev)
DECL|macro|SPPP_do_ioctl
mdefine_line|#define SPPP_do_ioctl(x, y, z)&t;sppp_do_ioctl((x)-&gt;pd-&gt;dev, (y), (z))
macro_line|#endif
macro_line|#endif
DECL|variable|lmc_first_ppp_load
r_static
r_int
id|lmc_first_ppp_load
op_assign
l_int|0
suffix:semicolon
singleline_comment|// init
DECL|function|lmc_proto_init
r_void
id|lmc_proto_init
c_func
(paren
id|lmc_softc_t
op_star
id|sc
)paren
multiline_comment|/*FOLD00*/
(brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_init in&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sc-&gt;if_type
)paren
(brace
r_case
id|LMC_PPP
suffix:colon
r_if
c_cond
(paren
id|lmc_first_ppp_load
op_eq
l_int|0
)paren
(brace
macro_line|#ifndef MODULE
id|SYNC_PPP_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20363
id|sc-&gt;pd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ppp_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|sc-&gt;pd-&gt;dev
op_assign
id|sc-&gt;lmc_device
suffix:semicolon
macro_line|#endif
id|sc-&gt;if_ptr
op_assign
id|sc-&gt;pd
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LMC_RAW
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_init out&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// attach
DECL|function|lmc_proto_attach
r_void
id|lmc_proto_attach
c_func
(paren
id|lmc_softc_t
op_star
id|sc
)paren
multiline_comment|/*FOLD00*/
(brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_attach in&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sc-&gt;if_type
)paren
(brace
r_case
id|LMC_PPP
suffix:colon
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|sc-&gt;lmc_device
suffix:semicolon
id|SPPP_attach
c_func
(paren
id|sc
)paren
suffix:semicolon
id|dev-&gt;do_ioctl
op_assign
id|lmc_ioctl
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LMC_NET
suffix:colon
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|sc-&gt;lmc_device
suffix:semicolon
multiline_comment|/*&n;             * They set a few basics because they don&squot;t use sync_ppp&n;             */
id|dev-&gt;flags
op_or_assign
id|IFF_POINTOPOINT
suffix:semicolon
id|dev-&gt;hard_header
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;addr_len
op_assign
l_int|0
suffix:semicolon
)brace
r_case
id|LMC_RAW
suffix:colon
multiline_comment|/* Setup the task queue, maybe we should notify someone? */
(brace
)brace
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_attach out&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// detach
DECL|function|lmc_proto_detach
r_void
id|lmc_proto_detach
c_func
(paren
id|lmc_softc_t
op_star
id|sc
)paren
multiline_comment|/*FOLD00*/
(brace
r_switch
c_cond
(paren
id|sc-&gt;if_type
)paren
(brace
r_case
id|LMC_PPP
suffix:colon
id|SPPP_detach
c_func
(paren
id|sc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LMC_RAW
suffix:colon
multiline_comment|/* Tell someone we&squot;re detaching? */
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
singleline_comment|// reopen
DECL|function|lmc_proto_reopen
r_void
id|lmc_proto_reopen
c_func
(paren
id|lmc_softc_t
op_star
id|sc
)paren
multiline_comment|/*FOLD00*/
(brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_reopen in&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sc-&gt;if_type
)paren
(brace
r_case
id|LMC_PPP
suffix:colon
id|SPPP_reopen
c_func
(paren
id|sc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LMC_RAW
suffix:colon
multiline_comment|/* Reset the interface after being down, prerape to receive packets again */
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_reopen out&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// ioctl
DECL|function|lmc_proto_ioctl
r_int
id|lmc_proto_ioctl
c_func
(paren
id|lmc_softc_t
op_star
id|sc
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
id|cmd
)paren
multiline_comment|/*FOLD00*/
(brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_ioctl out&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sc-&gt;if_type
)paren
(brace
r_case
id|LMC_PPP
suffix:colon
r_return
id|SPPP_do_ioctl
(paren
id|sc
comma
id|ifr
comma
id|cmd
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_break
suffix:semicolon
)brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_ioctl out&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// open
DECL|function|lmc_proto_open
r_void
id|lmc_proto_open
c_func
(paren
id|lmc_softc_t
op_star
id|sc
)paren
multiline_comment|/*FOLD00*/
(brace
r_int
id|ret
suffix:semicolon
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_open in&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sc-&gt;if_type
)paren
(brace
r_case
id|LMC_PPP
suffix:colon
id|ret
op_assign
id|SPPP_open
c_func
(paren
id|sc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: syncPPP open failed: %d&bslash;n&quot;
comma
id|sc-&gt;name
comma
id|ret
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|LMC_RAW
suffix:colon
multiline_comment|/* We&squot;re about to start getting packets! */
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_open out&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// close
DECL|function|lmc_proto_close
r_void
id|lmc_proto_close
c_func
(paren
id|lmc_softc_t
op_star
id|sc
)paren
multiline_comment|/*FOLD00*/
(brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_close in&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sc-&gt;if_type
)paren
(brace
r_case
id|LMC_PPP
suffix:colon
id|SPPP_close
c_func
(paren
id|sc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LMC_RAW
suffix:colon
multiline_comment|/* Interface going down */
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_close out&quot;
)paren
suffix:semicolon
)brace
DECL|function|lmc_proto_type
r_int
r_int
id|lmc_proto_type
c_func
(paren
id|lmc_softc_t
op_star
id|sc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
multiline_comment|/*FOLD00*/
(brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_type in&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sc-&gt;if_type
)paren
(brace
r_case
id|LMC_PPP
suffix:colon
r_return
id|htons
c_func
(paren
id|ETH_P_WAN_PPP
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LMC_NET
suffix:colon
r_return
id|htons
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LMC_RAW
suffix:colon
multiline_comment|/* Packet type for skbuff kind of useless */
r_return
id|htons
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: No protocol set for this interface, assuming 802.2 (which is wrong!!)&bslash;n&quot;
comma
id|sc-&gt;name
)paren
suffix:semicolon
r_return
id|htons
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_tye out&quot;
)paren
suffix:semicolon
)brace
DECL|function|lmc_proto_netif
r_void
id|lmc_proto_netif
c_func
(paren
id|lmc_softc_t
op_star
id|sc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
multiline_comment|/*FOLD00*/
(brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_netif in&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sc-&gt;if_type
)paren
(brace
r_case
id|LMC_PPP
suffix:colon
r_case
id|LMC_NET
suffix:colon
r_default
suffix:colon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LMC_RAW
suffix:colon
r_break
suffix:semicolon
)brace
id|lmc_trace
c_func
(paren
id|sc-&gt;lmc_device
comma
l_string|&quot;lmc_proto_netif out&quot;
)paren
suffix:semicolon
)brace
eof
