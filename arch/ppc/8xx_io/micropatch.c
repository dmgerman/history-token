multiline_comment|/* Microcode patches for the CPM as supplied by Motorola.&n; * This is the one for IIC/SPI.  There is a newer one that&n; * also relocates SMC2, but this would require additional changes&n; * to uart.c, so I am holding off on that for a moment.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/8xx_immap.h&gt;
macro_line|#include &quot;commproc.h&quot;
multiline_comment|/* Define this to get SMC patches as well.  You need to modify the uart&n; * driver as well......&n;#define USE_SMC_PATCH 1&n; */
macro_line|#ifdef CONFIG_USB_MPC8xx
DECL|macro|USE_USB_SOF_PATCH
mdefine_line|#define USE_USB_SOF_PATCH
macro_line|#endif
macro_line|#ifdef USE_IIC_PATCH
DECL|macro|PATCH_DEFINED
mdefine_line|#define PATCH_DEFINED
multiline_comment|/* IIC/SPI */
DECL|variable|patch_2000
id|uint
id|patch_2000
(braket
)braket
op_assign
(brace
l_int|0x7FFFEFD9
comma
l_int|0x3FFD0000
comma
l_int|0x7FFB49F7
comma
l_int|0x7FF90000
comma
l_int|0x5FEFADF7
comma
l_int|0x5F89ADF7
comma
l_int|0x5FEFAFF7
comma
l_int|0x5F89AFF7
comma
l_int|0x3A9CFBC8
comma
l_int|0xE7C0EDF0
comma
l_int|0x77C1E1BB
comma
l_int|0xF4DC7F1D
comma
l_int|0xABAD932F
comma
l_int|0x4E08FDCF
comma
l_int|0x6E0FAFF8
comma
l_int|0x7CCF76CF
comma
l_int|0xFD1FF9CF
comma
l_int|0xABF88DC6
comma
l_int|0xAB5679F7
comma
l_int|0xB0937383
comma
l_int|0xDFCE79F7
comma
l_int|0xB091E6BB
comma
l_int|0xE5BBE74F
comma
l_int|0xB3FA6F0F
comma
l_int|0x6FFB76CE
comma
l_int|0xEE0DF9CF
comma
l_int|0x2BFBEFEF
comma
l_int|0xCFEEF9CF
comma
l_int|0x76CEAD24
comma
l_int|0x90B2DF9A
comma
l_int|0x7FDDD0BF
comma
l_int|0x4BF847FD
comma
l_int|0x7CCF76CE
comma
l_int|0xCFEF7E1F
comma
l_int|0x7F1D7DFD
comma
l_int|0xF0B6EF71
comma
l_int|0x7FC177C1
comma
l_int|0xFBC86079
comma
l_int|0xE722FBC8
comma
l_int|0x5FFFDFFF
comma
l_int|0x5FB2FFFB
comma
l_int|0xFBC8F3C8
comma
l_int|0x94A67F01
comma
l_int|0x7F1D5F39
comma
l_int|0xAFE85F5E
comma
l_int|0xFFDFDF96
comma
l_int|0xCB9FAF7D
comma
l_int|0x5FC1AFED
comma
l_int|0x8C1C5FC1
comma
l_int|0xAFDD5FC3
comma
l_int|0xDF9A7EFD
comma
l_int|0xB0B25FB2
comma
l_int|0xFFFEABAD
comma
l_int|0x5FB2FFFE
comma
l_int|0x5FCE600B
comma
l_int|0xE6BB600B
comma
l_int|0x5FCEDFC6
comma
l_int|0x27FBEFDF
comma
l_int|0x5FC8CFDE
comma
l_int|0x3A9CE7C0
comma
l_int|0xEDF0F3C8
comma
l_int|0x7F0154CD
comma
l_int|0x7F1D2D3D
comma
l_int|0x363A7570
comma
l_int|0x7E0AF1CE
comma
l_int|0x37EF2E68
comma
l_int|0x7FEE10EC
comma
l_int|0xADF8EFDE
comma
l_int|0xCFEAE52F
comma
l_int|0x7D0FE12B
comma
l_int|0xF1CE5F65
comma
l_int|0x7E0A4DF8
comma
l_int|0xCFEA5F72
comma
l_int|0x7D0BEFEE
comma
l_int|0xCFEA5F74
comma
l_int|0xE522EFDE
comma
l_int|0x5F74CFDA
comma
l_int|0x0B627385
comma
l_int|0xDF627E0A
comma
l_int|0x30D8145B
comma
l_int|0xBFFFF3C8
comma
l_int|0x5FFFDFFF
comma
l_int|0xA7F85F5E
comma
l_int|0xBFFE7F7D
comma
l_int|0x10D31450
comma
l_int|0x5F36BFFF
comma
l_int|0xAF785F5E
comma
l_int|0xBFFDA7F8
comma
l_int|0x5F36BFFE
comma
l_int|0x77FD30C0
comma
l_int|0x4E08FDCF
comma
l_int|0xE5FF6E0F
comma
l_int|0xAFF87E1F
comma
l_int|0x7E0FFD1F
comma
l_int|0xF1CF5F1B
comma
l_int|0xABF80D5E
comma
l_int|0x5F5EFFEF
comma
l_int|0x79F730A2
comma
l_int|0xAFDD5F34
comma
l_int|0x47F85F34
comma
l_int|0xAFED7FDD
comma
l_int|0x50B24978
comma
l_int|0x47FD7F1D
comma
l_int|0x7DFD70AD
comma
l_int|0xEF717EC1
comma
l_int|0x6BA47F01
comma
l_int|0x2D267EFD
comma
l_int|0x30DE5F5E
comma
l_int|0xFFFD5F5E
comma
l_int|0xFFEF5F5E
comma
l_int|0xFFDF0CA0
comma
l_int|0xAFED0A9E
comma
l_int|0xAFDD0C3A
comma
l_int|0x5F3AAFBD
comma
l_int|0x7FBDB082
comma
l_int|0x5F8247F8
)brace
suffix:semicolon
DECL|variable|patch_2f00
id|uint
id|patch_2f00
(braket
)braket
op_assign
(brace
l_int|0x3E303430
comma
l_int|0x34343737
comma
l_int|0xABF7BF9B
comma
l_int|0x994B4FBD
comma
l_int|0xBD599493
comma
l_int|0x349FFF37
comma
l_int|0xFB9B177D
comma
l_int|0xD9936956
comma
l_int|0xBBFDD697
comma
l_int|0xBDD2FD11
comma
l_int|0x31DB9BB3
comma
l_int|0x63139637
comma
l_int|0x93733693
comma
l_int|0x193137F7
comma
l_int|0x331737AF
comma
l_int|0x7BB9B999
comma
l_int|0xBB197957
comma
l_int|0x7FDFD3D5
comma
l_int|0x73B773F7
comma
l_int|0x37933B99
comma
l_int|0x1D115316
comma
l_int|0x99315315
comma
l_int|0x31694BF4
comma
l_int|0xFBDBD359
comma
l_int|0x31497353
comma
l_int|0x76956D69
comma
l_int|0x7B9D9693
comma
l_int|0x13131979
comma
l_int|0x79376935
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef USE_SMC_PATCH
DECL|macro|PATCH_DEFINED
mdefine_line|#define PATCH_DEFINED
multiline_comment|/* SMC2/IIC/SPI Patch */
multiline_comment|/* This is the area from 0x2000 to 0x23ff.&n;*/
DECL|variable|patch_2000
id|uint
id|patch_2000
(braket
)braket
op_assign
(brace
l_int|0x3fff0000
comma
l_int|0x3ffd0000
comma
l_int|0x3ffb0000
comma
l_int|0x3ff90000
comma
l_int|0x5f13eff8
comma
l_int|0x5eb5eff8
comma
l_int|0x5f88adf7
comma
l_int|0x5fefadf7
comma
l_int|0x3a9cfbc8
comma
l_int|0x77cae1bb
comma
l_int|0xf4de7fad
comma
l_int|0xabae9330
comma
l_int|0x4e08fdcf
comma
l_int|0x6e0faff8
comma
l_int|0x7ccf76cf
comma
l_int|0xfdaff9cf
comma
l_int|0xabf88dc8
comma
l_int|0xab5879f7
comma
l_int|0xb0925d8d
comma
l_int|0xdfd079f7
comma
l_int|0xb090e6bb
comma
l_int|0xe5bbe74f
comma
l_int|0x9e046f0f
comma
l_int|0x6ffb76ce
comma
l_int|0xee0cf9cf
comma
l_int|0x2bfbefef
comma
l_int|0xcfeef9cf
comma
l_int|0x76cead23
comma
l_int|0x90b3df99
comma
l_int|0x7fddd0c1
comma
l_int|0x4bf847fd
comma
l_int|0x7ccf76ce
comma
l_int|0xcfef77ca
comma
l_int|0x7eaf7fad
comma
l_int|0x7dfdf0b7
comma
l_int|0xef7a7fca
comma
l_int|0x77cafbc8
comma
l_int|0x6079e722
comma
l_int|0xfbc85fff
comma
l_int|0xdfff5fb3
comma
l_int|0xfffbfbc8
comma
l_int|0xf3c894a5
comma
l_int|0xe7c9edf9
comma
l_int|0x7f9a7fad
comma
l_int|0x5f36afe8
comma
l_int|0x5f5bffdf
comma
l_int|0xdf95cb9e
comma
l_int|0xaf7d5fc3
comma
l_int|0xafed8c1b
comma
l_int|0x5fc3afdd
comma
l_int|0x5fc5df99
comma
l_int|0x7efdb0b3
comma
l_int|0x5fb3fffe
comma
l_int|0xabae5fb3
comma
l_int|0xfffe5fd0
comma
l_int|0x600be6bb
comma
l_int|0x600b5fd0
comma
l_int|0xdfc827fb
comma
l_int|0xefdf5fca
comma
l_int|0xcfde3a9c
comma
l_int|0xe7c9edf9
comma
l_int|0xf3c87f9e
comma
l_int|0x54ca7fed
comma
l_int|0x2d3a3637
comma
l_int|0x756f7e9a
comma
l_int|0xf1ce37ef
comma
l_int|0x2e677fee
comma
l_int|0x10ebadf8
comma
l_int|0xefdecfea
comma
l_int|0xe52f7d9f
comma
l_int|0xe12bf1ce
comma
l_int|0x5f647e9a
comma
l_int|0x4df8cfea
comma
l_int|0x5f717d9b
comma
l_int|0xefeecfea
comma
l_int|0x5f73e522
comma
l_int|0xefde5f73
comma
l_int|0xcfda0b61
comma
l_int|0x5d8fdf61
comma
l_int|0xe7c9edf9
comma
l_int|0x7e9a30d5
comma
l_int|0x1458bfff
comma
l_int|0xf3c85fff
comma
l_int|0xdfffa7f8
comma
l_int|0x5f5bbffe
comma
l_int|0x7f7d10d0
comma
l_int|0x144d5f33
comma
l_int|0xbfffaf78
comma
l_int|0x5f5bbffd
comma
l_int|0xa7f85f33
comma
l_int|0xbffe77fd
comma
l_int|0x30bd4e08
comma
l_int|0xfdcfe5ff
comma
l_int|0x6e0faff8
comma
l_int|0x7eef7e9f
comma
l_int|0xfdeff1cf
comma
l_int|0x5f17abf8
comma
l_int|0x0d5b5f5b
comma
l_int|0xffef79f7
comma
l_int|0x309eafdd
comma
l_int|0x5f3147f8
comma
l_int|0x5f31afed
comma
l_int|0x7fdd50af
comma
l_int|0x497847fd
comma
l_int|0x7f9e7fed
comma
l_int|0x7dfd70a9
comma
l_int|0xef7e7ece
comma
l_int|0x6ba07f9e
comma
l_int|0x2d227efd
comma
l_int|0x30db5f5b
comma
l_int|0xfffd5f5b
comma
l_int|0xffef5f5b
comma
l_int|0xffdf0c9c
comma
l_int|0xafed0a9a
comma
l_int|0xafdd0c37
comma
l_int|0x5f37afbd
comma
l_int|0x7fbdb081
comma
l_int|0x5f8147f8
comma
l_int|0x3a11e710
comma
l_int|0xedf0ccdd
comma
l_int|0xf3186d0a
comma
l_int|0x7f0e5f06
comma
l_int|0x7fedbb38
comma
l_int|0x3afe7468
comma
l_int|0x7fedf4fc
comma
l_int|0x8ffbb951
comma
l_int|0xb85f77fd
comma
l_int|0xb0df5ddd
comma
l_int|0xdefe7fed
comma
l_int|0x90e1e74d
comma
l_int|0x6f0dcbf7
comma
l_int|0xe7decfed
comma
l_int|0xcb74cfed
comma
l_int|0xcfeddf6d
comma
l_int|0x91714f74
comma
l_int|0x5dd2deef
comma
l_int|0x9e04e7df
comma
l_int|0xefbb6ffb
comma
l_int|0xe7ef7f0e
comma
l_int|0x9e097fed
comma
l_int|0xebdbeffa
comma
l_int|0xeb54affb
comma
l_int|0x7fea90d7
comma
l_int|0x7e0cf0c3
comma
l_int|0xbffff318
comma
l_int|0x5fffdfff
comma
l_int|0xac59efea
comma
l_int|0x7fce1ee5
comma
l_int|0xe2ff5ee1
comma
l_int|0xaffbe2ff
comma
l_int|0x5ee3affb
comma
l_int|0xf9cc7d0f
comma
l_int|0xaef8770f
comma
l_int|0x7d0fb0c6
comma
l_int|0xeffbbfff
comma
l_int|0xcfef5ede
comma
l_int|0x7d0fbfff
comma
l_int|0x5ede4cf8
comma
l_int|0x7fddd0bf
comma
l_int|0x49f847fd
comma
l_int|0x7efdf0bb
comma
l_int|0x7fedfffd
comma
l_int|0x7dfdf0b7
comma
l_int|0xef7e7e1e
comma
l_int|0x5ede7f0e
comma
l_int|0x3a11e710
comma
l_int|0xedf0ccab
comma
l_int|0xfb18ad2e
comma
l_int|0x1ea9bbb8
comma
l_int|0x74283b7e
comma
l_int|0x73c2e4bb
comma
l_int|0x2ada4fb8
comma
l_int|0xdc21e4bb
comma
l_int|0xb2a1ffbf
comma
l_int|0x5e2c43f8
comma
l_int|0xfc87e1bb
comma
l_int|0xe74ffd91
comma
l_int|0x6f0f4fe8
comma
l_int|0xc7ba32e2
comma
l_int|0xf396efeb
comma
l_int|0x600b4f78
comma
l_int|0xe5bb760b
comma
l_int|0x53acaef8
comma
l_int|0x4ef88b0e
comma
l_int|0xcfef9e09
comma
l_int|0xabf8751f
comma
l_int|0xefef5bac
comma
l_int|0x741f4fe8
comma
l_int|0x751e760d
comma
l_int|0x7fdbf081
comma
l_int|0x741cafce
comma
l_int|0xefcc7fce
comma
l_int|0x751e70ac
comma
l_int|0x741ce7bb
comma
l_int|0x3372cfed
comma
l_int|0xafdbefeb
comma
l_int|0xe5bb760b
comma
l_int|0x53f2aef8
comma
l_int|0xafe8e7eb
comma
l_int|0x4bf8771e
comma
l_int|0x7e247fed
comma
l_int|0x4fcbe2cc
comma
l_int|0x7fbc30a9
comma
l_int|0x7b0f7a0f
comma
l_int|0x34d577fd
comma
l_int|0x308b5db7
comma
l_int|0xde553e5f
comma
l_int|0xaf78741f
comma
l_int|0x741f30f0
comma
l_int|0xcfef5e2c
comma
l_int|0x741f3eac
comma
l_int|0xafb8771e
comma
l_int|0x5e677fed
comma
l_int|0x0bd3e2cc
comma
l_int|0x741ccfec
comma
l_int|0xe5ca53cd
comma
l_int|0x6fcb4f74
comma
l_int|0x5dadde4b
comma
l_int|0x2ab63d38
comma
l_int|0x4bb3de30
comma
l_int|0x751f741c
comma
l_int|0x6c42effa
comma
l_int|0xefea7fce
comma
l_int|0x6ffc30be
comma
l_int|0xefec3fca
comma
l_int|0x30b3de2e
comma
l_int|0xadf85d9e
comma
l_int|0xaf7daefd
comma
l_int|0x5d9ede2e
comma
l_int|0x5d9eafdd
comma
l_int|0x761f10ac
comma
l_int|0x1da07efd
comma
l_int|0x30adfffe
comma
l_int|0x4908fb18
comma
l_int|0x5fffdfff
comma
l_int|0xafbb709b
comma
l_int|0x4ef85e67
comma
l_int|0xadf814ad
comma
l_int|0x7a0f70ad
comma
l_int|0xcfef50ad
comma
l_int|0x7a0fde30
comma
l_int|0x5da0afed
comma
l_int|0x3c12780f
comma
l_int|0xefef780f
comma
l_int|0xefef790f
comma
l_int|0xa7f85e0f
comma
l_int|0xffef790f
comma
l_int|0xefef790f
comma
l_int|0x14adde2e
comma
l_int|0x5d9eadfd
comma
l_int|0x5e2dfffb
comma
l_int|0xe79addfd
comma
l_int|0xeff96079
comma
l_int|0x607ae79a
comma
l_int|0xddfceff9
comma
l_int|0x60795dff
comma
l_int|0x607acfef
comma
l_int|0xefefefdf
comma
l_int|0xefbfef7f
comma
l_int|0xeeffedff
comma
l_int|0xebffe7ff
comma
l_int|0xafefafdf
comma
l_int|0xafbfaf7f
comma
l_int|0xaeffadff
comma
l_int|0xabffa7ff
comma
l_int|0x6fef6fdf
comma
l_int|0x6fbf6f7f
comma
l_int|0x6eff6dff
comma
l_int|0x6bff67ff
comma
l_int|0x2fef2fdf
comma
l_int|0x2fbf2f7f
comma
l_int|0x2eff2dff
comma
l_int|0x2bff27ff
comma
l_int|0x4e08fd1f
comma
l_int|0xe5ff6e0f
comma
l_int|0xaff87eef
comma
l_int|0x7e0ffdef
comma
l_int|0xf11f6079
comma
l_int|0xabf8f542
comma
l_int|0x7e0af11c
comma
l_int|0x37cfae3a
comma
l_int|0x7fec90be
comma
l_int|0xadf8efdc
comma
l_int|0xcfeae52f
comma
l_int|0x7d0fe12b
comma
l_int|0xf11c6079
comma
l_int|0x7e0a4df8
comma
l_int|0xcfea5dc4
comma
l_int|0x7d0befec
comma
l_int|0xcfea5dc6
comma
l_int|0xe522efdc
comma
l_int|0x5dc6cfda
comma
l_int|0x4e08fd1f
comma
l_int|0x6e0faff8
comma
l_int|0x7c1f761f
comma
l_int|0xfdeff91f
comma
l_int|0x6079abf8
comma
l_int|0x761cee24
comma
l_int|0xf91f2bfb
comma
l_int|0xefefcfec
comma
l_int|0xf91f6079
comma
l_int|0x761c27fb
comma
l_int|0xefdf5da7
comma
l_int|0xcfdc7fdd
comma
l_int|0xd09c4bf8
comma
l_int|0x47fd7c1f
comma
l_int|0x761ccfcf
comma
l_int|0x7eef7fed
comma
l_int|0x7dfdf093
comma
l_int|0xef7e7f1e
comma
l_int|0x771efb18
comma
l_int|0x6079e722
comma
l_int|0xe6bbe5bb
comma
l_int|0xae0ae5bb
comma
l_int|0x600bae85
comma
l_int|0xe2bbe2bb
comma
l_int|0xe2bbe2bb
comma
l_int|0xaf02e2bb
comma
l_int|0xe2bb2ff9
comma
l_int|0x6079e2bb
)brace
suffix:semicolon
multiline_comment|/* This is from 0x2f00 to 0x2fff&n;&t;*/
DECL|variable|patch_2f00
id|uint
id|patch_2f00
(braket
)braket
op_assign
(brace
l_int|0x30303030
comma
l_int|0x3e3e3434
comma
l_int|0xabbf9b99
comma
l_int|0x4b4fbdbd
comma
l_int|0x59949334
comma
l_int|0x9fff37fb
comma
l_int|0x9b177dd9
comma
l_int|0x936956bb
comma
l_int|0xfbdd697b
comma
l_int|0xdd2fd113
comma
l_int|0x1db9f7bb
comma
l_int|0x36313963
comma
l_int|0x79373369
comma
l_int|0x3193137f
comma
l_int|0x7331737a
comma
l_int|0xf7bb9b99
comma
l_int|0x9bb19795
comma
l_int|0x77fdfd3d
comma
l_int|0x573b773f
comma
l_int|0x737933f7
comma
l_int|0xb991d115
comma
l_int|0x31699315
comma
l_int|0x31531694
comma
l_int|0xbf4fbdbd
comma
l_int|0x35931497
comma
l_int|0x35376956
comma
l_int|0xbd697b9d
comma
l_int|0x96931313
comma
l_int|0x19797937
comma
l_int|0x6935af78
comma
l_int|0xb9b3baa3
comma
l_int|0xb8788683
comma
l_int|0x368f78f7
comma
l_int|0x87778733
comma
l_int|0x3ffffb3b
comma
l_int|0x8e8f78b8
comma
l_int|0x1d118e13
comma
l_int|0xf3ff3f8b
comma
l_int|0x6bd8e173
comma
l_int|0xd1366856
comma
l_int|0x68d1687b
comma
l_int|0x3daf78b8
comma
l_int|0x3a3a3f87
comma
l_int|0x8f81378f
comma
l_int|0xf876f887
comma
l_int|0x77fd8778
comma
l_int|0x737de8d6
comma
l_int|0xbbf8bfff
comma
l_int|0xd8df87f7
comma
l_int|0xfd876f7b
comma
l_int|0x8bfff8bd
comma
l_int|0x8683387d
comma
l_int|0xb873d87b
comma
l_int|0x3b8fd7f8
comma
l_int|0xf7338883
comma
l_int|0xbb8ee1f8
comma
l_int|0xef837377
comma
l_int|0x3337b836
comma
l_int|0x817d11f8
comma
l_int|0x7378b878
comma
l_int|0xd3368b7d
comma
l_int|0xed731b7d
comma
l_int|0x833731f3
comma
l_int|0xf22f3f23
)brace
suffix:semicolon
DECL|variable|patch_2e00
id|uint
id|patch_2e00
(braket
)braket
op_assign
(brace
multiline_comment|/* This is from 0x2e00 to 0x2e3c&n;&t;*/
l_int|0x27eeeeee
comma
l_int|0xeeeeeeee
comma
l_int|0xeeeeeeee
comma
l_int|0xeeeeeeee
comma
l_int|0xee4bf4fb
comma
l_int|0xdbd259bb
comma
l_int|0x1979577f
comma
l_int|0xdfd2d573
comma
l_int|0xb773f737
comma
l_int|0x4b4fbdbd
comma
l_int|0x25b9b177
comma
l_int|0xd2d17376
comma
l_int|0x956bbfdd
comma
l_int|0x697bdd2f
comma
l_int|0xff9f79ff
comma
l_int|0xff9ff22f
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef USE_USB_SOF_PATCH
DECL|macro|PATCH_DEFINED
mdefine_line|#define PATCH_DEFINED
DECL|variable|patch_2000
id|uint
id|patch_2000
(braket
)braket
op_assign
(brace
l_int|0x7fff0000
comma
l_int|0x7ffd0000
comma
l_int|0x7ffb0000
comma
l_int|0x49f7ba5b
comma
l_int|0xba383ffb
comma
l_int|0xf9b8b46d
comma
l_int|0xe5ab4e07
comma
l_int|0xaf77bffe
comma
l_int|0x3f7bbf79
comma
l_int|0xba5bba38
comma
l_int|0xe7676076
comma
l_int|0x60750000
)brace
suffix:semicolon
DECL|variable|patch_2f00
id|uint
id|patch_2f00
(braket
)braket
op_assign
(brace
l_int|0x3030304c
comma
l_int|0xcab9e441
comma
l_int|0xa1aaf220
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Load the microcode patch.  This is called early in the CPM initialization&n; * with the controller in the reset state.  We enable the processor after&n; * we load the patch.&n; */
r_void
DECL|function|cpm_load_patch
id|cpm_load_patch
c_func
(paren
r_volatile
id|immap_t
op_star
id|immr
)paren
(brace
macro_line|#ifdef PATCH_DEFINED
r_volatile
id|uint
op_star
id|dp
suffix:semicolon
r_volatile
id|cpm8xx_t
op_star
id|commproc
suffix:semicolon
r_volatile
id|iic_t
op_star
id|iip
suffix:semicolon
r_volatile
id|spi_t
op_star
id|spp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|commproc
op_assign
(paren
id|cpm8xx_t
op_star
)paren
op_amp
id|immr-&gt;im_cpm
suffix:semicolon
multiline_comment|/* We work closely with commproc.c.  We know it only allocates&n;&t; * from data only space.&n;&t; * For this particular patch, we only use the bottom 512 bytes&n;&t; * and the upper 256 byte extension.  We will use the space&n;&t; * starting at 1K for the relocated parameters, as the general&n;&t; * CPM allocation won&squot;t come from that area.&n;&t; */
id|commproc-&gt;cp_rccr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Copy the patch into DPRAM.&n;&t;*/
id|dp
op_assign
(paren
id|uint
op_star
)paren
(paren
id|commproc-&gt;cp_dpmem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_sizeof
(paren
id|patch_2000
)paren
op_div
l_int|4
)paren
suffix:semicolon
id|i
op_increment
)paren
op_star
id|dp
op_increment
op_assign
id|patch_2000
(braket
id|i
)braket
suffix:semicolon
id|dp
op_assign
(paren
id|uint
op_star
)paren
op_amp
(paren
id|commproc-&gt;cp_dpmem
(braket
l_int|0x0f00
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_sizeof
(paren
id|patch_2f00
)paren
op_div
l_int|4
)paren
suffix:semicolon
id|i
op_increment
)paren
op_star
id|dp
op_increment
op_assign
id|patch_2f00
(braket
id|i
)braket
suffix:semicolon
macro_line|#ifdef USE_USB_SOF_PATCH
macro_line|#if 0 /* usb patch should not relocate iic */
id|iip
op_assign
(paren
id|iic_t
op_star
)paren
op_amp
id|commproc-&gt;cp_dparam
(braket
id|PROFF_IIC
)braket
suffix:semicolon
mdefine_line|#define RPBASE 0x0030
id|iip-&gt;iic_rpbase
op_assign
id|RPBASE
suffix:semicolon
multiline_comment|/* Put SPI above the IIC, also 32-byte aligned.&n;&t;*/
id|i
op_assign
(paren
id|RPBASE
op_plus
r_sizeof
(paren
id|iic_t
)paren
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
suffix:semicolon
id|spp
op_assign
(paren
id|spi_t
op_star
)paren
op_amp
id|commproc-&gt;cp_dparam
(braket
id|PROFF_SPI
)braket
suffix:semicolon
id|spp-&gt;spi_rpbase
op_assign
id|i
suffix:semicolon
macro_line|#endif
multiline_comment|/* Enable uCode fetches from DPRAM. */
id|commproc-&gt;cp_rccr
op_assign
l_int|0x0009
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;USB uCode patch installed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* USE_USB_SOF_PATCH */
macro_line|#if defined(USE_SMC_PATCH) || defined(USE_IIC_PATCH)
id|iip
op_assign
(paren
id|iic_t
op_star
)paren
op_amp
id|commproc-&gt;cp_dparam
(braket
id|PROFF_IIC
)braket
suffix:semicolon
DECL|macro|RPBASE
mdefine_line|#define RPBASE 0x0400
id|iip-&gt;iic_rpbase
op_assign
id|RPBASE
suffix:semicolon
multiline_comment|/* Put SPI above the IIC, also 32-byte aligned.&n;&t;*/
id|i
op_assign
(paren
id|RPBASE
op_plus
r_sizeof
(paren
id|iic_t
)paren
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
suffix:semicolon
id|spp
op_assign
(paren
id|spi_t
op_star
)paren
op_amp
id|commproc-&gt;cp_dparam
(braket
id|PROFF_SPI
)braket
suffix:semicolon
id|spp-&gt;spi_rpbase
op_assign
id|i
suffix:semicolon
macro_line|#ifdef USE_SMC_PATCH
id|dp
op_assign
(paren
id|uint
op_star
)paren
op_amp
(paren
id|commproc-&gt;cp_dpmem
(braket
l_int|0x0e00
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_sizeof
(paren
id|patch_2e00
)paren
op_div
l_int|4
)paren
suffix:semicolon
id|i
op_increment
)paren
op_star
id|dp
op_increment
op_assign
id|patch_2e00
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* Enable the traps to get to it.&n;&t;*/
id|commproc-&gt;cp_cpmcr1
op_assign
l_int|0x8080
suffix:semicolon
id|commproc-&gt;cp_cpmcr2
op_assign
l_int|0x808a
suffix:semicolon
id|commproc-&gt;cp_cpmcr3
op_assign
l_int|0x8028
suffix:semicolon
id|commproc-&gt;cp_cpmcr4
op_assign
l_int|0x802a
suffix:semicolon
multiline_comment|/* Enable uCode fetches from DPRAM.&n;&t;*/
id|commproc-&gt;cp_rccr
op_assign
l_int|3
suffix:semicolon
macro_line|#endif
macro_line|#ifdef USE_IIC_PATCH
multiline_comment|/* Enable the traps to get to it.&n;&t;*/
id|commproc-&gt;cp_cpmcr1
op_assign
l_int|0x802a
suffix:semicolon
id|commproc-&gt;cp_cpmcr2
op_assign
l_int|0x8028
suffix:semicolon
id|commproc-&gt;cp_cpmcr3
op_assign
l_int|0x802e
suffix:semicolon
id|commproc-&gt;cp_cpmcr4
op_assign
l_int|0x802c
suffix:semicolon
multiline_comment|/* Enable uCode fetches from DPRAM.&n;&t;*/
id|commproc-&gt;cp_rccr
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;I2C uCode patch installed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Relocate the IIC and SPI parameter areas.  These have to&n;&t; * aligned on 32-byte boundaries.&n;&t; */
id|iip
op_assign
(paren
id|iic_t
op_star
)paren
op_amp
id|commproc-&gt;cp_dparam
(braket
id|PROFF_IIC
)braket
suffix:semicolon
id|iip-&gt;iic_rpbase
op_assign
id|RPBASE
suffix:semicolon
multiline_comment|/* Put SPI above the IIC, also 32-byte aligned.&n;&t;*/
id|i
op_assign
(paren
id|RPBASE
op_plus
r_sizeof
(paren
id|iic_t
)paren
op_plus
l_int|31
)paren
op_amp
op_complement
l_int|31
suffix:semicolon
id|spp
op_assign
(paren
id|spi_t
op_star
)paren
op_amp
id|commproc-&gt;cp_dparam
(braket
id|PROFF_SPI
)braket
suffix:semicolon
id|spp-&gt;spi_rpbase
op_assign
id|i
suffix:semicolon
macro_line|#endif /* USE_SMC_PATCH || USE_IIC_PATCH */
macro_line|#endif /* PATCH_DEFINED */
)brace
r_void
DECL|function|verify_patch
id|verify_patch
c_func
(paren
r_volatile
id|immap_t
op_star
id|immr
)paren
(brace
macro_line|#ifdef PATCH_DEFINED
r_volatile
id|uint
op_star
id|dp
suffix:semicolon
r_volatile
id|cpm8xx_t
op_star
id|commproc
suffix:semicolon
r_int
id|i
suffix:semicolon
id|commproc
op_assign
(paren
id|cpm8xx_t
op_star
)paren
op_amp
id|immr-&gt;im_cpm
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cp_rccr %x&bslash;n&quot;
comma
id|commproc-&gt;cp_rccr
)paren
suffix:semicolon
id|commproc-&gt;cp_rccr
op_assign
l_int|0
suffix:semicolon
id|dp
op_assign
(paren
id|uint
op_star
)paren
(paren
id|commproc-&gt;cp_dpmem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_sizeof
(paren
id|patch_2000
)paren
op_div
l_int|4
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_star
id|dp
op_increment
op_ne
id|patch_2000
(braket
id|i
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;patch_2000 bad at %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|dp
op_decrement
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;found 0x%X, wanted 0x%X&bslash;n&quot;
comma
op_star
id|dp
comma
id|patch_2000
(braket
id|i
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dp
op_assign
(paren
id|uint
op_star
)paren
op_amp
(paren
id|commproc-&gt;cp_dpmem
(braket
l_int|0x0f00
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_sizeof
(paren
id|patch_2f00
)paren
op_div
l_int|4
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_star
id|dp
op_increment
op_ne
id|patch_2f00
(braket
id|i
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;patch_2f00 bad at %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|dp
op_decrement
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;found 0x%X, wanted 0x%X&bslash;n&quot;
comma
op_star
id|dp
comma
id|patch_2f00
(braket
id|i
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|commproc-&gt;cp_rccr
op_assign
l_int|0x0009
suffix:semicolon
macro_line|#endif /* PATCH_DEFINED */
)brace
eof
