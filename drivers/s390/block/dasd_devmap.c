multiline_comment|/*&n; * File...........: linux/drivers/s390/block/dasd_devmap.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; *&t;&t;    Horst Hummel &lt;Horst.Hummel@de.ibm.com&gt;&n; *&t;&t;    Carsten Otte &lt;Cotte@de.ibm.com&gt;&n; *&t;&t;    Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999-2001&n; *&n; * Device mapping and dasd= parameter parsing functions. All devmap&n; * functions may not be called from interrupt context. In particular&n; * dasd_get_device is a no-no from interrupt context.&n; *&n; * $Revision: 1.34 $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* This is ugly... */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;dasd_devmap:&quot;
macro_line|#include &quot;dasd_int.h&quot;
DECL|variable|dasd_page_cache
id|kmem_cache_t
op_star
id|dasd_page_cache
suffix:semicolon
DECL|variable|dasd_page_cache
id|EXPORT_SYMBOL
c_func
(paren
id|dasd_page_cache
)paren
suffix:semicolon
multiline_comment|/*&n; * dasd_devmap_t is used to store the features and the relation&n; * between device number and device index. To find a dasd_devmap_t&n; * that corresponds to a device number of a device index each&n; * dasd_devmap_t is added to two linked lists, one to search by&n; * the device number and one to search by the device index. As&n; * soon as big minor numbers are available the device index list&n; * can be removed since the device number will then be identical&n; * to the device index.&n; */
DECL|struct|dasd_devmap
r_struct
id|dasd_devmap
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|bus_id
r_char
id|bus_id
(braket
id|BUS_ID_SIZE
)braket
suffix:semicolon
DECL|member|devindex
r_int
r_int
id|devindex
suffix:semicolon
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
DECL|member|device
r_struct
id|dasd_device
op_star
id|device
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Parameter parsing functions for dasd= parameter. The syntax is:&n; *   &lt;devno&gt;&t;&t;: (0x)?[0-9a-fA-F]+&n; *   &lt;busid&gt;&t;&t;: [0-0a-f]&bslash;.[0-9a-f]&bslash;.(0x)?[0-9a-fA-F]+&n; *   &lt;feature&gt;&t;&t;: ro&n; *   &lt;feature_list&gt;&t;: &bslash;(&lt;feature&gt;(:&lt;feature&gt;)*&bslash;)&n; *   &lt;devno-range&gt;&t;: &lt;devno&gt;(-&lt;devno&gt;)?&lt;feature_list&gt;?&n; *   &lt;busid-range&gt;&t;: &lt;busid&gt;(-&lt;busid&gt;)?&lt;feature_list&gt;?&n; *   &lt;devices&gt;&t;&t;: &lt;devno-range&gt;|&lt;busid-range&gt;&n; *   &lt;dasd_module&gt;&t;: dasd_diag_mod|dasd_eckd_mod|dasd_fba_mod&n; *&n; *   &lt;dasd&gt;&t;&t;: autodetect|probeonly|&lt;devices&gt;(,&lt;devices&gt;)*&n; */
DECL|variable|dasd_probeonly
r_int
id|dasd_probeonly
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* is true, when probeonly mode is active */
DECL|variable|dasd_autodetect
r_int
id|dasd_autodetect
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* is true, when autodetection is active */
multiline_comment|/*&n; * char *dasd[] is intended to hold the ranges supplied by the dasd= statement&n; * it is named &squot;dasd&squot; to directly be filled by insmod with the comma separated&n; * strings when running as a module.&n; */
DECL|variable|dasd
r_static
r_char
op_star
id|dasd
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/*&n; * Single spinlock to protect devmap structures and lists.&n; */
DECL|variable|dasd_devmap_lock
r_static
id|spinlock_t
id|dasd_devmap_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Hash lists for devmap structures.&n; */
DECL|variable|dasd_hashlists
r_static
r_struct
id|list_head
id|dasd_hashlists
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|dasd_max_devindex
r_int
id|dasd_max_devindex
suffix:semicolon
r_static
r_struct
id|dasd_devmap
op_star
id|dasd_add_busid
c_func
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_int
DECL|function|dasd_hash_busid
id|dasd_hash_busid
c_func
(paren
r_char
op_star
id|bus_id
)paren
(brace
r_int
id|hash
comma
id|i
suffix:semicolon
id|hash
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|BUS_ID_SIZE
)paren
op_logical_and
op_star
id|bus_id
suffix:semicolon
id|i
op_increment
comma
id|bus_id
op_increment
)paren
id|hash
op_add_assign
op_star
id|bus_id
suffix:semicolon
r_return
id|hash
op_amp
l_int|0xff
suffix:semicolon
)brace
macro_line|#ifndef MODULE
multiline_comment|/*&n; * The parameter parsing functions for builtin-drivers are called&n; * before kmalloc works. Store the pointers to the parameters strings&n; * into dasd[] for later processing.&n; */
r_static
r_int
id|__init
DECL|function|dasd_call_setup
id|dasd_call_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_static
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|256
)paren
id|dasd
(braket
id|count
op_increment
)braket
op_assign
id|str
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
(paren
l_string|&quot;dasd=&quot;
comma
id|dasd_call_setup
)paren
suffix:semicolon
macro_line|#endif&t;/* #ifndef MODULE */
multiline_comment|/*&n; * Read a device busid/devno from a string.&n; */
r_static
r_inline
r_int
DECL|function|dasd_busid
id|dasd_busid
c_func
(paren
r_char
op_star
op_star
id|str
comma
r_int
op_star
id|id0
comma
r_int
op_star
id|id1
comma
r_int
op_star
id|devno
)paren
(brace
r_int
id|val
comma
id|old_style
suffix:semicolon
multiline_comment|/* check for leading &squot;0x&squot; */
id|old_style
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_eq
l_char|&squot;0&squot;
op_logical_and
(paren
op_star
id|str
)paren
(braket
l_int|1
)braket
op_eq
l_char|&squot;x&squot;
)paren
(brace
op_star
id|str
op_add_assign
l_int|2
suffix:semicolon
id|old_style
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|isxdigit
c_func
(paren
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
)paren
)paren
multiline_comment|/* We require at least one hex digit */
r_return
op_minus
id|EINVAL
suffix:semicolon
id|val
op_assign
id|simple_strtoul
c_func
(paren
op_star
id|str
comma
id|str
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_style
op_logical_or
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
(brace
op_star
id|id0
op_assign
op_star
id|id1
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|val
template_param
l_int|0xffff
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|devno
op_assign
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* New style x.y.z busid */
r_if
c_cond
(paren
id|val
template_param
l_int|0xff
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|id0
op_assign
id|val
suffix:semicolon
(paren
op_star
id|str
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isxdigit
c_func
(paren
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
)paren
)paren
multiline_comment|/* We require at least one hex digit */
r_return
op_minus
id|EINVAL
suffix:semicolon
id|val
op_assign
id|simple_strtoul
c_func
(paren
op_star
id|str
comma
id|str
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
template_param
l_int|0xff
op_logical_or
(paren
op_star
id|str
)paren
op_increment
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|id1
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isxdigit
c_func
(paren
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
)paren
)paren
multiline_comment|/* We require at least one hex digit */
r_return
op_minus
id|EINVAL
suffix:semicolon
id|val
op_assign
id|simple_strtoul
c_func
(paren
op_star
id|str
comma
id|str
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
template_param
l_int|0xffff
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|devno
op_assign
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Read colon separated list of dasd features. Currently there is&n; * only one: &quot;ro&quot; for read-only devices. The default feature set&n; * is empty (value 0).&n; */
r_static
r_inline
r_int
DECL|function|dasd_feature_list
id|dasd_feature_list
c_func
(paren
r_char
op_star
id|str
comma
r_char
op_star
op_star
id|endp
)paren
(brace
r_int
id|features
comma
id|len
comma
id|rc
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_ne
l_char|&squot;(&squot;
)paren
(brace
op_star
id|endp
op_assign
id|str
suffix:semicolon
r_return
id|DASD_FEATURE_DEFAULT
suffix:semicolon
)brace
id|str
op_increment
suffix:semicolon
id|features
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
id|str
(braket
id|len
)braket
op_logical_and
id|str
(braket
id|len
)braket
op_ne
l_char|&squot;:&squot;
op_logical_and
id|str
(braket
id|len
)braket
op_ne
l_char|&squot;)&squot;
suffix:semicolon
id|len
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|2
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;ro&quot;
comma
l_int|2
)paren
)paren
id|features
op_or_assign
id|DASD_FEATURE_READONLY
suffix:semicolon
r_else
r_if
c_cond
(paren
id|len
op_eq
l_int|4
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;diag&quot;
comma
l_int|4
)paren
)paren
id|features
op_or_assign
id|DASD_FEATURE_USEDIAG
suffix:semicolon
r_else
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;unsupported feature: %*s, &quot;
l_string|&quot;ignoring setting&quot;
comma
id|len
comma
id|str
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|str
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_ne
l_char|&squot;:&squot;
)paren
r_break
suffix:semicolon
id|str
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|str
op_ne
l_char|&squot;)&squot;
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;missing &squot;)&squot; in dasd parameter string&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
id|str
op_increment
suffix:semicolon
op_star
id|endp
op_assign
id|str
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_return
id|rc
suffix:semicolon
r_return
id|features
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to match the first element on the comma separated parse string&n; * with one of the known keywords. If a keyword is found, take the approprate&n; * action and return a pointer to the residual string. If the first element&n; * could not be matched to any keyword then return an error code.&n; */
r_static
r_char
op_star
DECL|function|dasd_parse_keyword
id|dasd_parse_keyword
c_func
(paren
r_char
op_star
id|parsestring
)paren
(brace
r_char
op_star
id|nextcomma
comma
op_star
id|residual_str
suffix:semicolon
r_int
id|length
suffix:semicolon
id|nextcomma
op_assign
id|strchr
c_func
(paren
id|parsestring
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nextcomma
)paren
(brace
id|length
op_assign
id|nextcomma
op_minus
id|parsestring
suffix:semicolon
id|residual_str
op_assign
id|nextcomma
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|length
op_assign
id|strlen
c_func
(paren
id|parsestring
)paren
suffix:semicolon
id|residual_str
op_assign
id|parsestring
op_plus
id|length
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
(paren
l_string|&quot;autodetect&quot;
comma
id|parsestring
comma
id|length
)paren
op_eq
l_int|0
)paren
(brace
id|dasd_autodetect
op_assign
l_int|1
suffix:semicolon
id|MESSAGE
(paren
id|KERN_INFO
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;turning to autodetection mode&quot;
)paren
suffix:semicolon
r_return
id|residual_str
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
(paren
l_string|&quot;probeonly&quot;
comma
id|parsestring
comma
id|length
)paren
op_eq
l_int|0
)paren
(brace
id|dasd_probeonly
op_assign
l_int|1
suffix:semicolon
id|MESSAGE
c_func
(paren
id|KERN_INFO
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;turning to probeonly mode&quot;
)paren
suffix:semicolon
r_return
id|residual_str
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
(paren
l_string|&quot;fixedbuffers&quot;
comma
id|parsestring
comma
id|length
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|dasd_page_cache
)paren
r_return
id|residual_str
suffix:semicolon
id|dasd_page_cache
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;dasd_page_cache&quot;
comma
id|PAGE_SIZE
comma
l_int|0
comma
id|SLAB_CACHE_DMA
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dasd_page_cache
)paren
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;Failed to create slab, &quot;
l_string|&quot;fixed buffer mode disabled.&quot;
)paren
suffix:semicolon
r_else
id|MESSAGE
(paren
id|KERN_INFO
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;turning on fixed buffer mode&quot;
)paren
suffix:semicolon
r_return
id|residual_str
suffix:semicolon
)brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to interprete the first element on the comma separated parse string&n; * as a device number or a range of devices. If the interpretation is&n; * successfull, create the matching dasd_devmap entries and return a pointer&n; * to the residual string.&n; * If interpretation fails or in case of an error, return an error code.&n; */
r_static
r_char
op_star
DECL|function|dasd_parse_range
id|dasd_parse_range
c_func
(paren
r_char
op_star
id|parsestring
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
suffix:semicolon
r_int
id|from
comma
id|from_id0
comma
id|from_id1
suffix:semicolon
r_int
id|to
comma
id|to_id0
comma
id|to_id1
suffix:semicolon
r_int
id|features
comma
id|rc
suffix:semicolon
r_char
id|bus_id
(braket
id|BUS_ID_SIZE
op_plus
l_int|1
)braket
comma
op_star
id|str
suffix:semicolon
id|str
op_assign
id|parsestring
suffix:semicolon
id|rc
op_assign
id|dasd_busid
c_func
(paren
op_amp
id|str
comma
op_amp
id|from_id0
comma
op_amp
id|from_id1
comma
op_amp
id|from
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|to
op_assign
id|from
suffix:semicolon
id|to_id0
op_assign
id|from_id0
suffix:semicolon
id|to_id1
op_assign
id|from_id1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|str
op_increment
suffix:semicolon
id|rc
op_assign
id|dasd_busid
c_func
(paren
op_amp
id|str
comma
op_amp
id|to_id0
comma
op_amp
id|to_id1
comma
op_amp
id|to
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
op_logical_and
(paren
id|from_id0
op_ne
id|to_id0
op_logical_or
id|from_id1
op_ne
id|to_id1
op_logical_or
id|from
OG
id|to
)paren
)paren
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_ERR
comma
l_string|&quot;Invalid device range %s&quot;
comma
id|parsestring
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|rc
)paren
suffix:semicolon
)brace
id|features
op_assign
id|dasd_feature_list
c_func
(paren
id|str
comma
op_amp
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|features
OL
l_int|0
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_while
c_loop
(paren
id|from
op_le
id|to
)paren
(brace
id|sprintf
c_func
(paren
id|bus_id
comma
l_string|&quot;%01x.%01x.%04x&quot;
comma
id|from_id0
comma
id|from_id1
comma
id|from
op_increment
)paren
suffix:semicolon
id|devmap
op_assign
id|dasd_add_busid
c_func
(paren
id|bus_id
comma
id|features
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|devmap
)paren
)paren
r_return
(paren
r_char
op_star
)paren
id|devmap
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;,&squot;
)paren
r_return
id|str
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
id|str
suffix:semicolon
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;junk at end of dasd parameter string: %s&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_static
r_inline
r_char
op_star
DECL|function|dasd_parse_next_element
id|dasd_parse_next_element
c_func
(paren
r_char
op_star
id|parsestring
)paren
(brace
r_char
op_star
id|residual_str
suffix:semicolon
id|residual_str
op_assign
id|dasd_parse_keyword
c_func
(paren
id|parsestring
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|residual_str
)paren
)paren
r_return
id|residual_str
suffix:semicolon
id|residual_str
op_assign
id|dasd_parse_range
c_func
(paren
id|parsestring
)paren
suffix:semicolon
r_return
id|residual_str
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse parameters stored in dasd[]&n; * The &squot;dasd=...&squot; parameter allows to specify a comma separated list of&n; * keywords and device ranges. When the dasd driver is build into the kernel,&n; * the complete list will be stored as one element of the dasd[] array.&n; * When the dasd driver is build as a module, then the list is broken into&n; * it&squot;s elements and each dasd[] entry contains one element.&n; */
r_int
DECL|function|dasd_parse
id|dasd_parse
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
comma
id|i
suffix:semicolon
r_char
op_star
id|parsestring
suffix:semicolon
id|rc
op_assign
l_int|0
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dasd
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|parsestring
op_assign
id|dasd
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* loop over the comma separated list in the parsestring */
r_while
c_loop
(paren
op_star
id|parsestring
)paren
(brace
id|parsestring
op_assign
id|dasd_parse_next_element
c_func
(paren
id|parsestring
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|parsestring
)paren
)paren
(brace
id|rc
op_assign
id|PTR_ERR
c_func
(paren
id|parsestring
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|rc
)paren
(brace
id|DBF_EVENT
c_func
(paren
id|DBF_ALERT
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;invalid range found&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a devmap for the device specified by busid. It is possible that&n; * the devmap already exists (dasd= parameter). The order of the devices&n; * added through this function will define the kdevs for the individual&n; * devices. &n; */
r_static
r_struct
id|dasd_devmap
op_star
DECL|function|dasd_add_busid
id|dasd_add_busid
c_func
(paren
r_char
op_star
id|bus_id
comma
r_int
id|features
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
comma
op_star
r_new
comma
op_star
id|tmp
suffix:semicolon
r_int
id|hash
suffix:semicolon
r_new
op_assign
(paren
r_struct
id|dasd_devmap
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dasd_devmap
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
id|devmap
op_assign
l_int|0
suffix:semicolon
id|hash
op_assign
id|dasd_hash_busid
c_func
(paren
id|bus_id
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|tmp
comma
op_amp
id|dasd_hashlists
(braket
id|hash
)braket
comma
id|list
)paren
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|tmp-&gt;bus_id
comma
id|bus_id
comma
id|BUS_ID_SIZE
)paren
op_eq
l_int|0
)paren
(brace
id|devmap
op_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|devmap
)paren
(brace
multiline_comment|/* This bus_id is new. */
r_new
op_member_access_from_pointer
id|devindex
op_assign
id|dasd_max_devindex
op_increment
suffix:semicolon
id|strncpy
c_func
(paren
r_new
op_member_access_from_pointer
id|bus_id
comma
id|bus_id
comma
id|BUS_ID_SIZE
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|features
op_assign
id|features
suffix:semicolon
r_new
op_member_access_from_pointer
id|device
op_assign
l_int|0
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
id|dasd_hashlists
(braket
id|hash
)braket
)paren
suffix:semicolon
id|devmap
op_assign
r_new
suffix:semicolon
r_new
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
)paren
id|kfree
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|devmap
suffix:semicolon
)brace
multiline_comment|/*&n; * Find devmap for device with given bus_id.&n; */
r_static
r_struct
id|dasd_devmap
op_star
DECL|function|dasd_find_busid
id|dasd_find_busid
c_func
(paren
r_char
op_star
id|bus_id
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
comma
op_star
id|tmp
suffix:semicolon
r_int
id|hash
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
id|devmap
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|hash
op_assign
id|dasd_hash_busid
c_func
(paren
id|bus_id
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|tmp
comma
op_amp
id|dasd_hashlists
(braket
id|hash
)braket
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|tmp-&gt;bus_id
comma
id|bus_id
comma
id|BUS_ID_SIZE
)paren
op_eq
l_int|0
)paren
(brace
id|devmap
op_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_return
id|devmap
suffix:semicolon
)brace
multiline_comment|/*&n; * Check if busid has been added to the list of dasd ranges.&n; */
r_int
DECL|function|dasd_busid_known
id|dasd_busid_known
c_func
(paren
r_char
op_star
id|bus_id
)paren
(brace
r_return
id|IS_ERR
c_func
(paren
id|dasd_find_busid
c_func
(paren
id|bus_id
)paren
)paren
ques
c_cond
op_minus
id|ENOENT
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Forget all about the device numbers added so far.&n; * This may only be called at module unload or system shutdown.&n; */
r_static
r_void
DECL|function|dasd_forget_ranges
id|dasd_forget_ranges
c_func
(paren
r_void
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
comma
op_star
id|n
suffix:semicolon
r_int
id|i
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_devmap_lock
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|list_for_each_entry_safe
c_func
(paren
id|devmap
comma
id|n
comma
op_amp
id|dasd_hashlists
(braket
id|i
)braket
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|devmap-&gt;device
op_ne
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|devmap-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|devmap
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Find the device struct by its device index.&n; */
r_struct
id|dasd_device
op_star
DECL|function|dasd_device_from_devindex
id|dasd_device_from_devindex
c_func
(paren
r_int
id|devindex
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|dasd_device
op_star
id|device
suffix:semicolon
r_int
id|i
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
id|devmap
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
l_int|256
)paren
op_logical_and
op_logical_neg
id|devmap
suffix:semicolon
id|i
op_increment
)paren
id|list_for_each_entry
c_func
(paren
id|tmp
comma
op_amp
id|dasd_hashlists
(braket
id|i
)braket
comma
id|list
)paren
r_if
c_cond
(paren
id|tmp-&gt;devindex
op_eq
id|devindex
)paren
(brace
multiline_comment|/* Found the devmap for the device. */
id|devmap
op_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|devmap
op_logical_and
id|devmap-&gt;device
)paren
(brace
id|device
op_assign
id|devmap-&gt;device
suffix:semicolon
id|dasd_get_device
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
r_else
id|device
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_return
id|device
suffix:semicolon
)brace
multiline_comment|/*&n; * Return devmap for cdev. If no devmap exists yet, create one and&n; * connect it to the cdev.&n; */
r_static
r_struct
id|dasd_devmap
op_star
DECL|function|dasd_devmap_from_cdev
id|dasd_devmap_from_cdev
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
suffix:semicolon
id|devmap
op_assign
id|dasd_find_busid
c_func
(paren
id|cdev-&gt;dev.bus_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|devmap
)paren
)paren
id|devmap
op_assign
id|dasd_add_busid
c_func
(paren
id|cdev-&gt;dev.bus_id
comma
id|DASD_FEATURE_DEFAULT
)paren
suffix:semicolon
r_return
id|devmap
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a dasd device structure for cdev.&n; */
r_struct
id|dasd_device
op_star
DECL|function|dasd_create_device
id|dasd_create_device
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
suffix:semicolon
r_struct
id|dasd_device
op_star
id|device
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_cdev
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|devmap
)paren
)paren
r_return
(paren
r_void
op_star
)paren
id|devmap
suffix:semicolon
id|cdev-&gt;dev.driver_data
op_assign
id|devmap
suffix:semicolon
id|device
op_assign
id|dasd_alloc_device
c_func
(paren
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
id|device
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|device-&gt;ref_count
comma
l_int|2
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|devmap-&gt;device
)paren
(brace
id|devmap-&gt;device
op_assign
id|device
suffix:semicolon
id|device-&gt;devindex
op_assign
id|devmap-&gt;devindex
suffix:semicolon
r_if
c_cond
(paren
id|devmap-&gt;features
op_amp
id|DASD_FEATURE_READONLY
)paren
id|set_bit
c_func
(paren
id|DASD_FLAG_RO
comma
op_amp
id|device-&gt;flags
)paren
suffix:semicolon
r_else
id|clear_bit
c_func
(paren
id|DASD_FLAG_RO
comma
op_amp
id|device-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devmap-&gt;features
op_amp
id|DASD_FEATURE_USEDIAG
)paren
id|set_bit
c_func
(paren
id|DASD_FLAG_USE_DIAG
comma
op_amp
id|device-&gt;flags
)paren
suffix:semicolon
r_else
id|clear_bit
c_func
(paren
id|DASD_FLAG_USE_DIAG
comma
op_amp
id|device-&gt;flags
)paren
suffix:semicolon
id|get_device
c_func
(paren
op_amp
id|cdev-&gt;dev
)paren
suffix:semicolon
id|device-&gt;cdev
op_assign
id|cdev
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
r_else
multiline_comment|/* Someone else was faster. */
id|rc
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|dasd_free_device
c_func
(paren
id|device
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|rc
)paren
suffix:semicolon
)brace
r_return
id|device
suffix:semicolon
)brace
multiline_comment|/*&n; * Wait queue for dasd_delete_device waits.&n; */
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|dasd_delete_wq
)paren
suffix:semicolon
multiline_comment|/*&n; * Remove a dasd device structure. The passed referenced&n; * is destroyed.&n; */
r_void
DECL|function|dasd_delete_device
id|dasd_delete_device
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
)paren
(brace
r_struct
id|ccw_device
op_star
id|cdev
suffix:semicolon
r_struct
id|dasd_devmap
op_star
id|devmap
suffix:semicolon
multiline_comment|/* First remove device pointer from devmap. */
id|devmap
op_assign
id|dasd_find_busid
c_func
(paren
id|device-&gt;cdev-&gt;dev.bus_id
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devmap-&gt;device
op_ne
id|device
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|device
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|devmap-&gt;device
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
multiline_comment|/* Drop ref_count by 2, one for the devmap reference and&n;&t; * one for the passed reference. */
id|atomic_sub
c_func
(paren
l_int|2
comma
op_amp
id|device-&gt;ref_count
)paren
suffix:semicolon
multiline_comment|/* Wait for reference counter to drop to zero. */
id|wait_event
c_func
(paren
id|dasd_delete_wq
comma
id|atomic_read
c_func
(paren
op_amp
id|device-&gt;ref_count
)paren
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Disconnect dasd_device structure from ccw_device structure. */
id|cdev
op_assign
id|device-&gt;cdev
suffix:semicolon
id|device-&gt;cdev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Disconnect dasd_devmap structure from ccw_device structure. */
id|cdev-&gt;dev.driver_data
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Put ccw_device structure. */
id|put_device
c_func
(paren
op_amp
id|cdev-&gt;dev
)paren
suffix:semicolon
multiline_comment|/* Now the device structure can be freed. */
id|dasd_free_device
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Reference counter dropped to zero. Wake up waiter&n; * in dasd_delete_device.&n; */
r_void
DECL|function|dasd_put_device_wake
id|dasd_put_device_wake
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|dasd_delete_wq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return dasd_device structure associated with cdev.&n; */
r_struct
id|dasd_device
op_star
DECL|function|dasd_device_from_cdev
id|dasd_device_from_cdev
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
suffix:semicolon
r_struct
id|dasd_device
op_star
id|device
suffix:semicolon
id|device
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
id|devmap
op_assign
id|cdev-&gt;dev.driver_data
suffix:semicolon
r_if
c_cond
(paren
id|devmap
op_logical_and
id|devmap-&gt;device
)paren
(brace
id|device
op_assign
id|devmap-&gt;device
suffix:semicolon
id|dasd_get_device
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_return
id|device
suffix:semicolon
)brace
multiline_comment|/*&n; * SECTION: files in sysfs&n; */
multiline_comment|/*&n; * readonly controls the readonly status of a dasd&n; */
r_static
id|ssize_t
DECL|function|dasd_ro_show
id|dasd_ro_show
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
suffix:semicolon
r_int
id|ro_flag
suffix:semicolon
id|devmap
op_assign
id|dev-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
id|devmap
)paren
id|ro_flag
op_assign
(paren
id|devmap-&gt;features
op_amp
id|DASD_FEATURE_READONLY
)paren
op_ne
l_int|0
suffix:semicolon
r_else
id|ro_flag
op_assign
(paren
id|DASD_FEATURE_DEFAULT
op_amp
id|DASD_FEATURE_READONLY
)paren
op_ne
l_int|0
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|buf
comma
id|PAGE_SIZE
comma
id|ro_flag
ques
c_cond
l_string|&quot;1&bslash;n&quot;
suffix:colon
l_string|&quot;0&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|dasd_ro_store
id|dasd_ro_store
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
suffix:semicolon
r_int
id|ro_flag
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_cdev
c_func
(paren
id|to_ccwdev
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|ro_flag
op_assign
id|buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;1&squot;
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ro_flag
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
r_if
c_cond
(paren
id|devmap-&gt;device
)paren
(brace
r_if
c_cond
(paren
id|devmap-&gt;device-&gt;gdp
)paren
id|set_disk_ro
c_func
(paren
id|devmap-&gt;device-&gt;gdp
comma
id|ro_flag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ro_flag
)paren
id|set_bit
c_func
(paren
id|DASD_FLAG_RO
comma
op_amp
id|devmap-&gt;device-&gt;flags
)paren
suffix:semicolon
r_else
id|clear_bit
c_func
(paren
id|DASD_FLAG_RO
comma
op_amp
id|devmap-&gt;device-&gt;flags
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|readonly
comma
l_int|0644
comma
id|dasd_ro_show
comma
id|dasd_ro_store
)paren
suffix:semicolon
multiline_comment|/*&n; * use_diag controls whether the driver should use diag rather than ssch&n; * to talk to the device&n; */
multiline_comment|/* TODO: Implement */
r_static
id|ssize_t
DECL|function|dasd_use_diag_show
id|dasd_use_diag_show
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
suffix:semicolon
r_int
id|use_diag
suffix:semicolon
id|devmap
op_assign
id|dev-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
id|devmap
)paren
id|use_diag
op_assign
(paren
id|devmap-&gt;features
op_amp
id|DASD_FEATURE_USEDIAG
)paren
op_ne
l_int|0
suffix:semicolon
r_else
id|use_diag
op_assign
(paren
id|DASD_FEATURE_DEFAULT
op_amp
id|DASD_FEATURE_USEDIAG
)paren
op_ne
l_int|0
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
id|use_diag
ques
c_cond
l_string|&quot;1&bslash;n&quot;
suffix:colon
l_string|&quot;0&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|dasd_use_diag_store
id|dasd_use_diag_store
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
suffix:semicolon
r_int
id|use_diag
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_cdev
c_func
(paren
id|to_ccwdev
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|use_diag
op_assign
id|buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;1&squot;
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
multiline_comment|/* Changing diag discipline flag is only allowed in offline state. */
r_if
c_cond
(paren
op_logical_neg
id|devmap-&gt;device
)paren
(brace
r_if
c_cond
(paren
id|use_diag
)paren
id|devmap-&gt;features
op_or_assign
id|DASD_FEATURE_USEDIAG
suffix:semicolon
r_else
id|devmap-&gt;features
op_and_assign
op_complement
id|DASD_FEATURE_USEDIAG
suffix:semicolon
)brace
r_else
id|count
op_assign
op_minus
id|EPERM
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|use_diag
comma
l_int|0644
comma
id|dasd_use_diag_show
comma
id|dasd_use_diag_store
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|dasd_discipline_show
id|dasd_discipline_show
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|dasd_devmap
op_star
id|devmap
suffix:semicolon
r_char
op_star
id|dname
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
id|dname
op_assign
l_string|&quot;none&quot;
suffix:semicolon
id|devmap
op_assign
id|dev-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
id|devmap
op_logical_and
id|devmap-&gt;device
op_logical_and
id|devmap-&gt;device-&gt;discipline
)paren
id|dname
op_assign
id|devmap-&gt;device-&gt;discipline-&gt;name
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dasd_devmap_lock
)paren
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|buf
comma
id|PAGE_SIZE
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|dname
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|discipline
comma
l_int|0444
comma
id|dasd_discipline_show
comma
l_int|NULL
)paren
suffix:semicolon
DECL|variable|dasd_attrs
r_static
r_struct
id|attribute
op_star
id|dasd_attrs
(braket
)braket
op_assign
(brace
op_amp
id|dev_attr_readonly.attr
comma
op_amp
id|dev_attr_discipline.attr
comma
op_amp
id|dev_attr_use_diag.attr
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|dasd_attr_group
r_static
r_struct
id|attribute_group
id|dasd_attr_group
op_assign
(brace
dot
id|attrs
op_assign
id|dasd_attrs
comma
)brace
suffix:semicolon
r_int
DECL|function|dasd_add_sysfs_files
id|dasd_add_sysfs_files
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_return
id|sysfs_create_group
c_func
(paren
op_amp
id|cdev-&gt;dev.kobj
comma
op_amp
id|dasd_attr_group
)paren
suffix:semicolon
)brace
r_void
DECL|function|dasd_remove_sysfs_files
id|dasd_remove_sysfs_files
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
id|sysfs_remove_group
c_func
(paren
op_amp
id|cdev-&gt;dev.kobj
comma
op_amp
id|dasd_attr_group
)paren
suffix:semicolon
)brace
r_int
DECL|function|dasd_devmap_init
id|dasd_devmap_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Initialize devmap structures. */
id|dasd_max_devindex
op_assign
l_int|0
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dasd_hashlists
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|dasd_devmap_exit
id|dasd_devmap_exit
c_func
(paren
r_void
)paren
(brace
id|dasd_forget_ranges
c_func
(paren
)paren
suffix:semicolon
)brace
eof
