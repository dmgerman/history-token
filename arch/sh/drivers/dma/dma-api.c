multiline_comment|/*&n; * arch/sh/drivers/dma/dma-api.c&n; *&n; * SuperH-specific DMA management API&n; *&n; * Copyright (C) 2003, 2004  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
DECL|variable|dma_spin_lock
id|DEFINE_SPINLOCK
c_func
(paren
id|dma_spin_lock
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|registered_dmac_list
)paren
suffix:semicolon
multiline_comment|/*&n; * A brief note about the reasons for this API as it stands.&n; *&n; * For starters, the old ISA DMA API didn&squot;t work for us for a number of&n; * reasons, for one, the vast majority of channels on the SH DMAC are&n; * dual-address mode only, and both the new and the old DMA APIs are after the&n; * concept of managing a DMA buffer, which doesn&squot;t overly fit this model very&n; * well. In addition to which, the new API is largely geared at IOMMUs and&n; * GARTs, and doesn&squot;t even support the channel notion very well.&n; *&n; * The other thing that&squot;s a marginal issue, is the sheer number of random DMA&n; * engines that are present (ie, in boards like the Dreamcast), some of which&n; * cascade off of the SH DMAC, and others do not. As such, there was a real&n; * need for a scalable subsystem that could deal with both single and&n; * dual-address mode usage, in addition to interoperating with cascaded DMACs.&n; *&n; * There really isn&squot;t any reason why this needs to be SH specific, though I&squot;m&n; * not aware of too many other processors (with the exception of some MIPS)&n; * that have the same concept of a dual address mode, or any real desire to&n; * actually make use of the DMAC even if such a subsystem were exposed&n; * elsewhere.&n; *&n; * The idea for this was derived from the ARM port, which acted as an excellent&n; * reference when trying to address these issues.&n; *&n; * It should also be noted that the decision to add Yet Another DMA API(tm) to&n; * the kernel wasn&squot;t made easily, and was only decided upon after conferring&n; * with jejb with regards to the state of the old and new APIs as they applied&n; * to these circumstances. Philip Blundell was also a great help in figuring&n; * out some single-address mode DMA semantics that were otherwise rather&n; * confusing.&n; */
DECL|function|get_dma_info
r_struct
id|dma_info
op_star
id|get_dma_info
c_func
(paren
r_int
r_int
id|chan
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|total
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Look for each DMAC&squot;s range to determine who the owner of&n;&t; * the channel is.&n;&t; */
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|tmp
comma
op_amp
id|registered_dmac_list
)paren
(brace
r_struct
id|dma_info
op_star
id|info
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|dma_info
comma
id|list
)paren
suffix:semicolon
id|total
op_add_assign
id|info-&gt;nr_channels
suffix:semicolon
r_if
c_cond
(paren
id|chan
OG
id|total
)paren
r_continue
suffix:semicolon
r_return
id|info
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|get_dma_channel
r_struct
id|dma_channel
op_star
id|get_dma_channel
c_func
(paren
r_int
r_int
id|chan
)paren
(brace
r_struct
id|dma_info
op_star
id|info
op_assign
id|get_dma_info
c_func
(paren
id|chan
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_return
id|info-&gt;channels
op_plus
id|chan
suffix:semicolon
)brace
DECL|function|get_dma_residue
r_int
id|get_dma_residue
c_func
(paren
r_int
r_int
id|chan
)paren
(brace
r_struct
id|dma_info
op_star
id|info
op_assign
id|get_dma_info
c_func
(paren
id|chan
)paren
suffix:semicolon
r_struct
id|dma_channel
op_star
id|channel
op_assign
op_amp
id|info-&gt;channels
(braket
id|chan
)braket
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;ops-&gt;get_residue
)paren
r_return
id|info-&gt;ops
op_member_access_from_pointer
id|get_residue
c_func
(paren
id|channel
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|request_dma
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|chan
comma
r_const
r_char
op_star
id|dev_id
)paren
(brace
r_struct
id|dma_info
op_star
id|info
op_assign
id|get_dma_info
c_func
(paren
id|chan
)paren
suffix:semicolon
r_struct
id|dma_channel
op_star
id|channel
op_assign
op_amp
id|info-&gt;channels
(braket
id|chan
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|channel-&gt;sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;ops
op_logical_or
id|chan
op_ge
id|MAX_DMA_CHANNELS
)paren
(brace
id|up
c_func
(paren
op_amp
id|channel-&gt;sem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|channel-&gt;busy
comma
l_int|1
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|channel-&gt;dev_id
comma
id|dev_id
comma
r_sizeof
(paren
id|channel-&gt;dev_id
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|channel-&gt;sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;ops-&gt;request
)paren
r_return
id|info-&gt;ops
op_member_access_from_pointer
id|request
c_func
(paren
id|channel
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_dma
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|chan
)paren
(brace
r_struct
id|dma_info
op_star
id|info
op_assign
id|get_dma_info
c_func
(paren
id|chan
)paren
suffix:semicolon
r_struct
id|dma_channel
op_star
id|channel
op_assign
op_amp
id|info-&gt;channels
(braket
id|chan
)braket
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;ops-&gt;free
)paren
id|info-&gt;ops
op_member_access_from_pointer
id|free
c_func
(paren
id|channel
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|channel-&gt;busy
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|dma_wait_for_completion
r_void
id|dma_wait_for_completion
c_func
(paren
r_int
r_int
id|chan
)paren
(brace
r_struct
id|dma_info
op_star
id|info
op_assign
id|get_dma_info
c_func
(paren
id|chan
)paren
suffix:semicolon
r_struct
id|dma_channel
op_star
id|channel
op_assign
op_amp
id|info-&gt;channels
(braket
id|chan
)braket
suffix:semicolon
r_if
c_cond
(paren
id|channel-&gt;flags
op_amp
id|DMA_TEI_CAPABLE
)paren
(brace
id|wait_event
c_func
(paren
id|channel-&gt;wait_queue
comma
(paren
id|info-&gt;ops
op_member_access_from_pointer
id|get_residue
c_func
(paren
id|channel
)paren
op_eq
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|info-&gt;ops
op_member_access_from_pointer
id|get_residue
c_func
(paren
id|channel
)paren
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|dma_configure_channel
r_void
id|dma_configure_channel
c_func
(paren
r_int
r_int
id|chan
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|dma_info
op_star
id|info
op_assign
id|get_dma_info
c_func
(paren
id|chan
)paren
suffix:semicolon
r_struct
id|dma_channel
op_star
id|channel
op_assign
op_amp
id|info-&gt;channels
(braket
id|chan
)braket
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;ops-&gt;configure
)paren
id|info-&gt;ops
op_member_access_from_pointer
id|configure
c_func
(paren
id|channel
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|dma_xfer
r_int
id|dma_xfer
c_func
(paren
r_int
r_int
id|chan
comma
r_int
r_int
id|from
comma
r_int
r_int
id|to
comma
r_int
id|size
comma
r_int
r_int
id|mode
)paren
(brace
r_struct
id|dma_info
op_star
id|info
op_assign
id|get_dma_info
c_func
(paren
id|chan
)paren
suffix:semicolon
r_struct
id|dma_channel
op_star
id|channel
op_assign
op_amp
id|info-&gt;channels
(braket
id|chan
)braket
suffix:semicolon
id|channel-&gt;sar
op_assign
id|from
suffix:semicolon
id|channel-&gt;dar
op_assign
id|to
suffix:semicolon
id|channel-&gt;count
op_assign
id|size
suffix:semicolon
id|channel-&gt;mode
op_assign
id|mode
suffix:semicolon
r_return
id|info-&gt;ops
op_member_access_from_pointer
id|xfer
c_func
(paren
id|channel
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|dma_read_proc
r_static
r_int
id|dma_read_proc
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|len
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|tmp
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|registered_dmac_list
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Iterate over each registered DMAC&n;&t; */
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|tmp
comma
op_amp
id|registered_dmac_list
)paren
(brace
r_struct
id|dma_info
op_star
id|info
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|dma_info
comma
id|list
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Iterate over each channel&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|info-&gt;nr_channels
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dma_channel
op_star
id|channel
op_assign
id|info-&gt;channels
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|channel-&gt;flags
op_amp
id|DMA_CONFIGURED
)paren
)paren
r_continue
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%2d: %14s    %s&bslash;n&quot;
comma
id|i
comma
id|info-&gt;name
comma
id|channel-&gt;dev_id
)paren
suffix:semicolon
)brace
)brace
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
macro_line|#endif
DECL|function|register_dmac
r_int
id|__init
id|register_dmac
c_func
(paren
r_struct
id|dma_info
op_star
id|info
)paren
(brace
r_int
id|i
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|info-&gt;list
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;DMA: Registering %s handler (%d channel%s).&bslash;n&quot;
comma
id|info-&gt;name
comma
id|info-&gt;nr_channels
comma
id|info-&gt;nr_channels
OG
l_int|1
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
(paren
id|info-&gt;flags
op_amp
id|DMAC_CHANNELS_CONFIGURED
)paren
op_logical_and
op_logical_neg
id|info-&gt;channels
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t touch pre-configured channels&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|info-&gt;flags
op_amp
id|DMAC_CHANNELS_CONFIGURED
)paren
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
r_struct
id|dma_channel
)paren
op_star
id|info-&gt;nr_channels
suffix:semicolon
id|info-&gt;channels
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;channels
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|info-&gt;channels
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
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
id|info-&gt;nr_channels
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dma_channel
op_star
id|chan
op_assign
id|info-&gt;channels
op_plus
id|i
suffix:semicolon
id|chan-&gt;chan
op_assign
id|i
suffix:semicolon
id|memcpy
c_func
(paren
id|chan-&gt;dev_id
comma
l_string|&quot;Unused&quot;
comma
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;flags
op_amp
id|DMAC_CHANNELS_TEI_CAPABLE
)paren
id|chan-&gt;flags
op_or_assign
id|DMA_TEI_CAPABLE
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|chan-&gt;sem
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|chan-&gt;wait_queue
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSFS
id|dma_create_sysfs_files
c_func
(paren
id|chan
)paren
suffix:semicolon
macro_line|#endif
)brace
id|list_add
c_func
(paren
op_amp
id|info-&gt;list
comma
op_amp
id|registered_dmac_list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_dmac
r_void
id|__exit
id|unregister_dmac
c_func
(paren
r_struct
id|dma_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|info-&gt;flags
op_amp
id|DMAC_CHANNELS_CONFIGURED
)paren
)paren
id|kfree
c_func
(paren
id|info-&gt;channels
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|info-&gt;list
)paren
suffix:semicolon
)brace
DECL|function|dma_api_init
r_static
r_int
id|__init
id|dma_api_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DMA: Registering DMA API.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|create_proc_read_entry
c_func
(paren
l_string|&quot;dma&quot;
comma
l_int|0
comma
l_int|0
comma
id|dma_read_proc
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dma_api_init
id|subsys_initcall
c_func
(paren
id|dma_api_init
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Paul Mundt &lt;lethal@linux-sh.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;DMA API for SuperH&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|request_dma
id|EXPORT_SYMBOL
c_func
(paren
id|request_dma
)paren
suffix:semicolon
DECL|variable|free_dma
id|EXPORT_SYMBOL
c_func
(paren
id|free_dma
)paren
suffix:semicolon
DECL|variable|register_dmac
id|EXPORT_SYMBOL
c_func
(paren
id|register_dmac
)paren
suffix:semicolon
DECL|variable|get_dma_residue
id|EXPORT_SYMBOL
c_func
(paren
id|get_dma_residue
)paren
suffix:semicolon
DECL|variable|get_dma_info
id|EXPORT_SYMBOL
c_func
(paren
id|get_dma_info
)paren
suffix:semicolon
DECL|variable|get_dma_channel
id|EXPORT_SYMBOL
c_func
(paren
id|get_dma_channel
)paren
suffix:semicolon
DECL|variable|dma_xfer
id|EXPORT_SYMBOL
c_func
(paren
id|dma_xfer
)paren
suffix:semicolon
DECL|variable|dma_wait_for_completion
id|EXPORT_SYMBOL
c_func
(paren
id|dma_wait_for_completion
)paren
suffix:semicolon
DECL|variable|dma_configure_channel
id|EXPORT_SYMBOL
c_func
(paren
id|dma_configure_channel
)paren
suffix:semicolon
eof
