multiline_comment|/* $XConsortium: nv_driver.c /main/3 1996/10/28 05:13:37 kaleb $ */
multiline_comment|/*&n; * Copyright 1996-1997  David J. McKay&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included in&n; * all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * DAVID J. MCKAY BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,&n; * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF&n; * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; */
multiline_comment|/*&n; * GPL licensing note -- nVidia is allowing a liberal interpretation of&n; * the documentation restriction above, to merely say that this nVidia&squot;s&n; * copyright and disclaimer should be included with all code derived&n; * from this source.  -- Jeff Garzik &lt;jgarzik@pobox.com&gt;, 01/Nov/99 &n; */
multiline_comment|/* Hacked together from mga driver and 3.3.4 NVIDIA driver by Jarno Paananen&n;   &lt;jpaana@s2.org&gt; */
multiline_comment|/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/nv/nv_setup.c,v 1.18 2002/08/0&n;5 20:47:06 mvojkovi Exp $ */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/pci_ids.h&gt;
macro_line|#include &quot;nv_type.h&quot;
macro_line|#include &quot;rivafb.h&quot;
macro_line|#include &quot;nvreg.h&quot;
macro_line|#ifndef CONFIG_PCI&t;&t;/* sanity check */
macro_line|#error This driver requires PCI support.
macro_line|#endif
DECL|macro|PFX
mdefine_line|#define PFX &quot;rivafb: &quot;
DECL|function|MISCin
r_static
r_inline
r_int
r_char
id|MISCin
c_func
(paren
r_struct
id|riva_par
op_star
id|par
)paren
(brace
r_return
(paren
id|VGA_RD08
c_func
(paren
id|par-&gt;riva.PVIO
comma
l_int|0x3cc
)paren
)paren
suffix:semicolon
)brace
r_static
id|Bool
DECL|function|riva_is_connected
id|riva_is_connected
c_func
(paren
r_struct
id|riva_par
op_star
id|par
comma
id|Bool
id|second
)paren
(brace
r_volatile
id|U032
id|__iomem
op_star
id|PRAMDAC
op_assign
id|par-&gt;riva.PRAMDAC0
suffix:semicolon
id|U032
id|reg52C
comma
id|reg608
suffix:semicolon
id|Bool
id|present
suffix:semicolon
r_if
c_cond
(paren
id|second
)paren
(brace
id|PRAMDAC
op_add_assign
l_int|0x800
suffix:semicolon
)brace
id|reg52C
op_assign
id|NV_RD32
c_func
(paren
id|PRAMDAC
comma
l_int|0x052C
)paren
suffix:semicolon
id|reg608
op_assign
id|NV_RD32
c_func
(paren
id|PRAMDAC
comma
l_int|0x0608
)paren
suffix:semicolon
id|NV_WR32
c_func
(paren
id|PRAMDAC
comma
l_int|0x0608
comma
id|reg608
op_amp
op_complement
l_int|0x00010000
)paren
suffix:semicolon
id|NV_WR32
c_func
(paren
id|PRAMDAC
comma
l_int|0x052C
comma
id|reg52C
op_amp
l_int|0x0000FEEE
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|NV_WR32
c_func
(paren
id|PRAMDAC
comma
l_int|0x052C
comma
id|NV_RD32
c_func
(paren
id|PRAMDAC
comma
l_int|0x052C
)paren
op_or
l_int|1
)paren
suffix:semicolon
id|NV_WR32
c_func
(paren
id|par-&gt;riva.PRAMDAC0
comma
l_int|0x0610
comma
l_int|0x94050140
)paren
suffix:semicolon
id|NV_WR32
c_func
(paren
id|par-&gt;riva.PRAMDAC0
comma
l_int|0x0608
comma
l_int|0x00001000
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|present
op_assign
(paren
id|NV_RD32
c_func
(paren
id|PRAMDAC
comma
l_int|0x0608
)paren
op_amp
(paren
l_int|1
op_lshift
l_int|28
)paren
)paren
ques
c_cond
id|TRUE
suffix:colon
id|FALSE
suffix:semicolon
id|NV_WR32
c_func
(paren
id|par-&gt;riva.PRAMDAC0
comma
l_int|0x0608
comma
id|NV_RD32
c_func
(paren
id|par-&gt;riva.PRAMDAC0
comma
l_int|0x0608
)paren
op_amp
l_int|0x0000EFFF
)paren
suffix:semicolon
id|NV_WR32
c_func
(paren
id|PRAMDAC
comma
l_int|0x052C
comma
id|reg52C
)paren
suffix:semicolon
id|NV_WR32
c_func
(paren
id|PRAMDAC
comma
l_int|0x0608
comma
id|reg608
)paren
suffix:semicolon
r_return
id|present
suffix:semicolon
)brace
r_static
r_void
DECL|function|riva_override_CRTC
id|riva_override_CRTC
c_func
(paren
r_struct
id|riva_par
op_star
id|par
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected CRTC controller %i being used&bslash;n&quot;
comma
id|par-&gt;SecondCRTC
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;forceCRTC
op_ne
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Forcing usage of CRTC %i&bslash;n&quot;
comma
id|par-&gt;forceCRTC
)paren
suffix:semicolon
id|par-&gt;SecondCRTC
op_assign
id|par-&gt;forceCRTC
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|riva_is_second
id|riva_is_second
c_func
(paren
r_struct
id|riva_par
op_star
id|par
)paren
(brace
r_if
c_cond
(paren
id|par-&gt;FlatPanel
op_eq
l_int|1
)paren
(brace
r_switch
c_cond
(paren
id|par-&gt;Chipset
op_amp
l_int|0xffff
)paren
(brace
r_case
l_int|0x0174
suffix:colon
r_case
l_int|0x0175
suffix:colon
r_case
l_int|0x0176
suffix:colon
r_case
l_int|0x0177
suffix:colon
r_case
l_int|0x0179
suffix:colon
r_case
l_int|0x017C
suffix:colon
r_case
l_int|0x017D
suffix:colon
r_case
l_int|0x0186
suffix:colon
r_case
l_int|0x0187
suffix:colon
multiline_comment|/* this might not be a good default for the chips below */
r_case
l_int|0x0286
suffix:colon
r_case
l_int|0x028C
suffix:colon
r_case
l_int|0x0316
suffix:colon
r_case
l_int|0x0317
suffix:colon
r_case
l_int|0x031A
suffix:colon
r_case
l_int|0x031B
suffix:colon
r_case
l_int|0x031C
suffix:colon
r_case
l_int|0x031D
suffix:colon
r_case
l_int|0x031E
suffix:colon
r_case
l_int|0x031F
suffix:colon
r_case
l_int|0x0324
suffix:colon
r_case
l_int|0x0325
suffix:colon
r_case
l_int|0x0328
suffix:colon
r_case
l_int|0x0329
suffix:colon
r_case
l_int|0x032C
suffix:colon
r_case
l_int|0x032D
suffix:colon
id|par-&gt;SecondCRTC
op_assign
id|TRUE
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|par-&gt;SecondCRTC
op_assign
id|FALSE
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|riva_is_connected
c_func
(paren
id|par
comma
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
id|NV_RD32
c_func
(paren
id|par-&gt;riva.PRAMDAC0
comma
l_int|0x0000052C
)paren
op_amp
l_int|0x100
)paren
id|par-&gt;SecondCRTC
op_assign
id|TRUE
suffix:semicolon
r_else
id|par-&gt;SecondCRTC
op_assign
id|FALSE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|riva_is_connected
c_func
(paren
id|par
comma
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
id|NV_RD32
c_func
(paren
id|par-&gt;riva.PRAMDAC0
comma
l_int|0x0000252C
)paren
op_amp
l_int|0x100
)paren
(brace
id|par-&gt;SecondCRTC
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
id|par-&gt;SecondCRTC
op_assign
id|FALSE
suffix:semicolon
)brace
r_else
multiline_comment|/* default */
id|par-&gt;SecondCRTC
op_assign
id|FALSE
suffix:semicolon
)brace
id|riva_override_CRTC
c_func
(paren
id|par
)paren
suffix:semicolon
)brace
DECL|function|riva_get_memlen
r_int
r_int
id|riva_get_memlen
c_func
(paren
r_struct
id|riva_par
op_star
id|par
)paren
(brace
id|RIVA_HW_INST
op_star
id|chip
op_assign
op_amp
id|par-&gt;riva
suffix:semicolon
r_int
r_int
id|memlen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|chipset
op_assign
id|par-&gt;Chipset
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|amt
suffix:semicolon
r_switch
c_cond
(paren
id|chip-&gt;Architecture
)paren
(brace
r_case
id|NV_ARCH_03
suffix:colon
r_if
c_cond
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PFB
comma
l_int|0x00000000
)paren
op_amp
l_int|0x00000020
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PMC
comma
l_int|0x00000000
)paren
op_amp
l_int|0xF0
)paren
op_eq
l_int|0x20
)paren
op_logical_and
(paren
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PMC
comma
l_int|0x00000000
)paren
op_amp
l_int|0x0F
)paren
op_ge
l_int|0x02
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * SDRAM 128 ZX.&n;&t;&t;&t;&t; */
r_switch
c_cond
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PFB
comma
l_int|0x00000000
)paren
op_amp
l_int|0x03
)paren
(brace
r_case
l_int|2
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|memlen
op_assign
l_int|1024
op_star
l_int|8
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * SGRAM 128.&n;&t;&t;&t; */
r_switch
c_cond
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PFB
comma
l_int|0x00000000
)paren
op_amp
l_int|0x00000003
)paren
(brace
r_case
l_int|0
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|NV_ARCH_04
suffix:colon
r_if
c_cond
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PFB
comma
l_int|0x00000000
)paren
op_amp
l_int|0x00000100
)paren
(brace
id|memlen
op_assign
(paren
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PFB
comma
l_int|0x00000000
)paren
op_rshift
l_int|12
)paren
op_amp
l_int|0x0F
)paren
op_star
l_int|1024
op_star
l_int|2
op_plus
l_int|1024
op_star
l_int|2
suffix:semicolon
)brace
r_else
(brace
r_switch
c_cond
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PFB
comma
l_int|0x00000000
)paren
op_amp
l_int|0x00000003
)paren
(brace
r_case
l_int|0
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_default
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|16
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|NV_ARCH_10
suffix:colon
r_case
id|NV_ARCH_20
suffix:colon
r_case
id|NV_ARCH_30
suffix:colon
r_if
c_cond
(paren
id|chipset
op_eq
id|NV_CHIP_IGEFORCE2
)paren
(brace
id|dev
op_assign
id|pci_find_slot
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x7C
comma
op_amp
id|amt
)paren
suffix:semicolon
id|memlen
op_assign
(paren
(paren
(paren
id|amt
op_rshift
l_int|6
)paren
op_amp
l_int|31
)paren
op_plus
l_int|1
)paren
op_star
l_int|1024
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|chipset
op_eq
id|NV_CHIP_0x01F0
)paren
(brace
id|dev
op_assign
id|pci_find_slot
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x84
comma
op_amp
id|amt
)paren
suffix:semicolon
id|memlen
op_assign
(paren
(paren
(paren
id|amt
op_rshift
l_int|4
)paren
op_amp
l_int|127
)paren
op_plus
l_int|1
)paren
op_star
l_int|1024
suffix:semicolon
)brace
r_else
(brace
r_switch
c_cond
(paren
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PFB
comma
l_int|0x0000020C
)paren
op_rshift
l_int|20
)paren
op_amp
l_int|0x000000FF
)paren
(brace
r_case
l_int|0x02
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x08
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x10
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x20
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x40
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|64
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x80
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|128
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|memlen
op_assign
l_int|1024
op_star
l_int|16
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_return
id|memlen
suffix:semicolon
)brace
DECL|function|riva_get_maxdclk
r_int
r_int
id|riva_get_maxdclk
c_func
(paren
r_struct
id|riva_par
op_star
id|par
)paren
(brace
id|RIVA_HW_INST
op_star
id|chip
op_assign
op_amp
id|par-&gt;riva
suffix:semicolon
r_int
r_int
id|dclk
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|chip-&gt;Architecture
)paren
(brace
r_case
id|NV_ARCH_03
suffix:colon
r_if
c_cond
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PFB
comma
l_int|0x00000000
)paren
op_amp
l_int|0x00000020
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PMC
comma
l_int|0x00000000
)paren
op_amp
l_int|0xF0
)paren
op_eq
l_int|0x20
)paren
op_logical_and
(paren
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PMC
comma
l_int|0x00000000
)paren
op_amp
l_int|0x0F
)paren
op_ge
l_int|0x02
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * SDRAM 128 ZX.&n;&t;&t;&t;&t; */
id|dclk
op_assign
l_int|800000
suffix:semicolon
)brace
r_else
(brace
id|dclk
op_assign
l_int|1000000
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * SGRAM 128.&n;&t;&t;&t; */
id|dclk
op_assign
l_int|1000000
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NV_ARCH_04
suffix:colon
r_case
id|NV_ARCH_10
suffix:colon
r_case
id|NV_ARCH_20
suffix:colon
r_case
id|NV_ARCH_30
suffix:colon
r_switch
c_cond
(paren
(paren
id|NV_RD32
c_func
(paren
id|chip-&gt;PFB
comma
l_int|0x00000000
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x00000003
)paren
(brace
r_case
l_int|3
suffix:colon
id|dclk
op_assign
l_int|800000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dclk
op_assign
l_int|1000000
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|dclk
suffix:semicolon
)brace
r_void
DECL|function|riva_common_setup
id|riva_common_setup
c_func
(paren
r_struct
id|riva_par
op_star
id|par
)paren
(brace
id|par-&gt;riva.EnableIRQ
op_assign
l_int|0
suffix:semicolon
id|par-&gt;riva.PRAMDAC0
op_assign
(paren
r_volatile
id|U032
id|__iomem
op_star
)paren
(paren
id|par-&gt;ctrl_base
op_plus
l_int|0x00680000
)paren
suffix:semicolon
id|par-&gt;riva.PFB
op_assign
(paren
r_volatile
id|U032
id|__iomem
op_star
)paren
(paren
id|par-&gt;ctrl_base
op_plus
l_int|0x00100000
)paren
suffix:semicolon
id|par-&gt;riva.PFIFO
op_assign
(paren
r_volatile
id|U032
id|__iomem
op_star
)paren
(paren
id|par-&gt;ctrl_base
op_plus
l_int|0x00002000
)paren
suffix:semicolon
id|par-&gt;riva.PGRAPH
op_assign
(paren
r_volatile
id|U032
id|__iomem
op_star
)paren
(paren
id|par-&gt;ctrl_base
op_plus
l_int|0x00400000
)paren
suffix:semicolon
id|par-&gt;riva.PEXTDEV
op_assign
(paren
r_volatile
id|U032
id|__iomem
op_star
)paren
(paren
id|par-&gt;ctrl_base
op_plus
l_int|0x00101000
)paren
suffix:semicolon
id|par-&gt;riva.PTIMER
op_assign
(paren
r_volatile
id|U032
id|__iomem
op_star
)paren
(paren
id|par-&gt;ctrl_base
op_plus
l_int|0x00009000
)paren
suffix:semicolon
id|par-&gt;riva.PMC
op_assign
(paren
r_volatile
id|U032
id|__iomem
op_star
)paren
(paren
id|par-&gt;ctrl_base
op_plus
l_int|0x00000000
)paren
suffix:semicolon
id|par-&gt;riva.FIFO
op_assign
(paren
r_volatile
id|U032
id|__iomem
op_star
)paren
(paren
id|par-&gt;ctrl_base
op_plus
l_int|0x00800000
)paren
suffix:semicolon
id|par-&gt;riva.PCIO0
op_assign
id|par-&gt;ctrl_base
op_plus
l_int|0x00601000
suffix:semicolon
id|par-&gt;riva.PDIO0
op_assign
id|par-&gt;ctrl_base
op_plus
l_int|0x00681000
suffix:semicolon
id|par-&gt;riva.PVIO
op_assign
id|par-&gt;ctrl_base
op_plus
l_int|0x000C0000
suffix:semicolon
id|par-&gt;riva.IO
op_assign
(paren
id|MISCin
c_func
(paren
id|par
)paren
op_amp
l_int|0x01
)paren
ques
c_cond
l_int|0x3D0
suffix:colon
l_int|0x3B0
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;FlatPanel
op_eq
op_minus
l_int|1
)paren
(brace
r_switch
c_cond
(paren
id|par-&gt;Chipset
op_amp
l_int|0xffff
)paren
(brace
r_case
l_int|0x0112
suffix:colon
multiline_comment|/* known laptop chips */
r_case
l_int|0x0174
suffix:colon
r_case
l_int|0x0175
suffix:colon
r_case
l_int|0x0176
suffix:colon
r_case
l_int|0x0177
suffix:colon
r_case
l_int|0x0179
suffix:colon
r_case
l_int|0x017C
suffix:colon
r_case
l_int|0x017D
suffix:colon
r_case
l_int|0x0186
suffix:colon
r_case
l_int|0x0187
suffix:colon
r_case
l_int|0x0286
suffix:colon
r_case
l_int|0x028C
suffix:colon
r_case
l_int|0x0316
suffix:colon
r_case
l_int|0x0317
suffix:colon
r_case
l_int|0x031A
suffix:colon
r_case
l_int|0x031B
suffix:colon
r_case
l_int|0x031C
suffix:colon
r_case
l_int|0x031D
suffix:colon
r_case
l_int|0x031E
suffix:colon
r_case
l_int|0x031F
suffix:colon
r_case
l_int|0x0324
suffix:colon
r_case
l_int|0x0325
suffix:colon
r_case
l_int|0x0328
suffix:colon
r_case
l_int|0x0329
suffix:colon
r_case
l_int|0x032C
suffix:colon
r_case
l_int|0x032D
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;On a laptop.  Assuming Digital Flat Panel&bslash;n&quot;
)paren
suffix:semicolon
id|par-&gt;FlatPanel
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|par-&gt;Chipset
op_amp
l_int|0x0ff0
)paren
(brace
r_case
l_int|0x0110
suffix:colon
r_if
c_cond
(paren
id|par-&gt;Chipset
op_eq
id|NV_CHIP_GEFORCE2_GO
)paren
id|par-&gt;SecondCRTC
op_assign
id|TRUE
suffix:semicolon
macro_line|#if defined(__powerpc__)
r_if
c_cond
(paren
id|par-&gt;FlatPanel
op_eq
l_int|1
)paren
id|par-&gt;SecondCRTC
op_assign
id|TRUE
suffix:semicolon
macro_line|#endif
id|riva_override_CRTC
c_func
(paren
id|par
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0170
suffix:colon
r_case
l_int|0x0180
suffix:colon
r_case
l_int|0x01F0
suffix:colon
r_case
l_int|0x0250
suffix:colon
r_case
l_int|0x0280
suffix:colon
r_case
l_int|0x0300
suffix:colon
r_case
l_int|0x0310
suffix:colon
r_case
l_int|0x0320
suffix:colon
r_case
l_int|0x0330
suffix:colon
r_case
l_int|0x0340
suffix:colon
id|riva_is_second
c_func
(paren
id|par
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|par-&gt;SecondCRTC
)paren
(brace
id|par-&gt;riva.PCIO
op_assign
id|par-&gt;riva.PCIO0
op_plus
l_int|0x2000
suffix:semicolon
id|par-&gt;riva.PCRTC
op_assign
id|par-&gt;riva.PCRTC0
op_plus
l_int|0x800
suffix:semicolon
id|par-&gt;riva.PRAMDAC
op_assign
id|par-&gt;riva.PRAMDAC0
op_plus
l_int|0x800
suffix:semicolon
id|par-&gt;riva.PDIO
op_assign
id|par-&gt;riva.PDIO0
op_plus
l_int|0x2000
suffix:semicolon
)brace
r_else
(brace
id|par-&gt;riva.PCIO
op_assign
id|par-&gt;riva.PCIO0
suffix:semicolon
id|par-&gt;riva.PCRTC
op_assign
id|par-&gt;riva.PCRTC0
suffix:semicolon
id|par-&gt;riva.PRAMDAC
op_assign
id|par-&gt;riva.PRAMDAC0
suffix:semicolon
id|par-&gt;riva.PDIO
op_assign
id|par-&gt;riva.PDIO0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|par-&gt;FlatPanel
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* Fix me, need x86 DDC code */
id|par-&gt;FlatPanel
op_assign
l_int|0
suffix:semicolon
)brace
id|par-&gt;riva.flatPanel
op_assign
(paren
id|par-&gt;FlatPanel
OG
l_int|0
)paren
ques
c_cond
id|TRUE
suffix:colon
id|FALSE
suffix:semicolon
id|RivaGetConfig
c_func
(paren
op_amp
id|par-&gt;riva
comma
id|par-&gt;Chipset
)paren
suffix:semicolon
)brace
eof
