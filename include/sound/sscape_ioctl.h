macro_line|#ifndef SSCAPE_IOCTL_H
DECL|macro|SSCAPE_IOCTL_H
mdefine_line|#define SSCAPE_IOCTL_H
DECL|struct|sscape_bootblock
r_struct
id|sscape_bootblock
(brace
DECL|member|code
r_int
r_char
id|code
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|version
r_int
id|version
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sscape_microcode
r_struct
id|sscape_microcode
(brace
DECL|member|code
r_int
r_char
id|code
(braket
l_int|65536
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SND_SSCAPE_LOAD_BOOTB
mdefine_line|#define SND_SSCAPE_LOAD_BOOTB  _IOWR(&squot;P&squot;, 100, struct sscape_bootblock)
DECL|macro|SND_SSCAPE_LOAD_MCODE
mdefine_line|#define SND_SSCAPE_LOAD_MCODE  _IOW(&squot;P&squot;, 101, struct sscape_microcode)
macro_line|#endif
eof
