module;
#include <cstdlib>
#include <memory>
#include <unordered_map>
#include <vector>

module CustomMemoryArena;

// PRIVATE
bool CustomMemoryArena::Block::overlaps(Block b)
{
    auto intPtr = reinterpret_cast<uintptr_t>(ptr);
    auto givenIntPtr = reinterpret_cast<uintptr_t>(b.ptr);

    auto startA = intPtr;
    auto endA = intPtr + size;

    auto startB = givenIntPtr;
    auto endB = givenIntPtr + b.size;

    return startA < endB && startB < endA;
}

// PUBLIC
CustomMemoryArena::CustomMemoryArena(size_t initialAmount)
{
    void* initialBlock = malloc(initialAmount);
    if (!initialBlock)
        throw std::bad_alloc();
    Block block {
        initialBlock,
        initialAmount
    };
    memoryBlocks.push_back(block);
}

CustomMemoryArena::~CustomMemoryArena()
{
    for (Block block : memoryBlocks)
        free(block.ptr);
    memoryBlocks.clear();
}

// PUBLIC
void* CustomMemoryArena::alloc(size_t amount, size_t alignment)
{
    for (Block b : memoryBlocks)
    {
        // Could this code be worse...
        if (b.size >= amount)
        {
            size_t sizeOfBlock = b.size;

            void* alignedPtr = std::align(alignment,
                amount,
                b.ptr,
                sizeOfBlock
                );
            auto alignedIntPtr = reinterpret_cast<
                uintptr_t>(alignedPtr);
            auto alignedBlockPtr = reinterpret_cast<
                uintptr_t>(b.ptr);
            if (!alignedPtr)
                return nullptr;
            bool foundAllocation = true;

            while (!canGiveOut(
                Block {
                    alignedPtr,
                    amount
                })
            )
            {
                alignedIntPtr += alignment;

                if (alignedIntPtr + amount > alignedBlockPtr + b.size)
                {
                    foundAllocation = false;
                    break;
                }
                alignedPtr = reinterpret_cast<void*>(alignedIntPtr);
            }
            if (!foundAllocation) continue;

            blocksGivenOut.push_back({
                alignedPtr,
                amount
            });
            return alignedPtr;
        }
    }
    size_t newBlockSize = (1024 * 1024) + amount;
    void* newPtr = malloc((1024 * 1024) + amount);

    if (!newPtr) return nullptr;

    Block newBlock { newPtr, newBlockSize };
    memoryBlocks.push_back(newBlock);

    return alloc(amount, alignment);
}

void CustomMemoryArena::free(void* ptr)
{
    std::erase_if(
       blocksGivenOut,
       [ptr](Block b)
       {
           return ptr == b.ptr;
        }
    );
}

// PRIVATE
bool CustomMemoryArena::canGiveOut(Block b)
{
    for (Block b1 : blocksGivenOut)
    {
        if (b1.overlaps(b)) return false;
    }
    return true;
}

// PRIVATE
