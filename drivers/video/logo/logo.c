multiline_comment|/*&n; *  Linux logo to be displayed on boot&n; *&n; *  Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)&n; *  Copyright (C) 1996,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *  Copyright (C) 2001 Greg Banks &lt;gnb@alphalink.com.au&gt;&n; *  Copyright (C) 2001 Jan-Benedict Glaw &lt;jbglaw@lug-owl.de&gt;&n; *  Copyright (C) 2003 Geert Uytterhoeven &lt;geert@linux-m68k.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linux_logo.h&gt;
macro_line|#ifdef CONFIG_M68K
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_MIPS) || defined(CONFIG_MIPS64)
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#endif
r_extern
r_const
r_struct
id|linux_logo
id|logo_linux_mono
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
id|logo_linux_vga16
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
id|logo_linux_clut224
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
id|logo_dec_clut224
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
id|logo_mac_clut224
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
id|logo_parisc_clut224
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
id|logo_sgi_clut224
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
id|logo_sun_clut224
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
id|logo_superh_mono
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
id|logo_superh_vga16
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
id|logo_superh_clut224
suffix:semicolon
DECL|function|fb_find_logo
r_const
r_struct
id|linux_logo
op_star
id|fb_find_logo
c_func
(paren
r_int
id|depth
)paren
(brace
r_const
r_struct
id|linux_logo
op_star
id|logo
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|depth
op_ge
l_int|1
)paren
(brace
macro_line|#ifdef CONFIG_LOGO_LINUX_MONO
multiline_comment|/* Generic Linux logo */
id|logo
op_assign
op_amp
id|logo_linux_mono
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LOGO_SUPERH_MONO
multiline_comment|/* SuperH Linux logo */
id|logo
op_assign
op_amp
id|logo_superh_mono
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|depth
op_ge
l_int|4
)paren
(brace
macro_line|#ifdef CONFIG_LOGO_LINUX_VGA16
multiline_comment|/* Generic Linux logo */
id|logo
op_assign
op_amp
id|logo_linux_vga16
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LOGO_SUPERH_VGA16
multiline_comment|/* SuperH Linux logo */
id|logo
op_assign
op_amp
id|logo_superh_vga16
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|depth
op_ge
l_int|8
)paren
(brace
macro_line|#ifdef CONFIG_LOGO_LINUX_CLUT224
multiline_comment|/* Generic Linux logo */
id|logo
op_assign
op_amp
id|logo_linux_clut224
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LOGO_DEC_CLUT224
multiline_comment|/* DEC Linux logo on MIPS/MIPS64 */
r_if
c_cond
(paren
id|mips_machgroup
op_eq
id|MACH_GROUP_DEC
)paren
id|logo
op_assign
op_amp
id|logo_dec_clut224
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LOGO_MAC_CLUT224
multiline_comment|/* Macintosh Linux logo on m68k */
r_if
c_cond
(paren
id|MACH_IS_MAC
)paren
id|logo
op_assign
op_amp
id|logo_mac_clut224
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LOGO_PARISC_CLUT224
multiline_comment|/* PA-RISC Linux logo */
id|logo
op_assign
op_amp
id|logo_parisc_clut224
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LOGO_SGI_CLUT224
multiline_comment|/* SGI Linux logo on MIPS/MIPS64 and VISWS */
macro_line|#ifndef CONFIG_X86_VISWS
r_if
c_cond
(paren
id|mips_machgroup
op_eq
id|MACH_GROUP_SGI
)paren
macro_line|#endif
id|logo
op_assign
op_amp
id|logo_sgi_clut224
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LOGO_SUN_CLUT224
multiline_comment|/* Sun Linux logo */
id|logo
op_assign
op_amp
id|logo_sun_clut224
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LOGO_SUPERH_CLUT224
multiline_comment|/* SuperH Linux logo */
id|logo
op_assign
op_amp
id|logo_superh_clut224
suffix:semicolon
macro_line|#endif
)brace
r_return
id|logo
suffix:semicolon
)brace
eof
