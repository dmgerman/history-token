multiline_comment|/*************************************************************************&n; *&n; * tape390.h&n; *         enables user programs to display messages on the tape device&n; *&n; *  S390 and zSeries version&n; *         Copyright (C) 2001 IBM Corporation&n; *         Author(s): Despina Papadopoulou &lt;despina_p@de.ibm.com&gt;&n; *&n; *************************************************************************/
macro_line|#ifndef _TAPE390_H
DECL|macro|_TAPE390_H
mdefine_line|#define _TAPE390_H
DECL|macro|TAPE390_DISPLAY
mdefine_line|#define TAPE390_DISPLAY _IOW(&squot;d&squot;, 1, struct display_struct)
multiline_comment|/*&n; * The TAPE390_DISPLAY ioctl calls the Load Display command&n; * which transfers 17 bytes of data from the channel to the subsystem:&n; *     - 1 format control byte, and&n; *     - two 8-byte messages&n; *&n; * Format control byte:&n; *   0-2: New Message Overlay&n; *     3: Alternate Messages&n; *     4: Blink Message&n; *     5: Display Low/High Message&n; *     6: Reserved&n; *     7: Automatic Load Request&n; *&n; */
DECL|struct|display_struct
r_typedef
r_struct
id|display_struct
(brace
DECL|member|cntrl
r_char
id|cntrl
suffix:semicolon
DECL|member|message1
r_char
id|message1
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|message2
r_char
id|message2
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|display_struct
)brace
id|display_struct
suffix:semicolon
macro_line|#endif 
eof
