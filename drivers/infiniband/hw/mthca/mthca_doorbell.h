multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: mthca_doorbell.h 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|MTHCA_RD_DOORBELL
mdefine_line|#define MTHCA_RD_DOORBELL      0x00
DECL|macro|MTHCA_SEND_DOORBELL
mdefine_line|#define MTHCA_SEND_DOORBELL    0x10
DECL|macro|MTHCA_RECEIVE_DOORBELL
mdefine_line|#define MTHCA_RECEIVE_DOORBELL 0x18
DECL|macro|MTHCA_CQ_DOORBELL
mdefine_line|#define MTHCA_CQ_DOORBELL      0x20
DECL|macro|MTHCA_EQ_DOORBELL
mdefine_line|#define MTHCA_EQ_DOORBELL      0x28
macro_line|#if BITS_PER_LONG == 64
multiline_comment|/*&n; * Assume that we can just write a 64-bit doorbell atomically.  s390&n; * actually doesn&squot;t have writeq() but S/390 systems don&squot;t even have&n; * PCI so we won&squot;t worry about it.&n; */
DECL|macro|MTHCA_DECLARE_DOORBELL_LOCK
mdefine_line|#define MTHCA_DECLARE_DOORBELL_LOCK(name)
DECL|macro|MTHCA_INIT_DOORBELL_LOCK
mdefine_line|#define MTHCA_INIT_DOORBELL_LOCK(ptr)    do { } while (0)
DECL|macro|MTHCA_GET_DOORBELL_LOCK
mdefine_line|#define MTHCA_GET_DOORBELL_LOCK(ptr)      (NULL)
DECL|function|mthca_write64
r_static
r_inline
r_void
id|mthca_write64
c_func
(paren
id|u32
id|val
(braket
l_int|2
)braket
comma
r_void
id|__iomem
op_star
id|dest
comma
id|spinlock_t
op_star
id|doorbell_lock
)paren
(brace
id|__raw_writeq
c_func
(paren
op_star
(paren
id|u64
op_star
)paren
id|val
comma
id|dest
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * Just fall back to a spinlock to protect the doorbell if&n; * BITS_PER_LONG is 32 -- there&squot;s no portable way to do atomic 64-bit&n; * MMIO writes.&n; */
DECL|macro|MTHCA_DECLARE_DOORBELL_LOCK
mdefine_line|#define MTHCA_DECLARE_DOORBELL_LOCK(name) spinlock_t name;
DECL|macro|MTHCA_INIT_DOORBELL_LOCK
mdefine_line|#define MTHCA_INIT_DOORBELL_LOCK(ptr)     spin_lock_init(ptr)
DECL|macro|MTHCA_GET_DOORBELL_LOCK
mdefine_line|#define MTHCA_GET_DOORBELL_LOCK(ptr)      (ptr)
DECL|function|mthca_write64
r_static
r_inline
r_void
id|mthca_write64
c_func
(paren
id|u32
id|val
(braket
l_int|2
)braket
comma
r_void
id|__iomem
op_star
id|dest
comma
id|spinlock_t
op_star
id|doorbell_lock
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|doorbell_lock
comma
id|flags
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|val
(braket
l_int|0
)braket
comma
id|dest
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|val
(braket
l_int|1
)braket
comma
id|dest
op_plus
l_int|4
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|doorbell_lock
comma
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
