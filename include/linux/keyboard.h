macro_line|#ifndef __LINUX_KEYBOARD_H
DECL|macro|__LINUX_KEYBOARD_H
mdefine_line|#define __LINUX_KEYBOARD_H
macro_line|#include &lt;linux/wait.h&gt;
DECL|macro|KG_SHIFT
mdefine_line|#define KG_SHIFT&t;0
DECL|macro|KG_CTRL
mdefine_line|#define KG_CTRL&t;&t;2
DECL|macro|KG_ALT
mdefine_line|#define KG_ALT&t;&t;3
DECL|macro|KG_ALTGR
mdefine_line|#define KG_ALTGR&t;1
DECL|macro|KG_SHIFTL
mdefine_line|#define KG_SHIFTL&t;4
DECL|macro|KG_SHIFTR
mdefine_line|#define KG_SHIFTR&t;5
DECL|macro|KG_CTRLL
mdefine_line|#define KG_CTRLL&t;6
DECL|macro|KG_CTRLR
mdefine_line|#define KG_CTRLR&t;7
DECL|macro|KG_CAPSSHIFT
mdefine_line|#define KG_CAPSSHIFT&t;8
DECL|macro|NR_SHIFT
mdefine_line|#define NR_SHIFT&t;9
DECL|macro|NR_KEYS
mdefine_line|#define NR_KEYS&t;&t;128
DECL|macro|MAX_NR_KEYMAPS
mdefine_line|#define MAX_NR_KEYMAPS&t;256
multiline_comment|/* This means 64Kb if all keymaps are allocated. Only the superuser&n;&t;may increase the number of keymaps beyond MAX_NR_OF_USER_KEYMAPS. */
DECL|macro|MAX_NR_OF_USER_KEYMAPS
mdefine_line|#define MAX_NR_OF_USER_KEYMAPS 256 &t;/* should be at least 7 */
macro_line|#ifdef __KERNEL__
r_extern
r_const
r_int
id|NR_TYPES
suffix:semicolon
r_extern
r_const
r_int
id|max_vals
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
op_star
id|key_maps
(braket
id|MAX_NR_KEYMAPS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|plain_map
(braket
id|NR_KEYS
)braket
suffix:semicolon
r_extern
r_int
r_char
id|keyboard_type
suffix:semicolon
macro_line|#endif
DECL|macro|MAX_NR_FUNC
mdefine_line|#define MAX_NR_FUNC&t;256&t;/* max nr of strings assigned to keys */
DECL|macro|KT_LATIN
mdefine_line|#define KT_LATIN&t;0&t;/* we depend on this being zero */
DECL|macro|KT_LETTER
mdefine_line|#define KT_LETTER&t;11&t;/* symbol that can be acted upon by CapsLock */
DECL|macro|KT_FN
mdefine_line|#define KT_FN&t;&t;1
DECL|macro|KT_SPEC
mdefine_line|#define KT_SPEC&t;&t;2
DECL|macro|KT_PAD
mdefine_line|#define KT_PAD&t;&t;3
DECL|macro|KT_DEAD
mdefine_line|#define KT_DEAD&t;&t;4
DECL|macro|KT_CONS
mdefine_line|#define KT_CONS&t;&t;5
DECL|macro|KT_CUR
mdefine_line|#define KT_CUR&t;&t;6
DECL|macro|KT_SHIFT
mdefine_line|#define KT_SHIFT&t;7
DECL|macro|KT_META
mdefine_line|#define KT_META&t;&t;8
DECL|macro|KT_ASCII
mdefine_line|#define KT_ASCII&t;9
DECL|macro|KT_LOCK
mdefine_line|#define KT_LOCK&t;&t;10
DECL|macro|KT_SLOCK
mdefine_line|#define KT_SLOCK&t;12
DECL|macro|K
mdefine_line|#define K(t,v)&t;&t;(((t)&lt;&lt;8)|(v))
DECL|macro|KTYP
mdefine_line|#define KTYP(x)&t;&t;((x) &gt;&gt; 8)
DECL|macro|KVAL
mdefine_line|#define KVAL(x)&t;&t;((x) &amp; 0xff)
DECL|macro|K_F1
mdefine_line|#define K_F1&t;&t;K(KT_FN,0)
DECL|macro|K_F2
mdefine_line|#define K_F2&t;&t;K(KT_FN,1)
DECL|macro|K_F3
mdefine_line|#define K_F3&t;&t;K(KT_FN,2)
DECL|macro|K_F4
mdefine_line|#define K_F4&t;&t;K(KT_FN,3)
DECL|macro|K_F5
mdefine_line|#define K_F5&t;&t;K(KT_FN,4)
DECL|macro|K_F6
mdefine_line|#define K_F6&t;&t;K(KT_FN,5)
DECL|macro|K_F7
mdefine_line|#define K_F7&t;&t;K(KT_FN,6)
DECL|macro|K_F8
mdefine_line|#define K_F8&t;&t;K(KT_FN,7)
DECL|macro|K_F9
mdefine_line|#define K_F9&t;&t;K(KT_FN,8)
DECL|macro|K_F10
mdefine_line|#define K_F10&t;&t;K(KT_FN,9)
DECL|macro|K_F11
mdefine_line|#define K_F11&t;&t;K(KT_FN,10)
DECL|macro|K_F12
mdefine_line|#define K_F12&t;&t;K(KT_FN,11)
DECL|macro|K_F13
mdefine_line|#define K_F13&t;&t;K(KT_FN,12)
DECL|macro|K_F14
mdefine_line|#define K_F14&t;&t;K(KT_FN,13)
DECL|macro|K_F15
mdefine_line|#define K_F15&t;&t;K(KT_FN,14)
DECL|macro|K_F16
mdefine_line|#define K_F16&t;&t;K(KT_FN,15)
DECL|macro|K_F17
mdefine_line|#define K_F17&t;&t;K(KT_FN,16)
DECL|macro|K_F18
mdefine_line|#define K_F18&t;&t;K(KT_FN,17)
DECL|macro|K_F19
mdefine_line|#define K_F19&t;&t;K(KT_FN,18)
DECL|macro|K_F20
mdefine_line|#define K_F20&t;&t;K(KT_FN,19)
DECL|macro|K_FIND
mdefine_line|#define K_FIND&t;&t;K(KT_FN,20)
DECL|macro|K_INSERT
mdefine_line|#define K_INSERT&t;K(KT_FN,21)
DECL|macro|K_REMOVE
mdefine_line|#define K_REMOVE&t;K(KT_FN,22)
DECL|macro|K_SELECT
mdefine_line|#define K_SELECT&t;K(KT_FN,23)
DECL|macro|K_PGUP
mdefine_line|#define K_PGUP&t;&t;K(KT_FN,24) /* PGUP is a synonym for PRIOR */
DECL|macro|K_PGDN
mdefine_line|#define K_PGDN&t;&t;K(KT_FN,25) /* PGDN is a synonym for NEXT */
DECL|macro|K_MACRO
mdefine_line|#define K_MACRO&t; &t;K(KT_FN,26)
DECL|macro|K_HELP
mdefine_line|#define K_HELP&t;&t;K(KT_FN,27)
DECL|macro|K_DO
mdefine_line|#define K_DO&t;&t;K(KT_FN,28)
DECL|macro|K_PAUSE
mdefine_line|#define K_PAUSE&t; &t;K(KT_FN,29)
DECL|macro|K_F21
mdefine_line|#define K_F21&t;&t;K(KT_FN,30)
DECL|macro|K_F22
mdefine_line|#define K_F22&t;&t;K(KT_FN,31)
DECL|macro|K_F23
mdefine_line|#define K_F23&t;&t;K(KT_FN,32)
DECL|macro|K_F24
mdefine_line|#define K_F24&t;&t;K(KT_FN,33)
DECL|macro|K_F25
mdefine_line|#define K_F25&t;&t;K(KT_FN,34)
DECL|macro|K_F26
mdefine_line|#define K_F26&t;&t;K(KT_FN,35)
DECL|macro|K_F27
mdefine_line|#define K_F27&t;&t;K(KT_FN,36)
DECL|macro|K_F28
mdefine_line|#define K_F28&t;&t;K(KT_FN,37)
DECL|macro|K_F29
mdefine_line|#define K_F29&t;&t;K(KT_FN,38)
DECL|macro|K_F30
mdefine_line|#define K_F30&t;&t;K(KT_FN,39)
DECL|macro|K_F31
mdefine_line|#define K_F31&t;&t;K(KT_FN,40)
DECL|macro|K_F32
mdefine_line|#define K_F32&t;&t;K(KT_FN,41)
DECL|macro|K_F33
mdefine_line|#define K_F33&t;&t;K(KT_FN,42)
DECL|macro|K_F34
mdefine_line|#define K_F34&t;&t;K(KT_FN,43)
DECL|macro|K_F35
mdefine_line|#define K_F35&t;&t;K(KT_FN,44)
DECL|macro|K_F36
mdefine_line|#define K_F36&t;&t;K(KT_FN,45)
DECL|macro|K_F37
mdefine_line|#define K_F37&t;&t;K(KT_FN,46)
DECL|macro|K_F38
mdefine_line|#define K_F38&t;&t;K(KT_FN,47)
DECL|macro|K_F39
mdefine_line|#define K_F39&t;&t;K(KT_FN,48)
DECL|macro|K_F40
mdefine_line|#define K_F40&t;&t;K(KT_FN,49)
DECL|macro|K_F41
mdefine_line|#define K_F41&t;&t;K(KT_FN,50)
DECL|macro|K_F42
mdefine_line|#define K_F42&t;&t;K(KT_FN,51)
DECL|macro|K_F43
mdefine_line|#define K_F43&t;&t;K(KT_FN,52)
DECL|macro|K_F44
mdefine_line|#define K_F44&t;&t;K(KT_FN,53)
DECL|macro|K_F45
mdefine_line|#define K_F45&t;&t;K(KT_FN,54)
DECL|macro|K_F46
mdefine_line|#define K_F46&t;&t;K(KT_FN,55)
DECL|macro|K_F47
mdefine_line|#define K_F47&t;&t;K(KT_FN,56)
DECL|macro|K_F48
mdefine_line|#define K_F48&t;&t;K(KT_FN,57)
DECL|macro|K_F49
mdefine_line|#define K_F49&t;&t;K(KT_FN,58)
DECL|macro|K_F50
mdefine_line|#define K_F50&t;&t;K(KT_FN,59)
DECL|macro|K_F51
mdefine_line|#define K_F51&t;&t;K(KT_FN,60)
DECL|macro|K_F52
mdefine_line|#define K_F52&t;&t;K(KT_FN,61)
DECL|macro|K_F53
mdefine_line|#define K_F53&t;&t;K(KT_FN,62)
DECL|macro|K_F54
mdefine_line|#define K_F54&t;&t;K(KT_FN,63)
DECL|macro|K_F55
mdefine_line|#define K_F55&t;&t;K(KT_FN,64)
DECL|macro|K_F56
mdefine_line|#define K_F56&t;&t;K(KT_FN,65)
DECL|macro|K_F57
mdefine_line|#define K_F57&t;&t;K(KT_FN,66)
DECL|macro|K_F58
mdefine_line|#define K_F58&t;&t;K(KT_FN,67)
DECL|macro|K_F59
mdefine_line|#define K_F59&t;&t;K(KT_FN,68)
DECL|macro|K_F60
mdefine_line|#define K_F60&t;&t;K(KT_FN,69)
DECL|macro|K_F61
mdefine_line|#define K_F61&t;&t;K(KT_FN,70)
DECL|macro|K_F62
mdefine_line|#define K_F62&t;&t;K(KT_FN,71)
DECL|macro|K_F63
mdefine_line|#define K_F63&t;&t;K(KT_FN,72)
DECL|macro|K_F64
mdefine_line|#define K_F64&t;&t;K(KT_FN,73)
DECL|macro|K_F65
mdefine_line|#define K_F65&t;&t;K(KT_FN,74)
DECL|macro|K_F66
mdefine_line|#define K_F66&t;&t;K(KT_FN,75)
DECL|macro|K_F67
mdefine_line|#define K_F67&t;&t;K(KT_FN,76)
DECL|macro|K_F68
mdefine_line|#define K_F68&t;&t;K(KT_FN,77)
DECL|macro|K_F69
mdefine_line|#define K_F69&t;&t;K(KT_FN,78)
DECL|macro|K_F70
mdefine_line|#define K_F70&t;&t;K(KT_FN,79)
DECL|macro|K_F71
mdefine_line|#define K_F71&t;&t;K(KT_FN,80)
DECL|macro|K_F72
mdefine_line|#define K_F72&t;&t;K(KT_FN,81)
DECL|macro|K_F73
mdefine_line|#define K_F73&t;&t;K(KT_FN,82)
DECL|macro|K_F74
mdefine_line|#define K_F74&t;&t;K(KT_FN,83)
DECL|macro|K_F75
mdefine_line|#define K_F75&t;&t;K(KT_FN,84)
DECL|macro|K_F76
mdefine_line|#define K_F76&t;&t;K(KT_FN,85)
DECL|macro|K_F77
mdefine_line|#define K_F77&t;&t;K(KT_FN,86)
DECL|macro|K_F78
mdefine_line|#define K_F78&t;&t;K(KT_FN,87)
DECL|macro|K_F79
mdefine_line|#define K_F79&t;&t;K(KT_FN,88)
DECL|macro|K_F80
mdefine_line|#define K_F80&t;&t;K(KT_FN,89)
DECL|macro|K_F81
mdefine_line|#define K_F81&t;&t;K(KT_FN,90)
DECL|macro|K_F82
mdefine_line|#define K_F82&t;&t;K(KT_FN,91)
DECL|macro|K_F83
mdefine_line|#define K_F83&t;&t;K(KT_FN,92)
DECL|macro|K_F84
mdefine_line|#define K_F84&t;&t;K(KT_FN,93)
DECL|macro|K_F85
mdefine_line|#define K_F85&t;&t;K(KT_FN,94)
DECL|macro|K_F86
mdefine_line|#define K_F86&t;&t;K(KT_FN,95)
DECL|macro|K_F87
mdefine_line|#define K_F87&t;&t;K(KT_FN,96)
DECL|macro|K_F88
mdefine_line|#define K_F88&t;&t;K(KT_FN,97)
DECL|macro|K_F89
mdefine_line|#define K_F89&t;&t;K(KT_FN,98)
DECL|macro|K_F90
mdefine_line|#define K_F90&t;&t;K(KT_FN,99)
DECL|macro|K_F91
mdefine_line|#define K_F91&t;&t;K(KT_FN,100)
DECL|macro|K_F92
mdefine_line|#define K_F92&t;&t;K(KT_FN,101)
DECL|macro|K_F93
mdefine_line|#define K_F93&t;&t;K(KT_FN,102)
DECL|macro|K_F94
mdefine_line|#define K_F94&t;&t;K(KT_FN,103)
DECL|macro|K_F95
mdefine_line|#define K_F95&t;&t;K(KT_FN,104)
DECL|macro|K_F96
mdefine_line|#define K_F96&t;&t;K(KT_FN,105)
DECL|macro|K_F97
mdefine_line|#define K_F97&t;&t;K(KT_FN,106)
DECL|macro|K_F98
mdefine_line|#define K_F98&t;&t;K(KT_FN,107)
DECL|macro|K_F99
mdefine_line|#define K_F99&t;&t;K(KT_FN,108)
DECL|macro|K_F100
mdefine_line|#define K_F100&t;&t;K(KT_FN,109)
DECL|macro|K_F101
mdefine_line|#define K_F101&t;&t;K(KT_FN,110)
DECL|macro|K_F102
mdefine_line|#define K_F102&t;&t;K(KT_FN,111)
DECL|macro|K_F103
mdefine_line|#define K_F103&t;&t;K(KT_FN,112)
DECL|macro|K_F104
mdefine_line|#define K_F104&t;&t;K(KT_FN,113)
DECL|macro|K_F105
mdefine_line|#define K_F105&t;&t;K(KT_FN,114)
DECL|macro|K_F106
mdefine_line|#define K_F106&t;&t;K(KT_FN,115)
DECL|macro|K_F107
mdefine_line|#define K_F107&t;&t;K(KT_FN,116)
DECL|macro|K_F108
mdefine_line|#define K_F108&t;&t;K(KT_FN,117)
DECL|macro|K_F109
mdefine_line|#define K_F109&t;&t;K(KT_FN,118)
DECL|macro|K_F110
mdefine_line|#define K_F110&t;&t;K(KT_FN,119)
DECL|macro|K_F111
mdefine_line|#define K_F111&t;&t;K(KT_FN,120)
DECL|macro|K_F112
mdefine_line|#define K_F112&t;&t;K(KT_FN,121)
DECL|macro|K_F113
mdefine_line|#define K_F113&t;&t;K(KT_FN,122)
DECL|macro|K_F114
mdefine_line|#define K_F114&t;&t;K(KT_FN,123)
DECL|macro|K_F115
mdefine_line|#define K_F115&t;&t;K(KT_FN,124)
DECL|macro|K_F116
mdefine_line|#define K_F116&t;&t;K(KT_FN,125)
DECL|macro|K_F117
mdefine_line|#define K_F117&t;&t;K(KT_FN,126)
DECL|macro|K_F118
mdefine_line|#define K_F118&t;&t;K(KT_FN,127)
DECL|macro|K_F119
mdefine_line|#define K_F119&t;&t;K(KT_FN,128)
DECL|macro|K_F120
mdefine_line|#define K_F120&t;&t;K(KT_FN,129)
DECL|macro|K_F121
mdefine_line|#define K_F121&t;&t;K(KT_FN,130)
DECL|macro|K_F122
mdefine_line|#define K_F122&t;&t;K(KT_FN,131)
DECL|macro|K_F123
mdefine_line|#define K_F123&t;&t;K(KT_FN,132)
DECL|macro|K_F124
mdefine_line|#define K_F124&t;&t;K(KT_FN,133)
DECL|macro|K_F125
mdefine_line|#define K_F125&t;&t;K(KT_FN,134)
DECL|macro|K_F126
mdefine_line|#define K_F126&t;&t;K(KT_FN,135)
DECL|macro|K_F127
mdefine_line|#define K_F127&t;&t;K(KT_FN,136)
DECL|macro|K_F128
mdefine_line|#define K_F128&t;&t;K(KT_FN,137)
DECL|macro|K_F129
mdefine_line|#define K_F129&t;&t;K(KT_FN,138)
DECL|macro|K_F130
mdefine_line|#define K_F130&t;&t;K(KT_FN,139)
DECL|macro|K_F131
mdefine_line|#define K_F131&t;&t;K(KT_FN,140)
DECL|macro|K_F132
mdefine_line|#define K_F132&t;&t;K(KT_FN,141)
DECL|macro|K_F133
mdefine_line|#define K_F133&t;&t;K(KT_FN,142)
DECL|macro|K_F134
mdefine_line|#define K_F134&t;&t;K(KT_FN,143)
DECL|macro|K_F135
mdefine_line|#define K_F135&t;&t;K(KT_FN,144)
DECL|macro|K_F136
mdefine_line|#define K_F136&t;&t;K(KT_FN,145)
DECL|macro|K_F137
mdefine_line|#define K_F137&t;&t;K(KT_FN,146)
DECL|macro|K_F138
mdefine_line|#define K_F138&t;&t;K(KT_FN,147)
DECL|macro|K_F139
mdefine_line|#define K_F139&t;&t;K(KT_FN,148)
DECL|macro|K_F140
mdefine_line|#define K_F140&t;&t;K(KT_FN,149)
DECL|macro|K_F141
mdefine_line|#define K_F141&t;&t;K(KT_FN,150)
DECL|macro|K_F142
mdefine_line|#define K_F142&t;&t;K(KT_FN,151)
DECL|macro|K_F143
mdefine_line|#define K_F143&t;&t;K(KT_FN,152)
DECL|macro|K_F144
mdefine_line|#define K_F144&t;&t;K(KT_FN,153)
DECL|macro|K_F145
mdefine_line|#define K_F145&t;&t;K(KT_FN,154)
DECL|macro|K_F146
mdefine_line|#define K_F146&t;&t;K(KT_FN,155)
DECL|macro|K_F147
mdefine_line|#define K_F147&t;&t;K(KT_FN,156)
DECL|macro|K_F148
mdefine_line|#define K_F148&t;&t;K(KT_FN,157)
DECL|macro|K_F149
mdefine_line|#define K_F149&t;&t;K(KT_FN,158)
DECL|macro|K_F150
mdefine_line|#define K_F150&t;&t;K(KT_FN,159)
DECL|macro|K_F151
mdefine_line|#define K_F151&t;&t;K(KT_FN,160)
DECL|macro|K_F152
mdefine_line|#define K_F152&t;&t;K(KT_FN,161)
DECL|macro|K_F153
mdefine_line|#define K_F153&t;&t;K(KT_FN,162)
DECL|macro|K_F154
mdefine_line|#define K_F154&t;&t;K(KT_FN,163)
DECL|macro|K_F155
mdefine_line|#define K_F155&t;&t;K(KT_FN,164)
DECL|macro|K_F156
mdefine_line|#define K_F156&t;&t;K(KT_FN,165)
DECL|macro|K_F157
mdefine_line|#define K_F157&t;&t;K(KT_FN,166)
DECL|macro|K_F158
mdefine_line|#define K_F158&t;&t;K(KT_FN,167)
DECL|macro|K_F159
mdefine_line|#define K_F159&t;&t;K(KT_FN,168)
DECL|macro|K_F160
mdefine_line|#define K_F160&t;&t;K(KT_FN,169)
DECL|macro|K_F161
mdefine_line|#define K_F161&t;&t;K(KT_FN,170)
DECL|macro|K_F162
mdefine_line|#define K_F162&t;&t;K(KT_FN,171)
DECL|macro|K_F163
mdefine_line|#define K_F163&t;&t;K(KT_FN,172)
DECL|macro|K_F164
mdefine_line|#define K_F164&t;&t;K(KT_FN,173)
DECL|macro|K_F165
mdefine_line|#define K_F165&t;&t;K(KT_FN,174)
DECL|macro|K_F166
mdefine_line|#define K_F166&t;&t;K(KT_FN,175)
DECL|macro|K_F167
mdefine_line|#define K_F167&t;&t;K(KT_FN,176)
DECL|macro|K_F168
mdefine_line|#define K_F168&t;&t;K(KT_FN,177)
DECL|macro|K_F169
mdefine_line|#define K_F169&t;&t;K(KT_FN,178)
DECL|macro|K_F170
mdefine_line|#define K_F170&t;&t;K(KT_FN,179)
DECL|macro|K_F171
mdefine_line|#define K_F171&t;&t;K(KT_FN,180)
DECL|macro|K_F172
mdefine_line|#define K_F172&t;&t;K(KT_FN,181)
DECL|macro|K_F173
mdefine_line|#define K_F173&t;&t;K(KT_FN,182)
DECL|macro|K_F174
mdefine_line|#define K_F174&t;&t;K(KT_FN,183)
DECL|macro|K_F175
mdefine_line|#define K_F175&t;&t;K(KT_FN,184)
DECL|macro|K_F176
mdefine_line|#define K_F176&t;&t;K(KT_FN,185)
DECL|macro|K_F177
mdefine_line|#define K_F177&t;&t;K(KT_FN,186)
DECL|macro|K_F178
mdefine_line|#define K_F178&t;&t;K(KT_FN,187)
DECL|macro|K_F179
mdefine_line|#define K_F179&t;&t;K(KT_FN,188)
DECL|macro|K_F180
mdefine_line|#define K_F180&t;&t;K(KT_FN,189)
DECL|macro|K_F181
mdefine_line|#define K_F181&t;&t;K(KT_FN,190)
DECL|macro|K_F182
mdefine_line|#define K_F182&t;&t;K(KT_FN,191)
DECL|macro|K_F183
mdefine_line|#define K_F183&t;&t;K(KT_FN,192)
DECL|macro|K_F184
mdefine_line|#define K_F184&t;&t;K(KT_FN,193)
DECL|macro|K_F185
mdefine_line|#define K_F185&t;&t;K(KT_FN,194)
DECL|macro|K_F186
mdefine_line|#define K_F186&t;&t;K(KT_FN,195)
DECL|macro|K_F187
mdefine_line|#define K_F187&t;&t;K(KT_FN,196)
DECL|macro|K_F188
mdefine_line|#define K_F188&t;&t;K(KT_FN,197)
DECL|macro|K_F189
mdefine_line|#define K_F189&t;&t;K(KT_FN,198)
DECL|macro|K_F190
mdefine_line|#define K_F190&t;&t;K(KT_FN,199)
DECL|macro|K_F191
mdefine_line|#define K_F191&t;&t;K(KT_FN,200)
DECL|macro|K_F192
mdefine_line|#define K_F192&t;&t;K(KT_FN,201)
DECL|macro|K_F193
mdefine_line|#define K_F193&t;&t;K(KT_FN,202)
DECL|macro|K_F194
mdefine_line|#define K_F194&t;&t;K(KT_FN,203)
DECL|macro|K_F195
mdefine_line|#define K_F195&t;&t;K(KT_FN,204)
DECL|macro|K_F196
mdefine_line|#define K_F196&t;&t;K(KT_FN,205)
DECL|macro|K_F197
mdefine_line|#define K_F197&t;&t;K(KT_FN,206)
DECL|macro|K_F198
mdefine_line|#define K_F198&t;&t;K(KT_FN,207)
DECL|macro|K_F199
mdefine_line|#define K_F199&t;&t;K(KT_FN,208)
DECL|macro|K_F200
mdefine_line|#define K_F200&t;&t;K(KT_FN,209)
DECL|macro|K_F201
mdefine_line|#define K_F201&t;&t;K(KT_FN,210)
DECL|macro|K_F202
mdefine_line|#define K_F202&t;&t;K(KT_FN,211)
DECL|macro|K_F203
mdefine_line|#define K_F203&t;&t;K(KT_FN,212)
DECL|macro|K_F204
mdefine_line|#define K_F204&t;&t;K(KT_FN,213)
DECL|macro|K_F205
mdefine_line|#define K_F205&t;&t;K(KT_FN,214)
DECL|macro|K_F206
mdefine_line|#define K_F206&t;&t;K(KT_FN,215)
DECL|macro|K_F207
mdefine_line|#define K_F207&t;&t;K(KT_FN,216)
DECL|macro|K_F208
mdefine_line|#define K_F208&t;&t;K(KT_FN,217)
DECL|macro|K_F209
mdefine_line|#define K_F209&t;&t;K(KT_FN,218)
DECL|macro|K_F210
mdefine_line|#define K_F210&t;&t;K(KT_FN,219)
DECL|macro|K_F211
mdefine_line|#define K_F211&t;&t;K(KT_FN,220)
DECL|macro|K_F212
mdefine_line|#define K_F212&t;&t;K(KT_FN,221)
DECL|macro|K_F213
mdefine_line|#define K_F213&t;&t;K(KT_FN,222)
DECL|macro|K_F214
mdefine_line|#define K_F214&t;&t;K(KT_FN,223)
DECL|macro|K_F215
mdefine_line|#define K_F215&t;&t;K(KT_FN,224)
DECL|macro|K_F216
mdefine_line|#define K_F216&t;&t;K(KT_FN,225)
DECL|macro|K_F217
mdefine_line|#define K_F217&t;&t;K(KT_FN,226)
DECL|macro|K_F218
mdefine_line|#define K_F218&t;&t;K(KT_FN,227)
DECL|macro|K_F219
mdefine_line|#define K_F219&t;&t;K(KT_FN,228)
DECL|macro|K_F220
mdefine_line|#define K_F220&t;&t;K(KT_FN,229)
DECL|macro|K_F221
mdefine_line|#define K_F221&t;&t;K(KT_FN,230)
DECL|macro|K_F222
mdefine_line|#define K_F222&t;&t;K(KT_FN,231)
DECL|macro|K_F223
mdefine_line|#define K_F223&t;&t;K(KT_FN,232)
DECL|macro|K_F224
mdefine_line|#define K_F224&t;&t;K(KT_FN,233)
DECL|macro|K_F225
mdefine_line|#define K_F225&t;&t;K(KT_FN,234)
DECL|macro|K_F226
mdefine_line|#define K_F226&t;&t;K(KT_FN,235)
DECL|macro|K_F227
mdefine_line|#define K_F227&t;&t;K(KT_FN,236)
DECL|macro|K_F228
mdefine_line|#define K_F228&t;&t;K(KT_FN,237)
DECL|macro|K_F229
mdefine_line|#define K_F229&t;&t;K(KT_FN,238)
DECL|macro|K_F230
mdefine_line|#define K_F230&t;&t;K(KT_FN,239)
DECL|macro|K_F231
mdefine_line|#define K_F231&t;&t;K(KT_FN,240)
DECL|macro|K_F232
mdefine_line|#define K_F232&t;&t;K(KT_FN,241)
DECL|macro|K_F233
mdefine_line|#define K_F233&t;&t;K(KT_FN,242)
DECL|macro|K_F234
mdefine_line|#define K_F234&t;&t;K(KT_FN,243)
DECL|macro|K_F235
mdefine_line|#define K_F235&t;&t;K(KT_FN,244)
DECL|macro|K_F236
mdefine_line|#define K_F236&t;&t;K(KT_FN,245)
DECL|macro|K_F237
mdefine_line|#define K_F237&t;&t;K(KT_FN,246)
DECL|macro|K_F238
mdefine_line|#define K_F238&t;&t;K(KT_FN,247)
DECL|macro|K_F239
mdefine_line|#define K_F239&t;&t;K(KT_FN,248)
DECL|macro|K_F240
mdefine_line|#define K_F240&t;&t;K(KT_FN,249)
DECL|macro|K_F241
mdefine_line|#define K_F241&t;&t;K(KT_FN,250)
DECL|macro|K_F242
mdefine_line|#define K_F242&t;&t;K(KT_FN,251)
DECL|macro|K_F243
mdefine_line|#define K_F243&t;&t;K(KT_FN,252)
DECL|macro|K_F244
mdefine_line|#define K_F244&t;&t;K(KT_FN,253)
DECL|macro|K_F245
mdefine_line|#define K_F245&t;&t;K(KT_FN,254)
DECL|macro|K_UNDO
mdefine_line|#define K_UNDO&t;&t;K(KT_FN,255)
DECL|macro|K_HOLE
mdefine_line|#define K_HOLE&t;&t;K(KT_SPEC,0)
DECL|macro|K_ENTER
mdefine_line|#define K_ENTER&t;&t;K(KT_SPEC,1)
DECL|macro|K_SH_REGS
mdefine_line|#define K_SH_REGS&t;K(KT_SPEC,2)
DECL|macro|K_SH_MEM
mdefine_line|#define K_SH_MEM&t;K(KT_SPEC,3)
DECL|macro|K_SH_STAT
mdefine_line|#define K_SH_STAT&t;K(KT_SPEC,4)
DECL|macro|K_BREAK
mdefine_line|#define K_BREAK&t;&t;K(KT_SPEC,5)
DECL|macro|K_CONS
mdefine_line|#define K_CONS&t;&t;K(KT_SPEC,6)
DECL|macro|K_CAPS
mdefine_line|#define K_CAPS&t;&t;K(KT_SPEC,7)
DECL|macro|K_NUM
mdefine_line|#define K_NUM&t;&t;K(KT_SPEC,8)
DECL|macro|K_HOLD
mdefine_line|#define K_HOLD&t;&t;K(KT_SPEC,9)
DECL|macro|K_SCROLLFORW
mdefine_line|#define K_SCROLLFORW&t;K(KT_SPEC,10)
DECL|macro|K_SCROLLBACK
mdefine_line|#define K_SCROLLBACK&t;K(KT_SPEC,11)
DECL|macro|K_BOOT
mdefine_line|#define K_BOOT&t;&t;K(KT_SPEC,12)
DECL|macro|K_CAPSON
mdefine_line|#define K_CAPSON&t;K(KT_SPEC,13)
DECL|macro|K_COMPOSE
mdefine_line|#define K_COMPOSE&t;K(KT_SPEC,14)
DECL|macro|K_SAK
mdefine_line|#define K_SAK&t;&t;K(KT_SPEC,15)
DECL|macro|K_DECRCONSOLE
mdefine_line|#define K_DECRCONSOLE&t;K(KT_SPEC,16)
DECL|macro|K_INCRCONSOLE
mdefine_line|#define K_INCRCONSOLE&t;K(KT_SPEC,17)
DECL|macro|K_SPAWNCONSOLE
mdefine_line|#define K_SPAWNCONSOLE&t;K(KT_SPEC,18)
DECL|macro|K_BARENUMLOCK
mdefine_line|#define K_BARENUMLOCK&t;K(KT_SPEC,19)
DECL|macro|K_ALLOCATED
mdefine_line|#define K_ALLOCATED&t;K(KT_SPEC,126) /* dynamically allocated keymap */
DECL|macro|K_NOSUCHMAP
mdefine_line|#define K_NOSUCHMAP&t;K(KT_SPEC,127) /* returned by KDGKBENT */
DECL|macro|K_P0
mdefine_line|#define K_P0&t;&t;K(KT_PAD,0)
DECL|macro|K_P1
mdefine_line|#define K_P1&t;&t;K(KT_PAD,1)
DECL|macro|K_P2
mdefine_line|#define K_P2&t;&t;K(KT_PAD,2)
DECL|macro|K_P3
mdefine_line|#define K_P3&t;&t;K(KT_PAD,3)
DECL|macro|K_P4
mdefine_line|#define K_P4&t;&t;K(KT_PAD,4)
DECL|macro|K_P5
mdefine_line|#define K_P5&t;&t;K(KT_PAD,5)
DECL|macro|K_P6
mdefine_line|#define K_P6&t;&t;K(KT_PAD,6)
DECL|macro|K_P7
mdefine_line|#define K_P7&t;&t;K(KT_PAD,7)
DECL|macro|K_P8
mdefine_line|#define K_P8&t;&t;K(KT_PAD,8)
DECL|macro|K_P9
mdefine_line|#define K_P9&t;&t;K(KT_PAD,9)
DECL|macro|K_PPLUS
mdefine_line|#define K_PPLUS&t;&t;K(KT_PAD,10)&t;/* key-pad plus */
DECL|macro|K_PMINUS
mdefine_line|#define K_PMINUS&t;K(KT_PAD,11)&t;/* key-pad minus */
DECL|macro|K_PSTAR
mdefine_line|#define K_PSTAR&t;&t;K(KT_PAD,12)&t;/* key-pad asterisk (star) */
DECL|macro|K_PSLASH
mdefine_line|#define K_PSLASH&t;K(KT_PAD,13)&t;/* key-pad slash */
DECL|macro|K_PENTER
mdefine_line|#define K_PENTER&t;K(KT_PAD,14)&t;/* key-pad enter */
DECL|macro|K_PCOMMA
mdefine_line|#define K_PCOMMA&t;K(KT_PAD,15)&t;/* key-pad comma: kludge... */
DECL|macro|K_PDOT
mdefine_line|#define K_PDOT&t;&t;K(KT_PAD,16)&t;/* key-pad dot (period): kludge... */
DECL|macro|K_PPLUSMINUS
mdefine_line|#define K_PPLUSMINUS&t;K(KT_PAD,17)&t;/* key-pad plus/minus */
DECL|macro|K_PPARENL
mdefine_line|#define K_PPARENL&t;K(KT_PAD,18)&t;/* key-pad left parenthesis */
DECL|macro|K_PPARENR
mdefine_line|#define K_PPARENR&t;K(KT_PAD,19)&t;/* key-pad right parenthesis */
DECL|macro|NR_PAD
mdefine_line|#define NR_PAD&t;&t;20
DECL|macro|K_DGRAVE
mdefine_line|#define K_DGRAVE&t;K(KT_DEAD,0)
DECL|macro|K_DACUTE
mdefine_line|#define K_DACUTE&t;K(KT_DEAD,1)
DECL|macro|K_DCIRCM
mdefine_line|#define K_DCIRCM&t;K(KT_DEAD,2)
DECL|macro|K_DTILDE
mdefine_line|#define K_DTILDE&t;K(KT_DEAD,3)
DECL|macro|K_DDIERE
mdefine_line|#define K_DDIERE&t;K(KT_DEAD,4)
DECL|macro|K_DCEDIL
mdefine_line|#define K_DCEDIL&t;K(KT_DEAD,5)
DECL|macro|NR_DEAD
mdefine_line|#define NR_DEAD&t;&t;6
DECL|macro|K_DOWN
mdefine_line|#define K_DOWN&t;&t;K(KT_CUR,0)
DECL|macro|K_LEFT
mdefine_line|#define K_LEFT&t;&t;K(KT_CUR,1)
DECL|macro|K_RIGHT
mdefine_line|#define K_RIGHT&t;&t;K(KT_CUR,2)
DECL|macro|K_UP
mdefine_line|#define K_UP&t;&t;K(KT_CUR,3)
DECL|macro|K_SHIFT
mdefine_line|#define K_SHIFT&t;&t;K(KT_SHIFT,KG_SHIFT)
DECL|macro|K_CTRL
mdefine_line|#define K_CTRL&t;&t;K(KT_SHIFT,KG_CTRL)
DECL|macro|K_ALT
mdefine_line|#define K_ALT&t;&t;K(KT_SHIFT,KG_ALT)
DECL|macro|K_ALTGR
mdefine_line|#define K_ALTGR&t;&t;K(KT_SHIFT,KG_ALTGR)
DECL|macro|K_SHIFTL
mdefine_line|#define K_SHIFTL&t;K(KT_SHIFT,KG_SHIFTL)
DECL|macro|K_SHIFTR
mdefine_line|#define K_SHIFTR&t;K(KT_SHIFT,KG_SHIFTR)
DECL|macro|K_CTRLL
mdefine_line|#define K_CTRLL&t; &t;K(KT_SHIFT,KG_CTRLL)
DECL|macro|K_CTRLR
mdefine_line|#define K_CTRLR&t; &t;K(KT_SHIFT,KG_CTRLR)
DECL|macro|K_CAPSSHIFT
mdefine_line|#define K_CAPSSHIFT&t;K(KT_SHIFT,KG_CAPSSHIFT)
DECL|macro|K_ASC0
mdefine_line|#define K_ASC0&t;&t;K(KT_ASCII,0)
DECL|macro|K_ASC1
mdefine_line|#define K_ASC1&t;&t;K(KT_ASCII,1)
DECL|macro|K_ASC2
mdefine_line|#define K_ASC2&t;&t;K(KT_ASCII,2)
DECL|macro|K_ASC3
mdefine_line|#define K_ASC3&t;&t;K(KT_ASCII,3)
DECL|macro|K_ASC4
mdefine_line|#define K_ASC4&t;&t;K(KT_ASCII,4)
DECL|macro|K_ASC5
mdefine_line|#define K_ASC5&t;&t;K(KT_ASCII,5)
DECL|macro|K_ASC6
mdefine_line|#define K_ASC6&t;&t;K(KT_ASCII,6)
DECL|macro|K_ASC7
mdefine_line|#define K_ASC7&t;&t;K(KT_ASCII,7)
DECL|macro|K_ASC8
mdefine_line|#define K_ASC8&t;&t;K(KT_ASCII,8)
DECL|macro|K_ASC9
mdefine_line|#define K_ASC9&t;&t;K(KT_ASCII,9)
DECL|macro|K_HEX0
mdefine_line|#define K_HEX0&t;&t;K(KT_ASCII,10)
DECL|macro|K_HEX1
mdefine_line|#define K_HEX1&t;&t;K(KT_ASCII,11)
DECL|macro|K_HEX2
mdefine_line|#define K_HEX2&t;&t;K(KT_ASCII,12)
DECL|macro|K_HEX3
mdefine_line|#define K_HEX3&t;&t;K(KT_ASCII,13)
DECL|macro|K_HEX4
mdefine_line|#define K_HEX4&t;&t;K(KT_ASCII,14)
DECL|macro|K_HEX5
mdefine_line|#define K_HEX5&t;&t;K(KT_ASCII,15)
DECL|macro|K_HEX6
mdefine_line|#define K_HEX6&t;&t;K(KT_ASCII,16)
DECL|macro|K_HEX7
mdefine_line|#define K_HEX7&t;&t;K(KT_ASCII,17)
DECL|macro|K_HEX8
mdefine_line|#define K_HEX8&t;&t;K(KT_ASCII,18)
DECL|macro|K_HEX9
mdefine_line|#define K_HEX9&t;&t;K(KT_ASCII,19)
DECL|macro|K_HEXa
mdefine_line|#define K_HEXa&t;&t;K(KT_ASCII,20)
DECL|macro|K_HEXb
mdefine_line|#define K_HEXb&t;&t;K(KT_ASCII,21)
DECL|macro|K_HEXc
mdefine_line|#define K_HEXc&t;&t;K(KT_ASCII,22)
DECL|macro|K_HEXd
mdefine_line|#define K_HEXd&t;&t;K(KT_ASCII,23)
DECL|macro|K_HEXe
mdefine_line|#define K_HEXe&t;&t;K(KT_ASCII,24)
DECL|macro|K_HEXf
mdefine_line|#define K_HEXf&t;&t;K(KT_ASCII,25)
DECL|macro|NR_ASCII
mdefine_line|#define NR_ASCII&t;26
DECL|macro|K_SHIFTLOCK
mdefine_line|#define K_SHIFTLOCK&t;K(KT_LOCK,KG_SHIFT)
DECL|macro|K_CTRLLOCK
mdefine_line|#define K_CTRLLOCK&t;K(KT_LOCK,KG_CTRL)
DECL|macro|K_ALTLOCK
mdefine_line|#define K_ALTLOCK&t;K(KT_LOCK,KG_ALT)
DECL|macro|K_ALTGRLOCK
mdefine_line|#define K_ALTGRLOCK&t;K(KT_LOCK,KG_ALTGR)
DECL|macro|K_SHIFTLLOCK
mdefine_line|#define K_SHIFTLLOCK&t;K(KT_LOCK,KG_SHIFTL)
DECL|macro|K_SHIFTRLOCK
mdefine_line|#define K_SHIFTRLOCK&t;K(KT_LOCK,KG_SHIFTR)
DECL|macro|K_CTRLLLOCK
mdefine_line|#define K_CTRLLLOCK&t;K(KT_LOCK,KG_CTRLL)
DECL|macro|K_CTRLRLOCK
mdefine_line|#define K_CTRLRLOCK&t;K(KT_LOCK,KG_CTRLR)
DECL|macro|K_SHIFT_SLOCK
mdefine_line|#define K_SHIFT_SLOCK&t;K(KT_SLOCK,KG_SHIFT)
DECL|macro|K_CTRL_SLOCK
mdefine_line|#define K_CTRL_SLOCK&t;K(KT_SLOCK,KG_CTRL)
DECL|macro|K_ALT_SLOCK
mdefine_line|#define K_ALT_SLOCK&t;K(KT_SLOCK,KG_ALT)
DECL|macro|K_ALTGR_SLOCK
mdefine_line|#define K_ALTGR_SLOCK&t;K(KT_SLOCK,KG_ALTGR)
DECL|macro|K_SHIFTL_SLOCK
mdefine_line|#define K_SHIFTL_SLOCK&t;K(KT_SLOCK,KG_SHIFTL)
DECL|macro|K_SHIFTR_SLOCK
mdefine_line|#define K_SHIFTR_SLOCK&t;K(KT_SLOCK,KG_SHIFTR)
DECL|macro|K_CTRLL_SLOCK
mdefine_line|#define K_CTRLL_SLOCK&t;K(KT_SLOCK,KG_CTRLL)
DECL|macro|K_CTRLR_SLOCK
mdefine_line|#define K_CTRLR_SLOCK&t;K(KT_SLOCK,KG_CTRLR)
DECL|macro|NR_LOCK
mdefine_line|#define NR_LOCK&t;&t;8
DECL|macro|MAX_DIACR
mdefine_line|#define MAX_DIACR&t;256
macro_line|#endif
eof
