multiline_comment|/*&n; *  Device management routines&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|function|snd_device_new
r_int
id|snd_device_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_device_type_t
id|type
comma
r_void
op_star
id|device_data
comma
id|snd_device_ops_t
op_star
id|ops
)paren
(brace
id|snd_device_t
op_star
id|dev
suffix:semicolon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
op_logical_and
id|device_data
op_ne
l_int|NULL
op_logical_and
id|ops
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|dev
op_assign
(paren
id|snd_device_t
op_star
)paren
id|snd_magic_kcalloc
c_func
(paren
id|snd_device_t
comma
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dev-&gt;card
op_assign
id|card
suffix:semicolon
id|dev-&gt;type
op_assign
id|type
suffix:semicolon
id|dev-&gt;state
op_assign
id|SNDRV_DEV_BUILD
suffix:semicolon
id|dev-&gt;device_data
op_assign
id|device_data
suffix:semicolon
id|dev-&gt;ops
op_assign
id|ops
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|dev-&gt;list
comma
op_amp
id|card-&gt;devices
)paren
suffix:semicolon
multiline_comment|/* add to the head of list */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_device_free
r_int
id|snd_device_free
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_void
op_star
id|device_data
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
id|snd_device_t
op_star
id|dev
suffix:semicolon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|device_data
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|card-&gt;devices
)paren
(brace
id|dev
op_assign
id|snd_device
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device_data
op_ne
id|device_data
)paren
r_continue
suffix:semicolon
multiline_comment|/* unlink */
id|list_del
c_func
(paren
op_amp
id|dev-&gt;list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;state
op_eq
id|SNDRV_DEV_REGISTERED
op_logical_and
id|dev-&gt;ops-&gt;dev_unregister
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;ops
op_member_access_from_pointer
id|dev_unregister
c_func
(paren
id|dev
)paren
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;device unregister failure&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|dev-&gt;ops-&gt;dev_free
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;ops
op_member_access_from_pointer
id|dev_free
c_func
(paren
id|dev
)paren
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;device free failure&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|snd_magic_kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|snd_printd
c_func
(paren
l_string|&quot;device free %p (from %p), not found&bslash;n&quot;
comma
id|device_data
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|snd_device_register
r_int
id|snd_device_register
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_void
op_star
id|device_data
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
id|snd_device_t
op_star
id|dev
suffix:semicolon
r_int
id|err
suffix:semicolon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
op_logical_and
id|device_data
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|card-&gt;devices
)paren
(brace
id|dev
op_assign
id|snd_device
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device_data
op_ne
id|device_data
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;state
op_eq
id|SNDRV_DEV_BUILD
op_logical_and
id|dev-&gt;ops-&gt;dev_register
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|dev-&gt;ops
op_member_access_from_pointer
id|dev_register
c_func
(paren
id|dev
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|dev-&gt;state
op_assign
id|SNDRV_DEV_REGISTERED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|snd_BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|snd_device_register_all
r_int
id|snd_device_register_all
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
id|snd_device_t
op_star
id|dev
suffix:semicolon
r_int
id|err
suffix:semicolon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|card-&gt;devices
)paren
(brace
id|dev
op_assign
id|snd_device
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;state
op_eq
id|SNDRV_DEV_BUILD
op_logical_and
id|dev-&gt;ops-&gt;dev_register
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|dev-&gt;ops
op_member_access_from_pointer
id|dev_register
c_func
(paren
id|dev
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|dev-&gt;state
op_assign
id|SNDRV_DEV_REGISTERED
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_device_free_all
r_int
id|snd_device_free_all
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_device_cmd_t
id|cmd
)paren
(brace
id|snd_device_t
op_star
id|dev
suffix:semicolon
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_int
id|err
comma
id|range_low
comma
id|range_high
suffix:semicolon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|range_low
op_assign
id|cmd
op_star
id|SNDRV_DEV_TYPE_RANGE_SIZE
suffix:semicolon
id|range_high
op_assign
id|range_low
op_plus
id|SNDRV_DEV_TYPE_RANGE_SIZE
op_minus
l_int|1
suffix:semicolon
id|__again
suffix:colon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|card-&gt;devices
)paren
(brace
id|dev
op_assign
id|snd_device
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;type
op_ge
id|range_low
op_logical_and
id|dev-&gt;type
op_le
id|range_high
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_device_free
c_func
(paren
id|card
comma
id|dev-&gt;device_data
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_goto
id|__again
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
