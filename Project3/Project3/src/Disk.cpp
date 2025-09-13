#include "Disk.h"

Disk::Disk(size_t p_DiskNum)
    : m_DiskNum(p_DiskNum)
{}

size_t Disk::GetDiskNumber() const
{
    return m_DiskNum;
}
