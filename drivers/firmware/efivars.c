multiline_comment|/*&n; * EFI Variables - efivars.c&n; *&n; * Copyright (C) 2001,2003,2004 Dell &lt;Matt_Domsch@dell.com&gt;&n; * Copyright (C) 2004 Intel Corporation &lt;matthew.e.tolentino@intel.com&gt;&n; *&n; * This code takes all variables accessible from EFI runtime and&n; *  exports them via sysfs&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * Changelog:&n; *&n; *  17 May 2004 - Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *   remove check for efi_enabled in exit&n; *   add MODULE_VERSION&n; *&n; *  26 Apr 2004 - Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *   minor bug fixes&n; *&n; *  21 Apr 2004 - Matt Tolentino &lt;matthew.e.tolentino@intel.com)&n; *   converted driver to export variable information via sysfs&n; *   and moved to drivers/firmware directory&n; *   bumped revision number to v0.07 to reflect conversion &amp; move&n; *&n; *  10 Dec 2002 - Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *   fix locking per Peter Chubb&squot;s findings&n; *&n; *  25 Mar 2002 - Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *   move uuid_unparse() to include/asm-ia64/efi.h:efi_guid_unparse()&n; *&n; *  12 Feb 2002 - Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *   use list_for_each_safe when deleting vars.&n; *   remove ifdef CONFIG_SMP around include &lt;linux/smp.h&gt;&n; *   v0.04 release to linux-ia64@linuxia64.org&n; *&n; *  20 April 2001 - Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *   Moved vars from /proc/efi to /proc/efi/vars, and made&n; *   efi.c own the /proc/efi directory.&n; *   v0.03 release to linux-ia64@linuxia64.org&n; *&n; *  26 March 2001 - Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *   At the request of Stephane, moved ownership of /proc/efi&n; *   to efi.c, and now efivars lives under /proc/efi/vars.&n; *&n; *  12 March 2001 - Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *   Feedback received from Stephane Eranian incorporated.&n; *   efivar_write() checks copy_from_user() return value.&n; *   efivar_read/write() returns proper errno.&n; *   v0.02 release to linux-ia64@linuxia64.org&n; *&n; *  26 February 2001 - Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; *   v0.01 release to linux-ia64@linuxia64.org&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;&t;&t;/* for capable() */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;linux/sysfs.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|EFIVARS_VERSION
mdefine_line|#define EFIVARS_VERSION &quot;0.08&quot;
DECL|macro|EFIVARS_DATE
mdefine_line|#define EFIVARS_DATE &quot;2004-May-17&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Matt Domsch &lt;Matt_Domsch@Dell.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;sysfs interface to EFI Variables&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|EFIVARS_VERSION
id|MODULE_VERSION
c_func
(paren
id|EFIVARS_VERSION
)paren
suffix:semicolon
multiline_comment|/*&n; * efivars_lock protects two things:&n; * 1) efivar_list - adds, removals, reads, writes&n; * 2) efi.[gs]et_variable() calls.&n; * It must not be held when creating sysfs entries or calling kmalloc.&n; * efi.get_next_variable() is only called from efivars_init(),&n; * which is protected by the BKL, so that path is safe.&n; */
DECL|variable|efivars_lock
r_static
id|spinlock_t
id|efivars_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|efivar_list
)paren
suffix:semicolon
multiline_comment|/*&n; * The maximum size of VariableName + Data = 1024&n; * Therefore, it&squot;s reasonable to save that much&n; * space in each part of the structure,&n; * and we use a page for reading/writing.&n; */
DECL|struct|efi_variable
r_struct
id|efi_variable
(brace
DECL|member|VariableName
id|efi_char16_t
id|VariableName
(braket
l_int|1024
op_div
r_sizeof
(paren
id|efi_char16_t
)paren
)braket
suffix:semicolon
DECL|member|VendorGuid
id|efi_guid_t
id|VendorGuid
suffix:semicolon
DECL|member|DataSize
r_int
r_int
id|DataSize
suffix:semicolon
DECL|member|Data
id|__u8
id|Data
(braket
l_int|1024
)braket
suffix:semicolon
DECL|member|Status
id|efi_status_t
id|Status
suffix:semicolon
DECL|member|Attributes
id|__u32
id|Attributes
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|efivar_entry
r_struct
id|efivar_entry
(brace
DECL|member|var
r_struct
id|efi_variable
id|var
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|get_efivar_entry
mdefine_line|#define get_efivar_entry(n) list_entry(n, struct efivar_entry, list)
DECL|struct|efivar_attribute
r_struct
id|efivar_attribute
(brace
DECL|member|attr
r_struct
id|attribute
id|attr
suffix:semicolon
DECL|member|show
id|ssize_t
(paren
op_star
id|show
)paren
(paren
r_struct
id|efivar_entry
op_star
id|entry
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|store
id|ssize_t
(paren
op_star
id|store
)paren
(paren
r_struct
id|efivar_entry
op_star
id|entry
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EFI_ATTR
mdefine_line|#define EFI_ATTR(_name, _mode, _show, _store) &bslash;&n;struct subsys_attribute efi_attr_##_name = { &bslash;&n;&t;.attr = {.name = __stringify(_name), .mode = _mode, .owner = THIS_MODULE}, &bslash;&n;&t;.show = _show, &bslash;&n;&t;.store = _store, &bslash;&n;};
DECL|macro|EFIVAR_ATTR
mdefine_line|#define EFIVAR_ATTR(_name, _mode, _show, _store) &bslash;&n;struct efivar_attribute efivar_attr_##_name = { &bslash;&n;&t;.attr = {.name = __stringify(_name), .mode = _mode, .owner = THIS_MODULE}, &bslash;&n;&t;.show = _show, &bslash;&n;&t;.store = _store, &bslash;&n;};
DECL|macro|VAR_SUBSYS_ATTR
mdefine_line|#define VAR_SUBSYS_ATTR(_name, _mode, _show, _store) &bslash;&n;struct subsys_attribute var_subsys_attr_##_name = { &bslash;&n;&t;.attr = {.name = __stringify(_name), .mode = _mode, .owner = THIS_MODULE}, &bslash;&n;&t;.show = _show, &bslash;&n;&t;.store = _store, &bslash;&n;};
DECL|macro|to_efivar_attr
mdefine_line|#define to_efivar_attr(_attr) container_of(_attr, struct efivar_attribute, attr)
DECL|macro|to_efivar_entry
mdefine_line|#define to_efivar_entry(obj)  container_of(obj, struct efivar_entry, kobj)
multiline_comment|/*&n; * Prototype for sysfs creation function&n; */
r_static
r_int
id|efivar_create_sysfs_entry
c_func
(paren
r_int
r_int
id|variable_name_size
comma
id|efi_char16_t
op_star
id|variable_name
comma
id|efi_guid_t
op_star
id|vendor_guid
)paren
suffix:semicolon
multiline_comment|/* Return the number of unicode characters in data */
r_static
r_int
r_int
DECL|function|utf8_strlen
id|utf8_strlen
c_func
(paren
id|efi_char16_t
op_star
id|data
comma
r_int
r_int
id|maxlength
)paren
(brace
r_int
r_int
id|length
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|data
op_increment
op_ne
l_int|0
op_logical_and
id|length
OL
id|maxlength
)paren
id|length
op_increment
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the number of bytes is the length of this string&n; * Note: this is NOT the same as the number of unicode characters&n; */
r_static
r_inline
r_int
r_int
DECL|function|utf8_strsize
id|utf8_strsize
c_func
(paren
id|efi_char16_t
op_star
id|data
comma
r_int
r_int
id|maxlength
)paren
(brace
r_return
id|utf8_strlen
c_func
(paren
id|data
comma
id|maxlength
op_div
r_sizeof
(paren
id|efi_char16_t
)paren
)paren
op_star
r_sizeof
(paren
id|efi_char16_t
)paren
suffix:semicolon
)brace
r_static
id|efi_status_t
DECL|function|get_var_data
id|get_var_data
c_func
(paren
r_struct
id|efi_variable
op_star
id|var
)paren
(brace
id|efi_status_t
id|status
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
id|var-&gt;DataSize
op_assign
l_int|1024
suffix:semicolon
id|status
op_assign
id|efi
dot
id|get_variable
c_func
(paren
id|var-&gt;VariableName
comma
op_amp
id|var-&gt;VendorGuid
comma
op_amp
id|var-&gt;Attributes
comma
op_amp
id|var-&gt;DataSize
comma
id|var-&gt;Data
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|EFI_SUCCESS
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;efivars: get_variable() failed 0x%lx!&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|efivar_guid_read
id|efivar_guid_read
c_func
(paren
r_struct
id|efivar_entry
op_star
id|entry
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|efi_variable
op_star
id|var
op_assign
op_amp
id|entry-&gt;var
suffix:semicolon
r_char
op_star
id|str
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
op_logical_or
op_logical_neg
id|buf
)paren
r_return
l_int|0
suffix:semicolon
id|efi_guid_unparse
c_func
(paren
op_amp
id|var-&gt;VendorGuid
comma
id|str
)paren
suffix:semicolon
id|str
op_add_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|str
op_minus
id|buf
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|efivar_attr_read
id|efivar_attr_read
c_func
(paren
r_struct
id|efivar_entry
op_star
id|entry
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|efi_variable
op_star
id|var
op_assign
op_amp
id|entry-&gt;var
suffix:semicolon
r_char
op_star
id|str
op_assign
id|buf
suffix:semicolon
id|efi_status_t
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
op_logical_or
op_logical_neg
id|buf
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|status
op_assign
id|get_var_data
c_func
(paren
id|var
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|EFI_SUCCESS
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;Attributes
op_amp
l_int|0x1
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;EFI_VARIABLE_NON_VOLATILE&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;Attributes
op_amp
l_int|0x2
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;EFI_VARIABLE_BOOTSERVICE_ACCESS&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;Attributes
op_amp
l_int|0x4
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;EFI_VARIABLE_RUNTIME_ACCESS&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|str
op_minus
id|buf
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|efivar_size_read
id|efivar_size_read
c_func
(paren
r_struct
id|efivar_entry
op_star
id|entry
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|efi_variable
op_star
id|var
op_assign
op_amp
id|entry-&gt;var
suffix:semicolon
r_char
op_star
id|str
op_assign
id|buf
suffix:semicolon
id|efi_status_t
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
op_logical_or
op_logical_neg
id|buf
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|status
op_assign
id|get_var_data
c_func
(paren
id|var
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|EFI_SUCCESS
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;0x%lx&bslash;n&quot;
comma
id|var-&gt;DataSize
)paren
suffix:semicolon
r_return
id|str
op_minus
id|buf
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|efivar_data_read
id|efivar_data_read
c_func
(paren
r_struct
id|efivar_entry
op_star
id|entry
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|efi_variable
op_star
id|var
op_assign
op_amp
id|entry-&gt;var
suffix:semicolon
id|efi_status_t
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
op_logical_or
op_logical_neg
id|buf
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|status
op_assign
id|get_var_data
c_func
(paren
id|var
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|EFI_SUCCESS
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|var-&gt;Data
comma
id|var-&gt;DataSize
)paren
suffix:semicolon
r_return
id|var-&gt;DataSize
suffix:semicolon
)brace
multiline_comment|/*&n; * We allow each variable to be edited via rewriting the&n; * entire efi variable structure.&n; */
r_static
id|ssize_t
DECL|function|efivar_store_raw
id|efivar_store_raw
c_func
(paren
r_struct
id|efivar_entry
op_star
id|entry
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|efi_variable
op_star
id|new_var
comma
op_star
id|var
op_assign
op_amp
id|entry-&gt;var
suffix:semicolon
id|efi_status_t
id|status
op_assign
id|EFI_NOT_FOUND
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
r_sizeof
(paren
r_struct
id|efi_variable
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|new_var
op_assign
(paren
r_struct
id|efi_variable
op_star
)paren
id|buf
suffix:semicolon
multiline_comment|/*&n;&t; * If only updating the variable data, then the name&n;&t; * and guid should remain the same&n;&t; */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|new_var-&gt;VariableName
comma
id|var-&gt;VariableName
comma
r_sizeof
(paren
id|var-&gt;VariableName
)paren
)paren
op_logical_or
id|efi_guidcmp
c_func
(paren
id|new_var-&gt;VendorGuid
comma
id|var-&gt;VendorGuid
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;efivars: Cannot edit the wrong variable!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|new_var-&gt;DataSize
op_le
l_int|0
)paren
op_logical_or
(paren
id|new_var-&gt;Attributes
op_eq
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;efivars: DataSize &amp; Attributes must be valid!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
id|status
op_assign
id|efi
dot
id|set_variable
c_func
(paren
id|new_var-&gt;VariableName
comma
op_amp
id|new_var-&gt;VendorGuid
comma
id|new_var-&gt;Attributes
comma
id|new_var-&gt;DataSize
comma
id|new_var-&gt;Data
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|EFI_SUCCESS
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;efivars: set_variable() failed: status=%lx&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|entry-&gt;var
comma
id|new_var
comma
id|count
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|efivar_show_raw
id|efivar_show_raw
c_func
(paren
r_struct
id|efivar_entry
op_star
id|entry
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|efi_variable
op_star
id|var
op_assign
op_amp
id|entry-&gt;var
suffix:semicolon
id|efi_status_t
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
op_logical_or
op_logical_neg
id|buf
)paren
r_return
l_int|0
suffix:semicolon
id|status
op_assign
id|get_var_data
c_func
(paren
id|var
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|EFI_SUCCESS
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|var
comma
r_sizeof
(paren
op_star
id|var
)paren
)paren
suffix:semicolon
r_return
r_sizeof
(paren
op_star
id|var
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic read/write functions that call the specific functions of&n; * the atttributes...&n; */
DECL|function|efivar_attr_show
r_static
id|ssize_t
id|efivar_attr_show
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|efivar_entry
op_star
id|var
op_assign
id|to_efivar_entry
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|efivar_attribute
op_star
id|efivar_attr
op_assign
id|to_efivar_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|efivar_attr-&gt;show
)paren
(brace
id|ret
op_assign
id|efivar_attr
op_member_access_from_pointer
id|show
c_func
(paren
id|var
comma
id|buf
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|efivar_attr_store
r_static
id|ssize_t
id|efivar_attr_store
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|efivar_entry
op_star
id|var
op_assign
id|to_efivar_entry
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|efivar_attribute
op_star
id|efivar_attr
op_assign
id|to_efivar_attr
c_func
(paren
id|attr
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|efivar_attr-&gt;store
)paren
id|ret
op_assign
id|efivar_attr
op_member_access_from_pointer
id|store
c_func
(paren
id|var
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|efivar_attr_ops
r_static
r_struct
id|sysfs_ops
id|efivar_attr_ops
op_assign
(brace
dot
id|show
op_assign
id|efivar_attr_show
comma
dot
id|store
op_assign
id|efivar_attr_store
comma
)brace
suffix:semicolon
DECL|function|efivar_release
r_static
r_void
id|efivar_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|efivar_entry
op_star
id|var
op_assign
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|efivar_entry
comma
id|kobj
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|var-&gt;list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|var
)paren
suffix:semicolon
)brace
r_static
id|EFIVAR_ATTR
c_func
(paren
id|guid
comma
l_int|0400
comma
id|efivar_guid_read
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|EFIVAR_ATTR
c_func
(paren
id|attributes
comma
l_int|0400
comma
id|efivar_attr_read
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|EFIVAR_ATTR
c_func
(paren
id|size
comma
l_int|0400
comma
id|efivar_size_read
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|EFIVAR_ATTR
c_func
(paren
id|data
comma
l_int|0400
comma
id|efivar_data_read
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|EFIVAR_ATTR
c_func
(paren
id|raw_var
comma
l_int|0600
comma
id|efivar_show_raw
comma
id|efivar_store_raw
)paren
suffix:semicolon
DECL|variable|def_attrs
r_static
r_struct
id|attribute
op_star
id|def_attrs
(braket
)braket
op_assign
(brace
op_amp
id|efivar_attr_guid.attr
comma
op_amp
id|efivar_attr_size.attr
comma
op_amp
id|efivar_attr_attributes.attr
comma
op_amp
id|efivar_attr_data.attr
comma
op_amp
id|efivar_attr_raw_var.attr
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|ktype_efivar
r_static
r_struct
id|kobj_type
id|ktype_efivar
op_assign
(brace
dot
id|release
op_assign
id|efivar_release
comma
dot
id|sysfs_ops
op_assign
op_amp
id|efivar_attr_ops
comma
dot
id|default_attrs
op_assign
id|def_attrs
comma
)brace
suffix:semicolon
r_static
id|ssize_t
DECL|function|dummy
id|dummy
c_func
(paren
r_struct
id|subsystem
op_star
id|sub
comma
r_char
op_star
id|buf
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|efivar_unregister
id|efivar_unregister
c_func
(paren
r_struct
id|efivar_entry
op_star
id|var
)paren
(brace
id|kobject_unregister
c_func
(paren
op_amp
id|var-&gt;kobj
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|efivar_create
id|efivar_create
c_func
(paren
r_struct
id|subsystem
op_star
id|sub
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|efi_variable
op_star
id|new_var
op_assign
(paren
r_struct
id|efi_variable
op_star
)paren
id|buf
suffix:semicolon
r_struct
id|efivar_entry
op_star
id|search_efivar
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|strsize1
comma
id|strsize2
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|n
suffix:semicolon
id|efi_status_t
id|status
op_assign
id|EFI_NOT_FOUND
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Does this variable already exist?&n;&t; */
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|n
comma
op_amp
id|efivar_list
)paren
(brace
id|search_efivar
op_assign
id|get_efivar_entry
c_func
(paren
id|pos
)paren
suffix:semicolon
id|strsize1
op_assign
id|utf8_strsize
c_func
(paren
id|search_efivar-&gt;var.VariableName
comma
l_int|1024
)paren
suffix:semicolon
id|strsize2
op_assign
id|utf8_strsize
c_func
(paren
id|new_var-&gt;VariableName
comma
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strsize1
op_eq
id|strsize2
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
op_amp
(paren
id|search_efivar-&gt;var.VariableName
)paren
comma
id|new_var-&gt;VariableName
comma
id|strsize1
)paren
op_logical_and
op_logical_neg
id|efi_guidcmp
c_func
(paren
id|search_efivar-&gt;var.VendorGuid
comma
id|new_var-&gt;VendorGuid
)paren
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|found
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* now *really* create the variable via EFI */
id|status
op_assign
id|efi
dot
id|set_variable
c_func
(paren
id|new_var-&gt;VariableName
comma
op_amp
id|new_var-&gt;VendorGuid
comma
id|new_var-&gt;Attributes
comma
id|new_var-&gt;DataSize
comma
id|new_var-&gt;Data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|EFI_SUCCESS
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;efivars: set_variable() failed: status=%lx&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
multiline_comment|/* Create the entry in sysfs.  Locking is not required here */
id|status
op_assign
id|efivar_create_sysfs_entry
c_func
(paren
id|utf8_strsize
c_func
(paren
id|new_var-&gt;VariableName
comma
l_int|1024
)paren
comma
id|new_var-&gt;VariableName
comma
op_amp
id|new_var-&gt;VendorGuid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;efivars: variable created, but sysfs entry wasn&squot;t.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|efivar_delete
id|efivar_delete
c_func
(paren
r_struct
id|subsystem
op_star
id|sub
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|efi_variable
op_star
id|del_var
op_assign
(paren
r_struct
id|efi_variable
op_star
)paren
id|buf
suffix:semicolon
r_struct
id|efivar_entry
op_star
id|search_efivar
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|strsize1
comma
id|strsize2
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|n
suffix:semicolon
id|efi_status_t
id|status
op_assign
id|EFI_NOT_FOUND
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Does this variable already exist?&n;&t; */
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|n
comma
op_amp
id|efivar_list
)paren
(brace
id|search_efivar
op_assign
id|get_efivar_entry
c_func
(paren
id|pos
)paren
suffix:semicolon
id|strsize1
op_assign
id|utf8_strsize
c_func
(paren
id|search_efivar-&gt;var.VariableName
comma
l_int|1024
)paren
suffix:semicolon
id|strsize2
op_assign
id|utf8_strsize
c_func
(paren
id|del_var-&gt;VariableName
comma
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strsize1
op_eq
id|strsize2
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
op_amp
(paren
id|search_efivar-&gt;var.VariableName
)paren
comma
id|del_var-&gt;VariableName
comma
id|strsize1
)paren
op_logical_and
op_logical_neg
id|efi_guidcmp
c_func
(paren
id|search_efivar-&gt;var.VendorGuid
comma
id|del_var-&gt;VendorGuid
)paren
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* force the Attributes/DataSize to 0 to ensure deletion */
id|del_var-&gt;Attributes
op_assign
l_int|0
suffix:semicolon
id|del_var-&gt;DataSize
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|efi
dot
id|set_variable
c_func
(paren
id|del_var-&gt;VariableName
comma
op_amp
id|del_var-&gt;VendorGuid
comma
id|del_var-&gt;Attributes
comma
id|del_var-&gt;DataSize
comma
id|del_var-&gt;Data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|EFI_SUCCESS
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;efivars: set_variable() failed: status=%lx&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* We need to release this lock before unregistering. */
id|spin_unlock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
id|efivar_unregister
c_func
(paren
id|search_efivar
)paren
suffix:semicolon
multiline_comment|/* It&squot;s dead Jim.... */
r_return
id|count
suffix:semicolon
)brace
r_static
id|VAR_SUBSYS_ATTR
c_func
(paren
id|new_var
comma
l_int|0200
comma
id|dummy
comma
id|efivar_create
)paren
suffix:semicolon
r_static
id|VAR_SUBSYS_ATTR
c_func
(paren
id|del_var
comma
l_int|0200
comma
id|dummy
comma
id|efivar_delete
)paren
suffix:semicolon
DECL|variable|var_subsys_attrs
r_static
r_struct
id|subsys_attribute
op_star
id|var_subsys_attrs
(braket
)braket
op_assign
(brace
op_amp
id|var_subsys_attr_new_var
comma
op_amp
id|var_subsys_attr_del_var
comma
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Let&squot;s not leave out systab information that snuck into&n; * the efivars driver&n; */
r_static
id|ssize_t
DECL|function|systab_read
id|systab_read
c_func
(paren
r_struct
id|subsystem
op_star
id|entry
comma
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|str
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
op_logical_or
op_logical_neg
id|buf
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|efi.mps
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;MPS=0x%lx&bslash;n&quot;
comma
id|__pa
c_func
(paren
id|efi.mps
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efi.acpi20
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;ACPI20=0x%lx&bslash;n&quot;
comma
id|__pa
c_func
(paren
id|efi.acpi20
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efi.acpi
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;ACPI=0x%lx&bslash;n&quot;
comma
id|__pa
c_func
(paren
id|efi.acpi
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efi.smbios
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;SMBIOS=0x%lx&bslash;n&quot;
comma
id|__pa
c_func
(paren
id|efi.smbios
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efi.hcdp
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;HCDP=0x%lx&bslash;n&quot;
comma
id|__pa
c_func
(paren
id|efi.hcdp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efi.boot_info
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;BOOTINFO=0x%lx&bslash;n&quot;
comma
id|__pa
c_func
(paren
id|efi.boot_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efi.uga
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;UGA=0x%lx&bslash;n&quot;
comma
id|__pa
c_func
(paren
id|efi.uga
)paren
)paren
suffix:semicolon
r_return
id|str
op_minus
id|buf
suffix:semicolon
)brace
r_static
id|EFI_ATTR
c_func
(paren
id|systab
comma
l_int|0400
comma
id|systab_read
comma
l_int|NULL
)paren
suffix:semicolon
DECL|variable|efi_subsys_attrs
r_static
r_struct
id|subsys_attribute
op_star
id|efi_subsys_attrs
(braket
)braket
op_assign
(brace
op_amp
id|efi_attr_systab
comma
l_int|NULL
comma
multiline_comment|/* maybe more in the future? */
)brace
suffix:semicolon
DECL|variable|decl_subsys
r_static
id|decl_subsys
c_func
(paren
id|vars
comma
op_amp
id|ktype_efivar
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|decl_subsys
c_func
(paren
id|efi
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n; * efivar_create_sysfs_entry()&n; * Requires:&n; *    variable_name_size = number of bytes required to hold&n; *                         variable_name (not counting the NULL&n; *                         character at the end.&n; *    efivars_lock is not held on entry or exit.&n; * Returns 1 on failure, 0 on success&n; */
r_static
r_int
DECL|function|efivar_create_sysfs_entry
id|efivar_create_sysfs_entry
c_func
(paren
r_int
r_int
id|variable_name_size
comma
id|efi_char16_t
op_star
id|variable_name
comma
id|efi_guid_t
op_star
id|vendor_guid
)paren
(brace
r_int
id|i
comma
id|short_name_size
op_assign
id|variable_name_size
op_div
r_sizeof
(paren
id|efi_char16_t
)paren
op_plus
l_int|38
suffix:semicolon
r_char
op_star
id|short_name
suffix:semicolon
r_struct
id|efivar_entry
op_star
id|new_efivar
suffix:semicolon
id|short_name
op_assign
id|kmalloc
c_func
(paren
id|short_name_size
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|new_efivar
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|efivar_entry
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|short_name
op_logical_or
op_logical_neg
id|new_efivar
)paren
(brace
r_if
c_cond
(paren
id|short_name
)paren
id|kfree
c_func
(paren
id|short_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_efivar
)paren
id|kfree
c_func
(paren
id|new_efivar
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
id|short_name
comma
l_int|0
comma
id|short_name_size
op_plus
l_int|1
)paren
suffix:semicolon
id|memset
c_func
(paren
id|new_efivar
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|efivar_entry
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|new_efivar-&gt;var.VariableName
comma
id|variable_name
comma
id|variable_name_size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
(paren
id|new_efivar-&gt;var.VendorGuid
)paren
comma
id|vendor_guid
comma
r_sizeof
(paren
id|efi_guid_t
)paren
)paren
suffix:semicolon
multiline_comment|/* Convert Unicode to normal chars (assume top bits are 0),&n;&t;   ala UTF-8 */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_int
)paren
(paren
id|variable_name_size
op_div
r_sizeof
(paren
id|efi_char16_t
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|short_name
(braket
id|i
)braket
op_assign
id|variable_name
(braket
id|i
)braket
op_amp
l_int|0xFF
suffix:semicolon
)brace
multiline_comment|/* This is ugly, but necessary to separate one vendor&squot;s&n;&t;   private variables from another&squot;s.         */
op_star
(paren
id|short_name
op_plus
id|strlen
c_func
(paren
id|short_name
)paren
)paren
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|efi_guid_unparse
c_func
(paren
id|vendor_guid
comma
id|short_name
op_plus
id|strlen
c_func
(paren
id|short_name
)paren
)paren
suffix:semicolon
id|kobject_set_name
c_func
(paren
op_amp
id|new_efivar-&gt;kobj
comma
l_string|&quot;%s&quot;
comma
id|short_name
)paren
suffix:semicolon
id|kobj_set_kset_s
c_func
(paren
id|new_efivar
comma
id|vars_subsys
)paren
suffix:semicolon
id|kobject_register
c_func
(paren
op_amp
id|new_efivar-&gt;kobj
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|short_name
)paren
suffix:semicolon
id|short_name
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|new_efivar-&gt;list
comma
op_amp
id|efivar_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|efivars_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * For now we register the efi subsystem with the firmware subsystem&n; * and the vars subsystem with the efi subsystem.  In the future, it&n; * might make sense to split off the efi subsystem into its own&n; * driver, but for now only efivars will register with it, so just&n; * include it here.&n; */
r_static
r_int
id|__init
DECL|function|efivars_init
id|efivars_init
c_func
(paren
r_void
)paren
(brace
id|efi_status_t
id|status
op_assign
id|EFI_NOT_FOUND
suffix:semicolon
id|efi_guid_t
id|vendor_guid
suffix:semicolon
id|efi_char16_t
op_star
id|variable_name
op_assign
id|kmalloc
c_func
(paren
l_int|1024
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_struct
id|subsys_attribute
op_star
id|attr
suffix:semicolon
r_int
r_int
id|variable_name_size
op_assign
l_int|1024
suffix:semicolon
r_int
id|i
comma
id|rc
op_assign
l_int|0
comma
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|efi_enabled
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;EFI Variables Facility v%s %s&bslash;n&quot;
comma
id|EFIVARS_VERSION
comma
id|EFIVARS_DATE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * For now we&squot;ll register the efi subsys within this driver&n;&t; */
id|rc
op_assign
id|firmware_register
c_func
(paren
op_amp
id|efi_subsys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|kset_set_kset_s
c_func
(paren
op_amp
id|vars_subsys
comma
id|efi_subsys
)paren
suffix:semicolon
id|subsystem_register
c_func
(paren
op_amp
id|vars_subsys
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Per EFI spec, the maximum storage allocated for both&n;&t; * the variable name and variable data is 1024 bytes.&n;&t; */
id|memset
c_func
(paren
id|variable_name
comma
l_int|0
comma
l_int|1024
)paren
suffix:semicolon
r_do
(brace
id|variable_name_size
op_assign
l_int|1024
suffix:semicolon
id|status
op_assign
id|efi
dot
id|get_next_variable
c_func
(paren
op_amp
id|variable_name_size
comma
id|variable_name
comma
op_amp
id|vendor_guid
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|EFI_SUCCESS
suffix:colon
id|efivar_create_sysfs_entry
c_func
(paren
id|variable_name_size
comma
id|variable_name
comma
op_amp
id|vendor_guid
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EFI_NOT_FOUND
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;efivars: get_next_variable: status=%lx&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|status
op_assign
id|EFI_NOT_FOUND
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|status
op_ne
id|EFI_NOT_FOUND
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now add attributes to allow creation of new vars&n;&t; * and deletion of existing ones...&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|attr
op_assign
id|var_subsys_attrs
(braket
id|i
)braket
)paren
op_logical_and
op_logical_neg
id|error
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|attr-&gt;show
op_logical_and
id|attr-&gt;store
)paren
id|error
op_assign
id|subsys_create_file
c_func
(paren
op_amp
id|vars_subsys
comma
id|attr
)paren
suffix:semicolon
)brace
multiline_comment|/* Don&squot;t forget the systab entry */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|attr
op_assign
id|efi_subsys_attrs
(braket
id|i
)braket
)paren
op_logical_and
op_logical_neg
id|error
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|attr-&gt;show
)paren
id|error
op_assign
id|subsys_create_file
c_func
(paren
op_amp
id|efi_subsys
comma
id|attr
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|variable_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|efivars_exit
id|efivars_exit
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|n
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|n
comma
op_amp
id|efivar_list
)paren
id|efivar_unregister
c_func
(paren
id|get_efivar_entry
c_func
(paren
id|pos
)paren
)paren
suffix:semicolon
id|subsystem_unregister
c_func
(paren
op_amp
id|vars_subsys
)paren
suffix:semicolon
id|firmware_unregister
c_func
(paren
op_amp
id|efi_subsys
)paren
suffix:semicolon
)brace
DECL|variable|efivars_init
id|module_init
c_func
(paren
id|efivars_init
)paren
suffix:semicolon
DECL|variable|efivars_exit
id|module_exit
c_func
(paren
id|efivars_exit
)paren
suffix:semicolon
eof
