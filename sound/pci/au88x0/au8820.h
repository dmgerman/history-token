multiline_comment|/*&n;    Aureal Vortex Soundcard driver.&n;&n;    IO addr collected from asp4core.vxd:&n;    function    address&n;    0005D5A0    13004&n;    00080674    14004&n;    00080AFF    12818&n;&n; */
DECL|macro|CHIP_AU8820
mdefine_line|#define CHIP_AU8820
DECL|macro|CARD_NAME
mdefine_line|#define CARD_NAME &quot;Aureal Vortex 3D Sound Processor&quot;
DECL|macro|CARD_NAME_SHORT
mdefine_line|#define CARD_NAME_SHORT &quot;au8820&quot;
multiline_comment|/* Number of ADB and WT channels */
DECL|macro|NR_ADB
mdefine_line|#define NR_ADB&t;&t;0x10
DECL|macro|NR_WT
mdefine_line|#define NR_WT&t;&t;0x20
DECL|macro|NR_SRC
mdefine_line|#define NR_SRC&t;&t;0x10
DECL|macro|NR_A3D
mdefine_line|#define NR_A3D&t;&t;0x00
DECL|macro|NR_MIXIN
mdefine_line|#define NR_MIXIN&t;0x10
DECL|macro|NR_MIXOUT
mdefine_line|#define NR_MIXOUT &t;0x10
multiline_comment|/* ADBDMA */
DECL|macro|VORTEX_ADBDMA_STAT
mdefine_line|#define VORTEX_ADBDMA_STAT 0x105c0&t;/* read only, subbuffer, DMA pos */
DECL|macro|POS_MASK
mdefine_line|#define&t;&t;POS_MASK 0x00000fff
DECL|macro|POS_SHIFT
mdefine_line|#define     POS_SHIFT 0x0
DECL|macro|ADB_SUBBUF_MASK
mdefine_line|#define &t;ADB_SUBBUF_MASK 0x00003000&t;/* ADB only. */
DECL|macro|ADB_SUBBUF_SHIFT
mdefine_line|#define     ADB_SUBBUF_SHIFT 0xc&t;/* ADB only. */
DECL|macro|VORTEX_ADBDMA_CTRL
mdefine_line|#define VORTEX_ADBDMA_CTRL 0x10580&t;/* write only, format, flags, DMA pos */
DECL|macro|OFFSET_MASK
mdefine_line|#define&t;&t;OFFSET_MASK 0x00000fff
DECL|macro|OFFSET_SHIFT
mdefine_line|#define     OFFSET_SHIFT 0x0
DECL|macro|IE_MASK
mdefine_line|#define&t;&t;IE_MASK 0x00001000&t;/* interrupt enable. */
DECL|macro|IE_SHIFT
mdefine_line|#define     IE_SHIFT 0xc
DECL|macro|DIR_MASK
mdefine_line|#define     DIR_MASK 0x00002000&t;/* Direction. */
DECL|macro|DIR_SHIFT
mdefine_line|#define     DIR_SHIFT 0xd
DECL|macro|FMT_MASK
mdefine_line|#define&t;&t;FMT_MASK 0x0003c000
DECL|macro|FMT_SHIFT
mdefine_line|#define&t;&t;FMT_SHIFT 0xe
singleline_comment|// The masks and shift also work for the wtdma, if not specified otherwise.
DECL|macro|VORTEX_ADBDMA_BUFCFG0
mdefine_line|#define VORTEX_ADBDMA_BUFCFG0 0x10400
DECL|macro|VORTEX_ADBDMA_BUFCFG1
mdefine_line|#define VORTEX_ADBDMA_BUFCFG1 0x10404
DECL|macro|VORTEX_ADBDMA_BUFBASE
mdefine_line|#define VORTEX_ADBDMA_BUFBASE 0x10200
DECL|macro|VORTEX_ADBDMA_START
mdefine_line|#define VORTEX_ADBDMA_START 0x106c0&t;/* Which subbuffer starts */
DECL|macro|VORTEX_ADBDMA_STATUS
mdefine_line|#define VORTEX_ADBDMA_STATUS 0x10600&t;/* stored at AdbDma-&gt;this_10 / 2 DWORD in size. */
multiline_comment|/* ADB */
DECL|macro|VORTEX_ADB_SR
mdefine_line|#define VORTEX_ADB_SR 0x10a00&t;/* Samplerates enable/disable */
DECL|macro|VORTEX_ADB_RTBASE
mdefine_line|#define VORTEX_ADB_RTBASE 0x10800
DECL|macro|VORTEX_ADB_RTBASE_COUNT
mdefine_line|#define VORTEX_ADB_RTBASE_COUNT 103
DECL|macro|VORTEX_ADB_CHNBASE
mdefine_line|#define VORTEX_ADB_CHNBASE 0x1099c
DECL|macro|VORTEX_ADB_CHNBASE_COUNT
mdefine_line|#define VORTEX_ADB_CHNBASE_COUNT 22
DECL|macro|ROUTE_MASK
mdefine_line|#define &t;ROUTE_MASK&t;0x3fff
DECL|macro|ADB_MASK
mdefine_line|#define     ADB_MASK   0x7f
DECL|macro|ADB_SHIFT
mdefine_line|#define&t;&t;ADB_SHIFT 0x7
singleline_comment|//#define     ADB_MIX_MASK 0xf
multiline_comment|/* ADB address */
DECL|macro|OFFSET_ADBDMA
mdefine_line|#define&t;&t;OFFSET_ADBDMA&t;0x00
DECL|macro|OFFSET_SRCOUT
mdefine_line|#define&t;&t;OFFSET_SRCOUT&t;0x10&t;/* on channel 0x11 */
DECL|macro|OFFSET_SRCIN
mdefine_line|#define&t;&t;OFFSET_SRCIN&t;0x10&t;/* on channel &lt; 0x11 */
DECL|macro|OFFSET_MIXOUT
mdefine_line|#define&t;&t;OFFSET_MIXOUT&t;0x20&t;/* source */
DECL|macro|OFFSET_MIXIN
mdefine_line|#define&t;&t;OFFSET_MIXIN&t;0x30&t;/* sink */
DECL|macro|OFFSET_CODECIN
mdefine_line|#define&t;&t;OFFSET_CODECIN&t;0x48&t;/* ADB source */
DECL|macro|OFFSET_CODECOUT
mdefine_line|#define&t;&t;OFFSET_CODECOUT&t;0x58&t;/* ADB sink/target */
DECL|macro|OFFSET_SPORTOUT
mdefine_line|#define&t;&t;OFFSET_SPORTOUT&t;0x60&t;/* sink */
DECL|macro|OFFSET_SPORTIN
mdefine_line|#define&t;&t;OFFSET_SPORTIN&t;0x50&t;/* source */
DECL|macro|OFFSET_EFXOUT
mdefine_line|#define&t;&t;OFFSET_EFXOUT&t;0x50&t;/* sink */
DECL|macro|OFFSET_EFXIN
mdefine_line|#define&t;&t;OFFSET_EFXIN&t;0x40&t;/* source */
DECL|macro|OFFSET_A3DOUT
mdefine_line|#define&t;&t;OFFSET_A3DOUT&t;0x00&t;/* This card has no HRTF :( */
DECL|macro|OFFSET_A3DIN
mdefine_line|#define&t;&t;OFFSET_A3DIN&t;0x00
DECL|macro|OFFSET_WTOUT
mdefine_line|#define&t;&t;OFFSET_WTOUT&t;0x58&t;/*  */
multiline_comment|/* ADB route translate helper */
DECL|macro|ADB_DMA
mdefine_line|#define ADB_DMA(x) (x + OFFSET_ADBDMA)
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
DECL|macro|ADB_SPORTOUT
mdefine_line|#define ADB_SPORTOUT(x) (x + OFFSET_SPORTOUT)
DECL|macro|ADB_SPORTIN
mdefine_line|#define ADB_SPORTIN(x) (x + OFFSET_SPORTIN)&t;/*  */
DECL|macro|ADB_A3DOUT
mdefine_line|#define ADB_A3DOUT(x) (x + OFFSET_A3DOUT)&t;/* 8 A3D blocks */
DECL|macro|ADB_A3DIN
mdefine_line|#define ADB_A3DIN(x) (x + OFFSET_A3DIN)
DECL|macro|ADB_WTOUT
mdefine_line|#define ADB_WTOUT(x,y) (y + OFFSET_WTOUT)
multiline_comment|/* WTDMA */
DECL|macro|VORTEX_WTDMA_CTRL
mdefine_line|#define VORTEX_WTDMA_CTRL 0x10500&t;/* format, DMA pos */
DECL|macro|VORTEX_WTDMA_STAT
mdefine_line|#define VORTEX_WTDMA_STAT 0x10500&t;/* DMA subbuf, DMA pos */
DECL|macro|WT_SUBBUF_MASK
mdefine_line|#define     WT_SUBBUF_MASK (0x3 &lt;&lt; WT_SUBBUF_SHIFT)
DECL|macro|WT_SUBBUF_SHIFT
mdefine_line|#define     WT_SUBBUF_SHIFT 0x15
DECL|macro|VORTEX_WTDMA_BUFBASE
mdefine_line|#define VORTEX_WTDMA_BUFBASE 0x10000
DECL|macro|VORTEX_WTDMA_BUFCFG0
mdefine_line|#define VORTEX_WTDMA_BUFCFG0 0x10300
DECL|macro|VORTEX_WTDMA_BUFCFG1
mdefine_line|#define VORTEX_WTDMA_BUFCFG1 0x10304
DECL|macro|VORTEX_WTDMA_START
mdefine_line|#define VORTEX_WTDMA_START 0x10640&t;/* which subbuffer is first */
DECL|macro|VORTEX_WT_BASE
mdefine_line|#define VORTEX_WT_BASE 0x9000
multiline_comment|/* MIXER */
DECL|macro|VORTEX_MIXER_SR
mdefine_line|#define VORTEX_MIXER_SR 0x9f00
DECL|macro|VORTEX_MIXER_CLIP
mdefine_line|#define VORTEX_MIXER_CLIP 0x9f80
DECL|macro|VORTEX_MIXER_CHNBASE
mdefine_line|#define VORTEX_MIXER_CHNBASE 0x9e40
DECL|macro|VORTEX_MIXER_RTBASE
mdefine_line|#define VORTEX_MIXER_RTBASE 0x9e00
DECL|macro|MIXER_RTBASE_SIZE
mdefine_line|#define &t;MIXER_RTBASE_SIZE 0x26
DECL|macro|VORTEX_MIX_ENIN
mdefine_line|#define VORTEX_MIX_ENIN 0x9a00&t;/* Input enable bits. 4 bits wide. */
DECL|macro|VORTEX_MIX_SMP
mdefine_line|#define VORTEX_MIX_SMP 0x9c00
multiline_comment|/* MIX */
DECL|macro|VORTEX_MIX_INVOL_A
mdefine_line|#define VORTEX_MIX_INVOL_A 0x9000&t;/* in? */
DECL|macro|VORTEX_MIX_INVOL_B
mdefine_line|#define VORTEX_MIX_INVOL_B 0x8000&t;/* out? */
DECL|macro|VORTEX_MIX_VOL_A
mdefine_line|#define VORTEX_MIX_VOL_A 0x9800
DECL|macro|VORTEX_MIX_VOL_B
mdefine_line|#define VORTEX_MIX_VOL_B 0x8800
DECL|macro|VOL_MIN
mdefine_line|#define &t;VOL_MIN 0x80&t;/* Input volume when muted. */
DECL|macro|VOL_MAX
mdefine_line|#define&t;&t;VOL_MAX 0x7f&t;/* FIXME: Not confirmed! Just guessed. */
singleline_comment|//#define MIX_OUTL    0xe
singleline_comment|//#define MIX_OUTR    0xf
singleline_comment|//#define MIX_INL     0xe
singleline_comment|//#define MIX_INR     0xf
DECL|macro|MIX_DEFIGAIN
mdefine_line|#define MIX_DEFIGAIN 0x08&t;/* 0x8 =&gt; 6dB */
DECL|macro|MIX_DEFOGAIN
mdefine_line|#define MIX_DEFOGAIN 0x08
multiline_comment|/* SRC */
DECL|macro|VORTEX_SRCBLOCK_SR
mdefine_line|#define VORTEX_SRCBLOCK_SR&t;0xccc0
DECL|macro|VORTEX_SRC_CHNBASE
mdefine_line|#define VORTEX_SRC_CHNBASE&t;0xcc40
DECL|macro|VORTEX_SRC_RTBASE
mdefine_line|#define VORTEX_SRC_RTBASE&t;0xcc00
DECL|macro|VORTEX_SRC_SOURCE
mdefine_line|#define VORTEX_SRC_SOURCE&t;0xccc4
DECL|macro|VORTEX_SRC_SOURCESIZE
mdefine_line|#define VORTEX_SRC_SOURCESIZE 0xccc8
DECL|macro|VORTEX_SRC_U0
mdefine_line|#define VORTEX_SRC_U0&t;&t;0xce00
DECL|macro|VORTEX_SRC_DRIFT0
mdefine_line|#define VORTEX_SRC_DRIFT0&t;0xce80
DECL|macro|VORTEX_SRC_DRIFT1
mdefine_line|#define VORTEX_SRC_DRIFT1&t;0xcec0
DECL|macro|VORTEX_SRC_U1
mdefine_line|#define VORTEX_SRC_U1&t;&t;0xcf00
DECL|macro|VORTEX_SRC_DRIFT2
mdefine_line|#define VORTEX_SRC_DRIFT2&t;0xcf40
DECL|macro|VORTEX_SRC_U2
mdefine_line|#define VORTEX_SRC_U2&t;&t;0xcf80
DECL|macro|VORTEX_SRC_DATA
mdefine_line|#define VORTEX_SRC_DATA&t;&t;0xc800
DECL|macro|VORTEX_SRC_DATA0
mdefine_line|#define VORTEX_SRC_DATA0&t;0xc000
DECL|macro|VORTEX_SRC_CONVRATIO
mdefine_line|#define VORTEX_SRC_CONVRATIO 0xce40
singleline_comment|//#define     SRC_RATIO(x) ((((x&lt;&lt;15)/48000) + 1)/2) /* Playback */
singleline_comment|//#define     SRC_RATIO2(x) ((((48000&lt;&lt;15)/x) + 1)/2) /* Recording */
multiline_comment|/* FIFO */
DECL|macro|VORTEX_FIFO_ADBCTRL
mdefine_line|#define VORTEX_FIFO_ADBCTRL 0xf800&t;/* Control bits. */
DECL|macro|VORTEX_FIFO_WTCTRL
mdefine_line|#define VORTEX_FIFO_WTCTRL 0xf840
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
DECL|macro|VORTEX_FIFO_ADBDATA
mdefine_line|#define VORTEX_FIFO_ADBDATA 0xe000
DECL|macro|VORTEX_FIFO_WTDATA
mdefine_line|#define VORTEX_FIFO_WTDATA 0xe800
multiline_comment|/* CODEC */
DECL|macro|VORTEX_CODEC_CTRL
mdefine_line|#define VORTEX_CODEC_CTRL 0x11984
DECL|macro|VORTEX_CODEC_EN
mdefine_line|#define VORTEX_CODEC_EN 0x11990
DECL|macro|EN_CODEC
mdefine_line|#define&t;&t;EN_CODEC&t;0x00000300
DECL|macro|EN_SPORT
mdefine_line|#define&t;&t;EN_SPORT&t;0x00030000
DECL|macro|EN_SPDIF
mdefine_line|#define&t;&t;EN_SPDIF&t;0x000c0000
DECL|macro|VORTEX_CODEC_CHN
mdefine_line|#define VORTEX_CODEC_CHN 0x11880
DECL|macro|VORTEX_CODEC_WRITE
mdefine_line|#define VORTEX_CODEC_WRITE 0x00800000
DECL|macro|VORTEX_CODEC_ADDSHIFT
mdefine_line|#define VORTEX_CODEC_ADDSHIFT 16
DECL|macro|VORTEX_CODEC_ADDMASK
mdefine_line|#define VORTEX_CODEC_ADDMASK 0x7f0000&t;/* 0x000f0000 */
DECL|macro|VORTEX_CODEC_DATSHIFT
mdefine_line|#define VORTEX_CODEC_DATSHIFT 0
DECL|macro|VORTEX_CODEC_DATMASK
mdefine_line|#define VORTEX_CODEC_DATMASK 0xffff
DECL|macro|VORTEX_CODEC_IO
mdefine_line|#define VORTEX_CODEC_IO 0x11988
DECL|macro|VORTEX_SPDIF_FLAGS
mdefine_line|#define VORTEX_SPDIF_FLAGS&t;&t;0x1005c&t;/* FIXME */
DECL|macro|VORTEX_SPDIF_CFG0
mdefine_line|#define VORTEX_SPDIF_CFG0&t;&t;0x119D0
DECL|macro|VORTEX_SPDIF_CFG1
mdefine_line|#define VORTEX_SPDIF_CFG1&t;&t;0x119D4
DECL|macro|VORTEX_SPDIF_SMPRATE
mdefine_line|#define VORTEX_SPDIF_SMPRATE&t;0x11994
multiline_comment|/* Sample timer */
DECL|macro|VORTEX_SMP_TIME
mdefine_line|#define VORTEX_SMP_TIME 0x11998
multiline_comment|/* IRQ */
DECL|macro|VORTEX_IRQ_SOURCE
mdefine_line|#define VORTEX_IRQ_SOURCE 0x12800&t;/* Interrupt source flags. */
DECL|macro|VORTEX_IRQ_CTRL
mdefine_line|#define VORTEX_IRQ_CTRL 0x12804&t;/* Interrupt source mask. */
DECL|macro|VORTEX_STAT
mdefine_line|#define VORTEX_STAT&t;&t;0x12808&t;/* ?? */
DECL|macro|VORTEX_CTRL
mdefine_line|#define VORTEX_CTRL 0x1280c
DECL|macro|CTRL_MIDI_EN
mdefine_line|#define &t;CTRL_MIDI_EN 0x00000001
DECL|macro|CTRL_MIDI_PORT
mdefine_line|#define &t;CTRL_MIDI_PORT 0x00000060
DECL|macro|CTRL_GAME_EN
mdefine_line|#define &t;CTRL_GAME_EN 0x00000008
DECL|macro|CTRL_GAME_PORT
mdefine_line|#define &t;CTRL_GAME_PORT 0x00000e00
DECL|macro|CTRL_IRQ_ENABLE
mdefine_line|#define &t;CTRL_IRQ_ENABLE 0x4000
multiline_comment|/* write: Timer period config / read: TIMER IRQ ack. */
DECL|macro|VORTEX_IRQ_STAT
mdefine_line|#define VORTEX_IRQ_STAT 0x1199c
multiline_comment|/* DMA */
DECL|macro|VORTEX_DMA_BUFFER
mdefine_line|#define VORTEX_DMA_BUFFER 0x10200
DECL|macro|VORTEX_ENGINE_CTRL
mdefine_line|#define VORTEX_ENGINE_CTRL 0x1060c
DECL|macro|ENGINE_INIT
mdefine_line|#define &t;ENGINE_INIT 0x0L
multiline_comment|/* MIDI */
multiline_comment|/* GAME. */
DECL|macro|VORTEX_MIDI_DATA
mdefine_line|#define VORTEX_MIDI_DATA 0x11000
DECL|macro|VORTEX_MIDI_CMD
mdefine_line|#define VORTEX_MIDI_CMD 0x11004&t;/* Write command / Read status */
DECL|macro|VORTEX_GAME_LEGACY
mdefine_line|#define VORTEX_GAME_LEGACY 0x11008
DECL|macro|VORTEX_CTRL2
mdefine_line|#define VORTEX_CTRL2 0x1100c
DECL|macro|CTRL2_GAME_ADCMODE
mdefine_line|#define &t;CTRL2_GAME_ADCMODE 0x40
DECL|macro|VORTEX_GAME_AXIS
mdefine_line|#define VORTEX_GAME_AXIS 0x11010
DECL|macro|AXIS_SIZE
mdefine_line|#define &t;AXIS_SIZE 4
DECL|macro|AXIS_RANGE
mdefine_line|#define&t;&t;AXIS_RANGE 0x1fff
eof
