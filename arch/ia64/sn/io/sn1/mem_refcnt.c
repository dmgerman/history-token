multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/hcl_util.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/sn1/mem_refcnt.h&gt;
macro_line|#include &lt;asm/sn/sn1/hwcntrs.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubspc.h&gt;
singleline_comment|// From numa_hw.h
DECL|macro|MIGR_COUNTER_MAX_GET
mdefine_line|#define MIGR_COUNTER_MAX_GET(nodeid) &bslash;&n;        (NODEPDA_MCD((nodeid))-&gt;migr_system_kparms.migr_threshold_reference)
multiline_comment|/*&n; * Get the Absolute Theshold&n; */
DECL|macro|MIGR_THRESHOLD_ABS_GET
mdefine_line|#define MIGR_THRESHOLD_ABS_GET(nodeid) ( &bslash;&n;        MD_MIG_VALUE_THRESH_GET(COMPACT_TO_NASID_NODEID(nodeid)))
multiline_comment|/*&n; * Get the current Differential Threshold&n; */
DECL|macro|MIGR_THRESHOLD_DIFF_GET
mdefine_line|#define MIGR_THRESHOLD_DIFF_GET(nodeid) &bslash;&n;        (NODEPDA_MCD(nodeid)-&gt;migr_as_kparms.migr_base_threshold)
DECL|macro|NUM_OF_HW_PAGES_PER_SW_PAGE
mdefine_line|#define NUM_OF_HW_PAGES_PER_SW_PAGE()   (NBPP / MD_PAGE_SIZE)
singleline_comment|// #include &quot;migr_control.h&quot;
r_int
DECL|function|mem_refcnt_attach
id|mem_refcnt_attach
c_func
(paren
id|devfs_handle_t
id|hub
)paren
(brace
macro_line|#ifndef CONFIG_IA64_SGI_SN
id|devfs_handle_t
id|refcnt_dev
suffix:semicolon
id|hwgraph_char_device_add
c_func
(paren
id|hub
comma
l_string|&quot;refcnt&quot;
comma
l_string|&quot;hubspc_&quot;
comma
op_amp
id|refcnt_dev
)paren
suffix:semicolon
id|device_info_set
c_func
(paren
id|refcnt_dev
comma
(paren
r_void
op_star
)paren
(paren
id|ulong
)paren
id|HUBSPC_REFCOUNTERS
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|mem_refcnt_open
id|mem_refcnt_open
c_func
(paren
id|devfs_handle_t
op_star
id|devp
comma
id|mode_t
id|oflag
comma
r_int
id|otyp
comma
id|cred_t
op_star
id|crp
)paren
(brace
id|cnodeid_t
id|node
suffix:semicolon
id|node
op_assign
id|master_node_get
c_func
(paren
op_star
id|devp
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
id|node
op_ge
l_int|0
)paren
op_logical_and
(paren
id|node
OL
id|numnodes
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_counterbuffer
op_eq
l_int|NULL
)paren
(brace
r_return
(paren
id|ENODEV
)paren
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_counterbase
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_cbsize
op_ne
(paren
r_int
)paren
l_int|0
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|mem_refcnt_close
id|mem_refcnt_close
c_func
(paren
id|devfs_handle_t
id|dev
comma
r_int
id|oflag
comma
r_int
id|otyp
comma
id|cred_t
op_star
id|crp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|mem_refcnt_mmap
id|mem_refcnt_mmap
c_func
(paren
id|devfs_handle_t
id|dev
comma
id|vhandl_t
op_star
id|vt
comma
id|off_t
id|off
comma
r_int
id|len
comma
id|uint
id|prot
)paren
(brace
id|cnodeid_t
id|node
suffix:semicolon
r_int
id|errcode
suffix:semicolon
r_char
op_star
id|buffer
suffix:semicolon
r_int
id|blen
suffix:semicolon
id|node
op_assign
id|master_node_get
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
id|node
op_ge
l_int|0
)paren
op_logical_and
(paren
id|node
OL
id|numnodes
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_counterbuffer
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_counterbase
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_cbsize
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;         * XXXX deal with prot&squot;s somewhere around here....&n;         */
id|buffer
op_assign
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_counterbuffer
suffix:semicolon
id|blen
op_assign
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_cbsize
suffix:semicolon
multiline_comment|/*&n;         * Force offset to be a multiple of sizeof(refcnt_t)&n;         * We round up.&n;         */
id|off
op_assign
(paren
(paren
(paren
id|off
op_minus
l_int|1
)paren
op_div
r_sizeof
(paren
id|refcnt_t
)paren
)paren
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
id|refcnt_t
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|buffer
op_plus
id|blen
)paren
op_minus
(paren
id|buffer
op_plus
id|off
op_plus
id|len
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
(paren
id|EPERM
)paren
suffix:semicolon
)brace
id|errcode
op_assign
id|v_mapphys
c_func
(paren
id|vt
comma
id|buffer
op_plus
id|off
comma
id|len
)paren
suffix:semicolon
r_return
id|errcode
suffix:semicolon
)brace
multiline_comment|/*ARGSUSED*/
r_int
DECL|function|mem_refcnt_unmap
id|mem_refcnt_unmap
c_func
(paren
id|devfs_handle_t
id|dev
comma
id|vhandl_t
op_star
id|vt
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ARGSUSED */
r_int
DECL|function|mem_refcnt_ioctl
id|mem_refcnt_ioctl
c_func
(paren
id|devfs_handle_t
id|dev
comma
r_int
id|cmd
comma
r_void
op_star
id|arg
comma
r_int
id|mode
comma
id|cred_t
op_star
id|cred_p
comma
r_int
op_star
id|rvalp
)paren
(brace
id|cnodeid_t
id|node
suffix:semicolon
r_int
id|errcode
suffix:semicolon
r_extern
r_int
id|numnodes
suffix:semicolon
id|node
op_assign
id|master_node_get
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
id|node
op_ge
l_int|0
)paren
op_logical_and
(paren
id|node
OL
id|numnodes
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_counterbuffer
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_counterbase
op_ne
l_int|NULL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_cbsize
op_ne
l_int|0
)paren
suffix:semicolon
id|errcode
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RCB_INFO_GET
suffix:colon
(brace
id|rcb_info_t
id|rcb
suffix:semicolon
id|rcb.rcb_len
op_assign
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_cbsize
suffix:semicolon
id|rcb.rcb_sw_sets
op_assign
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_numsets
suffix:semicolon
id|rcb.rcb_sw_counters_per_set
op_assign
id|numnodes
suffix:semicolon
id|rcb.rcb_sw_counter_size
op_assign
r_sizeof
(paren
id|refcnt_t
)paren
suffix:semicolon
id|rcb.rcb_base_pages
op_assign
id|NODEPDA
c_func
(paren
id|node
)paren
op_member_access_from_pointer
id|migr_refcnt_numsets
op_div
id|NUM_OF_HW_PAGES_PER_SW_PAGE
c_func
(paren
)paren
suffix:semicolon
id|rcb.rcb_base_page_size
op_assign
id|NBPP
suffix:semicolon
id|rcb.rcb_base_paddr
op_assign
id|ctob
c_func
(paren
id|slot_getbasepfn
c_func
(paren
id|node
comma
l_int|0
)paren
)paren
suffix:semicolon
id|rcb.rcb_cnodeid
op_assign
id|node
suffix:semicolon
id|rcb.rcb_granularity
op_assign
id|MD_PAGE_SIZE
suffix:semicolon
macro_line|#ifdef LATER
id|rcb.rcb_hw_counter_max
op_assign
id|MIGR_COUNTER_MAX_GET
c_func
(paren
id|node
)paren
suffix:semicolon
id|rcb.rcb_diff_threshold
op_assign
id|MIGR_THRESHOLD_DIFF_GET
c_func
(paren
id|node
)paren
suffix:semicolon
macro_line|#endif
id|rcb.rcb_abs_threshold
op_assign
id|MIGR_THRESHOLD_ABS_GET
c_func
(paren
id|node
)paren
suffix:semicolon
id|rcb.rcb_num_slots
op_assign
id|MAX_MEM_SLOTS
suffix:semicolon
r_if
c_cond
(paren
id|COPYOUT
c_func
(paren
op_amp
id|rcb
comma
id|arg
comma
r_sizeof
(paren
id|rcb_info_t
)paren
)paren
)paren
(brace
id|errcode
op_assign
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|RCB_SLOT_GET
suffix:colon
(brace
id|rcb_slot_t
id|slot
(braket
id|MAX_MEM_SLOTS
)braket
suffix:semicolon
r_int
id|s
suffix:semicolon
r_int
id|nslots
suffix:semicolon
id|nslots
op_assign
id|MAX_MEM_SLOTS
suffix:semicolon
id|ASSERT
c_func
(paren
id|nslots
op_le
id|MAX_MEM_SLOTS
)paren
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
id|nslots
suffix:semicolon
id|s
op_increment
)paren
(brace
id|slot
(braket
id|s
)braket
dot
id|base
op_assign
(paren
r_uint64
)paren
id|ctob
c_func
(paren
id|slot_getbasepfn
c_func
(paren
id|node
comma
id|s
)paren
)paren
suffix:semicolon
macro_line|#ifdef LATER
id|slot
(braket
id|s
)braket
dot
id|size
op_assign
(paren
r_uint64
)paren
id|ctob
c_func
(paren
id|slot_getsize
c_func
(paren
id|node
comma
id|s
)paren
)paren
suffix:semicolon
macro_line|#else
id|slot
(braket
id|s
)braket
dot
id|size
op_assign
(paren
r_uint64
)paren
l_int|1
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|COPYOUT
c_func
(paren
op_amp
id|slot
(braket
l_int|0
)braket
comma
id|arg
comma
id|nslots
op_star
r_sizeof
(paren
id|rcb_slot_t
)paren
)paren
)paren
(brace
id|errcode
op_assign
id|EFAULT
suffix:semicolon
)brace
op_star
id|rvalp
op_assign
id|nslots
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|errcode
op_assign
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|errcode
suffix:semicolon
)brace
eof