multiline_comment|/*************************************************************************&n; * Defines and structure definitions for PCI BIOS Interface &n; *************************************************************************/
DECL|macro|PCIMAX
mdefine_line|#define&t;PCIMAX  32&t;&t;/* maximum number of PCI boards */
DECL|macro|PCI_VENDOR_DIGI
mdefine_line|#define&t;PCI_VENDOR_DIGI&t;&t;0x114F
DECL|macro|PCI_DEVICE_EPC
mdefine_line|#define&t;PCI_DEVICE_EPC&t;&t;0x0002
DECL|macro|PCI_DEVICE_RIGHTSWITCH
mdefine_line|#define&t;PCI_DEVICE_RIGHTSWITCH 0x0003  /* For testing */
DECL|macro|PCI_DEVICE_XEM
mdefine_line|#define&t;PCI_DEVICE_XEM&t;&t;0x0004
DECL|macro|PCI_DEVICE_XR
mdefine_line|#define&t;PCI_DEVICE_XR&t;&t;0x0005
DECL|macro|PCI_DEVICE_CX
mdefine_line|#define&t;PCI_DEVICE_CX&t;&t;0x0006
DECL|macro|PCI_DEVICE_XRJ
mdefine_line|#define&t;PCI_DEVICE_XRJ&t;&t;0x0009   /* Jupiter boards with */
DECL|macro|PCI_DEVICE_EPCJ
mdefine_line|#define&t;PCI_DEVICE_EPCJ&t;&t;0x000a   /* PLX 9060 chip for PCI  */
multiline_comment|/*&n; * On the PCI boards, there is no IO space allocated &n; * The I/O registers will be in the first 3 bytes of the   &n; * upper 2MB of the 4MB memory space.  The board memory &n; * will be mapped into the low 2MB of the 4MB memory space &n; */
multiline_comment|/* Potential location of PCI Bios from E0000 to FFFFF*/
DECL|macro|PCI_BIOS_SIZE
mdefine_line|#define PCI_BIOS_SIZE&t;&t;0x00020000&t;
multiline_comment|/* Size of Memory and I/O for PCI (4MB) */
DECL|macro|PCI_RAM_SIZE
mdefine_line|#define PCI_RAM_SIZE&t;&t;0x00400000&t;
multiline_comment|/* Size of Memory (2MB) */
DECL|macro|PCI_MEM_SIZE
mdefine_line|#define PCI_MEM_SIZE&t;&t;0x00200000&t;
multiline_comment|/* Offset of I/0 in Memory (2MB) */
DECL|macro|PCI_IO_OFFSET
mdefine_line|#define PCI_IO_OFFSET &t;&t;0x00200000&t;
DECL|macro|MEMOUTB
mdefine_line|#define MEMOUTB(basemem, pnum, setmemval)  *(caddr_t)((basemem) + ( PCI_IO_OFFSET | pnum &lt;&lt; 4 | pnum )) = (setmemval)
DECL|macro|MEMINB
mdefine_line|#define MEMINB(basemem, pnum)  *(caddr_t)((basemem) + (PCI_IO_OFFSET | pnum &lt;&lt; 4 | pnum ))   /* for PCI I/O */
eof
