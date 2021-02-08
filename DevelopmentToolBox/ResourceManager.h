#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <mutex>

class ResourceManager
{
public:
    static void DestoryInstance();
    static ResourceManager *Instance();

public:
    ResourceManager();
    ~ResourceManager();

private:
    static std::mutex CreatInstance_Mutex;
    static ResourceManager* m_ClassInstance;
};

#endif // RESOURCEMANAGER_H
