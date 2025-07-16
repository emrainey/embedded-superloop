# Writing A Driver for Embedded Super Loop (jarnax)

There are several locations around Embedded SuperLoop and Jarnax that need to be added before a driver will function.

## Pre-requisites List

* Check the board's chip's linker script to see if the peripheral is exposed as a symbol.
* Import the peripheral headers from peripheralyzer. Iterate on names until it makes sense and matches linkers name or vice versa.
  * Headers should go into `modules/<vendor>/include/<vendor>/registers/<Peripheral>.hpp`
* Enable Clock Tree in `<board>/source/board.cpp` in BoardContext Initialize
* Add related GPIO in `<board>/include/board.hpp` in BoardContext
* Construct related GPIO in `<board>/source/board.cpp` in BoardContext. Set the Group and Pin number here.
* Initialize related GPIO in `<board>/source/board.cpp` in BoardContext. Set the GPIO settings here.
* Add Driver instance to `<board>/include/board.cpp` in BoardContext as variable and give it an accessor method which returns a reference to it.
* Add Driver related `constexpr` in `<board>/include/board.hpp`. This would include any debug flags, DMA sizes, etc.
* Construct the Driver in `<board>/source/board.cpp` in BoardContext constructor. Pass all the input dependencies on other drivers, gpios, etc there.
* Initialize the Driver in `<board>/source/board.cpp` in BoardContext after it's dependencies have been initialized. This is where you would pass Clock speeds, bus rates, addresses, etc.
* Enable Interrupt(s) in `modules/<vendor>/source/nvic.cpp`.
* If the Driver implements a Loopable, `Enlist` in the `<application>/source/GlobalContext.cpp`

## The Driver & Tests

* Implement core Driver functionality.
  * Implement an abstract pure virtual mockable interface in `modules/jarnax/include/jarnax/<type>/Driver.hpp`
  * Declare concrete implementation in `<vendor>/include/<vendor>/XXXXDriver.hpp`
    * should inherit from `jarnax::<type>::Driver`
  * Define concrete implementation in `modules/<vendor>/source/XXXXDriver.cpp`
* Implement Driver unit test where applicable in `modules/<vendor>/tests/xxxx_driver.cpp`.
  * State Machine objects should have their own unit tests.
  * Add mocks to
* Add driver a simple integration test to demonstrate the capabilities.
  * Application should only use the `jarnax::<type>::Driver&` from the `BoardContext`.

## Documentation

It also might be useful to draw a flow chart up at [d2lang.com](https://play.d2lang.com/).

## NVIC Priorities

DMA should have very high importance to allow non-blocking and conpletion.
Bus Oriented Drivers (I2C/SPI/UART/USART, etc) should have similar NVIC importance depending on the amount of data they process and their relative platform importance.

### Example Ordering

    * DMA
    * Bus Drivers based on traffic volume, importance. For Example
        * Ethernet
        * SPI
        * CAN
        * USART
        * I2C
        * UART
