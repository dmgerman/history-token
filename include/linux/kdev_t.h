macro_line|#ifndef _LINUX_KDEV_T_H
DECL|macro|_LINUX_KDEV_T_H
mdefine_line|#define _LINUX_KDEV_T_H
macro_line|#ifdef __KERNEL__
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
DECL|macro|print_dev_t
mdefine_line|#define print_dev_t(buffer, dev)&t;&t;&t;&t;&t;&bslash;&n;&t;sprintf((buffer), &quot;%u:%u&bslash;n&quot;, MAJOR(dev), MINOR(dev))
DECL|macro|format_dev_t
mdefine_line|#define format_dev_t(buffer, dev)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sprintf(buffer, &quot;%u:%u&quot;, MAJOR(dev), MINOR(dev));&t;&bslash;&n;&t;&t;buffer;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
macro_line|#else /* __KERNEL__ */
multiline_comment|/*&n;Some programs want their definitions of MAJOR and MINOR and MKDEV&n;from the kernel sources. These must be the externally visible ones.&n;*/
DECL|macro|MAJOR
mdefine_line|#define MAJOR(dev)&t;((dev)&gt;&gt;8)
DECL|macro|MINOR
mdefine_line|#define MINOR(dev)&t;((dev) &amp; 0xff)
DECL|macro|MKDEV
mdefine_line|#define MKDEV(ma,mi)&t;((ma)&lt;&lt;8 | (mi))
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
