# Bomberman_SDL2
A bomberman game created by use of the help from SDL2 tutorials from 
https://www.youtube.com/user/creaper
and
https://lazyfoo.net/tutorials/SDL/

![Alt text](https://i.gyazo.com/a51902f6d46fa68a04815df9fa0dd1c3.png?raw=true "Title")

# SDL2 library (.lib and .h) (SDL2 Img, SDL2 TTF, all in one) can be found here
[sdl2.zip](https://github.com/boiledsauce/Bomberman_SDL2/files/6954875/sdl2.zip)

# Install (Visual studio 2019 community edition):
1. Download the SDL2 library, place it somewhere.

2. Replace my values in the CMakeLists.txt to yours here;
 
 set(SDL2_INCLUDE_DIR YOUR_SDL2_INCLUDE_PATH_HERE/include)
 
 set(SDL2_LIB_DIR YOUR_SDL2_LIBS_PATH_HERE/lib/x86)
  
3. Create a new empty c++ project in Visual Studio. Use 32 bit (x86) MSVC Compiler for it.

4. File -> Open CMAKE -> Select the CMakeList.txt

5. Download these .dll files [necessary_dlls.zip](https://github.com/boiledsauce/Bomberman_SDL2/files/6961923/necessary_dlls.zip)

6. Place them in the build directory Visual Studio created for you (for me: bomberman\out\build\x86-Debug)

7. Download the sprites (graphics) from [Sprites.zip](https://github.com/boiledsauce/Bomberman_SDL2/files/6961941/Sprites.zip)
   Unpack and place the folder in the same directory as the build directory. 



https://user-images.githubusercontent.com/85931509/128648481-1c04fd08-d900-47e3-98f1-3bc7d1d6e7ab.mp4
