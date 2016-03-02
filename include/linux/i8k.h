multiline_comment|/*&n; * i8k.h -- Linux driver for accessing the SMM BIOS on Dell laptops&n; *&n; * Copyright (C) 2001  Massimo Dal Zotto &lt;dz@debian.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; */
macro_line|#ifndef _LINUX_I8K_H
DECL|macro|_LINUX_I8K_H
mdefine_line|#define _LINUX_I8K_H
DECL|macro|I8K_PROC
mdefine_line|#define I8K_PROC&t;&t;&quot;/proc/i8k&quot;
DECL|macro|I8K_PROC_FMT
mdefine_line|#define I8K_PROC_FMT&t;&t;&quot;1.0&quot;
DECL|macro|I8K_BIOS_VERSION
mdefine_line|#define I8K_BIOS_VERSION&t;_IOR (&squot;i&squot;, 0x80, int)&t;/* broken: meant 4 bytes */
DECL|macro|I8K_MACHINE_ID
mdefine_line|#define I8K_MACHINE_ID&t;&t;_IOR (&squot;i&squot;, 0x81, int)&t;/* broken: meant 16 bytes */
DECL|macro|I8K_POWER_STATUS
mdefine_line|#define I8K_POWER_STATUS&t;_IOR (&squot;i&squot;, 0x82, size_t)
DECL|macro|I8K_FN_STATUS
mdefine_line|#define I8K_FN_STATUS&t;&t;_IOR (&squot;i&squot;, 0x83, size_t)
DECL|macro|I8K_GET_TEMP
mdefine_line|#define I8K_GET_TEMP&t;&t;_IOR (&squot;i&squot;, 0x84, size_t)
DECL|macro|I8K_GET_SPEED
mdefine_line|#define I8K_GET_SPEED&t;&t;_IOWR(&squot;i&squot;, 0x85, size_t)
DECL|macro|I8K_GET_FAN
mdefine_line|#define I8K_GET_FAN&t;&t;_IOWR(&squot;i&squot;, 0x86, size_t)
DECL|macro|I8K_SET_FAN
mdefine_line|#define I8K_SET_FAN&t;&t;_IOWR(&squot;i&squot;, 0x87, size_t)
DECL|macro|I8K_FAN_LEFT
mdefine_line|#define I8K_FAN_LEFT&t;&t;1
DECL|macro|I8K_FAN_RIGHT
mdefine_line|#define I8K_FAN_RIGHT&t;&t;0
DECL|macro|I8K_FAN_OFF
mdefine_line|#define I8K_FAN_OFF&t;&t;0
DECL|macro|I8K_FAN_LOW
mdefine_line|#define I8K_FAN_LOW&t;&t;1
DECL|macro|I8K_FAN_HIGH
mdefine_line|#define I8K_FAN_HIGH&t;&t;2
DECL|macro|I8K_FAN_MAX
mdefine_line|#define I8K_FAN_MAX&t;&t;I8K_FAN_HIGH
DECL|macro|I8K_VOL_UP
mdefine_line|#define I8K_VOL_UP&t;&t;1
DECL|macro|I8K_VOL_DOWN
mdefine_line|#define I8K_VOL_DOWN&t;&t;2
DECL|macro|I8K_VOL_MUTE
mdefine_line|#define I8K_VOL_MUTE&t;&t;4
DECL|macro|I8K_AC
mdefine_line|#define I8K_AC&t;&t;&t;1
DECL|macro|I8K_BATTERY
mdefine_line|#define I8K_BATTERY&t;&t;0
macro_line|#endif
eof
