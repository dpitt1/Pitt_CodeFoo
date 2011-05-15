/* .h extension is arbitrary here. This document contains pseudocode.
 */

/* Here is a mock data-structure to store an item in the Rift Item Database
 *	See notes and documentation within.
 *	Design by David Pitt 5/2011
 */


ItemObject
{
	/* Item specifications */
	int uniqueID; //in case there are two(+) separate entries with the same name
	
	string displayName;
	
	categoryT category; //Eg., weapon, armor, consumable, accessory...
	
	subcategoryT subcategory; //Eg., sword, helmet, potion, amulet...
	
	int costSilver; //base unit is silver, can automatically convert to gold/plantinum
	
	int costPlanarites;
	
	map<currencyT, int> specialCurrencies; // currency-quantity pairs. Eg., special planarites, sourceshards, sourcestones
	
	map<string, int> ingredients; // ingredient-quantity pairs. see [Note] at bottom
	
	vector<callingT> callings; // vector contains all callings that apply. empty == all apply
	
	tradeskillT tradeskill;
	
	int requiredLevel;
	
	
	/* Item Image and Related */
	imageT image;
	
	string URL;
	
	// => for "related" see RelationGraphNode object below//
	
	
	/* Item Description */
	// >> I new to WebDev... I'm not sure how I would code the following hypertext objects //
	/*HypertextObject*/ source;
	
	/*HypertextObject*/ effects;
	
	/*HypertextObject*/ notes;
	
	
}

/* The following node object can be used to construct a graph of related items, 
 *	with arcs that specify how the items are related: eg, subSetOf, requiredFor,
 *	similarTo, etc. This graph will facilitate the construction of an ItemWiki.
 */
RelationGraphNode
{	
	ItemObject item;
	vector<relationArc> related; /* each relationArc points to another itemNode */
}


/*
 * [Note] I chose a vector of STRINGS for "ingredients" because there is such
 *	a diverse set of _ingredients_ in Rift that creating a defined categlog of
 *	ingredients	would be more trouble that in it's worth. This is one design choice
 *	that made sense to me, but it would not be hard to change it to something more defined.
 * /