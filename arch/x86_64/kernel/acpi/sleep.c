multiline_comment|/*&n; *  acpi.c - Architecture-Specific Low-Level ACPI Support&n; *&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *  Copyright (C) 2001 Jun Nakajima &lt;jun.nakajima@intel.com&gt;&n; *  Copyright (C) 2001 Patrick Mochel &lt;mochel@osdl.org&gt;&n; *  Copyright (C) 2002 Andi Kleen, SuSE Labs (x86-64 port)&n; *  Copyright (C) 2003 Pavel Machek, SuSE Labs&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;asm/apicdef.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/io_apic.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/* --------------------------------------------------------------------------&n;                              Low-Level Sleep Support&n;   -------------------------------------------------------------------------- */
macro_line|#ifdef CONFIG_ACPI_SLEEP
multiline_comment|/* address in low memory of the wakeup routine. */
DECL|variable|acpi_wakeup_address
r_int
r_int
id|acpi_wakeup_address
op_assign
l_int|0
suffix:semicolon
r_extern
r_char
id|wakeup_start
comma
id|wakeup_end
suffix:semicolon
r_extern
r_int
r_int
id|FASTCALL
c_func
(paren
id|acpi_copy_wakeup_routine
c_func
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
DECL|function|init_low_mapping
r_static
r_void
id|init_low_mapping
c_func
(paren
r_void
)paren
(brace
id|cpu_pda
(braket
l_int|0
)braket
dot
id|level4_pgt
(braket
l_int|0
)braket
op_assign
id|cpu_pda
(braket
l_int|0
)braket
dot
id|level4_pgt
(braket
id|pml4_index
c_func
(paren
id|PAGE_OFFSET
)paren
)braket
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_save_state_mem - save kernel state&n; *&n; * Create an identity mapped page table and copy the wakeup routine to&n; * low memory.&n; */
DECL|function|acpi_save_state_mem
r_int
id|acpi_save_state_mem
(paren
r_void
)paren
(brace
id|init_low_mapping
c_func
(paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|acpi_wakeup_address
comma
op_amp
id|wakeup_start
comma
op_amp
id|wakeup_end
op_minus
op_amp
id|wakeup_start
)paren
suffix:semicolon
id|acpi_copy_wakeup_routine
c_func
(paren
id|acpi_wakeup_address
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_save_state_disk - save kernel state to disk&n; *&n; */
DECL|function|acpi_save_state_disk
r_int
id|acpi_save_state_disk
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * acpi_restore_state&n; */
DECL|function|acpi_restore_state_mem
r_void
id|acpi_restore_state_mem
(paren
r_void
)paren
(brace
id|cpu_pda
(braket
l_int|0
)braket
dot
id|level4_pgt
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_reserve_bootmem - do _very_ early ACPI initialisation&n; *&n; * We allocate a page in low memory for the wakeup&n; * routine for when we come back from a sleep state. The&n; * runtime allocator allows specification of &lt;16M pages, but not&n; * &lt;1M pages.&n; */
DECL|function|acpi_reserve_bootmem
r_void
id|__init
id|acpi_reserve_bootmem
c_func
(paren
r_void
)paren
(brace
id|acpi_wakeup_address
op_assign
(paren
r_int
r_int
)paren
id|alloc_bootmem_low
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_amp
id|wakeup_end
op_minus
op_amp
id|wakeup_start
)paren
OG
id|PAGE_SIZE
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ACPI: Wakeup code way too big, will crash on attempt to suspend&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ACPI: have wakeup address 0x%8.8lx&bslash;n&quot;
comma
id|acpi_wakeup_address
)paren
suffix:semicolon
)brace
macro_line|#endif /*CONFIG_ACPI_SLEEP*/
DECL|function|acpi_pci_link_exit
r_void
id|acpi_pci_link_exit
c_func
(paren
r_void
)paren
(brace
)brace
eof
