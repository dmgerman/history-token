multiline_comment|/* Copyright (c) 2004 Coraid, Inc.  See COPYING for GPL terms. */
multiline_comment|/*&n; * aoemain.c&n; * Module initialization routines, discover timer&n; */
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;aoe.h&quot;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Sam Hopkins &lt;sah@coraid.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;AoE block/char driver for 2.6.[0-9]+&quot;
)paren
suffix:semicolon
DECL|variable|VERSION
id|MODULE_VERSION
c_func
(paren
id|VERSION
)paren
suffix:semicolon
DECL|enumerator|TINIT
DECL|enumerator|TRUN
DECL|enumerator|TKILL
r_enum
(brace
id|TINIT
comma
id|TRUN
comma
id|TKILL
)brace
suffix:semicolon
r_static
r_void
DECL|function|discover_timer
id|discover_timer
c_func
(paren
id|ulong
id|vp
)paren
(brace
r_static
r_struct
id|timer_list
id|t
suffix:semicolon
r_static
r_volatile
id|ulong
id|die
suffix:semicolon
r_static
id|spinlock_t
id|lock
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
r_enum
(brace
id|DTIMERTICK
op_assign
id|HZ
op_star
l_int|60
)brace
suffix:semicolon
multiline_comment|/* one minute */
r_switch
c_cond
(paren
id|vp
)paren
(brace
r_case
id|TINIT
suffix:colon
id|init_timer
c_func
(paren
op_amp
id|t
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|t.data
op_assign
id|TRUN
suffix:semicolon
id|t.function
op_assign
id|discover_timer
suffix:semicolon
id|die
op_assign
l_int|0
suffix:semicolon
r_case
id|TRUN
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|die
)paren
(brace
id|t.expires
op_assign
id|jiffies
op_plus
id|DTIMERTICK
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|t
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
id|aoecmd_cfg
c_func
(paren
l_int|0xffff
comma
l_int|0xff
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|TKILL
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
id|die
op_assign
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|t
)paren
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
)brace
r_static
r_void
id|__exit
DECL|function|aoe_exit
id|aoe_exit
c_func
(paren
r_void
)paren
(brace
id|discover_timer
c_func
(paren
id|TKILL
)paren
suffix:semicolon
id|aoenet_exit
c_func
(paren
)paren
suffix:semicolon
id|aoeblk_exit
c_func
(paren
)paren
suffix:semicolon
id|aoechr_exit
c_func
(paren
)paren
suffix:semicolon
id|aoedev_exit
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|aoe_init
id|aoe_init
c_func
(paren
r_void
)paren
(brace
r_int
id|n
comma
(paren
op_star
op_star
id|p
)paren
(paren
r_void
)paren
suffix:semicolon
r_int
(paren
op_star
id|fns
(braket
)braket
)paren
(paren
r_void
)paren
op_assign
(brace
id|aoedev_init
comma
id|aoechr_init
comma
id|aoeblk_init
comma
id|aoenet_init
comma
l_int|NULL
)brace
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|fns
suffix:semicolon
op_star
id|p
op_ne
l_int|NULL
suffix:semicolon
id|p
op_increment
)paren
(brace
id|n
op_assign
(paren
op_star
id|p
)paren
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
(brace
id|aoe_exit
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;aoe: aoe_init: initialisation failure.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;aoe: aoe_init: AoE v2.6-%s initialised.&bslash;n&quot;
comma
id|VERSION
)paren
suffix:semicolon
id|discover_timer
c_func
(paren
id|TINIT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|aoe_init
id|module_init
c_func
(paren
id|aoe_init
)paren
suffix:semicolon
DECL|variable|aoe_exit
id|module_exit
c_func
(paren
id|aoe_exit
)paren
suffix:semicolon
eof
