multiline_comment|/*&n; *  linux/drivers/ide/pci/generic.c&t;Version 0.11&t;December 30, 2002&n; *&n; *  Copyright (C) 2001-2002&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; *  Portions (C) Copyright 2002  Red Hat Inc &lt;alan@redhat.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * For the avoidance of doubt the &quot;preferred form&quot; of this code is one which&n; * is in an open non patent encumbered format. Where cryptographic key signing&n; * forms part of the process of creating an executable the information&n; * including keys needed to generate an equivalently functional executable&n; * are deemed to be part of the source code.&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;&t;/* most systems can safely undef this */
macro_line|#include &lt;linux/config.h&gt; /* for CONFIG_BLK_DEV_IDEPCI */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|function|init_chipset_generic
r_static
r_int
r_int
id|__init
id|init_chipset_generic
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_hwif_generic
r_static
r_void
id|__init
id|init_hwif_generic
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_switch
c_cond
(paren
id|hwif-&gt;pci_dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_UMC_UM8673F
suffix:colon
r_case
id|PCI_DEVICE_ID_UMC_UM8886A
suffix:colon
r_case
id|PCI_DEVICE_ID_UMC_UM8886BF
suffix:colon
id|hwif-&gt;irq
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|15
suffix:colon
l_int|14
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|hwif-&gt;dma_base
)paren
)paren
r_return
suffix:semicolon
id|hwif-&gt;atapi_dma
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;ultra_mask
op_assign
l_int|0x7f
suffix:semicolon
id|hwif-&gt;mwdma_mask
op_assign
l_int|0x07
suffix:semicolon
id|hwif-&gt;swdma_mask
op_assign
l_int|0x07
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|noautodma
)paren
id|hwif-&gt;autodma
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autodma
op_assign
id|hwif-&gt;autodma
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autodma
op_assign
id|hwif-&gt;autodma
suffix:semicolon
)brace
r_extern
r_void
id|ide_setup_pci_device
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|ide_pci_device_t
op_star
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Logic to add back later on */
r_if
c_cond
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_eq
id|PCI_CLASS_STORAGE_IDE
)paren
(brace
id|ide_pci_device_t
op_star
id|unknown
op_assign
id|unknown_chipset
suffix:semicolon
singleline_comment|//&t;&t;unknown-&gt;vendor = dev-&gt;vendor;
singleline_comment|//&t;&t;unknown-&gt;device = dev-&gt;device;
id|init_setup_unknown
c_func
(paren
id|dev
comma
id|unknown
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#endif&t;
multiline_comment|/**&n; *&t;generic_init_one&t;-&t;called when a PIIX is found&n; *&t;@dev: the generic device&n; *&t;@id: the matching pci id&n; *&n; *&t;Called when the PCI registration layer (or the IDE initialization)&n; *&t;finds a device matching our IDE device tables.&n; */
DECL|function|generic_init_one
r_static
r_int
id|__devinit
id|generic_init_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
id|ide_pci_device_t
op_star
id|d
op_assign
op_amp
id|generic_chipsets
(braket
id|id-&gt;driver_data
)braket
suffix:semicolon
id|u16
id|command
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device
op_ne
id|d-&gt;device
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|d-&gt;vendor
op_eq
id|PCI_VENDOR_ID_UMC
)paren
op_logical_and
(paren
id|d-&gt;device
op_eq
id|PCI_DEVICE_ID_UMC_UM8886A
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_amp
l_int|1
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* UM8886A/BF pair */
r_if
c_cond
(paren
(paren
id|d-&gt;vendor
op_eq
id|PCI_VENDOR_ID_OPTI
)paren
op_logical_and
(paren
id|d-&gt;device
op_eq
id|PCI_DEVICE_ID_OPTI_82C558
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_amp
l_int|1
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|command
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|command
op_amp
id|PCI_COMMAND_IO
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Skipping disabled %s IDE controller.&bslash;n&quot;
comma
id|d-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|generic_pci_tbl
r_static
r_struct
id|pci_device_id
id|generic_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_NS
comma
id|PCI_DEVICE_ID_NS_87410
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
id|PCI_VENDOR_ID_PCTECH
comma
id|PCI_DEVICE_ID_PCTECH_SAMURAI_IDE
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
(brace
id|PCI_VENDOR_ID_HOLTEK
comma
id|PCI_DEVICE_ID_HOLTEK_6565
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|2
)brace
comma
(brace
id|PCI_VENDOR_ID_UMC
comma
id|PCI_DEVICE_ID_UMC_UM8673F
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|3
)brace
comma
(brace
id|PCI_VENDOR_ID_UMC
comma
id|PCI_DEVICE_ID_UMC_UM8886A
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|4
)brace
comma
(brace
id|PCI_VENDOR_ID_UMC
comma
id|PCI_DEVICE_ID_UMC_UM8886BF
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|5
)brace
comma
(brace
id|PCI_VENDOR_ID_HINT
comma
id|PCI_DEVICE_ID_HINT_VXPROII_IDE
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|6
)brace
comma
(brace
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C561
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|7
)brace
comma
(brace
id|PCI_VENDOR_ID_OPTI
comma
id|PCI_DEVICE_ID_OPTI_82C558
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|8
)brace
comma
(brace
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8237_SATA
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|9
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|pci_driver
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PCI IDE&quot;
comma
dot
id|id_table
op_assign
id|generic_pci_tbl
comma
dot
id|probe
op_assign
id|generic_init_one
comma
)brace
suffix:semicolon
DECL|function|generic_ide_init
r_static
r_int
id|generic_ide_init
c_func
(paren
r_void
)paren
(brace
r_return
id|ide_pci_register_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|function|generic_ide_exit
r_static
r_void
id|generic_ide_exit
c_func
(paren
r_void
)paren
(brace
id|ide_pci_unregister_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|generic_ide_init
id|module_init
c_func
(paren
id|generic_ide_init
)paren
suffix:semicolon
DECL|variable|generic_ide_exit
id|module_exit
c_func
(paren
id|generic_ide_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andre Hedrick&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for generic PCI IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
