# PasswordKeyboard
Implementation of virtual keyboard that takes some password string as an input and quits on ^q. Kind of like unix shell password prompt. This requires C++11 due to use of unique_ptr.

# Build
g++ virtualKeyboardLinux.cpp -o virtualKeyboard.out -std=c++11
