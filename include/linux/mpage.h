multiline_comment|/*&n; * include/linux/mpage.h&n; *&n; * Contains declarations related to preparing and submitting BIOS which contain&n; * multiple pagecache pages.&n; */
multiline_comment|/*&n; * (And no, it doesn&squot;t do the #ifdef __MPAGE_H thing, and it doesn&squot;t do&n; * nested includes.  Get it right in the .c file).&n; */
r_struct
id|writeback_control
suffix:semicolon
r_int
id|mpage_readpages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|list_head
op_star
id|pages
comma
r_int
id|nr_pages
comma
id|get_block_t
id|get_block
)paren
suffix:semicolon
r_int
id|mpage_readpage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|get_block_t
id|get_block
)paren
suffix:semicolon
r_int
id|mpage_writepages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|writeback_control
op_star
id|wbc
comma
id|get_block_t
id|get_block
)paren
suffix:semicolon
r_static
r_inline
r_int
DECL|function|generic_writepages
id|generic_writepages
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|writeback_control
op_star
id|wbc
)paren
(brace
r_return
id|mpage_writepages
c_func
(paren
id|mapping
comma
id|wbc
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
