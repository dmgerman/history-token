multiline_comment|/******************************************************************************&n; *&n; * Name:&t;xmac_ii.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.27 $&n; * Date:&t;$Date: 2000/05/17 11:00:46 $&n; * Purpose:&t;Defines and Macros for XaQti&squot;s Gigabit Ethernet Controller&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: xmac_ii.h,v $&n; *&t;Revision 1.27  2000/05/17 11:00:46  malthoff&n; *&t;Add bit for enable/disable power management in BCOM chip.&n; *&t;&n; *&t;Revision 1.26  1999/11/22 14:03:00  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.25  1999/08/12 19:19:38  malthoff&n; *&t;Add PHY_B_AC_TX_TST bit according to BCOM A1 errata sheet.&n; *&t;&n; *&t;Revision 1.24  1999/07/30 11:27:21  cgoos&n; *&t;Fixed a missing end-of-comment.&n; *&t;&n; *&t;Revision 1.23  1999/07/30 07:03:31  malthoff&n; *&t;Cut some long comments.&n; *&t;Correct the XMAC PHY ID definitions.&n; *&t;&n; *&t;Revision 1.22  1999/05/19 07:33:18  cgoos&n; *&t;Changes for 1000Base-T.&n; *&t;&n; *&t;Revision 1.21  1999/03/25 07:46:11  malthoff&n; *&t;Add XM_HW_CFG, XM_TS_READ, and XM_TS_LOAD registers.&n; *&t;&n; *&t;Revision 1.20  1999/03/12 13:36:09  malthoff&n; *&t;Remove __STDC__.&n; *&n; *&t;Revision 1.19  1998/12/10 12:22:54  gklug&n; *&t;fix: RX_PAGE must be in interrupt mask&n; *&n; *&t;Revision 1.18  1998/12/10 10:36:36  gklug&n; *&t;fix: swap of pause bits&n; *&n; *&t;Revision 1.17  1998/11/18 13:21:45  gklug&n; *&t;fix: Default interrupt mask&n; *&n; *&t;Revision 1.16  1998/10/29 15:53:21  gklug&n; *&t;fix: Default mask uses ASS (GP0) signal&n; *&n; *&t;Revision 1.15  1998/10/28 13:52:52  malthoff&n; *&t;Add new bits in RX_CMD register.&n; *&n; *&t;Revision 1.14  1998/10/19 15:34:53  gklug&n; *&t;fix: typos&n; *&n; *&t;Revision 1.13  1998/10/14 07:19:03  malthoff&n; *&t;bug fix: Every define which describes bit 31&n; *&t;must be declared as unsigned long &squot;UL&squot;.&n; *&t;fix bit definitions of PHY_AN_RFB and PHY_AN_PAUSE.&n; *&t;Remove ANP defines. Rework the RFB defines.&n; *&n; *&t;Revision 1.12  1998/10/14 06:22:44  cgoos&n; *&t;Changed shifted constant to ULONG.&n; *&n; *&t;Revision 1.11  1998/10/14 05:43:26  gklug&n; *&t;add: shift pause codeing&n; *&t;fix: PAUSE bits definition&n; *&n; *&t;Revision 1.10  1998/10/13 09:19:21  malthoff&n; *&t;Again change XMR_FS_ANY_ERR because of new info from XaQti.&n; *&n; *&t;Revision 1.9  1998/10/09 07:58:30  malthoff&n; *&t;Add XMR_FS_FCS_ERR to XMR_FS_ANY_ERR.&n; *&n; *&t;Revision 1.8  1998/10/09 07:18:17  malthoff&n; *&t;bug fix of a bug fix: XM_PAUSE_MODE and XM_DEF_MODE&n; *&t;are not inverted! Bug XM_DEF_MSK is inverted.&n; *&n; *&t;Revision 1.7  1998/10/05 08:04:32  malthoff&n; *&t;bug fix: XM_PAUSE_MODE and XM_DEF_MODE&n; *&t;must be inverted declarations.&n; *&n; *&t;Revision 1.6  1998/09/28 13:38:18  malthoff&n; *&t;Add default modes and masks XM_DEF_MSK,&n; *&t;XM_PAUSE_MODE and XM_DEF_MODE&n; *&n; *&t;Revision 1.5  1998/09/16 14:42:04  malthoff&n; *&t;Bug Fix: XM_GP_PORT is a 32 bit (not a 16 bit) register.&n; *&n; *&t;Revision 1.4  1998/08/20 14:59:47  malthoff&n; *&t;Rework this file after reading the XaQti data sheet&n; *&t;&quot;Differences between Rev. B2 &amp; Rev. C XMAC II&quot;.&n; *&t;This file is now 100% XMAC II Rev. C complained.&n; *&n; *&t;Revision 1.3  1998/06/29 12:18:23  malthoff&n; *&t;Correct XMR_FS_ANY_ERR definition.&n; *&n; *&t;Revision 1.2  1998/06/29 12:10:56  malthoff&n; *&t;Add define XMR_FS_ANY_ERR.&n; *&n; *&t;Revision 1.1  1998/06/19 13:37:17  malthoff&n; *&t;created.&n; *&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_XMAC_H
DECL|macro|__INC_XMAC_H
mdefine_line|#define __INC_XMAC_H
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif&t;/* __cplusplus */
multiline_comment|/* defines ********************************************************************/
multiline_comment|/*&n; * XMAC II registers&n; *&n; * The XMAC registers are 16 or 32 bits wide. The XMACs host processor&n; * interface is set to 16 bit mode, therefore ALL registers will be&n; * addressed with 16 bit accesses.&n; *&n; * The following macros are provided to access the XMAC registers&n; * XM_IN16(), XM_OUT16, XM_IN32(), MX_OUT32(), XM_INADR(), XM_OUTADR(),&n; * XM_INHASH(), and XM_OUTHASH().&n; * The macros are defined in SkGeHw.h.&n; *&n; * Note:&t;NA reg&t;= Network Address e.g DA, SA etc.&n; *&n; */
DECL|macro|XM_MMU_CMD
mdefine_line|#define XM_MMU_CMD&t;0x0000&t;/* 16 bit r/w&t;MMU Command Register */
multiline_comment|/* 0x0004:&t;&t;reserved */
DECL|macro|XM_POFF
mdefine_line|#define XM_POFF&t;&t;0x0008&t;/* 32 bit r/w&t;Packet Offset Register */
DECL|macro|XM_BURST
mdefine_line|#define XM_BURST&t;0x000c&t;/* 32 bit r/w&t;Burst Register for half duplex*/
DECL|macro|XM_1L_VLAN_TAG
mdefine_line|#define XM_1L_VLAN_TAG&t;0x0010&t;/* 16 bit r/w&t;One Level VLAN Tag ID */
DECL|macro|XM_2L_VLAN_TAG
mdefine_line|#define XM_2L_VLAN_TAG&t;0x0014&t;/* 16 bit r/w&t;Two Level VLAN Tag ID */
multiline_comment|/* 0x0018 - 0x001e:&t;reserved */
DECL|macro|XM_TX_CMD
mdefine_line|#define XM_TX_CMD&t;0x0020&t;/* 16 bit r/w&t;Transmit Command Register */
DECL|macro|XM_TX_RT_LIM
mdefine_line|#define&t;XM_TX_RT_LIM&t;0x0024&t;/* 16 bit r/w&t;Transmit Retry Limit Register */
DECL|macro|XM_TX_STIME
mdefine_line|#define XM_TX_STIME&t;0x0028&t;/* 16 bit r/w&t;Transmit Slottime Register */
DECL|macro|XM_TX_IPG
mdefine_line|#define XM_TX_IPG&t;0x002c&t;/* 16 bit r/w&t;Transmit Inter Packet Gap */
DECL|macro|XM_RX_CMD
mdefine_line|#define XM_RX_CMD&t;0x0030&t;/* 16 bit r/w&t;Receive Command Register */
DECL|macro|XM_PHY_ADDR
mdefine_line|#define XM_PHY_ADDR&t;0x0034&t;/* 16 bit r/w&t;PHY Address Register */
DECL|macro|XM_PHY_DATA
mdefine_line|#define&t;XM_PHY_DATA&t;0x0038&t;/* 16 bit r/w&t;PHY Data Register */
multiline_comment|/* 0x003c: &t;&t;reserved */
DECL|macro|XM_GP_PORT
mdefine_line|#define XM_GP_PORT&t;0x0040&t;/* 32 bit r/w&t;General Purpose Port Register */
DECL|macro|XM_IMSK
mdefine_line|#define XM_IMSK&t;&t;0x0044&t;/* 16 bit r/w&t;Interrupt Mask Register */
DECL|macro|XM_ISRC
mdefine_line|#define XM_ISRC&t;&t;0x0048&t;/* 16 bit ro&t;Interrupt Status Register */
DECL|macro|XM_HW_CFG
mdefine_line|#define XM_HW_CFG&t;0x004c&t;/* 16 bit r/w&t;Hardware Config Register */
multiline_comment|/* 0x0050 - 0x005e:&t;reserved */
DECL|macro|XM_TX_LO_WM
mdefine_line|#define XM_TX_LO_WM&t;0x0060&t;/* 16 bit r/w&t;Tx FIFO Low Water Mark */
DECL|macro|XM_TX_HI_WM
mdefine_line|#define XM_TX_HI_WM&t;0x0062&t;/* 16 bit r/w&t;Tx FIFO High Water Mark */
DECL|macro|XM_TX_THR
mdefine_line|#define XM_TX_THR&t;0x0064&t;/* 16 bit r/w&t;Tx Request Threshold */
DECL|macro|XM_HT_THR
mdefine_line|#define&t;XM_HT_THR&t;0x0066&t;/* 16 bit r/w&t;Host Request Threshold */
DECL|macro|XM_PAUSE_DA
mdefine_line|#define&t;XM_PAUSE_DA&t;0x0068&t;/* NA reg r/w&t;Pause Destination Address */
multiline_comment|/* 0x006e: &t;&t;reserved */
DECL|macro|XM_CTL_PARA
mdefine_line|#define XM_CTL_PARA&t;0x0070&t;/* 32 bit r/w&t;Control Parameter Register */
DECL|macro|XM_MAC_OPCODE
mdefine_line|#define XM_MAC_OPCODE&t;0x0074&t;/* 16 bit r/w&t;Opcode for MAC control frames */
DECL|macro|XM_MAC_PTIME
mdefine_line|#define XM_MAC_PTIME&t;0x0076&t;/* 16 bit r/w&t;Pause time for MAC ctrl frames*/
DECL|macro|XM_TX_STAT
mdefine_line|#define XM_TX_STAT&t;0x0078&t;/* 32 bit ro&t;Tx Status LIFO Register */
multiline_comment|/* 0x0080 - 0x00fc:&t;16 NA reg r/w&t;Exakt Match Address Registers */
multiline_comment|/* &t;&t;&t;&t;use the XM_EMX() macro to address */
DECL|macro|XM_EXM_START
mdefine_line|#define XM_EXM_START&t;0x0080&t;&t;/* r/w&t;Start Address of the EXM Regs */
multiline_comment|/*&n;&t; * XM_EXM(Reg)&n;&t; *&n;&t; * returns the XMAC address offset off specified Exakt Match Addr Reg&n;&t; *&n;&t; * para:&t;Reg&t;EXM register to addr&t;(0 .. 15)&n;&t; *&n;&t; * usage:&t;XM_INADDR(XMAC_1,pAC,XM_EXM(i),&amp;val[i]) ;&n;&t; */
DECL|macro|XM_EXM
mdefine_line|#define XM_EXM(Reg)&t;(XM_EXM_START + ((Reg) &lt;&lt; 3))
DECL|macro|XM_SRC_CHK
mdefine_line|#define XM_SRC_CHK&t;0x0100&t;/* NA reg r/w&t;Source Check Address Register */
DECL|macro|XM_SA
mdefine_line|#define XM_SA&t;&t;0x0108&t;/* NA reg r/w&t;Station Address Register */
DECL|macro|XM_HSM
mdefine_line|#define XM_HSM&t;&t;0x0110&t;/* 64 bit r/w&t;Hash Match Address Registers */
DECL|macro|XM_RX_LO_WM
mdefine_line|#define XM_RX_LO_WM&t;0x0118&t;/* 16 bit r/w&t;Receive Low Water Mark */
DECL|macro|XM_RX_HI_WM
mdefine_line|#define XM_RX_HI_WM&t;0x011a&t;/* 16 bit r/w&t;Receive High Water Mark */
DECL|macro|XM_RX_THR
mdefine_line|#define XM_RX_THR&t;0x011c&t;/* 32 bit r/w&t;Receive Request Threshold */
DECL|macro|XM_DEV_ID
mdefine_line|#define XM_DEV_ID&t;0x0120&t;/* 32 bit ro&t;Device ID Register */
DECL|macro|XM_MODE
mdefine_line|#define XM_MODE&t;&t;0x0124&t;/* 32 bit r/w&t;Mode Register */
DECL|macro|XM_LSA
mdefine_line|#define XM_LSA&t;&t;0x0128&t;/* NA reg ro&t;Last Source Register */
multiline_comment|/* 0x012e:&t;&t;reserved */
DECL|macro|XM_TS_READ
mdefine_line|#define XM_TS_READ&t;0x0130&t;/* 32 bit ro&t;TimeStamp Read Regeister */
DECL|macro|XM_TS_LOAD
mdefine_line|#define XM_TS_LOAD&t;0x0134&t;/* 32 bit ro&t;TimeStamp Load Value */
multiline_comment|/* 0x0138 - 0x01fe:&t;reserved */
DECL|macro|XM_STAT_CMD
mdefine_line|#define XM_STAT_CMD&t;0x0200&t;/* 16 bit r/w&t;Statistics Command Register */
DECL|macro|XM_RX_CNT_EV
mdefine_line|#define&t;XM_RX_CNT_EV&t;0x0204&t;/* 32 bit ro&t;Rx Counter Event Register */
DECL|macro|XM_TX_CNT_EV
mdefine_line|#define XM_TX_CNT_EV&t;0x0208&t;/* 32 bit ro&t;Tx Counter Event Register */
DECL|macro|XM_RX_EV_MSK
mdefine_line|#define XM_RX_EV_MSK&t;0x020c&t;/* 32 bit r/w&t;Rx Counter Event Mask */
DECL|macro|XM_TX_EV_MSK
mdefine_line|#define XM_TX_EV_MSK&t;0x0210&t;/* 32 bit r/w&t;Tx Counter Event Mask */
multiline_comment|/* 0x0204 - 0x027e:&t;reserved */
DECL|macro|XM_TXF_OK
mdefine_line|#define XM_TXF_OK&t;0x0280&t;/* 32 bit ro&t;Frames Transmitted OK Conuter */
DECL|macro|XM_TXO_OK_HI
mdefine_line|#define XM_TXO_OK_HI&t;0x0284&t;/* 32 bit ro&t;Octets Transmitted OK High Cnt*/
DECL|macro|XM_TXO_OK_LO
mdefine_line|#define XM_TXO_OK_LO&t;0x0288&t;/* 32 bit ro&t;Octets Transmitted OK Low Cnt */
DECL|macro|XM_TXF_BC_OK
mdefine_line|#define XM_TXF_BC_OK&t;0x028c&t;/* 32 bit ro&t;Broadcast Frames Xmitted OK */
DECL|macro|XM_TXF_MC_OK
mdefine_line|#define XM_TXF_MC_OK&t;0x0290&t;/* 32 bit ro&t;Multicast Frames Xmitted OK */
DECL|macro|XM_TXF_UC_OK
mdefine_line|#define XM_TXF_UC_OK&t;0x0294&t;/* 32 bit ro&t;Unicast Frames Xmitted OK */
DECL|macro|XM_TXF_LONG
mdefine_line|#define XM_TXF_LONG&t;0x0298&t;/* 32 bit ro&t;Tx Long Frame Counter */
DECL|macro|XM_TXE_BURST
mdefine_line|#define XM_TXE_BURST&t;0x029c&t;/* 32 bit ro&t;Tx Burst Event Counter */
DECL|macro|XM_TXF_MPAUSE
mdefine_line|#define XM_TXF_MPAUSE&t;0x02a0&t;/* 32 bit ro&t;Tx Pause MAC Ctrl Frame Cnt */
DECL|macro|XM_TXF_MCTRL
mdefine_line|#define XM_TXF_MCTRL&t;0x02a4&t;/* 32 bit ro&t;Tx MAC Ctrl Frame Counter */
DECL|macro|XM_TXF_SNG_COL
mdefine_line|#define XM_TXF_SNG_COL&t;0x02a8&t;/* 32 bit ro&t;Tx Single Colliosion Counter */
DECL|macro|XM_TXF_MUL_COL
mdefine_line|#define XM_TXF_MUL_COL&t;0x02ac&t;/* 32 bit ro&t;Tx Multiple Collision Counter */
DECL|macro|XM_TXF_ABO_COL
mdefine_line|#define XM_TXF_ABO_COL&t;0x02b0&t;/* 32 bit ro&t;Tx aborted due to Exessive Col*/
DECL|macro|XM_TXF_LAT_COL
mdefine_line|#define XM_TXF_LAT_COL&t;0x02b4&t;/* 32 bit ro&t;Tx Late Collision Counter */
DECL|macro|XM_TXF_DEF
mdefine_line|#define XM_TXF_DEF&t;0x02b8&t;/* 32 bit ro&t;Tx Deferred Frame Counter */
DECL|macro|XM_TXF_EX_DEF
mdefine_line|#define XM_TXF_EX_DEF&t;0x02bc&t;/* 32 bit ro&t;Tx Excessive Deferall Counter */
DECL|macro|XM_TXE_FIFO_UR
mdefine_line|#define XM_TXE_FIFO_UR&t;0x02c0&t;/* 32 bit ro&t;Tx FIFO Underrun Event Cnt */
DECL|macro|XM_TXE_CS_ERR
mdefine_line|#define XM_TXE_CS_ERR&t;0x02c4&t;/* 32 bit ro&t;Tx Carrier Sence Error Cnt */
DECL|macro|XM_TXP_UTIL
mdefine_line|#define XM_TXP_UTIL&t;0x02c8&t;/* 32 bit ro&t;Tx Utilization in % */
multiline_comment|/* 0x02cc - 0x02ce:&t;reserved */
DECL|macro|XM_TXF_64B
mdefine_line|#define XM_TXF_64B&t;0x02d0&t;/* 32 bit ro&t;64 Byte Tx Frame Counter */
DECL|macro|XM_TXF_127B
mdefine_line|#define XM_TXF_127B&t;0x02d4&t;/* 32 bit ro&t;65-127 Byte Tx Frame Counter */
DECL|macro|XM_TXF_255B
mdefine_line|#define XM_TXF_255B&t;0x02d8&t;/* 32 bit ro&t;128-255 Byte Tx Frame Counter */
DECL|macro|XM_TXF_511B
mdefine_line|#define XM_TXF_511B&t;0x02dc&t;/* 32 bit ro&t;256-511 Byte Tx Frame Counter */
DECL|macro|XM_TXF_1023B
mdefine_line|#define XM_TXF_1023B&t;0x02e0&t;/* 32 bit ro&t;512-1023 Byte Tx Frame Counter*/
DECL|macro|XM_TXF_MAX_SZ
mdefine_line|#define XM_TXF_MAX_SZ&t;0x02e4&t;/* 32 bit ro&t;1024-MaxSize Byte Tx Frame Cnt*/
multiline_comment|/* 0x02e8 - 0x02fe:&t;reserved */
DECL|macro|XM_RXF_OK
mdefine_line|#define XM_RXF_OK&t;0x0300&t;/* 32 bit ro&t;Frames Received OK */
DECL|macro|XM_RXO_OK_HI
mdefine_line|#define XM_RXO_OK_HI&t;0x0304&t;/* 32 bit ro&t;Octets Received OK High Cnt */
DECL|macro|XM_RXO_OK_LO
mdefine_line|#define XM_RXO_OK_LO&t;0x0308&t;/* 32 bit ro&t;Octets Received OK Low Counter*/
DECL|macro|XM_RXF_BC_OK
mdefine_line|#define XM_RXF_BC_OK&t;0x030c&t;/* 32 bit ro&t;Broadcast Frames Received OK */
DECL|macro|XM_RXF_MC_OK
mdefine_line|#define XM_RXF_MC_OK&t;0x0310&t;/* 32 bit ro&t;Multicast Frames Received OK */
DECL|macro|XM_RXF_UC_OK
mdefine_line|#define XM_RXF_UC_OK&t;0x0314&t;/* 32 bit ro&t;Unicast Frames Received OK */
DECL|macro|XM_RXF_MPAUSE
mdefine_line|#define XM_RXF_MPAUSE&t;0x0318&t;/* 32 bit ro&t;Rx Pause MAC Ctrl Frame Cnt */
DECL|macro|XM_RXF_MCTRL
mdefine_line|#define XM_RXF_MCTRL&t;0x031c&t;/* 32 bit ro&t;Rx MAC Ctrl Frame Counter */
DECL|macro|XM_RXF_INV_MP
mdefine_line|#define XM_RXF_INV_MP&t;0x0320&t;/* 32 bit ro&t;Rx invalid Pause Frame Cnt */
DECL|macro|XM_RXF_INV_MOC
mdefine_line|#define XM_RXF_INV_MOC&t;0x0324&t;/* 32 bit ro&t;Rx Frames with inv. MAC Opcode*/
DECL|macro|XM_RXE_BURST
mdefine_line|#define XM_RXE_BURST&t;0x0328&t;/* 32 bit ro&t;Rx Burst Event Counter */
DECL|macro|XM_RXE_FMISS
mdefine_line|#define XM_RXE_FMISS&t;0x032c&t;/* 32 bit ro&t;Rx Missed Frames Event Cnt */
DECL|macro|XM_RXF_FRA_ERR
mdefine_line|#define XM_RXF_FRA_ERR&t;0x0330&t;/* 32 bit ro&t;Rx Framing Error Counter */
DECL|macro|XM_RXE_FIFO_OV
mdefine_line|#define XM_RXE_FIFO_OV&t;0x0334&t;/* 32 bit ro&t;Rx FIFO overflow Event Cnt */
DECL|macro|XM_RXF_JAB_PKT
mdefine_line|#define XM_RXF_JAB_PKT&t;0x0338&t;/* 32 bit ro&t;Rx Jabber Packet Frame Cnt */
DECL|macro|XM_RXE_CAR_ERR
mdefine_line|#define XM_RXE_CAR_ERR&t;0x033c&t;/* 32 bit ro&t;Rx Carrier Event Error Cnt */
DECL|macro|XM_RXF_LEN_ERR
mdefine_line|#define XM_RXF_LEN_ERR&t;0x0340&t;/* 32 bit ro&t;Rx in Range Length Error */
DECL|macro|XM_RXE_SYM_ERR
mdefine_line|#define XM_RXE_SYM_ERR&t;0x0344&t;/* 32 bit ro&t;Rx Symbol Error Counter */
DECL|macro|XM_RXE_SHT_ERR
mdefine_line|#define XM_RXE_SHT_ERR&t;0x0348&t;/* 32 bit ro&t;Rx Short Event Error Cnt */
DECL|macro|XM_RXE_RUNT
mdefine_line|#define XM_RXE_RUNT&t;0x034c&t;/* 32 bit ro&t;Rx Runt Event Counter */
DECL|macro|XM_RXF_LNG_ERR
mdefine_line|#define XM_RXF_LNG_ERR&t;0x0350&t;/* 32 bit ro&t;Rx Frame too Long Error Cnt */
DECL|macro|XM_RXF_FCS_ERR
mdefine_line|#define XM_RXF_FCS_ERR&t;0x0354&t;/* 32 bit ro&t;Rx Frame Check Seq. Error Cnt */
multiline_comment|/* 0x0358 - 0x035a:&t;reserved */
DECL|macro|XM_RXF_CEX_ERR
mdefine_line|#define XM_RXF_CEX_ERR&t;0x035c&t;/* 32 bit ro&t;Rx Carrier Ext Error Frame Cnt*/
DECL|macro|XM_RXP_UTIL
mdefine_line|#define XM_RXP_UTIL&t;0x0360&t;/* 32 bit ro&t;Rx Utilization in % */
multiline_comment|/* 0x0364 - 0x0366:&t;reserved */
DECL|macro|XM_RXF_64B
mdefine_line|#define XM_RXF_64B&t;0x0368&t;/* 32 bit ro&t;64 Byte Rx Frame Counter */
DECL|macro|XM_RXF_127B
mdefine_line|#define XM_RXF_127B&t;0x036c&t;/* 32 bit ro&t;65-127 Byte Rx Frame Counter */
DECL|macro|XM_RXF_255B
mdefine_line|#define XM_RXF_255B&t;0x0370&t;/* 32 bit ro&t;128-255 Byte Rx Frame Counter */
DECL|macro|XM_RXF_511B
mdefine_line|#define XM_RXF_511B&t;0x0374&t;/* 32 bit ro&t;256-511 Byte Rx Frame Counter */
DECL|macro|XM_RXF_1023B
mdefine_line|#define XM_RXF_1023B&t;0x0378&t;/* 32 bit ro&t;512-1023 Byte Rx Frame Counter*/
DECL|macro|XM_RXF_MAX_SZ
mdefine_line|#define XM_RXF_MAX_SZ&t;0x037c&t;/* 32 bit ro&t;1024-MaxSize Byte Rx Frame Cnt*/
multiline_comment|/* 0x02e8 - 0x02fe:&t;reserved */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * XMAC Bit Definitions&n; *&n; * If the bit access behaviour differs from the register access behaviour&n; * (r/w, ro) this is documented after the bit number. The following bit&n; * access behaviours are used:&n; *&t;(sc)&t;self clearing&n; *&t;(ro)&t;read only&n; */
multiline_comment|/*&t;XM_MMU_CMD&t;16 bit r/w&t;MMU Comamnd Register */
multiline_comment|/* Bit 15..13:&t;reserved */
DECL|macro|XM_MMU_PHY_RDY
mdefine_line|#define XM_MMU_PHY_RDY&t;(1&lt;&lt;12)&t;/* Bit 12:&t;PHY Read Ready */
DECL|macro|XM_MMU_PHY_BUSY
mdefine_line|#define XM_MMU_PHY_BUSY&t;(1&lt;&lt;11)&t;/* Bit 11:&t;PHY Busy */
DECL|macro|XM_MMU_IGN_PF
mdefine_line|#define XM_MMU_IGN_PF&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Ignore Pause Frame */
DECL|macro|XM_MMU_MAC_LB
mdefine_line|#define XM_MMU_MAC_LB&t;(1&lt;&lt;9)&t;/* Bit&t;9:&t;Enable MAC Loopback */
multiline_comment|/* Bit&t;8:&t;reserved */
DECL|macro|XM_MMU_FRC_COL
mdefine_line|#define XM_MMU_FRC_COL&t;(1&lt;&lt;7)&t;/* Bit&t;7:&t;Force Collision */
DECL|macro|XM_MMU_SIM_COL
mdefine_line|#define XM_MMU_SIM_COL&t;(1&lt;&lt;6)&t;/* Bit&t;6:&t;Simulate Collision */
DECL|macro|XM_MMU_NO_PRE
mdefine_line|#define XM_MMU_NO_PRE&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;No MDIO Preamble */
DECL|macro|XM_MMU_GMII_FD
mdefine_line|#define XM_MMU_GMII_FD&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;GMII uses Full Duplex */
DECL|macro|XM_MMU_RAT_CTRL
mdefine_line|#define XM_MMU_RAT_CTRL&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;Enable Rate Control */
DECL|macro|XM_MMU_GMII_LOOP
mdefine_line|#define XM_MMU_GMII_LOOP (1&lt;&lt;2)&t;/* Bit&t;2:&t;PHY is in Lookback Mode */
DECL|macro|XM_MMU_ENA_RX
mdefine_line|#define XM_MMU_ENA_RX&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Enable Receiver */
DECL|macro|XM_MMU_ENA_TX
mdefine_line|#define XM_MMU_ENA_TX&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Enable Transmitter */
multiline_comment|/*&t;XM_TX_CMD&t;16 bit r/w&t;Transmit Command Register */
multiline_comment|/* Bit 15..7:&t;reserved */
DECL|macro|XM_TX_BK2BK
mdefine_line|#define XM_TX_BK2BK&t;(1&lt;&lt;6)&t;/* Bit&t;6:&t;Ignor Carrier Sense (tx Bk2Bk)*/
DECL|macro|XM_TX_ENC_BYP
mdefine_line|#define XM_TX_ENC_BYP&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Set Encoder in Bypass Mode */
DECL|macro|XM_TX_SAM_LINE
mdefine_line|#define XM_TX_SAM_LINE&t;(1&lt;&lt;4)&t;/* Bit&t;4: (sc)&t;Start utilization calculation */
DECL|macro|XM_TX_NO_GIG_MD
mdefine_line|#define XM_TX_NO_GIG_MD&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;Disable Carrier Extension */
DECL|macro|XM_TX_NO_PRE
mdefine_line|#define XM_TX_NO_PRE&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;Disable Preamble Generation */
DECL|macro|XM_TX_NO_CRC
mdefine_line|#define XM_TX_NO_CRC&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Disable CRC Generation */
DECL|macro|XM_TX_AUTO_PAD
mdefine_line|#define XM_TX_AUTO_PAD&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Enable Automatic Padding */
multiline_comment|/*&t;XM_TX_RT_LIM&t;16 bit r/w&t;Transmit Retry Limit Register */
multiline_comment|/* Bit 15..5:&t;reserved */
DECL|macro|XM_RT_LIM_MSK
mdefine_line|#define&t;XM_RT_LIM_MSK&t;0x1f&t;/* Bit&t;4..0:&t;Tx Retry Limit */
multiline_comment|/*&t;XM_TX_STIME&t;16 bit r/w&t;Transmit Slottime Register */
multiline_comment|/* Bit 15..7:&t;reserved */
DECL|macro|XM_STIME_MSK
mdefine_line|#define XM_STIME_MSK&t;0x7f&t;/* Bit&t;6..0:&t;Tx Slottime bits */
multiline_comment|/*&t;XM_TX_IPG&t;16 bit r/w&t;Transmit Inter Packet Gap */
multiline_comment|/* Bit 15..8:&t;reserved */
DECL|macro|XM_IPG_MSK
mdefine_line|#define XM_IPG_MSK&t;0xff&t;/* Bit&t;7..0:&t;IPG value bits */
multiline_comment|/*&t;XM_RX_CMD&t;16 bit r/w&t;Receive Command Register */
multiline_comment|/* Bit 15..9:&t;reserved */
DECL|macro|XM_RX_LENERR_OK
mdefine_line|#define XM_RX_LENERR_OK (1&lt;&lt;8)&t;/* Bit&t;8&t;don&squot;t set Rx Err bit for */
multiline_comment|/*&t;&t;inrange error packets */
DECL|macro|XM_RX_BIG_PK_OK
mdefine_line|#define XM_RX_BIG_PK_OK&t;(1&lt;&lt;7)&t;/* Bit&t;7&t;don&squot;t set Rx Err bit for */
multiline_comment|/*&t;&t;jumbo packets */
DECL|macro|XM_RX_IPG_CAP
mdefine_line|#define XM_RX_IPG_CAP&t;(1&lt;&lt;6)&t;/* Bit&t;6&t;repl. type field with IPG */
DECL|macro|XM_RX_TP_MD
mdefine_line|#define XM_RX_TP_MD&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Enable transparent Mode */
DECL|macro|XM_RX_STRIP_FCS
mdefine_line|#define XM_RX_STRIP_FCS&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;Enable FCS Stripping */
DECL|macro|XM_RX_SELF_RX
mdefine_line|#define XM_RX_SELF_RX&t;(1&lt;&lt;3)&t;/* Bit&t;3: &t;Enable Rx of own packets */
DECL|macro|XM_RX_SAM_LINE
mdefine_line|#define XM_RX_SAM_LINE&t;(1&lt;&lt;2)&t;/* Bit&t;2: (sc)&t;Start utilization calculation */
DECL|macro|XM_RX_STRIP_PAD
mdefine_line|#define XM_RX_STRIP_PAD&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Strip pad bytes of rx frames */
DECL|macro|XM_RX_DIS_CEXT
mdefine_line|#define XM_RX_DIS_CEXT&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Disable carrier ext. check */
multiline_comment|/*&t;XM_PHY_ADDR&t;16 bit r/w&t;PHY Address Register */
multiline_comment|/* Bit 15..5:&t;reserved */
DECL|macro|XM_PHY_ADDR_SZ
mdefine_line|#define&t;XM_PHY_ADDR_SZ&t;0x1f&t;/* Bit&t;4..0:&t;PHY Address bits */
multiline_comment|/*&t;XM_GP_PORT&t;32 bit r/w&t;General Purpose Port Register */
multiline_comment|/* Bit 31..7:&t;reserved */
DECL|macro|XM_GP_ANIP
mdefine_line|#define&t;XM_GP_ANIP&t;(1L&lt;&lt;6)&t;/* Bit&t;6: (ro)&t;Auto Negotiation in Progress */
DECL|macro|XM_GP_FRC_INT
mdefine_line|#define XM_GP_FRC_INT&t;(1L&lt;&lt;5)&t;/* Bit&t;5: (sc)&t;Force Interrupt */
multiline_comment|/* Bit&t;4:&t;reserved */
DECL|macro|XM_GP_RES_MAC
mdefine_line|#define XM_GP_RES_MAC&t;(1L&lt;&lt;3)&t;/* Bit&t;3: (sc)&t;Reset MAC and FIFOs */
DECL|macro|XM_GP_RES_STAT
mdefine_line|#define XM_GP_RES_STAT&t;(1L&lt;&lt;2)&t;/* Bit&t;2: (sc)&t;Reset the statistics module */
multiline_comment|/* Bit&t;1:&t;reserved */
DECL|macro|XM_GP_INP_ASS
mdefine_line|#define XM_GP_INP_ASS&t;(1L&lt;&lt;0)&t;/* Bit&t;0: (ro) GP Input Pin asserted */
multiline_comment|/*&t;XM_IMSK&t;&t;16 bit r/w&t;Interrupt Mask Register */
multiline_comment|/*&t;XM_ISRC&t;&t;16 bit ro&t;Interrupt Status Register */
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
mdefine_line|#define XM_IS_RX_PAGE&t;(1&lt;&lt;9)&t;/* Bit&t;9:&t;Page Received */
DECL|macro|XM_IS_TX_PAGE
mdefine_line|#define XM_IS_TX_PAGE&t;(1&lt;&lt;8)&t;/* Bit&t;8:&t;Next Page Loaded for Transmit */
DECL|macro|XM_IS_AND
mdefine_line|#define XM_IS_AND&t;(1&lt;&lt;7)&t;/* Bit&t;7:&t;Auto Negotiation Done */
DECL|macro|XM_IS_TSC_OV
mdefine_line|#define XM_IS_TSC_OV&t;(1&lt;&lt;6)&t;/* Bit&t;6:&t;Time Stamp Counter Overflow */
DECL|macro|XM_IS_RXC_OV
mdefine_line|#define XM_IS_RXC_OV&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Rx Counter Event Overflow */
DECL|macro|XM_IS_TXC_OV
mdefine_line|#define XM_IS_TXC_OV&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;Tx Counter Event Overflow */
DECL|macro|XM_IS_RXF_OV
mdefine_line|#define XM_IS_RXF_OV&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;Receive FIFO Overflow */
DECL|macro|XM_IS_TXF_UR
mdefine_line|#define XM_IS_TXF_UR&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;Transmit FIFO Underrun */
DECL|macro|XM_IS_TX_COMP
mdefine_line|#define XM_IS_TX_COMP&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Frame Tx Complete */
DECL|macro|XM_IS_RX_COMP
mdefine_line|#define XM_IS_RX_COMP&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Frame Rx Complete */
DECL|macro|XM_DEF_MSK
mdefine_line|#define XM_DEF_MSK&t;(~(XM_IS_INP_ASS | XM_IS_LIPA_RC | XM_IS_RX_PAGE |&bslash;&n;&t;&t;&t;XM_IS_AND | XM_IS_RXC_OV | XM_IS_TXC_OV |&bslash;&n;&t;&t;&t;XM_IS_TXF_UR))
multiline_comment|/*&t;XM_HW_CFG&t;16 bit r/w&t;Hardware Config Register */
multiline_comment|/* Bit 15.. 4:&t;reserved */
DECL|macro|XM_HW_GEN_EOP
mdefine_line|#define&t;XM_HW_GEN_EOP&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;generate End of Packet pulse */
DECL|macro|XM_HW_COM4SIG
mdefine_line|#define XM_HW_COM4SIG&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;use Comma Detect for Sig. Det.*/
multiline_comment|/* Bit&t;1:&t;reserved */
DECL|macro|XM_HW_GMII_MD
mdefine_line|#define XM_HW_GMII_MD&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;GMII Interface selected */
multiline_comment|/*&t;XM_TX_LO_WM&t;16 bit r/w&t;Tx FIFO Low Water Mark */
multiline_comment|/*&t;XM_TX_HI_WM&t;16 bit r/w&t;Tx FIFO High Water Mark */
multiline_comment|/* Bit 15..10&t;reserved */
DECL|macro|XM_TX_WM_MSK
mdefine_line|#define&t;XM_TX_WM_MSK&t;0x01ff&t;/* Bit&t;9.. 0&t;Tx FIFO Watermark bits */
multiline_comment|/*&t;XM_TX_THR&t;16 bit r/w&t;Tx Request Threshold */
multiline_comment|/*&t;XM_HT_THR&t;16 bit r/w&t;Host Request Threshold */
multiline_comment|/*&t;XM_RX_THR&t;16 bit r/w&t;Receive Request Threshold */
multiline_comment|/* Bit 15..11&t;reserved */
DECL|macro|XM_THR_MSK
mdefine_line|#define&t;XM_THR_MSK&t;0x03ff&t;/* Bit 10.. 0&t;Tx FIFO Watermark bits */
multiline_comment|/*&t;XM_TX_STAT&t;32 bit ro&t;Tx Status LIFO Register */
DECL|macro|XM_ST_VALID
mdefine_line|#define XM_ST_VALID&t;(1UL&lt;&lt;31)&t;/* Bit 31:&t;Status Valid */
DECL|macro|XM_ST_BYTE_CNT
mdefine_line|#define XM_ST_BYTE_CNT&t;(0x3fffL&lt;&lt;17)&t;/* Bit 30..17:&t;Tx frame Length */
DECL|macro|XM_ST_RETRY_CNT
mdefine_line|#define XM_ST_RETRY_CNT&t;(0x1fL&lt;&lt;12)&t;/* Bit 16..12:&t;Retry Count */
DECL|macro|XM_ST_EX_COL
mdefine_line|#define XM_ST_EX_COL&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Excessive Collisions */
DECL|macro|XM_ST_EX_DEF
mdefine_line|#define XM_ST_EX_DEF&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Excessive Deferral */
DECL|macro|XM_ST_BURST
mdefine_line|#define XM_ST_BURST&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9:&t;p. xmitted in burst md*/
DECL|macro|XM_ST_DEFER
mdefine_line|#define XM_ST_DEFER&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8:&t;packet was defered */
DECL|macro|XM_ST_BC
mdefine_line|#define XM_ST_BC&t;(1L&lt;&lt;7)&t;&t;/* Bit&t;7:&t;Broadcast packet */
DECL|macro|XM_ST_MC
mdefine_line|#define XM_ST_MC&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;Multicast packet */
DECL|macro|XM_ST_UC
mdefine_line|#define XM_ST_UC&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;Unicast packet */
DECL|macro|XM_ST_TX_UR
mdefine_line|#define XM_ST_TX_UR&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;FIFO Underrun occurred */
DECL|macro|XM_ST_CS_ERR
mdefine_line|#define XM_ST_CS_ERR&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3:&t;Carrier Sense Error */
DECL|macro|XM_ST_LAT_COL
mdefine_line|#define XM_ST_LAT_COL&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;Late Collision Error */
DECL|macro|XM_ST_MUL_COL
mdefine_line|#define XM_ST_MUL_COL&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1:&t;Multiple Collisions */
DECL|macro|XM_ST_SGN_COL
mdefine_line|#define XM_ST_SGN_COL&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Single Collision */
multiline_comment|/*&t;XM_RX_LO_WM&t;16 bit r/w&t;Receive Low Water Mark */
multiline_comment|/*&t;XM_RX_HI_WM&t;16 bit r/w&t;Receive High Water Mark */
multiline_comment|/* Bit 15..11:&t;reserved */
DECL|macro|XM_RX_WM_MSK
mdefine_line|#define&t;XM_RX_WM_MSK&t;0x03ff&t;/* Bit 11.. 0:&t;Rx FIFO Watermark bits */
multiline_comment|/*&t;XM_DEV_ID&t;32 bit ro&t;Device ID Register */
DECL|macro|XM_DEV_OUI
mdefine_line|#define&t;XM_DEV_OUI&t;(0x00ffffffUL&lt;&lt;8)&t;/* Bit 31..8:&t;Device OUI */
DECL|macro|XM_DEV_REV
mdefine_line|#define XM_DEV_REV&t;(0x07L &lt;&lt; 5)&t;&t;/* Bit&t;7..5:&t;Chip Rev Num */
multiline_comment|/*&t;XM_MODE&t;&t;32 bit r/w&t;Mode Register */
multiline_comment|/* Bit 31..27:&t;reserved */
DECL|macro|XM_MD_ENA_REJ
mdefine_line|#define XM_MD_ENA_REJ&t;(1L&lt;&lt;26)&t;/* Bit 26:&t;Enable Frame Reject */
DECL|macro|XM_MD_SPOE_E
mdefine_line|#define XM_MD_SPOE_E&t;(1L&lt;&lt;25)&t;/* Bit 25:&t;Send Pause on Edge */
multiline_comment|/* &t;&t;extern generated */
DECL|macro|XM_MD_TX_REP
mdefine_line|#define XM_MD_TX_REP&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;Transmit Repeater Mode*/
DECL|macro|XM_MD_SPOFF_I
mdefine_line|#define XM_MD_SPOFF_I&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;Send Pause on FIFOfull*/
multiline_comment|/*&t;&t;intern generated */
DECL|macro|XM_MD_LE_STW
mdefine_line|#define XM_MD_LE_STW&t;(1L&lt;&lt;22)&t;/* Bit 22:&t;Rx Stat Word in Lit En*/
DECL|macro|XM_MD_TX_CONT
mdefine_line|#define XM_MD_TX_CONT&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;Send Continuous */
DECL|macro|XM_MD_TX_PAUSE
mdefine_line|#define XM_MD_TX_PAUSE&t;(1L&lt;&lt;20)&t;/* Bit 20: (sc)&t;Send Pause Frame */
DECL|macro|XM_MD_ATS
mdefine_line|#define XM_MD_ATS&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;Append Time Stamp */
DECL|macro|XM_MD_SPOL_I
mdefine_line|#define XM_MD_SPOL_I&t;(1L&lt;&lt;18)&t;/* Bit 18:&t;Send Pause on Low */
multiline_comment|/*&t;&t;intern generated */
DECL|macro|XM_MD_SPOH_I
mdefine_line|#define XM_MD_SPOH_I&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;Send Pause on High */
multiline_comment|/*&t;&t;intern generated */
DECL|macro|XM_MD_CAP
mdefine_line|#define XM_MD_CAP&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;Check Address Pair */
DECL|macro|XM_MD_ENA_HSH
mdefine_line|#define XM_MD_ENA_HSH&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Enable Hashing */
DECL|macro|XM_MD_CSA
mdefine_line|#define XM_MD_CSA&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;Check Station Address */
DECL|macro|XM_MD_CAA
mdefine_line|#define XM_MD_CAA&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Check Address Array */
DECL|macro|XM_MD_RX_MCTRL
mdefine_line|#define XM_MD_RX_MCTRL&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Rx MAC Control Frames */
DECL|macro|XM_MD_RX_RUNT
mdefine_line|#define XM_MD_RX_RUNT&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Rx Runt Frames */
DECL|macro|XM_MD_RX_IRLE
mdefine_line|#define XM_MD_RX_IRLE&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Rx in Range Len Err F */
DECL|macro|XM_MD_RX_LONG
mdefine_line|#define XM_MD_RX_LONG&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9:&t;Rx Long Frames */
DECL|macro|XM_MD_RX_CRCE
mdefine_line|#define XM_MD_RX_CRCE&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8:&t;Rx CRC Error Frames */
DECL|macro|XM_MD_RX_ERR
mdefine_line|#define XM_MD_RX_ERR&t;(1L&lt;&lt;7)&t;&t;/* Bit&t;7:&t;Rx Error Frames */
DECL|macro|XM_MD_DIS_UC
mdefine_line|#define XM_MD_DIS_UC&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;Disable Rx Unicast */
DECL|macro|XM_MD_DIS_MC
mdefine_line|#define XM_MD_DIS_MC&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;Disable Rx Multicast */
DECL|macro|XM_MD_DIS_BC
mdefine_line|#define XM_MD_DIS_BC&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Disable Rx Boradcast */
DECL|macro|XM_MD_ENA_PROM
mdefine_line|#define XM_MD_ENA_PROM&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3:&t;Enable Promiscuous */
DECL|macro|XM_MD_ENA_BE
mdefine_line|#define XM_MD_ENA_BE&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;Enable Big Endian */
DECL|macro|XM_MD_FTF
mdefine_line|#define XM_MD_FTF&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1: (sc)&t;Flush Tx FIFO */
DECL|macro|XM_MD_FRF
mdefine_line|#define XM_MD_FRF&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0: (sc)&t;Flush Rx FIFO */
DECL|macro|XM_PAUSE_MODE
mdefine_line|#define&t;XM_PAUSE_MODE&t;(XM_MD_SPOE_E | XM_MD_SPOL_I | XM_MD_SPOH_I)
DECL|macro|XM_DEF_MODE
mdefine_line|#define XM_DEF_MODE&t;(XM_MD_RX_RUNT | XM_MD_RX_IRLE | XM_MD_RX_LONG |&bslash;&n;&t;&t;&t; XM_MD_RX_CRCE | XM_MD_RX_ERR | XM_MD_CSA |&bslash;&n;&t;&t;&t; XM_MD_CAA)
multiline_comment|/*&t;XM_STAT_CMD&t;16 bit r/w&t;Statistics Command Register */
multiline_comment|/* Bit 16..6:&t;reserved */
DECL|macro|XM_SC_SNP_RXC
mdefine_line|#define XM_SC_SNP_RXC&t;(1&lt;&lt;5)&t;/* Bit&t;5: (sc)&t;Snap Rx Counters */
DECL|macro|XM_SC_SNP_TXC
mdefine_line|#define XM_SC_SNP_TXC&t;(1&lt;&lt;4)&t;/* Bit&t;4: (sc)&t;Snap Tx Counters */
DECL|macro|XM_SC_CP_RXC
mdefine_line|#define XM_SC_CP_RXC&t;(1&lt;&lt;3)&t;/* Bit&t;3: &t;Copy Rx Counters Continuously */
DECL|macro|XM_SC_CP_TXC
mdefine_line|#define XM_SC_CP_TXC&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;Copy Tx Counters Continuously */
DECL|macro|XM_SC_CLR_RXC
mdefine_line|#define XM_SC_CLR_RXC&t;(1&lt;&lt;1)&t;/* Bit&t;1: (sc)&t;Clear Rx Counters */
DECL|macro|XM_SC_CLR_TXC
mdefine_line|#define XM_SC_CLR_TXC&t;(1&lt;&lt;0)&t;/* Bit&t;0: (sc) Clear Tx Counters */
multiline_comment|/*&t;XM_RX_CNT_EV&t;32 bit ro&t;Rx Counter Event Register */
multiline_comment|/*&t;XM_RX_EV_MSK&t;32 bit r/w&t;Rx Counter Event Mask */
DECL|macro|XMR_MAX_SZ_OV
mdefine_line|#define&t;XMR_MAX_SZ_OV&t;(1UL&lt;&lt;31)&t;/* Bit 31:&t;1024-MaxSize Rx Cnt Ov*/
DECL|macro|XMR_1023B_OV
mdefine_line|#define XMR_1023B_OV&t;(1L&lt;&lt;30)&t;/* Bit 30:&t;512-1023Byte Rx Cnt Ov*/
DECL|macro|XMR_511B_OV
mdefine_line|#define XMR_511B_OV&t;(1L&lt;&lt;29)&t;/* Bit 29:&t;256-511 Byte Rx Cnt Ov*/
DECL|macro|XMR_255B_OV
mdefine_line|#define XMR_255B_OV&t;(1L&lt;&lt;28)&t;/* Bit 28:&t;128-255 Byte Rx Cnt Ov*/
DECL|macro|XMR_127B_OV
mdefine_line|#define XMR_127B_OV&t;(1L&lt;&lt;27)&t;/* Bit 27:&t;65-127 Byte Rx Cnt Ov */
DECL|macro|XMR_64B_OV
mdefine_line|#define XMR_64B_OV&t;(1L&lt;&lt;26)&t;/* Bit 26:&t;64 Byte Rx Cnt Ov */
DECL|macro|XMR_UTIL_OV
mdefine_line|#define XMR_UTIL_OV&t;(1L&lt;&lt;25)&t;/* Bit 25:&t;Rx Util Cnt Overflow */
DECL|macro|XMR_UTIL_UR
mdefine_line|#define XMR_UTIL_UR&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;Rx Util Cnt Underrun */
DECL|macro|XMR_CEX_ERR_OV
mdefine_line|#define XMR_CEX_ERR_OV&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;CEXT Err Cnt Ov */
multiline_comment|/* Bit 22:&t;reserved */
DECL|macro|XMR_FCS_ERR_OV
mdefine_line|#define XMR_FCS_ERR_OV&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;Rx FCS Error Cnt Ov */
DECL|macro|XMR_LNG_ERR_OV
mdefine_line|#define XMR_LNG_ERR_OV&t;(1L&lt;&lt;20)&t;/* Bit 20:&t;Rx too Long Err Cnt Ov*/
DECL|macro|XMR_RUNT_OV
mdefine_line|#define XMR_RUNT_OV&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;Runt Event Cnt Ov */
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
mdefine_line|#define XMR_FIFO_OV&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Rx FIFO Ov Ev Cnt Ov */
DECL|macro|XMR_FRA_ERR_OV
mdefine_line|#define XMR_FRA_ERR_OV&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Rx Framing Err Cnt Ov */
DECL|macro|XMR_FMISS_OV
mdefine_line|#define XMR_FMISS_OV&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Rx Missed Ev Cnt Ov */
DECL|macro|XMR_BURST
mdefine_line|#define XMR_BURST&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Rx Burst Event Cnt Ov */
DECL|macro|XMR_INV_MOC
mdefine_line|#define XMR_INV_MOC&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9:&t;Rx with inv. MAC OC Ov*/
DECL|macro|XMR_INV_MP
mdefine_line|#define XMR_INV_MP&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8:&t;Rx inv Pause Frame Ov */
DECL|macro|XMR_MCTRL_OV
mdefine_line|#define XMR_MCTRL_OV&t;(1L&lt;&lt;7)&t;&t;/* Bit&t;7:&t;Rx MAC Ctrl-F Cnt Ov */
DECL|macro|XMR_MPAUSE_OV
mdefine_line|#define XMR_MPAUSE_OV&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;Rx Pause MAC Ctrl-F Ov*/
DECL|macro|XMR_UC_OK_OV
mdefine_line|#define XMR_UC_OK_OV&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;Rx Unicast Frame CntOv*/
DECL|macro|XMR_MC_OK_OV
mdefine_line|#define XMR_MC_OK_OV&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Rx Multicast Cnt Ov */
DECL|macro|XMR_BC_OK_OV
mdefine_line|#define XMR_BC_OK_OV&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3:&t;Rx Broadcast Cnt Ov */
DECL|macro|XMR_OK_LO_OV
mdefine_line|#define XMR_OK_LO_OV&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;Octets Rx OK Low CntOv*/
DECL|macro|XMR_OK_HI_OV
mdefine_line|#define XMR_OK_HI_OV&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1:&t;Octets Rx OK Hi Cnt Ov*/
DECL|macro|XMR_OK_OV
mdefine_line|#define XMR_OK_OV&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Frames Received Ok Ov */
DECL|macro|XMR_DEF_MSK
mdefine_line|#define XMR_DEF_MSK&t;0x00000006L&t;/* all bits excepting 1 and 2 */
multiline_comment|/*&t;XM_TX_CNT_EV&t;32 bit ro&t;Tx Counter Event Register */
multiline_comment|/*&t;XM_TX_EV_MSK&t;32 bit r/w&t;Tx Counter Event Mask */
multiline_comment|/* Bit 31..26:&t;reserved */
DECL|macro|XMT_MAX_SZ_OV
mdefine_line|#define XMT_MAX_SZ_OV&t;(1L&lt;&lt;25)&t;/* Bit 25:&t;1024-MaxSize Tx Cnt Ov*/
DECL|macro|XMT_1023B_OV
mdefine_line|#define XMT_1023B_OV&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;512-1023Byte Tx Cnt Ov*/
DECL|macro|XMT_511B_OV
mdefine_line|#define XMT_511B_OV&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;256-511 Byte Tx Cnt Ov*/
DECL|macro|XMT_255B_OV
mdefine_line|#define XMT_255B_OV&t;(1L&lt;&lt;22)&t;/* Bit 22:&t;128-255 Byte Tx Cnt Ov*/
DECL|macro|XMT_127B_OV
mdefine_line|#define XMT_127B_OV&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;65-127 Byte Tx Cnt Ov */
DECL|macro|XMT_64B_OV
mdefine_line|#define XMT_64B_OV&t;(1L&lt;&lt;20)&t;/* Bit 20:&t;64 Byte Tx Cnt Ov */
DECL|macro|XMT_UTIL_OV
mdefine_line|#define XMT_UTIL_OV&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;Tx Util Cnt Overflow */
DECL|macro|XMT_UTIL_UR
mdefine_line|#define XMT_UTIL_UR&t;(1L&lt;&lt;18)&t;/* Bit 18:&t;Tx Util Cnt Underrun */
DECL|macro|XMT_CS_ERR_OV
mdefine_line|#define XMT_CS_ERR_OV&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;Tx Carr Sen Err Cnt Ov*/
DECL|macro|XMT_FIFO_UR_OV
mdefine_line|#define XMT_FIFO_UR_OV&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;Tx FIFO Ur Ev Cnt Ov */
DECL|macro|XMT_EX_DEF_OV
mdefine_line|#define XMT_EX_DEF_OV&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Tx Ex Deferall Cnt Ov */
DECL|macro|XMT_DEF
mdefine_line|#define XMT_DEF&t;&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;Tx Deferred Cnt Ov */
DECL|macro|XMT_LAT_COL_OV
mdefine_line|#define XMT_LAT_COL_OV&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Tx Late Col Cnt Ov */
DECL|macro|XMT_ABO_COL_OV
mdefine_line|#define XMT_ABO_COL_OV&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Tx abo dueto Ex Col Ov*/
DECL|macro|XMT_MUL_COL_OV
mdefine_line|#define XMT_MUL_COL_OV&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Tx Mult Col Cnt Ov */
DECL|macro|XMT_SNG_COL
mdefine_line|#define XMT_SNG_COL&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Tx Single Col Cnt Ov */
DECL|macro|XMT_MCTRL_OV
mdefine_line|#define XMT_MCTRL_OV&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9:&t;Tx MAC Ctrl Counter Ov*/
DECL|macro|XMT_MPAUSE
mdefine_line|#define XMT_MPAUSE&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8:&t;Tx Pause MAC Ctrl-F Ov*/
DECL|macro|XMT_BURST
mdefine_line|#define XMT_BURST&t;(1L&lt;&lt;7)&t;&t;/* Bit&t;7:&t;Tx Burst Event Cnt Ov */
DECL|macro|XMT_LONG
mdefine_line|#define XMT_LONG&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;Tx Long Frame Cnt Ov */
DECL|macro|XMT_UC_OK_OV
mdefine_line|#define XMT_UC_OK_OV&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;Tx Unicast Cnt Ov */
DECL|macro|XMT_MC_OK_OV
mdefine_line|#define XMT_MC_OK_OV&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Tx Multicast Cnt Ov */
DECL|macro|XMT_BC_OK_OV
mdefine_line|#define XMT_BC_OK_OV&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3:&t;Tx Broadcast Cnt Ov */
DECL|macro|XMT_OK_LO_OV
mdefine_line|#define XMT_OK_LO_OV&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;Octets Tx OK Low CntOv*/
DECL|macro|XMT_OK_HI_OV
mdefine_line|#define XMT_OK_HI_OV&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1:&t;Octets Tx OK Hi Cnt Ov*/
DECL|macro|XMT_OK_OV
mdefine_line|#define XMT_OK_OV&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Frames Tx Ok Ov */
DECL|macro|XMT_DEF_MSK
mdefine_line|#define XMT_DEF_MSK&t;0x00000006L&t;/* all bits excepting 1 and 2 */
multiline_comment|/*&n; * Receive Frame Status Encoding&n; */
DECL|macro|XMR_FS_LEN
mdefine_line|#define XMR_FS_LEN&t;(0x3fffUL&lt;&lt;18)&t;/* Bit 31..18:&t;Rx Frame Length */
DECL|macro|XMR_FS_2L_VLAN
mdefine_line|#define XMR_FS_2L_VLAN&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;tagged wh 2Lev VLAN ID*/
DECL|macro|XMR_FS_1L_VLAN
mdefine_line|#define XMR_FS_1L_VLAN&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;tagged wh 1Lev VLAN ID*/
DECL|macro|XMR_FS_BC
mdefine_line|#define XMR_FS_BC&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Broadcast Frame */
DECL|macro|XMR_FS_MC
mdefine_line|#define XMR_FS_MC&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;Multicast Frame */
DECL|macro|XMR_FS_UC
mdefine_line|#define XMR_FS_UC&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;Unicast Frame */
multiline_comment|/* Bit 12:&t;reserved */
DECL|macro|XMR_FS_BURST
mdefine_line|#define XMR_FS_BURST&t;(1L&lt;&lt;11)&t;/* Bit 11:&t;Burst Mode */
DECL|macro|XMR_FS_CEX_ERR
mdefine_line|#define XMR_FS_CEX_ERR&t;(1L&lt;&lt;10)&t;/* Bit 10:&t;Carrier Ext. Error */
DECL|macro|XMR_FS_802_3
mdefine_line|#define XMR_FS_802_3&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9:&t;802.3 Frame */
DECL|macro|XMR_FS_COL_ERR
mdefine_line|#define XMR_FS_COL_ERR&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8:&t;Collision Error */
DECL|macro|XMR_FS_CAR_ERR
mdefine_line|#define XMR_FS_CAR_ERR&t;(1L&lt;&lt;7)&t;&t;/* Bit&t;7:&t;Carrier Event Error */
DECL|macro|XMR_FS_LEN_ERR
mdefine_line|#define XMR_FS_LEN_ERR&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;In-Range Length Error */
DECL|macro|XMR_FS_FRA_ERR
mdefine_line|#define XMR_FS_FRA_ERR&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;Framing Error */
DECL|macro|XMR_FS_RUNT
mdefine_line|#define XMR_FS_RUNT&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Runt Error */
DECL|macro|XMR_FS_LNG_ERR
mdefine_line|#define XMR_FS_LNG_ERR&t;(1L&lt;&lt;3)&t;&t;/* Bit&t;3:&t;Gaint Error */
DECL|macro|XMR_FS_FCS_ERR
mdefine_line|#define XMR_FS_FCS_ERR&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;Frame Check Sequ Err */
DECL|macro|XMR_FS_ERR
mdefine_line|#define XMR_FS_ERR&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1:&t;Frame Error */
DECL|macro|XMR_FS_MCTRL
mdefine_line|#define XMR_FS_MCTRL&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;MAC Control Packet */
multiline_comment|/*&n; * XMR_FS_ERR will be set if&n; *&t;XMR_FS_FCS_ERR, XMR_FS_LNG_ERR, XMR_FS_RUNT,&n; *&t;XMR_FS_FRA_ERR, XMR_FS_LEN_ERR, or XMR_FS_CEX_ERR&n; * is set. XMR_FS_LNG_ERR and XMR_FS_LEN_ERR will issue&n; * XMR_FS_ERR unless the corresponding bit in the Receive Command&n; * Register is set.&n; */
DECL|macro|XMR_FS_ANY_ERR
mdefine_line|#define XMR_FS_ANY_ERR&t;XMR_FS_ERR
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * XMAC-PHY Registers, indirect addressed over the XMAC&n; */
DECL|macro|PHY_XMAC_CTRL
mdefine_line|#define&t;PHY_XMAC_CTRL&t;&t;0x00&t;/* 16 bit r/w&t;PHY Control Register */
DECL|macro|PHY_XMAC_STAT
mdefine_line|#define&t;PHY_XMAC_STAT&t;&t;0x01&t;/* 16 bit r/w&t;PHY Status Register */
DECL|macro|PHY_XMAC_ID0
mdefine_line|#define&t;PHY_XMAC_ID0&t;&t;0x02&t;/* 16 bit ro&t;PHY ID0 Register */
DECL|macro|PHY_XMAC_ID1
mdefine_line|#define&t;PHY_XMAC_ID1&t;&t;0x03&t;/* 16 bit ro&t;PHY ID1 Register */
DECL|macro|PHY_XMAC_AUNE_ADV
mdefine_line|#define&t;PHY_XMAC_AUNE_ADV&t;0x04&t;/* 16 bit r/w&t;Autoneg Advertisement */
DECL|macro|PHY_XMAC_AUNE_LP
mdefine_line|#define&t;PHY_XMAC_AUNE_LP&t;0x05&t;/* 16 bit ro&t;Link Partner Abi Reg */
DECL|macro|PHY_XMAC_AUNE_EXP
mdefine_line|#define&t;PHY_XMAC_AUNE_EXP&t;0x06&t;/* 16 bit ro&t;Autoneg Expansion Reg */
DECL|macro|PHY_XMAC_NEPG
mdefine_line|#define&t;PHY_XMAC_NEPG&t;&t;0x07&t;/* 16 bit r/w&t;Next Page Register */
DECL|macro|PHY_XMAC_NEPG_LP
mdefine_line|#define&t;PHY_XMAC_NEPG_LP&t;0x08&t;/* 16 bit ro&t;Next Page Link P Reg */
multiline_comment|/* 0x09 - 0x0e:&t;&t;reserved */
DECL|macro|PHY_XMAC_EXT_STAT
mdefine_line|#define&t;PHY_XMAC_EXT_STAT&t;0x0f&t;/* 16 bit ro&t;Ext Status Register */
DECL|macro|PHY_XMAC_RES_ABI
mdefine_line|#define&t;PHY_XMAC_RES_ABI&t;0x10&t;/* 16 bit ro&t;PHY Resolved Ability */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * Broadcom-PHY Registers, indirect addressed over XMAC&n; */
DECL|macro|PHY_BCOM_CTRL
mdefine_line|#define&t;PHY_BCOM_CTRL&t;&t;0x00&t;/* 16 bit r/w&t;PHY Control Register */
DECL|macro|PHY_BCOM_STAT
mdefine_line|#define&t;PHY_BCOM_STAT&t;&t;0x01&t;/* 16 bit ro&t;PHY Status Register */
DECL|macro|PHY_BCOM_ID0
mdefine_line|#define&t;PHY_BCOM_ID0&t;&t;0x02&t;/* 16 bit ro&t;PHY ID0 Register */
DECL|macro|PHY_BCOM_ID1
mdefine_line|#define&t;PHY_BCOM_ID1&t;&t;0x03&t;/* 16 bit ro&t;PHY ID1 Register */
DECL|macro|PHY_BCOM_AUNE_ADV
mdefine_line|#define&t;PHY_BCOM_AUNE_ADV&t;0x04&t;/* 16 bit r/w&t;Autoneg Advertisement */
DECL|macro|PHY_BCOM_AUNE_LP
mdefine_line|#define&t;PHY_BCOM_AUNE_LP&t;0x05&t;/* 16 bit ro&t;Link Part Ability Reg */
DECL|macro|PHY_BCOM_AUNE_EXP
mdefine_line|#define&t;PHY_BCOM_AUNE_EXP&t;0x06&t;/* 16 bit ro&t;Autoneg Expansion Reg */
DECL|macro|PHY_BCOM_NEPG
mdefine_line|#define&t;PHY_BCOM_NEPG&t;&t;0x07&t;/* 16 bit r/w&t;Next Page Register */
DECL|macro|PHY_BCOM_NEPG_LP
mdefine_line|#define&t;PHY_BCOM_NEPG_LP&t;0x08&t;/* 16 bit ro&t;Next Page Link P Reg */
multiline_comment|/* Broadcom-specific registers */
DECL|macro|PHY_BCOM_1000T_CTRL
mdefine_line|#define&t;PHY_BCOM_1000T_CTRL&t;0x09&t;/* 16 bit r/w&t;1000Base-T Ctrl Reg */
DECL|macro|PHY_BCOM_1000T_STAT
mdefine_line|#define&t;PHY_BCOM_1000T_STAT&t;0x0a&t;/* 16 bit ro&t;1000Base-T Status Reg */
multiline_comment|/* 0x0b - 0x0e:&t;&t;reserved */
DECL|macro|PHY_BCOM_EXT_STAT
mdefine_line|#define&t;PHY_BCOM_EXT_STAT&t;0x0f&t;/* 16 bit ro&t;Extended Status Reg */
DECL|macro|PHY_BCOM_P_EXT_CTRL
mdefine_line|#define&t;PHY_BCOM_P_EXT_CTRL&t;0x10&t;/* 16 bit r/w&t;PHY Extended Ctrl Reg */
DECL|macro|PHY_BCOM_P_EXT_STAT
mdefine_line|#define&t;PHY_BCOM_P_EXT_STAT&t;0x11&t;/* 16 bit ro&t;PHY Extended Stat Reg */
DECL|macro|PHY_BCOM_RE_CTR
mdefine_line|#define&t;PHY_BCOM_RE_CTR&t;&t;0x12&t;/* 16 bit r/w&t;Receive Error Counter */
DECL|macro|PHY_BCOM_FC_CTR
mdefine_line|#define&t;PHY_BCOM_FC_CTR&t;&t;0x13&t;/* 16 bit r/w&t;False Carr Sense Cnt */
DECL|macro|PHY_BCOM_RNO_CTR
mdefine_line|#define&t;PHY_BCOM_RNO_CTR&t;0x14&t;/* 16 bit r/w&t;Receiver NOT_OK Cnt */
multiline_comment|/* 0x15 - 0x17:&t;&t;reserved */
DECL|macro|PHY_BCOM_AUX_CTRL
mdefine_line|#define&t;PHY_BCOM_AUX_CTRL&t;0x18&t;/* 16 bit r/w&t;Auxiliary Control Reg */
DECL|macro|PHY_BCOM_AUX_STAT
mdefine_line|#define&t;PHY_BCOM_AUX_STAT&t;0x19&t;/* 16 bit ro&t;Auxiliary Stat Summary*/
DECL|macro|PHY_BCOM_INT_STAT
mdefine_line|#define&t;PHY_BCOM_INT_STAT&t;0x1a&t;/* 16 bit ro&t;Interrupt Status Reg */
DECL|macro|PHY_BCOM_INT_MASK
mdefine_line|#define&t;PHY_BCOM_INT_MASK&t;0x1b&t;/* 16 bit r/w&t;Interrupt Mask Reg */
multiline_comment|/* 0x1c:&t;&t;reserved */
multiline_comment|/* 0x1d - 0x1f:&t;&t;test registers */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * Level One-PHY Registers, indirect addressed over XMAC&n; */
DECL|macro|PHY_LONE_CTRL
mdefine_line|#define&t;PHY_LONE_CTRL&t;&t;0x00&t;/* 16 bit r/w&t;PHY Control Register */
DECL|macro|PHY_LONE_STAT
mdefine_line|#define&t;PHY_LONE_STAT&t;&t;0x01&t;/* 16 bit ro&t;PHY Status Register */
DECL|macro|PHY_LONE_ID0
mdefine_line|#define&t;PHY_LONE_ID0&t;&t;0x02&t;/* 16 bit ro&t;PHY ID0 Register */
DECL|macro|PHY_LONE_ID1
mdefine_line|#define&t;PHY_LONE_ID1&t;&t;0x03&t;/* 16 bit ro&t;PHY ID1 Register */
DECL|macro|PHY_LONE_AUNE_ADV
mdefine_line|#define&t;PHY_LONE_AUNE_ADV&t;0x04&t;/* 16 bit r/w&t;Autoneg Advertisement */
DECL|macro|PHY_LONE_AUNE_LP
mdefine_line|#define&t;PHY_LONE_AUNE_LP&t;0x05&t;/* 16 bit ro&t;Link Part Ability Reg */
DECL|macro|PHY_LONE_AUNE_EXP
mdefine_line|#define&t;PHY_LONE_AUNE_EXP&t;0x06&t;/* 16 bit ro&t;Autoneg Expansion Reg */
DECL|macro|PHY_LONE_NEPG
mdefine_line|#define&t;PHY_LONE_NEPG&t;&t;0x07&t;/* 16 bit r/w&t;Next Page Register */
DECL|macro|PHY_LONE_NEPG_LP
mdefine_line|#define&t;PHY_LONE_NEPG_LP&t;0x08&t;/* 16 bit ro&t;Next Page Link Partner*/
multiline_comment|/* Level One-specific registers */
DECL|macro|PHY_LONE_1000T_CTRL
mdefine_line|#define&t;PHY_LONE_1000T_CTRL&t;0x09&t;/* 16 bit r/w&t;1000Base-T Control Reg*/
DECL|macro|PHY_LONE_1000T_STAT
mdefine_line|#define&t;PHY_LONE_1000T_STAT&t;0x0a&t;/* 16 bit ro&t;1000Base-T Status Reg */
multiline_comment|/* 0x0b -0x0e:&t;&t;reserved */
DECL|macro|PHY_LONE_EXT_STAT
mdefine_line|#define&t;PHY_LONE_EXT_STAT&t;0x0f&t;/* 16 bit ro&t;Extended Status Reg */
DECL|macro|PHY_LONE_PORT_CFG
mdefine_line|#define&t;PHY_LONE_PORT_CFG&t;0x10&t;/* 16 bit r/w&t;Port Configuration Reg*/
DECL|macro|PHY_LONE_Q_STAT
mdefine_line|#define&t;PHY_LONE_Q_STAT&t;&t;0x11&t;/* 16 bit ro&t;Quick Status Reg */
DECL|macro|PHY_LONE_INT_ENAB
mdefine_line|#define&t;PHY_LONE_INT_ENAB&t;0x12&t;/* 16 bit r/w&t;Interrupt Enable Reg */
DECL|macro|PHY_LONE_INT_STAT
mdefine_line|#define&t;PHY_LONE_INT_STAT&t;0x13&t;/* 16 bit ro&t;Interrupt Status Reg */
DECL|macro|PHY_LONE_LED_CFG
mdefine_line|#define&t;PHY_LONE_LED_CFG&t;0x14&t;/* 16 bit r/w&t;LED Configuration Reg */
DECL|macro|PHY_LONE_PORT_CTRL
mdefine_line|#define&t;PHY_LONE_PORT_CTRL&t;0x15&t;/* 16 bit r/w&t;Port Control Reg */
DECL|macro|PHY_LONE_CIM
mdefine_line|#define&t;PHY_LONE_CIM&t;&t;0x16&t;/* 16 bit ro&t;CIM Reg */
multiline_comment|/* 0x17 -0x1c:&t;&t;reserved */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * National-PHY Registers, indirect addressed over XMAC&n; */
DECL|macro|PHY_NAT_CTRL
mdefine_line|#define&t;PHY_NAT_CTRL&t;&t;0x00&t;/* 16 bit r/w&t;PHY Control Register */
DECL|macro|PHY_NAT_STAT
mdefine_line|#define&t;PHY_NAT_STAT&t;&t;0x01&t;/* 16 bit r/w&t;PHY Status Register */
DECL|macro|PHY_NAT_ID0
mdefine_line|#define&t;PHY_NAT_ID0&t;&t;0x02&t;/* 16 bit ro&t;PHY ID0 Register */
DECL|macro|PHY_NAT_ID1
mdefine_line|#define&t;PHY_NAT_ID1&t;&t;0x03&t;/* 16 bit ro&t;PHY ID1 Register */
DECL|macro|PHY_NAT_AUNE_ADV
mdefine_line|#define&t;PHY_NAT_AUNE_ADV&t;0x04&t;/* 16 bit r/w&t;Autonegotiation Advertisement */
DECL|macro|PHY_NAT_AUNE_LP
mdefine_line|#define&t;PHY_NAT_AUNE_LP&t;&t;0x05&t;/* 16 bit ro&t;Link Partner Ability Reg */
DECL|macro|PHY_NAT_AUNE_EXP
mdefine_line|#define&t;PHY_NAT_AUNE_EXP&t;0x06&t;/* 16 bit ro&t;Autonegotiation Expansion Reg */
DECL|macro|PHY_NAT_NEPG
mdefine_line|#define&t;PHY_NAT_NEPG&t;&t;0x07&t;/* 16 bit r/w&t;Next Page Register */
DECL|macro|PHY_NAT_NEPG_LP
mdefine_line|#define&t;PHY_NAT_NEPG_LP&t;&t;0x08&t;/* 16 bit ro&t;Next Page Link Partner Reg */
multiline_comment|/* National-specific registers */
DECL|macro|PHY_NAT_1000T_CTRL
mdefine_line|#define&t;PHY_NAT_1000T_CTRL&t;0x09&t;/* 16 bit r/w&t;1000Base-T Control Reg */
DECL|macro|PHY_NAT_1000T_STAT
mdefine_line|#define&t;PHY_NAT_1000T_STAT&t;0x0a&t;/* 16 bit ro&t;1000Base-T Status Reg */
multiline_comment|/* 0x0b -0x0e:&t;&t;reserved */
DECL|macro|PHY_NAT_EXT_STAT
mdefine_line|#define&t;PHY_NAT_EXT_STAT&t;0x0f&t;/* 16 bit ro&t;Extended Status Register */
DECL|macro|PHY_NAT_EXT_CTRL1
mdefine_line|#define&t;PHY_NAT_EXT_CTRL1&t;0x10&t;/* 16 bit ro&t;Extended Control Reg1 */
DECL|macro|PHY_NAT_Q_STAT1
mdefine_line|#define&t;PHY_NAT_Q_STAT1&t;&t;0x11&t;/* 16 bit ro&t;Quick Status Reg1 */
DECL|macro|PHY_NAT_10B_OP
mdefine_line|#define&t;PHY_NAT_10B_OP&t;&t;0x12&t;/* 16 bit ro&t;10Base-T Operations Reg */
DECL|macro|PHY_NAT_EXT_CTRL2
mdefine_line|#define&t;PHY_NAT_EXT_CTRL2&t;0x13&t;/* 16 bit ro&t;Extended Control Reg1 */
DECL|macro|PHY_NAT_Q_STAT2
mdefine_line|#define&t;PHY_NAT_Q_STAT2&t;&t;0x14&t;/* 16 bit ro&t;Quick Status Reg2 */
multiline_comment|/* 0x15 -0x18:&t;&t;reserved */
DECL|macro|PHY_NAT_PHY_ADDR
mdefine_line|#define&t;PHY_NAT_PHY_ADDR&t;0x19&t;/* 16 bit ro&t;PHY Address Register */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/*&n; * PHY bit definitions&n; * Bits defined as PHY_X_..., PHY_B_..., PHY_L_... or PHY_N_... are&n; * Xmac/Broadcom/LevelOne/National-specific.&n; * All other are general.&n; */
multiline_comment|/*****&t;PHY_XMAC_CTRL&t;16 bit r/w&t;PHY Control Register *****/
multiline_comment|/*****&t;PHY_BCOM_CTRL&t;16 bit r/w&t;PHY Control Register *****/
multiline_comment|/*****&t;PHY_LONE_CTRL&t;16 bit r/w&t;PHY Control Register *****/
DECL|macro|PHY_CT_RESET
mdefine_line|#define&t;PHY_CT_RESET&t;(1&lt;&lt;15)&t;/* Bit 15: (sc)&t;clear all PHY releated regs */
DECL|macro|PHY_CT_LOOP
mdefine_line|#define PHY_CT_LOOP&t;(1&lt;&lt;14)&t;/* Bit 14:&t;enable Loopback over PHY */
DECL|macro|PHY_CT_SPS_LSB
mdefine_line|#define PHY_CT_SPS_LSB&t;(1&lt;&lt;13) /* Bit 13: (BC,L1) Speed select, lower bit */
DECL|macro|PHY_CT_ANE
mdefine_line|#define PHY_CT_ANE&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Autonegotiation Enabled */
DECL|macro|PHY_CT_PDOWN
mdefine_line|#define PHY_CT_PDOWN&t;(1&lt;&lt;11)&t;/* Bit 11: (BC,L1) Power Down Mode */
DECL|macro|PHY_CT_ISOL
mdefine_line|#define PHY_CT_ISOL&t;(1&lt;&lt;10)&t;/* Bit 10: (BC,L1) Isolate Mode */
DECL|macro|PHY_CT_RE_CFG
mdefine_line|#define PHY_CT_RE_CFG&t;(1&lt;&lt;9)&t;/* Bit&t;9: (sc) Restart Autonegotiation */
DECL|macro|PHY_CT_DUP_MD
mdefine_line|#define PHY_CT_DUP_MD&t;(1&lt;&lt;8)&t;/* Bit&t;8:&t;Duplex Mode */
DECL|macro|PHY_CT_COL_TST
mdefine_line|#define PHY_CT_COL_TST&t;(1&lt;&lt;7)&t;/* Bit&t;7: (BC,L1) Collsion Test enabled */
DECL|macro|PHY_CT_SPS_MSB
mdefine_line|#define PHY_CT_SPS_MSB&t;(1&lt;&lt;6)&t;/* Bit&t;6: (BC,L1) Speed select, upper bit */
multiline_comment|/* Bit&t;5..0:&t;reserved */
DECL|macro|PHY_B_CT_SP1000
mdefine_line|#define PHY_B_CT_SP1000&t;(1&lt;&lt;6)&t;/* Bit  6:&t;enable speed of 1000 MBit/s */
DECL|macro|PHY_B_CT_SP100
mdefine_line|#define PHY_B_CT_SP100&t;(1&lt;&lt;13)&t;/* Bit 13:&t;enable speed of  100 MBit/s */
DECL|macro|PHY_B_CT_SP10
mdefine_line|#define PHY_B_CT_SP10&t;(0)&t;/* Bit 6/13 not set,&t;speed of  10 MBit/s */
DECL|macro|PHY_L_CT_SP1000
mdefine_line|#define PHY_L_CT_SP1000&t;(1&lt;&lt;6)&t;/* Bit  6:      enable speed of 1000 MBit/s */
DECL|macro|PHY_L_CT_SP100
mdefine_line|#define PHY_L_CT_SP100&t;(1&lt;&lt;13)&t;/* Bit 13:      enable speed of  100 MBit/s */
DECL|macro|PHY_L_CT_SP10
mdefine_line|#define PHY_L_CT_SP10&t;(0)&t;/* Bit 6/13 not set,    speed of  10 MBit/s */
multiline_comment|/*****&t;PHY_XMAC_STAT&t;16 bit r/w&t;PHY Status Register *****/
multiline_comment|/*****&t;PHY_BCOM_STAT&t;16 bit r/w&t;PHY Status Register *****/
multiline_comment|/*****&t;PHY_LONE_STAT&t;16 bit r/w&t;PHY Status Register *****/
multiline_comment|/* Bit 15..9:&t;reserved */
multiline_comment|/*&t;(BC/L1) 100/10 MBit/s cap bits ignored*/
DECL|macro|PHY_ST_EXT_ST
mdefine_line|#define PHY_ST_EXT_ST&t;(1&lt;&lt;8)&t;/* Bit&t;8:&t;Extended Status Present */
multiline_comment|/* Bit&t;7:&t;reserved */
DECL|macro|PHY_ST_PRE_SUB
mdefine_line|#define PHY_ST_PRE_SUB&t;(1&lt;&lt;6)&t;/* Bit&t;6: (BC/L1) preamble suppression */
DECL|macro|PHY_ST_AN_OVER
mdefine_line|#define PHY_ST_AN_OVER&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Autonegotiation Over */
DECL|macro|PHY_ST_REM_FLT
mdefine_line|#define PHY_ST_REM_FLT&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;Remode Fault Condition Occured*/
DECL|macro|PHY_ST_AN_CAP
mdefine_line|#define PHY_ST_AN_CAP&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;Autonegotiation Capability */
DECL|macro|PHY_ST_LSYNC
mdefine_line|#define PHY_ST_LSYNC&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;Link Synchronized */
DECL|macro|PHY_ST_JAP_DET
mdefine_line|#define PHY_ST_JAP_DET&t;(1&lt;&lt;1)&t;/* Bit&t;1: (BC/L1) Japper Detected */
DECL|macro|PHY_ST_EXT_REG
mdefine_line|#define PHY_ST_EXT_REG&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Extended Register available */
multiline_comment|/*&t;PHY_XMAC_ID1&t;&t;16 bit ro&t;PHY ID1 Register */
multiline_comment|/*&t;PHY_BCOM_ID1&t;&t;16 bit ro&t;PHY ID1 Register */
multiline_comment|/*&t;PHY_LONE_ID1&t;&t;16 bit ro&t;PHY ID1 Register */
DECL|macro|PHY_I1_OUI
mdefine_line|#define&t;PHY_I1_OUI&t;(0x3f&lt;&lt;10)&t;/* Bit 15..10:&t;Organiz. Unique ID */
DECL|macro|PHY_I1_MOD_NUM
mdefine_line|#define PHY_I1_MOD_NUM&t;(0x3f&lt;&lt;4)&t;/* Bit&t;9.. 4:&t;Model Number */
DECL|macro|PHY_I1_REV
mdefine_line|#define PHY_I1_REV&t;(0x0f&lt;&lt;0)&t;/* Bit&t;3.. 0:&t;Revision Number */
multiline_comment|/*****&t;PHY_XMAC_AUNE_ADV&t;16 bit r/w&t;Autoneg Advertisement *****/
multiline_comment|/*****&t;PHY_XMAC_AUNE_LP&t;16 bit ro&t;Link Partner Ability Reg *****/
DECL|macro|PHY_AN_NXT_PG
mdefine_line|#define PHY_AN_NXT_PG&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Request Next Page */
DECL|macro|PHY_X_AN_ACK
mdefine_line|#define PHY_X_AN_ACK&t;(1&lt;&lt;14)&t;/* Bit 14: (ro)&t;Acknowledge Received */
DECL|macro|PHY_X_AN_RFB
mdefine_line|#define PHY_X_AN_RFB&t;(3&lt;&lt;12)&t;/* Bit 13..12:&t;Remode Fault Bits */
multiline_comment|/* Bit 11.. 9:&t;reserved */
DECL|macro|PHY_X_AN_PAUSE
mdefine_line|#define PHY_X_AN_PAUSE&t;(3&lt;&lt;7)&t;/* Bit&t;8.. 7:&t;Pause Bits */
DECL|macro|PHY_X_AN_HD
mdefine_line|#define PHY_X_AN_HD&t;(1&lt;&lt;6)&t;/* Bit&t;6:&t;Half Duplex */
DECL|macro|PHY_X_AN_FD
mdefine_line|#define PHY_X_AN_FD&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Full Duplex */
multiline_comment|/* Bit&t;4.. 0:&t;reserved */
multiline_comment|/*****&t;PHY_BCOM_AUNE_ADV&t;16 bit r/w&t;Autoneg Advertisement *****/
multiline_comment|/*****&t;PHY_BCOM_AUNE_LP&t;16 bit ro&t;Link Partner Ability Reg *****/
multiline_comment|/*&t;PHY_AN_NXT_PG&t;(see XMAC) Bit 15:&t;Request Next Page */
multiline_comment|/* Bit 14:&t;reserved */
DECL|macro|PHY_B_AN_RF
mdefine_line|#define PHY_B_AN_RF&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Remote Fault */
multiline_comment|/* Bit 12:&t;reserved */
DECL|macro|PHY_B_AN_ASP
mdefine_line|#define PHY_B_AN_ASP&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Asymetric Pause */
DECL|macro|PHY_B_AN_PC
mdefine_line|#define PHY_B_AN_PC&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Pause Capable */
multiline_comment|/* Bit&t;9..5:&t;100/10 BT cap bits ingnored */
DECL|macro|PHY_B_AN_SEL
mdefine_line|#define PHY_B_AN_SEL&t;(0x1f&lt;&lt;0)/* Bit 4..0:&t;Selector Field, 00001=Ethernet*/
multiline_comment|/*****&t;PHY_LONE_AUNE_ADV&t;16 bit r/w&t;Autoneg Advertisement *****/
multiline_comment|/*****&t;PHY_LONE_AUNE_LP&t;16 bit ro&t;Link Partner Ability Reg *****/
multiline_comment|/*&t;PHY_AN_NXT_PG&t;(see XMAC) Bit 15:&t;Request Next Page */
multiline_comment|/* Bit 14:&t;reserved */
DECL|macro|PHY_L_AN_RF
mdefine_line|#define PHY_L_AN_RF&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Remote Fault */
multiline_comment|/* Bit 12:&t;reserved */
DECL|macro|PHY_L_AN_ASP
mdefine_line|#define PHY_L_AN_ASP&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Asymetric Pause */
DECL|macro|PHY_L_AN_PC
mdefine_line|#define PHY_L_AN_PC&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Pause Capable */
multiline_comment|/* Bit&t;9..5:&t;100/10 BT cap bits ingnored */
DECL|macro|PHY_L_AN_SEL
mdefine_line|#define PHY_L_AN_SEL&t;(0x1f&lt;&lt;0)/* Bit 4..0:&t;Selector Field, 00001=Ethernet*/
multiline_comment|/*****&t;PHY_NAT_AUNE_ADV&t;16 bit r/w&t;Autoneg Advertisement *****/
multiline_comment|/*****&t;PHY_NAT_AUNE_LP&t;16 bit ro&t;Link Partner Ability Reg *****/
multiline_comment|/*&t;PHY_AN_NXT_PG&t;(see XMAC) Bit 15:&t;Request Next Page */
multiline_comment|/* Bit 14:&t;reserved */
DECL|macro|PHY_N_AN_RF
mdefine_line|#define PHY_N_AN_RF&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Remote Fault */
multiline_comment|/* Bit 12:&t;reserved */
DECL|macro|PHY_N_AN_100F
mdefine_line|#define PHY_N_AN_100F&t;(1&lt;&lt;11)&t;/* Bit 11:&t;100Base-T2 FD Support */
DECL|macro|PHY_N_AN_100H
mdefine_line|#define PHY_N_AN_100H&t;(1&lt;&lt;10)&t;/* Bit 10:&t;100Base-T2 HD Support */
multiline_comment|/* Bit&t;9..5:&t;100/10 BT cap bits ingnored */
DECL|macro|PHY_N_AN_SEL
mdefine_line|#define PHY_N_AN_SEL&t;(0x1f&lt;&lt;0)/* Bit 4..0:&t;Selector Field, 00001=Ethernet*/
multiline_comment|/* field type definition for PHY_x_AN_SEL */
DECL|macro|PHY_SEL_TYPE
mdefine_line|#define PHY_SEL_TYPE&t;0x01&t;/* 00001 = Ethernet */
multiline_comment|/*****&t;PHY_XMAC_AUNE_EXP&t;16 bit ro&t;Autoneg Expansion Reg *****/
multiline_comment|/* Bit 15..4:&t;reserved */
DECL|macro|PHY_AN_LP_NP
mdefine_line|#define PHY_AN_LP_NP&t;(1&lt;&lt;3)&t;/* Bit&t;3:&t;Link Partner can Next Page */
DECL|macro|PHY_AN_LOC_NP
mdefine_line|#define PHY_AN_LOC_NP&t;(1&lt;&lt;2)&t;/* Bit&t;2:&t;Local PHY can Next Page */
DECL|macro|PHY_AN_RX_PG
mdefine_line|#define PHY_AN_RX_PG&t;(1&lt;&lt;1)&t;/* Bit&t;1:&t;Page Received */
multiline_comment|/* Bit&t;0:&t;reserved */
multiline_comment|/*****&t;PHY_BCOM_AUNE_EXP&t;16 bit ro&t;Autoneg Expansion Reg *****/
multiline_comment|/* Bit 15..5:&t;reserved */
DECL|macro|PHY_B_AN_PDF
mdefine_line|#define PHY_B_AN_PDF&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;Parallel Detection Fault */
multiline_comment|/*&t;PHY_AN_LP_NP&t;(see XMAC) Bit&t;3:&t;Link Partner can Next Page */
multiline_comment|/*&t;PHY_AN_LOC_NP&t;(see XMAC) Bit&t;2:&t;Local PHY can Next Page */
multiline_comment|/*&t;PHY_AN_RX_PG&t;(see XMAC) Bit&t;1:&t;Page Received */
DECL|macro|PHY_B_AN_LP_CAP
mdefine_line|#define PHY_B_AN_LP_CAP&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Link Partner Autoneg Cap. */ &t;
multiline_comment|/*****&t;PHY_LONE_AUNE_EXP&t;16 bit ro&t;Autoneg Expansion Reg *****/
DECL|macro|PHY_L_AN_BP
mdefine_line|#define PHY_L_AN_BP&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Base Page Indication */
DECL|macro|PHY_L_AN_PDF
mdefine_line|#define PHY_L_AN_PDF&t;(1&lt;&lt;4)&t;/* Bit&t;4:&t;Parallel Detection Fault */
multiline_comment|/*&t;PHY_AN_LP_NP&t;(see XMAC) Bit&t;3:&t;Link Partner can Next Page */
multiline_comment|/*&t;PHY_AN_LOC_NP&t;(see XMAC) Bit&t;2:&t;Local PHY can Next Page */
multiline_comment|/*&t;PHY_AN_RX_PG&t;(see XMAC) Bit&t;1:&t;Page Received */
DECL|macro|PHY_B_AN_LP_CAP
mdefine_line|#define PHY_B_AN_LP_CAP&t;(1&lt;&lt;0)&t;/* Bit&t;0:&t;Link Partner Autoneg Cap. */ &t;
multiline_comment|/*****&t;PHY_XMAC_NEPG&t;&t;16 bit r/w&t;Next Page Register *****/
multiline_comment|/*****&t;PHY_BCOM_NEPG&t;&t;16 bit r/w&t;Next Page Register *****/
multiline_comment|/*****&t;PHY_LONE_NEPG&t;&t;16 bit r/w&t;Next Page Register *****/
multiline_comment|/*****&t;PHY_XMAC_NEPG_LP&t;16 bit ro&t;Next Page Link Partner *****/
multiline_comment|/*****&t;PHY_BCOM_NEPG_LP&t;16 bit ro&t;Next Page Link Partner *****/
multiline_comment|/*****&t;PHY_LONE_NEPG_LP&t;16 bit ro&t;Next Page Link Partner *****/
DECL|macro|PHY_NP_MORE
mdefine_line|#define PHY_NP_MORE&t;(1&lt;&lt;15)&t;/* Bit 15:&t;More, Next Pages to follow */
DECL|macro|PHY_NP_ACK1
mdefine_line|#define PHY_NP_ACK1&t;(1&lt;&lt;14)&t;/* Bit 14: (ro)&t;Ack 1, for receiving a message*/
DECL|macro|PHY_NP_MSG_VAL
mdefine_line|#define PHY_NP_MSG_VAL&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Message Page valid */
DECL|macro|PHY_NP_ACK2
mdefine_line|#define PHY_NP_ACK2&t;(1&lt;&lt;12)&t;/* Bit 12:&t;Ack 2, comply with msg content*/
DECL|macro|PHY_NP_TOG
mdefine_line|#define PHY_NP_TOG&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Toggle Bit, ensure sync */
DECL|macro|PHY_NP_MSG
mdefine_line|#define PHY_NP_MSG&t;0x07ff&t;/* Bit 10..0:&t;Message from/to Link Partner */
multiline_comment|/*&n; * XMAC-Specific&n; */
multiline_comment|/*****&t;PHY_XMAC_EXT_STAT&t;16 bit r/w&t;Extended Status Register *****/
DECL|macro|PHY_X_EX_FD
mdefine_line|#define PHY_X_EX_FD&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Device Supports Full Duplex */
DECL|macro|PHY_X_EX_HD
mdefine_line|#define PHY_X_EX_HD&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Device Supports Half Duplex */
multiline_comment|/* Bit 13..0:&t;reserved */
multiline_comment|/*****&t;PHY_XMAC_RES_ABI&t;16 bit ro&t;PHY Resolved Ability *****/
multiline_comment|/* Bit 15..9:&t;reserved */
DECL|macro|PHY_X_RS_PAUSE
mdefine_line|#define PHY_X_RS_PAUSE&t;(3&lt;&lt;7)&t;/* Bit&t;8..7:&t;selected Pause Mode */
DECL|macro|PHY_X_RS_HD
mdefine_line|#define PHY_X_RS_HD&t;(1&lt;&lt;6)&t;/* Bit&t;6:&t;Half Duplex Mode selected */
DECL|macro|PHY_X_RS_FD
mdefine_line|#define PHY_X_RS_FD&t;(1&lt;&lt;5)&t;/* Bit&t;5:&t;Full Duplex Mode selected */
DECL|macro|PHY_X_RS_ABLMIS
mdefine_line|#define PHY_X_RS_ABLMIS (1&lt;&lt;4)&t;/* Bit&t;4:&t;duplex or pause cap mismatch */
DECL|macro|PHY_X_RS_PAUMIS
mdefine_line|#define PHY_X_RS_PAUMIS (1&lt;&lt;3)&t;/* Bit&t;3:&t;pause capability missmatch */
multiline_comment|/* Bit&t;2..0:&t;reserved */
multiline_comment|/*&n; * Remote Fault Bits (PHY_X_AN_RFB) encoding&n; */
DECL|macro|X_RFB_OK
mdefine_line|#define X_RFB_OK&t;(0&lt;&lt;12)&t;/* Bit 12..13&t;No errors, Link OK */
DECL|macro|X_RFB_LF
mdefine_line|#define X_RFB_LF&t;(1&lt;&lt;12)&t;/* Bit 12..13&t;Link Failure */
DECL|macro|X_RFB_OFF
mdefine_line|#define X_RFB_OFF&t;(2&lt;&lt;12)&t;/* Bit 12..13&t;Offline */
DECL|macro|X_RFB_AN_ERR
mdefine_line|#define X_RFB_AN_ERR&t;(3&lt;&lt;12)&t;/* Bit 12..13&t;Autonegotiation Error */
multiline_comment|/*&n; * Pause Bits (PHY_X_AN_PAUSE and PHY_X_RS_PAUSE) encoding&n; */
DECL|macro|PHY_X_P_NO_PAUSE
mdefine_line|#define PHY_X_P_NO_PAUSE&t;(0&lt;&lt;7)&t;/* Bit&t;8..7:&t;no Pause Mode */
DECL|macro|PHY_X_P_SYM_MD
mdefine_line|#define PHY_X_P_SYM_MD&t;&t;(1&lt;&lt;7)&t;/* Bit&t;8..7:&t;symmetric Pause Mode */
DECL|macro|PHY_X_P_ASYM_MD
mdefine_line|#define PHY_X_P_ASYM_MD&t;&t;(2&lt;&lt;7)&t;/* Bit&t;8..7:&t;asymmetric Pause Mode */
DECL|macro|PHY_X_P_BOTH_MD
mdefine_line|#define PHY_X_P_BOTH_MD&t;&t;(3&lt;&lt;7)&t;/* Bit&t;8..7:&t;both Pause Mode */
multiline_comment|/*&n; * Broadcom-Specific&n; */
multiline_comment|/***** PHY_BCOM_1000T_CTRL&t;16 bit r/w&t;1000Base-T Control Reg *****/
DECL|macro|PHY_B_1000C_TEST
mdefine_line|#define PHY_B_1000C_TEST&t;(7&lt;&lt;13)&t;/* Bit&t;15..13:&t;Test Modes */
DECL|macro|PHY_B_1000C_MSE
mdefine_line|#define PHY_B_1000C_MSE&t;&t;(1&lt;&lt;12)&t;/* Bit&t;12:&t;Master/Slave Enable */
DECL|macro|PHY_B_1000C_MSC
mdefine_line|#define PHY_B_1000C_MSC&t;&t;(1&lt;&lt;11)&t;/* Bit&t;11:&t;M/S Configuration */
DECL|macro|PHY_B_1000C_RD
mdefine_line|#define PHY_B_1000C_RD&t;&t;(1&lt;&lt;10)&t;/* Bit&t;10:&t;Repeater/DTE */
DECL|macro|PHY_B_1000C_AFD
mdefine_line|#define PHY_B_1000C_AFD&t;&t;(1&lt;&lt;9)&t;/* Bit&t;9:&t;Advertise Full Duplex */
DECL|macro|PHY_B_1000C_AHD
mdefine_line|#define PHY_B_1000C_AHD&t;&t;(1&lt;&lt;8)&t;/* Bit&t;8:&t;Advertise Half Duplex */
multiline_comment|/* Bit&t;7..0:&t;reserved */
multiline_comment|/***** PHY_BCOM_1000T_STAT&t;16 bit ro&t;1000Base-T Status Reg *****/
DECL|macro|PHY_B_1000S_MSF
mdefine_line|#define PHY_B_1000S_MSF&t;&t;(1&lt;&lt;15)&t;/* Bit&t;15:&t;Master/Slave Fault */
DECL|macro|PHY_B_1000S_MSR
mdefine_line|#define PHY_B_1000S_MSR&t;&t;(1&lt;&lt;14)&t;/* Bit&t;14:&t;Master/Slave Result */
DECL|macro|PHY_B_1000S_LRS
mdefine_line|#define PHY_B_1000S_LRS&t;&t;(1&lt;&lt;13)&t;/* Bit&t;13:&t;Local Receiver Status */
DECL|macro|PHY_B_1000S_RRS
mdefine_line|#define PHY_B_1000S_RRS&t;&t;(1&lt;&lt;12)&t;/* Bit&t;12:&t;Remote Receiver Status */
DECL|macro|PHY_B_1000S_LP_FD
mdefine_line|#define PHY_B_1000S_LP_FD&t;(1&lt;&lt;11)&t;/* Bit&t;11:&t;Link Partner can FD */
DECL|macro|PHY_B_1000S_LP_HD
mdefine_line|#define PHY_B_1000S_LP_HD&t;(1&lt;&lt;10)&t;/* Bit&t;10:&t;Link Partner can HD */
multiline_comment|/* Bit&t;9..8:&t;reserved */
DECL|macro|PHY_B_1000S_IEC
mdefine_line|#define PHY_B_1000S_IEC&t;&t;(255&lt;&lt;0)/* Bit&t;7..0:&t;Idle Error Count */
multiline_comment|/*****&t;PHY_BCOM_EXT_STAT&t;16 bit ro&t;Extended Status Register *****/
DECL|macro|PHY_B_ES_X_FD_CAP
mdefine_line|#define PHY_B_ES_X_FD_CAP&t;(1&lt;&lt;15)&t;/* Bit 15:&t;1000Base-X FD capable */
DECL|macro|PHY_B_ES_X_HD_CAP
mdefine_line|#define PHY_B_ES_X_HD_CAP&t;(1&lt;&lt;14)&t;/* Bit 14:&t;1000Base-X HD capable */
DECL|macro|PHY_B_ES_T_FD_CAP
mdefine_line|#define PHY_B_ES_T_FD_CAP&t;(1&lt;&lt;13)&t;/* Bit 13:&t;1000Base-T FD capable */
DECL|macro|PHY_B_ES_T_HD_CAP
mdefine_line|#define PHY_B_ES_T_HD_CAP&t;(1&lt;&lt;12)&t;/* Bit 12:&t;1000Base-T HD capable */
multiline_comment|/* Bit 11..0:&t;reserved */
multiline_comment|/*****&t;PHY_BCOM_P_EXT_CTRL&t;16 bit r/w&t;PHY Extended Control Reg *****/
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
mdefine_line|#define PHY_B_PEC_BY_SCR&t;(1&lt;&lt;9)&t;/* Bit 9:&t;Bypass Scrambler */
DECL|macro|PHY_B_PEC_BY_MLT3
mdefine_line|#define PHY_B_PEC_BY_MLT3&t;(1&lt;&lt;8)&t;/* Bit 8:&t;Bypass MLT3 Encoder */
DECL|macro|PHY_B_PEC_BY_RXA
mdefine_line|#define PHY_B_PEC_BY_RXA&t;(1&lt;&lt;7)&t;/* Bit 7:&t;Bypass Rx Alignm. */
DECL|macro|PHY_B_PEC_RES_SCR
mdefine_line|#define PHY_B_PEC_RES_SCR&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Reset Scrambler */
DECL|macro|PHY_B_PEC_EN_LTR
mdefine_line|#define PHY_B_PEC_EN_LTR&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Ena LED Traffic Mode */
DECL|macro|PHY_B_PEC_LED_ON
mdefine_line|#define PHY_B_PEC_LED_ON&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Force LED&squot;s on */
DECL|macro|PHY_B_PEC_LED_OFF
mdefine_line|#define PHY_B_PEC_LED_OFF&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Force LED&squot;s off */
DECL|macro|PHY_B_PEC_EX_IPG
mdefine_line|#define PHY_B_PEC_EX_IPG&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Extend Tx IPG Mode */
DECL|macro|PHY_B_PEC_3_LED
mdefine_line|#define PHY_B_PEC_3_LED&t;&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Three Link LED mode */
DECL|macro|PHY_B_PEC_HIGH_LA
mdefine_line|#define PHY_B_PEC_HIGH_LA&t;(1&lt;&lt;0)&t;/* Bit 0:&t;GMII Fifo Elasticy */
multiline_comment|/*****&t;PHY_BCOM_P_EXT_STAT&t;16 bit ro&t;PHY Extended Status Reg *****/
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
mdefine_line|#define PHY_B_PES_LOCKED&t;(1&lt;&lt;9)&t;/* Bit 9:&t;Locked */
DECL|macro|PHY_B_PES_LS
mdefine_line|#define PHY_B_PES_LS&t;&t;(1&lt;&lt;8)&t;/* Bit 8:&t;Link Status */
DECL|macro|PHY_B_PES_RF
mdefine_line|#define PHY_B_PES_RF&t;&t;(1&lt;&lt;7)&t;/* Bit 7:&t;Remote Fault */
DECL|macro|PHY_B_PES_CE_ER
mdefine_line|#define PHY_B_PES_CE_ER&t;&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Carrier Ext Error */
DECL|macro|PHY_B_PES_BAD_SSD
mdefine_line|#define PHY_B_PES_BAD_SSD&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Bad SSD */
DECL|macro|PHY_B_PES_BAD_ESD
mdefine_line|#define PHY_B_PES_BAD_ESD&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Bad ESD */
DECL|macro|PHY_B_PES_RX_ER
mdefine_line|#define PHY_B_PES_RX_ER&t;&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Receive Error */
DECL|macro|PHY_B_PES_TX_ER
mdefine_line|#define PHY_B_PES_TX_ER&t;&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Transmit Error */
DECL|macro|PHY_B_PES_LOCK_ER
mdefine_line|#define PHY_B_PES_LOCK_ER&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Lock Error */
DECL|macro|PHY_B_PES_MLT3_ER
mdefine_line|#define PHY_B_PES_MLT3_ER&t;(1&lt;&lt;0)&t;/* Bit 0:&t;MLT3 code Error */
multiline_comment|/*****&t;PHY_BCOM_FC_CTR&t;&t;16 bit r/w&t;False Carrier Counter *****/
multiline_comment|/* Bit 15..8:&t;reserved */
DECL|macro|PHY_B_FC_CTR
mdefine_line|#define PHY_B_FC_CTR&t;&t;(255&lt;&lt;0)/* Bit 7..0:&t;False Carrier Counter */
multiline_comment|/*****&t;PHY_BCOM_RNO_CTR&t;16 bit r/w&t;Receive NOT_OK Counter *****/
DECL|macro|PHY_B_RC_LOC
mdefine_line|#define PHY_B_RC_LOC&t;&t;(255&lt;&lt;8)/* Bit 15..8:&t;Local Rx NOT_OK cnt */
DECL|macro|PHY_B_RC_REM
mdefine_line|#define PHY_B_RC_REM&t;&t;(255&lt;&lt;0)/* Bit  7..0:&t;Remote Rx NOT_OK cnt */
multiline_comment|/*****&t;PHY_BCOM_AUX_CTRL&t;16 bit r/w&t;Auxiliary Control Reg *****/
DECL|macro|PHY_B_AC_L_SQE
mdefine_line|#define PHY_B_AC_L_SQE&t;&t;(1&lt;&lt;15)&t;/* Bit 15:&t;Low Squelch */
DECL|macro|PHY_B_AC_LONG_PACK
mdefine_line|#define PHY_B_AC_LONG_PACK&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Rx Long Packets */
DECL|macro|PHY_B_AC_ER_CTRL
mdefine_line|#define PHY_B_AC_ER_CTRL&t;(3&lt;&lt;12)&t;/* Bit 13..12:&t;Edgerate Control */
multiline_comment|/* Bit 11:&t;reserved */
DECL|macro|PHY_B_AC_TX_TST
mdefine_line|#define PHY_B_AC_TX_TST&t;&t;(1&lt;&lt;10) /* Bit 10:&t;tx test bit, always 1 */
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
multiline_comment|/*****&t;PHY_BCOM_AUX_STAT&t;16 bit ro&t;Auxiliary Status Reg *****/
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
DECL|macro|PHY_B_AS_AN_RES
mdefine_line|#define PHY_B_AS_AN_RES&t;&t;(7&lt;&lt;8)&t;/* Bit 10..8:&t;AN HDC */
DECL|macro|PHY_B_AS_PDF
mdefine_line|#define PHY_B_AS_PDF&t;&t;(1&lt;&lt;7)&t;/* Bit 7:&t;Parallel Detect. Fault*/
DECL|macro|PHY_B_AS_RF
mdefine_line|#define PHY_B_AS_RF&t;&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Remote Fault */
DECL|macro|PHY_B_AS_ANP_R
mdefine_line|#define PHY_B_AS_ANP_R&t;&t;(1&lt;&lt;5)&t;/* Bit 5:&t;AN Page Received */
DECL|macro|PHY_B_AS_LP_ANAB
mdefine_line|#define PHY_B_AS_LP_ANAB&t;(1&lt;&lt;4)&t;/* Bit 4:&t;LP AN Ability */
DECL|macro|PHY_B_AS_LP_NPAB
mdefine_line|#define PHY_B_AS_LP_NPAB&t;(1&lt;&lt;3)&t;/* Bit 3:&t;LP Next Page Ability */
DECL|macro|PHY_B_AS_LS
mdefine_line|#define PHY_B_AS_LS&t;&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Link Status */
DECL|macro|PHY_B_AS_PRR
mdefine_line|#define PHY_B_AS_PRR&t;&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Pause Resolution-Rx */
DECL|macro|PHY_B_AS_PRT
mdefine_line|#define PHY_B_AS_PRT&t;&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Pause Resolution-Tx */
multiline_comment|/*****&t;PHY_BCOM_INT_STAT&t;16 bit ro&t;Interrupt Status Reg *****/
multiline_comment|/*****&t;PHY_BCOM_INT_MASK&t;16 bit r/w&t;Interrupt Mask Reg *****/
multiline_comment|/* Bit 15:&t;reserved */
DECL|macro|PHY_B_IS_PSE
mdefine_line|#define PHY_B_IS_PSE&t;&t;(1&lt;&lt;14)&t;/* Bit 14:&t;Pair Swap Error */
DECL|macro|PHY_B_IS_MDXI_SC
mdefine_line|#define PHY_B_IS_MDXI_SC&t;(1&lt;&lt;13)&t;/* Bit 13:&t;MDIX Status Change */
DECL|macro|PHY_B_IS_HCT
mdefine_line|#define PHY_B_IS_HCT&t;&t;(1&lt;&lt;12)&t;/* Bit 12:&t;counter above 32k */
DECL|macro|PHY_B_IS_LCT
mdefine_line|#define PHY_B_IS_LCT&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;all counter below 128 */
DECL|macro|PHY_B_IS_AN_PR
mdefine_line|#define PHY_B_IS_AN_PR&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Page Received */
DECL|macro|PHY_B_IS_NO_HDCL
mdefine_line|#define PHY_B_IS_NO_HDCL&t;(1&lt;&lt;9)&t;/* Bit 9:&t;No HCD Link */
DECL|macro|PHY_B_IS_NO_HDC
mdefine_line|#define PHY_B_IS_NO_HDC&t;&t;(1&lt;&lt;8)&t;/* Bit 8:&t;No HCD */
DECL|macro|PHY_B_IS_NEG_USHDC
mdefine_line|#define PHY_B_IS_NEG_USHDC&t;(1&lt;&lt;7)&t;/* Bit 7:&t;Negotiated Unsup. HCD */
DECL|macro|PHY_B_IS_SCR_S_ER
mdefine_line|#define PHY_B_IS_SCR_S_ER&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Scrambler Sync Error */
DECL|macro|PHY_B_IS_RRS_CHANGE
mdefine_line|#define PHY_B_IS_RRS_CHANGE&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Remote Rx Stat Change */
DECL|macro|PHY_B_IS_LRS_CHANGE
mdefine_line|#define PHY_B_IS_LRS_CHANGE&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Local Rx Stat Change */
DECL|macro|PHY_B_IS_DUP_CHANGE
mdefine_line|#define PHY_B_IS_DUP_CHANGE&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Duplex Mode Change */
DECL|macro|PHY_B_IS_LSP_CHANGE
mdefine_line|#define PHY_B_IS_LSP_CHANGE&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Link Speed Change */
DECL|macro|PHY_B_IS_LST_CHANGE
mdefine_line|#define PHY_B_IS_LST_CHANGE&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Link Status Changed */
DECL|macro|PHY_B_IS_CRC_ER
mdefine_line|#define PHY_B_IS_CRC_ER&t;&t;(1&lt;&lt;0)&t;/* Bit 0:&t;CRC Error */
DECL|macro|PHY_B_DEF_MSK
mdefine_line|#define PHY_B_DEF_MSK&t;(~(PHY_B_IS_AN_PR | PHY_B_IS_LST_CHANGE))
multiline_comment|/*&n; * Pause Bits (PHY_B_AN_ASP and PHY_B_AN_PC) encoding&n; */
DECL|macro|PHY_B_P_NO_PAUSE
mdefine_line|#define PHY_B_P_NO_PAUSE&t;(0&lt;&lt;10)&t;/* Bit&t;11..10:&t;no Pause Mode */
DECL|macro|PHY_B_P_SYM_MD
mdefine_line|#define PHY_B_P_SYM_MD&t;&t;(1&lt;&lt;10)&t;/* Bit&t;11..10:&t;symmetric Pause Mode */
DECL|macro|PHY_B_P_ASYM_MD
mdefine_line|#define PHY_B_P_ASYM_MD&t;&t;(2&lt;&lt;10)&t;/* Bit&t;11..10:&t;asymmetric Pause Mode */
DECL|macro|PHY_B_P_BOTH_MD
mdefine_line|#define PHY_B_P_BOTH_MD&t;&t;(3&lt;&lt;10)&t;/* Bit&t;11..10:&t;both Pause Mode */
multiline_comment|/*&n; * Resolved Duplex mode and Capabilities (Aux Status Summary Reg)&n; */
DECL|macro|PHY_B_RES_1000FD
mdefine_line|#define&t;PHY_B_RES_1000FD&t;(7&lt;&lt;8)&t;/* Bit&t;10..8:&t;1000Base-T Full Dup. */
DECL|macro|PHY_B_RES_1000HD
mdefine_line|#define&t;PHY_B_RES_1000HD&t;(6&lt;&lt;8)&t;/* Bit&t;10..8:&t;1000Base-T Half Dup. */
multiline_comment|/* others: 100/10: invalid for us */
multiline_comment|/*&n; * Level One-Specific&n; */
multiline_comment|/*****&t;PHY_LONE_1000T_CTRL&t;16 bit r/w&t;1000Base-T Control Reg *****/
DECL|macro|PHY_L_1000C_TEST
mdefine_line|#define PHY_L_1000C_TEST&t;(7&lt;&lt;13)&t;/* Bit&t;15..13:&t;Test Modes */
DECL|macro|PHY_L_1000C_MSE
mdefine_line|#define PHY_L_1000C_MSE&t;&t;(1&lt;&lt;12)&t;/* Bit&t;12:&t;Master/Slave Enable */
DECL|macro|PHY_L_1000C_MSC
mdefine_line|#define PHY_L_1000C_MSC&t;&t;(1&lt;&lt;11)&t;/* Bit&t;11:&t;M/S Configuration */
DECL|macro|PHY_L_1000C_RD
mdefine_line|#define PHY_L_1000C_RD&t;&t;(1&lt;&lt;10)&t;/* Bit&t;10:&t;Repeater/DTE */
DECL|macro|PHY_L_1000C_AFD
mdefine_line|#define PHY_L_1000C_AFD&t;&t;(1&lt;&lt;9)&t;/* Bit&t;9:&t;Advertise Full Duplex */
DECL|macro|PHY_L_1000C_AHD
mdefine_line|#define PHY_L_1000C_AHD&t;&t;(1&lt;&lt;8)&t;/* Bit&t;8:&t;Advertise Half Duplex */
multiline_comment|/* Bit&t;7..0:&t;reserved */
multiline_comment|/*****&t;PHY_LONE_1000T_STAT&t;16 bit ro&t;1000Base-T Status Reg *****/
DECL|macro|PHY_L_1000S_MSF
mdefine_line|#define PHY_L_1000S_MSF&t;&t;(1&lt;&lt;15)&t;/* Bit&t;15:&t;Master/Slave Fault */
DECL|macro|PHY_L_1000S_MSR
mdefine_line|#define PHY_L_1000S_MSR&t;&t;(1&lt;&lt;14)&t;/* Bit&t;14:&t;Master/Slave Result */
DECL|macro|PHY_L_1000S_LRS
mdefine_line|#define PHY_L_1000S_LRS&t;&t;(1&lt;&lt;13)&t;/* Bit&t;13:&t;Local Receiver Status */
DECL|macro|PHY_L_1000S_RRS
mdefine_line|#define PHY_L_1000S_RRS&t;&t;(1&lt;&lt;12)&t;/* Bit&t;12:&t;Remote Receiver Status*/
DECL|macro|PHY_L_1000S_LP_FD
mdefine_line|#define PHY_L_1000S_LP_FD&t;(1&lt;&lt;11)&t;/* Bit&t;11:&t;Link Partner can FD */
DECL|macro|PHY_L_1000S_LP_HD
mdefine_line|#define PHY_L_1000S_LP_HD&t;(1&lt;&lt;10)&t;/* Bit&t;10:&t;Link Partner can HD */
multiline_comment|/* Bit&t;9..8:&t;reserved */
DECL|macro|PHY_B_1000S_IEC
mdefine_line|#define PHY_B_1000S_IEC&t;&t;(255&lt;&lt;0)/* Bit&t;7..0:&t;Idle Error Count */
multiline_comment|/*****&t;PHY_LONE_EXT_STAT&t;16 bit ro&t;Extended Status Register *****/
DECL|macro|PHY_L_ES_X_FD_CAP
mdefine_line|#define PHY_L_ES_X_FD_CAP&t;(1&lt;&lt;15)&t;/* Bit 15:&t;1000Base-X FD capable */
DECL|macro|PHY_L_ES_X_HD_CAP
mdefine_line|#define PHY_L_ES_X_HD_CAP&t;(1&lt;&lt;14)&t;/* Bit 14:&t;1000Base-X HD capable */
DECL|macro|PHY_L_ES_T_FD_CAP
mdefine_line|#define PHY_L_ES_T_FD_CAP&t;(1&lt;&lt;13)&t;/* Bit 13:&t;1000Base-T FD capable */
DECL|macro|PHY_L_ES_T_HD_CAP
mdefine_line|#define PHY_L_ES_T_HD_CAP&t;(1&lt;&lt;12)&t;/* Bit 12:&t;1000Base-T HD capable */
multiline_comment|/* Bit 11..0:&t;reserved */
multiline_comment|/*****&t;PHY_LONE_PORT_CFG&t;16 bit r/w&t;Port Configuration Reg *****/
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
mdefine_line|#define PHY_L_PC_SQE&t;&t;(1&lt;&lt;9)&t;/* Bit 9:&t;Enable Heartbeat */
DECL|macro|PHY_L_PC_TP_LOOP
mdefine_line|#define PHY_L_PC_TP_LOOP&t;(1&lt;&lt;8)&t;/* Bit 8:&t;TP Loopback */
DECL|macro|PHY_L_PC_SSS
mdefine_line|#define PHY_L_PC_SSS&t;&t;(1&lt;&lt;7)&t;/* Bit 7:&t;Smart Speed Selection */
DECL|macro|PHY_L_PC_FIFO_SIZE
mdefine_line|#define PHY_L_PC_FIFO_SIZE&t;(1&lt;&lt;6)&t;/* Bit 6:&t;FIFO Size */
DECL|macro|PHY_L_PC_PRE_EN
mdefine_line|#define PHY_L_PC_PRE_EN&t;&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Preamble Enable */
DECL|macro|PHY_L_PC_CIM
mdefine_line|#define PHY_L_PC_CIM&t;&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Carrier Integrity Mon */
DECL|macro|PHY_L_PC_10_SER
mdefine_line|#define PHY_L_PC_10_SER&t;&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Use Serial Output */
DECL|macro|PHY_L_PC_ANISOL
mdefine_line|#define PHY_L_PC_ANISOL&t;&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Unisolate Port */
DECL|macro|PHY_L_PC_TEN_BIT
mdefine_line|#define PHY_L_PC_TEN_BIT&t;(1&lt;&lt;1)&t;/* Bit 1:&t;10bit iface mode on */
DECL|macro|PHY_L_PC_ALTCLOCK
mdefine_line|#define PHY_L_PC_ALTCLOCK&t;(1&lt;&lt;0)&t;/* Bit 0: (ro)&t;ALTCLOCK Mode on */
multiline_comment|/*****&t;PHY_LONE_Q_STAT&t;&t;16 bit ro&t;Quick Status Reg *****/
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
mdefine_line|#define PHY_L_QS_DUP_MOD&t;(1&lt;&lt;9)&t;/* Bit 9:&t;Full/Half Duplex */
DECL|macro|PHY_L_QS_AN
mdefine_line|#define PHY_L_QS_AN&t;&t;(1&lt;&lt;8)&t;/* Bit 8:&t;AutoNeg is On */
DECL|macro|PHY_L_QS_AN_C
mdefine_line|#define PHY_L_QS_AN_C&t;&t;(1&lt;&lt;7)&t;/* Bit 7:&t;AN is Complete */
DECL|macro|PHY_L_QS_LLE
mdefine_line|#define PHY_L_QS_LLE&t;&t;(7&lt;&lt;4)&t;/* Bit 6:&t;Line Length Estim. */
DECL|macro|PHY_L_QS_PAUSE
mdefine_line|#define PHY_L_QS_PAUSE&t;&t;(1&lt;&lt;3)&t;/* Bit 3:&t;LP advertised Pause */
DECL|macro|PHY_L_QS_AS_PAUSE
mdefine_line|#define PHY_L_QS_AS_PAUSE&t;(1&lt;&lt;2)&t;/* Bit 2:&t;LP adv. asym. Pause */
DECL|macro|PHY_L_QS_ISOLATE
mdefine_line|#define PHY_L_QS_ISOLATE&t;(1&lt;&lt;1)&t;/* Bit 1:&t;CIM Isolated */
DECL|macro|PHY_L_QS_EVENT
mdefine_line|#define PHY_L_QS_EVENT&t;&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Event has occurred */
multiline_comment|/*****&t;PHY_LONE_INT_ENAB&t;16 bit r/w&t;Interrupt Enable Reg *****/
multiline_comment|/*****&t;PHY_LONE_INT_STAT&t;16 bit ro&t;Interrupt Status Reg *****/
multiline_comment|/* Bit 15..14:&t;reserved */
DECL|macro|PHY_L_IS_AN_F
mdefine_line|#define PHY_L_IS_AN_F&t;&t;(1&lt;&lt;13)&t;/* Bit 13:&t;Autoneg fault */
multiline_comment|/* Bit 12:&t;not described */
DECL|macro|PHY_L_IS_CROSS
mdefine_line|#define PHY_L_IS_CROSS&t;&t;(1&lt;&lt;11)&t;/* Bit 11:&t;Crossover used */
DECL|macro|PHY_L_IS_POL
mdefine_line|#define PHY_L_IS_POL&t;&t;(1&lt;&lt;10)&t;/* Bit 10:&t;Polarity correct. used*/
DECL|macro|PHY_L_IS_SS
mdefine_line|#define PHY_L_IS_SS&t;&t;(1&lt;&lt;9)&t;/* Bit 9:&t;Smart Speed Downgrade*/
DECL|macro|PHY_L_IS_CFULL
mdefine_line|#define PHY_L_IS_CFULL&t;&t;(1&lt;&lt;8)&t;/* Bit 8:&t;Counter Full */
DECL|macro|PHY_L_IS_AN_C
mdefine_line|#define PHY_L_IS_AN_C&t;&t;(1&lt;&lt;7)&t;/* Bit 7:&t;AutoNeg Complete */
DECL|macro|PHY_L_IS_SPEED
mdefine_line|#define PHY_L_IS_SPEED&t;&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Speed Changed */
DECL|macro|PHY_L_IS_DUP
mdefine_line|#define PHY_L_IS_DUP&t;&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Duplex Changed */
DECL|macro|PHY_L_IS_LS
mdefine_line|#define PHY_L_IS_LS&t;&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Link Status Changed */
DECL|macro|PHY_L_IS_ISOL
mdefine_line|#define PHY_L_IS_ISOL&t;&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Isolate Occured */
DECL|macro|PHY_L_IS_MDINT
mdefine_line|#define PHY_L_IS_MDINT&t;&t;(1&lt;&lt;2)&t;/* Bit 2: (ro)&t;STAT: MII Int Pending */
DECL|macro|PHY_L_IS_INTEN
mdefine_line|#define PHY_L_IS_INTEN&t;&t;(1&lt;&lt;1)&t;/* Bit 1:&t;ENAB: Enable IRQs */
DECL|macro|PHY_L_IS_FORCE
mdefine_line|#define PHY_L_IS_FORCE&t;&t;(1&lt;&lt;0)&t;/* Bit 0:&t;ENAB: Force Interrupt */
DECL|macro|PHY_L_DEF_MSK
mdefine_line|#define PHY_L_DEF_MSK&t;&t;(PHY_L_IS_LS | PHY_L_IS_ISOL | &bslash;&n;&t;&t;&t;&t;PHY_L_IS_INTEN)&t;/* int. mask */
multiline_comment|/*****&t;PHY_LONE_LED_CFG&t;16 bit r/w&t;LED Configuration Reg *****/
DECL|macro|PHY_L_LC_LEDC
mdefine_line|#define PHY_L_LC_LEDC&t;&t;(3&lt;&lt;14)&t;/* Bit 15..14:&t;Col/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDR
mdefine_line|#define PHY_L_LC_LEDR&t;&t;(3&lt;&lt;12)&t;/* Bit 13..12:&t;Rx/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDT
mdefine_line|#define PHY_L_LC_LEDT&t;&t;(3&lt;&lt;10)&t;/* Bit 11..10:&t;Tx/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDG
mdefine_line|#define PHY_L_LC_LEDG&t;&t;(3&lt;&lt;8)&t;/* Bit 9..8:&t;Giga/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDS
mdefine_line|#define PHY_L_LC_LEDS&t;&t;(3&lt;&lt;6)&t;/* Bit 7..6:&t;10-100/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDL
mdefine_line|#define PHY_L_LC_LEDL&t;&t;(3&lt;&lt;4)&t;/* Bit 5..4:&t;Link/Blink/On/Off */
DECL|macro|PHY_L_LC_LEDF
mdefine_line|#define PHY_L_LC_LEDF&t;&t;(3&lt;&lt;2)&t;/* Bit 3..2:&t;Duplex/Blink/On/Off */
DECL|macro|PHY_L_LC_PSTRECH
mdefine_line|#define PHY_L_LC_PSTRECH&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Strech LED Pulses */
DECL|macro|PHY_L_LC_FREQ
mdefine_line|#define PHY_L_LC_FREQ&t;&t;(1&lt;&lt;0)&t;/* Bit 0:&t;30/100 ms */
multiline_comment|/*****&t;PHY_LONE_PORT_CTRL&t;16 bit r/w&t;Port Control Reg *****/
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
multiline_comment|/* Bit 9..0:&t;not described */
multiline_comment|/*****&t;PHY_LONE_CIM&t;&t;16 bit ro&t;CIM Reg *****/
DECL|macro|PHY_L_CIM_ISOL
mdefine_line|#define PHY_L_CIM_ISOL&t;&t;(255&lt;&lt;8)/* Bit 15..8:&t;Isolate Count */
DECL|macro|PHY_L_CIM_FALSE_CAR
mdefine_line|#define PHY_L_CIM_FALSE_CAR&t;(255&lt;&lt;0)/* Bit  7..0:&t;False Carrier Count */
multiline_comment|/*&n; * Pause Bits (PHY_L_AN_ASP and PHY_L_AN_PC) encoding&n; */
DECL|macro|PHY_L_P_NO_PAUSE
mdefine_line|#define PHY_L_P_NO_PAUSE&t;(0&lt;&lt;10)&t;/* Bit&t;11..10:&t;no Pause Mode */
DECL|macro|PHY_L_P_SYM_MD
mdefine_line|#define PHY_L_P_SYM_MD&t;&t;(1&lt;&lt;10)&t;/* Bit&t;11..10:&t;symmetric Pause Mode */
DECL|macro|PHY_L_P_ASYM_MD
mdefine_line|#define PHY_L_P_ASYM_MD&t;&t;(2&lt;&lt;10)&t;/* Bit&t;11..10:&t;asymmetric Pause Mode */
DECL|macro|PHY_L_P_BOTH_MD
mdefine_line|#define PHY_L_P_BOTH_MD&t;&t;(3&lt;&lt;10)&t;/* Bit&t;11..10:&t;both Pause Mode */
multiline_comment|/*&n; * National-Specific&n; */
multiline_comment|/***** PHY_NAT_1000T_CTRL&t;16 bit r/w&t;1000Base-T Control Reg *****/
DECL|macro|PHY_N_1000C_TEST
mdefine_line|#define PHY_N_1000C_TEST&t;(7&lt;&lt;13)&t;/* Bit&t;15..13:&t;Test Modes */
DECL|macro|PHY_N_1000C_MSE
mdefine_line|#define PHY_N_1000C_MSE&t;&t;(1&lt;&lt;12)&t;/* Bit&t;12:&t;Master/Slave Enable */
DECL|macro|PHY_N_1000C_MSC
mdefine_line|#define PHY_N_1000C_MSC&t;&t;(1&lt;&lt;11)&t;/* Bit&t;11:&t;M/S Configuration */
DECL|macro|PHY_N_1000C_RD
mdefine_line|#define PHY_N_1000C_RD&t;&t;(1&lt;&lt;10)&t;/* Bit&t;10:&t;Repeater/DTE */
DECL|macro|PHY_N_1000C_AFD
mdefine_line|#define PHY_N_1000C_AFD&t;&t;(1&lt;&lt;9)&t;/* Bit&t;9:&t;Advertise Full Duplex */
DECL|macro|PHY_N_1000C_AHD
mdefine_line|#define PHY_N_1000C_AHD&t;&t;(1&lt;&lt;8)&t;/* Bit&t;8:&t;Advertise Half Duplex */
DECL|macro|PHY_N_1000C_APC
mdefine_line|#define PHY_N_1000C_APC&t;&t;(1&lt;&lt;7)&t;/* Bit&t;7:&t;Asymetric Pause Cap. */
multiline_comment|/* Bit&t;6..0:&t;reserved */
multiline_comment|/***** PHY_NAT_1000T_STAT&t;16 bit ro&t;1000Base-T Status Reg *****/
DECL|macro|PHY_N_1000S_MSF
mdefine_line|#define PHY_N_1000S_MSF&t;&t;(1&lt;&lt;15)&t;/* Bit&t;15:&t;Master/Slave Fault */
DECL|macro|PHY_N_1000S_MSR
mdefine_line|#define PHY_N_1000S_MSR&t;&t;(1&lt;&lt;14)&t;/* Bit&t;14:&t;Master/Slave Result */
DECL|macro|PHY_N_1000S_LRS
mdefine_line|#define PHY_N_1000S_LRS&t;&t;(1&lt;&lt;13)&t;/* Bit&t;13:&t;Local Receiver Status */
DECL|macro|PHY_N_1000S_RRS
mdefine_line|#define PHY_N_1000S_RRS&t;&t;(1&lt;&lt;12)&t;/* Bit&t;12:&t;Remote Receiver Status*/
DECL|macro|PHY_N_1000S_LP_FD
mdefine_line|#define PHY_N_1000S_LP_FD&t;(1&lt;&lt;11)&t;/* Bit&t;11:&t;Link Partner can FD */
DECL|macro|PHY_N_1000S_LP_HD
mdefine_line|#define PHY_N_1000S_LP_HD&t;(1&lt;&lt;10)&t;/* Bit&t;10:&t;Link Partner can HD */
DECL|macro|PHY_N_1000C_LP_APC
mdefine_line|#define PHY_N_1000C_LP_APC&t;(1&lt;&lt;9)&t;/* Bit&t;9:&t;LP Asym. Pause Cap. */
multiline_comment|/* Bit&t;8:&t;reserved */
DECL|macro|PHY_N_1000S_IEC
mdefine_line|#define PHY_N_1000S_IEC&t;&t;(255&lt;&lt;0)/* Bit&t;7..0:&t;Idle Error Count */
multiline_comment|/*****&t;PHY_NAT_EXT_STAT&t;16 bit ro&t;Extended Status Register *****/
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
multiline_comment|/*****&t;PHY_NAT_EXT_CTRL1&t;16 bit ro&t;Extended Control Reg1 *****/
multiline_comment|/*****&t;PHY_NAT_Q_STAT1&t;&t;16 bit ro&t;Quick Status Reg1 *****/
multiline_comment|/*****&t;PHY_NAT_10B_OP&t;&t;16 bit ro&t;10Base-T Operations Reg *****/
multiline_comment|/*****&t;PHY_NAT_EXT_CTRL2&t;16 bit ro&t;Extended Control Reg1 *****/
multiline_comment|/*****&t;PHY_NAT_Q_STAT2&t;&t;16 bit ro&t;Quick Status Reg2 *****/
multiline_comment|/*****&t;PHY_NAT_PHY_ADDR&t;16 bit ro&t;PHY Address Register *****/
multiline_comment|/* typedefs *******************************************************************/
multiline_comment|/* function prototypes ********************************************************/
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif&t;/* __cplusplus */
macro_line|#endif&t;/* __INC_XMAC_H */
eof
