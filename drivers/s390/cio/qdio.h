macro_line|#ifndef _CIO_QDIO_H
DECL|macro|_CIO_QDIO_H
mdefine_line|#define _CIO_QDIO_H
DECL|macro|VERSION_CIO_QDIO_H
mdefine_line|#define VERSION_CIO_QDIO_H &quot;$Revision: 1.18 $&quot;
singleline_comment|//#define QDIO_DBF_LIKE_HELL
macro_line|#ifdef QDIO_DBF_LIKE_HELL
DECL|macro|QDIO_VERBOSE_LEVEL
mdefine_line|#define QDIO_VERBOSE_LEVEL 9
macro_line|#else /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_VERBOSE_LEVEL
mdefine_line|#define QDIO_VERBOSE_LEVEL 5
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_USE_PROCESSING_STATE
mdefine_line|#define QDIO_USE_PROCESSING_STATE
macro_line|#ifdef CONFIG_QDIO_PERF_STATS
DECL|macro|QDIO_PERFORMANCE_STATS
mdefine_line|#define QDIO_PERFORMANCE_STATS
macro_line|#endif /* CONFIG_QDIO_PERF_STATS */
DECL|macro|QDIO_MINIMAL_BH_RELIEF_TIME
mdefine_line|#define QDIO_MINIMAL_BH_RELIEF_TIME 16
DECL|macro|QDIO_TIMER_POLL_VALUE
mdefine_line|#define QDIO_TIMER_POLL_VALUE 1
DECL|macro|IQDIO_TIMER_POLL_VALUE
mdefine_line|#define IQDIO_TIMER_POLL_VALUE 1
multiline_comment|/*&n; * unfortunately this can&squot;t be (QDIO_MAX_BUFFERS_PER_Q*4/3) or so -- as&n; * we never know, whether we&squot;ll get initiative again, e.g. to give the&n; * transmit skb&squot;s back to the stack, however the stack may be waiting for&n; * them... therefore we define 4 as threshold to start polling (which&n; * will stop as soon as the asynchronous queue catches up)&n; * btw, this only applies to the asynchronous HiperSockets queue&n; */
DECL|macro|IQDIO_FILL_LEVEL_TO_POLL
mdefine_line|#define IQDIO_FILL_LEVEL_TO_POLL 4
DECL|macro|TIQDIO_THININT_ISC
mdefine_line|#define TIQDIO_THININT_ISC 3
DECL|macro|TIQDIO_DELAY_TARGET
mdefine_line|#define TIQDIO_DELAY_TARGET 0
DECL|macro|QDIO_BUSY_BIT_PATIENCE
mdefine_line|#define QDIO_BUSY_BIT_PATIENCE 2000 /* in microsecs */
DECL|macro|IQDIO_GLOBAL_LAPS
mdefine_line|#define IQDIO_GLOBAL_LAPS 2 /* GLOBAL_LAPS are not used as we */
DECL|macro|IQDIO_GLOBAL_LAPS_INT
mdefine_line|#define IQDIO_GLOBAL_LAPS_INT 1 /* don&squot;t global summary */
DECL|macro|IQDIO_LOCAL_LAPS
mdefine_line|#define IQDIO_LOCAL_LAPS 4
DECL|macro|IQDIO_LOCAL_LAPS_INT
mdefine_line|#define IQDIO_LOCAL_LAPS_INT 1
DECL|macro|IQDIO_GLOBAL_SUMMARY_CC_MASK
mdefine_line|#define IQDIO_GLOBAL_SUMMARY_CC_MASK 2
multiline_comment|/*#define IQDIO_IQDC_INT_PARM 0x1234*/
DECL|macro|QDIO_Q_LAPS
mdefine_line|#define QDIO_Q_LAPS 5
DECL|macro|QDIO_STORAGE_KEY
mdefine_line|#define QDIO_STORAGE_KEY 0
DECL|macro|L2_CACHELINE_SIZE
mdefine_line|#define L2_CACHELINE_SIZE 256
DECL|macro|INDICATORS_PER_CACHELINE
mdefine_line|#define INDICATORS_PER_CACHELINE (L2_CACHELINE_SIZE/sizeof(__u32))
DECL|macro|QDIO_PERF
mdefine_line|#define QDIO_PERF &quot;qdio_perf&quot;
multiline_comment|/* must be a power of 2 */
multiline_comment|/*#define QDIO_STATS_NUMBER 4&n;&n;#define QDIO_STATS_CLASSES 2&n;#define QDIO_STATS_COUNT_NEEDED 2*/
DECL|macro|QDIO_NO_USE_COUNT_TIME
mdefine_line|#define QDIO_NO_USE_COUNT_TIME 10
DECL|macro|QDIO_NO_USE_COUNT_TIMEOUT
mdefine_line|#define QDIO_NO_USE_COUNT_TIMEOUT 1000 /* wait for 1 sec on each q before&n;&t;&t;&t;&t;&t;  exiting without having use_count&n;&t;&t;&t;&t;&t;  of the queue to 0 */
DECL|macro|QDIO_ESTABLISH_TIMEOUT
mdefine_line|#define QDIO_ESTABLISH_TIMEOUT 1000
DECL|macro|QDIO_ACTIVATE_TIMEOUT
mdefine_line|#define QDIO_ACTIVATE_TIMEOUT 5
DECL|macro|QDIO_CLEANUP_CLEAR_TIMEOUT
mdefine_line|#define QDIO_CLEANUP_CLEAR_TIMEOUT 20000
DECL|macro|QDIO_CLEANUP_HALT_TIMEOUT
mdefine_line|#define QDIO_CLEANUP_HALT_TIMEOUT 10000
DECL|enum|qdio_irq_states
r_enum
id|qdio_irq_states
(brace
DECL|enumerator|QDIO_IRQ_STATE_INACTIVE
id|QDIO_IRQ_STATE_INACTIVE
comma
DECL|enumerator|QDIO_IRQ_STATE_ESTABLISHED
id|QDIO_IRQ_STATE_ESTABLISHED
comma
DECL|enumerator|QDIO_IRQ_STATE_ACTIVE
id|QDIO_IRQ_STATE_ACTIVE
comma
DECL|enumerator|QDIO_IRQ_STATE_STOPPED
id|QDIO_IRQ_STATE_STOPPED
comma
DECL|enumerator|QDIO_IRQ_STATE_CLEANUP
id|QDIO_IRQ_STATE_CLEANUP
comma
DECL|enumerator|QDIO_IRQ_STATE_ERR
id|QDIO_IRQ_STATE_ERR
comma
DECL|enumerator|NR_QDIO_IRQ_STATES
id|NR_QDIO_IRQ_STATES
comma
)brace
suffix:semicolon
multiline_comment|/* used as intparm in do_IO: */
DECL|macro|QDIO_DOING_SENSEID
mdefine_line|#define QDIO_DOING_SENSEID 0
DECL|macro|QDIO_DOING_ESTABLISH
mdefine_line|#define QDIO_DOING_ESTABLISH 1
DECL|macro|QDIO_DOING_ACTIVATE
mdefine_line|#define QDIO_DOING_ACTIVATE 2
DECL|macro|QDIO_DOING_CLEANUP
mdefine_line|#define QDIO_DOING_CLEANUP 3
multiline_comment|/************************* DEBUG FACILITY STUFF *********************/
DECL|macro|QDIO_DBF_HEX
mdefine_line|#define QDIO_DBF_HEX(ex,name,level,addr,len) &bslash;&n;&t;do { &bslash;&n;&t;if (ex) &bslash;&n;&t;&t;debug_exception(qdio_dbf_##name,level,(void*)(addr),len); &bslash;&n;&t;else &bslash;&n;&t;&t;debug_event(qdio_dbf_##name,level,(void*)(addr),len); &bslash;&n;&t;} while (0)
DECL|macro|QDIO_DBF_TEXT
mdefine_line|#define QDIO_DBF_TEXT(ex,name,level,text) &bslash;&n;&t;do { &bslash;&n;&t;if (ex) &bslash;&n;&t;&t;debug_text_exception(qdio_dbf_##name,level,text); &bslash;&n;&t;else &bslash;&n;&t;&t;debug_text_event(qdio_dbf_##name,level,text); &bslash;&n;&t;} while (0)
DECL|macro|QDIO_DBF_HEX0
mdefine_line|#define QDIO_DBF_HEX0(ex,name,addr,len) QDIO_DBF_HEX(ex,name,0,addr,len)
DECL|macro|QDIO_DBF_HEX1
mdefine_line|#define QDIO_DBF_HEX1(ex,name,addr,len) QDIO_DBF_HEX(ex,name,1,addr,len)
DECL|macro|QDIO_DBF_HEX2
mdefine_line|#define QDIO_DBF_HEX2(ex,name,addr,len) QDIO_DBF_HEX(ex,name,2,addr,len)
macro_line|#ifdef QDIO_DBF_LIKE_HELL
DECL|macro|QDIO_DBF_HEX3
mdefine_line|#define QDIO_DBF_HEX3(ex,name,addr,len) QDIO_DBF_HEX(ex,name,3,addr,len)
DECL|macro|QDIO_DBF_HEX4
mdefine_line|#define QDIO_DBF_HEX4(ex,name,addr,len) QDIO_DBF_HEX(ex,name,4,addr,len)
DECL|macro|QDIO_DBF_HEX5
mdefine_line|#define QDIO_DBF_HEX5(ex,name,addr,len) QDIO_DBF_HEX(ex,name,5,addr,len)
DECL|macro|QDIO_DBF_HEX6
mdefine_line|#define QDIO_DBF_HEX6(ex,name,addr,len) QDIO_DBF_HEX(ex,name,6,addr,len)
macro_line|#else /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_HEX3
mdefine_line|#define QDIO_DBF_HEX3(ex,name,addr,len) do {} while (0)
DECL|macro|QDIO_DBF_HEX4
mdefine_line|#define QDIO_DBF_HEX4(ex,name,addr,len) do {} while (0)
DECL|macro|QDIO_DBF_HEX5
mdefine_line|#define QDIO_DBF_HEX5(ex,name,addr,len) do {} while (0)
DECL|macro|QDIO_DBF_HEX6
mdefine_line|#define QDIO_DBF_HEX6(ex,name,addr,len) do {} while (0)
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_TEXT0
mdefine_line|#define QDIO_DBF_TEXT0(ex,name,text) QDIO_DBF_TEXT(ex,name,0,text)
DECL|macro|QDIO_DBF_TEXT1
mdefine_line|#define QDIO_DBF_TEXT1(ex,name,text) QDIO_DBF_TEXT(ex,name,1,text)
DECL|macro|QDIO_DBF_TEXT2
mdefine_line|#define QDIO_DBF_TEXT2(ex,name,text) QDIO_DBF_TEXT(ex,name,2,text)
macro_line|#ifdef QDIO_DBF_LIKE_HELL
DECL|macro|QDIO_DBF_TEXT3
mdefine_line|#define QDIO_DBF_TEXT3(ex,name,text) QDIO_DBF_TEXT(ex,name,3,text)
DECL|macro|QDIO_DBF_TEXT4
mdefine_line|#define QDIO_DBF_TEXT4(ex,name,text) QDIO_DBF_TEXT(ex,name,4,text)
DECL|macro|QDIO_DBF_TEXT5
mdefine_line|#define QDIO_DBF_TEXT5(ex,name,text) QDIO_DBF_TEXT(ex,name,5,text)
DECL|macro|QDIO_DBF_TEXT6
mdefine_line|#define QDIO_DBF_TEXT6(ex,name,text) QDIO_DBF_TEXT(ex,name,6,text)
macro_line|#else /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_TEXT3
mdefine_line|#define QDIO_DBF_TEXT3(ex,name,text) do {} while (0)
DECL|macro|QDIO_DBF_TEXT4
mdefine_line|#define QDIO_DBF_TEXT4(ex,name,text) do {} while (0)
DECL|macro|QDIO_DBF_TEXT5
mdefine_line|#define QDIO_DBF_TEXT5(ex,name,text) do {} while (0)
DECL|macro|QDIO_DBF_TEXT6
mdefine_line|#define QDIO_DBF_TEXT6(ex,name,text) do {} while (0)
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_SETUP_NAME
mdefine_line|#define QDIO_DBF_SETUP_NAME &quot;qdio_setup&quot;
DECL|macro|QDIO_DBF_SETUP_LEN
mdefine_line|#define QDIO_DBF_SETUP_LEN 8
DECL|macro|QDIO_DBF_SETUP_INDEX
mdefine_line|#define QDIO_DBF_SETUP_INDEX 2
DECL|macro|QDIO_DBF_SETUP_NR_AREAS
mdefine_line|#define QDIO_DBF_SETUP_NR_AREAS 1
macro_line|#ifdef QDIO_DBF_LIKE_HELL
DECL|macro|QDIO_DBF_SETUP_LEVEL
mdefine_line|#define QDIO_DBF_SETUP_LEVEL 6
macro_line|#else /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_SETUP_LEVEL
mdefine_line|#define QDIO_DBF_SETUP_LEVEL 2
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_SBAL_NAME
mdefine_line|#define QDIO_DBF_SBAL_NAME &quot;qdio_labs&quot; /* sbal */
DECL|macro|QDIO_DBF_SBAL_LEN
mdefine_line|#define QDIO_DBF_SBAL_LEN 256
DECL|macro|QDIO_DBF_SBAL_INDEX
mdefine_line|#define QDIO_DBF_SBAL_INDEX 2
DECL|macro|QDIO_DBF_SBAL_NR_AREAS
mdefine_line|#define QDIO_DBF_SBAL_NR_AREAS 2
macro_line|#ifdef QDIO_DBF_LIKE_HELL
DECL|macro|QDIO_DBF_SBAL_LEVEL
mdefine_line|#define QDIO_DBF_SBAL_LEVEL 6
macro_line|#else /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_SBAL_LEVEL
mdefine_line|#define QDIO_DBF_SBAL_LEVEL 2
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_TRACE_NAME
mdefine_line|#define QDIO_DBF_TRACE_NAME &quot;qdio_trace&quot;
DECL|macro|QDIO_DBF_TRACE_LEN
mdefine_line|#define QDIO_DBF_TRACE_LEN 8
DECL|macro|QDIO_DBF_TRACE_NR_AREAS
mdefine_line|#define QDIO_DBF_TRACE_NR_AREAS 2
macro_line|#ifdef QDIO_DBF_LIKE_HELL
DECL|macro|QDIO_DBF_TRACE_INDEX
mdefine_line|#define QDIO_DBF_TRACE_INDEX 4
DECL|macro|QDIO_DBF_TRACE_LEVEL
mdefine_line|#define QDIO_DBF_TRACE_LEVEL 4 /* -------- could be even more verbose here */
macro_line|#else /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_TRACE_INDEX
mdefine_line|#define QDIO_DBF_TRACE_INDEX 2
DECL|macro|QDIO_DBF_TRACE_LEVEL
mdefine_line|#define QDIO_DBF_TRACE_LEVEL 2
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_SENSE_NAME
mdefine_line|#define QDIO_DBF_SENSE_NAME &quot;qdio_sense&quot;
DECL|macro|QDIO_DBF_SENSE_LEN
mdefine_line|#define QDIO_DBF_SENSE_LEN 64
DECL|macro|QDIO_DBF_SENSE_INDEX
mdefine_line|#define QDIO_DBF_SENSE_INDEX 1
DECL|macro|QDIO_DBF_SENSE_NR_AREAS
mdefine_line|#define QDIO_DBF_SENSE_NR_AREAS 1
macro_line|#ifdef QDIO_DBF_LIKE_HELL
DECL|macro|QDIO_DBF_SENSE_LEVEL
mdefine_line|#define QDIO_DBF_SENSE_LEVEL 6
macro_line|#else /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_DBF_SENSE_LEVEL
mdefine_line|#define QDIO_DBF_SENSE_LEVEL 2
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
macro_line|#ifdef QDIO_DBF_LIKE_HELL
DECL|macro|QDIO_TRACE_QTYPE
mdefine_line|#define QDIO_TRACE_QTYPE QDIO_ZFCP_QFMT
DECL|macro|QDIO_DBF_SLSB_OUT_NAME
mdefine_line|#define QDIO_DBF_SLSB_OUT_NAME &quot;qdio_slsb_out&quot;
DECL|macro|QDIO_DBF_SLSB_OUT_LEN
mdefine_line|#define QDIO_DBF_SLSB_OUT_LEN QDIO_MAX_BUFFERS_PER_Q
DECL|macro|QDIO_DBF_SLSB_OUT_INDEX
mdefine_line|#define QDIO_DBF_SLSB_OUT_INDEX 8
DECL|macro|QDIO_DBF_SLSB_OUT_NR_AREAS
mdefine_line|#define QDIO_DBF_SLSB_OUT_NR_AREAS 1
DECL|macro|QDIO_DBF_SLSB_OUT_LEVEL
mdefine_line|#define QDIO_DBF_SLSB_OUT_LEVEL 6
DECL|macro|QDIO_DBF_SLSB_IN_NAME
mdefine_line|#define QDIO_DBF_SLSB_IN_NAME &quot;qdio_slsb_in&quot;
DECL|macro|QDIO_DBF_SLSB_IN_LEN
mdefine_line|#define QDIO_DBF_SLSB_IN_LEN QDIO_MAX_BUFFERS_PER_Q
DECL|macro|QDIO_DBF_SLSB_IN_INDEX
mdefine_line|#define QDIO_DBF_SLSB_IN_INDEX 8
DECL|macro|QDIO_DBF_SLSB_IN_NR_AREAS
mdefine_line|#define QDIO_DBF_SLSB_IN_NR_AREAS 1
DECL|macro|QDIO_DBF_SLSB_IN_LEVEL
mdefine_line|#define QDIO_DBF_SLSB_IN_LEVEL 6
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
DECL|macro|QDIO_PRINTK_HEADER
mdefine_line|#define QDIO_PRINTK_HEADER QDIO_NAME &quot;: &quot;
macro_line|#if QDIO_VERBOSE_LEVEL&gt;8
DECL|macro|QDIO_PRINT_STUPID
mdefine_line|#define QDIO_PRINT_STUPID(x...) printk( KERN_DEBUG QDIO_PRINTK_HEADER x)
macro_line|#else
DECL|macro|QDIO_PRINT_STUPID
mdefine_line|#define QDIO_PRINT_STUPID(x...)
macro_line|#endif
macro_line|#if QDIO_VERBOSE_LEVEL&gt;7
DECL|macro|QDIO_PRINT_ALL
mdefine_line|#define QDIO_PRINT_ALL(x...) printk( QDIO_PRINTK_HEADER x)
macro_line|#else
DECL|macro|QDIO_PRINT_ALL
mdefine_line|#define QDIO_PRINT_ALL(x...)
macro_line|#endif
macro_line|#if QDIO_VERBOSE_LEVEL&gt;6
DECL|macro|QDIO_PRINT_INFO
mdefine_line|#define QDIO_PRINT_INFO(x...) printk( QDIO_PRINTK_HEADER x)
macro_line|#else
DECL|macro|QDIO_PRINT_INFO
mdefine_line|#define QDIO_PRINT_INFO(x...)
macro_line|#endif
macro_line|#if QDIO_VERBOSE_LEVEL&gt;5
DECL|macro|QDIO_PRINT_WARN
mdefine_line|#define QDIO_PRINT_WARN(x...) printk( QDIO_PRINTK_HEADER x)
macro_line|#else
DECL|macro|QDIO_PRINT_WARN
mdefine_line|#define QDIO_PRINT_WARN(x...)
macro_line|#endif
macro_line|#if QDIO_VERBOSE_LEVEL&gt;4
DECL|macro|QDIO_PRINT_ERR
mdefine_line|#define QDIO_PRINT_ERR(x...) printk( QDIO_PRINTK_HEADER x)
macro_line|#else
DECL|macro|QDIO_PRINT_ERR
mdefine_line|#define QDIO_PRINT_ERR(x...)
macro_line|#endif
macro_line|#if QDIO_VERBOSE_LEVEL&gt;3
DECL|macro|QDIO_PRINT_CRIT
mdefine_line|#define QDIO_PRINT_CRIT(x...) printk( QDIO_PRINTK_HEADER x)
macro_line|#else
DECL|macro|QDIO_PRINT_CRIT
mdefine_line|#define QDIO_PRINT_CRIT(x...)
macro_line|#endif
macro_line|#if QDIO_VERBOSE_LEVEL&gt;2
DECL|macro|QDIO_PRINT_ALERT
mdefine_line|#define QDIO_PRINT_ALERT(x...) printk( QDIO_PRINTK_HEADER x)
macro_line|#else
DECL|macro|QDIO_PRINT_ALERT
mdefine_line|#define QDIO_PRINT_ALERT(x...)
macro_line|#endif
macro_line|#if QDIO_VERBOSE_LEVEL&gt;1
DECL|macro|QDIO_PRINT_EMERG
mdefine_line|#define QDIO_PRINT_EMERG(x...) printk( QDIO_PRINTK_HEADER x)
macro_line|#else
DECL|macro|QDIO_PRINT_EMERG
mdefine_line|#define QDIO_PRINT_EMERG(x...)
macro_line|#endif
DECL|macro|HEXDUMP16
mdefine_line|#define HEXDUMP16(importance,header,ptr) &bslash;&n;QDIO_PRINT_##importance(header &quot;%02x %02x %02x %02x  &quot; &bslash;&n;&t;&t;&t;&quot;%02x %02x %02x %02x  %02x %02x %02x %02x  &quot; &bslash;&n;&t;&t;&t;&quot;%02x %02x %02x %02x&bslash;n&quot;,*(((char*)ptr)), &bslash;&n;&t;&t;&t;*(((char*)ptr)+1),*(((char*)ptr)+2), &bslash;&n;&t;&t;&t;*(((char*)ptr)+3),*(((char*)ptr)+4), &bslash;&n;&t;&t;&t;*(((char*)ptr)+5),*(((char*)ptr)+6), &bslash;&n;&t;&t;&t;*(((char*)ptr)+7),*(((char*)ptr)+8), &bslash;&n;&t;&t;&t;*(((char*)ptr)+9),*(((char*)ptr)+10), &bslash;&n;&t;&t;&t;*(((char*)ptr)+11),*(((char*)ptr)+12), &bslash;&n;&t;&t;&t;*(((char*)ptr)+13),*(((char*)ptr)+14), &bslash;&n;&t;&t;&t;*(((char*)ptr)+15)); &bslash;&n;QDIO_PRINT_##importance(header &quot;%02x %02x %02x %02x  %02x %02x %02x %02x  &quot; &bslash;&n;&t;&t;&t;&quot;%02x %02x %02x %02x  %02x %02x %02x %02x&bslash;n&quot;, &bslash;&n;&t;&t;&t;*(((char*)ptr)+16),*(((char*)ptr)+17), &bslash;&n;&t;&t;&t;*(((char*)ptr)+18),*(((char*)ptr)+19), &bslash;&n;&t;&t;&t;*(((char*)ptr)+20),*(((char*)ptr)+21), &bslash;&n;&t;&t;&t;*(((char*)ptr)+22),*(((char*)ptr)+23), &bslash;&n;&t;&t;&t;*(((char*)ptr)+24),*(((char*)ptr)+25), &bslash;&n;&t;&t;&t;*(((char*)ptr)+26),*(((char*)ptr)+27), &bslash;&n;&t;&t;&t;*(((char*)ptr)+28),*(((char*)ptr)+29), &bslash;&n;&t;&t;&t;*(((char*)ptr)+30),*(((char*)ptr)+31));
multiline_comment|/****************** END OF DEBUG FACILITY STUFF *********************/
multiline_comment|/*&n; * Some instructions as assembly&n; */
r_extern
id|__inline__
r_int
DECL|function|do_siga_sync
id|do_siga_sync
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|mask1
comma
r_int
r_int
id|mask2
)paren
(brace
r_int
id|cc
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
id|asm
r_volatile
(paren
l_string|&quot;lhi&t;0,2&t;&bslash;n&bslash;t&quot;
l_string|&quot;lr&t;1,%1&t;&bslash;n&bslash;t&quot;
l_string|&quot;lr&t;2,%2&t;&bslash;n&bslash;t&quot;
l_string|&quot;lr&t;3,%3&t;&bslash;n&bslash;t&quot;
l_string|&quot;siga   0&t;&bslash;n&bslash;t&quot;
l_string|&quot;ipm&t;%0&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;%0,28&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|0x10000
op_or
id|irq
)paren
comma
l_string|&quot;d&quot;
(paren
id|mask1
)paren
comma
l_string|&quot;d&quot;
(paren
id|mask2
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|asm
r_volatile
(paren
l_string|&quot;lghi&t;0,2&t;&bslash;n&bslash;t&quot;
l_string|&quot;llgfr&t;1,%1&t;&bslash;n&bslash;t&quot;
l_string|&quot;llgfr&t;2,%2&t;&bslash;n&bslash;t&quot;
l_string|&quot;llgfr&t;3,%3&t;&bslash;n&bslash;t&quot;
l_string|&quot;siga   0&t;&bslash;n&bslash;t&quot;
l_string|&quot;ipm&t;%0&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;%0,28&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|0x10000
op_or
id|irq
)paren
comma
l_string|&quot;d&quot;
(paren
id|mask1
)paren
comma
l_string|&quot;d&quot;
(paren
id|mask2
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
r_return
id|cc
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|do_siga_input
id|do_siga_input
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|mask
)paren
(brace
r_int
id|cc
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
id|asm
r_volatile
(paren
l_string|&quot;lhi&t;0,1&t;&bslash;n&bslash;t&quot;
l_string|&quot;lr&t;1,%1&t;&bslash;n&bslash;t&quot;
l_string|&quot;lr&t;2,%2&t;&bslash;n&bslash;t&quot;
l_string|&quot;siga   0&t;&bslash;n&bslash;t&quot;
l_string|&quot;ipm&t;%0&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;%0,28&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|0x10000
op_or
id|irq
)paren
comma
l_string|&quot;d&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|asm
r_volatile
(paren
l_string|&quot;lghi&t;0,1&t;&bslash;n&bslash;t&quot;
l_string|&quot;llgfr&t;1,%1&t;&bslash;n&bslash;t&quot;
l_string|&quot;llgfr&t;2,%2&t;&bslash;n&bslash;t&quot;
l_string|&quot;siga   0&t;&bslash;n&bslash;t&quot;
l_string|&quot;ipm&t;%0&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;%0,28&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|0x10000
op_or
id|irq
)paren
comma
l_string|&quot;d&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
r_return
id|cc
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|do_siga_output
id|do_siga_output
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|mask
comma
id|__u32
op_star
id|bb
)paren
(brace
r_int
id|cc
suffix:semicolon
id|__u32
id|busy_bit
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
id|asm
r_volatile
(paren
l_string|&quot;lhi&t;0,0&t;&bslash;n&bslash;t&quot;
l_string|&quot;lr&t;1,%2&t;&bslash;n&bslash;t&quot;
l_string|&quot;lr&t;2,%3&t;&bslash;n&bslash;t&quot;
l_string|&quot;siga&t;0&t;&bslash;n&bslash;t&quot;
l_string|&quot;0:&quot;
l_string|&quot;ipm&t;%0&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;%0,28&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;0,31&t;&bslash;n&bslash;t&quot;
l_string|&quot;lr&t;%1,0&t;&bslash;n&bslash;t&quot;
l_string|&quot;1:&t;&bslash;n&bslash;t&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;2:&t;&bslash;n&bslash;t&quot;
l_string|&quot;lhi&t;%0,%4&t;&bslash;n&bslash;t&quot;
l_string|&quot;bras&t;1,3f&t;&bslash;n&bslash;t&quot;
l_string|&quot;.long 1b&t;&bslash;n&bslash;t&quot;
l_string|&quot;3:&t;&bslash;n&bslash;t&quot;
l_string|&quot;l&t;1,0(1)&t;&bslash;n&bslash;t&quot;
l_string|&quot;br&t;1&t;&bslash;n&bslash;t&quot;
l_string|&quot;.previous&t;&bslash;n&bslash;t&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;.align 4&t;&bslash;n&bslash;t&quot;
l_string|&quot;.long&t;0b,2b&t;&bslash;n&bslash;t&quot;
l_string|&quot;.previous&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
comma
l_string|&quot;=d&quot;
(paren
id|busy_bit
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|0x10000
op_or
id|irq
)paren
comma
l_string|&quot;d&quot;
(paren
id|mask
)paren
comma
l_string|&quot;i&quot;
(paren
id|QDIO_SIGA_ERROR_ACCESS_EXCEPTION
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|asm
r_volatile
(paren
l_string|&quot;lghi&t;0,0&t;&bslash;n&bslash;t&quot;
l_string|&quot;llgfr&t;1,%2&t;&bslash;n&bslash;t&quot;
l_string|&quot;llgfr&t;2,%3&t;&bslash;n&bslash;t&quot;
l_string|&quot;siga&t;0&t;&bslash;n&bslash;t&quot;
l_string|&quot;0:&quot;
l_string|&quot;ipm&t;%0&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;%0,28&t;&bslash;n&bslash;t&quot;
l_string|&quot;srl&t;0,31&t;&bslash;n&bslash;t&quot;
l_string|&quot;llgfr&t;%1,0&t;&bslash;n&bslash;t&quot;
l_string|&quot;1:&t;&bslash;n&bslash;t&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;lghi&t;%0,%4&t;&bslash;n&bslash;t&quot;
l_string|&quot;jg&t;1b&t;&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;.align 8&t;&bslash;n&bslash;t&quot;
l_string|&quot;.quad&t;0b,1b&t;&bslash;n&bslash;t&quot;
l_string|&quot;.previous&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
comma
l_string|&quot;=d&quot;
(paren
id|busy_bit
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|0x10000
op_or
id|irq
)paren
comma
l_string|&quot;d&quot;
(paren
id|mask
)paren
comma
l_string|&quot;i&quot;
(paren
id|QDIO_SIGA_ERROR_ACCESS_EXCEPTION
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
(paren
op_star
id|bb
)paren
op_assign
id|busy_bit
suffix:semicolon
r_return
id|cc
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
DECL|function|do_clear_global_summary
id|do_clear_global_summary
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|time
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
id|asm
r_volatile
(paren
l_string|&quot;lhi&t;1,3&t;&bslash;n&bslash;t&quot;
l_string|&quot;.insn&t;rre,0xb2650000,2,0&t;&bslash;n&bslash;t&quot;
l_string|&quot;lr&t;%0,3&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|time
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|asm
r_volatile
(paren
l_string|&quot;lghi&t;1,3&t;&bslash;n&bslash;t&quot;
l_string|&quot;.insn&t;rre,0xb2650000,2,0&t;&bslash;n&bslash;t&quot;
l_string|&quot;lgr&t;%0,3&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|time
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
r_return
id|time
suffix:semicolon
)brace
multiline_comment|/*&n; * QDIO device commands returned by extended Sense-ID&n; */
DECL|macro|DEFAULT_ESTABLISH_QS_CMD
mdefine_line|#define DEFAULT_ESTABLISH_QS_CMD 0x1b
DECL|macro|DEFAULT_ESTABLISH_QS_COUNT
mdefine_line|#define DEFAULT_ESTABLISH_QS_COUNT 0x1000
DECL|macro|DEFAULT_ACTIVATE_QS_CMD
mdefine_line|#define DEFAULT_ACTIVATE_QS_CMD 0x1f
DECL|macro|DEFAULT_ACTIVATE_QS_COUNT
mdefine_line|#define DEFAULT_ACTIVATE_QS_COUNT 0
multiline_comment|/*&n; * additional CIWs returned by extended Sense-ID&n; */
DECL|macro|CIW_TYPE_EQUEUE
mdefine_line|#define CIW_TYPE_EQUEUE 0x3       /* establish QDIO queues */
DECL|macro|CIW_TYPE_AQUEUE
mdefine_line|#define CIW_TYPE_AQUEUE 0x4       /* activate QDIO queues */
DECL|macro|QDIO_CHSC_RESPONSE_CODE_OK
mdefine_line|#define QDIO_CHSC_RESPONSE_CODE_OK 1
multiline_comment|/* flags for st qdio sch data */
DECL|macro|CHSC_FLAG_QDIO_CAPABILITY
mdefine_line|#define CHSC_FLAG_QDIO_CAPABILITY 0x80
DECL|macro|CHSC_FLAG_VALIDITY
mdefine_line|#define CHSC_FLAG_VALIDITY 0x40
DECL|macro|CHSC_FLAG_SIGA_INPUT_NECESSARY
mdefine_line|#define CHSC_FLAG_SIGA_INPUT_NECESSARY 0x40
DECL|macro|CHSC_FLAG_SIGA_OUTPUT_NECESSARY
mdefine_line|#define CHSC_FLAG_SIGA_OUTPUT_NECESSARY 0x20
DECL|macro|CHSC_FLAG_SIGA_SYNC_NECESSARY
mdefine_line|#define CHSC_FLAG_SIGA_SYNC_NECESSARY 0x10
DECL|macro|CHSC_FLAG_SIGA_SYNC_DONE_ON_THININTS
mdefine_line|#define CHSC_FLAG_SIGA_SYNC_DONE_ON_THININTS 0x08
DECL|macro|CHSC_FLAG_SIGA_SYNC_DONE_ON_OUTB_PCIS
mdefine_line|#define CHSC_FLAG_SIGA_SYNC_DONE_ON_OUTB_PCIS 0x04
macro_line|#ifdef QDIO_PERFORMANCE_STATS
DECL|struct|qdio_perf_stats
r_struct
id|qdio_perf_stats
(brace
DECL|member|tl_runs
r_int
r_int
id|tl_runs
suffix:semicolon
DECL|member|siga_outs
r_int
r_int
id|siga_outs
suffix:semicolon
DECL|member|siga_ins
r_int
r_int
id|siga_ins
suffix:semicolon
DECL|member|siga_syncs
r_int
r_int
id|siga_syncs
suffix:semicolon
DECL|member|pcis
r_int
r_int
id|pcis
suffix:semicolon
DECL|member|thinints
r_int
r_int
id|thinints
suffix:semicolon
DECL|member|fast_reqs
r_int
r_int
id|fast_reqs
suffix:semicolon
DECL|member|start_time_outbound
id|__u64
id|start_time_outbound
suffix:semicolon
DECL|member|outbound_cnt
r_int
r_int
id|outbound_cnt
suffix:semicolon
DECL|member|outbound_time
r_int
r_int
id|outbound_time
suffix:semicolon
DECL|member|start_time_inbound
id|__u64
id|start_time_inbound
suffix:semicolon
DECL|member|inbound_cnt
r_int
r_int
id|inbound_cnt
suffix:semicolon
DECL|member|inbound_time
r_int
r_int
id|inbound_time
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* QDIO_PERFORMANCE_STATS */
DECL|macro|atomic_swap
mdefine_line|#define atomic_swap(a,b) xchg((int*)a.counter,b)
multiline_comment|/* unlikely as the later the better */
DECL|macro|SYNC_MEMORY
mdefine_line|#define SYNC_MEMORY if (unlikely(q-&gt;siga_sync)) qdio_siga_sync_q(q)
DECL|macro|SYNC_MEMORY_ALL
mdefine_line|#define SYNC_MEMORY_ALL if (unlikely(q-&gt;siga_sync)) &bslash;&n;&t;qdio_siga_sync(q,~0U,~0U)
DECL|macro|SYNC_MEMORY_ALL_OUTB
mdefine_line|#define SYNC_MEMORY_ALL_OUTB if (unlikely(q-&gt;siga_sync)) &bslash;&n;&t;qdio_siga_sync(q,~0U,0)
DECL|macro|NOW
mdefine_line|#define NOW qdio_get_micros()
DECL|macro|SAVE_TIMESTAMP
mdefine_line|#define SAVE_TIMESTAMP(q) q-&gt;timing.last_transfer_time=NOW
DECL|macro|GET_SAVED_TIMESTAMP
mdefine_line|#define GET_SAVED_TIMESTAMP(q) (q-&gt;timing.last_transfer_time)
DECL|macro|SAVE_FRONTIER
mdefine_line|#define SAVE_FRONTIER(q,val) q-&gt;last_move_ftc=val
DECL|macro|GET_SAVED_FRONTIER
mdefine_line|#define GET_SAVED_FRONTIER(q) (q-&gt;last_move_ftc)
DECL|macro|MY_MODULE_STRING
mdefine_line|#define MY_MODULE_STRING(x) #x
macro_line|#ifdef CONFIG_ARCH_S390X
DECL|macro|QDIO_GET_ADDR
mdefine_line|#define QDIO_GET_ADDR(x) ((__u32)(unsigned long)x)
macro_line|#else /* CONFIG_ARCH_S390X */
DECL|macro|QDIO_GET_ADDR
mdefine_line|#define QDIO_GET_ADDR(x) ((__u32)(long)x)
macro_line|#endif /* CONFIG_ARCH_S390X */
macro_line|#ifdef QDIO_DBF_LIKE_HELL 
DECL|macro|set_slsb
mdefine_line|#define set_slsb(x,y) &bslash;&n;  if(q-&gt;queue_type==QDIO_TRACE_QTYPE) { &bslash;&n;        if(q-&gt;is_input_q) { &bslash;&n;            QDIO_DBF_HEX2(0,slsb_in,&amp;q-&gt;slsb,QDIO_MAX_BUFFERS_PER_Q); &bslash;&n;        } else { &bslash;&n;            QDIO_DBF_HEX2(0,slsb_out,&amp;q-&gt;slsb,QDIO_MAX_BUFFERS_PER_Q); &bslash;&n;        } &bslash;&n;  } &bslash;&n;  qdio_set_slsb(x,y); &bslash;&n;  if(q-&gt;queue_type==QDIO_TRACE_QTYPE) { &bslash;&n;        if(q-&gt;is_input_q) { &bslash;&n;            QDIO_DBF_HEX2(0,slsb_in,&amp;q-&gt;slsb,QDIO_MAX_BUFFERS_PER_Q); &bslash;&n;        } else { &bslash;&n;            QDIO_DBF_HEX2(0,slsb_out,&amp;q-&gt;slsb,QDIO_MAX_BUFFERS_PER_Q); &bslash;&n;        } &bslash;&n;  }
macro_line|#else /* QDIO_DBF_LIKE_HELL */
DECL|macro|set_slsb
mdefine_line|#define set_slsb(x,y) qdio_set_slsb(x,y)
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
DECL|struct|qdio_q
r_struct
id|qdio_q
(brace
DECL|member|slsb
r_volatile
r_struct
id|slsb
id|slsb
suffix:semicolon
DECL|member|dev_st_chg_ind
id|__u32
op_star
r_volatile
id|dev_st_chg_ind
suffix:semicolon
DECL|member|is_input_q
r_int
id|is_input_q
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|cdev
r_struct
id|ccw_device
op_star
id|cdev
suffix:semicolon
DECL|member|is_iqdio_q
r_int
r_int
id|is_iqdio_q
suffix:semicolon
DECL|member|is_thinint_q
r_int
r_int
id|is_thinint_q
suffix:semicolon
multiline_comment|/* bit 0 means queue 0, bit 1 means queue 1, ... */
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|q_no
r_int
r_int
id|q_no
suffix:semicolon
DECL|member|handler
id|qdio_handler_t
(paren
op_star
id|handler
)paren
suffix:semicolon
multiline_comment|/* points to the next buffer to be checked for having&n;&t; * been processed by the card (outbound)&n;&t; * or to the next buffer the program should check for (inbound) */
DECL|member|first_to_check
r_volatile
r_int
id|first_to_check
suffix:semicolon
multiline_comment|/* and the last time it was: */
DECL|member|last_move_ftc
r_volatile
r_int
id|last_move_ftc
suffix:semicolon
DECL|member|number_of_buffers_used
id|atomic_t
id|number_of_buffers_used
suffix:semicolon
DECL|member|polling
id|atomic_t
id|polling
suffix:semicolon
DECL|member|siga_in
r_int
r_int
id|siga_in
suffix:semicolon
DECL|member|siga_out
r_int
r_int
id|siga_out
suffix:semicolon
DECL|member|siga_sync
r_int
r_int
id|siga_sync
suffix:semicolon
DECL|member|siga_sync_done_on_thinints
r_int
r_int
id|siga_sync_done_on_thinints
suffix:semicolon
DECL|member|siga_sync_done_on_outb_tis
r_int
r_int
id|siga_sync_done_on_outb_tis
suffix:semicolon
DECL|member|hydra_gives_outbound_pcis
r_int
r_int
id|hydra_gives_outbound_pcis
suffix:semicolon
multiline_comment|/* used to save beginning position when calling dd_handlers */
DECL|member|first_element_to_kick
r_int
id|first_element_to_kick
suffix:semicolon
DECL|member|use_count
id|atomic_t
id|use_count
suffix:semicolon
DECL|member|is_in_shutdown
id|atomic_t
id|is_in_shutdown
suffix:semicolon
DECL|member|irq_ptr
r_void
op_star
id|irq_ptr
suffix:semicolon
macro_line|#ifdef QDIO_USE_TIMERS_FOR_POLLING
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|timer_already_set
id|atomic_t
id|timer_already_set
suffix:semicolon
DECL|member|timer_lock
id|spinlock_t
id|timer_lock
suffix:semicolon
macro_line|#else /* QDIO_USE_TIMERS_FOR_POLLING */
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
macro_line|#endif /* QDIO_USE_TIMERS_FOR_POLLING */
DECL|member|state
r_enum
id|qdio_irq_states
id|state
suffix:semicolon
multiline_comment|/* used to store the error condition during a data transfer */
DECL|member|qdio_error
r_int
r_int
id|qdio_error
suffix:semicolon
DECL|member|siga_error
r_int
r_int
id|siga_error
suffix:semicolon
DECL|member|error_status_flags
r_int
r_int
id|error_status_flags
suffix:semicolon
multiline_comment|/* list of interesting queues */
DECL|member|list_next
r_volatile
r_struct
id|qdio_q
op_star
id|list_next
suffix:semicolon
DECL|member|list_prev
r_volatile
r_struct
id|qdio_q
op_star
id|list_prev
suffix:semicolon
DECL|member|slib
r_struct
id|slib
op_star
id|slib
suffix:semicolon
multiline_comment|/* a page is allocated under this pointer,&n;&t;&t;&t;      sl points into this page, offset PAGE_SIZE/2&n;&t;&t;&t;      (after slib) */
DECL|member|sl
r_struct
id|sl
op_star
id|sl
suffix:semicolon
DECL|member|sbal
r_volatile
r_struct
id|sbal
op_star
id|sbal
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|qdio_buffers
r_struct
id|qdio_buffer
op_star
id|qdio_buffers
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|int_parm
r_int
r_int
id|int_parm
suffix:semicolon
multiline_comment|/*struct {&n;&t;&t;int in_bh_check_limit;&n;&t;&t;int threshold;&n;&t;} threshold_classes[QDIO_STATS_CLASSES];*/
r_struct
(brace
multiline_comment|/* inbound: the time to stop polling&n;&t;&t;   outbound: the time to kick peer */
DECL|member|threshold
r_int
id|threshold
suffix:semicolon
multiline_comment|/* the real value */
multiline_comment|/* outbound: last time of do_QDIO&n;&t;&t;   inbound: last time of noticing incoming data */
multiline_comment|/*__u64 last_transfer_times[QDIO_STATS_NUMBER];&n;&t;&t;int last_transfer_index; */
DECL|member|last_transfer_time
id|__u64
id|last_transfer_time
suffix:semicolon
DECL|member|timing
)brace
id|timing
suffix:semicolon
DECL|member|queue_type
r_int
r_int
id|queue_type
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
suffix:semicolon
DECL|struct|qdio_irq
r_struct
id|qdio_irq
(brace
DECL|member|dev_st_chg_ind
id|__u32
op_star
r_volatile
id|dev_st_chg_ind
suffix:semicolon
DECL|member|int_parm
r_int
r_int
id|int_parm
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|is_iqdio_irq
r_int
r_int
id|is_iqdio_irq
suffix:semicolon
DECL|member|is_thinint_irq
r_int
r_int
id|is_thinint_irq
suffix:semicolon
DECL|member|hydra_gives_outbound_pcis
r_int
r_int
id|hydra_gives_outbound_pcis
suffix:semicolon
DECL|member|sync_done_on_outb_pcis
r_int
r_int
id|sync_done_on_outb_pcis
suffix:semicolon
DECL|member|state
r_enum
id|qdio_irq_states
id|state
suffix:semicolon
DECL|member|setting_up_sema
r_struct
id|semaphore
id|setting_up_sema
suffix:semicolon
DECL|member|no_input_qs
r_int
r_int
id|no_input_qs
suffix:semicolon
DECL|member|no_output_qs
r_int
r_int
id|no_output_qs
suffix:semicolon
DECL|member|qdioac
r_int
r_char
id|qdioac
suffix:semicolon
DECL|member|input_qs
r_struct
id|qdio_q
op_star
id|input_qs
(braket
id|QDIO_MAX_QUEUES_PER_IRQ
)braket
suffix:semicolon
DECL|member|output_qs
r_struct
id|qdio_q
op_star
id|output_qs
(braket
id|QDIO_MAX_QUEUES_PER_IRQ
)braket
suffix:semicolon
DECL|member|ccw
r_struct
id|ccw1
id|ccw
suffix:semicolon
DECL|member|qdr
r_struct
id|qdr
op_star
id|qdr
suffix:semicolon
DECL|member|equeue
r_struct
id|ciw
id|equeue
suffix:semicolon
DECL|member|aqueue
r_struct
id|ciw
id|aqueue
suffix:semicolon
DECL|member|qib
r_struct
id|qib
id|qib
suffix:semicolon
DECL|member|original_int_handler
r_void
(paren
op_star
id|original_int_handler
)paren
(paren
r_struct
id|ccw_device
op_star
comma
r_int
r_int
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
