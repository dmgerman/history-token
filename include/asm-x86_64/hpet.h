macro_line|#ifndef _ASM_X8664_HPET_H
DECL|macro|_ASM_X8664_HPET_H
mdefine_line|#define _ASM_X8664_HPET_H 1
multiline_comment|/*&n; * Documentation on HPET can be found at:&n; *      http://www.intel.com/ial/home/sp/pcmmspec.htm&n; *      ftp://download.intel.com/ial/home/sp/mmts098.pdf&n; */
DECL|macro|HPET_MMAP_SIZE
mdefine_line|#define HPET_MMAP_SIZE&t;1024
DECL|macro|HPET_ID
mdefine_line|#define HPET_ID&t;&t;0x000
DECL|macro|HPET_PERIOD
mdefine_line|#define HPET_PERIOD&t;0x004
DECL|macro|HPET_CFG
mdefine_line|#define HPET_CFG&t;0x010
DECL|macro|HPET_STATUS
mdefine_line|#define HPET_STATUS&t;0x020
DECL|macro|HPET_COUNTER
mdefine_line|#define HPET_COUNTER&t;0x0f0
DECL|macro|HPET_T0_CFG
mdefine_line|#define HPET_T0_CFG&t;0x100
DECL|macro|HPET_T0_CMP
mdefine_line|#define HPET_T0_CMP&t;0x108
DECL|macro|HPET_T0_ROUTE
mdefine_line|#define HPET_T0_ROUTE&t;0x110
DECL|macro|HPET_T1_CFG
mdefine_line|#define HPET_T1_CFG&t;0x120
DECL|macro|HPET_T1_CMP
mdefine_line|#define HPET_T1_CMP&t;0x128
DECL|macro|HPET_T1_ROUTE
mdefine_line|#define HPET_T1_ROUTE&t;0x130
DECL|macro|HPET_T2_CFG
mdefine_line|#define HPET_T2_CFG&t;0x140
DECL|macro|HPET_T2_CMP
mdefine_line|#define HPET_T2_CMP&t;0x148
DECL|macro|HPET_T2_ROUTE
mdefine_line|#define HPET_T2_ROUTE&t;0x150
DECL|macro|HPET_ID_VENDOR
mdefine_line|#define HPET_ID_VENDOR&t;0xffff0000
DECL|macro|HPET_ID_LEGSUP
mdefine_line|#define HPET_ID_LEGSUP&t;0x00008000
DECL|macro|HPET_ID_NUMBER
mdefine_line|#define HPET_ID_NUMBER&t;0x00001f00
DECL|macro|HPET_ID_REV
mdefine_line|#define HPET_ID_REV&t;0x000000ff
DECL|macro|HPET_ID_NUMBER_SHIFT
mdefine_line|#define&t;HPET_ID_NUMBER_SHIFT&t;8
DECL|macro|HPET_ID_VENDOR_SHIFT
mdefine_line|#define HPET_ID_VENDOR_SHIFT&t;16
DECL|macro|HPET_ID_VENDOR_8086
mdefine_line|#define HPET_ID_VENDOR_8086&t;0x8086
DECL|macro|HPET_CFG_ENABLE
mdefine_line|#define HPET_CFG_ENABLE&t;0x001
DECL|macro|HPET_CFG_LEGACY
mdefine_line|#define HPET_CFG_LEGACY&t;0x002
DECL|macro|HPET_LEGACY_8254
mdefine_line|#define&t;HPET_LEGACY_8254&t;2
DECL|macro|HPET_LEGACY_RTC
mdefine_line|#define&t;HPET_LEGACY_RTC&t;&t;8
DECL|macro|HPET_TN_ENABLE
mdefine_line|#define HPET_TN_ENABLE&t;&t;0x004
DECL|macro|HPET_TN_PERIODIC
mdefine_line|#define HPET_TN_PERIODIC&t;0x008
DECL|macro|HPET_TN_PERIODIC_CAP
mdefine_line|#define HPET_TN_PERIODIC_CAP&t;0x010
DECL|macro|HPET_TN_SETVAL
mdefine_line|#define HPET_TN_SETVAL&t;&t;0x040
DECL|macro|HPET_TN_32BIT
mdefine_line|#define HPET_TN_32BIT&t;&t;0x100
r_extern
r_int
id|is_hpet_enabled
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hpet_rtc_timer_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HPET_EMULATE_RTC
r_extern
r_int
id|hpet_mask_rtc_irq_bit
c_func
(paren
r_int
r_int
id|bit_mask
)paren
suffix:semicolon
r_extern
r_int
id|hpet_set_rtc_irq_bit
c_func
(paren
r_int
r_int
id|bit_mask
)paren
suffix:semicolon
r_extern
r_int
id|hpet_set_alarm_time
c_func
(paren
r_int
r_char
id|hrs
comma
r_int
r_char
id|min
comma
r_int
r_char
id|sec
)paren
suffix:semicolon
r_extern
r_int
id|hpet_set_periodic_freq
c_func
(paren
r_int
r_int
id|freq
)paren
suffix:semicolon
r_extern
r_int
id|hpet_rtc_dropped_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hpet_rtc_timer_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|oem_force_hpet_timer
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_HPET_EMULATE_RTC */
macro_line|#endif
eof
