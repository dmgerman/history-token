multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_VECTOR_H
DECL|macro|_ASM_IA64_SN_VECTOR_H
mdefine_line|#define _ASM_IA64_SN_VECTOR_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|NET_VEC_NULL
mdefine_line|#define NET_VEC_NULL            ((net_vec_t)  0)
DECL|macro|NET_VEC_BAD
mdefine_line|#define NET_VEC_BAD             ((net_vec_t) -1)
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
DECL|macro|NET_ERROR_NONE
mdefine_line|#define NET_ERROR_NONE&t;&t;0&t;/* No error&t;&t;*/
DECL|macro|NET_ERROR_HARDWARE
mdefine_line|#define NET_ERROR_HARDWARE&t;(-1)&t;/* Hardware error&t;*/
DECL|macro|NET_ERROR_OVERRUN
mdefine_line|#define NET_ERROR_OVERRUN&t;(-2)&t;/* Extra response(s)&t;*/
DECL|macro|NET_ERROR_REPLY
mdefine_line|#define NET_ERROR_REPLY&t;&t;(-3)&t;/* Reply parms mismatch */
DECL|macro|NET_ERROR_ADDRESS
mdefine_line|#define NET_ERROR_ADDRESS&t;(-4)&t;/* Addr error response&t;*/
DECL|macro|NET_ERROR_COMMAND
mdefine_line|#define NET_ERROR_COMMAND&t;(-5)&t;/* Cmd error response&t;*/
DECL|macro|NET_ERROR_PROT
mdefine_line|#define NET_ERROR_PROT&t;&t;(-6)&t;/* Prot error response&t;*/
DECL|macro|NET_ERROR_TIMEOUT
mdefine_line|#define NET_ERROR_TIMEOUT&t;(-7)&t;/* Too many retries&t;*/
DECL|macro|NET_ERROR_VECTOR
mdefine_line|#define NET_ERROR_VECTOR&t;(-8)&t;/* Invalid vector/path&t;*/
DECL|macro|NET_ERROR_ROUTERLOCK
mdefine_line|#define NET_ERROR_ROUTERLOCK&t;(-9)&t;/* Timeout locking rtr&t;*/
DECL|macro|NET_ERROR_INVAL
mdefine_line|#define NET_ERROR_INVAL&t;&t;(-10)&t;/* Invalid vector request */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
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
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_SN_VECTOR_H */
eof
