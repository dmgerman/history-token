multiline_comment|/*&n; *  gendisk handling&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
DECL|macro|MAX_PROBE_HASH
mdefine_line|#define MAX_PROBE_HASH 255&t;/* random */
DECL|variable|block_subsys
r_static
r_struct
id|subsystem
id|block_subsys
suffix:semicolon
multiline_comment|/*&n; * Can be merged with blk_probe or deleted altogether. Later.&n; *&n; * Modified under both block_subsys.rwsem and major_names_lock.&n; */
DECL|struct|blk_major_name
r_static
r_struct
id|blk_major_name
(brace
DECL|member|next
r_struct
id|blk_major_name
op_star
id|next
suffix:semicolon
DECL|member|major
r_int
id|major
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|major_names
)brace
op_star
id|major_names
(braket
id|MAX_PROBE_HASH
)braket
suffix:semicolon
DECL|variable|major_names_lock
r_static
id|spinlock_t
id|major_names_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|struct|blk_probe
r_static
r_struct
id|blk_probe
(brace
DECL|member|next
r_struct
id|blk_probe
op_star
id|next
suffix:semicolon
DECL|member|dev
id|dev_t
id|dev
suffix:semicolon
DECL|member|range
r_int
r_int
id|range
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|get
r_struct
id|gendisk
op_star
(paren
op_star
id|get
)paren
(paren
id|dev_t
id|dev
comma
r_int
op_star
id|part
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|lock
r_int
(paren
op_star
id|lock
)paren
(paren
id|dev_t
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|variable|probes
)brace
op_star
id|probes
(braket
id|MAX_PROBE_HASH
)braket
suffix:semicolon
multiline_comment|/* index in the above - for now: assume no multimajor ranges */
DECL|function|major_to_index
r_static
r_inline
r_int
id|major_to_index
c_func
(paren
r_int
id|major
)paren
(brace
r_return
id|major
op_mod
id|MAX_PROBE_HASH
suffix:semicolon
)brace
DECL|function|dev_to_index
r_static
r_inline
r_int
id|dev_to_index
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_return
id|major_to_index
c_func
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * __bdevname may be called from interrupts, and must be atomic&n; */
DECL|function|__bdevname
r_const
r_char
op_star
id|__bdevname
c_func
(paren
id|dev_t
id|dev
comma
r_char
op_star
id|buffer
)paren
(brace
r_char
op_star
id|name
op_assign
l_string|&quot;unknown-block&quot;
suffix:semicolon
r_int
r_int
id|major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|index
op_assign
id|major_to_index
c_func
(paren
id|major
)paren
suffix:semicolon
r_struct
id|blk_major_name
op_star
id|n
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|major_names_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
id|major_names
(braket
id|index
)braket
suffix:semicolon
id|n
suffix:semicolon
id|n
op_assign
id|n-&gt;next
)paren
r_if
c_cond
(paren
id|n-&gt;major
op_eq
id|major
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
id|name
op_assign
op_amp
(paren
id|n-&gt;name
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|buffer
comma
id|BDEVNAME_SIZE
comma
l_string|&quot;%s(%u,%u)&quot;
comma
id|name
comma
id|major
comma
id|minor
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|major_names_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
multiline_comment|/* get block device names in somewhat random order */
DECL|function|get_blkdev_list
r_int
id|get_blkdev_list
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_struct
id|blk_major_name
op_star
id|n
suffix:semicolon
r_int
id|i
comma
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;nBlock devices:&bslash;n&quot;
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|block_subsys.rwsem
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
id|ARRAY_SIZE
c_func
(paren
id|major_names
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|n
op_assign
id|major_names
(braket
id|i
)braket
suffix:semicolon
id|n
suffix:semicolon
id|n
op_assign
id|n-&gt;next
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|p
op_plus
id|len
comma
l_string|&quot;%3d %s&bslash;n&quot;
comma
id|n-&gt;major
comma
id|n-&gt;name
)paren
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|register_blkdev
r_int
id|register_blkdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|blk_major_name
op_star
op_star
id|n
comma
op_star
id|p
suffix:semicolon
r_int
id|index
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
multiline_comment|/* temporary */
r_if
c_cond
(paren
id|major
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|index
op_assign
id|ARRAY_SIZE
c_func
(paren
id|major_names
)paren
op_minus
l_int|1
suffix:semicolon
id|index
OG
l_int|0
suffix:semicolon
id|index
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|major_names
(braket
id|index
)braket
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|index
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;register_blkdev: failed to get major for %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|major
op_assign
id|index
suffix:semicolon
id|ret
op_assign
id|major
suffix:semicolon
)brace
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|blk_major_name
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|p-&gt;major
op_assign
id|major
suffix:semicolon
id|strncpy
c_func
(paren
id|p-&gt;name
comma
id|name
comma
r_sizeof
(paren
id|p-&gt;name
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|p-&gt;name
(braket
r_sizeof
(paren
id|p-&gt;name
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|p-&gt;next
op_assign
l_int|0
suffix:semicolon
id|index
op_assign
id|major_to_index
c_func
(paren
id|major
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|major_names_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
op_amp
id|major_names
(braket
id|index
)braket
suffix:semicolon
op_star
id|n
suffix:semicolon
id|n
op_assign
op_amp
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|major
op_eq
id|major
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|n
)paren
op_star
id|n
op_assign
id|p
suffix:semicolon
r_else
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|major_names_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;register_blkdev: cannot get major %d for %s&bslash;n&quot;
comma
id|major
comma
id|name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|up_write
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* todo: make void - error printk here */
DECL|function|unregister_blkdev
r_int
id|unregister_blkdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|blk_major_name
op_star
op_star
id|n
suffix:semicolon
r_struct
id|blk_major_name
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
r_int
id|index
op_assign
id|major_to_index
c_func
(paren
id|major
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|major_names_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
op_amp
id|major_names
(braket
id|index
)braket
suffix:semicolon
op_star
id|n
suffix:semicolon
id|n
op_assign
op_amp
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|major
op_eq
id|major
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|n
op_logical_or
id|strcmp
c_func
(paren
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|name
comma
id|name
)paren
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
(brace
id|p
op_assign
op_star
id|n
suffix:semicolon
op_star
id|n
op_assign
id|p-&gt;next
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|major_names_lock
comma
id|flags
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Register device numbers dev..(dev+range-1)&n; * range must be nonzero&n; * The hash chain is sorted on range, so that subranges can override.&n; */
DECL|function|blk_register_region
r_void
id|blk_register_region
c_func
(paren
id|dev_t
id|dev
comma
r_int
r_int
id|range
comma
r_struct
id|module
op_star
id|module
comma
r_struct
id|gendisk
op_star
(paren
op_star
id|probe
)paren
(paren
id|dev_t
comma
r_int
op_star
comma
r_void
op_star
)paren
comma
r_int
(paren
op_star
id|lock
)paren
(paren
id|dev_t
comma
r_void
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|index
op_assign
id|dev_to_index
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|blk_probe
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|blk_probe
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_struct
id|blk_probe
op_star
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|p-&gt;owner
op_assign
id|module
suffix:semicolon
id|p-&gt;get
op_assign
id|probe
suffix:semicolon
id|p-&gt;lock
op_assign
id|lock
suffix:semicolon
id|p-&gt;dev
op_assign
id|dev
suffix:semicolon
id|p-&gt;range
op_assign
id|range
suffix:semicolon
id|p-&gt;data
op_assign
id|data
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
op_amp
id|probes
(braket
id|index
)braket
suffix:semicolon
op_star
id|s
op_logical_and
(paren
op_star
id|s
)paren
op_member_access_from_pointer
id|range
OL
id|range
suffix:semicolon
id|s
op_assign
op_amp
(paren
op_star
id|s
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
id|p-&gt;next
op_assign
op_star
id|s
suffix:semicolon
op_star
id|s
op_assign
id|p
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
)brace
DECL|function|blk_unregister_region
r_void
id|blk_unregister_region
c_func
(paren
id|dev_t
id|dev
comma
r_int
r_int
id|range
)paren
(brace
r_int
id|index
op_assign
id|dev_to_index
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|blk_probe
op_star
op_star
id|s
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
op_amp
id|probes
(braket
id|index
)braket
suffix:semicolon
op_star
id|s
suffix:semicolon
id|s
op_assign
op_amp
(paren
op_star
id|s
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_struct
id|blk_probe
op_star
id|p
op_assign
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;dev
op_eq
id|dev
op_logical_and
id|p-&gt;range
op_eq
id|range
)paren
(brace
op_star
id|s
op_assign
id|p-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|up_write
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
)brace
DECL|variable|blk_register_region
id|EXPORT_SYMBOL
c_func
(paren
id|blk_register_region
)paren
suffix:semicolon
DECL|variable|blk_unregister_region
id|EXPORT_SYMBOL
c_func
(paren
id|blk_unregister_region
)paren
suffix:semicolon
DECL|function|exact_match
r_static
r_struct
id|gendisk
op_star
id|exact_match
c_func
(paren
id|dev_t
id|dev
comma
r_int
op_star
id|part
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|data
suffix:semicolon
)brace
DECL|function|exact_lock
r_static
r_int
id|exact_lock
c_func
(paren
id|dev_t
id|dev
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|gendisk
op_star
id|p
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_disk
c_func
(paren
id|p
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * add_gendisk - add partitioning information to kernel list&n; * @disk: per-device partitioning information&n; *&n; * This function registers the partitioning information in @disk&n; * with the kernel.&n; */
DECL|function|add_disk
r_void
id|add_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
id|disk-&gt;flags
op_or_assign
id|GENHD_FL_UP
suffix:semicolon
id|blk_register_region
c_func
(paren
id|MKDEV
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
)paren
comma
id|disk-&gt;minors
comma
l_int|NULL
comma
id|exact_match
comma
id|exact_lock
comma
id|disk
)paren
suffix:semicolon
id|register_disk
c_func
(paren
id|disk
)paren
suffix:semicolon
id|elv_register_queue
c_func
(paren
id|disk
)paren
suffix:semicolon
)brace
DECL|variable|add_disk
id|EXPORT_SYMBOL
c_func
(paren
id|add_disk
)paren
suffix:semicolon
DECL|variable|del_gendisk
id|EXPORT_SYMBOL
c_func
(paren
id|del_gendisk
)paren
suffix:semicolon
multiline_comment|/* in partitions/check.c */
DECL|function|unlink_gendisk
r_void
id|unlink_gendisk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
id|elv_unregister_queue
c_func
(paren
id|disk
)paren
suffix:semicolon
id|blk_unregister_region
c_func
(paren
id|MKDEV
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
)paren
comma
id|disk-&gt;minors
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * get_gendisk - get partitioning information for a given device&n; * @dev: device to get partitioning information for&n; *&n; * This function gets the structure containing partitioning&n; * information for the given device @dev.&n; */
r_struct
id|gendisk
op_star
DECL|function|get_gendisk
id|get_gendisk
c_func
(paren
id|dev_t
id|dev
comma
r_int
op_star
id|part
)paren
(brace
r_int
id|index
op_assign
id|dev_to_index
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|gendisk
op_star
id|disk
suffix:semicolon
r_struct
id|blk_probe
op_star
id|p
suffix:semicolon
r_int
id|best
op_assign
op_complement
l_int|0U
suffix:semicolon
id|retry
suffix:colon
id|down_read
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|probes
(braket
id|index
)braket
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|gendisk
op_star
(paren
op_star
id|probe
)paren
(paren
id|dev_t
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_struct
id|module
op_star
id|owner
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;dev
OG
id|dev
op_logical_or
id|p-&gt;dev
op_plus
id|p-&gt;range
op_minus
l_int|1
OL
id|dev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;range
op_minus
l_int|1
op_ge
id|best
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|p-&gt;owner
)paren
)paren
r_continue
suffix:semicolon
id|owner
op_assign
id|p-&gt;owner
suffix:semicolon
id|data
op_assign
id|p-&gt;data
suffix:semicolon
id|probe
op_assign
id|p-&gt;get
suffix:semicolon
id|best
op_assign
id|p-&gt;range
op_minus
l_int|1
suffix:semicolon
op_star
id|part
op_assign
id|dev
op_minus
id|p-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;lock
op_logical_and
id|p
op_member_access_from_pointer
id|lock
c_func
(paren
id|dev
comma
id|data
)paren
OL
l_int|0
)paren
(brace
id|module_put
c_func
(paren
id|owner
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
id|disk
op_assign
id|probe
c_func
(paren
id|dev
comma
id|part
comma
id|data
)paren
suffix:semicolon
multiline_comment|/* Currently -&gt;owner protects _only_ -&gt;probe() itself. */
id|module_put
c_func
(paren
id|owner
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disk
)paren
r_return
id|disk
suffix:semicolon
r_goto
id|retry
suffix:semicolon
multiline_comment|/* this terminates: best decreases */
)brace
id|up_read
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/* iterator */
DECL|function|part_start
r_static
r_void
op_star
id|part_start
c_func
(paren
r_struct
id|seq_file
op_star
id|part
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|loff_t
id|l
op_assign
op_star
id|pos
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|block_subsys.kset.list
)paren
r_if
c_cond
(paren
op_logical_neg
id|l
op_decrement
)paren
r_return
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|gendisk
comma
id|kobj.entry
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|part_next
r_static
r_void
op_star
id|part_next
c_func
(paren
r_struct
id|seq_file
op_star
id|part
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|p
op_assign
(paren
(paren
r_struct
id|gendisk
op_star
)paren
id|v
)paren
op_member_access_from_pointer
id|kobj.entry.next
suffix:semicolon
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|p
op_eq
op_amp
id|block_subsys.kset.list
ques
c_cond
l_int|NULL
suffix:colon
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|gendisk
comma
id|kobj.entry
)paren
suffix:semicolon
)brace
DECL|function|part_stop
r_static
r_void
id|part_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|part
comma
r_void
op_star
id|v
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|block_subsys.rwsem
)paren
suffix:semicolon
)brace
DECL|function|show_partition
r_static
r_int
id|show_partition
c_func
(paren
r_struct
id|seq_file
op_star
id|part
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|gendisk
op_star
id|sgp
op_assign
id|v
suffix:semicolon
r_int
id|n
suffix:semicolon
r_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_if
c_cond
(paren
op_amp
id|sgp-&gt;kobj.entry
op_eq
id|block_subsys.kset.list.next
)paren
id|seq_puts
c_func
(paren
id|part
comma
l_string|&quot;major minor  #blocks  name&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t show non-partitionable devices or empty devices */
r_if
c_cond
(paren
op_logical_neg
id|get_capacity
c_func
(paren
id|sgp
)paren
op_logical_or
id|sgp-&gt;minors
op_eq
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* show the full disk and all non-0 size partitions of it */
id|seq_printf
c_func
(paren
id|part
comma
l_string|&quot;%4d  %4d %10llu %s&bslash;n&quot;
comma
id|sgp-&gt;major
comma
id|sgp-&gt;first_minor
comma
(paren
r_int
r_int
r_int
)paren
id|get_capacity
c_func
(paren
id|sgp
)paren
op_rshift
l_int|1
comma
id|disk_name
c_func
(paren
id|sgp
comma
l_int|0
comma
id|buf
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|sgp-&gt;minors
op_minus
l_int|1
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sgp-&gt;part
(braket
id|n
)braket
dot
id|nr_sects
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|seq_printf
c_func
(paren
id|part
comma
l_string|&quot;%4d  %4d %10llu %s&bslash;n&quot;
comma
id|sgp-&gt;major
comma
id|n
op_plus
l_int|1
op_plus
id|sgp-&gt;first_minor
comma
(paren
r_int
r_int
r_int
)paren
id|sgp-&gt;part
(braket
id|n
)braket
dot
id|nr_sects
op_rshift
l_int|1
comma
id|disk_name
c_func
(paren
id|sgp
comma
id|n
op_plus
l_int|1
comma
id|buf
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|partitions_op
r_struct
id|seq_operations
id|partitions_op
op_assign
(brace
dot
id|start
op_assign
id|part_start
comma
dot
id|next
op_assign
id|part_next
comma
dot
id|stop
op_assign
id|part_stop
comma
dot
id|show
op_assign
id|show_partition
)brace
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|blk_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|base_probe
r_static
r_struct
id|gendisk
op_star
id|base_probe
c_func
(paren
id|dev_t
id|dev
comma
r_int
op_star
id|part
comma
r_void
op_star
id|data
)paren
(brace
r_char
id|name
(braket
l_int|30
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;block-major-%d&quot;
comma
id|MAJOR
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|device_init
r_int
id|__init
id|device_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|blk_probe
op_star
id|base
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|blk_probe
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|base
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|blk_probe
)paren
)paren
suffix:semicolon
id|base-&gt;dev
op_assign
l_int|1
suffix:semicolon
id|base-&gt;range
op_assign
op_complement
l_int|0
suffix:semicolon
multiline_comment|/* range 1 .. ~0 */
id|base-&gt;get
op_assign
id|base_probe
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
id|MAX_PROBE_HASH
suffix:semicolon
id|i
op_increment
)paren
id|probes
(braket
id|i
)braket
op_assign
id|base
suffix:semicolon
multiline_comment|/* must remain last in chain */
id|blk_dev_init
c_func
(paren
)paren
suffix:semicolon
id|subsystem_register
c_func
(paren
op_amp
id|block_subsys
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|device_init
id|subsys_initcall
c_func
(paren
id|device_init
)paren
suffix:semicolon
multiline_comment|/*&n; * kobject &amp; sysfs bindings for block devices&n; */
DECL|macro|to_disk
mdefine_line|#define to_disk(obj) container_of(obj,struct gendisk,kobj)
DECL|struct|disk_attribute
r_struct
id|disk_attribute
(brace
DECL|member|attr
r_struct
id|attribute
id|attr
suffix:semicolon
DECL|member|show
id|ssize_t
(paren
op_star
id|show
)paren
(paren
r_struct
id|gendisk
op_star
comma
r_char
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|function|disk_attr_show
r_static
id|ssize_t
id|disk_attr_show
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_char
op_star
id|page
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
op_assign
id|to_disk
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|disk_attribute
op_star
id|disk_attr
op_assign
id|container_of
c_func
(paren
id|attr
comma
r_struct
id|disk_attribute
comma
id|attr
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|disk_attr-&gt;show
)paren
id|ret
op_assign
id|disk_attr
op_member_access_from_pointer
id|show
c_func
(paren
id|disk
comma
id|page
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|disk_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|disk_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
op_amp
id|disk_attr_show
comma
)brace
suffix:semicolon
DECL|function|disk_dev_read
r_static
id|ssize_t
id|disk_dev_read
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
comma
r_char
op_star
id|page
)paren
(brace
id|dev_t
id|base
op_assign
id|MKDEV
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%04x&bslash;n&quot;
comma
(paren
r_int
)paren
id|base
)paren
suffix:semicolon
)brace
DECL|function|disk_range_read
r_static
id|ssize_t
id|disk_range_read
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
comma
r_char
op_star
id|page
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|disk-&gt;minors
)paren
suffix:semicolon
)brace
DECL|function|disk_size_read
r_static
id|ssize_t
id|disk_size_read
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
comma
r_char
op_star
id|page
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%llu&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|get_capacity
c_func
(paren
id|disk
)paren
)paren
suffix:semicolon
)brace
DECL|function|jiffies_to_msec
r_static
r_inline
r_int
id|jiffies_to_msec
c_func
(paren
r_int
id|jif
)paren
(brace
macro_line|#if 1000 % HZ == 0
r_return
id|jif
op_star
(paren
l_int|1000
op_div
id|HZ
)paren
suffix:semicolon
macro_line|#elif HZ % 1000 == 0
r_return
id|jif
op_div
(paren
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
macro_line|#else
r_return
(paren
id|jif
op_div
id|HZ
)paren
op_star
l_int|1000
op_plus
(paren
id|jif
op_mod
id|HZ
)paren
op_star
l_int|1000
op_div
id|HZ
suffix:semicolon
macro_line|#endif
)brace
DECL|function|disk_stats_read
r_static
id|ssize_t
id|disk_stats_read
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
comma
r_char
op_star
id|page
)paren
(brace
id|disk_round_stats
c_func
(paren
id|disk
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%8u %8u %8llu %8u &quot;
l_string|&quot;%8u %8u %8llu %8u &quot;
l_string|&quot;%8u %8u %8u&quot;
l_string|&quot;&bslash;n&quot;
comma
id|disk_stat_read
c_func
(paren
id|disk
comma
id|reads
)paren
comma
id|disk_stat_read
c_func
(paren
id|disk
comma
id|read_merges
)paren
comma
(paren
r_int
r_int
r_int
)paren
id|disk_stat_read
c_func
(paren
id|disk
comma
id|read_sectors
)paren
comma
id|jiffies_to_msec
c_func
(paren
id|disk_stat_read
c_func
(paren
id|disk
comma
id|read_ticks
)paren
)paren
comma
id|disk_stat_read
c_func
(paren
id|disk
comma
id|writes
)paren
comma
id|disk_stat_read
c_func
(paren
id|disk
comma
id|write_merges
)paren
comma
(paren
r_int
r_int
r_int
)paren
id|disk_stat_read
c_func
(paren
id|disk
comma
id|write_sectors
)paren
comma
id|jiffies_to_msec
c_func
(paren
id|disk_stat_read
c_func
(paren
id|disk
comma
id|write_ticks
)paren
)paren
comma
id|disk_stat_read
c_func
(paren
id|disk
comma
id|in_flight
)paren
comma
id|jiffies_to_msec
c_func
(paren
id|disk_stat_read
c_func
(paren
id|disk
comma
id|io_ticks
)paren
)paren
comma
id|jiffies_to_msec
c_func
(paren
id|disk_stat_read
c_func
(paren
id|disk
comma
id|time_in_queue
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|variable|disk_attr_dev
r_static
r_struct
id|disk_attribute
id|disk_attr_dev
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;dev&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
)brace
comma
dot
id|show
op_assign
id|disk_dev_read
)brace
suffix:semicolon
DECL|variable|disk_attr_range
r_static
r_struct
id|disk_attribute
id|disk_attr_range
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;range&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
)brace
comma
dot
id|show
op_assign
id|disk_range_read
)brace
suffix:semicolon
DECL|variable|disk_attr_size
r_static
r_struct
id|disk_attribute
id|disk_attr_size
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;size&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
)brace
comma
dot
id|show
op_assign
id|disk_size_read
)brace
suffix:semicolon
DECL|variable|disk_attr_stat
r_static
r_struct
id|disk_attribute
id|disk_attr_stat
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;stat&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
)brace
comma
dot
id|show
op_assign
id|disk_stats_read
)brace
suffix:semicolon
DECL|variable|default_attrs
r_static
r_struct
id|attribute
op_star
id|default_attrs
(braket
)braket
op_assign
(brace
op_amp
id|disk_attr_dev.attr
comma
op_amp
id|disk_attr_range.attr
comma
op_amp
id|disk_attr_size.attr
comma
op_amp
id|disk_attr_stat.attr
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|disk_release
r_static
r_void
id|disk_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
op_assign
id|to_disk
c_func
(paren
id|kobj
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|disk-&gt;random
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|disk-&gt;part
)paren
suffix:semicolon
id|free_disk_stats
c_func
(paren
id|disk
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|disk
)paren
suffix:semicolon
)brace
DECL|variable|ktype_block
r_static
r_struct
id|kobj_type
id|ktype_block
op_assign
(brace
dot
id|release
op_assign
id|disk_release
comma
dot
id|sysfs_ops
op_assign
op_amp
id|disk_sysfs_ops
comma
dot
id|default_attrs
op_assign
id|default_attrs
comma
)brace
suffix:semicolon
multiline_comment|/* declare block_subsys. */
DECL|variable|decl_subsys
r_static
id|decl_subsys
c_func
(paren
id|block
comma
op_amp
id|ktype_block
)paren
suffix:semicolon
DECL|function|alloc_disk
r_struct
id|gendisk
op_star
id|alloc_disk
c_func
(paren
r_int
id|minors
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|gendisk
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disk
)paren
(brace
id|memset
c_func
(paren
id|disk
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|gendisk
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|init_disk_stats
c_func
(paren
id|disk
)paren
)paren
(brace
id|kfree
c_func
(paren
id|disk
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|minors
OG
l_int|1
)paren
(brace
r_int
id|size
op_assign
(paren
id|minors
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|hd_struct
)paren
suffix:semicolon
id|disk-&gt;part
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
id|disk-&gt;part
)paren
(brace
id|kfree
c_func
(paren
id|disk
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|disk-&gt;part
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
)brace
id|disk-&gt;minors
op_assign
id|minors
suffix:semicolon
r_while
c_loop
(paren
id|minors
op_rshift_assign
l_int|1
)paren
id|disk-&gt;minor_shift
op_increment
suffix:semicolon
id|kobj_set_kset_s
c_func
(paren
id|disk
comma
id|block_subsys
)paren
suffix:semicolon
id|kobject_init
c_func
(paren
op_amp
id|disk-&gt;kobj
)paren
suffix:semicolon
id|rand_initialize_disk
c_func
(paren
id|disk
)paren
suffix:semicolon
)brace
r_return
id|disk
suffix:semicolon
)brace
DECL|function|get_disk
r_struct
id|gendisk
op_star
id|get_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
r_struct
id|module
op_star
id|owner
suffix:semicolon
r_struct
id|kobject
op_star
id|kobj
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disk-&gt;fops
)paren
r_return
l_int|NULL
suffix:semicolon
id|owner
op_assign
id|disk-&gt;fops-&gt;owner
suffix:semicolon
r_if
c_cond
(paren
id|owner
op_logical_and
op_logical_neg
id|try_module_get
c_func
(paren
id|owner
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|kobj
op_assign
id|kobject_get
c_func
(paren
op_amp
id|disk-&gt;kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kobj
op_eq
l_int|NULL
)paren
(brace
id|module_put
c_func
(paren
id|owner
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|to_disk
c_func
(paren
id|kobj
)paren
suffix:semicolon
)brace
DECL|function|put_disk
r_void
id|put_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
r_if
c_cond
(paren
id|disk
)paren
id|kobject_put
c_func
(paren
op_amp
id|disk-&gt;kobj
)paren
suffix:semicolon
)brace
DECL|variable|alloc_disk
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_disk
)paren
suffix:semicolon
DECL|variable|get_disk
id|EXPORT_SYMBOL
c_func
(paren
id|get_disk
)paren
suffix:semicolon
DECL|variable|put_disk
id|EXPORT_SYMBOL
c_func
(paren
id|put_disk
)paren
suffix:semicolon
DECL|function|set_device_ro
r_void
id|set_device_ro
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|flag
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
op_assign
id|bdev-&gt;bd_disk
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_contains
op_ne
id|bdev
)paren
(brace
r_int
id|part
op_assign
id|bdev-&gt;bd_dev
op_minus
id|MKDEV
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
)paren
suffix:semicolon
r_struct
id|hd_struct
op_star
id|p
op_assign
op_amp
id|disk-&gt;part
(braket
id|part
op_minus
l_int|1
)braket
suffix:semicolon
id|p-&gt;policy
op_assign
id|flag
suffix:semicolon
)brace
r_else
id|disk-&gt;policy
op_assign
id|flag
suffix:semicolon
)brace
DECL|function|set_disk_ro
r_void
id|set_disk_ro
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
comma
r_int
id|flag
)paren
(brace
r_int
id|i
suffix:semicolon
id|disk-&gt;policy
op_assign
id|flag
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
id|disk-&gt;minors
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
id|disk-&gt;part
(braket
id|i
)braket
dot
id|policy
op_assign
id|flag
suffix:semicolon
)brace
DECL|function|bdev_read_only
r_int
id|bdev_read_only
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev
)paren
r_return
l_int|0
suffix:semicolon
id|disk
op_assign
id|bdev-&gt;bd_disk
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_contains
op_ne
id|bdev
)paren
(brace
r_int
id|part
op_assign
id|bdev-&gt;bd_dev
op_minus
id|MKDEV
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
)paren
suffix:semicolon
r_struct
id|hd_struct
op_star
id|p
op_assign
op_amp
id|disk-&gt;part
(braket
id|part
op_minus
l_int|1
)braket
suffix:semicolon
r_return
id|p-&gt;policy
suffix:semicolon
)brace
r_else
r_return
id|disk-&gt;policy
suffix:semicolon
)brace
DECL|variable|bdev_read_only
id|EXPORT_SYMBOL
c_func
(paren
id|bdev_read_only
)paren
suffix:semicolon
DECL|variable|set_device_ro
id|EXPORT_SYMBOL
c_func
(paren
id|set_device_ro
)paren
suffix:semicolon
DECL|variable|set_disk_ro
id|EXPORT_SYMBOL
c_func
(paren
id|set_disk_ro
)paren
suffix:semicolon
eof
