
DEVICE=stm32f407ve

if [[ $1 == "power" ]]; then
    JLinkExe -if SWD -device ${DEVICE} -speed 4000 -autoconnect 1 -CommandFile ./scripts/${DEVICE}.jlink -NoGui 1
elif [[ $1 == "server" ]]; then
    JLinkGDBServer -if SWD -device ${DEVICE} -speed 4000 -autoconnect 1 -NoGui 1
elif [[ $1 == "client" ]]; then
    arm-none-eabi-gdb -x ./scripts/${DEVICE}.gdb
elif [[ $1 == "renode" ]]; then
    sh /Applications/Renode.app/Contents/MacOS/macos_run.command scripts/segger_trb_stm32f407.resc
fi
