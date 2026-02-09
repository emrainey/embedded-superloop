# Processor Modes

Cortex-M uses three independent axes of "modes" that often get conflated:

* Privilege: access permissions for MPU regions and privileged system instructions.
* Stack: which stack pointer is active for exception entry/return.
* Execution: Thread mode (normal code) vs Handler mode (exceptions/interrupts).

These axes combine to define what is possible at any time.

| Execution | Privilege | Stack pointer | What is possible |
| --- | --- | --- | --- |
| Thread | Privileged or Unprivileged | PSP or MSP (configurable) | Normal code; unprivileged thread cannot access protected regions or privileged instructions. |
| Handler | Always Privileged | MSP (fixed) | Exception/ISR code with full privileged access. |

Key rules:

* Handler mode is always privileged and always uses the Main stack.
* Thread mode can be privileged or unprivileged and can use either stack pointer.
* Unprivileged thread code cannot switch to privileged; it must request service via exceptions.

Typical flow:

* Thread mode executes application code, often unprivileged on the Process stack.
* An exception (IRQ, fault, or `svc #imm`) causes hardware to push the Thread context to the current stack, switch to the Main stack, and enter Handler mode as privileged.
* Returning from the exception restores the prior Thread mode privilege and stack selection.

Reset vector:

* On reset, the core loads the initial MSP from the vector table at address 0x00000000 and then loads the Reset handler address from 0x00000004.
* The Reset handler runs in Handler mode, privileged, using the Main stack.
* Reset can be triggered by power-on reset, external reset pin, watchdog reset, software system reset (e.g., `SCB->AIRCR`), or brown-out conditions (device dependent).
