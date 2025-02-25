; This script runs StarryFiles++ on Win+E.
; The StarryFiles++ executable must be in the same directory as this script file.

#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
#SingleInstance force ; Only one copy of this script should run at a time.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

; preserve maximized window state
PreserveMaximizedState := false 

#e::

if PreserveMaximizedState AND WinExist("ahk_exe starryfiles++.exe")
  WinActivate
else
  Run()
return

Run()
{
  try {
      Run %A_ScriptDir%\StarryFiles++.exe
  } catch e {
      MsgBox Couldn't run StarryFiles++.`nPlease make sure it's in the same directory as this script (%A_ScriptDir%).
  }
}
