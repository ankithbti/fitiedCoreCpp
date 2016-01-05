#include <Message.hpp>
#include <MessageVisitor.hpp>

namespace genericTransport
{

void HBMessage::accept(boost::shared_ptr<MessageVistor> mv, ArrayBuffer buffer)
{
    mv->visit(shared_from_this(), buffer);
}

}