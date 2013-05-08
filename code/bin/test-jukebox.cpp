#include "Jukebox.h"
#include <unistd.h>

int main(int argc, char **argv) 
{
	Jukebox *jb = Jukebox::getJukeboxInstance();
	jb->addToPlaylist("data/awaken.mp3");
	jb->addToPlaylist("data/beginning.mp3");
	jb->addToPlaylist("data/benny.mp3");
	jb->setJukeboxMode(Jukebox::JukeboxMode::SHUFFLE);
	jb->playMusic();

	while (1) { sleep(10); jb->playNextTrack(); }

	return 0;
}
