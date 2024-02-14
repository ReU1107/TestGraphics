
#include "RHIDynamic.h"

namespace Alpha
{
    RHIDynamic* RHIDynamic::s_instance = nullptr;

    void RHIDynamic::SetInstance(RHIDynamic* instance)
    {
        s_instance = instance;
    }

    RHIDynamic* RHIDynamic::GetPtr()
    {
        return s_instance;
    }

    RHIDynamic::RHIDynamic()
    {
    }

    RHIDynamic::~RHIDynamic()
    {
    }

    void RHIDynamic::Init()
    {
    }

}