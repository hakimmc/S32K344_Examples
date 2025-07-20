author  hakimmc;
date    20.07.2025;
version 1.0.0;

How to use nbc tool :

Command : ./nbc.exe {configfileaddr} {binfileaddr} {cwafilename}
For example , './nbc.exe Configs/DefaultConfig.cfg Bin/DefaultBin.bin CwaOutput/Default.cwa'

If you execute this command, you will get cwa file.

++ Note :

My post-build commands are here : 

arm-none-eabi-objcopy -v -O srec "${BuildArtifactFileName}" "${BuildArtifactFileBaseName}.s19";
arm-none-eabi-objcopy -v -O ihex "${BuildArtifactFileName}" "${BuildArtifactFileBaseName}.hex";
arm-none-eabi-objcopy -v -O binary "${BuildArtifactFileName}" "${BuildArtifactFileBaseName}.bin";
${Nbcompiler}  ${ConfigFile} "${BuildArtifactFileBaseName}.bin" "${BuildArtifactFileBaseName}.cwa"

If you havent got Nbcompiler and ConfigFile environment ; you need to set these variables int Project >> Properties >> C/C++ Build >> Environment :

ConfigFile = ${ProjDirPath}\\ConfigFile\\nbc.cfg
Nbcompiler = ${ProjDirPath}\\..\\NXPBuggerTools\\nbc.exe
