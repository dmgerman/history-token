multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skqueue.h&n; * Project:&t;Gigabit Ethernet Adapters, Event Scheduler Module&n; * Version:&t;$Revision: 1.16 $&n; * Date:&t;$Date: 2003/09/16 12:50:32 $&n; * Purpose:&t;Defines for the Event queue&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect GmbH.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
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
mdefine_line|#define&t;SKGE_I2C&t;3&t;/* I2C Event Class */
DECL|macro|SKGE_PNMI
mdefine_line|#define&t;SKGE_PNMI&t;4&t;/* PNMI Event Class */
DECL|macro|SKGE_CSUM
mdefine_line|#define&t;SKGE_CSUM&t;5&t;/* Checksum Event Class */
DECL|macro|SKGE_HWAC
mdefine_line|#define&t;SKGE_HWAC&t;6&t;/* Hardware Access Event Class */
DECL|macro|SKGE_SWT
mdefine_line|#define&t;SKGE_SWT&t;9&t;/* Software Timer Event Class */
DECL|macro|SKGE_LACP
mdefine_line|#define&t;SKGE_LACP&t;10&t;/* LACP Aggregation Event Class */
DECL|macro|SKGE_RSF
mdefine_line|#define&t;SKGE_RSF&t;11&t;/* RSF Aggregation Event Class */
DECL|macro|SKGE_MARKER
mdefine_line|#define&t;SKGE_MARKER&t;12&t;/* MARKER Aggregation Event Class */
DECL|macro|SKGE_FD
mdefine_line|#define&t;SKGE_FD&t;&t;13&t;/* FD Distributor Event Class */
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
multiline_comment|/*&n; * Event Queue&n; *&t;skqueue.c&n; * events are class/value pairs&n; *&t;class&t;is addressee, e.g. RLMT, PNMI etc.&n; *&t;value&t;is command, e.g. line state change, ring op change etc.&n; */
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
