multiline_comment|/* &n; * IEEE754 floating point&n; * common internal header file&n; */
multiline_comment|/*&n; * MIPS floating point support&n; * Copyright (C) 1994-2000 Algorithmics Ltd.  All rights reserved.&n; * http://www.algor.co.uk&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; */
macro_line|#include &quot;ieee754.h&quot;
DECL|macro|DP_EBIAS
mdefine_line|#define DP_EBIAS&t;1023
DECL|macro|DP_EMIN
mdefine_line|#define DP_EMIN&t;&t;(-1022)
DECL|macro|DP_EMAX
mdefine_line|#define DP_EMAX&t;&t;1023
DECL|macro|DP_MBITS
mdefine_line|#define DP_MBITS&t;52
DECL|macro|SP_EBIAS
mdefine_line|#define SP_EBIAS&t;127
DECL|macro|SP_EMIN
mdefine_line|#define SP_EMIN&t;&t;(-126)
DECL|macro|SP_EMAX
mdefine_line|#define SP_EMAX&t;&t;127
DECL|macro|SP_MBITS
mdefine_line|#define SP_MBITS&t;23
DECL|macro|DP_MBIT
mdefine_line|#define DP_MBIT(x)&t;((unsigned long long)1 &lt;&lt; (x))
DECL|macro|DP_HIDDEN_BIT
mdefine_line|#define DP_HIDDEN_BIT&t;DP_MBIT(DP_MBITS)
DECL|macro|DP_SIGN_BIT
mdefine_line|#define DP_SIGN_BIT&t;DP_MBIT(63)
DECL|macro|SP_MBIT
mdefine_line|#define SP_MBIT(x)&t;((unsigned long)1 &lt;&lt; (x))
DECL|macro|SP_HIDDEN_BIT
mdefine_line|#define SP_HIDDEN_BIT&t;SP_MBIT(SP_MBITS)
DECL|macro|SP_SIGN_BIT
mdefine_line|#define SP_SIGN_BIT&t;SP_MBIT(31)
DECL|macro|SPSIGN
mdefine_line|#define SPSIGN(sp)&t;(sp.parts.sign)
DECL|macro|SPBEXP
mdefine_line|#define SPBEXP(sp)&t;(sp.parts.bexp)
DECL|macro|SPMANT
mdefine_line|#define SPMANT(sp)&t;(sp.parts.mant)
DECL|macro|DPSIGN
mdefine_line|#define DPSIGN(dp)&t;(dp.parts.sign)
DECL|macro|DPBEXP
mdefine_line|#define DPBEXP(dp)&t;(dp.parts.bexp)
DECL|macro|DPMANT
mdefine_line|#define DPMANT(dp)&t;(dp.parts.mant)
DECL|macro|CLPAIR
mdefine_line|#define CLPAIR(x,y)&t;((x)*6+(y))
DECL|macro|CLEARCX
mdefine_line|#define CLEARCX&t;&bslash;&n;  (ieee754_csr.cx = 0)
DECL|macro|SETCX
mdefine_line|#define SETCX(x) &bslash;&n;  (ieee754_csr.cx |= (x),ieee754_csr.sx |= (x),ieee754_csr.mx &amp; (x))
DECL|macro|TSTX
mdefine_line|#define TSTX()&t;&bslash;&n;&t;(ieee754_csr.cx &amp; ieee754_csr.mx)
DECL|macro|COMPXSP
mdefine_line|#define COMPXSP &bslash;&n;  unsigned xm; int xe; int xs; int xc
DECL|macro|COMPYSP
mdefine_line|#define COMPYSP &bslash;&n;  unsigned ym; int ye; int ys; int yc
DECL|macro|EXPLODESP
mdefine_line|#define EXPLODESP(v,vc,vs,ve,vm) &bslash;&n;{&bslash;&n;    vs = SPSIGN(v);&bslash;&n;    ve = SPBEXP(v);&bslash;&n;    vm = SPMANT(v);&bslash;&n;    if(ve == SP_EMAX+1+SP_EBIAS){&bslash;&n;&t;if(vm == 0)&bslash;&n;&t;  vc = IEEE754_CLASS_INF;&bslash;&n;&t;else if(vm &amp; SP_MBIT(SP_MBITS-1)) &bslash;&n;&t;  vc = IEEE754_CLASS_QNAN;&bslash;&n;&t;else &bslash;&n;&t;  vc = IEEE754_CLASS_SNAN;&bslash;&n;    } else if(ve == SP_EMIN-1+SP_EBIAS) {&bslash;&n;&t;if(vm) {&bslash;&n;&t;    ve = SP_EMIN;&bslash;&n;&t;    vc = IEEE754_CLASS_DNORM;&bslash;&n;&t;} else&bslash;&n;&t;  vc = IEEE754_CLASS_ZERO;&bslash;&n;    } else {&bslash;&n;&t;ve -= SP_EBIAS;&bslash;&n;&t;vm |= SP_HIDDEN_BIT;&bslash;&n;&t;vc = IEEE754_CLASS_NORM;&bslash;&n;    }&bslash;&n;}
DECL|macro|EXPLODEXSP
mdefine_line|#define EXPLODEXSP EXPLODESP(x,xc,xs,xe,xm)
DECL|macro|EXPLODEYSP
mdefine_line|#define EXPLODEYSP EXPLODESP(y,yc,ys,ye,ym)
DECL|macro|COMPXDP
mdefine_line|#define COMPXDP &bslash;&n;unsigned long long xm; int xe; int xs; int xc
DECL|macro|COMPYDP
mdefine_line|#define COMPYDP &bslash;&n;unsigned long long ym; int ye; int ys; int yc
DECL|macro|EXPLODEDP
mdefine_line|#define EXPLODEDP(v,vc,vs,ve,vm) &bslash;&n;{&bslash;&n;    vm = DPMANT(v);&bslash;&n;    vs = DPSIGN(v);&bslash;&n;    ve = DPBEXP(v);&bslash;&n;    if(ve == DP_EMAX+1+DP_EBIAS){&bslash;&n;&t;if(vm == 0)&bslash;&n;&t;  vc = IEEE754_CLASS_INF;&bslash;&n;&t;else if(vm &amp; DP_MBIT(DP_MBITS-1)) &bslash;&n;&t;  vc = IEEE754_CLASS_QNAN;&bslash;&n;&t;else &bslash;&n;&t;  vc = IEEE754_CLASS_SNAN;&bslash;&n;    } else if(ve == DP_EMIN-1+DP_EBIAS) {&bslash;&n;&t;if(vm) {&bslash;&n;&t;    ve = DP_EMIN;&bslash;&n;&t;    vc = IEEE754_CLASS_DNORM;&bslash;&n;&t;} else&bslash;&n;&t;  vc = IEEE754_CLASS_ZERO;&bslash;&n;    } else {&bslash;&n;&t;ve -= DP_EBIAS;&bslash;&n;&t;vm |= DP_HIDDEN_BIT;&bslash;&n;&t;vc = IEEE754_CLASS_NORM;&bslash;&n;    }&bslash;&n;}
DECL|macro|EXPLODEXDP
mdefine_line|#define EXPLODEXDP EXPLODEDP(x,xc,xs,xe,xm)
DECL|macro|EXPLODEYDP
mdefine_line|#define EXPLODEYDP EXPLODEDP(y,yc,ys,ye,ym)
eof
