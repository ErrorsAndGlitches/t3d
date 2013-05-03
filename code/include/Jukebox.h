#ifndef JUKEBOX_H
#define JUKEBOX_H
/**
 * @file
 * @brief Contains the Jukebox class declaration.
 * @author Benjamyn
 */
#include <cstddef>
#include <vector>
#include <string>
#include "RandomEngine.h"

#ifdef _WIN32
	#include "SDL.h"
	#include "SDL_mixer.h"
#else
	#include "SDL/SDL.h"
	#include "SDL/SDL_mixer.h"
#endif



/**
 * @brief A Jukebox encapsulates the musical audio that can be played by the user
 *
 * The Jukebox uses SDL as the backend to play audio. As a consequence of using
 * SDL, the Jukebox class is a singleton class. This is because SDL is
 * implemented in C and thus cannot access class methods.
 *
 * The default Jukebox mode is to loop through all of the songs in the playlist
 * and then stop playing. If new songs are added to the playlist while the
 * playlist is being played, then these songs will be queued.
 *
 * The SHUFFLE mode is non-terminating. The mode the jukebox is in is checked
 * after the termination of each song and the appropriate action is taken.
 *
 * The jukebox performs checks to make sure the music is in the proper mode
 * before trying to execute certain functions e.g. the jukebox will not do
 * anything if the user tries to pause music when no music is playing.
 *
 * The default mode of the jukebox is LOOP_ALL.
 */
class Jukebox {
	public:
		/**
		 * @brief Mode the jukebox should play the songs in the playlist
		 * 
		 * The Jukebox supports the following modes:
		 *   -# SINGLE: after the current song terminates, stop playing music
		 *   -# NO_LOOP: play the entire playlist sequentially and after reaching
		 *   				the last song, stop playing music
		 *   -# LOOP_ONE: repeat the current song ad infinitum
		 *   -# LOOP_ALL: cycle through the playlist sequentially and repeat the
		 * 					playlist when the last song is finished playing
		 *   -# SHUFFLE: choose a random song from the playlist ad infinitum. All
		 *   				the songs may not play before the same song is played again.
		 *
		 * If the music terminates in the particular mode, the current track is set
		 * to the next track (or to the beginning of the playlist if the end of the
		 * playlist is reached). The current track is not incremented for the
		 * LOOP_ONE mode.
		 */
		typedef enum { SINGLE, NO_LOOP, LOOP_ONE, LOOP_ALL, SHUFFLE, 
			NUMBER_JUKEBOX_MODES} JukeboxMode;

	private:
		// Single instance of the jukebox
		static Jukebox *jukeboxInstance;
		// list of files to play for music
		std::vector<std::string> *playlist;
		int trackNumber;
		// current music file being played
		Mix_Music *music;
		// Jukebox mode
		JukeboxMode jbMode;
		// random number generator enginge
		RandomEngine *randEng;

		/**
		 * @brief Initializes the jukebox to play music files, initializing the SDL
		 * backend
		 */
		Jukebox();

		/**
		 * @brief Cleans up SDL backend
		 *
		 * Deconstructor hidden so that users cannot delete the singleton instance
		 */
		~Jukebox();

		/**
		 * @brief Free the music handles/data/memory
		 */
		void cleanupMusic();

		/**
		 * @brief Increment the track number 
		 */
		void nextTrack();

		/**
		 * @brief Loads the current track
		 *
		 * This function performs NO CHECKS. Expects <music> to not have a loaded
		 * music file associated with it.
		 */
		void loadCurrentTrack();

		/**
		 * @brief Plays the current track
		 *
		 * This function performs NO CHECKS. Expects <music> to have a loaded
		 * music file associated with it.
		 */
		void playCurrentTrack();

	public:
		/**
		 * @brief Get the singleton instance of the Jukebox
		 *
		 * @return An instance of the Jukebox class
		 */
		static Jukebox* getJukeboxInstance();

		/**
		 * @brief Add file to playlist
		 *
		 * @param filename File name to add to the playlist
		 */
		void addToPlaylist(const char *filename);

		/**
		 * @brief Clear playlist of all songs and reset the track number to zero
		 */
		void clearPlaylist();

		/**
		 * @brief Get the jukebox's playlist
		 *
		 * @return A list of songs in the playlist
		 */
		std::vector<std::string> getPlaylist();

		/**
		 * @brief Set the Jukebox mode
		 *
		 * @param mode Jukebox mode
		 */
		void setJukeboxMode(JukeboxMode mode);

		/**
		 * @brief Get the Jukebox mode
		 *
		 * @return Jukebox mode
		 */
		JukeboxMode getJukeboxMode();

		/**
		 * @brief Play the current track from the beginning
		 */
		void playMusic();

		/**
		 * @brief Set the current track number
		 *
		 * If a song is currently playing, the song is terminated and the new song
		 * is played. Otherwise, only the track to be played is set. Thus, when
		 * calling playMusic(), this will cause that track to be played.
		 *
		 * If the given track number is invalid, the function does nothing.
		 *
		 * @param trackNumber Track to play
		 */
		void setCurrentTrack(int trackNumber);

		/**
		 * @brief Play the next track in accordance to whatever mode the jukebox
		 * is in.
		 */
		void playNextTrack();

		/**
		 * @brief This will cause music to play/resume if it is paused and to pause
		 * if the music is currently playing
		 *
		 * A track must have previously been playing or be paused for this function
		 * to do anything.
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
};

#endif
