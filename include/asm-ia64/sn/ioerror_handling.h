multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_IOERROR_HANDLING_H
DECL|macro|_ASM_SN_IOERROR_HANDLING_H
mdefine_line|#define _ASM_SN_IOERROR_HANDLING_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Basic types required for io error handling interfaces.&n; */
multiline_comment|/*&n; * Return code from the io error handling interfaces.&n; */
DECL|enum|error_return_code_e
r_enum
id|error_return_code_e
(brace
multiline_comment|/* Success */
DECL|enumerator|ERROR_RETURN_CODE_SUCCESS
id|ERROR_RETURN_CODE_SUCCESS
comma
multiline_comment|/* Unknown failure */
DECL|enumerator|ERROR_RETURN_CODE_GENERAL_FAILURE
id|ERROR_RETURN_CODE_GENERAL_FAILURE
comma
multiline_comment|/* Nth error noticed while handling the first error */
DECL|enumerator|ERROR_RETURN_CODE_NESTED_CALL
id|ERROR_RETURN_CODE_NESTED_CALL
comma
multiline_comment|/* State of the vertex is invalid */
DECL|enumerator|ERROR_RETURN_CODE_INVALID_STATE
id|ERROR_RETURN_CODE_INVALID_STATE
comma
multiline_comment|/* Invalid action */
DECL|enumerator|ERROR_RETURN_CODE_INVALID_ACTION
id|ERROR_RETURN_CODE_INVALID_ACTION
comma
multiline_comment|/* Valid action but not cannot set it */
DECL|enumerator|ERROR_RETURN_CODE_CANNOT_SET_ACTION
id|ERROR_RETURN_CODE_CANNOT_SET_ACTION
comma
multiline_comment|/* Valid action but not possible for the current state */
DECL|enumerator|ERROR_RETURN_CODE_CANNOT_PERFORM_ACTION
id|ERROR_RETURN_CODE_CANNOT_PERFORM_ACTION
comma
multiline_comment|/* Valid state but cannot change the state of the vertex to it */
DECL|enumerator|ERROR_RETURN_CODE_CANNOT_SET_STATE
id|ERROR_RETURN_CODE_CANNOT_SET_STATE
comma
multiline_comment|/* ??? */
DECL|enumerator|ERROR_RETURN_CODE_DUPLICATE
id|ERROR_RETURN_CODE_DUPLICATE
comma
multiline_comment|/* Reached the root of the system critical graph */
DECL|enumerator|ERROR_RETURN_CODE_SYS_CRITICAL_GRAPH_BEGIN
id|ERROR_RETURN_CODE_SYS_CRITICAL_GRAPH_BEGIN
comma
multiline_comment|/* Reached the leaf of the system critical graph */
DECL|enumerator|ERROR_RETURN_CODE_SYS_CRITICAL_GRAPH_ADD
id|ERROR_RETURN_CODE_SYS_CRITICAL_GRAPH_ADD
comma
multiline_comment|/* Cannot shutdown the device in hw/sw */
DECL|enumerator|ERROR_RETURN_CODE_SHUTDOWN_FAILED
id|ERROR_RETURN_CODE_SHUTDOWN_FAILED
comma
multiline_comment|/* Cannot restart the device in hw/sw */
DECL|enumerator|ERROR_RETURN_CODE_RESET_FAILED
id|ERROR_RETURN_CODE_RESET_FAILED
comma
multiline_comment|/* Cannot failover the io subsystem */
DECL|enumerator|ERROR_RETURN_CODE_FAILOVER_FAILED
id|ERROR_RETURN_CODE_FAILOVER_FAILED
comma
multiline_comment|/* No Jump Buffer exists */
DECL|enumerator|ERROR_RETURN_CODE_NO_JUMP_BUFFER
id|ERROR_RETURN_CODE_NO_JUMP_BUFFER
)brace
suffix:semicolon
DECL|typedef|error_return_code_t
r_typedef
r_uint64
id|error_return_code_t
suffix:semicolon
multiline_comment|/*&n; * State of the vertex during error handling.&n; */
DECL|enum|error_state_e
r_enum
id|error_state_e
(brace
multiline_comment|/* Ignore state */
DECL|enumerator|ERROR_STATE_IGNORE
id|ERROR_STATE_IGNORE
comma
multiline_comment|/* Invalid state */
DECL|enumerator|ERROR_STATE_NONE
id|ERROR_STATE_NONE
comma
multiline_comment|/* Trying to decipher the error bits */
DECL|enumerator|ERROR_STATE_LOOKUP
id|ERROR_STATE_LOOKUP
comma
multiline_comment|/* Trying to carryout the action decided upon after&n;&t; * looking at the error bits &n;&t; */
DECL|enumerator|ERROR_STATE_ACTION
id|ERROR_STATE_ACTION
comma
multiline_comment|/* Donot allow any other operations to this vertex from&n;&t; * other parts of the kernel. This is also used to indicate&n;&t; * that the device has been software shutdown.&n;&t; */
DECL|enumerator|ERROR_STATE_SHUTDOWN
id|ERROR_STATE_SHUTDOWN
comma
multiline_comment|/* This is a transitory state when no new requests are accepted&n;&t; * on behalf of the device. This is usually used when trying to&n;&t; * quiesce all the outstanding operations and preparing the&n;&t; * device for a failover / shutdown etc.&n;&t; */
DECL|enumerator|ERROR_STATE_SHUTDOWN_IN_PROGRESS
id|ERROR_STATE_SHUTDOWN_IN_PROGRESS
comma
multiline_comment|/* This is the state when there is absolutely no activity going&n;&t; * on wrt device.&n;&t; */
DECL|enumerator|ERROR_STATE_SHUTDOWN_COMPLETE
id|ERROR_STATE_SHUTDOWN_COMPLETE
comma
multiline_comment|/* This is the state when the device has issued a retry. */
DECL|enumerator|ERROR_STATE_RETRY
id|ERROR_STATE_RETRY
comma
multiline_comment|/* This is the normal state. This can also be used to indicate&n;&t; * that the device has been software-enabled after software-&n;&t; * shutting down previously.&n;&t; */
DECL|enumerator|ERROR_STATE_NORMAL
id|ERROR_STATE_NORMAL
)brace
suffix:semicolon
DECL|typedef|error_state_t
r_typedef
r_uint64
id|error_state_t
suffix:semicolon
multiline_comment|/*&n; * Generic error classes. This is used to classify errors after looking&n; * at the error bits and helpful in deciding on the action.&n; */
DECL|enum|error_class_e
r_enum
id|error_class_e
(brace
multiline_comment|/* Unclassified error */
DECL|enumerator|ERROR_CLASS_UNKNOWN
id|ERROR_CLASS_UNKNOWN
comma
multiline_comment|/* LLP transmit error */
DECL|enumerator|ERROR_CLASS_LLP_XMIT
id|ERROR_CLASS_LLP_XMIT
comma
multiline_comment|/* LLP receive error */
DECL|enumerator|ERROR_CLASS_LLP_RECV
id|ERROR_CLASS_LLP_RECV
comma
multiline_comment|/* Credit error */
DECL|enumerator|ERROR_CLASS_CREDIT
id|ERROR_CLASS_CREDIT
comma
multiline_comment|/* Timeout error */
DECL|enumerator|ERROR_CLASS_TIMEOUT
id|ERROR_CLASS_TIMEOUT
comma
multiline_comment|/* Access error */
DECL|enumerator|ERROR_CLASS_ACCESS
id|ERROR_CLASS_ACCESS
comma
multiline_comment|/* System coherency error */
DECL|enumerator|ERROR_CLASS_SYS_COHERENCY
id|ERROR_CLASS_SYS_COHERENCY
comma
multiline_comment|/* Bad data error (ecc / parity etc) */
DECL|enumerator|ERROR_CLASS_BAD_DATA
id|ERROR_CLASS_BAD_DATA
comma
multiline_comment|/* Illegal request packet */
DECL|enumerator|ERROR_CLASS_BAD_REQ_PKT
id|ERROR_CLASS_BAD_REQ_PKT
comma
multiline_comment|/* Illegal response packet */
DECL|enumerator|ERROR_CLASS_BAD_RESP_PKT
id|ERROR_CLASS_BAD_RESP_PKT
)brace
suffix:semicolon
DECL|typedef|error_class_t
r_typedef
r_uint64
id|error_class_t
suffix:semicolon
multiline_comment|/* &n; * Error context which the error action can use.&n; */
DECL|typedef|error_context_t
r_typedef
r_void
op_star
id|error_context_t
suffix:semicolon
DECL|macro|ERROR_CONTEXT_IGNORE
mdefine_line|#define ERROR_CONTEXT_IGNORE&t;((error_context_t)-1ll)
multiline_comment|/* &n; * Error action type.&n; */
DECL|typedef|error_action_f
r_typedef
id|error_return_code_t
(paren
op_star
id|error_action_f
)paren
(paren
id|error_context_t
)paren
suffix:semicolon
DECL|macro|ERROR_ACTION_IGNORE
mdefine_line|#define ERROR_ACTION_IGNORE&t;((error_action_f)-1ll)
multiline_comment|/* Typical set of error actions */
DECL|struct|error_action_set_s
r_typedef
r_struct
id|error_action_set_s
(brace
DECL|member|eas_panic
id|error_action_f
id|eas_panic
suffix:semicolon
DECL|member|eas_shutdown
id|error_action_f
id|eas_shutdown
suffix:semicolon
DECL|member|eas_abort
id|error_action_f
id|eas_abort
suffix:semicolon
DECL|member|eas_retry
id|error_action_f
id|eas_retry
suffix:semicolon
DECL|member|eas_failover
id|error_action_f
id|eas_failover
suffix:semicolon
DECL|member|eas_log_n_ignore
id|error_action_f
id|eas_log_n_ignore
suffix:semicolon
DECL|member|eas_reset
id|error_action_f
id|eas_reset
suffix:semicolon
DECL|typedef|error_action_set_t
)brace
id|error_action_set_t
suffix:semicolon
multiline_comment|/* Set of priorites for in case mutliple error actions/states&n; * are trying to be prescribed for a device.&n; * NOTE : The ordering below encapsulates the priorities. Highest value&n; * corresponds to highest priority.&n; */
DECL|enum|error_priority_e
r_enum
id|error_priority_e
(brace
DECL|enumerator|ERROR_PRIORITY_IGNORE
id|ERROR_PRIORITY_IGNORE
comma
DECL|enumerator|ERROR_PRIORITY_NONE
id|ERROR_PRIORITY_NONE
comma
DECL|enumerator|ERROR_PRIORITY_NORMAL
id|ERROR_PRIORITY_NORMAL
comma
DECL|enumerator|ERROR_PRIORITY_LOG
id|ERROR_PRIORITY_LOG
comma
DECL|enumerator|ERROR_PRIORITY_FAILOVER
id|ERROR_PRIORITY_FAILOVER
comma
DECL|enumerator|ERROR_PRIORITY_RETRY
id|ERROR_PRIORITY_RETRY
comma
DECL|enumerator|ERROR_PRIORITY_ABORT
id|ERROR_PRIORITY_ABORT
comma
DECL|enumerator|ERROR_PRIORITY_SHUTDOWN
id|ERROR_PRIORITY_SHUTDOWN
comma
DECL|enumerator|ERROR_PRIORITY_RESTART
id|ERROR_PRIORITY_RESTART
comma
DECL|enumerator|ERROR_PRIORITY_PANIC
id|ERROR_PRIORITY_PANIC
)brace
suffix:semicolon
DECL|typedef|error_priority_t
r_typedef
r_uint64
id|error_priority_t
suffix:semicolon
multiline_comment|/* Error state interfaces */
macro_line|#if defined(CONFIG_SGI_IO_ERROR_HANDLING)
r_extern
id|error_return_code_t
id|error_state_set
c_func
(paren
id|devfs_handle_t
comma
id|error_state_t
)paren
suffix:semicolon
r_extern
id|error_state_t
id|error_state_get
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* System critical graph interfaces */
r_extern
id|boolean_t
id|is_sys_critical_vertex
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|sys_critical_first_child_get
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|sys_critical_next_child_get
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|sys_critical_parent_get
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_extern
id|error_return_code_t
id|sys_critical_graph_vertex_add
c_func
(paren
id|devfs_handle_t
comma
id|devfs_handle_t
r_new
)paren
suffix:semicolon
multiline_comment|/* Error action interfaces */
r_extern
id|error_return_code_t
id|error_action_set
c_func
(paren
id|devfs_handle_t
comma
id|error_action_f
comma
id|error_context_t
comma
id|error_priority_t
)paren
suffix:semicolon
r_extern
id|error_return_code_t
id|error_action_perform
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
DECL|macro|INFO_LBL_ERROR_SKIP_ENV
mdefine_line|#define INFO_LBL_ERROR_SKIP_ENV&t;&quot;error_skip_env&quot;
DECL|macro|v_error_skip_env_get
mdefine_line|#define v_error_skip_env_get(v, l)&t;&t;&bslash;&n;hwgraph_info_get_LBL(v, INFO_LBL_ERROR_SKIP_ENV, (arbitrary_info_t *)&amp;l)
DECL|macro|v_error_skip_env_set
mdefine_line|#define v_error_skip_env_set(v, l, r)&t;&t;&bslash;&n;(r ? &t;&t;&t;&t;&t;&t;&bslash;&n; hwgraph_info_replace_LBL(v, INFO_LBL_ERROR_SKIP_ENV, (arbitrary_info_t)l,0) :&bslash;&n; hwgraph_info_add_LBL(v, INFO_LBL_ERROR_SKIP_ENV, (arbitrary_info_t)l))
DECL|macro|v_error_skip_env_clear
mdefine_line|#define v_error_skip_env_clear(v)&t;&t;&bslash;&n;hwgraph_info_remove_LBL(v, INFO_LBL_ERROR_SKIP_ENV, 0)
multiline_comment|/* Skip point interfaces */
r_extern
id|error_return_code_t
id|error_skip_point_jump
c_func
(paren
id|devfs_handle_t
comma
id|boolean_t
)paren
suffix:semicolon
r_extern
id|error_return_code_t
id|error_skip_point_clear
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
multiline_comment|/* REFERENCED */
macro_line|#if defined(CONFIG_SGI_IO_ERROR_HANDLING)
r_inline
r_static
r_int
DECL|function|error_skip_point_mark
id|error_skip_point_mark
c_func
(paren
id|devfs_handle_t
id|v
)paren
(brace
id|label_t
op_star
id|error_env
op_assign
l_int|NULL
suffix:semicolon
r_int
id|code
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Check if we have a valid hwgraph vertex */
macro_line|#ifdef IRIX
r_if
c_cond
(paren
op_logical_neg
id|dev_is_vertex
c_func
(paren
id|v
)paren
)paren
r_return
id|code
suffix:semicolon
macro_line|#endif
multiline_comment|/* There is no error jump buffer for this device vertex. Allocate&n;&t; * one.&t;&t;&t;&t;&t;&t;&t;&t; &n;&t; */
r_if
c_cond
(paren
id|v_error_skip_env_get
c_func
(paren
id|v
comma
id|error_env
)paren
op_ne
id|GRAPH_SUCCESS
)paren
(brace
id|error_env
op_assign
id|kmem_zalloc
c_func
(paren
r_sizeof
(paren
id|label_t
)paren
comma
id|KM_NOSLEEP
)paren
suffix:semicolon
multiline_comment|/* Unable to allocate memory for jum buffer. This should &n;&t;&t; * be a very rare occurrence.&t;&t;&t;&t; &n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|error_env
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Store the jump buffer information on the vertex.*/
r_if
c_cond
(paren
id|v_error_skip_env_set
c_func
(paren
id|v
comma
id|error_env
comma
l_int|0
)paren
op_ne
id|GRAPH_SUCCESS
)paren
r_return
op_minus
l_int|2
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|v_error_skip_env_get
c_func
(paren
id|v
comma
id|error_env
)paren
op_eq
id|GRAPH_SUCCESS
)paren
suffix:semicolon
id|code
op_assign
m_setjmp
(paren
op_star
id|error_env
)paren
suffix:semicolon
macro_line|#ifdef IRIX
multiline_comment|/* NOTE: It might be OK to leave the allocated jump buffer on the&n;&t; * vertex. This can be used for later purposes.&n;&t; */
r_if
c_cond
(paren
id|code
)paren
(brace
multiline_comment|/* This is the case where a long jump has been taken from one&n;&t;&t; * one of the error handling interfaces.&t;&t;     &n;&t;&t; */
r_if
c_cond
(paren
id|v_error_skip_env_clear
c_func
(paren
id|v
comma
id|error_env
)paren
op_eq
id|GRAPH_SUCCESS
)paren
id|kfree
c_func
(paren
id|error_env
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|code
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_SGI_IO_ERROR_HANDLING */
DECL|typedef|counter_t
r_typedef
r_uint64
id|counter_t
suffix:semicolon
r_extern
id|counter_t
id|error_retry_count_get
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_extern
id|error_return_code_t
id|error_retry_count_set
c_func
(paren
id|devfs_handle_t
comma
id|counter_t
)paren
suffix:semicolon
r_extern
id|counter_t
id|error_retry_count_increment
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_extern
id|counter_t
id|error_retry_count_decrement
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
multiline_comment|/* Except for the PIO Read error typically the other errors are handled in&n; * the context of an asynchronous error interrupt.&n; */
DECL|macro|IS_ERROR_INTR_CONTEXT
mdefine_line|#define&t;IS_ERROR_INTR_CONTEXT(_ec)&t;((_ec &amp; IOECODE_DMA) &t;&t;|| &bslash;&n;&t;&t;&t;&t;&t; (_ec == IOECODE_PIO_WRITE))
multiline_comment|/* Some convenience macros on device state. This state is accessed only &n; * thru the calls the io error handling layer.&n; */
macro_line|#if defined(CONFIG_SGI_IO_ERROR_HANDLING)
DECL|macro|IS_DEVICE_SHUTDOWN
mdefine_line|#define IS_DEVICE_SHUTDOWN(_d) &t;(error_state_get(_d) == ERROR_STATE_SHUTDOWN)
macro_line|#else
r_extern
id|boolean_t
id|is_device_shutdown
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
DECL|macro|IS_DEVICE_SHUTDOWN
mdefine_line|#define IS_DEVICE_SHUTDOWN(_d) &t;(is_device_shutdown(_d))
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_SN_IOERROR_HANDLING_H */
eof
