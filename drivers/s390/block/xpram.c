multiline_comment|/*&n; * Xpram.c -- the S/390 expanded memory RAM-disk&n; *           &n; * significant parts of this code are based on&n; * the sbull device driver presented in&n; * A. Rubini: Linux Device Drivers&n; *&n; * Author of XPRAM specific coding: Reinhard Buendgen&n; *                                  buendgen@de.ibm.com&n; * Rewrite for 2.5: Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; *&n; * External interfaces:&n; *   Interfaces to linux kernel&n; *        xpram_setup: read kernel parameters&n; *   Device specific file operations&n; *        xpram_iotcl&n; *        xpram_open&n; *&n; * &quot;ad-hoc&quot; partitioning:&n; *    the expanded memory can be partitioned among several devices &n; *    (with different minors). The partitioning set up can be&n; *    set by kernel or module parameters (int devs &amp; int sizes[])&n; *&n; * Potential future improvements:&n; *   generic hard disk support to replace ad-hoc partitioning&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;  /* isdigit, isxdigit */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;  /* HDIO_GETGEO */
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|XPRAM_NAME
mdefine_line|#define XPRAM_NAME&t;&quot;xpram&quot;
DECL|macro|XPRAM_DEVS
mdefine_line|#define XPRAM_DEVS&t;1&t;/* one partition */
DECL|macro|XPRAM_MAX_DEVS
mdefine_line|#define XPRAM_MAX_DEVS&t;32&t;/* maximal number of devices (partitions) */
DECL|macro|PRINT_DEBUG
mdefine_line|#define PRINT_DEBUG(x...)&t;printk(KERN_DEBUG XPRAM_NAME &quot; debug:&quot; x)
DECL|macro|PRINT_INFO
mdefine_line|#define PRINT_INFO(x...)&t;printk(KERN_INFO XPRAM_NAME &quot; info:&quot; x)
DECL|macro|PRINT_WARN
mdefine_line|#define PRINT_WARN(x...)&t;printk(KERN_WARNING XPRAM_NAME &quot; warning:&quot; x)
DECL|macro|PRINT_ERR
mdefine_line|#define PRINT_ERR(x...)&t;&t;printk(KERN_ERR XPRAM_NAME &quot; error:&quot; x)
DECL|variable|xpram_sysclass
r_static
r_struct
id|sysdev_class
id|xpram_sysclass
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;xpram&quot;
)paren
comma
)brace
suffix:semicolon
DECL|variable|xpram_sys_device
r_static
r_struct
id|sys_device
id|xpram_sys_device
op_assign
(brace
dot
id|id
op_assign
l_int|0
comma
dot
id|cls
op_assign
op_amp
id|xpram_sysclass
comma
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of xpram segment in pages */
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* start page of xpram segment */
DECL|typedef|xpram_device_t
)brace
id|xpram_device_t
suffix:semicolon
DECL|variable|xpram_devices
r_static
id|xpram_device_t
id|xpram_devices
(braket
id|XPRAM_MAX_DEVS
)braket
suffix:semicolon
DECL|variable|xpram_sizes
r_static
r_int
r_int
id|xpram_sizes
(braket
id|XPRAM_MAX_DEVS
)braket
suffix:semicolon
DECL|variable|xpram_disks
r_static
r_struct
id|gendisk
op_star
id|xpram_disks
(braket
id|XPRAM_MAX_DEVS
)braket
suffix:semicolon
DECL|variable|xpram_pages
r_static
r_int
r_int
id|xpram_pages
suffix:semicolon
DECL|variable|xpram_devs
r_static
r_int
id|xpram_devs
suffix:semicolon
multiline_comment|/*&n; * Parameter parsing functions.&n; */
DECL|variable|devs
r_static
r_int
id|devs
op_assign
id|XPRAM_DEVS
suffix:semicolon
DECL|variable|sizes
r_static
r_int
r_int
id|sizes
(braket
id|XPRAM_MAX_DEVS
)braket
suffix:semicolon
id|module_param
c_func
(paren
id|devs
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|sizes
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|XPRAM_MAX_DEVS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|devs
comma
l_string|&quot;number of devices (&bslash;&quot;partitions&bslash;&quot;), &quot;
"&bslash;"
l_string|&quot;the default is &quot;
id|__MODULE_STRING
c_func
(paren
id|XPRAM_DEVS
)paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|sizes
comma
l_string|&quot;list of device (partition) sizes &quot;
"&bslash;"
l_string|&quot;the defaults are 0s &bslash;n&quot;
"&bslash;"
l_string|&quot;All devices with size 0 equally partition the &quot;
l_string|&quot;remaining space on the expanded strorage not &quot;
l_string|&quot;claimed by explicit sizes&bslash;n&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#ifndef MODULE
multiline_comment|/*&n; * Parses the kernel parameters given in the kernel parameter line.&n; * The expected format is&n; *           &lt;number_of_partitions&gt;[&quot;,&quot;&lt;partition_size&gt;]*&n; * where&n; *           devices is a positive integer that initializes xpram_devs&n; *           each size is a non-negative integer possibly followed by a&n; *           magnitude (k,K,m,M,g,G), the list of sizes initialises&n; *           xpram_sizes&n; *&n; * Arguments&n; *           str: substring of kernel parameter line that contains xprams&n; *                kernel parameters.&n; *&n; * Result    0 on success, -EINVAL else -- only for Version &gt; 2.3&n; *&n; * Side effects&n; *           the global variabls devs is set to the value of&n; *           &lt;number_of_partitions&gt; and sizes[i] is set to the i-th&n; *           partition size (if provided). A parsing error of a value&n; *           results in this value being set to -EINVAL.&n; */
DECL|function|xpram_setup
r_static
r_int
id|__init
id|xpram_setup
(paren
r_char
op_star
id|str
)paren
(brace
r_char
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|devs
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
op_amp
id|cp
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cp
op_le
id|str
op_logical_or
id|devs
OG
id|XPRAM_MAX_DEVS
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|devs
)paren
op_logical_and
(paren
op_star
id|cp
op_increment
op_eq
l_char|&squot;,&squot;
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sizes
(braket
id|i
)braket
op_assign
id|simple_strtoul
c_func
(paren
id|cp
comma
op_amp
id|cp
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;g&squot;
op_logical_or
op_star
id|cp
op_eq
l_char|&squot;G&squot;
)paren
(brace
id|sizes
(braket
id|i
)braket
op_lshift_assign
l_int|20
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;m&squot;
op_logical_or
op_star
id|cp
op_eq
l_char|&squot;M&squot;
)paren
(brace
id|sizes
(braket
id|i
)braket
op_lshift_assign
l_int|10
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;k&squot;
op_logical_or
op_star
id|cp
op_eq
l_char|&squot;K&squot;
)paren
id|cp
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|cp
)paren
)paren
id|cp
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;,&squot;
op_logical_and
id|i
op_ge
id|devs
)paren
id|PRINT_WARN
c_func
(paren
l_string|&quot;partition sizes list has too many entries.&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|cp
op_ne
l_int|0
)paren
id|PRINT_WARN
c_func
(paren
l_string|&quot;ignored &squot;%s&squot; at end of parameter string.&bslash;n&quot;
comma
id|cp
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;xpram_parts=&quot;
comma
id|xpram_setup
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Copy expanded memory page (4kB) into main memory                  &n; * Arguments                                                         &n; *           page_addr:    address of target page                    &n; *           xpage_index:  index of expandeded memory page           &n; * Return value                                                      &n; *           0:            if operation succeeds&n; *           -EIO:         if pgin failed&n; *           -ENXIO:       if xpram has vanished&n; */
DECL|function|xpram_page_in
r_static
r_int
id|xpram_page_in
(paren
r_int
r_int
id|page_addr
comma
r_int
r_int
id|xpage_index
)paren
(brace
r_int
id|cc
suffix:semicolon
id|__asm__
id|__volatile
c_func
(paren
l_string|&quot;   lhi   %0,2&bslash;n&quot;
multiline_comment|/* return unused cc 2 if pgin traps */
l_string|&quot;   .insn rre,0xb22e0000,%1,%2&bslash;n&quot;
multiline_comment|/* pgin %1,%2 */
l_string|&quot;0: ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
macro_line|#ifndef CONFIG_ARCH_S390X
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long  0b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
macro_line|#else
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad 0b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
macro_line|#endif
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|__pa
c_func
(paren
id|page_addr
)paren
)paren
comma
l_string|&quot;a&quot;
(paren
id|xpage_index
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cc
op_eq
l_int|3
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|cc
op_eq
l_int|2
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;expanded storage lost!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cc
op_eq
l_int|1
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;page in failed for page index %u.&bslash;n&quot;
comma
id|xpage_index
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
multiline_comment|/*&n; * Copy a 4kB page of main memory to an expanded memory page          &n; * Arguments                                                          &n; *           page_addr:    address of source page                     &n; *           xpage_index:  index of expandeded memory page            &n; * Return value                                                       &n; *           0:            if operation succeeds&n; *           -EIO:         if pgout failed&n; *           -ENXIO:       if xpram has vanished&n; */
DECL|function|xpram_page_out
r_static
r_int
id|xpram_page_out
(paren
r_int
r_int
id|page_addr
comma
r_int
r_int
id|xpage_index
)paren
(brace
r_int
id|cc
suffix:semicolon
id|__asm__
id|__volatile
c_func
(paren
l_string|&quot;   lhi   %0,2&bslash;n&quot;
multiline_comment|/* return unused cc 2 if pgout traps */
l_string|&quot;   .insn rre,0xb22f0000,%1,%2&bslash;n&quot;
multiline_comment|/* pgout %1,%2 */
l_string|&quot;0: ipm   %0&bslash;n&quot;
l_string|&quot;   srl   %0,28&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
macro_line|#ifndef CONFIG_ARCH_S390X
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 4&bslash;n&quot;
l_string|&quot;   .long  0b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
macro_line|#else
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;   .align 8&bslash;n&quot;
l_string|&quot;   .quad 0b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
macro_line|#endif
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|__pa
c_func
(paren
id|page_addr
)paren
)paren
comma
l_string|&quot;a&quot;
(paren
id|xpage_index
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cc
op_eq
l_int|3
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|cc
op_eq
l_int|2
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;expanded storage lost!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cc
op_eq
l_int|1
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;page out failed for page index %u.&bslash;n&quot;
comma
id|xpage_index
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
multiline_comment|/*&n; * Check if xpram is available.&n; */
DECL|function|xpram_present
r_static
r_int
id|__init
id|xpram_present
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|mem_page
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|mem_page
op_assign
(paren
r_int
r_int
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem_page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|rc
op_assign
id|xpram_page_in
c_func
(paren
id|mem_page
comma
l_int|0
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|mem_page
)paren
suffix:semicolon
r_return
id|rc
ques
c_cond
op_minus
id|ENXIO
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return index of the last available xpram page.&n; */
DECL|function|xpram_highest_page_index
r_static
r_int
r_int
id|__init
id|xpram_highest_page_index
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|page_index
comma
id|add_bit
suffix:semicolon
r_int
r_int
id|mem_page
suffix:semicolon
id|mem_page
op_assign
(paren
r_int
r_int
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem_page
)paren
r_return
l_int|0
suffix:semicolon
id|page_index
op_assign
l_int|0
suffix:semicolon
id|add_bit
op_assign
l_int|1ULL
op_lshift
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|8
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|add_bit
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|xpram_page_in
c_func
(paren
id|mem_page
comma
id|page_index
op_or
id|add_bit
)paren
op_eq
l_int|0
)paren
id|page_index
op_or_assign
id|add_bit
suffix:semicolon
id|add_bit
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|free_page
(paren
id|mem_page
)paren
suffix:semicolon
r_return
id|page_index
suffix:semicolon
)brace
multiline_comment|/*&n; * Block device make request function.&n; */
DECL|function|xpram_make_request
r_static
r_int
id|xpram_make_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
id|xpram_device_t
op_star
id|xdev
op_assign
id|bio-&gt;bi_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
r_struct
id|bio_vec
op_star
id|bvec
suffix:semicolon
r_int
r_int
id|index
suffix:semicolon
r_int
r_int
id|page_addr
suffix:semicolon
r_int
r_int
id|bytes
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bio-&gt;bi_sector
op_amp
l_int|3
)paren
op_ne
l_int|0
op_logical_or
(paren
id|bio-&gt;bi_size
op_amp
l_int|4095
)paren
op_ne
l_int|0
)paren
multiline_comment|/* Request is not page-aligned. */
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bio-&gt;bi_size
op_rshift
l_int|12
)paren
OG
id|xdev-&gt;size
)paren
multiline_comment|/* Request size is no page-aligned. */
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bio-&gt;bi_sector
op_rshift
l_int|3
)paren
OG
l_int|0xffffffffU
op_minus
id|xdev-&gt;offset
)paren
r_goto
id|fail
suffix:semicolon
id|index
op_assign
(paren
id|bio-&gt;bi_sector
op_rshift
l_int|3
)paren
op_plus
id|xdev-&gt;offset
suffix:semicolon
id|bio_for_each_segment
c_func
(paren
id|bvec
comma
id|bio
comma
id|i
)paren
(brace
id|page_addr
op_assign
(paren
r_int
r_int
)paren
id|kmap
c_func
(paren
id|bvec-&gt;bv_page
)paren
op_plus
id|bvec-&gt;bv_offset
suffix:semicolon
id|bytes
op_assign
id|bvec-&gt;bv_len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|page_addr
op_amp
l_int|4095
)paren
op_ne
l_int|0
op_logical_or
(paren
id|bytes
op_amp
l_int|4095
)paren
op_ne
l_int|0
)paren
multiline_comment|/* More paranoia. */
r_goto
id|fail
suffix:semicolon
r_while
c_loop
(paren
id|bytes
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|bio_data_dir
c_func
(paren
id|bio
)paren
op_eq
id|READ
)paren
(brace
r_if
c_cond
(paren
id|xpram_page_in
c_func
(paren
id|page_addr
comma
id|index
)paren
op_ne
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|xpram_page_out
c_func
(paren
id|page_addr
comma
id|index
)paren
op_ne
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
)brace
id|page_addr
op_add_assign
l_int|4096
suffix:semicolon
id|bytes
op_sub_assign
l_int|4096
suffix:semicolon
id|index
op_increment
suffix:semicolon
)brace
)brace
id|set_bit
c_func
(paren
id|BIO_UPTODATE
comma
op_amp
id|bio-&gt;bi_flags
)paren
suffix:semicolon
id|bytes
op_assign
id|bio-&gt;bi_size
suffix:semicolon
id|bio-&gt;bi_size
op_assign
l_int|0
suffix:semicolon
id|bio
op_member_access_from_pointer
id|bi_end_io
c_func
(paren
id|bio
comma
id|bytes
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|bio_io_error
c_func
(paren
id|bio
comma
id|bio-&gt;bi_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xpram_ioctl
r_static
r_int
id|xpram_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|hd_geometry
op_star
id|geo
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|HDIO_GETGEO
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * get geometry: we have to fake one...  trim the size to a&n;&t; * multiple of 64 (32k): tell we have 16 sectors, 4 heads,&n;&t; * whatever cylinders. Tell also that data starts at sector. 4.&n;&t; */
id|geo
op_assign
(paren
r_struct
id|hd_geometry
op_star
)paren
id|arg
suffix:semicolon
id|size
op_assign
(paren
id|xpram_pages
op_star
l_int|8
)paren
op_amp
op_complement
l_int|0x3f
suffix:semicolon
id|put_user
c_func
(paren
id|size
op_rshift
l_int|6
comma
op_amp
id|geo-&gt;cylinders
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|4
comma
op_amp
id|geo-&gt;heads
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|16
comma
op_amp
id|geo-&gt;sectors
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|4
comma
op_amp
id|geo-&gt;start
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|xpram_devops
r_static
r_struct
id|block_device_operations
id|xpram_devops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ioctl
op_assign
id|xpram_ioctl
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Setup xpram_sizes array.&n; */
DECL|function|xpram_setup_sizes
r_static
r_int
id|__init
id|xpram_setup_sizes
c_func
(paren
r_int
r_int
id|pages
)paren
(brace
r_int
r_int
id|mem_needed
suffix:semicolon
r_int
r_int
id|mem_auto
suffix:semicolon
r_int
id|mem_auto_no
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Check number of devices. */
r_if
c_cond
(paren
id|devs
op_le
l_int|0
op_logical_or
id|devs
OG
id|XPRAM_MAX_DEVS
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;invalid number %d of devices&bslash;n&quot;
comma
id|devs
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|xpram_devs
op_assign
id|devs
suffix:semicolon
multiline_comment|/*&n;&t; * Copy sizes array to xpram_sizes and align partition&n;&t; * sizes to page boundary.&n;&t; */
id|mem_needed
op_assign
l_int|0
suffix:semicolon
id|mem_auto_no
op_assign
l_int|0
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
id|xpram_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|xpram_sizes
(braket
id|i
)braket
op_assign
(paren
id|sizes
(braket
id|i
)braket
op_plus
l_int|3
)paren
op_amp
op_minus
l_int|4UL
suffix:semicolon
r_if
c_cond
(paren
id|xpram_sizes
(braket
id|i
)braket
)paren
id|mem_needed
op_add_assign
id|xpram_sizes
(braket
id|i
)braket
suffix:semicolon
r_else
id|mem_auto_no
op_increment
suffix:semicolon
)brace
id|PRINT_INFO
c_func
(paren
l_string|&quot;  number of devices (partitions): %d &bslash;n&quot;
comma
id|xpram_devs
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
id|xpram_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|xpram_sizes
(braket
id|i
)braket
)paren
id|PRINT_INFO
c_func
(paren
l_string|&quot;  size of partition %d: %u kB&bslash;n&quot;
comma
id|i
comma
id|xpram_sizes
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|PRINT_INFO
c_func
(paren
l_string|&quot;  size of partition %d to be set &quot;
l_string|&quot;automatically&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;  memory needed (for sized partitions): %lu kB&bslash;n&quot;
comma
id|mem_needed
)paren
suffix:semicolon
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;  partitions to be sized automatically: %d&bslash;n&quot;
comma
id|mem_auto_no
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_needed
OG
id|pages
op_star
l_int|4
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;Not enough expanded memory available&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * partitioning:&n;&t; * xpram_sizes[i] != 0; partition i has size xpram_sizes[i] kB&n;&t; * else:             ; all partitions with zero xpram_sizes[i]&n;&t; *                     partition equally the remaining space&n;&t; */
r_if
c_cond
(paren
id|mem_auto_no
)paren
(brace
id|mem_auto
op_assign
(paren
(paren
id|pages
op_minus
id|mem_needed
op_div
l_int|4
)paren
op_div
id|mem_auto_no
)paren
op_star
l_int|4
suffix:semicolon
id|PRINT_INFO
c_func
(paren
l_string|&quot;  automatically determined &quot;
l_string|&quot;partition size: %lu kB&bslash;n&quot;
comma
id|mem_auto
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
id|xpram_devs
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|xpram_sizes
(braket
id|i
)braket
op_eq
l_int|0
)paren
id|xpram_sizes
(braket
id|i
)braket
op_assign
id|mem_auto
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|xpram_queue
r_static
r_struct
id|request_queue
id|xpram_queue
suffix:semicolon
DECL|function|xpram_setup_blkdev
r_static
r_int
id|__init
id|xpram_setup_blkdev
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
r_int
id|i
comma
id|rc
op_assign
op_minus
id|ENOMEM
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
id|xpram_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
op_assign
id|alloc_disk
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disk
)paren
r_goto
id|out
suffix:semicolon
id|xpram_disks
(braket
id|i
)braket
op_assign
id|disk
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Register xpram major.&n;&t; */
id|rc
op_assign
id|register_blkdev
c_func
(paren
id|XPRAM_MAJOR
comma
id|XPRAM_NAME
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|devfs_mk_dir
c_func
(paren
l_string|&quot;slram&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Assign the other needed values: make request function, sizes and&n;&t; * hardsect size. All the minor devices feature the same value.&n;&t; */
id|blk_queue_make_request
c_func
(paren
op_amp
id|xpram_queue
comma
id|xpram_make_request
)paren
suffix:semicolon
id|blk_queue_hardsect_size
c_func
(paren
op_amp
id|xpram_queue
comma
l_int|4096
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup device structures.&n;&t; */
id|offset
op_assign
l_int|0
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
id|xpram_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
op_assign
id|xpram_disks
(braket
id|i
)braket
suffix:semicolon
id|xpram_devices
(braket
id|i
)braket
dot
id|size
op_assign
id|xpram_sizes
(braket
id|i
)braket
op_div
l_int|4
suffix:semicolon
id|xpram_devices
(braket
id|i
)braket
dot
id|offset
op_assign
id|offset
suffix:semicolon
id|offset
op_add_assign
id|xpram_devices
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|disk-&gt;major
op_assign
id|XPRAM_MAJOR
suffix:semicolon
id|disk-&gt;first_minor
op_assign
id|i
suffix:semicolon
id|disk-&gt;fops
op_assign
op_amp
id|xpram_devops
suffix:semicolon
id|disk-&gt;private_data
op_assign
op_amp
id|xpram_devices
(braket
id|i
)braket
suffix:semicolon
id|disk-&gt;queue
op_assign
op_amp
id|xpram_queue
suffix:semicolon
id|sprintf
c_func
(paren
id|disk-&gt;disk_name
comma
l_string|&quot;slram%d&quot;
comma
id|i
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|disk-&gt;devfs_name
comma
l_string|&quot;slram/%d&quot;
comma
id|i
)paren
suffix:semicolon
id|set_capacity
c_func
(paren
id|disk
comma
id|xpram_sizes
(braket
id|i
)braket
op_lshift
l_int|1
)paren
suffix:semicolon
id|add_disk
c_func
(paren
id|disk
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|put_disk
c_func
(paren
id|xpram_disks
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Finally, the init/exit functions.&n; */
DECL|function|xpram_exit
r_static
r_void
id|__exit
id|xpram_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|xpram_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|del_gendisk
c_func
(paren
id|xpram_disks
(braket
id|i
)braket
)paren
suffix:semicolon
id|put_disk
c_func
(paren
id|xpram_disks
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|unregister_blkdev
c_func
(paren
id|XPRAM_MAJOR
comma
id|XPRAM_NAME
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;slram&quot;
)paren
suffix:semicolon
id|sysdev_unregister
c_func
(paren
op_amp
id|xpram_sys_device
)paren
suffix:semicolon
id|sysdev_class_unregister
c_func
(paren
op_amp
id|xpram_sysclass
)paren
suffix:semicolon
)brace
DECL|function|xpram_init
r_static
r_int
id|__init
id|xpram_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
multiline_comment|/* Find out size of expanded memory. */
r_if
c_cond
(paren
id|xpram_present
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
id|PRINT_WARN
c_func
(paren
l_string|&quot;No expanded memory available&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|xpram_pages
op_assign
id|xpram_highest_page_index
c_func
(paren
)paren
suffix:semicolon
id|PRINT_INFO
c_func
(paren
l_string|&quot;  %u pages expanded memory found (%lu KB).&bslash;n&quot;
comma
id|xpram_pages
comma
(paren
r_int
r_int
)paren
id|xpram_pages
op_star
l_int|4
)paren
suffix:semicolon
id|rc
op_assign
id|xpram_setup_sizes
c_func
(paren
id|xpram_pages
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
id|rc
op_assign
id|sysdev_class_register
c_func
(paren
op_amp
id|xpram_sysclass
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
id|rc
op_assign
id|sysdev_register
c_func
(paren
op_amp
id|xpram_sys_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|sysdev_class_unregister
c_func
(paren
op_amp
id|xpram_sysclass
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|rc
op_assign
id|xpram_setup_blkdev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|sysdev_unregister
c_func
(paren
op_amp
id|xpram_sys_device
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|xpram_init
id|module_init
c_func
(paren
id|xpram_init
)paren
suffix:semicolon
DECL|variable|xpram_exit
id|module_exit
c_func
(paren
id|xpram_exit
)paren
suffix:semicolon
eof
