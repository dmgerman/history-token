multiline_comment|/*&n; *&t;FILE    &t;bitfield.h&n; *&n; *&t;Version &t;1.1&n; *&t;Author  &t;Copyright (c) Marc A. Viredaz, 1998&n; *&t;        &t;DEC Western Research Laboratory, Palo Alto, CA&n; *&t;Date    &t;April 1998 (April 1997)&n; *&t;System  &t;Advanced RISC Machine (ARM)&n; *&t;Language&t;C or ARM Assembly&n; *&t;Purpose &t;Definition of macros to operate on bit fields.&n; */
macro_line|#ifndef BITFIELD
DECL|macro|BITFIELD
mdefine_line|#define BITFIELD
macro_line|#ifndef LANGUAGE
DECL|macro|LANGUAGE
mdefine_line|#define LANGUAGE&t;C
macro_line|#endif /* !defined (LANGUAGE) */
DECL|macro|C
mdefine_line|#define C       &t;0
DECL|macro|Assembly
mdefine_line|#define Assembly&t;1
macro_line|#if LANGUAGE == C
DECL|macro|UData
mdefine_line|#define UData(Data)&t;((unsigned int) (Data))
macro_line|#elif LANGUAGE == Assembly
DECL|macro|UData
mdefine_line|#define UData(Data)&t;(Data)
macro_line|#endif /* LANGUAGE == C || LANGUAGE == Assembly */
multiline_comment|/*&n; * MACRO: Fld&n; *&n; * Purpose&n; *    The macro &quot;Fld&quot; encodes a bit field, given its size and its shift value&n; *    with respect to bit 0.&n; *&n; * Note&n; *    A more intuitive way to encode bit fields would have been to use their&n; *    mask. However, extracting size and shift value information from a bit&n; *    field&squot;s mask is cumbersome and might break the assembler (255-character&n; *    line-size limit).&n; *&n; * Input&n; *    Size      &t;Size of the bit field, in number of bits.&n; *    Shft      &t;Shift value of the bit field with respect to bit 0.&n; *&n; * Output&n; *    Fld       &t;Encoded bit field.&n; */
DECL|macro|Fld
mdefine_line|#define Fld(Size, Shft)&t;(((Size) &lt;&lt; 16) + (Shft))
multiline_comment|/*&n; * MACROS: FSize, FShft, FMsk, FAlnMsk, F1stBit&n; *&n; * Purpose&n; *    The macros &quot;FSize&quot;, &quot;FShft&quot;, &quot;FMsk&quot;, &quot;FAlnMsk&quot;, and &quot;F1stBit&quot; return&n; *    the size, shift value, mask, aligned mask, and first bit of a&n; *    bit field.&n; *&n; * Input&n; *    Field     &t;Encoded bit field (using the macro &quot;Fld&quot;).&n; *&n; * Output&n; *    FSize     &t;Size of the bit field, in number of bits.&n; *    FShft     &t;Shift value of the bit field with respect to bit 0.&n; *    FMsk      &t;Mask for the bit field.&n; *    FAlnMsk   &t;Mask for the bit field, aligned on bit 0.&n; *    F1stBit   &t;First bit of the bit field.&n; */
DECL|macro|FSize
mdefine_line|#define FSize(Field)&t;((Field) &gt;&gt; 16)
DECL|macro|FShft
mdefine_line|#define FShft(Field)&t;((Field) &amp; 0x0000FFFF)
DECL|macro|FMsk
mdefine_line|#define FMsk(Field)&t;(((UData (1) &lt;&lt; FSize (Field)) - 1) &lt;&lt; FShft (Field))
DECL|macro|FAlnMsk
mdefine_line|#define FAlnMsk(Field)&t;((UData (1) &lt;&lt; FSize (Field)) - 1)
DECL|macro|F1stBit
mdefine_line|#define F1stBit(Field)&t;(UData (1) &lt;&lt; FShft (Field))
multiline_comment|/*&n; * MACRO: FInsrt&n; *&n; * Purpose&n; *    The macro &quot;FInsrt&quot; inserts a value into a bit field by shifting the&n; *    former appropriately.&n; *&n; * Input&n; *    Value     &t;Bit-field value.&n; *    Field     &t;Encoded bit field (using the macro &quot;Fld&quot;).&n; *&n; * Output&n; *    FInsrt    &t;Bit-field value positioned appropriately.&n; */
DECL|macro|FInsrt
mdefine_line|#define FInsrt(Value, Field) &bslash;&n;                &t;(UData (Value) &lt;&lt; FShft (Field))
multiline_comment|/*&n; * MACRO: FExtr&n; *&n; * Purpose&n; *    The macro &quot;FExtr&quot; extracts the value of a bit field by masking and&n; *    shifting it appropriately.&n; *&n; * Input&n; *    Data      &t;Data containing the bit-field to be extracted.&n; *    Field     &t;Encoded bit field (using the macro &quot;Fld&quot;).&n; *&n; * Output&n; *    FExtr     &t;Bit-field value.&n; */
DECL|macro|FExtr
mdefine_line|#define FExtr(Data, Field) &bslash;&n;                &t;((UData (Data) &gt;&gt; FShft (Field)) &amp; FAlnMsk (Field))
DECL|macro|C
macro_line|#undef C
DECL|macro|Assembly
macro_line|#undef Assembly
macro_line|#endif /* !defined (BITFIELD) */
eof
