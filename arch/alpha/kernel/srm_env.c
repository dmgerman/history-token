multiline_comment|/*&n; * srm_env.c - Access to SRM environment&n; *             variables through linux&squot; procfs&n; *&n; * Copyright (C) 2001-2002 Jan-Benedict Glaw &lt;jbglaw@lug-owl.de&gt;&n; *&n; * This driver is at all a modified version of Erik Mouw&squot;s&n; * ./linux/Documentation/DocBook/procfs_example.c, so: thank&n; * you, Erik! He can be reached via email at&n; * &lt;J.A.K.Mouw@its.tudelft.nl&gt;. It is based on an idea&n; * provided by DEC^WCompaq^WIntel&squot;s &quot;Jumpstart&quot; CD. They&n; * included a patch like this as well. Thanks for idea!&n; *&n; * This program is free software; you can redistribute&n; * it and/or modify it under the terms of the GNU General&n; * Public License version 2 as published by the Free Software&n; * Foundation.&n; *&n; * This program is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR&n; * PURPOSE.  See the GNU General Public License for more&n; * details.&n; * &n; * You should have received a copy of the GNU General Public&n; * License along with this program; if not, write to the&n; * Free Software Foundation, Inc., 59 Temple Place,&n; * Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
multiline_comment|/*&n; * Changelog&n; * ~~~~~~~~~&n; *&n; * Thu, 22 Aug 2002 15:10:43 +0200&n; * &t;- Update Config.help entry. I got a number of emails asking&n; * &t;  me to tell their senders if they could make use of this&n; * &t;  piece of code... So: &quot;SRM is something like BIOS for your&n; * &t;  Alpha&quot;&n; * &t;- Update code formatting a bit to better conform CodingStyle&n; * &t;  rules.&n; * &t;- So this is v0.0.5, with no changes (except formatting)&n; * &t;&n; * Wed, 22 May 2002 00:11:21 +0200&n; * &t;- Fix typo on comment (SRC -&gt; SRM)&n; * &t;- Call this &quot;Version 0.0.4&quot;&n; *&n; * Tue,  9 Apr 2002 18:44:40 +0200&n; * &t;- Implement access by variable name and additionally&n; * &t;  by number. This is done by creating two subdirectories&n; * &t;  where one holds all names (like the old directory&n; * &t;  did) and the other holding 256 files named like &quot;0&quot;,&n; * &t;  &quot;1&quot; and so on.&n; * &t;- Call this &quot;Version 0.0.3&quot;&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/console.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
DECL|macro|BASE_DIR
mdefine_line|#define BASE_DIR&t;&quot;srm_environment&quot;&t;/* Subdir in /proc/&t;&t;*/
DECL|macro|NAMED_DIR
mdefine_line|#define NAMED_DIR&t;&quot;named_variables&quot;&t;/* Subdir for known variables&t;*/
DECL|macro|NUMBERED_DIR
mdefine_line|#define NUMBERED_DIR&t;&quot;numbered_variables&quot;&t;/* Subdir for all variables&t;*/
DECL|macro|VERSION
mdefine_line|#define VERSION&t;&t;&quot;0.0.5&quot;&t;&t;&t;/* Module version&t;&t;*/
DECL|macro|NAME
mdefine_line|#define NAME&t;&t;&quot;srm_env&quot;&t;&t;/* Module name&t;&t;&t;*/
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jan-Benedict Glaw &lt;jbglaw@lug-owl.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Accessing Alpha SRM environment through procfs interface&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|struct|_srm_env
r_typedef
r_struct
id|_srm_env
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
DECL|typedef|srm_env_t
)brace
id|srm_env_t
suffix:semicolon
DECL|variable|base_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|base_dir
suffix:semicolon
DECL|variable|named_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|named_dir
suffix:semicolon
DECL|variable|numbered_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|numbered_dir
suffix:semicolon
DECL|variable|number
r_static
r_char
id|number
(braket
l_int|256
)braket
(braket
l_int|4
)braket
suffix:semicolon
DECL|variable|srm_named_entries
r_static
id|srm_env_t
id|srm_named_entries
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;auto_action&quot;
comma
id|ENV_AUTO_ACTION
)brace
comma
(brace
l_string|&quot;boot_dev&quot;
comma
id|ENV_BOOT_DEV
)brace
comma
(brace
l_string|&quot;bootdef_dev&quot;
comma
id|ENV_BOOTDEF_DEV
)brace
comma
(brace
l_string|&quot;booted_dev&quot;
comma
id|ENV_BOOTED_DEV
)brace
comma
(brace
l_string|&quot;boot_file&quot;
comma
id|ENV_BOOT_FILE
)brace
comma
(brace
l_string|&quot;booted_file&quot;
comma
id|ENV_BOOTED_FILE
)brace
comma
(brace
l_string|&quot;boot_osflags&quot;
comma
id|ENV_BOOT_OSFLAGS
)brace
comma
(brace
l_string|&quot;booted_osflags&quot;
comma
id|ENV_BOOTED_OSFLAGS
)brace
comma
(brace
l_string|&quot;boot_reset&quot;
comma
id|ENV_BOOT_RESET
)brace
comma
(brace
l_string|&quot;dump_dev&quot;
comma
id|ENV_DUMP_DEV
)brace
comma
(brace
l_string|&quot;enable_audit&quot;
comma
id|ENV_ENABLE_AUDIT
)brace
comma
(brace
l_string|&quot;license&quot;
comma
id|ENV_LICENSE
)brace
comma
(brace
l_string|&quot;char_set&quot;
comma
id|ENV_CHAR_SET
)brace
comma
(brace
l_string|&quot;language&quot;
comma
id|ENV_LANGUAGE
)brace
comma
(brace
l_string|&quot;tty_dev&quot;
comma
id|ENV_TTY_DEV
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|srm_numbered_entries
r_static
id|srm_env_t
id|srm_numbered_entries
(braket
l_int|256
)braket
suffix:semicolon
r_static
r_int
DECL|function|srm_env_read
id|srm_env_read
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
id|nbytes
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|srm_env_t
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|entry
op_assign
(paren
id|srm_env_t
op_star
)paren
id|data
suffix:semicolon
id|ret
op_assign
id|callback_getenv
c_func
(paren
id|entry-&gt;id
comma
id|page
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_rshift
l_int|61
)paren
op_eq
l_int|0
)paren
(brace
id|nbytes
op_assign
(paren
r_int
)paren
id|ret
suffix:semicolon
)brace
r_else
id|nbytes
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
id|nbytes
suffix:semicolon
)brace
r_static
r_int
DECL|function|srm_env_write
id|srm_env_write
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
id|res
suffix:semicolon
id|srm_env_t
op_star
id|entry
suffix:semicolon
r_char
op_star
id|buf
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_USER
)paren
suffix:semicolon
r_int
r_int
id|ret1
comma
id|ret2
suffix:semicolon
id|entry
op_assign
(paren
id|srm_env_t
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|res
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
id|PAGE_SIZE
)paren
r_goto
id|out
suffix:semicolon
id|res
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
id|buf
comma
id|buffer
comma
id|count
)paren
)paren
r_goto
id|out
suffix:semicolon
id|buf
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|ret1
op_assign
id|callback_setenv
c_func
(paren
id|entry-&gt;id
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret1
op_rshift
l_int|61
)paren
op_eq
l_int|0
)paren
(brace
r_do
id|ret2
op_assign
id|callback_save_env
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ret2
op_rshift
l_int|61
)paren
op_eq
l_int|1
)paren
(brace
suffix:semicolon
)brace
id|res
op_assign
(paren
r_int
)paren
id|ret1
suffix:semicolon
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buf
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_static
r_void
DECL|function|srm_env_cleanup
id|srm_env_cleanup
c_func
(paren
r_void
)paren
(brace
id|srm_env_t
op_star
id|entry
suffix:semicolon
r_int
r_int
id|var_num
suffix:semicolon
r_if
c_cond
(paren
id|base_dir
)paren
(brace
multiline_comment|/*&n;&t;&t; * Remove named entries&n;&t;&t; */
r_if
c_cond
(paren
id|named_dir
)paren
(brace
id|entry
op_assign
id|srm_named_entries
suffix:semicolon
r_while
c_loop
(paren
id|entry-&gt;name
op_ne
l_int|NULL
op_logical_and
id|entry-&gt;id
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;proc_entry
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|entry-&gt;name
comma
id|named_dir
)paren
suffix:semicolon
id|entry-&gt;proc_entry
op_assign
l_int|NULL
suffix:semicolon
)brace
id|entry
op_increment
suffix:semicolon
)brace
id|remove_proc_entry
c_func
(paren
id|NAMED_DIR
comma
id|base_dir
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Remove numbered entries&n;&t;&t; */
r_if
c_cond
(paren
id|numbered_dir
)paren
(brace
r_for
c_loop
(paren
id|var_num
op_assign
l_int|0
suffix:semicolon
id|var_num
op_le
l_int|255
suffix:semicolon
id|var_num
op_increment
)paren
(brace
id|entry
op_assign
op_amp
id|srm_numbered_entries
(braket
id|var_num
)braket
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;proc_entry
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|entry-&gt;name
comma
id|numbered_dir
)paren
suffix:semicolon
id|entry-&gt;proc_entry
op_assign
l_int|NULL
suffix:semicolon
id|entry-&gt;name
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|remove_proc_entry
c_func
(paren
id|NUMBERED_DIR
comma
id|base_dir
)paren
suffix:semicolon
)brace
id|remove_proc_entry
c_func
(paren
id|BASE_DIR
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|srm_env_init
id|srm_env_init
c_func
(paren
r_void
)paren
(brace
id|srm_env_t
op_star
id|entry
suffix:semicolon
r_int
r_int
id|var_num
suffix:semicolon
multiline_comment|/*&n;&t; * Check system&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|alpha_using_srm
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: This Alpha system doesn&squot;t &quot;
l_string|&quot;know about SRM (or you&squot;ve booted &quot;
l_string|&quot;SRM-&gt;MILO-&gt;Linux, which gets &quot;
l_string|&quot;misdetected)...&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Init numbers&n;&t; */
r_for
c_loop
(paren
id|var_num
op_assign
l_int|0
suffix:semicolon
id|var_num
op_le
l_int|255
suffix:semicolon
id|var_num
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|number
(braket
id|var_num
)braket
comma
l_string|&quot;%ld&quot;
comma
id|var_num
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Create base directory&n;&t; */
id|base_dir
op_assign
id|proc_mkdir
c_func
(paren
id|BASE_DIR
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base_dir
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Couldn&squot;t create base dir /proc/%s&bslash;n&quot;
comma
id|BASE_DIR
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|base_dir-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/*&n;&t; * Create per-name subdirectory&n;&t; */
id|named_dir
op_assign
id|proc_mkdir
c_func
(paren
id|NAMED_DIR
comma
id|base_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|named_dir
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Couldn&squot;t create dir /proc/%s/%s&bslash;n&quot;
comma
id|BASE_DIR
comma
id|NAMED_DIR
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|named_dir-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/*&n;&t; * Create per-number subdirectory&n;&t; */
id|numbered_dir
op_assign
id|proc_mkdir
c_func
(paren
id|NUMBERED_DIR
comma
id|base_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|numbered_dir
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Couldn&squot;t create dir /proc/%s/%s&bslash;n&quot;
comma
id|BASE_DIR
comma
id|NUMBERED_DIR
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|numbered_dir-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
multiline_comment|/*&n;&t; * Create all named nodes&n;&t; */
id|entry
op_assign
id|srm_named_entries
suffix:semicolon
r_while
c_loop
(paren
id|entry-&gt;name
op_ne
l_int|NULL
op_logical_and
id|entry-&gt;id
op_ne
l_int|0
)paren
(brace
id|entry-&gt;proc_entry
op_assign
id|create_proc_entry
c_func
(paren
id|entry-&gt;name
comma
l_int|0644
comma
id|named_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;proc_entry
op_eq
l_int|NULL
)paren
(brace
r_goto
id|cleanup
suffix:semicolon
)brace
id|entry-&gt;proc_entry-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|entry
suffix:semicolon
id|entry-&gt;proc_entry-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|entry-&gt;proc_entry-&gt;read_proc
op_assign
id|srm_env_read
suffix:semicolon
id|entry-&gt;proc_entry-&gt;write_proc
op_assign
id|srm_env_write
suffix:semicolon
id|entry
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Create all numbered nodes&n;&t; */
r_for
c_loop
(paren
id|var_num
op_assign
l_int|0
suffix:semicolon
id|var_num
op_le
l_int|255
suffix:semicolon
id|var_num
op_increment
)paren
(brace
id|entry
op_assign
op_amp
id|srm_numbered_entries
(braket
id|var_num
)braket
suffix:semicolon
id|entry-&gt;name
op_assign
id|number
(braket
id|var_num
)braket
suffix:semicolon
id|entry-&gt;proc_entry
op_assign
id|create_proc_entry
c_func
(paren
id|entry-&gt;name
comma
l_int|0644
comma
id|numbered_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;proc_entry
op_eq
l_int|NULL
)paren
(brace
r_goto
id|cleanup
suffix:semicolon
)brace
id|entry-&gt;id
op_assign
id|var_num
suffix:semicolon
id|entry-&gt;proc_entry-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|entry
suffix:semicolon
id|entry-&gt;proc_entry-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|entry-&gt;proc_entry-&gt;read_proc
op_assign
id|srm_env_read
suffix:semicolon
id|entry-&gt;proc_entry-&gt;write_proc
op_assign
id|srm_env_write
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: version %s loaded successfully&bslash;n&quot;
comma
id|NAME
comma
id|VERSION
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|cleanup
suffix:colon
id|srm_env_cleanup
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|srm_env_exit
id|srm_env_exit
c_func
(paren
r_void
)paren
(brace
id|srm_env_cleanup
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: unloaded successfully&bslash;n&quot;
comma
id|NAME
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|srm_env_init
id|module_init
c_func
(paren
id|srm_env_init
)paren
suffix:semicolon
DECL|variable|srm_env_exit
id|module_exit
c_func
(paren
id|srm_env_exit
)paren
suffix:semicolon
eof
