multiline_comment|/*&n; * linux/mii.h: definitions for MII-compatible transceivers&n; * Originally drivers/net/sunhme.h.&n; *&n; * Copyright (C) 1996, 1999, 2001 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef __LINUX_MII_H__
DECL|macro|__LINUX_MII_H__
mdefine_line|#define __LINUX_MII_H__
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* Generic MII registers. */
DECL|macro|MII_BMCR
mdefine_line|#define MII_BMCR            0x00        /* Basic mode control register */
DECL|macro|MII_BMSR
mdefine_line|#define MII_BMSR            0x01        /* Basic mode status register  */
DECL|macro|MII_PHYSID1
mdefine_line|#define MII_PHYSID1         0x02        /* PHYS ID 1                   */
DECL|macro|MII_PHYSID2
mdefine_line|#define MII_PHYSID2         0x03        /* PHYS ID 2                   */
DECL|macro|MII_ADVERTISE
mdefine_line|#define MII_ADVERTISE       0x04        /* Advertisement control reg   */
DECL|macro|MII_LPA
mdefine_line|#define MII_LPA             0x05        /* Link partner ability reg    */
DECL|macro|MII_EXPANSION
mdefine_line|#define MII_EXPANSION       0x06        /* Expansion register          */
DECL|macro|MII_DCOUNTER
mdefine_line|#define MII_DCOUNTER        0x12        /* Disconnect counter          */
DECL|macro|MII_FCSCOUNTER
mdefine_line|#define MII_FCSCOUNTER      0x13        /* False carrier counter       */
DECL|macro|MII_NWAYTEST
mdefine_line|#define MII_NWAYTEST        0x14        /* N-way auto-neg test reg     */
DECL|macro|MII_RERRCOUNTER
mdefine_line|#define MII_RERRCOUNTER     0x15        /* Receive error counter       */
DECL|macro|MII_SREVISION
mdefine_line|#define MII_SREVISION       0x16        /* Silicon revision            */
DECL|macro|MII_RESV1
mdefine_line|#define MII_RESV1           0x17        /* Reserved...                 */
DECL|macro|MII_LBRERROR
mdefine_line|#define MII_LBRERROR        0x18        /* Lpback, rx, bypass error    */
DECL|macro|MII_PHYADDR
mdefine_line|#define MII_PHYADDR         0x19        /* PHY address                 */
DECL|macro|MII_RESV2
mdefine_line|#define MII_RESV2           0x1a        /* Reserved...                 */
DECL|macro|MII_TPISTATUS
mdefine_line|#define MII_TPISTATUS       0x1b        /* TPI status for 10mbps       */
DECL|macro|MII_NCONFIG
mdefine_line|#define MII_NCONFIG         0x1c        /* Network interface config    */
multiline_comment|/* Basic mode control register. */
DECL|macro|BMCR_RESV
mdefine_line|#define BMCR_RESV               0x007f  /* Unused...                   */
DECL|macro|BMCR_CTST
mdefine_line|#define BMCR_CTST               0x0080  /* Collision test              */
DECL|macro|BMCR_FULLDPLX
mdefine_line|#define BMCR_FULLDPLX           0x0100  /* Full duplex                 */
DECL|macro|BMCR_ANRESTART
mdefine_line|#define BMCR_ANRESTART          0x0200  /* Auto negotiation restart    */
DECL|macro|BMCR_ISOLATE
mdefine_line|#define BMCR_ISOLATE            0x0400  /* Disconnect DP83840 from MII */
DECL|macro|BMCR_PDOWN
mdefine_line|#define BMCR_PDOWN              0x0800  /* Powerdown the DP83840       */
DECL|macro|BMCR_ANENABLE
mdefine_line|#define BMCR_ANENABLE           0x1000  /* Enable auto negotiation     */
DECL|macro|BMCR_SPEED100
mdefine_line|#define BMCR_SPEED100           0x2000  /* Select 100Mbps              */
DECL|macro|BMCR_LOOPBACK
mdefine_line|#define BMCR_LOOPBACK           0x4000  /* TXD loopback bits           */
DECL|macro|BMCR_RESET
mdefine_line|#define BMCR_RESET              0x8000  /* Reset the DP83840           */
multiline_comment|/* Basic mode status register. */
DECL|macro|BMSR_ERCAP
mdefine_line|#define BMSR_ERCAP              0x0001  /* Ext-reg capability          */
DECL|macro|BMSR_JCD
mdefine_line|#define BMSR_JCD                0x0002  /* Jabber detected             */
DECL|macro|BMSR_LSTATUS
mdefine_line|#define BMSR_LSTATUS            0x0004  /* Link status                 */
DECL|macro|BMSR_ANEGCAPABLE
mdefine_line|#define BMSR_ANEGCAPABLE        0x0008  /* Able to do auto-negotiation */
DECL|macro|BMSR_RFAULT
mdefine_line|#define BMSR_RFAULT             0x0010  /* Remote fault detected       */
DECL|macro|BMSR_ANEGCOMPLETE
mdefine_line|#define BMSR_ANEGCOMPLETE       0x0020  /* Auto-negotiation complete   */
DECL|macro|BMSR_RESV
mdefine_line|#define BMSR_RESV               0x07c0  /* Unused...                   */
DECL|macro|BMSR_10HALF
mdefine_line|#define BMSR_10HALF             0x0800  /* Can do 10mbps, half-duplex  */
DECL|macro|BMSR_10FULL
mdefine_line|#define BMSR_10FULL             0x1000  /* Can do 10mbps, full-duplex  */
DECL|macro|BMSR_100HALF
mdefine_line|#define BMSR_100HALF            0x2000  /* Can do 100mbps, half-duplex */
DECL|macro|BMSR_100FULL
mdefine_line|#define BMSR_100FULL            0x4000  /* Can do 100mbps, full-duplex */
DECL|macro|BMSR_100BASE4
mdefine_line|#define BMSR_100BASE4           0x8000  /* Can do 100mbps, 4k packets  */
multiline_comment|/* Advertisement control register. */
DECL|macro|ADVERTISE_SLCT
mdefine_line|#define ADVERTISE_SLCT          0x001f  /* Selector bits               */
DECL|macro|ADVERTISE_CSMA
mdefine_line|#define ADVERTISE_CSMA          0x0001  /* Only selector supported     */
DECL|macro|ADVERTISE_10HALF
mdefine_line|#define ADVERTISE_10HALF        0x0020  /* Try for 10mbps half-duplex  */
DECL|macro|ADVERTISE_10FULL
mdefine_line|#define ADVERTISE_10FULL        0x0040  /* Try for 10mbps full-duplex  */
DECL|macro|ADVERTISE_100HALF
mdefine_line|#define ADVERTISE_100HALF       0x0080  /* Try for 100mbps half-duplex */
DECL|macro|ADVERTISE_100FULL
mdefine_line|#define ADVERTISE_100FULL       0x0100  /* Try for 100mbps full-duplex */
DECL|macro|ADVERTISE_100BASE4
mdefine_line|#define ADVERTISE_100BASE4      0x0200  /* Try for 100mbps 4k packets  */
DECL|macro|ADVERTISE_RESV
mdefine_line|#define ADVERTISE_RESV          0x1c00  /* Unused...                   */
DECL|macro|ADVERTISE_RFAULT
mdefine_line|#define ADVERTISE_RFAULT        0x2000  /* Say we can detect faults    */
DECL|macro|ADVERTISE_LPACK
mdefine_line|#define ADVERTISE_LPACK         0x4000  /* Ack link partners response  */
DECL|macro|ADVERTISE_NPAGE
mdefine_line|#define ADVERTISE_NPAGE         0x8000  /* Next page bit               */
DECL|macro|ADVERTISE_ALL
mdefine_line|#define ADVERTISE_ALL (ADVERTISE_10HALF | ADVERTISE_10FULL | &bslash;&n;                       ADVERTISE_100HALF | ADVERTISE_100FULL)
multiline_comment|/* Link partner ability register. */
DECL|macro|LPA_SLCT
mdefine_line|#define LPA_SLCT                0x001f  /* Same as advertise selector  */
DECL|macro|LPA_10HALF
mdefine_line|#define LPA_10HALF              0x0020  /* Can do 10mbps half-duplex   */
DECL|macro|LPA_10FULL
mdefine_line|#define LPA_10FULL              0x0040  /* Can do 10mbps full-duplex   */
DECL|macro|LPA_100HALF
mdefine_line|#define LPA_100HALF             0x0080  /* Can do 100mbps half-duplex  */
DECL|macro|LPA_100FULL
mdefine_line|#define LPA_100FULL             0x0100  /* Can do 100mbps full-duplex  */
DECL|macro|LPA_100BASE4
mdefine_line|#define LPA_100BASE4            0x0200  /* Can do 100mbps 4k packets   */
DECL|macro|LPA_RESV
mdefine_line|#define LPA_RESV                0x1c00  /* Unused...                   */
DECL|macro|LPA_RFAULT
mdefine_line|#define LPA_RFAULT              0x2000  /* Link partner faulted        */
DECL|macro|LPA_LPACK
mdefine_line|#define LPA_LPACK               0x4000  /* Link partner acked us       */
DECL|macro|LPA_NPAGE
mdefine_line|#define LPA_NPAGE               0x8000  /* Next page bit               */
DECL|macro|LPA_DUPLEX
mdefine_line|#define LPA_DUPLEX&t;&t;(LPA_10FULL | LPA_100FULL)
DECL|macro|LPA_100
mdefine_line|#define LPA_100&t;&t;&t;(LPA_100FULL | LPA_100HALF | LPA_100BASE4)
multiline_comment|/* Expansion register for auto-negotiation. */
DECL|macro|EXPANSION_NWAY
mdefine_line|#define EXPANSION_NWAY          0x0001  /* Can do N-way auto-nego      */
DECL|macro|EXPANSION_LCWP
mdefine_line|#define EXPANSION_LCWP          0x0002  /* Got new RX page code word   */
DECL|macro|EXPANSION_ENABLENPAGE
mdefine_line|#define EXPANSION_ENABLENPAGE   0x0004  /* This enables npage words    */
DECL|macro|EXPANSION_NPCAPABLE
mdefine_line|#define EXPANSION_NPCAPABLE     0x0008  /* Link partner supports npage */
DECL|macro|EXPANSION_MFAULTS
mdefine_line|#define EXPANSION_MFAULTS       0x0010  /* Multiple faults detected    */
DECL|macro|EXPANSION_RESV
mdefine_line|#define EXPANSION_RESV          0xffe0  /* Unused...                   */
multiline_comment|/* N-way test register. */
DECL|macro|NWAYTEST_RESV1
mdefine_line|#define NWAYTEST_RESV1          0x00ff  /* Unused...                   */
DECL|macro|NWAYTEST_LOOPBACK
mdefine_line|#define NWAYTEST_LOOPBACK       0x0100  /* Enable loopback for N-way   */
DECL|macro|NWAYTEST_RESV2
mdefine_line|#define NWAYTEST_RESV2          0xfe00  /* Unused...                   */
multiline_comment|/* This structure is used in all SIOCxMIIxxx ioctl calls */
DECL|struct|mii_ioctl_data
r_struct
id|mii_ioctl_data
(brace
DECL|member|phy_id
id|u16
id|phy_id
suffix:semicolon
DECL|member|reg_num
id|u16
id|reg_num
suffix:semicolon
DECL|member|val_in
id|u16
id|val_in
suffix:semicolon
DECL|member|val_out
id|u16
id|val_out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * mii_nway_result&n; * @negotiated: value of MII ANAR and&squot;d with ANLPAR&n; *&n; * Given a set of MII abilities, check each bit and returns the&n; * currently supported media, in the priority order defined by&n; * IEEE 802.3u.  We use LPA_xxx constants but note this is not the&n; * value of LPA solely, as described above.&n; *&n; * The one exception to IEEE 802.3u is that 100baseT4 is placed&n; * between 100T-full and 100T-half.  If your phy does not support&n; * 100T4 this is fine.  If your phy places 100T4 elsewhere in the&n; * priority order, you will need to roll your own function.&n; */
DECL|function|mii_nway_result
r_static
r_inline
r_int
r_int
id|mii_nway_result
(paren
r_int
r_int
id|negotiated
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|negotiated
op_amp
id|LPA_100FULL
)paren
id|ret
op_assign
id|LPA_100FULL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|negotiated
op_amp
id|LPA_100BASE4
)paren
id|ret
op_assign
id|LPA_100BASE4
suffix:semicolon
r_else
r_if
c_cond
(paren
id|negotiated
op_amp
id|LPA_100HALF
)paren
id|ret
op_assign
id|LPA_100HALF
suffix:semicolon
r_else
r_if
c_cond
(paren
id|negotiated
op_amp
id|LPA_10FULL
)paren
id|ret
op_assign
id|LPA_10FULL
suffix:semicolon
r_else
id|ret
op_assign
id|LPA_10HALF
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * mii_duplex&n; * @duplex_lock: Non-zero if duplex is locked at full&n; * @negotiated: value of MII ANAR and&squot;d with ANLPAR&n; *&n; * A small helper function for a common case.  Returns one&n; * if the media is operating or locked at full duplex, and&n; * returns zero otherwise.&n; */
DECL|function|mii_duplex
r_static
r_inline
r_int
r_int
id|mii_duplex
(paren
r_int
r_int
id|duplex_lock
comma
r_int
r_int
id|negotiated
)paren
(brace
r_if
c_cond
(paren
id|duplex_lock
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|mii_nway_result
c_func
(paren
id|negotiated
)paren
op_amp
id|LPA_DUPLEX
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __LINUX_MII_H__ */
eof
