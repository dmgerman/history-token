multiline_comment|/*&n; *  include/asm-s390/misc390.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; */
DECL|macro|allocaligned2
mdefine_line|#define&t;allocaligned2(type,name,number,align)&t;&t;&t;&t;&bslash;&n;   __u8&t;name##buff[(sizeof(type)*(number+1))-1]; &t;                &bslash;&n;   type&t;*name=(type *)(((__u32)(&amp;name##buff[align-1]))&amp;(-align))
DECL|macro|allocaligned
mdefine_line|#define&t;allocaligned(type,name,number)  allocaligned2(type,name,number,__alignof__(type))
eof
