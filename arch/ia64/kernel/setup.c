multiline_comment|/*&n; * Architecture-specific setup.&n; *&n; * Copyright (C) 1998-2001, 2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; * Copyright (C) 2000, Rohit Seth &lt;rohit.seth@intel.com&gt;&n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *&n; * 11/12/01 D.Mosberger Convert get_cpuinfo() to seq_file based show_cpuinfo().&n; * 04/04/00 D.Mosberger renamed cpu_initialized to cpu_online_map&n; * 03/31/00 R.Seth&t;cpu_initialized and current-&gt;processor fixes&n; * 02/04/00 D.Mosberger&t;some more get_cpuinfo fixes...&n; * 02/01/00 R.Seth&t;fixed get_cpuinfo for SMP&n; * 01/07/99 S.Eranian&t;added the support for command line argument&n; * 06/24/99 W.Drummond&t;added boot_cpu_data.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/mca.h&gt;
macro_line|#include &lt;asm/meminit.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/patch.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#if defined(CONFIG_SMP) &amp;&amp; (IA64_CPU_SIZE &gt; PAGE_SIZE)
macro_line|# error &quot;struct cpuinfo_ia64 too big!&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
DECL|variable|__per_cpu_offset
r_int
r_int
id|__per_cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|__per_cpu_offset
id|EXPORT_SYMBOL
c_func
(paren
id|__per_cpu_offset
)paren
suffix:semicolon
macro_line|#endif
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|cpuinfo_ia64
comma
id|cpu_info
)paren
suffix:semicolon
id|DEFINE_PER_CPU
c_func
(paren
r_int
r_int
comma
id|local_per_cpu_offset
)paren
suffix:semicolon
id|DEFINE_PER_CPU
c_func
(paren
r_int
r_int
comma
id|ia64_phys_stacked_size_p8
)paren
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
DECL|variable|ia64_max_cacheline_size
r_int
r_int
id|ia64_max_cacheline_size
suffix:semicolon
DECL|variable|ia64_iobase
r_int
r_int
id|ia64_iobase
suffix:semicolon
multiline_comment|/* virtual address for I/O accesses */
DECL|variable|ia64_iobase
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_iobase
)paren
suffix:semicolon
DECL|variable|io_space
r_struct
id|io_space
id|io_space
(braket
id|MAX_IO_SPACES
)braket
suffix:semicolon
DECL|variable|io_space
id|EXPORT_SYMBOL
c_func
(paren
id|io_space
)paren
suffix:semicolon
DECL|variable|num_io_spaces
r_int
r_int
id|num_io_spaces
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
op_assign
l_int|0xaa
suffix:semicolon
multiline_comment|/* XXX remove this when legacy I/O is gone */
multiline_comment|/*&n; * The merge_mask variable needs to be set to (max(iommu_page_size(iommu)) - 1).  This&n; * mask specifies a mask of address bits that must be 0 in order for two buffers to be&n; * mergeable by the I/O MMU (i.e., the end address of the first buffer and the start&n; * address of the second buffer must be aligned to (merge_mask+1) in order to be&n; * mergeable).  By default, we assume there is no I/O MMU which can merge physically&n; * discontiguous buffers, so we set the merge_mask to ~0UL, which corresponds to a iommu&n; * page-size of 2^64.&n; */
DECL|variable|ia64_max_iommu_merge_mask
r_int
r_int
id|ia64_max_iommu_merge_mask
op_assign
op_complement
l_int|0UL
suffix:semicolon
DECL|variable|ia64_max_iommu_merge_mask
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_max_iommu_merge_mask
)paren
suffix:semicolon
multiline_comment|/*&n; * We use a special marker for the end of memory and it uses the extra (+1) slot&n; */
DECL|variable|rsvd_region
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
r_int
id|num_rsvd_regions
suffix:semicolon
multiline_comment|/*&n; * Filter incoming memory segments based on the primitive map created from the boot&n; * parameters. Segments contained in the map are removed from the memory ranges. A&n; * caller-specified function is called with the memory ranges that remain after filtering.&n; * This routine does not assume the incoming segments are sorted.&n; */
r_int
DECL|function|filter_rsvd_memory
id|filter_rsvd_memory
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
r_void
(paren
op_star
id|func
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
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
id|KERN_WARNING
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
id|func
op_assign
id|arg
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
id|max
c_func
(paren
id|start
comma
id|prev_start
)paren
suffix:semicolon
id|range_end
op_assign
id|min
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
id|call_pernode_memory
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
comma
id|func
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
multiline_comment|/**&n; * reserve_memory - setup reserved memory areas&n; *&n; * Setup the reserved memory areas set aside for the boot parameters,&n; * initrd, etc.  There are currently %IA64_MAX_RSVD_REGIONS defined,&n; * see include/asm-ia64/meminit.h if you need to define more.&n; */
r_void
DECL|function|reserve_memory
id|reserve_memory
(paren
r_void
)paren
(brace
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
(paren
r_int
r_int
)paren
id|ia64_imva
c_func
(paren
(paren
r_void
op_star
)paren
id|KERNEL_START
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
r_int
r_int
)paren
id|ia64_imva
c_func
(paren
id|_end
)paren
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
)brace
multiline_comment|/**&n; * find_initrd - get initrd parameters from the boot parameter structure&n; *&n; * Grab the initrd start and end from the boot parameter struct given us by&n; * the boot loader.&n; */
r_void
DECL|function|find_initrd
id|find_initrd
(paren
r_void
)paren
(brace
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
id|KERN_INFO
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
r_static
r_void
id|__init
DECL|function|io_port_init
id|io_port_init
(paren
r_void
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
id|KERN_INFO
l_string|&quot;No I/O port range found in EFI memory map, falling back &quot;
l_string|&quot;to AR.KR0&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
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
multiline_comment|/* setup legacy IO port space */
id|io_space
(braket
l_int|0
)braket
dot
id|mmio_base
op_assign
id|ia64_iobase
suffix:semicolon
id|io_space
(braket
l_int|0
)braket
dot
id|sparse
op_assign
l_int|1
suffix:semicolon
id|num_io_spaces
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SERIAL_8250_CONSOLE
r_static
r_void
id|__init
DECL|function|setup_serial_legacy
id|setup_serial_legacy
(paren
r_void
)paren
(brace
r_struct
id|uart_port
id|port
suffix:semicolon
r_int
r_int
id|i
comma
id|iobase
(braket
)braket
op_assign
(brace
l_int|0x3f8
comma
l_int|0x2f8
)brace
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Registering legacy COM ports for serial console&bslash;n&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
id|port
)paren
)paren
suffix:semicolon
id|port.iotype
op_assign
id|SERIAL_IO_PORT
suffix:semicolon
id|port.uartclk
op_assign
id|BASE_BAUD
op_star
l_int|16
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
id|ARRAY_SIZE
c_func
(paren
id|iobase
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|port.line
op_assign
id|i
suffix:semicolon
id|port.iobase
op_assign
id|iobase
(braket
id|i
)braket
suffix:semicolon
id|early_serial_setup
c_func
(paren
op_amp
id|port
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/**&n; * early_console_setup - setup debugging console&n; *&n; * Consoles started here require little enough setup that we can start using&n; * them very early in the boot process, either right after the machine&n; * vector initialization, or even before if the drivers can detect their hw.&n; *&n; * Returns non-zero if a console couldn&squot;t be setup.&n; */
r_static
r_inline
r_int
id|__init
DECL|function|early_console_setup
id|early_console_setup
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SERIAL_SGI_L1_CONSOLE
(brace
r_extern
r_int
id|sn_serial_console_early_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sn_serial_console_early_setup
c_func
(paren
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
op_minus
l_int|1
suffix:semicolon
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
id|unw_init
c_func
(paren
)paren
suffix:semicolon
id|ia64_patch_vtop
c_func
(paren
(paren
id|u64
)paren
id|__start___vtop_patchlist
comma
(paren
id|u64
)paren
id|__end___vtop_patchlist
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
id|strlcpy
c_func
(paren
id|saved_command_line
comma
op_star
id|cmdline_p
comma
id|COMMAND_LINE_SIZE
)paren
suffix:semicolon
id|efi_init
c_func
(paren
)paren
suffix:semicolon
id|io_port_init
c_func
(paren
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
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* If we register an early console, allow CPU 0 to printk */
r_if
c_cond
(paren
op_logical_neg
id|early_console_setup
c_func
(paren
)paren
)paren
id|cpu_set
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu_online_map
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ACPI_BOOT
multiline_comment|/* Initialize the ACPI boot-time table parser */
id|acpi_table_init
c_func
(paren
)paren
suffix:semicolon
macro_line|# ifdef CONFIG_ACPI_NUMA
id|acpi_numa_init
c_func
(paren
)paren
suffix:semicolon
macro_line|# endif
macro_line|#else
macro_line|# ifdef CONFIG_SMP
id|smp_build_cpu_map
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* happens, e.g., with the Ski simulator */
macro_line|# endif
macro_line|#endif /* CONFIG_APCI_BOOT */
id|find_memory
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* process SAL system table: */
id|ia64_sal_init
c_func
(paren
id|efi.sal_systab
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
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_EFI_PCDP
id|efi_setup_pcdp_console
c_func
(paren
op_star
id|cmdline_p
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_8250_CONSOLE
r_if
c_cond
(paren
op_logical_neg
id|efi.hcdp
)paren
id|setup_serial_legacy
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
r_if
c_cond
(paren
op_logical_neg
id|conswitchp
)paren
(brace
macro_line|# if defined(CONFIG_DUMMY_CONSOLE)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|# endif
macro_line|# if defined(CONFIG_VGA_CONSOLE)
multiline_comment|/*&n;&t;&t; * Non-legacy systems may route legacy VGA MMIO range to system&n;&t;&t; * memory.  vga_con probes the MMIO hole, so memory looks like&n;&t;&t; * a VGA device to it.  The EFI memory map can tell us if it&squot;s&n;&t;&t; * memory so we can avoid this problem.&n;&t;&t; */
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
)brace
macro_line|#endif
multiline_comment|/* enable IA-64 Machine Check Abort Handling unless disabled */
r_if
c_cond
(paren
op_logical_neg
id|strstr
c_func
(paren
id|saved_command_line
comma
l_string|&quot;nomca&quot;
)paren
)paren
id|ia64_mca_init
c_func
(paren
)paren
suffix:semicolon
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
r_static
r_struct
(brace
r_int
r_int
id|mask
suffix:semicolon
r_const
r_char
op_star
id|feature_name
suffix:semicolon
)brace
id|feature_bits
(braket
)braket
op_assign
(brace
(brace
l_int|1UL
op_lshift
l_int|0
comma
l_string|&quot;branchlong&quot;
)brace
comma
(brace
l_int|1UL
op_lshift
l_int|1
comma
l_string|&quot;spontaneous deferral&quot;
)brace
comma
(brace
l_int|1UL
op_lshift
l_int|2
comma
l_string|&quot;16-byte atomic ops&quot;
)brace
)brace
suffix:semicolon
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
comma
id|sep
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
r_int
id|i
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
l_string|&quot;Itanium 2&quot;
comma
l_int|10
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
id|sep
op_assign
l_int|0
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
(paren
r_int
)paren
id|ARRAY_SIZE
c_func
(paren
id|feature_bits
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|mask
op_amp
id|feature_bits
(braket
id|i
)braket
dot
id|mask
)paren
(brace
r_if
c_cond
(paren
id|sep
)paren
op_star
id|cp
op_increment
op_assign
id|sep
suffix:semicolon
id|sep
op_assign
l_char|&squot;,&squot;
suffix:semicolon
op_star
id|cp
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|strcpy
c_func
(paren
id|cp
comma
id|feature_bits
(braket
id|i
)braket
dot
id|feature_name
)paren
suffix:semicolon
id|cp
op_add_assign
id|strlen
c_func
(paren
id|feature_bits
(braket
id|i
)braket
dot
id|feature_name
)paren
suffix:semicolon
id|mask
op_and_assign
op_complement
id|feature_bits
(braket
id|i
)braket
dot
id|mask
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mask
)paren
(brace
multiline_comment|/* print unknown features as a hex value: */
r_if
c_cond
(paren
id|sep
)paren
op_star
id|cp
op_increment
op_assign
id|sep
suffix:semicolon
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
)brace
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
id|cpu_isset
c_func
(paren
op_star
id|pos
comma
id|cpu_online_map
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
dot
id|start
op_assign
id|c_start
comma
dot
id|next
op_assign
id|c_next
comma
dot
id|stop
op_assign
id|c_stop
comma
dot
id|show
op_assign
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
r_static
r_void
DECL|function|get_max_cacheline_size
id|get_max_cacheline_size
(paren
r_void
)paren
(brace
r_int
r_int
id|line_size
comma
id|max
op_assign
l_int|1
suffix:semicolon
id|u64
id|l
comma
id|levels
comma
id|unique_caches
suffix:semicolon
id|pal_cache_config_info_t
id|cci
suffix:semicolon
id|s64
id|status
suffix:semicolon
id|status
op_assign
id|ia64_pal_cache_summary
c_func
(paren
op_amp
id|levels
comma
op_amp
id|unique_caches
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: ia64_pal_cache_summary() failed (status=%ld)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|status
)paren
suffix:semicolon
id|max
op_assign
id|SMP_CACHE_BYTES
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_for
c_loop
(paren
id|l
op_assign
l_int|0
suffix:semicolon
id|l
OL
id|levels
suffix:semicolon
op_increment
id|l
)paren
(brace
id|status
op_assign
id|ia64_pal_cache_config_info
c_func
(paren
id|l
comma
multiline_comment|/* cache_type (data_or_unified)= */
l_int|2
comma
op_amp
id|cci
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: ia64_pal_cache_config_info(l=%lu) failed (status=%ld)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|l
comma
id|status
)paren
suffix:semicolon
id|max
op_assign
id|SMP_CACHE_BYTES
suffix:semicolon
)brace
id|line_size
op_assign
l_int|1
op_lshift
id|cci.pcci_line_size
suffix:semicolon
r_if
c_cond
(paren
id|line_size
OG
id|max
)paren
id|max
op_assign
id|line_size
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|max
OG
id|ia64_max_cacheline_size
)paren
id|ia64_max_cacheline_size
op_assign
id|max
suffix:semicolon
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
r_void
id|__devinit
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
id|cpu_info
suffix:semicolon
r_void
op_star
id|cpu_data
suffix:semicolon
id|cpu_data
op_assign
id|per_cpu_init
c_func
(paren
)paren
suffix:semicolon
id|get_max_cacheline_size
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We can&squot;t pass &quot;local_cpu_data&quot; to identify_cpu() because we haven&squot;t called&n;&t; * ia64_mmu_init() yet.  And we can&squot;t call ia64_mmu_init() first because it&n;&t; * depends on the data returned by identify_cpu().  We break the dependency by&n;&t; * accessing cpu_data() through the canonical per-CPU address.&n;&t; */
id|cpu_info
op_assign
id|cpu_data
op_plus
(paren
(paren
r_char
op_star
)paren
op_amp
id|__ia64_per_cpu_var
c_func
(paren
id|cpu_info
)paren
op_minus
id|__per_cpu_start
)paren
suffix:semicolon
id|identify_cpu
c_func
(paren
id|cpu_info
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MCKINLEY
(brace
DECL|macro|FEATURE_SET
macro_line|#&t;&t;define FEATURE_SET 16
r_struct
id|ia64_pal_retval
id|iprv
suffix:semicolon
r_if
c_cond
(paren
id|cpu_info-&gt;family
op_eq
l_int|0x1f
)paren
(brace
id|PAL_CALL_PHYS
c_func
(paren
id|iprv
comma
id|PAL_PROC_GET_FEATURES
comma
l_int|0
comma
id|FEATURE_SET
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|iprv.status
op_eq
l_int|0
)paren
op_logical_and
(paren
id|iprv.v0
op_amp
l_int|0x80
)paren
op_logical_and
(paren
id|iprv.v2
op_amp
l_int|0x80
)paren
)paren
id|PAL_CALL_PHYS
c_func
(paren
id|iprv
comma
id|PAL_PROC_SET_FEATURES
comma
(paren
id|iprv.v1
op_or
l_int|0x80
)paren
comma
id|FEATURE_SET
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
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
id|ia64_set_kr
c_func
(paren
id|IA64_KR_FPU_OWNER
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize default control register to defer all speculative faults.  The&n;&t; * kernel MUST NOT depend on a particular setting of these bits (in other words,&n;&t; * the kernel must have recovery code for all speculative accesses).  Turn on&n;&t; * dcr.lc as per recommendation by the architecture team.  Most IA-32 apps&n;&t; * shouldn&squot;t be affected by this (moral: keep your ia32 locks aligned and you&squot;ll&n;&t; * be fine).&n;&t; */
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_DCR
comma
(paren
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
)paren
suffix:semicolon
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
id|ia64_imva
c_func
(paren
id|cpu_data
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA32_SUPPORT
id|ia32_cpu_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Clear ITC to eliminiate sched_clock() overflows in human time.  */
id|ia64_set_itc
c_func
(paren
l_int|0
)paren
suffix:semicolon
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
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_PMV
comma
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_CMCV
comma
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* clear TPR &amp; XTP to enable all interrupt classes: */
id|ia64_setreg
c_func
(paren
id|_IA64_REG_CR_TPR
comma
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
id|KERN_WARNING
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
l_int|NULL
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cpu_init: PAL RSE info failed; assuming 96 physical &quot;
l_string|&quot;stacked regs&bslash;n&quot;
)paren
suffix:semicolon
id|num_phys_stacked
op_assign
l_int|96
suffix:semicolon
)brace
multiline_comment|/* size of physical stacked register partition plus 8 bytes: */
id|__get_cpu_var
c_func
(paren
id|ia64_phys_stacked_size_p8
)paren
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
r_void
DECL|function|check_bugs
id|check_bugs
(paren
r_void
)paren
(brace
id|ia64_patch_mckinley_e9
c_func
(paren
(paren
r_int
r_int
)paren
id|__start___mckinley_e9_bundles
comma
(paren
r_int
r_int
)paren
id|__end___mckinley_e9_bundles
)paren
suffix:semicolon
)brace
eof
