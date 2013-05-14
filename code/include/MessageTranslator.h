#ifndef MESSAGE_TRANSLATOR_H
#define MESSAGE_TRANSLATOR_H
/**
 * @file
 * @brief Contains the MessageTranslator class declaration.
 * @author Benjamyn
 */

#include "PlayerCommand.h"
#include "SuperBlock.h"

/**
 * @brief A MessageTranslator provides an interface for game to network and
 * network to game translation.
 */
class MessageTranslator {
	private:
		/**
		 * @brief Default constructor
		 *
		 * Hide, only allow access to static methods. Class basically provides
		 * translation method encapsulation.
		 */
		MessageTranslator();

	public:
		typedef enum {
			HOST,
			START_GAME,
			ACTION,
			NUMBER_MESSAGE_TYPES
		} MessageType;

		typedef struct {
			uint32_t magic;
			uint16_t msgType;
		} MessageInfo;

		/*
		 * Structure to send and receive messages
		 */
		typedef struct {
			MessageInfo msgInfo;

			union {
				struct {
					uint32_t ipAddr;
					uint16_t portNum;
				};

				struct {
					uint16_t action; // PlayerAction::Action
					uint16_t sbType; // SuperBlock::SuperBlockType
				};
			};
		} TetrisNetworkMessage;

		/**
		 * @brief Encode the message from host to network format
		 *
		 * @param tetMsg Message to encode
		 */
		static void encode(TetrisNetworkMessage *tetMsg);

		/**
		 * @brief Decode the message from network to host format
		 *
		 * @param tetMsg Message to decode
		 */
		static void decode(TetrisNetworkMessage *tetMsg);
};

#endif
