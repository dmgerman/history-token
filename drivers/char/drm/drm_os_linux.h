macro_line|#include &lt;linux/interrupt.h&gt;&t;/* For task queue support */
macro_line|#include &lt;linux/delay.h&gt;
DECL|macro|DRM_IOCTL_ARGS
mdefine_line|#define DRM_IOCTL_ARGS&t;&t;&t;struct inode *inode, struct file *filp, unsigned int cmd, unsigned long data
DECL|macro|DRM_ERR
mdefine_line|#define DRM_ERR(d)&t;&t;&t;-(d)
DECL|macro|DRM_CURRENTPID
mdefine_line|#define DRM_CURRENTPID&t;&t;&t;current-&gt;pid
DECL|macro|DRM_UDELAY
mdefine_line|#define DRM_UDELAY(d)&t;&t;&t;udelay(d)
DECL|macro|DRM_READ8
mdefine_line|#define DRM_READ8(addr)&t;&t;&t;readb(addr)
DECL|macro|DRM_READ32
mdefine_line|#define DRM_READ32(addr)&t;&t;readl(addr)
DECL|macro|DRM_WRITE8
mdefine_line|#define DRM_WRITE8(addr, val)&t;&t;writeb(val, addr)
DECL|macro|DRM_WRITE32
mdefine_line|#define DRM_WRITE32(addr, val)&t;&t;writel(val, addr)
DECL|macro|DRM_READMEMORYBARRIER
mdefine_line|#define DRM_READMEMORYBARRIER()&t;&t;mb()
DECL|macro|DRM_WRITEMEMORYBARRIER
mdefine_line|#define DRM_WRITEMEMORYBARRIER()&t;wmb()
DECL|macro|DRM_DEVICE
mdefine_line|#define DRM_DEVICE&t;drm_file_t&t;*priv&t;= filp-&gt;private_data; &bslash;&n;&t;&t;&t;drm_device_t&t;*dev&t;= priv-&gt;dev
DECL|macro|DRM_IRQ_ARGS
mdefine_line|#define DRM_IRQ_ARGS&t;        int irq, void *arg, struct pt_regs *regs
DECL|macro|DRM_TASKQUEUE_ARGS
mdefine_line|#define DRM_TASKQUEUE_ARGS&t;void *arg
multiline_comment|/* For data going from/to the kernel through the ioctl argument */
DECL|macro|DRM_COPY_FROM_USER_IOCTL
mdefine_line|#define DRM_COPY_FROM_USER_IOCTL(arg1, arg2, arg3)&t;&bslash;&n;&t;if ( copy_from_user(&amp;arg1, arg2, arg3) )&t;&bslash;&n;&t;&t;return -EFAULT
DECL|macro|DRM_COPY_TO_USER_IOCTL
mdefine_line|#define DRM_COPY_TO_USER_IOCTL(arg1, arg2, arg3)&t;&bslash;&n;&t;if ( copy_to_user(arg1, &amp;arg2, arg3) )&t;&t;&bslash;&n;&t;&t;return -EFAULT
multiline_comment|/* Other copying of data from/to kernel space */
DECL|macro|DRM_COPY_FROM_USER
mdefine_line|#define DRM_COPY_FROM_USER(arg1, arg2, arg3)&t;&t;&bslash;&n;&t;copy_from_user(arg1, arg2, arg3)
DECL|macro|DRM_COPY_TO_USER
mdefine_line|#define DRM_COPY_TO_USER(arg1, arg2, arg3)&t;&t;&bslash;&n;&t;copy_to_user(arg1, arg2, arg3)
multiline_comment|/* Macros for copyfrom user, but checking readability only once */
DECL|macro|DRM_VERIFYAREA_READ
mdefine_line|#define DRM_VERIFYAREA_READ( uaddr, size ) &t;&t;&bslash;&n;&t;verify_area( VERIFY_READ, uaddr, size )
DECL|macro|DRM_COPY_FROM_USER_UNCHECKED
mdefine_line|#define DRM_COPY_FROM_USER_UNCHECKED(arg1, arg2, arg3) &t;&bslash;&n;&t;__copy_from_user(arg1, arg2, arg3)
DECL|macro|DRM_GET_USER_UNCHECKED
mdefine_line|#define DRM_GET_USER_UNCHECKED(val, uaddr)&t;&t;&bslash;&n;&t;__get_user(val, uaddr)
multiline_comment|/* malloc/free without the overhead of DRM(alloc) */
DECL|macro|DRM_MALLOC
mdefine_line|#define DRM_MALLOC(x) kmalloc(x, GFP_KERNEL)
DECL|macro|DRM_FREE
mdefine_line|#define DRM_FREE(x) kfree(x)
DECL|macro|DRM_GETSAREA
mdefine_line|#define DRM_GETSAREA()&t;&t;&t;&t;&t;&t;&t; &bslash;&n;do { &t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;struct list_head *list;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;list_for_each( list, &amp;dev-&gt;maplist-&gt;head ) {&t;&t;&t; &bslash;&n;&t;&t;drm_map_list_t *entry = (drm_map_list_t *)list;&t;&t; &bslash;&n;&t;&t;if ( entry-&gt;map &amp;&amp;&t;&t;&t;&t;&t; &bslash;&n;&t;&t;     entry-&gt;map-&gt;type == _DRM_SHM &amp;&amp;&t;&t;&t; &bslash;&n;&t;&t;     (entry-&gt;map-&gt;flags &amp; _DRM_CONTAINS_LOCK) ) {&t; &bslash;&n;&t;&t;&t;dev_priv-&gt;sarea = entry-&gt;map;&t;&t;&t; &bslash;&n; &t;&t;&t;break;&t;&t;&t;&t;&t;&t; &bslash;&n; &t;&t;}&t;&t;&t;&t;&t;&t;&t; &bslash;&n; &t;}&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;} while (0)
DECL|macro|DRM_HZ
mdefine_line|#define DRM_HZ HZ
DECL|macro|DRM_WAIT_ON
mdefine_line|#define DRM_WAIT_ON( ret, queue, timeout, condition )&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DECLARE_WAITQUEUE(entry, current);&t;&t;&bslash;&n;&t;unsigned long end = jiffies + (timeout);&t;&bslash;&n;&t;add_wait_queue(&amp;(queue), &amp;entry);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;current-&gt;state = TASK_INTERRUPTIBLE;&t;&bslash;&n;&t;&t;if (condition) &t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&bslash;&n;&t;&t;if((signed)(end - jiffies) &lt;= 0) {&t;&bslash;&n;&t;&t;&t;ret = -EBUSY;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;&t;schedule_timeout((HZ/100 &gt; 1) ? HZ/100 : 1);&t;&bslash;&n;&t;&t;if (signal_pending(current)) {&t;&t;&bslash;&n;&t;&t;&t;ret = -EINTR;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&bslash;&n;&t;remove_wait_queue(&amp;(queue), &amp;entry);&t;&t;&bslash;&n;} while (0)
DECL|macro|DRM_WAKEUP
mdefine_line|#define DRM_WAKEUP( queue ) wake_up_interruptible( queue )
DECL|macro|DRM_INIT_WAITQUEUE
mdefine_line|#define DRM_INIT_WAITQUEUE( queue ) init_waitqueue_head( queue )
eof
