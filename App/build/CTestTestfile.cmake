# CMake generated Testfile for 
# Source directory: C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App
# Build directory: C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(EncryptionHelperTests "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build/EncryptionHelperTests.exe")
set_tests_properties(EncryptionHelperTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/CMakeLists.txt;131;add_test;C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/CMakeLists.txt;0;")
add_test(SettingsManagerTests "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build/SettingsManagerTests.exe")
set_tests_properties(SettingsManagerTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/CMakeLists.txt;138;add_test;C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/CMakeLists.txt;0;")
add_test(ScriptManagerTests "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build/ScriptManagerTests.exe")
set_tests_properties(ScriptManagerTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/CMakeLists.txt;145;add_test;C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/CMakeLists.txt;0;")
subdirs("qtkeychain")
