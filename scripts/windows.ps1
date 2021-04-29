Start-Process Powershell -Verb runAs
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
choco install mingw
choco install cmake
choco install make
choco install gsudo
mkdir build
cd build
cmake -G "Unix Makefiles" .. -DNO-TEST=True
make 
sudo make install