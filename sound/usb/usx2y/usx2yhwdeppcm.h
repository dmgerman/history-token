DECL|macro|MAXPACK
mdefine_line|#define MAXPACK 50
DECL|macro|MAXBUFFERMS
mdefine_line|#define MAXBUFFERMS 100
DECL|macro|MAXSTRIDE
mdefine_line|#define MAXSTRIDE 3
DECL|macro|SSS
mdefine_line|#define SSS (((MAXPACK*MAXBUFFERMS*MAXSTRIDE + 4096) / 4096) * 4096)
DECL|struct|snd_usX2Y_hwdep_pcm_shm
r_struct
id|snd_usX2Y_hwdep_pcm_shm
(brace
DECL|member|playback
r_char
id|playback
(braket
id|SSS
)braket
suffix:semicolon
DECL|member|capture0x8
r_char
id|capture0x8
(braket
id|SSS
)braket
suffix:semicolon
DECL|member|capture0xA
r_char
id|capture0xA
(braket
id|SSS
)braket
suffix:semicolon
DECL|member|playback_iso_head
r_volatile
r_int
id|playback_iso_head
suffix:semicolon
DECL|member|playback_iso_start
r_int
id|playback_iso_start
suffix:semicolon
r_struct
(brace
DECL|member|frame
r_int
id|frame
comma
DECL|member|offset
id|offset
comma
DECL|member|length
id|length
suffix:semicolon
DECL|member|captured_iso
)brace
id|captured_iso
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|captured_iso_head
r_volatile
r_int
id|captured_iso_head
suffix:semicolon
DECL|member|captured_iso_frames
r_volatile
r_int
id|captured_iso_frames
suffix:semicolon
DECL|member|capture_iso_start
r_int
id|capture_iso_start
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|snd_usX2Y_hwdep_pcm_shm_t
r_typedef
r_struct
id|snd_usX2Y_hwdep_pcm_shm
id|snd_usX2Y_hwdep_pcm_shm_t
suffix:semicolon
eof
