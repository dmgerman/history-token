macro_line|#ifndef _LINUX_KDEV_T_H
DECL|macro|_LINUX_KDEV_T_H
mdefine_line|#define _LINUX_KDEV_T_H
macro_line|#if defined(__KERNEL__) || defined(_LVM_H_INCLUDE)
multiline_comment|/*&n;As a preparation for the introduction of larger device numbers,&n;we introduce a type kdev_t to hold them. No information about&n;this type is known outside of this include file.&n;&n;Objects of type kdev_t designate a device. Outside of the kernel&n;the corresponding things are objects of type dev_t - usually an&n;integral type with the device major and minor in the high and low&n;bits, respectively. Conversion is done by&n;&n;extern kdev_t to_kdev_t(int);&n;&n;It is up to the various file systems to decide how objects of type&n;dev_t are stored on disk.&n;The only other point of contact between kernel and outside world&n;are the system calls stat and mknod, new versions of which will&n;eventually have to be used in libc.&n;&n;[Unfortunately, the floppy control ioctls fail to hide the internal&n;kernel structures, and the fd_device field of a struct floppy_drive_struct&n;is user-visible. So, it remains a dev_t for the moment, with some ugly&n;conversions in floppy.c.]&n;&n;Inside the kernel, we aim for a kdev_t type that is a pointer&n;to a structure with information about the device (like major,&n;minor, size, blocksize, sectorsize, name, read-only flag,&n;struct file_operations etc.).&n;&n;However, for the time being we let kdev_t be almost the same as dev_t:&n;&n;typedef struct { unsigned short major, minor; } kdev_t;&n;&n;Admissible operations on an object of type kdev_t:&n;- passing it along&n;- comparing it for equality with another such object&n;- storing it in ROOT_DEV, inode-&gt;i_dev, inode-&gt;i_rdev, sb-&gt;s_dev,&n;  bh-&gt;b_dev, req-&gt;rq_dev, de-&gt;dc_dev, tty-&gt;device&n;- using its bit pattern as argument in a hash function&n;- finding its major and minor&n;- complaining about it&n;&n;An object of type kdev_t is created only by the function MKDEV(),&n;with the single exception of the constant 0 (no device).&n;&n;Right now the other information mentioned above is usually found&n;in static arrays indexed by major or major,minor.&n;&n;An obstacle to immediately using&n;    typedef struct { ... (* lots of information *) } *kdev_t&n;is the case of mknod used to create a block device that the&n;kernel doesn&squot;t know about at present (but first learns about&n;when some module is inserted).&n;&n;aeb - 950811&n;*/
multiline_comment|/* Since MINOR(dev) is used as index in static arrays,&n;   the kernel is not quite ready yet for larger minors.&n;   However, everything runs fine with an arbitrary kdev_t type. */
DECL|macro|MINORBITS
mdefine_line|#define MINORBITS&t;8
DECL|macro|MINORMASK
mdefine_line|#define MINORMASK&t;((1U &lt;&lt; MINORBITS) - 1)
DECL|typedef|kdev_t
r_typedef
r_int
r_int
id|kdev_t
suffix:semicolon
DECL|macro|MAJOR
mdefine_line|#define MAJOR(dev)&t;((unsigned int) ((dev) &gt;&gt; MINORBITS))
DECL|macro|MINOR
mdefine_line|#define MINOR(dev)&t;((unsigned int) ((dev) &amp; MINORMASK))
DECL|macro|HASHDEV
mdefine_line|#define HASHDEV(dev)&t;((unsigned int) (dev))
DECL|macro|NODEV
mdefine_line|#define NODEV&t;&t;0
DECL|macro|MKDEV
mdefine_line|#define MKDEV(ma,mi)&t;(((ma) &lt;&lt; MINORBITS) | (mi))
DECL|macro|B_FREE
mdefine_line|#define B_FREE&t;&t;0xffff&t;&t;/* yuk */
r_extern
r_const
r_char
op_star
id|kdevname
c_func
(paren
id|kdev_t
)paren
suffix:semicolon
multiline_comment|/* note: returns pointer to static data! */
multiline_comment|/*&n;As long as device numbers in the outside world have 16 bits only,&n;we use these conversions.&n;*/
DECL|function|kdev_t_to_nr
r_static
r_inline
r_int
r_int
id|kdev_t_to_nr
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_return
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
op_lshift
l_int|8
)paren
op_or
id|MINOR
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|to_kdev_t
r_static
r_inline
id|kdev_t
id|to_kdev_t
c_func
(paren
r_int
id|dev
)paren
(brace
r_int
id|major
comma
id|minor
suffix:semicolon
macro_line|#if 0
id|major
op_assign
(paren
id|dev
op_rshift
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|major
)paren
(brace
id|major
op_assign
(paren
id|dev
op_rshift
l_int|8
)paren
suffix:semicolon
id|minor
op_assign
(paren
id|dev
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
r_else
id|minor
op_assign
(paren
id|dev
op_amp
l_int|0xffff
)paren
suffix:semicolon
macro_line|#else
id|major
op_assign
(paren
id|dev
op_rshift
l_int|8
)paren
suffix:semicolon
id|minor
op_assign
(paren
id|dev
op_amp
l_int|0xff
)paren
suffix:semicolon
macro_line|#endif
r_return
id|MKDEV
c_func
(paren
id|major
comma
id|minor
)paren
suffix:semicolon
)brace
macro_line|#else /* __KERNEL__ || _LVM_H_INCLUDE */
multiline_comment|/*&n;Some programs want their definitions of MAJOR and MINOR and MKDEV&n;from the kernel sources. These must be the externally visible ones.&n;*/
DECL|macro|MAJOR
mdefine_line|#define MAJOR(dev)&t;((dev)&gt;&gt;8)
DECL|macro|MINOR
mdefine_line|#define MINOR(dev)&t;((dev) &amp; 0xff)
DECL|macro|MKDEV
mdefine_line|#define MKDEV(ma,mi)&t;((ma)&lt;&lt;8 | (mi))
macro_line|#endif /* __KERNEL__ || _LVM_H_INCLUDE */
macro_line|#endif
eof
