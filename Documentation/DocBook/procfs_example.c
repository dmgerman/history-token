multiline_comment|/*&n; * procfs_example.c: an example proc interface&n; *&n; * Copyright (C) 2001, Erik Mouw (J.A.K.Mouw@its.tudelft.nl)&n; *&n; * This file accompanies the procfs-guide in the Linux kernel&n; * source. Its main use is to demonstrate the concepts and&n; * functions described in the guide.&n; *&n; * This software has been developed while working on the LART&n; * computing board (http://www.lart.tudelft.nl/), which is&n; * sponsored by the Mobile Multi-media Communications&n; * (http://www.mmc.tudelft.nl/) and Ubiquitous Communications &n; * (http://www.ubicom.tudelft.nl/) projects.&n; *&n; * The author can be reached at:&n; *&n; *  Erik Mouw&n; *  Information and Communication Theory Group&n; *  Faculty of Information Technology and Systems&n; *  Delft University of Technology&n; *  P.O. Box 5031&n; *  2600 GA Delft&n; *  The Netherlands&n; *&n; *&n; * This program is free software; you can redistribute&n; * it and/or modify it under the terms of the GNU General&n; * Public License as published by the Free Software&n; * Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR&n; * PURPOSE.  See the GNU General Public License for more&n; * details.&n; * &n; * You should have received a copy of the GNU General Public&n; * License along with this program; if not, write to the&n; * Free Software Foundation, Inc., 59 Temple Place,&n; * Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|MODULE_VERSION
mdefine_line|#define MODULE_VERSION &quot;1.0&quot;
DECL|macro|MODULE_NAME
mdefine_line|#define MODULE_NAME &quot;procfs_example&quot;
DECL|macro|FOOBAR_LEN
mdefine_line|#define FOOBAR_LEN 8
DECL|struct|fb_data_t
r_struct
id|fb_data_t
(brace
DECL|member|name
r_char
id|name
(braket
id|FOOBAR_LEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|value
r_char
id|value
(braket
id|FOOBAR_LEN
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|example_dir
DECL|variable|foo_file
r_static
r_struct
id|proc_dir_entry
op_star
id|example_dir
comma
op_star
id|foo_file
comma
DECL|variable|bar_file
DECL|variable|jiffies_file
DECL|variable|tty_device
DECL|variable|symlink
op_star
id|bar_file
comma
op_star
id|jiffies_file
comma
op_star
id|tty_device
comma
op_star
id|symlink
suffix:semicolon
DECL|variable|foo_data
DECL|variable|bar_data
r_struct
id|fb_data_t
id|foo_data
comma
id|bar_data
suffix:semicolon
DECL|function|proc_read_jiffies
r_static
r_int
id|proc_read_jiffies
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
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;jiffies = %ld&bslash;n&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|proc_read_foobar
r_static
r_int
id|proc_read_foobar
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
suffix:semicolon
r_struct
id|fb_data_t
op_star
id|fb_data
op_assign
(paren
r_struct
id|fb_data_t
op_star
)paren
id|data
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%s = &squot;%s&squot;&bslash;n&quot;
comma
id|fb_data-&gt;name
comma
id|fb_data-&gt;value
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|proc_write_foobar
r_static
r_int
id|proc_write_foobar
c_func
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
id|len
suffix:semicolon
r_struct
id|fb_data_t
op_star
id|fb_data
op_assign
(paren
r_struct
id|fb_data_t
op_star
)paren
id|data
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|FOOBAR_LEN
)paren
(brace
id|len
op_assign
id|FOOBAR_LEN
suffix:semicolon
)brace
r_else
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|fb_data-&gt;value
comma
id|buffer
comma
id|len
)paren
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|fb_data-&gt;value
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|init_procfs_example
r_static
r_int
id|__init
id|init_procfs_example
c_func
(paren
r_void
)paren
(brace
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* create directory */
id|example_dir
op_assign
id|proc_mkdir
c_func
(paren
id|MODULE_NAME
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|example_dir
op_eq
l_int|NULL
)paren
(brace
id|rv
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|example_dir-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/* create jiffies using convenience function */
id|jiffies_file
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;jiffies&quot;
comma
l_int|0444
comma
id|example_dir
comma
id|proc_read_jiffies
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jiffies_file
op_eq
l_int|NULL
)paren
(brace
id|rv
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|no_jiffies
suffix:semicolon
)brace
id|jiffies_file-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/* create foo and bar files using same callback&n;&t; * functions &n;&t; */
id|foo_file
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;foo&quot;
comma
l_int|0644
comma
id|example_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|foo_file
op_eq
l_int|NULL
)paren
(brace
id|rv
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|no_foo
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|foo_data.name
comma
l_string|&quot;foo&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|foo_data.value
comma
l_string|&quot;foo&quot;
)paren
suffix:semicolon
id|foo_file-&gt;data
op_assign
op_amp
id|foo_data
suffix:semicolon
id|foo_file-&gt;read_proc
op_assign
id|proc_read_foobar
suffix:semicolon
id|foo_file-&gt;write_proc
op_assign
id|proc_write_foobar
suffix:semicolon
id|foo_file-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|bar_file
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;bar&quot;
comma
l_int|0644
comma
id|example_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bar_file
op_eq
l_int|NULL
)paren
(brace
id|rv
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|no_bar
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|bar_data.name
comma
l_string|&quot;bar&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|bar_data.value
comma
l_string|&quot;bar&quot;
)paren
suffix:semicolon
id|bar_file-&gt;data
op_assign
op_amp
id|bar_data
suffix:semicolon
id|bar_file-&gt;read_proc
op_assign
id|proc_read_foobar
suffix:semicolon
id|bar_file-&gt;write_proc
op_assign
id|proc_write_foobar
suffix:semicolon
id|bar_file-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/* create tty device */
id|tty_device
op_assign
id|proc_mknod
c_func
(paren
l_string|&quot;tty&quot;
comma
id|S_IFCHR
op_or
l_int|0666
comma
id|example_dir
comma
id|MKDEV
c_func
(paren
l_int|5
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty_device
op_eq
l_int|NULL
)paren
(brace
id|rv
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|no_tty
suffix:semicolon
)brace
id|tty_device-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/* create symlink */
id|symlink
op_assign
id|proc_symlink
c_func
(paren
l_string|&quot;jiffies_too&quot;
comma
id|example_dir
comma
l_string|&quot;jiffies&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symlink
op_eq
l_int|NULL
)paren
(brace
id|rv
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|no_symlink
suffix:semicolon
)brace
id|symlink-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/* everything OK */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s %s initialised&bslash;n&quot;
comma
id|MODULE_NAME
comma
id|MODULE_VERSION
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|no_symlink
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;tty&quot;
comma
id|example_dir
)paren
suffix:semicolon
id|no_tty
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;bar&quot;
comma
id|example_dir
)paren
suffix:semicolon
id|no_bar
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;foo&quot;
comma
id|example_dir
)paren
suffix:semicolon
id|no_foo
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;jiffies&quot;
comma
id|example_dir
)paren
suffix:semicolon
id|no_jiffies
suffix:colon
id|remove_proc_entry
c_func
(paren
id|MODULE_NAME
comma
l_int|NULL
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rv
suffix:semicolon
)brace
DECL|function|cleanup_procfs_example
r_static
r_void
id|__exit
id|cleanup_procfs_example
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;jiffies_too&quot;
comma
id|example_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;tty&quot;
comma
id|example_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;bar&quot;
comma
id|example_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;foo&quot;
comma
id|example_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;jiffies&quot;
comma
id|example_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|MODULE_NAME
comma
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s %s removed&bslash;n&quot;
comma
id|MODULE_NAME
comma
id|MODULE_VERSION
)paren
suffix:semicolon
)brace
DECL|variable|init_procfs_example
id|module_init
c_func
(paren
id|init_procfs_example
)paren
suffix:semicolon
DECL|variable|cleanup_procfs_example
id|module_exit
c_func
(paren
id|cleanup_procfs_example
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Erik Mouw&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;procfs examples&quot;
)paren
suffix:semicolon
eof
