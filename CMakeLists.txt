cmake_minimum_required(VERSION 3.12)
project(WebLogAnalyzer)

set(CMAKE_CXX_STANDARD 14)

set(CppWebLogAnalyzer CppWebLogAnalyzer/CppWebLogAnalyzer/ClientAgentClassifierThread.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/Controller.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/CounterHTTPStatus.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/DynamicApiCounterThread.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/FilePathGenerator.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/FileProc.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/HttpStatusCounterThread.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/LogFilterThread.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/main.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/Model.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/View.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/Data/DataConfig.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/Data/DataInput.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/Data/DataLog.cpp CppWebLogAnalyzer/CppWebLogAnalyzer/wlacfg.txt)

add_executable(CppWebLogAnalyzer ${CppWebLogAnalyzer})

set(LogGenerator LogGenerator/LogGenerator/main.cpp LogGenerator/LogGenerator/LogData.cpp LogGenerator/LogGenerator/Console.cpp LogGenerator/LogGenerator/ConfigData.cpp)

add_executable(LogGenerator ${LogGenerator})

set(LogMonitor LogMonitor/LogMonitor/ArgumentData.cpp LogMonitor/LogMonitor/ConfigData.cpp LogMonitor/LogMonitor/Console.cpp LogMonitor/LogMonitor/Controller.cpp LogMonitor/LogMonitor/LogData.cpp LogMonitor/LogMonitor/LogFactory.cpp LogMonitor/LogMonitor/LogMonitor.cpp LogMonitor/LogMonitor/main.cpp LogMonitor/LogMonitor/SimpleLogData.cpp)

add_executable(LogMonitor ${LogMonitor})