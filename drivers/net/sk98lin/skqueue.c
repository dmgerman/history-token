multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skqueue.c&n; * Project:&t;PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.14 $&n; * Date:&t;$Date: 1998/10/15 15:11:35 $&n; * Purpose:&t;Management of an event queue.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1989-1998 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&t;All Rights Reserved&n; *&n; *&t;THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SYSKONNECT&n; *&t;The copyright notice above does not evidence any&n; *&t;actual or intended publication of such source code.&n; *&n; *&t;This Module contains Proprietary Information of SysKonnect&n; *&t;and should be treated as Confidential.&n; *&n; *&t;The information in this file is provided for the exclusive use of&n; *&t;the licensees of SysKonnect.&n; *&t;Such users have the right to use, modify, and incorporate this code&n; *&t;into products for purposes authorized by the license agreement&n; *&t;provided they include this notice and the associated copyright notice&n; *&t;with any such product.&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skqueue.c,v $&n; *&t;Revision 1.14  1998/10/15 15:11:35  gklug&n; *&t;fix: ID_sccs to SysKonnectFileId&n; *&t;&n; *&t;Revision 1.13  1998/09/08 08:47:52  gklug&n; *&t;add: init level handling&n; *&t;&n; *&t;Revision 1.12  1998/09/08 07:43:20  gklug&n; *&t;fix: Sirq Event function name&n; *&t;&n; *&t;Revision 1.11  1998/09/08 05:54:34  gklug&n; *&t;chg: define SK_CSUM is replaced by SK_USE_CSUM&n; *&t;&n; *&t;Revision 1.10  1998/09/03 14:14:49  gklug&n; *&t;add: CSUM and HWAC Eventclass and function.&n; *&t;&n; *&t;Revision 1.9  1998/08/19 09:50:50  gklug&n; *&t;fix: remove struct keyword from c-code (see CCC) add typedefs&n; *&t;&n; *&t;Revision 1.8  1998/08/17 13:43:11  gklug&n; *&t;chg: Parameter will be union of 64bit para, 2 times SK_U32 or SK_PTR&n; *&t;&n; *&t;Revision 1.7  1998/08/14 07:09:11  gklug&n; *&t;fix: chg pAc -&gt; pAC&n; *&t;&n; *&t;Revision 1.6  1998/08/11 12:13:14  gklug&n; *&t;add: return code feature of Event service routines&n; *&t;add: correct Error log calls&n; *&t;&n; *&t;Revision 1.5  1998/08/07 12:53:45  gklug&n; *&t;fix: first compiled version&n; *&t;&n; *&t;Revision 1.4  1998/08/07 09:20:48  gklug&n; *&t;adapt functions to C coding conventions.&n; *&t;&n; *&t;Revision 1.3  1998/08/05 11:29:32  gklug&n; *&t;rmv: Timer event entry. Timer will queue event directly&n; *&t;&n; *&t;Revision 1.2  1998/07/31 11:22:40  gklug&n; *&t;Initial version&n; *&t;&n; *&t;Revision 1.1  1998/07/30 15:14:01  gklug&n; *&t;Initial version. Adapted from SMT&n; *&t;&n; *&t;&n; *&n; ******************************************************************************/
multiline_comment|/*&n;&t;Event queue and dispatcher&n;*/
DECL|variable|SysKonnectFileId
r_static
r_const
r_char
id|SysKonnectFileId
(braket
)braket
op_assign
l_string|&quot;$Header: /usr56/projects/ge/schedule/skqueue.c,v 1.14 1998/10/15 15:11:35 gklug Exp $&quot;
suffix:semicolon
macro_line|#include &quot;h/skdrv1st.h&quot;&t;&t;/* Driver Specific Definitions */
macro_line|#include &quot;h/skqueue.h&quot;&t;&t;/* Queue Definitions */
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
DECL|macro|PRINTF
mdefine_line|#define PRINTF(a,b,c)
multiline_comment|/*&n; * init event queue management&n; *&n; * Must be called during init level 0.&n; */
DECL|function|SkEventInit
r_void
id|SkEventInit
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
multiline_comment|/* Adapter context */
id|SK_IOC
id|Ioc
comma
multiline_comment|/* IO context */
r_int
id|Level
)paren
multiline_comment|/* Init level */
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
id|pAC-&gt;Event.EvPut
op_assign
id|pAC-&gt;Event.EvGet
op_assign
id|pAC-&gt;Event.EvQueue
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * add event to queue&n; */
DECL|function|SkEventQueue
r_void
id|SkEventQueue
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
multiline_comment|/* Adapters context */
id|SK_U32
id|Class
comma
multiline_comment|/* Event Class */
id|SK_U32
id|Event
comma
multiline_comment|/* Event to be queued */
id|SK_EVPARA
id|Para
)paren
multiline_comment|/* Event parameter */
(brace
id|pAC-&gt;Event.EvPut-&gt;Class
op_assign
id|Class
suffix:semicolon
id|pAC-&gt;Event.EvPut-&gt;Event
op_assign
id|Event
suffix:semicolon
id|pAC-&gt;Event.EvPut-&gt;Para
op_assign
id|Para
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|pAC-&gt;Event.EvPut
op_eq
op_amp
id|pAC-&gt;Event.EvQueue
(braket
id|SK_MAX_EVENT
)braket
)paren
id|pAC-&gt;Event.EvPut
op_assign
id|pAC-&gt;Event.EvQueue
suffix:semicolon
r_if
c_cond
(paren
id|pAC-&gt;Event.EvPut
op_eq
id|pAC-&gt;Event.EvGet
)paren
(brace
id|SK_ERR_LOG
c_func
(paren
id|pAC
comma
id|SK_ERRCL_NORES
comma
id|SKERR_Q_E001
comma
id|SKERR_Q_E001MSG
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * event dispatcher&n; *&t;while event queue is not empty&n; *&t;&t;get event from queue&n; *&t;&t;send command to state machine&n; *&t;end&n; *&t;return error reported by individual Event function&n; *&t;&t;0 if no error occurred.&n; */
DECL|function|SkEventDispatcher
r_int
id|SkEventDispatcher
c_func
(paren
id|SK_AC
op_star
id|pAC
comma
multiline_comment|/* Adapters Context */
id|SK_IOC
id|Ioc
)paren
multiline_comment|/* Io context */
(brace
id|SK_EVENTELEM
op_star
id|pEv
suffix:semicolon
multiline_comment|/* pointer into queue */
id|SK_U32
id|Class
suffix:semicolon
r_int
id|Rtv
suffix:semicolon
id|pEv
op_assign
id|pAC-&gt;Event.EvGet
suffix:semicolon
id|PRINTF
c_func
(paren
l_string|&quot;dispatch get %x put %x&bslash;n&quot;
comma
id|pEv
comma
id|pAC-&gt;Event.ev_put
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pEv
op_ne
id|pAC-&gt;Event.EvPut
)paren
(brace
id|PRINTF
c_func
(paren
l_string|&quot;dispatch Class %d Event %d&bslash;n&quot;
comma
id|pEv-&gt;Class
comma
id|pEv-&gt;Event
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|Class
op_assign
id|pEv-&gt;Class
)paren
(brace
r_case
id|SKGE_DRV
suffix:colon
multiline_comment|/* Driver Event */
id|Rtv
op_assign
id|SkDrvEvent
c_func
(paren
id|pAC
comma
id|Ioc
comma
id|pEv-&gt;Event
comma
id|pEv-&gt;Para
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SKGE_RLMT
suffix:colon
multiline_comment|/* RLMT Event */
id|Rtv
op_assign
id|SkRlmtEvent
c_func
(paren
id|pAC
comma
id|Ioc
comma
id|pEv-&gt;Event
comma
id|pEv-&gt;Para
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SKGE_I2C
suffix:colon
multiline_comment|/* I2C Event */
id|Rtv
op_assign
id|SkI2cEvent
c_func
(paren
id|pAC
comma
id|Ioc
comma
id|pEv-&gt;Event
comma
id|pEv-&gt;Para
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SKGE_PNMI
suffix:colon
id|Rtv
op_assign
id|SkPnmiEvent
c_func
(paren
id|pAC
comma
id|Ioc
comma
id|pEv-&gt;Event
comma
id|pEv-&gt;Para
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SKGE_HWAC
suffix:colon
id|Rtv
op_assign
id|SkGeSirqEvent
c_func
(paren
id|pAC
comma
id|Ioc
comma
id|pEv-&gt;Event
comma
id|pEv-&gt;Para
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef&t;SK_USE_CSUM
r_case
id|SKGE_CSUM
suffix:colon
id|Rtv
op_assign
id|SkCsEvent
c_func
(paren
id|pAC
comma
id|Ioc
comma
id|pEv-&gt;Event
comma
id|pEv-&gt;Para
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif&t;/* SK_USE_CSUM */
r_default
suffix:colon
id|SK_ERR_LOG
c_func
(paren
id|pAC
comma
id|SK_ERRCL_SW
comma
id|SKERR_Q_E002
comma
id|SKERR_Q_E002MSG
)paren
suffix:semicolon
id|Rtv
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Rtv
op_ne
l_int|0
)paren
(brace
r_return
(paren
id|Rtv
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|pEv
op_eq
op_amp
id|pAC-&gt;Event.EvQueue
(braket
id|SK_MAX_EVENT
)braket
)paren
id|pEv
op_assign
id|pAC-&gt;Event.EvQueue
suffix:semicolon
multiline_comment|/* Renew get: it is used in queue_events to detect overruns */
id|pAC-&gt;Event.EvGet
op_assign
id|pEv
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* End of file */
eof
