@echo off
setlocal enabledelayedexpansion

set /p commitMessage="Enter your commit message: "

echo Staging all changes...
git add .

echo Committing with message: "!commitMessage!"
git commit -m "!commitMessage!"

echo Pushing to remote repository...
git push

echo All done!
pause