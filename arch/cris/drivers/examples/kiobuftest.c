multiline_comment|/*&n; * Example showing how to pin down a range of virtual pages from user-space&n; * to be able to do for example DMA directly into them.&n; *&n; * It is necessary because the pages the virtual pointers reference, might&n; * not exist in memory (could be mapped to the zero-page, filemapped etc)&n; * and DMA cannot trigger the MMU to force them in (and would have time &n; * contraints making it impossible to wait for it anyway).&n; *&n; * Author:  Bjorn Wesen&n; *&n; * $Log: kiobuftest.c,v $&n; * Revision 1.2  2001/02/27 13:52:50  bjornw&n; * malloc.h -&gt; slab.h&n; *&n; * Revision 1.1  2001/01/19 15:57:49  bjornw&n; * Example of how to do direct HW -&gt; user-mode DMA&n; *&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/iobuf.h&gt;
DECL|macro|KIOBUFTEST_MAJOR
mdefine_line|#define KIOBUFTEST_MAJOR 124  /* in the local range, experimental */
r_static
id|ssize_t
DECL|function|kiobuf_read
id|kiobuf_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|kiobuf
op_star
id|iobuf
suffix:semicolon
r_int
id|res
comma
id|i
suffix:semicolon
multiline_comment|/* Make a kiobuf that maps the entire length the reader has given&n;      * us&n;      */
id|res
op_assign
id|alloc_kiovec
c_func
(paren
l_int|1
comma
op_amp
id|iobuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_return
id|res
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|map_user_kiobuf
c_func
(paren
id|READ
comma
id|iobuf
comma
(paren
r_int
r_int
)paren
id|buf
comma
id|len
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;map_user_kiobuf failed, return %d&bslash;n&quot;
comma
id|res
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* At this point, the virtual area buf[0] -&gt; buf[len-1] will&n;      * have corresponding pages mapped in physical memory and locked&n;      * until we unmap the kiobuf. They cannot be swapped out or moved&n;      * around.&n;      */
id|printk
c_func
(paren
l_string|&quot;nr_pages == %d&bslash;noffset == %d&bslash;nlength == %d&bslash;n&quot;
comma
id|iobuf-&gt;nr_pages
comma
id|iobuf-&gt;offset
comma
id|iobuf-&gt;length
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
id|iobuf-&gt;nr_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;page_add(maplist[%d]) == 0x%x&bslash;n&quot;
comma
id|i
comma
id|page_address
c_func
(paren
id|iobuf-&gt;maplist
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* This is the place to create the necessary scatter-gather vector&n;      * for the DMA using the iobuf-&gt;maplist array and page_address&n;      * (don&squot;t forget __pa if the DMA needs the actual physical DRAM address)&n;      * and run it.&n;      */
multiline_comment|/* Release the mapping and exit */
id|unmap_kiobuf
c_func
(paren
id|iobuf
)paren
suffix:semicolon
multiline_comment|/* The unlock_kiobuf is implicit here */
r_return
id|len
suffix:semicolon
)brace
DECL|variable|kiobuf_fops
r_static
r_struct
id|file_operations
id|kiobuf_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|kiobuf_read
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|kiobuftest_init
id|kiobuftest_init
c_func
(paren
r_void
)paren
(brace
r_int
id|res
suffix:semicolon
multiline_comment|/* register char device */
id|res
op_assign
id|register_chrdev
c_func
(paren
id|KIOBUFTEST_MAJOR
comma
l_string|&quot;kiobuftest&quot;
comma
op_amp
id|kiobuf_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kiobuftest: couldn&squot;t get a major number.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Initializing kiobuf-test device&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|kiobuftest_init
id|module_init
c_func
(paren
id|kiobuftest_init
)paren
suffix:semicolon
eof
