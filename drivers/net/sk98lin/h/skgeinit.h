multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgeinit.h&n; * Project:&t;Gigabit Ethernet Adapters, Common Modules&n; * Version:&t;$Revision: 1.81 $&n; * Date:&t;$Date: 2003/07/04 12:30:38 $&n; * Purpose:&t;Structures and prototypes for the GE Init Module&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skgeinit.h,v $&n; *&t;Revision 1.81  2003/07/04 12:30:38  rschmidt&n; *&t;Added SK_FAR to pointers in MAC statistic functions (for PXE)&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.80  2003/05/28 15:25:30  rschmidt&n; *&t;Added SK_FAR to pointers in MAC/PHY read functions (for PXE)&n; *&t;Minor changes to avoid LINT warnings&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.79  2003/05/06 12:02:33  rschmidt&n; *&t;Added entry GIYukon in s_GeInit structure&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.78  2003/04/28 08:59:57  rschmidt&n; *&t;Added entries GIValIrqMask and GITimeStampCnt in s_GeInit structure&n; *&n; *&t;Revision 1.77  2003/04/08 16:27:02  rschmidt&n; *&t;Added entry GILedBlinkCtrl in s_GeInit structure&n; *&t;Added defines for LED Blink Control&n; *&n; *&t;Revision 1.76  2003/03/31 07:21:01  mkarl&n; *&t;Added PGmANegAdv to SK_GEPORT.&n; *&t;Corrected Copyright.&n; *&n; *&t;Revision 1.75  2003/02/05 13:36:39  rschmidt&n; *&t;Added define SK_FACT_78&t;for YUKON&squot;s Host Clock of 78.12 MHz&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.74  2003/01/28 09:39:16  rschmidt&n; *&t;Added entry GIYukonLite in s_GeInit structure&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.73  2002/11/15 12:47:25  rschmidt&n; *&t;Replaced error message SKERR_HWI_E024 for Cable Diagnostic with&n; *&t;Rx queue error in SkGeStopPort().&n; *&n; *&t;Revision 1.72  2002/11/12 17:08:35  rschmidt&n; *&t;Added entries for Cable Diagnostic to Port structure&n; *&t;Added entries GIPciSlot64 and GIPciClock66 in s_GeInit structure&n; *&t;Added error message for Cable Diagnostic&n; *&t;Added prototypes for SkGmCableDiagStatus()&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.71  2002/10/21 11:26:10  mkarl&n; *&t;Changed interface of SkGeInitAssignRamToQueues().&n; *&n; *&t;Revision 1.70  2002/10/14 08:21:32  rschmidt&n; *&t;Changed type of GICopperType, GIVauxAvail to SK_BOOL&n; *&t;Added entry PRxOverCnt to Port structure&n; *&t;Added entry GIYukon32Bit in s_GeInit structure&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.69  2002/10/09 16:57:15  mkarl&n; *&t;Added some constants and macros for SkGeInitAssignRamToQueues().&n; *&n; *&t;Revision 1.68  2002/09/12 08:58:51  rwahl&n; *&t;Retrieve counters needed for XMAC errata workarounds directly because&n; *&t;PNMI returns corrected counter values (e.g. #10620).&n; *&n; *&t;Revision 1.67  2002/08/16 14:40:30  rschmidt&n; *&t;Added entries GIGenesis and GICopperType in s_GeInit structure&n; *&t;Added prototypes for SkMacHashing()&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.66  2002/08/12 13:27:21  rschmidt&n; *&t;Added defines for Link speed capabilities&n; *&t;Added entry PLinkSpeedCap to Port structure&n; *&t;Added entry GIVauxAvail in s_GeInit structure&n; *&t;Added prototypes for SkMacPromiscMode()&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.65  2002/08/08 15:46:18  rschmidt&n; *&t;Added define SK_PHY_ACC_TO for PHY access timeout&n; *&t;Added define SK_XM_RX_HI_WM for XMAC Rx High Watermark&n; *&t;Added define SK_MIN_TXQ_SIZE for Min RAM Buffer Tx Queue Size&n; *&t;Added entry PhyId1 to Port structure&n; *&n; *&t;Revision 1.64  2002/07/23 16:02:56  rschmidt&n; *&t;Added entry GIWolOffs in s_GeInit struct (HW-Bug in YUKON 1st rev.)&n; *&t;Added prototypes for: SkGePhyRead(), SkGePhyWrite()&n; *&n; *&t;Revision 1.63  2002/07/18 08:17:38  rwahl&n; *&t;Corrected definitions for SK_LSPEED_xxx &amp; SK_LSPEED_STAT_xxx.&n; *&n; *&t;Revision 1.62  2002/07/17 18:21:55  rwahl&n; *&t;Added SK_LSPEED_INDETERMINATED define.&n; *&n; *&t;Revision 1.61  2002/07/17 17:16:03  rwahl&n; *&t;- MacType now member of GIni struct.&n; *&t;- Struct alignment to 32bit.&n; *&t;- Editorial change.&n; *&n; *&t;Revision 1.60  2002/07/15 18:23:39  rwahl&n; *&t;Added GeMacFunc to GE Init structure.&n; *&t;Added prototypes for SkXmUpdateStats(), SkGmUpdateStats(),&n; *&t;  SkXmMacStatistic(), SkGmMacStatistic(), SkXmResetCounter(),&n; *&t;  SkGmResetCounter(), SkXmOverflowStatus(), SkGmOverflowStatus().&n; *&t;Added defines for current link speed state.&n; *&t;Added ERRMSG defintions for MacUpdateStat() &amp; MacStatistics().&n; *&n; *&t;Revision 1.59  2002/07/15 15:40:22  rschmidt&n; *&t;Added entry PLinkSpeedUsed to Port structure&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.58  2002/06/10 09:36:30  rschmidt&n; *&t;Editorial changes.&n; *&n; *&t;Revision 1.57  2002/06/05 08:18:00  rschmidt&n; *&t;Corrected alignment in Port Structure&n; *&t;Added new prototypes for GMAC&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.56  2002/04/25 11:38:12  rschmidt&n; *&t;Added defines for Link speed values&n; *&t;Added defines for Loopback parameters for MAC and PHY&n; *&t;Removed entry PRxCmd from Port structure&n; *&t;Added entry PLinkSpeed to Port structure&n; *&t;Added entries GIChipId and GIChipRev to GE Init structure&n; *&t;Removed entry GIAnyPortAct from GE Init structure&n; *&t;Added prototypes for: SkMacInit(), SkMacInitPhy(),&n; *&t;SkMacRxTxDisable(), SkMacSoftRst(), SkMacHardRst(), SkMacIrq(),&n; *&t;SkMacIrqDisable(), SkMacFlushTxFifo(), SkMacFlushRxFifo(),&n; *&t;SkMacAutoNegDone(), SkMacAutoNegLipaPhy(), SkMacSetRxTxEn(),&n; *&t;SkXmPhyRead(), SkXmPhyRead(), SkGmPhyWrite(), SkGmPhyWrite();&n; *&t;Removed prototypes for static functions in SkXmac2.c&n; *&t;Editorial changes&n; *&n; *&t;Revision 1.55  2002/02/26 15:24:53  rwahl&n; *&t;Fix: no link with manual configuration (#10673). The previous fix for&n; *&t;#10639 was removed. So for RLMT mode = CLS the RLMT may switch to&n; *&t;misconfigured port. It should not occur for the other RLMT modes.&n; *&n; *&t;Revision 1.54  2002/01/18 16:52:52  rwahl&n; *&t;Editorial corrections.&n; *&n; *&t;Revision 1.53  2001/11/20 09:19:58  rwahl&n; *&t;Reworked bugfix #10639 (no dependency to RLMT mode).&n; *&n; *&t;Revision 1.52  2001/10/26 07:52:23  afischer&n; *&t;Port switching bug in `check local link` mode&n; *&n; *&t;Revision 1.51  2001/02/09 12:26:38  cgoos&n; *&t;Inserted #ifdef DIAG for half duplex workaround timer.&n; *&n; *&t;Revision 1.50  2001/02/07 07:56:40  rassmann&n; *&t;Corrected copyright.&n; *&n; *&t;Revision 1.49  2001/01/31 15:32:18  gklug&n; *&t;fix: problem with autosensing an SR8800 switch&n; *&t;add: counter for autoneg timeouts&n; *&n; *&t;Revision 1.48  2000/11/09 11:30:10  rassmann&n; *&t;WA: Waiting after releasing reset until BCom chip is accessible.&n; *&n; *&t;Revision 1.47  2000/10/18 12:22:40  cgoos&n; *&t;Added workaround for half duplex hangup.&n; *&n; *&t;Revision 1.46  2000/08/10 11:28:00  rassmann&n; *&t;Editorial changes.&n; *&t;Preserving 32-bit alignment in structs for the adapter context.&n; *&n; *&t;Revision 1.45  1999/11/22 13:56:19  cgoos&n; *&t;Changed license header to GPL.&n; *&n; *&t;Revision 1.44  1999/10/26 07:34:15  malthoff&n; *&t;The define SK_LNK_ON has been lost in v1.41.&n; *&n; *&t;Revision 1.43  1999/10/06 09:30:16  cgoos&n; *&t;Changed SK_XM_THR_JUMBO.&n; *&n; *&t;Revision 1.42  1999/09/16 12:58:26  cgoos&n; *&t;Changed SK_LED_STANDY macro to be independent of HW link sync.&n; *&n; *&t;Revision 1.41  1999/07/30 06:56:14  malthoff&n; *&t;Correct comment for SK_MS_STAT_UNSET.&n; *&n; *&t;Revision 1.40  1999/05/27 13:38:46  cgoos&n; *&t;Added SK_BMU_TX_WM.&n; *&t;Made SK_BMU_TX_WM and SK_BMU_RX_WM user-definable.&n; *&t;Changed XMAC Tx treshold to max. values.&n; *&n; *&t;Revision 1.39  1999/05/20 14:35:26  malthoff&n; *&t;Remove prototypes for SkGeLinkLED().&n; *&n; *&t;Revision 1.38  1999/05/19 11:59:12  cgoos&n; *&t;Added SK_MS_CAP_INDETERMINATED define.&n; *&n; *&t;Revision 1.37  1999/05/19 07:32:33  cgoos&n; *&t;Changes for 1000Base-T.&n; *&t;LED-defines for HWAC_LINK_LED macro.&n; *&n; *&t;Revision 1.36  1999/04/08 14:00:24  gklug&n; *&t;add:Port struct field PLinkResCt&n; *&n; *&t;Revision 1.35  1999/03/25 07:43:07  malthoff&n; *&t;Add error string for SKERR_HWI_E018MSG.&n; *&n; *&t;Revision 1.34  1999/03/12 16:25:57  malthoff&n; *&t;Remove PPollRxD and PPollTxD.&n; *&t;Add SKERR_HWI_E017MSG. and SK_DPOLL_MAX.&n; *&n; *&t;Revision 1.33  1999/03/12 13:34:41  malthoff&n; *&t;Add Autonegotiation error codes.&n; *&t;Change defines for parameter Mode in SkXmSetRxCmd().&n; *&t;Replace __STDC__ by SK_KR_PROTO.&n; *&n; *&t;Revision 1.32  1999/01/25 14:40:20  mhaveman&n; *&t;Added new return states for the virtual management port if multiple&n; *&t;ports are active but differently configured.&n; *&n; *&t;Revision 1.31  1998/12/11 15:17:02  gklug&n; *&t;add: Link partnet autoneg states : Unknown Manual and Auto-negotiation&n; *&n; *&t;Revision 1.30  1998/12/07 12:17:04  gklug&n; *&t;add: Link Partner auto-negotiation flag&n; *&n; *&t;Revision 1.29  1998/12/01 10:54:42  gklug&n; *&t;add: variables for XMAC Errata&n; *&n; *&t;Revision 1.28  1998/12/01 10:14:15  gklug&n; *&t;add: PIsave saves the Interrupt status word&n; *&n; *&t;Revision 1.27  1998/11/26 15:24:52  mhaveman&n; *&t;Added link status states SK_LMODE_STAT_AUTOHALF and&n; *&t;SK_LMODE_STAT_AUTOFULL which are used by PNMI.&n; *&n; *&t;Revision 1.26  1998/11/26 14:53:01  gklug&n; *&t;add:autoNeg Timeout variable&n; *&n; *&t;Revision 1.25  1998/11/26 08:58:50  gklug&n; *&t;add: Link Mode configuration (AUTO Sense mode)&n; *&n; *&t;Revision 1.24  1998/11/24 13:30:27  gklug&n; *&t;add: PCheckPar to port struct&n; *&n; *&t;Revision 1.23  1998/11/18 13:23:26  malthoff&n; *&t;Add SK_PKT_TO_MAX.&n; *&n; *&t;Revision 1.22  1998/11/18 13:19:54  gklug&n; *&t;add: PPrevShorts and PLinkBroken to port struct for WA XMAC Errata #C1&n; *&n; *&t;Revision 1.21  1998/10/26 08:02:57  malthoff&n; *&t;Add GIRamOffs.&n; *&n; *&t;Revision 1.20  1998/10/19 07:28:37  malthoff&n; *&t;Add prototype for SkGeInitRamIface().&n; *&n; *&t;Revision 1.19  1998/10/14 14:47:48  malthoff&n; *&t;SK_TIMER should not be defined for Diagnostics.&n; *&t;Add SKERR_HWI_E015MSG and SKERR_HWI_E016MSG.&n; *&n; *&t;Revision 1.18  1998/10/14 14:00:03  gklug&n; *&t;add: timer to port struct for workaround of Errata #2&n; *&n; *&t;Revision 1.17  1998/10/14 11:23:09  malthoff&n; *&t;Add prototype for SkXmAutoNegDone().&n; *&t;Fix SkXmSetRxCmd() prototype statement.&n; *&n; *&t;Revision 1.16  1998/10/14 05:42:29  gklug&n; *&t;add: HWLinkUp flag to Port struct&n; *&n; *&t;Revision 1.15  1998/10/09 08:26:33  malthoff&n; *&t;Rename SK_RB_ULPP_B to SK_RB_LLPP_B.&n; *&n; *&t;Revision 1.14  1998/10/09 07:11:13  malthoff&n; *&t;bug fix: SK_FACT_53 is 85 not 117.&n; *&t;Rework time out init values.&n; *&t;Add GIPortUsage and corresponding defines.&n; *&t;Add some error log messages.&n; *&n; *&t;Revision 1.13  1998/10/06 14:13:14  malthoff&n; *&t;Add prototype for SkGeLoadLnkSyncCnt().&n; *&n; *&t;Revision 1.12  1998/10/05 11:29:53  malthoff&n; *&t;bug fix: A comment was not closed.&n; *&n; *&t;Revision 1.11  1998/10/05 08:01:59  malthoff&n; *&t;Add default Timeout- Threshold- and&n; *&t;Watermark constants. Add QRam start and end&n; *&t;variables. Also add vars to store the polling&n; *&t;mode and receive command. Add new Error Log&n; *&t;Messages and function prototypes.&n; *&n; *&t;Revision 1.10  1998/09/28 13:34:48  malthoff&n; *&t;Add mode bits for LED functions.&n; *&t;Move Autoneg and Flow Ctrl bits from shgesirq.h&n; *&t;Add the required Error Log Entries&n; *&t;and Function Prototypes.&n; *&n; *&t;Revision 1.9  1998/09/16 14:38:41  malthoff&n; *&t;Rework the SK_LNK_xxx defines.&n; *&t;Add error log message defines.&n; *&t;Add prototypes for skxmac2.c&n; *&n; *&t;Revision 1.8  1998/09/11 05:29:18  gklug&n; *&t;add: init state of a port&n; *&n; *&t;Revision 1.7  1998/09/08 08:35:52  gklug&n; *&t;add: defines of the Init Levels&n; *&n; *&t;Revision 1.6  1998/09/03 13:48:42  gklug&n; *&t;add: Link strati, capabilities to Port struct&n; *&n; *&t;Revision 1.5  1998/09/03 13:30:59  malthoff&n; *&t;Add SK_LNK_BLINK and SK_LNK_PERM.&n; *&n; *&t;Revision 1.4  1998/09/03 09:55:31  malthoff&n; *&t;Add constants for parameters Dir and RstMode&n; *&t;when calling SkGeStopPort().&n; *&t;Rework the prototype section.&n; *&t;Add Queue Address offsets PRxQOff, PXsQOff, and PXaQOff.&n; *&t;Remove Ioc with IoC.&n; *&n; *&t;Revision 1.3  1998/08/19 09:11:54  gklug&n; *&t;fix: struct are removed from c-source (see CCC)&n; *&t;add: typedefs for all structs&n; *&n; *&t;Revision 1.2  1998/07/28 12:38:26  malthoff&n; *&t;The prototypes got the parameter &squot;IoC&squot;.&n; *&n; *&t;Revision 1.1  1998/07/23 09:50:24  malthoff&n; *&t;Created.&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKGEINIT_H_
DECL|macro|__INC_SKGEINIT_H_
mdefine_line|#define __INC_SKGEINIT_H_
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif&t;/* __cplusplus */
multiline_comment|/* defines ********************************************************************/
DECL|macro|SK_TEST_VAL
mdefine_line|#define SK_TEST_VAL&t;&t;0x11335577UL
multiline_comment|/* modifying Link LED behaviour (used with SkGeLinkLED()) */
DECL|macro|SK_LNK_OFF
mdefine_line|#define SK_LNK_OFF&t;&t;LED_OFF
DECL|macro|SK_LNK_ON
mdefine_line|#define SK_LNK_ON&t;&t;(LED_ON | LED_BLK_OFF | LED_SYNC_OFF)
DECL|macro|SK_LNK_BLINK
mdefine_line|#define SK_LNK_BLINK&t;(LED_ON | LED_BLK_ON  | LED_SYNC_ON)
DECL|macro|SK_LNK_PERM
mdefine_line|#define SK_LNK_PERM&t;&t;(LED_ON | LED_BLK_OFF | LED_SYNC_ON)
DECL|macro|SK_LNK_TST
mdefine_line|#define SK_LNK_TST&t;&t;(LED_ON | LED_BLK_ON  | LED_SYNC_OFF)
multiline_comment|/* parameter &squot;Mode&squot; when calling SK_HWAC_LINK_LED() */
DECL|macro|SK_LED_OFF
mdefine_line|#define SK_LED_OFF&t;&t;LED_OFF
DECL|macro|SK_LED_ACTIVE
mdefine_line|#define SK_LED_ACTIVE&t;(LED_ON | LED_BLK_OFF | LED_SYNC_OFF)
DECL|macro|SK_LED_STANDBY
mdefine_line|#define SK_LED_STANDBY&t;(LED_ON | LED_BLK_ON  | LED_SYNC_OFF)
multiline_comment|/* addressing LED Registers in SkGeXmitLED() */
DECL|macro|XMIT_LED_INI
mdefine_line|#define XMIT_LED_INI&t;0
DECL|macro|XMIT_LED_CNT
mdefine_line|#define XMIT_LED_CNT&t;(RX_LED_VAL - RX_LED_INI)
DECL|macro|XMIT_LED_CTRL
mdefine_line|#define XMIT_LED_CTRL&t;(RX_LED_CTRL- RX_LED_INI)
DECL|macro|XMIT_LED_TST
mdefine_line|#define XMIT_LED_TST&t;(RX_LED_TST - RX_LED_INI)
multiline_comment|/* parameter &squot;Mode&squot; when calling SkGeXmitLED() */
DECL|macro|SK_LED_DIS
mdefine_line|#define SK_LED_DIS&t;0
DECL|macro|SK_LED_ENA
mdefine_line|#define SK_LED_ENA&t;1
DECL|macro|SK_LED_TST
mdefine_line|#define SK_LED_TST&t;2
multiline_comment|/* Counter and Timer constants, for a host clock of 62.5 MHz */
DECL|macro|SK_XMIT_DUR
mdefine_line|#define SK_XMIT_DUR&t;&t;0x002faf08UL&t;/*  50 ms */
DECL|macro|SK_BLK_DUR
mdefine_line|#define SK_BLK_DUR&t;&t;0x01dcd650UL&t;/* 500 ms */
DECL|macro|SK_DPOLL_DEF
mdefine_line|#define SK_DPOLL_DEF&t;0x00ee6b28UL&t;/* 250 ms at 62.5 MHz */
DECL|macro|SK_DPOLL_MAX
mdefine_line|#define SK_DPOLL_MAX&t;0x00ffffffUL&t;/* 268 ms at 62.5 MHz */
multiline_comment|/* 215 ms at 78.12 MHz */
DECL|macro|SK_FACT_62
mdefine_line|#define SK_FACT_62&t;&t;100&t;&t;&t;/* is given in percent */
DECL|macro|SK_FACT_53
mdefine_line|#define SK_FACT_53&t;&t; 85         /* on GENESIS:&t;53.12 MHz */
DECL|macro|SK_FACT_78
mdefine_line|#define SK_FACT_78&t;&t;125&t;&t;&t;/* on YUKON:&t;78.12 MHz */
multiline_comment|/* Timeout values */
DECL|macro|SK_MAC_TO_53
mdefine_line|#define SK_MAC_TO_53&t;72&t;&t;&t;/* MAC arbiter timeout */
DECL|macro|SK_PKT_TO_53
mdefine_line|#define SK_PKT_TO_53&t;0x2000&t;&t;/* Packet arbiter timeout */
DECL|macro|SK_PKT_TO_MAX
mdefine_line|#define SK_PKT_TO_MAX&t;0xffff&t;&t;/* Maximum value */
DECL|macro|SK_RI_TO_53
mdefine_line|#define SK_RI_TO_53&t;&t;36&t;&t;&t;/* RAM interface timeout */
DECL|macro|SK_PHY_ACC_TO
mdefine_line|#define SK_PHY_ACC_TO&t;600000&t;&t;/* PHY access timeout */
multiline_comment|/* RAM Buffer High Pause Threshold values */
DECL|macro|SK_RB_ULPP
mdefine_line|#define SK_RB_ULPP&t;&t;( 8 * 1024)&t;/* Upper Level in kB/8 */
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
mdefine_line|#define SK_BMU_TX_WM&t;0x600&t;&t;/* BMU Tx Watermark */
macro_line|#endif
multiline_comment|/* XMAC II Rx High Watermark */
DECL|macro|SK_XM_RX_HI_WM
mdefine_line|#define SK_XM_RX_HI_WM&t;0x05aa&t;&t;/* 1450 */
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
mdefine_line|#define SK_RED_LINK&t;&t;1&t;&t;/* redundant link usage */
DECL|macro|SK_MUL_LINK
mdefine_line|#define SK_MUL_LINK&t;&t;2&t;&t;/* multiple link usage */
DECL|macro|SK_JUMBO_LINK
mdefine_line|#define SK_JUMBO_LINK&t;3&t;&t;/* driver uses jumbo frames */
multiline_comment|/* Minimum RAM Buffer Rx Queue Size */
DECL|macro|SK_MIN_RXQ_SIZE
mdefine_line|#define SK_MIN_RXQ_SIZE&t;16&t;&t;/* 16 kB */
multiline_comment|/* Minimum RAM Buffer Tx Queue Size */
DECL|macro|SK_MIN_TXQ_SIZE
mdefine_line|#define SK_MIN_TXQ_SIZE&t;16&t;&t;/* 16 kB */
multiline_comment|/* Queue Size units */
DECL|macro|QZ_UNITS
mdefine_line|#define QZ_UNITS&t;&t;0x7
DECL|macro|QZ_STEP
mdefine_line|#define QZ_STEP&t;&t;&t;8
multiline_comment|/* Percentage of queue size from whole memory */
multiline_comment|/* 80 % for receive */
DECL|macro|RAM_QUOTA_RX
mdefine_line|#define RAM_QUOTA_RX&t;80L
multiline_comment|/* 0% for sync transfer */
DECL|macro|RAM_QUOTA_SYNC
mdefine_line|#define&t;RAM_QUOTA_SYNC&t;0L
multiline_comment|/* the rest (20%) is taken for async transfer */
multiline_comment|/* Get the rounded queue size in Bytes in 8k steps */
DECL|macro|ROUND_QUEUE_SIZE
mdefine_line|#define ROUND_QUEUE_SIZE(SizeInBytes)&t;&t;&t;&t;&t;&bslash;&n;&t;((((unsigned long) (SizeInBytes) + (QZ_STEP*1024L)-1) / 1024) &amp;&t;&bslash;&n;&t;~(QZ_STEP-1))
multiline_comment|/* Get the rounded queue size in KBytes in 8k steps */
DECL|macro|ROUND_QUEUE_SIZE_KB
mdefine_line|#define ROUND_QUEUE_SIZE_KB(Kilobytes) &bslash;&n;&t;ROUND_QUEUE_SIZE((Kilobytes) * 1024L)
multiline_comment|/* Types of RAM Buffer Queues */
DECL|macro|SK_RX_SRAM_Q
mdefine_line|#define SK_RX_SRAM_Q&t;1&t;/* small receive queue */
DECL|macro|SK_RX_BRAM_Q
mdefine_line|#define SK_RX_BRAM_Q&t;2&t;/* big receive queue */
DECL|macro|SK_TX_RAM_Q
mdefine_line|#define SK_TX_RAM_Q&t;&t;3&t;/* small or big transmit queue */
multiline_comment|/* parameter &squot;Dir&squot; when calling SkGeStopPort() */
DECL|macro|SK_STOP_TX
mdefine_line|#define SK_STOP_TX&t;1&t;/* Stops the transmit path, resets the XMAC */
DECL|macro|SK_STOP_RX
mdefine_line|#define SK_STOP_RX&t;2&t;/* Stops the receive path */
DECL|macro|SK_STOP_ALL
mdefine_line|#define SK_STOP_ALL&t;3&t;/* Stops Rx and Tx path, resets the XMAC */
multiline_comment|/* parameter &squot;RstMode&squot; when calling SkGeStopPort() */
DECL|macro|SK_SOFT_RST
mdefine_line|#define SK_SOFT_RST&t;1&t;/* perform a software reset */
DECL|macro|SK_HARD_RST
mdefine_line|#define SK_HARD_RST&t;2&t;/* perform a hardware reset */
multiline_comment|/* Init Levels */
DECL|macro|SK_INIT_DATA
mdefine_line|#define SK_INIT_DATA&t;0&t;/* Init level 0: init data structures */
DECL|macro|SK_INIT_IO
mdefine_line|#define SK_INIT_IO&t;&t;1&t;/* Init level 1: init with IOs */
DECL|macro|SK_INIT_RUN
mdefine_line|#define SK_INIT_RUN&t;&t;2&t;/* Init level 2: init for run time */
multiline_comment|/* Link Mode Parameter */
DECL|macro|SK_LMODE_HALF
mdefine_line|#define SK_LMODE_HALF&t;&t;1&t;/* Half Duplex Mode */
DECL|macro|SK_LMODE_FULL
mdefine_line|#define SK_LMODE_FULL&t;&t;2&t;/* Full Duplex Mode */
DECL|macro|SK_LMODE_AUTOHALF
mdefine_line|#define SK_LMODE_AUTOHALF&t;3&t;/* AutoHalf Duplex Mode */
DECL|macro|SK_LMODE_AUTOFULL
mdefine_line|#define SK_LMODE_AUTOFULL&t;4&t;/* AutoFull Duplex Mode */
DECL|macro|SK_LMODE_AUTOBOTH
mdefine_line|#define SK_LMODE_AUTOBOTH&t;5&t;/* AutoBoth Duplex Mode */
DECL|macro|SK_LMODE_AUTOSENSE
mdefine_line|#define SK_LMODE_AUTOSENSE&t;6&t;/* configured mode auto sensing */
DECL|macro|SK_LMODE_INDETERMINATED
mdefine_line|#define SK_LMODE_INDETERMINATED&t;7&t;/* indeterminated */
multiline_comment|/* Auto-negotiation timeout in 100ms granularity */
DECL|macro|SK_AND_MAX_TO
mdefine_line|#define SK_AND_MAX_TO&t;&t;6&t;/* Wait 600 msec before link comes up */
multiline_comment|/* Auto-negotiation error codes */
DECL|macro|SK_AND_OK
mdefine_line|#define SK_AND_OK&t;&t;&t;0&t;/* no error */
DECL|macro|SK_AND_OTHER
mdefine_line|#define SK_AND_OTHER&t;&t;1&t;/* other error than below */
DECL|macro|SK_AND_DUP_CAP
mdefine_line|#define SK_AND_DUP_CAP&t;&t;2&t;/* Duplex capabilities error */
multiline_comment|/* Link Speed Capabilities */
DECL|macro|SK_LSPEED_CAP_AUTO
mdefine_line|#define SK_LSPEED_CAP_AUTO&t;&t;&t;(1&lt;&lt;0)&t;/* Automatic resolution */
DECL|macro|SK_LSPEED_CAP_10MBPS
mdefine_line|#define SK_LSPEED_CAP_10MBPS&t;&t;(1&lt;&lt;1)&t;/* 10 Mbps */
DECL|macro|SK_LSPEED_CAP_100MBPS
mdefine_line|#define SK_LSPEED_CAP_100MBPS&t;&t;(1&lt;&lt;2)&t;/* 100 Mbps */
DECL|macro|SK_LSPEED_CAP_1000MBPS
mdefine_line|#define SK_LSPEED_CAP_1000MBPS&t;&t;(1&lt;&lt;3)&t;/* 1000 Mbps */
DECL|macro|SK_LSPEED_CAP_INDETERMINATED
mdefine_line|#define SK_LSPEED_CAP_INDETERMINATED (1&lt;&lt;4) /* indeterminated */
multiline_comment|/* Link Speed Parameter */
DECL|macro|SK_LSPEED_AUTO
mdefine_line|#define SK_LSPEED_AUTO&t;&t;&t;&t;1&t;/* Automatic resolution */
DECL|macro|SK_LSPEED_10MBPS
mdefine_line|#define SK_LSPEED_10MBPS&t;&t;&t;2&t;/* 10 Mbps */
DECL|macro|SK_LSPEED_100MBPS
mdefine_line|#define SK_LSPEED_100MBPS&t;&t;&t;3&t;/* 100 Mbps */
DECL|macro|SK_LSPEED_1000MBPS
mdefine_line|#define SK_LSPEED_1000MBPS&t;&t;&t;4&t;/* 1000 Mbps */
DECL|macro|SK_LSPEED_INDETERMINATED
mdefine_line|#define SK_LSPEED_INDETERMINATED&t;5&t;/* indeterminated */
multiline_comment|/* Link Speed Current State */
DECL|macro|SK_LSPEED_STAT_UNKNOWN
mdefine_line|#define SK_LSPEED_STAT_UNKNOWN&t;&t;1
DECL|macro|SK_LSPEED_STAT_10MBPS
mdefine_line|#define SK_LSPEED_STAT_10MBPS&t;&t;2
DECL|macro|SK_LSPEED_STAT_100MBPS
mdefine_line|#define SK_LSPEED_STAT_100MBPS &t;&t;3
DECL|macro|SK_LSPEED_STAT_1000MBPS
mdefine_line|#define SK_LSPEED_STAT_1000MBPS&t;&t;4
DECL|macro|SK_LSPEED_STAT_INDETERMINATED
mdefine_line|#define SK_LSPEED_STAT_INDETERMINATED 5
multiline_comment|/* Link Capability Parameter */
DECL|macro|SK_LMODE_CAP_HALF
mdefine_line|#define SK_LMODE_CAP_HALF&t;&t;(1&lt;&lt;0)&t;/* Half Duplex Mode */
DECL|macro|SK_LMODE_CAP_FULL
mdefine_line|#define SK_LMODE_CAP_FULL&t;&t;(1&lt;&lt;1)&t;/* Full Duplex Mode */
DECL|macro|SK_LMODE_CAP_AUTOHALF
mdefine_line|#define SK_LMODE_CAP_AUTOHALF&t;(1&lt;&lt;2)&t;/* AutoHalf Duplex Mode */
DECL|macro|SK_LMODE_CAP_AUTOFULL
mdefine_line|#define SK_LMODE_CAP_AUTOFULL&t;(1&lt;&lt;3)&t;/* AutoFull Duplex Mode */
DECL|macro|SK_LMODE_CAP_INDETERMINATED
mdefine_line|#define SK_LMODE_CAP_INDETERMINATED (1&lt;&lt;4) /* indeterminated */
multiline_comment|/* Link Mode Current State */
DECL|macro|SK_LMODE_STAT_UNKNOWN
mdefine_line|#define SK_LMODE_STAT_UNKNOWN&t;1&t;/* Unknown Duplex Mode */
DECL|macro|SK_LMODE_STAT_HALF
mdefine_line|#define SK_LMODE_STAT_HALF&t;&t;2&t;/* Half Duplex Mode */
DECL|macro|SK_LMODE_STAT_FULL
mdefine_line|#define SK_LMODE_STAT_FULL&t;&t;3&t;/* Full Duplex Mode */
DECL|macro|SK_LMODE_STAT_AUTOHALF
mdefine_line|#define SK_LMODE_STAT_AUTOHALF&t;4&t;/* Half Duplex Mode obtained by Auto-Neg */
DECL|macro|SK_LMODE_STAT_AUTOFULL
mdefine_line|#define SK_LMODE_STAT_AUTOFULL&t;5&t;/* Full Duplex Mode obtained by Auto-Neg */
DECL|macro|SK_LMODE_STAT_INDETERMINATED
mdefine_line|#define SK_LMODE_STAT_INDETERMINATED 6&t;/* indeterminated */
multiline_comment|/* Flow Control Mode Parameter (and capabilities) */
DECL|macro|SK_FLOW_MODE_NONE
mdefine_line|#define SK_FLOW_MODE_NONE&t;&t;1&t;/* No Flow-Control */
DECL|macro|SK_FLOW_MODE_LOC_SEND
mdefine_line|#define SK_FLOW_MODE_LOC_SEND&t;2&t;/* Local station sends PAUSE */
DECL|macro|SK_FLOW_MODE_SYMMETRIC
mdefine_line|#define SK_FLOW_MODE_SYMMETRIC&t;3&t;/* Both stations may send PAUSE */
DECL|macro|SK_FLOW_MODE_SYM_OR_REM
mdefine_line|#define SK_FLOW_MODE_SYM_OR_REM&t;4&t;/* Both stations may send PAUSE or&n;&t;&t;&t;&t;&t; * just the remote station may send PAUSE&n;&t;&t;&t;&t;&t; */
DECL|macro|SK_FLOW_MODE_INDETERMINATED
mdefine_line|#define SK_FLOW_MODE_INDETERMINATED 5&t;/* indeterminated */
multiline_comment|/* Flow Control Status Parameter */
DECL|macro|SK_FLOW_STAT_NONE
mdefine_line|#define SK_FLOW_STAT_NONE&t;&t;1&t;/* No Flow Control */
DECL|macro|SK_FLOW_STAT_REM_SEND
mdefine_line|#define SK_FLOW_STAT_REM_SEND&t;2&t;/* Remote Station sends PAUSE */
DECL|macro|SK_FLOW_STAT_LOC_SEND
mdefine_line|#define SK_FLOW_STAT_LOC_SEND&t;3&t;/* Local station sends PAUSE */
DECL|macro|SK_FLOW_STAT_SYMMETRIC
mdefine_line|#define SK_FLOW_STAT_SYMMETRIC&t;4&t;/* Both station may send PAUSE */
DECL|macro|SK_FLOW_STAT_INDETERMINATED
mdefine_line|#define SK_FLOW_STAT_INDETERMINATED 5&t;/* indeterminated */
multiline_comment|/* Master/Slave Mode Capabilities */
DECL|macro|SK_MS_CAP_AUTO
mdefine_line|#define SK_MS_CAP_AUTO&t;&t;(1&lt;&lt;0)&t;/* Automatic resolution */
DECL|macro|SK_MS_CAP_MASTER
mdefine_line|#define SK_MS_CAP_MASTER&t;(1&lt;&lt;1)&t;/* This station is master */
DECL|macro|SK_MS_CAP_SLAVE
mdefine_line|#define SK_MS_CAP_SLAVE&t;&t;(1&lt;&lt;2)&t;/* This station is slave */
DECL|macro|SK_MS_CAP_INDETERMINATED
mdefine_line|#define SK_MS_CAP_INDETERMINATED (1&lt;&lt;3)&t;/* indeterminated */
multiline_comment|/* Set Master/Slave Mode Parameter (and capabilities) */
DECL|macro|SK_MS_MODE_AUTO
mdefine_line|#define SK_MS_MODE_AUTO&t;&t;1&t;/* Automatic resolution */
DECL|macro|SK_MS_MODE_MASTER
mdefine_line|#define SK_MS_MODE_MASTER&t;2&t;/* This station is master */
DECL|macro|SK_MS_MODE_SLAVE
mdefine_line|#define SK_MS_MODE_SLAVE&t;3&t;/* This station is slave */
DECL|macro|SK_MS_MODE_INDETERMINATED
mdefine_line|#define SK_MS_MODE_INDETERMINATED 4&t;/* indeterminated */
multiline_comment|/* Master/Slave Status Parameter */
DECL|macro|SK_MS_STAT_UNSET
mdefine_line|#define SK_MS_STAT_UNSET&t;1&t;/* The M/S status is not set */
DECL|macro|SK_MS_STAT_MASTER
mdefine_line|#define SK_MS_STAT_MASTER&t;2&t;/* This station is master */
DECL|macro|SK_MS_STAT_SLAVE
mdefine_line|#define SK_MS_STAT_SLAVE&t;3&t;/* This station is slave */
DECL|macro|SK_MS_STAT_FAULT
mdefine_line|#define SK_MS_STAT_FAULT&t;4&t;/* M/S resolution failed */
DECL|macro|SK_MS_STAT_INDETERMINATED
mdefine_line|#define SK_MS_STAT_INDETERMINATED 5&t;/* indeterminated */
multiline_comment|/* parameter &squot;Mode&squot; when calling SkXmSetRxCmd() */
DECL|macro|SK_STRIP_FCS_ON
mdefine_line|#define SK_STRIP_FCS_ON&t;&t;(1&lt;&lt;0)&t;/* Enable  FCS stripping of Rx frames */
DECL|macro|SK_STRIP_FCS_OFF
mdefine_line|#define SK_STRIP_FCS_OFF&t;(1&lt;&lt;1)&t;/* Disable FCS stripping of Rx frames */
DECL|macro|SK_STRIP_PAD_ON
mdefine_line|#define SK_STRIP_PAD_ON&t;&t;(1&lt;&lt;2)&t;/* Enable  pad byte stripping of Rx fr */
DECL|macro|SK_STRIP_PAD_OFF
mdefine_line|#define SK_STRIP_PAD_OFF&t;(1&lt;&lt;3)&t;/* Disable pad byte stripping of Rx fr */
DECL|macro|SK_LENERR_OK_ON
mdefine_line|#define SK_LENERR_OK_ON&t;&t;(1&lt;&lt;4)&t;/* Don&squot;t chk fr for in range len error */
DECL|macro|SK_LENERR_OK_OFF
mdefine_line|#define SK_LENERR_OK_OFF&t;(1&lt;&lt;5)&t;/* Check frames for in range len error */
DECL|macro|SK_BIG_PK_OK_ON
mdefine_line|#define SK_BIG_PK_OK_ON&t;&t;(1&lt;&lt;6)&t;/* Don&squot;t set Rx Error bit for big frames */
DECL|macro|SK_BIG_PK_OK_OFF
mdefine_line|#define SK_BIG_PK_OK_OFF&t;(1&lt;&lt;7)&t;/* Set Rx Error bit for big frames */
DECL|macro|SK_SELF_RX_ON
mdefine_line|#define SK_SELF_RX_ON&t;&t;(1&lt;&lt;8)&t;/* Enable  Rx of own packets */
DECL|macro|SK_SELF_RX_OFF
mdefine_line|#define SK_SELF_RX_OFF&t;&t;(1&lt;&lt;9)&t;/* Disable Rx of own packets */
multiline_comment|/* parameter &squot;Para&squot; when calling SkMacSetRxTxEn() */
DECL|macro|SK_MAC_LOOPB_ON
mdefine_line|#define SK_MAC_LOOPB_ON&t;&t;(1&lt;&lt;0)&t;/* Enable  MAC Loopback Mode */
DECL|macro|SK_MAC_LOOPB_OFF
mdefine_line|#define SK_MAC_LOOPB_OFF&t;(1&lt;&lt;1)&t;/* Disable MAC Loopback Mode */
DECL|macro|SK_PHY_LOOPB_ON
mdefine_line|#define SK_PHY_LOOPB_ON&t;&t;(1&lt;&lt;2)&t;/* Enable  PHY Loopback Mode */
DECL|macro|SK_PHY_LOOPB_OFF
mdefine_line|#define SK_PHY_LOOPB_OFF&t;(1&lt;&lt;3)&t;/* Disable PHY Loopback Mode */
DECL|macro|SK_PHY_FULLD_ON
mdefine_line|#define SK_PHY_FULLD_ON&t;&t;(1&lt;&lt;4)&t;/* Enable  GMII Full Duplex */
DECL|macro|SK_PHY_FULLD_OFF
mdefine_line|#define SK_PHY_FULLD_OFF&t;(1&lt;&lt;5)&t;/* Disable GMII Full Duplex */
multiline_comment|/* States of PState */
DECL|macro|SK_PRT_RESET
mdefine_line|#define SK_PRT_RESET&t;0&t;/* the port is reset */
DECL|macro|SK_PRT_STOP
mdefine_line|#define SK_PRT_STOP&t;&t;1&t;/* the port is stopped (similar to SW reset) */
DECL|macro|SK_PRT_INIT
mdefine_line|#define SK_PRT_INIT&t;&t;2&t;/* the port is initialized */
DECL|macro|SK_PRT_RUN
mdefine_line|#define SK_PRT_RUN&t;&t;3&t;/* the port has an active link */
multiline_comment|/* Default receive frame limit for Workaround of XMAC Errata */
DECL|macro|SK_DEF_RX_WA_LIM
mdefine_line|#define SK_DEF_RX_WA_LIM&t;SK_CONSTU64(100)
multiline_comment|/* values for GILedBlinkCtrl (LED Blink Control) */
DECL|macro|SK_ACT_LED_BLINK
mdefine_line|#define SK_ACT_LED_BLINK&t;(1&lt;&lt;0)&t;/* Active LED blinking */
DECL|macro|SK_DUP_LED_NORMAL
mdefine_line|#define SK_DUP_LED_NORMAL&t;(1&lt;&lt;1)&t;/* Duplex LED normal */
DECL|macro|SK_LED_LINK100_ON
mdefine_line|#define SK_LED_LINK100_ON&t;(1&lt;&lt;2)&t;/* Link 100M LED on */
multiline_comment|/* Link Partner Status */
DECL|macro|SK_LIPA_UNKNOWN
mdefine_line|#define SK_LIPA_UNKNOWN&t;0&t;/* Link partner is in unknown state */
DECL|macro|SK_LIPA_MANUAL
mdefine_line|#define SK_LIPA_MANUAL&t;1&t;/* Link partner is in detected manual state */
DECL|macro|SK_LIPA_AUTO
mdefine_line|#define SK_LIPA_AUTO&t;2&t;/* Link partner is in auto-negotiation state */
multiline_comment|/* Maximum Restarts before restart is ignored (3Com WA) */
DECL|macro|SK_MAX_LRESTART
mdefine_line|#define SK_MAX_LRESTART&t;3&t;/* Max. 3 times the link is restarted */
multiline_comment|/* Max. Auto-neg. timeouts before link detection in sense mode is reset */
DECL|macro|SK_MAX_ANEG_TO
mdefine_line|#define SK_MAX_ANEG_TO&t;10&t;/* Max. 10 times the sense mode is reset */
multiline_comment|/* structures *****************************************************************/
multiline_comment|/*&n; * MAC specific functions&n; */
DECL|struct|s_GeMacFunc
r_typedef
r_struct
id|s_GeMacFunc
(brace
DECL|member|pFnMacUpdateStats
r_int
(paren
op_star
id|pFnMacUpdateStats
)paren
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
r_int
id|Port
)paren
suffix:semicolon
DECL|member|pFnMacStatistic
r_int
(paren
op_star
id|pFnMacStatistic
)paren
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
r_int
id|Port
comma
id|SK_U16
id|StatAddr
comma
id|SK_U32
id|SK_FAR
op_star
id|pVal
)paren
suffix:semicolon
DECL|member|pFnMacResetCounter
r_int
(paren
op_star
id|pFnMacResetCounter
)paren
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
r_int
id|Port
)paren
suffix:semicolon
DECL|member|pFnMacOverflow
r_int
(paren
op_star
id|pFnMacOverflow
)paren
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
r_int
r_int
id|Port
comma
id|SK_U16
id|IStatus
comma
id|SK_U64
id|SK_FAR
op_star
id|pVal
)paren
suffix:semicolon
DECL|typedef|SK_GEMACFUNC
)brace
id|SK_GEMACFUNC
suffix:semicolon
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
DECL|member|HalfDupChkTimer
id|SK_TIMER
id|HalfDupChkTimer
suffix:semicolon
macro_line|#endif /* SK_DIAG */
DECL|member|PPrevShorts
id|SK_U32
id|PPrevShorts
suffix:semicolon
multiline_comment|/* Previous Short Counter checking */
DECL|member|PPrevFcs
id|SK_U32
id|PPrevFcs
suffix:semicolon
multiline_comment|/* Previous FCS Error Counter checking */
DECL|member|PPrevRx
id|SK_U64
id|PPrevRx
suffix:semicolon
multiline_comment|/* Previous RxOk Counter checking */
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
DECL|member|PLinkResCt
r_int
id|PLinkResCt
suffix:semicolon
multiline_comment|/* Link Restart Counter */
DECL|member|PAutoNegTimeOut
r_int
id|PAutoNegTimeOut
suffix:semicolon
multiline_comment|/* Auto-negotiation timeout current value */
DECL|member|PAutoNegTOCt
r_int
id|PAutoNegTOCt
suffix:semicolon
multiline_comment|/* Auto-negotiation Timeout Counter */
DECL|member|PRxQSize
r_int
id|PRxQSize
suffix:semicolon
multiline_comment|/* Port Rx Queue Size in kB */
DECL|member|PXSQSize
r_int
id|PXSQSize
suffix:semicolon
multiline_comment|/* Port Synchronous  Transmit Queue Size in kB */
DECL|member|PXAQSize
r_int
id|PXAQSize
suffix:semicolon
multiline_comment|/* Port Asynchronous Transmit Queue Size in kB */
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
DECL|member|PRxOverCnt
id|SK_U32
id|PRxOverCnt
suffix:semicolon
multiline_comment|/* Receive Overflow Counter */
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
DECL|member|PState
r_int
id|PState
suffix:semicolon
multiline_comment|/* Port status (reset, stop, init, run) */
DECL|member|PhyId1
id|SK_U16
id|PhyId1
suffix:semicolon
multiline_comment|/* PHY Id1 on this port */
DECL|member|PhyAddr
id|SK_U16
id|PhyAddr
suffix:semicolon
multiline_comment|/* MDIO/MDC PHY address */
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
DECL|member|PGmANegAdv
id|SK_U16
id|PGmANegAdv
suffix:semicolon
multiline_comment|/* Saved GPhy AutoNegAdvertisment register */
DECL|member|PHWLinkUp
id|SK_BOOL
id|PHWLinkUp
suffix:semicolon
multiline_comment|/* The hardware Link is up (wiring) */
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
DECL|member|PLinkSpeedCap
id|SK_U8
id|PLinkSpeedCap
suffix:semicolon
multiline_comment|/* Link Speed Capabilities(10/100/1000 Mbps) */
DECL|member|PLinkSpeed
id|SK_U8
id|PLinkSpeed
suffix:semicolon
multiline_comment|/* configured Link Speed (10/100/1000 Mbps) */
DECL|member|PLinkSpeedUsed
id|SK_U8
id|PLinkSpeedUsed
suffix:semicolon
multiline_comment|/* current Link Speed (10/100/1000 Mbps) */
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
id|SK_BOOL
id|PAutoNegFail
suffix:semicolon
multiline_comment|/* Auto-negotiation fail flag */
DECL|member|PLipaAutoNeg
id|SK_U8
id|PLipaAutoNeg
suffix:semicolon
multiline_comment|/* Auto-negotiation possible with Link Partner */
DECL|member|PCableLen
id|SK_U8
id|PCableLen
suffix:semicolon
multiline_comment|/* Cable Length */
DECL|member|PMdiPairLen
id|SK_U8
id|PMdiPairLen
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* MDI[0..3] Pair Length */
DECL|member|PMdiPairSts
id|SK_U8
id|PMdiPairSts
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* MDI[0..3] Pair Diagnostic Status */
DECL|typedef|SK_GEPORT
)brace
id|SK_GEPORT
suffix:semicolon
multiline_comment|/*&n; * Gigabit Ethernet Initialization Struct&n; * (has to be included in the adapter context)&n; */
DECL|struct|s_GeInit
r_typedef
r_struct
id|s_GeInit
(brace
DECL|member|GIChipId
r_int
id|GIChipId
suffix:semicolon
multiline_comment|/* Chip Identification Number */
DECL|member|GIChipRev
r_int
id|GIChipRev
suffix:semicolon
multiline_comment|/* Chip Revision Number */
DECL|member|GIPciHwRev
id|SK_U8
id|GIPciHwRev
suffix:semicolon
multiline_comment|/* PCI HW Revision Number */
DECL|member|GIGenesis
id|SK_BOOL
id|GIGenesis
suffix:semicolon
multiline_comment|/* Genesis adapter ? */
DECL|member|GIYukon
id|SK_BOOL
id|GIYukon
suffix:semicolon
multiline_comment|/* YUKON-A1/Bx chip */
DECL|member|GIYukonLite
id|SK_BOOL
id|GIYukonLite
suffix:semicolon
multiline_comment|/* YUKON-Lite chip */
DECL|member|GICopperType
id|SK_BOOL
id|GICopperType
suffix:semicolon
multiline_comment|/* Copper Type adapter ? */
DECL|member|GIPciSlot64
id|SK_BOOL
id|GIPciSlot64
suffix:semicolon
multiline_comment|/* 64-bit PCI Slot */
DECL|member|GIPciClock66
id|SK_BOOL
id|GIPciClock66
suffix:semicolon
multiline_comment|/* 66 MHz PCI Clock */
DECL|member|GIVauxAvail
id|SK_BOOL
id|GIVauxAvail
suffix:semicolon
multiline_comment|/* VAUX available (YUKON) */
DECL|member|GIYukon32Bit
id|SK_BOOL
id|GIYukon32Bit
suffix:semicolon
multiline_comment|/* 32-Bit YUKON adapter */
DECL|member|GILedBlinkCtrl
id|SK_U16
id|GILedBlinkCtrl
suffix:semicolon
multiline_comment|/* LED Blink Control */
DECL|member|GIMacsFound
r_int
id|GIMacsFound
suffix:semicolon
multiline_comment|/* Number of MACs found on this adapter */
DECL|member|GIMacType
r_int
id|GIMacType
suffix:semicolon
multiline_comment|/* MAC Type used on this adapter */
DECL|member|GIHstClkFact
r_int
id|GIHstClkFact
suffix:semicolon
multiline_comment|/* Host Clock Factor (62.5 / HstClk * 100) */
DECL|member|GIPortUsage
r_int
id|GIPortUsage
suffix:semicolon
multiline_comment|/* Driver Port Usage */
DECL|member|GILevel
r_int
id|GILevel
suffix:semicolon
multiline_comment|/* Initialization Level completed */
DECL|member|GIRamSize
r_int
id|GIRamSize
suffix:semicolon
multiline_comment|/* The RAM size of the adapter in kB */
DECL|member|GIWolOffs
r_int
id|GIWolOffs
suffix:semicolon
multiline_comment|/* WOL Register Offset (HW-Bug in Rev. A) */
DECL|member|GIRamOffs
id|SK_U32
id|GIRamOffs
suffix:semicolon
multiline_comment|/* RAM Address Offset for addr calculation */
DECL|member|GIPollTimerVal
id|SK_U32
id|GIPollTimerVal
suffix:semicolon
multiline_comment|/* Descr. Poll Timer Init Val (HstClk ticks) */
DECL|member|GIValIrqMask
id|SK_U32
id|GIValIrqMask
suffix:semicolon
multiline_comment|/* Value for Interrupt Mask */
DECL|member|GITimeStampCnt
id|SK_U32
id|GITimeStampCnt
suffix:semicolon
multiline_comment|/* Time Stamp High Counter (YUKON only) */
DECL|member|GP
id|SK_GEPORT
id|GP
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
multiline_comment|/* Port Dependent Information */
DECL|member|GIFunc
id|SK_GEMACFUNC
id|GIFunc
suffix:semicolon
multiline_comment|/* MAC depedent functions */
DECL|typedef|SK_GEINIT
)brace
id|SK_GEINIT
suffix:semicolon
multiline_comment|/*&n; * Error numbers and messages for skxmac2.c and skgeinit.c&n; */
DECL|macro|SKERR_HWI_E001
mdefine_line|#define SKERR_HWI_E001&t;&t;(SK_ERRBASE_HWINIT)
DECL|macro|SKERR_HWI_E001MSG
mdefine_line|#define SKERR_HWI_E001MSG&t;&quot;SkXmClrExactAddr() has got invalid parameters&quot;
DECL|macro|SKERR_HWI_E002
mdefine_line|#define SKERR_HWI_E002&t;&t;(SKERR_HWI_E001+1)
DECL|macro|SKERR_HWI_E002MSG
mdefine_line|#define SKERR_HWI_E002MSG&t;&quot;SkGeInit(): Level 1 call missing&quot;
DECL|macro|SKERR_HWI_E003
mdefine_line|#define SKERR_HWI_E003&t;&t;(SKERR_HWI_E002+1)
DECL|macro|SKERR_HWI_E003MSG
mdefine_line|#define SKERR_HWI_E003MSG&t;&quot;SkGeInit() called with invalid init Level&quot;
DECL|macro|SKERR_HWI_E004
mdefine_line|#define SKERR_HWI_E004&t;&t;(SKERR_HWI_E003+1)
DECL|macro|SKERR_HWI_E004MSG
mdefine_line|#define SKERR_HWI_E004MSG&t;&quot;SkGeInitPort(): Queue Size invalid configured&quot;
DECL|macro|SKERR_HWI_E005
mdefine_line|#define SKERR_HWI_E005&t;&t;(SKERR_HWI_E004+1)
DECL|macro|SKERR_HWI_E005MSG
mdefine_line|#define SKERR_HWI_E005MSG&t;&quot;SkGeInitPort(): cannot init running ports&quot;
DECL|macro|SKERR_HWI_E006
mdefine_line|#define SKERR_HWI_E006&t;&t;(SKERR_HWI_E005+1)
DECL|macro|SKERR_HWI_E006MSG
mdefine_line|#define SKERR_HWI_E006MSG&t;&quot;SkGeMacInit(): PState does not match HW state&quot;
DECL|macro|SKERR_HWI_E007
mdefine_line|#define SKERR_HWI_E007&t;&t;(SKERR_HWI_E006+1)
DECL|macro|SKERR_HWI_E007MSG
mdefine_line|#define SKERR_HWI_E007MSG&t;&quot;SkXmInitDupMd() called with invalid Dup Mode&quot;
DECL|macro|SKERR_HWI_E008
mdefine_line|#define SKERR_HWI_E008&t;&t;(SKERR_HWI_E007+1)
DECL|macro|SKERR_HWI_E008MSG
mdefine_line|#define SKERR_HWI_E008MSG&t;&quot;SkXmSetRxCmd() called with invalid Mode&quot;
DECL|macro|SKERR_HWI_E009
mdefine_line|#define SKERR_HWI_E009&t;&t;(SKERR_HWI_E008+1)
DECL|macro|SKERR_HWI_E009MSG
mdefine_line|#define SKERR_HWI_E009MSG&t;&quot;SkGeCfgSync() called although PXSQSize zero&quot;
DECL|macro|SKERR_HWI_E010
mdefine_line|#define SKERR_HWI_E010&t;&t;(SKERR_HWI_E009+1)
DECL|macro|SKERR_HWI_E010MSG
mdefine_line|#define SKERR_HWI_E010MSG&t;&quot;SkGeCfgSync() called with invalid parameters&quot;
DECL|macro|SKERR_HWI_E011
mdefine_line|#define SKERR_HWI_E011&t;&t;(SKERR_HWI_E010+1)
DECL|macro|SKERR_HWI_E011MSG
mdefine_line|#define SKERR_HWI_E011MSG&t;&quot;SkGeInitPort(): Receive Queue Size too small&quot;
DECL|macro|SKERR_HWI_E012
mdefine_line|#define SKERR_HWI_E012&t;&t;(SKERR_HWI_E011+1)
DECL|macro|SKERR_HWI_E012MSG
mdefine_line|#define SKERR_HWI_E012MSG&t;&quot;SkGeInitPort(): invalid Queue Size specified&quot;
DECL|macro|SKERR_HWI_E013
mdefine_line|#define SKERR_HWI_E013&t;&t;(SKERR_HWI_E012+1)
DECL|macro|SKERR_HWI_E013MSG
mdefine_line|#define SKERR_HWI_E013MSG&t;&quot;SkGeInitPort(): cfg changed for running queue&quot;
DECL|macro|SKERR_HWI_E014
mdefine_line|#define SKERR_HWI_E014&t;&t;(SKERR_HWI_E013+1)
DECL|macro|SKERR_HWI_E014MSG
mdefine_line|#define SKERR_HWI_E014MSG&t;&quot;SkGeInitPort(): unknown GIPortUsage specified&quot;
DECL|macro|SKERR_HWI_E015
mdefine_line|#define SKERR_HWI_E015&t;&t;(SKERR_HWI_E014+1)
DECL|macro|SKERR_HWI_E015MSG
mdefine_line|#define SKERR_HWI_E015MSG&t;&quot;Invalid Link mode parameter&quot;
DECL|macro|SKERR_HWI_E016
mdefine_line|#define SKERR_HWI_E016&t;&t;(SKERR_HWI_E015+1)
DECL|macro|SKERR_HWI_E016MSG
mdefine_line|#define SKERR_HWI_E016MSG&t;&quot;Invalid Flow control mode parameter&quot;
DECL|macro|SKERR_HWI_E017
mdefine_line|#define SKERR_HWI_E017&t;&t;(SKERR_HWI_E016+1)
DECL|macro|SKERR_HWI_E017MSG
mdefine_line|#define SKERR_HWI_E017MSG&t;&quot;Invalid value specified for GIPollTimerVal&quot;
DECL|macro|SKERR_HWI_E018
mdefine_line|#define SKERR_HWI_E018&t;&t;(SKERR_HWI_E017+1)
DECL|macro|SKERR_HWI_E018MSG
mdefine_line|#define SKERR_HWI_E018MSG&t;&quot;FATAL: SkGeStopPort() does not terminate (Tx)&quot;
DECL|macro|SKERR_HWI_E019
mdefine_line|#define SKERR_HWI_E019&t;&t;(SKERR_HWI_E018+1)
DECL|macro|SKERR_HWI_E019MSG
mdefine_line|#define SKERR_HWI_E019MSG&t;&quot;Invalid Speed parameter&quot;
DECL|macro|SKERR_HWI_E020
mdefine_line|#define SKERR_HWI_E020&t;&t;(SKERR_HWI_E019+1)
DECL|macro|SKERR_HWI_E020MSG
mdefine_line|#define SKERR_HWI_E020MSG&t;&quot;Invalid Master/Slave parameter&quot;
DECL|macro|SKERR_HWI_E021
mdefine_line|#define SKERR_HWI_E021&t;&t;(SKERR_HWI_E020+1)
DECL|macro|SKERR_HWI_E021MSG
mdefine_line|#define&t;SKERR_HWI_E021MSG&t;&quot;MacUpdateStats(): cannot update statistic counter&quot;
DECL|macro|SKERR_HWI_E022
mdefine_line|#define&t;SKERR_HWI_E022&t;&t;(SKERR_HWI_E021+1)
DECL|macro|SKERR_HWI_E022MSG
mdefine_line|#define&t;SKERR_HWI_E022MSG&t;&quot;MacStatistic(): invalid statistic base address&quot;
DECL|macro|SKERR_HWI_E023
mdefine_line|#define SKERR_HWI_E023&t;&t;(SKERR_HWI_E022+1)
DECL|macro|SKERR_HWI_E023MSG
mdefine_line|#define SKERR_HWI_E023MSG&t;&quot;SkGeInitPort(): Transmit Queue Size too small&quot;
DECL|macro|SKERR_HWI_E024
mdefine_line|#define SKERR_HWI_E024&t;&t;(SKERR_HWI_E023+1)
DECL|macro|SKERR_HWI_E024MSG
mdefine_line|#define SKERR_HWI_E024MSG&t;&quot;FATAL: SkGeStopPort() does not terminate (Rx)&quot;
DECL|macro|SKERR_HWI_E025
mdefine_line|#define SKERR_HWI_E025&t;&t;(SKERR_HWI_E024+1)
DECL|macro|SKERR_HWI_E025MSG
mdefine_line|#define SKERR_HWI_E025MSG&t;&quot;&quot;
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
r_extern
r_int
id|SkGeInitAssignRamToQueues
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
r_int
id|ActivePort
comma
id|SK_BOOL
id|DualNet
)paren
suffix:semicolon
multiline_comment|/*&n; * public functions in skxmac2.c&n; */
r_extern
r_void
id|SkMacRxTxDisable
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
id|SkMacSoftRst
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
id|SkMacHardRst
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
id|SkGmInitMac
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
id|SkMacInitPhy
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
id|DoLoop
)paren
suffix:semicolon
r_extern
r_void
id|SkMacIrqDisable
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
id|SkMacFlushTxFifo
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
id|SkMacFlushRxFifo
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
id|SkMacIrq
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
id|SkMacAutoNegDone
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
id|SkMacAutoNegLipaPhy
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
id|SkMacSetRxTxEn
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
id|Para
)paren
suffix:semicolon
r_extern
r_int
id|SkMacRxTxEnable
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
id|SkMacPromiscMode
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
id|Enable
)paren
suffix:semicolon
r_extern
r_void
id|SkMacHashing
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
id|Enable
)paren
suffix:semicolon
r_extern
r_void
id|SkXmPhyRead
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
id|Addr
comma
id|SK_U16
id|SK_FAR
op_star
id|pVal
)paren
suffix:semicolon
r_extern
r_void
id|SkXmPhyWrite
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
id|Addr
comma
id|SK_U16
id|Val
)paren
suffix:semicolon
r_extern
r_void
id|SkGmPhyRead
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
id|Addr
comma
id|SK_U16
id|SK_FAR
op_star
id|pVal
)paren
suffix:semicolon
r_extern
r_void
id|SkGmPhyWrite
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
id|Addr
comma
id|SK_U16
id|Val
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
r_int
id|SkXmUpdateStats
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
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_int
id|SkGmUpdateStats
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
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_int
id|SkXmMacStatistic
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
r_int
id|Port
comma
id|SK_U16
id|StatAddr
comma
id|SK_U32
id|SK_FAR
op_star
id|pVal
)paren
suffix:semicolon
r_extern
r_int
id|SkGmMacStatistic
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
r_int
id|Port
comma
id|SK_U16
id|StatAddr
comma
id|SK_U32
id|SK_FAR
op_star
id|pVal
)paren
suffix:semicolon
r_extern
r_int
id|SkXmResetCounter
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
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_int
id|SkGmResetCounter
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
r_int
id|Port
)paren
suffix:semicolon
r_extern
r_int
id|SkXmOverflowStatus
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
r_int
id|Port
comma
id|SK_U16
id|IStatus
comma
id|SK_U64
id|SK_FAR
op_star
id|pStatus
)paren
suffix:semicolon
r_extern
r_int
id|SkGmOverflowStatus
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
r_int
id|Port
comma
id|SK_U16
id|MacStatus
comma
id|SK_U64
id|SK_FAR
op_star
id|pStatus
)paren
suffix:semicolon
r_extern
r_int
id|SkGmCableDiagStatus
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
id|StartTest
)paren
suffix:semicolon
macro_line|#ifdef SK_DIAG
r_extern
r_void
id|SkGePhyRead
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
id|Addr
comma
id|SK_U16
op_star
id|pVal
)paren
suffix:semicolon
r_extern
r_void
id|SkGePhyWrite
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
id|Addr
comma
id|SK_U16
id|Val
)paren
suffix:semicolon
r_extern
r_void
id|SkMacSetRxCmd
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
id|SkMacCrcGener
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
id|Enable
)paren
suffix:semicolon
r_extern
r_void
id|SkMacTimeStamp
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
id|Enable
)paren
suffix:semicolon
r_extern
r_void
id|SkXmSendCont
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
id|Enable
)paren
suffix:semicolon
macro_line|#endif /* SK_DIAG */
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
r_extern
r_int
id|SkGeInitAssignRamToQueues
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * public functions in skxmac2.c&n; */
r_extern
r_void
id|SkMacRxTxDisable
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacSoftRst
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacHardRst
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacInitPhy
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkMacRxTxEnable
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacPromiscMode
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacHashing
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacIrqDisable
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacFlushTxFifo
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacFlushRxFifo
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacIrq
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkMacAutoNegDone
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacAutoNegLipaPhy
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacSetRxTxEn
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
id|SkXmPhyRead
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmPhyWrite
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGmInitMac
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGmPhyRead
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGmPhyWrite
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
r_void
id|SkXmAutoNegLipaXmac
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkXmUpdateStats
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkGmUpdateStats
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkXmMacStatistic
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkGmMacStatistic
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkXmResetCounter
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkGmResetCounter
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkXmOverflowStatus
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkGmOverflowStatus
c_func
(paren
)paren
suffix:semicolon
r_extern
r_int
id|SkGmCableDiagStatus
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef SK_DIAG
r_extern
r_void
id|SkGePhyRead
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkGePhyWrite
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacSetRxCmd
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacCrcGener
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkMacTimeStamp
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|SkXmSendCont
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* SK_DIAG */
macro_line|#endif&t;/* SK_KR_PROTO */
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif&t;/* __cplusplus */
macro_line|#endif&t;/* __INC_SKGEINIT_H_ */
eof
