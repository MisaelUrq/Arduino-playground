@echo off

if exist rm -rd obj_android/*

if not exist bin mkdir bin
if not exist gen mkdir gen
if not exist res mkdir res
if not exist assets mkdir assets
if not exist obj mkdir obj

SET AAPT="C:\Android\android-sdk\build-tools\28.0.3\aapt.exe"
SET DX="C:\Android\android-sdk\build-tools\28.0.3\dx.bat"
SET PLATFORM_ANDROID="C:\Android\android-sdk\platforms\android-16\android.jar"
SET ZIPALIGN="C:\Android\android-sdk\build-tools\28.0.3\zipalign.exe"
SET APKSIGNER="C:\Android\android-sdk\build-tools\26.0.2\apksigner.bat"

SET BUILD_FOR_ANDROID=0
SET INSTALL_ON_PHONE=0
SET BUILD_FOR_PC=1
SET DEGUG=1

SET APP_NAME=IoT

echo "Generating R.java file"
%AAPT% package -f -m -0 apk -J "gen" -M AndroidManifest.xml -A "assets" -S "res" -I %PLATFORM_ANDROID% -F "bin\resources.ap_" || goto END

echo "Compiling source code"
javac -d "obj" -classpath "src;gen;obj" -sourcepath "gen;src;" -bootclasspath %PLATFORM_ANDROID% -g -source 7 -target   7 -encoding UTF-8 @sourcefiles || goto END

echo "Translation bytecode"
call %DX% --dex --output="bin/classes.dex" "obj" || goto END

echo "Making the apk"
%AAPT% crunch -S "res" -C "res" || goto END
%AAPT% pacakge --no-crunch -f -0 apk -m -F "bin\%APP_NAME%.unaligned.apk" -M AndroidManifest.xml -S "res" -A "assets" -I %PLATFORM_ANDROID% || goto END
mv bin\classes.dex classes.dex
%AAPT% add -v "bin\%APP_NAME%.unaligned.apk" "classes.dex" || goto END
rm classes.dex

echo "Align apk"
%ZIPALIGN% -f 4 "bin\%APP_NAME%.unaligned.apk" "bin\%APP_NAME%.unsigned.apk" || goto END

echo "sign app"
call %APKSIGNER% sign --ks debug.keystore --key-pass pass:android --ks-pass pass:android --out "bin\%APP_NAME%.apk"  "bin\%APP_NAME%.unsigned.apk" || goto END

:END
