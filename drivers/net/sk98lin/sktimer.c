multiline_comment|/******************************************************************************&n; *&n; * Name:&t;sktimer.c&n; * Project:&t;Gigabit Ethernet Adapters, Event Scheduler Module&n; * Version:&t;$Revision: 1.14 $&n; * Date:&t;$Date: 2003/09/16 13:46:51 $&n; * Purpose:&t;High level timer functions.&n; *&n; ******************************************************************************/
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
l_string|&quot;@(#) $Id: sktimer.c,v 1.14 2003/09/16 13:46:51 rschmidt Exp $ (C) Marvell.&quot;
suffix:semicolon
macro_line|#endif
macro_line|#include &quot;h/skdrv1st.h&quot;&t;&t;/* Driver Specific Definitions */
macro_line|#include &quot;h/skdrv2nd.h&quot;&t;&t;/* Adapter Control- and Driver specific Def. */
macro_line|#ifdef __C2MAN__
multiline_comment|/*&n;&t;Event queue management.&n;&n;&t;General Description:&n;&n; */
DECL|function|intro
id|intro
c_func
(paren
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/* Forward declaration */
r_static
r_void
id|timer_done
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|Ioc
comma
r_int
id|Restart
)paren
suffix:semicolon
multiline_comment|/*&n; * Inits the software timer&n; *&n; * needs to be called during Init level 1.&n; */
DECL|function|SkTimerInit
r_void
id|SkTimerInit
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
r_int
id|Level
)paren
multiline_comment|/* Init Level */
(brace
r_switch
c_cond
(paren
id|Level
)paren
(brace
r_case
id|SK_INIT_DATA
suffix:colon
id|pAC-&gt;Tim.StQueue
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SK_INIT_IO
suffix:colon
id|SkHwtInit
c_func
(paren
id|pAC
comma
id|Ioc
)paren
suffix:semicolon
id|SkTimerDone
c_func
(paren
id|pAC
comma
id|Ioc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Stops a high level timer&n; * - If a timer is not in the queue the function returns normally, too.&n; */
DECL|function|SkTimerStop
r_void
id|SkTimerStop
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
id|SK_TIMER
op_star
id|pTimer
)paren
multiline_comment|/* Timer Pointer to be started */
(brace
id|SK_TIMER
op_star
op_star
id|ppTimPrev
suffix:semicolon
id|SK_TIMER
op_star
id|pTm
suffix:semicolon
multiline_comment|/*&n;&t; * remove timer from queue&n;&t; */
id|pTimer-&gt;TmActive
op_assign
id|SK_FALSE
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;Tim.StQueue
op_eq
id|pTimer
op_logical_and
op_logical_neg
id|pTimer-&gt;TmNext
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
)brace
r_for
c_loop
(paren
id|ppTimPrev
op_assign
op_amp
id|pAC-&gt;Tim.StQueue
suffix:semicolon
(paren
id|pTm
op_assign
op_star
id|ppTimPrev
)paren
suffix:semicolon
id|ppTimPrev
op_assign
op_amp
id|pTm-&gt;TmNext
)paren
(brace
r_if
c_cond
(paren
id|pTm
op_eq
id|pTimer
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Timer found in queue&n;&t;&t;&t; * - dequeue it and&n;&t;&t;&t; * - correct delta of the next timer&n;&t;&t;&t; */
op_star
id|ppTimPrev
op_assign
id|pTm-&gt;TmNext
suffix:semicolon
r_if
c_cond
(paren
id|pTm-&gt;TmNext
)paren
(brace
multiline_comment|/* correct delta of next timer in queue */
id|pTm-&gt;TmNext-&gt;TmDelta
op_add_assign
id|pTm-&gt;TmDelta
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Start a high level software timer&n; */
DECL|function|SkTimerStart
r_void
id|SkTimerStart
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
id|SK_TIMER
op_star
id|pTimer
comma
multiline_comment|/* Timer Pointer to be started */
id|SK_U32
id|Time
comma
multiline_comment|/* Time value */
id|SK_U32
id|Class
comma
multiline_comment|/* Event Class for this timer */
id|SK_U32
id|Event
comma
multiline_comment|/* Event Value for this timer */
id|SK_EVPARA
id|Para
)paren
multiline_comment|/* Event Parameter for this timer */
(brace
id|SK_TIMER
op_star
op_star
id|ppTimPrev
suffix:semicolon
id|SK_TIMER
op_star
id|pTm
suffix:semicolon
id|SK_U32
id|Delta
suffix:semicolon
id|Time
op_div_assign
l_int|16
suffix:semicolon
multiline_comment|/* input is uS, clock ticks are 16uS */
r_if
c_cond
(paren
op_logical_neg
id|Time
)paren
id|Time
op_assign
l_int|1
suffix:semicolon
id|SkTimerStop
c_func
(paren
id|pAC
comma
id|Ioc
comma
id|pTimer
)paren
suffix:semicolon
id|pTimer-&gt;TmClass
op_assign
id|Class
suffix:semicolon
id|pTimer-&gt;TmEvent
op_assign
id|Event
suffix:semicolon
id|pTimer-&gt;TmPara
op_assign
id|Para
suffix:semicolon
id|pTimer-&gt;TmActive
op_assign
id|SK_TRUE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pAC-&gt;Tim.StQueue
)paren
(brace
multiline_comment|/* First Timer to be started */
id|pAC-&gt;Tim.StQueue
op_assign
id|pTimer
suffix:semicolon
id|pTimer-&gt;TmNext
op_assign
l_int|0
suffix:semicolon
id|pTimer-&gt;TmDelta
op_assign
id|Time
suffix:semicolon
id|SkHwtStart
c_func
(paren
id|pAC
comma
id|Ioc
comma
id|Time
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * timer correction&n;&t; */
id|timer_done
c_func
(paren
id|pAC
comma
id|Ioc
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * find position in queue&n;&t; */
id|Delta
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|ppTimPrev
op_assign
op_amp
id|pAC-&gt;Tim.StQueue
suffix:semicolon
(paren
id|pTm
op_assign
op_star
id|ppTimPrev
)paren
suffix:semicolon
id|ppTimPrev
op_assign
op_amp
id|pTm-&gt;TmNext
)paren
(brace
r_if
c_cond
(paren
id|Delta
op_plus
id|pTm-&gt;TmDelta
OG
id|Time
)paren
(brace
multiline_comment|/* Position found */
multiline_comment|/* Here the timer needs to be inserted. */
r_break
suffix:semicolon
)brace
id|Delta
op_add_assign
id|pTm-&gt;TmDelta
suffix:semicolon
)brace
multiline_comment|/* insert in queue */
op_star
id|ppTimPrev
op_assign
id|pTimer
suffix:semicolon
id|pTimer-&gt;TmNext
op_assign
id|pTm
suffix:semicolon
id|pTimer-&gt;TmDelta
op_assign
id|Time
op_minus
id|Delta
suffix:semicolon
r_if
c_cond
(paren
id|pTm
)paren
(brace
multiline_comment|/* There is a next timer&n;&t;&t; * -&gt; correct its Delta value.&n;&t;&t; */
id|pTm-&gt;TmDelta
op_sub_assign
id|pTimer-&gt;TmDelta
suffix:semicolon
)brace
multiline_comment|/* restart with first */
id|SkHwtStart
c_func
(paren
id|pAC
comma
id|Ioc
comma
id|pAC-&gt;Tim.StQueue-&gt;TmDelta
)paren
suffix:semicolon
)brace
DECL|function|SkTimerDone
r_void
id|SkTimerDone
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
id|timer_done
c_func
(paren
id|pAC
comma
id|Ioc
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|timer_done
r_static
r_void
id|timer_done
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
r_int
id|Restart
)paren
multiline_comment|/* Do we need to restart the Hardware timer ? */
(brace
id|SK_U32
id|Delta
suffix:semicolon
id|SK_TIMER
op_star
id|pTm
suffix:semicolon
id|SK_TIMER
op_star
id|pTComp
suffix:semicolon
multiline_comment|/* Timer completed now now */
id|SK_TIMER
op_star
op_star
id|ppLast
suffix:semicolon
multiline_comment|/* Next field of Last timer to be deq */
r_int
id|Done
op_assign
l_int|0
suffix:semicolon
id|Delta
op_assign
id|SkHwtRead
c_func
(paren
id|pAC
comma
id|Ioc
)paren
suffix:semicolon
id|ppLast
op_assign
op_amp
id|pAC-&gt;Tim.StQueue
suffix:semicolon
id|pTm
op_assign
id|pAC-&gt;Tim.StQueue
suffix:semicolon
r_while
c_loop
(paren
id|pTm
op_logical_and
op_logical_neg
id|Done
)paren
(brace
r_if
c_cond
(paren
id|Delta
op_ge
id|pTm-&gt;TmDelta
)paren
(brace
multiline_comment|/* Timer ran out */
id|pTm-&gt;TmActive
op_assign
id|SK_FALSE
suffix:semicolon
id|Delta
op_sub_assign
id|pTm-&gt;TmDelta
suffix:semicolon
id|ppLast
op_assign
op_amp
id|pTm-&gt;TmNext
suffix:semicolon
id|pTm
op_assign
id|pTm-&gt;TmNext
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We found the first timer that did not run out */
id|pTm-&gt;TmDelta
op_sub_assign
id|Delta
suffix:semicolon
id|Delta
op_assign
l_int|0
suffix:semicolon
id|Done
op_assign
l_int|1
suffix:semicolon
)brace
)brace
op_star
id|ppLast
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * pTm points to the first Timer that did not run out.&n;&t; * StQueue points to the first Timer that run out.&n;&t; */
r_for
c_loop
(paren
id|pTComp
op_assign
id|pAC-&gt;Tim.StQueue
suffix:semicolon
id|pTComp
suffix:semicolon
id|pTComp
op_assign
id|pTComp-&gt;TmNext
)paren
(brace
id|SkEventQueue
c_func
(paren
id|pAC
comma
id|pTComp-&gt;TmClass
comma
id|pTComp-&gt;TmEvent
comma
id|pTComp-&gt;TmPara
)paren
suffix:semicolon
)brace
multiline_comment|/* Set head of timer queue to the first timer that did not run out */
id|pAC-&gt;Tim.StQueue
op_assign
id|pTm
suffix:semicolon
r_if
c_cond
(paren
id|Restart
op_logical_and
id|pAC-&gt;Tim.StQueue
)paren
(brace
multiline_comment|/* Restart HW timer */
id|SkHwtStart
c_func
(paren
id|pAC
comma
id|Ioc
comma
id|pAC-&gt;Tim.StQueue-&gt;TmDelta
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* End of file */
eof
