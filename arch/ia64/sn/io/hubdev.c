multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubdev.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
DECL|struct|hubdev_callout
r_struct
id|hubdev_callout
(brace
DECL|member|attach_method
r_int
(paren
op_star
id|attach_method
)paren
(paren
id|devfs_handle_t
)paren
suffix:semicolon
DECL|member|fp
r_struct
id|hubdev_callout
op_star
id|fp
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|hubdev_callout_t
r_typedef
r_struct
id|hubdev_callout
id|hubdev_callout_t
suffix:semicolon
DECL|variable|hubdev_callout_mutex
id|mutex_t
id|hubdev_callout_mutex
suffix:semicolon
DECL|variable|hubdev_callout_list
id|hubdev_callout_t
op_star
id|hubdev_callout_list
op_assign
l_int|NULL
suffix:semicolon
r_void
DECL|function|hubdev_init
id|hubdev_init
c_func
(paren
r_void
)paren
(brace
id|mutex_init
c_func
(paren
op_amp
id|hubdev_callout_mutex
)paren
suffix:semicolon
id|hubdev_callout_list
op_assign
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|hubdev_register
id|hubdev_register
c_func
(paren
r_int
(paren
op_star
id|attach_method
)paren
(paren
id|devfs_handle_t
)paren
)paren
(brace
id|hubdev_callout_t
op_star
id|callout
suffix:semicolon
id|ASSERT
c_func
(paren
id|attach_method
)paren
suffix:semicolon
id|callout
op_assign
(paren
id|hubdev_callout_t
op_star
)paren
id|snia_kmem_zalloc
c_func
(paren
r_sizeof
(paren
id|hubdev_callout_t
)paren
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|callout
)paren
suffix:semicolon
id|mutex_lock
c_func
(paren
op_amp
id|hubdev_callout_mutex
)paren
suffix:semicolon
multiline_comment|/*&n;         * Insert at the end of the list&n;         */
id|callout-&gt;fp
op_assign
id|hubdev_callout_list
suffix:semicolon
id|hubdev_callout_list
op_assign
id|callout
suffix:semicolon
id|callout-&gt;attach_method
op_assign
id|attach_method
suffix:semicolon
id|mutex_unlock
c_func
(paren
op_amp
id|hubdev_callout_mutex
)paren
suffix:semicolon
)brace
r_int
DECL|function|hubdev_unregister
id|hubdev_unregister
c_func
(paren
r_int
(paren
op_star
id|attach_method
)paren
(paren
id|devfs_handle_t
)paren
)paren
(brace
id|hubdev_callout_t
op_star
op_star
id|p
suffix:semicolon
id|ASSERT
c_func
(paren
id|attach_method
)paren
suffix:semicolon
id|mutex_lock
c_func
(paren
op_amp
id|hubdev_callout_mutex
)paren
suffix:semicolon
multiline_comment|/*&n;         * Remove registry element containing attach_method&n;         */
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|hubdev_callout_list
suffix:semicolon
op_star
id|p
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
op_amp
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|fp
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|attach_method
op_eq
id|attach_method
)paren
(brace
id|hubdev_callout_t
op_star
id|victim
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|fp
suffix:semicolon
id|kfree
c_func
(paren
id|victim
)paren
suffix:semicolon
id|mutex_unlock
c_func
(paren
op_amp
id|hubdev_callout_mutex
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|mutex_unlock
c_func
(paren
op_amp
id|hubdev_callout_mutex
)paren
suffix:semicolon
r_return
(paren
id|ENOENT
)paren
suffix:semicolon
)brace
r_int
DECL|function|hubdev_docallouts
id|hubdev_docallouts
c_func
(paren
id|devfs_handle_t
id|hub
)paren
(brace
id|hubdev_callout_t
op_star
id|p
suffix:semicolon
r_int
id|errcode
suffix:semicolon
id|mutex_lock
c_func
(paren
op_amp
id|hubdev_callout_mutex
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|hubdev_callout_list
suffix:semicolon
id|p
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
id|p-&gt;fp
)paren
(brace
id|ASSERT
c_func
(paren
id|p-&gt;attach_method
)paren
suffix:semicolon
id|errcode
op_assign
(paren
op_star
id|p-&gt;attach_method
)paren
(paren
id|hub
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errcode
op_ne
l_int|0
)paren
(brace
id|mutex_unlock
c_func
(paren
op_amp
id|hubdev_callout_mutex
)paren
suffix:semicolon
r_return
(paren
id|errcode
)paren
suffix:semicolon
)brace
)brace
id|mutex_unlock
c_func
(paren
op_amp
id|hubdev_callout_mutex
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Given a hub vertex, return the base address of the Hspec space&n; * for that hub.&n; */
macro_line|#if defined(CONFIG_IA64_SGI_SN1)
id|caddr_t
DECL|function|hubdev_prombase_get
id|hubdev_prombase_get
c_func
(paren
id|devfs_handle_t
id|hub
)paren
(brace
id|hubinfo_t
id|hinfo
op_assign
l_int|NULL
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|hub
comma
op_amp
id|hinfo
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hinfo
)paren
suffix:semicolon
r_return
(paren
(paren
id|caddr_t
)paren
id|NODE_RBOOT_BASE
c_func
(paren
id|hinfo-&gt;h_nasid
)paren
)paren
suffix:semicolon
)brace
id|cnodeid_t
DECL|function|hubdev_cnodeid_get
id|hubdev_cnodeid_get
c_func
(paren
id|devfs_handle_t
id|hub
)paren
(brace
id|hubinfo_t
id|hinfo
op_assign
l_int|NULL
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|hub
comma
op_amp
id|hinfo
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|hinfo
)paren
suffix:semicolon
r_return
id|hinfo-&gt;h_cnodeid
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_IA64_SGI_SN1 */
eof
