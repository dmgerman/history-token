multiline_comment|/* Base file for all ieee1394 ioctl&squot;s. Linux-1394 has allocated base &squot;#&squot;&n; * with a range of 0x00-0x3f. */
macro_line|#ifndef __IEEE1394_IOCTL_H
DECL|macro|__IEEE1394_IOCTL_H
mdefine_line|#define __IEEE1394_IOCTL_H
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* AMDTP Gets 6 */
DECL|macro|AMDTP_IOC_CHANNEL
mdefine_line|#define AMDTP_IOC_CHANNEL&t;_IOW(&squot;#&squot;, 0x00, struct amdtp_ioctl)
DECL|macro|AMDTP_IOC_PLUG
mdefine_line|#define AMDTP_IOC_PLUG&t;&t;_IOW(&squot;#&squot;, 0x01, struct amdtp_ioctl)
DECL|macro|AMDTP_IOC_PING
mdefine_line|#define AMDTP_IOC_PING&t;&t;_IOW(&squot;#&squot;, 0x02, struct amdtp_ioctl)
DECL|macro|AMDTP_IOC_ZAP
mdefine_line|#define AMDTP_IOC_ZAP&t;&t;_IO (&squot;#&squot;, 0x03)
multiline_comment|/* DV1394 Gets 10 */
multiline_comment|/* Get the driver ready to transmit video.  pass a struct dv1394_init* as&n; * the parameter (see below), or NULL to get default parameters */
DECL|macro|DV1394_IOC_INIT
mdefine_line|#define DV1394_IOC_INIT&t;&t;&t;_IOW(&squot;#&squot;, 0x06, struct dv1394_init)
multiline_comment|/* Stop transmitting video and free the ringbuffer */
DECL|macro|DV1394_IOC_SHUTDOWN
mdefine_line|#define DV1394_IOC_SHUTDOWN&t;&t;_IO (&squot;#&squot;, 0x07)
multiline_comment|/* Submit N new frames to be transmitted, where the index of the first new&n; * frame is first_clear_buffer, and the index of the last new frame is&n; * (first_clear_buffer + N) % n_frames */
DECL|macro|DV1394_IOC_SUBMIT_FRAMES
mdefine_line|#define DV1394_IOC_SUBMIT_FRAMES&t;_IO (&squot;#&squot;, 0x08)
multiline_comment|/* Block until N buffers are clear (pass N as the parameter) Because we&n; * re-transmit the last frame on underrun, there will at most be n_frames&n; * - 1 clear frames at any time */
DECL|macro|DV1394_IOC_WAIT_FRAMES
mdefine_line|#define DV1394_IOC_WAIT_FRAMES&t;&t;_IO (&squot;#&squot;, 0x09)
multiline_comment|/* Capture new frames that have been received, where the index of the&n; * first new frame is first_clear_buffer, and the index of the last new&n; * frame is (first_clear_buffer + N) % n_frames */
DECL|macro|DV1394_IOC_RECEIVE_FRAMES
mdefine_line|#define DV1394_IOC_RECEIVE_FRAMES&t;_IO (&squot;#&squot;, 0x0a)
multiline_comment|/* Tell card to start receiving DMA */
DECL|macro|DV1394_IOC_START_RECEIVE
mdefine_line|#define DV1394_IOC_START_RECEIVE&t;_IO (&squot;#&squot;, 0x0b)
multiline_comment|/* Pass a struct dv1394_status* as the parameter */
DECL|macro|DV1394_IOC_GET_STATUS
mdefine_line|#define DV1394_IOC_GET_STATUS&t;&t;_IOR(&squot;#&squot;, 0x0c, struct dv1394_status)
multiline_comment|/* Video1394 Gets 10 */
DECL|macro|VIDEO1394_IOC_LISTEN_CHANNEL
mdefine_line|#define VIDEO1394_IOC_LISTEN_CHANNEL&t;&t;&bslash;&n;&t;_IOWR(&squot;#&squot;, 0x10, struct video1394_mmap)
DECL|macro|VIDEO1394_IOC_UNLISTEN_CHANNEL
mdefine_line|#define VIDEO1394_IOC_UNLISTEN_CHANNEL&t;&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x11, int)
DECL|macro|VIDEO1394_IOC_LISTEN_QUEUE_BUFFER
mdefine_line|#define VIDEO1394_IOC_LISTEN_QUEUE_BUFFER&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x12, struct video1394_wait)
DECL|macro|VIDEO1394_IOC_LISTEN_WAIT_BUFFER
mdefine_line|#define VIDEO1394_IOC_LISTEN_WAIT_BUFFER&t;&bslash;&n;&t;_IOWR(&squot;#&squot;, 0x13, struct video1394_wait)
DECL|macro|VIDEO1394_IOC_TALK_CHANNEL
mdefine_line|#define VIDEO1394_IOC_TALK_CHANNEL&t;&t;&bslash;&n;&t;_IOWR(&squot;#&squot;, 0x14, struct video1394_mmap)
DECL|macro|VIDEO1394_IOC_UNTALK_CHANNEL
mdefine_line|#define VIDEO1394_IOC_UNTALK_CHANNEL&t;&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x15, int)
DECL|macro|VIDEO1394_IOC_TALK_QUEUE_BUFFER
mdefine_line|#define VIDEO1394_IOC_TALK_QUEUE_BUFFER &t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x16, sizeof (struct video1394_wait) + &bslash;&n;&t;&t;sizeof (struct video1394_queue_variable))
DECL|macro|VIDEO1394_IOC_TALK_WAIT_BUFFER
mdefine_line|#define VIDEO1394_IOC_TALK_WAIT_BUFFER&t;&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x17, struct video1394_wait)
DECL|macro|VIDEO1394_IOC_LISTEN_POLL_BUFFER
mdefine_line|#define VIDEO1394_IOC_LISTEN_POLL_BUFFER&t;&bslash;&n;&t;_IOWR(&squot;#&squot;, 0x18, struct video1394_wait)
multiline_comment|/* Raw1394&squot;s ISO interface */
DECL|macro|RAW1394_IOC_ISO_XMIT_INIT
mdefine_line|#define RAW1394_IOC_ISO_XMIT_INIT&t;&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x1a, struct raw1394_iso_status)
DECL|macro|RAW1394_IOC_ISO_RECV_INIT
mdefine_line|#define RAW1394_IOC_ISO_RECV_INIT&t;&t;&bslash;&n;&t;_IOWR(&squot;#&squot;, 0x1b, struct raw1394_iso_status)
DECL|macro|RAW1394_IOC_ISO_RECV_START
mdefine_line|#define RAW1394_IOC_ISO_RECV_START&t;&t;&bslash;&n;&t;_IOC (_IOC_WRITE, &squot;#&squot;, 0x1c, sizeof(int) * 3)
DECL|macro|RAW1394_IOC_ISO_XMIT_START
mdefine_line|#define RAW1394_IOC_ISO_XMIT_START&t;&t;&bslash;&n;&t;_IOC (_IOC_WRITE, &squot;#&squot;, 0x1d, sizeof(int) * 2)
DECL|macro|RAW1394_IOC_ISO_XMIT_RECV_STOP
mdefine_line|#define RAW1394_IOC_ISO_XMIT_RECV_STOP&t;&t;&bslash;&n;&t;_IO  (&squot;#&squot;, 0x1e)
DECL|macro|RAW1394_IOC_ISO_GET_STATUS
mdefine_line|#define RAW1394_IOC_ISO_GET_STATUS&t;&t;&bslash;&n;&t;_IOR (&squot;#&squot;, 0x1f, struct raw1394_iso_status)
DECL|macro|RAW1394_IOC_ISO_SHUTDOWN
mdefine_line|#define RAW1394_IOC_ISO_SHUTDOWN&t;&t;&bslash;&n;&t;_IO  (&squot;#&squot;, 0x20)
DECL|macro|RAW1394_IOC_ISO_QUEUE_ACTIVITY
mdefine_line|#define RAW1394_IOC_ISO_QUEUE_ACTIVITY&t;&t;&bslash;&n;&t;_IO  (&squot;#&squot;, 0x21)
DECL|macro|RAW1394_IOC_ISO_RECV_LISTEN_CHANNEL
mdefine_line|#define RAW1394_IOC_ISO_RECV_LISTEN_CHANNEL&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x22, unsigned char)
DECL|macro|RAW1394_IOC_ISO_RECV_UNLISTEN_CHANNEL
mdefine_line|#define RAW1394_IOC_ISO_RECV_UNLISTEN_CHANNEL&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x23, unsigned char)
DECL|macro|RAW1394_IOC_ISO_RECV_SET_CHANNEL_MASK
mdefine_line|#define RAW1394_IOC_ISO_RECV_SET_CHANNEL_MASK&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x24, __u64)
DECL|macro|RAW1394_IOC_ISO_RECV_PACKETS
mdefine_line|#define RAW1394_IOC_ISO_RECV_PACKETS&t;&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x25, struct raw1394_iso_packets)
DECL|macro|RAW1394_IOC_ISO_RECV_RELEASE_PACKETS
mdefine_line|#define RAW1394_IOC_ISO_RECV_RELEASE_PACKETS&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x26, unsigned int)
DECL|macro|RAW1394_IOC_ISO_XMIT_PACKETS
mdefine_line|#define RAW1394_IOC_ISO_XMIT_PACKETS&t;&t;&bslash;&n;&t;_IOW (&squot;#&squot;, 0x27, struct raw1394_iso_packets)
DECL|macro|RAW1394_IOC_ISO_XMIT_SYNC
mdefine_line|#define RAW1394_IOC_ISO_XMIT_SYNC&t;&t;&bslash;&n;&t;_IO  (&squot;#&squot;, 0x28)
DECL|macro|RAW1394_IOC_ISO_RECV_FLUSH
mdefine_line|#define RAW1394_IOC_ISO_RECV_FLUSH              &bslash;&n;&t;_IO  (&squot;#&squot;, 0x29)
macro_line|#endif /* __IEEE1394_IOCTL_H */
eof
