multiline_comment|/*&n; * Copyright (C) 2004 IBM Corporation&n; *&n; * Authors:&n; * Leendert van Doorn &lt;leendert@watson.ibm.com&gt;&n; * Dave Safford &lt;safford@watson.ibm.com&gt;&n; * Reiner Sailer &lt;sailer@watson.ibm.com&gt;&n; * Kylene Hall &lt;kjhall@us.ibm.com&gt;&n; *&n; * Maintained by: &lt;tpmdd_devel@lists.sourceforge.net&gt;&n; *&n; * Device driver for TCG/TCPA TPM (trusted platform module).&n; * Specifications at www.trustedcomputinggroup.org&t; &n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation, version 2 of the&n; * License.&n; * &n; */
macro_line|#include &quot;tpm.h&quot;
multiline_comment|/* Atmel definitions */
DECL|macro|TPM_ATML_BASE
mdefine_line|#define&t;TPM_ATML_BASE&t;&t;&t;0x400
multiline_comment|/* write status bits */
DECL|macro|ATML_STATUS_ABORT
mdefine_line|#define&t;ATML_STATUS_ABORT&t;&t;0x01
DECL|macro|ATML_STATUS_LASTBYTE
mdefine_line|#define&t;ATML_STATUS_LASTBYTE&t;&t;0x04
multiline_comment|/* read status bits */
DECL|macro|ATML_STATUS_BUSY
mdefine_line|#define&t;ATML_STATUS_BUSY&t;&t;0x01
DECL|macro|ATML_STATUS_DATA_AVAIL
mdefine_line|#define&t;ATML_STATUS_DATA_AVAIL&t;&t;0x02
DECL|macro|ATML_STATUS_REWRITE
mdefine_line|#define&t;ATML_STATUS_REWRITE&t;&t;0x04
DECL|function|tpm_atml_recv
r_static
r_int
id|tpm_atml_recv
c_func
(paren
r_struct
id|tpm_chip
op_star
id|chip
comma
id|u8
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|u8
id|status
comma
op_star
id|hdr
op_assign
id|buf
suffix:semicolon
id|u32
id|size
suffix:semicolon
r_int
id|i
suffix:semicolon
id|__be32
op_star
id|native_size
suffix:semicolon
multiline_comment|/* start reading header */
r_if
c_cond
(paren
id|count
OL
l_int|6
)paren
r_return
op_minus
id|EIO
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|inb
c_func
(paren
id|chip-&gt;vendor-&gt;base
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|ATML_STATUS_DATA_AVAIL
)paren
op_eq
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|chip-&gt;pci_dev-&gt;dev
comma
l_string|&quot;error reading header&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
op_star
id|buf
op_increment
op_assign
id|inb
c_func
(paren
id|chip-&gt;vendor-&gt;base
)paren
suffix:semicolon
)brace
multiline_comment|/* size of the data received */
id|native_size
op_assign
(paren
id|__force
id|__be32
op_star
)paren
(paren
id|hdr
op_plus
l_int|2
)paren
suffix:semicolon
id|size
op_assign
id|be32_to_cpu
c_func
(paren
op_star
id|native_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|size
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|chip-&gt;pci_dev-&gt;dev
comma
l_string|&quot;Recv size(%d) less than available space&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* clear the waiting data anyway */
id|status
op_assign
id|inb
c_func
(paren
id|chip-&gt;vendor-&gt;base
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|ATML_STATUS_DATA_AVAIL
)paren
op_eq
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|chip-&gt;pci_dev-&gt;dev
comma
l_string|&quot;error reading data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* read all the data available */
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|inb
c_func
(paren
id|chip-&gt;vendor-&gt;base
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|ATML_STATUS_DATA_AVAIL
)paren
op_eq
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|chip-&gt;pci_dev-&gt;dev
comma
l_string|&quot;error reading data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
op_star
id|buf
op_increment
op_assign
id|inb
c_func
(paren
id|chip-&gt;vendor-&gt;base
)paren
suffix:semicolon
)brace
multiline_comment|/* make sure data available is gone */
id|status
op_assign
id|inb
c_func
(paren
id|chip-&gt;vendor-&gt;base
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|ATML_STATUS_DATA_AVAIL
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|chip-&gt;pci_dev-&gt;dev
comma
l_string|&quot;data available is stuck&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
id|size
suffix:semicolon
)brace
DECL|function|tpm_atml_send
r_static
r_int
id|tpm_atml_send
c_func
(paren
r_struct
id|tpm_chip
op_star
id|chip
comma
id|u8
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|chip-&gt;pci_dev-&gt;dev
comma
l_string|&quot;tpm_atml_send: &quot;
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|chip-&gt;pci_dev-&gt;dev
comma
l_string|&quot;0x%x(%d) &quot;
comma
id|buf
(braket
id|i
)braket
comma
id|buf
(braket
id|i
)braket
)paren
suffix:semicolon
id|outb
c_func
(paren
id|buf
(braket
id|i
)braket
comma
id|chip-&gt;vendor-&gt;base
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|tpm_atml_cancel
r_static
r_void
id|tpm_atml_cancel
c_func
(paren
r_struct
id|tpm_chip
op_star
id|chip
)paren
(brace
id|outb
c_func
(paren
id|ATML_STATUS_ABORT
comma
id|chip-&gt;vendor-&gt;base
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|atmel_ops
r_static
r_struct
id|file_operations
id|atmel_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|open
op_assign
id|tpm_open
comma
dot
id|read
op_assign
id|tpm_read
comma
dot
id|write
op_assign
id|tpm_write
comma
dot
id|release
op_assign
id|tpm_release
comma
)brace
suffix:semicolon
DECL|variable|tpm_atmel
r_static
r_struct
id|tpm_vendor_specific
id|tpm_atmel
op_assign
(brace
dot
id|recv
op_assign
id|tpm_atml_recv
comma
dot
id|send
op_assign
id|tpm_atml_send
comma
dot
id|cancel
op_assign
id|tpm_atml_cancel
comma
dot
id|req_complete_mask
op_assign
id|ATML_STATUS_BUSY
op_or
id|ATML_STATUS_DATA_AVAIL
comma
dot
id|req_complete_val
op_assign
id|ATML_STATUS_DATA_AVAIL
comma
dot
id|base
op_assign
id|TPM_ATML_BASE
comma
dot
id|miscdev.fops
op_assign
op_amp
id|atmel_ops
comma
)brace
suffix:semicolon
DECL|function|tpm_atml_init
r_static
r_int
id|__devinit
id|tpm_atml_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci_dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|pci_id
)paren
(brace
id|u8
id|version
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|pci_dev
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|tpm_lpc_bus_init
c_func
(paren
id|pci_dev
comma
id|TPM_ATML_BASE
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
multiline_comment|/* verify that it is an Atmel part */
r_if
c_cond
(paren
id|tpm_read_index
c_func
(paren
l_int|4
)paren
op_ne
l_char|&squot;A&squot;
op_logical_or
id|tpm_read_index
c_func
(paren
l_int|5
)paren
op_ne
l_char|&squot;T&squot;
op_logical_or
id|tpm_read_index
c_func
(paren
l_int|6
)paren
op_ne
l_char|&squot;M&squot;
op_logical_or
id|tpm_read_index
c_func
(paren
l_int|7
)paren
op_ne
l_char|&squot;L&squot;
)paren
(brace
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
multiline_comment|/* query chip for its version number */
r_if
c_cond
(paren
(paren
id|version
(braket
l_int|0
)braket
op_assign
id|tpm_read_index
c_func
(paren
l_int|0x00
)paren
)paren
op_ne
l_int|0xFF
)paren
(brace
id|version
(braket
l_int|1
)braket
op_assign
id|tpm_read_index
c_func
(paren
l_int|0x01
)paren
suffix:semicolon
id|version
(braket
l_int|2
)braket
op_assign
id|tpm_read_index
c_func
(paren
l_int|0x02
)paren
suffix:semicolon
id|version
(braket
l_int|3
)braket
op_assign
id|tpm_read_index
c_func
(paren
l_int|0x03
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev_info
c_func
(paren
op_amp
id|pci_dev-&gt;dev
comma
l_string|&quot;version query failed&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|tpm_register_hardware
c_func
(paren
id|pci_dev
comma
op_amp
id|tpm_atmel
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out_err
suffix:semicolon
id|dev_info
c_func
(paren
op_amp
id|pci_dev-&gt;dev
comma
l_string|&quot;Atmel TPM version %d.%d.%d.%d&bslash;n&quot;
comma
id|version
(braket
l_int|0
)braket
comma
id|version
(braket
l_int|1
)braket
comma
id|version
(braket
l_int|2
)braket
comma
id|version
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_err
suffix:colon
id|pci_disable_device
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|tpm_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801BA_0
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801CA_12
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801DB_0
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801DB_12
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801EB_0
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_8111_LPC
)paren
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|tpm_pci_tbl
)paren
suffix:semicolon
DECL|variable|atmel_pci_driver
r_static
r_struct
id|pci_driver
id|atmel_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tpm_atmel&quot;
comma
dot
id|id_table
op_assign
id|tpm_pci_tbl
comma
dot
id|probe
op_assign
id|tpm_atml_init
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|tpm_remove
)paren
comma
dot
id|suspend
op_assign
id|tpm_pm_suspend
comma
dot
id|resume
op_assign
id|tpm_pm_resume
comma
)brace
suffix:semicolon
DECL|function|init_atmel
r_static
r_int
id|__init
id|init_atmel
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_register_driver
c_func
(paren
op_amp
id|atmel_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|cleanup_atmel
r_static
r_void
id|__exit
id|cleanup_atmel
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|atmel_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|init_atmel
id|module_init
c_func
(paren
id|init_atmel
)paren
suffix:semicolon
DECL|variable|cleanup_atmel
id|module_exit
c_func
(paren
id|cleanup_atmel
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Leendert van Doorn (leendert@watson.ibm.com)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;TPM Driver&quot;
)paren
suffix:semicolon
id|MODULE_VERSION
c_func
(paren
l_string|&quot;2.0&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
