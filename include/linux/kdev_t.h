macro_line|#ifndef _LINUX_KDEV_T_H
DECL|macro|_LINUX_KDEV_T_H
mdefine_line|#define _LINUX_KDEV_T_H
macro_line|#if defined(__KERNEL__) || defined(_LVM_H_INCLUDE)
multiline_comment|/*&n;As a preparation for the introduction of larger device numbers,&n;we introduce a type kdev_t to hold them. No information about&n;this type is known outside of this include file.&n;&n;Objects of type kdev_t designate a device. Outside of the kernel&n;the corresponding things are objects of type dev_t - usually an&n;integral type with the device major and minor in the high and low&n;bits, respectively. Conversion is done by&n;&n;extern kdev_t to_kdev_t(int);&n;&n;It is up to the various file systems to decide how objects of type&n;dev_t are stored on disk.&n;The only other point of contact between kernel and outside world&n;are the system calls stat and mknod, new versions of which will&n;eventually have to be used in libc.&n;&n;[Unfortunately, the floppy control ioctls fail to hide the internal&n;kernel structures, and the fd_device field of a struct floppy_drive_struct&n;is user-visible. So, it remains a dev_t for the moment, with some ugly&n;conversions in floppy.c.]&n;&n;Inside the kernel, we aim for a kdev_t type that is a pointer&n;to a structure with information about the device (like major,&n;minor, size, blocksize, sectorsize, name, read-only flag,&n;struct file_operations etc.).&n;&n;However, for the time being we let kdev_t be almost the same as dev_t:&n;&n;typedef struct { unsigned short major, minor; } kdev_t;&n;&n;Admissible operations on an object of type kdev_t:&n;- passing it along&n;- comparing it for equality with another such object&n;- storing it in inode-&gt;i_dev, inode-&gt;i_rdev, req-&gt;rq_dev, de-&gt;dc_dev,&n;- tty-&gt;device&n;- using its bit pattern as argument in a hash function&n;- finding its major and minor&n;- complaining about it&n;&n;An object of type kdev_t is created only by the function MKDEV(),&n;with the single exception of the constant 0 (no device).&n;&n;Right now the other information mentioned above is usually found&n;in static arrays indexed by major or major,minor.&n;&n;An obstacle to immediately using&n;    typedef struct { ... (* lots of information *) } *kdev_t&n;is the case of mknod used to create a block device that the&n;kernel doesn&squot;t know about at present (but first learns about&n;when some module is inserted).&n;&n;aeb - 950811&n;*/
multiline_comment|/*&n; * NOTE NOTE NOTE!&n; *&n; * The kernel-internal &quot;kdev_t&quot; will eventually have&n; * 20 bits for minor numbers, and 12 bits for majors.&n; *&n; * HOWEVER, the external representation is still 8+8&n; * bits, and there is no way to generate the extended&n; * &quot;kdev_t&quot; format yet. Which is just as well, since&n; * we still use &quot;minor&quot; as an index into various&n; * static arrays, and they are sized for a 8-bit index.&n; */
r_typedef
r_struct
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|typedef|kdev_t
)brace
id|kdev_t
suffix:semicolon
DECL|macro|KDEV_MINOR_BITS
mdefine_line|#define KDEV_MINOR_BITS&t;&t;8
DECL|macro|KDEV_MAJOR_BITS
mdefine_line|#define KDEV_MAJOR_BITS&t;&t;8
DECL|macro|__mkdev
mdefine_line|#define __mkdev(major,minor)&t;(((major) &lt;&lt; KDEV_MINOR_BITS) + (minor))
DECL|macro|mk_kdev
mdefine_line|#define mk_kdev(major, minor)&t;((kdev_t) { __mkdev(major,minor) } )
multiline_comment|/*&n; * The &quot;values&quot; are just _cookies_, usable for &n; * internal equality comparisons and for things&n; * like NFS filehandle conversion.&n; */
DECL|function|kdev_val
r_static
r_inline
r_int
r_int
id|kdev_val
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_return
id|dev.value
suffix:semicolon
)brace
DECL|function|val_to_kdev
r_static
r_inline
id|kdev_t
id|val_to_kdev
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|kdev_t
id|dev
suffix:semicolon
id|dev.value
op_assign
id|val
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
DECL|macro|HASHDEV
mdefine_line|#define HASHDEV(dev)&t;(kdev_val(dev))
DECL|macro|NODEV
mdefine_line|#define NODEV&t;&t;(mk_kdev(0,0))
DECL|macro|B_FREE
mdefine_line|#define B_FREE&t;&t;(mk_kdev(0xff,0xff))
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
DECL|function|kdev_same
r_static
r_inline
r_int
id|kdev_same
c_func
(paren
id|kdev_t
id|dev1
comma
id|kdev_t
id|dev2
)paren
(brace
r_return
id|dev1.value
op_eq
id|dev2.value
suffix:semicolon
)brace
DECL|macro|kdev_none
mdefine_line|#define kdev_none(d1)&t;(!kdev_val(d1))
multiline_comment|/* Mask off the high bits for now.. */
DECL|macro|minor
mdefine_line|#define minor(dev)&t;((dev).value &amp; 0xff)
DECL|macro|major
mdefine_line|#define major(dev)&t;(((dev).value &gt;&gt; KDEV_MINOR_BITS) &amp; 0xff)
multiline_comment|/* These are for user-level &quot;dev_t&quot; */
DECL|macro|MINORBITS
mdefine_line|#define MINORBITS&t;8
DECL|macro|MINORMASK
mdefine_line|#define MINORMASK&t;((1U &lt;&lt; MINORBITS) - 1)
DECL|macro|MAJOR
mdefine_line|#define MAJOR(dev)&t;((unsigned int) ((dev) &gt;&gt; MINORBITS))
DECL|macro|MINOR
mdefine_line|#define MINOR(dev)&t;((unsigned int) ((dev) &amp; MINORMASK))
DECL|macro|MKDEV
mdefine_line|#define MKDEV(ma,mi)&t;(((ma) &lt;&lt; MINORBITS) | (mi))
multiline_comment|/*&n; * Conversion functions&n; */
DECL|function|kdev_t_to_nr
r_static
r_inline
r_int
id|kdev_t_to_nr
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_return
id|MKDEV
c_func
(paren
id|major
c_func
(paren
id|dev
)paren
comma
id|minor
c_func
(paren
id|dev
)paren
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
r_return
id|mk_kdev
c_func
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
comma
id|MINOR
c_func
(paren
id|dev
)paren
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
