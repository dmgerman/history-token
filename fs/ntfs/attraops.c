macro_line|#include &quot;ntfs.h&quot;
multiline_comment|/*&n; * We need to define the attribute object structure. FIXME: Move these to&n; * ntfs.h.&n; */
r_typedef
r_struct
(brace
DECL|member|a_ni
id|ntfs_inode
op_star
id|a_ni
suffix:semicolon
DECL|member|a_vol
id|ntfs_volume
op_star
id|a_vol
suffix:semicolon
DECL|member|a_count
id|atomic_t
id|a_count
suffix:semicolon
DECL|member|a_size
id|s64
id|a_size
suffix:semicolon
DECL|member|a_sem
r_struct
id|rw_semaphore
id|a_sem
suffix:semicolon
DECL|member|a_mapping
r_struct
id|address_space
id|a_mapping
suffix:semicolon
DECL|member|a_flags
r_int
r_int
id|a_flags
suffix:semicolon
DECL|typedef|attr_obj
)brace
id|attr_obj
suffix:semicolon
multiline_comment|/**&n; * ntfs_attr_readpage - fill a page @page of an attribute object @aobj with data&n; * @aobj:&t;attribute object to which the page @page belongs&n; * @page:&t;page cache page to fill with data&n; *&n; */
singleline_comment|//static int ntfs_attr_readpage(attr_obj *aobj, struct page *page)
DECL|function|ntfs_attr_readpage
r_static
r_int
id|ntfs_attr_readpage
c_func
(paren
r_struct
id|file
op_star
id|aobj
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
multiline_comment|/*&n; * Address space operations for accessing attributes. Note that these functions&n; * do not accept an inode as the first parameter but an attribute object. We&n; * use this to implement a generic interface that is not bound to inodes in&n; * order to support multiple named streams per file, multiple bitmaps per file&n; * and directory, etc. Basically, this gives access to any attribute within an&n; * mft record.&n; *&n; * We make use of a slab cache for attribute object allocations.&n; */
DECL|variable|ntfs_attr_aops
r_struct
id|address_space_operations
id|ntfs_attr_aops
op_assign
(brace
id|writepage
suffix:colon
l_int|NULL
comma
multiline_comment|/* Write dirty page to disk. */
id|readpage
suffix:colon
id|ntfs_attr_readpage
comma
multiline_comment|/* Fill page with data. */
id|sync_page
suffix:colon
id|block_sync_page
comma
multiline_comment|/* Currently, just unplugs the&n;&t;&t;&t;&t;&t;&t;   disk request queue. */
id|prepare_write
suffix:colon
l_int|NULL
comma
multiline_comment|/* . */
id|commit_write
suffix:colon
l_int|NULL
comma
multiline_comment|/* . */
singleline_comment|//truncatepage:&t;NULL,&t;&t;&t;/* . */
)brace
suffix:semicolon
eof
