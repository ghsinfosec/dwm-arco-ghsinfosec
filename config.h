/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "Noto Sans Mono:size=11" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#6790EB";
static const char col_cyan[]        = "#af3a03";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },

	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "140x38", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
const char *spcmd4[] = {"qalculate-gtk", NULL };
const char *spcmd5[] = {"st", "-n", "vol", "-g", "144x41", "-e", "pulsemixer", NULL };
const char *spcmd6[] = {"mousepad", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keepassxc",   spcmd3},
	{"qalculate-gtk",   spcmd4},
	{"vol",   spcmd5},
	{"mousepad",   spcmd6},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
/* static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" }; */
/* static const char *tags[] = { "", "", "", "", "", "", "", "", "" }; */
/* static const char *tags[] = { "Web", "Chat", "Edit", "Meld", "Vb", "Mail", "Video", "Image", "Files" }; */


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *  use tags mask to point an application to a specific workspace
	 */
	/* class                       instance    title      tags mask      isfloating   monitor */
	{ "Gimp",                      NULL,       NULL,       0,            0,           -1 },
	{ "Xfce4-terminal",            NULL,       NULL,       0,            1,           -1 },
	{ "firefox",                   NULL,       NULL,       0,            0,           -1 },
	{ "Arcolinux-welcome-app.py",  NULL,       NULL,       0,            1,           -1 },
	{ "Arcolinux-calamares-tool.py",  NULL,       NULL,       0,            1,           -1 },	
	{ "zoom",	  NULL,			NULL,		1 << 8,			1,			 -1 },
	{ "VirtualBox Manager",	  NULL,			NULL,		1 << 2,			1,			 -1 },
	{ "burp-StartBurp",	  NULL,			NULL,		1 << 3,			1,			 -1 },
	{ "chromium-browser (/home/heath/.BurpSuite/pre-wired-browser)",	  NULL,			NULL,		1 << 3,			1,			 -1 },
	{ NULL,		  "spterm",		NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spfm",		NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "keepassxc",	NULL,		SPTAG(2),		1,			 -1 },
	{ NULL,		  "qalculate-gtk",	NULL,		SPTAG(3),		1,			 -1 },
	{ NULL,		  "vol",	    NULL,		SPTAG(4),		1,			 -1 },
	{ NULL,		  "mousepad",	    NULL,		SPTAG(5),		1,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "HHH",      grid },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *filecmd[] = { "thunar", NULL };
static const char *termcmd[] = { "st", NULL };
static const char *calendar[]  = { "gsimplecal", NULL };
static const char *taskmanager[]  = { "xfce4-taskmanager", NULL };
static const char *webcmd[] = { "brave", NULL };
static const char *dmsearch[] = { "dmsearch", NULL };
static const char *showkeys[] = { "showkeys", NULL };
static const char *logout[] = { "arcolinux-logout", NULL };
static const char *emacscmd[] = { "emacsclient", "-c", "-a", "'emacs'", NULL };
static const char *vboxcmd[] = { "virtualbox", NULL };

#include "selfrestart.c"
#include "shiftview.c"


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = dmsearch } },
	{ MODKEY|ShiftMask,             XK_f, 	   spawn,          {.v = filecmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_h,      spawn,          {.v = showkeys } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = logout } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = emacscmd } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = vboxcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,		XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,			XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_r,      self_restart,   {0} },
	{ Mod1Mask|ControlMask,         XK_Right,  shiftview,      {.i =  1 } },
	{ Mod1Mask|ControlMask,         XK_Left,   shiftview,      {.i = -1 } },
	{ Mod1Mask|ControlMask,         XK_Up,     shiftview,      {.i =  1 } },
	{ Mod1Mask|ControlMask,         XK_Down,   shiftview,      {.i = -1 } },	
	{ Mod1Mask,						XK_Tab,    shiftview,      {.i =  1 } },
	{ Mod1Mask|ShiftMask,	        XK_Tab,	   shiftview,	   {.i = -1 } },
	{ MODKEY,		        		XK_Tab,    shiftview,	   {.i =  1 } },
	{ MODKEY|ShiftMask,		        XK_Tab,	   shiftview,	   {.i = -1 } },
	{ MODKEY,            			XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            			XK_x,	   togglescratch,  {.ui = 2 } },
	{ MODKEY,            			XK_c,	   togglescratch,  {.ui = 3 } },
	{ MODKEY,            			XK_v,	   togglescratch,  {.ui = 4 } },
	{ MODKEY,            			XK_o,	   togglescratch,  {.ui = 5 } },


	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = taskmanager } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = filecmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = calendar } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
