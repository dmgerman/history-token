multiline_comment|/******************************************************************************&n; *&n; * Name:&t;xmac_ii.h&n; * Project:&t;Gigabit Ethernet Adapters, Common Modules&n; * Version:&t;$Revision: 1.48 $&n; * Date:&t;$Date: 2003/05/13 17:17:55 $&n; * Purpose:&t;Defines and Macros for Gigabit Ethernet Controller&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: xmac_ii.h,v $&n; *&t;Revision 1.48  2003/05/13 17:17:55  mkarl&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.47  2003/03/31 07:37:25  mkarl&n; *&t;Corrected Copyright.&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.46  2003/01/28 09:47:45  rschmidt&n; *&t;Added defines for copper MDI/MDIX configuration&n; *&t;Added defines for LED Control Register&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.45  2002/12/10 14:35:13  rschmidt&n; *&t;Corrected defines for Extended PHY Specific Control&n; *&t;Added defines for Ext. PHY Specific Ctrl 2 Reg. (Fiber specific)&n; *&t;&n; *&t;Revision 1.44  2002/12/09 14:58:41  rschmidt&n; *&t;Added defines for Ext. PHY Specific Ctrl Reg. (downshift feature)&n; *&t;Added &squot;GMR_FS_UN_SIZE&squot;-Bit to Rx GMAC FIFO Flush Mask&n; *&t;&n; *&t;Revision 1.43  2002/12/05 10:14:45  rschmidt&n; *&t;Added define for GMAC&squot;s Half Duplex Burst Mode&n; *&t;Added define for Rx GMAC FIFO Flush Mask (default)&n; *&t;&n; *&t;Revision 1.42  2002/11/12 16:48:19  rschmidt&n; *&t;Added defines for Cable Diagnostic Register (GPHY)&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.41  2002/10/21 11:20:22  rschmidt&n; *&t;Added bit GMR_FS_GOOD_FC to GMR_FS_ANY_ERR&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.40  2002/10/14 14:54:14  rschmidt&n; *&t;Added defines for GPHY Specific Status and GPHY Interrupt Status&n; *&t;Added bits PHY_M_IS_AN_ERROR and PHY_M_IS_FIFO_ERROR to PHY_M_DEF_MSK&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.39  2002/10/10 15:53:44  mkarl&n; *&t;added some bit definitions for link speed status and LED&squot;s&n; *&t;&n; *&t;Revision 1.38  2002/08/21 16:23:46  rschmidt&n; *&t;Added defines for PHY Specific Ctrl Reg&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.37  2002/08/16 14:50:33  rschmidt&n; *&t;Added defines for Auto-Neg. Advertisement YUKON Fiber (88E1011S only)&n; *&t;Changed define PHY_M_DEF_MSK for GPHY IRQ Mask&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.36  2002/08/12 13:21:10  rschmidt&n; *&t;Added defines for different Broadcom PHY Ids&n; *&t;&n; *&t;Revision 1.35  2002/08/08 15:58:01  rschmidt&n; *&t;Added defines for Manual LED Override register (YUKON)&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.34  2002/07/31 17:23:36  rwahl&n; *&t;Added define GMR_FS_ANY_ERR (analogous to XMR_FS_ANY_ERR).&n; *&t;&n; *&t;Revision 1.33  2002/07/23 16:03:37  rschmidt&n; *&t;Added defines for GPHY registers&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.32  2002/07/15 18:14:37  rwahl&n; *&t;Added GMAC MIB counters definitions.&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.31  2002/07/15 15:42:50  rschmidt&n; *&t;Removed defines from PHY specific reg. which are&n; *&t;common to all PHYs&n; *&t;Added defines for GMAC MIB Counters&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.30  2002/06/05 08:22:12  rschmidt&n; *&t;Changed defines for GMAC Rx Control Register and Rx Status&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.29  2002/04/25 11:43:56  rschmidt&n; *&t;Added define PHY_B_AS_PAUSE_MSK for BCom Pause Res.&n; *&t;Added new registers and defines for YUKON (GMAC, GPHY)&n; *&t;Added Receive Frame Status Encoding for YUKON&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.28  2000/11/09 12:32:49  rassmann&n; *&t;Renamed variables.&n; *&t;&n; *&t;Revision 1.27  2000/05/17 11:00:46  malthoff&n; *&t;Add bit for enable/disable power management in BCOM chip.&n; *&t;&n; *&t;Revision 1.26  1999/11/22 14:03:00  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.25  1999/08/12 19:19:38  malthoff&n; *&t;Add PHY_B_AC_TX_TST bit according to BCOM A1 errata sheet.&n; *&t;&n; *&t;Revision 1.24  1999/07/30 11:27:21  cgoos&n; *&t;Fixed a missing end-of-comment.&n; *&t;&n; *&t;Revision 1.23  1999/07/30 07:03:31  malthoff&n; *&t;Cut some long comments.&n; *&t;Correct the XMAC PHY ID definitions.&n; *&t;&n; *&t;Revision 1.22  1999/05/19 07:33:18  cgoos&n; *&t;Changes for 1000Base-T.&n; *&t;&n; *&t;Revision 1.21  1999/03/25 07:46:11  malthoff&n; *&t;Add XM_HW_CFG, XM_TS_READ, and XM_TS_LOAD registers.&n; *&t;&n; *&t;Revision 1.20  1999/03/12 13:36:09  malthoff&n; *&t;Remove __STDC__.&n; *&n; *&t;Revision 1.19  1998/12/10 12:22:54  gklug&n; *&t;fix: RX_PAGE must be in interrupt mask&n; *&n; *&t;Revision 1.18  1998/12/10 10:36:36  gklug&n; *&t;fix: swap of pause bits&n; *&n; *&t;Revision 1.17  1998/11/18 13:21:45  gklug&n; *&t;fix: Default interrupt mask&n; *&n; *&t;Revision 1.16  1998/10/29 15:53:21  gklug&n; *&t;fix: Default mask uses ASS (GP0) signal&n; *&n; *&t;Revision 1.15  1998/10/28 13:52:52  malthoff&n; *&t;Add new bits in RX_CMD register.&n; *&n; *&t;Revision 1.14  1998/10/19 15:34:53  gklug&n; *&t;fix: typos&n; *&n; *&t;Revision 1.13  1998/10/14 07:19:03  malthoff&n; *&t;bug fix: Every define which describes bit 31&n; *&t;must be declared as unsigned long &squot;UL&squot;.&n; *&t;fix bit definitions of PHY_AN_RFB and PHY_AN_PAUSE.&n; *&t;Remove ANP defines. Rework the RFB defines.&n; *&n; *&t;Revision 1.12  1998/10/14 06:22:44  cgoos&n; *&t;Changed shifted constant to ULONG.&n; *&n; *&t;Revision 1.11  1998/10/14 05:43:26  gklug&n; *&t;add: shift pause coding&n; *&t;fix: PAUSE bits definition&n; *&n; *&t;Revision 1.10  1998/10/13 09:19:21  malthoff&n; *&t;Again change XMR_FS_ANY_ERR because of new info from XaQti.&n; *&n; *&t;Revision 1.9  1998/10/09 07:58:30  malthoff&n; *&t;Add XMR_FS_FCS_ERR to XMR_FS_ANY_ERR.&n; *&n; *&t;Revision 1.8  1998/10/09 07:18:17  malthoff&n; *&t;bug fix of a bug fix: XM_PAUSE_MODE and XM_DEF_MODE&n; *&t;are not inverted! Bug XM_DEF_MSK is inverted.&n; *&n; *&t;Revision 1.7  1998/10/05 08:04:32  malthoff&n; *&t;bug fix: XM_PAUSE_MODE and XM_DEF_MODE&n; *&t;must be inverted declarations.&n; *&n; *&t;Revision 1.6  1998/09/28 13:38:18  malthoff&n; *&t;Add default modes and masks XM_DEF_MSK,&n; *&t;XM_PAUSE_MODE and XM_DEF_MODE&n; *&n; *&t;Revision 1.5  1998/09/16 14:42:04  malthoff&n; *&t;Bug Fix: XM_GP_PORT is a 32 bit (not a 16 bit) register.&n; *&n; *&t;Revision 1.4  1998/08/20 14:59:47  malthoff&n; *&t;Rework this file after reading the XaQti data sheet&n; *&t;&quot;Differences between Rev. B2 &amp; Rev. C XMAC II&quot;.&n; *&t;This file is now 100% XMAC II Rev. C complained.&n; *&n; *&t;Revision 1.3  1998/06/29 12:18:23  malthoff&n; *&t;Correct XMR_FS_ANY_ERR definition.&n; *&n; *&t;Revision 1.2  1998/06/29 12:10:56  malthoff&n; *&t;Add define XMR_FS_ANY_ERR.&n; *&n; *&t;Revision 1.1  1998/06/19 13:37:17  malthoff&n; *&t;created.&n; *&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_XMAC_H
DECL|macro|__INC_XMAC_H
mdefine_line|#define __INC_XMAC_H
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif&t;/* __cplusplus */
multiline_comment|/* defines ********************************************************************/
multiline_comment|/*&n; * XMAC II registers&n; *&n; * The XMAC registers are 16 or 32 bits wide.&n; * The XMACs host processor interface is set to 16 bit mode,&n; * therefore ALL registers will be addressed with 16 bit accesses.&n; *&n; * The following macros are provided to access the XMAC registers&n; * XM_IN16(), XM_OUT16, XM_IN32(), XM_OUT32(), XM_INADR(), XM_OUTADR(),&n; * XM_INHASH(), and XM_OUTHASH().&n; * The macros are defined in SkGeHw.h.&n; *&n; * Note:&t;NA reg&t;= Network Address e.g DA, SA etc.&n; *&n; */
DECL|macro|XM_MMU_CMD
mdefine_line|#define XM_MMU_CMD&t;&t;0x0000&t;/* 16 bit r/w&t;MMU Command Register */
multiline_comment|/* 0x0004:&t;&t;reserved */
DECL|macro|XM_POFF
mdefine_line|#define XM_POFF&t;&t;&t;0x0008&t;/* 32 bit r/w&t;Packet Offset Register */
DECL|macro|XM_BURST
mdefine_line|#define XM_BURST&t;&t;0x000c&t;/* 32 bit r/w&t;Burst Register for half duplex*/
DECL|macro|XM_1L_VLAN_TAG
mdefine_line|#define XM_1L_VLAN_TAG&t;0x0010&t;/* 16 bit r/w&t;One Level VLAN Tag ID */
DECL|macro|XM_2L_VLAN_TAG
mdefine_line|#define XM_2L_VLAN_TAG&t;0x0014&t;/* 16 bit r/w&t;Two Level VLAN Tag ID */
multiline_comment|/* 0x0018 - 0x001e:&t;reserved */
DECL|macro|XM_TX_CMD
mdefine_line|#define XM_TX_CMD&t;&t;0x0020&t;/* 16 bit r/w&t;Transmit Command Register */
DECL|macro|XM_TX_RT_LIM
mdefine_line|#define XM_TX_RT_LIM&t;0x0024&t;/* 16 bit r/w&t;Transmit Retry Limit Register */
DECL|macro|XM_TX_STIME
mdefine_line|#define XM_TX_STIME&t;&t;0x0028&t;/* 16 bit r/w&t;Transmit Slottime Register */
DECL|macro|XM_TX_IPG
mdefine_line|#define XM_TX_IPG&t;&t;0x002c&t;/* 16 bit r/w&t;Transmit Inter Packet Gap */
DECL|macro|XM_RX_CMD
mdefine_line|#define XM_RX_CMD&t;&t;0x0030&t;/* 16 bit r/w&t;Receive Command Register */
DECL|macro|XM_PHY_ADDR
mdefine_line|#define XM_PHY_ADDR&t;&t;0x0034&t;/* 16 bit r/w&t;PHY Address Register */
DECL|macro|XM_PHY_DATA
mdefine_line|#define XM_PHY_DATA&t;&t;0x0038&t;/* 16 bit r/w&t;PHY Data Register */
multiline_comment|/* 0x003c: &t;&t;reserved */
DECL|macro|XM_GP_PORT
mdefine_line|#define XM_GP_PORT&t;&t;0x0040&t;/* 32 bit r/w&t;General Purpose Port Register */
DECL|macro|XM_IMSK
mdefine_line|#define XM_IMSK&t;&t;&t;0x0044&t;/* 16 bit r/w&t;Interrupt Mask Register */
DECL|macro|XM_ISRC
mdefine_line|#define XM_ISRC&t;&t;&t;0x0048&t;/* 16 bit r/o&t;Interrupt Status Register */
DECL|macro|XM_HW_CFG
mdefine_line|#define XM_HW_CFG&t;&t;0x004c&t;/* 16 bit r/w&t;Hardware Config Register */
multiline_comment|/* 0x0050 - 0x005e:&t;reserved */
DECL|macro|XM_TX_LO_WM
mdefine_line|#define XM_TX_LO_WM&t;&t;0x0060&t;/* 16 bit r/w&t;Tx FIFO Low Water Mark */
DECL|macro|XM_TX_HI_WM
mdefine_line|#define XM_TX_HI_WM&t;&t;0x0062&t;/* 16 bit r/w&t;Tx FIFO High Water Mark */
DECL|macro|XM_TX_THR
mdefine_line|#define XM_TX_THR&t;&t;0x0064&t;/* 16 bit r/w&t;Tx Request Threshold */
DECL|macro|XM_HT_THR
mdefine_line|#define XM_HT_THR&t;&t;0x0066&t;/* 16 bit r/w&t;Host Request Threshold */
DECL|macro|XM_PAUSE_DA
mdefine_line|#define XM_PAUSE_DA&t;&t;0x0068&t;/* NA reg r/w&t;Pause Destination Address */
multiline_comment|/* 0x006e: &t;&t;reserved */
DECL|macro|XM_CTL_PARA
mdefine_line|#define XM_CTL_PARA&t;&t;0x0070&t;/* 32 bit r/w&t;Control Parameter Register */
DECL|macro|XM_MAC_OPCODE
mdefine_line|#define XM_MAC_OPCODE&t;0x0074&t;/* 16 bit r/w&t;Opcode for MAC control frames */
DECL|macro|XM_MAC_PTIME
mdefine_line|#define XM_MAC_PTIME&t;0x0076&t;/* 16 bit r/w&t;Pause time for MAC ctrl frames*/
DECL|macro|XM_TX_STAT
mdefine_line|#define XM_TX_STAT&t;&t;0x0078&t;/* 32 bit r/o&t;Tx Status LIFO Register */
multiline_comment|/* 0x0080 - 0x00fc:&t;16 NA reg r/w&t;Exact Match Address Registers */
multiline_comment|/* &t;&t;&t;&t;use the XM_EXM() macro to address */
DECL|macro|XM_EXM_START
mdefine_line|#define XM_EXM_START&t;0x0080&t;/* r/w&t;Start Address of the EXM Regs */
multiline_comment|/*&n;&t; * XM_EXM(Reg)&n;&t; *&n;&t; * returns the XMAC address offset of specified Exact Match Addr Reg&n;&t; *&n;&t; * para:&t;Reg&t;EXM register to addr&t;(0 .. 15)&n;&t; *&n;&t; * usage:&t;XM_INADDR(IoC, MAC_1, XM_EXM(i), &amp;val[i]);&n;&t; */
DECL|macro|XM_EXM
mdefine_line|#define XM_EXM(Reg)&t;(XM_EXM_START + ((Reg) &lt;&lt; 3))
DECL|macro|XM_SRC_CHK
mdefine_line|#define XM_SRC_CHK&t;&t;0x0100&t;/* NA reg r/w&t;Source Check Address Register */
DECL|macro|XM_SA
mdefine_line|#define XM_SA&t;&t;&t;0x0108&t;/* NA reg r/w&t;Station Address Register */
DECL|macro|XM_HSM
mdefine_line|#define XM_HSM&t;&t;&t;0x0110&t;/* 64 bit r/w&t;Hash Match Address Registers */
DECL|macro|XM_RX_LO_WM
mdefine_line|#define XM_RX_LO_WM&t;&t;0x0118&t;/* 16 bit r/w&t;Receive Low Water Mark */
DECL|macro|XM_RX_HI_WM
mdefine_line|#define XM_RX_HI_WM&t;&t;0x011a&t;/* 16 bit r/w&t;Receive High Water Mark */
DECL|macro|XM_RX_THR
mdefine_line|#define XM_RX_THR&t;&t;0x011c&t;/* 32 bit r/w&t;Receive Request Threshold */
DECL|macro|XM_DEV_ID
mdefine_line|#define XM_DEV_ID&t;&t;0x0120&t;/* 32 bit r/o&t;Device ID Register */
DECL|macro|XM_MODE
mdefine_line|#define XM_MODE&t;&t;&t;0x0124&t;/* 32 bit r/w&t;Mode Register */
DECL|macro|XM_LSA
mdefine_line|#define XM_LSA&t;&t;&t;0x0128&t;/* NA reg r/o&t;Last Source Register */
multiline_comment|/* 0x012e:&t;&t;reserved */
DECL|macro|XM_TS_READ
mdefine_line|#define XM_TS_READ&t;&t;0x0130&t;/* 32 bit r/o&t;Time Stamp Read Register */
DECL|macro|XM_TS_LOAD
mdefine_line|#define XM_TS_LOAD&t;&t;0x0134&t;/* 32 bit r/o&t;Time Stamp Load Value */
multiline_comment|/* 0x0138 - 0x01fe:&t;reserved */
DECL|macro|XM_STAT_CMD
mdefine_line|#define XM_STAT_CMD&t;0x0200&t;/* 16 bit r/w&t;Statistics Command Register */
DECL|macro|XM_RX_CNT_EV
mdefine_line|#define XM_RX_CNT_EV&t;0x0204&t;/* 32 bit r/o&t;Rx Counter Event Register */
DECL|macro|XM_TX_CNT_EV
mdefine_line|#define XM_TX_CNT_EV&t;0x0208&t;/* 32 bit r/o&t;Tx Counter Event Register */
DECL|macro|XM_RX_EV_MSK
mdefine_line|#define XM_RX_EV_MSK&t;0x020c&t;/* 32 bit r/w&t;Rx Counter Event Mask */
DECL|macro|XM_TX_EV_MSK
mdefine_line|#define XM_TX_EV_MSK&t;0x0210&t;/* 32 bit r/w&t;Tx Counter Event Mask */
multiline_comment|/* 0x0204 - 0x027e:&t;reserved */
DECL|macro|XM_TXF_OK
mdefine_line|#define XM_TXF_OK&t;&t;0x0280&t;/* 32 bit r/o&t;Frames Transmitted OK Conuter */
DECL|macro|XM_TXO_OK_HI
mdefine_line|#define XM_TXO_OK_HI&t;0x0284&t;/* 32 bit r/o&t;Octets Transmitted OK High Cnt*/
DECL|macro|XM_TXO_OK_LO
mdefine_line|#define XM_TXO_OK_LO&t;0x0288&t;/* 32 bit r/o&t;Octets Transmitted OK Low Cnt */
DECL|macro|XM_TXF_BC_OK
mdefine_line|#define XM_TXF_BC_OK&t;0x028c&t;/* 32 bit r/o&t;Broadcast Frames Xmitted OK */
DECL|macro|XM_TXF_MC_OK
mdefine_line|#define XM_TXF_MC_OK&t;0x0290&t;/* 32 bit r/o&t;Multicast Frames Xmitted OK */
DECL|macro|XM_TXF_UC_OK
mdefine_line|#define XM_TXF_UC_OK&t;0x0294&t;/* 32 bit r/o&t;Unicast Frames Xmitted OK */
DECL|macro|XM_TXF_LONG
mdefine_line|#define XM_TXF_LONG&t;&t;0x0298&t;/* 32 bit r/o&t;Tx Long Frame Counter */
DECL|macro|XM_TXE_BURST
mdefine_line|#define XM_TXE_BURST&t;0x029c&t;/* 32 bit r/o&t;Tx Burst Event Counter */
DECL|macro|XM_TXF_MPAUSE
mdefine_line|#define XM_TXF_MPAUSE&t;0x02a0&t;/* 32 bit r/o&t;Tx Pause MAC Ctrl Frame Cnt */
DECL|macro|XM_TXF_MCTRL
mdefine_line|#define XM_TXF_MCTRL&t;0x02a4&t;/* 32 bit r/o&t;Tx MAC Ctrl Frame Counter */
DECL|macro|XM_TXF_SNG_COL
mdefine_line|#define XM_TXF_SNG_COL&t;0x02a8&t;/* 32 bit r/o&t;Tx Single Collision Counter */
DECL|macro|XM_TXF_MUL_COL
mdefine_line|#define XM_TXF_MUL_COL&t;0x02ac&t;/* 32 bit r/o&t;Tx Multiple Collision Counter */
DECL|macro|XM_TXF_ABO_COL
mdefine_line|#define XM_TXF_ABO_COL&t;0x02b0&t;/* 32 bit r/o&t;Tx aborted due to Exces. Col. */
DECL|macro|XM_TXF_LAT_COL
mdefine_line|#define XM_TXF_LAT_COL&t;0x02b4&t;/* 32 bit r/o&t;Tx Late Collision Counter */
DECL|macro|XM_TXF_DEF
mdefine_line|#define XM_TXF_DEF&t;&t;0x02b8&t;/* 32 bit r/o&t;Tx Deferred Frame Counter */
DECL|macro|XM_TXF_EX_DEF
mdefine_line|#define XM_TXF_EX_DEF&t;0x02bc&t;/* 32 bit r/o&t;Tx Excessive Deferall Counter */
DECL|macro|XM_TXE_FIFO_UR
mdefine_line|#define XM_TXE_FIFO_UR&t;0x02c0&t;/* 32 bit r/o&t;Tx FIFO Underrun Event Cnt */
DECL|macro|XM_TXE_CS_ERR
mdefine_line|#define XM_TXE_CS_ERR&t;0x02c4&t;/* 32 bit r/o&t;Tx Carrier Sense Error Cnt */
DECL|macro|XM_TXP_UTIL
mdefine_line|#define XM_TXP_UTIL&t;&t;0x02c8&t;/* 32 bit r/o&t;Tx Utilization in % */
multiline_comment|/* 0x02cc - 0x02ce:&t;reserved */
DECL|macro|XM_TXF_64B
mdefine_line|#define XM_TXF_64B&t;&t;0x02d0&t;/* 32 bit r/o&t;64 Byte Tx Frame Counter */
DECL|macro|XM_TXF_127B
mdefine_line|#define XM_TXF_127B&t;&t;0x02d4&t;/* 32 bit r/o&t;65-127 Byte Tx Frame Counter */
DECL|macro|XM_TXF_255B
mdefine_line|#define XM_TXF_255B&t;&t;0x02d8&t;/* 32 bit r/o&t;128-255 Byte Tx Frame Counter */
DECL|macro|XM_TXF_511B
mdefine_line|#define XM_TXF_511B&t;&t;0x02dc&t;/* 32 bit r/o&t;256-511 Byte Tx Frame Counter */
DECL|macro|XM_TXF_1023B
mdefine_line|#define XM_TXF_1023B&t;0x02e0&t;/* 32 bit r/o&t;512-1023 Byte Tx Frame Counter*/
DECL|macro|XM_TXF_MAX_SZ
mdefine_line|#define XM_TXF_MAX_SZ&t;0x02e4&t;/* 32 bit r/o&t;1024-MaxSize Byte Tx Frame Cnt*/
multiline_comment|/* 0x02e8 - 0x02fe:&t;reserved */
DECL|macro|XM_RXF_OK
mdefine_line|#define XM_RXF_OK&t;&t;0x0300&t;/* 32 bit r/o&t;Frames Received OK */
DECL|macro|XM_RXO_OK_HI
mdefine_line|#define XM_RXO_OK_HI&t;0x0304&t;/* 32 bit r/o&t;Octets Received OK High Cnt */
DECL|macro|XM_RXO_OK_LO
mdefine_line|#define XM_RXO_OK_LO&t;0x0308&t;/* 32 bit r/o&t;Octets Received OK Low Counter*/
DECL|macro|XM_RXF_BC_OK
mdefine_line|#define XM_RXF_BC_OK&t;0x030c&t;/* 32 bit r/o&t;Broadcast Frames Received OK */
DECL|macro|XM_RXF_MC_OK
mdefine_line|#define XM_RXF_MC_OK&t;0x0310&t;/* 32 bit r/o&t;Multicast Frames Received OK */
DECL|macro|XM_RXF_UC_OK
mdefine_line|#define XM_RXF_UC_OK&t;0x0314&t;/* 32 bit r/o&t;Unicast Frames Received OK */
DECL|macro|XM_RXF_MPAUSE
mdefine_line|#define XM_RXF_MPAUSE&t;0x0318&t;/* 32 bit r/o&t;Rx Pause MAC Ctrl Frame Cnt */
DECL|macro|XM_RXF_MCTRL
mdefine_line|#define XM_RXF_MCTRL&t;0x031c&t;/* 32 bit r/o&t;Rx MAC Ctrl Frame Counter */
DECL|macro|XM_RXF_INV_MP
mdefine_line|#define XM_RXF_INV_MP&t;0x0320&t;/* 32 bit r/o&t;Rx invalid Pause Frame Cnt */
DECL|macro|XM_RXF_INV_MOC
mdefine_line|#define XM_RXF_INV_MOC&t;0x0324&t;/* 32 bit r/o&t;Rx Frames with inv. MAC Opcode*/
DECL|macro|XM_RXE_BURST
mdefine_line|#define XM_RXE_BURST&t;0x0328&t;/* 32 bit r/o&t;Rx Burst Event Counter */
DECL|macro|XM_RXE_FMISS
mdefine_line|#define XM_RXE_FMISS&t;0x032c&t;/* 32 bit r/o&t;Rx Missed Frames Event Cnt */
DECL|macro|XM_RXF_FRA_ERR
mdefine_line|#define XM_RXF_FRA_ERR&t;0x0330&t;/* 32 bit r/o&t;Rx Framing Error Counter */
DECL|macro|XM_RXE_FIFO_OV
mdefine_line|#define XM_RXE_FIFO_OV&t;0x0334&t;/* 32 bit r/o&t;Rx FIFO overflow Event Cnt */
DECL|macro|XM_RXF_JAB_PKT
mdefine_line|#define XM_RXF_JAB_PKT&t;0x0338&t;/* 32 bit r/o&t;Rx Jabber Packet Frame Cnt */
DECL|macro|XM_RXE_CAR_ERR
mdefine_line|#define XM_RXE_CAR_ERR&t;0x033c&t;/* 32 bit r/o&t;Rx Carrier Event Error Cnt */
DECL|macro|XM_RXF_LEN_ERR
mdefine_line|#define XM_RXF_LEN_ERR&t;0x0340&t;/* 32 bit r/o&t;Rx in Range Length Error */
DECL|macro|XM_RXE_SYM_ERR
mdefine_line|#define XM_RXE_SYM_ERR&t;0x0344&t;/* 32 bit r/o&t;Rx Symbol Error Counter */
DECL|macro|XM_RXE_SHT_ERR
mdefine_line|#define XM_RXE_SHT_ERR&t;0x0348&t;/* 32 bit r/o&t;Rx Short Event Error Cnt */
DECL|macro|XM_RXE_RUNT
mdefine_line|#define XM_RXE_RUNT&t;&t;0x034c&t;/* 32 bit r/o&t;Rx Runt Event Counter */
DECL|macro|XM_RXF_LNG_ERR
mdefine_line|#define XM_RXF_LNG_ERR&t;0x0350&t;/* 32 bit r/o&t;Rx Frame too Long Error Cnt */
DECL|macro|XM_RXF_FCS_ERR
mdefine_line|#define XM_RXF_FCS_ERR&t;0x0354&t;/* 32 bit r/o&t;Rx Frame Check Seq. Error Cnt */
multiline_comment|/* 0x0358 - 0x035a:&t;reserved */
DECL|macro|XM_RXF_CEX_ERR
mdefine_line|#define XM_RXF_CEX_ERR&t;0x035c&t;/* 32 bit r/o&t;Rx Carrier Ext Error Frame Cnt*/
DECL|macro|XM_RXP_UTIL
mdefine_line|#define XM_RXP_UTIL&t;&t;0x0360&t;/* 32 bit r/o&t;Rx Utilization in % */
multiline_comment|/* 0x0364 - 0x0366:&t;reserved */
DECL|macro|XM_RXF_64B
mdefine_line|#define XM_RXF_64B&t;&t;0x0368&t;/* 32 bit r/o&t;64 Byte Rx Frame Counter */
DECL|macro|XM_RXF_127B
mdefine_line|#define XM_RXF_127B&t;&t;0x036c&t;/* 32 bit r/o&t;65-127 Byte Rx Frame Counter */
DECL|macro|XM_RXF_255B
mdefine_line|#define XM_RXF_255B&t;&t;0x0370&t;/* 32 bit r/o&t;128-255 Byte Rx Frame Counter */
DECL|macro|XM_RXF_511B
mdefine_line|#define XM_RXF_511B&t;&t;0x0374&t;/* 32 bit r/o&t;256-511 Byte Rx Frame Counter */
DECL|macro|XM_RXF_1023B
mdefine_line|#define XM_RXF_1023B&t;0x0378&t;/* 32 bit r/o&t;512-1023 Byte Rx Frame Counter*/
DECL|macro|XM_RXF_MAX_SZ
mdefine_line|#define XM_RXF_MAX_SZ&t;0x037c&t;/* 32 bit r/o&t;1024-MaxSize Byte Rx Frame Cnt*/
multiline_comment|/* 0x02e8 - 0x02fe:&t;reserved */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * XMAC Bit Definitions&n; *&n; * If the bit access behaviour differs from the register access behaviour&n; * (r/w, r/o) this is documented after the bit number.&n; * The following bit access behaviours are used:&n; *&t;(sc)&t;self clearing&n; *&t;(ro)&t;read only&n; */
multiline_comment|/*&t;XM_MMU_CMD&t;16 bit r/w&t;MMU Command Register */
multiline_comment|/* Bit 15..13:&t;reserved */
DECL|macro|XM_MMU_PHY_RDY
mdefine_line|#define XM_MMU_PHY_RDY&t;(1&lt;&lt;12)&t;/* Bit 12:&t;PHY Read Ready */
DECL|macro|XM_MMU_PHY_BUSY
mdefine_line|#define XM_MMU_PHY_BUSY&t;(1&lt;&lt;11)&t;/* Bit 11:&t;PHY Busy */
DECL|macro|XM_MMU_IGN_PF
mdefine_line|#define XM_MMU_IGN_PF&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Ignore Pause Frame */
DECL|macro|XM_MMU_MAC_LB
mdefine_line|#define XM_MMU_MAC_LB&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Enable MAC Loopback */
multiline_comment|/* Bit  8:&t;reserved */
DECL|macro|XM_MMU_FRC_COL
mdefine_line|#define XM_MMU_FRC_COL&t;(1&lt;&lt;7)&t;/* Bit  7:&t;Force Collision */
DECL|macro|XM_MMU_SIM_COL
mdefine_line|#define XM_MMU_SIM_COL&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Simulate Collision */
DECL|macro|XM_MMU_NO_PRE
mdefine_line|#define XM_MMU_NO_PRE&t;(1&lt;&lt;5)&t;/* Bit  5:&t;No MDIO Preamble */
DECL|macro|XM_MMU_GMII_FD
mdefine_line|#define XM_MMU_GMII_FD&t;(1&lt;&lt;4)&t;/* Bit  4:&t;GMII uses Full Duplex */
DECL|macro|XM_MMU_RAT_CTRL
mdefine_line|#define XM_MMU_RAT_CTRL&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Enable Rate Control */
DECL|macro|XM_MMU_GMII_LOOP
mdefine_line|#define XM_MMU_GMII_LOOP (1&lt;&lt;2)&t;/* Bit  2:&t;PHY is in Loopback Mode */
DECL|macro|XM_MMU_ENA_RX
mdefine_line|#define XM_MMU_ENA_RX&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Enable Receiver */
DECL|macro|XM_MMU_ENA_TX
mdefine_line|#define XM_MMU_ENA_TX&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Enable Transmitter */
multiline_comment|/*&t;XM_TX_CMD&t;16 bit r/w&t;Transmit Command Register */
multiline_comment|/* Bit 15..7:&t;reserved */
DECL|macro|XM_TX_BK2BK
mdefine_line|#define XM_TX_BK2BK&t;&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Ignor Carrier Sense (Tx Bk2Bk)*/
DECL|macro|XM_TX_ENC_BYP
mdefine_line|#define XM_TX_ENC_BYP&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Set Encoder in Bypass Mode */
DECL|macro|XM_TX_SAM_LINE
mdefine_line|#define XM_TX_SAM_LINE&t;(1&lt;&lt;4)&t;/* Bit  4: (sc)&t;Start utilization calculation */
DECL|macro|XM_TX_NO_GIG_MD
mdefine_line|#define XM_TX_NO_GIG_MD&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Disable Carrier Extension */
DECL|macro|XM_TX_NO_PRE
mdefine_line|#define XM_TX_NO_PRE&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Disable Preamble Generation */
DECL|macro|XM_TX_NO_CRC
mdefine_line|#define XM_TX_NO_CRC&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Disable CRC Generation */
DECL|macro|XM_TX_AUTO_PAD
mdefine_line|#define XM_TX_AUTO_PAD&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Enable Automatic Padding */
multiline_comment|/*&t;XM_TX_RT_LIM&t;16 bit r/w&t;Transmit Retry Limit Register */
multiline_comment|/* Bit 15..5:&t;reserved */
DECL|macro|XM_RT_LIM_MSK
mdefine_line|#define XM_RT_LIM_MSK&t;0x1f&t;/* Bit  4..0:&t;Tx Retry Limit */
multiline_comment|/*&t;XM_TX_STIME&t;16 bit r/w&t;Transmit Slottime Register */
multiline_comment|/* Bit 15..7:&t;reserved */
DECL|macro|XM_STIME_MSK
mdefine_line|#define XM_STIME_MSK&t;0x7f&t;/* Bit  6..0:&t;Tx Slottime bits */
multiline_comment|/*&t;XM_TX_IPG&t;16 bit r/w&t;Transmit Inter Packet Gap */
multiline_comment|/* Bit 15..8:&t;reserved */
DECL|macro|XM_IPG_MSK
mdefine_line|#define XM_IPG_MSK&t;&t;0xff&t;/* Bit  7..0:&t;IPG value bits */
multiline_comment|/*&t;XM_RX_CMD&t;16 bit r/w&t;Receive Command Register */
multiline_comment|/* Bit 15..9:&t;reserved */
DECL|macro|XM_RX_LENERR_OK
mdefine_line|#define XM_RX_LENERR_OK (1&lt;&lt;8)&t;/* Bit  8&t;don&squot;t set Rx Err bit for */
multiline_comment|/*&t;&t;inrange error packets */
DECL|macro|XM_RX_BIG_PK_OK
mdefine_line|#define XM_RX_BIG_PK_OK&t;(1&lt;&lt;7)&t;/* Bit  7&t;don&squot;t set Rx Err bit for */
multiline_comment|/*&t;&t;jumbo packets */
DECL|macro|XM_RX_IPG_CAP
mdefine_line|#define XM_RX_IPG_CAP&t;(1&lt;&lt;6)&t;/* Bit  6&t;repl. type field with IPG */
DECL|macro|XM_RX_TP_MD
mdefine_line|#define XM_RX_TP_MD&t;&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Enable transparent Mode */
DECL|macro|XM_RX_STRIP_FCS
mdefine_line|#define XM_RX_STRIP_FCS&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Enable FCS Stripping */
DECL|macro|XM_RX_SELF_RX
mdefine_line|#define XM_RX_SELF_RX&t;(1&lt;&lt;3)&t;/* Bit  3: &t;Enable Rx of own packets */
DECL|macro|XM_RX_SAM_LINE
mdefine_line|#define XM_RX_SAM_LINE&t;(1&lt;&lt;2)&t;/* Bit  2: (sc)&t;Start utilization calculation */
DECL|macro|XM_RX_STRIP_PAD
mdefine_line|#define XM_RX_STRIP_PAD&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Strip pad bytes of Rx frames */
DECL|macro|XM_RX_DIS_CEXT
mdefine_line|#define XM_RX_DIS_CEXT&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Disable carrier ext. check */
multiline_comment|/*&t;XM_PHY_ADDR&t;16 bit r/w&t;PHY Address Register */
multiline_comment|/* Bit 15..5:&t;reserved */
DECL|macro|XM_PHY_ADDR_SZ
mdefine_line|#define XM_PHY_ADDR_SZ&t;0x1f&t;/* Bit  4..0:&t;PHY Address bits */
multiline_comment|/*&t;XM_GP_PORT&t;32 bit r/w&t;General Purpose Port Register */
multiline_comment|/* Bit 31..7:&t;reserved */
DECL|macro|XM_GP_ANIP
mdefine_line|#define XM_GP_ANIP&t;&t;(1L&lt;&lt;6)&t;/* Bit  6: (ro)&t;Auto-Neg. in progress */
DECL|macro|XM_GP_FRC_INT
mdefine_line|#define XM_GP_FRC_INT&t;(1L&lt;&lt;5)&t;/* Bit  5: (sc)&t;Force Interrupt */
multiline_comment|/* Bit  4:&t;reserved */
DECL|macro|XM_GP_RES_MAC
mdefine_line|#define XM_GP_RES_MAC&t;(1L&lt;&lt;3)&t;/* Bit  3: (sc)&t;Reset MAC and FIFOs */
DECL|macro|XM_GP_RES_STAT
mdefine_line|#define XM_GP_RES_STAT&t;(1L&lt;&lt;2)&t;/* Bit  2: (sc)&t;Reset the statistics module */
multiline_comment|/* Bit  1:&t;reserved */
DECL|macro|XM_GP_INP_ASS
mdefine_line|#define XM_GP_INP_ASS&t;(1L&lt;&lt;0)&t;/* Bit  0: (ro) GP Input Pin asserted */
multiline_comment|/*&t;XM_IMSK&t;&t;16 bit r/w&t;Interrupt Mask Register */
multiline_comment|/*&t;XM_ISRC&t;&t;16 bit r/o&t;Interrupt Status Register */
multiline_comment|/* Bit 15:&t;reserved */
DECL|macro|XM_IS_LNK_AE
mdefine_line|#define XM_IS_LNK_AE&t;(1&lt;&lt;14) /* Bit 14:&t;Link Asynchronous Event */
DECL|macro|XM_IS_TX_ABORT
mdefine_line|#define XM_IS_TX_ABORT&t;(1&lt;&lt;13) /* Bit 13:&t;Transmit Abort, late Col. etc */
DECL|macro|XM_IS_FRC_INT
mdefine_line|#define XM_IS_FRC_INT&t;(1&lt;&lt;12) /* Bit 12:&t;Force INT bit set in GP */
DECL|macro|XM_IS_INP_ASS
mdefine_line|#define XM_IS_INP_ASS&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Input Asserted, GP bit 0 set */
DECL|macro|XM_IS_LIPA_RC
mdefine_line|#define XM_IS_LIPA_RC&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Link Partner requests config */
DECL|macro|XM_IS_RX_PAGE
mdefine_line|#define XM_IS_RX_PAGE&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Page Received */
DECL|macro|XM_IS_TX_PAGE
mdefine_line|#define XM_IS_TX_PAGE&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Next Page Loaded for Transmit */
DECL|macro|XM_IS_AND
mdefine_line|#define XM_IS_AND&t;&t;(1&lt;&lt;7)&t;/* Bit  7:&t;Auto-Negotiation Done */
DECL|macro|XM_IS_TSC_OV
mdefine_line|#define XM_IS_TSC_OV&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Time Stamp Counter Overflow */
DECL|macro|XM_IS_RXC_OV
mdefine_line|#define XM_IS_RXC_OV&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Rx Counter Event Overflow */
DECL|macro|XM_IS_TXC_OV
mdefine_line|#define XM_IS_TXC_OV&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Tx Counter Event Overflow */
DECL|macro|XM_IS_RXF_OV
mdefine_line|#define XM_IS_RXF_OV&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Receive FIFO Overflow */
DECL|macro|XM_IS_TXF_UR
mdefine_line|#define XM_IS_TXF_UR&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Transmit FIFO Underrun */
DECL|macro|XM_IS_TX_COMP
mdefine_line|#define XM_IS_TX_COMP&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Frame Tx Complete */
DECL|macro|XM_IS_RX_COMP
mdefine_line|#define XM_IS_RX_COMP&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Frame Rx Complete */
DECL|macro|XM_DEF_MSK
mdefine_line|#define XM_DEF_MSK&t;(~(XM_IS_INP_ASS | XM_IS_LIPA_RC | XM_IS_RX_PAGE |&bslash;&n;&t;&t;&t;XM_IS_AND | XM_IS_RXC_OV | XM_IS_TXC_OV | XM_IS_TXF_UR))
multiline_comment|/*&t;XM_HW_CFG&t;16 bit r/w&t;Hardware Config Register */
multiline_comment|/* Bit 15.. 4:&t;reserved */
DECL|macro|XM_HW_GEN_EOP
mdefine_line|#define XM_HW_GEN_EOP&t;(1&lt;&lt;3)&t;/* Bit  3:&t;generate End of Packet pulse */
DECL|macro|XM_HW_COM4SIG
mdefine_line|#define XM_HW_COM4SIG&t;(1&lt;&lt;2)&t;/* Bit  2:&t;use Comma Detect for Sig. Det.*/
multiline_comment|/* Bit  1:&t;reserved */
DECL|macro|XM_HW_GMII_MD
mdefine_line|#define XM_HW_GMII_MD&t;(1&lt;&lt;0)&t;/* Bit  0:&t;GMII Interface selected */
multiline_comment|/*&t;XM_TX_LO_WM&t;16 bit r/w&t;Tx FIFO Low Water Mark */
multiline_comment|/*&t;XM_TX_HI_WM&t;16 bit r/w&t;Tx FIFO High Water Mark */
multiline_comment|/* Bit 15..10&t;reserved */
DECL|macro|XM_TX_WM_MSK
mdefine_line|#define XM_TX_WM_MSK&t;0x01ff&t;/* Bit  9.. 0&t;Tx FIFO Watermark bits */
multiline_comment|/*&t;XM_TX_THR&t;16 bit r/w&t;Tx Request Threshold */
multiline_comment|/*&t;XM_HT_THR&t;16 bit r/w&t;Host Request Threshold */
multiline_comment|/*&t;XM_RX_THR&t;16 bit r/w&t;Rx Request Threshold */
multiline_comment|/* Bit 15..11&t;reserved */
DECL|macro|XM_THR_MSK
mdefine_line|#define XM_THR_MSK&t;&t;0x03ff&t;/* Bit 10.. 0&t;Rx/Tx Request Threshold bits */
multiline_comment|/*&t;XM_TX_STAT&t;32 bit r/o&t;Tx Status LIFO Register */
DECL|macro|XM_ST_VALID
mdefine_line|#define XM_ST_VALID&t;&t;(1UL&lt;&lt;31)&t;/* Bit 31:&t;Status Valid */
DECL|macro|XM_ST_BYTE_CNT
mdefine_line|#define XM_ST_BYTE_CNT&t;(0x3fffL&lt;&lt;17)&t;/* Bit 30..17:&t;Tx frame Length */
DECL|macro|XM_ST_RETRY_CNT
mdefine_line|#define XM_ST_RETRY_CNT&t;(0x1fL&lt;&lt;12)&t;/* Bit 16..12:&t;Retry Count */
DECL|macro|XM_ST_EX_COL
mdefine_line|#define XM_ST_EX_COL&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Excessive Collisions */
DECL|macro|XM_ST_EX_DEF
mdefine_line|#define XM_ST_EX_DEF&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Excessive Deferral */
DECL|macro|XM_ST_BURST
mdefine_line|#define XM_ST_BURST&t;&t;(1L&lt;&lt;9)&t;&t;/* Bit  9:&t;p. xmitted in burst md*/
DECL|macro|XM_ST_DEFER
mdefine_line|#define XM_ST_DEFER&t;&t;(1L&lt;&lt;8)&t;&t;/* Bit  8:&t;packet was defered */
DECL|macro|XM_ST_BC
mdefine_line|#define XM_ST_BC&t;&t;(1L&lt;&lt;7)&t;&t;/* Bit  7:&t;Broadcast packet */
DECL|macro|XM_ST_MC
mdefine_line|#define XM_ST_MC&t;&t;(1L&lt;&lt;6)&t;&t;/* Bit  6:&t;Multicast packet */
DECL|macro|XM_ST_UC
mdefine_line|#define XM_ST_UC&t;&t;(1L&lt;&lt;5)&t;&t;/* Bit  5:&t;Unicast packet */
DECL|macro|XM_ST_TX_UR
mdefine_line|#define XM_ST_TX_UR&t;&t;(1L&lt;&lt;4)&t;&t;/* Bit  4:&t;FIFO Underrun occured */
DECL|macro|XM_ST_CS_ERR
mdefine_line|#define XM_ST_CS_ERR&t;(1L&lt;&lt;3)&t;&t;/* Bit  3:&t;Carrier Sense Error */
DECL|macro|XM_ST_LAT_COL
mdefine_line|#define XM_ST_LAT_COL&t;(1L&lt;&lt;2)&t;&t;/* Bit  2:&t;Late Collision Error */
DECL|macro|XM_ST_MUL_COL
mdefine_line|#define XM_ST_MUL_COL&t;(1L&lt;&lt;1)&t;&t;/* Bit  1:&t;Multiple Collisions */
DECL|macro|XM_ST_SGN_COL
mdefine_line|#define XM_ST_SGN_COL&t;(1L&lt;&lt;0)&t;&t;/* Bit  0:&t;Single Collision */
multiline_comment|/*&t;XM_RX_LO_WM&t;16 bit r/w&t;Receive Low Water Mark */
multiline_comment|/*&t;XM_RX_HI_WM&t;16 bit r/w&t;Receive High Water Mark */
multiline_comment|/* Bit 15..11:&t;reserved */
DECL|macro|XM_RX_WM_MSK
mdefine_line|#define XM_RX_WM_MSK&t;0x03ff&t;&t;/* Bit 11.. 0:&t;Rx FIFO Watermark bits */
multiline_comment|/*&t;XM_DEV_ID&t;32 bit r/o&t;Device ID Register */
DECL|macro|XM_DEV_OUI
mdefine_line|#define XM_DEV_OUI&t;(0x00ffffffUL&lt;&lt;8)&t;/* Bit 31..8:&t;Device OUI */
DECL|macro|XM_DEV_REV
mdefine_line|#define XM_DEV_REV&t;(0x07L &lt;&lt; 5)&t;&t;/* Bit  7..5:&t;Chip Rev Num */
multiline_comment|/*&t;XM_MODE&t;&t;32 bit r/w&t;Mode Register */
multiline_comment|/* Bit 31..27:&t;reserved */
DECL|macro|XM_MD_ENA_REJ
mdefine_line|#define XM_MD_ENA_REJ&t;(1L&lt;&lt;26)&t;/* Bit 26:&t;Enable Frame Reject */
DECL|macro|XM_MD_SPOE_E
mdefine_line|#define XM_MD_SPOE_E&t;(1L&lt;&lt;25)&t;/* Bit 25:&t;Send Pause on Edge */
multiline_comment|/* &t;&t;extern generated */
DECL|macro|XM_MD_TX_REP
mdefine_line|#define XM_MD_TX_REP&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;Transmit Repeater Mode */
DECL|macro|XM_MD_SPOFF_I
mdefine_line|#define XM_MD_SPOFF_I&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;Send Pause on FIFO full */
multiline_comment|/*&t;&t;intern generated */
DECL|macro|XM_MD_LE_STW
mdefine_line|#define XM_MD_LE_STW&t;(1L&lt;&lt;22)&t;/* Bit 22:&t;Rx Stat Word in Little Endian */
DECL|macro|XM_MD_TX_CONT
mdefine_line|#define XM_MD_TX_CONT&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;Send Continuous */
DECL|macro|XM_MD_TX_PAUSE
mdefine_line|#define XM_MD_TX_PAUSE&t;(1L&lt;&lt;20)&t;/* Bit 20: (sc)&t;Send Pause Frame */
DECL|macro|XM_MD_ATS
mdefine_line|#define XM_MD_ATS&t;&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;Append Time Stamp */
DECL|macro|XM_MD_SPOL_I
mdefine_line|#define XM_MD_SPOL_I&t;(1L&lt;&lt;18)&t;/* Bit 18:&t;Send Pause on Low */
multiline_comment|/*&t;&t;intern generated */
DECL|macro|XM_MD_SPOH_I
mdefine_line|#define XM_MD_SPOH_I&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;Send Pause on High */
multiline_comment|/*&t;&t;intern generated */
DECL|macro|XM_MD_CAP
mdefine_line|#define XM_MD_CAP&t;&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;Check Address Pair */
DECL|macro|XM_MD_ENA_HASH
mdefine_line|#define XM_MD_ENA_HASH&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Enable Hashing */
DECL|macro|XM_MD_CSA
mdefine_line|#define XM_MD_CSA&t;&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;Check Station Address */
DECL|macro|XM_MD_CAA
mdefine_line|#define XM_MD_CAA&t;&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Check Address Array */
DECL|macro|XM_MD_RX_MCTRL
mdefine_line|#define XM_MD_RX_MCTRL&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Rx MAC Control Frame */
DECL|macro|XM_MD_RX_RUNT
mdefine_line|#define XM_MD_RX_RUNT&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Rx Runt Frames */
DECL|macro|XM_MD_RX_IRLE
mdefine_line|#define XM_MD_RX_IRLE&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Rx in Range Len Err Frame */
DECL|macro|XM_MD_RX_LONG
mdefine_line|#define XM_MD_RX_LONG&t;(1L&lt;&lt;9)&t;&t;/* Bit  9:&t;Rx Long Frame */
DECL|macro|XM_MD_RX_CRCE
mdefine_line|#define XM_MD_RX_CRCE&t;(1L&lt;&lt;8)&t;&t;/* Bit  8:&t;Rx CRC Error Frame */
DECL|macro|XM_MD_RX_ERR
mdefine_line|#define XM_MD_RX_ERR&t;(1L&lt;&lt;7)&t;&t;/* Bit  7:&t;Rx Error Frame */
DECL|macro|XM_MD_DIS_UC
mdefine_line|#define XM_MD_DIS_UC&t;(1L&lt;&lt;6)&t;&t;/* Bit  6:&t;Disable Rx Unicast */
DECL|macro|XM_MD_DIS_MC
mdefine_line|#define XM_MD_DIS_MC&t;(1L&lt;&lt;5)&t;&t;/* Bit  5:&t;Disable Rx Multicast */
DECL|macro|XM_MD_DIS_BC
mdefine_line|#define XM_MD_DIS_BC&t;(1L&lt;&lt;4)&t;&t;/* Bit  4:&t;Disable Rx Broadcast */
DECL|macro|XM_MD_ENA_PROM
mdefine_line|#define XM_MD_ENA_PROM&t;(1L&lt;&lt;3)&t;&t;/* Bit  3:&t;Enable Promiscuous */
DECL|macro|XM_MD_ENA_BE
mdefine_line|#define XM_MD_ENA_BE&t;(1L&lt;&lt;2)&t;&t;/* Bit  2:&t;Enable Big Endian */
DECL|macro|XM_MD_FTF
mdefine_line|#define XM_MD_FTF&t;&t;(1L&lt;&lt;1)&t;&t;/* Bit  1: (sc)&t;Flush Tx FIFO */
DECL|macro|XM_MD_FRF
mdefine_line|#define XM_MD_FRF&t;&t;(1L&lt;&lt;0)&t;&t;/* Bit  0: (sc)&t;Flush Rx FIFO */
DECL|macro|XM_PAUSE_MODE
mdefine_line|#define XM_PAUSE_MODE&t;(XM_MD_SPOE_E | XM_MD_SPOL_I | XM_MD_SPOH_I)
DECL|macro|XM_DEF_MODE
mdefine_line|#define XM_DEF_MODE&t;&t;(XM_MD_RX_RUNT | XM_MD_RX_IRLE | XM_MD_RX_LONG |&bslash;&n;&t;&t;&t;&t;XM_MD_RX_CRCE | XM_MD_RX_ERR | XM_MD_CSA | XM_MD_CAA)
multiline_comment|/*&t;XM_STAT_CMD&t;16 bit r/w&t;Statistics Command Register */
multiline_comment|/* Bit 16..6:&t;reserved */
DECL|macro|XM_SC_SNP_RXC
mdefine_line|#define XM_SC_SNP_RXC&t;(1&lt;&lt;5)&t;/* Bit  5: (sc)&t;Snap Rx Counters */
DECL|macro|XM_SC_SNP_TXC
mdefine_line|#define XM_SC_SNP_TXC&t;(1&lt;&lt;4)&t;/* Bit  4: (sc)&t;Snap Tx Counters */
DECL|macro|XM_SC_CP_RXC
mdefine_line|#define XM_SC_CP_RXC&t;(1&lt;&lt;3)&t;/* Bit  3: &t;Copy Rx Counters Continuously */
DECL|macro|XM_SC_CP_TXC
mdefine_line|#define XM_SC_CP_TXC&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Copy Tx Counters Continuously */
DECL|macro|XM_SC_CLR_RXC
mdefine_line|#define XM_SC_CLR_RXC&t;(1&lt;&lt;1)&t;/* Bit  1: (sc)&t;Clear Rx Counters */
DECL|macro|XM_SC_CLR_TXC
mdefine_line|#define XM_SC_CLR_TXC&t;(1&lt;&lt;0)&t;/* Bit  0: (sc) Clear Tx Counters */
multiline_comment|/*&t;XM_RX_CNT_EV&t;32 bit r/o&t;Rx Counter Event Register */
multiline_comment|/*&t;XM_RX_EV_MSK&t;32 bit r/w&t;Rx Counter Event Mask */
DECL|macro|XMR_MAX_SZ_OV
mdefine_line|#define XMR_MAX_SZ_OV&t;(1UL&lt;&lt;31)&t;/* Bit 31:&t;1024-MaxSize Rx Cnt Ov*/
DECL|macro|XMR_1023B_OV
mdefine_line|#define XMR_1023B_OV&t;(1L&lt;&lt;30)&t;/* Bit 30:&t;512-1023Byte Rx Cnt Ov*/
DECL|macro|XMR_511B_OV
mdefine_line|#define XMR_511B_OV&t;&t;(1L&lt;&lt;29)&t;/* Bit 29:&t;256-511 Byte Rx Cnt Ov*/
DECL|macro|XMR_255B_OV
mdefine_line|#define XMR_255B_OV&t;&t;(1L&lt;&lt;28)&t;/* Bit 28:&t;128-255 Byte Rx Cnt Ov*/
DECL|macro|XMR_127B_OV
mdefine_line|#define XMR_127B_OV&t;&t;(1L&lt;&lt;27)&t;/* Bit 27:&t;65-127 Byte Rx Cnt Ov */
DECL|macro|XMR_64B_OV
mdefine_line|#define XMR_64B_OV&t;&t;(1L&lt;&lt;26)&t;/* Bit 26:&t;64 Byte Rx Cnt Ov */
DECL|macro|XMR_UTIL_OV
mdefine_line|#define XMR_UTIL_OV&t;&t;(1L&lt;&lt;25)&t;/* Bit 25:&t;Rx Util Cnt Overflow */
DECL|macro|XMR_UTIL_UR
mdefine_line|#define XMR_UTIL_UR&t;&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;Rx Util Cnt Underrun */
DECL|macro|XMR_CEX_ERR_OV
mdefine_line|#define XMR_CEX_ERR_OV&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;CEXT Err Cnt Ov */
multiline_comment|/* Bit 22:&t;reserved */
DECL|macro|XMR_FCS_ERR_OV
mdefine_line|#define XMR_FCS_ERR_OV&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;Rx FCS Error Cnt Ov */
DECL|macro|XMR_LNG_ERR_OV
mdefine_line|#define XMR_LNG_ERR_OV&t;(1L&lt;&lt;20)&t;/* Bit 20:&t;Rx too Long Err Cnt Ov*/
DECL|macro|XMR_RUNT_OV
mdefine_line|#define XMR_RUNT_OV&t;&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;Runt Event Cnt Ov */
DECL|macro|XMR_SHT_ERR_OV
mdefine_line|#define XMR_SHT_ERR_OV&t;(1L&lt;&lt;18)&t;/* Bit 18:&t;Rx Short Ev Err Cnt Ov*/
DECL|macro|XMR_SYM_ERR_OV
mdefine_line|#define XMR_SYM_ERR_OV&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;Rx Sym Err Cnt Ov */
multiline_comment|/* Bit 16:&t;reserved */
DECL|macro|XMR_CAR_ERR_OV
mdefine_line|#define XMR_CAR_ERR_OV&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Rx Carr Ev Err Cnt Ov */
DECL|macro|XMR_JAB_PKT_OV
mdefine_line|#define XMR_JAB_PKT_OV&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;Rx Jabb Packet Cnt Ov */
DECL|macro|XMR_FIFO_OV
mdefine_line|#define XMR_FIFO_OV&t;&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Rx FIFO Ov Ev Cnt Ov */
DECL|macro|XMR_FRA_ERR_OV
mdefine_line|#define XMR_FRA_ERR_OV&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Rx Framing Err Cnt Ov */
DECL|macro|XMR_FMISS_OV
mdefine_line|#define XMR_FMISS_OV&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Rx Missed Ev Cnt Ov */
DECL|macro|XMR_BURST
mdefine_line|#define XMR_BURST&t;&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Rx Burst Event Cnt Ov */
DECL|macro|XMR_INV_MOC
mdefine_line|#define XMR_INV_MOC&t;&t;(1L&lt;&lt;9)&t;&t;/* Bit  9:&t;Rx with inv. MAC OC Ov*/
DECL|macro|XMR_INV_MP
mdefine_line|#define XMR_INV_MP&t;&t;(1L&lt;&lt;8)&t;&t;/* Bit  8:&t;Rx inv Pause Frame Ov */
DECL|macro|XMR_MCTRL_OV
mdefine_line|#define XMR_MCTRL_OV&t;(1L&lt;&lt;7)&t;&t;/* Bit  7:&t;Rx MAC Ctrl-F Cnt Ov */
DECL|macro|XMR_MPAUSE_OV
mdefine_line|#define XMR_MPAUSE_OV&t;(1L&lt;&lt;6)&t;&t;/* Bit  6:&t;Rx Pause MAC Ctrl-F Ov*/
DECL|macro|XMR_UC_OK_OV
mdefine_line|#define XMR_UC_OK_OV&t;(1L&lt;&lt;5)&t;&t;/* Bit  5:&t;Rx Unicast Frame CntOv*/
DECL|macro|XMR_MC_OK_OV
mdefine_line|#define XMR_MC_OK_OV&t;(1L&lt;&lt;4)&t;&t;/* Bit  4:&t;Rx Multicast Cnt Ov */
DECL|macro|XMR_BC_OK_OV
mdefine_line|#define XMR_BC_OK_OV&t;(1L&lt;&lt;3)&t;&t;/* Bit  3:&t;Rx Broadcast Cnt Ov */
DECL|macro|XMR_OK_LO_OV
mdefine_line|#define XMR_OK_LO_OV&t;(1L&lt;&lt;2)&t;&t;/* Bit  2:&t;Octets Rx OK Low CntOv*/
DECL|macro|XMR_OK_HI_OV
mdefine_line|#define XMR_OK_HI_OV&t;(1L&lt;&lt;1)&t;&t;/* Bit  1:&t;Octets Rx OK Hi Cnt Ov*/
DECL|macro|XMR_OK_OV
mdefine_line|#define XMR_OK_OV&t;&t;(1L&lt;&lt;0)&t;&t;/* Bit  0:&t;Frames Received Ok Ov */
DECL|macro|XMR_DEF_MSK
mdefine_line|#define XMR_DEF_MSK&t;&t;(XMR_OK_LO_OV | XMR_OK_HI_OV)
multiline_comment|/*&t;XM_TX_CNT_EV&t;32 bit r/o&t;Tx Counter Event Register */
multiline_comment|/*&t;XM_TX_EV_MSK&t;32 bit r/w&t;Tx Counter Event Mask */
multiline_comment|/* Bit 31..26:&t;reserved */
DECL|macro|XMT_MAX_SZ_OV
mdefine_line|#define XMT_MAX_SZ_OV&t;(1L&lt;&lt;25)&t;/* Bit 25:&t;1024-MaxSize Tx Cnt Ov*/
DECL|macro|XMT_1023B_OV
mdefine_line|#define XMT_1023B_OV&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;512-1023Byte Tx Cnt Ov*/
DECL|macro|XMT_511B_OV
mdefine_line|#define XMT_511B_OV&t;&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;256-511 Byte Tx Cnt Ov*/
DECL|macro|XMT_255B_OV
mdefine_line|#define XMT_255B_OV&t;&t;(1L&lt;&lt;22)&t;/* Bit 22:&t;128-255 Byte Tx Cnt Ov*/
DECL|macro|XMT_127B_OV
mdefine_line|#define XMT_127B_OV&t;&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;65-127 Byte Tx Cnt Ov */
DECL|macro|XMT_64B_OV
mdefine_line|#define XMT_64B_OV&t;&t;(1L&lt;&lt;20)&t;/* Bit 20:&t;64 Byte Tx Cnt Ov */
DECL|macro|XMT_UTIL_OV
mdefine_line|#define XMT_UTIL_OV&t;&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;Tx Util Cnt Overflow */
DECL|macro|XMT_UTIL_UR
mdefine_line|#define XMT_UTIL_UR&t;&t;(1L&lt;&lt;18)&t;/* Bit 18:&t;Tx Util Cnt Underrun */
DECL|macro|XMT_CS_ERR_OV
mdefine_line|#define XMT_CS_ERR_OV&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;Tx Carr Sen Err Cnt Ov*/
DECL|macro|XMT_FIFO_UR_OV
mdefine_line|#define XMT_FIFO_UR_OV&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;Tx FIFO Ur Ev Cnt Ov */
DECL|macro|XMT_EX_DEF_OV
mdefine_line|#define XMT_EX_DEF_OV&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Tx Ex Deferall Cnt Ov */
DECL|macro|XMT_DEF
mdefine_line|#define XMT_DEF&t;&t;&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;Tx Deferred Cnt Ov */
DECL|macro|XMT_LAT_COL_OV
mdefine_line|#define XMT_LAT_COL_OV&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Tx Late Col Cnt Ov */
DECL|macro|XMT_ABO_COL_OV
mdefine_line|#define XMT_ABO_COL_OV&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Tx abo dueto Ex Col Ov*/
DECL|macro|XMT_MUL_COL_OV
mdefine_line|#define XMT_MUL_COL_OV&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Tx Mult Col Cnt Ov */
DECL|macro|XMT_SNG_COL
mdefine_line|#define XMT_SNG_COL&t;&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Tx Single Col Cnt Ov */
DECL|macro|XMT_MCTRL_OV
mdefine_line|#define XMT_MCTRL_OV&t;(1L&lt;&lt;9)&t;&t;/* Bit  9:&t;Tx MAC Ctrl Counter Ov*/
DECL|macro|XMT_MPAUSE
mdefine_line|#define XMT_MPAUSE&t;&t;(1L&lt;&lt;8)&t;&t;/* Bit  8:&t;Tx Pause MAC Ctrl-F Ov*/
DECL|macro|XMT_BURST
mdefine_line|#define XMT_BURST&t;&t;(1L&lt;&lt;7)&t;&t;/* Bit  7:&t;Tx Burst Event Cnt Ov */
DECL|macro|XMT_LONG
mdefine_line|#define XMT_LONG&t;&t;(1L&lt;&lt;6)&t;&t;/* Bit  6:&t;Tx Long Frame Cnt Ov */
DECL|macro|XMT_UC_OK_OV
mdefine_line|#define XMT_UC_OK_OV&t;(1L&lt;&lt;5)&t;&t;/* Bit  5:&t;Tx Unicast Cnt Ov */
DECL|macro|XMT_MC_OK_OV
mdefine_line|#define XMT_MC_OK_OV&t;(1L&lt;&lt;4)&t;&t;/* Bit  4:&t;Tx Multicast Cnt Ov */
DECL|macro|XMT_BC_OK_OV
mdefine_line|#define XMT_BC_OK_OV&t;(1L&lt;&lt;3)&t;&t;/* Bit  3:&t;Tx Broadcast Cnt Ov */
DECL|macro|XMT_OK_LO_OV
mdefine_line|#define XMT_OK_LO_OV&t;(1L&lt;&lt;2)&t;&t;/* Bit  2:&t;Octets Tx OK Low CntOv*/
DECL|macro|XMT_OK_HI_OV
mdefine_line|#define XMT_OK_HI_OV&t;(1L&lt;&lt;1)&t;&t;/* Bit  1:&t;Octets Tx OK Hi Cnt Ov*/
DECL|macro|XMT_OK_OV
mdefine_line|#define XMT_OK_OV&t;&t;(1L&lt;&lt;0)&t;&t;/* Bit  0:&t;Frames Tx Ok Ov */
DECL|macro|XMT_DEF_MSK
mdefine_line|#define XMT_DEF_MSK&t;&t;(XMT_OK_LO_OV | XMT_OK_HI_OV)
multiline_comment|/*&n; * Receive Frame Status Encoding&n; */
DECL|macro|XMR_FS_LEN
mdefine_line|#define XMR_FS_LEN&t;(0x3fffUL&lt;&lt;18)&t;/* Bit 31..18:&t;Rx Frame Length */
DECL|macro|XMR_FS_2L_VLAN
mdefine_line|#define XMR_FS_2L_VLAN&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;tagged wh 2Lev VLAN ID*/
DECL|macro|XMR_FS_1L_VLAN
mdefine_line|#define XMR_FS_1L_VLAN&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;tagged wh 1Lev VLAN ID*/
DECL|macro|XMR_FS_BC
mdefine_line|#define XMR_FS_BC&t;&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Broadcast Frame */
DECL|macro|XMR_FS_MC
mdefine_line|#define XMR_FS_MC&t;&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;Multicast Frame */
DECL|macro|XMR_FS_UC
mdefine_line|#define XMR_FS_UC&t;&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Unicast Frame */
multiline_comment|/* Bit 12:&t;reserved */
DECL|macro|XMR_FS_BURST
mdefine_line|#define XMR_FS_BURST&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Burst Mode */
DECL|macro|XMR_FS_CEX_ERR
mdefine_line|#define XMR_FS_CEX_ERR&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Carrier Ext. Error */
DECL|macro|XMR_FS_802_3
mdefine_line|#define XMR_FS_802_3&t;(1L&lt;&lt;9)&t;&t;/* Bit  9:&t;802.3 Frame */
DECL|macro|XMR_FS_COL_ERR
mdefine_line|#define XMR_FS_COL_ERR&t;(1L&lt;&lt;8)&t;&t;/* Bit  8:&t;Collision Error */
DECL|macro|XMR_FS_CAR_ERR
mdefine_line|#define XMR_FS_CAR_ERR&t;(1L&lt;&lt;7)&t;&t;/* Bit  7:&t;Carrier Event Error */
DECL|macro|XMR_FS_LEN_ERR
mdefine_line|#define XMR_FS_LEN_ERR&t;(1L&lt;&lt;6)&t;&t;/* Bit  6:&t;In-Range Length Error */
DECL|macro|XMR_FS_FRA_ERR
mdefine_line|#define XMR_FS_FRA_ERR&t;(1L&lt;&lt;5)&t;&t;/* Bit  5:&t;Framing Error */
DECL|macro|XMR_FS_RUNT
mdefine_line|#define XMR_FS_RUNT&t;&t;(1L&lt;&lt;4)&t;&t;/* Bit  4:&t;Runt Frame */
DECL|macro|XMR_FS_LNG_ERR
mdefine_line|#define XMR_FS_LNG_ERR&t;(1L&lt;&lt;3)&t;&t;/* Bit  3:&t;Giant (Jumbo) Frame */
DECL|macro|XMR_FS_FCS_ERR
mdefine_line|#define XMR_FS_FCS_ERR&t;(1L&lt;&lt;2)&t;&t;/* Bit  2:&t;Frame Check Sequ Err */
DECL|macro|XMR_FS_ERR
mdefine_line|#define XMR_FS_ERR&t;&t;(1L&lt;&lt;1)&t;&t;/* Bit  1:&t;Frame Error */
DECL|macro|XMR_FS_MCTRL
mdefine_line|#define XMR_FS_MCTRL&t;(1L&lt;&lt;0)&t;&t;/* Bit  0:&t;MAC Control Packet */
multiline_comment|/*&n; * XMR_FS_ERR will be set if&n; *&t;XMR_FS_FCS_ERR, XMR_FS_LNG_ERR, XMR_FS_RUNT,&n; *&t;XMR_FS_FRA_ERR, XMR_FS_LEN_ERR, or XMR_FS_CEX_ERR&n; * is set. XMR_FS_LNG_ERR and XMR_FS_LEN_ERR will issue&n; * XMR_FS_ERR unless the corresponding bit in the Receive Command&n; * Register is set.&n; */
DECL|macro|XMR_FS_ANY_ERR
mdefine_line|#define XMR_FS_ANY_ERR&t;XMR_FS_ERR
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * XMAC-PHY Registers, indirect addressed over the XMAC&n; */
DECL|macro|PHY_XMAC_CTRL
mdefine_line|#define PHY_XMAC_CTRL&t;&t;0x00&t;/* 16 bit r/w&t;PHY Control Register */
DECL|macro|PHY_XMAC_STAT
mdefine_line|#define PHY_XMAC_STAT&t;&t;0x01&t;/* 16 bit r/w&t;PHY Status Register */
DECL|macro|PHY_XMAC_ID0
mdefine_line|#define PHY_XMAC_ID0&t;&t;0x02&t;/* 16 bit r/o&t;PHY ID0 Register */
DECL|macro|PHY_XMAC_ID1
mdefine_line|#define PHY_XMAC_ID1&t;&t;0x03&t;/* 16 bit r/o&t;PHY ID1 Register */
DECL|macro|PHY_XMAC_AUNE_ADV
mdefine_line|#define PHY_XMAC_AUNE_ADV&t;0x04&t;/* 16 bit r/w&t;Auto-Neg. Advertisement */
DECL|macro|PHY_XMAC_AUNE_LP
mdefine_line|#define PHY_XMAC_AUNE_LP&t;0x05&t;/* 16 bit r/o&t;Link Partner Abi Reg */
DECL|macro|PHY_XMAC_AUNE_EXP
mdefine_line|#define PHY_XMAC_AUNE_EXP&t;0x06&t;/* 16 bit r/o&t;Auto-Neg. Expansion Reg */
DECL|macro|PHY_XMAC_NEPG
mdefine_line|#define PHY_XMAC_NEPG&t;&t;0x07&t;/* 16 bit r/w&t;Next Page Register */
DECL|macro|PHY_XMAC_NEPG_LP
mdefine_line|#define PHY_XMAC_NEPG_LP&t;0x08&t;/* 16 bit r/o&t;Next Page Link P Reg */
multiline_comment|/* 0x09 - 0x0e:&t;&t;reserved */
DECL|macro|PHY_XMAC_EXT_STAT
mdefine_line|#define PHY_XMAC_EXT_STAT&t;0x0f&t;/* 16 bit r/o&t;Ext Status Register */
DECL|macro|PHY_XMAC_RES_ABI
mdefine_line|#define PHY_XMAC_RES_ABI&t;0x10&t;/* 16 bit r/o&t;PHY Resolved Ability */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * Broadcom-PHY Registers, indirect addressed over XMAC&n; */
DECL|macro|PHY_BCOM_CTRL
mdefine_line|#define PHY_BCOM_CTRL&t;&t;0x00&t;/* 16 bit r/w&t;PHY Control Register */
DECL|macro|PHY_BCOM_STAT
mdefine_line|#define PHY_BCOM_STAT&t;&t;0x01&t;/* 16 bit r/o&t;PHY Status Register */
DECL|macro|PHY_BCOM_ID0
mdefine_line|#define PHY_BCOM_ID0&t;&t;0x02&t;/* 16 bit r/o&t;PHY ID0 Register */
DECL|macro|PHY_BCOM_ID1
mdefine_line|#define PHY_BCOM_ID1&t;&t;0x03&t;/* 16 bit r/o&t;PHY ID1 Register */
DECL|macro|PHY_BCOM_AUNE_ADV
mdefine_line|#define PHY_BCOM_AUNE_ADV&t;0x04&t;/* 16 bit r/w&t;Auto-Neg. Advertisement */
DECL|macro|PHY_BCOM_AUNE_LP
mdefine_line|#define PHY_BCOM_AUNE_LP&t;0x05&t;/* 16 bit r/o&t;Link Part Ability Reg */
DECL|macro|PHY_BCOM_AUNE_EXP
mdefine_line|#define PHY_BCOM_AUNE_EXP&t;0x06&t;/* 16 bit r/o&t;Auto-Neg. Expansion Reg */
DECL|macro|PHY_BCOM_NEPG
mdefine_line|#define PHY_BCOM_NEPG&t;&t;0x07&t;/* 16 bit r/w&t;Next Page Register */
DECL|macro|PHY_BCOM_NEPG_LP
mdefine_line|#define PHY_BCOM_NEPG_LP&t;0x08&t;/* 16 bit r/o&t;Next Page Link P Reg */
multiline_comment|/* Broadcom-specific registers */
DECL|macro|PHY_BCOM_1000T_CTRL
mdefine_line|#define PHY_BCOM_1000T_CTRL&t;0x09&t;/* 16 bit r/w&t;1000Base-T Ctrl Reg */
DECL|macro|PHY_BCOM_1000T_STAT
mdefine_line|#define PHY_BCOM_1000T_STAT&t;0x0a&t;/* 16 bit r/o&t;1000Base-T Status Reg */
multiline_comment|/* 0x0b - 0x0e:&t;&t;reserved */
DECL|macro|PHY_BCOM_EXT_STAT
mdefine_line|#define PHY_BCOM_EXT_STAT&t;0x0f&t;/* 16 bit r/o&t;Extended Status Reg */
DECL|macro|PHY_BCOM_P_EXT_CTRL
mdefine_line|#define PHY_BCOM_P_EXT_CTRL&t;0x10&t;/* 16 bit r/w&t;PHY Extended Ctrl Reg */
DECL|macro|PHY_BCOM_P_EXT_STAT
mdefine_line|#define PHY_BCOM_P_EXT_STAT&t;0x11&t;/* 16 bit r/o&t;PHY Extended Stat Reg */
DECL|macro|PHY_BCOM_RE_CTR
mdefine_line|#define PHY_BCOM_RE_CTR&t;&t;0x12&t;/* 16 bit r/w&t;Receive Error Counter */
DECL|macro|PHY_BCOM_FC_CTR
mdefine_line|#define PHY_BCOM_FC_CTR&t;&t;0x13&t;/* 16 bit r/w&t;False Carr Sense Cnt */
DECL|macro|PHY_BCOM_RNO_CTR
mdefine_line|#define PHY_BCOM_RNO_CTR&t;0x14&t;/* 16 bit r/w&t;Receiver NOT_OK Cnt */
multiline_comment|/* 0x15 - 0x17:&t;&t;reserved */
DECL|macro|PHY_BCOM_AUX_CTRL
mdefine_line|#define PHY_BCOM_AUX_CTRL&t;0x18&t;/* 16 bit r/w&t;Auxiliary Control Reg */
DECL|macro|PHY_BCOM_AUX_STAT
mdefine_line|#define PHY_BCOM_AUX_STAT&t;0x19&t;/* 16 bit r/o&t;Auxiliary Stat Summary */
DECL|macro|PHY_BCOM_INT_STAT
mdefine_line|#define PHY_BCOM_INT_STAT&t;0x1a&t;/* 16 bit r/o&t;Interrupt Status Reg */
DECL|macro|PHY_BCOM_INT_MASK
mdefine_line|#define PHY_BCOM_INT_MASK&t;0x1b&t;/* 16 bit r/w&t;Interrupt Mask Reg */
multiline_comment|/* 0x1c:&t;&t;reserved */
multiline_comment|/* 0x1d - 0x1f:&t;&t;test registers */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * Marvel-PHY Registers, indirect addressed over GMAC&n; */
DECL|macro|PHY_MARV_CTRL
mdefine_line|#define PHY_MARV_CTRL&t;&t;0x00&t;/* 16 bit r/w&t;PHY Control Register */
DECL|macro|PHY_MARV_STAT
mdefine_line|#define PHY_MARV_STAT&t;&t;0x01&t;/* 16 bit r/o&t;PHY Status Register */
DECL|macro|PHY_MARV_ID0
mdefine_line|#define PHY_MARV_ID0&t;&t;0x02&t;/* 16 bit r/o&t;PHY ID0 Register */
DECL|macro|PHY_MARV_ID1
mdefine_line|#define PHY_MARV_ID1&t;&t;0x03&t;/* 16 bit r/o&t;PHY ID1 Register */
DECL|macro|PHY_MARV_AUNE_ADV
mdefine_line|#define PHY_MARV_AUNE_ADV&t;0x04&t;/* 16 bit r/w&t;Auto-Neg. Advertisement */
DECL|macro|PHY_MARV_AUNE_LP
mdefine_line|#define PHY_MARV_AUNE_LP&t;0x05&t;/* 16 bit r/o&t;Link Part Ability Reg */
DECL|macro|PHY_MARV_AUNE_EXP
mdefine_line|#define PHY_MARV_AUNE_EXP&t;0x06&t;/* 16 bit r/o&t;Auto-Neg. Expansion Reg */
DECL|macro|PHY_MARV_NEPG
mdefine_line|#define PHY_MARV_NEPG&t;&t;0x07&t;/* 16 bit r/w&t;Next Page Register */
DECL|macro|PHY_MARV_NEPG_LP
mdefine_line|#define PHY_MARV_NEPG_LP&t;0x08&t;/* 16 bit r/o&t;Next Page Link P Reg */
multiline_comment|/* Marvel-specific registers */
DECL|macro|PHY_MARV_1000T_CTRL
mdefine_line|#define PHY_MARV_1000T_CTRL&t;0x09&t;/* 16 bit r/w&t;1000Base-T Ctrl Reg */
DECL|macro|PHY_MARV_1000T_STAT
mdefine_line|#define PHY_MARV_1000T_STAT&t;0x0a&t;/* 16 bit r/o&t;1000Base-T Status Reg */
multiline_comment|/* 0x0b - 0x0e:&t;&t;reserved */
DECL|macro|PHY_MARV_EXT_STAT
mdefine_line|#define PHY_MARV_EXT_STAT&t;0x0f&t;/* 16 bit r/o&t;Extended Status Reg */
DECL|macro|PHY_MARV_PHY_CTRL
mdefine_line|#define PHY_MARV_PHY_CTRL&t;0x10&t;/* 16 bit r/w&t;PHY Specific Ctrl Reg */
DECL|macro|PHY_MARV_PHY_STAT
mdefine_line|#define PHY_MARV_PHY_STAT&t;0x11&t;/* 16 bit r/o&t;PHY Specific Stat Reg */
DECL|macro|PHY_MARV_INT_MASK
mdefine_line|#define PHY_MARV_INT_MASK&t;0x12&t;/* 16 bit r/w&t;Interrupt Mask Reg */
DECL|macro|PHY_MARV_INT_STAT
mdefine_line|#define PHY_MARV_INT_STAT&t;0x13&t;/* 16 bit r/o&t;Interrupt Status Reg */
DECL|macro|PHY_MARV_EXT_CTRL
mdefine_line|#define PHY_MARV_EXT_CTRL&t;0x14&t;/* 16 bit r/w&t;Ext. PHY Specific Ctrl */
DECL|macro|PHY_MARV_RXE_CNT
mdefine_line|#define PHY_MARV_RXE_CNT&t;0x15&t;/* 16 bit r/w&t;Receive Error Counter */
DECL|macro|PHY_MARV_EXT_ADR
mdefine_line|#define PHY_MARV_EXT_ADR&t;0x16&t;/* 16 bit r/w&t;Ext. Ad. for Cable Diag. */
multiline_comment|/* 0x17:&t;&t;reserved */
DECL|macro|PHY_MARV_LED_CTRL
mdefine_line|#define PHY_MARV_LED_CTRL&t;0x18&t;/* 16 bit r/w&t;LED Control Reg */
DECL|macro|PHY_MARV_LED_OVER
mdefine_line|#define PHY_MARV_LED_OVER&t;0x19&t;/* 16 bit r/w&t;Manual LED Override Reg */
DECL|macro|PHY_MARV_EXT_CTRL_2
mdefine_line|#define PHY_MARV_EXT_CTRL_2&t;0x1a&t;/* 16 bit r/w&t;Ext. PHY Specific Ctrl 2 */
DECL|macro|PHY_MARV_EXT_P_STAT
mdefine_line|#define PHY_MARV_EXT_P_STAT&t;0x1b&t;/* 16 bit r/w&t;Ext. PHY Spec. Stat Reg */
DECL|macro|PHY_MARV_CABLE_DIAG
mdefine_line|#define PHY_MARV_CABLE_DIAG&t;0x1c&t;/* 16 bit r/o&t;Cable Diagnostic Reg */
multiline_comment|/* 0x1d - 0x1f:&t;&t;reserved */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * Level One-PHY Registers, indirect addressed over XMAC&n; */
DECL|macro|PHY_LONE_CTRL
mdefine_line|#define PHY_LONE_CTRL&t;&t;0x00&t;/* 16 bit r/w&t;PHY Control Register */
DECL|macro|PHY_LONE_STAT
mdefine_line|#define PHY_LONE_STAT&t;&t;0x01&t;/* 16 bit r/o&t;PHY Status Register */
DECL|macro|PHY_LONE_ID0
mdefine_line|#define PHY_LONE_ID0&t;&t;0x02&t;/* 16 bit r/o&t;PHY ID0 Register */
DECL|macro|PHY_LONE_ID1
mdefine_line|#define PHY_LONE_ID1&t;&t;0x03&t;/* 16 bit r/o&t;PHY ID1 Register */
DECL|macro|PHY_LONE_AUNE_ADV
mdefine_line|#define PHY_LONE_AUNE_ADV&t;0x04&t;/* 16 bit r/w&t;Auto-Neg. Advertisement */
DECL|macro|PHY_LONE_AUNE_LP
mdefine_line|#define PHY_LONE_AUNE_LP&t;0x05&t;/* 16 bit r/o&t;Link Part Ability Reg */
DECL|macro|PHY_LONE_AUNE_EXP
mdefine_line|#define PHY_LONE_AUNE_EXP&t;0x06&t;/* 16 bit r/o&t;Auto-Neg. Expansion Reg */
DECL|macro|PHY_LONE_NEPG
mdefine_line|#define PHY_LONE_NEPG&t;&t;0x07&t;/* 16 bit r/w&t;Next Page Register */
DECL|macro|PHY_LONE_NEPG_LP
mdefine_line|#define PHY_LONE_NEPG_LP&t;0x08&t;/* 16 bit r/o&t;Next Page Link Partner*/
multiline_comment|/* Level One-specific registers */
DECL|macro|PHY_LONE_1000T_CTRL
mdefine_line|#define PHY_LONE_1000T_CTRL&t;0x09&t;/* 16 bit r/w&t;1000Base-T Control Reg*/
DECL|macro|PHY_LONE_1000T_STAT
mdefine_line|#define PHY_LONE_1000T_STAT&t;0x0a&t;/* 16 bit r/o&t;1000Base-T Status Reg */
multiline_comment|/* 0x0b -0x0e:&t;&t;reserved */
DECL|macro|PHY_LONE_EXT_STAT
mdefine_line|#define PHY_LONE_EXT_STAT&t;0x0f&t;/* 16 bit r/o&t;Extended Status Reg */
DECL|macro|PHY_LONE_PORT_CFG
mdefine_line|#define PHY_LONE_PORT_CFG&t;0x10&t;/* 16 bit r/w&t;Port Configuration Reg*/
DECL|macro|PHY_LONE_Q_STAT
mdefine_line|#define PHY_LONE_Q_STAT&t;&t;0x11&t;/* 16 bit r/o&t;Quick Status Reg */
DECL|macro|PHY_LONE_INT_ENAB
mdefine_line|#define PHY_LONE_INT_ENAB&t;0x12&t;/* 16 bit r/w&t;Interrupt Enable Reg */
DECL|macro|PHY_LONE_INT_STAT
mdefine_line|#define PHY_LONE_INT_STAT&t;0x13&t;/* 16 bit r/o&t;Interrupt Status Reg */
DECL|macro|PHY_LONE_LED_CFG
mdefine_line|#define PHY_LONE_LED_CFG&t;0x14&t;/* 16 bit r/w&t;LED Configuration Reg */
DECL|macro|PHY_LONE_PORT_CTRL
mdefine_line|#define PHY_LONE_PORT_CTRL&t;0x15&t;/* 16 bit r/w&t;Port Control Reg */
DECL|macro|PHY_LONE_CIM
mdefine_line|#define PHY_LONE_CIM&t;&t;0x16&t;/* 16 bit r/o&t;CIM Reg */
multiline_comment|/* 0x17 -0x1c:&t;&t;reserved */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * National-PHY Registers, indirect addressed over XMAC&n; */
DECL|macro|PHY_NAT_CTRL
mdefine_line|#define PHY_NAT_CTRL&t;&t;0x00&t;/* 16 bit r/w&t;PHY Control Register */
DECL|macro|PHY_NAT_STAT
mdefine_line|#define PHY_NAT_STAT&t;&t;0x01&t;/* 16 bit r/w&t;PHY Status Register */
DECL|macro|PHY_NAT_ID0
mdefine_line|#define PHY_NAT_ID0&t;&t;&t;0x02&t;/* 16 bit r/o&t;PHY ID0 Register */
DECL|macro|PHY_NAT_ID1
mdefine_line|#define PHY_NAT_ID1&t;&t;&t;0x03&t;/* 16 bit r/o&t;PHY ID1 Register */
DECL|macro|PHY_NAT_AUNE_ADV
mdefine_line|#define PHY_NAT_AUNE_ADV&t;0x04&t;/* 16 bit r/w&t;Auto-Neg. Advertisement */
DECL|macro|PHY_NAT_AUNE_LP
mdefine_line|#define PHY_NAT_AUNE_LP&t;&t;0x05&t;/* 16 bit r/o&t;Link Partner Ability Reg */
DECL|macro|PHY_NAT_AUNE_EXP
mdefine_line|#define PHY_NAT_AUNE_EXP&t;0x06&t;/* 16 bit r/o&t;Auto-Neg. Expansion Reg */
DECL|macro|PHY_NAT_NEPG
mdefine_line|#define PHY_NAT_NEPG&t;&t;0x07&t;/* 16 bit r/w&t;Next Page Register */
DECL|macro|PHY_NAT_NEPG_LP
mdefine_line|#define PHY_NAT_NEPG_LP&t;&t;0x08&t;/* 16 bit r/o&t;Next Page Link Partner Reg */
multiline_comment|/* National-specific registers */
DECL|macro|PHY_NAT_1000T_CTRL
mdefine_line|#define PHY_NAT_1000T_CTRL&t;0x09&t;/* 16 bit r/w&t;1000Base-T Control Reg */
DECL|macro|PHY_NAT_1000T_STAT
mdefine_line|#define PHY_NAT_1000T_STAT&t;0x0a&t;/* 16 bit r/o&t;1000Base-T Status Reg */
multiline_comment|/* 0x0b -0x0e:&t;&t;reserved */
DECL|macro|PHY_NAT_EXT_STAT
mdefine_line|#define PHY_NAT_EXT_STAT&t;0x0f&t;/* 16 bit r/o&t;Extended Status Register */
DECL|macro|PHY_NAT_EXT_CTRL1
mdefine_line|#define PHY_NAT_EXT_CTRL1&t;0x10&t;/* 16 bit r/o&t;Extended Control Reg1 */
DECL|macro|PHY_NAT_Q_STAT1
mdefine_line|#define PHY_NAT_Q_STAT1&t;&t;0x11&t;/* 16 bit r/o&t;Quick Status Reg1 */
DECL|macro|PHY_NAT_10B_OP
mdefine_line|#define PHY_NAT_10B_OP&t;&t;0x12&t;/* 16 bit r/o&t;10Base-T Operations Reg */
DECL|macro|PHY_NAT_EXT_CTRL2
mdefine_line|#define PHY_NAT_EXT_CTRL2&t;0x13&t;/* 16 bit r/o&t;Extended Control Reg1 */
DECL|macro|PHY_NAT_Q_STAT2
mdefine_line|#define PHY_NAT_Q_STAT2&t;&t;0x14&t;/* 16 bit r/o&t;Quick Status Reg2 */
multiline_comment|/* 0x15 -0x18:&t;&t;reserved */
DECL|macro|PHY_NAT_PHY_ADDR
mdefine_line|#define PHY_NAT_PHY_ADDR&t;0x19&t;/* 16 bit r/o&t;PHY Address Register */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * PHY bit definitions&n; * Bits defined as PHY_X_..., PHY_B_..., PHY_L_... or PHY_N_... are&n; * Xmac/Broadcom/LevelOne/National-specific.&n; * All other are general.&n; */
multiline_comment|/*****  PHY_XMAC_CTRL&t;16 bit r/w&t;PHY Control Register *****/
multiline_comment|/*****  PHY_BCOM_CTRL&t;16 bit r/w&t;PHY Control Register *****/
multiline_comment|/*****  PHY_LONE_CTRL&t;16 bit r/w&t;PHY Control Register *****/
DECL|macro|PHY_CT_RESET
mdefine_line|#define PHY_CT_RESET&t;(1&lt;&lt;15)&t;/* Bit 15: (sc)&t;clear all PHY related regs */
DECL|macro|PHY_CT_LOOP
mdefine_line|#define PHY_CT_LOOP&t;&t;(1&lt;&lt;14)&t;/* Bit 14:&t;enable Loopback over PHY */
DECL|macro|PHY_CT_SPS_LSB
mdefine_line|#define PHY_CT_SPS_LSB&t;(1&lt;&lt;13) /* Bit 13: (BC,L1) Speed select, lower bit */
DECL|macro|PHY_CT_ANE
mdefine_line|#define PHY_CT_ANE&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Auto-Negotiation Enabled */
DECL|macro|PHY_CT_PDOWN
mdefine_line|#define PHY_CT_PDOWN&t;(1&lt;&lt;11)&t;/* Bit 11: (BC,L1) Power Down Mode */
DECL|macro|PHY_CT_ISOL
mdefine_line|#define PHY_CT_ISOL&t;&t;(1&lt;&lt;10)&t;/* Bit 10: (BC,L1) Isolate Mode */
DECL|macro|PHY_CT_RE_CFG
mdefine_line|#define PHY_CT_RE_CFG&t;(1&lt;&lt;9)&t;/* Bit  9: (sc) Restart Auto-Negotiation */
DECL|macro|PHY_CT_DUP_MD
mdefine_line|#define PHY_CT_DUP_MD&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Duplex Mode */
DECL|macro|PHY_CT_COL_TST
mdefine_line|#define PHY_CT_COL_TST&t;(1&lt;&lt;7)&t;/* Bit  7: (BC,L1) Collision Test enabled */
DECL|macro|PHY_CT_SPS_MSB
mdefine_line|#define PHY_CT_SPS_MSB&t;(1&lt;&lt;6)&t;/* Bit  6: (BC,L1) Speed select, upper bit */
multiline_comment|/* Bit  5..0:&t;reserved */
DECL|macro|PHY_CT_SP1000
mdefine_line|#define PHY_CT_SP1000&t;PHY_CT_SPS_MSB&t;/* enable speed of 1000 Mbps */
DECL|macro|PHY_CT_SP100
mdefine_line|#define PHY_CT_SP100&t;PHY_CT_SPS_LSB&t;/* enable speed of  100 Mbps */
DECL|macro|PHY_CT_SP10
mdefine_line|#define PHY_CT_SP10&t;&t;(0)&t;&t;&t;&t;/* enable speed of   10 Mbps */
multiline_comment|/*****  PHY_XMAC_STAT&t;16 bit r/w&t;PHY Status Register *****/
multiline_comment|/*****  PHY_BCOM_STAT&t;16 bit r/w&t;PHY Status Register *****/
multiline_comment|/*****  PHY_MARV_STAT&t;16 bit r/w&t;PHY Status Register *****/
multiline_comment|/*****  PHY_LONE_STAT&t;16 bit r/w&t;PHY Status Register *****/
multiline_comment|/* Bit 15..9:&t;reserved */
multiline_comment|/*&t;(BC/L1) 100/10 Mbps cap bits ignored*/
DECL|macro|PHY_ST_EXT_ST
mdefine_line|#define PHY_ST_EXT_ST&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Extended Status Present */
multiline_comment|/* Bit  7:&t;reserved */
DECL|macro|PHY_ST_PRE_SUP
mdefine_line|#define PHY_ST_PRE_SUP&t;(1&lt;&lt;6)&t;/* Bit  6: (BC/L1) preamble suppression */
DECL|macro|PHY_ST_AN_OVER
mdefine_line|#define PHY_ST_AN_OVER&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Auto-Negotiation Over */
DECL|macro|PHY_ST_REM_FLT
mdefine_line|#define PHY_ST_REM_FLT&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Remote Fault Condition Occured */
DECL|macro|PHY_ST_AN_CAP
mdefine_line|#define PHY_ST_AN_CAP&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Auto-Negotiation Capability */
DECL|macro|PHY_ST_LSYNC
mdefine_line|#define PHY_ST_LSYNC&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Link Synchronized */
DECL|macro|PHY_ST_JAB_DET
mdefine_line|#define PHY_ST_JAB_DET&t;(1&lt;&lt;1)&t;/* Bit  1: (BC/L1) Jabber Detected */
DECL|macro|PHY_ST_EXT_REG
mdefine_line|#define PHY_ST_EXT_REG&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Extended Register available */
multiline_comment|/*****&t;PHY_XMAC_ID1&t;&t;16 bit r/o&t;PHY ID1 Register */
multiline_comment|/*****&t;PHY_BCOM_ID1&t;&t;16 bit r/o&t;PHY ID1 Register */
multiline_comment|/*****&t;PHY_MARV_ID1&t;&t;16 bit r/o&t;PHY ID1 Register */
multiline_comment|/*****&t;PHY_LONE_ID1&t;&t;16 bit r/o&t;PHY ID1 Register */
DECL|macro|PHY_I1_OUI_MSK
mdefine_line|#define PHY_I1_OUI_MSK&t;(0x3f&lt;&lt;10)&t;/* Bit 15..10:&t;Organization Unique ID */
DECL|macro|PHY_I1_MOD_NUM
mdefine_line|#define PHY_I1_MOD_NUM&t;(0x3f&lt;&lt;4)&t;/* Bit  9.. 4:&t;Model Number */
DECL|macro|PHY_I1_REV_MSK
mdefine_line|#define PHY_I1_REV_MSK&t;0x0f&t;&t;/* Bit  3.. 0:&t;Revision Number */
multiline_comment|/* different Broadcom PHY Ids */
DECL|macro|PHY_BCOM_ID1_A1
mdefine_line|#define PHY_BCOM_ID1_A1&t;&t;0x6041
DECL|macro|PHY_BCOM_ID1_B2
mdefine_line|#define PHY_BCOM_ID1_B2&t;&t;0x6043
DECL|macro|PHY_BCOM_ID1_C0
mdefine_line|#define PHY_BCOM_ID1_C0&t;&t;0x6044
DECL|macro|PHY_BCOM_ID1_C5
mdefine_line|#define PHY_BCOM_ID1_C5&t;&t;0x6047
multiline_comment|/*****  PHY_XMAC_AUNE_ADV&t;16 bit r/w&t;Auto-Negotiation Advertisement *****/
multiline_comment|/*****  PHY_XMAC_AUNE_LP&t;16 bit r/o&t;Link Partner Ability Reg *****/
DECL|macro|PHY_AN_NXT_PG
mdefine_line|#define PHY_AN_NXT_PG&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Request Next Page */
DECL|macro|PHY_X_AN_ACK
mdefine_line|#define PHY_X_AN_ACK&t;(1&lt;&lt;14)&t;/* Bit 14: (ro)&t;Acknowledge Received */
DECL|macro|PHY_X_AN_RFB
mdefine_line|#define PHY_X_AN_RFB&t;(3&lt;&lt;12)&t;/* Bit 13..12:&t;Remote Fault Bits */
multiline_comment|/* Bit 11.. 9:&t;reserved */
DECL|macro|PHY_X_AN_PAUSE
mdefine_line|#define PHY_X_AN_PAUSE&t;(3&lt;&lt;7)&t;/* Bit  8.. 7:&t;Pause Bits */
DECL|macro|PHY_X_AN_HD
mdefine_line|#define PHY_X_AN_HD&t;&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Half Duplex */
DECL|macro|PHY_X_AN_FD
mdefine_line|#define PHY_X_AN_FD&t;&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Full Duplex */
multiline_comment|/* Bit  4.. 0:&t;reserved */
multiline_comment|/*****  PHY_BCOM_AUNE_ADV&t;16 bit r/w&t;Auto-Negotiation Advertisement *****/
multiline_comment|/*****  PHY_BCOM_AUNE_LP&t;16 bit r/o&t;Link Partner Ability Reg *****/
multiline_comment|/*&t;PHY_AN_NXT_PG&t;&t;(see XMAC) Bit 15:&t;Request Next Page */
multiline_comment|/* Bit 14:&t;reserved */
DECL|macro|PHY_B_AN_RF
mdefine_line|#define PHY_B_AN_RF&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Remote Fault */
multiline_comment|/* Bit 12:&t;reserved */
DECL|macro|PHY_B_AN_ASP
mdefine_line|#define PHY_B_AN_ASP&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Asymmetric Pause */
DECL|macro|PHY_B_AN_PC
mdefine_line|#define PHY_B_AN_PC&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Pause Capable */
multiline_comment|/* Bit  9..5:&t;100/10 BT cap bits ingnored */
DECL|macro|PHY_B_AN_SEL
mdefine_line|#define PHY_B_AN_SEL&t;0x1f&t;/* Bit 4..0:&t;Selector Field, 00001=Ethernet*/
multiline_comment|/*****  PHY_LONE_AUNE_ADV&t;16 bit r/w&t;Auto-Negotiation Advertisement *****/
multiline_comment|/*****  PHY_LONE_AUNE_LP&t;16 bit r/o&t;Link Partner Ability Reg *****/
multiline_comment|/*&t;PHY_AN_NXT_PG&t;&t;(see XMAC) Bit 15:&t;Request Next Page */
multiline_comment|/* Bit 14:&t;reserved */
DECL|macro|PHY_L_AN_RF
mdefine_line|#define PHY_L_AN_RF&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Remote Fault */
multiline_comment|/* Bit 12:&t;reserved */
DECL|macro|PHY_L_AN_ASP
mdefine_line|#define PHY_L_AN_ASP&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Asymmetric Pause */
DECL|macro|PHY_L_AN_PC
mdefine_line|#define PHY_L_AN_PC&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Pause Capable */
multiline_comment|/* Bit  9..5:&t;100/10 BT cap bits ingnored */
DECL|macro|PHY_L_AN_SEL
mdefine_line|#define PHY_L_AN_SEL&t;0x1f&t;/* Bit 4..0:&t;Selector Field, 00001=Ethernet*/
multiline_comment|/*****  PHY_NAT_AUNE_ADV&t;16 bit r/w&t;Auto-Negotiation Advertisement *****/
multiline_comment|/*****  PHY_NAT_AUNE_LP&t;&t;16 bit r/o&t;Link Partner Ability Reg *****/
multiline_comment|/*&t;PHY_AN_NXT_PG&t;&t;(see XMAC) Bit 15:&t;Request Next Page */
multiline_comment|/* Bit 14:&t;reserved */
DECL|macro|PHY_N_AN_RF
mdefine_line|#define PHY_N_AN_RF&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Remote Fault */
multiline_comment|/* Bit 12:&t;reserved */
DECL|macro|PHY_N_AN_100F
mdefine_line|#define PHY_N_AN_100F&t;(1&lt;&lt;11)&t;/* Bit 11:&t;100Base-T2 FD Support */
DECL|macro|PHY_N_AN_100H
mdefine_line|#define PHY_N_AN_100H&t;(1&lt;&lt;10)&t;/* Bit 10:&t;100Base-T2 HD Support */
multiline_comment|/* Bit  9..5:&t;100/10 BT cap bits ingnored */
DECL|macro|PHY_N_AN_SEL
mdefine_line|#define PHY_N_AN_SEL&t;0x1f&t;/* Bit 4..0:&t;Selector Field, 00001=Ethernet*/
multiline_comment|/* field type definition for PHY_x_AN_SEL */
DECL|macro|PHY_SEL_TYPE
mdefine_line|#define PHY_SEL_TYPE&t;0x01&t;/* 00001 = Ethernet */
multiline_comment|/*****  PHY_XMAC_AUNE_EXP&t;16 bit r/o&t;Auto-Negotiation Expansion Reg *****/
multiline_comment|/* Bit 15..4:&t;reserved */
DECL|macro|PHY_AN_LP_NP
mdefine_line|#define PHY_AN_LP_NP&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Link Partner can Next Page */
DECL|macro|PHY_AN_LOC_NP
mdefine_line|#define PHY_AN_LOC_NP&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Local PHY can Next Page */
DECL|macro|PHY_AN_RX_PG
mdefine_line|#define PHY_AN_RX_PG&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Page Received */
multiline_comment|/* Bit  0:&t;reserved */
multiline_comment|/*****  PHY_BCOM_AUNE_EXP&t;16 bit r/o&t;Auto-Negotiation Expansion Reg *****/
multiline_comment|/* Bit 15..5:&t;reserved */
DECL|macro|PHY_B_AN_PDF
mdefine_line|#define PHY_B_AN_PDF&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Parallel Detection Fault */
multiline_comment|/*&t;PHY_AN_LP_NP&t;&t;(see XMAC) Bit  3:&t;Link Partner can Next Page */
multiline_comment|/*&t;PHY_AN_LOC_NP&t;&t;(see XMAC) Bit  2:&t;Local PHY can Next Page */
multiline_comment|/*&t;PHY_AN_RX_PG&t;&t;(see XMAC) Bit  1:&t;Page Received */
DECL|macro|PHY_B_AN_LP_CAP
mdefine_line|#define PHY_B_AN_LP_CAP&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Link Partner Auto-Neg. Cap. */ &t;
multiline_comment|/*****  PHY_LONE_AUNE_EXP&t;16 bit r/o&t;Auto-Negotiation Expansion Reg *****/
DECL|macro|PHY_L_AN_BP
mdefine_line|#define PHY_L_AN_BP&t;&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Base Page Indication */
DECL|macro|PHY_L_AN_PDF
mdefine_line|#define PHY_L_AN_PDF&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Parallel Detection Fault */
multiline_comment|/*&t;PHY_AN_LP_NP&t;&t;(see XMAC) Bit  3:&t;Link Partner can Next Page */
multiline_comment|/*&t;PHY_AN_LOC_NP&t;&t;(see XMAC) Bit  2:&t;Local PHY can Next Page */
multiline_comment|/*&t;PHY_AN_RX_PG&t;&t;(see XMAC) Bit  1:&t;Page Received */
DECL|macro|PHY_B_AN_LP_CAP
mdefine_line|#define PHY_B_AN_LP_CAP&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Link Partner Auto-Neg. Cap. */ &t;
multiline_comment|/*****  PHY_XMAC_NEPG&t;&t;16 bit r/w&t;Next Page Register *****/
multiline_comment|/*****  PHY_BCOM_NEPG&t;&t;16 bit r/w&t;Next Page Register *****/
multiline_comment|/*****  PHY_LONE_NEPG&t;&t;16 bit r/w&t;Next Page Register *****/
multiline_comment|/*****  PHY_XMAC_NEPG_LP&t;16 bit r/o&t;Next Page Link Partner *****/
multiline_comment|/*****  PHY_BCOM_NEPG_LP&t;16 bit r/o&t;Next Page Link Partner *****/
multiline_comment|/*****  PHY_LONE_NEPG_LP&t;16 bit r/o&t;Next Page Link Partner *****/
DECL|macro|PHY_NP_MORE
mdefine_line|#define PHY_NP_MORE&t;&t;(1&lt;&lt;15)&t;/* Bit 15:&t;More, Next Pages to follow */
DECL|macro|PHY_NP_ACK1
mdefine_line|#define PHY_NP_ACK1&t;&t;(1&lt;&lt;14)&t;/* Bit 14: (ro)&t;Ack1, for receiving a message */
DECL|macro|PHY_NP_MSG_VAL
mdefine_line|#define PHY_NP_MSG_VAL&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Message Page valid */
DECL|macro|PHY_NP_ACK2
mdefine_line|#define PHY_NP_ACK2&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Ack2, comply with msg content */
DECL|macro|PHY_NP_TOG
mdefine_line|#define PHY_NP_TOG&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Toggle Bit, ensure sync */
DECL|macro|PHY_NP_MSG
mdefine_line|#define PHY_NP_MSG&t;&t;0x07ff&t;/* Bit 10..0:&t;Message from/to Link Partner */
multiline_comment|/*&n; * XMAC-Specific&n; */
multiline_comment|/*****  PHY_XMAC_EXT_STAT&t;16 bit r/w&t;Extended Status Register *****/
DECL|macro|PHY_X_EX_FD
mdefine_line|#define PHY_X_EX_FD&t;&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Device Supports Full Duplex */
DECL|macro|PHY_X_EX_HD
mdefine_line|#define PHY_X_EX_HD&t;&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Device Supports Half Duplex */
multiline_comment|/* Bit 13..0:&t;reserved */
multiline_comment|/*****  PHY_XMAC_RES_ABI&t;16 bit r/o&t;PHY Resolved Ability *****/
multiline_comment|/* Bit 15..9:&t;reserved */
DECL|macro|PHY_X_RS_PAUSE
mdefine_line|#define PHY_X_RS_PAUSE&t;(3&lt;&lt;7)&t;/* Bit  8..7:&t;selected Pause Mode */
DECL|macro|PHY_X_RS_HD
mdefine_line|#define PHY_X_RS_HD&t;&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Half Duplex Mode selected */
DECL|macro|PHY_X_RS_FD
mdefine_line|#define PHY_X_RS_FD&t;&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Full Duplex Mode selected */
DECL|macro|PHY_X_RS_ABLMIS
mdefine_line|#define PHY_X_RS_ABLMIS (1&lt;&lt;4)&t;/* Bit  4:&t;duplex or pause cap mismatch */
DECL|macro|PHY_X_RS_PAUMIS
mdefine_line|#define PHY_X_RS_PAUMIS (1&lt;&lt;3)&t;/* Bit  3:&t;pause capability missmatch */
multiline_comment|/* Bit  2..0:&t;reserved */
multiline_comment|/*&n; * Remote Fault Bits (PHY_X_AN_RFB) encoding&n; */
DECL|macro|X_RFB_OK
mdefine_line|#define X_RFB_OK&t;&t;(0&lt;&lt;12)&t;/* Bit 13..12&t;No errors, Link OK */
DECL|macro|X_RFB_LF
mdefine_line|#define X_RFB_LF&t;&t;(1&lt;&lt;12)&t;/* Bit 13..12&t;Link Failure */
DECL|macro|X_RFB_OFF
mdefine_line|#define X_RFB_OFF&t;&t;(2&lt;&lt;12)&t;/* Bit 13..12&t;Offline */
DECL|macro|X_RFB_AN_ERR
mdefine_line|#define X_RFB_AN_ERR&t;(3&lt;&lt;12)&t;/* Bit 13..12&t;Auto-Negotiation Error */
multiline_comment|/*&n; * Pause Bits (PHY_X_AN_PAUSE and PHY_X_RS_PAUSE) encoding&n; */
DECL|macro|PHY_X_P_NO_PAUSE
mdefine_line|#define PHY_X_P_NO_PAUSE&t;(0&lt;&lt;7)&t;/* Bit  8..7:&t;no Pause Mode */
DECL|macro|PHY_X_P_SYM_MD
mdefine_line|#define PHY_X_P_SYM_MD&t;&t;(1&lt;&lt;7)&t;/* Bit  8..7:&t;symmetric Pause Mode */
DECL|macro|PHY_X_P_ASYM_MD
mdefine_line|#define PHY_X_P_ASYM_MD&t;&t;(2&lt;&lt;7)&t;/* Bit  8..7:&t;asymmetric Pause Mode */
DECL|macro|PHY_X_P_BOTH_MD
mdefine_line|#define PHY_X_P_BOTH_MD&t;&t;(3&lt;&lt;7)&t;/* Bit  8..7:&t;both Pause Mode */
multiline_comment|/*&n; * Broadcom-Specific&n; */
multiline_comment|/*****  PHY_BCOM_1000T_CTRL&t;16 bit r/w&t;1000Base-T Control Reg *****/
DECL|macro|PHY_B_1000C_TEST
mdefine_line|#define PHY_B_1000C_TEST&t;(7&lt;&lt;13)&t;/* Bit 15..13:&t;Test Modes */
DECL|macro|PHY_B_1000C_MSE
mdefine_line|#define PHY_B_1000C_MSE&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Master/Slave Enable */
DECL|macro|PHY_B_1000C_MSC
mdefine_line|#define PHY_B_1000C_MSC&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;M/S Configuration */
DECL|macro|PHY_B_1000C_RD
mdefine_line|#define PHY_B_1000C_RD&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Repeater/DTE */
DECL|macro|PHY_B_1000C_AFD
mdefine_line|#define PHY_B_1000C_AFD&t;&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Advertise Full Duplex */
DECL|macro|PHY_B_1000C_AHD
mdefine_line|#define PHY_B_1000C_AHD&t;&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Advertise Half Duplex */
multiline_comment|/* Bit  7..0:&t;reserved */
multiline_comment|/*****  PHY_BCOM_1000T_STAT&t;16 bit r/o&t;1000Base-T Status Reg *****/
DECL|macro|PHY_B_1000S_MSF
mdefine_line|#define PHY_B_1000S_MSF&t;&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Master/Slave Fault */
DECL|macro|PHY_B_1000S_MSR
mdefine_line|#define PHY_B_1000S_MSR&t;&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Master/Slave Result */
DECL|macro|PHY_B_1000S_LRS
mdefine_line|#define PHY_B_1000S_LRS&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Local Receiver Status */
DECL|macro|PHY_B_1000S_RRS
mdefine_line|#define PHY_B_1000S_RRS&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Remote Receiver Status */
DECL|macro|PHY_B_1000S_LP_FD
mdefine_line|#define PHY_B_1000S_LP_FD&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Link Partner can FD */
DECL|macro|PHY_B_1000S_LP_HD
mdefine_line|#define PHY_B_1000S_LP_HD&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Link Partner can HD */
multiline_comment|/* Bit  9..8:&t;reserved */
DECL|macro|PHY_B_1000S_IEC
mdefine_line|#define PHY_B_1000S_IEC&t;&t;0xff&t;/* Bit  7..0:&t;Idle Error Count */
multiline_comment|/*****  PHY_BCOM_EXT_STAT&t;16 bit r/o&t;Extended Status Register *****/
DECL|macro|PHY_B_ES_X_FD_CAP
mdefine_line|#define PHY_B_ES_X_FD_CAP&t;(1&lt;&lt;15)&t;/* Bit 15:&t;1000Base-X FD capable */
DECL|macro|PHY_B_ES_X_HD_CAP
mdefine_line|#define PHY_B_ES_X_HD_CAP&t;(1&lt;&lt;14)&t;/* Bit 14:&t;1000Base-X HD capable */
DECL|macro|PHY_B_ES_T_FD_CAP
mdefine_line|#define PHY_B_ES_T_FD_CAP&t;(1&lt;&lt;13)&t;/* Bit 13:&t;1000Base-T FD capable */
DECL|macro|PHY_B_ES_T_HD_CAP
mdefine_line|#define PHY_B_ES_T_HD_CAP&t;(1&lt;&lt;12)&t;/* Bit 12:&t;1000Base-T HD capable */
multiline_comment|/* Bit 11..0:&t;reserved */
multiline_comment|/*****  PHY_BCOM_P_EXT_CTRL&t;16 bit r/w&t;PHY Extended Control Reg *****/
DECL|macro|PHY_B_PEC_MAC_PHY
mdefine_line|#define PHY_B_PEC_MAC_PHY&t;(1&lt;&lt;15)&t;/* Bit 15:&t;10BIT/GMI-Interface */
DECL|macro|PHY_B_PEC_DIS_CROSS
mdefine_line|#define PHY_B_PEC_DIS_CROSS&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Disable MDI Crossover */
DECL|macro|PHY_B_PEC_TX_DIS
mdefine_line|#define PHY_B_PEC_TX_DIS&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Tx output Disabled */
DECL|macro|PHY_B_PEC_INT_DIS
mdefine_line|#define PHY_B_PEC_INT_DIS&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Interrupts Disabled */
DECL|macro|PHY_B_PEC_F_INT
mdefine_line|#define PHY_B_PEC_F_INT&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Force Interrupt */
DECL|macro|PHY_B_PEC_BY_45
mdefine_line|#define PHY_B_PEC_BY_45&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Bypass 4B5B-Decoder */
DECL|macro|PHY_B_PEC_BY_SCR
mdefine_line|#define PHY_B_PEC_BY_SCR&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Bypass Scrambler */
DECL|macro|PHY_B_PEC_BY_MLT3
mdefine_line|#define PHY_B_PEC_BY_MLT3&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Bypass MLT3 Encoder */
DECL|macro|PHY_B_PEC_BY_RXA
mdefine_line|#define PHY_B_PEC_BY_RXA&t;(1&lt;&lt;7)&t;/* Bit  7:&t;Bypass Rx Alignm. */
DECL|macro|PHY_B_PEC_RES_SCR
mdefine_line|#define PHY_B_PEC_RES_SCR&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Reset Scrambler */
DECL|macro|PHY_B_PEC_EN_LTR
mdefine_line|#define PHY_B_PEC_EN_LTR&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Ena LED Traffic Mode */
DECL|macro|PHY_B_PEC_LED_ON
mdefine_line|#define PHY_B_PEC_LED_ON&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Force LED&squot;s on */
DECL|macro|PHY_B_PEC_LED_OFF
mdefine_line|#define PHY_B_PEC_LED_OFF&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Force LED&squot;s off */
DECL|macro|PHY_B_PEC_EX_IPG
mdefine_line|#define PHY_B_PEC_EX_IPG&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Extend Tx IPG Mode */
DECL|macro|PHY_B_PEC_3_LED
mdefine_line|#define PHY_B_PEC_3_LED&t;&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Three Link LED mode */
DECL|macro|PHY_B_PEC_HIGH_LA
mdefine_line|#define PHY_B_PEC_HIGH_LA&t;(1&lt;&lt;0)&t;/* Bit  0:&t;GMII FIFO Elasticy */
multiline_comment|/*****  PHY_BCOM_P_EXT_STAT&t;16 bit r/o&t;PHY Extended Status Reg *****/
multiline_comment|/* Bit 15..14:&t;reserved */
DECL|macro|PHY_B_PES_CROSS_STAT
mdefine_line|#define PHY_B_PES_CROSS_STAT&t;(1&lt;&lt;13)&t;/* Bit 13:&t;MDI Crossover Status */
DECL|macro|PHY_B_PES_INT_STAT
mdefine_line|#define PHY_B_PES_INT_STAT&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Interrupt Status */
DECL|macro|PHY_B_PES_RRS
mdefine_line|#define PHY_B_PES_RRS&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Remote Receiver Stat. */
DECL|macro|PHY_B_PES_LRS
mdefine_line|#define PHY_B_PES_LRS&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Local Receiver Stat. */
DECL|macro|PHY_B_PES_LOCKED
mdefine_line|#define PHY_B_PES_LOCKED&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Locked */
DECL|macro|PHY_B_PES_LS
mdefine_line|#define PHY_B_PES_LS&t;&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Link Status */
DECL|macro|PHY_B_PES_RF
mdefine_line|#define PHY_B_PES_RF&t;&t;(1&lt;&lt;7)&t;/* Bit  7:&t;Remote Fault */
DECL|macro|PHY_B_PES_CE_ER
mdefine_line|#define PHY_B_PES_CE_ER&t;&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Carrier Ext Error */
DECL|macro|PHY_B_PES_BAD_SSD
mdefine_line|#define PHY_B_PES_BAD_SSD&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Bad SSD */
DECL|macro|PHY_B_PES_BAD_ESD
mdefine_line|#define PHY_B_PES_BAD_ESD&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Bad ESD */
DECL|macro|PHY_B_PES_RX_ER
mdefine_line|#define PHY_B_PES_RX_ER&t;&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Receive Error */
DECL|macro|PHY_B_PES_TX_ER
mdefine_line|#define PHY_B_PES_TX_ER&t;&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Transmit Error */
DECL|macro|PHY_B_PES_LOCK_ER
mdefine_line|#define PHY_B_PES_LOCK_ER&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Lock Error */
DECL|macro|PHY_B_PES_MLT3_ER
mdefine_line|#define PHY_B_PES_MLT3_ER&t;(1&lt;&lt;0)&t;/* Bit  0:&t;MLT3 code Error */
multiline_comment|/*****  PHY_BCOM_FC_CTR&t;&t;16 bit r/w&t;False Carrier Counter *****/
multiline_comment|/* Bit 15..8:&t;reserved */
DECL|macro|PHY_B_FC_CTR
mdefine_line|#define PHY_B_FC_CTR&t;&t;0xff&t;/* Bit  7..0:&t;False Carrier Counter */
multiline_comment|/*****  PHY_BCOM_RNO_CTR&t;16 bit r/w&t;Receive NOT_OK Counter *****/
DECL|macro|PHY_B_RC_LOC_MSK
mdefine_line|#define PHY_B_RC_LOC_MSK&t;0xff00&t;/* Bit 15..8:&t;Local Rx NOT_OK cnt */
DECL|macro|PHY_B_RC_REM_MSK
mdefine_line|#define PHY_B_RC_REM_MSK&t;0x00ff&t;/* Bit  7..0:&t;Remote Rx NOT_OK cnt */
multiline_comment|/*****  PHY_BCOM_AUX_CTRL&t;16 bit r/w&t;Auxiliary Control Reg *****/
DECL|macro|PHY_B_AC_L_SQE
mdefine_line|#define PHY_B_AC_L_SQE&t;&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Low Squelch */
DECL|macro|PHY_B_AC_LONG_PACK
mdefine_line|#define PHY_B_AC_LONG_PACK&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Rx Long Packets */
DECL|macro|PHY_B_AC_ER_CTRL
mdefine_line|#define PHY_B_AC_ER_CTRL&t;(3&lt;&lt;12)&t;/* Bit 13..12:&t;Edgerate Control */
multiline_comment|/* Bit 11:&t;reserved */
DECL|macro|PHY_B_AC_TX_TST
mdefine_line|#define PHY_B_AC_TX_TST&t;&t;(1&lt;&lt;10) /* Bit 10:&t;Tx test bit, always 1 */
multiline_comment|/* Bit  9.. 8:&t;reserved */
DECL|macro|PHY_B_AC_DIS_PRF
mdefine_line|#define PHY_B_AC_DIS_PRF&t;(1&lt;&lt;7)&t;/* Bit  7:&t;dis part resp filter */
multiline_comment|/* Bit  6:&t;reserved */
DECL|macro|PHY_B_AC_DIS_PM
mdefine_line|#define PHY_B_AC_DIS_PM&t;&t;(1&lt;&lt;5)&t;/* Bit  5:&t;dis power management */
multiline_comment|/* Bit  4:&t;reserved */
DECL|macro|PHY_B_AC_DIAG
mdefine_line|#define PHY_B_AC_DIAG&t;&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Diagnostic Mode */
multiline_comment|/* Bit  2.. 0:&t;reserved */
multiline_comment|/*****  PHY_BCOM_AUX_STAT&t;16 bit r/o&t;Auxiliary Status Reg *****/
DECL|macro|PHY_B_AS_AN_C
mdefine_line|#define PHY_B_AS_AN_C&t;&t;(1&lt;&lt;15)&t;/* Bit 15:&t;AutoNeg complete */
DECL|macro|PHY_B_AS_AN_CA
mdefine_line|#define PHY_B_AS_AN_CA&t;&t;(1&lt;&lt;14)&t;/* Bit 14:&t;AN Complete Ack */
DECL|macro|PHY_B_AS_ANACK_D
mdefine_line|#define PHY_B_AS_ANACK_D&t;(1&lt;&lt;13)&t;/* Bit 13:&t;AN Ack Detect */
DECL|macro|PHY_B_AS_ANAB_D
mdefine_line|#define PHY_B_AS_ANAB_D&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;AN Ability Detect */
DECL|macro|PHY_B_AS_NPW
mdefine_line|#define PHY_B_AS_NPW&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;AN Next Page Wait */
DECL|macro|PHY_B_AS_AN_RES_MSK
mdefine_line|#define PHY_B_AS_AN_RES_MSK&t;(7&lt;&lt;8)&t;/* Bit 10..8:&t;AN HDC */
DECL|macro|PHY_B_AS_PDF
mdefine_line|#define PHY_B_AS_PDF&t;&t;(1&lt;&lt;7)&t;/* Bit  7:&t;Parallel Detect. Fault */
DECL|macro|PHY_B_AS_RF
mdefine_line|#define PHY_B_AS_RF&t;&t;&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Remote Fault */
DECL|macro|PHY_B_AS_ANP_R
mdefine_line|#define PHY_B_AS_ANP_R&t;&t;(1&lt;&lt;5)&t;/* Bit  5:&t;AN Page Received */
DECL|macro|PHY_B_AS_LP_ANAB
mdefine_line|#define PHY_B_AS_LP_ANAB&t;(1&lt;&lt;4)&t;/* Bit  4:&t;LP AN Ability */
DECL|macro|PHY_B_AS_LP_NPAB
mdefine_line|#define PHY_B_AS_LP_NPAB&t;(1&lt;&lt;3)&t;/* Bit  3:&t;LP Next Page Ability */
DECL|macro|PHY_B_AS_LS
mdefine_line|#define PHY_B_AS_LS&t;&t;&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Link Status */
DECL|macro|PHY_B_AS_PRR
mdefine_line|#define PHY_B_AS_PRR&t;&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Pause Resolution-Rx */
DECL|macro|PHY_B_AS_PRT
mdefine_line|#define PHY_B_AS_PRT&t;&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Pause Resolution-Tx */
DECL|macro|PHY_B_AS_PAUSE_MSK
mdefine_line|#define PHY_B_AS_PAUSE_MSK&t;(PHY_B_AS_PRR | PHY_B_AS_PRT)
multiline_comment|/*****  PHY_BCOM_INT_STAT&t;16 bit r/o&t;Interrupt Status Reg *****/
multiline_comment|/*****  PHY_BCOM_INT_MASK&t;16 bit r/w&t;Interrupt Mask Reg *****/
multiline_comment|/* Bit 15:&t;reserved */
DECL|macro|PHY_B_IS_PSE
mdefine_line|#define PHY_B_IS_PSE&t;&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Pair Swap Error */
DECL|macro|PHY_B_IS_MDXI_SC
mdefine_line|#define PHY_B_IS_MDXI_SC&t;(1&lt;&lt;13)&t;/* Bit 13:&t;MDIX Status Change */
DECL|macro|PHY_B_IS_HCT
mdefine_line|#define PHY_B_IS_HCT&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;counter above 32k */
DECL|macro|PHY_B_IS_LCT
mdefine_line|#define PHY_B_IS_LCT&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;counter above 128 */
DECL|macro|PHY_B_IS_AN_PR
mdefine_line|#define PHY_B_IS_AN_PR&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Page Received */
DECL|macro|PHY_B_IS_NO_HDCL
mdefine_line|#define PHY_B_IS_NO_HDCL&t;(1&lt;&lt;9)&t;/* Bit  9:&t;No HCD Link */
DECL|macro|PHY_B_IS_NO_HDC
mdefine_line|#define PHY_B_IS_NO_HDC&t;&t;(1&lt;&lt;8)&t;/* Bit  8:&t;No HCD */
DECL|macro|PHY_B_IS_NEG_USHDC
mdefine_line|#define PHY_B_IS_NEG_USHDC&t;(1&lt;&lt;7)&t;/* Bit  7:&t;Negotiated Unsup. HCD */
DECL|macro|PHY_B_IS_SCR_S_ER
mdefine_line|#define PHY_B_IS_SCR_S_ER&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Scrambler Sync Error */
DECL|macro|PHY_B_IS_RRS_CHANGE
mdefine_line|#define PHY_B_IS_RRS_CHANGE&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Remote Rx Stat Change */
DECL|macro|PHY_B_IS_LRS_CHANGE
mdefine_line|#define PHY_B_IS_LRS_CHANGE&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Local Rx Stat Change */
DECL|macro|PHY_B_IS_DUP_CHANGE
mdefine_line|#define PHY_B_IS_DUP_CHANGE&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Duplex Mode Change */
DECL|macro|PHY_B_IS_LSP_CHANGE
mdefine_line|#define PHY_B_IS_LSP_CHANGE&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Link Speed Change */
DECL|macro|PHY_B_IS_LST_CHANGE
mdefine_line|#define PHY_B_IS_LST_CHANGE&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Link Status Changed */
DECL|macro|PHY_B_IS_CRC_ER
mdefine_line|#define PHY_B_IS_CRC_ER&t;&t;(1&lt;&lt;0)&t;/* Bit  0:&t;CRC Error */
DECL|macro|PHY_B_DEF_MSK
mdefine_line|#define PHY_B_DEF_MSK&t;(~(PHY_B_IS_AN_PR | PHY_B_IS_LST_CHANGE))
multiline_comment|/* Pause Bits (PHY_B_AN_ASP and PHY_B_AN_PC) encoding */
DECL|macro|PHY_B_P_NO_PAUSE
mdefine_line|#define PHY_B_P_NO_PAUSE&t;(0&lt;&lt;10)&t;/* Bit 11..10:&t;no Pause Mode */
DECL|macro|PHY_B_P_SYM_MD
mdefine_line|#define PHY_B_P_SYM_MD&t;&t;(1&lt;&lt;10)&t;/* Bit 11..10:&t;symmetric Pause Mode */
DECL|macro|PHY_B_P_ASYM_MD
mdefine_line|#define PHY_B_P_ASYM_MD&t;&t;(2&lt;&lt;10)&t;/* Bit 11..10:&t;asymmetric Pause Mode */
DECL|macro|PHY_B_P_BOTH_MD
mdefine_line|#define PHY_B_P_BOTH_MD&t;&t;(3&lt;&lt;10)&t;/* Bit 11..10:&t;both Pause Mode */
multiline_comment|/*&n; * Resolved Duplex mode and Capabilities (Aux Status Summary Reg)&n; */
DECL|macro|PHY_B_RES_1000FD
mdefine_line|#define PHY_B_RES_1000FD&t;(7&lt;&lt;8)&t;/* Bit 10..8:&t;1000Base-T Full Dup. */
DECL|macro|PHY_B_RES_1000HD
mdefine_line|#define PHY_B_RES_1000HD&t;(6&lt;&lt;8)&t;/* Bit 10..8:&t;1000Base-T Half Dup. */
multiline_comment|/* others: 100/10: invalid for us */
multiline_comment|/*&n; * Level One-Specific&n; */
multiline_comment|/*****  PHY_LONE_1000T_CTRL&t;16 bit r/w&t;1000Base-T Control Reg *****/
DECL|macro|PHY_L_1000C_TEST
mdefine_line|#define PHY_L_1000C_TEST&t;(7&lt;&lt;13)&t;/* Bit 15..13:&t;Test Modes */
DECL|macro|PHY_L_1000C_MSE
mdefine_line|#define PHY_L_1000C_MSE&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Master/Slave Enable */
DECL|macro|PHY_L_1000C_MSC
mdefine_line|#define PHY_L_1000C_MSC&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;M/S Configuration */
DECL|macro|PHY_L_1000C_RD
mdefine_line|#define PHY_L_1000C_RD&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Repeater/DTE */
DECL|macro|PHY_L_1000C_AFD
mdefine_line|#define PHY_L_1000C_AFD&t;&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Advertise Full Duplex */
DECL|macro|PHY_L_1000C_AHD
mdefine_line|#define PHY_L_1000C_AHD&t;&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Advertise Half Duplex */
multiline_comment|/* Bit  7..0:&t;reserved */
multiline_comment|/*****  PHY_LONE_1000T_STAT&t;16 bit r/o&t;1000Base-T Status Reg *****/
DECL|macro|PHY_L_1000S_MSF
mdefine_line|#define PHY_L_1000S_MSF&t;&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Master/Slave Fault */
DECL|macro|PHY_L_1000S_MSR
mdefine_line|#define PHY_L_1000S_MSR&t;&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Master/Slave Result */
DECL|macro|PHY_L_1000S_LRS
mdefine_line|#define PHY_L_1000S_LRS&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Local Receiver Status */
DECL|macro|PHY_L_1000S_RRS
mdefine_line|#define PHY_L_1000S_RRS&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Remote Receiver Status */
DECL|macro|PHY_L_1000S_LP_FD
mdefine_line|#define PHY_L_1000S_LP_FD&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Link Partner can FD */
DECL|macro|PHY_L_1000S_LP_HD
mdefine_line|#define PHY_L_1000S_LP_HD&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Link Partner can HD */
multiline_comment|/* Bit  9..8:&t;reserved */
DECL|macro|PHY_B_1000S_IEC
mdefine_line|#define PHY_B_1000S_IEC&t;&t;0xff&t;/* Bit  7..0:&t;Idle Error Count */
multiline_comment|/*****  PHY_LONE_EXT_STAT&t;16 bit r/o&t;Extended Status Register *****/
DECL|macro|PHY_L_ES_X_FD_CAP
mdefine_line|#define PHY_L_ES_X_FD_CAP&t;(1&lt;&lt;15)&t;/* Bit 15:&t;1000Base-X FD capable */
DECL|macro|PHY_L_ES_X_HD_CAP
mdefine_line|#define PHY_L_ES_X_HD_CAP&t;(1&lt;&lt;14)&t;/* Bit 14:&t;1000Base-X HD capable */
DECL|macro|PHY_L_ES_T_FD_CAP
mdefine_line|#define PHY_L_ES_T_FD_CAP&t;(1&lt;&lt;13)&t;/* Bit 13:&t;1000Base-T FD capable */
DECL|macro|PHY_L_ES_T_HD_CAP
mdefine_line|#define PHY_L_ES_T_HD_CAP&t;(1&lt;&lt;12)&t;/* Bit 12:&t;1000Base-T HD capable */
multiline_comment|/* Bit 11..0:&t;reserved */
multiline_comment|/*****  PHY_LONE_PORT_CFG&t;16 bit r/w&t;Port Configuration Reg *****/
DECL|macro|PHY_L_PC_REP_MODE
mdefine_line|#define PHY_L_PC_REP_MODE&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Repeater Mode */
multiline_comment|/* Bit 14:&t;reserved */
DECL|macro|PHY_L_PC_TX_DIS
mdefine_line|#define PHY_L_PC_TX_DIS&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Tx output Disabled */
DECL|macro|PHY_L_PC_BY_SCR
mdefine_line|#define PHY_L_PC_BY_SCR&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Bypass Scrambler */
DECL|macro|PHY_L_PC_BY_45
mdefine_line|#define PHY_L_PC_BY_45&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Bypass 4B5B-Decoder */
DECL|macro|PHY_L_PC_JAB_DIS
mdefine_line|#define PHY_L_PC_JAB_DIS&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Jabber Disabled */
DECL|macro|PHY_L_PC_SQE
mdefine_line|#define PHY_L_PC_SQE&t;&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Enable Heartbeat */
DECL|macro|PHY_L_PC_TP_LOOP
mdefine_line|#define PHY_L_PC_TP_LOOP&t;(1&lt;&lt;8)&t;/* Bit  8:&t;TP Loopback */
DECL|macro|PHY_L_PC_SSS
mdefine_line|#define PHY_L_PC_SSS&t;&t;(1&lt;&lt;7)&t;/* Bit  7:&t;Smart Speed Selection */
DECL|macro|PHY_L_PC_FIFO_SIZE
mdefine_line|#define PHY_L_PC_FIFO_SIZE&t;(1&lt;&lt;6)&t;/* Bit  6:&t;FIFO Size */
DECL|macro|PHY_L_PC_PRE_EN
mdefine_line|#define PHY_L_PC_PRE_EN&t;&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Preamble Enable */
DECL|macro|PHY_L_PC_CIM
mdefine_line|#define PHY_L_PC_CIM&t;&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Carrier Integrity Mon */
DECL|macro|PHY_L_PC_10_SER
mdefine_line|#define PHY_L_PC_10_SER&t;&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Use Serial Output */
DECL|macro|PHY_L_PC_ANISOL
mdefine_line|#define PHY_L_PC_ANISOL&t;&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Unisolate Port */
DECL|macro|PHY_L_PC_TEN_BIT
mdefine_line|#define PHY_L_PC_TEN_BIT&t;(1&lt;&lt;1)&t;/* Bit  1:&t;10bit iface mode on */
DECL|macro|PHY_L_PC_ALTCLOCK
mdefine_line|#define PHY_L_PC_ALTCLOCK&t;(1&lt;&lt;0)&t;/* Bit  0: (ro)&t;ALTCLOCK Mode on */
multiline_comment|/*****  PHY_LONE_Q_STAT&t;&t;16 bit r/o&t;Quick Status Reg *****/
DECL|macro|PHY_L_QS_D_RATE
mdefine_line|#define PHY_L_QS_D_RATE&t;&t;(3&lt;&lt;14)&t;/* Bit 15..14:&t;Data Rate */
DECL|macro|PHY_L_QS_TX_STAT
mdefine_line|#define PHY_L_QS_TX_STAT&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Transmitting */
DECL|macro|PHY_L_QS_RX_STAT
mdefine_line|#define PHY_L_QS_RX_STAT&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Receiving */
DECL|macro|PHY_L_QS_COL_STAT
mdefine_line|#define PHY_L_QS_COL_STAT&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Collision */
DECL|macro|PHY_L_QS_L_STAT
mdefine_line|#define PHY_L_QS_L_STAT&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Link is up */
DECL|macro|PHY_L_QS_DUP_MOD
mdefine_line|#define PHY_L_QS_DUP_MOD&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Full/Half Duplex */
DECL|macro|PHY_L_QS_AN
mdefine_line|#define PHY_L_QS_AN&t;&t;&t;(1&lt;&lt;8)&t;/* Bit  8:&t;AutoNeg is On */
DECL|macro|PHY_L_QS_AN_C
mdefine_line|#define PHY_L_QS_AN_C&t;&t;(1&lt;&lt;7)&t;/* Bit  7:&t;AN is Complete */
DECL|macro|PHY_L_QS_LLE
mdefine_line|#define PHY_L_QS_LLE&t;&t;(7&lt;&lt;4)&t;/* Bit  6:&t;Line Length Estim. */
DECL|macro|PHY_L_QS_PAUSE
mdefine_line|#define PHY_L_QS_PAUSE&t;&t;(1&lt;&lt;3)&t;/* Bit  3:&t;LP advertised Pause */
DECL|macro|PHY_L_QS_AS_PAUSE
mdefine_line|#define PHY_L_QS_AS_PAUSE&t;(1&lt;&lt;2)&t;/* Bit  2:&t;LP adv. asym. Pause */
DECL|macro|PHY_L_QS_ISOLATE
mdefine_line|#define PHY_L_QS_ISOLATE&t;(1&lt;&lt;1)&t;/* Bit  1:&t;CIM Isolated */
DECL|macro|PHY_L_QS_EVENT
mdefine_line|#define PHY_L_QS_EVENT&t;&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Event has occurred */
multiline_comment|/*****  PHY_LONE_INT_ENAB&t;16 bit r/w&t;Interrupt Enable Reg *****/
multiline_comment|/*****  PHY_LONE_INT_STAT&t;16 bit r/o&t;Interrupt Status Reg *****/
multiline_comment|/* Bit 15..14:&t;reserved */
DECL|macro|PHY_L_IS_AN_F
mdefine_line|#define PHY_L_IS_AN_F&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Auto-Negotiation fault */
multiline_comment|/* Bit 12:&t;not described */
DECL|macro|PHY_L_IS_CROSS
mdefine_line|#define PHY_L_IS_CROSS&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Crossover used */
DECL|macro|PHY_L_IS_POL
mdefine_line|#define PHY_L_IS_POL&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Polarity correct. used */
DECL|macro|PHY_L_IS_SS
mdefine_line|#define PHY_L_IS_SS&t;&t;&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Smart Speed Downgrade */
DECL|macro|PHY_L_IS_CFULL
mdefine_line|#define PHY_L_IS_CFULL&t;&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Counter Full */
DECL|macro|PHY_L_IS_AN_C
mdefine_line|#define PHY_L_IS_AN_C&t;&t;(1&lt;&lt;7)&t;/* Bit  7:&t;AutoNeg Complete */
DECL|macro|PHY_L_IS_SPEED
mdefine_line|#define PHY_L_IS_SPEED&t;&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Speed Changed */
DECL|macro|PHY_L_IS_DUP
mdefine_line|#define PHY_L_IS_DUP&t;&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Duplex Changed */
DECL|macro|PHY_L_IS_LS
mdefine_line|#define PHY_L_IS_LS&t;&t;&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Link Status Changed */
DECL|macro|PHY_L_IS_ISOL
mdefine_line|#define PHY_L_IS_ISOL&t;&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Isolate Occured */
DECL|macro|PHY_L_IS_MDINT
mdefine_line|#define PHY_L_IS_MDINT&t;&t;(1&lt;&lt;2)&t;/* Bit  2: (ro)&t;STAT: MII Int Pending */
DECL|macro|PHY_L_IS_INTEN
mdefine_line|#define PHY_L_IS_INTEN&t;&t;(1&lt;&lt;1)&t;/* Bit  1:&t;ENAB: Enable IRQs */
DECL|macro|PHY_L_IS_FORCE
mdefine_line|#define PHY_L_IS_FORCE&t;&t;(1&lt;&lt;0)&t;/* Bit  0:&t;ENAB: Force Interrupt */
multiline_comment|/* int. mask */
DECL|macro|PHY_L_DEF_MSK
mdefine_line|#define PHY_L_DEF_MSK&t;&t;(PHY_L_IS_LS | PHY_L_IS_ISOL | PHY_L_IS_INTEN)
multiline_comment|/*****  PHY_LONE_LED_CFG&t;16 bit r/w&t;LED Configuration Reg *****/
DECL|macro|PHY_L_LC_LEDC
mdefine_line|#define PHY_L_LC_LEDC&t;&t;(3&lt;&lt;14)&t;/* Bit 15..14:&t;Col/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDR
mdefine_line|#define PHY_L_LC_LEDR&t;&t;(3&lt;&lt;12)&t;/* Bit 13..12:&t;Rx/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDT
mdefine_line|#define PHY_L_LC_LEDT&t;&t;(3&lt;&lt;10)&t;/* Bit 11..10:&t;Tx/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDG
mdefine_line|#define PHY_L_LC_LEDG&t;&t;(3&lt;&lt;8)&t;/* Bit  9..8:&t;Giga/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDS
mdefine_line|#define PHY_L_LC_LEDS&t;&t;(3&lt;&lt;6)&t;/* Bit  7..6:&t;10-100/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDL
mdefine_line|#define PHY_L_LC_LEDL&t;&t;(3&lt;&lt;4)&t;/* Bit  5..4:&t;Link/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDF
mdefine_line|#define PHY_L_LC_LEDF&t;&t;(3&lt;&lt;2)&t;/* Bit  3..2:&t;Duplex/Blink/On/Off */
DECL|macro|PHY_L_LC_PSTRECH
mdefine_line|#define PHY_L_LC_PSTRECH&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Strech LED Pulses */
DECL|macro|PHY_L_LC_FREQ
mdefine_line|#define PHY_L_LC_FREQ&t;&t;(1&lt;&lt;0)&t;/* Bit  0:&t;30/100 ms */
multiline_comment|/*****  PHY_LONE_PORT_CTRL&t;16 bit r/w&t;Port Control Reg *****/
DECL|macro|PHY_L_PC_TX_TCLK
mdefine_line|#define PHY_L_PC_TX_TCLK&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Enable TX_TCLK */
multiline_comment|/* Bit 14:&t;reserved */
DECL|macro|PHY_L_PC_ALT_NP
mdefine_line|#define PHY_L_PC_ALT_NP&t;&t;(1&lt;&lt;13)&t;/* Bit 14:&t;Alternate Next Page */
DECL|macro|PHY_L_PC_GMII_ALT
mdefine_line|#define PHY_L_PC_GMII_ALT&t;(1&lt;&lt;12)&t;/* Bit 13:&t;Alternate GMII driver */
multiline_comment|/* Bit 11:&t;reserved */
DECL|macro|PHY_L_PC_TEN_CRS
mdefine_line|#define PHY_L_PC_TEN_CRS&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Extend CRS*/
multiline_comment|/* Bit  9..0:&t;not described */
multiline_comment|/*****  PHY_LONE_CIM&t;&t;16 bit r/o&t;CIM Reg *****/
DECL|macro|PHY_L_CIM_ISOL
mdefine_line|#define PHY_L_CIM_ISOL&t;&t;(255&lt;&lt;8)/* Bit 15..8:&t;Isolate Count */
DECL|macro|PHY_L_CIM_FALSE_CAR
mdefine_line|#define PHY_L_CIM_FALSE_CAR&t;(255&lt;&lt;0)/* Bit  7..0:&t;False Carrier Count */
multiline_comment|/*&n; * Pause Bits (PHY_L_AN_ASP and PHY_L_AN_PC) encoding&n; */
DECL|macro|PHY_L_P_NO_PAUSE
mdefine_line|#define PHY_L_P_NO_PAUSE&t;(0&lt;&lt;10)&t;/* Bit 11..10:&t;no Pause Mode */
DECL|macro|PHY_L_P_SYM_MD
mdefine_line|#define PHY_L_P_SYM_MD&t;&t;(1&lt;&lt;10)&t;/* Bit 11..10:&t;symmetric Pause Mode */
DECL|macro|PHY_L_P_ASYM_MD
mdefine_line|#define PHY_L_P_ASYM_MD&t;&t;(2&lt;&lt;10)&t;/* Bit 11..10:&t;asymmetric Pause Mode */
DECL|macro|PHY_L_P_BOTH_MD
mdefine_line|#define PHY_L_P_BOTH_MD&t;&t;(3&lt;&lt;10)&t;/* Bit 11..10:&t;both Pause Mode */
multiline_comment|/*&n; * National-Specific&n; */
multiline_comment|/*****  PHY_NAT_1000T_CTRL&t;16 bit r/w&t;1000Base-T Control Reg *****/
DECL|macro|PHY_N_1000C_TEST
mdefine_line|#define PHY_N_1000C_TEST&t;(7&lt;&lt;13)&t;/* Bit 15..13:&t;Test Modes */
DECL|macro|PHY_N_1000C_MSE
mdefine_line|#define PHY_N_1000C_MSE&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Master/Slave Enable */
DECL|macro|PHY_N_1000C_MSC
mdefine_line|#define PHY_N_1000C_MSC&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;M/S Configuration */
DECL|macro|PHY_N_1000C_RD
mdefine_line|#define PHY_N_1000C_RD&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Repeater/DTE */
DECL|macro|PHY_N_1000C_AFD
mdefine_line|#define PHY_N_1000C_AFD&t;&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Advertise Full Duplex */
DECL|macro|PHY_N_1000C_AHD
mdefine_line|#define PHY_N_1000C_AHD&t;&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Advertise Half Duplex */
DECL|macro|PHY_N_1000C_APC
mdefine_line|#define PHY_N_1000C_APC&t;&t;(1&lt;&lt;7)&t;/* Bit  7:&t;Asymmetric Pause Cap. */
multiline_comment|/* Bit  6..0:&t;reserved */
multiline_comment|/*****  PHY_NAT_1000T_STAT&t;16 bit r/o&t;1000Base-T Status Reg *****/
DECL|macro|PHY_N_1000S_MSF
mdefine_line|#define PHY_N_1000S_MSF&t;&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Master/Slave Fault */
DECL|macro|PHY_N_1000S_MSR
mdefine_line|#define PHY_N_1000S_MSR&t;&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Master/Slave Result */
DECL|macro|PHY_N_1000S_LRS
mdefine_line|#define PHY_N_1000S_LRS&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Local Receiver Status */
DECL|macro|PHY_N_1000S_RRS
mdefine_line|#define PHY_N_1000S_RRS&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Remote Receiver Status*/
DECL|macro|PHY_N_1000S_LP_FD
mdefine_line|#define PHY_N_1000S_LP_FD&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Link Partner can FD */
DECL|macro|PHY_N_1000S_LP_HD
mdefine_line|#define PHY_N_1000S_LP_HD&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Link Partner can HD */
DECL|macro|PHY_N_1000C_LP_APC
mdefine_line|#define PHY_N_1000C_LP_APC&t;(1&lt;&lt;9)&t;/* Bit  9:&t;LP Asym. Pause Cap. */
multiline_comment|/* Bit  8:&t;reserved */
DECL|macro|PHY_N_1000S_IEC
mdefine_line|#define PHY_N_1000S_IEC&t;&t;0xff&t;/* Bit  7..0:&t;Idle Error Count */
multiline_comment|/*****  PHY_NAT_EXT_STAT&t;16 bit r/o&t;Extended Status Register *****/
DECL|macro|PHY_N_ES_X_FD_CAP
mdefine_line|#define PHY_N_ES_X_FD_CAP&t;(1&lt;&lt;15)&t;/* Bit 15:&t;1000Base-X FD capable */
DECL|macro|PHY_N_ES_X_HD_CAP
mdefine_line|#define PHY_N_ES_X_HD_CAP&t;(1&lt;&lt;14)&t;/* Bit 14:&t;1000Base-X HD capable */
DECL|macro|PHY_N_ES_T_FD_CAP
mdefine_line|#define PHY_N_ES_T_FD_CAP&t;(1&lt;&lt;13)&t;/* Bit 13:&t;1000Base-T FD capable */
DECL|macro|PHY_N_ES_T_HD_CAP
mdefine_line|#define PHY_N_ES_T_HD_CAP&t;(1&lt;&lt;12)&t;/* Bit 12:&t;1000Base-T HD capable */
multiline_comment|/* Bit 11..0:&t;reserved */
multiline_comment|/* todo: those are still missing */
multiline_comment|/*****  PHY_NAT_EXT_CTRL1&t;16 bit r/o&t;Extended Control Reg1 *****/
multiline_comment|/*****  PHY_NAT_Q_STAT1&t;&t;16 bit r/o&t;Quick Status Reg1 *****/
multiline_comment|/*****  PHY_NAT_10B_OP&t;&t;16 bit r/o&t;10Base-T Operations Reg *****/
multiline_comment|/*****  PHY_NAT_EXT_CTRL2&t;16 bit r/o&t;Extended Control Reg1 *****/
multiline_comment|/*****  PHY_NAT_Q_STAT2&t;&t;16 bit r/o&t;Quick Status Reg2 *****/
multiline_comment|/*****  PHY_NAT_PHY_ADDR&t;16 bit r/o&t;PHY Address Register *****/
multiline_comment|/*&n; * Marvell-Specific&n; */
multiline_comment|/*****  PHY_MARV_AUNE_ADV&t;16 bit r/w&t;Auto-Negotiation Advertisement *****/
multiline_comment|/*****  PHY_MARV_AUNE_LP&t;16 bit r/w&t;Link Part Ability Reg *****/
DECL|macro|PHY_M_AN_NXT_PG
mdefine_line|#define PHY_M_AN_NXT_PG&t;&t;BIT_15&t;/* Request Next Page */
DECL|macro|PHY_M_AN_ACK
mdefine_line|#define PHY_M_AN_ACK&t;&t;BIT_14&t;/* (ro)&t;Acknowledge Received */
DECL|macro|PHY_M_AN_RF
mdefine_line|#define PHY_M_AN_RF&t;&t;&t;BIT_13&t;/* Remote Fault */
multiline_comment|/* Bit 12:&t;reserved */
DECL|macro|PHY_M_AN_ASP
mdefine_line|#define PHY_M_AN_ASP&t;&t;BIT_11&t;/* Asymmetric Pause */
DECL|macro|PHY_M_AN_PC
mdefine_line|#define PHY_M_AN_PC&t;&t;&t;BIT_10&t;/* MAC Pause implemented */
DECL|macro|PHY_M_AN_100_FD
mdefine_line|#define PHY_M_AN_100_FD&t;&t;BIT_8&t;/* Advertise 100Base-TX Full Duplex */
DECL|macro|PHY_M_AN_100_HD
mdefine_line|#define PHY_M_AN_100_HD&t;&t;BIT_7&t;/* Advertise 100Base-TX Half Duplex */
DECL|macro|PHY_M_AN_10_FD
mdefine_line|#define PHY_M_AN_10_FD&t;&t;BIT_6&t;/* Advertise 10Base-TX Full Duplex */
DECL|macro|PHY_M_AN_10_HD
mdefine_line|#define PHY_M_AN_10_HD&t;&t;BIT_5&t;/* Advertise 10Base-TX Half Duplex */
multiline_comment|/* special defines for FIBER (88E1011S only) */
DECL|macro|PHY_M_AN_ASP_X
mdefine_line|#define PHY_M_AN_ASP_X&t;&t;BIT_8&t;/* Asymmetric Pause */
DECL|macro|PHY_M_AN_PC_X
mdefine_line|#define PHY_M_AN_PC_X&t;&t;BIT_7&t;/* MAC Pause implemented */
DECL|macro|PHY_M_AN_1000X_AHD
mdefine_line|#define PHY_M_AN_1000X_AHD&t;BIT_6&t;/* Advertise 10000Base-X Half Duplex */
DECL|macro|PHY_M_AN_1000X_AFD
mdefine_line|#define PHY_M_AN_1000X_AFD&t;BIT_5&t;/* Advertise 10000Base-X Full Duplex */
multiline_comment|/* Pause Bits (PHY_M_AN_ASP_X and PHY_M_AN_PC_X) encoding */
DECL|macro|PHY_M_P_NO_PAUSE_X
mdefine_line|#define PHY_M_P_NO_PAUSE_X&t;(0&lt;&lt;7)&t;/* Bit  8.. 7:&t;no Pause Mode */
DECL|macro|PHY_M_P_SYM_MD_X
mdefine_line|#define PHY_M_P_SYM_MD_X&t;(1&lt;&lt;7)&t;/* Bit  8.. 7:&t;symmetric Pause Mode */
DECL|macro|PHY_M_P_ASYM_MD_X
mdefine_line|#define PHY_M_P_ASYM_MD_X&t;(2&lt;&lt;7)&t;/* Bit  8.. 7:&t;asymmetric Pause Mode */
DECL|macro|PHY_M_P_BOTH_MD_X
mdefine_line|#define PHY_M_P_BOTH_MD_X&t;(3&lt;&lt;7)&t;/* Bit  8.. 7:&t;both Pause Mode */
multiline_comment|/*****  PHY_MARV_1000T_CTRL&t;16 bit r/w&t;1000Base-T Control Reg *****/
DECL|macro|PHY_M_1000C_TEST
mdefine_line|#define PHY_M_1000C_TEST&t;(7&lt;&lt;13)&t;/* Bit 15..13:&t;Test Modes */
DECL|macro|PHY_M_1000C_MSE
mdefine_line|#define PHY_M_1000C_MSE&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Manual Master/Slave Enable */
DECL|macro|PHY_M_1000C_MSC
mdefine_line|#define PHY_M_1000C_MSC&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;M/S Configuration (1=Master) */
DECL|macro|PHY_M_1000C_MPD
mdefine_line|#define PHY_M_1000C_MPD&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Multi-Port Device */
DECL|macro|PHY_M_1000C_AFD
mdefine_line|#define PHY_M_1000C_AFD&t;&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Advertise Full Duplex */
DECL|macro|PHY_M_1000C_AHD
mdefine_line|#define PHY_M_1000C_AHD&t;&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Advertise Half Duplex */
multiline_comment|/* Bit  7..0:&t;reserved */
multiline_comment|/*****  PHY_MARV_PHY_CTRL&t;16 bit r/w&t;PHY Specific Ctrl Reg *****/
DECL|macro|PHY_M_PC_TX_FFD_MSK
mdefine_line|#define PHY_M_PC_TX_FFD_MSK&t;(3&lt;&lt;14)&t;/* Bit 15..14:&t;Tx FIFO Depth Mask */
DECL|macro|PHY_M_PC_RX_FFD_MSK
mdefine_line|#define PHY_M_PC_RX_FFD_MSK&t;(3&lt;&lt;12)&t;/* Bit 13..12:&t;Rx FIFO Depth Mask */
DECL|macro|PHY_M_PC_ASS_CRS_TX
mdefine_line|#define PHY_M_PC_ASS_CRS_TX&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Assert CRS on Transmit */
DECL|macro|PHY_M_PC_FL_GOOD
mdefine_line|#define PHY_M_PC_FL_GOOD&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Force Link Good */
DECL|macro|PHY_M_PC_EN_DET_MSK
mdefine_line|#define PHY_M_PC_EN_DET_MSK&t;(3&lt;&lt;8)&t;/* Bit  9.. 8:&t;Energy Detect Mask */
DECL|macro|PHY_M_PC_ENA_EXT_D
mdefine_line|#define PHY_M_PC_ENA_EXT_D&t;(1&lt;&lt;7)&t;/* Bit  7:&t;Enable Ext. Distance (10BT) */
DECL|macro|PHY_M_PC_MDIX_MSK
mdefine_line|#define PHY_M_PC_MDIX_MSK&t;(3&lt;&lt;5)&t;/* Bit  6.. 5:&t;MDI/MDIX Config. Mask */
DECL|macro|PHY_M_PC_DIS_125CLK
mdefine_line|#define PHY_M_PC_DIS_125CLK&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Disable 125 CLK */
DECL|macro|PHY_M_PC_MAC_POW_UP
mdefine_line|#define PHY_M_PC_MAC_POW_UP&t;(1&lt;&lt;3)&t;/* Bit  3:&t;MAC Power up */
DECL|macro|PHY_M_PC_SQE_T_ENA
mdefine_line|#define PHY_M_PC_SQE_T_ENA&t;(1&lt;&lt;2)&t;/* Bit  2:&t;SQE Test Enabled */
DECL|macro|PHY_M_PC_POL_R_DIS
mdefine_line|#define PHY_M_PC_POL_R_DIS&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Polarity Reversal Disabled */
DECL|macro|PHY_M_PC_DIS_JABBER
mdefine_line|#define PHY_M_PC_DIS_JABBER&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Disable Jabber */
DECL|macro|PHY_M_PC_MDI_XMODE
mdefine_line|#define PHY_M_PC_MDI_XMODE(x)&t;SHIFT5(x)&t;
DECL|macro|PHY_M_PC_MAN_MDI
mdefine_line|#define PHY_M_PC_MAN_MDI&t;0    &t;/* 00 = Manual MDI configuration */
DECL|macro|PHY_M_PC_MAN_MDIX
mdefine_line|#define PHY_M_PC_MAN_MDIX&t;1&t;&t;/* 01 = Manual MDIX configuration */
DECL|macro|PHY_M_PC_ENA_AUTO
mdefine_line|#define PHY_M_PC_ENA_AUTO&t;3&t;&t;/* 11 = Enable Automatic Crossover */
multiline_comment|/*****  PHY_MARV_PHY_STAT&t;16 bit r/o&t;PHY Specific Status Reg *****/
DECL|macro|PHY_M_PS_SPEED_MSK
mdefine_line|#define PHY_M_PS_SPEED_MSK&t;(3&lt;&lt;14)&t;/* Bit 15..14:&t;Speed Mask */
DECL|macro|PHY_M_PS_SPEED_1000
mdefine_line|#define PHY_M_PS_SPEED_1000&t;(1&lt;&lt;15)&t;/*       10 = 1000 Mbps */
DECL|macro|PHY_M_PS_SPEED_100
mdefine_line|#define PHY_M_PS_SPEED_100&t;(1&lt;&lt;14)&t;/*       01 =  100 Mbps */
DECL|macro|PHY_M_PS_SPEED_10
mdefine_line|#define PHY_M_PS_SPEED_10&t;0&t;&t;/*       00 =   10 Mbps */
DECL|macro|PHY_M_PS_FULL_DUP
mdefine_line|#define PHY_M_PS_FULL_DUP&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Full Duplex */
DECL|macro|PHY_M_PS_PAGE_REC
mdefine_line|#define PHY_M_PS_PAGE_REC&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Page Received */
DECL|macro|PHY_M_PS_SPDUP_RES
mdefine_line|#define PHY_M_PS_SPDUP_RES&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Speed &amp; Duplex Resolved */
DECL|macro|PHY_M_PS_LINK_UP
mdefine_line|#define PHY_M_PS_LINK_UP&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Link Up */
DECL|macro|PHY_M_PS_CABLE_MSK
mdefine_line|#define PHY_M_PS_CABLE_MSK&t;(3&lt;&lt;7)&t;/* Bit  9.. 7:&t;Cable Length Mask */
DECL|macro|PHY_M_PS_MDI_X_STAT
mdefine_line|#define PHY_M_PS_MDI_X_STAT&t;(1&lt;&lt;6)&t;/* Bit  6:&t;MDI Crossover Stat (1=MDIX) */
DECL|macro|PHY_M_PS_DOWNS_STAT
mdefine_line|#define PHY_M_PS_DOWNS_STAT&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Downshift Status (1=downsh.) */
DECL|macro|PHY_M_PS_ENDET_STAT
mdefine_line|#define PHY_M_PS_ENDET_STAT&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Energy Detect Status (1=act) */
DECL|macro|PHY_M_PS_TX_P_EN
mdefine_line|#define PHY_M_PS_TX_P_EN&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Tx Pause Enabled */
DECL|macro|PHY_M_PS_RX_P_EN
mdefine_line|#define PHY_M_PS_RX_P_EN&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Rx Pause Enabled */
DECL|macro|PHY_M_PS_POL_REV
mdefine_line|#define PHY_M_PS_POL_REV&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Polarity Reversed */
DECL|macro|PHY_M_PC_JABBER
mdefine_line|#define PHY_M_PC_JABBER&t;&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Jabber */
DECL|macro|PHY_M_PS_PAUSE_MSK
mdefine_line|#define PHY_M_PS_PAUSE_MSK&t;(PHY_M_PS_TX_P_EN | PHY_M_PS_RX_P_EN)
multiline_comment|/*****  PHY_MARV_INT_MASK&t;16 bit r/w&t;Interrupt Mask Reg *****/
multiline_comment|/*****  PHY_MARV_INT_STAT&t;16 bit r/o&t;Interrupt Status Reg *****/
DECL|macro|PHY_M_IS_AN_ERROR
mdefine_line|#define PHY_M_IS_AN_ERROR&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Auto-Negotiation Error */
DECL|macro|PHY_M_IS_LSP_CHANGE
mdefine_line|#define PHY_M_IS_LSP_CHANGE&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Link Speed Changed */
DECL|macro|PHY_M_IS_DUP_CHANGE
mdefine_line|#define PHY_M_IS_DUP_CHANGE&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Duplex Mode Changed */
DECL|macro|PHY_M_IS_AN_PR
mdefine_line|#define PHY_M_IS_AN_PR&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Page Received */
DECL|macro|PHY_M_IS_AN_COMPL
mdefine_line|#define PHY_M_IS_AN_COMPL&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Auto-Negotiation Completed */
DECL|macro|PHY_M_IS_LST_CHANGE
mdefine_line|#define PHY_M_IS_LST_CHANGE&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Link Status Changed */
DECL|macro|PHY_M_IS_SYMB_ERROR
mdefine_line|#define PHY_M_IS_SYMB_ERROR&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Symbol Error */
DECL|macro|PHY_M_IS_FALSE_CARR
mdefine_line|#define PHY_M_IS_FALSE_CARR&t;(1&lt;&lt;8)&t;/* Bit  8:&t;False Carrier */
DECL|macro|PHY_M_IS_FIFO_ERROR
mdefine_line|#define PHY_M_IS_FIFO_ERROR&t;(1&lt;&lt;7)&t;/* Bit  7:&t;FIFO Overflow/Underrun Error */
DECL|macro|PHY_M_IS_MDI_CHANGE
mdefine_line|#define PHY_M_IS_MDI_CHANGE&t;(1&lt;&lt;6)&t;/* Bit  6:&t;MDI Crossover Changed */
DECL|macro|PHY_M_IS_DOWNSH_DET
mdefine_line|#define PHY_M_IS_DOWNSH_DET&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Downshift Detected */
DECL|macro|PHY_M_IS_END_CHANGE
mdefine_line|#define PHY_M_IS_END_CHANGE&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Energy Detect Changed */
multiline_comment|/* Bit  3..2:&t;reserved */
DECL|macro|PHY_M_IS_POL_CHANGE
mdefine_line|#define PHY_M_IS_POL_CHANGE&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Polarity Changed */
DECL|macro|PHY_M_IS_JABBER
mdefine_line|#define PHY_M_IS_JABBER&t;&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Jabber */
DECL|macro|PHY_M_DEF_MSK
mdefine_line|#define PHY_M_DEF_MSK&t;&t;(PHY_M_IS_AN_ERROR | PHY_M_IS_AN_PR | &bslash;&n;&t;&t;&t;&t;&t;&t;&t;PHY_M_IS_LST_CHANGE | PHY_M_IS_FIFO_ERROR)
multiline_comment|/*****  PHY_MARV_EXT_CTRL&t;16 bit r/w&t;Ext. PHY Specific Ctrl *****/
DECL|macro|PHY_M_EC_M_DSC_MSK
mdefine_line|#define PHY_M_EC_M_DSC_MSK&t;(3&lt;&lt;10)&t;/* Bit 11..10:&t;Master downshift counter */
DECL|macro|PHY_M_EC_S_DSC_MSK
mdefine_line|#define PHY_M_EC_S_DSC_MSK&t;(3&lt;&lt;8)&t;/* Bit  9.. 8:&t;Slave  downshift counter */
DECL|macro|PHY_M_EC_MAC_S_MSK
mdefine_line|#define PHY_M_EC_MAC_S_MSK&t;(7&lt;&lt;4)&t;/* Bit  6.. 4:&t;Def. MAC interface speed */
DECL|macro|PHY_M_EC_M_DSC
mdefine_line|#define PHY_M_EC_M_DSC(x)&t;&t;SHIFT10(x)&t;/* 00=1x; 01=2x; 10=3x; 11=4x */
DECL|macro|PHY_M_EC_S_DSC
mdefine_line|#define PHY_M_EC_S_DSC(x)&t;&t;SHIFT8(x)&t;/* 00=dis; 01=1x; 10=2x; 11=3x */
DECL|macro|PHY_M_EC_MAC_S
mdefine_line|#define PHY_M_EC_MAC_S(x)&t;&t;SHIFT4(x)&t;/* 01X=0; 110=2.5; 111=25 (MHz) */
DECL|macro|MAC_TX_CLK_0_MHZ
mdefine_line|#define MAC_TX_CLK_0_MHZ&t;2
DECL|macro|MAC_TX_CLK_2_5_MHZ
mdefine_line|#define MAC_TX_CLK_2_5_MHZ&t;6
DECL|macro|MAC_TX_CLK_25_MHZ
mdefine_line|#define MAC_TX_CLK_25_MHZ&t;7
multiline_comment|/*****  PHY_MARV_LED_CTRL&t;16 bit r/w&t;LED Control Reg *****/
DECL|macro|PHY_M_LEDC_DIS_LED
mdefine_line|#define PHY_M_LEDC_DIS_LED&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Disable LED */
DECL|macro|PHY_M_LEDC_PULS_MSK
mdefine_line|#define PHY_M_LEDC_PULS_MSK&t;(7&lt;&lt;12)&t;/* Bit 14..12:  Pulse Stretch Mask */
DECL|macro|PHY_M_LEDC_F_INT
mdefine_line|#define PHY_M_LEDC_F_INT&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Force Interrupt */
DECL|macro|PHY_M_LEDC_BL_R_MSK
mdefine_line|#define PHY_M_LEDC_BL_R_MSK&t;(7&lt;&lt;8)&t;/* Bit 10.. 8:  Blink Rate Mask */
multiline_comment|/* Bit  7.. 5:&t;reserved */
DECL|macro|PHY_M_LEDC_LINK_MSK
mdefine_line|#define PHY_M_LEDC_LINK_MSK&t;(3&lt;&lt;3)&t;/* Bit  4.. 3:&t;Link Control Mask */
DECL|macro|PHY_M_LEDC_DP_CTRL
mdefine_line|#define PHY_M_LEDC_DP_CTRL&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Duplex Control */
DECL|macro|PHY_M_LEDC_RX_CTRL
mdefine_line|#define PHY_M_LEDC_RX_CTRL&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Rx activity / Link */
DECL|macro|PHY_M_LEDC_TX_CTRL
mdefine_line|#define PHY_M_LEDC_TX_CTRL&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Tx activity / Link */
DECL|macro|PHY_M_LED_PULS_DUR
mdefine_line|#define PHY_M_LED_PULS_DUR(x)&t;SHIFT12(x)&t;/* Pulse Stretch Duration */
DECL|macro|PULS_NO_STR
mdefine_line|#define&t;PULS_NO_STR&t;&t;0&t;&t;/* no pulse stretching */
DECL|macro|PULS_21MS
mdefine_line|#define&t;PULS_21MS&t;&t;1&t;&t;/* 21 ms to 42 ms */
DECL|macro|PULS_42MS
mdefine_line|#define PULS_42MS&t;&t;2&t;&t;/* 42 ms to 84 ms */
DECL|macro|PULS_84MS
mdefine_line|#define PULS_84MS&t;&t;3&t;&t;/* 84 ms to 170 ms */
DECL|macro|PULS_170MS
mdefine_line|#define PULS_170MS&t;&t;4&t;&t;/* 170 ms to 340 ms */
DECL|macro|PULS_340MS
mdefine_line|#define PULS_340MS&t;&t;5&t;&t;/* 340 ms to 670 ms */
DECL|macro|PULS_670MS
mdefine_line|#define PULS_670MS&t;&t;6&t;&t;/* 670 ms to 1.3 s */
DECL|macro|PULS_1300MS
mdefine_line|#define PULS_1300MS&t;&t;7&t;&t;/* 1.3 s to 2.7 s */
DECL|macro|PHY_M_LED_BLINK_RT
mdefine_line|#define PHY_M_LED_BLINK_RT(x)&t;SHIFT8(x)&t;/* Blink Rate */
DECL|macro|BLINK_42MS
mdefine_line|#define BLINK_42MS&t;&t;0&t;&t;/* 42 ms */
DECL|macro|BLINK_84MS
mdefine_line|#define BLINK_84MS&t;&t;1&t;&t;/* 84 ms */
DECL|macro|BLINK_170MS
mdefine_line|#define BLINK_170MS&t;&t;2&t;&t;/* 170 ms */
DECL|macro|BLINK_340MS
mdefine_line|#define BLINK_340MS&t;&t;3&t;&t;/* 340 ms */
DECL|macro|BLINK_670MS
mdefine_line|#define BLINK_670MS&t;&t;4&t;&t;/* 670 ms */
multiline_comment|/* values 5 - 7: reserved */
multiline_comment|/*****  PHY_MARV_LED_OVER&t;16 bit r/w&t;Manual LED Override Reg *****/
DECL|macro|PHY_M_LED_MO_DUP
mdefine_line|#define PHY_M_LED_MO_DUP(x)&t;&t;SHIFT10(x)&t;/* Bit 11..10:  Duplex */
DECL|macro|PHY_M_LED_MO_10
mdefine_line|#define PHY_M_LED_MO_10(x)&t;&t;SHIFT8(x)&t;/* Bit  9.. 8:  Link 10 */
DECL|macro|PHY_M_LED_MO_100
mdefine_line|#define PHY_M_LED_MO_100(x)&t;&t;SHIFT6(x)&t;/* Bit  7.. 6:  Link 100 */
DECL|macro|PHY_M_LED_MO_1000
mdefine_line|#define PHY_M_LED_MO_1000(x)&t;SHIFT4(x)&t;/* Bit  5.. 4:  Link 1000 */
DECL|macro|PHY_M_LED_MO_RX
mdefine_line|#define PHY_M_LED_MO_RX(x)&t;&t;SHIFT2(x)&t;/* Bit  3.. 2:  Rx */
DECL|macro|PHY_M_LED_MO_TX
mdefine_line|#define PHY_M_LED_MO_TX(x)&t;&t;SHIFT0(x)&t;/* Bit  1.. 0:  Tx */
DECL|macro|MO_LED_NORM
mdefine_line|#define MO_LED_NORM&t;&t;&t;0
DECL|macro|MO_LED_BLINK
mdefine_line|#define MO_LED_BLINK&t;&t;1
DECL|macro|MO_LED_OFF
mdefine_line|#define MO_LED_OFF&t;&t;&t;2
DECL|macro|MO_LED_ON
mdefine_line|#define MO_LED_ON&t;&t;&t;3
multiline_comment|/*****  PHY_MARV_EXT_CTRL_2&t;16 bit r/w&t;Ext. PHY Specific Ctrl 2 *****/
multiline_comment|/* Bit 15.. 7:&t;reserved */
DECL|macro|PHY_M_EC2_FI_IMPED
mdefine_line|#define PHY_M_EC2_FI_IMPED&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Fiber Input  Impedance */
DECL|macro|PHY_M_EC2_FO_IMPED
mdefine_line|#define PHY_M_EC2_FO_IMPED&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Fiber Output Impedance */
DECL|macro|PHY_M_EC2_FO_M_CLK
mdefine_line|#define PHY_M_EC2_FO_M_CLK&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Fiber Mode Clock Enable */
DECL|macro|PHY_M_EC2_FO_BOOST
mdefine_line|#define PHY_M_EC2_FO_BOOST&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Fiber Output Boost */
DECL|macro|PHY_M_EC2_FO_AM_MSK
mdefine_line|#define PHY_M_EC2_FO_AM_MSK&t;7&t;&t;/* Bit  2.. 0:&t;Fiber Output Amplitude */
multiline_comment|/*****  PHY_MARV_CABLE_DIAG&t;16 bit r/o&t;Cable Diagnostic Reg *****/
DECL|macro|PHY_M_CABD_ENA_TEST
mdefine_line|#define PHY_M_CABD_ENA_TEST&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Enable Test */
DECL|macro|PHY_M_CABD_STAT_MSK
mdefine_line|#define PHY_M_CABD_STAT_MSK&t;(3&lt;&lt;13)&t;/* Bit 14..13:&t;Status */
multiline_comment|/* Bit 12.. 8:&t;reserved */
DECL|macro|PHY_M_CABD_DIST_MSK
mdefine_line|#define PHY_M_CABD_DIST_MSK&t;0xff&t;/* Bit  7.. 0:&t;Distance */
multiline_comment|/* values for Cable Diagnostic Status (11=fail; 00=OK; 10=open; 01=short) */
DECL|macro|CABD_STAT_NORMAL
mdefine_line|#define CABD_STAT_NORMAL&t;0
DECL|macro|CABD_STAT_SHORT
mdefine_line|#define CABD_STAT_SHORT&t;&t;1
DECL|macro|CABD_STAT_OPEN
mdefine_line|#define CABD_STAT_OPEN&t;&t;2
DECL|macro|CABD_STAT_FAIL
mdefine_line|#define CABD_STAT_FAIL&t;&t;3
multiline_comment|/*&n; * GMAC registers&n; *&n; * The GMAC registers are 16 or 32 bits wide.&n; * The GMACs host processor interface is 16 bits wide,&n; * therefore ALL registers will be addressed with 16 bit accesses.&n; *&n; * The following macros are provided to access the GMAC registers&n; * GM_IN16(), GM_OUT16, GM_IN32(), GM_OUT32(), GM_INADR(), GM_OUTADR(),&n; * GM_INHASH(), and GM_OUTHASH().&n; * The macros are defined in SkGeHw.h.&n; *&n; * Note:&t;NA reg&t;= Network Address e.g DA, SA etc.&n; *&n; */
multiline_comment|/* Port Registers */
DECL|macro|GM_GP_STAT
mdefine_line|#define GM_GP_STAT&t;&t;0x0000&t;&t;/* 16 bit r/o&t;General Purpose Status */
DECL|macro|GM_GP_CTRL
mdefine_line|#define GM_GP_CTRL&t;&t;0x0004&t;&t;/* 16 bit r/w&t;General Purpose Control */
DECL|macro|GM_TX_CTRL
mdefine_line|#define GM_TX_CTRL&t;&t;0x0008&t;&t;/* 16 bit r/w&t;Transmit Control Reg. */
DECL|macro|GM_RX_CTRL
mdefine_line|#define GM_RX_CTRL&t;&t;0x000c&t;&t;/* 16 bit r/w&t;Receive Control Reg. */
DECL|macro|GM_TX_FLOW_CTRL
mdefine_line|#define GM_TX_FLOW_CTRL&t;0x0010&t;&t;/* 16 bit r/w&t;Transmit Flow-Control */
DECL|macro|GM_TX_PARAM
mdefine_line|#define GM_TX_PARAM&t;&t;0x0014&t;&t;/* 16 bit r/w&t;Transmit Parameter Reg. */
DECL|macro|GM_SERIAL_MODE
mdefine_line|#define GM_SERIAL_MODE&t;0x0018&t;&t;/* 16 bit r/w&t;Serial Mode Register */
multiline_comment|/* Source Address Registers */
DECL|macro|GM_SRC_ADDR_1L
mdefine_line|#define GM_SRC_ADDR_1L&t;0x001c&t;&t;/* 16 bit r/w&t;Source Address 1 (low) */
DECL|macro|GM_SRC_ADDR_1M
mdefine_line|#define GM_SRC_ADDR_1M&t;0x0020&t;&t;/* 16 bit r/w&t;Source Address 1 (middle) */
DECL|macro|GM_SRC_ADDR_1H
mdefine_line|#define GM_SRC_ADDR_1H&t;0x0024&t;&t;/* 16 bit r/w&t;Source Address 1 (high) */
DECL|macro|GM_SRC_ADDR_2L
mdefine_line|#define GM_SRC_ADDR_2L&t;0x0028&t;&t;/* 16 bit r/w&t;Source Address 2 (low) */
DECL|macro|GM_SRC_ADDR_2M
mdefine_line|#define GM_SRC_ADDR_2M&t;0x002c&t;&t;/* 16 bit r/w&t;Source Address 2 (middle) */
DECL|macro|GM_SRC_ADDR_2H
mdefine_line|#define GM_SRC_ADDR_2H&t;0x0030&t;&t;/* 16 bit r/w&t;Source Address 2 (high) */
multiline_comment|/* Multicast Address Hash Registers */
DECL|macro|GM_MC_ADDR_H1
mdefine_line|#define GM_MC_ADDR_H1&t;0x0034&t;&t;/* 16 bit r/w&t;Multicast Address Hash 1 */
DECL|macro|GM_MC_ADDR_H2
mdefine_line|#define GM_MC_ADDR_H2&t;0x0038&t;&t;/* 16 bit r/w&t;Multicast Address Hash 2 */
DECL|macro|GM_MC_ADDR_H3
mdefine_line|#define GM_MC_ADDR_H3&t;0x003c&t;&t;/* 16 bit r/w&t;Multicast Address Hash 3 */
DECL|macro|GM_MC_ADDR_H4
mdefine_line|#define GM_MC_ADDR_H4&t;0x0040&t;&t;/* 16 bit r/w&t;Multicast Address Hash 4 */
multiline_comment|/* Interrupt Source Registers */
DECL|macro|GM_TX_IRQ_SRC
mdefine_line|#define GM_TX_IRQ_SRC&t;0x0044&t;&t;/* 16 bit r/o&t;Tx Overflow IRQ Source */
DECL|macro|GM_RX_IRQ_SRC
mdefine_line|#define GM_RX_IRQ_SRC&t;0x0048&t;&t;/* 16 bit r/o&t;Rx Overflow IRQ Source */
DECL|macro|GM_TR_IRQ_SRC
mdefine_line|#define GM_TR_IRQ_SRC&t;0x004c&t;&t;/* 16 bit r/o&t;Tx/Rx Over. IRQ Source */
multiline_comment|/* Interrupt Mask Registers */
DECL|macro|GM_TX_IRQ_MSK
mdefine_line|#define GM_TX_IRQ_MSK&t;0x0050&t;&t;/* 16 bit r/w&t;Tx Overflow IRQ Mask */
DECL|macro|GM_RX_IRQ_MSK
mdefine_line|#define GM_RX_IRQ_MSK&t;0x0054&t;&t;/* 16 bit r/w&t;Rx Overflow IRQ Mask */
DECL|macro|GM_TR_IRQ_MSK
mdefine_line|#define GM_TR_IRQ_MSK&t;0x0058&t;&t;/* 16 bit r/w&t;Tx/Rx Over. IRQ Mask */
multiline_comment|/* Serial Management Interface (SMI) Registers */
DECL|macro|GM_SMI_CTRL
mdefine_line|#define GM_SMI_CTRL&t;&t;0x0080&t;&t;/* 16 bit r/w&t;SMI Control Register */
DECL|macro|GM_SMI_DATA
mdefine_line|#define GM_SMI_DATA&t;&t;0x0084&t;&t;/* 16 bit r/w&t;SMI Data Register */
DECL|macro|GM_PHY_ADDR
mdefine_line|#define GM_PHY_ADDR&t;&t;0x0088&t;&t;/* 16 bit r/w&t;GPHY Address Register */
multiline_comment|/* MIB Counters */
DECL|macro|GM_MIB_CNT_BASE
mdefine_line|#define GM_MIB_CNT_BASE&t;0x0100&t;&t;/* Base Address of MIB Counters */
DECL|macro|GM_MIB_CNT_SIZE
mdefine_line|#define GM_MIB_CNT_SIZE&t;44&t;&t;&t;/* Number of MIB Counters */
multiline_comment|/*&n; * MIB Counters base address definitions (low word) -&n; * use offset 4 for access to high word&t;(32 bit r/o)&n; */
DECL|macro|GM_RXF_UC_OK
mdefine_line|#define GM_RXF_UC_OK &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 0)&t;/* Unicast Frames Received OK */
DECL|macro|GM_RXF_BC_OK
mdefine_line|#define GM_RXF_BC_OK &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 8)&t;/* Broadcast Frames Received OK */
DECL|macro|GM_RXF_MPAUSE
mdefine_line|#define GM_RXF_MPAUSE &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 16)&t;/* Pause MAC Ctrl Frames Received */
DECL|macro|GM_RXF_MC_OK
mdefine_line|#define GM_RXF_MC_OK &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 24)&t;/* Multicast Frames Received OK */
DECL|macro|GM_RXF_FCS_ERR
mdefine_line|#define GM_RXF_FCS_ERR &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 32)&t;/* Rx Frame Check Seq. Error */
multiline_comment|/* GM_MIB_CNT_BASE + 40:&t;reserved */
DECL|macro|GM_RXO_OK_LO
mdefine_line|#define GM_RXO_OK_LO &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 48)&t;/* Octets Received OK Low */
DECL|macro|GM_RXO_OK_HI
mdefine_line|#define GM_RXO_OK_HI &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 56)&t;/* Octets Received OK High */
DECL|macro|GM_RXO_ERR_LO
mdefine_line|#define GM_RXO_ERR_LO &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 64)&t;/* Octets Received Invalid Low */
DECL|macro|GM_RXO_ERR_HI
mdefine_line|#define GM_RXO_ERR_HI &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 72)&t;/* Octets Received Invalid High */
DECL|macro|GM_RXF_SHT
mdefine_line|#define GM_RXF_SHT &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 80)&t;/* Frames &lt;64 Byte Received OK */
DECL|macro|GM_RXE_FRAG
mdefine_line|#define GM_RXE_FRAG &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 88)&t;/* Frames &lt;64 Byte Receeived with FCS Err */
DECL|macro|GM_RXF_64B
mdefine_line|#define GM_RXF_64B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 96)&t;/* 64 Byte Rx Frame */
DECL|macro|GM_RXF_127B
mdefine_line|#define GM_RXF_127B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 104)&t;/* 65-127 Byte Rx Frame */
DECL|macro|GM_RXF_255B
mdefine_line|#define GM_RXF_255B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 112)&t;/* 128-255 Byte Rx Frame */
DECL|macro|GM_RXF_511B
mdefine_line|#define GM_RXF_511B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 120)&t;/* 256-511 Byte Rx Frame */
DECL|macro|GM_RXF_1023B
mdefine_line|#define GM_RXF_1023B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 128)&t;/* 512-1023 Byte Rx Frame */
DECL|macro|GM_RXF_1518B
mdefine_line|#define GM_RXF_1518B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 136)&t;/* 1024-1518 Byte Rx Frame */
DECL|macro|GM_RXF_MAX_SZ
mdefine_line|#define GM_RXF_MAX_SZ &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 144)&t;/* 1519-MaxSize Byte Rx Frame */
DECL|macro|GM_RXF_LNG_ERR
mdefine_line|#define GM_RXF_LNG_ERR &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 152)&t;/* Rx Frame too Long Error */
DECL|macro|GM_RXF_JAB_PKT
mdefine_line|#define GM_RXF_JAB_PKT &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 160)&t;/* Rx Jabber Packet Frame */
multiline_comment|/* GM_MIB_CNT_BASE + 168:&t;reserved */
DECL|macro|GM_RXE_FIFO_OV
mdefine_line|#define GM_RXE_FIFO_OV &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 176)&t;/* Rx FIFO overflow Event */
multiline_comment|/* GM_MIB_CNT_BASE + 184:&t;reserved */
DECL|macro|GM_TXF_UC_OK
mdefine_line|#define GM_TXF_UC_OK &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 192)&t;/* Unicast Frames Xmitted OK */
DECL|macro|GM_TXF_BC_OK
mdefine_line|#define GM_TXF_BC_OK &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 200)&t;/* Broadcast Frames Xmitted OK */
DECL|macro|GM_TXF_MPAUSE
mdefine_line|#define GM_TXF_MPAUSE &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 208)&t;/* Pause MAC Ctrl Frames Xmitted */
DECL|macro|GM_TXF_MC_OK
mdefine_line|#define GM_TXF_MC_OK &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 216)&t;/* Multicast Frames Xmitted OK */
DECL|macro|GM_TXO_OK_LO
mdefine_line|#define GM_TXO_OK_LO &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 224)&t;/* Octets Transmitted OK Low */
DECL|macro|GM_TXO_OK_HI
mdefine_line|#define GM_TXO_OK_HI &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 232)&t;/* Octets Transmitted OK High */
DECL|macro|GM_TXF_64B
mdefine_line|#define GM_TXF_64B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 240)&t;/* 64 Byte Tx Frame */
DECL|macro|GM_TXF_127B
mdefine_line|#define GM_TXF_127B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 248)&t;/* 65-127 Byte Tx Frame */
DECL|macro|GM_TXF_255B
mdefine_line|#define GM_TXF_255B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 256)&t;/* 128-255 Byte Tx Frame */
DECL|macro|GM_TXF_511B
mdefine_line|#define GM_TXF_511B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 264)&t;/* 256-511 Byte Tx Frame */
DECL|macro|GM_TXF_1023B
mdefine_line|#define GM_TXF_1023B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 272)&t;/* 512-1023 Byte Tx Frame */
DECL|macro|GM_TXF_1518B
mdefine_line|#define GM_TXF_1518B &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 280)&t;/* 1024-1518 Byte Tx Frame */
DECL|macro|GM_TXF_MAX_SZ
mdefine_line|#define GM_TXF_MAX_SZ &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 288)&t;/* 1519-MaxSize Byte Tx Frame */
multiline_comment|/* GM_MIB_CNT_BASE + 296:&t;reserved */
DECL|macro|GM_TXF_COL
mdefine_line|#define GM_TXF_COL &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 304)&t;/* Tx Collision */
DECL|macro|GM_TXF_LAT_COL
mdefine_line|#define GM_TXF_LAT_COL &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 312)&t;/* Tx Late Collision */
DECL|macro|GM_TXF_ABO_COL
mdefine_line|#define GM_TXF_ABO_COL &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 320)&t;/* Tx aborted due to Exces. Col. */
DECL|macro|GM_TXF_MUL_COL
mdefine_line|#define GM_TXF_MUL_COL &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 328)&t;/* Tx Multiple Collision */
DECL|macro|GM_TXF_SNG_COL
mdefine_line|#define GM_TXF_SNG_COL &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 336)&t;/* Tx Single Collision */
DECL|macro|GM_TXE_FIFO_UR
mdefine_line|#define GM_TXE_FIFO_UR &bslash;&n;&t;&t;&t;(GM_MIB_CNT_BASE + 344)&t;/* Tx FIFO Underrun Event */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * GMAC Bit Definitions&n; *&n; * If the bit access behaviour differs from the register access behaviour&n; * (r/w, r/o) this is documented after the bit number.&n; * The following bit access behaviours are used:&n; *&t;(sc)&t;self clearing&n; *&t;(r/o)&t;read only&n; */
multiline_comment|/*&t;GM_GP_STAT&t;16 bit r/o&t;General Purpose Status Register */
DECL|macro|GM_GPSR_SPEED
mdefine_line|#define GM_GPSR_SPEED&t;&t;(1&lt;&lt;15) /* Bit 15:&t;Port Speed (1 = 100 Mbps) */
DECL|macro|GM_GPSR_DUPLEX
mdefine_line|#define GM_GPSR_DUPLEX&t;&t;(1&lt;&lt;14) /* Bit 14:&t;Duplex Mode (1 = Full) */
DECL|macro|GM_GPSR_FC_TX_DIS
mdefine_line|#define GM_GPSR_FC_TX_DIS&t;(1&lt;&lt;13) /* Bit 13:&t;Tx Flow-Control Mode Disabled */
DECL|macro|GM_GPSR_LINK_UP
mdefine_line|#define GM_GPSR_LINK_UP&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Link Up Status */
DECL|macro|GM_GPSR_PAUSE
mdefine_line|#define GM_GPSR_PAUSE&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Pause State */
DECL|macro|GM_GPSR_TX_ACTIVE
mdefine_line|#define GM_GPSR_TX_ACTIVE&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Tx in Progress */
DECL|macro|GM_GPSR_EXC_COL
mdefine_line|#define GM_GPSR_EXC_COL&t;&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Excessive Collisions Occured */
DECL|macro|GM_GPSR_LAT_COL
mdefine_line|#define GM_GPSR_LAT_COL&t;&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Late Collisions Occured */
multiline_comment|/* Bit  7..6:&t;reserved */
DECL|macro|GM_GPSR_PHY_ST_CH
mdefine_line|#define GM_GPSR_PHY_ST_CH&t;(1&lt;&lt;5)&t;/* Bit  5:&t;PHY Status Change */
DECL|macro|GM_GPSR_GIG_SPEED
mdefine_line|#define GM_GPSR_GIG_SPEED&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Gigabit Speed (1 = 1000 Mbps) */
DECL|macro|GM_GPSR_PART_MODE
mdefine_line|#define GM_GPSR_PART_MODE&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Partition mode */
DECL|macro|GM_GPSR_FC_RX_DIS
mdefine_line|#define GM_GPSR_FC_RX_DIS&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Rx Flow-Control Mode Disabled */
DECL|macro|GM_GPSR_PROM_EN
mdefine_line|#define GM_GPSR_PROM_EN&t;&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Promiscuous Mode Enabled */
multiline_comment|/* Bit  0:&t;reserved */
multiline_comment|/*&t;GM_GP_CTRL&t;16 bit r/w&t;General Purpose Control Register */
multiline_comment|/* Bit 15:&t;reserved */
DECL|macro|GM_GPCR_PROM_ENA
mdefine_line|#define GM_GPCR_PROM_ENA&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Enable Promiscuous Mode */
DECL|macro|GM_GPCR_FC_TX_DIS
mdefine_line|#define GM_GPCR_FC_TX_DIS&t;(1&lt;&lt;13) /* Bit 13:&t;Disable Tx Flow-Control Mode */
DECL|macro|GM_GPCR_TX_ENA
mdefine_line|#define GM_GPCR_TX_ENA&t;&t;(1&lt;&lt;12) /* Bit 12:&t;Enable Transmit */
DECL|macro|GM_GPCR_RX_ENA
mdefine_line|#define GM_GPCR_RX_ENA&t;&t;(1&lt;&lt;11) /* Bit 11:&t;Enable Receive */
DECL|macro|GM_GPCR_BURST_ENA
mdefine_line|#define GM_GPCR_BURST_ENA&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Enable Burst Mode */
DECL|macro|GM_GPCR_LOOP_ENA
mdefine_line|#define GM_GPCR_LOOP_ENA&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Enable MAC Loopback Mode */
DECL|macro|GM_GPCR_PART_ENA
mdefine_line|#define GM_GPCR_PART_ENA&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Enable Partition Mode */
DECL|macro|GM_GPCR_GIGS_ENA
mdefine_line|#define GM_GPCR_GIGS_ENA&t;(1&lt;&lt;7)&t;/* Bit  7:&t;Gigabit Speed (1000 Mbps) */
DECL|macro|GM_GPCR_FL_PASS
mdefine_line|#define GM_GPCR_FL_PASS&t;&t;(1&lt;&lt;6)&t;/* Bit  6:&t;Force Link Pass */
DECL|macro|GM_GPCR_DUP_FULL
mdefine_line|#define GM_GPCR_DUP_FULL&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Full Duplex Mode */
DECL|macro|GM_GPCR_FC_RX_DIS
mdefine_line|#define GM_GPCR_FC_RX_DIS&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Disable Rx Flow-Control Mode */
DECL|macro|GM_GPCR_SPEED_100
mdefine_line|#define GM_GPCR_SPEED_100&t;(1&lt;&lt;3)  /* Bit  3:&t;Port Speed 100 Mbps */
DECL|macro|GM_GPCR_AU_DUP_DIS
mdefine_line|#define GM_GPCR_AU_DUP_DIS&t;(1&lt;&lt;2)&t;/* Bit  2:&t;Disable Auto-Update Duplex */
DECL|macro|GM_GPCR_AU_FCT_DIS
mdefine_line|#define GM_GPCR_AU_FCT_DIS&t;(1&lt;&lt;1)&t;/* Bit  1:&t;Disable Auto-Update Flow-C. */
DECL|macro|GM_GPCR_AU_SPD_DIS
mdefine_line|#define GM_GPCR_AU_SPD_DIS&t;(1&lt;&lt;0)&t;/* Bit  0:&t;Disable Auto-Update Speed */
DECL|macro|GM_GPCR_SPEED_1000
mdefine_line|#define GM_GPCR_SPEED_1000&t;(GM_GPCR_GIGS_ENA | GM_GPCR_SPEED_100)
DECL|macro|GM_GPCR_AU_ALL_DIS
mdefine_line|#define GM_GPCR_AU_ALL_DIS&t;(GM_GPCR_AU_DUP_DIS | GM_GPCR_AU_FCT_DIS |&bslash;&n;&t;&t;&t;&t;&t;&t;&t; GM_GPCR_AU_SPD_DIS)
multiline_comment|/*&t;GM_TX_CTRL&t;&t;&t;&t;16 bit r/w&t;Transmit Control Register */
DECL|macro|GM_TXCR_FORCE_JAM
mdefine_line|#define GM_TXCR_FORCE_JAM&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Force Jam / Flow-Control */
DECL|macro|GM_TXCR_CRC_DIS
mdefine_line|#define GM_TXCR_CRC_DIS&t;&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Disable insertion of CRC */
DECL|macro|GM_TXCR_PAD_DIS
mdefine_line|#define GM_TXCR_PAD_DIS&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Disable padding of packets */
DECL|macro|GM_TXCR_COL_THR
mdefine_line|#define GM_TXCR_COL_THR&t;&t;(4&lt;&lt;10)&t;/* Bit 12..10:&t;Collision Threshold */
multiline_comment|/*&t;GM_RX_CTRL&t;&t;&t;&t;16 bit r/w&t;Receive Control Register */
DECL|macro|GM_RXCR_UCF_ENA
mdefine_line|#define GM_RXCR_UCF_ENA&t;&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Enable Unicast filtering */
DECL|macro|GM_RXCR_MCF_ENA
mdefine_line|#define GM_RXCR_MCF_ENA&t;&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Enable Multicast filtering */
DECL|macro|GM_RXCR_CRC_DIS
mdefine_line|#define GM_RXCR_CRC_DIS&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Remove 4-byte CRC */
DECL|macro|GM_RXCR_PASS_FC
mdefine_line|#define GM_RXCR_PASS_FC&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Pass FC packets to FIFO */
multiline_comment|/*&t;GM_TX_PARAM&t;&t;&t;&t;16 bit r/w&t;Transmit Parameter Register */
DECL|macro|GM_TXPA_JAMLEN_MSK
mdefine_line|#define GM_TXPA_JAMLEN_MSK&t;(0x03&lt;&lt;14)&t;/* Bit 15..14:&t;Jam Length */
DECL|macro|GM_TXPA_JAMIPG_MSK
mdefine_line|#define GM_TXPA_JAMIPG_MSK&t;(0x1f&lt;&lt;9)&t;/* Bit 13..9:&t;Jam IPG */
DECL|macro|GM_TXPA_JAMDAT_MSK
mdefine_line|#define GM_TXPA_JAMDAT_MSK&t;(0x1f&lt;&lt;4)&t;/* Bit  8..4:&t;IPG Jam to Data */
multiline_comment|/* Bit  3..0:&t;reserved */
DECL|macro|JAM_LEN_VAL
mdefine_line|#define JAM_LEN_VAL(x)&t;&t;SHIFT14(x)
DECL|macro|JAM_IPG_VAL
mdefine_line|#define JAM_IPG_VAL(x)&t;&t;SHIFT9(x)
DECL|macro|IPG_JAM_DATA
mdefine_line|#define IPG_JAM_DATA(x)&t;&t;SHIFT4(x)
multiline_comment|/*&t;GM_SERIAL_MODE&t;&t;&t;16 bit r/w&t;Serial Mode Register */
DECL|macro|GM_SMOD_DATABL_MSK
mdefine_line|#define GM_SMOD_DATABL_MSK&t;(0x1f&lt;&lt;11)&t;/* Bit 15..11:&t;Data Blinder */
DECL|macro|GM_SMOD_LIMIT_4
mdefine_line|#define GM_SMOD_LIMIT_4&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;4 consecutive Tx trials */
DECL|macro|GM_SMOD_VLAN_ENA
mdefine_line|#define GM_SMOD_VLAN_ENA&t;(1&lt;&lt;9)&t;/* Bit  9:&t;Enable VLAN  (Max. Frame Len) */
DECL|macro|GM_SMOD_JUMBO_ENA
mdefine_line|#define GM_SMOD_JUMBO_ENA&t;(1&lt;&lt;8)&t;/* Bit  8:&t;Enable Jumbo (Max. Frame Len) */
multiline_comment|/* Bit  7..5:&t;reserved */
DECL|macro|GM_SMOD_IPG_MSK
mdefine_line|#define GM_SMOD_IPG_MSK&t;&t;0x1f&t;/* Bit 4..0:&t;Inter-Packet Gap (IPG) */
DECL|macro|DATA_BLIND_VAL
mdefine_line|#define DATA_BLIND_VAL(x)&t;SHIFT11(x)
DECL|macro|DATA_BLIND_FAST_ETH
mdefine_line|#define DATA_BLIND_FAST_ETH&t;0x1c
DECL|macro|DATA_BLIND_GIGABIT
mdefine_line|#define DATA_BLIND_GIGABIT&t;4
DECL|macro|IPG_VAL_FAST_ETH
mdefine_line|#define IPG_VAL_FAST_ETH&t;0x1e
DECL|macro|IPG_VAL_GIGABIT
mdefine_line|#define IPG_VAL_GIGABIT&t;&t;6
multiline_comment|/*&t;GM_SMI_CTRL&t;&t;&t;&t;16 bit r/w&t;SMI Control Register */
DECL|macro|GM_SMI_CT_PHY_AD
mdefine_line|#define GM_SMI_CT_PHY_AD(x)&t;SHIFT11(x)
DECL|macro|GM_SMI_CT_REG_AD
mdefine_line|#define GM_SMI_CT_REG_AD(x)&t;SHIFT6(x)
DECL|macro|GM_SMI_CT_OP_RD
mdefine_line|#define GM_SMI_CT_OP_RD&t;&t;(1&lt;&lt;5)&t;/* Bit  5:&t;OpCode Read (0=Write)*/
DECL|macro|GM_SMI_CT_RD_VAL
mdefine_line|#define GM_SMI_CT_RD_VAL&t;(1&lt;&lt;4)&t;/* Bit  4:&t;Read Valid (Read completed) */
DECL|macro|GM_SMI_CT_BUSY
mdefine_line|#define GM_SMI_CT_BUSY&t;&t;(1&lt;&lt;3)&t;/* Bit  3:&t;Busy (Operation in progress) */
multiline_comment|/* Bit   2..0:&t;reserved */
multiline_comment|/*&t;GM_PHY_ADDR&t;&t;&t;&t;16 bit r/w&t;GPHY Address Register */
multiline_comment|/* Bit  15..6:&t;reserved */
DECL|macro|GM_PAR_MIB_CLR
mdefine_line|#define GM_PAR_MIB_CLR&t;&t;(1&lt;&lt;5)&t;/* Bit  5:&t;Set MIB Clear Counter Mode */
DECL|macro|GM_PAR_MIB_TST
mdefine_line|#define GM_PAR_MIB_TST&t;&t;(1&lt;&lt;4)&t;/* Bit  4:&t;MIB Load Counter (Test Mode) */
multiline_comment|/* Bit   3..0:&t;reserved */
multiline_comment|/* Receive Frame Status Encoding */
DECL|macro|GMR_FS_LEN
mdefine_line|#define GMR_FS_LEN&t;(0xffffUL&lt;&lt;16)&t;/* Bit 31..16:&t;Rx Frame Length */
multiline_comment|/* Bit  15..14:&t;reserved */
DECL|macro|GMR_FS_VLAN
mdefine_line|#define GMR_FS_VLAN&t;&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;VLAN Packet */
DECL|macro|GMR_FS_JABBER
mdefine_line|#define GMR_FS_JABBER&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Jabber Packet */
DECL|macro|GMR_FS_UN_SIZE
mdefine_line|#define GMR_FS_UN_SIZE&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Undersize Packet */
DECL|macro|GMR_FS_MC
mdefine_line|#define GMR_FS_MC&t;&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Multicast Packet */
DECL|macro|GMR_FS_BC
mdefine_line|#define GMR_FS_BC&t;&t;(1L&lt;&lt;9)&t;&t;/* Bit  9:&t;Broadcast Packet */
DECL|macro|GMR_FS_RX_OK
mdefine_line|#define GMR_FS_RX_OK&t;(1L&lt;&lt;8)&t;&t;/* Bit  8:&t;Receive OK (Good Packet) */
DECL|macro|GMR_FS_GOOD_FC
mdefine_line|#define GMR_FS_GOOD_FC&t;(1L&lt;&lt;7)&t;&t;/* Bit  7:&t;Good Flow-Control Packet */
DECL|macro|GMR_FS_BAD_FC
mdefine_line|#define GMR_FS_BAD_FC&t;(1L&lt;&lt;6)&t;&t;/* Bit  6:&t;Bad  Flow-Control Packet */
DECL|macro|GMR_FS_MII_ERR
mdefine_line|#define GMR_FS_MII_ERR&t;(1L&lt;&lt;5)&t;&t;/* Bit  5:&t;MII Error */
DECL|macro|GMR_FS_LONG_ERR
mdefine_line|#define GMR_FS_LONG_ERR&t;(1L&lt;&lt;4)&t;&t;/* Bit  4:&t;Too Long Packet */
DECL|macro|GMR_FS_FRAGMENT
mdefine_line|#define GMR_FS_FRAGMENT&t;(1L&lt;&lt;3)&t;&t;/* Bit  3:&t;Fragment */
multiline_comment|/* Bit  2:&t;reserved */
DECL|macro|GMR_FS_CRC_ERR
mdefine_line|#define GMR_FS_CRC_ERR&t;(1L&lt;&lt;1)&t;&t;/* Bit  1:&t;CRC Error */
DECL|macro|GMR_FS_RX_FF_OV
mdefine_line|#define GMR_FS_RX_FF_OV&t;(1L&lt;&lt;0)&t;&t;/* Bit  0:&t;Rx FIFO Overflow */
multiline_comment|/*&n; * GMR_FS_ANY_ERR (analogous to XMR_FS_ANY_ERR)&n; */
DECL|macro|GMR_FS_ANY_ERR
mdefine_line|#define GMR_FS_ANY_ERR&t;(GMR_FS_CRC_ERR | &bslash;&n;&t;&t;&t;GMR_FS_LONG_ERR | &bslash;&n;&t;&t;&t;GMR_FS_MII_ERR | &bslash;&n;&t;&t;&t;GMR_FS_BAD_FC | &bslash;&n;&t;&t;&t;GMR_FS_GOOD_FC | &bslash;&n;&t;&t;&t;GMR_FS_JABBER)
multiline_comment|/* Rx GMAC FIFO Flush Mask (default) */
DECL|macro|RX_FF_FL_DEF_MSK
mdefine_line|#define RX_FF_FL_DEF_MSK&t;(GMR_FS_CRC_ERR | &bslash;&n;&t;&t;&t;GMR_FS_RX_FF_OV | &bslash;&n;&t;&t;&t;GMR_FS_MII_ERR | &bslash;&n;&t;&t;&t;GMR_FS_BAD_FC | &bslash;&n;&t;&t;&t;GMR_FS_GOOD_FC | &bslash;&n;&t;&t;&t;GMR_FS_UN_SIZE | &bslash;&n;&t;&t;&t;GMR_FS_JABBER)
multiline_comment|/* typedefs *******************************************************************/
multiline_comment|/* function prototypes ********************************************************/
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif&t;/* __cplusplus */
macro_line|#endif&t;/* __INC_XMAC_H */
eof
