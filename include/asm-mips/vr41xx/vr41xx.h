multiline_comment|/*&n; * include/asm-mips/vr41xx/vr41xx.h&n; *&n; * Include file for NEC VR4100 series.&n; *&n; * Copyright (C) 1999 Michael Klar&n; * Copyright (C) 2001, 2002 Paul Mundt&n; * Copyright (C) 2002 MontaVista Software, Inc.&n; * Copyright (C) 2002 TimeSys Corp.&n; * Copyright (C) 2003 Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; */
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
r_void
id|vr41xx_bcu_init
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
r_extern
r_void
id|vr41xx_cmu_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_clock_supply
c_func
(paren
r_int
r_int
id|clock
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_clock_mask
c_func
(paren
r_int
r_int
id|clock
)paren
suffix:semicolon
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
)brace
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
r_void
(paren
op_star
id|board_irq_init
)paren
(paren
r_void
)paren
suffix:semicolon
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
multiline_comment|/*&n; * Power Management Unit&n; */
r_extern
r_void
id|vr41xx_pmu_init
c_func
(paren
r_void
)paren
suffix:semicolon
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
r_int
id|interface
comma
r_int
id|module
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_siu_ifselect
c_func
(paren
r_int
id|interface
comma
r_int
id|module
)paren
suffix:semicolon
r_extern
r_int
id|vr41xx_serial_ports
suffix:semicolon
multiline_comment|/* SIU interfaces */
r_enum
(brace
DECL|enumerator|SIU_RS232C
id|SIU_RS232C
comma
DECL|enumerator|SIU_IRDA
id|SIU_IRDA
)brace
suffix:semicolon
multiline_comment|/* IrDA interfaces */
r_enum
(brace
DECL|enumerator|IRDA_SHARP
id|IRDA_SHARP
op_assign
l_int|1
comma
DECL|enumerator|IRDA_TEMIC
id|IRDA_TEMIC
comma
DECL|enumerator|IRDA_HP
id|IRDA_HP
)brace
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
DECL|struct|vr41xx_pci_address_space
r_struct
id|vr41xx_pci_address_space
(brace
DECL|member|internal_base
id|u32
id|internal_base
suffix:semicolon
DECL|member|address_mask
id|u32
id|address_mask
suffix:semicolon
DECL|member|pci_base
id|u32
id|pci_base
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vr41xx_pci_address_map
r_struct
id|vr41xx_pci_address_map
(brace
DECL|member|mem1
r_struct
id|vr41xx_pci_address_space
op_star
id|mem1
suffix:semicolon
DECL|member|mem2
r_struct
id|vr41xx_pci_address_space
op_star
id|mem2
suffix:semicolon
DECL|member|io
r_struct
id|vr41xx_pci_address_space
op_star
id|io
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|vr41xx_pciu_init
c_func
(paren
r_struct
id|vr41xx_pci_address_map
op_star
id|map
)paren
suffix:semicolon
multiline_comment|/*&n; * MISC&n; */
r_extern
r_void
id|vr41xx_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vr41xx_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
suffix:semicolon
macro_line|#endif /* __NEC_VR41XX_H */
eof
