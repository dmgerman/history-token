multiline_comment|/*&n; * BIOS32 and PCI BIOS handling.&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|PCIBIOS_PCI_FUNCTION_ID
mdefine_line|#define PCIBIOS_PCI_FUNCTION_ID &t;0xb1XX
DECL|macro|PCIBIOS_PCI_BIOS_PRESENT
mdefine_line|#define PCIBIOS_PCI_BIOS_PRESENT &t;0xb101
DECL|macro|PCIBIOS_FIND_PCI_DEVICE
mdefine_line|#define PCIBIOS_FIND_PCI_DEVICE&t;&t;0xb102
DECL|macro|PCIBIOS_FIND_PCI_CLASS_CODE
mdefine_line|#define PCIBIOS_FIND_PCI_CLASS_CODE&t;0xb103
DECL|macro|PCIBIOS_GENERATE_SPECIAL_CYCLE
mdefine_line|#define PCIBIOS_GENERATE_SPECIAL_CYCLE&t;0xb106
DECL|macro|PCIBIOS_READ_CONFIG_BYTE
mdefine_line|#define PCIBIOS_READ_CONFIG_BYTE&t;0xb108
DECL|macro|PCIBIOS_READ_CONFIG_WORD
mdefine_line|#define PCIBIOS_READ_CONFIG_WORD&t;0xb109
DECL|macro|PCIBIOS_READ_CONFIG_DWORD
mdefine_line|#define PCIBIOS_READ_CONFIG_DWORD&t;0xb10a
DECL|macro|PCIBIOS_WRITE_CONFIG_BYTE
mdefine_line|#define PCIBIOS_WRITE_CONFIG_BYTE&t;0xb10b
DECL|macro|PCIBIOS_WRITE_CONFIG_WORD
mdefine_line|#define PCIBIOS_WRITE_CONFIG_WORD&t;0xb10c
DECL|macro|PCIBIOS_WRITE_CONFIG_DWORD
mdefine_line|#define PCIBIOS_WRITE_CONFIG_DWORD&t;0xb10d
DECL|macro|PCIBIOS_GET_ROUTING_OPTIONS
mdefine_line|#define PCIBIOS_GET_ROUTING_OPTIONS&t;0xb10e
DECL|macro|PCIBIOS_SET_PCI_HW_INT
mdefine_line|#define PCIBIOS_SET_PCI_HW_INT&t;&t;0xb10f
multiline_comment|/* BIOS32 signature: &quot;_32_&quot; */
DECL|macro|BIOS32_SIGNATURE
mdefine_line|#define BIOS32_SIGNATURE&t;((&squot;_&squot; &lt;&lt; 0) + (&squot;3&squot; &lt;&lt; 8) + (&squot;2&squot; &lt;&lt; 16) + (&squot;_&squot; &lt;&lt; 24))
multiline_comment|/* PCI signature: &quot;PCI &quot; */
DECL|macro|PCI_SIGNATURE
mdefine_line|#define PCI_SIGNATURE&t;&t;((&squot;P&squot; &lt;&lt; 0) + (&squot;C&squot; &lt;&lt; 8) + (&squot;I&squot; &lt;&lt; 16) + (&squot; &squot; &lt;&lt; 24))
multiline_comment|/* PCI service signature: &quot;$PCI&quot; */
DECL|macro|PCI_SERVICE
mdefine_line|#define PCI_SERVICE&t;&t;((&squot;$&squot; &lt;&lt; 0) + (&squot;P&squot; &lt;&lt; 8) + (&squot;C&squot; &lt;&lt; 16) + (&squot;I&squot; &lt;&lt; 24))
multiline_comment|/* PCI BIOS hardware mechanism flags */
DECL|macro|PCIBIOS_HW_TYPE1
mdefine_line|#define PCIBIOS_HW_TYPE1&t;&t;0x01
DECL|macro|PCIBIOS_HW_TYPE2
mdefine_line|#define PCIBIOS_HW_TYPE2&t;&t;0x02
DECL|macro|PCIBIOS_HW_TYPE1_SPEC
mdefine_line|#define PCIBIOS_HW_TYPE1_SPEC&t;&t;0x10
DECL|macro|PCIBIOS_HW_TYPE2_SPEC
mdefine_line|#define PCIBIOS_HW_TYPE2_SPEC&t;&t;0x20
multiline_comment|/*&n; * This is the standard structure used to identify the entry point&n; * to the BIOS32 Service Directory, as documented in&n; * &t;Standard BIOS 32-bit Service Directory Proposal&n; * &t;Revision 0.4 May 24, 1993&n; * &t;Phoenix Technologies Ltd.&n; *&t;Norwood, MA&n; * and the PCI BIOS specification.&n; */
DECL|union|bios32
r_union
id|bios32
(brace
r_struct
(brace
DECL|member|signature
r_int
r_int
id|signature
suffix:semicolon
multiline_comment|/* _32_ */
DECL|member|entry
r_int
r_int
id|entry
suffix:semicolon
multiline_comment|/* 32 bit physical address */
DECL|member|revision
r_int
r_char
id|revision
suffix:semicolon
multiline_comment|/* Revision level, 0 */
DECL|member|length
r_int
r_char
id|length
suffix:semicolon
multiline_comment|/* Length in paragraphs should be 01 */
DECL|member|checksum
r_int
r_char
id|checksum
suffix:semicolon
multiline_comment|/* All bytes must add up to zero */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Must be zero */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|member|chars
r_char
id|chars
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Physical address of the service directory.  I don&squot;t know if we&squot;re&n; * allowed to have more than one of these or not, so just in case&n; * we&squot;ll make pcibios_present() take a memory start parameter and store&n; * the array there.&n; */
r_static
r_struct
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|segment
r_int
r_int
id|segment
suffix:semicolon
DECL|variable|bios32_indirect
)brace
id|bios32_indirect
op_assign
(brace
l_int|0
comma
id|__KERNEL_CS
)brace
suffix:semicolon
multiline_comment|/*&n; * Returns the entry point for the given service, NULL on error&n; */
DECL|function|bios32_service
r_static
r_int
r_int
id|bios32_service
c_func
(paren
r_int
r_int
id|service
)paren
(brace
r_int
r_char
id|return_code
suffix:semicolon
multiline_comment|/* %al */
r_int
r_int
id|address
suffix:semicolon
multiline_comment|/* %ebx */
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* %ecx */
r_int
r_int
id|entry
suffix:semicolon
multiline_comment|/* %edx */
r_int
r_int
id|flags
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;lcall *(%%edi); cld&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|return_code
)paren
comma
l_string|&quot;=b&quot;
(paren
id|address
)paren
comma
l_string|&quot;=c&quot;
(paren
id|length
)paren
comma
l_string|&quot;=d&quot;
(paren
id|entry
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|service
)paren
comma
l_string|&quot;1&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;D&quot;
(paren
op_amp
id|bios32_indirect
)paren
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|return_code
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
id|address
op_plus
id|entry
suffix:semicolon
r_case
l_int|0x80
suffix:colon
multiline_comment|/* Not present */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;bios32_service(0x%lx): not present&bslash;n&quot;
comma
id|service
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Shouldn&squot;t happen */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;bios32_service(0x%lx): returned 0x%x -- BIOS bug!&bslash;n&quot;
comma
id|service
comma
id|return_code
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_static
r_struct
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|segment
r_int
r_int
id|segment
suffix:semicolon
DECL|variable|pci_indirect
)brace
id|pci_indirect
op_assign
(brace
l_int|0
comma
id|__KERNEL_CS
)brace
suffix:semicolon
DECL|variable|pci_bios_present
r_static
r_int
id|pci_bios_present
suffix:semicolon
DECL|function|check_pcibios
r_static
r_int
id|__devinit
id|check_pcibios
c_func
(paren
r_void
)paren
(brace
id|u32
id|signature
comma
id|eax
comma
id|ebx
comma
id|ecx
suffix:semicolon
id|u8
id|status
comma
id|major_ver
comma
id|minor_ver
comma
id|hw_mech
suffix:semicolon
r_int
r_int
id|flags
comma
id|pcibios_entry
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pcibios_entry
op_assign
id|bios32_service
c_func
(paren
id|PCI_SERVICE
)paren
)paren
)paren
(brace
id|pci_indirect.address
op_assign
id|pcibios_entry
op_plus
id|PAGE_OFFSET
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;lcall *(%%edi); cld&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;xor %%ah, %%ah&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|signature
)paren
comma
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=b&quot;
(paren
id|ebx
)paren
comma
l_string|&quot;=c&quot;
(paren
id|ecx
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|PCIBIOS_PCI_BIOS_PRESENT
)paren
comma
l_string|&quot;D&quot;
(paren
op_amp
id|pci_indirect
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|status
op_assign
(paren
id|eax
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|hw_mech
op_assign
id|eax
op_amp
l_int|0xff
suffix:semicolon
id|major_ver
op_assign
(paren
id|ebx
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|minor_ver
op_assign
id|ebx
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|pcibios_last_bus
OL
l_int|0
)paren
id|pcibios_last_bus
op_assign
id|ecx
op_amp
l_int|0xff
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: BIOS probe returned s=%02x hw=%02x ver=%02x.%02x l=%02x&bslash;n&quot;
comma
id|status
comma
id|hw_mech
comma
id|major_ver
comma
id|minor_ver
comma
id|pcibios_last_bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_logical_or
id|signature
op_ne
id|PCI_SIGNATURE
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;PCI: BIOS BUG #%x[%08x] found&bslash;n&quot;
comma
id|status
comma
id|signature
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: PCI BIOS revision %x.%02x entry at 0x%lx, last bus=%d&bslash;n&quot;
comma
id|major_ver
comma
id|minor_ver
comma
id|pcibios_entry
comma
id|pcibios_last_bus
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI_DIRECT
r_if
c_cond
(paren
op_logical_neg
(paren
id|hw_mech
op_amp
id|PCIBIOS_HW_TYPE1
)paren
)paren
id|pci_probe
op_and_assign
op_complement
id|PCI_PROBE_CONF1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hw_mech
op_amp
id|PCIBIOS_HW_TYPE2
)paren
)paren
id|pci_probe
op_and_assign
op_complement
id|PCI_PROBE_CONF2
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_bios_find_device
r_static
r_int
id|__devinit
id|pci_bios_find_device
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device_id
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus
comma
r_int
r_char
op_star
id|device_fn
)paren
(brace
r_int
r_int
id|bx
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;lcall *(%%edi); cld&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;xor %%ah, %%ah&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=b&quot;
(paren
id|bx
)paren
comma
l_string|&quot;=a&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|PCIBIOS_FIND_PCI_DEVICE
)paren
comma
l_string|&quot;c&quot;
(paren
id|device_id
)paren
comma
l_string|&quot;d&quot;
(paren
id|vendor
)paren
comma
l_string|&quot;S&quot;
(paren
(paren
r_int
)paren
id|index
)paren
comma
l_string|&quot;D&quot;
(paren
op_amp
id|pci_indirect
)paren
)paren
suffix:semicolon
op_star
id|bus
op_assign
(paren
id|bx
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
op_star
id|device_fn
op_assign
id|bx
op_amp
l_int|0xff
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
id|ret
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
suffix:semicolon
)brace
DECL|function|pci_bios_read
r_static
r_int
id|pci_bios_read
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
op_star
id|value
)paren
(brace
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|bx
op_assign
(paren
(paren
id|bus
op_lshift
l_int|8
)paren
op_or
(paren
id|dev
op_lshift
l_int|3
)paren
op_or
id|fn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|dev
OG
l_int|31
)paren
op_logical_or
(paren
id|fn
OG
l_int|7
)paren
op_logical_or
(paren
id|reg
OG
l_int|255
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;lcall *(%%esi); cld&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;xor %%ah, %%ah&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=c&quot;
(paren
op_star
id|value
)paren
comma
l_string|&quot;=a&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|PCIBIOS_READ_CONFIG_BYTE
)paren
comma
l_string|&quot;b&quot;
(paren
id|bx
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|reg
)paren
comma
l_string|&quot;S&quot;
(paren
op_amp
id|pci_indirect
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;lcall *(%%esi); cld&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;xor %%ah, %%ah&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=c&quot;
(paren
op_star
id|value
)paren
comma
l_string|&quot;=a&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|PCIBIOS_READ_CONFIG_WORD
)paren
comma
l_string|&quot;b&quot;
(paren
id|bx
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|reg
)paren
comma
l_string|&quot;S&quot;
(paren
op_amp
id|pci_indirect
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;lcall *(%%esi); cld&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;xor %%ah, %%ah&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=c&quot;
(paren
op_star
id|value
)paren
comma
l_string|&quot;=a&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|PCIBIOS_READ_CONFIG_DWORD
)paren
comma
l_string|&quot;b&quot;
(paren
id|bx
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|reg
)paren
comma
l_string|&quot;S&quot;
(paren
op_amp
id|pci_indirect
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
(paren
id|result
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|pci_bios_write
r_static
r_int
id|pci_bios_write
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
id|value
)paren
(brace
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|bx
op_assign
(paren
(paren
id|bus
op_lshift
l_int|8
)paren
op_or
(paren
id|dev
op_lshift
l_int|3
)paren
op_or
id|fn
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|dev
OG
l_int|31
)paren
op_logical_or
(paren
id|fn
OG
l_int|7
)paren
op_logical_or
(paren
id|reg
OG
l_int|255
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;lcall *(%%esi); cld&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;xor %%ah, %%ah&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|PCIBIOS_WRITE_CONFIG_BYTE
)paren
comma
l_string|&quot;c&quot;
(paren
id|value
)paren
comma
l_string|&quot;b&quot;
(paren
id|bx
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|reg
)paren
comma
l_string|&quot;S&quot;
(paren
op_amp
id|pci_indirect
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;lcall *(%%esi); cld&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;xor %%ah, %%ah&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|PCIBIOS_WRITE_CONFIG_WORD
)paren
comma
l_string|&quot;c&quot;
(paren
id|value
)paren
comma
l_string|&quot;b&quot;
(paren
id|bx
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|reg
)paren
comma
l_string|&quot;S&quot;
(paren
op_amp
id|pci_indirect
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;lcall *(%%esi); cld&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;xor %%ah, %%ah&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|PCIBIOS_WRITE_CONFIG_DWORD
)paren
comma
l_string|&quot;c&quot;
(paren
id|value
)paren
comma
l_string|&quot;b&quot;
(paren
id|bx
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|reg
)paren
comma
l_string|&quot;S&quot;
(paren
op_amp
id|pci_indirect
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
(paren
id|result
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|pci_bios_read_config_byte
r_static
r_int
id|pci_bios_read_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
op_star
id|value
)paren
(brace
r_int
id|result
suffix:semicolon
id|u32
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|result
op_assign
id|pci_bios_read
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|1
comma
op_amp
id|data
)paren
suffix:semicolon
op_star
id|value
op_assign
(paren
id|u8
)paren
id|data
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_bios_read_config_word
r_static
r_int
id|pci_bios_read_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
op_star
id|value
)paren
(brace
r_int
id|result
suffix:semicolon
id|u32
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|result
op_assign
id|pci_bios_read
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|2
comma
op_amp
id|data
)paren
suffix:semicolon
op_star
id|value
op_assign
(paren
id|u16
)paren
id|data
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_bios_read_config_dword
r_static
r_int
id|pci_bios_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
op_star
id|value
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|pci_bios_read
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|4
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pci_bios_write_config_byte
r_static
r_int
id|pci_bios_write_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u8
id|value
)paren
(brace
r_return
id|pci_bios_write
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|1
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pci_bios_write_config_word
r_static
r_int
id|pci_bios_write_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u16
id|value
)paren
(brace
r_return
id|pci_bios_write
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|2
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pci_bios_write_config_dword
r_static
r_int
id|pci_bios_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
id|u32
id|value
)paren
(brace
r_return
id|pci_bios_write
c_func
(paren
l_int|0
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|where
comma
l_int|4
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function table for BIOS32 access&n; */
DECL|variable|pci_bios_access
r_static
r_struct
id|pci_ops
id|pci_bios_access
op_assign
(brace
id|pci_bios_read_config_byte
comma
id|pci_bios_read_config_word
comma
id|pci_bios_read_config_dword
comma
id|pci_bios_write_config_byte
comma
id|pci_bios_write_config_word
comma
id|pci_bios_write_config_dword
)brace
suffix:semicolon
multiline_comment|/*&n; * Try to find PCI BIOS.&n; */
DECL|function|pci_find_bios
r_static
r_struct
id|pci_ops
op_star
id|__devinit
id|pci_find_bios
c_func
(paren
r_void
)paren
(brace
r_union
id|bios32
op_star
id|check
suffix:semicolon
r_int
r_char
id|sum
suffix:semicolon
r_int
id|i
comma
id|length
suffix:semicolon
multiline_comment|/*&n;&t; * Follow the standard procedure for locating the BIOS32 Service&n;&t; * directory by scanning the permissible address range from&n;&t; * 0xe0000 through 0xfffff for a valid BIOS32 structure.&n;&t; */
r_for
c_loop
(paren
id|check
op_assign
(paren
r_union
id|bios32
op_star
)paren
id|__va
c_func
(paren
l_int|0xe0000
)paren
suffix:semicolon
id|check
op_le
(paren
r_union
id|bios32
op_star
)paren
id|__va
c_func
(paren
l_int|0xffff0
)paren
suffix:semicolon
op_increment
id|check
)paren
(brace
r_if
c_cond
(paren
id|check-&gt;fields.signature
op_ne
id|BIOS32_SIGNATURE
)paren
r_continue
suffix:semicolon
id|length
op_assign
id|check-&gt;fields.length
op_star
l_int|16
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|length
)paren
r_continue
suffix:semicolon
id|sum
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
id|length
suffix:semicolon
op_increment
id|i
)paren
id|sum
op_add_assign
id|check-&gt;chars
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sum
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|check-&gt;fields.revision
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: unsupported BIOS32 revision %d at 0x%p&bslash;n&quot;
comma
id|check-&gt;fields.revision
comma
id|check
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot;PCI: BIOS32 Service Directory structure at 0x%p&bslash;n&quot;
comma
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check-&gt;fields.entry
op_ge
l_int|0x100000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: BIOS32 entry (0x%p) in high memory, cannot use.&bslash;n&quot;
comma
id|check
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|bios32_entry
op_assign
id|check-&gt;fields.entry
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: BIOS32 Service Directory entry at 0x%lx&bslash;n&quot;
comma
id|bios32_entry
)paren
suffix:semicolon
id|bios32_indirect.address
op_assign
id|bios32_entry
op_plus
id|PAGE_OFFSET
suffix:semicolon
r_if
c_cond
(paren
id|check_pcibios
c_func
(paren
)paren
)paren
r_return
op_amp
id|pci_bios_access
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/* Hopefully more than one BIOS32 cannot happen... */
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Sort the device list according to PCI BIOS. Nasty hack, but since some&n; * fool forgot to define the `correct&squot; device order in the PCI BIOS specs&n; * and we want to be (possibly bug-to-bug ;-]) compatible with older kernels&n; * which used BIOS ordering, we are bound to do this...&n; */
DECL|function|pcibios_sort
r_void
id|__devinit
id|pcibios_sort
c_func
(paren
r_void
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|sorted_devices
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
comma
op_star
id|d
suffix:semicolon
r_int
id|idx
comma
id|found
suffix:semicolon
r_int
r_char
id|bus
comma
id|devfn
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: Sorting device list...&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|pci_devices
)paren
)paren
(brace
id|ln
op_assign
id|pci_devices.next
suffix:semicolon
id|dev
op_assign
id|pci_dev_g
c_func
(paren
id|ln
)paren
suffix:semicolon
id|idx
op_assign
id|found
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|pci_bios_find_device
c_func
(paren
id|dev-&gt;vendor
comma
id|dev-&gt;device
comma
id|idx
comma
op_amp
id|bus
comma
op_amp
id|devfn
)paren
op_eq
id|PCIBIOS_SUCCESSFUL
)paren
(brace
id|idx
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|ln
op_assign
id|pci_devices.next
suffix:semicolon
id|ln
op_ne
op_amp
id|pci_devices
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
id|d
op_assign
id|pci_dev_g
c_func
(paren
id|ln
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;bus-&gt;number
op_eq
id|bus
op_logical_and
id|d-&gt;devfn
op_eq
id|devfn
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|d-&gt;global_list
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|d-&gt;global_list
comma
op_amp
id|sorted_devices
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d
op_eq
id|dev
)paren
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ln
op_eq
op_amp
id|pci_devices
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: BIOS reporting unknown device %02x:%02x&bslash;n&quot;
comma
id|bus
comma
id|devfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * We must not continue scanning as several buggy BIOSes&n;&t;&t;&t;&t; * return garbage after the last device. Grr.&n;&t;&t;&t;&t; */
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: Device %02x:%02x not found by BIOS&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dev-&gt;global_list
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;global_list
comma
op_amp
id|sorted_devices
)paren
suffix:semicolon
)brace
)brace
id|list_splice
c_func
(paren
op_amp
id|sorted_devices
comma
op_amp
id|pci_devices
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  BIOS Functions for IRQ Routing&n; */
DECL|struct|irq_routing_options
r_struct
id|irq_routing_options
(brace
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|table
r_struct
id|irq_info
op_star
id|table
suffix:semicolon
DECL|member|segment
id|u16
id|segment
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|function|pcibios_get_irq_routing_table
r_struct
id|irq_routing_table
op_star
id|__devinit
id|pcibios_get_irq_routing_table
c_func
(paren
r_void
)paren
(brace
r_struct
id|irq_routing_options
id|opt
suffix:semicolon
r_struct
id|irq_routing_table
op_star
id|rt
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
comma
id|map
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_bios_present
)paren
r_return
l_int|NULL
suffix:semicolon
id|page
op_assign
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
l_int|NULL
suffix:semicolon
id|opt.table
op_assign
(paren
r_struct
id|irq_info
op_star
)paren
id|page
suffix:semicolon
id|opt.size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|opt.segment
op_assign
id|__KERNEL_DS
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: Fetching IRQ routing table... &quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;push %%es&bslash;n&bslash;t&quot;
l_string|&quot;push %%ds&bslash;n&bslash;t&quot;
l_string|&quot;pop  %%es&bslash;n&bslash;t&quot;
l_string|&quot;lcall *(%%esi); cld&bslash;n&bslash;t&quot;
l_string|&quot;pop %%es&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;xor %%ah, %%ah&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=b&quot;
(paren
id|map
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|PCIBIOS_GET_ROUTING_OPTIONS
)paren
comma
l_string|&quot;1&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
op_amp
id|opt
)paren
comma
l_string|&quot;S&quot;
(paren
op_amp
id|pci_indirect
)paren
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;OK  ret=%d, size=%d, map=%x&bslash;n&quot;
comma
id|ret
comma
id|opt.size
comma
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_amp
l_int|0xff00
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Error %02x when fetching IRQ routing table.&bslash;n&quot;
comma
(paren
id|ret
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|opt.size
)paren
(brace
id|rt
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irq_routing_table
)paren
op_plus
id|opt.size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rt
)paren
(brace
id|memset
c_func
(paren
id|rt
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irq_routing_table
)paren
)paren
suffix:semicolon
id|rt-&gt;size
op_assign
id|opt.size
op_plus
r_sizeof
(paren
r_struct
id|irq_routing_table
)paren
suffix:semicolon
id|rt-&gt;exclusive_irqs
op_assign
id|map
suffix:semicolon
id|memcpy
c_func
(paren
id|rt-&gt;slots
comma
(paren
r_void
op_star
)paren
id|page
comma
id|opt.size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Using BIOS Interrupt Routing Table&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|rt
suffix:semicolon
)brace
DECL|function|pcibios_set_irq_routing
r_int
id|pcibios_set_irq_routing
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pin
comma
r_int
id|irq
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;lcall *(%%esi); cld&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;xor %%ah, %%ah&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|PCIBIOS_SET_PCI_HW_INT
)paren
comma
l_string|&quot;b&quot;
(paren
(paren
id|dev-&gt;bus-&gt;number
op_lshift
l_int|8
)paren
op_or
id|dev-&gt;devfn
)paren
comma
l_string|&quot;c&quot;
(paren
(paren
id|irq
op_lshift
l_int|8
)paren
op_or
(paren
id|pin
op_plus
l_int|10
)paren
)paren
comma
l_string|&quot;S&quot;
(paren
op_amp
id|pci_indirect
)paren
)paren
suffix:semicolon
r_return
op_logical_neg
(paren
id|ret
op_amp
l_int|0xff00
)paren
suffix:semicolon
)brace
DECL|function|pci_pcbios_init
r_static
r_int
id|__init
id|pci_pcbios_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|pci_probe
op_amp
id|PCI_PROBE_BIOS
)paren
op_logical_and
(paren
(paren
id|pci_root_ops
op_assign
id|pci_find_bios
c_func
(paren
)paren
)paren
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_BIOS_SORT
suffix:semicolon
id|pci_bios_present
op_assign
l_int|1
suffix:semicolon
id|pci_config_read
op_assign
id|pci_bios_read
suffix:semicolon
id|pci_config_write
op_assign
id|pci_bios_write
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_pcbios_init
id|subsys_initcall
c_func
(paren
id|pci_pcbios_init
)paren
suffix:semicolon
eof
