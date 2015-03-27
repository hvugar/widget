@echo off

rmdir /S /Q tmp 
rmdir /S /Q bin
rmdir /S /Q release
rmdir /S /Q debug

del Makefile 
del Makefile.Debug 
del Makefile.Release 
del *.pro.user
del object_script*

rmdir /S /Q %%X\tmp 
rmdir /S /Q %%X\bin

del %%X\vc90.pdb 
del %%X\Makefile 
del %%X\Makefile.Debug 
del %%X\Makefile.Release

