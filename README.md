# StackPlusPlus - A genuine replica

Well, at least it's not COBOL...

# First-time use

* Rename .example.\*.store to just *.store in /database
* Make sure the project settings and the linker detect the dependencies in /vendor:
    * Open the project settings and under C/C++ -> General make sure to have the include folder for each dependency added at the additional include box
    * Next, under Linker -> Input add the .lib file for each dependency at additional dependencies 
    * If you are still getting errors, make sure the .dll is in the /app folder

## Testing

* https://vld.codeplex.com/ - For memory leaks under debug mode