multiline_comment|/*&n; * drivers/sbus/char/jsflash.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&t;(drivers/char/mem.c)&n; *  Copyright (C) 1997  Eddie C. Dost&t;&t;(drivers/sbus/char/flash.c)&n; *  Copyright (C) 1997-2000 Pavel Machek &lt;pavel@ucw.cz&gt;   (drivers/block/nbd.c)&n; *  Copyright (C) 1999-2000 Pete Zaitcev&n; *&n; * This driver is used to program OS into a Flash SIMM on&n; * Krups and Espresso platforms.&n; *&n; * TODO: do not allow erase/programming if file systems are mounted.&n; * TODO: Erase/program both banks of a 8MB SIMM.&n; *&n; * It is anticipated that programming an OS Flash will be a routine&n; * procedure. In the same time it is exeedingly dangerous because&n; * a user can program its OBP flash with OS image and effectively&n; * kill the machine.&n; *&n; * This driver uses an interface different from Eddie&squot;s flash.c&n; * as a silly safeguard.&n; *&n; * XXX The flash.c manipulates page caching characteristics in a certain&n; * dubious way; also it assumes that remap_pfn_range() can remap&n; * PCI bus locations, which may be false. ioremap() must be used&n; * instead. We should discuss this.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR&t;JSFD_MAJOR
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pcic.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/jsflash.h&gt;&t;&t;/* ioctl arguments. &lt;linux/&gt; ?? */
DECL|macro|JSFIDSZ
mdefine_line|#define JSFIDSZ&t;&t;(sizeof(struct jsflash_ident_arg))
DECL|macro|JSFPRGSZ
mdefine_line|#define JSFPRGSZ&t;(sizeof(struct jsflash_program_arg))
multiline_comment|/*&n; * Our device numbers have no business in system headers.&n; * The only thing a user knows is the device name /dev/jsflash.&n; *&n; * Block devices are laid out like this:&n; *   minor+0&t;- Bootstrap, for 8MB SIMM 0x20400000[0x800000]&n; *   minor+1&t;- Filesystem to mount, normally 0x20400400[0x7ffc00]&n; *   minor+2&t;- Whole flash area for any case... 0x20000000[0x01000000]&n; * Total 3 minors per flash device.&n; *&n; * It is easier to have static size vectors, so we define&n; * a total minor range JSF_MAX, which must cover all minors.&n; */
multiline_comment|/* character device */
DECL|macro|JSF_MINOR
mdefine_line|#define JSF_MINOR&t;178&t;/* 178 is registered with hpa */
multiline_comment|/* block device */
DECL|macro|JSF_MAX
mdefine_line|#define JSF_MAX&t;&t; 3&t;/* 3 minors wasted total so far. */
DECL|macro|JSF_NPART
mdefine_line|#define JSF_NPART&t; 3&t;/* 3 minors per flash device */
DECL|macro|JSF_PART_BITS
mdefine_line|#define JSF_PART_BITS&t; 2&t;/* 2 bits of minors to cover JSF_NPART */
DECL|macro|JSF_PART_MASK
mdefine_line|#define JSF_PART_MASK&t; 0x3&t;/* 2 bits mask */
multiline_comment|/*&n; * Access functions.&n; * We could ioremap(), but it&squot;s easier this way.&n; */
DECL|function|jsf_inl
r_static
r_int
r_int
id|jsf_inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_BYPASS
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|jsf_outl
r_static
r_void
id|jsf_outl
c_func
(paren
r_int
r_int
id|addr
comma
id|__u32
id|data
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %0, [%1] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|data
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_BYPASS
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * soft carrier&n; */
DECL|struct|jsfd_part
r_struct
id|jsfd_part
(brace
DECL|member|dbase
r_int
r_int
id|dbase
suffix:semicolon
DECL|member|dsize
r_int
r_int
id|dsize
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|jsflash
r_struct
id|jsflash
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|busy
r_int
r_int
id|busy
suffix:semicolon
multiline_comment|/* In use? */
DECL|member|id
r_struct
id|jsflash_ident_arg
id|id
suffix:semicolon
multiline_comment|/* int mbase; */
multiline_comment|/* Minor base, typically zero */
DECL|member|dv
r_struct
id|jsfd_part
id|dv
(braket
id|JSF_NPART
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * We do not map normal memory or obio as a safety precaution.&n; * But offsets are real, for ease of userland programming.&n; */
DECL|macro|JSF_BASE_TOP
mdefine_line|#define JSF_BASE_TOP&t;0x30000000
DECL|macro|JSF_BASE_ALL
mdefine_line|#define JSF_BASE_ALL&t;0x20000000
DECL|macro|JSF_BASE_JK
mdefine_line|#define JSF_BASE_JK&t;0x20400000
multiline_comment|/*&n; */
DECL|variable|jsfd_disk
r_static
r_struct
id|gendisk
op_star
id|jsfd_disk
(braket
id|JSF_MAX
)braket
suffix:semicolon
multiline_comment|/*&n; * Let&squot;s pretend we may have several of these...&n; */
DECL|variable|jsf0
r_static
r_struct
id|jsflash
id|jsf0
suffix:semicolon
multiline_comment|/*&n; * Wait for AMD to finish its embedded algorithm.&n; * We use the Toggle bit DQ6 (0x40) because it does not&n; * depend on the data value as /DATA bit DQ7 does.&n; *&n; * XXX Do we need any timeout here? So far it never hanged, beware broken hw.&n; */
DECL|function|jsf_wait
r_static
r_void
id|jsf_wait
c_func
(paren
r_int
r_int
id|p
)paren
(brace
r_int
r_int
id|x1
comma
id|x2
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|x1
op_assign
id|jsf_inl
c_func
(paren
id|p
)paren
suffix:semicolon
id|x2
op_assign
id|jsf_inl
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x1
op_amp
l_int|0x40404040
)paren
op_eq
(paren
id|x2
op_amp
l_int|0x40404040
)paren
)paren
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Programming will only work if Flash is clean,&n; * we leave it to the programmer application.&n; *&n; * AMD must be programmed one byte at a time;&n; * thus, Simple Tech SIMM must be written 4 bytes at a time.&n; *&n; * Write waits for the chip to become ready after the write&n; * was finished. This is done so that application would read&n; * consistent data after the write is done.&n; */
DECL|function|jsf_write4
r_static
r_void
id|jsf_write4
c_func
(paren
r_int
r_int
id|fa
comma
id|u32
id|data
)paren
(brace
id|jsf_outl
c_func
(paren
id|fa
comma
l_int|0xAAAAAAAA
)paren
suffix:semicolon
multiline_comment|/* Unlock 1 Write 1 */
id|jsf_outl
c_func
(paren
id|fa
comma
l_int|0x55555555
)paren
suffix:semicolon
multiline_comment|/* Unlock 1 Write 2 */
id|jsf_outl
c_func
(paren
id|fa
comma
l_int|0xA0A0A0A0
)paren
suffix:semicolon
multiline_comment|/* Byte Program */
id|jsf_outl
c_func
(paren
id|fa
comma
id|data
)paren
suffix:semicolon
id|jsf_wait
c_func
(paren
id|fa
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|function|jsfd_read
r_static
r_void
id|jsfd_read
c_func
(paren
r_char
op_star
id|buf
comma
r_int
r_int
id|p
comma
r_int
id|togo
)paren
(brace
r_union
id|byte4
(brace
r_char
id|s
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
)brace
id|b
suffix:semicolon
r_while
c_loop
(paren
id|togo
op_ge
l_int|4
)paren
(brace
id|togo
op_sub_assign
l_int|4
suffix:semicolon
id|b.n
op_assign
id|jsf_inl
c_func
(paren
id|p
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|b.s
comma
l_int|4
)paren
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
id|buf
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
DECL|function|jsfd_do_request
r_static
r_void
id|jsfd_do_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_while
c_loop
(paren
(paren
id|req
op_assign
id|elv_next_request
c_func
(paren
id|q
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|jsfd_part
op_star
id|jdp
op_assign
id|req-&gt;rq_disk-&gt;private_data
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|req-&gt;sector
op_lshift
l_int|9
suffix:semicolon
r_int
id|len
op_assign
id|req-&gt;current_nr_sectors
op_lshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
(paren
id|offset
op_plus
id|len
)paren
OG
id|jdp-&gt;dsize
)paren
(brace
id|end_request
c_func
(paren
id|req
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|req
)paren
op_ne
id|READ
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;jsfd: write&bslash;n&quot;
)paren
suffix:semicolon
id|end_request
c_func
(paren
id|req
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|jdp-&gt;dbase
op_amp
l_int|0xff000000
)paren
op_ne
l_int|0x20000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;jsfd: bad base %x&bslash;n&quot;
comma
(paren
r_int
)paren
id|jdp-&gt;dbase
)paren
suffix:semicolon
id|end_request
c_func
(paren
id|req
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|jsfd_read
c_func
(paren
id|req-&gt;buffer
comma
id|jdp-&gt;dbase
op_plus
id|offset
comma
id|len
)paren
suffix:semicolon
id|end_request
c_func
(paren
id|req
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The memory devices use the full 32/64 bits of the offset, and so we cannot&n; * check against negative addresses: they are ok. The return value is weird,&n; * though, in that case (0).&n; *&n; * also note that seeking relative to the &quot;end of file&quot; isn&squot;t supported:&n; * it has no meaning, so it returns -EINVAL.&n; */
DECL|function|jsf_lseek
r_static
id|loff_t
id|jsf_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
id|loff_t
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|ret
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
id|ret
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * OS SIMM Cannot be read in other size but a 32bits word.&n; */
DECL|function|jsf_read
r_static
id|ssize_t
id|jsf_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|togo
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
r_int
id|p
op_assign
op_star
id|ppos
suffix:semicolon
r_char
op_star
id|tmp
op_assign
id|buf
suffix:semicolon
r_union
id|byte4
(brace
r_char
id|s
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
)brace
id|b
suffix:semicolon
r_if
c_cond
(paren
id|p
OL
id|JSF_BASE_ALL
op_logical_or
id|p
op_ge
id|JSF_BASE_TOP
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|p
op_plus
id|togo
)paren
OL
id|p
multiline_comment|/* wrap */
op_logical_or
(paren
id|p
op_plus
id|togo
)paren
op_ge
id|JSF_BASE_TOP
)paren
(brace
id|togo
op_assign
id|JSF_BASE_TOP
op_minus
id|p
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
OL
id|JSF_BASE_ALL
op_logical_and
id|togo
op_ne
l_int|0
)paren
(brace
macro_line|#if 0 /* __bzero XXX */
r_int
id|x
op_assign
id|JSF_BASE_ALL
op_minus
id|p
suffix:semicolon
r_if
c_cond
(paren
id|x
OG
id|togo
)paren
id|x
op_assign
id|togo
suffix:semicolon
id|clear_user
c_func
(paren
id|tmp
comma
id|x
)paren
suffix:semicolon
id|tmp
op_add_assign
id|x
suffix:semicolon
id|p
op_add_assign
id|x
suffix:semicolon
id|togo
op_sub_assign
id|x
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t;&t; * Implementation of clear_user() calls __bzero&n;&t;&t; * without regard to modversions,&n;&t;&t; * so we cannot build a module.&n;&t;&t; */
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
r_while
c_loop
(paren
id|togo
op_ge
l_int|4
)paren
(brace
id|togo
op_sub_assign
l_int|4
suffix:semicolon
id|b.n
op_assign
id|jsf_inl
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|tmp
comma
id|b.s
comma
l_int|4
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|tmp
op_add_assign
l_int|4
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * XXX Small togo may remain if 1 byte is ordered.&n;&t; * It would be nice if we did a word size read and unpacked it.&n;&t; */
op_star
id|ppos
op_assign
id|p
suffix:semicolon
r_return
id|tmp
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|jsf_write
r_static
id|ssize_t
id|jsf_write
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
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|function|jsf_ioctl_erase
r_static
r_int
id|jsf_ioctl_erase
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_int
r_int
id|p
suffix:semicolon
multiline_comment|/* p = jsf0.base;&t;hits wrong bank */
id|p
op_assign
l_int|0x20400000
suffix:semicolon
id|jsf_outl
c_func
(paren
id|p
comma
l_int|0xAAAAAAAA
)paren
suffix:semicolon
multiline_comment|/* Unlock 1 Write 1 */
id|jsf_outl
c_func
(paren
id|p
comma
l_int|0x55555555
)paren
suffix:semicolon
multiline_comment|/* Unlock 1 Write 2 */
id|jsf_outl
c_func
(paren
id|p
comma
l_int|0x80808080
)paren
suffix:semicolon
multiline_comment|/* Erase setup */
id|jsf_outl
c_func
(paren
id|p
comma
l_int|0xAAAAAAAA
)paren
suffix:semicolon
multiline_comment|/* Unlock 2 Write 1 */
id|jsf_outl
c_func
(paren
id|p
comma
l_int|0x55555555
)paren
suffix:semicolon
multiline_comment|/* Unlock 2 Write 2 */
id|jsf_outl
c_func
(paren
id|p
comma
l_int|0x10101010
)paren
suffix:semicolon
multiline_comment|/* Chip erase */
macro_line|#if 0
multiline_comment|/*&n;&t; * This code is ok, except that counter based timeout&n;&t; * has no place in this world. Let&squot;s just drop timeouts...&n;&t; */
(brace
r_int
id|i
suffix:semicolon
id|__u32
id|x
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
l_int|1000000
suffix:semicolon
id|i
op_increment
)paren
(brace
id|x
op_assign
id|jsf_inl
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x
op_amp
l_int|0x80808080
)paren
op_eq
l_int|0x80808080
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|x
op_amp
l_int|0x80808080
)paren
op_ne
l_int|0x80808080
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;jsf0: erase timeout with 0x%08x&bslash;n&quot;
comma
id|x
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;jsf0: erase done with 0x%08x&bslash;n&quot;
comma
id|x
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
id|jsf_wait
c_func
(paren
id|p
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Program a block of flash.&n; * Very simple because we can do it byte by byte anyway.&n; */
DECL|function|jsf_ioctl_program
r_static
r_int
id|jsf_ioctl_program
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|jsflash_program_arg
id|abuf
suffix:semicolon
r_char
op_star
id|uptr
suffix:semicolon
r_int
r_int
id|p
suffix:semicolon
r_int
r_int
id|togo
suffix:semicolon
r_union
(brace
r_int
r_int
id|n
suffix:semicolon
r_char
id|s
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|b
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|abuf
comma
(paren
r_char
op_star
)paren
id|arg
comma
id|JSFPRGSZ
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|p
op_assign
id|abuf.off
suffix:semicolon
id|togo
op_assign
id|abuf.size
suffix:semicolon
r_if
c_cond
(paren
(paren
id|togo
op_amp
l_int|3
)paren
op_logical_or
(paren
id|p
op_amp
l_int|3
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|uptr
op_assign
(paren
r_char
op_star
)paren
(paren
r_int
r_int
)paren
id|abuf.data
suffix:semicolon
r_while
c_loop
(paren
id|togo
op_ne
l_int|0
)paren
(brace
id|togo
op_sub_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|b.s
(braket
l_int|0
)braket
comma
id|uptr
comma
l_int|4
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|jsf_write4
c_func
(paren
id|p
comma
id|b.n
)paren
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
id|uptr
op_add_assign
l_int|4
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jsf_ioctl
r_static
r_int
id|jsf_ioctl
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
id|f
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
r_int
id|error
op_assign
op_minus
id|ENOTTY
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
id|EPERM
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|JSFLASH_IDENT
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|jsf0.id
comma
id|JSFIDSZ
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|JSFLASH_ERASE
suffix:colon
id|error
op_assign
id|jsf_ioctl_erase
c_func
(paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|JSFLASH_PROGRAM
suffix:colon
id|error
op_assign
id|jsf_ioctl_program
c_func
(paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|jsf_mmap
r_static
r_int
id|jsf_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|jsf_open
r_static
r_int
id|jsf_open
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
id|filp
)paren
(brace
r_if
c_cond
(paren
id|jsf0.base
op_eq
l_int|0
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|jsf0.busy
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* XXX What security? */
)brace
DECL|function|jsf_release
r_static
r_int
id|jsf_release
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
id|jsf0.busy
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|jsf_fops
r_static
r_struct
id|file_operations
id|jsf_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|jsf_lseek
comma
dot
id|read
op_assign
id|jsf_read
comma
dot
id|write
op_assign
id|jsf_write
comma
dot
id|ioctl
op_assign
id|jsf_ioctl
comma
dot
id|mmap
op_assign
id|jsf_mmap
comma
dot
id|open
op_assign
id|jsf_open
comma
dot
id|release
op_assign
id|jsf_release
comma
)brace
suffix:semicolon
DECL|variable|jsf_dev
r_static
r_struct
id|miscdevice
id|jsf_dev
op_assign
(brace
id|JSF_MINOR
comma
l_string|&quot;jsflash&quot;
comma
op_amp
id|jsf_fops
)brace
suffix:semicolon
DECL|variable|jsfd_fops
r_static
r_struct
id|block_device_operations
id|jsfd_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|jsflash_init
r_static
r_int
id|jsflash_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|jsflash
op_star
id|jsf
suffix:semicolon
r_int
id|node
suffix:semicolon
r_char
id|banner
(braket
l_int|128
)braket
suffix:semicolon
r_struct
id|linux_prom_registers
id|reg0
suffix:semicolon
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;flash-memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
op_ne
l_int|0
op_logical_and
id|node
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|reg0
comma
r_sizeof
(paren
id|reg0
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;jsflash: no &bslash;&quot;reg&bslash;&quot; property&bslash;n&quot;
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
id|reg0.which_io
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;jsflash: bus number nonzero: 0x%x:%x&bslash;n&quot;
comma
id|reg0.which_io
comma
id|reg0.phys_addr
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Flash may be somewhere else, for instance on Ebus.&n;&t;&t; * So, don&squot;t do the following check for IIep flash space.&n;&t;&t; */
macro_line|#if 0
r_if
c_cond
(paren
(paren
id|reg0.phys_addr
op_rshift
l_int|24
)paren
op_ne
l_int|0x20
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;jsflash: suspicious address: 0x%x:%x&bslash;n&quot;
comma
id|reg0.which_io
comma
id|reg0.phys_addr
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
r_int
)paren
id|reg0.reg_size
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;jsflash: bad size 0x%x&bslash;n&quot;
comma
(paren
r_int
)paren
id|reg0.reg_size
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* XXX Remove this code once PROLL ID12 got widespread */
id|printk
c_func
(paren
l_string|&quot;jsflash: no /flash-memory node, use PROLL &gt;= 12&bslash;n&quot;
)paren
suffix:semicolon
id|prom_getproperty
c_func
(paren
id|prom_root_node
comma
l_string|&quot;banner-name&quot;
comma
id|banner
comma
l_int|128
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
(paren
id|banner
comma
l_string|&quot;JavaStation-NC&quot;
)paren
op_ne
l_int|0
op_logical_and
id|strcmp
(paren
id|banner
comma
l_string|&quot;JavaStation-E&quot;
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|reg0.which_io
op_assign
l_int|0
suffix:semicolon
id|reg0.phys_addr
op_assign
l_int|0x20400000
suffix:semicolon
id|reg0.reg_size
op_assign
l_int|0x00800000
suffix:semicolon
)brace
multiline_comment|/* Let us be really paranoid for modifications to probing code. */
multiline_comment|/* extern enum sparc_cpu sparc_cpu_model; */
multiline_comment|/* in &lt;asm/system.h&gt; */
r_if
c_cond
(paren
id|sparc_cpu_model
op_ne
id|sun4m
)paren
(brace
multiline_comment|/* We must be on sun4m because we use MMU Bypass ASI. */
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|jsf0.base
op_eq
l_int|0
)paren
(brace
id|jsf
op_assign
op_amp
id|jsf0
suffix:semicolon
id|jsf-&gt;base
op_assign
id|reg0.phys_addr
suffix:semicolon
id|jsf-&gt;size
op_assign
id|reg0.reg_size
suffix:semicolon
multiline_comment|/* XXX Redo the userland interface. */
id|jsf-&gt;id.off
op_assign
id|JSF_BASE_ALL
suffix:semicolon
id|jsf-&gt;id.size
op_assign
l_int|0x01000000
suffix:semicolon
multiline_comment|/* 16M - all segments */
id|strcpy
c_func
(paren
id|jsf-&gt;id.name
comma
l_string|&quot;Krups_all&quot;
)paren
suffix:semicolon
id|jsf-&gt;dv
(braket
l_int|0
)braket
dot
id|dbase
op_assign
id|jsf-&gt;base
suffix:semicolon
id|jsf-&gt;dv
(braket
l_int|0
)braket
dot
id|dsize
op_assign
id|jsf-&gt;size
suffix:semicolon
id|jsf-&gt;dv
(braket
l_int|1
)braket
dot
id|dbase
op_assign
id|jsf-&gt;base
op_plus
l_int|1024
suffix:semicolon
id|jsf-&gt;dv
(braket
l_int|1
)braket
dot
id|dsize
op_assign
id|jsf-&gt;size
op_minus
l_int|1024
suffix:semicolon
id|jsf-&gt;dv
(braket
l_int|2
)braket
dot
id|dbase
op_assign
id|JSF_BASE_ALL
suffix:semicolon
id|jsf-&gt;dv
(braket
l_int|2
)braket
dot
id|dsize
op_assign
l_int|0x01000000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Espresso Flash @0x%lx [%d MB]&bslash;n&quot;
comma
id|jsf-&gt;base
comma
(paren
r_int
)paren
(paren
id|jsf-&gt;size
op_div
(paren
l_int|1024
op_star
l_int|1024
)paren
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|misc_register
c_func
(paren
op_amp
id|jsf_dev
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;jsf: unable to get misc minor %d&bslash;n&quot;
comma
id|JSF_MINOR
)paren
suffix:semicolon
id|jsf0.base
op_assign
l_int|0
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|jsf_queue
r_static
r_struct
id|request_queue
op_star
id|jsf_queue
suffix:semicolon
DECL|function|jsfd_init
r_static
r_int
id|jsfd_init
c_func
(paren
r_void
)paren
(brace
r_static
id|spinlock_t
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_struct
id|jsflash
op_star
id|jsf
suffix:semicolon
r_struct
id|jsfd_part
op_star
id|jdp
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|jsf0.base
op_eq
l_int|0
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|err
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
id|JSF_MAX
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
id|jsfd_disk
(braket
id|i
)braket
op_assign
id|disk
suffix:semicolon
)brace
r_if
c_cond
(paren
id|register_blkdev
c_func
(paren
id|JSFD_MAJOR
comma
l_string|&quot;jsfd&quot;
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|jsf_queue
op_assign
id|blk_init_queue
c_func
(paren
id|jsfd_do_request
comma
op_amp
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|jsf_queue
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|unregister_blkdev
c_func
(paren
id|JSFD_MAJOR
comma
l_string|&quot;jsfd&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|JSF_MAX
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
id|jsfd_disk
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_amp
id|JSF_PART_MASK
)paren
op_ge
id|JSF_NPART
)paren
r_continue
suffix:semicolon
id|jsf
op_assign
op_amp
id|jsf0
suffix:semicolon
multiline_comment|/* actually, &amp;jsfv[i &gt;&gt; JSF_PART_BITS] */
id|jdp
op_assign
op_amp
id|jsf-&gt;dv
(braket
id|i
op_amp
id|JSF_PART_MASK
)braket
suffix:semicolon
id|disk-&gt;major
op_assign
id|JSFD_MAJOR
suffix:semicolon
id|disk-&gt;first_minor
op_assign
id|i
suffix:semicolon
id|sprintf
c_func
(paren
id|disk-&gt;disk_name
comma
l_string|&quot;jsfd%d&quot;
comma
id|i
)paren
suffix:semicolon
id|disk-&gt;fops
op_assign
op_amp
id|jsfd_fops
suffix:semicolon
id|set_capacity
c_func
(paren
id|disk
comma
id|jdp-&gt;dsize
op_rshift
l_int|9
)paren
suffix:semicolon
id|disk-&gt;private_data
op_assign
id|jdp
suffix:semicolon
id|disk-&gt;queue
op_assign
id|jsf_queue
suffix:semicolon
id|add_disk
c_func
(paren
id|disk
)paren
suffix:semicolon
id|set_disk_ro
c_func
(paren
id|disk
comma
l_int|1
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
id|jsfd_disk
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|jsflash_init_module
r_static
r_int
id|__init
id|jsflash_init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|jsflash_init
c_func
(paren
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|jsfd_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|function|jsflash_cleanup_module
r_static
r_void
id|__exit
id|jsflash_cleanup_module
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
id|JSF_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_amp
id|JSF_PART_MASK
)paren
op_ge
id|JSF_NPART
)paren
r_continue
suffix:semicolon
id|del_gendisk
c_func
(paren
id|jsfd_disk
(braket
id|i
)braket
)paren
suffix:semicolon
id|put_disk
c_func
(paren
id|jsfd_disk
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|jsf0.busy
)paren
id|printk
c_func
(paren
l_string|&quot;jsf0: cleaning busy unit&bslash;n&quot;
)paren
suffix:semicolon
id|jsf0.base
op_assign
l_int|0
suffix:semicolon
id|jsf0.busy
op_assign
l_int|0
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|jsf_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unregister_blkdev
c_func
(paren
id|JSFD_MAJOR
comma
l_string|&quot;jsfd&quot;
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;jsfd: cleanup_module failed&bslash;n&quot;
)paren
suffix:semicolon
id|blk_cleanup_queue
c_func
(paren
id|jsf_queue
)paren
suffix:semicolon
)brace
DECL|variable|jsflash_init_module
id|module_init
c_func
(paren
id|jsflash_init_module
)paren
suffix:semicolon
DECL|variable|jsflash_cleanup_module
id|module_exit
c_func
(paren
id|jsflash_cleanup_module
)paren
suffix:semicolon
eof
