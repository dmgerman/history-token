multiline_comment|/*&n; * Common prep/pmac/chrp boot and setup code.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/amigappc.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/bootx.h&gt;
macro_line|#include &lt;asm/btext.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/xmon.h&gt;
macro_line|#if defined CONFIG_KGDB
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#endif
r_extern
r_void
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
suffix:semicolon
r_extern
r_void
id|bootx_init
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|phys
)paren
suffix:semicolon
r_extern
r_void
id|identify_cpu
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_void
id|do_cpu_ftr_fixups
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_void
id|reloc_got2
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KGDB
r_extern
r_void
id|kgdb_map_scc
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|ppc6xx_idle
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|boot_infos_t
op_star
id|boot_infos
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
DECL|variable|ppc_ide_md
r_struct
id|ide_machdep_calls
id|ppc_ide_md
suffix:semicolon
DECL|variable|sysmap
r_char
op_star
id|sysmap
suffix:semicolon
DECL|variable|sysmap_size
r_int
r_int
id|sysmap_size
suffix:semicolon
multiline_comment|/* Used with the BI_MEMSIZE bootinfo parameter to store the memory&n;   size value reported by the boot loader. */
DECL|variable|boot_mem_size
r_int
r_int
id|boot_mem_size
suffix:semicolon
DECL|variable|ISA_DMA_THRESHOLD
r_int
r_int
id|ISA_DMA_THRESHOLD
suffix:semicolon
DECL|variable|DMA_MODE_READ
DECL|variable|DMA_MODE_WRITE
r_int
r_int
id|DMA_MODE_READ
comma
id|DMA_MODE_WRITE
suffix:semicolon
macro_line|#ifdef CONFIG_ALL_PPC
DECL|variable|_machine
r_int
id|_machine
op_assign
l_int|0
suffix:semicolon
r_extern
r_void
id|prep_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
suffix:semicolon
r_extern
r_void
id|pmac_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
suffix:semicolon
r_extern
r_void
id|chrp_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALL_PPC */
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|variable|SYSRQ_KEY
r_int
r_int
id|SYSRQ_KEY
op_assign
l_int|0x54
suffix:semicolon
macro_line|#endif /* CONFIG_MAGIC_SYSRQ */
macro_line|#ifdef CONFIG_VGA_CONSOLE
DECL|variable|vgacon_remap_base
r_int
r_int
id|vgacon_remap_base
suffix:semicolon
macro_line|#endif
DECL|variable|ppc_md
r_struct
id|machdep_calls
id|ppc_md
suffix:semicolon
multiline_comment|/*&n; * These are used in binfmt_elf.c to put aux entries on the stack&n; * for each elf executable being started.&n; */
DECL|variable|dcache_bsize
r_int
id|dcache_bsize
suffix:semicolon
DECL|variable|icache_bsize
r_int
id|icache_bsize
suffix:semicolon
DECL|variable|ucache_bsize
r_int
id|ucache_bsize
suffix:semicolon
macro_line|#if defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_FB_VGA16) || &bslash;&n;    defined(CONFIG_FB_VGA16_MODULE) || defined(CONFIG_FB_VESA)
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
op_assign
(brace
l_int|0
comma
l_int|25
comma
multiline_comment|/* orig-x, orig-y */
l_int|0
comma
multiline_comment|/* unused */
l_int|0
comma
multiline_comment|/* orig-video-page */
l_int|0
comma
multiline_comment|/* orig-video-mode */
l_int|80
comma
multiline_comment|/* orig-video-cols */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ega_ax, ega_bx, ega_cx */
l_int|25
comma
multiline_comment|/* orig-video-lines */
l_int|1
comma
multiline_comment|/* orig-video-isVGA */
l_int|16
multiline_comment|/* orig-video-points */
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_VGA_CONSOLE || CONFIG_FB_VGA16 || CONFIG_FB_VESA */
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|ppc_md
dot
id|restart
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
id|ppc_md
dot
id|power_off
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
id|ppc_md
dot
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|pm_power_off
r_void
(paren
op_star
id|pm_power_off
)paren
(paren
r_void
)paren
op_assign
id|machine_power_off
suffix:semicolon
macro_line|#ifdef CONFIG_TAU
r_extern
id|u32
id|cpu_temp
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_extern
id|u32
id|cpu_temp_both
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_TAU */
DECL|function|show_cpuinfo
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
r_int
id|i
op_assign
(paren
r_int
)paren
id|v
op_minus
l_int|1
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pvr
suffix:semicolon
r_int
r_int
id|maj
comma
id|min
suffix:semicolon
r_int
r_int
id|lpj
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|NR_CPUS
)paren
(brace
multiline_comment|/* Show summary information */
macro_line|#ifdef CONFIG_SMP
r_int
r_int
id|bogosum
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
id|NR_CPUS
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|i
)paren
)paren
id|bogosum
op_add_assign
id|cpu_data
(braket
id|i
)braket
dot
id|loops_per_jiffy
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;total bogomips&bslash;t: %lu.%02lu&bslash;n&quot;
comma
id|bogosum
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
id|bogosum
op_div
(paren
l_int|5000
op_div
id|HZ
)paren
op_mod
l_int|100
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
r_if
c_cond
(paren
id|ppc_md.show_cpuinfo
op_ne
l_int|NULL
)paren
id|err
op_assign
id|ppc_md
dot
id|show_cpuinfo
c_func
(paren
id|m
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
(paren
id|cpu_online_map
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|pvr
op_assign
id|cpu_data
(braket
id|i
)braket
dot
id|pvr
suffix:semicolon
id|lpj
op_assign
id|cpu_data
(braket
id|i
)braket
dot
id|loops_per_jiffy
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;processor&bslash;t: %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
macro_line|#else
id|pvr
op_assign
id|mfspr
c_func
(paren
id|PVR
)paren
suffix:semicolon
id|lpj
op_assign
id|loops_per_jiffy
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu&bslash;t&bslash;t: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur_cpu_spec
(braket
id|i
)braket
op_member_access_from_pointer
id|pvr_mask
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%s&quot;
comma
id|cur_cpu_spec
(braket
id|i
)braket
op_member_access_from_pointer
id|cpu_name
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;unknown (%08x)&quot;
comma
id|pvr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALTIVEC
r_if
c_cond
(paren
id|cur_cpu_spec
(braket
id|i
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_ALTIVEC
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;, altivec supported&quot;
)paren
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_TAU
r_if
c_cond
(paren
id|cur_cpu_spec
(braket
id|i
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_TAU
)paren
(brace
macro_line|#ifdef CONFIG_TAU_AVERAGE
multiline_comment|/* more straightforward, but potentially misleading */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;temperature &bslash;t: %u C (uncalibrated)&bslash;n&quot;
comma
id|cpu_temp
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* show the actual temp sensor range */
id|u32
id|temp
suffix:semicolon
id|temp
op_assign
id|cpu_temp_both
c_func
(paren
id|i
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;temperature &bslash;t: %u-%u C (uncalibrated)&bslash;n&quot;
comma
id|temp
op_amp
l_int|0xff
comma
id|temp
op_rshift
l_int|16
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* CONFIG_TAU */
r_if
c_cond
(paren
id|ppc_md.show_percpuinfo
op_ne
l_int|NULL
)paren
(brace
id|err
op_assign
id|ppc_md
dot
id|show_percpuinfo
c_func
(paren
id|m
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|PVR_VER
c_func
(paren
id|pvr
)paren
)paren
(brace
r_case
l_int|0x0020
suffix:colon
multiline_comment|/* 403 family */
id|maj
op_assign
id|PVR_MAJ
c_func
(paren
id|pvr
)paren
op_plus
l_int|1
suffix:semicolon
id|min
op_assign
id|PVR_MIN
c_func
(paren
id|pvr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1008
suffix:colon
multiline_comment|/* 740P/750P ?? */
id|maj
op_assign
(paren
(paren
id|pvr
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
)paren
op_minus
l_int|1
suffix:semicolon
id|min
op_assign
id|pvr
op_amp
l_int|0xFF
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|maj
op_assign
(paren
id|pvr
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|min
op_assign
id|pvr
op_amp
l_int|0xFF
suffix:semicolon
r_break
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;revision&bslash;t: %hd.%hd (pvr %04x %04x)&bslash;n&quot;
comma
id|maj
comma
id|min
comma
id|PVR_VER
c_func
(paren
id|pvr
)paren
comma
id|PVR_REV
c_func
(paren
id|pvr
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;bogomips&bslash;t: %lu.%02lu&bslash;n&quot;
comma
id|lpj
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|lpj
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
macro_line|#ifdef CONFIG_SMP
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
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
r_int
id|i
op_assign
op_star
id|pos
suffix:semicolon
r_return
id|i
op_le
id|NR_CPUS
ques
c_cond
(paren
r_void
op_star
)paren
(paren
id|i
op_plus
l_int|1
)paren
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
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * We&squot;re called here very early in the boot.  We determine the machine&n; * type and call the appropriate low-level setup functions.&n; *  -- Cort &lt;cort@fsmlabs.com&gt;&n; *&n; * Note that the kernel may be running at an address which is different&n; * from the address that it was linked at, so we must use RELOC/PTRRELOC&n; * to access static data (including strings).  -- paulus&n; */
id|__init
r_int
r_int
DECL|function|early_init
id|early_init
c_func
(paren
r_int
id|r3
comma
r_int
id|r4
comma
r_int
id|r5
)paren
(brace
r_extern
r_char
id|__bss_start
comma
id|_end
suffix:semicolon
r_int
r_int
id|phys
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Default */
id|phys
op_assign
id|offset
op_plus
id|KERNELBASE
suffix:semicolon
multiline_comment|/* First zero the BSS -- use memset, some arches don&squot;t have&n;&t; * caches on yet */
id|memset_io
c_func
(paren
id|PTRRELOC
c_func
(paren
op_amp
id|__bss_start
)paren
comma
l_int|0
comma
op_amp
id|_end
op_minus
op_amp
id|__bss_start
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Identify the CPU type and fix up code sections&n;&t; * that depend on which cpu we have.&n;&t; */
id|identify_cpu
c_func
(paren
id|offset
comma
l_int|0
)paren
suffix:semicolon
id|do_cpu_ftr_fixups
c_func
(paren
id|offset
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ALL_PPC)
id|reloc_got2
c_func
(paren
id|offset
)paren
suffix:semicolon
multiline_comment|/* If we came here from BootX, clear the screen,&n;&t; * set up some pointers and return. */
r_if
c_cond
(paren
(paren
id|r3
op_eq
l_int|0x426f6f58
)paren
op_logical_and
(paren
id|r5
op_eq
l_int|0
)paren
)paren
id|bootx_init
c_func
(paren
id|r4
comma
id|phys
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * don&squot;t do anything on prep&n;&t; * for now, don&squot;t use bootinfo because it breaks yaboot 0.5&n;&t; * and assume that if we didn&squot;t find a magic number, we have OF&n;&t; */
r_else
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
l_int|0
)paren
op_ne
l_int|0xdeadc0de
)paren
id|phys
op_assign
id|prom_init
c_func
(paren
id|r3
comma
id|r4
comma
(paren
id|prom_entry
)paren
id|r5
)paren
suffix:semicolon
id|reloc_got2
c_func
(paren
op_minus
id|offset
)paren
suffix:semicolon
macro_line|#endif
r_return
id|phys
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ALL_PPC
multiline_comment|/*&n; * Assume here that all clock rates are the same in a&n; * smp system.  -- Cort&n; */
r_int
id|__openfirmware
DECL|function|of_show_percpuinfo
id|of_show_percpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_int
id|i
)paren
(brace
r_struct
id|device_node
op_star
id|cpu_node
suffix:semicolon
r_int
op_star
id|fp
comma
id|s
suffix:semicolon
id|cpu_node
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_node
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
l_int|0
suffix:semicolon
id|s
OL
id|i
op_logical_and
id|cpu_node-&gt;next
suffix:semicolon
id|s
op_increment
)paren
id|cpu_node
op_assign
id|cpu_node-&gt;next
suffix:semicolon
id|fp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu_node
comma
l_string|&quot;clock-frequency&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fp
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;clock&bslash;t&bslash;t: %dMHz&bslash;n&quot;
comma
op_star
id|fp
op_div
l_int|1000000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|intuit_machine_type
id|intuit_machine_type
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|model
suffix:semicolon
r_struct
id|device_node
op_star
id|root
suffix:semicolon
multiline_comment|/* ask the OF info if we&squot;re a chrp or pmac */
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root
op_ne
l_int|0
)paren
(brace
multiline_comment|/* assume pmac unless proven to be chrp -- Cort */
id|_machine
op_assign
id|_MACH_Pmac
suffix:semicolon
id|model
op_assign
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;device_type&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;chrp&quot;
comma
id|model
comma
l_int|4
)paren
)paren
id|_machine
op_assign
id|_MACH_chrp
suffix:semicolon
r_else
(brace
id|model
op_assign
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;IBM&quot;
comma
l_int|3
)paren
)paren
id|_machine
op_assign
id|_MACH_chrp
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * The ALL_PPC version of platform_init...&n; */
r_void
id|__init
DECL|function|platform_init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_if
c_cond
(paren
id|boot_text_mapped
)paren
(brace
id|btext_clearscreen
c_func
(paren
)paren
suffix:semicolon
id|btext_welcome
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* if we didn&squot;t get any bootinfo telling us what we are... */
r_if
c_cond
(paren
id|_machine
op_eq
l_int|0
)paren
(brace
multiline_comment|/* prep boot loader tells us if we&squot;re prep or not */
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|KERNELBASE
)paren
op_eq
(paren
l_int|0xdeadc0de
)paren
)paren
id|_machine
op_assign
id|_MACH_prep
suffix:semicolon
)brace
multiline_comment|/* not much more to do here, if prep */
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_prep
)paren
(brace
id|prep_init
c_func
(paren
id|r3
comma
id|r4
comma
id|r5
comma
id|r6
comma
id|r7
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* prom_init has already been called from __start */
r_if
c_cond
(paren
id|boot_infos
)paren
id|relocate_nodes
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If we aren&squot;t PReP, we can find out if we&squot;re Pmac&n;&t; * or CHRP with this. */
r_if
c_cond
(paren
id|_machine
op_eq
l_int|0
)paren
id|intuit_machine_type
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* finish_device_tree may need _machine defined. */
id|finish_device_tree
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we were booted via quik, r3 points to the physical&n;&t; * address of the command-line parameters.&n;&t; * If we were booted from an xcoff image (i.e. netbooted or&n;&t; * booted from floppy), we get the command line from the&n;&t; * bootargs property of the /chosen node.&n;&t; * If an initial ramdisk is present, r3 and r4&n;&t; * are used for initrd_start and initrd_size,&n;&t; * otherwise they contain 0xdeadbeef.  &n;&t; */
id|cmd_line
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|r3
op_ge
l_int|0x4000
op_logical_and
id|r3
OL
l_int|0x800000
op_logical_and
id|r4
op_eq
l_int|0
)paren
(brace
id|strlcpy
c_func
(paren
id|cmd_line
comma
(paren
r_char
op_star
)paren
id|r3
op_plus
id|KERNELBASE
comma
r_sizeof
(paren
id|cmd_line
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|boot_infos
op_ne
l_int|0
)paren
(brace
multiline_comment|/* booted by BootX - check for ramdisk */
r_if
c_cond
(paren
id|boot_infos-&gt;kernelParamsOffset
op_ne
l_int|0
)paren
id|strlcpy
c_func
(paren
id|cmd_line
comma
(paren
r_char
op_star
)paren
id|boot_infos
op_plus
id|boot_infos-&gt;kernelParamsOffset
comma
r_sizeof
(paren
id|cmd_line
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|boot_infos-&gt;ramDisk
)paren
(brace
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
id|boot_infos
op_plus
id|boot_infos-&gt;ramDisk
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|boot_infos-&gt;ramDiskSize
suffix:semicolon
id|initrd_below_start_ok
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
r_struct
id|device_node
op_star
id|chosen
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|r3
op_logical_and
id|r4
op_logical_and
id|r4
op_ne
l_int|0xdeadbeef
)paren
(brace
r_if
c_cond
(paren
id|r3
OL
id|KERNELBASE
)paren
id|r3
op_add_assign
id|KERNELBASE
suffix:semicolon
id|initrd_start
op_assign
id|r3
suffix:semicolon
id|initrd_end
op_assign
id|r3
op_plus
id|r4
suffix:semicolon
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
id|initrd_below_start_ok
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
id|chosen
op_assign
id|find_devices
c_func
(paren
l_string|&quot;chosen&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chosen
op_ne
l_int|NULL
)paren
(brace
id|p
op_assign
id|get_property
c_func
(paren
id|chosen
comma
l_string|&quot;bootargs&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_logical_and
op_star
id|p
)paren
(brace
id|strlcpy
c_func
(paren
id|cmd_line
comma
id|p
comma
r_sizeof
(paren
id|cmd_line
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#ifdef CONFIG_ADB
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;adb_sync&quot;
)paren
)paren
(brace
r_extern
r_int
id|__adb_probe_sync
suffix:semicolon
id|__adb_probe_sync
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ADB */&t;
r_switch
c_cond
(paren
id|_machine
)paren
(brace
r_case
id|_MACH_Pmac
suffix:colon
id|pmac_init
c_func
(paren
id|r3
comma
id|r4
comma
id|r5
comma
id|r6
comma
id|r7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_MACH_chrp
suffix:colon
id|chrp_init
c_func
(paren
id|r3
comma
id|r4
comma
id|r5
comma
id|r6
comma
id|r7
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_ALL_PPC */
DECL|function|find_bootinfo
r_struct
id|bi_record
op_star
id|find_bootinfo
c_func
(paren
r_void
)paren
(brace
r_struct
id|bi_record
op_star
id|rec
suffix:semicolon
r_extern
r_char
id|__bss_start
(braket
)braket
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
id|_ALIGN
c_func
(paren
(paren
id|ulong
)paren
id|__bss_start
op_plus
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
comma
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;tag
op_ne
id|BI_FIRST
)paren
(brace
multiline_comment|/*&n;&t;&t; * This 0x10000 offset is a terrible hack but it will go away when&n;&t;&t; * we have the bootloader handle all the relocation and&n;&t;&t; * prom calls -- Cort&n;&t;&t; */
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
id|_ALIGN
c_func
(paren
(paren
id|ulong
)paren
id|__bss_start
op_plus
l_int|0x10000
op_plus
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
comma
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec-&gt;tag
op_ne
id|BI_FIRST
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|rec
suffix:semicolon
)brace
DECL|function|parse_bootinfo
r_void
id|parse_bootinfo
c_func
(paren
r_struct
id|bi_record
op_star
id|rec
)paren
(brace
r_if
c_cond
(paren
id|rec
op_eq
l_int|NULL
op_logical_or
id|rec-&gt;tag
op_ne
id|BI_FIRST
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|rec-&gt;tag
op_ne
id|BI_LAST
)paren
(brace
id|ulong
op_star
id|data
op_assign
id|rec-&gt;data
suffix:semicolon
r_switch
c_cond
(paren
id|rec-&gt;tag
)paren
(brace
r_case
id|BI_CMD_LINE
suffix:colon
id|memcpy
c_func
(paren
id|cmd_line
comma
(paren
r_void
op_star
)paren
id|data
comma
id|rec-&gt;size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_SYSMAP
suffix:colon
id|sysmap
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
id|data
(braket
l_int|0
)braket
op_ge
(paren
id|KERNELBASE
)paren
)paren
ques
c_cond
id|data
(braket
l_int|0
)braket
suffix:colon
(paren
id|data
(braket
l_int|0
)braket
op_plus
id|KERNELBASE
)paren
)paren
suffix:semicolon
id|sysmap_size
op_assign
id|data
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_case
id|BI_INITRD
suffix:colon
id|initrd_start
op_assign
id|data
(braket
l_int|0
)braket
op_plus
id|KERNELBASE
suffix:semicolon
id|initrd_end
op_assign
id|data
(braket
l_int|0
)braket
op_plus
id|data
(braket
l_int|1
)braket
op_plus
id|KERNELBASE
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
macro_line|#ifdef CONFIG_ALL_PPC
r_case
id|BI_MACHTYPE
suffix:colon
id|_machine
op_assign
id|data
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_ALL_PPC */
r_case
id|BI_MEMSIZE
suffix:colon
id|boot_mem_size
op_assign
id|data
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
id|ulong
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Find out what kind of machine we&squot;re on and save any data we need&n; * from the early boot process (devtree is copied on pmac by prom_init()).&n; * This is called very early on the boot process, after a minimal&n; * MMU environment has been set up but before MMU_init is called.&n; */
r_void
id|__init
DECL|function|machine_init
id|machine_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
macro_line|#ifdef CONFIG_CMDLINE
id|strcpy
c_func
(paren
id|cmd_line
comma
id|CONFIG_CMDLINE
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_CMDLINE */
macro_line|#if defined(CONFIG_6xx)
id|ppc_md.power_save
op_assign
id|ppc6xx_idle
suffix:semicolon
macro_line|#endif
id|platform_init
c_func
(paren
id|r3
comma
id|r4
comma
id|r5
comma
id|r6
comma
id|r7
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;id mach(): done&quot;
comma
l_int|0x200
)paren
suffix:semicolon
)brace
multiline_comment|/* Checks &quot;l2cr=xxxx&quot; command-line option */
DECL|function|ppc_setup_l2cr
r_int
id|__init
id|ppc_setup_l2cr
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
id|cur_cpu_spec
(braket
l_int|0
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_L2CR
)paren
(brace
r_int
r_int
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;l2cr set to %lx&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
id|_set_L2CR
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* force invalidate by disable cache */
id|_set_L2CR
c_func
(paren
id|val
)paren
suffix:semicolon
multiline_comment|/* and enable it */
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;l2cr=&quot;
comma
id|ppc_setup_l2cr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NVRAM
multiline_comment|/* Generic nvram hooks we now look into ppc_md.nvram_read_val&n; * on pmac too ;)&n; * //XX Those 2 could be moved to headers&n; */
r_int
r_char
DECL|function|nvram_read_byte
id|nvram_read_byte
c_func
(paren
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.nvram_read_val
)paren
r_return
id|ppc_md
dot
id|nvram_read_val
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
l_int|0xff
suffix:semicolon
)brace
r_void
DECL|function|nvram_write_byte
id|nvram_write_byte
c_func
(paren
r_int
r_char
id|val
comma
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.nvram_write_val
)paren
id|ppc_md
dot
id|nvram_write_val
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NVRAM */
DECL|function|ppc_init
r_int
id|__init
id|ppc_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* clear the progress line */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;             &quot;
comma
l_int|0xffff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.init
op_ne
l_int|NULL
)paren
(brace
id|ppc_md
dot
id|init
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ppc_init
id|arch_initcall
c_func
(paren
id|ppc_init
)paren
suffix:semicolon
multiline_comment|/* Warning, IO base is not yet inited */
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
r_extern
r_int
id|panic_timeout
suffix:semicolon
r_extern
r_char
id|_etext
(braket
)braket
comma
id|_edata
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|klimit
suffix:semicolon
r_extern
r_void
id|do_init_bootmem
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* so udelay does something sensible, assume &lt;= 1000 bogomips */
id|loops_per_jiffy
op_assign
l_int|500000000
op_div
id|HZ
suffix:semicolon
macro_line|#ifdef CONFIG_ALL_PPC
multiline_comment|/* This could be called &quot;early setup arch&quot;, it must be done&n;&t; * now because xmon need it&n;&t; */
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
id|pmac_feature_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* New cool way */
macro_line|#endif /* CONFIG_ALL_PPC */
macro_line|#ifdef CONFIG_XMON
id|xmon_map_scc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;xmon&quot;
)paren
)paren
id|xmon
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_XMON */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;setup_arch: enter&quot;
comma
l_int|0x3eab
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_KGDB)
id|kgdb_map_scc
c_func
(paren
)paren
suffix:semicolon
id|set_debug_traps
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;nokgdb&quot;
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;kgdb default breakpoint deactivated on command line&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;kgdb default breakpoint activated&bslash;n&quot;
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Set cache line size based on type of cpu as a default.&n;&t; * Systems with OF can look in the properties on the cpu node(s)&n;&t; * for a possibly more accurate value.&n;&t; */
r_if
c_cond
(paren
id|cur_cpu_spec
(braket
l_int|0
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_SPLIT_ID_CACHE
)paren
(brace
id|dcache_bsize
op_assign
id|cur_cpu_spec
(braket
l_int|0
)braket
op_member_access_from_pointer
id|dcache_bsize
suffix:semicolon
id|icache_bsize
op_assign
id|cur_cpu_spec
(braket
l_int|0
)braket
op_member_access_from_pointer
id|icache_bsize
suffix:semicolon
id|ucache_bsize
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|ucache_bsize
op_assign
id|dcache_bsize
op_assign
id|icache_bsize
op_assign
id|cur_cpu_spec
(braket
l_int|0
)braket
op_member_access_from_pointer
id|dcache_bsize
suffix:semicolon
multiline_comment|/* reboot on panic */
id|panic_timeout
op_assign
l_int|180
suffix:semicolon
id|init_mm.start_code
op_assign
id|PAGE_OFFSET
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
id|klimit
suffix:semicolon
multiline_comment|/* Save unparsed command line copy for /proc/cmdline */
id|strcpy
c_func
(paren
id|saved_command_line
comma
id|cmd_line
)paren
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|cmd_line
suffix:semicolon
multiline_comment|/* set up the bootmem stuff with available memory */
id|do_init_bootmem
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;setup_arch: bootmem&quot;
comma
l_int|0x3eab
)paren
suffix:semicolon
id|ppc_md
dot
id|setup_arch
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;arch: exit&quot;
comma
l_int|0x3eab
)paren
suffix:semicolon
id|paging_init
c_func
(paren
)paren
suffix:semicolon
id|sort_exception_table
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* this is for modules since _machine can be a define -- Cort */
id|ppc_md.ppc_machine
op_assign
id|_machine
suffix:semicolon
)brace
eof
