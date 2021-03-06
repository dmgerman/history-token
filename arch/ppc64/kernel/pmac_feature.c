multiline_comment|/*&n; *  arch/ppc/platforms/pmac_feature.c&n; *&n; *  Copyright (C) 1996-2001 Paul Mackerras (paulus@cs.anu.edu.au)&n; *                          Ben. Herrenschmidt (benh@kernel.crashing.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; *  TODO:&n; *&n; *   - Replace mdelay with some schedule loop if possible&n; *   - Shorten some obfuscated delays on some routines (like modem&n; *     power)&n; *   - Refcount some clocks (see darwin)&n; *   - Split split split...&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/keylargo.h&gt;
macro_line|#include &lt;asm/uninorth.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/dbdma.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/pmac_low_i2c.h&gt;
DECL|macro|DEBUG_FEATURE
macro_line|#undef DEBUG_FEATURE
macro_line|#ifdef DEBUG_FEATURE
DECL|macro|DBG
mdefine_line|#define DBG(fmt...) printk(KERN_DEBUG fmt)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fmt...)
macro_line|#endif
multiline_comment|/*&n; * We use a single global lock to protect accesses. Each driver has&n; * to take care of its own locking&n; */
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|feature_lock
id|__pmacdata
)paren
suffix:semicolon
DECL|macro|LOCK
mdefine_line|#define LOCK(flags)&t;spin_lock_irqsave(&amp;feature_lock, flags);
DECL|macro|UNLOCK
mdefine_line|#define UNLOCK(flags)&t;spin_unlock_irqrestore(&amp;feature_lock, flags);
multiline_comment|/*&n; * Instance of some macio stuffs&n; */
DECL|variable|__pmacdata
r_struct
id|macio_chip
id|macio_chips
(braket
id|MAX_MACIO_CHIPS
)braket
id|__pmacdata
suffix:semicolon
r_struct
id|macio_chip
op_star
id|__pmac
DECL|function|macio_find
id|macio_find
c_func
(paren
r_struct
id|device_node
op_star
id|child
comma
r_int
id|type
)paren
(brace
r_while
c_loop
(paren
id|child
)paren
(brace
r_int
id|i
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
id|MAX_MACIO_CHIPS
op_logical_and
id|macio_chips
(braket
id|i
)braket
dot
id|of_node
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|child
op_eq
id|macio_chips
(braket
id|i
)braket
dot
id|of_node
op_logical_and
(paren
op_logical_neg
id|type
op_logical_or
id|macio_chips
(braket
id|i
)braket
dot
id|type
op_eq
id|type
)paren
)paren
r_return
op_amp
id|macio_chips
(braket
id|i
)braket
suffix:semicolon
id|child
op_assign
id|child-&gt;parent
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|__pmacdata
r_static
r_const
r_char
op_star
id|macio_names
(braket
)braket
id|__pmacdata
op_assign
(brace
l_string|&quot;Unknown&quot;
comma
l_string|&quot;Grand Central&quot;
comma
l_string|&quot;OHare&quot;
comma
l_string|&quot;OHareII&quot;
comma
l_string|&quot;Heathrow&quot;
comma
l_string|&quot;Gatwick&quot;
comma
l_string|&quot;Paddington&quot;
comma
l_string|&quot;Keylargo&quot;
comma
l_string|&quot;Pangea&quot;
comma
l_string|&quot;Intrepid&quot;
comma
l_string|&quot;K2&quot;
)brace
suffix:semicolon
multiline_comment|/*&n; * Uninorth reg. access. Note that Uni-N regs are big endian&n; */
DECL|macro|UN_REG
mdefine_line|#define UN_REG(r)&t;(uninorth_base + ((r) &gt;&gt; 2))
DECL|macro|UN_IN
mdefine_line|#define UN_IN(r)&t;(in_be32(UN_REG(r)))
DECL|macro|UN_OUT
mdefine_line|#define UN_OUT(r,v)&t;(out_be32(UN_REG(r), (v)))
DECL|macro|UN_BIS
mdefine_line|#define UN_BIS(r,v)&t;(UN_OUT((r), UN_IN(r) | (v)))
DECL|macro|UN_BIC
mdefine_line|#define UN_BIC(r,v)&t;(UN_OUT((r), UN_IN(r) &amp; ~(v)))
DECL|variable|__pmacdata
r_static
r_struct
id|device_node
op_star
id|uninorth_node
id|__pmacdata
suffix:semicolon
DECL|variable|__pmacdata
r_static
id|u32
op_star
id|uninorth_base
id|__pmacdata
suffix:semicolon
DECL|variable|__pmacdata
r_static
id|u32
id|uninorth_rev
id|__pmacdata
suffix:semicolon
DECL|variable|u3_ht
r_static
r_void
op_star
id|u3_ht
suffix:semicolon
r_extern
r_struct
id|device_node
op_star
id|k2_skiplist
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n; * For each motherboard family, we have a table of functions pointers&n; * that handle the various features.&n; */
DECL|typedef|feature_call
r_typedef
r_int
(paren
op_star
id|feature_call
)paren
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|param
comma
r_int
id|value
)paren
suffix:semicolon
DECL|struct|feature_table_entry
r_struct
id|feature_table_entry
(brace
DECL|member|selector
r_int
r_int
id|selector
suffix:semicolon
DECL|member|function
id|feature_call
id|function
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pmac_mb_def
r_struct
id|pmac_mb_def
(brace
DECL|member|model_string
r_const
r_char
op_star
id|model_string
suffix:semicolon
DECL|member|model_name
r_const
r_char
op_star
id|model_name
suffix:semicolon
DECL|member|model_id
r_int
id|model_id
suffix:semicolon
DECL|member|features
r_struct
id|feature_table_entry
op_star
id|features
suffix:semicolon
DECL|member|board_flags
r_int
r_int
id|board_flags
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__pmacdata
r_static
r_struct
id|pmac_mb_def
id|pmac_mb
id|__pmacdata
suffix:semicolon
multiline_comment|/*&n; * Here are the chip specific feature functions&n; */
DECL|function|g5_read_gpio
r_static
r_int
id|__pmac
id|g5_read_gpio
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|param
comma
r_int
id|value
)paren
(brace
r_struct
id|macio_chip
op_star
id|macio
op_assign
op_amp
id|macio_chips
(braket
l_int|0
)braket
suffix:semicolon
r_return
id|MACIO_IN8
c_func
(paren
id|param
)paren
suffix:semicolon
)brace
DECL|function|g5_write_gpio
r_static
r_int
id|__pmac
id|g5_write_gpio
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|param
comma
r_int
id|value
)paren
(brace
r_struct
id|macio_chip
op_star
id|macio
op_assign
op_amp
id|macio_chips
(braket
l_int|0
)braket
suffix:semicolon
id|MACIO_OUT8
c_func
(paren
id|param
comma
(paren
id|u8
)paren
(paren
id|value
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|g5_gmac_enable
r_static
r_int
id|__pmac
id|g5_gmac_enable
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|param
comma
r_int
id|value
)paren
(brace
r_struct
id|macio_chip
op_star
id|macio
op_assign
op_amp
id|macio_chips
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|LOCK
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
id|MACIO_BIS
c_func
(paren
id|KEYLARGO_FCR1
comma
id|K2_FCR1_GMAC_CLK_ENABLE
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|k2_skiplist
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|k2_skiplist
(braket
l_int|0
)braket
op_assign
id|node
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|MACIO_BIC
c_func
(paren
id|KEYLARGO_FCR1
comma
id|K2_FCR1_GMAC_CLK_ENABLE
)paren
suffix:semicolon
)brace
id|UNLOCK
c_func
(paren
id|flags
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|g5_fw_enable
r_static
r_int
id|__pmac
id|g5_fw_enable
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|param
comma
r_int
id|value
)paren
(brace
r_struct
id|macio_chip
op_star
id|macio
op_assign
op_amp
id|macio_chips
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|LOCK
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
id|MACIO_BIS
c_func
(paren
id|KEYLARGO_FCR1
comma
id|K2_FCR1_FW_CLK_ENABLE
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|k2_skiplist
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|k2_skiplist
(braket
l_int|1
)braket
op_assign
id|node
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|MACIO_BIC
c_func
(paren
id|KEYLARGO_FCR1
comma
id|K2_FCR1_FW_CLK_ENABLE
)paren
suffix:semicolon
)brace
id|UNLOCK
c_func
(paren
id|flags
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|g5_mpic_enable
r_static
r_int
id|__pmac
id|g5_mpic_enable
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|param
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;parent
op_eq
l_int|NULL
op_logical_or
id|strcmp
c_func
(paren
id|node-&gt;parent-&gt;name
comma
l_string|&quot;u3&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|LOCK
c_func
(paren
id|flags
)paren
suffix:semicolon
id|UN_BIS
c_func
(paren
id|U3_TOGGLE_REG
comma
id|U3_MPIC_RESET
op_or
id|U3_MPIC_OUTPUT_ENABLE
)paren
suffix:semicolon
id|UNLOCK
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|g5_eth_phy_reset
r_static
r_int
id|__pmac
id|g5_eth_phy_reset
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|param
comma
r_int
id|value
)paren
(brace
r_struct
id|macio_chip
op_star
id|macio
op_assign
op_amp
id|macio_chips
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|device_node
op_star
id|phy
suffix:semicolon
r_int
id|need_reset
suffix:semicolon
multiline_comment|/*&n;&t; * We must not reset the combo PHYs, only the BCM5221 found in&n;&t; * the iMac G5.&n;&t; */
id|phy
op_assign
id|of_get_next_child
c_func
(paren
id|node
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|phy
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|need_reset
op_assign
id|device_is_compatible
c_func
(paren
id|phy
comma
l_string|&quot;B5221&quot;
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|phy
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_reset
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* PHY reset is GPIO 29, not in device-tree unfortunately */
id|MACIO_OUT8
c_func
(paren
id|K2_GPIO_EXTINT_0
op_plus
l_int|29
comma
id|KEYLARGO_GPIO_OUTPUT_ENABLE
op_or
id|KEYLARGO_GPIO_OUTOUT_DATA
)paren
suffix:semicolon
multiline_comment|/* Thankfully, this is now always called at a time when we can&n;&t; * schedule by sungem.&n;&t; */
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|MACIO_OUT8
c_func
(paren
id|K2_GPIO_EXTINT_0
op_plus
l_int|29
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|function|g5_reset_cpu
r_static
r_int
id|__pmac
id|g5_reset_cpu
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|param
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|reset_io
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|macio_chip
op_star
id|macio
suffix:semicolon
r_struct
id|device_node
op_star
id|np
suffix:semicolon
id|macio
op_assign
op_amp
id|macio_chips
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|macio-&gt;type
op_ne
id|macio_keylargo2
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|np
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/cpus&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_for
c_loop
(paren
id|np
op_assign
id|np-&gt;child
suffix:semicolon
id|np
op_ne
l_int|NULL
suffix:semicolon
id|np
op_assign
id|np-&gt;sibling
)paren
(brace
id|u32
op_star
id|num
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|u32
op_star
id|rst
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;soft-reset&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num
op_eq
l_int|NULL
op_logical_or
id|rst
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|param
op_eq
op_star
id|num
)paren
(brace
id|reset_io
op_assign
op_star
id|rst
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
op_logical_or
id|reset_io
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|LOCK
c_func
(paren
id|flags
)paren
suffix:semicolon
id|MACIO_OUT8
c_func
(paren
id|reset_io
comma
id|KEYLARGO_GPIO_OUTPUT_ENABLE
)paren
suffix:semicolon
(paren
r_void
)paren
id|MACIO_IN8
c_func
(paren
id|reset_io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|MACIO_OUT8
c_func
(paren
id|reset_io
comma
l_int|0
)paren
suffix:semicolon
(paren
r_void
)paren
id|MACIO_IN8
c_func
(paren
id|reset_io
)paren
suffix:semicolon
id|UNLOCK
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/*&n; * This can be called from pmac_smp so isn&squot;t static&n; *&n; * This takes the second CPU off the bus on dual CPU machines&n; * running UP&n; */
DECL|function|g5_phy_disable_cpu1
r_void
id|__pmac
id|g5_phy_disable_cpu1
c_func
(paren
r_void
)paren
(brace
id|UN_OUT
c_func
(paren
id|U3_API_PHY_CONFIG_1
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|generic_get_mb_info
r_static
r_int
id|__pmac
id|generic_get_mb_info
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|param
comma
r_int
id|value
)paren
(brace
r_switch
c_cond
(paren
id|param
)paren
(brace
r_case
id|PMAC_MB_INFO_MODEL
suffix:colon
r_return
id|pmac_mb.model_id
suffix:semicolon
r_case
id|PMAC_MB_INFO_FLAGS
suffix:colon
r_return
id|pmac_mb.board_flags
suffix:semicolon
r_case
id|PMAC_MB_INFO_NAME
suffix:colon
multiline_comment|/* hack hack hack... but should work */
op_star
(paren
(paren
r_const
r_char
op_star
op_star
)paren
id|value
)paren
op_assign
id|pmac_mb.model_name
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * Table definitions&n; */
multiline_comment|/* Used on any machine&n; */
DECL|variable|__pmacdata
r_static
r_struct
id|feature_table_entry
id|any_features
(braket
)braket
id|__pmacdata
op_assign
(brace
(brace
id|PMAC_FTR_GET_MB_INFO
comma
id|generic_get_mb_info
)brace
comma
(brace
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/* G5 features&n; */
DECL|variable|__pmacdata
r_static
r_struct
id|feature_table_entry
id|g5_features
(braket
)braket
id|__pmacdata
op_assign
(brace
(brace
id|PMAC_FTR_GMAC_ENABLE
comma
id|g5_gmac_enable
)brace
comma
(brace
id|PMAC_FTR_1394_ENABLE
comma
id|g5_fw_enable
)brace
comma
(brace
id|PMAC_FTR_ENABLE_MPIC
comma
id|g5_mpic_enable
)brace
comma
(brace
id|PMAC_FTR_READ_GPIO
comma
id|g5_read_gpio
)brace
comma
(brace
id|PMAC_FTR_WRITE_GPIO
comma
id|g5_write_gpio
)brace
comma
(brace
id|PMAC_FTR_GMAC_PHY_RESET
comma
id|g5_eth_phy_reset
)brace
comma
macro_line|#ifdef CONFIG_SMP
(brace
id|PMAC_FTR_RESET_CPU
comma
id|g5_reset_cpu
)brace
comma
macro_line|#endif /* CONFIG_SMP */
(brace
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|variable|__pmacdata
r_static
r_struct
id|pmac_mb_def
id|pmac_mb_defs
(braket
)braket
id|__pmacdata
op_assign
(brace
(brace
l_string|&quot;PowerMac7,2&quot;
comma
l_string|&quot;PowerMac G5&quot;
comma
id|PMAC_TYPE_POWERMAC_G5
comma
id|g5_features
comma
l_int|0
comma
)brace
comma
(brace
l_string|&quot;PowerMac7,3&quot;
comma
l_string|&quot;PowerMac G5&quot;
comma
id|PMAC_TYPE_POWERMAC_G5
comma
id|g5_features
comma
l_int|0
comma
)brace
comma
(brace
l_string|&quot;PowerMac8,1&quot;
comma
l_string|&quot;iMac G5&quot;
comma
id|PMAC_TYPE_IMAC_G5
comma
id|g5_features
comma
l_int|0
comma
)brace
comma
(brace
l_string|&quot;PowerMac9,1&quot;
comma
l_string|&quot;PowerMac G5&quot;
comma
id|PMAC_TYPE_POWERMAC_G5_U3L
comma
id|g5_features
comma
l_int|0
comma
)brace
comma
(brace
l_string|&quot;RackMac3,1&quot;
comma
l_string|&quot;XServe G5&quot;
comma
id|PMAC_TYPE_XSERVE_G5
comma
id|g5_features
comma
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The toplevel feature_call callback&n; */
DECL|function|pmac_do_feature_call
r_int
id|__pmac
id|pmac_do_feature_call
c_func
(paren
r_int
r_int
id|selector
comma
dot
dot
dot
)paren
(brace
r_struct
id|device_node
op_star
id|node
suffix:semicolon
r_int
id|param
comma
id|value
suffix:semicolon
r_int
id|i
suffix:semicolon
id|feature_call
id|func
op_assign
l_int|NULL
suffix:semicolon
id|va_list
id|args
suffix:semicolon
r_if
c_cond
(paren
id|pmac_mb.features
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|pmac_mb.features
(braket
id|i
)braket
dot
id|function
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|pmac_mb.features
(braket
id|i
)braket
dot
id|selector
op_eq
id|selector
)paren
(brace
id|func
op_assign
id|pmac_mb.features
(braket
id|i
)braket
dot
id|function
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|func
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|any_features
(braket
id|i
)braket
dot
id|function
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|any_features
(braket
id|i
)braket
dot
id|selector
op_eq
id|selector
)paren
(brace
id|func
op_assign
id|any_features
(braket
id|i
)braket
dot
id|function
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|func
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|selector
)paren
suffix:semicolon
id|node
op_assign
(paren
r_struct
id|device_node
op_star
)paren
id|va_arg
c_func
(paren
id|args
comma
r_void
op_star
)paren
suffix:semicolon
id|param
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
id|value
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|func
c_func
(paren
id|node
comma
id|param
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|probe_motherboard
r_static
r_int
id|__init
id|probe_motherboard
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|macio_chip
op_star
id|macio
op_assign
op_amp
id|macio_chips
(braket
l_int|0
)braket
suffix:semicolon
r_const
r_char
op_star
id|model
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|device_node
op_star
id|dt
suffix:semicolon
multiline_comment|/* Lookup known motherboard type in device-tree. First try an&n;&t; * exact match on the &quot;model&quot; property, then try a &quot;compatible&quot;&n;&t; * match is none is found.&n;&t; */
id|dt
op_assign
id|find_devices
c_func
(paren
l_string|&quot;device-tree&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dt
op_ne
l_int|NULL
)paren
id|model
op_assign
(paren
r_const
r_char
op_star
)paren
id|get_property
c_func
(paren
id|dt
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|model
op_logical_and
id|i
OL
(paren
r_sizeof
(paren
id|pmac_mb_defs
)paren
op_div
r_sizeof
(paren
r_struct
id|pmac_mb_def
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|model
comma
id|pmac_mb_defs
(braket
id|i
)braket
dot
id|model_string
)paren
op_eq
l_int|0
)paren
(brace
id|pmac_mb
op_assign
id|pmac_mb_defs
(braket
id|i
)braket
suffix:semicolon
r_goto
id|found
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_sizeof
(paren
id|pmac_mb_defs
)paren
op_div
r_sizeof
(paren
r_struct
id|pmac_mb_def
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|machine_is_compatible
c_func
(paren
id|pmac_mb_defs
(braket
id|i
)braket
dot
id|model_string
)paren
)paren
(brace
id|pmac_mb
op_assign
id|pmac_mb_defs
(braket
id|i
)braket
suffix:semicolon
r_goto
id|found
suffix:semicolon
)brace
)brace
multiline_comment|/* Fallback to selection depending on mac-io chip type */
r_switch
c_cond
(paren
id|macio-&gt;type
)paren
(brace
r_case
id|macio_keylargo2
suffix:colon
id|pmac_mb.model_id
op_assign
id|PMAC_TYPE_UNKNOWN_K2
suffix:semicolon
id|pmac_mb.model_name
op_assign
l_string|&quot;Unknown K2-based&quot;
suffix:semicolon
id|pmac_mb.features
op_assign
id|g5_features
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|found
suffix:colon
multiline_comment|/* Check for &quot;mobile&quot; machine */
r_if
c_cond
(paren
id|model
op_logical_and
(paren
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;PowerBook&quot;
comma
l_int|9
)paren
op_eq
l_int|0
op_logical_or
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;iBook&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
)paren
id|pmac_mb.board_flags
op_or_assign
id|PMAC_MB_MOBILE
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PowerMac motherboard: %s&bslash;n&quot;
comma
id|pmac_mb.model_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Initialize the Core99 UniNorth host bridge and memory controller&n; */
DECL|function|probe_uninorth
r_static
r_void
id|__init
id|probe_uninorth
c_func
(paren
r_void
)paren
(brace
id|uninorth_node
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;u3&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uninorth_node
op_logical_and
id|uninorth_node-&gt;n_addrs
OG
l_int|0
)paren
(brace
multiline_comment|/* Small hack until I figure out if parsing in prom.c is correct. I should&n;&t;&t; * get rid of those pre-parsed junk anyway&n;&t;&t; */
r_int
r_int
id|address
op_assign
id|uninorth_node-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
suffix:semicolon
id|uninorth_base
op_assign
id|ioremap
c_func
(paren
id|address
comma
l_int|0x40000
)paren
suffix:semicolon
id|uninorth_rev
op_assign
id|in_be32
c_func
(paren
id|UN_REG
c_func
(paren
id|UNI_N_VERSION
)paren
)paren
suffix:semicolon
id|u3_ht
op_assign
id|ioremap
c_func
(paren
id|address
op_plus
id|U3_HT_CONFIG_BASE
comma
l_int|0x1000
)paren
suffix:semicolon
)brace
r_else
id|uninorth_node
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uninorth_node
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Found U3 memory controller &amp; host bridge, revision: %d&bslash;n&quot;
comma
id|uninorth_rev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Mapped at 0x%08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|uninorth_base
)paren
suffix:semicolon
)brace
DECL|function|probe_one_macio
r_static
r_void
id|__init
id|probe_one_macio
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|compat
comma
r_int
id|type
)paren
(brace
r_struct
id|device_node
op_star
id|node
suffix:semicolon
r_int
id|i
suffix:semicolon
r_volatile
id|u32
op_star
id|base
suffix:semicolon
id|u32
op_star
id|revp
suffix:semicolon
id|node
op_assign
id|find_devices
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
op_logical_or
op_logical_neg
id|node-&gt;n_addrs
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|compat
)paren
r_do
(brace
r_if
c_cond
(paren
id|device_is_compatible
c_func
(paren
id|node
comma
id|compat
)paren
)paren
r_break
suffix:semicolon
id|node
op_assign
id|node-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
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
id|MAX_MACIO_CHIPS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|macio_chips
(braket
id|i
)braket
dot
id|of_node
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|macio_chips
(braket
id|i
)braket
dot
id|of_node
op_eq
id|node
)paren
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|MAX_MACIO_CHIPS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pmac_feature: Please increase MAX_MACIO_CHIPS !&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pmac_feature: %s skipped&bslash;n&quot;
comma
id|node-&gt;full_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|base
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|ioremap
c_func
(paren
id|node-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|node-&gt;addrs
(braket
l_int|0
)braket
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pmac_feature: Can&squot;t map mac-io chip !&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
op_eq
id|macio_keylargo
)paren
(brace
id|u32
op_star
id|did
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|node
comma
l_string|&quot;device-id&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|did
op_eq
l_int|0x00000025
)paren
id|type
op_assign
id|macio_pangea
suffix:semicolon
r_if
c_cond
(paren
op_star
id|did
op_eq
l_int|0x0000003e
)paren
id|type
op_assign
id|macio_intrepid
suffix:semicolon
)brace
id|macio_chips
(braket
id|i
)braket
dot
id|of_node
op_assign
id|node
suffix:semicolon
id|macio_chips
(braket
id|i
)braket
dot
id|type
op_assign
id|type
suffix:semicolon
id|macio_chips
(braket
id|i
)braket
dot
id|base
op_assign
id|base
suffix:semicolon
id|macio_chips
(braket
id|i
)braket
dot
id|flags
op_assign
id|MACIO_FLAG_SCCB_ON
op_or
id|MACIO_FLAG_SCCB_ON
suffix:semicolon
id|macio_chips
(braket
id|i
)braket
dot
id|name
op_assign
id|macio_names
(braket
id|type
)braket
suffix:semicolon
id|revp
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|node
comma
l_string|&quot;revision-id&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revp
)paren
id|macio_chips
(braket
id|i
)braket
dot
id|rev
op_assign
op_star
id|revp
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Found a %s mac-io controller, rev: %d, mapped at 0x%p&bslash;n&quot;
comma
id|macio_names
(braket
id|type
)braket
comma
id|macio_chips
(braket
id|i
)braket
dot
id|rev
comma
id|macio_chips
(braket
id|i
)braket
dot
id|base
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|probe_macios
id|probe_macios
c_func
(paren
r_void
)paren
(brace
id|probe_one_macio
c_func
(paren
l_string|&quot;mac-io&quot;
comma
l_string|&quot;K2-Keylargo&quot;
comma
id|macio_keylargo2
)paren
suffix:semicolon
id|macio_chips
(braket
l_int|0
)braket
dot
id|lbus.index
op_assign
l_int|0
suffix:semicolon
id|macio_chips
(braket
l_int|1
)braket
dot
id|lbus.index
op_assign
l_int|1
suffix:semicolon
r_return
(paren
id|macio_chips
(braket
l_int|0
)braket
dot
id|of_node
op_eq
l_int|NULL
)paren
ques
c_cond
op_minus
id|ENODEV
suffix:colon
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|set_initial_features
id|set_initial_features
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_if
c_cond
(paren
id|macio_chips
(braket
l_int|0
)braket
dot
id|type
op_eq
id|macio_keylargo2
)paren
(brace
macro_line|#ifndef CONFIG_SMP
multiline_comment|/* On SMP machines running UP, we have the second CPU eating&n;&t;&t; * bus cycles. We need to take it off the bus. This is done&n;&t;&t; * from pmac_smp for SMP kernels running on one CPU&n;&t;&t; */
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
l_int|NULL
comma
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_ne
l_int|NULL
)paren
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
id|np
comma
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_ne
l_int|NULL
)paren
(brace
id|g5_phy_disable_cpu1
c_func
(paren
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/* Enable GMAC for now for PCI probing. It will be disabled&n;&t;&t; * later on after PCI probe&n;&t;&t; */
id|np
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;ethernet&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|np
)paren
(brace
r_if
c_cond
(paren
id|device_is_compatible
c_func
(paren
id|np
comma
l_string|&quot;K2-GMAC&quot;
)paren
)paren
id|g5_gmac_enable
c_func
(paren
id|np
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|np
op_assign
id|of_find_node_by_name
c_func
(paren
id|np
comma
l_string|&quot;ethernet&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable FW before PCI probe. Will be disabled later on&n;&t;&t; * Note: We should have a batter way to check that we are&n;&t;&t; * dealing with uninorth internal cell and not a PCI cell&n;&t;&t; * on the external PCI. The code below works though.&n;&t;&t; */
id|np
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;firewire&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|np
)paren
(brace
r_if
c_cond
(paren
id|device_is_compatible
c_func
(paren
id|np
comma
l_string|&quot;pci106b,5811&quot;
)paren
)paren
(brace
id|macio_chips
(braket
l_int|0
)braket
dot
id|flags
op_or_assign
id|MACIO_FLAG_FW_SUPPORTED
suffix:semicolon
id|g5_fw_enable
c_func
(paren
id|np
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
id|np
op_assign
id|of_find_node_by_name
c_func
(paren
id|np
comma
l_string|&quot;firewire&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
r_void
id|__init
DECL|function|pmac_feature_init
id|pmac_feature_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Detect the UniNorth memory controller */
id|probe_uninorth
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Probe mac-io controllers */
r_if
c_cond
(paren
id|probe_macios
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;No mac-io chip found&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Setup low-level i2c stuffs */
id|pmac_init_low_i2c
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Probe machine type */
r_if
c_cond
(paren
id|probe_motherboard
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Unknown PowerMac !&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Set some initial features (turn off some chips that will&n;&t; * be later turned on)&n;&t; */
id|set_initial_features
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pmac_feature_late_init
r_int
id|__init
id|pmac_feature_late_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
r_struct
id|device_node
op_star
id|np
suffix:semicolon
multiline_comment|/* Request some resources late */
r_if
c_cond
(paren
id|uninorth_node
)paren
id|request_OF_resource
c_func
(paren
id|uninorth_node
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;hammerhead&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
)paren
id|request_OF_resource
c_func
(paren
id|np
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;interrupt-controller&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
)paren
id|request_OF_resource
c_func
(paren
id|np
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pmac_feature_late_init
id|device_initcall
c_func
(paren
id|pmac_feature_late_init
)paren
suffix:semicolon
macro_line|#if 0
r_static
r_void
id|dump_HT_speeds
c_func
(paren
r_char
op_star
id|name
comma
id|u32
id|cfg
comma
id|u32
id|frq
)paren
(brace
r_int
id|freqs
(braket
l_int|16
)braket
op_assign
(brace
l_int|200
comma
l_int|300
comma
l_int|400
comma
l_int|500
comma
l_int|600
comma
l_int|800
comma
l_int|1000
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|bits
(braket
l_int|8
)braket
op_assign
(brace
l_int|8
comma
l_int|16
comma
l_int|0
comma
l_int|32
comma
l_int|2
comma
l_int|4
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|freq
op_assign
(paren
id|frq
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
suffix:semicolon
r_if
c_cond
(paren
id|freqs
(braket
id|freq
)braket
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Unknown HT link frequency %x&bslash;n&quot;
comma
id|name
comma
id|freq
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;%s: %d MHz on main link, (%d in / %d out) bits width&bslash;n&quot;
comma
id|name
comma
id|freqs
(braket
id|freq
)braket
comma
id|bits
(braket
(paren
id|cfg
op_rshift
l_int|28
)paren
op_amp
l_int|0x7
)braket
comma
id|bits
(braket
(paren
id|cfg
op_rshift
l_int|24
)paren
op_amp
l_int|0x7
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|pmac_check_ht_link
r_void
id|__init
id|pmac_check_ht_link
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0 /* Disabled for now */
id|u32
id|ufreq
comma
id|freq
comma
id|ucfg
comma
id|cfg
suffix:semicolon
r_struct
id|device_node
op_star
id|pcix_node
suffix:semicolon
id|u8
id|px_bus
comma
id|px_devfn
suffix:semicolon
r_struct
id|pci_controller
op_star
id|px_hose
suffix:semicolon
(paren
r_void
)paren
id|in_be32
c_func
(paren
id|u3_ht
op_plus
id|U3_HT_LINK_COMMAND
)paren
suffix:semicolon
id|ucfg
op_assign
id|cfg
op_assign
id|in_be32
c_func
(paren
id|u3_ht
op_plus
id|U3_HT_LINK_CONFIG
)paren
suffix:semicolon
id|ufreq
op_assign
id|freq
op_assign
id|in_be32
c_func
(paren
id|u3_ht
op_plus
id|U3_HT_LINK_FREQ
)paren
suffix:semicolon
id|dump_HT_speeds
c_func
(paren
l_string|&quot;U3 HyperTransport&quot;
comma
id|cfg
comma
id|freq
)paren
suffix:semicolon
id|pcix_node
op_assign
id|of_find_compatible_node
c_func
(paren
l_int|NULL
comma
l_string|&quot;pci&quot;
comma
l_string|&quot;pci-x&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcix_node
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No PCI-X bridge found&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|px_hose
op_assign
id|pcix_node-&gt;phb
suffix:semicolon
id|px_bus
op_assign
id|pcix_node-&gt;busno
suffix:semicolon
id|px_devfn
op_assign
id|pcix_node-&gt;devfn
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|px_hose
comma
id|px_bus
comma
id|px_devfn
comma
l_int|0xc4
comma
op_amp
id|cfg
)paren
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|px_hose
comma
id|px_bus
comma
id|px_devfn
comma
l_int|0xcc
comma
op_amp
id|freq
)paren
suffix:semicolon
id|dump_HT_speeds
c_func
(paren
l_string|&quot;PCI-X HT Uplink&quot;
comma
id|cfg
comma
id|freq
)paren
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|px_hose
comma
id|px_bus
comma
id|px_devfn
comma
l_int|0xc8
comma
op_amp
id|cfg
)paren
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|px_hose
comma
id|px_bus
comma
id|px_devfn
comma
l_int|0xd0
comma
op_amp
id|freq
)paren
suffix:semicolon
id|dump_HT_speeds
c_func
(paren
l_string|&quot;PCI-X HT Downlink&quot;
comma
id|cfg
comma
id|freq
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
