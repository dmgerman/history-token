multiline_comment|/*&n; * ibm_emac_core.h&n; *&n; * Ethernet driver for the built in ethernet on the IBM 405 PowerPC&n; * processor.&n; *&n; *      Armin Kuster akuster@mvista.com&n; *      Sept, 2001&n; *&n; *      Orignial driver&n; *         Johnnie Peters&n; *         jpeters@mvista.com&n; *&n; * Copyright 2000 MontaVista Softare Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef _IBM_EMAC_CORE_H_
DECL|macro|_IBM_EMAC_CORE_H_
mdefine_line|#define _IBM_EMAC_CORE_H_
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;&t;&t;/* For phys_addr_t */
macro_line|#include &quot;ibm_emac.h&quot;
macro_line|#include &quot;ibm_emac_phy.h&quot;
macro_line|#include &quot;ibm_emac_rgmii.h&quot;
macro_line|#include &quot;ibm_emac_zmii.h&quot;
macro_line|#include &quot;ibm_emac_mal.h&quot;
macro_line|#include &quot;ibm_emac_tah.h&quot;
macro_line|#ifndef CONFIG_IBM_EMAC_TXB
DECL|macro|NUM_TX_BUFF
mdefine_line|#define NUM_TX_BUFF&t;&t;64
DECL|macro|NUM_RX_BUFF
mdefine_line|#define NUM_RX_BUFF&t;&t;64
macro_line|#else
DECL|macro|NUM_TX_BUFF
mdefine_line|#define NUM_TX_BUFF&t;&t;CONFIG_IBM_EMAC_TXB
DECL|macro|NUM_RX_BUFF
mdefine_line|#define NUM_RX_BUFF&t;&t;CONFIG_IBM_EMAC_RXB
macro_line|#endif
multiline_comment|/* This does 16 byte alignment, exactly what we need.&n; * The packet length includes FCS, but we don&squot;t want to&n; * include that when passing upstream as it messes up&n; * bridging applications.&n; */
macro_line|#ifndef CONFIG_IBM_EMAC_SKBRES
DECL|macro|SKB_RES
mdefine_line|#define SKB_RES 2
macro_line|#else
DECL|macro|SKB_RES
mdefine_line|#define SKB_RES CONFIG_IBM_EMAC_SKBRES
macro_line|#endif
multiline_comment|/* Note about alignement. alloc_skb() returns a cache line&n; * aligned buffer. However, dev_alloc_skb() will add 16 more&n; * bytes and &quot;reserve&quot; them, so our buffer will actually end&n; * on a half cache line. What we do is to use directly&n; * alloc_skb, allocate 16 more bytes to match the total amount&n; * allocated by dev_alloc_skb(), but we don&squot;t reserve.&n; */
DECL|macro|MAX_NUM_BUF_DESC
mdefine_line|#define MAX_NUM_BUF_DESC&t;255
DECL|macro|DESC_BUF_SIZE
mdefine_line|#define DESC_BUF_SIZE&t;&t;4080&t;/* max 4096-16 */
DECL|macro|DESC_BUF_SIZE_REG
mdefine_line|#define DESC_BUF_SIZE_REG&t;(DESC_BUF_SIZE / 16)
multiline_comment|/* Transmitter timeout. */
DECL|macro|TX_TIMEOUT
mdefine_line|#define TX_TIMEOUT&t;&t;(2*HZ)
multiline_comment|/* MDIO latency delay */
DECL|macro|MDIO_DELAY
mdefine_line|#define MDIO_DELAY&t;&t;250
multiline_comment|/* Power managment shift registers */
DECL|macro|IBM_CPM_EMMII
mdefine_line|#define IBM_CPM_EMMII&t;0&t;/* Shift value for MII */
DECL|macro|IBM_CPM_EMRX
mdefine_line|#define IBM_CPM_EMRX&t;1&t;/* Shift value for recv */
DECL|macro|IBM_CPM_EMTX
mdefine_line|#define IBM_CPM_EMTX&t;2&t;/* Shift value for MAC */
DECL|macro|IBM_CPM_EMAC
mdefine_line|#define IBM_CPM_EMAC(x)&t;(((x)&gt;&gt;IBM_CPM_EMMII) | ((x)&gt;&gt;IBM_CPM_EMRX) | ((x)&gt;&gt;IBM_CPM_EMTX))
DECL|macro|ENET_HEADER_SIZE
mdefine_line|#define ENET_HEADER_SIZE&t;14
DECL|macro|ENET_FCS_SIZE
mdefine_line|#define ENET_FCS_SIZE&t;&t;4
DECL|macro|EMAC_MIN_FRAME
mdefine_line|#define EMAC_MIN_FRAME&t;&t;64
DECL|macro|EMAC_MAX_FRAME
mdefine_line|#define EMAC_MAX_FRAME&t;&t;9018
DECL|macro|EMAC_MIN_MTU
mdefine_line|#define EMAC_MIN_MTU&t;&t;(EMAC_MIN_FRAME - ENET_HEADER_SIZE - ENET_FCS_SIZE)
DECL|macro|EMAC_MAX_MTU
mdefine_line|#define EMAC_MAX_MTU&t;&t;(EMAC_MAX_FRAME - ENET_HEADER_SIZE - ENET_FCS_SIZE)
macro_line|#ifdef CONFIG_IBM_EMAC_ERRMSG
r_void
id|emac_serr_dump_0
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|emac_serr_dump_1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|emac_err_dump
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|em0isr
)paren
suffix:semicolon
r_void
id|emac_phy_dump
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_void
id|emac_desc_dump
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_void
id|emac_mac_dump
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_void
id|emac_mal_dump
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|emac_serr_dump_0
mdefine_line|#define emac_serr_dump_0(dev) do { } while (0)
DECL|macro|emac_serr_dump_1
mdefine_line|#define emac_serr_dump_1(dev) do { } while (0)
DECL|macro|emac_err_dump
mdefine_line|#define emac_err_dump(dev,x) do { } while (0)
DECL|macro|emac_phy_dump
mdefine_line|#define emac_phy_dump(dev) do { } while (0)
DECL|macro|emac_desc_dump
mdefine_line|#define emac_desc_dump(dev) do { } while (0)
DECL|macro|emac_mac_dump
mdefine_line|#define emac_mac_dump(dev) do { } while (0)
DECL|macro|emac_mal_dump
mdefine_line|#define emac_mal_dump(dev) do { } while (0)
macro_line|#endif
DECL|struct|ocp_enet_private
r_struct
id|ocp_enet_private
(brace
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
(braket
id|NUM_TX_BUFF
)braket
suffix:semicolon
DECL|member|rx_skb
r_struct
id|sk_buff
op_star
id|rx_skb
(braket
id|NUM_RX_BUFF
)braket
suffix:semicolon
DECL|member|tx_desc
r_struct
id|mal_descriptor
op_star
id|tx_desc
suffix:semicolon
DECL|member|rx_desc
r_struct
id|mal_descriptor
op_star
id|rx_desc
suffix:semicolon
DECL|member|rx_dirty
r_struct
id|mal_descriptor
op_star
id|rx_dirty
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|tx_cnt
r_int
id|tx_cnt
suffix:semicolon
DECL|member|rx_slot
r_int
id|rx_slot
suffix:semicolon
DECL|member|dirty_rx
r_int
id|dirty_rx
suffix:semicolon
DECL|member|tx_slot
r_int
id|tx_slot
suffix:semicolon
DECL|member|ack_slot
r_int
id|ack_slot
suffix:semicolon
DECL|member|rx_buffer_size
r_int
id|rx_buffer_size
suffix:semicolon
DECL|member|phy_mii
r_struct
id|mii_phy
id|phy_mii
suffix:semicolon
DECL|member|mii_phy_addr
r_int
id|mii_phy_addr
suffix:semicolon
DECL|member|want_autoneg
r_int
id|want_autoneg
suffix:semicolon
DECL|member|timer_ticks
r_int
id|timer_ticks
suffix:semicolon
DECL|member|link_timer
r_struct
id|timer_list
id|link_timer
suffix:semicolon
DECL|member|mdio_dev
r_struct
id|net_device
op_star
id|mdio_dev
suffix:semicolon
DECL|member|rgmii_dev
r_struct
id|ocp_device
op_star
id|rgmii_dev
suffix:semicolon
DECL|member|rgmii_input
r_int
id|rgmii_input
suffix:semicolon
DECL|member|zmii_dev
r_struct
id|ocp_device
op_star
id|zmii_dev
suffix:semicolon
DECL|member|zmii_input
r_int
id|zmii_input
suffix:semicolon
DECL|member|mal
r_struct
id|ibm_ocp_mal
op_star
id|mal
suffix:semicolon
DECL|member|mal_tx_chan
DECL|member|mal_rx_chan
r_int
id|mal_tx_chan
comma
id|mal_rx_chan
suffix:semicolon
DECL|member|commac
r_struct
id|mal_commac
id|commac
suffix:semicolon
DECL|member|tah_dev
r_struct
id|ocp_device
op_star
id|tah_dev
suffix:semicolon
DECL|member|opened
r_int
id|opened
suffix:semicolon
DECL|member|going_away
r_int
id|going_away
suffix:semicolon
DECL|member|wol_irq
r_int
id|wol_irq
suffix:semicolon
DECL|member|emacp
id|emac_t
op_star
id|emacp
suffix:semicolon
DECL|member|ocpdev
r_struct
id|ocp_device
op_star
id|ocpdev
suffix:semicolon
DECL|member|ndev
r_struct
id|net_device
op_star
id|ndev
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _IBM_EMAC_CORE_H_ */
eof
