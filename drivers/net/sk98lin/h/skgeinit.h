multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgeinit.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.51 $&n; * Date:&t;$Date: 2001/02/09 12:26:38 $&n; * Purpose:&t;Structures and prototypes for the GE Init Module&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2001 SysKonnect GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skgeinit.h,v $&n; *&t;Revision 1.51  2001/02/09 12:26:38  cgoos&n; *&t;Inserted #ifdef DIAG for half duplex workaround timer.&n; *&t;&n; *&t;Revision 1.50  2001/02/07 07:56:40  rassmann&n; *&t;Corrected copyright.&n; *&t;&n; *&t;Revision 1.49  2001/01/31 15:32:18  gklug&n; *&t;fix: problem with autosensing an SR8800 switch&n; *&t;add: counter for autoneg timeouts&n; *&t;&n; *&t;Revision 1.48  2000/11/09 11:30:10  rassmann&n; *&t;WA: Waiting after releasing reset until BCom chip is accessible.&n; *&t;&n; *&t;Revision 1.47  2000/10/18 12:22:40  cgoos&n; *&t;Added workaround for half duplex hangup.&n; *&t;&n; *&t;Revision 1.46  2000/08/10 11:28:00  rassmann&n; *&t;Editorial changes.&n; *&t;Preserving 32-bit alignment in structs for the adapter context.&n; *&t;&n; *&t;Revision 1.45  1999/11/22 13:56:19  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.44  1999/10/26 07:34:15  malthoff&n; *&t;The define SK_LNK_ON has been lost in v1.41.&n; *&t;&n; *&t;Revision 1.43  1999/10/06 09:30:16  cgoos&n; *&t;Changed SK_XM_THR_JUMBO.&n; *&t;&n; *&t;Revision 1.42  1999/09/16 12:58:26  cgoos&n; *&t;Changed SK_LED_STANDY macro to be independent of HW link sync.&n; *&t;&n; *&t;Revision 1.41  1999/07/30 06:56:14  malthoff&n; *&t;Correct comment for SK_MS_STAT_UNSET.&n; *&t;&n; *&t;Revision 1.40  1999/05/27 13:38:46  cgoos&n; *&t;Added SK_BMU_TX_WM.&n; *&t;Made SK_BMU_TX_WM and SK_BMU_RX_WM user-definable.&n; *&t;Changed XMAC Tx treshold to max. values.&n; *&t;&n; *&t;Revision 1.39  1999/05/20 14:35:26  malthoff&n; *&t;Remove prototypes for SkGeLinkLED().&n; *&t;&n; *&t;Revision 1.38  1999/05/19 11:59:12  cgoos&n; *&t;Added SK_MS_CAP_INDETERMINATED define.&n; *&t;&n; *&t;Revision 1.37  1999/05/19 07:32:33  cgoos&n; *&t;Changes for 1000Base-T.&n; *&t;LED-defines for HWAC_LINK_LED macro.&n; *&t;&n; *&t;Revision 1.36  1999/04/08 14:00:24  gklug&n; *&t;add:Port struct field PLinkResCt&n; *&t;&n; *&t;Revision 1.35  1999/03/25 07:43:07  malthoff&n; *&t;Add error string for SKERR_HWI_E018MSG.&n; *&t;&n; *&t;Revision 1.34  1999/03/12 16:25:57  malthoff&n; *&t;Remove PPollRxD and PPollTxD.&n; *&t;Add SKERR_HWI_E017MSG. and SK_DPOLL_MAX.&n; *&t;&n; *&t;Revision 1.33  1999/03/12 13:34:41  malthoff&n; *&t;Add Autonegotiation error codes.&n; *&t;Change defines for parameter Mode in SkXmSetRxCmd().&n; *&t;Replace __STDC__ by SK_KR_PROTO.&n; *&t;&n; *&t;Revision 1.32  1999/01/25 14:40:20  mhaveman&n; *&t;Added new return states for the virtual management port if multiple&n; *&t;ports are active but differently configured.&n; *&t;&n; *&t;Revision 1.31  1998/12/11 15:17:02  gklug&n; *&t;add: Link partnet autoneg states : Unknown Manual and Autonegotiation&n; *&t;&n; *&t;Revision 1.30  1998/12/07 12:17:04  gklug&n; *&t;add: Link Partner autonegotiation flag&n; *&t;&n; *&t;Revision 1.29  1998/12/01 10:54:42  gklug&n; *&t;add: variables for XMAC Errata&n; *&t;&n; *&t;Revision 1.28  1998/12/01 10:14:15  gklug&n; *&t;add: PIsave saves the Interrupt status word&n; *&t;&n; *&t;Revision 1.27  1998/11/26 15:24:52  mhaveman&n; *&t;Added link status states SK_LMODE_STAT_AUTOHALF and&n; *&t;SK_LMODE_STAT_AUTOFULL which are used by PNMI.&n; *&t;&n; *&t;Revision 1.26  1998/11/26 14:53:01  gklug&n; *&t;add:autoNeg Timeout variable&n; *&t;&n; *&t;Revision 1.25  1998/11/26 08:58:50  gklug&n; *&t;add: Link Mode configuration (AUTO Sense mode)&n; *&t;&n; *&t;Revision 1.24  1998/11/24 13:30:27  gklug&n; *&t;add: PCheckPar to port struct&n; *&t;&n; *&t;Revision 1.23  1998/11/18 13:23:26  malthoff&n; *&t;Add SK_PKT_TO_MAX.&n; *&t;&n; *&t;Revision 1.22  1998/11/18 13:19:54  gklug&n; *&t;add: PPrevShorts and PLinkBroken to port struct for WA XMAC Errata #C1&n; *&n; *&t;Revision 1.21  1998/10/26 08:02:57  malthoff&n; *&t;Add GIRamOffs.&n; *&t;&n; *&t;Revision 1.20  1998/10/19 07:28:37  malthoff&n; *&t;Add prototyp for SkGeInitRamIface().&n; *&t;&n; *&t;Revision 1.19  1998/10/14 14:47:48  malthoff&n; *&t;SK_TIMER should not be defined for Diagnostics.&n; *&t;Add SKERR_HWI_E015MSG and SKERR_HWI_E016MSG.&n; *&t;&n; *&t;Revision 1.18  1998/10/14 14:00:03  gklug&n; *&t;add: timer to port struct for workaround of Errata #2&n; *&t;&n; *&t;Revision 1.17  1998/10/14 11:23:09  malthoff&n; *&t;Add prototype for SkXmAutoNegDone().&n; *&t;Fix SkXmSetRxCmd() prototype statement.&n; *&n; *&t;Revision 1.16  1998/10/14 05:42:29  gklug&n; *&t;add: HWLinkUp flag to Port struct&n; *&t;&n; *&t;Revision 1.15  1998/10/09 08:26:33  malthoff&n; *&t;Rename SK_RB_ULPP_B to SK_RB_LLPP_B.&n; *&t;&n; *&t;Revision 1.14  1998/10/09 07:11:13  malthoff&n; *&t;bug fix: SK_FACT_53 is 85 not 117.&n; *&t;Rework time out init values.&n; *&t;Add GIPortUsage and corresponding defines.&n; *&t;Add some error log messages.&n; *&t;&n; *&t;Revision 1.13  1998/10/06 14:13:14  malthoff&n; *&t;Add prototyp for SkGeLoadLnkSyncCnt().&n; *&n; *&t;Revision 1.12  1998/10/05 11:29:53  malthoff&n; *&t;bug fix: A comment was not closed.&n; *&n; *&t;Revision 1.11  1998/10/05 08:01:59  malthoff&n; *&t;Add default Timeout- Threshold- and&n; *&t;Watermark constants. Add QRam start and end&n; *&t;variables. Also add vars to store the polling&n; *&t;mode and receive command. Add new Error Log&n; *&t;Messages and function prototypes.&n; *&n; *&t;Revision 1.10  1998/09/28 13:34:48  malthoff&n; *&t;Add mode bits for LED functions.&n; *&t;Move Autoneg and Flow Ctrl bits from shgesirq.h&n; *&t;Add the required Error Log Entries&n; *&t;and Function Prototypes.&n; *&n; *&t;Revision 1.9  1998/09/16 14:38:41  malthoff&n; *&t;Rework the SK_LNK_xxx defines.&n; *&t;Add error log message defines.&n; *&t;Add prototypes for skxmac2.c&n; *&n; *&t;Revision 1.8  1998/09/11 05:29:18  gklug&n; *&t;add: init state of a port&n; *&n; *&t;Revision 1.7  1998/09/08 08:35:52  gklug&n; *&t;add: defines of the Init Levels&n; *&n; *&t;Revision 1.6  1998/09/03 13:48:42  gklug&n; *&t;add: Link strati, capabilities to Port struct&n; *&n; *&t;Revision 1.5  1998/09/03 13:30:59  malthoff&n; *&t;Add SK_LNK_BLINK and SK_LNK_PERM.&n; *&n; *&t;Revision 1.4  1998/09/03 09:55:31  malthoff&n; *&t;Add constants for parameters Dir and RstMode&n; *&t;when calling SkGeStopPort().&n; *&t;Rework the prototyp section.&n; *&t;Add Queue Address offsets PRxQOff, PXsQOff, and PXaQOff.&n; *&t;Remove Ioc with IoC.&n; *&n; *&t;Revision 1.3  1998/08/19 09:11:54  gklug&n; *&t;fix: struct are removed from c-source (see CCC)&n; *&t;add: typedefs for all structs&n; *&n; *&t;Revision 1.2  1998/07/28 12:38:26  malthoff&n; *&t;The prototypes got the parameter &squot;IoC&squot;.&n; *&n; *&t;Revision 1.1  1998/07/23 09:50:24  malthoff&n; *&t;Created.&n; *&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKGEINIT_H_
DECL|macro|__INC_SKGEINIT_H_
mdefine_line|#define __INC_SKGEINIT_H_
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif&t;/* __cplusplus */
multiline_comment|/* defines ********************************************************************/
multiline_comment|/*&n; * defines for modifying Link LED behaviour (has been used with SkGeLinkLED())&n; */
DECL|macro|SK_LNK_OFF
mdefine_line|#define SK_LNK_OFF&t;LED_OFF
DECL|macro|SK_LNK_ON
mdefine_line|#define SK_LNK_ON&t;(LED_ON | LED_BLK_OFF| LED_SYNC_OFF)&t;
DECL|macro|SK_LNK_BLINK
mdefine_line|#define SK_LNK_BLINK&t;(LED_ON | LED_BLK_ON | LED_SYNC_ON)
DECL|macro|SK_LNK_PERM
mdefine_line|#define SK_LNK_PERM&t;(LED_ON | LED_BLK_OFF| LED_SYNC_ON)
DECL|macro|SK_LNK_TST
mdefine_line|#define SK_LNK_TST&t;(LED_ON | LED_BLK_ON | LED_SYNC_OFF)
multiline_comment|/*&n; * defines for parameter &squot;Mode&squot; when calling SK_HWAC_LINK_LED()&n; */
DECL|macro|SK_LED_OFF
mdefine_line|#define SK_LED_OFF&t;LED_OFF
DECL|macro|SK_LED_ACTIVE
mdefine_line|#define SK_LED_ACTIVE&t;(LED_ON | LED_BLK_OFF| LED_SYNC_OFF)
DECL|macro|SK_LED_STANDBY
mdefine_line|#define SK_LED_STANDBY&t;(LED_ON | LED_BLK_ON| LED_SYNC_OFF)
multiline_comment|/*&n; * defines for parameter &squot;Mode&squot; when calling SkGeXmitLED()&n; */
DECL|macro|SK_LED_DIS
mdefine_line|#define SK_LED_DIS&t;0
DECL|macro|SK_LED_ENA
mdefine_line|#define SK_LED_ENA&t;1
DECL|macro|SK_LED_TST
mdefine_line|#define SK_LED_TST&t;2
multiline_comment|/*&n; * Counter and Timer constants, for a host clock of 62.5 MHz&n; */
DECL|macro|SK_XMIT_DUR
mdefine_line|#define SK_XMIT_DUR&t;0x002faf08L&t;&t;/*  50 ms */
DECL|macro|SK_BLK_DUR
mdefine_line|#define SK_BLK_DUR&t;0x01dcd650L&t;&t;/* 500 ms */
DECL|macro|SK_DPOLL_DEF
mdefine_line|#define SK_DPOLL_DEF&t;0x00EE6B28L&t;&t;/* 250 ms */
DECL|macro|SK_DPOLL_MAX
mdefine_line|#define SK_DPOLL_MAX&t;0x00FFFFFFL&t;&t;/* ca. 268ms */
DECL|macro|SK_FACT_62
mdefine_line|#define SK_FACT_62&t;100&t;&t;&t;/* is given in percent */
DECL|macro|SK_FACT_53
mdefine_line|#define SK_FACT_53&t; 85
multiline_comment|/*&n; * Timeout values&n; */
DECL|macro|SK_MAC_TO_53
mdefine_line|#define SK_MAC_TO_53&t;72&t;&t;/* MAC arbiter timeout */
DECL|macro|SK_PKT_TO_53
mdefine_line|#define SK_PKT_TO_53&t;0x2000&t;&t;/* Packet arbiter timeout */
DECL|macro|SK_PKT_TO_MAX
mdefine_line|#define SK_PKT_TO_MAX&t;0xffff&t;&t;/* Maximum value */
DECL|macro|SK_RI_TO_53
mdefine_line|#define SK_RI_TO_53&t;36&t;&t;/* RAM interface timeout */
multiline_comment|/*&n; * RAM Buffer High Pause Threshold values&n; */
DECL|macro|SK_RB_ULPP
mdefine_line|#define SK_RB_ULPP&t;( 8 * 1024)&t;/* Upper Level in kB/8 */
DECL|macro|SK_RB_LLPP_S
mdefine_line|#define SK_RB_LLPP_S&t;(10 * 1024)&t;/* Lower Level for small Queues */
DECL|macro|SK_RB_LLPP_B
mdefine_line|#define SK_RB_LLPP_B&t;(16 * 1024)&t;/* Lower Level for big Queues */
macro_line|#ifndef SK_BMU_RX_WM
DECL|macro|SK_BMU_RX_WM
mdefine_line|#define SK_BMU_RX_WM&t;0x600&t;&t;/* BMU Rx Watermark */
macro_line|#endif
macro_line|#ifndef SK_BMU_TX_WM
DECL|macro|SK_BMU_TX_WM
mdefine_line|#define SK_BMU_TX_WM&t;0x600&t;&t;/* BMU Rx Watermark */
macro_line|#endif
multiline_comment|/* XMAC II Tx Threshold */
DECL|macro|SK_XM_THR_REDL
mdefine_line|#define SK_XM_THR_REDL&t;0x01fb&t;&t;/* .. for redundant link usage */
DECL|macro|SK_XM_THR_SL
mdefine_line|#define SK_XM_THR_SL&t;0x01fb&t;&t;/* .. for single link adapters */
DECL|macro|SK_XM_THR_MULL
mdefine_line|#define SK_XM_THR_MULL&t;0x01fb&t;&t;/* .. for multiple link usage */
DECL|macro|SK_XM_THR_JUMBO
mdefine_line|#define SK_XM_THR_JUMBO&t;0x03fc&t;&t;/* .. for jumbo frame usage */
multiline_comment|/* values for GIPortUsage */
DECL|macro|SK_RED_LINK
mdefine_line|#define SK_RED_LINK&t;1&t;&t;/* redundant link usage */
DECL|macro|SK_MUL_LINK
mdefine_line|#define SK_MUL_LINK&t;2&t;&t;/* multiple link usage */
DECL|macro|SK_JUMBO_LINK
mdefine_line|#define SK_JUMBO_LINK&t;3&t;&t;/* driver uses jumbo frames */
multiline_comment|/* Minimum RAM Buffer Receive Queue Size */
DECL|macro|SK_MIN_RXQ_SIZE
mdefine_line|#define SK_MIN_RXQ_SIZE&t;16&t;/* 16 kB */
multiline_comment|/*&n; * defines for parameter &squot;Dir&squot; when calling SkGeStopPort()&n; */
DECL|macro|SK_STOP_TX
mdefine_line|#define&t;SK_STOP_TX&t;1&t;/* Stops the transmit path, resets the XMAC */
DECL|macro|SK_STOP_RX
mdefine_line|#define SK_STOP_RX&t;2&t;/* Stops the receive path */
DECL|macro|SK_STOP_ALL
mdefine_line|#define SK_STOP_ALL&t;3&t;/* Stops rx and tx path, resets the XMAC */
multiline_comment|/*&n; * defines for parameter &squot;RstMode&squot; when calling SkGeStopPort()&n; */
DECL|macro|SK_SOFT_RST
mdefine_line|#define SK_SOFT_RST&t;1&t;/* perform a software reset */
DECL|macro|SK_HARD_RST
mdefine_line|#define SK_HARD_RST&t;2&t;/* perform a hardware reset */
multiline_comment|/*&n; * Define Init Levels&n; */
DECL|macro|SK_INIT_DATA
mdefine_line|#define&t;SK_INIT_DATA&t;0&t;/* Init level 0: init data structures */
DECL|macro|SK_INIT_IO
mdefine_line|#define&t;SK_INIT_IO&t;1&t;/* Init level 1: init with IOs */
DECL|macro|SK_INIT_RUN
mdefine_line|#define&t;SK_INIT_RUN&t;2&t;/* Init level 2: init for run time */
multiline_comment|/*&n; * Set Link Mode Parameter&n; */
DECL|macro|SK_LMODE_HALF
mdefine_line|#define&t;SK_LMODE_HALF&t;&t;1&t;/* Half Duplex Mode */
DECL|macro|SK_LMODE_FULL
mdefine_line|#define&t;SK_LMODE_FULL&t;&t;2&t;/* Full Duplex Mode */
DECL|macro|SK_LMODE_AUTOHALF
mdefine_line|#define&t;SK_LMODE_AUTOHALF&t;3&t;/* AutoHalf Duplex Mode */
DECL|macro|SK_LMODE_AUTOFULL
mdefine_line|#define&t;SK_LMODE_AUTOFULL&t;4&t;/* AutoFull Duplex Mode */
DECL|macro|SK_LMODE_AUTOBOTH
mdefine_line|#define&t;SK_LMODE_AUTOBOTH&t;5&t;/* AutoBoth Duplex Mode */
DECL|macro|SK_LMODE_AUTOSENSE
mdefine_line|#define&t;SK_LMODE_AUTOSENSE&t;6&t;/* configured mode auto sensing */
DECL|macro|SK_LMODE_INDETERMINATED
mdefine_line|#define SK_LMODE_INDETERMINATED&t;7&t;/* Return value for virtual port if&n;&t;&t;&t;&t;&t; * multiple ports are differently&n;&t;&t;&t;&t;&t; * configured.&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Autonegotiation timeout in 100ms granularity.&n; */
DECL|macro|SK_AND_MAX_TO
mdefine_line|#define&t;SK_AND_MAX_TO&t;&t;6&t;/* Wait 600 msec before link comes up */
multiline_comment|/*&n; * Define Autonegotiation error codes here&n; */
DECL|macro|SK_AND_OK
mdefine_line|#define&t;SK_AND_OK&t;&t;0&t;/* no error */
DECL|macro|SK_AND_OTHER
mdefine_line|#define&t;SK_AND_OTHER&t;&t;1&t;/* other error than below */
DECL|macro|SK_AND_DUP_CAP
mdefine_line|#define&t;SK_AND_DUP_CAP&t;&t;2&t;/* Duplex capabilities error */
multiline_comment|/*&n; * Link Capability value&n; */
DECL|macro|SK_LMODE_CAP_HALF
mdefine_line|#define&t;SK_LMODE_CAP_HALF&t;(1&lt;&lt;0)&t;/* Half Duplex Mode */
DECL|macro|SK_LMODE_CAP_FULL
mdefine_line|#define&t;SK_LMODE_CAP_FULL&t;(1&lt;&lt;1)&t;/* Full Duplex Mode */
DECL|macro|SK_LMODE_CAP_AUTOHALF
mdefine_line|#define&t;SK_LMODE_CAP_AUTOHALF&t;(1&lt;&lt;2)&t;/* AutoHalf Duplex Mode */
DECL|macro|SK_LMODE_CAP_AUTOFULL
mdefine_line|#define&t;SK_LMODE_CAP_AUTOFULL&t;(1&lt;&lt;3)&t;/* AutoFull Duplex Mode */
DECL|macro|SK_LMODE_CAP_INDETERMINATED
mdefine_line|#define SK_LMODE_CAP_INDETERMINATED (1&lt;&lt;4) /* Return value for virtual port if&n;&t;&t;&t;&t;&t; * multiple ports are differently&n;&t;&t;&t;&t;&t; * configured.&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Link mode current state&n; */
DECL|macro|SK_LMODE_STAT_UNKNOWN
mdefine_line|#define&t;SK_LMODE_STAT_UNKNOWN&t;1&t;/* Unknown Duplex Mode */
DECL|macro|SK_LMODE_STAT_HALF
mdefine_line|#define&t;SK_LMODE_STAT_HALF&t;2&t;/* Half Duplex Mode */
DECL|macro|SK_LMODE_STAT_FULL
mdefine_line|#define&t;SK_LMODE_STAT_FULL&t;3&t;/* Full Duplex Mode */
DECL|macro|SK_LMODE_STAT_AUTOHALF
mdefine_line|#define SK_LMODE_STAT_AUTOHALF&t;4&t;/* Half Duplex Mode obtained by AutoNeg */
DECL|macro|SK_LMODE_STAT_AUTOFULL
mdefine_line|#define SK_LMODE_STAT_AUTOFULL&t;5&t;/* Half Duplex Mode obtained by AutoNeg */
DECL|macro|SK_LMODE_STAT_INDETERMINATED
mdefine_line|#define SK_LMODE_STAT_INDETERMINATED 6&t;/* Return value for virtual port if&n;&t;&t;&t;&t;&t; * multiple ports are differently&n;&t;&t;&t;&t;&t; * configured.&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Set Flow Control Mode Parameter (and capabilities)&n; */
DECL|macro|SK_FLOW_MODE_NONE
mdefine_line|#define&t;SK_FLOW_MODE_NONE&t;1&t;/* No Flow Control */
DECL|macro|SK_FLOW_MODE_LOC_SEND
mdefine_line|#define&t;SK_FLOW_MODE_LOC_SEND&t;2&t;/* Local station sends PAUSE */
DECL|macro|SK_FLOW_MODE_SYMMETRIC
mdefine_line|#define&t;SK_FLOW_MODE_SYMMETRIC&t;3&t;/* Both station may send PAUSE */
DECL|macro|SK_FLOW_MODE_SYM_OR_REM
mdefine_line|#define&t;SK_FLOW_MODE_SYM_OR_REM&t;4&t;/* Both station may send PAUSE or&n;&t;&t;&t;&t;&t; * just the remote station may send&n;&t;&t;&t;&t;&t; * PAUSE&n;&t;&t;&t;&t;&t; */
DECL|macro|SK_FLOW_MODE_INDETERMINATED
mdefine_line|#define SK_FLOW_MODE_INDETERMINATED 5&t;/* Return value for virtual port if&n;&t;&t;&t;&t;&t; * multiple ports are differently&n;&t;&t;&t;&t;&t; * configured.&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Flow Control Status Parameter&n; */
DECL|macro|SK_FLOW_STAT_NONE
mdefine_line|#define&t;SK_FLOW_STAT_NONE&t;1&t;/* No Flow Control */
DECL|macro|SK_FLOW_STAT_REM_SEND
mdefine_line|#define&t;SK_FLOW_STAT_REM_SEND&t;2&t;/* Remote Station sends PAUSE */
DECL|macro|SK_FLOW_STAT_LOC_SEND
mdefine_line|#define&t;SK_FLOW_STAT_LOC_SEND&t;3&t;/* Local station sends PAUSE */
DECL|macro|SK_FLOW_STAT_SYMMETRIC
mdefine_line|#define&t;SK_FLOW_STAT_SYMMETRIC&t;4&t;/* Both station may send PAUSE */
DECL|macro|SK_FLOW_STAT_INDETERMINATED
mdefine_line|#define SK_FLOW_STAT_INDETERMINATED 5&t;/* Return value for virtual port if&n;&t;&t;&t;&t;&t; * multiple ports are differently&n;&t;&t;&t;&t;&t; * configured.&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Master/Slave Mode capabilities&n; */
DECL|macro|SK_MS_CAP_AUTO
mdefine_line|#define&t;SK_MS_CAP_AUTO&t;&t;(1&lt;&lt;0)&t;/* Automatic resolution */
DECL|macro|SK_MS_CAP_MASTER
mdefine_line|#define&t;SK_MS_CAP_MASTER&t;(1&lt;&lt;1)&t;/* This station is master */
DECL|macro|SK_MS_CAP_SLAVE
mdefine_line|#define&t;SK_MS_CAP_SLAVE&t;&t;(1&lt;&lt;2)&t;/* This station is slave */
DECL|macro|SK_MS_CAP_INDETERMINATED
mdefine_line|#define&t;SK_MS_CAP_INDETERMINATED (1&lt;&lt;3)&t;/* Return value for virtual port if&n;&t;&t;&t;&t;&t; * multiple ports are differently&n;&t;&t;&t;&t;&t; * configured.&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Set Master/Slave Mode Parameter (and capabilities)&n; */
DECL|macro|SK_MS_MODE_AUTO
mdefine_line|#define&t;SK_MS_MODE_AUTO&t;&t;1&t;/* Automatic resolution */
DECL|macro|SK_MS_MODE_MASTER
mdefine_line|#define&t;SK_MS_MODE_MASTER&t;2&t;/* This station is master */
DECL|macro|SK_MS_MODE_SLAVE
mdefine_line|#define&t;SK_MS_MODE_SLAVE&t;3&t;/* This station is slave */
DECL|macro|SK_MS_MODE_INDETERMINATED
mdefine_line|#define SK_MS_MODE_INDETERMINATED 4&t;/* Return value for virtual port if &n;&t;&t;&t;&t;&t; * multiple ports are differently&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Master/Slave Status Parameter&n; */
DECL|macro|SK_MS_STAT_UNSET
mdefine_line|#define&t;SK_MS_STAT_UNSET&t;1&t;/* The MS status is never been determ*/
DECL|macro|SK_MS_STAT_MASTER
mdefine_line|#define&t;SK_MS_STAT_MASTER&t;2&t;/* This station is master */
DECL|macro|SK_MS_STAT_SLAVE
mdefine_line|#define&t;SK_MS_STAT_SLAVE&t;3&t;/* This station is slave */
DECL|macro|SK_MS_STAT_FAULT
mdefine_line|#define&t;SK_MS_STAT_FAULT&t;4&t;/* MS resolution failed */
DECL|macro|SK_MS_STAT_INDETERMINATED
mdefine_line|#define SK_MS_STAT_INDETERMINATED 5&t;/* Return value for virtual port if&n;&t;&t;&t;&t;&t; * multiple ports are differently&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * defines for parameter &squot;Mode&squot; when calling SkXmSetRxCmd()&n; */
DECL|macro|SK_STRIP_FCS_ON
mdefine_line|#define SK_STRIP_FCS_ON&t;&t;(1&lt;&lt;0)&t;/* Enable FCS stripping of rx frames */
DECL|macro|SK_STRIP_FCS_OFF
mdefine_line|#define SK_STRIP_FCS_OFF&t;(1&lt;&lt;1)&t;/* Disable FCS stripping of rx frames */
DECL|macro|SK_STRIP_PAD_ON
mdefine_line|#define SK_STRIP_PAD_ON&t;&t;(1&lt;&lt;2)&t;/* Enable pad byte stripping of rx f */
DECL|macro|SK_STRIP_PAD_OFF
mdefine_line|#define SK_STRIP_PAD_OFF&t;(1&lt;&lt;3)&t;/* Disable pad byte stripping of rx f */
DECL|macro|SK_LENERR_OK_ON
mdefine_line|#define SK_LENERR_OK_ON&t;&t;(1&lt;&lt;4)&t;/* Don&squot;t chk fr for in range len error*/
DECL|macro|SK_LENERR_OK_OFF
mdefine_line|#define SK_LENERR_OK_OFF&t;(1&lt;&lt;5)&t;/* Check frames for in range len error*/
DECL|macro|SK_BIG_PK_OK_ON
mdefine_line|#define SK_BIG_PK_OK_ON&t;&t;(1&lt;&lt;6)&t;/* Don&squot;t set rcvError bit for big fr */
DECL|macro|SK_BIG_PK_OK_OFF
mdefine_line|#define SK_BIG_PK_OK_OFF&t;(1&lt;&lt;7)&t;/* Set rcvError bit for big frames */&t;
multiline_comment|/*&n; * States of PState&n; */
DECL|macro|SK_PRT_RESET
mdefine_line|#define SK_PRT_RESET&t;0&t;/* the port is reset */
DECL|macro|SK_PRT_STOP
mdefine_line|#define SK_PRT_STOP&t;1&t;/* the port is stopped (similar to sw reset) */
DECL|macro|SK_PRT_INIT
mdefine_line|#define SK_PRT_INIT&t;2&t;/* the port is initialized */
DECL|macro|SK_PRT_RUN
mdefine_line|#define SK_PRT_RUN&t;3&t;/* the port has an active link */
multiline_comment|/*&n; * Default receive frame limit for Workaround of XMAC Errata&n; */
DECL|macro|SK_DEF_RX_WA_LIM
mdefine_line|#define&t;SK_DEF_RX_WA_LIM&t;SK_CONSTU64(100)
multiline_comment|/*&n; * Define link partner Status&n; */
DECL|macro|SK_LIPA_UNKNOWN
mdefine_line|#define&t;SK_LIPA_UNKNOWN&t;0&t;/* Link partner is in unknown state */
DECL|macro|SK_LIPA_MANUAL
mdefine_line|#define&t;SK_LIPA_MANUAL&t;1&t;/* Link partner is in detected manual state */
DECL|macro|SK_LIPA_AUTO
mdefine_line|#define&t;SK_LIPA_AUTO&t;2&t;/* Link partner is in autonegotiation state */
multiline_comment|/*&n; * Define Maximum Restarts before restart is ignored (3com WA)&n; */
DECL|macro|SK_MAX_LRESTART
mdefine_line|#define&t;SK_MAX_LRESTART&t;3&t;/* Max. 3 times the link is restarted */
multiline_comment|/*&n; * define max. autonegotiation timeouts before link detection in sense mode is&n; * reset.&n; */
DECL|macro|SK_MAX_ANEG_TO
mdefine_line|#define&t;SK_MAX_ANEG_TO&t;10&t;/* Max. 10 times the sense mode is reset */
multiline_comment|/* structures *****************************************************************/
multiline_comment|/*&n; * Port Structure&n; */
DECL|struct|s_GePort
r_typedef
r_struct
id|s_GePort
(brace
macro_line|#ifndef SK_DIAG
DECL|member|PWaTimer
id|SK_TIMER
id|PWaTimer
suffix:semicolon
multiline_comment|/* Workaround Timer */
macro_line|#endif
DECL|member|PPrevShorts
id|SK_U64
id|PPrevShorts
suffix:semicolon
multiline_comment|/* Previous short Counter checking */
DECL|member|PPrevRx
id|SK_U64
id|PPrevRx
suffix:semicolon
multiline_comment|/* Previous RxOk Counter checking */
DECL|member|PPrevFcs
id|SK_U64
id|PPrevFcs
suffix:semicolon
multiline_comment|/* Previous FCS Error Counter checking */
DECL|member|PRxLim
id|SK_U64
id|PRxLim
suffix:semicolon
multiline_comment|/* Previous RxOk Counter checking */
DECL|member|LastOctets
id|SK_U64
id|LastOctets
suffix:semicolon
multiline_comment|/* For half duplex hang check */
macro_line|#ifndef SK_DIAG
DECL|member|HalfDupChkTimer
id|SK_TIMER
id|HalfDupChkTimer
suffix:semicolon
macro_line|#endif
DECL|member|PLinkResCt
r_int
id|PLinkResCt
suffix:semicolon
multiline_comment|/* Link Restart Counter */
DECL|member|PAutoNegTimeOut
r_int
id|PAutoNegTimeOut
suffix:semicolon
multiline_comment|/* AutoNegotiation timeout current value */
DECL|member|PAutoNegTOCt
r_int
id|PAutoNegTOCt
suffix:semicolon
multiline_comment|/* AutoNeg Timeout Counter */
DECL|member|PRxQSize
r_int
id|PRxQSize
suffix:semicolon
multiline_comment|/* Port Rx Queue Size in kB */
DECL|member|PXSQSize
r_int
id|PXSQSize
suffix:semicolon
multiline_comment|/* Port Synchronous Transmit Queue Size in kB */
DECL|member|PXAQSize
r_int
id|PXAQSize
suffix:semicolon
multiline_comment|/* Port Asynchronous Transmit Queue Size in kB*/
DECL|member|PRxQRamStart
id|SK_U32
id|PRxQRamStart
suffix:semicolon
multiline_comment|/* Receive Queue RAM Buffer Start Address */
DECL|member|PRxQRamEnd
id|SK_U32
id|PRxQRamEnd
suffix:semicolon
multiline_comment|/* Receive Queue RAM Buffer End Address */
DECL|member|PXsQRamStart
id|SK_U32
id|PXsQRamStart
suffix:semicolon
multiline_comment|/* Sync Tx Queue RAM Buffer Start Address */
DECL|member|PXsQRamEnd
id|SK_U32
id|PXsQRamEnd
suffix:semicolon
multiline_comment|/* Sync Tx Queue RAM Buffer End Address */
DECL|member|PXaQRamStart
id|SK_U32
id|PXaQRamStart
suffix:semicolon
multiline_comment|/* Async Tx Queue RAM Buffer Start Address */
DECL|member|PXaQRamEnd
id|SK_U32
id|PXaQRamEnd
suffix:semicolon
multiline_comment|/* Async Tx Queue RAM Buffer End Address */
DECL|member|PRxQOff
r_int
id|PRxQOff
suffix:semicolon
multiline_comment|/* Rx Queue Address Offset */
DECL|member|PXsQOff
r_int
id|PXsQOff
suffix:semicolon
multiline_comment|/* Synchronous Tx Queue Address Offset */
DECL|member|PXaQOff
r_int
id|PXaQOff
suffix:semicolon
multiline_comment|/* Asynchronous Tx Queue Address Offset */
DECL|member|PhyType
r_int
id|PhyType
suffix:semicolon
multiline_comment|/* PHY used on this port */
DECL|member|PhyAddr
id|SK_U16
id|PhyAddr
suffix:semicolon
multiline_comment|/* MDIO/MDC PHY address */
DECL|member|PRxCmd
id|SK_U16
id|PRxCmd
suffix:semicolon
multiline_comment|/* Port Receive Command Configuration Value */
DECL|member|PIsave
id|SK_U16
id|PIsave
suffix:semicolon
multiline_comment|/* Saved Interrupt status word */
DECL|member|PSsave
id|SK_U16
id|PSsave
suffix:semicolon
multiline_comment|/* Saved PHY status word */
DECL|member|Align01
id|SK_U16
id|Align01
suffix:semicolon
DECL|member|PHWLinkUp
id|SK_BOOL
id|PHWLinkUp
suffix:semicolon
multiline_comment|/* The hardware Link is up (wireing) */
DECL|member|PState
id|SK_BOOL
id|PState
suffix:semicolon
multiline_comment|/* Is port initialized ? */
DECL|member|PLinkBroken
id|SK_BOOL
id|PLinkBroken
suffix:semicolon
multiline_comment|/* Is Link broken ? */
DECL|member|PCheckPar
id|SK_BOOL
id|PCheckPar
suffix:semicolon
multiline_comment|/* Do we check for parity errors ? */
DECL|member|HalfDupTimerActive
id|SK_BOOL
id|HalfDupTimerActive
suffix:semicolon
DECL|member|PLinkCap
id|SK_U8
id|PLinkCap
suffix:semicolon
multiline_comment|/* Link Capabilities */
DECL|member|PLinkModeConf
id|SK_U8
id|PLinkModeConf
suffix:semicolon
multiline_comment|/* Link Mode configured */
DECL|member|PLinkMode
id|SK_U8
id|PLinkMode
suffix:semicolon
multiline_comment|/* Link Mode currently used */
DECL|member|PLinkModeStatus
id|SK_U8
id|PLinkModeStatus
suffix:semicolon
multiline_comment|/* Link Mode Status */
DECL|member|PFlowCtrlCap
id|SK_U8
id|PFlowCtrlCap
suffix:semicolon
multiline_comment|/* Flow Control Capabilities */
DECL|member|PFlowCtrlMode
id|SK_U8
id|PFlowCtrlMode
suffix:semicolon
multiline_comment|/* Flow Control Mode */
DECL|member|PFlowCtrlStatus
id|SK_U8
id|PFlowCtrlStatus
suffix:semicolon
multiline_comment|/* Flow Control Status */
DECL|member|PMSCap
id|SK_U8
id|PMSCap
suffix:semicolon
multiline_comment|/* Master/Slave Capabilities */
DECL|member|PMSMode
id|SK_U8
id|PMSMode
suffix:semicolon
multiline_comment|/* Master/Slave Mode */
DECL|member|PMSStatus
id|SK_U8
id|PMSStatus
suffix:semicolon
multiline_comment|/* Master/Slave Status */
DECL|member|PAutoNegFail
id|SK_U8
id|PAutoNegFail
suffix:semicolon
multiline_comment|/* Autonegotiation fail flag */
DECL|member|PLipaAutoNeg
id|SK_U8
id|PLipaAutoNeg
suffix:semicolon
multiline_comment|/* Autonegotiation possible with Link Partner */
DECL|member|Align02
id|SK_U8
id|Align02
suffix:semicolon
DECL|typedef|SK_GEPORT
)brace
id|SK_GEPORT
suffix:semicolon
multiline_comment|/*&n; * Gigabit Ethernet Initalization Struct&n; * (has to be included in the adapter context)&n; */
DECL|struct|s_GeInit
r_typedef
r_struct
id|s_GeInit
(brace
DECL|member|GIMacsFound
r_int
id|GIMacsFound
suffix:semicolon
multiline_comment|/* Number of MACs found on this adapter */
DECL|member|GIPciHwRev
r_int
id|GIPciHwRev
suffix:semicolon
multiline_comment|/* PCI HW Revision Number */
DECL|member|GIRamOffs
id|SK_U32
id|GIRamOffs
suffix:semicolon
multiline_comment|/* RAM Address Offset for addr calculation */
DECL|member|GIRamSize
r_int
id|GIRamSize
suffix:semicolon
multiline_comment|/* The RAM size of the adapter in kB */
DECL|member|GIHstClkFact
r_int
id|GIHstClkFact
suffix:semicolon
multiline_comment|/* Host Clock Factor (62.5 / HstClk * 100) */
DECL|member|GIPortUsage
r_int
id|GIPortUsage
suffix:semicolon
multiline_comment|/* driver port usage: SK_RED_LINK/SK_MUL_LINK */
DECL|member|GIPollTimerVal
id|SK_U32
id|GIPollTimerVal
suffix:semicolon
multiline_comment|/* Descriptor Poll Timer Init Val in clk ticks*/
DECL|member|GILevel
r_int
id|GILevel
suffix:semicolon
multiline_comment|/* Initialization Level Completed */
DECL|member|GP
id|SK_GEPORT
id|GP
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
multiline_comment|/* Port Dependent Information */
DECL|member|GIAnyPortAct
id|SK_BOOL
id|GIAnyPortAct
suffix:semicolon
multiline_comment|/* Is True if one or more port is initialized */
DECL|member|Align01
id|SK_U8
id|Align01
suffix:semicolon
DECL|member|Align02
id|SK_U16
id|Align02
suffix:semicolon
DECL|typedef|SK_GEINIT
)brace
id|SK_GEINIT
suffix:semicolon
multiline_comment|/*&n; * Define the error numbers and messages for xmac_ii.c and skgeinit.c&n; */
DECL|macro|SKERR_HWI_E001
mdefine_line|#define&t;SKERR_HWI_E001&t;&t;(SK_ERRBASE_HWINIT)
DECL|macro|SKERR_HWI_E001MSG
mdefine_line|#define&t;SKERR_HWI_E001MSG&t;&quot;SkXmClrExactAddr() has got illegal parameters&quot;
DECL|macro|SKERR_HWI_E002
mdefine_line|#define&t;SKERR_HWI_E002&t;&t;(SKERR_HWI_E001+1)
DECL|macro|SKERR_HWI_E002MSG
mdefine_line|#define&t;SKERR_HWI_E002MSG&t;&quot;SkGeInit() Level 1 call missing&quot;
DECL|macro|SKERR_HWI_E003
mdefine_line|#define&t;SKERR_HWI_E003&t;&t;(SKERR_HWI_E002+1)
DECL|macro|SKERR_HWI_E003MSG
mdefine_line|#define&t;SKERR_HWI_E003MSG&t;&quot;SkGeInit() called with illegal init Level&quot;
DECL|macro|SKERR_HWI_E004
mdefine_line|#define&t;SKERR_HWI_E004&t;&t;(SKERR_HWI_E003+1)
DECL|macro|SKERR_HWI_E004MSG
mdefine_line|#define&t;SKERR_HWI_E004MSG&t;&quot;SkGeInitPort() Queue size illegal configured&quot;
DECL|macro|SKERR_HWI_E005
mdefine_line|#define&t;SKERR_HWI_E005&t;&t;(SKERR_HWI_E004+1)
DECL|macro|SKERR_HWI_E005MSG
mdefine_line|#define&t;SKERR_HWI_E005MSG&t;&quot;SkGeInitPort() cannot init running ports&quot;
DECL|macro|SKERR_HWI_E006
mdefine_line|#define&t;SKERR_HWI_E006&t;&t;(SKERR_HWI_E005+1)
DECL|macro|SKERR_HWI_E006MSG
mdefine_line|#define&t;SKERR_HWI_E006MSG&t;&quot;SkGeXmInit(): PState does not match HW state&quot;
DECL|macro|SKERR_HWI_E007
mdefine_line|#define&t;SKERR_HWI_E007&t;&t;(SKERR_HWI_E006+1)
DECL|macro|SKERR_HWI_E007MSG
mdefine_line|#define&t;SKERR_HWI_E007MSG&t;&quot;SkXmInitDupMd() called with invalid Dup Mode&quot;
DECL|macro|SKERR_HWI_E008
mdefine_line|#define&t;SKERR_HWI_E008&t;&t;(SKERR_HWI_E007+1)
DECL|macro|SKERR_HWI_E008MSG
mdefine_line|#define&t;SKERR_HWI_E008MSG&t;&quot;SkXmSetRxCmd() called with invalid Mode&quot;
DECL|macro|SKERR_HWI_E009
mdefine_line|#define&t;SKERR_HWI_E009&t;&t;(SKERR_HWI_E008+1)
DECL|macro|SKERR_HWI_E009MSG
mdefine_line|#define&t;SKERR_HWI_E009MSG&t;&quot;SkGeCfgSync() called although PXSQSize zero&quot;
DECL|macro|SKERR_HWI_E010
mdefine_line|#define&t;SKERR_HWI_E010&t;&t;(SKERR_HWI_E009+1)
DECL|macro|SKERR_HWI_E010MSG
mdefine_line|#define&t;SKERR_HWI_E010MSG&t;&quot;SkGeCfgSync() called with invalid parameters&quot;
DECL|macro|SKERR_HWI_E011
mdefine_line|#define&t;SKERR_HWI_E011&t;&t;(SKERR_HWI_E010+1)
DECL|macro|SKERR_HWI_E011MSG
mdefine_line|#define&t;SKERR_HWI_E011MSG&t;&quot;SkGeInitPort() Receive Queue Size to small&quot;
DECL|macro|SKERR_HWI_E012
mdefine_line|#define&t;SKERR_HWI_E012&t;&t;(SKERR_HWI_E011+1)
DECL|macro|SKERR_HWI_E012MSG
mdefine_line|#define&t;SKERR_HWI_E012MSG&t;&quot;SkGeInitPort() invalid Queue Size specified&quot;
DECL|macro|SKERR_HWI_E013
mdefine_line|#define&t;SKERR_HWI_E013&t;&t;(SKERR_HWI_E012+1)
DECL|macro|SKERR_HWI_E013MSG
mdefine_line|#define&t;SKERR_HWI_E013MSG&t;&quot;SkGeInitPort() cfg changed for running queue&quot;
DECL|macro|SKERR_HWI_E014
mdefine_line|#define&t;SKERR_HWI_E014&t;&t;(SKERR_HWI_E013+1)
DECL|macro|SKERR_HWI_E014MSG
mdefine_line|#define&t;SKERR_HWI_E014MSG&t;&quot;SkGeInitPort() unknown GIPortUsage specified&quot;
DECL|macro|SKERR_HWI_E015
mdefine_line|#define&t;SKERR_HWI_E015&t;&t;(SKERR_HWI_E014+1)
DECL|macro|SKERR_HWI_E015MSG
mdefine_line|#define&t;SKERR_HWI_E015MSG&t;&quot;Illegal Link mode parameter&quot;
DECL|macro|SKERR_HWI_E016
mdefine_line|#define&t;SKERR_HWI_E016&t;&t;(SKERR_HWI_E015+1)
DECL|macro|SKERR_HWI_E016MSG
mdefine_line|#define&t;SKERR_HWI_E016MSG&t;&quot;Illegal Flow control mode parameter&quot;
DECL|macro|SKERR_HWI_E017
mdefine_line|#define&t;SKERR_HWI_E017&t;&t;(SKERR_HWI_E016+1)
DECL|macro|SKERR_HWI_E017MSG
mdefine_line|#define&t;SKERR_HWI_E017MSG&t;&quot;Illegal value specified for GIPollTimerVal&quot;
DECL|macro|SKERR_HWI_E018
mdefine_line|#define&t;SKERR_HWI_E018&t;&t;(SKERR_HWI_E017+1)
DECL|macro|SKERR_HWI_E018MSG
mdefine_line|#define&t;SKERR_HWI_E018MSG&t;&quot;FATAL: SkGeStopPort() does not terminate&quot;
DECL|macro|SKERR_HWI_E019
mdefine_line|#define&t;SKERR_HWI_E019&t;&t;(SKERR_HWI_E018+1)
DECL|macro|SKERR_HWI_E019MSG
mdefine_line|#define&t;SKERR_HWI_E019MSG&t;&quot;&quot;
multiline_comment|/* function prototypes ********************************************************/
macro_line|#ifndef&t;SK_KR_PROTO
multiline_comment|/*&n; * public functions in skgeinit.c&n; */
r_extern
r_void
id|SkGePollRxD
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
id|SK_BOOL
id|PollRxD
)paren
suffix:semicolon
r_extern
r_void
id|SkGePollTxD
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
id|SK_BOOL
id|PollTxD
)paren
suffix:semicolon
r_extern
r_void
id|SkGeYellowLED
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|State
)paren
suffix:semicolon
r_extern
r_int
id|SkGeCfgSync
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
id|SK_U32
id|IntTime
comma
id|SK_U32
id|LimCount
comma
r_int
id|SyncMode
)paren
suffix:semicolon
r_extern
r_void
id|SkGeLoadLnkSyncCnt
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
id|SK_U32
id|CntVal
)paren
suffix:semicolon
r_extern
r_void
id|SkGeStopPort
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
r_int
id|Dir
comma
r_int
id|RstMode
)paren
suffix:semicolon
r_extern
r_int
id|SkGeInit
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Level
)paren
suffix:semicolon
r_extern
r_void
id|SkGeDeInit
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
)paren
suffix:semicolon
r_extern
r_int
id|SkGeInitPort
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_void
id|SkGeXmitLED
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Led
comma
r_int
id|Mode
)paren
suffix:semicolon
r_extern
r_void
id|SkGeInitRamIface
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
)paren
suffix:semicolon
multiline_comment|/*&n; * public functions in skxmac2.c&n; */
r_extern
r_void
id|SkXmSetRxCmd
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
r_int
id|Mode
)paren
suffix:semicolon
r_extern
r_void
id|SkXmClrExactAddr
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
r_int
id|StartNum
comma
r_int
id|StopNum
)paren
suffix:semicolon
r_extern
r_void
id|SkXmFlushTxFifo
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_void
id|SkXmFlushRxFifo
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_void
id|SkXmSoftRst
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_void
id|SkXmHardRst
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_void
id|SkXmInitMac
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_void
id|SkXmInitDupMd
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_void
id|SkXmInitPauseMd
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_int
id|SkXmAutoNegDone
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_void
id|SkXmAutoNegLipaXmac
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
id|SK_U16
id|IStatus
)paren
suffix:semicolon
r_extern
r_void
id|SkXmAutoNegLipaBcom
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
id|SK_U16
id|IStatus
)paren
suffix:semicolon
r_extern
r_void
id|SkXmAutoNegLipaLone
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
id|SK_U16
id|IStatus
)paren
suffix:semicolon
r_extern
r_void
id|SkXmIrq
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
id|Port
comma
id|SK_U16
id|IStatus
)paren
suffix:semicolon
macro_line|#else&t;/* SK_KR_PROTO */
multiline_comment|/*&n; * public functions in skgeinit.c&n; */
r_extern
r_void
id|SkGePollRxD
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGePollTxD
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGeYellowLED
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkGeCfgSync
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGeLoadLnkSyncCnt
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGeStopPort
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkGeInit
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGeDeInit
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkGeInitPort
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGeXmitLED
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGeInitRamIface
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * public functions in skxmac2.c&n; */
r_extern
r_void
id|SkXmSetRxCmd
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmClrExactAddr
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmFlushTxFifo
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmFlushRxFifo
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmSoftRst
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmHardRst
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmInitMac
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmInitDupMd
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmInitPauseMd
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkXmAutoNegDone
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmAutoNegLipa
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmIrq
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;/* SK_KR_PROTO */
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif&t;/* __cplusplus */
macro_line|#endif&t;/* __INC_SKGEINIT_H_ */
eof
