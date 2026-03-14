module;
#include <string>
#include <vector>

export module PacketType;
import Phase;

/**
 * All subclasses should be a singleton
 */
export class PacketType
{
public:
    virtual std::string getPacketIdentifier() = 0;

    virtual int getPacketID() = 0;
    virtual Phase getPhase() = 0;

    virtual bool isC2S() = 0;
public:
    virtual ~PacketType() = default;
};
