multiline_comment|/*&n; *&t;Low-Level PCI Support for SH7751 targets&n; *&n; *  Dustin McIntire (dustin@sensoria.com) (c) 2001&n; *&t;&n; *  May be copied or modified under the terms of the GNU General Public&n; *  License.  See linux/COPYING for more information.&n; *&n; */
macro_line|#ifndef _PCI_SH7751_H_
DECL|macro|_PCI_SH7751_H_
mdefine_line|#define _PCI_SH7751_H_
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/* set debug level 4=verbose...1=terse */
singleline_comment|//#define DEBUG_PCI 3
DECL|macro|DEBUG_PCI
macro_line|#undef DEBUG_PCI
macro_line|#ifdef DEBUG_PCI
DECL|macro|PCIDBG
mdefine_line|#define PCIDBG(n, x...) { if(DEBUG_PCI&gt;=n) printk(x); }
macro_line|#else
DECL|macro|PCIDBG
mdefine_line|#define PCIDBG(n, x...)
macro_line|#endif
multiline_comment|/* startup values */
DECL|macro|PCI_PROBE_BIOS
mdefine_line|#define PCI_PROBE_BIOS 1
DECL|macro|PCI_PROBE_CONF1
mdefine_line|#define PCI_PROBE_CONF1 2
DECL|macro|PCI_PROBE_CONF2
mdefine_line|#define PCI_PROBE_CONF2 4
DECL|macro|PCI_NO_SORT
mdefine_line|#define PCI_NO_SORT 0x100
DECL|macro|PCI_BIOS_SORT
mdefine_line|#define PCI_BIOS_SORT 0x200
DECL|macro|PCI_NO_CHECKS
mdefine_line|#define PCI_NO_CHECKS 0x400
DECL|macro|PCI_ASSIGN_ROMS
mdefine_line|#define PCI_ASSIGN_ROMS 0x1000
DECL|macro|PCI_BIOS_IRQ_SCAN
mdefine_line|#define PCI_BIOS_IRQ_SCAN 0x2000
multiline_comment|/* Platform Specific Values */
DECL|macro|SH7751_VENDOR_ID
mdefine_line|#define SH7751_VENDOR_ID             0x1054
DECL|macro|SH7751_DEVICE_ID
mdefine_line|#define SH7751_DEVICE_ID             0x3505
multiline_comment|/* SH7751 Specific Values */
DECL|macro|SH7751_PCI_CONFIG_BASE
mdefine_line|#define SH7751_PCI_CONFIG_BASE&t;     0xFD000000  /* Config space base addr */
DECL|macro|SH7751_PCI_CONFIG_SIZE
mdefine_line|#define SH7751_PCI_CONFIG_SIZE       0x1000000   /* Config space size */
DECL|macro|SH7751_PCI_MEMORY_BASE
mdefine_line|#define SH7751_PCI_MEMORY_BASE&t;     0xFD000000  /* Memory space base addr */
DECL|macro|SH7751_PCI_MEM_SIZE
mdefine_line|#define SH7751_PCI_MEM_SIZE          0x01000000  /* Size of Memory window */
DECL|macro|SH7751_PCI_IO_BASE
mdefine_line|#define SH7751_PCI_IO_BASE           0xFE240000  /* IO space base address */
DECL|macro|SH7751_PCI_IO_SIZE
mdefine_line|#define SH7751_PCI_IO_SIZE           0x40000     /* Size of IO window */
DECL|macro|SH7751_PCIREG_BASE
mdefine_line|#define SH7751_PCIREG_BASE           0xFE200000  /* PCI regs base address */
DECL|macro|PCI_REG
mdefine_line|#define PCI_REG(n)                  (SH7751_PCIREG_BASE+ n)
DECL|macro|SH7751_PCICONF0
mdefine_line|#define SH7751_PCICONF0            0x0           /* PCI Config Reg 0 */
DECL|macro|SH7751_PCICONF0_DEVID
mdefine_line|#define SH7751_PCICONF0_DEVID      0xFFFF0000  /* Device ID */
DECL|macro|SH7751_PCICONF0_VNDID
mdefine_line|#define SH7751_PCICONF0_VNDID      0x0000FFFF  /* Vendor ID */
DECL|macro|SH7751_PCICONF1
mdefine_line|#define SH7751_PCICONF1            0x4           /* PCI Config Reg 1 */
DECL|macro|SH7751_PCICONF1_DPE
mdefine_line|#define SH7751_PCICONF1_DPE        0x80000000  /* Data Parity Error */
DECL|macro|SH7751_PCICONF1_SSE
mdefine_line|#define SH7751_PCICONF1_SSE        0x40000000  /* System Error Status */
DECL|macro|SH7751_PCICONF1_RMA
mdefine_line|#define SH7751_PCICONF1_RMA        0x20000000  /* Master Abort */
DECL|macro|SH7751_PCICONF1_RTA
mdefine_line|#define SH7751_PCICONF1_RTA        0x10000000  /* Target Abort Rx Status */
DECL|macro|SH7751_PCICONF1_STA
mdefine_line|#define SH7751_PCICONF1_STA        0x08000000  /* Target Abort Exec Status */
DECL|macro|SH7751_PCICONF1_DEV
mdefine_line|#define SH7751_PCICONF1_DEV        0x06000000  /* Timing Status */
DECL|macro|SH7751_PCICONF1_DPD
mdefine_line|#define SH7751_PCICONF1_DPD        0x01000000  /* Data Parity Status */
DECL|macro|SH7751_PCICONF1_FBBC
mdefine_line|#define SH7751_PCICONF1_FBBC       0x00800000  /* Back 2 Back Status */
DECL|macro|SH7751_PCICONF1_UDF
mdefine_line|#define SH7751_PCICONF1_UDF        0x00400000  /* User Defined Status */
DECL|macro|SH7751_PCICONF1_66M
mdefine_line|#define SH7751_PCICONF1_66M        0x00200000  /* 66Mhz Operation Status */
DECL|macro|SH7751_PCICONF1_PM
mdefine_line|#define SH7751_PCICONF1_PM         0x00100000  /* Power Management Status */
DECL|macro|SH7751_PCICONF1_PBBE
mdefine_line|#define SH7751_PCICONF1_PBBE       0x00000200  /* Back 2 Back Control */
DECL|macro|SH7751_PCICONF1_SER
mdefine_line|#define SH7751_PCICONF1_SER        0x00000100  /* SERR Output Control */
DECL|macro|SH7751_PCICONF1_WCC
mdefine_line|#define SH7751_PCICONF1_WCC        0x00000080  /* Wait Cycle Control */
DECL|macro|SH7751_PCICONF1_PER
mdefine_line|#define SH7751_PCICONF1_PER        0x00000040  /* Parity Error Response */
DECL|macro|SH7751_PCICONF1_VPS
mdefine_line|#define SH7751_PCICONF1_VPS        0x00000020  /* VGA Pallet Snoop */
DECL|macro|SH7751_PCICONF1_MWIE
mdefine_line|#define SH7751_PCICONF1_MWIE       0x00000010  /* Memory Write+Invalidate */
DECL|macro|SH7751_PCICONF1_SPC
mdefine_line|#define SH7751_PCICONF1_SPC        0x00000008  /* Special Cycle Control */
DECL|macro|SH7751_PCICONF1_BUM
mdefine_line|#define SH7751_PCICONF1_BUM        0x00000004  /* Bus Master Control */
DECL|macro|SH7751_PCICONF1_MES
mdefine_line|#define SH7751_PCICONF1_MES        0x00000002  /* Memory Space Control */
DECL|macro|SH7751_PCICONF1_IOS
mdefine_line|#define SH7751_PCICONF1_IOS        0x00000001  /* I/O Space Control */
DECL|macro|SH7751_PCICONF2
mdefine_line|#define SH7751_PCICONF2            0x8           /* PCI Config Reg 2 */
DECL|macro|SH7751_PCICONF2_BCC
mdefine_line|#define SH7751_PCICONF2_BCC        0xFF000000  /* Base Class Code */
DECL|macro|SH7751_PCICONF2_SCC
mdefine_line|#define SH7751_PCICONF2_SCC        0x00FF0000  /* Sub-Class Code */
DECL|macro|SH7751_PCICONF2_RLPI
mdefine_line|#define SH7751_PCICONF2_RLPI       0x0000FF00  /* Programming Interface */
DECL|macro|SH7751_PCICONF2_REV
mdefine_line|#define SH7751_PCICONF2_REV        0x000000FF  /* Revision ID */
DECL|macro|SH7751_PCICONF3
mdefine_line|#define SH7751_PCICONF3            0xC           /* PCI Config Reg 3 */ 
DECL|macro|SH7751_PCICONF3_BIST7
mdefine_line|#define SH7751_PCICONF3_BIST7      0x80000000  /* Bist Supported */
DECL|macro|SH7751_PCICONF3_BIST6
mdefine_line|#define SH7751_PCICONF3_BIST6      0x40000000  /* Bist Executing */
DECL|macro|SH7751_PCICONF3_BIST3_0
mdefine_line|#define SH7751_PCICONF3_BIST3_0    0x0F000000  /* Bist Passed */
DECL|macro|SH7751_PCICONF3_HD7
mdefine_line|#define SH7751_PCICONF3_HD7        0x00800000  /* Single Funtion device */
DECL|macro|SH7751_PCICONF3_HD6_0
mdefine_line|#define SH7751_PCICONF3_HD6_0      0x007F0000  /* Configuration Layout */
DECL|macro|SH7751_PCICONF3_LAT
mdefine_line|#define SH7751_PCICONF3_LAT        0x0000FF00  /* Latency Timer */
DECL|macro|SH7751_PCICONF3_CLS
mdefine_line|#define SH7751_PCICONF3_CLS        0x000000FF  /* Cache Line Size */
DECL|macro|SH7751_PCICONF4
mdefine_line|#define SH7751_PCICONF4            0x10          /* PCI Config Reg 4 */
DECL|macro|SH7751_PCICONF4_BASE
mdefine_line|#define SH7751_PCICONF4_BASE       0xFFFFFFFC  /* I/O Space Base Addr */
DECL|macro|SH7751_PCICONF4_ASI
mdefine_line|#define SH7751_PCICONF4_ASI        0x00000001  /* Address Space Type */
DECL|macro|SH7751_PCICONF5
mdefine_line|#define SH7751_PCICONF5            0x14          /* PCI Config Reg 5 */
DECL|macro|SH7751_PCICONF5_BASE
mdefine_line|#define SH7751_PCICONF5_BASE       0xFFFFFFF0  /* Mem Space Base Addr */
DECL|macro|SH7751_PCICONF5_LAP
mdefine_line|#define SH7751_PCICONF5_LAP        0x00000008  /* Prefetch Enabled */
DECL|macro|SH7751_PCICONF5_LAT
mdefine_line|#define SH7751_PCICONF5_LAT        0x00000006  /* Local Memory type */
DECL|macro|SH7751_PCICONF5_ASI
mdefine_line|#define SH7751_PCICONF5_ASI        0x00000001  /* Address Space Type */  
DECL|macro|SH7751_PCICONF6
mdefine_line|#define SH7751_PCICONF6            0x18          /* PCI Config Reg 6 */
DECL|macro|SH7751_PCICONF6_BASE
mdefine_line|#define SH7751_PCICONF6_BASE       0xFFFFFFF0  /* Mem Space Base Addr */
DECL|macro|SH7751_PCICONF6_LAP
mdefine_line|#define SH7751_PCICONF6_LAP        0x00000008  /* Prefetch Enabled */
DECL|macro|SH7751_PCICONF6_LAT
mdefine_line|#define SH7751_PCICONF6_LAT        0x00000006  /* Local Memory type */
DECL|macro|SH7751_PCICONF6_ASI
mdefine_line|#define SH7751_PCICONF6_ASI        0x00000001  /* Address Space Type */  
multiline_comment|/* PCICONF7 - PCICONF10 are undefined */
DECL|macro|SH7751_PCICONF11
mdefine_line|#define SH7751_PCICONF11           0x2C          /* PCI Config Reg 11 */
DECL|macro|SH7751_PCICONF11_SSID
mdefine_line|#define SH7751_PCICONF11_SSID      0xFFFF0000  /* Subsystem ID */
DECL|macro|SH7751_PCICONF11_SVID
mdefine_line|#define SH7751_PCICONF11_SVID      0x0000FFFF  /* Subsystem Vendor ID */
multiline_comment|/* PCICONF12 is undefined */
DECL|macro|SH7751_PCICONF13
mdefine_line|#define SH7751_PCICONF13           0x34          /* PCI Config Reg 13 */
DECL|macro|SH7751_PCICONF13_CPTR
mdefine_line|#define SH7751_PCICONF13_CPTR      0x000000FF  /* PM function pointer */
multiline_comment|/* PCICONF14 is undefined */
DECL|macro|SH7751_PCICONF15
mdefine_line|#define SH7751_PCICONF15           0x3C          /* PCI Config Reg 15 */
DECL|macro|SH7751_PCICONF15_IPIN
mdefine_line|#define SH7751_PCICONF15_IPIN      0x000000FF  /* Interrupt Pin */
DECL|macro|SH7751_PCICONF16
mdefine_line|#define SH7751_PCICONF16           0x40          /* PCI Config Reg 16 */
DECL|macro|SH7751_PCICONF16_PMES
mdefine_line|#define SH7751_PCICONF16_PMES      0xF8000000  /* PME Support */
DECL|macro|SH7751_PCICONF16_D2S
mdefine_line|#define SH7751_PCICONF16_D2S       0x04000000  /* D2 Support */
DECL|macro|SH7751_PCICONF16_D1S
mdefine_line|#define SH7751_PCICONF16_D1S       0x02000000  /* D1 Support */
DECL|macro|SH7751_PCICONF16_DSI
mdefine_line|#define SH7751_PCICONF16_DSI       0x00200000  /* Bit Device Init. */
DECL|macro|SH7751_PCICONF16_PMCK
mdefine_line|#define SH7751_PCICONF16_PMCK      0x00080000  /* Clock for PME req. */
DECL|macro|SH7751_PCICONF16_VER
mdefine_line|#define SH7751_PCICONF16_VER       0x00070000  /* PM Version */
DECL|macro|SH7751_PCICONF16_NIP
mdefine_line|#define SH7751_PCICONF16_NIP       0x0000FF00  /* Next Item Pointer */
DECL|macro|SH7751_PCICONF16_CID
mdefine_line|#define SH7751_PCICONF16_CID       0x000000FF  /* Capability Identifier */
DECL|macro|SH7751_PCICONF17
mdefine_line|#define SH7751_PCICONF17           0x44          /* PCI Config Reg 17 */
DECL|macro|SH7751_PCICONF17_DATA
mdefine_line|#define SH7751_PCICONF17_DATA      0xFF000000  /* Data field for PM */
DECL|macro|SH7751_PCICONF17_PMES
mdefine_line|#define SH7751_PCICONF17_PMES      0x00800000  /* PME Status */
DECL|macro|SH7751_PCICONF17_DSCL
mdefine_line|#define SH7751_PCICONF17_DSCL      0x00600000  /* Data Scaling Value */
DECL|macro|SH7751_PCICONF17_DSEL
mdefine_line|#define SH7751_PCICONF17_DSEL      0x001E0000  /* Data Select */
DECL|macro|SH7751_PCICONF17_PMEN
mdefine_line|#define SH7751_PCICONF17_PMEN      0x00010000  /* PME Enable */
DECL|macro|SH7751_PCICONF17_PWST
mdefine_line|#define SH7751_PCICONF17_PWST      0x00000003  /* Power State */
multiline_comment|/* SH7715 Internal PCI Registers */
DECL|macro|SH7751_PCICR
mdefine_line|#define SH7751_PCICR               0x100         /* PCI Control Register */
DECL|macro|SH7751_PCICR_PREFIX
mdefine_line|#define SH7751_PCICR_PREFIX        0xA5000000  /* CR prefix for write */
DECL|macro|SH7751_PCICR_TRSB
mdefine_line|#define SH7751_PCICR_TRSB          0x00000200  /* Target Read Single */
DECL|macro|SH7751_PCICR_BSWP
mdefine_line|#define SH7751_PCICR_BSWP          0x00000100  /* Target Byte Swap */
DECL|macro|SH7751_PCICR_PLUP
mdefine_line|#define SH7751_PCICR_PLUP          0x00000080  /* Enable PCI Pullup */
DECL|macro|SH7751_PCICR_ARBM
mdefine_line|#define SH7751_PCICR_ARBM          0x00000040  /* PCI Arbitration Mode */
DECL|macro|SH7751_PCICR_MD
mdefine_line|#define SH7751_PCICR_MD            0x00000030  /* MD9 and MD10 status */
DECL|macro|SH7751_PCICR_SERR
mdefine_line|#define SH7751_PCICR_SERR          0x00000008  /* SERR output assert */
DECL|macro|SH7751_PCICR_INTA
mdefine_line|#define SH7751_PCICR_INTA          0x00000004  /* INTA output assert */
DECL|macro|SH7751_PCICR_PRST
mdefine_line|#define SH7751_PCICR_PRST          0x00000002  /* PCI Reset Assert */
DECL|macro|SH7751_PCICR_CFIN
mdefine_line|#define SH7751_PCICR_CFIN          0x00000001  /* Central Fun. Init Done */
DECL|macro|SH7751_PCILSR0
mdefine_line|#define SH7751_PCILSR0             0x104         /* PCI Local Space Register0 */
DECL|macro|SH7751_PCILSR1
mdefine_line|#define SH7751_PCILSR1             0x108         /* PCI Local Space Register1 */
DECL|macro|SH7751_PCILAR0
mdefine_line|#define SH7751_PCILAR0             0x10C         /* PCI Local Address Register1 */
DECL|macro|SH7751_PCILAR1
mdefine_line|#define SH7751_PCILAR1             0x110         /* PCI Local Address Register1 */
DECL|macro|SH7751_PCIINT
mdefine_line|#define SH7751_PCIINT              0x114         /* PCI Interrupt Register */
DECL|macro|SH7751_PCIINT_MLCK
mdefine_line|#define SH7751_PCIINT_MLCK         0x00008000  /* Master Lock Error */
DECL|macro|SH7751_PCIINT_TABT
mdefine_line|#define SH7751_PCIINT_TABT         0x00004000  /* Target Abort Error */
DECL|macro|SH7751_PCIINT_TRET
mdefine_line|#define SH7751_PCIINT_TRET         0x00000200  /* Target Retry Error */
DECL|macro|SH7751_PCIINT_MFDE
mdefine_line|#define SH7751_PCIINT_MFDE         0x00000100  /* Master Func. Disable Error */
DECL|macro|SH7751_PCIINT_PRTY
mdefine_line|#define SH7751_PCIINT_PRTY         0x00000080  /* Address Parity Error */
DECL|macro|SH7751_PCIINT_SERR
mdefine_line|#define SH7751_PCIINT_SERR         0x00000040  /* SERR Detection Error */
DECL|macro|SH7751_PCIINT_TWDP
mdefine_line|#define SH7751_PCIINT_TWDP         0x00000020  /* Tgt. Write Parity Error */
DECL|macro|SH7751_PCIINT_TRDP
mdefine_line|#define SH7751_PCIINT_TRDP         0x00000010  /* Tgt. Read Parity Error Det. */
DECL|macro|SH7751_PCIINT_MTABT
mdefine_line|#define SH7751_PCIINT_MTABT        0x00000008  /* Master-Tgt. Abort Error */
DECL|macro|SH7751_PCIINT_MMABT
mdefine_line|#define SH7751_PCIINT_MMABT        0x00000004  /* Master-Master Abort Error */
DECL|macro|SH7751_PCIINT_MWPD
mdefine_line|#define SH7751_PCIINT_MWPD         0x00000002  /* Master Write PERR Detect */
DECL|macro|SH7751_PCIINT_MRPD
mdefine_line|#define SH7751_PCIINT_MRPD         0x00000002  /* Master Read PERR Detect */
DECL|macro|SH7751_PCIINTM
mdefine_line|#define SH7751_PCIINTM             0x118         /* PCI Interrupt Mask Register */
DECL|macro|SH7751_PCIALR
mdefine_line|#define SH7751_PCIALR              0x11C         /* Error Address Register */
DECL|macro|SH7751_PCICLR
mdefine_line|#define SH7751_PCICLR              0x120         /* Error Command/Data Register */
DECL|macro|SH7751_PCICLR_MPIO
mdefine_line|#define SH7751_PCICLR_MPIO         0x80000000  /* Error Command/Data Register */
DECL|macro|SH7751_PCICLR_MDMA0
mdefine_line|#define SH7751_PCICLR_MDMA0        0x40000000  /* DMA0 Transfer Error */
DECL|macro|SH7751_PCICLR_MDMA1
mdefine_line|#define SH7751_PCICLR_MDMA1        0x20000000  /* DMA1 Transfer Error */
DECL|macro|SH7751_PCICLR_MDMA2
mdefine_line|#define SH7751_PCICLR_MDMA2        0x10000000  /* DMA2 Transfer Error */
DECL|macro|SH7751_PCICLR_MDMA3
mdefine_line|#define SH7751_PCICLR_MDMA3        0x08000000  /* DMA3 Transfer Error */
DECL|macro|SH7751_PCICLR_TGT
mdefine_line|#define SH7751_PCICLR_TGT          0x04000000  /* Target Transfer Error */
DECL|macro|SH7751_PCICLR_CMDL
mdefine_line|#define SH7751_PCICLR_CMDL         0x0000000F  /* PCI Command at Error */
DECL|macro|SH7751_PCIAINT
mdefine_line|#define SH7751_PCIAINT             0x130         /* Arbiter Interrupt Register */
DECL|macro|SH7751_PCIAINT_MBKN
mdefine_line|#define SH7751_PCIAINT_MBKN        0x00002000  /* Master Broken Interrupt */
DECL|macro|SH7751_PCIAINT_TBTO
mdefine_line|#define SH7751_PCIAINT_TBTO        0x00001000  /* Target Bus Time Out */
DECL|macro|SH7751_PCIAINT_MBTO
mdefine_line|#define SH7751_PCIAINT_MBTO        0x00001000  /* Master Bus Time Out */
DECL|macro|SH7751_PCIAINT_TABT
mdefine_line|#define SH7751_PCIAINT_TABT        0x00000008  /* Target Abort */
DECL|macro|SH7751_PCIAINT_MABT
mdefine_line|#define SH7751_PCIAINT_MABT        0x00000004  /* Master Abort */
DECL|macro|SH7751_PCIAINT_RDPE
mdefine_line|#define SH7751_PCIAINT_RDPE        0x00000002  /* Read Data Parity Error */
DECL|macro|SH7751_PCIAINT_WDPE
mdefine_line|#define SH7751_PCIAINT_WDPE        0x00000002  /* Write Data Parity Error */
DECL|macro|SH7751_PCIAINTM
mdefine_line|#define SH7751_PCIAINTM            0x134         /* Arbiter Int. Mask Register */
DECL|macro|SH7751_PCIBMLR
mdefine_line|#define SH7751_PCIBMLR             0x138         /* Error Bus Master Register */
DECL|macro|SH7751_PCIBMLR_REQ4
mdefine_line|#define SH7751_PCIBMLR_REQ4        0x00000010  /* REQ4 bus master at error */
DECL|macro|SH7751_PCIBMLR_REQ3
mdefine_line|#define SH7751_PCIBMLR_REQ3        0x00000008  /* REQ3 bus master at error */
DECL|macro|SH7751_PCIBMLR_REQ2
mdefine_line|#define SH7751_PCIBMLR_REQ2        0x00000004  /* REQ2 bus master at error */
DECL|macro|SH7751_PCIBMLR_REQ1
mdefine_line|#define SH7751_PCIBMLR_REQ1        0x00000002  /* REQ1 bus master at error */
DECL|macro|SH7751_PCIBMLR_REQ0
mdefine_line|#define SH7751_PCIBMLR_REQ0        0x00000001  /* REQ0 bus master at error */
DECL|macro|SH7751_PCIDMABT
mdefine_line|#define SH7751_PCIDMABT            0x140         /* DMA Transfer Arb. Register */
DECL|macro|SH7751_PCIDMABT_RRBN
mdefine_line|#define SH7751_PCIDMABT_RRBN       0x00000001  /* DMA Arbitor Round-Robin */
DECL|macro|SH7751_PCIDPA0
mdefine_line|#define SH7751_PCIDPA0             0x180         /* DMA0 Transfer Addr. Register */
DECL|macro|SH7751_PCIDLA0
mdefine_line|#define SH7751_PCIDLA0             0x184         /* DMA0 Local Addr. Register */
DECL|macro|SH7751_PCIDTC0
mdefine_line|#define SH7751_PCIDTC0             0x188         /* DMA0 Transfer Cnt. Register */
DECL|macro|SH7751_PCIDCR0
mdefine_line|#define SH7751_PCIDCR0             0x18C         /* DMA0 Control Register */
DECL|macro|SH7751_PCIDCR_ALGN
mdefine_line|#define SH7751_PCIDCR_ALGN         0x00000600  /* DMA Alignment Mode */
DECL|macro|SH7751_PCIDCR_MAST
mdefine_line|#define SH7751_PCIDCR_MAST         0x00000100  /* DMA Termination Type */
DECL|macro|SH7751_PCIDCR_INTM
mdefine_line|#define SH7751_PCIDCR_INTM         0x00000080  /* DMA Interrupt Done Mask*/
DECL|macro|SH7751_PCIDCR_INTS
mdefine_line|#define SH7751_PCIDCR_INTS         0x00000040  /* DMA Interrupt Done Status */
DECL|macro|SH7751_PCIDCR_LHLD
mdefine_line|#define SH7751_PCIDCR_LHLD         0x00000020  /* Local Address Control */
DECL|macro|SH7751_PCIDCR_PHLD
mdefine_line|#define SH7751_PCIDCR_PHLD         0x00000010  /* PCI Address Control*/
DECL|macro|SH7751_PCIDCR_IOSEL
mdefine_line|#define SH7751_PCIDCR_IOSEL        0x00000008  /* PCI Address Space Type */
DECL|macro|SH7751_PCIDCR_DIR
mdefine_line|#define SH7751_PCIDCR_DIR          0x00000004  /* DMA Transfer Direction */
DECL|macro|SH7751_PCIDCR_STOP
mdefine_line|#define SH7751_PCIDCR_STOP         0x00000002  /* Force DMA Stop */
DECL|macro|SH7751_PCIDCR_STRT
mdefine_line|#define SH7751_PCIDCR_STRT         0x00000001  /* DMA Start */
DECL|macro|SH7751_PCIDPA1
mdefine_line|#define SH7751_PCIDPA1             0x190         /* DMA1 Transfer Addr. Register */
DECL|macro|SH7751_PCIDLA1
mdefine_line|#define SH7751_PCIDLA1             0x194         /* DMA1 Local Addr. Register */
DECL|macro|SH7751_PCIDTC1
mdefine_line|#define SH7751_PCIDTC1             0x198         /* DMA1 Transfer Cnt. Register */
DECL|macro|SH7751_PCIDCR1
mdefine_line|#define SH7751_PCIDCR1             0x19C         /* DMA1 Control Register */
DECL|macro|SH7751_PCIDPA2
mdefine_line|#define SH7751_PCIDPA2             0x1A0         /* DMA2 Transfer Addr. Register */
DECL|macro|SH7751_PCIDLA2
mdefine_line|#define SH7751_PCIDLA2             0x1A4         /* DMA2 Local Addr. Register */
DECL|macro|SH7751_PCIDTC2
mdefine_line|#define SH7751_PCIDTC2             0x1A8         /* DMA2 Transfer Cnt. Register */
DECL|macro|SH7751_PCIDCR2
mdefine_line|#define SH7751_PCIDCR2             0x1AC         /* DMA2 Control Register */
DECL|macro|SH7751_PCIDPA3
mdefine_line|#define SH7751_PCIDPA3             0x1B0         /* DMA3 Transfer Addr. Register */
DECL|macro|SH7751_PCIDLA3
mdefine_line|#define SH7751_PCIDLA3             0x1B4         /* DMA3 Local Addr. Register */
DECL|macro|SH7751_PCIDTC3
mdefine_line|#define SH7751_PCIDTC3             0x1B8         /* DMA3 Transfer Cnt. Register */
DECL|macro|SH7751_PCIDCR3
mdefine_line|#define SH7751_PCIDCR3             0x1BC         /* DMA3 Control Register */
DECL|macro|SH7751_PCIPAR
mdefine_line|#define SH7751_PCIPAR              0x1C0         /* PIO Address Register */
DECL|macro|SH7751_PCIPAR_CFGEN
mdefine_line|#define SH7751_PCIPAR_CFGEN        0x80000000  /* Configuration Enable */
DECL|macro|SH7751_PCIPAR_BUSNO
mdefine_line|#define SH7751_PCIPAR_BUSNO        0x00FF0000  /* Config. Bus Number */
DECL|macro|SH7751_PCIPAR_DEVNO
mdefine_line|#define SH7751_PCIPAR_DEVNO        0x0000FF00  /* Config. Device Number */
DECL|macro|SH7751_PCIPAR_REGAD
mdefine_line|#define SH7751_PCIPAR_REGAD        0x000000FC  /* Register Address Number */
DECL|macro|SH7751_PCIMBR
mdefine_line|#define SH7751_PCIMBR              0x1C4         /* Memory Base Address Register */
DECL|macro|SH7751_PCIMBR_MASK
mdefine_line|#define SH7751_PCIMBR_MASK         0xFF000000  /* Memory Space Mask */
DECL|macro|SH7751_PCIMBR_LOCK
mdefine_line|#define SH7751_PCIMBR_LOCK         0x00000001  /* Lock Memory Space */
DECL|macro|SH7751_PCIIOBR
mdefine_line|#define SH7751_PCIIOBR             0x1C8         /* I/O Base Address Register */
DECL|macro|SH7751_PCIIOBR_MASK
mdefine_line|#define SH7751_PCIIOBR_MASK         0xFFFC0000 /* IO Space Mask */
DECL|macro|SH7751_PCIIOBR_LOCK
mdefine_line|#define SH7751_PCIIOBR_LOCK         0x00000001 /* Lock IO Space */
DECL|macro|SH7751_PCIPINT
mdefine_line|#define SH7751_PCIPINT             0x1CC         /* Power Mgmnt Int. Register */
DECL|macro|SH7751_PCIPINT_D3
mdefine_line|#define SH7751_PCIPINT_D3           0x00000002 /* D3 Pwr Mgmt. Interrupt */
DECL|macro|SH7751_PCIPINT_D0
mdefine_line|#define SH7751_PCIPINT_D0           0x00000001 /* D0 Pwr Mgmt. Interrupt */  
DECL|macro|SH7751_PCIPINTM
mdefine_line|#define SH7751_PCIPINTM            0x1D0         /* Power Mgmnt Mask Register */
DECL|macro|SH7751_PCICLKR
mdefine_line|#define SH7751_PCICLKR             0x1D4         /* Clock Ctrl. Register */
DECL|macro|SH7751_PCICLKR_PCSTP
mdefine_line|#define SH7751_PCICLKR_PCSTP        0x00000002 /* PCI Clock Stop */
DECL|macro|SH7751_PCICLKR_BCSTP
mdefine_line|#define SH7751_PCICLKR_BCSTP        0x00000002 /* BCLK Clock Stop */
multiline_comment|/* For definitions of BCR, MCR see ... */
DECL|macro|SH7751_PCIBCR1
mdefine_line|#define SH7751_PCIBCR1             0x1E0         /* Memory BCR1 Register */
DECL|macro|SH7751_PCIBCR2
mdefine_line|#define SH7751_PCIBCR2             0x1E4         /* Memory BCR2 Register */
DECL|macro|SH7751_PCIWCR1
mdefine_line|#define SH7751_PCIWCR1             0x1E8         /* Wait Control 1 Register */
DECL|macro|SH7751_PCIWCR2
mdefine_line|#define SH7751_PCIWCR2             0x1EC         /* Wait Control 2 Register */
DECL|macro|SH7751_PCIWCR3
mdefine_line|#define SH7751_PCIWCR3             0x1F0         /* Wait Control 3 Register */
DECL|macro|SH7751_PCIMCR
mdefine_line|#define SH7751_PCIMCR              0x1F4         /* Memory Control Register */
DECL|macro|SH7751_PCIPCTR
mdefine_line|#define SH7751_PCIPCTR             0x200         /* Port Control Register */
DECL|macro|SH7751_PCIPCTR_P2EN
mdefine_line|#define SH7751_PCIPCTR_P2EN        0x000400000 /* Port 2 Enable */
DECL|macro|SH7751_PCIPCTR_P1EN
mdefine_line|#define SH7751_PCIPCTR_P1EN        0x000200000 /* Port 1 Enable */
DECL|macro|SH7751_PCIPCTR_P0EN
mdefine_line|#define SH7751_PCIPCTR_P0EN        0x000100000 /* Port 0 Enable */
DECL|macro|SH7751_PCIPCTR_P2UP
mdefine_line|#define SH7751_PCIPCTR_P2UP        0x000000020 /* Port2 Pull Up Enable */
DECL|macro|SH7751_PCIPCTR_P2IO
mdefine_line|#define SH7751_PCIPCTR_P2IO        0x000000010 /* Port2 Output Enable */
DECL|macro|SH7751_PCIPCTR_P1UP
mdefine_line|#define SH7751_PCIPCTR_P1UP        0x000000008 /* Port1 Pull Up Enable */
DECL|macro|SH7751_PCIPCTR_P1IO
mdefine_line|#define SH7751_PCIPCTR_P1IO        0x000000004 /* Port1 Output Enable */
DECL|macro|SH7751_PCIPCTR_P0UP
mdefine_line|#define SH7751_PCIPCTR_P0UP        0x000000002 /* Port0 Pull Up Enable */
DECL|macro|SH7751_PCIPCTR_P0IO
mdefine_line|#define SH7751_PCIPCTR_P0IO        0x000000001 /* Port0 Output Enable */
DECL|macro|SH7751_PCIPDTR
mdefine_line|#define SH7751_PCIPDTR             0x204         /* Port Data Register */
DECL|macro|SH7751_PCIPDTR_PB5
mdefine_line|#define SH7751_PCIPDTR_PB5         0x000000020 /* Port 5 Enable */
DECL|macro|SH7751_PCIPDTR_PB4
mdefine_line|#define SH7751_PCIPDTR_PB4         0x000000010 /* Port 4 Enable */
DECL|macro|SH7751_PCIPDTR_PB3
mdefine_line|#define SH7751_PCIPDTR_PB3         0x000000008 /* Port 3 Enable */
DECL|macro|SH7751_PCIPDTR_PB2
mdefine_line|#define SH7751_PCIPDTR_PB2         0x000000004 /* Port 2 Enable */
DECL|macro|SH7751_PCIPDTR_PB1
mdefine_line|#define SH7751_PCIPDTR_PB1         0x000000002 /* Port 1 Enable */
DECL|macro|SH7751_PCIPDTR_PB0
mdefine_line|#define SH7751_PCIPDTR_PB0         0x000000001 /* Port 0 Enable */
DECL|macro|SH7751_PCIPDR
mdefine_line|#define SH7751_PCIPDR              0x220         /* Port IO Data Register */
multiline_comment|/* Memory Control Registers */
DECL|macro|SH7751_BCR1
mdefine_line|#define SH7751_BCR1                0xFF800000    /* Memory BCR1 Register */
DECL|macro|SH7751_BCR2
mdefine_line|#define SH7751_BCR2                0xFF800004    /* Memory BCR2 Register */
DECL|macro|SH7751_WCR1
mdefine_line|#define SH7751_WCR1                0xFF800008    /* Wait Control 1 Register */
DECL|macro|SH7751_WCR2
mdefine_line|#define SH7751_WCR2                0xFF80000C    /* Wait Control 2 Register */
DECL|macro|SH7751_WCR3
mdefine_line|#define SH7751_WCR3                0xFF800010    /* Wait Control 3 Register */
DECL|macro|SH7751_MCR
mdefine_line|#define SH7751_MCR                 0xFF800014    /* Memory Control Register */
multiline_comment|/* General Memory Config Addresses */
DECL|macro|SH7751_CS0_BASE_ADDR
mdefine_line|#define SH7751_CS0_BASE_ADDR       0x0
DECL|macro|SH7751_MEM_REGION_SIZE
mdefine_line|#define SH7751_MEM_REGION_SIZE     0x04000000
DECL|macro|SH7751_CS1_BASE_ADDR
mdefine_line|#define SH7751_CS1_BASE_ADDR       (SH7751_CS0_BASE_ADDR + SH7751_MEM_REGION_SIZE)
DECL|macro|SH7751_CS2_BASE_ADDR
mdefine_line|#define SH7751_CS2_BASE_ADDR       (SH7751_CS1_BASE_ADDR + SH7751_MEM_REGION_SIZE)
DECL|macro|SH7751_CS3_BASE_ADDR
mdefine_line|#define SH7751_CS3_BASE_ADDR       (SH7751_CS2_BASE_ADDR + SH7751_MEM_REGION_SIZE)
DECL|macro|SH7751_CS4_BASE_ADDR
mdefine_line|#define SH7751_CS4_BASE_ADDR       (SH7751_CS3_BASE_ADDR + SH7751_MEM_REGION_SIZE)
DECL|macro|SH7751_CS5_BASE_ADDR
mdefine_line|#define SH7751_CS5_BASE_ADDR       (SH7751_CS4_BASE_ADDR + SH7751_MEM_REGION_SIZE)
DECL|macro|SH7751_CS6_BASE_ADDR
mdefine_line|#define SH7751_CS6_BASE_ADDR       (SH7751_CS5_BASE_ADDR + SH7751_MEM_REGION_SIZE)
multiline_comment|/* General PCI values */
DECL|macro|SH7751_PCI_HOST_BRIDGE
mdefine_line|#define SH7751_PCI_HOST_BRIDGE&t;&t;0x6
multiline_comment|/* External functions defined per platform i.e. Big Sur, SE... (these could be routed &n; * through the machine vectors... */
r_extern
r_int
id|pcibios_init_platform
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pcibios_map_platform_irq
c_func
(paren
id|u8
id|slot
comma
id|u8
id|pin
)paren
suffix:semicolon
macro_line|#endif /* _PCI_SH7751_H_ */
eof
