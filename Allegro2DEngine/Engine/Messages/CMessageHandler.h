/**************************************************************************************************
// file:	Engine\Messages\CMessageHandler.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the message handler class
 **************************************************************************************************/
#ifndef A2DE_CMESSAGEHANDLER_H
#define A2DE_CMESSAGEHANDLER_H

#include "../a2de_vals.h"
#include <queue>
#include <list>
#include <set>
#include <functional>

#include "IMessageReceiver.h"
#include "IMessageSender.h"

A2DE_BEGIN

class Message;

class MessageHandler : public IMessageReceiver, public IMessageSender {

public:

    /**************************************************************************************************
    * <summary>Default constructor.</summary>
    * <remarks>Casey Ugone, 5/8/2013.</remarks>
    **************************************************************************************************/
    MessageHandler();

    /**************************************************************************************************
     * <summary>Receive message.</summary>
     * <remarks>Casey Ugone, 5/8/2013.</remarks>
     * <param name="msg">[in,out] If non-null, the message.</param>
     **************************************************************************************************/
    void ReceiveMessage(Message* msg);

    /**************************************************************************************************
     * <summary>Notifies all.</summary>
     * <remarks>Casey Ugone, 6/8/2015.</remarks>
     **************************************************************************************************/
    void NotifyAll();

    /**************************************************************************************************
     * <summary>Notifies the given receiver of the current message.</summary>
     * <remarks>Casey Ugone, 6/8/2015.</remarks>
     * <param name="receiver">[in,out] If non-null, the receiver.</param>
     **************************************************************************************************/
    void Notify(IMessageReceiver* receiver);

    /**************************************************************************************************
     * <summary>Notifies the given receiver.</summary>
     * <remarks>Casey Ugone, 6/8/2015.</remarks>
     * <param name="receiver">[in,out] If non-null, the receiver.</param>
     **************************************************************************************************/
    void Notify(IMessageReceiver* receiver, Message* msg);

    /**************************************************************************************************
     * <summary>Peeks a message without removing it from the queue.</summary>
     * <remarks>Casey Ugone, 5/8/2013.</remarks>
     * <returns>null if it fails, else the message.</returns>
     **************************************************************************************************/
    Message* PeekMessage();

    /**************************************************************************************************
     * <summary>Removes the next message from the queue and returns it.</summary>
     * <remarks>Casey Ugone, 5/8/2013.</remarks>
     * <returns>null if it fails, else the next message.</returns>
     **************************************************************************************************/
    Message* Next();

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 5/8/2013.</remarks>
     **************************************************************************************************/
    virtual ~MessageHandler();

    /**************************************************************************************************
     * <summary>Registers the recipient described by recipient.</summary>
     * <remarks>Casey Ugone, 5/8/2013.</remarks>
     * <param name="recipient">[in,out] If non-null, the recipient.</param>
     **************************************************************************************************/
    void RegisterRecipient(IMessageReceiver* recipient);

    /**************************************************************************************************
     * <summary>Un register recipient.</summary>
     * <remarks>Casey Ugone, 5/8/2013.</remarks>
     * <param name="recipient">[in,out] If non-null, the recipient.</param>
     **************************************************************************************************/
    void UnRegisterRecipient(IMessageReceiver* recipient);

    /**************************************************************************************************
     * <summary>Gets the size.</summary>
     * <remarks>Casey Ugone, 5/8/2013.</remarks>
     * <returns>.</returns>
     **************************************************************************************************/
    std::size_t Size();

    /**************************************************************************************************
     * <summary>Query if this object is empty.</summary>
     * <remarks>Casey Ugone, 5/8/2013.</remarks>
     * <returns>true if empty, false if not.</returns>
     **************************************************************************************************/
    bool IsEmpty();

protected:

    /**************************************************************************************************
     * <summary>Sends a message.</summary>
     * <remarks>Casey Ugone, 6/8/2015.</remarks>
     * <param name="receiver">[in,out] If non-null, the receiver.</param>
     * <param name="msg">     [in,out] If non-null, the message.</param>
     **************************************************************************************************/
    void SendMessage(IMessageReceiver* receiver, Message* msg);
private:

    /// <summary> Queue of messages </summary>
    std::queue<Message*, std::list<Message*> > _message_queue;
    /// <summary> The message recipients </summary>
    std::set<IMessageReceiver*> _message_recipients;

};

A2DE_END

#endif