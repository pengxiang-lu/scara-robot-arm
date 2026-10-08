SET PATH=D:\Software\Keil\ARM\ARMCC\Bin;D:\Software\python\Scripts\;D:\Software\python\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files (x86)\Windows Kits\10\Windows Performance Toolkit\;D:\SOFTWARE\runtime\win64;D:\SOFTWARE\bin;C:\Program Files\dotnet\;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;C:\Users\Lenovo\AppData\Local\Programs\Python\Python311\Scripts\;C:\Users\Lenovo\AppData\Local\Programs\Python\Python311\;C:\Users\Lenovo\AppData\Local\Microsoft\WindowsApps;;C:\Users\Lenovo\AppData\Local\Programs\Microsoft VS Code\bin
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"D:\Software\Keil\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_stm32f10x_md._ia"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\core_cm3.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_stm32f10x.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\misc.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_adc.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_bkp.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_can.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_cec.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_crc.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_dac.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_dbgmcu.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_dma.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_exti.__i"
"D:\Software\Keil\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\Project.lnp"
"D:\Software\Keil\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\Project.axf" --i32combined --output ".\Objects\Project.hex"
