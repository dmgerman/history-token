multiline_comment|/* Copyright (c) 2004 Coraid, Inc.  See COPYING for GPL terms. */
multiline_comment|/*&n; * aoeblk.c&n; * block device routines&n; */
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;aoe.h&quot;
DECL|variable|buf_pool_cache
r_static
id|kmem_cache_t
op_star
id|buf_pool_cache
suffix:semicolon
multiline_comment|/* add attributes for our block devices in sysfs */
DECL|function|aoedisk_show_state
r_static
id|ssize_t
id|aoedisk_show_state
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
r_struct
id|aoedev
op_star
id|d
op_assign
id|disk-&gt;private_data
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|page
comma
id|PAGE_SIZE
comma
l_string|&quot;%s%s&bslash;n&quot;
comma
(paren
id|d-&gt;flags
op_amp
id|DEVFL_UP
)paren
ques
c_cond
l_string|&quot;up&quot;
suffix:colon
l_string|&quot;down&quot;
comma
(paren
id|d-&gt;flags
op_amp
id|DEVFL_CLOSEWAIT
)paren
ques
c_cond
l_string|&quot;,closewait&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
DECL|function|aoedisk_show_mac
r_static
id|ssize_t
id|aoedisk_show_mac
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
r_struct
id|aoedev
op_star
id|d
op_assign
id|disk-&gt;private_data
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|page
comma
id|PAGE_SIZE
comma
l_string|&quot;%012llx&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|mac_addr
c_func
(paren
id|d-&gt;addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|aoedisk_show_netif
r_static
id|ssize_t
id|aoedisk_show_netif
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
r_struct
id|aoedev
op_star
id|d
op_assign
id|disk-&gt;private_data
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|page
comma
id|PAGE_SIZE
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|d-&gt;ifp-&gt;name
)paren
suffix:semicolon
)brace
DECL|variable|disk_attr_state
r_static
r_struct
id|disk_attribute
id|disk_attr_state
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;state&quot;
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
id|aoedisk_show_state
)brace
suffix:semicolon
DECL|variable|disk_attr_mac
r_static
r_struct
id|disk_attribute
id|disk_attr_mac
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mac&quot;
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
id|aoedisk_show_mac
)brace
suffix:semicolon
DECL|variable|disk_attr_netif
r_static
r_struct
id|disk_attribute
id|disk_attr_netif
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;netif&quot;
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
id|aoedisk_show_netif
)brace
suffix:semicolon
r_static
r_void
DECL|function|aoedisk_add_sysfs
id|aoedisk_add_sysfs
c_func
(paren
r_struct
id|aoedev
op_star
id|d
)paren
(brace
id|sysfs_create_file
c_func
(paren
op_amp
id|d-&gt;gd-&gt;kobj
comma
op_amp
id|disk_attr_state.attr
)paren
suffix:semicolon
id|sysfs_create_file
c_func
(paren
op_amp
id|d-&gt;gd-&gt;kobj
comma
op_amp
id|disk_attr_mac.attr
)paren
suffix:semicolon
id|sysfs_create_file
c_func
(paren
op_amp
id|d-&gt;gd-&gt;kobj
comma
op_amp
id|disk_attr_netif.attr
)paren
suffix:semicolon
)brace
r_void
DECL|function|aoedisk_rm_sysfs
id|aoedisk_rm_sysfs
c_func
(paren
r_struct
id|aoedev
op_star
id|d
)paren
(brace
id|sysfs_remove_link
c_func
(paren
op_amp
id|d-&gt;gd-&gt;kobj
comma
l_string|&quot;state&quot;
)paren
suffix:semicolon
id|sysfs_remove_link
c_func
(paren
op_amp
id|d-&gt;gd-&gt;kobj
comma
l_string|&quot;mac&quot;
)paren
suffix:semicolon
id|sysfs_remove_link
c_func
(paren
op_amp
id|d-&gt;gd-&gt;kobj
comma
l_string|&quot;netif&quot;
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|aoeblk_open
id|aoeblk_open
c_func
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
)paren
(brace
r_struct
id|aoedev
op_star
id|d
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
id|d
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;flags
op_amp
id|DEVFL_UP
)paren
(brace
id|d-&gt;nopen
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_static
r_int
DECL|function|aoeblk_release
id|aoeblk_release
c_func
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
)paren
(brace
r_struct
id|aoedev
op_star
id|d
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
id|d
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|d-&gt;nopen
op_eq
l_int|0
op_logical_and
(paren
id|d-&gt;flags
op_amp
id|DEVFL_CLOSEWAIT
)paren
)paren
(brace
id|d-&gt;flags
op_and_assign
op_complement
id|DEVFL_CLOSEWAIT
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|aoecmd_cfg
c_func
(paren
id|d-&gt;aoemajor
comma
id|d-&gt;aoeminor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|aoeblk_make_request
id|aoeblk_make_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_struct
id|aoedev
op_star
id|d
suffix:semicolon
r_struct
id|buf
op_star
id|buf
suffix:semicolon
r_struct
id|sk_buff
op_star
id|sl
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
id|blk_queue_bounce
c_func
(paren
id|q
comma
op_amp
id|bio
)paren
suffix:semicolon
id|d
op_assign
id|bio-&gt;bi_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
id|buf
op_assign
id|mempool_alloc
c_func
(paren
id|d-&gt;bufpool
comma
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;aoe: aoeblk_make_request: buf allocation &quot;
l_string|&quot;failure&bslash;n&quot;
)paren
suffix:semicolon
id|bio_endio
c_func
(paren
id|bio
comma
id|bio-&gt;bi_size
comma
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|buf
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|buf-&gt;bufs
)paren
suffix:semicolon
id|buf-&gt;bio
op_assign
id|bio
suffix:semicolon
id|buf-&gt;resid
op_assign
id|bio-&gt;bi_size
suffix:semicolon
id|buf-&gt;sector
op_assign
id|bio-&gt;bi_sector
suffix:semicolon
id|buf-&gt;bv
op_assign
id|buf-&gt;bio-&gt;bi_io_vec
suffix:semicolon
id|buf-&gt;bv_resid
op_assign
id|buf-&gt;bv-&gt;bv_len
suffix:semicolon
id|buf-&gt;bufaddr
op_assign
id|page_address
c_func
(paren
id|buf-&gt;bv-&gt;bv_page
)paren
op_plus
id|buf-&gt;bv-&gt;bv_offset
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|d-&gt;flags
op_amp
id|DEVFL_UP
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;aoe: aoeblk_make_request: device %ld.%ld is not up&bslash;n&quot;
comma
id|d-&gt;aoemajor
comma
id|d-&gt;aoeminor
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|mempool_free
c_func
(paren
id|buf
comma
id|d-&gt;bufpool
)paren
suffix:semicolon
id|bio_endio
c_func
(paren
id|bio
comma
id|bio-&gt;bi_size
comma
op_minus
id|ENXIO
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|list_add_tail
c_func
(paren
op_amp
id|buf-&gt;bufs
comma
op_amp
id|d-&gt;bufq
)paren
suffix:semicolon
id|aoecmd_work
c_func
(paren
id|d
)paren
suffix:semicolon
id|sl
op_assign
id|d-&gt;skblist
suffix:semicolon
id|d-&gt;skblist
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|aoenet_xmit
c_func
(paren
id|sl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This ioctl implementation expects userland to have the device node&n; * permissions set so that only priviledged users can open an aoe&n; * block device directly.&n; */
r_static
r_int
DECL|function|aoeblk_ioctl
id|aoeblk_ioctl
c_func
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
id|uint
id|cmd
comma
id|ulong
id|arg
)paren
(brace
r_struct
id|aoedev
op_star
id|d
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|d
op_assign
id|inode-&gt;i_bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
(paren
id|d-&gt;flags
op_amp
id|DEVFL_UP
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;aoe: aoeblk_ioctl: disk not up&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_eq
id|HDIO_GETGEO
)paren
(brace
id|d-&gt;geo.start
op_assign
id|get_start_sect
c_func
(paren
id|inode-&gt;i_bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|copy_to_user
c_func
(paren
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
op_amp
id|d-&gt;geo
comma
r_sizeof
id|d-&gt;geo
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;aoe: aoeblk_ioctl: unknown ioctl %d&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|aoe_bdops
r_static
r_struct
id|block_device_operations
id|aoe_bdops
op_assign
(brace
dot
id|open
op_assign
id|aoeblk_open
comma
dot
id|release
op_assign
id|aoeblk_release
comma
dot
id|ioctl
op_assign
id|aoeblk_ioctl
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/* alloc_disk and add_disk can sleep */
r_void
DECL|function|aoeblk_gdalloc
id|aoeblk_gdalloc
c_func
(paren
r_void
op_star
id|vp
)paren
(brace
r_struct
id|aoedev
op_star
id|d
op_assign
id|vp
suffix:semicolon
r_struct
id|gendisk
op_star
id|gd
suffix:semicolon
id|ulong
id|flags
suffix:semicolon
id|gd
op_assign
id|alloc_disk
c_func
(paren
id|AOE_PARTITIONS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gd
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;aoe: aoeblk_gdalloc: cannot allocate disk &quot;
l_string|&quot;structure for %ld.%ld&bslash;n&quot;
comma
id|d-&gt;aoemajor
comma
id|d-&gt;aoeminor
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|d-&gt;flags
op_and_assign
op_complement
id|DEVFL_WORKON
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|d-&gt;bufpool
op_assign
id|mempool_create
c_func
(paren
id|MIN_BUFS
comma
id|mempool_alloc_slab
comma
id|mempool_free_slab
comma
id|buf_pool_cache
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;bufpool
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;aoe: aoeblk_gdalloc: cannot allocate bufpool &quot;
l_string|&quot;for %ld.%ld&bslash;n&quot;
comma
id|d-&gt;aoemajor
comma
id|d-&gt;aoeminor
)paren
suffix:semicolon
id|put_disk
c_func
(paren
id|gd
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|d-&gt;flags
op_and_assign
op_complement
id|DEVFL_WORKON
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|blk_queue_make_request
c_func
(paren
op_amp
id|d-&gt;blkq
comma
id|aoeblk_make_request
)paren
suffix:semicolon
id|gd-&gt;major
op_assign
id|AOE_MAJOR
suffix:semicolon
id|gd-&gt;first_minor
op_assign
id|d-&gt;sysminor
op_star
id|AOE_PARTITIONS
suffix:semicolon
id|gd-&gt;fops
op_assign
op_amp
id|aoe_bdops
suffix:semicolon
id|gd-&gt;private_data
op_assign
id|d
suffix:semicolon
id|gd-&gt;capacity
op_assign
id|d-&gt;ssize
suffix:semicolon
id|snprintf
c_func
(paren
id|gd-&gt;disk_name
comma
r_sizeof
id|gd-&gt;disk_name
comma
l_string|&quot;etherd/e%ld.%ld&quot;
comma
id|d-&gt;aoemajor
comma
id|d-&gt;aoeminor
)paren
suffix:semicolon
id|gd-&gt;queue
op_assign
op_amp
id|d-&gt;blkq
suffix:semicolon
id|d-&gt;gd
op_assign
id|gd
suffix:semicolon
id|d-&gt;flags
op_and_assign
op_complement
id|DEVFL_WORKON
suffix:semicolon
id|d-&gt;flags
op_or_assign
id|DEVFL_UP
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|d-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|add_disk
c_func
(paren
id|gd
)paren
suffix:semicolon
id|aoedisk_add_sysfs
c_func
(paren
id|d
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;aoe: %012llx e%lu.%lu v%04x has %llu &quot;
l_string|&quot;sectors&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|mac_addr
c_func
(paren
id|d-&gt;addr
)paren
comma
id|d-&gt;aoemajor
comma
id|d-&gt;aoeminor
comma
id|d-&gt;fw_ver
comma
(paren
r_int
r_int
)paren
id|d-&gt;ssize
)paren
suffix:semicolon
)brace
r_void
DECL|function|aoeblk_exit
id|aoeblk_exit
c_func
(paren
r_void
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|buf_pool_cache
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|aoeblk_init
id|aoeblk_init
c_func
(paren
r_void
)paren
(brace
id|buf_pool_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;aoe_bufs&quot;
comma
r_sizeof
(paren
r_struct
id|buf
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf_pool_cache
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
