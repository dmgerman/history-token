multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __FRAME_I386_H
DECL|macro|__FRAME_I386_H
mdefine_line|#define __FRAME_I386_H
DECL|struct|arch_frame_data_raw
r_struct
id|arch_frame_data_raw
(brace
DECL|member|fp_start
r_int
r_int
id|fp_start
suffix:semicolon
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arch_frame_data
r_struct
id|arch_frame_data
(brace
DECL|member|fpstate_size
r_int
id|fpstate_size
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
