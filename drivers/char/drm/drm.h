multiline_comment|/**&n; * &bslash;file drm.h &n; * Header for the Direct Rendering Manager&n; * &n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *&n; * &bslash;par Acknowledgments:&n; * Dec 1999, Richard Henderson &lt;rth@twiddle.net&gt;, move to generic &bslash;c cmpxchg.&n; */
multiline_comment|/*&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#ifndef _DRM_H_
DECL|macro|_DRM_H_
mdefine_line|#define _DRM_H_
macro_line|#if defined(__linux__)
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ioctl.h&gt;&t;&t;/* For _IO* macros */
DECL|macro|DRM_IOCTL_NR
mdefine_line|#define DRM_IOCTL_NR(n)&t;&t;_IOC_NR(n)
DECL|macro|DRM_IOC_VOID
mdefine_line|#define DRM_IOC_VOID&t;&t;_IOC_NONE
DECL|macro|DRM_IOC_READ
mdefine_line|#define DRM_IOC_READ&t;&t;_IOC_READ
DECL|macro|DRM_IOC_WRITE
mdefine_line|#define DRM_IOC_WRITE&t;&t;_IOC_WRITE
DECL|macro|DRM_IOC_READWRITE
mdefine_line|#define DRM_IOC_READWRITE&t;_IOC_READ|_IOC_WRITE
DECL|macro|DRM_IOC
mdefine_line|#define DRM_IOC(dir, group, nr, size) _IOC(dir, group, nr, size)
macro_line|#elif defined(__FreeBSD__) || defined(__NetBSD__)
macro_line|#if defined(__FreeBSD__) &amp;&amp; defined(XFree86Server)
multiline_comment|/* Prevent name collision when including sys/ioccom.h */
DECL|macro|ioctl
macro_line|#undef ioctl
macro_line|#include &lt;sys/ioccom.h&gt;
DECL|macro|ioctl
mdefine_line|#define ioctl(a,b,c)&t;&t;xf86ioctl(a,b,c)
macro_line|#else
macro_line|#include &lt;sys/ioccom.h&gt;
macro_line|#endif /* __FreeBSD__ &amp;&amp; xf86ioctl */
DECL|macro|DRM_IOCTL_NR
mdefine_line|#define DRM_IOCTL_NR(n)&t;&t;((n) &amp; 0xff)
DECL|macro|DRM_IOC_VOID
mdefine_line|#define DRM_IOC_VOID&t;&t;IOC_VOID
DECL|macro|DRM_IOC_READ
mdefine_line|#define DRM_IOC_READ&t;&t;IOC_OUT
DECL|macro|DRM_IOC_WRITE
mdefine_line|#define DRM_IOC_WRITE&t;&t;IOC_IN
DECL|macro|DRM_IOC_READWRITE
mdefine_line|#define DRM_IOC_READWRITE&t;IOC_INOUT
DECL|macro|DRM_IOC
mdefine_line|#define DRM_IOC(dir, group, nr, size) _IOC(dir, group, nr, size)
macro_line|#endif
DECL|macro|XFREE86_VERSION
mdefine_line|#define XFREE86_VERSION(major,minor,patch,snap) &bslash;&n;&t;&t;((major &lt;&lt; 16) | (minor &lt;&lt; 8) | patch)
macro_line|#ifndef CONFIG_XFREE86_VERSION
DECL|macro|CONFIG_XFREE86_VERSION
mdefine_line|#define CONFIG_XFREE86_VERSION XFREE86_VERSION(4,1,0,0)
macro_line|#endif
macro_line|#if CONFIG_XFREE86_VERSION &lt; XFREE86_VERSION(4,1,0,0)
DECL|macro|DRM_PROC_DEVICES
mdefine_line|#define DRM_PROC_DEVICES &quot;/proc/devices&quot;
DECL|macro|DRM_PROC_MISC
mdefine_line|#define DRM_PROC_MISC&t; &quot;/proc/misc&quot;
DECL|macro|DRM_PROC_DRM
mdefine_line|#define DRM_PROC_DRM&t; &quot;/proc/drm&quot;
DECL|macro|DRM_DEV_DRM
mdefine_line|#define DRM_DEV_DRM&t; &quot;/dev/drm&quot;
DECL|macro|DRM_DEV_MODE
mdefine_line|#define DRM_DEV_MODE&t; (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)
DECL|macro|DRM_DEV_UID
mdefine_line|#define DRM_DEV_UID&t; 0
DECL|macro|DRM_DEV_GID
mdefine_line|#define DRM_DEV_GID&t; 0
macro_line|#endif
macro_line|#if CONFIG_XFREE86_VERSION &gt;= XFREE86_VERSION(4,1,0,0)
DECL|macro|DRM_MAJOR
mdefine_line|#define DRM_MAJOR       226
DECL|macro|DRM_MAX_MINOR
mdefine_line|#define DRM_MAX_MINOR   15
macro_line|#endif
DECL|macro|DRM_NAME
mdefine_line|#define DRM_NAME&t;&quot;drm&quot;&t;  /**&lt; Name in kernel, /dev, and /proc */
DECL|macro|DRM_MIN_ORDER
mdefine_line|#define DRM_MIN_ORDER&t;5&t;  /**&lt; At least 2^5 bytes = 32 bytes */
DECL|macro|DRM_MAX_ORDER
mdefine_line|#define DRM_MAX_ORDER&t;22&t;  /**&lt; Up to 2^22 bytes = 4MB */
DECL|macro|DRM_RAM_PERCENT
mdefine_line|#define DRM_RAM_PERCENT 10&t;  /**&lt; How much system ram can we lock? */
DECL|macro|_DRM_LOCK_HELD
mdefine_line|#define _DRM_LOCK_HELD&t;0x80000000 /**&lt; Hardware lock is held */
DECL|macro|_DRM_LOCK_CONT
mdefine_line|#define _DRM_LOCK_CONT&t;0x40000000 /**&lt; Hardware lock is contended */
DECL|macro|_DRM_LOCK_IS_HELD
mdefine_line|#define _DRM_LOCK_IS_HELD(lock)&t;   ((lock) &amp; _DRM_LOCK_HELD)
DECL|macro|_DRM_LOCK_IS_CONT
mdefine_line|#define _DRM_LOCK_IS_CONT(lock)&t;   ((lock) &amp; _DRM_LOCK_CONT)
DECL|macro|_DRM_LOCKING_CONTEXT
mdefine_line|#define _DRM_LOCKING_CONTEXT(lock) ((lock) &amp; ~(_DRM_LOCK_HELD|_DRM_LOCK_CONT))
DECL|typedef|drm_handle_t
r_typedef
r_int
r_int
id|drm_handle_t
suffix:semicolon
DECL|typedef|drm_context_t
r_typedef
r_int
r_int
id|drm_context_t
suffix:semicolon
DECL|typedef|drm_drawable_t
r_typedef
r_int
r_int
id|drm_drawable_t
suffix:semicolon
DECL|typedef|drm_magic_t
r_typedef
r_int
r_int
id|drm_magic_t
suffix:semicolon
multiline_comment|/**&n; * Cliprect.&n; * &n; * &bslash;warning: If you change this structure, make sure you change&n; * XF86DRIClipRectRec in the server as well&n; *&n; * &bslash;note KW: Actually it&squot;s illegal to change either for&n; * backwards-compatibility reasons.&n; */
DECL|struct|drm_clip_rect
r_typedef
r_struct
id|drm_clip_rect
(brace
DECL|member|x1
r_int
r_int
id|x1
suffix:semicolon
DECL|member|y1
r_int
r_int
id|y1
suffix:semicolon
DECL|member|x2
r_int
r_int
id|x2
suffix:semicolon
DECL|member|y2
r_int
r_int
id|y2
suffix:semicolon
DECL|typedef|drm_clip_rect_t
)brace
id|drm_clip_rect_t
suffix:semicolon
multiline_comment|/**&n; * Texture region,&n; */
DECL|struct|drm_tex_region
r_typedef
r_struct
id|drm_tex_region
(brace
DECL|member|next
r_int
r_char
id|next
suffix:semicolon
DECL|member|prev
r_int
r_char
id|prev
suffix:semicolon
DECL|member|in_use
r_int
r_char
id|in_use
suffix:semicolon
DECL|member|padding
r_int
r_char
id|padding
suffix:semicolon
DECL|member|age
r_int
r_int
id|age
suffix:semicolon
DECL|typedef|drm_tex_region_t
)brace
id|drm_tex_region_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_VERSION ioctl argument type.&n; * &n; * &bslash;sa drmGetVersion().&n; */
DECL|struct|drm_version
r_typedef
r_struct
id|drm_version
(brace
DECL|member|version_major
r_int
id|version_major
suffix:semicolon
multiline_comment|/**&lt; Major version */
DECL|member|version_minor
r_int
id|version_minor
suffix:semicolon
multiline_comment|/**&lt; Minor version */
DECL|member|version_patchlevel
r_int
id|version_patchlevel
suffix:semicolon
multiline_comment|/**&lt; Patch level */
DECL|member|name_len
r_int
id|name_len
suffix:semicolon
multiline_comment|/**&lt; Length of name buffer */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/**&lt; Name of driver */
DECL|member|date_len
r_int
id|date_len
suffix:semicolon
multiline_comment|/**&lt; Length of date buffer */
DECL|member|date
r_char
op_star
id|date
suffix:semicolon
multiline_comment|/**&lt; User-space buffer to hold date */
DECL|member|desc_len
r_int
id|desc_len
suffix:semicolon
multiline_comment|/**&lt; Length of desc buffer */
DECL|member|desc
r_char
op_star
id|desc
suffix:semicolon
multiline_comment|/**&lt; User-space buffer to hold desc */
DECL|typedef|drm_version_t
)brace
id|drm_version_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_GET_UNIQUE ioctl argument type.&n; *&n; * &bslash;sa drmGetBusid() and drmSetBusId().&n; */
DECL|struct|drm_unique
r_typedef
r_struct
id|drm_unique
(brace
DECL|member|unique_len
r_int
id|unique_len
suffix:semicolon
multiline_comment|/**&lt; Length of unique */
DECL|member|unique
r_char
op_star
id|unique
suffix:semicolon
multiline_comment|/**&lt; Unique name for driver instantiation */
DECL|typedef|drm_unique_t
)brace
id|drm_unique_t
suffix:semicolon
DECL|struct|drm_list
r_typedef
r_struct
id|drm_list
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/**&lt; Length of user-space structures */
DECL|member|version
id|drm_version_t
op_star
id|version
suffix:semicolon
DECL|typedef|drm_list_t
)brace
id|drm_list_t
suffix:semicolon
DECL|struct|drm_block
r_typedef
r_struct
id|drm_block
(brace
DECL|member|unused
r_int
id|unused
suffix:semicolon
DECL|typedef|drm_block_t
)brace
id|drm_block_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_CONTROL ioctl argument type.&n; *&n; * &bslash;sa drmCtlInstHandler() and drmCtlUninstHandler().&n; */
DECL|struct|drm_control
r_typedef
r_struct
id|drm_control
(brace
r_enum
(brace
DECL|enumerator|DRM_ADD_COMMAND
id|DRM_ADD_COMMAND
comma
DECL|enumerator|DRM_RM_COMMAND
id|DRM_RM_COMMAND
comma
DECL|enumerator|DRM_INST_HANDLER
id|DRM_INST_HANDLER
comma
DECL|enumerator|DRM_UNINST_HANDLER
id|DRM_UNINST_HANDLER
DECL|member|func
)brace
id|func
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|typedef|drm_control_t
)brace
id|drm_control_t
suffix:semicolon
multiline_comment|/**&n; * Type of memory to map.&n; */
DECL|enum|drm_map_type
r_typedef
r_enum
id|drm_map_type
(brace
DECL|enumerator|_DRM_FRAME_BUFFER
id|_DRM_FRAME_BUFFER
op_assign
l_int|0
comma
multiline_comment|/**&lt; WC (no caching), no core dump */
DECL|enumerator|_DRM_REGISTERS
id|_DRM_REGISTERS
op_assign
l_int|1
comma
multiline_comment|/**&lt; no caching, no core dump */
DECL|enumerator|_DRM_SHM
id|_DRM_SHM
op_assign
l_int|2
comma
multiline_comment|/**&lt; shared, cached */
DECL|enumerator|_DRM_AGP
id|_DRM_AGP
op_assign
l_int|3
comma
multiline_comment|/**&lt; AGP/GART */
DECL|enumerator|_DRM_SCATTER_GATHER
id|_DRM_SCATTER_GATHER
op_assign
l_int|4
multiline_comment|/**&lt; Scatter/gather memory for PCI DMA */
DECL|typedef|drm_map_type_t
)brace
id|drm_map_type_t
suffix:semicolon
multiline_comment|/**&n; * Memory mapping flags.&n; */
DECL|enum|drm_map_flags
r_typedef
r_enum
id|drm_map_flags
(brace
DECL|enumerator|_DRM_RESTRICTED
id|_DRM_RESTRICTED
op_assign
l_int|0x01
comma
multiline_comment|/**&lt; Cannot be mapped to user-virtual */
DECL|enumerator|_DRM_READ_ONLY
id|_DRM_READ_ONLY
op_assign
l_int|0x02
comma
DECL|enumerator|_DRM_LOCKED
id|_DRM_LOCKED
op_assign
l_int|0x04
comma
multiline_comment|/**&lt; shared, cached, locked */
DECL|enumerator|_DRM_KERNEL
id|_DRM_KERNEL
op_assign
l_int|0x08
comma
multiline_comment|/**&lt; kernel requires access */
DECL|enumerator|_DRM_WRITE_COMBINING
id|_DRM_WRITE_COMBINING
op_assign
l_int|0x10
comma
multiline_comment|/**&lt; use write-combining if available */
DECL|enumerator|_DRM_CONTAINS_LOCK
id|_DRM_CONTAINS_LOCK
op_assign
l_int|0x20
comma
multiline_comment|/**&lt; SHM page that contains lock */
DECL|enumerator|_DRM_REMOVABLE
id|_DRM_REMOVABLE
op_assign
l_int|0x40
multiline_comment|/**&lt; Removable mapping */
DECL|typedef|drm_map_flags_t
)brace
id|drm_map_flags_t
suffix:semicolon
DECL|struct|drm_ctx_priv_map
r_typedef
r_struct
id|drm_ctx_priv_map
(brace
DECL|member|ctx_id
r_int
r_int
id|ctx_id
suffix:semicolon
multiline_comment|/**&lt; Context requesting private mapping */
DECL|member|handle
r_void
op_star
id|handle
suffix:semicolon
multiline_comment|/**&lt; Handle of map */
DECL|typedef|drm_ctx_priv_map_t
)brace
id|drm_ctx_priv_map_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_GET_MAP, DRM_IOCTL_ADD_MAP and DRM_IOCTL_RM_MAP ioctls&n; * argument type.&n; *&n; * &bslash;sa drmAddMap().&n; */
DECL|struct|drm_map
r_typedef
r_struct
id|drm_map
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/**&lt; Requested physical address (0 for SAREA)*/
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/**&lt; Requested physical size (bytes) */
DECL|member|type
id|drm_map_type_t
id|type
suffix:semicolon
multiline_comment|/**&lt; Type of memory to map */
DECL|member|flags
id|drm_map_flags_t
id|flags
suffix:semicolon
multiline_comment|/**&lt; Flags */
DECL|member|handle
r_void
op_star
id|handle
suffix:semicolon
multiline_comment|/**&lt; User-space: &quot;Handle&quot; to pass to mmap() */
multiline_comment|/**&lt; Kernel-space: kernel-virtual address */
DECL|member|mtrr
r_int
id|mtrr
suffix:semicolon
multiline_comment|/**&lt; MTRR slot used */
multiline_comment|/*   Private data */
DECL|typedef|drm_map_t
)brace
id|drm_map_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_GET_CLIENT ioctl argument type.&n; */
DECL|struct|drm_client
r_typedef
r_struct
id|drm_client
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
multiline_comment|/**&lt; Which client desired? */
DECL|member|auth
r_int
id|auth
suffix:semicolon
multiline_comment|/**&lt; Is client authenticated? */
DECL|member|pid
r_int
r_int
id|pid
suffix:semicolon
multiline_comment|/**&lt; Process ID */
DECL|member|uid
r_int
r_int
id|uid
suffix:semicolon
multiline_comment|/**&lt; User ID */
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/**&lt; Magic */
DECL|member|iocs
r_int
r_int
id|iocs
suffix:semicolon
multiline_comment|/**&lt; Ioctl count */
DECL|typedef|drm_client_t
)brace
id|drm_client_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|_DRM_STAT_LOCK
id|_DRM_STAT_LOCK
comma
DECL|enumerator|_DRM_STAT_OPENS
id|_DRM_STAT_OPENS
comma
DECL|enumerator|_DRM_STAT_CLOSES
id|_DRM_STAT_CLOSES
comma
DECL|enumerator|_DRM_STAT_IOCTLS
id|_DRM_STAT_IOCTLS
comma
DECL|enumerator|_DRM_STAT_LOCKS
id|_DRM_STAT_LOCKS
comma
DECL|enumerator|_DRM_STAT_UNLOCKS
id|_DRM_STAT_UNLOCKS
comma
DECL|enumerator|_DRM_STAT_VALUE
id|_DRM_STAT_VALUE
comma
multiline_comment|/**&lt; Generic value */
DECL|enumerator|_DRM_STAT_BYTE
id|_DRM_STAT_BYTE
comma
multiline_comment|/**&lt; Generic byte counter (1024bytes/K) */
DECL|enumerator|_DRM_STAT_COUNT
id|_DRM_STAT_COUNT
comma
multiline_comment|/**&lt; Generic non-byte counter (1000/k) */
DECL|enumerator|_DRM_STAT_IRQ
id|_DRM_STAT_IRQ
comma
multiline_comment|/**&lt; IRQ */
DECL|enumerator|_DRM_STAT_PRIMARY
id|_DRM_STAT_PRIMARY
comma
multiline_comment|/**&lt; Primary DMA bytes */
DECL|enumerator|_DRM_STAT_SECONDARY
id|_DRM_STAT_SECONDARY
comma
multiline_comment|/**&lt; Secondary DMA bytes */
DECL|enumerator|_DRM_STAT_DMA
id|_DRM_STAT_DMA
comma
multiline_comment|/**&lt; DMA */
DECL|enumerator|_DRM_STAT_SPECIAL
id|_DRM_STAT_SPECIAL
comma
multiline_comment|/**&lt; Special DMA (e.g., priority or polled) */
DECL|enumerator|_DRM_STAT_MISSED
id|_DRM_STAT_MISSED
multiline_comment|/**&lt; Missed DMA opportunity */
multiline_comment|/* Add to the *END* of the list */
DECL|typedef|drm_stat_type_t
)brace
id|drm_stat_type_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_GET_STATS ioctl argument type.&n; */
DECL|struct|drm_stats
r_typedef
r_struct
id|drm_stats
(brace
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
r_struct
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|type
id|drm_stat_type_t
id|type
suffix:semicolon
DECL|member|data
)brace
id|data
(braket
l_int|15
)braket
suffix:semicolon
DECL|typedef|drm_stats_t
)brace
id|drm_stats_t
suffix:semicolon
multiline_comment|/**&n; * Hardware locking flags.&n; */
DECL|enum|drm_lock_flags
r_typedef
r_enum
id|drm_lock_flags
(brace
DECL|enumerator|_DRM_LOCK_READY
id|_DRM_LOCK_READY
op_assign
l_int|0x01
comma
multiline_comment|/**&lt; Wait until hardware is ready for DMA */
DECL|enumerator|_DRM_LOCK_QUIESCENT
id|_DRM_LOCK_QUIESCENT
op_assign
l_int|0x02
comma
multiline_comment|/**&lt; Wait until hardware quiescent */
DECL|enumerator|_DRM_LOCK_FLUSH
id|_DRM_LOCK_FLUSH
op_assign
l_int|0x04
comma
multiline_comment|/**&lt; Flush this context&squot;s DMA queue first */
DECL|enumerator|_DRM_LOCK_FLUSH_ALL
id|_DRM_LOCK_FLUSH_ALL
op_assign
l_int|0x08
comma
multiline_comment|/**&lt; Flush all DMA queues first */
multiline_comment|/* These *HALT* flags aren&squot;t supported yet&n;&t;&t;&t;&t;   -- they will be used to support the&n;&t;&t;&t;&t;   full-screen DGA-like mode. */
DECL|enumerator|_DRM_HALT_ALL_QUEUES
id|_DRM_HALT_ALL_QUEUES
op_assign
l_int|0x10
comma
multiline_comment|/**&lt; Halt all current and future queues */
DECL|enumerator|_DRM_HALT_CUR_QUEUES
id|_DRM_HALT_CUR_QUEUES
op_assign
l_int|0x20
multiline_comment|/**&lt; Halt all current queues */
DECL|typedef|drm_lock_flags_t
)brace
id|drm_lock_flags_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_LOCK, DRM_IOCTL_UNLOCK and DRM_IOCTL_FINISH ioctl argument type.&n; * &n; * &bslash;sa drmGetLock() and drmUnlock().&n; */
DECL|struct|drm_lock
r_typedef
r_struct
id|drm_lock
(brace
DECL|member|context
r_int
id|context
suffix:semicolon
DECL|member|flags
id|drm_lock_flags_t
id|flags
suffix:semicolon
DECL|typedef|drm_lock_t
)brace
id|drm_lock_t
suffix:semicolon
multiline_comment|/**&n; * DMA flags&n; *&n; * &bslash;warning &n; * These values &bslash;e must match xf86drm.h.&n; *&n; * &bslash;sa drm_dma.&n; */
DECL|enum|drm_dma_flags
r_typedef
r_enum
id|drm_dma_flags
(brace
multiline_comment|/* Flags for DMA buffer dispatch */
DECL|enumerator|_DRM_DMA_BLOCK
id|_DRM_DMA_BLOCK
op_assign
l_int|0x01
comma
multiline_comment|/**&lt;&n;&t;&t;&t;&t;       * Block until buffer dispatched.&n;&t;&t;&t;&t;       * &n;&t;&t;&t;&t;       * &bslash;note The buffer may not yet have&n;&t;&t;&t;&t;       * been processed by the hardware --&n;&t;&t;&t;&t;       * getting a hardware lock with the&n;&t;&t;&t;&t;       * hardware quiescent will ensure&n;&t;&t;&t;&t;       * that the buffer has been&n;&t;&t;&t;&t;       * processed.&n;&t;&t;&t;&t;       */
DECL|enumerator|_DRM_DMA_WHILE_LOCKED
id|_DRM_DMA_WHILE_LOCKED
op_assign
l_int|0x02
comma
multiline_comment|/**&lt; Dispatch while lock held */
DECL|enumerator|_DRM_DMA_PRIORITY
id|_DRM_DMA_PRIORITY
op_assign
l_int|0x04
comma
multiline_comment|/**&lt; High priority dispatch */
multiline_comment|/* Flags for DMA buffer request */
DECL|enumerator|_DRM_DMA_WAIT
id|_DRM_DMA_WAIT
op_assign
l_int|0x10
comma
multiline_comment|/**&lt; Wait for free buffers */
DECL|enumerator|_DRM_DMA_SMALLER_OK
id|_DRM_DMA_SMALLER_OK
op_assign
l_int|0x20
comma
multiline_comment|/**&lt; Smaller-than-requested buffers OK */
DECL|enumerator|_DRM_DMA_LARGER_OK
id|_DRM_DMA_LARGER_OK
op_assign
l_int|0x40
multiline_comment|/**&lt; Larger-than-requested buffers OK */
DECL|typedef|drm_dma_flags_t
)brace
id|drm_dma_flags_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_ADD_BUFS and DRM_IOCTL_MARK_BUFS ioctl argument type.&n; *&n; * &bslash;sa drmAddBufs().&n; */
DECL|struct|drm_buf_desc
r_typedef
r_struct
id|drm_buf_desc
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/**&lt; Number of buffers of this size */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/**&lt; Size in bytes */
DECL|member|low_mark
r_int
id|low_mark
suffix:semicolon
multiline_comment|/**&lt; Low water mark */
DECL|member|high_mark
r_int
id|high_mark
suffix:semicolon
multiline_comment|/**&lt; High water mark */
r_enum
(brace
DECL|enumerator|_DRM_PAGE_ALIGN
id|_DRM_PAGE_ALIGN
op_assign
l_int|0x01
comma
multiline_comment|/**&lt; Align on page boundaries for DMA */
DECL|enumerator|_DRM_AGP_BUFFER
id|_DRM_AGP_BUFFER
op_assign
l_int|0x02
comma
multiline_comment|/**&lt; Buffer is in AGP space */
DECL|enumerator|_DRM_SG_BUFFER
id|_DRM_SG_BUFFER
op_assign
l_int|0x04
multiline_comment|/**&lt; Scatter/gather memory buffer */
DECL|member|flags
)brace
id|flags
suffix:semicolon
DECL|member|agp_start
r_int
r_int
id|agp_start
suffix:semicolon
multiline_comment|/**&lt; &n;&t;&t;&t;&t;  * Start address of where the AGP buffers are&n;&t;&t;&t;&t;  * in the AGP aperture&n;&t;&t;&t;&t;  */
DECL|typedef|drm_buf_desc_t
)brace
id|drm_buf_desc_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_INFO_BUFS ioctl argument type.&n; */
DECL|struct|drm_buf_info
r_typedef
r_struct
id|drm_buf_info
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/**&lt; Entries in list */
DECL|member|list
id|drm_buf_desc_t
op_star
id|list
suffix:semicolon
DECL|typedef|drm_buf_info_t
)brace
id|drm_buf_info_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_FREE_BUFS ioctl argument type.&n; */
DECL|struct|drm_buf_free
r_typedef
r_struct
id|drm_buf_free
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|list
r_int
op_star
id|list
suffix:semicolon
DECL|typedef|drm_buf_free_t
)brace
id|drm_buf_free_t
suffix:semicolon
multiline_comment|/**&n; * Buffer information&n; *&n; * &bslash;sa drm_buf_map.&n; */
DECL|struct|drm_buf_pub
r_typedef
r_struct
id|drm_buf_pub
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
multiline_comment|/**&lt; Index into the master buffer list */
DECL|member|total
r_int
id|total
suffix:semicolon
multiline_comment|/**&lt; Buffer size */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/**&lt; Amount of buffer in use (for DMA) */
DECL|member|address
r_void
op_star
id|address
suffix:semicolon
multiline_comment|/**&lt; Address of buffer */
DECL|typedef|drm_buf_pub_t
)brace
id|drm_buf_pub_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_MAP_BUFS ioctl argument type.&n; */
DECL|struct|drm_buf_map
r_typedef
r_struct
id|drm_buf_map
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/**&lt; Length of the buffer list */
DECL|member|virtual
r_void
op_star
r_virtual
suffix:semicolon
multiline_comment|/**&lt; Mmap&squot;d area in user-virtual */
DECL|member|list
id|drm_buf_pub_t
op_star
id|list
suffix:semicolon
multiline_comment|/**&lt; Buffer information */
DECL|typedef|drm_buf_map_t
)brace
id|drm_buf_map_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_DMA ioctl argument type.&n; *&n; * Indices here refer to the offset into the buffer list in drm_buf_get.&n; *&n; * &bslash;sa drmDMA().&n; */
DECL|struct|drm_dma
r_typedef
r_struct
id|drm_dma
(brace
DECL|member|context
r_int
id|context
suffix:semicolon
multiline_comment|/**&lt; Context handle */
DECL|member|send_count
r_int
id|send_count
suffix:semicolon
multiline_comment|/**&lt; Number of buffers to send */
DECL|member|send_indices
r_int
op_star
id|send_indices
suffix:semicolon
multiline_comment|/**&lt; List of handles to buffers */
DECL|member|send_sizes
r_int
op_star
id|send_sizes
suffix:semicolon
multiline_comment|/**&lt; Lengths of data to send */
DECL|member|flags
id|drm_dma_flags_t
id|flags
suffix:semicolon
multiline_comment|/**&lt; Flags */
DECL|member|request_count
r_int
id|request_count
suffix:semicolon
multiline_comment|/**&lt; Number of buffers requested */
DECL|member|request_size
r_int
id|request_size
suffix:semicolon
multiline_comment|/**&lt; Desired size for buffers */
DECL|member|request_indices
r_int
op_star
id|request_indices
suffix:semicolon
multiline_comment|/**&lt; Buffer information */
DECL|member|request_sizes
r_int
op_star
id|request_sizes
suffix:semicolon
DECL|member|granted_count
r_int
id|granted_count
suffix:semicolon
multiline_comment|/**&lt; Number of buffers granted */
DECL|typedef|drm_dma_t
)brace
id|drm_dma_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|_DRM_CONTEXT_PRESERVED
id|_DRM_CONTEXT_PRESERVED
op_assign
l_int|0x01
comma
DECL|enumerator|_DRM_CONTEXT_2DONLY
id|_DRM_CONTEXT_2DONLY
op_assign
l_int|0x02
DECL|typedef|drm_ctx_flags_t
)brace
id|drm_ctx_flags_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_ADD_CTX ioctl argument type.&n; *&n; * &bslash;sa drmCreateContext() and drmDestroyContext().&n; */
DECL|struct|drm_ctx
r_typedef
r_struct
id|drm_ctx
(brace
DECL|member|handle
id|drm_context_t
id|handle
suffix:semicolon
DECL|member|flags
id|drm_ctx_flags_t
id|flags
suffix:semicolon
DECL|typedef|drm_ctx_t
)brace
id|drm_ctx_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_RES_CTX ioctl argument type.&n; */
DECL|struct|drm_ctx_res
r_typedef
r_struct
id|drm_ctx_res
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|contexts
id|drm_ctx_t
op_star
id|contexts
suffix:semicolon
DECL|typedef|drm_ctx_res_t
)brace
id|drm_ctx_res_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_ADD_DRAW and DRM_IOCTL_RM_DRAW ioctl argument type.&n; */
DECL|struct|drm_draw
r_typedef
r_struct
id|drm_draw
(brace
DECL|member|handle
id|drm_drawable_t
id|handle
suffix:semicolon
DECL|typedef|drm_draw_t
)brace
id|drm_draw_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_GET_MAGIC and DRM_IOCTL_AUTH_MAGIC ioctl argument type.&n; */
DECL|struct|drm_auth
r_typedef
r_struct
id|drm_auth
(brace
DECL|member|magic
id|drm_magic_t
id|magic
suffix:semicolon
DECL|typedef|drm_auth_t
)brace
id|drm_auth_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_IRQ_BUSID ioctl argument type.&n; *&n; * &bslash;sa drmGetInterruptFromBusID().&n; */
DECL|struct|drm_irq_busid
r_typedef
r_struct
id|drm_irq_busid
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/**&lt; IRQ number */
DECL|member|busnum
r_int
id|busnum
suffix:semicolon
multiline_comment|/**&lt; bus number */
DECL|member|devnum
r_int
id|devnum
suffix:semicolon
multiline_comment|/**&lt; device number */
DECL|member|funcnum
r_int
id|funcnum
suffix:semicolon
multiline_comment|/**&lt; function number */
DECL|typedef|drm_irq_busid_t
)brace
id|drm_irq_busid_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|_DRM_VBLANK_ABSOLUTE
id|_DRM_VBLANK_ABSOLUTE
op_assign
l_int|0x0
comma
multiline_comment|/**&lt; Wait for specific vblank sequence number */
DECL|enumerator|_DRM_VBLANK_RELATIVE
id|_DRM_VBLANK_RELATIVE
op_assign
l_int|0x1
comma
multiline_comment|/**&lt; Wait for given number of vblanks */
DECL|enumerator|_DRM_VBLANK_SIGNAL
id|_DRM_VBLANK_SIGNAL
op_assign
l_int|0x40000000
multiline_comment|/**&lt; Send signal instead of blocking */
DECL|typedef|drm_vblank_seq_type_t
)brace
id|drm_vblank_seq_type_t
suffix:semicolon
DECL|macro|_DRM_VBLANK_FLAGS_MASK
mdefine_line|#define _DRM_VBLANK_FLAGS_MASK _DRM_VBLANK_SIGNAL
DECL|struct|drm_wait_vblank_request
r_struct
id|drm_wait_vblank_request
(brace
DECL|member|type
id|drm_vblank_seq_type_t
id|type
suffix:semicolon
DECL|member|sequence
r_int
r_int
id|sequence
suffix:semicolon
DECL|member|signal
r_int
r_int
id|signal
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|drm_wait_vblank_reply
r_struct
id|drm_wait_vblank_reply
(brace
DECL|member|type
id|drm_vblank_seq_type_t
id|type
suffix:semicolon
DECL|member|sequence
r_int
r_int
id|sequence
suffix:semicolon
DECL|member|tval_sec
r_int
id|tval_sec
suffix:semicolon
DECL|member|tval_usec
r_int
id|tval_usec
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_WAIT_VBLANK ioctl argument type.&n; *&n; * &bslash;sa drmWaitVBlank().&n; */
DECL|union|drm_wait_vblank
r_typedef
r_union
id|drm_wait_vblank
(brace
DECL|member|request
r_struct
id|drm_wait_vblank_request
id|request
suffix:semicolon
DECL|member|reply
r_struct
id|drm_wait_vblank_reply
id|reply
suffix:semicolon
DECL|typedef|drm_wait_vblank_t
)brace
id|drm_wait_vblank_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_AGP_ENABLE ioctl argument type.&n; *&n; * &bslash;sa drmAgpEnable().&n; */
DECL|struct|drm_agp_mode
r_typedef
r_struct
id|drm_agp_mode
(brace
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/**&lt; AGP mode */
DECL|typedef|drm_agp_mode_t
)brace
id|drm_agp_mode_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_AGP_ALLOC and DRM_IOCTL_AGP_FREE ioctls argument type.&n; *&n; * &bslash;sa drmAgpAlloc() and drmAgpFree().&n; */
DECL|struct|drm_agp_buffer
r_typedef
r_struct
id|drm_agp_buffer
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/**&lt; In bytes -- will round to page boundary */
DECL|member|handle
r_int
r_int
id|handle
suffix:semicolon
multiline_comment|/**&lt; Used for binding / unbinding */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/**&lt; Type of memory to allocate */
DECL|member|physical
r_int
r_int
id|physical
suffix:semicolon
multiline_comment|/**&lt; Physical used by i810 */
DECL|typedef|drm_agp_buffer_t
)brace
id|drm_agp_buffer_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_AGP_BIND and DRM_IOCTL_AGP_UNBIND ioctls argument type.&n; *&n; * &bslash;sa drmAgpBind() and drmAgpUnbind().&n; */
DECL|struct|drm_agp_binding
r_typedef
r_struct
id|drm_agp_binding
(brace
DECL|member|handle
r_int
r_int
id|handle
suffix:semicolon
multiline_comment|/**&lt; From drm_agp_buffer */
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/**&lt; In bytes -- will round to page boundary */
DECL|typedef|drm_agp_binding_t
)brace
id|drm_agp_binding_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_AGP_INFO ioctl argument type.&n; *&n; * &bslash;sa drmAgpVersionMajor(), drmAgpVersionMinor(), drmAgpGetMode(),&n; * drmAgpBase(), drmAgpSize(), drmAgpMemoryUsed(), drmAgpMemoryAvail(),&n; * drmAgpVendorId() and drmAgpDeviceId().&n; */
DECL|struct|drm_agp_info
r_typedef
r_struct
id|drm_agp_info
(brace
DECL|member|agp_version_major
r_int
id|agp_version_major
suffix:semicolon
DECL|member|agp_version_minor
r_int
id|agp_version_minor
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|aperture_base
r_int
r_int
id|aperture_base
suffix:semicolon
multiline_comment|/* physical address */
DECL|member|aperture_size
r_int
r_int
id|aperture_size
suffix:semicolon
multiline_comment|/* bytes */
DECL|member|memory_allowed
r_int
r_int
id|memory_allowed
suffix:semicolon
multiline_comment|/* bytes */
DECL|member|memory_used
r_int
r_int
id|memory_used
suffix:semicolon
multiline_comment|/* PCI information */
DECL|member|id_vendor
r_int
r_int
id|id_vendor
suffix:semicolon
DECL|member|id_device
r_int
r_int
id|id_device
suffix:semicolon
DECL|typedef|drm_agp_info_t
)brace
id|drm_agp_info_t
suffix:semicolon
multiline_comment|/**&n; * DRM_IOCTL_SG_ALLOC ioctl argument type.&n; */
DECL|struct|drm_scatter_gather
r_typedef
r_struct
id|drm_scatter_gather
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/**&lt; In bytes -- will round to page boundary */
DECL|member|handle
r_int
r_int
id|handle
suffix:semicolon
multiline_comment|/**&lt; Used for mapping / unmapping */
DECL|typedef|drm_scatter_gather_t
)brace
id|drm_scatter_gather_t
suffix:semicolon
DECL|macro|DRM_IOCTL_BASE
mdefine_line|#define DRM_IOCTL_BASE&t;&t;&t;&squot;d&squot;
DECL|macro|DRM_IO
mdefine_line|#define DRM_IO(nr)&t;&t;&t;_IO(DRM_IOCTL_BASE,nr)
DECL|macro|DRM_IOR
mdefine_line|#define DRM_IOR(nr,type)&t;&t;_IOR(DRM_IOCTL_BASE,nr,type)
DECL|macro|DRM_IOW
mdefine_line|#define DRM_IOW(nr,type)&t;&t;_IOW(DRM_IOCTL_BASE,nr,type)
DECL|macro|DRM_IOWR
mdefine_line|#define DRM_IOWR(nr,type)&t;&t;_IOWR(DRM_IOCTL_BASE,nr,type)
DECL|macro|DRM_IOCTL_VERSION
mdefine_line|#define DRM_IOCTL_VERSION&t;&t;DRM_IOWR(0x00, drm_version_t)
DECL|macro|DRM_IOCTL_GET_UNIQUE
mdefine_line|#define DRM_IOCTL_GET_UNIQUE&t;&t;DRM_IOWR(0x01, drm_unique_t)
DECL|macro|DRM_IOCTL_GET_MAGIC
mdefine_line|#define DRM_IOCTL_GET_MAGIC&t;&t;DRM_IOR( 0x02, drm_auth_t)
DECL|macro|DRM_IOCTL_IRQ_BUSID
mdefine_line|#define DRM_IOCTL_IRQ_BUSID&t;&t;DRM_IOWR(0x03, drm_irq_busid_t)
DECL|macro|DRM_IOCTL_GET_MAP
mdefine_line|#define DRM_IOCTL_GET_MAP               DRM_IOWR(0x04, drm_map_t)
DECL|macro|DRM_IOCTL_GET_CLIENT
mdefine_line|#define DRM_IOCTL_GET_CLIENT            DRM_IOWR(0x05, drm_client_t)
DECL|macro|DRM_IOCTL_GET_STATS
mdefine_line|#define DRM_IOCTL_GET_STATS             DRM_IOR( 0x06, drm_stats_t)
DECL|macro|DRM_IOCTL_SET_UNIQUE
mdefine_line|#define DRM_IOCTL_SET_UNIQUE&t;&t;DRM_IOW( 0x10, drm_unique_t)
DECL|macro|DRM_IOCTL_AUTH_MAGIC
mdefine_line|#define DRM_IOCTL_AUTH_MAGIC&t;&t;DRM_IOW( 0x11, drm_auth_t)
DECL|macro|DRM_IOCTL_BLOCK
mdefine_line|#define DRM_IOCTL_BLOCK&t;&t;&t;DRM_IOWR(0x12, drm_block_t)
DECL|macro|DRM_IOCTL_UNBLOCK
mdefine_line|#define DRM_IOCTL_UNBLOCK&t;&t;DRM_IOWR(0x13, drm_block_t)
DECL|macro|DRM_IOCTL_CONTROL
mdefine_line|#define DRM_IOCTL_CONTROL&t;&t;DRM_IOW( 0x14, drm_control_t)
DECL|macro|DRM_IOCTL_ADD_MAP
mdefine_line|#define DRM_IOCTL_ADD_MAP&t;&t;DRM_IOWR(0x15, drm_map_t)
DECL|macro|DRM_IOCTL_ADD_BUFS
mdefine_line|#define DRM_IOCTL_ADD_BUFS&t;&t;DRM_IOWR(0x16, drm_buf_desc_t)
DECL|macro|DRM_IOCTL_MARK_BUFS
mdefine_line|#define DRM_IOCTL_MARK_BUFS&t;&t;DRM_IOW( 0x17, drm_buf_desc_t)
DECL|macro|DRM_IOCTL_INFO_BUFS
mdefine_line|#define DRM_IOCTL_INFO_BUFS&t;&t;DRM_IOWR(0x18, drm_buf_info_t)
DECL|macro|DRM_IOCTL_MAP_BUFS
mdefine_line|#define DRM_IOCTL_MAP_BUFS&t;&t;DRM_IOWR(0x19, drm_buf_map_t)
DECL|macro|DRM_IOCTL_FREE_BUFS
mdefine_line|#define DRM_IOCTL_FREE_BUFS&t;&t;DRM_IOW( 0x1a, drm_buf_free_t)
DECL|macro|DRM_IOCTL_RM_MAP
mdefine_line|#define DRM_IOCTL_RM_MAP&t;&t;DRM_IOW( 0x1b, drm_map_t)
DECL|macro|DRM_IOCTL_SET_SAREA_CTX
mdefine_line|#define DRM_IOCTL_SET_SAREA_CTX&t;&t;DRM_IOW( 0x1c, drm_ctx_priv_map_t)
DECL|macro|DRM_IOCTL_GET_SAREA_CTX
mdefine_line|#define DRM_IOCTL_GET_SAREA_CTX &t;DRM_IOWR(0x1d, drm_ctx_priv_map_t)
DECL|macro|DRM_IOCTL_ADD_CTX
mdefine_line|#define DRM_IOCTL_ADD_CTX&t;&t;DRM_IOWR(0x20, drm_ctx_t)
DECL|macro|DRM_IOCTL_RM_CTX
mdefine_line|#define DRM_IOCTL_RM_CTX&t;&t;DRM_IOWR(0x21, drm_ctx_t)
DECL|macro|DRM_IOCTL_MOD_CTX
mdefine_line|#define DRM_IOCTL_MOD_CTX&t;&t;DRM_IOW( 0x22, drm_ctx_t)
DECL|macro|DRM_IOCTL_GET_CTX
mdefine_line|#define DRM_IOCTL_GET_CTX&t;&t;DRM_IOWR(0x23, drm_ctx_t)
DECL|macro|DRM_IOCTL_SWITCH_CTX
mdefine_line|#define DRM_IOCTL_SWITCH_CTX&t;&t;DRM_IOW( 0x24, drm_ctx_t)
DECL|macro|DRM_IOCTL_NEW_CTX
mdefine_line|#define DRM_IOCTL_NEW_CTX&t;&t;DRM_IOW( 0x25, drm_ctx_t)
DECL|macro|DRM_IOCTL_RES_CTX
mdefine_line|#define DRM_IOCTL_RES_CTX&t;&t;DRM_IOWR(0x26, drm_ctx_res_t)
DECL|macro|DRM_IOCTL_ADD_DRAW
mdefine_line|#define DRM_IOCTL_ADD_DRAW&t;&t;DRM_IOWR(0x27, drm_draw_t)
DECL|macro|DRM_IOCTL_RM_DRAW
mdefine_line|#define DRM_IOCTL_RM_DRAW&t;&t;DRM_IOWR(0x28, drm_draw_t)
DECL|macro|DRM_IOCTL_DMA
mdefine_line|#define DRM_IOCTL_DMA&t;&t;&t;DRM_IOWR(0x29, drm_dma_t)
DECL|macro|DRM_IOCTL_LOCK
mdefine_line|#define DRM_IOCTL_LOCK&t;&t;&t;DRM_IOW( 0x2a, drm_lock_t)
DECL|macro|DRM_IOCTL_UNLOCK
mdefine_line|#define DRM_IOCTL_UNLOCK&t;&t;DRM_IOW( 0x2b, drm_lock_t)
DECL|macro|DRM_IOCTL_FINISH
mdefine_line|#define DRM_IOCTL_FINISH&t;&t;DRM_IOW( 0x2c, drm_lock_t)
DECL|macro|DRM_IOCTL_AGP_ACQUIRE
mdefine_line|#define DRM_IOCTL_AGP_ACQUIRE&t;&t;DRM_IO(  0x30)
DECL|macro|DRM_IOCTL_AGP_RELEASE
mdefine_line|#define DRM_IOCTL_AGP_RELEASE&t;&t;DRM_IO(  0x31)
DECL|macro|DRM_IOCTL_AGP_ENABLE
mdefine_line|#define DRM_IOCTL_AGP_ENABLE&t;&t;DRM_IOW( 0x32, drm_agp_mode_t)
DECL|macro|DRM_IOCTL_AGP_INFO
mdefine_line|#define DRM_IOCTL_AGP_INFO&t;&t;DRM_IOR( 0x33, drm_agp_info_t)
DECL|macro|DRM_IOCTL_AGP_ALLOC
mdefine_line|#define DRM_IOCTL_AGP_ALLOC&t;&t;DRM_IOWR(0x34, drm_agp_buffer_t)
DECL|macro|DRM_IOCTL_AGP_FREE
mdefine_line|#define DRM_IOCTL_AGP_FREE&t;&t;DRM_IOW( 0x35, drm_agp_buffer_t)
DECL|macro|DRM_IOCTL_AGP_BIND
mdefine_line|#define DRM_IOCTL_AGP_BIND&t;&t;DRM_IOW( 0x36, drm_agp_binding_t)
DECL|macro|DRM_IOCTL_AGP_UNBIND
mdefine_line|#define DRM_IOCTL_AGP_UNBIND&t;&t;DRM_IOW( 0x37, drm_agp_binding_t)
DECL|macro|DRM_IOCTL_SG_ALLOC
mdefine_line|#define DRM_IOCTL_SG_ALLOC&t;&t;DRM_IOW( 0x38, drm_scatter_gather_t)
DECL|macro|DRM_IOCTL_SG_FREE
mdefine_line|#define DRM_IOCTL_SG_FREE&t;&t;DRM_IOW( 0x39, drm_scatter_gather_t)
DECL|macro|DRM_IOCTL_WAIT_VBLANK
mdefine_line|#define DRM_IOCTL_WAIT_VBLANK&t;&t;DRM_IOWR(0x3a, drm_wait_vblank_t)
multiline_comment|/**&n; * Device specific ioctls should only be in their respective headers&n; * The device specific ioctl range is from 0x40 to 0x79.&n; *&n; * &bslash;sa drmCommandNone(), drmCommandRead(), drmCommandWrite(), and&n; * drmCommandReadWrite().&n; */
DECL|macro|DRM_COMMAND_BASE
mdefine_line|#define DRM_COMMAND_BASE                0x40
macro_line|#endif
eof
