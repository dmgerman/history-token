multiline_comment|/******************************************************************************&n; *&n; * Name:&t;sktimer.h&n; * Project:&t;Genesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.8 $&n; * Date:&t;$Date: 1998/09/08 08:48:02 $&n; * Purpose:&t;Defines for the timer functions&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1989-1998 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&t;All Rights Reserved&n; *&n; *&t;THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SYSKONNECT&n; *&t;The copyright notice above does not evidence any&n; *&t;actual or intended publication of such source code.&n; *&n; *&t;This Module contains Proprietary Information of SysKonnect&n; *&t;and should be treated as Confidential.&n; *&n; *&t;The information in this file is provided for the exclusive use of&n; *&t;the licensees of SysKonnect.&n; *&t;Such users have the right to use, modify, and incorporate this code&n; *&t;into products for purposes authorized by the license agreement&n; *&t;provided they include this notice and the associated copyright notice&n; *&t;with any such product.&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: sktimer.h,v $&n; *&t;Revision 1.8  1998/09/08 08:48:02  gklug&n; *&t;add: init level handling&n; *&t;&n; *&t;Revision 1.7  1998/08/20 12:31:29  gklug&n; *&t;fix: SK_TIMCTRL needs to be defined&n; *&t;&n; *&t;Revision 1.6  1998/08/19 09:51:00  gklug&n; *&t;fix: remove struct keyword from c-code (see CCC) add typedefs&n; *&t;&n; *&t;Revision 1.5  1998/08/17 13:43:21  gklug&n; *&t;chg: Parameter will be union of 64bit para, 2 times SK_U32 or SK_PTR&n; *&t;&n; *&t;Revision 1.4  1998/08/14 07:09:31  gklug&n; *&t;fix: chg pAc -&gt; pAC&n; *&t;&n; *&t;Revision 1.3  1998/08/07 12:54:24  gklug&n; *&t;fix: first compiled version&n; *&t;&n; *&t;Revision 1.2  1998/08/07 09:35:29  gklug&n; *&t;add: Timer control struct for Adapters context&n; *&t;add: function prototypes&n; *&t;&n; *&t;Revision 1.1  1998/08/05 11:27:01  gklug&n; *&t;First version: adapted from SMT&n; *&t;&n; *&n; ******************************************************************************/
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
multiline_comment|/* flag : active/inactive */
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
