multiline_comment|/*&n; * QLogic ISP6322 device driver for Linux 2.6.x&n; * Copyright (C) 2003-2004 QLogic Corporation (www.qlogic.com)&n; *&n; * Released under GPL v2.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;qla_def.h&quot;
DECL|variable|qla_driver_name
r_static
r_char
id|qla_driver_name
(braket
)braket
op_assign
l_string|&quot;qla6322&quot;
suffix:semicolon
r_extern
r_int
r_char
id|fw2322flx_version
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|fw2322flx_version_str
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|fw2322flx_addr01
suffix:semicolon
r_extern
r_int
r_int
id|fw2322flx_code01
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|fw2322flx_length01
suffix:semicolon
r_extern
r_int
r_int
id|rseqflx_code_addr01
suffix:semicolon
r_extern
r_int
r_int
id|rseqflx_code01
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|rseqflx_code_length01
suffix:semicolon
r_extern
r_int
r_int
id|xseqflx_code_addr01
suffix:semicolon
r_extern
r_int
r_int
id|xseqflx_code01
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|xseqflx_code_length01
suffix:semicolon
DECL|variable|qla_fw_tbl
r_static
r_struct
id|qla_fw_info
id|qla_fw_tbl
(braket
)braket
op_assign
(brace
(brace
dot
id|addressing
op_assign
id|FW_INFO_ADDR_NORMAL
comma
dot
id|fwcode
op_assign
op_amp
id|fw2322flx_code01
(braket
l_int|0
)braket
comma
dot
id|fwlen
op_assign
op_amp
id|fw2322flx_length01
comma
dot
id|fwstart
op_assign
op_amp
id|fw2322flx_addr01
comma
)brace
comma
(brace
dot
id|addressing
op_assign
id|FW_INFO_ADDR_EXTENDED
comma
dot
id|fwcode
op_assign
op_amp
id|rseqflx_code01
(braket
l_int|0
)braket
comma
dot
id|fwlen
op_assign
op_amp
id|rseqflx_code_length01
comma
dot
id|lfwstart
op_assign
op_amp
id|rseqflx_code_addr01
comma
)brace
comma
(brace
dot
id|addressing
op_assign
id|FW_INFO_ADDR_EXTENDED
comma
dot
id|fwcode
op_assign
op_amp
id|xseqflx_code01
(braket
l_int|0
)braket
comma
dot
id|fwlen
op_assign
op_amp
id|xseqflx_code_length01
comma
dot
id|lfwstart
op_assign
op_amp
id|xseqflx_code_addr01
comma
)brace
comma
(brace
id|FW_INFO_ADDR_NOMORE
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|qla_board_tbl
r_static
r_struct
id|qla_board_info
id|qla_board_tbl
(braket
)braket
op_assign
(brace
(brace
dot
id|drv_name
op_assign
id|qla_driver_name
comma
dot
id|isp_name
op_assign
l_string|&quot;ISP6322&quot;
comma
dot
id|fw_info
op_assign
id|qla_fw_tbl
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|qla6322_pci_tbl
r_static
r_struct
id|pci_device_id
id|qla6322_pci_tbl
(braket
)braket
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_QLOGIC
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_QLOGIC_ISP6322
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
dot
id|driver_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|qla_board_tbl
(braket
l_int|0
)braket
comma
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|qla6322_pci_tbl
)paren
suffix:semicolon
r_static
r_int
id|__devinit
DECL|function|qla6322_probe_one
id|qla6322_probe_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_return
id|qla2x00_probe_one
c_func
(paren
id|pdev
comma
(paren
r_struct
id|qla_board_info
op_star
)paren
id|id-&gt;driver_data
)paren
suffix:semicolon
)brace
r_static
r_void
id|__devexit
DECL|function|qla6322_remove_one
id|qla6322_remove_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|qla2x00_remove_one
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
DECL|variable|qla6322_pci_driver
r_static
r_struct
id|pci_driver
id|qla6322_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;qla6322&quot;
comma
dot
id|id_table
op_assign
id|qla6322_pci_tbl
comma
dot
id|probe
op_assign
id|qla6322_probe_one
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|qla6322_remove_one
)paren
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|qla6322_init
id|qla6322_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|qla6322_pci_driver
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|qla6322_exit
id|qla6322_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|qla6322_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|qla6322_init
id|module_init
c_func
(paren
id|qla6322_init
)paren
suffix:semicolon
DECL|variable|qla6322_exit
id|module_exit
c_func
(paren
id|qla6322_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;QLogic Corporation&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;QLogic ISP6322 FC-SCSI Host Bus Adapter driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
