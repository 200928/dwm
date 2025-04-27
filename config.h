/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;  /* border pixel of windows */
static const unsigned int snap      = 64; /* snap pixel */
static const unsigned int gappih    = 0;  /* 窗体之间的水平内部间隙 */
static const unsigned int gappiv    = 0;  /* 窗体之间的垂直内部间隙 */
static const unsigned int gappoh    = 0;  /* 窗口和屏幕边缘之间的垂直外部间隙 */
static const unsigned int gappov    = 0;  /* 窗口和屏幕边缘之间的水平外部间隙*/
static int                smartgaps = 1;  /* 1 means no outer gap when there is
  only one window */

static const int   showbar = 1; /* 0 means no bar */
static const int   topbar  = 1; /* 0 means bottom bar */
// static const char *fonts[]          = { "monospace:size=10" };
static const char* fonts[] = {
    "UbuntuMono Nerd Font:size=10",
    "Mono:size=10:style=Regular:antialias=true:autohint=true",
    "WenQuanYi Micro Hei:size=10:style=Regular:antialias=true:autohint=true"};
// "JetBrains Mono SemiBold:size=10",
// static const char *fonts[] = {
// "JetBrains Mono SemiBold:size=10",
// "Rec Mono Casual:style=Regular:size=11:LineHeight=1.2"
// "SauceCodePro Nerd Font Mono:size=10",
//"UbuntuMono Nerd Font Mono:size=10:type=Regular:antialias=true:autohint=true",
// "Rec Mono Casual:size=11:type=Regular:antialias=true:autohint=true",
// "WenQuanYi Micro Hei:size=10:type=Regular:antialias=true:autohint=true"
//"JoyPixels:pixelsize=10:type=Regular:antialias=true:autohint=true" };
//};
// static const char dmenufont[]       = "monospace:size=10";
static const char         dmenufont[] = "WenQuanYi Micro Hei:size=11";
static const char         col_gray1[] = "#222222";
static const char         col_gray2[] = "#444444";
static const char         col_gray3[] = "#bbbbbb";
static const char         col_gray4[] = "#ffffff";
static const char         col_cyan[]  = "#37474F";
static const char         col_cyan_[] = "#42A5F5";
// static const char col_cyan_[]       = "#ffd9e6";
static const unsigned int baralpha    = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char*        colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel]  = {col_gray4, col_cyan,  col_cyan_},
};
static const unsigned int alphas[][3] = {
    /*               fg      bg        border     */
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel]  = {OPAQUE, baralpha, borderalpha},
};

/* tagging */
static const char* tags[] = {"一", "二", "三", "四", "五",
                             "六", "七", "八", "九"};
// static const char *tags[] = { "₁", "₂", "₃", "₄", "₅", "₆", "₇", "₈", "₉" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp",    NULL, NULL, 0,      1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact   = 0.55; /* factor of master area size [0.05..0.95] */
static const int   nmaster = 1;    /* number of clients in master area */
static const int   resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT \
	1 /* nrowgrid layout: force two clients to always split vertica ly */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[平铺]", tile                  }, /* first entry is default */
    {"[M]",    monocle               },
    {"[螺旋]", spiral                },
    {"[\\]",   dwindle               },
    {"H[]",    deck                  },
    {"TTT",    bstack                },
    {"===",    bstackhoriz           },
    {"HHH",    grid                  },
    {"###",    nrowgrid              },
    {"---",    horizgrid             },
    {":::",    gaplessgrid           },
    {"|M|",    centeredmaster        },
    {">M>",    centeredfloatingmaster},
    {"浮动",   NULL                  }, /* no layout function means floating behavior */
    {NULL,     NULL                  },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                          \
	{MODKEY, KEY, view, {.ui = 1 << TAG}},                         \
	    {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}}, \
	    {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},          \
	    {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                          \
	{                                                       \
		.v = (const char*[]) { "/bin/sh", "-c", cmd, NULL } \
	}

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char* dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
// static const char *termcmd[]  = { "st", NULL };
static const char* termcmd[]        = {"alacritty", NULL};
static const char  scratchpadname[] = "scratchpad";
static const char* scratchpadcmd[]  = {"st", "-t",     scratchpadname,
                                       "-g", "120x30", NULL};
static const char* voldown[]        = {"/home/ming/scripts/voldown.sh", NULL};
static const char* volup[]          = {"/home/ming/scripts/volup.sh", NULL};
static const char* voltoggle[]      = {"/home/ming/scripts/voltoggle.sh", NULL};
static const char* microphone_toggle[] = {
    "/home/ming/scripts/microphone_toggle.sh", NULL};
static const char* flameshot[]      = {"/home/ming/scripts/flameshot.sh", NULL};
static const char* flameshot_gui[]  = {"/home/ming/scripts/flameshot_gui.sh",
                                       NULL};
static const char* kill_flameshot[] = {"killall", "flameshot", NULL};
static const char* lightdown[]      = {"/home/ming/scripts/lightdown.sh", NULL};
static const char* lightup[]        = {"/home/ming/scripts/lightup.sh", NULL};
static const char* typora[]         = {"kstart5", "/opt/typora/Typora", NULL};
static const char* chrome[]         = {"google-chrome-stable",
                                       "--proxy-server=127.0.0.1:8889", NULL};
static const char* yesplaymusic[]   = {"kstart5",
                                       "/opt/YesPlayMusic/yesplaymusic", NULL};
static const char* kdeconnect_handler[] = {"kdeconnect-handler", NULL};
static const char* dolphin[]            = {"dolphin", NULL};
static const char* qv2ray[]             = {"kstart5", "qv2ray", NULL};
static const char* trayer[]   = {"/home/ming/scripts/trayer.sh", NULL};
static const char* redshift[] = {"/home/ming/scripts/redshift.sh", NULL};
static const char* slock[]    = {"slock", NULL};
static const char* change_wallpaper[] = {
    "/home/ming/scripts/change_wallpaper.sh", NULL};
static const char* nvim[]       = {"nvim", NULL};
static const char* rofi[]       = {"/home/ming/scripts/rofi.sh", NULL};
static const char* rofi_start[] = {"rofi", "-show", NULL};
static const char* powermenu[]  = {"/home/ming/scripts/powermenu.sh", NULL};
static const char* time[]       = {"/home/ming/scripts/time.sh", NULL};
static Key         keys[]       = {
    /* modifier                     key        function        argument */
    //================================音量和亮度调节====================================
    {Mod4Mask,                           XK_F1,     spawn,          {.v = voltoggle}         },
    {Mod4Mask,                           XK_F2,     spawn,          {.v = voldown}           },
    {Mod4Mask,                           XK_F3,     spawn,          {.v = volup}             },
    {Mod4Mask,                           XK_F4,     spawn,          {.v = microphone_toggle} },
    {Mod4Mask,                           XK_F5,     spawn,          {.v = lightdown}         },
    {Mod4Mask,                           XK_F6,     spawn,          {.v = lightup}           },
    {Mod4Mask,                           XK_F7,     spawn,          {.v = change_wallpaper}  },
    {Mod4Mask,                           XK_F9,     spawn,          {.v = redshift}          },
    {Mod1Mask,                           XK_l,      spawn,          {.v = powermenu}         },
    //=================================自定义快捷键=====================================
    {Mod1Mask | ControlMask,             XK_a,      spawn,          {.v = flameshot}         },
    {Mod1Mask | ControlMask,             XK_z,      spawn,          {.v = flameshot_gui}     },
    {Mod1Mask | ControlMask | ShiftMask, XK_z,      spawn,          {.v = kill_flameshot}    },
    {ControlMask | Mod1Mask,             XK_t,      spawn,          {.v = typora}            },
    {ControlMask | Mod1Mask,             XK_g,      spawn,          {.v = chrome}            },
    {ControlMask | Mod1Mask,             XK_m,      spawn,          {.v = yesplaymusic}      },
    {ControlMask | Mod1Mask,             XK_p,      spawn,          {.v = kdeconnect_handler}},
    {ControlMask | Mod1Mask,             XK_q,      spawn,          {.v = qv2ray}            },
    {ControlMask | Mod1Mask,             XK_v,      spawn,          {.v = nvim}              },
    {Mod4Mask,                           XK_e,      spawn,          {.v = dolphin}           },
    {Mod4Mask,                           XK_t,      spawn,          {.v = time}              },
    {Mod1Mask | ShiftMask,               XK_t,      spawn,          {.v = trayer}            },
    //===================================默认===========================================
    {MODKEY,                             XK_grave,  togglescratch,  {.v = scratchpadcmd}     },
    {Mod1Mask,                           XK_k,      hidewin,        {0}                      },
    {Mod1Mask | ShiftMask,               XK_k,      restorewin,     {0}                      },
    {MODKEY | ShiftMask,                 XK_Return, spawn,          {.v = termcmd}           },
    {MODKEY | ShiftMask,                 XK_space,  togglefloating, {0}                      },
    {MODKEY,                             XK_p,      spawn,          {.v = rofi}              },
    {MODKEY,                             XK_b,      togglebar,      {0}                      },
    {MODKEY | ShiftMask,                 XK_j,      rotatestack,    {.i = +1}                },
    {MODKEY | ShiftMask,                 XK_k,      rotatestack,    {.i = -1}                },
    {MODKEY,                             XK_j,      focusstack,     {.i = +1}                },
    {MODKEY,                             XK_k,      focusstack,     {.i = -1}                },
    {MODKEY,                             XK_a,      focusstack,     {.i = +1}                },
    {MODKEY,                             XK_q,      focusstack,     {.i = -1}                },
    {MODKEY,                             XK_s,      incnmaster,     {.i = +1}                },
    {MODKEY,                             XK_v,      incnmaster,     {.i = -1}                },
    {MODKEY,                             XK_h,      setmfact,       {.f = -0.05}             },
    {MODKEY,                             XK_l,      setmfact,       {.f = +0.05}             },
    {MODKEY,                             XK_Return, zoom,           {0}                      },
    {MODKEY | Mod1Mask,                  XK_u,      incrgaps,       {.i = +1}                },
    {MODKEY | Mod1Mask | ShiftMask,      XK_u,      incrgaps,       {.i = -1}                },
    {MODKEY | Mod1Mask,                  XK_i,      incrigaps,      {.i = +1}                },
    {MODKEY | Mod1Mask | ShiftMask,      XK_i,      incrigaps,      {.i = -1}                },
    {MODKEY | Mod1Mask,                  XK_o,      incrogaps,      {.i = +1}                },
    {MODKEY | Mod1Mask | ShiftMask,      XK_o,      incrogaps,      {.i = -1}                },
    {MODKEY | Mod1Mask,                  XK_6,      incrihgaps,     {.i = +1}                },
    {MODKEY | Mod1Mask | ShiftMask,      XK_6,      incrihgaps,     {.i = -1}                },
    {MODKEY | Mod1Mask,                  XK_7,      incrivgaps,     {.i = +1}                },
    {MODKEY | Mod1Mask | ShiftMask,      XK_7,      incrivgaps,     {.i = -1}                },
    {MODKEY | Mod1Mask,                  XK_8,      incrohgaps,     {.i = +1}                },
    {MODKEY | Mod1Mask | ShiftMask,      XK_8,      incrohgaps,     {.i = -1}                },
    {MODKEY | Mod1Mask,                  XK_9,      incrovgaps,     {.i = +1}                },
    {MODKEY | Mod1Mask | ShiftMask,      XK_9,      incrovgaps,     {.i = -1}                },
    {MODKEY | Mod1Mask,                  XK_0,      togglegaps,     {0}                      },
    {MODKEY | Mod1Mask | ShiftMask,      XK_0,      defaultgaps,    {0}                      },
    {MODKEY,                             XK_Tab,    view,           {0}                      },
    {MODKEY | ShiftMask,                 XK_c,      killclient,     {0}                      },
    {MODKEY | ShiftMask,                 XK_f,      fullscreen,     {0}                      },
    {MODKEY,                             XK_t,      setlayout,      {.v = &layouts[0]}       },
    {MODKEY,                             XK_f,      setlayout,      {.v = &layouts[1]}       },
    {MODKEY,                             XK_m,      setlayout,      {.v = &layouts[2]}       },
    {ControlMask | ShiftMask,            XK_1,      setlayout,      {.v = &layouts[1]}       },
    {ControlMask | ShiftMask,            XK_2,      setlayout,      {.v = &layouts[2]}       },
    {ControlMask | ShiftMask,            XK_3,      setlayout,      {.v = &layouts[3]}       },
    {ControlMask | ShiftMask,            XK_4,      setlayout,      {.v = &layouts[4]}       },
    {ControlMask | ShiftMask,            XK_5,      setlayout,      {.v = &layouts[5]}       },
    {ControlMask | ShiftMask,            XK_6,      setlayout,      {.v = &layouts[6]}       },
    {ControlMask | ShiftMask,            XK_7,      setlayout,      {.v = &layouts[7]}       },
    {MODKEY,                             XK_space,  setlayout,      {0}                      },
    {MODKEY,                             XK_0,      view,           {.ui = ~0}               },
    {MODKEY | ShiftMask,                 XK_0,      tag,            {.ui = ~0}               },
    {MODKEY,                             XK_comma,  focusmon,       {.i = -1}                },
    {MODKEY,                             XK_period, focusmon,       {.i = +1}                },
    {MODKEY | ShiftMask,                 XK_comma,  tagmon,         {.i = -1}                },
    {MODKEY | ShiftMask,                 XK_period, tagmon,         {.i = +1}                },
    {MODKEY | ShiftMask,                 XK_q,      quit,           {0}                      },
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol,   0,      Button1, setlayout,      {0}               },
    {ClkLtSymbol,   0,      Button3, setlayout,      {.v = &layouts[2]}},
    {ClkWinTitle,   0,      Button2, zoom,           {0}               },
    {ClkStatusText, 0,      Button2, spawn,          {.v = termcmd}    },
    {ClkClientWin,  MODKEY, Button1, movemouse,      {0}               },
    {ClkClientWin,  MODKEY, Button2, togglefloating, {0}               },
    {ClkClientWin,  MODKEY, Button3, resizemouse,    {0}               },
    {ClkTagBar,     0,      Button1, view,           {0}               },
    {ClkTagBar,     0,      Button3, toggleview,     {0}               },
    {ClkTagBar,     MODKEY, Button1, tag,            {0}               },
    {ClkTagBar,     MODKEY, Button3, toggletag,      {0}               },
};
