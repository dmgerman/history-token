multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skqueue.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.13 $&n; * Date:&t;$Date: 1999/11/22 13:59:05 $&n; * Purpose:&t;Defines for the Event queue&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skqueue.h,v $&n; *&t;Revision 1.13  1999/11/22 13:59:05  cgoos&n; *&t;Changed license header to GPL.&n; *&t;&n; *&t;Revision 1.12  1998/09/08 08:48:01  gklug&n; *&t;add: init level handling&n; *&t;&n; *&t;Revision 1.11  1998/09/03 14:15:11  gklug&n; *&t;add: CSUM and HWAC Eventclass and function.&n; *&t;fix: pParaPtr according to CCC&n; *&t;&n; *&t;Revision 1.10  1998/08/20 12:43:03  gklug&n; *&t;add: typedef SK_QUEUE&n; *&t;&n; *&t;Revision 1.9  1998/08/19 09:50:59  gklug&n; *&t;fix: remove struct keyword from c-code (see CCC) add typedefs&n; *&t;&n; *&t;Revision 1.8  1998/08/18 07:00:01  gklug&n; *&t;fix: SK_PTR not defined use void * instead.&n; *&t;&n; *&t;Revision 1.7  1998/08/17 13:43:19  gklug&n; *&t;chg: Parameter will be union of 64bit para, 2 times SK_U32 or SK_PTR&n; *&t;&n; *&t;Revision 1.6  1998/08/14 07:09:30  gklug&n; *&t;fix: chg pAc -&gt; pAC&n; *&t;&n; *&t;Revision 1.5  1998/08/11 14:26:44  gklug&n; *&t;chg: Event Dispatcher returns now int.&n; *&t;&n; *&t;Revision 1.4  1998/08/11 12:15:21  gklug&n; *&t;add: Error numbers of skqueue module&n; *&t;&n; *&t;Revision 1.3  1998/08/07 12:54:23  gklug&n; *&t;fix: first compiled version&n; *&t;&n; *&t;Revision 1.2  1998/08/07 09:34:00  gklug&n; *&t;adapt structure defs to CCC&n; *&t;add: prototypes for functions&n; *&t;&n; *&t;Revision 1.1  1998/07/30 14:52:12  gklug&n; *&t;Initial version.&n; *&t;Defines Event Classes, Event structs and queue management variables.&n; *&t;&n; *&t;&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * SKQUEUE.H&t;contains all defines and types for the event queue&n; */
macro_line|#ifndef _SKQUEUE_H_
DECL|macro|_SKQUEUE_H_
mdefine_line|#define _SKQUEUE_H_
multiline_comment|/*&n; * define the event classes to be served&n; */
DECL|macro|SKGE_DRV
mdefine_line|#define&t;SKGE_DRV&t;1&t;/* Driver Event Class */
DECL|macro|SKGE_RLMT
mdefine_line|#define&t;SKGE_RLMT&t;2&t;/* RLMT Event Class */
DECL|macro|SKGE_I2C
mdefine_line|#define&t;SKGE_I2C&t;3&t;/* i2C Event Class */
DECL|macro|SKGE_PNMI
mdefine_line|#define&t;SKGE_PNMI&t;4&t;/* PNMI Event Class */
DECL|macro|SKGE_CSUM
mdefine_line|#define&t;SKGE_CSUM&t;5&t;/* Checksum Event Class */
DECL|macro|SKGE_HWAC
mdefine_line|#define&t;SKGE_HWAC&t;6&t;/* Hardware Access Event Class */
multiline_comment|/*&n; * define event queue as circular buffer&n; */
DECL|macro|SK_MAX_EVENT
mdefine_line|#define SK_MAX_EVENT&t;64
multiline_comment|/*&n; * Parameter union for the Para stuff&n; */
DECL|union|u_EvPara
r_typedef
r_union
id|u_EvPara
(brace
DECL|member|pParaPtr
r_void
op_star
id|pParaPtr
suffix:semicolon
multiline_comment|/* Parameter Pointer */
DECL|member|Para64
id|SK_U64
id|Para64
suffix:semicolon
multiline_comment|/* Parameter 64bit version */
DECL|member|Para32
id|SK_U32
id|Para32
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Parameter Array of 32bit parameters */
DECL|typedef|SK_EVPARA
)brace
id|SK_EVPARA
suffix:semicolon
multiline_comment|/*&n; * Event Queue&n; *&t;skqueue.c&n; * events are class/value pairs&n; *&t;class&t;is addressee, e.g. RMT, PCM etc.&n; *&t;value&t;is command, e.g. line state change, ring op change etc.&n; */
DECL|struct|s_EventElem
r_typedef
r_struct
id|s_EventElem
(brace
DECL|member|Class
id|SK_U32
id|Class
suffix:semicolon
multiline_comment|/* Event class */
DECL|member|Event
id|SK_U32
id|Event
suffix:semicolon
multiline_comment|/* Event value */
DECL|member|Para
id|SK_EVPARA
id|Para
suffix:semicolon
multiline_comment|/* Event parameter */
DECL|typedef|SK_EVENTELEM
)brace
id|SK_EVENTELEM
suffix:semicolon
DECL|struct|s_Queue
r_typedef
r_struct
id|s_Queue
(brace
DECL|member|EvQueue
id|SK_EVENTELEM
id|EvQueue
(braket
id|SK_MAX_EVENT
)braket
suffix:semicolon
DECL|member|EvPut
id|SK_EVENTELEM
op_star
id|EvPut
suffix:semicolon
DECL|member|EvGet
id|SK_EVENTELEM
op_star
id|EvGet
suffix:semicolon
DECL|typedef|SK_QUEUE
)brace
id|SK_QUEUE
suffix:semicolon
r_extern
r_void
id|SkEventInit
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
id|SkEventQueue
c_func
(paren
id|SK_AC
op_star
id|pAC
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
r_int
id|SkEventDispatcher
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
multiline_comment|/* Define Error Numbers and messages */
DECL|macro|SKERR_Q_E001
mdefine_line|#define&t;SKERR_Q_E001&t;(SK_ERRBASE_QUEUE+0)
DECL|macro|SKERR_Q_E001MSG
mdefine_line|#define&t;SKERR_Q_E001MSG&t;&quot;Event queue overflow&quot;
DECL|macro|SKERR_Q_E002
mdefine_line|#define&t;SKERR_Q_E002&t;(SKERR_Q_E001+1)
DECL|macro|SKERR_Q_E002MSG
mdefine_line|#define&t;SKERR_Q_E002MSG&t;&quot;Undefined event class&quot;
macro_line|#endif&t;/* _SKQUEUE_H_ */
eof
