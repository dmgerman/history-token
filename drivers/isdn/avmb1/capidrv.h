multiline_comment|/*&n; * $Id: capidrv.h,v 1.2 1998/03/29 16:06:06 calle Exp $&n; *&n; * ISDN4Linux Driver, using capi20 interface (kernelcapi)&n; *&n; * Copyright 1997 by Carsten Paeth (calle@calle.in-berlin.de)&n; *&n; * $Log: capidrv.h,v $&n; * Revision 1.2  1998/03/29 16:06:06  calle&n; * changes from 2.0 tree merged.&n; *&n; * Revision 1.1.2.1  1998/03/20 14:38:28  calle&n; * capidrv: prepared state machines for suspend/resume/hold&n; * capidrv: fix bug in state machine if B1/T1 is out of nccis&n; * b1capi: changed some errno returns.&n; * b1capi: detect if you try to add same T1 to different io address.&n; * b1capi: change number of nccis depending on number of channels.&n; * b1lli: cosmetics&n; *&n; * Revision 1.1  1997/03/04 21:50:33  calle&n; * Frirst version in isdn4linux&n; *&n; * Revision 2.2  1997/02/12 09:31:39  calle&n; * new version&n; *&n; * Revision 1.1  1997/01/31 10:32:20  calle&n; * Initial revision&n; *&n; */
macro_line|#ifndef __CAPIDRV_H__
DECL|macro|__CAPIDRV_H__
mdefine_line|#define __CAPIDRV_H__
multiline_comment|/*&n; * LISTEN state machine&n; */
DECL|macro|ST_LISTEN_NONE
mdefine_line|#define ST_LISTEN_NONE&t;&t;&t;0&t;/* L-0 */
DECL|macro|ST_LISTEN_WAIT_CONF
mdefine_line|#define ST_LISTEN_WAIT_CONF&t;&t;1&t;/* L-0.1 */
DECL|macro|ST_LISTEN_ACTIVE
mdefine_line|#define ST_LISTEN_ACTIVE&t;&t;2&t;/* L-1 */
DECL|macro|ST_LISTEN_ACTIVE_WAIT_CONF
mdefine_line|#define ST_LISTEN_ACTIVE_WAIT_CONF&t;3&t;/* L-1.1 */
DECL|macro|EV_LISTEN_REQ
mdefine_line|#define EV_LISTEN_REQ&t;&t;&t;1&t;/* L-0 -&gt; L-0.1&n;&t;&t;&t;&t;&t;&t;   L-1 -&gt; L-1.1 */
DECL|macro|EV_LISTEN_CONF_ERROR
mdefine_line|#define EV_LISTEN_CONF_ERROR&t;&t;2&t;/* L-0.1 -&gt; L-0&n;&t;&t;&t;&t;&t;&t;   L-1.1 -&gt; L-1 */
DECL|macro|EV_LISTEN_CONF_EMPTY
mdefine_line|#define EV_LISTEN_CONF_EMPTY&t;&t;3&t;/* L-0.1 -&gt; L-0&n;&t;&t;&t;&t;&t;&t;   L-1.1 -&gt; L-0 */
DECL|macro|EV_LISTEN_CONF_OK
mdefine_line|#define EV_LISTEN_CONF_OK&t;&t;4&t;/* L-0.1 -&gt; L-1&n;&t;&t;&t;&t;&t;&t;   L-1.1 -&gt; L.1 */
multiline_comment|/*&n; * per plci state machine&n; */
DECL|macro|ST_PLCI_NONE
mdefine_line|#define ST_PLCI_NONE&t;&t;&t;0&t;/* P-0 */
DECL|macro|ST_PLCI_OUTGOING
mdefine_line|#define ST_PLCI_OUTGOING &t;&t;1&t;/* P-0.1 */
DECL|macro|ST_PLCI_ALLOCATED
mdefine_line|#define ST_PLCI_ALLOCATED&t;&t;2&t;/* P-1 */
DECL|macro|ST_PLCI_ACTIVE
mdefine_line|#define ST_PLCI_ACTIVE&t;&t;&t;3&t;/* P-ACT */
DECL|macro|ST_PLCI_INCOMING
mdefine_line|#define ST_PLCI_INCOMING&t;&t;4&t;/* P-2 */
DECL|macro|ST_PLCI_FACILITY_IND
mdefine_line|#define ST_PLCI_FACILITY_IND&t;&t;5&t;/* P-3 */
DECL|macro|ST_PLCI_ACCEPTING
mdefine_line|#define ST_PLCI_ACCEPTING&t;&t;6&t;/* P-4 */
DECL|macro|ST_PLCI_DISCONNECTING
mdefine_line|#define ST_PLCI_DISCONNECTING&t;&t;7&t;/* P-5 */
DECL|macro|ST_PLCI_DISCONNECTED
mdefine_line|#define ST_PLCI_DISCONNECTED&t;&t;8&t;/* P-6 */
DECL|macro|ST_PLCI_RESUMEING
mdefine_line|#define ST_PLCI_RESUMEING&t;&t;9&t;/* P-0.Res */
DECL|macro|ST_PLCI_RESUME
mdefine_line|#define ST_PLCI_RESUME&t;&t;&t;10&t;/* P-Res */
DECL|macro|ST_PLCI_HELD
mdefine_line|#define ST_PLCI_HELD&t;&t;&t;11&t;/* P-HELD */
DECL|macro|EV_PLCI_CONNECT_REQ
mdefine_line|#define EV_PLCI_CONNECT_REQ&t;&t;1&t;/* P-0 -&gt; P-0.1&n;                                                 */
DECL|macro|EV_PLCI_CONNECT_CONF_ERROR
mdefine_line|#define EV_PLCI_CONNECT_CONF_ERROR&t;2&t;/* P-0.1 -&gt; P-0&n;                                                 */
DECL|macro|EV_PLCI_CONNECT_CONF_OK
mdefine_line|#define EV_PLCI_CONNECT_CONF_OK&t;&t;3&t;/* P-0.1 -&gt; P-1&n;                                                 */
DECL|macro|EV_PLCI_FACILITY_IND_UP
mdefine_line|#define EV_PLCI_FACILITY_IND_UP&t;&t;4&t;/* P-0 -&gt; P-1&n;                                                 */
DECL|macro|EV_PLCI_CONNECT_IND
mdefine_line|#define EV_PLCI_CONNECT_IND&t;&t;5&t;/* P-0 -&gt; P-2&n;                                                 */
DECL|macro|EV_PLCI_CONNECT_ACTIVE_IND
mdefine_line|#define EV_PLCI_CONNECT_ACTIVE_IND&t;6&t;/* P-1 -&gt; P-ACT&n;                                                 */
DECL|macro|EV_PLCI_CONNECT_REJECT
mdefine_line|#define EV_PLCI_CONNECT_REJECT&t;&t;7&t;/* P-2 -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-3 -&gt; P-5&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|EV_PLCI_DISCONNECT_REQ
mdefine_line|#define EV_PLCI_DISCONNECT_REQ&t;&t;8&t;/* P-1 -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-2 -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-3 -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-4 -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-ACT -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-Res -&gt; P-5 (*)&n;&t;&t;&t;&t;&t;&t;   P-HELD -&gt; P-5 (*)&n;&t;&t;&t;&t;&t;&t;   */
DECL|macro|EV_PLCI_DISCONNECT_IND
mdefine_line|#define EV_PLCI_DISCONNECT_IND&t;&t;9&t;/* P-1 -&gt; P-6&n;&t;&t;&t;&t;&t;&t;   P-2 -&gt; P-6&n;&t;&t;&t;&t;&t;&t;   P-3 -&gt; P-6&n;&t;&t;&t;&t;&t;&t;   P-4 -&gt; P-6&n;&t;&t;&t;&t;&t;&t;   P-5 -&gt; P-6&n;&t;&t;&t;&t;&t;&t;   P-ACT -&gt; P-6&n;&t;&t;&t;&t;&t;&t;   P-Res -&gt; P-6 (*)&n;&t;&t;&t;&t;&t;&t;   P-HELD -&gt; P-6 (*)&n;&t;&t;&t;&t;&t;&t;   */
DECL|macro|EV_PLCI_FACILITY_IND_DOWN
mdefine_line|#define EV_PLCI_FACILITY_IND_DOWN&t;10&t;/* P-0.1 -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-1 -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-ACT -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-2 -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-3 -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   P-4 -&gt; P-5&n;&t;&t;&t;&t;&t;&t;   */
DECL|macro|EV_PLCI_DISCONNECT_RESP
mdefine_line|#define EV_PLCI_DISCONNECT_RESP&t;&t;11&t;/* P-6 -&gt; P-0&n;                                                   */
DECL|macro|EV_PLCI_CONNECT_RESP
mdefine_line|#define EV_PLCI_CONNECT_RESP&t;&t;12&t;/* P-6 -&gt; P-0&n;                                                   */
DECL|macro|EV_PLCI_RESUME_REQ
mdefine_line|#define EV_PLCI_RESUME_REQ&t;&t;13&t;/* P-0 -&gt; P-0.Res&n;                                                 */
DECL|macro|EV_PLCI_RESUME_CONF_OK
mdefine_line|#define EV_PLCI_RESUME_CONF_OK&t;&t;14&t;/* P-0.Res -&gt; P-Res&n;                                                 */
DECL|macro|EV_PLCI_RESUME_CONF_ERROR
mdefine_line|#define EV_PLCI_RESUME_CONF_ERROR&t;15&t;/* P-0.Res -&gt; P-0&n;                                                 */
DECL|macro|EV_PLCI_RESUME_IND
mdefine_line|#define EV_PLCI_RESUME_IND&t;&t;16&t;/* P-Res -&gt; P-ACT&n;                                                 */
DECL|macro|EV_PLCI_HOLD_IND
mdefine_line|#define EV_PLCI_HOLD_IND&t;&t;17&t;/* P-ACT -&gt; P-HELD&n;                                                 */
DECL|macro|EV_PLCI_RETRIEVE_IND
mdefine_line|#define EV_PLCI_RETRIEVE_IND&t;&t;18&t;/* P-HELD -&gt; P-ACT&n;                                                 */
DECL|macro|EV_PLCI_SUSPEND_IND
mdefine_line|#define EV_PLCI_SUSPEND_IND&t;&t;19&t;/* P-ACT -&gt; P-5&n;                                                 */
DECL|macro|EV_PLCI_CD_IND
mdefine_line|#define EV_PLCI_CD_IND&t;&t;&t;20&t;/* P-2 -&gt; P-5&n;                                                 */
multiline_comment|/*&n; * per ncci state machine&n; */
DECL|macro|ST_NCCI_PREVIOUS
mdefine_line|#define ST_NCCI_PREVIOUS&t;&t;&t;-1
DECL|macro|ST_NCCI_NONE
mdefine_line|#define ST_NCCI_NONE&t;&t;&t;&t;0&t;/* N-0 */
DECL|macro|ST_NCCI_OUTGOING
mdefine_line|#define ST_NCCI_OUTGOING&t;&t;&t;1&t;/* N-0.1 */
DECL|macro|ST_NCCI_INCOMING
mdefine_line|#define ST_NCCI_INCOMING&t;&t;&t;2&t;/* N-1 */
DECL|macro|ST_NCCI_ALLOCATED
mdefine_line|#define ST_NCCI_ALLOCATED&t;&t;&t;3&t;/* N-2 */
DECL|macro|ST_NCCI_ACTIVE
mdefine_line|#define ST_NCCI_ACTIVE&t;&t;&t;&t;4&t;/* N-ACT */
DECL|macro|ST_NCCI_RESETING
mdefine_line|#define ST_NCCI_RESETING&t;&t;&t;5&t;/* N-3 */
DECL|macro|ST_NCCI_DISCONNECTING
mdefine_line|#define ST_NCCI_DISCONNECTING&t;&t;&t;6&t;/* N-4 */
DECL|macro|ST_NCCI_DISCONNECTED
mdefine_line|#define ST_NCCI_DISCONNECTED&t;&t;&t;7&t;/* N-5 */
DECL|macro|EV_NCCI_CONNECT_B3_REQ
mdefine_line|#define EV_NCCI_CONNECT_B3_REQ&t;&t;&t;1&t;/* N-0 -&gt; N-0.1 */
DECL|macro|EV_NCCI_CONNECT_B3_IND
mdefine_line|#define EV_NCCI_CONNECT_B3_IND&t;&t;&t;2&t;/* N-0 -&gt; N.1 */
DECL|macro|EV_NCCI_CONNECT_B3_CONF_OK
mdefine_line|#define EV_NCCI_CONNECT_B3_CONF_OK&t;&t;3&t;/* N-0.1 -&gt; N.2 */
DECL|macro|EV_NCCI_CONNECT_B3_CONF_ERROR
mdefine_line|#define EV_NCCI_CONNECT_B3_CONF_ERROR&t;&t;4&t;/* N-0.1 -&gt; N.0 */
DECL|macro|EV_NCCI_CONNECT_B3_REJECT
mdefine_line|#define EV_NCCI_CONNECT_B3_REJECT&t;&t;5&t;/* N-1 -&gt; N-4 */
DECL|macro|EV_NCCI_CONNECT_B3_RESP
mdefine_line|#define EV_NCCI_CONNECT_B3_RESP&t;&t;&t;6&t;/* N-1 -&gt; N-2 */
DECL|macro|EV_NCCI_CONNECT_B3_ACTIVE_IND
mdefine_line|#define EV_NCCI_CONNECT_B3_ACTIVE_IND&t;&t;7&t;/* N-2 -&gt; N-ACT */
DECL|macro|EV_NCCI_RESET_B3_REQ
mdefine_line|#define EV_NCCI_RESET_B3_REQ&t;&t;&t;8&t;/* N-ACT -&gt; N-3 */
DECL|macro|EV_NCCI_RESET_B3_IND
mdefine_line|#define EV_NCCI_RESET_B3_IND&t;&t;&t;9&t;/* N-3 -&gt; N-ACT */
DECL|macro|EV_NCCI_DISCONNECT_B3_IND
mdefine_line|#define EV_NCCI_DISCONNECT_B3_IND&t;&t;10&t;/* N-4 -&gt; N.5 */
DECL|macro|EV_NCCI_DISCONNECT_B3_CONF_ERROR
mdefine_line|#define EV_NCCI_DISCONNECT_B3_CONF_ERROR&t;11&t;/* N-4 -&gt; previous */
DECL|macro|EV_NCCI_DISCONNECT_B3_REQ
mdefine_line|#define EV_NCCI_DISCONNECT_B3_REQ&t;&t;12&t;/* N-1 -&gt; N-4&n;&t;&t;&t;&t;&t;&t;&t;   N-2 -&gt; N-4&n;&t;&t;&t;&t;&t;&t;&t;   N-3 -&gt; N-4&n;&t;&t;&t;&t;&t;&t;&t;   N-ACT -&gt; N-4 */
DECL|macro|EV_NCCI_DISCONNECT_B3_RESP
mdefine_line|#define EV_NCCI_DISCONNECT_B3_RESP&t;&t;13&t;/* N-5 -&gt; N-0 */
macro_line|#endif&t;&t;&t;&t;/* __CAPIDRV_H__ */
eof
