multiline_comment|/* include/asm-m68knommu/MC68332.h: &squot;332 control registers&n; *&n; * Copyright (C) 1998  Kenneth Albanowski &lt;kjahds@kjahds.com&gt;,&n; *&n; */
macro_line|#ifndef _MC68332_H_
DECL|macro|_MC68332_H_
mdefine_line|#define _MC68332_H_
DECL|macro|BYTE_REF
mdefine_line|#define BYTE_REF(addr) (*((volatile unsigned char*)addr))
DECL|macro|WORD_REF
mdefine_line|#define WORD_REF(addr) (*((volatile unsigned short*)addr))
DECL|macro|PORTE_ADDR
mdefine_line|#define PORTE_ADDR&t;0xfffa11
DECL|macro|PORTE
mdefine_line|#define PORTE&t;BYTE_REF(PORTE_ADDR)
DECL|macro|DDRE_ADDR
mdefine_line|#define DDRE_ADDR&t;0xfffa15
DECL|macro|DDRE
mdefine_line|#define DDRE&t;BYTE_REF(DDRE_ADDR)
DECL|macro|PEPAR_ADDR
mdefine_line|#define PEPAR_ADDR&t;0xfffa17
DECL|macro|PEPAR
mdefine_line|#define PEPAR&t;BYTE_REF(PEPAR_ADDR)
DECL|macro|PORTF_ADDR
mdefine_line|#define PORTF_ADDR&t;0xfffa19
DECL|macro|PORTF
mdefine_line|#define PORTF&t;BYTE_REF(PORTF_ADDR)
DECL|macro|DDRF_ADDR
mdefine_line|#define DDRF_ADDR&t;0xfffa1d
DECL|macro|DDRF
mdefine_line|#define DDRF&t;BYTE_REF(DDRF_ADDR)
DECL|macro|PFPAR_ADDR
mdefine_line|#define PFPAR_ADDR&t;0xfffa1f
DECL|macro|PFPAR
mdefine_line|#define PFPAR&t;BYTE_REF(PFPAR_ADDR)
DECL|macro|PORTQS_ADDR
mdefine_line|#define PORTQS_ADDR&t;0xfffc15
DECL|macro|PORTQS
mdefine_line|#define PORTQS&t;BYTE_REF(PORTQS_ADDR)
DECL|macro|DDRQS_ADDR
mdefine_line|#define DDRQS_ADDR&t;0xfffc17
DECL|macro|DDRQS
mdefine_line|#define DDRQS&t;BYTE_REF(DDRQS_ADDR)
DECL|macro|PQSPAR_ADDR
mdefine_line|#define PQSPAR_ADDR&t;0xfffc16
DECL|macro|PQSPAR
mdefine_line|#define PQSPAR&t;BYTE_REF(PQSPAR_ADDR)
DECL|macro|CSPAR0_ADDR
mdefine_line|#define CSPAR0_ADDR 0xFFFA44
DECL|macro|CSPAR0
mdefine_line|#define CSPAR0 WORD_REF(CSPAR0_ADDR)
DECL|macro|CSPAR1_ADDR
mdefine_line|#define CSPAR1_ADDR 0xFFFA46
DECL|macro|CSPAR1
mdefine_line|#define CSPAR1 WORD_REF(CSPAR1_ADDR)
DECL|macro|CSARBT_ADDR
mdefine_line|#define CSARBT_ADDR 0xFFFA48
DECL|macro|CSARBT
mdefine_line|#define CSARBT WORD_REF(CSARBT_ADDR)
DECL|macro|CSOPBT_ADDR
mdefine_line|#define CSOPBT_ADDR 0xFFFA4A
DECL|macro|CSOPBT
mdefine_line|#define CSOPBT WORD_REF(CSOPBT_ADDR)
DECL|macro|CSBAR0_ADDR
mdefine_line|#define CSBAR0_ADDR 0xFFFA4C
DECL|macro|CSBAR0
mdefine_line|#define CSBAR0 WORD_REF(CSBAR0_ADDR)
DECL|macro|CSOR0_ADDR
mdefine_line|#define CSOR0_ADDR 0xFFFA4E
DECL|macro|CSOR0
mdefine_line|#define CSOR0 WORD_REF(CSOR0_ADDR)
DECL|macro|CSBAR1_ADDR
mdefine_line|#define CSBAR1_ADDR 0xFFFA50
DECL|macro|CSBAR1
mdefine_line|#define CSBAR1 WORD_REF(CSBAR1_ADDR)
DECL|macro|CSOR1_ADDR
mdefine_line|#define CSOR1_ADDR 0xFFFA52
DECL|macro|CSOR1
mdefine_line|#define CSOR1 WORD_REF(CSOR1_ADDR)
DECL|macro|CSBAR2_ADDR
mdefine_line|#define CSBAR2_ADDR 0xFFFA54
DECL|macro|CSBAR2
mdefine_line|#define CSBAR2 WORD_REF(CSBAR2_ADDR)
DECL|macro|CSOR2_ADDR
mdefine_line|#define CSOR2_ADDR 0xFFFA56
DECL|macro|CSOR2
mdefine_line|#define CSOR2 WORD_REF(CSOR2_ADDR)
DECL|macro|CSBAR3_ADDR
mdefine_line|#define CSBAR3_ADDR 0xFFFA58
DECL|macro|CSBAR3
mdefine_line|#define CSBAR3 WORD_REF(CSBAR3_ADDR)
DECL|macro|CSOR3_ADDR
mdefine_line|#define CSOR3_ADDR 0xFFFA5A
DECL|macro|CSOR3
mdefine_line|#define CSOR3 WORD_REF(CSOR3_ADDR)
DECL|macro|CSBAR4_ADDR
mdefine_line|#define CSBAR4_ADDR 0xFFFA5C
DECL|macro|CSBAR4
mdefine_line|#define CSBAR4 WORD_REF(CSBAR4_ADDR)
DECL|macro|CSOR4_ADDR
mdefine_line|#define CSOR4_ADDR 0xFFFA5E
DECL|macro|CSOR4
mdefine_line|#define CSOR4 WORD_REF(CSOR4_ADDR)
DECL|macro|CSBAR5_ADDR
mdefine_line|#define CSBAR5_ADDR 0xFFFA60
DECL|macro|CSBAR5
mdefine_line|#define CSBAR5 WORD_REF(CSBAR5_ADDR)
DECL|macro|CSOR5_ADDR
mdefine_line|#define CSOR5_ADDR 0xFFFA62
DECL|macro|CSOR5
mdefine_line|#define CSOR5 WORD_REF(CSOR5_ADDR)
DECL|macro|CSBAR6_ADDR
mdefine_line|#define CSBAR6_ADDR 0xFFFA64
DECL|macro|CSBAR6
mdefine_line|#define CSBAR6 WORD_REF(CSBAR6_ADDR)
DECL|macro|CSOR6_ADDR
mdefine_line|#define CSOR6_ADDR 0xFFFA66
DECL|macro|CSOR6
mdefine_line|#define CSOR6 WORD_REF(CSOR6_ADDR)
DECL|macro|CSBAR7_ADDR
mdefine_line|#define CSBAR7_ADDR 0xFFFA68
DECL|macro|CSBAR7
mdefine_line|#define CSBAR7 WORD_REF(CSBAR7_ADDR)
DECL|macro|CSOR7_ADDR
mdefine_line|#define CSOR7_ADDR 0xFFFA6A
DECL|macro|CSOR7
mdefine_line|#define CSOR7 WORD_REF(CSOR7_ADDR)
DECL|macro|CSBAR8_ADDR
mdefine_line|#define CSBAR8_ADDR 0xFFFA6C
DECL|macro|CSBAR8
mdefine_line|#define CSBAR8 WORD_REF(CSBAR8_ADDR)
DECL|macro|CSOR8_ADDR
mdefine_line|#define CSOR8_ADDR 0xFFFA6E
DECL|macro|CSOR8
mdefine_line|#define CSOR8 WORD_REF(CSOR8_ADDR)
DECL|macro|CSBAR9_ADDR
mdefine_line|#define CSBAR9_ADDR 0xFFFA70
DECL|macro|CSBAR9
mdefine_line|#define CSBAR9 WORD_REF(CSBAR9_ADDR)
DECL|macro|CSOR9_ADDR
mdefine_line|#define CSOR9_ADDR 0xFFFA72
DECL|macro|CSOR9
mdefine_line|#define CSOR9 WORD_REF(CSOR9_ADDR)
DECL|macro|CSBAR10_ADDR
mdefine_line|#define CSBAR10_ADDR 0xFFFA74
DECL|macro|CSBAR10
mdefine_line|#define CSBAR10 WORD_REF(CSBAR10_ADDR)
DECL|macro|CSOR10_ADDR
mdefine_line|#define CSOR10_ADDR 0xFFFA76
DECL|macro|CSOR10
mdefine_line|#define CSOR10 WORD_REF(CSOR10_ADDR)
DECL|macro|CSOR_MODE_ASYNC
mdefine_line|#define CSOR_MODE_ASYNC&t;0x0000
DECL|macro|CSOR_MODE_SYNC
mdefine_line|#define CSOR_MODE_SYNC&t;0x8000
DECL|macro|CSOR_MODE_MASK
mdefine_line|#define CSOR_MODE_MASK&t;0x8000
DECL|macro|CSOR_BYTE_DISABLE
mdefine_line|#define CSOR_BYTE_DISABLE&t;0x0000
DECL|macro|CSOR_BYTE_UPPER
mdefine_line|#define CSOR_BYTE_UPPER&t;&t;0x4000
DECL|macro|CSOR_BYTE_LOWER
mdefine_line|#define CSOR_BYTE_LOWER&t;&t;0x2000
DECL|macro|CSOR_BYTE_BOTH
mdefine_line|#define CSOR_BYTE_BOTH&t;&t;0x6000
DECL|macro|CSOR_BYTE_MASK
mdefine_line|#define CSOR_BYTE_MASK&t;&t;0x6000
DECL|macro|CSOR_RW_RSVD
mdefine_line|#define CSOR_RW_RSVD&t;&t;0x0000
DECL|macro|CSOR_RW_READ
mdefine_line|#define CSOR_RW_READ&t;&t;0x0800
DECL|macro|CSOR_RW_WRITE
mdefine_line|#define CSOR_RW_WRITE&t;&t;0x1000
DECL|macro|CSOR_RW_BOTH
mdefine_line|#define CSOR_RW_BOTH&t;&t;0x1800
DECL|macro|CSOR_RW_MASK
mdefine_line|#define CSOR_RW_MASK&t;&t;0x1800
DECL|macro|CSOR_STROBE_DS
mdefine_line|#define CSOR_STROBE_DS&t;&t;0x0400
DECL|macro|CSOR_STROBE_AS
mdefine_line|#define CSOR_STROBE_AS&t;&t;0x0000
DECL|macro|CSOR_STROBE_MASK
mdefine_line|#define CSOR_STROBE_MASK&t;0x0400
DECL|macro|CSOR_DSACK_WAIT
mdefine_line|#define CSOR_DSACK_WAIT(x)&t;(wait &lt;&lt; 6)
DECL|macro|CSOR_DSACK_FTERM
mdefine_line|#define CSOR_DSACK_FTERM&t;(14 &lt;&lt; 6)
DECL|macro|CSOR_DSACK_EXTERNAL
mdefine_line|#define CSOR_DSACK_EXTERNAL&t;(15 &lt;&lt; 6)
DECL|macro|CSOR_DSACK_MASK
mdefine_line|#define CSOR_DSACK_MASK&t;&t;0x03c0
DECL|macro|CSOR_SPACE_CPU
mdefine_line|#define CSOR_SPACE_CPU&t;&t;0x0000
DECL|macro|CSOR_SPACE_USER
mdefine_line|#define CSOR_SPACE_USER&t;&t;0x0010
DECL|macro|CSOR_SPACE_SU
mdefine_line|#define CSOR_SPACE_SU&t;&t;0x0020
DECL|macro|CSOR_SPACE_BOTH
mdefine_line|#define CSOR_SPACE_BOTH&t;&t;0x0030
DECL|macro|CSOR_SPACE_MASK
mdefine_line|#define CSOR_SPACE_MASK&t;&t;0x0030
DECL|macro|CSOR_IPL_ALL
mdefine_line|#define CSOR_IPL_ALL&t;&t;0x0000
DECL|macro|CSOR_IPL_PRIORITY
mdefine_line|#define CSOR_IPL_PRIORITY(x)&t;(x &lt;&lt; 1)
DECL|macro|CSOR_IPL_MASK
mdefine_line|#define CSOR_IPL_MASK&t;&t;0x000e
DECL|macro|CSOR_AVEC_ON
mdefine_line|#define CSOR_AVEC_ON&t;&t;0x0001
DECL|macro|CSOR_AVEC_OFF
mdefine_line|#define CSOR_AVEC_OFF&t;&t;0x0000
DECL|macro|CSOR_AVEC_MASK
mdefine_line|#define CSOR_AVEC_MASK&t;&t;0x0001
DECL|macro|CSBAR_ADDR
mdefine_line|#define CSBAR_ADDR(x)&t;&t;((addr &gt;&gt; 11) &lt;&lt; 3) 
DECL|macro|CSBAR_ADDR_MASK
mdefine_line|#define CSBAR_ADDR_MASK&t;&t;0xfff8
DECL|macro|CSBAR_BLKSIZE_2K
mdefine_line|#define CSBAR_BLKSIZE_2K&t;0x0000
DECL|macro|CSBAR_BLKSIZE_8K
mdefine_line|#define CSBAR_BLKSIZE_8K&t;0x0001
DECL|macro|CSBAR_BLKSIZE_16K
mdefine_line|#define CSBAR_BLKSIZE_16K&t;0x0002
DECL|macro|CSBAR_BLKSIZE_64K
mdefine_line|#define CSBAR_BLKSIZE_64K&t;0x0003
DECL|macro|CSBAR_BLKSIZE_128K
mdefine_line|#define CSBAR_BLKSIZE_128K&t;0x0004
DECL|macro|CSBAR_BLKSIZE_256K
mdefine_line|#define CSBAR_BLKSIZE_256K&t;0x0005
DECL|macro|CSBAR_BLKSIZE_512K
mdefine_line|#define CSBAR_BLKSIZE_512K&t;0x0006
DECL|macro|CSBAR_BLKSIZE_1M
mdefine_line|#define CSBAR_BLKSIZE_1M&t;0x0007
DECL|macro|CSBAR_BLKSIZE_MASK
mdefine_line|#define CSBAR_BLKSIZE_MASK&t;0x0007
DECL|macro|CSPAR_DISC
mdefine_line|#define CSPAR_DISC&t;0
DECL|macro|CSPAR_ALT
mdefine_line|#define CSPAR_ALT&t;1
DECL|macro|CSPAR_CS8
mdefine_line|#define CSPAR_CS8&t;2
DECL|macro|CSPAR_CS16
mdefine_line|#define CSPAR_CS16&t;3
DECL|macro|CSPAR_MASK
mdefine_line|#define CSPAR_MASK&t;3
DECL|macro|CSPAR0_CSBOOT
mdefine_line|#define CSPAR0_CSBOOT(x) (x &lt;&lt; 0)
DECL|macro|CSPAR0_CS0
mdefine_line|#define CSPAR0_CS0(x)&t;(x &lt;&lt; 2)
DECL|macro|CSPAR0_CS1
mdefine_line|#define CSPAR0_CS1(x)&t;(x &lt;&lt; 4)
DECL|macro|CSPAR0_CS2
mdefine_line|#define CSPAR0_CS2(x)&t;(x &lt;&lt; 6)
DECL|macro|CSPAR0_CS3
mdefine_line|#define CSPAR0_CS3(x)&t;(x &lt;&lt; 8)
DECL|macro|CSPAR0_CS4
mdefine_line|#define CSPAR0_CS4(x)&t;(x &lt;&lt; 10)
DECL|macro|CSPAR0_CS5
mdefine_line|#define CSPAR0_CS5(x)&t;(x &lt;&lt; 12)
DECL|macro|CSPAR1_CS6
mdefine_line|#define CSPAR1_CS6(x)&t;(x &lt;&lt; 0)
DECL|macro|CSPAR1_CS7
mdefine_line|#define CSPAR1_CS7(x)&t;(x &lt;&lt; 2)
DECL|macro|CSPAR1_CS8
mdefine_line|#define CSPAR1_CS8(x)&t;(x &lt;&lt; 4)
DECL|macro|CSPAR1_CS9
mdefine_line|#define CSPAR1_CS9(x)&t;(x &lt;&lt; 6)
DECL|macro|CSPAR1_CS10
mdefine_line|#define CSPAR1_CS10(x)&t;(x &lt;&lt; 8)
macro_line|#endif
eof
