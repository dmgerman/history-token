multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgesirq.h&n; * Project:&t;Gigabit Ethernet Adapters, Common Modules&n; * Version:&t;$Revision: 1.30 $&n; * Date:&t;$Date: 2003/07/04 12:34:13 $&n; * Purpose:&t;SK specific Gigabit Ethernet special IRQ functions&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&t;$Log: skgesirq.h,v $&n; *&t;Revision 1.30  2003/07/04 12:34:13  rschmidt&n; *&t;Added SKERR_SIRQ_E025 for Downshift detected (Yukon-Copper)&n; *&t;&n; *&t;Revision 1.29  2003/05/28 15:14:49  rschmidt&n; *&t;Moved defines for return codes of SkGePortCheckUp() to header file.&n; *&t;Minor changes to avoid LINT warnings.&n; *&t;&n; *&t;Revision 1.28  2003/05/13 17:22:43  mkarl&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.27  2003/03/31 07:32:34  mkarl&n; *&t;Corrected Copyright.&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.26  2002/10/14 09:52:36  rschmidt&n; *&t;Added SKERR_SIRQ_E023 and SKERR_SIRQ_E024 for GPHY (Yukon)&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.25  2002/07/15 18:15:52  rwahl&n; *&t;Editorial changes.&n; *&t;&n; *&t;Revision 1.24  2002/07/15 15:39:21  rschmidt&n; *&t;Corrected define for SKERR_SIRQ_E022&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.23  2002/04/25 11:09:45  rschmidt&n; *&t;Removed declarations for SkXmInitPhy(), SkXmRxTxEnable()&n; *&t;Editorial changes&n; *&t;&n; *&t;Revision 1.22  2000/11/09 11:30:10  rassmann&n; *&t;WA: Waiting after releasing reset until BCom chip is accessible.&n; *&t;&n; *&t;Revision 1.21  2000/10/18 12:22:40  cgoos&n; *&t;Added workaround for half duplex hangup.&n; *&t;&n; *&t;Revision 1.20  1999/12/06 10:00:44  cgoos&n; *&t;Added SET event for role.&n; *&t;&n; *&t;Revision 1.19  1999/11/22 13:58:26  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.18  1999/05/19 07:32:59  cgoos&n; *&t;Changes for 1000Base-T.&n; *&t;&n; *&t;Revision 1.17  1999/03/12 13:29:31  malthoff&n; *&t;Move Autonegotiation Error Codes to skgeinit.h.&n; *&t;&n; *&t;Revision 1.16  1999/03/08 10:11:28  gklug&n; *&t;add: AutoNegDone return codes&n; *&t;&n; *&t;Revision 1.15  1998/11/18 13:20:53  gklug&n; *&t;add: different timeouts for active and non-active links&n; *&t;&n; *&t;Revision 1.14  1998/11/04 07:18:14  cgoos&n; *&t;Added prototype for SkXmRxTxEnable.&n; *&t;&n; *&t;Revision 1.13  1998/10/21 05:52:23  gklug&n; *&t;add: parameter DoLoop to InitPhy function&n; *&t;&n; *&t;Revision 1.12  1998/10/19 06:45:03  cgoos&n; *&t;Added prototype for SkXmInitPhy.&n; *&t;&n; *&t;Revision 1.11  1998/10/15 14:34:10  gklug&n; *&t;add: WA_TIME is 500 msec&n; *&t;&n; *&t;Revision 1.10  1998/10/14 14:49:41  malthoff&n; *&t;Remove err log defines E021 and E022. They are&n; *&t;defined in skgeinit.h now.&n; *&n; *&t;Revision 1.9  1998/10/14 14:00:39  gklug&n; *&t;add: error logs for init phys&n; *&t;&n; *&t;Revision 1.8  1998/10/14 05:44:05  gklug&n; *&t;add: E020&n; *&t;&n; *&t;Revision 1.7  1998/10/02 06:24:58  gklug&n; *&t;add: error messages&n; *&t;&n; *&t;Revision 1.6  1998/10/01 07:54:45  gklug&n; *&t;add: PNMI debug module&n; *&t;&n; *&t;Revision 1.5  1998/09/28 13:36:31  malthoff&n; *&t;Move the bit definitions for Autonegotiation&n; *&t;and Flow Control to skgeinit.h.&n; *&t;&n; *&t;Revision 1.4  1998/09/15 12:29:34  gklug&n; *&t;add: error logs&n; *&t;&n; *&t;Revision 1.3  1998/09/03 13:54:02  gklug&n; *&t;add: function prototypes&n; *&t;&n; *&t;Revision 1.2  1998/09/03 10:24:36  gklug&n; *&t;add: Events send by PNMI&n; *&t;add: parameter definition for Flow Control etc.&n; *&t;&n; *&t;Revision 1.1  1998/08/27 11:50:27  gklug&n; *&t;initial revision&n; *&t;&n; *&n; ******************************************************************************/
macro_line|#ifndef _INC_SKGESIRQ_H_
DECL|macro|_INC_SKGESIRQ_H_
mdefine_line|#define _INC_SKGESIRQ_H_
multiline_comment|/* Define return codes of SkGePortCheckUp and CheckShort */
DECL|macro|SK_HW_PS_NONE
mdefine_line|#define&t;SK_HW_PS_NONE&t;&t;0&t;/* No action needed */
DECL|macro|SK_HW_PS_RESTART
mdefine_line|#define&t;SK_HW_PS_RESTART&t;1&t;/* Restart needed */
DECL|macro|SK_HW_PS_LINK
mdefine_line|#define&t;SK_HW_PS_LINK&t;&t;2&t;/* Link Up actions needed */
multiline_comment|/*&n; * Define the Event the special IRQ/INI module can handle&n; */
DECL|macro|SK_HWEV_WATIM
mdefine_line|#define SK_HWEV_WATIM&t;&t;&t;1&t;/* Timeout for WA Errata #2 XMAC */
DECL|macro|SK_HWEV_PORT_START
mdefine_line|#define SK_HWEV_PORT_START&t;&t;2&t;/* Port Start Event by RLMT */
DECL|macro|SK_HWEV_PORT_STOP
mdefine_line|#define SK_HWEV_PORT_STOP&t;&t;3&t;/* Port Stop Event by RLMT */
DECL|macro|SK_HWEV_CLEAR_STAT
mdefine_line|#define SK_HWEV_CLEAR_STAT&t;&t;4&t;/* Clear Statistics by PNMI */
DECL|macro|SK_HWEV_UPDATE_STAT
mdefine_line|#define SK_HWEV_UPDATE_STAT&t;&t;5&t;/* Update Statistics by PNMI */
DECL|macro|SK_HWEV_SET_LMODE
mdefine_line|#define SK_HWEV_SET_LMODE&t;&t;6&t;/* Set Link Mode by PNMI */
DECL|macro|SK_HWEV_SET_FLOWMODE
mdefine_line|#define SK_HWEV_SET_FLOWMODE&t;7&t;/* Set Flow Control Mode by PNMI */
DECL|macro|SK_HWEV_SET_ROLE
mdefine_line|#define SK_HWEV_SET_ROLE&t;&t;8&t;/* Set Master/Slave (Role) by PNMI */
DECL|macro|SK_HWEV_SET_SPEED
mdefine_line|#define SK_HWEV_SET_SPEED&t;&t;9&t;/* Set Link Speed by PNMI */
DECL|macro|SK_HWEV_HALFDUP_CHK
mdefine_line|#define SK_HWEV_HALFDUP_CHK&t;&t;10&t;/* Half Duplex Hangup Workaround */
DECL|macro|SK_WA_ACT_TIME
mdefine_line|#define SK_WA_ACT_TIME&t;&t;(5000000UL)&t;/* 5 sec */
DECL|macro|SK_WA_INA_TIME
mdefine_line|#define SK_WA_INA_TIME&t;&t;(100000UL)&t;/* 100 msec */
DECL|macro|SK_HALFDUP_CHK_TIME
mdefine_line|#define SK_HALFDUP_CHK_TIME&t;(10000UL)&t;/* 10 msec */
multiline_comment|/*&n; * Define the error numbers and messages&n; */
DECL|macro|SKERR_SIRQ_E001
mdefine_line|#define SKERR_SIRQ_E001&t;&t;(SK_ERRBASE_SIRQ+0)
DECL|macro|SKERR_SIRQ_E001MSG
mdefine_line|#define SKERR_SIRQ_E001MSG&t;&quot;Unknown event&quot;
DECL|macro|SKERR_SIRQ_E002
mdefine_line|#define SKERR_SIRQ_E002&t;&t;(SKERR_SIRQ_E001+1)
DECL|macro|SKERR_SIRQ_E002MSG
mdefine_line|#define SKERR_SIRQ_E002MSG&t;&quot;Packet timeout RX1&quot;
DECL|macro|SKERR_SIRQ_E003
mdefine_line|#define SKERR_SIRQ_E003&t;&t;(SKERR_SIRQ_E002+1)
DECL|macro|SKERR_SIRQ_E003MSG
mdefine_line|#define SKERR_SIRQ_E003MSG&t;&quot;Packet timeout RX2&quot;
DECL|macro|SKERR_SIRQ_E004
mdefine_line|#define SKERR_SIRQ_E004&t;&t;(SKERR_SIRQ_E003+1)
DECL|macro|SKERR_SIRQ_E004MSG
mdefine_line|#define SKERR_SIRQ_E004MSG&t;&quot;MAC 1 not correctly initialized&quot;
DECL|macro|SKERR_SIRQ_E005
mdefine_line|#define SKERR_SIRQ_E005&t;&t;(SKERR_SIRQ_E004+1)
DECL|macro|SKERR_SIRQ_E005MSG
mdefine_line|#define SKERR_SIRQ_E005MSG&t;&quot;MAC 2 not correctly initialized&quot;
DECL|macro|SKERR_SIRQ_E006
mdefine_line|#define SKERR_SIRQ_E006&t;&t;(SKERR_SIRQ_E005+1)
DECL|macro|SKERR_SIRQ_E006MSG
mdefine_line|#define SKERR_SIRQ_E006MSG&t;&quot;CHECK failure R1&quot;
DECL|macro|SKERR_SIRQ_E007
mdefine_line|#define SKERR_SIRQ_E007&t;&t;(SKERR_SIRQ_E006+1)
DECL|macro|SKERR_SIRQ_E007MSG
mdefine_line|#define SKERR_SIRQ_E007MSG&t;&quot;CHECK failure R2&quot;
DECL|macro|SKERR_SIRQ_E008
mdefine_line|#define SKERR_SIRQ_E008&t;&t;(SKERR_SIRQ_E007+1)
DECL|macro|SKERR_SIRQ_E008MSG
mdefine_line|#define SKERR_SIRQ_E008MSG&t;&quot;CHECK failure XS1&quot;
DECL|macro|SKERR_SIRQ_E009
mdefine_line|#define SKERR_SIRQ_E009&t;&t;(SKERR_SIRQ_E008+1)
DECL|macro|SKERR_SIRQ_E009MSG
mdefine_line|#define SKERR_SIRQ_E009MSG&t;&quot;CHECK failure XA1&quot;
DECL|macro|SKERR_SIRQ_E010
mdefine_line|#define SKERR_SIRQ_E010&t;&t;(SKERR_SIRQ_E009+1)
DECL|macro|SKERR_SIRQ_E010MSG
mdefine_line|#define SKERR_SIRQ_E010MSG&t;&quot;CHECK failure XS2&quot;
DECL|macro|SKERR_SIRQ_E011
mdefine_line|#define SKERR_SIRQ_E011&t;&t;(SKERR_SIRQ_E010+1)
DECL|macro|SKERR_SIRQ_E011MSG
mdefine_line|#define SKERR_SIRQ_E011MSG&t;&quot;CHECK failure XA2&quot;
DECL|macro|SKERR_SIRQ_E012
mdefine_line|#define SKERR_SIRQ_E012&t;&t;(SKERR_SIRQ_E011+1)
DECL|macro|SKERR_SIRQ_E012MSG
mdefine_line|#define SKERR_SIRQ_E012MSG&t;&quot;unexpected IRQ Master error&quot;
DECL|macro|SKERR_SIRQ_E013
mdefine_line|#define SKERR_SIRQ_E013&t;&t;(SKERR_SIRQ_E012+1)
DECL|macro|SKERR_SIRQ_E013MSG
mdefine_line|#define SKERR_SIRQ_E013MSG&t;&quot;unexpected IRQ Status error&quot;
DECL|macro|SKERR_SIRQ_E014
mdefine_line|#define SKERR_SIRQ_E014&t;&t;(SKERR_SIRQ_E013+1)
DECL|macro|SKERR_SIRQ_E014MSG
mdefine_line|#define SKERR_SIRQ_E014MSG&t;&quot;Parity error on RAM (read)&quot;
DECL|macro|SKERR_SIRQ_E015
mdefine_line|#define SKERR_SIRQ_E015&t;&t;(SKERR_SIRQ_E014+1)
DECL|macro|SKERR_SIRQ_E015MSG
mdefine_line|#define SKERR_SIRQ_E015MSG&t;&quot;Parity error on RAM (write)&quot;
DECL|macro|SKERR_SIRQ_E016
mdefine_line|#define SKERR_SIRQ_E016&t;&t;(SKERR_SIRQ_E015+1)
DECL|macro|SKERR_SIRQ_E016MSG
mdefine_line|#define SKERR_SIRQ_E016MSG&t;&quot;Parity error MAC 1&quot;
DECL|macro|SKERR_SIRQ_E017
mdefine_line|#define SKERR_SIRQ_E017&t;&t;(SKERR_SIRQ_E016+1)
DECL|macro|SKERR_SIRQ_E017MSG
mdefine_line|#define SKERR_SIRQ_E017MSG&t;&quot;Parity error MAC 2&quot;
DECL|macro|SKERR_SIRQ_E018
mdefine_line|#define SKERR_SIRQ_E018&t;&t;(SKERR_SIRQ_E017+1)
DECL|macro|SKERR_SIRQ_E018MSG
mdefine_line|#define SKERR_SIRQ_E018MSG&t;&quot;Parity error RX 1&quot;
DECL|macro|SKERR_SIRQ_E019
mdefine_line|#define SKERR_SIRQ_E019&t;&t;(SKERR_SIRQ_E018+1)
DECL|macro|SKERR_SIRQ_E019MSG
mdefine_line|#define SKERR_SIRQ_E019MSG&t;&quot;Parity error RX 2&quot;
DECL|macro|SKERR_SIRQ_E020
mdefine_line|#define SKERR_SIRQ_E020&t;&t;(SKERR_SIRQ_E019+1)
DECL|macro|SKERR_SIRQ_E020MSG
mdefine_line|#define SKERR_SIRQ_E020MSG&t;&quot;MAC transmit FIFO underrun&quot;
DECL|macro|SKERR_SIRQ_E021
mdefine_line|#define SKERR_SIRQ_E021&t;&t;(SKERR_SIRQ_E020+1)
DECL|macro|SKERR_SIRQ_E021MSG
mdefine_line|#define SKERR_SIRQ_E021MSG&t;&quot;Spurious TWSI interrupt&quot;
DECL|macro|SKERR_SIRQ_E022
mdefine_line|#define SKERR_SIRQ_E022&t;&t;(SKERR_SIRQ_E021+1)
DECL|macro|SKERR_SIRQ_E022MSG
mdefine_line|#define SKERR_SIRQ_E022MSG&t;&quot;Cable pair swap error&quot;
DECL|macro|SKERR_SIRQ_E023
mdefine_line|#define SKERR_SIRQ_E023&t;&t;(SKERR_SIRQ_E022+1)
DECL|macro|SKERR_SIRQ_E023MSG
mdefine_line|#define SKERR_SIRQ_E023MSG&t;&quot;Auto-negotiation error&quot;
DECL|macro|SKERR_SIRQ_E024
mdefine_line|#define SKERR_SIRQ_E024&t;&t;(SKERR_SIRQ_E023+1)
DECL|macro|SKERR_SIRQ_E024MSG
mdefine_line|#define SKERR_SIRQ_E024MSG&t;&quot;FIFO overflow error&quot;
DECL|macro|SKERR_SIRQ_E025
mdefine_line|#define SKERR_SIRQ_E025&t;&t;(SKERR_SIRQ_E024+1)
DECL|macro|SKERR_SIRQ_E025MSG
mdefine_line|#define SKERR_SIRQ_E025MSG&t;&quot;2 Pair Downshift detected&quot;
r_extern
r_void
id|SkGeSirqIsr
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
id|SK_U32
id|Istatus
)paren
suffix:semicolon
r_extern
r_int
id|SkGeSirqEvent
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|IoC
comma
id|SK_U32
id|Event
comma
id|SK_EVPARA
id|Para
)paren
suffix:semicolon
r_extern
r_void
id|SkHWLinkUp
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
id|SkHWLinkDown
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
macro_line|#endif&t;/* _INC_SKGESIRQ_H_ */
eof
