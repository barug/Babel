#     ____  ___    ____  ________       ____  __ __ __    __  ___
#    / __ )/   |  / __ )/ ____/ /      / __ \/ //_// /   /  |/  /
#   / __  / /| | / __  / __/ / /      / / / / ,<  / /   / /|_/ / 
#  / /_/ / ___ |/ /_/ / /___/ /___   / /_/ / /| |/ /___/ /  / /  
# /_____/_/  |_/_____/_____/_____/   \____/_/ |_/_____/_/  /_/   
#

cmake_minimum_required(VERSION 3.5)

project(Babel)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH ./lib/gcc_64/lib/ ./src/Client/QtBabel/lib/ ./lib/)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

set(MOC_FILES
  ./src/Client/QtBabel/mainwindow.h
  ./src/Client/QtBabel/QtNet.h
  ./src/Client/QtBabel/QtGui.h
  ./src/Client/QtBabel/QtUdpSocket.h
  )

set(INCLUDES_CLIENT
  ./src/Client/QtBabel/BabelClient.h
  ./src/Client/QtBabel/Contact.h
  ./src/Client/QtBabel/Message.h
  ./src/Client/QtBabel/QtCircularBuffer.h
  ./src/Client/QtBabel/Event.hpp
  ./src/Client/QtBabel/ICircularBuffer.hpp
  ./src/Client/QtBabel/INetwork.hpp
  ./src/Client/QtBabel/IGui.hpp
  ./src/Client/QtBabel/IUdpSocket.hpp
  ./src/Client/QtBabel/include/opus/opus.h
  ./src/Client/QtBabel/include/opus/opus_multistream.h
  ./src/Client/QtBabel/include/opus/opus_types.h
  ./src/Client/QtBabel/include/opus/opus_defines.h
  ./src/Client/QtBabel/include/portaudio/portaudio.h    
  )

set(SOURCES_CLIENT
  ./src/Client/QtBabel/BabelClient.cpp
  ./src/Client/QtBabel/contact.cpp
  ./src/Client/QtBabel/Event.cpp
  ./src/Client/QtBabel/main.cpp
  ./src/Client/QtBabel/mainwindow.cpp  
  ./src/Client/QtBabel/Message.cpp
  ./src/Client/QtBabel/QtCircularBuffer.cpp
  ./src/Client/QtBabel/QtNet.cpp  
  ./src/Client/QtBabel/QtGui.cpp
  ./src/Client/QtBabel/QtUdpSocket.cpp
  ./src/Client/QtBabel/VoiceInterpreter.cpp
  ./src/Client/QtBabel/RingBuffer.cpp
  )

QT5_WRAP_CPP(manager_moc ${MOC_FILES})

include_directories(./src/Client/QtBabel/)

add_executable(client WIN32 ${SOURCES_CLIENT} ${INCLUDES_CLIENT} # ${manager_moc}
  )

QT5_USE_MODULES(client Widgets Network)

target_link_libraries(client Qt5::Widgets Qt5::Network -lpthread -lportaudio)

set(CMAKE_PREFIX_PATH ./lib/boost)

set(SOURCES_SERVER
  ./src/Server/BabelServer.cpp
  ./src/Server/BoostCircularBuffer.cpp
  ./src/Server/BoostConnexionAcceptor.cpp
  ./src/Server/BoostSerializer
  ./src/Server/BoostSocket.cpp
  ./src/Server/Client.cpp
  ./src/Server/CommandHandler.cpp
  ./src/Server/Main.cpp
  ./src/Server/Message.cpp
  ./src/Server/SocketSelector.cpp
  )

set(Boost_LIBRARY_DIR boost_serialization boost_system boost_filesystem)

add_executable(server WIN32 ${SOURCES_SERVER})
target_link_libraries(server ${Boost_LIBRARY_DIR})

