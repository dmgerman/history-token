multiline_comment|/*&n; * arch/ppc/platforms/adir.h&n; * &n; * Definitions for SBS Adirondack board support&n; *&n; * By Michael Sokolov &lt;msokolov@ivan.Harhan.ORG&gt;&n; */
macro_line|#ifndef __PPC_PLATFORMS_ADIR_H
DECL|macro|__PPC_PLATFORMS_ADIR_H
mdefine_line|#define __PPC_PLATFORMS_ADIR_H
multiline_comment|/*&n; * SBS Adirondack definitions&n; */
multiline_comment|/* PPC physical address space layout. We use the one set up by the firmware. */
DECL|macro|ADIR_PCI32_MEM_BASE
mdefine_line|#define&t;ADIR_PCI32_MEM_BASE&t;0x80000000
DECL|macro|ADIR_PCI32_MEM_SIZE
mdefine_line|#define&t;ADIR_PCI32_MEM_SIZE&t;0x20000000
DECL|macro|ADIR_PCI64_MEM_BASE
mdefine_line|#define&t;ADIR_PCI64_MEM_BASE&t;0xA0000000
DECL|macro|ADIR_PCI64_MEM_SIZE
mdefine_line|#define&t;ADIR_PCI64_MEM_SIZE&t;0x20000000
DECL|macro|ADIR_PCI32_IO_BASE
mdefine_line|#define&t;ADIR_PCI32_IO_BASE&t;0xC0000000
DECL|macro|ADIR_PCI32_IO_SIZE
mdefine_line|#define&t;ADIR_PCI32_IO_SIZE&t;0x10000000
DECL|macro|ADIR_PCI64_IO_BASE
mdefine_line|#define&t;ADIR_PCI64_IO_BASE&t;0xD0000000
DECL|macro|ADIR_PCI64_IO_SIZE
mdefine_line|#define&t;ADIR_PCI64_IO_SIZE&t;0x10000000
DECL|macro|ADIR_PCI64_PHB
mdefine_line|#define&t;ADIR_PCI64_PHB&t;&t;0xFF400000
DECL|macro|ADIR_PCI32_PHB
mdefine_line|#define&t;ADIR_PCI32_PHB&t;&t;0xFF500000
DECL|macro|ADIR_PCI64_CONFIG_ADDR
mdefine_line|#define ADIR_PCI64_CONFIG_ADDR&t;(ADIR_PCI64_PHB + 0x000f8000)
DECL|macro|ADIR_PCI64_CONFIG_DATA
mdefine_line|#define ADIR_PCI64_CONFIG_DATA&t;(ADIR_PCI64_PHB + 0x000f8010)
DECL|macro|ADIR_PCI32_CONFIG_ADDR
mdefine_line|#define ADIR_PCI32_CONFIG_ADDR&t;(ADIR_PCI32_PHB + 0x000f8000)
DECL|macro|ADIR_PCI32_CONFIG_DATA
mdefine_line|#define ADIR_PCI32_CONFIG_DATA&t;(ADIR_PCI32_PHB + 0x000f8010)
multiline_comment|/* System memory as seen from PCI */
DECL|macro|ADIR_PCI_SYS_MEM_BASE
mdefine_line|#define ADIR_PCI_SYS_MEM_BASE&t;0x80000000
multiline_comment|/* Static virtual mapping of PCI I/O */
DECL|macro|ADIR_PCI32_VIRT_IO_BASE
mdefine_line|#define&t;ADIR_PCI32_VIRT_IO_BASE&t;0xFE000000
DECL|macro|ADIR_PCI32_VIRT_IO_SIZE
mdefine_line|#define&t;ADIR_PCI32_VIRT_IO_SIZE&t;0x01000000
DECL|macro|ADIR_PCI64_VIRT_IO_BASE
mdefine_line|#define&t;ADIR_PCI64_VIRT_IO_BASE&t;0xFF000000
DECL|macro|ADIR_PCI64_VIRT_IO_SIZE
mdefine_line|#define&t;ADIR_PCI64_VIRT_IO_SIZE&t;0x01000000
multiline_comment|/* Registers */
DECL|macro|ADIR_NVRAM_RTC_ADDR
mdefine_line|#define&t;ADIR_NVRAM_RTC_ADDR&t;0x74
DECL|macro|ADIR_NVRAM_RTC_DATA
mdefine_line|#define&t;ADIR_NVRAM_RTC_DATA&t;0x75
DECL|macro|ADIR_BOARD_ID_REG
mdefine_line|#define&t;ADIR_BOARD_ID_REG&t;(ADIR_PCI32_VIRT_IO_BASE + 0x08FFF0)
DECL|macro|ADIR_CPLD1REV_REG
mdefine_line|#define&t;ADIR_CPLD1REV_REG&t;(ADIR_PCI32_VIRT_IO_BASE + 0x08FFF1)
DECL|macro|ADIR_CPLD2REV_REG
mdefine_line|#define&t;ADIR_CPLD2REV_REG&t;(ADIR_PCI32_VIRT_IO_BASE + 0x08FFF2)
DECL|macro|ADIR_FLASHCTL_REG
mdefine_line|#define&t;ADIR_FLASHCTL_REG&t;(ADIR_PCI32_VIRT_IO_BASE + 0x08FFF3)
DECL|macro|ADIR_CPC710_STAT_REG
mdefine_line|#define&t;ADIR_CPC710_STAT_REG&t;(ADIR_PCI32_VIRT_IO_BASE + 0x08FFF4)
DECL|macro|ADIR_CLOCK_REG
mdefine_line|#define&t;ADIR_CLOCK_REG&t;&t;(ADIR_PCI32_VIRT_IO_BASE + 0x08FFF5)
DECL|macro|ADIR_GPIO_REG
mdefine_line|#define&t;ADIR_GPIO_REG&t;&t;(ADIR_PCI32_VIRT_IO_BASE + 0x08FFF8)
DECL|macro|ADIR_MISC_REG
mdefine_line|#define&t;ADIR_MISC_REG&t;&t;(ADIR_PCI32_VIRT_IO_BASE + 0x08FFF9)
DECL|macro|ADIR_LED_REG
mdefine_line|#define&t;ADIR_LED_REG&t;&t;(ADIR_PCI32_VIRT_IO_BASE + 0x08FFFA)
DECL|macro|ADIR_CLOCK_REG_PD
mdefine_line|#define&t;ADIR_CLOCK_REG_PD&t;0x10
DECL|macro|ADIR_CLOCK_REG_SPREAD
mdefine_line|#define&t;ADIR_CLOCK_REG_SPREAD&t;0x08
DECL|macro|ADIR_CLOCK_REG_SEL133
mdefine_line|#define&t;ADIR_CLOCK_REG_SEL133&t;0x04
DECL|macro|ADIR_CLOCK_REG_SEL1
mdefine_line|#define&t;ADIR_CLOCK_REG_SEL1&t;0x02
DECL|macro|ADIR_CLOCK_REG_SEL0
mdefine_line|#define&t;ADIR_CLOCK_REG_SEL0&t;0x01
DECL|macro|ADIR_PROCA_INT_MASK
mdefine_line|#define&t;ADIR_PROCA_INT_MASK&t;(ADIR_PCI32_VIRT_IO_BASE + 0x0EFFF0)
DECL|macro|ADIR_PROCB_INT_MASK
mdefine_line|#define&t;ADIR_PROCB_INT_MASK&t;(ADIR_PCI32_VIRT_IO_BASE + 0x0EFFF2)
DECL|macro|ADIR_PROCA_INT_STAT
mdefine_line|#define&t;ADIR_PROCA_INT_STAT&t;(ADIR_PCI32_VIRT_IO_BASE + 0x0EFFF4)
DECL|macro|ADIR_PROCB_INT_STAT
mdefine_line|#define&t;ADIR_PROCB_INT_STAT&t;(ADIR_PCI32_VIRT_IO_BASE + 0x0EFFF6)
multiline_comment|/* Linux IRQ numbers */
DECL|macro|ADIR_IRQ_NONE
mdefine_line|#define&t;ADIR_IRQ_NONE&t;&t;-1
DECL|macro|ADIR_IRQ_SERIAL2
mdefine_line|#define&t;ADIR_IRQ_SERIAL2&t;3
DECL|macro|ADIR_IRQ_SERIAL1
mdefine_line|#define&t;ADIR_IRQ_SERIAL1&t;4
DECL|macro|ADIR_IRQ_FDC
mdefine_line|#define&t;ADIR_IRQ_FDC&t;&t;6
DECL|macro|ADIR_IRQ_PARALLEL
mdefine_line|#define&t;ADIR_IRQ_PARALLEL&t;7
DECL|macro|ADIR_IRQ_VIA_AUDIO
mdefine_line|#define&t;ADIR_IRQ_VIA_AUDIO&t;10
DECL|macro|ADIR_IRQ_VIA_USB
mdefine_line|#define&t;ADIR_IRQ_VIA_USB&t;11
DECL|macro|ADIR_IRQ_IDE0
mdefine_line|#define&t;ADIR_IRQ_IDE0&t;&t;14
DECL|macro|ADIR_IRQ_IDE1
mdefine_line|#define&t;ADIR_IRQ_IDE1&t;&t;15
DECL|macro|ADIR_IRQ_PCI0_INTA
mdefine_line|#define&t;ADIR_IRQ_PCI0_INTA&t;16
DECL|macro|ADIR_IRQ_PCI0_INTB
mdefine_line|#define&t;ADIR_IRQ_PCI0_INTB&t;17
DECL|macro|ADIR_IRQ_PCI0_INTC
mdefine_line|#define&t;ADIR_IRQ_PCI0_INTC&t;18
DECL|macro|ADIR_IRQ_PCI0_INTD
mdefine_line|#define&t;ADIR_IRQ_PCI0_INTD&t;19
DECL|macro|ADIR_IRQ_PCI1_INTA
mdefine_line|#define&t;ADIR_IRQ_PCI1_INTA&t;20
DECL|macro|ADIR_IRQ_PCI1_INTB
mdefine_line|#define&t;ADIR_IRQ_PCI1_INTB&t;21
DECL|macro|ADIR_IRQ_PCI1_INTC
mdefine_line|#define&t;ADIR_IRQ_PCI1_INTC&t;22
DECL|macro|ADIR_IRQ_PCI1_INTD
mdefine_line|#define&t;ADIR_IRQ_PCI1_INTD&t;23
DECL|macro|ADIR_IRQ_MBSCSI
mdefine_line|#define&t;ADIR_IRQ_MBSCSI&t;&t;24&t;/* motherboard SCSI */
DECL|macro|ADIR_IRQ_MBETH1
mdefine_line|#define&t;ADIR_IRQ_MBETH1&t;&t;25&t;/* motherboard Ethernet 1 */
DECL|macro|ADIR_IRQ_MBETH0
mdefine_line|#define&t;ADIR_IRQ_MBETH0&t;&t;26&t;/* motherboard Ethernet 0 */
DECL|macro|ADIR_IRQ_CPC710_INT1
mdefine_line|#define&t;ADIR_IRQ_CPC710_INT1&t;27
DECL|macro|ADIR_IRQ_CPC710_INT2
mdefine_line|#define&t;ADIR_IRQ_CPC710_INT2&t;28
DECL|macro|ADIR_IRQ_VT82C686_NMI
mdefine_line|#define&t;ADIR_IRQ_VT82C686_NMI&t;29
DECL|macro|ADIR_IRQ_VT82C686_INTR
mdefine_line|#define&t;ADIR_IRQ_VT82C686_INTR&t;30
DECL|macro|ADIR_IRQ_INTERPROC
mdefine_line|#define&t;ADIR_IRQ_INTERPROC&t;31
macro_line|#endif /* __PPC_PLATFORMS_ADIR_H */
eof
