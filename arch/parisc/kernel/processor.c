multiline_comment|/*    $Id: processor.c,v 1.1 2002/07/20 16:27:06 rhirst Exp $&n; *&n; *    Initial setup-routines for HP 9000 based hardware.&n; *&n; *    Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *    Modifications for PA-RISC (C) 1999 Helge Deller &lt;deller@gmx.de&gt;&n; *    Modifications copyright 1999 SuSE GmbH (Philipp Rumpf)&n; *    Modifications copyright 2000 Martin K. Petersen &lt;mkp@mkp.net&gt;&n; *    Modifications copyright 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *    Modifications copyright 2001 Ryan Bradetich &lt;rbradetich@uswest.net&gt;&n; *&n; *    Initial PA-RISC Version: 04-23-1999 by Helge Deller&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|macro|PCI_DEBUG
mdefine_line|#define PCI_DEBUG
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|PCI_DEBUG
macro_line|#undef PCI_DEBUG
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;&t;/* for register_parisc_driver() stuff */
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/irq.h&gt;&t;&t;/* for struct irq_region */
macro_line|#include &lt;asm/parisc-device.h&gt;
DECL|variable|boot_cpu_data
r_struct
id|system_cpuinfo_parisc
id|boot_cpu_data
suffix:semicolon
DECL|variable|cpu_data
r_struct
id|cpuinfo_parisc
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n;**  &t;PARISC CPU driver - claim &quot;device&quot; and initialize CPU data structures.&n;**&n;** Consolidate per CPU initialization into (mostly) one module.&n;** Monarch CPU will initialize boot_cpu_data which shouldn&squot;t&n;** change once the system has booted.&n;**&n;** The callback *should* do per-instance initialization of&n;** everything including the monarch. &quot;Per CPU&quot; init code in&n;** setup.c:start_parisc() has migrated here and start_parisc()&n;** will call register_parisc_driver(&amp;cpu_driver) before calling do_inventory().&n;**&n;** The goal of consolidating CPU initialization into one place is&n;** to make sure all CPU&squot;s get initialized the same way.&n;** The code path not shared is how PDC hands control of the CPU to the OS.&n;** The initialization of OS data structures is the same (done below).&n;*/
multiline_comment|/**&n; * processor_probe - Determine if processor driver should claim this device.&n; * @dev: The device which has been found.&n; *&n; * Determine if processor driver should claim this chip (return 0) or not &n; * (return 1).  If so, initialize the chip and tell other partners in crime &n; * they have work to do.&n; */
DECL|function|processor_probe
r_static
r_int
id|__init
id|processor_probe
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|txn_addr
suffix:semicolon
r_int
r_int
id|cpuid
suffix:semicolon
r_struct
id|cpuinfo_parisc
op_star
id|p
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|boot_cpu_data.cpu_count
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CONFIG_SMP=n  ignoring additional CPUs&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* logical CPU ID and update global counter&n;&t; * May get overwritten by PAT code.&n;&t; */
id|cpuid
op_assign
id|boot_cpu_data.cpu_count
suffix:semicolon
id|txn_addr
op_assign
id|dev-&gt;hpa
suffix:semicolon
multiline_comment|/* for legacy PDC */
macro_line|#ifdef __LP64__
r_if
c_cond
(paren
id|is_pdc_pat
c_func
(paren
)paren
)paren
(brace
id|ulong
id|status
suffix:semicolon
r_int
r_int
id|bytecnt
suffix:semicolon
id|pdc_pat_cell_mod_maddr_block_t
id|pa_pdc_cell
suffix:semicolon
DECL|macro|USE_PAT_CPUID
macro_line|#undef USE_PAT_CPUID
macro_line|#ifdef USE_PAT_CPUID
r_struct
id|pdc_pat_cpu_num
id|cpu_info
suffix:semicolon
macro_line|#endif
id|status
op_assign
id|pdc_pat_cell_module
c_func
(paren
op_amp
id|bytecnt
comma
id|dev-&gt;pcell_loc
comma
id|dev-&gt;mod_index
comma
id|PA_VIEW
comma
op_amp
id|pa_pdc_cell
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|PDC_OK
op_eq
id|status
)paren
suffix:semicolon
multiline_comment|/* verify it&squot;s the same as what do_pat_inventory() found */
id|ASSERT
c_func
(paren
id|dev-&gt;mod_info
op_eq
id|pa_pdc_cell.mod_info
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|dev-&gt;pmod_loc
op_eq
id|pa_pdc_cell.mod_location
)paren
suffix:semicolon
id|txn_addr
op_assign
id|pa_pdc_cell.mod
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* id_eid for IO sapic */
macro_line|#ifdef USE_PAT_CPUID
multiline_comment|/* We need contiguous numbers for cpuid. Firmware&squot;s notion&n; * of cpuid is for physical CPUs and we just don&squot;t care yet.&n; * We&squot;ll care when we need to query PAT PDC about a CPU *after*&n; * boot time (ie shutdown a CPU from an OS perspective).&n; */
multiline_comment|/* get the cpu number */
id|status
op_assign
id|pdc_pat_cpu_get_number
c_func
(paren
op_amp
id|cpu_info
comma
id|dev-&gt;hpa
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|PDC_OK
op_eq
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_info.cpu_num
op_ge
id|NR_CPUS
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;IGNORING CPU at 0x%x,&quot;
l_string|&quot; cpu_slot_id &gt; NR_CPUS&quot;
l_string|&quot; (%ld &gt; %d)&bslash;n&quot;
comma
id|dev-&gt;hpa
comma
id|cpu_info.cpu_num
comma
id|NR_CPUS
)paren
suffix:semicolon
multiline_comment|/* Ignore CPU since it will only crash */
id|boot_cpu_data.cpu_count
op_decrement
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|cpuid
op_assign
id|cpu_info.cpu_num
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#endif
id|p
op_assign
op_amp
id|cpu_data
(braket
id|cpuid
)braket
suffix:semicolon
id|boot_cpu_data.cpu_count
op_increment
suffix:semicolon
multiline_comment|/* initialize counters */
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cpuinfo_parisc
)paren
)paren
suffix:semicolon
id|p-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* Save IODC data in case we need it */
id|p-&gt;hpa
op_assign
id|dev-&gt;hpa
suffix:semicolon
multiline_comment|/* save CPU hpa */
id|p-&gt;cpuid
op_assign
id|cpuid
suffix:semicolon
multiline_comment|/* save CPU id */
id|p-&gt;txn_addr
op_assign
id|txn_addr
suffix:semicolon
multiline_comment|/* save CPU IRQ address */
macro_line|#ifdef CONFIG_SMP
id|p-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n;&t;** FIXME: review if any other initialization is clobbered&n;&t;**&t;for boot_cpu by the above memset().&n;&t;*/
multiline_comment|/* stolen from init_percpu_prof() */
id|cpu_data
(braket
id|cpuid
)braket
dot
id|prof_counter
op_assign
l_int|1
suffix:semicolon
id|cpu_data
(braket
id|cpuid
)braket
dot
id|prof_multiplier
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;** CONFIG_SMP: init_smp_config() will attempt to get CPU&squot;s into&n;&t;** OS control. RENDEZVOUS is the default state - see mem_set above.&n;&t;**&t;p-&gt;state = STATE_RENDEZVOUS;&n;&t;*/
macro_line|#if 0
multiline_comment|/* CPU 0 IRQ table is statically allocated/initialized */
r_if
c_cond
(paren
id|cpuid
)paren
(brace
r_struct
id|irqaction
id|actions
(braket
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t;** itimer and ipi IRQ handlers are statically initialized in&n;&t;&t;** arch/parisc/kernel/irq.c. ie Don&squot;t need to register them.&n;&t;&t;*/
id|actions
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irqaction
)paren
op_star
id|MAX_CPU_IRQ
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|actions
)paren
(brace
multiline_comment|/* not getting it&squot;s own table, share with monarch */
id|actions
op_assign
id|cpu_irq_actions
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|cpu_irq_actions
(braket
id|cpuid
)braket
op_assign
id|actions
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * collect_boot_cpu_data - Fill the boot_cpu_data structure.&n; *&n; * This function collects and stores the generic processor information&n; * in the boot_cpu_data structure.&n; */
DECL|function|collect_boot_cpu_data
r_void
id|__init
id|collect_boot_cpu_data
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
op_amp
id|boot_cpu_data
comma
l_int|0
comma
r_sizeof
(paren
id|boot_cpu_data
)paren
)paren
suffix:semicolon
id|boot_cpu_data.cpu_hz
op_assign
l_int|100
op_star
id|PAGE0-&gt;mem_10msec
suffix:semicolon
multiline_comment|/* Hz of this PARISC */
multiline_comment|/* get CPU-Model Information... */
DECL|macro|p
mdefine_line|#define p ((unsigned long *)&amp;boot_cpu_data.pdc.model)
r_if
c_cond
(paren
id|pdc_model_info
c_func
(paren
op_amp
id|boot_cpu_data.pdc.model
)paren
op_eq
id|PDC_OK
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;model %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
id|p
(braket
l_int|0
)braket
comma
id|p
(braket
l_int|1
)braket
comma
id|p
(braket
l_int|2
)braket
comma
id|p
(braket
l_int|3
)braket
comma
id|p
(braket
l_int|4
)braket
comma
id|p
(braket
l_int|5
)braket
comma
id|p
(braket
l_int|6
)braket
comma
id|p
(braket
l_int|7
)braket
comma
id|p
(braket
l_int|8
)braket
)paren
suffix:semicolon
DECL|macro|p
macro_line|#undef p
r_if
c_cond
(paren
id|pdc_model_versions
c_func
(paren
op_amp
id|boot_cpu_data.pdc.versions
comma
l_int|0
)paren
op_eq
id|PDC_OK
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vers  %08lx&bslash;n&quot;
comma
id|boot_cpu_data.pdc.versions
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdc_model_cpuid
c_func
(paren
op_amp
id|boot_cpu_data.pdc.cpuid
)paren
op_eq
id|PDC_OK
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPUID vers %ld rev %ld (0x%08lx)&bslash;n&quot;
comma
(paren
id|boot_cpu_data.pdc.cpuid
op_rshift
l_int|5
)paren
op_amp
l_int|127
comma
id|boot_cpu_data.pdc.cpuid
op_amp
l_int|31
comma
id|boot_cpu_data.pdc.cpuid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdc_model_capabilities
c_func
(paren
op_amp
id|boot_cpu_data.pdc.capabilities
)paren
op_eq
id|PDC_OK
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;capabilities 0x%lx&bslash;n&quot;
comma
id|boot_cpu_data.pdc.capabilities
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdc_model_sysmodel
c_func
(paren
id|boot_cpu_data.pdc.sys_model_name
)paren
op_eq
id|PDC_OK
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;model %s&bslash;n&quot;
comma
id|boot_cpu_data.pdc.sys_model_name
)paren
suffix:semicolon
id|boot_cpu_data.hversion
op_assign
id|boot_cpu_data.pdc.model.hversion
suffix:semicolon
id|boot_cpu_data.sversion
op_assign
id|boot_cpu_data.pdc.model.sversion
suffix:semicolon
id|boot_cpu_data.cpu_type
op_assign
id|parisc_get_cpu_type
c_func
(paren
id|boot_cpu_data.hversion
)paren
suffix:semicolon
id|boot_cpu_data.cpu_name
op_assign
id|cpu_name_version
(braket
id|boot_cpu_data.cpu_type
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|boot_cpu_data.family_name
op_assign
id|cpu_name_version
(braket
id|boot_cpu_data.cpu_type
)braket
(braket
l_int|1
)braket
suffix:semicolon
)brace
multiline_comment|/**&n; * init_cpu_profiler - enable/setup per cpu profiling hooks.&n; * @cpunum: The processor instance.&n; *&n; * FIXME: doesn&squot;t do much yet...&n; */
r_static
r_inline
r_void
id|__init
DECL|function|init_percpu_prof
id|init_percpu_prof
c_func
(paren
r_int
id|cpunum
)paren
(brace
id|cpu_data
(braket
id|cpunum
)braket
dot
id|prof_counter
op_assign
l_int|1
suffix:semicolon
id|cpu_data
(braket
id|cpunum
)braket
dot
id|prof_multiplier
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * init_per_cpu - Handle individual processor initializations.&n; * @cpunum: logical processor number.&n; *&n; * This function handles initialization for *every* CPU&n; * in the system:&n; *&n; * o Set &quot;default&quot; CPU width for trap handlers&n; *&n; * o Enable FP coprocessor&n; *   REVISIT: this could be done in the &quot;code 22&quot; trap handler.&n; *&t;(frowands idea - that way we know which processes need FP&n; *&t;registers saved on the interrupt stack.)&n; *   NEWS FLASH: wide kernels need FP coprocessor enabled to handle&n; *&t;formatted printing of %lx for example (double divides I think)&n; *&n; * o Enable CPU profiling hooks.&n; */
DECL|function|init_per_cpu
r_int
id|__init
id|init_per_cpu
c_func
(paren
r_int
id|cpunum
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|pdc_coproc_cfg
id|coproc_cfg
suffix:semicolon
id|ret
op_assign
id|pdc_coproc_cfg
c_func
(paren
op_amp
id|coproc_cfg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
op_logical_and
id|coproc_cfg.ccr_functional
)paren
(brace
id|mtctl
c_func
(paren
id|coproc_cfg.ccr_functional
comma
l_int|10
)paren
suffix:semicolon
multiline_comment|/* 10 == Coprocessor Control Reg */
multiline_comment|/* FWIW, FP rev/model is a more accurate way to determine&n;&t;&t;** CPU type. CPU rev/model has some ambiguous cases.&n;&t;&t;*/
id|cpu_data
(braket
id|cpunum
)braket
dot
id|fp_rev
op_assign
id|coproc_cfg.revision
suffix:semicolon
id|cpu_data
(braket
id|cpunum
)braket
dot
id|fp_model
op_assign
id|coproc_cfg.model
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;FP[%d] enabled: Rev %ld Model %ld&bslash;n&quot;
comma
id|cpunum
comma
id|coproc_cfg.revision
comma
id|coproc_cfg.model
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;** store status register to stack (hopefully aligned)&n;&t;&t;** and clear the T-bit.&n;&t;&t;*/
id|asm
r_volatile
(paren
l_string|&quot;fstd    %fr0,8(%sp)&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;WARNING: No FP CoProcessor?!&quot;
l_string|&quot; (coproc_cfg.ccr_functional == 0x%lx, expected 0xc0)&bslash;n&quot;
macro_line|#ifdef __LP64__
l_string|&quot;Halting Machine - FP required&bslash;n&quot;
macro_line|#endif
comma
id|coproc_cfg.ccr_functional
)paren
suffix:semicolon
macro_line|#ifdef __LP64__
id|mdelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* previous chars get pushed to console */
id|panic
c_func
(paren
l_string|&quot;FP CoProc not reported&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* FUTURE: Enable Performance Monitor : ccr bit 0x20 */
id|init_percpu_prof
c_func
(paren
id|cpunum
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Display cpu info for all cpu&squot;s.&n; */
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
r_int
id|n
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|boot_cpu_data.cpu_count
suffix:semicolon
id|n
op_increment
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
l_int|0
op_eq
id|cpu_data
(braket
id|n
)braket
dot
id|hpa
)paren
r_continue
suffix:semicolon
macro_line|#ifdef ENTRY_SYS_CPUS
macro_line|#error iCOD support wants to show CPU state here
macro_line|#endif
macro_line|#endif
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;processor&bslash;t: %d&bslash;n&quot;
l_string|&quot;cpu family&bslash;t: PA-RISC %s&bslash;n&quot;
comma
id|n
comma
id|boot_cpu_data.family_name
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu&bslash;t&bslash;t: %s&bslash;n&quot;
comma
id|boot_cpu_data.cpu_name
)paren
suffix:semicolon
multiline_comment|/* cpu MHz */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu MHz&bslash;t&bslash;t: %d.%06d&bslash;n&quot;
comma
id|boot_cpu_data.cpu_hz
op_div
l_int|1000000
comma
id|boot_cpu_data.cpu_hz
op_mod
l_int|1000000
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;model&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;model name&bslash;t: %s&bslash;n&quot;
comma
id|boot_cpu_data.pdc.sys_model_name
comma
id|cpu_data
(braket
id|n
)braket
dot
id|dev
ques
c_cond
id|cpu_data
(braket
id|n
)braket
dot
id|dev-&gt;name
suffix:colon
l_string|&quot;Unknown&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;hversion&bslash;t: 0x%08x&bslash;n&quot;
l_string|&quot;sversion&bslash;t: 0x%08x&bslash;n&quot;
comma
id|boot_cpu_data.hversion
comma
id|boot_cpu_data.sversion
)paren
suffix:semicolon
multiline_comment|/* print cachesize info */
id|show_cache_info
c_func
(paren
id|m
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;bogomips&bslash;t: %lu.%02lu&bslash;n&quot;
comma
id|loops_per_jiffy
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|loops_per_jiffy
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
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;software id&bslash;t: %ld&bslash;n&bslash;n&quot;
comma
id|boot_cpu_data.pdc.model.sw_id
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|processor_tbl
r_static
r_struct
id|parisc_device_id
id|processor_tbl
(braket
)braket
op_assign
(brace
(brace
id|HPHW_NPROC
comma
id|HVERSION_REV_ANY_ID
comma
id|HVERSION_ANY_ID
comma
id|SVERSION_ANY_ID
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|cpu_driver
r_static
r_struct
id|parisc_driver
id|cpu_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;CPU&quot;
comma
dot
id|id_table
op_assign
id|processor_tbl
comma
dot
id|probe
op_assign
id|processor_probe
)brace
suffix:semicolon
multiline_comment|/**&n; * processor_init - Processor initalization procedure.&n; *&n; * Register this driver.&n; */
DECL|function|processor_init
r_void
id|__init
id|processor_init
c_func
(paren
r_void
)paren
(brace
id|register_parisc_driver
c_func
(paren
op_amp
id|cpu_driver
)paren
suffix:semicolon
)brace
eof
