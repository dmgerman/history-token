multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1997, 1999 by Ralf Baechle&n; * Copyright (c) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_BCACHE_H
DECL|macro|_ASM_BCACHE_H
mdefine_line|#define _ASM_BCACHE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Some R4000 / R4400 / R4600 / R5000 machines may have a non-dma-coherent,&n;   chipset implemented caches.  On machines with other CPUs the CPU does the&n;   cache thing itself. */
DECL|struct|bcache_ops
r_struct
id|bcache_ops
(brace
DECL|member|bc_enable
r_void
(paren
op_star
id|bc_enable
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|bc_disable
r_void
(paren
op_star
id|bc_disable
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|bc_wback_inv
r_void
(paren
op_star
id|bc_wback_inv
)paren
(paren
r_int
r_int
id|page
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|bc_inv
r_void
(paren
op_star
id|bc_inv
)paren
(paren
r_int
r_int
id|page
comma
r_int
r_int
id|size
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|indy_sc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sni_pcimt_sc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BOARD_SCACHE
r_extern
r_struct
id|bcache_ops
op_star
id|bcops
suffix:semicolon
DECL|function|bc_enable
r_static
r_inline
r_void
id|bc_enable
c_func
(paren
r_void
)paren
(brace
id|bcops
op_member_access_from_pointer
id|bc_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|bc_disable
r_static
r_inline
r_void
id|bc_disable
c_func
(paren
r_void
)paren
(brace
id|bcops
op_member_access_from_pointer
id|bc_disable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|bc_wback_inv
r_static
r_inline
r_void
id|bc_wback_inv
c_func
(paren
r_int
r_int
id|page
comma
r_int
r_int
id|size
)paren
(brace
id|bcops
op_member_access_from_pointer
id|bc_wback_inv
c_func
(paren
id|page
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|bc_inv
r_static
r_inline
r_void
id|bc_inv
c_func
(paren
r_int
r_int
id|page
comma
r_int
r_int
id|size
)paren
(brace
id|bcops
op_member_access_from_pointer
id|bc_inv
c_func
(paren
id|page
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#else /* !defined(CONFIG_BOARD_SCACHE) */
multiline_comment|/* Not R4000 / R4400 / R4600 / R5000.  */
DECL|macro|bc_enable
mdefine_line|#define bc_enable() do { } while (0)
DECL|macro|bc_disable
mdefine_line|#define bc_disable() do { } while (0)
DECL|macro|bc_wback_inv
mdefine_line|#define bc_wback_inv(page, size) do { } while (0)
DECL|macro|bc_inv
mdefine_line|#define bc_inv(page, size) do { } while (0)
macro_line|#endif /* !defined(CONFIG_BOARD_SCACHE) */
macro_line|#endif /* _ASM_BCACHE_H */
eof
