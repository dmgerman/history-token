multiline_comment|/*&n;===============================================================================&n;&n;This C header file is part of the SoftFloat IEC/IEEE Floating-point&n;Arithmetic Package, Release 2.&n;&n;Written by John R. Hauser.  This work was made possible in part by the&n;International Computer Science Institute, located at Suite 600, 1947 Center&n;Street, Berkeley, California 94704.  Funding was partially provided by the&n;National Science Foundation under grant MIP-9311980.  The original version&n;of this code was written as part of a project to build a fixed-point vector&n;processor in collaboration with the University of California at Berkeley,&n;overseen by Profs. Nelson Morgan and John Wawrzynek.  More information&n;is available through the Web page `http://HTTP.CS.Berkeley.EDU/~jhauser/&n;arithmetic/softfloat.html&squot;.&n;&n;THIS SOFTWARE IS DISTRIBUTED AS IS, FOR FREE.  Although reasonable effort&n;has been made to avoid it, THIS SOFTWARE MAY CONTAIN FAULTS THAT WILL AT&n;TIMES RESULT IN INCORRECT BEHAVIOR.  USE OF THIS SOFTWARE IS RESTRICTED TO&n;PERSONS AND ORGANIZATIONS WHO CAN AND WILL TAKE FULL RESPONSIBILITY FOR ANY&n;AND ALL LOSSES, COSTS, OR OTHER PROBLEMS ARISING FROM ITS USE.&n;&n;Derivative works are acceptable, even for commercial purposes, so long as&n;(1) they include prominent notice that the work is derivative, and (2) they&n;include prominent notice akin to these three paragraphs for those parts of&n;this code that are retained.&n;&n;===============================================================================&n;*/
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Include common integer types and flags.&n;-------------------------------------------------------------------------------&n;*/
macro_line|#include &quot;ARM-gcc.h&quot;
multiline_comment|/*&n;-------------------------------------------------------------------------------&n;Symbolic Boolean literals.&n;-------------------------------------------------------------------------------&n;*/
r_enum
(brace
DECL|enumerator|FALSE
id|FALSE
op_assign
l_int|0
comma
DECL|enumerator|TRUE
id|TRUE
op_assign
l_int|1
)brace
suffix:semicolon
eof
