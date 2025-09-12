#include "Disk.h"

size_t Disk::s_DiskCount = 0;

Disk::Disk()
    : m_DiskNum(++s_DiskCount)
{}

size_t Disk::GetDiskNumber() const
{
    return m_DiskNum;
}

Disk::~Disk()
{
    --s_DiskCount;
}
