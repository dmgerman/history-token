multiline_comment|/*&n; * Xpram.c -- the S/390 expanded memory RAM-disk&n; *           &n; * significant parts of this code are based on&n; * the sbull device driver presented in&n; * A. Rubini: Linux Device Drivers&n; *&n; * Author of XPRAM specific coding: Reinhard Buendgen&n; *                                  buendgen@de.ibm.com&n; *&n; * External interfaces:&n; *   Interfaces to linux kernel&n; *        xpram_setup: read kernel parameters   (see init/main.c)&n; *        xpram_init:  initialize device driver (see drivers/block/ll_rw_blk.c)&n; *   Module interfaces&n; *        init_module&n; *        cleanup_module&n; *   Device specific file operations&n; *        xpram_iotcl&n; *        xpram_open&n; *        xpram_release&n; *&n; * &quot;ad-hoc&quot; partitioning:         &n; *    the expanded memory can be partitioned among several devices &n; *    (with different minors). The partitioning set up can be&n; *    set by kernel or module parameters (int devs &amp; int sizes[])&n; *&n; *    module parameters: devs= and sizes=&n; *    kernel parameters: xpram_parts=&n; *      note: I did not succeed in parsing numbers &n; *            for module parameters of type string &quot;s&quot; ?!?&n; *&n; * Other kenel files/modules affected(gerp for &quot;xpram&quot; or &quot;XPRAM&quot;:&n; *    drivers/s390/Config.in&n; *    drivers/s390/block/Makefile&n; *    include/linux/blk.h&n; *    include/linux/major.h&n; *    init/main.c&n; *    drivers/block//ll_rw_blk.c&n; *&n; *&n; * Potential future improvements:&n; *   request clustering: first coding started not yet tested or integrated&n; *                       I doubt that it really pays off &n; *   generic hard disk support to replace ad-hoc partitioning&n; *&n; * Tested with 2.2.14 (under VM)&n; */
macro_line|#ifdef MODULE
macro_line|#  ifndef __KERNEL__
DECL|macro|__KERNEL__
macro_line|#    define __KERNEL__
macro_line|#  endif
DECL|macro|__NO_VERSION__
macro_line|#  define __NO_VERSION__ /* don&squot;t define kernel_version in module.h */
macro_line|#endif /* MODULE */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifdef MODULE
DECL|variable|kernel_version
r_char
id|kernel_version
(braket
)braket
op_assign
id|UTS_RELEASE
suffix:semicolon
macro_line|#endif
macro_line|#if (LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,3,98))
DECL|macro|XPRAM_VERSION
macro_line|#  define XPRAM_VERSION 24
macro_line|#else
DECL|macro|XPRAM_VERSION
macro_line|#  define XPRAM_VERSION 22
macro_line|#endif 
macro_line|#if (XPRAM_VERSION == 24)
macro_line|#  include &lt;linux/config.h&gt;
macro_line|#  include &lt;linux/init.h&gt;
macro_line|#endif /* V24 */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt; /* printk() */
macro_line|#include &lt;linux/slab.h&gt; /* kmalloc() */
macro_line|#if (XPRAM_VERSION == 24)
macro_line|#  include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#endif /* V24 */
macro_line|#include &lt;linux/fs.h&gt;     /* everything... */
macro_line|#include &lt;linux/errno.h&gt;  /* error codes */
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/types.h&gt;  /* size_t */
macro_line|#include &lt;linux/ctype.h&gt;  /* isdigit, isxdigit */
macro_line|#include &lt;linux/fcntl.h&gt;  /* O_ACCMODE */
macro_line|#include &lt;linux/hdreg.h&gt;  /* HDIO_GETGEO */
macro_line|#include &lt;asm/system.h&gt;   /* cli(), *_flags */
macro_line|#include &lt;asm/uaccess.h&gt;  /* put_user */
macro_line|#if (XPRAM_VERSION == 24)
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR xpram_major /* force definitions on in blk.h */
DECL|variable|xpram_major
r_int
id|xpram_major
suffix:semicolon
multiline_comment|/* must be declared before including blk.h */
DECL|variable|xpram_devfs_handle
id|devfs_handle_t
id|xpram_devfs_handle
suffix:semicolon
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) MINOR(device)   /* xpram has no partition bits */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;xpram&quot;               /* name for messaging */
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR xpram_intrptr         /* pointer to the bottom half */
DECL|macro|DEVICE_NO_RANDOM
mdefine_line|#define DEVICE_NO_RANDOM                  /* no entropy to contribute */
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(d)                     /* do-nothing */
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;xpram.h&quot;        /* local definitions */
id|__setup
c_func
(paren
l_string|&quot;xpram_parts=&quot;
comma
id|xpram_setup
)paren
suffix:semicolon
macro_line|#endif /* V24 */
multiline_comment|/*&n;   define the debug levels:&n;   - 0 No debugging output to console or syslog&n;   - 1 Log internal errors to syslog, ignore check conditions &n;   - 2 Log internal errors and check conditions to syslog&n;   - 3 Log internal errors to console, log check conditions to syslog&n;   - 4 Log internal errors and check conditions to console&n;   - 5 panic on internal errors, log check conditions to console&n;   - 6 panic on both, internal errors and check conditions&n; */
DECL|macro|XPRAM_DEBUG
mdefine_line|#define XPRAM_DEBUG 4
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER XPRAM_NAME
macro_line|#if XPRAM_DEBUG &gt; 0
DECL|macro|PRINT_DEBUG
mdefine_line|#define PRINT_DEBUG(x...) printk ( KERN_DEBUG PRINTK_HEADER &quot;debug:&quot; x )
DECL|macro|PRINT_INFO
mdefine_line|#define PRINT_INFO(x...) printk ( KERN_INFO PRINTK_HEADER &quot;info:&quot; x )
DECL|macro|PRINT_WARN
mdefine_line|#define PRINT_WARN(x...) printk ( KERN_WARNING PRINTK_HEADER &quot;warning:&quot; x )
DECL|macro|PRINT_ERR
mdefine_line|#define PRINT_ERR(x...) printk ( KERN_ERR PRINTK_HEADER &quot;error:&quot; x )
DECL|macro|PRINT_FATAL
mdefine_line|#define PRINT_FATAL(x...) panic ( PRINTK_HEADER &quot;panic:&quot;x )
macro_line|#else
DECL|macro|PRINT_DEBUG
mdefine_line|#define PRINT_DEBUG(x...) printk ( KERN_DEBUG PRINTK_HEADER &quot;debug:&quot;  x )
DECL|macro|PRINT_INFO
mdefine_line|#define PRINT_INFO(x...) printk ( KERN_DEBUG PRINTK_HEADER &quot;info:&quot; x )
DECL|macro|PRINT_WARN
mdefine_line|#define PRINT_WARN(x...) printk ( KERN_DEBUG PRINTK_HEADER &quot;warning:&quot; x )
DECL|macro|PRINT_ERR
mdefine_line|#define PRINT_ERR(x...) printk ( KERN_DEBUG PRINTK_HEADER &quot;error:&quot; x )
DECL|macro|PRINT_FATAL
mdefine_line|#define PRINT_FATAL(x...) printk ( KERN_DEBUG PRINTK_HEADER &quot;panic:&quot; x )
macro_line|#endif&t;
macro_line|#if (XPRAM_VERSION == 22)
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR xpram_major /* force definitions on in blk.h */
DECL|variable|xpram_major
r_int
id|xpram_major
suffix:semicolon
multiline_comment|/* must be declared before including blk.h */
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) MINOR(device)   /* xpram has no partition bits */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;xpram&quot;               /* name for messaging */
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR xpram_intrptr         /* pointer to the bottom half */
DECL|macro|DEVICE_NO_RANDOM
mdefine_line|#define DEVICE_NO_RANDOM                  /* no entropy to contribute */
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(d) /* do-nothing */
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST *xpram_dummy_device_request  /* dummy function variable &n;&t;&t;&t;&t;&t;&t;     * to prevent warnings &n;&t;&t;&t;&t;&t;&t;     */#include &lt;linux/blk.h&gt;
macro_line|#include &quot;xpram.h&quot;        /* local definitions */
macro_line|#endif /* V22 */
multiline_comment|/*&n; * Non-prefixed symbols are static. They are meant to be assigned at&n; * load time. Prefixed symbols are not static, so they can be used in&n; * debugging. They are hidden anyways by register_symtab() unless&n; * XPRAM_DEBUG is defined.&n; */
DECL|variable|major
r_static
r_int
id|major
op_assign
id|XPRAM_MAJOR
suffix:semicolon
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
id|sizes
(braket
id|XPRAM_MAX_DEVS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|blksize
r_static
r_int
id|blksize
op_assign
id|XPRAM_BLKSIZE
suffix:semicolon
DECL|variable|hardsect
r_static
r_int
id|hardsect
op_assign
id|XPRAM_HARDSECT
suffix:semicolon
DECL|variable|xpram_devs
r_int
id|xpram_devs
suffix:semicolon
DECL|variable|xpram_blksize
DECL|variable|xpram_hardsect
r_int
id|xpram_blksize
comma
id|xpram_hardsect
suffix:semicolon
DECL|variable|xpram_mem_avail
r_int
id|xpram_mem_avail
op_assign
l_int|0
suffix:semicolon
DECL|variable|xpram_sizes
r_int
r_int
id|xpram_sizes
(braket
id|XPRAM_MAX_DEVS
)braket
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|devs
comma
l_string|&quot;i&quot;
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
multiline_comment|/* The following items are obtained through kmalloc() in init_module() */
DECL|variable|xpram_devices
id|Xpram_Dev
op_star
id|xpram_devices
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|xpram_blksizes
r_int
op_star
id|xpram_blksizes
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|xpram_offsets
r_int
op_star
id|xpram_offsets
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* partition offsets */
DECL|macro|MIN
mdefine_line|#define MIN(x,y) ((x) &lt; (y) ? (x) : (y))
DECL|macro|MAX
mdefine_line|#define MAX(x,y) ((x) &gt; (y) ? (x) : (y))
multiline_comment|/* &n; *              compute nearest multiple of 4 , argument must be non-negative&n; *              the macros used depends on XPRAM_KB_IN_PG = 4 &n; */
DECL|macro|NEXT4
mdefine_line|#define NEXT4(x) ((x &amp; 0x3) ? (x+4-(x &amp;0x3)) : (x))   /* increment if needed */
DECL|macro|LAST4
mdefine_line|#define LAST4(x) ((x &amp; 0x3) ? (x-4+(x &amp; 0x3)) : (x))  /* decrement if needed */
macro_line|#if 0               /* this is probably not faster than the previous code */
mdefine_line|#define NEXT4(x)   ((((x-1)&gt;&gt;2)&gt;&gt;2)+4)             /* increment if needed */
mdefine_line|#define LAST4(x)   (((x+3)&gt;&gt;2)&lt;&lt;2)                 /* decrement if needed */
macro_line|#endif
multiline_comment|/* integer formats */
DECL|macro|XPRAM_INVALF
mdefine_line|#define XPRAM_INVALF -1    /* invalid     */
DECL|macro|XPRAM_HEXF
mdefine_line|#define XPRAM_HEXF    0    /* hexadecimal */
DECL|macro|XPRAM_DECF
mdefine_line|#define XPRAM_DECF    1    /* decimal     */
multiline_comment|/* &n; *    parsing operations (needed for kernel parameter parsing)&n; */
multiline_comment|/* -------------------------------------------------------------------------&n; * sets the string pointer after the next comma &n; *&n; * argument:    strptr pointer to string&n; * side effect: strptr points to endof string or to position of the next &n; *              comma &n; * ------------------------------------------------------------------------*/
r_static
r_void
DECL|function|xpram_scan_to_next_comma
id|xpram_scan_to_next_comma
(paren
r_char
op_star
op_star
id|strptr
)paren
(brace
r_while
c_loop
(paren
(paren
(paren
op_star
op_star
id|strptr
)paren
op_ne
l_char|&squot;,&squot;
)paren
op_logical_and
(paren
op_star
op_star
id|strptr
)paren
)paren
(paren
op_star
id|strptr
)paren
op_increment
suffix:semicolon
)brace
multiline_comment|/* -------------------------------------------------------------------------&n; * interpret character as hex-digit&n; *&n; * argument: c charcter&n; * result: c interpreted as hex-digit&n; * note: can be used to read digits for any base &lt;= 16&n; * ------------------------------------------------------------------------*/
r_static
r_int
DECL|function|xpram_get_hexdigit
id|xpram_get_hexdigit
(paren
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;0&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;9&squot;
)paren
)paren
r_return
id|c
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;a&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;f&squot;
)paren
)paren
r_return
id|c
op_plus
l_int|10
op_minus
l_char|&squot;a&squot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;A&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;F&squot;
)paren
)paren
r_return
id|c
op_plus
l_int|10
op_minus
l_char|&squot;A&squot;
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------&n; * Check format of unsigned integer&n; *&n; * Argument: strptr pointer to string &n; * result:   -1 if strptr does not start with a digit &n; *                (does not start an integer)&n; *           0  if strptr starts a positive hex-integer with &quot;0x&quot; &n; *           1  if strptr start a positive decimal integer&n; *&n; * side effect: if strptr start a positive hex-integer then strptr is&n; *              set to the character after the &quot;0x&quot;&n; *-------------------------------------------------------------------------*/
r_static
r_int
DECL|function|xpram_int_format
id|xpram_int_format
c_func
(paren
r_char
op_star
op_star
id|strptr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|isdigit
c_func
(paren
op_star
op_star
id|strptr
)paren
)paren
r_return
id|XPRAM_INVALF
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
op_star
id|strptr
op_eq
l_char|&squot;0&squot;
)paren
op_logical_and
(paren
(paren
op_star
(paren
(paren
op_star
id|strptr
)paren
op_plus
l_int|1
)paren
op_eq
l_char|&squot;x&squot;
)paren
op_logical_or
(paren
op_star
(paren
(paren
op_star
id|strptr
)paren
op_plus
l_int|1
)paren
op_eq
l_char|&squot;X&squot;
)paren
)paren
op_logical_and
id|isdigit
c_func
(paren
op_star
(paren
(paren
op_star
id|strptr
)paren
op_plus
l_int|3
)paren
)paren
)paren
(brace
op_star
id|strptr
op_assign
(paren
op_star
id|strptr
)paren
op_plus
l_int|2
suffix:semicolon
r_return
id|XPRAM_HEXF
suffix:semicolon
)brace
r_else
r_return
id|XPRAM_DECF
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------&n; * Read non-negative decimal integer&n; *&n; * Argument: strptr pointer to string starting with a non-negative integer&n; *           in decimal format&n; * result:   the value of theinitial integer pointed to by strptr&n; *&n; * side effect: strptr is set to the first character following the integer&n; *-------------------------------------------------------------------------*/
r_static
r_int
DECL|function|xpram_read_decint
id|xpram_read_decint
(paren
r_char
op_star
op_star
id|strptr
)paren
(brace
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|isdigit
c_func
(paren
op_star
op_star
id|strptr
)paren
)paren
(brace
id|res
op_assign
(paren
id|res
op_star
l_int|10
)paren
op_plus
id|xpram_get_hexdigit
c_func
(paren
op_star
op_star
id|strptr
)paren
suffix:semicolon
(paren
op_star
id|strptr
)paren
op_increment
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------&n; * Read non-negative hex-integer&n; *&n; * Argument: strptr pointer to string starting with a non-negative integer&n; *           in hexformat (without &quot;0x&quot; prefix)&n; * result:   the value of the initial integer pointed to by strptr&n; *&n; * side effect: strptr is set to the first character following the integer&n; *-------------------------------------------------------------------------*/
r_static
r_int
DECL|function|xpram_read_hexint
id|xpram_read_hexint
(paren
r_char
op_star
op_star
id|strptr
)paren
(brace
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|isxdigit
c_func
(paren
op_star
op_star
id|strptr
)paren
)paren
(brace
id|res
op_assign
(paren
id|res
op_lshift
l_int|4
)paren
op_plus
id|xpram_get_hexdigit
c_func
(paren
op_star
op_star
id|strptr
)paren
suffix:semicolon
(paren
op_star
id|strptr
)paren
op_increment
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------&n; * Read non-negative integer&n; *&n; * Argument: strptr pointer to string starting with a non-negative integer&n;             (either in decimal- or in hex-format&n; * result:   the value of the initial integer pointed to by strptr&n; *           in case of a parsing error the result is -EINVAL&n; *&n; * side effect: strptr is set to the first character following the integer&n; *-------------------------------------------------------------------------*/
r_static
r_int
DECL|function|xpram_read_int
id|xpram_read_int
(paren
r_char
op_star
op_star
id|strptr
)paren
(brace
r_switch
c_cond
(paren
id|xpram_int_format
c_func
(paren
id|strptr
)paren
)paren
(brace
r_case
id|XPRAM_INVALF
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|XPRAM_HEXF
suffix:colon
r_return
id|xpram_read_hexint
c_func
(paren
id|strptr
)paren
suffix:semicolon
r_case
id|XPRAM_DECF
suffix:colon
r_return
id|xpram_read_decint
c_func
(paren
id|strptr
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*--------------------------------------------------------------------------&n; * Read size&n; *&n; * Argument: strptr pointer to string starting with a non-negative integer&n; *           followed optionally by a size modifier:&n; *             k or K for kilo (default),&n; *             m or M for mega&n; *             g or G for giga&n; * result:   the value of the initial integer pointed to by strptr&n; *           multiplied by the modifier value devided by 1024&n; *           in case of a parsing error the result is -EINVAL&n; *&n; * side effect: strptr is set to the first character following the size&n; *-------------------------------------------------------------------------*/
r_static
r_int
DECL|function|xpram_read_size
id|xpram_read_size
(paren
r_char
op_star
op_star
id|strptr
)paren
(brace
r_int
id|res
suffix:semicolon
id|res
op_assign
id|xpram_read_int
c_func
(paren
id|strptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
r_switch
c_cond
(paren
op_star
op_star
id|strptr
)paren
(brace
r_case
l_char|&squot;g&squot;
suffix:colon
r_case
l_char|&squot;G&squot;
suffix:colon
id|res
op_assign
id|res
op_star
l_int|1024
suffix:semicolon
r_case
l_char|&squot;m&squot;
suffix:colon
r_case
l_char|&squot;M&squot;
suffix:colon
id|res
op_assign
id|res
op_star
l_int|1024
suffix:semicolon
r_case
l_char|&squot;k&squot;
suffix:colon
r_case
l_char|&squot;K&squot;
suffix:colon
(paren
op_star
id|strptr
)paren
op_increment
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------------&n; * Read tail of comma separated size list  &quot;,i1,i2,...,in&quot;&n; *&n; * Arguments:strptr pointer to string. It is assumed that the string has&n; *                  the format (&quot;,&quot;&lt;size&gt;)*&n; *           maxl integer describing the maximal number of elements in the&n;                  list pointed to by strptr, max must be &gt; 0.&n; *           ilist array of dimension &gt;= maxl of integers to be modified&n; *&n; * result:   -EINVAL if the list is longer than maxl&n; *           0 otherwise&n; *&n; * side effects: for j=1,...,n ilist[ij] is set to the value of ij if it is&n; *               a valid non-negative integer and to -EINVAL otherwise&n; *               if no comma is found where it is expected an entry in&n; *               ilist is set to -EINVAL&n; *-------------------------------------------------------------------------*/
r_static
r_int
DECL|function|xpram_read_size_list_tail
id|xpram_read_size_list_tail
(paren
r_char
op_star
op_star
id|strptr
comma
r_int
id|maxl
comma
r_int
op_star
id|ilist
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|str
op_assign
op_star
id|strptr
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|str
op_eq
l_char|&squot;,&squot;
)paren
op_logical_and
(paren
id|i
OL
id|maxl
)paren
)paren
(brace
id|str
op_increment
suffix:semicolon
id|ilist
(braket
id|i
)braket
op_assign
id|xpram_read_size
c_func
(paren
op_amp
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ilist
(braket
id|i
)braket
op_eq
op_minus
id|EINVAL
)paren
(brace
id|xpram_scan_to_next_comma
c_func
(paren
op_amp
id|str
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
macro_line|#if 0  /* be lenient about trailing stuff */
r_if
c_cond
(paren
op_star
id|str
op_ne
l_int|0
op_logical_and
op_star
id|str
op_ne
l_char|&squot; &squot;
)paren
(brace
id|ilist
(braket
id|MAX
c_func
(paren
id|i
op_minus
l_int|1
comma
l_int|0
)paren
)braket
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *   expanded memory operations&n; */
multiline_comment|/*--------------------------------------------------------------------*/
multiline_comment|/* Copy expanded memory page (4kB) into main memory                   */
multiline_comment|/* Arguments                                                          */
multiline_comment|/*           page_addr:    address of target page                     */
multiline_comment|/*           xpage_index:  index of expandeded memory page            */
multiline_comment|/* Return value                                                       */
multiline_comment|/*           0:            if operation succeeds                      */
multiline_comment|/*           non-0:       otherwise                                   */
multiline_comment|/*--------------------------------------------------------------------*/
DECL|function|xpram_page_in
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
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|real_page_addr
op_assign
id|__pa
c_func
(paren
id|page_addr
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lr  1,%1         &bslash;n&quot;
multiline_comment|/* r1 = real_page_addr            */
l_string|&quot;   lr  2,%2         &bslash;n&quot;
multiline_comment|/* r2 = xpage_index               */
l_string|&quot;   .long 0xb22e0012 &bslash;n&quot;
multiline_comment|/* pgin r1,r2                     */
multiline_comment|/* copy page from expanded memory */
l_string|&quot;0: ipm  %0          &bslash;n&quot;
multiline_comment|/* save status (cc &amp; program mask */
l_string|&quot;   srl  %0,28       &bslash;n&quot;
multiline_comment|/* cc into least significant bits */
l_string|&quot;1:                  &bslash;n&quot;
multiline_comment|/* we are done                    */
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
multiline_comment|/* start of fix up section        */
l_string|&quot;2: lhi    %0,2      &bslash;n&quot;
multiline_comment|/* return unused condition code 2 */
l_string|&quot;   bras 1,3f        &bslash;n&quot;
multiline_comment|/* safe label 1: in r1 and goto 3 */
l_string|&quot;   .long 1b         &bslash;n&quot;
multiline_comment|/* literal containing label 1     */
l_string|&quot;3: l    1,0(1)      &bslash;n&quot;
multiline_comment|/* load label 1 address into r1   */
l_string|&quot;   br   1           &bslash;n&quot;
multiline_comment|/* goto label 1 (across sections) */
l_string|&quot;.previous           &bslash;n&quot;
multiline_comment|/* back in text section           */
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
multiline_comment|/* start __extable             */
l_string|&quot;   .align 4         &bslash;n&quot;
l_string|&quot;   .long 0b,2b      &bslash;n&quot;
multiline_comment|/* failure point 0, fixup code 2  */
l_string|&quot;.previous           &bslash;n&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|real_page_addr
)paren
comma
l_string|&quot;d&quot;
(paren
id|xpage_index
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|__asm__
id|__volatile__
(paren
l_string|&quot;   lgr  1,%1        &bslash;n&quot;
multiline_comment|/* r1 = real_page_addr            */
l_string|&quot;   lgr  2,%2        &bslash;n&quot;
multiline_comment|/* r2 = xpage_index               */
l_string|&quot;   .long 0xb22e0012 &bslash;n&quot;
multiline_comment|/* pgin r1,r2                     */
multiline_comment|/* copy page from expanded memory */
l_string|&quot;0: ipm  %0          &bslash;n&quot;
multiline_comment|/* save status (cc &amp; program mask */
l_string|&quot;   srl  %0,28       &bslash;n&quot;
multiline_comment|/* cc into least significant bits */
l_string|&quot;1:                  &bslash;n&quot;
multiline_comment|/* we are done                    */
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
multiline_comment|/* start of fix up section        */
l_string|&quot;2: lghi %0,2        &bslash;n&quot;
multiline_comment|/* return unused condition code 2 */
l_string|&quot;   jg   1b          &bslash;n&quot;
multiline_comment|/* goto label 1 above             */
l_string|&quot;.previous           &bslash;n&quot;
multiline_comment|/* back in text section           */
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
multiline_comment|/* start __extable             */
l_string|&quot;   .align 8         &bslash;n&quot;
l_string|&quot;   .quad 0b,2b      &bslash;n&quot;
multiline_comment|/* failure point 0, fixup code 2  */
l_string|&quot;.previous           &bslash;n&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|real_page_addr
)paren
comma
l_string|&quot;d&quot;
(paren
id|xpage_index
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
r_switch
c_cond
(paren
id|cc
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
op_minus
id|ENXIO
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
op_minus
id|ENXIO
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* should not happen */
)brace
suffix:semicolon
)brace
multiline_comment|/*--------------------------------------------------------------------*/
multiline_comment|/* Copy a 4kB page of main memory to an expanded memory page          */
multiline_comment|/* Arguments                                                          */
multiline_comment|/*           page_addr:    address of source page                     */
multiline_comment|/*           xpage_index:  index of expandeded memory page            */
multiline_comment|/* Return value                                                       */
multiline_comment|/*           0:            if operation succeeds                      */
multiline_comment|/*           non-0:        otherwise                                  */
multiline_comment|/*--------------------------------------------------------------------*/
DECL|function|xpram_page_out
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
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|real_page_addr
op_assign
id|__pa
c_func
(paren
id|page_addr
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
id|__asm__
id|__volatile__
(paren
l_string|&quot;  lr  1,%1        &bslash;n&quot;
multiline_comment|/* r1 = mem_page                  */
l_string|&quot;  lr  2,%2        &bslash;n&quot;
multiline_comment|/* r2 = rpi                       */
l_string|&quot; .long 0xb22f0012 &bslash;n&quot;
multiline_comment|/* pgout r1,r2                    */
multiline_comment|/* copy page from expanded memory */
l_string|&quot;0: ipm  %0        &bslash;n&quot;
multiline_comment|/* save status (cc &amp; program mask */
l_string|&quot; srl  %0,28       &bslash;n&quot;
multiline_comment|/* cc into least significant bits */
l_string|&quot;1:                  &bslash;n&quot;
multiline_comment|/* we are done                    */
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
multiline_comment|/* start of fix up section        */
l_string|&quot;2: lhi   %0,2       &bslash;n&quot;
multiline_comment|/* return unused condition code 2 */
l_string|&quot;   bras 1,3f        &bslash;n&quot;
multiline_comment|/* safe label 1: in r1 and goto 3 */
l_string|&quot;   .long 1b         &bslash;n&quot;
multiline_comment|/* literal containing label 1     */
l_string|&quot;3: l    1,0(1)      &bslash;n&quot;
multiline_comment|/* load label 1 address into r1   */
l_string|&quot;   br   1           &bslash;n&quot;
multiline_comment|/* goto label 1 (across sections) */
l_string|&quot;.previous           &bslash;n&quot;
multiline_comment|/* back in text section           */
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
multiline_comment|/* start __extable             */
l_string|&quot;   .align 4         &bslash;n&quot;
l_string|&quot;   .long 0b,2b      &bslash;n&quot;
multiline_comment|/* failure point 0, fixup code 2  */
l_string|&quot;.previous           &bslash;n&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|real_page_addr
)paren
comma
l_string|&quot;d&quot;
(paren
id|xpage_index
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|__asm__
id|__volatile__
(paren
l_string|&quot;  lgr  1,%1       &bslash;n&quot;
multiline_comment|/* r1 = mem_page                  */
l_string|&quot;  lgr  2,%2       &bslash;n&quot;
multiline_comment|/* r2 = rpi                       */
l_string|&quot; .long 0xb22f0012 &bslash;n&quot;
multiline_comment|/* pgout r1,r2                    */
multiline_comment|/* copy page from expanded memory */
l_string|&quot;0: ipm  %0        &bslash;n&quot;
multiline_comment|/* save status (cc &amp; program mask */
l_string|&quot;  srl  %0,28      &bslash;n&quot;
multiline_comment|/* cc into least significant bits */
l_string|&quot;1:                &bslash;n&quot;
multiline_comment|/* we are done                    */
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
multiline_comment|/* start of fix up section      */
l_string|&quot;2: lghi %0,2      &bslash;n&quot;
multiline_comment|/* return unused condition code 2 */
l_string|&quot;   jg   1b        &bslash;n&quot;
multiline_comment|/* goto label 1 above             */
l_string|&quot;.previous         &bslash;n&quot;
multiline_comment|/* back in text section           */
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
multiline_comment|/* start __extable           */
l_string|&quot;   .align 8       &bslash;n&quot;
l_string|&quot;   .quad 0b,2b    &bslash;n&quot;
multiline_comment|/* failure point 0, fixup code 2  */
l_string|&quot;.previous         &bslash;n&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|real_page_addr
)paren
comma
l_string|&quot;d&quot;
(paren
id|xpage_index
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_ARCH_S390X */
r_switch
c_cond
(paren
id|cc
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
r_case
l_int|2
suffix:colon
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
r_case
l_int|3
suffix:colon
r_return
op_minus
id|ENXIO
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* should not happen */
)brace
)brace
multiline_comment|/*--------------------------------------------------------------------*/
multiline_comment|/* Measure expanded memory                                            */
multiline_comment|/* Return value                                                       */
multiline_comment|/*           size of expanded memory in kB (must be a multipe of 4)   */
multiline_comment|/*--------------------------------------------------------------------*/
DECL|function|xpram_size
r_int
id|xpram_size
c_func
(paren
r_void
)paren
(brace
r_int
id|cc
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|base
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|po
comma
id|pi
comma
id|rpi
suffix:semicolon
multiline_comment|/* page index order, page index */
r_int
r_int
id|mem_page
op_assign
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* for po=0,1,2,... try to move in page number base+(2^po)-1 */
id|pi
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|po
op_assign
l_int|0
suffix:semicolon
id|po
op_le
l_int|32
suffix:semicolon
id|po
op_increment
)paren
(brace
multiline_comment|/* pi = 2^po */
id|cc
op_assign
id|xpram_page_in
c_func
(paren
id|mem_page
comma
id|base
op_plus
id|pi
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cc
)paren
r_break
suffix:semicolon
id|pi
op_lshift_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cc
op_logical_and
(paren
id|po
OL
l_int|31
)paren
)paren
(brace
id|pi
op_rshift_assign
l_int|1
suffix:semicolon
id|base
op_add_assign
id|pi
suffix:semicolon
id|pi
op_rshift_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|pi
OG
l_int|0
suffix:semicolon
id|pi
op_rshift_assign
l_int|1
)paren
(brace
id|rpi
op_assign
id|pi
op_minus
l_int|1
suffix:semicolon
id|cc
op_assign
id|xpram_page_in
c_func
(paren
id|mem_page
comma
id|base
op_plus
id|rpi
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cc
)paren
id|base
op_add_assign
id|pi
suffix:semicolon
)brace
)brace
id|free_page
(paren
id|mem_page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cc
op_logical_and
(paren
id|po
OL
l_int|31
)paren
)paren
r_return
(paren
id|XPRAM_KB_IN_PG
op_star
id|base
)paren
suffix:semicolon
r_else
multiline_comment|/* return maximal value possible */
r_return
id|INT_MAX
suffix:semicolon
)brace
multiline_comment|/*&n; * Open and close&n; */
DECL|function|xpram_open
r_int
id|xpram_open
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
id|Xpram_Dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* device information */
r_int
id|num
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num
op_ge
id|xpram_devs
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dev
op_assign
id|xpram_devices
op_plus
id|num
suffix:semicolon
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;calling xpram_open for device %d&bslash;n&quot;
comma
id|num
)paren
suffix:semicolon
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;  size %dkB, name %s, usage: %d&bslash;n&quot;
comma
id|dev-&gt;size
comma
id|dev-&gt;device_name
comma
id|atomic_read
c_func
(paren
op_amp
(paren
id|dev-&gt;usage
)paren
)paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
(paren
id|dev-&gt;usage
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* success */
)brace
DECL|function|xpram_release
r_int
id|xpram_release
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
id|Xpram_Dev
op_star
id|dev
op_assign
id|xpram_devices
op_plus
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;calling xpram_release for device %d (size %dkB, usage: %d)&bslash;n&quot;
comma
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
comma
id|dev-&gt;size
comma
id|atomic_read
c_func
(paren
op_amp
(paren
id|dev-&gt;usage
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the device is closed for the last time, start a timer&n;&t; * to release RAM in half a minute. The function and argument&n;&t; * for the timer have been setup in init_module()&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|atomic_dec_return
c_func
(paren
op_amp
(paren
id|dev-&gt;usage
)paren
)paren
)paren
(brace
multiline_comment|/* but flush it right now */
multiline_comment|/* Everything is already flushed by caller -- AV */
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The ioctl() implementation&n; */
DECL|function|xpram_ioctl
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
r_int
id|err
comma
id|size
suffix:semicolon
r_struct
id|hd_geometry
op_star
id|geo
op_assign
(paren
r_struct
id|hd_geometry
op_star
)paren
id|arg
suffix:semicolon
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;ioctl 0x%x 0x%lx&bslash;n&quot;
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BLKGETSIZE
suffix:colon
multiline_comment|/* 0x1260 */
multiline_comment|/* Return the device size, expressed in sectors */
r_return
id|put_user
c_func
(paren
l_int|1024
op_star
id|xpram_sizes
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
op_div
id|XPRAM_SOFTSECT
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|BLKGETSIZE64
suffix:colon
r_return
id|put_user
c_func
(paren
(paren
id|u64
)paren
(paren
l_int|1024
op_star
id|xpram_sizes
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
op_div
id|XPRAM_SOFTSECT
)paren
op_lshift
l_int|9
comma
(paren
id|u64
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|BLKFLSBUF
suffix:colon
multiline_comment|/* flush, 0x1261 */
id|fsync_bdev
c_func
(paren
id|inode-&gt;i_bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
id|invalidate_bdev
c_func
(paren
id|inode-&gt;i_bdev
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|BLKRRPART
suffix:colon
multiline_comment|/* re-read partition table: can&squot;t do it, 0x1259 */
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#if (XPRAM_VERSION == 22)
id|RO_IOCTLS
c_func
(paren
id|inode-&gt;i_rdev
comma
id|arg
)paren
suffix:semicolon
multiline_comment|/* the default RO operations &n;                                                * BLKROSET&n;&t;&t;&t;&t;&t;&t;* BLKROGET&n;                                                */
macro_line|#endif /* V22 */
r_case
id|HDIO_GETGEO
suffix:colon
multiline_comment|/*&n;&t;&t; * get geometry: we have to fake one...  trim the size to a&n;&t;&t; * multiple of 64 (32k): tell we have 16 sectors, 4 heads,&n;&t;&t; * whatever cylinders. Tell also that data starts at sector. 4.&n;&t;&t; */
id|size
op_assign
id|xpram_mem_avail
op_star
l_int|1024
op_div
id|XPRAM_SOFTSECT
suffix:semicolon
multiline_comment|/* size = xpram_mem_avail * 1024 / xpram_hardsect; */
id|size
op_and_assign
op_complement
l_int|0x3f
suffix:semicolon
multiline_comment|/* multiple of 64 */
r_if
c_cond
(paren
id|geo
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* &n;                 * err=verify_area_20(VERIFY_WRITE, geo, sizeof(*geo));&n;&t;&t; * if (err) return err;&n;                 */
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
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* unknown command */
)brace
multiline_comment|/*&n; * The file operations&n; */
macro_line|#if (XPRAM_VERSION == 22)
DECL|variable|xpram_fops
r_struct
id|file_operations
id|xpram_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek: default */
id|block_read
comma
id|block_write
comma
l_int|NULL
comma
multiline_comment|/* xpram_readdir */
l_int|NULL
comma
multiline_comment|/* xpram_select */
id|xpram_ioctl
comma
l_int|NULL
comma
multiline_comment|/* xpram_mmap */
id|xpram_open
comma
l_int|NULL
comma
multiline_comment|/* flush */
id|xpram_release
comma
id|block_fsync
comma
l_int|NULL
comma
multiline_comment|/* xpram_fasync */
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
macro_line|#endif /* V22 */
macro_line|#if (XPRAM_VERSION == 24)
DECL|variable|xpram_devops
r_struct
id|block_device_operations
id|xpram_devops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|ioctl
suffix:colon
id|xpram_ioctl
comma
id|open
suffix:colon
id|xpram_open
comma
id|release
suffix:colon
id|xpram_release
comma
)brace
suffix:semicolon
macro_line|#endif /* V24 */
multiline_comment|/*&n; * Block-driver specific functions&n; */
DECL|function|xpram_request
r_void
id|xpram_request
c_func
(paren
id|request_queue_t
op_star
id|queue
)paren
(brace
id|Xpram_Dev
op_star
id|device
suffix:semicolon
multiline_comment|/*     u8 *ptr;          */
multiline_comment|/*    int size;          */
r_int
r_int
id|page_no
suffix:semicolon
multiline_comment|/* expanded memory page number */
r_int
r_int
id|sects_to_copy
suffix:semicolon
multiline_comment|/* number of sectors to be copied */
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* local pointer into buffer cache */
r_int
id|dev_no
suffix:semicolon
multiline_comment|/* device number of request */
r_int
id|fault
suffix:semicolon
multiline_comment|/* faulty access to expanded memory */
macro_line|#if ( XPRAM_VERSION == 24 )&t;
r_struct
id|request
op_star
id|current_req
suffix:semicolon
multiline_comment|/* working request */
macro_line|#else 
macro_line|#       define current_req CURRENT
macro_line|#endif /* V24 */
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|INIT_REQUEST
suffix:semicolon
id|fault
op_assign
l_int|0
suffix:semicolon
macro_line|#if ( XPRAM_VERSION == 24 )
id|current_req
op_assign
id|CURRENT
suffix:semicolon
macro_line|#endif /* V24 */
id|dev_no
op_assign
id|DEVICE_NR
c_func
(paren
id|current_req-&gt;rq_dev
)paren
suffix:semicolon
multiline_comment|/* Check if the minor number is in range */
r_if
c_cond
(paren
id|dev_no
OG
id|xpram_devs
)paren
(brace
r_static
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_increment
OL
l_int|5
)paren
multiline_comment|/* print the message at most five times */
id|PRINT_WARN
c_func
(paren
l_string|&quot; request for unknown device&bslash;n&quot;
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* pointer to device structure, from the global array */
id|device
op_assign
id|xpram_devices
op_plus
id|dev_no
suffix:semicolon
id|sects_to_copy
op_assign
id|current_req-&gt;current_nr_sectors
suffix:semicolon
multiline_comment|/* does request exceed size of device ? */
r_if
c_cond
(paren
id|XPRAM_SEC2KB
c_func
(paren
id|sects_to_copy
)paren
OG
id|xpram_sizes
(braket
id|dev_no
)braket
)paren
(brace
id|PRINT_WARN
c_func
(paren
l_string|&quot; request past end of device&bslash;n&quot;
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Does request start at page boundery? -- paranoia */
macro_line|#if 0
id|PRINT_DEBUG
c_func
(paren
l_string|&quot; req %lx, sect %lx, to copy %lx, buf addr %lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|current_req
comma
id|current_req-&gt;sector
comma
id|sects_to_copy
comma
(paren
r_int
r_int
)paren
id|current_req-&gt;buffer
)paren
suffix:semicolon
macro_line|#endif
id|buffer
op_assign
id|current_req-&gt;buffer
suffix:semicolon
macro_line|#if XPRAM_SEC_IN_PG != 1
multiline_comment|/* Does request start at an expanded storage page boundery? */
r_if
c_cond
(paren
id|current_req-&gt;sector
op_amp
(paren
id|XPRAM_SEC_IN_PG
op_minus
l_int|1
)paren
)paren
(brace
id|PRINT_WARN
c_func
(paren
l_string|&quot; request does not start at an expanded storage page boundery&bslash;n&quot;
)paren
suffix:semicolon
id|PRINT_WARN
c_func
(paren
l_string|&quot; referenced sector: %ld&bslash;n&quot;
comma
id|current_req-&gt;sector
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Does request refere to partial expanded storage pages? */
r_if
c_cond
(paren
id|sects_to_copy
op_amp
(paren
id|XPRAM_SEC_IN_PG
op_minus
l_int|1
)paren
)paren
(brace
id|PRINT_WARN
c_func
(paren
l_string|&quot; request referes to a partial expanded storage page&bslash;n&quot;
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif /*  XPRAM_SEC_IN_PG != 1 */
multiline_comment|/* Is request buffer aligned with kernel pages? */
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|buffer
)paren
op_amp
(paren
id|XPRAM_PGSIZE
op_minus
l_int|1
)paren
)paren
(brace
id|PRINT_WARN
c_func
(paren
l_string|&quot; request buffer is not aligned with kernel pages&bslash;n&quot;
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* which page of expanded storage is affected first? */
id|page_no
op_assign
(paren
id|xpram_offsets
(braket
id|dev_no
)braket
op_rshift
id|XPRAM_KB_IN_PG_ORDER
)paren
op_plus
(paren
id|current_req-&gt;sector
op_rshift
id|XPRAM_SEC_IN_PG_ORDER
)paren
suffix:semicolon
macro_line|#if 0 
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;request: %d ( dev %d, copy %d sectors, at page %d ) &bslash;n&quot;
comma
id|current_req-&gt;cmd
comma
id|dev_no
comma
id|sects_to_copy
comma
id|page_no
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|current_req-&gt;cmd
)paren
(brace
r_case
id|READ
suffix:colon
r_do
(brace
r_if
c_cond
(paren
(paren
id|fault
op_assign
id|xpram_page_in
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer
comma
id|page_no
)paren
)paren
)paren
(brace
id|PRINT_WARN
c_func
(paren
l_string|&quot;xpram(dev %d): page in failed for page %ld.&bslash;n&quot;
comma
id|dev_no
comma
id|page_no
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sects_to_copy
op_sub_assign
id|XPRAM_SEC_IN_PG
suffix:semicolon
id|buffer
op_add_assign
id|XPRAM_PGSIZE
suffix:semicolon
id|page_no
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sects_to_copy
OG
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE
suffix:colon
r_do
(brace
r_if
c_cond
(paren
(paren
id|fault
op_assign
id|xpram_page_out
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer
comma
id|page_no
)paren
)paren
)paren
(brace
id|PRINT_WARN
c_func
(paren
l_string|&quot;xpram(dev %d): page out failed for page %ld.&bslash;n&quot;
comma
id|dev_no
comma
id|page_no
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sects_to_copy
op_sub_assign
id|XPRAM_SEC_IN_PG
suffix:semicolon
id|buffer
op_add_assign
id|XPRAM_PGSIZE
suffix:semicolon
id|page_no
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sects_to_copy
OG
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* can&squot;t happen */
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fault
)paren
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_else
id|end_request
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* success */
)brace
)brace
multiline_comment|/*&n; *    Kernel interfaces&n; */
multiline_comment|/*&n; * Parses the kernel parameters given in the kernel parameter line.&n; * The expected format is &n; *           &lt;number_of_partitions&gt;[&quot;,&quot;&lt;partition_size&gt;]*&n; * where &n; *           devices is a positive integer that initializes xpram_devs&n; *           each size is a non-negative integer possibly followed by a&n; *           magnitude (k,K,m,M,g,G), the list of sizes initialises &n; *           xpram_sizes&n; *&n; * Arguments&n; *           str: substring of kernel parameter line that contains xprams&n; *                kernel parameters. &n; *           ints: not used -- not in Version &gt; 2.3 any more&n; *&n; * Result    0 on success, -EINVAl else -- only for Version &gt; 2.3&n; *&n; * Side effects&n; *           the global variabls devs is set to the value of &n; *           &lt;number_of_partitions&gt; and sizes[i] is set to the i-th&n; *           partition size (if provided). A parsing error of a value&n; *           results in this value being set to -EINVAL.&n; */
macro_line|#if (XPRAM_VERSION == 22)
DECL|function|xpram_setup
r_void
id|xpram_setup
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
macro_line|#else 
r_int
id|xpram_setup
(paren
r_char
op_star
id|str
)paren
macro_line|#endif /* V22 */
(brace
id|devs
op_assign
id|xpram_read_int
c_func
(paren
op_amp
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devs
op_ne
op_minus
id|EINVAL
)paren
r_if
c_cond
(paren
id|xpram_read_size_list_tail
c_func
(paren
op_amp
id|str
comma
id|devs
comma
id|sizes
)paren
OL
l_int|0
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;error while reading xpram parameters.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if (XPRAM_VERSION == 24)
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif /* V24 */
)brace
macro_line|#if (XPRAM_VERSION == 24)
r_else
r_return
l_int|0
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#elif (XPRAM_VERSION == 22)
r_return
suffix:semicolon
macro_line|#endif /* V24/V22 */
)brace
multiline_comment|/*&n; * initialize xpram device driver&n; *&n; * Result: 0 ok&n; *         negative number: negative error code&n; */
DECL|function|xpram_init
r_int
id|xpram_init
c_func
(paren
r_void
)paren
(brace
r_int
id|result
comma
id|i
suffix:semicolon
r_int
id|mem_usable
suffix:semicolon
multiline_comment|/* net size of expanded memory */
r_int
id|mem_needed
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* size of expanded memory needed to fullfill&n;&t;&t;&t;       * requirements of non-zero parameters in sizes&n;&t;&t;&t;       */
r_int
id|mem_auto_no
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* number of (implicit) zero parameters in sizes */
r_int
id|mem_auto
suffix:semicolon
multiline_comment|/* automatically determined device size          */
macro_line|#if (XPRAM_VERSION == 24)
r_int
id|minor_length
suffix:semicolon
multiline_comment|/* store the length of a minor (w/o &squot;&bslash;0&squot;) */
r_int
id|minor_thresh
suffix:semicolon
multiline_comment|/* threshhold for minor lenght            */
id|request_queue_t
op_star
id|q
suffix:semicolon
multiline_comment|/* request queue */
macro_line|#endif /* V24 */
multiline_comment|/*&n;&t;&t;&t;&t; * Copy the (static) cfg variables to public prefixed ones to allow&n;&t;&t;&t;&t; * snoozing with a debugger.&n;&t;&t;&t;&t; */
id|xpram_blksize
op_assign
id|blksize
suffix:semicolon
id|xpram_hardsect
op_assign
id|hardsect
suffix:semicolon
id|PRINT_INFO
c_func
(paren
l_string|&quot;initializing: %s&bslash;n&quot;
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
multiline_comment|/* check arguments */
id|xpram_major
op_assign
id|major
suffix:semicolon
r_if
c_cond
(paren
(paren
id|devs
op_le
l_int|0
)paren
op_logical_or
(paren
id|devs
OG
id|XPRAM_MAX_DEVS
)paren
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
id|PRINT_ERR
c_func
(paren
l_string|&quot;Giving up xpram&bslash;n&quot;
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
id|sizes
(braket
id|i
)braket
OL
l_int|0
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;Invalid partition size %d kB&bslash;n&quot;
comma
id|xpram_sizes
(braket
id|i
)braket
)paren
suffix:semicolon
id|PRINT_ERR
c_func
(paren
l_string|&quot;Giving up xpram&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
id|xpram_sizes
(braket
id|i
)braket
op_assign
id|NEXT4
c_func
(paren
id|sizes
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* page align */
r_if
c_cond
(paren
id|sizes
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
)brace
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;  major %d &bslash;n&quot;
comma
id|xpram_major
)paren
suffix:semicolon
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
id|sizes
(braket
id|i
)braket
)paren
id|PRINT_INFO
c_func
(paren
l_string|&quot;  size of partition %d: %d kB&bslash;n&quot;
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
l_string|&quot;  size of partition %d to be set automatically&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;  memory needed (for sized partitions): %d kB&bslash;n&quot;
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
macro_line|#if 0
multiline_comment|/* Hardsect can&squot;t be changed :( */
multiline_comment|/* I try it any way. Yet I must distinguish&n;                                 * between hardsects (to be changed to 4096)&n;                                 * and soft sectors, hard-coded for buffer &n;                                 * sizes within the requests&n;                                 */
r_if
c_cond
(paren
id|hardsect
op_ne
l_int|512
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;Can&squot;t change hardsect size&bslash;n&quot;
)paren
suffix:semicolon
id|hardsect
op_assign
id|xpram_hardsect
op_assign
l_int|512
suffix:semicolon
)brace
macro_line|#endif
id|PRINT_INFO
c_func
(paren
l_string|&quot;  hardsector size: %dB &bslash;n&quot;
comma
id|xpram_hardsect
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Register your major, and accept a dynamic number&n;&t; */
macro_line|#if (XPRAM_VERSION == 22)
id|result
op_assign
id|register_blkdev
c_func
(paren
id|xpram_major
comma
l_string|&quot;xpram&quot;
comma
op_amp
id|xpram_fops
)paren
suffix:semicolon
macro_line|#elif (XPRAM_VERSION == 24)
id|result
op_assign
id|devfs_register_blkdev
c_func
(paren
id|xpram_major
comma
l_string|&quot;xpram&quot;
comma
op_amp
id|xpram_devops
)paren
suffix:semicolon
macro_line|#endif /* V22/V24 */
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;Can&squot;t get major %d&bslash;n&quot;
comma
id|xpram_major
)paren
suffix:semicolon
id|PRINT_ERR
c_func
(paren
l_string|&quot;Giving up xpram&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#if (XPRAM_VERSION == 24)
id|xpram_devfs_handle
op_assign
id|devfs_mk_dir
(paren
l_int|NULL
comma
l_string|&quot;slram&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|devfs_register_series
(paren
id|xpram_devfs_handle
comma
l_string|&quot;%u&quot;
comma
id|XPRAM_MAX_DEVS
comma
id|DEVFS_FL_DEFAULT
comma
id|XPRAM_MAJOR
comma
l_int|0
comma
id|S_IFBLK
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|xpram_devops
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif /* V22/V24 */
r_if
c_cond
(paren
id|xpram_major
op_eq
l_int|0
)paren
id|xpram_major
op_assign
id|result
suffix:semicolon
multiline_comment|/* dynamic */
id|major
op_assign
id|xpram_major
suffix:semicolon
multiline_comment|/* Use `major&squot; later on to save typing */
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* for the possible errors */
multiline_comment|/* &n;&t; * measure expanded memory&n;&t; */
id|xpram_mem_avail
op_assign
id|xpram_size
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xpram_mem_avail
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;No or not enough expanded memory available&bslash;n&quot;
)paren
suffix:semicolon
id|PRINT_ERR
c_func
(paren
l_string|&quot;Giving up xpram&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|fail_malloc
suffix:semicolon
)brace
id|PRINT_INFO
c_func
(paren
l_string|&quot;  %d kB expanded memory found.&bslash;n&quot;
comma
id|xpram_mem_avail
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Assign the other needed values: request, size, blksize,&n;&t; * hardsect. All the minor devices feature the same value.&n;&t; * Note that `xpram&squot; defines all of them to allow testing non-default&n;&t; * values. A real device could well avoid setting values in global&n;&t; * arrays if it uses the default values.&n;&t; */
macro_line|#if (XPRAM_VERSION == 22)
id|blk_dev
(braket
id|major
)braket
dot
id|request_fn
op_assign
id|xpram_request
suffix:semicolon
macro_line|#elif (XPRAM_VERSION == 24)
id|q
op_assign
id|BLK_DEFAULT_QUEUE
(paren
id|major
)paren
suffix:semicolon
id|blk_init_queue
(paren
id|q
comma
id|xpram_request
)paren
suffix:semicolon
id|blk_queue_hardsect_size
c_func
(paren
id|q
comma
id|xpram_hardsect
)paren
suffix:semicolon
macro_line|#endif /* V22/V24 */
multiline_comment|/* we want to have XPRAM_UNUSED blocks security buffer between devices */
id|mem_usable
op_assign
id|xpram_mem_avail
op_minus
(paren
id|XPRAM_UNUSED
op_star
(paren
id|xpram_devs
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_needed
OG
id|mem_usable
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;Not enough expanded memory available&bslash;n&quot;
)paren
suffix:semicolon
id|PRINT_ERR
c_func
(paren
l_string|&quot;Giving up xpram&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_malloc
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * partitioning:&n;&t; * xpram_sizes[i] != 0; partition i has size xpram_sizes[i] kB&n;&t; * else:             ; all partitions i with xpram_sizesxpram_size[i] &n;&t; *                     partition equally the remaining space&n;&t; */
r_if
c_cond
(paren
id|mem_auto_no
)paren
(brace
id|mem_auto
op_assign
id|LAST4
c_func
(paren
(paren
id|mem_usable
op_minus
id|mem_needed
)paren
op_div
id|mem_auto_no
)paren
suffix:semicolon
id|PRINT_INFO
c_func
(paren
l_string|&quot;  automatically determined partition size: %d kB&bslash;n&quot;
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
id|blk_size
(braket
id|major
)braket
op_assign
id|xpram_sizes
suffix:semicolon
id|xpram_offsets
op_assign
id|kmalloc
c_func
(paren
id|xpram_devs
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xpram_offsets
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;Not enough memory for xpram_offsets&bslash;n&quot;
)paren
suffix:semicolon
id|PRINT_ERR
c_func
(paren
l_string|&quot;Giving up xpram&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_malloc
suffix:semicolon
)brace
id|xpram_offsets
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|xpram_devs
suffix:semicolon
id|i
op_increment
)paren
id|xpram_offsets
(braket
id|i
)braket
op_assign
id|xpram_offsets
(braket
id|i
op_minus
l_int|1
)braket
op_plus
id|xpram_sizes
(braket
id|i
op_minus
l_int|1
)braket
op_plus
id|XPRAM_UNUSED
suffix:semicolon
macro_line|#if 0
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
id|PRINT_DEBUG
c_func
(paren
l_string|&quot; device(%d) offset = %d kB, size = %d kB&bslash;n&quot;
comma
id|i
comma
id|xpram_offsets
(braket
id|i
)braket
comma
id|xpram_sizes
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
id|xpram_blksizes
op_assign
id|kmalloc
c_func
(paren
id|xpram_devs
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xpram_blksizes
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;Not enough memory for xpram_blksizes&bslash;n&quot;
)paren
suffix:semicolon
id|PRINT_ERR
c_func
(paren
l_string|&quot;Giving up xpram&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_malloc_blksizes
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
id|xpram_devs
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* all the same blocksize */
id|xpram_blksizes
(braket
id|i
)braket
op_assign
id|xpram_blksize
suffix:semicolon
id|blksize_size
(braket
id|major
)braket
op_assign
id|xpram_blksizes
suffix:semicolon
multiline_comment|/* &n;&t; * allocate the devices -- we can&squot;t have them static, as the number&n;&t; * can be specified at load time&n;&t; */
id|xpram_devices
op_assign
id|kmalloc
c_func
(paren
id|xpram_devs
op_star
r_sizeof
(paren
id|Xpram_Dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xpram_devices
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;Not enough memory for xpram_devices&bslash;n&quot;
)paren
suffix:semicolon
id|PRINT_ERR
c_func
(paren
l_string|&quot;Giving up xpram&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_malloc_devices
suffix:semicolon
)brace
id|memset
c_func
(paren
id|xpram_devices
comma
l_int|0
comma
id|xpram_devs
op_star
r_sizeof
(paren
id|Xpram_Dev
)paren
)paren
suffix:semicolon
macro_line|#if (XPRAM_VERSION == 24)
id|minor_length
op_assign
l_int|1
suffix:semicolon
id|minor_thresh
op_assign
l_int|10
suffix:semicolon
macro_line|#endif /* V24 */
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
multiline_comment|/* data and usage remain zeroed */
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
suffix:semicolon
multiline_comment|/* size in kB not in bytes */
id|atomic_set
c_func
(paren
op_amp
(paren
id|xpram_devices
(braket
id|i
)braket
dot
id|usage
)paren
comma
l_int|0
)paren
suffix:semicolon
macro_line|#if (XPRAM_VERSION == 24)
r_if
c_cond
(paren
id|i
op_eq
id|minor_thresh
)paren
(brace
id|minor_length
op_increment
suffix:semicolon
id|minor_thresh
op_mul_assign
l_int|10
suffix:semicolon
)brace
id|xpram_devices
(braket
id|i
)braket
dot
id|device_name
op_assign
id|kmalloc
c_func
(paren
l_int|1
op_plus
id|strlen
c_func
(paren
id|XPRAM_DEVICE_NAME_PREFIX
)paren
op_plus
id|minor_length
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xpram_devices
(braket
id|i
)braket
dot
id|device_name
op_eq
l_int|NULL
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;Not enough memory for xpram_devices[%d].device_name&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|PRINT_ERR
c_func
(paren
l_string|&quot;Giving up xpram&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_devfs_register
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|xpram_devices
(braket
id|i
)braket
dot
id|device_name
comma
id|XPRAM_DEVICE_NAME_PREFIX
l_string|&quot;%d&quot;
comma
id|i
)paren
suffix:semicolon
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;initializing xpram_open for device %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;  size %dkB, name %s, usage: %d&bslash;n&quot;
comma
id|xpram_devices
(braket
id|i
)braket
dot
id|size
comma
id|xpram_devices
(braket
id|i
)braket
dot
id|device_name
comma
id|atomic_read
c_func
(paren
op_amp
(paren
id|xpram_devices
(braket
id|i
)braket
dot
id|usage
)paren
)paren
)paren
suffix:semicolon
macro_line|#if 0  /* WHY? */
id|xpram_devices
(braket
id|i
)braket
dot
id|devfs_entry
op_assign
id|devfs_register
c_func
(paren
l_int|NULL
multiline_comment|/* devfs root dir */
comma
id|xpram_devices
(braket
id|i
)braket
dot
id|device_name
comma
l_int|0
comma
l_int|0
multiline_comment|/* flags */
comma
id|XPRAM_MAJOR
comma
id|i
comma
l_int|0755
multiline_comment|/* access mode */
comma
l_int|0
multiline_comment|/* uid */
comma
l_int|0
multiline_comment|/* gid */
comma
op_amp
id|xpram_devops
comma
(paren
r_void
op_star
)paren
op_amp
(paren
id|xpram_devices
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xpram_devices
(braket
id|i
)braket
dot
id|devfs_entry
op_eq
l_int|NULL
)paren
(brace
id|PRINT_ERR
c_func
(paren
l_string|&quot;devfs system registry failed&bslash;n&quot;
)paren
suffix:semicolon
id|PRINT_ERR
c_func
(paren
l_string|&quot;Giving up xpram&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_devfs_register
suffix:semicolon
)brace
macro_line|#endif  /* WHY? */
macro_line|#endif /* V24 */
)brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* succeed */
multiline_comment|/* clean up memory in case of failures */
macro_line|#if (XPRAM_VERSION == 24)
id|fail_devfs_register
suffix:colon
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
id|xpram_devices
(braket
id|i
)braket
dot
id|device_name
)paren
id|kfree
c_func
(paren
id|xpram_devices
(braket
id|i
)braket
dot
id|device_name
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|xpram_devices
)paren
suffix:semicolon
macro_line|#endif /* V24 */
id|fail_malloc_blksizes
suffix:colon
id|kfree
(paren
id|xpram_offsets
)paren
suffix:semicolon
id|kfree
(paren
id|xpram_blksizes
)paren
suffix:semicolon
id|blksize_size
(braket
id|major
)braket
op_assign
l_int|NULL
suffix:semicolon
id|fail_malloc_devices
suffix:colon
id|fail_malloc
suffix:colon
macro_line|#if (XPRAM_VERSION == 22)
id|blk_dev
(braket
id|major
)braket
dot
id|request_fn
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif /* V22 */
multiline_comment|/* ???&t;unregister_chrdev(major, &quot;xpram&quot;); */
id|unregister_blkdev
c_func
(paren
id|major
comma
l_string|&quot;xpram&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Finally, the module stuff&n; */
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|PRINT_INFO
(paren
l_string|&quot;trying to load module&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
id|xpram_init
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|PRINT_INFO
(paren
l_string|&quot;Module loaded successfully&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|PRINT_WARN
(paren
l_string|&quot;Module load returned rc=%d&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* first of all, reset all the data structures */
macro_line|#if (XPRAM_VERSION == 22)
id|blk_dev
(braket
id|major
)braket
dot
id|request_fn
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif /* V22 */
id|kfree
c_func
(paren
id|blksize_size
(braket
id|major
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|xpram_offsets
)paren
suffix:semicolon
id|blk_clear
c_func
(paren
id|major
)paren
suffix:semicolon
multiline_comment|/* finally, the usual cleanup */
macro_line|#if (XPRAM_VERSION == 22)
id|unregister_blkdev
c_func
(paren
id|major
comma
l_string|&quot;xpram&quot;
)paren
suffix:semicolon
macro_line|#elif (XPRAM_VERSION == 24)
id|devfs_unregister
c_func
(paren
id|xpram_devfs_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devfs_unregister_blkdev
c_func
(paren
id|MAJOR_NR
comma
l_string|&quot;xpram&quot;
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;xpram: cannot unregister blkdev&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* V22/V24 */
id|kfree
c_func
(paren
id|xpram_devices
)paren
suffix:semicolon
)brace
eof
