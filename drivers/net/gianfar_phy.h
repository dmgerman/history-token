multiline_comment|/* &n; * drivers/net/gianfar_phy.h&n; *&n; * Gianfar Ethernet Driver -- PHY handling&n; * Driver for FEC on MPC8540 and TSEC on MPC8540/MPC8560&n; * Based on 8260_io/fcc_enet.c&n; *&n; * Author: Andy Fleming&n; * Maintainer: Kumar Gala (kumar.gala@freescale.com)&n; *&n; * Copyright (c) 2002-2004 Freescale Semiconductor, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __GIANFAR_PHY_H
DECL|macro|__GIANFAR_PHY_H
mdefine_line|#define __GIANFAR_PHY_H
DECL|macro|MII_end
mdefine_line|#define MII_end ((u32)-2)
DECL|macro|MII_read
mdefine_line|#define MII_read ((u32)-1)
DECL|macro|MIIMIND_BUSY
mdefine_line|#define MIIMIND_BUSY            0x00000001
DECL|macro|MIIMIND_NOTVALID
mdefine_line|#define MIIMIND_NOTVALID        0x00000004
DECL|macro|GFAR_AN_TIMEOUT
mdefine_line|#define GFAR_AN_TIMEOUT         2000
multiline_comment|/* 1000BT control (Marvell &amp; BCM54xx at least) */
DECL|macro|MII_1000BASETCONTROL
mdefine_line|#define MII_1000BASETCONTROL&t;&t;&t;0x09
DECL|macro|MII_1000BASETCONTROL_FULLDUPLEXCAP
mdefine_line|#define MII_1000BASETCONTROL_FULLDUPLEXCAP&t;0x0200
DECL|macro|MII_1000BASETCONTROL_HALFDUPLEXCAP
mdefine_line|#define MII_1000BASETCONTROL_HALFDUPLEXCAP&t;0x0100
multiline_comment|/* Cicada Extended Control Register 1 */
DECL|macro|MII_CIS8201_EXT_CON1
mdefine_line|#define MII_CIS8201_EXT_CON1           0x17
DECL|macro|MII_CIS8201_EXTCON1_INIT
mdefine_line|#define MII_CIS8201_EXTCON1_INIT       0x0000
multiline_comment|/* Cicada Interrupt Mask Register */
DECL|macro|MII_CIS8201_IMASK
mdefine_line|#define MII_CIS8201_IMASK&t;&t;0x19
DECL|macro|MII_CIS8201_IMASK_IEN
mdefine_line|#define MII_CIS8201_IMASK_IEN&t;&t;0x8000
DECL|macro|MII_CIS8201_IMASK_SPEED
mdefine_line|#define MII_CIS8201_IMASK_SPEED&t;0x4000
DECL|macro|MII_CIS8201_IMASK_LINK
mdefine_line|#define MII_CIS8201_IMASK_LINK&t;&t;0x2000
DECL|macro|MII_CIS8201_IMASK_DUPLEX
mdefine_line|#define MII_CIS8201_IMASK_DUPLEX&t;0x1000
DECL|macro|MII_CIS8201_IMASK_MASK
mdefine_line|#define MII_CIS8201_IMASK_MASK&t;&t;0xf000
multiline_comment|/* Cicada Interrupt Status Register */
DECL|macro|MII_CIS8201_ISTAT
mdefine_line|#define MII_CIS8201_ISTAT&t;&t;0x1a
DECL|macro|MII_CIS8201_ISTAT_STATUS
mdefine_line|#define MII_CIS8201_ISTAT_STATUS&t;0x8000
DECL|macro|MII_CIS8201_ISTAT_SPEED
mdefine_line|#define MII_CIS8201_ISTAT_SPEED&t;0x4000
DECL|macro|MII_CIS8201_ISTAT_LINK
mdefine_line|#define MII_CIS8201_ISTAT_LINK&t;&t;0x2000
DECL|macro|MII_CIS8201_ISTAT_DUPLEX
mdefine_line|#define MII_CIS8201_ISTAT_DUPLEX&t;0x1000
multiline_comment|/* Cicada Auxiliary Control/Status Register */
DECL|macro|MII_CIS8201_AUX_CONSTAT
mdefine_line|#define MII_CIS8201_AUX_CONSTAT        0x1c
DECL|macro|MII_CIS8201_AUXCONSTAT_INIT
mdefine_line|#define MII_CIS8201_AUXCONSTAT_INIT    0x0004
DECL|macro|MII_CIS8201_AUXCONSTAT_DUPLEX
mdefine_line|#define MII_CIS8201_AUXCONSTAT_DUPLEX  0x0020
DECL|macro|MII_CIS8201_AUXCONSTAT_SPEED
mdefine_line|#define MII_CIS8201_AUXCONSTAT_SPEED   0x0018
DECL|macro|MII_CIS8201_AUXCONSTAT_GBIT
mdefine_line|#define MII_CIS8201_AUXCONSTAT_GBIT    0x0010
DECL|macro|MII_CIS8201_AUXCONSTAT_100
mdefine_line|#define MII_CIS8201_AUXCONSTAT_100     0x0008
multiline_comment|/* 88E1011 PHY Status Register */
DECL|macro|MII_M1011_PHY_SPEC_STATUS
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS&t;&t;0x11
DECL|macro|MII_M1011_PHY_SPEC_STATUS_1000
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_1000&t;&t;0x8000
DECL|macro|MII_M1011_PHY_SPEC_STATUS_100
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_100&t;&t;0x4000
DECL|macro|MII_M1011_PHY_SPEC_STATUS_SPD_MASK
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_SPD_MASK&t;0xc000
DECL|macro|MII_M1011_PHY_SPEC_STATUS_FULLDUPLEX
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_FULLDUPLEX&t;0x2000
DECL|macro|MII_M1011_PHY_SPEC_STATUS_RESOLVED
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_RESOLVED&t;0x0800
DECL|macro|MII_M1011_PHY_SPEC_STATUS_LINK
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_LINK&t;&t;0x0400
DECL|macro|MII_M1011_IEVENT
mdefine_line|#define MII_M1011_IEVENT&t;&t;0x13
DECL|macro|MII_M1011_IEVENT_CLEAR
mdefine_line|#define MII_M1011_IEVENT_CLEAR&t;&t;0x0000
DECL|macro|MII_M1011_IMASK
mdefine_line|#define MII_M1011_IMASK&t;&t;&t;0x12
DECL|macro|MII_M1011_IMASK_INIT
mdefine_line|#define MII_M1011_IMASK_INIT&t;&t;0x6400
DECL|macro|MII_M1011_IMASK_CLEAR
mdefine_line|#define MII_M1011_IMASK_CLEAR&t;&t;0x0000
DECL|macro|MII_DM9161_SCR
mdefine_line|#define MII_DM9161_SCR&t;&t;0x10
DECL|macro|MII_DM9161_SCR_INIT
mdefine_line|#define MII_DM9161_SCR_INIT&t;0x0610
multiline_comment|/* DM9161 Specified Configuration and Status Register */
DECL|macro|MII_DM9161_SCSR
mdefine_line|#define MII_DM9161_SCSR&t;0x11
DECL|macro|MII_DM9161_SCSR_100F
mdefine_line|#define MII_DM9161_SCSR_100F&t;0x8000
DECL|macro|MII_DM9161_SCSR_100H
mdefine_line|#define MII_DM9161_SCSR_100H&t;0x4000
DECL|macro|MII_DM9161_SCSR_10F
mdefine_line|#define MII_DM9161_SCSR_10F&t;0x2000
DECL|macro|MII_DM9161_SCSR_10H
mdefine_line|#define MII_DM9161_SCSR_10H&t;0x1000
multiline_comment|/* DM9161 Interrupt Register */
DECL|macro|MII_DM9161_INTR
mdefine_line|#define MII_DM9161_INTR&t;0x15
DECL|macro|MII_DM9161_INTR_PEND
mdefine_line|#define MII_DM9161_INTR_PEND&t;&t;0x8000
DECL|macro|MII_DM9161_INTR_DPLX_MASK
mdefine_line|#define MII_DM9161_INTR_DPLX_MASK&t;0x0800
DECL|macro|MII_DM9161_INTR_SPD_MASK
mdefine_line|#define MII_DM9161_INTR_SPD_MASK&t;0x0400
DECL|macro|MII_DM9161_INTR_LINK_MASK
mdefine_line|#define MII_DM9161_INTR_LINK_MASK&t;0x0200
DECL|macro|MII_DM9161_INTR_MASK
mdefine_line|#define MII_DM9161_INTR_MASK&t;&t;0x0100
DECL|macro|MII_DM9161_INTR_DPLX_CHANGE
mdefine_line|#define MII_DM9161_INTR_DPLX_CHANGE&t;0x0010
DECL|macro|MII_DM9161_INTR_SPD_CHANGE
mdefine_line|#define MII_DM9161_INTR_SPD_CHANGE&t;0x0008
DECL|macro|MII_DM9161_INTR_LINK_CHANGE
mdefine_line|#define MII_DM9161_INTR_LINK_CHANGE&t;0x0004
DECL|macro|MII_DM9161_INTR_INIT
mdefine_line|#define MII_DM9161_INTR_INIT &t;&t;0x0000
DECL|macro|MII_DM9161_INTR_STOP
mdefine_line|#define MII_DM9161_INTR_STOP&t;&bslash;&n;(MII_DM9161_INTR_DPLX_MASK | MII_DM9161_INTR_SPD_MASK &bslash;&n; | MII_DM9161_INTR_LINK_MASK | MII_DM9161_INTR_MASK)
multiline_comment|/* DM9161 10BT Configuration/Status */
DECL|macro|MII_DM9161_10BTCSR
mdefine_line|#define MII_DM9161_10BTCSR&t;0x12
DECL|macro|MII_DM9161_10BTCSR_INIT
mdefine_line|#define MII_DM9161_10BTCSR_INIT&t;0x7800
DECL|macro|MII_BASIC_FEATURES
mdefine_line|#define MII_BASIC_FEATURES&t;(SUPPORTED_10baseT_Half | &bslash;&n;&t;&t;&t;&t; SUPPORTED_10baseT_Full | &bslash;&n;&t;&t;&t;&t; SUPPORTED_100baseT_Half | &bslash;&n;&t;&t;&t;&t; SUPPORTED_100baseT_Full | &bslash;&n;&t;&t;&t;&t; SUPPORTED_Autoneg | &bslash;&n;&t;&t;&t;&t; SUPPORTED_TP | &bslash;&n;&t;&t;&t;&t; SUPPORTED_MII)
DECL|macro|MII_GBIT_FEATURES
mdefine_line|#define MII_GBIT_FEATURES&t;(MII_BASIC_FEATURES | &bslash;&n;&t;&t;&t;&t; SUPPORTED_1000baseT_Half | &bslash;&n;&t;&t;&t;&t; SUPPORTED_1000baseT_Full)
DECL|macro|MII_READ_COMMAND
mdefine_line|#define MII_READ_COMMAND       0x00000001
DECL|macro|MII_INTERRUPT_DISABLED
mdefine_line|#define MII_INTERRUPT_DISABLED 0x0
DECL|macro|MII_INTERRUPT_ENABLED
mdefine_line|#define MII_INTERRUPT_ENABLED 0x1
multiline_comment|/* Taken from mii_if_info and sungem_phy.h */
DECL|struct|gfar_mii_info
r_struct
id|gfar_mii_info
(brace
multiline_comment|/* Information about the PHY type */
multiline_comment|/* And management functions */
DECL|member|phyinfo
r_struct
id|phy_info
op_star
id|phyinfo
suffix:semicolon
multiline_comment|/* forced speed &amp; duplex (no autoneg)&n;&t; * partner speed &amp; duplex &amp; pause (autoneg)&n;&t; */
DECL|member|speed
r_int
id|speed
suffix:semicolon
DECL|member|duplex
r_int
id|duplex
suffix:semicolon
DECL|member|pause
r_int
id|pause
suffix:semicolon
multiline_comment|/* The most recently read link state */
DECL|member|link
r_int
id|link
suffix:semicolon
multiline_comment|/* Enabled Interrupts */
DECL|member|interrupts
id|u32
id|interrupts
suffix:semicolon
DECL|member|advertising
id|u32
id|advertising
suffix:semicolon
DECL|member|autoneg
r_int
id|autoneg
suffix:semicolon
DECL|member|mii_id
r_int
id|mii_id
suffix:semicolon
multiline_comment|/* private data pointer */
multiline_comment|/* For use by PHYs to maintain extra state */
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Provided by host chip */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* A lock to ensure that only one thing can read/write&n;&t; * the MDIO bus at a time */
DECL|member|mdio_lock
id|spinlock_t
id|mdio_lock
suffix:semicolon
multiline_comment|/* Provided by ethernet driver */
DECL|member|mdio_read
r_int
(paren
op_star
id|mdio_read
)paren
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
id|reg
)paren
suffix:semicolon
DECL|member|mdio_write
r_void
(paren
op_star
id|mdio_write
)paren
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
id|reg
comma
r_int
id|val
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* struct phy_info: a structure which defines attributes for a PHY&n; *&n; * id will contain a number which represents the PHY.  During&n; * startup, the driver will poll the PHY to find out what its&n; * UID--as defined by registers 2 and 3--is.  The 32-bit result&n; * gotten from the PHY will be ANDed with phy_id_mask to&n; * discard any bits which may change based on revision numbers&n; * unimportant to functionality&n; *&n; * There are 6 commands which take a gfar_mii_info structure.&n; * Each PHY must declare config_aneg, and read_status.&n; */
DECL|struct|phy_info
r_struct
id|phy_info
(brace
DECL|member|phy_id
id|u32
id|phy_id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|phy_id_mask
r_int
r_int
id|phy_id_mask
suffix:semicolon
DECL|member|features
id|u32
id|features
suffix:semicolon
multiline_comment|/* Called to initialize the PHY */
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
multiline_comment|/* Called to suspend the PHY for power */
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
multiline_comment|/* Reconfigures autonegotiation (or disables it) */
DECL|member|config_aneg
r_int
(paren
op_star
id|config_aneg
)paren
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
multiline_comment|/* Determines the negotiated speed and duplex */
DECL|member|read_status
r_int
(paren
op_star
id|read_status
)paren
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
multiline_comment|/* Clears any pending interrupts */
DECL|member|ack_interrupt
r_int
(paren
op_star
id|ack_interrupt
)paren
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
multiline_comment|/* Enables or disables interrupts */
DECL|member|config_intr
r_int
(paren
op_star
id|config_intr
)paren
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
multiline_comment|/* Clears up any memory if needed */
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
)brace
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
r_void
id|mii_clear_phy_interrupt
c_func
(paren
r_struct
id|gfar_mii_info
op_star
id|mii_info
)paren
suffix:semicolon
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
suffix:semicolon
DECL|struct|dm9161_private
r_struct
id|dm9161_private
(brace
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|resetdone
r_int
id|resetdone
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* GIANFAR_PHY_H */
eof
