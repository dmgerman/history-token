multiline_comment|/* r128_irq.c -- IRQ handling for radeon -*- linux-c -*-&n; *&n; * Copyright (C) The Weather Channel, Inc.  2002.  All Rights Reserved.&n; * &n; * The Weather Channel (TM) funded Tungsten Graphics to develop the&n; * initial release of the Radeon 8500 driver under the XFree86 license.&n; * This notice must be preserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Keith Whitwell &lt;keith@tungstengraphics.com&gt;&n; *    Eric Anholt &lt;anholt@FreeBSD.org&gt;&n; */
macro_line|#include &quot;r128.h&quot;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;drm.h&quot;
macro_line|#include &quot;r128_drm.h&quot;
macro_line|#include &quot;r128_drv.h&quot;
DECL|function|r128_dma_service
id|irqreturn_t
id|r128_dma_service
c_func
(paren
id|DRM_IRQ_ARGS
)paren
(brace
id|drm_device_t
op_star
id|dev
op_assign
(paren
id|drm_device_t
op_star
)paren
id|arg
suffix:semicolon
id|drm_r128_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_r128_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
r_int
id|status
suffix:semicolon
id|status
op_assign
id|R128_READ
c_func
(paren
id|R128_GEN_INT_STATUS
)paren
suffix:semicolon
multiline_comment|/* VBLANK interrupt */
r_if
c_cond
(paren
id|status
op_amp
id|R128_CRTC_VBLANK_INT
)paren
(brace
id|R128_WRITE
c_func
(paren
id|R128_GEN_INT_STATUS
comma
id|R128_CRTC_VBLANK_INT_AK
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;vbl_received
)paren
suffix:semicolon
id|DRM_WAKEUP
c_func
(paren
op_amp
id|dev-&gt;vbl_queue
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|vbl_send_signals
)paren
(paren
id|dev
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_return
id|IRQ_NONE
suffix:semicolon
)brace
DECL|function|vblank_wait
r_int
id|DRM
c_func
(paren
id|vblank_wait
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
r_int
op_star
id|sequence
)paren
(brace
r_int
r_int
id|cur_vblank
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Assume that the user has missed the current sequence number&n;&t; * by about a day rather than she wants to wait for years&n;&t; * using vertical blanks... &n;&t; */
id|DRM_WAIT_ON
c_func
(paren
id|ret
comma
id|dev-&gt;vbl_queue
comma
l_int|3
op_star
id|DRM_HZ
comma
(paren
(paren
(paren
id|cur_vblank
op_assign
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;vbl_received
)paren
)paren
op_minus
op_star
id|sequence
)paren
op_le
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
)paren
suffix:semicolon
op_star
id|sequence
op_assign
id|cur_vblank
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|r128_driver_irq_preinstall
r_void
id|r128_driver_irq_preinstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_r128_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_r128_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
multiline_comment|/* Disable *all* interrupts */
id|R128_WRITE
c_func
(paren
id|R128_GEN_INT_CNTL
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Clear vblank bit if it&squot;s already high */
id|R128_WRITE
c_func
(paren
id|R128_GEN_INT_STATUS
comma
id|R128_CRTC_VBLANK_INT_AK
)paren
suffix:semicolon
)brace
DECL|function|r128_driver_irq_postinstall
r_void
id|r128_driver_irq_postinstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_r128_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_r128_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
multiline_comment|/* Turn on VBL interrupt */
id|R128_WRITE
c_func
(paren
id|R128_GEN_INT_CNTL
comma
id|R128_CRTC_VBLANK_INT_EN
)paren
suffix:semicolon
)brace
DECL|function|r128_driver_irq_uninstall
r_void
id|r128_driver_irq_uninstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|drm_r128_private_t
op_star
id|dev_priv
op_assign
(paren
id|drm_r128_private_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
r_if
c_cond
(paren
id|dev_priv
)paren
(brace
multiline_comment|/* Disable *all* interrupts */
id|R128_WRITE
c_func
(paren
id|R128_GEN_INT_CNTL
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
eof
