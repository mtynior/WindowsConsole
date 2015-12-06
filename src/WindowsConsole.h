//======================================================================================================
//
//	File:		WindowsConsole.h
//	Created:	Sunday, 14 March 2010 17:07:52
//
//	Copyright (c) 2010 Michal Tynior. All Rights Reserved.
//
//------------------------------------------------------------------------------------------------------
//
//	Windows console wrapper.
//	
//======================================================================================================

#ifndef __WINDOWSCONSOLE_H__
#define __WINDOWSCONSOLE_H__
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>

namespace WindowConsole
{
	enum ConsoleColor
	{
		Black = 0,
		DarkBlue = FOREGROUND_BLUE,
		DarkGreen = FOREGROUND_GREEN,
		DarkAqua = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DarkRed = FOREGROUND_RED,
		DarkPurple = FOREGROUND_BLUE | FOREGROUND_RED,
		DarkYellow = FOREGROUND_GREEN | FOREGROUND_RED,
		DarkWhite = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Grey = FOREGROUND_INTENSITY,
		Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,	
		Aqua = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
		Purple = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY,
		Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,	
		None = -1
	}; 

	class WindowsConsole
	{
	public:

		/// <summary>
		/// Constructor. Sets default values for member variables. 
		/// </summary>
		WindowsConsole();

	
		/// <summary>
		/// Destructor. Destroys object and cleans up. 
		/// </summary>
		~WindowsConsole();


		/// <summary>
		/// Creates and sets up console. 
		/// </summary>
		/// <remarks>
		///	If you created console application project then WindowsConsole object takes control over the
		///	existing console and releases control when you call Destroy() method.
		///	If you created windows application project then WindowsConsole object creates new console 
		///	and destroy it when you call Destroy() method.
		///</remarks>
		void Create();

	
		/// <summary>
		/// Destroys console's object and cleans up. 
		/// </summary>
		/// <remarks>
		///	If you created console application project then WindowsConsole object takes control over the
		///	existing console and releases control when you call Destroy() method.
		///	If you created windows application project then WindowsConsole object creates new console 
		///	and destroy it when you call Destroy() method.
		///</remarks>
		void Destroy();


		/// <summary>
		/// Sets new title. It is displayed in title bar of console window.
		/// </summary>
		/// <param>The tite to be displayed in title bar of console window.</param>
		/// <returns> True when succeeded, otherwise false.</returns>
		bool SetCaption(const std::wstring &inCaption);


		/// <summary>
		/// Returns title of the current console window. 
		/// </summary>
		/// <returns> The string with title of the console window.</returns> 
		std::wstring GetCaption();


		/// <summary>
		/// Moves cursor to fixed position.
		/// </summary>
		/// <param>The X coordinate.</param>
		/// <param>The Y coordinate.</param>
		/// <remarks>
		/// The X and Y coordinates are zero based. Position {X = 0, Y = 0} is in upper-left corner of the window.
		///</remarks>
		void GotoXY(const short &inX, const short &inY);


		/// <summary>
		/// Hides cursor.
		/// </summary>
		/// <returns> True when succeeded, otherwise false.</returns>
		bool HideCursor();

		/// <summary>
		/// Shows cursor.
		/// </summary>
		/// <returns> True when succeeded, otherwise false.</returns>
		bool ShowCursor();


		/// <summary>
		/// Sets cursor's size.
		/// </summary>
		/// <param>New size of the cursor</param>
		/// <returns> True when succeeded, otherwise false.</returns>
		/// <remarks>
		/// The cursor's size should be between 0 and 100. If it is greater than 100, size of the cursor will be cut to 100.
		///</remarks>
		bool SetCursorSize(const char &inSize);


		/// <summary>
		/// Returns cursor's size.
		/// </summary>
		/// <returns>Size of the cursor. </return>
		char GetCursorSize();

	
		/// <summary>
		/// Returns handle to console window.
		/// </summary>
		/// <returns>Handle to console window.</return>
		HWND GetWindowHandle();


		/// <summary>
		/// Shows console window on the screen..
		/// </summary>
		/// <returns> True when succeeded, otherwise false.</returns>
		bool ShowConsoleWindow();


		/// <summary>
		/// Hide console window.
		/// </summary>
		/// <returns> True when succeeded, otherwise false.</returns>
		bool HideConsoleWindow();

		/// <summary>
		/// Resizes console window.
		/// </summary>
		/// <param>New width of the console window in number of characters.</param>
		/// <param>New height of the console window in number of characters.</param>
		/// <returns>True when succeeded, otherwise false.</returns>
		/// <remarks>
		/// Size of the console window is limited and depends of user's screen resolution. You can 
		///	resize window to specific size returned by GetlargestWindowSize(). If you  try to create
		///	to big window method will not work and return false. 
		///</remarks>
		bool SetWindowsSize(const short &inWidth, const short &inHeight);


		/// <summary>
		/// Returns console window size.
		/// </summary>
		/// <returns>Struct that contains width and height of the console window.</returns>
		/// <remarks>
		/// Returned value is specified in number of characters.
		///</remarks>
		COORD GetWindowSize();


		/// <summary>
		/// Returns largest avalible console window size.
		/// </summary>
		/// <returns>Struct that contains largest avalible width and height of the console window.</returns>
		COORD GetLargestWindowSize();

	
		/// <summary>
		/// Sets new background color of the console.
		/// </summary>
		/// <params>New color of the backround.</params>
		void SetBackgroudColor(ConsoleColor inBackgroundColor);

	
		/// <summary>
		/// Sets new color of the input font.
		/// </summary>
		/// <params>New color of the input font.</params>
		void SetInputColor(ConsoleColor inInputColor);

	
		/// <summary>
		/// Sets new color of the output font.
		/// </summary>
		/// <params>New color of the output font.</params>
		void SetOutputColor(ConsoleColor inOutputColor);


		/// <summary>
		/// Returns color of the backround.
		/// </summary>
		/// <returns>Color of the backround.</returns>
		ConsoleColor GetBackgroudColor();

	
		/// <summary>
		/// Returns color of the input font.
		/// </summary>
		/// <returns>Color of the input font.</returns>
		ConsoleColor GetInputColor();


		/// <summary>
		/// Returns color of the output font.
		/// </summary>
		/// <returns>Color of the output font.</returns>
		ConsoleColor GetOutputColor();


		/// <summary>
		/// Write text on the console screen.
		/// </summary>
		/// <param>Text that will be displayed on the console screen.</param>
		/// <param>Input font color only for this input string. If it is ommited then defualt color (or set by SetInputColor()) will be used. </param>
		/// <param>Background color only for this input string. If it is ommited then defualt color (or set by SetInputColor()) will be used. </param>
		/// <remarks>
		/// Method starts writing at the last cursor position and leaves cursor at the position right 
		///	behind the last character of the displated wstring.
		///</remarks>
		void Write(const std::wstring &inText, ConsoleColor inOutputColor = ConsoleColor::None, ConsoleColor inBackgroundColor = ConsoleColor::None);
	

		/// <summary>
		/// Write text on the console screen and move cursor to new line.
		/// </summary>
		/// <param>Text that will be displayed on the console screen.</param>
		/// <param>Input font color only for this input string. If it is ommited then defualt color (or set by SetInputColor()) will be used. </param>
		/// <param>Background color only for this input string. If it is ommited then defualt color (or set by SetInputColor()) will be used. </param>
		/// <remarks>
		/// Method starts writing at the last cursor position and move cursor to new line.
		///</remarks>
		void Writeln(const std::wstring &inText, ConsoleColor inOutputColor = ConsoleColor::None, ConsoleColor inBackgroundColor = ConsoleColor::None);
	
	
		/// <summary>
		/// Clears console buffer.
		/// </summary>
		/// <param>The new background color of the console.</param>
		/// <remarks>
		/// If the inBackgroundColor is passed, then a new backgorund color is set. It works like SetBackgorunColor().
		///</remarks>
		void Clear(ConsoleColor inBackgroundColor = ConsoleColor::None);

	
		/// <summary>
		/// Clears line where is a cursor.
		/// </summary>
		void Clearln();


		/// <summary>
		/// Resizes console buffer.
		/// </summary>
		/// <param>New width of the console buffer in number of characters.</param>
		/// <param>New height of the console buffer in number of characters.</param>
		/// <returns>True when succeeded, otherwise false.</returns>
		/// <remarks>
		/// Sometimes `SetBufferSize()` will also resize console window. This is necesary to resize buffer.
		/// For example, that happens when you create buffer smaller than window.
		///</remarks>
		bool SetBufferSize(const short &inWidth, const short &inHeight);


		/// <summary>
		/// Returns console buffer size.
		/// </summary>
		/// <returns>Struct that contains width and height of the console buffer.</returns>
		/// <remarks>
		/// Returned value is specified in number of characters.
		///</remarks>
		COORD GetBufferSize();


		/// <summary>
		/// Reads characters from console input and save them in outBuffer.
		/// </summary>
		/// <param>Buffer that receives the characters from console input.</param>
		/// <param>Input font color only for this input string. If it is ommited then defualt color (or set by SetInputColor()) will be used. </param>
		/// <param>Background color only for this input string. If it is ommited then defualt color (or set by SetInputColor()) will be used. </param>
		/// <remarks>
		/// Number of characters read from input must be smaller than input buffer size. 
		/// You can get input buffer size using GetInputBufferSize() and set it with SetInputBufferSize().
		///</remarks>
		void Read(std::wstring &outBuffor, ConsoleColor inInputColor = ConsoleColor::None, ConsoleColor inBackgroundColor = ConsoleColor::None);


		/// <summary>
		/// Sets input buffer size.
		/// </summary>
		/// <param>Number of characters that console will be able to read from input.</param>
		void SetInputBufferSize(const short &inSize);


		/// <summary>
		/// Returns input buffer size.
		/// </summary>
		/// <returns>Number of character that can be read form input.</returns>
		short GetInputBufferSize();


		/// <summary>
		/// Returns code of the key that is down.
		/// </summary>
		/// <returns> Code of the key that is down..</returns>
		int ReadKey();


		/// <summary>
		/// Enables console echo.
		/// </summary>
		/// <remarks>
		/// When echo is enabled then charcters sent from input are displayed on the screen.
		///</remarks>
		void EnableEcho();


		/// <summary>
		/// Disables console echo.
		/// </summary>
		/// <remarks>
		/// When echo is disabled then charcters sent from input are NOT displayed on the screen.
		///</remarks>
		void DisableEcho();

	protected:
		short mWidth, mHeight, mBufferWidth, mBufferHeight;
		HANDLE mHInput, mHOutput, mHOldOutput; 
		std::wstring mCaption;
		bool mIsCursorVisible, mIsWindowVisible;
		char mCursorSize;
		ConsoleColor mInputColor, mOutputColor, mBackgroudColor; 
		wchar_t * mInputBuffer;	
		unsigned short mInputBufferSize;
		DWORD mConsoleMode;
	};

}

#endif