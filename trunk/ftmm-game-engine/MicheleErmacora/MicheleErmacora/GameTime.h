#ifndef __GameTime_h__
#define __GameTime_h__


class GameTime
{
public:
	#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX GameTime included")


	// The amount of elapsed game time since the last update.
	// public TimeSpan ElapsedGameTime { get; set; }
	Uint32 get_elapsedGameTime();

	// Gets a value indicating that the game loop is taking longer than its TargetElapsedTime. In this case, the game loop can be considered to be running too slowly and should do something to "catch up."
	bool IsRunningSlowly();

	// The amount of game time since the start of the game.
	Uint32 TotalGameTime();
};

#endif