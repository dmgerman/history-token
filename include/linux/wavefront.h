macro_line|#ifndef __wavefront_h__
DECL|macro|__wavefront_h__
mdefine_line|#define __wavefront_h__
multiline_comment|/* WaveFront header file.&n; *   &n; * Copyright (C) by Paul Barton-Davis 1998&n; *&n; * This program is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.  &n; */
macro_line|#if (!defined(__GNUC__) &amp;&amp; !defined(__GNUG__))
DECL|variable|gcc
id|You
id|will
op_logical_neg
id|be
id|able
id|to
id|compile
id|this
id|file
id|correctly
id|without
id|gcc
comma
id|because
id|it
id|is
id|necessary
id|to
id|pack
id|the
l_string|&quot;wavefront_alias&quot;
id|structure
id|to
id|a
id|size
DECL|variable|bytes
id|of
l_int|22
id|bytes
comma
id|corresponding
id|to
l_int|16
op_minus
id|bit
id|alignment
(paren
id|as
id|would
id|have
id|been
DECL|variable|done
id|the
r_case
id|on
id|the
id|original
id|platform
comma
id|MS
op_minus
id|DOS
)paren
dot
id|If
id|this
id|is
op_logical_neg
id|done
comma
id|then
id|WavePatch
op_minus
id|format
id|files
id|cannot
id|be
id|read
op_div
id|written
id|correctly
dot
id|The
id|method
id|used
id|to
r_do
id|this
id|here
(paren
l_string|&quot;__attribute__((packed)&quot;
)paren
id|is
id|completely
id|compiler
id|dependent
dot
id|All
id|other
id|wavefront_
op_star
id|types
id|end
id|up
id|aligned
id|to
l_int|32
id|bit
id|values
op_logical_and
id|still
id|have
id|the
id|same
(paren
id|correct
)paren
id|size
dot
macro_line|#else
multiline_comment|/* However, note that as of G++ 2.7.3.2, g++ was unable to&n;&t;correctly parse *type* __attribute__ tags. It will do the&n;&t;right thing if we use the &quot;packed&quot; attribute on each struct&n;&t;member, which has the same semantics anyway. &n;     */
macro_line|#endif __GNUC__
multiline_comment|/***************************** WARNING ********************************&n;  PLEASE DO NOT MODIFY THIS FILE IN ANY WAY THAT AFFECTS ITS ABILITY TO &n;  BE USED WITH EITHER C *OR* C++.&n; **********************************************************************/
macro_line|#ifndef NUM_MIDIKEYS 
DECL|macro|NUM_MIDIKEYS
mdefine_line|#define NUM_MIDIKEYS 128
macro_line|#endif  NUM_MIDIKEYS
macro_line|#ifndef NUM_MIDICHANNELS
DECL|macro|NUM_MIDICHANNELS
mdefine_line|#define NUM_MIDICHANNELS 16
macro_line|#endif  NUM_MIDICHANNELS
multiline_comment|/* These are very useful/important. the original wavefront interface&n;   was developed on a 16 bit system, where sizeof(int) = 2&n;   bytes. Defining things like this makes the code much more portable, and&n;   easier to understand without having to toggle back and forth&n;   between a 16-bit view of the world and a 32-bit one. &n; */
DECL|typedef|INT16
r_typedef
r_int
id|INT16
suffix:semicolon
DECL|typedef|UINT16
r_typedef
r_int
r_int
id|UINT16
suffix:semicolon
DECL|typedef|INT32
r_typedef
r_int
id|INT32
suffix:semicolon
DECL|typedef|UINT32
r_typedef
r_int
r_int
id|UINT32
suffix:semicolon
DECL|typedef|CHAR8
r_typedef
r_char
id|CHAR8
suffix:semicolon
DECL|typedef|UCHAR8
r_typedef
r_int
r_char
id|UCHAR8
suffix:semicolon
multiline_comment|/* Pseudo-commands not part of the WaveFront command set.&n;   These are used for various driver controls and direct&n;   hardware control.&n; */
DECL|macro|WFC_DEBUG_DRIVER
mdefine_line|#define WFC_DEBUG_DRIVER                0
DECL|macro|WFC_FX_IOCTL
mdefine_line|#define WFC_FX_IOCTL                    1
DECL|macro|WFC_PATCH_STATUS
mdefine_line|#define WFC_PATCH_STATUS                2
DECL|macro|WFC_PROGRAM_STATUS
mdefine_line|#define WFC_PROGRAM_STATUS              3
DECL|macro|WFC_SAMPLE_STATUS
mdefine_line|#define WFC_SAMPLE_STATUS               4
DECL|macro|WFC_DISABLE_INTERRUPTS
mdefine_line|#define WFC_DISABLE_INTERRUPTS          5
DECL|macro|WFC_ENABLE_INTERRUPTS
mdefine_line|#define WFC_ENABLE_INTERRUPTS           6
DECL|macro|WFC_INTERRUPT_STATUS
mdefine_line|#define WFC_INTERRUPT_STATUS            7
DECL|macro|WFC_ROMSAMPLES_RDONLY
mdefine_line|#define WFC_ROMSAMPLES_RDONLY           8
DECL|macro|WFC_IDENTIFY_SLOT_TYPE
mdefine_line|#define WFC_IDENTIFY_SLOT_TYPE          9
multiline_comment|/* Wavefront synth commands&n; */
DECL|macro|WFC_DOWNLOAD_SAMPLE
mdefine_line|#define WFC_DOWNLOAD_SAMPLE&t;&t;0x80
DECL|macro|WFC_DOWNLOAD_BLOCK
mdefine_line|#define WFC_DOWNLOAD_BLOCK&t;&t;0x81
DECL|macro|WFC_DOWNLOAD_MULTISAMPLE
mdefine_line|#define WFC_DOWNLOAD_MULTISAMPLE&t;0x82
DECL|macro|WFC_DOWNLOAD_SAMPLE_ALIAS
mdefine_line|#define WFC_DOWNLOAD_SAMPLE_ALIAS&t;0x83
DECL|macro|WFC_DELETE_SAMPLE
mdefine_line|#define WFC_DELETE_SAMPLE&t;&t;0x84
DECL|macro|WFC_REPORT_FREE_MEMORY
mdefine_line|#define WFC_REPORT_FREE_MEMORY&t;&t;0x85
DECL|macro|WFC_DOWNLOAD_PATCH
mdefine_line|#define WFC_DOWNLOAD_PATCH&t;&t;0x86
DECL|macro|WFC_DOWNLOAD_PROGRAM
mdefine_line|#define WFC_DOWNLOAD_PROGRAM&t;&t;0x87
DECL|macro|WFC_SET_SYNTHVOL
mdefine_line|#define WFC_SET_SYNTHVOL&t;&t;0x89
DECL|macro|WFC_SET_NVOICES
mdefine_line|#define WFC_SET_NVOICES&t;&t;&t;0x8B
DECL|macro|WFC_DOWNLOAD_DRUM
mdefine_line|#define WFC_DOWNLOAD_DRUM&t;&t;0x90
DECL|macro|WFC_GET_SYNTHVOL
mdefine_line|#define WFC_GET_SYNTHVOL&t;&t;0x92
DECL|macro|WFC_GET_NVOICES
mdefine_line|#define WFC_GET_NVOICES&t;&t;&t;0x94
DECL|macro|WFC_DISABLE_CHANNEL
mdefine_line|#define WFC_DISABLE_CHANNEL&t;&t;0x9A
DECL|macro|WFC_ENABLE_CHANNEL
mdefine_line|#define WFC_ENABLE_CHANNEL&t;&t;0x9B
DECL|macro|WFC_MISYNTH_OFF
mdefine_line|#define WFC_MISYNTH_OFF&t;&t;&t;0x9D
DECL|macro|WFC_MISYNTH_ON
mdefine_line|#define WFC_MISYNTH_ON&t;&t;&t;0x9E
DECL|macro|WFC_FIRMWARE_VERSION
mdefine_line|#define WFC_FIRMWARE_VERSION&t;&t;0x9F
DECL|macro|WFC_GET_NSAMPLES
mdefine_line|#define WFC_GET_NSAMPLES&t;&t;0xA0
DECL|macro|WFC_DISABLE_DRUM_PROGRAM
mdefine_line|#define WFC_DISABLE_DRUM_PROGRAM&t;0xA2
DECL|macro|WFC_UPLOAD_PATCH
mdefine_line|#define WFC_UPLOAD_PATCH&t;&t;0xA3
DECL|macro|WFC_UPLOAD_PROGRAM
mdefine_line|#define WFC_UPLOAD_PROGRAM&t;&t;0xA4
DECL|macro|WFC_SET_TUNING
mdefine_line|#define WFC_SET_TUNING&t;&t;&t;0xA6
DECL|macro|WFC_GET_TUNING
mdefine_line|#define WFC_GET_TUNING&t;&t;&t;0xA7
DECL|macro|WFC_VMIDI_ON
mdefine_line|#define WFC_VMIDI_ON&t;&t;&t;0xA8
DECL|macro|WFC_VMIDI_OFF
mdefine_line|#define WFC_VMIDI_OFF&t;&t;&t;0xA9
DECL|macro|WFC_MIDI_STATUS
mdefine_line|#define WFC_MIDI_STATUS&t;&t;&t;0xAA
DECL|macro|WFC_GET_CHANNEL_STATUS
mdefine_line|#define WFC_GET_CHANNEL_STATUS&t;&t;0xAB
DECL|macro|WFC_DOWNLOAD_SAMPLE_HEADER
mdefine_line|#define WFC_DOWNLOAD_SAMPLE_HEADER&t;0xAC
DECL|macro|WFC_UPLOAD_SAMPLE_HEADER
mdefine_line|#define WFC_UPLOAD_SAMPLE_HEADER&t;0xAD
DECL|macro|WFC_UPLOAD_MULTISAMPLE
mdefine_line|#define WFC_UPLOAD_MULTISAMPLE&t;&t;0xAE
DECL|macro|WFC_UPLOAD_SAMPLE_ALIAS
mdefine_line|#define WFC_UPLOAD_SAMPLE_ALIAS&t;&t;0xAF
DECL|macro|WFC_IDENTIFY_SAMPLE_TYPE
mdefine_line|#define WFC_IDENTIFY_SAMPLE_TYPE&t;0xB0
DECL|macro|WFC_DOWNLOAD_EDRUM_PROGRAM
mdefine_line|#define WFC_DOWNLOAD_EDRUM_PROGRAM&t;0xB1
DECL|macro|WFC_UPLOAD_EDRUM_PROGRAM
mdefine_line|#define WFC_UPLOAD_EDRUM_PROGRAM&t;0xB2
DECL|macro|WFC_SET_EDRUM_CHANNEL
mdefine_line|#define WFC_SET_EDRUM_CHANNEL&t;&t;0xB3
DECL|macro|WFC_INSTOUT_LEVELS
mdefine_line|#define WFC_INSTOUT_LEVELS&t;&t;0xB4
DECL|macro|WFC_PEAKOUT_LEVELS
mdefine_line|#define WFC_PEAKOUT_LEVELS&t;&t;0xB5
DECL|macro|WFC_REPORT_CHANNEL_PROGRAMS
mdefine_line|#define WFC_REPORT_CHANNEL_PROGRAMS&t;0xB6
DECL|macro|WFC_HARDWARE_VERSION
mdefine_line|#define WFC_HARDWARE_VERSION&t;&t;0xCF
DECL|macro|WFC_UPLOAD_SAMPLE_PARAMS
mdefine_line|#define WFC_UPLOAD_SAMPLE_PARAMS&t;0xD7
DECL|macro|WFC_DOWNLOAD_OS
mdefine_line|#define WFC_DOWNLOAD_OS&t;&t;&t;0xF1
DECL|macro|WFC_NOOP
mdefine_line|#define WFC_NOOP                        0xFF
DECL|macro|WF_MAX_SAMPLE
mdefine_line|#define WF_MAX_SAMPLE   512
DECL|macro|WF_MAX_PATCH
mdefine_line|#define WF_MAX_PATCH    256
DECL|macro|WF_MAX_PROGRAM
mdefine_line|#define WF_MAX_PROGRAM  128
DECL|macro|WF_SECTION_MAX
mdefine_line|#define WF_SECTION_MAX  44   /* longest OS section length */
multiline_comment|/* # of bytes we send to the board when sending it various kinds of&n;   substantive data, such as samples, patches and programs.&n;*/
DECL|macro|WF_PROGRAM_BYTES
mdefine_line|#define WF_PROGRAM_BYTES 32
DECL|macro|WF_PATCH_BYTES
mdefine_line|#define WF_PATCH_BYTES 132
DECL|macro|WF_SAMPLE_BYTES
mdefine_line|#define WF_SAMPLE_BYTES 27
DECL|macro|WF_SAMPLE_HDR_BYTES
mdefine_line|#define WF_SAMPLE_HDR_BYTES 25
DECL|macro|WF_ALIAS_BYTES
mdefine_line|#define WF_ALIAS_BYTES 25
DECL|macro|WF_DRUM_BYTES
mdefine_line|#define WF_DRUM_BYTES 9
DECL|macro|WF_MSAMPLE_BYTES
mdefine_line|#define WF_MSAMPLE_BYTES 259 /* (MIDI_KEYS * 2) + 3 */
DECL|macro|WF_ACK
mdefine_line|#define WF_ACK     0x80
DECL|macro|WF_DMA_ACK
mdefine_line|#define WF_DMA_ACK 0x81
multiline_comment|/* OR-values for MIDI status bits */
DECL|macro|WF_MIDI_VIRTUAL_ENABLED
mdefine_line|#define WF_MIDI_VIRTUAL_ENABLED 0x1
DECL|macro|WF_MIDI_VIRTUAL_IS_EXTERNAL
mdefine_line|#define WF_MIDI_VIRTUAL_IS_EXTERNAL 0x2
DECL|macro|WF_MIDI_IN_TO_SYNTH_DISABLED
mdefine_line|#define WF_MIDI_IN_TO_SYNTH_DISABLED 0x4
multiline_comment|/* slot indexes for struct address_info: makes code a little more mnemonic */
DECL|macro|WF_SYNTH_SLOT
mdefine_line|#define WF_SYNTH_SLOT         0
DECL|macro|WF_INTERNAL_MIDI_SLOT
mdefine_line|#define WF_INTERNAL_MIDI_SLOT 1
DECL|macro|WF_EXTERNAL_MIDI_SLOT
mdefine_line|#define WF_EXTERNAL_MIDI_SLOT 2
multiline_comment|/* Magic MIDI bytes used to switch I/O streams on the ICS2115 MPU401&n;   emulation. Note these NEVER show up in output from the device and&n;   should NEVER be used in input unless Virtual MIDI mode has been &n;   disabled. If they do show up as input, the results are unpredictable.&n;*/
DECL|macro|WF_EXTERNAL_SWITCH
mdefine_line|#define WF_EXTERNAL_SWITCH  0xFD
DECL|macro|WF_INTERNAL_SWITCH
mdefine_line|#define WF_INTERNAL_SWITCH  0xF9
multiline_comment|/* Debugging flags */
DECL|macro|WF_DEBUG_CMD
mdefine_line|#define WF_DEBUG_CMD 0x1
DECL|macro|WF_DEBUG_DATA
mdefine_line|#define WF_DEBUG_DATA 0x2
DECL|macro|WF_DEBUG_LOAD_PATCH
mdefine_line|#define WF_DEBUG_LOAD_PATCH 0x4
DECL|macro|WF_DEBUG_IO
mdefine_line|#define WF_DEBUG_IO 0x8
multiline_comment|/* WavePatch file format stuff */
DECL|macro|WF_WAVEPATCH_VERSION
mdefine_line|#define WF_WAVEPATCH_VERSION     120;  /*  Current version number (1.2)  */
DECL|macro|WF_MAX_COMMENT
mdefine_line|#define WF_MAX_COMMENT           64    /*  Comment length */
DECL|macro|WF_NUM_LAYERS
mdefine_line|#define WF_NUM_LAYERS            4
DECL|macro|WF_NAME_LENGTH
mdefine_line|#define WF_NAME_LENGTH           32
DECL|macro|WF_SOURCE_LENGTH
mdefine_line|#define WF_SOURCE_LENGTH         260
DECL|macro|BankFileID
mdefine_line|#define BankFileID     &quot;Bank&quot;
DECL|macro|DrumkitFileID
mdefine_line|#define DrumkitFileID  &quot;DrumKit&quot;
DECL|macro|ProgramFileID
mdefine_line|#define ProgramFileID  &quot;Program&quot;
DECL|struct|wf_envelope
r_struct
id|wf_envelope
(brace
DECL|member|attack_time
id|UCHAR8
id|attack_time
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused1
id|UCHAR8
id|Unused1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|decay1_time
id|UCHAR8
id|decay1_time
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused2
id|UCHAR8
id|Unused2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|decay2_time
id|UCHAR8
id|decay2_time
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused3
id|UCHAR8
id|Unused3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sustain_time
id|UCHAR8
id|sustain_time
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused4
id|UCHAR8
id|Unused4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|release_time
id|UCHAR8
id|release_time
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused5
id|UCHAR8
id|Unused5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|release2_time
id|UCHAR8
id|release2_time
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused6
id|UCHAR8
id|Unused6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|attack_level
id|CHAR8
id|attack_level
suffix:semicolon
DECL|member|decay1_level
id|CHAR8
id|decay1_level
suffix:semicolon
DECL|member|decay2_level
id|CHAR8
id|decay2_level
suffix:semicolon
DECL|member|sustain_level
id|CHAR8
id|sustain_level
suffix:semicolon
DECL|member|release_level
id|CHAR8
id|release_level
suffix:semicolon
DECL|member|attack_velocity
id|UCHAR8
id|attack_velocity
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused7
id|UCHAR8
id|Unused7
suffix:colon
l_int|1
suffix:semicolon
DECL|member|volume_velocity
id|UCHAR8
id|volume_velocity
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused8
id|UCHAR8
id|Unused8
suffix:colon
l_int|1
suffix:semicolon
DECL|member|keyboard_scaling
id|UCHAR8
id|keyboard_scaling
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused9
id|UCHAR8
id|Unused9
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|wavefront_envelope
r_typedef
r_struct
id|wf_envelope
id|wavefront_envelope
suffix:semicolon
DECL|struct|wf_lfo
r_struct
id|wf_lfo
(brace
DECL|member|sample_number
id|UCHAR8
id|sample_number
suffix:semicolon
DECL|member|frequency
id|UCHAR8
id|frequency
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused1
id|UCHAR8
id|Unused1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|am_src
id|UCHAR8
id|am_src
suffix:colon
l_int|4
suffix:semicolon
DECL|member|fm_src
id|UCHAR8
id|fm_src
suffix:colon
l_int|4
suffix:semicolon
DECL|member|fm_amount
id|CHAR8
id|fm_amount
suffix:semicolon
DECL|member|am_amount
id|CHAR8
id|am_amount
suffix:semicolon
DECL|member|start_level
id|CHAR8
id|start_level
suffix:semicolon
DECL|member|end_level
id|CHAR8
id|end_level
suffix:semicolon
DECL|member|ramp_delay
id|UCHAR8
id|ramp_delay
suffix:colon
l_int|7
suffix:semicolon
DECL|member|wave_restart
id|UCHAR8
id|wave_restart
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* for LFO2 only */
DECL|member|ramp_time
id|UCHAR8
id|ramp_time
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused2
id|UCHAR8
id|Unused2
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|wavefront_lfo
r_typedef
r_struct
id|wf_lfo
id|wavefront_lfo
suffix:semicolon
DECL|struct|wf_patch
r_struct
id|wf_patch
(brace
DECL|member|frequency_bias
id|INT16
id|frequency_bias
suffix:semicolon
multiline_comment|/*  ** THIS IS IN MOTOROLA FORMAT!! ** */
DECL|member|amplitude_bias
id|UCHAR8
id|amplitude_bias
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused1
id|UCHAR8
id|Unused1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|portamento
id|UCHAR8
id|portamento
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused2
id|UCHAR8
id|Unused2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sample_number
id|UCHAR8
id|sample_number
suffix:semicolon
DECL|member|pitch_bend
id|UCHAR8
id|pitch_bend
suffix:colon
l_int|4
suffix:semicolon
DECL|member|sample_msb
id|UCHAR8
id|sample_msb
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Unused3
id|UCHAR8
id|Unused3
suffix:colon
l_int|3
suffix:semicolon
DECL|member|mono
id|UCHAR8
id|mono
suffix:colon
l_int|1
suffix:semicolon
DECL|member|retrigger
id|UCHAR8
id|retrigger
suffix:colon
l_int|1
suffix:semicolon
DECL|member|nohold
id|UCHAR8
id|nohold
suffix:colon
l_int|1
suffix:semicolon
DECL|member|restart
id|UCHAR8
id|restart
suffix:colon
l_int|1
suffix:semicolon
DECL|member|filterconfig
id|UCHAR8
id|filterconfig
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* SDK says &quot;not used&quot; */
DECL|member|reuse
id|UCHAR8
id|reuse
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reset_lfo
id|UCHAR8
id|reset_lfo
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fm_src2
id|UCHAR8
id|fm_src2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|fm_src1
id|UCHAR8
id|fm_src1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|fm_amount1
id|CHAR8
id|fm_amount1
suffix:semicolon
DECL|member|fm_amount2
id|CHAR8
id|fm_amount2
suffix:semicolon
DECL|member|am_src
id|UCHAR8
id|am_src
suffix:colon
l_int|4
suffix:semicolon
DECL|member|Unused4
id|UCHAR8
id|Unused4
suffix:colon
l_int|4
suffix:semicolon
DECL|member|am_amount
id|CHAR8
id|am_amount
suffix:semicolon
DECL|member|fc1_mode
id|UCHAR8
id|fc1_mode
suffix:colon
l_int|4
suffix:semicolon
DECL|member|fc2_mode
id|UCHAR8
id|fc2_mode
suffix:colon
l_int|4
suffix:semicolon
DECL|member|fc1_mod_amount
id|CHAR8
id|fc1_mod_amount
suffix:semicolon
DECL|member|fc1_keyboard_scaling
id|CHAR8
id|fc1_keyboard_scaling
suffix:semicolon
DECL|member|fc1_bias
id|CHAR8
id|fc1_bias
suffix:semicolon
DECL|member|fc2_mod_amount
id|CHAR8
id|fc2_mod_amount
suffix:semicolon
DECL|member|fc2_keyboard_scaling
id|CHAR8
id|fc2_keyboard_scaling
suffix:semicolon
DECL|member|fc2_bias
id|CHAR8
id|fc2_bias
suffix:semicolon
DECL|member|randomizer
id|UCHAR8
id|randomizer
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unused5
id|UCHAR8
id|Unused5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|envelope1
r_struct
id|wf_envelope
id|envelope1
suffix:semicolon
DECL|member|envelope2
r_struct
id|wf_envelope
id|envelope2
suffix:semicolon
DECL|member|lfo1
r_struct
id|wf_lfo
id|lfo1
suffix:semicolon
DECL|member|lfo2
r_struct
id|wf_lfo
id|lfo2
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|wavefront_patch
r_typedef
r_struct
id|wf_patch
id|wavefront_patch
suffix:semicolon
DECL|struct|wf_layer
r_struct
id|wf_layer
(brace
DECL|member|patch_number
id|UCHAR8
id|patch_number
suffix:semicolon
DECL|member|mix_level
id|UCHAR8
id|mix_level
suffix:colon
l_int|7
suffix:semicolon
DECL|member|mute
id|UCHAR8
id|mute
suffix:colon
l_int|1
suffix:semicolon
DECL|member|split_point
id|UCHAR8
id|split_point
suffix:colon
l_int|7
suffix:semicolon
DECL|member|play_below
id|UCHAR8
id|play_below
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pan_mod_src
id|UCHAR8
id|pan_mod_src
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pan_or_mod
id|UCHAR8
id|pan_or_mod
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pan
id|UCHAR8
id|pan
suffix:colon
l_int|4
suffix:semicolon
DECL|member|split_type
id|UCHAR8
id|split_type
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|wavefront_layer
r_typedef
r_struct
id|wf_layer
id|wavefront_layer
suffix:semicolon
DECL|struct|wf_program
r_struct
id|wf_program
(brace
DECL|member|layer
r_struct
id|wf_layer
id|layer
(braket
id|WF_NUM_LAYERS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|wavefront_program
r_typedef
r_struct
id|wf_program
id|wavefront_program
suffix:semicolon
DECL|struct|wf_sample_offset
r_struct
id|wf_sample_offset
(brace
DECL|member|Fraction
id|INT32
id|Fraction
suffix:colon
l_int|4
suffix:semicolon
DECL|member|Integer
id|INT32
id|Integer
suffix:colon
l_int|20
suffix:semicolon
DECL|member|Unused
id|INT32
id|Unused
suffix:colon
l_int|8
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|wavefront_sample_offset
r_typedef
r_struct
id|wf_sample_offset
id|wavefront_sample_offset
suffix:semicolon
multiline_comment|/* Sample slot types */
DECL|macro|WF_ST_SAMPLE
mdefine_line|#define WF_ST_SAMPLE      0
DECL|macro|WF_ST_MULTISAMPLE
mdefine_line|#define WF_ST_MULTISAMPLE 1
DECL|macro|WF_ST_ALIAS
mdefine_line|#define WF_ST_ALIAS       2
DECL|macro|WF_ST_EMPTY
mdefine_line|#define WF_ST_EMPTY       3
multiline_comment|/* pseudo&squot;s */
DECL|macro|WF_ST_DRUM
mdefine_line|#define WF_ST_DRUM        4
DECL|macro|WF_ST_PROGRAM
mdefine_line|#define WF_ST_PROGRAM     5
DECL|macro|WF_ST_PATCH
mdefine_line|#define WF_ST_PATCH       6
DECL|macro|WF_ST_SAMPLEHDR
mdefine_line|#define WF_ST_SAMPLEHDR   7
DECL|macro|WF_ST_MASK
mdefine_line|#define WF_ST_MASK        0xf
multiline_comment|/* Flags for slot status. These occupy the upper bits of the same byte&n;   as a sample type.&n;*/
DECL|macro|WF_SLOT_USED
mdefine_line|#define WF_SLOT_USED      0x80   /* XXX don&squot;t rely on this being accurate */
DECL|macro|WF_SLOT_FILLED
mdefine_line|#define WF_SLOT_FILLED    0x40
DECL|macro|WF_SLOT_ROM
mdefine_line|#define WF_SLOT_ROM       0x20
DECL|macro|WF_SLOT_MASK
mdefine_line|#define WF_SLOT_MASK      0xf0
multiline_comment|/* channel constants */
DECL|macro|WF_CH_MONO
mdefine_line|#define WF_CH_MONO  0
DECL|macro|WF_CH_LEFT
mdefine_line|#define WF_CH_LEFT  1
DECL|macro|WF_CH_RIGHT
mdefine_line|#define WF_CH_RIGHT 2
multiline_comment|/* Sample formats */
DECL|macro|LINEAR_16BIT
mdefine_line|#define LINEAR_16BIT 0
DECL|macro|WHITE_NOISE
mdefine_line|#define WHITE_NOISE  1
DECL|macro|LINEAR_8BIT
mdefine_line|#define LINEAR_8BIT  2
DECL|macro|MULAW_8BIT
mdefine_line|#define MULAW_8BIT   3
DECL|macro|WF_SAMPLE_IS_8BIT
mdefine_line|#define WF_SAMPLE_IS_8BIT(smpl) ((smpl)-&gt;SampleResolution&amp;2)
multiline_comment|/* &n;&n;  Because most/all of the sample data we pass in via pointers has&n;  never been copied (just mmap-ed into user space straight from the&n;  disk), it would be nice to allow handling of multi-channel sample&n;  data without forcing user-level extraction of the relevant bytes.&n;  &n;  So, we need a way of specifying which channel to use (the WaveFront&n;  only handles mono samples in a given slot), and the only way to do&n;  this without using some struct other than wavefront_sample as the&n;  interface is the awful hack of using the unused bits in a&n;  wavefront_sample:&n;  &n;  Val      Meaning&n;  ---      -------&n;  0        no channel selection (use channel 1, sample is MONO)&n;  1        use first channel, and skip one&n;  2        use second channel, and skip one&n;  3        use third channel, and skip two&n;  4        use fourth channel, skip three&n;  5        use fifth channel, skip four&n;  6        use six channel, skip five&n;&n;&n;  This can handle up to 4 channels, and anyone downloading &gt;4 channels&n;  of sample data just to select one of them needs to find some tools&n;  like sox ...&n;&n;  NOTE: values 0, 1 and 2 correspond to WF_CH_* above. This is &n;  important.&n;&n;*/
DECL|macro|WF_SET_CHANNEL
mdefine_line|#define WF_SET_CHANNEL(samp,chn) &bslash;&n; (samp)-&gt;Unused1 = chn &amp; 0x1; &bslash;&n; (samp)-&gt;Unused2 = chn &amp; 0x2; &bslash;&n; (samp)-&gt;Unused3 = chn &amp; 0x4 
DECL|macro|WF_GET_CHANNEL
mdefine_line|#define WF_GET_CHANNEL(samp) &bslash;&n;  (((samp)-&gt;Unused3 &lt;&lt; 2)|((samp)-&gt;Unused2&lt;&lt;1)|(samp)-&gt;Unused1)
DECL|struct|wf_sample
r_typedef
r_struct
id|wf_sample
(brace
DECL|member|sampleStartOffset
r_struct
id|wf_sample_offset
id|sampleStartOffset
suffix:semicolon
DECL|member|loopStartOffset
r_struct
id|wf_sample_offset
id|loopStartOffset
suffix:semicolon
DECL|member|loopEndOffset
r_struct
id|wf_sample_offset
id|loopEndOffset
suffix:semicolon
DECL|member|sampleEndOffset
r_struct
id|wf_sample_offset
id|sampleEndOffset
suffix:semicolon
DECL|member|FrequencyBias
id|INT16
id|FrequencyBias
suffix:semicolon
DECL|member|SampleResolution
id|UCHAR8
id|SampleResolution
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* sample_format */
DECL|member|Unused1
id|UCHAR8
id|Unused1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Loop
id|UCHAR8
id|Loop
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Bidirectional
id|UCHAR8
id|Bidirectional
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Unused2
id|UCHAR8
id|Unused2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Reverse
id|UCHAR8
id|Reverse
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Unused3
id|UCHAR8
id|Unused3
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|wavefront_sample
)brace
id|wavefront_sample
suffix:semicolon
DECL|struct|wf_multisample
r_typedef
r_struct
id|wf_multisample
(brace
DECL|member|NumberOfSamples
id|INT16
id|NumberOfSamples
suffix:semicolon
multiline_comment|/* log2 of the number of samples */
DECL|member|SampleNumber
id|INT16
id|SampleNumber
(braket
id|NUM_MIDIKEYS
)braket
suffix:semicolon
DECL|typedef|wavefront_multisample
)brace
id|wavefront_multisample
suffix:semicolon
DECL|struct|wf_alias
r_typedef
r_struct
id|wf_alias
(brace
DECL|member|OriginalSample
id|INT16
id|OriginalSample
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|sampleStartOffset
r_struct
id|wf_sample_offset
id|sampleStartOffset
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|loopStartOffset
r_struct
id|wf_sample_offset
id|loopStartOffset
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|sampleEndOffset
r_struct
id|wf_sample_offset
id|sampleEndOffset
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|loopEndOffset
r_struct
id|wf_sample_offset
id|loopEndOffset
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|FrequencyBias
id|INT16
id|FrequencyBias
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|SampleResolution
id|UCHAR8
id|SampleResolution
suffix:colon
l_int|2
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Unused1
id|UCHAR8
id|Unused1
suffix:colon
l_int|1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Loop
id|UCHAR8
id|Loop
suffix:colon
l_int|1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Bidirectional
id|UCHAR8
id|Bidirectional
suffix:colon
l_int|1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Unused2
id|UCHAR8
id|Unused2
suffix:colon
l_int|1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reverse
id|UCHAR8
id|Reverse
suffix:colon
l_int|1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Unused3
id|UCHAR8
id|Unused3
suffix:colon
l_int|1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* This structure is meant to be padded only to 16 bits on their&n;       original. Of course, whoever wrote their documentation didn&squot;t&n;       realize that sizeof(struct) can be &gt;=&n;       sum(sizeof(struct-fields)) and so thought that giving a C level&n;       description of the structs used in WavePatch files was&n;       sufficient. I suppose it was, as long as you remember the &n;       standard 16-&gt;32 bit issues.&n;    */
DECL|member|sixteen_bit_padding
id|UCHAR8
id|sixteen_bit_padding
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|wavefront_alias
)brace
id|wavefront_alias
suffix:semicolon
DECL|struct|wf_drum
r_typedef
r_struct
id|wf_drum
(brace
DECL|member|PatchNumber
id|UCHAR8
id|PatchNumber
suffix:semicolon
DECL|member|MixLevel
id|UCHAR8
id|MixLevel
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Unmute
id|UCHAR8
id|Unmute
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Group
id|UCHAR8
id|Group
suffix:colon
l_int|4
suffix:semicolon
DECL|member|Unused1
id|UCHAR8
id|Unused1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|PanModSource
id|UCHAR8
id|PanModSource
suffix:colon
l_int|2
suffix:semicolon
DECL|member|PanModulated
id|UCHAR8
id|PanModulated
suffix:colon
l_int|1
suffix:semicolon
DECL|member|PanAmount
id|UCHAR8
id|PanAmount
suffix:colon
l_int|4
suffix:semicolon
DECL|member|Unused2
id|UCHAR8
id|Unused2
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|wavefront_drum
)brace
id|wavefront_drum
suffix:semicolon
DECL|struct|wf_drumkit
r_typedef
r_struct
id|wf_drumkit
(brace
DECL|member|drum
r_struct
id|wf_drum
id|drum
(braket
id|NUM_MIDIKEYS
)braket
suffix:semicolon
DECL|typedef|wavefront_drumkit
)brace
id|wavefront_drumkit
suffix:semicolon
DECL|struct|wf_channel_programs
r_typedef
r_struct
id|wf_channel_programs
(brace
DECL|member|Program
id|UCHAR8
id|Program
(braket
id|NUM_MIDICHANNELS
)braket
suffix:semicolon
DECL|typedef|wavefront_channel_programs
)brace
id|wavefront_channel_programs
suffix:semicolon
multiline_comment|/* How to get MIDI channel status from the data returned by&n;   a WFC_GET_CHANNEL_STATUS command (a struct wf_channel_programs)&n;*/
DECL|macro|WF_CHANNEL_STATUS
mdefine_line|#define WF_CHANNEL_STATUS(ch,wcp) (wcp)[(ch/7)] &amp; (1&lt;&lt;((ch)%7))
DECL|union|wf_any
r_typedef
r_union
id|wf_any
(brace
DECL|member|s
id|wavefront_sample
id|s
suffix:semicolon
DECL|member|ms
id|wavefront_multisample
id|ms
suffix:semicolon
DECL|member|a
id|wavefront_alias
id|a
suffix:semicolon
DECL|member|pr
id|wavefront_program
id|pr
suffix:semicolon
DECL|member|p
id|wavefront_patch
id|p
suffix:semicolon
DECL|member|d
id|wavefront_drum
id|d
suffix:semicolon
DECL|typedef|wavefront_any
)brace
id|wavefront_any
suffix:semicolon
multiline_comment|/* Hannu Solvainen hoped that his &quot;patch_info&quot; struct in soundcard.h&n;   might work for other wave-table based patch loading situations.&n;   Alas, his fears were correct. The WaveFront doesn&squot;t even come with&n;   just &quot;patches&quot;, but several different kind of structures that&n;   control the sound generation process.&n; */
DECL|struct|wf_patch_info
r_typedef
r_struct
id|wf_patch_info
(brace
multiline_comment|/* the first two fields are used by the OSS &quot;patch loading&quot; interface&n;       only, and are unused by the current user-level library.&n;    */
DECL|member|key
id|INT16
id|key
suffix:semicolon
multiline_comment|/* Use WAVEFRONT_PATCH here */
DECL|member|devno
id|UINT16
id|devno
suffix:semicolon
multiline_comment|/* fill in when sending */
DECL|member|subkey
id|UCHAR8
id|subkey
suffix:semicolon
multiline_comment|/* WF_ST_{SAMPLE,ALIAS,etc.} */
DECL|macro|WAVEFRONT_FIND_FREE_SAMPLE_SLOT
mdefine_line|#define WAVEFRONT_FIND_FREE_SAMPLE_SLOT 999
DECL|member|number
id|UINT16
id|number
suffix:semicolon
multiline_comment|/* patch/sample/prog number */
DECL|member|size
id|UINT32
id|size
suffix:semicolon
multiline_comment|/* size of any data included in &n;&t;&t;&t;&t;  one of the fields in `hdrptr&squot;, or&n;&t;&t;&t;&t;  as `dataptr&squot;.&n;&n;&t;&t;&t;&t;  NOTE: for actual samples, this is&n;&t;&t;&t;&t;  the size of the *SELECTED CHANNEL*&n;&t;&t;&t;&t;  even if more data is actually available.&n;&t;&t;&t;&t;  &n;&t;&t;&t;&t;  So, a stereo sample (2 channels) of&n;&t;&t;&t;&t;  6000 bytes total has `size&squot; = 3000.&n;&n;&t;&t;&t;&t;  See the macros and comments for&n;&t;&t;&t;&t;  WF_{GET,SET}_CHANNEL above.&n;&n;&t;&t;&t;       */
DECL|member|hdrptr
id|wavefront_any
op_star
id|hdrptr
suffix:semicolon
multiline_comment|/* user-space ptr to hdr bytes */
DECL|member|dataptr
id|UINT16
op_star
id|dataptr
suffix:semicolon
multiline_comment|/* actual sample data */
DECL|member|hdr
id|wavefront_any
id|hdr
suffix:semicolon
multiline_comment|/* kernel-space copy of hdr bytes */
DECL|typedef|wavefront_patch_info
)brace
id|wavefront_patch_info
suffix:semicolon
multiline_comment|/* The maximum number of bytes we will ever move to or from user space&n;   in response to a WFC_* command.  This obviously doesn&squot;t cover&n;   actual sample data.&n;*/
DECL|macro|WF_MAX_READ
mdefine_line|#define WF_MAX_READ sizeof(wavefront_multisample)
DECL|macro|WF_MAX_WRITE
mdefine_line|#define WF_MAX_WRITE sizeof(wavefront_multisample)
multiline_comment|/*&n;   This allows us to execute any WF command except the download/upload&n;   ones, which are handled differently due to copyin/copyout issues as&n;   well as data-nybbling to/from the card.&n; */
DECL|struct|wavefront_control
r_typedef
r_struct
id|wavefront_control
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
multiline_comment|/* WFC_* */
DECL|member|status
r_char
id|status
suffix:semicolon
multiline_comment|/* return status to user-space */
DECL|member|rbuf
r_int
r_char
id|rbuf
(braket
id|WF_MAX_READ
)braket
suffix:semicolon
multiline_comment|/* bytes read from card */
DECL|member|wbuf
r_int
r_char
id|wbuf
(braket
id|WF_MAX_WRITE
)braket
suffix:semicolon
multiline_comment|/* bytes written to card */
DECL|typedef|wavefront_control
)brace
id|wavefront_control
suffix:semicolon
DECL|macro|WFCTL_WFCMD
mdefine_line|#define WFCTL_WFCMD    0x1
DECL|macro|WFCTL_LOAD_SPP
mdefine_line|#define WFCTL_LOAD_SPP 0x2
multiline_comment|/* Modulator table */
DECL|macro|WF_MOD_LFO1
mdefine_line|#define WF_MOD_LFO1      0
DECL|macro|WF_MOD_LFO2
mdefine_line|#define WF_MOD_LFO2      1
DECL|macro|WF_MOD_ENV1
mdefine_line|#define WF_MOD_ENV1      2
DECL|macro|WF_MOD_ENV2
mdefine_line|#define WF_MOD_ENV2      3
DECL|macro|WF_MOD_KEYBOARD
mdefine_line|#define WF_MOD_KEYBOARD  4
DECL|macro|WF_MOD_LOGKEY
mdefine_line|#define WF_MOD_LOGKEY    5
DECL|macro|WF_MOD_VELOCITY
mdefine_line|#define WF_MOD_VELOCITY  6
DECL|macro|WF_MOD_LOGVEL
mdefine_line|#define WF_MOD_LOGVEL    7
DECL|macro|WF_MOD_RANDOM
mdefine_line|#define WF_MOD_RANDOM    8
DECL|macro|WF_MOD_PRESSURE
mdefine_line|#define WF_MOD_PRESSURE  9
DECL|macro|WF_MOD_MOD_WHEEL
mdefine_line|#define WF_MOD_MOD_WHEEL 10
DECL|macro|WF_MOD_1
mdefine_line|#define WF_MOD_1         WF_MOD_MOD_WHEEL 
DECL|macro|WF_MOD_BREATH
mdefine_line|#define WF_MOD_BREATH    11
DECL|macro|WF_MOD_2
mdefine_line|#define WF_MOD_2         WF_MOD_BREATH
DECL|macro|WF_MOD_FOOT
mdefine_line|#define WF_MOD_FOOT      12
DECL|macro|WF_MOD_4
mdefine_line|#define WF_MOD_4         WF_MOD_FOOT
DECL|macro|WF_MOD_VOLUME
mdefine_line|#define WF_MOD_VOLUME    13
DECL|macro|WF_MOD_7
mdefine_line|#define WF_MOD_7         WF_MOD_VOLUME
DECL|macro|WF_MOD_PAN
mdefine_line|#define WF_MOD_PAN       14
DECL|macro|WF_MOD_10
mdefine_line|#define WF_MOD_10        WF_MOD_PAN
DECL|macro|WF_MOD_EXPR
mdefine_line|#define WF_MOD_EXPR      15
DECL|macro|WF_MOD_11
mdefine_line|#define WF_MOD_11        WF_MOD_EXPR
multiline_comment|/* FX-related material */
DECL|struct|wf_fx_info
r_typedef
r_struct
id|wf_fx_info
(brace
DECL|member|request
r_int
id|request
suffix:semicolon
multiline_comment|/* see list below */
DECL|member|data
r_int
id|data
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* we don&squot;t need much */
DECL|typedef|wavefront_fx_info
)brace
id|wavefront_fx_info
suffix:semicolon
multiline_comment|/* support for each of these will be forthcoming once I or someone &n;   else has figured out which of the addresses on page 6 and page 7 of &n;   the YSS225 control each parameter. Incidentally, these come from&n;   the Windows driver interface, but again, Turtle Beach didn&squot;t&n;   document the API to use them.&n;*/
DECL|macro|WFFX_SETOUTGAIN
mdefine_line|#define WFFX_SETOUTGAIN&t;&t;        0
DECL|macro|WFFX_SETSTEREOOUTGAIN
mdefine_line|#define WFFX_SETSTEREOOUTGAIN&t;&t;1
DECL|macro|WFFX_SETREVERBIN1GAIN
mdefine_line|#define WFFX_SETREVERBIN1GAIN&t;&t;2
DECL|macro|WFFX_SETREVERBIN2GAIN
mdefine_line|#define WFFX_SETREVERBIN2GAIN&t;&t;3
DECL|macro|WFFX_SETREVERBIN3GAIN
mdefine_line|#define WFFX_SETREVERBIN3GAIN&t;&t;4
DECL|macro|WFFX_SETCHORUSINPORT
mdefine_line|#define WFFX_SETCHORUSINPORT&t;&t;5
DECL|macro|WFFX_SETREVERBIN1PORT
mdefine_line|#define WFFX_SETREVERBIN1PORT&t;&t;6
DECL|macro|WFFX_SETREVERBIN2PORT
mdefine_line|#define WFFX_SETREVERBIN2PORT&t;&t;7
DECL|macro|WFFX_SETREVERBIN3PORT
mdefine_line|#define WFFX_SETREVERBIN3PORT&t;&t;8
DECL|macro|WFFX_SETEFFECTPORT
mdefine_line|#define WFFX_SETEFFECTPORT&t;&t;9
DECL|macro|WFFX_SETAUXPORT
mdefine_line|#define WFFX_SETAUXPORT&t;&t;        10
DECL|macro|WFFX_SETREVERBTYPE
mdefine_line|#define WFFX_SETREVERBTYPE&t;&t;11
DECL|macro|WFFX_SETREVERBDELAY
mdefine_line|#define WFFX_SETREVERBDELAY&t;&t;12
DECL|macro|WFFX_SETCHORUSLFO
mdefine_line|#define WFFX_SETCHORUSLFO&t;&t;13
DECL|macro|WFFX_SETCHORUSPMD
mdefine_line|#define WFFX_SETCHORUSPMD&t;&t;14
DECL|macro|WFFX_SETCHORUSAMD
mdefine_line|#define WFFX_SETCHORUSAMD&t;&t;15
DECL|macro|WFFX_SETEFFECT
mdefine_line|#define WFFX_SETEFFECT&t;&t;        16
DECL|macro|WFFX_SETBASEALL
mdefine_line|#define WFFX_SETBASEALL&t;&t;        17
DECL|macro|WFFX_SETREVERBALL
mdefine_line|#define WFFX_SETREVERBALL&t;&t;18
DECL|macro|WFFX_SETCHORUSALL
mdefine_line|#define WFFX_SETCHORUSALL&t;&t;20
DECL|macro|WFFX_SETREVERBDEF
mdefine_line|#define WFFX_SETREVERBDEF&t;&t;22
DECL|macro|WFFX_SETCHORUSDEF
mdefine_line|#define WFFX_SETCHORUSDEF&t;&t;23
DECL|macro|WFFX_DELAYSETINGAIN
mdefine_line|#define WFFX_DELAYSETINGAIN&t;&t;24
DECL|macro|WFFX_DELAYSETFBGAIN
mdefine_line|#define WFFX_DELAYSETFBGAIN&t;        25
DECL|macro|WFFX_DELAYSETFBLPF
mdefine_line|#define WFFX_DELAYSETFBLPF&t;&t;26
DECL|macro|WFFX_DELAYSETGAIN
mdefine_line|#define WFFX_DELAYSETGAIN&t;&t;27
DECL|macro|WFFX_DELAYSETTIME
mdefine_line|#define WFFX_DELAYSETTIME&t;&t;28
DECL|macro|WFFX_DELAYSETFBTIME
mdefine_line|#define WFFX_DELAYSETFBTIME&t;&t;29
DECL|macro|WFFX_DELAYSETALL
mdefine_line|#define WFFX_DELAYSETALL&t;&t;30
DECL|macro|WFFX_DELAYSETDEF
mdefine_line|#define WFFX_DELAYSETDEF&t;&t;32
DECL|macro|WFFX_SDELAYSETINGAIN
mdefine_line|#define WFFX_SDELAYSETINGAIN&t;&t;33
DECL|macro|WFFX_SDELAYSETFBGAIN
mdefine_line|#define WFFX_SDELAYSETFBGAIN&t;&t;34
DECL|macro|WFFX_SDELAYSETFBLPF
mdefine_line|#define WFFX_SDELAYSETFBLPF&t;&t;35
DECL|macro|WFFX_SDELAYSETGAIN
mdefine_line|#define WFFX_SDELAYSETGAIN&t;&t;36
DECL|macro|WFFX_SDELAYSETTIME
mdefine_line|#define WFFX_SDELAYSETTIME&t;&t;37
DECL|macro|WFFX_SDELAYSETFBTIME
mdefine_line|#define WFFX_SDELAYSETFBTIME&t;&t;38
DECL|macro|WFFX_SDELAYSETALL
mdefine_line|#define WFFX_SDELAYSETALL&t;&t;39
DECL|macro|WFFX_SDELAYSETDEF
mdefine_line|#define WFFX_SDELAYSETDEF&t;&t;41
DECL|macro|WFFX_DEQSETINGAIN
mdefine_line|#define WFFX_DEQSETINGAIN&t;&t;42
DECL|macro|WFFX_DEQSETFILTER
mdefine_line|#define WFFX_DEQSETFILTER&t;&t;43
DECL|macro|WFFX_DEQSETALL
mdefine_line|#define WFFX_DEQSETALL&t;&t;        44
DECL|macro|WFFX_DEQSETDEF
mdefine_line|#define WFFX_DEQSETDEF&t;&t;        46
DECL|macro|WFFX_MUTE
mdefine_line|#define WFFX_MUTE&t;&t;        47
DECL|macro|WFFX_FLANGESETBALANCE
mdefine_line|#define WFFX_FLANGESETBALANCE&t;        48&t;
DECL|macro|WFFX_FLANGESETDELAY
mdefine_line|#define WFFX_FLANGESETDELAY&t;&t;49
DECL|macro|WFFX_FLANGESETDWFFX_TH
mdefine_line|#define WFFX_FLANGESETDWFFX_TH&t;&t;50
DECL|macro|WFFX_FLANGESETFBGAIN
mdefine_line|#define WFFX_FLANGESETFBGAIN&t;&t;51
DECL|macro|WFFX_FLANGESETINGAIN
mdefine_line|#define WFFX_FLANGESETINGAIN&t;&t;52
DECL|macro|WFFX_FLANGESETLFO
mdefine_line|#define WFFX_FLANGESETLFO&t;&t;53
DECL|macro|WFFX_FLANGESETALL
mdefine_line|#define WFFX_FLANGESETALL&t;&t;54
DECL|macro|WFFX_FLANGESETDEF
mdefine_line|#define WFFX_FLANGESETDEF&t;&t;56
DECL|macro|WFFX_PITCHSETSHIFT
mdefine_line|#define WFFX_PITCHSETSHIFT&t;&t;57
DECL|macro|WFFX_PITCHSETBALANCE
mdefine_line|#define WFFX_PITCHSETBALANCE&t;&t;58
DECL|macro|WFFX_PITCHSETALL
mdefine_line|#define WFFX_PITCHSETALL&t;&t;59
DECL|macro|WFFX_PITCHSETDEF
mdefine_line|#define WFFX_PITCHSETDEF&t;&t;61
DECL|macro|WFFX_SRSSETINGAIN
mdefine_line|#define WFFX_SRSSETINGAIN&t;&t;62
DECL|macro|WFFX_SRSSETSPACE
mdefine_line|#define WFFX_SRSSETSPACE&t;&t;63
DECL|macro|WFFX_SRSSETCENTER
mdefine_line|#define WFFX_SRSSETCENTER&t;&t;64
DECL|macro|WFFX_SRSSETGAIN
mdefine_line|#define WFFX_SRSSETGAIN&t;&t;        65
DECL|macro|WFFX_SRSSETMODE
mdefine_line|#define WFFX_SRSSETMODE&t;        &t;66
DECL|macro|WFFX_SRSSETDEF
mdefine_line|#define WFFX_SRSSETDEF&t;&t;        68
multiline_comment|/* Allow direct user-space control over FX memory/coefficient data.&n;   In theory this could be used to download the FX microprogram,&n;   but it would be a little slower, and involve some wierd code.&n; */
DECL|macro|WFFX_MEMSET
mdefine_line|#define WFFX_MEMSET              69
macro_line|#endif __wavefront_h__
eof
