multiline_comment|/*&n; * include/asm-mips/vr41xx/vr41xx.h&n; *&n; * Include file for NEC VR4100 series.&n; *&n; * Copyright (C) 1999 Michael Klar&n; * Copyright (C) 2001, 2002 Paul Mundt&n; * Copyright (C) 2002 MontaVista Software, Inc.&n; * Copyright (C) 2002 TimeSys Corp.&n; * Copyright (C) 2003-2004 Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __NEC_VR41XX_H
DECL|macro|__NEC_VR41XX_H
mdefine_line|#define __NEC_VR41XX_H
macro_line|#include &lt;linux/interrupt.h&gt;
multiline_comment|/*&n; * CPU Revision&n; */
multiline_comment|/* VR4122 0x00000c70-0x00000c72 */
DECL|macro|PRID_VR4122_REV1_0
mdefine_line|#define PRID_VR4122_REV1_0&t;0x00000c70
DECL|macro|PRID_VR4122_REV2_0
mdefine_line|#define PRID_VR4122_REV2_0&t;0x00000c70
DECL|macro|PRID_VR4122_REV2_1
mdefine_line|#define PRID_VR4122_REV2_1&t;0x00000c70
DECL|macro|PRID_VR4122_REV3_0
mdefine_line|#define PRID_VR4122_REV3_0&t;0x00000c71
DECL|macro|PRID_VR4122_REV3_1
mdefine_line|#define PRID_VR4122_REV3_1&t;0x00000c72
multiline_comment|/* VR4181A 0x00000c73-0x00000c7f */
DECL|macro|PRID_VR4181A_REV1_0
mdefine_line|#define PRID_VR4181A_REV1_0&t;0x00000c73
DECL|macro|PRID_VR4181A_REV1_1
mdefine_line|#define PRID_VR4181A_REV1_1&t;0x00000c74
multiline_comment|/* VR4131 0x00000c80-0x00000c83 */
DECL|macro|PRID_VR4131_REV1_2
mdefine_line|#define PRID_VR4131_REV1_2&t;0x00000c80
DECL|macro|PRID_VR4131_REV2_0
mdefine_line|#define PRID_VR4131_REV2_0&t;0x00000c81
DECL|macro|PRID_VR4131_REV2_1
mdefine_line|#define PRID_VR4131_REV2_1&t;0x00000c82
DECL|macro|PRID_VR4131_REV2_2
mdefine_line|#define PRID_VR4131_REV2_2&t;0x00000c83
multiline_comment|/* VR4133 0x00000c84- */
DECL|macro|PRID_VR4133
mdefine_line|#define PRID_VR4133&t;&t;0x00000c84
multiline_comment|/*&n; * Bus Control Uint&n; */
r_extern
r_int
r_int
id|vr41xx_calculate_clock_frequency
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|vr41xx_get_vtclock_frequency
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|vr41xx_get_tclock_frequency
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Clock Mask Unit&n; */
r_typedef
r_enum
(brace
DECL|enumerator|PIU_CLOCK
id|PIU_CLOCK
comma
DECL|enumerator|SIU_CLOCK
id|SIU_CLOCK
comma
DECL|enumerator|AIU_CLOCK
id|AIU_CLOCK
comma
DECL|enumerator|KIU_CLOCK
id|KIU_CLOCK
comma
DECL|enumerator|FIR_CLOCK
id|FIR_CLOCK
comma
DECL|enumerator|DSIU_CLOCK
id|DSIU_CLOCK
comma
DECL|enumerator|CSI_CLOCK
id|CSI_CLOCK
comma
DECL|enumerator|PCIU_CLOCK
id|PCIU_CLOCK
comma
DECL|enumerator|HSP_CLOCK
id|HSP_CLOCK
comma
DECL|enumerator|PCI_CLOCK
id|PCI_CLOCK
comma
DECL|enumerator|CEU_CLOCK
id|CEU_CLOCK
comma
DECL|enumerator|ETHER0_CLOCK
id|ETHER0_CLOCK
comma
DECL|enumerator|ETHER1_CLOCK
id|ETHER1_CLOCK
DECL|typedef|vr41xx_clock_t
)brace
id|vr41xx_clock_t
suffix:semicolon
r_extern
r_void
id|vr41xx_supply_clock
c_func
(paren
id|vr41xx_clock_t
id|clock
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_mask_clock
c_func
(paren
id|vr41xx_clock_t
id|clock
)paren
suffix:semicolon
multiline_comment|/*&n; * Interrupt Control Unit&n; */
multiline_comment|/* CPU core Interrupt Numbers */
DECL|macro|MIPS_CPU_IRQ_BASE
mdefine_line|#define MIPS_CPU_IRQ_BASE&t;0
DECL|macro|MIPS_CPU_IRQ
mdefine_line|#define MIPS_CPU_IRQ(x)&t;&t;(MIPS_CPU_IRQ_BASE + (x))
DECL|macro|MIPS_SOFTINT0_IRQ
mdefine_line|#define MIPS_SOFTINT0_IRQ&t;MIPS_CPU_IRQ(0)
DECL|macro|MIPS_SOFTINT1_IRQ
mdefine_line|#define MIPS_SOFTINT1_IRQ&t;MIPS_CPU_IRQ(1)
DECL|macro|INT0_CASCADE_IRQ
mdefine_line|#define INT0_CASCADE_IRQ&t;MIPS_CPU_IRQ(2)
DECL|macro|INT1_CASCADE_IRQ
mdefine_line|#define INT1_CASCADE_IRQ&t;MIPS_CPU_IRQ(3)
DECL|macro|INT2_CASCADE_IRQ
mdefine_line|#define INT2_CASCADE_IRQ&t;MIPS_CPU_IRQ(4)
DECL|macro|INT3_CASCADE_IRQ
mdefine_line|#define INT3_CASCADE_IRQ&t;MIPS_CPU_IRQ(5)
DECL|macro|INT4_CASCADE_IRQ
mdefine_line|#define INT4_CASCADE_IRQ&t;MIPS_CPU_IRQ(6)
DECL|macro|MIPS_COUNTER_IRQ
mdefine_line|#define MIPS_COUNTER_IRQ&t;MIPS_CPU_IRQ(7)
multiline_comment|/* SYINT1 Interrupt Numbers */
DECL|macro|SYSINT1_IRQ_BASE
mdefine_line|#define SYSINT1_IRQ_BASE&t;8
DECL|macro|SYSINT1_IRQ
mdefine_line|#define SYSINT1_IRQ(x)&t;&t;(SYSINT1_IRQ_BASE + (x))
DECL|macro|BATTRY_IRQ
mdefine_line|#define BATTRY_IRQ&t;&t;SYSINT1_IRQ(0)
DECL|macro|POWER_IRQ
mdefine_line|#define POWER_IRQ&t;&t;SYSINT1_IRQ(1)
DECL|macro|RTCLONG1_IRQ
mdefine_line|#define RTCLONG1_IRQ&t;&t;SYSINT1_IRQ(2)
DECL|macro|ELAPSEDTIME_IRQ
mdefine_line|#define ELAPSEDTIME_IRQ&t;&t;SYSINT1_IRQ(3)
multiline_comment|/* RFU */
DECL|macro|PIU_IRQ
mdefine_line|#define PIU_IRQ&t;&t;&t;SYSINT1_IRQ(5)
DECL|macro|AIU_IRQ
mdefine_line|#define AIU_IRQ&t;&t;&t;SYSINT1_IRQ(6)
DECL|macro|KIU_IRQ
mdefine_line|#define KIU_IRQ&t;&t;&t;SYSINT1_IRQ(7)
DECL|macro|GIUINT_CASCADE_IRQ
mdefine_line|#define GIUINT_CASCADE_IRQ&t;SYSINT1_IRQ(8)
DECL|macro|SIU_IRQ
mdefine_line|#define SIU_IRQ&t;&t;&t;SYSINT1_IRQ(9)
DECL|macro|BUSERR_IRQ
mdefine_line|#define BUSERR_IRQ&t;&t;SYSINT1_IRQ(10)
DECL|macro|SOFTINT_IRQ
mdefine_line|#define SOFTINT_IRQ&t;&t;SYSINT1_IRQ(11)
DECL|macro|CLKRUN_IRQ
mdefine_line|#define CLKRUN_IRQ&t;&t;SYSINT1_IRQ(12)
DECL|macro|DOZEPIU_IRQ
mdefine_line|#define DOZEPIU_IRQ&t;&t;SYSINT1_IRQ(13)
DECL|macro|SYSINT1_IRQ_LAST
mdefine_line|#define SYSINT1_IRQ_LAST&t;DOZEPIU_IRQ
multiline_comment|/* SYSINT2 Interrupt Numbers */
DECL|macro|SYSINT2_IRQ_BASE
mdefine_line|#define SYSINT2_IRQ_BASE&t;24
DECL|macro|SYSINT2_IRQ
mdefine_line|#define SYSINT2_IRQ(x)&t;&t;(SYSINT2_IRQ_BASE + (x))
DECL|macro|RTCLONG2_IRQ
mdefine_line|#define RTCLONG2_IRQ&t;&t;SYSINT2_IRQ(0)
DECL|macro|LED_IRQ
mdefine_line|#define LED_IRQ&t;&t;&t;SYSINT2_IRQ(1)
DECL|macro|HSP_IRQ
mdefine_line|#define HSP_IRQ&t;&t;&t;SYSINT2_IRQ(2)
DECL|macro|TCLOCK_IRQ
mdefine_line|#define TCLOCK_IRQ&t;&t;SYSINT2_IRQ(3)
DECL|macro|FIR_IRQ
mdefine_line|#define FIR_IRQ&t;&t;&t;SYSINT2_IRQ(4)
DECL|macro|CEU_IRQ
mdefine_line|#define CEU_IRQ&t;&t;&t;SYSINT2_IRQ(4)&t;/* same number as FIR_IRQ */
DECL|macro|DSIU_IRQ
mdefine_line|#define DSIU_IRQ&t;&t;SYSINT2_IRQ(5)
DECL|macro|PCI_IRQ
mdefine_line|#define PCI_IRQ&t;&t;&t;SYSINT2_IRQ(6)
DECL|macro|SCU_IRQ
mdefine_line|#define SCU_IRQ&t;&t;&t;SYSINT2_IRQ(7)
DECL|macro|CSI_IRQ
mdefine_line|#define CSI_IRQ&t;&t;&t;SYSINT2_IRQ(8)
DECL|macro|BCU_IRQ
mdefine_line|#define BCU_IRQ&t;&t;&t;SYSINT2_IRQ(9)
DECL|macro|ETHERNET_IRQ
mdefine_line|#define ETHERNET_IRQ&t;&t;SYSINT2_IRQ(10)
DECL|macro|SYSINT2_IRQ_LAST
mdefine_line|#define SYSINT2_IRQ_LAST&t;ETHERNET_IRQ
multiline_comment|/* GIU Interrupt Numbers */
DECL|macro|GIU_IRQ_BASE
mdefine_line|#define GIU_IRQ_BASE&t;&t;40
DECL|macro|GIU_IRQ
mdefine_line|#define GIU_IRQ(x)&t;&t;(GIU_IRQ_BASE + (x))&t;/* IRQ 40-71 */
DECL|macro|GIU_IRQ_LAST
mdefine_line|#define GIU_IRQ_LAST&t;&t;GIU_IRQ(31)
DECL|macro|GIU_IRQ_TO_PIN
mdefine_line|#define GIU_IRQ_TO_PIN(x)&t;((x) - GIU_IRQ_BASE)&t;/* Pin 0-31 */
r_extern
r_int
id|vr41xx_set_intassign
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_char
id|intassign
)paren
suffix:semicolon
r_extern
r_int
id|vr41xx_cascade_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
(paren
op_star
id|get_irq_number
)paren
(paren
r_int
id|irq
)paren
)paren
suffix:semicolon
DECL|macro|PIUINT_COMMAND
mdefine_line|#define PIUINT_COMMAND&t;&t;0x0040
DECL|macro|PIUINT_DATA
mdefine_line|#define PIUINT_DATA&t;&t;0x0020
DECL|macro|PIUINT_PAGE1
mdefine_line|#define PIUINT_PAGE1&t;&t;0x0010
DECL|macro|PIUINT_PAGE0
mdefine_line|#define PIUINT_PAGE0&t;&t;0x0008
DECL|macro|PIUINT_DATALOST
mdefine_line|#define PIUINT_DATALOST&t;&t;0x0004
DECL|macro|PIUINT_STATUSCHANGE
mdefine_line|#define PIUINT_STATUSCHANGE&t;0x0001
r_extern
r_void
id|vr41xx_enable_piuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_disable_piuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
DECL|macro|AIUINT_INPUT_DMAEND
mdefine_line|#define AIUINT_INPUT_DMAEND&t;0x0800
DECL|macro|AIUINT_INPUT_DMAHALT
mdefine_line|#define AIUINT_INPUT_DMAHALT&t;0x0400
DECL|macro|AIUINT_INPUT_DATALOST
mdefine_line|#define AIUINT_INPUT_DATALOST&t;0x0200
DECL|macro|AIUINT_INPUT_DATA
mdefine_line|#define AIUINT_INPUT_DATA&t;0x0100
DECL|macro|AIUINT_OUTPUT_DMAEND
mdefine_line|#define AIUINT_OUTPUT_DMAEND&t;0x0008
DECL|macro|AIUINT_OUTPUT_DMAHALT
mdefine_line|#define AIUINT_OUTPUT_DMAHALT&t;0x0004
DECL|macro|AIUINT_OUTPUT_NODATA
mdefine_line|#define AIUINT_OUTPUT_NODATA&t;0x0002
r_extern
r_void
id|vr41xx_enable_aiuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_disable_aiuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
DECL|macro|KIUINT_DATALOST
mdefine_line|#define KIUINT_DATALOST&t;&t;0x0004
DECL|macro|KIUINT_DATAREADY
mdefine_line|#define KIUINT_DATAREADY&t;0x0002
DECL|macro|KIUINT_SCAN
mdefine_line|#define KIUINT_SCAN&t;&t;0x0001
r_extern
r_void
id|vr41xx_enable_kiuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_disable_kiuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
DECL|macro|DSIUINT_CTS
mdefine_line|#define DSIUINT_CTS&t;&t;0x0800
DECL|macro|DSIUINT_RXERR
mdefine_line|#define DSIUINT_RXERR&t;&t;0x0400
DECL|macro|DSIUINT_RX
mdefine_line|#define DSIUINT_RX&t;&t;0x0200
DECL|macro|DSIUINT_TX
mdefine_line|#define DSIUINT_TX&t;&t;0x0100
DECL|macro|DSIUINT_ALL
mdefine_line|#define DSIUINT_ALL&t;&t;0x0f00
r_extern
r_void
id|vr41xx_enable_dsiuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_disable_dsiuint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
DECL|macro|FIRINT_UNIT
mdefine_line|#define FIRINT_UNIT&t;&t;0x0010
DECL|macro|FIRINT_RX_DMAEND
mdefine_line|#define FIRINT_RX_DMAEND&t;0x0008
DECL|macro|FIRINT_RX_DMAHALT
mdefine_line|#define FIRINT_RX_DMAHALT&t;0x0004
DECL|macro|FIRINT_TX_DMAEND
mdefine_line|#define FIRINT_TX_DMAEND&t;0x0002
DECL|macro|FIRINT_TX_DMAHALT
mdefine_line|#define FIRINT_TX_DMAHALT&t;0x0001
r_extern
r_void
id|vr41xx_enable_firint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_disable_firint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_enable_pciint
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_disable_pciint
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_enable_scuint
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_disable_scuint
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|CSIINT_TX_DMAEND
mdefine_line|#define CSIINT_TX_DMAEND&t;0x0040
DECL|macro|CSIINT_TX_DMAHALT
mdefine_line|#define CSIINT_TX_DMAHALT&t;0x0020
DECL|macro|CSIINT_TX_DATA
mdefine_line|#define CSIINT_TX_DATA&t;&t;0x0010
DECL|macro|CSIINT_TX_FIFOEMPTY
mdefine_line|#define CSIINT_TX_FIFOEMPTY&t;0x0008
DECL|macro|CSIINT_RX_DMAEND
mdefine_line|#define CSIINT_RX_DMAEND&t;0x0004
DECL|macro|CSIINT_RX_DMAHALT
mdefine_line|#define CSIINT_RX_DMAHALT&t;0x0002
DECL|macro|CSIINT_RX_FIFOEMPTY
mdefine_line|#define CSIINT_RX_FIFOEMPTY&t;0x0001
r_extern
r_void
id|vr41xx_enable_csiint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_disable_csiint
c_func
(paren
r_uint16
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_enable_bcuint
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_disable_bcuint
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Power Management Unit&n; */
multiline_comment|/*&n; * RTC&n; */
r_extern
r_void
id|vr41xx_set_rtclong1_cycle
c_func
(paren
r_uint32
id|cycles
)paren
suffix:semicolon
r_extern
r_uint32
id|vr41xx_read_rtclong1_counter
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_set_rtclong2_cycle
c_func
(paren
r_uint32
id|cycles
)paren
suffix:semicolon
r_extern
r_uint32
id|vr41xx_read_rtclong2_counter
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_set_tclock_cycle
c_func
(paren
r_uint32
id|cycles
)paren
suffix:semicolon
r_extern
r_uint32
id|vr41xx_read_tclock_counter
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * General-Purpose I/O Unit&n; */
r_enum
(brace
DECL|enumerator|TRIGGER_LEVEL
id|TRIGGER_LEVEL
comma
DECL|enumerator|TRIGGER_EDGE
id|TRIGGER_EDGE
comma
DECL|enumerator|TRIGGER_EDGE_FALLING
id|TRIGGER_EDGE_FALLING
comma
DECL|enumerator|TRIGGER_EDGE_RISING
id|TRIGGER_EDGE_RISING
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|SIGNAL_THROUGH
id|SIGNAL_THROUGH
comma
DECL|enumerator|SIGNAL_HOLD
id|SIGNAL_HOLD
)brace
suffix:semicolon
r_extern
r_void
id|vr41xx_set_irq_trigger
c_func
(paren
r_int
id|pin
comma
r_int
id|trigger
comma
r_int
id|hold
)paren
suffix:semicolon
r_enum
(brace
DECL|enumerator|LEVEL_LOW
id|LEVEL_LOW
comma
DECL|enumerator|LEVEL_HIGH
id|LEVEL_HIGH
)brace
suffix:semicolon
r_extern
r_void
id|vr41xx_set_irq_level
c_func
(paren
r_int
id|pin
comma
r_int
id|level
)paren
suffix:semicolon
r_enum
(brace
DECL|enumerator|PIO_INPUT
id|PIO_INPUT
comma
DECL|enumerator|PIO_OUTPUT
id|PIO_OUTPUT
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|DATA_LOW
id|DATA_LOW
comma
DECL|enumerator|DATA_HIGH
id|DATA_HIGH
)brace
suffix:semicolon
multiline_comment|/*&n; * Serial Interface Unit&n; */
r_extern
r_void
id|vr41xx_siu_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|vr41xx_serial_ports
suffix:semicolon
multiline_comment|/* SIU interfaces */
r_typedef
r_enum
(brace
DECL|enumerator|SIU_RS232C
id|SIU_RS232C
comma
DECL|enumerator|SIU_IRDA
id|SIU_IRDA
DECL|typedef|siu_interface_t
)brace
id|siu_interface_t
suffix:semicolon
multiline_comment|/* IrDA interfaces */
r_typedef
r_enum
(brace
DECL|enumerator|IRDA_NONE
id|IRDA_NONE
comma
DECL|enumerator|IRDA_SHARP
id|IRDA_SHARP
comma
DECL|enumerator|IRDA_TEMIC
id|IRDA_TEMIC
comma
DECL|enumerator|IRDA_HP
id|IRDA_HP
DECL|typedef|irda_module_t
)brace
id|irda_module_t
suffix:semicolon
r_extern
r_void
id|vr41xx_select_siu_interface
c_func
(paren
id|siu_interface_t
id|interface
comma
id|irda_module_t
id|module
)paren
suffix:semicolon
multiline_comment|/*&n; * Debug Serial Interface Unit&n; */
r_extern
r_void
id|vr41xx_dsiu_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * PCI Control Unit&n; */
DECL|macro|PCI_MASTER_ADDRESS_MASK
mdefine_line|#define PCI_MASTER_ADDRESS_MASK&t;0x7fffffffU
DECL|struct|pci_master_address_conversion
r_struct
id|pci_master_address_conversion
(brace
DECL|member|bus_base_address
r_uint32
id|bus_base_address
suffix:semicolon
DECL|member|address_mask
r_uint32
id|address_mask
suffix:semicolon
DECL|member|pci_base_address
r_uint32
id|pci_base_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_target_address_conversion
r_struct
id|pci_target_address_conversion
(brace
DECL|member|address_mask
r_uint32
id|address_mask
suffix:semicolon
DECL|member|bus_base_address
r_uint32
id|bus_base_address
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|CANNOT_LOCK_FROM_DEVICE
id|CANNOT_LOCK_FROM_DEVICE
comma
DECL|enumerator|CAN_LOCK_FROM_DEVICE
id|CAN_LOCK_FROM_DEVICE
comma
DECL|typedef|pci_exclusive_access_t
)brace
id|pci_exclusive_access_t
suffix:semicolon
DECL|struct|pci_mailbox_address
r_struct
id|pci_mailbox_address
(brace
DECL|member|base_address
r_uint32
id|base_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_target_address_window
r_struct
id|pci_target_address_window
(brace
DECL|member|base_address
r_uint32
id|base_address
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|PCI_ARBITRATION_MODE_FAIR
id|PCI_ARBITRATION_MODE_FAIR
comma
DECL|enumerator|PCI_ARBITRATION_MODE_ALTERNATE_0
id|PCI_ARBITRATION_MODE_ALTERNATE_0
comma
DECL|enumerator|PCI_ARBITRATION_MODE_ALTERNATE_B
id|PCI_ARBITRATION_MODE_ALTERNATE_B
comma
DECL|typedef|pci_arbiter_priority_control_t
)brace
id|pci_arbiter_priority_control_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|PCI_TAKE_AWAY_GNT_DISABLE
id|PCI_TAKE_AWAY_GNT_DISABLE
comma
DECL|enumerator|PCI_TAKE_AWAY_GNT_ENABLE
id|PCI_TAKE_AWAY_GNT_ENABLE
comma
DECL|typedef|pci_take_away_gnt_mode_t
)brace
id|pci_take_away_gnt_mode_t
suffix:semicolon
DECL|struct|pci_controller_unit_setup
r_struct
id|pci_controller_unit_setup
(brace
DECL|member|master_memory1
r_struct
id|pci_master_address_conversion
op_star
id|master_memory1
suffix:semicolon
DECL|member|master_memory2
r_struct
id|pci_master_address_conversion
op_star
id|master_memory2
suffix:semicolon
DECL|member|target_memory1
r_struct
id|pci_target_address_conversion
op_star
id|target_memory1
suffix:semicolon
DECL|member|target_memory2
r_struct
id|pci_target_address_conversion
op_star
id|target_memory2
suffix:semicolon
DECL|member|master_io
r_struct
id|pci_master_address_conversion
op_star
id|master_io
suffix:semicolon
DECL|member|exclusive_access
id|pci_exclusive_access_t
id|exclusive_access
suffix:semicolon
DECL|member|pci_clock_max
r_uint32
id|pci_clock_max
suffix:semicolon
DECL|member|wait_time_limit_from_irdy_to_trdy
r_uint8
id|wait_time_limit_from_irdy_to_trdy
suffix:semicolon
multiline_comment|/* Only VR4122 is supported */
DECL|member|mailbox
r_struct
id|pci_mailbox_address
op_star
id|mailbox
suffix:semicolon
DECL|member|target_window1
r_struct
id|pci_target_address_window
op_star
id|target_window1
suffix:semicolon
DECL|member|target_window2
r_struct
id|pci_target_address_window
op_star
id|target_window2
suffix:semicolon
DECL|member|master_latency_timer
r_uint8
id|master_latency_timer
suffix:semicolon
DECL|member|retry_limit
r_uint8
id|retry_limit
suffix:semicolon
DECL|member|arbiter_priority_control
id|pci_arbiter_priority_control_t
id|arbiter_priority_control
suffix:semicolon
DECL|member|take_away_gnt_mode
id|pci_take_away_gnt_mode_t
id|take_away_gnt_mode
suffix:semicolon
DECL|member|mem_resource
r_struct
id|resource
op_star
id|mem_resource
suffix:semicolon
DECL|member|io_resource
r_struct
id|resource
op_star
id|io_resource
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|vr41xx_pciu_setup
c_func
(paren
r_struct
id|pci_controller_unit_setup
op_star
id|setup
)paren
suffix:semicolon
macro_line|#endif /* __NEC_VR41XX_H */
eof
