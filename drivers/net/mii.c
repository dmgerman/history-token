multiline_comment|/*&n;&n;&t;mii.c: MII interface library&n;&n;&t;Maintained by Jeff Garzik &lt;jgarzik@mandrakesoft.com&gt;&n;&t;Copyright 2001,2002 Jeff Garzik&n;&n;&t;Various code came from myson803.c and other files by&n;&t;Donald Becker.  Copyright:&n;&n;&t;&t;Written 1998-2002 by Donald Becker.&n;&n;&t;&t;This software may be used and distributed according&n;&t;&t;to the terms of the GNU General Public License (GPL),&n;&t;&t;incorporated herein by reference.  Drivers based on&n;&t;&t;or derived from this code fall under the GPL and must&n;&t;&t;retain the authorship, copyright and license notice.&n;&t;&t;This file is not a complete program and may only be&n;&t;&t;used when the entire operating system is licensed&n;&t;&t;under the GPL.&n;&n;&t;&t;The author may be reached as becker@scyld.com, or C/O&n;&t;&t;Scyld Computing Corporation&n;&t;&t;410 Severn Ave., Suite 210&n;&t;&t;Annapolis MD 21403&n;&n;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/ethtool.h&gt;
macro_line|#include &lt;linux/mii.h&gt;
DECL|function|mii_ethtool_gset
r_int
id|mii_ethtool_gset
c_func
(paren
r_struct
id|mii_if_info
op_star
id|mii
comma
r_struct
id|ethtool_cmd
op_star
id|ecmd
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|mii-&gt;dev
suffix:semicolon
id|u32
id|advert
comma
id|bmcr
comma
id|lpa
comma
id|nego
suffix:semicolon
id|ecmd-&gt;supported
op_assign
(paren
id|SUPPORTED_10baseT_Half
op_or
id|SUPPORTED_10baseT_Full
op_or
id|SUPPORTED_100baseT_Half
op_or
id|SUPPORTED_100baseT_Full
op_or
id|SUPPORTED_Autoneg
op_or
id|SUPPORTED_TP
op_or
id|SUPPORTED_MII
)paren
suffix:semicolon
multiline_comment|/* only supports twisted-pair */
id|ecmd-&gt;port
op_assign
id|PORT_MII
suffix:semicolon
multiline_comment|/* only supports internal transceiver */
id|ecmd-&gt;transceiver
op_assign
id|XCVR_INTERNAL
suffix:semicolon
multiline_comment|/* this isn&squot;t fully supported at higher layers */
id|ecmd-&gt;phy_address
op_assign
id|mii-&gt;phy_id
suffix:semicolon
id|ecmd-&gt;advertising
op_assign
id|ADVERTISED_TP
op_or
id|ADVERTISED_MII
suffix:semicolon
id|advert
op_assign
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|dev
comma
id|mii-&gt;phy_id
comma
id|MII_ADVERTISE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|advert
op_amp
id|ADVERTISE_10HALF
)paren
id|ecmd-&gt;advertising
op_or_assign
id|ADVERTISED_10baseT_Half
suffix:semicolon
r_if
c_cond
(paren
id|advert
op_amp
id|ADVERTISE_10FULL
)paren
id|ecmd-&gt;advertising
op_or_assign
id|ADVERTISED_10baseT_Full
suffix:semicolon
r_if
c_cond
(paren
id|advert
op_amp
id|ADVERTISE_100HALF
)paren
id|ecmd-&gt;advertising
op_or_assign
id|ADVERTISED_100baseT_Half
suffix:semicolon
r_if
c_cond
(paren
id|advert
op_amp
id|ADVERTISE_100FULL
)paren
id|ecmd-&gt;advertising
op_or_assign
id|ADVERTISED_100baseT_Full
suffix:semicolon
id|bmcr
op_assign
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|dev
comma
id|mii-&gt;phy_id
comma
id|MII_BMCR
)paren
suffix:semicolon
id|lpa
op_assign
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|dev
comma
id|mii-&gt;phy_id
comma
id|MII_LPA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bmcr
op_amp
id|BMCR_ANENABLE
)paren
(brace
id|ecmd-&gt;advertising
op_or_assign
id|ADVERTISED_Autoneg
suffix:semicolon
id|ecmd-&gt;autoneg
op_assign
id|AUTONEG_ENABLE
suffix:semicolon
id|nego
op_assign
id|mii_nway_result
c_func
(paren
id|advert
op_amp
id|lpa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nego
op_eq
id|LPA_100FULL
op_logical_or
id|nego
op_eq
id|LPA_100HALF
)paren
id|ecmd-&gt;speed
op_assign
id|SPEED_100
suffix:semicolon
r_else
id|ecmd-&gt;speed
op_assign
id|SPEED_10
suffix:semicolon
r_if
c_cond
(paren
id|nego
op_eq
id|LPA_100FULL
op_logical_or
id|nego
op_eq
id|LPA_10FULL
)paren
(brace
id|ecmd-&gt;duplex
op_assign
id|DUPLEX_FULL
suffix:semicolon
id|mii-&gt;full_duplex
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|ecmd-&gt;duplex
op_assign
id|DUPLEX_HALF
suffix:semicolon
id|mii-&gt;full_duplex
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|ecmd-&gt;autoneg
op_assign
id|AUTONEG_DISABLE
suffix:semicolon
id|ecmd-&gt;speed
op_assign
(paren
id|bmcr
op_amp
id|BMCR_SPEED100
)paren
ques
c_cond
id|SPEED_100
suffix:colon
id|SPEED_10
suffix:semicolon
id|ecmd-&gt;duplex
op_assign
(paren
id|bmcr
op_amp
id|BMCR_FULLDPLX
)paren
ques
c_cond
id|DUPLEX_FULL
suffix:colon
id|DUPLEX_HALF
suffix:semicolon
)brace
multiline_comment|/* ignore maxtxpkt, maxrxpkt for now */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mii_ethtool_sset
r_int
id|mii_ethtool_sset
c_func
(paren
r_struct
id|mii_if_info
op_star
id|mii
comma
r_struct
id|ethtool_cmd
op_star
id|ecmd
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|mii-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;speed
op_ne
id|SPEED_10
op_logical_and
id|ecmd-&gt;speed
op_ne
id|SPEED_100
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;duplex
op_ne
id|DUPLEX_HALF
op_logical_and
id|ecmd-&gt;duplex
op_ne
id|DUPLEX_FULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;port
op_ne
id|PORT_MII
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;transceiver
op_ne
id|XCVR_INTERNAL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;phy_address
op_ne
id|mii-&gt;phy_id
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;autoneg
op_ne
id|AUTONEG_DISABLE
op_logical_and
id|ecmd-&gt;autoneg
op_ne
id|AUTONEG_ENABLE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* ignore supported, maxtxpkt, maxrxpkt */
r_if
c_cond
(paren
id|ecmd-&gt;autoneg
op_eq
id|AUTONEG_ENABLE
)paren
(brace
id|u32
id|bmcr
comma
id|advert
comma
id|tmp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ecmd-&gt;advertising
op_amp
(paren
id|ADVERTISED_10baseT_Half
op_or
id|ADVERTISED_10baseT_Full
op_or
id|ADVERTISED_100baseT_Half
op_or
id|ADVERTISED_100baseT_Full
)paren
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* advertise only what has been requested */
id|advert
op_assign
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|dev
comma
id|mii-&gt;phy_id
comma
id|MII_ADVERTISE
)paren
suffix:semicolon
id|tmp
op_assign
id|advert
op_amp
op_complement
(paren
id|ADVERTISE_ALL
op_or
id|ADVERTISE_100BASE4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ADVERTISED_10baseT_Half
)paren
id|tmp
op_or_assign
id|ADVERTISE_10HALF
suffix:semicolon
r_if
c_cond
(paren
id|ADVERTISED_10baseT_Full
)paren
id|tmp
op_or_assign
id|ADVERTISE_10FULL
suffix:semicolon
r_if
c_cond
(paren
id|ADVERTISED_100baseT_Half
)paren
id|tmp
op_or_assign
id|ADVERTISE_100HALF
suffix:semicolon
r_if
c_cond
(paren
id|ADVERTISED_100baseT_Full
)paren
id|tmp
op_or_assign
id|ADVERTISE_100FULL
suffix:semicolon
r_if
c_cond
(paren
id|advert
op_ne
id|tmp
)paren
(brace
id|mii
op_member_access_from_pointer
id|mdio_write
c_func
(paren
id|dev
comma
id|mii-&gt;phy_id
comma
id|MII_ADVERTISE
comma
id|tmp
)paren
suffix:semicolon
id|mii-&gt;advertising
op_assign
id|tmp
suffix:semicolon
)brace
multiline_comment|/* turn on autonegotiation, and force a renegotiate */
id|bmcr
op_assign
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|dev
comma
id|mii-&gt;phy_id
comma
id|MII_BMCR
)paren
suffix:semicolon
id|bmcr
op_or_assign
(paren
id|BMCR_ANENABLE
op_or
id|BMCR_ANRESTART
)paren
suffix:semicolon
id|mii
op_member_access_from_pointer
id|mdio_write
c_func
(paren
id|dev
comma
id|mii-&gt;phy_id
comma
id|MII_BMCR
comma
id|bmcr
)paren
suffix:semicolon
id|mii-&gt;force_media
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|u32
id|bmcr
comma
id|tmp
suffix:semicolon
multiline_comment|/* turn off auto negotiation, set speed and duplexity */
id|bmcr
op_assign
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|dev
comma
id|mii-&gt;phy_id
comma
id|MII_BMCR
)paren
suffix:semicolon
id|tmp
op_assign
id|bmcr
op_amp
op_complement
(paren
id|BMCR_ANENABLE
op_or
id|BMCR_SPEED100
op_or
id|BMCR_FULLDPLX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;speed
op_eq
id|SPEED_100
)paren
id|tmp
op_or_assign
id|BMCR_SPEED100
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;duplex
op_eq
id|DUPLEX_FULL
)paren
(brace
id|tmp
op_or_assign
id|BMCR_FULLDPLX
suffix:semicolon
id|mii-&gt;full_duplex
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|mii-&gt;full_duplex
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bmcr
op_ne
id|tmp
)paren
id|mii
op_member_access_from_pointer
id|mdio_write
c_func
(paren
id|dev
comma
id|mii-&gt;phy_id
comma
id|MII_BMCR
comma
id|tmp
)paren
suffix:semicolon
id|mii-&gt;force_media
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mii_link_ok
r_int
id|mii_link_ok
(paren
r_struct
id|mii_if_info
op_star
id|mii
)paren
(brace
multiline_comment|/* first, a dummy read, needed to latch some MII phys */
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|mii-&gt;dev
comma
id|mii-&gt;phy_id
comma
id|MII_BMSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|mii-&gt;dev
comma
id|mii-&gt;phy_id
comma
id|MII_BMSR
)paren
op_amp
id|BMSR_LSTATUS
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mii_nway_restart
r_int
id|mii_nway_restart
(paren
r_struct
id|mii_if_info
op_star
id|mii
)paren
(brace
r_int
id|bmcr
suffix:semicolon
r_int
id|r
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* if autoneg is off, it&squot;s an error */
id|bmcr
op_assign
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|mii-&gt;dev
comma
id|mii-&gt;phy_id
comma
id|MII_BMCR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bmcr
op_amp
id|BMCR_ANENABLE
)paren
(brace
id|bmcr
op_or_assign
id|BMCR_ANRESTART
suffix:semicolon
id|mii
op_member_access_from_pointer
id|mdio_write
c_func
(paren
id|mii-&gt;dev
comma
id|mii-&gt;phy_id
comma
id|MII_BMCR
comma
id|bmcr
)paren
suffix:semicolon
id|r
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
DECL|function|mii_check_link
r_void
id|mii_check_link
(paren
r_struct
id|mii_if_info
op_star
id|mii
)paren
(brace
r_if
c_cond
(paren
id|mii_link_ok
c_func
(paren
id|mii
)paren
)paren
id|netif_carrier_on
c_func
(paren
id|mii-&gt;dev
)paren
suffix:semicolon
r_else
id|netif_carrier_off
c_func
(paren
id|mii-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|mii_check_media
r_int
r_int
id|mii_check_media
(paren
r_struct
id|mii_if_info
op_star
id|mii
comma
r_int
r_int
id|ok_to_print
comma
r_int
r_int
id|init_media
)paren
(brace
r_int
r_int
id|old_carrier
comma
id|new_carrier
suffix:semicolon
r_int
id|advertise
comma
id|lpa
comma
id|media
comma
id|duplex
suffix:semicolon
multiline_comment|/* if forced media, go no further */
r_if
c_cond
(paren
id|mii-&gt;force_media
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* duplex did not change */
multiline_comment|/* check current and old link status */
id|old_carrier
op_assign
id|netif_carrier_ok
c_func
(paren
id|mii-&gt;dev
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|new_carrier
op_assign
(paren
r_int
r_int
)paren
id|mii_link_ok
c_func
(paren
id|mii
)paren
suffix:semicolon
multiline_comment|/* if carrier state did not change, this is a &quot;bounce&quot;,&n;&t; * just exit as everything is already set correctly&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|init_media
)paren
op_logical_and
(paren
id|old_carrier
op_eq
id|new_carrier
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* duplex did not change */
multiline_comment|/* no carrier, nothing much to do */
r_if
c_cond
(paren
op_logical_neg
id|new_carrier
)paren
(brace
id|netif_carrier_off
c_func
(paren
id|mii-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ok_to_print
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: link down&bslash;n&quot;
comma
id|mii-&gt;dev-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* duplex did not change */
)brace
multiline_comment|/*&n;&t; * we have carrier, see who&squot;s on the other end&n;&t; */
id|netif_carrier_on
c_func
(paren
id|mii-&gt;dev
)paren
suffix:semicolon
multiline_comment|/* get MII advertise and LPA values */
r_if
c_cond
(paren
(paren
op_logical_neg
id|init_media
)paren
op_logical_and
(paren
id|mii-&gt;advertising
)paren
)paren
id|advertise
op_assign
id|mii-&gt;advertising
suffix:semicolon
r_else
(brace
id|advertise
op_assign
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|mii-&gt;dev
comma
id|mii-&gt;phy_id
comma
id|MII_ADVERTISE
)paren
suffix:semicolon
id|mii-&gt;advertising
op_assign
id|advertise
suffix:semicolon
)brace
id|lpa
op_assign
id|mii
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|mii-&gt;dev
comma
id|mii-&gt;phy_id
comma
id|MII_LPA
)paren
suffix:semicolon
multiline_comment|/* figure out media and duplex from advertise and LPA values */
id|media
op_assign
id|mii_nway_result
c_func
(paren
id|lpa
op_amp
id|advertise
)paren
suffix:semicolon
id|duplex
op_assign
(paren
id|media
op_amp
id|ADVERTISE_FULL
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ok_to_print
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: link up, %sMbps, %s-duplex, lpa 0x%04X&bslash;n&quot;
comma
id|mii-&gt;dev-&gt;name
comma
id|media
op_amp
(paren
id|ADVERTISE_100FULL
op_or
id|ADVERTISE_100HALF
)paren
ques
c_cond
l_string|&quot;100&quot;
suffix:colon
l_string|&quot;10&quot;
comma
id|duplex
ques
c_cond
l_string|&quot;full&quot;
suffix:colon
l_string|&quot;half&quot;
comma
id|lpa
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|init_media
)paren
op_logical_or
(paren
id|mii-&gt;full_duplex
op_ne
id|duplex
)paren
)paren
(brace
id|mii-&gt;full_duplex
op_assign
id|duplex
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* duplex changed */
)brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* duplex did not change */
)brace
DECL|function|generic_mii_ioctl
r_int
id|generic_mii_ioctl
c_func
(paren
r_struct
id|mii_if_info
op_star
id|mii_if
comma
r_struct
id|mii_ioctl_data
op_star
id|mii_data
comma
r_int
id|cmd
comma
r_int
r_int
op_star
id|duplex_chg_out
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|duplex_changed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|duplex_chg_out
)paren
op_star
id|duplex_chg_out
op_assign
l_int|0
suffix:semicolon
id|mii_data-&gt;phy_id
op_and_assign
id|mii_if-&gt;phy_id_mask
suffix:semicolon
id|mii_data-&gt;reg_num
op_and_assign
id|mii_if-&gt;reg_num_mask
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCGMIIPHY
suffix:colon
id|mii_data-&gt;phy_id
op_assign
id|mii_if-&gt;phy_id
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|SIOCGMIIREG
suffix:colon
id|mii_data-&gt;val_out
op_assign
id|mii_if
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|mii_if-&gt;dev
comma
id|mii_data-&gt;phy_id
comma
id|mii_data-&gt;reg_num
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIOCSMIIREG
suffix:colon
(brace
id|u16
id|val
op_assign
id|mii_data-&gt;val_in
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|mii_data-&gt;phy_id
op_eq
id|mii_if-&gt;phy_id
)paren
(brace
r_switch
c_cond
(paren
id|mii_data-&gt;reg_num
)paren
(brace
r_case
id|MII_BMCR
suffix:colon
(brace
r_int
r_int
id|new_duplex
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
(paren
id|BMCR_RESET
op_or
id|BMCR_ANENABLE
)paren
)paren
id|mii_if-&gt;force_media
op_assign
l_int|1
suffix:semicolon
r_else
id|mii_if-&gt;force_media
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mii_if-&gt;force_media
op_logical_and
(paren
id|val
op_amp
id|BMCR_FULLDPLX
)paren
)paren
id|new_duplex
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|mii_if-&gt;full_duplex
op_ne
id|new_duplex
)paren
(brace
id|duplex_changed
op_assign
l_int|1
suffix:semicolon
id|mii_if-&gt;full_duplex
op_assign
id|new_duplex
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|MII_ADVERTISE
suffix:colon
id|mii_if-&gt;advertising
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* do nothing */
r_break
suffix:semicolon
)brace
)brace
id|mii_if
op_member_access_from_pointer
id|mdio_write
c_func
(paren
id|mii_if-&gt;dev
comma
id|mii_data-&gt;phy_id
comma
id|mii_data-&gt;reg_num
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|rc
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rc
op_eq
l_int|0
)paren
op_logical_and
(paren
id|duplex_chg_out
)paren
op_logical_and
(paren
id|duplex_changed
)paren
)paren
op_star
id|duplex_chg_out
op_assign
l_int|1
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Jeff Garzik &lt;jgarzik@mandrakesoft.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;MII hardware support library&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|mii_link_ok
id|EXPORT_SYMBOL
c_func
(paren
id|mii_link_ok
)paren
suffix:semicolon
DECL|variable|mii_nway_restart
id|EXPORT_SYMBOL
c_func
(paren
id|mii_nway_restart
)paren
suffix:semicolon
DECL|variable|mii_ethtool_gset
id|EXPORT_SYMBOL
c_func
(paren
id|mii_ethtool_gset
)paren
suffix:semicolon
DECL|variable|mii_ethtool_sset
id|EXPORT_SYMBOL
c_func
(paren
id|mii_ethtool_sset
)paren
suffix:semicolon
DECL|variable|mii_check_link
id|EXPORT_SYMBOL
c_func
(paren
id|mii_check_link
)paren
suffix:semicolon
DECL|variable|mii_check_media
id|EXPORT_SYMBOL
c_func
(paren
id|mii_check_media
)paren
suffix:semicolon
DECL|variable|generic_mii_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|generic_mii_ioctl
)paren
suffix:semicolon
eof
