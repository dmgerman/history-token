macro_line|#ifndef _LMC_DEBUG_H_
DECL|macro|_LMC_DEBUG_H_
mdefine_line|#define _LMC_DEBUG_H_
macro_line|#ifdef DEBUG
macro_line|#ifdef LMC_PACKET_LOG
DECL|macro|LMC_CONSOLE_LOG
mdefine_line|#define LMC_CONSOLE_LOG(x,y,z) lmcConsoleLog((x), (y), (z))
macro_line|#else
DECL|macro|LMC_CONSOLE_LOG
mdefine_line|#define LMC_CONSOLE_LOG(x,y,z)
macro_line|#endif
macro_line|#else
DECL|macro|LMC_CONSOLE_LOG
mdefine_line|#define LMC_CONSOLE_LOG(x,y,z)
macro_line|#endif
multiline_comment|/* Debug --- Event log definitions --- */
multiline_comment|/* EVENTLOGSIZE*EVENTLOGARGS needs to be a power of 2 */
DECL|macro|LMC_EVENTLOGSIZE
mdefine_line|#define LMC_EVENTLOGSIZE 1024&t;/* number of events in eventlog */
DECL|macro|LMC_EVENTLOGARGS
mdefine_line|#define LMC_EVENTLOGARGS 4&t;&t;/* number of args for each event */
multiline_comment|/* event indicators */
DECL|macro|LMC_EVENT_XMT
mdefine_line|#define LMC_EVENT_XMT           1
DECL|macro|LMC_EVENT_XMTEND
mdefine_line|#define LMC_EVENT_XMTEND        2
DECL|macro|LMC_EVENT_XMTINT
mdefine_line|#define LMC_EVENT_XMTINT        3
DECL|macro|LMC_EVENT_RCVINT
mdefine_line|#define LMC_EVENT_RCVINT        4
DECL|macro|LMC_EVENT_RCVEND
mdefine_line|#define LMC_EVENT_RCVEND        5
DECL|macro|LMC_EVENT_INT
mdefine_line|#define LMC_EVENT_INT           6
DECL|macro|LMC_EVENT_XMTINTTMO
mdefine_line|#define LMC_EVENT_XMTINTTMO     7
DECL|macro|LMC_EVENT_XMTPRCTMO
mdefine_line|#define LMC_EVENT_XMTPRCTMO     8
DECL|macro|LMC_EVENT_INTEND
mdefine_line|#define LMC_EVENT_INTEND        9
DECL|macro|LMC_EVENT_RESET1
mdefine_line|#define LMC_EVENT_RESET1       10
DECL|macro|LMC_EVENT_RESET2
mdefine_line|#define LMC_EVENT_RESET2       11
DECL|macro|LMC_EVENT_FORCEDRESET
mdefine_line|#define LMC_EVENT_FORCEDRESET  12
DECL|macro|LMC_EVENT_WATCHDOG
mdefine_line|#define LMC_EVENT_WATCHDOG     13
DECL|macro|LMC_EVENT_BADPKTSURGE
mdefine_line|#define LMC_EVENT_BADPKTSURGE  14
DECL|macro|LMC_EVENT_TBUSY0
mdefine_line|#define LMC_EVENT_TBUSY0       15
DECL|macro|LMC_EVENT_TBUSY1
mdefine_line|#define LMC_EVENT_TBUSY1       16
macro_line|#ifdef DEBUG
r_extern
id|u_int32_t
id|lmcEventLogIndex
suffix:semicolon
r_extern
id|u_int32_t
id|lmcEventLogBuf
(braket
id|LMC_EVENTLOGSIZE
op_star
id|LMC_EVENTLOGARGS
)braket
suffix:semicolon
DECL|macro|LMC_EVENT_LOG
mdefine_line|#define LMC_EVENT_LOG(x, y, z) lmcEventLog((x), (y), (z))
macro_line|#else
DECL|macro|LMC_EVENT_LOG
mdefine_line|#define LMC_EVENT_LOG(x,y,z)
macro_line|#endif /* end ifdef _DBG_EVENTLOG */
r_void
id|lmcConsoleLog
c_func
(paren
r_char
op_star
id|type
comma
r_int
r_char
op_star
id|ucData
comma
r_int
id|iLen
)paren
suffix:semicolon
r_void
id|lmcEventLog
(paren
id|u_int32_t
id|EventNum
comma
id|u_int32_t
id|arg2
comma
id|u_int32_t
id|arg3
)paren
suffix:semicolon
r_inline
r_void
id|lmc_trace
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|msg
)paren
suffix:semicolon
macro_line|#endif
eof
