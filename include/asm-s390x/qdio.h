multiline_comment|/*&n; * linux/include/asm/qdio.h&n; *&n; * Linux for S/390 QDIO base support, Hipersocket base support&n; * version 2&n; *&n; * Copyright 2000,2002 IBM Corporation&n; * Author(s): Utz Bacher &lt;utz.bacher@de.ibm.com&gt;&n; *&n; */
macro_line|#ifndef __QDIO_H__
DECL|macro|__QDIO_H__
mdefine_line|#define __QDIO_H__
DECL|macro|VERSION_QDIO_H
mdefine_line|#define VERSION_QDIO_H &quot;$Revision: 1.57 $&quot;
multiline_comment|/* note, that most of the typedef&squot;s are from ingo. */
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/cio.h&gt;
DECL|macro|QDIO_NAME
mdefine_line|#define QDIO_NAME &quot;qdio &quot;
macro_line|#ifndef CONFIG_ARCH_S390X
DECL|macro|QDIO_32_BIT
mdefine_line|#define QDIO_32_BIT
macro_line|#endif /* CONFIG_ARCH_S390X */
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
DECL|macro|QDIO_QETH_QFMT
mdefine_line|#define QDIO_QETH_QFMT 0
DECL|macro|QDIO_ZFCP_QFMT
mdefine_line|#define QDIO_ZFCP_QFMT 1
DECL|macro|QDIO_IQDIO_QFMT
mdefine_line|#define QDIO_IQDIO_QFMT 2
DECL|struct|qdio_buffer_element
r_struct
id|qdio_buffer_element
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
suffix:semicolon
DECL|struct|qdio_buffer
r_struct
id|qdio_buffer
(brace
DECL|member|element
r_volatile
r_struct
id|qdio_buffer_element
id|element
(braket
l_int|16
)braket
suffix:semicolon
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
suffix:semicolon
multiline_comment|/* params are: ccw_device, status, qdio_error, siga_error,&n;   queue_number, first element processed, number of elements processed,&n;   int_parm */
DECL|typedef|qdio_handler_t
r_typedef
r_void
id|qdio_handler_t
c_func
(paren
r_struct
id|ccw_device
op_star
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
DECL|struct|qdio_initialize
r_struct
id|qdio_initialize
(brace
DECL|member|cdev
r_struct
id|ccw_device
op_star
id|cdev
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
)brace
suffix:semicolon
r_extern
r_int
id|qdio_initialize
c_func
(paren
r_struct
id|qdio_initialize
op_star
id|init_data
)paren
suffix:semicolon
r_extern
r_int
id|qdio_allocate
c_func
(paren
r_struct
id|qdio_initialize
op_star
id|init_data
)paren
suffix:semicolon
r_extern
r_int
id|qdio_establish
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qdio_activate
c_func
(paren
r_struct
id|ccw_device
op_star
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
r_struct
id|ccw_device
op_star
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
r_struct
id|qdio_buffer
op_star
id|buffers
)paren
suffix:semicolon
r_extern
r_int
id|qdio_synchronize
c_func
(paren
r_struct
id|ccw_device
op_star
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
r_struct
id|ccw_device
op_star
comma
r_int
id|how
)paren
suffix:semicolon
r_extern
r_int
id|qdio_shutdown
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_int
id|how
)paren
suffix:semicolon
r_extern
r_int
id|qdio_free
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_int
r_char
id|qdio_get_slsb_state
c_func
(paren
r_struct
id|ccw_device
op_star
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
DECL|struct|qdesfmt0
r_struct
id|qdesfmt0
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Queue-Description record (QDR)&n; */
DECL|struct|qdr
r_struct
id|qdr
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
r_struct
id|qdesfmt0
id|qdf0
(braket
l_int|126
)braket
suffix:semicolon
multiline_comment|/*&t;} qd;*/
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
suffix:semicolon
multiline_comment|/*&n; * queue information block (QIB)&n; */
DECL|macro|QIB_AC_INBOUND_PCI_SUPPORTED
mdefine_line|#define QIB_AC_INBOUND_PCI_SUPPORTED 0x80
DECL|macro|QIB_AC_OUTBOUND_PCI_SUPPORTED
mdefine_line|#define QIB_AC_OUTBOUND_PCI_SUPPORTED 0x40
DECL|struct|qib
r_struct
id|qib
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
suffix:semicolon
multiline_comment|/*&n; * storage-list-information block element (SLIBE)&n; */
DECL|struct|slibe
r_struct
id|slibe
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
)brace
suffix:semicolon
multiline_comment|/*&n; * storage-list-information block (SLIB)&n; */
DECL|struct|slib
r_struct
id|slib
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
r_struct
id|slibe
id|slibe
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
multiline_comment|/* SLIB elements */
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
suffix:semicolon
DECL|struct|sbal_flags
r_struct
id|sbal_flags
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
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
DECL|struct|sbal_sbalf_0
r_struct
id|sbal_sbalf_0
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|sbal_sbalf_1
r_struct
id|sbal_sbalf_1
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|sbal_sbalf_14
r_struct
id|sbal_sbalf_14
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|sbal_sbalf_15
r_struct
id|sbal_sbalf_15
(brace
DECL|member|reason
r_int
r_char
id|reason
suffix:semicolon
multiline_comment|/* reserved */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|union|sbal_sbalf
r_union
id|sbal_sbalf
(brace
DECL|member|i0
r_struct
id|sbal_sbalf_0
id|i0
suffix:semicolon
DECL|member|i1
r_struct
id|sbal_sbalf_1
id|i1
suffix:semicolon
DECL|member|i14
r_struct
id|sbal_sbalf_14
id|i14
suffix:semicolon
DECL|member|i15
r_struct
id|sbal_sbalf_15
id|i15
suffix:semicolon
DECL|member|value
r_int
r_char
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sbal_element
r_struct
id|sbal_element
(brace
r_union
(brace
DECL|member|bits
r_struct
id|sbal_flags
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
r_union
id|sbal_sbalf
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
suffix:semicolon
multiline_comment|/*&n; * strorage-block access-list (SBAL)&n; */
DECL|struct|sbal
r_struct
id|sbal
(brace
DECL|member|element
r_struct
id|sbal_element
id|element
(braket
id|QDIO_MAX_ELEMENTS_PER_BUFFER
)braket
suffix:semicolon
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
suffix:semicolon
multiline_comment|/*&n; * storage-list (SL)&n; */
DECL|struct|sl_element
r_struct
id|sl_element
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|sl
r_struct
id|sl
(brace
DECL|member|element
r_struct
id|sl_element
id|element
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
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
suffix:semicolon
multiline_comment|/*&n; * storage-list-state block (SLSB)&n; */
DECL|struct|slsb_flags
r_struct
id|slsb_flags
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|slsb
r_struct
id|slsb
(brace
r_union
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
r_struct
id|slsb_flags
id|flags
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|acc
)brace
id|acc
suffix:semicolon
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
macro_line|#endif /* __QDIO_H__ */
eof
