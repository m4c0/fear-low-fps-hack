# FEAR low FPS hack

Fixes the cause of low FPS in the Fear game when playing in modern computers.

## The problem

In modern computers, FEAR slows down after a while due to an incompatibility
with modern HID devices. The game engine assumes two types of devices: gamepads
and "others". Years ago, that works because "other" could only be mouses and
keyboards. Nowadays, your Windows will have much more than those three devices.

Unfortunately, FEAR bogus out when dealing with unknown devices. For every
unrecognized device, it tries to reset it and try again. This "reset" is done
per device many times per second.

The "reset" seems to have some form of leak, which accumulates over time and
causes the slowdown in the game.

## The solution

This hack works by replacing DirectInput with a hook DLL. This DLL, when placed
in the same folder as the game's EXE, it will be loaded before the real DLL.
That hook DLL will call out the real DLL as needed.

Then, whenever FEAR tries to enumerate "other" devices, our hook will intercept
it and ask DirectInput to enumerate only mouses and keyboards. This avoids any
issues with devices unsupported by the game, while keeping the behaviour similar
to how it worked years ago.

## How to use the hack

1. Download the project
2. Open in Visual Studio
3. Build it
4. Open the "Debug" folder inside the project directory
5. Copy the generated `dinput8.dll` file to the same folder as the EXE for the
   game. **Do NOT put it inside your system folder**
   
## TODO

* Better build instructions
* Use CI to automatically create a downloadable DLL
* List similar solutions
