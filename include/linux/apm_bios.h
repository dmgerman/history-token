macro_line|#ifndef _LINUX_APM_H
DECL|macro|_LINUX_APM_H
mdefine_line|#define _LINUX_APM_H
multiline_comment|/*&n; * Include file for the interface to an APM BIOS&n; * Copyright 1994-2001 Stephen Rothwell (sfr@canb.auug.org.au)&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; */
DECL|typedef|apm_event_t
r_typedef
r_int
r_int
id|apm_event_t
suffix:semicolon
DECL|typedef|apm_eventinfo_t
r_typedef
r_int
r_int
id|apm_eventinfo_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|APM_40
mdefine_line|#define APM_40&t;&t;0x40
DECL|macro|APM_CS
mdefine_line|#define APM_CS&t;&t;(APM_40 + 8)
DECL|macro|APM_CS_16
mdefine_line|#define APM_CS_16&t;(APM_CS + 8)
DECL|macro|APM_DS
mdefine_line|#define APM_DS&t;&t;(APM_CS_16 + 8)
DECL|struct|apm_bios_info
r_struct
id|apm_bios_info
(brace
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|cseg
r_int
r_int
id|cseg
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|cseg_16
r_int
r_int
id|cseg_16
suffix:semicolon
DECL|member|dseg
r_int
r_int
id|dseg
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|cseg_len
r_int
r_int
id|cseg_len
suffix:semicolon
DECL|member|cseg_16_len
r_int
r_int
id|cseg_16_len
suffix:semicolon
DECL|member|dseg_len
r_int
r_int
id|dseg_len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Results of APM Installation Check */
DECL|macro|APM_16_BIT_SUPPORT
mdefine_line|#define APM_16_BIT_SUPPORT&t;0x0001
DECL|macro|APM_32_BIT_SUPPORT
mdefine_line|#define APM_32_BIT_SUPPORT&t;0x0002
DECL|macro|APM_IDLE_SLOWS_CLOCK
mdefine_line|#define APM_IDLE_SLOWS_CLOCK&t;0x0004
DECL|macro|APM_BIOS_DISABLED
mdefine_line|#define APM_BIOS_DISABLED      &t;0x0008
DECL|macro|APM_BIOS_DISENGAGED
mdefine_line|#define APM_BIOS_DISENGAGED     0x0010
multiline_comment|/*&n; * Data for APM that is persistant across module unload/load&n; */
DECL|struct|apm_info
r_struct
id|apm_info
(brace
DECL|member|bios
r_struct
id|apm_bios_info
id|bios
suffix:semicolon
DECL|member|connection_version
r_int
r_int
id|connection_version
suffix:semicolon
DECL|member|get_power_status_broken
r_int
id|get_power_status_broken
suffix:semicolon
DECL|member|get_power_status_swabinminutes
r_int
id|get_power_status_swabinminutes
suffix:semicolon
DECL|member|allow_ints
r_int
id|allow_ints
suffix:semicolon
DECL|member|realmode_power_off
r_int
id|realmode_power_off
suffix:semicolon
DECL|member|disabled
r_int
id|disabled
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The APM function codes&n; */
DECL|macro|APM_FUNC_INST_CHECK
mdefine_line|#define&t;APM_FUNC_INST_CHECK&t;0x5300
DECL|macro|APM_FUNC_REAL_CONN
mdefine_line|#define&t;APM_FUNC_REAL_CONN&t;0x5301
DECL|macro|APM_FUNC_16BIT_CONN
mdefine_line|#define&t;APM_FUNC_16BIT_CONN&t;0x5302
DECL|macro|APM_FUNC_32BIT_CONN
mdefine_line|#define&t;APM_FUNC_32BIT_CONN&t;0x5303
DECL|macro|APM_FUNC_DISCONN
mdefine_line|#define&t;APM_FUNC_DISCONN&t;0x5304
DECL|macro|APM_FUNC_IDLE
mdefine_line|#define&t;APM_FUNC_IDLE&t;&t;0x5305
DECL|macro|APM_FUNC_BUSY
mdefine_line|#define&t;APM_FUNC_BUSY&t;&t;0x5306
DECL|macro|APM_FUNC_SET_STATE
mdefine_line|#define&t;APM_FUNC_SET_STATE&t;0x5307
DECL|macro|APM_FUNC_ENABLE_PM
mdefine_line|#define&t;APM_FUNC_ENABLE_PM&t;0x5308
DECL|macro|APM_FUNC_RESTORE_BIOS
mdefine_line|#define&t;APM_FUNC_RESTORE_BIOS&t;0x5309
DECL|macro|APM_FUNC_GET_STATUS
mdefine_line|#define&t;APM_FUNC_GET_STATUS&t;0x530a
DECL|macro|APM_FUNC_GET_EVENT
mdefine_line|#define&t;APM_FUNC_GET_EVENT&t;0x530b
DECL|macro|APM_FUNC_GET_STATE
mdefine_line|#define&t;APM_FUNC_GET_STATE&t;0x530c
DECL|macro|APM_FUNC_ENABLE_DEV_PM
mdefine_line|#define&t;APM_FUNC_ENABLE_DEV_PM&t;0x530d
DECL|macro|APM_FUNC_VERSION
mdefine_line|#define&t;APM_FUNC_VERSION&t;0x530e
DECL|macro|APM_FUNC_ENGAGE_PM
mdefine_line|#define&t;APM_FUNC_ENGAGE_PM&t;0x530f
DECL|macro|APM_FUNC_GET_CAP
mdefine_line|#define&t;APM_FUNC_GET_CAP&t;0x5310
DECL|macro|APM_FUNC_RESUME_TIMER
mdefine_line|#define&t;APM_FUNC_RESUME_TIMER&t;0x5311
DECL|macro|APM_FUNC_RESUME_ON_RING
mdefine_line|#define&t;APM_FUNC_RESUME_ON_RING&t;0x5312
DECL|macro|APM_FUNC_TIMER
mdefine_line|#define&t;APM_FUNC_TIMER&t;&t;0x5313
multiline_comment|/*&n; * Function code for APM_FUNC_RESUME_TIMER&n; */
DECL|macro|APM_FUNC_DISABLE_TIMER
mdefine_line|#define&t;APM_FUNC_DISABLE_TIMER&t;0
DECL|macro|APM_FUNC_GET_TIMER
mdefine_line|#define&t;APM_FUNC_GET_TIMER&t;1
DECL|macro|APM_FUNC_SET_TIMER
mdefine_line|#define&t;APM_FUNC_SET_TIMER&t;2
multiline_comment|/*&n; * Function code for APM_FUNC_RESUME_ON_RING&n; */
DECL|macro|APM_FUNC_DISABLE_RING
mdefine_line|#define&t;APM_FUNC_DISABLE_RING&t;0
DECL|macro|APM_FUNC_ENABLE_RING
mdefine_line|#define&t;APM_FUNC_ENABLE_RING&t;1
DECL|macro|APM_FUNC_GET_RING
mdefine_line|#define&t;APM_FUNC_GET_RING&t;2
multiline_comment|/*&n; * Function code for APM_FUNC_TIMER_STATUS&n; */
DECL|macro|APM_FUNC_TIMER_DISABLE
mdefine_line|#define&t;APM_FUNC_TIMER_DISABLE&t;0
DECL|macro|APM_FUNC_TIMER_ENABLE
mdefine_line|#define&t;APM_FUNC_TIMER_ENABLE&t;1
DECL|macro|APM_FUNC_TIMER_GET
mdefine_line|#define&t;APM_FUNC_TIMER_GET&t;2
multiline_comment|/*&n; * in arch/i386/kernel/setup.c&n; */
r_extern
r_struct
id|apm_info
id|apm_info
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/*&n; * Power states&n; */
DECL|macro|APM_STATE_READY
mdefine_line|#define APM_STATE_READY&t;&t;0x0000
DECL|macro|APM_STATE_STANDBY
mdefine_line|#define APM_STATE_STANDBY&t;0x0001
DECL|macro|APM_STATE_SUSPEND
mdefine_line|#define APM_STATE_SUSPEND&t;0x0002
DECL|macro|APM_STATE_OFF
mdefine_line|#define APM_STATE_OFF&t;&t;0x0003
DECL|macro|APM_STATE_BUSY
mdefine_line|#define APM_STATE_BUSY&t;&t;0x0004
DECL|macro|APM_STATE_REJECT
mdefine_line|#define APM_STATE_REJECT&t;0x0005
DECL|macro|APM_STATE_OEM_SYS
mdefine_line|#define APM_STATE_OEM_SYS&t;0x0020
DECL|macro|APM_STATE_OEM_DEV
mdefine_line|#define APM_STATE_OEM_DEV&t;0x0040
DECL|macro|APM_STATE_DISABLE
mdefine_line|#define APM_STATE_DISABLE&t;0x0000
DECL|macro|APM_STATE_ENABLE
mdefine_line|#define APM_STATE_ENABLE&t;0x0001
DECL|macro|APM_STATE_DISENGAGE
mdefine_line|#define APM_STATE_DISENGAGE&t;0x0000
DECL|macro|APM_STATE_ENGAGE
mdefine_line|#define APM_STATE_ENGAGE&t;0x0001
multiline_comment|/*&n; * Events (results of Get PM Event)&n; */
DECL|macro|APM_SYS_STANDBY
mdefine_line|#define APM_SYS_STANDBY&t;&t;0x0001
DECL|macro|APM_SYS_SUSPEND
mdefine_line|#define APM_SYS_SUSPEND&t;&t;0x0002
DECL|macro|APM_NORMAL_RESUME
mdefine_line|#define APM_NORMAL_RESUME&t;0x0003
DECL|macro|APM_CRITICAL_RESUME
mdefine_line|#define APM_CRITICAL_RESUME&t;0x0004
DECL|macro|APM_LOW_BATTERY
mdefine_line|#define APM_LOW_BATTERY&t;&t;0x0005
DECL|macro|APM_POWER_STATUS_CHANGE
mdefine_line|#define APM_POWER_STATUS_CHANGE&t;0x0006
DECL|macro|APM_UPDATE_TIME
mdefine_line|#define APM_UPDATE_TIME&t;&t;0x0007
DECL|macro|APM_CRITICAL_SUSPEND
mdefine_line|#define APM_CRITICAL_SUSPEND&t;0x0008
DECL|macro|APM_USER_STANDBY
mdefine_line|#define APM_USER_STANDBY&t;0x0009
DECL|macro|APM_USER_SUSPEND
mdefine_line|#define APM_USER_SUSPEND&t;0x000a
DECL|macro|APM_STANDBY_RESUME
mdefine_line|#define APM_STANDBY_RESUME&t;0x000b
DECL|macro|APM_CAPABILITY_CHANGE
mdefine_line|#define APM_CAPABILITY_CHANGE&t;0x000c
multiline_comment|/*&n; * Error codes&n; */
DECL|macro|APM_SUCCESS
mdefine_line|#define APM_SUCCESS&t;&t;0x00
DECL|macro|APM_DISABLED
mdefine_line|#define APM_DISABLED&t;&t;0x01
DECL|macro|APM_CONNECTED
mdefine_line|#define APM_CONNECTED&t;&t;0x02
DECL|macro|APM_NOT_CONNECTED
mdefine_line|#define APM_NOT_CONNECTED&t;0x03
DECL|macro|APM_16_CONNECTED
mdefine_line|#define APM_16_CONNECTED&t;0x05
DECL|macro|APM_16_UNSUPPORTED
mdefine_line|#define APM_16_UNSUPPORTED&t;0x06
DECL|macro|APM_32_CONNECTED
mdefine_line|#define APM_32_CONNECTED&t;0x07
DECL|macro|APM_32_UNSUPPORTED
mdefine_line|#define APM_32_UNSUPPORTED&t;0x08
DECL|macro|APM_BAD_DEVICE
mdefine_line|#define APM_BAD_DEVICE&t;&t;0x09
DECL|macro|APM_BAD_PARAM
mdefine_line|#define APM_BAD_PARAM&t;&t;0x0a
DECL|macro|APM_NOT_ENGAGED
mdefine_line|#define APM_NOT_ENGAGED&t;&t;0x0b
DECL|macro|APM_BAD_FUNCTION
mdefine_line|#define APM_BAD_FUNCTION&t;0x0c
DECL|macro|APM_RESUME_DISABLED
mdefine_line|#define APM_RESUME_DISABLED&t;0x0d
DECL|macro|APM_NO_ERROR
mdefine_line|#define APM_NO_ERROR&t;&t;0x53
DECL|macro|APM_BAD_STATE
mdefine_line|#define APM_BAD_STATE&t;&t;0x60
DECL|macro|APM_NO_EVENTS
mdefine_line|#define APM_NO_EVENTS&t;&t;0x80
DECL|macro|APM_NOT_PRESENT
mdefine_line|#define APM_NOT_PRESENT&t;&t;0x86
multiline_comment|/*&n; * APM Device IDs&n; */
DECL|macro|APM_DEVICE_BIOS
mdefine_line|#define APM_DEVICE_BIOS&t;&t;0x0000
DECL|macro|APM_DEVICE_ALL
mdefine_line|#define APM_DEVICE_ALL&t;&t;0x0001
DECL|macro|APM_DEVICE_DISPLAY
mdefine_line|#define APM_DEVICE_DISPLAY&t;0x0100
DECL|macro|APM_DEVICE_STORAGE
mdefine_line|#define APM_DEVICE_STORAGE&t;0x0200
DECL|macro|APM_DEVICE_PARALLEL
mdefine_line|#define APM_DEVICE_PARALLEL&t;0x0300
DECL|macro|APM_DEVICE_SERIAL
mdefine_line|#define APM_DEVICE_SERIAL&t;0x0400
DECL|macro|APM_DEVICE_NETWORK
mdefine_line|#define APM_DEVICE_NETWORK&t;0x0500
DECL|macro|APM_DEVICE_PCMCIA
mdefine_line|#define APM_DEVICE_PCMCIA&t;0x0600
DECL|macro|APM_DEVICE_BATTERY
mdefine_line|#define APM_DEVICE_BATTERY&t;0x8000
DECL|macro|APM_DEVICE_OEM
mdefine_line|#define APM_DEVICE_OEM&t;&t;0xe000
DECL|macro|APM_DEVICE_OLD_ALL
mdefine_line|#define APM_DEVICE_OLD_ALL&t;0xffff
DECL|macro|APM_DEVICE_CLASS
mdefine_line|#define APM_DEVICE_CLASS&t;0x00ff
DECL|macro|APM_DEVICE_MASK
mdefine_line|#define APM_DEVICE_MASK&t;&t;0xff00
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This is the &quot;All Devices&quot; ID communicated to the BIOS&n; */
DECL|macro|APM_DEVICE_BALL
mdefine_line|#define APM_DEVICE_BALL&t;&t;((apm_info.connection_version &gt; 0x0100) ? &bslash;&n;&t;&t;&t;&t; APM_DEVICE_ALL : APM_DEVICE_OLD_ALL)
macro_line|#endif
multiline_comment|/*&n; * Battery status&n; */
DECL|macro|APM_MAX_BATTERIES
mdefine_line|#define APM_MAX_BATTERIES&t;2
multiline_comment|/*&n; * APM defined capability bit flags&n; */
DECL|macro|APM_CAP_GLOBAL_STANDBY
mdefine_line|#define APM_CAP_GLOBAL_STANDBY&t;&t;0x0001
DECL|macro|APM_CAP_GLOBAL_SUSPEND
mdefine_line|#define APM_CAP_GLOBAL_SUSPEND&t;&t;0x0002
DECL|macro|APM_CAP_RESUME_STANDBY_TIMER
mdefine_line|#define APM_CAP_RESUME_STANDBY_TIMER&t;0x0004 /* Timer resume from standby */
DECL|macro|APM_CAP_RESUME_SUSPEND_TIMER
mdefine_line|#define APM_CAP_RESUME_SUSPEND_TIMER&t;0x0008 /* Timer resume from suspend */
DECL|macro|APM_CAP_RESUME_STANDBY_RING
mdefine_line|#define APM_CAP_RESUME_STANDBY_RING&t;0x0010 /* Resume on Ring fr standby */
DECL|macro|APM_CAP_RESUME_SUSPEND_RING
mdefine_line|#define APM_CAP_RESUME_SUSPEND_RING&t;0x0020 /* Resume on Ring fr suspend */
DECL|macro|APM_CAP_RESUME_STANDBY_PCMCIA
mdefine_line|#define APM_CAP_RESUME_STANDBY_PCMCIA&t;0x0040 /* Resume on PCMCIA Ring&t;*/
DECL|macro|APM_CAP_RESUME_SUSPEND_PCMCIA
mdefine_line|#define APM_CAP_RESUME_SUSPEND_PCMCIA&t;0x0080 /* Resume on PCMCIA Ring&t;*/
multiline_comment|/*&n; * ioctl operations&n; */
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|APM_IOC_STANDBY
mdefine_line|#define APM_IOC_STANDBY&t;&t;_IO(&squot;A&squot;, 1)
DECL|macro|APM_IOC_SUSPEND
mdefine_line|#define APM_IOC_SUSPEND&t;&t;_IO(&squot;A&squot;, 2)
macro_line|#endif&t;/* LINUX_APM_H */
eof
