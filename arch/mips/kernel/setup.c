multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995  Linus Torvalds&n; * Copyright (C) 1995  Waldorf Electronics&n; * Copyright (C) 1995, 1996, 1997, 1998, 1999, 2000, 2001  Ralf Baechle&n; * Copyright (C) 1996  Stoned Elipot&n; * Copyright (C) 2000, 2001, 2002  Maciej W. Rozycki&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|variable|cpu_data
r_struct
id|cpuinfo_mips
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; * There are several bus types available for MIPS machines.  &quot;RISC PC&quot;&n; * type machines have ISA, EISA, VLB or PCI available, DECstations&n; * have Turbochannel or Q-Bus, SGI has GIO, there are lots of VME&n; * boxes ...&n; * This flag is set if a EISA slots are available.&n; */
macro_line|#ifdef CONFIG_EISA
DECL|variable|EISA_bus
r_int
id|EISA_bus
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
suffix:semicolon
r_extern
r_struct
id|fd_ops
id|no_fd_ops
suffix:semicolon
DECL|variable|fd_ops
r_struct
id|fd_ops
op_star
id|fd_ops
suffix:semicolon
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
r_extern
r_struct
id|ide_ops
id|no_ide_ops
suffix:semicolon
DECL|variable|ide_ops
r_struct
id|ide_ops
op_star
id|ide_ops
suffix:semicolon
macro_line|#endif
r_extern
r_void
op_star
id|__rd_start
comma
op_star
id|__rd_end
suffix:semicolon
r_extern
r_struct
id|rtc_ops
id|no_rtc_ops
suffix:semicolon
DECL|variable|rtc_ops
r_struct
id|rtc_ops
op_star
id|rtc_ops
suffix:semicolon
multiline_comment|/*&n; * Setup information&n; *&n; * These are initialized so they are in the .data section&n; */
DECL|variable|mips_machtype
r_int
r_int
id|mips_machtype
op_assign
id|MACH_UNKNOWN
suffix:semicolon
DECL|variable|mips_machgroup
r_int
r_int
id|mips_machgroup
op_assign
id|MACH_GROUP_UNKNOWN
suffix:semicolon
DECL|variable|boot_mem_map
r_struct
id|boot_mem_map
id|boot_mem_map
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
DECL|variable|command_line
r_static
r_char
id|command_line
(braket
id|CL_SIZE
)braket
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
id|CL_SIZE
)braket
suffix:semicolon
r_extern
r_char
id|arcs_cmdline
(braket
id|CL_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * mips_io_port_base is the begin of the address space to which x86 style&n; * I/O ports are mapped.&n; */
DECL|variable|mips_io_port_base
r_const
r_int
r_int
id|mips_io_port_base
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|mips_io_port_base
id|EXPORT_SYMBOL
c_func
(paren
id|mips_io_port_base
)paren
suffix:semicolon
multiline_comment|/*&n; * isa_slot_offset is the address where E(ISA) busaddress 0 is mapped&n; * for the processor.&n; */
DECL|variable|isa_slot_offset
r_int
r_int
id|isa_slot_offset
suffix:semicolon
DECL|variable|isa_slot_offset
id|EXPORT_SYMBOL
c_func
(paren
id|isa_slot_offset
)paren
suffix:semicolon
r_extern
r_void
id|SetUpBootInfo
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|load_mmu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|start_kernel
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_init
c_func
(paren
r_int
comma
r_char
op_star
op_star
comma
r_char
op_star
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|variable|code_resource
r_static
r_struct
id|resource
id|code_resource
op_assign
(brace
l_string|&quot;Kernel code&quot;
)brace
suffix:semicolon
DECL|variable|data_resource
r_static
r_struct
id|resource
id|data_resource
op_assign
(brace
l_string|&quot;Kernel data&quot;
)brace
suffix:semicolon
id|asmlinkage
r_void
id|__init
DECL|function|init_arch
id|init_arch
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
comma
r_int
op_star
id|prom_vec
)paren
(brace
multiline_comment|/* Determine which MIPS variant we are running on. */
id|cpu_probe
c_func
(paren
)paren
suffix:semicolon
id|prom_init
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
comma
id|prom_vec
)paren
suffix:semicolon
id|cpu_report
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Determine the mmu/cache attached to this machine,&n;&t; * then flush the tlb and caches.  On the r4xx0&n;&t; * variants this also sets CP0_WIRED to zero.&n;&t; */
id|load_mmu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable coprocessors and set FPU for 16/32 FPR register model */
id|clear_c0_status
c_func
(paren
id|ST0_CU1
op_or
id|ST0_CU2
op_or
id|ST0_CU3
op_or
id|ST0_KX
op_or
id|ST0_SX
op_or
id|ST0_FR
)paren
suffix:semicolon
id|set_c0_status
c_func
(paren
id|ST0_CU0
)paren
suffix:semicolon
id|start_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|add_memory_region
r_void
id|__init
id|add_memory_region
c_func
(paren
id|phys_t
id|start
comma
id|phys_t
id|size
comma
r_int
id|type
)paren
(brace
r_int
id|x
op_assign
id|boot_mem_map.nr_map
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
id|BOOT_MEM_MAP_MAX
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Ooops! Too many entries in the memory map!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|boot_mem_map.map
(braket
id|x
)braket
dot
id|addr
op_assign
id|start
suffix:semicolon
id|boot_mem_map.map
(braket
id|x
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
id|boot_mem_map.map
(braket
id|x
)braket
dot
id|type
op_assign
id|type
suffix:semicolon
id|boot_mem_map.nr_map
op_increment
suffix:semicolon
)brace
DECL|function|print_memory_map
r_static
r_void
id|__init
id|print_memory_map
c_func
(paren
r_void
)paren
(brace
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
id|boot_mem_map.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; memory: %08Lx @ %08Lx &quot;
comma
(paren
id|u64
)paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|size
comma
(paren
id|u64
)paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|type
)paren
(brace
r_case
id|BOOT_MEM_RAM
suffix:colon
id|printk
c_func
(paren
l_string|&quot;(usable)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BOOT_MEM_ROM_DATA
suffix:colon
id|printk
c_func
(paren
l_string|&quot;(ROM data)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BOOT_MEM_RESERVED
suffix:colon
id|printk
c_func
(paren
l_string|&quot;(reserved)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;type %lu&bslash;n&quot;
comma
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|parse_cmdline_early
r_static
r_inline
r_void
id|parse_cmdline_early
c_func
(paren
r_void
)paren
(brace
r_char
id|c
op_assign
l_char|&squot; &squot;
comma
op_star
id|to
op_assign
id|command_line
comma
op_star
id|from
op_assign
id|saved_command_line
suffix:semicolon
r_int
r_int
id|start_at
comma
id|mem_size
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|usermem
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Determined physical RAM map:&bslash;n&quot;
)paren
suffix:semicolon
id|print_memory_map
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/*&n;&t;&t; * &quot;mem=XXX[kKmM]&quot; defines a memory region from&n;&t;&t; * 0 to &lt;XXX&gt;, overriding the determined size.&n;&t;&t; * &quot;mem=XXX[KkmM]@YYY[KkmM]&quot; defines a memory region from&n;&t;&t; * &lt;YYY&gt; to &lt;YYY&gt;+&lt;XXX&gt;, overriding the determined size.&n;&t;&t; */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot; &squot;
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|from
comma
l_string|&quot;mem=&quot;
comma
l_int|4
)paren
)paren
(brace
r_if
c_cond
(paren
id|to
op_ne
id|command_line
)paren
id|to
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If a user specifies memory size, we&n;&t;&t;&t; * blow away any automatically generated&n;&t;&t;&t; * size.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|usermem
op_eq
l_int|0
)paren
(brace
id|boot_mem_map.nr_map
op_assign
l_int|0
suffix:semicolon
id|usermem
op_assign
l_int|1
suffix:semicolon
)brace
id|mem_size
op_assign
id|memparse
c_func
(paren
id|from
op_plus
l_int|4
comma
op_amp
id|from
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|from
op_eq
l_char|&squot;@&squot;
)paren
id|start_at
op_assign
id|memparse
c_func
(paren
id|from
op_plus
l_int|1
comma
op_amp
id|from
)paren
suffix:semicolon
r_else
id|start_at
op_assign
l_int|0
suffix:semicolon
id|add_memory_region
c_func
(paren
id|start_at
comma
id|mem_size
comma
id|BOOT_MEM_RAM
)paren
suffix:semicolon
)brace
id|c
op_assign
op_star
(paren
id|from
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|CL_SIZE
op_le
op_increment
id|len
)paren
r_break
suffix:semicolon
op_star
(paren
id|to
op_increment
)paren
op_assign
id|c
suffix:semicolon
)brace
op_star
id|to
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|usermem
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;User-defined physical RAM map:&bslash;n&quot;
)paren
suffix:semicolon
id|print_memory_map
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;(((x) + PAGE_SIZE - 1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_DOWN
mdefine_line|#define PFN_DOWN(x)&t;((x) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_PHYS
mdefine_line|#define PFN_PHYS(x)&t;((x) &lt;&lt; PAGE_SHIFT)
DECL|macro|MAXMEM
mdefine_line|#define MAXMEM&t;&t;HIGHMEM_START
DECL|macro|MAXMEM_PFN
mdefine_line|#define MAXMEM_PFN&t;PFN_DOWN(MAXMEM)
DECL|function|bootmem_init
r_static
r_inline
r_void
id|bootmem_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
op_star
id|initrd_header
suffix:semicolon
macro_line|#endif
r_int
r_int
id|bootmap_size
suffix:semicolon
r_int
r_int
id|start_pfn
comma
id|max_low_pfn
comma
id|first_usable_pfn
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|tmp
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
op_amp
id|_end
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
)paren
op_minus
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OL
(paren
r_int
r_int
)paren
op_amp
id|_end
)paren
id|tmp
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|initrd_header
op_assign
(paren
r_int
r_int
op_star
)paren
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|initrd_header
(braket
l_int|0
)braket
op_eq
l_int|0x494E5244
)paren
(brace
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|initrd_header
(braket
l_int|2
)braket
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|initrd_header
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|start_pfn
op_assign
id|PFN_UP
c_func
(paren
id|__pa
c_func
(paren
(paren
op_amp
id|_end
)paren
op_plus
(paren
id|initrd_end
op_minus
id|initrd_start
)paren
op_plus
id|PAGE_SIZE
)paren
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t; * Partially used pages are not usable - thus&n;&t; * we are rounding upwards.&n;&t; */
id|start_pfn
op_assign
id|PFN_UP
c_func
(paren
id|__pa
c_func
(paren
op_amp
id|_end
)paren
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_BLK_DEV_INITRD */
multiline_comment|/* Find the highest page frame number we have available.  */
id|max_pfn
op_assign
l_int|0
suffix:semicolon
id|first_usable_pfn
op_assign
op_minus
l_int|1UL
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
id|boot_mem_map.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|type
op_ne
id|BOOT_MEM_RAM
)paren
r_continue
suffix:semicolon
id|start
op_assign
id|PFN_UP
c_func
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
)paren
suffix:semicolon
id|end
op_assign
id|PFN_DOWN
c_func
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|max_pfn
)paren
id|max_pfn
op_assign
id|end
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|first_usable_pfn
)paren
(brace
r_if
c_cond
(paren
id|start
OG
id|start_pfn
)paren
(brace
id|first_usable_pfn
op_assign
id|start
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|end
OG
id|start_pfn
)paren
(brace
id|first_usable_pfn
op_assign
id|start_pfn
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; * Determine low and high memory ranges&n;&t; */
id|max_low_pfn
op_assign
id|max_pfn
suffix:semicolon
r_if
c_cond
(paren
id|max_low_pfn
OG
id|MAXMEM_PFN
)paren
(brace
id|max_low_pfn
op_assign
id|MAXMEM_PFN
suffix:semicolon
macro_line|#ifndef CONFIG_HIGHMEM
multiline_comment|/* Maximum memory usable is what is directly addressable */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning only %dMB will be used.&bslash;n&quot;
comma
id|MAXMEM
op_rshift
l_int|20
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Use a HIGHMEM enabled kernel.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_HIGHMEM
multiline_comment|/*&n;&t; * Crude, we really should make a better attempt at detecting&n;&t; * highstart_pfn&n;&t; */
id|highstart_pfn
op_assign
id|highend_pfn
op_assign
id|max_pfn
suffix:semicolon
r_if
c_cond
(paren
id|max_pfn
OG
id|MAXMEM_PFN
)paren
(brace
id|highstart_pfn
op_assign
id|MAXMEM_PFN
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%ldMB HIGHMEM available.&bslash;n&quot;
comma
(paren
id|highend_pfn
op_minus
id|highstart_pfn
)paren
op_rshift
(paren
l_int|20
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Initialize the boot-time allocator with low memory only.  */
id|bootmap_size
op_assign
id|init_bootmem
c_func
(paren
id|first_usable_pfn
comma
id|max_low_pfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Register fully available low RAM pages with the bootmem allocator.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|boot_mem_map.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|curr_pfn
comma
id|last_pfn
comma
id|size
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Reserve usable memory.&n;&t;&t; */
r_if
c_cond
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|type
op_ne
id|BOOT_MEM_RAM
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We are rounding up the start address of usable memory:&n;&t;&t; */
id|curr_pfn
op_assign
id|PFN_UP
c_func
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr_pfn
op_ge
id|max_low_pfn
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|curr_pfn
OL
id|start_pfn
)paren
id|curr_pfn
op_assign
id|start_pfn
suffix:semicolon
multiline_comment|/*&n;&t;&t; * ... and at the end of the usable range downwards:&n;&t;&t; */
id|last_pfn
op_assign
id|PFN_DOWN
c_func
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_pfn
OG
id|max_low_pfn
)paren
id|last_pfn
op_assign
id|max_low_pfn
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Only register lowmem part of lowmem segment with bootmem.&n;&t;&t; */
id|size
op_assign
id|last_pfn
op_minus
id|curr_pfn
suffix:semicolon
r_if
c_cond
(paren
id|curr_pfn
OG
id|PFN_DOWN
c_func
(paren
id|HIGHMEM_START
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|curr_pfn
op_plus
id|size
op_minus
l_int|1
OG
id|PFN_DOWN
c_func
(paren
id|HIGHMEM_START
)paren
)paren
id|size
op_assign
id|PFN_DOWN
c_func
(paren
id|HIGHMEM_START
)paren
op_minus
id|curr_pfn
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * ... finally, did all the rounding and playing&n;&t;&t; * around just make the area go away?&n;&t;&t; */
r_if
c_cond
(paren
id|last_pfn
op_le
id|curr_pfn
)paren
r_continue
suffix:semicolon
multiline_comment|/* Register lowmem ranges */
id|free_bootmem
c_func
(paren
id|PFN_PHYS
c_func
(paren
id|curr_pfn
)paren
comma
id|PFN_PHYS
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Reserve the bootmap memory.  */
id|reserve_bootmem
c_func
(paren
id|PFN_PHYS
c_func
(paren
id|first_usable_pfn
)paren
comma
id|bootmap_size
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* Board specific code should have set up initrd_start and initrd_end */
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
r_if
c_cond
(paren
op_amp
id|__rd_start
op_ne
op_amp
id|__rd_end
)paren
(brace
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__rd_start
suffix:semicolon
id|initrd_end
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__rd_end
suffix:semicolon
)brace
id|initrd_below_start_ok
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|initrd_start
)paren
(brace
r_int
r_int
id|initrd_size
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|initrd_end
)paren
op_minus
(paren
(paren
r_int
r_char
op_star
)paren
id|initrd_start
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initial ramdisk at: 0x%p (%lu bytes)&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|initrd_start
comma
id|initrd_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PHYSADDR
c_func
(paren
id|initrd_end
)paren
OG
id|PFN_PHYS
c_func
(paren
id|max_low_pfn
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%08lx &gt; 0x%08lx)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|PHYSADDR
c_func
(paren
id|initrd_end
)paren
comma
id|PFN_PHYS
c_func
(paren
id|max_low_pfn
)paren
)paren
suffix:semicolon
id|initrd_start
op_assign
id|initrd_end
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_BLK_DEV_INITRD  */
)brace
DECL|function|resource_init
r_static
r_inline
r_void
id|resource_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|code_resource.start
op_assign
id|virt_to_phys
c_func
(paren
op_amp
id|_text
)paren
suffix:semicolon
id|code_resource.end
op_assign
id|virt_to_phys
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
id|virt_to_phys
c_func
(paren
op_amp
id|_etext
)paren
suffix:semicolon
id|data_resource.end
op_assign
id|virt_to_phys
c_func
(paren
op_amp
id|_edata
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Request address space for all standard RAM.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|boot_mem_map.nr_map
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
r_int
id|start
comma
id|end
suffix:semicolon
id|start
op_assign
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
id|end
op_assign
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|addr
op_plus
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|MAXMEM
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|end
op_ge
id|MAXMEM
)paren
id|end
op_assign
id|MAXMEM
op_minus
l_int|1
suffix:semicolon
id|res
op_assign
id|alloc_bootmem
c_func
(paren
r_sizeof
(paren
r_struct
id|resource
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|boot_mem_map.map
(braket
id|i
)braket
dot
id|type
)paren
(brace
r_case
id|BOOT_MEM_RAM
suffix:colon
r_case
id|BOOT_MEM_ROM_DATA
suffix:colon
id|res-&gt;name
op_assign
l_string|&quot;System RAM&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BOOT_MEM_RESERVED
suffix:colon
r_default
suffix:colon
id|res-&gt;name
op_assign
l_string|&quot;reserved&quot;
suffix:semicolon
)brace
id|res-&gt;start
op_assign
id|start
suffix:semicolon
id|res-&gt;end
op_assign
id|end
suffix:semicolon
id|res-&gt;flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_BUSY
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
id|res
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  We don&squot;t know which RAM region contains kernel data,&n;&t;&t; *  so we try it repeatedly and let the resource manager&n;&t;&t; *  test it.&n;&t;&t; */
id|request_resource
c_func
(paren
id|res
comma
op_amp
id|code_resource
)paren
suffix:semicolon
id|request_resource
c_func
(paren
id|res
comma
op_amp
id|data_resource
)paren
suffix:semicolon
)brace
)brace
DECL|macro|PFN_UP
macro_line|#undef PFN_UP
DECL|macro|PFN_DOWN
macro_line|#undef PFN_DOWN
DECL|macro|PFN_PHYS
macro_line|#undef PFN_PHYS
DECL|macro|MAXMEM
macro_line|#undef MAXMEM
DECL|macro|MAXMEM_PFN
macro_line|#undef MAXMEM_PFN
DECL|function|setup_arch
r_void
id|__init
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_void
id|atlas_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|baget_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cobalt_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|lasat_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ddb_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|decstation_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|deskstation_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jazz_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sni_rm200_pci_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ip22_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ev96100_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|malta_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sead_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ikos_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|momenco_ocelot_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|momenco_ocelot_g_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|momenco_ocelot_c_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nec_osprey_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nec_eagle_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|zao_capcella_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|victor_mpc30x_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ibm_workpad_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|casio_e55_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jmr3927_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|it8172_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|swarm_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|hp_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|au1x00_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|frame_info_init
c_func
(paren
r_void
)paren
suffix:semicolon
id|frame_info_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_FD
id|fd_ops
op_assign
op_amp
id|no_fd_ops
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDE
id|ide_ops
op_assign
op_amp
id|no_ide_ops
suffix:semicolon
macro_line|#endif
id|rtc_ops
op_assign
op_amp
id|no_rtc_ops
suffix:semicolon
r_switch
c_cond
(paren
id|mips_machgroup
)paren
(brace
macro_line|#ifdef CONFIG_BAGET_MIPS
r_case
id|MACH_GROUP_BAGET
suffix:colon
id|baget_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_COBALT
r_case
id|MACH_GROUP_COBALT
suffix:colon
id|cobalt_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DECSTATION
r_case
id|MACH_GROUP_DEC
suffix:colon
id|decstation_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_ATLAS
r_case
id|MACH_GROUP_UNKNOWN
suffix:colon
id|atlas_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_JAZZ
r_case
id|MACH_GROUP_JAZZ
suffix:colon
id|jazz_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_MALTA
r_case
id|MACH_GROUP_UNKNOWN
suffix:colon
id|malta_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MOMENCO_OCELOT
r_case
id|MACH_GROUP_MOMENCO
suffix:colon
id|momenco_ocelot_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MOMENCO_OCELOT_G
r_case
id|MACH_GROUP_MOMENCO
suffix:colon
id|momenco_ocelot_g_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MOMENCO_OCELOT_C
r_case
id|MACH_GROUP_MOMENCO
suffix:colon
id|momenco_ocelot_c_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_SEAD
r_case
id|MACH_GROUP_UNKNOWN
suffix:colon
id|sead_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_IP22
multiline_comment|/* As of now this is only IP22.  */
r_case
id|MACH_GROUP_SGI
suffix:colon
id|ip22_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SNI_RM200_PCI
r_case
id|MACH_GROUP_SNI_RM
suffix:colon
id|sni_rm200_pci_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DDB5074
r_case
id|MACH_GROUP_NEC_DDB
suffix:colon
id|ddb_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DDB5476
r_case
id|MACH_GROUP_NEC_DDB
suffix:colon
id|ddb_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DDB5477
r_case
id|MACH_GROUP_NEC_DDB
suffix:colon
id|ddb_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_VR41XX
r_case
id|MACH_GROUP_NEC_VR41XX
suffix:colon
r_switch
c_cond
(paren
id|mips_machtype
)paren
(brace
macro_line|#ifdef CONFIG_NEC_OSPREY
r_case
id|MACH_NEC_OSPREY
suffix:colon
id|nec_osprey_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NEC_EAGLE
r_case
id|MACH_NEC_EAGLE
suffix:colon
id|nec_eagle_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ZAO_CAPCELLA
r_case
id|MACH_ZAO_CAPCELLA
suffix:colon
id|zao_capcella_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VICTOR_MPC30X
r_case
id|MACH_VICTOR_MPC30X
suffix:colon
id|victor_mpc30x_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_IBM_WORKPAD
r_case
id|MACH_IBM_WORKPAD
suffix:colon
id|ibm_workpad_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CASIO_E55
r_case
id|MACH_CASIO_E55
suffix:colon
id|casio_e55_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TANBAC_TB0229
r_case
id|MACH_TANBAC_TB0229
suffix:colon
id|tanbac_tb0229_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_EV96100
r_case
id|MACH_GROUP_GALILEO
suffix:colon
id|ev96100_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_EV64120
r_case
id|MACH_GROUP_GALILEO
suffix:colon
id|ev64120_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_MIPS_IVR) || defined(CONFIG_MIPS_ITE8172)
r_case
id|MACH_GROUP_ITE
suffix:colon
r_case
id|MACH_GROUP_GLOBESPAN
suffix:colon
id|it8172_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LASAT
r_case
id|MACH_GROUP_LASAT
suffix:colon
id|lasat_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SOC_AU1X00
r_case
id|MACH_GROUP_ALCHEMY
suffix:colon
id|au1x00_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TOSHIBA_JMR3927
r_case
id|MACH_GROUP_TOSHIBA
suffix:colon
id|jmr3927_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TOSHIBA_RBTX4927
r_case
id|MACH_GROUP_TOSHIBA
suffix:colon
id|tx4927_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SIBYTE_BOARD
r_case
id|MACH_GROUP_SIBYTE
suffix:colon
id|swarm_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HP_LASERJET
r_case
id|MACH_GROUP_HP_LJ
suffix:colon
id|hp_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unsupported architecture&quot;
)paren
suffix:semicolon
)brace
id|strlcpy
c_func
(paren
id|command_line
comma
id|arcs_cmdline
comma
r_sizeof
id|command_line
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|saved_command_line
comma
id|command_line
comma
r_sizeof
id|saved_command_line
)paren
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
id|parse_cmdline_early
c_func
(paren
)paren
suffix:semicolon
id|bootmem_init
c_func
(paren
)paren
suffix:semicolon
id|paging_init
c_func
(paren
)paren
suffix:semicolon
id|resource_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fpu_disable
r_int
id|__init
id|fpu_disable
c_func
(paren
r_char
op_star
id|s
)paren
(brace
id|cpu_data
(braket
l_int|0
)braket
dot
id|options
op_and_assign
op_complement
id|MIPS_CPU_FPU
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nofpu&quot;
comma
id|fpu_disable
)paren
suffix:semicolon
eof
