print("Building Project!")
workspace "DrachEngine"
location "."
architecture "x64"

startproject "Launcher"

configurations {
    "Debug", 
    "Release"
}

include "launcher"