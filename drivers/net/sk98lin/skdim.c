multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skdim.c&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.4 $&n; * Date:&t;$Date: 2003/07/07 09:45:47 $&n; * Purpose:&t;All functions to maintain interrupt moderation&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&t;&n; *&t;$Log: skdim.c,v $&n; *&t;Revision 1.4  2003/07/07 09:45:47  rroesler&n; *&t;Fix: Compiler warnings corrected&n; *&t;&n; *&t;Revision 1.3  2003/06/10 09:16:40  rroesler&n; *&t;Adapt GetCurrentSystemLoad() to NOT access the kernels&n; *&t;kstat-structure in kernel 2.5/2.6. This must be done&n; *&t;due to a not exported symbol. Instead of evaluating the&n; *&t;SystemLoad directly, the nbr of interrupts is used as&n; *&t;a rough basis for the load.&n; *&t;&n; *&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * Description:&n; *&n; * This module is intended to manage the dynamic interrupt moderation on both   &n; * GEnesis and Yukon adapters.&n; *&n; * Include File Hierarchy:&n; *&n; *&t;&quot;skdrv1st.h&quot;&n; *&t;&quot;skdrv2nd.h&quot;&n; *&n; ******************************************************************************/
macro_line|#ifndef&t;lint
DECL|variable|SysKonnectFileId
r_static
r_const
r_char
id|SysKonnectFileId
(braket
)braket
op_assign
l_string|&quot;@(#) $Id: skdim.c,v 1.4 2003/07/07 09:45:47 rroesler Exp $ (C) SysKonnect.&quot;
suffix:semicolon
macro_line|#endif
DECL|macro|__SKADDR_C
mdefine_line|#define __SKADDR_C
macro_line|#ifdef __cplusplus
macro_line|#error C++ is not yet supported.
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/*******************************************************************************&n;**&n;** Includes&n;**&n;*******************************************************************************/
macro_line|#ifndef __INC_SKDRV1ST_H
macro_line|#include &quot;h/skdrv1st.h&quot;
macro_line|#endif
macro_line|#ifndef __INC_SKDRV2ND_H
macro_line|#include &quot;h/skdrv2nd.h&quot;
macro_line|#endif
macro_line|#include&t;&lt;linux/kernel_stat.h&gt;
multiline_comment|/*******************************************************************************&n;**&n;** Defines&n;**&n;*******************************************************************************/
multiline_comment|/*******************************************************************************&n;**&n;** Typedefs&n;**&n;*******************************************************************************/
multiline_comment|/*******************************************************************************&n;**&n;** Local function prototypes &n;**&n;*******************************************************************************/
r_static
r_int
r_int
id|GetCurrentSystemLoad
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
suffix:semicolon
r_static
id|SK_U64
id|GetIsrCalls
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
suffix:semicolon
r_static
id|SK_BOOL
id|IsIntModEnabled
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
suffix:semicolon
r_static
r_void
id|SetCurrIntCtr
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
suffix:semicolon
r_static
r_void
id|EnableIntMod
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
suffix:semicolon
r_static
r_void
id|DisableIntMod
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
suffix:semicolon
r_static
r_void
id|ResizeDimTimerDuration
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
suffix:semicolon
r_static
r_void
id|DisplaySelectedModerationType
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
suffix:semicolon
r_static
r_void
id|DisplaySelectedModerationMask
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
suffix:semicolon
r_static
r_void
id|DisplayDescrRatio
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
suffix:semicolon
multiline_comment|/*******************************************************************************&n;**&n;** Global variables&n;**&n;*******************************************************************************/
multiline_comment|/*******************************************************************************&n;**&n;** Local variables&n;**&n;*******************************************************************************/
multiline_comment|/*******************************************************************************&n;**&n;** Global functions &n;**&n;*******************************************************************************/
multiline_comment|/*******************************************************************************&n;** Function     : SkDimModerate&n;** Description  : Called in every ISR to check if moderation is to be applied&n;**                or not for the current number of interrupts&n;** Programmer   : Ralph Roesler&n;** Last Modified: 22-mar-03&n;** Returns      : void (!)&n;** Notes        : -&n;*******************************************************************************/
r_void
DECL|function|SkDimModerate
id|SkDimModerate
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
r_int
r_int
id|CurrSysLoad
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* expressed in percent */
r_int
r_int
id|LoadIncrease
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* expressed in percent */
id|SK_U64
id|ThresholdInts
op_assign
l_int|0
suffix:semicolon
id|SK_U64
id|IsrCallsPerSec
op_assign
l_int|0
suffix:semicolon
DECL|macro|M_DIMINFO
mdefine_line|#define M_DIMINFO pAC-&gt;DynIrqModInfo
r_if
c_cond
(paren
op_logical_neg
id|IsIntModEnabled
c_func
(paren
id|pAC
)paren
)paren
(brace
r_if
c_cond
(paren
id|M_DIMINFO.IntModTypeSelect
op_eq
id|C_INT_MOD_DYNAMIC
)paren
(brace
id|CurrSysLoad
op_assign
id|GetCurrentSystemLoad
c_func
(paren
id|pAC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CurrSysLoad
OG
l_int|75
)paren
(brace
multiline_comment|/* &n;                    ** More than 75% total system load! Enable the moderation &n;                    ** to shield the system against too many interrupts.&n;                    */
id|EnableIntMod
c_func
(paren
id|pAC
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CurrSysLoad
OG
id|M_DIMINFO.PrevSysLoad
)paren
(brace
id|LoadIncrease
op_assign
(paren
id|CurrSysLoad
op_minus
id|M_DIMINFO.PrevSysLoad
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LoadIncrease
OG
(paren
(paren
id|M_DIMINFO.PrevSysLoad
op_star
id|C_INT_MOD_ENABLE_PERCENTAGE
)paren
op_div
l_int|100
)paren
)paren
(brace
r_if
c_cond
(paren
id|CurrSysLoad
OG
l_int|10
)paren
(brace
multiline_comment|/* &n;                        ** More than 50% increase with respect to the &n;                        ** previous load of the system. Most likely this &n;                        ** is due to our ISR-proc...&n;                        */
id|EnableIntMod
c_func
(paren
id|pAC
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/*&n;                ** Neither too much system load at all nor too much increase&n;                ** with respect to the previous system load. Hence, we can leave&n;                ** the ISR-handling like it is without enabling moderation.&n;                */
)brace
id|M_DIMINFO.PrevSysLoad
op_assign
id|CurrSysLoad
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|M_DIMINFO.IntModTypeSelect
op_eq
id|C_INT_MOD_DYNAMIC
)paren
(brace
id|ThresholdInts
op_assign
(paren
(paren
id|M_DIMINFO.MaxModIntsPerSec
op_star
id|C_INT_MOD_DISABLE_PERCENTAGE
)paren
op_div
l_int|100
)paren
suffix:semicolon
id|IsrCallsPerSec
op_assign
id|GetIsrCalls
c_func
(paren
id|pAC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IsrCallsPerSec
op_le
id|ThresholdInts
)paren
(brace
multiline_comment|/* &n;                ** The number of interrupts within the last second is &n;                ** lower than the disable_percentage of the desried &n;                ** maxrate. Therefore we can disable the moderation.&n;                */
id|DisableIntMod
c_func
(paren
id|pAC
)paren
suffix:semicolon
id|M_DIMINFO.MaxModIntsPerSec
op_assign
(paren
id|M_DIMINFO.MaxModIntsPerSecUpperLimit
op_plus
id|M_DIMINFO.MaxModIntsPerSecLowerLimit
)paren
op_div
l_int|2
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;                ** The number of interrupts per sec is the same as expected.&n;                ** Evalulate the descriptor-ratio. If it has changed, a resize &n;                ** in the moderation timer might be usefull&n;                */
r_if
c_cond
(paren
id|M_DIMINFO.AutoSizing
)paren
(brace
id|ResizeDimTimerDuration
c_func
(paren
id|pAC
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n;    ** Some information to the log...&n;    */
r_if
c_cond
(paren
id|M_DIMINFO.DisplayStats
)paren
(brace
id|DisplaySelectedModerationType
c_func
(paren
id|pAC
)paren
suffix:semicolon
id|DisplaySelectedModerationMask
c_func
(paren
id|pAC
)paren
suffix:semicolon
id|DisplayDescrRatio
c_func
(paren
id|pAC
)paren
suffix:semicolon
)brace
id|M_DIMINFO.NbrProcessedDescr
op_assign
l_int|0
suffix:semicolon
id|SetCurrIntCtr
c_func
(paren
id|pAC
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n;** Function     : SkDimStartModerationTimer&n;** Description  : Starts the audit-timer for the dynamic interrupt moderation&n;** Programmer   : Ralph Roesler&n;** Last Modified: 22-mar-03&n;** Returns      : void (!)&n;** Notes        : -&n;*******************************************************************************/
r_void
DECL|function|SkDimStartModerationTimer
id|SkDimStartModerationTimer
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
id|SK_EVPARA
id|EventParam
suffix:semicolon
multiline_comment|/* Event struct for timer event */
id|SK_MEMSET
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|EventParam
comma
l_int|0
comma
r_sizeof
(paren
id|EventParam
)paren
)paren
suffix:semicolon
id|EventParam.Para32
(braket
l_int|0
)braket
op_assign
id|SK_DRV_MODERATION_TIMER
suffix:semicolon
id|SkTimerStart
c_func
(paren
id|pAC
comma
id|pAC-&gt;IoBase
comma
op_amp
id|pAC-&gt;DynIrqModInfo.ModTimer
comma
id|SK_DRV_MODERATION_TIMER_LENGTH
comma
id|SKGE_DRV
comma
id|SK_DRV_TIMER
comma
id|EventParam
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n;** Function     : SkDimEnableModerationIfNeeded&n;** Description  : Either enables or disables moderation&n;** Programmer   : Ralph Roesler&n;** Last Modified: 22-mar-03&n;** Returns      : void (!)&n;** Notes        : This function is called when a particular adapter is opened&n;**                There is no Disable function, because when all interrupts &n;**                might be disable, the moderation timer has no meaning at all&n;******************************************************************************/
r_void
DECL|function|SkDimEnableModerationIfNeeded
id|SkDimEnableModerationIfNeeded
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
r_if
c_cond
(paren
id|M_DIMINFO.IntModTypeSelect
op_eq
id|C_INT_MOD_STATIC
)paren
(brace
id|EnableIntMod
c_func
(paren
id|pAC
)paren
suffix:semicolon
multiline_comment|/* notification print in this function */
)brace
r_else
r_if
c_cond
(paren
id|M_DIMINFO.IntModTypeSelect
op_eq
id|C_INT_MOD_DYNAMIC
)paren
(brace
id|SkDimStartModerationTimer
c_func
(paren
id|pAC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|M_DIMINFO.DisplayStats
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Dynamic moderation has been enabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|M_DIMINFO.DisplayStats
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No moderation has been enabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*******************************************************************************&n;** Function     : SkDimDisplayModerationSettings&n;** Description  : Displays the current settings regaring interrupt moderation&n;** Programmer   : Ralph Roesler&n;** Last Modified: 22-mar-03&n;** Returns      : void (!)&n;** Notes        : -&n;*******************************************************************************/
r_void
DECL|function|SkDimDisplayModerationSettings
id|SkDimDisplayModerationSettings
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
id|DisplaySelectedModerationType
c_func
(paren
id|pAC
)paren
suffix:semicolon
id|DisplaySelectedModerationMask
c_func
(paren
id|pAC
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n;**&n;** Local functions &n;**&n;*******************************************************************************/
multiline_comment|/*******************************************************************************&n;** Function     : GetCurrentSystemLoad&n;** Description  : Retrieves the current system load of the system. This load&n;**                is evaluated for all processors within the system.&n;** Programmer   : Ralph Roesler&n;** Last Modified: 22-mar-03&n;** Returns      : unsigned int: load expressed in percentage&n;** Notes        : The possible range being returned is from 0 up to 100.&n;**                Whereas 0 means &squot;no load at all&squot; and 100 &squot;system fully loaded&squot;&n;**                It is impossible to determine what actually causes the system&n;**                to be in 100%, but maybe that is due to too much interrupts.&n;*******************************************************************************/
r_static
r_int
r_int
DECL|function|GetCurrentSystemLoad
id|GetCurrentSystemLoad
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
r_int
r_int
id|jif
op_assign
id|jiffies
suffix:semicolon
r_int
r_int
id|UserTime
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|SystemTime
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|NiceTime
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|IdleTime
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|TotalTime
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|UsedTime
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|SystemLoad
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* unsigned int  NbrCpu      = 0; */
multiline_comment|/*&n;&t;** The following lines have been commented out, because&n;&t;** from kernel 2.5.44 onwards, the kernel-owned structure&n;&t;**&n;&t;**      struct kernel_stat kstat&n;&t;**&n;&t;** is not marked as an exported symbol in the file&n;&t;**&n;&t;**      kernel/ksyms.c &n;&t;**&n;&t;** As a consequence, using this driver as KLM is not possible&n;&t;** and any access of the structure kernel_stat via the &n;&t;** dedicated macros kstat_cpu(i).cpustat.xxx is to be avoided.&n;&t;**&n;&t;** The kstat-information might be added again in future &n;&t;** versions of the 2.5.xx kernel, but for the time being, &n;&t;** number of interrupts will serve as indication how much &n;&t;** load we currently have... &n;&t;**&n;&t;** for (NbrCpu = 0; NbrCpu &lt; num_online_cpus(); NbrCpu++) {&n;&t;**&t;UserTime   = UserTime   + kstat_cpu(NbrCpu).cpustat.user;&n;&t;**&t;NiceTime   = NiceTime   + kstat_cpu(NbrCpu).cpustat.nice;&n;&t;**&t;SystemTime = SystemTime + kstat_cpu(NbrCpu).cpustat.system;&n;&t;** }&n;&t;*/
id|SK_U64
id|ThresholdInts
op_assign
l_int|0
suffix:semicolon
id|SK_U64
id|IsrCallsPerSec
op_assign
l_int|0
suffix:semicolon
id|ThresholdInts
op_assign
(paren
(paren
id|M_DIMINFO.MaxModIntsPerSec
op_star
id|C_INT_MOD_ENABLE_PERCENTAGE
)paren
op_plus
l_int|100
)paren
suffix:semicolon
id|IsrCallsPerSec
op_assign
id|GetIsrCalls
c_func
(paren
id|pAC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IsrCallsPerSec
op_ge
id|ThresholdInts
)paren
(brace
multiline_comment|/*&n;&t;    ** We do not know how much the real CPU-load is!&n;&t;    ** Return 80% as a default in order to activate DIM&n;&t;    */
id|SystemLoad
op_assign
l_int|80
suffix:semicolon
r_return
(paren
id|SystemLoad
)paren
suffix:semicolon
)brace
id|UsedTime
op_assign
id|UserTime
op_plus
id|NiceTime
op_plus
id|SystemTime
suffix:semicolon
id|IdleTime
op_assign
id|jif
op_star
id|num_online_cpus
c_func
(paren
)paren
op_minus
id|UsedTime
suffix:semicolon
id|TotalTime
op_assign
id|UsedTime
op_plus
id|IdleTime
suffix:semicolon
id|SystemLoad
op_assign
(paren
l_int|100
op_star
(paren
id|UsedTime
op_minus
id|M_DIMINFO.PrevUsedTime
)paren
)paren
op_div
(paren
id|TotalTime
op_minus
id|M_DIMINFO.PrevTotalTime
)paren
suffix:semicolon
r_if
c_cond
(paren
id|M_DIMINFO.DisplayStats
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Current system load is: %u&bslash;n&quot;
comma
id|SystemLoad
)paren
suffix:semicolon
)brace
id|M_DIMINFO.PrevTotalTime
op_assign
id|TotalTime
suffix:semicolon
id|M_DIMINFO.PrevUsedTime
op_assign
id|UsedTime
suffix:semicolon
r_return
(paren
id|SystemLoad
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n;** Function     : GetIsrCalls&n;** Description  : Depending on the selected moderation mask, this function will&n;**                return the number of interrupts handled in the previous time-&n;**                frame. This evaluated number is based on the current number &n;**                of interrupts stored in PNMI-context and the previous stored &n;**                interrupts.&n;** Programmer   : Ralph Roesler&n;** Last Modified: 23-mar-03&n;** Returns      : int:   the number of interrupts being executed in the last&n;**                       timeframe&n;** Notes        : It makes only sense to call this function, when dynamic &n;**                interrupt moderation is applied&n;*******************************************************************************/
r_static
id|SK_U64
DECL|function|GetIsrCalls
id|GetIsrCalls
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
id|SK_U64
id|RxPort0IntDiff
op_assign
l_int|0
suffix:semicolon
id|SK_U64
id|RxPort1IntDiff
op_assign
l_int|0
suffix:semicolon
id|SK_U64
id|TxPort0IntDiff
op_assign
l_int|0
suffix:semicolon
id|SK_U64
id|TxPort1IntDiff
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;DynIrqModInfo.MaskIrqModeration
op_eq
id|IRQ_MASK_TX_ONLY
)paren
(brace
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIMacsFound
op_eq
l_int|2
)paren
(brace
id|TxPort1IntDiff
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|1
)braket
dot
id|TxIntrCts
op_minus
id|pAC-&gt;DynIrqModInfo.PrevPort1TxIntrCts
suffix:semicolon
)brace
id|TxPort0IntDiff
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|0
)braket
dot
id|TxIntrCts
op_minus
id|pAC-&gt;DynIrqModInfo.PrevPort0TxIntrCts
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pAC-&gt;DynIrqModInfo.MaskIrqModeration
op_eq
id|IRQ_MASK_RX_ONLY
)paren
(brace
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIMacsFound
op_eq
l_int|2
)paren
(brace
id|RxPort1IntDiff
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|1
)braket
dot
id|RxIntrCts
op_minus
id|pAC-&gt;DynIrqModInfo.PrevPort1RxIntrCts
suffix:semicolon
)brace
id|RxPort0IntDiff
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|0
)braket
dot
id|RxIntrCts
op_minus
id|pAC-&gt;DynIrqModInfo.PrevPort0RxIntrCts
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIMacsFound
op_eq
l_int|2
)paren
(brace
id|RxPort1IntDiff
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|1
)braket
dot
id|RxIntrCts
op_minus
id|pAC-&gt;DynIrqModInfo.PrevPort1RxIntrCts
suffix:semicolon
id|TxPort1IntDiff
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|1
)braket
dot
id|TxIntrCts
op_minus
id|pAC-&gt;DynIrqModInfo.PrevPort1TxIntrCts
suffix:semicolon
)brace
id|RxPort0IntDiff
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|0
)braket
dot
id|RxIntrCts
op_minus
id|pAC-&gt;DynIrqModInfo.PrevPort0RxIntrCts
suffix:semicolon
id|TxPort0IntDiff
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|0
)braket
dot
id|TxIntrCts
op_minus
id|pAC-&gt;DynIrqModInfo.PrevPort0TxIntrCts
suffix:semicolon
)brace
r_return
(paren
id|RxPort0IntDiff
op_plus
id|RxPort1IntDiff
op_plus
id|TxPort0IntDiff
op_plus
id|TxPort1IntDiff
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n;** Function     : GetRxCalls&n;** Description  : This function will return the number of times a receive inter-&n;**                rupt was processed. This is needed to evaluate any resizing &n;**                factor.&n;** Programmer   : Ralph Roesler&n;** Last Modified: 23-mar-03&n;** Returns      : SK_U64: the number of RX-ints being processed&n;** Notes        : It makes only sense to call this function, when dynamic &n;**                interrupt moderation is applied&n;*******************************************************************************/
r_static
id|SK_U64
DECL|function|GetRxCalls
id|GetRxCalls
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
id|SK_U64
id|RxPort0IntDiff
op_assign
l_int|0
suffix:semicolon
id|SK_U64
id|RxPort1IntDiff
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIMacsFound
op_eq
l_int|2
)paren
(brace
id|RxPort1IntDiff
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|1
)braket
dot
id|RxIntrCts
op_minus
id|pAC-&gt;DynIrqModInfo.PrevPort1RxIntrCts
suffix:semicolon
)brace
id|RxPort0IntDiff
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|0
)braket
dot
id|RxIntrCts
op_minus
id|pAC-&gt;DynIrqModInfo.PrevPort0RxIntrCts
suffix:semicolon
r_return
(paren
id|RxPort0IntDiff
op_plus
id|RxPort1IntDiff
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n;** Function     : SetCurrIntCtr&n;** Description  : Will store the current number orf occured interrupts in the &n;**                adapter context. This is needed to evaluated the number of &n;**                interrupts within a current timeframe.&n;** Programmer   : Ralph Roesler&n;** Last Modified: 23-mar-03&n;** Returns      : void (!)&n;** Notes        : -&n;*******************************************************************************/
r_static
r_void
DECL|function|SetCurrIntCtr
id|SetCurrIntCtr
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIMacsFound
op_eq
l_int|2
)paren
(brace
id|pAC-&gt;DynIrqModInfo.PrevPort1RxIntrCts
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|1
)braket
dot
id|RxIntrCts
suffix:semicolon
id|pAC-&gt;DynIrqModInfo.PrevPort1TxIntrCts
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|1
)braket
dot
id|TxIntrCts
suffix:semicolon
)brace
id|pAC-&gt;DynIrqModInfo.PrevPort0RxIntrCts
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|0
)braket
dot
id|RxIntrCts
suffix:semicolon
id|pAC-&gt;DynIrqModInfo.PrevPort0TxIntrCts
op_assign
id|pAC-&gt;Pnmi.Port
(braket
l_int|0
)braket
dot
id|TxIntrCts
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n;** Function     : IsIntModEnabled()&n;** Description  : Retrieves the current value of the interrupts moderation&n;**                command register. Its content determines whether any &n;**                moderation is running or not.&n;** Programmer   : Ralph Roesler&n;** Last Modified: 23-mar-03&n;** Returns      : SK_TRUE  : if mod timer running&n;**                SK_FALSE : if no moderation is being performed&n;** Notes        : -&n;*******************************************************************************/
r_static
id|SK_BOOL
DECL|function|IsIntModEnabled
id|IsIntModEnabled
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
r_int
r_int
id|CtrCmd
suffix:semicolon
id|SK_IN32
c_func
(paren
id|pAC-&gt;IoBase
comma
id|B2_IRQM_CTRL
comma
op_amp
id|CtrCmd
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|CtrCmd
op_amp
id|TIM_START
)paren
op_eq
id|TIM_START
)paren
(brace
r_return
id|SK_TRUE
suffix:semicolon
)brace
r_else
(brace
r_return
id|SK_FALSE
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n;** Function     : EnableIntMod()&n;** Description  : Enables the interrupt moderation using the values stored in&n;**                in the pAC-&gt;DynIntMod data structure&n;** Programmer   : Ralph Roesler&n;** Last Modified: 22-mar-03&n;** Returns      : -&n;** Notes        : -&n;*******************************************************************************/
r_static
r_void
DECL|function|EnableIntMod
id|EnableIntMod
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
r_int
r_int
id|ModBase
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIChipId
op_eq
id|CHIP_ID_GENESIS
)paren
(brace
id|ModBase
op_assign
id|C_CLK_FREQ_GENESIS
op_div
id|pAC-&gt;DynIrqModInfo.MaxModIntsPerSec
suffix:semicolon
)brace
r_else
(brace
id|ModBase
op_assign
id|C_CLK_FREQ_YUKON
op_div
id|pAC-&gt;DynIrqModInfo.MaxModIntsPerSec
suffix:semicolon
)brace
id|SK_OUT32
c_func
(paren
id|pAC-&gt;IoBase
comma
id|B2_IRQM_INI
comma
id|ModBase
)paren
suffix:semicolon
id|SK_OUT32
c_func
(paren
id|pAC-&gt;IoBase
comma
id|B2_IRQM_MSK
comma
id|pAC-&gt;DynIrqModInfo.MaskIrqModeration
)paren
suffix:semicolon
id|SK_OUT32
c_func
(paren
id|pAC-&gt;IoBase
comma
id|B2_IRQM_CTRL
comma
id|TIM_START
)paren
suffix:semicolon
r_if
c_cond
(paren
id|M_DIMINFO.DisplayStats
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Enabled interrupt moderation (%i ints/sec)&bslash;n&quot;
comma
id|M_DIMINFO.MaxModIntsPerSec
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n;** Function     : DisableIntMod()&n;** Description  : Disbles the interrupt moderation independent of what inter-&n;**                rupts are running or not&n;** Programmer   : Ralph Roesler&n;** Last Modified: 23-mar-03&n;** Returns      : -&n;** Notes        : -&n;*******************************************************************************/
r_static
r_void
DECL|function|DisableIntMod
id|DisableIntMod
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
id|SK_OUT32
c_func
(paren
id|pAC-&gt;IoBase
comma
id|B2_IRQM_CTRL
comma
id|TIM_STOP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|M_DIMINFO.DisplayStats
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Disabled interrupt moderation&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n;** Function     : ResizeDimTimerDuration();&n;** Description  : Checks the current used descriptor ratio and resizes the &n;**                duration timer (longer/smaller) if possible. &n;** Programmer   : Ralph Roesler&n;** Last Modified: 23-mar-03&n;** Returns      : -&n;** Notes        : There are both maximum and minimum timer duration value. &n;**                This function assumes that interrupt moderation is already&n;**                enabled!&n;*******************************************************************************/
r_static
r_void
DECL|function|ResizeDimTimerDuration
id|ResizeDimTimerDuration
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
id|SK_BOOL
id|IncreaseTimerDuration
suffix:semicolon
r_int
id|TotalMaxNbrDescr
suffix:semicolon
r_int
id|UsedDescrRatio
suffix:semicolon
r_int
id|RatioDiffAbs
suffix:semicolon
r_int
id|RatioDiffRel
suffix:semicolon
r_int
id|NewMaxModIntsPerSec
suffix:semicolon
r_int
id|ModAdjValue
suffix:semicolon
r_int
id|ModBase
suffix:semicolon
multiline_comment|/*&n;    ** Check first if we are allowed to perform any modification&n;    */
r_if
c_cond
(paren
id|IsIntModEnabled
c_func
(paren
id|pAC
)paren
)paren
(brace
r_if
c_cond
(paren
id|M_DIMINFO.IntModTypeSelect
op_ne
id|C_INT_MOD_DYNAMIC
)paren
(brace
r_return
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|M_DIMINFO.ModJustEnabled
)paren
(brace
id|M_DIMINFO.ModJustEnabled
op_assign
id|SK_FALSE
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;    ** If we got until here, we have to evaluate the amount of the&n;    ** descriptor ratio change...&n;    */
id|TotalMaxNbrDescr
op_assign
id|pAC-&gt;RxDescrPerRing
op_star
id|GetRxCalls
c_func
(paren
id|pAC
)paren
suffix:semicolon
id|UsedDescrRatio
op_assign
(paren
id|M_DIMINFO.NbrProcessedDescr
op_star
l_int|100
)paren
op_div
id|TotalMaxNbrDescr
suffix:semicolon
r_if
c_cond
(paren
id|UsedDescrRatio
OG
id|M_DIMINFO.PrevUsedDescrRatio
)paren
(brace
id|RatioDiffAbs
op_assign
(paren
id|UsedDescrRatio
op_minus
id|M_DIMINFO.PrevUsedDescrRatio
)paren
suffix:semicolon
id|RatioDiffRel
op_assign
(paren
id|RatioDiffAbs
op_star
l_int|100
)paren
op_div
id|UsedDescrRatio
suffix:semicolon
id|M_DIMINFO.PrevUsedDescrRatio
op_assign
id|UsedDescrRatio
suffix:semicolon
id|IncreaseTimerDuration
op_assign
id|SK_FALSE
suffix:semicolon
multiline_comment|/* in other words: DECREASE */
)brace
r_else
r_if
c_cond
(paren
id|UsedDescrRatio
OL
id|M_DIMINFO.PrevUsedDescrRatio
)paren
(brace
id|RatioDiffAbs
op_assign
(paren
id|M_DIMINFO.PrevUsedDescrRatio
op_minus
id|UsedDescrRatio
)paren
suffix:semicolon
id|RatioDiffRel
op_assign
(paren
id|RatioDiffAbs
op_star
l_int|100
)paren
op_div
id|M_DIMINFO.PrevUsedDescrRatio
suffix:semicolon
id|M_DIMINFO.PrevUsedDescrRatio
op_assign
id|UsedDescrRatio
suffix:semicolon
id|IncreaseTimerDuration
op_assign
id|SK_TRUE
suffix:semicolon
multiline_comment|/* in other words: INCREASE */
)brace
r_else
(brace
id|RatioDiffAbs
op_assign
(paren
id|M_DIMINFO.PrevUsedDescrRatio
op_minus
id|UsedDescrRatio
)paren
suffix:semicolon
id|RatioDiffRel
op_assign
(paren
id|RatioDiffAbs
op_star
l_int|100
)paren
op_div
id|M_DIMINFO.PrevUsedDescrRatio
suffix:semicolon
id|M_DIMINFO.PrevUsedDescrRatio
op_assign
id|UsedDescrRatio
suffix:semicolon
id|IncreaseTimerDuration
op_assign
id|SK_TRUE
suffix:semicolon
multiline_comment|/* in other words: INCREASE */
)brace
multiline_comment|/*&n;    ** Now we can determine the change in percent&n;    */
r_if
c_cond
(paren
(paren
id|RatioDiffRel
op_ge
l_int|0
)paren
op_logical_and
(paren
id|RatioDiffRel
op_le
l_int|5
)paren
)paren
(brace
id|ModAdjValue
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*  1% change - maybe some other value in future */
)brace
r_else
r_if
c_cond
(paren
(paren
id|RatioDiffRel
OG
l_int|5
)paren
op_logical_and
(paren
id|RatioDiffRel
op_le
l_int|10
)paren
)paren
(brace
id|ModAdjValue
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*  1% change - maybe some other value in future */
)brace
r_else
r_if
c_cond
(paren
(paren
id|RatioDiffRel
OG
l_int|10
)paren
op_logical_and
(paren
id|RatioDiffRel
op_le
l_int|15
)paren
)paren
(brace
id|ModAdjValue
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*  1% change - maybe some other value in future */
)brace
r_else
(brace
id|ModAdjValue
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*  1% change - maybe some other value in future */
)brace
r_if
c_cond
(paren
id|IncreaseTimerDuration
)paren
(brace
id|NewMaxModIntsPerSec
op_assign
id|M_DIMINFO.MaxModIntsPerSec
op_plus
(paren
id|M_DIMINFO.MaxModIntsPerSec
op_star
id|ModAdjValue
)paren
op_div
l_int|100
suffix:semicolon
)brace
r_else
(brace
id|NewMaxModIntsPerSec
op_assign
id|M_DIMINFO.MaxModIntsPerSec
op_minus
(paren
id|M_DIMINFO.MaxModIntsPerSec
op_star
id|ModAdjValue
)paren
op_div
l_int|100
suffix:semicolon
)brace
multiline_comment|/* &n;    ** Check if we exceed boundaries...&n;    */
r_if
c_cond
(paren
(paren
id|NewMaxModIntsPerSec
OG
id|M_DIMINFO.MaxModIntsPerSecUpperLimit
)paren
op_logical_or
(paren
id|NewMaxModIntsPerSec
OL
id|M_DIMINFO.MaxModIntsPerSecLowerLimit
)paren
)paren
(brace
r_if
c_cond
(paren
id|M_DIMINFO.DisplayStats
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Cannot change ModTim from %i to %i ints/sec&bslash;n&quot;
comma
id|M_DIMINFO.MaxModIntsPerSec
comma
id|NewMaxModIntsPerSec
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|M_DIMINFO.DisplayStats
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Resized ModTim from %i to %i ints/sec&bslash;n&quot;
comma
id|M_DIMINFO.MaxModIntsPerSec
comma
id|NewMaxModIntsPerSec
)paren
suffix:semicolon
)brace
)brace
id|M_DIMINFO.MaxModIntsPerSec
op_assign
id|NewMaxModIntsPerSec
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;GIni.GIChipId
op_eq
id|CHIP_ID_GENESIS
)paren
(brace
id|ModBase
op_assign
id|C_CLK_FREQ_GENESIS
op_div
id|pAC-&gt;DynIrqModInfo.MaxModIntsPerSec
suffix:semicolon
)brace
r_else
(brace
id|ModBase
op_assign
id|C_CLK_FREQ_YUKON
op_div
id|pAC-&gt;DynIrqModInfo.MaxModIntsPerSec
suffix:semicolon
)brace
multiline_comment|/* &n;    ** We do not need to touch any other registers&n;    */
id|SK_OUT32
c_func
(paren
id|pAC-&gt;IoBase
comma
id|B2_IRQM_INI
comma
id|ModBase
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n;** Function     : DisplaySelectedModerationType()&n;** Description  : Displays what type of moderation we have&n;** Programmer   : Ralph Roesler&n;** Last Modified: 23-mar-03&n;** Returns      : void!&n;** Notes        : -&n;*******************************************************************************/
r_static
r_void
DECL|function|DisplaySelectedModerationType
id|DisplaySelectedModerationType
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
r_if
c_cond
(paren
id|pAC-&gt;DynIrqModInfo.DisplayStats
)paren
(brace
r_if
c_cond
(paren
id|pAC-&gt;DynIrqModInfo.IntModTypeSelect
op_eq
id|C_INT_MOD_STATIC
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Static int moderation runs with %i INTS/sec&bslash;n&quot;
comma
id|pAC-&gt;DynIrqModInfo.MaxModIntsPerSec
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pAC-&gt;DynIrqModInfo.IntModTypeSelect
op_eq
id|C_INT_MOD_DYNAMIC
)paren
(brace
r_if
c_cond
(paren
id|IsIntModEnabled
c_func
(paren
id|pAC
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Dynamic int moderation runs with %i INTS/sec&bslash;n&quot;
comma
id|pAC-&gt;DynIrqModInfo.MaxModIntsPerSec
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Dynamic int moderation currently not applied&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;No interrupt moderation selected!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*******************************************************************************&n;** Function     : DisplaySelectedModerationMask()&n;** Description  : Displays what interrupts are moderated&n;** Programmer   : Ralph Roesler&n;** Last Modified: 23-mar-03&n;** Returns      : void!&n;** Notes        : -&n;*******************************************************************************/
r_static
r_void
DECL|function|DisplaySelectedModerationMask
id|DisplaySelectedModerationMask
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
r_if
c_cond
(paren
id|pAC-&gt;DynIrqModInfo.DisplayStats
)paren
(brace
r_if
c_cond
(paren
id|pAC-&gt;DynIrqModInfo.IntModTypeSelect
op_ne
id|C_INT_MOD_NONE
)paren
(brace
r_switch
c_cond
(paren
id|pAC-&gt;DynIrqModInfo.MaskIrqModeration
)paren
(brace
r_case
id|IRQ_MASK_TX_ONLY
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Only Tx-interrupts are moderated&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MASK_RX_ONLY
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Only Rx-interrupts are moderated&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MASK_SP_ONLY
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Only special-interrupts are moderated&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MASK_TX_RX
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Tx- and Rx-interrupts are moderated&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MASK_SP_RX
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Special- and Rx-interrupts are moderated&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MASK_SP_TX
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Special- and Tx-interrupts are moderated&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MASK_RX_TX_SP
suffix:colon
id|printk
c_func
(paren
l_string|&quot;All Rx-, Tx and special-interrupts are moderated&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Don&squot;t know what is moderated&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;No specific interrupts masked for moderation&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*******************************************************************************&n;** Function     : DisplayDescrRatio&n;** Description  : Like the name states...&n;** Programmer   : Ralph Roesler&n;** Last Modified: 23-mar-03&n;** Returns      : void!&n;** Notes        : -&n;*******************************************************************************/
r_static
r_void
DECL|function|DisplayDescrRatio
id|DisplayDescrRatio
c_func
(paren
id|SK_AC
op_star
id|pAC
)paren
(brace
r_int
id|TotalMaxNbrDescr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;DynIrqModInfo.DisplayStats
)paren
(brace
id|TotalMaxNbrDescr
op_assign
id|pAC-&gt;RxDescrPerRing
op_star
id|GetRxCalls
c_func
(paren
id|pAC
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Ratio descriptors: %i/%i&bslash;n&quot;
comma
id|M_DIMINFO.NbrProcessedDescr
comma
id|TotalMaxNbrDescr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n;**&n;** End of file&n;**&n;*******************************************************************************/
eof
