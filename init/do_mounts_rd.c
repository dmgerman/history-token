macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/romfs_fs.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &quot;do_mounts.h&quot;
DECL|macro|BUILD_CRAMDISK
mdefine_line|#define BUILD_CRAMDISK
DECL|variable|rd_prompt
r_int
id|__initdata
id|rd_prompt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* 1 = prompt for RAM disk, 0 = don&squot;t prompt */
DECL|function|prompt_ramdisk
r_static
r_int
id|__init
id|prompt_ramdisk
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|rd_prompt
op_assign
id|simple_strtol
c_func
(paren
id|str
comma
l_int|NULL
comma
l_int|0
)paren
op_amp
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;prompt_ramdisk=&quot;
comma
id|prompt_ramdisk
)paren
suffix:semicolon
DECL|variable|rd_image_start
r_int
id|__initdata
id|rd_image_start
suffix:semicolon
multiline_comment|/* starting block # of image */
DECL|function|ramdisk_start_setup
r_static
r_int
id|__init
id|ramdisk_start_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|rd_image_start
op_assign
id|simple_strtol
c_func
(paren
id|str
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;ramdisk_start=&quot;
comma
id|ramdisk_start_setup
)paren
suffix:semicolon
r_static
r_int
id|__init
id|crd_load
c_func
(paren
r_int
id|in_fd
comma
r_int
id|out_fd
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine tries to find a RAM disk image to load, and returns the&n; * number of blocks to read for a non-compressed image, 0 if the image&n; * is a compressed image, and -1 if an image with the right magic&n; * numbers could not be found.&n; *&n; * We currently check for the following magic numbers:&n; * &t;minix&n; * &t;ext2&n; *&t;romfs&n; * &t;gzip&n; */
r_static
r_int
id|__init
DECL|function|identify_ramdisk_image
id|identify_ramdisk_image
c_func
(paren
r_int
id|fd
comma
r_int
id|start_block
)paren
(brace
r_const
r_int
id|size
op_assign
l_int|512
suffix:semicolon
r_struct
id|minix_super_block
op_star
id|minixsb
suffix:semicolon
r_struct
id|ext2_super_block
op_star
id|ext2sb
suffix:semicolon
r_struct
id|romfs_super_block
op_star
id|romfsb
suffix:semicolon
r_int
id|nblocks
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
r_char
op_star
id|buf
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|minixsb
op_assign
(paren
r_struct
id|minix_super_block
op_star
)paren
id|buf
suffix:semicolon
id|ext2sb
op_assign
(paren
r_struct
id|ext2_super_block
op_star
)paren
id|buf
suffix:semicolon
id|romfsb
op_assign
(paren
r_struct
id|romfs_super_block
op_star
)paren
id|buf
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0xe5
comma
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Read block 0 to test for gzipped kernel&n;&t; */
id|lseek
c_func
(paren
id|fd
comma
id|start_block
op_star
id|BLOCK_SIZE
comma
l_int|0
)paren
suffix:semicolon
id|read
c_func
(paren
id|fd
comma
id|buf
comma
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If it matches the gzip magic numbers, return -1&n;&t; */
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_eq
l_int|037
op_logical_and
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_eq
l_int|0213
)paren
op_logical_or
(paren
id|buf
(braket
l_int|1
)braket
op_eq
l_int|0236
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;RAMDISK: Compressed image found at block %d&bslash;n&quot;
comma
id|start_block
)paren
suffix:semicolon
id|nblocks
op_assign
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/* romfs is at block zero too */
r_if
c_cond
(paren
id|romfsb-&gt;word0
op_eq
id|ROMSB_WORD0
op_logical_and
id|romfsb-&gt;word1
op_eq
id|ROMSB_WORD1
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;RAMDISK: romfs filesystem found at block %d&bslash;n&quot;
comma
id|start_block
)paren
suffix:semicolon
id|nblocks
op_assign
(paren
id|ntohl
c_func
(paren
id|romfsb-&gt;size
)paren
op_plus
id|BLOCK_SIZE
op_minus
l_int|1
)paren
op_rshift
id|BLOCK_SIZE_BITS
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Read block 1 to test for minix and ext2 superblock&n;&t; */
id|lseek
c_func
(paren
id|fd
comma
(paren
id|start_block
op_plus
l_int|1
)paren
op_star
id|BLOCK_SIZE
comma
l_int|0
)paren
suffix:semicolon
id|read
c_func
(paren
id|fd
comma
id|buf
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Try minix */
r_if
c_cond
(paren
id|minixsb-&gt;s_magic
op_eq
id|MINIX_SUPER_MAGIC
op_logical_or
id|minixsb-&gt;s_magic
op_eq
id|MINIX_SUPER_MAGIC2
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;RAMDISK: Minix filesystem found at block %d&bslash;n&quot;
comma
id|start_block
)paren
suffix:semicolon
id|nblocks
op_assign
id|minixsb-&gt;s_nzones
op_lshift
id|minixsb-&gt;s_log_zone_size
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/* Try ext2 */
r_if
c_cond
(paren
id|ext2sb-&gt;s_magic
op_eq
id|cpu_to_le16
c_func
(paren
id|EXT2_SUPER_MAGIC
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;RAMDISK: ext2 filesystem found at block %d&bslash;n&quot;
comma
id|start_block
)paren
suffix:semicolon
id|nblocks
op_assign
id|le32_to_cpu
c_func
(paren
id|ext2sb-&gt;s_blocks_count
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;RAMDISK: Couldn&squot;t find valid RAM disk image starting at %d.&bslash;n&quot;
comma
id|start_block
)paren
suffix:semicolon
id|done
suffix:colon
id|lseek
c_func
(paren
id|fd
comma
id|start_block
op_star
id|BLOCK_SIZE
comma
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|nblocks
suffix:semicolon
)brace
DECL|function|rd_load_image
r_int
id|__init
id|rd_load_image
c_func
(paren
r_char
op_star
id|from
)paren
(brace
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_int
id|in_fd
comma
id|out_fd
suffix:semicolon
r_int
r_int
id|rd_blocks
comma
id|devblocks
suffix:semicolon
r_int
id|nblocks
comma
id|i
comma
id|disk
suffix:semicolon
r_char
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|rotate
op_assign
l_int|0
suffix:semicolon
macro_line|#if !defined(CONFIG_ARCH_S390) &amp;&amp; !defined(CONFIG_PPC_ISERIES)
r_char
id|rotator
(braket
l_int|4
)braket
op_assign
(brace
l_char|&squot;|&squot;
comma
l_char|&squot;/&squot;
comma
l_char|&squot;-&squot;
comma
l_char|&squot;&bslash;&bslash;&squot;
)brace
suffix:semicolon
macro_line|#endif
id|out_fd
op_assign
id|open
c_func
(paren
l_string|&quot;/dev/ram&quot;
comma
id|O_RDWR
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_fd
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|in_fd
op_assign
id|open
c_func
(paren
id|from
comma
id|O_RDONLY
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_fd
OL
l_int|0
)paren
r_goto
id|noclose_input
suffix:semicolon
id|nblocks
op_assign
id|identify_ramdisk_image
c_func
(paren
id|in_fd
comma
id|rd_image_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nblocks
OL
l_int|0
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|nblocks
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef BUILD_CRAMDISK
r_if
c_cond
(paren
id|crd_load
c_func
(paren
id|in_fd
comma
id|out_fd
)paren
op_eq
l_int|0
)paren
r_goto
id|successful_load
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;RAMDISK: Kernel does not support compressed &quot;
l_string|&quot;RAM disk images&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * NOTE NOTE: nblocks suppose that the blocksize is BLOCK_SIZE, so&n;&t; * rd_load_image will work only with filesystem BLOCK_SIZE wide!&n;&t; * So make sure to use 1k blocksize while generating ext2fs&n;&t; * ramdisk-images.&n;&t; */
r_if
c_cond
(paren
id|sys_ioctl
c_func
(paren
id|out_fd
comma
id|BLKGETSIZE
comma
(paren
r_int
r_int
)paren
op_amp
id|rd_blocks
)paren
OL
l_int|0
)paren
id|rd_blocks
op_assign
l_int|0
suffix:semicolon
r_else
id|rd_blocks
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|nblocks
OG
id|rd_blocks
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RAMDISK: image too big! (%d/%ld blocks)&bslash;n&quot;
comma
id|nblocks
comma
id|rd_blocks
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * OK, time to copy in the data&n;&t; */
r_if
c_cond
(paren
id|sys_ioctl
c_func
(paren
id|in_fd
comma
id|BLKGETSIZE
comma
(paren
r_int
r_int
)paren
op_amp
id|devblocks
)paren
OL
l_int|0
)paren
id|devblocks
op_assign
l_int|0
suffix:semicolon
r_else
id|devblocks
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|from
comma
l_string|&quot;/dev/initrd&quot;
)paren
op_eq
l_int|0
)paren
id|devblocks
op_assign
id|nblocks
suffix:semicolon
r_if
c_cond
(paren
id|devblocks
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;RAMDISK: could not determine device size&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|buf
op_assign
id|kmalloc
c_func
(paren
id|BLOCK_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;RAMDISK: could not allocate buffer&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;RAMDISK: Loading %d blocks [%ld disk%s] into ram disk... &quot;
comma
id|nblocks
comma
(paren
(paren
id|nblocks
op_minus
l_int|1
)paren
op_div
id|devblocks
)paren
op_plus
l_int|1
comma
id|nblocks
OG
id|devblocks
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|disk
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|nblocks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_logical_and
(paren
id|i
op_mod
id|devblocks
op_eq
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;done disk #%d.&bslash;n&quot;
comma
id|disk
op_increment
)paren
suffix:semicolon
id|rotate
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|close
c_func
(paren
id|in_fd
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Error closing the disk.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|noclose_input
suffix:semicolon
)brace
id|change_floppy
c_func
(paren
l_string|&quot;disk #%d&quot;
comma
id|disk
)paren
suffix:semicolon
id|in_fd
op_assign
id|open
c_func
(paren
id|from
comma
id|O_RDONLY
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_fd
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Error opening disk.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|noclose_input
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Loading disk #%d... &quot;
comma
id|disk
)paren
suffix:semicolon
)brace
id|read
c_func
(paren
id|in_fd
comma
id|buf
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
id|write
c_func
(paren
id|out_fd
comma
id|buf
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_ARCH_S390) &amp;&amp; !defined(CONFIG_PPC_ISERIES)
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_mod
l_int|16
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%c&bslash;b&quot;
comma
id|rotator
(braket
id|rotate
op_amp
l_int|0x3
)braket
)paren
suffix:semicolon
id|rotate
op_increment
suffix:semicolon
)brace
macro_line|#endif
)brace
id|printk
c_func
(paren
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
id|successful_load
suffix:colon
id|res
op_assign
l_int|1
suffix:semicolon
id|done
suffix:colon
id|close
c_func
(paren
id|in_fd
)paren
suffix:semicolon
id|noclose_input
suffix:colon
id|close
c_func
(paren
id|out_fd
)paren
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|sys_unlink
c_func
(paren
l_string|&quot;/dev/ram&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|rd_load_disk
r_int
id|__init
id|rd_load_disk
c_func
(paren
r_int
id|n
)paren
(brace
r_if
c_cond
(paren
id|rd_prompt
)paren
id|change_floppy
c_func
(paren
l_string|&quot;root floppy disk to be loaded into RAM disk&quot;
)paren
suffix:semicolon
id|create_dev
c_func
(paren
l_string|&quot;/dev/root&quot;
comma
id|ROOT_DEV
comma
id|root_device_name
)paren
suffix:semicolon
id|create_dev
c_func
(paren
l_string|&quot;/dev/ram&quot;
comma
id|MKDEV
c_func
(paren
id|RAMDISK_MAJOR
comma
id|n
)paren
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|rd_load_image
c_func
(paren
l_string|&quot;/dev/root&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef BUILD_CRAMDISK
multiline_comment|/*&n; * gzip declarations&n; */
DECL|macro|OF
mdefine_line|#define OF(args)  args
macro_line|#ifndef memzero
DECL|macro|memzero
mdefine_line|#define memzero(s, n)     memset ((s), 0, (n))
macro_line|#endif
DECL|typedef|uch
r_typedef
r_int
r_char
id|uch
suffix:semicolon
DECL|typedef|ush
r_typedef
r_int
r_int
id|ush
suffix:semicolon
DECL|typedef|ulg
r_typedef
r_int
r_int
id|ulg
suffix:semicolon
DECL|macro|INBUFSIZ
mdefine_line|#define INBUFSIZ 4096
DECL|macro|WSIZE
mdefine_line|#define WSIZE 0x8000    /* window size--must be a power of two, and */
multiline_comment|/*  at least 32K for zip&squot;s deflate method */
DECL|variable|inbuf
r_static
id|uch
op_star
id|inbuf
suffix:semicolon
DECL|variable|window
r_static
id|uch
op_star
id|window
suffix:semicolon
DECL|variable|insize
r_static
r_int
id|insize
suffix:semicolon
multiline_comment|/* valid bytes in inbuf */
DECL|variable|inptr
r_static
r_int
id|inptr
suffix:semicolon
multiline_comment|/* index of next byte to be processed in inbuf */
DECL|variable|outcnt
r_static
r_int
id|outcnt
suffix:semicolon
multiline_comment|/* bytes in output buffer */
DECL|variable|exit_code
r_static
r_int
id|exit_code
suffix:semicolon
DECL|variable|unzip_error
r_static
r_int
id|unzip_error
suffix:semicolon
DECL|variable|bytes_out
r_static
r_int
id|bytes_out
suffix:semicolon
DECL|variable|crd_infd
DECL|variable|crd_outfd
r_static
r_int
id|crd_infd
comma
id|crd_outfd
suffix:semicolon
DECL|macro|get_byte
mdefine_line|#define get_byte()  (inptr &lt; insize ? inbuf[inptr++] : fill_inbuf())
multiline_comment|/* Diagnostic functions (stubbed out) */
DECL|macro|Assert
mdefine_line|#define Assert(cond,msg)
DECL|macro|Trace
mdefine_line|#define Trace(x)
DECL|macro|Tracev
mdefine_line|#define Tracev(x)
DECL|macro|Tracevv
mdefine_line|#define Tracevv(x)
DECL|macro|Tracec
mdefine_line|#define Tracec(c,x)
DECL|macro|Tracecv
mdefine_line|#define Tracecv(c,x)
DECL|macro|STATIC
mdefine_line|#define STATIC static
r_static
r_int
id|fill_inbuf
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|flush_window
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
op_star
id|malloc
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
r_static
r_void
id|free
c_func
(paren
r_void
op_star
id|where
)paren
suffix:semicolon
r_static
r_void
id|error
c_func
(paren
r_char
op_star
id|m
)paren
suffix:semicolon
r_static
r_void
id|gzip_mark
c_func
(paren
r_void
op_star
op_star
)paren
suffix:semicolon
r_static
r_void
id|gzip_release
c_func
(paren
r_void
op_star
op_star
)paren
suffix:semicolon
macro_line|#include &quot;../lib/inflate.c&quot;
DECL|function|malloc
r_static
r_void
id|__init
op_star
id|malloc
c_func
(paren
r_int
id|size
)paren
(brace
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
DECL|function|free
r_static
r_void
id|__init
id|free
c_func
(paren
r_void
op_star
id|where
)paren
(brace
id|kfree
c_func
(paren
id|where
)paren
suffix:semicolon
)brace
DECL|function|gzip_mark
r_static
r_void
id|__init
id|gzip_mark
c_func
(paren
r_void
op_star
op_star
id|ptr
)paren
(brace
)brace
DECL|function|gzip_release
r_static
r_void
id|__init
id|gzip_release
c_func
(paren
r_void
op_star
op_star
id|ptr
)paren
(brace
)brace
multiline_comment|/* ===========================================================================&n; * Fill the input buffer. This is called only when the buffer is empty&n; * and at least one byte is really needed.&n; * Returning -1 does not guarantee that gunzip() will ever return.&n; */
DECL|function|fill_inbuf
r_static
r_int
id|__init
id|fill_inbuf
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|exit_code
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|insize
op_assign
id|read
c_func
(paren
id|crd_infd
comma
id|inbuf
comma
id|INBUFSIZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|insize
op_eq
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;RAMDISK: ran out of compressed data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|inptr
op_assign
l_int|1
suffix:semicolon
r_return
id|inbuf
(braket
l_int|0
)braket
suffix:semicolon
)brace
multiline_comment|/* ===========================================================================&n; * Write the output window window[0..outcnt-1] and update crc and bytes_out.&n; * (Used for the decompressed data only.)&n; */
DECL|function|flush_window
r_static
r_void
id|__init
id|flush_window
c_func
(paren
r_void
)paren
(brace
id|ulg
id|c
op_assign
id|crc
suffix:semicolon
multiline_comment|/* temporary variable */
r_int
id|n
comma
id|written
suffix:semicolon
id|uch
op_star
id|in
comma
id|ch
suffix:semicolon
id|written
op_assign
id|write
c_func
(paren
id|crd_outfd
comma
id|window
comma
id|outcnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|written
op_ne
id|outcnt
op_logical_and
id|unzip_error
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;RAMDISK: incomplete write (%d != %d) %ld&bslash;n&quot;
comma
id|written
comma
id|outcnt
comma
id|bytes_out
)paren
suffix:semicolon
id|unzip_error
op_assign
l_int|1
suffix:semicolon
)brace
id|in
op_assign
id|window
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|outcnt
suffix:semicolon
id|n
op_increment
)paren
(brace
id|ch
op_assign
op_star
id|in
op_increment
suffix:semicolon
id|c
op_assign
id|crc_32_tab
(braket
(paren
(paren
r_int
)paren
id|c
op_xor
id|ch
)paren
op_amp
l_int|0xff
)braket
op_xor
(paren
id|c
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
id|crc
op_assign
id|c
suffix:semicolon
id|bytes_out
op_add_assign
(paren
id|ulg
)paren
id|outcnt
suffix:semicolon
id|outcnt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|error
r_static
r_void
id|__init
id|error
c_func
(paren
r_char
op_star
id|x
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s&quot;
comma
id|x
)paren
suffix:semicolon
id|exit_code
op_assign
l_int|1
suffix:semicolon
id|unzip_error
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|crd_load
r_static
r_int
id|__init
id|crd_load
c_func
(paren
r_int
id|in_fd
comma
r_int
id|out_fd
)paren
(brace
r_int
id|result
suffix:semicolon
id|insize
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* valid bytes in inbuf */
id|inptr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* index of next byte to be processed in inbuf */
id|outcnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* bytes in output buffer */
id|exit_code
op_assign
l_int|0
suffix:semicolon
id|bytes_out
op_assign
l_int|0
suffix:semicolon
id|crc
op_assign
(paren
id|ulg
)paren
l_int|0xffffffffL
suffix:semicolon
multiline_comment|/* shift register contents */
id|crd_infd
op_assign
id|in_fd
suffix:semicolon
id|crd_outfd
op_assign
id|out_fd
suffix:semicolon
id|inbuf
op_assign
id|kmalloc
c_func
(paren
id|INBUFSIZ
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inbuf
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;RAMDISK: Couldn&squot;t allocate gzip buffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|window
op_assign
id|kmalloc
c_func
(paren
id|WSIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|window
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;RAMDISK: Couldn&squot;t allocate gzip window&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|inbuf
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|makecrc
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
id|gunzip
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unzip_error
)paren
id|result
op_assign
l_int|1
suffix:semicolon
id|kfree
c_func
(paren
id|inbuf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|window
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif  /* BUILD_CRAMDISK */
eof
