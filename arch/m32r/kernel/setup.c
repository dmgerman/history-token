multiline_comment|/*&n; *  linux/arch/m32r/kernel/setup.c&n; *&n; *  Setup routines for Renesas M32R&n; *&n; *  Copyright (c) 2001, 2002  Hiroyuki Kondo, Hirokazu Takata,&n; *                            Hitoshi Yamamoto&n; */
multiline_comment|/* $Id$ */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#ifdef CONFIG_MMU
r_extern
r_void
id|init_mmu
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_HD)&t;&bslash;&n;&t;|| defined(CONFIG_BLK_DEV_IDE_MODULE)&t;&t;&t;&bslash;&n;&t;|| defined(CONFIG_BLK_DEV_HD_MODULE)
DECL|struct|drive_info_struct
DECL|member|dummy
DECL|variable|drive_info
r_struct
id|drive_info_struct
(brace
r_char
id|dummy
(braket
l_int|32
)braket
suffix:semicolon
)brace
id|drive_info
suffix:semicolon
macro_line|#endif
r_extern
r_char
id|_end
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Machine setup..&n; */
DECL|variable|boot_cpu_data
r_struct
id|cpuinfo_m32r
id|boot_cpu_data
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_RAM
r_extern
r_int
id|rd_doload
suffix:semicolon
multiline_comment|/* 1 = load ramdisk, 0 = don&squot;t load */
r_extern
r_int
id|rd_prompt
suffix:semicolon
multiline_comment|/* 1 = prompt for ramdisk, 0 = don&squot;t prompt */
r_extern
r_int
id|rd_image_start
suffix:semicolon
multiline_comment|/* starting block # of image */
macro_line|#endif
macro_line|#if defined(CONFIG_VGA_CONSOLE)
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
op_assign
(brace
dot
id|orig_video_lines
op_assign
l_int|25
comma
dot
id|orig_video_cols
op_assign
l_int|80
comma
dot
id|orig_video_mode
op_assign
l_int|0
comma
dot
id|orig_video_ega_bx
op_assign
l_int|0
comma
dot
id|orig_video_isVGA
op_assign
l_int|1
comma
dot
id|orig_video_points
op_assign
l_int|8
)brace
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|root_mountflags
suffix:semicolon
DECL|variable|command_line
r_static
r_char
id|command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
DECL|variable|data_resource
r_static
r_struct
id|resource
id|data_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Kernel data&quot;
comma
dot
id|start
op_assign
l_int|0
comma
dot
id|end
op_assign
l_int|0
comma
dot
id|flags
op_assign
id|IORESOURCE_BUSY
op_or
id|IORESOURCE_MEM
)brace
suffix:semicolon
DECL|variable|code_resource
r_static
r_struct
id|resource
id|code_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Kernel code&quot;
comma
dot
id|start
op_assign
l_int|0
comma
dot
id|end
op_assign
l_int|0
comma
dot
id|flags
op_assign
id|IORESOURCE_BUSY
op_or
id|IORESOURCE_MEM
)brace
suffix:semicolon
DECL|variable|memory_start
r_int
r_int
id|memory_start
suffix:semicolon
DECL|variable|memory_end
r_int
r_int
id|memory_end
suffix:semicolon
r_void
id|__init
id|setup_arch
c_func
(paren
r_char
op_star
op_star
)paren
suffix:semicolon
r_int
id|get_cpuinfo
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|function|parse_mem_cmdline
r_static
id|__inline__
r_void
id|parse_mem_cmdline
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_char
id|c
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_char
op_star
id|to
op_assign
id|command_line
suffix:semicolon
r_char
op_star
id|from
op_assign
id|COMMAND_LINE
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
multiline_comment|/* Save unparsed command line copy for /proc/cmdline */
id|memcpy
c_func
(paren
id|saved_command_line
comma
id|COMMAND_LINE
comma
id|COMMAND_LINE_SIZE
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
id|memory_start
op_assign
(paren
r_int
r_int
)paren
id|CONFIG_MEMORY_START
op_plus
id|PAGE_OFFSET
suffix:semicolon
id|memory_end
op_assign
id|memory_start
op_plus
(paren
r_int
r_int
)paren
id|CONFIG_MEMORY_SIZE
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
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
(brace
r_int
r_int
id|mem_size
suffix:semicolon
id|usermem
op_assign
l_int|1
suffix:semicolon
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
id|memory_end
op_assign
id|memory_start
op_plus
id|mem_size
suffix:semicolon
)brace
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
id|COMMAND_LINE_SIZE
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
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
r_if
c_cond
(paren
id|usermem
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;user-defined physical RAM map:&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|function|setup_memory
r_static
r_int
r_int
id|__init
id|setup_memory
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start_pfn
comma
id|max_low_pfn
comma
id|bootmap_size
suffix:semicolon
id|start_pfn
op_assign
id|PFN_UP
c_func
(paren
id|__pa
c_func
(paren
id|_end
)paren
)paren
suffix:semicolon
id|max_low_pfn
op_assign
id|PFN_DOWN
c_func
(paren
id|__pa
c_func
(paren
id|memory_end
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the boot-time allocator (with low memory only):&n;&t; */
id|bootmap_size
op_assign
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|start_pfn
comma
id|CONFIG_MEMORY_START
op_rshift
id|PAGE_SHIFT
comma
id|max_low_pfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Register fully available low RAM pages with the bootmem allocator.&n;&t; */
(brace
r_int
r_int
id|curr_pfn
suffix:semicolon
r_int
r_int
id|last_pfn
suffix:semicolon
r_int
r_int
id|pages
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We are rounding up the start address of usable memory:&n;&t;&t; */
id|curr_pfn
op_assign
id|PFN_UP
c_func
(paren
id|__pa
c_func
(paren
id|memory_start
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * ... and at the end of the usable range downwards:&n;&t;&t; */
id|last_pfn
op_assign
id|PFN_DOWN
c_func
(paren
id|__pa
c_func
(paren
id|memory_end
)paren
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
id|pages
op_assign
id|last_pfn
op_minus
id|curr_pfn
suffix:semicolon
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
id|pages
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Reserve the kernel text and&n;&t; * Reserve the bootmem bitmap. We do this in two steps (first step&n;&t; * was init_bootmem()), because this catches the (definitely buggy)&n;&t; * case of us accidentally initializing the bootmem allocator with&n;&t; * an invalid RAM area.&n;&t; */
id|reserve_bootmem
c_func
(paren
id|CONFIG_MEMORY_START
op_plus
id|PAGE_SIZE
comma
(paren
id|PFN_PHYS
c_func
(paren
id|start_pfn
)paren
op_plus
id|bootmap_size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_minus
id|CONFIG_MEMORY_START
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * reserve physical page 0 - it&squot;s a special BIOS page on many boxes,&n;&t; * enabling clean reboots, SMP operation, laptop functions.&n;&t; */
id|reserve_bootmem
c_func
(paren
id|CONFIG_MEMORY_START
comma
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * reserve memory hole&n;&t; */
macro_line|#ifdef CONFIG_MEMHOLE
id|reserve_bootmem
c_func
(paren
id|CONFIG_MEMHOLE_START
comma
id|CONFIG_MEMHOLE_SIZE
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|LOADER_TYPE
op_logical_and
id|INITRD_START
)paren
(brace
r_if
c_cond
(paren
id|INITRD_START
op_plus
id|INITRD_SIZE
op_le
(paren
id|max_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
)paren
(brace
id|reserve_bootmem
c_func
(paren
id|INITRD_START
comma
id|INITRD_SIZE
)paren
suffix:semicolon
id|initrd_start
op_assign
id|INITRD_START
ques
c_cond
id|INITRD_START
op_plus
id|PAGE_OFFSET
suffix:colon
l_int|0
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|INITRD_SIZE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;initrd:start[%08lx],size[%08lx]&bslash;n&quot;
comma
id|initrd_start
comma
id|INITRD_SIZE
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%08lx &gt; 0x%08lx)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|INITRD_START
op_plus
id|INITRD_SIZE
comma
id|max_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
id|max_low_pfn
suffix:semicolon
)brace
macro_line|#else&t;/* CONFIG_DISCONTIGMEM */
r_extern
r_int
r_int
id|setup_memory
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_DISCONTIGMEM */
DECL|macro|M32R_PCC_PCATCR
mdefine_line|#define M32R_PCC_PCATCR&t;0x00ef7014&t;/* will move to m32r.h */
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
id|ROOT_DEV
op_assign
id|old_decode_dev
c_func
(paren
id|ORIG_ROOT_DEV
)paren
suffix:semicolon
id|boot_cpu_data.cpu_clock
op_assign
id|M32R_CPUCLK
suffix:semicolon
id|boot_cpu_data.bus_clock
op_assign
id|M32R_BUSCLK
suffix:semicolon
id|boot_cpu_data.timer_divide
op_assign
id|M32R_TIMER_DIVIDE
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_RAM
id|rd_image_start
op_assign
id|RAMDISK_FLAGS
op_amp
id|RAMDISK_IMAGE_START_MASK
suffix:semicolon
id|rd_prompt
op_assign
(paren
(paren
id|RAMDISK_FLAGS
op_amp
id|RAMDISK_PROMPT_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|rd_doload
op_assign
(paren
(paren
id|RAMDISK_FLAGS
op_amp
id|RAMDISK_LOAD_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|MOUNT_ROOT_RDONLY
)paren
id|root_mountflags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
macro_line|#ifdef CONFIG_VT
macro_line|#if defined(CONFIG_VGA_CONSOLE)
id|conswitchp
op_assign
op_amp
id|vga_con
suffix:semicolon
macro_line|#elif defined(CONFIG_DUMMY_CONSOLE)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_DISCONTIGMEM
id|nodes_clear
c_func
(paren
id|node_online_map
)paren
suffix:semicolon
id|node_set_online
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|node_set_online
c_func
(paren
l_int|1
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_DISCONTIGMEM */
id|init_mm.start_code
op_assign
(paren
r_int
r_int
)paren
id|_text
suffix:semicolon
id|init_mm.end_code
op_assign
(paren
r_int
r_int
)paren
id|_etext
suffix:semicolon
id|init_mm.end_data
op_assign
(paren
r_int
r_int
)paren
id|_edata
suffix:semicolon
id|init_mm.brk
op_assign
(paren
r_int
r_int
)paren
id|_end
suffix:semicolon
id|code_resource.start
op_assign
id|virt_to_phys
c_func
(paren
id|_text
)paren
suffix:semicolon
id|code_resource.end
op_assign
id|virt_to_phys
c_func
(paren
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
id|_etext
)paren
suffix:semicolon
id|data_resource.end
op_assign
id|virt_to_phys
c_func
(paren
id|_edata
)paren
op_minus
l_int|1
suffix:semicolon
id|parse_mem_cmdline
c_func
(paren
id|cmdline_p
)paren
suffix:semicolon
id|setup_memory
c_func
(paren
)paren
suffix:semicolon
id|paging_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/*&n; *&t;Get CPU information for use by the procfs.&n; */
DECL|function|show_cpuinfo
r_static
r_int
id|show_cpuinfo
c_func
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
r_struct
id|cpuinfo_m32r
op_star
id|c
op_assign
id|v
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|c
op_minus
id|cpu_data
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif  /* CONFIG_SMP */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;processor&bslash;t: %ld&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CHIP_VDEC2
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu family&bslash;t: VDEC2&bslash;n&quot;
l_string|&quot;cache size&bslash;t: Unknown&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#elif  CONFIG_CHIP_M32700
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu family&bslash;t: M32700&bslash;n&quot;
l_string|&quot;cache size&bslash;t: I-8KB/D-8KB&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#elif  CONFIG_CHIP_M32102
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu family&bslash;t: M32102&bslash;n&quot;
l_string|&quot;cache size&bslash;t: I-8KB&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#elif  CONFIG_CHIP_OPSP
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu family&bslash;t: OPSP&bslash;n&quot;
l_string|&quot;cache size&bslash;t: I-8KB/D-8KB&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#elif  CONFIG_CHIP_MP
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu family&bslash;t: M32R-MP&bslash;n&quot;
l_string|&quot;cache size&bslash;t: I-xxKB/D-xxKB&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu family&bslash;t: Unknown&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;bogomips&bslash;t: %lu.%02lu&bslash;n&quot;
comma
id|c-&gt;loops_per_jiffy
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|c-&gt;loops_per_jiffy
op_div
(paren
l_int|5000
op_div
id|HZ
)paren
)paren
op_mod
l_int|100
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PLAT_MAPPI
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Machine&bslash;t&bslash;t: Mappi Evaluation board&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#elif CONFIG_PLAT_MAPPI2
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Machine&bslash;t&bslash;t: Mappi-II Evaluation board&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#elif  CONFIG_PLAT_M32700UT
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Machine&bslash;t&bslash;t: M32700UT Evaluation board&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#elif  CONFIG_PLAT_OPSPUT
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Machine&bslash;t&bslash;t: OPSPUT Evaluation board&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#elif  CONFIG_PLAT_USRV
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Machine&bslash;t&bslash;t: uServer&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#elif  CONFIG_PLAT_OAKS32R
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Machine&bslash;t&bslash;t: OAKS32R&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Machine&bslash;t&bslash;t: Unknown&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|PRINT_CLOCK
mdefine_line|#define PRINT_CLOCK(name, value)&t;&t;&t;&t;&bslash;&n;&t;seq_printf(m, name &quot; clock&bslash;t: %d.%02dMHz&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;((value) / 1000000), ((value) % 1000000)/10000)
id|PRINT_CLOCK
c_func
(paren
l_string|&quot;CPU&quot;
comma
(paren
r_int
)paren
id|c-&gt;cpu_clock
)paren
suffix:semicolon
id|PRINT_CLOCK
c_func
(paren
l_string|&quot;Bus&quot;
comma
(paren
r_int
)paren
id|c-&gt;bus_clock
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|c_start
r_static
r_void
op_star
id|c_start
c_func
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
r_return
op_star
id|pos
OL
id|NR_CPUS
ques
c_cond
id|cpu_data
op_plus
op_star
id|pos
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|c_next
r_static
r_void
op_star
id|c_next
c_func
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
DECL|function|c_stop
r_static
r_void
id|c_stop
c_func
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
comma
)brace
suffix:semicolon
macro_line|#endif  /* CONFIG_PROC_FS */
DECL|variable|__initdata
r_int
r_int
id|cpu_initialized
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * cpu_init() initializes state that is per-CPU. Some data is already&n; * initialized (naturally) in the bootstrap process.&n; * We reload them nevertheless, this function acts as a&n; * &squot;CPU state barrier&squot;, nothing should get across.&n; */
macro_line|#if defined(CONFIG_CHIP_VDEC2) || defined(CONFIG_CHIP_XNUX2)&t;&bslash;&n;&t;|| defined(CONFIG_CHIP_M32700) || defined(CONFIG_CHIP_M32102) &bslash;&n;&t;|| defined(CONFIG_CHIP_OPSP)
DECL|function|cpu_init
r_void
id|__init
id|cpu_init
(paren
r_void
)paren
(brace
r_int
id|cpu_id
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|cpu_id
comma
op_amp
id|cpu_initialized
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;CPU#%d already initialized!&bslash;n&quot;
comma
id|cpu_id
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Initializing CPU#%d&bslash;n&quot;
comma
id|cpu_id
)paren
suffix:semicolon
multiline_comment|/* Set up and load the per-CPU TSS and LDT */
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
multiline_comment|/* Force FPU initialization */
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|status
op_assign
l_int|0
suffix:semicolon
id|clear_used_math
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
multiline_comment|/* Set up MMU */
id|init_mmu
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Set up ICUIMASK */
id|outl
c_func
(paren
l_int|0x00070000
comma
id|M32R_ICU_IMASK_PORTL
)paren
suffix:semicolon
multiline_comment|/* imask=111 */
)brace
macro_line|#endif  /* defined(CONFIG_CHIP_VDEC2) ... */
eof
