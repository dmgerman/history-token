r_int
id|midi_synth_ioctl
(paren
r_int
id|dev
comma
r_int
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
suffix:semicolon
r_int
id|midi_synth_kill_note
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|note
comma
r_int
id|velocity
)paren
suffix:semicolon
r_int
id|midi_synth_set_instr
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|instr_no
)paren
suffix:semicolon
r_int
id|midi_synth_start_note
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|note
comma
r_int
id|volume
)paren
suffix:semicolon
r_void
id|midi_synth_reset
(paren
r_int
id|dev
)paren
suffix:semicolon
r_int
id|midi_synth_open
(paren
r_int
id|dev
comma
r_int
id|mode
)paren
suffix:semicolon
r_void
id|midi_synth_close
(paren
r_int
id|dev
)paren
suffix:semicolon
r_void
id|midi_synth_hw_control
(paren
r_int
id|dev
comma
r_int
r_char
op_star
id|event
)paren
suffix:semicolon
r_int
id|midi_synth_load_patch
(paren
r_int
id|dev
comma
r_int
id|format
comma
r_const
r_char
id|__user
op_star
id|addr
comma
r_int
id|offs
comma
r_int
id|count
comma
r_int
id|pmgr_flag
)paren
suffix:semicolon
r_void
id|midi_synth_panning
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|pressure
)paren
suffix:semicolon
r_void
id|midi_synth_aftertouch
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|pressure
)paren
suffix:semicolon
r_void
id|midi_synth_controller
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|ctrl_num
comma
r_int
id|value
)paren
suffix:semicolon
r_void
id|midi_synth_bender
(paren
r_int
id|dev
comma
r_int
id|chn
comma
r_int
id|value
)paren
suffix:semicolon
r_void
id|midi_synth_setup_voice
(paren
r_int
id|dev
comma
r_int
id|voice
comma
r_int
id|chn
)paren
suffix:semicolon
r_int
id|midi_synth_send_sysex
c_func
(paren
r_int
id|dev
comma
r_int
r_char
op_star
id|bytes
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#ifndef _MIDI_SYNTH_C_
DECL|variable|std_synth_info
r_static
r_struct
id|synth_info
id|std_synth_info
op_assign
(brace
id|MIDI_SYNTH_NAME
comma
l_int|0
comma
id|SYNTH_TYPE_MIDI
comma
l_int|0
comma
l_int|0
comma
l_int|128
comma
l_int|0
comma
l_int|128
comma
id|MIDI_SYNTH_CAPS
)brace
suffix:semicolon
DECL|variable|std_midi_synth
r_static
r_struct
id|synth_operations
id|std_midi_synth
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
l_string|&quot;MIDI&quot;
comma
dot
id|info
op_assign
op_amp
id|std_synth_info
comma
dot
id|midi_dev
op_assign
l_int|0
comma
dot
id|synth_type
op_assign
id|SYNTH_TYPE_MIDI
comma
dot
id|synth_subtype
op_assign
l_int|0
comma
dot
id|open
op_assign
id|midi_synth_open
comma
dot
id|close
op_assign
id|midi_synth_close
comma
dot
id|ioctl
op_assign
id|midi_synth_ioctl
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
macro_line|#endif
eof
