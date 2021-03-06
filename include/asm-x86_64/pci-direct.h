macro_line|#ifndef ASM_PCI_DIRECT_H
DECL|macro|ASM_PCI_DIRECT_H
mdefine_line|#define ASM_PCI_DIRECT_H 1
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Direct PCI access. This is used for PCI accesses in early boot before&n;   the PCI subsystem works. */
DECL|macro|PDprintk
mdefine_line|#define PDprintk(x...)
DECL|function|read_pci_config
r_static
r_inline
id|u32
id|read_pci_config
c_func
(paren
id|u8
id|bus
comma
id|u8
id|slot
comma
id|u8
id|func
comma
id|u8
id|offset
)paren
(brace
id|u32
id|v
suffix:semicolon
id|outl
c_func
(paren
l_int|0x80000000
op_or
(paren
id|bus
op_lshift
l_int|16
)paren
op_or
(paren
id|slot
op_lshift
l_int|11
)paren
op_or
(paren
id|func
op_lshift
l_int|8
)paren
op_or
id|offset
comma
l_int|0xcf8
)paren
suffix:semicolon
id|v
op_assign
id|inl
c_func
(paren
l_int|0xcfc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
op_ne
l_int|0xffffffff
)paren
id|PDprintk
c_func
(paren
l_string|&quot;%x reading 4 from %x: %x&bslash;n&quot;
comma
id|slot
comma
id|offset
comma
id|v
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|read_pci_config_byte
r_static
r_inline
id|u8
id|read_pci_config_byte
c_func
(paren
id|u8
id|bus
comma
id|u8
id|slot
comma
id|u8
id|func
comma
id|u8
id|offset
)paren
(brace
id|u8
id|v
suffix:semicolon
id|outl
c_func
(paren
l_int|0x80000000
op_or
(paren
id|bus
op_lshift
l_int|16
)paren
op_or
(paren
id|slot
op_lshift
l_int|11
)paren
op_or
(paren
id|func
op_lshift
l_int|8
)paren
op_or
id|offset
comma
l_int|0xcf8
)paren
suffix:semicolon
id|v
op_assign
id|inb
c_func
(paren
l_int|0xcfc
op_plus
(paren
id|offset
op_amp
l_int|3
)paren
)paren
suffix:semicolon
id|PDprintk
c_func
(paren
l_string|&quot;%x reading 1 from %x: %x&bslash;n&quot;
comma
id|slot
comma
id|offset
comma
id|v
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|read_pci_config_16
r_static
r_inline
id|u16
id|read_pci_config_16
c_func
(paren
id|u8
id|bus
comma
id|u8
id|slot
comma
id|u8
id|func
comma
id|u8
id|offset
)paren
(brace
id|u16
id|v
suffix:semicolon
id|outl
c_func
(paren
l_int|0x80000000
op_or
(paren
id|bus
op_lshift
l_int|16
)paren
op_or
(paren
id|slot
op_lshift
l_int|11
)paren
op_or
(paren
id|func
op_lshift
l_int|8
)paren
op_or
id|offset
comma
l_int|0xcf8
)paren
suffix:semicolon
id|v
op_assign
id|inw
c_func
(paren
l_int|0xcfc
op_plus
(paren
id|offset
op_amp
l_int|2
)paren
)paren
suffix:semicolon
id|PDprintk
c_func
(paren
l_string|&quot;%x reading 2 from %x: %x&bslash;n&quot;
comma
id|slot
comma
id|offset
comma
id|v
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|write_pci_config
r_static
r_inline
r_void
id|write_pci_config
c_func
(paren
id|u8
id|bus
comma
id|u8
id|slot
comma
id|u8
id|func
comma
id|u8
id|offset
comma
id|u32
id|val
)paren
(brace
id|PDprintk
c_func
(paren
l_string|&quot;%x writing to %x: %x&bslash;n&quot;
comma
id|slot
comma
id|offset
comma
id|val
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x80000000
op_or
(paren
id|bus
op_lshift
l_int|16
)paren
op_or
(paren
id|slot
op_lshift
l_int|11
)paren
op_or
(paren
id|func
op_lshift
l_int|8
)paren
op_or
id|offset
comma
l_int|0xcf8
)paren
suffix:semicolon
id|outl
c_func
(paren
id|val
comma
l_int|0xcfc
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
