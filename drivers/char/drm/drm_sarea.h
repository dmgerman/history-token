multiline_comment|/**&n; * &bslash;file drm_sarea.h &n; * &bslash;brief SAREA definitions&n; *&n; * &bslash;author Michel D&#xfffd;nzer &lt;michel@daenzer.net&gt;&n; */
multiline_comment|/*&n; * Copyright 2002 Tungsten Graphics, Inc., Cedar Park, Texas.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#ifndef _DRM_SAREA_H_
DECL|macro|_DRM_SAREA_H_
mdefine_line|#define _DRM_SAREA_H_
multiline_comment|/** Maximum number of drawables in the SAREA */
DECL|macro|SAREA_MAX_DRAWABLES
mdefine_line|#define SAREA_MAX_DRAWABLES &t;&t;256
multiline_comment|/** SAREA drawable */
DECL|struct|drm_sarea_drawable
r_typedef
r_struct
id|drm_sarea_drawable
(brace
DECL|member|stamp
r_int
r_int
id|stamp
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|typedef|drm_sarea_drawable_t
)brace
id|drm_sarea_drawable_t
suffix:semicolon
multiline_comment|/** SAREA frame */
DECL|struct|drm_sarea_frame
r_typedef
r_struct
id|drm_sarea_frame
(brace
DECL|member|x
r_int
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
r_int
id|y
suffix:semicolon
DECL|member|width
r_int
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
r_int
id|height
suffix:semicolon
DECL|member|fullscreen
r_int
r_int
id|fullscreen
suffix:semicolon
DECL|typedef|drm_sarea_frame_t
)brace
id|drm_sarea_frame_t
suffix:semicolon
multiline_comment|/** SAREA */
DECL|struct|drm_sarea
r_typedef
r_struct
id|drm_sarea
(brace
multiline_comment|/** first thing is always the DRM locking structure */
DECL|member|lock
id|drm_hw_lock_t
id|lock
suffix:semicolon
multiline_comment|/** &bslash;todo Use readers/writer lock for drm_sarea::drawable_lock */
DECL|member|drawable_lock
id|drm_hw_lock_t
id|drawable_lock
suffix:semicolon
DECL|member|drawableTable
id|drm_sarea_drawable_t
id|drawableTable
(braket
id|SAREA_MAX_DRAWABLES
)braket
suffix:semicolon
multiline_comment|/**&lt; drawables */
DECL|member|frame
id|drm_sarea_frame_t
id|frame
suffix:semicolon
multiline_comment|/**&lt; frame */
DECL|member|dummy_context
id|drm_context_t
id|dummy_context
suffix:semicolon
DECL|typedef|drm_sarea_t
)brace
id|drm_sarea_t
suffix:semicolon
macro_line|#endif&t;/* _DRM_SAREA_H_ */
eof
