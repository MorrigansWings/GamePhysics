
SET ARC_PATH="C:\Users\Stephen\Desktop\Repositories\Arc-2.0"

xcopy /s /y %ARC_PATH%\Debug\ArcCore.lib lib\ArcCore.lib
xcopy /s /y %ARC_PATH%\Debug\ArcData.lib lib\ArcData.lib

xcopy /s /y %ARC_PATH%\Modules\ArcCore\Arc\*.h include\Arc\
xcopy /s /y %ARC_PATH%\Modules\ArcData\Arc\*.h include\Arc\