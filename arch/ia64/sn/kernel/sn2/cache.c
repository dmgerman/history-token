multiline_comment|/*&n; * &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; * &n; * Copyright (C) 2001-2002 Silicon Graphics, Inc. All rights reserved.&n; *&n; */
macro_line|#include &lt;asm/pgalloc.h&gt;
multiline_comment|/**&n; * sn_flush_all_caches - flush a range of address from all caches (incl. L4)&n; * @flush_addr: identity mapped region 7 address to start flushing&n; * @bytes: number of bytes to flush&n; *&n; * Flush a range of addresses from all caches including L4. &n; * All addresses fully or partially contained within &n; * @flush_addr to @flush_addr + @bytes are flushed&n; * from the all caches.&n; */
r_void
DECL|function|sn_flush_all_caches
id|sn_flush_all_caches
c_func
(paren
r_int
id|flush_addr
comma
r_int
id|bytes
)paren
(brace
id|flush_icache_range
c_func
(paren
id|flush_addr
comma
id|flush_addr
op_plus
id|bytes
)paren
suffix:semicolon
)brace
eof
