// Copyright (C) 2025 lingyicute
// SPDX-License-Identifier: GPL-3.0-only
// See LICENSE in the top level directory

#pragma once

#include "MainResource.h"
#include <unordered_map>

// clang-format off
const std::unordered_map<std::wstring, int> ACCELERATOR_MAPPINGS = {
	// Accelerators.
	{L"address_bar", IDA_ADDRESSBAR},
	{L"address_bar_dropdown", IDA_COMBODROPDOWN},
	{L"home", IDA_HOME},
	{L"select_last_tab", IDA_LASTTAB},
	{L"select_next_tab", IDA_NEXTTAB},
	{L"focus_next_window", IDA_NEXTWINDOW},
	{L"select_previous_tab", IDA_PREVIOUSTAB},
	{L"focus_previous_window", IDA_PREVIOUSWINDOW},
	{L"select_tab_1", IDA_TAB1},
	{L"select_tab_2", IDA_TAB2},
	{L"select_tab_3", IDA_TAB3},
	{L"select_tab_4", IDA_TAB4},
	{L"select_tab_5", IDA_TAB5},
	{L"select_tab_6", IDA_TAB6},
	{L"select_tab_7", IDA_TAB7},
	{L"select_tab_8", IDA_TAB8},
	{L"duplicate_tab", IDA_TAB_DUPLICATETAB},

	// The accelerators below are specifically excluded from customization.
	// {L"right_click", IDA_RCLICK}

	// Main menu items.
	{L"new_tab", IDM_FILE_NEWTAB},
	{L"close_tab", IDM_FILE_CLOSETAB},
	{L"clone_window", IDM_FILE_CLONEWINDOW},
	{L"save_directory_listing", IDM_FILE_SAVEDIRECTORYLISTING},
	{L"open_command_prompt", IDM_FILE_OPENCOMMANDPROMPT},
	{L"open_command_prompt_as_administrator", IDM_FILE_OPENCOMMANDPROMPTADMINISTRATOR},
	{L"copy_folder_path", IDM_FILE_COPYFOLDERPATH},
	{L"copy_file_paths", IDM_FILE_COPYITEMPATH},
	{L"copy_universal_file_paths", IDM_FILE_COPYUNIVERSALFILEPATHS},
	{L"copy_column_text", IDM_FILE_COPYCOLUMNTEXT},
	{L"set_file_attributes", IDM_FILE_SETFILEATTRIBUTES},
	{L"delete_permanently", IDM_FILE_DELETEPERMANENTLY},
	{L"rename", IDM_FILE_RENAME},
	{L"properties", IDM_FILE_PROPERTIES},
	{L"exit", IDM_FILE_EXIT},

	{L"undo", IDM_EDIT_UNDO},
	{L"paste_shortcut", IDM_EDIT_PASTESHORTCUT},
	{L"paste_hard_link", IDM_EDIT_PASTEHARDLINK},
	{L"copy_to_folder", IDM_EDIT_COPYTOFOLDER},
	{L"move_to_folder", IDM_EDIT_MOVETOFOLDER},
	{L"resolve_link", IDM_EDIT_RESOLVELINK},

	{L"select_all_of_same_type", IDM_EDIT_SELECTALLOFSAMETYPE},
	{L"select_none", IDM_EDIT_SELECTNONE},
	{L"wildcard_deselect", IDM_EDIT_WILDCARDDESELECT},
	{L"wildcard_select", IDM_EDIT_WILDCARDSELECTION},

	{L"toggle_status_bar", IDM_VIEW_STATUSBAR},
	{L"toggle_folders", IDM_VIEW_FOLDERS},
	{L"toggle_display_window", IDM_VIEW_DISPLAYWINDOW},
	{L"toggle_address_bar", IDM_TOOLBARS_ADDRESSBAR},
	{L"toggle_main_toolbar", IDM_TOOLBARS_MAINTOOLBAR},
	{L"toggle_bookmarks_toolbar", IDM_TOOLBARS_BOOKMARKSTOOLBAR},
	{L"toggle_drives_toolbar", IDM_TOOLBARS_DRIVES},
	{L"toggle_application_toolbar", IDM_TOOLBARS_APPLICATIONTOOLBAR},
	{L"lock_toolbars", IDM_TOOLBARS_LOCKTOOLBARS},
	{L"customize_toolbars", IDM_TOOLBARS_CUSTOMIZE},

	{L"view_mode_thumbnails", IDM_VIEW_THUMBNAILS},
	{L"view_mode_tiles", IDM_VIEW_TILES},
	{L"view_mode_extra_large_icons", IDM_VIEW_EXTRALARGEICONS},
	{L"view_mode_large_icons", IDM_VIEW_LARGEICONS},
	{L"view_mode_icons", IDM_VIEW_ICONS},
	{L"view_mode_small_icons", IDM_VIEW_SMALLICONS},
	{L"view_mode_list", IDM_VIEW_LIST},
	{L"view_mode_details", IDM_VIEW_DETAILS},
	{L"view_mode_large_thumbnails", IDM_VIEW_LARGETHUMBNAILS},
	{L"view_mode_extra_large_thumbnails", IDM_VIEW_EXTRALARGETHUMBNAILS},

	{L"auto_arrange", IDM_VIEW_AUTOARRANGE},
	{L"toggle_hidden_files", IDM_VIEW_SHOWHIDDENFILES},
	{L"refresh", IDM_VIEW_REFRESH},

	{L"sort_by_name", IDM_SORTBY_NAME},
	{L"sort_by_size", IDM_SORTBY_SIZE},
	{L"sort_by_type", IDM_SORTBY_TYPE},
	{L"sort_by_date_modified", IDM_SORTBY_DATEMODIFIED},
	{L"sort_by_total_size", IDM_SORTBY_TOTALSIZE},
	{L"sort_by_free_space", IDM_SORTBY_FREESPACE},
	{L"sort_by_date_deleted", IDM_SORTBY_DATEDELETED},
	{L"sort_by_original_location", IDM_SORTBY_ORIGINALLOCATION},
	{L"sort_by_attributes", IDM_SORTBY_ATTRIBUTES},
	{L"sort_by_real_size", IDM_SORTBY_REALSIZE},
	{L"sort_by_short_name", IDM_SORTBY_SHORTNAME},
	{L"sort_by_owner", IDM_SORTBY_OWNER},
	{L"sort_by_product_name", IDM_SORTBY_PRODUCTNAME},
	{L"sort_by_company", IDM_SORTBY_COMPANY},
	{L"sort_by_description", IDM_SORTBY_DESCRIPTION},
	{L"sort_by_file_version", IDM_SORTBY_FILEVERSION},
	{L"sort_by_product_version", IDM_SORTBY_PRODUCTVERSION},
	{L"sort_by_shortcut_to", IDM_SORTBY_SHORTCUTTO},
	{L"sort_by_hard_links", IDM_SORTBY_HARDLINKS},
	{L"sort_by_extension", IDM_SORTBY_EXTENSION},
	{L"sort_by_created", IDM_SORTBY_CREATED},
	{L"sort_by_accessed", IDM_SORTBY_ACCESSED},
	{L"sort_by_title", IDM_SORTBY_TITLE},
	{L"sort_by_subject", IDM_SORTBY_SUBJECT},
	{L"sort_by_author", IDM_SORTBY_AUTHOR},
	{L"sort_by_keywords", IDM_SORTBY_KEYWORDS},
	{L"sort_by_comments", IDM_SORTBY_COMMENTS},
	{L"sort_by_camera_model", IDM_SORTBY_CAMERAMODEL},
	{L"sort_by_date_taken", IDM_SORTBY_DATETAKEN},
	{L"sort_by_width", IDM_SORTBY_WIDTH},
	{L"sort_by_height", IDM_SORTBY_HEIGHT},
	{L"sort_by_virtual_comments", IDM_SORTBY_VIRTUALCOMMENTS},
	{L"sort_by_filesystem", IDM_SORTBY_FILESYSTEM},
	{L"sort_by_num_printer_documents", IDM_SORTBY_NUMPRINTERDOCUMENTS},
	{L"sort_by_printer_status", IDM_SORTBY_PRINTERSTATUS},
	{L"sort_by_printer_comments", IDM_SORTBY_PRINTERCOMMENTS},
	{L"sort_by_printer_location", IDM_SORTBY_PRINTERLOCATION},
	{L"sort_by_network_adapter_status", IDM_SORTBY_NETWORKADAPTER_STATUS},
	{L"sort_by_media_bitrate", IDM_SORTBY_MEDIA_BITRATE},
	{L"sort_by_media_copyright", IDM_SORTBY_MEDIA_COPYRIGHT},
	{L"sort_by_media_duration", IDM_SORTBY_MEDIA_DURATION},
	{L"sort_by_media_protected", IDM_SORTBY_MEDIA_PROTECTED},
	{L"sort_by_media_rating", IDM_SORTBY_MEDIA_RATING},
	{L"sort_by_mediat_album_artist", IDM_SORTBY_MEDIA_ALBUM_ARTIST},
	{L"sort_by_media_album", IDM_SORTBY_MEDIA_ALBUM},
	{L"sort_by_media_beats_per_minute", IDM_SORTBY_MEDIA_BEATS_PER_MINUTE},
	{L"sort_by_media_composer", IDM_SORTBY_MEDIA_COMPOSER},
	{L"sort_by_media_conductor", IDM_SORTBY_MEDIA_CONDUCTOR},
	{L"sort_by_media_director", IDM_SORTBY_MEDIA_DIRECTOR},
	{L"sort_by_media_genre", IDM_SORTBY_MEDIA_GENRE},
	{L"sort_by_media_language", IDM_SORTBY_MEDIA_LANGUAGE},
	{L"sort_by_media_broadcast_date", IDM_SORTBY_MEDIA_BROADCAST_DATE},
	{L"sort_by_media_channel", IDM_SORTBY_MEDIA_CHANNEL},
	{L"sort_by_media_station_name", IDM_SORTBY_MEDIA_STATION_NAME},
	{L"sort_by_media_mood", IDM_SORTBY_MEDIA_MOOD},
	{L"sort_by_media_parental_rating", IDM_SORTBY_MEDIA_PARENTAL_RATING},
	{L"sort_by_media_parental_rating_reason", IDM_SORTBY_MEDIA_PARENTAL_RATNG_REASON},
	{L"sort_by_media_period", IDM_SORTBY_MEDIA_PERIOD},
	{L"sort_by_media_producer", IDM_SORTBY_MEDIA_PRODUCER},
	{L"sort_by_media_publisher", IDM_SORTBY_MEDIA_PUBLISHER},
	{L"sort_by_media_writer", IDM_SORTBY_MEDIA_WRITER},
	{L"sort_by_media_year", IDM_SORTBY_MEDIA_YEAR},

	{L"group_by_name", IDM_GROUPBY_NAME},
	{L"group_by_size", IDM_GROUPBY_SIZE},
	{L"group_by_type", IDM_GROUPBY_TYPE},
	{L"group_by_date_modified", IDM_GROUPBY_DATEMODIFIED},
	{L"group_by_total_size", IDM_GROUPBY_TOTALSIZE},
	{L"group_by_free_space", IDM_GROUPBY_FREESPACE},
	{L"group_by_date_deleted", IDM_GROUPBY_DATEDELETED},
	{L"group_by_original_location", IDM_GROUPBY_ORIGINALLOCATION},
	{L"group_by_attributes", IDM_GROUPBY_ATTRIBUTES},
	{L"group_by_real_size", IDM_GROUPBY_REALSIZE},
	{L"group_by_short_name", IDM_GROUPBY_SHORTNAME},
	{L"group_by_owner", IDM_GROUPBY_OWNER},
	{L"group_by_product_name", IDM_GROUPBY_PRODUCTNAME},
	{L"group_by_company", IDM_GROUPBY_COMPANY},
	{L"group_by_description", IDM_GROUPBY_DESCRIPTION},
	{L"group_by_file_version", IDM_GROUPBY_FILEVERSION},
	{L"group_by_product_version", IDM_GROUPBY_PRODUCTVERSION},
	{L"group_by_shortcut_to", IDM_GROUPBY_SHORTCUTTO},
	{L"group_by_hard_links", IDM_GROUPBY_HARDLINKS},
	{L"group_by_extension", IDM_GROUPBY_EXTENSION},
	{L"group_by_created", IDM_GROUPBY_CREATED},
	{L"group_by_accessed", IDM_GROUPBY_ACCESSED},
	{L"group_by_title", IDM_GROUPBY_TITLE},
	{L"group_by_subject", IDM_GROUPBY_SUBJECT},
	{L"group_by_author", IDM_GROUPBY_AUTHOR},
	{L"group_by_keywords", IDM_GROUPBY_KEYWORDS},
	{L"group_by_comments", IDM_GROUPBY_COMMENTS},
	{L"group_by_camera_model", IDM_GROUPBY_CAMERAMODEL},
	{L"group_by_date_taken", IDM_GROUPBY_DATETAKEN},
	{L"group_by_width", IDM_GROUPBY_WIDTH},
	{L"group_by_height", IDM_GROUPBY_HEIGHT},
	{L"group_by_virtual_comments", IDM_GROUPBY_VIRTUALCOMMENTS},
	{L"group_by_filesystem", IDM_GROUPBY_FILESYSTEM},
	{L"group_by_num_printer_documents", IDM_GROUPBY_NUMPRINTERDOCUMENTS},
	{L"group_by_printer_status", IDM_GROUPBY_PRINTERSTATUS},
	{L"group_by_printer_comments", IDM_GROUPBY_PRINTERCOMMENTS},
	{L"group_by_printer_location", IDM_GROUPBY_PRINTERLOCATION},
	{L"group_by_network_adapter_status", IDM_GROUPBY_NETWORKADAPTER_STATUS},
	{L"group_by_media_bitrate", IDM_GROUPBY_MEDIA_BITRATE},
	{L"group_by_media_copyright", IDM_GROUPBY_MEDIA_COPYRIGHT},
	{L"group_by_media_duration", IDM_GROUPBY_MEDIA_DURATION},
	{L"group_by_media_protected", IDM_GROUPBY_MEDIA_PROTECTED},
	{L"group_by_media_rating", IDM_GROUPBY_MEDIA_RATING},
	{L"group_by_mediat_album_artist", IDM_GROUPBY_MEDIA_ALBUM_ARTIST},
	{L"group_by_media_album", IDM_GROUPBY_MEDIA_ALBUM},
	{L"group_by_media_beats_per_minute", IDM_GROUPBY_MEDIA_BEATS_PER_MINUTE},
	{L"group_by_media_composer", IDM_GROUPBY_MEDIA_COMPOSER},
	{L"group_by_media_conductor", IDM_GROUPBY_MEDIA_CONDUCTOR},
	{L"group_by_media_director", IDM_GROUPBY_MEDIA_DIRECTOR},
	{L"group_by_media_genre", IDM_GROUPBY_MEDIA_GENRE},
	{L"group_by_media_language", IDM_GROUPBY_MEDIA_LANGUAGE},
	{L"group_by_media_broadcast_date", IDM_GROUPBY_MEDIA_BROADCAST_DATE},
	{L"group_by_media_channel", IDM_GROUPBY_MEDIA_CHANNEL},
	{L"group_by_media_station_name", IDM_GROUPBY_MEDIA_STATION_NAME},
	{L"group_by_media_mood", IDM_GROUPBY_MEDIA_MOOD},
	{L"group_by_media_parental_rating", IDM_GROUPBY_MEDIA_PARENTAL_RATING},
	{L"group_by_media_parental_rating_reason", IDM_GROUPBY_MEDIA_PARENTAL_RATING_REASON},
	{L"group_by_media_period", IDM_GROUPBY_MEDIA_PERIOD},
	{L"group_by_media_producer", IDM_GROUPBY_MEDIA_PRODUCER},
	{L"group_by_media_publisher", IDM_GROUPBY_MEDIA_PUBLISHER},
	{L"group_by_media_writer", IDM_GROUPBY_MEDIA_WRITER},
	{L"group_by_media_year", IDM_GROUPBY_MEDIA_YEAR},

	{L"select_columns", IDM_VIEW_SELECTCOLUMNS},
	{L"autosize_columns", IDM_VIEW_AUTOSIZECOLUMNS},
	{L"save_column_layout_as_default", IDM_VIEW_SAVECOLUMNLAYOUTASDEFAULT},
	{L"change_display_window_colors", IDM_VIEW_CHANGEDISPLAYCOLOURS},

	{L"set_filter", IDM_FILTER_FILTERRESULTS},
	{L"apply_filter", IDM_FILTER_APPLYFILTER},

	{L"new_folder", IDM_ACTIONS_NEWFOLDER},
	{L"split_file", IDM_ACTIONS_SPLITFILE},
	{L"merge_files", IDM_ACTIONS_MERGEFILES},
	{L"destroy_files", IDM_ACTIONS_DESTROYFILES},

	{L"back", IDM_GO_BACK},
	{L"forward", IDM_GO_FORWARD},
	{L"up", IDM_GO_UP},
	{L"go_quick_access", IDM_GO_QUICK_ACCESS},
	{L"go_computer", IDM_GO_COMPUTER},
	{L"go_documents", IDM_GO_DOCUMENTS},
	{L"go_downloads", IDM_GO_DOWNLOADS},
	{L"go_music", IDM_GO_MUSIC},
	{L"go_pictures", IDM_GO_PICTURES},
	{L"go_videos", IDM_GO_VIDEOS},
	{L"go_desktop", IDM_GO_DESKTOP},
	{L"go_recycle_bin", IDM_GO_RECYCLE_BIN},
	{L"go_control_panel", IDM_GO_CONTROL_PANEL},
	{L"go_printers", IDM_GO_PRINTERS},
	{L"go_network_places", IDM_GO_NETWORK},
	{L"go_wsl_distributions", IDM_GO_WSL_DISTRIBUTIONS},

	{L"bookmark_tab", IDM_BOOKMARKS_BOOKMARKTHISTAB},
	{L"manage_bookmarks", IDM_BOOKMARKS_MANAGEBOOKMARKS},

	{L"search", IDM_TOOLS_SEARCH},
	{L"customize_colors", IDM_TOOLS_CUSTOMIZECOLORS},
	{L"run_script", IDM_TOOLS_RUNSCRIPT},
	{L"options", IDM_TOOLS_OPTIONS},

	{L"help", IDM_HELP_ONLINE_DOCUMENTATION},
	{L"check_for_updates", IDM_HELP_CHECKFORUPDATES},
	{L"about", IDM_HELP_ABOUT}
};
// clang-format on
