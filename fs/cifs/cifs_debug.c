multiline_comment|/*&n; *   fs/cifs_debug.c&n; *&n; *   Copyright (c) International Business Machines  Corp., 2000,2002&n; *&n; *   Modified by Steve French (sfrench@us.ibm.com)&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot;
macro_line|#include &quot;cifsproto.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
r_void
DECL|function|cifs_dump_mem
id|cifs_dump_mem
c_func
(paren
r_char
op_star
id|label
comma
r_void
op_star
id|data
comma
r_int
id|length
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
op_star
id|intptr
op_assign
id|data
suffix:semicolon
r_char
op_star
id|charptr
op_assign
id|data
suffix:semicolon
r_char
id|buf
(braket
l_int|10
)braket
comma
id|line
(braket
l_int|80
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: dump of %d bytes of data at 0x%p&bslash;n&bslash;n&quot;
comma
id|label
comma
id|length
comma
id|data
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|length
suffix:semicolon
id|i
op_add_assign
l_int|16
)paren
(brace
id|line
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
(paren
id|j
OL
l_int|4
)paren
op_logical_and
(paren
id|i
op_plus
id|j
op_star
l_int|4
OL
id|length
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot; %08x&quot;
comma
id|intptr
(braket
id|i
op_div
l_int|4
op_plus
id|j
)braket
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|line
comma
id|buf
)paren
suffix:semicolon
)brace
id|buf
(braket
l_int|0
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
(paren
id|j
OL
l_int|16
)paren
op_logical_and
(paren
id|i
op_plus
id|j
OL
id|length
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
id|buf
(braket
l_int|1
)braket
op_assign
id|isprint
c_func
(paren
id|charptr
(braket
id|i
op_plus
id|j
)braket
)paren
ques
c_cond
id|charptr
(braket
id|i
op_plus
id|j
)braket
suffix:colon
l_char|&squot;.&squot;
suffix:semicolon
id|strcat
c_func
(paren
id|line
comma
id|buf
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
)brace
)brace
macro_line|#if CONFIG_PROC_FS
r_int
DECL|function|cifs_debug_data_read
id|cifs_debug_data_read
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|beginBuffer
comma
id|off_t
id|offset
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
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|cifsSesInfo
op_star
id|ses
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|tcon
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|length
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|buf_start
op_assign
id|buf
suffix:semicolon
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Display Internal CIFS Data Structures for Debugging&bslash;n&quot;
l_string|&quot;---------------------------------------------------&bslash;n&quot;
)paren
suffix:semicolon
id|buf
op_add_assign
id|length
suffix:semicolon
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Servers: &bslash;n&quot;
)paren
suffix:semicolon
id|buf
op_add_assign
id|length
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|GlobalSMBSessionList
)paren
(brace
id|i
op_increment
suffix:semicolon
id|ses
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|cifsSesInfo
comma
id|cifsSessionList
)paren
suffix:semicolon
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n%d) Name: %s  Domain: %s Mounts: %d ServerOS: %s  ServerNOS: %s&bslash;n&bslash;tCapabilities: 0x%x&quot;
comma
id|i
comma
id|ses-&gt;serverName
comma
id|ses-&gt;serverDomain
comma
id|atomic_read
c_func
(paren
op_amp
id|ses-&gt;inUse
)paren
comma
id|ses-&gt;serverOS
comma
id|ses-&gt;serverNOS
comma
id|ses-&gt;capabilities
)paren
suffix:semicolon
id|buf
op_add_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|ses-&gt;server
)paren
(brace
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;tLocal Users To Same Server: %d &quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|ses-&gt;server-&gt;socketUseCount
)paren
)paren
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;nShares: &bslash;n&quot;
)paren
suffix:semicolon
id|buf
op_add_assign
id|length
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|GlobalTreeConnectionList
)paren
(brace
id|i
op_increment
suffix:semicolon
id|tcon
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|cifsTconInfo
comma
id|cifsConnectionList
)paren
suffix:semicolon
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n%d) %s Uses: %d on FS: %s with characteristics: 0x%x Attributes: 0x%x&bslash;n&bslash;tPathComponentMax: %d&quot;
comma
id|i
comma
id|tcon-&gt;treeName
comma
id|atomic_read
c_func
(paren
op_amp
id|tcon-&gt;useCount
)paren
comma
id|tcon-&gt;nativeFileSystem
comma
id|tcon-&gt;fsDevInfo.DeviceCharacteristics
comma
id|tcon-&gt;fsAttrInfo.Attributes
comma
id|tcon-&gt;fsAttrInfo.MaxPathNameComponentLength
)paren
suffix:semicolon
id|buf
op_add_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|tcon-&gt;fsDevInfo.DeviceType
op_eq
id|FILE_DEVICE_DISK
)paren
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot; type: DISK &quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tcon-&gt;fsDevInfo.DeviceType
op_eq
id|FILE_DEVICE_CD_ROM
)paren
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot; type: CDROM &quot;
)paren
suffix:semicolon
r_else
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot; type: %d &quot;
comma
id|tcon-&gt;fsDevInfo.DeviceType
)paren
suffix:semicolon
id|buf
op_add_assign
id|length
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|buf
op_add_assign
id|length
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* BB add code to dump additional info such as TCP session info now */
multiline_comment|/*&n;&t;   if (offset &gt;= (buf - buf_start)) &n;&t;   {&n;&t;   *beginBuffer = buf;&n;&t;   return 0;&n;&t;   }&n;&t;   *beginBuffer = buf + offset;&n;&t;   if ((buf - buf_start - offset) &gt; count)&n;&t;   return count;&n;   else */
r_return
(paren
id|buf
op_minus
id|buf_start
op_minus
id|offset
)paren
suffix:semicolon
)brace
r_int
DECL|function|cifs_total_xid_read
id|cifs_total_xid_read
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|beginBuffer
comma
id|off_t
id|offset
comma
r_int
id|length
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
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Total vfs operations: %d and maximum simultaneous serviced by this filesystem: %d&bslash;n&quot;
comma
id|GlobalCurrentXid
comma
id|GlobalMaxActiveXid
)paren
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
r_int
DECL|function|cifs_stats_read
id|cifs_stats_read
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|beginBuffer
comma
id|off_t
id|offset
comma
r_int
id|length
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
id|item_length
suffix:semicolon
id|length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Currently Allocated structures&bslash;nCIFS Sessions: %d&bslash;n&quot;
comma
id|sesInfoAllocCount.counter
)paren
suffix:semicolon
id|buf
op_add_assign
id|length
suffix:semicolon
id|item_length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Shares (unique mount targets): %d&bslash;n&quot;
comma
id|tconInfoAllocCount.counter
)paren
suffix:semicolon
id|length
op_add_assign
id|item_length
suffix:semicolon
id|buf
op_add_assign
id|item_length
suffix:semicolon
id|item_length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Allocated SMB Request and Response Buffers: %d&bslash;n&quot;
comma
id|bufAllocCount.counter
)paren
suffix:semicolon
id|length
op_add_assign
id|item_length
suffix:semicolon
id|buf
op_add_assign
id|item_length
suffix:semicolon
id|item_length
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Active Operations (MIDs in use): %d&bslash;n&quot;
comma
id|midCount.counter
)paren
suffix:semicolon
id|length
op_add_assign
id|item_length
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
DECL|variable|proc_fs_cifs
r_struct
id|proc_dir_entry
op_star
id|proc_fs_cifs
suffix:semicolon
DECL|variable|cifs_txanchor_read
id|read_proc_t
id|cifs_txanchor_read
suffix:semicolon
DECL|variable|cifsFYI_read
r_static
id|read_proc_t
id|cifsFYI_read
suffix:semicolon
DECL|variable|cifsFYI_write
r_static
id|write_proc_t
id|cifsFYI_write
suffix:semicolon
DECL|variable|oplockEnabled_read
r_static
id|read_proc_t
id|oplockEnabled_read
suffix:semicolon
DECL|variable|oplockEnabled_write
r_static
id|write_proc_t
id|oplockEnabled_write
suffix:semicolon
DECL|variable|traceSMB_read
r_static
id|read_proc_t
id|traceSMB_read
suffix:semicolon
DECL|variable|traceSMB_write
r_static
id|write_proc_t
id|traceSMB_write
suffix:semicolon
DECL|variable|multiuser_mount_read
r_static
id|read_proc_t
id|multiuser_mount_read
suffix:semicolon
DECL|variable|multiuser_mount_write
r_static
id|write_proc_t
id|multiuser_mount_write
suffix:semicolon
DECL|variable|extended_security_read
r_static
id|read_proc_t
id|extended_security_read
suffix:semicolon
DECL|variable|extended_security_write
r_static
id|write_proc_t
id|extended_security_write
suffix:semicolon
DECL|variable|ntlmv2_enabled_read
r_static
id|read_proc_t
id|ntlmv2_enabled_read
suffix:semicolon
DECL|variable|ntlmv2_enabled_write
r_static
id|write_proc_t
id|ntlmv2_enabled_write
suffix:semicolon
DECL|variable|packet_signing_enabled_read
r_static
id|read_proc_t
id|packet_signing_enabled_read
suffix:semicolon
DECL|variable|packet_signing_enabled_write
r_static
id|write_proc_t
id|packet_signing_enabled_write
suffix:semicolon
r_void
DECL|function|cifs_proc_init
id|cifs_proc_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|pde
suffix:semicolon
id|proc_fs_cifs
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;cifs&quot;
comma
id|proc_root_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_fs_cifs
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|proc_fs_cifs-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|create_proc_read_entry
c_func
(paren
l_string|&quot;DebugData&quot;
comma
l_int|0
comma
id|proc_fs_cifs
comma
id|cifs_debug_data_read
comma
l_int|0
)paren
suffix:semicolon
id|create_proc_read_entry
c_func
(paren
l_string|&quot;SimultaneousOps&quot;
comma
l_int|0
comma
id|proc_fs_cifs
comma
id|cifs_total_xid_read
comma
l_int|0
)paren
suffix:semicolon
id|create_proc_read_entry
c_func
(paren
l_string|&quot;Stats&quot;
comma
l_int|0
comma
id|proc_fs_cifs
comma
id|cifs_stats_read
comma
l_int|0
)paren
suffix:semicolon
id|pde
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;cifsFYI&quot;
comma
l_int|0
comma
id|proc_fs_cifs
comma
id|cifsFYI_read
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pde
)paren
id|pde-&gt;write_proc
op_assign
id|cifsFYI_write
suffix:semicolon
id|pde
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;traceSMB&quot;
comma
l_int|0
comma
id|proc_fs_cifs
comma
id|traceSMB_read
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pde
)paren
id|pde-&gt;write_proc
op_assign
id|traceSMB_write
suffix:semicolon
id|pde
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;oplockEnabled&quot;
comma
l_int|0
comma
id|proc_fs_cifs
comma
id|oplockEnabled_read
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pde
)paren
id|pde-&gt;write_proc
op_assign
id|oplockEnabled_write
suffix:semicolon
id|pde
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;MultiuserMount&quot;
comma
l_int|0
comma
id|proc_fs_cifs
comma
id|multiuser_mount_read
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pde
)paren
id|pde-&gt;write_proc
op_assign
id|multiuser_mount_write
suffix:semicolon
id|pde
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;ExtendedSecurity&quot;
comma
l_int|0
comma
id|proc_fs_cifs
comma
id|extended_security_read
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pde
)paren
id|pde-&gt;write_proc
op_assign
id|extended_security_write
suffix:semicolon
id|pde
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;NTLMV2Enabled&quot;
comma
l_int|0
comma
id|proc_fs_cifs
comma
id|ntlmv2_enabled_read
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pde
)paren
id|pde-&gt;write_proc
op_assign
id|ntlmv2_enabled_write
suffix:semicolon
id|pde
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;PacketSigningEnabled&quot;
comma
l_int|0
comma
id|proc_fs_cifs
comma
id|packet_signing_enabled_read
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pde
)paren
id|pde-&gt;write_proc
op_assign
id|packet_signing_enabled_write
suffix:semicolon
)brace
r_void
DECL|function|cifs_proc_clean
id|cifs_proc_clean
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|proc_fs_cifs
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;DebugData&quot;
comma
id|proc_fs_cifs
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;cifsFYI&quot;
comma
id|proc_fs_cifs
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;TraceSMB&quot;
comma
id|proc_fs_cifs
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;SimultaneousOps&quot;
comma
id|proc_fs_cifs
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;TotalOps&quot;
comma
id|proc_fs_cifs
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;MultiuserMount&quot;
comma
id|proc_fs_cifs
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;oplockEnabled&quot;
comma
id|proc_fs_cifs
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;NTLMV2Enabled&quot;
comma
id|proc_fs_cifs
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;ExtendedSecurity&quot;
comma
id|proc_fs_cifs
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;PacketSigningEnabled&quot;
comma
id|proc_fs_cifs
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;cifs&quot;
comma
id|proc_root_fs
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|cifsFYI_read
id|cifsFYI_read
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
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|cifsFYI
)paren
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
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
r_else
op_star
id|eof
op_assign
l_int|1
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
DECL|function|cifsFYI_write
id|cifsFYI_write
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
r_char
id|c
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|get_user
c_func
(paren
id|c
comma
id|buffer
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
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;0&squot;
op_logical_or
id|c
op_eq
l_char|&squot;n&squot;
op_logical_or
id|c
op_eq
l_char|&squot;N&squot;
)paren
id|cifsFYI
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;1&squot;
op_logical_or
id|c
op_eq
l_char|&squot;y&squot;
op_logical_or
id|c
op_eq
l_char|&squot;Y&squot;
)paren
id|cifsFYI
op_assign
l_int|1
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|oplockEnabled_read
id|oplockEnabled_read
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
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|oplockEnabled
)paren
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
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
r_else
op_star
id|eof
op_assign
l_int|1
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
DECL|function|oplockEnabled_write
id|oplockEnabled_write
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
r_char
id|c
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|get_user
c_func
(paren
id|c
comma
id|buffer
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
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;0&squot;
op_logical_or
id|c
op_eq
l_char|&squot;n&squot;
op_logical_or
id|c
op_eq
l_char|&squot;N&squot;
)paren
id|oplockEnabled
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;1&squot;
op_logical_or
id|c
op_eq
l_char|&squot;y&squot;
op_logical_or
id|c
op_eq
l_char|&squot;Y&squot;
)paren
id|oplockEnabled
op_assign
l_int|1
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|traceSMB_read
id|traceSMB_read
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
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|traceSMB
)paren
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
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
r_else
op_star
id|eof
op_assign
l_int|1
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
DECL|function|traceSMB_write
id|traceSMB_write
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
r_char
id|c
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|get_user
c_func
(paren
id|c
comma
id|buffer
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
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;0&squot;
op_logical_or
id|c
op_eq
l_char|&squot;n&squot;
op_logical_or
id|c
op_eq
l_char|&squot;N&squot;
)paren
id|traceSMB
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;1&squot;
op_logical_or
id|c
op_eq
l_char|&squot;y&squot;
op_logical_or
id|c
op_eq
l_char|&squot;Y&squot;
)paren
id|traceSMB
op_assign
l_int|1
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|multiuser_mount_read
id|multiuser_mount_read
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
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|multiuser_mount
)paren
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
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
r_else
op_star
id|eof
op_assign
l_int|1
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
DECL|function|multiuser_mount_write
id|multiuser_mount_write
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
r_char
id|c
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|get_user
c_func
(paren
id|c
comma
id|buffer
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
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;0&squot;
op_logical_or
id|c
op_eq
l_char|&squot;n&squot;
op_logical_or
id|c
op_eq
l_char|&squot;N&squot;
)paren
id|multiuser_mount
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;1&squot;
op_logical_or
id|c
op_eq
l_char|&squot;y&squot;
op_logical_or
id|c
op_eq
l_char|&squot;Y&squot;
)paren
id|multiuser_mount
op_assign
l_int|1
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|extended_security_read
id|extended_security_read
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
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|extended_security
)paren
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
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
r_else
op_star
id|eof
op_assign
l_int|1
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
DECL|function|extended_security_write
id|extended_security_write
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
r_char
id|c
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|get_user
c_func
(paren
id|c
comma
id|buffer
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
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;0&squot;
op_logical_or
id|c
op_eq
l_char|&squot;n&squot;
op_logical_or
id|c
op_eq
l_char|&squot;N&squot;
)paren
id|extended_security
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;1&squot;
op_logical_or
id|c
op_eq
l_char|&squot;y&squot;
op_logical_or
id|c
op_eq
l_char|&squot;Y&squot;
)paren
id|extended_security
op_assign
l_int|1
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|ntlmv2_enabled_read
id|ntlmv2_enabled_read
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
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|ntlmv2_support
)paren
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
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
r_else
op_star
id|eof
op_assign
l_int|1
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
DECL|function|ntlmv2_enabled_write
id|ntlmv2_enabled_write
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
r_char
id|c
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|get_user
c_func
(paren
id|c
comma
id|buffer
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
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;0&squot;
op_logical_or
id|c
op_eq
l_char|&squot;n&squot;
op_logical_or
id|c
op_eq
l_char|&squot;N&squot;
)paren
id|ntlmv2_support
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;1&squot;
op_logical_or
id|c
op_eq
l_char|&squot;y&squot;
op_logical_or
id|c
op_eq
l_char|&squot;Y&squot;
)paren
id|ntlmv2_support
op_assign
l_int|1
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|packet_signing_enabled_read
id|packet_signing_enabled_read
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
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|sign_CIFS_PDUs
)paren
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
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
r_else
op_star
id|eof
op_assign
l_int|1
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
DECL|function|packet_signing_enabled_write
id|packet_signing_enabled_write
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
r_char
id|c
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|get_user
c_func
(paren
id|c
comma
id|buffer
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
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;0&squot;
op_logical_or
id|c
op_eq
l_char|&squot;n&squot;
op_logical_or
id|c
op_eq
l_char|&squot;N&squot;
)paren
id|sign_CIFS_PDUs
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;1&squot;
op_logical_or
id|c
op_eq
l_char|&squot;y&squot;
op_logical_or
id|c
op_eq
l_char|&squot;Y&squot;
)paren
id|sign_CIFS_PDUs
op_assign
l_int|1
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
macro_line|#endif
eof
