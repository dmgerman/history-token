multiline_comment|/******************************************************************************&n; *&n; * Name:&t;sktimer.h&n; * Project:&t;Gigabit Ethernet Adapters, Event Scheduler Module&n; * Version:&t;$Revision: 1.11 $&n; * Date:&t;$Date: 2003/09/16 12:58:18 $&n; * Purpose:&t;Defines for the timer functions&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect GmbH.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * SKTIMER.H&t;contains all defines and types for the timer functions&n; */
macro_line|#ifndef&t;_SKTIMER_H_
DECL|macro|_SKTIMER_H_
mdefine_line|#define _SKTIMER_H_
macro_line|#include &quot;h/skqueue.h&quot;
multiline_comment|/*&n; * SK timer&n; * - needed wherever a timer is used. Put this in your data structure&n; *   wherever you want.&n; */
DECL|typedef|SK_TIMER
r_typedef
r_struct
id|s_Timer
id|SK_TIMER
suffix:semicolon
DECL|struct|s_Timer
r_struct
id|s_Timer
(brace
DECL|member|TmNext
id|SK_TIMER
op_star
id|TmNext
suffix:semicolon
multiline_comment|/* linked list */
DECL|member|TmClass
id|SK_U32
id|TmClass
suffix:semicolon
multiline_comment|/* Timer Event class */
DECL|member|TmEvent
id|SK_U32
id|TmEvent
suffix:semicolon
multiline_comment|/* Timer Event value */
DECL|member|TmPara
id|SK_EVPARA
id|TmPara
suffix:semicolon
multiline_comment|/* Timer Event parameter */
DECL|member|TmDelta
id|SK_U32
id|TmDelta
suffix:semicolon
multiline_comment|/* delta time */
DECL|member|TmActive
r_int
id|TmActive
suffix:semicolon
multiline_comment|/* flag: active/inactive */
)brace
suffix:semicolon
multiline_comment|/*&n; * Timer control struct.&n; * - use in Adapters context name pAC-&gt;Tim&n; */
DECL|struct|s_TimCtrl
r_typedef
r_struct
id|s_TimCtrl
(brace
DECL|member|StQueue
id|SK_TIMER
op_star
id|StQueue
suffix:semicolon
multiline_comment|/* Head of Timer queue */
DECL|typedef|SK_TIMCTRL
)brace
id|SK_TIMCTRL
suffix:semicolon
r_extern
r_void
id|SkTimerInit
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
id|Level
)paren
suffix:semicolon
r_extern
r_void
id|SkTimerStop
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|Ioc
comma
id|SK_TIMER
op_star
id|pTimer
)paren
suffix:semicolon
r_extern
r_void
id|SkTimerStart
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|Ioc
comma
id|SK_TIMER
op_star
id|pTimer
comma
id|SK_U32
id|Time
comma
id|SK_U32
id|Class
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
id|SkTimerDone
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
id|SK_IOC
id|Ioc
)paren
suffix:semicolon
macro_line|#endif&t;/* _SKTIMER_H_ */
eof
