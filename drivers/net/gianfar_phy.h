multiline_comment|/* &n; * drivers/net/gianfar_phy.h&n; *&n; * Gianfar Ethernet Driver -- PHY handling&n; * Driver for FEC on MPC8540 and TSEC on MPC8540/MPC8560&n; * Based on 8260_io/fcc_enet.c&n; *&n; * Author: Andy Fleming&n; * Maintainer: Kumar Gala (kumar.gala@freescale.com)&n; *&n; * Copyright 2004 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __GIANFAR_PHY_H
DECL|macro|__GIANFAR_PHY_H
mdefine_line|#define __GIANFAR_PHY_H
DECL|macro|miim_end
mdefine_line|#define miim_end ((u32)-2)
DECL|macro|miim_read
mdefine_line|#define miim_read ((u32)-1)
DECL|macro|MIIMIND_BUSY
mdefine_line|#define MIIMIND_BUSY            0x00000001
DECL|macro|MIIMIND_NOTVALID
mdefine_line|#define MIIMIND_NOTVALID        0x00000004
DECL|macro|MIIM_CONTROL
mdefine_line|#define MIIM_CONTROL&t;&t;0x00
DECL|macro|MIIM_CONTROL_RESET
mdefine_line|#define MIIM_CONTROL_RESET&t;0x00008000
DECL|macro|MIIM_CONTROL_INIT
mdefine_line|#define MIIM_CONTROL_INIT&t;0x00001140
DECL|macro|MIIM_ANEN
mdefine_line|#define MIIM_ANEN&t;&t;0x00001000
DECL|macro|MIIM_CR
mdefine_line|#define MIIM_CR                 0x00
DECL|macro|MIIM_CR_RST
mdefine_line|#define MIIM_CR_RST&t;&t;0x00008000
DECL|macro|MIIM_CR_INIT
mdefine_line|#define MIIM_CR_INIT&t;        0x00001000
DECL|macro|MIIM_STATUS
mdefine_line|#define MIIM_STATUS&t;&t;0x1
DECL|macro|MIIM_STATUS_AN_DONE
mdefine_line|#define MIIM_STATUS_AN_DONE&t;0x00000020
DECL|macro|MIIM_STATUS_LINK
mdefine_line|#define MIIM_STATUS_LINK&t;0x0004
DECL|macro|MIIM_PHYIR1
mdefine_line|#define MIIM_PHYIR1&t;&t;0x2
DECL|macro|MIIM_PHYIR2
mdefine_line|#define MIIM_PHYIR2&t;&t;0x3
DECL|macro|GFAR_AN_TIMEOUT
mdefine_line|#define GFAR_AN_TIMEOUT         0x000fffff
DECL|macro|MIIM_ANLPBPA
mdefine_line|#define MIIM_ANLPBPA&t;0x5
DECL|macro|MIIM_ANLPBPA_HALF
mdefine_line|#define MIIM_ANLPBPA_HALF&t;0x00000040
DECL|macro|MIIM_ANLPBPA_FULL
mdefine_line|#define MIIM_ANLPBPA_FULL&t;0x00000020
DECL|macro|MIIM_ANEX
mdefine_line|#define MIIM_ANEX&t;&t;0x6
DECL|macro|MIIM_ANEX_NP
mdefine_line|#define MIIM_ANEX_NP    &t;0x00000004
DECL|macro|MIIM_ANEX_PRX
mdefine_line|#define MIIM_ANEX_PRX   &t;0x00000002
multiline_comment|/* Cicada Extended Control Register 1 */
DECL|macro|MIIM_CIS8201_EXT_CON1
mdefine_line|#define MIIM_CIS8201_EXT_CON1           0x17
DECL|macro|MIIM_CIS8201_EXTCON1_INIT
mdefine_line|#define MIIM_CIS8201_EXTCON1_INIT       0x0000
multiline_comment|/* Cicada Interrupt Mask Register */
DECL|macro|MIIM_CIS8204_IMASK
mdefine_line|#define MIIM_CIS8204_IMASK&t;&t;0x19
DECL|macro|MIIM_CIS8204_IMASK_IEN
mdefine_line|#define MIIM_CIS8204_IMASK_IEN&t;&t;0x8000
DECL|macro|MIIM_CIS8204_IMASK_SPEED
mdefine_line|#define MIIM_CIS8204_IMASK_SPEED&t;0x4000
DECL|macro|MIIM_CIS8204_IMASK_LINK
mdefine_line|#define MIIM_CIS8204_IMASK_LINK&t;&t;0x2000
DECL|macro|MIIM_CIS8204_IMASK_DUPLEX
mdefine_line|#define MIIM_CIS8204_IMASK_DUPLEX&t;0x1000
DECL|macro|MIIM_CIS8204_IMASK_MASK
mdefine_line|#define MIIM_CIS8204_IMASK_MASK&t;&t;0xf000
multiline_comment|/* Cicada Interrupt Status Register */
DECL|macro|MIIM_CIS8204_ISTAT
mdefine_line|#define MIIM_CIS8204_ISTAT&t;&t;0x1a
DECL|macro|MIIM_CIS8204_ISTAT_STATUS
mdefine_line|#define MIIM_CIS8204_ISTAT_STATUS&t;0x8000
DECL|macro|MIIM_CIS8204_ISTAT_SPEED
mdefine_line|#define MIIM_CIS8204_ISTAT_SPEED&t;0x4000
DECL|macro|MIIM_CIS8204_ISTAT_LINK
mdefine_line|#define MIIM_CIS8204_ISTAT_LINK&t;&t;0x2000
DECL|macro|MIIM_CIS8204_ISTAT_DUPLEX
mdefine_line|#define MIIM_CIS8204_ISTAT_DUPLEX&t;0x1000
multiline_comment|/* Cicada Auxiliary Control/Status Register */
DECL|macro|MIIM_CIS8201_AUX_CONSTAT
mdefine_line|#define MIIM_CIS8201_AUX_CONSTAT        0x1c
DECL|macro|MIIM_CIS8201_AUXCONSTAT_INIT
mdefine_line|#define MIIM_CIS8201_AUXCONSTAT_INIT    0x0004
DECL|macro|MIIM_CIS8201_AUXCONSTAT_DUPLEX
mdefine_line|#define MIIM_CIS8201_AUXCONSTAT_DUPLEX  0x0020
DECL|macro|MIIM_CIS8201_AUXCONSTAT_SPEED
mdefine_line|#define MIIM_CIS8201_AUXCONSTAT_SPEED   0x0018
DECL|macro|MIIM_CIS8201_AUXCONSTAT_GBIT
mdefine_line|#define MIIM_CIS8201_AUXCONSTAT_GBIT    0x0010
DECL|macro|MIIM_CIS8201_AUXCONSTAT_100
mdefine_line|#define MIIM_CIS8201_AUXCONSTAT_100     0x0008
multiline_comment|/* 88E1011 PHY Status Register */
DECL|macro|MIIM_88E1011_PHY_STATUS
mdefine_line|#define MIIM_88E1011_PHY_STATUS         0x11
DECL|macro|MIIM_88E1011_PHYSTAT_SPEED
mdefine_line|#define MIIM_88E1011_PHYSTAT_SPEED      0xc000
DECL|macro|MIIM_88E1011_PHYSTAT_GBIT
mdefine_line|#define MIIM_88E1011_PHYSTAT_GBIT       0x8000
DECL|macro|MIIM_88E1011_PHYSTAT_100
mdefine_line|#define MIIM_88E1011_PHYSTAT_100        0x4000
DECL|macro|MIIM_88E1011_PHYSTAT_DUPLEX
mdefine_line|#define MIIM_88E1011_PHYSTAT_DUPLEX     0x2000
DECL|macro|MIIM_88E1011_PHYSTAT_LINK
mdefine_line|#define MIIM_88E1011_PHYSTAT_LINK&t;0x0400
DECL|macro|MIIM_88E1011_IEVENT
mdefine_line|#define MIIM_88E1011_IEVENT&t;&t;0x13
DECL|macro|MIIM_88E1011_IEVENT_CLEAR
mdefine_line|#define MIIM_88E1011_IEVENT_CLEAR&t;0x0000
DECL|macro|MIIM_88E1011_IMASK
mdefine_line|#define MIIM_88E1011_IMASK&t;&t;0x12
DECL|macro|MIIM_88E1011_IMASK_INIT
mdefine_line|#define MIIM_88E1011_IMASK_INIT&t;&t;0x6400
DECL|macro|MIIM_88E1011_IMASK_CLEAR
mdefine_line|#define MIIM_88E1011_IMASK_CLEAR&t;0x0000
multiline_comment|/* DM9161 Control register values */
DECL|macro|MIIM_DM9161_CR_STOP
mdefine_line|#define MIIM_DM9161_CR_STOP&t;0x0400
DECL|macro|MIIM_DM9161_CR_RSTAN
mdefine_line|#define MIIM_DM9161_CR_RSTAN&t;0x1200
DECL|macro|MIIM_DM9161_SCR
mdefine_line|#define MIIM_DM9161_SCR&t;&t;0x10
DECL|macro|MIIM_DM9161_SCR_INIT
mdefine_line|#define MIIM_DM9161_SCR_INIT&t;0x0610
multiline_comment|/* DM9161 Specified Configuration and Status Register */
DECL|macro|MIIM_DM9161_SCSR
mdefine_line|#define MIIM_DM9161_SCSR&t;0x11
DECL|macro|MIIM_DM9161_SCSR_100F
mdefine_line|#define MIIM_DM9161_SCSR_100F&t;0x8000
DECL|macro|MIIM_DM9161_SCSR_100H
mdefine_line|#define MIIM_DM9161_SCSR_100H&t;0x4000
DECL|macro|MIIM_DM9161_SCSR_10F
mdefine_line|#define MIIM_DM9161_SCSR_10F&t;0x2000
DECL|macro|MIIM_DM9161_SCSR_10H
mdefine_line|#define MIIM_DM9161_SCSR_10H&t;0x1000
multiline_comment|/* DM9161 Interrupt Register */
DECL|macro|MIIM_DM9161_INTR
mdefine_line|#define MIIM_DM9161_INTR&t;0x15
DECL|macro|MIIM_DM9161_INTR_PEND
mdefine_line|#define MIIM_DM9161_INTR_PEND&t;&t;0x8000
DECL|macro|MIIM_DM9161_INTR_DPLX_MASK
mdefine_line|#define MIIM_DM9161_INTR_DPLX_MASK&t;0x0800
DECL|macro|MIIM_DM9161_INTR_SPD_MASK
mdefine_line|#define MIIM_DM9161_INTR_SPD_MASK&t;0x0400
DECL|macro|MIIM_DM9161_INTR_LINK_MASK
mdefine_line|#define MIIM_DM9161_INTR_LINK_MASK&t;0x0200
DECL|macro|MIIM_DM9161_INTR_MASK
mdefine_line|#define MIIM_DM9161_INTR_MASK&t;&t;0x0100
DECL|macro|MIIM_DM9161_INTR_DPLX_CHANGE
mdefine_line|#define MIIM_DM9161_INTR_DPLX_CHANGE&t;0x0010
DECL|macro|MIIM_DM9161_INTR_SPD_CHANGE
mdefine_line|#define MIIM_DM9161_INTR_SPD_CHANGE&t;0x0008
DECL|macro|MIIM_DM9161_INTR_LINK_CHANGE
mdefine_line|#define MIIM_DM9161_INTR_LINK_CHANGE&t;0x0004
DECL|macro|MIIM_DM9161_INTR_INIT
mdefine_line|#define MIIM_DM9161_INTR_INIT &t;&t;0x0000
DECL|macro|MIIM_DM9161_INTR_STOP
mdefine_line|#define MIIM_DM9161_INTR_STOP&t;&bslash;&n;(MIIM_DM9161_INTR_DPLX_MASK | MIIM_DM9161_INTR_SPD_MASK &bslash;&n; | MIIM_DM9161_INTR_LINK_MASK | MIIM_DM9161_INTR_MASK)
multiline_comment|/* DM9161 10BT Configuration/Status */
DECL|macro|MIIM_DM9161_10BTCSR
mdefine_line|#define MIIM_DM9161_10BTCSR&t;0x12
DECL|macro|MIIM_DM9161_10BTCSR_INIT
mdefine_line|#define MIIM_DM9161_10BTCSR_INIT&t;0x7800
DECL|macro|MIIM_READ_COMMAND
mdefine_line|#define MIIM_READ_COMMAND       0x00000001
multiline_comment|/*&n; * struct phy_cmd:  A command for reading or writing a PHY register&n; *&n; * mii_reg:  The register to read or write&n; *&n; * mii_data:  For writes, the value to put in the register.&n; * &t;A value of -1 indicates this is a read.&n; *&n; * funct: A function pointer which is invoked for each command.&n; * &t;For reads, this function will be passed the value read&n; *&t;from the PHY, and process it.&n; *&t;For writes, the result of this function will be written&n; *&t;to the PHY register&n; */
DECL|struct|phy_cmd
r_struct
id|phy_cmd
(brace
DECL|member|mii_reg
id|u32
id|mii_reg
suffix:semicolon
DECL|member|mii_data
id|u32
id|mii_data
suffix:semicolon
DECL|member|funct
id|u16
(paren
op_star
id|funct
)paren
(paren
id|u16
id|mii_reg
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* struct phy_info: a structure which defines attributes for a PHY&n; *&n; * id will contain a number which represents the PHY.  During&n; * startup, the driver will poll the PHY to find out what its&n; * UID--as defined by registers 2 and 3--is.  The 32-bit result&n; * gotten from the PHY will be shifted right by &quot;shift&quot; bits to&n; * discard any bits which may change based on revision numbers&n; * unimportant to functionality&n; *&n; * The struct phy_cmd entries represent pointers to an arrays of&n; * commands which tell the driver what to do to the PHY.&n; */
DECL|struct|phy_info
r_struct
id|phy_info
(brace
DECL|member|id
id|u32
id|id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|shift
r_int
r_int
id|shift
suffix:semicolon
multiline_comment|/* Called to configure the PHY, and modify the controller&n;     * based on the results */
DECL|member|config
r_const
r_struct
id|phy_cmd
op_star
id|config
suffix:semicolon
multiline_comment|/* Called when starting up the controller.  Usually sets&n;     * up the interrupt for state changes */
DECL|member|startup
r_const
r_struct
id|phy_cmd
op_star
id|startup
suffix:semicolon
multiline_comment|/* Called inside the interrupt handler to acknowledge&n;     * the interrupt */
DECL|member|ack_int
r_const
r_struct
id|phy_cmd
op_star
id|ack_int
suffix:semicolon
multiline_comment|/* Called in the bottom half to handle the interrupt */
DECL|member|handle_int
r_const
r_struct
id|phy_cmd
op_star
id|handle_int
suffix:semicolon
multiline_comment|/* Called when bringing down the controller.  Usually stops&n;     * the interrupts from being generated */
DECL|member|shutdown
r_const
r_struct
id|phy_cmd
op_star
id|shutdown
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
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|phy_run_commands
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_const
r_struct
id|phy_cmd
op_star
id|cmd
)paren
suffix:semicolon
macro_line|#endif /* GIANFAR_PHY_H */
eof
