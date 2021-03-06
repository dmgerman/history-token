multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 Keith M Wesolowski&n; * Copyright (C) 2005 Ilya A. Volynets (Total Knowledge)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/ip32/crime.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
r_extern
r_void
id|crime_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|prom_meminit
r_void
id|__init
id|prom_meminit
(paren
r_void
)paren
(brace
id|u64
id|base
comma
id|size
suffix:semicolon
r_int
id|bank
suffix:semicolon
id|crime_init
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|bank
op_assign
l_int|0
suffix:semicolon
id|bank
OL
id|CRIME_MAXBANKS
suffix:semicolon
id|bank
op_increment
)paren
(brace
id|u64
id|bankctl
op_assign
id|crime-&gt;bank_ctrl
(braket
id|bank
)braket
suffix:semicolon
id|base
op_assign
(paren
id|bankctl
op_amp
id|CRIME_MEM_BANK_CONTROL_ADDR
)paren
op_lshift
l_int|25
suffix:semicolon
r_if
c_cond
(paren
id|bank
op_ne
l_int|0
op_logical_and
id|base
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|size
op_assign
(paren
id|bankctl
op_amp
id|CRIME_MEM_BANK_CONTROL_SDRAM_SIZE
)paren
ques
c_cond
l_int|128
suffix:colon
l_int|32
suffix:semicolon
id|size
op_lshift_assign
l_int|20
suffix:semicolon
r_if
c_cond
(paren
id|base
op_plus
id|size
OG
(paren
l_int|256
op_lshift
l_int|20
)paren
)paren
id|base
op_add_assign
id|CRIME_HI_MEM_BASE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CRIME MC: bank %u base 0x%016lx size %luMB&bslash;n&quot;
comma
id|bank
comma
id|base
comma
id|size
)paren
suffix:semicolon
id|add_memory_region
(paren
id|base
comma
id|size
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
)brace
)brace
DECL|function|prom_free_prom_memory
r_int
r_int
id|__init
id|prom_free_prom_memory
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
