multiline_comment|/*&n; * Architecture-specific setup.&n; *&n; * Copyright (C) 1998-2001 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; * Copyright (C) 2000, Rohit Seth &lt;rohit.seth@intel.com&gt;&n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *&n; * 11/12/01 D.Mosberger Convert get_cpuinfo() to seq_file based show_cpuinfo().&n; * 04/04/00 D.Mosberger renamed cpu_initialized to cpu_online_map&n; * 03/31/00 R.Seth&t;cpu_initialized and current-&gt;processor fixes&n; * 02/04/00 D.Mosberger&t;some more get_cpuinfo fixes...&n; * 02/01/00 R.Seth&t;fixed get_cpuinfo for SMP&n; * 01/07/99 S.Eranian&t;added the support for command line argument&n; * 06/24/99 W.Drummond&t;added boot_cpu_data.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/mca.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|# include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_SMP) &amp;&amp; (IA64_CPU_SIZE &gt; PAGE_SIZE)
macro_line|# error &quot;struct cpuinfo_ia64 too big!&quot;
macro_line|#endif
DECL|macro|MIN
mdefine_line|#define MIN(a,b)&t;((a) &lt; (b) ? (a) : (b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b)&t;((a) &gt; (b) ? (a) : (b))
r_extern
r_char
id|_end
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|variable|__per_cpu_offset
r_int
r_int
id|__per_cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif
DECL|variable|__per_cpu_data
r_struct
id|cpuinfo_ia64
id|cpu_info
id|__per_cpu_data
suffix:semicolon
DECL|variable|ia64_phys_stacked_size_p8
r_int
r_int
id|ia64_phys_stacked_size_p8
suffix:semicolon
DECL|variable|ia64_cycles_per_usec
r_int
r_int
id|ia64_cycles_per_usec
suffix:semicolon
DECL|variable|ia64_boot_param
r_struct
id|ia64_boot_param
op_star
id|ia64_boot_param
suffix:semicolon
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
suffix:semicolon
DECL|variable|ia64_iobase
r_int
r_int
id|ia64_iobase
suffix:semicolon
multiline_comment|/* virtual address for I/O accesses */
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
op_assign
l_int|0xaa
suffix:semicolon
multiline_comment|/* XXX remove this when legacy I/O is gone */
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE&t;512
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
multiline_comment|/* used in proc filesystem */
multiline_comment|/*&n; * Entries defined so far:&n; * &t;- boot param structure itself&n; * &t;- memory map&n; * &t;- initrd (optional)&n; * &t;- command line string&n; * &t;- kernel code &amp; data&n; *&n; * More could be added if necessary&n; */
DECL|macro|IA64_MAX_RSVD_REGIONS
mdefine_line|#define IA64_MAX_RSVD_REGIONS 5
DECL|struct|rsvd_region
r_struct
id|rsvd_region
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* virtual address of beginning of element */
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
multiline_comment|/* virtual address of end of element + 1 */
)brace
suffix:semicolon
multiline_comment|/*&n; * We use a special marker for the end of memory and it uses the extra (+1) slot&n; */
DECL|variable|rsvd_region
r_static
r_struct
id|rsvd_region
id|rsvd_region
(braket
id|IA64_MAX_RSVD_REGIONS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|num_rsvd_regions
r_static
r_int
id|num_rsvd_regions
suffix:semicolon
DECL|variable|bootmap_start
r_static
r_int
r_int
id|bootmap_start
suffix:semicolon
multiline_comment|/* physical address where the bootmem map is located */
r_static
r_int
DECL|function|find_max_pfn
id|find_max_pfn
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
op_star
id|max_pfn
op_assign
id|arg
comma
id|pfn
suffix:semicolon
id|pfn
op_assign
(paren
id|PAGE_ALIGN
c_func
(paren
id|end
op_minus
l_int|1
)paren
op_minus
id|PAGE_OFFSET
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|pfn
OG
op_star
id|max_pfn
)paren
op_star
id|max_pfn
op_assign
id|pfn
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|IGNORE_PFN0
mdefine_line|#define IGNORE_PFN0&t;1&t;/* XXX fix me: ignore pfn 0 until TLB miss handler is updated... */
multiline_comment|/*&n; * Free available memory based on the primitive map created from&n; * the boot parameters. This routine does not assume the incoming&n; * segments are sorted.&n; */
r_static
r_int
DECL|function|free_available_memory
id|free_available_memory
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
id|range_start
comma
id|range_end
comma
id|prev_start
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#if IGNORE_PFN0
r_if
c_cond
(paren
id|start
op_eq
id|PAGE_OFFSET
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;warning: skipping physical page 0&bslash;n&quot;
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * lowest possible address(walker uses virtual)&n;&t; */
id|prev_start
op_assign
id|PAGE_OFFSET
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
id|num_rsvd_regions
suffix:semicolon
op_increment
id|i
)paren
(brace
id|range_start
op_assign
id|MAX
c_func
(paren
id|start
comma
id|prev_start
)paren
suffix:semicolon
id|range_end
op_assign
id|MIN
c_func
(paren
id|end
comma
id|rsvd_region
(braket
id|i
)braket
dot
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|range_start
OL
id|range_end
)paren
id|free_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|range_start
)paren
comma
id|range_end
op_minus
id|range_start
)paren
suffix:semicolon
multiline_comment|/* nothing more available in this segment */
r_if
c_cond
(paren
id|range_end
op_eq
id|end
)paren
r_return
l_int|0
suffix:semicolon
id|prev_start
op_assign
id|rsvd_region
(braket
id|i
)braket
dot
id|end
suffix:semicolon
)brace
multiline_comment|/* end of memory marker allows full processing inside loop body */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Find a place to put the bootmap and return its starting address in bootmap_start.&n; * This address must be page-aligned.&n; */
r_static
r_int
DECL|function|find_bootmap_location
id|find_bootmap_location
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
id|needed
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|arg
suffix:semicolon
r_int
r_int
id|range_start
comma
id|range_end
comma
id|free_start
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#if IGNORE_PFN0
r_if
c_cond
(paren
id|start
op_eq
id|PAGE_OFFSET
)paren
(brace
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|free_start
op_assign
id|PAGE_OFFSET
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
id|num_rsvd_regions
suffix:semicolon
id|i
op_increment
)paren
(brace
id|range_start
op_assign
id|MAX
c_func
(paren
id|start
comma
id|free_start
)paren
suffix:semicolon
id|range_end
op_assign
id|MIN
c_func
(paren
id|end
comma
id|rsvd_region
(braket
id|i
)braket
dot
id|start
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|range_end
op_le
id|range_start
)paren
r_continue
suffix:semicolon
multiline_comment|/* skip over empty range */
r_if
c_cond
(paren
id|range_end
op_minus
id|range_start
op_ge
id|needed
)paren
(brace
id|bootmap_start
op_assign
id|__pa
c_func
(paren
id|range_start
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* done */
)brace
multiline_comment|/* nothing more available in this segment */
r_if
c_cond
(paren
id|range_end
op_eq
id|end
)paren
r_return
l_int|0
suffix:semicolon
id|free_start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|rsvd_region
(braket
id|i
)braket
dot
id|end
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|sort_regions
id|sort_regions
(paren
r_struct
id|rsvd_region
op_star
id|rsvd_region
comma
r_int
id|max
)paren
(brace
r_int
id|j
suffix:semicolon
multiline_comment|/* simple bubble sorting */
r_while
c_loop
(paren
id|max
op_decrement
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|max
suffix:semicolon
op_increment
id|j
)paren
(brace
r_if
c_cond
(paren
id|rsvd_region
(braket
id|j
)braket
dot
id|start
OG
id|rsvd_region
(braket
id|j
op_plus
l_int|1
)braket
dot
id|start
)paren
(brace
r_struct
id|rsvd_region
id|tmp
suffix:semicolon
id|tmp
op_assign
id|rsvd_region
(braket
id|j
)braket
suffix:semicolon
id|rsvd_region
(braket
id|j
)braket
op_assign
id|rsvd_region
(braket
id|j
op_plus
l_int|1
)braket
suffix:semicolon
id|rsvd_region
(braket
id|j
op_plus
l_int|1
)braket
op_assign
id|tmp
suffix:semicolon
)brace
)brace
)brace
)brace
r_static
r_void
DECL|function|find_memory
id|find_memory
(paren
r_void
)paren
(brace
DECL|macro|KERNEL_END
macro_line|#&t;define KERNEL_END&t;((unsigned long) &amp;_end)
r_int
r_int
id|bootmap_size
suffix:semicolon
r_int
r_int
id|max_pfn
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * none of the entries in this table overlap&n;&t; */
id|rsvd_region
(braket
id|n
)braket
dot
id|start
op_assign
(paren
r_int
r_int
)paren
id|ia64_boot_param
suffix:semicolon
id|rsvd_region
(braket
id|n
)braket
dot
id|end
op_assign
id|rsvd_region
(braket
id|n
)braket
dot
id|start
op_plus
r_sizeof
(paren
op_star
id|ia64_boot_param
)paren
suffix:semicolon
id|n
op_increment
suffix:semicolon
id|rsvd_region
(braket
id|n
)braket
dot
id|start
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|ia64_boot_param-&gt;efi_memmap
)paren
suffix:semicolon
id|rsvd_region
(braket
id|n
)braket
dot
id|end
op_assign
id|rsvd_region
(braket
id|n
)braket
dot
id|start
op_plus
id|ia64_boot_param-&gt;efi_memmap_size
suffix:semicolon
id|n
op_increment
suffix:semicolon
id|rsvd_region
(braket
id|n
)braket
dot
id|start
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|ia64_boot_param-&gt;command_line
)paren
suffix:semicolon
id|rsvd_region
(braket
id|n
)braket
dot
id|end
op_assign
(paren
id|rsvd_region
(braket
id|n
)braket
dot
id|start
op_plus
id|strlen
c_func
(paren
id|__va
c_func
(paren
id|ia64_boot_param-&gt;command_line
)paren
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|n
op_increment
suffix:semicolon
id|rsvd_region
(braket
id|n
)braket
dot
id|start
op_assign
id|KERNEL_START
suffix:semicolon
id|rsvd_region
(braket
id|n
)braket
dot
id|end
op_assign
id|KERNEL_END
suffix:semicolon
id|n
op_increment
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|ia64_boot_param-&gt;initrd_start
)paren
(brace
id|rsvd_region
(braket
id|n
)braket
dot
id|start
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|ia64_boot_param-&gt;initrd_start
)paren
suffix:semicolon
id|rsvd_region
(braket
id|n
)braket
dot
id|end
op_assign
id|rsvd_region
(braket
id|n
)braket
dot
id|start
op_plus
id|ia64_boot_param-&gt;initrd_size
suffix:semicolon
id|n
op_increment
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* end of memory marker */
id|rsvd_region
(braket
id|n
)braket
dot
id|start
op_assign
op_complement
l_int|0UL
suffix:semicolon
id|rsvd_region
(braket
id|n
)braket
dot
id|end
op_assign
op_complement
l_int|0UL
suffix:semicolon
id|n
op_increment
suffix:semicolon
id|num_rsvd_regions
op_assign
id|n
suffix:semicolon
id|sort_regions
c_func
(paren
id|rsvd_region
comma
id|num_rsvd_regions
)paren
suffix:semicolon
multiline_comment|/* first find highest page frame number */
id|max_pfn
op_assign
l_int|0
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|find_max_pfn
comma
op_amp
id|max_pfn
)paren
suffix:semicolon
multiline_comment|/* how many bytes to cover all the pages */
id|bootmap_size
op_assign
id|bootmem_bootmap_pages
c_func
(paren
id|max_pfn
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* look for a location to hold the bootmap */
id|bootmap_start
op_assign
op_complement
l_int|0UL
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|find_bootmap_location
comma
op_amp
id|bootmap_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bootmap_start
op_eq
op_complement
l_int|0UL
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot find %ld bytes for bootmap&bslash;n&quot;
comma
id|bootmap_size
)paren
suffix:semicolon
id|bootmap_size
op_assign
id|init_bootmem
c_func
(paren
id|bootmap_start
op_rshift
id|PAGE_SHIFT
comma
id|max_pfn
)paren
suffix:semicolon
multiline_comment|/* Free all available memory, then mark bootmem-map as being in use.  */
id|efi_memmap_walk
c_func
(paren
id|free_available_memory
comma
l_int|0
)paren
suffix:semicolon
id|reserve_bootmem
c_func
(paren
id|bootmap_start
comma
id|bootmap_size
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|ia64_boot_param-&gt;initrd_start
)paren
(brace
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|ia64_boot_param-&gt;initrd_start
)paren
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|ia64_boot_param-&gt;initrd_size
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initial ramdisk at: 0x%lx (%lu bytes)&bslash;n&quot;
comma
id|initrd_start
comma
id|ia64_boot_param-&gt;initrd_size
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_void
id|__init
DECL|function|setup_arch
id|setup_arch
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_extern
r_int
r_int
id|ia64_iobase
suffix:semicolon
r_int
r_int
id|phys_iobase
suffix:semicolon
id|unw_init
c_func
(paren
)paren
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|__va
c_func
(paren
id|ia64_boot_param-&gt;command_line
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|saved_command_line
comma
op_star
id|cmdline_p
comma
r_sizeof
(paren
id|saved_command_line
)paren
)paren
suffix:semicolon
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* for safety */
id|efi_init
c_func
(paren
)paren
suffix:semicolon
id|find_memory
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* XXX fix me */
id|init_mm.start_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|init_mm.end_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
suffix:semicolon
id|init_mm.end_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_edata
suffix:semicolon
id|init_mm.brk
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
id|code_resource.start
op_assign
id|virt_to_bus
c_func
(paren
op_amp
id|_text
)paren
suffix:semicolon
id|code_resource.end
op_assign
id|virt_to_bus
c_func
(paren
op_amp
id|_etext
)paren
op_minus
l_int|1
suffix:semicolon
id|data_resource.start
op_assign
id|virt_to_bus
c_func
(paren
op_amp
id|_etext
)paren
suffix:semicolon
id|data_resource.end
op_assign
id|virt_to_bus
c_func
(paren
op_amp
id|_edata
)paren
op_minus
l_int|1
suffix:semicolon
macro_line|#endif
multiline_comment|/* process SAL system table: */
id|ia64_sal_init
c_func
(paren
id|efi.sal_systab
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_GENERIC
id|machvec_init
c_func
(paren
id|acpi_get_sysname
c_func
(paren
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Set `iobase&squot; to the appropriate address in region 6 (uncached access range).&n;&t; *&n;&t; *  The EFI memory map is the &quot;preferred&quot; location to get the I/O port space base,&n;&t; *  rather the relying on AR.KR0. This should become more clear in future SAL&n;&t; *  specs. We&squot;ll fall back to getting it out of AR.KR0 if no appropriate entry is&n;&t; *  found in the memory map.&n;&t; */
id|phys_iobase
op_assign
id|efi_get_iobase
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phys_iobase
)paren
multiline_comment|/* set AR.KR0 since this is all we use it for anyway */
id|ia64_set_kr
c_func
(paren
id|IA64_KR_IO_BASE
comma
id|phys_iobase
)paren
suffix:semicolon
r_else
(brace
id|phys_iobase
op_assign
id|ia64_get_kr
c_func
(paren
id|IA64_KR_IO_BASE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;No I/O port range found in EFI memory map, falling back to AR.KR0&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;I/O port base = 0x%lx&bslash;n&quot;
comma
id|phys_iobase
)paren
suffix:semicolon
)brace
id|ia64_iobase
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|phys_iobase
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|cpu_physical_id
c_func
(paren
l_int|0
)paren
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|cpu_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* initialize the bootstrap CPU */
macro_line|#ifdef CONFIG_ACPI_BOOT
id|acpi_boot_init
c_func
(paren
op_star
id|cmdline_p
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
macro_line|# if defined(CONFIG_DUMMY_CONSOLE)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|# endif
macro_line|# if defined(CONFIG_VGA_CONSOLE)
multiline_comment|/*&n;&t; * Non-legacy systems may route legacy VGA MMIO range to system&n;&t; * memory.  vga_con probes the MMIO hole, so memory looks like&n;&t; * a VGA device to it.  The EFI memory map can tell us if it&squot;s&n;&t; * memory so we can avoid this problem.&n;&t; */
r_if
c_cond
(paren
id|efi_mem_type
c_func
(paren
l_int|0xA0000
)paren
op_ne
id|EFI_CONVENTIONAL_MEMORY
)paren
id|conswitchp
op_assign
op_amp
id|vga_con
suffix:semicolon
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_IA64_MCA
multiline_comment|/* enable IA-64 Machine Check Abort Handling */
id|ia64_mca_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|platform_setup
c_func
(paren
id|cmdline_p
)paren
suffix:semicolon
id|paging_init
c_func
(paren
)paren
suffix:semicolon
id|unw_create_gate_table
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Display cpu info for all cpu&squot;s.&n; */
r_static
r_int
DECL|function|show_cpuinfo
id|show_cpuinfo
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
macro_line|#ifdef CONFIG_SMP
DECL|macro|lpj
macro_line|#&t;define lpj&t;c-&gt;loops_per_jiffy
DECL|macro|cpunum
macro_line|#&t;define cpunum&t;c-&gt;cpu
macro_line|#else
macro_line|#&t;define lpj&t;loops_per_jiffy
macro_line|#&t;define cpunum&t;0
macro_line|#endif
r_char
id|family
(braket
l_int|32
)braket
comma
id|features
(braket
l_int|128
)braket
comma
op_star
id|cp
suffix:semicolon
r_struct
id|cpuinfo_ia64
op_star
id|c
op_assign
id|v
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
id|mask
op_assign
id|c-&gt;features
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;family
)paren
(brace
r_case
l_int|0x07
suffix:colon
id|memcpy
c_func
(paren
id|family
comma
l_string|&quot;Itanium&quot;
comma
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1f
suffix:colon
id|memcpy
c_func
(paren
id|family
comma
l_string|&quot;McKinley&quot;
comma
l_int|9
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|sprintf
c_func
(paren
id|family
comma
l_string|&quot;%u&quot;
comma
id|c-&gt;family
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* build the feature string: */
id|memcpy
c_func
(paren
id|features
comma
l_string|&quot; standard&quot;
comma
l_int|10
)paren
suffix:semicolon
id|cp
op_assign
id|features
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
(brace
id|strcpy
c_func
(paren
id|cp
comma
l_string|&quot; branchlong&quot;
)paren
suffix:semicolon
id|cp
op_assign
id|strchr
c_func
(paren
id|cp
comma
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
id|mask
op_and_assign
op_complement
l_int|1UL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mask
)paren
id|sprintf
c_func
(paren
id|cp
comma
l_string|&quot; 0x%lx&quot;
comma
id|mask
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;processor  : %d&bslash;n&quot;
l_string|&quot;vendor     : %s&bslash;n&quot;
l_string|&quot;arch       : IA-64&bslash;n&quot;
l_string|&quot;family     : %s&bslash;n&quot;
l_string|&quot;model      : %u&bslash;n&quot;
l_string|&quot;revision   : %u&bslash;n&quot;
l_string|&quot;archrev    : %u&bslash;n&quot;
l_string|&quot;features   :%s&bslash;n&quot;
multiline_comment|/* don&squot;t change this---it _is_ right! */
l_string|&quot;cpu number : %lu&bslash;n&quot;
l_string|&quot;cpu regs   : %u&bslash;n&quot;
l_string|&quot;cpu MHz    : %lu.%06lu&bslash;n&quot;
l_string|&quot;itc MHz    : %lu.%06lu&bslash;n&quot;
l_string|&quot;BogoMIPS   : %lu.%02lu&bslash;n&bslash;n&quot;
comma
id|cpunum
comma
id|c-&gt;vendor
comma
id|family
comma
id|c-&gt;model
comma
id|c-&gt;revision
comma
id|c-&gt;archrev
comma
id|features
comma
id|c-&gt;ppn
comma
id|c-&gt;number
comma
id|c-&gt;proc_freq
op_div
l_int|1000000
comma
id|c-&gt;proc_freq
op_mod
l_int|1000000
comma
id|c-&gt;itc_freq
op_div
l_int|1000000
comma
id|c-&gt;itc_freq
op_mod
l_int|1000000
comma
id|lpj
op_star
id|HZ
op_div
l_int|500000
comma
(paren
id|lpj
op_star
id|HZ
op_div
l_int|5000
)paren
op_mod
l_int|100
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
op_star
DECL|function|c_start
id|c_start
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_while
c_loop
(paren
op_star
id|pos
OL
id|NR_CPUS
op_logical_and
op_logical_neg
(paren
id|cpu_online_map
op_amp
(paren
l_int|1
op_lshift
op_star
id|pos
)paren
)paren
)paren
op_increment
op_star
id|pos
suffix:semicolon
macro_line|#endif
r_return
op_star
id|pos
OL
id|NR_CPUS
ques
c_cond
id|cpu_data
c_func
(paren
op_star
id|pos
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
r_static
r_void
op_star
DECL|function|c_next
id|c_next
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|c_start
c_func
(paren
id|m
comma
id|pos
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|c_stop
id|c_stop
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
)brace
DECL|variable|cpuinfo_op
r_struct
id|seq_operations
id|cpuinfo_op
op_assign
(brace
id|start
suffix:colon
id|c_start
comma
id|next
suffix:colon
id|c_next
comma
id|stop
suffix:colon
id|c_stop
comma
id|show
suffix:colon
id|show_cpuinfo
)brace
suffix:semicolon
r_void
DECL|function|identify_cpu
id|identify_cpu
(paren
r_struct
id|cpuinfo_ia64
op_star
id|c
)paren
(brace
r_union
(brace
r_int
r_int
id|bits
(braket
l_int|5
)braket
suffix:semicolon
r_struct
(brace
multiline_comment|/* id 0 &amp; 1: */
r_char
id|vendor
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* id 2 */
id|u64
id|ppn
suffix:semicolon
multiline_comment|/* processor serial number */
multiline_comment|/* id 3: */
r_int
id|number
suffix:colon
l_int|8
suffix:semicolon
r_int
id|revision
suffix:colon
l_int|8
suffix:semicolon
r_int
id|model
suffix:colon
l_int|8
suffix:semicolon
r_int
id|family
suffix:colon
l_int|8
suffix:semicolon
r_int
id|archrev
suffix:colon
l_int|8
suffix:semicolon
r_int
id|reserved
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* id 4: */
id|u64
id|features
suffix:semicolon
)brace
id|field
suffix:semicolon
)brace
id|cpuid
suffix:semicolon
id|pal_vm_info_1_u_t
id|vm1
suffix:semicolon
id|pal_vm_info_2_u_t
id|vm2
suffix:semicolon
id|pal_status_t
id|status
suffix:semicolon
r_int
r_int
id|impl_va_msb
op_assign
l_int|50
comma
id|phys_addr_size
op_assign
l_int|44
suffix:semicolon
multiline_comment|/* Itanium defaults */
r_int
id|i
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
l_int|5
suffix:semicolon
op_increment
id|i
)paren
id|cpuid.bits
(braket
id|i
)braket
op_assign
id|ia64_get_cpuid
c_func
(paren
id|i
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|c-&gt;vendor
comma
id|cpuid.field.vendor
comma
l_int|16
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|c-&gt;cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|c-&gt;ppn
op_assign
id|cpuid.field.ppn
suffix:semicolon
id|c-&gt;number
op_assign
id|cpuid.field.number
suffix:semicolon
id|c-&gt;revision
op_assign
id|cpuid.field.revision
suffix:semicolon
id|c-&gt;model
op_assign
id|cpuid.field.model
suffix:semicolon
id|c-&gt;family
op_assign
id|cpuid.field.family
suffix:semicolon
id|c-&gt;archrev
op_assign
id|cpuid.field.archrev
suffix:semicolon
id|c-&gt;features
op_assign
id|cpuid.field.features
suffix:semicolon
id|status
op_assign
id|ia64_pal_vm_summary
c_func
(paren
op_amp
id|vm1
comma
op_amp
id|vm2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|PAL_STATUS_SUCCESS
)paren
(brace
id|impl_va_msb
op_assign
id|vm2.pal_vm_info_2_s.impl_va_msb
suffix:semicolon
id|phys_addr_size
op_assign
id|vm1.pal_vm_info_1_s.phys_add_size
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;CPU %d: %lu virtual and %lu physical address bits&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|impl_va_msb
op_plus
l_int|1
comma
id|phys_addr_size
)paren
suffix:semicolon
id|c-&gt;unimpl_va_mask
op_assign
op_complement
(paren
(paren
l_int|7L
op_lshift
l_int|61
)paren
op_or
(paren
(paren
l_int|1L
op_lshift
(paren
id|impl_va_msb
op_plus
l_int|1
)paren
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|c-&gt;unimpl_pa_mask
op_assign
op_complement
(paren
(paren
l_int|1L
op_lshift
l_int|63
)paren
op_or
(paren
(paren
l_int|1L
op_lshift
id|phys_addr_size
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|setup_per_cpu_areas
id|setup_per_cpu_areas
(paren
r_void
)paren
(brace
multiline_comment|/* start_kernel() requires this... */
)brace
multiline_comment|/*&n; * cpu_init() initializes state that is per-CPU.  This function acts&n; * as a &squot;CPU state barrier&squot;, nothing should get across.&n; */
r_void
DECL|function|cpu_init
id|cpu_init
(paren
r_void
)paren
(brace
r_extern
r_char
id|__per_cpu_start
(braket
)braket
comma
id|__phys_per_cpu_start
(braket
)braket
suffix:semicolon
r_extern
r_void
id|__init
id|ia64_mmu_init
(paren
r_void
op_star
)paren
suffix:semicolon
r_int
r_int
id|num_phys_stacked
suffix:semicolon
id|pal_vm_info_2_u_t
id|vmi
suffix:semicolon
r_int
r_int
id|max_ctx
suffix:semicolon
r_struct
id|cpuinfo_ia64
op_star
id|my_cpu_info
suffix:semicolon
r_void
op_star
id|my_cpu_data
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_char
id|__per_cpu_end
(braket
)braket
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|my_cpu_data
op_assign
id|alloc_bootmem_pages
c_func
(paren
id|__per_cpu_end
op_minus
id|__per_cpu_start
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|my_cpu_data
comma
id|__phys_per_cpu_start
comma
id|__per_cpu_end
op_minus
id|__per_cpu_start
)paren
suffix:semicolon
id|__per_cpu_offset
(braket
id|cpu
)braket
op_assign
(paren
r_char
op_star
)paren
id|my_cpu_data
op_minus
id|__per_cpu_start
suffix:semicolon
id|my_cpu_info
op_assign
id|my_cpu_data
op_plus
(paren
(paren
r_char
op_star
)paren
op_amp
id|cpu_info
op_minus
id|__per_cpu_start
)paren
suffix:semicolon
macro_line|#else
id|my_cpu_data
op_assign
id|__phys_per_cpu_start
suffix:semicolon
macro_line|#endif
id|my_cpu_info
op_assign
id|my_cpu_data
op_plus
(paren
(paren
r_char
op_star
)paren
op_amp
id|cpu_info
op_minus
id|__per_cpu_start
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We can&squot;t pass &quot;local_cpu_data&quot; to identify_cpu() because we haven&squot;t called&n;&t; * ia64_mmu_init() yet.  And we can&squot;t call ia64_mmu_init() first because it&n;&t; * depends on the data returned by identify_cpu().  We break the dependency by&n;&t; * accessing cpu_data() the old way, through identity mapped space.&n;&t; */
id|identify_cpu
c_func
(paren
id|my_cpu_info
)paren
suffix:semicolon
multiline_comment|/* Clear the stack memory reserved for pt_regs: */
id|memset
c_func
(paren
id|ia64_task_regs
c_func
(paren
id|current
)paren
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize default control register to defer all speculative faults.  The&n;&t; * kernel MUST NOT depend on a particular setting of these bits (in other words,&n;&t; * the kernel must have recovery code for all speculative accesses).  Turn on&n;&t; * dcr.lc as per recommendation by the architecture team.  Most IA-32 apps&n;&t; * shouldn&squot;t be affected by this (moral: keep your ia32 locks aligned and you&squot;ll&n;&t; * be fine).&n;&t; */
id|ia64_set_dcr
c_func
(paren
id|IA64_DCR_DM
op_or
id|IA64_DCR_DP
op_or
id|IA64_DCR_DK
op_or
id|IA64_DCR_DX
op_or
id|IA64_DCR_DR
op_or
id|IA64_DCR_DA
op_or
id|IA64_DCR_DD
op_or
id|IA64_DCR_LC
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|ia64_set_fpu_owner
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|ia64_mmu_init
c_func
(paren
id|my_cpu_data
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA32_SUPPORT
multiline_comment|/* initialize global ia32 state - CR0 and CR4 */
id|asm
r_volatile
(paren
l_string|&quot;mov ar.cflg = %0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
(paren
(paren
id|ulong
)paren
id|IA32_CR4
op_lshift
l_int|32
)paren
op_or
id|IA32_CR0
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* disable all local interrupt sources: */
id|ia64_set_itv
c_func
(paren
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
id|ia64_set_lrr0
c_func
(paren
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
id|ia64_set_lrr1
c_func
(paren
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
id|ia64_set_pmv
c_func
(paren
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
id|ia64_set_cmcv
c_func
(paren
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* clear TPR &amp; XTP to enable all interrupt classes: */
id|ia64_set_tpr
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|normal_xtp
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* set ia64_ctx.max_rid to the maximum RID that is supported by all CPUs: */
r_if
c_cond
(paren
id|ia64_pal_vm_summary
c_func
(paren
l_int|NULL
comma
op_amp
id|vmi
)paren
op_eq
l_int|0
)paren
id|max_ctx
op_assign
(paren
l_int|1U
op_lshift
(paren
id|vmi.pal_vm_info_2_s.rid_size
op_minus
l_int|3
)paren
)paren
op_minus
l_int|1
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;cpu_init: PAL VM summary failed, assuming 18 RID bits&bslash;n&quot;
)paren
suffix:semicolon
id|max_ctx
op_assign
(paren
l_int|1U
op_lshift
l_int|15
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* use architected minimum */
)brace
r_while
c_loop
(paren
id|max_ctx
OL
id|ia64_ctx.max_ctx
)paren
(brace
r_int
r_int
id|old
op_assign
id|ia64_ctx.max_ctx
suffix:semicolon
r_if
c_cond
(paren
id|cmpxchg
c_func
(paren
op_amp
id|ia64_ctx.max_ctx
comma
id|old
comma
id|max_ctx
)paren
op_eq
id|old
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ia64_pal_rse_info
c_func
(paren
op_amp
id|num_phys_stacked
comma
l_int|0
)paren
op_ne
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;cpu_init: PAL RSE info failed, assuming 96 physical stacked regs&bslash;n&quot;
)paren
suffix:semicolon
id|num_phys_stacked
op_assign
l_int|96
suffix:semicolon
)brace
multiline_comment|/* size of physical stacked register partition plus 8 bytes: */
id|ia64_phys_stacked_size_p8
op_assign
id|num_phys_stacked
op_star
l_int|8
op_plus
l_int|8
suffix:semicolon
id|platform_cpu_init
c_func
(paren
)paren
suffix:semicolon
)brace
eof
