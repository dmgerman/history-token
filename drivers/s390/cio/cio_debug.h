macro_line|#ifndef S390_DEBUG_H
DECL|macro|S390_DEBUG_H
mdefine_line|#define S390_DEBUG_H
DECL|macro|SANITY_CHECK
mdefine_line|#define SANITY_CHECK(irq) do { &bslash;&n;if (irq &gt; highest_subchannel || irq &lt; 0) &bslash;&n;&t;&t;return (-ENODEV); &bslash;&n;&t;if (ioinfo[irq] == INVALID_STORAGE_AREA) &bslash;&n;&t;&t;return (-ENODEV); &bslash;&n;        if (ioinfo[irq]-&gt;st) &bslash;&n;                return -ENODEV; &bslash;&n;&t;} while(0)
DECL|macro|CIO_TRACE_EVENT
mdefine_line|#define CIO_TRACE_EVENT(imp, txt) do { &bslash;&n;&t;if (cio_debug_initialized) &bslash;&n;&t;&t;debug_text_event(cio_debug_trace_id, &bslash;&n;&t;&t;&t;&t; imp, &bslash;&n;&t;&t;&t;&t; txt); &bslash;&n;        }while (0)
DECL|macro|CIO_MSG_EVENT
mdefine_line|#define CIO_MSG_EVENT(imp, args...) do { &bslash;&n;        if (cio_debug_initialized) &bslash;&n;                debug_sprintf_event(cio_debug_msg_id, &bslash;&n;                                    imp, &bslash;&n;                                    ##args); &bslash;&n;        } while (0)
DECL|macro|CIO_CRW_EVENT
mdefine_line|#define CIO_CRW_EVENT(imp, args...) do { &bslash;&n;        if (cio_debug_initialized) &bslash;&n;                debug_sprintf_event(cio_debug_crw_id, &bslash;&n;                                    imp, &bslash;&n;                                    ##args); &bslash;&n;        } while (0)
DECL|macro|CONFIG_DEBUG_IO
macro_line|#undef  CONFIG_DEBUG_IO
DECL|macro|CONFIG_DEBUG_CRW
mdefine_line|#define CONFIG_DEBUG_CRW
DECL|macro|CONFIG_DEBUG_CHSC
mdefine_line|#define CONFIG_DEBUG_CHSC
macro_line|#ifdef CONFIG_DEBUG_IO
DECL|macro|DBG
mdefine_line|#define DBG printk
macro_line|#else /* CONFIG_DEBUG_IO */
DECL|macro|DBG
mdefine_line|#define DBG(args,...)  do {} while (0) 
macro_line|#endif /* CONFIG_DEBUG_IO */
DECL|macro|CIO_DEBUG
mdefine_line|#define CIO_DEBUG(printk_level,event_level,msg...) ({&bslash;&n;&t;DBG(printk_level msg); &bslash;&n;&t;CIO_MSG_EVENT (event_level, msg); &bslash;&n;})
DECL|macro|CIO_DEBUG_IFMSG
mdefine_line|#define CIO_DEBUG_IFMSG(printk_level,event_level,msg...) ({&bslash;&n;&t;if (cio_show_msg) printk(printk_level msg); &bslash;&n;&t;CIO_MSG_EVENT (event_level, msg); &bslash;&n;})
DECL|macro|CIO_DEBUG_ALWAYS
mdefine_line|#define CIO_DEBUG_ALWAYS(printk_level,event_level,msg...) ({&bslash;&n;&t;printk(printk_level msg); &bslash;&n;&t;CIO_MSG_EVENT (event_level, msg); &bslash;&n;})
DECL|macro|CIO_DEBUG_NOCONS
mdefine_line|#define CIO_DEBUG_NOCONS(irq,printk_level,func,event_level,msg...) ({&bslash;&n;&t;if (irq != cons_dev) func(printk_level msg); &bslash;&n;&t;CIO_MSG_EVENT (event_level, msg); &bslash;&n;})
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
r_extern
r_int
id|cio_debug_initialized
suffix:semicolon
macro_line|#endif
eof
