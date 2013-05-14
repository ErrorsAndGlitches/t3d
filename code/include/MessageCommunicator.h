#ifndef MESSAGE_COMMUNICATOR_H
#define MESSAGE_COMMUNICATOR_H
/**
 * @file
 * @brief Contains the MessageCommunicator class declaration.
 * @author Benjamyn
 */

#include "PlayerCommand.h"
#include "SuperBlock.h"

/**
 * @brief A MessageCommunicator provides an interface to send messages over
 * different protocols
 */
class MessageCommunicator {
	private:
		/**
		 * @brief Default constructor
		 *
		 * Hide, only allow access to static methods. Class basically provides
		 * framing encapsulation.
		 */
		MessageCommunicator();

	public:
		/**
		 * @brief Send a message of the given size and sent through the given socket
		 *
		 * @param socket The network socket to send the data through
		 * @param msg The message. Must be at least msgSize bytes
		 * @param msgSize The size in bytes of the message
		 *
		 * @return The number of bytes written into the socket
		 */
		static int sendMessage(int socket, const void *msg, size_t msgSize);

		/**
		 * @brief Receive a message sent to the socket
		 *
		 * @param socket The network socket to receive data from
		 * @param msg Buffer to store the received data
		 * @param msgSize Size of the buffer
		 *
		 * This function expects data to be waiting at the socket to be read. Use select.
		 *
		 * @return The number of bytes read from the socket
		 */
		static int recvMessage(int socket, void *msg, size_t msgSize);
};

#endif
