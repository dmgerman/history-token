multiline_comment|/* &n; * drivers/net/gianfar_phy.c&n; *&n; * Gianfar Ethernet Driver -- PHY handling&n; * Driver for FEC on MPC8540 and TSEC on MPC8540/MPC8560&n; * Based on 8260_io/fcc_enet.c&n; *&n; * Author: Andy Fleming&n; * Maintainer: Kumar Gala (kumar.gala@freescale.com)&n; *&n; * Copyright (c) 2002-2004 Freescale Semiconductor, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/crc32.h&gt;
macro_line|#include &lt;linux/mii.h&gt;
macro_line|#include &quot;gianfar.h&quot;
macro_line|#include &quot;gianfar_phy.h&quot;
r_static
r_void
id|config_genmii_advert
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
r_static
r_void
id|genmii_setup_forced
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
r_static
r_void
id|genmii_restart_aneg
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
r_static
r_int
id|gbit_config_aneg
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
r_static
r_int
id|genmii_config_aneg
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
r_static
r_int
id|genmii_update_link
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
r_static
r_int
id|genmii_read_status
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
id|u16
id|phy_read
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
comma
id|u16
id|regnum
)paren
suffix:semicolon
r_void
id|phy_write
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
comma
id|u16
id|regnum
comma
id|u16
id|val
)paren
suffix:semicolon
multiline_comment|/* Write value to the PHY for this device to the register at regnum, */
multiline_comment|/* waiting until the write is done before it returns.  All PHY */
multiline_comment|/* configuration has to be done through the TSEC1 MIIM regs */
DECL|function|write_phy_reg
r_void
id|write_phy_reg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mii_id
comma
r_int
id|regnum
comma
r_int
id|value
)paren
(brace
r_struct
id|gfar_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|gfar
op_star
id|regbase
op_assign
id|priv-&gt;phyregs
suffix:semicolon
multiline_comment|/* Set the PHY address and the register address we want to write */
id|gfar_write
c_func
(paren
op_amp
id|regbase-&gt;miimadd
comma
(paren
id|mii_id
op_lshift
l_int|8
)paren
op_or
id|regnum
)paren
suffix:semicolon
multiline_comment|/* Write out the value we want */
id|gfar_write
c_func
(paren
op_amp
id|regbase-&gt;miimcon
comma
id|value
)paren
suffix:semicolon
multiline_comment|/* Wait for the transaction to finish */
r_while
c_loop
(paren
id|gfar_read
c_func
(paren
op_amp
id|regbase-&gt;miimind
)paren
op_amp
id|MIIMIND_BUSY
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Reads from register regnum in the PHY for device dev, */
multiline_comment|/* returning the value.  Clears miimcom first.  All PHY */
multiline_comment|/* configuration has to be done through the TSEC1 MIIM regs */
DECL|function|read_phy_reg
r_int
id|read_phy_reg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mii_id
comma
r_int
id|regnum
)paren
(brace
r_struct
id|gfar_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|gfar
op_star
id|regbase
op_assign
id|priv-&gt;phyregs
suffix:semicolon
id|u16
id|value
suffix:semicolon
multiline_comment|/* Set the PHY address and the register address we want to read */
id|gfar_write
c_func
(paren
op_amp
id|regbase-&gt;miimadd
comma
(paren
id|mii_id
op_lshift
l_int|8
)paren
op_or
id|regnum
)paren
suffix:semicolon
multiline_comment|/* Clear miimcom, and then initiate a read */
id|gfar_write
c_func
(paren
op_amp
id|regbase-&gt;miimcom
comma
l_int|0
)paren
suffix:semicolon
id|gfar_write
c_func
(paren
op_amp
id|regbase-&gt;miimcom
comma
id|MII_READ_COMMAND
)paren
suffix:semicolon
multiline_comment|/* Wait for the transaction to finish */
r_while
c_loop
(paren
id|gfar_read
c_func
(paren
op_amp
id|regbase-&gt;miimind
)paren
op_amp
(paren
id|MIIMIND_NOTVALID
op_or
id|MIIMIND_BUSY
)paren
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Grab the value of the register from miimstat */
id|value
op_assign
id|gfar_read
c_func
(paren
op_amp
id|regbase-&gt;miimstat
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|mii_clear_phy_interrupt
r_void
id|mii_clear_phy_interrupt
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
r_if
c_cond
(paren
id|mii_info-&gt;phyinfo-&gt;ack_interrupt
)paren
(brace
id|mii_info-&gt;phyinfo
op_member_access_from_pointer
id|ack_interrupt
c_func
(paren
id|mii_info
)paren
suffix:semicolon
)brace
)brace
DECL|function|mii_configure_phy_interrupt
r_void
id|mii_configure_phy_interrupt
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
comma
id|u32
id|interrupts
)paren
(brace
id|mii_info-&gt;interrupts
op_assign
id|interrupts
suffix:semicolon
r_if
c_cond
(paren
id|mii_info-&gt;phyinfo-&gt;config_intr
)paren
(brace
id|mii_info-&gt;phyinfo
op_member_access_from_pointer
id|config_intr
c_func
(paren
id|mii_info
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Writes MII_ADVERTISE with the appropriate values, after&n; * sanitizing advertise to make sure only supported features&n; * are advertised &n; */
DECL|function|config_genmii_advert
r_static
r_void
id|config_genmii_advert
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|u32
id|advertise
suffix:semicolon
id|u16
id|adv
suffix:semicolon
multiline_comment|/* Only allow advertising what this PHY supports */
id|mii_info-&gt;advertising
op_and_assign
id|mii_info-&gt;phyinfo-&gt;features
suffix:semicolon
id|advertise
op_assign
id|mii_info-&gt;advertising
suffix:semicolon
multiline_comment|/* Setup standard advertisement */
id|adv
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_ADVERTISE
)paren
suffix:semicolon
id|adv
op_and_assign
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
id|advertise
op_amp
id|ADVERTISED_10baseT_Half
)paren
id|adv
op_or_assign
id|ADVERTISE_10HALF
suffix:semicolon
r_if
c_cond
(paren
id|advertise
op_amp
id|ADVERTISED_10baseT_Full
)paren
id|adv
op_or_assign
id|ADVERTISE_10FULL
suffix:semicolon
r_if
c_cond
(paren
id|advertise
op_amp
id|ADVERTISED_100baseT_Half
)paren
id|adv
op_or_assign
id|ADVERTISE_100HALF
suffix:semicolon
r_if
c_cond
(paren
id|advertise
op_amp
id|ADVERTISED_100baseT_Full
)paren
id|adv
op_or_assign
id|ADVERTISE_100FULL
suffix:semicolon
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_ADVERTISE
comma
id|adv
)paren
suffix:semicolon
)brace
DECL|function|genmii_setup_forced
r_static
r_void
id|genmii_setup_forced
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|u16
id|ctrl
suffix:semicolon
id|u32
id|features
op_assign
id|mii_info-&gt;phyinfo-&gt;features
suffix:semicolon
id|ctrl
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_BMCR
)paren
suffix:semicolon
id|ctrl
op_and_assign
op_complement
(paren
id|BMCR_FULLDPLX
op_or
id|BMCR_SPEED100
op_or
id|BMCR_SPEED1000
op_or
id|BMCR_ANENABLE
)paren
suffix:semicolon
id|ctrl
op_or_assign
id|BMCR_RESET
suffix:semicolon
r_switch
c_cond
(paren
id|mii_info-&gt;speed
)paren
(brace
r_case
id|SPEED_1000
suffix:colon
r_if
c_cond
(paren
id|features
op_amp
(paren
id|SUPPORTED_1000baseT_Half
op_or
id|SUPPORTED_1000baseT_Full
)paren
)paren
(brace
id|ctrl
op_or_assign
id|BMCR_SPEED1000
suffix:semicolon
r_break
suffix:semicolon
)brace
id|mii_info-&gt;speed
op_assign
id|SPEED_100
suffix:semicolon
r_case
id|SPEED_100
suffix:colon
r_if
c_cond
(paren
id|features
op_amp
(paren
id|SUPPORTED_100baseT_Half
op_or
id|SUPPORTED_100baseT_Full
)paren
)paren
(brace
id|ctrl
op_or_assign
id|BMCR_SPEED100
suffix:semicolon
r_break
suffix:semicolon
)brace
id|mii_info-&gt;speed
op_assign
id|SPEED_10
suffix:semicolon
r_case
id|SPEED_10
suffix:colon
r_if
c_cond
(paren
id|features
op_amp
(paren
id|SUPPORTED_10baseT_Half
op_or
id|SUPPORTED_10baseT_Full
)paren
)paren
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unsupported speed! */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Bad speed!&bslash;n&quot;
comma
id|mii_info-&gt;dev-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_BMCR
comma
id|ctrl
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable and Restart Autonegotiation */
DECL|function|genmii_restart_aneg
r_static
r_void
id|genmii_restart_aneg
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|u16
id|ctl
suffix:semicolon
id|ctl
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_BMCR
)paren
suffix:semicolon
id|ctl
op_or_assign
(paren
id|BMCR_ANENABLE
op_or
id|BMCR_ANRESTART
)paren
suffix:semicolon
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_BMCR
comma
id|ctl
)paren
suffix:semicolon
)brace
DECL|function|gbit_config_aneg
r_static
r_int
id|gbit_config_aneg
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|u16
id|adv
suffix:semicolon
id|u32
id|advertise
suffix:semicolon
r_if
c_cond
(paren
id|mii_info-&gt;autoneg
)paren
(brace
multiline_comment|/* Configure the ADVERTISE register */
id|config_genmii_advert
c_func
(paren
id|mii_info
)paren
suffix:semicolon
id|advertise
op_assign
id|mii_info-&gt;advertising
suffix:semicolon
id|adv
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_1000BASETCONTROL
)paren
suffix:semicolon
id|adv
op_and_assign
op_complement
(paren
id|MII_1000BASETCONTROL_FULLDUPLEXCAP
op_or
id|MII_1000BASETCONTROL_HALFDUPLEXCAP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|advertise
op_amp
id|SUPPORTED_1000baseT_Half
)paren
id|adv
op_or_assign
id|MII_1000BASETCONTROL_HALFDUPLEXCAP
suffix:semicolon
r_if
c_cond
(paren
id|advertise
op_amp
id|SUPPORTED_1000baseT_Full
)paren
id|adv
op_or_assign
id|MII_1000BASETCONTROL_FULLDUPLEXCAP
suffix:semicolon
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_1000BASETCONTROL
comma
id|adv
)paren
suffix:semicolon
multiline_comment|/* Start/Restart aneg */
id|genmii_restart_aneg
c_func
(paren
id|mii_info
)paren
suffix:semicolon
)brace
r_else
id|genmii_setup_forced
c_func
(paren
id|mii_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|marvell_config_aneg
r_static
r_int
id|marvell_config_aneg
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
multiline_comment|/* The Marvell PHY has an errata which requires&n;&t; * that certain registers get written in order&n;&t; * to restart autonegotiation */
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_BMCR
comma
id|BMCR_RESET
)paren
suffix:semicolon
id|phy_write
c_func
(paren
id|mii_info
comma
l_int|0x1d
comma
l_int|0x1f
)paren
suffix:semicolon
id|phy_write
c_func
(paren
id|mii_info
comma
l_int|0x1e
comma
l_int|0x200c
)paren
suffix:semicolon
id|phy_write
c_func
(paren
id|mii_info
comma
l_int|0x1d
comma
l_int|0x5
)paren
suffix:semicolon
id|phy_write
c_func
(paren
id|mii_info
comma
l_int|0x1e
comma
l_int|0
)paren
suffix:semicolon
id|phy_write
c_func
(paren
id|mii_info
comma
l_int|0x1e
comma
l_int|0x100
)paren
suffix:semicolon
id|gbit_config_aneg
c_func
(paren
id|mii_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|genmii_config_aneg
r_static
r_int
id|genmii_config_aneg
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
r_if
c_cond
(paren
id|mii_info-&gt;autoneg
)paren
(brace
id|config_genmii_advert
c_func
(paren
id|mii_info
)paren
suffix:semicolon
id|genmii_restart_aneg
c_func
(paren
id|mii_info
)paren
suffix:semicolon
)brace
r_else
id|genmii_setup_forced
c_func
(paren
id|mii_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|genmii_update_link
r_static
r_int
id|genmii_update_link
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|u16
id|status
suffix:semicolon
multiline_comment|/* Do a fake read */
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_BMSR
)paren
suffix:semicolon
multiline_comment|/* Read link and autonegotiation status */
id|status
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_BMSR
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|BMSR_LSTATUS
)paren
op_eq
l_int|0
)paren
id|mii_info-&gt;link
op_assign
l_int|0
suffix:semicolon
r_else
id|mii_info-&gt;link
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* If we are autonegotiating, and not done, &n;&t; * return an error */
r_if
c_cond
(paren
id|mii_info-&gt;autoneg
op_logical_and
op_logical_neg
(paren
id|status
op_amp
id|BMSR_ANEGCOMPLETE
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|genmii_read_status
r_static
r_int
id|genmii_read_status
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|u16
id|status
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* Update the link, but return if there&n;&t; * was an error */
id|err
op_assign
id|genmii_update_link
c_func
(paren
id|mii_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|mii_info-&gt;autoneg
)paren
(brace
id|status
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_LPA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
id|LPA_10FULL
op_or
id|LPA_100FULL
)paren
)paren
id|mii_info-&gt;duplex
op_assign
id|DUPLEX_FULL
suffix:semicolon
r_else
id|mii_info-&gt;duplex
op_assign
id|DUPLEX_HALF
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
id|LPA_100FULL
op_or
id|LPA_100HALF
)paren
)paren
id|mii_info-&gt;speed
op_assign
id|SPEED_100
suffix:semicolon
r_else
id|mii_info-&gt;speed
op_assign
id|SPEED_10
suffix:semicolon
id|mii_info-&gt;pause
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* On non-aneg, we assume what we put in BMCR is the speed,&n;&t; * though magic-aneg shouldn&squot;t prevent this case from occurring&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|marvell_read_status
r_static
r_int
id|marvell_read_status
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|u16
id|status
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* Update the link, but return if there&n;&t; * was an error */
id|err
op_assign
id|genmii_update_link
c_func
(paren
id|mii_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* If the link is up, read the speed and duplex */
multiline_comment|/* If we aren&squot;t autonegotiating, assume speeds &n;&t; * are as set */
r_if
c_cond
(paren
id|mii_info-&gt;autoneg
op_logical_and
id|mii_info-&gt;link
)paren
(brace
r_int
id|speed
suffix:semicolon
id|status
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_M1011_PHY_SPEC_STATUS
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* If speed and duplex aren&squot;t resolved,&n;&t;&t; * return an error.  Isn&squot;t this handled&n;&t;&t; * by checking aneg?&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|status
op_amp
id|MII_M1011_PHY_SPEC_STATUS_RESOLVED
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
macro_line|#endif
multiline_comment|/* Get the duplexity */
r_if
c_cond
(paren
id|status
op_amp
id|MII_M1011_PHY_SPEC_STATUS_FULLDUPLEX
)paren
id|mii_info-&gt;duplex
op_assign
id|DUPLEX_FULL
suffix:semicolon
r_else
id|mii_info-&gt;duplex
op_assign
id|DUPLEX_HALF
suffix:semicolon
multiline_comment|/* Get the speed */
id|speed
op_assign
id|status
op_amp
id|MII_M1011_PHY_SPEC_STATUS_SPD_MASK
suffix:semicolon
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_case
id|MII_M1011_PHY_SPEC_STATUS_1000
suffix:colon
id|mii_info-&gt;speed
op_assign
id|SPEED_1000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MII_M1011_PHY_SPEC_STATUS_100
suffix:colon
id|mii_info-&gt;speed
op_assign
id|SPEED_100
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|mii_info-&gt;speed
op_assign
id|SPEED_10
suffix:semicolon
r_break
suffix:semicolon
)brace
id|mii_info-&gt;pause
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cis820x_read_status
r_static
r_int
id|cis820x_read_status
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|u16
id|status
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* Update the link, but return if there&n;&t; * was an error */
id|err
op_assign
id|genmii_update_link
c_func
(paren
id|mii_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* If the link is up, read the speed and duplex */
multiline_comment|/* If we aren&squot;t autonegotiating, assume speeds &n;&t; * are as set */
r_if
c_cond
(paren
id|mii_info-&gt;autoneg
op_logical_and
id|mii_info-&gt;link
)paren
(brace
r_int
id|speed
suffix:semicolon
id|status
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_CIS8201_AUX_CONSTAT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|MII_CIS8201_AUXCONSTAT_DUPLEX
)paren
id|mii_info-&gt;duplex
op_assign
id|DUPLEX_FULL
suffix:semicolon
r_else
id|mii_info-&gt;duplex
op_assign
id|DUPLEX_HALF
suffix:semicolon
id|speed
op_assign
id|status
op_amp
id|MII_CIS8201_AUXCONSTAT_SPEED
suffix:semicolon
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_case
id|MII_CIS8201_AUXCONSTAT_GBIT
suffix:colon
id|mii_info-&gt;speed
op_assign
id|SPEED_1000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MII_CIS8201_AUXCONSTAT_100
suffix:colon
id|mii_info-&gt;speed
op_assign
id|SPEED_100
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|mii_info-&gt;speed
op_assign
id|SPEED_10
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|marvell_ack_interrupt
r_static
r_int
id|marvell_ack_interrupt
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
multiline_comment|/* Clear the interrupts by reading the reg */
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_M1011_IEVENT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|marvell_config_intr
r_static
r_int
id|marvell_config_intr
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
r_if
c_cond
(paren
id|mii_info-&gt;interrupts
op_eq
id|MII_INTERRUPT_ENABLED
)paren
(brace
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_M1011_IMASK
comma
id|MII_M1011_IMASK_INIT
)paren
suffix:semicolon
)brace
r_else
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_M1011_IMASK
comma
id|MII_M1011_IMASK_CLEAR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cis820x_init
r_static
r_int
id|cis820x_init
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_CIS8201_AUX_CONSTAT
comma
id|MII_CIS8201_AUXCONSTAT_INIT
)paren
suffix:semicolon
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_CIS8201_EXT_CON1
comma
id|MII_CIS8201_EXTCON1_INIT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cis820x_ack_interrupt
r_static
r_int
id|cis820x_ack_interrupt
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_CIS8201_ISTAT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cis820x_config_intr
r_static
r_int
id|cis820x_config_intr
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
r_if
c_cond
(paren
id|mii_info-&gt;interrupts
op_eq
id|MII_INTERRUPT_ENABLED
)paren
(brace
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_CIS8201_IMASK
comma
id|MII_CIS8201_IMASK_MASK
)paren
suffix:semicolon
)brace
r_else
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_CIS8201_IMASK
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|DM9161_DELAY
mdefine_line|#define DM9161_DELAY 10
DECL|function|dm9161_read_status
r_static
r_int
id|dm9161_read_status
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|u16
id|status
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* Update the link, but return if there&n;&t; * was an error */
id|err
op_assign
id|genmii_update_link
c_func
(paren
id|mii_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* If the link is up, read the speed and duplex */
multiline_comment|/* If we aren&squot;t autonegotiating, assume speeds &n;&t; * are as set */
r_if
c_cond
(paren
id|mii_info-&gt;autoneg
op_logical_and
id|mii_info-&gt;link
)paren
(brace
id|status
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_DM9161_SCSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
id|MII_DM9161_SCSR_100F
op_or
id|MII_DM9161_SCSR_100H
)paren
)paren
id|mii_info-&gt;speed
op_assign
id|SPEED_100
suffix:semicolon
r_else
id|mii_info-&gt;speed
op_assign
id|SPEED_10
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
id|MII_DM9161_SCSR_100F
op_or
id|MII_DM9161_SCSR_10F
)paren
)paren
id|mii_info-&gt;duplex
op_assign
id|DUPLEX_FULL
suffix:semicolon
r_else
id|mii_info-&gt;duplex
op_assign
id|DUPLEX_HALF
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm9161_config_aneg
r_static
r_int
id|dm9161_config_aneg
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
r_struct
id|dm9161_private
op_star
id|priv
op_assign
id|mii_info-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|priv-&gt;resetdone
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm9161_timer
r_static
r_void
id|dm9161_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|gfar_mii_info
op_star
id|mii_info
op_assign
(paren
r_struct
id|gfar_mii_info
op_star
)paren
id|data
suffix:semicolon
r_struct
id|dm9161_private
op_star
id|priv
op_assign
id|mii_info-&gt;priv
suffix:semicolon
id|u16
id|status
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_BMSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|BMSR_ANEGCOMPLETE
)paren
(brace
id|priv-&gt;resetdone
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|mod_timer
c_func
(paren
op_amp
id|priv-&gt;timer
comma
id|jiffies
op_plus
id|DM9161_DELAY
op_star
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|dm9161_init
r_static
r_int
id|dm9161_init
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
r_struct
id|dm9161_private
op_star
id|priv
suffix:semicolon
multiline_comment|/* Allocate the private data structure */
id|priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dm9161_private
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|priv
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|mii_info-&gt;priv
op_assign
id|priv
suffix:semicolon
multiline_comment|/* Reset is not done yet */
id|priv-&gt;resetdone
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Isolate the PHY */
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_BMCR
comma
id|BMCR_ISOLATE
)paren
suffix:semicolon
multiline_comment|/* Do not bypass the scrambler/descrambler */
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_DM9161_SCR
comma
id|MII_DM9161_SCR_INIT
)paren
suffix:semicolon
multiline_comment|/* Clear 10BTCSR to default */
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_DM9161_10BTCSR
comma
id|MII_DM9161_10BTCSR_INIT
)paren
suffix:semicolon
multiline_comment|/* Reconnect the PHY, and enable Autonegotiation */
id|phy_write
c_func
(paren
id|mii_info
comma
id|MII_BMCR
comma
id|BMCR_ANENABLE
)paren
suffix:semicolon
multiline_comment|/* Start a timer for DM9161_DELAY seconds to wait&n;&t; * for the PHY to be ready */
id|init_timer
c_func
(paren
op_amp
id|priv-&gt;timer
)paren
suffix:semicolon
id|priv-&gt;timer.function
op_assign
op_amp
id|dm9161_timer
suffix:semicolon
id|priv-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|mii_info
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|priv-&gt;timer
comma
id|jiffies
op_plus
id|DM9161_DELAY
op_star
id|HZ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dm9161_close
r_static
r_void
id|dm9161_close
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
r_struct
id|dm9161_private
op_star
id|priv
op_assign
id|mii_info-&gt;priv
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|priv-&gt;timer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_int
id|dm9161_ack_interrupt
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_DM9161_INTR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Cicada 820x */
DECL|variable|phy_info_cis820x
r_static
r_struct
id|phy_info
id|phy_info_cis820x
op_assign
(brace
l_int|0x000fc440
comma
l_string|&quot;Cicada Cis8204&quot;
comma
l_int|0x000fffc0
comma
dot
id|features
op_assign
id|MII_GBIT_FEATURES
comma
dot
id|init
op_assign
op_amp
id|cis820x_init
comma
dot
id|config_aneg
op_assign
op_amp
id|gbit_config_aneg
comma
dot
id|read_status
op_assign
op_amp
id|cis820x_read_status
comma
dot
id|ack_interrupt
op_assign
op_amp
id|cis820x_ack_interrupt
comma
dot
id|config_intr
op_assign
op_amp
id|cis820x_config_intr
comma
)brace
suffix:semicolon
DECL|variable|phy_info_dm9161
r_static
r_struct
id|phy_info
id|phy_info_dm9161
op_assign
(brace
dot
id|phy_id
op_assign
l_int|0x0181b880
comma
dot
id|name
op_assign
l_string|&quot;Davicom DM9161E&quot;
comma
dot
id|phy_id_mask
op_assign
l_int|0x0ffffff0
comma
dot
id|init
op_assign
id|dm9161_init
comma
dot
id|config_aneg
op_assign
id|dm9161_config_aneg
comma
dot
id|read_status
op_assign
id|dm9161_read_status
comma
dot
id|close
op_assign
id|dm9161_close
comma
)brace
suffix:semicolon
DECL|variable|phy_info_marvell
r_static
r_struct
id|phy_info
id|phy_info_marvell
op_assign
(brace
dot
id|phy_id
op_assign
l_int|0x01410c00
comma
dot
id|phy_id_mask
op_assign
l_int|0xffffff00
comma
dot
id|name
op_assign
l_string|&quot;Marvell 88E1101&quot;
comma
dot
id|features
op_assign
id|MII_GBIT_FEATURES
comma
dot
id|config_aneg
op_assign
op_amp
id|marvell_config_aneg
comma
dot
id|read_status
op_assign
op_amp
id|marvell_read_status
comma
dot
id|ack_interrupt
op_assign
op_amp
id|marvell_ack_interrupt
comma
dot
id|config_intr
op_assign
op_amp
id|marvell_config_intr
comma
)brace
suffix:semicolon
DECL|variable|phy_info_genmii
r_static
r_struct
id|phy_info
id|phy_info_genmii
op_assign
(brace
dot
id|phy_id
op_assign
l_int|0x00000000
comma
dot
id|phy_id_mask
op_assign
l_int|0x00000000
comma
dot
id|name
op_assign
l_string|&quot;Generic MII&quot;
comma
dot
id|features
op_assign
id|MII_BASIC_FEATURES
comma
dot
id|config_aneg
op_assign
id|genmii_config_aneg
comma
dot
id|read_status
op_assign
id|genmii_read_status
comma
)brace
suffix:semicolon
DECL|variable|phy_info
r_static
r_struct
id|phy_info
op_star
id|phy_info
(braket
)braket
op_assign
(brace
op_amp
id|phy_info_cis820x
comma
op_amp
id|phy_info_marvell
comma
op_amp
id|phy_info_dm9161
comma
op_amp
id|phy_info_genmii
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|phy_read
id|u16
id|phy_read
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
comma
id|u16
id|regnum
)paren
(brace
id|u16
id|retval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mii_info-&gt;mdio_lock
comma
id|flags
)paren
suffix:semicolon
id|retval
op_assign
id|mii_info
op_member_access_from_pointer
id|mdio_read
c_func
(paren
id|mii_info-&gt;dev
comma
id|mii_info-&gt;mii_id
comma
id|regnum
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mii_info-&gt;mdio_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|phy_write
r_void
id|phy_write
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
comma
id|u16
id|regnum
comma
id|u16
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mii_info-&gt;mdio_lock
comma
id|flags
)paren
suffix:semicolon
id|mii_info
op_member_access_from_pointer
id|mdio_write
c_func
(paren
id|mii_info-&gt;dev
comma
id|mii_info-&gt;mii_id
comma
id|regnum
comma
id|val
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mii_info-&gt;mdio_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Use the PHY ID registers to determine what type of PHY is attached&n; * to device dev.  return a struct phy_info structure describing that PHY&n; */
DECL|function|get_phy_info
r_struct
id|phy_info
op_star
id|get_phy_info
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
(brace
id|u16
id|phy_reg
suffix:semicolon
id|u32
id|phy_ID
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|phy_info
op_star
id|theInfo
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|mii_info-&gt;dev
suffix:semicolon
multiline_comment|/* Grab the bits from PHYIR1, and put them in the upper half */
id|phy_reg
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_PHYSID1
)paren
suffix:semicolon
id|phy_ID
op_assign
(paren
id|phy_reg
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
suffix:semicolon
multiline_comment|/* Grab the bits from PHYIR2, and put them in the lower half */
id|phy_reg
op_assign
id|phy_read
c_func
(paren
id|mii_info
comma
id|MII_PHYSID2
)paren
suffix:semicolon
id|phy_ID
op_or_assign
(paren
id|phy_reg
op_amp
l_int|0xffff
)paren
suffix:semicolon
multiline_comment|/* loop through all the known PHY types, and find one that */
multiline_comment|/* matches the ID we read from the PHY. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|phy_info
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|phy_info
(braket
id|i
)braket
op_member_access_from_pointer
id|phy_id
op_eq
(paren
id|phy_ID
op_amp
id|phy_info
(braket
id|i
)braket
op_member_access_from_pointer
id|phy_id_mask
)paren
)paren
(brace
id|theInfo
op_assign
id|phy_info
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* This shouldn&squot;t happen, as we have generic PHY support */
r_if
c_cond
(paren
id|theInfo
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: PHY id %x is not supported!&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|phy_ID
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;%s: PHY is %s (%x)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|theInfo-&gt;name
comma
id|phy_ID
)paren
suffix:semicolon
)brace
r_return
id|theInfo
suffix:semicolon
)brace
eof
