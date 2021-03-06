multiline_comment|/*&n; *  ATI Frame Buffer Device Driver Core Definitions&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
multiline_comment|/*&n;     *  Elements of the hardware specific atyfb_par structure&n;     */
DECL|struct|crtc
r_struct
id|crtc
(brace
DECL|member|vxres
id|u32
id|vxres
suffix:semicolon
DECL|member|vyres
id|u32
id|vyres
suffix:semicolon
DECL|member|xoffset
id|u32
id|xoffset
suffix:semicolon
DECL|member|yoffset
id|u32
id|yoffset
suffix:semicolon
DECL|member|bpp
id|u32
id|bpp
suffix:semicolon
DECL|member|h_tot_disp
id|u32
id|h_tot_disp
suffix:semicolon
DECL|member|h_sync_strt_wid
id|u32
id|h_sync_strt_wid
suffix:semicolon
DECL|member|v_tot_disp
id|u32
id|v_tot_disp
suffix:semicolon
DECL|member|v_sync_strt_wid
id|u32
id|v_sync_strt_wid
suffix:semicolon
DECL|member|vline_crnt_vline
id|u32
id|vline_crnt_vline
suffix:semicolon
DECL|member|off_pitch
id|u32
id|off_pitch
suffix:semicolon
DECL|member|gen_cntl
id|u32
id|gen_cntl
suffix:semicolon
DECL|member|dp_pix_width
id|u32
id|dp_pix_width
suffix:semicolon
multiline_comment|/* acceleration */
DECL|member|dp_chain_mask
id|u32
id|dp_chain_mask
suffix:semicolon
multiline_comment|/* acceleration */
macro_line|#ifdef CONFIG_FB_ATY_GENERIC_LCD
DECL|member|horz_stretching
id|u32
id|horz_stretching
suffix:semicolon
DECL|member|vert_stretching
id|u32
id|vert_stretching
suffix:semicolon
DECL|member|ext_vert_stretch
id|u32
id|ext_vert_stretch
suffix:semicolon
DECL|member|shadow_h_tot_disp
id|u32
id|shadow_h_tot_disp
suffix:semicolon
DECL|member|shadow_h_sync_strt_wid
id|u32
id|shadow_h_sync_strt_wid
suffix:semicolon
DECL|member|shadow_v_tot_disp
id|u32
id|shadow_v_tot_disp
suffix:semicolon
DECL|member|shadow_v_sync_strt_wid
id|u32
id|shadow_v_sync_strt_wid
suffix:semicolon
DECL|member|lcd_gen_cntl
id|u32
id|lcd_gen_cntl
suffix:semicolon
DECL|member|lcd_config_panel
id|u32
id|lcd_config_panel
suffix:semicolon
DECL|member|lcd_index
id|u32
id|lcd_index
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|aty_interrupt
r_struct
id|aty_interrupt
(brace
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|pan_display
r_int
id|pan_display
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pll_info
r_struct
id|pll_info
(brace
DECL|member|pll_max
r_int
id|pll_max
suffix:semicolon
DECL|member|pll_min
r_int
id|pll_min
suffix:semicolon
DECL|member|sclk
DECL|member|mclk
DECL|member|mclk_pm
DECL|member|xclk
r_int
id|sclk
comma
id|mclk
comma
id|mclk_pm
comma
id|xclk
suffix:semicolon
DECL|member|ref_div
r_int
id|ref_div
suffix:semicolon
DECL|member|ref_clk
r_int
id|ref_clk
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|unknown1
id|u16
id|unknown1
suffix:semicolon
DECL|member|PCLK_min_freq
id|u16
id|PCLK_min_freq
suffix:semicolon
DECL|member|PCLK_max_freq
id|u16
id|PCLK_max_freq
suffix:semicolon
DECL|member|unknown2
id|u16
id|unknown2
suffix:semicolon
DECL|member|ref_freq
id|u16
id|ref_freq
suffix:semicolon
DECL|member|ref_divider
id|u16
id|ref_divider
suffix:semicolon
DECL|member|unknown3
id|u16
id|unknown3
suffix:semicolon
DECL|member|MCLK_pwd
id|u16
id|MCLK_pwd
suffix:semicolon
DECL|member|MCLK_max_freq
id|u16
id|MCLK_max_freq
suffix:semicolon
DECL|member|XCLK_max_freq
id|u16
id|XCLK_max_freq
suffix:semicolon
DECL|member|SCLK_freq
id|u16
id|SCLK_freq
suffix:semicolon
DECL|typedef|PLL_BLOCK_MACH64
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|PLL_BLOCK_MACH64
suffix:semicolon
DECL|struct|pll_514
r_struct
id|pll_514
(brace
DECL|member|m
id|u8
id|m
suffix:semicolon
DECL|member|n
id|u8
id|n
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pll_18818
r_struct
id|pll_18818
(brace
DECL|member|program_bits
id|u32
id|program_bits
suffix:semicolon
DECL|member|locationAddr
id|u32
id|locationAddr
suffix:semicolon
DECL|member|period_in_ps
id|u32
id|period_in_ps
suffix:semicolon
DECL|member|post_divider
id|u32
id|post_divider
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pll_ct
r_struct
id|pll_ct
(brace
DECL|member|pll_ref_div
id|u8
id|pll_ref_div
suffix:semicolon
DECL|member|pll_gen_cntl
id|u8
id|pll_gen_cntl
suffix:semicolon
DECL|member|mclk_fb_div
id|u8
id|mclk_fb_div
suffix:semicolon
DECL|member|mclk_fb_mult
id|u8
id|mclk_fb_mult
suffix:semicolon
multiline_comment|/* 2 ro 4 */
DECL|member|sclk_fb_div
id|u8
id|sclk_fb_div
suffix:semicolon
DECL|member|pll_vclk_cntl
id|u8
id|pll_vclk_cntl
suffix:semicolon
DECL|member|vclk_post_div
id|u8
id|vclk_post_div
suffix:semicolon
DECL|member|vclk_fb_div
id|u8
id|vclk_fb_div
suffix:semicolon
DECL|member|pll_ext_cntl
id|u8
id|pll_ext_cntl
suffix:semicolon
DECL|member|ext_vpll_cntl
id|u8
id|ext_vpll_cntl
suffix:semicolon
DECL|member|spll_cntl2
id|u8
id|spll_cntl2
suffix:semicolon
DECL|member|dsp_config
id|u32
id|dsp_config
suffix:semicolon
multiline_comment|/* Mach64 GTB DSP */
DECL|member|dsp_on_off
id|u32
id|dsp_on_off
suffix:semicolon
multiline_comment|/* Mach64 GTB DSP */
DECL|member|dsp_loop_latency
id|u32
id|dsp_loop_latency
suffix:semicolon
DECL|member|fifo_size
id|u32
id|fifo_size
suffix:semicolon
DECL|member|xclkpagefaultdelay
id|u32
id|xclkpagefaultdelay
suffix:semicolon
DECL|member|xclkmaxrasdelay
id|u32
id|xclkmaxrasdelay
suffix:semicolon
DECL|member|xclk_ref_div
id|u8
id|xclk_ref_div
suffix:semicolon
DECL|member|xclk_post_div
id|u8
id|xclk_post_div
suffix:semicolon
DECL|member|mclk_post_div_real
id|u8
id|mclk_post_div_real
suffix:semicolon
DECL|member|xclk_post_div_real
id|u8
id|xclk_post_div_real
suffix:semicolon
DECL|member|vclk_post_div_real
id|u8
id|vclk_post_div_real
suffix:semicolon
DECL|member|features
id|u8
id|features
suffix:semicolon
macro_line|#ifdef CONFIG_FB_ATY_GENERIC_LCD
DECL|member|xres
id|u32
id|xres
suffix:semicolon
multiline_comment|/* use for LCD stretching/scaling */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n;&t;for pll_ct.features&n;*/
DECL|macro|DONT_USE_SPLL
mdefine_line|#define DONT_USE_SPLL 0x1
DECL|macro|DONT_USE_XDLL
mdefine_line|#define DONT_USE_XDLL 0x2
DECL|macro|USE_CPUCLK
mdefine_line|#define USE_CPUCLK    0x4
DECL|macro|POWERDOWN_PLL
mdefine_line|#define POWERDOWN_PLL 0x8
DECL|union|aty_pll
r_union
id|aty_pll
(brace
DECL|member|ct
r_struct
id|pll_ct
id|ct
suffix:semicolon
DECL|member|ibm514
r_struct
id|pll_514
id|ibm514
suffix:semicolon
DECL|member|ics2595
r_struct
id|pll_18818
id|ics2595
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;     *  The hardware parameters for each card&n;     */
DECL|struct|atyfb_par
r_struct
id|atyfb_par
(brace
DECL|member|aty_cmap_regs
r_struct
id|aty_cmap_regs
id|__iomem
op_star
id|aty_cmap_regs
suffix:semicolon
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|palette
r_struct
(brace
id|u8
id|red
comma
id|green
comma
id|blue
suffix:semicolon
)brace
id|palette
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|dac_ops
r_const
r_struct
id|aty_dac_ops
op_star
id|dac_ops
suffix:semicolon
DECL|member|pll_ops
r_const
r_struct
id|aty_pll_ops
op_star
id|pll_ops
suffix:semicolon
DECL|member|ati_regbase
r_void
id|__iomem
op_star
id|ati_regbase
suffix:semicolon
DECL|member|clk_wr_offset
r_int
r_int
id|clk_wr_offset
suffix:semicolon
multiline_comment|/* meaning overloaded, clock id by CT */
DECL|member|crtc
r_struct
id|crtc
id|crtc
suffix:semicolon
DECL|member|pll
r_union
id|aty_pll
id|pll
suffix:semicolon
DECL|member|pll_limits
r_struct
id|pll_info
id|pll_limits
suffix:semicolon
DECL|member|features
id|u32
id|features
suffix:semicolon
DECL|member|ref_clk_per
id|u32
id|ref_clk_per
suffix:semicolon
DECL|member|pll_per
id|u32
id|pll_per
suffix:semicolon
DECL|member|mclk_per
id|u32
id|mclk_per
suffix:semicolon
DECL|member|xclk_per
id|u32
id|xclk_per
suffix:semicolon
DECL|member|bus_type
id|u8
id|bus_type
suffix:semicolon
DECL|member|ram_type
id|u8
id|ram_type
suffix:semicolon
DECL|member|mem_refresh_rate
id|u8
id|mem_refresh_rate
suffix:semicolon
DECL|member|pci_id
id|u16
id|pci_id
suffix:semicolon
DECL|member|accel_flags
id|u32
id|accel_flags
suffix:semicolon
DECL|member|blitter_may_be_busy
r_int
id|blitter_may_be_busy
suffix:semicolon
DECL|member|asleep
r_int
id|asleep
suffix:semicolon
DECL|member|lock_blank
r_int
id|lock_blank
suffix:semicolon
DECL|member|res_start
r_int
r_int
id|res_start
suffix:semicolon
DECL|member|res_size
r_int
r_int
id|res_size
suffix:semicolon
macro_line|#ifdef __sparc__
DECL|member|mmap_map
r_struct
id|pci_mmap_map
op_star
id|mmap_map
suffix:semicolon
DECL|member|mmaped
id|u8
id|mmaped
suffix:semicolon
macro_line|#endif
DECL|member|open
r_int
id|open
suffix:semicolon
macro_line|#ifdef CONFIG_FB_ATY_GENERIC_LCD
DECL|member|bios_base_phys
r_int
r_int
id|bios_base_phys
suffix:semicolon
DECL|member|bios_base
r_int
r_int
id|bios_base
suffix:semicolon
DECL|member|lcd_table
r_int
r_int
id|lcd_table
suffix:semicolon
DECL|member|lcd_width
id|u16
id|lcd_width
suffix:semicolon
DECL|member|lcd_height
id|u16
id|lcd_height
suffix:semicolon
DECL|member|lcd_pixclock
id|u32
id|lcd_pixclock
suffix:semicolon
DECL|member|lcd_refreshrate
id|u16
id|lcd_refreshrate
suffix:semicolon
DECL|member|lcd_htotal
id|u16
id|lcd_htotal
suffix:semicolon
DECL|member|lcd_hdisp
id|u16
id|lcd_hdisp
suffix:semicolon
DECL|member|lcd_hsync_dly
id|u16
id|lcd_hsync_dly
suffix:semicolon
DECL|member|lcd_hsync_len
id|u16
id|lcd_hsync_len
suffix:semicolon
DECL|member|lcd_vtotal
id|u16
id|lcd_vtotal
suffix:semicolon
DECL|member|lcd_vdisp
id|u16
id|lcd_vdisp
suffix:semicolon
DECL|member|lcd_vsync_len
id|u16
id|lcd_vsync_len
suffix:semicolon
DECL|member|lcd_right_margin
id|u16
id|lcd_right_margin
suffix:semicolon
DECL|member|lcd_lower_margin
id|u16
id|lcd_lower_margin
suffix:semicolon
DECL|member|lcd_hblank_len
id|u16
id|lcd_hblank_len
suffix:semicolon
DECL|member|lcd_vblank_len
id|u16
id|lcd_vblank_len
suffix:semicolon
macro_line|#endif
DECL|member|aux_start
r_int
r_int
id|aux_start
suffix:semicolon
multiline_comment|/* auxiliary aperture */
DECL|member|aux_size
r_int
r_int
id|aux_size
suffix:semicolon
DECL|member|vblank
r_struct
id|aty_interrupt
id|vblank
suffix:semicolon
DECL|member|irq_flags
r_int
r_int
id|irq_flags
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|int_lock
id|spinlock_t
id|int_lock
suffix:semicolon
macro_line|#ifdef CONFIG_MTRR
DECL|member|mtrr_aper
r_int
id|mtrr_aper
suffix:semicolon
DECL|member|mtrr_reg
r_int
id|mtrr_reg
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n;     *  ATI Mach64 features&n;     */
DECL|macro|M64_HAS
mdefine_line|#define M64_HAS(feature)&t;((par)-&gt;features &amp; (M64F_##feature))
DECL|macro|M64F_RESET_3D
mdefine_line|#define M64F_RESET_3D&t;&t;0x00000001
DECL|macro|M64F_MAGIC_FIFO
mdefine_line|#define M64F_MAGIC_FIFO&t;&t;0x00000002
DECL|macro|M64F_GTB_DSP
mdefine_line|#define M64F_GTB_DSP&t;&t;0x00000004
DECL|macro|M64F_FIFO_32
mdefine_line|#define M64F_FIFO_32&t;&t;0x00000008
DECL|macro|M64F_SDRAM_MAGIC_PLL
mdefine_line|#define M64F_SDRAM_MAGIC_PLL&t;0x00000010
DECL|macro|M64F_MAGIC_POSTDIV
mdefine_line|#define M64F_MAGIC_POSTDIV&t;0x00000020
DECL|macro|M64F_INTEGRATED
mdefine_line|#define M64F_INTEGRATED&t;&t;0x00000040
DECL|macro|M64F_CT_BUS
mdefine_line|#define M64F_CT_BUS&t;&t;0x00000080
DECL|macro|M64F_VT_BUS
mdefine_line|#define M64F_VT_BUS&t;&t;0x00000100
DECL|macro|M64F_MOBIL_BUS
mdefine_line|#define M64F_MOBIL_BUS&t;&t;0x00000200
DECL|macro|M64F_GX
mdefine_line|#define M64F_GX&t;&t;&t;0x00000400
DECL|macro|M64F_CT
mdefine_line|#define M64F_CT&t;&t;&t;0x00000800
DECL|macro|M64F_VT
mdefine_line|#define M64F_VT&t;&t;&t;0x00001000
DECL|macro|M64F_GT
mdefine_line|#define M64F_GT&t;&t;&t;0x00002000
DECL|macro|M64F_MAGIC_VRAM_SIZE
mdefine_line|#define M64F_MAGIC_VRAM_SIZE&t;0x00004000
DECL|macro|M64F_G3_PB_1_1
mdefine_line|#define M64F_G3_PB_1_1&t;&t;0x00008000
DECL|macro|M64F_G3_PB_1024x768
mdefine_line|#define M64F_G3_PB_1024x768&t;0x00010000
DECL|macro|M64F_EXTRA_BRIGHT
mdefine_line|#define M64F_EXTRA_BRIGHT&t;0x00020000
DECL|macro|M64F_LT_LCD_REGS
mdefine_line|#define M64F_LT_LCD_REGS&t;0x00040000
DECL|macro|M64F_XL_DLL
mdefine_line|#define M64F_XL_DLL&t;&t;0x00080000
DECL|macro|M64F_MFB_FORCE_4
mdefine_line|#define M64F_MFB_FORCE_4&t;0x00100000
DECL|macro|M64F_HW_TRIPLE
mdefine_line|#define M64F_HW_TRIPLE&t;&t;0x00200000
multiline_comment|/*&n;     *  Register access&n;     */
DECL|function|aty_ld_le32
r_static
r_inline
id|u32
id|aty_ld_le32
c_func
(paren
r_int
id|regindex
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
(brace
multiline_comment|/* Hack for bloc 1, should be cleanly optimized by compiler */
r_if
c_cond
(paren
id|regindex
op_ge
l_int|0x400
)paren
id|regindex
op_sub_assign
l_int|0x800
suffix:semicolon
macro_line|#ifdef CONFIG_ATARI
r_return
id|in_le32
c_func
(paren
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|par-&gt;ati_regbase
op_plus
id|regindex
)paren
)paren
suffix:semicolon
macro_line|#else
r_return
id|readl
c_func
(paren
id|par-&gt;ati_regbase
op_plus
id|regindex
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|aty_st_le32
r_static
r_inline
r_void
id|aty_st_le32
c_func
(paren
r_int
id|regindex
comma
id|u32
id|val
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
(brace
multiline_comment|/* Hack for bloc 1, should be cleanly optimized by compiler */
r_if
c_cond
(paren
id|regindex
op_ge
l_int|0x400
)paren
id|regindex
op_sub_assign
l_int|0x800
suffix:semicolon
macro_line|#ifdef CONFIG_ATARI
id|out_le32
c_func
(paren
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|par-&gt;ati_regbase
op_plus
id|regindex
)paren
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|writel
c_func
(paren
id|val
comma
id|par-&gt;ati_regbase
op_plus
id|regindex
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|aty_st_le16
r_static
r_inline
r_void
id|aty_st_le16
c_func
(paren
r_int
id|regindex
comma
id|u16
id|val
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
(brace
multiline_comment|/* Hack for bloc 1, should be cleanly optimized by compiler */
r_if
c_cond
(paren
id|regindex
op_ge
l_int|0x400
)paren
id|regindex
op_sub_assign
l_int|0x800
suffix:semicolon
macro_line|#ifdef CONFIG_ATARI
id|out_le16
c_func
(paren
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|par-&gt;ati_regbase
op_plus
id|regindex
)paren
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|writel
c_func
(paren
id|val
comma
id|par-&gt;ati_regbase
op_plus
id|regindex
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|aty_ld_8
r_static
r_inline
id|u8
id|aty_ld_8
c_func
(paren
r_int
id|regindex
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
(brace
multiline_comment|/* Hack for bloc 1, should be cleanly optimized by compiler */
r_if
c_cond
(paren
id|regindex
op_ge
l_int|0x400
)paren
id|regindex
op_sub_assign
l_int|0x800
suffix:semicolon
macro_line|#ifdef CONFIG_ATARI
r_return
id|in_8
c_func
(paren
id|par-&gt;ati_regbase
op_plus
id|regindex
)paren
suffix:semicolon
macro_line|#else
r_return
id|readb
c_func
(paren
id|par-&gt;ati_regbase
op_plus
id|regindex
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|aty_st_8
r_static
r_inline
r_void
id|aty_st_8
c_func
(paren
r_int
id|regindex
comma
id|u8
id|val
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
(brace
multiline_comment|/* Hack for bloc 1, should be cleanly optimized by compiler */
r_if
c_cond
(paren
id|regindex
op_ge
l_int|0x400
)paren
id|regindex
op_sub_assign
l_int|0x800
suffix:semicolon
macro_line|#ifdef CONFIG_ATARI
id|out_8
c_func
(paren
id|par-&gt;ati_regbase
op_plus
id|regindex
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|writeb
c_func
(paren
id|val
comma
id|par-&gt;ati_regbase
op_plus
id|regindex
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if defined(CONFIG_PM) || defined(CONFIG_PMAC_BACKLIGHT) || defined (CONFIG_FB_ATY_GENERIC_LCD)
r_extern
r_void
id|aty_st_lcd
c_func
(paren
r_int
id|index
comma
id|u32
id|val
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
suffix:semicolon
r_extern
id|u32
id|aty_ld_lcd
c_func
(paren
r_int
id|index
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;     *  DAC operations&n;     */
DECL|struct|aty_dac_ops
r_struct
id|aty_dac_ops
(brace
DECL|member|set_dac
r_int
(paren
op_star
id|set_dac
)paren
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_union
id|aty_pll
op_star
id|pll
comma
id|u32
id|bpp
comma
id|u32
id|accel
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_const
r_struct
id|aty_dac_ops
id|aty_dac_ibm514
suffix:semicolon
multiline_comment|/* IBM RGB514 */
r_extern
r_const
r_struct
id|aty_dac_ops
id|aty_dac_ati68860b
suffix:semicolon
multiline_comment|/* ATI 68860-B */
r_extern
r_const
r_struct
id|aty_dac_ops
id|aty_dac_att21c498
suffix:semicolon
multiline_comment|/* AT&amp;T 21C498 */
r_extern
r_const
r_struct
id|aty_dac_ops
id|aty_dac_unsupported
suffix:semicolon
multiline_comment|/* unsupported */
r_extern
r_const
r_struct
id|aty_dac_ops
id|aty_dac_ct
suffix:semicolon
multiline_comment|/* Integrated */
multiline_comment|/*&n;     *  Clock operations&n;     */
DECL|struct|aty_pll_ops
r_struct
id|aty_pll_ops
(brace
DECL|member|var_to_pll
r_int
(paren
op_star
id|var_to_pll
)paren
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
id|u32
id|vclk_per
comma
id|u32
id|bpp
comma
r_union
id|aty_pll
op_star
id|pll
)paren
suffix:semicolon
DECL|member|pll_to_var
id|u32
(paren
op_star
id|pll_to_var
)paren
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_union
id|aty_pll
op_star
id|pll
)paren
suffix:semicolon
DECL|member|set_pll
r_void
(paren
op_star
id|set_pll
)paren
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_union
id|aty_pll
op_star
id|pll
)paren
suffix:semicolon
DECL|member|get_pll
r_void
(paren
op_star
id|get_pll
)paren
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
r_union
id|aty_pll
op_star
id|pll
)paren
suffix:semicolon
DECL|member|init_pll
r_int
(paren
op_star
id|init_pll
)paren
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
r_union
id|aty_pll
op_star
id|pll
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_const
r_struct
id|aty_pll_ops
id|aty_pll_ati18818_1
suffix:semicolon
multiline_comment|/* ATI 18818 */
r_extern
r_const
r_struct
id|aty_pll_ops
id|aty_pll_stg1703
suffix:semicolon
multiline_comment|/* STG 1703 */
r_extern
r_const
r_struct
id|aty_pll_ops
id|aty_pll_ch8398
suffix:semicolon
multiline_comment|/* Chrontel 8398 */
r_extern
r_const
r_struct
id|aty_pll_ops
id|aty_pll_att20c408
suffix:semicolon
multiline_comment|/* AT&amp;T 20C408 */
r_extern
r_const
r_struct
id|aty_pll_ops
id|aty_pll_ibm514
suffix:semicolon
multiline_comment|/* IBM RGB514 */
r_extern
r_const
r_struct
id|aty_pll_ops
id|aty_pll_unsupported
suffix:semicolon
multiline_comment|/* unsupported */
r_extern
r_const
r_struct
id|aty_pll_ops
id|aty_pll_ct
suffix:semicolon
multiline_comment|/* Integrated */
r_extern
r_void
id|aty_set_pll_ct
c_func
(paren
r_const
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_union
id|aty_pll
op_star
id|pll
)paren
suffix:semicolon
r_extern
id|u8
id|aty_ld_pll_ct
c_func
(paren
r_int
id|offset
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Hardware cursor support&n;     */
r_extern
r_int
id|aty_init_cursor
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Hardware acceleration&n;     */
DECL|function|wait_for_fifo
r_static
r_inline
r_void
id|wait_for_fifo
c_func
(paren
id|u16
id|entries
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
(brace
r_while
c_loop
(paren
(paren
id|aty_ld_le32
c_func
(paren
id|FIFO_STAT
comma
id|par
)paren
op_amp
l_int|0xffff
)paren
OG
(paren
(paren
id|u32
)paren
(paren
l_int|0x8000
op_rshift
id|entries
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|wait_for_idle
r_static
r_inline
r_void
id|wait_for_idle
c_func
(paren
r_struct
id|atyfb_par
op_star
id|par
)paren
(brace
id|wait_for_fifo
c_func
(paren
l_int|16
comma
id|par
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|aty_ld_le32
c_func
(paren
id|GUI_STAT
comma
id|par
)paren
op_amp
l_int|1
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|par-&gt;blitter_may_be_busy
op_assign
l_int|0
suffix:semicolon
)brace
r_extern
r_void
id|aty_reset_engine
c_func
(paren
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
suffix:semicolon
r_extern
r_void
id|aty_init_engine
c_func
(paren
r_struct
id|atyfb_par
op_star
id|par
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|atyfb_xl_init
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|aty_st_pll_ct
c_func
(paren
r_int
id|offset
comma
id|u8
id|val
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
suffix:semicolon
r_extern
id|u8
id|aty_ld_pll_ct
c_func
(paren
r_int
id|offset
comma
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
suffix:semicolon
eof
