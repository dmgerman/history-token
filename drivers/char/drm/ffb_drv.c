multiline_comment|/* $Id: ffb_drv.c,v 1.16 2001/10/18 16:00:24 davem Exp $&n; * ffb_drv.c: Creator/Creator3D direct rendering driver.&n; *&n; * Copyright (C) 2000 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;ffb.h&quot;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;ffb_drv.h&quot;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/shmparam.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/upa.h&gt;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;David S. Miller&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;ffb&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;Creator/Creator3D&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20000517&quot;
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;0
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;0
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;1
DECL|macro|DRIVER_FOPS
mdefine_line|#define DRIVER_FOPS&t;&t;&t;&t;&t;&t;&bslash;&n;static struct file_operations&t;DRM(fops) = {&t;&t;&t;&bslash;&n;&t;.owner   &t;&t;= THIS_MODULE,&t;&t;&t;&bslash;&n;&t;.open&t; &t;&t;= DRM(open),&t;&t;&t;&bslash;&n;&t;.flush&t; &t;&t;= DRM(flush),&t;&t;&t;&bslash;&n;&t;.release &t;&t;= DRM(release),&t;&t;&t;&bslash;&n;&t;.ioctl&t; &t;&t;= DRM(ioctl),&t;&t;&t;&bslash;&n;&t;.mmap&t; &t;&t;= DRM(mmap),&t;&t;&t;&bslash;&n;&t;.read&t; &t;&t;= DRM(read),&t;&t;&t;&bslash;&n;&t;.fasync&t; &t;&t;= DRM(fasync),&t;&t;&t;&bslash;&n;&t;.poll&t; &t;&t;= DRM(poll),&t;&t;&t;&bslash;&n;&t;.get_unmapped_area&t;= ffb_get_unmapped_area,&t;&t;&bslash;&n;}
DECL|macro|DRIVER_COUNT_CARDS
mdefine_line|#define DRIVER_COUNT_CARDS()&t;ffb_count_card_instances()
multiline_comment|/* Allocate private structure and fill it */
DECL|macro|DRIVER_PRESETUP
mdefine_line|#define DRIVER_PRESETUP()&t;do {&t;&t;&bslash;&n;&t;int _ret;&t;&t;&t;&t;&bslash;&n;&t;_ret = ffb_presetup(dev);&t;&t;&bslash;&n;&t;if (_ret != 0) return _ret;&t;&t;&bslash;&n;} while(0)
multiline_comment|/* Free private structure */
DECL|macro|DRIVER_PRETAKEDOWN
mdefine_line|#define DRIVER_PRETAKEDOWN()&t;do {&t;&t;&t;&t;&bslash;&n;&t;if (dev-&gt;dev_private) kfree(dev-&gt;dev_private);&t;&t;&bslash;&n;} while(0)
DECL|macro|DRIVER_POSTCLEANUP
mdefine_line|#define DRIVER_POSTCLEANUP()&t;do {&t;&t;&t;&t;&bslash;&n;&t;if (ffb_position != NULL) kfree(ffb_position);&t;&t;&bslash;&n;} while(0)
multiline_comment|/* We have to free up the rogue hw context state holding error or &n; * else we will leak it.&n; */
DECL|macro|DRIVER_RELEASE
mdefine_line|#define DRIVER_RELEASE()&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;ffb_dev_priv_t *fpriv = (ffb_dev_priv_t *) dev-&gt;dev_private;&t;&bslash;&n;&t;int context = _DRM_LOCKING_CONTEXT(dev-&gt;lock.hw_lock-&gt;lock);&t;&bslash;&n;&t;int idx;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;idx = context - 1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (fpriv &amp;&amp;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    context != DRM_KERNEL_CONTEXT &amp;&amp;&t;&t;&t;&t;&bslash;&n;&t;    fpriv-&gt;hw_state[idx] != NULL) {&t;&t;&t;&t;&bslash;&n;&t;&t;kfree(fpriv-&gt;hw_state[idx]);&t;&t;&t;&t;&bslash;&n;&t;&t;fpriv-&gt;hw_state[idx] = NULL;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
multiline_comment|/* For mmap customization */
DECL|macro|DRIVER_GET_MAP_OFS
mdefine_line|#define DRIVER_GET_MAP_OFS()&t;(map-&gt;offset &amp; 0xffffffff)
DECL|macro|DRIVER_GET_REG_OFS
mdefine_line|#define DRIVER_GET_REG_OFS()&t;ffb_get_reg_offset(dev)
DECL|struct|_ffb_position_t
r_typedef
r_struct
id|_ffb_position_t
(brace
DECL|member|node
r_int
id|node
suffix:semicolon
DECL|member|root
r_int
id|root
suffix:semicolon
DECL|typedef|ffb_position_t
)brace
id|ffb_position_t
suffix:semicolon
DECL|variable|ffb_position
r_static
id|ffb_position_t
op_star
id|ffb_position
suffix:semicolon
DECL|function|get_ffb_type
r_static
r_void
id|get_ffb_type
c_func
(paren
id|ffb_dev_priv_t
op_star
id|ffb_priv
comma
r_int
id|instance
)paren
(brace
r_volatile
r_int
r_char
op_star
id|strap_bits
suffix:semicolon
r_int
r_char
id|val
suffix:semicolon
id|strap_bits
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|ffb_priv-&gt;card_phys_base
op_plus
l_int|0x00200000UL
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t ask, you have to read the value twice for whatever&n;&t; * reason to get correct contents.&n;&t; */
id|val
op_assign
id|upa_readb
c_func
(paren
id|strap_bits
)paren
suffix:semicolon
id|val
op_assign
id|upa_readb
c_func
(paren
id|strap_bits
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|val
op_amp
l_int|0x78
)paren
(brace
r_case
(paren
l_int|0x0
op_lshift
l_int|5
)paren
op_or
(paren
l_int|0x0
op_lshift
l_int|3
)paren
suffix:colon
id|ffb_priv-&gt;ffb_type
op_assign
id|ffb1_prototype
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ffb%d: Detected FFB1 pre-FCS prototype&bslash;n&quot;
comma
id|instance
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|0x0
op_lshift
l_int|5
)paren
op_or
(paren
l_int|0x1
op_lshift
l_int|3
)paren
suffix:colon
id|ffb_priv-&gt;ffb_type
op_assign
id|ffb1_standard
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ffb%d: Detected FFB1&bslash;n&quot;
comma
id|instance
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|0x0
op_lshift
l_int|5
)paren
op_or
(paren
l_int|0x3
op_lshift
l_int|3
)paren
suffix:colon
id|ffb_priv-&gt;ffb_type
op_assign
id|ffb1_speedsort
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ffb%d: Detected FFB1-SpeedSort&bslash;n&quot;
comma
id|instance
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|0x1
op_lshift
l_int|5
)paren
op_or
(paren
l_int|0x0
op_lshift
l_int|3
)paren
suffix:colon
id|ffb_priv-&gt;ffb_type
op_assign
id|ffb2_prototype
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ffb%d: Detected FFB2/vertical pre-FCS prototype&bslash;n&quot;
comma
id|instance
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|0x1
op_lshift
l_int|5
)paren
op_or
(paren
l_int|0x1
op_lshift
l_int|3
)paren
suffix:colon
id|ffb_priv-&gt;ffb_type
op_assign
id|ffb2_vertical
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ffb%d: Detected FFB2/vertical&bslash;n&quot;
comma
id|instance
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|0x1
op_lshift
l_int|5
)paren
op_or
(paren
l_int|0x2
op_lshift
l_int|3
)paren
suffix:colon
id|ffb_priv-&gt;ffb_type
op_assign
id|ffb2_vertical_plus
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ffb%d: Detected FFB2+/vertical&bslash;n&quot;
comma
id|instance
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|0x2
op_lshift
l_int|5
)paren
op_or
(paren
l_int|0x0
op_lshift
l_int|3
)paren
suffix:colon
id|ffb_priv-&gt;ffb_type
op_assign
id|ffb2_horizontal
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ffb%d: Detected FFB2/horizontal&bslash;n&quot;
comma
id|instance
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|0x2
op_lshift
l_int|5
)paren
op_or
(paren
l_int|0x2
op_lshift
l_int|3
)paren
suffix:colon
id|ffb_priv-&gt;ffb_type
op_assign
id|ffb2_horizontal
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ffb%d: Detected FFB2+/horizontal&bslash;n&quot;
comma
id|instance
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ffb_priv-&gt;ffb_type
op_assign
id|ffb2_vertical
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ffb%d: Unknown boardID[%08x], assuming FFB2&bslash;n&quot;
comma
id|instance
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
)brace
DECL|function|ffb_apply_upa_parent_ranges
r_static
r_void
id|ffb_apply_upa_parent_ranges
c_func
(paren
r_int
id|parent
comma
r_struct
id|linux_prom64_registers
op_star
id|regs
)paren
(brace
r_struct
id|linux_prom64_ranges
id|ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|len
comma
id|i
suffix:semicolon
id|prom_getproperty
c_func
(paren
id|parent
comma
l_string|&quot;name&quot;
comma
id|name
comma
r_sizeof
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;upa&quot;
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|parent
comma
l_string|&quot;ranges&quot;
comma
(paren
r_void
op_star
)paren
id|ranges
comma
r_sizeof
(paren
id|ranges
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_return
suffix:semicolon
id|len
op_div_assign
r_sizeof
(paren
r_struct
id|linux_prom64_ranges
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|linux_prom64_ranges
op_star
id|rng
op_assign
op_amp
id|ranges
(braket
id|i
)braket
suffix:semicolon
id|u64
id|phys_addr
op_assign
id|regs-&gt;phys_addr
suffix:semicolon
r_if
c_cond
(paren
id|phys_addr
op_ge
id|rng-&gt;ot_child_base
op_logical_and
id|phys_addr
OL
(paren
id|rng-&gt;ot_child_base
op_plus
id|rng-&gt;or_size
)paren
)paren
(brace
id|regs-&gt;phys_addr
op_sub_assign
id|rng-&gt;ot_child_base
suffix:semicolon
id|regs-&gt;phys_addr
op_add_assign
id|rng-&gt;ot_parent_base
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
DECL|function|ffb_init_one
r_static
r_int
id|ffb_init_one
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|prom_node
comma
r_int
id|parent_node
comma
r_int
id|instance
)paren
(brace
r_struct
id|linux_prom64_registers
id|regs
(braket
l_int|2
op_star
id|PROMREG_MAX
)braket
suffix:semicolon
id|ffb_dev_priv_t
op_star
id|ffb_priv
op_assign
(paren
id|ffb_dev_priv_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ffb_priv-&gt;prom_node
op_assign
id|prom_node
suffix:semicolon
r_if
c_cond
(paren
id|prom_getproperty
c_func
(paren
id|ffb_priv-&gt;prom_node
comma
l_string|&quot;reg&quot;
comma
(paren
r_void
op_star
)paren
id|regs
comma
r_sizeof
(paren
id|regs
)paren
)paren
op_le
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ffb_apply_upa_parent_ranges
c_func
(paren
id|parent_node
comma
op_amp
id|regs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ffb_priv-&gt;card_phys_base
op_assign
id|regs
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
id|ffb_priv-&gt;regs
op_assign
(paren
id|ffb_fbcPtr
)paren
(paren
id|regs
(braket
l_int|0
)braket
dot
id|phys_addr
op_plus
l_int|0x00600000UL
)paren
suffix:semicolon
id|get_ffb_type
c_func
(paren
id|ffb_priv
comma
id|instance
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
id|FFB_MAX_CTXS
suffix:semicolon
id|i
op_increment
)paren
id|ffb_priv-&gt;hw_state
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ffb_count_siblings
r_static
r_int
id|__init
id|ffb_count_siblings
c_func
(paren
r_int
id|root
)paren
(brace
r_int
id|node
comma
id|child
comma
id|count
op_assign
l_int|0
suffix:semicolon
id|child
op_assign
id|prom_getchild
c_func
(paren
id|root
)paren
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|child
comma
l_string|&quot;SUNW,ffb&quot;
)paren
suffix:semicolon
id|node
suffix:semicolon
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|prom_getsibling
c_func
(paren
id|node
)paren
comma
l_string|&quot;SUNW,ffb&quot;
)paren
)paren
id|count
op_increment
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|ffb_scan_siblings
r_static
r_int
id|__init
id|ffb_scan_siblings
c_func
(paren
r_int
id|root
comma
r_int
id|instance
)paren
(brace
r_int
id|node
comma
id|child
suffix:semicolon
id|child
op_assign
id|prom_getchild
c_func
(paren
id|root
)paren
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|child
comma
l_string|&quot;SUNW,ffb&quot;
)paren
suffix:semicolon
id|node
suffix:semicolon
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|prom_getsibling
c_func
(paren
id|node
)paren
comma
l_string|&quot;SUNW,ffb&quot;
)paren
)paren
(brace
id|ffb_position
(braket
id|instance
)braket
dot
id|node
op_assign
id|node
suffix:semicolon
id|ffb_position
(braket
id|instance
)braket
dot
id|root
op_assign
id|root
suffix:semicolon
id|instance
op_increment
suffix:semicolon
)brace
r_return
id|instance
suffix:semicolon
)brace
r_static
r_int
id|ffb_presetup
c_func
(paren
id|drm_device_t
op_star
)paren
suffix:semicolon
DECL|function|ffb_count_card_instances
r_static
r_int
id|__init
id|ffb_count_card_instances
c_func
(paren
r_void
)paren
(brace
r_int
id|root
comma
id|total
comma
id|instance
suffix:semicolon
id|total
op_assign
id|ffb_count_siblings
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|root
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
r_for
c_loop
(paren
id|root
op_assign
id|prom_searchsiblings
c_func
(paren
id|root
comma
l_string|&quot;upa&quot;
)paren
suffix:semicolon
id|root
suffix:semicolon
id|root
op_assign
id|prom_searchsiblings
c_func
(paren
id|prom_getsibling
c_func
(paren
id|root
)paren
comma
l_string|&quot;upa&quot;
)paren
)paren
id|total
op_add_assign
id|ffb_count_siblings
c_func
(paren
id|root
)paren
suffix:semicolon
id|ffb_position
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ffb_position_t
)paren
op_star
id|total
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* Actual failure will be caught during ffb_presetup b/c we can&squot;t catch&n;&t; * it easily here.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ffb_position
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|instance
op_assign
id|ffb_scan_siblings
c_func
(paren
id|prom_root_node
comma
l_int|0
)paren
suffix:semicolon
id|root
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
r_for
c_loop
(paren
id|root
op_assign
id|prom_searchsiblings
c_func
(paren
id|root
comma
l_string|&quot;upa&quot;
)paren
suffix:semicolon
id|root
suffix:semicolon
id|root
op_assign
id|prom_searchsiblings
c_func
(paren
id|prom_getsibling
c_func
(paren
id|root
)paren
comma
l_string|&quot;upa&quot;
)paren
)paren
id|instance
op_assign
id|ffb_scan_siblings
c_func
(paren
id|root
comma
id|instance
)paren
suffix:semicolon
r_return
id|total
suffix:semicolon
)brace
DECL|function|ffb_find_map
r_static
id|drm_map_t
op_star
id|ffb_find_map
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|off
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
suffix:semicolon
id|drm_map_list_t
op_star
id|r_list
suffix:semicolon
r_struct
id|list_head
op_star
id|list
suffix:semicolon
id|drm_map_t
op_star
id|map
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
op_logical_or
(paren
id|dev
op_assign
id|priv-&gt;dev
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
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
r_int
r_int
id|uoff
suffix:semicolon
id|r_list
op_assign
(paren
id|drm_map_list_t
op_star
)paren
id|list
suffix:semicolon
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
r_continue
suffix:semicolon
id|uoff
op_assign
(paren
id|map-&gt;offset
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uoff
op_eq
id|off
)paren
r_return
id|map
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ffb_get_unmapped_area
r_static
r_int
r_int
id|ffb_get_unmapped_area
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|hint
comma
r_int
r_int
id|len
comma
r_int
r_int
id|pgoff
comma
r_int
r_int
id|flags
)paren
(brace
id|drm_map_t
op_star
id|map
op_assign
id|ffb_find_map
c_func
(paren
id|filp
comma
id|pgoff
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_int
r_int
id|addr
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
r_return
id|get_unmapped_area
c_func
(paren
l_int|NULL
comma
id|hint
comma
id|len
comma
id|pgoff
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;type
op_eq
id|_DRM_FRAME_BUFFER
op_logical_or
id|map-&gt;type
op_eq
id|_DRM_REGISTERS
)paren
(brace
macro_line|#ifdef HAVE_ARCH_FB_UNMAPPED_AREA
id|addr
op_assign
id|get_fb_unmapped_area
c_func
(paren
id|filp
comma
id|hint
comma
id|len
comma
id|pgoff
comma
id|flags
)paren
suffix:semicolon
macro_line|#else
id|addr
op_assign
id|get_unmapped_area
c_func
(paren
l_int|NULL
comma
id|hint
comma
id|len
comma
id|pgoff
comma
id|flags
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
id|map-&gt;type
op_eq
id|_DRM_SHM
op_logical_and
id|SHMLBA
OG
id|PAGE_SIZE
)paren
(brace
r_int
r_int
id|slack
op_assign
id|SHMLBA
op_minus
id|PAGE_SIZE
suffix:semicolon
id|addr
op_assign
id|get_unmapped_area
c_func
(paren
l_int|NULL
comma
id|hint
comma
id|len
op_plus
id|slack
comma
id|pgoff
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
(brace
r_int
r_int
id|kvirt
op_assign
(paren
r_int
r_int
)paren
id|map-&gt;handle
suffix:semicolon
r_if
c_cond
(paren
(paren
id|kvirt
op_amp
(paren
id|SHMLBA
op_minus
l_int|1
)paren
)paren
op_ne
(paren
id|addr
op_amp
(paren
id|SHMLBA
op_minus
l_int|1
)paren
)paren
)paren
(brace
r_int
r_int
id|koff
comma
id|aoff
suffix:semicolon
id|koff
op_assign
id|kvirt
op_amp
(paren
id|SHMLBA
op_minus
l_int|1
)paren
suffix:semicolon
id|aoff
op_assign
id|addr
op_amp
(paren
id|SHMLBA
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|koff
OL
id|aoff
)paren
id|koff
op_add_assign
id|SHMLBA
suffix:semicolon
id|addr
op_add_assign
(paren
id|koff
op_minus
id|aoff
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|addr
op_assign
id|get_unmapped_area
c_func
(paren
l_int|NULL
comma
id|hint
comma
id|len
comma
id|pgoff
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
id|addr
suffix:semicolon
)brace
DECL|function|ffb_get_reg_offset
r_static
r_int
r_int
id|ffb_get_reg_offset
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|ffb_dev_priv_t
op_star
id|ffb_priv
op_assign
(paren
id|ffb_dev_priv_t
op_star
)paren
id|dev-&gt;dev_private
suffix:semicolon
r_if
c_cond
(paren
id|ffb_priv
)paren
r_return
id|ffb_priv-&gt;card_phys_base
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#include &quot;drm_auth.h&quot;
macro_line|#include &quot;drm_bufs.h&quot;
macro_line|#include &quot;drm_dma.h&quot;
macro_line|#include &quot;drm_drawable.h&quot;
macro_line|#include &quot;drm_drv.h&quot;
multiline_comment|/* This functions must be here since it references DRM(numdevs)&n; * which drm_drv.h declares.&n; */
DECL|function|ffb_presetup
r_static
r_int
id|ffb_presetup
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
id|ffb_dev_priv_t
op_star
id|ffb_priv
suffix:semicolon
id|drm_device_t
op_star
id|temp_dev
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Check for the case where no device was found. */
r_if
c_cond
(paren
id|ffb_position
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Find our instance number by finding our device in dev structure */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DRM
c_func
(paren
id|numdevs
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|temp_dev
op_assign
op_amp
(paren
id|DRM
c_func
(paren
id|device
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp_dev
op_eq
id|dev
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
id|DRM
c_func
(paren
id|numdevs
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ffb_priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|ffb_dev_priv_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ffb_priv
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|ffb_priv
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ffb_priv
)paren
)paren
suffix:semicolon
id|dev-&gt;dev_private
op_assign
id|ffb_priv
suffix:semicolon
id|ret
op_assign
id|ffb_init_one
c_func
(paren
id|dev
comma
id|ffb_position
(braket
id|i
)braket
dot
id|node
comma
id|ffb_position
(braket
id|i
)braket
dot
id|root
comma
id|i
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifndef MODULE
multiline_comment|/* DRM(options) is called by the kernel to parse command-line options&n; * passed via the boot-loader (e.g., LILO).  It calls the insmod option&n; * routine, drm_parse_drm.&n; */
multiline_comment|/* JH- We have to hand expand the string ourselves because of the cpp.  If&n; * anyone can think of a way that we can fit into the __setup macro without&n; * changing it, then please send the solution my way.&n; */
DECL|function|ffb_options
r_static
r_int
id|__init
id|ffb_options
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|DRM
c_func
(paren
id|parse_options
)paren
(paren
id|str
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
id|DRIVER_NAME
l_string|&quot;=&quot;
comma
id|ffb_options
)paren
suffix:semicolon
macro_line|#endif
macro_line|#include &quot;drm_fops.h&quot;
macro_line|#include &quot;drm_init.h&quot;
macro_line|#include &quot;drm_ioctl.h&quot;
macro_line|#include &quot;drm_lock.h&quot;
macro_line|#include &quot;drm_memory.h&quot;
macro_line|#include &quot;drm_proc.h&quot;
macro_line|#include &quot;drm_vm.h&quot;
macro_line|#include &quot;drm_stub.h&quot;
eof
