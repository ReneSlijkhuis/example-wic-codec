rem - Use: Developer Command Prompt VS2015

cd installer
del /F /S /Q Setup-ExampleWicCodec.exe
cd ..

cd codec
MSBuild WicCodec.sln /t:Rebuild /p:Configuration=Release /p:Platform=x64
MSBuild WicCodec.sln /t:Rebuild /p:Configuration=Release /p:Platform=x86
cd ..

cd installer
"C:\Program Files (x86)\Inno Setup 5\ISCC.exe" Setup-ExampleWicCodec.iss
cd ..
