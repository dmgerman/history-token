macro_line|#ifndef _M68K_ATARI_STRAM_H
DECL|macro|_M68K_ATARI_STRAM_H
mdefine_line|#define _M68K_ATARI_STRAM_H
multiline_comment|/*&n; * Functions for Atari ST-RAM management&n; */
multiline_comment|/* public interface */
r_void
op_star
id|atari_stram_alloc
c_func
(paren
r_int
id|size
comma
r_const
r_char
op_star
id|owner
)paren
suffix:semicolon
r_void
id|atari_stram_free
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* functions called internally by other parts of the kernel */
r_void
id|atari_stram_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|atari_stram_reserve_pages
c_func
(paren
r_void
op_star
id|start_mem
)paren
suffix:semicolon
r_void
id|atari_stram_mem_init_hook
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /*_M68K_ATARI_STRAM_H */
eof
