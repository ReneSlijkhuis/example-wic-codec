# Example WIC codec
The Windows Imaging Component (WIC) provides an extensible framework for working with images and image metadata. WIC makes it possible for independent software vendors (ISVs) and independent hardware vendors (IHVs) to develop their own image codecs and get the same platform support as standard image formats (for example, TIFF, JPEG, PNG, GIF, BMP, and HDPhoto). A single, consistent set of interfaces is used for all image processing, regardless of image format, so any application using the WIC gets automatic support for new image formats as soon as the codec is installed. The extensible metadata framework makes it possible for applications to read and write their own proprietary metadata directly to image files, so the metadata never gets lost or separated from the image.  

This C++ project contains an example codec for the Lisa image format which was created to demo this codec. This example codec provides the following functionality:

* Read support for the Lisa image format.
* Write support for the Lisa image format.
* Support for the Windows Property System.

![example_3](http://www.slijkhuis.org/wic/lisa_wic_codec.png)

## Requirements
* Microsoft Windows 7 or later.
* Microsoft Visual Studio 2015 or later.
* Microsoft Visual Studio 2013 with Update 5 (needed for platform toolset "v120_xp")
* [Inno Setup Compiler](http://www.jrsoftware.org/).

## Build instructions
* Open a "Developer Command Prompt for VS2015" and change the working directory to the root of this archive.
* Run "build.bat".
* You can find the installer in the subdirectory "installer".

## Lisa image format
The Lisa image format is named to a woman (Elisabeth) and is only created for demo purposes. The table below shows version 1 of the format specification. The byte order of Lisa files should always be little-endian.

| Offset (decimal) | Data Type | Description |
| :--- | :--- | :--- |
| **0** | Char array (5 bytes) | Human readable ID.<br>```LISA``` (ASCII)<br>```4C 49 53 41 00``` (hexadecimal) |
| **5** | GUID (16 bytes) | File format ID.<br>```17 26 71 F7 9E CC 43 4B BC 7A 8F 21 5D 77 DE 35``` (hexadecimal) |
| **21** | UINT32 (4 bytes) | Format specification version.<br>This specification uses version number ```1``` (decimal) |
| **25** | UINT32 (4 bytes) | Image width in pixels. |
| **29** | UINT32 (4 bytes) | Image height in pixels. |
| **33** | UINT32 (4 bytes) | Pixel format enumeration.<br>```0``` - 8 Bits per pixel grayscale<br>```1``` - 24 Bits per pixel RGB |
| **37** | UINT32 (4 bytes) | Offset to the image data from the beginning of the file. |

## Downloads
* [Setup-ExampleWicCodec.exe](http://www.slijkhuis.org/wic/Setup-ExampleWicCodec.exe) (installs the example codec)
* [Example Lisa image 1](http://www.slijkhuis.org/wic/Hello_Kitty.lisa)
* [Example Lisa image 2](http://www.slijkhuis.org/wic/Donald_Trump.lisa)

## Other example codecs
* [FLIF Windows Codec](https://github.com/peirick/FlifWICCodec)
* [WebP WIC Codec](https://github.com/webmproject/webp-wic-codec) (no encoder or property support)

## Example WIC applications
If you’re interested in how to use WIC codecs from the application side, please have a look at:  
[example-wic-applications](https://github.com/ReneSlijkhuis/example-wic-applications)

## Disclaimer
The purpose of this project is to provide a starting point for a Windows Imaging Component (WIC) codec. Proper error handling should be added when the code is used in production environments.  

The Lisa image format is only created to demo this codec, which means that no additional application support or documentation is available.

## License
Released under the [MIT license](https://en.wikipedia.org/wiki/MIT_License).