multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skgehwt.c&n; * Project:&t;Gigabit Ethernet Adapters, Event Scheduler Module&n; * Version:&t;$Revision: 1.15 $&n; * Date:&t;$Date: 2003/09/16 13:41:23 $&n; * Purpose:&t;Hardware Timer&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect GmbH.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *&t;Event queue and dispatcher&n; */
macro_line|#if (defined(DEBUG) || ((!defined(LINT)) &amp;&amp; (!defined(SK_SLIM))))
DECL|variable|SysKonnectFileId
r_static
r_const
r_char
id|SysKonnectFileId
(braket
)braket
op_assign
l_string|&quot;@(#) $Id: skgehwt.c,v 1.15 2003/09/16 13:41:23 rschmidt Exp $ (C) Marvell.&quot;
suffix:semicolon
macro_line|#endif
macro_line|#include &quot;h/skdrv1st.h&quot;&t;&t;/* Driver Specific Definitions */
macro_line|#include &quot;h/skdrv2nd.h&quot;&t;&t;/* Adapter Control- and Driver specific Def. */
macro_line|#ifdef __C2MAN__
multiline_comment|/*&n; *   Hardware Timer function queue management.&n; */
DECL|function|intro
id|intro
c_func
(paren
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/*&n; * Prototypes of local functions.&n; */
DECL|macro|SK_HWT_MAX
mdefine_line|#define&t;SK_HWT_MAX&t;(65000)
multiline_comment|/* correction factor */
DECL|macro|SK_HWT_FAC
mdefine_line|#define&t;SK_HWT_FAC&t;(1000 * (SK_U32)pAC-&gt;GIni.GIHstClkFact / 100)
multiline_comment|/*&n; * Initialize hardware timer.&n; *&n; * Must be called during init level 1.&n; */
DECL|function|SkHwtInit
r_void
id|SkHwtInit
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
multiline_comment|/* Adapters context */
id|SK_IOC
id|Ioc
)paren
multiline_comment|/* IoContext */
(brace
id|pAC-&gt;Hwt.TStart
op_assign
l_int|0
suffix:semicolon
id|pAC-&gt;Hwt.TStop
op_assign
l_int|0
suffix:semicolon
id|pAC-&gt;Hwt.TActive
op_assign
id|SK_FALSE
suffix:semicolon
id|SkHwtStop
c_func
(paren
id|pAC
comma
id|Ioc
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&n; * Start hardware timer (clock ticks are 16us).&n; *&n; */
DECL|function|SkHwtStart
r_void
id|SkHwtStart
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
multiline_comment|/* Adapters context */
id|SK_IOC
id|Ioc
comma
multiline_comment|/* IoContext */
id|SK_U32
id|Time
)paren
multiline_comment|/* Time in units of 16us to load the timer with. */
(brace
id|SK_U32
id|Cnt
suffix:semicolon
r_if
c_cond
(paren
id|Time
OG
id|SK_HWT_MAX
)paren
id|Time
op_assign
id|SK_HWT_MAX
suffix:semicolon
id|pAC-&gt;Hwt.TStart
op_assign
id|Time
suffix:semicolon
id|pAC-&gt;Hwt.TStop
op_assign
l_int|0L
suffix:semicolon
id|Cnt
op_assign
id|Time
suffix:semicolon
multiline_comment|/*&n;&t; * if time &lt; 16 us&n;&t; *&t;time = 16 us&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|Cnt
)paren
(brace
id|Cnt
op_increment
suffix:semicolon
)brace
id|SK_OUT32
c_func
(paren
id|Ioc
comma
id|B2_TI_INI
comma
id|Cnt
op_star
id|SK_HWT_FAC
)paren
suffix:semicolon
id|SK_OUT16
c_func
(paren
id|Ioc
comma
id|B2_TI_CTRL
comma
id|TIM_START
)paren
suffix:semicolon
multiline_comment|/* Start timer. */
id|pAC-&gt;Hwt.TActive
op_assign
id|SK_TRUE
suffix:semicolon
)brace
multiline_comment|/*&n; * Stop hardware timer.&n; * and clear the timer IRQ&n; */
DECL|function|SkHwtStop
r_void
id|SkHwtStop
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
multiline_comment|/* Adapters context */
id|SK_IOC
id|Ioc
)paren
multiline_comment|/* IoContext */
(brace
id|SK_OUT16
c_func
(paren
id|Ioc
comma
id|B2_TI_CTRL
comma
id|TIM_STOP
)paren
suffix:semicolon
id|SK_OUT16
c_func
(paren
id|Ioc
comma
id|B2_TI_CTRL
comma
id|TIM_CLR_IRQ
)paren
suffix:semicolon
id|pAC-&gt;Hwt.TActive
op_assign
id|SK_FALSE
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Stop hardware timer and read time elapsed since last start.&n; *&n; * returns&n; *&t;The elapsed time since last start in units of 16us.&n; *&n; */
DECL|function|SkHwtRead
id|SK_U32
id|SkHwtRead
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
multiline_comment|/* Adapters context */
id|SK_IOC
id|Ioc
)paren
multiline_comment|/* IoContext */
(brace
id|SK_U32
id|TRead
suffix:semicolon
id|SK_U32
id|IStatus
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;Hwt.TActive
)paren
(brace
id|SkHwtStop
c_func
(paren
id|pAC
comma
id|Ioc
)paren
suffix:semicolon
id|SK_IN32
c_func
(paren
id|Ioc
comma
id|B2_TI_VAL
comma
op_amp
id|TRead
)paren
suffix:semicolon
id|TRead
op_div_assign
id|SK_HWT_FAC
suffix:semicolon
id|SK_IN32
c_func
(paren
id|Ioc
comma
id|B0_ISRC
comma
op_amp
id|IStatus
)paren
suffix:semicolon
multiline_comment|/* Check if timer expired (or wraped around) */
r_if
c_cond
(paren
(paren
id|TRead
OG
id|pAC-&gt;Hwt.TStart
)paren
op_logical_or
(paren
id|IStatus
op_amp
id|IS_TIMINT
)paren
)paren
(brace
id|SkHwtStop
c_func
(paren
id|pAC
comma
id|Ioc
)paren
suffix:semicolon
id|pAC-&gt;Hwt.TStop
op_assign
id|pAC-&gt;Hwt.TStart
suffix:semicolon
)brace
r_else
(brace
id|pAC-&gt;Hwt.TStop
op_assign
id|pAC-&gt;Hwt.TStart
op_minus
id|TRead
suffix:semicolon
)brace
)brace
r_return
id|pAC-&gt;Hwt.TStop
suffix:semicolon
)brace
multiline_comment|/*&n; * interrupt source= timer&n; */
DECL|function|SkHwtIsr
r_void
id|SkHwtIsr
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
multiline_comment|/* Adapters context */
id|SK_IOC
id|Ioc
)paren
multiline_comment|/* IoContext */
(brace
id|SkHwtStop
c_func
(paren
id|pAC
comma
id|Ioc
)paren
suffix:semicolon
id|pAC-&gt;Hwt.TStop
op_assign
id|pAC-&gt;Hwt.TStart
suffix:semicolon
id|SkTimerDone
c_func
(paren
id|pAC
comma
id|Ioc
)paren
suffix:semicolon
)brace
multiline_comment|/* End of file */
eof
