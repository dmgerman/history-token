multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001-2003 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_FETCHOP_H
DECL|macro|_ASM_IA64_SN_FETCHOP_H
mdefine_line|#define _ASM_IA64_SN_FETCHOP_H
macro_line|#include &lt;linux/config.h&gt;
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
mdefine_line|#define FETCHOP_LOAD_OP(addr, op) ( &bslash;&n;         *(volatile long *)((char*) (addr) + (op)))
DECL|macro|FETCHOP_STORE_OP
mdefine_line|#define FETCHOP_STORE_OP(addr, op, x) ( &bslash;&n;         *(volatile long *)((char*) (addr) + (op)) = (long) (x))
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Convert a region 6 (kaddr) address to the address of the fetchop variable&n; */
DECL|macro|FETCHOP_KADDR_TO_MSPEC_ADDR
mdefine_line|#define FETCHOP_KADDR_TO_MSPEC_ADDR(kaddr)&t;TO_MSPEC(kaddr)
multiline_comment|/*&n; * Each Atomic Memory Operation (AMO formerly known as fetchop)&n; * variable is 64 bytes long.  The first 8 bytes are used.  The&n; * remaining 56 bytes are unaddressable due to the operation taking&n; * that portion of the address.&n; * &n; * NOTE: The AMO_t _MUST_ be placed in either the first or second half&n; * of the cache line.  The cache line _MUST NOT_ be used for anything&n; * other than additional AMO_t entries.  This is because there are two&n; * addresses which reference the same physical cache line.  One will&n; * be a cached entry with the memory type bits all set.  This address&n; * may be loaded into processor cache.  The AMO_t will be referenced&n; * uncached via the memory special memory type.  If any portion of the&n; * cached cache-line is modified, when that line is flushed, it will&n; * overwrite the uncached value in physical memory and lead to&n; * inconsistency.&n; */
r_typedef
r_struct
(brace
DECL|member|variable
id|u64
id|variable
suffix:semicolon
DECL|member|unused
id|u64
id|unused
(braket
l_int|7
)braket
suffix:semicolon
DECL|typedef|AMO_t
)brace
id|AMO_t
suffix:semicolon
multiline_comment|/*&n; * The following APIs are externalized to the kernel to allocate/free fetchop variables.&n; * &t;fetchop_kalloc_one&t;- Allocate/initialize 1 fetchop variable on the specified cnode.&n; * &t;fetchop_kfree_one&t;- Free a previously allocated fetchop variable &n; */
r_int
r_int
id|fetchop_kalloc_one
c_func
(paren
r_int
id|nid
)paren
suffix:semicolon
r_void
id|fetchop_kfree_one
c_func
(paren
r_int
r_int
id|maddr
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IA64_SN_FETCHOP_H */
eof
