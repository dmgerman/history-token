multiline_comment|/*&n; *  colors.h -- color attribute definitions&n; *&n; *  AUTHOR: Savio Lam (lam836@cs.cuhk.hk)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version 2&n; *  of the License, or (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; *   Default color definitions&n; *&n; *   *_FG = foreground&n; *   *_BG = background&n; *   *_HL = highlight?&n; */
DECL|macro|SCREEN_FG
mdefine_line|#define SCREEN_FG                    COLOR_CYAN
DECL|macro|SCREEN_BG
mdefine_line|#define SCREEN_BG                    COLOR_BLUE
DECL|macro|SCREEN_HL
mdefine_line|#define SCREEN_HL                    TRUE
DECL|macro|SHADOW_FG
mdefine_line|#define SHADOW_FG                    COLOR_BLACK
DECL|macro|SHADOW_BG
mdefine_line|#define SHADOW_BG                    COLOR_BLACK
DECL|macro|SHADOW_HL
mdefine_line|#define SHADOW_HL                    TRUE
DECL|macro|DIALOG_FG
mdefine_line|#define DIALOG_FG                    COLOR_BLACK
DECL|macro|DIALOG_BG
mdefine_line|#define DIALOG_BG                    COLOR_WHITE
DECL|macro|DIALOG_HL
mdefine_line|#define DIALOG_HL                    FALSE
DECL|macro|TITLE_FG
mdefine_line|#define TITLE_FG                     COLOR_YELLOW
DECL|macro|TITLE_BG
mdefine_line|#define TITLE_BG                     COLOR_WHITE
DECL|macro|TITLE_HL
mdefine_line|#define TITLE_HL                     TRUE
DECL|macro|BORDER_FG
mdefine_line|#define BORDER_FG                    COLOR_WHITE
DECL|macro|BORDER_BG
mdefine_line|#define BORDER_BG                    COLOR_WHITE
DECL|macro|BORDER_HL
mdefine_line|#define BORDER_HL                    TRUE
DECL|macro|BUTTON_ACTIVE_FG
mdefine_line|#define BUTTON_ACTIVE_FG             COLOR_WHITE
DECL|macro|BUTTON_ACTIVE_BG
mdefine_line|#define BUTTON_ACTIVE_BG             COLOR_BLUE
DECL|macro|BUTTON_ACTIVE_HL
mdefine_line|#define BUTTON_ACTIVE_HL             TRUE
DECL|macro|BUTTON_INACTIVE_FG
mdefine_line|#define BUTTON_INACTIVE_FG           COLOR_BLACK
DECL|macro|BUTTON_INACTIVE_BG
mdefine_line|#define BUTTON_INACTIVE_BG           COLOR_WHITE
DECL|macro|BUTTON_INACTIVE_HL
mdefine_line|#define BUTTON_INACTIVE_HL           FALSE
DECL|macro|BUTTON_KEY_ACTIVE_FG
mdefine_line|#define BUTTON_KEY_ACTIVE_FG         COLOR_WHITE
DECL|macro|BUTTON_KEY_ACTIVE_BG
mdefine_line|#define BUTTON_KEY_ACTIVE_BG         COLOR_BLUE
DECL|macro|BUTTON_KEY_ACTIVE_HL
mdefine_line|#define BUTTON_KEY_ACTIVE_HL         TRUE
DECL|macro|BUTTON_KEY_INACTIVE_FG
mdefine_line|#define BUTTON_KEY_INACTIVE_FG       COLOR_RED
DECL|macro|BUTTON_KEY_INACTIVE_BG
mdefine_line|#define BUTTON_KEY_INACTIVE_BG       COLOR_WHITE
DECL|macro|BUTTON_KEY_INACTIVE_HL
mdefine_line|#define BUTTON_KEY_INACTIVE_HL       FALSE
DECL|macro|BUTTON_LABEL_ACTIVE_FG
mdefine_line|#define BUTTON_LABEL_ACTIVE_FG       COLOR_YELLOW
DECL|macro|BUTTON_LABEL_ACTIVE_BG
mdefine_line|#define BUTTON_LABEL_ACTIVE_BG       COLOR_BLUE
DECL|macro|BUTTON_LABEL_ACTIVE_HL
mdefine_line|#define BUTTON_LABEL_ACTIVE_HL       TRUE
DECL|macro|BUTTON_LABEL_INACTIVE_FG
mdefine_line|#define BUTTON_LABEL_INACTIVE_FG     COLOR_BLACK
DECL|macro|BUTTON_LABEL_INACTIVE_BG
mdefine_line|#define BUTTON_LABEL_INACTIVE_BG     COLOR_WHITE
DECL|macro|BUTTON_LABEL_INACTIVE_HL
mdefine_line|#define BUTTON_LABEL_INACTIVE_HL     TRUE
DECL|macro|INPUTBOX_FG
mdefine_line|#define INPUTBOX_FG                  COLOR_BLACK
DECL|macro|INPUTBOX_BG
mdefine_line|#define INPUTBOX_BG                  COLOR_WHITE
DECL|macro|INPUTBOX_HL
mdefine_line|#define INPUTBOX_HL                  FALSE
DECL|macro|INPUTBOX_BORDER_FG
mdefine_line|#define INPUTBOX_BORDER_FG           COLOR_BLACK
DECL|macro|INPUTBOX_BORDER_BG
mdefine_line|#define INPUTBOX_BORDER_BG           COLOR_WHITE
DECL|macro|INPUTBOX_BORDER_HL
mdefine_line|#define INPUTBOX_BORDER_HL           FALSE
DECL|macro|SEARCHBOX_FG
mdefine_line|#define SEARCHBOX_FG                 COLOR_BLACK
DECL|macro|SEARCHBOX_BG
mdefine_line|#define SEARCHBOX_BG                 COLOR_WHITE
DECL|macro|SEARCHBOX_HL
mdefine_line|#define SEARCHBOX_HL                 FALSE
DECL|macro|SEARCHBOX_TITLE_FG
mdefine_line|#define SEARCHBOX_TITLE_FG           COLOR_YELLOW
DECL|macro|SEARCHBOX_TITLE_BG
mdefine_line|#define SEARCHBOX_TITLE_BG           COLOR_WHITE
DECL|macro|SEARCHBOX_TITLE_HL
mdefine_line|#define SEARCHBOX_TITLE_HL           TRUE
DECL|macro|SEARCHBOX_BORDER_FG
mdefine_line|#define SEARCHBOX_BORDER_FG          COLOR_WHITE
DECL|macro|SEARCHBOX_BORDER_BG
mdefine_line|#define SEARCHBOX_BORDER_BG          COLOR_WHITE
DECL|macro|SEARCHBOX_BORDER_HL
mdefine_line|#define SEARCHBOX_BORDER_HL          TRUE
DECL|macro|POSITION_INDICATOR_FG
mdefine_line|#define POSITION_INDICATOR_FG        COLOR_YELLOW
DECL|macro|POSITION_INDICATOR_BG
mdefine_line|#define POSITION_INDICATOR_BG        COLOR_WHITE
DECL|macro|POSITION_INDICATOR_HL
mdefine_line|#define POSITION_INDICATOR_HL        TRUE
DECL|macro|MENUBOX_FG
mdefine_line|#define MENUBOX_FG                   COLOR_BLACK
DECL|macro|MENUBOX_BG
mdefine_line|#define MENUBOX_BG                   COLOR_WHITE
DECL|macro|MENUBOX_HL
mdefine_line|#define MENUBOX_HL                   FALSE
DECL|macro|MENUBOX_BORDER_FG
mdefine_line|#define MENUBOX_BORDER_FG            COLOR_WHITE
DECL|macro|MENUBOX_BORDER_BG
mdefine_line|#define MENUBOX_BORDER_BG            COLOR_WHITE
DECL|macro|MENUBOX_BORDER_HL
mdefine_line|#define MENUBOX_BORDER_HL            TRUE
DECL|macro|ITEM_FG
mdefine_line|#define ITEM_FG                      COLOR_BLACK
DECL|macro|ITEM_BG
mdefine_line|#define ITEM_BG                      COLOR_WHITE
DECL|macro|ITEM_HL
mdefine_line|#define ITEM_HL                      FALSE
DECL|macro|ITEM_SELECTED_FG
mdefine_line|#define ITEM_SELECTED_FG             COLOR_WHITE
DECL|macro|ITEM_SELECTED_BG
mdefine_line|#define ITEM_SELECTED_BG             COLOR_BLUE
DECL|macro|ITEM_SELECTED_HL
mdefine_line|#define ITEM_SELECTED_HL             TRUE
DECL|macro|TAG_FG
mdefine_line|#define TAG_FG                       COLOR_YELLOW
DECL|macro|TAG_BG
mdefine_line|#define TAG_BG                       COLOR_WHITE
DECL|macro|TAG_HL
mdefine_line|#define TAG_HL                       TRUE
DECL|macro|TAG_SELECTED_FG
mdefine_line|#define TAG_SELECTED_FG              COLOR_YELLOW
DECL|macro|TAG_SELECTED_BG
mdefine_line|#define TAG_SELECTED_BG              COLOR_BLUE
DECL|macro|TAG_SELECTED_HL
mdefine_line|#define TAG_SELECTED_HL              TRUE
DECL|macro|TAG_KEY_FG
mdefine_line|#define TAG_KEY_FG                   COLOR_YELLOW
DECL|macro|TAG_KEY_BG
mdefine_line|#define TAG_KEY_BG                   COLOR_WHITE
DECL|macro|TAG_KEY_HL
mdefine_line|#define TAG_KEY_HL                   TRUE
DECL|macro|TAG_KEY_SELECTED_FG
mdefine_line|#define TAG_KEY_SELECTED_FG          COLOR_YELLOW
DECL|macro|TAG_KEY_SELECTED_BG
mdefine_line|#define TAG_KEY_SELECTED_BG          COLOR_BLUE
DECL|macro|TAG_KEY_SELECTED_HL
mdefine_line|#define TAG_KEY_SELECTED_HL          TRUE
DECL|macro|CHECK_FG
mdefine_line|#define CHECK_FG                     COLOR_BLACK
DECL|macro|CHECK_BG
mdefine_line|#define CHECK_BG                     COLOR_WHITE
DECL|macro|CHECK_HL
mdefine_line|#define CHECK_HL                     FALSE
DECL|macro|CHECK_SELECTED_FG
mdefine_line|#define CHECK_SELECTED_FG            COLOR_WHITE
DECL|macro|CHECK_SELECTED_BG
mdefine_line|#define CHECK_SELECTED_BG            COLOR_BLUE
DECL|macro|CHECK_SELECTED_HL
mdefine_line|#define CHECK_SELECTED_HL            TRUE
DECL|macro|UARROW_FG
mdefine_line|#define UARROW_FG                    COLOR_GREEN
DECL|macro|UARROW_BG
mdefine_line|#define UARROW_BG                    COLOR_WHITE
DECL|macro|UARROW_HL
mdefine_line|#define UARROW_HL                    TRUE
DECL|macro|DARROW_FG
mdefine_line|#define DARROW_FG                    COLOR_GREEN
DECL|macro|DARROW_BG
mdefine_line|#define DARROW_BG                    COLOR_WHITE
DECL|macro|DARROW_HL
mdefine_line|#define DARROW_HL                    TRUE
multiline_comment|/* End of default color definitions */
DECL|macro|C_ATTR
mdefine_line|#define C_ATTR(x,y)                  ((x ? A_BOLD : 0) | COLOR_PAIR((y)))
DECL|macro|COLOR_NAME_LEN
mdefine_line|#define COLOR_NAME_LEN               10
DECL|macro|COLOR_COUNT
mdefine_line|#define COLOR_COUNT                  8
multiline_comment|/*&n; * Global variables&n; */
r_typedef
r_struct
(brace
DECL|member|name
r_char
id|name
(braket
id|COLOR_NAME_LEN
)braket
suffix:semicolon
DECL|member|value
r_int
id|value
suffix:semicolon
DECL|typedef|color_names_st
)brace
id|color_names_st
suffix:semicolon
r_extern
id|color_names_st
id|color_names
(braket
)braket
suffix:semicolon
r_extern
r_int
id|color_table
(braket
)braket
(braket
l_int|3
)braket
suffix:semicolon
eof
