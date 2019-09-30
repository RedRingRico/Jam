#ifndef __JAM_DATATYPES_HPP__
#error This file should not be included directly (ErrorCodes.hpp).  Include DataTypes.hpp, instead.
#endif // __JAM_DATATYPES_HPP__

#ifndef __JAM_ERRORCODES_HPP__
#define __JAM_ERRORCODES_HPP__

namespace Jam
{
	enum class ErrorCode : SInt32
	{
		// Windowing system (XCB)
		XCBOpenDisplayFailed = -32000,
		PrimaryOutputFailure,
		PrimaryOutputInfoFailure,

		// Renderer
		InitialiseFailed = -16000,

		// System
		CloseLibraryFailed = -1000,
		// File I/O
		FileSystemAlreadyInitialised,
		InvalidFileAccessFlags,
		InvalidFileHandle,
		FileNotOpen,
		FileRewindFailed,
		ReadBytesFailed,
		WriteBytesFailed,
		MalformedFileURI,
		UnknownFileURI,
		OpenFileFailed,
		FileURIHandlerUndefined,
		NativeFileContainerOpenFailed,

		// Game
		WindowCreationFailed = -100,

		// General
		FatalError = -1,
		Okay = 0,
		Error = 1,
	};
}

#endif // __JAM_ERRORCODES_HPP__

