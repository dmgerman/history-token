multiline_comment|/*&n; * include/linux/backing-dev.h&n; *&n; * low-level device information and state which is propagated up through&n; * to high-level code.&n; */
macro_line|#ifndef _LINUX_BACKING_DEV_H
DECL|macro|_LINUX_BACKING_DEV_H
mdefine_line|#define _LINUX_BACKING_DEV_H
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * Bits in backing_dev_info.state&n; */
DECL|enum|bdi_state
r_enum
id|bdi_state
(brace
DECL|enumerator|BDI_pdflush
id|BDI_pdflush
comma
multiline_comment|/* A pdflush thread is working this device */
DECL|enumerator|BDI_write_congested
id|BDI_write_congested
comma
multiline_comment|/* The write queue is getting full */
DECL|enumerator|BDI_read_congested
id|BDI_read_congested
comma
multiline_comment|/* The read queue is getting full */
DECL|enumerator|BDI_unused
id|BDI_unused
comma
multiline_comment|/* Available bits start here */
)brace
suffix:semicolon
DECL|typedef|congested_fn
r_typedef
r_int
(paren
id|congested_fn
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|struct|backing_dev_info
r_struct
id|backing_dev_info
(brace
DECL|member|ra_pages
r_int
r_int
id|ra_pages
suffix:semicolon
multiline_comment|/* max readahead in PAGE_CACHE_SIZE units */
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* Always use atomic bitops on this */
DECL|member|capabilities
r_int
r_int
id|capabilities
suffix:semicolon
multiline_comment|/* Device capabilities */
DECL|member|congested_fn
id|congested_fn
op_star
id|congested_fn
suffix:semicolon
multiline_comment|/* Function pointer if device is md/dm */
DECL|member|congested_data
r_void
op_star
id|congested_data
suffix:semicolon
multiline_comment|/* Pointer to aux data for congested func */
DECL|member|unplug_io_fn
r_void
(paren
op_star
id|unplug_io_fn
)paren
(paren
r_struct
id|backing_dev_info
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
DECL|member|unplug_io_data
r_void
op_star
id|unplug_io_data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Flags in backing_dev_info::capability&n; * - The first two flags control whether dirty pages will contribute to the&n; *   VM&squot;s accounting and whether writepages() should be called for dirty pages&n; *   (something that would not, for example, be appropriate for ramfs)&n; * - These flags let !MMU mmap() govern direct device mapping vs immediate&n; *   copying more easily for MAP_PRIVATE, especially for ROM filesystems&n; */
DECL|macro|BDI_CAP_NO_ACCT_DIRTY
mdefine_line|#define BDI_CAP_NO_ACCT_DIRTY&t;0x00000001&t;/* Dirty pages shouldn&squot;t contribute to accounting */
DECL|macro|BDI_CAP_NO_WRITEBACK
mdefine_line|#define BDI_CAP_NO_WRITEBACK&t;0x00000002&t;/* Don&squot;t write pages back */
DECL|macro|BDI_CAP_MAP_COPY
mdefine_line|#define BDI_CAP_MAP_COPY&t;0x00000004&t;/* Copy can be mapped (MAP_PRIVATE) */
DECL|macro|BDI_CAP_MAP_DIRECT
mdefine_line|#define BDI_CAP_MAP_DIRECT&t;0x00000008&t;/* Can be mapped directly (MAP_SHARED) */
DECL|macro|BDI_CAP_READ_MAP
mdefine_line|#define BDI_CAP_READ_MAP&t;0x00000010&t;/* Can be mapped for reading */
DECL|macro|BDI_CAP_WRITE_MAP
mdefine_line|#define BDI_CAP_WRITE_MAP&t;0x00000020&t;/* Can be mapped for writing */
DECL|macro|BDI_CAP_EXEC_MAP
mdefine_line|#define BDI_CAP_EXEC_MAP&t;0x00000040&t;/* Can be mapped for execution */
DECL|macro|BDI_CAP_VMFLAGS
mdefine_line|#define BDI_CAP_VMFLAGS &bslash;&n;&t;(BDI_CAP_READ_MAP | BDI_CAP_WRITE_MAP | BDI_CAP_EXEC_MAP)
macro_line|#if defined(VM_MAYREAD) &amp;&amp; &bslash;&n;&t;(BDI_CAP_READ_MAP != VM_MAYREAD || &bslash;&n;&t; BDI_CAP_WRITE_MAP != VM_MAYWRITE || &bslash;&n;&t; BDI_CAP_EXEC_MAP != VM_MAYEXEC)
macro_line|#error please change backing_dev_info::capabilities flags
macro_line|#endif
r_extern
r_struct
id|backing_dev_info
id|default_backing_dev_info
suffix:semicolon
r_void
id|default_unplug_io_fn
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
comma
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_int
id|writeback_acquire
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
)paren
suffix:semicolon
r_int
id|writeback_in_progress
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
)paren
suffix:semicolon
r_void
id|writeback_release
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
)paren
suffix:semicolon
DECL|function|bdi_congested
r_static
r_inline
r_int
id|bdi_congested
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
comma
r_int
id|bdi_bits
)paren
(brace
r_if
c_cond
(paren
id|bdi-&gt;congested_fn
)paren
r_return
id|bdi
op_member_access_from_pointer
id|congested_fn
c_func
(paren
id|bdi-&gt;congested_data
comma
id|bdi_bits
)paren
suffix:semicolon
r_return
(paren
id|bdi-&gt;state
op_amp
id|bdi_bits
)paren
suffix:semicolon
)brace
DECL|function|bdi_read_congested
r_static
r_inline
r_int
id|bdi_read_congested
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
)paren
(brace
r_return
id|bdi_congested
c_func
(paren
id|bdi
comma
l_int|1
op_lshift
id|BDI_read_congested
)paren
suffix:semicolon
)brace
DECL|function|bdi_write_congested
r_static
r_inline
r_int
id|bdi_write_congested
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
)paren
(brace
r_return
id|bdi_congested
c_func
(paren
id|bdi
comma
l_int|1
op_lshift
id|BDI_write_congested
)paren
suffix:semicolon
)brace
DECL|function|bdi_rw_congested
r_static
r_inline
r_int
id|bdi_rw_congested
c_func
(paren
r_struct
id|backing_dev_info
op_star
id|bdi
)paren
(brace
r_return
id|bdi_congested
c_func
(paren
id|bdi
comma
(paren
l_int|1
op_lshift
id|BDI_read_congested
)paren
op_or
(paren
l_int|1
op_lshift
id|BDI_write_congested
)paren
)paren
suffix:semicolon
)brace
DECL|macro|bdi_cap_writeback_dirty
mdefine_line|#define bdi_cap_writeback_dirty(bdi) &bslash;&n;&t;(!((bdi)-&gt;capabilities &amp; BDI_CAP_NO_WRITEBACK))
DECL|macro|bdi_cap_account_dirty
mdefine_line|#define bdi_cap_account_dirty(bdi) &bslash;&n;&t;(!((bdi)-&gt;capabilities &amp; BDI_CAP_NO_ACCT_DIRTY))
DECL|macro|mapping_cap_writeback_dirty
mdefine_line|#define mapping_cap_writeback_dirty(mapping) &bslash;&n;&t;bdi_cap_writeback_dirty((mapping)-&gt;backing_dev_info)
DECL|macro|mapping_cap_account_dirty
mdefine_line|#define mapping_cap_account_dirty(mapping) &bslash;&n;&t;bdi_cap_account_dirty((mapping)-&gt;backing_dev_info)
macro_line|#endif&t;&t;/* _LINUX_BACKING_DEV_H */
eof
