multiline_comment|/* Hewlett-Packard Harmony audio driver&n; * Copyright (C) 2004, Kyle McMartin &lt;kyle@parisc-linux.org&gt;&n; */
macro_line|#ifndef __HARMONY_H__
DECL|macro|__HARMONY_H__
mdefine_line|#define __HARMONY_H__
DECL|struct|harmony_buffer
r_struct
id|harmony_buffer
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|buf
r_int
id|buf
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|coherent
r_int
id|coherent
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_card_harmony
r_typedef
r_struct
id|snd_card_harmony
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|hpa
r_int
r_int
id|hpa
suffix:semicolon
multiline_comment|/* hard physical address */
DECL|member|iobase
r_void
id|__iomem
op_star
id|iobase
suffix:semicolon
multiline_comment|/* remapped io address */
DECL|member|dev
r_struct
id|parisc_device
op_star
id|dev
suffix:semicolon
r_struct
(brace
DECL|member|gain
id|u32
id|gain
suffix:semicolon
DECL|member|rate
id|u32
id|rate
suffix:semicolon
DECL|member|format
id|u32
id|format
suffix:semicolon
DECL|member|stereo
id|u32
id|stereo
suffix:semicolon
DECL|member|playing
r_int
id|playing
suffix:semicolon
DECL|member|capturing
r_int
id|capturing
suffix:semicolon
DECL|member|st
)brace
id|st
suffix:semicolon
DECL|member|dma
r_struct
id|snd_dma_device
id|dma
suffix:semicolon
multiline_comment|/* playback/capture */
DECL|member|pbuf
r_struct
id|harmony_buffer
id|pbuf
suffix:semicolon
DECL|member|cbuf
r_struct
id|harmony_buffer
id|cbuf
suffix:semicolon
DECL|member|gdma
r_struct
id|snd_dma_buffer
id|gdma
suffix:semicolon
multiline_comment|/* graveyard */
DECL|member|sdma
r_struct
id|snd_dma_buffer
id|sdma
suffix:semicolon
multiline_comment|/* silence */
r_struct
(brace
DECL|member|play_intr
r_int
r_int
id|play_intr
suffix:semicolon
DECL|member|rec_intr
r_int
r_int
id|rec_intr
suffix:semicolon
DECL|member|graveyard_intr
r_int
r_int
id|graveyard_intr
suffix:semicolon
DECL|member|silence_intr
r_int
r_int
id|silence_intr
suffix:semicolon
DECL|member|stats
)brace
id|stats
suffix:semicolon
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|psubs
id|snd_pcm_substream_t
op_star
id|psubs
suffix:semicolon
DECL|member|csubs
id|snd_pcm_substream_t
op_star
id|csubs
suffix:semicolon
DECL|member|proc
id|snd_info_entry_t
op_star
id|proc
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|mixer_lock
id|spinlock_t
id|mixer_lock
suffix:semicolon
DECL|typedef|harmony_t
)brace
id|harmony_t
suffix:semicolon
DECL|macro|MAX_PCM_DEVICES
mdefine_line|#define MAX_PCM_DEVICES     1
DECL|macro|MAX_PCM_SUBSTREAMS
mdefine_line|#define MAX_PCM_SUBSTREAMS  4
DECL|macro|MAX_MIDI_DEVICES
mdefine_line|#define MAX_MIDI_DEVICES    0
DECL|macro|HARMONY_SIZE
mdefine_line|#define HARMONY_SIZE       64
DECL|macro|BUF_SIZE
mdefine_line|#define BUF_SIZE     PAGE_SIZE
DECL|macro|MAX_BUFS
mdefine_line|#define MAX_BUFS     10
DECL|macro|MAX_BUF_SIZE
mdefine_line|#define MAX_BUF_SIZE (MAX_BUFS * BUF_SIZE)
DECL|macro|PLAYBACK_BUFS
mdefine_line|#define PLAYBACK_BUFS    MAX_BUFS
DECL|macro|RECORD_BUFS
mdefine_line|#define RECORD_BUFS      MAX_BUFS
DECL|macro|GRAVEYARD_BUFS
mdefine_line|#define GRAVEYARD_BUFS   1
DECL|macro|GRAVEYARD_BUFSZ
mdefine_line|#define GRAVEYARD_BUFSZ  (GRAVEYARD_BUFS*BUF_SIZE)
DECL|macro|SILENCE_BUFS
mdefine_line|#define SILENCE_BUFS     1
DECL|macro|SILENCE_BUFSZ
mdefine_line|#define SILENCE_BUFSZ    (SILENCE_BUFS*BUF_SIZE)
DECL|macro|HARMONY_ID
mdefine_line|#define HARMONY_ID       0x000
DECL|macro|HARMONY_RESET
mdefine_line|#define HARMONY_RESET    0x004
DECL|macro|HARMONY_CNTL
mdefine_line|#define HARMONY_CNTL     0x008
DECL|macro|HARMONY_GAINCTL
mdefine_line|#define HARMONY_GAINCTL  0x00c
DECL|macro|HARMONY_PNXTADD
mdefine_line|#define HARMONY_PNXTADD  0x010
DECL|macro|HARMONY_PCURADD
mdefine_line|#define HARMONY_PCURADD  0x014
DECL|macro|HARMONY_RNXTADD
mdefine_line|#define HARMONY_RNXTADD  0x018
DECL|macro|HARMONY_RCURADD
mdefine_line|#define HARMONY_RCURADD  0x01c
DECL|macro|HARMONY_DSTATUS
mdefine_line|#define HARMONY_DSTATUS  0x020
DECL|macro|HARMONY_OV
mdefine_line|#define HARMONY_OV       0x024
DECL|macro|HARMONY_PIO
mdefine_line|#define HARMONY_PIO      0x028
DECL|macro|HARMONY_DIAG
mdefine_line|#define HARMONY_DIAG     0x03c
DECL|macro|HARMONY_CNTL_C
mdefine_line|#define HARMONY_CNTL_C          0x80000000
DECL|macro|HARMONY_CNTL_ST
mdefine_line|#define HARMONY_CNTL_ST         0x00000020
DECL|macro|HARMONY_CNTL_44100
mdefine_line|#define HARMONY_CNTL_44100      0x00000015      /* HARMONY_SR_44KHZ */
DECL|macro|HARMONY_CNTL_8000
mdefine_line|#define HARMONY_CNTL_8000       0x00000008      /* HARMONY_SR_8KHZ */
DECL|macro|HARMONY_DSTATUS_ID
mdefine_line|#define HARMONY_DSTATUS_ID      0x00000000 /* interrupts off */
DECL|macro|HARMONY_DSTATUS_PN
mdefine_line|#define HARMONY_DSTATUS_PN      0x00000200 /* playback fill */
DECL|macro|HARMONY_DSTATUS_RN
mdefine_line|#define HARMONY_DSTATUS_RN      0x00000002 /* record fill */
DECL|macro|HARMONY_DSTATUS_IE
mdefine_line|#define HARMONY_DSTATUS_IE      0x80000000 /* interrupts on */
DECL|macro|HARMONY_DF_16BIT_LINEAR
mdefine_line|#define HARMONY_DF_16BIT_LINEAR 0x00000000
DECL|macro|HARMONY_DF_8BIT_ULAW
mdefine_line|#define HARMONY_DF_8BIT_ULAW    0x00000001
DECL|macro|HARMONY_DF_8BIT_ALAW
mdefine_line|#define HARMONY_DF_8BIT_ALAW    0x00000002
DECL|macro|HARMONY_SS_MONO
mdefine_line|#define HARMONY_SS_MONO         0x00000000
DECL|macro|HARMONY_SS_STEREO
mdefine_line|#define HARMONY_SS_STEREO       0x00000001
DECL|macro|HARMONY_GAIN_SILENCE
mdefine_line|#define HARMONY_GAIN_SILENCE    0x00F00FFF
DECL|macro|HARMONY_GAIN_DEFAULT
mdefine_line|#define HARMONY_GAIN_DEFAULT    0x0FF00000
DECL|macro|HARMONY_GAIN_HE_SHIFT
mdefine_line|#define HARMONY_GAIN_HE_SHIFT   27
DECL|macro|HARMONY_GAIN_HE_MASK
mdefine_line|#define HARMONY_GAIN_HE_MASK    (1 &lt;&lt; HARMONY_GAIN_HE_SHIFT)
DECL|macro|HARMONY_GAIN_LE_SHIFT
mdefine_line|#define HARMONY_GAIN_LE_SHIFT   26
DECL|macro|HARMONY_GAIN_LE_MASK
mdefine_line|#define HARMONY_GAIN_LE_MASK    (1 &lt;&lt; HARMONY_GAIN_LE_SHIFT)
DECL|macro|HARMONY_GAIN_SE_SHIFT
mdefine_line|#define HARMONY_GAIN_SE_SHIFT   25
DECL|macro|HARMONY_GAIN_SE_MASK
mdefine_line|#define HARMONY_GAIN_SE_MASK    (1 &lt;&lt; HARMONY_GAIN_SE_SHIFT)
DECL|macro|HARMONY_GAIN_IS_SHIFT
mdefine_line|#define HARMONY_GAIN_IS_SHIFT   24
DECL|macro|HARMONY_GAIN_IS_MASK
mdefine_line|#define HARMONY_GAIN_IS_MASK    (1 &lt;&lt; HARMONY_GAIN_IS_SHIFT)
DECL|macro|HARMONY_GAIN_MA
mdefine_line|#define HARMONY_GAIN_MA         0x0f
DECL|macro|HARMONY_GAIN_MA_SHIFT
mdefine_line|#define HARMONY_GAIN_MA_SHIFT   20
DECL|macro|HARMONY_GAIN_MA_MASK
mdefine_line|#define HARMONY_GAIN_MA_MASK    (HARMONY_GAIN_MA &lt;&lt; HARMONY_GAIN_MA_SHIFT)
DECL|macro|HARMONY_GAIN_IN
mdefine_line|#define HARMONY_GAIN_IN         0x0f
DECL|macro|HARMONY_GAIN_LI_SHIFT
mdefine_line|#define HARMONY_GAIN_LI_SHIFT   16
DECL|macro|HARMONY_GAIN_LI_MASK
mdefine_line|#define HARMONY_GAIN_LI_MASK    (HARMONY_GAIN_IN &lt;&lt; HARMONY_GAIN_LI_SHIFT)
DECL|macro|HARMONY_GAIN_RI_SHIFT
mdefine_line|#define HARMONY_GAIN_RI_SHIFT   12
DECL|macro|HARMONY_GAIN_RI_MASK
mdefine_line|#define HARMONY_GAIN_RI_MASK    (HARMONY_GAIN_IN &lt;&lt; HARMONY_GAIN_RI_SHIFT)
DECL|macro|HARMONY_GAIN_OUT
mdefine_line|#define HARMONY_GAIN_OUT        0x3f
DECL|macro|HARMONY_GAIN_LO_SHIFT
mdefine_line|#define HARMONY_GAIN_LO_SHIFT   6
DECL|macro|HARMONY_GAIN_LO_MASK
mdefine_line|#define HARMONY_GAIN_LO_MASK    (HARMONY_GAIN_OUT &lt;&lt; HARMONY_GAIN_LO_SHIFT)
DECL|macro|HARMONY_GAIN_RO_SHIFT
mdefine_line|#define HARMONY_GAIN_RO_SHIFT   0
DECL|macro|HARMONY_GAIN_RO_MASK
mdefine_line|#define HARMONY_GAIN_RO_MASK    (HARMONY_GAIN_OUT &lt;&lt; HARMONY_GAIN_RO_SHIFT)
DECL|macro|HARMONY_MAX_OUT
mdefine_line|#define HARMONY_MAX_OUT (HARMONY_GAIN_RO_MASK &gt;&gt; HARMONY_GAIN_RO_SHIFT)
DECL|macro|HARMONY_MAX_IN
mdefine_line|#define HARMONY_MAX_IN  (HARMONY_GAIN_RI_MASK &gt;&gt; HARMONY_GAIN_RI_SHIFT)
DECL|macro|HARMONY_MAX_MON
mdefine_line|#define HARMONY_MAX_MON (HARMONY_GAIN_MA_MASK &gt;&gt; HARMONY_GAIN_MA_SHIFT)
DECL|macro|HARMONY_SR_8KHZ
mdefine_line|#define HARMONY_SR_8KHZ         0x08
DECL|macro|HARMONY_SR_16KHZ
mdefine_line|#define HARMONY_SR_16KHZ        0x09
DECL|macro|HARMONY_SR_27KHZ
mdefine_line|#define HARMONY_SR_27KHZ        0x0A
DECL|macro|HARMONY_SR_32KHZ
mdefine_line|#define HARMONY_SR_32KHZ        0x0B
DECL|macro|HARMONY_SR_48KHZ
mdefine_line|#define HARMONY_SR_48KHZ        0x0E
DECL|macro|HARMONY_SR_9KHZ
mdefine_line|#define HARMONY_SR_9KHZ         0x0F
DECL|macro|HARMONY_SR_5KHZ
mdefine_line|#define HARMONY_SR_5KHZ         0x10
DECL|macro|HARMONY_SR_11KHZ
mdefine_line|#define HARMONY_SR_11KHZ        0x11
DECL|macro|HARMONY_SR_18KHZ
mdefine_line|#define HARMONY_SR_18KHZ        0x12
DECL|macro|HARMONY_SR_22KHZ
mdefine_line|#define HARMONY_SR_22KHZ        0x13
DECL|macro|HARMONY_SR_37KHZ
mdefine_line|#define HARMONY_SR_37KHZ        0x14
DECL|macro|HARMONY_SR_44KHZ
mdefine_line|#define HARMONY_SR_44KHZ        0x15
DECL|macro|HARMONY_SR_33KHZ
mdefine_line|#define HARMONY_SR_33KHZ        0x16
DECL|macro|HARMONY_SR_6KHZ
mdefine_line|#define HARMONY_SR_6KHZ         0x17
macro_line|#endif /* __HARMONY_H__ */
eof
