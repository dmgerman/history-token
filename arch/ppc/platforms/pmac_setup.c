multiline_comment|/*&n; *  arch/ppc/platforms/setup.c&n; *&n; *  PowerPC version &n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Adapted for Power Macintosh by Paul Mackerras&n; *    Copyright (C) 1996 Paul Mackerras (paulus@cs.anu.edu.au)&n; *&n; *  Derived from &quot;arch/alpha/kernel/setup.c&quot;&n; *    Copyright (C) 1995 Linus Torvalds&n; *&n; *  Maintained by Benjamin Herrenschmidt (benh@kernel.crashing.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/cuda.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/ohare.h&gt;
macro_line|#include &lt;asm/mediabay.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/bootx.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/btext.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &quot;pmac_pic.h&quot;
macro_line|#include &quot;mem_pieces.h&quot;
DECL|macro|SHOW_GATWICK_IRQS
macro_line|#undef SHOW_GATWICK_IRQS
r_extern
r_int
id|pmac_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pmac_get_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pmac_set_rtc_time
c_func
(paren
r_int
r_int
id|nowtime
)paren
suffix:semicolon
r_extern
r_void
id|pmac_read_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pmac_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pmac_pcibios_fixup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pmac_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pmac_ide_check_base
c_func
(paren
id|ide_ioreg_t
id|base
)paren
suffix:semicolon
r_extern
id|ide_ioreg_t
id|pmac_ide_get_base
c_func
(paren
r_int
id|index
)paren
suffix:semicolon
r_extern
r_void
id|pmac_nvram_update
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|pmac_nvram_read_byte
c_func
(paren
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|pmac_nvram_write_byte
c_func
(paren
r_int
id|addr
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_extern
r_int
id|pmac_pci_enable_device_hook
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|initial
)paren
suffix:semicolon
r_extern
r_void
id|pmac_pcibios_after_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
id|kdev_t
id|sd_find_target
c_func
(paren
r_void
op_star
id|host
comma
r_int
id|tgt
)paren
suffix:semicolon
DECL|variable|memory_node
r_struct
id|device_node
op_star
id|memory_node
suffix:semicolon
DECL|variable|drive_info
r_int
r_char
id|drive_info
suffix:semicolon
DECL|variable|ppc_override_l2cr
r_int
id|ppc_override_l2cr
op_assign
l_int|0
suffix:semicolon
DECL|variable|ppc_override_l2cr_value
r_int
id|ppc_override_l2cr_value
suffix:semicolon
DECL|variable|has_l2cache
r_int
id|has_l2cache
op_assign
l_int|0
suffix:semicolon
DECL|variable|current_root_goodness
r_static
r_int
id|current_root_goodness
op_assign
op_minus
l_int|1
suffix:semicolon
r_extern
r_char
id|saved_command_line
(braket
)braket
suffix:semicolon
r_extern
r_int
id|pmac_newworld
suffix:semicolon
DECL|macro|DEFAULT_ROOT_DEVICE
mdefine_line|#define DEFAULT_ROOT_DEVICE 0x0801&t;/* sda1 - slightly silly choice */
r_extern
r_void
id|zs_kgdb_hook
c_func
(paren
r_int
id|tty_num
)paren
suffix:semicolon
r_static
r_void
id|ohare_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_void
id|pmac_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|sys_ctrler
id|sys_ctrler_t
id|sys_ctrler
op_assign
id|SYS_CTRLER_UNKNOWN
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_struct
id|smp_ops_t
id|psurge_smp_ops
suffix:semicolon
r_extern
r_struct
id|smp_ops_t
id|core99_smp_ops
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
r_int
id|__pmac
DECL|function|pmac_show_cpuinfo
id|pmac_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_char
op_star
id|pp
suffix:semicolon
r_int
id|plen
suffix:semicolon
r_int
id|mbmodel
op_assign
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_GET_MB_INFO
comma
l_int|NULL
comma
id|PMAC_MB_INFO_MODEL
comma
l_int|0
)paren
suffix:semicolon
r_int
r_int
id|mbflags
op_assign
(paren
r_int
r_int
)paren
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_GET_MB_INFO
comma
l_int|NULL
comma
id|PMAC_MB_INFO_FLAGS
comma
l_int|0
)paren
suffix:semicolon
r_char
op_star
id|mbname
suffix:semicolon
r_if
c_cond
(paren
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_GET_MB_INFO
comma
l_int|NULL
comma
id|PMAC_MB_INFO_NAME
comma
(paren
r_int
)paren
op_amp
id|mbname
)paren
op_ne
l_int|0
)paren
id|mbname
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
multiline_comment|/* find motherboard type */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: &quot;
)paren
suffix:semicolon
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;device-tree&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_ne
l_int|NULL
)paren
(brace
id|pp
op_assign
(paren
r_char
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp
op_ne
l_int|NULL
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|pp
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;PowerMac&bslash;n&quot;
)paren
suffix:semicolon
id|pp
op_assign
(paren
r_char
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;compatible&quot;
comma
op_amp
id|plen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp
op_ne
l_int|NULL
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;motherboard&bslash;t:&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|plen
OG
l_int|0
)paren
(brace
r_int
id|l
op_assign
id|strlen
c_func
(paren
id|pp
)paren
op_plus
l_int|1
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot; %s&quot;
comma
id|pp
)paren
suffix:semicolon
id|plen
op_sub_assign
id|l
suffix:semicolon
id|pp
op_add_assign
id|l
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;PowerMac&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* print parsed model */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;detected as&bslash;t: %d (%s)&bslash;n&quot;
comma
id|mbmodel
comma
id|mbname
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pmac flags&bslash;t: %08x&bslash;n&quot;
comma
id|mbflags
)paren
suffix:semicolon
multiline_comment|/* find l2 cache info */
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;l2-cache&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|0
)paren
id|np
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;cache&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_ne
l_int|0
)paren
(brace
r_int
r_int
op_star
id|ic
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;i-cache-size&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_int
r_int
op_star
id|dc
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;d-cache-size&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;L2 cache&bslash;t:&quot;
)paren
suffix:semicolon
id|has_l2cache
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;cache-unified&quot;
comma
l_int|NULL
)paren
op_ne
l_int|0
op_logical_and
id|dc
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot; %dK unified&quot;
comma
op_star
id|dc
op_div
l_int|1024
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ic
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot; %dK instruction&quot;
comma
op_star
id|ic
op_div
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dc
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%s %dK data&quot;
comma
(paren
id|ic
ques
c_cond
l_string|&quot; +&quot;
suffix:colon
l_string|&quot;&quot;
)paren
comma
op_star
id|dc
op_div
l_int|1024
)paren
suffix:semicolon
)brace
id|pp
op_assign
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;ram-type&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot; %s&quot;
comma
id|pp
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
)brace
multiline_comment|/* find ram info */
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_ne
l_int|0
)paren
(brace
r_int
id|n
suffix:semicolon
r_struct
id|reg_property
op_star
id|reg
op_assign
(paren
r_struct
id|reg_property
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;reg&quot;
comma
op_amp
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_ne
l_int|0
)paren
(brace
r_int
r_int
id|total
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|n
op_div_assign
r_sizeof
(paren
r_struct
id|reg_property
)paren
suffix:semicolon
id|n
OG
l_int|0
suffix:semicolon
op_decrement
id|n
)paren
id|total
op_add_assign
(paren
id|reg
op_increment
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;memory&bslash;t&bslash;t: %luMB&bslash;n&quot;
comma
id|total
op_rshift
l_int|20
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Checks &quot;l2cr-value&quot; property in the registry */
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;cpus&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|0
)paren
id|np
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
id|np
op_ne
l_int|0
)paren
(brace
r_int
r_int
op_star
id|l2cr
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;l2cr-value&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l2cr
op_ne
l_int|0
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;l2cr override&bslash;t: 0x%x&bslash;n&quot;
comma
op_star
id|l2cr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Indicate newworld/oldworld */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pmac-generation&bslash;t: %s&bslash;n&quot;
comma
id|pmac_newworld
ques
c_cond
l_string|&quot;NewWorld&quot;
suffix:colon
l_string|&quot;OldWorld&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sysctrl_regs
r_static
r_volatile
id|u32
op_star
id|sysctrl_regs
suffix:semicolon
r_void
id|__init
DECL|function|pmac_setup_arch
id|pmac_setup_arch
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|cpu
suffix:semicolon
r_int
op_star
id|fp
suffix:semicolon
r_int
r_int
id|pvr
suffix:semicolon
id|pvr
op_assign
id|PVR_VER
c_func
(paren
id|mfspr
c_func
(paren
id|PVR
)paren
)paren
suffix:semicolon
multiline_comment|/* Set loops_per_jiffy to a half-way reasonable value,&n;&t;   for use until calibrate_delay gets called. */
id|cpu
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
id|cpu
op_ne
l_int|0
)paren
(brace
id|fp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu
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
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|pvr
op_eq
l_int|4
op_logical_or
id|pvr
op_ge
l_int|8
)paren
multiline_comment|/* 604, G3, G4 etc. */
id|loops_per_jiffy
op_assign
op_star
id|fp
op_div
id|HZ
suffix:semicolon
r_else
multiline_comment|/* 601, 603, etc. */
id|loops_per_jiffy
op_assign
op_star
id|fp
op_div
(paren
l_int|2
op_star
id|HZ
)paren
suffix:semicolon
)brace
r_else
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
)brace
multiline_comment|/* this area has the CPU identification register&n;&t;   and some registers used by smp boards */
id|sysctrl_regs
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|ioremap
c_func
(paren
l_int|0xf8000000
comma
l_int|0x1000
)paren
suffix:semicolon
id|ohare_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Lookup PCI hosts */
id|pmac_find_bridges
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Checks &quot;l2cr-value&quot; property in the registry */
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
r_struct
id|device_node
op_star
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;cpus&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|0
)paren
id|np
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
id|np
op_ne
l_int|0
)paren
(brace
r_int
r_int
op_star
id|l2cr
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;l2cr-value&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l2cr
op_ne
l_int|0
)paren
(brace
id|ppc_override_l2cr
op_assign
l_int|1
suffix:semicolon
id|ppc_override_l2cr_value
op_assign
op_star
id|l2cr
suffix:semicolon
id|_set_L2CR
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|_set_L2CR
c_func
(paren
id|ppc_override_l2cr_value
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|ppc_override_l2cr
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;L2CR overriden (0x%x), backside cache is %s&bslash;n&quot;
comma
id|ppc_override_l2cr_value
comma
(paren
id|ppc_override_l2cr_value
op_amp
l_int|0x80000000
)paren
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KGDB
id|zs_kgdb_hook
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ADB_CUDA
id|find_via_cuda
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|find_devices
c_func
(paren
l_string|&quot;via-cuda&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING ! Your machine is Cuda based but your kernel&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;          wasn&squot;t compiled with CONFIG_ADB_CUDA option !&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
macro_line|#ifdef CONFIG_ADB_PMU
id|find_via_pmu
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|find_devices
c_func
(paren
l_string|&quot;via-pmu&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING ! Your machine is PMU based but your kernel&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;          wasn&squot;t compiled with CONFIG_ADB_PMU option !&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
macro_line|#ifdef CONFIG_NVRAM
id|pmac_nvram_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
)paren
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
r_else
macro_line|#endif
id|ROOT_DEV
op_assign
id|DEFAULT_ROOT_DEVICE
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Check for Core99 */
r_if
c_cond
(paren
id|find_devices
c_func
(paren
l_string|&quot;uni-n&quot;
)paren
)paren
id|ppc_md.smp_ops
op_assign
op_amp
id|core99_smp_ops
suffix:semicolon
r_else
id|ppc_md.smp_ops
op_assign
op_amp
id|psurge_smp_ops
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
id|pci_create_OF_bus_map
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ohare_init
r_static
r_void
id|__init
id|ohare_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Turn on the L2 cache.&n;&t; * We assume that we have a PSX memory controller iff&n;&t; * we have an ohare I/O controller.&n;&t; */
r_if
c_cond
(paren
id|find_devices
c_func
(paren
l_string|&quot;ohare&quot;
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|sysctrl_regs
(braket
l_int|2
)braket
op_rshift
l_int|24
)paren
op_amp
l_int|0xf
)paren
op_ge
l_int|3
)paren
(brace
r_if
c_cond
(paren
id|sysctrl_regs
(braket
l_int|4
)braket
op_amp
l_int|0x10
)paren
id|sysctrl_regs
(braket
l_int|4
)braket
op_or_assign
l_int|0x04000020
suffix:semicolon
r_else
id|sysctrl_regs
(braket
l_int|4
)braket
op_or_assign
l_int|0x04000000
suffix:semicolon
r_if
c_cond
(paren
id|has_l2cache
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Level 2 cache enabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_extern
r_char
op_star
id|bootpath
suffix:semicolon
r_extern
r_char
op_star
id|bootdevice
suffix:semicolon
DECL|variable|boot_host
r_void
op_star
id|boot_host
suffix:semicolon
DECL|variable|boot_target
r_int
id|boot_target
suffix:semicolon
DECL|variable|boot_part
r_int
id|boot_part
suffix:semicolon
r_extern
id|kdev_t
id|boot_dev
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI
r_void
id|__init
DECL|function|note_scsi_host
id|note_scsi_host
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_void
op_star
id|host
)paren
(brace
r_int
id|l
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
id|l
op_assign
id|strlen
c_func
(paren
id|node-&gt;full_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bootpath
op_ne
l_int|NULL
op_logical_and
id|bootdevice
op_ne
l_int|NULL
op_logical_and
id|strncmp
c_func
(paren
id|node-&gt;full_name
comma
id|bootdevice
comma
id|l
)paren
op_eq
l_int|0
op_logical_and
(paren
id|bootdevice
(braket
id|l
)braket
op_eq
l_char|&squot;/&squot;
op_logical_or
id|bootdevice
(braket
id|l
)braket
op_eq
l_int|0
)paren
)paren
(brace
id|boot_host
op_assign
id|host
suffix:semicolon
multiline_comment|/*&n;&t;&t; * There&squot;s a bug in OF 1.0.5.  (Why am I not surprised.)&n;&t;&t; * If you pass a path like scsi/sd@1:0 to canon, it returns&n;&t;&t; * something like /bandit@F2000000/gc@10/53c94@10000/sd@0,0&n;&t;&t; * That is, the scsi target number doesn&squot;t get preserved.&n;&t;&t; * So we pick the target number out of bootpath and use that.&n;&t;&t; */
id|p
op_assign
id|strstr
c_func
(paren
id|bootpath
comma
l_string|&quot;/sd@&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
id|p
op_add_assign
l_int|4
suffix:semicolon
id|boot_target
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
l_int|NULL
)paren
id|boot_part
op_assign
id|simple_strtoul
c_func
(paren
id|p
op_plus
l_int|1
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_IDE) &amp;&amp; defined(CONFIG_BLK_DEV_IDE_PMAC)
id|kdev_t
id|__init
DECL|function|find_ide_boot
id|find_ide_boot
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_int
id|n
suffix:semicolon
id|kdev_t
id|__init
id|pmac_find_ide_boot
c_func
(paren
r_char
op_star
id|bootdevice
comma
r_int
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bootdevice
op_eq
l_int|NULL
)paren
r_return
id|NODEV
suffix:semicolon
id|p
op_assign
id|strrchr
c_func
(paren
id|bootdevice
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
id|NODEV
suffix:semicolon
id|n
op_assign
id|p
op_minus
id|bootdevice
suffix:semicolon
r_return
id|pmac_find_ide_boot
c_func
(paren
id|bootdevice
comma
id|n
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDE &amp;&amp; CONFIG_BLK_DEV_IDE_PMAC */
r_void
id|__init
DECL|function|find_boot_device
id|find_boot_device
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_SCSI) &amp;&amp; defined(CONFIG_BLK_DEV_SD)
r_if
c_cond
(paren
id|boot_host
op_ne
l_int|NULL
)paren
(brace
id|boot_dev
op_assign
id|sd_find_target
c_func
(paren
id|boot_host
comma
id|boot_target
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kdev_same
c_func
(paren
id|boot_dev
comma
id|NODEV
)paren
)paren
r_return
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_IDE) &amp;&amp; defined(CONFIG_BLK_DEV_IDE_PMAC)
id|boot_dev
op_assign
id|find_ide_boot
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|initializing
r_static
r_int
id|initializing
op_assign
l_int|1
suffix:semicolon
DECL|function|pmac_late_init
r_static
r_int
id|pmac_late_init
c_func
(paren
r_void
)paren
(brace
id|initializing
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pmac_late_init
id|late_initcall
c_func
(paren
id|pmac_late_init
)paren
suffix:semicolon
multiline_comment|/* can&squot;t be __init - can be called whenever a disk is first accessed */
r_void
id|__pmac
DECL|function|note_bootable_part
id|note_bootable_part
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|part
comma
r_int
id|goodness
)paren
(brace
r_static
r_int
id|found_boot
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initializing
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|goodness
op_le
id|current_root_goodness
)paren
op_logical_and
id|ROOT_DEV
op_ne
id|DEFAULT_ROOT_DEVICE
)paren
r_return
suffix:semicolon
id|p
op_assign
id|strstr
c_func
(paren
id|saved_command_line
comma
l_string|&quot;root=&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
l_int|NULL
op_logical_and
(paren
id|p
op_eq
id|saved_command_line
op_logical_or
id|p
(braket
op_minus
l_int|1
)braket
op_eq
l_char|&squot; &squot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|found_boot
)paren
(brace
id|find_boot_device
c_func
(paren
)paren
suffix:semicolon
id|found_boot
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kdev_same
c_func
(paren
id|boot_dev
comma
id|NODEV
)paren
op_logical_or
id|kdev_same
c_func
(paren
id|dev
comma
id|boot_dev
)paren
)paren
(brace
id|ROOT_DEV
op_assign
id|MKDEV
c_func
(paren
id|major
c_func
(paren
id|dev
)paren
comma
id|minor
c_func
(paren
id|dev
)paren
op_plus
id|part
)paren
suffix:semicolon
id|boot_dev
op_assign
id|NODEV
suffix:semicolon
id|current_root_goodness
op_assign
id|goodness
suffix:semicolon
)brace
)brace
r_void
id|__pmac
DECL|function|pmac_restart
id|pmac_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
macro_line|#ifdef CONFIG_ADB_CUDA
r_struct
id|adb_request
id|req
suffix:semicolon
macro_line|#endif /* CONFIG_ADB_CUDA */
macro_line|#ifdef CONFIG_NVRAM
id|pmac_nvram_update
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|sys_ctrler
)paren
(brace
macro_line|#ifdef CONFIG_ADB_CUDA
r_case
id|SYS_CTRLER_CUDA
suffix:colon
id|cuda_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|2
comma
id|CUDA_PACKET
comma
id|CUDA_RESET_SYSTEM
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|cuda_poll
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_ADB_CUDA */
macro_line|#ifdef CONFIG_ADB_PMU&t;&t;
r_case
id|SYS_CTRLER_PMU
suffix:colon
id|pmu_restart
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_ADB_PMU */&t;&t;
r_default
suffix:colon
suffix:semicolon
)brace
)brace
r_void
id|__pmac
DECL|function|pmac_power_off
id|pmac_power_off
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ADB_CUDA
r_struct
id|adb_request
id|req
suffix:semicolon
macro_line|#endif /* CONFIG_ADB_CUDA */
macro_line|#ifdef CONFIG_NVRAM
id|pmac_nvram_update
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|sys_ctrler
)paren
(brace
macro_line|#ifdef CONFIG_ADB_CUDA
r_case
id|SYS_CTRLER_CUDA
suffix:colon
id|cuda_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|2
comma
id|CUDA_PACKET
comma
id|CUDA_POWERDOWN
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|cuda_poll
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_ADB_CUDA */
macro_line|#ifdef CONFIG_ADB_PMU
r_case
id|SYS_CTRLER_PMU
suffix:colon
id|pmu_shutdown
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_ADB_PMU */
r_default
suffix:colon
suffix:semicolon
)brace
)brace
r_void
id|__pmac
DECL|function|pmac_halt
id|pmac_halt
c_func
(paren
r_void
)paren
(brace
id|pmac_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read in a property describing some pieces of memory.&n; */
r_static
r_int
id|__init
DECL|function|get_mem_prop
id|get_mem_prop
c_func
(paren
r_char
op_star
id|name
comma
r_struct
id|mem_pieces
op_star
id|mp
)paren
(brace
r_struct
id|reg_property
op_star
id|rp
suffix:semicolon
r_int
id|i
comma
id|s
suffix:semicolon
r_int
r_int
op_star
id|ip
suffix:semicolon
r_int
id|nac
op_assign
id|prom_n_addr_cells
c_func
(paren
id|memory_node
)paren
suffix:semicolon
r_int
id|nsc
op_assign
id|prom_n_size_cells
c_func
(paren
id|memory_node
)paren
suffix:semicolon
id|ip
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|memory_node
comma
id|name
comma
op_amp
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error: couldn&squot;t get %s property on /memory&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|s
op_div_assign
(paren
id|nsc
op_plus
id|nac
)paren
op_star
l_int|4
suffix:semicolon
id|rp
op_assign
id|mp-&gt;regions
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
id|s
suffix:semicolon
op_increment
id|i
comma
id|ip
op_add_assign
id|nac
op_plus
id|nsc
)paren
(brace
r_if
c_cond
(paren
id|nac
op_ge
l_int|2
op_logical_and
id|ip
(braket
id|nac
op_minus
l_int|2
)braket
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
id|rp-&gt;address
op_assign
id|ip
(braket
id|nac
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nsc
op_ge
l_int|2
op_logical_and
id|ip
(braket
id|nac
op_plus
id|nsc
op_minus
l_int|2
)braket
op_ne
l_int|0
)paren
id|rp-&gt;size
op_assign
op_complement
l_int|0U
suffix:semicolon
r_else
id|rp-&gt;size
op_assign
id|ip
(braket
id|nac
op_plus
id|nsc
op_minus
l_int|1
)braket
suffix:semicolon
op_increment
id|rp
suffix:semicolon
)brace
id|mp-&gt;n_regions
op_assign
id|rp
op_minus
id|mp-&gt;regions
suffix:semicolon
multiline_comment|/* Make sure the pieces are sorted. */
id|mem_pieces_sort
c_func
(paren
id|mp
)paren
suffix:semicolon
id|mem_pieces_coalesce
c_func
(paren
id|mp
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * On systems with Open Firmware, collect information about&n; * physical RAM and which pieces are already in use.&n; * At this point, we have (at least) the first 8MB mapped with a BAT.&n; * Our text, data, bss use something over 1MB, starting at 0.&n; * Open Firmware may be using 1MB at the 4MB point.&n; */
r_int
r_int
id|__init
DECL|function|pmac_find_end_of_memory
id|pmac_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|a
comma
id|total
suffix:semicolon
r_struct
id|mem_pieces
id|phys_mem
suffix:semicolon
multiline_comment|/*&n;&t; * Find out where physical memory is, and check that it&n;&t; * starts at 0 and is contiguous.  It seems that RAM is&n;&t; * always physically contiguous on Power Macintoshes.&n;&t; *&n;&t; * Supporting discontiguous physical memory isn&squot;t hard,&n;&t; * it just makes the virtual &lt;-&gt; physical mapping functions&n;&t; * more complicated (or else you end up wasting space&n;&t; * in mem_map).&n;&t; */
id|memory_node
op_assign
id|find_devices
c_func
(paren
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memory_node
op_eq
l_int|NULL
op_logical_or
op_logical_neg
id|get_mem_prop
c_func
(paren
l_string|&quot;reg&quot;
comma
op_amp
id|phys_mem
)paren
op_logical_or
id|phys_mem.n_regions
op_eq
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;No RAM??&quot;
)paren
suffix:semicolon
id|a
op_assign
id|phys_mem.regions
(braket
l_int|0
)braket
dot
id|address
suffix:semicolon
r_if
c_cond
(paren
id|a
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;RAM doesn&squot;t start at physical address 0&quot;
)paren
suffix:semicolon
id|total
op_assign
id|phys_mem.regions
(braket
l_int|0
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|phys_mem.n_regions
OG
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RAM starting at 0x%x is not contiguous&bslash;n&quot;
comma
id|phys_mem.regions
(braket
l_int|1
)braket
dot
id|address
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Using RAM from 0 to 0x%lx&bslash;n&quot;
comma
id|total
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|total
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pmac_init
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
(brace
multiline_comment|/* isa_io_base gets set in pmac_find_bridges */
id|isa_mem_base
op_assign
id|PMAC_ISA_MEM_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|PMAC_PCI_DRAM_OFFSET
suffix:semicolon
id|ISA_DMA_THRESHOLD
op_assign
op_complement
l_int|0L
suffix:semicolon
id|DMA_MODE_READ
op_assign
l_int|1
suffix:semicolon
id|DMA_MODE_WRITE
op_assign
l_int|2
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|pmac_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|pmac_show_cpuinfo
suffix:semicolon
id|ppc_md.show_percpuinfo
op_assign
id|of_show_percpuinfo
suffix:semicolon
id|ppc_md.irq_cannonicalize
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|pmac_pic_init
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|pmac_get_irq
suffix:semicolon
multiline_comment|/* Changed later on ... */
id|ppc_md.pcibios_fixup
op_assign
id|pmac_pcibios_fixup
suffix:semicolon
id|ppc_md.pcibios_enable_device_hook
op_assign
id|pmac_pci_enable_device_hook
suffix:semicolon
id|ppc_md.pcibios_after_init
op_assign
id|pmac_pcibios_after_init
suffix:semicolon
id|ppc_md.restart
op_assign
id|pmac_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|pmac_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|pmac_halt
suffix:semicolon
id|ppc_md.time_init
op_assign
id|pmac_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|pmac_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|pmac_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|pmac_calibrate_decr
suffix:semicolon
macro_line|#ifdef CONFIG_NVRAM
id|ppc_md.nvram_read_val
op_assign
id|pmac_nvram_read_byte
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|pmac_nvram_write_byte
suffix:semicolon
macro_line|#endif
id|ppc_md.find_end_of_memory
op_assign
id|pmac_find_end_of_memory
suffix:semicolon
id|ppc_md.feature_call
op_assign
id|pmac_do_feature_call
suffix:semicolon
macro_line|#ifdef CONFIG_BOOTX_TEXT
id|ppc_md.progress
op_assign
id|pmac_progress
suffix:semicolon
macro_line|#endif /* CONFIG_BOOTX_TEXT */
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
l_string|&quot;pmac_init(): exit&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BOOTX_TEXT
r_void
id|__init
DECL|function|pmac_progress
id|pmac_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
(brace
r_if
c_cond
(paren
id|boot_text_mapped
)paren
(brace
id|btext_drawstring
c_func
(paren
id|s
)paren
suffix:semicolon
id|btext_drawchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_BOOTX_TEXT */
eof
