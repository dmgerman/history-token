multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999,2001-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * Module to export the system&squot;s Firmware Interface Tables, including&n; * PROM revision numbers and banners, in /proc&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/nodemask.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PROM version reporting for /proc&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Chad Talbott&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Standard Intel FIT entry types */
DECL|macro|FIT_ENTRY_FIT_HEADER
mdefine_line|#define FIT_ENTRY_FIT_HEADER&t;0x00&t;/* FIT header entry */
DECL|macro|FIT_ENTRY_PAL_B
mdefine_line|#define FIT_ENTRY_PAL_B&t;&t;0x01&t;/* PAL_B entry */
multiline_comment|/* Entries 0x02 through 0x0D reserved by Intel */
DECL|macro|FIT_ENTRY_PAL_A_PROC
mdefine_line|#define FIT_ENTRY_PAL_A_PROC&t;0x0E&t;/* Processor-specific PAL_A entry */
DECL|macro|FIT_ENTRY_PAL_A
mdefine_line|#define FIT_ENTRY_PAL_A&t;&t;0x0F&t;/* PAL_A entry, same as... */
DECL|macro|FIT_ENTRY_PAL_A_GEN
mdefine_line|#define FIT_ENTRY_PAL_A_GEN&t;0x0F&t;/* ...Generic PAL_A entry */
DECL|macro|FIT_ENTRY_UNUSED
mdefine_line|#define FIT_ENTRY_UNUSED&t;0x7F&t;/* Unused (reserved by Intel?) */
multiline_comment|/* OEM-defined entries range from 0x10 to 0x7E. */
DECL|macro|FIT_ENTRY_SAL_A
mdefine_line|#define FIT_ENTRY_SAL_A&t;&t;0x10&t;/* SAL_A entry */
DECL|macro|FIT_ENTRY_SAL_B
mdefine_line|#define FIT_ENTRY_SAL_B&t;&t;0x11&t;/* SAL_B entry */
DECL|macro|FIT_ENTRY_SALRUNTIME
mdefine_line|#define FIT_ENTRY_SALRUNTIME&t;0x12&t;/* SAL runtime entry */
DECL|macro|FIT_ENTRY_EFI
mdefine_line|#define FIT_ENTRY_EFI&t;&t;0x1F&t;/* EFI entry */
DECL|macro|FIT_ENTRY_FPSWA
mdefine_line|#define FIT_ENTRY_FPSWA&t;&t;0x20&t;/* embedded fpswa entry */
DECL|macro|FIT_ENTRY_VMLINUX
mdefine_line|#define FIT_ENTRY_VMLINUX&t;0x21&t;/* embedded vmlinux entry */
DECL|macro|FIT_MAJOR_SHIFT
mdefine_line|#define FIT_MAJOR_SHIFT&t;(32 + 8)
DECL|macro|FIT_MAJOR_MASK
mdefine_line|#define FIT_MAJOR_MASK&t;((1 &lt;&lt; 8) - 1)
DECL|macro|FIT_MINOR_SHIFT
mdefine_line|#define FIT_MINOR_SHIFT&t;32
DECL|macro|FIT_MINOR_MASK
mdefine_line|#define FIT_MINOR_MASK&t;((1 &lt;&lt; 8) - 1)
DECL|macro|FIT_MAJOR
mdefine_line|#define FIT_MAJOR(q)&t;&bslash;&n;&t;((unsigned) ((q) &gt;&gt; FIT_MAJOR_SHIFT) &amp; FIT_MAJOR_MASK)
DECL|macro|FIT_MINOR
mdefine_line|#define FIT_MINOR(q)&t;&bslash;&n;&t;((unsigned) ((q) &gt;&gt; FIT_MINOR_SHIFT) &amp; FIT_MINOR_MASK)
DECL|macro|FIT_TYPE_SHIFT
mdefine_line|#define FIT_TYPE_SHIFT&t;(32 + 16)
DECL|macro|FIT_TYPE_MASK
mdefine_line|#define FIT_TYPE_MASK&t;((1 &lt;&lt; 7) - 1)
DECL|macro|FIT_TYPE
mdefine_line|#define FIT_TYPE(q)&t;&bslash;&n;&t;((unsigned) ((q) &gt;&gt; FIT_TYPE_SHIFT) &amp; FIT_TYPE_MASK)
DECL|struct|fit_type_map_t
r_struct
id|fit_type_map_t
(brace
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|fit_entry_types
r_static
r_const
r_struct
id|fit_type_map_t
id|fit_entry_types
(braket
)braket
op_assign
(brace
(brace
id|FIT_ENTRY_FIT_HEADER
comma
l_string|&quot;FIT Header&quot;
)brace
comma
(brace
id|FIT_ENTRY_PAL_A_GEN
comma
l_string|&quot;Generic PAL_A&quot;
)brace
comma
(brace
id|FIT_ENTRY_PAL_A_PROC
comma
l_string|&quot;Processor-specific PAL_A&quot;
)brace
comma
(brace
id|FIT_ENTRY_PAL_A
comma
l_string|&quot;PAL_A&quot;
)brace
comma
(brace
id|FIT_ENTRY_PAL_B
comma
l_string|&quot;PAL_B&quot;
)brace
comma
(brace
id|FIT_ENTRY_SAL_A
comma
l_string|&quot;SAL_A&quot;
)brace
comma
(brace
id|FIT_ENTRY_SAL_B
comma
l_string|&quot;SAL_B&quot;
)brace
comma
(brace
id|FIT_ENTRY_SALRUNTIME
comma
l_string|&quot;SAL runtime&quot;
)brace
comma
(brace
id|FIT_ENTRY_EFI
comma
l_string|&quot;EFI&quot;
)brace
comma
(brace
id|FIT_ENTRY_VMLINUX
comma
l_string|&quot;Embedded Linux&quot;
)brace
comma
(brace
id|FIT_ENTRY_FPSWA
comma
l_string|&quot;Embedded FPSWA&quot;
)brace
comma
(brace
id|FIT_ENTRY_UNUSED
comma
l_string|&quot;Unused&quot;
)brace
comma
(brace
l_int|0xff
comma
l_string|&quot;Error&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|fit_type_name
r_static
r_const
r_char
op_star
id|fit_type_name
c_func
(paren
r_int
r_char
id|type
)paren
(brace
r_struct
id|fit_type_map_t
r_const
op_star
id|mapp
suffix:semicolon
r_for
c_loop
(paren
id|mapp
op_assign
id|fit_entry_types
suffix:semicolon
id|mapp-&gt;type
op_ne
l_int|0xff
suffix:semicolon
id|mapp
op_increment
)paren
r_if
c_cond
(paren
id|type
op_eq
id|mapp-&gt;type
)paren
r_return
id|mapp-&gt;name
suffix:semicolon
r_if
c_cond
(paren
(paren
id|type
OG
id|FIT_ENTRY_PAL_A
)paren
op_logical_and
(paren
id|type
OL
id|FIT_ENTRY_UNUSED
)paren
)paren
r_return
l_string|&quot;OEM type&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|type
OG
id|FIT_ENTRY_PAL_B
)paren
op_logical_and
(paren
id|type
OL
id|FIT_ENTRY_PAL_A
)paren
)paren
r_return
l_string|&quot;Reserved&quot;
suffix:semicolon
r_return
l_string|&quot;Unknown type&quot;
suffix:semicolon
)brace
r_static
r_int
DECL|function|get_fit_entry
id|get_fit_entry
c_func
(paren
r_int
r_int
id|nasid
comma
r_int
id|index
comma
r_int
r_int
op_star
id|fentry
comma
r_char
op_star
id|banner
comma
r_int
id|banlen
)paren
(brace
r_return
id|ia64_sn_get_fit_compt
c_func
(paren
id|nasid
comma
id|index
comma
id|fentry
comma
id|banner
comma
id|banlen
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These two routines display the FIT table for each node.&n; */
DECL|function|dump_fit_entry
r_static
r_int
id|dump_fit_entry
c_func
(paren
r_char
op_star
id|page
comma
r_int
r_int
op_star
id|fentry
)paren
(brace
r_int
id|type
suffix:semicolon
id|type
op_assign
id|FIT_TYPE
c_func
(paren
id|fentry
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%02x %-25s %x.%02x %016lx %u&bslash;n&quot;
comma
id|type
comma
id|fit_type_name
c_func
(paren
id|type
)paren
comma
id|FIT_MAJOR
c_func
(paren
id|fentry
(braket
l_int|1
)braket
)paren
comma
id|FIT_MINOR
c_func
(paren
id|fentry
(braket
l_int|1
)braket
)paren
comma
id|fentry
(braket
l_int|0
)braket
comma
multiline_comment|/* mult by sixteen to get size in bytes */
(paren
r_int
)paren
(paren
id|fentry
(braket
l_int|1
)braket
op_amp
l_int|0xffffff
)paren
op_star
l_int|16
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We assume that the fit table will be small enough that we can print&n; * the whole thing into one page.  (This is true for our default 16kB&n; * pages -- each entry is about 60 chars wide when printed.)  I read&n; * somewhere that the maximum size of the FIT is 128 entries, so we&squot;re&n; * OK except for 4kB pages (and no one is going to do that on SN&n; * anyway).&n; */
r_static
r_int
DECL|function|dump_fit
id|dump_fit
c_func
(paren
r_char
op_star
id|page
comma
r_int
r_int
id|nasid
)paren
(brace
r_int
r_int
id|fentry
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|index
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
id|p
op_assign
id|page
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|index
op_increment
)paren
(brace
id|BUG_ON
c_func
(paren
id|index
op_star
l_int|60
OG
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_fit_entry
c_func
(paren
id|nasid
comma
id|index
comma
id|fentry
comma
l_int|NULL
comma
l_int|0
)paren
)paren
r_break
suffix:semicolon
id|p
op_add_assign
id|dump_fit_entry
c_func
(paren
id|p
comma
id|fentry
)paren
suffix:semicolon
)brace
r_return
id|p
op_minus
id|page
suffix:semicolon
)brace
r_static
r_int
DECL|function|dump_version
id|dump_version
c_func
(paren
r_char
op_star
id|page
comma
r_int
r_int
id|nasid
)paren
(brace
r_int
r_int
id|fentry
(braket
l_int|2
)braket
suffix:semicolon
r_char
id|banner
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|index
suffix:semicolon
r_int
id|len
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|index
op_increment
)paren
(brace
r_if
c_cond
(paren
id|get_fit_entry
c_func
(paren
id|nasid
comma
id|index
comma
id|fentry
comma
id|banner
comma
r_sizeof
(paren
id|banner
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|FIT_TYPE
c_func
(paren
id|fentry
(braket
l_int|1
)braket
)paren
op_eq
id|FIT_ENTRY_SAL_A
)paren
r_break
suffix:semicolon
)brace
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%x.%02x&bslash;n&quot;
comma
id|FIT_MAJOR
c_func
(paren
id|fentry
(braket
l_int|1
)braket
)paren
comma
id|FIT_MINOR
c_func
(paren
id|fentry
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|page
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|banner
(braket
l_int|0
)braket
)paren
id|len
op_add_assign
id|snprintf
c_func
(paren
id|page
comma
id|PAGE_SIZE
op_minus
id|len
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|banner
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* same as in proc_misc.c */
r_static
r_int
DECL|function|proc_calc_metrics
id|proc_calc_metrics
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_le
id|off
op_plus
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
DECL|function|read_version_entry
id|read_version_entry
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* data holds the NASID of the node */
id|len
op_assign
id|dump_version
c_func
(paren
id|page
comma
(paren
r_int
r_int
)paren
id|data
)paren
suffix:semicolon
id|len
op_assign
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
DECL|function|read_fit_entry
id|read_fit_entry
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* data holds the NASID of the node */
id|len
op_assign
id|dump_fit
c_func
(paren
id|page
comma
(paren
r_int
r_int
)paren
id|data
)paren
suffix:semicolon
id|len
op_assign
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* module entry points */
r_int
id|__init
id|prominfo_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|__exit
id|prominfo_exit
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|prominfo_init
id|module_init
c_func
(paren
id|prominfo_init
)paren
suffix:semicolon
DECL|variable|prominfo_exit
id|module_exit
c_func
(paren
id|prominfo_exit
)paren
suffix:semicolon
DECL|variable|proc_entries
r_static
r_struct
id|proc_dir_entry
op_star
op_star
id|proc_entries
suffix:semicolon
DECL|variable|sgi_prominfo_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|sgi_prominfo_entry
suffix:semicolon
DECL|macro|NODE_NAME_LEN
mdefine_line|#define NODE_NAME_LEN 11
DECL|function|prominfo_init
r_int
id|__init
id|prominfo_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
op_star
id|entp
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
id|cnodeid_t
id|cnodeid
suffix:semicolon
r_int
r_int
id|nasid
suffix:semicolon
r_char
id|name
(braket
id|NODE_NAME_LEN
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ia64_platform_is
c_func
(paren
l_string|&quot;sn2&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|proc_entries
op_assign
id|kmalloc
c_func
(paren
id|num_online_nodes
c_func
(paren
)paren
op_star
r_sizeof
(paren
r_struct
id|proc_dir_entry
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|sgi_prominfo_entry
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;sgi_prominfo&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|entp
op_assign
id|proc_entries
suffix:semicolon
id|for_each_online_node
c_func
(paren
id|cnodeid
)paren
(brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;node%d&quot;
comma
id|cnodeid
)paren
suffix:semicolon
op_star
id|entp
op_assign
id|proc_mkdir
c_func
(paren
id|name
comma
id|sgi_prominfo_entry
)paren
suffix:semicolon
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnodeid
)paren
suffix:semicolon
id|p
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;fit&quot;
comma
l_int|0
comma
op_star
id|entp
comma
id|read_fit_entry
comma
(paren
r_void
op_star
)paren
id|nasid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|p-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|p
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;version&quot;
comma
l_int|0
comma
op_star
id|entp
comma
id|read_version_entry
comma
(paren
r_void
op_star
)paren
id|nasid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|p-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|entp
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prominfo_exit
r_void
id|__exit
id|prominfo_exit
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
op_star
id|entp
suffix:semicolon
r_int
id|cnodeid
suffix:semicolon
r_char
id|name
(braket
id|NODE_NAME_LEN
)braket
suffix:semicolon
id|entp
op_assign
id|proc_entries
suffix:semicolon
id|for_each_online_node
c_func
(paren
id|cnodeid
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;fit&quot;
comma
op_star
id|entp
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;version&quot;
comma
op_star
id|entp
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;node%d&quot;
comma
id|cnodeid
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|name
comma
id|sgi_prominfo_entry
)paren
suffix:semicolon
id|entp
op_increment
suffix:semicolon
)brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;sgi_prominfo&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|proc_entries
)paren
suffix:semicolon
)brace
eof
