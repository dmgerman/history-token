macro_line|#ifndef __MATROXFB_MISC_H__
DECL|macro|__MATROXFB_MISC_H__
mdefine_line|#define __MATROXFB_MISC_H__
macro_line|#include &quot;matroxfb_base.h&quot;
multiline_comment|/* also for modules */
r_int
id|matroxfb_PLL_calcclock
c_func
(paren
r_const
r_struct
id|matrox_pll_features
op_star
id|pll
comma
r_int
r_int
id|freq
comma
r_int
r_int
id|fmax
comma
r_int
r_int
op_star
id|in
comma
r_int
r_int
op_star
id|feed
comma
r_int
r_int
op_star
id|post
)paren
suffix:semicolon
DECL|function|PLL_calcclock
r_static
r_inline
r_int
id|PLL_calcclock
c_func
(paren
id|CPMINFO
r_int
r_int
id|freq
comma
r_int
r_int
id|fmax
comma
r_int
r_int
op_star
id|in
comma
r_int
r_int
op_star
id|feed
comma
r_int
r_int
op_star
id|post
)paren
(brace
r_return
id|matroxfb_PLL_calcclock
c_func
(paren
op_amp
id|ACCESS_FBINFO
c_func
(paren
id|features.pll
)paren
comma
id|freq
comma
id|fmax
comma
id|in
comma
id|feed
comma
id|post
)paren
suffix:semicolon
)brace
r_void
id|matroxfb_createcursorshape
c_func
(paren
id|WPMINFO
r_struct
id|display
op_star
id|p
comma
r_int
id|vmode
)paren
suffix:semicolon
r_int
id|matroxfb_vgaHWinit
c_func
(paren
id|WPMINFO
r_struct
id|my_timming
op_star
id|m
comma
r_struct
id|display
op_star
id|p
)paren
suffix:semicolon
r_void
id|matroxfb_vgaHWrestore
c_func
(paren
id|WPMINFO2
)paren
suffix:semicolon
r_void
id|matroxfb_fastfont_init
c_func
(paren
r_struct
id|matrox_fb_info
op_star
id|minfo
)paren
suffix:semicolon
r_int
id|matrox_text_loadfont
c_func
(paren
id|WPMINFO
r_struct
id|display
op_star
id|p
)paren
suffix:semicolon
r_int
id|matroxfb_fastfont_tryset
c_func
(paren
id|WPMINFO
r_struct
id|display
op_star
id|p
)paren
suffix:semicolon
r_void
id|matroxfb_read_pins
c_func
(paren
id|WPMINFO2
)paren
suffix:semicolon
macro_line|#endif&t;/* __MATROXFB_MISC_H__ */
eof
