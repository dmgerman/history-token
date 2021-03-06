multiline_comment|/*&n; * PowerPC64 LPAR Configuration Information Driver&n; *&n; * Dave Engebretsen engebret@us.ibm.com&n; *    Copyright (c) 2003 Dave Engebretsen&n; * Will Schmidt willschm@us.ibm.com&n; *    SPLPAR updates, Copyright (c) 2003 Will Schmidt IBM Corporation.&n; *    seq_file updates, Copyright (c) 2004 Will Schmidt IBM Corporation.&n; * Nathan Lynch nathanl@austin.ibm.com&n; *    Added lparcfg_write, Copyright (C) 2004 Nathan Lynch IBM Corporation.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; * This driver creates a proc file at /proc/ppc64/lparcfg which contains&n; * keyword - value pairs that specify the configuration of the partition.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/iSeries/HvLpConfig.h&gt;
macro_line|#include &lt;asm/lppaca.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/hvcall.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/time.h&gt;
DECL|macro|MODULE_VERS
mdefine_line|#define MODULE_VERS &quot;1.6&quot;
DECL|macro|MODULE_NAME
mdefine_line|#define MODULE_NAME &quot;lparcfg&quot;
multiline_comment|/* #define LPARCFG_DEBUG */
multiline_comment|/* find a better place for this function... */
DECL|function|log_plpar_hcall_return
r_void
id|log_plpar_hcall_return
c_func
(paren
r_int
r_int
id|rc
comma
r_char
op_star
id|tag
)paren
(brace
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
multiline_comment|/* success, return */
r_return
suffix:semicolon
multiline_comment|/* check for null tag ? */
r_if
c_cond
(paren
id|rc
op_eq
id|H_Hardware
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;plpar-hcall (%s) failed with hardware fault&bslash;n&quot;
comma
id|tag
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rc
op_eq
id|H_Function
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;plpar-hcall (%s) failed; function not allowed&bslash;n&quot;
comma
id|tag
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rc
op_eq
id|H_Authority
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;plpar-hcall (%s) failed; not authorized to this function&bslash;n&quot;
comma
id|tag
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rc
op_eq
id|H_Parameter
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;plpar-hcall (%s) failed; Bad parameter(s)&bslash;n&quot;
comma
id|tag
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;plpar-hcall (%s) failed with unexpected rc(0x%lx)&bslash;n&quot;
comma
id|tag
comma
id|rc
)paren
suffix:semicolon
)brace
DECL|variable|proc_ppc64_lparcfg
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_ppc64_lparcfg
suffix:semicolon
DECL|macro|LPARCFG_BUFF_SIZE
mdefine_line|#define LPARCFG_BUFF_SIZE 4096
macro_line|#ifdef CONFIG_PPC_ISERIES
multiline_comment|/*&n; * For iSeries legacy systems, the PPA purr function is available from the&n; * emulated_time_base field in the paca.&n; */
DECL|function|get_purr
r_static
r_int
r_int
id|get_purr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sum_purr
op_assign
l_int|0
suffix:semicolon
r_int
id|cpu
suffix:semicolon
r_struct
id|paca_struct
op_star
id|lpaca
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|cpu
)paren
(brace
id|lpaca
op_assign
id|paca
op_plus
id|cpu
suffix:semicolon
id|sum_purr
op_add_assign
id|lpaca-&gt;lppaca.emulated_time_base
suffix:semicolon
macro_line|#ifdef PURR_DEBUG
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;get_purr for cpu (%d) has value (%ld) &bslash;n&quot;
comma
id|cpu
comma
id|lpaca-&gt;lppaca.emulated_time_base
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
id|sum_purr
suffix:semicolon
)brace
DECL|macro|lparcfg_write
mdefine_line|#define lparcfg_write NULL
multiline_comment|/* &n; * Methods used to fetch LPAR data when running on an iSeries platform.&n; */
DECL|function|lparcfg_data
r_static
r_int
id|lparcfg_data
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
id|pool_id
comma
id|lp_index
suffix:semicolon
r_int
id|shared
comma
id|entitled_capacity
comma
id|max_entitled_capacity
suffix:semicolon
r_int
id|processors
comma
id|max_processors
suffix:semicolon
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
r_int
r_int
id|purr
op_assign
id|get_purr
c_func
(paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%s %s &bslash;n&quot;
comma
id|MODULE_NAME
comma
id|MODULE_VERS
)paren
suffix:semicolon
id|shared
op_assign
(paren
r_int
)paren
(paren
id|lpaca-&gt;lppaca_ptr-&gt;shared_proc
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;serial_number=%c%c%c%c%c%c%c&bslash;n&quot;
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.mfgID
(braket
l_int|2
)braket
)paren
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.mfgID
(braket
l_int|3
)braket
)paren
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.systemSerial
(braket
l_int|1
)braket
)paren
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.systemSerial
(braket
l_int|2
)braket
)paren
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.systemSerial
(braket
l_int|3
)braket
)paren
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.systemSerial
(braket
l_int|4
)braket
)paren
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.systemSerial
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system_type=%c%c%c%c&bslash;n&quot;
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.machineType
(braket
l_int|0
)braket
)paren
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.machineType
(braket
l_int|1
)braket
)paren
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.machineType
(braket
l_int|2
)braket
)paren
comma
id|e2a
c_func
(paren
id|xItExtVpdPanel.machineType
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
id|lp_index
op_assign
id|HvLpConfig_getLpIndex
c_func
(paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;partition_id=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|lp_index
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system_active_processors=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|HvLpConfig_getSystemPhysicalProcessors
c_func
(paren
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system_potential_processors=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|HvLpConfig_getSystemPhysicalProcessors
c_func
(paren
)paren
)paren
suffix:semicolon
id|processors
op_assign
(paren
r_int
)paren
id|HvLpConfig_getPhysicalProcessors
c_func
(paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;partition_active_processors=%d&bslash;n&quot;
comma
id|processors
)paren
suffix:semicolon
id|max_processors
op_assign
(paren
r_int
)paren
id|HvLpConfig_getMaxPhysicalProcessors
c_func
(paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;partition_potential_processors=%d&bslash;n&quot;
comma
id|max_processors
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shared
)paren
(brace
id|entitled_capacity
op_assign
id|HvLpConfig_getSharedProcUnits
c_func
(paren
)paren
suffix:semicolon
id|max_entitled_capacity
op_assign
id|HvLpConfig_getMaxSharedProcUnits
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|entitled_capacity
op_assign
id|processors
op_star
l_int|100
suffix:semicolon
id|max_entitled_capacity
op_assign
id|max_processors
op_star
l_int|100
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;partition_entitled_capacity=%d&bslash;n&quot;
comma
id|entitled_capacity
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;partition_max_entitled_capacity=%d&bslash;n&quot;
comma
id|max_entitled_capacity
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shared
)paren
(brace
id|pool_id
op_assign
id|HvLpConfig_getSharedPoolIndex
c_func
(paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pool=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|pool_id
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pool_capacity=%d&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|HvLpConfig_getNumProcsInSharedPool
c_func
(paren
id|pool_id
)paren
op_star
l_int|100
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;purr=%ld&bslash;n&quot;
comma
id|purr
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;shared_processor_mode=%d&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* CONFIG_PPC_ISERIES */
macro_line|#ifdef CONFIG_PPC_PSERIES
multiline_comment|/* &n; * Methods used to fetch LPAR data when running on a pSeries platform.&n; */
multiline_comment|/*&n; * H_GET_PPP hcall returns info in 4 parms.&n; *  entitled_capacity,unallocated_capacity,&n; *  aggregation, resource_capability).&n; *&n; *  R4 = Entitled Processor Capacity Percentage. &n; *  R5 = Unallocated Processor Capacity Percentage.&n; *  R6 (AABBCCDDEEFFGGHH).&n; *      XXXX - reserved (0)&n; *          XXXX - reserved (0)&n; *              XXXX - Group Number&n; *                  XXXX - Pool Number.&n; *  R7 (IIJJKKLLMMNNOOPP).&n; *      XX - reserved. (0)&n; *        XX - bit 0-6 reserved (0).   bit 7 is Capped indicator.&n; *          XX - variable processor Capacity Weight&n; *            XX - Unallocated Variable Processor Capacity Weight.&n; *              XXXX - Active processors in Physical Processor Pool.&n; *                  XXXX  - Processors active on platform. &n; */
DECL|function|h_get_ppp
r_static
r_int
r_int
id|h_get_ppp
c_func
(paren
r_int
r_int
op_star
id|entitled
comma
r_int
r_int
op_star
id|unallocated
comma
r_int
r_int
op_star
id|aggregation
comma
r_int
r_int
op_star
id|resource
)paren
(brace
r_int
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|plpar_hcall_4out
c_func
(paren
id|H_GET_PPP
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|entitled
comma
id|unallocated
comma
id|aggregation
comma
id|resource
)paren
suffix:semicolon
id|log_plpar_hcall_return
c_func
(paren
id|rc
comma
l_string|&quot;H_GET_PPP&quot;
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|h_pic
r_static
r_void
id|h_pic
c_func
(paren
r_int
r_int
op_star
id|pool_idle_time
comma
r_int
r_int
op_star
id|num_procs
)paren
(brace
r_int
r_int
id|rc
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
id|rc
op_assign
id|plpar_hcall
c_func
(paren
id|H_PIC
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|pool_idle_time
comma
id|num_procs
comma
op_amp
id|dummy
)paren
suffix:semicolon
id|log_plpar_hcall_return
c_func
(paren
id|rc
comma
l_string|&quot;H_PIC&quot;
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
id|get_purr
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Track sum of all purrs across all processors. This is used to further */
multiline_comment|/* calculate usage values by different applications                       */
DECL|function|get_purr
r_static
r_int
r_int
id|get_purr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sum_purr
op_assign
l_int|0
suffix:semicolon
r_int
id|cpu
suffix:semicolon
r_struct
id|cpu_usage
op_star
id|cu
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|cpu
)paren
(brace
id|cu
op_assign
op_amp
id|per_cpu
c_func
(paren
id|cpu_usage_array
comma
id|cpu
)paren
suffix:semicolon
id|sum_purr
op_add_assign
id|cu-&gt;current_tb
suffix:semicolon
)brace
r_return
id|sum_purr
suffix:semicolon
)brace
DECL|macro|SPLPAR_CHARACTERISTICS_TOKEN
mdefine_line|#define SPLPAR_CHARACTERISTICS_TOKEN 20
DECL|macro|SPLPAR_MAXLENGTH
mdefine_line|#define SPLPAR_MAXLENGTH 1026*(sizeof(char))
multiline_comment|/*&n; * parse_system_parameter_string()&n; * Retrieve the potential_processors, max_entitled_capacity and friends&n; * through the get-system-parameter rtas call.  Replace keyword strings as&n; * necessary.&n; */
DECL|function|parse_system_parameter_string
r_static
r_void
id|parse_system_parameter_string
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_int
id|call_status
suffix:semicolon
r_char
op_star
id|local_buffer
op_assign
id|kmalloc
c_func
(paren
id|SPLPAR_MAXLENGTH
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|local_buffer
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s %s kmalloc failure at line %d &bslash;n&quot;
comma
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|rtas_data_buf_lock
)paren
suffix:semicolon
id|memset
c_func
(paren
id|rtas_data_buf
comma
l_int|0
comma
id|SPLPAR_MAXLENGTH
)paren
suffix:semicolon
id|call_status
op_assign
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;ibm,get-system-parameter&quot;
)paren
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
id|SPLPAR_CHARACTERISTICS_TOKEN
comma
id|__pa
c_func
(paren
id|rtas_data_buf
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|local_buffer
comma
id|rtas_data_buf
comma
id|SPLPAR_MAXLENGTH
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rtas_data_buf_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|call_status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s %s Error calling get-system-parameter (0x%x)&bslash;n&quot;
comma
id|__FILE__
comma
id|__FUNCTION__
comma
id|call_status
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|splpar_strlen
suffix:semicolon
r_int
id|idx
comma
id|w_idx
suffix:semicolon
r_char
op_star
id|workbuffer
op_assign
id|kmalloc
c_func
(paren
id|SPLPAR_MAXLENGTH
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|workbuffer
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s %s kmalloc failure at line %d &bslash;n&quot;
comma
id|__FILE__
comma
id|__FUNCTION__
comma
id|__LINE__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef LPARCFG_DEBUG
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;success calling get-system-parameter &bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|splpar_strlen
op_assign
id|local_buffer
(braket
l_int|0
)braket
op_star
l_int|16
op_plus
id|local_buffer
(braket
l_int|1
)braket
suffix:semicolon
id|local_buffer
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* step over strlen value */
id|memset
c_func
(paren
id|workbuffer
comma
l_int|0
comma
id|SPLPAR_MAXLENGTH
)paren
suffix:semicolon
id|w_idx
op_assign
l_int|0
suffix:semicolon
id|idx
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|local_buffer
)paren
op_logical_and
(paren
id|idx
OL
id|splpar_strlen
)paren
)paren
(brace
id|workbuffer
(braket
id|w_idx
op_increment
)braket
op_assign
id|local_buffer
(braket
id|idx
op_increment
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|local_buffer
(braket
id|idx
)braket
op_eq
l_char|&squot;,&squot;
)paren
op_logical_or
(paren
id|local_buffer
(braket
id|idx
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
)paren
(brace
id|workbuffer
(braket
id|w_idx
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|w_idx
)paren
(brace
multiline_comment|/* avoid the empty string */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|workbuffer
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|workbuffer
comma
l_int|0
comma
id|SPLPAR_MAXLENGTH
)paren
suffix:semicolon
id|idx
op_increment
suffix:semicolon
multiline_comment|/* skip the comma */
id|w_idx
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|local_buffer
(braket
id|idx
)braket
op_eq
l_char|&squot;=&squot;
)paren
(brace
multiline_comment|/* code here to replace workbuffer contents&n;&t;&t;&t;&t;   with different keyword strings */
r_if
c_cond
(paren
l_int|0
op_eq
id|strcmp
c_func
(paren
id|workbuffer
comma
l_string|&quot;MaxEntCap&quot;
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|workbuffer
comma
l_string|&quot;partition_max_entitled_capacity&quot;
)paren
suffix:semicolon
id|w_idx
op_assign
id|strlen
c_func
(paren
id|workbuffer
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|strcmp
c_func
(paren
id|workbuffer
comma
l_string|&quot;MaxPlatProcs&quot;
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|workbuffer
comma
l_string|&quot;system_potential_processors&quot;
)paren
suffix:semicolon
id|w_idx
op_assign
id|strlen
c_func
(paren
id|workbuffer
)paren
suffix:semicolon
)brace
)brace
)brace
id|kfree
c_func
(paren
id|workbuffer
)paren
suffix:semicolon
id|local_buffer
op_sub_assign
l_int|2
suffix:semicolon
multiline_comment|/* back up over strlen value */
)brace
id|kfree
c_func
(paren
id|local_buffer
)paren
suffix:semicolon
)brace
r_static
r_int
id|lparcfg_count_active_processors
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Return the number of processors in the system.&n; * This function reads through the device tree and counts&n; * the virtual processors, this does not include threads.&n; */
DECL|function|lparcfg_count_active_processors
r_static
r_int
id|lparcfg_count_active_processors
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|cpus_dn
op_assign
l_int|NULL
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|cpus_dn
op_assign
id|of_find_node_by_type
c_func
(paren
id|cpus_dn
comma
l_string|&quot;cpu&quot;
)paren
)paren
)paren
(brace
macro_line|#ifdef LPARCFG_DEBUG
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpus_dn %p &bslash;n&quot;
comma
id|cpus_dn
)paren
suffix:semicolon
macro_line|#endif
id|count
op_increment
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|lparcfg_data
r_static
r_int
id|lparcfg_data
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
id|partition_potential_processors
suffix:semicolon
r_int
id|partition_active_processors
suffix:semicolon
r_struct
id|device_node
op_star
id|rootdn
suffix:semicolon
r_const
r_char
op_star
id|model
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_const
r_char
op_star
id|system_id
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_int
r_int
op_star
id|lp_index_ptr
comma
id|lp_index
op_assign
l_int|0
suffix:semicolon
r_struct
id|device_node
op_star
id|rtas_node
suffix:semicolon
r_int
op_star
id|lrdrp
suffix:semicolon
id|rootdn
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
id|rootdn
)paren
(brace
id|model
op_assign
id|get_property
c_func
(paren
id|rootdn
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|system_id
op_assign
id|get_property
c_func
(paren
id|rootdn
comma
l_string|&quot;system-id&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|lp_index_ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|rootdn
comma
l_string|&quot;ibm,partition-no&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp_index_ptr
)paren
id|lp_index
op_assign
op_star
id|lp_index_ptr
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%s %s &bslash;n&quot;
comma
id|MODULE_NAME
comma
id|MODULE_VERS
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;serial_number=%s&bslash;n&quot;
comma
id|system_id
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system_type=%s&bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;partition_id=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|lp_index
)paren
suffix:semicolon
id|rtas_node
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/rtas&quot;
)paren
suffix:semicolon
id|lrdrp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|rtas_node
comma
l_string|&quot;ibm,lrdr-capacity&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lrdrp
op_eq
l_int|NULL
)paren
(brace
id|partition_potential_processors
op_assign
id|systemcfg-&gt;processorCount
suffix:semicolon
)brace
r_else
(brace
id|partition_potential_processors
op_assign
op_star
(paren
id|lrdrp
op_plus
l_int|4
)paren
suffix:semicolon
)brace
id|partition_active_processors
op_assign
id|lparcfg_count_active_processors
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;firmware_features
op_amp
id|FW_FEATURE_SPLPAR
)paren
(brace
r_int
r_int
id|h_entitled
comma
id|h_unallocated
suffix:semicolon
r_int
r_int
id|h_aggregation
comma
id|h_resource
suffix:semicolon
r_int
r_int
id|pool_idle_time
comma
id|pool_procs
suffix:semicolon
r_int
r_int
id|purr
suffix:semicolon
id|h_get_ppp
c_func
(paren
op_amp
id|h_entitled
comma
op_amp
id|h_unallocated
comma
op_amp
id|h_aggregation
comma
op_amp
id|h_resource
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;R4=0x%lx&bslash;n&quot;
comma
id|h_entitled
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;R5=0x%lx&bslash;n&quot;
comma
id|h_unallocated
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;R6=0x%lx&bslash;n&quot;
comma
id|h_aggregation
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;R7=0x%lx&bslash;n&quot;
comma
id|h_resource
)paren
suffix:semicolon
id|purr
op_assign
id|get_purr
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* this call handles the ibm,get-system-parameter contents */
id|parse_system_parameter_string
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
l_string|&quot;partition_entitled_capacity=%ld&bslash;n&quot;
comma
id|h_entitled
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;group=%ld&bslash;n&quot;
comma
(paren
id|h_aggregation
op_rshift
l_int|2
op_star
l_int|8
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system_active_processors=%ld&bslash;n&quot;
comma
(paren
id|h_resource
op_rshift
l_int|0
op_star
l_int|8
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
multiline_comment|/* pool related entries are apropriate for shared configs */
r_if
c_cond
(paren
id|paca
(braket
l_int|0
)braket
dot
id|lppaca.shared_proc
)paren
(brace
id|h_pic
c_func
(paren
op_amp
id|pool_idle_time
comma
op_amp
id|pool_procs
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pool=%ld&bslash;n&quot;
comma
(paren
id|h_aggregation
op_rshift
l_int|0
op_star
l_int|8
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
multiline_comment|/* report pool_capacity in percentage */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pool_capacity=%ld&bslash;n&quot;
comma
(paren
(paren
id|h_resource
op_rshift
l_int|2
op_star
l_int|8
)paren
op_amp
l_int|0xffff
)paren
op_star
l_int|100
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pool_idle_time=%ld&bslash;n&quot;
comma
id|pool_idle_time
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pool_num_procs=%ld&bslash;n&quot;
comma
id|pool_procs
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;unallocated_capacity_weight=%ld&bslash;n&quot;
comma
(paren
id|h_resource
op_rshift
l_int|4
op_star
l_int|8
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;capacity_weight=%ld&bslash;n&quot;
comma
(paren
id|h_resource
op_rshift
l_int|5
op_star
l_int|8
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;capped=%ld&bslash;n&quot;
comma
(paren
id|h_resource
op_rshift
l_int|6
op_star
l_int|8
)paren
op_amp
l_int|0x01
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;unallocated_capacity=%ld&bslash;n&quot;
comma
id|h_unallocated
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;purr=%ld&bslash;n&quot;
comma
id|purr
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* non SPLPAR case */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system_active_processors=%d&bslash;n&quot;
comma
id|partition_potential_processors
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system_potential_processors=%d&bslash;n&quot;
comma
id|partition_potential_processors
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;partition_max_entitled_capacity=%d&bslash;n&quot;
comma
id|partition_potential_processors
op_star
l_int|100
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;partition_entitled_capacity=%d&bslash;n&quot;
comma
id|partition_active_processors
op_star
l_int|100
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;partition_active_processors=%d&bslash;n&quot;
comma
id|partition_active_processors
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;partition_potential_processors=%d&bslash;n&quot;
comma
id|partition_potential_processors
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;shared_processor_mode=%d&bslash;n&quot;
comma
id|paca
(braket
l_int|0
)braket
dot
id|lppaca.shared_proc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Interface for changing system parameters (variable capacity weight&n; * and entitled capacity).  Format of input is &quot;param_name=value&quot;;&n; * anything after value is ignored.  Valid parameters at this time are&n; * &quot;partition_entitled_capacity&quot; and &quot;capacity_weight&quot;.  We use&n; * H_SET_PPP to alter parameters.&n; *&n; * This function should be invoked only on systems with&n; * FW_FEATURE_SPLPAR.&n; */
DECL|function|lparcfg_write
r_static
id|ssize_t
id|lparcfg_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_char
op_star
id|kbuf
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
id|u64
id|new_entitled
comma
op_star
id|new_entitled_ptr
op_assign
op_amp
id|new_entitled
suffix:semicolon
id|u8
id|new_weight
comma
op_star
id|new_weight_ptr
op_assign
op_amp
id|new_weight
suffix:semicolon
r_int
r_int
id|current_entitled
suffix:semicolon
multiline_comment|/* parameters for h_get_ppp */
r_int
r_int
id|dummy
suffix:semicolon
r_int
r_int
id|resource
suffix:semicolon
id|u8
id|current_weight
suffix:semicolon
id|ssize_t
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|kbuf
op_assign
id|kmalloc
c_func
(paren
id|count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbuf
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kbuf
comma
id|buf
comma
id|count
)paren
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|kbuf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|tmp
op_assign
id|strchr
c_func
(paren
id|kbuf
comma
l_char|&squot;=&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_goto
id|out
suffix:semicolon
op_star
id|tmp
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|kbuf
comma
l_string|&quot;partition_entitled_capacity&quot;
)paren
)paren
(brace
r_char
op_star
id|endp
suffix:semicolon
op_star
id|new_entitled_ptr
op_assign
(paren
id|u64
)paren
id|simple_strtoul
c_func
(paren
id|tmp
comma
op_amp
id|endp
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|endp
op_eq
id|tmp
)paren
r_goto
id|out
suffix:semicolon
id|new_weight_ptr
op_assign
op_amp
id|current_weight
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|kbuf
comma
l_string|&quot;capacity_weight&quot;
)paren
)paren
(brace
r_char
op_star
id|endp
suffix:semicolon
op_star
id|new_weight_ptr
op_assign
(paren
id|u8
)paren
id|simple_strtoul
c_func
(paren
id|tmp
comma
op_amp
id|endp
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|endp
op_eq
id|tmp
)paren
r_goto
id|out
suffix:semicolon
id|new_entitled_ptr
op_assign
op_amp
id|current_entitled
suffix:semicolon
)brace
r_else
r_goto
id|out
suffix:semicolon
multiline_comment|/* Get our current parameters */
id|retval
op_assign
id|h_get_ppp
c_func
(paren
op_amp
id|current_entitled
comma
op_amp
id|dummy
comma
op_amp
id|dummy
comma
op_amp
id|resource
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|current_weight
op_assign
(paren
id|resource
op_rshift
l_int|5
op_star
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: current_entitled = %lu, current_weight = %lu&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|current_entitled
comma
id|current_weight
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: new_entitled = %lu, new_weight = %lu&bslash;n&quot;
comma
id|__FUNCTION__
comma
op_star
id|new_entitled_ptr
comma
op_star
id|new_weight_ptr
)paren
suffix:semicolon
id|retval
op_assign
id|plpar_hcall_norets
c_func
(paren
id|H_SET_PPP
comma
op_star
id|new_entitled_ptr
comma
op_star
id|new_weight_ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
id|H_Success
op_logical_or
id|retval
op_eq
id|H_Constrained
)paren
(brace
id|retval
op_assign
id|count
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|retval
op_eq
id|H_Busy
)paren
(brace
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|retval
op_eq
id|H_Hardware
)paren
(brace
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|retval
op_eq
id|H_Parameter
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: received unknown hv return code %ld&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|out
suffix:colon
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* CONFIG_PPC_PSERIES */
DECL|function|lparcfg_open
r_static
r_int
id|lparcfg_open
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
id|lparcfg_data
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|lparcfg_fops
r_struct
id|file_operations
id|lparcfg_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|open
op_assign
id|lparcfg_open
comma
dot
id|release
op_assign
id|single_release
comma
)brace
suffix:semicolon
DECL|function|lparcfg_init
r_int
id|__init
id|lparcfg_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
id|mode_t
id|mode
op_assign
id|S_IRUSR
suffix:semicolon
multiline_comment|/* Allow writing if we have FW_FEATURE_SPLPAR */
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;firmware_features
op_amp
id|FW_FEATURE_SPLPAR
)paren
(brace
id|lparcfg_fops.write
op_assign
id|lparcfg_write
suffix:semicolon
id|mode
op_or_assign
id|S_IWUSR
suffix:semicolon
)brace
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;ppc64/lparcfg&quot;
comma
id|mode
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|ent-&gt;proc_fops
op_assign
op_amp
id|lparcfg_fops
suffix:semicolon
id|ent-&gt;data
op_assign
id|kmalloc
c_func
(paren
id|LPARCFG_BUFF_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent-&gt;data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to allocate buffer for lparcfg&bslash;n&quot;
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;lparcfg&quot;
comma
id|ent-&gt;parent
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to create ppc64/lparcfg&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|proc_ppc64_lparcfg
op_assign
id|ent
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lparcfg_cleanup
r_void
id|__exit
id|lparcfg_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|proc_ppc64_lparcfg
)paren
(brace
r_if
c_cond
(paren
id|proc_ppc64_lparcfg-&gt;data
)paren
(brace
id|kfree
c_func
(paren
id|proc_ppc64_lparcfg-&gt;data
)paren
suffix:semicolon
)brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;lparcfg&quot;
comma
id|proc_ppc64_lparcfg-&gt;parent
)paren
suffix:semicolon
)brace
)brace
DECL|variable|lparcfg_init
id|module_init
c_func
(paren
id|lparcfg_init
)paren
suffix:semicolon
DECL|variable|lparcfg_cleanup
id|module_exit
c_func
(paren
id|lparcfg_cleanup
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Interface for LPAR configuration data&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dave Engebretsen&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
