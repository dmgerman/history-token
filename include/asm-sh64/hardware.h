macro_line|#ifndef __ASM_SH64_HARDWARE_H
DECL|macro|__ASM_SH64_HARDWARE_H
mdefine_line|#define __ASM_SH64_HARDWARE_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/hardware.h&n; *&n; * Copyright (C) 2002 Stuart Menefy&n; * Copyright (C) 2003 Paul Mundt&n; *&n; * Defitions of the locations of registers in the physical address space.&n; */
DECL|macro|PHYS_PERIPHERAL_BLOCK
mdefine_line|#define&t;PHYS_PERIPHERAL_BLOCK&t;0x09000000
DECL|macro|PHYS_DMAC_BLOCK
mdefine_line|#define PHYS_DMAC_BLOCK&t;&t;0x0e000000
DECL|macro|PHYS_PCI_BLOCK
mdefine_line|#define PHYS_PCI_BLOCK&t;&t;0x60000000
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|struct|vcr_info
r_struct
id|vcr_info
(brace
DECL|member|perr_flags
id|u8
id|perr_flags
suffix:semicolon
multiline_comment|/* P-port Error flags */
DECL|member|merr_flags
id|u8
id|merr_flags
suffix:semicolon
multiline_comment|/* Module Error flags */
DECL|member|mod_vers
id|u16
id|mod_vers
suffix:semicolon
multiline_comment|/* Module Version */
DECL|member|mod_id
id|u16
id|mod_id
suffix:semicolon
multiline_comment|/* Module ID */
DECL|member|bot_mb
id|u8
id|bot_mb
suffix:semicolon
multiline_comment|/* Bottom Memory block */
DECL|member|top_mb
id|u8
id|top_mb
suffix:semicolon
multiline_comment|/* Top Memory block */
)brace
suffix:semicolon
DECL|function|sh64_get_vcr_info
r_static
r_inline
r_struct
id|vcr_info
id|sh64_get_vcr_info
c_func
(paren
r_int
r_int
id|base
)paren
(brace
r_int
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
id|sh64_in64
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
op_star
(paren
(paren
r_struct
id|vcr_info
op_star
)paren
op_amp
id|tmp
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_SH64_HARDWARE_H */
eof
