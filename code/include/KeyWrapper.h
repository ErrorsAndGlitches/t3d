#ifndef KEYWRAPPER_H
#define KEYWRAPPER_H
/**
 * @file
 * @brief Contains the Key Wrapper class declaration.
 * @author Zach
 */


/**
 * @brief A keyboard key can be either a normal key (a char) or a special key (an int). 
 *		This class wraps both types of keys into a common interface.
 */
class KeyWrapper
{
public:
	
	/**
	* @brief Constructor for the specified key wrapper.
	* @param key the normal keyboard key.
	*/
	KeyWrapper(unsigned char key);

	/**
	* @brief Constructor for the specified key wrapper.
	* @param key the normal keyboard key.
	*/
	KeyWrapper(int key);

	/**
	* @brief Default keyboard key constructor.
	*/
	KeyWrapper(){}
	~KeyWrapper(void){}

	/**
	* @brief Checks for equality with the specified key.
	*
	* @param otherKey the key with which to compare.
	*
	* @return true if the key is equal to the key being wrapped
	*/
	bool equals(int otherKey);

	
	/**
	* @brief Checks for equality with the specified key.
	*
	* @param otherKey the key with which to compare.
	*
	* @return true if the key is equal to the key being wrapped
	*/
	bool equals(unsigned char otherKey);

private:
	bool isSpecial;

	//Store the key value here (whether int or char)
	union { 
		unsigned char normalKey;
		int specialKey;
	} keyValue;				
};

#endif