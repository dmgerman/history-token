DECL|struct|vmidi_devc
r_typedef
r_struct
id|vmidi_devc
(brace
DECL|member|dev
r_int
id|dev
suffix:semicolon
multiline_comment|/* State variables */
DECL|member|opened
r_int
id|opened
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* MIDI fields */
DECL|member|my_mididev
r_int
id|my_mididev
suffix:semicolon
DECL|member|pair_mididev
r_int
id|pair_mididev
suffix:semicolon
DECL|member|input_opened
r_int
id|input_opened
suffix:semicolon
DECL|member|intr_active
r_int
id|intr_active
suffix:semicolon
DECL|member|midi_input_intr
r_void
(paren
op_star
id|midi_input_intr
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
DECL|typedef|vmidi_devc
)brace
id|vmidi_devc
suffix:semicolon
eof
