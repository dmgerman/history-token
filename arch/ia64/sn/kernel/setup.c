multiline_comment|/*&n; * Copyright (C) 1999,2001-2003 Silicon Graphics, Inc. All rights reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/simulator.h&gt;
macro_line|#include &lt;asm/sn/leds.h&gt;
macro_line|#include &lt;asm/sn/bte.h&gt;
macro_line|#include &lt;asm/sn/clksupport.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub.h&gt;
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|pda_s
comma
id|pda_percpu
)paren
suffix:semicolon
DECL|macro|pxm_to_nasid
mdefine_line|#define pxm_to_nasid(pxm) ((pxm)&lt;&lt;1)
DECL|macro|MAX_PHYS_MEMORY
mdefine_line|#define MAX_PHYS_MEMORY&t;&t;(1UL &lt;&lt; 49)     /* 1 TB */
r_extern
r_void
id|bte_init_node
(paren
id|nodepda_t
op_star
comma
id|cnodeid_t
)paren
suffix:semicolon
r_extern
r_void
id|bte_init_cpu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sn_timer_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|last_time_offset
suffix:semicolon
r_extern
r_void
(paren
op_star
id|ia64_mark_idle
)paren
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|snidle
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|variable|sn_rtc_cycles_per_second
r_int
r_int
id|sn_rtc_cycles_per_second
suffix:semicolon
DECL|variable|sn_partid
id|partid_t
id|sn_partid
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|sn_system_serial_number_string
r_char
id|sn_system_serial_number_string
(braket
l_int|128
)braket
suffix:semicolon
DECL|variable|sn_partition_serial_number
id|u64
id|sn_partition_serial_number
suffix:semicolon
DECL|variable|physical_node_map
r_int
id|physical_node_map
(braket
id|MAX_PHYSNODE_ID
)braket
suffix:semicolon
multiline_comment|/*&n; * This is the address of the RRegs in the HSpace of the global&n; * master.  It is used by a hack in serial.c (serial_[in|out],&n; * printk.c (early_printk), and kdb_io.c to put console output on that&n; * node&squot;s Bedrock UART.  It is initialized here to 0, so that&n; * early_printk won&squot;t try to access the UART before&n; * master_node_bedrock_address is properly calculated.&n; */
DECL|variable|master_node_bedrock_address
id|u64
id|master_node_bedrock_address
suffix:semicolon
r_static
r_void
id|sn_init_pdas
c_func
(paren
r_char
op_star
op_star
)paren
suffix:semicolon
DECL|variable|nodepdaindr
r_static
id|nodepda_t
op_star
id|nodepdaindr
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|variable|irqpdaindr
id|irqpda_t
op_star
id|irqpdaindr
suffix:semicolon
multiline_comment|/*&n; * The format of &quot;screen_info&quot; is strange, and due to early i386-setup&n; * code. This is just enough to make the console code think we&squot;re on a&n; * VGA color display.&n; */
DECL|variable|sn_screen_info
r_struct
id|screen_info
id|sn_screen_info
op_assign
(brace
id|orig_x
suffix:colon
l_int|0
comma
id|orig_y
suffix:colon
l_int|0
comma
id|orig_video_mode
suffix:colon
l_int|3
comma
id|orig_video_cols
suffix:colon
l_int|80
comma
id|orig_video_ega_bx
suffix:colon
l_int|3
comma
id|orig_video_lines
suffix:colon
l_int|25
comma
id|orig_video_isVGA
suffix:colon
l_int|1
comma
id|orig_video_points
suffix:colon
l_int|16
)brace
suffix:semicolon
multiline_comment|/*&n; * This is here so we can use the CMOS detection in ide-probe.c to&n; * determine what drives are present.  In theory, we don&squot;t need this&n; * as the auto-detection could be done via ide-probe.c:do_probe() but&n; * in practice that would be much slower, which is painful when&n; * running in the simulator.  Note that passing zeroes in DRIVE_INFO&n; * is sufficient (the IDE driver will autodetect the drive geometry).&n; */
macro_line|#ifdef CONFIG_IA64_GENERIC
r_extern
r_char
id|drive_info
(braket
l_int|4
op_star
l_int|16
)braket
suffix:semicolon
macro_line|#else
DECL|variable|drive_info
r_char
id|drive_info
(braket
l_int|4
op_star
l_int|16
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/**&n; * early_sn_setup - early setup routine for SN platforms&n; *&n; * Sets up an initial console to aid debugging.  Intended primarily&n; * for bringup.  See start_kernel() in init/main.c.&n; */
macro_line|#if defined(CONFIG_IA64_EARLY_PRINTK_SGI_SN) || defined(CONFIG_IA64_SGI_SN_SIM)
r_void
id|__init
DECL|function|early_sn_setup
id|early_sn_setup
c_func
(paren
r_void
)paren
(brace
r_void
id|ia64_sal_handler_init
(paren
r_void
op_star
id|entry_point
comma
r_void
op_star
id|gpval
)paren
suffix:semicolon
id|efi_system_table_t
op_star
id|efi_systab
suffix:semicolon
id|efi_config_table_t
op_star
id|config_tables
suffix:semicolon
r_struct
id|ia64_sal_systab
op_star
id|sal_systab
suffix:semicolon
r_struct
id|ia64_sal_desc_entry_point
op_star
id|ep
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Parse enough of the SAL tables to locate the SAL entry point. Since, console&n;&t; * IO on SN2 is done via SAL calls, early_printk won&squot;t work without this.&n;&t; *&n;&t; * This code duplicates some of the ACPI table parsing that is in efi.c &amp; sal.c.&n;&t; * Any changes to those file may have to be made hereas well.&n;&t; */
id|efi_systab
op_assign
(paren
id|efi_system_table_t
op_star
)paren
id|__va
c_func
(paren
id|ia64_boot_param-&gt;efi_systab
)paren
suffix:semicolon
id|config_tables
op_assign
id|__va
c_func
(paren
id|efi_systab-&gt;tables
)paren
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
id|efi_systab-&gt;nr_tables
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|efi_guidcmp
c_func
(paren
id|config_tables
(braket
id|i
)braket
dot
id|guid
comma
id|SAL_SYSTEM_TABLE_GUID
)paren
op_eq
l_int|0
)paren
(brace
id|sal_systab
op_assign
id|__va
c_func
(paren
id|config_tables
(braket
id|i
)braket
dot
id|table
)paren
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
id|sal_systab
op_plus
l_int|1
)paren
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
id|sal_systab-&gt;entry_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
id|SAL_DESC_ENTRY_POINT
)paren
(brace
id|ep
op_assign
(paren
r_struct
id|ia64_sal_desc_entry_point
op_star
)paren
id|p
suffix:semicolon
id|ia64_sal_handler_init
c_func
(paren
id|__va
c_func
(paren
id|ep-&gt;sal_proc
)paren
comma
id|__va
c_func
(paren
id|ep-&gt;gp
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|p
op_add_assign
id|SAL_DESC_SIZE
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
(brace
id|master_node_bedrock_address
op_assign
(paren
id|u64
)paren
id|REMOTE_HUB
c_func
(paren
id|get_nasid
c_func
(paren
)paren
comma
id|SH_JUNK_BUS_UART0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;early_sn_setup: setting master_node_bedrock_address to 0x%lx&bslash;n&quot;
comma
id|master_node_bedrock_address
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_IA64_EARLY_PRINTK_SGI_SN */
macro_line|#ifdef CONFIG_IA64_MCA
r_extern
r_int
id|platform_intr_list
(braket
)braket
suffix:semicolon
macro_line|#endif
r_extern
id|nasid_t
id|master_nasid
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|shub_1_1_found
id|__initdata
suffix:semicolon
multiline_comment|/*&n; * sn_check_for_wars&n; *&n; * Set flag for enabling shub specific wars&n; */
r_static
r_inline
r_int
id|__init
DECL|function|is_shub_1_1
id|is_shub_1_1
c_func
(paren
r_int
id|nasid
)paren
(brace
r_int
r_int
id|id
suffix:semicolon
r_int
id|rev
suffix:semicolon
id|id
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|SH_SHUB_ID
)paren
suffix:semicolon
id|rev
op_assign
(paren
id|id
op_amp
id|SH_SHUB_ID_REVISION_MASK
)paren
op_rshift
id|SH_SHUB_ID_REVISION_SHFT
suffix:semicolon
r_return
id|rev
op_le
l_int|2
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|sn_check_for_wars
id|sn_check_for_wars
c_func
(paren
r_void
)paren
(brace
r_int
id|cnode
suffix:semicolon
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
r_if
c_cond
(paren
id|is_shub_1_1
c_func
(paren
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
)paren
)paren
id|shub_1_1_found
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * sn_setup - SN platform setup routine&n; * @cmdline_p: kernel command line&n; *&n; * Handles platform setup for SN machines.  This includes determining&n; * the RTC frequency (via a SAL call), initializing secondary CPUs, and&n; * setting up per-node data areas.  The console is also initialized here.&n; */
r_void
id|__init
DECL|function|sn_setup
id|sn_setup
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_int
id|status
comma
id|ticks_per_sec
comma
id|drift
suffix:semicolon
r_int
id|pxm
suffix:semicolon
r_int
id|major
op_assign
id|sn_sal_rev_major
c_func
(paren
)paren
comma
id|minor
op_assign
id|sn_sal_rev_minor
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|io_sh_swapper
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
id|nasid_t
id|get_master_baseio_nasid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sn_cpu_init
c_func
(paren
r_void
)paren
suffix:semicolon
id|MAX_DMA_ADDRESS
op_assign
id|PAGE_OFFSET
op_plus
id|MAX_PHYS_MEMORY
suffix:semicolon
id|memset
c_func
(paren
id|physical_node_map
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|physical_node_map
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pxm
op_assign
l_int|0
suffix:semicolon
id|pxm
OL
id|MAX_PXM_DOMAINS
suffix:semicolon
id|pxm
op_increment
)paren
r_if
c_cond
(paren
id|pxm_to_nid_map
(braket
id|pxm
)braket
op_ne
op_minus
l_int|1
)paren
id|physical_node_map
(braket
id|pxm_to_nasid
c_func
(paren
id|pxm
)paren
)braket
op_assign
id|pxm_to_nid_map
(braket
id|pxm
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SGI SAL version %x.%02x&bslash;n&quot;
comma
id|major
comma
id|minor
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Confirm the SAL we&squot;re running on is recent enough...&n;&t; */
r_if
c_cond
(paren
(paren
id|major
OL
id|SN_SAL_MIN_MAJOR
)paren
op_logical_or
(paren
id|major
op_eq
id|SN_SAL_MIN_MAJOR
op_logical_and
id|minor
OL
id|SN_SAL_MIN_MINOR
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;This kernel needs SGI SAL version &gt;= &quot;
l_string|&quot;%x.%02x&bslash;n&quot;
comma
id|SN_SAL_MIN_MAJOR
comma
id|SN_SAL_MIN_MINOR
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;PROM version too old&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|io_sh_swapper
c_func
(paren
id|get_nasid
c_func
(paren
)paren
comma
l_int|0
)paren
suffix:semicolon
id|master_nasid
op_assign
id|get_nasid
c_func
(paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|get_console_nasid
c_func
(paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|get_master_baseio_nasid
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
id|ia64_sal_freq_base
c_func
(paren
id|SAL_FREQ_BASE_REALTIME_CLOCK
comma
op_amp
id|ticks_per_sec
comma
op_amp
id|drift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
op_logical_or
id|ticks_per_sec
OL
l_int|100000
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;unable to determine platform RTC clock frequency, guessing.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* PROM gives wrong value for clock freq. so guess */
id|sn_rtc_cycles_per_second
op_assign
l_int|1000000000000UL
op_div
l_int|30000UL
suffix:semicolon
)brace
r_else
id|sn_rtc_cycles_per_second
op_assign
id|ticks_per_sec
suffix:semicolon
id|platform_intr_list
(braket
id|ACPI_INTERRUPT_CPEI
)braket
op_assign
id|IA64_PCE_VECTOR
suffix:semicolon
r_if
c_cond
(paren
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
(brace
id|master_node_bedrock_address
op_assign
(paren
id|u64
)paren
id|REMOTE_HUB
c_func
(paren
id|get_nasid
c_func
(paren
)paren
comma
id|SH_JUNK_BUS_UART0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;sn_setup: setting master_node_bedrock_address to 0x%lx&bslash;n&quot;
comma
id|master_node_bedrock_address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * we set the default root device to /dev/hda&n;&t; * to make simulation easy&n;&t; */
id|ROOT_DEV
op_assign
id|Root_HDA1
suffix:semicolon
multiline_comment|/*&n;&t; * Create the PDAs and NODEPDAs for all the cpus.&n;&t; */
id|sn_init_pdas
c_func
(paren
id|cmdline_p
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check for WARs.&n;&t; */
id|sn_check_for_wars
c_func
(paren
)paren
suffix:semicolon
id|ia64_mark_idle
op_assign
op_amp
id|snidle
suffix:semicolon
multiline_comment|/* &n;&t; * For the bootcpu, we do this here. All other cpus will make the&n;&t; * call as part of cpu_init in slave cpu initialization.&n;&t; */
id|sn_cpu_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|init_smp_config
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|screen_info
op_assign
id|sn_screen_info
suffix:semicolon
id|sn_timer_init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sn_init_pdas - setup node data areas&n; *&n; * One time setup for Node Data Area.  Called by sn_setup().&n; */
r_void
DECL|function|sn_init_pdas
id|sn_init_pdas
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
id|cnodeid_t
id|cnode
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure that the PDA fits entirely in the same page as the &n;&t; * cpu_data area.&n;&t; */
r_if
c_cond
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|pda
op_amp
(paren
op_complement
id|PAGE_MASK
)paren
)paren
op_plus
r_sizeof
(paren
id|pda_t
)paren
)paren
OG
id|PAGE_SIZE
)paren
id|panic
c_func
(paren
l_string|&quot;overflow of cpu_data page&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pda-&gt;cnodeid_to_nasid_table
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|pda-&gt;cnodeid_to_nasid_table
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
id|pda-&gt;cnodeid_to_nasid_table
(braket
id|cnode
)braket
op_assign
id|pxm_to_nasid
c_func
(paren
id|nid_to_pxm_map
(braket
id|cnode
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;         * Allocate &amp; initalize the nodepda for each node.&n;         */
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
id|nodepdaindr
(braket
id|cnode
)braket
op_assign
id|alloc_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|cnode
)paren
comma
r_sizeof
(paren
id|nodepda_t
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|nodepdaindr
(braket
id|cnode
)braket
comma
l_int|0
comma
r_sizeof
(paren
id|nodepda_t
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now copy the array of nodepda pointers to each nodepda.&n;&t; */
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
id|memcpy
c_func
(paren
id|nodepdaindr
(braket
id|cnode
)braket
op_member_access_from_pointer
id|pernode_pdaindr
comma
id|nodepdaindr
comma
r_sizeof
(paren
id|nodepdaindr
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up IO related platform-dependent nodepda fields.&n;&t; * The following routine actually sets up the hubinfo struct&n;&t; * in nodepda.&n;&t; */
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
id|init_platform_nodepda
c_func
(paren
id|nodepdaindr
(braket
id|cnode
)braket
comma
id|cnode
)paren
suffix:semicolon
id|bte_init_node
(paren
id|nodepdaindr
(braket
id|cnode
)braket
comma
id|cnode
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * sn_cpu_init - initialize per-cpu data areas&n; * @cpuid: cpuid of the caller&n; *&n; * Called during cpu initialization on each cpu as it starts.&n; * Currently, initializes the per-cpu data area for SNIA.&n; * Also sets up a few fields in the nodepda.  Also known as&n; * platform_cpu_init() by the ia64 machvec code.&n; */
r_void
id|__init
DECL|function|sn_cpu_init
id|sn_cpu_init
c_func
(paren
r_void
)paren
(brace
r_int
id|cpuid
suffix:semicolon
r_int
id|cpuphyid
suffix:semicolon
r_int
id|nasid
suffix:semicolon
r_int
id|slice
suffix:semicolon
r_int
id|cnode
comma
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * The boot cpu makes this call again after platform initialization is&n;&t; * complete.&n;&t; */
r_if
c_cond
(paren
id|nodepdaindr
(braket
l_int|0
)braket
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|cpuid
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|cpuphyid
op_assign
(paren
(paren
id|ia64_get_lid
c_func
(paren
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|nasid
op_assign
id|cpu_physical_id_to_nasid
c_func
(paren
id|cpuphyid
)paren
suffix:semicolon
id|cnode
op_assign
id|nasid_to_cnodeid
c_func
(paren
id|nasid
)paren
suffix:semicolon
id|slice
op_assign
id|cpu_physical_id_to_slice
c_func
(paren
id|cpuphyid
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d: nasid %d, slice %d, cnode %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|nasid
comma
id|slice
comma
id|cnode
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pda
comma
l_int|0
comma
r_sizeof
(paren
id|pda
)paren
)paren
suffix:semicolon
id|pda-&gt;p_nodepda
op_assign
id|nodepdaindr
(braket
id|cnode
)braket
suffix:semicolon
id|pda-&gt;led_address
op_assign
(paren
id|typeof
c_func
(paren
id|pda-&gt;led_address
)paren
)paren
(paren
id|LED0
op_plus
(paren
id|slice
op_lshift
id|LED_CPU_SHIFT
)paren
)paren
suffix:semicolon
id|pda-&gt;led_state
op_assign
id|LED_ALWAYS_SET
suffix:semicolon
id|pda-&gt;hb_count
op_assign
id|HZ
op_div
l_int|2
suffix:semicolon
id|pda-&gt;hb_state
op_assign
l_int|0
suffix:semicolon
id|pda-&gt;idle_flag
op_assign
l_int|0
suffix:semicolon
id|pda-&gt;shub_1_1_found
op_assign
id|shub_1_1_found
suffix:semicolon
id|memset
c_func
(paren
id|pda-&gt;cnodeid_to_nasid_table
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|pda-&gt;cnodeid_to_nasid_table
)paren
)paren
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
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
id|pda-&gt;cnodeid_to_nasid_table
(braket
id|i
)braket
op_assign
id|pxm_to_nasid
c_func
(paren
id|nid_to_pxm_map
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|local_node_data-&gt;active_cpu_count
op_eq
l_int|1
)paren
id|nodepda-&gt;node_first_cpu
op_assign
id|cpuid
suffix:semicolon
multiline_comment|/*&n;&t; * We must use different memory allocators for first cpu (bootmem &n;&t; * allocator) than for the other cpus (regular allocator).&n;&t; */
r_if
c_cond
(paren
id|cpuid
op_eq
l_int|0
)paren
id|irqpdaindr
op_assign
id|alloc_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|cpuid_to_cnodeid
c_func
(paren
id|cpuid
)paren
)paren
comma
r_sizeof
(paren
id|irqpda_t
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|irqpdaindr
comma
l_int|0
comma
r_sizeof
(paren
id|irqpda_t
)paren
)paren
suffix:semicolon
id|irqpdaindr-&gt;irq_flags
(braket
id|SGI_PCIBR_ERROR
)braket
op_assign
id|SN2_IRQ_SHARED
suffix:semicolon
id|irqpdaindr-&gt;irq_flags
(braket
id|SGI_PCIBR_ERROR
)braket
op_or_assign
id|SN2_IRQ_RESERVED
suffix:semicolon
id|irqpdaindr-&gt;irq_flags
(braket
id|SGI_II_ERROR
)braket
op_assign
id|SN2_IRQ_SHARED
suffix:semicolon
id|irqpdaindr-&gt;irq_flags
(braket
id|SGI_II_ERROR
)braket
op_or_assign
id|SN2_IRQ_RESERVED
suffix:semicolon
id|pda-&gt;pio_write_status_addr
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
(paren
id|slice
OL
l_int|2
ques
c_cond
id|SH_PIO_WRITE_STATUS_0
suffix:colon
id|SH_PIO_WRITE_STATUS_1
)paren
)paren
suffix:semicolon
id|pda-&gt;mem_write_status_addr
op_assign
(paren
r_volatile
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
(paren
id|slice
OL
l_int|2
ques
c_cond
id|SH_MEMORY_WRITE_STATUS_0
suffix:colon
id|SH_MEMORY_WRITE_STATUS_1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nodepda-&gt;node_first_cpu
op_eq
id|cpuid
)paren
(brace
r_int
id|buddy_nasid
suffix:semicolon
id|buddy_nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|numa_node_id
c_func
(paren
)paren
op_eq
id|numnodes
op_minus
l_int|1
ques
c_cond
l_int|0
suffix:colon
id|numa_node_id
c_func
(paren
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|pda-&gt;pio_shub_war_cam_addr
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|GLOBAL_MMR_ADDR
c_func
(paren
id|nasid
comma
id|SH_PI_CAM_CONTROL
)paren
suffix:semicolon
)brace
id|bte_init_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
eof
