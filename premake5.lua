local match = os.matchfiles("DrachEngine.sln")
if not (#match == 0) then
    print("Removing old SLN file.")
    os.remove("DrachEngine.sln")
end
print("Building Project!")
workspace "DrachEngine"
location "."
architecture "x64"

startproject "Launcher"

configurations {"Debug", "Release"}

include "vendor"
include "launcher"
include "engine"
include "editor"

