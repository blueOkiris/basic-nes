# 6502 Programmign Reference Guide (for C)

## C 6502 Tips:

In order to get the most out of 6502 C:

 - Avoid local variables as much as possible, make them static at least

 - Avoid passing parameters to functions

 - Avoid to use functions that only used once

 - Use __fastcall__ calling convention

 - Arrays of structs are slow, separate arrays are faster

 - Fastest type is unsigned char, use it as much as possible. Don't forget that in CC65 int is 16 bit wide

 - Signed types are slower

 - You can put some variables into zero page using a pragma (see below), it makes them faster

 - Don't forget that you need to declare array of pointers as const type* const if you need to put it into ROM

 - Use preincrements where possible, they are both faster and shorter

 - Avoid to use multiple and division as much as possible, they are very slow. Use bit shifts where possible instead

 - If you need to process an array of objects, it is better to copy data from arrays to separate vars. Use these vars in the code, and then copy new data back to the arrays. This could make code significally shorter and faster, because access to an array item generates more code than access to a variable

 - Declaring global variables as static also helps to find unused global variables, compiler will report about them

 - use unsigned char for most variables

 - use ++g instead of g++

 - array max of 256 bytes
 

## CPU Memory Map

| Memory        | Description                   |
|:-------------:|:-----------------------------:|
| $0000-07FF    | Internal RAM                  |
| $0800-1FFF    | Mirrors of Above              |
| $2000-2007    | PPU Registers                 |
| $2008-3FFF    | Mirrors of Abvoce             |
| $4000-4017    | APU Register / Controllers    |
| $4018-5FFF    | Nothing useful                |
| $6000-7FFF    | Extra RAM if on cartridge     |
| $8000-FFFF    | ROM, on cartridge             |
| $FFFA-FFFB    | NMI vector                    |
| $FFFC-FFFD    | Reset vector                  |
| $FFFE-FFFF    | IRQ/BRK vector                |

## PPU Memory Map

| Memory        | Description                   |
|:-------------:|:-----------------------------:|
| $0000-0FFF    | Tileset 0                     |
| $1000-1FFF    | Tileset 1                     |
| $2000-23FF    | Nametable 0                   |
| $2400-27FF    | Nametable 1                   |
| $2800-2BFF    | Nametable 2                   |
| $2C00-2FFF    | Nametable 3                   |
| $3000-$3EFF   | Mirror of 2000 - 2EFF         |
| $3F00-3F1F    | Color Palette                 |
| $3F20-3FFF    | Mirrors of palette            |

 * Also another 256 bytes dedicated to sprites which is written every frame
