multiline_comment|/*&n;    Aureal Advantage Soundcard driver.&n; */
DECL|macro|CHIP_AU8810
mdefine_line|#define CHIP_AU8810
DECL|macro|CARD_NAME
mdefine_line|#define CARD_NAME &quot;Aureal Advantage 3D Sound Processor&quot;
DECL|macro|CARD_NAME_SHORT
mdefine_line|#define CARD_NAME_SHORT &quot;au8810&quot;
DECL|macro|NR_ADB
mdefine_line|#define NR_ADB&t;&t;0x10
DECL|macro|NR_WT
mdefine_line|#define NR_WT&t;&t;0x00
DECL|macro|NR_SRC
mdefine_line|#define NR_SRC&t;&t;0x10
DECL|macro|NR_A3D
mdefine_line|#define NR_A3D&t;&t;0x10
DECL|macro|NR_MIXIN
mdefine_line|#define NR_MIXIN&t;0x20
DECL|macro|NR_MIXOUT
mdefine_line|#define NR_MIXOUT&t;0x10
multiline_comment|/* ADBDMA */
DECL|macro|VORTEX_ADBDMA_STAT
mdefine_line|#define VORTEX_ADBDMA_STAT 0x27e00&t;/* read only, subbuffer, DMA pos */
DECL|macro|POS_MASK
mdefine_line|#define&t;&t;POS_MASK 0x00000fff
DECL|macro|POS_SHIFT
mdefine_line|#define     POS_SHIFT 0x0
DECL|macro|ADB_SUBBUF_MASK
mdefine_line|#define &t;ADB_SUBBUF_MASK 0x00003000&t;/* ADB only. */
DECL|macro|ADB_SUBBUF_SHIFT
mdefine_line|#define     ADB_SUBBUF_SHIFT 0xc&t;/* ADB only. */
DECL|macro|VORTEX_ADBDMA_CTRL
mdefine_line|#define VORTEX_ADBDMA_CTRL 0x27180&t;/* write only; format, flags, DMA pos */
DECL|macro|OFFSET_MASK
mdefine_line|#define&t;&t;OFFSET_MASK 0x00000fff
DECL|macro|OFFSET_SHIFT
mdefine_line|#define     OFFSET_SHIFT 0x0
DECL|macro|IE_MASK
mdefine_line|#define&t;&t;IE_MASK 0x00001000&t;/* interrupt enable. */
DECL|macro|IE_SHIFT
mdefine_line|#define     IE_SHIFT 0xc
DECL|macro|DIR_MASK
mdefine_line|#define     DIR_MASK 0x00002000&t;/* Direction */
DECL|macro|DIR_SHIFT
mdefine_line|#define     DIR_SHIFT 0xd
DECL|macro|FMT_MASK
mdefine_line|#define&t;&t;FMT_MASK 0x0003c000
DECL|macro|FMT_SHIFT
mdefine_line|#define&t;&t;FMT_SHIFT 0xe
singleline_comment|// The ADB masks and shift also are valid for the wtdma, except if specified otherwise.
DECL|macro|VORTEX_ADBDMA_BUFCFG0
mdefine_line|#define VORTEX_ADBDMA_BUFCFG0 0x27100
DECL|macro|VORTEX_ADBDMA_BUFCFG1
mdefine_line|#define VORTEX_ADBDMA_BUFCFG1 0x27104
DECL|macro|VORTEX_ADBDMA_BUFBASE
mdefine_line|#define VORTEX_ADBDMA_BUFBASE 0x27000
DECL|macro|VORTEX_ADBDMA_START
mdefine_line|#define VORTEX_ADBDMA_START 0x27c00&t;/* Which subbuffer starts */
DECL|macro|VORTEX_ADBDMA_STATUS
mdefine_line|#define VORTEX_ADBDMA_STATUS 0x27A90&t;/* stored at AdbDma-&gt;this_10 / 2 DWORD in size. */
multiline_comment|/* WTDMA */
DECL|macro|VORTEX_WTDMA_CTRL
mdefine_line|#define VORTEX_WTDMA_CTRL 0x27fd8&t;/* format, DMA pos */
DECL|macro|VORTEX_WTDMA_STAT
mdefine_line|#define VORTEX_WTDMA_STAT 0x27fe8&t;/* DMA subbuf, DMA pos */
DECL|macro|WT_SUBBUF_MASK
mdefine_line|#define     WT_SUBBUF_MASK 0x3
DECL|macro|WT_SUBBUF_SHIFT
mdefine_line|#define     WT_SUBBUF_SHIFT 0xc
DECL|macro|VORTEX_WTDMA_BUFBASE
mdefine_line|#define VORTEX_WTDMA_BUFBASE 0x27fc0
DECL|macro|VORTEX_WTDMA_BUFCFG0
mdefine_line|#define VORTEX_WTDMA_BUFCFG0 0x27fd0
DECL|macro|VORTEX_WTDMA_BUFCFG1
mdefine_line|#define VORTEX_WTDMA_BUFCFG1 0x27fd4
DECL|macro|VORTEX_WTDMA_START
mdefine_line|#define VORTEX_WTDMA_START 0x27fe4&t;/* which subbuffer is first */
multiline_comment|/* ADB */
DECL|macro|VORTEX_ADB_SR
mdefine_line|#define VORTEX_ADB_SR 0x28400&t;/* Samplerates enable/disable */
DECL|macro|VORTEX_ADB_RTBASE
mdefine_line|#define VORTEX_ADB_RTBASE 0x28000
DECL|macro|VORTEX_ADB_RTBASE_COUNT
mdefine_line|#define VORTEX_ADB_RTBASE_COUNT 173
DECL|macro|VORTEX_ADB_CHNBASE
mdefine_line|#define VORTEX_ADB_CHNBASE 0x282b4
DECL|macro|VORTEX_ADB_CHNBASE_COUNT
mdefine_line|#define VORTEX_ADB_CHNBASE_COUNT 24
DECL|macro|ROUTE_MASK
mdefine_line|#define &t;ROUTE_MASK&t;0xffff
DECL|macro|SOURCE_MASK
mdefine_line|#define&t;&t;SOURCE_MASK&t;0xff00
DECL|macro|ADB_MASK
mdefine_line|#define     ADB_MASK   0xff
DECL|macro|ADB_SHIFT
mdefine_line|#define&t;&t;ADB_SHIFT 0x8
multiline_comment|/* ADB address */
DECL|macro|OFFSET_ADBDMA
mdefine_line|#define&t;&t;OFFSET_ADBDMA&t;0x00
DECL|macro|OFFSET_SRCIN
mdefine_line|#define&t;&t;OFFSET_SRCIN&t;0x40
DECL|macro|OFFSET_SRCOUT
mdefine_line|#define&t;&t;OFFSET_SRCOUT&t;0x20
DECL|macro|OFFSET_MIXIN
mdefine_line|#define&t;&t;OFFSET_MIXIN&t;0x50
DECL|macro|OFFSET_MIXOUT
mdefine_line|#define&t;&t;OFFSET_MIXOUT&t;0x30
DECL|macro|OFFSET_CODECIN
mdefine_line|#define&t;&t;OFFSET_CODECIN&t;0x70
DECL|macro|OFFSET_CODECOUT
mdefine_line|#define&t;&t;OFFSET_CODECOUT&t;0x88
DECL|macro|OFFSET_SPORTIN
mdefine_line|#define&t;&t;OFFSET_SPORTIN&t;0x78&t;/* ch 0x13 */
DECL|macro|OFFSET_SPORTOUT
mdefine_line|#define&t;&t;OFFSET_SPORTOUT&t;0x90
DECL|macro|OFFSET_SPDIFOUT
mdefine_line|#define&t;&t;OFFSET_SPDIFOUT&t;0x92&t;/* ch 0x14 check this! */
DECL|macro|OFFSET_EQIN
mdefine_line|#define&t;&t;OFFSET_EQIN&t;0xa0
DECL|macro|OFFSET_EQOUT
mdefine_line|#define&t;&t;OFFSET_EQOUT&t;0x7e&t;/* 2 routes on ch 0x11 */
DECL|macro|OFFSET_XTALKOUT
mdefine_line|#define&t;&t;OFFSET_XTALKOUT&t;0x66&t;/* crosstalk canceller (source) */
DECL|macro|OFFSET_XTALKIN
mdefine_line|#define&t;&t;OFFSET_XTALKIN&t;0x96&t;/* crosstalk canceller (sink) */
DECL|macro|OFFSET_A3DIN
mdefine_line|#define&t;&t;OFFSET_A3DIN&t;0x70&t;/* ADB sink. */
DECL|macro|OFFSET_A3DOUT
mdefine_line|#define&t;&t;OFFSET_A3DOUT&t;0xA6&t;/* ADB source. 2 routes per slice = 8 */
DECL|macro|OFFSET_EFXIN
mdefine_line|#define&t;&t;OFFSET_EFXIN&t;0x80&t;/* ADB sink. */
DECL|macro|OFFSET_EFXOUT
mdefine_line|#define&t;&t;OFFSET_EFXOUT&t;0x68&t;/* ADB source. */
multiline_comment|/* ADB route translate helper */
DECL|macro|ADB_DMA
mdefine_line|#define ADB_DMA(x) (x)
DECL|macro|ADB_SRCOUT
mdefine_line|#define ADB_SRCOUT(x) (x + OFFSET_SRCOUT)
DECL|macro|ADB_SRCIN
mdefine_line|#define ADB_SRCIN(x) (x + OFFSET_SRCIN)
DECL|macro|ADB_MIXOUT
mdefine_line|#define ADB_MIXOUT(x) (x + OFFSET_MIXOUT)
DECL|macro|ADB_MIXIN
mdefine_line|#define ADB_MIXIN(x) (x + OFFSET_MIXIN)
DECL|macro|ADB_CODECIN
mdefine_line|#define ADB_CODECIN(x) (x + OFFSET_CODECIN)
DECL|macro|ADB_CODECOUT
mdefine_line|#define ADB_CODECOUT(x) (x + OFFSET_CODECOUT)
DECL|macro|ADB_SPORTIN
mdefine_line|#define ADB_SPORTIN(x) (x + OFFSET_SPORTIN)
DECL|macro|ADB_SPORTOUT
mdefine_line|#define ADB_SPORTOUT(x) (x + OFFSET_SPORTOUT)
DECL|macro|ADB_SPDIFOUT
mdefine_line|#define ADB_SPDIFOUT(x)&t;(x + OFFSET_SPDIFOUT)
DECL|macro|ADB_EQIN
mdefine_line|#define ADB_EQIN(x) (x + OFFSET_EQIN)
DECL|macro|ADB_EQOUT
mdefine_line|#define ADB_EQOUT(x) (x + OFFSET_EQOUT)
DECL|macro|ADB_A3DOUT
mdefine_line|#define ADB_A3DOUT(x) (x + OFFSET_A3DOUT)&t;/* 0x10 A3D blocks */
DECL|macro|ADB_A3DIN
mdefine_line|#define ADB_A3DIN(x) (x + OFFSET_A3DIN)
DECL|macro|ADB_XTALKIN
mdefine_line|#define ADB_XTALKIN(x) (x + OFFSET_XTALKIN)
DECL|macro|ADB_XTALKOUT
mdefine_line|#define ADB_XTALKOUT(x) (x + OFFSET_XTALKOUT)
DECL|macro|MIX_OUTL
mdefine_line|#define MIX_OUTL    0xe
DECL|macro|MIX_OUTR
mdefine_line|#define MIX_OUTR    0xf
DECL|macro|MIX_INL
mdefine_line|#define MIX_INL     0x1e
DECL|macro|MIX_INR
mdefine_line|#define MIX_INR     0x1f
DECL|macro|MIX_DEFIGAIN
mdefine_line|#define MIX_DEFIGAIN 0x08&t;/* 0x8 =&gt; 6dB */
DECL|macro|MIX_DEFOGAIN
mdefine_line|#define MIX_DEFOGAIN 0x08
multiline_comment|/* MIXER */
DECL|macro|VORTEX_MIXER_SR
mdefine_line|#define VORTEX_MIXER_SR 0x21f00
DECL|macro|VORTEX_MIXER_CLIP
mdefine_line|#define VORTEX_MIXER_CLIP 0x21f80
DECL|macro|VORTEX_MIXER_CHNBASE
mdefine_line|#define VORTEX_MIXER_CHNBASE 0x21e40
DECL|macro|VORTEX_MIXER_RTBASE
mdefine_line|#define VORTEX_MIXER_RTBASE 0x21e00
DECL|macro|MIXER_RTBASE_SIZE
mdefine_line|#define &t;MIXER_RTBASE_SIZE 0x38
DECL|macro|VORTEX_MIX_ENIN
mdefine_line|#define VORTEX_MIX_ENIN 0x21a00&t;/* Input enable bits. 4 bits wide. */
DECL|macro|VORTEX_MIX_SMP
mdefine_line|#define VORTEX_MIX_SMP 0x21c00&t;/* AU8820: 0x9c00 */
multiline_comment|/* MIX */
DECL|macro|VORTEX_MIX_INVOL_A
mdefine_line|#define VORTEX_MIX_INVOL_A 0x21000&t;/* in? */
DECL|macro|VORTEX_MIX_INVOL_B
mdefine_line|#define VORTEX_MIX_INVOL_B 0x20000&t;/* out? */
DECL|macro|VORTEX_MIX_VOL_A
mdefine_line|#define VORTEX_MIX_VOL_A 0x21800
DECL|macro|VORTEX_MIX_VOL_B
mdefine_line|#define VORTEX_MIX_VOL_B 0x20800
DECL|macro|VOL_MIN
mdefine_line|#define &t;VOL_MIN 0x80&t;/* Input volume when muted. */
DECL|macro|VOL_MAX
mdefine_line|#define&t;&t;VOL_MAX 0x7f&t;/* FIXME: Not confirmed! Just guessed. */
multiline_comment|/* SRC */
DECL|macro|VORTEX_SRC_CHNBASE
mdefine_line|#define VORTEX_SRC_CHNBASE&t;&t;0x26c40
DECL|macro|VORTEX_SRC_RTBASE
mdefine_line|#define VORTEX_SRC_RTBASE&t;&t;0x26c00
DECL|macro|VORTEX_SRCBLOCK_SR
mdefine_line|#define VORTEX_SRCBLOCK_SR&t;&t;0x26cc0
DECL|macro|VORTEX_SRC_SOURCE
mdefine_line|#define VORTEX_SRC_SOURCE&t;&t;0x26cc4
DECL|macro|VORTEX_SRC_SOURCESIZE
mdefine_line|#define VORTEX_SRC_SOURCESIZE&t;0x26cc8
multiline_comment|/* Params&n;&t;0x26e00&t;: 1 U0&n;&t;0x26e40&t;: 2 CR&n;&t;0x26e80&t;: 3 U3&n;&t;0x26ec0&t;: 4 DRIFT1&n;&t;0x26f00 : 5 U1&n;&t;0x26f40&t;: 6 DRIFT2&n;&t;0x26f80&t;: 7 U2 : Target rate, direction&n;*/
DECL|macro|VORTEX_SRC_CONVRATIO
mdefine_line|#define VORTEX_SRC_CONVRATIO&t;0x26e40
DECL|macro|VORTEX_SRC_DRIFT0
mdefine_line|#define VORTEX_SRC_DRIFT0&t;&t;0x26e80
DECL|macro|VORTEX_SRC_DRIFT1
mdefine_line|#define VORTEX_SRC_DRIFT1&t;&t;0x26ec0
DECL|macro|VORTEX_SRC_DRIFT2
mdefine_line|#define VORTEX_SRC_DRIFT2&t;&t;0x26f40
DECL|macro|VORTEX_SRC_U0
mdefine_line|#define VORTEX_SRC_U0&t;&t;&t;0x26e00
DECL|macro|U0_SLOWLOCK
mdefine_line|#define&t;&t;U0_SLOWLOCK&t;&t;0x200
DECL|macro|VORTEX_SRC_U1
mdefine_line|#define VORTEX_SRC_U1&t;&t;&t;0x26f00
DECL|macro|VORTEX_SRC_U2
mdefine_line|#define VORTEX_SRC_U2&t;&t;&t;0x26f80
DECL|macro|VORTEX_SRC_DATA
mdefine_line|#define VORTEX_SRC_DATA&t;&t;&t;0x26800&t;/* 0xc800 */
DECL|macro|VORTEX_SRC_DATA0
mdefine_line|#define VORTEX_SRC_DATA0&t;&t;0x26000
multiline_comment|/* FIFO */
DECL|macro|VORTEX_FIFO_ADBCTRL
mdefine_line|#define VORTEX_FIFO_ADBCTRL 0x16100&t;/* Control bits. */
DECL|macro|VORTEX_FIFO_WTCTRL
mdefine_line|#define VORTEX_FIFO_WTCTRL 0x16000
DECL|macro|FIFO_RDONLY
mdefine_line|#define&t;&t;FIFO_RDONLY&t;0x00000001
DECL|macro|FIFO_CTRL
mdefine_line|#define&t;&t;FIFO_CTRL&t;0x00000002&t;/* Allow ctrl. ? */
DECL|macro|FIFO_VALID
mdefine_line|#define&t;&t;FIFO_VALID&t;0x00000010
DECL|macro|FIFO_EMPTY
mdefine_line|#define &t;FIFO_EMPTY&t;0x00000020
DECL|macro|FIFO_U0
mdefine_line|#define&t;&t;FIFO_U0&t;&t;0x00001000&t;/* Unknown. */
DECL|macro|FIFO_U1
mdefine_line|#define&t;&t;FIFO_U1&t;&t;0x00010000
DECL|macro|FIFO_SIZE_BITS
mdefine_line|#define&t;&t;FIFO_SIZE_BITS 5
DECL|macro|FIFO_SIZE
mdefine_line|#define&t;&t;FIFO_SIZE&t;(1&lt;&lt;FIFO_SIZE_BITS)&t;
singleline_comment|// 0x20
DECL|macro|FIFO_MASK
mdefine_line|#define &t;FIFO_MASK&t;(FIFO_SIZE-1)&t;
singleline_comment|//0x1f    /* at shift left 0xc */
singleline_comment|//#define       FIFO_MASK       0x1f    /* at shift left 0xb */
singleline_comment|//#define               FIFO_SIZE       0x20
DECL|macro|FIFO_BITS
mdefine_line|#define &t;FIFO_BITS&t;0x03880000
DECL|macro|VORTEX_FIFO_ADBDATA
mdefine_line|#define VORTEX_FIFO_ADBDATA&t;0x14000
DECL|macro|VORTEX_FIFO_WTDATA
mdefine_line|#define VORTEX_FIFO_WTDATA&t;0x10000
multiline_comment|/* CODEC */
DECL|macro|VORTEX_CODEC_CTRL
mdefine_line|#define VORTEX_CODEC_CTRL&t;0x29184
DECL|macro|VORTEX_CODEC_EN
mdefine_line|#define VORTEX_CODEC_EN&t;&t;0x29190
DECL|macro|EN_CODEC0
mdefine_line|#define&t;&t;EN_CODEC0&t;0x00000300
DECL|macro|EN_AC98
mdefine_line|#define &t;EN_AC98&t;&t;0x00000c00 /* Modem AC98 slots. */
DECL|macro|EN_CODEC1
mdefine_line|#define&t;&t;EN_CODEC1&t;0x00003000
DECL|macro|EN_CODEC
mdefine_line|#define&t;&t;EN_CODEC&t;(EN_CODEC0 | EN_CODEC1)
DECL|macro|EN_SPORT
mdefine_line|#define&t;&t;EN_SPORT&t;0x00030000
DECL|macro|EN_SPDIF
mdefine_line|#define&t;&t;EN_SPDIF&t;0x000c0000
DECL|macro|VORTEX_CODEC_CHN
mdefine_line|#define VORTEX_CODEC_CHN &t;0x29080
DECL|macro|VORTEX_CODEC_WRITE
mdefine_line|#define VORTEX_CODEC_WRITE&t;0x00800000
DECL|macro|VORTEX_CODEC_ADDSHIFT
mdefine_line|#define VORTEX_CODEC_ADDSHIFT &t;16
DECL|macro|VORTEX_CODEC_ADDMASK
mdefine_line|#define VORTEX_CODEC_ADDMASK&t;0x7f0000&t;/* 0x000f0000 */
DECL|macro|VORTEX_CODEC_DATSHIFT
mdefine_line|#define VORTEX_CODEC_DATSHIFT&t;0
DECL|macro|VORTEX_CODEC_DATMASK
mdefine_line|#define VORTEX_CODEC_DATMASK&t;0xffff
DECL|macro|VORTEX_CODEC_IO
mdefine_line|#define VORTEX_CODEC_IO&t;&t;0x29188
multiline_comment|/* SPDIF */
DECL|macro|VORTEX_SPDIF_FLAGS
mdefine_line|#define VORTEX_SPDIF_FLAGS&t;0x2205c
DECL|macro|VORTEX_SPDIF_CFG0
mdefine_line|#define VORTEX_SPDIF_CFG0&t;0x291D0
DECL|macro|VORTEX_SPDIF_CFG1
mdefine_line|#define VORTEX_SPDIF_CFG1&t;0x291D4
DECL|macro|VORTEX_SPDIF_SMPRATE
mdefine_line|#define VORTEX_SPDIF_SMPRATE&t;0x29194
multiline_comment|/* Sample timer */
DECL|macro|VORTEX_SMP_TIME
mdefine_line|#define VORTEX_SMP_TIME&t;&t;0x29198
DECL|macro|VORTEX_MODEM_CTRL
mdefine_line|#define VORTEX_MODEM_CTRL&t;0x291ac
multiline_comment|/* IRQ */
DECL|macro|VORTEX_IRQ_SOURCE
mdefine_line|#define VORTEX_IRQ_SOURCE 0x2a000&t;/* Interrupt source flags. */
DECL|macro|VORTEX_IRQ_CTRL
mdefine_line|#define VORTEX_IRQ_CTRL 0x2a004&t;/* Interrupt source mask. */
DECL|macro|VORTEX_STAT
mdefine_line|#define VORTEX_STAT&t;0x2a008&t;/* Status */
DECL|macro|VORTEX_CTRL
mdefine_line|#define VORTEX_CTRL&t;&t;0x2a00c
DECL|macro|CTRL_MIDI_EN
mdefine_line|#define &t;CTRL_MIDI_EN&t;0x00000001
DECL|macro|CTRL_MIDI_PORT
mdefine_line|#define &t;CTRL_MIDI_PORT&t;0x00000060
DECL|macro|CTRL_GAME_EN
mdefine_line|#define &t;CTRL_GAME_EN&t;0x00000008
DECL|macro|CTRL_GAME_PORT
mdefine_line|#define &t;CTRL_GAME_PORT&t;0x00000e00
singleline_comment|//#define       CTRL_IRQ_ENABLE 0x01004000
DECL|macro|CTRL_IRQ_ENABLE
mdefine_line|#define &t;CTRL_IRQ_ENABLE&t;0x00004000
multiline_comment|/* write: Timer period config / read: TIMER IRQ ack. */
DECL|macro|VORTEX_IRQ_STAT
mdefine_line|#define VORTEX_IRQ_STAT&t;&t;0x2919c
multiline_comment|/* DMA */
DECL|macro|VORTEX_ENGINE_CTRL
mdefine_line|#define VORTEX_ENGINE_CTRL&t;0x27ae8
DECL|macro|ENGINE_INIT
mdefine_line|#define &t;ENGINE_INIT&t;0x1380000
multiline_comment|/* MIDI */
multiline_comment|/* GAME. */
DECL|macro|VORTEX_MIDI_DATA
mdefine_line|#define VORTEX_MIDI_DATA&t;0x28800
DECL|macro|VORTEX_MIDI_CMD
mdefine_line|#define VORTEX_MIDI_CMD&t;&t;0x28804&t;/* Write command / Read status */
DECL|macro|VORTEX_CTRL2
mdefine_line|#define VORTEX_CTRL2&t;&t;0x2880c
DECL|macro|CTRL2_GAME_ADCMODE
mdefine_line|#define&t;&t;CTRL2_GAME_ADCMODE 0x40
DECL|macro|VORTEX_GAME_LEGACY
mdefine_line|#define VORTEX_GAME_LEGACY&t;0x28808
DECL|macro|VORTEX_GAME_AXIS
mdefine_line|#define VORTEX_GAME_AXIS&t;0x28810
DECL|macro|AXIS_SIZE
mdefine_line|#define&t;&t;AXIS_SIZE 4
DECL|macro|AXIS_RANGE
mdefine_line|#define&t;&t;AXIS_RANGE 0x1fff
eof
