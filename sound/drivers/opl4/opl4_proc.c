multiline_comment|/*&n; * Functions for the OPL4 proc file&n; * Copyright (c) 2003 by Clemens Ladisch &lt;clemens@ladisch.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;opl4_local.h&quot;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;sound/info.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|snd_opl4_mem_proc_open
r_static
r_int
id|snd_opl4_mem_proc_open
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_int
r_int
id|mode
comma
r_void
op_star
op_star
id|file_private_data
)paren
(brace
id|opl4_t
op_star
id|opl4
op_assign
id|snd_magic_cast
c_func
(paren
id|opl4_t
comma
id|entry-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opl4-&gt;memory_access
)paren
(brace
id|up
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|opl4-&gt;memory_access
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl4_mem_proc_release
r_static
r_int
id|snd_opl4_mem_proc_release
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_int
r_int
id|mode
comma
r_void
op_star
id|file_private_data
)paren
(brace
id|opl4_t
op_star
id|opl4
op_assign
id|snd_magic_cast
c_func
(paren
id|opl4_t
comma
id|entry-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
id|opl4-&gt;memory_access
op_decrement
suffix:semicolon
id|up
c_func
(paren
op_amp
id|opl4-&gt;access_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl4_mem_proc_read
r_static
r_int
id|snd_opl4_mem_proc_read
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|file_private_data
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|_buf
comma
r_int
id|count
)paren
(brace
id|opl4_t
op_star
id|opl4
op_assign
id|snd_magic_cast
c_func
(paren
id|opl4_t
comma
id|entry-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_int
id|size
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
id|size
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_pos
op_plus
id|size
OG
id|entry-&gt;size
)paren
id|size
op_assign
id|entry-&gt;size
op_minus
id|file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
(brace
id|buf
op_assign
id|vmalloc
c_func
(paren
id|size
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
id|snd_opl4_read_memory
c_func
(paren
id|opl4
comma
id|buf
comma
id|file-&gt;f_pos
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|_buf
comma
id|buf
comma
id|size
)paren
)paren
(brace
id|vfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|vfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|size
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl4_mem_proc_write
r_static
r_int
id|snd_opl4_mem_proc_write
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|file_private_data
comma
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|_buf
comma
r_int
id|count
)paren
(brace
id|opl4_t
op_star
id|opl4
op_assign
id|snd_magic_cast
c_func
(paren
id|opl4_t
comma
id|entry-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_int
id|size
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
id|size
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_pos
op_plus
id|size
OG
id|entry-&gt;size
)paren
id|size
op_assign
id|entry-&gt;size
op_minus
id|file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
(brace
id|buf
op_assign
id|vmalloc
c_func
(paren
id|size
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
id|_buf
comma
id|size
)paren
)paren
(brace
id|vfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|snd_opl4_write_memory
c_func
(paren
id|opl4
comma
id|buf
comma
id|file-&gt;f_pos
comma
id|size
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|size
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl4_mem_proc_llseek
r_static
r_int
r_int
id|snd_opl4_mem_proc_llseek
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|file_private_data
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|offset
comma
r_int
id|orig
)paren
(brace
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* SEEK_SET */
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* SEEK_CUR */
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* SEEK_END, offset is negative */
id|file-&gt;f_pos
op_assign
id|entry-&gt;size
op_plus
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_pos
OG
id|entry-&gt;size
)paren
id|file-&gt;f_pos
op_assign
id|entry-&gt;size
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
)brace
DECL|variable|snd_opl4_mem_proc_ops
r_static
r_struct
id|snd_info_entry_ops
id|snd_opl4_mem_proc_ops
op_assign
(brace
dot
id|open
op_assign
id|snd_opl4_mem_proc_open
comma
dot
id|release
op_assign
id|snd_opl4_mem_proc_release
comma
dot
id|read
op_assign
id|snd_opl4_mem_proc_read
comma
dot
id|write
op_assign
id|snd_opl4_mem_proc_write
comma
dot
id|llseek
op_assign
id|snd_opl4_mem_proc_llseek
comma
)brace
suffix:semicolon
DECL|function|snd_opl4_create_proc
r_int
id|snd_opl4_create_proc
c_func
(paren
id|opl4_t
op_star
id|opl4
)paren
(brace
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|snd_info_create_card_entry
c_func
(paren
id|opl4-&gt;card
comma
l_string|&quot;opl4-mem&quot;
comma
id|opl4-&gt;card-&gt;proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
r_if
c_cond
(paren
id|opl4-&gt;hardware
OL
id|OPL3_HW_OPL4_ML
)paren
(brace
multiline_comment|/* OPL4 can access 4 MB external ROM/SRAM */
id|entry-&gt;mode
op_or_assign
id|S_IWUSR
suffix:semicolon
id|entry-&gt;size
op_assign
l_int|4
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* OPL4-ML has 1 MB internal ROM */
id|entry-&gt;size
op_assign
l_int|1
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
)brace
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_DATA
suffix:semicolon
id|entry-&gt;c.ops
op_assign
op_amp
id|snd_opl4_mem_proc_ops
suffix:semicolon
id|entry-&gt;module
op_assign
id|THIS_MODULE
suffix:semicolon
id|entry-&gt;private_data
op_assign
id|opl4
suffix:semicolon
r_if
c_cond
(paren
id|snd_info_register
c_func
(paren
id|entry
)paren
OL
l_int|0
)paren
(brace
id|snd_info_free_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
id|entry
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|opl4-&gt;proc_entry
op_assign
id|entry
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_opl4_free_proc
r_void
id|snd_opl4_free_proc
c_func
(paren
id|opl4_t
op_star
id|opl4
)paren
(brace
r_if
c_cond
(paren
id|opl4-&gt;proc_entry
)paren
id|snd_info_unregister
c_func
(paren
id|opl4-&gt;proc_entry
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof
