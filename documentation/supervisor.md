## System / User Call System over SVC

### What is it?

An instruction used to enter the privileged supervisor handler in the cortex-m vector table. If the main stack is enabled, it will use that.

```asm
svc #IMM
```

* In thumb mode, `svc` instructions have an 8 bit `IMM` value, take `R0, R1, R2, R3` and return a value in `R0`.
* The immediate value is limited to `0` to `255`. This is not given to the function, it has to be extracted from the _instruction stream itself_ using some indirection.

### How could/should it be used?

* `IMM` - This could be the enumerated value of the "command" or some other indicator of calling convention.
* The Registers are 32 bit values, but can be any 32 bit value (pointer, float, uint32_t, etc)
* Returned values should not be pointers or references back to supervisor memory (which will be protected). Access to protected memory will fault.
* Returned values should be system codes (if they can fit in a single uint32_t)

### Usecases

* Core System Library Calls like `disable interrupts`, `flush data cache`, etc. No parameters, can't fail and don't return a status. Some don't even return (`reset`)
* Core System Library Calls that take some parameters (`invalid address X`). Can't fail, but need some simple parameter.
* Non-privileged code calls privileged code with a given (internal C++) interface. Objects become "split" across the system. A thin shim exists in non-privileged space to setup the `supervisor<X>(...)` call which is received by the other side of the split in privileged side which reassembles the call into some other C++ interface.
  * Special Objects (Timers, Watchdog, etc), Drivers, Services and other concepts could be split like this.

### Option 1

All `IMM` are just enumeration of commands. Parameters are ad-hoc. Returns are simple Status codes.

`auto ret = foo(x, y, z, w);` becomes `auto ret = supervisor<FOO>(x, y, z, w);`, internally a switch cases handles `case FOO:` which knows to how reinterpret `arg0-arg3`. Things are added manually.

#### Pros

* Simple-ish

#### Cons

* Poor object oriented abstraction, hard to mock.
* Lots of duplicated code.

### Option 2

All `IMM` indicate which type of C++ interface they are using. The System maintains a list of known SVC interfaces. The conventions for each interface are well defined.

* `System`
  * arg0 is sub enum class for `System::Call`
    * `reset`
    * `halt` (spin forever)
    * `idle` (spin a period or use idle instruction if exists)
    * `sleep` (and other low power modes)
    * `yield` ?
    * `interrupt` ops (enable all, disable all, enable single, enable single, assign priority, test NMI etc)
    * `data cache` ops (invalidate, flush, etc)
    * `instruction cache` ops (???)
  * arg1, arg2, arg3 - optional?
  * void return
* `Ticks` or `Timers` Object (1 or more)
* `Watchdog` Object (1 or more)
* `Console` Object (singleton?)
  * choose destination?
  * set print mask (output types, `RTT`, `SWO`, `Semihosting`, `UART`, etc)
* Abstract `Driver/Service`
  * arg0 is the instance handle? enum?
  * arg1 is the call enum (per class type?)
    * Common - `Emplace`, `Dismiss`
  * arg2 is the pointer to a input structure?
  * arg3 is the pointer to a output structure?
  * returns Status code

#### Pros

* Relatively simple
* Extensible

#### Cons

* Some repeated code over each different interface type

### Option 3

All `IMM` are encoded to describe the calling convention:

* Has parameters or not (1 bit)
* Number of parameters 1, 2, 3, 4 (2 bits)
* Return is void or not (1 bit)
* 4 bits left - encodes 16 different types of parameter passing?
  * Known system interface calls from option 2

## System Interface (mockable)

```c++
/// For calls which have severe side effects!
class uSystem {
virtual void reset(void);
virtual void halt(void);
enum class Code {...};
virtual void abort(Code); //? what does this do exactly?
virtual void idle(time::duration); // still handles interrupts
virtual void sleep(time::duration); // does not handle interrups
virtual bool bist(void); // Boot Up Self Test
virtual size_t ticks(void); // returns number of ticks
};

// -=====initialized======-
System& system = GetSystem();
// -=====used======-
auto ticks = system.ticks();

```
