multiline_comment|/*&n; * include/linux/pagevec.h&n; *&n; * In many places it is efficient to batch an operation up against multiple&n; * pages.  A pagevec is a multipage container which is used for that.&n; */
DECL|macro|PAGEVEC_SIZE
mdefine_line|#define PAGEVEC_SIZE&t;16
r_struct
id|page
suffix:semicolon
r_struct
id|address_space
suffix:semicolon
DECL|struct|pagevec
r_struct
id|pagevec
(brace
DECL|member|nr
r_int
id|nr
suffix:semicolon
DECL|member|cold
r_int
id|cold
suffix:semicolon
DECL|member|pages
r_struct
id|page
op_star
id|pages
(braket
id|PAGEVEC_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
r_void
id|__pagevec_release
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
suffix:semicolon
r_void
id|__pagevec_release_nonlru
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
suffix:semicolon
r_void
id|__pagevec_free
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
suffix:semicolon
r_void
id|__pagevec_lru_add
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
suffix:semicolon
r_void
id|__pagevec_lru_add_active
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
suffix:semicolon
r_void
id|lru_add_drain
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pagevec_deactivate_inactive
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
suffix:semicolon
r_void
id|pagevec_strip
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
suffix:semicolon
r_int
r_int
id|pagevec_lookup
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
comma
r_struct
id|address_space
op_star
id|mapping
comma
id|pgoff_t
id|start
comma
r_int
r_int
id|nr_pages
)paren
suffix:semicolon
DECL|function|pagevec_init
r_static
r_inline
r_void
id|pagevec_init
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
comma
r_int
id|cold
)paren
(brace
id|pvec-&gt;nr
op_assign
l_int|0
suffix:semicolon
id|pvec-&gt;cold
op_assign
id|cold
suffix:semicolon
)brace
DECL|function|pagevec_reinit
r_static
r_inline
r_void
id|pagevec_reinit
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
id|pvec-&gt;nr
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|pagevec_count
r_static
r_inline
r_int
id|pagevec_count
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
r_return
id|pvec-&gt;nr
suffix:semicolon
)brace
DECL|function|pagevec_space
r_static
r_inline
r_int
id|pagevec_space
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
r_return
id|PAGEVEC_SIZE
op_minus
id|pvec-&gt;nr
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a page to a pagevec.  Returns the number of slots still available.&n; */
DECL|function|pagevec_add
r_static
r_inline
r_int
id|pagevec_add
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|pvec-&gt;pages
(braket
id|pvec-&gt;nr
op_increment
)braket
op_assign
id|page
suffix:semicolon
r_return
id|pagevec_space
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
DECL|function|pagevec_release
r_static
r_inline
r_void
id|pagevec_release
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
r_if
c_cond
(paren
id|pagevec_count
c_func
(paren
id|pvec
)paren
)paren
id|__pagevec_release
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
DECL|function|pagevec_release_nonlru
r_static
r_inline
r_void
id|pagevec_release_nonlru
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
r_if
c_cond
(paren
id|pagevec_count
c_func
(paren
id|pvec
)paren
)paren
id|__pagevec_release_nonlru
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
DECL|function|pagevec_free
r_static
r_inline
r_void
id|pagevec_free
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
r_if
c_cond
(paren
id|pagevec_count
c_func
(paren
id|pvec
)paren
)paren
id|__pagevec_free
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
DECL|function|pagevec_lru_add
r_static
r_inline
r_void
id|pagevec_lru_add
c_func
(paren
r_struct
id|pagevec
op_star
id|pvec
)paren
(brace
r_if
c_cond
(paren
id|pagevec_count
c_func
(paren
id|pvec
)paren
)paren
id|__pagevec_lru_add
c_func
(paren
id|pvec
)paren
suffix:semicolon
)brace
eof
