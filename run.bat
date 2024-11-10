   @echo off
   g++ raytracing.cpp -o raytracing.exe
   if %errorlevel% neq 0 (
       echo Compilation failed.
       exit /b
   )
   raytracing.exe > image.ppm
   echo Image generated: image.ppm