SET PATH=D:\Keil\ARM\ARMCC\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\system32\config\systemprofile\.dnx\bin;C:\Program Files\Microsoft DNX\Dnvm\;C:\Program Files\Microsoft SQL Server\130\Tools\Binn\;C:\Program Files (x86)\ATMEL Corporation\AT91-ISP v1.13\Library\;C:\Program Files (x86)\ATMEL Corporation\AT91-ISP v1.13\sam-ba 2.9;D:\VSCODE\Microsoft VS Code\bin;D:\Mingw\bin;C:\Program Files (x86)\SSH Communications Security\SSH Secure Shell
SET CPU_TYPE=LPC1778
SET CPU_VENDOR=NXP
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via "..\output\main.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmAsm" --Via "..\output\startup_lpc17xx._ia"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via "..\output\core_cm3.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via "..\output\system_lpc177x_8x.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via "..\output\lpc177x_8x_clkpwr.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via "..\output\lpc177x_8x_gpio.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via "..\output\lpc177x_8x_systick.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via "..\output\lpc177x_8x_uart.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmCC" --Via "..\output\uart0.__i"
"D:\Keil\ARM\ARMCC\Bin\ArmLink" --Via "..\Output\myostest.lnp"
"D:\Keil\ARM\ARMCC\Bin\fromelf.exe" "..\Output\myostest.axf" --i32combined --output "..\Output\myostest.hex"
