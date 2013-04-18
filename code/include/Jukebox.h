#ifndef JUKEBOX_H
#define JUKEBOX_H
/**
 * @file
 * @brief Contains the Jukebox class declaration.
 * @author Benjamyn
 */
#include <cstddef>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

/**
 * @brief A Jukebox encapsulates the musical audio that can be played by the user
 *
 * The Jukebox uses SDL as the backend to play audio.
 */
class Jukebox {
	public:
		static Jukebox *registeredJukebox;

	private:
		Mix_Music *music;

	public:
		/**
		 * @brief Initializes the jukebox to play music files, initializing the SDL
		 * backend
		 */
		Jukebox();

		/**
		 * @brief Cleans up SDL backend
		 */
		~Jukebox();

		/**
		 * @brief Register this jukebox so that SDL knows when the song has
		 * completed
		 */
		void registerJukebox();

		/**
		 * @brief Load a music file
		 *
		 * @param filename Music file to load
		 *
		 * @return 0 on success, non-zero on error
		 */
		int loadMusicFile(const char *filename);

		/**
		 * @brief Play the music that is currently loaded
		 *
		 * If no music is loaded or if music is already playing, this does nothing.
		 */
		void playMusic();

		/**
		 * @brief This will cause music to play/resume if it is paused and to pause
		 * if the music is currently playing
		 */
		void toggleMusic();

		/**
		 * @brief Pause the music that is currently playing
		 *
		 * If no music is loaded or if music is already paused, this does nothing.
		 */
		void pauseMusic();

		/**
		 * @brief Resume music if music was previously playing
		 */
		void resumeMusic();

		/**
		 * @brief Free the music handles/data/memory
		 *
		 * This method should not be used most of the time. Instead, you should
		 * register the jukebox. The music will be cleaned up when it finishes
		 * playing.
		 */
		void cleanupMusic();
};

#endif
