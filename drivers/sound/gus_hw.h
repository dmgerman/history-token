multiline_comment|/*&n; * I/O addresses&n; */
DECL|macro|u_Base
mdefine_line|#define u_Base&t;&t;&t;(gus_base + 0x000)
DECL|macro|u_Mixer
mdefine_line|#define u_Mixer&t;&t;&t;u_Base
DECL|macro|u_Status
mdefine_line|#define u_Status&t;&t;(gus_base + 0x006)
DECL|macro|u_TimerControl
mdefine_line|#define u_TimerControl&t;&t;(gus_base + 0x008)
DECL|macro|u_TimerData
mdefine_line|#define u_TimerData&t;&t;(gus_base + 0x009)
DECL|macro|u_IRQDMAControl
mdefine_line|#define u_IRQDMAControl&t;&t;(gus_base + 0x00b)
DECL|macro|u_MidiControl
mdefine_line|#define u_MidiControl&t;&t;(gus_base + 0x100)
DECL|macro|MIDI_RESET
mdefine_line|#define &t;MIDI_RESET&t;&t;0x03
DECL|macro|MIDI_ENABLE_XMIT
mdefine_line|#define&t;&t;MIDI_ENABLE_XMIT&t;0x20
DECL|macro|MIDI_ENABLE_RCV
mdefine_line|#define&t;&t;MIDI_ENABLE_RCV&t;&t;0x80
DECL|macro|u_MidiStatus
mdefine_line|#define u_MidiStatus&t;&t;u_MidiControl
DECL|macro|MIDI_RCV_FULL
mdefine_line|#define&t;&t;MIDI_RCV_FULL&t;&t;0x01
DECL|macro|MIDI_XMIT_EMPTY
mdefine_line|#define &t;MIDI_XMIT_EMPTY&t;&t;0x02
DECL|macro|MIDI_FRAME_ERR
mdefine_line|#define &t;MIDI_FRAME_ERR&t;&t;0x10
DECL|macro|MIDI_OVERRUN
mdefine_line|#define &t;MIDI_OVERRUN&t;&t;0x20
DECL|macro|MIDI_IRQ_PEND
mdefine_line|#define &t;MIDI_IRQ_PEND&t;&t;0x80
DECL|macro|u_MidiData
mdefine_line|#define u_MidiData&t;&t;(gus_base + 0x101)
DECL|macro|u_Voice
mdefine_line|#define u_Voice&t;&t;&t;(gus_base + 0x102)
DECL|macro|u_Command
mdefine_line|#define u_Command&t;&t;(gus_base + 0x103)
DECL|macro|u_DataLo
mdefine_line|#define u_DataLo&t;&t;(gus_base + 0x104)
DECL|macro|u_DataHi
mdefine_line|#define u_DataHi&t;&t;(gus_base + 0x105)
DECL|macro|u_MixData
mdefine_line|#define u_MixData               (gus_base + 0x106)   /* Rev. 3.7+ mixing */
DECL|macro|u_MixSelect
mdefine_line|#define u_MixSelect             (gus_base + 0x506)   /* registers.       */
DECL|macro|u_IrqStatus
mdefine_line|#define u_IrqStatus&t;&t;u_Status
DECL|macro|MIDI_TX_IRQ
macro_line|#&t;define MIDI_TX_IRQ&t;&t;0x01&t;/* pending MIDI xmit IRQ */
DECL|macro|MIDI_RX_IRQ
macro_line|#&t;define MIDI_RX_IRQ&t;&t;0x02&t;/* pending MIDI recv IRQ */
DECL|macro|GF1_TIMER1_IRQ
macro_line|#&t;define GF1_TIMER1_IRQ&t;&t;0x04&t;/* general purpose timer */
DECL|macro|GF1_TIMER2_IRQ
macro_line|#&t;define GF1_TIMER2_IRQ&t;&t;0x08&t;/* general purpose timer */
DECL|macro|WAVETABLE_IRQ
macro_line|#&t;define WAVETABLE_IRQ&t;&t;0x20&t;/* pending wavetable IRQ */
DECL|macro|ENVELOPE_IRQ
macro_line|#&t;define ENVELOPE_IRQ&t;&t;0x40&t;/* pending volume envelope IRQ */
DECL|macro|DMA_TC_IRQ
macro_line|#&t;define DMA_TC_IRQ&t;&t;0x80&t;/* pending dma tc IRQ */
DECL|macro|ICS2101
mdefine_line|#define ICS2101&t;&t;1
DECL|macro|ICS_MIXDEVS
macro_line|#&t;define ICS_MIXDEVS&t;6
DECL|macro|DEV_MIC
macro_line|#&t;define DEV_MIC&t;&t;0
DECL|macro|DEV_LINE
macro_line|#&t;define DEV_LINE&t;&t;1
DECL|macro|DEV_CD
macro_line|#&t;define DEV_CD&t;&t;2
DECL|macro|DEV_GF1
macro_line|#&t;define DEV_GF1&t;&t;3
DECL|macro|DEV_UNUSED
macro_line|#&t;define DEV_UNUSED&t;4
DECL|macro|DEV_VOL
macro_line|#&t;define DEV_VOL&t;&t;5
DECL|macro|CHN_LEFT
macro_line|#&t;define CHN_LEFT&t;&t;0
DECL|macro|CHN_RIGHT
macro_line|#&t;define CHN_RIGHT&t;1
DECL|macro|CS4231
mdefine_line|#define CS4231&t;&t;2
DECL|macro|u_DRAMIO
mdefine_line|#define u_DRAMIO&t;&t;(gus_base + 0x107)
eof
