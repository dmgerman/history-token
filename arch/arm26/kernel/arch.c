multiline_comment|/* &n; *  linux/arch/arm/kernel/arch.c&n; *&n; *  Architecture specific fixups.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|variable|vram_size
r_int
r_int
id|vram_size
suffix:semicolon
DECL|variable|memc_ctrl_reg
r_int
r_int
id|memc_ctrl_reg
suffix:semicolon
DECL|variable|number_mfm_drives
r_int
r_int
id|number_mfm_drives
suffix:semicolon
DECL|function|parse_tag_acorn
r_static
r_int
id|__init
id|parse_tag_acorn
c_func
(paren
r_const
r_struct
id|tag
op_star
id|tag
)paren
(brace
id|memc_ctrl_reg
op_assign
id|tag-&gt;u.acorn.memc_control_reg
suffix:semicolon
id|number_mfm_drives
op_assign
id|tag-&gt;u.acorn.adfsdrives
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__tagtable
c_func
(paren
id|ATAG_ACORN
comma
id|parse_tag_acorn
)paren
suffix:semicolon
eof
