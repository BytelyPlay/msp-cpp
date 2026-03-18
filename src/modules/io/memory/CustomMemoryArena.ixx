module;
#include <vector>

export module CustomMemoryArena;

/**
 * It's more of an allocator.
*/ /* export */ class CustomMemoryArena
{
private:
    struct Block
    {
        void* ptr;
        size_t size;

        bool overlaps(Block b);
    };
public:
    CustomMemoryArena(size_t initialAmount);
    ~CustomMemoryArena();
public:
    void* alloc(size_t amount, size_t alignment);
    void free(void* ptr);
private:
    bool canGiveOut(Block b);
private:
    std::vector<Block> memoryBlocks;
    std::vector<Block> blocksGivenOut;
};
