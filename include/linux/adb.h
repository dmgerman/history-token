multiline_comment|/*&n; * Definitions for ADB (Apple Desktop Bus) support.&n; */
macro_line|#ifndef __ADB_H
DECL|macro|__ADB_H
mdefine_line|#define __ADB_H
multiline_comment|/* ADB commands */
DECL|macro|ADB_BUSRESET
mdefine_line|#define ADB_BUSRESET&t;&t;0
DECL|macro|ADB_FLUSH
mdefine_line|#define ADB_FLUSH(id)&t;&t;(0x01 | ((id) &lt;&lt; 4))
DECL|macro|ADB_WRITEREG
mdefine_line|#define ADB_WRITEREG(id, reg)&t;(0x08 | (reg) | ((id) &lt;&lt; 4))
DECL|macro|ADB_READREG
mdefine_line|#define ADB_READREG(id, reg)&t;(0x0C | (reg) | ((id) &lt;&lt; 4))
multiline_comment|/* ADB default device IDs (upper 4 bits of ADB command byte) */
DECL|macro|ADB_DONGLE
mdefine_line|#define ADB_DONGLE&t;1&t;/* &quot;software execution control&quot; devices */
DECL|macro|ADB_KEYBOARD
mdefine_line|#define ADB_KEYBOARD&t;2
DECL|macro|ADB_MOUSE
mdefine_line|#define ADB_MOUSE&t;3
DECL|macro|ADB_TABLET
mdefine_line|#define ADB_TABLET&t;4
DECL|macro|ADB_MODEM
mdefine_line|#define ADB_MODEM&t;5
DECL|macro|ADB_MISC
mdefine_line|#define ADB_MISC&t;7&t;/* maybe a monitor */
DECL|macro|ADB_RET_OK
mdefine_line|#define ADB_RET_OK&t;0
DECL|macro|ADB_RET_TIMEOUT
mdefine_line|#define ADB_RET_TIMEOUT&t;3
multiline_comment|/* The kind of ADB request. The controller may emulate some&n;   or all of those CUDA/PMU packet kinds */
DECL|macro|ADB_PACKET
mdefine_line|#define ADB_PACKET&t;0
DECL|macro|CUDA_PACKET
mdefine_line|#define CUDA_PACKET&t;1
DECL|macro|ERROR_PACKET
mdefine_line|#define ERROR_PACKET&t;2
DECL|macro|TIMER_PACKET
mdefine_line|#define TIMER_PACKET&t;3
DECL|macro|POWER_PACKET
mdefine_line|#define POWER_PACKET&t;4
DECL|macro|MACIIC_PACKET
mdefine_line|#define MACIIC_PACKET&t;5
DECL|macro|PMU_PACKET
mdefine_line|#define PMU_PACKET&t;6
DECL|macro|ADB_QUERY
mdefine_line|#define ADB_QUERY&t;7
multiline_comment|/* ADB queries */
multiline_comment|/* ADB_QUERY_GETDEVINFO&n; * Query ADB slot for device presence&n; * data[2] = id, rep[0] = orig addr, rep[1] = handler_id&n; */
DECL|macro|ADB_QUERY_GETDEVINFO
mdefine_line|#define ADB_QUERY_GETDEVINFO&t;1
macro_line|#ifdef __KERNEL__
DECL|struct|adb_request
r_struct
id|adb_request
(brace
DECL|member|data
r_int
r_char
id|data
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|nbytes
r_int
id|nbytes
suffix:semicolon
DECL|member|reply
r_int
r_char
id|reply
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|reply_len
r_int
id|reply_len
suffix:semicolon
DECL|member|reply_expected
r_int
r_char
id|reply_expected
suffix:semicolon
DECL|member|sent
r_int
r_char
id|sent
suffix:semicolon
DECL|member|complete
r_int
r_char
id|complete
suffix:semicolon
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|adb_request
op_star
)paren
suffix:semicolon
DECL|member|arg
r_void
op_star
id|arg
suffix:semicolon
DECL|member|next
r_struct
id|adb_request
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|adb_ids
r_struct
id|adb_ids
(brace
DECL|member|nids
r_int
id|nids
suffix:semicolon
DECL|member|id
r_int
r_char
id|id
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Structure which encapsulates a low-level ADB driver */
DECL|struct|adb_driver
r_struct
id|adb_driver
(brace
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|send_request
r_int
(paren
op_star
id|send_request
)paren
(paren
r_struct
id|adb_request
op_star
id|req
comma
r_int
id|sync
)paren
suffix:semicolon
DECL|member|autopoll
r_int
(paren
op_star
id|autopoll
)paren
(paren
r_int
id|devs
)paren
suffix:semicolon
DECL|member|poll
r_void
(paren
op_star
id|poll
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|reset_bus
r_int
(paren
op_star
id|reset_bus
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Values for adb_request flags */
DECL|macro|ADBREQ_REPLY
mdefine_line|#define ADBREQ_REPLY&t;1&t;/* expect reply */
DECL|macro|ADBREQ_SYNC
mdefine_line|#define ADBREQ_SYNC&t;2&t;/* poll until done */
DECL|macro|ADBREQ_NOSEND
mdefine_line|#define ADBREQ_NOSEND&t;4&t;/* build the request, but don&squot;t send it */
multiline_comment|/* Messages sent thru the client_list notifier. You should NOT stop&n;   the operation, at least not with this version */
DECL|enum|adb_message
r_enum
id|adb_message
(brace
DECL|enumerator|ADB_MSG_POWERDOWN
id|ADB_MSG_POWERDOWN
comma
multiline_comment|/* Currently called before sleep only */
DECL|enumerator|ADB_MSG_PRE_RESET
id|ADB_MSG_PRE_RESET
comma
multiline_comment|/* Called before resetting the bus */
DECL|enumerator|ADB_MSG_POST_RESET
id|ADB_MSG_POST_RESET
multiline_comment|/* Called after resetting the bus (re-do init &amp; register) */
)brace
suffix:semicolon
r_extern
r_struct
id|adb_driver
op_star
id|adb_controller
suffix:semicolon
r_extern
r_struct
id|notifier_block
op_star
id|adb_client_list
suffix:semicolon
r_int
id|adb_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|adb_request
op_star
)paren
comma
r_int
id|flags
comma
r_int
id|nbytes
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|adb_register
c_func
(paren
r_int
id|default_id
comma
r_int
id|handler_id
comma
r_struct
id|adb_ids
op_star
id|ids
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
r_char
op_star
comma
r_int
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
)paren
suffix:semicolon
r_int
id|adb_unregister
c_func
(paren
r_int
id|index
)paren
suffix:semicolon
r_void
id|adb_poll
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|adb_input
c_func
(paren
r_int
r_char
op_star
comma
r_int
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|adb_reset_bus
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|adb_try_handler_change
c_func
(paren
r_int
id|address
comma
r_int
id|new_id
)paren
suffix:semicolon
r_int
id|adb_get_infos
c_func
(paren
r_int
id|address
comma
r_int
op_star
id|original_address
comma
r_int
op_star
id|handler_id
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ADB_H */
eof
