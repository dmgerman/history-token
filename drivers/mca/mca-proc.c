multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/*&n; * MCA bus support functions for the proc fs.&n; *&n; * NOTE: this code *requires* the legacy MCA api.&n; *&n; * Legacy API means the API that operates in terms of MCA slot number&n; *&n; * (C) 2002 James Bottomley &lt;James.Bottomley@HansenPartnership.com&gt;&n; *&n;**-----------------------------------------------------------------------------&n;**  &n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/mca.h&gt;
DECL|function|get_mca_info_helper
r_static
r_int
id|get_mca_info_helper
c_func
(paren
r_struct
id|mca_device
op_star
id|mca_dev
comma
r_char
op_star
id|page
comma
r_int
id|len
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%02x &quot;
comma
id|mca_dev
ques
c_cond
id|mca_dev-&gt;pos
(braket
id|j
)braket
suffix:colon
l_int|0xff
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot; %s&bslash;n&quot;
comma
id|mca_dev
ques
c_cond
id|mca_dev-&gt;dev.name
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|get_mca_info
r_int
id|get_mca_info
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
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|MCA_bus
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
suffix:semicolon
multiline_comment|/* Format POS registers of eight MCA slots */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MCA_MAX_SLOT_NR
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|i
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Slot %d: &quot;
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
id|len
op_assign
id|get_mca_info_helper
c_func
(paren
id|mca_dev
comma
id|page
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/* Format POS registers of integrated video subsystem */
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|MCA_INTEGVIDEO
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Video : &quot;
)paren
suffix:semicolon
id|len
op_assign
id|get_mca_info_helper
c_func
(paren
id|mca_dev
comma
id|page
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* Format POS registers of integrated SCSI subsystem */
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|MCA_INTEGSCSI
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;SCSI  : &quot;
)paren
suffix:semicolon
id|len
op_assign
id|get_mca_info_helper
c_func
(paren
id|mca_dev
comma
id|page
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* Format POS registers of motherboard */
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|MCA_MOTHERBOARD
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Planar: &quot;
)paren
suffix:semicolon
id|len
op_assign
id|get_mca_info_helper
c_func
(paren
id|mca_dev
comma
id|page
comma
id|len
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Leave it empty if MCA not detected - this should *never*&n;&t;&t; * happen!&n;&t;&t; */
)brace
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
multiline_comment|/*--------------------------------------------------------------------*/
DECL|function|mca_default_procfn
r_static
r_int
id|mca_default_procfn
c_func
(paren
r_char
op_star
id|buf
comma
r_struct
id|mca_device
op_star
id|mca_dev
)paren
(brace
r_int
id|len
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_int
id|slot
op_assign
id|mca_dev-&gt;slot
suffix:semicolon
multiline_comment|/* Print out the basic information */
r_if
c_cond
(paren
id|slot
OL
id|MCA_MAX_SLOT_NR
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Slot: %d&bslash;n&quot;
comma
id|slot
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|slot
op_eq
id|MCA_INTEGSCSI
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Integrated SCSI Adapter&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|slot
op_eq
id|MCA_INTEGVIDEO
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Integrated Video Adapter&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|slot
op_eq
id|MCA_MOTHERBOARD
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Motherboard&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mca_dev-&gt;dev.name
(braket
l_int|0
)braket
)paren
(brace
multiline_comment|/* Drivers might register a name without /proc handler... */
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Adapter Name: %s&bslash;n&quot;
comma
id|mca_dev-&gt;dev.name
)paren
suffix:semicolon
)brace
r_else
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Adapter Name: Unknown&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Id: %02x%02x&bslash;n&quot;
comma
id|mca_dev-&gt;pos
(braket
l_int|1
)braket
comma
id|mca_dev-&gt;pos
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Enabled: %s&bslash;nPOS: &quot;
comma
id|mca_isenabled
c_func
(paren
id|slot
)paren
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No&quot;
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%02x &quot;
comma
id|mca_dev-&gt;pos
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;&bslash;nDriver Installed: %s&quot;
comma
id|mca_is_adapter_used
c_func
(paren
id|slot
)paren
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No&quot;
)paren
suffix:semicolon
id|buf
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* mca_default_procfn() */
DECL|function|get_mca_machine_info
r_static
r_int
id|get_mca_machine_info
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
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Model Id: 0x%x&bslash;n&quot;
comma
id|machine_id
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Submodel Id: 0x%x&bslash;n&quot;
comma
id|machine_submodel_id
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;BIOS Revision: 0x%x&bslash;n&quot;
comma
id|BIOS_revision
)paren
suffix:semicolon
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
DECL|function|mca_read_proc
r_static
r_int
id|mca_read_proc
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
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
(paren
r_struct
id|mca_device
op_star
)paren
id|data
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Get the standard info */
id|len
op_assign
id|mca_default_procfn
c_func
(paren
id|page
comma
id|mca_dev
)paren
suffix:semicolon
multiline_comment|/* Do any device-specific processing, if there is any */
r_if
c_cond
(paren
id|mca_dev-&gt;procfn
)paren
(brace
id|len
op_add_assign
id|mca_dev
op_member_access_from_pointer
id|procfn
c_func
(paren
id|page
op_plus
id|len
comma
id|mca_dev-&gt;slot
comma
id|mca_dev-&gt;proc_dev
)paren
suffix:semicolon
)brace
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
multiline_comment|/* mca_read_proc() */
multiline_comment|/*--------------------------------------------------------------------*/
DECL|function|mca_do_proc_init
r_void
id|__init
id|mca_do_proc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|proc_mca
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|node
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|mca_device
op_star
id|mca_dev
suffix:semicolon
id|proc_mca
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;mca&quot;
comma
op_amp
id|proc_root
)paren
suffix:semicolon
id|create_proc_read_entry
c_func
(paren
l_string|&quot;pos&quot;
comma
l_int|0
comma
id|proc_mca
comma
id|get_mca_info
comma
l_int|NULL
)paren
suffix:semicolon
id|create_proc_read_entry
c_func
(paren
l_string|&quot;machine&quot;
comma
l_int|0
comma
id|proc_mca
comma
id|get_mca_machine_info
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Initialize /proc/mca entries for existing adapters */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MCA_NUMADAPTERS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_continue
suffix:semicolon
)brace
id|mca_dev-&gt;procfn
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|MCA_MAX_SLOT_NR
)paren
(brace
id|sprintf
c_func
(paren
id|mca_dev-&gt;procname
comma
l_string|&quot;slot%d&quot;
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
id|MCA_INTEGVIDEO
)paren
(brace
id|sprintf
c_func
(paren
id|mca_dev-&gt;procname
comma
l_string|&quot;video&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
id|MCA_INTEGSCSI
)paren
(brace
id|sprintf
c_func
(paren
id|mca_dev-&gt;procname
comma
l_string|&quot;scsi&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
id|MCA_MOTHERBOARD
)paren
(brace
id|sprintf
c_func
(paren
id|mca_dev-&gt;procname
comma
l_string|&quot;planar&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mca_isadapter
c_func
(paren
id|i
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
id|node
op_assign
id|create_proc_read_entry
c_func
(paren
id|mca_dev-&gt;procname
comma
l_int|0
comma
id|proc_mca
comma
id|mca_read_proc
comma
(paren
r_void
op_star
)paren
id|mca_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to allocate memory for MCA proc-entries!&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* mca_do_proc_init() */
multiline_comment|/**&n; *&t;mca_set_adapter_procfn - Set the /proc callback&n; *&t;@slot: slot to configure&n; *&t;@procfn: callback function to call for /proc&n; *&t;@dev: device information passed to the callback&n; *&n; *&t;This sets up an information callback for /proc/mca/slot?.  The&n; *&t;function is called with the buffer, slot, and device pointer (or&n; *&t;some equally informative context information, or nothing, if you&n; *&t;prefer), and is expected to put useful information into the&n; *&t;buffer.  The adapter name, ID, and POS registers get printed&n; *&t;before this is called though, so don&squot;t do it again.&n; *&n; *&t;This should be called with a %NULL @procfn when a module&n; *&t;unregisters, thus preventing kernel crashes and other such&n; *&t;nastiness.&n; */
DECL|function|mca_set_adapter_procfn
r_void
id|mca_set_adapter_procfn
c_func
(paren
r_int
id|slot
comma
id|MCA_ProcFn
id|procfn
comma
r_void
op_star
id|proc_dev
)paren
(brace
r_struct
id|mca_device
op_star
id|mca_dev
op_assign
id|mca_find_device_by_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mca_dev
)paren
(brace
r_return
suffix:semicolon
)brace
id|mca_dev-&gt;procfn
op_assign
id|procfn
suffix:semicolon
id|mca_dev-&gt;proc_dev
op_assign
id|proc_dev
suffix:semicolon
)brace
DECL|variable|mca_set_adapter_procfn
id|EXPORT_SYMBOL
c_func
(paren
id|mca_set_adapter_procfn
)paren
suffix:semicolon
eof
