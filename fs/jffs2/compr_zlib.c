multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001-2003 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@redhat.com&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: compr_zlib.c,v 1.28 2004/06/23 16:34:40 havasi Exp $&n; *&n; */
macro_line|#if !defined(__KERNEL__) &amp;&amp; !defined(__ECOS)
macro_line|#error &quot;The userspace support got too messy and was removed. Update your mkfs.jffs2&quot;
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/zlib.h&gt;
macro_line|#include &lt;linux/zutil.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;nodelist.h&quot;
macro_line|#include &quot;compr.h&quot;
multiline_comment|/* Plan: call deflate() with avail_in == *sourcelen, &n;&t;&t;avail_out = *dstlen - 12 and flush == Z_FINISH. &n;&t;&t;If it doesn&squot;t manage to finish,&t;call it again with&n;&t;&t;avail_in == 0 and avail_out set to the remaining 12&n;&t;&t;bytes for it to clean up. &n;&t;   Q: Is 12 bytes sufficient?&n;&t;*/
DECL|macro|STREAM_END_SPACE
mdefine_line|#define STREAM_END_SPACE 12
r_static
id|DECLARE_MUTEX
c_func
(paren
id|deflate_sem
)paren
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|inflate_sem
)paren
suffix:semicolon
DECL|variable|inf_strm
DECL|variable|def_strm
r_static
id|z_stream
id|inf_strm
comma
id|def_strm
suffix:semicolon
macro_line|#ifdef __KERNEL__ /* Linux-only */
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|function|alloc_workspaces
r_static
r_int
id|__init
id|alloc_workspaces
c_func
(paren
r_void
)paren
(brace
id|def_strm.workspace
op_assign
id|vmalloc
c_func
(paren
id|zlib_deflate_workspacesize
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|def_strm.workspace
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Failed to allocate %d bytes for deflate workspace&bslash;n&quot;
comma
id|zlib_deflate_workspacesize
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Allocated %d bytes for deflate workspace&bslash;n&quot;
comma
id|zlib_deflate_workspacesize
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
id|inf_strm.workspace
op_assign
id|vmalloc
c_func
(paren
id|zlib_inflate_workspacesize
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inf_strm.workspace
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Failed to allocate %d bytes for inflate workspace&bslash;n&quot;
comma
id|zlib_inflate_workspacesize
c_func
(paren
)paren
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|def_strm.workspace
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Allocated %d bytes for inflate workspace&bslash;n&quot;
comma
id|zlib_inflate_workspacesize
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_workspaces
r_static
r_void
id|free_workspaces
c_func
(paren
r_void
)paren
(brace
id|vfree
c_func
(paren
id|def_strm.workspace
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|inf_strm.workspace
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|alloc_workspaces
mdefine_line|#define alloc_workspaces() (0)
DECL|macro|free_workspaces
mdefine_line|#define free_workspaces() do { } while(0)
macro_line|#endif /* __KERNEL__ */
DECL|function|jffs2_zlib_compress
r_int
id|jffs2_zlib_compress
c_func
(paren
r_int
r_char
op_star
id|data_in
comma
r_int
r_char
op_star
id|cpage_out
comma
r_uint32
op_star
id|sourcelen
comma
r_uint32
op_star
id|dstlen
comma
r_void
op_star
id|model
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_star
id|dstlen
op_le
id|STREAM_END_SPACE
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|down
c_func
(paren
op_amp
id|deflate_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Z_OK
op_ne
id|zlib_deflateInit
c_func
(paren
op_amp
id|def_strm
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;deflateInit failed&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|deflate_sem
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|def_strm.next_in
op_assign
id|data_in
suffix:semicolon
id|def_strm.total_in
op_assign
l_int|0
suffix:semicolon
id|def_strm.next_out
op_assign
id|cpage_out
suffix:semicolon
id|def_strm.total_out
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|def_strm.total_out
OL
op_star
id|dstlen
op_minus
id|STREAM_END_SPACE
op_logical_and
id|def_strm.total_in
OL
op_star
id|sourcelen
)paren
(brace
id|def_strm.avail_out
op_assign
op_star
id|dstlen
op_minus
(paren
id|def_strm.total_out
op_plus
id|STREAM_END_SPACE
)paren
suffix:semicolon
id|def_strm.avail_in
op_assign
id|min
c_func
(paren
(paren
r_int
)paren
(paren
op_star
id|sourcelen
op_minus
id|def_strm.total_in
)paren
comma
id|def_strm.avail_out
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;calling deflate with avail_in %d, avail_out %d&bslash;n&quot;
comma
id|def_strm.avail_in
comma
id|def_strm.avail_out
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|zlib_deflate
c_func
(paren
op_amp
id|def_strm
comma
id|Z_PARTIAL_FLUSH
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;deflate returned with avail_in %d, avail_out %d, total_in %ld, total_out %ld&bslash;n&quot;
comma
id|def_strm.avail_in
comma
id|def_strm.avail_out
comma
id|def_strm.total_in
comma
id|def_strm.total_out
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|Z_OK
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;deflate in loop returned %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
id|zlib_deflateEnd
c_func
(paren
op_amp
id|def_strm
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|deflate_sem
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|def_strm.avail_out
op_add_assign
id|STREAM_END_SPACE
suffix:semicolon
id|def_strm.avail_in
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|zlib_deflate
c_func
(paren
op_amp
id|def_strm
comma
id|Z_FINISH
)paren
suffix:semicolon
id|zlib_deflateEnd
c_func
(paren
op_amp
id|def_strm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|Z_STREAM_END
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;final deflate returned %d&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|def_strm.total_out
op_ge
id|def_strm.total_in
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;zlib compressed %ld bytes into %ld; failing&bslash;n&quot;
comma
id|def_strm.total_in
comma
id|def_strm.total_out
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;zlib compressed %ld bytes into %ld&bslash;n&quot;
comma
id|def_strm.total_in
comma
id|def_strm.total_out
)paren
)paren
suffix:semicolon
op_star
id|dstlen
op_assign
id|def_strm.total_out
suffix:semicolon
op_star
id|sourcelen
op_assign
id|def_strm.total_in
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|deflate_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_zlib_decompress
r_int
id|jffs2_zlib_decompress
c_func
(paren
r_int
r_char
op_star
id|data_in
comma
r_int
r_char
op_star
id|cpage_out
comma
r_uint32
id|srclen
comma
r_uint32
id|destlen
comma
r_void
op_star
id|model
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
id|wbits
op_assign
id|MAX_WBITS
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inflate_sem
)paren
suffix:semicolon
id|inf_strm.next_in
op_assign
id|data_in
suffix:semicolon
id|inf_strm.avail_in
op_assign
id|srclen
suffix:semicolon
id|inf_strm.total_in
op_assign
l_int|0
suffix:semicolon
id|inf_strm.next_out
op_assign
id|cpage_out
suffix:semicolon
id|inf_strm.avail_out
op_assign
id|destlen
suffix:semicolon
id|inf_strm.total_out
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* If it&squot;s deflate, and it&squot;s got no preset dictionary, then&n;&t;   we can tell zlib to skip the adler32 check. */
r_if
c_cond
(paren
id|srclen
OG
l_int|2
op_logical_and
op_logical_neg
(paren
id|data_in
(braket
l_int|1
)braket
op_amp
id|PRESET_DICT
)paren
op_logical_and
(paren
(paren
id|data_in
(braket
l_int|0
)braket
op_amp
l_int|0x0f
)paren
op_eq
id|Z_DEFLATED
)paren
op_logical_and
op_logical_neg
(paren
(paren
(paren
id|data_in
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_plus
id|data_in
(braket
l_int|1
)braket
)paren
op_mod
l_int|31
)paren
)paren
(brace
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;inflate skipping adler32&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|wbits
op_assign
op_minus
(paren
(paren
id|data_in
(braket
l_int|0
)braket
op_rshift
l_int|4
)paren
op_plus
l_int|8
)paren
suffix:semicolon
id|inf_strm.next_in
op_add_assign
l_int|2
suffix:semicolon
id|inf_strm.avail_in
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Let this remain D1 for now -- it should never happen */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;inflate not skipping adler32&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|Z_OK
op_ne
id|zlib_inflateInit2
c_func
(paren
op_amp
id|inf_strm
comma
id|wbits
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;inflateInit failed&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inflate_sem
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|ret
op_assign
id|zlib_inflate
c_func
(paren
op_amp
id|inf_strm
comma
id|Z_FINISH
)paren
)paren
op_eq
id|Z_OK
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_ne
id|Z_STREAM_END
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;inflate returned %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
)brace
id|zlib_inflateEnd
c_func
(paren
op_amp
id|inf_strm
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inflate_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|jffs2_zlib_comp
r_static
r_struct
id|jffs2_compressor
id|jffs2_zlib_comp
op_assign
(brace
dot
id|priority
op_assign
id|JFFS2_ZLIB_PRIORITY
comma
dot
id|name
op_assign
l_string|&quot;zlib&quot;
comma
dot
id|compr
op_assign
id|JFFS2_COMPR_ZLIB
comma
dot
id|compress
op_assign
op_amp
id|jffs2_zlib_compress
comma
dot
id|decompress
op_assign
op_amp
id|jffs2_zlib_decompress
comma
macro_line|#ifdef JFFS2_ZLIB_DISABLED
dot
id|disabled
op_assign
l_int|1
comma
macro_line|#else
dot
id|disabled
op_assign
l_int|0
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|jffs2_zlib_init
r_int
id|__init
id|jffs2_zlib_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|alloc_workspaces
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|ret
op_assign
id|jffs2_register_compressor
c_func
(paren
op_amp
id|jffs2_zlib_comp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|free_workspaces
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_zlib_exit
r_void
id|jffs2_zlib_exit
c_func
(paren
r_void
)paren
(brace
id|jffs2_unregister_compressor
c_func
(paren
op_amp
id|jffs2_zlib_comp
)paren
suffix:semicolon
id|free_workspaces
c_func
(paren
)paren
suffix:semicolon
)brace
eof
