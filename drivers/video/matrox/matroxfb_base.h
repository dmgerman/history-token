multiline_comment|/*&n; *&n; * Hardware accelerated Matrox Millennium I, II, Mystique, G100, G200 and G400&n; *&n; * (c) 1998,1999,2000 Petr Vandrovec &lt;vandrove@vc.cvut.cz&gt;&n; *&n; */
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
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#ifdef CONFIG_MTRR
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#endif
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb4.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &lt;video/fbcon-cfb16.h&gt;
macro_line|#include &lt;video/fbcon-cfb24.h&gt;
macro_line|#include &lt;video/fbcon-cfb32.h&gt;
macro_line|#if defined(CONFIG_FB_COMPAT_XPMAC)
macro_line|#include &lt;asm/vc_ioctl.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_PPC)
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;video/macmodes.h&gt;
macro_line|#endif
multiline_comment|/* always compile support for 32MB... It cost almost nothing */
DECL|macro|CONFIG_FB_MATROX_32MB
mdefine_line|#define CONFIG_FB_MATROX_32MB
DECL|macro|FBCON_HAS_VGATEXT
mdefine_line|#define FBCON_HAS_VGATEXT
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
macro_line|#if !defined(__i386__) &amp;&amp; !defined(__x86_64__)
macro_line|#ifndef ioremap_nocache
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(X,Y) ioremap(X,Y)
macro_line|#endif
macro_line|#endif
macro_line|#if defined(__alpha__) || defined(__m68k__)
DECL|macro|READx_WORKS
mdefine_line|#define READx_WORKS
DECL|macro|MEMCPYTOIO_WORKS
mdefine_line|#define MEMCPYTOIO_WORKS
macro_line|#else
DECL|macro|READx_FAILS
mdefine_line|#define READx_FAILS
multiline_comment|/* recheck __ppc__, maybe that __ppc__ needs MEMCPYTOIO_WRITEL */
multiline_comment|/* I benchmarked PII/350MHz with G200... MEMCPY, MEMCPYTOIO and WRITEL are on same speed ( &lt;2% diff) */
multiline_comment|/* so that means that G200 speed (or AGP speed?) is our limit... I do not have benchmark to test, how */
multiline_comment|/* much of PCI bandwidth is used during transfers... */
macro_line|#if defined(__i386__) || defined(__x86_64__)
DECL|macro|MEMCPYTOIO_MEMCPY
mdefine_line|#define MEMCPYTOIO_MEMCPY
macro_line|#else
DECL|macro|MEMCPYTOIO_WRITEL
mdefine_line|#define MEMCPYTOIO_WRITEL
macro_line|#endif
macro_line|#endif
macro_line|#ifdef __sparc__
macro_line|#error &quot;Sorry, I have no idea how to do this on sparc... There is mapioaddr... With bus_type parameter...&quot;
macro_line|#endif
macro_line|#if defined(__m68k__)
DECL|macro|MAP_BUSTOVIRT
mdefine_line|#define MAP_BUSTOVIRT
macro_line|#else
DECL|macro|MAP_IOREMAP
mdefine_line|#define MAP_IOREMAP
macro_line|#endif
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
macro_line|#ifndef PCI_DEVICE_ID_MATROX_G200_PCI
DECL|macro|PCI_DEVICE_ID_MATROX_G200_PCI
mdefine_line|#define PCI_DEVICE_ID_MATROX_G200_PCI&t;0x0520
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_MATROX_G200_AGP
DECL|macro|PCI_DEVICE_ID_MATROX_G200_AGP
mdefine_line|#define PCI_DEVICE_ID_MATROX_G200_AGP&t;0x0521
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_MATROX_G100
DECL|macro|PCI_DEVICE_ID_MATROX_G100
mdefine_line|#define PCI_DEVICE_ID_MATROX_G100&t;0x1000
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_MATROX_G100_AGP
DECL|macro|PCI_DEVICE_ID_MATROX_G100_AGP
mdefine_line|#define PCI_DEVICE_ID_MATROX_G100_AGP&t;0x1001
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_MATROX_G400_AGP
DECL|macro|PCI_DEVICE_ID_MATROX_G400_AGP
mdefine_line|#define PCI_DEVICE_ID_MATROX_G400_AGP&t;0x0525
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
multiline_comment|/* G100, G200 and Mystique have (almost) same DAC */
DECL|macro|NEED_DAC1064
macro_line|#undef NEED_DAC1064
macro_line|#if defined(CONFIG_FB_MATROX_MYSTIQUE) || defined(CONFIG_FB_MATROX_G100)
DECL|macro|NEED_DAC1064
mdefine_line|#define NEED_DAC1064 1
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|vaddr
id|u_int8_t
op_star
id|vaddr
suffix:semicolon
DECL|typedef|vaddr_t
)brace
id|vaddr_t
suffix:semicolon
macro_line|#ifdef READx_WORKS
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
DECL|function|mga_readw
r_static
r_inline
r_int
r_int
id|mga_readw
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
id|readw
c_func
(paren
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
macro_line|#else
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
op_star
(paren
r_volatile
id|u_int8_t
op_star
)paren
(paren
id|va.vaddr
op_plus
id|offs
)paren
suffix:semicolon
)brace
DECL|function|mga_readw
r_static
r_inline
r_int
r_int
id|mga_readw
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
op_star
(paren
r_volatile
id|u_int16_t
op_star
)paren
(paren
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
op_star
(paren
r_volatile
id|u_int32_t
op_star
)paren
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
op_star
(paren
r_volatile
id|u_int8_t
op_star
)paren
(paren
id|va.vaddr
op_plus
id|offs
)paren
op_assign
id|value
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
op_star
(paren
r_volatile
id|u_int16_t
op_star
)paren
(paren
id|va.vaddr
op_plus
id|offs
)paren
op_assign
id|value
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
op_star
(paren
r_volatile
id|u_int32_t
op_star
)paren
(paren
id|va.vaddr
op_plus
id|offs
)paren
op_assign
id|value
suffix:semicolon
)brace
macro_line|#endif
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
r_int
r_int
id|offs
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
macro_line|#ifdef MEMCPYTOIO_WORKS
id|memcpy_toio
c_func
(paren
id|va.vaddr
op_plus
id|offs
comma
id|src
comma
id|len
)paren
suffix:semicolon
macro_line|#elif defined(MEMCPYTOIO_WRITEL)
mdefine_line|#define srcd ((const u_int32_t*)src)
r_if
c_cond
(paren
id|offs
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
id|mga_writel
c_func
(paren
id|va
comma
id|offs
comma
id|get_unaligned
c_func
(paren
id|srcd
op_increment
)paren
)paren
suffix:semicolon
id|offs
op_add_assign
l_int|4
suffix:semicolon
id|len
op_sub_assign
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
id|mga_writel
c_func
(paren
id|va
comma
id|offs
comma
op_star
id|srcd
op_increment
)paren
suffix:semicolon
id|offs
op_add_assign
l_int|4
suffix:semicolon
id|len
op_sub_assign
l_int|4
suffix:semicolon
)brace
)brace
macro_line|#undef srcd
r_if
c_cond
(paren
id|len
)paren
(brace
id|u_int32_t
id|tmp
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|tmp
comma
id|src
comma
id|len
)paren
suffix:semicolon
id|mga_writel
c_func
(paren
id|va
comma
id|offs
comma
id|tmp
)paren
suffix:semicolon
)brace
macro_line|#elif defined(MEMCPYTOIO_MEMCPY)
id|memcpy
c_func
(paren
id|va.vaddr
op_plus
id|offs
comma
id|src
comma
id|len
)paren
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Sorry, do not know how to write block of data to device&quot;
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
macro_line|#ifdef MAP_IOREMAP
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
macro_line|#else
macro_line|#ifdef MAP_BUSTOVIRT
id|virt-&gt;vaddr
op_assign
id|bus_to_virt
c_func
(paren
id|phys
)paren
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Your architecture does not have neither ioremap nor bus_to_virt... Giving up&quot;
macro_line|#endif
macro_line|#endif
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
macro_line|#ifdef MAP_IOREMAP
id|iounmap
c_func
(paren
id|va.vaddr
)paren
suffix:semicolon
macro_line|#endif
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
DECL|member|putc
r_void
(paren
op_star
id|putc
)paren
(paren
id|u_int32_t
comma
id|u_int32_t
comma
r_struct
id|display
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|putcs
r_void
(paren
op_star
id|putcs
)paren
(paren
id|u_int32_t
comma
id|u_int32_t
comma
r_struct
id|display
op_star
comma
r_const
r_int
r_int
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
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
DECL|member|cursorimage
r_int
r_int
id|cursorimage
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
multiline_comment|/* CRTC2 only */
multiline_comment|/* u_int32_t&t;TBD */
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
DECL|struct|matrox_altout
r_struct
id|matrox_altout
(brace
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
comma
r_struct
id|matrox_hw_state
op_star
id|state
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
comma
r_const
r_struct
id|matrox_hw_state
op_star
id|state
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
DECL|member|incuse
r_void
(paren
op_star
id|incuse
)paren
(paren
r_void
op_star
id|altout_dev
)paren
suffix:semicolon
DECL|member|decuse
r_void
(paren
op_star
id|decuse
)paren
(paren
r_void
op_star
id|altout_dev
)paren
suffix:semicolon
DECL|member|setmode
r_int
(paren
op_star
id|setmode
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
DECL|member|getmode
r_int
(paren
op_star
id|getmode
)paren
(paren
r_void
op_star
id|altout_dev
comma
id|u_int32_t
op_star
id|mode
)paren
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|matrox_switch
suffix:semicolon
r_struct
id|matroxfb_driver
suffix:semicolon
DECL|struct|matrox_fb_info
r_struct
id|matrox_fb_info
(brace
multiline_comment|/* fb_info must be first */
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
DECL|member|usecount
r_int
r_int
id|usecount
suffix:semicolon
DECL|member|curr
r_struct
id|matroxfb_par
id|curr
suffix:semicolon
DECL|member|hw1
r_struct
id|matrox_hw_state
id|hw1
suffix:semicolon
DECL|member|hw2
r_struct
id|matrox_hw_state
id|hw2
suffix:semicolon
DECL|member|newhw
r_struct
id|matrox_hw_state
op_star
id|newhw
suffix:semicolon
DECL|member|currenthw
r_struct
id|matrox_hw_state
op_star
id|currenthw
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
DECL|member|all
id|u_int32_t
id|all
suffix:semicolon
DECL|member|ph
id|u_int32_t
id|ph
suffix:semicolon
DECL|member|sh
id|u_int32_t
id|sh
suffix:semicolon
DECL|member|output
)brace
id|output
suffix:semicolon
DECL|member|primout
r_struct
id|matrox_altout
op_star
id|primout
suffix:semicolon
r_struct
(brace
DECL|member|info
r_struct
id|fb_info
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
DECL|member|output
r_struct
id|matrox_altout
op_star
id|output
suffix:semicolon
DECL|member|device
r_void
op_star
id|device
suffix:semicolon
DECL|member|lock
r_struct
id|rw_semaphore
id|lock
suffix:semicolon
DECL|member|altout
)brace
id|altout
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
DECL|member|currcon
r_int
id|currcon
suffix:semicolon
DECL|member|currcon_display
r_struct
id|display
op_star
id|currcon_display
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
r_struct
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|mgabase
r_int
r_int
id|mgabase
suffix:semicolon
DECL|member|vbase
id|vaddr_t
id|vbase
suffix:semicolon
DECL|member|fastfont
)brace
id|fastfont
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
DECL|member|inverse
r_int
id|inverse
suffix:semicolon
DECL|member|hwcursor
r_int
id|hwcursor
suffix:semicolon
DECL|member|blink
r_int
id|blink
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
DECL|member|devflags
)brace
id|devflags
suffix:semicolon
DECL|member|dispsw
r_struct
id|display_switch
id|dispsw
suffix:semicolon
r_struct
(brace
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
DECL|member|w
r_int
r_int
id|w
suffix:semicolon
DECL|member|u
r_int
r_int
id|u
suffix:semicolon
DECL|member|d
r_int
r_int
id|d
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|redraw
r_int
id|redraw
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|cursor
)brace
id|cursor
suffix:semicolon
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|transp
DECL|member|palette
r_struct
(brace
r_int
id|red
comma
id|green
comma
id|blue
comma
id|transp
suffix:semicolon
)brace
id|palette
(braket
l_int|256
)braket
suffix:semicolon
macro_line|#if defined(CONFIG_FB_COMPAT_XPMAC)
DECL|member|matrox_name
r_char
id|matrox_name
(braket
l_int|32
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/* These ifdefs must be last! They differ for module &amp; non-module compiles */
macro_line|#if defined(FBCON_HAS_CFB16) || defined(FBCON_HAS_CFB24) || defined(FBCON_HAS_CFB32)
r_union
(brace
macro_line|#ifdef FBCON_HAS_CFB16
DECL|member|cfb16
id|u_int16_t
id|cfb16
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB24
DECL|member|cfb24
id|u_int32_t
id|cfb24
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
DECL|member|cfb32
id|u_int32_t
id|cfb32
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
DECL|member|cmap
)brace
id|cmap
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
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
DECL|function|mxinfo
r_static
r_inline
r_struct
id|matrox_fb_info
op_star
id|mxinfo
c_func
(paren
r_const
r_struct
id|display
op_star
id|p
)paren
(brace
r_return
(paren
r_struct
id|matrox_fb_info
op_star
)paren
id|p-&gt;fb_info
suffix:semicolon
)brace
DECL|macro|PMXINFO
mdefine_line|#define PMXINFO(p)&t;   mxinfo(p),
DECL|macro|MINFO_FROM
mdefine_line|#define MINFO_FROM(x)&t;   struct matrox_fb_info* minfo = x
DECL|macro|MINFO_FROM_DISP
mdefine_line|#define MINFO_FROM_DISP(x) MINFO_FROM(mxinfo(x))
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
macro_line|#if 0
r_static
r_inline
r_struct
id|matrox_fb_info
op_star
id|mxinfo
c_func
(paren
r_const
r_struct
id|display
op_star
id|p
)paren
(brace
r_return
op_amp
id|matroxfb_global_mxinfo
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|PMXINFO
mdefine_line|#define PMXINFO(p)
DECL|macro|MINFO_FROM
mdefine_line|#define MINFO_FROM(x)
DECL|macro|MINFO_FROM_DISP
mdefine_line|#define MINFO_FROM_DISP(x)
macro_line|#endif
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
id|WPMINFO
r_struct
id|matrox_hw_state
op_star
)paren
suffix:semicolon
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
id|WPMINFO
r_struct
id|matrox_hw_state
op_star
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
id|CPMINFO
r_struct
id|matrox_hw_state
op_star
comma
r_struct
id|my_timming
op_star
comma
r_struct
id|display
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
id|WPMINFO
r_struct
id|matrox_hw_state
op_star
comma
r_struct
id|matrox_hw_state
op_star
comma
r_struct
id|display
op_star
)paren
suffix:semicolon
DECL|member|selhwcursor
r_int
(paren
op_star
id|selhwcursor
)paren
(paren
id|WPMINFO
r_struct
id|display
op_star
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
DECL|macro|PCI_MGA_INDEX
mdefine_line|#define PCI_MGA_INDEX&t;0x44
DECL|macro|PCI_MGA_DATA
mdefine_line|#define PCI_MGA_DATA&t;0x48
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
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|MX_OPTION_BSWAP
mdefine_line|#define MX_OPTION_BSWAP&t;&t;0x00000000
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
DECL|macro|MX_OPTION_BSWAP
mdefine_line|#define MX_OPTION_BSWAP&t;&t;0x80000000
DECL|macro|M_OPMODE_4BPP
mdefine_line|#define M_OPMODE_4BPP&t;(M_OPMODE_DMA_LE | M_OPMODE_DIR_LE | M_OPMODE_DMA_BLIT)&t;/* TODO */
DECL|macro|M_OPMODE_8BPP
mdefine_line|#define M_OPMODE_8BPP&t;(M_OPMODE_DMA_BE_8BPP  | M_OPMODE_DIR_BE_8BPP  | M_OPMODE_DMA_BLIT)
DECL|macro|M_OPMODE_16BPP
mdefine_line|#define M_OPMODE_16BPP&t;(M_OPMODE_DMA_BE_16BPP | M_OPMODE_DIR_BE_16BPP | M_OPMODE_DMA_BLIT)
DECL|macro|M_OPMODE_24BPP
mdefine_line|#define M_OPMODE_24BPP&t;(M_OPMODE_DMA_BE_8BPP | M_OPMODE_DIR_BE_8BPP | M_OPMODE_DMA_BLIT)&t;/* TODO, ?32 */
DECL|macro|M_OPMODE_32BPP
mdefine_line|#define M_OPMODE_32BPP&t;(M_OPMODE_DMA_BE_32BPP | M_OPMODE_DIR_BE_32BPP | M_OPMODE_DMA_BLIT)
macro_line|#else
macro_line|#error &quot;Byte ordering have to be defined. Cannot continue.&quot;
macro_line|#endif
macro_line|#endif
DECL|macro|mga_inb
mdefine_line|#define mga_inb(addr)&t;mga_readb(ACCESS_FBINFO(mmio.vbase), (addr))
DECL|macro|mga_inl
mdefine_line|#define mga_inl(addr)&t;mga_readl(ACCESS_FBINFO(mmio.vbase), (addr))
DECL|macro|mga_outb
mdefine_line|#define mga_outb(addr,val) mga_writeb(ACCESS_FBINFO(mmio.vbase), (addr), (val))
DECL|macro|mga_outw
mdefine_line|#define mga_outw(addr,val) mga_writew(ACCESS_FBINFO(mmio.vbase), (addr), (val))
DECL|macro|mga_outl
mdefine_line|#define mga_outl(addr,val) mga_writel(ACCESS_FBINFO(mmio.vbase), (addr), (val))
DECL|macro|mga_readr
mdefine_line|#define mga_readr(port,idx) (mga_outb((port),(idx)), mga_inb((port)+1))
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|mga_setr
mdefine_line|#define mga_setr(addr,port,val) mga_outw(addr, ((val)&lt;&lt;8) | (port))
macro_line|#else
DECL|macro|mga_setr
mdefine_line|#define mga_setr(addr,port,val) do { mga_outb(addr, port); mga_outb((addr)+1, val); } while (0)
macro_line|#endif
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
r_struct
id|list_head
id|matroxfb_list
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
