multiline_comment|/* &n; * $Id: divert_init.c,v 1.5 2000/11/13 22:51:47 kai Exp $&n; *&n; * Module init for DSS1 diversion services for i4l.&n; *&n; * Copyright 1999       by Werner Cornelius (werner@isdn4linux.de)&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &quot;isdn_divert.h&quot;
multiline_comment|/********************/
multiline_comment|/* needed externals */
multiline_comment|/********************/
r_extern
r_int
id|printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/****************************************/
multiline_comment|/* structure containing interface to hl */
multiline_comment|/****************************************/
DECL|variable|divert_if
id|isdn_divert_if
id|divert_if
op_assign
(brace
id|DIVERT_IF_MAGIC
comma
multiline_comment|/* magic value */
id|DIVERT_CMD_REG
comma
multiline_comment|/* register cmd */
id|ll_callback
comma
multiline_comment|/* callback routine from ll */
l_int|NULL
comma
multiline_comment|/* command still not specified */
l_int|NULL
comma
multiline_comment|/* drv_to_name */
l_int|NULL
comma
multiline_comment|/* name_to_drv */
)brace
suffix:semicolon
multiline_comment|/*************************/
multiline_comment|/* Module interface code */
multiline_comment|/* no cmd line parms     */
multiline_comment|/*************************/
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|divert_dev_init
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;dss1_divert: cannot install device, not loaded&bslash;n&quot;
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
(paren
id|i
op_assign
id|DIVERT_REG_NAME
c_func
(paren
op_amp
id|divert_if
)paren
)paren
op_ne
id|DIVERT_NO_ERR
)paren
(brace
id|divert_dev_deinit
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;dss1_divert: error %d registering module, not loaded&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
macro_line|#if (LINUX_VERSION_CODE &lt; 0x020111)
id|register_symtab
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;dss1_divert module successfully installed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* init_module */
multiline_comment|/**********************/
multiline_comment|/* Module deinit code */
multiline_comment|/**********************/
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|divert_if.cmd
op_assign
id|DIVERT_CMD_REL
suffix:semicolon
multiline_comment|/* release */
r_if
c_cond
(paren
(paren
id|i
op_assign
id|DIVERT_REG_NAME
c_func
(paren
op_amp
id|divert_if
)paren
)paren
op_ne
id|DIVERT_NO_ERR
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;dss1_divert: error %d releasing module&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|divert_dev_deinit
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;dss1_divert: device busy, remove cancelled&bslash;n&quot;
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|deleterule
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* delete all rules and free mem */
id|deleteprocs
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;dss1_divert module successfully removed &bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* cleanup_module */
eof
