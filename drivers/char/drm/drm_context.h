multiline_comment|/**&n; * &bslash;file drm_context.h &n; * IOCTLs for generic contexts&n; * &n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/*&n; * Created: Fri Nov 24 18:31:37 2000 by gareth@valinux.com&n; *&n; * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
multiline_comment|/*&n; * ChangeLog:&n; *  2001-11-16&t;Torsten Duwe &lt;duwe@caldera.de&gt;&n; *&t;&t;added context constructor/destructor hooks,&n; *&t;&t;needed by SiS driver&squot;s memory management.&n; */
macro_line|#include &quot;drmP.h&quot;
macro_line|#if !__HAVE_CTX_BITMAP
macro_line|#error &quot;__HAVE_CTX_BITMAP must be defined&quot;
macro_line|#endif
multiline_comment|/******************************************************************/
multiline_comment|/** &bslash;name Context bitmap support */
multiline_comment|/*@{*/
multiline_comment|/**&n; * Free a handle from the context bitmap.&n; *&n; * &bslash;param dev DRM device.&n; * &bslash;param ctx_handle context handle.&n; *&n; * Clears the bit specified by &bslash;p ctx_handle in drm_device::ctx_bitmap and the entry&n; * in drm_device::context_sareas, while holding the drm_device::struct_sem&n; * lock.&n; */
DECL|function|ctxbitmap_free
r_void
id|DRM
c_func
(paren
id|ctxbitmap_free
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|ctx_handle
)paren
(brace
r_if
c_cond
(paren
id|ctx_handle
OL
l_int|0
)paren
r_goto
id|failed
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ctx_bitmap
)paren
r_goto
id|failed
suffix:semicolon
r_if
c_cond
(paren
id|ctx_handle
OL
id|DRM_MAX_CTXBITMAP
)paren
(brace
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|ctx_handle
comma
id|dev-&gt;ctx_bitmap
)paren
suffix:semicolon
id|dev-&gt;context_sareas
(braket
id|ctx_handle
)braket
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|failed
suffix:colon
id|DRM_ERROR
c_func
(paren
l_string|&quot;Attempt to free invalid context handle: %d&bslash;n&quot;
comma
id|ctx_handle
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/** &n; * Context bitmap allocation.&n; *&n; * &bslash;param dev DRM device.&n; * &bslash;return (non-negative) context handle on success or a negative number on failure.&n; *&n; * Find the first zero bit in drm_device::ctx_bitmap and (re)allocates&n; * drm_device::context_sareas to accommodate the new entry while holding the&n; * drm_device::struct_sem lock.&n; */
DECL|function|ctxbitmap_next
r_int
id|DRM
c_func
(paren
id|ctxbitmap_next
)paren
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|bit
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ctx_bitmap
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|bit
op_assign
id|find_first_zero_bit
c_func
(paren
id|dev-&gt;ctx_bitmap
comma
id|DRM_MAX_CTXBITMAP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bit
OL
id|DRM_MAX_CTXBITMAP
)paren
(brace
id|set_bit
c_func
(paren
id|bit
comma
id|dev-&gt;ctx_bitmap
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;drm_ctxbitmap_next bit : %d&bslash;n&quot;
comma
id|bit
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bit
op_plus
l_int|1
)paren
OG
id|dev-&gt;max_context
)paren
(brace
id|dev-&gt;max_context
op_assign
(paren
id|bit
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;context_sareas
)paren
(brace
id|drm_map_t
op_star
op_star
id|ctx_sareas
suffix:semicolon
id|ctx_sareas
op_assign
id|DRM
c_func
(paren
id|realloc
)paren
(paren
id|dev-&gt;context_sareas
comma
(paren
id|dev-&gt;max_context
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|dev-&gt;context_sareas
)paren
comma
id|dev-&gt;max_context
op_star
r_sizeof
(paren
op_star
id|dev-&gt;context_sareas
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctx_sareas
)paren
(brace
id|clear_bit
c_func
(paren
id|bit
comma
id|dev-&gt;ctx_bitmap
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dev-&gt;context_sareas
op_assign
id|ctx_sareas
suffix:semicolon
id|dev-&gt;context_sareas
(braket
id|bit
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* max_context == 1 at this point */
id|dev-&gt;context_sareas
op_assign
id|DRM
c_func
(paren
id|alloc
)paren
(paren
id|dev-&gt;max_context
op_star
r_sizeof
(paren
op_star
id|dev-&gt;context_sareas
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;context_sareas
)paren
(brace
id|clear_bit
c_func
(paren
id|bit
comma
id|dev-&gt;ctx_bitmap
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dev-&gt;context_sareas
(braket
id|bit
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
id|bit
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * Context bitmap initialization.&n; *&n; * &bslash;param dev DRM device.&n; *&n; * Allocates and initialize drm_device::ctx_bitmap and drm_device::context_sareas, while holding&n; * the drm_device::struct_sem lock.&n; */
DECL|function|ctxbitmap_init
r_int
id|DRM
c_func
(paren
id|ctxbitmap_init
)paren
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|temp
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|dev-&gt;ctx_bitmap
op_assign
(paren
r_int
r_int
op_star
)paren
id|DRM
c_func
(paren
id|alloc
)paren
(paren
id|PAGE_SIZE
comma
id|DRM_MEM_CTXBITMAP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;ctx_bitmap
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|dev-&gt;ctx_bitmap
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|dev-&gt;context_sareas
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;max_context
op_assign
op_minus
l_int|1
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
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
id|DRM_RESERVED_CONTEXTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|temp
op_assign
id|DRM
c_func
(paren
id|ctxbitmap_next
)paren
(paren
id|dev
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;drm_ctxbitmap_init : %d&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Context bitmap cleanup.&n; *&n; * &bslash;param dev DRM device.&n; *&n; * Frees drm_device::ctx_bitmap and drm_device::context_sareas, while holding&n; * the drm_device::struct_sem lock.&n; */
DECL|function|ctxbitmap_cleanup
r_void
id|DRM
c_func
(paren
id|ctxbitmap_cleanup
)paren
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;context_sareas
)paren
(brace
id|DRM
c_func
(paren
id|free
)paren
(paren
id|dev-&gt;context_sareas
comma
r_sizeof
(paren
op_star
id|dev-&gt;context_sareas
)paren
op_star
id|dev-&gt;max_context
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
)brace
id|DRM
c_func
(paren
id|free
)paren
(paren
(paren
r_void
op_star
)paren
id|dev-&gt;ctx_bitmap
comma
id|PAGE_SIZE
comma
id|DRM_MEM_CTXBITMAP
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
)brace
multiline_comment|/*@}*/
multiline_comment|/******************************************************************/
multiline_comment|/** &bslash;name Per Context SAREA Support */
multiline_comment|/*@{*/
multiline_comment|/**&n; * Get per-context SAREA.&n; * &n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument pointing to a drm_ctx_priv_map structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Gets the map from drm_device::context_sareas with the handle specified and&n; * returns its handle.&n; */
DECL|function|getsareactx
r_int
id|DRM
c_func
(paren
id|getsareactx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_ctx_priv_map_t
id|request
suffix:semicolon
id|drm_map_t
op_star
id|map
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|request
comma
(paren
id|drm_ctx_priv_map_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;max_context
OL
l_int|0
op_logical_or
id|request.ctx_id
op_ge
(paren
r_int
)paren
id|dev-&gt;max_context
)paren
(brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|map
op_assign
id|dev-&gt;context_sareas
(braket
id|request.ctx_id
)braket
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|request.handle
op_assign
id|map-&gt;handle
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_ctx_priv_map_t
op_star
)paren
id|arg
comma
op_amp
id|request
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Set per-context SAREA.&n; * &n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument pointing to a drm_ctx_priv_map structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Searches the mapping specified in &bslash;p arg and update the entry in&n; * drm_device::context_sareas with it.&n; */
DECL|function|setsareactx
r_int
id|DRM
c_func
(paren
id|setsareactx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_ctx_priv_map_t
id|request
suffix:semicolon
id|drm_map_t
op_star
id|map
op_assign
l_int|NULL
suffix:semicolon
id|drm_map_list_t
op_star
id|r_list
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|request
comma
(paren
id|drm_ctx_priv_map_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|dev-&gt;maplist-&gt;head
)paren
(brace
id|r_list
op_assign
id|list_entry
c_func
(paren
id|list
comma
id|drm_map_list_t
comma
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r_list-&gt;map
op_logical_and
id|r_list-&gt;map-&gt;handle
op_eq
id|request.handle
)paren
(brace
r_goto
id|found
suffix:semicolon
)brace
)brace
id|bad
suffix:colon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
id|found
suffix:colon
id|map
op_assign
id|r_list-&gt;map
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;max_context
OL
l_int|0
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
id|request.ctx_id
op_ge
(paren
r_int
)paren
id|dev-&gt;max_context
)paren
r_goto
id|bad
suffix:semicolon
id|dev-&gt;context_sareas
(braket
id|request.ctx_id
)braket
op_assign
id|map
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*@}*/
multiline_comment|/******************************************************************/
multiline_comment|/** &bslash;name The actual DRM context handling routines */
multiline_comment|/*@{*/
multiline_comment|/**&n; * Switch context.&n; *&n; * &bslash;param dev DRM device.&n; * &bslash;param old old context handle.&n; * &bslash;param new new context handle.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Attempt to set drm_device::context_flag.&n; */
DECL|function|context_switch
r_int
id|DRM
c_func
(paren
id|context_switch
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|old
comma
r_int
r_new
)paren
(brace
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;context_flag
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Reentering -- FIXME&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;Context switch from %d to %d&bslash;n&quot;
comma
id|old
comma
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
id|dev-&gt;last_context
)paren
(brace
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;context_flag
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Complete context switch.&n; *&n; * &bslash;param dev DRM device.&n; * &bslash;param new new context handle.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Updates drm_device::last_context and drm_device::last_switch. Verifies the&n; * hardware lock is held, clears the drm_device::context_flag and wakes up&n; * drm_device::context_wait.&n; */
DECL|function|context_switch_complete
r_int
id|DRM
c_func
(paren
id|context_switch_complete
)paren
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
r_new
)paren
(brace
id|dev-&gt;last_context
op_assign
r_new
suffix:semicolon
multiline_comment|/* PRE/POST: This is the _only_ writer. */
id|dev-&gt;last_switch
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_DRM_LOCK_IS_HELD
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Lock isn&squot;t held after context switch&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* If a context switch is ever initiated&n;                                   when the kernel holds the lock, release&n;                                   that lock here. */
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;context_flag
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|dev-&gt;context_wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Reserve contexts.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument pointing to a drm_ctx_res structure.&n; * &bslash;return zero on success or a negative number on failure.&n; */
DECL|function|resctx
r_int
id|DRM
c_func
(paren
id|resctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_ctx_res_t
id|res
suffix:semicolon
id|drm_ctx_t
id|ctx
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|res
comma
(paren
id|drm_ctx_res_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|res
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|res.count
op_ge
id|DRM_RESERVED_CONTEXTS
)paren
(brace
id|memset
c_func
(paren
op_amp
id|ctx
comma
l_int|0
comma
r_sizeof
(paren
id|ctx
)paren
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
id|DRM_RESERVED_CONTEXTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ctx.handle
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|res.contexts
(braket
id|i
)braket
comma
op_amp
id|i
comma
r_sizeof
(paren
id|i
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
id|res.count
op_assign
id|DRM_RESERVED_CONTEXTS
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_ctx_res_t
op_star
)paren
id|arg
comma
op_amp
id|res
comma
r_sizeof
(paren
id|res
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Add context.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument pointing to a drm_ctx structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Get a new handle for the context and copy to userspace.&n; */
DECL|function|addctx
r_int
id|DRM
c_func
(paren
id|addctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_ctx_t
id|ctx
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
(paren
id|drm_ctx_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ctx.handle
op_assign
id|DRM
c_func
(paren
id|ctxbitmap_next
)paren
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx.handle
op_eq
id|DRM_KERNEL_CONTEXT
)paren
(brace
multiline_comment|/* Skip kernel&squot;s context and get a new one. */
id|ctx.handle
op_assign
id|DRM
c_func
(paren
id|ctxbitmap_next
)paren
(paren
id|dev
)paren
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|ctx.handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx.handle
op_eq
op_minus
l_int|1
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;Not enough free contexts.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Should this return -EBUSY instead? */
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
macro_line|#ifdef DRIVER_CTX_CTOR
r_if
c_cond
(paren
id|ctx.handle
op_ne
id|DRM_KERNEL_CONTEXT
)paren
id|DRIVER_CTX_CTOR
c_func
(paren
id|ctx.handle
)paren
suffix:semicolon
multiline_comment|/* XXX: also pass dev ? */
macro_line|#endif
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_ctx_t
op_star
)paren
id|arg
comma
op_amp
id|ctx
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|modctx
r_int
id|DRM
c_func
(paren
id|modctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
multiline_comment|/* This does nothing */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Get context.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument pointing to a drm_ctx structure.&n; * &bslash;return zero on success or a negative number on failure.&n; */
DECL|function|getctx
r_int
id|DRM
c_func
(paren
id|getctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_ctx_t
id|ctx
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
(paren
id|drm_ctx_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* This is 0, because we don&squot;t handle any context flags */
id|ctx.flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_ctx_t
op_star
)paren
id|arg
comma
op_amp
id|ctx
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Switch context.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument pointing to a drm_ctx structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Calls context_switch().&n; */
DECL|function|switchctx
r_int
id|DRM
c_func
(paren
id|switchctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_ctx_t
id|ctx
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
(paren
id|drm_ctx_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|ctx.handle
)paren
suffix:semicolon
r_return
id|DRM
c_func
(paren
id|context_switch
)paren
(paren
id|dev
comma
id|dev-&gt;last_context
comma
id|ctx.handle
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * New context.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument pointing to a drm_ctx structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * Calls context_switch_complete().&n; */
DECL|function|newctx
r_int
id|DRM
c_func
(paren
id|newctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_ctx_t
id|ctx
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
(paren
id|drm_ctx_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|ctx.handle
)paren
suffix:semicolon
id|DRM
c_func
(paren
id|context_switch_complete
)paren
(paren
id|dev
comma
id|ctx.handle
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Remove context.&n; *&n; * &bslash;param inode device inode.&n; * &bslash;param filp file pointer.&n; * &bslash;param cmd command.&n; * &bslash;param arg user argument pointing to a drm_ctx structure.&n; * &bslash;return zero on success or a negative number on failure.&n; *&n; * If not the special kernel context, calls ctxbitmap_free() to free the specified context.&n; */
DECL|function|rmctx
r_int
id|DRM
c_func
(paren
id|rmctx
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_ctx_t
id|ctx
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ctx
comma
(paren
id|drm_ctx_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ctx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|ctx.handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx.handle
op_eq
id|DRM_KERNEL_CONTEXT
op_plus
l_int|1
)paren
(brace
id|priv-&gt;remove_auth_on_close
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctx.handle
op_ne
id|DRM_KERNEL_CONTEXT
)paren
(brace
macro_line|#ifdef DRIVER_CTX_DTOR
id|DRIVER_CTX_DTOR
c_func
(paren
id|ctx.handle
)paren
suffix:semicolon
multiline_comment|/* XXX: also pass dev ? */
macro_line|#endif
id|DRM
c_func
(paren
id|ctxbitmap_free
)paren
(paren
id|dev
comma
id|ctx.handle
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*@}*/
eof
