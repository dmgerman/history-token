multiline_comment|/*&n; * sleep.c - x86-specific ACPI sleep support.&n; *&n; *  Copyright (C) 2001-2003 Patrick Mochel&n; *  Copyright (C) 2001-2003 Pavel Machek &lt;pavel@suse.cz&gt;&n; */
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/* address in low memory of the wakeup routine. */
DECL|variable|acpi_wakeup_address
r_int
r_int
id|acpi_wakeup_address
op_assign
l_int|0
suffix:semicolon
DECL|variable|acpi_video_flags
r_int
r_int
id|acpi_video_flags
suffix:semicolon
r_extern
r_char
id|wakeup_start
comma
id|wakeup_end
suffix:semicolon
r_extern
r_void
id|zap_low_mappings
c_func
(paren
r_void
)paren
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
id|pgd_t
op_star
id|pgd
comma
r_int
id|pgd_limit
)paren
(brace
r_int
id|pgd_ofs
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|pgd_ofs
OL
id|pgd_limit
)paren
op_logical_and
(paren
id|pgd_ofs
op_plus
id|USER_PTRS_PER_PGD
OL
id|PTRS_PER_PGD
)paren
)paren
(brace
id|set_pgd
c_func
(paren
id|pgd
comma
op_star
(paren
id|pgd
op_plus
id|USER_PTRS_PER_PGD
)paren
)paren
suffix:semicolon
id|pgd_ofs
op_increment
comma
id|pgd
op_increment
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|acpi_wakeup_address
)paren
r_return
l_int|1
suffix:semicolon
id|init_low_mapping
c_func
(paren
id|swapper_pg_dir
comma
id|USER_PTRS_PER_PGD
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
multiline_comment|/*&n; * acpi_restore_state - undo effects of acpi_save_state_mem&n; */
DECL|function|acpi_restore_state_mem
r_void
id|acpi_restore_state_mem
(paren
r_void
)paren
(brace
id|zap_low_mappings
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_reserve_bootmem - do _very_ early ACPI initialisation&n; *&n; * We allocate a page from the first 1MB of memory for the wakeup&n; * routine for when we come back from a sleep state. The&n; * runtime allocator allows specification of &lt;16MB pages, but not&n; * &lt;1MB pages.&n; */
DECL|function|acpi_reserve_bootmem
r_void
id|__init
id|acpi_reserve_bootmem
c_func
(paren
r_void
)paren
(brace
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
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: Wakeup code way too big, S3 disabled.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
op_logical_neg
id|acpi_wakeup_address
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: Cannot allocate lowmem, S3 disabled.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|acpi_sleep_setup
r_static
r_int
id|__init
id|acpi_sleep_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_while
c_loop
(paren
(paren
id|str
op_ne
l_int|NULL
)paren
op_logical_and
(paren
op_star
id|str
op_ne
l_char|&squot;&bslash;0&squot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;s3_bios&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
id|acpi_video_flags
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;s3_mode&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
id|acpi_video_flags
op_or_assign
l_int|2
suffix:semicolon
id|str
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str
op_ne
l_int|NULL
)paren
id|str
op_add_assign
id|strspn
c_func
(paren
id|str
comma
l_string|&quot;, &bslash;t&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;acpi_sleep=&quot;
comma
id|acpi_sleep_setup
)paren
suffix:semicolon
eof
