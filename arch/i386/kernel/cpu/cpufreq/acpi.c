multiline_comment|/*&n; * acpi_processor_perf.c - ACPI Processor P-States Driver ($Revision: 71 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *  Copyright (C) 2002, 2003 Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;acpi/processor.h&gt;
DECL|macro|ACPI_PROCESSOR_COMPONENT
mdefine_line|#define ACPI_PROCESSOR_COMPONENT&t;0x01000000
DECL|macro|ACPI_PROCESSOR_CLASS
mdefine_line|#define ACPI_PROCESSOR_CLASS&t;&t;&quot;processor&quot;
DECL|macro|ACPI_PROCESSOR_DRIVER_NAME
mdefine_line|#define ACPI_PROCESSOR_DRIVER_NAME&t;&quot;ACPI Processor P-States Driver&quot;
DECL|macro|ACPI_PROCESSOR_DEVICE_NAME
mdefine_line|#define ACPI_PROCESSOR_DEVICE_NAME&t;&quot;Processor&quot;
DECL|macro|ACPI_PROCESSOR_FILE_PERFORMANCE
mdefine_line|#define ACPI_PROCESSOR_FILE_PERFORMANCE&t;&quot;performance&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_PROCESSOR_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;acpi_processor_perf&quot;
)paren
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Paul Diefenbaugh, Dominik Brodowski&quot;
)paren
suffix:semicolon
DECL|variable|ACPI_PROCESSOR_DRIVER_NAME
id|MODULE_DESCRIPTION
c_func
(paren
id|ACPI_PROCESSOR_DRIVER_NAME
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Performance Management */
DECL|variable|performance
r_static
r_struct
id|acpi_processor_performance
op_star
id|performance
suffix:semicolon
DECL|variable|acpi_cpufreq_driver
r_static
r_struct
id|cpufreq_driver
id|acpi_cpufreq_driver
suffix:semicolon
r_static
r_int
id|acpi_processor_perf_open_fs
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
DECL|variable|acpi_processor_perf_fops
r_static
r_struct
id|file_operations
id|acpi_processor_perf_fops
op_assign
(brace
dot
id|open
op_assign
id|acpi_processor_perf_open_fs
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|single_release
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|acpi_processor_get_performance_control
id|acpi_processor_get_performance_control
(paren
r_struct
id|acpi_processor
op_star
id|pr
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
op_assign
(brace
id|ACPI_ALLOCATE_BUFFER
comma
l_int|NULL
)brace
suffix:semicolon
r_union
id|acpi_object
op_star
id|pct
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_object
id|obj
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_struct
id|acpi_pct_register
op_star
id|reg
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_processor_get_performance_control&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|pr-&gt;handle
comma
l_string|&quot;_PCT&quot;
comma
l_int|NULL
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Error evaluating _PCT&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|pct
op_assign
(paren
r_union
id|acpi_object
op_star
)paren
id|buffer.pointer
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pct
op_logical_or
(paren
id|pct-&gt;type
op_ne
id|ACPI_TYPE_PACKAGE
)paren
op_logical_or
(paren
id|pct-&gt;package.count
op_ne
l_int|2
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid _PCT data&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * control_register&n;&t; */
id|obj
op_assign
id|pct-&gt;package.elements
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|obj.type
op_ne
id|ACPI_TYPE_BUFFER
)paren
op_logical_or
(paren
id|obj.buffer.length
OL
r_sizeof
(paren
r_struct
id|acpi_pct_register
)paren
)paren
op_logical_or
(paren
id|obj.buffer.pointer
op_eq
l_int|NULL
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid _PCT data (control_register)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|reg
op_assign
(paren
r_struct
id|acpi_pct_register
op_star
)paren
(paren
id|obj.buffer.pointer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg-&gt;space_id
op_ne
id|ACPI_ADR_SPACE_SYSTEM_IO
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unsupported address space [%d] (control_register)&bslash;n&quot;
comma
(paren
id|u32
)paren
id|reg-&gt;space_id
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|pr-&gt;performance-&gt;control_register
op_assign
(paren
id|u16
)paren
id|reg-&gt;address
suffix:semicolon
multiline_comment|/*&n;&t; * status_register&n;&t; */
id|obj
op_assign
id|pct-&gt;package.elements
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|obj.type
op_ne
id|ACPI_TYPE_BUFFER
)paren
op_logical_or
(paren
id|obj.buffer.length
OL
r_sizeof
(paren
r_struct
id|acpi_pct_register
)paren
)paren
op_logical_or
(paren
id|obj.buffer.pointer
op_eq
l_int|NULL
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid _PCT data (status_register)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|reg
op_assign
(paren
r_struct
id|acpi_pct_register
op_star
)paren
(paren
id|obj.buffer.pointer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg-&gt;space_id
op_ne
id|ACPI_ADR_SPACE_SYSTEM_IO
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unsupported address space [%d] (status_register)&bslash;n&quot;
comma
(paren
id|u32
)paren
id|reg-&gt;space_id
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|pr-&gt;performance-&gt;status_register
op_assign
(paren
id|u16
)paren
id|reg-&gt;address
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;control_register[0x%04x] status_register[0x%04x]&bslash;n&quot;
comma
id|pr-&gt;performance-&gt;control_register
comma
id|pr-&gt;performance-&gt;status_register
)paren
)paren
suffix:semicolon
id|end
suffix:colon
id|acpi_os_free
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_processor_get_performance_states
id|acpi_processor_get_performance_states
(paren
r_struct
id|acpi_processor
op_star
id|pr
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
op_assign
(brace
id|ACPI_ALLOCATE_BUFFER
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|acpi_buffer
id|format
op_assign
(brace
r_sizeof
(paren
l_string|&quot;NNNNNN&quot;
)paren
comma
l_string|&quot;NNNNNN&quot;
)brace
suffix:semicolon
r_struct
id|acpi_buffer
id|state
op_assign
(brace
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
r_union
id|acpi_object
op_star
id|pss
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_processor_get_performance_states&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|pr-&gt;handle
comma
l_string|&quot;_PSS&quot;
comma
l_int|NULL
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Error evaluating _PSS&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|pss
op_assign
(paren
r_union
id|acpi_object
op_star
)paren
id|buffer.pointer
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss
op_logical_or
(paren
id|pss-&gt;type
op_ne
id|ACPI_TYPE_PACKAGE
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid _PSS data&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Found %d performance states&bslash;n&quot;
comma
id|pss-&gt;package.count
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pss-&gt;package.count
OG
id|ACPI_PROCESSOR_MAX_PERFORMANCE
)paren
(brace
id|pr-&gt;performance-&gt;state_count
op_assign
id|ACPI_PROCESSOR_MAX_PERFORMANCE
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Limiting number of states to max (%d)&bslash;n&quot;
comma
id|ACPI_PROCESSOR_MAX_PERFORMANCE
)paren
)paren
suffix:semicolon
)brace
r_else
id|pr-&gt;performance-&gt;state_count
op_assign
id|pss-&gt;package.count
suffix:semicolon
r_if
c_cond
(paren
id|pr-&gt;performance-&gt;state_count
OG
l_int|1
)paren
id|pr-&gt;flags.performance
op_assign
l_int|1
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
id|pr-&gt;performance-&gt;state_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|acpi_processor_px
op_star
id|px
op_assign
op_amp
(paren
id|pr-&gt;performance-&gt;states
(braket
id|i
)braket
)paren
suffix:semicolon
id|state.length
op_assign
r_sizeof
(paren
r_struct
id|acpi_processor_px
)paren
suffix:semicolon
id|state.pointer
op_assign
id|px
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Extracting state %d&bslash;n&quot;
comma
id|i
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_extract_package
c_func
(paren
op_amp
(paren
id|pss-&gt;package.elements
(braket
id|i
)braket
)paren
comma
op_amp
id|format
comma
op_amp
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid _PSS data&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;State [%d]: core_frequency[%d] power[%d] transition_latency[%d] bus_master_latency[%d] control[0x%x] status[0x%x]&bslash;n&quot;
comma
id|i
comma
(paren
id|u32
)paren
id|px-&gt;core_frequency
comma
(paren
id|u32
)paren
id|px-&gt;power
comma
(paren
id|u32
)paren
id|px-&gt;transition_latency
comma
(paren
id|u32
)paren
id|px-&gt;bus_master_latency
comma
(paren
id|u32
)paren
id|px-&gt;control
comma
(paren
id|u32
)paren
id|px-&gt;status
)paren
)paren
suffix:semicolon
)brace
id|end
suffix:colon
id|acpi_os_free
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_processor_set_performance
id|acpi_processor_set_performance
(paren
r_struct
id|acpi_processor
op_star
id|pr
comma
r_int
id|state
)paren
(brace
id|u16
id|port
op_assign
l_int|0
suffix:semicolon
id|u8
id|value
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|cpufreq_freqs
id|cpufreq_freqs
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_processor_set_performance&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr-&gt;flags.performance
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_ge
id|pr-&gt;performance-&gt;state_count
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Invalid target state (P%d)&bslash;n&quot;
comma
id|state
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state
OL
id|pr-&gt;performance_platform_limit
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Platform limit (P%d) overrides target state (P%d)&bslash;n&quot;
comma
id|pr-&gt;performance-&gt;platform_limit
comma
id|state
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state
op_eq
id|pr-&gt;performance-&gt;state
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Already at target state (P%d)&bslash;n&quot;
comma
id|state
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Transitioning from P%d to P%d&bslash;n&quot;
comma
id|pr-&gt;performance-&gt;state
comma
id|state
)paren
)paren
suffix:semicolon
multiline_comment|/* cpufreq frequency struct */
id|cpufreq_freqs.cpu
op_assign
id|pr-&gt;id
suffix:semicolon
id|cpufreq_freqs.old
op_assign
id|pr-&gt;performance-&gt;states
(braket
id|pr-&gt;performance-&gt;state
)braket
dot
id|core_frequency
suffix:semicolon
id|cpufreq_freqs
dot
r_new
op_assign
id|pr-&gt;performance-&gt;states
(braket
id|state
)braket
dot
id|core_frequency
suffix:semicolon
multiline_comment|/* notify cpufreq */
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|cpufreq_freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * First we write the target state&squot;s &squot;control&squot; value to the&n;&t; * control_register.&n;&t; */
id|port
op_assign
id|pr-&gt;performance-&gt;control_register
suffix:semicolon
id|value
op_assign
(paren
id|u16
)paren
id|pr-&gt;performance-&gt;states
(braket
id|state
)braket
dot
id|control
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Writing 0x%02x to port 0x%04x&bslash;n&quot;
comma
id|value
comma
id|port
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|value
comma
id|port
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Then we read the &squot;status_register&squot; and compare the value with the&n;&t; * target state&squot;s &squot;status&squot; to make sure the transition was successful.&n;&t; * Note that we&squot;ll poll for up to 1ms (100 cycles of 10us) before&n;&t; * giving up.&n;&t; */
id|port
op_assign
id|pr-&gt;performance-&gt;status_register
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Looking for 0x%02x from port 0x%04x&bslash;n&quot;
comma
(paren
id|u8
)paren
id|pr-&gt;performance-&gt;states
(braket
id|state
)braket
dot
id|status
comma
id|port
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
l_int|100
suffix:semicolon
id|i
op_increment
)paren
(brace
id|value
op_assign
id|inb
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
(paren
id|u8
)paren
id|pr-&gt;performance-&gt;states
(braket
id|state
)braket
dot
id|status
)paren
r_break
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
multiline_comment|/* notify cpufreq */
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|cpufreq_freqs
comma
id|CPUFREQ_POSTCHANGE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_ne
id|pr-&gt;performance-&gt;states
(braket
id|state
)braket
dot
id|status
)paren
(brace
r_int
r_int
id|tmp
op_assign
id|cpufreq_freqs
dot
r_new
suffix:semicolon
id|cpufreq_freqs
dot
r_new
op_assign
id|cpufreq_freqs.old
suffix:semicolon
id|cpufreq_freqs.old
op_assign
id|tmp
suffix:semicolon
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|cpufreq_freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|cpufreq_freqs
comma
id|CPUFREQ_POSTCHANGE
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Transition failed&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Transition successful after %d microseconds&bslash;n&quot;
comma
id|i
op_star
l_int|10
)paren
)paren
suffix:semicolon
id|pr-&gt;performance-&gt;state
op_assign
id|state
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|acpi_processor_perf_seq_show
r_static
r_int
id|acpi_processor_perf_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|offset
)paren
(brace
r_struct
id|acpi_processor
op_star
id|pr
op_assign
(paren
r_struct
id|acpi_processor
op_star
)paren
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_processor_perf_seq_show&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr-&gt;flags.performance
)paren
(brace
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&lt;not supported&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;state count:             %d&bslash;n&quot;
l_string|&quot;active state:            P%d&bslash;n&quot;
comma
id|pr-&gt;performance-&gt;state_count
comma
id|pr-&gt;performance-&gt;state
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;states:&bslash;n&quot;
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
id|pr-&gt;performance-&gt;state_count
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;   %cP%d:                  %d MHz, %d mW, %d uS&bslash;n&quot;
comma
(paren
id|i
op_eq
id|pr-&gt;performance-&gt;state
ques
c_cond
l_char|&squot;*&squot;
suffix:colon
l_char|&squot; &squot;
)paren
comma
id|i
comma
(paren
id|u32
)paren
id|pr-&gt;performance-&gt;states
(braket
id|i
)braket
dot
id|core_frequency
comma
(paren
id|u32
)paren
id|pr-&gt;performance-&gt;states
(braket
id|i
)braket
dot
id|power
comma
(paren
id|u32
)paren
id|pr-&gt;performance-&gt;states
(braket
id|i
)braket
dot
id|transition_latency
)paren
suffix:semicolon
id|end
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|acpi_processor_perf_open_fs
r_static
r_int
id|acpi_processor_perf_open_fs
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|single_open
c_func
(paren
id|file
comma
id|acpi_processor_perf_seq_show
comma
id|PDE
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|data
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_processor_write_performance
id|acpi_processor_write_performance
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_processor
op_star
id|pr
op_assign
(paren
r_struct
id|acpi_processor
op_star
)paren
id|data
suffix:semicolon
r_char
id|state_string
(braket
l_int|12
)braket
op_assign
(brace
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
r_int
r_int
id|new_state
op_assign
l_int|0
suffix:semicolon
r_struct
id|cpufreq_policy
id|policy
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_processor_write_performance&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
op_logical_or
op_logical_neg
id|pr-&gt;performance
op_logical_or
(paren
id|count
OG
r_sizeof
(paren
id|state_string
)paren
op_minus
l_int|1
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|state_string
comma
id|buffer
comma
id|count
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
id|state_string
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|new_state
op_assign
id|simple_strtoul
c_func
(paren
id|state_string
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|cpufreq_get_policy
c_func
(paren
op_amp
id|policy
comma
id|pr-&gt;id
)paren
suffix:semicolon
id|policy.cpu
op_assign
id|pr-&gt;id
suffix:semicolon
id|policy.max
op_assign
id|pr-&gt;performance-&gt;states
(braket
id|new_state
)braket
dot
id|core_frequency
op_star
l_int|1000
suffix:semicolon
id|result
op_assign
id|cpufreq_set_policy
c_func
(paren
op_amp
id|policy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|count
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_cpufreq_setpolicy
id|acpi_cpufreq_setpolicy
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_struct
id|acpi_processor
op_star
id|pr
op_assign
id|performance
(braket
id|policy-&gt;cpu
)braket
dot
id|pr
suffix:semicolon
r_int
r_int
id|next_state
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_cpufreq_setpolicy&quot;
)paren
suffix:semicolon
id|result
op_assign
id|cpufreq_frequency_table_setpolicy
c_func
(paren
id|policy
comma
op_amp
id|performance
(braket
id|policy-&gt;cpu
)braket
dot
id|freq_table
(braket
id|pr-&gt;limit.state.px
)braket
comma
op_amp
id|next_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
id|result
op_assign
id|acpi_processor_set_performance
(paren
id|pr
comma
id|next_state
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_cpufreq_verify
id|acpi_cpufreq_verify
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|policy-&gt;cpu
suffix:semicolon
r_struct
id|acpi_processor
op_star
id|pr
op_assign
id|performance
(braket
id|policy-&gt;cpu
)braket
dot
id|pr
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_cpufreq_verify&quot;
)paren
suffix:semicolon
id|result
op_assign
id|cpufreq_frequency_table_verify
c_func
(paren
id|policy
comma
op_amp
id|performance
(braket
id|cpu
)braket
dot
id|freq_table
(braket
id|pr-&gt;limit.state.px
)braket
)paren
suffix:semicolon
id|cpufreq_verify_within_limits
c_func
(paren
id|policy
comma
id|performance
(braket
id|cpu
)braket
dot
id|states
(braket
id|performance
(braket
id|cpu
)braket
dot
id|state_count
op_minus
l_int|1
)braket
dot
id|core_frequency
op_star
l_int|1000
comma
id|performance
(braket
id|cpu
)braket
dot
id|states
(braket
id|pr-&gt;limit.state.px
)braket
dot
id|core_frequency
op_star
l_int|1000
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_processor_get_performance_info
id|acpi_processor_get_performance_info
(paren
r_struct
id|acpi_processor
op_star
id|pr
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|acpi_handle
id|handle
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_processor_get_performance_info&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|status
op_assign
id|acpi_get_handle
c_func
(paren
id|pr-&gt;handle
comma
l_string|&quot;_PCT&quot;
comma
op_amp
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;ACPI-based processor performance control unavailable&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|result
op_assign
id|acpi_processor_get_performance_control
c_func
(paren
id|pr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
id|result
op_assign
id|acpi_processor_get_performance_states
c_func
(paren
id|pr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
id|result
op_assign
id|acpi_processor_get_platform_limit
c_func
(paren
id|pr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_cpufreq_cpu_init
id|acpi_cpufreq_cpu_init
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|policy-&gt;cpu
suffix:semicolon
r_struct
id|acpi_processor
op_star
id|pr
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_device
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_cpufreq_cpu_init&quot;
)paren
suffix:semicolon
id|acpi_processor_register_performance
c_func
(paren
op_amp
id|performance
(braket
id|cpu
)braket
comma
op_amp
id|pr
comma
id|cpu
)paren
suffix:semicolon
id|pr
op_assign
id|performance
(braket
id|cpu
)braket
dot
id|pr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_bus_get_device
c_func
(paren
id|pr-&gt;handle
comma
op_amp
id|device
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|result
op_assign
id|acpi_processor_get_performance_info
c_func
(paren
id|performance
(braket
id|cpu
)braket
dot
id|pr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
multiline_comment|/* capability check */
r_if
c_cond
(paren
op_logical_neg
id|pr-&gt;flags.performance
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
multiline_comment|/* detect transition latency */
id|policy-&gt;cpuinfo.transition_latency
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
id|performance
(braket
id|cpu
)braket
dot
id|state_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|performance
(braket
id|cpu
)braket
dot
id|states
(braket
id|i
)braket
dot
id|transition_latency
OG
id|policy-&gt;cpuinfo.transition_latency
)paren
id|policy-&gt;cpuinfo.transition_latency
op_assign
id|performance
(braket
id|cpu
)braket
dot
id|states
(braket
id|i
)braket
dot
id|transition_latency
suffix:semicolon
)brace
id|policy-&gt;policy
op_assign
id|CPUFREQ_POLICY_PERFORMANCE
suffix:semicolon
multiline_comment|/* table init */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|performance
(braket
id|cpu
)braket
dot
id|state_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|performance
(braket
id|cpu
)braket
dot
id|freq_table
(braket
id|i
)braket
dot
id|index
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|performance
(braket
id|cpu
)braket
dot
id|state_count
)paren
id|performance
(braket
id|cpu
)braket
dot
id|freq_table
(braket
id|i
)braket
dot
id|frequency
op_assign
id|performance
(braket
id|cpu
)braket
dot
id|states
(braket
id|i
)braket
dot
id|core_frequency
op_star
l_int|1000
suffix:semicolon
r_else
id|performance
(braket
id|cpu
)braket
dot
id|freq_table
(braket
id|i
)braket
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_CPU_FREQ_24_API
id|acpi_cpufreq_driver.cpu_cur_freq
(braket
id|policy-&gt;cpu
)braket
op_assign
id|performance
(braket
id|cpu
)braket
dot
id|states
(braket
id|pr-&gt;limit.state.px
)braket
dot
id|core_frequency
op_star
l_int|1000
suffix:semicolon
macro_line|#endif
id|result
op_assign
id|cpufreq_frequency_table_cpuinfo
c_func
(paren
id|policy
comma
op_amp
id|performance
(braket
id|cpu
)braket
dot
id|freq_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* add file &squot;performance&squot; [R/W] */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
id|ACPI_PROCESSOR_FILE_PERFORMANCE
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|acpi_device_dir
c_func
(paren
id|device
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unable to create &squot;%s&squot; fs entry&bslash;n&quot;
comma
id|ACPI_PROCESSOR_FILE_PERFORMANCE
)paren
)paren
suffix:semicolon
r_else
(brace
id|entry-&gt;proc_fops
op_assign
op_amp
id|acpi_processor_perf_fops
suffix:semicolon
id|entry-&gt;write_proc
op_assign
id|acpi_processor_write_performance
suffix:semicolon
id|entry-&gt;data
op_assign
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_cpufreq_init
id|acpi_cpufreq_init
(paren
r_void
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|current_state
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_processor
op_star
id|pr
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_cpufreq_init&quot;
)paren
suffix:semicolon
multiline_comment|/* alloc memory */
r_if
c_cond
(paren
id|performance
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EBUSY
)paren
suffix:semicolon
id|performance
op_assign
id|kmalloc
c_func
(paren
id|NR_CPUS
op_star
r_sizeof
(paren
r_struct
id|acpi_processor_performance
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|performance
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|performance
comma
l_int|0
comma
id|NR_CPUS
op_star
r_sizeof
(paren
r_struct
id|acpi_processor_performance
)paren
)paren
suffix:semicolon
multiline_comment|/* register struct acpi_performance performance */
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
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|i
)paren
)paren
id|acpi_processor_register_performance
c_func
(paren
op_amp
id|performance
(braket
id|i
)braket
comma
op_amp
id|pr
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* initialize  */
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
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|i
)paren
op_logical_and
id|performance
(braket
id|i
)braket
dot
id|pr
)paren
id|result
op_assign
id|acpi_processor_get_performance_info
c_func
(paren
id|performance
(braket
id|i
)braket
dot
id|pr
)paren
suffix:semicolon
)brace
multiline_comment|/* test it on one CPU */
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
id|i
op_increment
)paren
(brace
id|pr
op_assign
id|performance
(braket
id|i
)braket
dot
id|pr
suffix:semicolon
r_if
c_cond
(paren
id|pr
op_logical_and
id|pr-&gt;flags.performance
)paren
r_goto
id|found_capable_cpu
suffix:semicolon
)brace
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err
suffix:semicolon
id|found_capable_cpu
suffix:colon
id|current_state
op_assign
id|pr-&gt;performance-&gt;state
suffix:semicolon
r_if
c_cond
(paren
id|current_state
op_eq
id|pr-&gt;limit.state.px
)paren
(brace
id|result
op_assign
id|acpi_processor_set_performance
c_func
(paren
id|pr
comma
(paren
id|pr-&gt;performance-&gt;state_count
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Disabled P-States due to failure while switching.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
)brace
id|result
op_assign
id|acpi_processor_set_performance
c_func
(paren
id|pr
comma
id|pr-&gt;limit.state.px
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Disabled P-States due to failure while switching.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current_state
op_ne
l_int|0
)paren
(brace
id|result
op_assign
id|acpi_processor_set_performance
c_func
(paren
id|pr
comma
id|current_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Disabled P-States due to failure while switching.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
)brace
id|result
op_assign
id|cpufreq_register_driver
c_func
(paren
op_amp
id|acpi_cpufreq_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|err
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* error handling */
id|err
suffix:colon
multiline_comment|/* unregister struct acpi_performance performance */
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
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|performance
(braket
id|i
)braket
dot
id|pr
)paren
(brace
id|performance
(braket
id|i
)braket
dot
id|pr-&gt;flags.performance
op_assign
l_int|0
suffix:semicolon
id|performance
(braket
id|i
)braket
dot
id|pr-&gt;performance
op_assign
l_int|NULL
suffix:semicolon
id|performance
(braket
id|i
)braket
dot
id|pr
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|performance
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|acpi_cpufreq_exit
id|acpi_cpufreq_exit
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_cpufreq_exit&quot;
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|performance
(braket
id|i
)braket
dot
id|pr
)paren
id|performance
(braket
id|i
)braket
dot
id|pr-&gt;flags.performance
op_assign
l_int|0
suffix:semicolon
)brace
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|acpi_cpufreq_driver
)paren
suffix:semicolon
multiline_comment|/* unregister struct acpi_performance performance */
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
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|performance
(braket
id|i
)braket
dot
id|pr
)paren
(brace
id|performance
(braket
id|i
)braket
dot
id|pr-&gt;flags.performance
op_assign
l_int|0
suffix:semicolon
id|performance
(braket
id|i
)braket
dot
id|pr-&gt;performance
op_assign
l_int|NULL
suffix:semicolon
id|performance
(braket
id|i
)braket
dot
id|pr
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|performance
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
DECL|variable|acpi_cpufreq_driver
r_static
r_struct
id|cpufreq_driver
id|acpi_cpufreq_driver
op_assign
(brace
dot
id|verify
op_assign
id|acpi_cpufreq_verify
comma
dot
id|setpolicy
op_assign
id|acpi_cpufreq_setpolicy
comma
dot
id|init
op_assign
id|acpi_cpufreq_cpu_init
comma
dot
m_exit
op_assign
l_int|NULL
comma
dot
id|policy
op_assign
l_int|NULL
comma
dot
id|name
op_assign
l_string|&quot;acpi-cpufreq&quot;
comma
)brace
suffix:semicolon
DECL|variable|acpi_cpufreq_init
id|late_initcall
c_func
(paren
id|acpi_cpufreq_init
)paren
suffix:semicolon
DECL|variable|acpi_cpufreq_exit
id|module_exit
c_func
(paren
id|acpi_cpufreq_exit
)paren
suffix:semicolon
eof
