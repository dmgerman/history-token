multiline_comment|/* leo.c: LEO frame buffer driver&n; *&n; * Copyright (C) 2003 David S. Miller (davem@redhat.com)&n; * Copyright (C) 1996-1999 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1997 Michal Rehacek (Michal.Rehacek@st.mff.cuni.cz)&n; *&n; * Driver layout based loosely on tgafb.c, see that file for credits.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/fbio.h&gt;
macro_line|#include &quot;sbuslib.h&quot;
multiline_comment|/*&n; * Local functions.&n; */
r_static
r_int
id|leo_setcolreg
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
r_static
r_int
id|leo_blank
c_func
(paren
r_int
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
r_static
r_int
id|leo_mmap
c_func
(paren
r_struct
id|fb_info
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_static
r_int
id|leo_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
r_static
r_int
id|leo_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; *  Frame buffer operations&n; */
DECL|variable|leo_ops
r_static
r_struct
id|fb_ops
id|leo_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_setcolreg
op_assign
id|leo_setcolreg
comma
dot
id|fb_blank
op_assign
id|leo_blank
comma
dot
id|fb_pan_display
op_assign
id|leo_pan_display
comma
dot
id|fb_fillrect
op_assign
id|cfb_fillrect
comma
dot
id|fb_copyarea
op_assign
id|cfb_copyarea
comma
dot
id|fb_imageblit
op_assign
id|cfb_imageblit
comma
dot
id|fb_mmap
op_assign
id|leo_mmap
comma
dot
id|fb_ioctl
op_assign
id|leo_ioctl
comma
dot
id|fb_cursor
op_assign
id|soft_cursor
comma
)brace
suffix:semicolon
DECL|macro|LEO_OFF_LC_SS0_KRN
mdefine_line|#define LEO_OFF_LC_SS0_KRN&t;0x00200000UL
DECL|macro|LEO_OFF_LC_SS0_USR
mdefine_line|#define LEO_OFF_LC_SS0_USR&t;0x00201000UL
DECL|macro|LEO_OFF_LC_SS1_KRN
mdefine_line|#define LEO_OFF_LC_SS1_KRN&t;0x01200000UL
DECL|macro|LEO_OFF_LC_SS1_USR
mdefine_line|#define LEO_OFF_LC_SS1_USR&t;0x01201000UL
DECL|macro|LEO_OFF_LD_SS0
mdefine_line|#define LEO_OFF_LD_SS0&t;&t;0x00400000UL
DECL|macro|LEO_OFF_LD_SS1
mdefine_line|#define LEO_OFF_LD_SS1&t;&t;0x01400000UL
DECL|macro|LEO_OFF_LD_GBL
mdefine_line|#define LEO_OFF_LD_GBL&t;&t;0x00401000UL
DECL|macro|LEO_OFF_LX_KRN
mdefine_line|#define LEO_OFF_LX_KRN&t;&t;0x00600000UL
DECL|macro|LEO_OFF_LX_CURSOR
mdefine_line|#define LEO_OFF_LX_CURSOR&t;0x00601000UL
DECL|macro|LEO_OFF_SS0
mdefine_line|#define LEO_OFF_SS0&t;&t;0x00800000UL
DECL|macro|LEO_OFF_SS1
mdefine_line|#define LEO_OFF_SS1&t;&t;0x01800000UL
DECL|macro|LEO_OFF_UNK
mdefine_line|#define LEO_OFF_UNK&t;&t;0x00602000UL
DECL|macro|LEO_OFF_UNK2
mdefine_line|#define LEO_OFF_UNK2&t;&t;0x00000000UL
DECL|macro|LEO_CUR_ENABLE
mdefine_line|#define LEO_CUR_ENABLE&t;&t;0x00000080
DECL|macro|LEO_CUR_UPDATE
mdefine_line|#define LEO_CUR_UPDATE&t;&t;0x00000030
DECL|macro|LEO_CUR_PROGRESS
mdefine_line|#define LEO_CUR_PROGRESS&t;0x00000006
DECL|macro|LEO_CUR_UPDATECMAP
mdefine_line|#define LEO_CUR_UPDATECMAP&t;0x00000003
DECL|macro|LEO_CUR_TYPE_MASK
mdefine_line|#define LEO_CUR_TYPE_MASK&t;0x00000000
DECL|macro|LEO_CUR_TYPE_IMAGE
mdefine_line|#define LEO_CUR_TYPE_IMAGE&t;0x00000020
DECL|macro|LEO_CUR_TYPE_CMAP
mdefine_line|#define LEO_CUR_TYPE_CMAP&t;0x00000050
DECL|struct|leo_cursor
r_struct
id|leo_cursor
(brace
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|cur_type
r_volatile
id|u32
id|cur_type
suffix:semicolon
DECL|member|cur_misc
r_volatile
id|u32
id|cur_misc
suffix:semicolon
DECL|member|cur_cursxy
r_volatile
id|u32
id|cur_cursxy
suffix:semicolon
DECL|member|cur_data
r_volatile
id|u32
id|cur_data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LEO_KRN_TYPE_CLUT0
mdefine_line|#define LEO_KRN_TYPE_CLUT0&t;0x00001000
DECL|macro|LEO_KRN_TYPE_CLUT1
mdefine_line|#define LEO_KRN_TYPE_CLUT1&t;0x00001001
DECL|macro|LEO_KRN_TYPE_CLUT2
mdefine_line|#define LEO_KRN_TYPE_CLUT2&t;0x00001002
DECL|macro|LEO_KRN_TYPE_WID
mdefine_line|#define LEO_KRN_TYPE_WID&t;0x00001003
DECL|macro|LEO_KRN_TYPE_UNK
mdefine_line|#define LEO_KRN_TYPE_UNK&t;0x00001006
DECL|macro|LEO_KRN_TYPE_VIDEO
mdefine_line|#define LEO_KRN_TYPE_VIDEO&t;0x00002003
DECL|macro|LEO_KRN_TYPE_CLUTDATA
mdefine_line|#define LEO_KRN_TYPE_CLUTDATA&t;0x00004000
DECL|macro|LEO_KRN_CSR_ENABLE
mdefine_line|#define LEO_KRN_CSR_ENABLE&t;0x00000008
DECL|macro|LEO_KRN_CSR_PROGRESS
mdefine_line|#define LEO_KRN_CSR_PROGRESS&t;0x00000004
DECL|macro|LEO_KRN_CSR_UNK
mdefine_line|#define LEO_KRN_CSR_UNK&t;&t;0x00000002
DECL|macro|LEO_KRN_CSR_UNK2
mdefine_line|#define LEO_KRN_CSR_UNK2&t;0x00000001
DECL|struct|leo_lx_krn
r_struct
id|leo_lx_krn
(brace
DECL|member|krn_type
r_volatile
id|u32
id|krn_type
suffix:semicolon
DECL|member|krn_csr
r_volatile
id|u32
id|krn_csr
suffix:semicolon
DECL|member|krn_value
r_volatile
id|u32
id|krn_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|leo_lc_ss0_krn
r_struct
id|leo_lc_ss0_krn
(brace
DECL|member|misc
r_volatile
id|u32
id|misc
suffix:semicolon
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|0x800
op_minus
l_int|4
)braket
suffix:semicolon
DECL|member|rev
r_volatile
id|u32
id|rev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|leo_lc_ss0_usr
r_struct
id|leo_lc_ss0_usr
(brace
DECL|member|csr
r_volatile
id|u32
id|csr
suffix:semicolon
DECL|member|addrspace
r_volatile
id|u32
id|addrspace
suffix:semicolon
DECL|member|fontmsk
r_volatile
id|u32
id|fontmsk
suffix:semicolon
DECL|member|fontt
r_volatile
id|u32
id|fontt
suffix:semicolon
DECL|member|extent
r_volatile
id|u32
id|extent
suffix:semicolon
DECL|member|src
r_volatile
id|u32
id|src
suffix:semicolon
DECL|member|dst
id|u32
id|dst
suffix:semicolon
DECL|member|copy
r_volatile
id|u32
id|copy
suffix:semicolon
DECL|member|fill
r_volatile
id|u32
id|fill
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|leo_lc_ss1_krn
r_struct
id|leo_lc_ss1_krn
(brace
DECL|member|unknown
id|u8
id|unknown
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|leo_lc_ss1_usr
r_struct
id|leo_lc_ss1_usr
(brace
DECL|member|unknown
id|u8
id|unknown
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|leo_ld
r_struct
id|leo_ld
(brace
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|0xe00
)braket
suffix:semicolon
DECL|member|csr
r_volatile
id|u32
id|csr
suffix:semicolon
DECL|member|wid
r_volatile
id|u32
id|wid
suffix:semicolon
DECL|member|wmask
r_volatile
id|u32
id|wmask
suffix:semicolon
DECL|member|widclip
r_volatile
id|u32
id|widclip
suffix:semicolon
DECL|member|vclipmin
r_volatile
id|u32
id|vclipmin
suffix:semicolon
DECL|member|vclipmax
r_volatile
id|u32
id|vclipmax
suffix:semicolon
DECL|member|pickmin
r_volatile
id|u32
id|pickmin
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|pickmax
r_volatile
id|u32
id|pickmax
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|fg
r_volatile
id|u32
id|fg
suffix:semicolon
DECL|member|bg
r_volatile
id|u32
id|bg
suffix:semicolon
DECL|member|src
r_volatile
id|u32
id|src
suffix:semicolon
multiline_comment|/* Copy/Scroll (SS0 only) */
DECL|member|dst
r_volatile
id|u32
id|dst
suffix:semicolon
multiline_comment|/* Copy/Scroll/Fill (SS0 only) */
DECL|member|extent
r_volatile
id|u32
id|extent
suffix:semicolon
multiline_comment|/* Copy/Scroll/Fill size (SS0 only) */
DECL|member|xxx1
id|u32
id|xxx1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|setsem
r_volatile
id|u32
id|setsem
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|clrsem
r_volatile
id|u32
id|clrsem
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|clrpick
r_volatile
id|u32
id|clrpick
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|clrdat
r_volatile
id|u32
id|clrdat
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|alpha
r_volatile
id|u32
id|alpha
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|xxx2
id|u8
id|xxx2
(braket
l_int|0x2c
)braket
suffix:semicolon
DECL|member|winbg
r_volatile
id|u32
id|winbg
suffix:semicolon
DECL|member|planemask
r_volatile
id|u32
id|planemask
suffix:semicolon
DECL|member|rop
r_volatile
id|u32
id|rop
suffix:semicolon
DECL|member|z
r_volatile
id|u32
id|z
suffix:semicolon
DECL|member|dczf
r_volatile
id|u32
id|dczf
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|dczb
r_volatile
id|u32
id|dczb
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|dcs
r_volatile
id|u32
id|dcs
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|dczs
r_volatile
id|u32
id|dczs
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|pickfb
r_volatile
id|u32
id|pickfb
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|pickbb
r_volatile
id|u32
id|pickbb
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|dcfc
r_volatile
id|u32
id|dcfc
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|forcecol
r_volatile
id|u32
id|forcecol
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|door
r_volatile
id|u32
id|door
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* SS1 only */
DECL|member|pick
r_volatile
id|u32
id|pick
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* SS1 only */
)brace
suffix:semicolon
DECL|macro|LEO_SS1_MISC_ENABLE
mdefine_line|#define LEO_SS1_MISC_ENABLE&t;0x00000001
DECL|macro|LEO_SS1_MISC_STEREO
mdefine_line|#define LEO_SS1_MISC_STEREO&t;0x00000002
DECL|struct|leo_ld_ss1
r_struct
id|leo_ld_ss1
(brace
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|0xef4
)braket
suffix:semicolon
DECL|member|ss1_misc
r_volatile
id|u32
id|ss1_misc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|leo_ld_gbl
r_struct
id|leo_ld_gbl
(brace
DECL|member|unknown
id|u8
id|unknown
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|leo_par
r_struct
id|leo_par
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|lx_krn
r_struct
id|leo_lx_krn
op_star
id|lx_krn
suffix:semicolon
DECL|member|lc_ss0_usr
r_struct
id|leo_lc_ss0_usr
op_star
id|lc_ss0_usr
suffix:semicolon
DECL|member|ld_ss0
r_struct
id|leo_ld_ss0
op_star
id|ld_ss0
suffix:semicolon
DECL|member|ld_ss1
r_struct
id|leo_ld_ss1
op_star
id|ld_ss1
suffix:semicolon
DECL|member|cursor
r_struct
id|leo_cursor
op_star
id|cursor
suffix:semicolon
DECL|member|extent
id|u32
id|extent
suffix:semicolon
DECL|member|clut_data
id|u32
id|clut_data
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|macro|LEO_FLAG_BLANKED
mdefine_line|#define LEO_FLAG_BLANKED&t;0x00000001
DECL|member|physbase
r_int
r_int
id|physbase
suffix:semicolon
DECL|member|fbsize
r_int
r_int
id|fbsize
suffix:semicolon
DECL|member|sdev
r_struct
id|sbus_dev
op_star
id|sdev
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|function|leo_wait
r_static
r_void
id|leo_wait
c_func
(paren
r_struct
id|leo_lx_krn
op_star
id|lx_krn
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|sbus_readl
c_func
(paren
op_amp
id|lx_krn-&gt;krn_csr
)paren
op_amp
id|LEO_KRN_CSR_PROGRESS
)paren
op_logical_and
id|i
OL
l_int|300000
suffix:semicolon
id|i
op_increment
)paren
id|udelay
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Busy wait at most 0.3 sec */
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; *      leo_setcolreg - Optional function. Sets a color register.&n; *      @regno: boolean, 0 copy local, 1 get_user() function&n; *      @red: frame buffer colormap structure&n; *      @green: The green value which can be up to 16 bits wide&n; *      @blue:  The blue value which can be up to 16 bits wide.&n; *      @transp: If supported the alpha value which can be up to 16 bits wide.&n; *      @info: frame buffer info structure&n; */
DECL|function|leo_setcolreg
r_static
r_int
id|leo_setcolreg
c_func
(paren
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
comma
r_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|leo_par
op_star
id|par
op_assign
(paren
r_struct
id|leo_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|leo_lx_krn
op_star
id|lx_krn
op_assign
id|par-&gt;lx_krn
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|val
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_ge
l_int|256
)paren
r_return
l_int|1
suffix:semicolon
id|red
op_rshift_assign
l_int|8
suffix:semicolon
id|green
op_rshift_assign
l_int|8
suffix:semicolon
id|blue
op_rshift_assign
l_int|8
suffix:semicolon
id|par-&gt;clut_data
(braket
id|regno
)braket
op_assign
id|red
op_or
(paren
id|green
op_lshift
l_int|8
)paren
op_or
(paren
id|blue
op_lshift
l_int|16
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|leo_wait
c_func
(paren
id|lx_krn
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
id|LEO_KRN_TYPE_CLUTDATA
comma
op_amp
id|lx_krn-&gt;krn_type
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
id|sbus_writel
c_func
(paren
id|par-&gt;clut_data
(braket
id|i
)braket
comma
op_amp
id|lx_krn-&gt;krn_value
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
id|LEO_KRN_TYPE_CLUT0
comma
op_amp
id|lx_krn-&gt;krn_type
)paren
suffix:semicolon
id|val
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|lx_krn-&gt;krn_csr
)paren
suffix:semicolon
id|val
op_or_assign
(paren
id|LEO_KRN_CSR_UNK
op_or
id|LEO_KRN_CSR_UNK2
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
id|val
comma
op_amp
id|lx_krn-&gt;krn_csr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *      leo_blank - Optional function.  Blanks the display.&n; *      @blank_mode: the blank mode we want.&n; *      @info: frame buffer structure that represents a single frame buffer&n; */
DECL|function|leo_blank
r_static
r_int
id|leo_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|leo_par
op_star
id|par
op_assign
(paren
r_struct
id|leo_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|leo_lx_krn
op_star
id|lx_krn
op_assign
id|par-&gt;lx_krn
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|blank
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Unblanking */
id|val
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|lx_krn-&gt;krn_csr
)paren
suffix:semicolon
id|val
op_or_assign
id|LEO_KRN_CSR_ENABLE
suffix:semicolon
id|sbus_writel
c_func
(paren
id|val
comma
op_amp
id|lx_krn-&gt;krn_csr
)paren
suffix:semicolon
id|par-&gt;flags
op_and_assign
op_complement
id|LEO_FLAG_BLANKED
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Normal blanking */
r_case
l_int|2
suffix:colon
multiline_comment|/* VESA blank (vsync off) */
r_case
l_int|3
suffix:colon
multiline_comment|/* VESA blank (hsync off) */
r_case
l_int|4
suffix:colon
multiline_comment|/* Poweroff */
id|val
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|lx_krn-&gt;krn_csr
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|LEO_KRN_CSR_ENABLE
suffix:semicolon
id|sbus_writel
c_func
(paren
id|val
comma
op_amp
id|lx_krn-&gt;krn_csr
)paren
suffix:semicolon
id|par-&gt;flags
op_or_assign
id|LEO_FLAG_BLANKED
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|leo_mmap_map
r_static
r_struct
id|sbus_mmap_map
id|leo_mmap_map
(braket
)braket
op_assign
(brace
(brace
dot
id|voff
op_assign
id|LEO_SS0_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_SS0
comma
dot
id|size
op_assign
l_int|0x800000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_LC_SS0_USR_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_LC_SS0_USR
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_LD_SS0_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_LD_SS0
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_LX_CURSOR_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_LX_CURSOR
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_SS1_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_SS1
comma
dot
id|size
op_assign
l_int|0x800000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_LC_SS1_USR_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_LC_SS1_USR
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_LD_SS1_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_LD_SS1
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_UNK_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_UNK
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_LX_KRN_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_LX_KRN
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_LC_SS0_KRN_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_LC_SS0_KRN
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_LC_SS1_KRN_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_LC_SS1_KRN
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_LD_GBL_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_LD_GBL
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|LEO_UNK2_MAP
comma
dot
id|poff
op_assign
id|LEO_OFF_UNK2
comma
dot
id|size
op_assign
l_int|0x100000
)brace
comma
(brace
dot
id|size
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|leo_mmap
r_static
r_int
id|leo_mmap
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|leo_par
op_star
id|par
op_assign
(paren
r_struct
id|leo_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_return
id|sbusfb_mmap_helper
c_func
(paren
id|leo_mmap_map
comma
id|par-&gt;physbase
comma
id|par-&gt;fbsize
comma
id|par-&gt;sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|which_io
comma
id|vma
)paren
suffix:semicolon
)brace
DECL|function|leo_ioctl
r_static
r_int
id|leo_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|leo_par
op_star
id|par
op_assign
(paren
r_struct
id|leo_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_return
id|sbusfb_ioctl_helper
c_func
(paren
id|cmd
comma
id|arg
comma
id|info
comma
id|FBTYPE_SUNLEO
comma
l_int|32
comma
id|par-&gt;fbsize
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Initialisation&n; */
r_static
r_void
DECL|function|leo_init_fix
id|leo_init_fix
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|leo_par
op_star
id|par
op_assign
(paren
r_struct
id|leo_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
id|strlcpy
c_func
(paren
id|info-&gt;fix.id
comma
id|par-&gt;sdev-&gt;prom_name
comma
r_sizeof
(paren
id|info-&gt;fix.id
)paren
)paren
suffix:semicolon
id|info-&gt;fix.type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|info-&gt;fix.line_length
op_assign
l_int|8192
suffix:semicolon
id|info-&gt;fix.accel
op_assign
id|FB_ACCEL_SUN_LEO
suffix:semicolon
)brace
DECL|function|leo_wid_put
r_static
r_void
id|leo_wid_put
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_wid_list
op_star
id|wl
)paren
(brace
r_struct
id|leo_par
op_star
id|par
op_assign
(paren
r_struct
id|leo_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|leo_lx_krn
op_star
id|lx_krn
op_assign
id|par-&gt;lx_krn
suffix:semicolon
r_struct
id|fb_wid_item
op_star
id|wi
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|val
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|leo_wait
c_func
(paren
id|lx_krn
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|wi
op_assign
id|wl-&gt;wl_list
suffix:semicolon
id|i
OL
id|wl-&gt;wl_count
suffix:semicolon
id|i
op_increment
comma
id|wi
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|wi-&gt;wi_type
)paren
(brace
r_case
id|FB_WID_DBL_8
suffix:colon
id|j
op_assign
(paren
id|wi-&gt;wi_index
op_amp
l_int|0xf
)paren
op_plus
l_int|0x40
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FB_WID_DBL_24
suffix:colon
id|j
op_assign
id|wi-&gt;wi_index
op_amp
l_int|0x3f
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_continue
suffix:semicolon
)brace
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0x5800
op_plus
id|j
comma
op_amp
id|lx_krn-&gt;krn_type
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
id|wi-&gt;wi_values
(braket
l_int|0
)braket
comma
op_amp
id|lx_krn-&gt;krn_value
)paren
suffix:semicolon
)brace
id|sbus_writel
c_func
(paren
id|LEO_KRN_TYPE_WID
comma
op_amp
id|lx_krn-&gt;krn_type
)paren
suffix:semicolon
id|val
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|lx_krn-&gt;krn_csr
)paren
suffix:semicolon
id|val
op_or_assign
(paren
id|LEO_KRN_CSR_UNK
op_or
id|LEO_KRN_CSR_UNK2
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
id|val
comma
op_amp
id|lx_krn-&gt;krn_csr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|leo_init_wids
r_static
r_void
id|leo_init_wids
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_wid_item
id|wi
suffix:semicolon
r_struct
id|fb_wid_list
id|wl
suffix:semicolon
id|wl.wl_count
op_assign
l_int|1
suffix:semicolon
id|wl.wl_list
op_assign
op_amp
id|wi
suffix:semicolon
id|wi.wi_type
op_assign
id|FB_WID_DBL_8
suffix:semicolon
id|wi.wi_index
op_assign
l_int|0
suffix:semicolon
id|wi.wi_values
(braket
l_int|0
)braket
op_assign
l_int|0x2c0
suffix:semicolon
id|leo_wid_put
c_func
(paren
id|info
comma
op_amp
id|wl
)paren
suffix:semicolon
id|wi.wi_index
op_assign
l_int|1
suffix:semicolon
id|wi.wi_values
(braket
l_int|0
)braket
op_assign
l_int|0x30
suffix:semicolon
id|leo_wid_put
c_func
(paren
id|info
comma
op_amp
id|wl
)paren
suffix:semicolon
id|wi.wi_index
op_assign
l_int|2
suffix:semicolon
id|wi.wi_values
(braket
l_int|0
)braket
op_assign
l_int|0x20
suffix:semicolon
id|leo_wid_put
c_func
(paren
id|info
comma
op_amp
id|wl
)paren
suffix:semicolon
id|wi.wi_type
op_assign
id|FB_WID_DBL_24
suffix:semicolon
id|wi.wi_index
op_assign
l_int|1
suffix:semicolon
id|wi.wi_values
(braket
l_int|0
)braket
op_assign
l_int|0x30
suffix:semicolon
id|leo_wid_put
c_func
(paren
id|info
comma
op_amp
id|wl
)paren
suffix:semicolon
)brace
DECL|function|leo_switch_from_graph
r_static
r_void
id|leo_switch_from_graph
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|leo_par
op_star
id|par
op_assign
(paren
r_struct
id|leo_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|leo_ld
op_star
id|ss
op_assign
(paren
r_struct
id|leo_ld
op_star
)paren
id|par-&gt;ld_ss0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|par-&gt;extent
op_assign
(paren
(paren
id|info-&gt;var.xres
op_minus
l_int|1
)paren
op_or
(paren
(paren
id|info-&gt;var.yres
op_minus
l_int|1
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0xffffffff
comma
op_amp
id|ss-&gt;wid
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0xffff
comma
op_amp
id|ss-&gt;wmask
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0
comma
op_amp
id|ss-&gt;vclipmin
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
id|par-&gt;extent
comma
op_amp
id|ss-&gt;vclipmax
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0
comma
op_amp
id|ss-&gt;fg
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0xff000000
comma
op_amp
id|ss-&gt;planemask
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0x310850
comma
op_amp
id|ss-&gt;rop
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0
comma
op_amp
id|ss-&gt;widclip
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
(paren
id|info-&gt;var.xres
op_minus
l_int|1
)paren
op_or
(paren
(paren
id|info-&gt;var.yres
op_minus
l_int|1
)paren
op_lshift
l_int|11
)paren
comma
op_amp
id|par-&gt;lc_ss0_usr-&gt;extent
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|4
comma
op_amp
id|par-&gt;lc_ss0_usr-&gt;addrspace
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0x80000000
comma
op_amp
id|par-&gt;lc_ss0_usr-&gt;fill
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0
comma
op_amp
id|par-&gt;lc_ss0_usr-&gt;fontt
)paren
suffix:semicolon
r_do
(brace
id|val
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|par-&gt;lc_ss0_usr-&gt;csr
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|val
op_amp
l_int|0x20000000
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|leo_pan_display
r_static
r_int
id|leo_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/* We just use this to catch switches out of&n;&t; * graphics mode.&n;&t; */
id|leo_switch_from_graph
c_func
(paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;xoffset
op_logical_or
id|var-&gt;yoffset
op_logical_or
id|var-&gt;vmode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|leo_init_hw
r_static
r_void
id|leo_init_hw
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|leo_par
op_star
id|par
op_assign
(paren
r_struct
id|leo_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|val
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|par-&gt;ld_ss1-&gt;ss1_misc
)paren
suffix:semicolon
id|val
op_or_assign
id|LEO_SS1_MISC_ENABLE
suffix:semicolon
id|sbus_writel
c_func
(paren
id|val
comma
op_amp
id|par-&gt;ld_ss1-&gt;ss1_misc
)paren
suffix:semicolon
id|leo_switch_from_graph
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
DECL|function|leo_fixup_var_rgb
r_static
r_void
id|leo_fixup_var_rgb
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
(brace
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|16
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
)brace
DECL|struct|all_info
r_struct
id|all_info
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
DECL|member|par
r_struct
id|leo_par
id|par
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|leo_list
)paren
suffix:semicolon
DECL|function|leo_init_one
r_static
r_void
id|leo_init_one
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
)paren
(brace
r_struct
id|all_info
op_star
id|all
suffix:semicolon
r_int
id|linebytes
suffix:semicolon
id|all
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|all
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|all
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;leo: Cannot allocate memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|all
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|all
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|all-&gt;list
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|all-&gt;par.lock
)paren
suffix:semicolon
id|all-&gt;par.sdev
op_assign
id|sdev
suffix:semicolon
id|all-&gt;par.physbase
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
id|sbusfb_fill_var
c_func
(paren
op_amp
id|all-&gt;info.var
comma
id|sdev-&gt;prom_node
comma
l_int|32
)paren
suffix:semicolon
id|leo_fixup_var_rgb
c_func
(paren
op_amp
id|all-&gt;info.var
)paren
suffix:semicolon
id|linebytes
op_assign
id|prom_getintdefault
c_func
(paren
id|sdev-&gt;prom_node
comma
l_string|&quot;linebytes&quot;
comma
id|all-&gt;info.var.xres
)paren
suffix:semicolon
id|all-&gt;par.fbsize
op_assign
id|PAGE_ALIGN
c_func
(paren
id|linebytes
op_star
id|all-&gt;info.var.yres
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SPARC32
id|all-&gt;info.screen_base
op_assign
(paren
r_char
op_star
)paren
id|prom_getintdefault
c_func
(paren
id|sdev-&gt;prom_node
comma
l_string|&quot;address&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|all-&gt;info.screen_base
)paren
id|all-&gt;info.screen_base
op_assign
(paren
r_char
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
id|LEO_OFF_SS0
comma
l_int|0x800000
comma
l_string|&quot;leo ram&quot;
)paren
suffix:semicolon
id|all-&gt;par.lc_ss0_usr
op_assign
(paren
r_struct
id|leo_lc_ss0_usr
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
id|LEO_OFF_LC_SS0_USR
comma
l_int|0x1000
comma
l_string|&quot;leolc ss0usr&quot;
)paren
suffix:semicolon
id|all-&gt;par.ld_ss0
op_assign
(paren
r_struct
id|leo_ld_ss0
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
id|LEO_OFF_LD_SS0
comma
l_int|0x1000
comma
l_string|&quot;leold ss0&quot;
)paren
suffix:semicolon
id|all-&gt;par.ld_ss1
op_assign
(paren
r_struct
id|leo_ld_ss1
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
id|LEO_OFF_LD_SS1
comma
l_int|0x1000
comma
l_string|&quot;leold ss1&quot;
)paren
suffix:semicolon
id|all-&gt;par.lx_krn
op_assign
(paren
r_struct
id|leo_lx_krn
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
id|LEO_OFF_LX_KRN
comma
l_int|0x1000
comma
l_string|&quot;leolx krn&quot;
)paren
suffix:semicolon
id|all-&gt;par.cursor
op_assign
(paren
r_struct
id|leo_cursor
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
id|LEO_OFF_LX_CURSOR
comma
r_sizeof
(paren
r_struct
id|leo_cursor
)paren
comma
l_string|&quot;leolx cursor&quot;
)paren
suffix:semicolon
id|all-&gt;info.flags
op_assign
id|FBINFO_DEFAULT
op_or
id|FBINFO_HWACCEL_YPAN
suffix:semicolon
id|all-&gt;info.fbops
op_assign
op_amp
id|leo_ops
suffix:semicolon
id|all-&gt;info.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|all-&gt;info.par
op_assign
op_amp
id|all-&gt;par
suffix:semicolon
id|leo_init_wids
c_func
(paren
op_amp
id|all-&gt;info
)paren
suffix:semicolon
id|leo_init_hw
c_func
(paren
op_amp
id|all-&gt;info
)paren
suffix:semicolon
id|leo_blank
c_func
(paren
l_int|0
comma
op_amp
id|all-&gt;info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fb_alloc_cmap
c_func
(paren
op_amp
id|all-&gt;info.cmap
comma
l_int|256
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;leo: Could not allocate color map.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|all
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|leo_init_fix
c_func
(paren
op_amp
id|all-&gt;info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|all-&gt;info
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;leo: Could not register framebuffer.&bslash;n&quot;
)paren
suffix:semicolon
id|fb_dealloc_cmap
c_func
(paren
op_amp
id|all-&gt;info.cmap
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|all
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|all-&gt;list
comma
op_amp
id|leo_list
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;leo: %s at %lx:%lx&bslash;n&quot;
comma
id|sdev-&gt;prom_name
comma
(paren
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|which_io
comma
(paren
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
)paren
suffix:semicolon
)brace
DECL|function|leo_init
r_int
id|__init
id|leo_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
r_struct
id|sbus_dev
op_star
id|sdev
suffix:semicolon
r_if
c_cond
(paren
id|fb_get_options
c_func
(paren
l_string|&quot;leofb&quot;
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|for_all_sbusdev
c_func
(paren
id|sdev
comma
id|sbus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|sdev-&gt;prom_name
comma
l_string|&quot;leo&quot;
)paren
)paren
id|leo_init_one
c_func
(paren
id|sdev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|leo_exit
r_void
id|__exit
id|leo_exit
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|tmp
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|tmp
comma
op_amp
id|leo_list
)paren
(brace
r_struct
id|all_info
op_star
id|all
op_assign
id|list_entry
c_func
(paren
id|pos
comma
id|typeof
c_func
(paren
op_star
id|all
)paren
comma
id|list
)paren
suffix:semicolon
id|unregister_framebuffer
c_func
(paren
op_amp
id|all-&gt;info
)paren
suffix:semicolon
id|fb_dealloc_cmap
c_func
(paren
op_amp
id|all-&gt;info.cmap
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|all
)paren
suffix:semicolon
)brace
)brace
r_int
id|__init
DECL|function|leo_setup
id|leo_setup
c_func
(paren
r_char
op_star
id|arg
)paren
(brace
multiline_comment|/* No cmdline options yet... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|leo_init
id|module_init
c_func
(paren
id|leo_init
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|variable|leo_exit
id|module_exit
c_func
(paren
id|leo_exit
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;framebuffer driver for LEO chipsets&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David S. Miller &lt;davem@redhat.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
