multiline_comment|/*&n; * include/linux/backing-dev.h&n; *&n; * low-level device information and state which is propagated up through&n; * to high-level code.&n; */
macro_line|#ifndef _LINUX_BACKING_DEV_H
DECL|macro|_LINUX_BACKING_DEV_H
mdefine_line|#define _LINUX_BACKING_DEV_H
multiline_comment|/*&n; * Bits in backing_dev_info.state&n; */
DECL|enum|bdi_state
r_enum
id|bdi_state
(brace
DECL|enumerator|BDI_pdflush
id|BDI_pdflush
comma
multiline_comment|/* A pdflush thread is working this device */
DECL|enumerator|BDI_unused
id|BDI_unused
comma
multiline_comment|/* Available bits start here */
)brace
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
)brace
suffix:semicolon
r_extern
r_struct
id|backing_dev_info
id|default_backing_dev_info
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
macro_line|#endif&t;&t;/* _LINUX_BACKING_DEV_H */
eof
