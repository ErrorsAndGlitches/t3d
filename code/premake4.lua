--
-- Premake4 script to generate the 3D Tetris Game, T3D
--

buildDir = "build"

-- build doxygen
newaction {
	trigger = "dox",
	description = "Creates doxygen html and latex documentation files",
	execute = function ()
		os.execute("doxygen Doxyfile")
	end
}

-- clean doxygen
newaction {
	trigger = "doxclean",
	description = "Clean doxygen files",
	execute = function ()
		os.execute("rm -r html latex")
	end
}

-- remove build directory
newaction {
	trigger = "rmbuild",
	description = "Remove build directory",
	execute = function ()
		os.execute("rm -rf "..buildDir)
	end
}

solution "T3D"
	configurations { "Release", "Debug", "Benjamyn" }
	buildoptions { "-std=c++11", "-pipe" }

	configuration "Release"
		buildoptions { "-O2" }
	configuration "Benjamyn"
		buildoptions { "-O2", "-march=corei7" }
	configuration "Debug"
		flags { "ExtraWarnings" , "Symbols" }
	configuration "DebugLinux"
		buildoptions { "-pg", "-fno-omit-frame-pointer", "-fno-omit-frame-pointer", "-fno-inline-functions-called-once", "-fno-optimize-sibling-calls" } -- gnu prof options
		flags { "ExtraWarnings" , "Symbols" }

project "T3D"
	kind "WindowedApp"
	language "C++"
	targetname "t3d"
	includedirs { "include" }
	files { "src/*.cpp", "include/*.h" } -- ** means recurse into directories
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)
		
project "Test-Layer"
	kind "WindowedApp"
	language "C++"
	targetname "t3d-test-layer"
	includedirs { "include" }
	files { "bin/test-layer.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)
		
project "Test-SuperBlock"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-superblock"
	files { "bin/test-superblock.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)
		
project "Test-Plateform"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-plateform"
	files { "bin/test-plateform.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)
		
project "Test-SuperBlockFactory"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-superblockfactory"
	files { "bin/test-superblockfactory.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)
		
project "Test-Subarena"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-subarena"
	files { "bin/test-subarena.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)
		
project "Test-Arena"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-arena"
	files { "bin/test-arena.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)

	
project "Test-World"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-world"
	files { "bin/test-world.cpp" }
    files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)


project "Test-Jukebox"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-jukebox"
	files { "bin/test-jukebox.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)

project "Test-Server"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-server"
	files { "bin/test-server.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)

project "Test-Client"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-client"
	files { "bin/test-client.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)

project "Test-Host"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-network-host"
	files { "bin/test-network-host.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)

project "Test-Join"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-network-join"
	files { "bin/test-network-join.cpp" }
	files { "src/*.cpp", "include/*.h" }
	links { "glut", "GLU", "GL", "SDL", "SDL_image", "SDL_mixer" }
	location (buildDir)
	objdir (buildDir)
