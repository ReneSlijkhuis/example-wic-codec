; This setup script is compiled with Inno Setup Compiler version 5.5.9
; See: http://www.jrsoftware.org/

#define AppVersion    "1.0.0"
#define AppName       "Example WIC Codec"
#define AppPublisher  "René Slijkhuis"

[Setup]
AppName =                           "{#AppName}"
AppVerName =                        "{#AppName} {#AppVersion}"
AppCopyright =                      "Copyright © 2017 {#AppPublisher}"
AppPublisher =                      "{#AppPublisher}"
AppPublisherURL =                   "http://www.slijkhuis.org/"
AppVersion =                        "{#AppVersion}"
DefaultDirName =                    "{pf}\{#AppName}"
DirExistsWarning =                  no
DisableStartupPrompt =              yes
DisableWelcomePage =                yes
DisableDirPage =                    yes
DisableProgramGroupPage =           yes
SourceDir =                         "."
OutputBaseFilename =                "Setup-ExampleWicCodec"
OutputDir =                         "."
UninstallDisplayIcon =              "{app}\WicCodec.dll"
UninstallDisplayName =              "{#AppName}"
MinVersion =                        6.1
ArchitecturesAllowed =              x64
ArchitecturesInstallIn64BitMode =   x64
PrivilegesRequired =                admin
ChangesAssociations =               yes

[Files]
; x64
Source: "..\redistributables\x64\msvcp120.dll"; DestDir: "{app}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\redistributables\x64\msvcr120.dll"; DestDir: "{app}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\codec\bin\x64\Release\WicCodec.dll"; DestDir: "{app}"; Flags: ignoreversion regserver restartreplace uninsrestartdelete

; x86
Source: "..\redistributables\x86\msvcp120.dll"; DestDir: "{pf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\redistributables\x86\msvcr120.dll"; DestDir: "{pf32}\{#AppName}"; Flags: ignoreversion restartreplace uninsrestartdelete
Source: "..\codec\bin\Win32\Release\WicCodec.dll"; DestDir: "{pf32}\{#AppName}"; Flags: ignoreversion regserver restartreplace uninsrestartdelete

[Registry]
; WIC Registry Entries
; - https://msdn.microsoft.com/en-us/library/windows/desktop/ee719880(v=vs.85).aspx

; WIC Decoder - x64
Root: HKCR; Subkey: "CLSID\{{7ED96837-96F0-4812-B211-F13C24117ED3}\Instance\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CLSID\{{7ED96837-96F0-4812-B211-F13C24117ED3}\Instance\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "CLSID"; ValueData: "{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}";
Root: HKCR; Subkey: "CLSID\{{7ED96837-96F0-4812-B211-F13C24117ED3}\Instance\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "FriendlyName"; ValueData: "Lisa Decoder";

Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: ""; ValueData: "Lisa Decoder";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "Author"; ValueData: "{#AppPublisher}";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "Description"; ValueData: "Example WIC Decoder";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "FileExtensions"; ValueData: ".lisa";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "FriendlyName"; ValueData: "Lisa Decoder";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "ContainerFormat"; ValueData: "{{91DFBD70-3D2C-440F-B297-1E2097D4A833}";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "Vendor"; ValueData: "{{E27AE9AE-D620-4AEB-AD02-E2AE03104234}";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "Version"; ValueData: "{#AppVersion}";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "MimeTypes"; ValueData: "image/lisa";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: dword;  ValueName: "SupportAnimation";  ValueData: "0";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: dword;  ValueName: "SupportChromaKey";  ValueData: "0";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: dword;  ValueName: "SupportLossless";   ValueData: "1";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: dword;  ValueName: "SupportMultiframe"; ValueData: "0";

; GUID_WICPixelFormat8bppGray
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Formats\{{6FDDC324-4E03-4BFE-B185-3D77768DC908}";
; GUID_WICPixelFormat24bppRGB
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Formats\{{6FDDC324-4E03-4BFE-B185-3D77768DC90D}";

Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\InprocServer32";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\InprocServer32"; ValueType: string; ValueName: ""; ValueData: "{app}\WicCodec.dll";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\InprocServer32"; ValueType: string; ValueName: "ThreadingModel"; ValueData: "Both";

; WIC Encoder - x64
Root: HKCR; Subkey: "CLSID\{{AC757296-3522-4E11-9862-C17BE5A1767E}\Instance\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CLSID\{{AC757296-3522-4E11-9862-C17BE5A1767E}\Instance\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "CLSID"; ValueData: "{{79CC92AA-B204-4B11-A341-1617D9CD8A88}";
Root: HKCR; Subkey: "CLSID\{{AC757296-3522-4E11-9862-C17BE5A1767E}\Instance\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "FriendlyName"; ValueData: "Lisa Encoder";

Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: ""; ValueData: "Lisa Encoder";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "Author"; ValueData: "{#AppPublisher}";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "Description"; ValueData: "Example WIC Encoder";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "FileExtensions"; ValueData: ".lisa";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "FriendlyName"; ValueData: "Lisa Encoder";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "ContainerFormat"; ValueData: "{{91DFBD70-3D2C-440F-B297-1E2097D4A833}";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "Vendor"; ValueData: "{{E27AE9AE-D620-4AEB-AD02-E2AE03104234}";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "Version"; ValueData: "{#AppVersion}";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "MimeTypes"; ValueData: "image/lisa";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: dword;  ValueName: "SupportAnimation";  ValueData: "0";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: dword;  ValueName: "SupportChromaKey";  ValueData: "0";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: dword;  ValueName: "SupportLossless";   ValueData: "1";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: dword;  ValueName: "SupportMultiframe"; ValueData: "0";

; GUID_WICPixelFormat8bppGray
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}\Formats\{{6FDDC324-4E03-4BFE-B185-3D77768DC908}";
; GUID_WICPixelFormat24bppRGB
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}\Formats\{{6FDDC324-4E03-4BFE-B185-3D77768DC90D}";

Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}\InprocServer32";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}\InprocServer32"; ValueType: string; ValueName: ""; ValueData: "{app}\WicCodec.dll";
Root: HKCR; Subkey: "CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}\InprocServer32"; ValueType: string; ValueName: "ThreadingModel"; ValueData: "Both";

Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Patterns\0";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Patterns\0"; ValueType: dword; ValueName: "Position"; ValueData: "0";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Patterns\0"; ValueType: dword; ValueName: "Length"; ValueData: "21";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Patterns\0"; ValueType: binary; ValueName: "Pattern"; ValueData: "4C 49 53 41 00 17 26 71 F7 9E CC 43 4B BC 7A 8F 21 5D 77 DE 35";
Root: HKCR; Subkey: "CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Patterns\0"; ValueType: binary; ValueName: "Mask"; ValueData: "FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF";

; WIC Decoder - x86
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{7ED96837-96F0-4812-B211-F13C24117ED3}\Instance\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{7ED96837-96F0-4812-B211-F13C24117ED3}\Instance\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "CLSID"; ValueData: "{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{7ED96837-96F0-4812-B211-F13C24117ED3}\Instance\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "FriendlyName"; ValueData: "Lisa Decoder";

Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: ""; ValueData: "Lisa Decoder";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "Author"; ValueData: "{#AppPublisher}";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "Description"; ValueData: "Example WIC Decoder";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "FileExtensions"; ValueData: ".lisa";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "FriendlyName"; ValueData: "Lisa Decoder";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "ContainerFormat"; ValueData: "{{91DFBD70-3D2C-440F-B297-1E2097D4A833}";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "Vendor"; ValueData: "{{E27AE9AE-D620-4AEB-AD02-E2AE03104234}";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "Version"; ValueData: "{#AppVersion}";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: string; ValueName: "MimeTypes"; ValueData: "image/lisa";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: dword;  ValueName: "SupportAnimation";  ValueData: "0";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: dword;  ValueName: "SupportChromaKey";  ValueData: "0";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: dword;  ValueName: "SupportLossless";   ValueData: "1";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}"; ValueType: dword;  ValueName: "SupportMultiframe"; ValueData: "0";

; GUID_WICPixelFormat8bppGray
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Formats\{{6FDDC324-4E03-4BFE-B185-3D77768DC908}";
; GUID_WICPixelFormat24bppRGB
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Formats\{{6FDDC324-4E03-4BFE-B185-3D77768DC90D}";

Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\InprocServer32";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\InprocServer32"; ValueType: string; ValueName: ""; ValueData: "{pf32}\{#AppName}\WicCodec.dll";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\InprocServer32"; ValueType: string; ValueName: "ThreadingModel"; ValueData: "Both";

; WIC Encoder - x86
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{AC757296-3522-4E11-9862-C17BE5A1767E}\Instance\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{AC757296-3522-4E11-9862-C17BE5A1767E}\Instance\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "CLSID"; ValueData: "{{79CC92AA-B204-4B11-A341-1617D9CD8A88}";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{AC757296-3522-4E11-9862-C17BE5A1767E}\Instance\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "FriendlyName"; ValueData: "Lisa Encoder";

Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: ""; ValueData: "Lisa Encoder";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "Author"; ValueData: "{#AppPublisher}";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "Description"; ValueData: "Example WIC Encoder";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "FileExtensions"; ValueData: ".lisa";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "FriendlyName"; ValueData: "Lisa Encoder";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "ContainerFormat"; ValueData: "{{91DFBD70-3D2C-440F-B297-1E2097D4A833}";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "Vendor"; ValueData: "{{E27AE9AE-D620-4AEB-AD02-E2AE03104234}";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "Version"; ValueData: "{#AppVersion}";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: string; ValueName: "MimeTypes"; ValueData: "image/lisa";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: dword;  ValueName: "SupportAnimation";  ValueData: "0";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: dword;  ValueName: "SupportChromaKey";  ValueData: "0";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: dword;  ValueName: "SupportLossless";   ValueData: "1";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}"; ValueType: dword;  ValueName: "SupportMultiframe"; ValueData: "0";

; GUID_WICPixelFormat8bppGray
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}\Formats\{{6FDDC324-4E03-4BFE-B185-3D77768DC908}";
; GUID_WICPixelFormat24bppRGB
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}\Formats\{{6FDDC324-4E03-4BFE-B185-3D77768DC90D}";

Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}\InprocServer32";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}\InprocServer32"; ValueType: string; ValueName: ""; ValueData: "{pf32}\{#AppName}\WicCodec.dll";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{79CC92AA-B204-4B11-A341-1617D9CD8A88}\InprocServer32"; ValueType: string; ValueName: "ThreadingModel"; ValueData: "Both";

Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Patterns\0";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Patterns\0"; ValueType: dword; ValueName: "Position"; ValueData: "0";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Patterns\0"; ValueType: dword; ValueName: "Length"; ValueData: "21";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Patterns\0"; ValueType: binary; ValueName: "Pattern"; ValueData: "4C 49 53 41 00 17 26 71 F7 9E CC 43 4B BC 7A 8F 21 5D 77 DE 35";
Root: HKCR; Subkey: "Wow6432Node\CLSID\{{EB68FE9B-B1D7-4E76-8B68-781E5CFB5290}\Patterns\0"; ValueType: binary; ValueName: "Mask"; ValueData: "FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF";

; PropertyHandler
Root: HKCR; Subkey: "CLSID\{{308BF946-3857-4083-B2B9-3D19093A7EA2}"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CLSID\{{308BF946-3857-4083-B2B9-3D19093A7EA2}"; ValueType: string; ValueName: ""; ValueData: "PropertyHandler";
Root: HKCR; Subkey: "CLSID\{{308BF946-3857-4083-B2B9-3D19093A7EA2}"; ValueType: dword; ValueName: "ManualSafeSave"; ValueData: "1";
Root: HKCR; Subkey: "CLSID\{{308BF946-3857-4083-B2B9-3D19093A7EA2}\InprocServer32";
Root: HKCR; Subkey: "CLSID\{{308BF946-3857-4083-B2B9-3D19093A7EA2}\InprocServer32"; ValueType: string; ValueName: ""; ValueData: "{app}\WicCodec.dll";
Root: HKCR; Subkey: "CLSID\{{308BF946-3857-4083-B2B9-3D19093A7EA2}\InprocServer32"; ValueType: string; ValueName: "ThreadingModel"; ValueData: "Apartment";

; RAW
Root: HKCR; Subkey: ".lisa"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: ".lisa"; ValueType: string; ValueName: ""; ValueData: "ExampleWicFile"; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".lisa"; ValueType: string; ValueName: "Content Type"; ValueData: "image/lisa"; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".lisa"; ValueType: string; ValueName: "PerceivedType"; ValueData: "image"; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".lisa\OpenWithList\PhotoViewer.dll"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: ".lisa\OpenWithProgids"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: ".lisa\OpenWithProgids"; ValueType: string; ValueName: "ExampleWicFile"; ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".lisa\shellex\ContextMenuHandlers\ShellImagePreview"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: ".lisa\shellex\ContextMenuHandlers\ShellImagePreview"; ValueType: string; ValueName: ""; ValueData: "{{FFE2A43C-56B9-4bf5-9A79-CC6D4285608A}"; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".lisa\shellex\{{e357fccd-a995-4576-b01f-234630154e96}"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: ".lisa\shellex\{{e357fccd-a995-4576-b01f-234630154e96}"; ValueType: string; ValueName: ""; ValueData: "{{C7657C4A-9F68-40fa-A4DF-96BC08EB3551}"; Flags: uninsdeletevalue

; Container Format
;     https://msdn.microsoft.com/en-us/library/windows/desktop/cc144133%28v=vs.85%29.aspx
;     https://msdn.microsoft.com/en-us/library/windows/desktop/dd561977%28v=vs.85%29.aspx
Root: HKCR; Subkey: "ExampleWicFile"; Flags: uninsdeletekey
Root: HKCR; Subkey: "ExampleWicFile"; ValueType: string; ValueName: ""; ValueData: "Example WIC Image"
Root: HKCR; Subkey: "ExampleWicFile"; ValueType: string; ValueName: "FullDetails"; ValueData: "prop:System.Image.HorizontalSize;System.Image.VerticalSize;System.Image.BitDepth;System.DateModified;System.DateCreated";
Root: HKCR; Subkey: "ExampleWicFile"; ValueType: string; ValueName: "PreviewDetails"; ValueData: "prop:System.Image.HorizontalSize;System.Image.VerticalSize;System.Image.BitDepth;System.Size;System.DateModified;System.DateCreated";
Root: HKCR; Subkey: "ExampleWicFile"; ValueType: string; ValueName: "TileInfo"; ValueData: "prop:System.Image.Dimensions;System.Size";
Root: HKCR; Subkey: "ExampleWicFile"; ValueType: string; ValueName: "InfoTip"; ValueData: "prop:System.Image.Dimensions;System.Image.BitDepth;System.Size;System.DateModified;System.DateCreated";

Root: HKCR; Subkey: "ExampleWicFile\shell\open";
Root: HKCR; Subkey: "ExampleWicFile\shell\open"; ValueType: expandsz; ValueName: "MuiVerb"; ValueData: "@%ProgramFiles%\Windows Photo Viewer\photoviewer.dll,-3043"

Root: HKCR; Subkey: "ExampleWicFile\shell\open\command";
Root: HKCR; Subkey: "ExampleWicFile\shell\open\command"; ValueType: expandsz; ValueName: ""; ValueData: "%SystemRoot%\System32\rundll32.exe ""%ProgramFiles%\Windows Photo Viewer\PhotoViewer.dll"", ImageView_Fullscreen %1"

Root: HKCR; Subkey: "ExampleWicFile\shell\open\DropTarget";
Root: HKCR; Subkey: "ExampleWicFile\shell\open\DropTarget"; ValueType: string; ValueName: "Clsid"; ValueData: "{{FFE2A43C-56B9-4bf5-9A79-CC6D4285608A}";

Root: HKCR; Subkey: "ExampleWicFile\shellex\ContextMenuHandlers\{{649EAC06-3FB9-42C9-BA69-88BC473130F5}";
Root: HKCR; Subkey: "ExampleWicFile\shellex\ContextMenuHandlers\{{649EAC06-3FB9-42C9-BA69-88BC473130F5}"; ValueType: string; ValueName: ""; ValueData: "ContextMenuHandler";

; Windows shell integration
;     https://msdn.microsoft.com/en-us/library/windows/desktop/cc144110%28v=vs.85%29.aspx
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\Shell Extensions\Approved"; ValueType: string; ValueName: "{{308BF946-3857-4083-B2B9-3D19093A7EA2}"; ValueData: "{#AppName}"; Flags: uninsdeletevalue
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\PropertySystem\PropertyHandlers\.lisa"; ValueType: string; ValueName: ""; ValueData: "{{308BF946-3857-4083-B2B9-3D19093A7EA2}"; Flags: uninsdeletekey

;     https://msdn.microsoft.com/en-us/library/windows/desktop/cc144136%28v=vs.85%29.aspx
Root: HKLM; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\KindMap"; ValueType: string; ValueName: ".lisa"; ValueData: "picture";