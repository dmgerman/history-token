multiline_comment|/* SCTP reference Implementation &n; * Copyright (C) 1999 Cisco, Inc. &n; * Copyright (C) 1999 Motorola, Inc.&n; *&n; * This file originates from Randy Stewart&squot;s SCTP reference Implementation.&n; * &n; * The SCTP reference implementation is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; * &n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by: &n; *    Randy Stewart &lt;rstewar1@email.mot.com&gt;&n; *    Ken Morneau   &lt;kmorneau@cisco.com&gt; &n; *    Qiaobing Xie  &lt;qxie1@email.mot.com&gt;&n; */
macro_line|#ifndef __SLA1_h__
DECL|macro|__SLA1_h__
mdefine_line|#define __SLA1_h__
macro_line|#ifdef&t;__cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
DECL|struct|SLA_1_Context
r_struct
id|SLA_1_Context
(brace
DECL|member|A
r_int
r_int
id|A
suffix:semicolon
DECL|member|B
r_int
r_int
id|B
suffix:semicolon
DECL|member|C
r_int
r_int
id|C
suffix:semicolon
DECL|member|D
r_int
r_int
id|D
suffix:semicolon
DECL|member|E
r_int
r_int
id|E
suffix:semicolon
DECL|member|H0
r_int
r_int
id|H0
suffix:semicolon
DECL|member|H1
r_int
r_int
id|H1
suffix:semicolon
DECL|member|H2
r_int
r_int
id|H2
suffix:semicolon
DECL|member|H3
r_int
r_int
id|H3
suffix:semicolon
DECL|member|H4
r_int
r_int
id|H4
suffix:semicolon
DECL|member|words
r_int
r_int
id|words
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|TEMP
r_int
r_int
id|TEMP
suffix:semicolon
multiline_comment|/* block I am collecting to process */
DECL|member|SLAblock
r_char
id|SLAblock
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* collected so far */
DECL|member|howManyInBlock
r_int
id|howManyInBlock
suffix:semicolon
DECL|member|runningTotal
r_int
r_int
id|runningTotal
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|F1
mdefine_line|#define F1(B,C,D) (((B &amp; C) | ((~B) &amp; D)))       /* 0  &lt;= t &lt;= 19 */
DECL|macro|F2
mdefine_line|#define F2(B,C,D) (B ^ C ^ D)                   /* 20 &lt;= t &lt;= 39 */
DECL|macro|F3
mdefine_line|#define F3(B,C,D) ((B &amp; C) | (B &amp; D) | (C &amp; D)) /* 40 &lt;= t &lt;= 59 */
DECL|macro|F4
mdefine_line|#define F4(B,C,D) (B ^ C ^ D)                   /*600 &lt;= t &lt;= 79 */
multiline_comment|/* circular shift */
DECL|macro|CSHIFT
mdefine_line|#define CSHIFT(A,B) ((B &lt;&lt; A) | (B &gt;&gt; (32-A)))
DECL|macro|K1
mdefine_line|#define K1 0x5a827999       /* 0  &lt;= t &lt;= 19 */
DECL|macro|K2
mdefine_line|#define K2 0x6ed9eba1       /* 20 &lt;= t &lt;= 39 */
DECL|macro|K3
mdefine_line|#define K3 0x8f1bbcdc       /* 40 &lt;= t &lt;= 59 */
DECL|macro|K4
mdefine_line|#define K4 0xca62c1d6       /* 60 &lt;= t &lt;= 79 */
DECL|macro|H0INIT
mdefine_line|#define H0INIT 0x67452301
DECL|macro|H1INIT
mdefine_line|#define H1INIT 0xefcdab89
DECL|macro|H2INIT
mdefine_line|#define H2INIT 0x98badcfe
DECL|macro|H3INIT
mdefine_line|#define H3INIT 0x10325476
DECL|macro|H4INIT
mdefine_line|#define H4INIT 0xc3d2e1f0
r_extern
r_void
id|SLA1_Init
c_func
(paren
r_struct
id|SLA_1_Context
op_star
)paren
suffix:semicolon
r_extern
r_void
id|SLA1_Process
c_func
(paren
r_struct
id|SLA_1_Context
op_star
comma
r_const
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|SLA1_Final
c_func
(paren
r_struct
id|SLA_1_Context
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
macro_line|#ifdef&t;__cplusplus
)brace
macro_line|#endif
macro_line|#endif
eof
