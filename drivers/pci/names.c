multiline_comment|/*&n; *&t;PCI Class and Device Name Tables&n; *&n; *&t;Copyright 1993--1999 Drew Eckhardt, Frederic Potter,&n; *&t;David Mosberger-Tang, Martin Mares&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_PCI_NAMES
DECL|struct|pci_device_info
r_struct
id|pci_device_info
(brace
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
DECL|member|seen
r_int
r_int
id|seen
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_vendor_info
r_struct
id|pci_vendor_info
(brace
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|devices
r_struct
id|pci_device_info
op_star
id|devices
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is ridiculous, but we want the strings in&n; * the .init section so that they don&squot;t take up&n; * real memory.. Parse the same file multiple times&n; * to get all the info.&n; */
DECL|macro|VENDOR
mdefine_line|#define VENDOR( vendor, name )&t;&t;static char __vendorstr_##vendor[] __devinitdata = name;
DECL|macro|ENDVENDOR
mdefine_line|#define ENDVENDOR()
DECL|macro|DEVICE
mdefine_line|#define DEVICE( vendor, device, name ) &t;static char __devicestr_##vendor##device[] __devinitdata = name;
macro_line|#include &quot;devlist.h&quot;
DECL|macro|VENDOR
mdefine_line|#define VENDOR( vendor, name )&t;&t;static struct pci_device_info __devices_##vendor[] __devinitdata = {
DECL|macro|ENDVENDOR
mdefine_line|#define ENDVENDOR()&t;&t;&t;};
DECL|macro|DEVICE
mdefine_line|#define DEVICE( vendor, device, name )&t;{ 0x##device, 0, __devicestr_##vendor##device },
macro_line|#include &quot;devlist.h&quot;
DECL|variable|pci_vendor_list
r_static
r_struct
id|pci_vendor_info
id|__devinitdata
id|pci_vendor_list
(braket
)braket
op_assign
(brace
DECL|macro|VENDOR
mdefine_line|#define VENDOR( vendor, name )&t;&t;{ 0x##vendor, sizeof(__devices_##vendor) / sizeof(struct pci_device_info), __vendorstr_##vendor, __devices_##vendor },
DECL|macro|ENDVENDOR
mdefine_line|#define ENDVENDOR()
DECL|macro|DEVICE
mdefine_line|#define DEVICE( vendor, device, name )
macro_line|#include &quot;devlist.h&quot;
)brace
suffix:semicolon
DECL|macro|VENDORS
mdefine_line|#define VENDORS (sizeof(pci_vendor_list)/sizeof(struct pci_vendor_info))
DECL|function|pci_name_device
r_void
id|__devinit
id|pci_name_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_const
r_struct
id|pci_vendor_info
op_star
id|vendor_p
op_assign
id|pci_vendor_list
suffix:semicolon
r_int
id|i
op_assign
id|VENDORS
suffix:semicolon
r_char
op_star
id|name
op_assign
id|dev-&gt;pretty_name
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|vendor_p-&gt;vendor
op_eq
id|dev-&gt;vendor
)paren
r_goto
id|match_vendor
suffix:semicolon
id|vendor_p
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
)paren
suffix:semicolon
multiline_comment|/* Couldn&squot;t find either the vendor nor the device */
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;PCI device %04x:%04x&quot;
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
)paren
suffix:semicolon
r_return
suffix:semicolon
id|match_vendor
suffix:colon
(brace
r_struct
id|pci_device_info
op_star
id|device_p
op_assign
id|vendor_p-&gt;devices
suffix:semicolon
r_int
id|i
op_assign
id|vendor_p-&gt;nr
suffix:semicolon
r_while
c_loop
(paren
id|i
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|device_p-&gt;device
op_eq
id|dev-&gt;device
)paren
r_goto
id|match_device
suffix:semicolon
id|device_p
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Ok, found the vendor, but unknown device */
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;PCI device %04x:%04x (%.&quot;
id|PCI_NAME_HALF
l_string|&quot;s)&quot;
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
comma
id|vendor_p-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* Full match */
id|match_device
suffix:colon
(brace
r_char
op_star
id|n
op_assign
id|name
op_plus
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%.&quot;
id|PCI_NAME_HALF
l_string|&quot;s %.&quot;
id|PCI_NAME_HALF
l_string|&quot;s&quot;
comma
id|vendor_p-&gt;name
comma
id|device_p-&gt;name
)paren
suffix:semicolon
r_int
id|nr
op_assign
id|device_p-&gt;seen
op_plus
l_int|1
suffix:semicolon
id|device_p-&gt;seen
op_assign
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|nr
OG
l_int|1
)paren
id|sprintf
c_func
(paren
id|n
comma
l_string|&quot; (#%d)&quot;
comma
id|nr
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *  Class names. Not in .init section as they are needed in runtime.&n; */
DECL|variable|pci_class_numbers
r_static
id|u16
id|pci_class_numbers
(braket
)braket
op_assign
(brace
DECL|macro|CLASS
mdefine_line|#define CLASS(x,y) 0x##x,
macro_line|#include &quot;classlist.h&quot;
)brace
suffix:semicolon
DECL|variable|pci_class_names
r_static
r_char
op_star
id|pci_class_names
(braket
)braket
op_assign
(brace
DECL|macro|CLASS
mdefine_line|#define CLASS(x,y) y,
macro_line|#include &quot;classlist.h&quot;
)brace
suffix:semicolon
r_char
op_star
DECL|function|pci_class_name
id|pci_class_name
c_func
(paren
id|u32
r_class
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
r_sizeof
(paren
id|pci_class_numbers
)paren
op_div
r_sizeof
(paren
id|pci_class_numbers
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|pci_class_numbers
(braket
id|i
)braket
op_eq
r_class
)paren
r_return
id|pci_class_names
(braket
id|i
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#else
DECL|function|pci_name_device
r_void
id|__devinit
id|pci_name_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
r_char
op_star
DECL|function|pci_class_name
id|pci_class_name
c_func
(paren
id|u32
r_class
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI_NAMES */
eof
