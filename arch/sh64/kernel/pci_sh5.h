multiline_comment|/*&n; * Copyright (C) 2001 David J. Mckay (david.mckay@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Defintions for the SH5 PCI hardware.&n; */
multiline_comment|/* Product ID */
DECL|macro|PCISH5_PID
mdefine_line|#define PCISH5_PID&t;&t;0x350d
multiline_comment|/* vendor ID */
DECL|macro|PCISH5_VID
mdefine_line|#define PCISH5_VID&t;&t;0x1054
multiline_comment|/* Configuration types */
DECL|macro|ST_TYPE0
mdefine_line|#define ST_TYPE0                0x00    /* Configuration cycle type 0 */
DECL|macro|ST_TYPE1
mdefine_line|#define ST_TYPE1                0x01    /* Configuration cycle type 1 */
multiline_comment|/* VCR data */
DECL|macro|PCISH5_VCR_STATUS
mdefine_line|#define PCISH5_VCR_STATUS      0x00
DECL|macro|PCISH5_VCR_VERSION
mdefine_line|#define PCISH5_VCR_VERSION     0x08
multiline_comment|/*&n;** ICR register offsets and bits&n;*/
DECL|macro|PCISH5_ICR_CR
mdefine_line|#define PCISH5_ICR_CR          0x100   /* PCI control register values */
DECL|macro|CR_PBAM
mdefine_line|#define CR_PBAM                 (1&lt;&lt;12)
DECL|macro|CR_PFCS
mdefine_line|#define CR_PFCS                 (1&lt;&lt;11)
DECL|macro|CR_FTO
mdefine_line|#define CR_FTO                  (1&lt;&lt;10)
DECL|macro|CR_PFE
mdefine_line|#define CR_PFE                  (1&lt;&lt;9)
DECL|macro|CR_TBS
mdefine_line|#define CR_TBS                  (1&lt;&lt;8)
DECL|macro|CR_SPUE
mdefine_line|#define CR_SPUE                 (1&lt;&lt;7)
DECL|macro|CR_BMAM
mdefine_line|#define CR_BMAM                 (1&lt;&lt;6)
DECL|macro|CR_HOST
mdefine_line|#define CR_HOST                 (1&lt;&lt;5)
DECL|macro|CR_CLKEN
mdefine_line|#define CR_CLKEN                (1&lt;&lt;4)
DECL|macro|CR_SOCS
mdefine_line|#define CR_SOCS                 (1&lt;&lt;3)
DECL|macro|CR_IOCS
mdefine_line|#define CR_IOCS                 (1&lt;&lt;2)
DECL|macro|CR_RSTCTL
mdefine_line|#define CR_RSTCTL               (1&lt;&lt;1)
DECL|macro|CR_CFINT
mdefine_line|#define CR_CFINT                (1&lt;&lt;0)
DECL|macro|CR_LOCK_MASK
mdefine_line|#define CR_LOCK_MASK            0xa5000000
DECL|macro|PCISH5_ICR_INT
mdefine_line|#define PCISH5_ICR_INT         0x114   /* Interrupt registert values     */
DECL|macro|INT_MADIM
mdefine_line|#define INT_MADIM               (1&lt;&lt;2)
DECL|macro|PCISH5_ICR_LSR0
mdefine_line|#define PCISH5_ICR_LSR0        0X104   /* Local space register values    */
DECL|macro|PCISH5_ICR_LSR1
mdefine_line|#define PCISH5_ICR_LSR1        0X108   /* Local space register values    */
DECL|macro|PCISH5_ICR_LAR0
mdefine_line|#define PCISH5_ICR_LAR0        0x10c   /* Local address register values  */
DECL|macro|PCISH5_ICR_LAR1
mdefine_line|#define PCISH5_ICR_LAR1        0x110   /* Local address register values  */
DECL|macro|PCISH5_ICR_INTM
mdefine_line|#define PCISH5_ICR_INTM        0x118   /* Interrupt mask register values                         */
DECL|macro|PCISH5_ICR_AIR
mdefine_line|#define PCISH5_ICR_AIR         0x11c   /* Interrupt error address information register values    */
DECL|macro|PCISH5_ICR_CIR
mdefine_line|#define PCISH5_ICR_CIR         0x120   /* Interrupt error command information register values    */
DECL|macro|PCISH5_ICR_AINT
mdefine_line|#define PCISH5_ICR_AINT        0x130   /* Interrupt error arbiter interrupt register values      */
DECL|macro|PCISH5_ICR_AINTM
mdefine_line|#define PCISH5_ICR_AINTM       0x134   /* Interrupt error arbiter interrupt mask register values */
DECL|macro|PCISH5_ICR_BMIR
mdefine_line|#define PCISH5_ICR_BMIR        0x138   /* Interrupt error info register of bus master values     */
DECL|macro|PCISH5_ICR_PAR
mdefine_line|#define PCISH5_ICR_PAR         0x1c0   /* Pio address register values                            */
DECL|macro|PCISH5_ICR_MBR
mdefine_line|#define PCISH5_ICR_MBR         0x1c4   /* Memory space bank register values                      */
DECL|macro|PCISH5_ICR_IOBR
mdefine_line|#define PCISH5_ICR_IOBR        0x1c8   /* I/O space bank register values                         */
DECL|macro|PCISH5_ICR_PINT
mdefine_line|#define PCISH5_ICR_PINT        0x1cc   /* power management interrupt register values             */
DECL|macro|PCISH5_ICR_PINTM
mdefine_line|#define PCISH5_ICR_PINTM       0x1d0   /* power management interrupt mask register values        */
DECL|macro|PCISH5_ICR_MBMR
mdefine_line|#define PCISH5_ICR_MBMR        0x1d8   /* memory space bank mask register values                 */
DECL|macro|PCISH5_ICR_IOBMR
mdefine_line|#define PCISH5_ICR_IOBMR       0x1dc   /* I/O space bank mask register values                    */
DECL|macro|PCISH5_ICR_CSCR0
mdefine_line|#define PCISH5_ICR_CSCR0       0x210   /* PCI cache snoop control register 0                     */
DECL|macro|PCISH5_ICR_CSCR1
mdefine_line|#define PCISH5_ICR_CSCR1       0x214   /* PCI cache snoop control register 1                     */
DECL|macro|PCISH5_ICR_PDR
mdefine_line|#define PCISH5_ICR_PDR         0x220   /* Pio data register values                               */
multiline_comment|/* These are configs space registers */
DECL|macro|PCISH5_ICR_CSR_VID
mdefine_line|#define PCISH5_ICR_CSR_VID     0x000&t;/* Vendor id                           */
DECL|macro|PCISH5_ICR_CSR_DID
mdefine_line|#define PCISH5_ICR_CSR_DID     0x002   /* Device id                           */
DECL|macro|PCISH5_ICR_CSR_CMD
mdefine_line|#define PCISH5_ICR_CSR_CMD     0x004   /* Command register                    */
DECL|macro|PCISH5_ICR_CSR_STATUS
mdefine_line|#define PCISH5_ICR_CSR_STATUS  0x006   /* Stautus                             */
DECL|macro|PCISH5_ICR_CSR_IBAR0
mdefine_line|#define PCISH5_ICR_CSR_IBAR0   0x010   /* I/O base address register           */
DECL|macro|PCISH5_ICR_CSR_MBAR0
mdefine_line|#define PCISH5_ICR_CSR_MBAR0   0x014   /* First  Memory base address register */
DECL|macro|PCISH5_ICR_CSR_MBAR1
mdefine_line|#define PCISH5_ICR_CSR_MBAR1   0x018   /* Second Memory base address register */
multiline_comment|/* Base address of registers */
DECL|macro|SH5PCI_ICR_BASE
mdefine_line|#define SH5PCI_ICR_BASE (PHYS_PCI_BLOCK + 0x00040000)
DECL|macro|SH5PCI_IO_BASE
mdefine_line|#define SH5PCI_IO_BASE  (PHYS_PCI_BLOCK + 0x00800000)
multiline_comment|/* #define SH5PCI_VCR_BASE (P2SEG_PCICB_BLOCK + P2SEG)    */
multiline_comment|/* Register selection macro */
DECL|macro|PCISH5_ICR_REG
mdefine_line|#define PCISH5_ICR_REG(x)                ( pcicr_virt + (PCISH5_ICR_##x))
multiline_comment|/* #define PCISH5_VCR_REG(x)                ( SH5PCI_VCR_BASE (PCISH5_VCR_##x)) */
multiline_comment|/* Write I/O functions */
DECL|macro|SH5PCI_WRITE
mdefine_line|#define SH5PCI_WRITE(reg,val)        ctrl_outl((u32)(val),PCISH5_ICR_REG(reg))
DECL|macro|SH5PCI_WRITE_SHORT
mdefine_line|#define SH5PCI_WRITE_SHORT(reg,val)  ctrl_outw((u16)(val),PCISH5_ICR_REG(reg))
DECL|macro|SH5PCI_WRITE_BYTE
mdefine_line|#define SH5PCI_WRITE_BYTE(reg,val)   ctrl_outb((u8)(val),PCISH5_ICR_REG(reg))
multiline_comment|/* Read I/O functions */
DECL|macro|SH5PCI_READ
mdefine_line|#define SH5PCI_READ(reg)             ctrl_inl(PCISH5_ICR_REG(reg))
DECL|macro|SH5PCI_READ_SHORT
mdefine_line|#define SH5PCI_READ_SHORT(reg)       ctrl_inw(PCISH5_ICR_REG(reg))
DECL|macro|SH5PCI_READ_BYTE
mdefine_line|#define SH5PCI_READ_BYTE(reg)        ctrl_inb(PCISH5_ICR_REG(reg))
multiline_comment|/* Set PCI config bits */
DECL|macro|SET_CONFIG_BITS
mdefine_line|#define SET_CONFIG_BITS(bus,devfn,where)  ((((bus) &lt;&lt; 16) | ((devfn) &lt;&lt; 8) | ((where) &amp; ~3)) | 0x80000000)
multiline_comment|/* Set PCI command register */
DECL|macro|CONFIG_CMD
mdefine_line|#define CONFIG_CMD(bus, devfn, where)            SET_CONFIG_BITS(bus-&gt;number,devfn,where)
multiline_comment|/* Size converters */
DECL|macro|PCISH5_MEM_SIZCONV
mdefine_line|#define PCISH5_MEM_SIZCONV(x)&t;&t;  (((x / 0x40000) - 1) &lt;&lt; 18)
DECL|macro|PCISH5_IO_SIZCONV
mdefine_line|#define PCISH5_IO_SIZCONV(x)&t;&t;  (((x / 0x40000) - 1) &lt;&lt; 18)
eof
