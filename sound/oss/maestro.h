multiline_comment|/*&n; *&t;Registers for the ESS PCI cards&n; */
multiline_comment|/*&n; *&t;Memory access&n; */
DECL|macro|ESS_MEM_DATA
mdefine_line|#define ESS_MEM_DATA&t;&t;0x00
DECL|macro|ESS_MEM_INDEX
mdefine_line|#define&t;ESS_MEM_INDEX&t;&t;0x02
multiline_comment|/*&n; *&t;AC-97 Codec port. Delay 1uS after each write. This is used to&n; *&t;talk AC-97 (see intel.com). Write data then register.&n; */
DECL|macro|ESS_AC97_INDEX
mdefine_line|#define ESS_AC97_INDEX&t;&t;0x30&t;&t;/* byte wide */
DECL|macro|ESS_AC97_DATA
mdefine_line|#define ESS_AC97_DATA&t;&t;0x32
multiline_comment|/* &n; *&t;Reading is a bit different. You write register|0x80 to ubdex&n; *&t;delay 1uS poll the low bit of index, when it clears read the&n; *&t;data value.&n; */
multiline_comment|/*&n; *&t;Control port. Not yet fully understood&n; *&t;The value 0xC090 gets loaded to it then 0x0000 and 0x2800&n; *&t;to the data port. Then after 4uS the value 0x300 is written&n; */
DECL|macro|RING_BUS_CTRL_L
mdefine_line|#define RING_BUS_CTRL_L&t;&t;0x34
DECL|macro|RING_BUS_CTRL_H
mdefine_line|#define RING_BUS_CTRL_H&t;&t;0x36
multiline_comment|/*&n; *&t;This is also used during setup. The value 0x17 is written to it&n; */
DECL|macro|ESS_SETUP_18
mdefine_line|#define ESS_SETUP_18&t;&t;0x18
multiline_comment|/*&n; *&t;And this one gets 0x000b&n; */
DECL|macro|ESS_SETUP_A2
mdefine_line|#define ESS_SETUP_A2&t;&t;0xA2
multiline_comment|/*&n; *&t;And this 0x0000&n; */
DECL|macro|ESS_SETUP_A4
mdefine_line|#define ESS_SETUP_A4&t;&t;0xA4
DECL|macro|ESS_SETUP_A6
mdefine_line|#define ESS_SETUP_A6&t;&t;0xA6
multiline_comment|/*&n; *&t;Stuff to do with Harpo - the wave stuff&n; */
DECL|macro|ESS_WAVETABLE_SIZE
mdefine_line|#define ESS_WAVETABLE_SIZE&t;0x14
DECL|macro|ESS_WAVETABLE_2M
mdefine_line|#define &t;ESS_WAVETABLE_2M&t;0xA180
eof
