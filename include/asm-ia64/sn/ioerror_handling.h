multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_IOERROR_HANDLING_H
DECL|macro|_ASM_IA64_SN_IOERROR_HANDLING_H
mdefine_line|#define _ASM_IA64_SN_IOERROR_HANDLING_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IA64_SN_IOERROR_HANDLING_H */
eof
