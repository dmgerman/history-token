multiline_comment|/*&n; * include/asm-ppc/m8260_pci.h&n; *&n; * Definitions for the MPC8250/MPC8265/MPC8266 integrated PCI host bridge.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __M8260_PCI_H
DECL|macro|__M8260_PCI_H
mdefine_line|#define __M8260_PCI_H
macro_line|#include &lt;linux/pci_ids.h&gt;
multiline_comment|/*&n; * Define the vendor/device ID for the MPC8265.&n; */
DECL|macro|PCI_DEVICE_ID_MPC8265
mdefine_line|#define&t;PCI_DEVICE_ID_MPC8265&t;((0x18C0 &lt;&lt; 16) | PCI_VENDOR_ID_MOTOROLA)
DECL|macro|M8265_PCIBR0
mdefine_line|#define M8265_PCIBR0&t;0x101ac
DECL|macro|M8265_PCIBR1
mdefine_line|#define M8265_PCIBR1&t;0x101b0
DECL|macro|M8265_PCIMSK0
mdefine_line|#define M8265_PCIMSK0&t;0x101c4
DECL|macro|M8265_PCIMSK1
mdefine_line|#define M8265_PCIMSK1&t;0x101c8
multiline_comment|/* Bit definitions for PCIBR registers */
DECL|macro|PCIBR_ENABLE
mdefine_line|#define PCIBR_ENABLE        0x00000001
multiline_comment|/* Bit definitions for PCIMSK registers */
DECL|macro|PCIMSK_32KiB
mdefine_line|#define PCIMSK_32KiB         0xFFFF8000  /* Size of window, smallest */
DECL|macro|PCIMSK_64KiB
mdefine_line|#define PCIMSK_64KiB         0xFFFF0000
DECL|macro|PCIMSK_128KiB
mdefine_line|#define PCIMSK_128KiB        0xFFFE0000
DECL|macro|PCIMSK_256KiB
mdefine_line|#define PCIMSK_256KiB        0xFFFC0000
DECL|macro|PCIMSK_512KiB
mdefine_line|#define PCIMSK_512KiB        0xFFF80000
DECL|macro|PCIMSK_1MiB
mdefine_line|#define PCIMSK_1MiB          0xFFF00000
DECL|macro|PCIMSK_2MiB
mdefine_line|#define PCIMSK_2MiB          0xFFE00000
DECL|macro|PCIMSK_4MiB
mdefine_line|#define PCIMSK_4MiB          0xFFC00000
DECL|macro|PCIMSK_8MiB
mdefine_line|#define PCIMSK_8MiB          0xFF800000
DECL|macro|PCIMSK_16MiB
mdefine_line|#define PCIMSK_16MiB         0xFF000000
DECL|macro|PCIMSK_32MiB
mdefine_line|#define PCIMSK_32MiB         0xFE000000
DECL|macro|PCIMSK_64MiB
mdefine_line|#define PCIMSK_64MiB         0xFC000000
DECL|macro|PCIMSK_128MiB
mdefine_line|#define PCIMSK_128MiB        0xF8000000
DECL|macro|PCIMSK_256MiB
mdefine_line|#define PCIMSK_256MiB        0xF0000000
DECL|macro|PCIMSK_512MiB
mdefine_line|#define PCIMSK_512MiB        0xE0000000
DECL|macro|PCIMSK_1GiB
mdefine_line|#define PCIMSK_1GiB          0xC0000000  /* Size of window, largest */
DECL|macro|M826X_SCCR_PCI_MODE_EN
mdefine_line|#define M826X_SCCR_PCI_MODE_EN 0x100
multiline_comment|/*&n; * Outbound ATU registers (3 sets). These registers control how 60x bus (local) &n; * addresses are translated to PCI addresses when the MPC826x is a PCI bus &n; * master (initiator).&n; */
DECL|macro|POTAR_REG0
mdefine_line|#define POTAR_REG0          0x10800     /* PCI Outbound Translation Addr registers */
DECL|macro|POTAR_REG1
mdefine_line|#define POTAR_REG1          0x10818
DECL|macro|POTAR_REG2
mdefine_line|#define POTAR_REG2          0x10830
DECL|macro|POBAR_REG0
mdefine_line|#define POBAR_REG0          0x10808     /* PCI Outbound Base Addr registers */
DECL|macro|POBAR_REG1
mdefine_line|#define POBAR_REG1          0x10820
DECL|macro|POBAR_REG2
mdefine_line|#define POBAR_REG2          0x10838
DECL|macro|POCMR_REG0
mdefine_line|#define POCMR_REG0          0x10810     /* PCI Outbound Comparison Mask registers */
DECL|macro|POCMR_REG1
mdefine_line|#define POCMR_REG1          0x10828
DECL|macro|POCMR_REG2
mdefine_line|#define POCMR_REG2          0x10840
multiline_comment|/* Bit definitions for POMCR registers */
DECL|macro|POCMR_MASK_4KiB
mdefine_line|#define POCMR_MASK_4KiB      0x000FFFFF
DECL|macro|POCMR_MASK_8KiB
mdefine_line|#define POCMR_MASK_8KiB      0x000FFFFE
DECL|macro|POCMR_MASK_16KiB
mdefine_line|#define POCMR_MASK_16KiB     0x000FFFFC
DECL|macro|POCMR_MASK_32KiB
mdefine_line|#define POCMR_MASK_32KiB     0x000FFFF8
DECL|macro|POCMR_MASK_64KiB
mdefine_line|#define POCMR_MASK_64KiB     0x000FFFF0
DECL|macro|POCMR_MASK_128KiB
mdefine_line|#define POCMR_MASK_128KiB    0x000FFFE0
DECL|macro|POCMR_MASK_256KiB
mdefine_line|#define POCMR_MASK_256KiB    0x000FFFC0
DECL|macro|POCMR_MASK_512KiB
mdefine_line|#define POCMR_MASK_512KiB    0x000FFF80
DECL|macro|POCMR_MASK_1MiB
mdefine_line|#define POCMR_MASK_1MiB      0x000FFF00
DECL|macro|POCMR_MASK_2MiB
mdefine_line|#define POCMR_MASK_2MiB      0x000FFE00
DECL|macro|POCMR_MASK_4MiB
mdefine_line|#define POCMR_MASK_4MiB      0x000FFC00
DECL|macro|POCMR_MASK_8MiB
mdefine_line|#define POCMR_MASK_8MiB      0x000FF800
DECL|macro|POCMR_MASK_16MiB
mdefine_line|#define POCMR_MASK_16MiB     0x000FF000
DECL|macro|POCMR_MASK_32MiB
mdefine_line|#define POCMR_MASK_32MiB     0x000FE000
DECL|macro|POCMR_MASK_64MiB
mdefine_line|#define POCMR_MASK_64MiB     0x000FC000
DECL|macro|POCMR_MASK_128MiB
mdefine_line|#define POCMR_MASK_128MiB    0x000F8000
DECL|macro|POCMR_MASK_256MiB
mdefine_line|#define POCMR_MASK_256MiB    0x000F0000
DECL|macro|POCMR_MASK_512MiB
mdefine_line|#define POCMR_MASK_512MiB    0x000E0000
DECL|macro|POCMR_MASK_1GiB
mdefine_line|#define POCMR_MASK_1GiB      0x000C0000
DECL|macro|POCMR_ENABLE
mdefine_line|#define POCMR_ENABLE        0x80000000
DECL|macro|POCMR_PCI_IO
mdefine_line|#define POCMR_PCI_IO        0x40000000
DECL|macro|POCMR_PREFETCH_EN
mdefine_line|#define POCMR_PREFETCH_EN   0x20000000
multiline_comment|/* Soft PCI reset */
DECL|macro|PCI_GCR_REG
mdefine_line|#define PCI_GCR_REG         0x10880
multiline_comment|/* Bit definitions for PCI_GCR registers */
DECL|macro|PCIGCR_PCI_BUS_EN
mdefine_line|#define PCIGCR_PCI_BUS_EN   0x1
DECL|macro|PCI_EMR_REG
mdefine_line|#define PCI_EMR_REG&t;    0x10888
multiline_comment|/*&n; * Inbound ATU registers (2 sets). These registers control how PCI addresses &n; * are translated to 60x bus (local) addresses when the MPC826x is a PCI bus target.&n; */
DECL|macro|PITAR_REG1
mdefine_line|#define PITAR_REG1          0x108D0
DECL|macro|PIBAR_REG1
mdefine_line|#define PIBAR_REG1          0x108D8
DECL|macro|PICMR_REG1
mdefine_line|#define PICMR_REG1          0x108E0
DECL|macro|PITAR_REG0
mdefine_line|#define PITAR_REG0          0x108E8
DECL|macro|PIBAR_REG0
mdefine_line|#define PIBAR_REG0          0x108F0
DECL|macro|PICMR_REG0
mdefine_line|#define PICMR_REG0          0x108F8
multiline_comment|/* Bit definitions for PCI Inbound Comparison Mask registers */
DECL|macro|PICMR_MASK_4KiB
mdefine_line|#define PICMR_MASK_4KiB       0x000FFFFF
DECL|macro|PICMR_MASK_8KiB
mdefine_line|#define PICMR_MASK_8KiB       0x000FFFFE
DECL|macro|PICMR_MASK_16KiB
mdefine_line|#define PICMR_MASK_16KiB      0x000FFFFC
DECL|macro|PICMR_MASK_32KiB
mdefine_line|#define PICMR_MASK_32KiB      0x000FFFF8
DECL|macro|PICMR_MASK_64KiB
mdefine_line|#define PICMR_MASK_64KiB      0x000FFFF0
DECL|macro|PICMR_MASK_128KiB
mdefine_line|#define PICMR_MASK_128KiB     0x000FFFE0
DECL|macro|PICMR_MASK_256KiB
mdefine_line|#define PICMR_MASK_256KiB     0x000FFFC0
DECL|macro|PICMR_MASK_512KiB
mdefine_line|#define PICMR_MASK_512KiB     0x000FFF80
DECL|macro|PICMR_MASK_1MiB
mdefine_line|#define PICMR_MASK_1MiB       0x000FFF00
DECL|macro|PICMR_MASK_2MiB
mdefine_line|#define PICMR_MASK_2MiB       0x000FFE00
DECL|macro|PICMR_MASK_4MiB
mdefine_line|#define PICMR_MASK_4MiB       0x000FFC00
DECL|macro|PICMR_MASK_8MiB
mdefine_line|#define PICMR_MASK_8MiB       0x000FF800
DECL|macro|PICMR_MASK_16MiB
mdefine_line|#define PICMR_MASK_16MiB      0x000FF000
DECL|macro|PICMR_MASK_32MiB
mdefine_line|#define PICMR_MASK_32MiB      0x000FE000
DECL|macro|PICMR_MASK_64MiB
mdefine_line|#define PICMR_MASK_64MiB      0x000FC000
DECL|macro|PICMR_MASK_128MiB
mdefine_line|#define PICMR_MASK_128MiB     0x000F8000
DECL|macro|PICMR_MASK_256MiB
mdefine_line|#define PICMR_MASK_256MiB     0x000F0000
DECL|macro|PICMR_MASK_512MiB
mdefine_line|#define PICMR_MASK_512MiB     0x000E0000
DECL|macro|PICMR_MASK_1GiB
mdefine_line|#define PICMR_MASK_1GiB       0x000C0000
DECL|macro|PICMR_ENABLE
mdefine_line|#define PICMR_ENABLE         0x80000000
DECL|macro|PICMR_NO_SNOOP_EN
mdefine_line|#define PICMR_NO_SNOOP_EN    0x40000000
DECL|macro|PICMR_PREFETCH_EN
mdefine_line|#define PICMR_PREFETCH_EN    0x20000000
multiline_comment|/* PCI error Registers */
DECL|macro|PCI_ERROR_STATUS_REG
mdefine_line|#define&t;PCI_ERROR_STATUS_REG&t;&t;0x10884
DECL|macro|PCI_ERROR_MASK_REG
mdefine_line|#define&t;PCI_ERROR_MASK_REG&t;&t;0x10888
DECL|macro|PCI_ERROR_CONTROL_REG
mdefine_line|#define&t;PCI_ERROR_CONTROL_REG&t;&t;0x1088C
DECL|macro|PCI_ERROR_ADRS_CAPTURE_REG
mdefine_line|#define PCI_ERROR_ADRS_CAPTURE_REG      0x10890
DECL|macro|PCI_ERROR_DATA_CAPTURE_REG
mdefine_line|#define PCI_ERROR_DATA_CAPTURE_REG      0x10898
DECL|macro|PCI_ERROR_CTRL_CAPTURE_REG
mdefine_line|#define PCI_ERROR_CTRL_CAPTURE_REG      0x108A0
multiline_comment|/* PCI error Register bit defines */
DECL|macro|PCI_ERROR_PCI_ADDR_PAR
mdefine_line|#define&t;PCI_ERROR_PCI_ADDR_PAR&t;&t;&t;0x00000001
DECL|macro|PCI_ERROR_PCI_DATA_PAR_WR
mdefine_line|#define&t;PCI_ERROR_PCI_DATA_PAR_WR&t;&t;0x00000002
DECL|macro|PCI_ERROR_PCI_DATA_PAR_RD
mdefine_line|#define&t;PCI_ERROR_PCI_DATA_PAR_RD&t;&t;0x00000004
DECL|macro|PCI_ERROR_PCI_NO_RSP
mdefine_line|#define&t;PCI_ERROR_PCI_NO_RSP&t;&t;&t;0x00000008
DECL|macro|PCI_ERROR_PCI_TAR_ABT
mdefine_line|#define&t;PCI_ERROR_PCI_TAR_ABT&t;&t;&t;0x00000010
DECL|macro|PCI_ERROR_PCI_SERR
mdefine_line|#define&t;PCI_ERROR_PCI_SERR&t;&t;&t;0x00000020
DECL|macro|PCI_ERROR_PCI_PERR_RD
mdefine_line|#define&t;PCI_ERROR_PCI_PERR_RD&t;&t;&t;0x00000040
DECL|macro|PCI_ERROR_PCI_PERR_WR
mdefine_line|#define&t;PCI_ERROR_PCI_PERR_WR&t;&t;&t;0x00000080
DECL|macro|PCI_ERROR_I2O_OFQO
mdefine_line|#define&t;PCI_ERROR_I2O_OFQO&t;&t;&t;0x00000100
DECL|macro|PCI_ERROR_I2O_IPQO
mdefine_line|#define&t;PCI_ERROR_I2O_IPQO&t;&t;&t;0x00000200
DECL|macro|PCI_ERROR_IRA
mdefine_line|#define&t;PCI_ERROR_IRA&t;&t;&t;&t;0x00000400
DECL|macro|PCI_ERROR_NMI
mdefine_line|#define&t;PCI_ERROR_NMI&t;&t;&t;&t;0x00000800
DECL|macro|PCI_ERROR_I2O_DBMC
mdefine_line|#define&t;PCI_ERROR_I2O_DBMC&t;&t;&t;0x00001000
multiline_comment|/*&n; * Register pair used to generate configuration cycles on the PCI bus&n; * and access the MPC826x&squot;s own PCI configuration registers.&n; */
DECL|macro|PCI_CFG_ADDR_REG
mdefine_line|#define PCI_CFG_ADDR_REG     0x10900
DECL|macro|PCI_CFG_DATA_REG
mdefine_line|#define PCI_CFG_DATA_REG     0x10904
multiline_comment|/* Bus parking decides where the bus control sits when idle */
multiline_comment|/* If modifying memory controllers for PCI park on the core */
DECL|macro|PPC_ACR_BUS_PARK_CORE
mdefine_line|#define PPC_ACR_BUS_PARK_CORE 0x6
DECL|macro|PPC_ACR_BUS_PARK_PCI
mdefine_line|#define PPC_ACR_BUS_PARK_PCI  0x3
macro_line|#endif /* __M8260_PCI_H */
macro_line|#endif /* __KERNEL__ */
eof
