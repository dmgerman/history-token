macro_line|#ifndef USBUSX2Y_H
DECL|macro|USBUSX2Y_H
mdefine_line|#define USBUSX2Y_H
macro_line|#include &quot;../usbaudio.h&quot;
macro_line|#include &quot;usbus428ctldefs.h&quot; 
DECL|macro|NRURBS
mdefine_line|#define NRURBS&t;        2&t;
DECL|macro|URBS_AsyncSeq
mdefine_line|#define URBS_AsyncSeq 10
DECL|macro|URB_DataLen_AsyncSeq
mdefine_line|#define URB_DataLen_AsyncSeq 32
r_typedef
r_struct
(brace
DECL|member|urb
r_struct
id|urb
op_star
id|urb
(braket
id|URBS_AsyncSeq
)braket
suffix:semicolon
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|typedef|snd_usX2Y_AsyncSeq_t
)brace
id|snd_usX2Y_AsyncSeq_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|submitted
r_int
id|submitted
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|snd_usX2Y_urbSeq_t
)brace
id|snd_usX2Y_urbSeq_t
suffix:semicolon
DECL|typedef|snd_usX2Y_substream_t
r_typedef
r_struct
id|snd_usX2Y_substream
id|snd_usX2Y_substream_t
suffix:semicolon
macro_line|#include &quot;usx2yhwdeppcm.h&quot;
r_typedef
r_struct
(brace
DECL|member|chip
id|snd_usb_audio_t
id|chip
suffix:semicolon
DECL|member|stride
r_int
id|stride
suffix:semicolon
DECL|member|In04urb
r_struct
id|urb
op_star
id|In04urb
suffix:semicolon
DECL|member|In04Buf
r_void
op_star
id|In04Buf
suffix:semicolon
DECL|member|In04Last
r_char
id|In04Last
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|In04IntCalls
r_int
id|In04IntCalls
suffix:semicolon
DECL|member|US04
id|snd_usX2Y_urbSeq_t
op_star
id|US04
suffix:semicolon
DECL|member|In04WaitQueue
id|wait_queue_head_t
id|In04WaitQueue
suffix:semicolon
DECL|member|AS04
id|snd_usX2Y_AsyncSeq_t
id|AS04
suffix:semicolon
DECL|member|rate
r_int
r_int
id|rate
comma
DECL|member|format
id|format
suffix:semicolon
DECL|member|chip_status
r_int
id|chip_status
suffix:semicolon
DECL|member|prepare_mutex
r_struct
id|semaphore
id|prepare_mutex
suffix:semicolon
DECL|member|us428ctls_sharedmem
id|us428ctls_sharedmem_t
op_star
id|us428ctls_sharedmem
suffix:semicolon
DECL|member|wait_iso_frame
r_int
id|wait_iso_frame
suffix:semicolon
DECL|member|us428ctls_wait_queue_head
id|wait_queue_head_t
id|us428ctls_wait_queue_head
suffix:semicolon
DECL|member|hwdep_pcm_shm
id|snd_usX2Y_hwdep_pcm_shm_t
op_star
id|hwdep_pcm_shm
suffix:semicolon
DECL|member|subs
id|snd_usX2Y_substream_t
op_star
id|subs
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|prepare_subs
id|snd_usX2Y_substream_t
op_star
r_volatile
id|prepare_subs
suffix:semicolon
DECL|member|prepare_wait_queue
id|wait_queue_head_t
id|prepare_wait_queue
suffix:semicolon
DECL|typedef|usX2Ydev_t
)brace
id|usX2Ydev_t
suffix:semicolon
DECL|struct|snd_usX2Y_substream
r_struct
id|snd_usX2Y_substream
(brace
DECL|member|usX2Y
id|usX2Ydev_t
op_star
id|usX2Y
suffix:semicolon
DECL|member|pcm_substream
id|snd_pcm_substream_t
op_star
id|pcm_substream
suffix:semicolon
DECL|member|endpoint
r_int
id|endpoint
suffix:semicolon
DECL|member|maxpacksize
r_int
r_int
id|maxpacksize
suffix:semicolon
multiline_comment|/* max packet size in bytes */
DECL|member|state
id|atomic_t
id|state
suffix:semicolon
DECL|macro|state_STOPPED
mdefine_line|#define state_STOPPED&t;0
DECL|macro|state_STARTING1
mdefine_line|#define state_STARTING1 1
DECL|macro|state_STARTING2
mdefine_line|#define state_STARTING2 2
DECL|macro|state_STARTING3
mdefine_line|#define state_STARTING3 3
DECL|macro|state_PREPARED
mdefine_line|#define state_PREPARED&t;4
DECL|macro|state_PRERUNNING
mdefine_line|#define state_PRERUNNING  6
DECL|macro|state_RUNNING
mdefine_line|#define state_RUNNING&t;8
DECL|member|hwptr
r_int
id|hwptr
suffix:semicolon
multiline_comment|/* free frame position in the buffer (only for playback) */
DECL|member|hwptr_done
r_int
id|hwptr_done
suffix:semicolon
multiline_comment|/* processed frame position in the buffer */
DECL|member|transfer_done
r_int
id|transfer_done
suffix:semicolon
multiline_comment|/* processed frames since last period update */
DECL|member|urb
r_struct
id|urb
op_star
id|urb
(braket
id|NRURBS
)braket
suffix:semicolon
multiline_comment|/* data urb table */
DECL|member|completed_urb
r_struct
id|urb
op_star
id|completed_urb
suffix:semicolon
DECL|member|tmpbuf
r_char
op_star
id|tmpbuf
suffix:semicolon
multiline_comment|/* temporary buffer for playback */
)brace
suffix:semicolon
DECL|macro|usX2Y
mdefine_line|#define usX2Y(c) ((usX2Ydev_t*)(c)-&gt;private_data)
r_int
id|usX2Y_audio_create
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|usX2Y_AsyncSeq04_init
c_func
(paren
id|usX2Ydev_t
op_star
id|usX2Y
)paren
suffix:semicolon
r_int
id|usX2Y_In04_init
c_func
(paren
id|usX2Ydev_t
op_star
id|usX2Y
)paren
suffix:semicolon
DECL|macro|NAME_ALLCAPS
mdefine_line|#define NAME_ALLCAPS &quot;US-X2Y&quot;
macro_line|#endif
eof
