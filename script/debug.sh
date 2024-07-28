#!/bin/bash

"C:/Program Files/SEGGER/JLink/JLinkGDBServerCL.exe" -singlerun -nogui -if swd -port 50000 -swoport 50001 -telnetport 50002 -device -at32f421g8u7 &
sleep 1
echo '
target remote 127.0.0.1:50000
' > build/gdb.cmd
$1 'build/at32f421.elf' --command build/gdb.cmd
