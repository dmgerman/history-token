multiline_comment|/*&n; * Definitions for various on board processors on the sound cards. For&n; * example DSP processors.&n; */
multiline_comment|/*&n; * Coprocessor access types &n; */
DECL|macro|COPR_CUSTOM
mdefine_line|#define COPR_CUSTOM&t;&t;0x0001&t;/* Custom applications */
DECL|macro|COPR_MIDI
mdefine_line|#define COPR_MIDI&t;&t;0x0002&t;/* MIDI (MPU-401) emulation */
DECL|macro|COPR_PCM
mdefine_line|#define COPR_PCM&t;&t;0x0004&t;/* Digitized voice applications */
DECL|macro|COPR_SYNTH
mdefine_line|#define COPR_SYNTH&t;&t;0x0008&t;/* Music synthesis */
eof
