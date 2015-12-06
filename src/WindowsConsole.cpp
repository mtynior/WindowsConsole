//======================================================================================================
//
//	File:		WindowsConsole.cpp
//	Created:	Sunday, 14 March 2010 17:07:52
//
//	Copyright (c) 2010 Michal Tynior. All Rights Reserved.
//
//------------------------------------------------------------------------------------------------------
//
//	Windows console wrapper.
//	
//======================================================================================================

#include "WindowsConsole.h"

using namespace WindowConsole;

WindowsConsole::WindowsConsole(): mHInput(0), mHOutput(0), mHOldOutput(0),
	mWidth(80), mHeight(25), mBufferWidth(80), mBufferHeight(300),
	mCaption(L""), mIsCursorVisible(true), mIsWindowVisible(true), mCursorSize(25), mInputBuffer(NULL), mInputBufferSize(1024),
	mBackgroudColor(ConsoleColor::Black), mInputColor(ConsoleColor::DarkWhite), mOutputColor(ConsoleColor::DarkWhite)
{  }

WindowsConsole::~WindowsConsole()
{  }

void WindowsConsole::Create()
{
	__if_not_exists(argc)
	{
		AllocConsole();
	}
	mHInput = GetStdHandle(STD_INPUT_HANDLE);
	mHOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetBufferSize(mBufferWidth, mBufferHeight);	
	mInputBuffer = new wchar_t[mInputBufferSize];
	ZeroMemory(mInputBuffer, sizeof(mInputBuffer));	
	GetConsoleMode(mHInput, &mConsoleMode);
}

void WindowsConsole::Destroy()
{
	SetConsoleMode(mHInput, mConsoleMode);
	delete [] mInputBuffer;
	__if_not_exists(argc)
	{
		FreeConsole();
	}
}

bool WindowsConsole::SetCaption(const std::wstring &inCaption)
{
	mCaption = inCaption;
	if( !SetConsoleTitle(mCaption.c_str()) )
		return false;
	return true;
}

std::wstring WindowsConsole::GetCaption()
{
	return mCaption;
}

void WindowsConsole::GotoXY(const short &inX, const short &inY)
{
	COORD position = {inX, inY};
	SetConsoleCursorPosition(mHOutput, position);
}

bool WindowsConsole::HideCursor()
{
	if( mIsCursorVisible )
	{
		CONSOLE_CURSOR_INFO info;

		info.dwSize = mCursorSize;
		info.bVisible = false;
		mIsCursorVisible = false;
		if( SetConsoleCursorInfo(mHOutput, &info) )
			return true;
	}
	return false;
}

bool WindowsConsole::ShowCursor()
{
	if( !mIsCursorVisible )
	{
		CONSOLE_CURSOR_INFO info;

		info.dwSize = mCursorSize;
		info.bVisible = true;
		mIsCursorVisible = true;
		if( SetConsoleCursorInfo(mHOutput, &info) )
			return true;
	}
	return false;
}

bool WindowsConsole::SetCursorSize(const char &inSize)
{
	CONSOLE_CURSOR_INFO info;
	
	if( inSize>100 )
		mCursorSize = 100;
	else
		mCursorSize = inSize;
	info.dwSize = mCursorSize;
	info.bVisible = true;	
	if( SetConsoleCursorInfo(mHOutput, &info) )	
		return true;
	else
		return false;
}

char WindowsConsole::GetCursorSize()
{
	return mCursorSize;
}

HWND WindowsConsole::GetWindowHandle()
{
	return GetConsoleWindow();
}

bool WindowsConsole::ShowConsoleWindow()
{
	if( !mIsWindowVisible )
	{
		if( ShowWindow( GetConsoleWindow(), SW_SHOW) )
			return true;
	}
	return false;
}

bool WindowsConsole::HideConsoleWindow()
{
	if( mIsWindowVisible )
	{
		if( ShowWindow( GetConsoleWindow(), SW_HIDE) )
			return true;
	}
	return false;
}

bool WindowsConsole::SetWindowsSize(const short &inWidth, const short &inHeight)
{
	mWidth = inWidth;
	mHeight = inHeight;
	SMALL_RECT rect = {0, 0, mWidth - 1, mHeight - 1};

	COORD coord = GetLargestConsoleWindowSize(mHOutput);

	if( ( (mWidth >= 14) && (mWidth <= 80) ) && ( (mHeight >= 1) && (mHeight <= coord.Y) ) )
	{		
		if( SetConsoleWindowInfo(mHOutput, true, &rect) )
		{
			if( SetBufferSize(mWidth, mHeight) )
				return true;
		}
	}
	else if( ( (mWidth >= 81) && (mWidth <= coord.X) )  && ( (mHeight >= 25) && (mHeight <= coord.Y) ) )
	{
		if ( SetBufferSize(mWidth, mHeight) )
		{
			if( SetConsoleWindowInfo(mHOutput, true, &rect) )
				return true;
		}
	}
	else if( ( (mWidth >= 81) && (mWidth <= coord.X) )  && ( (mHeight >= 1) && (mHeight <= 24) ) )
	{
		if ( SetBufferSize(mWidth, mBufferHeight) )
		{
			if( SetConsoleWindowInfo(mHOutput, true, &rect) )
			{
				SetBufferSize(mWidth, mHeight);
				return true;
			}
		}
	}
		
	return false;
}

COORD WindowsConsole::GetWindowSize()
{
	COORD temp = {mWidth, mHeight};
	return temp;
}

COORD WindowsConsole::GetLargestWindowSize()
{
	COORD size = GetLargestConsoleWindowSize(mHOutput);
	return size;
}

void WindowsConsole::SetBackgroudColor(ConsoleColor inBackgroundColor)
{
	mBackgroudColor = inBackgroundColor;
	wchar_t * buffer = new wchar_t[mBufferWidth * mBufferHeight];
	WORD *attrBuffer = new WORD[mBufferWidth * mBufferHeight];
	COORD startPos = {0, 0};
	DWORD lenght;

	ReadConsoleOutputAttribute(mHOutput, attrBuffer, mBufferWidth * mBufferHeight, startPos, &lenght);
	ReadConsoleOutputCharacterW(mHOutput, buffer, mBufferWidth * mBufferHeight, startPos, &lenght);

	for(int i = 0; i < (mBufferWidth * mBufferHeight); ++i)
	{
		WORD outColor = (attrBuffer[i] & 0x0F);
		attrBuffer[i] = ( ( (mBackgroudColor & 0x0F) << 4) + (outColor & 0x0F) );
	}

	WriteConsoleOutputAttribute(mHOutput, attrBuffer, (mBufferWidth * mBufferHeight), startPos, &lenght);
	WriteConsoleOutputCharacterW(mHOutput, buffer, (mBufferWidth * mBufferHeight), startPos, &lenght);
	delete [] attrBuffer;
	delete [] buffer;
}

void WindowsConsole::SetInputColor(ConsoleColor inInputColor)
{
	mInputColor = inInputColor;
}

void WindowsConsole::SetOutputColor(ConsoleColor inOutputColor)
{
	mOutputColor = inOutputColor;
}


ConsoleColor WindowsConsole::GetBackgroudColor()
{
	return mBackgroudColor;
}

ConsoleColor WindowsConsole::GetInputColor()
{
	return mInputColor;
}

ConsoleColor WindowsConsole::GetOutputColor()
{
	return mOutputColor;
}

void WindowsConsole::Write(const std::wstring &inText, ConsoleColor inOutputColor, ConsoleColor inBackgroundColor)
{ 
	DWORD lenght;
	if( inOutputColor == ConsoleColor::None )
	{
		inOutputColor = mOutputColor;
	}
	if( inBackgroundColor == ConsoleColor::None )
	{
		inBackgroundColor = mBackgroudColor;
	}
	SetConsoleTextAttribute(mHOutput, ( (inBackgroundColor & 0x0F) << 4) + (inOutputColor & 0x0F) );
	WriteConsole(mHOutput, inText.data(), (DWORD)inText.length(), &lenght, NULL);	
}

void WindowsConsole::Writeln(const std::wstring &inText, ConsoleColor inOutputColor, ConsoleColor inBackgroundColor)
{
	Write(inText + L"\r\n", inOutputColor, inBackgroundColor);
}

void WindowsConsole::Clear(ConsoleColor inBackgroundColor)
{
	// buffer is cleared, this is new position for cursor
	COORD coord = {0, 0};

	if( inBackgroundColor == ConsoleColor::None )
	{
		inBackgroundColor = mBackgroudColor;
	}
	
	// background color and font color
	 unsigned short color = ((inBackgroundColor & 0x0F) << 4) + (mOutputColor & 0x0F);

	// number of characters that has been changed
    DWORD count;

	// console properties
    CONSOLE_SCREEN_BUFFER_INFO csbi;    
	
	// set new background and font colors
	SetConsoleTextAttribute(mHOutput, color);

	if(GetConsoleScreenBufferInfo(mHOutput, &csbi))
    {
        // fill buffer with empty spaces
        FillConsoleOutputCharacter(mHOutput, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        FillConsoleOutputAttribute(mHOutput, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
        
		// set new cursor's position
		SetConsoleCursorPosition(mHOutput, coord);
    }	
}

void WindowsConsole::Clearln()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(mHOutput, &info);
	
	// buffer is cleared, this is new position for cursor
	COORD coord = {0, info.dwCursorPosition.Y};
	
	// background color and font color
	WORD color = ((mBackgroudColor & 0x0F) << 4) + (mOutputColor & 0x0F);

	// number of characters that has been changed
    DWORD count;

	// console properties
    CONSOLE_SCREEN_BUFFER_INFO csbi;    
	
	// set new background and font colors
	SetConsoleTextAttribute(mHOutput, color);

	if(GetConsoleScreenBufferInfo(mHOutput, &csbi))
    {

		// fill buffer with empty spaces
		FillConsoleOutputCharacter(mHOutput, (TCHAR) 32, mBufferWidth, coord, &count);
		FillConsoleOutputAttribute(mHOutput, csbi.wAttributes, mBufferWidth, coord, &count );
        
		// set new cursor's position
		SetConsoleCursorPosition(mHOutput, coord);
    }	
} 

bool WindowsConsole::SetBufferSize(const short &inWidth, const short &inHeight)
{
	mBufferWidth = inWidth;
	mBufferHeight = inHeight;	
	COORD bufferCoord = {mBufferWidth, mBufferHeight};
	if( !SetConsoleScreenBufferSize(mHOutput, bufferCoord) )
		return false;
	return true;
}

COORD WindowsConsole::GetBufferSize()
{
	COORD temp = {mBufferWidth, mBufferHeight};
	return temp;
}

void WindowsConsole::Read(std::wstring &outBuffor, ConsoleColor inInputColor, ConsoleColor inBackgroundColor)
{
	if( inInputColor == ConsoleColor::None )
	{
		inInputColor = mInputColor;
	}
	if( inBackgroundColor == ConsoleColor::None )
	{
		inBackgroundColor = mBackgroudColor;
	}

	DWORD lenght;	
	SetConsoleTextAttribute(mHOutput, ( (inBackgroundColor & 0x0F) << 4) + (inInputColor & 0x0F) );
	ReadConsole( mHInput, mInputBuffer, mInputBufferSize, &lenght, 0 );
	outBuffor.clear();
	outBuffor = std::wstring(mInputBuffer, lenght - 2);	
}

void WindowsConsole::SetInputBufferSize(const short &inSize)
{
	mInputBufferSize = inSize;
}

short WindowsConsole::GetInputBufferSize()
{
	return mInputBufferSize;
}

int WindowsConsole::ReadKey()
{
	int returnCode = 0;
	
	DWORD eventCounter;
    DWORD eventsRead;
	INPUT_RECORD* eventBuffer;
	GetNumberOfConsoleInputEvents(mHInput, &eventCounter);
	eventBuffer = new INPUT_RECORD[eventCounter];

	if (eventCounter != 0) 
	{
		ReadConsoleInput(mHInput, eventBuffer, 1, &eventsRead);
		
		if (  ( eventBuffer[eventCounter - 1].EventType == KEY_EVENT ) &&
			  ( eventBuffer[eventCounter-1].Event.KeyEvent.bKeyDown) )
			returnCode = eventBuffer[eventCounter - 1].Event.KeyEvent.wVirtualKeyCode;
	}	

	delete eventBuffer;
	return returnCode;
}

void WindowsConsole::EnableEcho()
{
	DWORD mode = mConsoleMode |ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT;
	SetConsoleMode(mHInput, mode);
}

void WindowsConsole::DisableEcho()
{
	DWORD mode = mConsoleMode & ~(ENABLE_ECHO_INPUT);
	SetConsoleMode(mHInput, mode);
}