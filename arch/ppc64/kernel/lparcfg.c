multiline_comment|/*&n; * PowerPC64 LPAR Configuration Information Driver&n; *&n; * Dave Engebretsen engebret@us.ibm.com&n; *    Copyright (c) 2003 Dave Engebretsen&n; * Will Schmidt willschm@us.ibm.com&n; *    SPLPAR updates, Copyright (c) 2003 Will Schmidt IBM Corporation.&n; * Nathan Lynch nathanl@austin.ibm.com&n; *    Added lparcfg_write, Copyright (C) 2004 Nathan Lynch IBM Corporation.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; * This driver creates a proc file at /proc/ppc64/lparcfg which contains&n; * keyword - value pairs that specify the configuration of the partition.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/iSeries/HvLpConfig.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include &lt;asm/hvcall.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
DECL|macro|MODULE_VERS
mdefine_line|#define MODULE_VERS &quot;1.0&quot;
DECL|macro|MODULE_NAME
mdefine_line|#define MODULE_NAME &quot;lparcfg&quot;
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
DECL|macro|lparcfg_write
mdefine_line|#define lparcfg_write NULL
DECL|function|e2a
r_static
r_int
r_char
id|e2a
c_func
(paren
r_int
r_char
id|x
)paren
(brace
r_switch
c_cond
(paren
id|x
)paren
(brace
r_case
l_int|0xF0
suffix:colon
r_return
l_char|&squot;0&squot;
suffix:semicolon
r_case
l_int|0xF1
suffix:colon
r_return
l_char|&squot;1&squot;
suffix:semicolon
r_case
l_int|0xF2
suffix:colon
r_return
l_char|&squot;2&squot;
suffix:semicolon
r_case
l_int|0xF3
suffix:colon
r_return
l_char|&squot;3&squot;
suffix:semicolon
r_case
l_int|0xF4
suffix:colon
r_return
l_char|&squot;4&squot;
suffix:semicolon
r_case
l_int|0xF5
suffix:colon
r_return
l_char|&squot;5&squot;
suffix:semicolon
r_case
l_int|0xF6
suffix:colon
r_return
l_char|&squot;6&squot;
suffix:semicolon
r_case
l_int|0xF7
suffix:colon
r_return
l_char|&squot;7&squot;
suffix:semicolon
r_case
l_int|0xF8
suffix:colon
r_return
l_char|&squot;8&squot;
suffix:semicolon
r_case
l_int|0xF9
suffix:colon
r_return
l_char|&squot;9&squot;
suffix:semicolon
r_case
l_int|0xC1
suffix:colon
r_return
l_char|&squot;A&squot;
suffix:semicolon
r_case
l_int|0xC2
suffix:colon
r_return
l_char|&squot;B&squot;
suffix:semicolon
r_case
l_int|0xC3
suffix:colon
r_return
l_char|&squot;C&squot;
suffix:semicolon
r_case
l_int|0xC4
suffix:colon
r_return
l_char|&squot;D&squot;
suffix:semicolon
r_case
l_int|0xC5
suffix:colon
r_return
l_char|&squot;E&squot;
suffix:semicolon
r_case
l_int|0xC6
suffix:colon
r_return
l_char|&squot;F&squot;
suffix:semicolon
r_case
l_int|0xC7
suffix:colon
r_return
l_char|&squot;G&squot;
suffix:semicolon
r_case
l_int|0xC8
suffix:colon
r_return
l_char|&squot;H&squot;
suffix:semicolon
r_case
l_int|0xC9
suffix:colon
r_return
l_char|&squot;I&squot;
suffix:semicolon
r_case
l_int|0xD1
suffix:colon
r_return
l_char|&squot;J&squot;
suffix:semicolon
r_case
l_int|0xD2
suffix:colon
r_return
l_char|&squot;K&squot;
suffix:semicolon
r_case
l_int|0xD3
suffix:colon
r_return
l_char|&squot;L&squot;
suffix:semicolon
r_case
l_int|0xD4
suffix:colon
r_return
l_char|&squot;M&squot;
suffix:semicolon
r_case
l_int|0xD5
suffix:colon
r_return
l_char|&squot;N&squot;
suffix:semicolon
r_case
l_int|0xD6
suffix:colon
r_return
l_char|&squot;O&squot;
suffix:semicolon
r_case
l_int|0xD7
suffix:colon
r_return
l_char|&squot;P&squot;
suffix:semicolon
r_case
l_int|0xD8
suffix:colon
r_return
l_char|&squot;Q&squot;
suffix:semicolon
r_case
l_int|0xD9
suffix:colon
r_return
l_char|&squot;R&squot;
suffix:semicolon
r_case
l_int|0xE2
suffix:colon
r_return
l_char|&squot;S&squot;
suffix:semicolon
r_case
l_int|0xE3
suffix:colon
r_return
l_char|&squot;T&squot;
suffix:semicolon
r_case
l_int|0xE4
suffix:colon
r_return
l_char|&squot;U&squot;
suffix:semicolon
r_case
l_int|0xE5
suffix:colon
r_return
l_char|&squot;V&squot;
suffix:semicolon
r_case
l_int|0xE6
suffix:colon
r_return
l_char|&squot;W&squot;
suffix:semicolon
r_case
l_int|0xE7
suffix:colon
r_return
l_char|&squot;X&squot;
suffix:semicolon
r_case
l_int|0xE8
suffix:colon
r_return
l_char|&squot;Y&squot;
suffix:semicolon
r_case
l_int|0xE9
suffix:colon
r_return
l_char|&squot;Z&squot;
suffix:semicolon
)brace
r_return
l_char|&squot; &squot;
suffix:semicolon
)brace
multiline_comment|/* &n; * Methods used to fetch LPAR data when running on an iSeries platform.&n; */
DECL|function|lparcfg_data
r_static
r_int
id|lparcfg_data
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|n
op_assign
l_int|0
comma
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
r_if
c_cond
(paren
(paren
id|buf
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|size
OG
id|LPARCFG_BUFF_SIZE
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|shared
op_assign
(paren
r_int
)paren
(paren
id|lpaca-&gt;lppaca.xSharedProc
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;partition_id=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|lp_index
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;partition_entitled_capacity=%d&bslash;n&quot;
comma
id|entitled_capacity
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;pool=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|pool_id
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
)brace
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
macro_line|#endif /* CONFIG_PPC_ISERIES */
macro_line|#ifdef CONFIG_PPC_PSERIES
multiline_comment|/* &n; * Methods used to fetch LPAR data when running on a pSeries platform.&n; */
multiline_comment|/*&n; * H_GET_PPP hcall returns info in 4 parms.&n; *  entitled_capacity,unallocated_capacity,&n; *  aggregation, resource_capability).&n; *&n; *  R4 = Entitled Processor Capacity Percentage. &n; *  R5 = Unallocated Processor Capacity Percentage.&n; *  R6 (AABBCCDDEEFFGGHH).&n; *      XXXX - reserved (0)&n; *          XXXX - reserved (0)&n; *              XXXX - Group Number&n; *                  XXXX - Pool Number.&n; *  R7 (PPOONNMMLLKKJJII)&n; *      XX - reserved. (0)&n; *        XX - bit 0-6 reserved (0).   bit 7 is Capped indicator.&n; *          XX - variable processor Capacity Weight&n; *            XX - Unallocated Variable Processor Capacity Weight.&n; *              XXXX - Active processors in Physical Processor Pool.&n; *                  XXXX  - Processors active on platform. &n; */
DECL|function|h_get_ppp
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * get_splpar_potential_characteristics().&n; * Retrieve the potential_processors and max_entitled_capacity values&n; * through the get-system-parameter rtas call.&n; */
DECL|macro|SPLPAR_CHARACTERISTICS_TOKEN
mdefine_line|#define SPLPAR_CHARACTERISTICS_TOKEN 20
DECL|macro|SPLPAR_MAXLENGTH
mdefine_line|#define SPLPAR_MAXLENGTH 1026*(sizeof(char))
DECL|function|get_splpar_potential_characteristics
r_int
r_int
id|get_splpar_potential_characteristics
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* return 0 for now.  Underlying rtas functionality is not yet complete. 12/01/2003*/
r_return
l_int|0
suffix:semicolon
macro_line|#if 0 
r_int
id|call_status
suffix:semicolon
r_int
r_int
id|ret
(braket
l_int|2
)braket
suffix:semicolon
r_char
op_star
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|SPLPAR_MAXLENGTH
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;token for ibm,get-system-parameter (0x%x)&bslash;n&quot;
comma
id|rtas_token
c_func
(paren
l_string|&quot;ibm,get-system-parameter&quot;
)paren
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
op_amp
id|buffer
comma
id|SPLPAR_MAXLENGTH
comma
(paren
r_void
op_star
)paren
op_amp
id|ret
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
l_string|&quot;Error calling get-system-parameter (0x%lx)&bslash;n&quot;
comma
id|call_status
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;get-system-parameter (%s)&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
multiline_comment|/* TODO: Add code here to parse out value for system_potential_processors and partition_max_entitled_capacity */
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|lparcfg_data
r_static
r_int
id|lparcfg_data
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_int
id|shared
comma
id|max_entitled_capacity
suffix:semicolon
r_int
id|processors
comma
id|system_active_processors
comma
id|system_potential_processors
suffix:semicolon
r_struct
id|device_node
op_star
id|root
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
id|ip
suffix:semicolon
r_int
r_int
id|h_entitled
comma
id|h_unallocated
comma
id|h_aggregation
comma
id|h_resource
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buf
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|size
OG
id|LPARCFG_BUFF_SIZE
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
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
)paren
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
id|system_id
op_assign
id|get_property
c_func
(paren
id|root
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
id|root
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
(brace
id|lp_index
op_assign
op_star
id|lp_index_ptr
suffix:semicolon
)brace
)brace
id|n
op_assign
id|scnprintf
c_func
(paren
id|buf
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;serial_number=%s&bslash;n&quot;
comma
id|system_id
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;system_type=%s&bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
id|ip
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
id|ip
op_eq
l_int|NULL
)paren
(brace
id|system_active_processors
op_assign
id|systemcfg-&gt;processorCount
suffix:semicolon
)brace
r_else
(brace
id|system_active_processors
op_assign
op_star
(paren
id|ip
op_plus
l_int|4
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;firmware_features
op_amp
id|FW_FEATURE_SPLPAR
)paren
(brace
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
macro_line|#ifdef DEBUG
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;R4=0x%lx&bslash;n&quot;
comma
id|h_entitled
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;R5=0x%lx&bslash;n&quot;
comma
id|h_unallocated
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;R6=0x%lx&bslash;n&quot;
comma
id|h_aggregation
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;R7=0x%lx&bslash;n&quot;
comma
id|h_resource
)paren
suffix:semicolon
macro_line|#endif /* DEBUG */
)brace
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;firmware_features
op_amp
id|FW_FEATURE_SPLPAR
)paren
(brace
id|system_potential_processors
op_assign
id|get_splpar_potential_characteristics
c_func
(paren
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;system_active_processors=%ld&bslash;n&quot;
comma
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
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;system_potential_processors=%d&bslash;n&quot;
comma
id|system_potential_processors
)paren
suffix:semicolon
)brace
r_else
(brace
id|system_potential_processors
op_assign
id|system_active_processors
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;system_active_processors=%d&bslash;n&quot;
comma
id|system_active_processors
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;system_potential_processors=%d&bslash;n&quot;
comma
id|system_potential_processors
)paren
suffix:semicolon
)brace
id|processors
op_assign
id|systemcfg-&gt;processorCount
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;partition_active_processors=%d&bslash;n&quot;
comma
id|processors
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;partition_potential_processors=%d&bslash;n&quot;
comma
id|system_active_processors
)paren
suffix:semicolon
multiline_comment|/* max_entitled_capacity will come out of get_splpar_potential_characteristics() when that function is complete */
id|max_entitled_capacity
op_assign
id|system_active_processors
op_star
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;firmware_features
op_amp
id|FW_FEATURE_SPLPAR
)paren
(brace
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;partition_entitled_capacity=%ld&bslash;n&quot;
comma
id|h_entitled
)paren
suffix:semicolon
)brace
r_else
(brace
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;partition_entitled_capacity=%d&bslash;n&quot;
comma
id|system_active_processors
op_star
l_int|100
)paren
suffix:semicolon
)brace
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;partition_max_entitled_capacity=%d&bslash;n&quot;
comma
id|max_entitled_capacity
)paren
suffix:semicolon
id|shared
op_assign
l_int|0
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;shared_processor_mode=%d&bslash;n&quot;
comma
id|shared
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
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;pool_capacity=%ld&bslash;n&quot;
comma
(paren
id|h_resource
op_rshift
l_int|3
op_star
l_int|8
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
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
l_int|0x40
)paren
suffix:semicolon
id|n
op_add_assign
id|scnprintf
c_func
(paren
id|buf
op_plus
id|n
comma
id|LPARCFG_BUFF_SIZE
op_minus
id|n
comma
l_string|&quot;capacity_weight=%d&bslash;n&quot;
comma
(paren
r_int
)paren
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
)brace
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
macro_line|#endif /* CONFIG_PPC_PSERIES */
DECL|function|lparcfg_read
r_static
id|ssize_t
id|lparcfg_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_int
r_int
op_star
id|data
op_assign
(paren
r_int
r_int
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_int
r_int
id|p
suffix:semicolon
id|ssize_t
id|read
suffix:semicolon
r_char
op_star
id|pnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;lparcfg: read failed no data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ppos
)paren
(brace
id|p
op_assign
op_star
id|ppos
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
op_ge
id|LPARCFG_BUFF_SIZE
)paren
r_return
l_int|0
suffix:semicolon
id|lparcfg_data
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|data
comma
id|LPARCFG_BUFF_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
(paren
id|strlen
c_func
(paren
(paren
r_char
op_star
)paren
id|data
)paren
op_minus
id|p
)paren
)paren
id|count
op_assign
(paren
id|strlen
c_func
(paren
(paren
r_char
op_star
)paren
id|data
)paren
)paren
op_minus
id|p
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
id|pnt
op_assign
(paren
r_char
op_star
)paren
(paren
id|data
)paren
op_plus
id|p
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
id|pnt
comma
id|count
)paren
suffix:semicolon
id|read
op_add_assign
id|count
suffix:semicolon
op_star
id|ppos
op_add_assign
id|read
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
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
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_int
r_int
op_star
id|data
op_assign
(paren
r_int
r_int
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;lparcfg: open failed no data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|lparcfg_fops
r_struct
id|file_operations
id|lparcfg_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|lparcfg_read
comma
id|open
suffix:colon
id|lparcfg_open
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
