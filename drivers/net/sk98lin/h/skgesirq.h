multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgesirq.h&n; * Project:&t;Gigabit Ethernet Adapters, Common Modules&n; * Purpose:&t;SK specific Gigabit Ethernet special IRQ functions&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
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
