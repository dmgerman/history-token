multiline_comment|/*&n; * $Id: iforce.h,v 1.12 2002/06/09 11:08:04 jdeneux Exp $&n; *&n; *  Copyright (c) 2000-2002 Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&n; *  Copyright (c) 2001-2002 Johann Deneux &lt;deneux@ifrance.com&gt;&n; *&n; *  USB/RS232 I-Force joysticks and wheels.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/circ_buf.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/* FF: This module provides arbitrary resource management routines.&n; * I use it to manage the device&squot;s memory.&n; * Despite the name of this module, I am *not* going to access the ioports.&n; */
macro_line|#include &lt;linux/ioport.h&gt;
DECL|macro|IFORCE_MAX_LENGTH
mdefine_line|#define IFORCE_MAX_LENGTH&t;16
macro_line|#if defined(CONFIG_JOYSTICK_IFORCE_232)
DECL|macro|IFORCE_232
mdefine_line|#define IFORCE_232&t;1
macro_line|#endif
macro_line|#if defined(CONFIG_JOYSTICK_IFORCE_USB)
DECL|macro|IFORCE_USB
mdefine_line|#define IFORCE_USB&t;2
macro_line|#endif
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|TRUE
mdefine_line|#define TRUE 1
DECL|macro|FF_EFFECTS_MAX
mdefine_line|#define FF_EFFECTS_MAX&t;32
multiline_comment|/* Each force feedback effect is made of one core effect, which can be&n; * associated to at most to effect modifiers&n; */
DECL|macro|FF_MOD1_IS_USED
mdefine_line|#define FF_MOD1_IS_USED&t;&t;0
DECL|macro|FF_MOD2_IS_USED
mdefine_line|#define FF_MOD2_IS_USED&t;&t;1
DECL|macro|FF_CORE_IS_USED
mdefine_line|#define FF_CORE_IS_USED&t;&t;2
DECL|macro|FF_CORE_IS_PLAYED
mdefine_line|#define FF_CORE_IS_PLAYED&t;3&t;/* Effect is currently being played */
DECL|macro|FF_CORE_SHOULD_PLAY
mdefine_line|#define FF_CORE_SHOULD_PLAY&t;4&t;/* User wants the effect to be played */
DECL|macro|FF_CORE_UPDATE
mdefine_line|#define FF_CORE_UPDATE&t;&t;5&t;/* Effect is being updated */
DECL|macro|FF_MODCORE_MAX
mdefine_line|#define FF_MODCORE_MAX&t;&t;5
DECL|macro|CHECK_OWNERSHIP
mdefine_line|#define CHECK_OWNERSHIP(i, iforce)&t;&bslash;&n;&t;((i) &lt; FF_EFFECTS_MAX &amp;&amp; i &gt;= 0 &amp;&amp; &bslash;&n;&t;test_bit(FF_CORE_IS_USED, (iforce)-&gt;core_effects[(i)].flags) &amp;&amp; &bslash;&n;&t;(current-&gt;pid == 0 || &bslash;&n;&t;(iforce)-&gt;core_effects[(i)].owner == current-&gt;pid))
DECL|struct|iforce_core_effect
r_struct
id|iforce_core_effect
(brace
multiline_comment|/* Information about where modifiers are stored in the device&squot;s memory */
DECL|member|mod1_chunk
r_struct
id|resource
id|mod1_chunk
suffix:semicolon
DECL|member|mod2_chunk
r_struct
id|resource
id|mod2_chunk
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
(braket
id|NBITS
c_func
(paren
id|FF_MODCORE_MAX
)paren
)braket
suffix:semicolon
DECL|member|owner
id|pid_t
id|owner
suffix:semicolon
multiline_comment|/* Used to keep track of parameters of an effect. They are needed&n;&t; * to know what parts of an effect changed in an update operation.&n;&t; * We try to send only parameter packets if possible, as sending&n;&t; * effect parameter requires the effect to be stoped and restarted&n;&t; */
DECL|member|effect
r_struct
id|ff_effect
id|effect
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FF_CMD_EFFECT
mdefine_line|#define FF_CMD_EFFECT&t;&t;0x010e
DECL|macro|FF_CMD_ENVELOPE
mdefine_line|#define FF_CMD_ENVELOPE&t;&t;0x0208
DECL|macro|FF_CMD_MAGNITUDE
mdefine_line|#define FF_CMD_MAGNITUDE&t;0x0303
DECL|macro|FF_CMD_PERIOD
mdefine_line|#define FF_CMD_PERIOD&t;&t;0x0407
DECL|macro|FF_CMD_CONDITION
mdefine_line|#define FF_CMD_CONDITION&t;0x050a
DECL|macro|FF_CMD_AUTOCENTER
mdefine_line|#define FF_CMD_AUTOCENTER&t;0x4002
DECL|macro|FF_CMD_PLAY
mdefine_line|#define FF_CMD_PLAY&t;&t;0x4103
DECL|macro|FF_CMD_ENABLE
mdefine_line|#define FF_CMD_ENABLE&t;&t;0x4201
DECL|macro|FF_CMD_GAIN
mdefine_line|#define FF_CMD_GAIN&t;&t;0x4301
DECL|macro|FF_CMD_QUERY
mdefine_line|#define FF_CMD_QUERY&t;&t;0xff01
multiline_comment|/* Buffer for async write */
DECL|macro|XMIT_SIZE
mdefine_line|#define XMIT_SIZE&t;&t;256
DECL|macro|XMIT_INC
mdefine_line|#define XMIT_INC(var, n)&t;(var)+=n; (var)&amp;= XMIT_SIZE -1
multiline_comment|/* iforce::xmit_flags */
DECL|macro|IFORCE_XMIT_RUNNING
mdefine_line|#define IFORCE_XMIT_RUNNING&t;0
DECL|macro|IFORCE_XMIT_AGAIN
mdefine_line|#define IFORCE_XMIT_AGAIN&t;1
DECL|struct|iforce_device
r_struct
id|iforce_device
(brace
DECL|member|idvendor
id|u16
id|idvendor
suffix:semicolon
DECL|member|idproduct
id|u16
id|idproduct
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|btn
r_int
r_int
op_star
id|btn
suffix:semicolon
DECL|member|abs
r_int
r_int
op_star
id|abs
suffix:semicolon
DECL|member|ff
r_int
r_int
op_star
id|ff
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|iforce
r_struct
id|iforce
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
multiline_comment|/* Input device interface */
DECL|member|type
r_struct
id|iforce_device
op_star
id|type
suffix:semicolon
DECL|member|bus
r_int
id|bus
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
id|IFORCE_MAX_LENGTH
)braket
suffix:semicolon
DECL|member|edata
r_int
r_char
id|edata
(braket
id|IFORCE_MAX_LENGTH
)braket
suffix:semicolon
DECL|member|ecmd
id|u16
id|ecmd
suffix:semicolon
DECL|member|expect_packet
id|u16
id|expect_packet
suffix:semicolon
macro_line|#ifdef IFORCE_232
DECL|member|serio
r_struct
id|serio
op_star
id|serio
suffix:semicolon
multiline_comment|/* RS232 transfer */
DECL|member|idx
DECL|member|pkt
DECL|member|len
DECL|member|id
r_int
id|idx
comma
id|pkt
comma
id|len
comma
id|id
suffix:semicolon
DECL|member|csum
r_int
r_char
id|csum
suffix:semicolon
macro_line|#endif
macro_line|#ifdef IFORCE_USB
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
multiline_comment|/* USB transfer */
DECL|member|irq
DECL|member|out
DECL|member|ctrl
r_struct
id|urb
op_star
id|irq
comma
op_star
id|out
comma
op_star
id|ctrl
suffix:semicolon
DECL|member|cr
r_struct
id|usb_ctrlrequest
id|cr
suffix:semicolon
macro_line|#endif
DECL|member|xmit_lock
id|spinlock_t
id|xmit_lock
suffix:semicolon
multiline_comment|/* Buffer used for asynchronous sending of bytes to the device */
DECL|member|xmit
r_struct
id|circ_buf
id|xmit
suffix:semicolon
DECL|member|xmit_data
r_int
r_char
id|xmit_data
(braket
id|XMIT_SIZE
)braket
suffix:semicolon
DECL|member|xmit_flags
r_int
id|xmit_flags
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Force Feedback */
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|device_memory
r_struct
id|resource
id|device_memory
suffix:semicolon
DECL|member|core_effects
r_struct
id|iforce_core_effect
id|core_effects
(braket
id|FF_EFFECTS_MAX
)braket
suffix:semicolon
DECL|member|mem_mutex
r_struct
id|semaphore
id|mem_mutex
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Get hi and low bytes of a 16-bits int */
DECL|macro|HI
mdefine_line|#define HI(a)&t;((unsigned char)((a) &gt;&gt; 8))
DECL|macro|LO
mdefine_line|#define LO(a)&t;((unsigned char)((a) &amp; 0xff))
multiline_comment|/* For many parameters, it seems that 0x80 is a special value that should&n; * be avoided. Instead, we replace this value by 0x7f&n; */
DECL|macro|HIFIX80
mdefine_line|#define HIFIX80(a) ((unsigned char)(((a)&lt;0? (a)+255 : (a))&gt;&gt;8))
multiline_comment|/* Encode a time value */
DECL|macro|TIME_SCALE
mdefine_line|#define TIME_SCALE(a)&t;(a)
multiline_comment|/* Public functions */
multiline_comment|/* iforce-serio.c */
r_void
id|iforce_serial_xmit
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
)paren
suffix:semicolon
multiline_comment|/* iforce-usb.c */
r_void
id|iforce_usb_xmit
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
)paren
suffix:semicolon
r_void
id|iforce_usb_delete
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
)paren
suffix:semicolon
multiline_comment|/* iforce-main.c */
r_int
id|iforce_init_device
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
)paren
suffix:semicolon
r_void
id|iforce_delete_device
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
)paren
suffix:semicolon
multiline_comment|/* iforce-packets.c */
r_int
id|iforce_control_playback
c_func
(paren
r_struct
id|iforce
op_star
comma
id|u16
id|id
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|iforce_process_packet
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
comma
id|u16
id|cmd
comma
r_int
r_char
op_star
id|data
)paren
suffix:semicolon
r_int
id|iforce_send_packet
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
comma
id|u16
id|cmd
comma
r_int
r_char
op_star
id|data
)paren
suffix:semicolon
r_void
id|iforce_dump_packet
c_func
(paren
r_char
op_star
id|msg
comma
id|u16
id|cmd
comma
r_int
r_char
op_star
id|data
)paren
suffix:semicolon
r_int
id|iforce_get_id_packet
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
comma
r_char
op_star
id|packet
)paren
suffix:semicolon
multiline_comment|/* iforce-ff.c */
r_int
id|iforce_upload_periodic
c_func
(paren
r_struct
id|iforce
op_star
comma
r_struct
id|ff_effect
op_star
comma
r_int
id|is_update
)paren
suffix:semicolon
r_int
id|iforce_upload_constant
c_func
(paren
r_struct
id|iforce
op_star
comma
r_struct
id|ff_effect
op_star
comma
r_int
id|is_update
)paren
suffix:semicolon
r_int
id|iforce_upload_condition
c_func
(paren
r_struct
id|iforce
op_star
comma
r_struct
id|ff_effect
op_star
comma
r_int
id|is_update
)paren
suffix:semicolon
multiline_comment|/* Public variables */
r_extern
r_struct
id|serio_dev
id|iforce_serio_dev
suffix:semicolon
r_extern
r_struct
id|usb_driver
id|iforce_usb_driver
suffix:semicolon
eof
