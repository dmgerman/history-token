multiline_comment|/*&n; * Macros for vr4181 IRQ numbers.&n; *&n; * Copyright (C) 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
multiline_comment|/*&n; * Strategy:&n; *&n; * Vr4181 has conceptually three levels of interrupt controllers:&n; *  1. the CPU itself with 8 intr level.&n; *  2. system interrupt controller, cascaded from int0 pin in CPU, 32 intrs&n; *  3. GPIO interrupts : forwarding external interrupts to sys intr controller&n; */
multiline_comment|/* decide the irq block assignment */
DECL|macro|VR4181_NUM_CPU_IRQ
mdefine_line|#define&t;VR4181_NUM_CPU_IRQ&t;8
DECL|macro|VR4181_NUM_SYS_IRQ
mdefine_line|#define&t;VR4181_NUM_SYS_IRQ&t;32
DECL|macro|VR4181_NUM_GPIO_IRQ
mdefine_line|#define&t;VR4181_NUM_GPIO_IRQ&t;16
DECL|macro|VR4181_IRQ_BASE
mdefine_line|#define&t;VR4181_IRQ_BASE&t;&t;0
DECL|macro|VR4181_CPU_IRQ_BASE
mdefine_line|#define&t;VR4181_CPU_IRQ_BASE&t;VR4181_IRQ_BASE
DECL|macro|VR4181_SYS_IRQ_BASE
mdefine_line|#define&t;VR4181_SYS_IRQ_BASE&t;(VR4181_CPU_IRQ_BASE + VR4181_NUM_CPU_IRQ)
DECL|macro|VR4181_GPIO_IRQ_BASE
mdefine_line|#define&t;VR4181_GPIO_IRQ_BASE&t;(VR4181_SYS_IRQ_BASE + VR4181_NUM_SYS_IRQ)
multiline_comment|/* CPU interrupts */
multiline_comment|/*&n;   IP0 - Software interrupt&n;   IP1 - Software interrupt&n;   IP2 - All but battery, high speed modem, and real time clock&n;   IP3 - RTC Long1 (system timer)&n;   IP4 - RTC Long2&n;   IP5 - High Speed Modem (unused on VR4181)&n;   IP6 - Unused&n;   IP7 - Timer interrupt from CPO_COMPARE&n;*/
DECL|macro|VR4181_IRQ_SW1
mdefine_line|#define VR4181_IRQ_SW1       (VR4181_CPU_IRQ_BASE + 0)
DECL|macro|VR4181_IRQ_SW2
mdefine_line|#define VR4181_IRQ_SW2       (VR4181_CPU_IRQ_BASE + 1)
DECL|macro|VR4181_IRQ_INT0
mdefine_line|#define VR4181_IRQ_INT0      (VR4181_CPU_IRQ_BASE + 2)
DECL|macro|VR4181_IRQ_INT1
mdefine_line|#define VR4181_IRQ_INT1      (VR4181_CPU_IRQ_BASE + 3)
DECL|macro|VR4181_IRQ_INT2
mdefine_line|#define VR4181_IRQ_INT2      (VR4181_CPU_IRQ_BASE + 4)
DECL|macro|VR4181_IRQ_INT3
mdefine_line|#define VR4181_IRQ_INT3      (VR4181_CPU_IRQ_BASE + 5)
DECL|macro|VR4181_IRQ_INT4
mdefine_line|#define VR4181_IRQ_INT4      (VR4181_CPU_IRQ_BASE + 6)
DECL|macro|VR4181_IRQ_TIMER
mdefine_line|#define VR4181_IRQ_TIMER     (VR4181_CPU_IRQ_BASE + 7)
multiline_comment|/* Cascaded from VR4181_IRQ_INT0 (ICU mapped interrupts) */
multiline_comment|/*&n;   IP2 - same as VR4181_IRQ_INT1&n;   IP8 - This is a cascade to GPIO IRQ&squot;s. Do not use.&n;   IP16 - same as VR4181_IRQ_INT2&n;   IP18 - CompactFlash&n;*/
DECL|macro|VR4181_IRQ_BATTERY
mdefine_line|#define VR4181_IRQ_BATTERY   (VR4181_SYS_IRQ_BASE + 0)
DECL|macro|VR4181_IRQ_POWER
mdefine_line|#define VR4181_IRQ_POWER     (VR4181_SYS_IRQ_BASE + 1)
DECL|macro|VR4181_IRQ_RTCL1
mdefine_line|#define VR4181_IRQ_RTCL1     (VR4181_SYS_IRQ_BASE + 2)
DECL|macro|VR4181_IRQ_ETIMER
mdefine_line|#define VR4181_IRQ_ETIMER    (VR4181_SYS_IRQ_BASE + 3)
DECL|macro|VR4181_IRQ_RFU12
mdefine_line|#define VR4181_IRQ_RFU12     (VR4181_SYS_IRQ_BASE + 4)
DECL|macro|VR4181_IRQ_PIU
mdefine_line|#define VR4181_IRQ_PIU       (VR4181_SYS_IRQ_BASE + 5)
DECL|macro|VR4181_IRQ_AIU
mdefine_line|#define VR4181_IRQ_AIU       (VR4181_SYS_IRQ_BASE + 6)
DECL|macro|VR4181_IRQ_KIU
mdefine_line|#define VR4181_IRQ_KIU       (VR4181_SYS_IRQ_BASE + 7)
DECL|macro|VR4181_IRQ_GIU
mdefine_line|#define VR4181_IRQ_GIU       (VR4181_SYS_IRQ_BASE + 8)
DECL|macro|VR4181_IRQ_SIU
mdefine_line|#define VR4181_IRQ_SIU       (VR4181_SYS_IRQ_BASE + 9)
DECL|macro|VR4181_IRQ_RFU18
mdefine_line|#define VR4181_IRQ_RFU18     (VR4181_SYS_IRQ_BASE + 10)
DECL|macro|VR4181_IRQ_SOFT
mdefine_line|#define VR4181_IRQ_SOFT      (VR4181_SYS_IRQ_BASE + 11)
DECL|macro|VR4181_IRQ_RFU20
mdefine_line|#define VR4181_IRQ_RFU20     (VR4181_SYS_IRQ_BASE + 12)
DECL|macro|VR4181_IRQ_DOZEPIU
mdefine_line|#define VR4181_IRQ_DOZEPIU   (VR4181_SYS_IRQ_BASE + 13)
DECL|macro|VR4181_IRQ_RFU22
mdefine_line|#define VR4181_IRQ_RFU22     (VR4181_SYS_IRQ_BASE + 14)
DECL|macro|VR4181_IRQ_RFU23
mdefine_line|#define VR4181_IRQ_RFU23     (VR4181_SYS_IRQ_BASE + 15)
DECL|macro|VR4181_IRQ_RTCL2
mdefine_line|#define VR4181_IRQ_RTCL2     (VR4181_SYS_IRQ_BASE + 16)
DECL|macro|VR4181_IRQ_LED
mdefine_line|#define VR4181_IRQ_LED       (VR4181_SYS_IRQ_BASE + 17)
DECL|macro|VR4181_IRQ_ECU
mdefine_line|#define VR4181_IRQ_ECU       (VR4181_SYS_IRQ_BASE + 18)
DECL|macro|VR4181_IRQ_CSU
mdefine_line|#define VR4181_IRQ_CSU       (VR4181_SYS_IRQ_BASE + 19)
DECL|macro|VR4181_IRQ_USB
mdefine_line|#define VR4181_IRQ_USB       (VR4181_SYS_IRQ_BASE + 20)
DECL|macro|VR4181_IRQ_DMA
mdefine_line|#define VR4181_IRQ_DMA       (VR4181_SYS_IRQ_BASE + 21)
DECL|macro|VR4181_IRQ_LCD
mdefine_line|#define VR4181_IRQ_LCD       (VR4181_SYS_IRQ_BASE + 22)
DECL|macro|VR4181_IRQ_RFU31
mdefine_line|#define VR4181_IRQ_RFU31     (VR4181_SYS_IRQ_BASE + 23)
DECL|macro|VR4181_IRQ_RFU32
mdefine_line|#define VR4181_IRQ_RFU32     (VR4181_SYS_IRQ_BASE + 24)
DECL|macro|VR4181_IRQ_RFU33
mdefine_line|#define VR4181_IRQ_RFU33     (VR4181_SYS_IRQ_BASE + 25)
DECL|macro|VR4181_IRQ_RFU34
mdefine_line|#define VR4181_IRQ_RFU34     (VR4181_SYS_IRQ_BASE + 26)
DECL|macro|VR4181_IRQ_RFU35
mdefine_line|#define VR4181_IRQ_RFU35     (VR4181_SYS_IRQ_BASE + 27)
DECL|macro|VR4181_IRQ_RFU36
mdefine_line|#define VR4181_IRQ_RFU36     (VR4181_SYS_IRQ_BASE + 28)
DECL|macro|VR4181_IRQ_RFU37
mdefine_line|#define VR4181_IRQ_RFU37     (VR4181_SYS_IRQ_BASE + 29)
DECL|macro|VR4181_IRQ_RFU38
mdefine_line|#define VR4181_IRQ_RFU38     (VR4181_SYS_IRQ_BASE + 30)
DECL|macro|VR4181_IRQ_RFU39
mdefine_line|#define VR4181_IRQ_RFU39     (VR4181_SYS_IRQ_BASE + 31)
multiline_comment|/* Cascaded from VR4181_IRQ_GIU */
DECL|macro|VR4181_IRQ_GPIO0
mdefine_line|#define VR4181_IRQ_GPIO0     (VR4181_GPIO_IRQ_BASE + 0)
DECL|macro|VR4181_IRQ_GPIO1
mdefine_line|#define VR4181_IRQ_GPIO1     (VR4181_GPIO_IRQ_BASE + 1)
DECL|macro|VR4181_IRQ_GPIO2
mdefine_line|#define VR4181_IRQ_GPIO2     (VR4181_GPIO_IRQ_BASE + 2)
DECL|macro|VR4181_IRQ_GPIO3
mdefine_line|#define VR4181_IRQ_GPIO3     (VR4181_GPIO_IRQ_BASE + 3)
DECL|macro|VR4181_IRQ_GPIO4
mdefine_line|#define VR4181_IRQ_GPIO4     (VR4181_GPIO_IRQ_BASE + 4)
DECL|macro|VR4181_IRQ_GPIO5
mdefine_line|#define VR4181_IRQ_GPIO5     (VR4181_GPIO_IRQ_BASE + 5)
DECL|macro|VR4181_IRQ_GPIO6
mdefine_line|#define VR4181_IRQ_GPIO6     (VR4181_GPIO_IRQ_BASE + 6)
DECL|macro|VR4181_IRQ_GPIO7
mdefine_line|#define VR4181_IRQ_GPIO7     (VR4181_GPIO_IRQ_BASE + 7)
DECL|macro|VR4181_IRQ_GPIO8
mdefine_line|#define VR4181_IRQ_GPIO8     (VR4181_GPIO_IRQ_BASE + 8)
DECL|macro|VR4181_IRQ_GPIO9
mdefine_line|#define VR4181_IRQ_GPIO9     (VR4181_GPIO_IRQ_BASE + 9)
DECL|macro|VR4181_IRQ_GPIO10
mdefine_line|#define VR4181_IRQ_GPIO10    (VR4181_GPIO_IRQ_BASE + 10)
DECL|macro|VR4181_IRQ_GPIO11
mdefine_line|#define VR4181_IRQ_GPIO11    (VR4181_GPIO_IRQ_BASE + 11)
DECL|macro|VR4181_IRQ_GPIO12
mdefine_line|#define VR4181_IRQ_GPIO12    (VR4181_GPIO_IRQ_BASE + 12)
DECL|macro|VR4181_IRQ_GPIO13
mdefine_line|#define VR4181_IRQ_GPIO13    (VR4181_GPIO_IRQ_BASE + 13)
DECL|macro|VR4181_IRQ_GPIO14
mdefine_line|#define VR4181_IRQ_GPIO14    (VR4181_GPIO_IRQ_BASE + 14)
DECL|macro|VR4181_IRQ_GPIO15
mdefine_line|#define VR4181_IRQ_GPIO15    (VR4181_GPIO_IRQ_BASE + 15)
singleline_comment|// Alternative to above GPIO IRQ defines
DECL|macro|VR4181_IRQ_GPIO
mdefine_line|#define VR4181_IRQ_GPIO(pin) ((VR4181_IRQ_GPIO0) + (pin))
DECL|macro|VR4181_IRQ_MAX
mdefine_line|#define VR4181_IRQ_MAX       (VR4181_IRQ_BASE + VR4181_NUM_CPU_IRQ + &bslash;&n;                              VR4181_NUM_SYS_IRQ + VR4181_NUM_GPIO_IRQ)
eof
