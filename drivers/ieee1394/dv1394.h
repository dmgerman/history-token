multiline_comment|/*&n; * dv1394.h - DV input/output over IEEE 1394 on OHCI chips&n; *   Copyright (C)2001 Daniel Maas &lt;dmaas@dcine.com&gt;&n; *     receive, proc_fs by Dan Dennedy &lt;dan@dennedy.org&gt;&n; *&n; * based on:&n; *   video1394.h - driver for OHCI 1394 boards&n; *   Copyright (C)1999,2000 Sebastien Rougeaux &lt;sebastien.rougeaux@anu.edu.au&gt;&n; *                          Peter Schlaile &lt;udbz@rz.uni-karlsruhe.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ifndef _DV_1394_H
DECL|macro|_DV_1394_H
mdefine_line|#define _DV_1394_H
multiline_comment|/* This is the public user-space interface. Try not to break it. */
DECL|macro|DV1394_API_VERSION
mdefine_line|#define DV1394_API_VERSION 0x20011127
multiline_comment|/* ********************&n;   **                **&n;   **   DV1394 API   **&n;   **                **&n;   ********************&n;&n;   There are two methods of operating the DV1394 DV output device.&n;&n;   1)&n;&n;   The simplest is an interface based on write(): simply write&n;   full DV frames of data to the device, and they will be transmitted&n;   as quickly as possible. The FD may be set for non-blocking I/O,&n;   in which case you can use select() or poll() to wait for output&n;   buffer space.&n;&n;   To set the DV output parameters (e.g. whether you want NTSC or PAL&n;   video), use the DV1394_INIT ioctl, passing in the parameters you&n;   want in a struct dv1394_init.&n; &n;   Example 1:&n;         To play a raw .DV file:   cat foo.DV &gt; /dev/dv1394&n;&t; (cat will use write() internally)&n;&n;   Example 2:&n;           static struct dv1394_init init = {&n;&t;      0x63,        (broadcast channel)&n;              4,           (four-frame ringbuffer)&n;&t;      DV1394_NTSC, (send NTSC video)&n;&t;      0, 0         (default empty packet rate)&n;           }&n;&n;&t;   ioctl(fd, DV1394_INIT, &amp;init);&n;&n;&t;   while(1) {&n;&t;          read( &lt;a raw DV file&gt;, buf, DV1394_NTSC_FRAME_SIZE );&n;&t;&t;  write( &lt;the dv1394 FD&gt;, buf, DV1394_NTSC_FRAME_SIZE );&n;           }&n;&n;   2)&n;&n;   For more control over buffering, and to avoid unnecessary copies&n;   of the DV data, you can use the more sophisticated the mmap() interface. &n;   First, call the DV1394_INIT ioctl to specify your parameters, &n;   including the number of frames in the ringbuffer. Then, calling mmap() &n;   on the dv1394 device will give you direct access to the ringbuffer&n;   from which the DV card reads your frame data.&n;&n;   The ringbuffer is simply one large, contiguous region of memory&n;   containing two or more frames of packed DV data. Each frame of DV data&n;   is 120000 bytes (NTSC) or 144000 bytes (PAL).&n;&n;   Fill one or more frames in the ringbuffer, then use the DV1394_SUBMIT_FRAMES&n;   ioctl to begin I/O. You can use either the DV1394_WAIT_FRAMES ioctl&n;   or select()/poll() to wait until the frames are transmitted. Next, you&squot;ll&n;   need to call the DV1394_GET_STATUS ioctl to determine which ringbuffer&n;   frames are clear (ready to be filled with new DV data). Finally, use&n;   DV1394_SUBMIT_FRAMES again to send the new data to the DV output.&n;&n;&n;   Example: here is what a four-frame ringbuffer might look like&n;            during DV transmission:&n;&n;&n;         frame 0   frame 1   frame 2   frame 3&n;&n;&t;*--------------------------------------*&n;        | CLEAR   | DV data | DV data | CLEAR  |&n;        *--------------------------------------*&n;                   &lt;ACTIVE&gt; &n;&n;&t;transmission goes in this direction ---&gt;&gt;&gt;&n;&n;&n;   The DV hardware is currently transmitting the data in frame 1.&n;   Once frame 1 is finished, it will automatically transmit frame 2.&n;   (if frame 2 finishes before frame 3 is submitted, the device&n;   will continue to transmit frame 2, and will increase the dropped_frames&n;   counter each time it repeats the transmission).&n;&n; &n;   If you called DV1394_GET_STATUS at this instant, you would&n;   receive the following values:&n;   &n;                  n_frames          = 4&n;&t;&t;  active_frame      = 1&n;&t;&t;  first_clear_frame = 3&n;&t;&t;  n_clear_frames    = 2&n;&n;   At this point, you should write new DV data into frame 3 and optionally&n;   frame 0. Then call DV1394_SUBMIT_FRAMES to inform the device that&n;   it may transmit the new frames.&n;&n;*/
multiline_comment|/* maximum number of frames in the ringbuffer */
DECL|macro|DV1394_MAX_FRAMES
mdefine_line|#define DV1394_MAX_FRAMES 32
multiline_comment|/* number of *full* isochronous packets per DV frame */
DECL|macro|DV1394_NTSC_PACKETS_PER_FRAME
mdefine_line|#define DV1394_NTSC_PACKETS_PER_FRAME 250
DECL|macro|DV1394_PAL_PACKETS_PER_FRAME
mdefine_line|#define DV1394_PAL_PACKETS_PER_FRAME  300
multiline_comment|/* size of one frame&squot;s worth of DV data, in bytes */
DECL|macro|DV1394_NTSC_FRAME_SIZE
mdefine_line|#define DV1394_NTSC_FRAME_SIZE (480 * DV1394_NTSC_PACKETS_PER_FRAME)
DECL|macro|DV1394_PAL_FRAME_SIZE
mdefine_line|#define DV1394_PAL_FRAME_SIZE  (480 * DV1394_PAL_PACKETS_PER_FRAME)
multiline_comment|/* ioctl() commands */
r_enum
(brace
multiline_comment|/* I don&squot;t like using 0 as a valid ioctl() */
DECL|enumerator|DV1394_INVALID
id|DV1394_INVALID
op_assign
l_int|0
comma
multiline_comment|/* get the driver ready to transmit video.&n;&t;   pass a struct dv1394_init* as the parameter (see below),&n;&t;   or NULL to get default parameters */
DECL|enumerator|DV1394_INIT
id|DV1394_INIT
comma
multiline_comment|/* stop transmitting video and free the ringbuffer */
DECL|enumerator|DV1394_SHUTDOWN
id|DV1394_SHUTDOWN
comma
multiline_comment|/* submit N new frames to be transmitted, where&n;&t;   the index of the first new frame is first_clear_buffer,&n;&t;   and the index of the last new frame is&n;&t;   (first_clear_buffer + N) % n_frames */
DECL|enumerator|DV1394_SUBMIT_FRAMES
id|DV1394_SUBMIT_FRAMES
comma
multiline_comment|/* block until N buffers are clear (pass N as the parameter)&n;&t;   Because we re-transmit the last frame on underrun, there&n;&t;   will at most be n_frames - 1 clear frames at any time */
DECL|enumerator|DV1394_WAIT_FRAMES
id|DV1394_WAIT_FRAMES
comma
multiline_comment|/* capture new frames that have been received, where&n;&t;   the index of the first new frame is first_clear_buffer,&n;&t;   and the index of the last new frame is&n;&t;   (first_clear_buffer + N) % n_frames */
DECL|enumerator|DV1394_RECEIVE_FRAMES
id|DV1394_RECEIVE_FRAMES
comma
DECL|enumerator|DV1394_START_RECEIVE
id|DV1394_START_RECEIVE
comma
multiline_comment|/* pass a struct dv1394_status* as the parameter (see below) */
DECL|enumerator|DV1394_GET_STATUS
id|DV1394_GET_STATUS
comma
)brace
suffix:semicolon
DECL|enum|pal_or_ntsc
r_enum
id|pal_or_ntsc
(brace
DECL|enumerator|DV1394_NTSC
id|DV1394_NTSC
op_assign
l_int|0
comma
DECL|enumerator|DV1394_PAL
id|DV1394_PAL
)brace
suffix:semicolon
multiline_comment|/* this is the argument to DV1394_INIT */
DECL|struct|dv1394_init
r_struct
id|dv1394_init
(brace
multiline_comment|/* DV1394_API_VERSION */
DECL|member|api_version
r_int
r_int
id|api_version
suffix:semicolon
multiline_comment|/* isochronous transmission channel to use */
DECL|member|channel
r_int
r_int
id|channel
suffix:semicolon
multiline_comment|/* number of frames in the ringbuffer. Must be at least 2&n;&t;   and at most DV1394_MAX_FRAMES. */
DECL|member|n_frames
r_int
r_int
id|n_frames
suffix:semicolon
multiline_comment|/* send/receive PAL or NTSC video format */
DECL|member|format
r_enum
id|pal_or_ntsc
id|format
suffix:semicolon
multiline_comment|/* the following are used only for transmission */
multiline_comment|/* set these to zero unless you want a&n;&t;   non-default empty packet rate (see below) */
DECL|member|cip_n
r_int
r_int
id|cip_n
suffix:semicolon
DECL|member|cip_d
r_int
r_int
id|cip_d
suffix:semicolon
multiline_comment|/* set this to zero unless you want a&n;&t;   non-default SYT cycle offset (default = 3 cycles) */
DECL|member|syt_offset
r_int
r_int
id|syt_offset
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Q: What are cip_n and cip_d? */
multiline_comment|/*&n;  A: DV video streams do not utilize 100% of the potential bandwidth offered&n;  by IEEE 1394 (FireWire). To achieve the correct rate of data transmission,&n;  DV devices must periodically insert empty packets into the 1394 data stream.&n;  Typically there is one empty packet per 14-16 data-carrying packets.&n;&n;  Some DV devices will accept a wide range of empty packet rates, while others&n;  require a precise rate. If the dv1394 driver produces empty packets at&n;  a rate that your device does not accept, you may see ugly patterns on the&n;  DV output, or even no output at all.&n;&n;  The default empty packet insertion rate seems to work for many people; if&n;  your DV output is stable, you can simply ignore this discussion. However,&n;  we have exposed the empty packet rate as a parameter to support devices that&n;  do not work with the default rate. &n;&n;  The decision to insert an empty packet is made with a numerator/denominator&n;  algorithm. Empty packets are produced at an average rate of CIP_N / CIP_D.&n;  You can alter the empty packet rate by passing non-zero values for cip_n&n;  and cip_d to the INIT ioctl.&n;  &n; */
DECL|struct|dv1394_status
r_struct
id|dv1394_status
(brace
multiline_comment|/* this embedded init struct returns the current dv1394&n;&t;   parameters in use */
DECL|member|init
r_struct
id|dv1394_init
id|init
suffix:semicolon
multiline_comment|/* the ringbuffer frame that is currently being&n;&t;   displayed. (-1 if the device is not transmitting anything) */
DECL|member|active_frame
r_int
id|active_frame
suffix:semicolon
multiline_comment|/* index of the first buffer (ahead of active_frame) that&n;&t;   is ready to be filled with data */
DECL|member|first_clear_frame
r_int
r_int
id|first_clear_frame
suffix:semicolon
multiline_comment|/* how many buffers, including first_clear_buffer, are&n;&t;   ready to be filled with data */
DECL|member|n_clear_frames
r_int
r_int
id|n_clear_frames
suffix:semicolon
multiline_comment|/* how many times the DV output has underflowed&n;&t;   since the last call to DV1394_GET_STATUS */
DECL|member|dropped_frames
r_int
r_int
id|dropped_frames
suffix:semicolon
multiline_comment|/* N.B. The dropped_frames counter is only a lower bound on the actual&n;&t;   number of dropped frames, with the special case that if dropped_frames&n;&t;   is zero, then it is guaranteed that NO frames have been dropped&n;&t;   since the last call to DV1394_GET_STATUS.&n;&t;*/
)brace
suffix:semicolon
macro_line|#endif /* _DV_1394_H */
eof
