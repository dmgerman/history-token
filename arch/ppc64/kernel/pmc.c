multiline_comment|/*&n; * pmc.c&n; * Copyright (C) 2001 Dave Engebretsen &amp; Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/* Change Activity:&n; * 2001/06/05 : engebret : Created.&n; * End Change Activity &n; */
macro_line|#include &lt;asm/proc_fs.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/pmc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
DECL|variable|pmc_sw_system
r_struct
id|_pmc_sw
id|pmc_sw_system
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|pmc_sw_cpu
r_struct
id|_pmc_sw
id|pmc_sw_cpu
(braket
id|NR_CPUS
)braket
op_assign
(brace
(brace
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Provide enough storage for either system level counters or&n; * one cpu&squot;s counters.&n; */
DECL|variable|pmc_sw_text
r_struct
id|_pmc_sw_text
id|pmc_sw_text
suffix:semicolon
DECL|variable|pmc_hw_text
r_struct
id|_pmc_hw_text
id|pmc_hw_text
suffix:semicolon
r_char
op_star
DECL|function|ppc64_pmc_stab
id|ppc64_pmc_stab
c_func
(paren
r_int
id|file
)paren
(brace
r_int
id|n
suffix:semicolon
r_int
r_int
id|stab_faults
comma
id|stab_capacity_castouts
comma
id|stab_invalidations
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|stab_faults
op_assign
id|stab_capacity_castouts
op_assign
id|stab_invalidations
op_assign
id|n
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|file
op_eq
op_minus
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
(brace
id|stab_faults
op_add_assign
id|pmc_sw_cpu
(braket
id|i
)braket
dot
id|stab_faults
suffix:semicolon
id|stab_capacity_castouts
op_add_assign
id|pmc_sw_cpu
(braket
id|i
)braket
dot
id|stab_capacity_castouts
suffix:semicolon
id|stab_invalidations
op_add_assign
id|pmc_sw_cpu
(braket
id|i
)braket
dot
id|stab_invalidations
suffix:semicolon
)brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Faults         0x%lx&bslash;n&quot;
comma
id|stab_faults
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Castouts       0x%lx&bslash;n&quot;
comma
id|stab_capacity_castouts
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Invalidations  0x%lx&bslash;n&quot;
comma
id|stab_invalidations
)paren
suffix:semicolon
)brace
r_else
(brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Faults         0x%lx&bslash;n&quot;
comma
id|pmc_sw_cpu
(braket
id|file
)braket
dot
id|stab_faults
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Castouts       0x%lx&bslash;n&quot;
comma
id|pmc_sw_cpu
(braket
id|file
)braket
dot
id|stab_capacity_castouts
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Invalidations  0x%lx&bslash;n&quot;
comma
id|pmc_sw_cpu
(braket
id|file
)braket
dot
id|stab_invalidations
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|STAB_ENTRY_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pmc_sw_cpu
(braket
id|file
)braket
dot
id|stab_entry_use
(braket
id|i
)braket
)paren
(brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Entry %02ld       0x%lx&bslash;n&quot;
comma
id|i
comma
id|pmc_sw_cpu
(braket
id|file
)braket
dot
id|stab_entry_use
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|pmc_sw_text.buffer
suffix:semicolon
)brace
r_char
op_star
DECL|function|ppc64_pmc_htab
id|ppc64_pmc_htab
c_func
(paren
r_int
id|file
)paren
(brace
r_int
id|n
suffix:semicolon
r_int
r_int
id|htab_primary_overflows
comma
id|htab_capacity_castouts
suffix:semicolon
r_int
r_int
id|htab_read_to_write_faults
suffix:semicolon
id|htab_primary_overflows
op_assign
id|htab_capacity_castouts
op_assign
l_int|0
suffix:semicolon
id|htab_read_to_write_faults
op_assign
id|n
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|file
op_eq
op_minus
l_int|1
)paren
(brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Primary Overflows  0x%lx&bslash;n&quot;
comma
id|pmc_sw_system.htab_primary_overflows
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Castouts           0x%lx&bslash;n&quot;
comma
id|pmc_sw_system.htab_capacity_castouts
)paren
suffix:semicolon
)brace
r_else
(brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Primary Overflows  N/A&bslash;n&quot;
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_sw_text.buffer
op_plus
id|n
comma
l_string|&quot;Castouts           N/A&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|pmc_sw_text.buffer
suffix:semicolon
)brace
r_char
op_star
DECL|function|ppc64_pmc_hw
id|ppc64_pmc_hw
c_func
(paren
r_int
id|file
)paren
(brace
r_int
id|n
suffix:semicolon
id|n
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|file
op_eq
op_minus
l_int|1
)paren
(brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;Not Implemented&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;MMCR0  0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|MMCR0
)paren
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;MMCR1  0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|MMCR1
)paren
)paren
suffix:semicolon
macro_line|#if 0
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;MMCRA  0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|MMCRA
)paren
)paren
suffix:semicolon
macro_line|#endif
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;PMC1   0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|PMC1
)paren
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;PMC2   0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|PMC2
)paren
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;PMC3   0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|PMC3
)paren
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;PMC4   0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|PMC4
)paren
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;PMC5   0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|PMC5
)paren
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;PMC6   0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|PMC6
)paren
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;PMC7   0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|PMC7
)paren
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|pmc_hw_text.buffer
op_plus
id|n
comma
l_string|&quot;PMC8   0x%lx&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|PMC8
)paren
)paren
suffix:semicolon
)brace
r_return
id|pmc_hw_text.buffer
suffix:semicolon
)brace
eof
