multiline_comment|/*&n; * Definitions for talking to the PMU.  The PMU is a microcontroller&n; * which controls battery charging and system power on PowerBook 3400&n; * and 2400 models as well as the RTC and various other things.&n; *&n; * Copyright (C) 1998 Paul Mackerras.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|PMU_DRIVER_VERSION
mdefine_line|#define PMU_DRIVER_VERSION&t;2
multiline_comment|/*&n; * PMU commands&n; */
DECL|macro|PMU_POWER_CTRL0
mdefine_line|#define PMU_POWER_CTRL0&t;&t;0x10&t;/* control power of some devices */
DECL|macro|PMU_POWER_CTRL
mdefine_line|#define PMU_POWER_CTRL&t;&t;0x11&t;/* control power of some devices */
DECL|macro|PMU_ADB_CMD
mdefine_line|#define PMU_ADB_CMD&t;&t;0x20&t;/* send ADB packet */
DECL|macro|PMU_ADB_POLL_OFF
mdefine_line|#define PMU_ADB_POLL_OFF&t;0x21&t;/* disable ADB auto-poll */
DECL|macro|PMU_WRITE_NVRAM
mdefine_line|#define PMU_WRITE_NVRAM&t;&t;0x33&t;/* write non-volatile RAM */
DECL|macro|PMU_READ_NVRAM
mdefine_line|#define PMU_READ_NVRAM&t;&t;0x3b&t;/* read non-volatile RAM */
DECL|macro|PMU_SET_RTC
mdefine_line|#define PMU_SET_RTC&t;&t;0x30&t;/* set real-time clock */
DECL|macro|PMU_READ_RTC
mdefine_line|#define PMU_READ_RTC&t;&t;0x38&t;/* read real-time clock */
DECL|macro|PMU_SET_VOLBUTTON
mdefine_line|#define PMU_SET_VOLBUTTON&t;0x40&t;/* set volume up/down position */
DECL|macro|PMU_BACKLIGHT_BRIGHT
mdefine_line|#define PMU_BACKLIGHT_BRIGHT&t;0x41&t;/* set backlight brightness */
DECL|macro|PMU_GET_VOLBUTTON
mdefine_line|#define PMU_GET_VOLBUTTON&t;0x48&t;/* get volume up/down position */
DECL|macro|PMU_PCEJECT
mdefine_line|#define PMU_PCEJECT&t;&t;0x4c&t;/* eject PC-card from slot */
DECL|macro|PMU_BATTERY_STATE
mdefine_line|#define PMU_BATTERY_STATE&t;0x6b&t;/* report battery state etc. */
DECL|macro|PMU_SMART_BATTERY_STATE
mdefine_line|#define PMU_SMART_BATTERY_STATE&t;0x6f&t;/* report battery state (new way) */
DECL|macro|PMU_SET_INTR_MASK
mdefine_line|#define PMU_SET_INTR_MASK&t;0x70&t;/* set PMU interrupt mask */
DECL|macro|PMU_INT_ACK
mdefine_line|#define PMU_INT_ACK&t;&t;0x78&t;/* read interrupt bits */
DECL|macro|PMU_SHUTDOWN
mdefine_line|#define PMU_SHUTDOWN&t;&t;0x7e&t;/* turn power off */
DECL|macro|PMU_SLEEP
mdefine_line|#define PMU_SLEEP&t;&t;0x7f&t;/* put CPU to sleep */
DECL|macro|PMU_POWER_EVENTS
mdefine_line|#define PMU_POWER_EVENTS&t;0x8f&t;/* Send power-event commands to PMU */
DECL|macro|PMU_RESET
mdefine_line|#define PMU_RESET&t;&t;0xd0&t;/* reset CPU */
DECL|macro|PMU_GET_BRIGHTBUTTON
mdefine_line|#define PMU_GET_BRIGHTBUTTON&t;0xd9&t;/* report brightness up/down pos */
DECL|macro|PMU_GET_COVER
mdefine_line|#define PMU_GET_COVER&t;&t;0xdc&t;/* report cover open/closed */
DECL|macro|PMU_SYSTEM_READY
mdefine_line|#define PMU_SYSTEM_READY&t;0xdf&t;/* tell PMU we are awake */
DECL|macro|PMU_GET_VERSION
mdefine_line|#define PMU_GET_VERSION&t;&t;0xea&t;/* read the PMU version */
multiline_comment|/* Bits to use with the PMU_POWER_CTRL0 command */
DECL|macro|PMU_POW0_ON
mdefine_line|#define PMU_POW0_ON&t;&t;0x80&t;/* OR this to power ON the device */
DECL|macro|PMU_POW0_OFF
mdefine_line|#define PMU_POW0_OFF&t;&t;0x00&t;/* leave bit 7 to 0 to power it OFF */
DECL|macro|PMU_POW0_HARD_DRIVE
mdefine_line|#define PMU_POW0_HARD_DRIVE&t;0x04&t;/* Hard drive power (on wallstreet/lombard ?) */
multiline_comment|/* Bits to use with the PMU_POWER_CTRL command */
DECL|macro|PMU_POW_ON
mdefine_line|#define PMU_POW_ON&t;&t;0x80&t;/* OR this to power ON the device */
DECL|macro|PMU_POW_OFF
mdefine_line|#define PMU_POW_OFF&t;&t;0x00&t;/* leave bit 7 to 0 to power it OFF */
DECL|macro|PMU_POW_BACKLIGHT
mdefine_line|#define PMU_POW_BACKLIGHT&t;0x01&t;/* backlight power */
DECL|macro|PMU_POW_CHARGER
mdefine_line|#define PMU_POW_CHARGER&t;&t;0x02&t;/* battery charger power */
DECL|macro|PMU_POW_IRLED
mdefine_line|#define PMU_POW_IRLED&t;&t;0x04&t;/* IR led power (on wallstreet) */
DECL|macro|PMU_POW_MEDIABAY
mdefine_line|#define PMU_POW_MEDIABAY&t;0x08&t;/* media bay power (wallstreet/lombard ?) */
multiline_comment|/* Bits in PMU interrupt and interrupt mask bytes */
DECL|macro|PMU_INT_PCEJECT
mdefine_line|#define PMU_INT_PCEJECT&t;&t;0x04&t;/* PC-card eject buttons */
DECL|macro|PMU_INT_SNDBRT
mdefine_line|#define PMU_INT_SNDBRT&t;&t;0x08&t;/* sound/brightness up/down buttons */
DECL|macro|PMU_INT_ADB
mdefine_line|#define PMU_INT_ADB&t;&t;0x10&t;/* ADB autopoll or reply data */
DECL|macro|PMU_INT_BATTERY
mdefine_line|#define PMU_INT_BATTERY&t;&t;0x20&t;/* Battery state change */
DECL|macro|PMU_INT_ENVIRONMENT
mdefine_line|#define PMU_INT_ENVIRONMENT&t;0x40&t;/* Environment interrupts */
DECL|macro|PMU_INT_TICK
mdefine_line|#define PMU_INT_TICK&t;&t;0x80&t;/* 1-second tick interrupt */
multiline_comment|/* Other bits in PMU interrupt valid when PMU_INT_ADB is set */
DECL|macro|PMU_INT_ADB_AUTO
mdefine_line|#define PMU_INT_ADB_AUTO&t;0x04&t;/* ADB autopoll, when PMU_INT_ADB */
DECL|macro|PMU_INT_WAITING_CHARGER
mdefine_line|#define PMU_INT_WAITING_CHARGER&t;0x01&t;/* ??? */
DECL|macro|PMU_INT_AUTO_SRQ_POLL
mdefine_line|#define PMU_INT_AUTO_SRQ_POLL&t;0x02&t;/* ??? */
multiline_comment|/* Bits in the environement message (either obtained via PMU_GET_COVER,&n; * or via PMU_INT_ENVIRONMENT on core99 */
DECL|macro|PMU_ENV_LID_CLOSED
mdefine_line|#define PMU_ENV_LID_CLOSED&t;0x01&t;/* The lid is closed */
multiline_comment|/* Kind of PMU (model) */
r_enum
(brace
DECL|enumerator|PMU_UNKNOWN
id|PMU_UNKNOWN
comma
DECL|enumerator|PMU_OHARE_BASED
id|PMU_OHARE_BASED
comma
multiline_comment|/* 2400, 3400, 3500 (old G3 powerbook) */
DECL|enumerator|PMU_HEATHROW_BASED
id|PMU_HEATHROW_BASED
comma
multiline_comment|/* PowerBook G3 series */
DECL|enumerator|PMU_PADDINGTON_BASED
id|PMU_PADDINGTON_BASED
comma
multiline_comment|/* 1999 PowerBook G3 */
DECL|enumerator|PMU_KEYLARGO_BASED
id|PMU_KEYLARGO_BASED
comma
multiline_comment|/* Core99 motherboard (PMU99) */
)brace
suffix:semicolon
multiline_comment|/* PMU PMU_POWER_EVENTS commands */
r_enum
(brace
DECL|enumerator|PMU_PWR_GET_POWERUP_EVENTS
id|PMU_PWR_GET_POWERUP_EVENTS
op_assign
l_int|0x00
comma
DECL|enumerator|PMU_PWR_SET_POWERUP_EVENTS
id|PMU_PWR_SET_POWERUP_EVENTS
op_assign
l_int|0x01
comma
DECL|enumerator|PMU_PWR_CLR_POWERUP_EVENTS
id|PMU_PWR_CLR_POWERUP_EVENTS
op_assign
l_int|0x02
comma
DECL|enumerator|PMU_PWR_GET_WAKEUP_EVENTS
id|PMU_PWR_GET_WAKEUP_EVENTS
op_assign
l_int|0x03
comma
DECL|enumerator|PMU_PWR_SET_WAKEUP_EVENTS
id|PMU_PWR_SET_WAKEUP_EVENTS
op_assign
l_int|0x04
comma
DECL|enumerator|PMU_PWR_CLR_WAKEUP_EVENTS
id|PMU_PWR_CLR_WAKEUP_EVENTS
op_assign
l_int|0x05
comma
)brace
suffix:semicolon
multiline_comment|/* Power events wakeup bits */
r_enum
(brace
DECL|enumerator|PMU_PWR_WAKEUP_KEY
id|PMU_PWR_WAKEUP_KEY
op_assign
l_int|0x01
comma
multiline_comment|/* Wake on key press */
DECL|enumerator|PMU_PWR_WAKEUP_AC_INSERT
id|PMU_PWR_WAKEUP_AC_INSERT
op_assign
l_int|0x02
comma
multiline_comment|/* Wake on AC adapter plug */
DECL|enumerator|PMU_PWR_WAKEUP_AC_CHANGE
id|PMU_PWR_WAKEUP_AC_CHANGE
op_assign
l_int|0x04
comma
DECL|enumerator|PMU_PWR_WAKEUP_LID_OPEN
id|PMU_PWR_WAKEUP_LID_OPEN
op_assign
l_int|0x08
comma
DECL|enumerator|PMU_PWR_WAKEUP_RING
id|PMU_PWR_WAKEUP_RING
op_assign
l_int|0x10
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Ioctl commands for the /dev/pmu device&n; */
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* no param */
DECL|macro|PMU_IOC_SLEEP
mdefine_line|#define PMU_IOC_SLEEP&t;&t;_IO(&squot;B&squot;, 0)
multiline_comment|/* out param: u32*&t;backlight value: 0 to 15 */
DECL|macro|PMU_IOC_GET_BACKLIGHT
mdefine_line|#define PMU_IOC_GET_BACKLIGHT&t;_IOR(&squot;B&squot;, 1, sizeof(__u32*))
multiline_comment|/* in param: u32&t;backlight value: 0 to 15 */
DECL|macro|PMU_IOC_SET_BACKLIGHT
mdefine_line|#define PMU_IOC_SET_BACKLIGHT&t;_IOW(&squot;B&squot;, 2, sizeof(__u32))
multiline_comment|/* out param: u32*&t;PMU model */
DECL|macro|PMU_IOC_GET_MODEL
mdefine_line|#define PMU_IOC_GET_MODEL&t;_IOR(&squot;B&squot;, 3, sizeof(__u32*))
multiline_comment|/* out param: u32*&t;has_adb: 0 or 1 */
DECL|macro|PMU_IOC_HAS_ADB
mdefine_line|#define PMU_IOC_HAS_ADB&t;&t;_IOR(&squot;B&squot;, 4, sizeof(__u32*)) 
multiline_comment|/* out param: u32*&t;can_sleep: 0 or 1 */
DECL|macro|PMU_IOC_CAN_SLEEP
mdefine_line|#define PMU_IOC_CAN_SLEEP&t;_IOR(&squot;B&squot;, 5, sizeof(__u32*)) 
multiline_comment|/* no param */
DECL|macro|PMU_IOC_GRAB_BACKLIGHT
mdefine_line|#define PMU_IOC_GRAB_BACKLIGHT&t;_IOR(&squot;B&squot;, 6, 0) 
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|find_via_pmu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pmu_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|adb_request
op_star
)paren
comma
r_int
id|nbytes
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|pmu_poll
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* For use before switching interrupts off for a long time;&n; * warning: not stackable&n; */
r_extern
r_void
id|pmu_suspend
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pmu_resume
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pmu_enable_irled
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
r_extern
r_void
id|pmu_restart
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pmu_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pmu_present
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pmu_get_model
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_PBOOK
multiline_comment|/*&n; * Stuff for putting the powerbook to sleep and waking it again.&n; *&n; */
macro_line|#include &lt;linux/list.h&gt;
DECL|struct|pmu_sleep_notifier
r_struct
id|pmu_sleep_notifier
(brace
DECL|member|notifier_call
r_int
(paren
op_star
id|notifier_call
)paren
(paren
r_struct
id|pmu_sleep_notifier
op_star
id|self
comma
r_int
id|when
)paren
suffix:semicolon
DECL|member|priority
r_int
id|priority
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Code values for calling sleep/wakeup handlers&n; *&n; * Note: If a sleep request got cancelled, all drivers will get&n; * the PBOOK_SLEEP_REJECT, even those who didn&squot;t get the PBOOK_SLEEP_REQUEST.&n; */
DECL|macro|PBOOK_SLEEP_REQUEST
mdefine_line|#define PBOOK_SLEEP_REQUEST&t;1
DECL|macro|PBOOK_SLEEP_NOW
mdefine_line|#define PBOOK_SLEEP_NOW&t;&t;2
DECL|macro|PBOOK_SLEEP_REJECT
mdefine_line|#define PBOOK_SLEEP_REJECT&t;3
DECL|macro|PBOOK_WAKE
mdefine_line|#define PBOOK_WAKE&t;&t;4
multiline_comment|/* Result codes returned by the notifiers */
DECL|macro|PBOOK_SLEEP_OK
mdefine_line|#define PBOOK_SLEEP_OK&t;&t;0
DECL|macro|PBOOK_SLEEP_REFUSE
mdefine_line|#define PBOOK_SLEEP_REFUSE&t;-1
multiline_comment|/* priority levels in notifiers */
DECL|macro|SLEEP_LEVEL_VIDEO
mdefine_line|#define SLEEP_LEVEL_VIDEO&t;100&t;/* Video driver (first wake) */
DECL|macro|SLEEP_LEVEL_MEDIABAY
mdefine_line|#define SLEEP_LEVEL_MEDIABAY&t;90&t;/* Media bay driver */
DECL|macro|SLEEP_LEVEL_BLOCK
mdefine_line|#define SLEEP_LEVEL_BLOCK&t;80&t;/* IDE, SCSI */
DECL|macro|SLEEP_LEVEL_NET
mdefine_line|#define SLEEP_LEVEL_NET&t;&t;70&t;/* bmac, gmac */
DECL|macro|SLEEP_LEVEL_MISC
mdefine_line|#define SLEEP_LEVEL_MISC&t;60&t;/* Anything else */
DECL|macro|SLEEP_LEVEL_USERLAND
mdefine_line|#define SLEEP_LEVEL_USERLAND&t;55&t;/* Reserved for apm_emu */
DECL|macro|SLEEP_LEVEL_ADB
mdefine_line|#define SLEEP_LEVEL_ADB&t;&t;50&t;/* ADB (async) */
DECL|macro|SLEEP_LEVEL_SOUND
mdefine_line|#define SLEEP_LEVEL_SOUND&t;40&t;/* Sound driver (blocking) */
multiline_comment|/* special register notifier functions */
r_int
id|pmu_register_sleep_notifier
c_func
(paren
r_struct
id|pmu_sleep_notifier
op_star
id|notifier
)paren
suffix:semicolon
r_int
id|pmu_unregister_sleep_notifier
c_func
(paren
r_struct
id|pmu_sleep_notifier
op_star
id|notifier
)paren
suffix:semicolon
DECL|macro|PMU_MAX_BATTERIES
mdefine_line|#define PMU_MAX_BATTERIES&t;2
multiline_comment|/* values for pmu_power_flags */
DECL|macro|PMU_PWR_AC_PRESENT
mdefine_line|#define PMU_PWR_AC_PRESENT&t;0x00000001
multiline_comment|/* values for pmu_battery_info.flags */
DECL|macro|PMU_BATT_PRESENT
mdefine_line|#define PMU_BATT_PRESENT&t;0x00000001
DECL|macro|PMU_BATT_CHARGING
mdefine_line|#define PMU_BATT_CHARGING&t;0x00000002
DECL|struct|pmu_battery_info
r_struct
id|pmu_battery_info
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|charge
r_int
r_int
id|charge
suffix:semicolon
multiline_comment|/* current charge */
DECL|member|max_charge
r_int
r_int
id|max_charge
suffix:semicolon
multiline_comment|/* maximum charge */
DECL|member|current
r_int
r_int
id|current
suffix:semicolon
multiline_comment|/* current, positive if charging */
DECL|member|voltage
r_int
r_int
id|voltage
suffix:semicolon
multiline_comment|/* voltage */
DECL|member|time_remaining
r_int
r_int
id|time_remaining
suffix:semicolon
multiline_comment|/* remaining time */
)brace
suffix:semicolon
r_extern
r_int
id|pmu_battery_count
suffix:semicolon
r_extern
r_struct
id|pmu_battery_info
id|pmu_batteries
(braket
id|PMU_MAX_BATTERIES
)braket
suffix:semicolon
r_extern
r_int
r_int
id|pmu_power_flags
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_PBOOK */
macro_line|#endif&t;/* __KERNEL__ */
eof
