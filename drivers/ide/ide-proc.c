multiline_comment|/*&n; *  linux/drivers/ide/ide-proc.c&t;Version 1.05&t;Mar 05, 2003&n; *&n; *  Copyright (C) 1997-1998&t;Mark Lord&n; *  Copyright (C) 2003&t;&t;Red Hat &lt;alan@redhat.com&gt;&n; */
multiline_comment|/*&n; * This is the /proc/ide/ filesystem implementation.&n; *&n; * Drive/Driver settings can be retrieved by reading the drive&squot;s&n; * &quot;settings&quot; files.  e.g.    &quot;cat /proc/ide0/hda/settings&quot;&n; * To write a new value &quot;val&quot; into a specific setting &quot;name&quot;, use:&n; *   echo &quot;name:val&quot; &gt;/proc/ide/ide0/hda/settings&n; *&n; * Also useful, &quot;cat /proc/ide0/hda/[identify, smart_values,&n; * smart_thresholds, capabilities]&quot; will issue an IDENTIFY /&n; * PACKET_IDENTIFY / SMART_READ_VALUES / SMART_READ_THRESHOLDS /&n; * SENSE CAPABILITIES command to /dev/hda, and then dump out the&n; * returned data as 256 16-bit words.  The &quot;hdparm&quot; utility will&n; * be updated someday soon to use this mechanism.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|proc_ide_read_imodel
r_static
r_int
id|proc_ide_read_imodel
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
id|ide_hwif_t
op_star
id|hwif
op_assign
(paren
id|ide_hwif_t
op_star
)paren
id|data
suffix:semicolon
r_int
id|len
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/*&n;&t; * Neither ide_unknown nor ide_forced should be set at this point.&n;&t; */
r_switch
c_cond
(paren
id|hwif-&gt;chipset
)paren
(brace
r_case
id|ide_generic
suffix:colon
id|name
op_assign
l_string|&quot;generic&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_pci
suffix:colon
id|name
op_assign
l_string|&quot;pci&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_cmd640
suffix:colon
id|name
op_assign
l_string|&quot;cmd640&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_dtc2278
suffix:colon
id|name
op_assign
l_string|&quot;dtc2278&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_ali14xx
suffix:colon
id|name
op_assign
l_string|&quot;ali14xx&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_qd65xx
suffix:colon
id|name
op_assign
l_string|&quot;qd65xx&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_umc8672
suffix:colon
id|name
op_assign
l_string|&quot;umc8672&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_ht6560b
suffix:colon
id|name
op_assign
l_string|&quot;ht6560b&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_rz1000
suffix:colon
id|name
op_assign
l_string|&quot;rz1000&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_trm290
suffix:colon
id|name
op_assign
l_string|&quot;trm290&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_cmd646
suffix:colon
id|name
op_assign
l_string|&quot;cmd646&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_cy82c693
suffix:colon
id|name
op_assign
l_string|&quot;cy82c693&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_4drives
suffix:colon
id|name
op_assign
l_string|&quot;4drives&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_pmac
suffix:colon
id|name
op_assign
l_string|&quot;mac-io&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|name
op_assign
l_string|&quot;(unknown)&quot;
suffix:semicolon
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
l_string|&quot;%s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|PROC_IDE_READ_RETURN
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
)brace
DECL|function|proc_ide_read_mate
r_static
r_int
id|proc_ide_read_mate
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
id|ide_hwif_t
op_star
id|hwif
op_assign
(paren
id|ide_hwif_t
op_star
)paren
id|data
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|hwif
op_logical_and
id|hwif-&gt;mate
op_logical_and
id|hwif-&gt;mate-&gt;present
)paren
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|hwif-&gt;mate-&gt;name
)paren
suffix:semicolon
r_else
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;(none)&bslash;n&quot;
)paren
suffix:semicolon
id|PROC_IDE_READ_RETURN
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
)brace
DECL|function|proc_ide_read_channel
r_static
r_int
id|proc_ide_read_channel
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
id|ide_hwif_t
op_star
id|hwif
op_assign
(paren
id|ide_hwif_t
op_star
)paren
id|data
suffix:semicolon
r_int
id|len
suffix:semicolon
id|page
(braket
l_int|0
)braket
op_assign
id|hwif-&gt;channel
ques
c_cond
l_char|&squot;1&squot;
suffix:colon
l_char|&squot;0&squot;
suffix:semicolon
id|page
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|len
op_assign
l_int|2
suffix:semicolon
id|PROC_IDE_READ_RETURN
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
)brace
DECL|function|proc_ide_read_identify
r_static
r_int
id|proc_ide_read_identify
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
id|ide_drive_t
op_star
id|drive
op_assign
(paren
id|ide_drive_t
op_star
)paren
id|data
suffix:semicolon
r_int
id|len
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive
)paren
(brace
r_int
r_int
op_star
id|val
op_assign
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|drive-&gt;driver
)paren
suffix:semicolon
id|err
op_assign
id|taskfile_lib_get_identify
c_func
(paren
id|drive
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
r_char
op_star
id|out
op_assign
(paren
(paren
r_char
op_star
)paren
id|page
)paren
op_plus
(paren
id|SECTOR_WORDS
op_star
l_int|4
)paren
suffix:semicolon
id|page
op_assign
id|out
suffix:semicolon
r_do
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%04x%c&quot;
comma
id|le16_to_cpu
c_func
(paren
op_star
id|val
)paren
comma
(paren
op_increment
id|i
op_amp
l_int|7
)paren
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|val
op_add_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
(paren
id|SECTOR_WORDS
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|len
op_assign
id|out
op_minus
id|page
suffix:semicolon
)brace
)brace
id|PROC_IDE_READ_RETURN
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
)brace
DECL|function|proc_ide_settings_warn
r_static
r_void
id|proc_ide_settings_warn
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|warned
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|warned
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning: /proc/ide/hd?/settings interface is &quot;
l_string|&quot;obsolete, and will be removed soon!&bslash;n&quot;
)paren
suffix:semicolon
id|warned
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|proc_ide_read_settings
r_static
r_int
id|proc_ide_read_settings
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
id|ide_drive_t
op_star
id|drive
op_assign
(paren
id|ide_drive_t
op_star
)paren
id|data
suffix:semicolon
id|ide_settings_t
op_star
id|setting
op_assign
(paren
id|ide_settings_t
op_star
)paren
id|drive-&gt;settings
suffix:semicolon
r_char
op_star
id|out
op_assign
id|page
suffix:semicolon
r_int
id|len
comma
id|rc
comma
id|mul_factor
comma
id|div_factor
suffix:semicolon
id|proc_ide_settings_warn
c_func
(paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ide_setting_sem
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;name&bslash;t&bslash;t&bslash;tvalue&bslash;t&bslash;tmin&bslash;t&bslash;tmax&bslash;t&bslash;tmode&bslash;n&quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;----&bslash;t&bslash;t&bslash;t-----&bslash;t&bslash;t---&bslash;t&bslash;t---&bslash;t&bslash;t----&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|setting
)paren
(brace
id|mul_factor
op_assign
id|setting-&gt;mul_factor
suffix:semicolon
id|div_factor
op_assign
id|setting-&gt;div_factor
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%-24s&quot;
comma
id|setting-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|ide_read_setting
c_func
(paren
id|drive
comma
id|setting
)paren
)paren
op_ge
l_int|0
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%-16d&quot;
comma
id|rc
op_star
id|mul_factor
op_div
id|div_factor
)paren
suffix:semicolon
r_else
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%-16s&quot;
comma
l_string|&quot;write-only&quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;%-16d%-16d&quot;
comma
(paren
id|setting-&gt;min
op_star
id|mul_factor
op_plus
id|div_factor
op_minus
l_int|1
)paren
op_div
id|div_factor
comma
id|setting-&gt;max
op_star
id|mul_factor
op_div
id|div_factor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setting-&gt;rw
op_amp
id|SETTING_READ
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setting-&gt;rw
op_amp
id|SETTING_WRITE
)paren
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|setting
op_assign
id|setting-&gt;next
suffix:semicolon
)brace
id|len
op_assign
id|out
op_minus
id|page
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ide_setting_sem
)paren
suffix:semicolon
id|PROC_IDE_READ_RETURN
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
)brace
DECL|macro|MAX_LEN
mdefine_line|#define MAX_LEN&t;30
DECL|function|proc_ide_write_settings
r_static
r_int
id|proc_ide_write_settings
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
id|ide_drive_t
op_star
id|drive
op_assign
(paren
id|ide_drive_t
op_star
)paren
id|data
suffix:semicolon
r_char
id|name
(braket
id|MAX_LEN
op_plus
l_int|1
)braket
suffix:semicolon
r_int
id|for_real
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
id|ide_settings_t
op_star
id|setting
suffix:semicolon
r_char
op_star
id|buf
comma
op_star
id|s
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
id|proc_ide_settings_warn
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
id|PAGE_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|s
op_assign
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
(brace
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
op_minus
id|EFAULT
suffix:semicolon
)brace
id|buf
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/*&n;&t; * Skip over leading whitespace&n;&t; */
r_while
c_loop
(paren
id|count
op_logical_and
id|isspace
c_func
(paren
op_star
id|s
)paren
)paren
(brace
op_decrement
id|count
suffix:semicolon
op_increment
id|s
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Do one full pass to verify all parameters,&n;&t; * then do another to actually write the new settings.&n;&t; */
r_do
(brace
r_char
op_star
id|p
op_assign
id|s
suffix:semicolon
id|n
op_assign
id|count
suffix:semicolon
r_while
c_loop
(paren
id|n
OG
l_int|0
)paren
(brace
r_int
id|val
suffix:semicolon
r_char
op_star
id|q
op_assign
id|p
suffix:semicolon
r_while
c_loop
(paren
id|n
OG
l_int|0
op_logical_and
op_star
id|p
op_ne
l_char|&squot;:&squot;
)paren
(brace
op_decrement
id|n
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|p
op_ne
l_char|&squot;:&squot;
)paren
r_goto
id|parse_error
suffix:semicolon
r_if
c_cond
(paren
id|p
op_minus
id|q
OG
id|MAX_LEN
)paren
r_goto
id|parse_error
suffix:semicolon
id|memcpy
c_func
(paren
id|name
comma
id|q
comma
id|p
op_minus
id|q
)paren
suffix:semicolon
id|name
(braket
id|p
op_minus
id|q
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|0
)paren
(brace
op_decrement
id|n
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
r_else
r_goto
id|parse_error
suffix:semicolon
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
op_amp
id|q
comma
l_int|10
)paren
suffix:semicolon
id|n
op_sub_assign
id|q
op_minus
id|p
suffix:semicolon
id|p
op_assign
id|q
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|0
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
op_star
id|p
)paren
)paren
r_goto
id|parse_error
suffix:semicolon
r_while
c_loop
(paren
id|n
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
op_star
id|p
)paren
)paren
(brace
op_decrement
id|n
suffix:semicolon
op_increment
id|p
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|ide_setting_sem
)paren
suffix:semicolon
id|setting
op_assign
id|ide_find_setting_by_name
c_func
(paren
id|drive
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|setting
)paren
(brace
id|up
c_func
(paren
op_amp
id|ide_setting_sem
)paren
suffix:semicolon
r_goto
id|parse_error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|for_real
)paren
id|ide_write_setting
c_func
(paren
id|drive
comma
id|setting
comma
id|val
op_star
id|setting-&gt;div_factor
op_div
id|setting-&gt;mul_factor
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ide_setting_sem
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
id|for_real
op_increment
)paren
suffix:semicolon
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
id|count
suffix:semicolon
id|parse_error
suffix:colon
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
id|printk
c_func
(paren
l_string|&quot;proc_ide_write_settings(): parse error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|proc_ide_read_capacity
r_int
id|proc_ide_read_capacity
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
id|ide_drive_t
op_star
id|drive
op_assign
(paren
id|ide_drive_t
op_star
)paren
id|data
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%llu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
(paren
id|DRIVER
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|capacity
c_func
(paren
id|drive
)paren
)paren
)paren
suffix:semicolon
id|PROC_IDE_READ_RETURN
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
)brace
DECL|function|proc_ide_read_geometry
r_int
id|proc_ide_read_geometry
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
id|ide_drive_t
op_star
id|drive
op_assign
(paren
id|ide_drive_t
op_star
)paren
id|data
suffix:semicolon
r_char
op_star
id|out
op_assign
id|page
suffix:semicolon
r_int
id|len
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;physical     %d/%d/%d&bslash;n&quot;
comma
id|drive-&gt;cyl
comma
id|drive-&gt;head
comma
id|drive-&gt;sect
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;logical      %d/%d/%d&bslash;n&quot;
comma
id|drive-&gt;bios_cyl
comma
id|drive-&gt;bios_head
comma
id|drive-&gt;bios_sect
)paren
suffix:semicolon
id|len
op_assign
id|out
op_minus
id|page
suffix:semicolon
id|PROC_IDE_READ_RETURN
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
)brace
DECL|variable|proc_ide_read_geometry
id|EXPORT_SYMBOL
c_func
(paren
id|proc_ide_read_geometry
)paren
suffix:semicolon
DECL|function|proc_ide_read_dmodel
r_static
r_int
id|proc_ide_read_dmodel
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
id|ide_drive_t
op_star
id|drive
op_assign
(paren
id|ide_drive_t
op_star
)paren
id|data
suffix:semicolon
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%.40s&bslash;n&quot;
comma
(paren
id|id
op_logical_and
id|id-&gt;model
(braket
l_int|0
)braket
)paren
ques
c_cond
(paren
r_char
op_star
)paren
id|id-&gt;model
suffix:colon
l_string|&quot;(none)&quot;
)paren
suffix:semicolon
id|PROC_IDE_READ_RETURN
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
)brace
DECL|function|proc_ide_read_driver
r_static
r_int
id|proc_ide_read_driver
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
id|ide_drive_t
op_star
id|drive
op_assign
(paren
id|ide_drive_t
op_star
)paren
id|data
suffix:semicolon
id|ide_driver_t
op_star
id|driver
op_assign
id|drive-&gt;driver
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%s version %s&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|driver-&gt;version
)paren
suffix:semicolon
id|PROC_IDE_READ_RETURN
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
)brace
DECL|function|proc_ide_write_driver
r_static
r_int
id|proc_ide_write_driver
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
id|ide_drive_t
op_star
id|drive
op_assign
(paren
id|ide_drive_t
op_star
)paren
id|data
suffix:semicolon
r_char
id|name
(braket
l_int|32
)braket
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
id|count
OG
l_int|31
)paren
id|count
op_assign
l_int|31
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|name
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|name
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|ide_replace_subdriver
c_func
(paren
id|drive
comma
id|name
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|proc_ide_read_media
r_static
r_int
id|proc_ide_read_media
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
id|ide_drive_t
op_star
id|drive
op_assign
(paren
id|ide_drive_t
op_star
)paren
id|data
suffix:semicolon
r_const
r_char
op_star
id|media
suffix:semicolon
r_int
id|len
suffix:semicolon
r_switch
c_cond
(paren
id|drive-&gt;media
)paren
(brace
r_case
id|ide_disk
suffix:colon
id|media
op_assign
l_string|&quot;disk&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_cdrom
suffix:colon
id|media
op_assign
l_string|&quot;cdrom&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_tape
suffix:colon
id|media
op_assign
l_string|&quot;tape&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_floppy
suffix:colon
id|media
op_assign
l_string|&quot;floppy&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|media
op_assign
l_string|&quot;UNKNOWN&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|page
comma
id|media
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|media
)paren
suffix:semicolon
id|PROC_IDE_READ_RETURN
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
)brace
DECL|variable|generic_drive_entries
r_static
id|ide_proc_entry_t
id|generic_drive_entries
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;driver&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
id|proc_ide_read_driver
comma
id|proc_ide_write_driver
)brace
comma
(brace
l_string|&quot;identify&quot;
comma
id|S_IFREG
op_or
id|S_IRUSR
comma
id|proc_ide_read_identify
comma
l_int|NULL
)brace
comma
(brace
l_string|&quot;media&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
id|proc_ide_read_media
comma
l_int|NULL
)brace
comma
(brace
l_string|&quot;model&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
id|proc_ide_read_dmodel
comma
l_int|NULL
)brace
comma
(brace
l_string|&quot;settings&quot;
comma
id|S_IFREG
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|proc_ide_read_settings
comma
id|proc_ide_write_settings
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|ide_add_proc_entries
r_void
id|ide_add_proc_entries
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|dir
comma
id|ide_proc_entry_t
op_star
id|p
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
op_logical_neg
id|p
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|p-&gt;name
op_ne
l_int|NULL
)paren
(brace
id|ent
op_assign
id|create_proc_entry
c_func
(paren
id|p-&gt;name
comma
id|p-&gt;mode
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
suffix:semicolon
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;data
op_assign
id|data
suffix:semicolon
id|ent-&gt;read_proc
op_assign
id|p-&gt;read_proc
suffix:semicolon
id|ent-&gt;write_proc
op_assign
id|p-&gt;write_proc
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
)brace
DECL|function|ide_remove_proc_entries
r_void
id|ide_remove_proc_entries
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|dir
comma
id|ide_proc_entry_t
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
op_logical_neg
id|p
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|p-&gt;name
op_ne
l_int|NULL
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|p-&gt;name
comma
id|dir
)paren
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
)brace
DECL|function|create_proc_ide_drives
r_static
r_void
id|create_proc_ide_drives
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_int
id|d
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|parent
op_assign
id|hwif-&gt;proc
suffix:semicolon
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
l_int|0
suffix:semicolon
id|d
OL
id|MAX_DRIVES
suffix:semicolon
id|d
op_increment
)paren
(brace
id|ide_drive_t
op_star
id|drive
op_assign
op_amp
id|hwif-&gt;drives
(braket
id|d
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;present
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;proc
)paren
r_continue
suffix:semicolon
id|drive-&gt;proc
op_assign
id|proc_mkdir
c_func
(paren
id|drive-&gt;name
comma
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;proc
)paren
id|ide_add_proc_entries
c_func
(paren
id|drive-&gt;proc
comma
id|generic_drive_entries
comma
id|drive
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;ide%d/%s&quot;
comma
(paren
id|drive-&gt;name
(braket
l_int|2
)braket
op_minus
l_char|&squot;a&squot;
)paren
op_div
l_int|2
comma
id|drive-&gt;name
)paren
suffix:semicolon
id|ent
op_assign
id|proc_symlink
c_func
(paren
id|drive-&gt;name
comma
id|proc_ide_root
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
suffix:semicolon
)brace
)brace
DECL|function|destroy_proc_ide_device
r_static
r_void
id|destroy_proc_ide_device
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
comma
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_driver_t
op_star
id|driver
op_assign
id|drive-&gt;driver
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;proc
)paren
(brace
id|ide_remove_proc_entries
c_func
(paren
id|drive-&gt;proc
comma
id|driver-&gt;proc
)paren
suffix:semicolon
id|ide_remove_proc_entries
c_func
(paren
id|drive-&gt;proc
comma
id|generic_drive_entries
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|drive-&gt;name
comma
id|proc_ide_root
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|drive-&gt;name
comma
id|hwif-&gt;proc
)paren
suffix:semicolon
id|drive-&gt;proc
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|destroy_proc_ide_drives
r_static
r_void
id|destroy_proc_ide_drives
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_int
id|d
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
l_int|0
suffix:semicolon
id|d
OL
id|MAX_DRIVES
suffix:semicolon
id|d
op_increment
)paren
(brace
id|ide_drive_t
op_star
id|drive
op_assign
op_amp
id|hwif-&gt;drives
(braket
id|d
)braket
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;proc
)paren
id|destroy_proc_ide_device
c_func
(paren
id|hwif
comma
id|drive
)paren
suffix:semicolon
)brace
)brace
DECL|variable|hwif_entries
r_static
id|ide_proc_entry_t
id|hwif_entries
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;channel&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
id|proc_ide_read_channel
comma
l_int|NULL
)brace
comma
(brace
l_string|&quot;mate&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
id|proc_ide_read_mate
comma
l_int|NULL
)brace
comma
(brace
l_string|&quot;model&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
id|proc_ide_read_imodel
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|create_proc_ide_interfaces
r_void
id|create_proc_ide_interfaces
c_func
(paren
r_void
)paren
(brace
r_int
id|h
suffix:semicolon
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
id|MAX_HWIFS
suffix:semicolon
id|h
op_increment
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
op_amp
id|ide_hwifs
(braket
id|h
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;present
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;proc
)paren
(brace
id|hwif-&gt;proc
op_assign
id|proc_mkdir
c_func
(paren
id|hwif-&gt;name
comma
id|proc_ide_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;proc
)paren
r_return
suffix:semicolon
id|ide_add_proc_entries
c_func
(paren
id|hwif-&gt;proc
comma
id|hwif_entries
comma
id|hwif
)paren
suffix:semicolon
)brace
id|create_proc_ide_drives
c_func
(paren
id|hwif
)paren
suffix:semicolon
)brace
)brace
DECL|variable|create_proc_ide_interfaces
id|EXPORT_SYMBOL
c_func
(paren
id|create_proc_ide_interfaces
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEPCI
DECL|function|ide_pci_create_host_proc
r_void
id|ide_pci_create_host_proc
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|get_info_t
op_star
id|get_info
)paren
(brace
id|create_proc_info_entry
c_func
(paren
id|name
comma
l_int|0
comma
id|proc_ide_root
comma
id|get_info
)paren
suffix:semicolon
)brace
DECL|variable|ide_pci_create_host_proc
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|ide_pci_create_host_proc
)paren
suffix:semicolon
macro_line|#endif
DECL|function|destroy_proc_ide_interface
r_void
id|destroy_proc_ide_interface
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_if
c_cond
(paren
id|hwif-&gt;proc
)paren
(brace
id|destroy_proc_ide_drives
c_func
(paren
id|hwif
)paren
suffix:semicolon
id|ide_remove_proc_entries
c_func
(paren
id|hwif-&gt;proc
comma
id|hwif_entries
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|hwif-&gt;name
comma
id|proc_ide_root
)paren
suffix:semicolon
id|hwif-&gt;proc
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_extern
r_struct
id|seq_operations
id|ide_drivers_op
suffix:semicolon
DECL|function|ide_drivers_open
r_static
r_int
id|ide_drivers_open
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
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|ide_drivers_op
)paren
suffix:semicolon
)brace
DECL|variable|ide_drivers_operations
r_static
r_struct
id|file_operations
id|ide_drivers_operations
op_assign
(brace
dot
id|open
op_assign
id|ide_drivers_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
comma
)brace
suffix:semicolon
DECL|function|proc_ide_create
r_void
id|proc_ide_create
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_ide_root
)paren
r_return
suffix:semicolon
id|create_proc_ide_interfaces
c_func
(paren
)paren
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;drivers&quot;
comma
l_int|0
comma
id|proc_ide_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|ide_drivers_operations
suffix:semicolon
)brace
DECL|function|proc_ide_destroy
r_void
id|proc_ide_destroy
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;ide/drivers&quot;
comma
id|proc_ide_root
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;ide&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
