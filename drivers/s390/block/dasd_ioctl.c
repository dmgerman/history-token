multiline_comment|/*&n; * File...........: linux/drivers/s390/block/dasd_ioctl.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; *&t;&t;    Horst Hummel &lt;Horst.Hummel@de.ibm.com&gt;&n; *&t;&t;    Carsten Otte &lt;Cotte@de.ibm.com&gt;&n; *&t;&t;    Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999-2001&n; *&n; * i/o controls for the dasd driver.&n; *&n; * 05/04/02 split from dasd.c, code restructuring.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* This is ugly... */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;dasd_ioctl:&quot;
macro_line|#include &quot;dasd_int.h&quot;
multiline_comment|/*&n; * SECTION: ioctl functions.&n; */
DECL|variable|dasd_ioctl_list
r_static
r_struct
id|list_head
id|dasd_ioctl_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|dasd_ioctl_list
)paren
suffix:semicolon
multiline_comment|/*&n; * Find the ioctl with number no.&n; */
r_static
id|dasd_ioctl_list_t
op_star
DECL|function|dasd_find_ioctl
id|dasd_find_ioctl
c_func
(paren
r_int
id|no
)paren
(brace
r_struct
id|list_head
op_star
id|curr
suffix:semicolon
id|list_for_each
(paren
id|curr
comma
op_amp
id|dasd_ioctl_list
)paren
(brace
r_if
c_cond
(paren
id|list_entry
(paren
id|curr
comma
id|dasd_ioctl_list_t
comma
id|list
)paren
op_member_access_from_pointer
id|no
op_eq
id|no
)paren
(brace
r_return
id|list_entry
(paren
id|curr
comma
id|dasd_ioctl_list_t
comma
id|list
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Register ioctl with number no.&n; */
r_int
DECL|function|dasd_ioctl_no_register
id|dasd_ioctl_no_register
c_func
(paren
r_struct
id|module
op_star
id|owner
comma
r_int
id|no
comma
id|dasd_ioctl_fn_t
id|handler
)paren
(brace
id|dasd_ioctl_list_t
op_star
r_new
suffix:semicolon
r_if
c_cond
(paren
id|dasd_find_ioctl
c_func
(paren
id|no
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_new
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|dasd_ioctl_list_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_new
op_member_access_from_pointer
id|owner
op_assign
id|owner
suffix:semicolon
r_new
op_member_access_from_pointer
id|no
op_assign
id|no
suffix:semicolon
r_new
op_member_access_from_pointer
id|handler
op_assign
id|handler
suffix:semicolon
id|list_add
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|list
comma
op_amp
id|dasd_ioctl_list
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Deregister ioctl with number no.&n; */
r_int
DECL|function|dasd_ioctl_no_unregister
id|dasd_ioctl_no_unregister
c_func
(paren
r_struct
id|module
op_star
id|owner
comma
r_int
id|no
comma
id|dasd_ioctl_fn_t
id|handler
)paren
(brace
id|dasd_ioctl_list_t
op_star
id|old
op_assign
id|dasd_find_ioctl
c_func
(paren
id|no
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|old-&gt;no
op_ne
id|no
op_logical_or
id|old-&gt;handler
op_ne
id|handler
op_logical_or
id|owner
op_ne
id|old-&gt;owner
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|old-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|old
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|dasd_ioctl
id|dasd_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inp
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|no
comma
r_int
r_int
id|data
)paren
(brace
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|dasd_device_t
op_star
id|device
suffix:semicolon
id|dasd_ioctl_list_t
op_star
id|ioctl
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_const
r_char
op_star
id|dir
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|inp
)paren
op_logical_or
id|kdev_none
c_func
(paren
id|inp-&gt;i_rdev
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|_IOC_DIR
c_func
(paren
id|no
)paren
op_ne
id|_IOC_NONE
)paren
op_logical_and
(paren
id|data
op_eq
l_int|0
)paren
)paren
(brace
id|PRINT_DEBUG
c_func
(paren
l_string|&quot;empty data ptr&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|bdev
op_assign
id|bdget
c_func
(paren
id|kdev_t_to_nr
c_func
(paren
id|inp-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|device
op_assign
(paren
id|devmap
op_ne
l_int|NULL
)paren
ques
c_cond
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:colon
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;No device registered as device %s&quot;
comma
id|bdevname
c_func
(paren
id|bdev
)paren
)paren
suffix:semicolon
id|bdput
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dir
op_assign
id|_IOC_DIR
(paren
id|no
)paren
op_eq
id|_IOC_NONE
ques
c_cond
l_string|&quot;0&quot;
suffix:colon
id|_IOC_DIR
(paren
id|no
)paren
op_eq
id|_IOC_READ
ques
c_cond
l_string|&quot;r&quot;
suffix:colon
id|_IOC_DIR
(paren
id|no
)paren
op_eq
id|_IOC_WRITE
ques
c_cond
l_string|&quot;w&quot;
suffix:colon
id|_IOC_DIR
(paren
id|no
)paren
op_eq
(paren
id|_IOC_READ
op_or
id|_IOC_WRITE
)paren
ques
c_cond
l_string|&quot;rw&quot;
suffix:colon
l_string|&quot;u&quot;
suffix:semicolon
id|DBF_DEV_EVENT
c_func
(paren
id|DBF_DEBUG
comma
id|device
comma
l_string|&quot;ioctl 0x%08x %s&squot;0x%x&squot;%d(%d) with data %8lx&quot;
comma
id|no
comma
id|dir
comma
id|_IOC_TYPE
c_func
(paren
id|no
)paren
comma
id|_IOC_NR
c_func
(paren
id|no
)paren
comma
id|_IOC_SIZE
c_func
(paren
id|no
)paren
comma
id|data
)paren
suffix:semicolon
multiline_comment|/* Search for ioctl no in the ioctl list. */
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|dasd_ioctl_list
)paren
(brace
id|ioctl
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|dasd_ioctl_list_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ioctl-&gt;no
op_eq
id|no
)paren
(brace
multiline_comment|/* Found a matching ioctl. Call it. */
r_if
c_cond
(paren
id|ioctl-&gt;owner
)paren
(brace
r_if
c_cond
(paren
id|try_inc_mod_count
c_func
(paren
id|ioctl-&gt;owner
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
id|rc
op_assign
id|ioctl
op_member_access_from_pointer
id|handler
c_func
(paren
id|bdev
comma
id|no
comma
id|data
)paren
suffix:semicolon
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|ioctl-&gt;owner
)paren
suffix:semicolon
)brace
r_else
id|rc
op_assign
id|ioctl
op_member_access_from_pointer
id|handler
c_func
(paren
id|bdev
comma
id|no
comma
id|data
)paren
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
id|bdput
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
)brace
multiline_comment|/* No ioctl with number no. */
id|DBF_DEV_EVENT
c_func
(paren
id|DBF_INFO
comma
id|device
comma
l_string|&quot;unknown ioctl 0x%08x=%s&squot;0x%x&squot;%d(%d) data %8lx&quot;
comma
id|no
comma
id|dir
comma
id|_IOC_TYPE
c_func
(paren
id|no
)paren
comma
id|_IOC_NR
c_func
(paren
id|no
)paren
comma
id|_IOC_SIZE
c_func
(paren
id|no
)paren
comma
id|data
)paren
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
id|bdput
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_ioctl_api_version
id|dasd_ioctl_api_version
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
r_int
id|ver
op_assign
id|DASD_API_VERSION
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|ver
comma
(paren
r_int
op_star
)paren
id|args
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Enable device.&n; */
r_static
r_int
DECL|function|dasd_ioctl_enable
id|dasd_ioctl_enable
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|dasd_device_t
op_star
id|device
suffix:semicolon
r_int
id|devno
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|device
op_assign
(paren
id|devmap
op_ne
l_int|NULL
)paren
ques
c_cond
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:colon
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|device
)paren
suffix:semicolon
id|devno
op_assign
id|device-&gt;devinfo.devno
suffix:semicolon
id|dasd_enable_devices
c_func
(paren
id|devno
comma
id|devno
)paren
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Disable device.&n; */
r_static
r_int
DECL|function|dasd_ioctl_disable
id|dasd_ioctl_disable
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|dasd_device_t
op_star
id|device
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|device
op_assign
(paren
id|devmap
op_ne
l_int|NULL
)paren
ques
c_cond
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:colon
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|device
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Man this is sick. We don&squot;t do a real disable but only downgrade&n;&t; * the device to DASD_STATE_BASIC. The reason is that dasdfmt uses&n;&t; * BIODASDDISABLE to disable accesses to the device via the block&n;&t; * device layer but it still wants to do i/o on the device by&n;&t; * using the BIODASDFMT ioctl. Therefore the correct state for the&n;&t; * device is DASD_STATE_BASIC that allows to do basic i/o.&n;&t; */
id|dasd_set_target_state
c_func
(paren
id|device
comma
id|DASD_STATE_BASIC
)paren
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * performs formatting of _device_ according to _fdata_&n; * Note: The discipline&squot;s format_function is assumed to deliver formatting&n; * commands to format a single unit of the device. In terms of the ECKD&n; * devices this means CCWs are generated to format a single track.&n; */
r_static
r_int
DECL|function|dasd_format
id|dasd_format
c_func
(paren
id|dasd_device_t
op_star
id|device
comma
id|format_data_t
op_star
id|fdata
)paren
(brace
id|dasd_ccw_req_t
op_star
id|cqr
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;discipline-&gt;format_device
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|device-&gt;open_count
)paren
OG
l_int|1
)paren
(brace
id|DEV_MESSAGE
c_func
(paren
id|KERN_WARNING
comma
id|device
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;dasd_format: device is open! &quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|DBF_DEV_EVENT
c_func
(paren
id|DBF_NOTICE
comma
id|device
comma
l_string|&quot;formatting units %d to %d (%d B blocks) flags %d&quot;
comma
id|fdata-&gt;start_unit
comma
id|fdata-&gt;stop_unit
comma
id|fdata-&gt;blksize
comma
id|fdata-&gt;intensity
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fdata-&gt;start_unit
op_le
id|fdata-&gt;stop_unit
)paren
(brace
id|cqr
op_assign
id|device-&gt;discipline
op_member_access_from_pointer
id|format_device
c_func
(paren
id|device
comma
id|fdata
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|cqr
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|cqr
)paren
suffix:semicolon
id|rc
op_assign
id|dasd_sleep_on_interruptible
c_func
(paren
id|cqr
)paren
suffix:semicolon
id|dasd_sfree_request
c_func
(paren
id|cqr
comma
id|cqr-&gt;device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_if
c_cond
(paren
id|rc
op_ne
op_minus
id|ERESTARTSYS
)paren
id|DEV_MESSAGE
c_func
(paren
id|KERN_ERR
comma
id|device
comma
l_string|&quot; Formatting of unit %d failed &quot;
l_string|&quot;with rc = %d&quot;
comma
id|fdata-&gt;start_unit
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|fdata-&gt;start_unit
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Format device.&n; */
r_static
r_int
DECL|function|dasd_ioctl_format
id|dasd_ioctl_format
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|dasd_device_t
op_star
id|device
suffix:semicolon
id|format_data_t
id|fdata
suffix:semicolon
r_int
id|partn
comma
id|rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|args
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* fdata == NULL is no longer a valid arg to dasd_format ! */
id|partn
op_assign
id|MINOR
c_func
(paren
id|bdev-&gt;bd_dev
)paren
op_amp
id|DASD_PARTN_MASK
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|device
op_assign
(paren
id|devmap
op_ne
l_int|NULL
)paren
ques
c_cond
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:colon
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|device
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|devmap-&gt;features
op_amp
id|DASD_FEATURE_READONLY
)paren
id|rc
op_assign
op_minus
id|EROFS
suffix:semicolon
r_else
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|fdata
comma
(paren
r_void
op_star
)paren
id|args
comma
r_sizeof
(paren
id|format_data_t
)paren
)paren
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_else
r_if
c_cond
(paren
id|partn
op_ne
l_int|0
)paren
(brace
id|DEV_MESSAGE
c_func
(paren
id|KERN_WARNING
comma
id|device
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;Cannot low-level format a partition&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
id|rc
op_assign
id|dasd_format
c_func
(paren
id|device
comma
op_amp
id|fdata
)paren
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DASD_PROFILE
multiline_comment|/*&n; * Reset device profile information&n; */
r_static
r_int
DECL|function|dasd_ioctl_reset_profile
id|dasd_ioctl_reset_profile
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|dasd_device_t
op_star
id|device
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|device
op_assign
(paren
id|devmap
op_ne
l_int|NULL
)paren
ques
c_cond
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:colon
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|device
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|device-&gt;profile
comma
l_int|0
comma
r_sizeof
(paren
id|dasd_profile_info_t
)paren
)paren
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return device profile information&n; */
r_static
r_int
DECL|function|dasd_ioctl_read_profile
id|dasd_ioctl_read_profile
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|dasd_device_t
op_star
id|device
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|device
op_assign
(paren
id|devmap
op_ne
l_int|NULL
)paren
ques
c_cond
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:colon
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|device
)paren
suffix:semicolon
id|rc
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
r_int
op_star
)paren
id|args
comma
(paren
r_int
op_star
)paren
op_amp
id|device-&gt;profile
comma
r_sizeof
(paren
id|dasd_profile_info_t
)paren
)paren
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
macro_line|#else
r_static
r_int
DECL|function|dasd_ioctl_reset_profile
id|dasd_ioctl_reset_profile
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_ioctl_read_profile
id|dasd_ioctl_read_profile
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Return dasd information. Used for BIODASDINFO and BIODASDINFO2.&n; */
r_static
r_int
DECL|function|dasd_ioctl_information
id|dasd_ioctl_information
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|dasd_device_t
op_star
id|device
suffix:semicolon
id|dasd_information2_t
op_star
id|dasd_info
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|device
op_assign
(paren
id|devmap
op_ne
l_int|NULL
)paren
ques
c_cond
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:colon
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device-&gt;discipline-&gt;fill_info
)paren
(brace
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dasd_info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|dasd_information2_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dasd_info
op_eq
l_int|NULL
)paren
(brace
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|rc
op_assign
id|device-&gt;discipline
op_member_access_from_pointer
id|fill_info
c_func
(paren
id|device
comma
id|dasd_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dasd_info
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|dasd_info-&gt;devno
op_assign
id|device-&gt;devinfo.devno
suffix:semicolon
id|dasd_info-&gt;schid
op_assign
id|device-&gt;devinfo.irq
suffix:semicolon
id|dasd_info-&gt;cu_type
op_assign
id|device-&gt;devinfo.sid_data.cu_type
suffix:semicolon
id|dasd_info-&gt;cu_model
op_assign
id|device-&gt;devinfo.sid_data.cu_model
suffix:semicolon
id|dasd_info-&gt;dev_type
op_assign
id|device-&gt;devinfo.sid_data.dev_type
suffix:semicolon
id|dasd_info-&gt;dev_model
op_assign
id|device-&gt;devinfo.sid_data.dev_model
suffix:semicolon
id|dasd_info-&gt;open_count
op_assign
id|atomic_read
c_func
(paren
op_amp
id|device-&gt;open_count
)paren
suffix:semicolon
id|dasd_info-&gt;status
op_assign
id|device-&gt;state
suffix:semicolon
multiline_comment|/*&n;&t; * check if device is really formatted&n;&t; * LDL / CDL was returned by &squot;fill_info&squot;&n;&t; */
r_if
c_cond
(paren
(paren
id|device-&gt;state
OL
id|DASD_STATE_READY
)paren
op_logical_or
(paren
id|dasd_check_blocksize
c_func
(paren
id|device-&gt;bp_block
)paren
)paren
)paren
id|dasd_info-&gt;format
op_assign
id|DASD_FORMAT_NONE
suffix:semicolon
id|dasd_info-&gt;features
op_assign
id|devmap-&gt;features
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;discipline
)paren
id|memcpy
c_func
(paren
id|dasd_info-&gt;type
comma
id|device-&gt;discipline-&gt;name
comma
l_int|4
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|dasd_info-&gt;type
comma
l_string|&quot;none&quot;
comma
l_int|4
)paren
suffix:semicolon
id|dasd_info-&gt;req_queue_len
op_assign
l_int|0
suffix:semicolon
id|dasd_info-&gt;chanq_len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;request_queue-&gt;request_fn
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
macro_line|#ifdef DASD_EXTENDED_PROFILING
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|device-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|device-&gt;request_queue-&gt;queue_head
)paren
id|dasd_info-&gt;req_queue_len
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|device-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* DASD_EXTENDED_PROFILING */
id|spin_lock_irqsave
c_func
(paren
id|get_irq_lock
c_func
(paren
id|device-&gt;devinfo.irq
)paren
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|device-&gt;ccw_queue
)paren
id|dasd_info-&gt;chanq_len
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|get_irq_lock
c_func
(paren
id|device-&gt;devinfo.irq
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
id|rc
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
r_int
op_star
)paren
id|args
comma
(paren
r_int
op_star
)paren
id|dasd_info
comma
(paren
(paren
id|no
op_eq
(paren
r_int
r_int
)paren
id|BIODASDINFO2
)paren
ques
c_cond
r_sizeof
(paren
id|dasd_information2_t
)paren
suffix:colon
r_sizeof
(paren
id|dasd_information_t
)paren
)paren
)paren
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dasd_info
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Set read only&n; */
r_static
r_int
DECL|function|dasd_ioctl_set_ro
id|dasd_ioctl_set_ro
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|dasd_device_t
op_star
id|device
suffix:semicolon
r_int
id|intval
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|bdev-&gt;bd_dev
)paren
op_amp
id|DASD_PARTN_MASK
)paren
singleline_comment|// ro setting is not allowed for partitions
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|intval
comma
(paren
r_int
op_star
)paren
id|args
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|device
op_assign
(paren
id|devmap
op_ne
l_int|NULL
)paren
ques
c_cond
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:colon
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intval
)paren
id|devmap-&gt;features
op_or_assign
id|DASD_FEATURE_READONLY
suffix:semicolon
r_else
id|devmap-&gt;features
op_and_assign
op_complement
id|DASD_FEATURE_READONLY
suffix:semicolon
id|set_disk_ro
c_func
(paren
id|bdev-&gt;bd_disk
comma
id|intval
)paren
suffix:semicolon
id|device-&gt;ro_flag
op_assign
id|intval
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return disk geometry.&n; */
r_static
r_int
DECL|function|dasd_ioctl_getgeo
id|dasd_ioctl_getgeo
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|no
comma
r_int
id|args
)paren
(brace
r_struct
id|hd_geometry
id|geo
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|dasd_device_t
op_star
id|device
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|device
op_assign
(paren
id|devmap
op_ne
l_int|NULL
)paren
ques
c_cond
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:colon
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|device
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|device
op_ne
l_int|NULL
op_logical_and
id|device-&gt;discipline
op_ne
l_int|NULL
op_logical_and
id|device-&gt;discipline-&gt;fill_geometry
op_ne
l_int|NULL
)paren
(brace
id|device-&gt;discipline
op_member_access_from_pointer
id|fill_geometry
c_func
(paren
id|device
comma
op_amp
id|geo
)paren
suffix:semicolon
id|geo.start
op_assign
id|get_start_sect
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|hd_geometry
op_star
)paren
id|args
comma
op_amp
id|geo
comma
r_sizeof
(paren
r_struct
id|hd_geometry
)paren
)paren
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * List of static ioctls.&n; */
DECL|member|no
DECL|member|fn
DECL|variable|dasd_ioctls
r_static
r_struct
(brace
r_int
id|no
suffix:semicolon
id|dasd_ioctl_fn_t
id|fn
suffix:semicolon
)brace
id|dasd_ioctls
(braket
)braket
op_assign
(brace
(brace
id|BIODASDDISABLE
comma
id|dasd_ioctl_disable
)brace
comma
(brace
id|BIODASDENABLE
comma
id|dasd_ioctl_enable
)brace
comma
(brace
id|BIODASDFMT
comma
id|dasd_ioctl_format
)brace
comma
(brace
id|BIODASDINFO
comma
id|dasd_ioctl_information
)brace
comma
(brace
id|BIODASDINFO2
comma
id|dasd_ioctl_information
)brace
comma
(brace
id|BIODASDPRRD
comma
id|dasd_ioctl_read_profile
)brace
comma
(brace
id|BIODASDPRRST
comma
id|dasd_ioctl_reset_profile
)brace
comma
(brace
id|BLKROSET
comma
id|dasd_ioctl_set_ro
)brace
comma
(brace
id|DASDAPIVER
comma
id|dasd_ioctl_api_version
)brace
comma
(brace
id|HDIO_GETGEO
comma
id|dasd_ioctl_getgeo
)brace
comma
(brace
op_minus
l_int|1
comma
l_int|NULL
)brace
)brace
suffix:semicolon
r_int
DECL|function|dasd_ioctl_init
id|dasd_ioctl_init
c_func
(paren
r_void
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
id|dasd_ioctls
(braket
id|i
)braket
dot
id|no
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
id|dasd_ioctl_no_register
c_func
(paren
l_int|NULL
comma
id|dasd_ioctls
(braket
id|i
)braket
dot
id|no
comma
id|dasd_ioctls
(braket
id|i
)braket
dot
id|fn
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|dasd_ioctl_exit
id|dasd_ioctl_exit
c_func
(paren
r_void
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
id|dasd_ioctls
(braket
id|i
)braket
dot
id|no
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
id|dasd_ioctl_no_unregister
c_func
(paren
l_int|NULL
comma
id|dasd_ioctls
(braket
id|i
)braket
dot
id|no
comma
id|dasd_ioctls
(braket
id|i
)braket
dot
id|fn
)paren
suffix:semicolon
)brace
DECL|variable|dasd_ioctl_no_register
id|EXPORT_SYMBOL
c_func
(paren
id|dasd_ioctl_no_register
)paren
suffix:semicolon
DECL|variable|dasd_ioctl_no_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|dasd_ioctl_no_unregister
)paren
suffix:semicolon
eof
