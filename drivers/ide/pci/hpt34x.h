macro_line|#ifndef HPT34X_H
DECL|macro|HPT34X_H
mdefine_line|#define HPT34X_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|HPT343_DEBUG_DRIVE_INFO
mdefine_line|#define HPT343_DEBUG_DRIVE_INFO&t;&t;0
macro_line|#ifndef SPLIT_BYTE
DECL|macro|SPLIT_BYTE
mdefine_line|#define SPLIT_BYTE(B,H,L)&t;((H)=(B&gt;&gt;4), (L)=(B-((B&gt;&gt;4)&lt;&lt;4)))
macro_line|#endif
r_static
r_int
r_int
id|init_chipset_hpt34x
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_hwif_hpt34x
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|hpt34x_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
dot
id|name
op_assign
l_string|&quot;HPT34X&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_hpt34x
comma
dot
id|init_hwif
op_assign
id|init_hwif_hpt34x
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|NOAUTODMA
comma
dot
id|bootable
op_assign
id|NEVER_BOARD
comma
dot
id|extra
op_assign
l_int|16
)brace
)brace
suffix:semicolon
macro_line|#endif /* HPT34X_H */
eof
