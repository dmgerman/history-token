multiline_comment|/*&n; * xpram.h -- definitions for the char module&n; *&n; *********/
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/major.h&gt;
multiline_comment|/* version dependencies have been confined to a separate file */
multiline_comment|/*&n; * Macros to help debugging&n; */
DECL|macro|XPRAM_NAME
mdefine_line|#define XPRAM_NAME &quot;xpram&quot;  /* name of device/module */
DECL|macro|XPRAM_DEVICE_NAME_PREFIX
mdefine_line|#define XPRAM_DEVICE_NAME_PREFIX &quot;slram&quot; /* Prefix device name for major 35 */
DECL|macro|XPRAM_DEVS
mdefine_line|#define XPRAM_DEVS 1        /* one partition */
DECL|macro|XPRAM_RAHEAD
mdefine_line|#define XPRAM_RAHEAD 8      /* no real read ahead */
DECL|macro|XPRAM_PGSIZE
mdefine_line|#define XPRAM_PGSIZE 4096   /* page size of (expanded) mememory pages&n;                             * according to S/390 architecture&n;                             */
DECL|macro|XPRAM_BLKSIZE
mdefine_line|#define XPRAM_BLKSIZE XPRAM_PGSIZE  /* must be equalt to page size ! */
DECL|macro|XPRAM_HARDSECT
mdefine_line|#define XPRAM_HARDSECT XPRAM_PGSIZE /* FIXME -- we have to deal with both&n;                                     * this hard sect size and in some cases&n;                                     * hard coded 512 bytes which I call&n;                                     * soft sects:&n;                                     */
DECL|macro|XPRAM_SOFTSECT
mdefine_line|#define XPRAM_SOFTSECT 512
DECL|macro|XPRAM_MAX_DEVS
mdefine_line|#define XPRAM_MAX_DEVS 32   /* maximal number of devices (partitions) */
DECL|macro|XPRAM_MAX_DEVS1
mdefine_line|#define XPRAM_MAX_DEVS1 33  /* maximal number of devices (partitions) +1 */
multiline_comment|/* The following macros depend on the sizes above */
DECL|macro|XPRAM_KB_IN_PG
mdefine_line|#define XPRAM_KB_IN_PG 4                     /* 4 kBs per page */
DECL|macro|XPRAM_KB_IN_PG_ORDER
mdefine_line|#define XPRAM_KB_IN_PG_ORDER 2               /* 2^? kBs per page */
multiline_comment|/* Eventhough XPRAM_HARDSECT is set to 4k some data structures use hard&n; * coded 512 byte sa sector size&n; */
DECL|macro|XPRAM_SEC2KB
mdefine_line|#define XPRAM_SEC2KB(x) ((x &gt;&gt; 1) + (x &amp; 1)) /* modifier used to compute size &n;                                                in kB from number of sectors */
DECL|macro|XPRAM_SEC_IN_PG
mdefine_line|#define XPRAM_SEC_IN_PG 8                    /* 8 sectors per page */
DECL|macro|XPRAM_SEC_IN_PG_ORDER
mdefine_line|#define XPRAM_SEC_IN_PG_ORDER 3              /* 2^? sectors per page */
DECL|macro|XPRAM_UNUSED
mdefine_line|#define XPRAM_UNUSED 40                     /* unused space between devices, &n;                                             * in kB, i.e.&n;                                             * must be a multiple of 4&n;                                             */
multiline_comment|/*&n; * The xpram device is removable: if it is left closed for more than&n; * half a minute, it is removed. Thus use a usage count and a&n; * kernel timer&n; */
DECL|struct|Xpram_Dev
r_typedef
r_struct
id|Xpram_Dev
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size in KB not in Byte - RB - */
DECL|member|usage
id|atomic_t
id|usage
suffix:semicolon
DECL|member|device_name
r_char
op_star
id|device_name
suffix:semicolon
multiline_comment|/* device name prefix in devfs */
DECL|member|devfs_entry
id|devfs_handle_t
id|devfs_entry
suffix:semicolon
multiline_comment|/* handle needed to unregister dev from devfs */
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
DECL|typedef|Xpram_Dev
)brace
id|Xpram_Dev
suffix:semicolon
multiline_comment|/* 2.2: void xpram_setup (char *, int *); */
multiline_comment|/* begin 2.3 */
r_int
id|xpram_setup
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* end 2.3 */
r_int
id|xpram_init
c_func
(paren
r_void
)paren
suffix:semicolon
eof
