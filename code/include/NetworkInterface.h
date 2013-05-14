#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H
/**
 * @file
 * @brief Contains the NetworkInterface class declaration.
 * @author Benjamyn
 */

#include "PlayerCommand.h"
#include "SuperBlock.h"
#include "MessageTranslator.h"
#include "MessageCommunicator.h"

/**
 * @brief A NetworkInterface is a simple interface to provide networking
 * capabilities to the 3D Tetris game. It allows both hosting and connecting to
 * games. After successfully creating a full game connection with another
 * player, actions as defined in PlayerCommand can be sent across the network.
 */
class NetworkInterface {
	private:
		int sock; // socket to connect to the other player
		struct sockaddr_in oppAddr; // network address of other player
		MessageTranslator::TetrisNetworkMessage msgBuffer; // buffer for message sending/receiving

		int setupTCPServerSocket(const char *service);

		bool dataAvailable();

	public:
		/**
		 * @brief Default constructor
		 */
		NetworkInterface();

		/**
		 * @brief Host a game
		 *
		 * When returning from this function, a game connection with another player
		 * has been fully realized.
		 */
		void hostGame();

		/**
		 * @brief Join a game
		 *
		 * When returning from this function, a game connection with another player
		 * has been fully realized.
		 */
		void joinGame();

		/**
		 * @brief Release all network resources
		 */
		void endGame();

		/**
		 * @brief Send an action performed by the player
		 *
		 * @param action The action performed
		 *
		 * <em>Note: if you want to send the TEST_NEW_SUPERBLOCK action, you should
		 * use the method sendNewSuperBlock. This function implicitly sends the
		 * TEST_NEW_SUPERBLOCK action to the other player.</em>
		 */
		void sendPlayerAction(const PlayerCommand::Action action);

		/**
		 * @brief Send the new SuperBlock that has been created by this player to
		 * the other player
		 *
		 * @param sbType The new SuperBlock type
		 */
		void sendNewSuperBlock(const SuperBlock::SuperBlockType sbType);

		/**
		 * @brief Query to see if an action has been sent by the other player. If
		 * the action returned is equal to PlayerCommand::Action::ActionCount, then
		 * no actions have been received
		 *
		 * @return The action received from the other player
		 *
		 * If the Action is TEST_NEW_SUPERBLOCK, a call to getNewSuperBlock will
		 * return the SuperBlock type send by the other player.
		 */
		PlayerCommand::Action getPlayerAction();

		/**
		 * @brief Get the SuperBlock type sent by the other player
		 *
		 * @return The SuperBlock type of the other player's new SuperBlock
		 */
		SuperBlock::SuperBlockType getNewSuperBlock() const;
};

#endif
