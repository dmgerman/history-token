multiline_comment|/* mga_warp.c -- Matrox G200/G400 WARP engine management -*- linux-c -*-&n; * Created: Thu Jan 11 21:29:32 2001 by gareth@valinux.com&n; *&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm.h&quot;
macro_line|#include &quot;mga_drm.h&quot;
macro_line|#include &quot;mga_drv.h&quot;
macro_line|#include &quot;mga_ucode.h&quot;
DECL|macro|MGA_WARP_CODE_ALIGN
mdefine_line|#define MGA_WARP_CODE_ALIGN&t;&t;256&t;&t;/* in bytes */
DECL|macro|WARP_UCODE_SIZE
mdefine_line|#define WARP_UCODE_SIZE( which )&t;&t;&t;&t;&t;&bslash;&n;&t;((sizeof(which) / MGA_WARP_CODE_ALIGN + 1) * MGA_WARP_CODE_ALIGN)
DECL|macro|WARP_UCODE_INSTALL
mdefine_line|#define WARP_UCODE_INSTALL( which, where )&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DRM_DEBUG( &quot; pcbase = 0x%08lx  vcbase = %p&bslash;n&quot;, pcbase, vcbase );&bslash;&n;&t;dev_priv-&gt;warp_pipe_phys[where] = pcbase;&t;&t;&t;&bslash;&n;&t;memcpy( vcbase, which, sizeof(which) );&t;&t;&t;&t;&bslash;&n;&t;pcbase += WARP_UCODE_SIZE( which );&t;&t;&t;&t;&bslash;&n;&t;vcbase += WARP_UCODE_SIZE( which );&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|function|mga_warp_g400_microcode_size
r_static
r_int
r_int
id|mga_warp_g400_microcode_size
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
id|size
op_assign
(paren
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_tgz
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_tgza
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_tgzaf
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_tgzf
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_tgzs
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_tgzsa
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_tgzsaf
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_tgzsf
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_t2gz
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_t2gza
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_t2gzaf
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_t2gzf
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_t2gzs
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_t2gzsa
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_t2gzsaf
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g400_t2gzsf
)paren
)paren
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;G400 ucode size = %d bytes&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|mga_warp_g200_microcode_size
r_static
r_int
r_int
id|mga_warp_g200_microcode_size
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
id|size
op_assign
(paren
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g200_tgz
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g200_tgza
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g200_tgzaf
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g200_tgzf
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g200_tgzs
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g200_tgzsa
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g200_tgzsaf
)paren
op_plus
id|WARP_UCODE_SIZE
c_func
(paren
id|warp_g200_tgzsf
)paren
)paren
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;G200 ucode size = %d bytes&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|mga_warp_install_g400_microcode
r_static
r_int
id|mga_warp_install_g400_microcode
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
(brace
r_int
r_char
op_star
id|vcbase
op_assign
id|dev_priv-&gt;warp-&gt;handle
suffix:semicolon
r_int
r_int
id|pcbase
op_assign
id|dev_priv-&gt;warp-&gt;offset
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|size
op_assign
id|mga_warp_g400_microcode_size
c_func
(paren
id|dev_priv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|dev_priv-&gt;warp-&gt;size
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;microcode too large! (%u &gt; %lu)&bslash;n&quot;
comma
id|size
comma
id|dev_priv-&gt;warp-&gt;size
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|ENOMEM
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev_priv-&gt;warp_pipe_phys
comma
l_int|0
comma
r_sizeof
(paren
id|dev_priv-&gt;warp_pipe_phys
)paren
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_tgz
comma
id|MGA_WARP_TGZ
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_tgzf
comma
id|MGA_WARP_TGZF
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_tgza
comma
id|MGA_WARP_TGZA
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_tgzaf
comma
id|MGA_WARP_TGZAF
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_tgzs
comma
id|MGA_WARP_TGZS
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_tgzsf
comma
id|MGA_WARP_TGZSF
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_tgzsa
comma
id|MGA_WARP_TGZSA
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_tgzsaf
comma
id|MGA_WARP_TGZSAF
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_t2gz
comma
id|MGA_WARP_T2GZ
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_t2gzf
comma
id|MGA_WARP_T2GZF
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_t2gza
comma
id|MGA_WARP_T2GZA
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_t2gzaf
comma
id|MGA_WARP_T2GZAF
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_t2gzs
comma
id|MGA_WARP_T2GZS
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_t2gzsf
comma
id|MGA_WARP_T2GZSF
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_t2gzsa
comma
id|MGA_WARP_T2GZSA
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g400_t2gzsaf
comma
id|MGA_WARP_T2GZSAF
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mga_warp_install_g200_microcode
r_static
r_int
id|mga_warp_install_g200_microcode
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
(brace
r_int
r_char
op_star
id|vcbase
op_assign
id|dev_priv-&gt;warp-&gt;handle
suffix:semicolon
r_int
r_int
id|pcbase
op_assign
id|dev_priv-&gt;warp-&gt;offset
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|size
op_assign
id|mga_warp_g200_microcode_size
c_func
(paren
id|dev_priv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|dev_priv-&gt;warp-&gt;size
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;microcode too large! (%u &gt; %lu)&bslash;n&quot;
comma
id|size
comma
id|dev_priv-&gt;warp-&gt;size
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|ENOMEM
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev_priv-&gt;warp_pipe_phys
comma
l_int|0
comma
r_sizeof
(paren
id|dev_priv-&gt;warp_pipe_phys
)paren
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g200_tgz
comma
id|MGA_WARP_TGZ
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g200_tgzf
comma
id|MGA_WARP_TGZF
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g200_tgza
comma
id|MGA_WARP_TGZA
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g200_tgzaf
comma
id|MGA_WARP_TGZAF
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g200_tgzs
comma
id|MGA_WARP_TGZS
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g200_tgzsf
comma
id|MGA_WARP_TGZSF
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g200_tgzsa
comma
id|MGA_WARP_TGZSA
)paren
suffix:semicolon
id|WARP_UCODE_INSTALL
c_func
(paren
id|warp_g200_tgzsaf
comma
id|MGA_WARP_TGZSAF
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mga_warp_install_microcode
r_int
id|mga_warp_install_microcode
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
(brace
r_switch
c_cond
(paren
id|dev_priv-&gt;chipset
)paren
(brace
r_case
id|MGA_CARD_TYPE_G400
suffix:colon
r_return
id|mga_warp_install_g400_microcode
c_func
(paren
id|dev_priv
)paren
suffix:semicolon
r_case
id|MGA_CARD_TYPE_G200
suffix:colon
r_return
id|mga_warp_install_g200_microcode
c_func
(paren
id|dev_priv
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
)brace
DECL|macro|WMISC_EXPECTED
mdefine_line|#define WMISC_EXPECTED&t;&t;(MGA_WUCODECACHE_ENABLE | MGA_WMASTER_ENABLE)
DECL|function|mga_warp_init
r_int
id|mga_warp_init
c_func
(paren
id|drm_mga_private_t
op_star
id|dev_priv
)paren
(brace
id|u32
id|wmisc
suffix:semicolon
multiline_comment|/* FIXME: Get rid of these damned magic numbers...&n;&t; */
r_switch
c_cond
(paren
id|dev_priv-&gt;chipset
)paren
(brace
r_case
id|MGA_CARD_TYPE_G400
suffix:colon
id|MGA_WRITE
c_func
(paren
id|MGA_WIADDR2
comma
id|MGA_WMODE_SUSPEND
)paren
suffix:semicolon
id|MGA_WRITE
c_func
(paren
id|MGA_WGETMSB
comma
l_int|0x00000E00
)paren
suffix:semicolon
id|MGA_WRITE
c_func
(paren
id|MGA_WVRTXSZ
comma
l_int|0x00001807
)paren
suffix:semicolon
id|MGA_WRITE
c_func
(paren
id|MGA_WACCEPTSEQ
comma
l_int|0x18000000
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MGA_CARD_TYPE_G200
suffix:colon
id|MGA_WRITE
c_func
(paren
id|MGA_WIADDR
comma
id|MGA_WMODE_SUSPEND
)paren
suffix:semicolon
id|MGA_WRITE
c_func
(paren
id|MGA_WGETMSB
comma
l_int|0x1606
)paren
suffix:semicolon
id|MGA_WRITE
c_func
(paren
id|MGA_WVRTXSZ
comma
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
id|MGA_WRITE
c_func
(paren
id|MGA_WMISC
comma
(paren
id|MGA_WUCODECACHE_ENABLE
op_or
id|MGA_WMASTER_ENABLE
op_or
id|MGA_WCACHEFLUSH_ENABLE
)paren
)paren
suffix:semicolon
id|wmisc
op_assign
id|MGA_READ
c_func
(paren
id|MGA_WMISC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wmisc
op_ne
id|WMISC_EXPECTED
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;WARP engine config failed! 0x%x != 0x%x&bslash;n&quot;
comma
id|wmisc
comma
id|WMISC_EXPECTED
)paren
suffix:semicolon
r_return
id|DRM_ERR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
