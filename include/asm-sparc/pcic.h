multiline_comment|/* $Id: pcic.h,v 1.4 1999/11/17 07:34:20 zaitcev Exp $&n; * pcic.h: JavaEngine 1 specific PCI definitions.&n; *&n; * Copyright (C) 1998 V. Roganov and G. Raiko&n; */
macro_line|#ifndef __SPARC_PCIC_H
DECL|macro|__SPARC_PCIC_H
mdefine_line|#define __SPARC_PCIC_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/pbm.h&gt;
DECL|struct|linux_pcic
r_struct
id|linux_pcic
(brace
DECL|member|pcic_regs
r_int
r_int
id|pcic_regs
suffix:semicolon
DECL|member|pcic_io
r_int
r_int
id|pcic_io
suffix:semicolon
DECL|member|pcic_config_space_addr
r_int
r_int
id|pcic_config_space_addr
suffix:semicolon
DECL|member|pcic_config_space_data
r_int
r_int
id|pcic_config_space_data
suffix:semicolon
DECL|member|pcic_res_regs
r_struct
id|resource
id|pcic_res_regs
suffix:semicolon
DECL|member|pcic_res_io
r_struct
id|resource
id|pcic_res_io
suffix:semicolon
DECL|member|pcic_res_cfg_addr
r_struct
id|resource
id|pcic_res_cfg_addr
suffix:semicolon
DECL|member|pcic_res_cfg_data
r_struct
id|resource
id|pcic_res_cfg_data
suffix:semicolon
DECL|member|pbm
r_struct
id|linux_pbm_info
id|pbm
suffix:semicolon
DECL|member|pcic_imap
r_struct
id|pcic_ca2irq
op_star
id|pcic_imap
suffix:semicolon
DECL|member|pcic_imdim
r_int
id|pcic_imdim
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|pcic_probe
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Erm... MJ redefined pcibios_present() so that it does not work early. */
r_extern
r_int
id|pcic_present
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sun4m_pci_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Size of PCI I/O space which we relocate. */
DECL|macro|PCI_SPACE_SIZE
mdefine_line|#define PCI_SPACE_SIZE                  0x1000000       /* 16 MB */
multiline_comment|/* PCIC Register Set. */
DECL|macro|PCI_DIAGNOSTIC_0
mdefine_line|#define PCI_DIAGNOSTIC_0                0x40    /* 32 bits */
DECL|macro|PCI_SIZE_0
mdefine_line|#define PCI_SIZE_0                      0x44    /* 32 bits */
DECL|macro|PCI_SIZE_1
mdefine_line|#define PCI_SIZE_1                      0x48    /* 32 bits */
DECL|macro|PCI_SIZE_2
mdefine_line|#define PCI_SIZE_2                      0x4c    /* 32 bits */
DECL|macro|PCI_SIZE_3
mdefine_line|#define PCI_SIZE_3                      0x50    /* 32 bits */
DECL|macro|PCI_SIZE_4
mdefine_line|#define PCI_SIZE_4                      0x54    /* 32 bits */
DECL|macro|PCI_SIZE_5
mdefine_line|#define PCI_SIZE_5                      0x58    /* 32 bits */
DECL|macro|PCI_PIO_CONTROL
mdefine_line|#define PCI_PIO_CONTROL                 0x60    /* 8  bits */
DECL|macro|PCI_DVMA_CONTROL
mdefine_line|#define PCI_DVMA_CONTROL                0x62    /* 8  bits */
DECL|macro|PCI_DVMA_CONTROL_INACTIVITY_REQ
mdefine_line|#define  PCI_DVMA_CONTROL_INACTIVITY_REQ        (1&lt;&lt;0)
DECL|macro|PCI_DVMA_CONTROL_IOTLB_ENABLE
mdefine_line|#define  PCI_DVMA_CONTROL_IOTLB_ENABLE          (1&lt;&lt;0)
DECL|macro|PCI_DVMA_CONTROL_IOTLB_DISABLE
mdefine_line|#define  PCI_DVMA_CONTROL_IOTLB_DISABLE         0
DECL|macro|PCI_DVMA_CONTROL_INACTIVITY_ACK
mdefine_line|#define  PCI_DVMA_CONTROL_INACTIVITY_ACK        (1&lt;&lt;4)
DECL|macro|PCI_INTERRUPT_CONTROL
mdefine_line|#define PCI_INTERRUPT_CONTROL           0x63    /* 8  bits */
DECL|macro|PCI_CPU_INTERRUPT_PENDING
mdefine_line|#define PCI_CPU_INTERRUPT_PENDING       0x64    /* 32 bits */
DECL|macro|PCI_DIAGNOSTIC_1
mdefine_line|#define PCI_DIAGNOSTIC_1                0x68    /* 16 bits */
DECL|macro|PCI_SOFTWARE_INT_CLEAR
mdefine_line|#define PCI_SOFTWARE_INT_CLEAR          0x6a    /* 16 bits */
DECL|macro|PCI_SOFTWARE_INT_SET
mdefine_line|#define PCI_SOFTWARE_INT_SET            0x6e    /* 16 bits */
DECL|macro|PCI_SYS_INT_PENDING
mdefine_line|#define PCI_SYS_INT_PENDING             0x70    /* 32 bits */
DECL|macro|PCI_SYS_INT_PENDING_PIO
mdefine_line|#define  PCI_SYS_INT_PENDING_PIO&t;&t;0x40000000
DECL|macro|PCI_SYS_INT_PENDING_DMA
mdefine_line|#define  PCI_SYS_INT_PENDING_DMA&t;&t;0x20000000
DECL|macro|PCI_SYS_INT_PENDING_PCI
mdefine_line|#define  PCI_SYS_INT_PENDING_PCI&t;&t;0x10000000
DECL|macro|PCI_SYS_INT_PENDING_APSR
mdefine_line|#define  PCI_SYS_INT_PENDING_APSR&t;&t;0x08000000
DECL|macro|PCI_SYS_INT_TARGET_MASK
mdefine_line|#define PCI_SYS_INT_TARGET_MASK         0x74    /* 32 bits */
DECL|macro|PCI_SYS_INT_TARGET_MASK_CLEAR
mdefine_line|#define PCI_SYS_INT_TARGET_MASK_CLEAR   0x78    /* 32 bits */
DECL|macro|PCI_SYS_INT_TARGET_MASK_SET
mdefine_line|#define PCI_SYS_INT_TARGET_MASK_SET     0x7c    /* 32 bits */
DECL|macro|PCI_SYS_INT_PENDING_CLEAR
mdefine_line|#define PCI_SYS_INT_PENDING_CLEAR       0x83    /* 8  bits */
DECL|macro|PCI_SYS_INT_PENDING_CLEAR_ALL
mdefine_line|#define  PCI_SYS_INT_PENDING_CLEAR_ALL&t;&t;0x80
DECL|macro|PCI_SYS_INT_PENDING_CLEAR_PIO
mdefine_line|#define  PCI_SYS_INT_PENDING_CLEAR_PIO&t;&t;0x40
DECL|macro|PCI_SYS_INT_PENDING_CLEAR_DMA
mdefine_line|#define  PCI_SYS_INT_PENDING_CLEAR_DMA&t;&t;0x20
DECL|macro|PCI_SYS_INT_PENDING_CLEAR_PCI
mdefine_line|#define  PCI_SYS_INT_PENDING_CLEAR_PCI&t;&t;0x10
DECL|macro|PCI_IOTLB_CONTROL
mdefine_line|#define PCI_IOTLB_CONTROL               0x84    /* 8  bits */
DECL|macro|PCI_INT_SELECT_LO
mdefine_line|#define PCI_INT_SELECT_LO               0x88    /* 16 bits */
DECL|macro|PCI_ARBITRATION_SELECT
mdefine_line|#define PCI_ARBITRATION_SELECT          0x8a    /* 16 bits */
DECL|macro|PCI_INT_SELECT_HI
mdefine_line|#define PCI_INT_SELECT_HI               0x8c    /* 16 bits */
DECL|macro|PCI_HW_INT_OUTPUT
mdefine_line|#define PCI_HW_INT_OUTPUT               0x8e    /* 16 bits */
DECL|macro|PCI_IOTLB_RAM_INPUT
mdefine_line|#define PCI_IOTLB_RAM_INPUT             0x90    /* 32 bits */
DECL|macro|PCI_IOTLB_CAM_INPUT
mdefine_line|#define PCI_IOTLB_CAM_INPUT             0x94    /* 32 bits */
DECL|macro|PCI_IOTLB_RAM_OUTPUT
mdefine_line|#define PCI_IOTLB_RAM_OUTPUT            0x98    /* 32 bits */
DECL|macro|PCI_IOTLB_CAM_OUTPUT
mdefine_line|#define PCI_IOTLB_CAM_OUTPUT            0x9c    /* 32 bits */
DECL|macro|PCI_SMBAR0
mdefine_line|#define PCI_SMBAR0                      0xa0    /* 8  bits */
DECL|macro|PCI_MSIZE0
mdefine_line|#define PCI_MSIZE0                      0xa1    /* 8  bits */
DECL|macro|PCI_PMBAR0
mdefine_line|#define PCI_PMBAR0                      0xa2    /* 8  bits */
DECL|macro|PCI_SMBAR1
mdefine_line|#define PCI_SMBAR1                      0xa4    /* 8  bits */
DECL|macro|PCI_MSIZE1
mdefine_line|#define PCI_MSIZE1                      0xa5    /* 8  bits */
DECL|macro|PCI_PMBAR1
mdefine_line|#define PCI_PMBAR1                      0xa6    /* 8  bits */
DECL|macro|PCI_SIBAR
mdefine_line|#define PCI_SIBAR                       0xa8    /* 8  bits */
DECL|macro|PCI_SIBAR_ADDRESS_MASK
mdefine_line|#define   PCI_SIBAR_ADDRESS_MASK        0xf
DECL|macro|PCI_ISIZE
mdefine_line|#define PCI_ISIZE                       0xa9    /* 8  bits */
DECL|macro|PCI_ISIZE_16M
mdefine_line|#define   PCI_ISIZE_16M                 0xf
DECL|macro|PCI_ISIZE_32M
mdefine_line|#define   PCI_ISIZE_32M                 0xe
DECL|macro|PCI_ISIZE_64M
mdefine_line|#define   PCI_ISIZE_64M                 0xc
DECL|macro|PCI_ISIZE_128M
mdefine_line|#define   PCI_ISIZE_128M                0x8
DECL|macro|PCI_ISIZE_256M
mdefine_line|#define   PCI_ISIZE_256M                0x0
DECL|macro|PCI_PIBAR
mdefine_line|#define PCI_PIBAR                       0xaa    /* 8  bits */
DECL|macro|PCI_CPU_COUNTER_LIMIT_HI
mdefine_line|#define PCI_CPU_COUNTER_LIMIT_HI        0xac    /* 32 bits */
DECL|macro|PCI_CPU_COUNTER_LIMIT_LO
mdefine_line|#define PCI_CPU_COUNTER_LIMIT_LO        0xb0    /* 32 bits */
DECL|macro|PCI_CPU_COUNTER_LIMIT
mdefine_line|#define PCI_CPU_COUNTER_LIMIT           0xb4    /* 32 bits */
DECL|macro|PCI_SYS_LIMIT
mdefine_line|#define PCI_SYS_LIMIT                   0xb8    /* 32 bits */
DECL|macro|PCI_SYS_COUNTER
mdefine_line|#define PCI_SYS_COUNTER                 0xbc    /* 32 bits */
DECL|macro|PCI_SYS_COUNTER_OVERFLOW
mdefine_line|#define   PCI_SYS_COUNTER_OVERFLOW      (1&lt;&lt;31) /* Limit reached */
DECL|macro|PCI_SYS_LIMIT_PSEUDO
mdefine_line|#define PCI_SYS_LIMIT_PSEUDO            0xc0    /* 32 bits */
DECL|macro|PCI_USER_TIMER_CONTROL
mdefine_line|#define PCI_USER_TIMER_CONTROL          0xc4    /* 8  bits */
DECL|macro|PCI_USER_TIMER_CONFIG
mdefine_line|#define PCI_USER_TIMER_CONFIG           0xc5    /* 8  bits */
DECL|macro|PCI_COUNTER_IRQ
mdefine_line|#define PCI_COUNTER_IRQ                 0xc6    /* 8  bits */
DECL|macro|PCI_COUNTER_IRQ_SET
mdefine_line|#define  PCI_COUNTER_IRQ_SET(sys_irq, cpu_irq)  ((((sys_irq) &amp; 0xf) &lt;&lt; 4) | &bslash;&n;                                                  ((cpu_irq) &amp; 0xf))
DECL|macro|PCI_COUNTER_IRQ_SYS
mdefine_line|#define  PCI_COUNTER_IRQ_SYS(v)                 (((v) &gt;&gt; 4) &amp; 0xf)
DECL|macro|PCI_COUNTER_IRQ_CPU
mdefine_line|#define  PCI_COUNTER_IRQ_CPU(v)                 ((v) &amp; 0xf)
DECL|macro|PCI_PIO_ERROR_COMMAND
mdefine_line|#define PCI_PIO_ERROR_COMMAND           0xc7    /* 8  bits */
DECL|macro|PCI_PIO_ERROR_ADDRESS
mdefine_line|#define PCI_PIO_ERROR_ADDRESS           0xc8    /* 32 bits */
DECL|macro|PCI_IOTLB_ERROR_ADDRESS
mdefine_line|#define PCI_IOTLB_ERROR_ADDRESS         0xcc    /* 32 bits */
DECL|macro|PCI_SYS_STATUS
mdefine_line|#define PCI_SYS_STATUS                  0xd0    /* 8  bits */
DECL|macro|PCI_SYS_STATUS_RESET_ENABLE
mdefine_line|#define   PCI_SYS_STATUS_RESET_ENABLE           (1&lt;&lt;0)
DECL|macro|PCI_SYS_STATUS_RESET
mdefine_line|#define   PCI_SYS_STATUS_RESET                  (1&lt;&lt;1)
DECL|macro|PCI_SYS_STATUS_WATCHDOG_RESET
mdefine_line|#define   PCI_SYS_STATUS_WATCHDOG_RESET         (1&lt;&lt;4)
DECL|macro|PCI_SYS_STATUS_PCI_RESET
mdefine_line|#define   PCI_SYS_STATUS_PCI_RESET              (1&lt;&lt;5)
DECL|macro|PCI_SYS_STATUS_PCI_RESET_ENABLE
mdefine_line|#define   PCI_SYS_STATUS_PCI_RESET_ENABLE       (1&lt;&lt;6)
DECL|macro|PCI_SYS_STATUS_PCI_SATTELITE_MODE
mdefine_line|#define   PCI_SYS_STATUS_PCI_SATTELITE_MODE     (1&lt;&lt;7)
macro_line|#endif /* !(__SPARC_PCIC_H) */
eof
