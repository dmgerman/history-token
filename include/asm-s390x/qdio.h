multiline_comment|/*&n; * linux/include/asm/qdio.h&n; *&n; * Linux for S/390 QDIO base support, Hipersocket base support&n; * version 2&n; *&n; * Copyright 2000,2002 IBM Corporation&n; * Author(s): Utz Bacher &lt;utz.bacher@de.ibm.com&gt;&n; *&n; */
macro_line|#ifndef __QDIO_H__
DECL|macro|__QDIO_H__
mdefine_line|#define __QDIO_H__
DECL|macro|VERSION_QDIO_H
mdefine_line|#define VERSION_QDIO_H &quot;$Revision: 1.48 $&quot;
multiline_comment|/* note, that most of the typedef&squot;s are from ingo. */
macro_line|#include &lt;linux/interrupt.h&gt;
singleline_comment|//#define QDIO_DBF_LIKE_HELL
DECL|macro|QDIO_NAME
mdefine_line|#define QDIO_NAME &quot;qdio &quot;
DECL|macro|QDIO_VERBOSE_LEVEL
mdefine_line|#define QDIO_VERBOSE_LEVEL 9
macro_line|#ifndef CONFIG_ARCH_S390X
DECL|macro|QDIO_32_BIT
mdefine_line|#define QDIO_32_BIT
macro_line|#endif /* CONFIG_ARCH_S390X */
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
multiline_comment|/**** CONSTANTS, that are relied on without using these symbols *****/
DECL|macro|QDIO_MAX_QUEUES_PER_IRQ
mdefine_line|#define QDIO_MAX_QUEUES_PER_IRQ 32 /* used in width of unsigned int */
multiline_comment|/************************ END of CONSTANTS **************************/
DECL|macro|QDIO_MAX_BUFFERS_PER_Q
mdefine_line|#define QDIO_MAX_BUFFERS_PER_Q 128 /* must be a power of 2 (%x=&amp;(x-1)*/
DECL|macro|QDIO_BUF_ORDER
mdefine_line|#define QDIO_BUF_ORDER 7 /* 2**this == number of pages used for sbals in 1 q */
DECL|macro|QDIO_MAX_ELEMENTS_PER_BUFFER
mdefine_line|#define QDIO_MAX_ELEMENTS_PER_BUFFER 16
DECL|macro|SBAL_SIZE
mdefine_line|#define SBAL_SIZE 256
DECL|macro|IQDIO_FILL_LEVEL_TO_POLL
mdefine_line|#define IQDIO_FILL_LEVEL_TO_POLL (QDIO_MAX_BUFFERS_PER_Q*4/3)
DECL|macro|IQDIO_THININT_ISC
mdefine_line|#define IQDIO_THININT_ISC 3
DECL|macro|IQDIO_DELAY_TARGET
mdefine_line|#define IQDIO_DELAY_TARGET 0
DECL|macro|QDIO_BUSY_BIT_PATIENCE
mdefine_line|#define QDIO_BUSY_BIT_PATIENCE 2000 /* in microsecs */
DECL|macro|IQDIO_GLOBAL_LAPS
mdefine_line|#define IQDIO_GLOBAL_LAPS 2 /* GLOBAL_LAPS are not used as we */
DECL|macro|IQDIO_GLOBAL_LAPS_INT
mdefine_line|#define IQDIO_GLOBAL_LAPS_INT 1 /* dont global summary */
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
mdefine_line|#define QDIO_ACTIVATE_TIMEOUT 100
DECL|macro|QDIO_CLEANUP_CLEAR_TIMEOUT
mdefine_line|#define QDIO_CLEANUP_CLEAR_TIMEOUT 20000
DECL|macro|QDIO_CLEANUP_HALT_TIMEOUT
mdefine_line|#define QDIO_CLEANUP_HALT_TIMEOUT 10000
DECL|macro|QDIO_BH
mdefine_line|#define QDIO_BH AURORA_BH
DECL|macro|QDIO_IRQ_BUCKETS
mdefine_line|#define QDIO_IRQ_BUCKETS 256 /* heavy..., but does only use a few bytes, but&n;&t;&t;&t;      be rather faster in cases of collisions&n;&t;&t;&t;      (if there really is a collision, it is&n;&t;&t;&t;      on every (traditional) interrupt and every&n;&t;&t;&t;      do_QDIO, so we rather are generous */
DECL|macro|QDIO_QETH_QFMT
mdefine_line|#define QDIO_QETH_QFMT 0
DECL|macro|QDIO_ZFCP_QFMT
mdefine_line|#define QDIO_ZFCP_QFMT 1
DECL|macro|QDIO_IQDIO_QFMT
mdefine_line|#define QDIO_IQDIO_QFMT 2
DECL|macro|QDIO_IRQ_STATE_FRESH
mdefine_line|#define QDIO_IRQ_STATE_FRESH 0 /* must be 0 -&gt; memset has set it to 0 */
DECL|macro|QDIO_IRQ_STATE_INACTIVE
mdefine_line|#define QDIO_IRQ_STATE_INACTIVE 1
DECL|macro|QDIO_IRQ_STATE_ESTABLISHED
mdefine_line|#define QDIO_IRQ_STATE_ESTABLISHED 2
DECL|macro|QDIO_IRQ_STATE_ACTIVE
mdefine_line|#define QDIO_IRQ_STATE_ACTIVE 3
DECL|macro|QDIO_IRQ_STATE_STOPPED
mdefine_line|#define QDIO_IRQ_STATE_STOPPED 4
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
multiline_comment|/* #define QDIO_DBF_LIKE_HELL */
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
DECL|macro|QDIO_DBF_HEX3
mdefine_line|#define QDIO_DBF_HEX3(ex,name,addr,len) QDIO_DBF_HEX(ex,name,3,addr,len)
DECL|macro|QDIO_DBF_HEX4
mdefine_line|#define QDIO_DBF_HEX4(ex,name,addr,len) QDIO_DBF_HEX(ex,name,4,addr,len)
DECL|macro|QDIO_DBF_HEX5
mdefine_line|#define QDIO_DBF_HEX5(ex,name,addr,len) QDIO_DBF_HEX(ex,name,5,addr,len)
DECL|macro|QDIO_DBF_HEX6
mdefine_line|#define QDIO_DBF_HEX6(ex,name,addr,len) QDIO_DBF_HEX(ex,name,6,addr,len)
macro_line|#ifdef QDIO_DBF_LIKE_HELL
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
macro_line|#if 0
mdefine_line|#define QDIO_DBF_HEX0(ex,name,addr,len) do {} while (0)
mdefine_line|#define QDIO_DBF_HEX1(ex,name,addr,len) do {} while (0)
mdefine_line|#define QDIO_DBF_HEX2(ex,name,addr,len) do {} while (0)
macro_line|#ifndef QDIO_DBF_LIKE_HELL
mdefine_line|#define QDIO_DBF_HEX3(ex,name,addr,len) do {} while (0)
mdefine_line|#define QDIO_DBF_HEX4(ex,name,addr,len) do {} while (0)
mdefine_line|#define QDIO_DBF_HEX5(ex,name,addr,len) do {} while (0)
mdefine_line|#define QDIO_DBF_HEX6(ex,name,addr,len) do {} while (0)
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
macro_line|#endif /* 0 */
DECL|macro|QDIO_DBF_TEXT0
mdefine_line|#define QDIO_DBF_TEXT0(ex,name,text) QDIO_DBF_TEXT(ex,name,0,text)
DECL|macro|QDIO_DBF_TEXT1
mdefine_line|#define QDIO_DBF_TEXT1(ex,name,text) QDIO_DBF_TEXT(ex,name,1,text)
DECL|macro|QDIO_DBF_TEXT2
mdefine_line|#define QDIO_DBF_TEXT2(ex,name,text) QDIO_DBF_TEXT(ex,name,2,text)
DECL|macro|QDIO_DBF_TEXT3
mdefine_line|#define QDIO_DBF_TEXT3(ex,name,text) QDIO_DBF_TEXT(ex,name,3,text)
DECL|macro|QDIO_DBF_TEXT4
mdefine_line|#define QDIO_DBF_TEXT4(ex,name,text) QDIO_DBF_TEXT(ex,name,4,text)
DECL|macro|QDIO_DBF_TEXT5
mdefine_line|#define QDIO_DBF_TEXT5(ex,name,text) QDIO_DBF_TEXT(ex,name,5,text)
DECL|macro|QDIO_DBF_TEXT6
mdefine_line|#define QDIO_DBF_TEXT6(ex,name,text) QDIO_DBF_TEXT(ex,name,6,text)
macro_line|#ifdef QDIO_DBF_LIKE_HELL
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
macro_line|#if 0
mdefine_line|#define QDIO_DBF_TEXT0(ex,name,text) do {} while (0)
mdefine_line|#define QDIO_DBF_TEXT1(ex,name,text) do {} while (0)
mdefine_line|#define QDIO_DBF_TEXT2(ex,name,text) do {} while (0)
macro_line|#ifndef QDIO_DBF_LIKE_HELL
mdefine_line|#define QDIO_DBF_TEXT3(ex,name,text) do {} while (0)
mdefine_line|#define QDIO_DBF_TEXT4(ex,name,text) do {} while (0)
mdefine_line|#define QDIO_DBF_TEXT5(ex,name,text) do {} while (0)
mdefine_line|#define QDIO_DBF_TEXT6(ex,name,text) do {} while (0)
macro_line|#endif /* QDIO_DBF_LIKE_HELL */
macro_line|#endif /* 0 */
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
multiline_comment|/****************** END OF DEBUG FACILITY STUFF *********************/
DECL|struct|qdio_buffer_element_t
r_typedef
r_struct
id|qdio_buffer_element_t
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
macro_line|#ifdef QDIO_32_BIT
DECL|member|reserved
r_void
op_star
id|reserved
suffix:semicolon
macro_line|#endif /* QDIO_32_BIT */
DECL|member|addr
r_void
op_star
id|addr
suffix:semicolon
DECL|typedef|qdio_buffer_element_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
id|qdio_buffer_element_t
suffix:semicolon
DECL|struct|qdio_buffer_t
r_typedef
r_struct
id|qdio_buffer_t
(brace
DECL|member|element
r_volatile
id|qdio_buffer_element_t
id|element
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|qdio_buffer_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
id|qdio_buffer_t
suffix:semicolon
multiline_comment|/* params are: irq, status, qdio_error, siga_error,&n;   queue_number, first element processed, number of elements processed,&n;   int_parm */
DECL|typedef|qdio_handler_t
r_typedef
r_void
id|qdio_handler_t
c_func
(paren
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|QDIO_STATUS_INBOUND_INT
mdefine_line|#define QDIO_STATUS_INBOUND_INT 0x01
DECL|macro|QDIO_STATUS_OUTBOUND_INT
mdefine_line|#define QDIO_STATUS_OUTBOUND_INT 0x02
DECL|macro|QDIO_STATUS_LOOK_FOR_ERROR
mdefine_line|#define QDIO_STATUS_LOOK_FOR_ERROR 0x04
DECL|macro|QDIO_STATUS_MORE_THAN_ONE_QDIO_ERROR
mdefine_line|#define QDIO_STATUS_MORE_THAN_ONE_QDIO_ERROR 0x08
DECL|macro|QDIO_STATUS_MORE_THAN_ONE_SIGA_ERROR
mdefine_line|#define QDIO_STATUS_MORE_THAN_ONE_SIGA_ERROR 0x10
DECL|macro|QDIO_STATUS_ACTIVATE_CHECK_CONDITION
mdefine_line|#define QDIO_STATUS_ACTIVATE_CHECK_CONDITION 0x20
DECL|macro|QDIO_SIGA_ERROR_ACCESS_EXCEPTION
mdefine_line|#define QDIO_SIGA_ERROR_ACCESS_EXCEPTION 0x10
DECL|macro|QDIO_SIGA_ERROR_B_BIT_SET
mdefine_line|#define QDIO_SIGA_ERROR_B_BIT_SET 0x20
multiline_comment|/* for qdio_initialize */
DECL|macro|QDIO_INBOUND_0COPY_SBALS
mdefine_line|#define QDIO_INBOUND_0COPY_SBALS 0x01
DECL|macro|QDIO_OUTBOUND_0COPY_SBALS
mdefine_line|#define QDIO_OUTBOUND_0COPY_SBALS 0x02
DECL|macro|QDIO_USE_OUTBOUND_PCIS
mdefine_line|#define QDIO_USE_OUTBOUND_PCIS 0x04
multiline_comment|/* for qdio_cleanup */
DECL|macro|QDIO_FLAG_CLEANUP_USING_CLEAR
mdefine_line|#define QDIO_FLAG_CLEANUP_USING_CLEAR 0x01
DECL|macro|QDIO_FLAG_CLEANUP_USING_HALT
mdefine_line|#define QDIO_FLAG_CLEANUP_USING_HALT 0x02
DECL|struct|qdio_initialize_t
r_typedef
r_struct
id|qdio_initialize_t
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|q_format
r_int
r_char
id|q_format
suffix:semicolon
DECL|member|adapter_name
r_int
r_char
id|adapter_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|qib_param_field_format
r_int
r_int
id|qib_param_field_format
suffix:semicolon
multiline_comment|/*adapter dependent*/
multiline_comment|/* pointer to 128 bytes or NULL, if no param field */
DECL|member|qib_param_field
r_int
r_char
op_star
id|qib_param_field
suffix:semicolon
multiline_comment|/* adapter dependent */
multiline_comment|/* pointer to no_queues*128 words of data or NULL */
DECL|member|input_slib_elements
r_int
r_int
op_star
id|input_slib_elements
suffix:semicolon
DECL|member|output_slib_elements
r_int
r_int
op_star
id|output_slib_elements
suffix:semicolon
DECL|member|min_input_threshold
r_int
r_int
id|min_input_threshold
suffix:semicolon
DECL|member|max_input_threshold
r_int
r_int
id|max_input_threshold
suffix:semicolon
DECL|member|min_output_threshold
r_int
r_int
id|min_output_threshold
suffix:semicolon
DECL|member|max_output_threshold
r_int
r_int
id|max_output_threshold
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
DECL|member|input_handler
id|qdio_handler_t
op_star
id|input_handler
suffix:semicolon
DECL|member|output_handler
id|qdio_handler_t
op_star
id|output_handler
suffix:semicolon
DECL|member|int_parm
r_int
r_int
id|int_parm
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|input_sbal_addr_array
r_void
op_star
op_star
id|input_sbal_addr_array
suffix:semicolon
multiline_comment|/* addr of n*128 void ptrs */
DECL|member|output_sbal_addr_array
r_void
op_star
op_star
id|output_sbal_addr_array
suffix:semicolon
multiline_comment|/* addr of n*128 void ptrs */
DECL|typedef|qdio_initialize_t
)brace
id|qdio_initialize_t
suffix:semicolon
r_extern
r_int
id|qdio_initialize
c_func
(paren
id|qdio_initialize_t
op_star
id|init_data
)paren
suffix:semicolon
r_extern
r_int
id|qdio_activate
c_func
(paren
r_int
id|irq
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|macro|QDIO_STATE_MUST_USE_OUTB_PCI
mdefine_line|#define QDIO_STATE_MUST_USE_OUTB_PCI&t;0x00000001
DECL|macro|QDIO_STATE_INACTIVE
mdefine_line|#define QDIO_STATE_INACTIVE &t;&t;0x00000002 /* after qdio_cleanup */
DECL|macro|QDIO_STATE_ESTABLISHED
mdefine_line|#define QDIO_STATE_ESTABLISHED &t;&t;0x00000004 /* after qdio_initialize */
DECL|macro|QDIO_STATE_ACTIVE
mdefine_line|#define QDIO_STATE_ACTIVE &t;&t;0x00000008 /* after qdio_activate */
DECL|macro|QDIO_STATE_STOPPED
mdefine_line|#define QDIO_STATE_STOPPED &t;&t;0x00000010 /* after queues went down */
r_extern
r_int
r_int
id|qdio_get_status
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
DECL|macro|QDIO_FLAG_SYNC_INPUT
mdefine_line|#define QDIO_FLAG_SYNC_INPUT     0x01
DECL|macro|QDIO_FLAG_SYNC_OUTPUT
mdefine_line|#define QDIO_FLAG_SYNC_OUTPUT    0x02
DECL|macro|QDIO_FLAG_UNDER_INTERRUPT
mdefine_line|#define QDIO_FLAG_UNDER_INTERRUPT 0x04
DECL|macro|QDIO_FLAG_NO_INPUT_INTERRUPT_CONTEXT
mdefine_line|#define QDIO_FLAG_NO_INPUT_INTERRUPT_CONTEXT 0x08 /* no effect on&n;&t;&t;&t;&t;&t;&t;     adapter interrupts */
DECL|macro|QDIO_FLAG_DONT_SIGA
mdefine_line|#define QDIO_FLAG_DONT_SIGA 0x10
r_extern
r_int
id|do_QDIO
c_func
(paren
r_int
id|irq
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|queue_number
comma
r_int
r_int
id|qidx
comma
r_int
r_int
id|count
comma
id|qdio_buffer_t
op_star
id|buffers
)paren
suffix:semicolon
r_extern
r_int
id|qdio_synchronize
c_func
(paren
r_int
id|irq
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|queue_number
)paren
suffix:semicolon
r_extern
r_int
id|qdio_cleanup
c_func
(paren
r_int
id|irq
comma
r_int
id|how
)paren
suffix:semicolon
r_int
r_char
id|qdio_get_slsb_state
c_func
(paren
r_int
id|irq
comma
r_int
r_int
id|flag
comma
r_int
r_int
id|queue_number
comma
r_int
r_int
id|qidx
)paren
suffix:semicolon
r_extern
r_void
id|qdio_init_scrubber
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * QDIO device commands returned by extended Sense-ID&n; */
DECL|macro|DEFAULT_ESTABLISH_QS_CMD
mdefine_line|#define DEFAULT_ESTABLISH_QS_CMD 0x1b
DECL|macro|DEFAULT_ESTABLISH_QS_COUNT
mdefine_line|#define DEFAULT_ESTABLISH_QS_COUNT 0x1000
DECL|macro|DEFAULT_ACTIVATE_QS_CMD
mdefine_line|#define DEFAULT_ACTIVATE_QS_CMD 0x1f
DECL|macro|DEFAULT_ACTIVATE_QS_COUNT
mdefine_line|#define DEFAULT_ACTIVATE_QS_COUNT 0
DECL|struct|_qdio_cmds
r_typedef
r_struct
id|_qdio_cmds
(brace
DECL|member|rcd
r_int
r_char
id|rcd
suffix:semicolon
multiline_comment|/* read configuration data */
DECL|member|count_rcd
r_int
r_int
id|count_rcd
suffix:semicolon
DECL|member|sii
r_int
r_char
id|sii
suffix:semicolon
multiline_comment|/* set interface identifier */
DECL|member|count_sii
r_int
r_int
id|count_sii
suffix:semicolon
DECL|member|rni
r_int
r_char
id|rni
suffix:semicolon
multiline_comment|/* read node identifier */
DECL|member|count_rni
r_int
r_int
id|count_rni
suffix:semicolon
DECL|member|eq
r_int
r_char
id|eq
suffix:semicolon
multiline_comment|/* establish QDIO queues */
DECL|member|count_eq
r_int
r_int
id|count_eq
suffix:semicolon
DECL|member|aq
r_int
r_char
id|aq
suffix:semicolon
multiline_comment|/* activate QDIO queues */
DECL|member|count_aq
r_int
r_int
id|count_aq
suffix:semicolon
DECL|typedef|qdio_cmds_t
)brace
id|qdio_cmds_t
suffix:semicolon
multiline_comment|/*&n; * additional CIWs returned by extended Sense-ID&n; */
DECL|macro|CIW_TYPE_EQUEUE
mdefine_line|#define CIW_TYPE_EQUEUE 0x3       /* establish QDIO queues */
DECL|macro|CIW_TYPE_AQUEUE
mdefine_line|#define CIW_TYPE_AQUEUE 0x4       /* activate QDIO queues */
DECL|struct|_qdesfmt0
r_typedef
r_struct
id|_qdesfmt0
(brace
macro_line|#ifdef QDIO_32_BIT
DECL|member|res1
r_int
r_int
id|res1
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|sliba
r_int
r_int
id|sliba
suffix:semicolon
multiline_comment|/* storage-list-information-block&n;&t;&t;&t;&t;&t;   address */
macro_line|#ifdef QDIO_32_BIT
DECL|member|res2
r_int
r_int
id|res2
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|sla
r_int
r_int
id|sla
suffix:semicolon
multiline_comment|/* storage-list address */
macro_line|#ifdef QDIO_32_BIT
DECL|member|res3
r_int
r_int
id|res3
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|slsba
r_int
r_int
id|slsba
suffix:semicolon
multiline_comment|/* storage-list-state-block address */
DECL|member|res4
r_int
r_int
id|res4
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|akey
r_int
r_int
id|akey
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* access key for DLIB */
DECL|member|bkey
r_int
r_int
id|bkey
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* access key for SL */
DECL|member|ckey
r_int
r_int
id|ckey
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* access key for SBALs */
DECL|member|dkey
r_int
r_int
id|dkey
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* access key for SLSB */
DECL|member|res5
r_int
r_int
id|res5
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|qdesfmt0_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|qdesfmt0_t
suffix:semicolon
multiline_comment|/*&n; * Queue-Description record (QDR)&n; */
DECL|struct|_qdr
r_typedef
r_struct
id|_qdr
(brace
DECL|member|qfmt
r_int
r_int
id|qfmt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* queue format */
DECL|member|pfmt
r_int
r_int
id|pfmt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* impl. dep. parameter format */
DECL|member|res1
r_int
r_int
id|res1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|ac
r_int
r_int
id|ac
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* adapter characteristics */
DECL|member|res2
r_int
r_int
id|res2
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|iqdcnt
r_int
r_int
id|iqdcnt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* input-queue-descriptor count */
DECL|member|res3
r_int
r_int
id|res3
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|oqdcnt
r_int
r_int
id|oqdcnt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* output-queue-descriptor count */
DECL|member|res4
r_int
r_int
id|res4
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|iqdsz
r_int
r_int
id|iqdsz
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* input-queue-descriptor size */
DECL|member|res5
r_int
r_int
id|res5
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|oqdsz
r_int
r_int
id|oqdsz
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* output-queue-descriptor size */
DECL|member|res6
r_int
r_int
id|res6
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#ifdef QDIO_32_BIT
DECL|member|res7
r_int
r_int
id|res7
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|qiba
r_int
r_int
id|qiba
suffix:semicolon
multiline_comment|/* queue-information-block address */
DECL|member|res8
r_int
r_int
id|res8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|qkey
r_int
r_int
id|qkey
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* queue-informatio-block key */
DECL|member|res9
r_int
r_int
id|res9
suffix:colon
l_int|28
suffix:semicolon
multiline_comment|/* reserved */
multiline_comment|/*&t;union _qd {*/
multiline_comment|/* why this? */
DECL|member|qdf0
id|qdesfmt0_t
id|qdf0
(braket
l_int|126
)braket
suffix:semicolon
multiline_comment|/*&t;} qd;*/
DECL|typedef|qdr_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4096
)paren
)paren
)paren
id|qdr_t
suffix:semicolon
multiline_comment|/*&n; * queue information block (QIB)&n; */
DECL|macro|QIB_AC_INBOUND_PCI_SUPPORTED
mdefine_line|#define QIB_AC_INBOUND_PCI_SUPPORTED 0x80
DECL|macro|QIB_AC_OUTBOUND_PCI_SUPPORTED
mdefine_line|#define QIB_AC_OUTBOUND_PCI_SUPPORTED 0x40
DECL|struct|_qib
r_typedef
r_struct
id|_qib
(brace
DECL|member|qfmt
r_int
r_int
id|qfmt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* queue format */
DECL|member|pfmt
r_int
r_int
id|pfmt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* impl. dep. parameter format */
DECL|member|res1
r_int
r_int
id|res1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|ac
r_int
r_int
id|ac
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* adapter characteristics */
DECL|member|res2
r_int
r_int
id|res2
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#ifdef QDIO_32_BIT
DECL|member|res3
r_int
r_int
id|res3
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|isliba
r_int
r_int
id|isliba
suffix:semicolon
multiline_comment|/* absolute address of 1st&n;&t;&t;&t;&t;&t;   input SLIB */
macro_line|#ifdef QDIO_32_BIT
DECL|member|res4
r_int
r_int
id|res4
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|osliba
r_int
r_int
id|osliba
suffix:semicolon
multiline_comment|/* absolute address of 1st&n;&t;&t;&t;&t;&t;   output SLIB */
DECL|member|res5
r_int
r_int
id|res5
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|res6
r_int
r_int
id|res6
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|ebcnam
r_int
r_char
id|ebcnam
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* adapter identifier in EBCDIC */
DECL|member|res7
r_int
r_char
id|res7
(braket
l_int|88
)braket
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|parm
r_int
r_char
id|parm
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
multiline_comment|/* implementation dependent&n;&t;&t;&t;&t;&t;   parameters */
DECL|typedef|qib_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
id|qib_t
suffix:semicolon
multiline_comment|/*&n; * storage-list-information block element (SLIBE)&n; */
DECL|struct|_slibe
r_typedef
r_struct
id|_slibe
(brace
macro_line|#ifdef QDIO_32_BIT
DECL|member|res
r_int
r_int
id|res
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|parms
r_int
r_int
id|parms
suffix:semicolon
multiline_comment|/* implementation dependent&n;&t;&t;&t;&t;&t;   parameters */
DECL|typedef|slibe_t
)brace
id|slibe_t
suffix:semicolon
multiline_comment|/*&n; * storage-list-information block (SLIB)&n; */
DECL|struct|_slib
r_typedef
r_struct
id|_slib
(brace
macro_line|#ifdef QDIO_32_BIT
DECL|member|res1
r_int
r_int
id|res1
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|nsliba
r_int
r_int
id|nsliba
suffix:semicolon
multiline_comment|/* next SLIB address (if any) */
macro_line|#ifdef QDIO_32_BIT
DECL|member|res2
r_int
r_int
id|res2
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|sla
r_int
r_int
id|sla
suffix:semicolon
multiline_comment|/* SL address */
macro_line|#ifdef QDIO_32_BIT
DECL|member|res3
r_int
r_int
id|res3
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|slsba
r_int
r_int
id|slsba
suffix:semicolon
multiline_comment|/* SLSB address */
DECL|member|res4
r_int
r_char
id|res4
(braket
l_int|1000
)braket
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|slibe
id|slibe_t
id|slibe
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
multiline_comment|/* SLIB elements */
DECL|typedef|slib_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|2048
)paren
)paren
)paren
id|slib_t
suffix:semicolon
DECL|struct|_sbal_flags
r_typedef
r_struct
id|_sbal_flags
(brace
DECL|member|res1
r_int
r_char
id|res1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|last
r_int
r_char
id|last
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* last entry */
DECL|member|cont
r_int
r_char
id|cont
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* contiguous storage */
DECL|member|res2
r_int
r_char
id|res2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|frag
r_int
r_char
id|frag
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* fragmentation (s.below) */
DECL|member|res3
r_int
r_char
id|res3
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|sbal_flags_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|sbal_flags_t
suffix:semicolon
DECL|macro|SBAL_FLAGS_FIRST_FRAG
mdefine_line|#define SBAL_FLAGS_FIRST_FRAG&t;     0x04000000UL
DECL|macro|SBAL_FLAGS_MIDDLE_FRAG
mdefine_line|#define SBAL_FLAGS_MIDDLE_FRAG&t;     0x08000000UL
DECL|macro|SBAL_FLAGS_LAST_FRAG
mdefine_line|#define SBAL_FLAGS_LAST_FRAG&t;     0x0c000000UL
DECL|macro|SBAL_FLAGS_LAST_ENTRY
mdefine_line|#define SBAL_FLAGS_LAST_ENTRY&t;     0x40000000UL
DECL|macro|SBAL_FLAGS_CONTIGUOUS
mdefine_line|#define SBAL_FLAGS_CONTIGUOUS&t;     0x20000000UL
DECL|macro|SBAL_FLAGS0_DATA_CONTINUATION
mdefine_line|#define SBAL_FLAGS0_DATA_CONTINUATION 0x20UL
multiline_comment|/* Awesome OpenFCP extensions */
DECL|macro|SBAL_FLAGS0_TYPE_STATUS
mdefine_line|#define SBAL_FLAGS0_TYPE_STATUS       0x00UL
DECL|macro|SBAL_FLAGS0_TYPE_WRITE
mdefine_line|#define SBAL_FLAGS0_TYPE_WRITE        0x08UL
DECL|macro|SBAL_FLAGS0_TYPE_READ
mdefine_line|#define SBAL_FLAGS0_TYPE_READ         0x10UL
DECL|macro|SBAL_FLAGS0_TYPE_WRITE_READ
mdefine_line|#define SBAL_FLAGS0_TYPE_WRITE_READ   0x18UL
DECL|macro|SBAL_FLAGS0_MORE_SBALS
mdefine_line|#define SBAL_FLAGS0_MORE_SBALS&t;      0x04UL
DECL|macro|SBAL_FLAGS0_COMMAND
mdefine_line|#define SBAL_FLAGS0_COMMAND           0x02UL
DECL|macro|SBAL_FLAGS0_LAST_SBAL
mdefine_line|#define SBAL_FLAGS0_LAST_SBAL         0x00UL
DECL|macro|SBAL_FLAGS0_ONLY_SBAL
mdefine_line|#define SBAL_FLAGS0_ONLY_SBAL         SBAL_FLAGS0_COMMAND
DECL|macro|SBAL_FLAGS0_MIDDLE_SBAL
mdefine_line|#define SBAL_FLAGS0_MIDDLE_SBAL       SBAL_FLAGS0_MORE_SBALS
DECL|macro|SBAL_FLAGS0_FIRST_SBAL
mdefine_line|#define SBAL_FLAGS0_FIRST_SBAL        SBAL_FLAGS0_MORE_SBALS | SBAL_FLAGS0_COMMAND
multiline_comment|/* Naught of interest beyond this point */
DECL|macro|SBAL_FLAGS0_PCI
mdefine_line|#define SBAL_FLAGS0_PCI&t;&t;0x40
DECL|struct|_sbal_sbalf_0
r_typedef
r_struct
id|_sbal_sbalf_0
(brace
DECL|member|res1
r_int
r_char
id|res1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|pci
r_int
r_char
id|pci
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* PCI indicator */
DECL|member|cont
r_int
r_char
id|cont
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* data continuation */
DECL|member|sbtype
r_int
r_char
id|sbtype
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* storage-block type (OpenFCP) */
DECL|member|res2
r_int
r_char
id|res2
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|sbal_sbalf_0_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|sbal_sbalf_0_t
suffix:semicolon
DECL|struct|_sbal_sbalf_1
r_typedef
r_struct
id|_sbal_sbalf_1
(brace
DECL|member|res1
r_int
r_char
id|res1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|key
r_int
r_char
id|key
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* storage key */
DECL|typedef|sbal_sbalf_1_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|sbal_sbalf_1_t
suffix:semicolon
DECL|struct|_sbal_sbalf_14
r_typedef
r_struct
id|_sbal_sbalf_14
(brace
DECL|member|res1
r_int
r_char
id|res1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|erridx
r_int
r_char
id|erridx
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* error index */
DECL|typedef|sbal_sbalf_14_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|sbal_sbalf_14_t
suffix:semicolon
DECL|struct|_sbal_sbalf_15
r_typedef
r_struct
id|_sbal_sbalf_15
(brace
DECL|member|reason
r_int
r_char
id|reason
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|sbal_sbalf_15_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|sbal_sbalf_15_t
suffix:semicolon
DECL|union|_sbal_sbalf
r_typedef
r_union
id|_sbal_sbalf
(brace
DECL|member|i0
id|sbal_sbalf_0_t
id|i0
suffix:semicolon
DECL|member|i1
id|sbal_sbalf_1_t
id|i1
suffix:semicolon
DECL|member|i14
id|sbal_sbalf_14_t
id|i14
suffix:semicolon
DECL|member|i15
id|sbal_sbalf_15_t
id|i15
suffix:semicolon
DECL|member|value
r_int
r_char
id|value
suffix:semicolon
DECL|typedef|sbal_sbalf_t
)brace
id|sbal_sbalf_t
suffix:semicolon
DECL|struct|_sbale
r_typedef
r_struct
id|_sbale
(brace
r_union
(brace
DECL|member|bits
id|sbal_flags_t
id|bits
suffix:semicolon
multiline_comment|/* flags */
DECL|member|value
r_int
r_char
id|value
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
DECL|member|res1
r_int
r_int
id|res1
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|sbalf
id|sbal_sbalf_t
id|sbalf
suffix:semicolon
multiline_comment|/* SBAL flags */
DECL|member|res2
r_int
r_int
id|res2
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|count
r_int
r_int
id|count
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* data count */
macro_line|#ifdef QDIO_32_BIT
DECL|member|res3
r_int
r_int
id|res3
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* absolute data address */
DECL|typedef|sbal_element_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
id|sbal_element_t
suffix:semicolon
multiline_comment|/*&n; * strorage-block access-list (SBAL)&n; */
DECL|struct|_sbal
r_typedef
r_struct
id|_sbal
(brace
DECL|member|element
id|sbal_element_t
id|element
(braket
id|QDIO_MAX_ELEMENTS_PER_BUFFER
)braket
suffix:semicolon
DECL|typedef|sbal_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
id|sbal_t
suffix:semicolon
multiline_comment|/*&n; * storage-list (SL)&n; */
DECL|struct|_sl_element
r_typedef
r_struct
id|_sl_element
(brace
macro_line|#ifdef QDIO_32_BIT
DECL|member|res
r_int
r_int
id|res
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif /* QDIO_32_BIT */
DECL|member|sbal
r_int
r_int
id|sbal
suffix:semicolon
multiline_comment|/* absolute SBAL address */
DECL|typedef|sl_element_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|sl_element_t
suffix:semicolon
DECL|struct|_sl
r_typedef
r_struct
id|_sl
(brace
DECL|member|element
id|sl_element_t
id|element
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|typedef|sl_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|1024
)paren
)paren
)paren
id|sl_t
suffix:semicolon
multiline_comment|/*&n; * storage-list-state block (SLSB)&n; */
multiline_comment|/*typedef struct _slsb_val {*/
multiline_comment|/*&t;unsigned char value;       */
multiline_comment|/* SLSB entry as a single byte value */
multiline_comment|/*} __attribute__ ((packed)) slsb_val_t;*/
DECL|struct|_slsb_flags
r_typedef
r_struct
id|_slsb_flags
(brace
DECL|member|owner
r_int
r_char
id|owner
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* SBAL owner */
DECL|member|type
r_int
r_char
id|type
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* buffer type */
DECL|member|state
r_int
r_char
id|state
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* processing state */
DECL|typedef|slsb_flags_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|slsb_flags_t
suffix:semicolon
DECL|struct|_slsb
r_typedef
r_struct
id|_slsb
(brace
DECL|union|_acc
r_union
id|_acc
(brace
DECL|member|val
r_int
r_char
id|val
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|flags
id|slsb_flags_t
id|flags
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|acc
)brace
id|acc
suffix:semicolon
DECL|typedef|slsb_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
id|slsb_t
suffix:semicolon
multiline_comment|/*&n; * SLSB values&n; */
DECL|macro|SLSB_OWNER_PROG
mdefine_line|#define SLSB_OWNER_PROG              1
DECL|macro|SLSB_OWNER_CU
mdefine_line|#define SLSB_OWNER_CU                2
DECL|macro|SLSB_TYPE_INPUT
mdefine_line|#define SLSB_TYPE_INPUT              0
DECL|macro|SLSB_TYPE_OUTPUT
mdefine_line|#define SLSB_TYPE_OUTPUT             1
DECL|macro|SLSB_STATE_NOT_INIT
mdefine_line|#define SLSB_STATE_NOT_INIT          0
DECL|macro|SLSB_STATE_EMPTY
mdefine_line|#define SLSB_STATE_EMPTY             1
DECL|macro|SLSB_STATE_PRIMED
mdefine_line|#define SLSB_STATE_PRIMED            2
DECL|macro|SLSB_STATE_HALTED
mdefine_line|#define SLSB_STATE_HALTED          0xe
DECL|macro|SLSB_STATE_ERROR
mdefine_line|#define SLSB_STATE_ERROR           0xf
DECL|macro|SLSB_P_INPUT_NOT_INIT
mdefine_line|#define SLSB_P_INPUT_NOT_INIT     0x80
DECL|macro|SLSB_P_INPUT_PROCESSING
mdefine_line|#define SLSB_P_INPUT_PROCESSING&t;  0x81
DECL|macro|SLSB_CU_INPUT_EMPTY
mdefine_line|#define SLSB_CU_INPUT_EMPTY       0x41
DECL|macro|SLSB_P_INPUT_PRIMED
mdefine_line|#define SLSB_P_INPUT_PRIMED       0x82
DECL|macro|SLSB_P_INPUT_HALTED
mdefine_line|#define SLSB_P_INPUT_HALTED       0x8E
DECL|macro|SLSB_P_INPUT_ERROR
mdefine_line|#define SLSB_P_INPUT_ERROR        0x8F
DECL|macro|SLSB_P_OUTPUT_NOT_INIT
mdefine_line|#define SLSB_P_OUTPUT_NOT_INIT    0xA0
DECL|macro|SLSB_P_OUTPUT_EMPTY
mdefine_line|#define SLSB_P_OUTPUT_EMPTY       0xA1
DECL|macro|SLSB_CU_OUTPUT_PRIMED
mdefine_line|#define SLSB_CU_OUTPUT_PRIMED     0x62
DECL|macro|SLSB_P_OUTPUT_HALTED
mdefine_line|#define SLSB_P_OUTPUT_HALTED      0xAE
DECL|macro|SLSB_P_OUTPUT_ERROR
mdefine_line|#define SLSB_P_OUTPUT_ERROR       0xAF
DECL|macro|SLSB_ERROR_DURING_LOOKUP
mdefine_line|#define SLSB_ERROR_DURING_LOOKUP  0xFF
multiline_comment|/*&n; * path management control word (extended layout)&n; */
r_typedef
r_struct
(brace
DECL|member|intparm
r_int
r_int
id|intparm
suffix:semicolon
multiline_comment|/* interruption parameter */
DECL|member|qf
r_int
r_int
id|qf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* qdio facility */
DECL|member|res0
r_int
r_int
id|res0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|isc
r_int
r_int
id|isc
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* interruption sublass */
DECL|member|res5
r_int
r_int
id|res5
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* reserved zeros */
DECL|member|ena
r_int
r_int
id|ena
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* enabled */
DECL|member|lm
r_int
r_int
id|lm
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* limit mode */
DECL|member|mme
r_int
r_int
id|mme
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* measurement-mode enable */
DECL|member|mp
r_int
r_int
id|mp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* multipath mode */
DECL|member|tf
r_int
r_int
id|tf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* timing facility */
DECL|member|dnv
r_int
r_int
id|dnv
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* device number valid */
DECL|member|dev
r_int
r_int
id|dev
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* device number */
DECL|member|lpm
r_int
r_char
id|lpm
suffix:semicolon
multiline_comment|/* logical path mask */
DECL|member|pnom
r_int
r_char
id|pnom
suffix:semicolon
multiline_comment|/* path not operational mask */
DECL|member|lpum
r_int
r_char
id|lpum
suffix:semicolon
multiline_comment|/* last path used mask */
DECL|member|pim
r_int
r_char
id|pim
suffix:semicolon
multiline_comment|/* path installed mask */
DECL|member|mbi
r_int
r_int
id|mbi
suffix:semicolon
multiline_comment|/* measurement-block index */
DECL|member|pom
r_int
r_char
id|pom
suffix:semicolon
multiline_comment|/* path operational mask */
DECL|member|pam
r_int
r_char
id|pam
suffix:semicolon
multiline_comment|/* path available mask */
DECL|member|chpid
r_int
r_char
id|chpid
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* CHPID 0-7 (if available) */
DECL|member|res1
r_int
r_int
id|res1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|st
r_int
r_int
id|st
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* */
DECL|member|res2
r_int
r_int
id|res2
suffix:colon
l_int|20
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|csense
r_int
r_int
id|csense
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* concurrent sense; can be enabled&n;&t;&t;&t;&t;&t;per MSCH, however, if facility&n;&t;&t;&t;&t;&t;is not installed, this results&n;&t;&t;&t;&t;&t;in an operand exception. */
DECL|typedef|pmcw_e_t
)brace
id|pmcw_e_t
suffix:semicolon
multiline_comment|/*&n; * subchannel status word (extended layout)&n; */
r_typedef
r_struct
(brace
DECL|member|key
r_int
r_int
id|key
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* subchannel key */
DECL|member|sctl
r_int
r_int
id|sctl
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* suspend control */
DECL|member|eswf
r_int
r_int
id|eswf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ESW format */
DECL|member|cc
r_int
r_int
id|cc
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* deferred condition code */
DECL|member|fmt
r_int
r_int
id|fmt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* format */
DECL|member|pfch
r_int
r_int
id|pfch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* prefetch */
DECL|member|isic
r_int
r_int
id|isic
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* initial-status interruption control */
DECL|member|alcc
r_int
r_int
id|alcc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* address-limit checking control */
DECL|member|ssi
r_int
r_int
id|ssi
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* supress-suspended interruption */
DECL|member|zcc
r_int
r_int
id|zcc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* zero condition code */
DECL|member|ectl
r_int
r_int
id|ectl
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* extended control */
DECL|member|pno
r_int
r_int
id|pno
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* path not operational */
DECL|member|qact
r_int
r_int
id|qact
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* qdio active */
DECL|member|fctl
r_int
r_int
id|fctl
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* function control */
DECL|member|actl
r_int
r_int
id|actl
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* activity control */
DECL|member|stctl
r_int
r_int
id|stctl
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* status control */
DECL|member|cpa
r_int
r_int
id|cpa
suffix:semicolon
multiline_comment|/* channel program address */
DECL|member|dstat
r_int
r_int
id|dstat
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* device status */
DECL|member|cstat
r_int
r_int
id|cstat
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* subchannel status */
DECL|member|count
r_int
r_int
id|count
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* residual count */
DECL|typedef|scsw_e_t
)brace
id|scsw_e_t
suffix:semicolon
DECL|struct|qdio_q_t
r_typedef
r_struct
id|qdio_q_t
(brace
DECL|member|slsb
r_volatile
id|slsb_t
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
DECL|member|is_0copy_sbals_q
r_int
id|is_0copy_sbals_q
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|is_iqdio_q
r_int
r_int
id|is_iqdio_q
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
r_int
r_int
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
id|qdio_q_t
op_star
id|list_next
suffix:semicolon
DECL|member|list_prev
r_volatile
r_struct
id|qdio_q_t
op_star
id|list_prev
suffix:semicolon
DECL|member|slib
id|slib_t
op_star
id|slib
suffix:semicolon
multiline_comment|/* a page is allocated under this pointer,&n;&t;&t;&t; sl points into this page, offset PAGE_SIZE/2&n;&t;&t;&t; (after slib) */
DECL|member|sl
id|sl_t
op_star
id|sl
suffix:semicolon
DECL|member|sbal
r_volatile
id|sbal_t
op_star
id|sbal
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|qdio_buffers
id|qdio_buffer_t
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
DECL|typedef|qdio_q_t
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
id|qdio_q_t
suffix:semicolon
DECL|struct|qdio_irq_t
r_typedef
r_struct
id|qdio_irq_t
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
r_int
r_int
id|state
suffix:semicolon
DECL|member|setting_up_lock
id|spinlock_t
id|setting_up_lock
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
id|qdio_q_t
op_star
id|input_qs
(braket
id|QDIO_MAX_QUEUES_PER_IRQ
)braket
suffix:semicolon
DECL|member|output_qs
id|qdio_q_t
op_star
id|output_qs
(braket
id|QDIO_MAX_QUEUES_PER_IRQ
)braket
suffix:semicolon
DECL|member|ccw
id|ccw1_t
id|ccw
suffix:semicolon
DECL|member|io_result_cstat
r_int
id|io_result_cstat
suffix:semicolon
DECL|member|io_result_dstat
r_int
id|io_result_dstat
suffix:semicolon
DECL|member|io_result_flags
r_int
id|io_result_flags
suffix:semicolon
DECL|member|interrupt_has_arrived
id|atomic_t
id|interrupt_has_arrived
suffix:semicolon
DECL|member|interrupt_has_been_cleaned
id|atomic_t
id|interrupt_has_been_cleaned
suffix:semicolon
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
DECL|member|qdr
id|qdr_t
op_star
id|qdr
suffix:semicolon
DECL|member|commands
id|qdio_cmds_t
id|commands
suffix:semicolon
DECL|member|qib
id|qib_t
id|qib
suffix:semicolon
DECL|member|original_int_handler
id|io_handler_func_t
id|original_int_handler
suffix:semicolon
DECL|member|next
r_struct
id|qdio_irq_t
op_star
id|next
suffix:semicolon
DECL|typedef|qdio_irq_t
)brace
id|qdio_irq_t
suffix:semicolon
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
DECL|struct|qdio_chsc_area_t
r_typedef
r_struct
id|qdio_chsc_area_t
(brace
r_struct
(brace
multiline_comment|/* word 0 */
DECL|member|command_code1
id|__u16
id|command_code1
suffix:semicolon
DECL|member|command_code2
id|__u16
id|command_code2
suffix:semicolon
multiline_comment|/* word 1 */
DECL|member|operation_code
id|__u16
id|operation_code
suffix:semicolon
DECL|member|first_sch
id|__u16
id|first_sch
suffix:semicolon
multiline_comment|/* word 2 */
DECL|member|reserved1
id|__u8
id|reserved1
suffix:semicolon
DECL|member|image_id
id|__u8
id|image_id
suffix:semicolon
DECL|member|last_sch
id|__u16
id|last_sch
suffix:semicolon
multiline_comment|/* word 3 */
DECL|member|reserved2
id|__u32
id|reserved2
suffix:semicolon
multiline_comment|/* word 4 */
r_union
(brace
r_struct
(brace
multiline_comment|/* word 4&amp;5 */
DECL|member|summary_indicator_addr
id|__u64
id|summary_indicator_addr
suffix:semicolon
multiline_comment|/* word 6&amp;7 */
DECL|member|subchannel_indicator_addr
id|__u64
id|subchannel_indicator_addr
suffix:semicolon
multiline_comment|/* word 8 */
DECL|member|ks
r_int
id|ks
suffix:colon
l_int|4
suffix:semicolon
DECL|member|kc
r_int
id|kc
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved1
r_int
id|reserved1
suffix:colon
l_int|21
suffix:semicolon
DECL|member|isc
r_int
id|isc
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* word 9&amp;10 */
DECL|member|reserved2
id|__u32
id|reserved2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* word 11 */
DECL|member|subsystem_id
id|__u32
id|subsystem_id
suffix:semicolon
multiline_comment|/* word 12-1015 */
DECL|member|reserved3
id|__u32
id|reserved3
(braket
l_int|1004
)braket
suffix:semicolon
DECL|member|set_chsc
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
id|set_chsc
suffix:semicolon
r_struct
(brace
multiline_comment|/* word 4&amp;5 */
DECL|member|reserved1
id|__u32
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* word 6 */
DECL|member|delay_target
id|__u32
id|delay_target
suffix:semicolon
multiline_comment|/* word 7-1015 */
DECL|member|reserved4
id|__u32
id|reserved4
(braket
l_int|1009
)braket
suffix:semicolon
DECL|member|set_chsc_fast
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|4
)paren
)paren
)paren
id|set_chsc_fast
suffix:semicolon
r_struct
(brace
multiline_comment|/* word 0 */
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|response_code
id|__u16
id|response_code
suffix:semicolon
multiline_comment|/* word 1 */
DECL|member|reserved1
id|__u32
id|reserved1
suffix:semicolon
multiline_comment|/* words 2 to 9 for st sch qdio data */
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:semicolon
DECL|member|sch
id|__u16
id|sch
suffix:semicolon
DECL|member|qfmt
id|__u8
id|qfmt
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:semicolon
DECL|member|qdioac
id|__u8
id|qdioac
suffix:semicolon
DECL|member|sch_class
id|__u8
id|sch_class
suffix:semicolon
DECL|member|reserved4
id|__u8
id|reserved4
suffix:semicolon
DECL|member|icnt
id|__u8
id|icnt
suffix:semicolon
DECL|member|reserved5
id|__u8
id|reserved5
suffix:semicolon
DECL|member|ocnt
id|__u8
id|ocnt
suffix:semicolon
multiline_comment|/* plus 5 words of reserved fields */
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
DECL|member|store_qdio_data_response
id|store_qdio_data_response
suffix:semicolon
DECL|member|operation_data_area
)brace
id|operation_data_area
suffix:semicolon
DECL|member|request_block
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|request_block
suffix:semicolon
r_struct
(brace
multiline_comment|/* word 0 */
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|response_code
id|__u16
id|response_code
suffix:semicolon
multiline_comment|/* word 1 */
DECL|member|reserved1
id|__u32
id|reserved1
suffix:semicolon
DECL|member|response_block
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
id|response_block
suffix:semicolon
DECL|typedef|qdio_chsc_area_t
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
id|qdio_chsc_area_t
suffix:semicolon
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
macro_line|#endif /* __QDIO_H__ */
eof
