multiline_comment|/*&n; * Defines for the mixcom board&n; *&n; * Author: Gergely Madarasz &lt;gorgo@itc.hu&gt;&n; *&n; * Copyright (C) 1999 ITConsult-Pro Co. &lt;info@itc.hu&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; */
DECL|macro|MIXCOM_IO_EXTENT
mdefine_line|#define&t;MIXCOM_IO_EXTENT&t;0x20
DECL|macro|MIXCOM_DEFAULT_IO
mdefine_line|#define&t;MIXCOM_DEFAULT_IO&t;0x180
DECL|macro|MIXCOM_DEFAULT_IRQ
mdefine_line|#define&t;MIXCOM_DEFAULT_IRQ&t;5
DECL|macro|MIXCOM_ID
mdefine_line|#define MIXCOM_ID&t;&t;0x11
DECL|macro|MIXCOM_SERIAL_OFFSET
mdefine_line|#define MIXCOM_SERIAL_OFFSET&t;0x1000
DECL|macro|MIXCOM_CHANNEL_OFFSET
mdefine_line|#define MIXCOM_CHANNEL_OFFSET&t;0x400
DECL|macro|MIXCOM_IT_OFFSET
mdefine_line|#define MIXCOM_IT_OFFSET&t;0xc14
DECL|macro|MIXCOM_STATUS_OFFSET
mdefine_line|#define MIXCOM_STATUS_OFFSET&t;0xc14
DECL|macro|MIXCOM_ID_OFFSET
mdefine_line|#define MIXCOM_ID_OFFSET&t;0xc10
DECL|macro|MIXCOM_ON
mdefine_line|#define MIXCOM_ON&t;&t;0x1
DECL|macro|MIXCOM_OFF
mdefine_line|#define MIXCOM_OFF&t;&t;0x0
multiline_comment|/* Status register bits */
DECL|macro|MIXCOM_CTSB
mdefine_line|#define MIXCOM_CTSB&t;&t;0x1
DECL|macro|MIXCOM_CTSA
mdefine_line|#define MIXCOM_CTSA&t;&t;0x2
DECL|macro|MIXCOM_CHANNELNO
mdefine_line|#define MIXCOM_CHANNELNO&t;0x20
DECL|macro|MIXCOM_POWERFAIL
mdefine_line|#define MIXCOM_POWERFAIL&t;0x40
DECL|macro|MIXCOM_BOOT
mdefine_line|#define MIXCOM_BOOT&t;&t;0x80
eof
