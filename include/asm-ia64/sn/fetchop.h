multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_FETCHOP_H
DECL|macro|_ASM_IA64_SN_FETCHOP_H
mdefine_line|#define _ASM_IA64_SN_FETCHOP_H
DECL|macro|FETCHOP_BASENAME
mdefine_line|#define FETCHOP_BASENAME&t;&quot;sgi_fetchop&quot;
DECL|macro|FETCHOP_FULLNAME
mdefine_line|#define FETCHOP_FULLNAME&t;&quot;/dev/sgi_fetchop&quot;
DECL|macro|FETCHOP_VAR_SIZE
mdefine_line|#define FETCHOP_VAR_SIZE 64 /* 64 byte per fetchop variable */
DECL|macro|FETCHOP_LOAD
mdefine_line|#define FETCHOP_LOAD&t;&t;0
DECL|macro|FETCHOP_INCREMENT
mdefine_line|#define FETCHOP_INCREMENT&t;8
DECL|macro|FETCHOP_DECREMENT
mdefine_line|#define FETCHOP_DECREMENT&t;16
DECL|macro|FETCHOP_CLEAR
mdefine_line|#define FETCHOP_CLEAR&t;&t;24
DECL|macro|FETCHOP_STORE
mdefine_line|#define FETCHOP_STORE&t;&t;0
DECL|macro|FETCHOP_AND
mdefine_line|#define FETCHOP_AND&t;&t;24
DECL|macro|FETCHOP_OR
mdefine_line|#define FETCHOP_OR&t;&t;32
DECL|macro|FETCHOP_CLEAR_CACHE
mdefine_line|#define FETCHOP_CLEAR_CACHE&t;56
DECL|macro|FETCHOP_LOAD_OP
mdefine_line|#define FETCHOP_LOAD_OP(addr, op) ( &bslash;&n;         *(long *)((char*) (addr) + (op)))
DECL|macro|FETCHOP_STORE_OP
mdefine_line|#define FETCHOP_STORE_OP(addr, op, x) ( &bslash;&n;         *(long *)((char*) (addr) + (op)) = &bslash;&n;              (long) (x))
macro_line|#endif /* _ASM_IA64_SN_FETCHOP_H */
eof
