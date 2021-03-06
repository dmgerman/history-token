multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001-2003 Red Hat, Inc.&n; * Created by Arjan van de Ven &lt;arjanv@redhat.com&gt;&n; *&n; * Copyright (C) 2004 Ferenc Havasi &lt;havasi@inf.u-szeged.hu&gt;,&n; *                    University of Szeged, Hungary&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: compr.c,v 1.42 2004/08/07 21:56:08 dwmw2 Exp $&n; *&n; */
macro_line|#include &quot;compr.h&quot;
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
multiline_comment|/* Available compressors are on this list */
r_static
id|LIST_HEAD
c_func
(paren
id|jffs2_compressor_list
)paren
suffix:semicolon
multiline_comment|/* Actual compression mode */
DECL|variable|jffs2_compression_mode
r_static
r_int
id|jffs2_compression_mode
op_assign
id|JFFS2_COMPR_MODE_PRIORITY
suffix:semicolon
multiline_comment|/* Statistics for blocks stored without compression */
DECL|variable|none_stat_compr_blocks
DECL|variable|none_stat_decompr_blocks
DECL|variable|none_stat_compr_size
r_static
r_uint32
id|none_stat_compr_blocks
op_assign
l_int|0
comma
id|none_stat_decompr_blocks
op_assign
l_int|0
comma
id|none_stat_compr_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* jffs2_compress:&n; * @data: Pointer to uncompressed data&n; * @cdata: Pointer to returned pointer to buffer for compressed data&n; * @datalen: On entry, holds the amount of data available for compression.&n; *&t;On exit, expected to hold the amount of data actually compressed.&n; * @cdatalen: On entry, holds the amount of space available for compressed&n; *&t;data. On exit, expected to hold the actual size of the compressed&n; *&t;data.&n; *&n; * Returns: Lower byte to be stored with data indicating compression type used.&n; * Zero is used to show that the data could not be compressed - the &n; * compressed version was actually larger than the original.&n; * Upper byte will be used later. (soon)&n; *&n; * If the cdata buffer isn&squot;t large enough to hold all the uncompressed data,&n; * jffs2_compress should compress as much as will fit, and should set &n; * *datalen accordingly to show the amount of data which were compressed.&n; */
DECL|function|jffs2_compress
r_uint16
id|jffs2_compress
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_info
op_star
id|f
comma
r_int
r_char
op_star
id|data_in
comma
r_int
r_char
op_star
op_star
id|cpage_out
comma
r_uint32
op_star
id|datalen
comma
r_uint32
op_star
id|cdatalen
)paren
(brace
r_int
id|ret
op_assign
id|JFFS2_COMPR_NONE
suffix:semicolon
r_int
id|compr_ret
suffix:semicolon
r_struct
id|jffs2_compressor
op_star
id|this
comma
op_star
id|best
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
op_star
id|output_buf
op_assign
l_int|NULL
comma
op_star
id|tmp_buf
suffix:semicolon
r_uint32
id|orig_slen
comma
id|orig_dlen
suffix:semicolon
r_uint32
id|best_slen
op_assign
l_int|0
comma
id|best_dlen
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|jffs2_compression_mode
)paren
(brace
r_case
id|JFFS2_COMPR_MODE_NONE
suffix:colon
r_break
suffix:semicolon
r_case
id|JFFS2_COMPR_MODE_PRIORITY
suffix:colon
id|output_buf
op_assign
id|kmalloc
c_func
(paren
op_star
id|cdatalen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|output_buf
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;JFFS2: No memory for compressor allocation. Compression failed.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|orig_slen
op_assign
op_star
id|datalen
suffix:semicolon
id|orig_dlen
op_assign
op_star
id|cdatalen
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
multiline_comment|/* Skip decompress-only backwards-compatibility and disabled modules */
r_if
c_cond
(paren
(paren
op_logical_neg
id|this-&gt;compress
)paren
op_logical_or
(paren
id|this-&gt;disabled
)paren
)paren
r_continue
suffix:semicolon
id|this-&gt;usecount
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
op_star
id|datalen
op_assign
id|orig_slen
suffix:semicolon
op_star
id|cdatalen
op_assign
id|orig_dlen
suffix:semicolon
id|compr_ret
op_assign
id|this
op_member_access_from_pointer
id|compress
c_func
(paren
id|data_in
comma
id|output_buf
comma
id|datalen
comma
id|cdatalen
comma
l_int|NULL
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|this-&gt;usecount
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|compr_ret
)paren
(brace
id|ret
op_assign
id|this-&gt;compr
suffix:semicolon
id|this-&gt;stat_compr_blocks
op_increment
suffix:semicolon
id|this-&gt;stat_compr_orig_size
op_add_assign
op_star
id|datalen
suffix:semicolon
id|this-&gt;stat_compr_new_size
op_add_assign
op_star
id|cdatalen
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|JFFS2_COMPR_NONE
)paren
id|kfree
c_func
(paren
id|output_buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|JFFS2_COMPR_MODE_SIZE
suffix:colon
id|orig_slen
op_assign
op_star
id|datalen
suffix:semicolon
id|orig_dlen
op_assign
op_star
id|cdatalen
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
multiline_comment|/* Skip decompress-only backwards-compatibility and disabled modules */
r_if
c_cond
(paren
(paren
op_logical_neg
id|this-&gt;compress
)paren
op_logical_or
(paren
id|this-&gt;disabled
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Allocating memory for output buffer if necessary */
r_if
c_cond
(paren
(paren
id|this-&gt;compr_buf_size
OL
id|orig_dlen
)paren
op_logical_and
(paren
id|this-&gt;compr_buf
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|this-&gt;compr_buf
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|this-&gt;compr_buf_size
op_assign
l_int|0
suffix:semicolon
id|this-&gt;compr_buf
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|this-&gt;compr_buf
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|tmp_buf
op_assign
id|kmalloc
c_func
(paren
id|orig_dlen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp_buf
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;JFFS2: No memory for compressor allocation. (%d bytes)&bslash;n&quot;
comma
id|orig_dlen
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
(brace
id|this-&gt;compr_buf
op_assign
id|tmp_buf
suffix:semicolon
id|this-&gt;compr_buf_size
op_assign
id|orig_dlen
suffix:semicolon
)brace
)brace
id|this-&gt;usecount
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
op_star
id|datalen
op_assign
id|orig_slen
suffix:semicolon
op_star
id|cdatalen
op_assign
id|orig_dlen
suffix:semicolon
id|compr_ret
op_assign
id|this
op_member_access_from_pointer
id|compress
c_func
(paren
id|data_in
comma
id|this-&gt;compr_buf
comma
id|datalen
comma
id|cdatalen
comma
l_int|NULL
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|this-&gt;usecount
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|compr_ret
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|best_dlen
)paren
op_logical_or
(paren
id|best_dlen
OG
op_star
id|cdatalen
)paren
)paren
(brace
id|best_dlen
op_assign
op_star
id|cdatalen
suffix:semicolon
id|best_slen
op_assign
op_star
id|datalen
suffix:semicolon
id|best
op_assign
id|this
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|best_dlen
)paren
(brace
op_star
id|cdatalen
op_assign
id|best_dlen
suffix:semicolon
op_star
id|datalen
op_assign
id|best_slen
suffix:semicolon
id|output_buf
op_assign
id|best-&gt;compr_buf
suffix:semicolon
id|best-&gt;compr_buf
op_assign
l_int|NULL
suffix:semicolon
id|best-&gt;compr_buf_size
op_assign
l_int|0
suffix:semicolon
id|best-&gt;stat_compr_blocks
op_increment
suffix:semicolon
id|best-&gt;stat_compr_orig_size
op_add_assign
id|best_slen
suffix:semicolon
id|best-&gt;stat_compr_new_size
op_add_assign
id|best_dlen
suffix:semicolon
id|ret
op_assign
id|best-&gt;compr
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFFS2: unknow compression mode.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|ret
op_eq
id|JFFS2_COMPR_NONE
)paren
(brace
op_star
id|cpage_out
op_assign
id|data_in
suffix:semicolon
op_star
id|datalen
op_assign
op_star
id|cdatalen
suffix:semicolon
id|none_stat_compr_blocks
op_increment
suffix:semicolon
id|none_stat_compr_size
op_add_assign
op_star
id|datalen
suffix:semicolon
)brace
r_else
(brace
op_star
id|cpage_out
op_assign
id|output_buf
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_decompress
r_int
id|jffs2_decompress
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_struct
id|jffs2_inode_info
op_star
id|f
comma
r_uint16
id|comprtype
comma
r_int
r_char
op_star
id|cdata_in
comma
r_int
r_char
op_star
id|data_out
comma
r_uint32
id|cdatalen
comma
r_uint32
id|datalen
)paren
(brace
r_struct
id|jffs2_compressor
op_star
id|this
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* Older code had a bug where it would write non-zero &squot;usercompr&squot;&n;&t;   fields. Deal with it. */
r_if
c_cond
(paren
(paren
id|comprtype
op_amp
l_int|0xff
)paren
op_le
id|JFFS2_COMPR_ZLIB
)paren
id|comprtype
op_and_assign
l_int|0xff
suffix:semicolon
r_switch
c_cond
(paren
id|comprtype
op_amp
l_int|0xff
)paren
(brace
r_case
id|JFFS2_COMPR_NONE
suffix:colon
multiline_comment|/* This should be special-cased elsewhere, but we might as well deal with it */
id|memcpy
c_func
(paren
id|data_out
comma
id|cdata_in
comma
id|datalen
)paren
suffix:semicolon
id|none_stat_decompr_blocks
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|JFFS2_COMPR_ZERO
suffix:colon
id|memset
c_func
(paren
id|data_out
comma
l_int|0
comma
id|datalen
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|comprtype
op_eq
id|this-&gt;compr
)paren
(brace
id|this-&gt;usecount
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|ret
op_assign
id|this
op_member_access_from_pointer
id|decompress
c_func
(paren
id|cdata_in
comma
id|data_out
comma
id|cdatalen
comma
id|datalen
comma
l_int|NULL
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Decompressor &bslash;&quot;%s&bslash;&quot; returned %d&bslash;n&quot;
comma
id|this-&gt;name
comma
id|ret
)paren
suffix:semicolon
)brace
r_else
(brace
id|this-&gt;stat_decompr_blocks
op_increment
suffix:semicolon
)brace
id|this-&gt;usecount
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;JFFS2 compression type 0x%02x not available.&bslash;n&quot;
comma
id|comprtype
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_register_compressor
r_int
id|jffs2_register_compressor
c_func
(paren
r_struct
id|jffs2_compressor
op_star
id|comp
)paren
(brace
r_struct
id|jffs2_compressor
op_star
id|this
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|comp-&gt;name
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NULL compressor name at registering JFFS2 compressor. Failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|comp-&gt;compr_buf_size
op_assign
l_int|0
suffix:semicolon
id|comp-&gt;compr_buf
op_assign
l_int|NULL
suffix:semicolon
id|comp-&gt;usecount
op_assign
l_int|0
suffix:semicolon
id|comp-&gt;stat_compr_orig_size
op_assign
l_int|0
suffix:semicolon
id|comp-&gt;stat_compr_new_size
op_assign
l_int|0
suffix:semicolon
id|comp-&gt;stat_compr_blocks
op_assign
l_int|0
suffix:semicolon
id|comp-&gt;stat_decompr_blocks
op_assign
l_int|0
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Registering JFFS2 compressor &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|comp-&gt;name
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|this-&gt;priority
OL
id|comp-&gt;priority
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|comp-&gt;list
comma
id|this-&gt;list.prev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|list_add_tail
c_func
(paren
op_amp
id|comp-&gt;list
comma
op_amp
id|jffs2_compressor_list
)paren
suffix:semicolon
id|out
suffix:colon
id|D2
c_func
(paren
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Compressor &bslash;&quot;%s&bslash;&quot;, prio %d&bslash;n&quot;
comma
id|this-&gt;name
comma
id|this-&gt;priority
)paren
suffix:semicolon
)brace
)paren
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_unregister_compressor
r_int
id|jffs2_unregister_compressor
c_func
(paren
r_struct
id|jffs2_compressor
op_star
id|comp
)paren
(brace
id|D2
c_func
(paren
r_struct
id|jffs2_compressor
op_star
id|this
suffix:semicolon
)paren
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Unregistering JFFS2 compressor &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|comp-&gt;name
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|comp-&gt;usecount
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;JFFS2: Compressor modul is in use. Unregister failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|list_del
c_func
(paren
op_amp
id|comp-&gt;list
)paren
suffix:semicolon
id|D2
c_func
(paren
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Compressor &bslash;&quot;%s&bslash;&quot;, prio %d&bslash;n&quot;
comma
id|this-&gt;name
comma
id|this-&gt;priority
)paren
suffix:semicolon
)brace
)paren
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_JFFS2_PROC
DECL|macro|JFFS2_STAT_BUF_SIZE
mdefine_line|#define JFFS2_STAT_BUF_SIZE 16000
DECL|function|jffs2_list_compressors
r_char
op_star
id|jffs2_list_compressors
c_func
(paren
r_void
)paren
(brace
r_struct
id|jffs2_compressor
op_star
id|this
suffix:semicolon
r_char
op_star
id|buf
comma
op_star
id|act_buf
suffix:semicolon
id|act_buf
op_assign
id|buf
op_assign
id|kmalloc
c_func
(paren
id|JFFS2_STAT_BUF_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;%10s priority:%d &quot;
comma
id|this-&gt;name
comma
id|this-&gt;priority
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|this-&gt;disabled
)paren
op_logical_or
(paren
op_logical_neg
id|this-&gt;compress
)paren
)paren
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;disabled&quot;
)paren
suffix:semicolon
r_else
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;enabled&quot;
)paren
suffix:semicolon
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|buf
suffix:semicolon
)brace
DECL|function|jffs2_stats
r_char
op_star
id|jffs2_stats
c_func
(paren
r_void
)paren
(brace
r_struct
id|jffs2_compressor
op_star
id|this
suffix:semicolon
r_char
op_star
id|buf
comma
op_star
id|act_buf
suffix:semicolon
id|act_buf
op_assign
id|buf
op_assign
id|kmalloc
c_func
(paren
id|JFFS2_STAT_BUF_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;JFFS2 compressor statistics:&bslash;n&quot;
)paren
suffix:semicolon
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;%10s   &quot;
comma
l_string|&quot;none&quot;
)paren
suffix:semicolon
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;compr: %d blocks (%d)  decompr: %d blocks&bslash;n&quot;
comma
id|none_stat_compr_blocks
comma
id|none_stat_compr_size
comma
id|none_stat_decompr_blocks
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;%10s &quot;
comma
id|this-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|this-&gt;disabled
)paren
op_logical_or
(paren
op_logical_neg
id|this-&gt;compress
)paren
)paren
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;- &quot;
)paren
suffix:semicolon
r_else
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;+ &quot;
)paren
suffix:semicolon
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;compr: %d blocks (%d/%d)  decompr: %d blocks &quot;
comma
id|this-&gt;stat_compr_blocks
comma
id|this-&gt;stat_compr_new_size
comma
id|this-&gt;stat_compr_orig_size
comma
id|this-&gt;stat_decompr_blocks
)paren
suffix:semicolon
id|act_buf
op_add_assign
id|sprintf
c_func
(paren
id|act_buf
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|function|jffs2_get_compression_mode_name
r_char
op_star
id|jffs2_get_compression_mode_name
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|jffs2_compression_mode
)paren
(brace
r_case
id|JFFS2_COMPR_MODE_NONE
suffix:colon
r_return
l_string|&quot;none&quot;
suffix:semicolon
r_case
id|JFFS2_COMPR_MODE_PRIORITY
suffix:colon
r_return
l_string|&quot;priority&quot;
suffix:semicolon
r_case
id|JFFS2_COMPR_MODE_SIZE
suffix:colon
r_return
l_string|&quot;size&quot;
suffix:semicolon
)brace
r_return
l_string|&quot;unkown&quot;
suffix:semicolon
)brace
DECL|function|jffs2_set_compression_mode_name
r_int
id|jffs2_set_compression_mode_name
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;none&quot;
comma
id|name
)paren
)paren
(brace
id|jffs2_compression_mode
op_assign
id|JFFS2_COMPR_MODE_NONE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;priority&quot;
comma
id|name
)paren
)paren
(brace
id|jffs2_compression_mode
op_assign
id|JFFS2_COMPR_MODE_PRIORITY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;size&quot;
comma
id|name
)paren
)paren
(brace
id|jffs2_compression_mode
op_assign
id|JFFS2_COMPR_MODE_SIZE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|jffs2_compressor_Xable
r_static
r_int
id|jffs2_compressor_Xable
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|disabled
)paren
(brace
r_struct
id|jffs2_compressor
op_star
id|this
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this-&gt;name
comma
id|name
)paren
)paren
(brace
id|this-&gt;disabled
op_assign
id|disabled
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;JFFS2: compressor %s not found.&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|jffs2_enable_compressor_name
r_int
id|jffs2_enable_compressor_name
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_return
id|jffs2_compressor_Xable
c_func
(paren
id|name
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|jffs2_disable_compressor_name
r_int
id|jffs2_disable_compressor_name
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_return
id|jffs2_compressor_Xable
c_func
(paren
id|name
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|jffs2_set_compressor_priority
r_int
id|jffs2_set_compressor_priority
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|priority
)paren
(brace
r_struct
id|jffs2_compressor
op_star
id|this
comma
op_star
id|comp
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this-&gt;name
comma
id|name
)paren
)paren
(brace
id|this-&gt;priority
op_assign
id|priority
suffix:semicolon
id|comp
op_assign
id|this
suffix:semicolon
r_goto
id|reinsert
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;JFFS2: compressor %s not found.&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|reinsert
suffix:colon
multiline_comment|/* list is sorted in the order of priority, so if&n;           we change it we have to reinsert it into the&n;           good place */
id|list_del
c_func
(paren
op_amp
id|comp-&gt;list
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|this
comma
op_amp
id|jffs2_compressor_list
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|this-&gt;priority
OL
id|comp-&gt;priority
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|comp-&gt;list
comma
id|this-&gt;list.prev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|list_add_tail
c_func
(paren
op_amp
id|comp-&gt;list
comma
op_amp
id|jffs2_compressor_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|jffs2_compressor_list_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|jffs2_free_comprbuf
r_void
id|jffs2_free_comprbuf
c_func
(paren
r_int
r_char
op_star
id|comprbuf
comma
r_int
r_char
op_star
id|orig
)paren
(brace
r_if
c_cond
(paren
id|orig
op_ne
id|comprbuf
)paren
id|kfree
c_func
(paren
id|comprbuf
)paren
suffix:semicolon
)brace
DECL|function|jffs2_compressors_init
r_int
id|jffs2_compressors_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Registering compressors */
macro_line|#ifdef CONFIG_JFFS2_ZLIB
id|jffs2_zlib_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JFFS2_RTIME
id|jffs2_rtime_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JFFS2_RUBIN
id|jffs2_rubinmips_init
c_func
(paren
)paren
suffix:semicolon
id|jffs2_dynrubin_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JFFS2_LZARI
id|jffs2_lzari_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JFFS2_LZO
id|jffs2_lzo_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Setting default compression mode */
macro_line|#ifdef CONFIG_JFFS2_CMODE_NONE
id|jffs2_compression_mode
op_assign
id|JFFS2_COMPR_MODE_NONE
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;JFFS2: default compression mode: none&bslash;n&quot;
)paren
suffix:semicolon
)paren
macro_line|#else
macro_line|#ifdef CONFIG_JFFS2_CMODE_SIZE
id|jffs2_compression_mode
op_assign
id|JFFS2_COMPR_MODE_SIZE
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;JFFS2: default compression mode: size&bslash;n&quot;
)paren
suffix:semicolon
)paren
macro_line|#else
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;JFFS2: default compression mode: priority&bslash;n&quot;
)paren
suffix:semicolon
)paren
macro_line|#endif
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_compressors_exit
r_int
id|jffs2_compressors_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Unregistering compressors */
macro_line|#ifdef CONFIG_JFFS2_LZO
id|jffs2_lzo_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JFFS2_LZARI
id|jffs2_lzari_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JFFS2_RUBIN
id|jffs2_dynrubin_exit
c_func
(paren
)paren
suffix:semicolon
id|jffs2_rubinmips_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JFFS2_RTIME
id|jffs2_rtime_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JFFS2_ZLIB
id|jffs2_zlib_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
