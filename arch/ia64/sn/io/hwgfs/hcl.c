multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; *  hcl - SGI&squot;s Hardware Graph compatibility layer.&n; *&n; * Copyright (C) 1992-1997,2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;                /* needed for smp_lock.h :( */
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/hwgfs.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/simulator.h&gt;
DECL|macro|HCL_NAME
mdefine_line|#define HCL_NAME &quot;SGI-HWGRAPH COMPATIBILITY DRIVER&quot;
DECL|macro|HCL_TEMP_NAME
mdefine_line|#define HCL_TEMP_NAME &quot;HCL_TEMP_NAME_USED_FOR_HWGRAPH_VERTEX_CREATE&quot;
DECL|macro|HCL_TEMP_NAME_LEN
mdefine_line|#define HCL_TEMP_NAME_LEN 44 
DECL|macro|HCL_VERSION
mdefine_line|#define HCL_VERSION &quot;1.0&quot;
DECL|macro|vertex_hdl_t
mdefine_line|#define vertex_hdl_t hwgfs_handle_t
DECL|variable|hwgraph_root
id|vertex_hdl_t
id|hwgraph_root
suffix:semicolon
DECL|variable|linux_busnum
id|vertex_hdl_t
id|linux_busnum
suffix:semicolon
r_extern
r_void
id|pci_bus_cvlink_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Debug flag definition.&n; */
DECL|macro|OPTION_NONE
mdefine_line|#define OPTION_NONE             0x00
DECL|macro|HCL_DEBUG_NONE
mdefine_line|#define HCL_DEBUG_NONE 0x00000
DECL|macro|HCL_DEBUG_ALL
mdefine_line|#define HCL_DEBUG_ALL  0x0ffff
macro_line|#if defined(CONFIG_HCL_DEBUG)
DECL|variable|__initdata
r_static
r_int
r_int
id|hcl_debug_init
id|__initdata
op_assign
id|HCL_DEBUG_NONE
suffix:semicolon
macro_line|#endif
DECL|variable|hcl_debug
r_static
r_int
r_int
id|hcl_debug
op_assign
id|HCL_DEBUG_NONE
suffix:semicolon
macro_line|#if defined(CONFIG_HCL_DEBUG) &amp;&amp; !defined(MODULE)
DECL|variable|boot_options
r_static
r_int
r_int
id|boot_options
op_assign
id|OPTION_NONE
suffix:semicolon
macro_line|#endif
DECL|variable|invplace_none
id|invplace_t
id|invplace_none
op_assign
(brace
id|GRAPH_VERTEX_NONE
comma
id|GRAPH_VERTEX_PLACE_NONE
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; * init_hcl() - Boot time initialization.&n; *&n; */
DECL|function|init_hcl
r_int
id|__init
id|init_hcl
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|string_table_init
c_func
(paren
r_struct
id|string_table
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|string_table
id|label_string_table
suffix:semicolon
r_extern
r_int
id|init_ioconfig_bus
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_hwgfs_fs
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|rv
op_assign
l_int|0
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
r_extern
id|u64
id|klgraph_addr
(braket
)braket
suffix:semicolon
id|klgraph_addr
(braket
l_int|0
)braket
op_assign
l_int|0xe000003000030000
suffix:semicolon
)brace
id|init_hwgfs_fs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create the hwgraph_root.&n;&t; */
id|rv
op_assign
id|hwgraph_path_add
c_func
(paren
l_int|NULL
comma
id|EDGE_LBL_HW
comma
op_amp
id|hwgraph_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;init_hcl: Failed to create hwgraph_root.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Initialize the HCL string table.&n;&t; */
id|string_table_init
c_func
(paren
op_amp
id|label_string_table
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create the directory that links Linux bus numbers to our Xwidget.&n;&t; */
id|rv
op_assign
id|hwgraph_path_add
c_func
(paren
id|hwgraph_root
comma
id|EDGE_LBL_LINUX_BUS
comma
op_amp
id|linux_busnum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|linux_busnum
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HCL: Unable to create %s&bslash;n&quot;
comma
id|EDGE_LBL_LINUX_BUS
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|pci_bus_cvlink_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the ifconfgi_net driver that does network devices &n;&t; * Persistent Naming.&n;&t; */
id|init_ioconfig_bus
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hcl_setup() - Process boot time parameters if given.&n; *&t;&quot;hcl=&quot;&n; *&t;This routine gets called only if &quot;hcl=&quot; is given in the &n; *&t;boot line and before init_hcl().&n; *&n; *&t;We currently do not have any boot options .. when we do, &n; *&t;functionalities can be added here.&n; *&n; */
DECL|function|hcl_setup
r_static
r_int
id|__init
id|hcl_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_while
c_loop
(paren
(paren
op_star
id|str
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_logical_and
op_logical_neg
id|isspace
(paren
op_star
id|str
)paren
)paren
(brace
macro_line|#ifdef CONFIG_HCL_DEBUG
r_if
c_cond
(paren
id|strncmp
(paren
id|str
comma
l_string|&quot;all&quot;
comma
l_int|3
)paren
op_eq
l_int|0
)paren
(brace
id|hcl_debug_init
op_or_assign
id|HCL_DEBUG_ALL
suffix:semicolon
id|str
op_add_assign
l_int|3
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_star
id|str
op_ne
l_char|&squot;,&squot;
)paren
r_return
l_int|0
suffix:semicolon
op_increment
id|str
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;hcl=&quot;
comma
id|hcl_setup
)paren
suffix:semicolon
multiline_comment|/*&n; * Set device specific &quot;fast information&quot;.&n; *&n; */
r_void
DECL|function|hwgraph_fastinfo_set
id|hwgraph_fastinfo_set
c_func
(paren
id|vertex_hdl_t
id|de
comma
id|arbitrary_info_t
id|fastinfo
)paren
(brace
id|labelcl_info_replace_IDX
c_func
(paren
id|de
comma
id|HWGRAPH_FASTINFO
comma
id|fastinfo
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get device specific &quot;fast information&quot;.&n; *&n; */
id|arbitrary_info_t
DECL|function|hwgraph_fastinfo_get
id|hwgraph_fastinfo_get
c_func
(paren
id|vertex_hdl_t
id|de
)paren
(brace
id|arbitrary_info_t
id|fastinfo
suffix:semicolon
r_int
id|rv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HCL: hwgraph_fastinfo_get handle given is NULL.&bslash;n&quot;
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rv
op_assign
id|labelcl_info_get_IDX
c_func
(paren
id|de
comma
id|HWGRAPH_FASTINFO
comma
op_amp
id|fastinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_eq
l_int|0
)paren
r_return
id|fastinfo
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_connectpt_set - Sets the connect point handle in de to the &n; *&t;given connect_de handle.  By default, the connect point of the &n; *&t;node is the parent.  This effectively changes this assumption.&n; */
r_int
DECL|function|hwgraph_connectpt_set
id|hwgraph_connectpt_set
c_func
(paren
id|vertex_hdl_t
id|de
comma
id|vertex_hdl_t
id|connect_de
)paren
(brace
r_int
id|rv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|rv
op_assign
id|labelcl_info_connectpt_set
c_func
(paren
id|de
comma
id|connect_de
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_connectpt_get: Returns the entry&squot;s connect point.&n; *&n; */
id|vertex_hdl_t
DECL|function|hwgraph_connectpt_get
id|hwgraph_connectpt_get
c_func
(paren
id|vertex_hdl_t
id|de
)paren
(brace
r_int
id|rv
suffix:semicolon
id|arbitrary_info_t
id|info
suffix:semicolon
id|vertex_hdl_t
id|connect
suffix:semicolon
id|rv
op_assign
id|labelcl_info_get_IDX
c_func
(paren
id|de
comma
id|HWGRAPH_CONNECTPT
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_ne
l_int|0
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|connect
op_assign
(paren
id|vertex_hdl_t
)paren
id|info
suffix:semicolon
r_return
id|connect
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_mk_dir - Creates a directory entry.&n; */
id|vertex_hdl_t
DECL|function|hwgraph_mk_dir
id|hwgraph_mk_dir
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|namelen
comma
r_void
op_star
id|info
)paren
(brace
r_int
id|rv
suffix:semicolon
id|labelcl_info_t
op_star
id|labelcl_info
op_assign
l_int|NULL
suffix:semicolon
id|vertex_hdl_t
id|new_handle
op_assign
l_int|NULL
suffix:semicolon
id|vertex_hdl_t
id|parent
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Create the device info structure for hwgraph compatiblity support.&n;&t; */
id|labelcl_info
op_assign
id|labelcl_info_create
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|labelcl_info
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Create an entry.&n;&t; */
id|new_handle
op_assign
id|hwgfs_mk_dir
c_func
(paren
id|de
comma
id|name
comma
(paren
r_void
op_star
)paren
id|labelcl_info
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_handle
)paren
(brace
id|labelcl_info_destroy
c_func
(paren
id|labelcl_info
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get the parent handle.&n;&t; */
id|parent
op_assign
id|hwgfs_get_parent
(paren
id|new_handle
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * To provide the same semantics as the hwgraph, set the connect point.&n;&t; */
id|rv
op_assign
id|hwgraph_connectpt_set
c_func
(paren
id|new_handle
comma
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rv
)paren
(brace
multiline_comment|/*&n;&t;&t; * We need to clean up!&n;&t;&t; */
)brace
multiline_comment|/*&n;&t; * If the caller provides a private data pointer, save it in the &n;&t; * labelcl info structure(fastinfo).  This can be retrieved via&n;&t; * hwgraph_fastinfo_get()&n;&t; */
r_if
c_cond
(paren
id|info
)paren
id|hwgraph_fastinfo_set
c_func
(paren
id|new_handle
comma
(paren
id|arbitrary_info_t
)paren
id|info
)paren
suffix:semicolon
r_return
id|new_handle
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_path_add - Create a directory node with the given path starting &n; * from the given fromv.&n; */
r_int
DECL|function|hwgraph_path_add
id|hwgraph_path_add
c_func
(paren
id|vertex_hdl_t
id|fromv
comma
r_char
op_star
id|path
comma
id|vertex_hdl_t
op_star
id|new_de
)paren
(brace
r_int
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_int
id|rv
suffix:semicolon
multiline_comment|/*&n;&t; * We need to handle the case when fromv is NULL ..&n;&t; * in this case we need to create the path from the &n;&t; * hwgraph root!&n;&t; */
r_if
c_cond
(paren
id|fromv
op_eq
l_int|NULL
)paren
id|fromv
op_assign
id|hwgraph_root
suffix:semicolon
multiline_comment|/*&n;&t; * check the entry doesn&squot;t already exist, if it does&n;&t; * then we simply want new_de to point to it (otherwise&n;&t; * we&squot;ll overwrite the existing labelcl_info struct)&n;&t; */
id|rv
op_assign
id|hwgraph_edge_get
c_func
(paren
id|fromv
comma
id|path
comma
id|new_de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
(brace
multiline_comment|/* couldn&squot;t find entry so we create it */
op_star
id|new_de
op_assign
id|hwgraph_mk_dir
c_func
(paren
id|fromv
comma
id|path
comma
id|namelen
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_de
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_register  - Creates a special device file.&n; *&n; */
id|vertex_hdl_t
DECL|function|hwgraph_register
id|hwgraph_register
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|namelen
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|major
comma
r_int
r_int
id|minor
comma
id|umode_t
id|mode
comma
id|uid_t
id|uid
comma
id|gid_t
id|gid
comma
r_struct
id|file_operations
op_star
id|fops
comma
r_void
op_star
id|info
)paren
(brace
id|vertex_hdl_t
id|new_handle
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;         * Create an entry.&n;         */
id|new_handle
op_assign
id|hwgfs_register
c_func
(paren
id|de
comma
id|name
comma
id|flags
comma
id|major
comma
id|minor
comma
id|mode
comma
id|fops
comma
id|info
)paren
suffix:semicolon
r_return
id|new_handle
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_mk_symlink - Create a symbolic link.&n; */
r_int
DECL|function|hwgraph_mk_symlink
id|hwgraph_mk_symlink
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|namelen
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|link
comma
r_int
r_int
id|linklen
comma
id|vertex_hdl_t
op_star
id|handle
comma
r_void
op_star
id|info
)paren
(brace
r_void
op_star
id|labelcl_info
op_assign
l_int|NULL
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
id|vertex_hdl_t
id|new_handle
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Create the labelcl info structure for hwgraph compatiblity support.&n;&t; */
id|labelcl_info
op_assign
id|labelcl_info_create
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|labelcl_info
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Create a symbolic link.&n;&t; */
id|status
op_assign
id|hwgfs_mk_symlink
c_func
(paren
id|de
comma
id|name
comma
id|flags
comma
id|link
comma
op_amp
id|new_handle
comma
id|labelcl_info
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|new_handle
)paren
op_logical_or
(paren
op_logical_neg
id|status
)paren
)paren
(brace
id|labelcl_info_destroy
c_func
(paren
(paren
id|labelcl_info_t
op_star
)paren
id|labelcl_info
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the caller provides a private data pointer, save it in the &n;&t; * labelcl info structure(fastinfo).  This can be retrieved via&n;&t; * hwgraph_fastinfo_get()&n;&t; */
r_if
c_cond
(paren
id|info
)paren
id|hwgraph_fastinfo_set
c_func
(paren
id|new_handle
comma
(paren
id|arbitrary_info_t
)paren
id|info
)paren
suffix:semicolon
op_star
id|handle
op_assign
id|new_handle
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_vertex_destroy - Destroy the entry&n; */
r_int
DECL|function|hwgraph_vertex_destroy
id|hwgraph_vertex_destroy
c_func
(paren
id|vertex_hdl_t
id|de
)paren
(brace
r_void
op_star
id|labelcl_info
op_assign
l_int|NULL
suffix:semicolon
id|labelcl_info
op_assign
id|hwgfs_get_info
c_func
(paren
id|de
)paren
suffix:semicolon
id|hwgfs_unregister
c_func
(paren
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
id|labelcl_info
)paren
id|labelcl_info_destroy
c_func
(paren
(paren
id|labelcl_info_t
op_star
)paren
id|labelcl_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/*&n; * hwgraph_edge_add - This routines has changed from the original conext.&n; * All it does now is to create a symbolic link from &quot;from&quot; to &quot;to&quot;.&n; */
multiline_comment|/* ARGSUSED */
r_int
id|hwgraph_edge_add
c_func
(paren
id|vertex_hdl_t
id|from
comma
id|vertex_hdl_t
id|to
comma
r_char
op_star
id|name
)paren
(brace
r_char
op_star
id|path
comma
op_star
id|link
suffix:semicolon
id|vertex_hdl_t
id|handle
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rv
comma
id|i
suffix:semicolon
id|handle
op_assign
id|hwgfs_find_handle
c_func
(paren
id|from
comma
id|name
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|handle
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|path
op_assign
id|kmalloc
c_func
(paren
l_int|1024
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|path
comma
l_int|0x0
comma
l_int|1024
)paren
suffix:semicolon
id|link
op_assign
id|kmalloc
c_func
(paren
l_int|1024
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|path
comma
l_int|0x0
comma
l_int|1024
)paren
suffix:semicolon
id|i
op_assign
id|hwgfs_generate_path
(paren
id|to
comma
id|link
comma
l_int|1024
)paren
suffix:semicolon
id|rv
op_assign
id|hwgfs_mk_symlink
(paren
id|from
comma
(paren
r_const
r_char
op_star
)paren
id|name
comma
id|DEVFS_FL_DEFAULT
comma
id|link
comma
op_amp
id|handle
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_int
DECL|function|hwgraph_edge_add
id|hwgraph_edge_add
c_func
(paren
id|vertex_hdl_t
id|from
comma
id|vertex_hdl_t
id|to
comma
r_char
op_star
id|name
)paren
(brace
r_char
op_star
id|path
comma
op_star
id|link
suffix:semicolon
r_char
op_star
id|s1
suffix:semicolon
r_char
op_star
id|index
suffix:semicolon
id|vertex_hdl_t
id|handle
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rv
suffix:semicolon
r_int
id|i
comma
id|count
suffix:semicolon
id|path
op_assign
id|kmalloc
c_func
(paren
l_int|1024
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|path
comma
l_int|0x0
comma
l_int|1024
)paren
suffix:semicolon
id|link
op_assign
id|kmalloc
c_func
(paren
l_int|1024
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|link
comma
l_int|0x0
comma
l_int|1024
)paren
suffix:semicolon
id|i
op_assign
id|hwgfs_generate_path
(paren
id|from
comma
id|path
comma
l_int|1024
)paren
suffix:semicolon
id|s1
op_assign
(paren
r_char
op_star
)paren
id|path
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|index
op_assign
id|strstr
(paren
id|s1
comma
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
)paren
(brace
id|count
op_increment
suffix:semicolon
id|s1
op_assign
op_increment
id|index
suffix:semicolon
)brace
r_else
(brace
id|count
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|strcat
c_func
(paren
(paren
r_char
op_star
)paren
id|link
comma
l_string|&quot;../&quot;
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|path
comma
l_int|0x0
comma
l_int|1024
)paren
suffix:semicolon
id|i
op_assign
id|hwgfs_generate_path
(paren
id|to
comma
id|path
comma
l_int|1024
)paren
suffix:semicolon
id|strcat
c_func
(paren
(paren
r_char
op_star
)paren
id|link
comma
(paren
r_char
op_star
)paren
id|path
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Otherwise, just create a symlink to the vertex.&n;&t; * In this case the vertex was previous created with a REAL pathname.&n;&t; */
id|rv
op_assign
id|hwgfs_mk_symlink
(paren
id|from
comma
(paren
r_const
r_char
op_star
)paren
id|name
comma
l_int|0
comma
id|link
comma
op_amp
id|handle
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|path
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
multiline_comment|/* ARGSUSED */
r_int
DECL|function|hwgraph_edge_get
id|hwgraph_edge_get
c_func
(paren
id|vertex_hdl_t
id|from
comma
r_char
op_star
id|name
comma
id|vertex_hdl_t
op_star
id|toptr
)paren
(brace
id|vertex_hdl_t
id|target_handle
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|name
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|toptr
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * If the name is &quot;.&quot; just return the current entry handle.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
id|HWGRAPH_EDGELBL_DOT
)paren
)paren
(brace
r_if
c_cond
(paren
id|toptr
)paren
(brace
op_star
id|toptr
op_assign
id|from
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
id|HWGRAPH_EDGELBL_DOTDOT
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Hmmm .. should we return the connect point or parent ..&n;&t;&t; * see in hwgraph, the concept of parent is the connectpt!&n;&t;&t; *&n;&t;&t; * Maybe we should see whether the connectpt is set .. if &n;&t;&t; * not just return the parent!&n;&t;&t; */
id|target_handle
op_assign
id|hwgraph_connectpt_get
c_func
(paren
id|from
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_handle
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Just return the connect point.&n;&t;&t;&t; */
op_star
id|toptr
op_assign
id|target_handle
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|target_handle
op_assign
id|hwgfs_get_parent
c_func
(paren
id|from
)paren
suffix:semicolon
op_star
id|toptr
op_assign
id|target_handle
suffix:semicolon
)brace
r_else
(brace
id|target_handle
op_assign
id|hwgfs_find_handle
(paren
id|from
comma
id|name
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Yes traverse symbolic links */
)brace
r_if
c_cond
(paren
id|target_handle
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
op_star
id|toptr
op_assign
id|target_handle
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_info_add_LBL - Adds a new label for the device.  Mark the info_desc&n; *&t;of the label as INFO_DESC_PRIVATE and store the info in the label.&n; */
multiline_comment|/* ARGSUSED */
r_int
DECL|function|hwgraph_info_add_LBL
id|hwgraph_info_add_LBL
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_char
op_star
id|name
comma
id|arbitrary_info_t
id|info
)paren
(brace
r_return
id|labelcl_info_add_LBL
c_func
(paren
id|de
comma
id|name
comma
id|INFO_DESC_PRIVATE
comma
id|info
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_info_remove_LBL - Remove the label entry for the device.&n; */
multiline_comment|/* ARGSUSED */
r_int
DECL|function|hwgraph_info_remove_LBL
id|hwgraph_info_remove_LBL
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_char
op_star
id|name
comma
id|arbitrary_info_t
op_star
id|old_info
)paren
(brace
r_return
id|labelcl_info_remove_LBL
c_func
(paren
id|de
comma
id|name
comma
l_int|NULL
comma
id|old_info
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_info_replace_LBL - replaces an existing label with &n; *&t;a new label info value.&n; */
multiline_comment|/* ARGSUSED */
r_int
DECL|function|hwgraph_info_replace_LBL
id|hwgraph_info_replace_LBL
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_char
op_star
id|name
comma
id|arbitrary_info_t
id|info
comma
id|arbitrary_info_t
op_star
id|old_info
)paren
(brace
r_return
id|labelcl_info_replace_LBL
c_func
(paren
id|de
comma
id|name
comma
id|INFO_DESC_PRIVATE
comma
id|info
comma
l_int|NULL
comma
id|old_info
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_info_get_LBL - Get and return the info value in the label of the &n; * &t;device.&n; */
multiline_comment|/* ARGSUSED */
r_int
DECL|function|hwgraph_info_get_LBL
id|hwgraph_info_get_LBL
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_char
op_star
id|name
comma
id|arbitrary_info_t
op_star
id|infop
)paren
(brace
r_return
id|labelcl_info_get_LBL
c_func
(paren
id|de
comma
id|name
comma
l_int|NULL
comma
id|infop
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_info_get_exported_LBL - Retrieve the info_desc and info pointer &n; *&t;of the given label for the device.  The weird thing is that the label &n; *&t;that matches the name is return irrespective of the info_desc value!&n; *&t;Do not understand why the word &quot;exported&quot; is used!&n; */
multiline_comment|/* ARGSUSED */
r_int
DECL|function|hwgraph_info_get_exported_LBL
id|hwgraph_info_get_exported_LBL
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_char
op_star
id|name
comma
r_int
op_star
id|export_info
comma
id|arbitrary_info_t
op_star
id|infop
)paren
(brace
r_int
id|rc
suffix:semicolon
id|arb_info_desc_t
id|info_desc
suffix:semicolon
id|rc
op_assign
id|labelcl_info_get_LBL
c_func
(paren
id|de
comma
id|name
comma
op_amp
id|info_desc
comma
id|infop
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
op_star
id|export_info
op_assign
(paren
r_int
)paren
id|info_desc
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_info_get_next_LBL - Returns the next label info given the &n; *&t;current label entry in place.&n; *&n; *&t;Once again this has no locking or reference count for protection.&n; *&n; */
multiline_comment|/* ARGSUSED */
r_int
DECL|function|hwgraph_info_get_next_LBL
id|hwgraph_info_get_next_LBL
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_char
op_star
id|buf
comma
id|arbitrary_info_t
op_star
id|infop
comma
id|labelcl_info_place_t
op_star
id|place
)paren
(brace
r_return
id|labelcl_info_get_next_LBL
c_func
(paren
id|de
comma
id|buf
comma
l_int|NULL
comma
id|infop
comma
id|place
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_info_export_LBL - Retrieve the specified label entry and modify &n; *&t;the info_desc field with the given value in nbytes.&n; */
multiline_comment|/* ARGSUSED */
r_int
DECL|function|hwgraph_info_export_LBL
id|hwgraph_info_export_LBL
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_char
op_star
id|name
comma
r_int
id|nbytes
)paren
(brace
id|arbitrary_info_t
id|info
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_eq
l_int|0
)paren
id|nbytes
op_assign
id|INFO_DESC_EXPORT
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|rc
op_assign
id|labelcl_info_get_LBL
c_func
(paren
id|de
comma
id|name
comma
l_int|NULL
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_return
id|rc
suffix:semicolon
id|rc
op_assign
id|labelcl_info_replace_LBL
c_func
(paren
id|de
comma
id|name
comma
id|nbytes
comma
id|info
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_info_unexport_LBL - Retrieve the given label entry and change the &n; * label info_descr filed to INFO_DESC_PRIVATE.&n; */
multiline_comment|/* ARGSUSED */
r_int
DECL|function|hwgraph_info_unexport_LBL
id|hwgraph_info_unexport_LBL
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_char
op_star
id|name
)paren
(brace
id|arbitrary_info_t
id|info
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|labelcl_info_get_LBL
c_func
(paren
id|de
comma
id|name
comma
l_int|NULL
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_return
id|rc
suffix:semicolon
id|rc
op_assign
id|labelcl_info_replace_LBL
c_func
(paren
id|de
comma
id|name
comma
id|INFO_DESC_PRIVATE
comma
id|info
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_traverse - Find and return the handle starting from de.&n; *&n; */
id|graph_error_t
DECL|function|hwgraph_traverse
id|hwgraph_traverse
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_char
op_star
id|path
comma
id|vertex_hdl_t
op_star
id|found
)paren
(brace
multiline_comment|/* &n;&t; * get the directory entry (path should end in a directory)&n;&t; */
op_star
id|found
op_assign
id|hwgfs_find_handle
c_func
(paren
id|de
comma
multiline_comment|/* start dir */
id|path
comma
multiline_comment|/* path */
l_int|0
comma
multiline_comment|/* major */
l_int|0
comma
multiline_comment|/* minor */
l_int|0
comma
multiline_comment|/* char | block */
l_int|1
)paren
suffix:semicolon
multiline_comment|/* traverse symlinks */
r_if
c_cond
(paren
op_star
id|found
op_eq
l_int|NULL
)paren
r_return
id|GRAPH_NOT_FOUND
suffix:semicolon
r_else
r_return
id|GRAPH_SUCCESS
suffix:semicolon
)brace
multiline_comment|/*&n; * hwgraph_path_to_vertex - Return the entry handle for the given &n; *&t;pathname .. assume traverse symlinks too!.&n; */
id|vertex_hdl_t
DECL|function|hwgraph_path_to_vertex
id|hwgraph_path_to_vertex
c_func
(paren
r_char
op_star
id|path
)paren
(brace
r_return
id|hwgfs_find_handle
c_func
(paren
l_int|NULL
comma
multiline_comment|/* start dir */
id|path
comma
multiline_comment|/* path */
l_int|0
comma
multiline_comment|/* major */
l_int|0
comma
multiline_comment|/* minor */
l_int|0
comma
multiline_comment|/* char | block */
l_int|1
)paren
suffix:semicolon
multiline_comment|/* traverse symlinks */
)brace
multiline_comment|/*&n; * hwgraph_inventory_remove - Removes an inventory entry.&n; *&n; *&t;Remove an inventory item associated with a vertex.   It is the caller&squot;s&n; *&t;responsibility to make sure that there are no races between removing&n; *&t;inventory from a vertex and simultaneously removing that vertex.&n;*/
r_int
DECL|function|hwgraph_inventory_remove
id|hwgraph_inventory_remove
c_func
(paren
id|vertex_hdl_t
id|de
comma
r_int
r_class
comma
r_int
id|type
comma
id|major_t
id|controller
comma
id|minor_t
id|unit
comma
r_int
id|state
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Just a Stub for IRIX code. */
)brace
multiline_comment|/*&n; * Find the canonical name for a given vertex by walking back through&n; * connectpt&squot;s until we hit the hwgraph root vertex (or until we run&n; * out of buffer space or until something goes wrong).&n; *&n; *&t;COMPATIBILITY FUNCTIONALITY&n; * Walks back through &squot;parents&squot;, not necessarily the same as connectpts.&n; *&n; * Need to resolve the fact that does not return the path from &n; * &quot;/&quot; but rather it just stops right before /dev ..&n; */
r_int
DECL|function|hwgraph_vertex_name_get
id|hwgraph_vertex_name_get
c_func
(paren
id|vertex_hdl_t
id|vhdl
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_char
op_star
id|locbuf
suffix:semicolon
r_int
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|buflen
OL
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* XXX should be GRAPH_BAD_PARAM ? */
id|locbuf
op_assign
id|kmalloc
c_func
(paren
id|buflen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|pos
op_assign
id|hwgfs_generate_path
c_func
(paren
id|vhdl
comma
id|locbuf
comma
id|buflen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|locbuf
)paren
suffix:semicolon
r_return
id|pos
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|buf
comma
op_amp
id|locbuf
(braket
id|pos
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|locbuf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;** vertex_to_name converts a vertex into a canonical name by walking&n;** back through connect points until we hit the hwgraph root (or until&n;** we run out of buffer space).&n;**&n;** Usually returns a pointer to the original buffer, filled in as&n;** appropriate.  If the buffer is too small to hold the entire name,&n;** or if anything goes wrong while determining the name, vertex_to_name&n;** returns &quot;UnknownDevice&quot;.&n;*/
DECL|macro|DEVNAME_UNKNOWN
mdefine_line|#define DEVNAME_UNKNOWN &quot;UnknownDevice&quot;
r_char
op_star
DECL|function|vertex_to_name
id|vertex_to_name
c_func
(paren
id|vertex_hdl_t
id|vhdl
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_if
c_cond
(paren
id|hwgraph_vertex_name_get
c_func
(paren
id|vhdl
comma
id|buf
comma
id|buflen
)paren
op_eq
id|GRAPH_SUCCESS
)paren
r_return
id|buf
suffix:semicolon
r_else
r_return
id|DEVNAME_UNKNOWN
suffix:semicolon
)brace
id|graph_error_t
DECL|function|hwgraph_edge_remove
id|hwgraph_edge_remove
c_func
(paren
id|vertex_hdl_t
id|from
comma
r_char
op_star
id|name
comma
id|vertex_hdl_t
op_star
id|toptr
)paren
(brace
r_return
id|GRAPH_ILLEGAL_REQUEST
suffix:semicolon
)brace
id|graph_error_t
DECL|function|hwgraph_vertex_unref
id|hwgraph_vertex_unref
c_func
(paren
id|vertex_hdl_t
id|vhdl
)paren
(brace
r_return
id|GRAPH_ILLEGAL_REQUEST
suffix:semicolon
)brace
DECL|variable|hwgraph_mk_dir
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_mk_dir
)paren
suffix:semicolon
DECL|variable|hwgraph_path_add
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_path_add
)paren
suffix:semicolon
DECL|variable|hwgraph_register
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_register
)paren
suffix:semicolon
DECL|variable|hwgraph_vertex_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_vertex_destroy
)paren
suffix:semicolon
DECL|variable|hwgraph_fastinfo_get
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_fastinfo_get
)paren
suffix:semicolon
DECL|variable|hwgraph_fastinfo_set
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_fastinfo_set
)paren
suffix:semicolon
DECL|variable|hwgraph_connectpt_set
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_connectpt_set
)paren
suffix:semicolon
DECL|variable|hwgraph_connectpt_get
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_connectpt_get
)paren
suffix:semicolon
DECL|variable|hwgraph_info_add_LBL
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_info_add_LBL
)paren
suffix:semicolon
DECL|variable|hwgraph_info_remove_LBL
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_info_remove_LBL
)paren
suffix:semicolon
DECL|variable|hwgraph_info_replace_LBL
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_info_replace_LBL
)paren
suffix:semicolon
DECL|variable|hwgraph_info_get_LBL
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_info_get_LBL
)paren
suffix:semicolon
DECL|variable|hwgraph_info_get_exported_LBL
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_info_get_exported_LBL
)paren
suffix:semicolon
DECL|variable|hwgraph_info_get_next_LBL
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_info_get_next_LBL
)paren
suffix:semicolon
DECL|variable|hwgraph_info_export_LBL
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_info_export_LBL
)paren
suffix:semicolon
DECL|variable|hwgraph_info_unexport_LBL
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_info_unexport_LBL
)paren
suffix:semicolon
DECL|variable|hwgraph_traverse
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_traverse
)paren
suffix:semicolon
DECL|variable|hwgraph_vertex_name_get
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_vertex_name_get
)paren
suffix:semicolon
eof
