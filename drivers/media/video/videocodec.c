multiline_comment|/*&n; * VIDEO MOTION CODECs internal API for video devices&n; *&n; * Interface for MJPEG (and maybe later MPEG/WAVELETS) codec&squot;s&n; * bound to a master device.&n; *&n; * (c) 2002 Wolfgang Scherr &lt;scherr@net4you.at&gt;&n; *&n; * $Id: videocodec.c,v 1.1.2.8 2003/03/29 07:16:04 rbultje Exp $&n; *&n; * ------------------------------------------------------------------------&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * ------------------------------------------------------------------------&n; */
DECL|macro|VIDEOCODEC_VERSION
mdefine_line|#define VIDEOCODEC_VERSION &quot;v0.2&quot;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
singleline_comment|// kernel config is here (procfs flag)
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifndef KERNEL_VERSION
DECL|macro|KERNEL_VERSION
mdefine_line|#define KERNEL_VERSION(a,b,c) ((a)*65536+(b)*256+(c))
macro_line|#endif
macro_line|#include &quot;videocodec.h&quot;
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Debug level (0-4)&quot;
)paren
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(num, format, args...) &bslash;&n;&t;do { &bslash;&n;&t;&t;if (debug &gt;= num) &bslash;&n;&t;&t;&t;printk(format, ##args); &bslash;&n;&t;} while (0)
DECL|struct|attached_list
r_struct
id|attached_list
(brace
DECL|member|codec
r_struct
id|videocodec
op_star
id|codec
suffix:semicolon
DECL|member|next
r_struct
id|attached_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|codec_list
r_struct
id|codec_list
(brace
DECL|member|codec
r_const
r_struct
id|videocodec
op_star
id|codec
suffix:semicolon
DECL|member|attached
r_int
id|attached
suffix:semicolon
DECL|member|list
r_struct
id|attached_list
op_star
id|list
suffix:semicolon
DECL|member|next
r_struct
id|codec_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|codeclist_top
r_static
r_struct
id|codec_list
op_star
id|codeclist_top
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* ================================================= */
multiline_comment|/* function prototypes of the master/slave interface */
multiline_comment|/* ================================================= */
r_struct
id|videocodec
op_star
DECL|function|videocodec_attach
id|videocodec_attach
(paren
r_struct
id|videocodec_master
op_star
id|master
)paren
(brace
r_struct
id|codec_list
op_star
id|h
op_assign
id|codeclist_top
suffix:semicolon
r_struct
id|attached_list
op_star
id|a
comma
op_star
id|ptr
suffix:semicolon
r_struct
id|videocodec
op_star
id|codec
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|master
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_attach: no data&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;videocodec_attach: &squot;%s&squot;, type: %x, flags %lx, magic %lx&bslash;n&quot;
comma
id|master-&gt;name
comma
id|master-&gt;type
comma
id|master-&gt;flags
comma
id|master-&gt;magic
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_attach: no device available&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|h
)paren
(brace
singleline_comment|// attach only if the slave has at least the flags
singleline_comment|// expected by the master
r_if
c_cond
(paren
(paren
id|master-&gt;flags
op_amp
id|h-&gt;codec-&gt;flags
)paren
op_eq
id|master-&gt;flags
)paren
(brace
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec_attach: try &squot;%s&squot;&bslash;n&quot;
comma
id|h-&gt;codec-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|h-&gt;codec-&gt;owner
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|codec
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|videocodec
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|codec
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_attach: no mem&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_module_put
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|codec
comma
id|h-&gt;codec
comma
r_sizeof
(paren
r_struct
id|videocodec
)paren
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|codec-&gt;name
comma
r_sizeof
(paren
id|codec-&gt;name
)paren
comma
l_string|&quot;%s[%d]&quot;
comma
id|codec-&gt;name
comma
id|h-&gt;attached
)paren
suffix:semicolon
id|codec-&gt;master_data
op_assign
id|master
suffix:semicolon
id|res
op_assign
id|codec
op_member_access_from_pointer
id|setup
c_func
(paren
id|codec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_int|3
comma
l_string|&quot;videocodec_attach &squot;%s&squot;&bslash;n&quot;
comma
id|codec-&gt;name
)paren
suffix:semicolon
id|ptr
op_assign
(paren
r_struct
id|attached_list
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|attached_list
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_attach: no memory&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_kfree
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|attached_list
)paren
)paren
suffix:semicolon
id|ptr-&gt;codec
op_assign
id|codec
suffix:semicolon
id|a
op_assign
id|h-&gt;list
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
(brace
id|h-&gt;list
op_assign
id|ptr
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec: first element&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|a-&gt;next
)paren
id|a
op_assign
id|a-&gt;next
suffix:semicolon
singleline_comment|// find end
id|a-&gt;next
op_assign
id|ptr
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec: in after &squot;%s&squot;&bslash;n&quot;
comma
id|h-&gt;codec-&gt;name
)paren
suffix:semicolon
)brace
id|h-&gt;attached
op_add_assign
l_int|1
suffix:semicolon
r_return
id|codec
suffix:semicolon
)brace
r_else
(brace
id|kfree
c_func
(paren
id|codec
)paren
suffix:semicolon
)brace
)brace
id|h
op_assign
id|h-&gt;next
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_attach: no codec found!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
id|out_module_put
suffix:colon
id|module_put
c_func
(paren
id|h-&gt;codec-&gt;owner
)paren
suffix:semicolon
id|out_kfree
suffix:colon
id|kfree
c_func
(paren
id|codec
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_int
DECL|function|videocodec_detach
id|videocodec_detach
(paren
r_struct
id|videocodec
op_star
id|codec
)paren
(brace
r_struct
id|codec_list
op_star
id|h
op_assign
id|codeclist_top
suffix:semicolon
r_struct
id|attached_list
op_star
id|a
comma
op_star
id|prev
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|codec
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_detach: no data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;videocodec_detach: &squot;%s&squot;, type: %x, flags %lx, magic %lx&bslash;n&quot;
comma
id|codec-&gt;name
comma
id|codec-&gt;type
comma
id|codec-&gt;flags
comma
id|codec-&gt;magic
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_detach: no device left...&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_while
c_loop
(paren
id|h
)paren
(brace
id|a
op_assign
id|h-&gt;list
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|a
)paren
(brace
r_if
c_cond
(paren
id|codec
op_eq
id|a-&gt;codec
)paren
(brace
id|res
op_assign
id|a-&gt;codec
op_member_access_from_pointer
id|unset
c_func
(paren
id|a-&gt;codec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ge
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_int|3
comma
l_string|&quot;videocodec_detach: &squot;%s&squot;&bslash;n&quot;
comma
id|a-&gt;codec-&gt;name
)paren
suffix:semicolon
id|a-&gt;codec-&gt;master_data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_detach: &squot;%s&squot;&bslash;n&quot;
comma
id|a-&gt;codec-&gt;name
)paren
suffix:semicolon
id|a-&gt;codec-&gt;master_data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev
op_eq
l_int|NULL
)paren
(brace
id|h-&gt;list
op_assign
id|a-&gt;next
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec: delete first&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|prev-&gt;next
op_assign
id|a-&gt;next
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec: delete middle&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|module_put
c_func
(paren
id|a-&gt;codec-&gt;owner
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|a-&gt;codec
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|a
)paren
suffix:semicolon
id|h-&gt;attached
op_sub_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|prev
op_assign
id|a
suffix:semicolon
id|a
op_assign
id|a-&gt;next
suffix:semicolon
)brace
id|h
op_assign
id|h-&gt;next
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_detach: given codec not found!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_int
DECL|function|videocodec_register
id|videocodec_register
(paren
r_const
r_struct
id|videocodec
op_star
id|codec
)paren
(brace
r_struct
id|codec_list
op_star
id|ptr
comma
op_star
id|h
op_assign
id|codeclist_top
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|codec
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_register: no data!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;videocodec: register &squot;%s&squot;, type: %x, flags %lx, magic %lx&bslash;n&quot;
comma
id|codec-&gt;name
comma
id|codec-&gt;type
comma
id|codec-&gt;flags
comma
id|codec-&gt;magic
)paren
suffix:semicolon
id|ptr
op_assign
(paren
r_struct
id|codec_list
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|codec_list
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_register: no memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|codec_list
)paren
)paren
suffix:semicolon
id|ptr-&gt;codec
op_assign
id|codec
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h
)paren
(brace
id|codeclist_top
op_assign
id|ptr
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec: hooked in as first element&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|h-&gt;next
)paren
id|h
op_assign
id|h-&gt;next
suffix:semicolon
singleline_comment|// find the end
id|h-&gt;next
op_assign
id|ptr
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec: hooked in after &squot;%s&squot;&bslash;n&quot;
comma
id|h-&gt;codec-&gt;name
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|videocodec_unregister
id|videocodec_unregister
(paren
r_const
r_struct
id|videocodec
op_star
id|codec
)paren
(brace
r_struct
id|codec_list
op_star
id|prev
op_assign
l_int|NULL
comma
op_star
id|h
op_assign
id|codeclist_top
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|codec
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_unregister: no data!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;videocodec: unregister &squot;%s&squot;, type: %x, flags %lx, magic %lx&bslash;n&quot;
comma
id|codec-&gt;name
comma
id|codec-&gt;type
comma
id|codec-&gt;flags
comma
id|codec-&gt;magic
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_unregister: no device left...&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_while
c_loop
(paren
id|h
)paren
(brace
r_if
c_cond
(paren
id|codec
op_eq
id|h-&gt;codec
)paren
(brace
r_if
c_cond
(paren
id|h-&gt;attached
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec: &squot;%s&squot; is used&bslash;n&quot;
comma
id|h-&gt;codec-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|3
comma
l_string|&quot;videocodec: unregister &squot;%s&squot; is ok.&bslash;n&quot;
comma
id|h-&gt;codec-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev
op_eq
l_int|NULL
)paren
(brace
id|codeclist_top
op_assign
id|h-&gt;next
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec: delete first element&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|prev-&gt;next
op_assign
id|h-&gt;next
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec: delete middle element&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|h
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|prev
op_assign
id|h
suffix:semicolon
id|h
op_assign
id|h-&gt;next
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec_unregister: given codec not found!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/* ============ */
multiline_comment|/* procfs stuff */
multiline_comment|/* ============ */
DECL|variable|videocodec_buf
r_static
r_char
op_star
id|videocodec_buf
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|videocodec_bufsize
r_static
r_int
id|videocodec_bufsize
op_assign
l_int|0
suffix:semicolon
r_static
r_int
DECL|function|videocodec_build_table
id|videocodec_build_table
(paren
r_void
)paren
(brace
r_struct
id|codec_list
op_star
id|h
op_assign
id|codeclist_top
suffix:semicolon
r_struct
id|attached_list
op_star
id|a
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|size
suffix:semicolon
singleline_comment|// sum up amount of slaves plus their attached masters
r_while
c_loop
(paren
id|h
)paren
(brace
id|i
op_add_assign
id|h-&gt;attached
op_plus
l_int|1
suffix:semicolon
id|h
op_assign
id|h-&gt;next
suffix:semicolon
)brace
DECL|macro|LINESIZE
mdefine_line|#define LINESIZE 100
id|size
op_assign
id|LINESIZE
op_star
(paren
id|i
op_plus
l_int|1
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|3
comma
l_string|&quot;videocodec_build table: %d entries, %d bytes&bslash;n&quot;
comma
id|i
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|videocodec_buf
)paren
id|kfree
c_func
(paren
id|videocodec_buf
)paren
suffix:semicolon
id|videocodec_buf
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_add_assign
id|scnprintf
c_func
(paren
id|videocodec_buf
op_plus
id|i
comma
id|size
op_minus
l_int|1
comma
l_string|&quot;&lt;S&gt;lave or attached &lt;M&gt;aster name  type flags    magic    &quot;
)paren
suffix:semicolon
id|i
op_add_assign
id|scnprintf
c_func
(paren
id|videocodec_buf
op_plus
id|i
comma
id|size
op_minus
id|i
op_minus
l_int|1
comma
l_string|&quot;(connected as)&bslash;n&quot;
)paren
suffix:semicolon
id|h
op_assign
id|codeclist_top
suffix:semicolon
r_while
c_loop
(paren
id|h
)paren
(brace
r_if
c_cond
(paren
id|i
OG
(paren
id|size
op_minus
id|LINESIZE
)paren
)paren
r_break
suffix:semicolon
singleline_comment|// security check
id|i
op_add_assign
id|scnprintf
c_func
(paren
id|videocodec_buf
op_plus
id|i
comma
id|size
op_minus
id|i
op_minus
l_int|1
comma
l_string|&quot;S %32s %04x %08lx %08lx (TEMPLATE)&bslash;n&quot;
comma
id|h-&gt;codec-&gt;name
comma
id|h-&gt;codec-&gt;type
comma
id|h-&gt;codec-&gt;flags
comma
id|h-&gt;codec-&gt;magic
)paren
suffix:semicolon
id|a
op_assign
id|h-&gt;list
suffix:semicolon
r_while
c_loop
(paren
id|a
)paren
(brace
r_if
c_cond
(paren
id|i
OG
(paren
id|size
op_minus
id|LINESIZE
)paren
)paren
r_break
suffix:semicolon
singleline_comment|// security check
id|i
op_add_assign
id|scnprintf
c_func
(paren
id|videocodec_buf
op_plus
id|i
comma
id|size
op_minus
id|i
op_minus
l_int|1
comma
l_string|&quot;M %32s %04x %08lx %08lx (%s)&bslash;n&quot;
comma
id|a-&gt;codec-&gt;master_data-&gt;name
comma
id|a-&gt;codec-&gt;master_data-&gt;type
comma
id|a-&gt;codec-&gt;master_data-&gt;flags
comma
id|a-&gt;codec-&gt;master_data-&gt;magic
comma
id|a-&gt;codec-&gt;name
)paren
suffix:semicolon
id|a
op_assign
id|a-&gt;next
suffix:semicolon
)brace
id|h
op_assign
id|h-&gt;next
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
singleline_comment|//The definition:
singleline_comment|//typedef int (read_proc_t)(char *page, char **start, off_t off,
singleline_comment|//                          int count, int *eof, void *data);
r_static
r_int
DECL|function|videocodec_info
id|videocodec_info
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|buffer_location
comma
id|off_t
id|offset
comma
r_int
id|buffer_length
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
id|size
suffix:semicolon
id|dprintk
c_func
(paren
l_int|3
comma
l_string|&quot;videocodec_info: offset: %ld, len %d / size %d&bslash;n&quot;
comma
id|offset
comma
id|buffer_length
comma
id|videocodec_bufsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
l_int|0
)paren
(brace
id|videocodec_bufsize
op_assign
id|videocodec_build_table
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|offset
OL
l_int|0
)paren
op_logical_or
(paren
id|offset
op_ge
id|videocodec_bufsize
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec_info: call delivers no result, return 0&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buffer_length
OL
(paren
id|videocodec_bufsize
op_minus
id|offset
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec_info: %ld needed, %d got&bslash;n&quot;
comma
id|videocodec_bufsize
op_minus
id|offset
comma
id|buffer_length
)paren
suffix:semicolon
id|size
op_assign
id|buffer_length
suffix:semicolon
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;videocodec_info: last reading of %ld bytes&bslash;n&quot;
comma
id|videocodec_bufsize
op_minus
id|offset
)paren
suffix:semicolon
id|size
op_assign
id|videocodec_bufsize
op_minus
id|offset
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|buffer
comma
id|videocodec_buf
op_plus
id|offset
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* doesn&squot;t work...                           */
multiline_comment|/* copy_to_user(buffer, videocodec_buf+offset, size); */
multiline_comment|/* *buffer_location = videocodec_buf+offset; */
r_return
id|size
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* ===================== */
multiline_comment|/* hook in driver module */
multiline_comment|/* ===================== */
r_static
r_int
id|__init
DECL|function|videocodec_init
id|videocodec_init
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_struct
id|proc_dir_entry
op_star
id|videocodec_proc_entry
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Linux video codec intermediate layer: %s&bslash;n&quot;
comma
id|VIDEOCODEC_VERSION
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|videocodec_buf
op_assign
l_int|NULL
suffix:semicolon
id|videocodec_bufsize
op_assign
l_int|0
suffix:semicolon
id|videocodec_proc_entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;videocodecs&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|videocodec_proc_entry
)paren
(brace
id|videocodec_proc_entry-&gt;read_proc
op_assign
id|videocodec_info
suffix:semicolon
id|videocodec_proc_entry-&gt;write_proc
op_assign
l_int|NULL
suffix:semicolon
id|videocodec_proc_entry-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|videocodec_proc_entry-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;videocodec: can&squot;t init procfs.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|videocodec_exit
id|videocodec_exit
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
id|remove_proc_entry
c_func
(paren
l_string|&quot;videocodecs&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|videocodec_buf
)paren
id|kfree
c_func
(paren
id|videocodec_buf
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|videocodec_attach
id|EXPORT_SYMBOL
c_func
(paren
id|videocodec_attach
)paren
suffix:semicolon
DECL|variable|videocodec_detach
id|EXPORT_SYMBOL
c_func
(paren
id|videocodec_detach
)paren
suffix:semicolon
DECL|variable|videocodec_register
id|EXPORT_SYMBOL
c_func
(paren
id|videocodec_register
)paren
suffix:semicolon
DECL|variable|videocodec_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|videocodec_unregister
)paren
suffix:semicolon
DECL|variable|videocodec_init
id|module_init
c_func
(paren
id|videocodec_init
)paren
suffix:semicolon
DECL|variable|videocodec_exit
id|module_exit
c_func
(paren
id|videocodec_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Wolfgang Scherr &lt;scherr@net4you.at&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Intermediate API module for video codecs &quot;
id|VIDEOCODEC_VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
