multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_VECTOR_H
DECL|macro|_ASM_SN_VECTOR_H
mdefine_line|#define _ASM_SN_VECTOR_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|NET_VEC_NULL
mdefine_line|#define NET_VEC_NULL            ((net_vec_t)  0)
DECL|macro|NET_VEC_BAD
mdefine_line|#define NET_VEC_BAD             ((net_vec_t) -1)
macro_line|#ifdef RTL
DECL|macro|VEC_POLLS_W
mdefine_line|#define VEC_POLLS_W&t;&t;16&t;/* Polls before write times out */
DECL|macro|VEC_POLLS_R
mdefine_line|#define VEC_POLLS_R&t;&t;16&t;/* Polls before read times out */
DECL|macro|VEC_POLLS_X
mdefine_line|#define VEC_POLLS_X&t;&t;16&t;/* Polls before exch times out */
DECL|macro|VEC_RETRIES_W
mdefine_line|#define VEC_RETRIES_W&t;&t;1&t;/* Retries before write fails */
DECL|macro|VEC_RETRIES_R
mdefine_line|#define VEC_RETRIES_R&t;&t;1&t;/* Retries before read fails */
DECL|macro|VEC_RETRIES_X
mdefine_line|#define VEC_RETRIES_X&t;&t;1&t;/* Retries before exch fails */
macro_line|#else /* RTL */
DECL|macro|VEC_POLLS_W
mdefine_line|#define VEC_POLLS_W&t;&t;128&t;/* Polls before write times out */
DECL|macro|VEC_POLLS_R
mdefine_line|#define VEC_POLLS_R&t;&t;128&t;/* Polls before read times out */
DECL|macro|VEC_POLLS_X
mdefine_line|#define VEC_POLLS_X&t;&t;128&t;/* Polls before exch times out */
DECL|macro|VEC_RETRIES_W
mdefine_line|#define VEC_RETRIES_W&t;&t;8&t;/* Retries before write fails */
DECL|macro|VEC_RETRIES_R
mdefine_line|#define VEC_RETRIES_R           8&t;/* Retries before read fails */
DECL|macro|VEC_RETRIES_X
mdefine_line|#define VEC_RETRIES_X&t;&t;4&t;/* Retries before exch fails */
macro_line|#endif /* RTL */
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
DECL|macro|VECTOR_PARMS
mdefine_line|#define VECTOR_PARMS&t;&t;LB_VECTOR_PARMS
DECL|macro|VECTOR_ROUTE
mdefine_line|#define VECTOR_ROUTE&t;&t;LB_VECTOR_ROUTE
DECL|macro|VECTOR_DATA
mdefine_line|#define VECTOR_DATA&t;&t;LB_VECTOR_DATA
DECL|macro|VECTOR_STATUS
mdefine_line|#define VECTOR_STATUS&t;&t;LB_VECTOR_STATUS
DECL|macro|VECTOR_RETURN
mdefine_line|#define VECTOR_RETURN&t;&t;LB_VECTOR_RETURN
DECL|macro|VECTOR_READ_DATA
mdefine_line|#define VECTOR_READ_DATA&t;LB_VECTOR_READ_DATA
DECL|macro|VECTOR_STATUS_CLEAR
mdefine_line|#define VECTOR_STATUS_CLEAR&t;LB_VECTOR_STATUS_CLEAR
DECL|macro|VP_PIOID_SHFT
mdefine_line|#define VP_PIOID_SHFT&t;&t;LVP_PIOID_SHFT
DECL|macro|VP_PIOID_MASK
mdefine_line|#define VP_PIOID_MASK&t;&t;LVP_PIOID_MASK
DECL|macro|VP_WRITEID_SHFT
mdefine_line|#define VP_WRITEID_SHFT&t;&t;LVP_WRITEID_SHFT
DECL|macro|VP_WRITEID_MASK
mdefine_line|#define VP_WRITEID_MASK&t;&t;LVP_WRITEID_MASK
DECL|macro|VP_ADDRESS_MASK
mdefine_line|#define VP_ADDRESS_MASK&t;&t;LVP_ADDRESS_MASK
DECL|macro|VP_TYPE_SHFT
mdefine_line|#define VP_TYPE_SHFT&t;&t;LVP_TYPE_SHFT
DECL|macro|VP_TYPE_MASK
mdefine_line|#define VP_TYPE_MASK&t;&t;LVP_TYPE_MASK
DECL|macro|VS_VALID
mdefine_line|#define VS_VALID&t;&t;LVS_VALID
DECL|macro|VS_OVERRUN
mdefine_line|#define VS_OVERRUN&t;&t;LVS_OVERRUN
DECL|macro|VS_TARGET_SHFT
mdefine_line|#define VS_TARGET_SHFT&t;&t;LVS_TARGET_SHFT
DECL|macro|VS_TARGET_MASK
mdefine_line|#define VS_TARGET_MASK&t;&t;LVS_TARGET_MASK
DECL|macro|VS_PIOID_SHFT
mdefine_line|#define VS_PIOID_SHFT&t;&t;LVS_PIOID_SHFT
DECL|macro|VS_PIOID_MASK
mdefine_line|#define VS_PIOID_MASK&t;&t;LVS_PIOID_MASK
DECL|macro|VS_WRITEID_SHFT
mdefine_line|#define VS_WRITEID_SHFT&t;&t;LVS_WRITEID_SHFT
DECL|macro|VS_WRITEID_MASK
mdefine_line|#define VS_WRITEID_MASK&t;&t;LVS_WRITEID_MASK
DECL|macro|VS_ADDRESS_MASK
mdefine_line|#define VS_ADDRESS_MASK&t;&t;LVS_ADDRESS_MASK
DECL|macro|VS_TYPE_SHFT
mdefine_line|#define VS_TYPE_SHFT&t;&t;LVS_TYPE_SHFT
DECL|macro|VS_TYPE_MASK
mdefine_line|#define VS_TYPE_MASK&t;&t;LVS_TYPE_MASK
DECL|macro|VS_ERROR_MASK
mdefine_line|#define VS_ERROR_MASK&t;&t;LVS_ERROR_MASK
macro_line|#endif
DECL|macro|NET_ERROR_NONE
mdefine_line|#define NET_ERROR_NONE          0       /* No error             */
DECL|macro|NET_ERROR_HARDWARE
mdefine_line|#define NET_ERROR_HARDWARE     -1       /* Hardware error       */
DECL|macro|NET_ERROR_OVERRUN
mdefine_line|#define NET_ERROR_OVERRUN      -2       /* Extra response(s)    */
DECL|macro|NET_ERROR_REPLY
mdefine_line|#define NET_ERROR_REPLY        -3       /* Reply parms mismatch */
DECL|macro|NET_ERROR_ADDRESS
mdefine_line|#define NET_ERROR_ADDRESS      -4       /* Addr error response  */
DECL|macro|NET_ERROR_COMMAND
mdefine_line|#define NET_ERROR_COMMAND      -5       /* Cmd error response   */
DECL|macro|NET_ERROR_PROT
mdefine_line|#define NET_ERROR_PROT         -6       /* Prot error response  */
DECL|macro|NET_ERROR_TIMEOUT
mdefine_line|#define NET_ERROR_TIMEOUT      -7       /* Too many retries     */
DECL|macro|NET_ERROR_VECTOR
mdefine_line|#define NET_ERROR_VECTOR       -8       /* Invalid vector/path  */
DECL|macro|NET_ERROR_ROUTERLOCK
mdefine_line|#define NET_ERROR_ROUTERLOCK   -9       /* Timeout locking rtr  */
DECL|macro|NET_ERROR_INVAL
mdefine_line|#define NET_ERROR_INVAL&t;       -10&t;/* Invalid vector request */
macro_line|#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
DECL|typedef|net_reg_t
r_typedef
r_uint64
id|net_reg_t
suffix:semicolon
DECL|typedef|net_vec_t
r_typedef
r_uint64
id|net_vec_t
suffix:semicolon
r_int
id|vector_write
c_func
(paren
id|net_vec_t
id|dest
comma
r_int
id|write_id
comma
r_int
id|address
comma
r_uint64
id|value
)paren
suffix:semicolon
r_int
id|vector_read
c_func
(paren
id|net_vec_t
id|dest
comma
r_int
id|write_id
comma
r_int
id|address
comma
r_uint64
op_star
id|value
)paren
suffix:semicolon
r_int
id|vector_write_node
c_func
(paren
id|net_vec_t
id|dest
comma
id|nasid_t
id|nasid
comma
r_int
id|write_id
comma
r_int
id|address
comma
r_uint64
id|value
)paren
suffix:semicolon
r_int
id|vector_read_node
c_func
(paren
id|net_vec_t
id|dest
comma
id|nasid_t
id|nasid
comma
r_int
id|write_id
comma
r_int
id|address
comma
r_uint64
op_star
id|value
)paren
suffix:semicolon
r_int
id|vector_length
c_func
(paren
id|net_vec_t
id|vec
)paren
suffix:semicolon
id|net_vec_t
id|vector_get
c_func
(paren
id|net_vec_t
id|vec
comma
r_int
id|n
)paren
suffix:semicolon
id|net_vec_t
id|vector_prefix
c_func
(paren
id|net_vec_t
id|vec
comma
r_int
id|n
)paren
suffix:semicolon
id|net_vec_t
id|vector_modify
c_func
(paren
id|net_vec_t
id|entry
comma
r_int
id|n
comma
r_int
id|route
)paren
suffix:semicolon
id|net_vec_t
id|vector_reverse
c_func
(paren
id|net_vec_t
id|vec
)paren
suffix:semicolon
id|net_vec_t
id|vector_concat
c_func
(paren
id|net_vec_t
id|vec1
comma
id|net_vec_t
id|vec2
)paren
suffix:semicolon
r_char
op_star
id|net_errmsg
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#ifndef _STANDALONE
r_int
id|hub_vector_write
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|net_vec_t
id|vector
comma
r_int
id|writeid
comma
r_int
id|addr
comma
id|net_reg_t
id|value
)paren
suffix:semicolon
r_int
id|hub_vector_read
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|net_vec_t
id|vector
comma
r_int
id|writeid
comma
r_int
id|addr
comma
id|net_reg_t
op_star
id|value
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _LANGUAGE_C || _LANGUAGE_C_PLUS_PLUS */
macro_line|#endif /* _ASM_SN_VECTOR_H */
eof
