multiline_comment|/*&n; *&t;PCI BIOS function codes for the PC9800. Different to&n; *&t;standard PC systems&n; */
multiline_comment|/* Note: PC-9800 confirms PCI 2.1 on only few models */
DECL|macro|PCIBIOS_PCI_FUNCTION_ID
mdefine_line|#define PCIBIOS_PCI_FUNCTION_ID &t;0xccXX
DECL|macro|PCIBIOS_PCI_BIOS_PRESENT
mdefine_line|#define PCIBIOS_PCI_BIOS_PRESENT &t;0xcc81
DECL|macro|PCIBIOS_FIND_PCI_DEVICE
mdefine_line|#define PCIBIOS_FIND_PCI_DEVICE&t;&t;0xcc82
DECL|macro|PCIBIOS_FIND_PCI_CLASS_CODE
mdefine_line|#define PCIBIOS_FIND_PCI_CLASS_CODE&t;0xcc83
multiline_comment|/*      PCIBIOS_GENERATE_SPECIAL_CYCLE&t;0xcc86&t;(not supported by bios) */
DECL|macro|PCIBIOS_READ_CONFIG_BYTE
mdefine_line|#define PCIBIOS_READ_CONFIG_BYTE&t;0xcc88
DECL|macro|PCIBIOS_READ_CONFIG_WORD
mdefine_line|#define PCIBIOS_READ_CONFIG_WORD&t;0xcc89
DECL|macro|PCIBIOS_READ_CONFIG_DWORD
mdefine_line|#define PCIBIOS_READ_CONFIG_DWORD&t;0xcc8a
DECL|macro|PCIBIOS_WRITE_CONFIG_BYTE
mdefine_line|#define PCIBIOS_WRITE_CONFIG_BYTE&t;0xcc8b
DECL|macro|PCIBIOS_WRITE_CONFIG_WORD
mdefine_line|#define PCIBIOS_WRITE_CONFIG_WORD&t;0xcc8c
DECL|macro|PCIBIOS_WRITE_CONFIG_DWORD
mdefine_line|#define PCIBIOS_WRITE_CONFIG_DWORD&t;0xcc8d
DECL|macro|PCIBIOS_GET_ROUTING_OPTIONS
mdefine_line|#define PCIBIOS_GET_ROUTING_OPTIONS&t;0xcc8e&t;/* PCI 2.1 only */
DECL|macro|PCIBIOS_SET_PCI_HW_INT
mdefine_line|#define PCIBIOS_SET_PCI_HW_INT&t;&t;0xcc8f&t;/* PCI 2.1 only */
eof
