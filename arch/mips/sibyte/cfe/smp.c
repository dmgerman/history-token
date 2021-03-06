multiline_comment|/*&n; * Copyright (C) 2000, 2001, 2002, 2003 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &quot;cfe_api.h&quot;
macro_line|#include &quot;cfe_error.h&quot;
multiline_comment|/*&n; * Use CFE to find out how many CPUs are available, setting up&n; * phys_cpu_present_map and the logical/physical mappings.&n; * XXXKW will the boot CPU ever not be physical 0?&n; *&n; * Common setup before any secondaries are started&n; */
DECL|function|prom_prepare_cpus
r_void
id|__init
id|prom_prepare_cpus
c_func
(paren
r_int
r_int
id|max_cpus
)paren
(brace
r_int
id|i
comma
id|num
suffix:semicolon
id|cpus_clear
c_func
(paren
id|phys_cpu_present_map
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
l_int|0
comma
id|phys_cpu_present_map
)paren
suffix:semicolon
id|__cpu_number_map
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|__cpu_logical_map
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
comma
id|num
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cfe_cpu_stop
c_func
(paren
id|i
)paren
op_eq
l_int|0
)paren
(brace
id|cpu_set
c_func
(paren
id|i
comma
id|phys_cpu_present_map
)paren
suffix:semicolon
id|__cpu_number_map
(braket
id|i
)braket
op_assign
op_increment
id|num
suffix:semicolon
id|__cpu_logical_map
(braket
id|num
)braket
op_assign
id|i
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;Detected %i available secondary CPU(s)&bslash;n&quot;
comma
id|num
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Setup the PC, SP, and GP of a secondary processor and start it&n; * running!&n; */
DECL|function|prom_boot_secondary
r_void
id|prom_boot_secondary
c_func
(paren
r_int
id|cpu
comma
r_struct
id|task_struct
op_star
id|idle
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|cfe_cpu_start
c_func
(paren
id|cpu_logical_map
c_func
(paren
id|cpu
)paren
comma
op_amp
id|smp_bootstrap
comma
id|__KSTK_TOS
c_func
(paren
id|idle
)paren
comma
(paren
r_int
r_int
)paren
id|idle-&gt;thread_info
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;cfe_start_cpu(%i) returned %i&bslash;n&quot;
comma
id|cpu
comma
id|retval
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Code to run on secondary just after probing the CPU&n; */
DECL|function|prom_init_secondary
r_void
id|prom_init_secondary
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|sb1250_smp_init
c_func
(paren
r_void
)paren
suffix:semicolon
id|sb1250_smp_init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do any tidying up before marking online and running the idle&n; * loop&n; */
DECL|function|prom_smp_finish
r_void
id|prom_smp_finish
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|sb1250_smp_finish
c_func
(paren
r_void
)paren
suffix:semicolon
id|sb1250_smp_finish
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Final cleanup after all secondaries booted&n; */
DECL|function|prom_cpus_done
r_void
id|prom_cpus_done
c_func
(paren
r_void
)paren
(brace
)brace
eof
