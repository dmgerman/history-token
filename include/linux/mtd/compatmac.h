multiline_comment|/*&n; * mtd/include/compatmac.h&n; *&n; * $Id: compatmac.h,v 1.4 2000/07/03 10:01:38 dwmw2 Exp $&n; *&n; * Extensions and omissions from the normal &squot;linux/compatmac.h&squot;&n; * files. hopefully this will end up empty as the &squot;real&squot; one &n; * becomes fully-featured.&n; */
multiline_comment|/* First, include the parts which the kernel is good enough to provide &n; * to us &n; */
macro_line|#ifndef __LINUX_MTD_COMPATMAC_H__
DECL|macro|__LINUX_MTD_COMPATMAC_H__
mdefine_line|#define __LINUX_MTD_COMPATMAC_H__
macro_line|#include &lt;linux/compatmac.h&gt;
macro_line|#include &lt;linux/types.h&gt; /* used later in this header */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,0)
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,0,0)
macro_line|#  error &quot;This kernel is too old: not supported by this file&quot;
macro_line|#endif
multiline_comment|/* Modularization issues */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,18)
DECL|macro|__USE_OLD_SYMTAB__
macro_line|#  define __USE_OLD_SYMTAB__
DECL|macro|EXPORT_NO_SYMBOLS
macro_line|#  define EXPORT_NO_SYMBOLS register_symtab(NULL);
DECL|macro|REGISTER_SYMTAB
macro_line|#  define REGISTER_SYMTAB(tab) register_symtab(tab)
macro_line|#else
DECL|macro|REGISTER_SYMTAB
macro_line|#  define REGISTER_SYMTAB(tab) /* nothing */
macro_line|#endif
macro_line|#ifdef __USE_OLD_SYMTAB__
DECL|macro|__MODULE_STRING
macro_line|#  define __MODULE_STRING(s)         /* nothing */
DECL|macro|MODULE_PARM
macro_line|#  define MODULE_PARM(v,t)           /* nothing */
DECL|macro|MODULE_PARM_DESC
macro_line|#  define MODULE_PARM_DESC(v,t)      /* nothing */
DECL|macro|MODULE_AUTHOR
macro_line|#  define MODULE_AUTHOR(n)           /* nothing */
DECL|macro|MODULE_DESCRIPTION
macro_line|#  define MODULE_DESCRIPTION(d)      /* nothing */
DECL|macro|MODULE_SUPPORTED_DEVICE
macro_line|#  define MODULE_SUPPORTED_DEVICE(n) /* nothing */
macro_line|#endif
multiline_comment|/*&n; * &quot;select&quot; changed in 2.1.23. The implementation is twin, but this&n; * header is new&n; */
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,1,22)
macro_line|#  include &lt;linux/poll.h&gt;
macro_line|#else
DECL|macro|__USE_OLD_SELECT__
macro_line|#  define __USE_OLD_SELECT__
macro_line|#endif
multiline_comment|/* Other change in the fops are solved using pseudo-types */
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,0)
DECL|macro|lseek_t
macro_line|#  define lseek_t      long long
DECL|macro|lseek_off_t
macro_line|#  define lseek_off_t  long long
macro_line|#else
DECL|macro|lseek_t
macro_line|#  define lseek_t      int
DECL|macro|lseek_off_t
macro_line|#  define lseek_off_t  off_t
macro_line|#endif
multiline_comment|/* changed the prototype of read/write */
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,0) || defined(__alpha__)
DECL|macro|count_t
macro_line|# define count_t unsigned long
DECL|macro|read_write_t
macro_line|# define read_write_t long
macro_line|#else
DECL|macro|count_t
macro_line|# define count_t int
DECL|macro|read_write_t
macro_line|# define read_write_t int
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,31)
DECL|macro|release_t
macro_line|# define release_t void
DECL|macro|release_return
macro_line|#  define release_return(x) return
macro_line|#else
DECL|macro|release_t
macro_line|#  define release_t int
DECL|macro|release_return
macro_line|#  define release_return(x) return (x)
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; 0x20300
DECL|macro|__exit
mdefine_line|#define __exit
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; 0x20200
DECL|macro|__init
mdefine_line|#define __init
macro_line|#else
macro_line|#include &lt;linux/init.h&gt;
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; 0x20300
DECL|macro|init_MUTEX
mdefine_line|#define init_MUTEX(x) do {*(x) = MUTEX;} while (0)
DECL|macro|RQFUNC_ARG
mdefine_line|#define RQFUNC_ARG void
DECL|macro|blkdev_dequeue_request
mdefine_line|#define blkdev_dequeue_request(req) do {CURRENT = req-&gt;next;} while (0)
macro_line|#else
DECL|macro|RQFUNC_ARG
mdefine_line|#define RQFUNC_ARG request_queue_t *q
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,2,0)
DECL|macro|__MOD_INC_USE_COUNT
mdefine_line|#define __MOD_INC_USE_COUNT(mod)                                        &bslash;&n;        (atomic_inc(&amp;(mod)-&gt;uc.usecount), (mod)-&gt;flags |= MOD_VISITED|MOD_USED_ONCE)
DECL|macro|__MOD_DEC_USE_COUNT
mdefine_line|#define __MOD_DEC_USE_COUNT(mod)                                        &bslash;&n;        (atomic_dec(&amp;(mod)-&gt;uc.usecount), (mod)-&gt;flags |= MOD_VISITED)
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)
DECL|macro|DECLARE_WAIT_QUEUE_HEAD
mdefine_line|#define DECLARE_WAIT_QUEUE_HEAD(x) struct wait_queue *x = NULL
DECL|macro|init_waitqueue_head
mdefine_line|#define init_waitqueue_head init_waitqueue
DECL|function|try_inc_mod_count
r_static
r_inline
r_int
id|try_inc_mod_count
c_func
(paren
r_struct
id|module
op_star
id|mod
)paren
(brace
r_if
c_cond
(paren
id|mod
)paren
id|__MOD_INC_USE_COUNT
c_func
(paren
id|mod
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Yes, I&squot;m aware that it&squot;s a fairly ugly hack.&n;   Until the __constant_* macros appear in Linus&squot; own kernels, this is&n;   the way it has to be done.&n; DW 19/1/00&n; */
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifndef __constant_cpu_to_le16
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|__constant_cpu_to_le64
mdefine_line|#define __constant_cpu_to_le64(x) ___swab64((x))
DECL|macro|__constant_le64_to_cpu
mdefine_line|#define __constant_le64_to_cpu(x) ___swab64((x))
DECL|macro|__constant_cpu_to_le32
mdefine_line|#define __constant_cpu_to_le32(x) ___swab32((x))
DECL|macro|__constant_le32_to_cpu
mdefine_line|#define __constant_le32_to_cpu(x) ___swab32((x))
DECL|macro|__constant_cpu_to_le16
mdefine_line|#define __constant_cpu_to_le16(x) ___swab16((x))
DECL|macro|__constant_le16_to_cpu
mdefine_line|#define __constant_le16_to_cpu(x) ___swab16((x))
DECL|macro|__constant_cpu_to_be64
mdefine_line|#define __constant_cpu_to_be64(x) ((__u64)(x))
DECL|macro|__constant_be64_to_cpu
mdefine_line|#define __constant_be64_to_cpu(x) ((__u64)(x))
DECL|macro|__constant_cpu_to_be32
mdefine_line|#define __constant_cpu_to_be32(x) ((__u32)(x))
DECL|macro|__constant_be32_to_cpu
mdefine_line|#define __constant_be32_to_cpu(x) ((__u32)(x))
DECL|macro|__constant_cpu_to_be16
mdefine_line|#define __constant_cpu_to_be16(x) ((__u16)(x))
DECL|macro|__constant_be16_to_cpu
mdefine_line|#define __constant_be16_to_cpu(x) ((__u16)(x))
macro_line|#else
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|__constant_cpu_to_le64
mdefine_line|#define __constant_cpu_to_le64(x) ((__u64)(x))
DECL|macro|__constant_le64_to_cpu
mdefine_line|#define __constant_le64_to_cpu(x) ((__u64)(x))
DECL|macro|__constant_cpu_to_le32
mdefine_line|#define __constant_cpu_to_le32(x) ((__u32)(x))
DECL|macro|__constant_le32_to_cpu
mdefine_line|#define __constant_le32_to_cpu(x) ((__u32)(x))
DECL|macro|__constant_cpu_to_le16
mdefine_line|#define __constant_cpu_to_le16(x) ((__u16)(x))
DECL|macro|__constant_le16_to_cpu
mdefine_line|#define __constant_le16_to_cpu(x) ((__u16)(x))
DECL|macro|__constant_cpu_to_be64
mdefine_line|#define __constant_cpu_to_be64(x) ___swab64((x))
DECL|macro|__constant_be64_to_cpu
mdefine_line|#define __constant_be64_to_cpu(x) ___swab64((x))
DECL|macro|__constant_cpu_to_be32
mdefine_line|#define __constant_cpu_to_be32(x) ___swab32((x))
DECL|macro|__constant_be32_to_cpu
mdefine_line|#define __constant_be32_to_cpu(x) ___swab32((x))
DECL|macro|__constant_cpu_to_be16
mdefine_line|#define __constant_cpu_to_be16(x) ___swab16((x))
DECL|macro|__constant_be16_to_cpu
mdefine_line|#define __constant_be16_to_cpu(x) ___swab16((x))
macro_line|#else
macro_line|#error No (recognised) endianness defined (unless it,s PDP)
macro_line|#endif /* __LITTLE_ENDIAN */
macro_line|#endif /* __BIG_ENDIAN */
macro_line|#endif /* ifndef __constant_cpu_to_le16 */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)
DECL|macro|mod_init_t
mdefine_line|#define mod_init_t int  __init
DECL|macro|mod_exit_t
mdefine_line|#define mod_exit_t void  
macro_line|#else
DECL|macro|mod_init_t
mdefine_line|#define mod_init_t static int __init
DECL|macro|mod_exit_t
mdefine_line|#define mod_exit_t static void __exit
macro_line|#endif
macro_line|#ifndef THIS_MODULE
macro_line|#ifdef MODULE
DECL|macro|THIS_MODULE
mdefine_line|#define THIS_MODULE (&amp;__this_module)
macro_line|#else
DECL|macro|THIS_MODULE
mdefine_line|#define THIS_MODULE (NULL)
macro_line|#endif
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; 0x20300
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|macro|spin_lock_bh
mdefine_line|#define spin_lock_bh(lock) do {start_bh_atomic();spin_lock(lock);}while(0);
DECL|macro|spin_unlock_bh
mdefine_line|#define spin_unlock_bh(lock) do {spin_unlock(lock);end_bh_atomic();}while(0);
macro_line|#else
macro_line|#include &lt;asm/softirq.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#endif
macro_line|#endif /* __LINUX_MTD_COMPATMAC_H__ */
eof
