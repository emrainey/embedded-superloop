# Jarnax

![A bare metal firmware superloop](baremetal_firmware_superloop.jpg)

A Super-loop embedded system re-imagined in, at _least_, C++14 and _only_ in C++, on the Cortex M4 architecture. Some minor assembly is unavoidable due to the architecture but C++ standards are still followed with assembly usage.

## Purpose

To write a safety oriented Cortex-M bare-metal system in C++14 or later, with no `C` baggage. This means:

* No `C` casts when casting is needed.
* No `#defines`, including macros. Instead replaced with `inline`d code, `using`s and other C++-isms.
* No `CMSIS`. The Cortex System Structures are all defined locally as C++ bit-fields with the proper types _built in_ mainly using inspiration from the [peripheralyzer](https://github.com/emrainey/peripheralyzer) project.

This bare-metal firmware also does not permit several C++ features in order to reduce failure modes:

* No C++ exceptions.
* No C++ RTTI (Run Time Type Information)
* No `dynamic_cast`, use as few `reinterpret_cast` as possible, favoring to get types correct first.
* No dynamic memory allocation.

Using the STL or libc with these features turned off is challenging and leads to hard-to-meet expectations about which structures or templates or related features will work.

Which common types won't work usually comes down to objects which are resizable at runtime or so heavily depend on exceptions that you practically have to reinvent them to have a usable API.

* `std::vector` - resizeable at runtime and uses exceptions to communicate failures (even when a simple bool would have worked).
* `std::bind` - sometimes allocates, sometimes doesn't, it's roulette!
* `std::string` - also sometime an allocation roulette!

In order to fill the _need_ that the _STL_ or other template libraries provide, this project seeks to implement a bare-minimum number of templates to function.

* `Span`
* `Array`
* `Ring`
* `Stack`
* `Container`
* `Pool`

Additionally the design of the firmware is generally

* A single thread of execution.
* A bare minimum number of interrupts are enabled.
* Asynchronous and non-blocking functions in all interfaces
* Client facing applications use Pure Virtual Interfaces to communicate interface and expectations.
* When the need for the complexity arrives, StateCharts or State Machines are employed to control the state of some internal hardware or external chip or some gestalt thereof.
* A single `while(true)` loop is permitted, in `main`

## Documentation

* <https://www.st.com/en/microcontrollers-microprocessors/stm32f407ve.html>
* <https://wiki.segger.com/J-Link_GDB_Server>

## Links

* <https://interrupt.memfault.com/blog/arm-cortex-m-exceptions-and-nvic#exception-entry--exit>
* <https://www.eng.auburn.edu/~nelson/courses/elec5260_6260/slides/ARM%20STM32F476%20Interrupts.pdf>
* <https://microcontrollerslab.com/nested-vectored-interrupt-controller-nvic-arm-cortex-m/>
* <https://interrupt.memfault.com/blog/arm-cortex-m-exceptions-and-nvic>
* <https://mcuoneclipse.com/2016/10/17/tutorial-using-single-wire-output-swo-with-arm-cortex-m-and-eclipse/>
* <https://maskray.me/blog/2021-11-07-init-ctors-init-array>

## Renode

Renode is a (not nearly complete enough) emulation of the Cortex M series and it has a _board_ emulation of the Segger TRB (STM32F407VE). Typically this is used by other system to emulate for testing purposes. Renode's emulation is missing some features like ITM/TPIU and SWO and Ticks and a bunch of other stuff.

* <https://interrupt.memfault.com/blog/intro-to-renode>
* <https://zephyr-dashboard.renode.io/renodepedia/boards/segger_trb_stm32f407/?view=hardware&demo=Hello_World>

## Building

Visual Studio Code should be able to run this and identify the presets configuration. However you can also use the command line.

```bash
# After installing arm-none-eabi-gcc via mac pkg
$ export PATH=$PATH:/Application/ARM/bin
$ cmake --list-presets
Available configure presets:

  "stm32-gcc-arm-none-eabi-10" - GCC ARM None EABI 10 for STM32
  "stm32-gcc-arm-none-eabi-11" - GCC ARM None EABI 11 for STM32
  "stm32-gcc-arm-none-eabi-12" - GCC ARM None EABI 12 for STM32
  "stm32-gcc-arm-none-eabi-13" - GCC ARM None EABI 13 for STM32
  "native-gcc-11"              - Homebrew GCC 11
  "native-gcc-12"              - Homebrew GCC 12
  "native-gcc-13"              - Homebrew GCC 13
  "native-llvm-17"             - LLVM 17.0.0
  "native-clang"               - Native Clang Toolchain
$ cmake --preset stm32-gcc-arm-none-eabi-13 -B build/stm32-gcc-arm-none-eabi-13 -S .
$ cmake --build build/stm32-gcc-arm-none-eabi-13
```

## Debug

```bash
# in one window
./scripts/debug.sh renode
# or if yu have a JLink
./scripts/debug.sh server

# in another terminal
# modify ./scripts/stm32f407ve.gdb for commands as needed
./scripts/debug.sh client
```

## Modules

Components are layedout into modules which are independent and require build support to interwork. This is done to prevent accidental inclusion in single `include/` folder systems for all components. After a dependency is formed in the build system, the appropriate include paths, defines, sources, etc. will be provided.

```text
modules/
  jarnax/
  core/
  cortex/
  stm32/
```

### System

System Components and interfaces live in the system library and namespace. Generally it's header files and interfaces live in `include/system` and are used by Applications. System source is built in the `libs/jarnax/source/`

Layout:

* `libs/`
  * `jarnax/`
    * `include/system` - only path to `include` is made a dependency
    * `source/*.cpp`

## Driver Model

Chip specific drivers live in the chip specific namespace like `stm32`. These internal driver headers will also be in an `include/stm32` subfolder.

* `platform/`
  * `stm32/`
    * `include/stm32` - only path to `include` is made a dependency
    * `source/*.cpp`

## Things To Do

```
[ ] Pick a better name than _jarnax_ (first word that popped into my mind)
  [x] bare-metal firmware = bmf
  [ ] bare-metal firmware super loop - bmfsl
[x] Modern CMake INTERFACE libraries
[x] Encapsulate Firmware Build in a CMake Function
[x] Separate Cortex flags from Strict flags from Firmware options in CMake.
[x] Group System things in `system`
[x] Group THUMB specialty instructions in `always_inline` C++ header and `thumb::` namespace
[x] Group Cortex related code into `cortex::` namespace
[x] Group Core C++ Template Classes into `core::` namespace
[x] Organize headers better (<name>/<namespace>.hpp cascade includes whole namespace)
[x] Separate most functions into separate .cpp files
[x] Write `reset_entry` into C++ code
[x] Write vector table entries
[x] Write basic linker script w/ backup ram for fun
[x] Add basic Cortex M series headers.
[x] Zero Initialize BSS
[x] Load from ReadOnly Flash section into Globals
[x] Verify Global Data Values (like clock_frequency)
[x] Generate Linker Map w/ Cross Reference (in CMake)
[x] Generate Disassembly of Firmware (in build.sh)
[x] Call the __preinit_array and__init_array functions which GCC adds
[x] Make all headers .hpp
[x] Verify that a constructor was called. <- Requires a complex constructible object
[x] Implement `memset` to appease GCC during `-O1` w/ `-nostdlib`
[x] Implement a cortex register based external reset request and test it.
[x] Implement `Span`
[x] Implement `Array`
[x] Implement `Ring`
[x] Implement `Stack`
[ ] Implement `List` (what am I counting here as a List?)
[x] Implement 'Split' - for a variable bit split (upper/lower)
[ ] Implement Iterators in Span/Array/Ring/Stack/List
[ ] Implement Unit Test for Span in an Application
[ ] Implement Unit Test for Array in an Application
[ ] Implement Unit Test for Ring in an Application
[ ] Implement Unit Test for Stack in an Application
[ ] Implement Unit Test for List in an Application
[ ] Implement Unit Test for Split in an Application
[x] Replace for() loops with `for(auto .:..)`
[x] Complete generic boot sequence (up to enabling interrupts)
[x] Enable MPU w/ simple mapping from linker (duplicated? or pulled from linker script itself?)
[ ] Split Vendor MPU Settings from System MPU settings (call vendor from system)
[ ] Enable SWO/ITM/TPIU (mostly)
[ ] Capture SWO output
[x] Enable VSCode launch.json for debugging
[x] Move the "configure.hpp" to each app so they can configure the firmware build.
[x] Make all Register volatile and placed by the linkerscript at the right addresses, no #defines or casts needed.
[x] Add System Tick float unit (1/128th or 1/256th or more, not less) to configuration.
[ ] Enable System Tick - but do not use a power of 10 base, use a power of 2 base. Time can be more easily represented in powers of 2 in floats.  1/128 (0.0078125 or ~8ms) or 1/256 (0.00390625 or ~4ms).system configuration issue.
[ ] Implement Unit Test for System Tick in an Application
[x] Enabled choosing MSP or PSP at boot along with other Cortex M modes.
[x] Write up the Interrupt Structures from Cortex Manual
[ ] Self Test at Boot which triggers and captures all Interrupt Modes before going to main. In BootSelfTest mode, the handler will return correctly to exterior code.
[ ] Implement Data Cache and Instruction Cache operations (for real)
[ ] Replace all Fault Register Definitions from CMSIS
[x] Capture a Non Maskable Interrupt in Ozone
[ ] Process the NMI as what? yield?
[ ] Capture a Hard Fault in Ozone
[ ] Process a Hard Fault (if Bist, return, else?)
[ ] Capture a Memory Management Fault in Ozone
[ ] Process a Memory Management Fault (if Bist, return, else?)
[ ] Capture a Usage Fault in Ozone
[ ] Process a Usage Fault (if Bist, return, else?)
[x] Capture a SVC Call in Ozone
[x] Trigger SVC Call (w/ parameters?)
[x] Return a value back from SVC
[ ] Write compact handler entry/exit in assembler? `asm()` version leaks registers here and there.
[ ] Capture a PendSV Call
[ ] Capture an External Fault -> requires a different board? Renode?
[x] Setup the Privilege vs. User mode function (sets MSP/PSP then jump)
[x] Implement running in User mode vs. Privileged mode via `jarnax::run_in_privileged_mode_only`
[ ] Implement a STM32F407VE SPI Driver
[ ] Implement a LSM9DS1 IMU Driver
[x] Add a .clang_format
[x] Add a .clang-tidy
[x] Add doxygen everywhere
[x] Generate doxygen in CMake
[x] Learn how to run in Renode in a Container
[x] Run in Renode (takes forever to start)
[x] Create VSCode cmake variant fileb
[ ] Generate Coverage in Renode
[ ] Determinstic builds (ld GUID removal, no __FILE__)
[x] Add disassembly target to build.
[ ] Verify all System Linker Register addresses in an On Target Unit Test
```
