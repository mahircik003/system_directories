#include "File.h"

Block File::getBlock(int index) const
{
    Block b;
    if (!blocks.getNodeAtIndex(index))
        return b;
    return blocks.getNodeAtIndex(index)->data;
}

size_t File::fileSize() const
{
    size_t total_size = 0;

    for (int i = 0; i < blocks.getSize(); i++)
    {
        total_size += (blocks.getNodeAtIndex(i)->data).getSize();
    }
    return total_size;
}

int File::numBlocks() const
{
    return blocks.getSize();
}

bool File::isEmpty() const
{
    return blocks.isEmpty();
}

bool File::operator==(const File &rhs) const
{
    if (blocks.getSize() != rhs.blocks.getSize())
        return false;

    Node<Block> *current = blocks.getFirstNode();
    Node<Block> *rhs_current = rhs.blocks.getFirstNode();

    for (current, rhs_current; current; current = current->next, rhs_current = rhs_current->next)
    {
        if (current->data == rhs_current->data)
            ;
        else
            return false;
    }
    return true;
}

void File::newBlock(const Block &block)
{
    blocks.append(block);
}

void File::removeBlock(int index)
{
    blocks.removeNodeAtIndex(index);
}

void File::mergeBlocks(int sourceIndex, int destIndex)
{
    blocks.mergeNodes(sourceIndex, destIndex);
}

void File::printContents() const
{
    if (isEmpty())
    {
        std::cout << "File is empty" << std::endl;
    }
    else
    {
        for (int i = 0; i < blocks.getSize(); i++)
        {
            Node<Block> *block = blocks.getNodeAtIndex(i);
            std::cout << block->data.getContent();
        }
        std::cout << std::endl
                  << fileSize() << std::endl;
    }
}