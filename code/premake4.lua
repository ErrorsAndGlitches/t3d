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

project "T3D"
	kind "WindowedApp"
	language "C++"
	targetname "t3d"
	includedirs { "include" }
	files { "src/*.cpp", "include/*.h" } -- ** means recurse into directories
	links { "glut", "GLU", "GL", "SDL", "SDL_image" }
	location (buildDir)
	objdir (buildDir)
		
project "Test-Layer"
	kind "WindowedApp"
	language "C++"
	targetname "t3d-test-layer"
	includedirs { "include" }
	files { "bin/test-layer.cpp" }
	files { "src/*.cpp", "include/*.h" } -- ** means recurse into directories
	links { "glut", "GLU", "GL", "SDL", "SDL_image" }
	location (buildDir)
	objdir (buildDir)
		
project "Test-SuperBlock"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-superblock"
	files { "bin/test-superblock.cpp" }
	files { "src/*.cpp", "include/*.h" } -- ** means recurse into directories
	links { "glut", "GLU", "GL", "SDL", "SDL_image" }
	location (buildDir)
	objdir (buildDir)

		
project "Test-Plateform"
	kind "WindowedApp"
	language "C++"
	includedirs { "include" }
	targetname "t3d-test-plateform"
	files { "bin/test-plateform.cpp" }
	files { "src/*.cpp", "include/*.h" } -- ** means recurse into directories
	links { "glut", "GLU", "GL", "SDL", "SDL_image" }
	location (buildDir)
	objdir (buildDir)
