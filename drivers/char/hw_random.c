multiline_comment|/*&n; &t;Hardware driver for the Intel/AMD/Via Random Number Generators (RNG)&n;&t;(c) Copyright 2003 Red Hat Inc &lt;jgarzik@redhat.com&gt;&n; &n; &t;derived from&n; &n;        Hardware driver for the AMD 768 Random Number Generator (RNG)&n;        (c) Copyright 2001 Red Hat Inc &lt;alan@redhat.com&gt;&n;&n; &t;derived from&n; &n;&t;Hardware driver for Intel i810 Random Number Generator (RNG)&n;&t;Copyright 2000,2001 Jeff Garzik &lt;jgarzik@pobox.com&gt;&n;&t;Copyright 2000,2001 Philipp Rumpf &lt;prumpf@mandrakesoft.com&gt;&n;&n;&t;Please read Documentation/hw_random.txt for details on use.&n;&n;&t;----------------------------------------------------------&n;&t;This software may be used and distributed according to the terms&n;        of the GNU General Public License, incorporated herein by reference.&n;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#ifdef __i386__
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/cpufeature.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * core module and version information&n; */
DECL|macro|RNG_VERSION
mdefine_line|#define RNG_VERSION &quot;0.9.0&quot;
DECL|macro|RNG_MODULE_NAME
mdefine_line|#define RNG_MODULE_NAME &quot;hw_random&quot;
DECL|macro|RNG_DRIVER_NAME
mdefine_line|#define RNG_DRIVER_NAME   RNG_MODULE_NAME &quot; hardware driver &quot; RNG_VERSION
DECL|macro|PFX
mdefine_line|#define PFX RNG_MODULE_NAME &quot;: &quot;
multiline_comment|/*&n; * debugging macros&n; */
DECL|macro|RNG_DEBUG
macro_line|#undef RNG_DEBUG /* define to enable copious debugging info */
macro_line|#ifdef RNG_DEBUG
multiline_comment|/* note: prints function name for you */
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...) printk(KERN_DEBUG &quot;%s: &quot; fmt, __FUNCTION__ , ## args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...)
macro_line|#endif
DECL|macro|RNG_NDEBUG
mdefine_line|#define RNG_NDEBUG        /* define to disable lightweight runtime checks */
macro_line|#ifdef RNG_NDEBUG
DECL|macro|assert
mdefine_line|#define assert(expr)
macro_line|#else
DECL|macro|assert
mdefine_line|#define assert(expr) &bslash;&n;        if(!(expr)) {                                   &bslash;&n;        printk( &quot;Assertion failed! %s,%s,%s,line=%d&bslash;n&quot;, &bslash;&n;        #expr,__FILE__,__FUNCTION__,__LINE__);          &bslash;&n;        }
macro_line|#endif
DECL|macro|RNG_MISCDEV_MINOR
mdefine_line|#define RNG_MISCDEV_MINOR&t;&t;183 /* official */
r_static
r_int
id|rng_dev_open
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
suffix:semicolon
r_static
r_int
id|rng_dev_release
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
suffix:semicolon
r_static
id|ssize_t
id|rng_dev_read
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
id|size
comma
id|loff_t
op_star
id|offp
)paren
suffix:semicolon
r_static
r_int
id|__init
id|intel_init
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|__exit
id|intel_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
r_int
id|intel_data_present
(paren
r_void
)paren
suffix:semicolon
r_static
id|u32
id|intel_data_read
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|__init
id|amd_init
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|__exit
id|amd_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
r_int
id|amd_data_present
(paren
r_void
)paren
suffix:semicolon
r_static
id|u32
id|amd_data_read
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|__init
id|via_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|__exit
id|via_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
r_int
id|via_data_present
(paren
r_void
)paren
suffix:semicolon
r_static
id|u32
id|via_data_read
(paren
r_void
)paren
suffix:semicolon
DECL|struct|rng_operations
r_struct
id|rng_operations
(brace
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|cleanup
r_void
(paren
op_star
id|cleanup
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|data_present
r_int
r_int
(paren
op_star
id|data_present
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|data_read
id|u32
(paren
op_star
id|data_read
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|n_bytes
r_int
r_int
id|n_bytes
suffix:semicolon
multiline_comment|/* number of bytes per -&gt;data_read */
)brace
suffix:semicolon
DECL|variable|rng_ops
r_static
r_struct
id|rng_operations
op_star
id|rng_ops
suffix:semicolon
DECL|variable|rng_open_sem
r_static
r_struct
id|semaphore
id|rng_open_sem
suffix:semicolon
multiline_comment|/* Semaphore for serializing rng_open/release */
DECL|variable|rng_chrdev_ops
r_static
r_struct
id|file_operations
id|rng_chrdev_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|rng_dev_open
comma
dot
id|release
op_assign
id|rng_dev_release
comma
dot
id|read
op_assign
id|rng_dev_read
comma
)brace
suffix:semicolon
DECL|variable|rng_miscdev
r_static
r_struct
id|miscdevice
id|rng_miscdev
op_assign
(brace
id|RNG_MISCDEV_MINOR
comma
id|RNG_MODULE_NAME
comma
op_amp
id|rng_chrdev_ops
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|rng_hw_none
id|rng_hw_none
comma
DECL|enumerator|rng_hw_intel
id|rng_hw_intel
comma
DECL|enumerator|rng_hw_amd
id|rng_hw_amd
comma
DECL|enumerator|rng_hw_via
id|rng_hw_via
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|rng_operations
id|rng_vendor_ops
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* rng_hw_none */
(brace
)brace
comma
multiline_comment|/* rng_hw_intel */
(brace
id|intel_init
comma
id|intel_cleanup
comma
id|intel_data_present
comma
id|intel_data_read
comma
l_int|1
)brace
comma
multiline_comment|/* rng_hw_amd */
(brace
id|amd_init
comma
id|amd_cleanup
comma
id|amd_data_present
comma
id|amd_data_read
comma
l_int|4
)brace
comma
multiline_comment|/* rng_hw_via */
(brace
id|via_init
comma
id|via_cleanup
comma
id|via_data_present
comma
id|via_data_read
comma
l_int|1
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Data for PCI driver interface&n; *&n; * This data only exists for exporting the supported&n; * PCI ids via MODULE_DEVICE_TABLE.  We do not actually&n; * register a pci_driver, because someone else might one day&n; * want to register another driver on the same PCI id.&n; */
DECL|variable|__initdata
r_static
r_struct
id|pci_device_id
id|rng_pci_tbl
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0x1022
comma
l_int|0x7443
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|rng_hw_amd
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x2418
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|rng_hw_intel
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x2428
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|rng_hw_intel
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x2448
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|rng_hw_intel
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x244e
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|rng_hw_intel
)brace
comma
(brace
l_int|0x8086
comma
l_int|0x245e
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|rng_hw_intel
)brace
comma
(brace
l_int|0
comma
)brace
comma
multiline_comment|/* terminate list */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|pci
comma
id|rng_pci_tbl
)paren
suffix:semicolon
multiline_comment|/***********************************************************************&n; *&n; * Intel RNG operations&n; *&n; */
multiline_comment|/*&n; * RNG registers (offsets from rng_mem)&n; */
DECL|macro|INTEL_RNG_HW_STATUS
mdefine_line|#define INTEL_RNG_HW_STATUS&t;&t;&t;0
DECL|macro|INTEL_RNG_PRESENT
mdefine_line|#define         INTEL_RNG_PRESENT&t;&t;0x40
DECL|macro|INTEL_RNG_ENABLED
mdefine_line|#define         INTEL_RNG_ENABLED&t;&t;0x01
DECL|macro|INTEL_RNG_STATUS
mdefine_line|#define INTEL_RNG_STATUS&t;&t;&t;1
DECL|macro|INTEL_RNG_DATA_PRESENT
mdefine_line|#define         INTEL_RNG_DATA_PRESENT&t;&t;0x01
DECL|macro|INTEL_RNG_DATA
mdefine_line|#define INTEL_RNG_DATA&t;&t;&t;&t;2
multiline_comment|/*&n; * Magic address at which Intel PCI bridges locate the RNG&n; */
DECL|macro|INTEL_RNG_ADDR
mdefine_line|#define INTEL_RNG_ADDR&t;&t;&t;&t;0xFFBC015F
DECL|macro|INTEL_RNG_ADDR_LEN
mdefine_line|#define INTEL_RNG_ADDR_LEN&t;&t;&t;3
multiline_comment|/* token to our ioremap&squot;d RNG register area */
DECL|variable|rng_mem
r_static
r_void
op_star
id|rng_mem
suffix:semicolon
DECL|function|intel_hwstatus
r_static
r_inline
id|u8
id|intel_hwstatus
(paren
r_void
)paren
(brace
m_assert
(paren
id|rng_mem
op_ne
l_int|NULL
)paren
suffix:semicolon
r_return
id|readb
(paren
id|rng_mem
op_plus
id|INTEL_RNG_HW_STATUS
)paren
suffix:semicolon
)brace
DECL|function|intel_hwstatus_set
r_static
r_inline
id|u8
id|intel_hwstatus_set
(paren
id|u8
id|hw_status
)paren
(brace
m_assert
(paren
id|rng_mem
op_ne
l_int|NULL
)paren
suffix:semicolon
id|writeb
(paren
id|hw_status
comma
id|rng_mem
op_plus
id|INTEL_RNG_HW_STATUS
)paren
suffix:semicolon
r_return
id|intel_hwstatus
(paren
)paren
suffix:semicolon
)brace
DECL|function|intel_data_present
r_static
r_int
r_int
id|intel_data_present
c_func
(paren
r_void
)paren
(brace
m_assert
(paren
id|rng_mem
op_ne
l_int|NULL
)paren
suffix:semicolon
r_return
(paren
id|readb
(paren
id|rng_mem
op_plus
id|INTEL_RNG_STATUS
)paren
op_amp
id|INTEL_RNG_DATA_PRESENT
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|intel_data_read
r_static
id|u32
id|intel_data_read
c_func
(paren
r_void
)paren
(brace
m_assert
(paren
id|rng_mem
op_ne
l_int|NULL
)paren
suffix:semicolon
r_return
id|readb
(paren
id|rng_mem
op_plus
id|INTEL_RNG_DATA
)paren
suffix:semicolon
)brace
DECL|function|intel_init
r_static
r_int
id|__init
id|intel_init
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|rc
suffix:semicolon
id|u8
id|hw_status
suffix:semicolon
id|DPRINTK
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
suffix:semicolon
id|rng_mem
op_assign
id|ioremap
(paren
id|INTEL_RNG_ADDR
comma
id|INTEL_RNG_ADDR_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rng_mem
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot ioremap RNG Memory&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
multiline_comment|/* Check for Intel 82802 */
id|hw_status
op_assign
id|intel_hwstatus
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hw_status
op_amp
id|INTEL_RNG_PRESENT
)paren
op_eq
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;RNG not detected&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err_out_free_map
suffix:semicolon
)brace
multiline_comment|/* turn RNG h/w on, if it&squot;s off */
r_if
c_cond
(paren
(paren
id|hw_status
op_amp
id|INTEL_RNG_ENABLED
)paren
op_eq
l_int|0
)paren
id|hw_status
op_assign
id|intel_hwstatus_set
(paren
id|hw_status
op_or
id|INTEL_RNG_ENABLED
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hw_status
op_amp
id|INTEL_RNG_ENABLED
)paren
op_eq
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot enable RNG, aborting&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_out_free_map
suffix:semicolon
)brace
id|DPRINTK
(paren
l_string|&quot;EXIT, returning 0&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_free_map
suffix:colon
id|iounmap
(paren
id|rng_mem
)paren
suffix:semicolon
id|rng_mem
op_assign
l_int|NULL
suffix:semicolon
id|err_out
suffix:colon
id|DPRINTK
(paren
l_string|&quot;EXIT, returning %d&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|intel_cleanup
r_static
r_void
id|__exit
id|intel_cleanup
c_func
(paren
r_void
)paren
(brace
id|u8
id|hw_status
suffix:semicolon
id|hw_status
op_assign
id|intel_hwstatus
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw_status
op_amp
id|INTEL_RNG_ENABLED
)paren
id|intel_hwstatus_set
(paren
id|hw_status
op_amp
op_complement
id|INTEL_RNG_ENABLED
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;unusual: RNG already disabled&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|rng_mem
)paren
suffix:semicolon
id|rng_mem
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/***********************************************************************&n; *&n; * AMD RNG operations&n; *&n; */
DECL|variable|pmbase
r_static
id|u32
id|pmbase
suffix:semicolon
multiline_comment|/* PMxx I/O base */
DECL|variable|amd_dev
r_static
r_struct
id|pci_dev
op_star
id|amd_dev
suffix:semicolon
DECL|function|amd_data_present
r_static
r_int
r_int
id|amd_data_present
(paren
r_void
)paren
(brace
r_return
id|inl
c_func
(paren
id|pmbase
op_plus
l_int|0xF4
)paren
op_amp
l_int|1
suffix:semicolon
)brace
DECL|function|amd_data_read
r_static
id|u32
id|amd_data_read
(paren
r_void
)paren
(brace
r_return
id|inl
c_func
(paren
id|pmbase
op_plus
l_int|0xF0
)paren
suffix:semicolon
)brace
DECL|function|amd_init
r_static
r_int
id|__init
id|amd_init
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|rc
suffix:semicolon
id|u8
id|rnen
suffix:semicolon
id|DPRINTK
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x58
comma
op_amp
id|pmbase
)paren
suffix:semicolon
id|pmbase
op_and_assign
l_int|0x0000FF00
suffix:semicolon
r_if
c_cond
(paren
id|pmbase
op_eq
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;power management base not set&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|rnen
)paren
suffix:semicolon
id|rnen
op_or_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
suffix:semicolon
multiline_comment|/* RNG on */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x40
comma
id|rnen
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x41
comma
op_amp
id|rnen
)paren
suffix:semicolon
id|rnen
op_or_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
suffix:semicolon
multiline_comment|/* PMIO enable */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x41
comma
id|rnen
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;AMD768 system management I/O registers at 0x%X.&bslash;n&quot;
comma
id|pmbase
)paren
suffix:semicolon
id|amd_dev
op_assign
id|dev
suffix:semicolon
id|DPRINTK
(paren
l_string|&quot;EXIT, returning 0&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out
suffix:colon
id|DPRINTK
(paren
l_string|&quot;EXIT, returning %d&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|amd_cleanup
r_static
r_void
id|__exit
id|amd_cleanup
c_func
(paren
r_void
)paren
(brace
id|u8
id|rnen
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|amd_dev
comma
l_int|0x40
comma
op_amp
id|rnen
)paren
suffix:semicolon
id|rnen
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|7
)paren
suffix:semicolon
multiline_comment|/* RNG off */
id|pci_write_config_byte
c_func
(paren
id|amd_dev
comma
l_int|0x40
comma
id|rnen
)paren
suffix:semicolon
multiline_comment|/* FIXME: twiddle pmio, also? */
)brace
multiline_comment|/***********************************************************************&n; *&n; * Via RNG operations&n; *&n; */
r_enum
(brace
DECL|enumerator|VIA_STRFILT_CNT_SHIFT
id|VIA_STRFILT_CNT_SHIFT
op_assign
l_int|16
comma
DECL|enumerator|VIA_STRFILT_FAIL
id|VIA_STRFILT_FAIL
op_assign
(paren
l_int|1
op_lshift
l_int|15
)paren
comma
DECL|enumerator|VIA_STRFILT_ENABLE
id|VIA_STRFILT_ENABLE
op_assign
(paren
l_int|1
op_lshift
l_int|14
)paren
comma
DECL|enumerator|VIA_RAWBITS_ENABLE
id|VIA_RAWBITS_ENABLE
op_assign
(paren
l_int|1
op_lshift
l_int|13
)paren
comma
DECL|enumerator|VIA_RNG_ENABLE
id|VIA_RNG_ENABLE
op_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
DECL|enumerator|VIA_XSTORE_CNT_MASK
id|VIA_XSTORE_CNT_MASK
op_assign
l_int|0x0F
comma
DECL|enumerator|VIA_RNG_CHUNK_8
id|VIA_RNG_CHUNK_8
op_assign
l_int|0x00
comma
multiline_comment|/* 64 rand bits, 64 stored bits */
DECL|enumerator|VIA_RNG_CHUNK_4
id|VIA_RNG_CHUNK_4
op_assign
l_int|0x01
comma
multiline_comment|/* 32 rand bits, 32 stored bits */
DECL|enumerator|VIA_RNG_CHUNK_4_MASK
id|VIA_RNG_CHUNK_4_MASK
op_assign
l_int|0xFFFFFFFF
comma
DECL|enumerator|VIA_RNG_CHUNK_2
id|VIA_RNG_CHUNK_2
op_assign
l_int|0x02
comma
multiline_comment|/* 16 rand bits, 32 stored bits */
DECL|enumerator|VIA_RNG_CHUNK_2_MASK
id|VIA_RNG_CHUNK_2_MASK
op_assign
l_int|0xFFFF
comma
DECL|enumerator|VIA_RNG_CHUNK_1
id|VIA_RNG_CHUNK_1
op_assign
l_int|0x03
comma
multiline_comment|/* 8 rand bits, 32 stored bits */
DECL|enumerator|VIA_RNG_CHUNK_1_MASK
id|VIA_RNG_CHUNK_1_MASK
op_assign
l_int|0xFF
comma
)brace
suffix:semicolon
DECL|variable|via_rng_datum
id|u32
id|via_rng_datum
suffix:semicolon
multiline_comment|/*&n; * Investigate using the &squot;rep&squot; prefix to obtain 32 bits of random data&n; * in one insn.  The upside is potentially better performance.  The&n; * downside is that the instruction becomes no longer atomic.  Due to&n; * this, just like familiar issues with /dev/random itself, the worst&n; * case of a &squot;rep xstore&squot; could potentially pause a cpu for an&n; * unreasonably long time.  In practice, this condition would likely&n; * only occur when the hardware is failing.  (or so we hope :))&n; *&n; * Another possible performance boost may come from simply buffering&n; * until we have 4 bytes, thus returning a u32 at a time,&n; * instead of the current u8-at-a-time.&n; */
DECL|function|xstore
r_static
r_inline
id|u32
id|xstore
c_func
(paren
id|u32
op_star
id|addr
comma
id|u32
id|edx_in
)paren
(brace
id|u32
id|eax_out
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.byte 0x0F,0xA7,0xC0 /* xstore %%edi (addr=%0) */&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
comma
l_string|&quot;=a&quot;
(paren
id|eax_out
)paren
suffix:colon
l_string|&quot;D&quot;
(paren
id|addr
)paren
comma
l_string|&quot;d&quot;
(paren
id|edx_in
)paren
)paren
suffix:semicolon
r_return
id|eax_out
suffix:semicolon
)brace
DECL|function|via_data_present
r_static
r_int
r_int
id|via_data_present
c_func
(paren
r_void
)paren
(brace
id|u32
id|bytes_out
suffix:semicolon
multiline_comment|/* We choose the recommended 1-byte-per-instruction RNG rate,&n;&t; * for greater randomness at the expense of speed.  Larger&n;&t; * values 2, 4, or 8 bytes-per-instruction yield greater&n;&t; * speed at lesser randomness.&n;&t; *&n;&t; * If you change this to another VIA_CHUNK_n, you must also&n;&t; * change the -&gt;n_bytes values in rng_vendor_ops[] tables.&n;&t; * VIA_CHUNK_8 requires further code changes.&n;&t; *&n;&t; * A copy of MSR_VIA_RNG is placed in eax_out when xstore&n;&t; * completes.&n;&t; */
id|via_rng_datum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* paranoia, not really necessary */
id|bytes_out
op_assign
id|xstore
c_func
(paren
op_amp
id|via_rng_datum
comma
id|VIA_RNG_CHUNK_1
)paren
op_amp
id|VIA_XSTORE_CNT_MASK
suffix:semicolon
r_if
c_cond
(paren
id|bytes_out
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|via_data_read
r_static
id|u32
id|via_data_read
c_func
(paren
r_void
)paren
(brace
r_return
id|via_rng_datum
suffix:semicolon
)brace
DECL|function|via_init
r_static
r_int
id|__init
id|via_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u32
id|lo
comma
id|hi
comma
id|old_lo
suffix:semicolon
multiline_comment|/* Control the RNG via MSR.  Tread lightly and pay very close&n;&t; * close attention to values written, as the reserved fields&n;&t; * are documented to be &quot;undefined and unpredictable&quot;; but it&n;&t; * does not say to write them as zero, so I make a guess that&n;&t; * we restore the values we find in the register.&n;&t; */
id|rdmsr
c_func
(paren
id|MSR_VIA_RNG
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|old_lo
op_assign
id|lo
suffix:semicolon
id|lo
op_and_assign
op_complement
(paren
l_int|0x7f
op_lshift
id|VIA_STRFILT_CNT_SHIFT
)paren
suffix:semicolon
id|lo
op_and_assign
op_complement
id|VIA_XSTORE_CNT_MASK
suffix:semicolon
id|lo
op_and_assign
op_complement
(paren
id|VIA_STRFILT_ENABLE
op_or
id|VIA_STRFILT_FAIL
op_or
id|VIA_RAWBITS_ENABLE
)paren
suffix:semicolon
id|lo
op_or_assign
id|VIA_RNG_ENABLE
suffix:semicolon
r_if
c_cond
(paren
id|lo
op_ne
id|old_lo
)paren
id|wrmsr
c_func
(paren
id|MSR_VIA_RNG
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
multiline_comment|/* perhaps-unnecessary sanity check; remove after testing if&n;&t;   unneeded */
id|rdmsr
c_func
(paren
id|MSR_VIA_RNG
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lo
op_amp
id|VIA_RNG_ENABLE
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;cannot enable Via C3 RNG, aborting&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|via_cleanup
r_static
r_void
id|__exit
id|via_cleanup
c_func
(paren
r_void
)paren
(brace
id|u32
id|lo
comma
id|hi
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_VIA_RNG
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|lo
op_and_assign
op_complement
id|VIA_RNG_ENABLE
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_VIA_RNG
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
)brace
multiline_comment|/***********************************************************************&n; *&n; * /dev/hwrandom character device handling (major 10, minor 183)&n; *&n; */
DECL|function|rng_dev_open
r_static
r_int
id|rng_dev_open
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
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_READ
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* wait for device to become free */
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
r_if
c_cond
(paren
id|down_trylock
(paren
op_amp
id|rng_open_sem
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|down_interruptible
(paren
op_amp
id|rng_open_sem
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rng_dev_release
r_static
r_int
id|rng_dev_release
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
id|up
c_func
(paren
op_amp
id|rng_open_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rng_dev_read
r_static
id|ssize_t
id|rng_dev_read
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
id|size
comma
id|loff_t
op_star
id|offp
)paren
(brace
r_static
id|spinlock_t
id|rng_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_int
r_int
id|have_data
suffix:semicolon
id|u32
id|data
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|rng_lock
)paren
suffix:semicolon
id|have_data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rng_ops
op_member_access_from_pointer
id|data_present
c_func
(paren
)paren
)paren
(brace
id|data
op_assign
id|rng_ops
op_member_access_from_pointer
id|data_read
c_func
(paren
)paren
suffix:semicolon
id|have_data
op_assign
id|rng_ops-&gt;n_bytes
suffix:semicolon
)brace
id|spin_unlock
(paren
op_amp
id|rng_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|have_data
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
(paren
id|u8
)paren
id|data
comma
id|buf
op_increment
)paren
)paren
(brace
id|ret
op_assign
id|ret
ques
c_cond
suffix:colon
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|size
op_decrement
suffix:semicolon
id|ret
op_increment
suffix:semicolon
id|have_data
op_decrement
suffix:semicolon
id|data
op_rshift_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
id|ret
ques
c_cond
suffix:colon
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* FIXME: We could poll for 250uS ?? */
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
r_return
id|ret
ques
c_cond
suffix:colon
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * rng_init_one - look for and attempt to init a single RNG&n; */
DECL|function|rng_init_one
r_static
r_int
id|__init
id|rng_init_one
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|rc
suffix:semicolon
id|DPRINTK
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
suffix:semicolon
m_assert
(paren
id|rng_ops
op_ne
l_int|NULL
)paren
suffix:semicolon
id|rc
op_assign
id|rng_ops
op_member_access_from_pointer
id|init
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|err_out
suffix:semicolon
id|rc
op_assign
id|misc_register
(paren
op_amp
id|rng_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
(paren
id|KERN_ERR
id|PFX
l_string|&quot;misc device register failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out_cleanup_hw
suffix:semicolon
)brace
id|DPRINTK
(paren
l_string|&quot;EXIT, returning 0&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_cleanup_hw
suffix:colon
id|rng_ops
op_member_access_from_pointer
id|cleanup
c_func
(paren
)paren
suffix:semicolon
id|err_out
suffix:colon
id|DPRINTK
(paren
l_string|&quot;EXIT, returning %d&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;The Linux Kernel team&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;H/W Random Number Generator (RNG) driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * rng_init - initialize RNG module&n; */
DECL|function|rng_init
r_static
r_int
id|__init
id|rng_init
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_const
r_struct
id|pci_device_id
op_star
id|ent
suffix:semicolon
id|DPRINTK
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
suffix:semicolon
id|init_MUTEX
(paren
op_amp
id|rng_open_sem
)paren
suffix:semicolon
multiline_comment|/* Probe for Intel, AMD RNGs */
id|pci_for_each_dev
c_func
(paren
id|pdev
)paren
(brace
id|ent
op_assign
id|pci_match_device
(paren
id|rng_pci_tbl
comma
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|rng_ops
op_assign
op_amp
id|rng_vendor_ops
(braket
id|ent-&gt;driver_data
)braket
suffix:semicolon
r_goto
id|match
suffix:semicolon
)brace
)brace
macro_line|#ifdef __i386__
multiline_comment|/* Probe for Via RNG */
r_if
c_cond
(paren
id|cpu_has_xstore
)paren
(brace
id|rng_ops
op_assign
op_amp
id|rng_vendor_ops
(braket
id|rng_hw_via
)braket
suffix:semicolon
id|pdev
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|match
suffix:semicolon
)brace
macro_line|#endif
id|DPRINTK
(paren
l_string|&quot;EXIT, returning -ENODEV&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
id|match
suffix:colon
id|rc
op_assign
id|rng_init_one
(paren
id|pdev
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
id|printk
(paren
id|KERN_INFO
id|RNG_DRIVER_NAME
l_string|&quot; loaded&bslash;n&quot;
)paren
suffix:semicolon
id|DPRINTK
(paren
l_string|&quot;EXIT, returning 0&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * rng_init - shutdown RNG module&n; */
DECL|function|rng_cleanup
r_static
r_void
id|__exit
id|rng_cleanup
(paren
r_void
)paren
(brace
id|DPRINTK
(paren
l_string|&quot;ENTER&bslash;n&quot;
)paren
suffix:semicolon
id|misc_deregister
(paren
op_amp
id|rng_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rng_ops-&gt;cleanup
)paren
id|rng_ops
op_member_access_from_pointer
id|cleanup
c_func
(paren
)paren
suffix:semicolon
id|DPRINTK
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|rng_init
id|module_init
(paren
id|rng_init
)paren
suffix:semicolon
DECL|variable|rng_cleanup
id|module_exit
(paren
id|rng_cleanup
)paren
suffix:semicolon
eof
