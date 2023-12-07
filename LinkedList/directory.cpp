#include "Directory.h"

File Directory::getFile(int index) const
{
    File empty_file;
    if (index >= numFiles() || index < 0)
        return empty_file;
    return files.at(index);
}

size_t Directory::directorySize() const
{
    size_t sum = 0;
    for (int i = 0; i < numFiles(); i++)
    {
        sum = sum + files.at(i).fileSize();
    }

    return sum;
}

bool Directory::isEmpty() const
{
    if (numFiles() == 0)
        return true;
    return false;
}

size_t Directory::numFiles() const
{
    return files.size();
}

void Directory::newFile(const File &file)
{
    files.push_back(file);
}

void Directory::removeFile(int index)
{
    if (index >= files.size() || index < 0)
        return;
    files.erase(files.begin() + index);
}

void Directory::removeFile(File &file)
{
    for (int i = 0; i < numFiles(); i++)
    {
        if (files.at(i) == file)
        {
            removeFile(i);
            return;
        }
    }
}

void Directory::removeBiggestFile()
{
    File max_sized;
    int index_max;
    for (int i = 0; i < numFiles(); i++)
    {
        if (files.at(i).fileSize() > max_sized.fileSize())
        {
            max_sized = files.at(i);
            index_max = i;
        }
    }
    removeFile(index_max);
}
