macro_line|#ifndef FEC_8XX_H
DECL|macro|FEC_8XX_H
mdefine_line|#define FEC_8XX_H
macro_line|#include &lt;linux/mii.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* HW info */
multiline_comment|/* CRC polynomium used by the FEC for the multicast group filtering */
DECL|macro|FEC_CRC_POLY
mdefine_line|#define FEC_CRC_POLY   0x04C11DB7
DECL|macro|MII_ADVERTISE_HALF
mdefine_line|#define MII_ADVERTISE_HALF&t;(ADVERTISE_100HALF | &bslash;&n;&t;&t;&t;&t; ADVERTISE_10HALF | ADVERTISE_CSMA)
DECL|macro|MII_ADVERTISE_ALL
mdefine_line|#define MII_ADVERTISE_ALL&t;(ADVERTISE_100FULL | &bslash;&n;&t;&t;&t;&t; ADVERTISE_10FULL | MII_ADVERTISE_HALF)
multiline_comment|/* Interrupt events/masks.&n;*/
DECL|macro|FEC_ENET_HBERR
mdefine_line|#define FEC_ENET_HBERR&t;0x80000000U&t;/* Heartbeat error          */
DECL|macro|FEC_ENET_BABR
mdefine_line|#define FEC_ENET_BABR&t;0x40000000U&t;/* Babbling receiver        */
DECL|macro|FEC_ENET_BABT
mdefine_line|#define FEC_ENET_BABT&t;0x20000000U&t;/* Babbling transmitter     */
DECL|macro|FEC_ENET_GRA
mdefine_line|#define FEC_ENET_GRA&t;0x10000000U&t;/* Graceful stop complete   */
DECL|macro|FEC_ENET_TXF
mdefine_line|#define FEC_ENET_TXF&t;0x08000000U&t;/* Full frame transmitted   */
DECL|macro|FEC_ENET_TXB
mdefine_line|#define FEC_ENET_TXB&t;0x04000000U&t;/* A buffer was transmitted */
DECL|macro|FEC_ENET_RXF
mdefine_line|#define FEC_ENET_RXF&t;0x02000000U&t;/* Full frame received      */
DECL|macro|FEC_ENET_RXB
mdefine_line|#define FEC_ENET_RXB&t;0x01000000U&t;/* A buffer was received    */
DECL|macro|FEC_ENET_MII
mdefine_line|#define FEC_ENET_MII&t;0x00800000U&t;/* MII interrupt            */
DECL|macro|FEC_ENET_EBERR
mdefine_line|#define FEC_ENET_EBERR&t;0x00400000U&t;/* SDMA bus error           */
DECL|macro|FEC_ECNTRL_PINMUX
mdefine_line|#define FEC_ECNTRL_PINMUX&t;0x00000004
DECL|macro|FEC_ECNTRL_ETHER_EN
mdefine_line|#define FEC_ECNTRL_ETHER_EN&t;0x00000002
DECL|macro|FEC_ECNTRL_RESET
mdefine_line|#define FEC_ECNTRL_RESET&t;0x00000001
DECL|macro|FEC_RCNTRL_BC_REJ
mdefine_line|#define FEC_RCNTRL_BC_REJ&t;0x00000010
DECL|macro|FEC_RCNTRL_PROM
mdefine_line|#define FEC_RCNTRL_PROM&t;&t;0x00000008
DECL|macro|FEC_RCNTRL_MII_MODE
mdefine_line|#define FEC_RCNTRL_MII_MODE&t;0x00000004
DECL|macro|FEC_RCNTRL_DRT
mdefine_line|#define FEC_RCNTRL_DRT&t;&t;0x00000002
DECL|macro|FEC_RCNTRL_LOOP
mdefine_line|#define FEC_RCNTRL_LOOP&t;&t;0x00000001
DECL|macro|FEC_TCNTRL_FDEN
mdefine_line|#define FEC_TCNTRL_FDEN&t;&t;0x00000004
DECL|macro|FEC_TCNTRL_HBC
mdefine_line|#define FEC_TCNTRL_HBC&t;&t;0x00000002
DECL|macro|FEC_TCNTRL_GTS
mdefine_line|#define FEC_TCNTRL_GTS&t;&t;0x00000001
multiline_comment|/* values for MII phy_status */
DECL|macro|PHY_CONF_ANE
mdefine_line|#define PHY_CONF_ANE&t;0x0001&t;/* 1 auto-negotiation enabled     */
DECL|macro|PHY_CONF_LOOP
mdefine_line|#define PHY_CONF_LOOP&t;0x0002&t;/* 1 loopback mode enabled        */
DECL|macro|PHY_CONF_SPMASK
mdefine_line|#define PHY_CONF_SPMASK&t;0x00f0&t;/* mask for speed                 */
DECL|macro|PHY_CONF_10HDX
mdefine_line|#define PHY_CONF_10HDX&t;0x0010&t;/* 10 Mbit half duplex supported  */
DECL|macro|PHY_CONF_10FDX
mdefine_line|#define PHY_CONF_10FDX&t;0x0020&t;/* 10 Mbit full duplex supported  */
DECL|macro|PHY_CONF_100HDX
mdefine_line|#define PHY_CONF_100HDX&t;0x0040&t;/* 100 Mbit half duplex supported */
DECL|macro|PHY_CONF_100FDX
mdefine_line|#define PHY_CONF_100FDX&t;0x0080&t;/* 100 Mbit full duplex supported */
DECL|macro|PHY_STAT_LINK
mdefine_line|#define PHY_STAT_LINK&t;0x0100&t;/* 1 up - 0 down                  */
DECL|macro|PHY_STAT_FAULT
mdefine_line|#define PHY_STAT_FAULT&t;0x0200&t;/* 1 remote fault                 */
DECL|macro|PHY_STAT_ANC
mdefine_line|#define PHY_STAT_ANC&t;0x0400&t;/* 1 auto-negotiation complete    */
DECL|macro|PHY_STAT_SPMASK
mdefine_line|#define PHY_STAT_SPMASK&t;0xf000&t;/* mask for speed                 */
DECL|macro|PHY_STAT_10HDX
mdefine_line|#define PHY_STAT_10HDX&t;0x1000&t;/* 10 Mbit half duplex selected   */
DECL|macro|PHY_STAT_10FDX
mdefine_line|#define PHY_STAT_10FDX&t;0x2000&t;/* 10 Mbit full duplex selected   */
DECL|macro|PHY_STAT_100HDX
mdefine_line|#define PHY_STAT_100HDX&t;0x4000&t;/* 100 Mbit half duplex selected  */
DECL|macro|PHY_STAT_100FDX
mdefine_line|#define PHY_STAT_100FDX&t;0x8000&t;/* 100 Mbit full duplex selected  */
DECL|struct|phy_info
r_typedef
r_struct
id|phy_info
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|startup
r_void
(paren
op_star
id|startup
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|shutdown
r_void
(paren
op_star
id|shutdown
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|ack_int
r_void
(paren
op_star
id|ack_int
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|typedef|phy_info_t
)brace
id|phy_info_t
suffix:semicolon
multiline_comment|/* The FEC stores dest/src/type, data, and checksum for receive packets.&n; */
DECL|macro|MAX_MTU
mdefine_line|#define MAX_MTU 1508&t;&t;/* Allow fullsized pppoe packets over VLAN */
DECL|macro|MIN_MTU
mdefine_line|#define MIN_MTU 46&t;&t;/* this is data size */
DECL|macro|CRC_LEN
mdefine_line|#define CRC_LEN 4
DECL|macro|PKT_MAXBUF_SIZE
mdefine_line|#define PKT_MAXBUF_SIZE&t;&t;(MAX_MTU+ETH_HLEN+CRC_LEN)
DECL|macro|PKT_MINBUF_SIZE
mdefine_line|#define PKT_MINBUF_SIZE&t;&t;(MIN_MTU+ETH_HLEN+CRC_LEN)
multiline_comment|/* Must be a multiple of 4 */
DECL|macro|PKT_MAXBLR_SIZE
mdefine_line|#define PKT_MAXBLR_SIZE&t;&t;((PKT_MAXBUF_SIZE+3) &amp; ~3)
multiline_comment|/* This is needed so that invalidate_xxx wont invalidate too much */
DECL|macro|ENET_RX_FRSIZE
mdefine_line|#define ENET_RX_FRSIZE&t;&t;L1_CACHE_ALIGN(PKT_MAXBUF_SIZE)
multiline_comment|/* platform interface */
DECL|struct|fec_platform_info
r_struct
id|fec_platform_info
(brace
DECL|member|fec_no
r_int
id|fec_no
suffix:semicolon
multiline_comment|/* FEC index                  */
DECL|member|use_mdio
r_int
id|use_mdio
suffix:semicolon
multiline_comment|/* use external MII           */
DECL|member|phy_addr
r_int
id|phy_addr
suffix:semicolon
multiline_comment|/* the phy address            */
DECL|member|fec_irq
DECL|member|phy_irq
r_int
id|fec_irq
comma
id|phy_irq
suffix:semicolon
multiline_comment|/* the irq for the controller */
DECL|member|rx_ring
DECL|member|tx_ring
r_int
id|rx_ring
comma
id|tx_ring
suffix:semicolon
multiline_comment|/* number of buffers on rx    */
DECL|member|sys_clk
r_int
id|sys_clk
suffix:semicolon
multiline_comment|/* system clock               */
DECL|member|macaddr
id|__u8
id|macaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* mac address                */
DECL|member|rx_copybreak
r_int
id|rx_copybreak
suffix:semicolon
multiline_comment|/* limit we copy small frames */
DECL|member|use_napi
r_int
id|use_napi
suffix:semicolon
multiline_comment|/* use NAPI                   */
DECL|member|napi_weight
r_int
id|napi_weight
suffix:semicolon
multiline_comment|/* NAPI weight                */
)brace
suffix:semicolon
multiline_comment|/* forward declaration */
r_struct
id|fec
suffix:semicolon
DECL|struct|fec_enet_private
r_struct
id|fec_enet_private
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* during all ops except TX pckt processing */
DECL|member|tx_lock
id|spinlock_t
id|tx_lock
suffix:semicolon
multiline_comment|/* during fec_start_xmit and fec_tx         */
DECL|member|fecno
r_int
id|fecno
suffix:semicolon
DECL|member|fecp
r_struct
id|fec
op_star
id|fecp
suffix:semicolon
DECL|member|fpi
r_const
r_struct
id|fec_platform_info
op_star
id|fpi
suffix:semicolon
DECL|member|rx_ring
DECL|member|tx_ring
r_int
id|rx_ring
comma
id|tx_ring
suffix:semicolon
DECL|member|ring_mem_addr
id|dma_addr_t
id|ring_mem_addr
suffix:semicolon
DECL|member|ring_base
r_void
op_star
id|ring_base
suffix:semicolon
DECL|member|rx_skbuff
r_struct
id|sk_buff
op_star
op_star
id|rx_skbuff
suffix:semicolon
DECL|member|tx_skbuff
r_struct
id|sk_buff
op_star
op_star
id|tx_skbuff
suffix:semicolon
DECL|member|rx_bd_base
id|cbd_t
op_star
id|rx_bd_base
suffix:semicolon
multiline_comment|/* Address of Rx and Tx buffers.    */
DECL|member|tx_bd_base
id|cbd_t
op_star
id|tx_bd_base
suffix:semicolon
DECL|member|dirty_tx
id|cbd_t
op_star
id|dirty_tx
suffix:semicolon
multiline_comment|/* ring entries to be free()ed.     */
DECL|member|cur_rx
id|cbd_t
op_star
id|cur_rx
suffix:semicolon
DECL|member|cur_tx
id|cbd_t
op_star
id|cur_tx
suffix:semicolon
DECL|member|tx_free
r_int
id|tx_free
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|phy_timer_list
r_struct
id|timer_list
id|phy_timer_list
suffix:semicolon
DECL|member|phy
r_const
r_struct
id|phy_info
op_star
id|phy
suffix:semicolon
DECL|member|fec_phy_speed
r_int
r_int
id|fec_phy_speed
suffix:semicolon
DECL|member|msg_enable
id|__u32
id|msg_enable
suffix:semicolon
DECL|member|mii_if
r_struct
id|mii_if_info
id|mii_if
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/***************************************************************************/
r_void
id|fec_restart
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|duplex
comma
r_int
id|speed
)paren
suffix:semicolon
r_void
id|fec_stop
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/***************************************************************************/
r_int
id|fec_mii_read
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|phy_id
comma
r_int
id|location
)paren
suffix:semicolon
r_void
id|fec_mii_write
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|phy_id
comma
r_int
id|location
comma
r_int
id|value
)paren
suffix:semicolon
r_int
id|fec_mii_phy_id_detect
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|fec_mii_startup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|fec_mii_shutdown
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|fec_mii_ack_int
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|fec_mii_link_status_change_check
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|init_media
)paren
suffix:semicolon
multiline_comment|/***************************************************************************/
DECL|macro|FEC1_NO
mdefine_line|#define FEC1_NO&t;0x00
DECL|macro|FEC2_NO
mdefine_line|#define FEC2_NO&t;0x01
DECL|macro|FEC3_NO
mdefine_line|#define FEC3_NO&t;0x02
r_int
id|fec_8xx_init_one
c_func
(paren
r_const
r_struct
id|fec_platform_info
op_star
id|fpi
comma
r_struct
id|net_device
op_star
op_star
id|devp
)paren
suffix:semicolon
r_int
id|fec_8xx_cleanup_one
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/***************************************************************************/
DECL|macro|DRV_MODULE_NAME
mdefine_line|#define DRV_MODULE_NAME&t;&t;&quot;fec_8xx&quot;
DECL|macro|PFX
mdefine_line|#define PFX DRV_MODULE_NAME&t;&quot;: &quot;
DECL|macro|DRV_MODULE_VERSION
mdefine_line|#define DRV_MODULE_VERSION&t;&quot;0.1&quot;
DECL|macro|DRV_MODULE_RELDATE
mdefine_line|#define DRV_MODULE_RELDATE&t;&quot;May 6, 2004&quot;
multiline_comment|/***************************************************************************/
r_int
id|fec_8xx_platform_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|fec_8xx_platform_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/***************************************************************************/
multiline_comment|/* FEC access macros */
macro_line|#if defined(CONFIG_8xx)
multiline_comment|/* for a 8xx __raw_xxx&squot;s are sufficient */
DECL|macro|__fec_out32
mdefine_line|#define __fec_out32(addr, x)&t;__raw_writel(x, addr)
DECL|macro|__fec_out16
mdefine_line|#define __fec_out16(addr, x)&t;__raw_writew(x, addr)
DECL|macro|__fec_in32
mdefine_line|#define __fec_in32(addr)&t;__raw_readl(addr)
DECL|macro|__fec_in16
mdefine_line|#define __fec_in16(addr)&t;__raw_readw(addr)
macro_line|#else
multiline_comment|/* for others play it safe */
DECL|macro|__fec_out32
mdefine_line|#define __fec_out32(addr, x)&t;out_be32(addr, x)
DECL|macro|__fec_out16
mdefine_line|#define __fec_out16(addr, x)&t;out_be16(addr, x)
DECL|macro|__fec_in32
mdefine_line|#define __fec_in32(addr)&t;in_be32(addr)
DECL|macro|__fec_in16
mdefine_line|#define __fec_in16(addr)&t;in_be16(addr)
macro_line|#endif
multiline_comment|/* write */
DECL|macro|FW
mdefine_line|#define FW(_fecp, _reg, _v) __fec_out32(&amp;(_fecp)-&gt;fec_ ## _reg, (_v))
multiline_comment|/* read */
DECL|macro|FR
mdefine_line|#define FR(_fecp, _reg)&t;__fec_in32(&amp;(_fecp)-&gt;fec_ ## _reg)
multiline_comment|/* set bits */
DECL|macro|FS
mdefine_line|#define FS(_fecp, _reg, _v) FW(_fecp, _reg, FR(_fecp, _reg) | (_v))
multiline_comment|/* clear bits */
DECL|macro|FC
mdefine_line|#define FC(_fecp, _reg, _v) FW(_fecp, _reg, FR(_fecp, _reg) &amp; ~(_v))
multiline_comment|/* buffer descriptor access macros */
multiline_comment|/* write */
DECL|macro|CBDW_SC
mdefine_line|#define CBDW_SC(_cbd, _sc) &t;&t;__fec_out16(&amp;(_cbd)-&gt;cbd_sc, (_sc))
DECL|macro|CBDW_DATLEN
mdefine_line|#define CBDW_DATLEN(_cbd, _datlen)&t;__fec_out16(&amp;(_cbd)-&gt;cbd_datlen, (_datlen))
DECL|macro|CBDW_BUFADDR
mdefine_line|#define CBDW_BUFADDR(_cbd, _bufaddr)&t;__fec_out32(&amp;(_cbd)-&gt;cbd_bufaddr, (_bufaddr))
multiline_comment|/* read */
DECL|macro|CBDR_SC
mdefine_line|#define CBDR_SC(_cbd) &t;&t;&t;__fec_in16(&amp;(_cbd)-&gt;cbd_sc)
DECL|macro|CBDR_DATLEN
mdefine_line|#define CBDR_DATLEN(_cbd)&t;&t;__fec_in16(&amp;(_cbd)-&gt;cbd_datlen)
DECL|macro|CBDR_BUFADDR
mdefine_line|#define CBDR_BUFADDR(_cbd)&t;&t;__fec_in32(&amp;(_cbd)-&gt;cbd_bufaddr)
multiline_comment|/* set bits */
DECL|macro|CBDS_SC
mdefine_line|#define CBDS_SC(_cbd, _sc) &t;&t;CBDW_SC(_cbd, CBDR_SC(_cbd) | (_sc))
multiline_comment|/* clear bits */
DECL|macro|CBDC_SC
mdefine_line|#define CBDC_SC(_cbd, _sc) &t;&t;CBDW_SC(_cbd, CBDR_SC(_cbd) &amp; ~(_sc))
multiline_comment|/***************************************************************************/
macro_line|#endif
eof
