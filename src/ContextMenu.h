

const int MI_MOUSE_GESTURE       = WM_APP + 1;
const int MI_NATURAL_SCROLL      = WM_APP + 2;
const int MI_THROUGH_BORDER      = WM_APP + 3;
const int MI_SUPER_KEY           = WM_APP + 4;
const int MI_SUPER_DRAG          = WM_APP + 5;
const int MI_SUPER_VOLUME        = WM_APP + 6;
const int MI_HIDE_MOUSE_TRACK    = WM_APP + 7;
const int MI_HIDE_GESTURE_RESULT = WM_APP + 8;
const int MI_VOLUME_SOUND        = WM_APP + 9;
const int MI_HIDE_ICON           = WM_APP + 10;
const int MI_ABOUT               = WM_APP + 11;
const int MI_AUTO_RUN            = WM_APP + 12;
const int MI_EXIT                = WM_APP + 13;
const int MI_SCROLL_THROUGH      = WM_APP + 14;

const int MI_TOGGLE_ICON         = WM_APP + 100;

void ShowContextMenu(HWND hwnd)
{
    POINT pt;
    ::GetCursorPos(&pt);
    HMENU menu = ::CreatePopupMenu();
    HMENU pop_menu;

    ::AppendMenu(menu, MF_BYPOSITION | (Config::GetInt(L"Basic", L"MouseGesture")?MF_CHECKED:0),
        MI_MOUSE_GESTURE, i18n::GetString(L"mouse_gesture").c_str());
    ::AppendMenu(menu, MF_BYPOSITION | (Config::GetInt(L"Basic", L"ScrollThrough")?MF_CHECKED:0),
        MI_SCROLL_THROUGH, i18n::GetString(L"scroll_through").c_str());
    ::AppendMenu(menu, MF_BYPOSITION | (Config::GetInt(L"Basic", L"NaturalScroll")?MF_CHECKED:0),
        MI_NATURAL_SCROLL, i18n::GetString(L"natural_scroll").c_str());
    ::AppendMenu(menu, MF_BYPOSITION | (Config::GetInt(L"Basic", L"ThroughBorder")?MF_CHECKED:0),
        MI_THROUGH_BORDER, i18n::GetString(L"through_border").c_str());

    // 超级键
    pop_menu = CreatePopupMenu();
    ::AppendMenu(pop_menu, MF_BYPOSITION | (Config::SuperKey?MF_CHECKED:0),
        MI_SUPER_KEY, i18n::GetString(L"enable").c_str());
    ::AppendMenu(pop_menu, MF_SEPARATOR, 0, NULL);
    ::AppendMenu(pop_menu, MF_BYPOSITION | (Config::GetInt(L"SuperKey", L"SuperDrag")?MF_CHECKED:0) | (Config::SuperKey?0:MF_DISABLED),
        MI_SUPER_DRAG, i18n::GetString(L"super_drag").c_str());
    ::AppendMenu(pop_menu, MF_BYPOSITION | (Config::GetInt(L"SuperKey", L"SuperVolume")?MF_CHECKED:0) | (Config::SuperKey?0:MF_DISABLED),
        MI_SUPER_VOLUME, i18n::GetString(L"super_volume").c_str());
    ::AppendMenuW(menu, MF_POPUP | MF_BYPOSITION, (UINT_PTR)pop_menu, i18n::GetString(L"super_key").c_str());
    ::AppendMenu(menu, MF_SEPARATOR, 0, NULL);

    // 其它设置
    pop_menu = CreatePopupMenu();
    ::AppendMenu(pop_menu, MF_BYPOSITION | (Config::GetInt(L"Other", L"HideGestureTrack")?MF_CHECKED:0) | (Config::GetInt(L"Basic", L"MouseGesture")?0:MF_DISABLED),
        MI_HIDE_MOUSE_TRACK, i18n::GetString(L"hide_mouse_track").c_str());
    ::AppendMenu(pop_menu, MF_BYPOSITION | (Config::GetInt(L"Other", L"HideGestureResult")?MF_CHECKED:0) | (Config::GetInt(L"Basic", L"MouseGesture")?0:MF_DISABLED),
        MI_HIDE_GESTURE_RESULT, i18n::GetString(L"hide_gesture_result").c_str());
    ::AppendMenu(pop_menu, MF_SEPARATOR, 0, NULL);
    ::AppendMenu(pop_menu, MF_BYPOSITION | (Config::GetInt(L"Other", L"VolumeSound", 1)?MF_CHECKED:0) | (Config::SuperKey?0:MF_DISABLED),
        MI_VOLUME_SOUND, i18n::GetString(L"volume_sound").c_str());
    ::AppendMenu(pop_menu, MF_SEPARATOR, 0, NULL);
    ::AppendMenu(pop_menu, MF_BYPOSITION | (Config::GetInt(L"Other", L"HideTrayIcon")?MF_CHECKED:0),
        MI_HIDE_ICON, i18n::GetString(L"hide_icon").c_str());
    ::AppendMenu(menu, MF_POPUP | MF_BYPOSITION, (UINT_PTR)pop_menu, i18n::GetString(L"other").c_str());
    ::AppendMenu(menu, MF_SEPARATOR, 0, NULL);


    ::AppendMenu(menu, MF_BYPOSITION | (is_autorun() ? MF_CHECKED : 0), MI_AUTO_RUN, i18n::GetString(L"autorun").c_str());
    ::AppendMenu(menu, MF_BYPOSITION, MI_ABOUT, i18n::GetString(L"about").c_str());
    ::AppendMenu(menu, MF_BYPOSITION, MI_EXIT, i18n::GetString(L"exit").c_str());

    //显示菜单
    ::SetForegroundWindow(hwnd);
    ::TrackPopupMenu(menu, TPM_BOTTOMALIGN, pt.x, pt.y, 0, hwnd, NULL);
    ::DestroyMenu(menu);
}

//默认菜单处理
void MenuDefaultHandle(HWND hwnd, WPARAM id)
{
    switch(id)
    {
        case MI_MOUSE_GESTURE:
            Config::Switch(L"Basic", L"MouseGesture");
            break;
        case MI_SCROLL_THROUGH:
            Config::Switch(L"Basic", L"ScrollThrough");
            break;
        case MI_NATURAL_SCROLL:
            Config::Switch(L"Basic", L"NaturalScroll");
            break;
        case MI_THROUGH_BORDER:
            Config::Switch(L"Basic", L"ThroughBorder");
            break;
        case MI_SUPER_KEY:
            Config::Switch(L"Basic", L"SuperKey");
            Config::ParseSuperKey();
            break;
        case MI_SUPER_DRAG:
            Config::Switch(L"SuperKey", L"SuperDrag");
            break;
        case MI_SUPER_VOLUME:
            Config::Switch(L"SuperKey", L"SuperVolume");
            break;
        case MI_HIDE_MOUSE_TRACK:
            Config::Switch(L"Other", L"HideGestureTrack");
            break;
        case MI_HIDE_GESTURE_RESULT:
            Config::Switch(L"Other", L"HideGestureResult");
            break;
        case MI_VOLUME_SOUND:
            Config::Switch(L"Other", L"VolumeSound");
            break;
    }
}