multiline_comment|/* mptlan.h */
macro_line|#ifndef LINUX_MPTLAN_H_INCLUDED
DECL|macro|LINUX_MPTLAN_H_INCLUDED
mdefine_line|#define LINUX_MPTLAN_H_INCLUDED
multiline_comment|/*****************************************************************************/
macro_line|#if !defined(__GENKSYMS__)
macro_line|#include &lt;linux/module.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
singleline_comment|// #include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/fcdevice.h&gt;
singleline_comment|// #include &lt;linux/fddidevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
singleline_comment|// #include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Override mptbase.h by pre-defining these! */
DECL|macro|MODULEAUTHOR
mdefine_line|#define MODULEAUTHOR &quot;Noah Romer, Eddie C. Dost&quot;
macro_line|#include &quot;mptbase.h&quot;
multiline_comment|/*****************************************************************************/
DECL|macro|LANAME
mdefine_line|#define LANAME&t;&t;&quot;Fusion MPT LAN driver&quot;
DECL|macro|LANVER
mdefine_line|#define LANVER&t;&t;MPT_LINUX_VERSION_COMMON
macro_line|#ifdef MODULE
DECL|variable|MODULEAUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|MODULEAUTHOR
)paren
suffix:semicolon
DECL|variable|LANAME
id|MODULE_DESCRIPTION
c_func
(paren
id|LANAME
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*****************************************************************************/
DECL|macro|MPT_LAN_MAX_BUCKETS_OUT
mdefine_line|#define MPT_LAN_MAX_BUCKETS_OUT 256
DECL|macro|MPT_LAN_BUCKET_THRESH
mdefine_line|#define MPT_LAN_BUCKET_THRESH&t;18 /* 9 buckets in one message */
DECL|macro|MPT_LAN_BUCKETS_REMAIN_MISMATCH_THRESH
mdefine_line|#define MPT_LAN_BUCKETS_REMAIN_MISMATCH_THRESH 10
DECL|macro|MPT_LAN_RX_COPYBREAK
mdefine_line|#define MPT_LAN_RX_COPYBREAK&t;200
DECL|macro|MPT_LAN_TX_TIMEOUT
mdefine_line|#define MPT_LAN_TX_TIMEOUT&t;(1*HZ)
DECL|macro|MPT_TX_MAX_OUT_LIM
mdefine_line|#define MPT_TX_MAX_OUT_LIM      127
DECL|macro|MPT_LAN_MIN_MTU
mdefine_line|#define MPT_LAN_MIN_MTU&t;&t;96&t;&t;/* RFC2625 */
DECL|macro|MPT_LAN_MAX_MTU
mdefine_line|#define MPT_LAN_MAX_MTU&t;&t;65280&t;&t;/* RFC2625 */
DECL|macro|MPT_LAN_MTU
mdefine_line|#define MPT_LAN_MTU             13312&t;&t;/* Max perf range + lower mem&n;&t;&t;&t;&t;&t;&t;   usage than 16128 */
DECL|macro|MPT_LAN_NAA_RFC2625
mdefine_line|#define MPT_LAN_NAA_RFC2625     0x1
DECL|macro|MPT_LAN_NAA_QLOGIC
mdefine_line|#define MPT_LAN_NAA_QLOGIC      0x2
multiline_comment|/* MPT LAN Reset and Suspend Resource Flags Defines */
DECL|macro|MPT_LAN_RESOURCE_FLAG_RETURN_POSTED_BUCKETS
mdefine_line|#define MPT_LAN_RESOURCE_FLAG_RETURN_POSTED_BUCKETS    0x01
DECL|macro|MPT_LAN_RESOURCE_FLAG_RETURN_PEND_TRANSMITS
mdefine_line|#define MPT_LAN_RESOURCE_FLAG_RETURN_PEND_TRANSMITS    0x02
multiline_comment|/*****************************************************************************/
macro_line|#ifdef MPT_LAN_IO_DEBUG
DECL|macro|dioprintk
mdefine_line|#define dioprintk(x)  printk x
macro_line|#else
DECL|macro|dioprintk
mdefine_line|#define dioprintk(x)
macro_line|#endif
macro_line|#ifdef MPT_LAN_DEBUG
DECL|macro|dlprintk
mdefine_line|#define dlprintk(x)  printk x
macro_line|#else
DECL|macro|dlprintk
mdefine_line|#define dlprintk(x)
macro_line|#endif
DECL|macro|NETDEV_TO_LANPRIV_PTR
mdefine_line|#define NETDEV_TO_LANPRIV_PTR(d)&t;((struct mpt_lan_priv *)(d)-&gt;priv)
DECL|macro|NETDEV_PTR_TO_IOC_NAME_s
mdefine_line|#define NETDEV_PTR_TO_IOC_NAME_s(d)&t;(NETDEV_TO_LANPRIV_PTR(d)-&gt;mpt_dev-&gt;name)
DECL|macro|IOC_AND_NETDEV_NAMES_s_s
mdefine_line|#define IOC_AND_NETDEV_NAMES_s_s(d)&t;NETDEV_PTR_TO_IOC_NAME_s(d), (d)-&gt;name
multiline_comment|/*****************************************************************************/
macro_line|#endif
eof
