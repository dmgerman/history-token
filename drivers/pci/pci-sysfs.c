multiline_comment|/*&n; * drivers/pci/pci-sysfs.c&n; *&n; * (C) Copyright 2002-2004 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; * (C) Copyright 2002-2004 IBM Corp.&n; * (C) Copyright 2003 Matthew Wilcox&n; * (C) Copyright 2003 Hewlett-Packard&n; * (C) Copyright 2004 Jon Smirl &lt;jonsmirl@yahoo.com&gt;&n; * (C) Copyright 2004 Silicon Graphics, Inc. Jesse Barnes &lt;jbarnes@sgi.com&gt;&n; *&n; * File attributes for PCI devices&n; *&n; * Modeled after usb&squot;s driverfs.c &n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/topology.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|variable|sysfs_initialized
r_static
r_int
id|sysfs_initialized
suffix:semicolon
multiline_comment|/* = 0 */
multiline_comment|/* show configuration fields */
DECL|macro|pci_config_attr
mdefine_line|#define pci_config_attr(field, format_string)&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;field##_show(struct device *dev, char *buf)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct pci_dev *pdev;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pdev = to_pci_dev (dev);&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf (buf, format_string, pdev-&gt;field);&t;&t;&bslash;&n;}
id|pci_config_attr
c_func
(paren
id|vendor
comma
l_string|&quot;0x%04x&bslash;n&quot;
)paren
suffix:semicolon
id|pci_config_attr
c_func
(paren
id|device
comma
l_string|&quot;0x%04x&bslash;n&quot;
)paren
suffix:semicolon
id|pci_config_attr
c_func
(paren
id|subsystem_vendor
comma
l_string|&quot;0x%04x&bslash;n&quot;
)paren
suffix:semicolon
id|pci_config_attr
c_func
(paren
id|subsystem_device
comma
l_string|&quot;0x%04x&bslash;n&quot;
)paren
suffix:semicolon
id|pci_config_attr
c_func
(paren
r_class
comma
l_string|&quot;0x%06x&bslash;n&quot;
)paren
suffix:semicolon
id|pci_config_attr
c_func
(paren
id|irq
comma
l_string|&quot;%u&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|local_cpus_show
r_static
id|ssize_t
id|local_cpus_show
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
id|cpumask_t
id|mask
op_assign
id|pcibus_to_cpumask
c_func
(paren
id|to_pci_dev
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|bus-&gt;number
)paren
suffix:semicolon
r_int
id|len
op_assign
id|cpumask_scnprintf
c_func
(paren
id|buf
comma
id|PAGE_SIZE
op_minus
l_int|2
comma
id|mask
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
op_plus
id|len
suffix:semicolon
)brace
multiline_comment|/* show resources */
r_static
id|ssize_t
DECL|function|resource_show
id|resource_show
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
id|pci_dev
op_star
id|pci_dev
op_assign
id|to_pci_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_char
op_star
id|str
op_assign
id|buf
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|max
op_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|pci_dev-&gt;subordinate
)paren
id|max
op_assign
id|DEVICE_COUNT_RESOURCE
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
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;0x%016lx 0x%016lx 0x%016lx&bslash;n&quot;
comma
id|pci_resource_start
c_func
(paren
id|pci_dev
comma
id|i
)paren
comma
id|pci_resource_end
c_func
(paren
id|pci_dev
comma
id|i
)paren
comma
id|pci_resource_flags
c_func
(paren
id|pci_dev
comma
id|i
)paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
DECL|variable|pci_dev_attrs
r_struct
id|device_attribute
id|pci_dev_attrs
(braket
)braket
op_assign
(brace
id|__ATTR_RO
c_func
(paren
id|resource
)paren
comma
id|__ATTR_RO
c_func
(paren
id|vendor
)paren
comma
id|__ATTR_RO
c_func
(paren
id|device
)paren
comma
id|__ATTR_RO
c_func
(paren
id|subsystem_vendor
)paren
comma
id|__ATTR_RO
c_func
(paren
id|subsystem_device
)paren
comma
id|__ATTR_RO
c_func
(paren
r_class
)paren
comma
id|__ATTR_RO
c_func
(paren
id|irq
)paren
comma
id|__ATTR_RO
c_func
(paren
id|local_cpus
)paren
comma
id|__ATTR_NULL
comma
)brace
suffix:semicolon
r_static
id|ssize_t
DECL|function|pci_read_config
id|pci_read_config
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buf
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|to_pci_dev
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|device
comma
id|kobj
)paren
)paren
suffix:semicolon
r_int
r_int
id|size
op_assign
l_int|64
suffix:semicolon
id|loff_t
id|init_off
op_assign
id|off
suffix:semicolon
multiline_comment|/* Several chips lock up trying to read undefined config space */
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
id|size
op_assign
id|dev-&gt;cfg_size
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_CARDBUS
)paren
(brace
id|size
op_assign
l_int|128
suffix:semicolon
)brace
r_if
c_cond
(paren
id|off
OG
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
op_plus
id|count
OG
id|size
)paren
(brace
id|size
op_sub_assign
id|off
suffix:semicolon
id|count
op_assign
id|size
suffix:semicolon
)brace
r_else
(brace
id|size
op_assign
id|count
suffix:semicolon
)brace
r_while
c_loop
(paren
id|off
op_amp
l_int|3
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|off
comma
op_amp
id|val
)paren
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
)braket
op_assign
id|val
suffix:semicolon
id|off
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|size
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|3
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|off
comma
op_amp
id|val
)paren
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
)braket
op_assign
id|val
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|1
)braket
op_assign
(paren
id|val
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|2
)braket
op_assign
(paren
id|val
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|3
)braket
op_assign
(paren
id|val
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
id|off
op_add_assign
l_int|4
suffix:semicolon
id|size
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|off
comma
op_amp
id|val
)paren
suffix:semicolon
id|buf
(braket
id|off
op_minus
id|init_off
)braket
op_assign
id|val
suffix:semicolon
id|off
op_increment
suffix:semicolon
op_decrement
id|size
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|pci_write_config
id|pci_write_config
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buf
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|to_pci_dev
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|device
comma
id|kobj
)paren
)paren
suffix:semicolon
r_int
r_int
id|size
op_assign
id|count
suffix:semicolon
id|loff_t
id|init_off
op_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|off
OG
id|dev-&gt;cfg_size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
op_plus
id|count
OG
id|dev-&gt;cfg_size
)paren
(brace
id|size
op_assign
id|dev-&gt;cfg_size
op_minus
id|off
suffix:semicolon
id|count
op_assign
id|size
suffix:semicolon
)brace
r_while
c_loop
(paren
id|off
op_amp
l_int|3
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|off
comma
id|buf
(braket
id|off
op_minus
id|init_off
)braket
)paren
suffix:semicolon
id|off
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|size
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|3
)paren
(brace
r_int
r_int
id|val
op_assign
id|buf
(braket
id|off
op_minus
id|init_off
)braket
suffix:semicolon
id|val
op_or_assign
(paren
r_int
r_int
)paren
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|1
)braket
op_lshift
l_int|8
suffix:semicolon
id|val
op_or_assign
(paren
r_int
r_int
)paren
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|2
)braket
op_lshift
l_int|16
suffix:semicolon
id|val
op_or_assign
(paren
r_int
r_int
)paren
id|buf
(braket
id|off
op_minus
id|init_off
op_plus
l_int|3
)braket
op_lshift
l_int|24
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|off
comma
id|val
)paren
suffix:semicolon
id|off
op_add_assign
l_int|4
suffix:semicolon
id|size
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|off
comma
id|buf
(braket
id|off
op_minus
id|init_off
)braket
)paren
suffix:semicolon
id|off
op_increment
suffix:semicolon
op_decrement
id|size
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
macro_line|#ifdef HAVE_PCI_LEGACY
multiline_comment|/**&n; * pci_read_legacy_io - read byte(s) from legacy I/O port space&n; * @kobj: kobject corresponding to file to read from&n; * @buf: buffer to store results&n; * @off: offset into legacy I/O port space&n; * @count: number of bytes to read&n; *&n; * Reads 1, 2, or 4 bytes from legacy I/O port space using an arch specific&n; * callback routine (pci_legacy_read).&n; */
id|ssize_t
DECL|function|pci_read_legacy_io
id|pci_read_legacy_io
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buf
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|to_pci_bus
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|class_device
comma
id|kobj
)paren
)paren
suffix:semicolon
multiline_comment|/* Only support 1, 2 or 4 byte accesses */
r_if
c_cond
(paren
id|count
op_ne
l_int|1
op_logical_and
id|count
op_ne
l_int|2
op_logical_and
id|count
op_ne
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|pci_legacy_read
c_func
(paren
id|bus
comma
id|off
comma
(paren
id|u32
op_star
)paren
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_write_legacy_io - write byte(s) to legacy I/O port space&n; * @kobj: kobject corresponding to file to read from&n; * @buf: buffer containing value to be written&n; * @off: offset into legacy I/O port space&n; * @count: number of bytes to write&n; *&n; * Writes 1, 2, or 4 bytes from legacy I/O port space using an arch specific&n; * callback routine (pci_legacy_write).&n; */
id|ssize_t
DECL|function|pci_write_legacy_io
id|pci_write_legacy_io
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buf
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|to_pci_bus
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|class_device
comma
id|kobj
)paren
)paren
suffix:semicolon
multiline_comment|/* Only support 1, 2 or 4 byte accesses */
r_if
c_cond
(paren
id|count
op_ne
l_int|1
op_logical_and
id|count
op_ne
l_int|2
op_logical_and
id|count
op_ne
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|pci_legacy_write
c_func
(paren
id|bus
comma
id|off
comma
op_star
(paren
id|u32
op_star
)paren
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_mmap_legacy_mem - map legacy PCI memory into user memory space&n; * @kobj: kobject corresponding to device to be mapped&n; * @attr: struct bin_attribute for this file&n; * @vma: struct vm_area_struct passed to mmap&n; *&n; * Uses an arch specific callback, pci_mmap_legacy_page_range, to mmap&n; * legacy memory space (first meg of bus space) into application virtual&n; * memory space.&n; */
r_int
DECL|function|pci_mmap_legacy_mem
id|pci_mmap_legacy_mem
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|bin_attribute
op_star
id|attr
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|to_pci_bus
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|class_device
comma
id|kobj
)paren
)paren
suffix:semicolon
r_return
id|pci_mmap_legacy_page_range
c_func
(paren
id|bus
comma
id|vma
)paren
suffix:semicolon
)brace
macro_line|#endif /* HAVE_PCI_LEGACY */
macro_line|#ifdef HAVE_PCI_MMAP
multiline_comment|/**&n; * pci_mmap_resource - map a PCI resource into user memory space&n; * @kobj: kobject for mapping&n; * @attr: struct bin_attribute for the file being mapped&n; * @vma: struct vm_area_struct passed into the mmap&n; *&n; * Use the regular PCI mapping routines to map a PCI resource into userspace.&n; * FIXME: write combining?  maybe automatic for prefetchable regions?&n; */
r_static
r_int
DECL|function|pci_mmap_resource
id|pci_mmap_resource
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|bin_attribute
op_star
id|attr
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|to_pci_dev
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|device
comma
id|kobj
)paren
)paren
suffix:semicolon
r_struct
id|resource
op_star
id|res
op_assign
(paren
r_struct
id|resource
op_star
)paren
id|attr
op_member_access_from_pointer
r_private
suffix:semicolon
r_enum
id|pci_mmap_state
id|mmap_type
suffix:semicolon
id|vma-&gt;vm_pgoff
op_add_assign
id|res-&gt;start
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|mmap_type
op_assign
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
ques
c_cond
id|pci_mmap_mem
suffix:colon
id|pci_mmap_io
suffix:semicolon
r_return
id|pci_mmap_page_range
c_func
(paren
id|pdev
comma
id|vma
comma
id|mmap_type
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_create_resource_files - create resource files in sysfs for @dev&n; * @dev: dev in question&n; *&n; * Walk the resources in @dev creating files for each resource available.&n; */
r_static
r_void
DECL|function|pci_create_resource_files
id|pci_create_resource_files
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Expose the PCI resources from this device as files */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PCI_ROM_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|bin_attribute
op_star
id|res_attr
suffix:semicolon
multiline_comment|/* skip empty resources */
r_if
c_cond
(paren
op_logical_neg
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|i
)paren
)paren
r_continue
suffix:semicolon
id|res_attr
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|res_attr
)paren
op_plus
l_int|10
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res_attr
)paren
(brace
id|memset
c_func
(paren
id|res_attr
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|res_attr
)paren
op_plus
l_int|10
)paren
suffix:semicolon
id|pdev-&gt;res_attr
(braket
id|i
)braket
op_assign
id|res_attr
suffix:semicolon
multiline_comment|/* Allocated above after the res_attr struct */
id|res_attr-&gt;attr.name
op_assign
(paren
r_char
op_star
)paren
(paren
id|res_attr
op_plus
l_int|1
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|res_attr-&gt;attr.name
comma
l_string|&quot;resource%d&quot;
comma
id|i
)paren
suffix:semicolon
id|res_attr-&gt;size
op_assign
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|i
)paren
suffix:semicolon
id|res_attr-&gt;attr.mode
op_assign
id|S_IRUSR
op_or
id|S_IWUSR
suffix:semicolon
id|res_attr-&gt;attr.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|res_attr-&gt;mmap
op_assign
id|pci_mmap_resource
suffix:semicolon
id|res_attr
op_member_access_from_pointer
r_private
op_assign
op_amp
id|pdev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
id|sysfs_create_bin_file
c_func
(paren
op_amp
id|pdev-&gt;dev.kobj
comma
id|res_attr
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; * pci_remove_resource_files - cleanup resource files&n; * @dev: dev to cleanup&n; *&n; * If we created resource files for @dev, remove them from sysfs and&n; * free their resources.&n; */
r_static
r_void
DECL|function|pci_remove_resource_files
id|pci_remove_resource_files
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
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
id|PCI_ROM_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|bin_attribute
op_star
id|res_attr
suffix:semicolon
id|res_attr
op_assign
id|pdev-&gt;res_attr
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|res_attr
)paren
(brace
id|sysfs_remove_bin_file
c_func
(paren
op_amp
id|pdev-&gt;dev.kobj
comma
id|res_attr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|res_attr
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#else /* !HAVE_PCI_MMAP */
DECL|function|pci_create_resource_files
r_static
r_inline
r_void
id|pci_create_resource_files
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|pci_remove_resource_files
r_static
r_inline
r_void
id|pci_remove_resource_files
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif /* HAVE_PCI_MMAP */
multiline_comment|/**&n; * pci_write_rom - used to enable access to the PCI ROM display&n; * @kobj: kernel object handle&n; * @buf: user input&n; * @off: file offset&n; * @count: number of byte in input&n; *&n; * writing anything except 0 enables it&n; */
r_static
id|ssize_t
DECL|function|pci_write_rom
id|pci_write_rom
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buf
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|to_pci_dev
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|device
comma
id|kobj
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|off
op_eq
l_int|0
)paren
op_logical_and
(paren
op_star
id|buf
op_eq
l_char|&squot;0&squot;
)paren
op_logical_and
(paren
id|count
op_eq
l_int|2
)paren
)paren
id|pdev-&gt;rom_attr_enabled
op_assign
l_int|0
suffix:semicolon
r_else
id|pdev-&gt;rom_attr_enabled
op_assign
l_int|1
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_read_rom - read a PCI ROM&n; * @kobj: kernel object handle&n; * @buf: where to put the data we read from the ROM&n; * @off: file offset&n; * @count: number of bytes to read&n; *&n; * Put @count bytes starting at @off into @buf from the ROM in the PCI&n; * device corresponding to @kobj.&n; */
r_static
id|ssize_t
DECL|function|pci_read_rom
id|pci_read_rom
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buf
comma
id|loff_t
id|off
comma
r_int
id|count
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|to_pci_dev
c_func
(paren
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|device
comma
id|kobj
)paren
)paren
suffix:semicolon
r_void
id|__iomem
op_star
id|rom
suffix:semicolon
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev-&gt;rom_attr_enabled
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|rom
op_assign
id|pci_map_rom
c_func
(paren
id|pdev
comma
op_amp
id|size
)paren
suffix:semicolon
multiline_comment|/* size starts out as PCI window size */
r_if
c_cond
(paren
op_logical_neg
id|rom
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ge
id|size
)paren
id|count
op_assign
l_int|0
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|off
op_plus
id|count
OG
id|size
)paren
id|count
op_assign
id|size
op_minus
id|off
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|buf
comma
id|rom
op_plus
id|off
comma
id|count
)paren
suffix:semicolon
)brace
id|pci_unmap_rom
c_func
(paren
id|pdev
comma
id|rom
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|pci_config_attr
r_static
r_struct
id|bin_attribute
id|pci_config_attr
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;config&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
op_or
id|S_IWUSR
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
comma
dot
id|size
op_assign
l_int|256
comma
dot
id|read
op_assign
id|pci_read_config
comma
dot
id|write
op_assign
id|pci_write_config
comma
)brace
suffix:semicolon
DECL|variable|pcie_config_attr
r_static
r_struct
id|bin_attribute
id|pcie_config_attr
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;config&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
op_or
id|S_IWUSR
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
comma
dot
id|size
op_assign
l_int|4096
comma
dot
id|read
op_assign
id|pci_read_config
comma
dot
id|write
op_assign
id|pci_write_config
comma
)brace
suffix:semicolon
DECL|function|pci_create_sysfs_dev_files
r_int
id|pci_create_sysfs_dev_files
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sysfs_initialized
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|pdev-&gt;cfg_size
OL
l_int|4096
)paren
id|sysfs_create_bin_file
c_func
(paren
op_amp
id|pdev-&gt;dev.kobj
comma
op_amp
id|pci_config_attr
)paren
suffix:semicolon
r_else
id|sysfs_create_bin_file
c_func
(paren
op_amp
id|pdev-&gt;dev.kobj
comma
op_amp
id|pcie_config_attr
)paren
suffix:semicolon
id|pci_create_resource_files
c_func
(paren
id|pdev
)paren
suffix:semicolon
multiline_comment|/* If the device has a ROM, try to expose it in sysfs. */
r_if
c_cond
(paren
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|PCI_ROM_RESOURCE
)paren
)paren
(brace
r_struct
id|bin_attribute
op_star
id|rom_attr
suffix:semicolon
id|rom_attr
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|rom_attr
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rom_attr
)paren
(brace
id|pdev-&gt;rom_attr
op_assign
id|rom_attr
suffix:semicolon
id|rom_attr-&gt;size
op_assign
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|PCI_ROM_RESOURCE
)paren
suffix:semicolon
id|rom_attr-&gt;attr.name
op_assign
l_string|&quot;rom&quot;
suffix:semicolon
id|rom_attr-&gt;attr.mode
op_assign
id|S_IRUSR
suffix:semicolon
id|rom_attr-&gt;attr.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|rom_attr-&gt;read
op_assign
id|pci_read_rom
suffix:semicolon
id|rom_attr-&gt;write
op_assign
id|pci_write_rom
suffix:semicolon
id|sysfs_create_bin_file
c_func
(paren
op_amp
id|pdev-&gt;dev.kobj
comma
id|rom_attr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* add platform-specific attributes */
id|pcibios_add_platform_entries
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_remove_sysfs_dev_files - cleanup PCI specific sysfs files&n; * @pdev: device whose entries we should free&n; *&n; * Cleanup when @pdev is removed from sysfs.&n; */
DECL|function|pci_remove_sysfs_dev_files
r_void
id|pci_remove_sysfs_dev_files
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_if
c_cond
(paren
id|pdev-&gt;cfg_size
OL
l_int|4096
)paren
id|sysfs_remove_bin_file
c_func
(paren
op_amp
id|pdev-&gt;dev.kobj
comma
op_amp
id|pci_config_attr
)paren
suffix:semicolon
r_else
id|sysfs_remove_bin_file
c_func
(paren
op_amp
id|pdev-&gt;dev.kobj
comma
op_amp
id|pcie_config_attr
)paren
suffix:semicolon
id|pci_remove_resource_files
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_resource_len
c_func
(paren
id|pdev
comma
id|PCI_ROM_RESOURCE
)paren
)paren
(brace
r_if
c_cond
(paren
id|pdev-&gt;rom_attr
)paren
(brace
id|sysfs_remove_bin_file
c_func
(paren
op_amp
id|pdev-&gt;dev.kobj
comma
id|pdev-&gt;rom_attr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pdev-&gt;rom_attr
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|pci_sysfs_init
r_static
r_int
id|__init
id|pci_sysfs_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
l_int|NULL
suffix:semicolon
id|sysfs_initialized
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|pdev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|pdev
)paren
)paren
op_ne
l_int|NULL
)paren
id|pci_create_sysfs_dev_files
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_sysfs_init
id|__initcall
c_func
(paren
id|pci_sysfs_init
)paren
suffix:semicolon
eof
