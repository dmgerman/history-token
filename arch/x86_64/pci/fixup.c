multiline_comment|/*&n; * Exceptions for specific devices. Usually work-arounds for fatal design flaws.&n; *&n;&n;Short list on x86-64........so far. &n;&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|function|pci_fixup_ncr53c810
r_static
r_void
id|__devinit
id|pci_fixup_ncr53c810
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
multiline_comment|/*&n;&t; * NCR 53C810 returns class code 0 (at least on some systems).&n;&t; * Fix class to be PCI_CLASS_STORAGE_SCSI&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|d
op_member_access_from_pointer
r_class
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: fixing NCR 53C810 class code for %s&bslash;n&quot;
comma
id|d-&gt;slot_name
)paren
suffix:semicolon
id|d
op_member_access_from_pointer
r_class
op_assign
id|PCI_CLASS_STORAGE_SCSI
op_lshift
l_int|8
suffix:semicolon
)brace
)brace
DECL|function|pci_fixup_ide_bases
r_static
r_void
id|__devinit
id|pci_fixup_ide_bases
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * PCI IDE controllers use non-standard I/O port decoding, respect it.&n;&t; */
r_if
c_cond
(paren
(paren
id|d
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_STORAGE_IDE
)paren
r_return
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: IDE base address fixup for %s&bslash;n&quot;
comma
id|d-&gt;slot_name
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|d-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r-&gt;start
op_amp
op_complement
l_int|0x80
)paren
op_eq
l_int|0x374
)paren
(brace
id|r-&gt;start
op_or_assign
l_int|2
suffix:semicolon
id|r-&gt;end
op_assign
id|r-&gt;start
suffix:semicolon
)brace
)brace
)brace
DECL|function|pci_fixup_ide_trash
r_static
r_void
id|__devinit
id|pci_fixup_ide_trash
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * There exist PCI IDE controllers which have utter garbage&n;&t; * in first four base registers. Ignore that.&n;&t; */
id|DBG
c_func
(paren
l_string|&quot;PCI: IDE base address trash cleared for %s&bslash;n&quot;
comma
id|d-&gt;slot_name
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|d-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
id|d-&gt;resource
(braket
id|i
)braket
dot
id|end
op_assign
id|d-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|pci_fixup_ide_bases
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_NCR
comma
id|PCI_DEVICE_ID_NCR_53C810
comma
id|pci_fixup_ncr53c810
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
eof
