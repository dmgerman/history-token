multiline_comment|/***************************************************************************&n; *&n; *  drivers/s390/char/tape3490.h&n; *    tape device discipline for 3490E tapes.&n; *&n; *  S390 and zSeries version&n; *    Copyright (C) 2001 IBM Corporation&n; *    Author(s): Carsten Otte &lt;cotte@de.ibm.com&gt;&n; *               Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&n; ****************************************************************************&n; */
macro_line|#ifndef _TAPE3490_H
DECL|macro|_TAPE3490_H
mdefine_line|#define _TAPE3490_H
DECL|struct|_tape3490_disc_data_t
r_typedef
r_struct
id|_tape3490_disc_data_t
(brace
DECL|member|modeset_byte
id|__u8
id|modeset_byte
suffix:semicolon
DECL|typedef|tape3490_disc_data_t
)brace
id|tape3490_disc_data_t
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
id|tape_discipline_t
op_star
id|tape3490_init
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// _TAPE3490_H
eof
