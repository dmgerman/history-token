multiline_comment|/* $Id: l3dss1.h,v 1.10.6.2 2001/09/23 22:24:50 kai Exp $&n; *&n; * DSS1 (Euro) D-channel protocol defines&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef l3dss1_process
DECL|macro|T302
mdefine_line|#define T302&t;15000
DECL|macro|T303
mdefine_line|#define T303&t;4000
DECL|macro|T304
mdefine_line|#define T304&t;30000
DECL|macro|T305
mdefine_line|#define T305&t;30000
DECL|macro|T308
mdefine_line|#define T308&t;4000
multiline_comment|/* for layer 1 certification T309 &lt; layer1 T3 (e.g. 4000) */
multiline_comment|/* This makes some tests easier and quicker */
DECL|macro|T309
mdefine_line|#define T309&t;40000
DECL|macro|T310
mdefine_line|#define T310&t;30000
DECL|macro|T313
mdefine_line|#define T313&t;4000
DECL|macro|T318
mdefine_line|#define T318&t;4000
DECL|macro|T319
mdefine_line|#define T319&t;4000
multiline_comment|/*&n; * Message-Types&n; */
DECL|macro|MT_ALERTING
mdefine_line|#define MT_ALERTING&t;&t;0x01
DECL|macro|MT_CALL_PROCEEDING
mdefine_line|#define MT_CALL_PROCEEDING&t;0x02
DECL|macro|MT_CONNECT
mdefine_line|#define MT_CONNECT&t;&t;0x07
DECL|macro|MT_CONNECT_ACKNOWLEDGE
mdefine_line|#define MT_CONNECT_ACKNOWLEDGE&t;0x0f
DECL|macro|MT_PROGRESS
mdefine_line|#define MT_PROGRESS&t;&t;0x03
DECL|macro|MT_SETUP
mdefine_line|#define MT_SETUP&t;&t;0x05
DECL|macro|MT_SETUP_ACKNOWLEDGE
mdefine_line|#define MT_SETUP_ACKNOWLEDGE&t;0x0d
DECL|macro|MT_RESUME
mdefine_line|#define MT_RESUME&t;&t;0x26
DECL|macro|MT_RESUME_ACKNOWLEDGE
mdefine_line|#define MT_RESUME_ACKNOWLEDGE&t;0x2e
DECL|macro|MT_RESUME_REJECT
mdefine_line|#define MT_RESUME_REJECT&t;0x22
DECL|macro|MT_SUSPEND
mdefine_line|#define MT_SUSPEND&t;&t;0x25
DECL|macro|MT_SUSPEND_ACKNOWLEDGE
mdefine_line|#define MT_SUSPEND_ACKNOWLEDGE&t;0x2d
DECL|macro|MT_SUSPEND_REJECT
mdefine_line|#define MT_SUSPEND_REJECT&t;0x21
DECL|macro|MT_USER_INFORMATION
mdefine_line|#define MT_USER_INFORMATION&t;0x20
DECL|macro|MT_DISCONNECT
mdefine_line|#define MT_DISCONNECT&t;&t;0x45
DECL|macro|MT_RELEASE
mdefine_line|#define MT_RELEASE&t;&t;0x4d
DECL|macro|MT_RELEASE_COMPLETE
mdefine_line|#define MT_RELEASE_COMPLETE&t;0x5a
DECL|macro|MT_RESTART
mdefine_line|#define MT_RESTART&t;&t;0x46
DECL|macro|MT_RESTART_ACKNOWLEDGE
mdefine_line|#define MT_RESTART_ACKNOWLEDGE&t;0x4e
DECL|macro|MT_SEGMENT
mdefine_line|#define MT_SEGMENT&t;&t;0x60
DECL|macro|MT_CONGESTION_CONTROL
mdefine_line|#define MT_CONGESTION_CONTROL&t;0x79
DECL|macro|MT_INFORMATION
mdefine_line|#define MT_INFORMATION&t;&t;0x7b
DECL|macro|MT_FACILITY
mdefine_line|#define MT_FACILITY&t;&t;0x62
DECL|macro|MT_NOTIFY
mdefine_line|#define MT_NOTIFY&t;&t;0x6e
DECL|macro|MT_STATUS
mdefine_line|#define MT_STATUS&t;&t;0x7d
DECL|macro|MT_STATUS_ENQUIRY
mdefine_line|#define MT_STATUS_ENQUIRY&t;0x75
DECL|macro|IE_SEGMENT
mdefine_line|#define IE_SEGMENT&t;0x00
DECL|macro|IE_BEARER
mdefine_line|#define IE_BEARER&t;0x04
DECL|macro|IE_CAUSE
mdefine_line|#define IE_CAUSE&t;0x08
DECL|macro|IE_CALL_ID
mdefine_line|#define IE_CALL_ID&t;0x10
DECL|macro|IE_CALL_STATE
mdefine_line|#define IE_CALL_STATE&t;0x14
DECL|macro|IE_CHANNEL_ID
mdefine_line|#define IE_CHANNEL_ID&t;0x18
DECL|macro|IE_FACILITY
mdefine_line|#define IE_FACILITY&t;0x1c
DECL|macro|IE_PROGRESS
mdefine_line|#define IE_PROGRESS&t;0x1e
DECL|macro|IE_NET_FAC
mdefine_line|#define IE_NET_FAC&t;0x20
DECL|macro|IE_NOTIFY
mdefine_line|#define IE_NOTIFY&t;0x27
DECL|macro|IE_DISPLAY
mdefine_line|#define IE_DISPLAY&t;0x28
DECL|macro|IE_DATE
mdefine_line|#define IE_DATE&t;&t;0x29
DECL|macro|IE_KEYPAD
mdefine_line|#define IE_KEYPAD&t;0x2c
DECL|macro|IE_SIGNAL
mdefine_line|#define IE_SIGNAL&t;0x34
DECL|macro|IE_INFORATE
mdefine_line|#define IE_INFORATE&t;0x40
DECL|macro|IE_E2E_TDELAY
mdefine_line|#define IE_E2E_TDELAY&t;0x42
DECL|macro|IE_TDELAY_SEL
mdefine_line|#define IE_TDELAY_SEL&t;0x43
DECL|macro|IE_PACK_BINPARA
mdefine_line|#define IE_PACK_BINPARA&t;0x44
DECL|macro|IE_PACK_WINSIZE
mdefine_line|#define IE_PACK_WINSIZE&t;0x45
DECL|macro|IE_PACK_SIZE
mdefine_line|#define IE_PACK_SIZE&t;0x46
DECL|macro|IE_CUG
mdefine_line|#define IE_CUG&t;&t;0x47
DECL|macro|IE_REV_CHARGE
mdefine_line|#define&t;IE_REV_CHARGE&t;0x4a
DECL|macro|IE_CONNECT_PN
mdefine_line|#define IE_CONNECT_PN&t;0x4c
DECL|macro|IE_CONNECT_SUB
mdefine_line|#define IE_CONNECT_SUB&t;0x4d
DECL|macro|IE_CALLING_PN
mdefine_line|#define IE_CALLING_PN&t;0x6c
DECL|macro|IE_CALLING_SUB
mdefine_line|#define IE_CALLING_SUB&t;0x6d
DECL|macro|IE_CALLED_PN
mdefine_line|#define IE_CALLED_PN&t;0x70
DECL|macro|IE_CALLED_SUB
mdefine_line|#define IE_CALLED_SUB&t;0x71
DECL|macro|IE_REDIR_NR
mdefine_line|#define IE_REDIR_NR&t;0x74
DECL|macro|IE_TRANS_SEL
mdefine_line|#define IE_TRANS_SEL&t;0x78
DECL|macro|IE_RESTART_IND
mdefine_line|#define IE_RESTART_IND&t;0x79
DECL|macro|IE_LLC
mdefine_line|#define IE_LLC&t;&t;0x7c
DECL|macro|IE_HLC
mdefine_line|#define IE_HLC&t;&t;0x7d
DECL|macro|IE_USER_USER
mdefine_line|#define IE_USER_USER&t;0x7e
DECL|macro|IE_ESCAPE
mdefine_line|#define IE_ESCAPE&t;0x7f
DECL|macro|IE_SHIFT
mdefine_line|#define IE_SHIFT&t;0x90
DECL|macro|IE_MORE_DATA
mdefine_line|#define IE_MORE_DATA&t;0xa0
DECL|macro|IE_COMPLETE
mdefine_line|#define IE_COMPLETE&t;0xa1
DECL|macro|IE_CONGESTION
mdefine_line|#define IE_CONGESTION&t;0xb0
DECL|macro|IE_REPEAT
mdefine_line|#define IE_REPEAT&t;0xd0
DECL|macro|IE_MANDATORY
mdefine_line|#define IE_MANDATORY&t;0x0100
multiline_comment|/* mandatory not in every case */
DECL|macro|IE_MANDATORY_1
mdefine_line|#define IE_MANDATORY_1&t;0x0200
DECL|macro|ERR_IE_COMPREHENSION
mdefine_line|#define ERR_IE_COMPREHENSION&t; 1
DECL|macro|ERR_IE_UNRECOGNIZED
mdefine_line|#define ERR_IE_UNRECOGNIZED&t;-1
DECL|macro|ERR_IE_LENGTH
mdefine_line|#define ERR_IE_LENGTH&t;&t;-2
DECL|macro|ERR_IE_SEQUENCE
mdefine_line|#define ERR_IE_SEQUENCE&t;&t;-3
macro_line|#else /* only l3dss1_process */
multiline_comment|/* l3dss1 specific data in l3 process */
r_typedef
r_struct
DECL|member|invoke_id
(brace
r_int
r_char
id|invoke_id
suffix:semicolon
multiline_comment|/* used invoke id in remote ops, 0 = not active */
DECL|member|ll_id
id|ulong
id|ll_id
suffix:semicolon
multiline_comment|/* remebered ll id */
DECL|member|remote_operation
id|u_char
id|remote_operation
suffix:semicolon
multiline_comment|/* handled remote operation, 0 = not active */
DECL|member|proc
r_int
id|proc
suffix:semicolon
multiline_comment|/* rememered procedure */
DECL|member|remote_result
id|ulong
id|remote_result
suffix:semicolon
multiline_comment|/* result of remote operation for statcallb */
DECL|member|uus1_data
r_char
id|uus1_data
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* data send during alerting or disconnect */
DECL|typedef|dss1_proc_priv
)brace
id|dss1_proc_priv
suffix:semicolon
multiline_comment|/* l3dss1 specific data in protocol stack */
r_typedef
r_struct
DECL|member|last_invoke_id
(brace
r_int
r_char
id|last_invoke_id
suffix:semicolon
multiline_comment|/* last used value for invoking */
DECL|member|invoke_used
r_int
r_char
id|invoke_used
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 256 bits for 256 values */
DECL|typedef|dss1_stk_priv
)brace
id|dss1_stk_priv
suffix:semicolon
macro_line|#endif /* only l3dss1_process */
eof
