macro_line|#if 0
mdefine_line|#define TRACE_TXT(text) &bslash;&n;&t;{ &bslash;&n;&t;  if(dtlk_trace) &bslash;&n;&t;  { &bslash;&n;&t;    console_print(text); &bslash;&n;&t;    console_print(&quot;&bslash;n&quot;); &bslash;&n;&t;  } &bslash;&n;&t;}
mdefine_line|#define TRACE_CHR(chr) &bslash;&n;&t;{ &bslash;&n;&t;  if(dtlk_trace) &bslash;&n;&t;    console_print(chr); &bslash;&n;&t;} &bslash;&n;
macro_line|#endif
DECL|macro|DTLK_MINOR
mdefine_line|#define DTLK_MINOR&t;0
DECL|macro|DTLK_IO_EXTENT
mdefine_line|#define DTLK_IO_EXTENT&t;0x02
multiline_comment|/* ioctl&squot;s use magic number of 0xa3 */
DECL|macro|DTLK_INTERROGATE
mdefine_line|#define DTLK_INTERROGATE 0xa390&t;/* get settings from the DoubleTalk */
DECL|macro|DTLK_STATUS
mdefine_line|#define DTLK_STATUS 0xa391&t;/* get status from the DoubleTalk */
DECL|macro|DTLK_CLEAR
mdefine_line|#define DTLK_CLEAR 0x18&t;&t;/* stops speech */
DECL|macro|DTLK_MAX_RETRIES
mdefine_line|#define DTLK_MAX_RETRIES (loops_per_jiffy/(10000/HZ))
multiline_comment|/* TTS Port Status Flags */
DECL|macro|TTS_READABLE
mdefine_line|#define TTS_READABLE     0x80&t;/* mask for bit which is nonzero if a&n;&t;&t;&t;&t;   byte can be read from the TTS port */
DECL|macro|TTS_SPEAKING
mdefine_line|#define TTS_SPEAKING     0x40&t;/* mask for SYNC bit, which is nonzero&n;&t;&t;&t;&t;   while DoubleTalk is producing&n;&t;&t;&t;&t;   output with TTS, PCM or CVSD&n;&t;&t;&t;&t;   synthesizers or tone generators&n;&t;&t;&t;&t;   (that is, all but LPC) */
DECL|macro|TTS_SPEAKING2
mdefine_line|#define TTS_SPEAKING2    0x20&t;/* mask for SYNC2 bit,&n;&t;&t;&t;&t;   which falls to zero up to 0.4 sec&n;&t;&t;&t;&t;   before speech stops */
DECL|macro|TTS_WRITABLE
mdefine_line|#define TTS_WRITABLE     0x10&t;/* mask for RDY bit, which when set to&n;             &t;&t;&t;   1, indicates the TTS port is ready&n;             &t;&t;&t;   to accept a byte of data.  The RDY&n;             &t;&t;&t;   bit goes zero 2-3 usec after&n;             &t;&t;&t;   writing, and goes 1 again 180-190&n;             &t;&t;&t;   usec later. */
DECL|macro|TTS_ALMOST_FULL
mdefine_line|#define TTS_ALMOST_FULL  0x08&t;/* mask for AF bit: When set to 1,&n;&t;&t;&t;&t;   indicates that less than 300 free&n;&t;&t;&t;&t;   bytes are available in the TTS&n;&t;&t;&t;&t;   input buffer. AF is always 0 in the&n;&t;&t;&t;&t;   PCM, TGN and CVSD modes. */
DECL|macro|TTS_ALMOST_EMPTY
mdefine_line|#define TTS_ALMOST_EMPTY 0x04&t;/* mask for AE bit: When set to 1,&n;&t;&t;&t;&t;   indicates that less than 300 bytes&n;&t;&t;&t;&t;   of data remain in DoubleTalk&squot;s&n;&t;&t;&t;&t;   input (TTS or PCM) buffer. AE is&n;&t;&t;&t;&t;   always 1 in the TGN and CVSD&n;&t;&t;&t;&t;   modes. */
multiline_comment|/* LPC speak commands */
DECL|macro|LPC_5220_NORMAL
mdefine_line|#define LPC_5220_NORMAL 0x60&t;/* 5220 format decoding table, normal rate */
DECL|macro|LPC_5220_FAST
mdefine_line|#define LPC_5220_FAST 0x64&t;/* 5220 format decoding table, fast rate */
DECL|macro|LPC_D6_NORMAL
mdefine_line|#define LPC_D6_NORMAL 0x20&t;/* D6 format decoding table, normal rate */
DECL|macro|LPC_D6_FAST
mdefine_line|#define LPC_D6_FAST 0x24&t;/* D6 format decoding table, fast rate */
multiline_comment|/* LPC Port Status Flags (valid only after one of the LPC&n;           speak commands) */
DECL|macro|LPC_SPEAKING
mdefine_line|#define LPC_SPEAKING     0x80&t;/* mask for TS bit: When set to 1,&n;&t;&t;&t;&t;   indicates the LPC synthesizer is&n;&t;&t;&t;&t;   producing speech.*/
DECL|macro|LPC_BUFFER_LOW
mdefine_line|#define LPC_BUFFER_LOW   0x40&t;/* mask for BL bit: When set to 1,&n;&t;&t;&t;&t;   indicates that the hardware LPC&n;&t;&t;&t;&t;   data buffer has less than 30 bytes&n;&t;&t;&t;&t;   remaining. (Total internal buffer&n;&t;&t;&t;&t;   size = 4096 bytes.) */
DECL|macro|LPC_BUFFER_EMPTY
mdefine_line|#define LPC_BUFFER_EMPTY 0x20&t;/* mask for BE bit: When set to 1,&n;&t;&t;&t;&t;   indicates that the LPC data buffer&n;&t;&t;&t;&t;   ran out of data (error condition if&n;&t;&t;&t;&t;   TS is also 1).  */
multiline_comment|/* data returned by Interrogate command */
DECL|struct|dtlk_settings
r_struct
id|dtlk_settings
(brace
DECL|member|serial_number
r_int
r_int
id|serial_number
suffix:semicolon
multiline_comment|/* 0-7Fh:0-7Fh */
DECL|member|rom_version
r_int
r_char
id|rom_version
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* null terminated string */
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* 0=Character; 1=Phoneme; 2=Text */
DECL|member|punc_level
r_int
r_char
id|punc_level
suffix:semicolon
multiline_comment|/* nB; 0-7 */
DECL|member|formant_freq
r_int
r_char
id|formant_freq
suffix:semicolon
multiline_comment|/* nF; 0-9 */
DECL|member|pitch
r_int
r_char
id|pitch
suffix:semicolon
multiline_comment|/* nP; 0-99 */
DECL|member|speed
r_int
r_char
id|speed
suffix:semicolon
multiline_comment|/* nS; 0-9 */
DECL|member|volume
r_int
r_char
id|volume
suffix:semicolon
multiline_comment|/* nV; 0-9 */
DECL|member|tone
r_int
r_char
id|tone
suffix:semicolon
multiline_comment|/* nX; 0-2 */
DECL|member|expression
r_int
r_char
id|expression
suffix:semicolon
multiline_comment|/* nE; 0-9 */
DECL|member|ext_dict_loaded
r_int
r_char
id|ext_dict_loaded
suffix:semicolon
multiline_comment|/* 1=exception dictionary loaded */
DECL|member|ext_dict_status
r_int
r_char
id|ext_dict_status
suffix:semicolon
multiline_comment|/* 1=exception dictionary enabled */
DECL|member|free_ram
r_int
r_char
id|free_ram
suffix:semicolon
multiline_comment|/* # pages (truncated) remaining for&n;                                   text buffer */
DECL|member|articulation
r_int
r_char
id|articulation
suffix:semicolon
multiline_comment|/* nA; 0-9 */
DECL|member|reverb
r_int
r_char
id|reverb
suffix:semicolon
multiline_comment|/* nR; 0-9 */
DECL|member|eob
r_int
r_char
id|eob
suffix:semicolon
multiline_comment|/* 7Fh value indicating end of&n;                                   parameter block */
DECL|member|has_indexing
r_int
r_char
id|has_indexing
suffix:semicolon
multiline_comment|/* nonzero if indexing is implemented */
)brace
suffix:semicolon
eof
