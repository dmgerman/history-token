multiline_comment|/*********************************************************************&n; *&n; * msnd.h&n; *&n; * Turtle Beach MultiSound Sound Card Driver for Linux&n; *&n; * Some parts of this header file were derived from the Turtle Beach&n; * MultiSound Driver Development Kit.&n; *&n; * Copyright (C) 1998 Andrew Veliath&n; * Copyright (C) 1993 Turtle Beach Systems, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Id: msnd.h,v 1.36 1999/03/21 17:05:42 andrewtv Exp $&n; *&n; ********************************************************************/
macro_line|#ifndef __MSND_H
DECL|macro|__MSND_H
mdefine_line|#define __MSND_H
DECL|macro|VERSION
mdefine_line|#define VERSION&t;&t;&t;&quot;0.8.3.1&quot;
DECL|macro|DEFSAMPLERATE
mdefine_line|#define DEFSAMPLERATE&t;&t;DSP_DEFAULT_SPEED
DECL|macro|DEFSAMPLESIZE
mdefine_line|#define DEFSAMPLESIZE&t;&t;AFMT_U8
DECL|macro|DEFCHANNELS
mdefine_line|#define DEFCHANNELS&t;&t;1
DECL|macro|DEFFIFOSIZE
mdefine_line|#define DEFFIFOSIZE&t;&t;128
DECL|macro|SNDCARD_MSND
mdefine_line|#define SNDCARD_MSND&t;&t;38
DECL|macro|SRAM_BANK_SIZE
mdefine_line|#define SRAM_BANK_SIZE&t;&t;0x8000
DECL|macro|SRAM_CNTL_START
mdefine_line|#define SRAM_CNTL_START&t;&t;0x7F00
DECL|macro|DSP_BASE_ADDR
mdefine_line|#define DSP_BASE_ADDR&t;&t;0x4000
DECL|macro|DSP_BANK_BASE
mdefine_line|#define DSP_BANK_BASE&t;&t;0x4000
DECL|macro|HP_ICR
mdefine_line|#define&t;HP_ICR&t;&t;&t;0x00
DECL|macro|HP_CVR
mdefine_line|#define&t;HP_CVR&t;&t;&t;0x01
DECL|macro|HP_ISR
mdefine_line|#define&t;HP_ISR&t;&t;&t;0x02
DECL|macro|HP_IVR
mdefine_line|#define&t;HP_IVR&t;&t;&t;0x03
DECL|macro|HP_NU
mdefine_line|#define HP_NU&t;&t;&t;0x04
DECL|macro|HP_INFO
mdefine_line|#define HP_INFO&t;&t;&t;0x04
DECL|macro|HP_TXH
mdefine_line|#define&t;HP_TXH&t;&t;&t;0x05
DECL|macro|HP_RXH
mdefine_line|#define&t;HP_RXH&t;&t;&t;0x05
DECL|macro|HP_TXM
mdefine_line|#define&t;HP_TXM&t;&t;&t;0x06
DECL|macro|HP_RXM
mdefine_line|#define&t;HP_RXM&t;&t;&t;0x06
DECL|macro|HP_TXL
mdefine_line|#define&t;HP_TXL&t;&t;&t;0x07
DECL|macro|HP_RXL
mdefine_line|#define&t;HP_RXL&t;&t;&t;0x07
DECL|macro|HP_ICR_DEF
mdefine_line|#define HP_ICR_DEF&t;&t;0x00
DECL|macro|HP_CVR_DEF
mdefine_line|#define HP_CVR_DEF&t;&t;0x12
DECL|macro|HP_ISR_DEF
mdefine_line|#define HP_ISR_DEF&t;&t;0x06
DECL|macro|HP_IVR_DEF
mdefine_line|#define HP_IVR_DEF&t;&t;0x0f
DECL|macro|HP_NU_DEF
mdefine_line|#define HP_NU_DEF&t;&t;0x00
DECL|macro|HP_IRQM
mdefine_line|#define&t;HP_IRQM&t;&t;&t;0x09
DECL|macro|HPR_BLRC
mdefine_line|#define&t;HPR_BLRC&t;&t;0x08
DECL|macro|HPR_SPR1
mdefine_line|#define&t;HPR_SPR1&t;&t;0x09
DECL|macro|HPR_SPR2
mdefine_line|#define&t;HPR_SPR2&t;&t;0x0A
DECL|macro|HPR_TCL0
mdefine_line|#define&t;HPR_TCL0&t;&t;0x0B
DECL|macro|HPR_TCL1
mdefine_line|#define&t;HPR_TCL1&t;&t;0x0C
DECL|macro|HPR_TCL2
mdefine_line|#define&t;HPR_TCL2&t;&t;0x0D
DECL|macro|HPR_TCL3
mdefine_line|#define&t;HPR_TCL3&t;&t;0x0E
DECL|macro|HPR_TCL4
mdefine_line|#define&t;HPR_TCL4&t;&t;0x0F
DECL|macro|HPICR_INIT
mdefine_line|#define&t;HPICR_INIT&t;&t;0x80
DECL|macro|HPICR_HM1
mdefine_line|#define HPICR_HM1&t;&t;0x40
DECL|macro|HPICR_HM0
mdefine_line|#define HPICR_HM0&t;&t;0x20
DECL|macro|HPICR_HF1
mdefine_line|#define HPICR_HF1&t;&t;0x10
DECL|macro|HPICR_HF0
mdefine_line|#define HPICR_HF0&t;&t;0x08
DECL|macro|HPICR_TREQ
mdefine_line|#define&t;HPICR_TREQ&t;&t;0x02
DECL|macro|HPICR_RREQ
mdefine_line|#define&t;HPICR_RREQ&t;&t;0x01
DECL|macro|HPCVR_HC
mdefine_line|#define HPCVR_HC&t;&t;0x80
DECL|macro|HPISR_HREQ
mdefine_line|#define&t;HPISR_HREQ&t;&t;0x80
DECL|macro|HPISR_DMA
mdefine_line|#define HPISR_DMA&t;&t;0x40
DECL|macro|HPISR_HF3
mdefine_line|#define HPISR_HF3&t;&t;0x10
DECL|macro|HPISR_HF2
mdefine_line|#define HPISR_HF2&t;&t;0x08
DECL|macro|HPISR_TRDY
mdefine_line|#define&t;HPISR_TRDY&t;&t;0x04
DECL|macro|HPISR_TXDE
mdefine_line|#define&t;HPISR_TXDE&t;&t;0x02
DECL|macro|HPISR_RXDF
mdefine_line|#define&t;HPISR_RXDF&t;&t;0x01
DECL|macro|HPIO_290
mdefine_line|#define&t;HPIO_290&t;&t;0
DECL|macro|HPIO_260
mdefine_line|#define&t;HPIO_260&t;&t;1
DECL|macro|HPIO_250
mdefine_line|#define&t;HPIO_250&t;&t;2
DECL|macro|HPIO_240
mdefine_line|#define&t;HPIO_240&t;&t;3
DECL|macro|HPIO_230
mdefine_line|#define&t;HPIO_230&t;&t;4
DECL|macro|HPIO_220
mdefine_line|#define&t;HPIO_220&t;&t;5
DECL|macro|HPIO_210
mdefine_line|#define&t;HPIO_210&t;&t;6
DECL|macro|HPIO_3E0
mdefine_line|#define&t;HPIO_3E0&t;&t;7
DECL|macro|HPMEM_NONE
mdefine_line|#define&t;HPMEM_NONE&t;&t;0
DECL|macro|HPMEM_B000
mdefine_line|#define&t;HPMEM_B000&t;&t;1
DECL|macro|HPMEM_C800
mdefine_line|#define&t;HPMEM_C800&t;&t;2
DECL|macro|HPMEM_D000
mdefine_line|#define&t;HPMEM_D000&t;&t;3
DECL|macro|HPMEM_D400
mdefine_line|#define&t;HPMEM_D400&t;&t;4
DECL|macro|HPMEM_D800
mdefine_line|#define&t;HPMEM_D800&t;&t;5
DECL|macro|HPMEM_E000
mdefine_line|#define&t;HPMEM_E000&t;&t;6
DECL|macro|HPMEM_E800
mdefine_line|#define&t;HPMEM_E800&t;&t;7
DECL|macro|HPIRQ_NONE
mdefine_line|#define&t;HPIRQ_NONE&t;&t;0
DECL|macro|HPIRQ_5
mdefine_line|#define HPIRQ_5&t;&t;&t;1
DECL|macro|HPIRQ_7
mdefine_line|#define HPIRQ_7&t;&t;&t;2
DECL|macro|HPIRQ_9
mdefine_line|#define HPIRQ_9&t;&t;&t;3
DECL|macro|HPIRQ_10
mdefine_line|#define HPIRQ_10&t;&t;4
DECL|macro|HPIRQ_11
mdefine_line|#define HPIRQ_11&t;&t;5
DECL|macro|HPIRQ_12
mdefine_line|#define HPIRQ_12&t;&t;6
DECL|macro|HPIRQ_15
mdefine_line|#define HPIRQ_15&t;&t;7
DECL|macro|HIMT_PLAY_DONE
mdefine_line|#define&t;HIMT_PLAY_DONE&t;&t;0x00
DECL|macro|HIMT_RECORD_DONE
mdefine_line|#define&t;HIMT_RECORD_DONE&t;0x01
DECL|macro|HIMT_MIDI_EOS
mdefine_line|#define&t;HIMT_MIDI_EOS&t;&t;0x02
DECL|macro|HIMT_MIDI_OUT
mdefine_line|#define&t;HIMT_MIDI_OUT&t;&t;0x03
DECL|macro|HIMT_MIDI_IN_UCHAR
mdefine_line|#define&t;HIMT_MIDI_IN_UCHAR&t;0x0E
DECL|macro|HIMT_DSP
mdefine_line|#define&t;HIMT_DSP&t;&t;0x0F
DECL|macro|HDEX_BASE
mdefine_line|#define&t;HDEX_BASE&t;       &t;0x92
DECL|macro|HDEX_PLAY_START
mdefine_line|#define&t;HDEX_PLAY_START&t;&t;(0 + HDEX_BASE)
DECL|macro|HDEX_PLAY_STOP
mdefine_line|#define&t;HDEX_PLAY_STOP&t;&t;(1 + HDEX_BASE)
DECL|macro|HDEX_PLAY_PAUSE
mdefine_line|#define&t;HDEX_PLAY_PAUSE&t;&t;(2 + HDEX_BASE)
DECL|macro|HDEX_PLAY_RESUME
mdefine_line|#define&t;HDEX_PLAY_RESUME&t;(3 + HDEX_BASE)
DECL|macro|HDEX_RECORD_START
mdefine_line|#define&t;HDEX_RECORD_START&t;(4 + HDEX_BASE)
DECL|macro|HDEX_RECORD_STOP
mdefine_line|#define&t;HDEX_RECORD_STOP&t;(5 + HDEX_BASE)
DECL|macro|HDEX_MIDI_IN_START
mdefine_line|#define&t;HDEX_MIDI_IN_START &t;(6 + HDEX_BASE)
DECL|macro|HDEX_MIDI_IN_STOP
mdefine_line|#define&t;HDEX_MIDI_IN_STOP&t;(7 + HDEX_BASE)
DECL|macro|HDEX_MIDI_OUT_START
mdefine_line|#define&t;HDEX_MIDI_OUT_START&t;(8 + HDEX_BASE)
DECL|macro|HDEX_MIDI_OUT_STOP
mdefine_line|#define&t;HDEX_MIDI_OUT_STOP&t;(9 + HDEX_BASE)
DECL|macro|HDEX_AUX_REQ
mdefine_line|#define&t;HDEX_AUX_REQ&t;&t;(10 + HDEX_BASE)
DECL|macro|HIWORD
mdefine_line|#define HIWORD(l)&t;&t;((WORD)((((DWORD)(l)) &gt;&gt; 16) &amp; 0xFFFF))
DECL|macro|LOWORD
mdefine_line|#define LOWORD(l)&t;&t;((WORD)(DWORD)(l))
DECL|macro|HIBYTE
mdefine_line|#define HIBYTE(w)&t;&t;((BYTE)(((WORD)(w) &gt;&gt; 8) &amp; 0xFF))
DECL|macro|LOBYTE
mdefine_line|#define LOBYTE(w)&t;&t;((BYTE)(w))
DECL|macro|MAKELONG
mdefine_line|#define MAKELONG(low,hi)&t;((long)(((WORD)(low))|(((DWORD)((WORD)(hi)))&lt;&lt;16)))
DECL|macro|MAKEWORD
mdefine_line|#define MAKEWORD(low,hi)&t;((WORD)(((BYTE)(low))|(((WORD)((BYTE)(hi)))&lt;&lt;8)))
DECL|macro|PCTODSP_OFFSET
mdefine_line|#define PCTODSP_OFFSET(w)&t;(USHORT)((w)/2)
DECL|macro|PCTODSP_BASED
mdefine_line|#define PCTODSP_BASED(w)&t;(USHORT)(((w)/2) + DSP_BASE_ADDR)
DECL|macro|DSPTOPC_BASED
mdefine_line|#define DSPTOPC_BASED(w)&t;(((w) - DSP_BASE_ADDR) * 2)
macro_line|#ifdef SLOWIO
DECL|macro|outb
macro_line|#  undef outb
DECL|macro|inb
macro_line|#  undef inb
DECL|macro|outb
macro_line|#  define outb&t;&t;&t;outb_p
DECL|macro|inb
macro_line|#  define inb&t;&t;&t;inb_p
macro_line|#endif
multiline_comment|/* JobQueueStruct */
DECL|macro|JQS_wStart
mdefine_line|#define JQS_wStart&t;&t;0x00
DECL|macro|JQS_wSize
mdefine_line|#define JQS_wSize&t;&t;0x02
DECL|macro|JQS_wHead
mdefine_line|#define JQS_wHead&t;&t;0x04
DECL|macro|JQS_wTail
mdefine_line|#define JQS_wTail&t;&t;0x06
DECL|macro|JQS__size
mdefine_line|#define JQS__size&t;&t;0x08
multiline_comment|/* DAQueueDataStruct */
DECL|macro|DAQDS_wStart
mdefine_line|#define DAQDS_wStart&t;&t;0x00
DECL|macro|DAQDS_wSize
mdefine_line|#define DAQDS_wSize&t;&t;0x02
DECL|macro|DAQDS_wFormat
mdefine_line|#define DAQDS_wFormat&t;&t;0x04
DECL|macro|DAQDS_wSampleSize
mdefine_line|#define DAQDS_wSampleSize&t;0x06
DECL|macro|DAQDS_wChannels
mdefine_line|#define DAQDS_wChannels&t;&t;0x08
DECL|macro|DAQDS_wSampleRate
mdefine_line|#define DAQDS_wSampleRate&t;0x0A
DECL|macro|DAQDS_wIntMsg
mdefine_line|#define DAQDS_wIntMsg&t;&t;0x0C
DECL|macro|DAQDS_wFlags
mdefine_line|#define DAQDS_wFlags&t;&t;0x0E
DECL|macro|DAQDS__size
mdefine_line|#define DAQDS__size&t;&t;0x10
DECL|typedef|BYTE
r_typedef
id|u8
id|BYTE
suffix:semicolon
DECL|typedef|USHORT
r_typedef
id|u16
id|USHORT
suffix:semicolon
DECL|typedef|WORD
r_typedef
id|u16
id|WORD
suffix:semicolon
DECL|typedef|DWORD
r_typedef
id|u32
id|DWORD
suffix:semicolon
DECL|typedef|LPDAQD
r_typedef
r_int
r_int
id|LPDAQD
suffix:semicolon
multiline_comment|/* Generic FIFO */
r_typedef
r_struct
(brace
DECL|member|n
DECL|member|len
r_int
id|n
comma
id|len
suffix:semicolon
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|head
DECL|member|tail
r_int
id|head
comma
id|tail
suffix:semicolon
DECL|typedef|msnd_fifo
)brace
id|msnd_fifo
suffix:semicolon
DECL|struct|multisound_dev
r_typedef
r_struct
id|multisound_dev
(brace
multiline_comment|/* Linux device info */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|dsp_minor
DECL|member|mixer_minor
r_int
id|dsp_minor
comma
id|mixer_minor
suffix:semicolon
DECL|member|ext_midi_dev
DECL|member|hdr_midi_dev
r_int
id|ext_midi_dev
comma
id|hdr_midi_dev
suffix:semicolon
multiline_comment|/* Hardware resources */
DECL|member|io
DECL|member|numio
r_int
id|io
comma
id|numio
suffix:semicolon
DECL|member|memid
DECL|member|irqid
r_int
id|memid
comma
id|irqid
suffix:semicolon
DECL|member|irq
DECL|member|irq_ref
r_int
id|irq
comma
id|irq_ref
suffix:semicolon
DECL|member|info
r_int
r_char
id|info
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* Motorola 56k DSP SMA */
DECL|member|SMA
r_int
r_int
id|SMA
suffix:semicolon
DECL|member|DAPQ
DECL|member|DARQ
DECL|member|MODQ
DECL|member|MIDQ
DECL|member|DSPQ
r_int
r_int
id|DAPQ
comma
id|DARQ
comma
id|MODQ
comma
id|MIDQ
comma
id|DSPQ
suffix:semicolon
DECL|member|pwDSPQData
DECL|member|pwMIDQData
DECL|member|pwMODQData
r_int
r_int
id|pwDSPQData
comma
id|pwMIDQData
comma
id|pwMODQData
suffix:semicolon
DECL|member|dspq_data_buff
DECL|member|dspq_buff_size
r_int
id|dspq_data_buff
comma
id|dspq_buff_size
suffix:semicolon
multiline_comment|/* State variables */
DECL|enumerator|msndClassic
DECL|enumerator|msndPinnacle
DECL|member|type
r_enum
(brace
id|msndClassic
comma
id|msndPinnacle
)brace
id|type
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|F_RESETTING
mdefine_line|#define F_RESETTING&t;&t;&t;0
DECL|macro|F_HAVEDIGITAL
mdefine_line|#define F_HAVEDIGITAL&t;&t;&t;1
DECL|macro|F_AUDIO_WRITE_INUSE
mdefine_line|#define F_AUDIO_WRITE_INUSE&t;&t;2
DECL|macro|F_WRITING
mdefine_line|#define F_WRITING&t;&t;&t;3
DECL|macro|F_WRITEBLOCK
mdefine_line|#define F_WRITEBLOCK&t;&t;&t;4
DECL|macro|F_WRITEFLUSH
mdefine_line|#define F_WRITEFLUSH&t;&t;&t;5
DECL|macro|F_AUDIO_READ_INUSE
mdefine_line|#define F_AUDIO_READ_INUSE&t;&t;6
DECL|macro|F_READING
mdefine_line|#define F_READING&t;&t;&t;7
DECL|macro|F_READBLOCK
mdefine_line|#define F_READBLOCK&t;&t;&t;8
DECL|macro|F_EXT_MIDI_INUSE
mdefine_line|#define F_EXT_MIDI_INUSE&t;&t;9
DECL|macro|F_HDR_MIDI_INUSE
mdefine_line|#define F_HDR_MIDI_INUSE&t;&t;10
DECL|macro|F_DISABLE_WRITE_NDELAY
mdefine_line|#define F_DISABLE_WRITE_NDELAY&t;&t;11
DECL|member|writeblock
id|wait_queue_head_t
id|writeblock
suffix:semicolon
DECL|member|readblock
id|wait_queue_head_t
id|readblock
suffix:semicolon
DECL|member|writeflush
id|wait_queue_head_t
id|writeflush
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|nresets
r_int
id|nresets
suffix:semicolon
DECL|member|recsrc
r_int
r_int
id|recsrc
suffix:semicolon
DECL|member|left_levels
r_int
id|left_levels
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|right_levels
r_int
id|right_levels
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|mixer_mod_count
r_int
id|mixer_mod_count
suffix:semicolon
DECL|member|calibrate_signal
r_int
id|calibrate_signal
suffix:semicolon
DECL|member|play_sample_size
DECL|member|play_sample_rate
DECL|member|play_channels
r_int
id|play_sample_size
comma
id|play_sample_rate
comma
id|play_channels
suffix:semicolon
DECL|member|play_ndelay
r_int
id|play_ndelay
suffix:semicolon
DECL|member|rec_sample_size
DECL|member|rec_sample_rate
DECL|member|rec_channels
r_int
id|rec_sample_size
comma
id|rec_sample_rate
comma
id|rec_channels
suffix:semicolon
DECL|member|rec_ndelay
r_int
id|rec_ndelay
suffix:semicolon
DECL|member|bCurrentMidiPatch
id|BYTE
id|bCurrentMidiPatch
suffix:semicolon
multiline_comment|/* Digital audio FIFOs */
DECL|member|DAPF
DECL|member|DARF
id|msnd_fifo
id|DAPF
comma
id|DARF
suffix:semicolon
DECL|member|fifosize
r_int
id|fifosize
suffix:semicolon
DECL|member|last_playbank
DECL|member|last_recbank
r_int
id|last_playbank
comma
id|last_recbank
suffix:semicolon
multiline_comment|/* MIDI in callback */
DECL|member|midi_in_interrupt
r_void
(paren
op_star
id|midi_in_interrupt
)paren
(paren
r_struct
id|multisound_dev
op_star
)paren
suffix:semicolon
DECL|typedef|multisound_dev_t
)brace
id|multisound_dev_t
suffix:semicolon
macro_line|#ifndef mdelay
DECL|macro|mdelay
macro_line|#  define mdelay(a)&t;&t;udelay((a) * 1000)
macro_line|#endif
r_int
id|msnd_register
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
suffix:semicolon
r_void
id|msnd_unregister
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
suffix:semicolon
r_int
id|msnd_get_num_devs
c_func
(paren
r_void
)paren
suffix:semicolon
id|multisound_dev_t
op_star
id|msnd_get_dev
c_func
(paren
r_int
id|i
)paren
suffix:semicolon
r_void
id|msnd_init_queue
c_func
(paren
r_int
r_int
comma
r_int
id|start
comma
r_int
id|size
)paren
suffix:semicolon
r_void
id|msnd_fifo_init
c_func
(paren
id|msnd_fifo
op_star
id|f
)paren
suffix:semicolon
r_void
id|msnd_fifo_free
c_func
(paren
id|msnd_fifo
op_star
id|f
)paren
suffix:semicolon
r_int
id|msnd_fifo_alloc
c_func
(paren
id|msnd_fifo
op_star
id|f
comma
r_int
id|n
)paren
suffix:semicolon
r_void
id|msnd_fifo_make_empty
c_func
(paren
id|msnd_fifo
op_star
id|f
)paren
suffix:semicolon
r_int
id|msnd_fifo_write
c_func
(paren
id|msnd_fifo
op_star
id|f
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|user
)paren
suffix:semicolon
r_int
id|msnd_fifo_read
c_func
(paren
id|msnd_fifo
op_star
id|f
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|user
)paren
suffix:semicolon
r_int
id|msnd_wait_TXDE
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
suffix:semicolon
r_int
id|msnd_wait_HC0
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
suffix:semicolon
r_int
id|msnd_send_dsp_cmd
c_func
(paren
id|multisound_dev_t
op_star
id|dev
comma
id|BYTE
id|cmd
)paren
suffix:semicolon
r_int
id|msnd_send_word
c_func
(paren
id|multisound_dev_t
op_star
id|dev
comma
r_int
r_char
id|high
comma
r_int
r_char
id|mid
comma
r_int
r_char
id|low
)paren
suffix:semicolon
r_int
id|msnd_upload_host
c_func
(paren
id|multisound_dev_t
op_star
id|dev
comma
r_char
op_star
id|bin
comma
r_int
id|len
)paren
suffix:semicolon
r_int
id|msnd_enable_irq
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
suffix:semicolon
r_int
id|msnd_disable_irq
c_func
(paren
id|multisound_dev_t
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* __MSND_H */
eof
