multiline_comment|/*&n; *&t;arch/mips/pci/fixup-sb1250.c&n; *&n; *&t;Copyright (C) 2004  MIPS Technologies, Inc.  All rights reserved.&n; *&t;    Author:&t;Maciej W. Rozycki &lt;macro@mips.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/*&n; * The BCM1250, etc. PCI/HT bridge reports as a host bridge.&n; */
DECL|function|quirk_sb1250_ht
r_static
r_void
id|__init
id|quirk_sb1250_ht
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|dev
op_member_access_from_pointer
r_class
op_assign
id|PCI_CLASS_BRIDGE_PCI
op_lshift
l_int|8
suffix:semicolon
)brace
id|DECLARE_PCI_FIXUP_EARLY
c_func
(paren
id|PCI_VENDOR_ID_SIBYTE
comma
id|PCI_DEVICE_ID_BCM1250_HT
comma
id|quirk_sb1250_ht
)paren
suffix:semicolon
eof
