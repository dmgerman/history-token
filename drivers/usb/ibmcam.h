multiline_comment|/*&n; * Header file for USB IBM C-It Video Camera driver.&n; *&n; * Supports IBM C-It Video Camera.&n; *&n; * This driver is based on earlier work of:&n; *&n; * (C) Copyright 1999 Johannes Erdfelt&n; * (C) Copyright 1999 Randy Dunlap&n; */
macro_line|#ifndef __LINUX_IBMCAM_H
DECL|macro|__LINUX_IBMCAM_H
mdefine_line|#define __LINUX_IBMCAM_H
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|USES_IBMCAM_PUTPIXEL
mdefine_line|#define USES_IBMCAM_PUTPIXEL    0       /* 0=Fast/oops 1=Slow/secure */
multiline_comment|/* Video Size 384 x 288 x 3 bytes for RGB */
multiline_comment|/* 384 because xawtv tries to grab 384 even though we tell it 352 is our max */
DECL|macro|V4L_FRAME_WIDTH
mdefine_line|#define V4L_FRAME_WIDTH         384
DECL|macro|V4L_FRAME_WIDTH_USED
mdefine_line|#define V4L_FRAME_WIDTH_USED&t;352
DECL|macro|V4L_FRAME_HEIGHT
mdefine_line|#define V4L_FRAME_HEIGHT        288
DECL|macro|V4L_BYTES_PER_PIXEL
mdefine_line|#define V4L_BYTES_PER_PIXEL     3
DECL|macro|MAX_FRAME_SIZE
mdefine_line|#define MAX_FRAME_SIZE          (V4L_FRAME_WIDTH * V4L_FRAME_HEIGHT * V4L_BYTES_PER_PIXEL)
multiline_comment|/* Camera capabilities (maximum) */
DECL|macro|CAMERA_IMAGE_WIDTH
mdefine_line|#define CAMERA_IMAGE_WIDTH      352
DECL|macro|CAMERA_IMAGE_HEIGHT
mdefine_line|#define CAMERA_IMAGE_HEIGHT     288
DECL|macro|CAMERA_IMAGE_LINE_SZ
mdefine_line|#define CAMERA_IMAGE_LINE_SZ    ((CAMERA_IMAGE_WIDTH * 3) / 2) /* Bytes */
DECL|macro|CAMERA_URB_FRAMES
mdefine_line|#define CAMERA_URB_FRAMES       32
DECL|macro|CAMERA_MAX_ISO_PACKET
mdefine_line|#define CAMERA_MAX_ISO_PACKET   1023 /* 1022 actually sent by camera */
DECL|macro|IBMCAM_NUMFRAMES
mdefine_line|#define IBMCAM_NUMFRAMES&t;2
DECL|macro|IBMCAM_NUMSBUF
mdefine_line|#define IBMCAM_NUMSBUF&t;&t;2
DECL|macro|FRAMES_PER_DESC
mdefine_line|#define FRAMES_PER_DESC&t;&t;(CAMERA_URB_FRAMES)
DECL|macro|FRAME_SIZE_PER_DESC
mdefine_line|#define FRAME_SIZE_PER_DESC&t;(CAMERA_MAX_ISO_PACKET)
multiline_comment|/* This macro restricts an int variable to an inclusive range */
DECL|macro|RESTRICT_TO_RANGE
mdefine_line|#define RESTRICT_TO_RANGE(v,mi,ma) { if ((v) &lt; (mi)) (v) = (mi); else if ((v) &gt; (ma)) (v) = (ma); }
multiline_comment|/*&n; * This macro performs bounds checking - use it when working with&n; * new formats, or else you may get oopses all over the place.&n; * If pixel falls out of bounds then it gets shoved back (as close&n; * to place of offence as possible) and is painted bright red.&n; */
DECL|macro|IBMCAM_PUTPIXEL
mdefine_line|#define IBMCAM_PUTPIXEL(fr, ix, iy, vr, vg, vb) { &bslash;&n;&t;register unsigned char *pf; &bslash;&n;&t;int limiter = 0, mx, my; &bslash;&n;&t;mx = ix; &bslash;&n;&t;my = iy; &bslash;&n;&t;if (mx &lt; 0) { &bslash;&n;&t;&t;mx=0; &bslash;&n;&t;&t;limiter++; &bslash;&n;&t;} else if (mx &gt;= 352) { &bslash;&n;&t;&t;mx=351; &bslash;&n;&t;&t;limiter++; &bslash;&n;&t;} &bslash;&n;&t;if (my &lt; 0) { &bslash;&n;&t;&t;my = 0; &bslash;&n;&t;&t;limiter++; &bslash;&n;&t;} else if (my &gt;= V4L_FRAME_HEIGHT) { &bslash;&n;&t;&t;my = V4L_FRAME_HEIGHT - 1; &bslash;&n;&t;&t;limiter++; &bslash;&n;&t;} &bslash;&n;&t;pf = (fr)-&gt;data + V4L_BYTES_PER_PIXEL*((iy)*352 + (ix)); &bslash;&n;&t;if (limiter) { &bslash;&n;&t;&t;*pf++ = 0; &bslash;&n;&t;&t;*pf++ = 0; &bslash;&n;&t;&t;*pf++ = 0xFF; &bslash;&n;&t;} else { &bslash;&n;&t;&t;*pf++ = (vb); &bslash;&n;&t;&t;*pf++ = (vg); &bslash;&n;&t;&t;*pf++ = (vr); &bslash;&n;&t;} &bslash;&n;}
multiline_comment|/*&n; * We use macros to do YUV -&gt; RGB conversion because this is&n; * very important for speed and totally unimportant for size.&n; *&n; * YUV -&gt; RGB Conversion&n; * ---------------------&n; *&n; * B = 1.164*(Y-16)&t;&t;    + 2.018*(V-128)&n; * G = 1.164*(Y-16) - 0.813*(U-128) - 0.391*(V-128)&n; * R = 1.164*(Y-16) + 1.596*(U-128)&n; *&n; * If you fancy integer arithmetics (as you should), hear this:&n; *&n; * 65536*B = 76284*(Y-16)&t;&t;  + 132252*(V-128)&n; * 65536*G = 76284*(Y-16) -  53281*(U-128) -  25625*(V-128)&n; * 65536*R = 76284*(Y-16) + 104595*(U-128)&n; *&n; * Make sure the output values are within [0..255] range.&n; */
DECL|macro|LIMIT_RGB
mdefine_line|#define LIMIT_RGB(x) (((x) &lt; 0) ? 0 : (((x) &gt; 255) ? 255 : (x)))
DECL|macro|YUV_TO_RGB_BY_THE_BOOK
mdefine_line|#define YUV_TO_RGB_BY_THE_BOOK(my,mu,mv,mr,mg,mb) { &bslash;&n;    int mm_y, mm_yc, mm_u, mm_v, mm_r, mm_g, mm_b; &bslash;&n;    mm_y = (my) - 16;  &bslash;&n;    mm_u = (mu) - 128; &bslash;&n;    mm_v = (mv) - 128; &bslash;&n;    mm_yc= mm_y * 76284; &bslash;&n;    mm_b = (mm_yc&t;&t;+ 132252*mm_v&t;) &gt;&gt; 16; &bslash;&n;    mm_g = (mm_yc -  53281*mm_u -  25625*mm_v&t;) &gt;&gt; 16; &bslash;&n;    mm_r = (mm_yc + 104595*mm_u&t;&t;&t;) &gt;&gt; 16; &bslash;&n;    mb = LIMIT_RGB(mm_b); &bslash;&n;    mg = LIMIT_RGB(mm_g); &bslash;&n;    mr = LIMIT_RGB(mm_r); &bslash;&n;}
multiline_comment|/* Debugging aid */
DECL|macro|IBMCAM_SAY_AND_WAIT
mdefine_line|#define IBMCAM_SAY_AND_WAIT(what) { &bslash;&n;&t;wait_queue_head_t wq; &bslash;&n;&t;init_waitqueue_head(&amp;wq); &bslash;&n;&t;printk(KERN_INFO &quot;Say: %s&bslash;n&quot;, what); &bslash;&n;&t;interruptible_sleep_on_timeout (&amp;wq, HZ*3); &bslash;&n;}
multiline_comment|/*&n; * This macro checks if ibmcam is still operational. The &squot;ibmcam&squot;&n; * pointer must be valid, ibmcam-&gt;dev must be valid, we are not&n; * removing the device and the device has not erred on us.&n; */
DECL|macro|IBMCAM_IS_OPERATIONAL
mdefine_line|#define IBMCAM_IS_OPERATIONAL(ibm_cam) (&bslash;&n;&t;(ibm_cam != NULL) &amp;&amp; &bslash;&n;&t;((ibm_cam)-&gt;dev != NULL) &amp;&amp; &bslash;&n;&t;((ibm_cam)-&gt;last_error == 0) &amp;&amp; &bslash;&n;&t;(!(ibm_cam)-&gt;remove_pending))
r_enum
(brace
DECL|enumerator|STATE_SCANNING
id|STATE_SCANNING
comma
multiline_comment|/* Scanning for header */
DECL|enumerator|STATE_LINES
id|STATE_LINES
comma
multiline_comment|/* Parsing lines */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|FRAME_UNUSED
id|FRAME_UNUSED
comma
multiline_comment|/* Unused (no MCAPTURE) */
DECL|enumerator|FRAME_READY
id|FRAME_READY
comma
multiline_comment|/* Ready to start grabbing */
DECL|enumerator|FRAME_GRABBING
id|FRAME_GRABBING
comma
multiline_comment|/* In the process of being grabbed into */
DECL|enumerator|FRAME_DONE
id|FRAME_DONE
comma
multiline_comment|/* Finished grabbing, but not been synced yet */
DECL|enumerator|FRAME_ERROR
id|FRAME_ERROR
comma
multiline_comment|/* Something bad happened while processing */
)brace
suffix:semicolon
r_struct
id|usb_device
suffix:semicolon
DECL|struct|ibmcam_sbuf
r_struct
id|ibmcam_sbuf
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ibmcam_frame
r_struct
id|ibmcam_frame
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Frame buffer */
DECL|member|order_uv
r_int
id|order_uv
suffix:semicolon
multiline_comment|/* True=UV False=VU */
DECL|member|order_yc
r_int
id|order_yc
suffix:semicolon
multiline_comment|/* True=Yc False=cY (&squot;c&squot;=either U or V) */
DECL|member|hdr_sig
r_int
r_char
id|hdr_sig
suffix:semicolon
multiline_comment|/* &quot;00 FF 00 ??&quot; where &squot;hdr_sig&squot; is &squot;??&squot; */
DECL|member|width
r_int
id|width
suffix:semicolon
multiline_comment|/* Width application is expecting */
DECL|member|height
r_int
id|height
suffix:semicolon
multiline_comment|/* Height */
DECL|member|frmwidth
r_int
id|frmwidth
suffix:semicolon
multiline_comment|/* Width the frame actually is */
DECL|member|frmheight
r_int
id|frmheight
suffix:semicolon
multiline_comment|/* Height */
DECL|member|grabstate
r_volatile
r_int
id|grabstate
suffix:semicolon
multiline_comment|/* State of grabbing */
DECL|member|scanstate
r_int
id|scanstate
suffix:semicolon
multiline_comment|/* State of scanning */
DECL|member|curline
r_int
id|curline
suffix:semicolon
multiline_comment|/* Line of frame we&squot;re working on */
DECL|member|scanlength
r_int
id|scanlength
suffix:semicolon
multiline_comment|/* uncompressed, raw data length of frame */
DECL|member|bytes_read
r_int
id|bytes_read
suffix:semicolon
multiline_comment|/* amount of scanlength that has been read from *data */
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
multiline_comment|/* Processes waiting */
)brace
suffix:semicolon
DECL|macro|IBMCAM_MODEL_1
mdefine_line|#define&t;IBMCAM_MODEL_1&t;1&t;/* XVP-501, 3 interfaces, rev. 0.02 */
DECL|macro|IBMCAM_MODEL_2
mdefine_line|#define IBMCAM_MODEL_2&t;2&t;/* KSX-X9903, 2 interfaces, rev. 3.0a */
DECL|struct|usb_ibmcam
r_struct
id|usb_ibmcam
(brace
DECL|member|vdev
r_struct
id|video_device
id|vdev
suffix:semicolon
multiline_comment|/* Device structure */
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|iface
r_int
r_char
id|iface
suffix:semicolon
multiline_comment|/* Video interface number */
DECL|member|ifaceAltActive
DECL|member|ifaceAltInactive
r_int
r_char
id|ifaceAltActive
comma
id|ifaceAltInactive
suffix:semicolon
multiline_comment|/* Alt settings */
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|user
r_int
id|user
suffix:semicolon
multiline_comment|/* user count for exclusive use */
DECL|member|ibmcam_used
r_int
id|ibmcam_used
suffix:semicolon
multiline_comment|/* Is this structure in use? */
DECL|member|initialized
r_int
id|initialized
suffix:semicolon
multiline_comment|/* Had we already sent init sequence? */
DECL|member|camera_model
r_int
id|camera_model
suffix:semicolon
multiline_comment|/* What type of IBM camera we got? */
DECL|member|streaming
r_int
id|streaming
suffix:semicolon
multiline_comment|/* Are we streaming Isochronous? */
DECL|member|grabbing
r_int
id|grabbing
suffix:semicolon
multiline_comment|/* Are we grabbing? */
DECL|member|last_error
r_int
id|last_error
suffix:semicolon
multiline_comment|/* What calamity struck us? */
DECL|member|compress
r_int
id|compress
suffix:semicolon
multiline_comment|/* Should the next frame be compressed? */
DECL|member|fbuf
r_char
op_star
id|fbuf
suffix:semicolon
multiline_comment|/* Videodev buffer area */
DECL|member|fbuf_size
r_int
id|fbuf_size
suffix:semicolon
multiline_comment|/* Videodev buffer size */
DECL|member|curframe
r_int
id|curframe
suffix:semicolon
DECL|member|frame
r_struct
id|ibmcam_frame
id|frame
(braket
id|IBMCAM_NUMFRAMES
)braket
suffix:semicolon
multiline_comment|/* Double buffering */
DECL|member|cursbuf
r_int
id|cursbuf
suffix:semicolon
multiline_comment|/* Current receiving sbuf */
DECL|member|sbuf
r_struct
id|ibmcam_sbuf
id|sbuf
(braket
id|IBMCAM_NUMSBUF
)braket
suffix:semicolon
multiline_comment|/* Double buffering */
DECL|member|remove_pending
r_volatile
r_int
id|remove_pending
suffix:semicolon
multiline_comment|/* If set then about to exit */
multiline_comment|/*&n;&t; * Scratch space from the Isochronous pipe.&n;&t; * Scratch buffer should contain at least one pair of lines&n;&t; * (CAMERA_IMAGE_LINE_SZ). We set it to two pairs here.&n;&t; * This will be approximately 2 KB. HOWEVER in reality this&n;&t; * buffer must be as large as hundred of KB because otherwise&n;&t; * you&squot;ll get lots of overflows because V4L client may request&n;&t; * frames not as uniformly as USB sources them.&n;&t; */
DECL|member|scratch
r_int
r_char
op_star
id|scratch
suffix:semicolon
DECL|member|scratchlen
r_int
id|scratchlen
suffix:semicolon
DECL|member|vpic
DECL|member|vpic_old
r_struct
id|video_picture
id|vpic
comma
id|vpic_old
suffix:semicolon
multiline_comment|/* Picture settings */
DECL|member|vcap
r_struct
id|video_capability
id|vcap
suffix:semicolon
multiline_comment|/* Video capabilities */
DECL|member|vchan
r_struct
id|video_channel
id|vchan
suffix:semicolon
multiline_comment|/* May be used for tuner support */
DECL|member|video_endp
r_int
r_char
id|video_endp
suffix:semicolon
multiline_comment|/* 0x82 for IBM camera */
DECL|member|has_hdr
r_int
id|has_hdr
suffix:semicolon
DECL|member|frame_num
r_int
id|frame_num
suffix:semicolon
DECL|member|iso_packet_len
r_int
id|iso_packet_len
suffix:semicolon
multiline_comment|/* Videomode-dependent, saves bus bandwidth */
multiline_comment|/* Statistics that can be overlayed on screen */
DECL|member|urb_count
r_int
r_int
id|urb_count
suffix:semicolon
multiline_comment|/* How many URBs we received so far */
DECL|member|urb_length
r_int
r_int
id|urb_length
suffix:semicolon
multiline_comment|/* Length of last URB */
DECL|member|data_count
r_int
r_int
id|data_count
suffix:semicolon
multiline_comment|/* How many bytes we received */
DECL|member|header_count
r_int
r_int
id|header_count
suffix:semicolon
multiline_comment|/* How many frame headers we found */
DECL|member|scratch_ovf_count
r_int
r_int
id|scratch_ovf_count
suffix:semicolon
multiline_comment|/* How many times we overflowed scratch */
DECL|member|iso_skip_count
r_int
r_int
id|iso_skip_count
suffix:semicolon
multiline_comment|/* How many empty ISO packets received */
DECL|member|iso_err_count
r_int
r_int
id|iso_err_count
suffix:semicolon
multiline_comment|/* How many bad ISO packets received */
)brace
suffix:semicolon
macro_line|#endif /* __LINUX_IBMCAM_H */
eof
