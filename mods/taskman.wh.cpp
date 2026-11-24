// ==WindhawkMod==
// @id              taskman
// @name            Taskman
// @description     Alt+Q quit, display scaling with the mouse wheel, pinned program windows, mini task manager, opacity bar, Shift+Space screenshot and a shortcut help (Ctrl+Num 0)
// @version         1.0.0
// @author          Eikka
// @github          https://github.com/reset-eikka
// @include         windhawk.exe
// @compilerOptions -lpdh -lshell32 -lgdi32 -luser32 -lole32 -luuid -ladvapi32 -ldwmapi -lwtsapi32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Taskman

All my small Windhawk tools in one mod. Ctrl+Numpad 0 pops up a list of the shortcuts that are on right now.

## Shortcuts

Numpad ones need NumLock off, unless you change that in the settings.

- **Ctrl+Num 1-9** shows / hides the program in that slot, **Shift+Num** saves where it is and how big it is
- **Ctrl+Num 3** task manager overlay, **Ctrl+Num 4** opacity bar, **Ctrl+Num 7** hide / show everything, **Ctrl+Num 0** the help
- **Alt+Q** quits the focused program
- **Alt+Shift+mouse wheel** changes the display scaling
- **Shift+Space** takes a screenshot (Win+Shift+S)
- **Shift or Alt + mouse wheel** over Obsidian zooms it

## Programs

The slots are in the settings. Put in an exe name (like `claude.exe`) or the full path, pick the numpad key, and pick if it works with NumLock off, on or both. With a full path the program is also started if it isn't running. Store apps like Sticky Notes: use `ApplicationFrameHost.exe` and fill in the window title.

Opacity grows with the window width. The bar sets the base value, and a window that is half the monitor wide or wider is fully opaque.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- altQ: true
  $name: Alt+Q quits the focused program
  $description: "Closes the whole program, all its windows, like Cmd+Q on a Mac. In File Explorer it only closes the one window."
- scaleScroll: true
  $name: Alt+Shift+mouse wheel changes the display scaling
- shiftSpaceSnip: true
  $name: Shift+Space opens the snipping tool
  $description: "Sends Win+Shift+S. Heads up, it also fires if you type a capital letter and hit space while Shift is still down, so turn it off if it annoys you."
- builtinNumLock: numlock_off
  $name: NumLock state for the built-in keys (0, 3, 4, 7)
  $options:
  - numlock_off: NumLock off
  - numlock_on: NumLock on
  - numlock_any: Either
- slot1_program: "claude.exe"
  $name: Slot 1 - program
  $description: "Exe name (like claude.exe) or the full path. With a full path the program also gets started if it is not running. Empty = slot is off."
- slot1_key: 1
  $name: Slot 1 - numpad key
  $description: "Numpad digit 1-9. Ctrl+Num shows / hides, Shift+Num saves the position. 0 = slot is off. Keys 0, 3, 4 and 7 are taken by the built-in stuff."
- slot1_numlock: numlock_off
  $name: Slot 1 - NumLock state
  $options:
  - numlock_off: NumLock off
  - numlock_on: NumLock on
  - numlock_any: Either
- slot1_title: ""
  $name: Slot 1 - window title contains (optional)
  $description: "Only use windows that have this text in the title. Separate alternatives with |."
- slot2_program: "obsidian.exe"
  $name: Slot 2 - program
- slot2_key: 2
  $name: Slot 2 - numpad key
- slot2_numlock: numlock_off
  $name: Slot 2 - NumLock state
  $options:
  - numlock_off: NumLock off
  - numlock_on: NumLock on
  - numlock_any: Either
- slot2_title: ""
  $name: Slot 2 - window title contains (optional)
- slot3_program: "spotify.exe"
  $name: Slot 3 - program
- slot3_key: 9
  $name: Slot 3 - numpad key
- slot3_numlock: numlock_off
  $name: Slot 3 - NumLock state
  $options:
  - numlock_off: NumLock off
  - numlock_on: NumLock on
  - numlock_any: Either
- slot3_title: ""
  $name: Slot 3 - window title contains (optional)
- slot4_program: "ApplicationFrameHost.exe"
  $name: Slot 4 - program
- slot4_key: 6
  $name: Slot 4 - numpad key
- slot4_numlock: numlock_off
  $name: Slot 4 - NumLock state
  $options:
  - numlock_off: NumLock off
  - numlock_on: NumLock on
  - numlock_any: Either
- slot4_title: "Sticky Notes|Tarralaput"
  $name: Slot 4 - window title contains (optional)
- slot5_program: "explorer.exe"
  $name: Slot 5 - program
- slot5_key: 5
  $name: Slot 5 - numpad key
- slot5_numlock: numlock_off
  $name: Slot 5 - NumLock state
  $options:
  - numlock_off: NumLock off
  - numlock_on: NumLock on
  - numlock_any: Either
- slot5_title: ""
  $name: Slot 5 - window title contains (optional)
- slot6_program: ""
  $name: Slot 6 - program
- slot6_key: 0
  $name: Slot 6 - numpad key
- slot6_numlock: numlock_off
  $name: Slot 6 - NumLock state
  $options:
  - numlock_off: NumLock off
  - numlock_on: NumLock on
  - numlock_any: Either
- slot6_title: ""
  $name: Slot 6 - window title contains (optional)
- slot7_program: ""
  $name: Slot 7 - program
- slot7_key: 0
  $name: Slot 7 - numpad key
- slot7_numlock: numlock_off
  $name: Slot 7 - NumLock state
  $options:
  - numlock_off: NumLock off
  - numlock_on: NumLock on
  - numlock_any: Either
- slot7_title: ""
  $name: Slot 7 - window title contains (optional)
- slot8_program: ""
  $name: Slot 8 - program
- slot8_key: 0
  $name: Slot 8 - numpad key
- slot8_numlock: numlock_off
  $name: Slot 8 - NumLock state
  $options:
  - numlock_off: NumLock off
  - numlock_on: NumLock on
  - numlock_any: Either
- slot8_title: ""
  $name: Slot 8 - window title contains (optional)
*/
// ==/WindhawkModSettings==

#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <shobjidl.h>
#include <shlobj.h>
#include <propkey.h>
#include <dwmapi.h>
#include <pdh.h>
#include <wtsapi32.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <vector>
#include <algorithm>

#define SU_WM_CMD        (WM_APP + 10)
#define SU_WM_TM_TOGGLE  (WM_USER + 2)
#define SU_MAX_WIN       16
#define WM_SAVE_POS      (WM_USER + 3)

// ---- opacity ----

static int  g_basePct = 85;
static HWND g_sliderHwnd = nullptr;

static int SuClamp(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }

static int SuiteBasePct() { return g_basePct; }

static void SuiteSetBase(int pct) {
    pct = SuClamp(pct, 0, 100);
    if (pct == g_basePct) return;
    g_basePct = pct;
    Wh_SetIntValue(L"BasePct", pct);
    HWND s = g_sliderHwnd;
    if (s) InvalidateRect(s, nullptr, FALSE);
}

// base opacity at width 0, fully opaque from half the monitor width, linear in between
static BYTE SuiteAlphaFor(HWND h) {
    RECT r;
    if (!GetWindowRect(h, &r)) return (BYTE)(255 * g_basePct / 100);
    int half = 960;
    MONITORINFO mi = { sizeof(mi) };
    HMONITOR mon = MonitorFromWindow(h, MONITOR_DEFAULTTONEAREST);
    if (mon && GetMonitorInfoW(mon, &mi)) half = (mi.rcMonitor.right - mi.rcMonitor.left) / 2;
    if (half < 1) half = 1;
    int w = SuClamp(r.right - r.left, 0, half);
    int pct = g_basePct + (100 - g_basePct) * w / half;
    return (BYTE)(255 * pct / 100);
}

// ---- task manager overlay ----

namespace tman {

// older SDKs don't have these
#ifndef PDH_MORE_DATA
#define PDH_MORE_DATA ((PDH_STATUS)0x800007D2L)
#endif
#ifndef PDH_CSTATUS_VALID_DATA
#define PDH_CSTATUS_VALID_DATA ((LONG)0x00000000L)
#endif

// rounded corners on win11, defined here so older headers still build
#ifndef DWMWA_WINDOW_CORNER_PREFERENCE
#define DWMWA_WINDOW_CORNER_PREFERENCE 33
#endif
#ifndef DWMWCP_ROUND
#define DWMWCP_ROUND 2
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

// ---- Constants ----

#define TRAY_ICON_ID        1
#define WM_TRAY_CALLBACK    (WM_USER + 1)
#define WM_TOGGLE_OVERLAY   (WM_USER + 2)
#define WM_TIMER_ID         1

#ifndef NIN_SELECT
#define NIN_SELECT          (WM_USER + 0)
#endif
#ifndef NIN_KEYSELECT
#define NIN_KEYSELECT       (WM_USER + 1)
#endif

// overlay size at 96 dpi, Sc() scales it
#define POPUP_WIDTH         444
#define RAIL_W              44
#define POPUP_HEIGHT        460
#define VISIBLE_ROWS        16

#define MAX_PROCESSES       1024
#define MAX_GROUPS          512
#define PROCESS_BUF_SIZE    (512 * 1024)

// retry gpu init every N ticks if it failed
#define GPU_RETRY_TICKS     30

#define MENU_OPEN_WINDHAWK   9000
#define MENU_TOGGLE          9004
#define MENU_PROC_END        9200
#define MENU_PROC_LOCATION   9202
#define MENU_INTERVAL_300MS  9100
#define MENU_INTERVAL_500MS  9101
#define MENU_INTERVAL_1S     9102
#define MENU_INTERVAL_3S     9103
#define MENU_RESET_POS       9005
#define MENU_COMPACT         9006
#define HOTKEY_ID            1
#define OPACITY_MIN          0

// fixed guid for the tray icon
static const GUID MICROMANAGER_TRAY_GUID =
    {0x3C1E9B52, 0x7A44, 0x4D0F, {0x8E, 0x21, 0xB6, 0x5D, 0x90, 0x4A, 0xC7, 0x13}};

// ---- NtQuerySystemInformation ----

#ifndef UNICODE_STRING
typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING;
#endif

typedef LONG NTSTATUS;

#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
#define SystemProcessInformation 5

typedef struct {
    ULONG NextEntryOffset;
    ULONG NumberOfThreads;
    LARGE_INTEGER WorkingSetPrivateSize;
    ULONG HardFaultCount;
    ULONG NumberOfThreadsHighWatermark;
    LARGE_INTEGER CycleTime;
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    UNICODE_STRING ImageName;
    LONG BasePriority;
    HANDLE UniqueProcessId;
    HANDLE InheritedFromUniqueProcessId;
    ULONG HandleCount;
    ULONG SessionId;
    ULONG_PTR Reserved1;
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
    LARGE_INTEGER ReadOperationCount;
    LARGE_INTEGER WriteOperationCount;
    LARGE_INTEGER OtherOperationCount;
    LARGE_INTEGER ReadTransferCount;
    LARGE_INTEGER WriteTransferCount;
    LARGE_INTEGER OtherTransferCount;
} MY_SYSTEM_PROCESS_INFO;

typedef NTSTATUS (WINAPI *NtQuerySystemInformation_t)(ULONG, PVOID, ULONG, PULONG);

// ---- Types ----

struct ProcessTarget { DWORD pid = 0; LONGLONG created = 0; WCHAR name[64] = {}; };

// one process sample
struct ProcSample {
    DWORD     pid;
    LONGLONG  created;
    LONGLONG  time;     // kernel + user time
    LONGLONG  delta;    // CPU time used since previous tick
    ULONGLONG ws;       // private working set, bytes
    DWORD     session;
    WCHAR     name[64];
};

// processes grouped by exe name
struct ProcGroup {
    WCHAR     name[64];
    int       count;
    double    cpu;      // percent of total CPU capacity
    ULONGLONG ram;      // bytes
    double    gpu;      // percent
    int       rank;     // old position, used while hovering
};

struct GpuProc { DWORD pid; double total; };

enum { PG_PROCESSES, PG_PERF, PG_HISTORY, PG_STARTUP, PG_USERS, PG_DETAILS, PG_SERVICES, PG_SETTINGS, PG_COUNT };

// table row, every list page uses these
struct TRow {
    WCHAR  key[128];     // selection key
    WCHAR  t[4][64];     // cell text
    double v[4];         // numeric sort values
    int    rank;
};

struct HistEntry { WCHAR name[64]; double sec; };

static void RefreshPage();
static int VisibleRows();

// ---- Globals ----

static HANDLE              g_trayThread   = nullptr;
static HWND                g_trayHwnd     = nullptr;
static HWND                g_popupHwnd    = nullptr;
static ULONGLONG           g_lastToggleTime = 0;
static HINSTANCE           g_hInstance    = nullptr;
static WCHAR               g_windhawkPath[MAX_PATH] = {};
static WCHAR               g_windhawkModPath[MAX_PATH] = {};
static WCHAR               g_ddoresDllPath[MAX_PATH] = {};

static DWORD               g_updateMs     = 1000;
static int                 g_opacityPct   = 85;

// opacity comes from the shared slider value
static int SharedOpacityRead() { return SuiteBasePct(); }
static void SharedOpacityWrite(int pct) { SuiteSetBase(pct); }
static bool                g_hasPos       = false;   // user has moved the overlay
static int                 g_posX         = 0;
static int                 g_posY         = 0;
static int                 g_sizeW        = POPUP_WIDTH;    // 96 dpi size, can be resized
static int                 g_sizeH        = POPUP_HEIGHT;
static int                 g_viewH        = POPUP_HEIGHT;   // current client height in pixels
static bool                g_draggingSlider = false;
static bool                g_inlineVals   = true;    // names only mode: values after the name
static bool                g_compact      = false;   // names only (no CPU/Memory/GPU columns)
static int                 g_dpi          = 96;
static ULONGLONG           g_totalPhys    = 0;

// header totals, -1 = n/a
static int                 g_totalCpu     = -1;
static int                 g_totalGpu     = -1;
static int                 g_totalRam     = -1;

// Page / list state
static int                 g_page         = PG_PROCESSES;
static bool                g_forceRebuild = true;
static ProcGroup           g_groups[MAX_GROUPS];
static int                 g_groupCount   = 0;
static double              g_lastTotalDelta = 0;
static TRow                g_rows[MAX_PROCESSES];
static int                 g_rowCount     = 0;
static WCHAR               g_tblOrder[MAX_PROCESSES][128];
static int                 g_tblOrderCount = 0;
static int                 g_tblSort[PG_COUNT] = { 1, 0, 1, 0, 2, 2, 0, 0 };
static int                 g_scroll       = 0;
static WCHAR               g_selName[128] = {};

static HistEntry           g_hist[MAX_GROUPS];
static int                 g_histCount    = 0;
#define PERF_SAMPLES 60
static int                 g_perf[3][PERF_SAMPLES];
static int                 g_perfCount    = 0;
static int                 g_perfPos      = 0;
static ULONGLONG           g_ramUsed      = 0;
static ULONGLONG           g_ramTotal     = 0;
static HFONT               g_hIconFont    = nullptr;

// GPU PDH handles
static PDH_HQUERY          g_gpuQuery     = nullptr;
static PDH_HCOUNTER        g_gpuCounter   = nullptr;
static int                 g_gpuRetryIn   = 0;

// per-pid gpu, tray thread only
static GpuProc             g_gpuProcs[MAX_PROCESSES];
static int                 g_gpuProcCount = 0;

static NtQuerySystemInformation_t g_ntQuery = nullptr;

// process samples, previous and current
static FILETIME            g_prevIdle     = {};
static FILETIME            g_prevKernel   = {};
static FILETIME            g_prevUser     = {};
static ProcSample          g_prevProcs[MAX_PROCESSES], g_curProcs[MAX_PROCESSES];
static int                 g_prevProcCount = 0;
static BOOL                g_hasPrevSample = FALSE;

static HICON               g_iconEnabled  = nullptr;
static HFONT               g_hPopupFont   = nullptr;
static int                 g_fontDpi      = 0;

static UINT                g_taskbarCreatedMsg = 0;
static WCHAR               g_lastTip[128] = {};

static HMODULE             g_hUxTheme     = nullptr;

// ---- DPI / Font helpers ----

static int Sc(int v) { return MulDiv(v, g_dpi, 96); }

static void EnsureFont() {
    if (g_hPopupFont && g_fontDpi == g_dpi) return;
    if (g_hPopupFont) { DeleteObject(g_hPopupFont); g_hPopupFont = nullptr; }
    if (g_hIconFont) { DeleteObject(g_hIconFont); g_hIconFont = nullptr; }
    g_hPopupFont = CreateFontW(-Sc(13), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
    g_hIconFont = CreateFontW(-Sc(16), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe MDL2 Assets");
    g_fontDpi = g_dpi;
}

// ---- Process / GPU sampling ----

static NtQuerySystemInformation_t GetNtQuery() {
    if (!g_ntQuery) {
        HMODULE h = GetModuleHandleW(L"ntdll.dll");
        if (h)
            g_ntQuery = (NtQuerySystemInformation_t)GetProcAddress(
                h, "NtQuerySystemInformation");
    }
    return g_ntQuery;
}

static int CollectProcessInfo(MY_SYSTEM_PROCESS_INFO** outBuf) {
    NtQuerySystemInformation_t NtQuery = GetNtQuery();
    if (!NtQuery) return 0;

    *outBuf = nullptr;

    for (int retry = 0; retry < 5; retry++) {
        ULONG bufSize = PROCESS_BUF_SIZE * (retry + 2);
        MY_SYSTEM_PROCESS_INFO* newBuf = (MY_SYSTEM_PROCESS_INFO*)realloc(*outBuf, bufSize);
        if (!newBuf) { free(*outBuf); *outBuf = nullptr; return 0; }
        *outBuf = newBuf;
        NTSTATUS status = NtQuery(SystemProcessInformation, *outBuf, bufSize, nullptr);
        if (status != STATUS_INFO_LENGTH_MISMATCH) {
            if (status < 0) {
                free(*outBuf);
                *outBuf = nullptr;
                return 0;
            }
            return 1;
        }
    }
    free(*outBuf);
    *outBuf = nullptr;
    return 0;
}

static void GetProcessDisplayName(MY_SYSTEM_PROCESS_INFO* p, WCHAR* outBuf, size_t maxLen) {
    if (p->ImageName.Buffer && p->ImageName.Length > 0) {
        wcsncpy_s(outBuf, maxLen, p->ImageName.Buffer,
            MIN(p->ImageName.Length / sizeof(WCHAR), maxLen - 1));
        outBuf[maxLen - 1] = L'\0';
    } else {
        DWORD pid = (DWORD)(ULONG_PTR)p->UniqueProcessId;
        if (pid == 0)
            wcscpy_s(outBuf, maxLen, L"System Idle Process");
        else if (pid == 4)
            wcscpy_s(outBuf, maxLen, L"System");
        else
            swprintf_s(outBuf, maxLen, L"PID %u", pid);
    }
}

static void InitGpuQuery() {
    if (g_gpuQuery) return;

    PDH_STATUS ps = PdhOpenQueryW(nullptr, 0, &g_gpuQuery);
    if (ps != ERROR_SUCCESS) {
        g_gpuQuery = nullptr;
        g_gpuRetryIn = GPU_RETRY_TICKS;
        return;
    }

    ps = PdhAddEnglishCounterW(g_gpuQuery,
        L"\\GPU Engine(*)\\Utilization Percentage", 0, &g_gpuCounter);
    if (ps != ERROR_SUCCESS) {
        PdhCloseQuery(g_gpuQuery);
        g_gpuQuery = nullptr;
        g_gpuCounter = nullptr;
        g_gpuRetryIn = GPU_RETRY_TICKS;
        return;
    }

    // first collect always returns 0, so do one now
    PdhCollectQueryData(g_gpuQuery);
}

// total gpu load 0-100, or -1. also fills g_gpuProcs
static int CollectGpuStats() {
    g_gpuProcCount = 0;

    if (!g_gpuQuery) {
        if (g_gpuRetryIn > 0) { g_gpuRetryIn--; return -1; }
        InitGpuQuery();
        if (!g_gpuQuery) return -1;
    }

    PdhCollectQueryData(g_gpuQuery);

    DWORD bufSize = 0;
    DWORD itemCount = 0;
    PDH_STATUS ps = PdhGetFormattedCounterArrayW(g_gpuCounter, PDH_FMT_DOUBLE,
        &bufSize, &itemCount, nullptr);
    if (ps != PDH_MORE_DATA || bufSize == 0 || itemCount == 0) return -1;

    PDH_FMT_COUNTERVALUE_ITEM_W* items = (PDH_FMT_COUNTERVALUE_ITEM_W*)malloc(bufSize);
    if (!items) return -1;

    ps = PdhGetFormattedCounterArrayW(g_gpuCounter, PDH_FMT_DOUBLE,
        &bufSize, &itemCount, items);
    if (ps != ERROR_SUCCESS) { free(items); return -1; }

    int procCount = 0;
    double grandTotal = 0;

    for (DWORD i = 0; i < itemCount; i++) {
        if (items[i].FmtValue.CStatus != PDH_CSTATUS_VALID_DATA) continue;

        double val = items[i].FmtValue.doubleValue;
        grandTotal += val;

        // Instance: "pid_1234_luid_0x00000000_phys_0_eng_0_enum_1"
        PCWSTR s = items[i].szName;
        if (wcsncmp(s, L"pid_", 4) != 0) continue;
        DWORD pid = 0;
        for (s += 4; *s >= L'0' && *s <= L'9'; s++)
            pid = pid * 10 + (*s - L'0');

        int j;
        for (j = 0; j < procCount; j++) {
            if (g_gpuProcs[j].pid == pid) { g_gpuProcs[j].total += val; break; }
        }
        if (j >= procCount && procCount < MAX_PROCESSES) {
            g_gpuProcs[procCount].pid = pid;
            g_gpuProcs[procCount].total = val;
            procCount++;
        }
    }
    free(items);

    g_gpuProcCount = procCount;
    if (grandTotal > 100.0) grandTotal = 100.0;
    return (int)(grandTotal + 0.5);
}

// ---- Grouping / sorting ----

static void ClampScroll() {
    int maxScroll = g_rowCount - VisibleRows();
    if (maxScroll < 0) maxScroll = 0;
    if (g_scroll > maxScroll) g_scroll = maxScroll;
    if (g_scroll < 0) g_scroll = 0;
}

static bool OverlayHovered() {
    if (!g_popupHwnd || !IsWindowVisible(g_popupHwnd)) return false;
    POINT pt; RECT rc;
    return GetCursorPos(&pt) && GetWindowRect(g_popupHwnd, &rc) && PtInRect(&rc, pt);
}

static void AddHistory(const WCHAR* name, LONGLONG delta100ns) {
    if (delta100ns <= 0) return;
    int i;
    for (i = 0; i < g_histCount; i++) if (_wcsicmp(g_hist[i].name, name) == 0) break;
    if (i == g_histCount) {
        if (g_histCount >= MAX_GROUPS) return;
        lstrcpynW(g_hist[i].name, name, 64);
        g_hist[i].sec = 0;
        g_histCount++;
    }
    g_hist[i].sec += (double)delta100ns / 1e7;
}

static void AppendPerf(int cpu, int gpu, int ram) {
    g_perf[0][g_perfPos] = cpu;
    g_perf[1][g_perfPos] = gpu;
    g_perf[2][g_perfPos] = ram;
    g_perfPos = (g_perfPos + 1) % PERF_SAMPLES;
    if (g_perfCount < PERF_SAMPLES) g_perfCount++;
}

static void BuildGroups(double totalDelta) {
    int n = 0;
    for (int i = 0; i < g_prevProcCount; i++) {
        const ProcSample& s = g_prevProcs[i];
        if (s.pid == 0) continue;   // System Idle Process

        double cpu = totalDelta > 0 ? 100.0 * (double)s.delta / totalDelta : 0.0;
        double gpu = 0.0;
        for (int j = 0; j < g_gpuProcCount; j++) {
            if (g_gpuProcs[j].pid == s.pid) { gpu = g_gpuProcs[j].total; break; }
        }

        int g;
        for (g = 0; g < n; g++) {
            if (_wcsicmp(g_groups[g].name, s.name) == 0) break;
        }
        if (g == n) {
            if (n >= MAX_GROUPS) continue;
            wcscpy_s(g_groups[n].name, s.name);
            g_groups[n].count = 0;
            g_groups[n].cpu = 0;
            g_groups[n].ram = 0;
            g_groups[n].gpu = 0;
            g_groups[n].rank = -1;
            n++;
        }
        g_groups[g].count++;
        g_groups[g].cpu += cpu;
        g_groups[g].ram += s.ws;
        g_groups[g].gpu += gpu;
        AddHistory(s.name, s.delta);
    }
    for (int i = 0; i < n; i++) {
        if (g_groups[i].gpu > 100.0) g_groups[i].gpu = 100.0;
    }
    g_groupCount = n;

    g_lastTotalDelta = totalDelta;
}

static ProcGroup* FindGroup(const WCHAR* name) {
    if (!name[0]) return nullptr;
    for (int i = 0; i < g_groupCount; i++) {
        if (_wcsicmp(g_groups[i].name, name) == 0) return &g_groups[i];
    }
    return nullptr;
}

// ---- Data refresh ----

// tray icon is off, set to true to get it back
static const bool kShowTrayIcon = false;

static void RefreshData() {
    int newTotalCpu = -1;
    int newTotalRam = -1;
    bool haveProcs = false;

    MEMORYSTATUSEX mem = {sizeof(mem)};
    if (GlobalMemoryStatusEx(&mem)) {
        newTotalRam = (int)mem.dwMemoryLoad;
        g_ramTotal = mem.ullTotalPhys;
        g_ramUsed = mem.ullTotalPhys - mem.ullAvailPhys;
    }

    FILETIME nowIdle = {}, nowKernel = {}, nowUser = {};
    BOOL systemTimesValid = GetSystemTimes(&nowIdle, &nowKernel, &nowUser);

    ULARGE_INTEGER ui, uk, uu, pi, pk, pu;
    ui.LowPart = nowIdle.dwLowDateTime;     ui.HighPart = nowIdle.dwHighDateTime;
    uk.LowPart = nowKernel.dwLowDateTime;   uk.HighPart = nowKernel.dwHighDateTime;
    uu.LowPart = nowUser.dwLowDateTime;     uu.HighPart = nowUser.dwHighDateTime;
    pi.LowPart = g_prevIdle.dwLowDateTime;  pi.HighPart = g_prevIdle.dwHighDateTime;
    pk.LowPart = g_prevKernel.dwLowDateTime; pk.HighPart = g_prevKernel.dwHighDateTime;
    pu.LowPart = g_prevUser.dwLowDateTime;  pu.HighPart = g_prevUser.dwHighDateTime;

    double totalDelta = (double)(uk.QuadPart - pk.QuadPart) + (double)(uu.QuadPart - pu.QuadPart);
    double idleDelta = (double)(ui.QuadPart - pi.QuadPart);

    if (systemTimesValid && g_hasPrevSample &&
        uk.QuadPart >= pk.QuadPart && uu.QuadPart >= pu.QuadPart &&
        ui.QuadPart >= pi.QuadPart && totalDelta > 0 && idleDelta <= totalDelta) {
        newTotalCpu = (int)(100.0 - 100.0 * idleDelta / totalDelta + 0.5);

        MY_SYSTEM_PROCESS_INFO* buf = nullptr;
        if (CollectProcessInfo(&buf) && buf) {
            MY_SYSTEM_PROCESS_INFO* p = buf;
            int count = 0;

            while (true) {
                DWORD pid = (DWORD)(ULONG_PTR)p->UniqueProcessId;
                LONGLONG curTime = p->KernelTime.QuadPart + p->UserTime.QuadPart;

                LONGLONG prevTime = 0;
                BOOL foundInPrev = FALSE;
                for (int i = 0; i < g_prevProcCount; i++) {
                    if (g_prevProcs[i].pid == pid && g_prevProcs[i].created == p->CreateTime.QuadPart) {
                        prevTime = g_prevProcs[i].time;
                        foundInPrev = TRUE;
                        break;
                    }
                }
                // skip processes we didn't see last tick, they'd show their whole lifetime cpu as one spike
                LONGLONG delta = (foundInPrev && pid != 0 && curTime >= prevTime) ? (curTime - prevTime) : 0;

                if (count < MAX_PROCESSES) {
                    g_curProcs[count].pid = pid;
                    g_curProcs[count].created = p->CreateTime.QuadPart;
                    g_curProcs[count].time = curTime;
                    g_curProcs[count].delta = delta;
                    g_curProcs[count].ws = (ULONGLONG)p->WorkingSetPrivateSize.QuadPart;
                    g_curProcs[count].session = p->SessionId;
                    GetProcessDisplayName(p, g_curProcs[count].name, 64);
                    count++;
                }

                if (p->NextEntryOffset == 0) break;
                p = (MY_SYSTEM_PROCESS_INFO*)((BYTE*)p + p->NextEntryOffset);
            }
            memcpy(g_prevProcs, g_curProcs, count * sizeof(ProcSample));
            g_prevProcCount = count;
            free(buf);
            haveProcs = true;
        }
    }

    if (systemTimesValid) {
        g_prevIdle = nowIdle; g_prevKernel = nowKernel; g_prevUser = nowUser;
        g_hasPrevSample = TRUE;
    } else {
        g_hasPrevSample = FALSE;
    }

    int newTotalGpu = CollectGpuStats();

    g_totalCpu = newTotalCpu;
    g_totalGpu = newTotalGpu;
    g_totalRam = newTotalRam;

    AppendPerf(newTotalCpu, newTotalGpu, newTotalRam);
    if (haveProcs) BuildGroups(totalDelta);
    RefreshPage();

    if (g_popupHwnd && IsWindowVisible(g_popupHwnd)) {
        InvalidateRect(g_popupHwnd, nullptr, FALSE);
    }

    // tooltip, only update when the numbers change
    if (g_trayHwnd && kShowTrayIcon) {
        WCHAR cpuS[8], gpuS[8], ramS[8], tip[128];
        if (newTotalCpu < 0) wcscpy_s(cpuS, L"--"); else swprintf_s(cpuS, L"%d%%", newTotalCpu);
        if (newTotalGpu < 0) wcscpy_s(gpuS, L"--"); else swprintf_s(gpuS, L"%d%%", newTotalGpu);
        if (newTotalRam < 0) wcscpy_s(ramS, L"--"); else swprintf_s(ramS, L"%d%%", newTotalRam);
        swprintf_s(tip, L"CPU %s   GPU %s   RAM %s", cpuS, gpuS, ramS);

        if (wcscmp(tip, g_lastTip) != 0) {
            wcscpy_s(g_lastTip, tip);
            NOTIFYICONDATAW nid = {sizeof(nid)};
            nid.hWnd     = (HWND)g_trayHwnd;
            nid.uID      = TRAY_ICON_ID;
            nid.uFlags   = NIF_TIP | NIF_GUID | NIF_SHOWTIP;
            nid.guidItem = MICROMANAGER_TRAY_GUID;
            lstrcpynW(nid.szTip, tip, 128);
            if (!Shell_NotifyIconW(NIM_MODIFY, &nid)) {
                g_lastTip[0] = L'\0';
            }
        }
    }
}

// ---- theme ----

static bool IsSystemDarkMode() {
    DWORD value = 1, size = sizeof(value);
    RegGetValueW(HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"AppsUseLightTheme", RRF_RT_REG_DWORD, nullptr, &value, &size);
    return value == 0;
}

static void ApplyContextMenuTheme(HWND hWnd, bool dark) {
    if (!g_hUxTheme) {
        g_hUxTheme = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    }
    if (!g_hUxTheme) return;
    using Fn135 = int(WINAPI*)(int);
    using Fn133 = bool(WINAPI*)(HWND, bool);
    using Fn136 = void(WINAPI*)();
    if (auto f = (Fn135)GetProcAddress(g_hUxTheme, MAKEINTRESOURCEA(135))) f(dark ? 2 : 0);
    if (auto f = (Fn133)GetProcAddress(g_hUxTheme, MAKEINTRESOURCEA(133))) f(hWnd, dark);
    if (auto f = (Fn136)GetProcAddress(g_hUxTheme, MAKEINTRESOURCEA(136))) f();
}

// ---- Process actions ----

static HANDLE OpenSampledProcess(const ProcessTarget& target, DWORD rights) {
    if (!target.pid || !target.created || target.pid == GetCurrentProcessId()) return nullptr;
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | rights, FALSE, target.pid);
    if (!process) return nullptr;
    FILETIME created, exited, kernel, user;
    ULARGE_INTEGER stamp;
    if (!GetProcessTimes(process, &created, &exited, &kernel, &user)) {
        CloseHandle(process);
        return nullptr;
    }
    stamp.LowPart = created.dwLowDateTime;
    stamp.HighPart = created.dwHighDateTime;
    if (stamp.QuadPart != (ULONGLONG)target.created ||
        WaitForSingleObject(process, 0) != WAIT_TIMEOUT) {
        CloseHandle(process);
        return nullptr;
    }
    return process;
}

static bool IsProtectedProcess(HANDLE process) {
    if (g_windhawkPath[0] != L'\0' || g_windhawkModPath[0] != L'\0') {
        WCHAR path[MAX_PATH];
        DWORD len = ARRAYSIZE(path);
        if (QueryFullProcessImageNameW(process, 0, path, &len)) {
            if (g_windhawkPath[0] != L'\0' && _wcsicmp(path, g_windhawkPath) == 0) return true;
            if (g_windhawkModPath[0] != L'\0' && _wcsicmp(path, g_windhawkModPath) == 0) return true;
        }
    }
    BOOL critical = FALSE;
    if (!IsProcessCritical(process, &critical) || critical) return true;
    HANDLE token = nullptr;
    if (!OpenProcessToken(process, TOKEN_QUERY, &token)) return true;
    BYTE storage[512];
    DWORD needed = 0;
    bool protectedAccount = true;
    if (GetTokenInformation(token, TokenUser, storage, sizeof(storage), &needed)) {
        PSID sid = reinterpret_cast<TOKEN_USER*>(storage)->User.Sid;
        protectedAccount = IsWellKnownSid(sid, WinLocalSystemSid) ||
            IsWellKnownSid(sid, WinLocalServiceSid) ||
            IsWellKnownSid(sid, WinNetworkServiceSid);
    }
    CloseHandle(token);
    return protectedAccount;
}

// ends all instances of an exe, like "End task" in task manager
// asks first
static void EndTaskByName(HWND popup, const WCHAR* nameIn) {
    WCHAR name[64];
    wcscpy_s(name, nameIn);

    DWORD shellPid = 0;
    HWND hShell = GetShellWindow();
    if (hShell) GetWindowThreadProcessId(hShell, &shellPid);

    if (_wcsicmp(name, L"explorer.exe") == 0) {
        MessageBoxW(popup,
            L"Ending Windows Explorer is not supported because it would close the shell and all desktop windows.",
            L"Taskman", MB_OK | MB_ICONWARNING | MB_SETFOREGROUND);
        return;
    }

    static ProcessTarget targets[MAX_PROCESSES];
    int n = 0;
    for (int i = 0; i < g_prevProcCount && n < MAX_PROCESSES; i++) {
        const ProcSample& s = g_prevProcs[i];
        if (s.pid == 0 || s.pid == 4 || s.pid == shellPid) continue;
        if (_wcsicmp(s.name, name) != 0) continue;
        targets[n].pid = s.pid;
        targets[n].created = s.created;
        wcscpy_s(targets[n].name, s.name);
        n++;
    }

    int endable = 0;
    for (int i = 0; i < n; i++) {
        HANDLE h = OpenSampledProcess(targets[i], PROCESS_TERMINATE | SYNCHRONIZE);
        if (h) {
            if (!IsProtectedProcess(h)) endable++;
            CloseHandle(h);
        }
    }
    if (endable == 0) {
        MessageBoxW(popup, L"This process is protected, has already exited, or access was denied.",
                    L"Taskman", MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND);
        return;
    }

    WCHAR prompt[256];
    if (endable == 1)
        swprintf_s(prompt, L"End %s?\nUnsaved work may be lost.", name);
    else
        swprintf_s(prompt, L"End all %d instances of %s?\nUnsaved work may be lost.", endable, name);

    if (MessageBoxW(popup, prompt, L"Confirm End Task",
                    MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2 | MB_SETFOREGROUND) != IDYES) {
        return;
    }

    for (int i = 0; i < n; i++) {
        HANDLE h = OpenSampledProcess(targets[i], PROCESS_TERMINATE | SYNCHRONIZE);
        if (h) {
            if (!IsProtectedProcess(h)) TerminateProcess(h, 1);
            CloseHandle(h);
        }
    }
}

static void OpenLocationByName(HWND popup, const WCHAR* nameIn) {
    WCHAR name[64];
    wcscpy_s(name, nameIn);
    for (int i = 0; i < g_prevProcCount; i++) {
        const ProcSample& s = g_prevProcs[i];
        if (s.pid == 0 || _wcsicmp(s.name, name) != 0) continue;
        ProcessTarget t;
        t.pid = s.pid;
        t.created = s.created;
        wcscpy_s(t.name, s.name);
        HANDLE process = OpenSampledProcess(t, SYNCHRONIZE);
        if (!process) continue;

        WCHAR path[32768];
        DWORD length = ARRAYSIZE(path);
        PIDLIST_ABSOLUTE item = nullptr;
        bool ok = QueryFullProcessImageNameW(process, 0, path, &length) &&
                  SUCCEEDED(SHParseDisplayName(path, nullptr, &item, 0, nullptr)) && item &&
                  SUCCEEDED(SHOpenFolderAndSelectItems(item, 0, nullptr, 0));
        if (item) CoTaskMemFree(item);
        CloseHandle(process);
        if (ok) return;
    }
    MessageBoxW(popup, L"The executable location is unavailable.", L"Taskman",
                MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND);
}

// ---- Layout ----

static int LayoutTotalsY() { return Sc(10); }
static int LayoutHeaderY() { return Sc(40); }
static bool IsTablePage(int p);
static int LayoutListY()   { return (g_compact && IsTablePage(g_page)) ? Sc(44) : Sc(64); }
static int LayoutRowH()    { return Sc(22); }
static int LayoutFootY()   { return g_viewH - Sc(36); }
static int VisibleRows() {
    int n = (LayoutFootY() - Sc(6) - LayoutListY()) / LayoutRowH();
    return n < 3 ? 3 : n;
}
static int RailW()         { return Sc(RAIL_W); }

static RECT ButtonRect(int W) {
    RECT r = { W - Sc(104), LayoutFootY(), W - Sc(12), LayoutFootY() + Sc(26) };
    return r;
}

// side rail, settings at the bottom
static RECT RailRect(int page, int H) {
    int rw = RailW();
    int y = (page == PG_SETTINGS) ? H - Sc(48) : Sc(8) + page * Sc(40);
    RECT r = { 0, y, rw, y + Sc(40) };
    return r;
}

static int RailHit(int x, int y, int H) {
    if (x < 0 || x >= RailW()) return -1;
    for (int p = 0; p < PG_COUNT; p++) {
        RECT r = RailRect(p, H);
        if (y >= r.top && y < r.bottom) return p;
    }
    return -1;
}

// table columns
struct PageDef { int ncol; PCWSTR hdr[4]; int w[4]; };
static const PageDef kPages[PG_COUNT] = {
    /* PROCESSES */ { 4, { L"Name", L"CPU", L"Memory", L"GPU" },     { 0, 56, 84, 56 } },
    /* PERF      */ { 0, { nullptr, nullptr, nullptr, nullptr },     { 0, 0, 0, 0 } },
    /* HISTORY   */ { 2, { L"Name", L"CPU time", nullptr, nullptr }, { 0, 90, 0, 0 } },
    /* STARTUP   */ { 3, { L"Name", L"Status", L"Source", nullptr }, { 0, 76, 76, 0 } },
    /* USERS     */ { 4, { L"User", L"Session", L"CPU", L"Memory" }, { 0, 60, 56, 84 } },
    /* DETAILS   */ { 4, { L"Name", L"PID", L"CPU", L"Memory" },     { 0, 56, 56, 84 } },
    /* SERVICES  */ { 3, { L"Name", L"Status", L"PID", nullptr },    { 0, 80, 56, 0 } },
    /* SETTINGS  */ { 0, { nullptr, nullptr, nullptr, nullptr },     { 0, 0, 0, 0 } },
};

static bool IsTablePage(int p) { return kPages[p].ncol > 0; }

// rights[c] = right edge of column c, nameR = right edge of the name column
static void TblCols(int page, int W, int* rights, int* nameR) {
    const PageDef& d = kPages[page];
    int x = W - Sc(16);
    for (int c = d.ncol - 1; c >= 1; c--) { rights[c] = x; x -= Sc(d.w[c]); }
    *nameR = x;
}

// column under a header click
static int TblHitCol(int page, int W, int x) {
    int rights[4] = {}, nameR = 0;
    TblCols(page, W, rights, &nameR);
    if (x < nameR) return 0;
    for (int c = 1; c < kPages[page].ncol; c++) {
        if (x < rights[c]) return c;
    }
    return kPages[page].ncol - 1;
}

// ---- settings page layout ----
static int SetY0() { return LayoutHeaderY() + Sc(14); }

static void SliderTrack(int W, int* left, int* right) {
    *left  = Sc(90);
    *right = W - Sc(70);
}

static int SliderThumbX(int W) {
    int l, r;
    SliderTrack(W, &l, &r);
    return l + (r - l) * (g_opacityPct - OPACITY_MIN) / (100 - OPACITY_MIN);
}

static bool SliderHit(int W, int x, int y) {
    int l, r;
    SliderTrack(W, &l, &r);
    return x >= l - Sc(8) && x <= r + Sc(8) && y >= SetY0() && y < SetY0() + Sc(26);
}

static RECT RefreshBtnRect(int i) {
    int y = SetY0() + Sc(44);
    RECT r = { Sc(90) + i * Sc(62), y, Sc(90) + i * Sc(62) + Sc(56), y + Sc(26) };
    return r;
}

static RECT CompactBtnRect() {
    int y = SetY0() + Sc(80);
    RECT r = { Sc(90), y, Sc(270), y + Sc(26) };
    return r;
}

static RECT InlineBtnRect() {
    int y = SetY0() + Sc(112);
    RECT r = { Sc(90), y, Sc(270), y + Sc(26) };
    return r;
}

static RECT ResetBtnRect() {
    int y = SetY0() + Sc(184);
    RECT r = { Sc(12), y, Sc(172), y + Sc(28) };
    return r;
}

static RECT OpenWhBtnRect() {
    int y = SetY0() + Sc(184);
    RECT r = { Sc(182), y, Sc(312), y + Sc(28) };
    return r;
}

static const DWORD kRefreshChoices[4] = { 300, 500, 1000, 3000 };

// ---- Formatting / drawing helpers ----

static void FmtPct(WCHAR* out, size_t n, double v) {
    if (v < 0.05)      wcscpy_s(out, n, L"0%");
    else if (v < 10.0) swprintf_s(out, n, L"%.1f%%", v);
    else               swprintf_s(out, n, L"%.0f%%", v);
}

static void FmtMem(WCHAR* out, size_t n, ULONGLONG bytes) {
    double mb = (double)bytes / (1024.0 * 1024.0);
    if (mb >= 1024.0) swprintf_s(out, n, L"%.1f GB", mb / 1024.0);
    else              swprintf_s(out, n, L"%.0f MB", mb);
}

static void FmtDuration(WCHAR* out, size_t n, double sec) {
    int s = (int)sec;
    if (s >= 3600) swprintf_s(out, n, L"%d:%02d:%02d", s / 3600, (s / 60) % 60, s % 60);
    else           swprintf_s(out, n, L"%d:%02d", s / 60, s % 60);
}

static void DrawTextBox(HDC hdc, PCWSTR text, int left, int top, int right, int height, UINT flags) {
    RECT r = { left, top, right, top + height };
    DrawTextW(hdc, text, -1, &r, flags | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
}

// ---- Generic table helpers ----

static TRow* AddRow(const WCHAR* key) {
    if (g_rowCount >= MAX_PROCESSES) return nullptr;
    TRow* r = &g_rows[g_rowCount++];
    memset(r, 0, sizeof(*r));
    lstrcpynW(r->key, key, 128);
    return r;
}

static TRow* FindRow(const WCHAR* key) {
    if (!key[0]) return nullptr;
    for (int i = 0; i < g_rowCount; i++) {
        if (wcscmp(g_rows[i].key, key) == 0) return &g_rows[i];
    }
    return nullptr;
}

// keepOrder: don't reshuffle the rows while the mouse is over the overlay
static void SortRows(bool keepOrder) {
    int col = g_tblSort[g_page];
    for (int i = 0; i < g_rowCount; i++) {
        g_rows[i].rank = -1;
        if (keepOrder) {
            for (int j = 0; j < g_tblOrderCount; j++) {
                if (wcscmp(g_tblOrder[j], g_rows[i].key) == 0) { g_rows[i].rank = j; break; }
            }
        }
    }
    std::sort(g_rows, g_rows + g_rowCount, [col](const TRow& a, const TRow& b) {
        if (a.rank >= 0 && b.rank >= 0) return a.rank < b.rank;
        if (a.rank >= 0) return true;
        if (b.rank >= 0) return false;
        if (col > 0 && a.v[col] != b.v[col]) return a.v[col] > b.v[col];
        return _wcsicmp(a.t[0], b.t[0]) < 0;
    });
    g_tblOrderCount = g_rowCount;
    for (int i = 0; i < g_rowCount; i++) lstrcpynW(g_tblOrder[i], g_rows[i].key, 128);
}

// ---- Page data builders ----

static void BuildProcessRows() {
    g_rowCount = 0;
    for (int i = 0; i < g_groupCount; i++) {
        const ProcGroup& g = g_groups[i];
        TRow* r = AddRow(g.name);
        if (!r) break;
        WCHAR tmp[96];
        if (g.count > 1) swprintf_s(tmp, L"%s (%d)", g.name, g.count);
        else             lstrcpynW(tmp, g.name, 96);
        lstrcpynW(r->t[0], tmp, 64);
        FmtPct(r->t[1], 64, g.cpu);   r->v[1] = g.cpu;
        FmtMem(r->t[2], 64, g.ram);   r->v[2] = (double)g.ram;
        FmtPct(r->t[3], 64, g.gpu);   r->v[3] = g.gpu;
    }
}

static void BuildDetails() {
    g_rowCount = 0;
    for (int i = 0; i < g_prevProcCount; i++) {
        const ProcSample& s = g_prevProcs[i];
        if (s.pid == 0) continue;
        WCHAR key[16];
        swprintf_s(key, L"%u", s.pid);
        TRow* r = AddRow(key);
        if (!r) break;
        double cpu = g_lastTotalDelta > 0 ? 100.0 * (double)s.delta / g_lastTotalDelta : 0.0;
        lstrcpynW(r->t[0], s.name, 64);
        swprintf_s(r->t[1], 64, L"%u", s.pid);   r->v[1] = (double)s.pid;
        FmtPct(r->t[2], 64, cpu);                r->v[2] = cpu;
        FmtMem(r->t[3], 64, s.ws);               r->v[3] = (double)s.ws;
    }
}

static void BuildUsers() {
    g_rowCount = 0;
    PWTS_SESSION_INFOW si = nullptr;
    DWORD n = 0;
    if (!WTSEnumerateSessionsW(WTS_CURRENT_SERVER_HANDLE, 0, 1, &si, &n) || !si) return;
    for (DWORD i = 0; i < n; i++) {
        LPWSTR user = nullptr;
        DWORD len = 0;
        if (!WTSQuerySessionInformationW(WTS_CURRENT_SERVER_HANDLE, si[i].SessionId,
                                         WTSUserName, &user, &len) || !user) continue;
        if (user[0]) {
            WCHAR key[16];
            swprintf_s(key, L"%u", si[i].SessionId);
            TRow* r = AddRow(key);
            if (r) {
                double cpu = 0;
                ULONGLONG ram = 0;
                for (int k = 0; k < g_prevProcCount; k++) {
                    if (g_prevProcs[k].pid == 0 || g_prevProcs[k].session != si[i].SessionId) continue;
                    if (g_lastTotalDelta > 0) cpu += 100.0 * (double)g_prevProcs[k].delta / g_lastTotalDelta;
                    ram += g_prevProcs[k].ws;
                }
                lstrcpynW(r->t[0], user, 64);
                swprintf_s(r->t[1], 64, L"%u", si[i].SessionId);   r->v[1] = (double)si[i].SessionId;
                FmtPct(r->t[2], 64, cpu);                          r->v[2] = cpu;
                FmtMem(r->t[3], 64, ram);                          r->v[3] = (double)ram;
            }
        }
        WTSFreeMemory(user);
    }
    WTSFreeMemory(si);
}

static void BuildHistory() {
    g_rowCount = 0;
    for (int i = 0; i < g_histCount; i++) {
        TRow* r = AddRow(g_hist[i].name);
        if (!r) break;
        lstrcpynW(r->t[0], g_hist[i].name, 64);
        FmtDuration(r->t[1], 64, g_hist[i].sec);
        r->v[1] = g_hist[i].sec;
    }
}

static void BuildServices() {
    g_rowCount = 0;
    SC_HANDLE scm = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ENUMERATE_SERVICE);
    if (!scm) return;
    DWORD need = 0, cnt = 0, resume = 0;
    EnumServicesStatusExW(scm, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
                          nullptr, 0, &need, &cnt, &resume, nullptr);
    if (need) {
        DWORD size = need + 8192;
        BYTE* buf = (BYTE*)malloc(size);
        resume = 0;
        if (buf && EnumServicesStatusExW(scm, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
                                         buf, size, &need, &cnt, &resume, nullptr)) {
            ENUM_SERVICE_STATUS_PROCESSW* e = (ENUM_SERVICE_STATUS_PROCESSW*)buf;
            for (DWORD i = 0; i < cnt; i++) {
                TRow* r = AddRow(e[i].lpServiceName);
                if (!r) break;
                lstrcpynW(r->t[0], e[i].lpDisplayName ? e[i].lpDisplayName : e[i].lpServiceName, 64);
                DWORD st = e[i].ServiceStatusProcess.dwCurrentState;
                PCWSTR txt = st == SERVICE_RUNNING ? L"Running" : st == SERVICE_STOPPED ? L"Stopped" :
                             st == SERVICE_PAUSED ? L"Paused" : st == SERVICE_START_PENDING ? L"Starting" :
                             st == SERVICE_STOP_PENDING ? L"Stopping" : L"...";
                lstrcpynW(r->t[1], txt, 64);
                r->v[1] = (double)st;
                DWORD pid = e[i].ServiceStatusProcess.dwProcessId;
                if (pid) swprintf_s(r->t[2], 64, L"%u", pid);
                r->v[2] = (double)pid;
            }
        }
        free(buf);
    }
    CloseServiceHandle(scm);
}

struct StartSrc { HKEY root; PCWSTR run; PCWSTR approved; PCWSTR label; };
static const StartSrc kStartSrc[3] = {
    { HKEY_CURRENT_USER,  L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
      L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved\\Run", L"User" },
    { HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
      L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved\\Run", L"System" },
    { HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Run",
      L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved\\Run32", L"System x86" },
};

static bool StartupEnabled(const StartSrc& s, const WCHAR* name) {
    bool enabled = true;
    HKEY k;
    if (RegOpenKeyExW(s.root, s.approved, 0, KEY_QUERY_VALUE, &k) == ERROR_SUCCESS) {
        BYTE data[16];
        DWORD sz = sizeof(data), type = 0;
        if (RegQueryValueExW(k, name, nullptr, &type, data, &sz) == ERROR_SUCCESS &&
            type == REG_BINARY && sz > 0) {
            enabled = ((data[0] & 1) == 0);   // 02/06 = enabled, 03/07 = disabled
        }
        RegCloseKey(k);
    }
    return enabled;
}

static void BuildStartup() {
    g_rowCount = 0;
    for (int si = 0; si < 3; si++) {
        HKEY k;
        if (RegOpenKeyExW(kStartSrc[si].root, kStartSrc[si].run, 0, KEY_QUERY_VALUE, &k) != ERROR_SUCCESS)
            continue;
        for (DWORD i = 0; ; i++) {
            WCHAR name[256];
            DWORD nl = 256;
            LONG rc = RegEnumValueW(k, i, name, &nl, nullptr, nullptr, nullptr, nullptr);
            if (rc == ERROR_NO_MORE_ITEMS) break;
            if (rc != ERROR_SUCCESS) continue;
            WCHAR key[128];
            key[0] = (WCHAR)(L'0' + si);
            key[1] = L'|';
            lstrcpynW(key + 2, name, 126);
            TRow* r = AddRow(key);
            if (!r) break;
            bool en = StartupEnabled(kStartSrc[si], name);
            lstrcpynW(r->t[0], name, 64);
            lstrcpynW(r->t[1], en ? L"Enabled" : L"Disabled", 64);
            lstrcpynW(r->t[2], kStartSrc[si].label, 64);
            r->v[1] = en ? 1.0 : 0.0;
            r->v[2] = (double)si;
        }
        RegCloseKey(k);
    }
}

// rebuild rows for the current page. services and startup change slowly,
// so they're only re-read every few ticks or when forced
static void RefreshPage() {
    static int tick = 0;
    tick++;
    bool force = g_forceRebuild;
    g_forceRebuild = false;

    bool rebuilt = true;
    switch (g_page) {
        case PG_PROCESSES: BuildProcessRows(); break;
        case PG_DETAILS:   BuildDetails();     break;
        case PG_USERS:     BuildUsers();       break;
        case PG_HISTORY:   BuildHistory();     break;
        case PG_SERVICES:  if (force || tick % 3 == 0) BuildServices(); else rebuilt = false; break;
        case PG_STARTUP:   if (force || tick % 5 == 0) BuildStartup();  else rebuilt = false; break;
        default:           rebuilt = false; g_rowCount = 0; break;
    }
    if (rebuilt) SortRows(OverlayHovered());
    ClampScroll();
}

// ---- Page actions ----

static void SaveIntervalMs(DWORD ms);
static void PositionOverlay();
static void ApplyOpacity();

static void Msg(HWND owner, PCWSTR text, UINT icon = MB_ICONINFORMATION) {
    MessageBoxW(owner, text, L"Taskman", MB_OK | icon | MB_SETFOREGROUND);
}

static bool FindSampleByPid(DWORD pid, ProcessTarget* out) {
    for (int i = 0; i < g_prevProcCount; i++) {
        const ProcSample& s = g_prevProcs[i];
        if (s.pid != pid || pid == 0) continue;
        out->pid = s.pid;
        out->created = s.created;
        lstrcpynW(out->name, s.name, 64);
        return true;
    }
    return false;
}

// details page, ends one process
static void EndTaskByPid(HWND popup, DWORD pid) {
    ProcessTarget t;
    DWORD shellPid = 0;
    HWND hShell = GetShellWindow();
    if (hShell) GetWindowThreadProcessId(hShell, &shellPid);
    if (!FindSampleByPid(pid, &t) || pid == 4 || pid == shellPid) {
        Msg(popup, L"This process cannot be ended from here.", MB_ICONWARNING);
        return;
    }
    HANDLE h = OpenSampledProcess(t, PROCESS_TERMINATE | SYNCHRONIZE);
    if (!h) { Msg(popup, L"The process has exited or access was denied."); return; }
    if (IsProtectedProcess(h)) {
        CloseHandle(h);
        Msg(popup, L"This process is protected.", MB_ICONWARNING);
        return;
    }
    WCHAR prompt[200];
    swprintf_s(prompt, L"End %s (PID %u)?\nUnsaved work may be lost.", t.name, pid);
    if (MessageBoxW(popup, prompt, L"Confirm End Task",
                    MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2 | MB_SETFOREGROUND) == IDYES &&
        WaitForSingleObject(h, 0) == WAIT_TIMEOUT) {
        TerminateProcess(h, 1);
    }
    CloseHandle(h);
}

static void OpenLocationByPid(HWND popup, DWORD pid) {
    ProcessTarget t;
    if (!FindSampleByPid(pid, &t)) { Msg(popup, L"The process has exited."); return; }
    OpenLocationByName(popup, t.name);
}

// act: 0 = start, 1 = stop, 2 = restart
static void ServiceAction(HWND popup, const WCHAR* name, int act) {
    if (act != 0) {
        if (MessageBoxW(popup, act == 1 ? L"Stop this service?" : L"Restart this service?",
                        L"Confirm service action",
                        MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2 | MB_SETFOREGROUND) != IDYES) return;
    }
    SC_HANDLE scm = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_CONNECT);
    SC_HANDLE svc = scm ? OpenServiceW(scm, name, SERVICE_START | SERVICE_STOP | SERVICE_QUERY_STATUS) : nullptr;
    if (!svc) {
        DWORD e = GetLastError();
        Msg(popup, e == ERROR_ACCESS_DENIED
            ? L"Administrator rights are required to control this service. Run Windhawk as administrator."
            : L"Could not open the service.", MB_ICONWARNING);
        if (scm) CloseServiceHandle(scm);
        return;
    }
    SERVICE_STATUS st;
    bool ok = true;
    if (act == 1 || act == 2) {
        if (!ControlService(svc, SERVICE_CONTROL_STOP, &st) && GetLastError() != ERROR_SERVICE_NOT_ACTIVE) {
            Msg(popup, L"Could not stop the service.", MB_ICONWARNING);
            ok = false;
        } else {
            for (int i = 0; i < 50; i++) {
                if (!QueryServiceStatus(svc, &st) || st.dwCurrentState == SERVICE_STOPPED) break;
                Sleep(100);
            }
        }
    }
    if (ok && (act == 0 || act == 2)) {
        if (!StartServiceW(svc, 0, nullptr) && GetLastError() != ERROR_SERVICE_ALREADY_RUNNING)
            Msg(popup, L"Could not start the service.", MB_ICONWARNING);
    }
    CloseServiceHandle(svc);
    CloseServiceHandle(scm);
    g_forceRebuild = true;
    RefreshPage();
}

static void ToggleStartup(HWND popup, const WCHAR* key, bool enable) {
    int si = key[0] - L'0';
    if (si < 0 || si > 2 || key[1] != L'|') return;
    HKEY k;
    if (RegCreateKeyExW(kStartSrc[si].root, kStartSrc[si].approved, 0, nullptr, 0,
                        KEY_SET_VALUE, nullptr, &k, nullptr) != ERROR_SUCCESS) {
        Msg(popup, L"Could not change this startup entry (administrator rights may be required).", MB_ICONWARNING);
        return;
    }
    BYTE data[12] = {};
    data[0] = enable ? 2 : 3;
    LONG rc = RegSetValueExW(k, key + 2, 0, REG_BINARY, data, sizeof(data));
    RegCloseKey(k);
    if (rc != ERROR_SUCCESS)
        Msg(popup, L"Could not change this startup entry (administrator rights may be required).", MB_ICONWARNING);
    g_forceRebuild = true;
    RefreshPage();
}

static void SetPage(HWND hWnd, int page) {
    if (page < 0 || page >= PG_COUNT) return;
    g_page = page;
    g_scroll = 0;
    g_selName[0] = L'\0';
    g_tblOrderCount = 0;
    g_forceRebuild = true;
    RefreshPage();
    InvalidateRect(hWnd, nullptr, FALSE);
}

static void SetRefreshMs(DWORD ms) {
    if (ms == g_updateMs || !g_trayHwnd) return;
    g_updateMs = ms;
    KillTimer(g_trayHwnd, WM_TIMER_ID);
    SetTimer(g_trayHwnd, WM_TIMER_ID, ms, nullptr);
    SaveIntervalMs(ms);
}

static void OpenWindhawk() {
    if (g_windhawkPath[0] == L'\0') return;
    SHELLEXECUTEINFOW sei = {sizeof(sei)};
    sei.lpFile = g_windhawkPath;
    sei.nShow  = SW_SHOWNORMAL;
    ShellExecuteExW(&sei);
}

static void SetCompact(bool on) {
    g_compact = on;
    Wh_SetIntValue(L"Compact", on ? 1 : 0);
    ClampScroll();
    if (g_popupHwnd) InvalidateRect(g_popupHwnd, nullptr, FALSE);
}

// sort button in the footer cycles through the heavy columns (cpu / memory / gpu)
static int MetricCols(int page, int* cols) {
    switch (page) {
        case PG_PROCESSES: cols[0] = 1; cols[1] = 2; cols[2] = 3; return 3;
        case PG_DETAILS:
        case PG_USERS:     cols[0] = 2; cols[1] = 3; return 2;
        default:           return 0;
    }
}

static RECT SortBtnRect() {
    RECT r = { Sc(12), LayoutFootY(), Sc(142), LayoutFootY() + Sc(26) };
    return r;
}

static void CycleSort(HWND hWnd) {
    int cols[3];
    int n = MetricCols(g_page, cols);
    if (!n) return;
    int cur = g_tblSort[g_page], next = cols[0];
    for (int i = 0; i < n; i++) {
        if (cols[i] == cur) { next = cols[(i + 1) % n]; break; }
    }
    g_tblSort[g_page] = next;
    if (g_page == PG_PROCESSES) Wh_SetIntValue(L"SortCol", next);
    g_scroll = 0;
    SortRows(false);
    InvalidateRect(hWnd, nullptr, FALSE);
}

static void ResetPosition() {
    g_hasPos = false;
    g_sizeW = POPUP_WIDTH;
    g_sizeH = POPUP_HEIGHT;
    Wh_SetIntValue(L"PosSet", 0);
    Wh_SetIntValue(L"SizeW", g_sizeW);
    Wh_SetIntValue(L"SizeH", g_sizeH);
    if (g_popupHwnd && IsWindowVisible(g_popupHwnd)) PositionOverlay();
}

// footer button, depends on the page
static PCWSTR FooterLabel() {
    TRow* r = FindRow(g_selName);
    switch (g_page) {
        case PG_PROCESSES:
        case PG_DETAILS:   return L"End task";
        case PG_SERVICES:  return (r && r->v[1] == SERVICE_RUNNING) ? L"Stop" : L"Start";
        case PG_STARTUP:   return (r && r->v[1] > 0.5) ? L"Disable" : L"Enable";
        case PG_HISTORY:   return L"Reset";
        default:           return nullptr;
    }
}

static bool FooterEnabled() {
    if (g_page == PG_HISTORY) return true;
    return FooterLabel() != nullptr && FindRow(g_selName) != nullptr;
}

static void DoFooterAction(HWND hWnd) {
    if (!FooterEnabled()) return;
    TRow* r = FindRow(g_selName);
    WCHAR key[128];
    lstrcpynW(key, g_selName, 128);
    switch (g_page) {
        case PG_PROCESSES: EndTaskByName(hWnd, key); break;
        case PG_DETAILS:   EndTaskByPid(hWnd, (DWORD)wcstoul(key, nullptr, 10)); break;
        case PG_SERVICES:  ServiceAction(hWnd, key, (r && r->v[1] == SERVICE_RUNNING) ? 1 : 0); break;
        case PG_STARTUP:   ToggleStartup(hWnd, key, !(r && r->v[1] > 0.5)); break;
        case PG_HISTORY:   g_histCount = 0; RefreshPage(); break;
    }
    InvalidateRect(hWnd, nullptr, FALSE);
}

// ---- Painting ----

static const COLORREF kWhite = RGB(255, 255, 255);
static const COLORREF kDim   = RGB(140, 140, 140);
static const COLORREF kLine  = RGB(64, 64, 64);
static const COLORREF kAccent = RGB(76, 194, 255);
static const COLORREF kMetricColors[3] = { RGB(0, 200, 255), RGB(0, 220, 100), RGB(255, 180, 70) };

// rail icons (Segoe MDL2 glyphs)
static const WCHAR kRailGlyph[PG_COUNT] = {
    0xE71D,  // Processes
    0xE9D9,  // Performance
    0xE81C,  // App history
    0xE7E8,  // Startup apps
    0xE716,  // Users
    0xE8FD,  // Details
    0xE895,  // Services
    0xE713,  // Settings
};

static void FillRectColor(HDC hdc, const RECT& r, COLORREF c) {
    HBRUSH b = CreateSolidBrush(c);
    FillRect(hdc, &r, b);
    DeleteObject(b);
}

static void PaintRail(HDC hdc, int H) {
    RECT rail = { 0, 0, RailW(), H };
    FillRectColor(hdc, rail, RGB(24, 24, 24));

    HFONT old = (HFONT)SelectObject(hdc, g_hIconFont);
    for (int p = 0; p < PG_COUNT; p++) {
        RECT r = RailRect(p, H);
        if (p == g_page) {
            RECT sel = { r.left + Sc(4), r.top + Sc(3), r.right - Sc(4), r.bottom - Sc(3) };
            FillRectColor(hdc, sel, RGB(48, 48, 48));
            RECT bar = { r.left + Sc(3), r.top + Sc(11), r.left + Sc(6), r.bottom - Sc(11) };
            FillRectColor(hdc, bar, kAccent);
        }
        WCHAR g[2] = { kRailGlyph[p], 0 };
        SetTextColor(hdc, p == g_page ? kWhite : RGB(200, 200, 200));
        DrawTextBox(hdc, g, r.left, r.top, r.right, r.bottom - r.top, DT_CENTER);
    }
    SelectObject(hdc, old);

    HPEN pen = CreatePen(PS_SOLID, 1, kLine);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    MoveToEx(hdc, RailW(), 0, nullptr);
    LineTo(hdc, RailW(), H);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

static void PaintTotals(HDC hdc, int W) {
    static const PCWSTR kLabels[3] = { L"CPU", L"GPU", L"RAM" };
    int totals[3] = { g_totalCpu, g_totalGpu, g_totalRam };
    int segW = (W - Sc(24)) / 3;
    for (int i = 0; i < 3; i++) {
        int x = Sc(12) + i * segW;
        SetTextColor(hdc, kWhite);
        DrawTextBox(hdc, kLabels[i], x, LayoutTotalsY(), x + Sc(40), Sc(26), DT_LEFT);
        WCHAR buf[16];
        if (totals[i] < 0) wcscpy_s(buf, L"--"); else swprintf_s(buf, L"%d%%", totals[i]);
        SetTextColor(hdc, kMetricColors[i]);
        DrawTextBox(hdc, buf, x + Sc(38), LayoutTotalsY(), x + segW, Sc(26), DT_LEFT);
    }
}

static void PaintTable(HDC hdc, int W) {
    const PageDef& d = kPages[g_page];
    int rights[4] = {}, nameR = 0;
    TblCols(g_page, W, rights, &nameR);
    if (g_compact) nameR = W - Sc(16);

    // header
    if (!g_compact) {
    int hy = LayoutHeaderY(), hh = Sc(22);
    for (int c = 0; c < d.ncol; c++) {
        WCHAR lab[64];
        if (g_tblSort[g_page] == c)
            swprintf_s(lab, L"%s %s", d.hdr[c], c == 0 ? L"\x25B2" : L"\x25BC");
        else
            lstrcpynW(lab, d.hdr[c], 64);
        SetTextColor(hdc, g_tblSort[g_page] == c ? kWhite : kDim);
        if (c == 0) DrawTextBox(hdc, lab, Sc(12), hy, nameR, hh, DT_LEFT);
        else        DrawTextBox(hdc, lab, rights[c] - Sc(90), hy, rights[c], hh, DT_RIGHT);
    }
    HPEN pen = CreatePen(PS_SOLID, 1, kLine);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    MoveToEx(hdc, Sc(8), LayoutListY() - Sc(2), nullptr);
    LineTo(hdc, W - Sc(8), LayoutListY() - Sc(2));
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    }

    // rows
    int rowH = LayoutRowH();
    for (int i = 0; i < VisibleRows(); i++) {
        int idx = g_scroll + i;
        if (idx >= g_rowCount) break;
        const TRow& r = g_rows[idx];
        int y = LayoutListY() + i * rowH;
        if (g_selName[0] && wcscmp(r.key, g_selName) == 0) {
            RECT sel = { Sc(6), y, W - Sc(10), y + rowH };
            FillRectColor(hdc, sel, RGB(52, 72, 98));
        }
        SetTextColor(hdc, kWhite);
        DrawTextBox(hdc, r.t[0], Sc(12), y, nameR + Sc(2), rowH, DT_LEFT | DT_END_ELLIPSIS);
        if (g_compact && g_inlineVals && d.ncol > 1) {
            SIZE sz = {};
            GetTextExtentPoint32W(hdc, r.t[0], (int)wcslen(r.t[0]), &sz);
            WCHAR vals[200];
            vals[0] = L'\0';
            int first = (g_page == PG_DETAILS || g_page == PG_USERS) ? 2 : 1;   // skip PID / session
            for (int c = first; c < d.ncol; c++) {
                if (!r.t[c][0]) continue;
                if (vals[0]) wcscat_s(vals, 200, L"  \x00B7  ");
                wcscat_s(vals, 200, r.t[c]);
            }
            int vx = Sc(12) + sz.cx + Sc(12);
            if (vals[0] && vx < W - Sc(24)) {
                SetTextColor(hdc, kDim);
                DrawTextBox(hdc, vals, vx, y, W - Sc(16), rowH, DT_LEFT | DT_END_ELLIPSIS);
            }
        }
        for (int c = 1; !g_compact && c < d.ncol; c++) {
            SetTextColor(hdc, wcscmp(r.t[c], L"0%") == 0 ? kDim : kWhite);
            DrawTextBox(hdc, r.t[c], rights[c] - Sc(90), y, rights[c], rowH, DT_RIGHT);
        }
    }
    if (g_rowCount == 0) {
        SetTextColor(hdc, kDim);
        DrawTextBox(hdc, L"Nothing to show", Sc(12), LayoutListY(), W - Sc(12), rowH, DT_LEFT);
    }

    // scrollbar thumb
    if (g_rowCount > VisibleRows()) {
        int listH = VisibleRows() * rowH;
        int thumbH = std::max(Sc(16), listH * VisibleRows() / g_rowCount);
        int range = g_rowCount - VisibleRows();
        int thumbY = LayoutListY() + (listH - thumbH) * g_scroll / range;
        RECT r = { W - Sc(7), thumbY, W - Sc(4), thumbY + thumbH };
        FillRectColor(hdc, r, RGB(100, 100, 100));
    }
}

static void PaintPerf(HDC hdc, int W) {
    int top = LayoutHeaderY();
    int bottom = LayoutFootY() + Sc(26);
    int ph = (bottom - top - Sc(8)) / 3;
    static const PCWSTR kNames[3] = { L"CPU", L"GPU", L"Memory" };
    for (int i = 0; i < 3; i++) {
        int py = top + i * (ph + Sc(4));
        int cur = g_perfCount > 0 ? g_perf[i][(g_perfPos + PERF_SAMPLES - 1) % PERF_SAMPLES] : -1;
        WCHAR lab[80];
        if (cur < 0) swprintf_s(lab, L"%s   --", kNames[i]);
        else if (i == 2 && g_ramTotal)
            swprintf_s(lab, L"%s   %d%%   (%.1f / %.1f GB)", kNames[i], cur,
                       (double)g_ramUsed / 1073741824.0, (double)g_ramTotal / 1073741824.0);
        else swprintf_s(lab, L"%s   %d%%", kNames[i], cur);
        SetTextColor(hdc, kMetricColors[i]);
        DrawTextBox(hdc, lab, Sc(12), py, W - Sc(12), Sc(20), DT_LEFT);

        int gx = Sc(12), gy = py + Sc(22), gw = W - Sc(24), gh = ph - Sc(26);
        RECT box = { gx, gy, gx + gw, gy + gh };
        FillRectColor(hdc, box, RGB(42, 42, 42));
        RECT mid = { gx, gy + gh / 2, gx + gw, gy + gh / 2 + 1 };
        FillRectColor(hdc, mid, RGB(58, 58, 58));

        HBRUSH bar = CreateSolidBrush(kMetricColors[i]);
        int n = g_perfCount;
        for (int k = 0; k < n; k++) {
            int v = g_perf[i][(g_perfPos + PERF_SAMPLES - n + k) % PERF_SAMPLES];
            if (v < 0) continue;
            int x1 = gx + (PERF_SAMPLES - n + k) * gw / PERF_SAMPLES;
            int x2 = gx + (PERF_SAMPLES - n + k + 1) * gw / PERF_SAMPLES - 1;
            int h = std::max(1, std::min(100, v) * gh / 100);
            RECT b = { x1, gy + gh - h, x2, gy + gh };
            FillRect(hdc, &b, bar);
        }
        DeleteObject(bar);
    }
}

static void DrawButton(HDC hdc, const RECT& b, PCWSTR text, COLORREF bg, COLORREF fg) {
    FillRectColor(hdc, b, bg);
    SetTextColor(hdc, fg);
    DrawTextBox(hdc, text, b.left, b.top, b.right, b.bottom - b.top, DT_CENTER);
}

static void PaintSettings(HDC hdc, int W) {
    int y0 = SetY0();

    SetTextColor(hdc, kWhite);
    DrawTextBox(hdc, L"Opacity", Sc(12), y0, Sc(86), Sc(26), DT_LEFT);
    int tl, tr;
    SliderTrack(W, &tl, &tr);
    int cy = y0 + Sc(13), tx = SliderThumbX(W);
    RECT track = { tl, cy - Sc(2), tr, cy + Sc(2) };
    FillRectColor(hdc, track, RGB(75, 75, 75));
    RECT fill = { tl, cy - Sc(2), tx, cy + Sc(2) };
    FillRectColor(hdc, fill, RGB(0, 160, 220));
    RECT th = { tx - Sc(5), cy - Sc(9), tx + Sc(5), cy + Sc(9) };
    FillRectColor(hdc, th, RGB(235, 235, 235));
    WCHAR pct[16];
    swprintf_s(pct, L"%d%%", g_opacityPct);
    DrawTextBox(hdc, pct, tr + Sc(10), y0, W - Sc(4), Sc(26), DT_LEFT);

    DrawTextBox(hdc, L"Refresh", Sc(12), y0 + Sc(44), Sc(86), Sc(26), DT_LEFT);
    static const PCWSTR kRefLabels[4] = { L"0.3 s", L"0.5 s", L"1 s", L"3 s" };
    for (int i = 0; i < 4; i++) {
        bool cur = (g_updateMs == kRefreshChoices[i]);
        DrawButton(hdc, RefreshBtnRect(i), kRefLabels[i], cur ? RGB(0, 110, 170) : RGB(55, 55, 55), kWhite);
    }

    SetTextColor(hdc, kWhite);
    DrawTextBox(hdc, L"View", Sc(12), y0 + Sc(80), Sc(86), Sc(26), DT_LEFT);
    DrawButton(hdc, CompactBtnRect(), g_compact ? L"Names only: on" : L"Names only: off",
               g_compact ? RGB(0, 110, 170) : RGB(55, 55, 55), kWhite);
    DrawButton(hdc, InlineBtnRect(), g_inlineVals ? L"Values after names: on" : L"Values after names: off",
               g_inlineVals ? RGB(0, 110, 170) : RGB(55, 55, 55), kWhite);

    SetTextColor(hdc, kDim);
    RECT hint = { Sc(12), y0 + Sc(146), W - Sc(12), y0 + Sc(180) };
    DrawTextW(hdc, L"Ctrl+Num 3 shows / hides, Shift+Num 3 saves the position. Drag the top strip to move (double-click: names only), the edges to resize.",
              -1, &hint, DT_LEFT | DT_WORDBREAK | DT_NOPREFIX);

    DrawButton(hdc, ResetBtnRect(), L"Reset position & size", RGB(55, 55, 55), kWhite);
    DrawButton(hdc, OpenWhBtnRect(), L"Open Windhawk", RGB(55, 55, 55), kWhite);

    SetTextColor(hdc, kDim);
    DrawTextBox(hdc, L"Taskman by Resetti", Sc(12), y0 + Sc(232), W - Sc(12), Sc(26), DT_LEFT);
}

static void PaintFooter(HDC hdc, int W) {
    PCWSTR label = FooterLabel();
    if (!IsTablePage(g_page) && g_page != PG_HISTORY) return;
    WCHAR buf[64];
    swprintf_s(buf, g_page == PG_PROCESSES ? L"%d apps/processes" : L"%d items", g_rowCount);
    SetTextColor(hdc, kDim);
    int mc[3];
    int textX = Sc(12);
    if (MetricCols(g_page, mc) > 0) {
        WCHAR sl[64];
        int col = g_tblSort[g_page];
        if (col > 0) swprintf_s(sl, L"Heaviest: %s \x25BC", kPages[g_page].hdr[col]);
        else         wcscpy_s(sl, L"Sort: name");
        DrawButton(hdc, SortBtnRect(), sl, RGB(55, 55, 55), kWhite);
        textX = Sc(150);
    }
    DrawTextBox(hdc, buf, textX, LayoutFootY(), W - Sc(110), Sc(26), DT_LEFT);
    if (label) {
        bool en = FooterEnabled();
        DrawButton(hdc, ButtonRect(W), label, en ? RGB(120, 45, 45) : RGB(50, 50, 50), en ? kWhite : kDim);
    }
}

static void PaintOverlay(HDC hdc, int W, int H) {
    EnsureFont();
    RECT all = { 0, 0, W, H };
    FillRectColor(hdc, all, RGB(32, 32, 32));
    SetBkMode(hdc, TRANSPARENT);
    HFONT oldFont = (HFONT)SelectObject(hdc, g_hPopupFont);

    PaintRail(hdc, H);

    SetViewportOrgEx(hdc, RailW(), 0, nullptr);
    int cw = W - RailW();
    PaintTotals(hdc, cw);
    if (IsTablePage(g_page)) PaintTable(hdc, cw);
    else if (g_page == PG_PERF) PaintPerf(hdc, cw);
    else if (g_page == PG_SETTINGS) PaintSettings(hdc, cw);
    PaintFooter(hdc, cw);
    SetViewportOrgEx(hdc, 0, 0, nullptr);

    HPEN borderPen = CreatePen(PS_SOLID, 1, kLine);
    HPEN oldPen = (HPEN)SelectObject(hdc, borderPen);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Rectangle(hdc, 0, 0, W, H);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(borderPen);
    SelectObject(hdc, oldFont);
}

// ---- Overlay window ----

static void SetOpacityFromX(HWND hWnd, int cx) {
    RECT rc;
    GetClientRect(hWnd, &rc);
    int l, r;
    SliderTrack(rc.right - RailW(), &l, &r);
    int pct = OPACITY_MIN + (cx - l) * (100 - OPACITY_MIN) / (r - l);
    if (pct < OPACITY_MIN) pct = OPACITY_MIN;
    if (pct > 100) pct = 100;
    if (pct != g_opacityPct) {
        g_opacityPct = pct;
        SharedOpacityWrite(pct);
        ApplyOpacity();
        InvalidateRect(hWnd, nullptr, FALSE);
    }
}

static void ShowRowMenu(HWND popup, POINT point) {
    TRow* row = FindRow(g_selName);
    if (!row) return;
    WCHAR key[128], title[64];
    lstrcpynW(key, g_selName, 128);
    lstrcpynW(title, row->t[0], 64);
    bool running = (row->v[1] == SERVICE_RUNNING);
    bool enabled = row->v[1] > 0.5;

    HMENU menu = CreatePopupMenu();
    if (!menu) return;
    AppendMenuW(menu, MF_STRING | MF_DISABLED, 0, title);
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    switch (g_page) {
        case PG_PROCESSES:
        case PG_DETAILS:
            AppendMenuW(menu, MF_STRING, 1, L"End task");
            AppendMenuW(menu, MF_STRING, 2, L"Open file location");
            break;
        case PG_SERVICES:
            AppendMenuW(menu, MF_STRING | (running ? MF_GRAYED : 0), 3, L"Start");
            AppendMenuW(menu, MF_STRING | (running ? 0 : MF_GRAYED), 4, L"Stop");
            AppendMenuW(menu, MF_STRING | (running ? 0 : MF_GRAYED), 5, L"Restart");
            break;
        case PG_STARTUP:
            AppendMenuW(menu, MF_STRING, 6, enabled ? L"Disable" : L"Enable");
            break;
        default:
            DestroyMenu(menu);
            return;
    }

    ApplyContextMenuTheme(popup, IsSystemDarkMode());
    SetForegroundWindow(popup);
    UINT action = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, 0, popup, nullptr);
    PostMessageW(popup, WM_NULL, 0, 0);
    DestroyMenu(menu);

    DWORD pid = (DWORD)wcstoul(key, nullptr, 10);
    switch (action) {
        case 1: if (g_page == PG_PROCESSES) EndTaskByName(popup, key); else EndTaskByPid(popup, pid); break;
        case 2: if (g_page == PG_PROCESSES) OpenLocationByName(popup, key); else OpenLocationByPid(popup, pid); break;
        case 3: ServiceAction(popup, key, 0); break;
        case 4: ServiceAction(popup, key, 1); break;
        case 5: ServiceAction(popup, key, 2); break;
        case 6: ToggleStartup(popup, key, !enabled); break;
    }
    InvalidateRect(popup, nullptr, FALSE);
}

static int RowAtY(int y) {
    if (y < LayoutListY() || y >= LayoutListY() + VisibleRows() * LayoutRowH()) return -1;
    int idx = g_scroll + (y - LayoutListY()) / LayoutRowH();
    return (idx >= 0 && idx < g_rowCount) ? idx : -1;
}

static void HandleSettingsClick(HWND hWnd, int cx, int y, int W) {
    if (SliderHit(W, cx, y)) {
        g_draggingSlider = true;
        SetCapture(hWnd);
        SetOpacityFromX(hWnd, cx);
        return;
    }
    POINT pt = { cx, y };
    for (int i = 0; i < 4; i++) {
        RECT r = RefreshBtnRect(i);
        if (PtInRect(&r, pt)) { SetRefreshMs(kRefreshChoices[i]); InvalidateRect(hWnd, nullptr, FALSE); return; }
    }
    RECT rin = InlineBtnRect();
    if (PtInRect(&rin, pt)) {
        g_inlineVals = !g_inlineVals;
        Wh_SetIntValue(L"InlineVals", g_inlineVals ? 1 : 0);
        InvalidateRect(hWnd, nullptr, FALSE);
        return;
    }
    RECT rcm = CompactBtnRect();
    if (PtInRect(&rcm, pt)) { SetCompact(!g_compact); return; }
    RECT rr = ResetBtnRect();
    if (PtInRect(&rr, pt)) { ResetPosition(); return; }
    RECT ro = OpenWhBtnRect();
    if (PtInRect(&ro, pt)) OpenWindhawk();
}

static void SavePlacement() {
    RECT r;
    if (!g_popupHwnd || !GetWindowRect(g_popupHwnd, &r)) { MessageBeep(MB_ICONEXCLAMATION); return; }
    g_hasPos = true;
    g_posX = r.left;
    g_posY = r.top;
    g_sizeW = std::max(RAIL_W + 180, (int)MulDiv(r.right - r.left, 96, g_dpi));
    g_sizeH = std::max(300, (int)MulDiv(r.bottom - r.top, 96, g_dpi));
    Wh_SetIntValue(L"SizeW", g_sizeW);
    Wh_SetIntValue(L"SizeH", g_sizeH);
    Wh_SetIntValue(L"PosSet", 1);
    Wh_SetIntValue(L"PosX", g_posX);
    Wh_SetIntValue(L"PosY", g_posY);
    MessageBeep(MB_OK);
}

static LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;

        case WM_ERASEBKGND:
            return 1;

        case WM_NCLBUTTONDBLCLK:
            if (wParam == HTCAPTION) { SetCompact(!g_compact); return 0; }
            break;

        case WM_NCHITTEST: {
            // drag the overlay by the top strip
            POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            ScreenToClient(hWnd, &pt);
            RECT crc;
            GetClientRect(hWnd, &crc);
            int e = Sc(6);
            bool onL = pt.x < e, onR = pt.x >= crc.right - e, onB = pt.y >= crc.bottom - e;
            if (onB && onL) return HTBOTTOMLEFT;
            if (onB && onR) return HTBOTTOMRIGHT;
            if (onB) return HTBOTTOM;
            if (onL) return HTLEFT;
            if (onR) return HTRIGHT;
            if (pt.x >= RailW() && pt.y < LayoutHeaderY()) return HTCAPTION;
            return HTCLIENT;
        }

        case WM_GETMINMAXINFO: {
            MINMAXINFO* mm = (MINMAXINFO*)lParam;
            mm->ptMinTrackSize.x = Sc(RAIL_W + (g_compact ? 180 : 300));
            mm->ptMinTrackSize.y = Sc(300);
            return 0;
        }

        case WM_SIZE:
            g_viewH = HIWORD(lParam);
            ApplyOpacity();   // opacity depends on the width
            ClampScroll();
            InvalidateRect(hWnd, nullptr, FALSE);
            return 0;

        case WM_EXITSIZEMOVE:
            return 0;   // position is saved with Shift+Num 3

        case WM_DISPLAYCHANGE:
        case WM_SETTINGCHANGE:
            if (IsWindowVisible(hWnd)) PositionOverlay();
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdcWin = BeginPaint(hWnd, &ps);
            RECT rc;
            GetClientRect(hWnd, &rc);
            int W = rc.right, H = rc.bottom;
            HDC hdc = CreateCompatibleDC(hdcWin);   // double buffered
            HBITMAP bmp = CreateCompatibleBitmap(hdcWin, W, H);
            HGDIOBJ oldBmp = SelectObject(hdc, bmp);
            PaintOverlay(hdc, W, H);
            BitBlt(hdcWin, 0, 0, W, H, hdc, 0, 0, SRCCOPY);
            SelectObject(hdc, oldBmp);
            DeleteObject(bmp);
            DeleteDC(hdc);
            EndPaint(hWnd, &ps);
            return 0;
        }

        case WM_MOUSEWHEEL: {
            int notches = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            if (notches != 0 && IsTablePage(g_page)) {
                g_scroll -= notches * 3;
                ClampScroll();
                InvalidateRect(hWnd, nullptr, FALSE);
            }
            return 0;
        }

        case WM_MOUSEMOVE:
            if (g_draggingSlider) SetOpacityFromX(hWnd, (short)LOWORD(lParam) - RailW());
            return 0;

        case WM_LBUTTONUP:
        case WM_CAPTURECHANGED:
            if (g_draggingSlider) {
                g_draggingSlider = false;
                if (msg == WM_LBUTTONUP) ReleaseCapture();
                Wh_SetIntValue(L"OpacityPct", g_opacityPct);
            }
            return 0;

        case WM_LBUTTONDOWN: {
            int x = (short)LOWORD(lParam), y = (short)HIWORD(lParam);
            RECT rc;
            GetClientRect(hWnd, &rc);
            int W = rc.right - RailW();

            int rp = RailHit(x, y, rc.bottom);
            if (rp >= 0) { SetPage(hWnd, rp); return 0; }
            int cx = x - RailW();
            if (cx < 0) return 0;

            if (IsTablePage(g_page)) {
                if (!g_compact && y >= LayoutHeaderY() && y < LayoutListY() - Sc(2)) {
                    int col = TblHitCol(g_page, W, cx);
                    if (col >= 0 && col != g_tblSort[g_page]) {
                        g_tblSort[g_page] = col;
                        if (g_page == PG_PROCESSES) Wh_SetIntValue(L"SortCol", col);
                        g_scroll = 0;
                        SortRows(false);
                        InvalidateRect(hWnd, nullptr, FALSE);
                    }
                } else if (RowAtY(y) >= 0) {
                    lstrcpynW(g_selName, g_rows[RowAtY(y)].key, 128);
                    InvalidateRect(hWnd, nullptr, FALSE);
                } else {
                    POINT pt = { cx, y };
                    RECT sb = SortBtnRect();
                    int mc[3];
                    if (MetricCols(g_page, mc) > 0 && PtInRect(&sb, pt)) {
                        CycleSort(hWnd);
                    } else if (FooterLabel()) {
                        RECT b = ButtonRect(W);
                        if (PtInRect(&b, pt)) DoFooterAction(hWnd);
                    }
                }
            } else if (g_page == PG_SETTINGS) {
                HandleSettingsClick(hWnd, cx, y, W);
            }
            return 0;
        }

        case WM_CONTEXTMENU: {
            if (!IsTablePage(g_page)) return 0;
            POINT point = { (short)LOWORD(lParam), (short)HIWORD(lParam) };
            if (GET_X_LPARAM(lParam) != -1 || GET_Y_LPARAM(lParam) != -1) {
                POINT client = point;
                ScreenToClient(hWnd, &client);
                int idx = RowAtY(client.y);
                if (client.x < RailW() || idx < 0) return 0;
                lstrcpynW(g_selName, g_rows[idx].key, 128);
                InvalidateRect(hWnd, nullptr, FALSE);
            } else {
                RECT rect; GetWindowRect(hWnd, &rect);
                point.x = rect.left + Sc(160);
                point.y = rect.top + Sc(80);
            }
            ShowRowMenu(hWnd, point);
            return 0;
        }

        case WM_DESTROY:
            InterlockedExchangePointer((PVOID*)&g_popupHwnd, nullptr);
            break;
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

static void ApplyOpacity() {
    if (!g_popupHwnd) return;
    SetLayeredWindowAttributes(g_popupHwnd, 0, SuiteAlphaFor(g_popupHwnd), LWA_ALPHA);
}

// default spot is the top right of the main monitor
static void PositionOverlay() {
    if (!g_popupHwnd) return;

    UINT dpi = GetDpiForWindow(g_popupHwnd);
    g_dpi = dpi ? (int)dpi : 96;
    EnsureFont();

    int w = Sc(g_sizeW), h = Sc(g_sizeH);
    int x = 0, y = 0;
    MONITORINFO mi = { sizeof(mi) };
    if (g_hasPos) {
        // saved position, clamped to the nearest monitor
        HMONITOR hm = MonitorFromPoint(POINT{ g_posX + w / 2, g_posY + h / 2 }, MONITOR_DEFAULTTONEAREST);
        x = g_posX;
        y = g_posY;
        if (GetMonitorInfoW(hm, &mi)) {
            x = std::min(std::max(x, (int)mi.rcWork.left), std::max((int)mi.rcWork.left, (int)mi.rcWork.right - w));
            y = std::min(std::max(y, (int)mi.rcWork.top),  std::max((int)mi.rcWork.top,  (int)mi.rcWork.bottom - h));
        }
    } else {
        HMONITOR hm = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
        if (GetMonitorInfoW(hm, &mi)) {
            x = mi.rcWork.right - w - Sc(8);
            y = mi.rcWork.top + Sc(8);
            if (y + h > mi.rcWork.bottom) y = std::max((int)mi.rcWork.top, (int)mi.rcWork.bottom - h);
        }
    }
    SetWindowPos(g_popupHwnd, HWND_TOPMOST, x, y, w, h,
        SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

static void ShowPopup(HWND hTrayWnd) {
    if (!g_popupHwnd) {
        Wh_Log(L"Taskman: creating overlay window");
        WNDCLASSW wc = {0};
        wc.lpfnWndProc = PopupWndProc;
        wc.hInstance = g_hInstance;
        wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        wc.lpszClassName = L"MicroManagerOverlayPopupClass";
        wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
        if (!RegisterClassW(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
            Wh_Log(L"Popup RegisterClassW failed (%u)", GetLastError());
            return;
        }

        // noactivate so it never steals focus
        // layered for the transparency
        g_popupHwnd = CreateWindowExW(
            WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_LAYERED,
            wc.lpszClassName, L"Taskman",
            WS_POPUP | WS_BORDER,
            0, 0, Sc(POPUP_WIDTH), Sc(POPUP_HEIGHT),
            nullptr, nullptr, g_hInstance, nullptr);
        if (!g_popupHwnd) {
            Wh_Log(L"Taskman: CreateWindowExW failed (%u)", GetLastError());
            UnregisterClassW(L"MicroManagerOverlayPopupClass", g_hInstance);
            return;
        }
        ApplyOpacity();
    }

    PositionOverlay();

    // round corners (win11 only)
    int corner = DWMWCP_ROUND;
    DwmSetWindowAttribute(g_popupHwnd, DWMWA_WINDOW_CORNER_PREFERENCE,
        &corner, sizeof(corner));
}

static void SetOverlayVisible(HWND hTrayWnd, bool show) {
    if (show) ShowPopup(hTrayWnd);
    else if (g_popupHwnd) ShowWindow(g_popupHwnd, SW_HIDE);
    Wh_SetIntValue(L"OverlayVisible", show ? 1 : 0);
}

static void ToggleOverlay(HWND hTrayWnd) {
    bool visible = g_popupHwnd && IsWindowVisible(g_popupHwnd);
    SetOverlayVisible(hTrayWnd, !visible);
}

// ---- Settings ----

static void SaveIntervalMs(DWORD ms) {
    Wh_SetIntValue(L"UpdateIntervalMs", (int)ms);
}

static DWORD LoadIntervalMs() {
    DWORD ms = (DWORD)Wh_GetIntValue(L"UpdateIntervalMs", 1000);
    if (ms != 300 && ms != 500 && ms != 1000 && ms != 3000) ms = 1000;
    return ms;
}

static int LoadOpacityPct() {
    int v = SuiteBasePct();
    if (v < OPACITY_MIN) v = OPACITY_MIN;
    if (v > 100) v = 100;
    return v;
}

// ---- Tray window procedure ----

static LRESULT CALLBACK TrayWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            RefreshData();
            SetTimer(hWnd, WM_TIMER_ID, g_updateMs, nullptr);
            SetTimer(hWnd, 2, 40, nullptr);   // follow the shared opacity slider
            return 0;

        case WM_TIMER:
            if (wParam == 2) {
                int sv = SharedOpacityRead();
                if (sv >= OPACITY_MIN && sv != g_opacityPct) {
                    g_opacityPct = sv;
                    ApplyOpacity();
                    if (g_popupHwnd) InvalidateRect(g_popupHwnd, nullptr, FALSE);
                }
                return 0;
            }
            if (wParam == WM_TIMER_ID) {
                RefreshData();
            }
            return 0;

        case WM_HOTKEY:
            if (wParam == HOTKEY_ID) ToggleOverlay(hWnd);
            return 0;

        case WM_TOGGLE_OVERLAY:
            ToggleOverlay(hWnd);
            return 0;

        case WM_SAVE_POS:
            SavePlacement();
            return 0;

        case WM_TRAY_CALLBACK:
            switch (LOWORD(lParam)) {
                case WM_LBUTTONUP:
                case NIN_SELECT:
                case NIN_KEYSELECT: {
                    // v4 tray click sends both mouse-up and select
                    ULONGLONG now = GetTickCount64();
                    if (now - g_lastToggleTime < 250) break;
                    g_lastToggleTime = now;
                    ToggleOverlay(hWnd);
                    break;
                }

                case WM_CONTEXTMENU: {
                    HMENU hMenu = CreatePopupMenu();

                    WCHAR statusText[128];
                    if (g_totalCpu >= 0 && g_totalGpu >= 0 && g_totalRam >= 0)
                        swprintf_s(statusText, L"CPU: %d%%  GPU: %d%%  RAM: %d%%", g_totalCpu, g_totalGpu, g_totalRam);
                    else
                        lstrcpyW(statusText, L"Collecting...");
                    AppendMenuW(hMenu, MF_STRING, 0, statusText);
                    AppendMenuW(hMenu, MF_SEPARATOR, 0, nullptr);

                    UINT chk300 = (g_updateMs == 300)  ? (MF_STRING | MF_CHECKED) : MF_STRING;
                    UINT chk500 = (g_updateMs == 500)  ? (MF_STRING | MF_CHECKED) : MF_STRING;
                    UINT chk1s  = (g_updateMs == 1000) ? (MF_STRING | MF_CHECKED) : MF_STRING;
                    UINT chk3s  = (g_updateMs == 3000) ? (MF_STRING | MF_CHECKED) : MF_STRING;
                    AppendMenuW(hMenu, chk300, MENU_INTERVAL_300MS, L"Refresh: 0.3s");
                    AppendMenuW(hMenu, chk500, MENU_INTERVAL_500MS, L"Refresh: 0.5s");
                    AppendMenuW(hMenu, chk1s,  MENU_INTERVAL_1S,    L"Refresh: 1s");
                    AppendMenuW(hMenu, chk3s,  MENU_INTERVAL_3S,    L"Refresh: 3s");
                    AppendMenuW(hMenu, MF_SEPARATOR, 0, nullptr);
                    AppendMenuW(hMenu, MF_STRING | (g_compact ? MF_CHECKED : 0), MENU_COMPACT, L"Names only");
                    AppendMenuW(hMenu, MF_STRING, MENU_TOGGLE, L"Show/hide Taskman (Ctrl+Num 3)");
                    AppendMenuW(hMenu, MF_STRING, MENU_RESET_POS, L"Reset position");
                    AppendMenuW(hMenu, MF_STRING, MENU_OPEN_WINDHAWK, L"Open Windhawk");

                    POINT pt = { (short)LOWORD(wParam), (short)HIWORD(wParam) };
                    if (pt.x == 0 && pt.y == 0) {
                        GetCursorPos(&pt);
                    }
                    ApplyContextMenuTheme(hWnd, IsSystemDarkMode());
                    SetForegroundWindow(hWnd);
                    int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_RIGHTBUTTON |
                        TPM_BOTTOMALIGN | TPM_RIGHTALIGN,
                        pt.x, pt.y, 0, hWnd, nullptr);
                    PostMessageW(hWnd, WM_NULL, 0, 0);
                    DestroyMenu(hMenu);

                    DWORD newMs = 0;
                    if      (cmd == MENU_INTERVAL_300MS) newMs = 300;
                    else if (cmd == MENU_INTERVAL_500MS) newMs = 500;
                    else if (cmd == MENU_INTERVAL_1S)    newMs = 1000;
                    else if (cmd == MENU_INTERVAL_3S)    newMs = 3000;
                    else if (cmd == MENU_RESET_POS) {
                        g_hasPos = false;
                        Wh_SetIntValue(L"PosSet", 0);
                        if (g_popupHwnd && IsWindowVisible(g_popupHwnd)) PositionOverlay();
                    }
                    else if (cmd == MENU_COMPACT) {
                        SetCompact(!g_compact);
                    }
                    else if (cmd == MENU_TOGGLE) {
                        ToggleOverlay(hWnd);
                    }
                    else if (cmd == MENU_OPEN_WINDHAWK) {
                        if (g_windhawkPath[0] != L'\0') {
                            SHELLEXECUTEINFOW sei = {sizeof(sei)};
                            sei.lpFile = g_windhawkPath;
                            sei.nShow  = SW_SHOWNORMAL;
                            ShellExecuteExW(&sei);
                        }
                    }

                    if (newMs > 0 && newMs != g_updateMs) {
                        g_updateMs = newMs;
                        KillTimer(hWnd, WM_TIMER_ID);
                        SetTimer(hWnd, WM_TIMER_ID, newMs, nullptr);
                        SaveIntervalMs(newMs);
                    }
                    break;
                }
            }
            return 0;

        case WM_CLOSE:
            // destroy the popup first, on the tray thread
            if (g_popupHwnd) { DestroyWindow(g_popupHwnd); g_popupHwnd = nullptr; }
            DestroyWindow(hWnd);
            return 0;

        case WM_DESTROY:
            UnregisterHotKey(hWnd, HOTKEY_ID);
            KillTimer(hWnd, WM_TIMER_ID);
            {
                NOTIFYICONDATAW nid = {sizeof(nid)};
                nid.hWnd     = hWnd;
                nid.uID      = TRAY_ICON_ID;
                nid.uFlags   = NIF_GUID;
                nid.guidItem = MICROMANAGER_TRAY_GUID;
                Shell_NotifyIconW(NIM_DELETE, &nid);
            }
            PostQuitMessage(0);
            return 0;
    }

    // explorer restarted, add the icon again
    if (kShowTrayIcon && msg == g_taskbarCreatedMsg && g_taskbarCreatedMsg != 0) {
        g_lastTip[0] = L'\0';
        NOTIFYICONDATAW nid = {sizeof(nid)};
        nid.hWnd            = hWnd;
        nid.uID             = TRAY_ICON_ID;
        nid.uFlags          = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_GUID | NIF_SHOWTIP;
        nid.guidItem        = MICROMANAGER_TRAY_GUID;
        nid.uCallbackMessage = WM_TRAY_CALLBACK;
        lstrcpynW(nid.szTip, L"Taskman", 128);
        if (!g_iconEnabled)
            ExtractIconExW(g_ddoresDllPath, 28, nullptr, &g_iconEnabled, 1);
        nid.hIcon = g_iconEnabled ? g_iconEnabled : LoadIconW(nullptr, IDI_APPLICATION);
        if (!Shell_NotifyIconW(NIM_ADD, &nid)) {
            Shell_NotifyIconW(NIM_DELETE, &nid);
            Shell_NotifyIconW(NIM_ADD, &nid);
        }
        NOTIFYICONDATAW nidVer = {sizeof(nidVer)};
        nidVer.hWnd     = hWnd;
        nidVer.uID      = TRAY_ICON_ID;
        nidVer.uFlags   = NIF_GUID;
        nidVer.guidItem = MICROMANAGER_TRAY_GUID;
        nidVer.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &nidVer);
        return 0;
    }

    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

// ---- Tray thread ----

static DWORD WINAPI TrayThreadProc(LPVOID) {
    Wh_Log(L"Taskman: tray thread started");
    // per monitor dpi so it's sharp on scaled screens
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    HRESULT hrCo = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hrCo) && hrCo != RPC_E_CHANGED_MODE) {
        Wh_Log(L"TrayThread: CoInitializeEx failed (0x%X)", hrCo);
        return 1;
    }

    g_taskbarCreatedMsg = RegisterWindowMessageW(L"TaskbarCreated");

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = TrayWndProc;
    wc.hInstance = g_hInstance;
    wc.lpszClassName = L"MicroManagerOverlayTrayClass";
    if (!RegisterClassW(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        Wh_Log(L"Tray RegisterClassW failed (%u)", GetLastError());
        if (SUCCEEDED(hrCo)) CoUninitialize();
        return 1;
    }

    InterlockedExchangePointer((PVOID*)&g_trayHwnd, CreateWindowExW(
        WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
        wc.lpszClassName, L"Taskman",
        WS_POPUP,
        0, 0, 1, 1, nullptr, nullptr, g_hInstance, nullptr));
    if (!g_trayHwnd) {
        if (SUCCEEDED(hrCo)) CoUninitialize();
        return 1;
    }

    // own AUMID so windows doesn't group it with windhawk
    IPropertyStore* pps = nullptr;
    if (SUCCEEDED(SHGetPropertyStoreForWindow(g_trayHwnd, IID_PPV_ARGS(&pps)))) {
        wchar_t aumid[] = L"Resetti.Taskman";
        PROPVARIANT var;
        PropVariantInit(&var);
        var.vt = VT_LPWSTR;
        var.pwszVal = aumid;
        if (SUCCEEDED(pps->SetValue(PKEY_AppUserModel_ID, var))) {
            pps->Commit();
        }
        pps->Release();
    }

    if (kShowTrayIcon) {
    NOTIFYICONDATAW nid = {sizeof(nid)};
    nid.hWnd            = g_trayHwnd;
    nid.uID             = TRAY_ICON_ID;
    nid.uFlags          = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_GUID | NIF_SHOWTIP;
    nid.guidItem        = MICROMANAGER_TRAY_GUID;
    nid.uCallbackMessage = WM_TRAY_CALLBACK;
    lstrcpynW(nid.szTip, L"Taskman", 128);
    nid.hIcon = g_iconEnabled ? g_iconEnabled : LoadIconW(nullptr, IDI_APPLICATION);
    if (!Shell_NotifyIconW(NIM_ADD, &nid)) {
        Shell_NotifyIconW(NIM_DELETE, &nid);
        Shell_NotifyIconW(NIM_ADD, &nid);
    }
    NOTIFYICONDATAW nidVer = {sizeof(nidVer)};
    nidVer.hWnd     = g_trayHwnd;
    nidVer.uID      = TRAY_ICON_ID;
    nidVer.uFlags   = NIF_GUID;
    nidVer.guidItem = MICROMANAGER_TRAY_GUID;
    nidVer.uVersion = NOTIFYICON_VERSION_4;
    Shell_NotifyIconW(NIM_SETVERSION, &nidVer);
    }

    // show / hide is Ctrl+Num 3

    // visible by default, after that remembers
    Wh_Log(L"Taskman: tray window %p, hotkey registered, showing overlay", g_trayHwnd);
    if (Wh_GetIntValue(L"OverlayVisible", 1)) ShowPopup(g_trayHwnd);
    Wh_Log(L"Taskman: overlay window %p", g_popupHwnd);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    InterlockedExchangePointer((PVOID*)&g_trayHwnd, nullptr);
    if (SUCCEEDED(hrCo)) CoUninitialize();
    return 0;
}

// ---- Windhawk callbacks ----

BOOL Init() {
    Wh_Log(L"Taskman Init");

    g_updateMs = LoadIntervalMs();
    g_opacityPct = LoadOpacityPct();
    g_hasPos = Wh_GetIntValue(L"PosSet", 0) != 0;
    g_compact = Wh_GetIntValue(L"Compact", 0) != 0;
    g_inlineVals = Wh_GetIntValue(L"InlineVals", 1) != 0;
    g_sizeW = std::min(3000, std::max(RAIL_W + 180, Wh_GetIntValue(L"SizeW", POPUP_WIDTH)));
    g_sizeH = std::min(3000, std::max(300, Wh_GetIntValue(L"SizeH", POPUP_HEIGHT)));
    g_posX = Wh_GetIntValue(L"PosX", 0);
    g_posY = Wh_GetIntValue(L"PosY", 0);
    g_tblSort[PG_PROCESSES] = Wh_GetIntValue(L"SortCol", 1);
    if (g_tblSort[PG_PROCESSES] < 1 || g_tblSort[PG_PROCESSES] > 3) g_tblSort[PG_PROCESSES] = 1;

    MEMORYSTATUSEX mem = {sizeof(mem)};
    if (GlobalMemoryStatusEx(&mem)) g_totalPhys = mem.ullTotalPhys;

    g_hInstance = GetModuleHandleW(nullptr);
    WCHAR modulePath[MAX_PATH];
    switch (GetModuleFileNameW(g_hInstance, modulePath, ARRAYSIZE(modulePath))) {
        case 0:
        case ARRAYSIZE(modulePath):
            Wh_Log(L"GetModuleFileNameW failed");
            g_windhawkPath[0] = L'\0';
            g_windhawkModPath[0] = L'\0';
            break;
        default: {
            WCHAR* lastSlash = wcsrchr(modulePath, L'\\');
            if (lastSlash) {
                *lastSlash = L'\0';
                swprintf_s(g_windhawkPath, L"%s\\windhawk.exe", modulePath);
                swprintf_s(g_windhawkModPath, L"%s\\windhawk-mod.exe", modulePath);
            } else {
                wcscpy_s(g_windhawkPath, L"windhawk.exe");
                wcscpy_s(g_windhawkModPath, L"windhawk-mod.exe");
            }
            break;
        }
    }

    // full path to ddores.dll, ExtractIconExW deals with the .mun redirect
    UINT sysLen = GetSystemDirectoryW(g_ddoresDllPath, MAX_PATH);
    if (sysLen > 0 && sysLen < MAX_PATH - 12)
        lstrcatW(g_ddoresDllPath, L"\\ddores.dll");
    else
        lstrcpyW(g_ddoresDllPath, L"ddores.dll");

    ExtractIconExW(g_ddoresDllPath, 28, nullptr, &g_iconEnabled, 1);

    InitGpuQuery();

    // first cpu sample so the first tick has a delta
    GetSystemTimes(&g_prevIdle, &g_prevKernel, &g_prevUser);
    MY_SYSTEM_PROCESS_INFO* initBuf = nullptr;
    if (CollectProcessInfo(&initBuf) && initBuf) {
        MY_SYSTEM_PROCESS_INFO* p = initBuf;
        int count = 0;
        while (count < MAX_PROCESSES) {
            g_prevProcs[count].pid = (DWORD)(ULONG_PTR)p->UniqueProcessId;
            g_prevProcs[count].created = p->CreateTime.QuadPart;
            g_prevProcs[count].time = p->KernelTime.QuadPart + p->UserTime.QuadPart;
            g_prevProcs[count].delta = 0;
            g_prevProcs[count].ws = (ULONGLONG)p->WorkingSetPrivateSize.QuadPart;
            g_prevProcs[count].session = p->SessionId;
            GetProcessDisplayName(p, g_prevProcs[count].name, ARRAYSIZE(g_prevProcs[count].name));
            count++;
            if (p->NextEntryOffset == 0) break;
            p = (MY_SYSTEM_PROCESS_INFO*)((BYTE*)p + p->NextEntryOffset);
        }
        g_prevProcCount = count;
        free(initBuf);
    }

    g_trayThread = CreateThread(nullptr, 0, TrayThreadProc, nullptr, 0, nullptr);
    return TRUE;
}

void SettingsChanged() {
    // no settings here
}

void Uninit() {
    Wh_Log(L"Taskman Uninit");

    HWND hwndClose = (HWND)InterlockedCompareExchangePointer((PVOID*)&g_trayHwnd, nullptr, nullptr);
    if (hwndClose && IsWindow(hwndClose)) PostMessageW(hwndClose, WM_CLOSE, 0, 0);
    if (g_trayThread) {
        WaitForSingleObject(g_trayThread, 3000);
        CloseHandle(g_trayThread);
        g_trayThread = nullptr;
    }

    UnregisterClassW(L"MicroManagerOverlayPopupClass", g_hInstance);
    UnregisterClassW(L"MicroManagerOverlayTrayClass", g_hInstance);

    if (g_iconEnabled) { DestroyIcon(g_iconEnabled); g_iconEnabled = nullptr; }
    if (g_hPopupFont) { DeleteObject(g_hPopupFont); g_hPopupFont = nullptr; }
    if (g_hIconFont) { DeleteObject(g_hIconFont); g_hIconFont = nullptr; }
    if (g_gpuQuery) { PdhCloseQuery(g_gpuQuery); g_gpuQuery = nullptr; g_gpuCounter = nullptr; }
    if (g_hUxTheme) { FreeLibrary(g_hUxTheme); g_hUxTheme = nullptr; }
}

}  // namespace tman

// ---- pinned windows ----

struct Pin {
    WCHAR  exe[MAX_PATH];     // exe name ("" = any)
    WCHAR  cls[64];           // class prefix
    WCHAR  title[128];        // title contains one of these, split by |
    WCHAR  path[MAX_PATH];    // full path, used to launch it
    WCHAR  key[48];           // prefix for the saved position
    int    numKey;            // numpad digit
    int    mode;              // 1 = NumLock off, 2 = NumLock on, 3 = either
    int    defW, defH;
    HWND   win[SU_MAX_WIN];
    int    n;
    HWND   hid[SU_MAX_WIN];   // windows hidden by "hide all"
    int    nHid;
};

#define SU_MAX_SLOTS 8
static Pin  g_pins[SU_MAX_SLOTS];
static int  g_npins = 0;
static int  g_modeOf[10] = {};            // per numpad digit: bit 1 = NumLock off, bit 2 = NumLock on
static volatile LONG g_optAltQ = 1, g_optScale = 1, g_optSnip = 1;
static int  g_builtinMode = 1;
static HWND g_helpHwnd = nullptr;

static void HelpToggle();
static void LoadConfig(bool keep);

#define SU_DEF_W    440
#define SU_DEF_H    640
#define SU_MARGIN   8

static int SuGet(const Pin& p, PCWSTR f, int def) {
    WCHAR k[64];
    swprintf_s(k, L"%s%s", p.key, f);
    return Wh_GetIntValue(k, def);
}

static void SuSet(const Pin& p, PCWSTR f, int v) {
    WCHAR k[64];
    swprintf_s(k, L"%s%s", p.key, f);
    Wh_SetIntValue(k, v);
}

struct SuFind { const Pin* pin; HWND found[SU_MAX_WIN]; int count; DWORD lastPid; bool lastOk; };

static bool SuPidMatch(SuFind* c, DWORD pid) {
    if (!c->pin->exe[0]) return true;
    if (pid == c->lastPid) return c->lastOk;
    c->lastPid = pid;
    c->lastOk = false;
    HANDLE ph = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!ph) return false;
    WCHAR path[MAX_PATH];
    DWORD len = MAX_PATH;
    if (QueryFullProcessImageNameW(ph, 0, path, &len)) {
        PCWSTR base = wcsrchr(path, L'\\');
        base = base ? base + 1 : path;
        c->lastOk = (_wcsicmp(base, c->pin->exe) == 0);
    }
    CloseHandle(ph);
    return c->lastOk;
}

static bool SuTitleMatch(PCWSTR title, PCWSTR pat) {
    WCHAR part[128];
    while (*pat) {
        size_t n = 0;
        while (pat[n] && pat[n] != L'|') n++;
        if (n > 0 && n < 128) {
            wmemcpy(part, pat, n);
            part[n] = 0;
            if (wcsstr(title, part)) return true;
        }
        pat += n;
        if (*pat == L'|') pat++;
    }
    return false;
}

static BOOL CALLBACK SuEnum(HWND h, LPARAM lp) {
    SuFind* c = (SuFind*)lp;
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    WCHAR cls[64];
    if (!GetClassNameW(h, cls, 64) || wcsncmp(cls, c->pin->cls, wcslen(c->pin->cls)) != 0) return TRUE;
    if (!SuPidMatch(c, pid)) return TRUE;
    if (GetWindow(h, GW_OWNER)) return TRUE;                 // popups, dialogs
    if (GetWindowTextLengthW(h) == 0) return TRUE;           // tooltips, helper windows
    if (c->pin->title[0]) {
        WCHAR title[128];
        if (GetWindowTextW(h, title, 128) <= 0) return TRUE;
        if (!SuTitleMatch(title, c->pin->title)) return TRUE;
    }
    if (GetWindowLongPtrW(h, GWL_EXSTYLE) & WS_EX_TOOLWINDOW) return TRUE;
    if (c->count < SU_MAX_WIN) c->found[c->count++] = h;
    return TRUE;
}

static bool PinHas(const Pin& p, HWND h) {
    for (int i = 0; i < p.n; i++) if (p.win[i] == h) return true;
    return false;
}

static void PinPurge(Pin& p) {
    int n = 0;
    for (int i = 0; i < p.n; i++) if (IsWindow(p.win[i])) p.win[n++] = p.win[i];
    p.n = n;
}

static void PinStyle(HWND h) {
    LONG_PTR ex = GetWindowLongPtrW(h, GWL_EXSTYLE);
    if (!(ex & WS_EX_LAYERED)) SetWindowLongPtrW(h, GWL_EXSTYLE, ex | WS_EX_LAYERED);
    SetLayeredWindowAttributes(h, 0, SuiteAlphaFor(h), LWA_ALPHA);
    SetWindowPos(h, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

// only syncs the alpha
static void PinAlphaSync(HWND h) {
    LONG_PTR ex = GetWindowLongPtrW(h, GWL_EXSTYLE);
    if (!(ex & WS_EX_LAYERED)) return;
    BYTE cur = 0;
    DWORD fl = 0;
    BYTE want = SuiteAlphaFor(h);
    if (GetLayeredWindowAttributes(h, nullptr, &cur, &fl) && (fl & LWA_ALPHA) && cur == want) return;
    SetLayeredWindowAttributes(h, 0, want, LWA_ALPHA);
}

static void PinLayout(const Pin& p, HWND h) {
    if (IsZoomed(h) || IsIconic(h)) ShowWindow(h, SW_RESTORE);

    if (SuGet(p, L"Set", 0)) {
        int sx = SuGet(p, L"X", 0);
        int sy = SuGet(p, L"Y", 0);
        int sw = SuGet(p, L"W", p.defW);
        int sh = SuGet(p, L"H", p.defH);
        if (sw >= 200 && sh >= 150) {
            SetWindowPos(h, nullptr, sx, sy, sw, sh, SWP_NOZORDER | SWP_NOACTIVATE);
            return;
        }
    }
    MONITORINFO mi = { sizeof(mi) };
    HMONITOR mon = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
    if (!GetMonitorInfoW(mon, &mi)) return;
    int x = mi.rcWork.right - p.defW - SU_MARGIN;
    int y = mi.rcWork.top + SU_MARGIN;
    SetWindowPos(h, nullptr, x, y, p.defW, p.defH, SWP_NOZORDER | SWP_NOACTIVATE);
}

static void PinScan(Pin& p) {
    PinPurge(p);
    SuFind c = {};
    c.pin = &p;
    EnumWindows(SuEnum, (LPARAM)&c);
    for (int i = 0; i < c.count; i++) {
        HWND h = c.found[i];
        if (!PinHas(p, h)) {
            if (!IsWindowVisible(h) || p.n >= SU_MAX_WIN) continue;
            p.win[p.n++] = h;
            PinLayout(p, h);   // only once per window so dragging sticks
            PinStyle(h);
        } else {
            LONG_PTR ex = GetWindowLongPtrW(h, GWL_EXSTYLE);
            if (!(ex & WS_EX_LAYERED) || !(ex & WS_EX_TOPMOST)) PinStyle(h);
        }
    }
}

static HWND PinPick(Pin& p) {
    PinPurge(p);
    HWND fg = GetForegroundWindow();
    for (int i = 0; i < p.n; i++) if (p.win[i] == fg) return fg;
    for (int i = 0; i < p.n; i++) if (IsWindowVisible(p.win[i])) return p.win[i];
    return p.n ? p.win[0] : nullptr;
}

// Ctrl+Num: hide, or show again in the saved spot
static void PinToggle(Pin& p) {
    PinScan(p);
    if (p.n == 0) {
        if (p.path[0]) ShellExecuteW(nullptr, L"open", p.path, nullptr, nullptr, SW_SHOWNORMAL);
        else MessageBeep(MB_ICONEXCLAMATION);
        return;
    }
    bool anyVisible = false;
    for (int i = 0; i < p.n; i++) if (IsWindowVisible(p.win[i])) { anyVisible = true; break; }
    for (int i = 0; i < p.n; i++) {
        if (anyVisible) {
            ShowWindow(p.win[i], SW_HIDE);
        } else {
            ShowWindow(p.win[i], SW_SHOW);
            PinLayout(p, p.win[i]);
            PinStyle(p.win[i]);
        }
    }
    if (!anyVisible) SetForegroundWindow(p.win[0]);
}

// Shift+Num: save position and size
static void PinSave(Pin& p) {
    HWND h = PinPick(p);
    RECT r;
    if (!h || IsZoomed(h) || IsIconic(h) || !GetWindowRect(h, &r)) { MessageBeep(MB_ICONEXCLAMATION); return; }
    SuSet(p, L"X", r.left);
    SuSet(p, L"Y", r.top);
    SuSet(p, L"W", r.right - r.left);
    SuSet(p, L"H", r.bottom - r.top);
    SuSet(p, L"Set", 1);
    MessageBeep(MB_OK);
}

static void PinRestoreLook(Pin& p) {
    for (int i = 0; i < p.n; i++) {
        HWND h = p.win[i];
        if (!IsWindow(h)) continue;
        if (!IsWindowVisible(h)) ShowWindow(h, SW_SHOW);
        SetLayeredWindowAttributes(h, 0, 255, LWA_ALPHA);
        LONG_PTR ex = GetWindowLongPtrW(h, GWL_EXSTYLE);
        SetWindowLongPtrW(h, GWL_EXSTYLE, ex & ~(LONG_PTR)WS_EX_LAYERED);
        SetWindowPos(h, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    p.n = 0;
}

// ---- opacity bar ----

static int  g_sdpi = 96;
static bool g_sdrag = false;
static bool g_allHidden = false;
static bool g_tmHidden = false;
static volatile LONG g_numLock = 0;

static int SSc(int v) { return MulDiv(v, g_sdpi, 96); }
#define SU_NUM_W 80
static void STrack(int w, int* l, int* r) { *l = SSc(62); *r = w - SSc(44) - SSc(SU_NUM_W) - SSc(50); }
static int  SBtnLeft(int w) { return w - SSc(50); }
static int  SNumLeft(int w) { return w - SSc(50) - SSc(SU_NUM_W); }

static int SPctFromX(HWND h, int x) {
    RECT rc;
    GetClientRect(h, &rc);
    int l, r;
    STrack(rc.right, &l, &r);
    return (x - l) * 100 / (r - l);
}

static void SliderPaint(HWND h) {
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(h, &ps);
    RECT rc;
    GetClientRect(h, &rc);
    int W = rc.right, H = rc.bottom;

    HDC mem = CreateCompatibleDC(dc);
    HBITMAP bmp = CreateCompatibleBitmap(dc, W, H);
    HGDIOBJ oldBmp = SelectObject(mem, bmp);

    HBRUSH bg = CreateSolidBrush(RGB(30, 30, 30));
    FillRect(mem, &rc, bg);
    DeleteObject(bg);
    HBRUSH border = CreateSolidBrush(RGB(70, 70, 70));
    FrameRect(mem, &rc, border);
    DeleteObject(border);

    HFONT font = CreateFontW(-SSc(12), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             CLEARTYPE_QUALITY, 0, L"Segoe UI");
    HGDIOBJ oldFont = SelectObject(mem, font);
    SetBkMode(mem, TRANSPARENT);

    SetTextColor(mem, RGB(170, 170, 170));
    RECT lr = { SSc(8), 0, SSc(60), H };
    DrawTextW(mem, L"Opacity", -1, &lr, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    int l, r;
    STrack(W, &l, &r);
    int cy = H / 2;
    int tx = l + g_basePct * (r - l) / 100;

    HBRUSH trackBg = CreateSolidBrush(RGB(70, 70, 70));
    RECT t1 = { l, cy - SSc(2), r, cy + SSc(2) };
    FillRect(mem, &t1, trackBg);
    DeleteObject(trackBg);
    HBRUSH trackFg = CreateSolidBrush(RGB(232, 198, 43));
    RECT t2 = { l, cy - SSc(2), tx, cy + SSc(2) };
    FillRect(mem, &t2, trackFg);
    DeleteObject(trackFg);

    HBRUSH thumb = CreateSolidBrush(RGB(240, 240, 240));
    HGDIOBJ oldBrush = SelectObject(mem, thumb);
    HPEN nullPen = (HPEN)GetStockObject(NULL_PEN);
    HGDIOBJ oldPen = SelectObject(mem, nullPen);
    Ellipse(mem, tx - SSc(6), cy - SSc(6), tx + SSc(6), cy + SSc(6));
    SelectObject(mem, oldPen);
    SelectObject(mem, oldBrush);
    DeleteObject(thumb);

    WCHAR txt[16];
    swprintf_s(txt, L"%d%%", g_basePct);
    SetTextColor(mem, RGB(235, 235, 235));
    RECT pr = { r + SSc(8), 0, SNumLeft(W) - SSc(2), H };
    DrawTextW(mem, txt, -1, &pr, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    // numlock box
    bool nl = g_numLock != 0;
    RECT nr = { SNumLeft(W) + SSc(2), SSc(3), SBtnLeft(W) - SSc(2), H - SSc(3) };
    HBRUSH nb = CreateSolidBrush(nl ? RGB(232, 198, 43) : RGB(62, 62, 62));
    FillRect(mem, &nr, nb);
    DeleteObject(nb);
    SetTextColor(mem, nl ? RGB(20, 20, 20) : RGB(140, 140, 140));
    DrawTextW(mem, L"Taskumatti", -1, &nr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // "Hide all" button
    RECT br = { SBtnLeft(W), SSc(3), W - SSc(4), H - SSc(3) };
    HBRUSH bb = CreateSolidBrush(g_allHidden ? RGB(232, 198, 43) : RGB(62, 62, 62));
    FillRect(mem, &br, bb);
    DeleteObject(bb);
    SetTextColor(mem, g_allHidden ? RGB(20, 20, 20) : RGB(235, 235, 235));
    DrawTextW(mem, g_allHidden ? L"Show" : L"Hide", -1, &br, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SelectObject(mem, oldFont);
    DeleteObject(font);

    BitBlt(dc, 0, 0, W, H, mem, 0, 0, SRCCOPY);
    SelectObject(mem, oldBmp);
    DeleteObject(bmp);
    DeleteDC(mem);
    EndPaint(h, &ps);
}

// hide / show everything except the bar
static void SuToggleAll() {
    HWND tray = tman::g_trayHwnd;
    HWND popup = tman::g_popupHwnd;
    if (!g_allHidden) {
        for (int k = 0; k < g_npins; k++) {
            Pin& p = g_pins[k];
            PinScan(p);
            p.nHid = 0;
            for (int i = 0; i < p.n; i++) {
                if (IsWindowVisible(p.win[i]) && p.nHid < SU_MAX_WIN) {
                    p.hid[p.nHid++] = p.win[i];
                    ShowWindow(p.win[i], SW_HIDE);
                }
            }
        }
        g_tmHidden = false;
        if (tray && popup && IsWindowVisible(popup)) {
            PostMessageW(tray, SU_WM_TM_TOGGLE, 0, 0);
            g_tmHidden = true;
        }
        g_allHidden = true;
    } else {
        for (int k = 0; k < g_npins; k++) {
            Pin& p = g_pins[k];
            for (int i = 0; i < p.nHid; i++)
                if (IsWindow(p.hid[i])) ShowWindow(p.hid[i], SW_SHOWNA);
            p.nHid = 0;
        }
        if (g_tmHidden && tray && popup && !IsWindowVisible(popup))
            PostMessageW(tray, SU_WM_TM_TOGGLE, 0, 0);
        g_tmHidden = false;
        g_allHidden = false;
    }
    if (g_sliderHwnd) InvalidateRect(g_sliderHwnd, nullptr, FALSE);
}

static void SliderPlace() {
    HWND h = g_sliderHwnd;
    if (!h) return;
    int W = SSc(380), H = SSc(26);
    int x, y;
    if (Wh_GetIntValue(L"SliderSet", 0)) {
        x = Wh_GetIntValue(L"SliderX", 0);
        y = Wh_GetIntValue(L"SliderY", 0);
        POINT pt = { x + 10, y + 10 };
        if (!MonitorFromPoint(pt, MONITOR_DEFAULTTONULL)) { x = 100; y = 8; }
    } else {
        RECT wa;
        SystemParametersInfoW(SPI_GETWORKAREA, 0, &wa, 0);
        x = wa.left + (wa.right - wa.left - W) / 2;
        y = wa.top + 8;
    }
    SetWindowPos(h, HWND_TOPMOST, x, y, W, H, SWP_NOACTIVATE);
}

static void SliderToggle() {
    HWND h = g_sliderHwnd;
    if (!h) return;
    if (IsWindowVisible(h)) {
        ShowWindow(h, SW_HIDE);
    } else {
        SliderPlace();
        ShowWindow(h, SW_SHOWNA);
    }
}

static void SliderSave() {
    HWND h = g_sliderHwnd;
    RECT r;
    if (!h || !GetWindowRect(h, &r)) { MessageBeep(MB_ICONEXCLAMATION); return; }
    Wh_SetIntValue(L"SliderX", r.left);
    Wh_SetIntValue(L"SliderY", r.top);
    Wh_SetIntValue(L"SliderSet", 1);
    MessageBeep(MB_OK);
}

static LRESULT CALLBACK SliderProc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_PAINT:
            SliderPaint(h);
            return 0;
        case WM_ERASEBKGND:
            return 1;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_NCHITTEST: {
            POINT pt = { (short)LOWORD(lp), (short)HIWORD(lp) };
            ScreenToClient(h, &pt);
            RECT rc;
            GetClientRect(h, &rc);
            int l, r;
            STrack(rc.right, &l, &r);
            if (pt.x >= SBtnLeft(rc.right)) return HTCLIENT;
            if (pt.x < l - SSc(8) || pt.x > r + SSc(6)) return HTCAPTION;
            return HTCLIENT;
        }
        case WM_LBUTTONDOWN: {
            RECT cr;
            GetClientRect(h, &cr);
            if ((short)LOWORD(lp) >= SBtnLeft(cr.right)) { SuToggleAll(); return 0; }
            g_sdrag = true;
            SetCapture(h);
            SuiteSetBase(SPctFromX(h, (short)LOWORD(lp)));
            return 0;
        }
        case WM_MOUSEMOVE:
            if (g_sdrag) SuiteSetBase(SPctFromX(h, (short)LOWORD(lp)));
            return 0;
        case WM_LBUTTONUP:
            if (g_sdrag) { g_sdrag = false; ReleaseCapture(); }
            return 0;
        case WM_MOUSEWHEEL:
            SuiteSetBase(g_basePct + (GET_WHEEL_DELTA_WPARAM(wp) > 0 ? 5 : -5));
            return 0;
    }
    return DefWindowProcW(h, msg, wp, lp);
}

// ---- help window ----

struct HelpRow { WCHAR keys[48]; WCHAR what[112]; };
static HelpRow g_help[40];
static int     g_helpN = 0;

static void HelpAdd(PCWSTR keys, PCWSTR what) {
    if (g_helpN >= 40) return;
    lstrcpynW(g_help[g_helpN].keys, keys, 48);
    lstrcpynW(g_help[g_helpN].what, what, 112);
    g_helpN++;
}

static PCWSTR NlTag(int mode) {
    return mode == 2 ? L"   [NumLock on]" : mode == 3 ? L"   [any NumLock]" : L"";
}

static void PinName(const Pin& p, WCHAR* out, int cap) {
    lstrcpynW(out, p.title[0] ? p.title : p.exe, cap);
    WCHAR* bar = wcschr(out, L'|');
    if (bar) *bar = 0;
    if (!p.title[0]) {
        size_t l = wcslen(out);
        if (l > 4 && _wcsicmp(out + l - 4, L".exe") == 0) out[l - 4] = 0;
    }
}

static void HelpBuild() {
    g_helpN = 0;
    WCHAR w[320], k[64], nm[64];
    int bm = g_builtinMode;

    swprintf_s(w, L"This help (click to close)%s", NlTag(bm));
    HelpAdd(L"Ctrl+Num 0", w);
    swprintf_s(w, L"Taskman monitor show / hide, Shift+Num 3 saves position%s", NlTag(bm));
    HelpAdd(L"Ctrl+Num 3", w);
    swprintf_s(w, L"Opacity bar show / hide, Shift+Num 4 saves position%s", NlTag(bm));
    HelpAdd(L"Ctrl+Num 4", w);
    swprintf_s(w, L"Hide / show all windows%s", NlTag(bm));
    HelpAdd(L"Ctrl+Num 7", w);

    for (int i = 0; i < g_npins; i++) {
        const Pin& p = g_pins[i];
        PinName(p, nm, 64);
        swprintf_s(k, L"Ctrl+Num %d", p.numKey);
        swprintf_s(w, L"%s show / hide, Shift+Num %d saves position%s", nm, p.numKey, NlTag(p.mode));
        HelpAdd(k, w);
    }
    if (g_optAltQ)  HelpAdd(L"Alt+Q", L"Quit the focused program (all its windows)");
    if (g_optSnip)  HelpAdd(L"Shift+Space", L"Snipping tool (Win+Shift+S)");
    if (g_optScale) HelpAdd(L"Alt+Shift+wheel", L"Change the display scaling");
    for (int i = 0; i < g_npins; i++) {
        if (_wcsicmp(g_pins[i].exe, L"obsidian.exe") == 0) {
            HelpAdd(L"Shift/Alt+wheel", L"Zoom the interface while the pointer is over Obsidian");
            break;
        }
    }
    HelpAdd(L"Note", L"Numpad combos need NumLock off unless a row says otherwise");
}

static void HelpPaint(HWND h) {
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(h, &ps);
    RECT rc;
    GetClientRect(h, &rc);

    HBRUSH bg = CreateSolidBrush(RGB(30, 30, 30));
    FillRect(dc, &rc, bg);
    DeleteObject(bg);
    HBRUSH border = CreateSolidBrush(RGB(70, 70, 70));
    FrameRect(dc, &rc, border);
    DeleteObject(border);

    HFONT font = CreateFontW(-SSc(13), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             CLEARTYPE_QUALITY, 0, L"Segoe UI");
    HFONT bold = CreateFontW(-SSc(15), 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             CLEARTYPE_QUALITY, 0, L"Segoe UI");
    HGDIOBJ oldFont = SelectObject(dc, bold);
    SetBkMode(dc, TRANSPARENT);

    SetTextColor(dc, RGB(235, 235, 235));
    RECT tr = { SSc(14), SSc(8), rc.right - SSc(14), SSc(34) };
    DrawTextW(dc, L"Taskman shortcuts", -1, &tr, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    SelectObject(dc, font);
    int y = SSc(40);
    for (int i = 0; i < g_helpN; i++) {
        RECT kr = { SSc(14), y, SSc(170), y + SSc(22) };
        SetTextColor(dc, RGB(232, 198, 43));
        DrawTextW(dc, g_help[i].keys, -1, &kr, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
        RECT wr = { SSc(176), y, rc.right - SSc(14), y + SSc(22) };
        SetTextColor(dc, RGB(220, 220, 220));
        DrawTextW(dc, g_help[i].what, -1, &wr,
                  DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX | DT_END_ELLIPSIS);
        y += SSc(22);
    }

    SelectObject(dc, oldFont);
    DeleteObject(font);
    DeleteObject(bold);
    EndPaint(h, &ps);
}

static LRESULT CALLBACK HelpProc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_PAINT:
            HelpPaint(h);
            return 0;
        case WM_ERASEBKGND:
            return 1;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_LBUTTONDOWN:
            ShowWindow(h, SW_HIDE);
            return 0;
    }
    return DefWindowProcW(h, msg, wp, lp);
}

static void HelpToggle() {
    if (g_helpHwnd && IsWindowVisible(g_helpHwnd)) {
        ShowWindow(g_helpHwnd, SW_HIDE);
        return;
    }
    HelpBuild();
    if (!g_helpHwnd) {
        g_helpHwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_LAYERED,
                                     L"ResettiSuiteHelp", L"Taskman shortcuts", WS_POPUP,
                                     0, 0, SSc(600), SSc(300), nullptr, nullptr,
                                     GetModuleHandleW(nullptr), nullptr);
        if (!g_helpHwnd) return;
    }
    int W = SSc(600);
    int H = SSc(40) + g_helpN * SSc(22) + SSc(14);
    RECT wa;
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &wa, 0);
    int x = wa.left + (wa.right - wa.left - W) / 2;
    int y = wa.top + (wa.bottom - wa.top - H) / 2;
    SetWindowPos(g_helpHwnd, HWND_TOPMOST, x, y, W, H, SWP_NOACTIVATE | SWP_SHOWWINDOW);
    SetLayeredWindowAttributes(g_helpHwnd, 0, SuiteAlphaFor(g_helpHwnd), LWA_ALPHA);
    InvalidateRect(g_helpHwnd, nullptr, FALSE);
}

// ---- commands (worker thread) ----

// action: 0 = show/hide (Ctrl+Num), 1 = save position (Shift+Num); n = numpad digit
static void SuCommand(int action, int n) {
    int nlBit = g_numLock ? 2 : 1;
    for (int k = 0; k < g_npins; k++) {
        Pin& p = g_pins[k];
        if (p.numKey == n && (p.mode & nlBit)) {
            if (action == 0) PinToggle(p); else PinSave(p);
            return;
        }
    }
    if (!(g_builtinMode & nlBit)) return;
    switch (n) {
        case 0:
            if (action == 0) HelpToggle();
            break;
        case 3: {
            HWND t = tman::g_trayHwnd;
            if (!t) { MessageBeep(MB_ICONEXCLAMATION); return; }
            PostMessageW(t, action == 0 ? SU_WM_TM_TOGGLE : WM_SAVE_POS, 0, 0);
            break;
        }
        case 4:
            if (action == 0) SliderToggle(); else SliderSave();
            break;
        case 7:
            if (action == 0) SuToggleAll();
            break;
    }
}

static HWND   g_cmdWnd = nullptr;
static HANDLE g_worker = nullptr;
static int    g_lastNl = -1;

#define SU_WM_ZOOM (WM_APP + 11)
#define SU_WM_QUIT (WM_APP + 12)
#define SU_WM_RELOAD (WM_APP + 13)

static void SuKeyEvt(WORD vk, bool up) {
    INPUT in = {};
    in.type = INPUT_KEYBOARD;
    in.ki.wVk = vk;
    in.ki.wScan = (WORD)MapVirtualKeyW(vk, MAPVK_VK_TO_VSC);
    in.ki.dwFlags = up ? KEYEVENTF_KEYUP : 0;
    SendInput(1, &in, sizeof(in));
}

// zooms obsidian with ctrl+plus / minus while shift or alt is held
static void SuZoomStep(HWND root, int dir) {
    if (!IsWindow(root)) return;
    HWND fg = GetForegroundWindow();
    if (fg != root) {
        DWORD me = GetCurrentThreadId();
        DWORD fgT = fg ? GetWindowThreadProcessId(fg, nullptr) : 0;
        if (fgT && fgT != me) AttachThreadInput(me, fgT, TRUE);
        SetForegroundWindow(root);
        if (fgT && fgT != me) AttachThreadInput(me, fgT, FALSE);
        Sleep(30);
        if (GetForegroundWindow() != root) return;   // Windows refused to switch
    }
    bool altDown = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
    bool shiftDown = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    if (altDown) {
        // dummy key so the alt release isn't taken as a menu tap
        SuKeyEvt(0xFC, false);
        SuKeyEvt(0xFC, true);
        SuKeyEvt(VK_MENU, true);
    }
    if (shiftDown) SuKeyEvt(VK_SHIFT, true);
    SuKeyEvt(VK_CONTROL, false);
    SuKeyEvt(dir > 0 ? VK_OEM_PLUS : VK_OEM_MINUS, false);
    SuKeyEvt(dir > 0 ? VK_OEM_PLUS : VK_OEM_MINUS, true);
    SuKeyEvt(VK_CONTROL, true);
    if (shiftDown) SuKeyEvt(VK_SHIFT, false);
    if (altDown) SuKeyEvt(VK_MENU, false);
}

// ---- alt+q quit ----

static bool g_qqSwallow = false;
static bool g_spSwallow = false;

struct QqCtx { DWORD pid; bool found; };

static BOOL CALLBACK QqCloseEnum(HWND h, LPARAM lp) {
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (pid == ((QqCtx*)lp)->pid && IsWindowVisible(h) && !GetWindow(h, GW_OWNER))
        PostMessageW(h, WM_CLOSE, 0, 0);
    return TRUE;
}

static BOOL CALLBACK QqVisibleEnum(HWND h, LPARAM lp) {
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (pid == ((QqCtx*)lp)->pid && IsWindowVisible(h)) { ((QqCtx*)lp)->found = true; return FALSE; }
    return TRUE;
}

// uwp apps live inside an ApplicationFrameWindow, the real process is the CoreWindow child
static BOOL CALLBACK QqChildEnum(HWND h, LPARAM lp) {
    WCHAR cls[64];
    if (GetClassNameW(h, cls, 64) && wcscmp(cls, L"Windows.UI.Core.CoreWindow") == 0) {
        DWORD pid = 0;
        GetWindowThreadProcessId(h, &pid);
        if (pid) { *(DWORD*)lp = pid; return FALSE; }
    }
    return TRUE;
}

static bool QqExeName(DWORD pid, WCHAR* out, DWORD cap) {
    HANDLE ph = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!ph) return false;
    WCHAR path[MAX_PATH];
    DWORD len = MAX_PATH;
    bool ok = QueryFullProcessImageNameW(ph, 0, path, &len) != 0;
    CloseHandle(ph);
    if (!ok) return false;
    PCWSTR base = wcsrchr(path, L'\\');
    base = base ? base + 1 : path;
    wcsncpy(out, base, cap - 1);
    out[cap - 1] = 0;
    return true;
}

static bool QqProtected(PCWSTR exe) {
    static const PCWSTR k[] = {
        L"explorer.exe", L"ApplicationFrameHost.exe", L"ShellExperienceHost.exe",
        L"StartMenuExperienceHost.exe", L"SearchHost.exe", L"SearchApp.exe", L"TextInputHost.exe",
        L"LockApp.exe", L"dwm.exe", L"winlogon.exe", L"csrss.exe", L"LogonUI.exe",
        L"taskmgr.exe", L"windhawk.exe", L"SystemSettings.exe"
    };
    for (PCWSTR n : k) if (_wcsicmp(exe, n) == 0) return true;
    return false;
}

static DWORD WINAPI QqKillThread(LPVOID p) {
    DWORD pid = (DWORD)(UINT_PTR)p;
    Sleep(1500);
    QqCtx c = { pid, false };
    EnumWindows(QqVisibleEnum, (LPARAM)&c);
    if (c.found) return 0;   // something is still open, e.g. a save prompt
    HANDLE ph = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (ph) { TerminateProcess(ph, 0); CloseHandle(ph); }
    return 0;
}

static void QqQuit(HWND fg) {
    if (!fg || !IsWindow(fg)) return;
    WCHAR cls[64] = L"";
    GetClassNameW(fg, cls, 64);
    if (!wcscmp(cls, L"Progman") || !wcscmp(cls, L"WorkerW") ||
        !wcscmp(cls, L"Shell_TrayWnd") || !wcscmp(cls, L"Shell_SecondaryTrayWnd")) return;

    DWORD pid = 0;
    GetWindowThreadProcessId(fg, &pid);
    if (!pid || pid == GetCurrentProcessId()) return;

    WCHAR exe[MAX_PATH] = L"";
    bool known = QqExeName(pid, exe, MAX_PATH);

    if (known && _wcsicmp(exe, L"ApplicationFrameHost.exe") == 0) {
        DWORD appPid = 0;
        EnumChildWindows(fg, QqChildEnum, (LPARAM)&appPid);
        PostMessageW(fg, WM_CLOSE, 0, 0);
        WCHAR appExe[MAX_PATH] = L"";
        if (appPid && QqExeName(appPid, appExe, MAX_PATH) && !QqProtected(appExe)) {
            HANDLE t = CreateThread(nullptr, 0, QqKillThread, (LPVOID)(UINT_PTR)appPid, 0, nullptr);
            if (t) CloseHandle(t);
        }
        return;
    }
    if (!known) { PostMessageW(fg, WM_CLOSE, 0, 0); return; }
    if (_wcsicmp(exe, L"explorer.exe") == 0) {            // File Explorer: just this window
        PostMessageW(fg, WM_CLOSE, 0, 0);
        return;
    }
    if (QqProtected(exe)) return;

    QqCtx c = { pid, false };
    EnumWindows(QqCloseEnum, (LPARAM)&c);
    HANDLE t = CreateThread(nullptr, 0, QqKillThread, (LPVOID)(UINT_PTR)pid, 0, nullptr);
    if (t) CloseHandle(t);
}

// ---- display scaling ----

#define SS_MSG_STEP (WM_APP + 1)

static HANDLE        g_ssThread = nullptr;
static DWORD         g_ssTid = 0;
static volatile LONG g_ssBusy = 0;

struct SsGetDpi { DISPLAYCONFIG_DEVICE_INFO_HEADER header; INT32 minScaleRel; INT32 curScaleRel; INT32 maxScaleRel; };
struct SsSetDpi { DISPLAYCONFIG_DEVICE_INFO_HEADER header; INT32 scaleRel; };

static const int kDpi[] = { 100, 125, 150, 175, 200, 225, 250, 300, 350, 400, 450, 500 };

static void SsStep(int dir, POINT pt) {
    HMONITOR mon = MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFOEXW mi = {};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(mon, &mi)) return;

    UINT32 np = 0, nm = 0;
    if (GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &np, &nm) != ERROR_SUCCESS || !np) return;
    DISPLAYCONFIG_PATH_INFO* paths = (DISPLAYCONFIG_PATH_INFO*)calloc(np, sizeof(*paths));
    DISPLAYCONFIG_MODE_INFO* modes = (DISPLAYCONFIG_MODE_INFO*)calloc(nm ? nm : 1, sizeof(*modes));
    if (!paths || !modes) { free(paths); free(modes); return; }
    if (QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &np, paths, &nm, modes, nullptr) == ERROR_SUCCESS) {
        for (UINT32 i = 0; i < np; i++) {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sn = {};
            sn.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sn.header.size = sizeof(sn);
            sn.header.adapterId = paths[i].sourceInfo.adapterId;
            sn.header.id = paths[i].sourceInfo.id;
            if (DisplayConfigGetDeviceInfo(&sn.header) != ERROR_SUCCESS) continue;
            if (_wcsicmp(sn.viewGdiDeviceName, mi.szDevice) != 0) continue;

            SsGetDpi g = {};
            g.header.type = (DISPLAYCONFIG_DEVICE_INFO_TYPE)-3;
            g.header.size = sizeof(g);
            g.header.adapterId = paths[i].sourceInfo.adapterId;
            g.header.id = paths[i].sourceInfo.id;
            if (DisplayConfigGetDeviceInfo(&g.header) != ERROR_SUCCESS) break;

            int rec = -g.minScaleRel;                 // index of the recommended scale
            int cur = rec + g.curScaleRel;
            int nxt = cur + dir;
            int maxIdx = rec + g.maxScaleRel;
            if (nxt < 0) nxt = 0;
            if (nxt > maxIdx) nxt = maxIdx;
            if (nxt >= (int)(sizeof(kDpi) / sizeof(kDpi[0]))) nxt = (int)(sizeof(kDpi) / sizeof(kDpi[0])) - 1;
            if (nxt == cur) break;

            SsSetDpi s = {};
            s.header.type = (DISPLAYCONFIG_DEVICE_INFO_TYPE)-4;
            s.header.size = sizeof(s);
            s.header.adapterId = paths[i].sourceInfo.adapterId;
            s.header.id = paths[i].sourceInfo.id;
            s.scaleRel = nxt - rec;
            LONG r = DisplayConfigSetDeviceInfo(&s.header);
            Wh_Log(L"Scale %d%% -> %d%% (result %ld)", kDpi[cur], kDpi[nxt], r);
            break;
        }
    }
    free(paths);
    free(modes);
}

static DWORD WINAPI SsThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);   // create the message queue
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.message == SS_MSG_STEP) {
            POINT pt = { (short)LOWORD(msg.lParam), (short)HIWORD(msg.lParam) };
            SsStep((int)msg.wParam, pt);
            Sleep(250);                       // let Windows settle, one step per pause
            InterlockedExchange(&g_ssBusy, 0);
        }
    }
    return 0;
}

// ---- Settings ----

static void SuTrim(WCHAR* s) {
    size_t n = wcslen(s), a = 0;
    while (a < n && (s[a] == L' ' || s[a] == L'\t' || s[a] == L'"')) a++;
    while (n > a && (s[n - 1] == L' ' || s[n - 1] == L'\t' || s[n - 1] == L'"')) n--;
    if (a) memmove(s, s + a, (n - a) * sizeof(WCHAR));
    s[n - a] = 0;
}

static void SuAlnum(WCHAR* dst, size_t cap, PCWSTR src, size_t maxN) {
    size_t o = wcslen(dst), added = 0;
    for (; *src && added < maxN && o + 1 < cap; src++) {
        WCHAR c = *src;
        if ((c >= L'0' && c <= L'9') || (c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z')) {
            dst[o++] = c;
            added++;
        }
    }
    dst[o] = 0;
}

static void SuGetStr(WCHAR* dst, int cap, PCWSTR name, int i) {
    PCWSTR v = Wh_GetStringSetting(name, i);
    lstrcpynW(dst, v ? v : L"", cap);
    Wh_FreeStringSetting(v);
    SuTrim(dst);
}

static int SuParseMode(PCWSTR s) {
    if (wcscmp(s, L"numlock_on") == 0) return 2;
    if (wcscmp(s, L"numlock_any") == 0) return 3;
    return 1;
}

static bool SuBuildPin(int i, Pin& p) {
    memset(&p, 0, sizeof(p));
    int key = Wh_GetIntSetting(L"slot%d_key", i);
    WCHAR prog[MAX_PATH];
    SuGetStr(prog, MAX_PATH, L"slot%d_program", i);
    if (key < 1 || key > 9 || !prog[0]) return false;

    PCWSTR slash = wcsrchr(prog, L'\\');
    PCWSTR slash2 = wcsrchr(prog, L'/');
    if (slash2 > slash) slash = slash2;
    lstrcpynW(p.exe, slash ? slash + 1 : prog, MAX_PATH);
    if (!wcschr(p.exe, L'.')) wcscat_s(p.exe, L".exe");
    if (slash) lstrcpynW(p.path, prog, MAX_PATH);

    SuGetStr(p.title, 128, L"slot%d_title", i);

    PCWSTR modeS = Wh_GetStringSetting(L"slot%d_numlock", i);
    p.mode = SuParseMode(modeS ? modeS : L"");
    Wh_FreeStringSetting(modeS);
    p.numKey = key;

    p.defW = 440;
    p.defH = 640;
    if (_wcsicmp(p.exe, L"explorer.exe") == 0) {
        wcscpy_s(p.cls, L"CabinetWClass");
        p.defW = 640;
        p.defH = 480;
    } else if (_wcsicmp(p.exe, L"ApplicationFrameHost.exe") == 0) {
        wcscpy_s(p.cls, L"ApplicationFrameWindow");
        p.defW = 320;
        p.defH = 360;
    }

    p.key[0] = 0;
    SuAlnum(p.key, 48, p.exe, 24);
    SuAlnum(p.key, 48, p.title, 14);
    return true;
}

// keep = true on a settings change, slots that didn't change keep their windows
// so they don't jump back to the saved spots
static void LoadConfig(bool keep) {
    static Pin nw[SU_MAX_SLOTS];
    static Pin old[SU_MAX_SLOTS];
    int oldN = g_npins;
    if (keep) memcpy(old, g_pins, sizeof(old));

    g_optAltQ  = Wh_GetIntSetting(L"altQ") ? 1 : 0;
    g_optScale = Wh_GetIntSetting(L"scaleScroll") ? 1 : 0;
    g_optSnip  = Wh_GetIntSetting(L"shiftSpaceSnip") ? 1 : 0;

    PCWSTR bm = Wh_GetStringSetting(L"builtinNumLock");
    g_builtinMode = SuParseMode(bm ? bm : L"");
    Wh_FreeStringSetting(bm);

    int n = 0;
    for (int i = 1; i <= SU_MAX_SLOTS; i++) {
        if (SuBuildPin(i, nw[n])) n++;
    }

    if (keep) {
        bool used[SU_MAX_SLOTS] = {};
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < oldN; j++) {
                if (used[j]) continue;
                if (_wcsicmp(nw[k].exe, old[j].exe) == 0 && wcscmp(nw[k].title, old[j].title) == 0) {
                    memcpy(nw[k].win, old[j].win, sizeof(nw[k].win));
                    nw[k].n = old[j].n;
                    memcpy(nw[k].hid, old[j].hid, sizeof(nw[k].hid));
                    nw[k].nHid = old[j].nHid;
                    used[j] = true;
                    break;
                }
            }
        }
        for (int j = 0; j < oldN; j++) {
            if (!used[j]) PinRestoreLook(old[j]);
        }
    }

    int modes[10] = {};
    const int builtin[4] = { 0, 3, 4, 7 };
    for (int d = 0; d < 4; d++) modes[builtin[d]] |= g_builtinMode;
    for (int k = 0; k < n; k++) modes[nw[k].numKey] |= nw[k].mode;

    g_npins = 0;
    memcpy(g_pins, nw, sizeof(Pin) * n);
    g_npins = n;
    for (int d = 0; d < 10; d++) g_modeOf[d] = modes[d];
}

static LRESULT CALLBACK SuMsgProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case SU_WM_CMD:
            SuCommand((int)wp, (int)lp);
            return 0;
        case SU_WM_ZOOM:
            SuZoomStep((HWND)wp, (int)lp);
            return 0;
        case SU_WM_QUIT:
            QqQuit((HWND)wp);
            return 0;
        case SU_WM_RELOAD:
            LoadConfig(true);
            return 0;
        case WM_TIMER:
            if (wp == 1) {
                for (int k = 0; k < g_npins; k++) PinScan(g_pins[k]);
            } else if (wp == 2) {
                for (int k = 0; k < g_npins; k++)
                    for (int i = 0; i < g_pins[k].n; i++)
                        if (IsWindow(g_pins[k].win[i])) PinAlphaSync(g_pins[k].win[i]);
                if (g_sliderHwnd) PinAlphaSync(g_sliderHwnd);
            } else if (wp == 3) {
                HWND s = g_sliderHwnd;
                if (s) {
                    if ((int)g_numLock != g_lastNl) {
                        g_lastNl = (int)g_numLock;
                        InvalidateRect(s, nullptr, FALSE);
                    }
                    if (IsWindowVisible(s) && !(GetWindowLongPtrW(s, GWL_EXSTYLE) & WS_EX_TOPMOST))
                        SetWindowPos(s, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                }
            }
            return 0;
        case WM_CLOSE:
            if (g_sliderHwnd) { DestroyWindow(g_sliderHwnd); g_sliderHwnd = nullptr; }
            if (g_helpHwnd) { DestroyWindow(g_helpHwnd); g_helpHwnd = nullptr; }
            DestroyWindow(hWnd);
            return 0;
        case WM_DESTROY:
            KillTimer(hWnd, 1);
            KillTimer(hWnd, 2);
            KillTimer(hWnd, 3);
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hWnd, msg, wp, lp);
}

static DWORD WINAPI SuWorker(LPVOID) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HINSTANCE inst = GetModuleHandleW(nullptr);

    WNDCLASSW mc = {};
    mc.lpfnWndProc = SuMsgProc;
    mc.hInstance = inst;
    mc.lpszClassName = L"ResettiSuiteMessageWindow";
    RegisterClassW(&mc);

    WNDCLASSW sc = {};
    sc.lpfnWndProc = SliderProc;
    sc.hInstance = inst;
    sc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    sc.lpszClassName = L"ResettiSuiteSlider";
    RegisterClassW(&sc);

    WNDCLASSW hc = {};
    hc.lpfnWndProc = HelpProc;
    hc.hInstance = inst;
    hc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    hc.lpszClassName = L"ResettiSuiteHelp";
    RegisterClassW(&hc);

    HWND msgWnd = CreateWindowExW(0, mc.lpszClassName, L"", 0, 0, 0, 0, 0,
                                  HWND_MESSAGE, nullptr, inst, nullptr);
    if (!msgWnd) {
        Wh_Log(L"Message window failed (%u)", GetLastError());
        return 1;
    }

    g_sdpi = (int)GetDpiForSystem();
    if (g_sdpi < 96) g_sdpi = 96;
    HWND sl = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_LAYERED,
                              sc.lpszClassName, L"Taskumatti", WS_POPUP,
                              0, 0, SSc(380), SSc(26), nullptr, nullptr, inst, nullptr);
    if (sl) {
        UINT d = GetDpiForWindow(sl);
        if (d) g_sdpi = (int)d;
        g_sliderHwnd = sl;
        SetLayeredWindowAttributes(sl, 0, 255, LWA_ALPHA);
        SliderPlace();
        PinAlphaSync(sl);
        ShowWindow(sl, SW_SHOWNA);
    }

    g_cmdWnd = msgWnd;
    SetTimer(msgWnd, 1, 300, nullptr);   // look for new windows
    SetTimer(msgWnd, 2, 40, nullptr);    // opacity follows slider and window width
    SetTimer(msgWnd, 3, 250, nullptr);   // NumLock indicator, keep slider on top

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    g_cmdWnd = nullptr;
    g_sliderHwnd = nullptr;
    UnregisterClassW(sc.lpszClassName, inst);
    UnregisterClassW(L"ResettiSuiteHelp", inst);
    UnregisterClassW(mc.lpszClassName, inst);
    return 0;
}

// ---- keyboard hook ----
// numpad keys are matched by scan code, so it doesn't matter if shift turned them into Home/End/arrows

static HHOOK  g_kbHook = nullptr;
static HANDLE g_hookThread = nullptr;
static DWORD  g_hookTid = 0;
static bool   g_ctrl = false;
static bool   g_shift = false;
static bool   g_nlHeld = false;
static bool   g_swallow[10] = {};

static int NumpadIndex(const KBDLLHOOKSTRUCT* k) {
    if (k->flags & LLKHF_EXTENDED) return -1;   // the dedicated Home/End/arrow block
    switch (k->scanCode) {
        case 0x52: return 0;
        case 0x4F: return 1;
        case 0x50: return 2;
        case 0x51: return 3;
        case 0x4B: return 4;
        case 0x4C: return 5;
        case 0x4D: return 6;
        case 0x47: return 7;
        case 0x48: return 8;
        case 0x49: return 9;
    }
    return -1;
}

static void SuSnip() {
    SuKeyEvt(VK_LWIN, false);
    SuKeyEvt('S', false);
    SuKeyEvt('S', true);
    SuKeyEvt(VK_LWIN, true);
}

static LRESULT CALLBACK SuKbProc(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION) {
        const KBDLLHOOKSTRUCT* k = (const KBDLLHOOKSTRUCT*)lp;
        bool injected = (k->flags & LLKHF_INJECTED) != 0;
        bool down = (wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN);
        bool up = (wp == WM_KEYUP || wp == WM_SYSKEYUP);

        // windows fakes shift releases for shift+numpad, so only real events count
        // the fake ones have scan codes over 0xFF, skip those too
        if (!injected && k->scanCode <= 0xFF) {
            switch (k->vkCode) {
                case VK_LCONTROL: case VK_RCONTROL: case VK_CONTROL:
                    g_ctrl = down;
                    break;
                case VK_LSHIFT: case VK_RSHIFT: case VK_SHIFT:
                    g_shift = down;
                    break;
                case VK_NUMLOCK:
                    if (down && !g_nlHeld) { g_nlHeld = true; InterlockedExchange(&g_numLock, g_numLock ? 0 : 1); }
                    if (up) g_nlHeld = false;
                    break;
            }
        }

        // Alt+Q: quit the focused program.
        if (!injected && k->vkCode == 'Q' && g_optAltQ) {
            if (down) {
                bool alt = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
                bool bad = (GetAsyncKeyState(VK_SHIFT) & 0x8000) || (GetAsyncKeyState(VK_CONTROL) & 0x8000) ||
                           (GetAsyncKeyState(VK_LWIN) & 0x8000) || (GetAsyncKeyState(VK_RWIN) & 0x8000);
                if (alt && !bad) {
                    if (!g_qqSwallow) {
                        g_qqSwallow = true;
                        // same dummy key trick
                        INPUT in[2] = {};
                        in[0].type = INPUT_KEYBOARD; in[0].ki.wVk = 0xFC;
                        in[1].type = INPUT_KEYBOARD; in[1].ki.wVk = 0xFC; in[1].ki.dwFlags = KEYEVENTF_KEYUP;
                        SendInput(2, in, sizeof(INPUT));
                        HWND c = g_cmdWnd;
                        if (c) PostMessageW(c, SU_WM_QUIT, (WPARAM)GetForegroundWindow(), 0);
                    }
                    return 1;
                }
            } else if (up && g_qqSwallow) {
                g_qqSwallow = false;
                return 1;
            }
        }

        // Shift+Space: snipping tool (Win+Shift+S).
        if (!injected && k->vkCode == VK_SPACE && g_optSnip) {
            if (down) {
                bool shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
                bool bad = (GetAsyncKeyState(VK_MENU) & 0x8000) || (GetAsyncKeyState(VK_CONTROL) & 0x8000) ||
                           (GetAsyncKeyState(VK_LWIN) & 0x8000) || (GetAsyncKeyState(VK_RWIN) & 0x8000);
                if (shift && !bad) {
                    if (!g_spSwallow) {
                        g_spSwallow = true;
                        SuSnip();
                    }
                    return 1;
                }
            } else if (up && g_spSwallow) {
                g_spSwallow = false;
                return 1;
            }
        }

        // Ctrl / Shift + numpad digit
        int n = NumpadIndex(k);
        if (n >= 0 && !injected) {
            if (down) {
                bool other = (GetAsyncKeyState(VK_MENU) & 0x8000) ||
                             (GetAsyncKeyState(VK_LWIN) & 0x8000) ||
                             (GetAsyncKeyState(VK_RWIN) & 0x8000);
                int nlBit = g_numLock ? 2 : 1;
                if ((g_modeOf[n] & nlBit) && !other && (g_ctrl != g_shift) && !(n == 0 && g_shift)) {
                    if (!g_swallow[n]) {
                        g_swallow[n] = true;
                        HWND c = g_cmdWnd;
                        if (c) PostMessageW(c, SU_WM_CMD, g_ctrl ? 0 : 1, n);
                    }
                    return 1;
                }
            } else if (up && g_swallow[n]) {
                g_swallow[n] = false;
                return 1;
            }
        }
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}

// shift / alt + wheel over obsidian zooms it
static HHOOK g_mouseHook = nullptr;

static bool SuIsZoomWindow(HWND root) {
    for (int k = 0; k < g_npins; k++) {
        if (_wcsicmp(g_pins[k].exe, L"obsidian.exe") == 0 && PinHas(g_pins[k], root)) return true;
    }
    return false;
}

static LRESULT CALLBACK SuMouseProc(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION && wp == WM_MOUSEWHEEL) {
        bool alt = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
        bool shiftKey = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;

        // Alt+Shift+wheel: display scaling
        if (g_optScale && alt && shiftKey) {
            bool other = (GetAsyncKeyState(VK_CONTROL) & 0x8000) ||
                         (GetAsyncKeyState(VK_LWIN) & 0x8000) || (GetAsyncKeyState(VK_RWIN) & 0x8000);
            if (!other) {
                const MSLLHOOKSTRUCT* ms = (const MSLLHOOKSTRUCT*)lp;
                short delta = (short)HIWORD(ms->mouseData);
                // dummy key so alt+shift doesn't switch the keyboard layout
                INPUT in[2] = {};
                in[0].type = INPUT_KEYBOARD; in[0].ki.wVk = 0xFC;
                in[1].type = INPUT_KEYBOARD; in[1].ki.wVk = 0xFC; in[1].ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(2, in, sizeof(INPUT));
                if (InterlockedCompareExchange(&g_ssBusy, 1, 0) == 0) {
                    if (!PostThreadMessageW(g_ssTid, SS_MSG_STEP, (WPARAM)(delta > 0 ? 1 : -1),
                                            MAKELPARAM((short)ms->pt.x, (short)ms->pt.y)))
                        InterlockedExchange(&g_ssBusy, 0);
                }
                return 1;
            }
        }

        // obsidian zoom
        bool trig = !g_ctrl && ((g_shift && !alt) || (alt && !g_shift));
        if (trig) {
            MSLLHOOKSTRUCT* ms = (MSLLHOOKSTRUCT*)lp;
            HWND w = WindowFromPoint(ms->pt);
            HWND root = w ? GetAncestor(w, GA_ROOT) : nullptr;
            HWND c = g_cmdWnd;
            if (root && c && SuIsZoomWindow(root)) {
                short delta = (short)HIWORD(ms->mouseData);
                PostMessageW(c, SU_WM_ZOOM, (WPARAM)root, delta > 0 ? 1 : -1);
                return 1;   // swallow the wheel event
            }
        }
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}

static DWORD WINAPI SuHookThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);   // create the queue
    g_ctrl = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
    g_shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    InterlockedExchange(&g_numLock, (GetKeyState(VK_NUMLOCK) & 1) ? 1 : 0);
    g_kbHook = SetWindowsHookExW(WH_KEYBOARD_LL, SuKbProc, GetModuleHandleW(nullptr), 0);
    if (!g_kbHook) Wh_Log(L"Keyboard hook failed (%u)", GetLastError());
    g_mouseHook = SetWindowsHookExW(WH_MOUSE_LL, SuMouseProc, GetModuleHandleW(nullptr), 0);
    if (!g_mouseHook) Wh_Log(L"Mouse hook failed (%u)", GetLastError());
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    if (g_mouseHook) { UnhookWindowsHookEx(g_mouseHook); g_mouseHook = nullptr; }
    if (g_kbHook) { UnhookWindowsHookEx(g_kbHook); g_kbHook = nullptr; }
    return 0;
}

// ---- Windhawk callbacks ----

BOOL WhTool_ModInit() {
    g_basePct = SuClamp(Wh_GetIntValue(L"BasePct", 85), 0, 100);
    LoadConfig(false);
    tman::Init();
    g_worker = CreateThread(nullptr, 0, SuWorker, nullptr, 0, nullptr);
    g_ssThread = CreateThread(nullptr, 0, SsThread, nullptr, 0, &g_ssTid);
    g_hookThread = CreateThread(nullptr, 0, SuHookThread, nullptr, 0, &g_hookTid);
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    HWND c = g_cmdWnd;
    if (c) PostMessageW(c, SU_WM_RELOAD, 0, 0);
}

void WhTool_ModUninit() {
    if (g_hookThread) {
        PostThreadMessageW(g_hookTid, WM_QUIT, 0, 0);
        WaitForSingleObject(g_hookThread, 2000);
        CloseHandle(g_hookThread);
        g_hookThread = nullptr;
    }
    if (g_ssThread) {
        PostThreadMessageW(g_ssTid, WM_QUIT, 0, 0);
        WaitForSingleObject(g_ssThread, 2000);
        CloseHandle(g_ssThread);
        g_ssThread = nullptr;
    }
    HWND c = g_cmdWnd;
    if (c) PostMessageW(c, WM_CLOSE, 0, 0);
    if (g_worker) {
        WaitForSingleObject(g_worker, 3000);
        CloseHandle(g_worker);
        g_worker = nullptr;
    }
    for (int k = 0; k < g_npins; k++) PinRestoreLook(g_pins[k]);
    tman::Uninit();
}

////////////////////////////////////////////////////////////////////////////////
// Windhawk tool mod implementation for mods which don't need to inject to other
// processes or hook other functions. Context:
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process
//
// The mod will load and run in a dedicated windhawk.exe process.
//
// Paste the code below as part of the mod code, and use these callbacks:
// * WhTool_ModInit
// * WhTool_ModSettingsChanged
// * WhTool_ModUninit
//
// Currently, other callbacks are not supported.

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) &&
        sessionId == 0) {
        return FALSE;
    }

    bool isExcluded = false;
    bool isToolModProcess = false;
    bool isCurrentToolModProcess = false;
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
    if (!argv) {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0) {
            isExcluded = true;
            break;
        }
    }

    for (int i = 1; i < argc - 1; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0) {
            isToolModProcess = true;
            if (wcscmp(argv[i + 1], WH_MOD_ID) == 0) {
                isCurrentToolModProcess = true;
            }
            break;
        }
    }

    LocalFree(argv);

    if (isExcluded) {
        return FALSE;
    }

    if (isCurrentToolModProcess) {
        g_toolModProcessMutex =
            CreateMutex(nullptr, TRUE, L"windhawk-tool-mod_" WH_MOD_ID);
        if (!g_toolModProcessMutex) {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }

        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        if (!WhTool_ModInit()) {
            ExitProcess(1);
        }

        IMAGE_DOS_HEADER* dosHeader =
            (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);

        DWORD entryPointRVA = ntHeaders->OptionalHeader.AddressOfEntryPoint;
        void* entryPoint = (BYTE*)dosHeader + entryPointRVA;

        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess) {
        return FALSE;
    }

    g_isToolModProcessLauncher = true;
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) {
        return;
    }

    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath,
                              ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR
    commandLine[MAX_PATH + 2 +
                (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath,
               WH_MOD_ID);

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule) {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule) {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE hUserToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
        LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
        LPSTARTUPINFOW lpStartupInfo,
        LPPROCESS_INFORMATION lpProcessInformation,
        PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule,
                                                 "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine,
                                 nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                                 nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"CreateProcess failed");
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModUninit();
    ExitProcess(0);
}
