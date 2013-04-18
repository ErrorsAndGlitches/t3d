#include "Jukebox.h"
#include "Defs.h"

Jukebox* Jukebox::registeredJukebox = NULL;

static void musicFinishedHook() 
{
	if (Jukebox::registeredJukebox) { Jukebox::registeredJukebox->cleanupMusic(); }
}

Jukebox::Jukebox(): music(NULL)
{
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFER);
	Mix_HookMusicFinished(musicFinishedHook);
}

Jukebox::~Jukebox()
{
	SDL_Quit();

	// unregister if needed
	if (this == Jukebox::registeredJukebox) {
		Jukebox::registeredJukebox = NULL;
	}
}

void Jukebox::registerJukebox()
{
	Jukebox::registeredJukebox = this;
}

int Jukebox::loadMusicFile(const char *filename) 
{
	// make sure we don't have any music current playing/loaded
	if (music) {
		cleanupMusic();
	}

	music = Mix_LoadMUS(filename);

	if (music) { return 0; }
	else { return -1; }
}

void Jukebox::playMusic() 
{
	if (music) {
		if (Mix_PlayingMusic()) {
			if (Mix_PausedMusic()) {
				Mix_ResumeMusic();
			}
		}
		else {
			Mix_PlayMusic(music, 0); // play once
		}
	}
}

void Jukebox::toggleMusic()
{
	if (music) {
		if (Mix_PlayingMusic()) { 
			if (Mix_PausedMusic()) { Mix_ResumeMusic(); }
			else { Mix_PauseMusic(); }
		}
		else {
			Mix_PlayMusic(music, 0); // play once
		}
	}
}

void Jukebox::pauseMusic() 
{
	if (music && !Mix_PausedMusic()) {
		Mix_PauseMusic(); // play once
	}
}

void Jukebox::resumeMusic()
{
	if (music && Mix_PlayingMusic() && Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
}

void Jukebox::cleanupMusic()
{
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	music = NULL;
}
