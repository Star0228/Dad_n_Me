#include "MusicSupport.h"

static int MusicState = 1;

void PlayMusic()
{
	
	switch() 
	{
		
		
		   
	       
    	  mciSendString("open music/1967.mp3", NULL, 0, NULL); mciSendString("play music/1967.mp3 repeat", NULL, 0, NULL);break;
    	  
      mciSendString("open music/lose.mp3", NULL, 0, NULL); mciSendString("play music/lose.mp3", NULL, 0, NULL);break;
    mciSendString("open music/win.mp3", NULL, 0, NULL); mciSendString("play music/win.mp3", NULL, 0, NULL); break;
    	
	}
	
	MusicState = 1;
	
    
    //注：后续可以考虑不同场景放不同音乐。
}


void CloseMusic()
{
	
	MusicState = 0;
	switch(GetCurrentGameState()) 
	{
		case WelcomePage:  
		case InitialPage:   
		case FileAbout:    
	    case EditMap:   
    	case PlayGame:  mciSendString("close music/1967.mp3", NULL, 0, NULL); break;
    	  
    	case FailGame:  mciSendString("close music/lose.mp3", NULL, 0, NULL); break;
    	case WinGame:  mciSendString("close music/win.mp3", NULL, 0, NULL);  break;
    	
	}
}

int GetMusicState()
{
	return MusicState;
}


