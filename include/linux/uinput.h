macro_line|#ifndef __UINPUT_H_
DECL|macro|__UINPUT_H_
mdefine_line|#define __UINPUT_H_
multiline_comment|/*&n; *  User level driver support for input subsystem&n; *&n; * Heavily based on evdev.c by Vojtech Pavlik&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Author: Aristeu Sergio Rozanski Filho &lt;aris@cathedrallabs.org&gt;&n; * &n; * Changes/Revisions:&n; *&t;0.2&t;16/10/2004 (Micah Dowty &lt;micah@navi.cx&gt;)&n; *&t;&t;- added force feedback support&n; *             - added UI_SET_PHYS&n; *&t;0.1&t;20/06/2002&n; *&t;&t;- first public version&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|UINPUT_MINOR
mdefine_line|#define UINPUT_MINOR&t;&t;223
DECL|macro|UINPUT_NAME
mdefine_line|#define UINPUT_NAME&t;&t;&quot;uinput&quot;
DECL|macro|UINPUT_BUFFER_SIZE
mdefine_line|#define UINPUT_BUFFER_SIZE&t;16
DECL|macro|UINPUT_NUM_REQUESTS
mdefine_line|#define UINPUT_NUM_REQUESTS&t;16
multiline_comment|/* state flags =&gt; bit index for {set|clear|test}_bit ops */
DECL|macro|UIST_CREATED
mdefine_line|#define UIST_CREATED&t;&t;0
DECL|struct|uinput_request
r_struct
id|uinput_request
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|code
r_int
id|code
suffix:semicolon
multiline_comment|/* UI_FF_UPLOAD, UI_FF_ERASE */
DECL|member|retval
r_int
id|retval
suffix:semicolon
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
DECL|member|completed
r_int
id|completed
suffix:semicolon
r_union
(brace
DECL|member|effect_id
r_int
id|effect_id
suffix:semicolon
DECL|member|effect
r_struct
id|ff_effect
op_star
id|effect
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|uinput_device
r_struct
id|uinput_device
(brace
DECL|member|dev
r_struct
id|input_dev
op_star
id|dev
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
DECL|member|ready
r_int
r_char
id|ready
comma
DECL|member|head
id|head
comma
DECL|member|tail
id|tail
suffix:semicolon
DECL|member|buff
r_struct
id|input_event
id|buff
(braket
id|UINPUT_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|requests
r_struct
id|uinput_request
op_star
id|requests
(braket
id|UINPUT_NUM_REQUESTS
)braket
suffix:semicolon
DECL|member|requests_waitq
id|wait_queue_head_t
id|requests_waitq
suffix:semicolon
DECL|member|requests_sem
r_struct
id|semaphore
id|requests_sem
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
DECL|struct|uinput_ff_upload
r_struct
id|uinput_ff_upload
(brace
DECL|member|request_id
r_int
id|request_id
suffix:semicolon
DECL|member|retval
r_int
id|retval
suffix:semicolon
DECL|member|effect
r_struct
id|ff_effect
id|effect
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|uinput_ff_erase
r_struct
id|uinput_ff_erase
(brace
DECL|member|request_id
r_int
id|request_id
suffix:semicolon
DECL|member|retval
r_int
id|retval
suffix:semicolon
DECL|member|effect_id
r_int
id|effect_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ioctl */
DECL|macro|UINPUT_IOCTL_BASE
mdefine_line|#define UINPUT_IOCTL_BASE&t;&squot;U&squot;
DECL|macro|UI_DEV_CREATE
mdefine_line|#define UI_DEV_CREATE&t;&t;_IO(UINPUT_IOCTL_BASE, 1)
DECL|macro|UI_DEV_DESTROY
mdefine_line|#define UI_DEV_DESTROY&t;&t;_IO(UINPUT_IOCTL_BASE, 2)
DECL|macro|UI_SET_EVBIT
mdefine_line|#define UI_SET_EVBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 100, int)
DECL|macro|UI_SET_KEYBIT
mdefine_line|#define UI_SET_KEYBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 101, int)
DECL|macro|UI_SET_RELBIT
mdefine_line|#define UI_SET_RELBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 102, int)
DECL|macro|UI_SET_ABSBIT
mdefine_line|#define UI_SET_ABSBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 103, int)
DECL|macro|UI_SET_MSCBIT
mdefine_line|#define UI_SET_MSCBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 104, int)
DECL|macro|UI_SET_LEDBIT
mdefine_line|#define UI_SET_LEDBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 105, int)
DECL|macro|UI_SET_SNDBIT
mdefine_line|#define UI_SET_SNDBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 106, int)
DECL|macro|UI_SET_FFBIT
mdefine_line|#define UI_SET_FFBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 107, int)
DECL|macro|UI_SET_PHYS
mdefine_line|#define UI_SET_PHYS&t;&t;_IOW(UINPUT_IOCTL_BASE, 108, char*)
DECL|macro|UI_BEGIN_FF_UPLOAD
mdefine_line|#define UI_BEGIN_FF_UPLOAD&t;_IOWR(UINPUT_IOCTL_BASE, 200, struct uinput_ff_upload)
DECL|macro|UI_END_FF_UPLOAD
mdefine_line|#define UI_END_FF_UPLOAD&t;_IOW(UINPUT_IOCTL_BASE, 201, struct uinput_ff_upload)
DECL|macro|UI_BEGIN_FF_ERASE
mdefine_line|#define UI_BEGIN_FF_ERASE&t;_IOWR(UINPUT_IOCTL_BASE, 202, struct uinput_ff_erase)
DECL|macro|UI_END_FF_ERASE
mdefine_line|#define UI_END_FF_ERASE&t;&t;_IOW(UINPUT_IOCTL_BASE, 203, struct uinput_ff_erase)
multiline_comment|/* To write a force-feedback-capable driver, the upload_effect&n; * and erase_effect callbacks in input_dev must be implemented.&n; * The uinput driver will generate a fake input event when one of&n; * these callbacks are invoked. The userspace code then uses&n; * ioctls to retrieve additional parameters and send the return code.&n; * The callback blocks until this return code is sent.&n; *&n; * The described callback mechanism is only used if EV_FF is set.&n; * Otherwise, default implementations of upload_effect and erase_effect&n; * are used.&n; *&n; * To implement upload_effect():&n; *   1. Wait for an event with type==EV_UINPUT and code==UI_FF_UPLOAD.&n; *      A request ID will be given in &squot;value&squot;.&n; *   2. Allocate a uinput_ff_upload struct, fill in request_id with&n; *      the &squot;value&squot; from the EV_UINPUT event.&n; *   3. Issue a UI_BEGIN_FF_UPLOAD ioctl, giving it the&n; *      uinput_ff_upload struct. It will be filled in with the&n; *      ff_effect passed to upload_effect().&n; *   4. Perform the effect upload, and place the modified ff_effect&n; *      and a return code back into the uinput_ff_upload struct.&n; *   5. Issue a UI_END_FF_UPLOAD ioctl, also giving it the&n; *      uinput_ff_upload_effect struct. This will complete execution&n; *      of our upload_effect() handler.&n; *&n; * To implement erase_effect():&n; *   1. Wait for an event with type==EV_UINPUT and code==UI_FF_ERASE.&n; *      A request ID will be given in &squot;value&squot;.&n; *   2. Allocate a uinput_ff_erase struct, fill in request_id with&n; *      the &squot;value&squot; from the EV_UINPUT event.&n; *   3. Issue a UI_BEGIN_FF_ERASE ioctl, giving it the&n; *      uinput_ff_erase struct. It will be filled in with the&n; *      effect ID passed to erase_effect().&n; *   4. Perform the effect erasure, and place a return code back&n; *      into the uinput_ff_erase struct.&n; *      and a return code back into the uinput_ff_erase struct.&n; *   5. Issue a UI_END_FF_ERASE ioctl, also giving it the&n; *      uinput_ff_erase_effect struct. This will complete execution&n; *      of our erase_effect() handler.&n; */
multiline_comment|/* This is the new event type, used only by uinput.&n; * &squot;code&squot; is UI_FF_UPLOAD or UI_FF_ERASE, and &squot;value&squot;&n; * is the unique request ID. This number was picked&n; * arbitrarily, above EV_MAX (since the input system&n; * never sees it) but in the range of a 16-bit int.&n; */
DECL|macro|EV_UINPUT
mdefine_line|#define EV_UINPUT&t;&t;0x0101
DECL|macro|UI_FF_UPLOAD
mdefine_line|#define UI_FF_UPLOAD&t;&t;1
DECL|macro|UI_FF_ERASE
mdefine_line|#define UI_FF_ERASE&t;&t;2
macro_line|#ifndef NBITS
DECL|macro|NBITS
mdefine_line|#define NBITS(x) ((((x)-1)/(sizeof(long)*8))+1)
macro_line|#endif&t;/* NBITS */
DECL|macro|UINPUT_MAX_NAME_SIZE
mdefine_line|#define UINPUT_MAX_NAME_SIZE&t;80
DECL|struct|uinput_user_dev
r_struct
id|uinput_user_dev
(brace
DECL|member|name
r_char
id|name
(braket
id|UINPUT_MAX_NAME_SIZE
)braket
suffix:semicolon
DECL|member|id
r_struct
id|input_id
id|id
suffix:semicolon
DECL|member|ff_effects_max
r_int
id|ff_effects_max
suffix:semicolon
DECL|member|absmax
r_int
id|absmax
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|absmin
r_int
id|absmin
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|absfuzz
r_int
id|absfuzz
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|absflat
r_int
id|absflat
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* __UINPUT_H_ */
eof
