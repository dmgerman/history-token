multiline_comment|/*&n; * Copyright (C) 2003 Christoph Hellwig.&n; *&t;Released under GPL v2.&n; *&n; * Support for old-style host templates.&n; *&n; * NOTE:  Do not use this for new drivers ever.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
DECL|function|init_this_scsi_driver
r_static
r_int
id|__init
id|init_this_scsi_driver
c_func
(paren
r_void
)paren
(brace
id|Scsi_Host_Template
op_star
id|sht
op_assign
op_amp
id|driver_template
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sht-&gt;release
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scsi HBA driver %s didn&squot;t set a release method.&bslash;n&quot;
comma
id|sht-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|sht-&gt;module
op_assign
id|THIS_MODULE
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|sht-&gt;legacy_hosts
)paren
suffix:semicolon
id|sht
op_member_access_from_pointer
id|detect
c_func
(paren
id|sht
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sht-&gt;present
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|shost
comma
op_amp
id|sht-&gt;legacy_hosts
comma
id|sht_legacy_list
)paren
(brace
id|error
op_assign
id|scsi_add_host
c_func
(paren
id|shost
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|l
op_assign
op_amp
id|shost-&gt;sht_legacy_list
suffix:semicolon
r_while
c_loop
(paren
(paren
id|l
op_assign
id|l-&gt;prev
)paren
op_ne
op_amp
id|sht-&gt;legacy_hosts
)paren
id|scsi_remove_host
c_func
(paren
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|Scsi_Host
comma
id|sht_legacy_list
)paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|exit_this_scsi_driver
r_static
r_void
id|__exit
id|exit_this_scsi_driver
c_func
(paren
r_void
)paren
(brace
id|Scsi_Host_Template
op_star
id|sht
op_assign
op_amp
id|driver_template
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shost
comma
op_star
id|s
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|shost
comma
op_amp
id|sht-&gt;legacy_hosts
comma
id|sht_legacy_list
)paren
id|scsi_remove_host
c_func
(paren
id|shost
)paren
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|shost
comma
id|s
comma
op_amp
id|sht-&gt;legacy_hosts
comma
id|sht_legacy_list
)paren
id|sht
op_member_access_from_pointer
id|release
c_func
(paren
id|shost
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|sht-&gt;legacy_hosts
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s did not call scsi_unregister&bslash;n&quot;
comma
id|sht-&gt;name
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|shost
comma
id|s
comma
op_amp
id|sht-&gt;legacy_hosts
comma
id|sht_legacy_list
)paren
id|scsi_unregister
c_func
(paren
id|shost
)paren
suffix:semicolon
)brace
DECL|variable|init_this_scsi_driver
id|module_init
c_func
(paren
id|init_this_scsi_driver
)paren
suffix:semicolon
DECL|variable|exit_this_scsi_driver
id|module_exit
c_func
(paren
id|exit_this_scsi_driver
)paren
suffix:semicolon
eof
