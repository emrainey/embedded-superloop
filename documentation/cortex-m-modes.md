# Processor Modes

There are several "dimensions" to the Mode discussion.

* Privilege - Determines access in the MPU to protected regions of memory and to specific (co)processor instructions.
* Stack - Stores data and frames on one of two stacks Main (stored in `MSP`) and Process (stored in `PSP`)
* Execution - Code can be executed in either Handler (via any handler) or Thread (normal)

In this mix several concepts together with some disjointed parlance but the core notion is that when you are in the elevated Mode you'll be executing a `handler` which will be `privileged`, with it's context on `main` stack.

When you are in the non-elevated mode, you'll be in some `Thread` of execution, which will be `non-privileged` with it's context on the `process` stack.

When you call an `svc #IMM` in `Thread` mode, the processor will save it's state on the `Process` Stack and then swap to the `Main` stack and run a `handler` in `privileged` mode.
