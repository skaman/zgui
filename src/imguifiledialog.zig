const std = @import("std");
const gui = @import("gui.zig");

pub const FileStyleFlags = packed struct(c_int) {
    by_type_file: bool = false,
    by_type_dir: bool = false,
    by_type_link: bool = false,
    by_type_extenstion: bool = false,
    by_type_full_name: bool = false,
    by_container_in_full_name: bool = false,
    padding: u26 = 0,
};

pub const FileDialogFlags = packed struct(c_int) {
    confirm_overwrite: bool = false,
    dont_show_hidden_files: bool = false,
    disable_create_direction_button: bool = false,
    hide_column_type: bool = false,
    hide_column_size: bool = false,
    hide_column_date: bool = false,
    no_dialog: bool = false,
    read_only_file_named_field: bool = false,
    case_insensitive_extension_filtering: bool = false,
    model: bool = false,
    disable_thumbnail_mode: bool = false,
    disable_place_mode: bool = false,
    disable_quick_path_selection: bool = false,
    show_devices_button: bool = false,
    natural_sorting: bool = false,
    padding: u17 = 0,
};

pub const ResultMode = enum(c_int) {
    add_if_no_file_ext,
    overwrite_file_ext,
    keep_input_file,
};

pub const FileDialogConfig = extern struct {
    path: [*c]const u8 = "",
    file_name: [*c]const u8 = "",
    file_path_name: [*c]const u8 = "",
    count_selection_max: c_int = 1,
    user_datas: ?*anyopaque = null,
    flags: FileDialogFlags = .{},
    side_pane_width: f32 = 250.0,
};

pub fn open_dialog(key: [*c]const u8, title: [*c]const u8, filters: [*c]const u8, config: FileDialogConfig) void {
    imguifiledialog_OpenDialog(key, title, filters, &config);
}
extern fn imguifiledialog_OpenDialog(key: [*c]const u8, title: [*c]const u8, filters: [*c]const u8, config: *const FileDialogConfig) void;

pub const DisplayArgs = struct {
    flags: gui.WindowFlags = .{
        .no_collapse = true,
    },
    min_size: [2]f32 = .{ 0.0, 0.0 },
    max_size: [2]f32 = .{ std.math.floatMax(f32), std.math.floatMax(f32) },
};
pub fn display(key: [*c]const u8, args: DisplayArgs) bool {
    return imguifiledialog_Display(
        key,
        args.flags,
        args.min_size[0],
        args.min_size[1],
        args.max_size[0],
        args.max_size[1],
    );
}
extern fn imguifiledialog_Display(
    key: [*c]const u8,
    flags: gui.WindowFlags,
    min_size_x: f32,
    min_size_y: f32,
    max_size_x: f32,
    max_size_y: f32,
) bool;

pub fn close() void {
    imguifiledialog_Close();
}
extern fn imguifiledialog_Close() void;

pub fn was_opened_this_frame_by_key(key: [*c]const u8) bool {
    return imguifiledialog_WasOpenedThisFrameByKey(key);
}
extern fn imguifiledialog_WasOpenedThisFrameByKey(key: [*c]const u8) bool;

pub fn was_opened_this_frame() bool {
    return imguifiledialog_WasOpenedThisFrame();
}
extern fn imguifiledialog_WasOpenedThisFrame() bool;

pub fn is_opened_by_key(key: [*c]const u8) bool {
    return imguifiledialog_IsOpenedByKey(key);
}
extern fn imguifiledialog_IsOpenedByKey(key: [*c]const u8) bool;

pub fn is_opened() bool {
    return imguifiledialog_IsOpened();
}
extern fn imguifiledialog_IsOpened() bool;

pub fn get_opened_key(buffer: []u8) void {
    imguifiledialog_GetOpenedKey(&buffer[0], buffer.len);
}
extern fn imguifiledialog_GetOpenedKey(buffer: [*c]const u8, buffer_size: usize) void;

pub fn is_ok() bool {
    return imguifiledialog_IsOk();
}
extern fn imguifiledialog_IsOk() bool;

const SelectionItem = extern struct {
    file_name: [*c]const u8,
    file_path_name: [*c]const u8,
};

const Selection = extern struct {
    items: [*c]SelectionItem,
    count: usize,
};

pub fn get_selection(result_mode: ResultMode) Selection {
    return imguifiledialog_GetSelection(result_mode);
}
extern fn imguifiledialog_GetSelection(result_mode: ResultMode) Selection;

pub fn free_selection(selection: *const Selection) void {
    imguifiledialog_FreeSelection(selection);
}
extern fn imguifiledialog_FreeSelection(selection: *const Selection) void;

pub fn get_file_path_name(buffer: [:0]u8, result_mode: ResultMode) void {
    imguifiledialog_GetFilePathName(&buffer[0], buffer.len, result_mode);
}
extern fn imguifiledialog_GetFilePathName(buffer: [*c]const u8, buffer_size: usize, result_mode: ResultMode) void;

pub fn get_current_file_name(buffer: [:0]u8, result_mode: ResultMode) void {
    return imguifiledialog_GetCurrentFileName(&buffer[0], buffer.len, result_mode);
}
extern fn imguifiledialog_GetCurrentFileName(buffer: [*c]const u8, buffer_size: usize, result_mode: ResultMode) void;

pub fn get_current_path(buffer: [:0]u8) void {
    return imguifiledialog_GetCurrentPath(&buffer[0], buffer.len);
}
extern fn imguifiledialog_GetCurrentPath(buffer: [*c]const u8, buffer_size: usize) void;

pub fn get_current_filter(buffer: [:0]u8) void {
    return imguifiledialog_GetCurrentFilter(&buffer[0], buffer.len);
}
extern fn imguifiledialog_GetCurrentFilter(buffer: [*c]const u8, buffer_size: usize) void;

pub fn get_user_datas() ?*anyopaque {
    return imguifiledialog_GetUserDatas();
}
extern fn imguifiledialog_GetUserDatas() ?*anyopaque;

const FileStyle = extern struct {
    color: u32 = 0,
    icon: [*c]const u8 = null,
    font: ?gui.Font = null,
    flags: FileStyleFlags = .{},
};

pub fn set_file_style(flags: FileStyleFlags, criteria: [*c]const u8, infos: FileStyle) void {
    imguifiledialog_SetFileStyle(flags, criteria, &infos);
}
extern fn imguifiledialog_SetFileStyle(flags: FileStyleFlags, criteria: [*c]const u8, infos: *const FileStyle) void;

pub fn get_file_style(flags: FileStyleFlags, criteria: [*c]const u8, out_color: *u32, out_icon: ?[*c]const u8, out_font: ?*gui.Font) void {
    imguifiledialog_GetFileStyle(flags, criteria, out_color, out_icon, out_font);
}
extern fn imguifiledialog_GetFileStyle(flags: FileStyleFlags, criteria: [*c]const u8, out_color: *u32, out_icon: ?[*c]const u8, out_font: ?*gui.Font) void;

pub fn clear_files_style() void {
    imguifiledialog_ClearFilesStyle();
}
extern fn imguifiledialog_ClearFilesStyle() void;

pub fn set_locales(locale_category: c_int, locale_begin: [*c]const u8, locale_end: [*c]const u8) void {
    imguifiledialog_SetLocales(locale_category, locale_begin, locale_end);
}
extern fn imguifiledialog_SetLocales(locale_category: c_int, locale_begin: [*c]const u8, locale_end: [*c]const u8) void;
