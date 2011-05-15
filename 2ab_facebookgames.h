/* .h extension is arbitrary here. This document contains pseudocode.
 */

/* DATA STRUCTURE FOR A FACEBOOK GAME APP
 *	(loosely follows C naming/syntax convention, but of course this structure could be in any language)
 *	Object includes _basic information_, _statistics_ to help IGN categorize/organize games by popularity and
 *	demographics, and _ratings_ to help IGN users find content they like.
 *
 *	Desgin by David Pitt 5/2011
 */

GameObject
{
	/* basics */
	int uniqueID; //unique game identifier from facebook.

	string displayName;

	categoryT category, subcategory;

	imageT gameIcon; //game image

	vector<string> tags; //eg, "educational", "violent", "funny", "casino", "multiplayer"

	GameList usersAlsoLike; //maps to a collection of other games users tend to play

	languageT language; //not all FB games are in English…
	
	vector<imageT> screenshots; //everybody loves screenshots!
	

	/* stats */
	int numUsers; //indicates overall popularity, so user can find most popular games

	int numUsersLastMonth; //recent popularity

	double avgUserAge; //indicates age demographic, this way IGN can sort games into recommended age categories (under 5, 5 - 10, 10 - 15, 15 - 20, 20 - 30, 30 - 40, 40+).

	timeT avgPlayTime; //Hrs & mins playtime _per user session_. Indicates how addicting a game is. Some IGN users might want to search for most addicting games.
	

	/* ratings */
	double difficultyRating; // 1 - 10. Some IGN users might want to browse by game difficulty.

	double facebookRating; //1 - 5, as per FB statistics.

	double ignRating; // 1 - 10. Rated by IGN users, not facebook.
}



/* CATEGORY TYPES:
 *	Facebook already provides the supercategories. Here I suggest some subcategories which
 *	IGN admins or perhaps users could use to tag games. Subcategories will help users find
 *	what they are looking for faster. Some games may fit into more than one (sub)category.
 *	This category list is not complete: admins (and maybe users?) can expand categories as necessary.
 */

/* Format: {Supercategories {subcategories}} */

CategoryT {

	ActionArcade { Sports, Driving, FirstPersonShooter, Puzzle, Platformer, Fighting, ClassicArcade  }

	BoardGame { Trivia, BrainTeaser, ClassicBG }

	CardGame { /* This one's pretty good on it's own */ }

	RolePlaying { ClassicRPG, RealTimeStrategy, SocialSim }

	VirtualWorld { CityBuilder, TowerDefense, TycoonGame }

	WordGame { /* Also pretty good on it's own */ }

	Other { PetCare, Drawing, DesignGame, Parody, Misc }

}



/* PSEUDOCODE TO BUILD GAME OBJECT FROM FACEBOOK
 *  => We make use of FQL (facebook query language) to retrieve information and statistics about each game from Facebook's "Social Graph", via the Graph API.
 *  => https://developers.facebook.com/docs/reference/api/
 */
	
GetGameInfo {
	
	Specify a game application on facebook /* (search for app name, or enter unique id) */;
		
	Retreive game app data from FB''s Social Graph;
		
	/* => https://graph.facebook.com/ID :: where ID is a unique identifier number */

	Create new GameObject x;

	// Using FQL // 

	x.uniqueID = app/graph/ID
	x.displayName = app/graph/name
	x.numUsers = app/graph/userCount
		... and so on
		
/* Follow this procedure to fill elements in GameObject from the facebook social graph.
 *	Some elements will not be available on facebook's social graph - such as ignRating.
 * 	=>Initialize such elements as NULL, until they are specified on IGN's side.
 */

}