multiline_comment|/*&n; * sound/wf_midi.c&n; *&n; * The low level driver for the WaveFront ICS2115 MIDI interface(s)&n; * Note that there is also an MPU-401 emulation (actually, a UART-401&n; * emulation) on the CS4232 on the Tropez Plus. This code has nothing&n; * to do with that interface at all.&n; *&n; * The interface is essentially just a UART-401, but is has the&n; * interesting property of supporting what Turtle Beach called&n; * &quot;Virtual MIDI&quot; mode. In this mode, there are effectively *two*&n; * MIDI buses accessible via the interface, one that is routed&n; * solely to/from the external WaveFront synthesizer and the other&n; * corresponding to the pin/socket connector used to link external&n; * MIDI devices to the board.&n; *&n; * This driver fully supports this mode, allowing two distinct&n; * midi devices (/dev/midiNN and /dev/midiNN+1) to be used&n; * completely independently, giving 32 channels of MIDI routing,&n; * 16 to the WaveFront synth and 16 to the external MIDI bus.&n; *&n; * Switching between the two is accomplished externally by the driver&n; * using the two otherwise unused MIDI bytes. See the code for more details.&n; *&n; * NOTE: VIRTUAL MIDI MODE IS ON BY DEFAULT (see wavefront.c)&n; *&n; * The main reason to turn off Virtual MIDI mode is when you want to&n; * tightly couple the WaveFront synth with an external MIDI&n; * device. You won&squot;t be able to distinguish the source of any MIDI&n; * data except via SysEx ID, but thats probably OK, since for the most&n; * part, the WaveFront won&squot;t be sending any MIDI data at all.&n; *  &n; * The main reason to turn on Virtual MIDI Mode is to provide two&n; * completely independent 16-channel MIDI buses, one to the&n; * WaveFront and one to any external MIDI devices. Given the 32&n; * voice nature of the WaveFront, its pretty easy to find a use&n; * for all 16 channels driving just that synth.&n; *&n; */
multiline_comment|/*&n; * Copyright (C) by Paul Barton-Davis 1998&n; * Some portions of this file are derived from work that is:&n; *&n; *    CopyriGht (C) by Hannu Savolainen 1993-1996&n; *&n; * USS/Lite for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &lt;linux/wavefront.h&gt;
macro_line|#ifdef MODULE
DECL|struct|wf_mpu_config
r_struct
id|wf_mpu_config
(brace
DECL|member|base
r_int
id|base
suffix:semicolon
DECL|macro|DATAPORT
mdefine_line|#define&t;DATAPORT(d)   (d)-&gt;base
DECL|macro|COMDPORT
mdefine_line|#define&t;COMDPORT(d)   (d)-&gt;base+1
DECL|macro|STATPORT
mdefine_line|#define&t;STATPORT(d)   (d)-&gt;base+1
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|opened
r_int
id|opened
suffix:semicolon
DECL|member|devno
r_int
id|devno
suffix:semicolon
DECL|member|synthno
r_int
id|synthno
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|macro|MODE_MIDI
mdefine_line|#define MODE_MIDI&t;1
DECL|macro|MODE_SYNTH
mdefine_line|#define MODE_SYNTH&t;2
DECL|member|inputintr
r_void
(paren
op_star
id|inputintr
)paren
(paren
r_int
id|dev
comma
r_int
r_char
id|data
)paren
suffix:semicolon
DECL|member|isvirtual
r_char
id|isvirtual
suffix:semicolon
multiline_comment|/* do virtual I/O stuff */
)brace
suffix:semicolon
DECL|variable|devs
r_static
r_struct
id|wf_mpu_config
id|devs
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|phys_dev
r_static
r_struct
id|wf_mpu_config
op_star
id|phys_dev
op_assign
op_amp
id|devs
(braket
l_int|0
)braket
suffix:semicolon
DECL|variable|virt_dev
r_static
r_struct
id|wf_mpu_config
op_star
id|virt_dev
op_assign
op_amp
id|devs
(braket
l_int|1
)braket
suffix:semicolon
r_static
r_void
id|start_uart_mode
(paren
r_void
)paren
suffix:semicolon
DECL|variable|lock
r_static
id|spinlock_t
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|OUTPUT_READY
mdefine_line|#define&t;OUTPUT_READY&t;0x40
DECL|macro|INPUT_AVAIL
mdefine_line|#define&t;INPUT_AVAIL&t;0x80
DECL|macro|MPU_ACK
mdefine_line|#define&t;MPU_ACK&t;&t;0xFE
DECL|macro|UART_MODE_ON
mdefine_line|#define&t;UART_MODE_ON&t;0x3F
DECL|function|wf_mpu_status
r_static
r_inline
r_int
id|wf_mpu_status
(paren
r_void
)paren
(brace
r_return
id|inb
(paren
id|STATPORT
(paren
id|phys_dev
)paren
)paren
suffix:semicolon
)brace
DECL|function|input_avail
r_static
r_inline
r_int
id|input_avail
(paren
r_void
)paren
(brace
r_return
op_logical_neg
(paren
id|wf_mpu_status
c_func
(paren
)paren
op_amp
id|INPUT_AVAIL
)paren
suffix:semicolon
)brace
DECL|function|output_ready
r_static
r_inline
r_int
id|output_ready
(paren
r_void
)paren
(brace
r_return
op_logical_neg
(paren
id|wf_mpu_status
c_func
(paren
)paren
op_amp
id|OUTPUT_READY
)paren
suffix:semicolon
)brace
DECL|function|read_data
r_static
r_inline
r_int
id|read_data
(paren
r_void
)paren
(brace
r_return
id|inb
(paren
id|DATAPORT
(paren
id|phys_dev
)paren
)paren
suffix:semicolon
)brace
DECL|function|write_data
r_static
r_inline
r_void
id|write_data
(paren
r_int
r_char
id|byte
)paren
(brace
id|outb
(paren
id|byte
comma
id|DATAPORT
(paren
id|phys_dev
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * States for the input scanner (should be in dev_table.h)&n; */
DECL|macro|MST_SYSMSG
mdefine_line|#define MST_SYSMSG&t;&t;100&t;/* System message (sysx etc). */
DECL|macro|MST_MTC
mdefine_line|#define MST_MTC&t;&t;&t;102&t;/* Midi Time Code (MTC) qframe msg */
DECL|macro|MST_SONGSEL
mdefine_line|#define MST_SONGSEL&t;&t;103&t;/* Song select */
DECL|macro|MST_SONGPOS
mdefine_line|#define MST_SONGPOS&t;&t;104&t;/* Song position pointer */
DECL|macro|MST_TIMED
mdefine_line|#define MST_TIMED&t;&t;105&t;/* Leading timing byte rcvd */
multiline_comment|/* buffer space check for input scanner */
DECL|macro|BUFTEST
mdefine_line|#define BUFTEST(mi) if (mi-&gt;m_ptr &gt;= MI_MAX || mi-&gt;m_ptr &lt; 0) &bslash;&n;{printk(KERN_ERR &quot;WF-MPU: Invalid buffer pointer %d/%d, s=%d&bslash;n&quot;, &bslash;&n;&t;mi-&gt;m_ptr, mi-&gt;m_left, mi-&gt;m_state);mi-&gt;m_ptr--;}
DECL|variable|len_tab
r_static
r_int
r_char
id|len_tab
(braket
)braket
op_assign
multiline_comment|/* # of data bytes following a status&n;&t;&t;&t;&t;&t; */
(brace
l_int|2
comma
multiline_comment|/* 8x */
l_int|2
comma
multiline_comment|/* 9x */
l_int|2
comma
multiline_comment|/* Ax */
l_int|2
comma
multiline_comment|/* Bx */
l_int|1
comma
multiline_comment|/* Cx */
l_int|1
comma
multiline_comment|/* Dx */
l_int|2
comma
multiline_comment|/* Ex */
l_int|0
multiline_comment|/* Fx */
)brace
suffix:semicolon
r_static
r_int
DECL|function|wf_mpu_input_scanner
id|wf_mpu_input_scanner
(paren
r_int
id|devno
comma
r_int
id|synthdev
comma
r_int
r_char
id|midic
)paren
(brace
r_struct
id|midi_input_info
op_star
id|mi
op_assign
op_amp
id|midi_devs
(braket
id|devno
)braket
op_member_access_from_pointer
id|in_info
suffix:semicolon
r_switch
c_cond
(paren
id|mi-&gt;m_state
)paren
(brace
r_case
id|MST_INIT
suffix:colon
r_switch
c_cond
(paren
id|midic
)paren
(brace
r_case
l_int|0xf8
suffix:colon
multiline_comment|/* Timer overflow */
r_break
suffix:semicolon
r_case
l_int|0xfc
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0xfd
suffix:colon
multiline_comment|/* XXX do something useful with this. If there is&n;&t;&t;&t;   an external MIDI timer (e.g. a hardware sequencer,&n;&t;&t;&t;   a useful timer can be derived ...&n;&t;&t;   &n;&t;&t;&t;   For now, no timer support.&n;&t;&t;&t;*/
r_break
suffix:semicolon
r_case
l_int|0xfe
suffix:colon
r_return
id|MPU_ACK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf0
suffix:colon
r_case
l_int|0xf1
suffix:colon
r_case
l_int|0xf2
suffix:colon
r_case
l_int|0xf3
suffix:colon
r_case
l_int|0xf4
suffix:colon
r_case
l_int|0xf5
suffix:colon
r_case
l_int|0xf6
suffix:colon
r_case
l_int|0xf7
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0xf9
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0xff
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_SYSMSG
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|midic
op_le
l_int|0xef
)paren
(brace
id|mi-&gt;m_state
op_assign
id|MST_TIMED
suffix:semicolon
)brace
r_else
id|printk
(paren
id|KERN_ERR
l_string|&quot;&lt;MPU: Unknown event %02x&gt; &quot;
comma
id|midic
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|MST_TIMED
suffix:colon
(brace
r_int
id|msg
op_assign
(paren
(paren
r_int
)paren
(paren
id|midic
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
id|mi-&gt;m_state
op_assign
id|MST_DATA
suffix:semicolon
r_if
c_cond
(paren
id|msg
OL
l_int|8
)paren
(brace
multiline_comment|/* Data byte */
id|msg
op_assign
(paren
(paren
r_int
)paren
(paren
id|mi-&gt;m_prev_status
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
id|msg
op_sub_assign
l_int|8
suffix:semicolon
id|mi-&gt;m_left
op_assign
id|len_tab
(braket
id|msg
)braket
op_minus
l_int|1
suffix:semicolon
id|mi-&gt;m_ptr
op_assign
l_int|2
suffix:semicolon
id|mi-&gt;m_buf
(braket
l_int|0
)braket
op_assign
id|mi-&gt;m_prev_status
suffix:semicolon
id|mi-&gt;m_buf
(braket
l_int|1
)braket
op_assign
id|midic
suffix:semicolon
r_if
c_cond
(paren
id|mi-&gt;m_left
op_le
l_int|0
)paren
(brace
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
id|do_midi_msg
(paren
id|synthdev
comma
id|mi-&gt;m_buf
comma
id|mi-&gt;m_ptr
)paren
suffix:semicolon
id|mi-&gt;m_ptr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|msg
op_eq
l_int|0xf
)paren
(brace
multiline_comment|/* MPU MARK */
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
r_switch
c_cond
(paren
id|midic
)paren
(brace
r_case
l_int|0xf8
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0xf9
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0xfc
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|mi-&gt;m_prev_status
op_assign
id|midic
suffix:semicolon
id|msg
op_sub_assign
l_int|8
suffix:semicolon
id|mi-&gt;m_left
op_assign
id|len_tab
(braket
id|msg
)braket
suffix:semicolon
id|mi-&gt;m_ptr
op_assign
l_int|1
suffix:semicolon
id|mi-&gt;m_buf
(braket
l_int|0
)braket
op_assign
id|midic
suffix:semicolon
r_if
c_cond
(paren
id|mi-&gt;m_left
op_le
l_int|0
)paren
(brace
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
id|do_midi_msg
(paren
id|synthdev
comma
id|mi-&gt;m_buf
comma
id|mi-&gt;m_ptr
)paren
suffix:semicolon
id|mi-&gt;m_ptr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_break
suffix:semicolon
r_case
id|MST_SYSMSG
suffix:colon
r_switch
c_cond
(paren
id|midic
)paren
(brace
r_case
l_int|0xf0
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_SYSEX
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf1
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_MTC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf2
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_SONGPOS
suffix:semicolon
id|mi-&gt;m_ptr
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf3
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_SONGSEL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf6
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *    Real time messages&n;&t;&t;&t; */
r_case
l_int|0xf8
suffix:colon
multiline_comment|/* midi clock */
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
multiline_comment|/* XXX need ext MIDI timer support */
r_break
suffix:semicolon
r_case
l_int|0xfA
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
multiline_comment|/* XXX need ext MIDI timer support */
r_break
suffix:semicolon
r_case
l_int|0xFB
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
multiline_comment|/* XXX need ext MIDI timer support */
r_break
suffix:semicolon
r_case
l_int|0xFC
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
multiline_comment|/* XXX need ext MIDI timer support */
r_break
suffix:semicolon
r_case
l_int|0xFE
suffix:colon
multiline_comment|/* active sensing */
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xff
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
id|KERN_ERR
l_string|&quot;unknown MIDI sysmsg %0x&bslash;n&quot;
comma
id|midic
)paren
suffix:semicolon
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|MST_MTC
suffix:colon
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MST_SYSEX
suffix:colon
r_if
c_cond
(paren
id|midic
op_eq
l_int|0xf7
)paren
(brace
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* XXX fix me */
)brace
r_break
suffix:semicolon
r_case
id|MST_SONGPOS
suffix:colon
id|BUFTEST
(paren
id|mi
)paren
suffix:semicolon
id|mi-&gt;m_buf
(braket
id|mi-&gt;m_ptr
op_increment
)braket
op_assign
id|midic
suffix:semicolon
r_if
c_cond
(paren
id|mi-&gt;m_ptr
op_eq
l_int|2
)paren
(brace
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
id|mi-&gt;m_ptr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX need ext MIDI timer support */
)brace
r_break
suffix:semicolon
r_case
id|MST_DATA
suffix:colon
id|BUFTEST
(paren
id|mi
)paren
suffix:semicolon
id|mi-&gt;m_buf
(braket
id|mi-&gt;m_ptr
op_increment
)braket
op_assign
id|midic
suffix:semicolon
r_if
c_cond
(paren
(paren
op_decrement
id|mi-&gt;m_left
)paren
op_le
l_int|0
)paren
(brace
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
id|do_midi_msg
(paren
id|synthdev
comma
id|mi-&gt;m_buf
comma
id|mi-&gt;m_ptr
)paren
suffix:semicolon
id|mi-&gt;m_ptr
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
id|KERN_ERR
l_string|&quot;Bad state %d &quot;
comma
id|mi-&gt;m_state
)paren
suffix:semicolon
id|mi-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|wf_mpuintr
id|wf_mpuintr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|dummy
)paren
(brace
r_struct
id|wf_mpu_config
op_star
id|physical_dev
op_assign
id|dev_id
suffix:semicolon
r_static
r_struct
id|wf_mpu_config
op_star
id|input_dev
op_assign
l_int|0
suffix:semicolon
r_struct
id|midi_input_info
op_star
id|mi
op_assign
op_amp
id|midi_devs
(braket
id|physical_dev-&gt;devno
)braket
op_member_access_from_pointer
id|in_info
suffix:semicolon
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|input_avail
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* not for us */
r_return
id|IRQ_NONE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mi-&gt;m_busy
)paren
r_return
id|IRQ_HANDLED
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|mi-&gt;m_busy
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|input_dev
)paren
(brace
id|input_dev
op_assign
id|physical_dev
suffix:semicolon
)brace
id|n
op_assign
l_int|50
suffix:semicolon
multiline_comment|/* XXX why ? */
r_do
(brace
r_int
r_char
id|c
op_assign
id|read_data
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phys_dev-&gt;isvirtual
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
id|WF_EXTERNAL_SWITCH
)paren
(brace
id|input_dev
op_assign
id|virt_dev
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
id|WF_INTERNAL_SWITCH
)paren
(brace
id|input_dev
op_assign
id|phys_dev
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* else just leave it as it is */
)brace
r_else
(brace
id|input_dev
op_assign
id|phys_dev
suffix:semicolon
)brace
r_if
c_cond
(paren
id|input_dev-&gt;mode
op_eq
id|MODE_SYNTH
)paren
(brace
id|wf_mpu_input_scanner
(paren
id|input_dev-&gt;devno
comma
id|input_dev-&gt;synthno
comma
id|c
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|input_dev-&gt;opened
op_amp
id|OPEN_READ
)paren
(brace
r_if
c_cond
(paren
id|input_dev-&gt;inputintr
)paren
(brace
id|input_dev-&gt;inputintr
(paren
id|input_dev-&gt;devno
comma
id|c
)paren
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
id|input_avail
c_func
(paren
)paren
op_logical_and
id|n
op_decrement
OG
l_int|0
)paren
suffix:semicolon
id|mi-&gt;m_busy
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
r_int
DECL|function|wf_mpu_open
id|wf_mpu_open
(paren
r_int
id|dev
comma
r_int
id|mode
comma
r_void
(paren
op_star
id|input
)paren
(paren
r_int
id|dev
comma
r_int
r_char
id|data
)paren
comma
r_void
(paren
op_star
id|output
)paren
(paren
r_int
id|dev
)paren
)paren
(brace
r_struct
id|wf_mpu_config
op_star
id|devc
suffix:semicolon
r_if
c_cond
(paren
id|dev
OL
l_int|0
op_logical_or
id|dev
op_ge
id|num_midis
op_logical_or
id|midi_devs
(braket
id|dev
)braket
op_eq
l_int|NULL
)paren
r_return
op_minus
(paren
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phys_dev-&gt;devno
op_eq
id|dev
)paren
(brace
id|devc
op_assign
id|phys_dev
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|phys_dev-&gt;isvirtual
op_logical_and
id|virt_dev-&gt;devno
op_eq
id|dev
)paren
(brace
id|devc
op_assign
id|virt_dev
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;WF-MPU: unknown device number %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|devc-&gt;opened
)paren
(brace
r_return
op_minus
(paren
id|EBUSY
)paren
suffix:semicolon
)brace
id|devc-&gt;mode
op_assign
id|MODE_MIDI
suffix:semicolon
id|devc-&gt;opened
op_assign
id|mode
suffix:semicolon
id|devc-&gt;synthno
op_assign
l_int|0
suffix:semicolon
id|devc-&gt;inputintr
op_assign
id|input
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|wf_mpu_close
id|wf_mpu_close
(paren
r_int
id|dev
)paren
(brace
r_struct
id|wf_mpu_config
op_star
id|devc
suffix:semicolon
r_if
c_cond
(paren
id|dev
OL
l_int|0
op_logical_or
id|dev
op_ge
id|num_midis
op_logical_or
id|midi_devs
(braket
id|dev
)braket
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|phys_dev-&gt;devno
op_eq
id|dev
)paren
(brace
id|devc
op_assign
id|phys_dev
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|phys_dev-&gt;isvirtual
op_logical_and
id|virt_dev-&gt;devno
op_eq
id|dev
)paren
(brace
id|devc
op_assign
id|virt_dev
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;WF-MPU: unknown device number %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|devc-&gt;mode
op_assign
l_int|0
suffix:semicolon
id|devc-&gt;inputintr
op_assign
l_int|NULL
suffix:semicolon
id|devc-&gt;opened
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|wf_mpu_out
id|wf_mpu_out
(paren
r_int
id|dev
comma
r_int
r_char
id|midi_byte
)paren
(brace
r_int
id|timeout
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_static
r_int
id|lastoutdev
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
r_char
id|switchch
suffix:semicolon
r_if
c_cond
(paren
id|phys_dev-&gt;isvirtual
op_logical_and
id|lastoutdev
op_ne
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev
op_eq
id|phys_dev-&gt;devno
)paren
(brace
id|switchch
op_assign
id|WF_INTERNAL_SWITCH
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev
op_eq
id|virt_dev-&gt;devno
)paren
(brace
id|switchch
op_assign
id|WF_EXTERNAL_SWITCH
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;WF-MPU: bad device number %d&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX fix me */
r_for
c_loop
(paren
id|timeout
op_assign
l_int|30000
suffix:semicolon
id|timeout
OG
l_int|0
op_logical_and
op_logical_neg
id|output_ready
(paren
)paren
suffix:semicolon
id|timeout
op_decrement
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|output_ready
(paren
)paren
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;WF-MPU: Send switch &quot;
l_string|&quot;byte timeout&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|write_data
(paren
id|switchch
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|lastoutdev
op_assign
id|dev
suffix:semicolon
multiline_comment|/*&n;&t; * Sometimes it takes about 30000 loops before the output becomes ready&n;&t; * (After reset). Normally it takes just about 10 loops.&n;&t; */
multiline_comment|/* XXX fix me */
r_for
c_loop
(paren
id|timeout
op_assign
l_int|30000
suffix:semicolon
id|timeout
OG
l_int|0
op_logical_and
op_logical_neg
id|output_ready
(paren
)paren
suffix:semicolon
id|timeout
op_decrement
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|output_ready
(paren
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
id|printk
(paren
id|KERN_WARNING
l_string|&quot;WF-MPU: Send data timeout&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|write_data
(paren
id|midi_byte
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|wf_mpu_start_read
r_static
r_inline
r_int
id|wf_mpu_start_read
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|wf_mpu_end_read
r_static
r_inline
r_int
id|wf_mpu_end_read
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|wf_mpu_ioctl
r_static
r_int
id|wf_mpu_ioctl
(paren
r_int
id|dev
comma
r_int
id|cmd
comma
id|caddr_t
id|arg
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;WF-MPU: Intelligent mode not supported by hardware.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
DECL|function|wf_mpu_buffer_status
r_static
r_int
id|wf_mpu_buffer_status
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|wf_mpu_synth_operations
r_static
r_struct
id|synth_operations
id|wf_mpu_synth_operations
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|wf_mpu_midi_operations
r_static
r_struct
id|midi_operations
id|wf_mpu_midi_operations
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|wf_mpu_midi_proto
r_static
r_struct
id|midi_operations
id|wf_mpu_midi_proto
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|info
op_assign
(brace
l_string|&quot;WF-MPU MIDI&quot;
comma
l_int|0
comma
id|MIDI_CAP_MPU401
comma
id|SNDCARD_MPU401
)brace
comma
dot
id|in_info
op_assign
(brace
l_int|0
)brace
comma
multiline_comment|/* in_info */
dot
id|open
op_assign
id|wf_mpu_open
comma
dot
id|close
op_assign
id|wf_mpu_close
comma
dot
id|ioctl
op_assign
id|wf_mpu_ioctl
comma
dot
id|outputc
op_assign
id|wf_mpu_out
comma
dot
id|start_read
op_assign
id|wf_mpu_start_read
comma
dot
id|end_read
op_assign
id|wf_mpu_end_read
comma
dot
id|buffer_status
op_assign
id|wf_mpu_buffer_status
comma
)brace
suffix:semicolon
DECL|variable|wf_mpu_synth_info_proto
r_static
r_struct
id|synth_info
id|wf_mpu_synth_info_proto
op_assign
(brace
l_string|&quot;WaveFront MPU-401 interface&quot;
comma
l_int|0
comma
id|SYNTH_TYPE_MIDI
comma
id|MIDI_TYPE_MPU401
comma
l_int|0
comma
l_int|128
comma
l_int|0
comma
l_int|128
comma
id|SYNTH_CAP_INPUT
)brace
suffix:semicolon
DECL|variable|wf_mpu_synth_info
r_static
r_struct
id|synth_info
id|wf_mpu_synth_info
(braket
l_int|2
)braket
suffix:semicolon
r_static
r_int
DECL|function|wf_mpu_synth_ioctl
id|wf_mpu_synth_ioctl
(paren
r_int
id|dev
comma
r_int
r_int
id|cmd
comma
id|caddr_t
id|arg
)paren
(brace
r_int
id|midi_dev
suffix:semicolon
r_int
id|index
suffix:semicolon
id|midi_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_if
c_cond
(paren
id|midi_dev
template_param
id|num_midis
op_logical_or
id|midi_devs
(braket
id|midi_dev
)braket
op_eq
l_int|NULL
)paren
r_return
op_minus
(paren
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|midi_dev
op_eq
id|phys_dev-&gt;devno
)paren
(brace
id|index
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|phys_dev-&gt;isvirtual
op_logical_and
id|midi_dev
op_eq
id|virt_dev-&gt;devno
)paren
(brace
id|index
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDCTL_SYNTH_INFO
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
(paren
op_amp
(paren
(paren
r_char
op_star
)paren
id|arg
)paren
(braket
l_int|0
)braket
comma
op_amp
id|wf_mpu_synth_info
(braket
id|index
)braket
comma
r_sizeof
(paren
r_struct
id|synth_info
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|SNDCTL_SYNTH_MEMAVL
suffix:colon
r_return
l_int|0x7fffffff
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|wf_mpu_synth_open
id|wf_mpu_synth_open
(paren
r_int
id|dev
comma
r_int
id|mode
)paren
(brace
r_int
id|midi_dev
suffix:semicolon
r_struct
id|wf_mpu_config
op_star
id|devc
suffix:semicolon
id|midi_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_if
c_cond
(paren
id|midi_dev
template_param
id|num_midis
op_logical_or
id|midi_devs
(braket
id|midi_dev
)braket
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
(paren
id|ENXIO
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|phys_dev-&gt;devno
op_eq
id|midi_dev
)paren
(brace
id|devc
op_assign
id|phys_dev
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|phys_dev-&gt;isvirtual
op_logical_and
id|virt_dev-&gt;devno
op_eq
id|midi_dev
)paren
(brace
id|devc
op_assign
id|virt_dev
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;WF-MPU: unknown device number %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|devc-&gt;opened
)paren
(brace
r_return
op_minus
(paren
id|EBUSY
)paren
suffix:semicolon
)brace
id|devc-&gt;mode
op_assign
id|MODE_SYNTH
suffix:semicolon
id|devc-&gt;synthno
op_assign
id|dev
suffix:semicolon
id|devc-&gt;opened
op_assign
id|mode
suffix:semicolon
id|devc-&gt;inputintr
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|wf_mpu_synth_close
id|wf_mpu_synth_close
(paren
r_int
id|dev
)paren
(brace
r_int
id|midi_dev
suffix:semicolon
r_struct
id|wf_mpu_config
op_star
id|devc
suffix:semicolon
id|midi_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_if
c_cond
(paren
id|phys_dev-&gt;devno
op_eq
id|midi_dev
)paren
(brace
id|devc
op_assign
id|phys_dev
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|phys_dev-&gt;isvirtual
op_logical_and
id|virt_dev-&gt;devno
op_eq
id|midi_dev
)paren
(brace
id|devc
op_assign
id|virt_dev
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;WF-MPU: unknown device number %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|devc-&gt;inputintr
op_assign
l_int|NULL
suffix:semicolon
id|devc-&gt;opened
op_assign
l_int|0
suffix:semicolon
id|devc-&gt;mode
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|_MIDI_SYNTH_C_
mdefine_line|#define _MIDI_SYNTH_C_
DECL|macro|MIDI_SYNTH_NAME
mdefine_line|#define MIDI_SYNTH_NAME&t;&quot;WaveFront (MIDI)&quot;
DECL|macro|MIDI_SYNTH_CAPS
mdefine_line|#define MIDI_SYNTH_CAPS&t;SYNTH_CAP_INPUT
macro_line|#include &quot;midi_synth.h&quot;
DECL|variable|wf_mpu_synth_proto
r_static
r_struct
id|synth_operations
id|wf_mpu_synth_proto
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|id
op_assign
l_string|&quot;WaveFront (ICS2115)&quot;
comma
dot
id|info
op_assign
l_int|NULL
comma
multiline_comment|/* info field, filled in during configuration */
dot
id|midi_dev
op_assign
l_int|0
comma
multiline_comment|/* MIDI dev XXX should this be -1 ? */
dot
id|synth_type
op_assign
id|SYNTH_TYPE_MIDI
comma
dot
id|synth_subtype
op_assign
id|SAMPLE_TYPE_WAVEFRONT
comma
dot
id|open
op_assign
id|wf_mpu_synth_open
comma
dot
id|close
op_assign
id|wf_mpu_synth_close
comma
dot
id|ioctl
op_assign
id|wf_mpu_synth_ioctl
comma
dot
id|kill_note
op_assign
id|midi_synth_kill_note
comma
dot
id|start_note
op_assign
id|midi_synth_start_note
comma
dot
id|set_instr
op_assign
id|midi_synth_set_instr
comma
dot
id|reset
op_assign
id|midi_synth_reset
comma
dot
id|hw_control
op_assign
id|midi_synth_hw_control
comma
dot
id|load_patch
op_assign
id|midi_synth_load_patch
comma
dot
id|aftertouch
op_assign
id|midi_synth_aftertouch
comma
dot
id|controller
op_assign
id|midi_synth_controller
comma
dot
id|panning
op_assign
id|midi_synth_panning
comma
dot
id|bender
op_assign
id|midi_synth_bender
comma
dot
id|setup_voice
op_assign
id|midi_synth_setup_voice
comma
dot
id|send_sysex
op_assign
id|midi_synth_send_sysex
)brace
suffix:semicolon
r_static
r_int
DECL|function|config_wf_mpu
id|config_wf_mpu
(paren
r_struct
id|wf_mpu_config
op_star
id|dev
)paren
(brace
r_int
id|is_external
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
id|phys_dev
)paren
(brace
id|name
op_assign
l_string|&quot;WaveFront internal MIDI&quot;
suffix:semicolon
id|is_external
op_assign
l_int|0
suffix:semicolon
id|index
op_assign
l_int|0
suffix:semicolon
id|memcpy
(paren
(paren
r_char
op_star
)paren
op_amp
id|wf_mpu_synth_operations
(braket
id|index
)braket
comma
(paren
r_char
op_star
)paren
op_amp
id|wf_mpu_synth_proto
comma
r_sizeof
(paren
r_struct
id|synth_operations
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|name
op_assign
l_string|&quot;WaveFront external MIDI&quot;
suffix:semicolon
id|is_external
op_assign
l_int|1
suffix:semicolon
id|index
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* no synth operations for an external MIDI interface */
)brace
id|memcpy
(paren
(paren
r_char
op_star
)paren
op_amp
id|wf_mpu_synth_info
(braket
id|dev-&gt;devno
)braket
comma
(paren
r_char
op_star
)paren
op_amp
id|wf_mpu_synth_info_proto
comma
r_sizeof
(paren
r_struct
id|synth_info
)paren
)paren
suffix:semicolon
id|strcpy
(paren
id|wf_mpu_synth_info
(braket
id|index
)braket
dot
id|name
comma
id|name
)paren
suffix:semicolon
id|wf_mpu_synth_operations
(braket
id|index
)braket
dot
id|midi_dev
op_assign
id|dev-&gt;devno
suffix:semicolon
id|wf_mpu_synth_operations
(braket
id|index
)braket
dot
id|info
op_assign
op_amp
id|wf_mpu_synth_info
(braket
id|index
)braket
suffix:semicolon
id|memcpy
(paren
(paren
r_char
op_star
)paren
op_amp
id|wf_mpu_midi_operations
(braket
id|index
)braket
comma
(paren
r_char
op_star
)paren
op_amp
id|wf_mpu_midi_proto
comma
r_sizeof
(paren
r_struct
id|midi_operations
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_external
)paren
(brace
id|wf_mpu_midi_operations
(braket
id|index
)braket
dot
id|converter
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|wf_mpu_midi_operations
(braket
id|index
)braket
dot
id|converter
op_assign
op_amp
id|wf_mpu_synth_operations
(braket
id|index
)braket
suffix:semicolon
)brace
id|strcpy
(paren
id|wf_mpu_midi_operations
(braket
id|index
)braket
dot
id|info.name
comma
id|name
)paren
suffix:semicolon
id|midi_devs
(braket
id|dev-&gt;devno
)braket
op_assign
op_amp
id|wf_mpu_midi_operations
(braket
id|index
)braket
suffix:semicolon
id|midi_devs
(braket
id|dev-&gt;devno
)braket
op_member_access_from_pointer
id|in_info.m_busy
op_assign
l_int|0
suffix:semicolon
id|midi_devs
(braket
id|dev-&gt;devno
)braket
op_member_access_from_pointer
id|in_info.m_state
op_assign
id|MST_INIT
suffix:semicolon
id|midi_devs
(braket
id|dev-&gt;devno
)braket
op_member_access_from_pointer
id|in_info.m_ptr
op_assign
l_int|0
suffix:semicolon
id|midi_devs
(braket
id|dev-&gt;devno
)braket
op_member_access_from_pointer
id|in_info.m_left
op_assign
l_int|0
suffix:semicolon
id|midi_devs
(braket
id|dev-&gt;devno
)braket
op_member_access_from_pointer
id|in_info.m_prev_status
op_assign
l_int|0
suffix:semicolon
id|devs
(braket
id|index
)braket
dot
id|opened
op_assign
l_int|0
suffix:semicolon
id|devs
(braket
id|index
)braket
dot
id|mode
op_assign
l_int|0
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|virtual_midi_enable
r_int
id|virtual_midi_enable
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|virt_dev-&gt;devno
OL
l_int|0
)paren
op_logical_and
(paren
id|virt_dev-&gt;devno
op_assign
id|sound_alloc_mididev
c_func
(paren
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;WF-MPU: too many midi devices detected&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|config_wf_mpu
(paren
id|virt_dev
)paren
suffix:semicolon
id|phys_dev-&gt;isvirtual
op_assign
l_int|1
suffix:semicolon
r_return
id|virt_dev-&gt;devno
suffix:semicolon
)brace
r_int
DECL|function|virtual_midi_disable
id|virtual_midi_disable
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
id|wf_mpu_close
(paren
id|virt_dev-&gt;devno
)paren
suffix:semicolon
multiline_comment|/* no synth on virt_dev, so no need to call wf_mpu_synth_close() */
id|phys_dev-&gt;isvirtual
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|detect_wf_mpu
r_int
id|__init
id|detect_wf_mpu
(paren
r_int
id|irq
comma
r_int
id|io_base
)paren
(brace
r_if
c_cond
(paren
id|check_region
(paren
id|io_base
comma
l_int|2
)paren
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;WF-MPU: I/O port %x already in use.&bslash;n&quot;
comma
id|io_base
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|phys_dev-&gt;base
op_assign
id|io_base
suffix:semicolon
id|phys_dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|phys_dev-&gt;devno
op_assign
op_minus
l_int|1
suffix:semicolon
id|virt_dev-&gt;devno
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|install_wf_mpu
r_int
id|__init
id|install_wf_mpu
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|phys_dev-&gt;devno
op_assign
id|sound_alloc_mididev
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;WF-MPU: Too many MIDI devices detected.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|request_region
(paren
id|phys_dev-&gt;base
comma
l_int|2
comma
l_string|&quot;wavefront midi&quot;
)paren
suffix:semicolon
id|phys_dev-&gt;isvirtual
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|config_wf_mpu
(paren
id|phys_dev
)paren
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;WF-MPU: configuration for MIDI device %d failed&bslash;n&quot;
comma
id|phys_dev-&gt;devno
)paren
suffix:semicolon
id|sound_unload_mididev
(paren
id|phys_dev-&gt;devno
)paren
suffix:semicolon
)brace
multiline_comment|/* OK, now we&squot;re configured to handle an interrupt ... */
r_if
c_cond
(paren
id|request_irq
(paren
id|phys_dev-&gt;irq
comma
id|wf_mpuintr
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
comma
l_string|&quot;wavefront midi&quot;
comma
id|phys_dev
)paren
OL
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;WF-MPU: Failed to allocate IRQ%d&bslash;n&quot;
comma
id|phys_dev-&gt;irq
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This being a WaveFront (ICS-2115) emulated MPU-401, we have&n;&t;   to switch it into UART (dumb) mode, because otherwise, it&n;&t;   won&squot;t do anything at all.&n;&t;*/
id|start_uart_mode
(paren
)paren
suffix:semicolon
r_return
id|phys_dev-&gt;devno
suffix:semicolon
)brace
r_void
DECL|function|uninstall_wf_mpu
id|uninstall_wf_mpu
(paren
r_void
)paren
(brace
id|release_region
(paren
id|phys_dev-&gt;base
comma
l_int|2
)paren
suffix:semicolon
id|free_irq
(paren
id|phys_dev-&gt;irq
comma
id|phys_dev
)paren
suffix:semicolon
id|sound_unload_mididev
(paren
id|phys_dev-&gt;devno
)paren
suffix:semicolon
r_if
c_cond
(paren
id|virt_dev-&gt;devno
op_ge
l_int|0
)paren
(brace
id|sound_unload_mididev
(paren
id|virt_dev-&gt;devno
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|start_uart_mode
id|start_uart_mode
(paren
r_void
)paren
(brace
r_int
id|ok
comma
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* XXX fix me */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|30000
op_logical_and
op_logical_neg
id|output_ready
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
id|outb
(paren
id|UART_MODE_ON
comma
id|COMDPORT
c_func
(paren
id|phys_dev
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ok
op_assign
l_int|0
comma
id|i
op_assign
l_int|50000
suffix:semicolon
id|i
OG
l_int|0
op_logical_and
op_logical_neg
id|ok
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|input_avail
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|read_data
(paren
)paren
op_eq
id|MPU_ACK
)paren
(brace
id|ok
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
