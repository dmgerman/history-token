DECL|macro|USB_DT_CS_DEVICE
mdefine_line|#define USB_DT_CS_DEVICE                0x21
DECL|macro|USB_DT_CS_CONFIG
mdefine_line|#define USB_DT_CS_CONFIG                0x22
DECL|macro|USB_DT_CS_STRING
mdefine_line|#define USB_DT_CS_STRING                0x23
DECL|macro|USB_DT_CS_INTERFACE
mdefine_line|#define USB_DT_CS_INTERFACE             0x24
DECL|macro|USB_DT_CS_ENDPOINT
mdefine_line|#define USB_DT_CS_ENDPOINT              0x25
DECL|macro|CS_AUDIO_UNDEFINED
mdefine_line|#define CS_AUDIO_UNDEFINED&t;&t;0x20
DECL|macro|CS_AUDIO_DEVICE
mdefine_line|#define CS_AUDIO_DEVICE&t;&t;&t;0x21
DECL|macro|CS_AUDIO_CONFIGURATION
mdefine_line|#define CS_AUDIO_CONFIGURATION&t;&t;0x22
DECL|macro|CS_AUDIO_STRING
mdefine_line|#define CS_AUDIO_STRING&t;&t;&t;0x23
DECL|macro|CS_AUDIO_INTERFACE
mdefine_line|#define CS_AUDIO_INTERFACE&t;&t;0x24
DECL|macro|CS_AUDIO_ENDPOINT
mdefine_line|#define CS_AUDIO_ENDPOINT&t;&t;0x25
DECL|macro|HEADER
mdefine_line|#define HEADER&t;&t;&t;&t;0x01
DECL|macro|INPUT_TERMINAL
mdefine_line|#define INPUT_TERMINAL&t;&t;&t;0x02
DECL|macro|OUTPUT_TERMINAL
mdefine_line|#define OUTPUT_TERMINAL&t;&t;&t;0x03
DECL|macro|MIXER_UNIT
mdefine_line|#define MIXER_UNIT&t;&t;&t;0x04
DECL|macro|SELECTOR_UNIT
mdefine_line|#define SELECTOR_UNIT&t;&t;&t;0x05
DECL|macro|FEATURE_UNIT
mdefine_line|#define FEATURE_UNIT&t;&t;&t;0x06
DECL|macro|PROCESSING_UNIT
mdefine_line|#define PROCESSING_UNIT&t;&t;&t;0x07
DECL|macro|EXTENSION_UNIT
mdefine_line|#define EXTENSION_UNIT&t;&t;&t;0x08
DECL|macro|AS_GENERAL
mdefine_line|#define AS_GENERAL&t;&t;&t;0x01
DECL|macro|FORMAT_TYPE
mdefine_line|#define FORMAT_TYPE&t;&t;&t;0x02
DECL|macro|FORMAT_SPECIFIC
mdefine_line|#define FORMAT_SPECIFIC&t;&t;&t;0x03
DECL|macro|EP_GENERAL
mdefine_line|#define EP_GENERAL&t;&t;&t;0x01
DECL|macro|MAX_CHAN
mdefine_line|#define MAX_CHAN&t;&t;&t;9
DECL|macro|MAX_FREQ
mdefine_line|#define MAX_FREQ&t;&t;&t;16
DECL|macro|MAX_IFACE
mdefine_line|#define MAX_IFACE&t;&t;&t;8
DECL|macro|MAX_FORMAT
mdefine_line|#define MAX_FORMAT&t;&t;&t;8
DECL|macro|MAX_ALT
mdefine_line|#define MAX_ALT&t;&t;&t;&t;32 &t;/* Sorry, we need quite a few for the Philips webcams */
DECL|struct|usb_audio_terminal
r_struct
id|usb_audio_terminal
(brace
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|assoc
id|u8
id|assoc
suffix:semicolon
DECL|member|type
id|u16
id|type
suffix:semicolon
multiline_comment|/* Mic etc */
DECL|member|channels
id|u8
id|channels
suffix:semicolon
DECL|member|source
id|u8
id|source
suffix:semicolon
DECL|member|chancfg
id|u16
id|chancfg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usb_audio_format
r_struct
id|usb_audio_format
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|channels
id|u8
id|channels
suffix:semicolon
DECL|member|num_freq
id|u8
id|num_freq
suffix:semicolon
DECL|member|sfz
id|u8
id|sfz
suffix:semicolon
DECL|member|bits
id|u8
id|bits
suffix:semicolon
DECL|member|freq
id|u16
id|freq
(braket
id|MAX_FREQ
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usb_audio_interface
r_struct
id|usb_audio_interface
(brace
DECL|member|terminal
id|u8
id|terminal
suffix:semicolon
DECL|member|delay
id|u8
id|delay
suffix:semicolon
DECL|member|num_formats
id|u16
id|num_formats
suffix:semicolon
DECL|member|format_type
id|u16
id|format_type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|idleconf
id|u8
id|idleconf
suffix:semicolon
multiline_comment|/* Idle config */
DECL|macro|AU_IFACE_FOUND
mdefine_line|#define AU_IFACE_FOUND&t;1
DECL|member|format
r_struct
id|usb_audio_format
id|format
(braket
id|MAX_FORMAT
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usb_audio_device
r_struct
id|usb_audio_device
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|mixer
id|u8
id|mixer
suffix:semicolon
DECL|member|selector
id|u8
id|selector
suffix:semicolon
DECL|member|irq_handle
r_void
op_star
id|irq_handle
suffix:semicolon
DECL|member|num_channels
id|u8
id|num_channels
suffix:semicolon
DECL|member|num_dsp_iface
id|u8
id|num_dsp_iface
suffix:semicolon
DECL|member|channel_map
id|u8
id|channel_map
(braket
id|MAX_CHAN
)braket
suffix:semicolon
DECL|member|terminal
r_struct
id|usb_audio_terminal
id|terminal
(braket
id|MAX_CHAN
)braket
suffix:semicolon
DECL|member|interface
r_struct
id|usb_audio_interface
id|interface
(braket
id|MAX_IFACE
)braket
(braket
id|MAX_ALT
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Audio Class specific Request Codes */
DECL|macro|SET_CUR
mdefine_line|#define SET_CUR    0x01
DECL|macro|GET_CUR
mdefine_line|#define GET_CUR    0x81
DECL|macro|SET_MIN
mdefine_line|#define SET_MIN    0x02
DECL|macro|GET_MIN
mdefine_line|#define GET_MIN    0x82
DECL|macro|SET_MAX
mdefine_line|#define SET_MAX    0x03
DECL|macro|GET_MAX
mdefine_line|#define GET_MAX    0x83
DECL|macro|SET_RES
mdefine_line|#define SET_RES    0x04
DECL|macro|GET_RES
mdefine_line|#define GET_RES    0x84
DECL|macro|SET_MEM
mdefine_line|#define SET_MEM    0x05
DECL|macro|GET_MEM
mdefine_line|#define GET_MEM    0x85
DECL|macro|GET_STAT
mdefine_line|#define GET_STAT   0xff
multiline_comment|/* Terminal Control Selectors */
DECL|macro|COPY_PROTECT_CONTROL
mdefine_line|#define COPY_PROTECT_CONTROL       0x01
multiline_comment|/* Feature Unit Control Selectors */
DECL|macro|MUTE_CONTROL
mdefine_line|#define MUTE_CONTROL               0x01
DECL|macro|VOLUME_CONTROL
mdefine_line|#define VOLUME_CONTROL             0x02
DECL|macro|BASS_CONTROL
mdefine_line|#define BASS_CONTROL               0x03
DECL|macro|MID_CONTROL
mdefine_line|#define MID_CONTROL                0x04
DECL|macro|TREBLE_CONTROL
mdefine_line|#define TREBLE_CONTROL             0x05
DECL|macro|GRAPHIC_EQUALIZER_CONTROL
mdefine_line|#define GRAPHIC_EQUALIZER_CONTROL  0x06
DECL|macro|AUTOMATIC_GAIN_CONTROL
mdefine_line|#define AUTOMATIC_GAIN_CONTROL     0x07
DECL|macro|DELAY_CONTROL
mdefine_line|#define DELAY_CONTROL              0x08
DECL|macro|BASS_BOOST_CONTROL
mdefine_line|#define BASS_BOOST_CONTROL         0x09
DECL|macro|LOUDNESS_CONTROL
mdefine_line|#define LOUDNESS_CONTROL           0x0a
multiline_comment|/* Endpoint Control Selectors */
DECL|macro|SAMPLING_FREQ_CONTROL
mdefine_line|#define SAMPLING_FREQ_CONTROL      0x01
DECL|macro|PITCH_CONTROL
mdefine_line|#define PITCH_CONTROL              0x02
eof
