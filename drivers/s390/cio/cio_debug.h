macro_line|#ifndef CIO_DEBUG_H
DECL|macro|CIO_DEBUG_H
mdefine_line|#define CIO_DEBUG_H
macro_line|#include &lt;asm/debug.h&gt;
DECL|macro|CIO_TRACE_EVENT
mdefine_line|#define CIO_TRACE_EVENT(imp, txt) do { &bslash;&n;&t;&t;debug_text_event(cio_debug_trace_id, imp, txt); &bslash;&n;&t;} while (0)
DECL|macro|CIO_MSG_EVENT
mdefine_line|#define CIO_MSG_EVENT(imp, args...) do { &bslash;&n;&t;&t;debug_sprintf_event(cio_debug_msg_id, imp , ##args); &bslash;&n;&t;} while (0)
DECL|macro|CIO_CRW_EVENT
mdefine_line|#define CIO_CRW_EVENT(imp, args...) do { &bslash;&n;&t;&t;debug_sprintf_event(cio_debug_crw_id, imp , ##args); &bslash;&n;&t;} while (0)
DECL|macro|CIO_HEX_EVENT
mdefine_line|#define CIO_HEX_EVENT(imp, args...) do { &bslash;&n;                debug_event(cio_debug_trace_id, imp, ##args); &bslash;&n;        } while (0)
DECL|macro|CIO_DEBUG
mdefine_line|#define CIO_DEBUG(printk_level,event_level,msg...) ({ &bslash;&n;&t;if (cio_show_msg) printk(printk_level msg); &bslash;&n;&t;CIO_MSG_EVENT (event_level, msg); &bslash;&n;})
multiline_comment|/* for use of debug feature */
r_extern
id|debug_info_t
op_star
id|cio_debug_msg_id
suffix:semicolon
r_extern
id|debug_info_t
op_star
id|cio_debug_trace_id
suffix:semicolon
r_extern
id|debug_info_t
op_star
id|cio_debug_crw_id
suffix:semicolon
macro_line|#endif
eof
