# game64 for Nintendo64

N64 game developed for the N64brew Jam #2

## Note

This ROM file has been tested to work on real Nintendo 64 hardware using the
[EverDrive-64 by krikzz](http://krikzz.com/). It should also work with
[64drive by retroactive](http://64drive.retroactive.be/).

This ROM file is only known to work on low-level, high-accuracy Nintendo 64
emulators such as [CEN64](https://cen64.com/) or [MAME](http://mamedev.org/)
due to the use of [libdragon](https://dragonminded.com/n64dev/libdragon/)
instead of the proprietary SDK used by official licensed Nintendo software.

## Building

### Using Docker

All development can be done using Docker. It's the easiest way to build the ROM on Windows and MacOS.

 * Install [Docker](https://docker.com)
 * Run `make` to produce the `game64.z64` ROM file.

 ### On linux

* Install [libdragon development toolchain](https://github.com/DragonMinded/libdragon)
* Run `make sblobber.z64` to produce the `game64.z64` ROM file.

## Testing

* Download / compile / install [CEN64](https://cen64.com/).
* Set the `CEN64_DIR` env var to the cen64 folder.
* Run `make cen64`.

## Thanks

* Thanks to [Kenney](https://www.kenney.nl) for the art used in the game.
* Thanks to [Jennifer Taylor](https://github.com/DragonMinded) for libdragon.
