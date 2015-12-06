#Windows Console
**Windows Console** provides Object Oriented wrapper around Window's console.

#Usage 

```cpp
#include "WindowsConsole.h"

using namespace WindowConsole;

int main() {

	// create
	WindowsConsole *console = new WindowsConsole();
	console->Create();
	
	// set title
	console->SetCaption(L"My console");
	
	// write on screen
	console->Writeln(L"Hello world");

	// wait for ESC key
	while(console->ReadKey() != 27) {  }

	// clean up
	console->Destroy();
	delete console;

	return 0;
}

```

#Available functions

## Create
Creates and sets up console. If you created console application project, then WindowsConsole object takes control over the existing console and releases control when you call `Destroy()` method. If you created windows application project, then WindowsConsole object creates new console and destroy it when you call `Destroy()` method.

```cpp
WindowsConsole *console = new WindowsConsole();
console->Create();
```

## Destroy
Destroys console's object and cleans up. If you created console application project, then WindowsConsole object takes control over the existing console and releases control when you call `Destroy()` method.If you created windows application project, then WindowsConsole object creates new console and destroy it when you call `Destroy()` method.

```cpp
WindowsConsole *console = new WindowsConsole();
console->Create();

// ....

console->Destroy();
delete console;
```

##Write
Write text on the console screen.

Method starts writing at the last cursor position and leaves cursor at the position right behind the last character of the displated text.

```cpp
console->Write(L"Hello world");
```

You can also specify color of the output text:

```cpp
console->Write(L"Hello world", ConsoleColor::Red);
```
As well as background color of the output text:

```cpp
console->Write(L"Hello world", ConsoleColor::Red, ConsoleColor::White);
```

##Writeln
Write text on the console screen and move cursor to new line.

Method starts writing at the last cursor position and move cursor to new line.

```cpp
console->Writeln(L"Hello world");
console->Writeln(L"Hello world", ConsoleColor::Red);
console->Writeln(L"Hello world", ConsoleColor::Red, ConsoleColor::White);
```

##Read
Reads characters from console input and save them in `outBuffer`.

Number of characters read from input must be smaller than *input buffer size*. You can get *input buffer size* using `GetInputBufferSize()` and set it with `SetInputBufferSize()`.

```cpp
std::wstring outBuffer;
console->Read(outBuffer);
```

You can also specify color of the input text:

```cpp
std::wstring outBuffer;
console->Read(outBuffer, ConsoleColor::Red);
```
As well as background color of the input text:

```cpp
std::wstring outBuffer;
console->Read(outBuffer, ConsoleColor::Red, ConsoleColor::White);
```

##ReadKey
Returns code of the key that is down.

```cpp
	// wait for ESC key
	while(console->ReadKey() != 27) {  }
```

##Clear
Clears console buffer.

If color is passed as argument, then a new backgorund color is set - it works like `SetBackgorunColor()`.

```cpp
console->Clear()
console->Clear(ConsoleColor::Red)
```

##Clearln
Clears line where the cursor is.

```cpp
console->Clearln()
```

## SetCaption
Sets new title. It is displayed in title bar of console window.

```cpp
console->SetCaption(L"My title");
```

## GetCaption
Returns title of the current console window. 

```cpp
std::wstring = console->GetCaption();
```

## GotoXY
Moves cursor to fixed position.

The X and Y coordinates are zero based. Position {X = 0, Y = 0} is in upper-left corner of the window.

```cpp
console->GotoXY(64, 32);
```

## HideCursor
Hides cursor.

```cpp
console->HideCursor();
```

## ShowCursor
Shows cursor.

```cpp
console->ShowCursor();
```

## SetCursorSize
Sets cursor's size. 

The cursor's size should be between 0 and 100. If it is greater than 100, size of the cursor will be cut to 100.

```cpp
console->SetCursorSize(24);
```

## GetCursorSize
Returns size of the cursor. Returned size is in [0, 100].

```cpp
char cursorSize = console->GetCursorSize();
```

##HideConsoleWindow
Hide console window.

```cpp
console->HideConsoleWindow();
```

##ShowConsoleWindow 
Shows console window on the screen.

```cpp
console->ShowConsoleWindow();
```

##SetBackgroudColor
Sets new background color of the console.

```cpp
console->SetBackgroudColor(ConsoleColor::Red);
```
##SetInputColor
Sets new color of the input font.

```cpp
console->SetInputColor(ConsoleColor::Yellow);
```

##SetOutputColor
Sets new color of the output font.

```cpp
console->SetOutputColor(ConsoleColor::White);
```

##GetBackgroudColor
Returns color of the backround.

```cpp
ConsoleColor backgroundColor = console->GetBackgroudColor();
```

##GetInputColor
Returns color of the input font.

```cpp
ConsoleColor inputColor = console->GetInputColor();
```

##GetOutputColor
Returns color of the output font.

```cpp
ConsoleColor outputColor = console->GetOutputColor();
```

##SetWindowSize
Resizes console window.

Size of the console window is limited and depends of user's screen resolution. You can resize window to specific size returned by `GetLargestWindowSize()`. If you try to create window that is too large, method will do nothing and return false.

```cpp
console->SetWindowSize(128, 64);
```

##GetWindowSize
Returns console window size.

```cpp
COORD size = console->GetWindowSize();
```

##GetLargestWindowSize
Returns largest avalible console window size.

```cpp
COORD largestSize = console->GetLargestWindowSize();
```


## SetBufferSize
Resizes console buffer.

Sometimes `SetBufferSize()` will also resize console window. This is necesary to resize buffer. For example, that happens when you create buffer smaller than window.

```cpp
console->SetBufferSize(128, 64);
```

## GetBufferSize
Returns console buffer size.

```cpp
COORD size = console->GetBufferSize();
```

##SetInputBufferSize
Set the input buffer size. This is number of characters that console will be able to read from input.

```cpp
console-> SetInputBufferSize(1024);
```

##GetInputBufferSize
Returns input buffer size. This is number of character that can be read from input.

```cpp
short inputBufferSize = console->GetInputBufferSize();
```

##EnableEcho
Enables console echo.

When echo is enabled then charcters sent from input are displayed on the screen.

```cpp
console->EnableEcho();
```

##DisableEcho
Disables console echo.

When echo is disabled then charcters sent from input are **NOT** displayed on the screen.

```cpp
console->DisableEcho();
```

##GetWindowHandle
Returns handle (HWND) to console window.

```cpp
HWND handle = console->GetWindowHandle();
```

#ConsoleColor
`ConsoleColor` contains following colors:

- Black
- DarkBlue,
- DarkGreen,
- DarkAqua,
- DarkRed
- DarkPurple,
- DarkYellow,
- DarkWhite,
- Grey,
- Blue,
- Green,	
- Aqua,
- Red,
- Purple,
- Yellow,
- White,	
- None

# License

**WindowsConsole** is released under the MIT license. See LICENSE for details.