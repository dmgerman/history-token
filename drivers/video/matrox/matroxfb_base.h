multiline_comment|/*&n; *&n; * Hardware accelerated Matrox Millennium I, II, Mystique, G100, G200, G400 and G450&n; *&n; * (c) 1998-2002 Petr Vandrovec &lt;vandrove@vc.cvut.cz&gt;&n; *&n; */
macro_line|#ifndef __MATROXFB_H__
DECL|macro|__MATROXFB_H__
mdefine_line|#define __MATROXFB_H__
multiline_comment|/* general, but fairly heavy, debugging */
DECL|macro|MATROXFB_DEBUG
macro_line|#undef MATROXFB_DEBUG
multiline_comment|/* heavy debugging: */
multiline_comment|/* -- logs putc[s], so everytime a char is displayed, it&squot;s logged */
DECL|macro|MATROXFB_DEBUG_HEAVY
macro_line|#undef MATROXFB_DEBUG_HEAVY
multiline_comment|/* This one _could_ cause infinite loops */
multiline_comment|/* It _does_ cause lots and lots of messages during idle loops */
DECL|macro|MATROXFB_DEBUG_LOOP
macro_line|#undef MATROXFB_DEBUG_LOOP
multiline_comment|/* Debug register calls, too? */
DECL|macro|MATROXFB_DEBUG_REG
macro_line|#undef MATROXFB_DEBUG_REG
multiline_comment|/* Guard accelerator accesses with spin_lock_irqsave... */
DECL|macro|MATROXFB_USE_SPINLOCKS
macro_line|#undef MATROXFB_USE_SPINLOCKS
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#ifdef CONFIG_MTRR
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#endif
macro_line|#include &quot;../console/fbcon.h&quot;
macro_line|#if defined(CONFIG_PPC_PMAC)
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &quot;../macmodes.h&quot;
macro_line|#endif
multiline_comment|/* always compile support for 32MB... It cost almost nothing */
DECL|macro|CONFIG_FB_MATROX_32MB
mdefine_line|#define CONFIG_FB_MATROX_32MB
macro_line|#ifdef MATROXFB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x)&t;&t;printk(KERN_DEBUG &quot;matroxfb: %s&bslash;n&quot;, (x));
macro_line|#ifdef MATROXFB_DEBUG_HEAVY
DECL|macro|DBG_HEAVY
mdefine_line|#define DBG_HEAVY(x)&t;DBG(x)
macro_line|#else /* MATROXFB_DEBUG_HEAVY */
DECL|macro|DBG_HEAVY
mdefine_line|#define DBG_HEAVY(x)&t;/* DBG_HEAVY */
macro_line|#endif /* MATROXFB_DEBUG_HEAVY */
macro_line|#ifdef MATROXFB_DEBUG_LOOP
DECL|macro|DBG_LOOP
mdefine_line|#define DBG_LOOP(x)&t;DBG(x)
macro_line|#else /* MATROXFB_DEBUG_LOOP */
DECL|macro|DBG_LOOP
mdefine_line|#define DBG_LOOP(x)&t;/* DBG_LOOP */
macro_line|#endif /* MATROXFB_DEBUG_LOOP */
macro_line|#ifdef MATROXFB_DEBUG_REG
DECL|macro|DBG_REG
mdefine_line|#define DBG_REG(x)&t;DBG(x)
macro_line|#else /* MATROXFB_DEBUG_REG */
DECL|macro|DBG_REG
mdefine_line|#define DBG_REG(x)&t;/* DBG_REG */
macro_line|#endif /* MATROXFB_DEBUG_REG */
macro_line|#else /* MATROXFB_DEBUG */
DECL|macro|DBG
mdefine_line|#define DBG(x)&t;&t;/* DBG */
DECL|macro|DBG_HEAVY
mdefine_line|#define DBG_HEAVY(x)&t;/* DBG_HEAVY */
DECL|macro|DBG_REG
mdefine_line|#define DBG_REG(x)&t;/* DBG_REG */
DECL|macro|DBG_LOOP
mdefine_line|#define DBG_LOOP(x)&t;/* DBG_LOOP */
macro_line|#endif /* MATROXFB_DEBUG */
macro_line|#ifdef DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(X...)&t;printk(X)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(X...)
macro_line|#endif
macro_line|#ifndef PCI_SS_VENDOR_ID_SIEMENS_NIXDORF
DECL|macro|PCI_SS_VENDOR_ID_SIEMENS_NIXDORF
mdefine_line|#define PCI_SS_VENDOR_ID_SIEMENS_NIXDORF&t;0x110A
macro_line|#endif
macro_line|#ifndef PCI_SS_VENDOR_ID_MATROX
DECL|macro|PCI_SS_VENDOR_ID_MATROX
mdefine_line|#define PCI_SS_VENDOR_ID_MATROX&t;&t;PCI_VENDOR_ID_MATROX
macro_line|#endif
macro_line|#ifndef PCI_SS_ID_MATROX_PRODUCTIVA_G100_AGP
DECL|macro|PCI_SS_ID_MATROX_GENERIC
mdefine_line|#define PCI_SS_ID_MATROX_GENERIC&t;&t;0xFF00
DECL|macro|PCI_SS_ID_MATROX_PRODUCTIVA_G100_AGP
mdefine_line|#define PCI_SS_ID_MATROX_PRODUCTIVA_G100_AGP&t;0xFF01
DECL|macro|PCI_SS_ID_MATROX_MYSTIQUE_G200_AGP
mdefine_line|#define PCI_SS_ID_MATROX_MYSTIQUE_G200_AGP&t;0xFF02
DECL|macro|PCI_SS_ID_MATROX_MILLENIUM_G200_AGP
mdefine_line|#define PCI_SS_ID_MATROX_MILLENIUM_G200_AGP&t;0xFF03
DECL|macro|PCI_SS_ID_MATROX_MARVEL_G200_AGP
mdefine_line|#define PCI_SS_ID_MATROX_MARVEL_G200_AGP&t;0xFF04
DECL|macro|PCI_SS_ID_MATROX_MGA_G100_PCI
mdefine_line|#define PCI_SS_ID_MATROX_MGA_G100_PCI&t;&t;0xFF05
DECL|macro|PCI_SS_ID_MATROX_MGA_G100_AGP
mdefine_line|#define PCI_SS_ID_MATROX_MGA_G100_AGP&t;&t;0x1001
DECL|macro|PCI_SS_ID_MATROX_MILLENNIUM_G400_MAX_AGP
mdefine_line|#define PCI_SS_ID_MATROX_MILLENNIUM_G400_MAX_AGP&t;0x2179
DECL|macro|PCI_SS_ID_SIEMENS_MGA_G100_AGP
mdefine_line|#define PCI_SS_ID_SIEMENS_MGA_G100_AGP&t;&t;0x001E /* 30 */
DECL|macro|PCI_SS_ID_SIEMENS_MGA_G200_AGP
mdefine_line|#define PCI_SS_ID_SIEMENS_MGA_G200_AGP&t;&t;0x0032 /* 50 */
macro_line|#endif
DECL|macro|MX_VISUAL_TRUECOLOR
mdefine_line|#define MX_VISUAL_TRUECOLOR&t;FB_VISUAL_DIRECTCOLOR
DECL|macro|MX_VISUAL_DIRECTCOLOR
mdefine_line|#define MX_VISUAL_DIRECTCOLOR&t;FB_VISUAL_TRUECOLOR
DECL|macro|MX_VISUAL_PSEUDOCOLOR
mdefine_line|#define MX_VISUAL_PSEUDOCOLOR&t;FB_VISUAL_PSEUDOCOLOR
DECL|macro|CNVT_TOHW
mdefine_line|#define CNVT_TOHW(val,width) ((((val)&lt;&lt;(width))+0x7FFF-(val))&gt;&gt;16)
multiline_comment|/* G-series and Mystique have (almost) same DAC */
DECL|macro|NEED_DAC1064
macro_line|#undef NEED_DAC1064
macro_line|#if defined(CONFIG_FB_MATROX_MYSTIQUE) || defined(CONFIG_FB_MATROX_G)
DECL|macro|NEED_DAC1064
mdefine_line|#define NEED_DAC1064 1
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|vaddr
r_void
id|__iomem
op_star
id|vaddr
suffix:semicolon
DECL|typedef|vaddr_t
)brace
id|vaddr_t
suffix:semicolon
DECL|function|mga_readb
r_static
r_inline
r_int
r_int
id|mga_readb
c_func
(paren
id|vaddr_t
id|va
comma
r_int
r_int
id|offs
)paren
(brace
r_return
id|readb
c_func
(paren
id|va.vaddr
op_plus
id|offs
)paren
suffix:semicolon
)brace
DECL|function|mga_writeb
r_static
r_inline
r_void
id|mga_writeb
c_func
(paren
id|vaddr_t
id|va
comma
r_int
r_int
id|offs
comma
id|u_int8_t
id|value
)paren
(brace
id|writeb
c_func
(paren
id|value
comma
id|va.vaddr
op_plus
id|offs
)paren
suffix:semicolon
)brace
DECL|function|mga_writew
r_static
r_inline
r_void
id|mga_writew
c_func
(paren
id|vaddr_t
id|va
comma
r_int
r_int
id|offs
comma
id|u_int16_t
id|value
)paren
(brace
id|writew
c_func
(paren
id|value
comma
id|va.vaddr
op_plus
id|offs
)paren
suffix:semicolon
)brace
DECL|function|mga_readl
r_static
r_inline
id|u_int32_t
id|mga_readl
c_func
(paren
id|vaddr_t
id|va
comma
r_int
r_int
id|offs
)paren
(brace
r_return
id|readl
c_func
(paren
id|va.vaddr
op_plus
id|offs
)paren
suffix:semicolon
)brace
DECL|function|mga_writel
r_static
r_inline
r_void
id|mga_writel
c_func
(paren
id|vaddr_t
id|va
comma
r_int
r_int
id|offs
comma
id|u_int32_t
id|value
)paren
(brace
id|writel
c_func
(paren
id|value
comma
id|va.vaddr
op_plus
id|offs
)paren
suffix:semicolon
)brace
DECL|function|mga_memcpy_toio
r_static
r_inline
r_void
id|mga_memcpy_toio
c_func
(paren
id|vaddr_t
id|va
comma
r_const
r_void
op_star
id|src
comma
r_int
id|len
)paren
(brace
macro_line|#if defined(__alpha__) || defined(__i386__) || defined(__x86_64__)
multiline_comment|/*&n;&t; * memcpy_toio works for us if:&n;&t; *  (1) Copies data as 32bit quantities, not byte after byte,&n;&t; *  (2) Performs LE ordered stores, and&n;&t; *  (3) It copes with unaligned source (destination is guaranteed to be page&n;&t; *      aligned and length is guaranteed to be multiple of 4).&n;&t; */
id|memcpy_toio
c_func
(paren
id|va.vaddr
comma
id|src
comma
id|len
)paren
suffix:semicolon
macro_line|#else
id|u_int32_t
id|__iomem
op_star
id|addr
op_assign
id|va.vaddr
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|src
op_amp
l_int|3
)paren
(brace
r_while
c_loop
(paren
id|len
op_ge
l_int|4
)paren
(brace
id|writel
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|u32
op_star
)paren
id|src
)paren
comma
id|addr
)paren
suffix:semicolon
id|addr
op_increment
suffix:semicolon
id|len
op_sub_assign
l_int|4
suffix:semicolon
id|src
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|len
op_ge
l_int|4
)paren
(brace
id|writel
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|src
comma
id|addr
)paren
suffix:semicolon
id|addr
op_increment
suffix:semicolon
id|len
op_sub_assign
l_int|4
suffix:semicolon
id|src
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
DECL|function|vaddr_add
r_static
r_inline
r_void
id|vaddr_add
c_func
(paren
id|vaddr_t
op_star
id|va
comma
r_int
r_int
id|offs
)paren
(brace
id|va-&gt;vaddr
op_add_assign
id|offs
suffix:semicolon
)brace
DECL|function|vaddr_va
r_static
r_inline
r_void
id|__iomem
op_star
id|vaddr_va
c_func
(paren
id|vaddr_t
id|va
)paren
(brace
r_return
id|va.vaddr
suffix:semicolon
)brace
DECL|macro|MGA_IOREMAP_NORMAL
mdefine_line|#define MGA_IOREMAP_NORMAL&t;0
DECL|macro|MGA_IOREMAP_NOCACHE
mdefine_line|#define MGA_IOREMAP_NOCACHE&t;1
DECL|macro|MGA_IOREMAP_FB
mdefine_line|#define MGA_IOREMAP_FB&t;&t;MGA_IOREMAP_NOCACHE
DECL|macro|MGA_IOREMAP_MMIO
mdefine_line|#define MGA_IOREMAP_MMIO&t;MGA_IOREMAP_NOCACHE
DECL|function|mga_ioremap
r_static
r_inline
r_int
id|mga_ioremap
c_func
(paren
r_int
r_int
id|phys
comma
r_int
r_int
id|size
comma
r_int
id|flags
comma
id|vaddr_t
op_star
id|virt
)paren
(brace
r_if
c_cond
(paren
id|flags
op_amp
id|MGA_IOREMAP_NOCACHE
)paren
id|virt-&gt;vaddr
op_assign
id|ioremap_nocache
c_func
(paren
id|phys
comma
id|size
)paren
suffix:semicolon
r_else
id|virt-&gt;vaddr
op_assign
id|ioremap
c_func
(paren
id|phys
comma
id|size
)paren
suffix:semicolon
r_return
(paren
id|virt-&gt;vaddr
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 0, !0... 0, error_code in future */
)brace
DECL|function|mga_iounmap
r_static
r_inline
r_void
id|mga_iounmap
c_func
(paren
id|vaddr_t
id|va
)paren
(brace
id|iounmap
c_func
(paren
id|va.vaddr
)paren
suffix:semicolon
)brace
DECL|struct|my_timming
r_struct
id|my_timming
(brace
DECL|member|pixclock
r_int
r_int
id|pixclock
suffix:semicolon
DECL|member|mnp
r_int
id|mnp
suffix:semicolon
DECL|member|crtc
r_int
r_int
id|crtc
suffix:semicolon
DECL|member|HDisplay
r_int
r_int
id|HDisplay
suffix:semicolon
DECL|member|HSyncStart
r_int
r_int
id|HSyncStart
suffix:semicolon
DECL|member|HSyncEnd
r_int
r_int
id|HSyncEnd
suffix:semicolon
DECL|member|HTotal
r_int
r_int
id|HTotal
suffix:semicolon
DECL|member|VDisplay
r_int
r_int
id|VDisplay
suffix:semicolon
DECL|member|VSyncStart
r_int
r_int
id|VSyncStart
suffix:semicolon
DECL|member|VSyncEnd
r_int
r_int
id|VSyncEnd
suffix:semicolon
DECL|member|VTotal
r_int
r_int
id|VTotal
suffix:semicolon
DECL|member|sync
r_int
r_int
id|sync
suffix:semicolon
DECL|member|dblscan
r_int
id|dblscan
suffix:semicolon
DECL|member|interlaced
r_int
id|interlaced
suffix:semicolon
DECL|member|delay
r_int
r_int
id|delay
suffix:semicolon
multiline_comment|/* CRTC delay */
)brace
suffix:semicolon
DECL|enumerator|M_SYSTEM_PLL
DECL|enumerator|M_PIXEL_PLL_A
DECL|enumerator|M_PIXEL_PLL_B
DECL|enumerator|M_PIXEL_PLL_C
DECL|enumerator|M_VIDEO_PLL
r_enum
(brace
id|M_SYSTEM_PLL
comma
id|M_PIXEL_PLL_A
comma
id|M_PIXEL_PLL_B
comma
id|M_PIXEL_PLL_C
comma
id|M_VIDEO_PLL
)brace
suffix:semicolon
DECL|struct|matrox_pll_cache
r_struct
id|matrox_pll_cache
(brace
DECL|member|valid
r_int
r_int
id|valid
suffix:semicolon
r_struct
(brace
DECL|member|mnp_key
r_int
r_int
id|mnp_key
suffix:semicolon
DECL|member|mnp_value
r_int
r_int
id|mnp_value
suffix:semicolon
DECL|member|data
)brace
id|data
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|matrox_pll_limits
r_struct
id|matrox_pll_limits
(brace
DECL|member|vcomin
r_int
r_int
id|vcomin
suffix:semicolon
DECL|member|vcomax
r_int
r_int
id|vcomax
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|matrox_pll_features
r_struct
id|matrox_pll_features
(brace
DECL|member|vco_freq_min
r_int
r_int
id|vco_freq_min
suffix:semicolon
DECL|member|ref_freq
r_int
r_int
id|ref_freq
suffix:semicolon
DECL|member|feed_div_min
r_int
r_int
id|feed_div_min
suffix:semicolon
DECL|member|feed_div_max
r_int
r_int
id|feed_div_max
suffix:semicolon
DECL|member|in_div_min
r_int
r_int
id|in_div_min
suffix:semicolon
DECL|member|in_div_max
r_int
r_int
id|in_div_max
suffix:semicolon
DECL|member|post_shift_max
r_int
r_int
id|post_shift_max
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|matroxfb_par
r_struct
id|matroxfb_par
(brace
DECL|member|final_bppShift
r_int
r_int
id|final_bppShift
suffix:semicolon
DECL|member|cmap_len
r_int
r_int
id|cmap_len
suffix:semicolon
r_struct
(brace
DECL|member|bytes
r_int
r_int
id|bytes
suffix:semicolon
DECL|member|pixels
r_int
r_int
id|pixels
suffix:semicolon
DECL|member|chunks
r_int
r_int
id|chunks
suffix:semicolon
DECL|member|ydstorg
)brace
id|ydstorg
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|matrox_fb_info
suffix:semicolon
DECL|struct|matrox_DAC1064_features
r_struct
id|matrox_DAC1064_features
(brace
DECL|member|xvrefctrl
id|u_int8_t
id|xvrefctrl
suffix:semicolon
DECL|member|xmiscctrl
id|u_int8_t
id|xmiscctrl
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|matrox_accel_features
r_struct
id|matrox_accel_features
(brace
DECL|member|has_cacheflush
r_int
id|has_cacheflush
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* current hardware status */
DECL|struct|mavenregs
r_struct
id|mavenregs
(brace
DECL|member|regs
id|u_int8_t
id|regs
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|vlines
r_int
id|vlines
suffix:semicolon
DECL|member|xtal
r_int
id|xtal
suffix:semicolon
DECL|member|fv
r_int
id|fv
suffix:semicolon
DECL|member|htotal
id|u_int16_t
id|htotal
suffix:semicolon
DECL|member|hcorr
id|u_int16_t
id|hcorr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|matrox_crtc2
r_struct
id|matrox_crtc2
(brace
DECL|member|ctl
id|u_int32_t
id|ctl
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|matrox_hw_state
r_struct
id|matrox_hw_state
(brace
DECL|member|MXoptionReg
id|u_int32_t
id|MXoptionReg
suffix:semicolon
DECL|member|DACclk
r_int
r_char
id|DACclk
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|DACreg
r_int
r_char
id|DACreg
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|MiscOutReg
r_int
r_char
id|MiscOutReg
suffix:semicolon
DECL|member|DACpal
r_int
r_char
id|DACpal
(braket
l_int|768
)braket
suffix:semicolon
DECL|member|CRTC
r_int
r_char
id|CRTC
(braket
l_int|25
)braket
suffix:semicolon
DECL|member|CRTCEXT
r_int
r_char
id|CRTCEXT
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|SEQ
r_int
r_char
id|SEQ
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* unused for MGA mode, but who knows... */
DECL|member|GCTL
r_int
r_char
id|GCTL
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* unused for MGA mode, but who knows... */
DECL|member|ATTR
r_int
r_char
id|ATTR
(braket
l_int|21
)braket
suffix:semicolon
multiline_comment|/* TVOut only */
DECL|member|maven
r_struct
id|mavenregs
id|maven
suffix:semicolon
DECL|member|crtc2
r_struct
id|matrox_crtc2
id|crtc2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|matrox_accel_data
r_struct
id|matrox_accel_data
(brace
macro_line|#ifdef CONFIG_FB_MATROX_MILLENIUM
DECL|member|ramdac_rev
r_int
r_char
id|ramdac_rev
suffix:semicolon
macro_line|#endif
DECL|member|m_dwg_rect
id|u_int32_t
id|m_dwg_rect
suffix:semicolon
DECL|member|m_opmode
id|u_int32_t
id|m_opmode
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|v4l2_queryctrl
suffix:semicolon
r_struct
id|v4l2_control
suffix:semicolon
DECL|struct|matrox_altout
r_struct
id|matrox_altout
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|compute
r_int
(paren
op_star
id|compute
)paren
(paren
r_void
op_star
id|altout_dev
comma
r_struct
id|my_timming
op_star
id|input
)paren
suffix:semicolon
DECL|member|program
r_int
(paren
op_star
id|program
)paren
(paren
r_void
op_star
id|altout_dev
)paren
suffix:semicolon
DECL|member|start
r_int
(paren
op_star
id|start
)paren
(paren
r_void
op_star
id|altout_dev
)paren
suffix:semicolon
DECL|member|verifymode
r_int
(paren
op_star
id|verifymode
)paren
(paren
r_void
op_star
id|altout_dev
comma
id|u_int32_t
id|mode
)paren
suffix:semicolon
DECL|member|getqueryctrl
r_int
(paren
op_star
id|getqueryctrl
)paren
(paren
r_void
op_star
id|altout_dev
comma
r_struct
id|v4l2_queryctrl
op_star
id|ctrl
)paren
suffix:semicolon
DECL|member|getctrl
r_int
(paren
op_star
id|getctrl
)paren
(paren
r_void
op_star
id|altout_dev
comma
r_struct
id|v4l2_control
op_star
id|ctrl
)paren
suffix:semicolon
DECL|member|setctrl
r_int
(paren
op_star
id|setctrl
)paren
(paren
r_void
op_star
id|altout_dev
comma
r_struct
id|v4l2_control
op_star
id|ctrl
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MATROXFB_SRC_NONE
mdefine_line|#define MATROXFB_SRC_NONE&t;0
DECL|macro|MATROXFB_SRC_CRTC1
mdefine_line|#define MATROXFB_SRC_CRTC1&t;1
DECL|macro|MATROXFB_SRC_CRTC2
mdefine_line|#define MATROXFB_SRC_CRTC2&t;2
DECL|enum|mga_chip
DECL|enumerator|MGA_2064
DECL|enumerator|MGA_2164
DECL|enumerator|MGA_1064
DECL|enumerator|MGA_1164
DECL|enumerator|MGA_G100
DECL|enumerator|MGA_G200
DECL|enumerator|MGA_G400
DECL|enumerator|MGA_G450
DECL|enumerator|MGA_G550
r_enum
id|mga_chip
(brace
id|MGA_2064
comma
id|MGA_2164
comma
id|MGA_1064
comma
id|MGA_1164
comma
id|MGA_G100
comma
id|MGA_G200
comma
id|MGA_G400
comma
id|MGA_G450
comma
id|MGA_G550
)brace
suffix:semicolon
DECL|struct|matrox_bios
r_struct
id|matrox_bios
(brace
DECL|member|bios_valid
r_int
r_int
id|bios_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pins_len
r_int
r_int
id|pins_len
suffix:semicolon
DECL|member|pins
r_int
r_char
id|pins
(braket
l_int|128
)braket
suffix:semicolon
r_struct
(brace
DECL|member|vMaj
DECL|member|vMin
DECL|member|vRev
r_int
r_char
id|vMaj
comma
id|vMin
comma
id|vRev
suffix:semicolon
DECL|member|version
)brace
id|version
suffix:semicolon
r_struct
(brace
DECL|member|state
DECL|member|tvout
r_int
r_char
id|state
comma
id|tvout
suffix:semicolon
DECL|member|output
)brace
id|output
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|display
id|fb_display
(braket
)braket
suffix:semicolon
r_struct
id|matrox_switch
suffix:semicolon
r_struct
id|matroxfb_driver
suffix:semicolon
r_struct
id|matroxfb_dh_fb_info
suffix:semicolon
DECL|struct|matrox_vsync
r_struct
id|matrox_vsync
(brace
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|cnt
r_int
r_int
id|cnt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|matrox_fb_info
r_struct
id|matrox_fb_info
(brace
DECL|member|fbcon
r_struct
id|fb_info
id|fbcon
suffix:semicolon
DECL|member|next_fb
r_struct
id|list_head
id|next_fb
suffix:semicolon
DECL|member|dead
r_int
id|dead
suffix:semicolon
DECL|member|initialized
r_int
id|initialized
suffix:semicolon
DECL|member|usecount
r_int
r_int
id|usecount
suffix:semicolon
DECL|member|userusecount
r_int
r_int
id|userusecount
suffix:semicolon
DECL|member|irq_flags
r_int
r_int
id|irq_flags
suffix:semicolon
DECL|member|curr
r_struct
id|matroxfb_par
id|curr
suffix:semicolon
DECL|member|hw
r_struct
id|matrox_hw_state
id|hw
suffix:semicolon
DECL|member|accel
r_struct
id|matrox_accel_data
id|accel
suffix:semicolon
DECL|member|pcidev
r_struct
id|pci_dev
op_star
id|pcidev
suffix:semicolon
r_struct
(brace
DECL|member|vsync
r_struct
id|matrox_vsync
id|vsync
suffix:semicolon
DECL|member|pixclock
r_int
r_int
id|pixclock
suffix:semicolon
DECL|member|mnp
r_int
id|mnp
suffix:semicolon
DECL|member|panpos
r_int
id|panpos
suffix:semicolon
DECL|member|crtc1
)brace
id|crtc1
suffix:semicolon
r_struct
(brace
DECL|member|vsync
r_struct
id|matrox_vsync
id|vsync
suffix:semicolon
DECL|member|pixclock
r_int
r_int
id|pixclock
suffix:semicolon
DECL|member|mnp
r_int
id|mnp
suffix:semicolon
DECL|member|info
r_struct
id|matroxfb_dh_fb_info
op_star
id|info
suffix:semicolon
DECL|member|lock
r_struct
id|rw_semaphore
id|lock
suffix:semicolon
DECL|member|crtc2
)brace
id|crtc2
suffix:semicolon
r_struct
(brace
DECL|member|lock
r_struct
id|rw_semaphore
id|lock
suffix:semicolon
r_struct
(brace
DECL|member|brightness
DECL|member|contrast
DECL|member|saturation
DECL|member|hue
DECL|member|gamma
r_int
id|brightness
comma
id|contrast
comma
id|saturation
comma
id|hue
comma
id|gamma
suffix:semicolon
DECL|member|testout
DECL|member|deflicker
r_int
id|testout
comma
id|deflicker
suffix:semicolon
DECL|member|tvo_params
)brace
id|tvo_params
suffix:semicolon
DECL|member|altout
)brace
id|altout
suffix:semicolon
DECL|macro|MATROXFB_MAX_OUTPUTS
mdefine_line|#define MATROXFB_MAX_OUTPUTS&t;&t;3
r_struct
(brace
DECL|member|src
r_int
r_int
id|src
suffix:semicolon
DECL|member|output
r_struct
id|matrox_altout
op_star
id|output
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|default_src
r_int
r_int
id|default_src
suffix:semicolon
DECL|member|outputs
)brace
id|outputs
(braket
id|MATROXFB_MAX_OUTPUTS
)braket
suffix:semicolon
DECL|macro|MATROXFB_MAX_FB_DRIVERS
mdefine_line|#define MATROXFB_MAX_FB_DRIVERS&t;&t;5
DECL|member|drivers
r_struct
id|matroxfb_driver
op_star
(paren
id|drivers
(braket
id|MATROXFB_MAX_FB_DRIVERS
)braket
)paren
suffix:semicolon
DECL|member|drivers_data
r_void
op_star
(paren
id|drivers_data
(braket
id|MATROXFB_MAX_FB_DRIVERS
)braket
)paren
suffix:semicolon
DECL|member|drivers_count
r_int
r_int
id|drivers_count
suffix:semicolon
r_struct
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* physical */
DECL|member|vbase
id|vaddr_t
id|vbase
suffix:semicolon
multiline_comment|/* CPU view */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|len_usable
r_int
r_int
id|len_usable
suffix:semicolon
DECL|member|len_maximum
r_int
r_int
id|len_maximum
suffix:semicolon
DECL|member|video
)brace
id|video
suffix:semicolon
r_struct
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* physical */
DECL|member|vbase
id|vaddr_t
id|vbase
suffix:semicolon
multiline_comment|/* CPU view */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|mmio
)brace
id|mmio
suffix:semicolon
DECL|member|max_pixel_clock
r_int
r_int
id|max_pixel_clock
suffix:semicolon
DECL|member|hw_switch
r_struct
id|matrox_switch
op_star
id|hw_switch
suffix:semicolon
r_struct
(brace
DECL|member|pll
r_struct
id|matrox_pll_features
id|pll
suffix:semicolon
DECL|member|DAC1064
r_struct
id|matrox_DAC1064_features
id|DAC1064
suffix:semicolon
DECL|member|accel
r_struct
id|matrox_accel_features
id|accel
suffix:semicolon
DECL|member|features
)brace
id|features
suffix:semicolon
r_struct
(brace
DECL|member|DAC
id|spinlock_t
id|DAC
suffix:semicolon
DECL|member|accel
id|spinlock_t
id|accel
suffix:semicolon
DECL|member|lock
)brace
id|lock
suffix:semicolon
DECL|member|chip
r_enum
id|mga_chip
id|chip
suffix:semicolon
DECL|member|interleave
r_int
id|interleave
suffix:semicolon
DECL|member|millenium
r_int
id|millenium
suffix:semicolon
DECL|member|milleniumII
r_int
id|milleniumII
suffix:semicolon
r_struct
(brace
DECL|member|cfb4
r_int
id|cfb4
suffix:semicolon
DECL|member|vxres
r_const
r_int
op_star
id|vxres
suffix:semicolon
DECL|member|cross4MB
r_int
id|cross4MB
suffix:semicolon
DECL|member|text
r_int
id|text
suffix:semicolon
DECL|member|plnwt
r_int
id|plnwt
suffix:semicolon
DECL|member|srcorg
r_int
id|srcorg
suffix:semicolon
DECL|member|capable
)brace
id|capable
suffix:semicolon
macro_line|#ifdef CONFIG_MTRR
r_struct
(brace
DECL|member|vram
r_int
id|vram
suffix:semicolon
DECL|member|vram_valid
r_int
id|vram_valid
suffix:semicolon
DECL|member|mtrr
)brace
id|mtrr
suffix:semicolon
macro_line|#endif
r_struct
(brace
DECL|member|precise_width
r_int
id|precise_width
suffix:semicolon
DECL|member|mga_24bpp_fix
r_int
id|mga_24bpp_fix
suffix:semicolon
DECL|member|novga
r_int
id|novga
suffix:semicolon
DECL|member|nobios
r_int
id|nobios
suffix:semicolon
DECL|member|nopciretry
r_int
id|nopciretry
suffix:semicolon
DECL|member|noinit
r_int
id|noinit
suffix:semicolon
DECL|member|sgram
r_int
id|sgram
suffix:semicolon
macro_line|#ifdef CONFIG_FB_MATROX_32MB
DECL|member|support32MB
r_int
id|support32MB
suffix:semicolon
macro_line|#endif
DECL|member|accelerator
r_int
id|accelerator
suffix:semicolon
DECL|member|text_type_aux
r_int
id|text_type_aux
suffix:semicolon
DECL|member|video64bits
r_int
id|video64bits
suffix:semicolon
DECL|member|crtc2
r_int
id|crtc2
suffix:semicolon
DECL|member|maven_capable
r_int
id|maven_capable
suffix:semicolon
DECL|member|vgastep
r_int
r_int
id|vgastep
suffix:semicolon
DECL|member|textmode
r_int
r_int
id|textmode
suffix:semicolon
DECL|member|textstep
r_int
r_int
id|textstep
suffix:semicolon
DECL|member|textvram
r_int
r_int
id|textvram
suffix:semicolon
multiline_comment|/* character cells */
DECL|member|ydstorg
r_int
r_int
id|ydstorg
suffix:semicolon
multiline_comment|/* offset in bytes from video start to usable memory */
multiline_comment|/* 0 except for 6MB Millenium */
DECL|member|memtype
r_int
id|memtype
suffix:semicolon
DECL|member|g450dac
r_int
id|g450dac
suffix:semicolon
DECL|member|dfp_type
r_int
id|dfp_type
suffix:semicolon
DECL|member|panellink
r_int
id|panellink
suffix:semicolon
multiline_comment|/* G400 DFP possible (not G450/G550) */
DECL|member|dualhead
r_int
id|dualhead
suffix:semicolon
DECL|member|fbResource
r_int
r_int
id|fbResource
suffix:semicolon
DECL|member|devflags
)brace
id|devflags
suffix:semicolon
DECL|member|fbops
r_struct
id|fb_ops
id|fbops
suffix:semicolon
DECL|member|bios
r_struct
id|matrox_bios
id|bios
suffix:semicolon
r_struct
(brace
DECL|member|pixel
r_struct
id|matrox_pll_limits
id|pixel
suffix:semicolon
DECL|member|system
r_struct
id|matrox_pll_limits
id|system
suffix:semicolon
DECL|member|video
r_struct
id|matrox_pll_limits
id|video
suffix:semicolon
DECL|member|limits
)brace
id|limits
suffix:semicolon
r_struct
(brace
DECL|member|pixel
r_struct
id|matrox_pll_cache
id|pixel
suffix:semicolon
DECL|member|system
r_struct
id|matrox_pll_cache
id|system
suffix:semicolon
DECL|member|video
r_struct
id|matrox_pll_cache
id|video
suffix:semicolon
DECL|member|cache
)brace
id|cache
suffix:semicolon
r_struct
(brace
r_struct
(brace
DECL|member|video
r_int
r_int
id|video
suffix:semicolon
DECL|member|system
r_int
r_int
id|system
suffix:semicolon
DECL|member|pll
)brace
id|pll
suffix:semicolon
r_struct
(brace
DECL|member|opt
id|u_int32_t
id|opt
suffix:semicolon
DECL|member|opt2
id|u_int32_t
id|opt2
suffix:semicolon
DECL|member|opt3
id|u_int32_t
id|opt3
suffix:semicolon
DECL|member|mctlwtst
id|u_int32_t
id|mctlwtst
suffix:semicolon
DECL|member|mctlwtst_core
id|u_int32_t
id|mctlwtst_core
suffix:semicolon
DECL|member|memmisc
id|u_int32_t
id|memmisc
suffix:semicolon
DECL|member|memrdbk
id|u_int32_t
id|memrdbk
suffix:semicolon
DECL|member|maccess
id|u_int32_t
id|maccess
suffix:semicolon
DECL|member|reg
)brace
id|reg
suffix:semicolon
r_struct
(brace
DECL|member|ddr
r_int
r_int
id|ddr
suffix:colon
l_int|1
comma
DECL|member|emrswen
id|emrswen
suffix:colon
l_int|1
comma
DECL|member|dll
id|dll
suffix:colon
l_int|1
suffix:semicolon
DECL|member|memory
)brace
id|memory
suffix:semicolon
DECL|member|values
)brace
id|values
suffix:semicolon
DECL|member|cmap
id|u_int32_t
id|cmap
(braket
l_int|17
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|info2minfo
mdefine_line|#define info2minfo(info) container_of(info, struct matrox_fb_info, fbcon)
macro_line|#ifdef CONFIG_FB_MATROX_MULTIHEAD
DECL|macro|ACCESS_FBINFO2
mdefine_line|#define ACCESS_FBINFO2(info, x) (info-&gt;x)
DECL|macro|ACCESS_FBINFO
mdefine_line|#define ACCESS_FBINFO(x) ACCESS_FBINFO2(minfo,x)
DECL|macro|MINFO
mdefine_line|#define MINFO minfo
DECL|macro|WPMINFO2
mdefine_line|#define WPMINFO2 struct matrox_fb_info* minfo
DECL|macro|WPMINFO
mdefine_line|#define WPMINFO  WPMINFO2 ,
DECL|macro|CPMINFO2
mdefine_line|#define CPMINFO2 const struct matrox_fb_info* minfo
DECL|macro|CPMINFO
mdefine_line|#define CPMINFO&t; CPMINFO2 ,
DECL|macro|PMINFO2
mdefine_line|#define PMINFO2  minfo
DECL|macro|PMINFO
mdefine_line|#define PMINFO   PMINFO2 ,
DECL|macro|MINFO_FROM
mdefine_line|#define MINFO_FROM(x)&t;   struct matrox_fb_info* minfo = x
macro_line|#else
r_extern
r_struct
id|matrox_fb_info
id|matroxfb_global_mxinfo
suffix:semicolon
DECL|macro|ACCESS_FBINFO
mdefine_line|#define ACCESS_FBINFO(x) (matroxfb_global_mxinfo.x)
DECL|macro|ACCESS_FBINFO2
mdefine_line|#define ACCESS_FBINFO2(info, x) (matroxfb_global_mxinfo.x)
DECL|macro|MINFO
mdefine_line|#define MINFO (&amp;matroxfb_global_mxinfo)
DECL|macro|WPMINFO2
mdefine_line|#define WPMINFO2 void
DECL|macro|WPMINFO
mdefine_line|#define WPMINFO
DECL|macro|CPMINFO2
mdefine_line|#define CPMINFO2 void
DECL|macro|CPMINFO
mdefine_line|#define CPMINFO
DECL|macro|PMINFO2
mdefine_line|#define PMINFO2
DECL|macro|PMINFO
mdefine_line|#define PMINFO
DECL|macro|MINFO_FROM
mdefine_line|#define MINFO_FROM(x)
macro_line|#endif
DECL|macro|MINFO_FROM_INFO
mdefine_line|#define MINFO_FROM_INFO(x) MINFO_FROM(info2minfo(x))
DECL|struct|matrox_switch
r_struct
id|matrox_switch
(brace
DECL|member|preinit
r_int
(paren
op_star
id|preinit
)paren
(paren
id|WPMINFO2
)paren
suffix:semicolon
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
id|WPMINFO2
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
id|WPMINFO
r_struct
id|my_timming
op_star
)paren
suffix:semicolon
DECL|member|restore
r_void
(paren
op_star
id|restore
)paren
(paren
id|WPMINFO2
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|matroxfb_driver
r_struct
id|matroxfb_driver
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|probe
r_void
op_star
(paren
op_star
id|probe
)paren
(paren
r_struct
id|matrox_fb_info
op_star
id|info
)paren
suffix:semicolon
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|matrox_fb_info
op_star
id|info
comma
r_void
op_star
id|data
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|matroxfb_register_driver
c_func
(paren
r_struct
id|matroxfb_driver
op_star
id|drv
)paren
suffix:semicolon
r_void
id|matroxfb_unregister_driver
c_func
(paren
r_struct
id|matroxfb_driver
op_star
id|drv
)paren
suffix:semicolon
DECL|macro|PCI_OPTION_REG
mdefine_line|#define PCI_OPTION_REG&t;0x40
DECL|macro|PCI_OPTION_ENABLE_ROM
mdefine_line|#define   PCI_OPTION_ENABLE_ROM&t;&t;0x40000000
DECL|macro|PCI_MGA_INDEX
mdefine_line|#define PCI_MGA_INDEX&t;0x44
DECL|macro|PCI_MGA_DATA
mdefine_line|#define PCI_MGA_DATA&t;0x48
DECL|macro|PCI_OPTION2_REG
mdefine_line|#define PCI_OPTION2_REG&t;0x50
DECL|macro|PCI_OPTION3_REG
mdefine_line|#define PCI_OPTION3_REG&t;0x54
DECL|macro|PCI_MEMMISC_REG
mdefine_line|#define PCI_MEMMISC_REG&t;0x58
DECL|macro|M_DWGCTL
mdefine_line|#define M_DWGCTL&t;0x1C00
DECL|macro|M_MACCESS
mdefine_line|#define M_MACCESS&t;0x1C04
DECL|macro|M_CTLWTST
mdefine_line|#define M_CTLWTST&t;0x1C08
DECL|macro|M_PLNWT
mdefine_line|#define M_PLNWT&t;&t;0x1C1C
DECL|macro|M_BCOL
mdefine_line|#define M_BCOL&t;&t;0x1C20
DECL|macro|M_FCOL
mdefine_line|#define M_FCOL&t;&t;0x1C24
DECL|macro|M_SGN
mdefine_line|#define M_SGN&t;&t;0x1C58
DECL|macro|M_LEN
mdefine_line|#define M_LEN&t;&t;0x1C5C
DECL|macro|M_AR0
mdefine_line|#define M_AR0&t;&t;0x1C60
DECL|macro|M_AR1
mdefine_line|#define M_AR1&t;&t;0x1C64
DECL|macro|M_AR2
mdefine_line|#define M_AR2&t;&t;0x1C68
DECL|macro|M_AR3
mdefine_line|#define M_AR3&t;&t;0x1C6C
DECL|macro|M_AR4
mdefine_line|#define M_AR4&t;&t;0x1C70
DECL|macro|M_AR5
mdefine_line|#define M_AR5&t;&t;0x1C74
DECL|macro|M_AR6
mdefine_line|#define M_AR6&t;&t;0x1C78
DECL|macro|M_CXBNDRY
mdefine_line|#define M_CXBNDRY&t;0x1C80
DECL|macro|M_FXBNDRY
mdefine_line|#define M_FXBNDRY&t;0x1C84
DECL|macro|M_YDSTLEN
mdefine_line|#define M_YDSTLEN&t;0x1C88
DECL|macro|M_PITCH
mdefine_line|#define M_PITCH&t;&t;0x1C8C
DECL|macro|M_YDST
mdefine_line|#define M_YDST&t;&t;0x1C90
DECL|macro|M_YDSTORG
mdefine_line|#define M_YDSTORG&t;0x1C94
DECL|macro|M_YTOP
mdefine_line|#define M_YTOP&t;&t;0x1C98
DECL|macro|M_YBOT
mdefine_line|#define M_YBOT&t;&t;0x1C9C
multiline_comment|/* mystique only */
DECL|macro|M_CACHEFLUSH
mdefine_line|#define M_CACHEFLUSH&t;0x1FFF
DECL|macro|M_EXEC
mdefine_line|#define M_EXEC&t;&t;0x0100
DECL|macro|M_DWG_TRAP
mdefine_line|#define M_DWG_TRAP&t;0x04
DECL|macro|M_DWG_BITBLT
mdefine_line|#define M_DWG_BITBLT&t;0x08
DECL|macro|M_DWG_ILOAD
mdefine_line|#define M_DWG_ILOAD&t;0x09
DECL|macro|M_DWG_LINEAR
mdefine_line|#define M_DWG_LINEAR&t;0x0080
DECL|macro|M_DWG_SOLID
mdefine_line|#define M_DWG_SOLID&t;0x0800
DECL|macro|M_DWG_ARZERO
mdefine_line|#define M_DWG_ARZERO&t;0x1000
DECL|macro|M_DWG_SGNZERO
mdefine_line|#define M_DWG_SGNZERO&t;0x2000
DECL|macro|M_DWG_SHIFTZERO
mdefine_line|#define M_DWG_SHIFTZERO&t;0x4000
DECL|macro|M_DWG_REPLACE
mdefine_line|#define M_DWG_REPLACE&t;0x000C0000
DECL|macro|M_DWG_REPLACE2
mdefine_line|#define M_DWG_REPLACE2&t;(M_DWG_REPLACE | 0x40)
DECL|macro|M_DWG_XOR
mdefine_line|#define M_DWG_XOR&t;0x00060010
DECL|macro|M_DWG_BFCOL
mdefine_line|#define M_DWG_BFCOL&t;0x04000000
DECL|macro|M_DWG_BMONOWF
mdefine_line|#define M_DWG_BMONOWF&t;0x08000000
DECL|macro|M_DWG_TRANSC
mdefine_line|#define M_DWG_TRANSC&t;0x40000000
DECL|macro|M_FIFOSTATUS
mdefine_line|#define M_FIFOSTATUS&t;0x1E10
DECL|macro|M_STATUS
mdefine_line|#define M_STATUS&t;0x1E14
DECL|macro|M_ICLEAR
mdefine_line|#define M_ICLEAR&t;0x1E18
DECL|macro|M_IEN
mdefine_line|#define M_IEN&t;&t;0x1E1C
DECL|macro|M_VCOUNT
mdefine_line|#define M_VCOUNT&t;0x1E20
DECL|macro|M_RESET
mdefine_line|#define M_RESET&t;&t;0x1E40
DECL|macro|M_MEMRDBK
mdefine_line|#define M_MEMRDBK&t;0x1E44
DECL|macro|M_AGP2PLL
mdefine_line|#define M_AGP2PLL&t;0x1E4C
DECL|macro|M_OPMODE
mdefine_line|#define M_OPMODE&t;0x1E54
DECL|macro|M_OPMODE_DMA_GEN_WRITE
mdefine_line|#define     M_OPMODE_DMA_GEN_WRITE&t;0x00
DECL|macro|M_OPMODE_DMA_BLIT
mdefine_line|#define     M_OPMODE_DMA_BLIT&t;&t;0x04
DECL|macro|M_OPMODE_DMA_VECTOR_WRITE
mdefine_line|#define     M_OPMODE_DMA_VECTOR_WRITE&t;0x08
DECL|macro|M_OPMODE_DMA_LE
mdefine_line|#define     M_OPMODE_DMA_LE&t;&t;0x0000&t;&t;/* little endian - no transformation */
DECL|macro|M_OPMODE_DMA_BE_8BPP
mdefine_line|#define     M_OPMODE_DMA_BE_8BPP&t;0x0000
DECL|macro|M_OPMODE_DMA_BE_16BPP
mdefine_line|#define     M_OPMODE_DMA_BE_16BPP&t;0x0100
DECL|macro|M_OPMODE_DMA_BE_32BPP
mdefine_line|#define     M_OPMODE_DMA_BE_32BPP&t;0x0200
DECL|macro|M_OPMODE_DIR_LE
mdefine_line|#define     M_OPMODE_DIR_LE&t;&t;0x000000&t;/* little endian - no transformation */
DECL|macro|M_OPMODE_DIR_BE_8BPP
mdefine_line|#define     M_OPMODE_DIR_BE_8BPP&t;0x000000
DECL|macro|M_OPMODE_DIR_BE_16BPP
mdefine_line|#define     M_OPMODE_DIR_BE_16BPP&t;0x010000
DECL|macro|M_OPMODE_DIR_BE_32BPP
mdefine_line|#define     M_OPMODE_DIR_BE_32BPP&t;0x020000
DECL|macro|M_ATTR_INDEX
mdefine_line|#define M_ATTR_INDEX&t;0x1FC0
DECL|macro|M_ATTR_DATA
mdefine_line|#define M_ATTR_DATA&t;0x1FC1
DECL|macro|M_MISC_REG
mdefine_line|#define M_MISC_REG&t;0x1FC2
DECL|macro|M_3C2_RD
mdefine_line|#define M_3C2_RD&t;0x1FC2
DECL|macro|M_SEQ_INDEX
mdefine_line|#define M_SEQ_INDEX&t;0x1FC4
DECL|macro|M_SEQ_DATA
mdefine_line|#define M_SEQ_DATA&t;0x1FC5
DECL|macro|M_MISC_REG_READ
mdefine_line|#define M_MISC_REG_READ&t;0x1FCC
DECL|macro|M_GRAPHICS_INDEX
mdefine_line|#define M_GRAPHICS_INDEX 0x1FCE
DECL|macro|M_GRAPHICS_DATA
mdefine_line|#define M_GRAPHICS_DATA&t;0x1FCF
DECL|macro|M_CRTC_INDEX
mdefine_line|#define M_CRTC_INDEX&t;0x1FD4
DECL|macro|M_ATTR_RESET
mdefine_line|#define M_ATTR_RESET&t;0x1FDA
DECL|macro|M_3DA_WR
mdefine_line|#define M_3DA_WR&t;0x1FDA
DECL|macro|M_INSTS1
mdefine_line|#define M_INSTS1&t;0x1FDA
DECL|macro|M_EXTVGA_INDEX
mdefine_line|#define M_EXTVGA_INDEX&t;0x1FDE
DECL|macro|M_EXTVGA_DATA
mdefine_line|#define M_EXTVGA_DATA&t;0x1FDF
multiline_comment|/* G200 only */
DECL|macro|M_SRCORG
mdefine_line|#define M_SRCORG&t;0x2CB4
DECL|macro|M_DSTORG
mdefine_line|#define M_DSTORG&t;0x2CB8
DECL|macro|M_RAMDAC_BASE
mdefine_line|#define M_RAMDAC_BASE&t;0x3C00
multiline_comment|/* fortunately, same on TVP3026 and MGA1064 */
DECL|macro|M_DAC_REG
mdefine_line|#define M_DAC_REG&t;(M_RAMDAC_BASE+0)
DECL|macro|M_DAC_VAL
mdefine_line|#define M_DAC_VAL&t;(M_RAMDAC_BASE+1)
DECL|macro|M_PALETTE_MASK
mdefine_line|#define M_PALETTE_MASK&t;(M_RAMDAC_BASE+2)
DECL|macro|M_X_INDEX
mdefine_line|#define M_X_INDEX&t;0x00
DECL|macro|M_X_DATAREG
mdefine_line|#define M_X_DATAREG&t;0x0A
DECL|macro|DAC_XGENIOCTRL
mdefine_line|#define DAC_XGENIOCTRL&t;&t;0x2A
DECL|macro|DAC_XGENIODATA
mdefine_line|#define DAC_XGENIODATA&t;&t;0x2B
DECL|macro|M_C2CTL
mdefine_line|#define M_C2CTL&t;&t;0x3C10
DECL|macro|MX_OPTION_BSWAP
mdefine_line|#define MX_OPTION_BSWAP         0x00000000
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|M_OPMODE_4BPP
mdefine_line|#define M_OPMODE_4BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_LE | M_OPMODE_DMA_BLIT)
DECL|macro|M_OPMODE_8BPP
mdefine_line|#define M_OPMODE_8BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_LE | M_OPMODE_DMA_BLIT)
DECL|macro|M_OPMODE_16BPP
mdefine_line|#define M_OPMODE_16BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_LE | M_OPMODE_DMA_BLIT)
DECL|macro|M_OPMODE_24BPP
mdefine_line|#define M_OPMODE_24BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_LE | M_OPMODE_DMA_BLIT)
DECL|macro|M_OPMODE_32BPP
mdefine_line|#define M_OPMODE_32BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_LE | M_OPMODE_DMA_BLIT)
macro_line|#else
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|M_OPMODE_4BPP
mdefine_line|#define M_OPMODE_4BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_LE       | M_OPMODE_DMA_BLIT)&t;/* TODO */
DECL|macro|M_OPMODE_8BPP
mdefine_line|#define M_OPMODE_8BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_BE_8BPP  | M_OPMODE_DMA_BLIT)
DECL|macro|M_OPMODE_16BPP
mdefine_line|#define M_OPMODE_16BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_BE_16BPP | M_OPMODE_DMA_BLIT)
DECL|macro|M_OPMODE_24BPP
mdefine_line|#define M_OPMODE_24BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_BE_8BPP  | M_OPMODE_DMA_BLIT)&t;/* TODO, ?32 */
DECL|macro|M_OPMODE_32BPP
mdefine_line|#define M_OPMODE_32BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_BE_32BPP | M_OPMODE_DMA_BLIT)
macro_line|#else
macro_line|#error &quot;Byte ordering have to be defined. Cannot continue.&quot;
macro_line|#endif
macro_line|#endif
DECL|macro|mga_inb
mdefine_line|#define mga_inb(addr)&t;&t;mga_readb(ACCESS_FBINFO(mmio.vbase), (addr))
DECL|macro|mga_inl
mdefine_line|#define mga_inl(addr)&t;&t;mga_readl(ACCESS_FBINFO(mmio.vbase), (addr))
DECL|macro|mga_outb
mdefine_line|#define mga_outb(addr,val)&t;mga_writeb(ACCESS_FBINFO(mmio.vbase), (addr), (val))
DECL|macro|mga_outw
mdefine_line|#define mga_outw(addr,val)&t;mga_writew(ACCESS_FBINFO(mmio.vbase), (addr), (val))
DECL|macro|mga_outl
mdefine_line|#define mga_outl(addr,val)&t;mga_writel(ACCESS_FBINFO(mmio.vbase), (addr), (val))
DECL|macro|mga_readr
mdefine_line|#define mga_readr(port,idx)&t;(mga_outb((port),(idx)), mga_inb((port)+1))
DECL|macro|mga_setr
mdefine_line|#define mga_setr(addr,port,val)&t;mga_outw(addr, ((val)&lt;&lt;8) | (port))
DECL|macro|mga_fifo
mdefine_line|#define mga_fifo(n)&t;do {} while ((mga_inl(M_FIFOSTATUS) &amp; 0xFF) &lt; (n))
DECL|macro|WaitTillIdle
mdefine_line|#define WaitTillIdle()&t;do {} while (mga_inl(M_STATUS) &amp; 0x10000)
multiline_comment|/* code speedup */
macro_line|#ifdef CONFIG_FB_MATROX_MILLENIUM
DECL|macro|isInterleave
mdefine_line|#define isInterleave(x)&t; (x-&gt;interleave)
DECL|macro|isMillenium
mdefine_line|#define isMillenium(x)&t; (x-&gt;millenium)
DECL|macro|isMilleniumII
mdefine_line|#define isMilleniumII(x) (x-&gt;milleniumII)
macro_line|#else
DECL|macro|isInterleave
mdefine_line|#define isInterleave(x)  (0)
DECL|macro|isMillenium
mdefine_line|#define isMillenium(x)&t; (0)
DECL|macro|isMilleniumII
mdefine_line|#define isMilleniumII(x) (0)
macro_line|#endif
DECL|macro|matroxfb_DAC_lock
mdefine_line|#define matroxfb_DAC_lock()                   spin_lock(&amp;ACCESS_FBINFO(lock.DAC))
DECL|macro|matroxfb_DAC_unlock
mdefine_line|#define matroxfb_DAC_unlock()                 spin_unlock(&amp;ACCESS_FBINFO(lock.DAC))
DECL|macro|matroxfb_DAC_lock_irqsave
mdefine_line|#define matroxfb_DAC_lock_irqsave(flags)      spin_lock_irqsave(&amp;ACCESS_FBINFO(lock.DAC),flags)
DECL|macro|matroxfb_DAC_unlock_irqrestore
mdefine_line|#define matroxfb_DAC_unlock_irqrestore(flags) spin_unlock_irqrestore(&amp;ACCESS_FBINFO(lock.DAC),flags)
r_extern
r_void
id|matroxfb_DAC_out
c_func
(paren
id|CPMINFO
r_int
id|reg
comma
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|matroxfb_DAC_in
c_func
(paren
id|CPMINFO
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|matroxfb_var2my
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|fvsi
comma
r_struct
id|my_timming
op_star
id|mt
)paren
suffix:semicolon
r_extern
r_int
id|matroxfb_wait_for_sync
c_func
(paren
id|WPMINFO
id|u_int32_t
id|crtc
)paren
suffix:semicolon
r_extern
r_int
id|matroxfb_enable_irq
c_func
(paren
id|WPMINFO
r_int
id|reenable
)paren
suffix:semicolon
macro_line|#ifdef MATROXFB_USE_SPINLOCKS
DECL|macro|CRITBEGIN
mdefine_line|#define CRITBEGIN  spin_lock_irqsave(&amp;ACCESS_FBINFO(lock.accel), critflags);
DECL|macro|CRITEND
mdefine_line|#define CRITEND&t;   spin_unlock_irqrestore(&amp;ACCESS_FBINFO(lock.accel), critflags);
DECL|macro|CRITFLAGS
mdefine_line|#define CRITFLAGS  unsigned long critflags;
macro_line|#else
DECL|macro|CRITBEGIN
mdefine_line|#define CRITBEGIN
DECL|macro|CRITEND
mdefine_line|#define CRITEND
DECL|macro|CRITFLAGS
mdefine_line|#define CRITFLAGS
macro_line|#endif
macro_line|#endif&t;/* __MATROXFB_H__ */
eof
