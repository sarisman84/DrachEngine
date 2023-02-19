include "common.lua"

function importNlohmann(projectDir)
    local message = "--Importing Nlohmann"
    local nlohmannDir = projectDir .. "nlohmann/"
    if readSettings().use_single_include then
        message = message .. " as SINGLE_INCLUDE"
        files {nlohmannDir .. "single_include/nlohmann/*"}
        includedirs {nlohmannDir .. "single_include/"}
    else
        message = message .. " as NORMAL"
        files {nlohmannDir .. "include/nlohmann/*"}
        includedirs {nlohmannDir .. "include/"}
    end
    print(message)
end

function importEntt(projectDir)
    local message = "--Importing ENTT"
    local enttDir = projectDir .. "entt/"
    if readSettings().use_single_include then
        message = message .. " as SINGLE_INCLUDE"
        files {enttDir .. "single_include/entt/*"}
        includedirs {enttDir .. "single_include/"}
    else
        message = message .. " as NORMAL"
        files {enttDir .. "src/entt/*"}
        includedirs {enttDir .. "src/"}
    end
    print(message)
end

-- External Libraries
importLibrary = {}
importLibrary[os.realpath(directory.global_vendor .. "source/entt")] = importEntt
importLibrary[os.realpath(directory.global_vendor .. "source/nlohmann")] = importNlohmann

function importLibraries(projectDir)

    local directories = os.matchdirs(projectDir .. "*")

    for dir, func in pairs(importLibrary) do
        print(dir)
    end

    for i, directory in ipairs(directories) do
        if importLibrary[os.realpath(directory)] ~= nil then
            importLibrary[os.realpath(directory)](projectDir)
        end
    end

end
