multiline_comment|/* $Id: hysdn_net.c,v 1.8.6.4 2001/09/23 22:24:54 kai Exp $&n; *&n; * Linux driver for HYSDN cards, net (ethernet type) handling routines.&n; *&n; * Author    Werner Cornelius (werner@titro.de) for Hypercope GmbH&n; * Copyright 1999 by Werner Cornelius (werner@titro.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * This net module has been inspired by the skeleton driver from&n; * Donald Becker (becker@CESDIS.gsfc.nasa.gov)&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &quot;hysdn_defs.h&quot;
DECL|variable|hynet_enable
r_int
r_int
id|hynet_enable
op_assign
l_int|0xffffffff
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|hynet_enable
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
multiline_comment|/* store the actual version for log reporting */
DECL|variable|hysdn_net_revision
r_char
op_star
id|hysdn_net_revision
op_assign
l_string|&quot;$Revision: 1.8.6.4 $&quot;
suffix:semicolon
DECL|macro|MAX_SKB_BUFFERS
mdefine_line|#define MAX_SKB_BUFFERS 20&t;/* number of buffers for keeping TX-data */
multiline_comment|/****************************************************************************/
multiline_comment|/* structure containing the complete network data. The structure is aligned */
multiline_comment|/* in a way that both, the device and statistics are kept inside it.        */
multiline_comment|/* for proper access, the device structure MUST be the first var/struct     */
multiline_comment|/* inside the definition.                                                   */
multiline_comment|/****************************************************************************/
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|netdev
r_struct
id|net_device
id|netdev
suffix:semicolon
multiline_comment|/* the network device */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* additional vars may be added here */
DECL|member|dev_name
r_char
id|dev_name
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* our own device name */
multiline_comment|/* Tx control lock.  This protects the transmit buffer ring&n;&t; * state along with the &quot;tx full&quot; state of the driver.  This&n;&t; * means all netif_queue flow control actions are protected&n;&t; * by this lock as well.&n;&t; */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|skbs
r_struct
id|sk_buff
op_star
id|skbs
(braket
id|MAX_SKB_BUFFERS
)braket
suffix:semicolon
multiline_comment|/* pointers to tx-skbs */
DECL|member|in_idx
DECL|member|out_idx
r_int
id|in_idx
comma
id|out_idx
suffix:semicolon
multiline_comment|/* indexes to buffer ring */
DECL|member|sk_count
r_int
id|sk_count
suffix:semicolon
multiline_comment|/* number of buffers currently in ring */
)brace
suffix:semicolon
multiline_comment|/* net_local */
multiline_comment|/*****************************************************/
multiline_comment|/* Get the current statistics for this card.         */
multiline_comment|/* This may be called with the card open or closed ! */
multiline_comment|/*****************************************************/
r_static
r_struct
id|net_device_stats
op_star
DECL|function|net_get_stats
id|net_get_stats
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
op_amp
(paren
(paren
r_struct
id|net_local
op_star
)paren
id|dev
)paren
op_member_access_from_pointer
id|stats
)paren
suffix:semicolon
)brace
multiline_comment|/* net_device_stats */
multiline_comment|/*********************************************************************/
multiline_comment|/* Open/initialize the board. This is called (in the current kernel) */
multiline_comment|/* sometime after booting when the &squot;ifconfig&squot; program is run.        */
multiline_comment|/* This routine should set everything up anew at each open, even     */
multiline_comment|/* registers that &quot;should&quot; only need to be set once at boot, so that */
multiline_comment|/* there is non-reboot way to recover if something goes wrong.       */
multiline_comment|/*********************************************************************/
r_static
r_int
DECL|function|net_open
id|net_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|in_device
op_star
id|in_dev
suffix:semicolon
id|hysdn_card
op_star
id|card
op_assign
id|dev-&gt;priv
suffix:semicolon
r_int
id|i
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* start tx-queueing */
multiline_comment|/* Fill in the MAC-level header (if not already set) */
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;mac_addr
(braket
l_int|0
)braket
)paren
(brace
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
op_minus
r_sizeof
(paren
id|ulong
)paren
suffix:semicolon
id|i
op_increment
)paren
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
l_int|0xfc
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
r_struct
id|in_ifaddr
op_star
id|ifa
op_assign
id|in_dev-&gt;ifa_list
suffix:semicolon
r_if
c_cond
(paren
id|ifa
op_ne
l_int|NULL
)paren
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
op_plus
(paren
id|ETH_ALEN
op_minus
r_sizeof
(paren
id|ulong
)paren
)paren
comma
op_amp
id|ifa-&gt;ifa_local
comma
r_sizeof
(paren
id|ulong
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
id|card-&gt;mac_addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* net_open */
multiline_comment|/*******************************************/
multiline_comment|/* flush the currently occupied tx-buffers */
multiline_comment|/* must only be called when device closed  */
multiline_comment|/*******************************************/
r_static
r_void
DECL|function|flush_tx_buffers
id|flush_tx_buffers
c_func
(paren
r_struct
id|net_local
op_star
id|nl
)paren
(brace
r_while
c_loop
(paren
id|nl-&gt;sk_count
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|nl-&gt;skbs
(braket
id|nl-&gt;out_idx
op_increment
)braket
)paren
suffix:semicolon
multiline_comment|/* free skb */
r_if
c_cond
(paren
id|nl-&gt;out_idx
op_ge
id|MAX_SKB_BUFFERS
)paren
id|nl-&gt;out_idx
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* wrap around */
id|nl-&gt;sk_count
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/* flush_tx_buffers */
multiline_comment|/*********************************************************************/
multiline_comment|/* close/decativate the device. The device is not removed, but only  */
multiline_comment|/* deactivated.                                                      */
multiline_comment|/*********************************************************************/
r_static
r_int
DECL|function|net_close
id|net_close
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
multiline_comment|/* disable queueing */
id|flush_tx_buffers
c_func
(paren
(paren
r_struct
id|net_local
op_star
)paren
id|dev
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* success */
)brace
multiline_comment|/* net_close */
multiline_comment|/************************************/
multiline_comment|/* send a packet on this interface. */
multiline_comment|/* new style for kernel &gt;= 2.3.33   */
multiline_comment|/************************************/
r_static
r_int
DECL|function|net_send_packet
id|net_send_packet
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
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|lp-&gt;lock
)paren
suffix:semicolon
id|lp-&gt;skbs
(braket
id|lp-&gt;in_idx
op_increment
)braket
op_assign
id|skb
suffix:semicolon
multiline_comment|/* add to buffer list */
r_if
c_cond
(paren
id|lp-&gt;in_idx
op_ge
id|MAX_SKB_BUFFERS
)paren
id|lp-&gt;in_idx
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* wrap around */
id|lp-&gt;sk_count
op_increment
suffix:semicolon
multiline_comment|/* adjust counter */
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* If we just used up the very last entry in the&n;&t; * TX ring on this device, tell the queueing&n;&t; * layer to send no more.&n;&t; */
r_if
c_cond
(paren
id|lp-&gt;sk_count
op_ge
id|MAX_SKB_BUFFERS
)paren
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* When the TX completion hw interrupt arrives, this&n;&t; * is when the transmit statistics are updated.&n;&t; */
id|spin_unlock_irq
c_func
(paren
op_amp
id|lp-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;sk_count
op_le
l_int|3
)paren
(brace
id|schedule_work
c_func
(paren
op_amp
(paren
(paren
id|hysdn_card
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|irq_queue
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* success */
)brace
multiline_comment|/* net_send_packet */
multiline_comment|/***********************************************************************/
multiline_comment|/* acknowlegde a packet send. The network layer will be informed about */
multiline_comment|/* completion                                                          */
multiline_comment|/***********************************************************************/
r_void
DECL|function|hysdn_tx_netack
id|hysdn_tx_netack
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
id|card-&gt;netif
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp
)paren
r_return
suffix:semicolon
multiline_comment|/* non existing device */
r_if
c_cond
(paren
op_logical_neg
id|lp-&gt;sk_count
)paren
r_return
suffix:semicolon
multiline_comment|/* error condition */
id|lp-&gt;stats.tx_packets
op_increment
suffix:semicolon
id|lp-&gt;stats.tx_bytes
op_add_assign
id|lp-&gt;skbs
(braket
id|lp-&gt;out_idx
)braket
op_member_access_from_pointer
id|len
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|lp-&gt;skbs
(braket
id|lp-&gt;out_idx
op_increment
)braket
)paren
suffix:semicolon
multiline_comment|/* free skb */
r_if
c_cond
(paren
id|lp-&gt;out_idx
op_ge
id|MAX_SKB_BUFFERS
)paren
id|lp-&gt;out_idx
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* wrap around */
r_if
c_cond
(paren
id|lp-&gt;sk_count
op_decrement
op_eq
id|MAX_SKB_BUFFERS
)paren
multiline_comment|/* dec usage count */
id|netif_start_queue
c_func
(paren
(paren
r_struct
id|net_device
op_star
)paren
id|lp
)paren
suffix:semicolon
)brace
multiline_comment|/* hysdn_tx_netack */
multiline_comment|/*****************************************************/
multiline_comment|/* we got a packet from the network, go and queue it */
multiline_comment|/*****************************************************/
r_void
DECL|function|hysdn_rx_netpkt
id|hysdn_rx_netpkt
c_func
(paren
id|hysdn_card
op_star
id|card
comma
id|uchar
op_star
id|buf
comma
id|word
id|len
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
id|card-&gt;netif
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp
)paren
r_return
suffix:semicolon
multiline_comment|/* non existing device */
id|lp-&gt;stats.rx_bytes
op_add_assign
id|len
suffix:semicolon
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|len
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
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s: Memory squeeze, dropping packet.&bslash;n&quot;
comma
id|lp-&gt;netdev.name
)paren
suffix:semicolon
id|lp-&gt;stats.rx_dropped
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
op_amp
id|lp-&gt;netdev
suffix:semicolon
multiline_comment|/* copy the data */
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
comma
id|buf
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* determine the used protocol */
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
op_amp
id|lp-&gt;netdev
)paren
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|lp-&gt;stats.rx_packets
op_increment
suffix:semicolon
multiline_comment|/* adjust packet count */
)brace
multiline_comment|/* hysdn_rx_netpkt */
multiline_comment|/*****************************************************/
multiline_comment|/* return the pointer to a network packet to be send */
multiline_comment|/*****************************************************/
r_struct
id|sk_buff
op_star
DECL|function|hysdn_tx_netget
id|hysdn_tx_netget
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
id|card-&gt;netif
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp
)paren
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* non existing device */
r_if
c_cond
(paren
op_logical_neg
id|lp-&gt;sk_count
)paren
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* nothing available */
r_return
(paren
id|lp-&gt;skbs
(braket
id|lp-&gt;out_idx
)braket
)paren
suffix:semicolon
multiline_comment|/* next packet to send */
)brace
multiline_comment|/* hysdn_tx_netget */
multiline_comment|/*******************************************/
multiline_comment|/* init function called by register device */
multiline_comment|/*******************************************/
r_static
r_int
DECL|function|net_init
id|net_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* setup the function table */
id|dev-&gt;open
op_assign
id|net_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|net_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|net_send_packet
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|net_get_stats
suffix:semicolon
multiline_comment|/* Fill in the fields of the device structure with ethernet values. */
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* success */
)brace
multiline_comment|/* net_init */
multiline_comment|/*****************************************************************************/
multiline_comment|/* hysdn_net_create creates a new net device for the given card. If a device */
multiline_comment|/* already exists, it will be deleted and created a new one. The return value */
multiline_comment|/* 0 announces success, else a negative error code will be returned.         */
multiline_comment|/*****************************************************************************/
r_int
DECL|function|hysdn_net_create
id|hysdn_net_create
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;No card-pt in hysdn_net_create!&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|hysdn_net_release
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* release an existing net device */
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|net_local
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HYSDN: unable to allocate mem&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|net_local
)paren
)paren
suffix:semicolon
multiline_comment|/* clean the structure */
id|spin_lock_init
c_func
(paren
op_amp
(paren
(paren
r_struct
id|net_local
op_star
)paren
id|dev
)paren
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
multiline_comment|/* initialise necessary or informing fields */
id|dev-&gt;base_addr
op_assign
id|card-&gt;iobase
suffix:semicolon
multiline_comment|/* IO address */
id|dev-&gt;irq
op_assign
id|card-&gt;irq
suffix:semicolon
multiline_comment|/* irq */
id|dev-&gt;init
op_assign
id|net_init
suffix:semicolon
multiline_comment|/* the init function of the device */
r_if
c_cond
(paren
id|dev-&gt;name
)paren
(brace
id|strcpy
c_func
(paren
id|dev-&gt;name
comma
(paren
(paren
r_struct
id|net_local
op_star
)paren
id|dev
)paren
op_member_access_from_pointer
id|dev_name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|i
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HYSDN: unable to create network device&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
(paren
id|i
)paren
suffix:semicolon
)brace
id|dev-&gt;priv
op_assign
id|card
suffix:semicolon
multiline_comment|/* remember pointer to own data structure */
id|card-&gt;netif
op_assign
id|dev
suffix:semicolon
multiline_comment|/* setup the local pointer */
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_NET_INIT
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;network device created&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* and return success */
)brace
multiline_comment|/* hysdn_net_create */
multiline_comment|/***************************************************************************/
multiline_comment|/* hysdn_net_release deletes the net device for the given card. The return */
multiline_comment|/* value 0 announces success, else a negative error code will be returned. */
multiline_comment|/***************************************************************************/
r_int
DECL|function|hysdn_net_release
id|hysdn_net_release
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|card-&gt;netif
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* non existing */
id|card-&gt;netif
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* clear out pointer */
id|dev
op_member_access_from_pointer
id|stop
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* close the device */
id|flush_tx_buffers
c_func
(paren
(paren
r_struct
id|net_local
op_star
)paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* empty buffers */
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* release the device */
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* release the memory allocated */
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_NET_INIT
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;network device deleted&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* always successful */
)brace
multiline_comment|/* hysdn_net_release */
multiline_comment|/*****************************************************************************/
multiline_comment|/* hysdn_net_getname returns a pointer to the name of the network interface. */
multiline_comment|/* if the interface is not existing, a &quot;-&quot; is returned.                      */
multiline_comment|/*****************************************************************************/
r_char
op_star
DECL|function|hysdn_net_getname
id|hysdn_net_getname
c_func
(paren
id|hysdn_card
op_star
id|card
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|card-&gt;netif
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
(paren
l_string|&quot;-&quot;
)paren
suffix:semicolon
multiline_comment|/* non existing */
r_return
(paren
id|dev-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/* hysdn_net_getname */
eof
