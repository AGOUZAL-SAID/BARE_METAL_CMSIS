target ext :2331
mon endian little
mon halt

# interface with asm, regs and cmd windows
define split
  layout split
  layout asm
  layout regs
  focus cmd
end

# interface with C source, regs and cmd windows
define ss
  layout split
  layout src
  layout regs
  focus cmd
end

define flash
  dont-repeat
  mon reset
  load
end

# Useful function when the processor is in hardfault to see
# where it comes from.
define armex
  printf "EXEC_RETURN (LR):\n",
  info registers $lr
    if ($lr & 0x4)
      printf "Uses MSP 0x%x return.\n", $MSP
      set $armex_base = $MSP
    else
      printf "Uses PSP 0x%x return.\n", $PSP
      set $armex_base = $PSP
    end

    printf "xPSR            0x%x\n", *($armex_base+28)
    printf "ReturnAddress   0x%x\n", *($armex_base+24)
    printf "LR (R14)        0x%x\n", *($armex_base+20)
    printf "R12             0x%x\n", *($armex_base+16)
    printf "R3              0x%x\n", *($armex_base+12)
    printf "R2              0x%x\n", *($armex_base+8)
    printf "R1              0x%x\n", *($armex_base+4)
    printf "R0              0x%x\n", *($armex_base)
    printf "Return instruction:\n"
    x/i *($armex_base+24)
    printf "LR instruction:\n"
    x/i *($armex_base+20)
end

document armex
ARMv7 Exception entry behavior.
xPSR, ReturnAddress, LR (R14), R12, R3, R2, R1, and R0
end
