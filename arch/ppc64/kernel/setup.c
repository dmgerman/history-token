multiline_comment|/*&n; * &n; * Common boot and setup code.&n; *&n; * Copyright (C) 2001 PPC64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/time.h&gt;
r_extern
r_int
r_int
id|klimit
suffix:semicolon
multiline_comment|/* extern void *stab; */
r_extern
id|HTAB
id|htab_data
suffix:semicolon
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
r_extern
r_int
r_int
id|embedded_sysmap_start
suffix:semicolon
r_extern
r_int
r_int
id|embedded_sysmap_end
suffix:semicolon
DECL|variable|have_of
r_int
id|have_of
op_assign
l_int|1
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
r_extern
r_void
id|chrp_init_map_io_space
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iSeries_init_early
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pSeries_init_early
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pSeriesLP_init_early
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mm_init_ppc64
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|decr_overclock
r_int
r_int
id|decr_overclock
op_assign
l_int|1
suffix:semicolon
DECL|variable|decr_overclock_proc0
r_int
r_int
id|decr_overclock_proc0
op_assign
l_int|1
suffix:semicolon
DECL|variable|decr_overclock_set
r_int
r_int
id|decr_overclock_set
op_assign
l_int|0
suffix:semicolon
DECL|variable|decr_overclock_proc0_set
r_int
r_int
id|decr_overclock_proc0_set
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
r_extern
r_void
id|xmon_map_scc
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
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
r_void
id|parse_cmd_line
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
r_int
id|parse_bootinfo
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|variable|SYSRQ_KEY
r_int
r_int
id|SYSRQ_KEY
suffix:semicolon
macro_line|#endif /* CONFIG_MAGIC_SYSRQ */
DECL|variable|ppc_md
r_struct
id|machdep_calls
id|ppc_md
suffix:semicolon
multiline_comment|/*&n; * Perhaps we can put the pmac screen_info[] here&n; * on pmac as well so we don&squot;t need the ifdef&squot;s.&n; * Until we get multiple-console support in here&n; * that is.  -- Cort&n; * Maybe tie it to serial consoles, since this is really what&n; * these processors use on existing boards.  -- Dan&n; */
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
multiline_comment|/*&n; * Initialize the PPCDBG state.  Called before relocation has been enabled.&n; */
DECL|function|ppcdbg_initialize
r_void
id|ppcdbg_initialize
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|naca_struct
op_star
id|_naca
op_assign
id|RELOC
c_func
(paren
id|naca
)paren
suffix:semicolon
id|_naca-&gt;debug_switch
op_assign
id|PPC_DEBUG_DEFAULT
suffix:semicolon
multiline_comment|/* | PPCDBG_BUSWALK | PPCDBG_PHBINIT | PPCDBG_MM | PPCDBG_MMINIT | PPCDBG_TCEINIT | PPCDBG_TCE */
suffix:semicolon
)brace
multiline_comment|/*&n; * Do some initial setup of the system.  The paramters are those which &n; * were passed in from the bootloader.&n; */
DECL|function|setup_system
r_void
id|setup_system
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
multiline_comment|/* This should be fixed properly in kernel/resource.c */
id|iomem_resource.end
op_assign
id|MEM_SPACE_LIMIT
suffix:semicolon
macro_line|#ifdef CONFIG_XMON_DEFAULT
id|debugger
op_assign
id|xmon
suffix:semicolon
id|debugger_bpt
op_assign
id|xmon_bpt
suffix:semicolon
id|debugger_sstep
op_assign
id|xmon_sstep
suffix:semicolon
id|debugger_iabr_match
op_assign
id|xmon_iabr_match
suffix:semicolon
id|debugger_dabr_match
op_assign
id|xmon_dabr_match
suffix:semicolon
macro_line|#endif
multiline_comment|/* pSeries systems are identified in prom.c via OF. */
r_if
c_cond
(paren
id|itLpNaca.xLparInstalled
op_eq
l_int|1
)paren
id|naca-&gt;platform
op_assign
id|PLATFORM_ISERIES_LPAR
suffix:semicolon
r_switch
c_cond
(paren
id|naca-&gt;platform
)paren
(brace
r_case
id|PLATFORM_ISERIES_LPAR
suffix:colon
id|iSeries_init_early
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_PSERIES
r_case
id|PLATFORM_PSERIES
suffix:colon
id|pSeries_init_early
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|initrd_start
op_assign
id|initrd_end
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|parse_bootinfo
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PLATFORM_PSERIES_LPAR
suffix:colon
id|pSeriesLP_init_early
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|initrd_start
op_assign
id|initrd_end
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|parse_bootinfo
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
id|udbg_puts
c_func
(paren
l_string|&quot;&bslash;n-----------------------------------------------------&bslash;n&quot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;Naca Info...&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca                       = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|naca
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;processorCount       = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;processorCount
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;physicalMemorySize   = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;physicalMemorySize
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;dCacheL1LineSize     = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;dCacheL1LineSize
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;dCacheL1LogLineSize  = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;dCacheL1LogLineSize
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;dCacheL1LinesPerPage = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;dCacheL1LinesPerPage
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;iCacheL1LineSize     = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;iCacheL1LineSize
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;iCacheL1LogLineSize  = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;iCacheL1LogLineSize
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;iCacheL1LinesPerPage = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;iCacheL1LinesPerPage
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;pftSize              = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;pftSize
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;serialPortAddr       = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;serialPortAddr
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;naca-&gt;interrupt_controller = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|naca-&gt;interrupt_controller
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;&bslash;nHTAB Info ...&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;htab_data.htab             = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|htab_data.htab
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;htab_data.num_ptegs        = 0x&quot;
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|htab_data.htab_num_ptegs
)paren
suffix:semicolon
id|udbg_putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
l_string|&quot;&bslash;n-----------------------------------------------------&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|naca-&gt;platform
op_amp
id|PLATFORM_PSERIES
)paren
(brace
id|finish_device_tree
c_func
(paren
)paren
suffix:semicolon
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
)brace
id|mm_init_ppc64
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|naca-&gt;platform
)paren
(brace
r_case
id|PLATFORM_ISERIES_LPAR
suffix:colon
id|iSeries_init
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* The following relies on the device tree being */
multiline_comment|/* fully configured.                             */
id|parse_cmd_line
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
)brace
)brace
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
DECL|variable|ppc_proc_freq
r_int
r_int
id|ppc_proc_freq
suffix:semicolon
DECL|variable|ppc_tb_freq
r_int
r_int
id|ppc_tb_freq
suffix:semicolon
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
r_int
r_int
id|cpu_id
op_assign
(paren
r_int
r_int
)paren
id|v
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|pvr
suffix:semicolon
r_int
r_int
id|maj
suffix:semicolon
r_int
r_int
id|min
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|cpu_id
op_eq
id|NR_CPUS
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.get_cpuinfo
op_ne
l_int|NULL
)paren
id|ppc_md
dot
id|get_cpuinfo
c_func
(paren
id|m
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|cpu_id
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
id|pvr
op_assign
id|paca
(braket
id|cpu_id
)braket
dot
id|pvr
suffix:semicolon
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
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;processor&bslash;t: %lu&bslash;n&quot;
comma
id|cpu_id
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu&bslash;t&bslash;t: &quot;
)paren
suffix:semicolon
id|pvr
op_assign
id|paca
(braket
id|cpu_id
)braket
dot
id|pvr
suffix:semicolon
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
id|PV_PULSAR
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;RS64-III (pulsar)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PV_POWER4
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;POWER4 (gp)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PV_ICESTAR
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;RS64-III (icestar)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PV_SSTAR
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;RS64-IV (sstar)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PV_630
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;POWER3 (630)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PV_630p
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;POWER3 (630+)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;Unknown (%08x)&bslash;n&quot;
comma
id|pvr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Assume here that all clock rates are the same in a&n;&t; * smp system.  -- Cort&n;&t; */
r_if
c_cond
(paren
id|naca-&gt;platform
op_ne
id|PLATFORM_ISERIES_LPAR
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
id|cpu_node
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
)brace
)brace
r_if
c_cond
(paren
id|ppc_md.setup_residual
op_ne
l_int|NULL
)paren
id|ppc_md
dot
id|setup_residual
c_func
(paren
id|m
comma
id|cpu_id
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;revision&bslash;t: %hd.%hd&bslash;n&bslash;n&quot;
comma
id|maj
comma
id|min
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
op_le
id|NR_CPUS
ques
c_cond
(paren
r_void
op_star
)paren
(paren
(paren
op_star
id|pos
)paren
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
multiline_comment|/*&n; * Fetch the cmd_line from open firmware. */
DECL|function|parse_cmd_line
r_void
id|parse_cmd_line
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
(paren
id|initrd_start
op_eq
l_int|0
)paren
op_logical_and
id|r3
op_logical_and
id|r4
op_logical_and
id|r4
op_ne
l_int|0xdeadbeef
)paren
(brace
id|initrd_start
op_assign
(paren
id|r3
op_ge
id|KERNELBASE
)paren
ques
c_cond
id|r3
suffix:colon
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|r3
)paren
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
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
id|cmd_line
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
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
op_ne
l_int|NULL
op_logical_and
id|p
(braket
l_int|0
)braket
op_ne
l_int|0
)paren
id|strncpy
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
id|cmd_line
(braket
r_sizeof
(paren
id|cmd_line
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Look for mem= option on command line */
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;mem=&quot;
)paren
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
r_int
id|maxmem
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
r_int
id|__max_memory
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|cmd_line
suffix:semicolon
(paren
id|p
op_assign
id|strstr
c_func
(paren
id|q
comma
l_string|&quot;mem=&quot;
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)paren
(brace
id|q
op_assign
id|p
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p
OG
id|cmd_line
op_logical_and
id|p
(braket
op_minus
l_int|1
)braket
op_ne
l_char|&squot; &squot;
)paren
r_continue
suffix:semicolon
id|maxmem
op_assign
id|simple_strtoul
c_func
(paren
id|q
comma
op_amp
id|q
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|q
op_eq
l_char|&squot;k&squot;
op_logical_or
op_star
id|q
op_eq
l_char|&squot;K&squot;
)paren
(brace
id|maxmem
op_lshift_assign
l_int|10
suffix:semicolon
op_increment
id|q
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|q
op_eq
l_char|&squot;m&squot;
op_logical_or
op_star
id|q
op_eq
l_char|&squot;M&squot;
)paren
(brace
id|maxmem
op_lshift_assign
l_int|20
suffix:semicolon
op_increment
id|q
suffix:semicolon
)brace
)brace
id|__max_memory
op_assign
id|maxmem
suffix:semicolon
)brace
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;id mach: done&quot;
comma
l_int|0x200
)paren
suffix:semicolon
)brace
DECL|function|bi_tag2str
r_char
op_star
id|bi_tag2str
c_func
(paren
r_int
r_int
id|tag
)paren
(brace
r_switch
c_cond
(paren
id|tag
)paren
(brace
r_case
id|BI_FIRST
suffix:colon
r_return
l_string|&quot;BI_FIRST&quot;
suffix:semicolon
r_case
id|BI_LAST
suffix:colon
r_return
l_string|&quot;BI_LAST&quot;
suffix:semicolon
r_case
id|BI_CMD_LINE
suffix:colon
r_return
l_string|&quot;BI_CMD_LINE&quot;
suffix:semicolon
r_case
id|BI_BOOTLOADER_ID
suffix:colon
r_return
l_string|&quot;BI_BOOTLOADER_ID&quot;
suffix:semicolon
r_case
id|BI_INITRD
suffix:colon
r_return
l_string|&quot;BI_INITRD&quot;
suffix:semicolon
r_case
id|BI_SYSMAP
suffix:colon
r_return
l_string|&quot;BI_SYSMAP&quot;
suffix:semicolon
r_case
id|BI_MACHTYPE
suffix:colon
r_return
l_string|&quot;BI_MACHTYPE&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;BI_UNKNOWN&quot;
suffix:semicolon
)brace
)brace
DECL|function|parse_bootinfo
r_int
id|parse_bootinfo
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
op_star
id|sysmap
suffix:semicolon
r_extern
r_int
r_int
id|sysmap_size
suffix:semicolon
id|rec
op_assign
id|prom.bi_recs
suffix:semicolon
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
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|rec-&gt;tag
op_ne
id|BI_LAST
suffix:semicolon
id|rec
op_assign
id|bi_rec_next
c_func
(paren
id|rec
)paren
)paren
(brace
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
id|rec-&gt;data
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
id|rec-&gt;data
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
id|rec-&gt;data
(braket
l_int|0
)braket
suffix:colon
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|rec-&gt;data
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|sysmap_size
op_assign
id|rec-&gt;data
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
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|rec-&gt;data
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|rec-&gt;data
(braket
l_int|1
)braket
suffix:semicolon
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
id|initrd_below_start_ok
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot; &quot;
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
DECL|function|ppc64_calibrate_delay
r_void
id|__init
id|ppc64_calibrate_delay
c_func
(paren
r_void
)paren
(brace
id|loops_per_jiffy
op_assign
id|tb_ticks_per_jiffy
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Calibrating delay loop... %lu.%02lu BogoMips&bslash;n&quot;
comma
id|loops_per_jiffy
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
id|loops_per_jiffy
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
)brace
r_extern
r_void
(paren
op_star
id|calibrate_delay
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sort_exception_table
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Called into from start_kernel, after lock_kernel has been called.&n; * Initializes bootmem, which is unsed to manage page allocation until&n; * mem_init is called.&n; */
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
r_void
id|do_init_bootmem
c_func
(paren
r_void
)paren
suffix:semicolon
id|calibrate_delay
op_assign
id|ppc64_calibrate_delay
suffix:semicolon
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
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;setup_arch:enter&quot;
comma
l_int|0x3eab
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set cache line size based on type of cpu as a default.&n;&t; * Systems with OF can look in the properties on the cpu node(s)&n;&t; * for a possibly more accurate value.&n;&t; */
id|dcache_bsize
op_assign
id|naca-&gt;dCacheL1LineSize
suffix:semicolon
id|icache_bsize
op_assign
id|naca-&gt;iCacheL1LineSize
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
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;setup_arch:bootmem&quot;
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
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;setup_arch: exit&quot;
comma
l_int|0x3eab
)paren
suffix:semicolon
)brace
DECL|function|set_spread_lpevents
r_int
id|set_spread_lpevents
c_func
(paren
r_char
op_star
id|str
)paren
(brace
multiline_comment|/* The parameter is the number of processors to share in processing lp events */
r_int
r_int
id|i
suffix:semicolon
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
r_if
c_cond
(paren
(paren
id|val
OG
l_int|0
)paren
op_logical_and
(paren
id|val
op_le
id|MAX_PACAS
)paren
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|val
suffix:semicolon
op_increment
id|i
)paren
id|paca
(braket
id|i
)braket
dot
id|lpQueuePtr
op_assign
id|paca
(braket
l_int|0
)braket
dot
id|lpQueuePtr
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;lpevent processing spread over %ld processors&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;invalid spreaqd_lpevents %ld&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This should only be called on processor 0 during calibrate decr */
DECL|function|setup_default_decr
r_void
id|setup_default_decr
c_func
(paren
r_void
)paren
(brace
r_struct
id|paca_struct
op_star
id|lpaca
op_assign
id|get_paca
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|decr_overclock_set
op_logical_and
op_logical_neg
id|decr_overclock_proc0_set
)paren
id|decr_overclock_proc0
op_assign
id|decr_overclock
suffix:semicolon
id|lpaca-&gt;default_decr
op_assign
id|tb_ticks_per_jiffy
op_div
id|decr_overclock_proc0
suffix:semicolon
id|lpaca-&gt;next_jiffy_update_tb
op_assign
id|get_tb
c_func
(paren
)paren
op_plus
id|tb_ticks_per_jiffy
suffix:semicolon
)brace
DECL|function|set_decr_overclock_proc0
r_int
id|set_decr_overclock_proc0
c_func
(paren
r_char
op_star
id|str
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
r_if
c_cond
(paren
(paren
id|val
op_ge
l_int|1
)paren
op_logical_and
(paren
id|val
op_le
l_int|48
)paren
)paren
(brace
id|decr_overclock_proc0_set
op_assign
l_int|1
suffix:semicolon
id|decr_overclock_proc0
op_assign
id|val
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;proc 0 decrementer overclock factor of %ld&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;invalid proc 0 decrementer overclock factor of %ld&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|set_decr_overclock
r_int
id|set_decr_overclock
c_func
(paren
r_char
op_star
id|str
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
r_if
c_cond
(paren
(paren
id|val
op_ge
l_int|1
)paren
op_logical_and
(paren
id|val
op_le
l_int|48
)paren
)paren
(brace
id|decr_overclock_set
op_assign
l_int|1
suffix:semicolon
id|decr_overclock
op_assign
id|val
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;decrementer overclock factor of %ld&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;invalid decrementer overclock factor of %ld&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;spread_lpevents=&quot;
comma
id|set_spread_lpevents
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;decr_overclock_proc0=&quot;
comma
id|set_decr_overclock_proc0
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;decr_overclock=&quot;
comma
id|set_decr_overclock
)paren
suffix:semicolon
eof
