multiline_comment|/* &n; * Sony Programmable I/O Control Device driver for VAIO&n; *&n; * Copyright (C) 2001-2003 Stelian Pop &lt;stelian@popies.net&gt;&n; *&n; * Copyright (C) 2001-2002 Alc&#xfffd;ve &lt;www.alcove.com&gt;&n; *&n; * Copyright (C) 2001 Michael Ashley &lt;m.ashley@unsw.edu.au&gt;&n; *&n; * Copyright (C) 2001 Junichi Morita &lt;jun1m@mars.dti.ne.jp&gt;&n; *&n; * Copyright (C) 2000 Takaya Kinjo &lt;t-kinjo@tc4.so-net.ne.jp&gt;&n; *&n; * Copyright (C) 2000 Andrew Tridgell &lt;tridge@valinux.com&gt;&n; *&n; * Earlier work by Werner Almesberger, Paul `Rusty&squot; Russell and Paul Mackerras.&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef _SONYPI_PRIV_H_ 
DECL|macro|_SONYPI_PRIV_H_
mdefine_line|#define _SONYPI_PRIV_H_
macro_line|#ifdef __KERNEL__
DECL|macro|SONYPI_DRIVER_MAJORVERSION
mdefine_line|#define SONYPI_DRIVER_MAJORVERSION&t; 1
DECL|macro|SONYPI_DRIVER_MINORVERSION
mdefine_line|#define SONYPI_DRIVER_MINORVERSION&t;22
DECL|macro|SONYPI_DEVICE_MODEL_TYPE1
mdefine_line|#define SONYPI_DEVICE_MODEL_TYPE1&t;1
DECL|macro|SONYPI_DEVICE_MODEL_TYPE2
mdefine_line|#define SONYPI_DEVICE_MODEL_TYPE2&t;2
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &quot;linux/sonypi.h&quot;
multiline_comment|/* type1 models use those */
DECL|macro|SONYPI_IRQ_PORT
mdefine_line|#define SONYPI_IRQ_PORT&t;&t;&t;0x8034
DECL|macro|SONYPI_IRQ_SHIFT
mdefine_line|#define SONYPI_IRQ_SHIFT&t;&t;22
DECL|macro|SONYPI_BASE
mdefine_line|#define SONYPI_BASE&t;&t;&t;0x50
DECL|macro|SONYPI_G10A
mdefine_line|#define SONYPI_G10A&t;&t;&t;(SONYPI_BASE+0x14)
DECL|macro|SONYPI_TYPE1_REGION_SIZE
mdefine_line|#define SONYPI_TYPE1_REGION_SIZE&t;0x08
DECL|macro|SONYPI_TYPE1_EVTYPE_OFFSET
mdefine_line|#define SONYPI_TYPE1_EVTYPE_OFFSET&t;0x04
multiline_comment|/* type2 series specifics */
DECL|macro|SONYPI_SIRQ
mdefine_line|#define SONYPI_SIRQ&t;&t;&t;0x9b
DECL|macro|SONYPI_SLOB
mdefine_line|#define SONYPI_SLOB&t;&t;&t;0x9c
DECL|macro|SONYPI_SHIB
mdefine_line|#define SONYPI_SHIB&t;&t;&t;0x9d
DECL|macro|SONYPI_TYPE2_REGION_SIZE
mdefine_line|#define SONYPI_TYPE2_REGION_SIZE&t;0x20
DECL|macro|SONYPI_TYPE2_EVTYPE_OFFSET
mdefine_line|#define SONYPI_TYPE2_EVTYPE_OFFSET&t;0x12
multiline_comment|/* battery / brightness addresses */
DECL|macro|SONYPI_BAT_FLAGS
mdefine_line|#define SONYPI_BAT_FLAGS&t;0x81
DECL|macro|SONYPI_LCD_LIGHT
mdefine_line|#define SONYPI_LCD_LIGHT&t;0x96
DECL|macro|SONYPI_BAT1_PCTRM
mdefine_line|#define SONYPI_BAT1_PCTRM&t;0xa0
DECL|macro|SONYPI_BAT1_LEFT
mdefine_line|#define SONYPI_BAT1_LEFT&t;0xa2
DECL|macro|SONYPI_BAT1_MAXRT
mdefine_line|#define SONYPI_BAT1_MAXRT&t;0xa4
DECL|macro|SONYPI_BAT2_PCTRM
mdefine_line|#define SONYPI_BAT2_PCTRM&t;0xa8
DECL|macro|SONYPI_BAT2_LEFT
mdefine_line|#define SONYPI_BAT2_LEFT&t;0xaa
DECL|macro|SONYPI_BAT2_MAXRT
mdefine_line|#define SONYPI_BAT2_MAXRT&t;0xac
DECL|macro|SONYPI_BAT1_MAXTK
mdefine_line|#define SONYPI_BAT1_MAXTK&t;0xb0
DECL|macro|SONYPI_BAT1_FULL
mdefine_line|#define SONYPI_BAT1_FULL&t;0xb2
DECL|macro|SONYPI_BAT2_MAXTK
mdefine_line|#define SONYPI_BAT2_MAXTK&t;0xb8
DECL|macro|SONYPI_BAT2_FULL
mdefine_line|#define SONYPI_BAT2_FULL&t;0xba
multiline_comment|/* ioports used for brightness and type2 events */
DECL|macro|SONYPI_DATA_IOPORT
mdefine_line|#define SONYPI_DATA_IOPORT&t;0x62
DECL|macro|SONYPI_CST_IOPORT
mdefine_line|#define SONYPI_CST_IOPORT&t;0x66
multiline_comment|/* The set of possible ioports */
DECL|struct|sonypi_ioport_list
r_struct
id|sonypi_ioport_list
(brace
DECL|member|port1
id|u16
id|port1
suffix:semicolon
DECL|member|port2
id|u16
id|port2
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|sonypi_type1_ioport_list
r_static
r_struct
id|sonypi_ioport_list
id|sonypi_type1_ioport_list
(braket
)braket
op_assign
(brace
(brace
l_int|0x10c0
comma
l_int|0x10c4
)brace
comma
multiline_comment|/* looks like the default on C1Vx */
(brace
l_int|0x1080
comma
l_int|0x1084
)brace
comma
(brace
l_int|0x1090
comma
l_int|0x1094
)brace
comma
(brace
l_int|0x10a0
comma
l_int|0x10a4
)brace
comma
(brace
l_int|0x10b0
comma
l_int|0x10b4
)brace
comma
(brace
l_int|0x0
comma
l_int|0x0
)brace
)brace
suffix:semicolon
DECL|variable|sonypi_type2_ioport_list
r_static
r_struct
id|sonypi_ioport_list
id|sonypi_type2_ioport_list
(braket
)braket
op_assign
(brace
(brace
l_int|0x1080
comma
l_int|0x1084
)brace
comma
(brace
l_int|0x10a0
comma
l_int|0x10a4
)brace
comma
(brace
l_int|0x10c0
comma
l_int|0x10c4
)brace
comma
(brace
l_int|0x10e0
comma
l_int|0x10e4
)brace
comma
(brace
l_int|0x0
comma
l_int|0x0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible interrupts */
DECL|struct|sonypi_irq_list
r_struct
id|sonypi_irq_list
(brace
DECL|member|irq
id|u16
id|irq
suffix:semicolon
DECL|member|bits
id|u16
id|bits
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|sonypi_type1_irq_list
r_static
r_struct
id|sonypi_irq_list
id|sonypi_type1_irq_list
(braket
)braket
op_assign
(brace
(brace
l_int|11
comma
l_int|0x2
)brace
comma
multiline_comment|/* IRQ 11, GO22=0,GO23=1 in AML */
(brace
l_int|10
comma
l_int|0x1
)brace
comma
multiline_comment|/* IRQ 10, GO22=1,GO23=0 in AML */
(brace
l_int|5
comma
l_int|0x0
)brace
comma
multiline_comment|/* IRQ  5, GO22=0,GO23=0 in AML */
(brace
l_int|0
comma
l_int|0x3
)brace
multiline_comment|/* no IRQ, GO22=1,GO23=1 in AML */
)brace
suffix:semicolon
DECL|variable|sonypi_type2_irq_list
r_static
r_struct
id|sonypi_irq_list
id|sonypi_type2_irq_list
(braket
)braket
op_assign
(brace
(brace
l_int|11
comma
l_int|0x80
)brace
comma
multiline_comment|/* IRQ 11, 0x80 in SIRQ in AML */
(brace
l_int|10
comma
l_int|0x40
)brace
comma
multiline_comment|/* IRQ 10, 0x40 in SIRQ in AML */
(brace
l_int|9
comma
l_int|0x20
)brace
comma
multiline_comment|/* IRQ  9, 0x20 in SIRQ in AML */
(brace
l_int|6
comma
l_int|0x10
)brace
comma
multiline_comment|/* IRQ  6, 0x10 in SIRQ in AML */
(brace
l_int|0
comma
l_int|0x00
)brace
multiline_comment|/* no IRQ, 0x00 in SIRQ in AML */
)brace
suffix:semicolon
DECL|macro|SONYPI_CAMERA_BRIGHTNESS
mdefine_line|#define SONYPI_CAMERA_BRIGHTNESS&t;&t;0
DECL|macro|SONYPI_CAMERA_CONTRAST
mdefine_line|#define SONYPI_CAMERA_CONTRAST&t;&t;&t;1
DECL|macro|SONYPI_CAMERA_HUE
mdefine_line|#define SONYPI_CAMERA_HUE&t;&t;&t;2
DECL|macro|SONYPI_CAMERA_COLOR
mdefine_line|#define SONYPI_CAMERA_COLOR&t;&t;&t;3
DECL|macro|SONYPI_CAMERA_SHARPNESS
mdefine_line|#define SONYPI_CAMERA_SHARPNESS&t;&t;&t;4
DECL|macro|SONYPI_CAMERA_PICTURE
mdefine_line|#define SONYPI_CAMERA_PICTURE&t;&t;&t;5
DECL|macro|SONYPI_CAMERA_EXPOSURE_MASK
mdefine_line|#define SONYPI_CAMERA_EXPOSURE_MASK&t;&t;0xC
DECL|macro|SONYPI_CAMERA_WHITE_BALANCE_MASK
mdefine_line|#define SONYPI_CAMERA_WHITE_BALANCE_MASK&t;0x3
DECL|macro|SONYPI_CAMERA_PICTURE_MODE_MASK
mdefine_line|#define SONYPI_CAMERA_PICTURE_MODE_MASK&t;&t;0x30
DECL|macro|SONYPI_CAMERA_MUTE_MASK
mdefine_line|#define SONYPI_CAMERA_MUTE_MASK&t;&t;&t;0x40
multiline_comment|/* the rest don&squot;t need a loop until not 0xff */
DECL|macro|SONYPI_CAMERA_AGC
mdefine_line|#define SONYPI_CAMERA_AGC&t;&t;&t;6
DECL|macro|SONYPI_CAMERA_AGC_MASK
mdefine_line|#define SONYPI_CAMERA_AGC_MASK&t;&t;&t;0x30
DECL|macro|SONYPI_CAMERA_SHUTTER_MASK
mdefine_line|#define SONYPI_CAMERA_SHUTTER_MASK &t;&t;0x7
DECL|macro|SONYPI_CAMERA_SHUTDOWN_REQUEST
mdefine_line|#define SONYPI_CAMERA_SHUTDOWN_REQUEST&t;&t;7
DECL|macro|SONYPI_CAMERA_CONTROL
mdefine_line|#define SONYPI_CAMERA_CONTROL&t;&t;&t;0x10
DECL|macro|SONYPI_CAMERA_STATUS
mdefine_line|#define SONYPI_CAMERA_STATUS &t;&t;&t;7
DECL|macro|SONYPI_CAMERA_STATUS_READY
mdefine_line|#define SONYPI_CAMERA_STATUS_READY &t;&t;0x2
DECL|macro|SONYPI_CAMERA_STATUS_POSITION
mdefine_line|#define SONYPI_CAMERA_STATUS_POSITION&t;&t;0x4
DECL|macro|SONYPI_DIRECTION_BACKWARDS
mdefine_line|#define SONYPI_DIRECTION_BACKWARDS &t;&t;0x4
DECL|macro|SONYPI_CAMERA_REVISION
mdefine_line|#define SONYPI_CAMERA_REVISION &t;&t;&t;8
DECL|macro|SONYPI_CAMERA_ROMVERSION
mdefine_line|#define SONYPI_CAMERA_ROMVERSION &t;&t;9
multiline_comment|/* Event masks */
DECL|macro|SONYPI_JOGGER_MASK
mdefine_line|#define SONYPI_JOGGER_MASK&t;&t;&t;0x00000001
DECL|macro|SONYPI_CAPTURE_MASK
mdefine_line|#define SONYPI_CAPTURE_MASK&t;&t;&t;0x00000002
DECL|macro|SONYPI_FNKEY_MASK
mdefine_line|#define SONYPI_FNKEY_MASK&t;&t;&t;0x00000004
DECL|macro|SONYPI_BLUETOOTH_MASK
mdefine_line|#define SONYPI_BLUETOOTH_MASK&t;&t;&t;0x00000008
DECL|macro|SONYPI_PKEY_MASK
mdefine_line|#define SONYPI_PKEY_MASK&t;&t;&t;0x00000010
DECL|macro|SONYPI_BACK_MASK
mdefine_line|#define SONYPI_BACK_MASK&t;&t;&t;0x00000020
DECL|macro|SONYPI_HELP_MASK
mdefine_line|#define SONYPI_HELP_MASK&t;&t;&t;0x00000040
DECL|macro|SONYPI_LID_MASK
mdefine_line|#define SONYPI_LID_MASK&t;&t;&t;&t;0x00000080
DECL|macro|SONYPI_ZOOM_MASK
mdefine_line|#define SONYPI_ZOOM_MASK&t;&t;&t;0x00000100
DECL|macro|SONYPI_THUMBPHRASE_MASK
mdefine_line|#define SONYPI_THUMBPHRASE_MASK&t;&t;&t;0x00000200
DECL|macro|SONYPI_MEYE_MASK
mdefine_line|#define SONYPI_MEYE_MASK&t;&t;&t;0x00000400
DECL|macro|SONYPI_MEMORYSTICK_MASK
mdefine_line|#define SONYPI_MEMORYSTICK_MASK&t;&t;&t;0x00000800
DECL|macro|SONYPI_BATTERY_MASK
mdefine_line|#define SONYPI_BATTERY_MASK&t;&t;&t;0x00001000
DECL|struct|sonypi_event
r_struct
id|sonypi_event
(brace
DECL|member|data
id|u8
id|data
suffix:semicolon
DECL|member|event
id|u8
id|event
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The set of possible button release events */
DECL|variable|sonypi_releaseev
r_static
r_struct
id|sonypi_event
id|sonypi_releaseev
(braket
)braket
op_assign
(brace
(brace
l_int|0x00
comma
id|SONYPI_EVENT_ANYBUTTON_RELEASED
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible jogger events  */
DECL|variable|sonypi_joggerev
r_static
r_struct
id|sonypi_event
id|sonypi_joggerev
(braket
)braket
op_assign
(brace
(brace
l_int|0x1f
comma
id|SONYPI_EVENT_JOGDIAL_UP
)brace
comma
(brace
l_int|0x01
comma
id|SONYPI_EVENT_JOGDIAL_DOWN
)brace
comma
(brace
l_int|0x5f
comma
id|SONYPI_EVENT_JOGDIAL_UP_PRESSED
)brace
comma
(brace
l_int|0x41
comma
id|SONYPI_EVENT_JOGDIAL_DOWN_PRESSED
)brace
comma
(brace
l_int|0x1e
comma
id|SONYPI_EVENT_JOGDIAL_FAST_UP
)brace
comma
(brace
l_int|0x02
comma
id|SONYPI_EVENT_JOGDIAL_FAST_DOWN
)brace
comma
(brace
l_int|0x5e
comma
id|SONYPI_EVENT_JOGDIAL_FAST_UP_PRESSED
)brace
comma
(brace
l_int|0x42
comma
id|SONYPI_EVENT_JOGDIAL_FAST_DOWN_PRESSED
)brace
comma
(brace
l_int|0x1d
comma
id|SONYPI_EVENT_JOGDIAL_VFAST_UP
)brace
comma
(brace
l_int|0x03
comma
id|SONYPI_EVENT_JOGDIAL_VFAST_DOWN
)brace
comma
(brace
l_int|0x5d
comma
id|SONYPI_EVENT_JOGDIAL_VFAST_UP_PRESSED
)brace
comma
(brace
l_int|0x43
comma
id|SONYPI_EVENT_JOGDIAL_VFAST_DOWN_PRESSED
)brace
comma
(brace
l_int|0x40
comma
id|SONYPI_EVENT_JOGDIAL_PRESSED
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible capture button events */
DECL|variable|sonypi_captureev
r_static
r_struct
id|sonypi_event
id|sonypi_captureev
(braket
)braket
op_assign
(brace
(brace
l_int|0x05
comma
id|SONYPI_EVENT_CAPTURE_PARTIALPRESSED
)brace
comma
(brace
l_int|0x07
comma
id|SONYPI_EVENT_CAPTURE_PRESSED
)brace
comma
(brace
l_int|0x01
comma
id|SONYPI_EVENT_CAPTURE_PARTIALRELEASED
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible fnkeys events */
DECL|variable|sonypi_fnkeyev
r_static
r_struct
id|sonypi_event
id|sonypi_fnkeyev
(braket
)braket
op_assign
(brace
(brace
l_int|0x10
comma
id|SONYPI_EVENT_FNKEY_ESC
)brace
comma
(brace
l_int|0x11
comma
id|SONYPI_EVENT_FNKEY_F1
)brace
comma
(brace
l_int|0x12
comma
id|SONYPI_EVENT_FNKEY_F2
)brace
comma
(brace
l_int|0x13
comma
id|SONYPI_EVENT_FNKEY_F3
)brace
comma
(brace
l_int|0x14
comma
id|SONYPI_EVENT_FNKEY_F4
)brace
comma
(brace
l_int|0x15
comma
id|SONYPI_EVENT_FNKEY_F5
)brace
comma
(brace
l_int|0x16
comma
id|SONYPI_EVENT_FNKEY_F6
)brace
comma
(brace
l_int|0x17
comma
id|SONYPI_EVENT_FNKEY_F7
)brace
comma
(brace
l_int|0x18
comma
id|SONYPI_EVENT_FNKEY_F8
)brace
comma
(brace
l_int|0x19
comma
id|SONYPI_EVENT_FNKEY_F9
)brace
comma
(brace
l_int|0x1a
comma
id|SONYPI_EVENT_FNKEY_F10
)brace
comma
(brace
l_int|0x1b
comma
id|SONYPI_EVENT_FNKEY_F11
)brace
comma
(brace
l_int|0x1c
comma
id|SONYPI_EVENT_FNKEY_F12
)brace
comma
(brace
l_int|0x21
comma
id|SONYPI_EVENT_FNKEY_1
)brace
comma
(brace
l_int|0x22
comma
id|SONYPI_EVENT_FNKEY_2
)brace
comma
(brace
l_int|0x31
comma
id|SONYPI_EVENT_FNKEY_D
)brace
comma
(brace
l_int|0x32
comma
id|SONYPI_EVENT_FNKEY_E
)brace
comma
(brace
l_int|0x33
comma
id|SONYPI_EVENT_FNKEY_F
)brace
comma
(brace
l_int|0x34
comma
id|SONYPI_EVENT_FNKEY_S
)brace
comma
(brace
l_int|0x35
comma
id|SONYPI_EVENT_FNKEY_B
)brace
comma
(brace
l_int|0x36
comma
id|SONYPI_EVENT_FNKEY_ONLY
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible program key events */
DECL|variable|sonypi_pkeyev
r_static
r_struct
id|sonypi_event
id|sonypi_pkeyev
(braket
)braket
op_assign
(brace
(brace
l_int|0x01
comma
id|SONYPI_EVENT_PKEY_P1
)brace
comma
(brace
l_int|0x02
comma
id|SONYPI_EVENT_PKEY_P2
)brace
comma
(brace
l_int|0x04
comma
id|SONYPI_EVENT_PKEY_P3
)brace
comma
(brace
l_int|0x5c
comma
id|SONYPI_EVENT_PKEY_P1
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible bluetooth events */
DECL|variable|sonypi_blueev
r_static
r_struct
id|sonypi_event
id|sonypi_blueev
(braket
)braket
op_assign
(brace
(brace
l_int|0x55
comma
id|SONYPI_EVENT_BLUETOOTH_PRESSED
)brace
comma
(brace
l_int|0x59
comma
id|SONYPI_EVENT_BLUETOOTH_ON
)brace
comma
(brace
l_int|0x5a
comma
id|SONYPI_EVENT_BLUETOOTH_OFF
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible back button events */
DECL|variable|sonypi_backev
r_static
r_struct
id|sonypi_event
id|sonypi_backev
(braket
)braket
op_assign
(brace
(brace
l_int|0x20
comma
id|SONYPI_EVENT_BACK_PRESSED
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible help button events */
DECL|variable|sonypi_helpev
r_static
r_struct
id|sonypi_event
id|sonypi_helpev
(braket
)braket
op_assign
(brace
(brace
l_int|0x3b
comma
id|SONYPI_EVENT_HELP_PRESSED
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible lid events */
DECL|variable|sonypi_lidev
r_static
r_struct
id|sonypi_event
id|sonypi_lidev
(braket
)braket
op_assign
(brace
(brace
l_int|0x51
comma
id|SONYPI_EVENT_LID_CLOSED
)brace
comma
(brace
l_int|0x50
comma
id|SONYPI_EVENT_LID_OPENED
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible zoom events */
DECL|variable|sonypi_zoomev
r_static
r_struct
id|sonypi_event
id|sonypi_zoomev
(braket
)braket
op_assign
(brace
(brace
l_int|0x39
comma
id|SONYPI_EVENT_ZOOM_PRESSED
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible thumbphrase events */
DECL|variable|sonypi_thumbphraseev
r_static
r_struct
id|sonypi_event
id|sonypi_thumbphraseev
(braket
)braket
op_assign
(brace
(brace
l_int|0x3a
comma
id|SONYPI_EVENT_THUMBPHRASE_PRESSED
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible motioneye camera events */
DECL|variable|sonypi_meyeev
r_static
r_struct
id|sonypi_event
id|sonypi_meyeev
(braket
)braket
op_assign
(brace
(brace
l_int|0x00
comma
id|SONYPI_EVENT_MEYE_FACE
)brace
comma
(brace
l_int|0x01
comma
id|SONYPI_EVENT_MEYE_OPPOSITE
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible memorystick events */
DECL|variable|sonypi_memorystickev
r_static
r_struct
id|sonypi_event
id|sonypi_memorystickev
(braket
)braket
op_assign
(brace
(brace
l_int|0x53
comma
id|SONYPI_EVENT_MEMORYSTICK_INSERT
)brace
comma
(brace
l_int|0x54
comma
id|SONYPI_EVENT_MEMORYSTICK_EJECT
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* The set of possible battery events */
DECL|variable|sonypi_batteryev
r_static
r_struct
id|sonypi_event
id|sonypi_batteryev
(braket
)braket
op_assign
(brace
(brace
l_int|0x20
comma
id|SONYPI_EVENT_BATTERY_INSERT
)brace
comma
(brace
l_int|0x30
comma
id|SONYPI_EVENT_BATTERY_REMOVE
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|struct|sonypi_eventtypes
r_struct
id|sonypi_eventtypes
(brace
DECL|member|model
r_int
id|model
suffix:semicolon
DECL|member|data
id|u8
id|data
suffix:semicolon
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|events
r_struct
id|sonypi_event
op_star
id|events
suffix:semicolon
DECL|variable|sonypi_eventtypes
)brace
id|sonypi_eventtypes
(braket
)braket
op_assign
(brace
(brace
id|SONYPI_DEVICE_MODEL_TYPE1
comma
l_int|0
comma
l_int|0xffffffff
comma
id|sonypi_releaseev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE1
comma
l_int|0x70
comma
id|SONYPI_MEYE_MASK
comma
id|sonypi_meyeev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE1
comma
l_int|0x30
comma
id|SONYPI_LID_MASK
comma
id|sonypi_lidev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE1
comma
l_int|0x60
comma
id|SONYPI_CAPTURE_MASK
comma
id|sonypi_captureev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE1
comma
l_int|0x10
comma
id|SONYPI_JOGGER_MASK
comma
id|sonypi_joggerev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE1
comma
l_int|0x20
comma
id|SONYPI_FNKEY_MASK
comma
id|sonypi_fnkeyev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE1
comma
l_int|0x30
comma
id|SONYPI_BLUETOOTH_MASK
comma
id|sonypi_blueev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE1
comma
l_int|0x40
comma
id|SONYPI_PKEY_MASK
comma
id|sonypi_pkeyev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE1
comma
l_int|0x30
comma
id|SONYPI_MEMORYSTICK_MASK
comma
id|sonypi_memorystickev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE1
comma
l_int|0x40
comma
id|SONYPI_BATTERY_MASK
comma
id|sonypi_batteryev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0
comma
l_int|0xffffffff
comma
id|sonypi_releaseev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x38
comma
id|SONYPI_LID_MASK
comma
id|sonypi_lidev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x11
comma
id|SONYPI_JOGGER_MASK
comma
id|sonypi_joggerev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x61
comma
id|SONYPI_CAPTURE_MASK
comma
id|sonypi_captureev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x21
comma
id|SONYPI_FNKEY_MASK
comma
id|sonypi_fnkeyev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x31
comma
id|SONYPI_BLUETOOTH_MASK
comma
id|sonypi_blueev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x08
comma
id|SONYPI_PKEY_MASK
comma
id|sonypi_pkeyev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x11
comma
id|SONYPI_BACK_MASK
comma
id|sonypi_backev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x08
comma
id|SONYPI_HELP_MASK
comma
id|sonypi_helpev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x21
comma
id|SONYPI_ZOOM_MASK
comma
id|sonypi_zoomev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x20
comma
id|SONYPI_THUMBPHRASE_MASK
comma
id|sonypi_thumbphraseev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x31
comma
id|SONYPI_MEMORYSTICK_MASK
comma
id|sonypi_memorystickev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x41
comma
id|SONYPI_BATTERY_MASK
comma
id|sonypi_batteryev
)brace
comma
(brace
id|SONYPI_DEVICE_MODEL_TYPE2
comma
l_int|0x31
comma
id|SONYPI_PKEY_MASK
comma
id|sonypi_pkeyev
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|SONYPI_BUF_SIZE
mdefine_line|#define SONYPI_BUF_SIZE&t;128
DECL|struct|sonypi_queue
r_struct
id|sonypi_queue
(brace
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|s_lock
id|spinlock_t
id|s_lock
suffix:semicolon
DECL|member|proc_list
id|wait_queue_head_t
id|proc_list
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
id|SONYPI_BUF_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* We enable input subsystem event forwarding if the input &n; * subsystem is compiled in, but only if sonypi is not into the&n; * kernel and input as a module... */
macro_line|#if defined(CONFIG_INPUT) || defined(CONFIG_INPUT_MODULE)
macro_line|#if ! (defined(CONFIG_SONYPI) &amp;&amp; defined(CONFIG_INPUT_MODULE))
DECL|macro|SONYPI_USE_INPUT
mdefine_line|#define SONYPI_USE_INPUT
macro_line|#endif
macro_line|#endif
multiline_comment|/* The name of the Jog Dial for the input device drivers */
DECL|macro|SONYPI_INPUTNAME
mdefine_line|#define SONYPI_INPUTNAME&t;&quot;Sony VAIO Jog Dial&quot;
DECL|struct|sonypi_device
r_struct
id|sonypi_device
(brace
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|irq
id|u16
id|irq
suffix:semicolon
DECL|member|bits
id|u16
id|bits
suffix:semicolon
DECL|member|ioport1
id|u16
id|ioport1
suffix:semicolon
DECL|member|ioport2
id|u16
id|ioport2
suffix:semicolon
DECL|member|region_size
id|u16
id|region_size
suffix:semicolon
DECL|member|evtype_offset
id|u16
id|evtype_offset
suffix:semicolon
DECL|member|camera_power
r_int
id|camera_power
suffix:semicolon
DECL|member|bluetooth_power
r_int
id|bluetooth_power
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|queue
r_struct
id|sonypi_queue
id|queue
suffix:semicolon
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
DECL|member|model
r_int
id|model
suffix:semicolon
macro_line|#ifdef SONYPI_USE_INPUT
DECL|member|jog_dev
r_struct
id|input_dev
id|jog_dev
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PM
DECL|member|pm
r_struct
id|pm_dev
op_star
id|pm
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|ITERATIONS_LONG
mdefine_line|#define ITERATIONS_LONG&t;&t;10000
DECL|macro|ITERATIONS_SHORT
mdefine_line|#define ITERATIONS_SHORT&t;10
DECL|macro|wait_on_command
mdefine_line|#define wait_on_command(quiet, command, iterations) { &bslash;&n;&t;unsigned int n = iterations; &bslash;&n;&t;while (--n &amp;&amp; (command)) &bslash;&n;&t;&t;udelay(1); &bslash;&n;&t;if (!n &amp;&amp; (verbose || !quiet)) &bslash;&n;&t;&t;printk(KERN_WARNING &quot;sonypi command failed at %s : %s (line %d)&bslash;n&quot;, __FILE__, __FUNCTION__, __LINE__); &bslash;&n;}
macro_line|#ifdef CONFIG_ACPI
DECL|macro|SONYPI_ACPI_ACTIVE
mdefine_line|#define SONYPI_ACPI_ACTIVE (!acpi_disabled)
macro_line|#else
DECL|macro|SONYPI_ACPI_ACTIVE
mdefine_line|#define SONYPI_ACPI_ACTIVE 0
macro_line|#endif /* CONFIG_ACPI */
r_extern
r_int
id|verbose
suffix:semicolon
DECL|function|sonypi_ec_write
r_static
r_inline
r_int
id|sonypi_ec_write
c_func
(paren
id|u8
id|addr
comma
id|u8
id|value
)paren
(brace
macro_line|#ifdef CONFIG_ACPI_EC
r_if
c_cond
(paren
id|SONYPI_ACPI_ACTIVE
)paren
r_return
id|ec_write
c_func
(paren
id|addr
comma
id|value
)paren
suffix:semicolon
macro_line|#endif
id|wait_on_command
c_func
(paren
l_int|1
comma
id|inb_p
c_func
(paren
id|SONYPI_CST_IOPORT
)paren
op_amp
l_int|3
comma
id|ITERATIONS_LONG
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x81
comma
id|SONYPI_CST_IOPORT
)paren
suffix:semicolon
id|wait_on_command
c_func
(paren
l_int|0
comma
id|inb_p
c_func
(paren
id|SONYPI_CST_IOPORT
)paren
op_amp
l_int|2
comma
id|ITERATIONS_LONG
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|addr
comma
id|SONYPI_DATA_IOPORT
)paren
suffix:semicolon
id|wait_on_command
c_func
(paren
l_int|0
comma
id|inb_p
c_func
(paren
id|SONYPI_CST_IOPORT
)paren
op_amp
l_int|2
comma
id|ITERATIONS_LONG
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|value
comma
id|SONYPI_DATA_IOPORT
)paren
suffix:semicolon
id|wait_on_command
c_func
(paren
l_int|0
comma
id|inb_p
c_func
(paren
id|SONYPI_CST_IOPORT
)paren
op_amp
l_int|2
comma
id|ITERATIONS_LONG
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sonypi_ec_read
r_static
r_inline
r_int
id|sonypi_ec_read
c_func
(paren
id|u8
id|addr
comma
id|u8
op_star
id|value
)paren
(brace
macro_line|#ifdef CONFIG_ACPI_EC
r_if
c_cond
(paren
id|SONYPI_ACPI_ACTIVE
)paren
r_return
id|ec_read
c_func
(paren
id|addr
comma
id|value
)paren
suffix:semicolon
macro_line|#endif
id|wait_on_command
c_func
(paren
l_int|1
comma
id|inb_p
c_func
(paren
id|SONYPI_CST_IOPORT
)paren
op_amp
l_int|3
comma
id|ITERATIONS_LONG
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x80
comma
id|SONYPI_CST_IOPORT
)paren
suffix:semicolon
id|wait_on_command
c_func
(paren
l_int|0
comma
id|inb_p
c_func
(paren
id|SONYPI_CST_IOPORT
)paren
op_amp
l_int|2
comma
id|ITERATIONS_LONG
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|addr
comma
id|SONYPI_DATA_IOPORT
)paren
suffix:semicolon
id|wait_on_command
c_func
(paren
l_int|0
comma
id|inb_p
c_func
(paren
id|SONYPI_CST_IOPORT
)paren
op_amp
l_int|2
comma
id|ITERATIONS_LONG
)paren
suffix:semicolon
op_star
id|value
op_assign
id|inb_p
c_func
(paren
id|SONYPI_DATA_IOPORT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SONYPI_PRIV_H_ */
eof
