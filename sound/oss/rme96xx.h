multiline_comment|/* (C) 2000 Guenter Geiger &lt;geiger@debian.org&gt;&n;   with copy/pastes from the driver of Winfried Ritsch &lt;ritsch@iem.kug.ac.at&gt;&n;&n;Modifications - Heiko Purnhagen &lt;purnhage@tnt.uni-hannover.de&gt;&n;   HP20020116 towards REV 1.5 support, based on ALSA&squot;s card-rme9652.c&n;   HP20020201 completed?&n;&n;A text/graphic control panel (rmectrl/xrmectrl) is available from&n;   http://gige.xdv.org/pages/soft/pages/rme&n;*/
macro_line|#ifndef AFMT_S32_BLOCKED
DECL|macro|AFMT_S32_BLOCKED
mdefine_line|#define AFMT_S32_BLOCKED 0x0000400
macro_line|#endif
multiline_comment|/* AFMT_S16_BLOCKED not yet supported */
macro_line|#ifndef AFMT_S16_BLOCKED 
DECL|macro|AFMT_S16_BLOCKED
mdefine_line|#define AFMT_S16_BLOCKED 0x0000800
macro_line|#endif
DECL|struct|rme_status
r_typedef
r_struct
id|rme_status
(brace
DECL|member|irq
r_int
r_int
id|irq
suffix:colon
l_int|1
suffix:semicolon
DECL|member|lockmask
r_int
r_int
id|lockmask
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* ADAT input PLLs locked */
multiline_comment|/*   100=ADAT1, 010=ADAT2, 001=ADAT3 */
DECL|member|sr48
r_int
r_int
id|sr48
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* sample rate: 0=44.1/88.2 1=48/96 kHz */
DECL|member|wclock
r_int
r_int
id|wclock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1=wordclock used */
DECL|member|bufpoint
r_int
r_int
id|bufpoint
suffix:colon
l_int|10
suffix:semicolon
DECL|member|syncmask
r_int
r_int
id|syncmask
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* ADAT input in sync with system clock */
multiline_comment|/* 100=ADAT1, 010=ADAT2, 001=ADAT3 */
DECL|member|doublespeed
r_int
r_int
id|doublespeed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* sample rate: 0=44.1/48 1=88.2/96 kHz */
DECL|member|tc_busy
r_int
r_int
id|tc_busy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tc_out
r_int
r_int
id|tc_out
suffix:colon
l_int|1
suffix:semicolon
DECL|member|crystalrate
r_int
r_int
id|crystalrate
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* spdif input sample rate: */
multiline_comment|/*   000=64kHz, 100=88.2kHz, 011=96kHz */
multiline_comment|/*   111=32kHz, 110=44.1kHz, 101=48kHz */
DECL|member|spdif_error
r_int
r_int
id|spdif_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1=no spdif lock */
DECL|member|bufid
r_int
r_int
id|bufid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tc_valid
r_int
r_int
id|tc_valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1=timecode input detected */
DECL|member|spdif_read
r_int
r_int
id|spdif_read
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|rme_status_t
)brace
id|rme_status_t
suffix:semicolon
multiline_comment|/* only fields marked W: can be modified by writing to SOUND_MIXER_PRIVATE3 */
DECL|struct|rme_control
r_typedef
r_struct
id|rme_control
(brace
DECL|member|start
r_int
r_int
id|start
suffix:colon
l_int|1
suffix:semicolon
DECL|member|latency
r_int
r_int
id|latency
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* buffer size / latency [samples]: */
multiline_comment|/*   0=64 ... 7=8192 */
DECL|member|master
r_int
r_int
id|master
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* W: clock mode: 1=master 0=slave/auto */
DECL|member|ie
r_int
r_int
id|ie
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sr48
r_int
r_int
id|sr48
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* samplerate 0=44.1/88.2, 1=48/96 kHz */
DECL|member|spare
r_int
r_int
id|spare
suffix:colon
l_int|1
suffix:semicolon
DECL|member|doublespeed
r_int
r_int
id|doublespeed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* double speed 0=44.1/48, 1=88.2/96 Khz */
DECL|member|pro
r_int
r_int
id|pro
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* W: SPDIF-OUT 0=consumer, 1=professional */
DECL|member|emphasis
r_int
r_int
id|emphasis
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* W: SPDIF-OUT emphasis 0=off, 1=on */
DECL|member|dolby
r_int
r_int
id|dolby
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* W: SPDIF-OUT non-audio bit 1=set, 0=unset */
DECL|member|opt_out
r_int
r_int
id|opt_out
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* W: use 1st optical OUT as SPDIF: 1=yes, 0=no */
DECL|member|wordclock
r_int
r_int
id|wordclock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* W: use Wordclock as sync (overwrites master) */
DECL|member|spdif_in
r_int
r_int
id|spdif_in
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* W: SPDIF-IN: */
multiline_comment|/*    00=optical (ADAT1), 01=coaxial (Cinch), 10=internal CDROM */
DECL|member|sync_ref
r_int
r_int
id|sync_ref
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* W: preferred sync-source in autosync */
multiline_comment|/*    00=ADAT1, 01=ADAT2, 10=ADAT3, 11=SPDIF */
DECL|member|spdif_reset
r_int
r_int
id|spdif_reset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|spdif_select
r_int
r_int
id|spdif_select
suffix:colon
l_int|1
suffix:semicolon
DECL|member|spdif_clock
r_int
r_int
id|spdif_clock
suffix:colon
l_int|1
suffix:semicolon
DECL|member|spdif_write
r_int
r_int
id|spdif_write
suffix:colon
l_int|1
suffix:semicolon
DECL|member|adat1_cd
r_int
r_int
id|adat1_cd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* W: Rev 1.5+: if set, internal CD connector carries ADAT */
DECL|typedef|rme_ctrl_t
)brace
id|rme_ctrl_t
suffix:semicolon
DECL|struct|_rme_mixer
r_typedef
r_struct
id|_rme_mixer
(brace
DECL|member|i_offset
r_int
id|i_offset
suffix:semicolon
DECL|member|o_offset
r_int
id|o_offset
suffix:semicolon
DECL|member|devnr
r_int
id|devnr
suffix:semicolon
DECL|member|spare
r_int
id|spare
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|rme_mixer
)brace
id|rme_mixer
suffix:semicolon
eof
