macro_line|#ifndef __SOUND_AZF3328_H
DECL|macro|__SOUND_AZF3328_H
mdefine_line|#define __SOUND_AZF3328_H
multiline_comment|/* type argument to use for the I/O functions */
DECL|macro|WORD_VALUE
mdefine_line|#define WORD_VALUE      0x1000
DECL|macro|DWORD_VALUE
mdefine_line|#define DWORD_VALUE     0x2000
DECL|macro|BYTE_VALUE
mdefine_line|#define BYTE_VALUE      0x4000
multiline_comment|/*** main I/O area port indices ***/
multiline_comment|/* (only 0x70 of 0x80 bytes saved/restored by Windows driver) */
multiline_comment|/* the driver initialisation suggests a layout of 3 main areas:&n; * from 0x00 (playback), from 0x20 (recording) and from 0x40 (maybe DirectX&n; * timer ???). and probably another area from 0x60 to 0x6f&n; * (IRQ management, power management etc. ???). */
multiline_comment|/* playback area */
DECL|macro|IDX_IO_PLAY_FLAGS
mdefine_line|#define IDX_IO_PLAY_FLAGS       0x00
multiline_comment|/* able to reactivate output after output muting due to 8/16bit&n;      * output change, just like 0x0002.&n;      * 0x0001 is the only bit that&squot;s able to start the DMA counter */
DECL|macro|DMA_RESUME
mdefine_line|#define DMA_RESUME&t;&t;&t;0x0001 /* paused if cleared ? */
multiline_comment|/* 0x0002 *temporarily* set during DMA stopping. hmm&n;      * both 0x0002 and 0x0004 set in playback setup. */
multiline_comment|/* able to reactivate output after output muting due to 8/16bit&n;      * output change, just like 0x0001. */
DECL|macro|DMA_PLAY_SOMETHING1
mdefine_line|#define DMA_PLAY_SOMETHING1&t;&t;0x0002 /* &bslash; alternated (toggled) */
multiline_comment|/* 0x0004: NOT able to reactivate output */
DECL|macro|DMA_PLAY_SOMETHING2
mdefine_line|#define DMA_PLAY_SOMETHING2&t;&t;0x0004 /* / bits */
DECL|macro|SOMETHING_ALMOST_ALWAYS_SET
mdefine_line|#define SOMETHING_ALMOST_ALWAYS_SET&t;0x0008 /* ???; can be modified */
DECL|macro|DMA_EPILOGUE_SOMETHING
mdefine_line|#define DMA_EPILOGUE_SOMETHING&t;0x0010
DECL|macro|DMA_SOMETHING_ELSE
mdefine_line|#define DMA_SOMETHING_ELSE&t;&t;0x0020 /* ??? */
DECL|macro|SOMETHING_UNMODIFIABLE
mdefine_line|#define SOMETHING_UNMODIFIABLE&t;0xffc0 /* unused ? not modifiable */
DECL|macro|IDX_IO_PLAY_IRQMASK
mdefine_line|#define IDX_IO_PLAY_IRQMASK     0x02
multiline_comment|/* write back to flags in case flags are set, in order to ACK IRQ in handler&n;   * (bit 1 of port 0x64 indicates interrupt for one of these three types)&n;   * sometimes in this case it just writes 0xffff to globally ACK all IRQs&n;   * settings written are not reflected when reading back, though.&n;   * seems to be IRQ, too (frequently used: port |= 0x07 !), but who knows ? */
DECL|macro|IRQ_PLAY_SOMETHING
mdefine_line|#define IRQ_PLAY_SOMETHING&t;&t;0x0001 /* something &amp; ACK */
DECL|macro|IRQ_FINISHED_PLAYBUF_1
mdefine_line|#define IRQ_FINISHED_PLAYBUF_1&t;0x0002 /* 1st dmabuf finished &amp; ACK */
DECL|macro|IRQ_FINISHED_PLAYBUF_2
mdefine_line|#define IRQ_FINISHED_PLAYBUF_2&t;0x0004 /* 2nd dmabuf finished &amp; ACK */
DECL|macro|IRQMASK_SOME_STATUS_1
mdefine_line|#define IRQMASK_SOME_STATUS_1&t;&t;0x0008 /* &bslash; related bits */
DECL|macro|IRQMASK_SOME_STATUS_2
mdefine_line|#define IRQMASK_SOME_STATUS_2&t;&t;0x0010 /* / (checked together in loop) */
DECL|macro|IRQMASK_UNMODIFIABLE
mdefine_line|#define IRQMASK_UNMODIFIABLE&t;&t;0xffe0 /* unused ? not modifiable */
DECL|macro|IDX_IO_PLAY_DMA_START_1
mdefine_line|#define IDX_IO_PLAY_DMA_START_1 0x04 /* start address of 1st DMA play area */
DECL|macro|IDX_IO_PLAY_DMA_START_2
mdefine_line|#define IDX_IO_PLAY_DMA_START_2 0x08 /* start address of 2nd DMA play area */
DECL|macro|IDX_IO_PLAY_DMA_LEN_1
mdefine_line|#define IDX_IO_PLAY_DMA_LEN_1   0x0c /* length of 1st DMA play area */
DECL|macro|IDX_IO_PLAY_DMA_LEN_2
mdefine_line|#define IDX_IO_PLAY_DMA_LEN_2   0x0e /* length of 2nd DMA play area */
DECL|macro|IDX_IO_PLAY_DMA_CURRPOS
mdefine_line|#define IDX_IO_PLAY_DMA_CURRPOS 0x10 /* current DMA position  */
DECL|macro|IDX_IO_PLAY_DMA_CURROFS
mdefine_line|#define IDX_IO_PLAY_DMA_CURROFS&t;0x14 /* offset within current DMA play area */
DECL|macro|IDX_IO_PLAY_SOUNDFORMAT
mdefine_line|#define IDX_IO_PLAY_SOUNDFORMAT 0x16
multiline_comment|/* all unspecified bits can&squot;t be modified */
DECL|macro|SOUNDFORMAT_FREQUENCY_MASK
mdefine_line|#define SOUNDFORMAT_FREQUENCY_MASK&t;0x000f
multiline_comment|/* all _SUSPECTED_ values are not used by Windows drivers, so we don&squot;t&n;     * have any hard facts, only rough measurements */
DECL|macro|SOUNDFORMAT_FREQ_SUSPECTED_4000
mdefine_line|#define SOUNDFORMAT_FREQ_SUSPECTED_4000&t;0x0c
DECL|macro|SOUNDFORMAT_FREQ_SUSPECTED_4800
mdefine_line|#define SOUNDFORMAT_FREQ_SUSPECTED_4800&t;0x0a
DECL|macro|SOUNDFORMAT_FREQ_5510
mdefine_line|#define SOUNDFORMAT_FREQ_5510&t;&t;0x0d
DECL|macro|SOUNDFORMAT_FREQ_6620
mdefine_line|#define SOUNDFORMAT_FREQ_6620&t;&t;0x0b
DECL|macro|SOUNDFORMAT_FREQ_8000
mdefine_line|#define SOUNDFORMAT_FREQ_8000&t;&t;0x00 /* also 0x0e ? */
DECL|macro|SOUNDFORMAT_FREQ_9600
mdefine_line|#define SOUNDFORMAT_FREQ_9600&t;&t;0x08
DECL|macro|SOUNDFORMAT_FREQ_SUSPECTED_12000
mdefine_line|#define SOUNDFORMAT_FREQ_SUSPECTED_12000&t;0x09
DECL|macro|SOUNDFORMAT_FREQ_11025
mdefine_line|#define SOUNDFORMAT_FREQ_11025&t;&t;0x01 /* also 0x0f ? */
DECL|macro|SOUNDFORMAT_FREQ_16000
mdefine_line|#define SOUNDFORMAT_FREQ_16000&t;&t;0x02
DECL|macro|SOUNDFORMAT_FREQ_22050
mdefine_line|#define SOUNDFORMAT_FREQ_22050&t;&t;0x03
DECL|macro|SOUNDFORMAT_FREQ_32000
mdefine_line|#define SOUNDFORMAT_FREQ_32000&t;&t;0x04
DECL|macro|SOUNDFORMAT_FREQ_44100
mdefine_line|#define SOUNDFORMAT_FREQ_44100&t;&t;0x05
DECL|macro|SOUNDFORMAT_FREQ_48000
mdefine_line|#define SOUNDFORMAT_FREQ_48000&t;&t;0x06
DECL|macro|SOUNDFORMAT_FREQ_SUSPECTED_64000
mdefine_line|#define SOUNDFORMAT_FREQ_SUSPECTED_64000&t;0x07
DECL|macro|SOUNDFORMAT_FLAG_16BIT
mdefine_line|#define SOUNDFORMAT_FLAG_16BIT&t;0x0010
DECL|macro|SOUNDFORMAT_FLAG_2CHANNELS
mdefine_line|#define SOUNDFORMAT_FLAG_2CHANNELS&t;0x0020
multiline_comment|/* recording area (see also: playback bit flag definitions) */
DECL|macro|IDX_IO_REC_FLAGS
mdefine_line|#define IDX_IO_REC_FLAGS&t;0x20 /* ?? */
DECL|macro|IDX_IO_REC_IRQMASK
mdefine_line|#define IDX_IO_REC_IRQMASK&t;0x22 /* ?? */
DECL|macro|IRQ_REC_SOMETHING
mdefine_line|#define IRQ_REC_SOMETHING&t;&t;0x0001 /* something &amp; ACK */
DECL|macro|IRQ_FINISHED_RECBUF_1
mdefine_line|#define IRQ_FINISHED_RECBUF_1&t;&t;0x0002 /* 1st dmabuf finished &amp; ACK */
DECL|macro|IRQ_FINISHED_RECBUF_2
mdefine_line|#define IRQ_FINISHED_RECBUF_2&t;&t;0x0004 /* 2nd dmabuf finished &amp; ACK */
multiline_comment|/* hmm, maybe these are just the corresponding *recording* flags ?&n;   * but OTOH they are most likely at port 0x22 instead */
DECL|macro|IRQMASK_SOME_STATUS_1
mdefine_line|#define IRQMASK_SOME_STATUS_1&t;&t;0x0008 /* &bslash; related bits */
DECL|macro|IRQMASK_SOME_STATUS_2
mdefine_line|#define IRQMASK_SOME_STATUS_2&t;&t;0x0010 /* / (checked together in loop) */
DECL|macro|IDX_IO_REC_DMA_START_1
mdefine_line|#define IDX_IO_REC_DMA_START_1  0x24
DECL|macro|IDX_IO_REC_DMA_START_2
mdefine_line|#define IDX_IO_REC_DMA_START_2  0x28
DECL|macro|IDX_IO_REC_DMA_LEN_1
mdefine_line|#define IDX_IO_REC_DMA_LEN_1    0x2c
DECL|macro|IDX_IO_REC_DMA_LEN_2
mdefine_line|#define IDX_IO_REC_DMA_LEN_2    0x2e
DECL|macro|IDX_IO_REC_DMA_CURRPOS
mdefine_line|#define IDX_IO_REC_DMA_CURRPOS  0x30
DECL|macro|IDX_IO_REC_DMA_CURROFS
mdefine_line|#define IDX_IO_REC_DMA_CURROFS  0x34
DECL|macro|IDX_IO_REC_SOUNDFORMAT
mdefine_line|#define IDX_IO_REC_SOUNDFORMAT  0x36
multiline_comment|/* some third area ? (after playback and recording) */
DECL|macro|IDX_IO_SOMETHING_FLAGS
mdefine_line|#define IDX_IO_SOMETHING_FLAGS&t;0x40 /* gets set to 0x34 just like port 0x0 and 0x20 on card init */
multiline_comment|/* general */
DECL|macro|IDX_IO_60H
mdefine_line|#define IDX_IO_60H&t;&t;0x60 /* writing 0xffff returns 0xffff */
DECL|macro|IDX_IO_62H
mdefine_line|#define IDX_IO_62H&t;&t;0x62 /* writing to WORD 0x0062 can hang the box ! --&gt; responsible for IRQ management as a whole ?? */
DECL|macro|IDX_IO_IRQ63H
mdefine_line|#define IDX_IO_IRQ63H&t;&t;0x63 /* FIXME !! */
DECL|macro|IO_IRQ63H_SOMETHING
mdefine_line|#define IO_IRQ63H_SOMETHING&t;&t;0x04 /* being set in IRQ handler in case port 0x00 had 0x0020 set upon IRQ handler */
DECL|macro|IDX_IO_IRQSTATUS
mdefine_line|#define IDX_IO_IRQSTATUS        0x64
DECL|macro|IRQ_PLAYBACK
mdefine_line|#define IRQ_PLAYBACK&t;&t;&t;0x0001
DECL|macro|IRQ_RECORDING
mdefine_line|#define IRQ_RECORDING&t;&t;&t;0x0002
DECL|macro|IRQ_MPU401
mdefine_line|#define IRQ_MPU401&t;&t;&t;0x0010
DECL|macro|IRQ_SOMEIRQ
mdefine_line|#define IRQ_SOMEIRQ&t;&t;&t;0x0020 /* ???? */
DECL|macro|IRQ_WHO_KNOWS_UNUSED
mdefine_line|#define IRQ_WHO_KNOWS_UNUSED&t;&t;0x00e0 /* probably unused */
DECL|macro|IDX_IO_66H
mdefine_line|#define IDX_IO_66H&t;&t;0x66    /* writing 0xffff returns 0x0000 */
DECL|macro|IDX_IO_SOME_VALUE
mdefine_line|#define IDX_IO_SOME_VALUE&t;0x68&t;/* this is always set to 0x3ff, and writable; maybe some buffer limit, but I couldn&squot;t find out more */
DECL|macro|IDX_IO_6AH
mdefine_line|#define IDX_IO_6AH&t;&t;0x6A&t;/* this WORD can be set to have bits 0x0028 activated; actually inhibits PCM playback !!! maybe power management ?? */
DECL|macro|IDX_IO_6CH
mdefine_line|#define IDX_IO_6CH&t;&t;0x6C&t;/* this WORD can have all its bits activated ? */
DECL|macro|IDX_IO_6EH
mdefine_line|#define IDX_IO_6EH&t;&t;0x6E&t;/* writing 0xffff returns 0x83fe */
multiline_comment|/* further I/O indices not saved/restored, so probably not used */
multiline_comment|/*** I/O 2 area port indices ***/
multiline_comment|/* (only 0x06 of 0x08 bytes saved/restored by Windows driver) */
DECL|macro|IDX_IO2_LEGACY_ADDR
mdefine_line|#define IDX_IO2_LEGACY_ADDR&t;0x04
DECL|macro|LEGACY_SOMETHING
mdefine_line|#define LEGACY_SOMETHING&t;&t;0x01 /* OPL3 ?? */
DECL|macro|LEGACY_JOY
mdefine_line|#define LEGACY_JOY&t;&t;&t;0x08
multiline_comment|/*** mixer I/O area port indices ***/
multiline_comment|/* (only 0x22 of 0x40 bytes saved/restored by Windows driver)&n; * generally spoken: AC97 register index = AZF3328 mixer reg index + 2&n; * (in other words: AZF3328 NOT fully AC97 compliant) */
DECL|macro|MIXER_VOLUME_RIGHT_MASK
mdefine_line|#define MIXER_VOLUME_RIGHT_MASK&t;0x001f
DECL|macro|MIXER_VOLUME_LEFT_MASK
mdefine_line|#define MIXER_VOLUME_LEFT_MASK&t;0x1f00
DECL|macro|MIXER_MUTE_MASK
mdefine_line|#define MIXER_MUTE_MASK&t;&t;0x8000
DECL|macro|IDX_MIXER_RESET
mdefine_line|#define IDX_MIXER_RESET&t;&t;0x00 /* does NOT seem to have AC97 ID bits */
DECL|macro|IDX_MIXER_PLAY_MASTER
mdefine_line|#define IDX_MIXER_PLAY_MASTER   0x02
DECL|macro|IDX_MIXER_MODEMOUT
mdefine_line|#define IDX_MIXER_MODEMOUT      0x04
DECL|macro|IDX_MIXER_BASSTREBLE
mdefine_line|#define IDX_MIXER_BASSTREBLE    0x06
DECL|macro|MIXER_BASSTREBLE_TREBLE_VOLUME_MASK
mdefine_line|#define MIXER_BASSTREBLE_TREBLE_VOLUME_MASK&t;0x000e
DECL|macro|MIXER_BASSTREBLE_BASS_VOLUME_MASK
mdefine_line|#define MIXER_BASSTREBLE_BASS_VOLUME_MASK&t;0x0e00
DECL|macro|IDX_MIXER_PCBEEP
mdefine_line|#define IDX_MIXER_PCBEEP        0x08
DECL|macro|IDX_MIXER_MODEMIN
mdefine_line|#define IDX_MIXER_MODEMIN       0x0a
DECL|macro|IDX_MIXER_MIC
mdefine_line|#define IDX_MIXER_MIC           0x0c
DECL|macro|MIXER_MIC_MICGAIN_20DB_ENHANCEMENT_MASK
mdefine_line|#define MIXER_MIC_MICGAIN_20DB_ENHANCEMENT_MASK&t;0x0040
DECL|macro|IDX_MIXER_LINEIN
mdefine_line|#define IDX_MIXER_LINEIN        0x0e
DECL|macro|IDX_MIXER_CDAUDIO
mdefine_line|#define IDX_MIXER_CDAUDIO       0x10
DECL|macro|IDX_MIXER_VIDEO
mdefine_line|#define IDX_MIXER_VIDEO         0x12
DECL|macro|IDX_MIXER_AUX
mdefine_line|#define IDX_MIXER_AUX           0x14
DECL|macro|IDX_MIXER_WAVEOUT
mdefine_line|#define IDX_MIXER_WAVEOUT       0x16
DECL|macro|IDX_MIXER_FMSYNTH
mdefine_line|#define IDX_MIXER_FMSYNTH       0x18
DECL|macro|IDX_MIXER_REC_SELECT
mdefine_line|#define IDX_MIXER_REC_SELECT    0x1a
DECL|macro|MIXER_REC_SELECT_MIC
mdefine_line|#define MIXER_REC_SELECT_MIC&t;&t;0x00
DECL|macro|MIXER_REC_SELECT_CD
mdefine_line|#define MIXER_REC_SELECT_CD&t;&t;0x01
DECL|macro|MIXER_REC_SELECT_VIDEO
mdefine_line|#define MIXER_REC_SELECT_VIDEO&t;0x02
DECL|macro|MIXER_REC_SELECT_AUX
mdefine_line|#define MIXER_REC_SELECT_AUX&t;&t;0x03
DECL|macro|MIXER_REC_SELECT_LINEIN
mdefine_line|#define MIXER_REC_SELECT_LINEIN&t;0x04
DECL|macro|MIXER_REC_SELECT_MIXSTEREO
mdefine_line|#define MIXER_REC_SELECT_MIXSTEREO&t;0x05
DECL|macro|MIXER_REC_SELECT_MIXMONO
mdefine_line|#define MIXER_REC_SELECT_MIXMONO&t;0x06
DECL|macro|MIXER_REC_SELECT_MONOIN
mdefine_line|#define MIXER_REC_SELECT_MONOIN&t;0x07
DECL|macro|IDX_MIXER_REC_VOLUME
mdefine_line|#define IDX_MIXER_REC_VOLUME    0x1c
DECL|macro|IDX_MIXER_ADVCTL1
mdefine_line|#define IDX_MIXER_ADVCTL1       0x1e
multiline_comment|/* unlisted bits are unmodifiable */
DECL|macro|MIXER_ADVCTL1_3DWIDTH_MASK
mdefine_line|#define MIXER_ADVCTL1_3DWIDTH_MASK&t;0x000e
DECL|macro|MIXER_ADVCTL1_HIFI3D_MASK
mdefine_line|#define MIXER_ADVCTL1_HIFI3D_MASK&t;0x0300
DECL|macro|IDX_MIXER_ADVCTL2
mdefine_line|#define IDX_MIXER_ADVCTL2       0x20 /* resembles AC97_GENERAL_PURPOSE reg ! */
multiline_comment|/* unlisted bits are unmodifiable */
DECL|macro|MIXER_ADVCTL2_BIT7
mdefine_line|#define MIXER_ADVCTL2_BIT7&t;&t;0x0080 /* WaveOut 3D Bypass ? mutes WaveOut at LineOut */
DECL|macro|MIXER_ADVCTL2_BIT8
mdefine_line|#define MIXER_ADVCTL2_BIT8&t;&t;0x0100 /* is this Modem Out Select ? */
DECL|macro|MIXER_ADVCTL2_BIT9
mdefine_line|#define MIXER_ADVCTL2_BIT9&t;&t;0x0200 /* Mono Select Source ? */
DECL|macro|MIXER_ADVCTL2_BIT13
mdefine_line|#define MIXER_ADVCTL2_BIT13&t;&t;0x2000 /* 3D enable ? */
DECL|macro|MIXER_ADVCTL2_BIT15
mdefine_line|#define MIXER_ADVCTL2_BIT15&t;&t;0x8000 /* unknown */
DECL|macro|IDX_MIXER_SOMETHING30H
mdefine_line|#define IDX_MIXER_SOMETHING30H&t;0x30 /* used, but unknown ??? */
multiline_comment|/* driver internal flags */
DECL|macro|SET_CHAN_LEFT
mdefine_line|#define SET_CHAN_LEFT&t;1
DECL|macro|SET_CHAN_RIGHT
mdefine_line|#define SET_CHAN_RIGHT&t;2
macro_line|#endif /* __SOUND_AZF3328_H  */
eof
